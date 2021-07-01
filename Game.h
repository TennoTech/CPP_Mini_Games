#pragma once

#include <vector>
#include <sstream>

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

	// Resources
	sf::Font font;
	sf::Text uiText;

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
	void RenderText(sf::RenderTarget& target);
	void UpdateText();
	void SpawnEnemy();
	void UpdateEnemies();
	void RenderEnemies(sf::RenderTarget& target);
	void UpdatePollEvents();
	void UpdateMousePositions();
	void Update();
	void Render();

};

