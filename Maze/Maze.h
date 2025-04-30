#pragma once
#include "Stack.h"
#include "UniquePtr.h"
#include <windows.h>
#include "Random.h"
#include "HashTable.h"
#include "Coord.h"
#include "ConsoleUI.h"
#include "Wall.h"
#include "Passage.h"
#include "Player.h"
#include "Enemy.h"
#include "Life.h"
#include "Key.h"
#include "Exit.h"
#define white 7

struct Cell
{
	UniquePtr<Entity> content;
};

class Maze
{
	const int height = 57;
	const int width = 189;

	Cell maze[57][189];

	Random& random;

public:
	Maze(Random& random) : random(random) {};

	void InitMaze()
	{
		for (short i = 0; i < height; i++)
		{
			for (short j = 0; j < width; j++)
			{
				maze[i][j].content = UniquePtr<Entity>(new Wall());
			}
		}
	}

	void AddToPool(Vector<Entity*>& pool, Entity* object, short count)
	{
		for (short i = 0; i < count; i++)
		{
			pool.PushBack(object);
		}
	}

	Vector<Entity*> GenerateObjectPool()
	{
		Vector<Entity*> objects;

		objects.PushBack(new Exit);
		objects.PushBack(new Key);

		short enemy_count = random(5, 10);
		short life_count = random(3, 5);

		//AddToPool(objects, new Enemy, enemy_count);
		AddToPool(objects, new Life, life_count);

		Shuffle(objects, random.GetEngine());

		return objects;
	}

	Vector<Moveable*> GenerateMaze(Player* player, const Coord& start = Coord(2, 2))
	{
		Stack<Coord> stack;
		short vacant_squares = (height - 1) * (width - 1) / 16;
		Vector<Moveable*> moveableObjects;

		moveableObjects.PushBack(player);
		stack.Push(start);
		SetPassage(start, start);

		maze[start.GetY()][start.GetX()].content = UniquePtr<Entity>(player);
		vacant_squares--;
		short spawn_rate = vacant_squares;

		Vector<Entity*> objects = GenerateObjectPool();

		Vector<Coord> offsets = { Coord(4, 0), Coord(0, 4), Coord(-4, 0), Coord(0, -4) };

		while (!stack.Empty())
		{
			Coord current = stack.Top();

			Shuffle(offsets, random.GetEngine());

			bool moved = false;
			for (int i = 0; i < offsets.Size(); ++i)
			{
				Coord _position = current + offsets[i];

				if (_position.GetY() > 1 && _position.GetY() < height - 1 &&
					_position.GetX() > 1 && _position.GetX() < width - 1 &&
					dynamic_cast<Wall*>(maze[_position.GetY()][_position.GetX()].content.get()))
				{
					SetPassage(current, _position);

					stack.Push(_position);
					moved = true;

					if (objects.Size() > 0)
					{
						short rnd = random(0, spawn_rate);

						if (rnd < objects.Size())
						{
				/*			auto moveable = dynamic_cast<Enemy*>(objects[rnd]);
							if (moveable) {
								moveableObjects.PushBack(moveable);
							}*/
							maze[_position.GetY()][_position.GetX()].content = objects[rnd];
							objects.Remove(rnd);
							spawn_rate = --vacant_squares;
						}
						else
						{
							spawn_rate -= spawn_rate / 20;
						}
						break;
					}
				}
			}

			if (!moved)
			{
				stack.Pop();
			}
		}

		return moveableObjects;
	}

	void SetPassage(const Coord& current, const Coord& next)
	{
		for (short i = -1; i < 2; i++)
		{
			for (short j = -1; j < 2; j++)
			{
				maze[next.GetY() + i][next.GetX() + j].content = UniquePtr<Entity>(new Passage);
			}

			if (current.GetY() - next.GetY()) {
				maze[(current.GetY() + next.GetY()) / 2][i + (current.GetX() + next.GetX()) / 2].content = UniquePtr<Entity>(new Passage);
			}
			else {
				maze[i + (current.GetY() + next.GetY()) / 2][(current.GetX() + next.GetX()) / 2].content = UniquePtr<Entity>(new Passage);
			}
		}
	}

	void SetColor(int colorCode) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, colorCode);
	}

	Entity* IdentifyObject(const Coord coord) const
	{
		return maze[coord.GetY()][coord.GetX()].content.get();
	}

	void PrintMaze()
	{
		for (size_t i = 0; i < height; i++)
		{
			for (size_t j = 0; j < width; j++)
			{
				SetColor(maze[i][j].content.get()->GetColorCode());
				std::cout << maze[i][j].content.get()->GetSymbol();
			}

			std::cout << '\n';
			SetColor(white);
		}
	}
};
