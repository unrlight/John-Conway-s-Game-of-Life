#pragma once
#include <vector>
#include <ostream>
#include <string>
#include <iostream>

#define pix char('@')
#define empty_pix char(' ')

class Generation
{
	//class Cell
	//{
	//	//std::vector<Cell*> neighbours;
	//	bool alive;
	//public:
	//	const int x;
	//	const int y;
	//	Cell(const int _x, const int _y, const bool _alive) :x(_x), y(_y), alive(_alive) {}
	//	//Cell copy() const { return Cell(x, y, alive); }
	//	bool is_alive() const { return alive; }
	//	//void push_back(Cell& cell) { /*neighbours.emplace_back(&cell);*/ }
	//	//int alive_neighbours() const {
	//	//	int count = 0;
	//	//	for (size_t i = 0; i < neighbours.size(); i++)
	//	//		if (neighbours[i]->is_alive()) count++;
	//	//	return count;
	//	//}
	//	void kill() { alive = false; }
	//	void reproduce() { alive = true; }
	//	Cell& operator=(const Cell& other) {
	//		*const_cast<int*>(&x) = other.x;
	//		*const_cast<int*>(&y) = other.y;
	//		alive = other.alive;
	//		return *this;
	//	}
	//	//Cell& operator[](int i) { return *neighbours[i]; }
	//}; // Cell

	struct Cell {
		bool alive;
		Cell(bool _alive = false) :alive{ _alive } {}
	};

	const int width;
	const int height;
	const int neighboursCount = 8;
	std::vector<std::vector<std::vector<Cell*>>> cells;

	void initialize_neighbours();
	Cell& get(int x, int y);

public:
	Generation(int _width, int _height);
	//void emplace_back(int x, int y, bool alive);
	void change();
	int size() const;
	//Cell& get(int x, int y);
	void fill(int x, int y);
	void create_glider(int x, int y);
	void create_random_field();
	//Cell& operator[](int i);
	void print() const;
	void save_as_ppm(const std::string& filename) const;
}; // Generation


class test
{
public:
	static void _GameField()
	{
		const int width = 1921;
		const int height = 1081;
		const int generations = 1000;

		Generation gen(width, height);
		//gen.create_glider(width/2, height/2);
		gen.create_random_field();
		//gen.fill(-1, 1);
		//gen.fill(-1, 0);
		//gen.fill(0, 0);
		//gen.fill(0, 1);
		//gen.fill(width / 2, height / 2);

		//gen.fill(width/2+0, height/2+0);
		//gen.fill(width / 2 -3, height / 2 + -1);
		//gen.fill(width / 2 -2, height / 2 + -1);
		//gen.fill(width / 2 -2, height / 2 + 1);
		//gen.fill(width / 2+1, height / 2 + -1);
		//gen.fill(width / 2+2, height / 2 + -1);
		//gen.fill(width / 2+3, height / 2 - 1);
		gen.print();

		for (int i = 0; i < generations; i++) {
			getchar();
			gen.change();
			gen.print();
		}

	}
	static void _save_as_ppm()
	{
		const int width = 1000;
		const int height = 1000;
		const int generations = 1000;
		Generation gen(width, height);
		gen.fill(width / 2, height / 2);
		gen.fill(width / 2 + 1, height / 2);
		gen.fill(width / 2, height / 2 + 1);
		gen.fill(width / 2 + 1, height / 2 + 1);
		//gen.fill(width/2, height/2);
		//gen.fill(-3, -1);
		//gen.fill(-2, -1);
		//gen.fill(-2, 1);
		//gen.fill(1, -1);
		//gen.fill(2, -1);
		//gen.fill(3, -1);
		/*gen.fill(width / 2 - 3, height / 2 + -1);
		gen.fill(width / 2 - 2, height / 2 + -1);
		gen.fill(width / 2 - 2, height / 2 + 1);
		gen.fill(width / 2 + 1, height / 2 + -1);
		gen.fill(width / 2 + 2, height / 2 + -1);
		gen.fill(width / 2 + 3, height / 2 - 1);*/
		for (int i = 0; i < generations; i++) {
			std::cout << std::to_string(i + 1) + "/" + std::to_string(generations) + "\n";
			gen.change();
		}

		gen.save_as_ppm("C:\\out");
	}
	static void _save_as_gif() {
		const int width = 21;
		const int height = 21;
		const int generations = 10;
		//GameField field(width, height);
		Generation field(width, height);
		field.create_glider(0, 0);

		for (int i = 0; i < generations; i++) {
			field.change();
		}

		//field.save_as_gif("C:\\1gif");
	}
};