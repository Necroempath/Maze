#include "Game.h"

UniquePtr<Random> Game::random = nullptr;
UniquePtr<Maze> Game::maze = nullptr;

void Game::LaunchGame()
{
	ConsoleUI::MainMenu();
	system("cls");
	GameData data;

	random = UniquePtr<Random>(new Random);
	maze = UniquePtr<Maze>(new Maze(*random));

	maze->InitMaze();
	Vector<Moveable*> moveableObjects = maze->GenerateMaze(data.player.get());
	data.moveableObjects = &moveableObjects;
	maze->PrintMaze();

	GameLoop(data);
}

void Game::GameLoop(GameData& data)
{
	auto lastTick = std::chrono::steady_clock::now();
	Vector<std::pair<Coord, Item*>> hiddenItems;
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
					SharedPtr<Entity> passage = SharedPtr<Entity>(new Passage);

					if (auto item = dynamic_cast<Item*>(target); item)
					{
						if (dynamic_cast<Player*>(moveable) && item->IsActive())
							item->OnTouch(data);
						else if (dynamic_cast<Enemy*>(moveable) && item->IsActive())
							hiddenItems.PushBack(std::make_pair(newPos, item));
					}
						
					ConsoleUI::DrawEntityAt(oldPos, passage.get());			
					ConsoleUI::DrawEntityAt(newPos, moveable);

					maze->SetEntityTo(newPos, data.player.get());
					maze->SetEntityTo(oldPos, passage.get());

					if (hiddenItems.Size() > 0)
					{
						for (size_t i = 0; i < hiddenItems.Size(); i++)
						{
							if (oldPos == hiddenItems[i].first)
							{
								maze->SetEntityTo(oldPos, hiddenItems[i].second);
								ConsoleUI::DrawEntityAt(oldPos, hiddenItems[i].second);
							}
						}
					}
				}
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		data.globalTime += deltaTime;

		ConsoleUI::DisplayInfo(data);
	}
}

void Game::MainMenuHandler(short option)
{
	switch (option)
	{
	default:
		return;
		break;
	}
}
