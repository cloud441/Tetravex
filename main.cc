#include <iostream>
#include <vector>
#include <array>

#include "mediamanager.hh"
#include "utils.hh"
#include "solve.hh"
#include "test.hh"

int main(int argc, char **argv) {
    
	if (argc != 3) {
        	std::cerr << "Error: You need to give exactly 2 arguments: a input filepath, and a output filepath." << std::endl;
        	return 1;
    	}

    mediaManager m_manager = mediaManager();

    if (m_manager.read_file(argv[1]) == 1)
        return 1;

    std::vector<std::array<int, 5>> tetravex = m_manager.get_input_tetravex();
    if (tetravex.empty())
        return 1;

    tetravex = solve(tetravex, false);

    m_manager.write_tetravex_file(argv[2], tetravex);

    return 0;
}
