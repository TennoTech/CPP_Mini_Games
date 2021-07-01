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

	font.loadFromFile("Fonts/Frizon.ttf");
	uiText.setFont(font);
	uiText.setCharacterSize(25);
	uiText.setFillColor(sf::Color::Magenta);
	uiText.setString("Something");
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

void Game::RenderText(sf::RenderTarget& target)
{
	target.draw(uiText);
}

void Game::UpdateText()
{
	std::stringstream ss;
	ss << points << " " << health;

	uiText.setString(ss.str());
}

void Game::SpawnEnemy()
{
	// Setting random position
	enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(window->getSize().x - enemy.getSize().x)),
		0.0f
	);

	int type = rand() % 5;

	switch (type)
	{
	case 0:
		enemy.setFillColor(sf::Color::Green);
		enemy.setSize(sf::Vector2f(25.0f, 25.0f));
		break;
	case 1:
		enemy.setFillColor(sf::Color::Blue);
		enemy.setSize(sf::Vector2f(50.0f, 50.0f));
		break;
	case 2:
		enemy.setFillColor(sf::Color::Red);
		enemy.setSize(sf::Vector2f(75.0f, 75.0f));
		break;
	case 3:
		enemy.setFillColor(sf::Color::Yellow);
		enemy.setSize(sf::Vector2f(100.0f, 100.0f));
		break;
	case 4:
		enemy.setFillColor(sf::Color::White);
		enemy.setSize(sf::Vector2f(125.0f, 125.0f));
		break;
	default:
		enemy.setFillColor(sf::Color::Magenta);
		enemy.setSize(sf::Vector2f(150.0f, 150.0f));
		break;
	}

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
					points++;
					isDeleted = true;
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

void Game::RenderEnemies(sf::RenderTarget& target)
{
	for (auto& e : enemies)
	{
		target.draw(e);
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
		UpdateText();
	}

	if (health <= 0)
		hasGameEnded = true;
}


void Game::Render()
{
	window->clear();

	// Draw Game
	RenderEnemies(*window);

	RenderText(*window);

	window->display();
}
