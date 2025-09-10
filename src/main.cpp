#include "blish.h"

int main() {
	blish shell{ {}, std::cin, std::cout, "config.conf" };
	shell.run();
}
