#include <iostream>
#include <vector>
#include <array>
#include <random>

#include "utils.hh"
#include "mediamanager.hh"


int compute_cost(std::vector<std::array<int, 5>> tetravex)
{
	int size = sqrt(tetravex.size());
	int cost = 0;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			int index = i * size + j;

			if (i != 0)
			{
				if (tetravex[index][0] != tetravex[index - size][4])
				{
					cost += 1;
				}
			}

			if (i != size - 1)
			{
				if (tetravex[index][4] != tetravex[index + size][0])
				{
					cost += 1;
				}
			}

			if (j != 0)
			{
				if (tetravex[index][1] != tetravex[index - 1][2])
				{
					cost += 1;
				}
			}

			if (j != size - 1)
			{
				if (tetravex[index][2] != tetravex[index + 1][1])
				{
					cost += 1;
				}
			}
		}
	}

	return cost / 2;

}

std::vector<std::array<int, 5>> swap_tile(int i, int j, std::vector<std::array<int, 5>> tetravex)
{
	std::array<int, 5> temp = tetravex[i];
	tetravex[i] = tetravex[j];
	tetravex[j] = temp;

	return tetravex;
}


std::array<int, 2> select_random_tile(std::vector<int> valid_tile)
{

	srand(time(NULL));
	
	std::array<int, 2> res;
	int size = valid_tile.size();

	int v1 = rand() % size;
	int v2 = rand() % size;

	if (v1 == v2)
	{
		v2 = (v2 + 1) % size;
	}

	res[0] = valid_tile[v1];
	res[1] = valid_tile[v2];

	return res;
}

std::vector<std::array<int, 5>> solve(std::vector<std::array<int, 5>> tetravex)
{
	std::vector<std::array<int, 5>> solve_tetravex = tetravex;
	std::vector<int> tile_to_move;

	for (int i = 0; i < tetravex.size(); i++)
	{
		if (tetravex[i][4] == 0)
		{
			tile_to_move.push_back(i);
		}
	}


	int cost = compute_cost(tetravex);
	double temperature = 100;
	double factor = 0.99;

	int nb_step = 0;

	while (cost != 0 and nb_step < 10)
	{
		solve_tetravex = tetravex;
		std::array<int, 2> next_move = select_random_tile(tile_to_move);

		solve_tetravex = swap_tile(next_move[0], next_move[1], solve_tetravex);
		int temp_cost = compute_cost(solve_tetravex);

		if (temp_cost <= cost)
		{
			tetravex = solve_tetravex;
			cost = temp_cost;
		}
		else
		{
			srand(time(NULL));
			double nb = (double)(rand() % 100) / 100;

			double compare_value = exp(-(temp_cost - cost) / temperature);

			if (nb <= compare_value)
			{
				tetravex = solve_tetravex;
				cost = temp_cost;
			}
		}

		nb_step++;
		temperature = factor * temperature;
	}

	print_tetravex(tetravex);

	return solve_tetravex;
}
