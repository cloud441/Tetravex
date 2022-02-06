#pragma once

#include <iostream>
#include <vector>
#include <array>
#include <math.h>

int compute_cost(std::vector<std::array<int, 5>> tetravex);

void swap_tile(int i, int j, std::vector<std::array<int, 5>> tetravex);

std::array<int, 2> select_random_tile(std::vector<int> valid_tile);

std::vector<std::array<int, 5>> solve(std::vector<std::array<int, 5>> tetravex, bool debug);
