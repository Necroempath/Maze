#include "Game.h"
UniquePtr<Random> Game::random = nullptr;
UniquePtr<Maze> Game::maze = nullptr;

void Game::LaunchGame()
{
    random = UniquePtr<Random>(new Random);
    maze = UniquePtr<Maze>(new Maze(*random));
    maze->InitMaze();
    Vector<Moveable*> moveableObjects = maze->GenerateMaze(new Player());

    GameLoop(moveableObjects);
    //maze->PrintMaze();
}

void Game::GameLoop(Vector<Moveable*>& moveableObjects)
{
    bool gameOver = false;
    bool gameStop = false;

    HashTable<Coord, Item*> hiddenItems;

    while (gameOver)
    {
        for (auto& moveable : moveableObjects)
        {
            Coord newCoord = moveable->UpdateDirection();
            Item* item = moveable->Move(newCoord, maze->InentifyObject(newCoord));

            if (item)
            {
                hiddenItems.Add(newCoord, item);
            }
        }
    }
}
