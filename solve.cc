#include <iostream>
#include <vector>
#include <array>
#include <random>
#include <time.h>

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
				if (tetravex[index][0] != tetravex[index - size][3])
				{
					cost += 1;
				}
			}

			if (i != size - 1)
			{
				if (tetravex[index][3] != tetravex[index + size][0])
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

	
	std::array<int, 2> res;
	int size = valid_tile.size();

	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> uni(0,size - 1);
	
	int v1 = uni(rng);
	int v2 = uni(rng);

	if (v1 == v2)
	{
		v2 = (v2 + 1) % size;
	}

	res[0] = valid_tile[v1];
	res[1] = valid_tile[v2];

	return res;
}

std::vector<std::array<int, 5>> solve(std::vector<std::array<int, 5>> tetravex, bool debug)
{
	int time = 0;

	if (debug)
		std::cout << "Our Tetravex is the following : " << std::endl;

	
	std::vector<std::array<int, 5>> solve_tetravex = tetravex;
	std::vector<int> tile_to_move;

	for (int i = 0; i < tetravex.size(); i++)
	{
		if (tetravex[i][4] == 0)
		{
			tile_to_move.push_back(i);
		}
	}

	if (debug)
		std::cout << "We can move the following tiles :";

	for (int i = 0; i < tile_to_move.size(); i++)
	{
		if (debug)
			std::cout << " " << tile_to_move[i];
	}

	if (debug)
		std::cout << "\n" << std::endl;


	int cost = compute_cost(tetravex);
	double temperature = 4 * tetravex.size() - 4 * sqrt(tetravex.size());
	double factor = 0.9999999;
	int nb_step = 0;
	int last_upgrade = 0;

	if (debug)
		std::cout << "Before first step we have :\n\tcost : " << cost << "\n\ttemperature : ";
	
	
	if (debug)
		std::cout << temperature << "\n\tstep : " << nb_step << "\n\n" << std::endl;


	while (cost != 0)
	{
		if (debug)
			std::cout << "\n\nWe start the step " << nb_step << std::endl;

		solve_tetravex = tetravex;
		std::array<int, 2> next_move = select_random_tile(tile_to_move);

		if (debug)
			std::cout << "We will move the tiles : " << next_move[0] << " and " << next_move[1];
		if (debug)
			std::cout << std::endl;

		solve_tetravex = swap_tile(next_move[0], next_move[1], solve_tetravex);
		if (debug)
			std::cout << "\n" << std::endl;
		if (debug)
			print_tetravex(solve_tetravex);
		if (debug)
			std::cout << "\n" << std::endl;

		int temp_cost = compute_cost(solve_tetravex);

		if (debug)
			std::cout << "Our new cost is now : " << temp_cost << std::endl;

		if (temp_cost < cost)
		{
			if (debug)
				std::cout << "We have a better cost so we change it" << std::endl;
			tetravex = solve_tetravex;
			cost = temp_cost;
			last_upgrade = nb_step;
		}
		else
		{
			if (debug)
				std::cout << "Our cost is not better" << std::endl;
	
			std::random_device rd;
			std::mt19937 rng(rd());
			std::uniform_int_distribution<int> uni(0,100);
	
			int v1 = uni(rng);
			double nb = (double)(v1) / 100;

			double compare_value = exp(-(temp_cost - cost) / temperature);

			if (debug)
				std::cout << "So we have a random at " << v1 << " and a value of ";
			if (debug)
				std::cout << compare_value << std::endl;

			if (nb <= compare_value)
			{
				if (debug)
					std::cout << "So we change because we have the proba" << std::endl;
				tetravex = solve_tetravex;
				cost = temp_cost;
			}
		}

		nb_step++;
		temperature = factor * temperature;

		/*
		if ((nb_step - last_upgrade) > 100000)
		{
			temperature += (int)(((4 * tetravex.size() - 4 * sqrt(tetravex.size())) - temperature) / 2);
		}*/
	}


	if (debug)
		std::cout << "We have resolve the tetravex in " << nb_step << std::endl;

	time = clock();
	std::cout << "Solve in " << time << " and in " << nb_step << " step !" << std::endl;

	return solve_tetravex;
}
