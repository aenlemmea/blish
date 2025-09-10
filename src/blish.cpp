#include "blish.h"
#include "parse.h"
#include <string>

void blish::prompt(std::string_view pr) const {
	out << pr << std::flush;
}

void blish::run()  noexcept {
	std::string line;
	while(true) {
		if (static_cast<bool>(error)) {
			out << "ERROR: " << error.message() << "\n";
			error.clear();
		 	exit(EXIT_FAILURE);
		}
		this->prompt(":: ");
		
		if (!std::getline(inp, line)) break;
		if (line == "exit") exit(EXIT_SUCCESS);
		if (line == "") continue;

		action c = parse(line);
		c.act();
	}
}

