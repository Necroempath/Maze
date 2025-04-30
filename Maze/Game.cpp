#include "Game.h"

UniquePtr<Random> Game::random = nullptr;
UniquePtr<Maze> Game::maze = nullptr;

void Game::LaunchGame()
{
    GameData data;
  
    random = UniquePtr<Random>(new Random);
    maze = UniquePtr<Maze>(new Maze(*random));
    UniquePtr<Player> player = UniquePtr<Player>(new Player(Coord(2, 2), 10, 100));
    data.player = player.get();

    maze->InitMaze();
    UniquePtr<Vector<Moveable*>> moveableObjects = maze->GenerateMaze(player.get());
    data.moveableObjects = moveableObjects.get();
    maze->PrintMaze();
    
    GameLoop(data);

}

void Game::GameLoop(GameData& data)
{
    auto lastTick = std::chrono::steady_clock::now();
   // HashTable<Coord, Item*> hiddenItems;
    ConsoleUI::HideCursor();
    while (!data.gameOver)
    {
        auto now = std::chrono::steady_clock::now();
        float deltaTime = std::chrono::duration<float>(now - lastTick).count();
        lastTick = now;

        for (auto& moveable : *data.moveableObjects)
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
                        item->OnTouch(data);
                    }

                    Passage p;

                    ConsoleUI::DrawEntityAt(oldPos, &p);

                    ConsoleUI::DrawEntityAt(newPos, moveable);
                }
            }            
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        data.globalTime += deltaTime;

        ConsoleUI::DisplayInfo(data);
    }
}
