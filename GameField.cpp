#include "GameField.h"
#include <random>
#include <fstream>

Generation::Generation(int _width, int _height) :width(_width), height(_height), cells(width)
{
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			cells[i].emplace_back(std::vector<Cell*>());
			cells[i][j].emplace_back(new Cell(false)); // cell itself
		}
	}

	initialize_neighbours();
}
void Generation::initialize_neighbours()
{
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			auto* d = &get(x - 1, y + 1);
			cells[x][y].emplace_back(&get(x - 1, y + 1));
			cells[x][y].emplace_back(&get(x - 1, y));
			cells[x][y].emplace_back(&get(x - 1, y - 1));
			cells[x][y].emplace_back(&get(x, y - 1));
			cells[x][y].emplace_back(&get(x + 1, y - 1));
			cells[x][y].emplace_back(&get(x + 1, y));
			cells[x][y].emplace_back(&get(x + 1, y + 1));
			cells[x][y].emplace_back(&get(x, y + 1));
		}
	}
}
void Generation::change()
{
	std::vector<std::pair<std::pair<int, int>, bool>> updates;
	for (int i = 0; i < cells.size(); i++)
	{
		for (int j = 0; j < cells[i].size(); j++)
		{
			int count = 0;
			auto& cell = cells[i][j][0];
			for (int k = 1; k < cells[i][j].size(); k++)
			{
				if (cells[i][j][k]->alive) count++;
			}
			if (cell->alive) {
				if (count < 2 || count>3) {
					//if(count < 2 || count>6){
					updates.push_back({ {i,j},false }); // kill
				}
			}
			else if (count == 3) {
			//else if (count > 1 && count < 8){
				updates.push_back({ { i,j }, true }); // reproduce
			}
		}
	}

	for (int i = 0; i < updates.size(); i++)
	{
		if (updates[i].second) {
			cells[updates[i].first.first][updates[i].first.second][0]->alive = true;
		}
		else {
			cells[updates[i].first.first][updates[i].first.second][0]->alive = false;
		}
	}
}
int Generation::size() const
{
	if (cells.size() < 1 || cells[0].size() < 1) return 0;
	return cells.size() * cells[0].size();
}

Generation::Cell& Generation::get(int x, int y)
{
	return *cells[x >= 0 ? x % width : width - (-x % width)][y >= 0 ? y % height : height - (-y % height)][0];
}
void Generation::fill(int x, int y)
{
	get(x, y).alive = true;
}
void Generation::create_glider(int x, int y)
{
	fill(x, y);
	fill(x - 1, y - 1);
	fill(x + 1, y - 2);
	fill(x, y - 2);
	fill(x - 1, y - 2);
}
void Generation::create_random_field()
{
	std::random_device dev;
	std::mt19937 rng(dev());
	for (size_t i = 0; i < cells.size(); i++) {
		for (size_t j = 0; j < cells[i].size(); j++) {
			std::uniform_int_distribution<std::mt19937::result_type> num(1, 7);
			if (num(rng) > 6) {
				cells[i][j][0]->alive = true;
			}
		}
	}
}
void Generation::print() const
{
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++) {
			if (cells[j][i][0]->alive)std::cout << pix;
			else std::cout << empty_pix;
		}
}
void Generation::save_as_ppm(const std::string& filename) const
{
	std::ofstream fout;
	fout.open(filename + ".ppm");
	fout << "P3\n" + std::to_string(height) + " " + std::to_string(width) + "\n1\n";

	for (int i = 0; i < cells.size(); i++) {
		for (int j = 0; j < cells[i].size(); j++)
		{
			if (cells[i][j][0]->alive)fout << "1 1 1 ";
			else fout << "0 0 0 ";
		}
	}

	fout.close();
}