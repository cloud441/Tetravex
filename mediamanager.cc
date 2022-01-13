#include "mediamanager.hh"

int mediaManager::read_file(std::string filepath) {
    this->input_file.open(filepath);

    if (!(this->input_file.is_open())) {
        std::cerr << "Error: input file couldn't be read." << std::endl;
        return 1;
    }

    return 0;
}

/*
   A Tetravex is represented as a matrix of size (tile_number, 5). the 4 first value of each line
   are the value in each tile, and the last value is a 1/0 according to the condition "Does the
   tile is well positioned."
 */
std::vector<std::array<int, 5>> mediaManager::get_input_tetravex() {
    std::vector<std::array<int, 5>> tetravex;
    std::array<int, 5> tile;
    std::string line;
    int line_idx = 1;

    if (!(this->input_file.is_open())) {
        std::cerr << "Error: input stream is already empty, maybe you are doing a useless double read." << std::endl;
        return {};
    }

    while (std::getline(this->input_file, line)) {

        // Does the tile is well positioned ?
        tile[4] = ((line.length() == 6) && (line.at(5) == '@')) ? 1 : 0;
        if (line.length() == 6)
            line = line.substr(0, line.length() - 2);


        if (line.length() != 4) {
            std::cerr << "Error: input tetravex in badly formatted at line: " << line_idx << std::endl;
        }

        for (int i = 0; i < 4; i++) {
            if (line[i] < '0' || line[i] > '9') {
                std::cerr << "Error: input tetravex in badly formatted at line: " << line_idx << std::endl;
                return {};
            }
            tile[i] = int(line[i] - '0');
        }

        tetravex.push_back(tile);
        line_idx++;
    }

    int tmp_sqrt = sqrt(--line_idx);
    if (tmp_sqrt * tmp_sqrt != line_idx) {
        std::cerr << "Error: input tetravex shape isn't a square." << std::endl;
        return {};
    }

    return tetravex;
}


void mediaManager::write_tetravex_file(std::string filepath, std::vector<std::array<int, 5>> tetravex) {
    std::ofstream output_file;
    output_file.open(filepath, std::ofstream::out | std::ofstream::trunc);

    for (auto tile: tetravex) {
        output_file << tile[0] << tile[1] << tile[2] << tile[3] << '\n';
    }
}
