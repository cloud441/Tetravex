#include <iostream>
#include <vector>
#include <array>

#include "mediamanager.hh"
#include "utils.hh"


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

    print_tetravex(tetravex);

    return 0;
}
