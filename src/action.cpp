#include "action.h"
#include <sys/types.h>
#include <cstring>
#include <unistd.h>
#include <cassert>
#include <sys/wait.h>

void action::push_arg(const char* arg) {
	args.push_back(strdup(arg));
}

static int spawn(std::vector<char*>& args) {
	 args.push_back(nullptr);

	 pid_t child_pid = fork();
	 if (child_pid != 0) {
		int status;
		waitpid(child_pid, &status, 0);
		return child_pid;
	 } else {
		execvp(args[0], args.data());
		abort(); // Not sure propagate error back up.
	 }
}

int action::act() {
	if (builtin) {
		return builtin(args);
	}
	int ret = spawn(args);
	assert(ret != 0);
	return ret;
}

