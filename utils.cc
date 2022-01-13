#include "utils.hh"


void print_tetravex(std::vector<std::array<int, 5>> tetravex) {
    for (int i = 0; i < sqrt(tetravex.size()); i++) {
        for (int j = 0; j < sqrt(tetravex.size()); j++) {
            std::cout << "+-----";
        }
        std::cout << "+\n";

        for (int j = 0; j < sqrt(tetravex.size()); j++) {
            std::cout << "|  " << tetravex[sqrt(tetravex.size()) * i + j][0] << "  ";
        }
        std::cout << "|\n";

        for (int j = 0; j < sqrt(tetravex.size()); j++) {
            std::cout << "| " << tetravex[sqrt(tetravex.size()) * i + j][1] << " "
                << tetravex[sqrt(tetravex.size()) * i + j][2] << " ";
        }
        std::cout << "|\n";

        for (int j = 0; j < sqrt(tetravex.size()); j++) {
            std::cout << "|  " << tetravex[sqrt(tetravex.size()) * i + j][3] << "  ";
        }
        std::cout << "|\n";
    }

    for (int j = 0; j < sqrt(tetravex.size()); j++) {
        std::cout << "+-----";
    }
    std::cout << "+\n";
}
