#pragma once
#include "Stack.h"
#include "UniquePtr.h"
#include <windows.h>
#include "Random.h"
#define white 7
#pragma region classes

struct Coord
{
	short y, x;
};

struct Cell
{
	UniquePtr<Entity> content;
};

class Moveable
{
protected:
	Coord pos;

public:
	Coord GetPos() const { return pos; }

	virtual void UpdateDirectory() const = 0;

	void Move();

	virtual ~Moveable() = default;
};

class Entity
{
public:
	virtual char GetSymbol() const = 0;
	virtual int GetColorCode() const = 0;

	virtual ~Entity() = default;
};

class Item : public Entity
{
public:
	virtual char GetSymbol() const = 0;
	virtual int GetColorCode() const = 0;

	virtual ~Item() = default;
};

class Key : public Item
{
public:
	char GetSymbol() const override { return 'k'; }
	int GetColorCode() const override { return 13; }//Enum class replace
};

class Life : public Item
{
public:
	char GetSymbol() const override { return '$'; }
	int GetColorCode() const override { return 3; }//Enum class replace
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
	char GetSymbol() const override { return 'E'; }
	int GetColorCode() const override { return 6; }
};

#pragma endregion

class Maze
{
	const int height = 65; 
	const int width = 213;

	Cell maze[65][217];

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

		AddToPool(objects, new Enemy, enemy_count);
		AddToPool(objects, new Life, life_count);

		Shuffle(objects, random.GetEngine());

		return objects;
	}
	
	void GenerateMaze(const Coord& start = { 2, 2 })
	{
		Stack<Coord> stack;
		short vacant_squares = (height - 1) * (width - 1) / 16;

		stack.Push(start);
		SetPassage(start, start);

		maze[start.y][start.x].content = UniquePtr<Entity>(new Player());
		vacant_squares--;
		short spawn_rate = vacant_squares;

		Vector<Entity*> objects = GenerateObjectPool();
		
		Vector<Coord> offsets = { {4, 0}, {0, 4}, {-4, 0}, {0, -4} };

		while (!stack.Empty())
		{
			Coord current = stack.Top();

			Shuffle(offsets, random.GetEngine());

			bool moved = false;
			for (int i = 0; i < offsets.Size(); ++i)
			{
				Coord newCoord = { current.y + offsets[i].y, current.x + offsets[i].x };

				if (newCoord.y > 1 && newCoord.y < height - 1 &&
  					newCoord.x > 1 && newCoord.x < width - 1 &&
					dynamic_cast<Wall*>(maze[newCoord.y][newCoord.x].content.get()))
				{
					SetPassage(current, newCoord);

					stack.Push(newCoord);
					moved = true;

					if(objects.Size() > 0)
					{
						short rnd = random(0, spawn_rate);

						if (rnd < objects.Size())
						{
							maze[newCoord.y][newCoord.x].content = objects[rnd];
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
	}

	void SetPassage(const Coord& current, const Coord& next)
	{	
		for (short i = -1; i < 2; i++)
		{
			for (short j = -1; j < 2; j++)
			{
				maze[next.y + i][next.x + j].content = UniquePtr<Entity>(new Passage);
			}

			if (current.y - next.y)	{
				maze[(current.y + next.y) / 2][i + (current.x + next.x) / 2].content = UniquePtr<Entity>(new Passage);
			}
			else {
				maze[i + (current.y + next.y) / 2][(current.x + next.x) / 2].content = UniquePtr<Entity>(new Passage);
			}
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
				SetColor(maze[i][j].content.get()->GetColorCode());
				std::cout << maze[i][j].content.get()->GetSymbol();
			}

			std::cout << '\n';

			SetColor(white);
		}
	}
};


