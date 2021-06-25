#include <iostream>
#include "Game.h"

void Game::InitWindow()
{
	videoMode.height = 600;
	videoMode.width = 800;

	window = new sf::RenderWindow(videoMode, "First Game", sf::Style::Titlebar | sf::Style::Close);
	window->setFramerateLimit(60);
}

void Game::InitEnemy()
{
	enemy.setPosition(10.0f, 10.0f);
	enemy.setSize(sf::Vector2f(100.0f, 100.0f));
	enemy.setFillColor(sf::Color::Cyan);
	enemies.push_back(enemy);
}

Game::Game()
	:
	window{ nullptr },
	points{ 0 },
	enemySpawnTimerMax{ 100.0f },
	enemySpawnTimer{ enemySpawnTimerMax },
	maxEnemies{ 5 }

{
	InitWindow();
	InitEnemy();
}

Game::~Game()
{
	delete window;
}

const bool Game::IsWindowOpen() const
{
	return window->isOpen();
}

void Game::SpawnEnemy()
{
	// Setting random position
	enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(window->getSize().x - enemy.getSize().x)),
		0.0f
	);


	enemy.setFillColor(sf::Color::Green);

	// Spawning enemy
	enemies.push_back(enemy);
}

void Game::UpdateEnemies()
{
	// Timer for spawning enemies
	if (enemies.size() < maxEnemies)
	{
		if (enemySpawnTimer >= enemySpawnTimerMax)
		{
			SpawnEnemy();
			enemySpawnTimer = 0.0f;
		}
		else
			enemySpawnTimer += 1.0f;
	}

	// Moving enemies
	for (auto& e : enemies)
	{
		e.move(0.0f, 1.0f);
	}
}

void Game::RenderEnemies()
{
	for (auto& e : enemies)
	{
		window->draw(e);
	}
}

void Game::UpdatePollEvents()
{
	while (window->pollEvent(ev))
	{
		switch (ev.type)
		{
		case sf::Event::Closed:
			window->close();
			break;
		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::Escape)
				window->close();
			break;
		}
	}
}

void Game::UpdateMousePositions()
{
	mousePosition = sf::Mouse::getPosition(*window);
}

void Game::Update()
{
	UpdatePollEvents();
	UpdateMousePositions();
	UpdateEnemies();
}


void Game::Render()
{
	window->clear();

	// Draw Game
	RenderEnemies();

	window->display();
}
