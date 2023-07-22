// SPDX-License-Identifier: GPL-3.0-only

#include <string>
#include <vector>
#include <iostream>

int main(int argc, char *argv[])
{
	std::vector<std::string> args(argv + 1, argv + argc);
	for(std::string arg : args)
		std::cout << arg << "\n";
	
    return 0;
}

