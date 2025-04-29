#include "Game.h"
#include <chrono>
UniquePtr<Random> Game::random = nullptr;
UniquePtr<Maze> Game::maze = nullptr;

void Game::LaunchGame()
{
    random = UniquePtr<Random>(new Random);
    maze = UniquePtr<Maze>(new Maze(*random));

    maze->InitMaze();
    Vector<Moveable*> moveableObjects = maze->GenerateMaze(new Player(Coord(2,2), 10, 100));

    maze->PrintMaze();
    GameLoop(moveableObjects);

}

void Game::GameLoop(Vector<Moveable*>& moveableObjects)
{
    bool gameOver = false;
    bool gameStop = false;
    auto lastTick = std::chrono::steady_clock::now();
   // HashTable<Coord, Item*> hiddenItems;
    ConsoleUI::HideCursor();
    while (!gameOver)
    {
        auto now = std::chrono::steady_clock::now();
        float deltaTime = std::chrono::duration<float>(now - lastTick).count();
        lastTick = now;

        for (auto& moveable : moveableObjects)
        {
            if (moveable->CanMove(deltaTime))
            {
                Coord oldPos = moveable->GetPos();
                Coord newPos = moveable->UpdateDirection();
                Entity* target = maze->IdentifyObject(newPos);

                if (moveable->Move(newPos, target))
                {
                    if (auto item = dynamic_cast<Item*>(target); item && dynamic_cast<Player*>(moveable))
                    {
                        item->OnTouch();
                    }

                    Passage p;

                    ConsoleUI::DrawEntityAt(oldPos, &p);

                    ConsoleUI::DrawEntityAt(newPos, moveable);
                }
            }            
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}
