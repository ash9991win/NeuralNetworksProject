#include"pch.h"
#include"InputManager.h"
#include"World.h"
#include"CollisionComponent.h"
#include"ResourceManager.h"
#include"BackgroundActor.h"
#include"AnimationComponent.h"
#include"Player.h"
#include "Boss.h"
#include"StateMachine.h"
#include<iostream>
#include"NNVisualizer.h"
#include"Primitive.h"
#include"CollisionManager.h"
#include"Timer.h"
#include"StaticActor.h"
#include"ThreadManager.h"
#include"TileMap.h"
#include"GeneticPathFinder.h"
#include"GAVisualizer.h"
#include"PatternChooser.h"
sf::RenderWindow window2(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "ANN");
sf::RenderWindow GAWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Genetic Algorithm");
//The main game loop that updates the world and renders the NN visualizer
GAVisualizer<shared_ptr<Action>> GAVisual;


int main()
{
	std::srand(std::time(0));
	
	//ThreadManager::FinishThreads();
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Test Input");
	World::CreateWorld(&window);
	sf::Clock GameClock;
	auto BgActor = World::SpawnActor<BackgroundActor>("Background");
	auto animC = BgActor->AddComponent<AnimationComponent>();
	animC->SetFrames({"background0","background1","background2"});
	animC->SetTimeBetweenFrames(0.5f);
	animC->SetFrameDimensions(WINDOW_WIDTH, WINDOW_HEIGHT);
	auto PlayerActor = World::SpawnActor<Player>("Player");
	auto Floor = World::SpawnActor<StaticActor>("floor",WINDOW_WIDTH,20.0f);
	auto BossActor = World::SpawnActor<Boss>("Boss");
	Floor->mPosition.x = FLOOR_X;
	Floor->mPosition.y = FLOOR_Y;
	World::CURRENT_GAME_STATE = GAME_STATE::GAME_STARTED;
	World::BeginWorld();
	GameClock.restart();
	sf::Time deltaTime;
	NNVisualizer visualizer;
	visualizer.AssignNetwork(*(BossActor->GetBrain()));
	visualizer.AssignWindow(window2);
	Primitive::SetWindow(&window2);
	World::CURRENT_GAME_STATE = GAME_STATE::GAME_RUNNING;
	//auto nnThread(std::async([&] {
	//	while (window2.isOpen())
	//	{
	//		window2.clear(sf::Color::White);
	//		visualizer.Render();
	//		window2.display();
	//	}
	//}));

	TileMap::Initialize();
	GeneticPathFinder pathFinder(sf::Vector2f(0, 0), sf::Vector2f(75, 0));
	InputManager::MousePressedEvents.Bind([BossActor](sf::Vector2i position) {
		sf::Vector2f pos;
		pos.x = position.x;
		pos.y = position.y;
		BossActor->mPatternChooser->FindNextBestPattern(BossActor->Patterns);
	});
	GAVisual.AssignWindow(GAWindow);
	GAVisual.AssignGA(BossActor->mPatternChooser->PatternSearch);
	GAVisual.PopulateLegends();
	//auto GAThread(std::async([]
	//{
	//	
	//}));
//	pathFinder.FindPath();

	while (window.isOpen())
	{
		
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::EventType::KeyReleased)
			{
				InputManager::HandleKeyRelease(event.key.code, deltaTime.asSeconds());
			}
			if (event.type == sf::Event::EventType::KeyPressed)
			{
				InputManager::HandleKeyPress(event.key.code,deltaTime.asSeconds());
			}
			if (event.type == sf::Event::EventType::MouseButtonPressed)
			{
				InputManager::HandleMouseEvents(event.type,window);
			}
			
		}
		
		window.clear(sf::Color::Black);
		World::UpdateWorld(deltaTime.asSeconds());
		CollisionManager::Update(deltaTime.asSeconds());
		window.display();
	
		deltaTime = GameClock.restart();
		if (GAWindow.isOpen())
		{
			GAWindow.clear(sf::Color::White);
			GAVisual.Render();
			GAWindow.display();
		}
	}
	
	//nnThread.get();
	ThreadManager::FinishThreads();
	for (auto& timerThread : Timer::mTimerThreads)
	{
		
		timerThread.get();
	}
}