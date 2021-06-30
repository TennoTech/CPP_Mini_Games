#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

// Game Engine Wrapper Class

class Game
{
private:
	// Functions
	void InitWindow();
	void InitEnemy();

	// Variables
	
	// Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	sf::Vector2i mousePositionWindow;
	sf::Vector2f mousePositionView;

	int points;
	int health;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	size_t maxEnemies;
	bool mouseHeld;
	bool hasGameEnded;

	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;

public:
	Game();
	virtual ~Game();

	const bool IsWindowOpen() const;
	const bool GetHasGameEnded() const;

	// Functions
	void SpawnEnemy();
	void UpdateEnemies();
	void RenderEnemies();
	void UpdatePollEvents();
	void UpdateMousePositions();
	void Update();
	void Render();

};

