#ifndef ACTION_HH
#define ACTION_HH

#include <string>
#include <vector>
#include <ostream>
#include <functional>

struct action {
	std::vector<char*> args;
	std::function<int(std::vector<char*>&)> builtin;
	bool is_builtin;

	void push_arg(const char* tok);
	int act();

	action() = default;
	action(const action&) = delete;
	action& operator=(const action&) = delete;

	action(action&& other) noexcept : args(std::move(other.args)) {
		other.args.clear();
	}

	action& operator=(action&& other) noexcept {
		if (this != &other) {
			for (auto ptr : args) free(ptr);
			args = std::move(other.args);
			other.args.clear();
		}
		return *this;
	}

	void print_args(std::ostream& os) const {
		os << "args: ";
		for (auto* arg : args) {
			if (arg) {
				os << " {" << arg << "}";
			}
		}
		os << "\n";
	}
	
	~action() {
		for (auto ptr : args) {
			free(ptr);
		}
	}
};

#endif
