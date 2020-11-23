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
	Snake snakeHead;
	std::vector <Snake> snakeBody;

	//Timer
	sf::Clock clock;
	float timer;
	float delay;

	//Fruit
	Fruit fruit;
	unsigned points;

	//World background
	sf::Texture texure;
	sf::Sprite worldBackground;

	//GUI text
	sf::Font font;
	sf::Text guiText;

	//Private functions
	void initVariables();
	void initWindow();
	void initWorldBackground();
	void initFruit();
	void initGUI();
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
	void updateGUI();
	void update();

	void renderWorldBackground();
	void renderSnake();
	void renderGUI(sf::RenderTarget& target);
	void render();
};

