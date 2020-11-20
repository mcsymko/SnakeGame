#pragma once

#include "Snake.h"
#include "Fruit.h"

class Game
{
private:
	//Window
	sf::RenderWindow window;
	sf::Event ev;

	bool running;

	//Snake
	std::vector <Snake> snake;

	//Fruit
	Fruit fruit;

	//World background
	sf::Texture texure;
	sf::Sprite worldBackground;

	//Private functions
	void initVariables();
	void initWindow();
	void initWorldBackground();
	void initFruit();
public:
	Game();
	~Game();

	//Accessors
	const sf::RenderWindow& getWindow() const;

	//Functions
	bool gameRunning();

	void updateInput();
	void updateCollision();
	void updateEating();
	void updateTail();
	void update();

	void renderWorldBackground();
	void renderSnake();
	void render();
};

