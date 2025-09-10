#include <map>
#include <string_view>
#include <sstream>
#include "blish.h"
#include "action.h"

#include <unistd.h>

const std::map<const std::string, std::error_code> err_map = {
	{"invalid_args",  std::make_error_code(std::errc::invalid_argument)},
};

// TODO: Remove this, have separate files for builtins
int cd_builtin(std::vector<char*>& args) {
	if (args.size() < 2) {
		return -1;
	}
	if (chdir(args[1]) != 0) {
		perror("cd");
		return errno;
	}
	return 0;
}

const std::map<std::string, std::function<int(std::vector<char*>&)>> 
	builtin_map = {
		{"cd", cd_builtin}
	};


blish& register_error(blish& sh, std::string_view err) {
 	if (auto it = err_map.find(std::string(err)); it != err_map.end()) {
		sh.error = it->second;
	} else {
		sh.error = std::make_error_code(std::errc::bad_message);
	}
	return sh;
}

action parse(const std::string& line) {
	action act;
	std::istringstream iss(line);
	std::string token;

	while(iss >> token) {
		if (auto it = builtin_map.find(token); it != builtin_map.end()) {
			act.builtin = it->second;			
		}
		act.push_arg(token.c_str());
	}
	return act;
}
