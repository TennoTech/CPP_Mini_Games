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
	health{ 5 },
	enemySpawnTimerMax{ 10.0f },
	enemySpawnTimer{ enemySpawnTimerMax },
	maxEnemies{ 5 },
	mouseHeld{ false },
	hasGameEnded{ false }
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

const bool Game::GetHasGameEnded() const
{
	return hasGameEnded;
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

	// Moving enemies and updating enemies
	for (size_t i = 0; i < enemies.size(); i++)
	{
		// It only deletes one at a time
		bool isDeleted = false;
		enemies[i].move(0.0f, 1.0f);

		if (enemies[i].getPosition().y >= window->getSize().y)
		{
			enemies.erase(enemies.begin() + i);
			health -= 1;
		}

		// Check if clicked enemy
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			// Checking every iteration to see if we are holding mouse
			if (!mouseHeld)
			{
				mouseHeld = true;
				if (enemies[i].getGlobalBounds().contains(mousePositionView))
				{
					isDeleted = true;
					points++;
				}

				// Starts at the beginning of the array then goes up to specified index
				if (isDeleted)
					enemies.erase(enemies.begin() + i);
			}
		}
		else
		{
			mouseHeld = false;
		}
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
	mousePositionWindow = sf::Mouse::getPosition(*window);

	// Converting the window coords to a float
	mousePositionView = window->mapPixelToCoords(mousePositionWindow);
}

void Game::Update()
{
	UpdatePollEvents();

	if (!hasGameEnded)
	{
		UpdateMousePositions();
		UpdateEnemies();
	}

	if (health <= 0)
		hasGameEnded = true;
}


void Game::Render()
{
	window->clear();

	// Draw Game
	RenderEnemies();

	window->display();
}
