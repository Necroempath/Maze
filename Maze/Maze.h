#pragma once
#include "Stack.h"
#include "UniquePtr.h"
#include <windows.h>
#define white 7
class Entity
{
public:
    virtual char GetSymbol() const = 0;
    virtual int GetColorCode() const = 0;

    virtual ~Entity() = default;
};

class Wall : public Entity
{
public:
    char GetSymbol() const override { return '#'; }
    int GetColorCode() const override { return 7; }

    virtual ~Wall() = default;
};

class Passage : public Entity
{
public:
    char GetSymbol() const override { return ' '; }
    int GetColorCode() const override { return 0; }
};

class Player : public Entity
{
    short _health;
    short _speed;
public:
    char GetSymbol() const override { return '@'; }
    int GetColorCode() const override { return 1; }
};

class Enemy : public Entity
{
    short _speed;
public:
    char GetSymbol() const override { return '!'; }
    int GetColorCode() const override { return 4; }
};

class Exit : public Entity
{
public:
    char GetSymbol() const override { return '*'; }
    int GetColorCode() const override { return 6; }
};

struct Coord
{
    int y, x;
};

struct Cell
{
    UniquePtr<Entity> content;
};

class Maze
{
	const int height = 37;
	const int width = 51;

	Cell maze[37][51];

public:
	void InitMaze()
	{
		int counter = 0;
		for (short i = 0; i < height; i++)
		{
			for (short j = 0; j < width; j++)
			{
				maze[i][j].content = UniquePtr<Entity>(new Wall());
			}
		}
	}

	void GenerateMaze(const Coord& start = { 1, 1 })
	{
		Stack<Coord> stack;
		stack.Push(start);
		maze[start.y][start.x].content = UniquePtr<Entity>(new Player());

		std::random_device random;
		std::mt19937 engine(random());

		Vector<Coord> offsets = { {2, 0}, {0, 2}, {-2, 0}, {0, -2} };

		while (!stack.Empty())
		{
			Coord current = stack.Top();
			
			Shuffle(offsets, engine);

			bool moved = false;
			for (int i = 0; i < offsets.Size(); ++i)
			{
				Coord newCoord = {current.y + offsets[i].y, current.x + offsets[i].x};

				if (newCoord.y > 0 && newCoord.y < height - 1 &&
					newCoord.x > 0 && newCoord.x < width - 1 &&
					dynamic_cast<Wall*>(maze[newCoord.y][newCoord.x].content.get()))
				{
					maze[newCoord.y][newCoord.x].content = UniquePtr<Entity>(new Passage());
					maze[(current.y + newCoord.y) / 2][(current.x + newCoord.x) / 2].content = UniquePtr<Entity>(new Passage());

					stack.Push(newCoord);
					moved = true;
					break;
				}
			}

			if (!moved)
				stack.Pop(); 	
		}
	}

	void SetColor(int colorCode) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, colorCode);
	}

	void PrintMaze()
	{
		char wall = '#';
		char passage = ' ';

		for (size_t i = 0; i < height; i++)
		{
			for (size_t j = 0; j < width; j++)
			{
				if (dynamic_cast<Wall*>(maze[i][j].content.get()))
				{
					SetColor(maze[i][j].content.get()->GetColorCode());

					std::cout << wall << wall << wall;
				}
				else
				{
					SetColor(0);
					std::cout << passage;
					SetColor(maze[i][j].content.get()->GetColorCode());
					std::cout << maze[i][j].content.get()->GetSymbol();
					SetColor(0);
					std::cout << passage;
				}
			}

			std::cout << '\n';

			SetColor(white);
		}
	}
};


