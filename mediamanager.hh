#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <array>
#include <math.h>

class mediaManager {
    private:

        std::ifstream input_file;


    public:

        int read_file(std::string filepath);
        std::vector<std::array<int, 5>>get_input_tetravex();
        void write_tetravex_file(std::string filepath, std::vector<std::array<int, 5>> tetravex);
};
