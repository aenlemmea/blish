#ifndef BLISH_HH
#define BLISH_HH

#include <system_error>
#include <iostream>

struct blish {
	std::error_code error; // Track error after each exec
	std::istream& inp;
	std::ostream& out;
	std::string config_path;

	blish(std::error_code err, std::istream& i, std::ostream& o, 
		std::string_view conf) : error(err), inp(i), out(o), 
		config_path(conf) {}

	blish() = delete;

	inline void prompt(std::string_view pr) const;
	[[noreturn]] void run()  noexcept;
};

#endif
