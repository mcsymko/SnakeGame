#include "stdafx.h"
#include "Game.h"

void Game::initVariables()
{
	this->running = true;
	this->timer = 0;
	this->delay = 0.1f;
}

void Game::initWindow()
{
	this->window.create(sf::VideoMode(789, 575), "Snake Game Beta", sf::Style::Close | sf::Style::Titlebar);
	this->window.setFramerateLimit(60);
}

void Game::initWorldBackground()
{
	this->texure.loadFromFile("Textures\\background.jpg");

	this->worldBackground.setTexture(this->texure);
}

void Game::initFruit()
{
	//Setting start position of the fruit
	this->fruit.setPosition(
		static_cast<float>(this->fruit.getRadius() * 2 + rand() % this->window.getSize().x - static_cast<int>(this->fruit.getRadius() * 4 + 1)),
		static_cast<float>(this->fruit.getRadius() * 2 + rand() % this->window.getSize().y - static_cast<int>(this->fruit.getRadius() * 4 + 1)));
}

Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initWorldBackground();
	this->initFruit();
}

Game::~Game()
{

}

const sf::RenderWindow& Game::getWindow() const
{
	return this->window;
}

bool Game::gameRunning()
{
	return this->running;
}

void Game::updateInput()
{
	float time = clock.getElapsedTime().asSeconds();
	this->clock.restart();
	this->timer += time;
	if (this->timer > this->delay)
	{
		this->timer = 0;
		this->updateTail();
	}

	//Movement
	if (this->snakeHead.getMovementState() == LEFT)
	{
		this->snakeHead.move(-1.f, 0.f);
	}
	else if (this->snakeHead.getMovementState() == RIGHT)
	{
		this->snakeHead.move(1.f, 0.f);
	}
	else if (this->snakeHead.getMovementState() == UP)
	{
		this->snakeHead.move(0.f, -1.f);
	}
	else if (this->snakeHead.getMovementState() == DOWN)
	{
		this->snakeHead.move(0.f, 1.f);
	}
}

void Game::updateCollision()
{
	//If snake touches the wall game is over
	if (this->snakeHead.getBounds().left < 0.f)
	{
		this->running = false;
	}
	else if (this->snakeHead.getBounds().left + this->snakeHead.getBounds().width > this->window.getSize().x)
	{
		this->running = false;
	}
	if (this->snakeHead.getBounds().top < 0.f)
	{
		this->running = false;
	}
	else if (this->snakeHead.getBounds().top + this->snakeHead.getBounds().height > this->window.getSize().y)
	{
		this->running = false;
	}
}

void Game::updateEating()
{
	//Setting correct variables for random positioning and inside the map
	int correctX = this->window.getSize().x - static_cast<int>(this->fruit.getRadius() * 4 + 1);
	int correctY = this->window.getSize().y - static_cast<int>(this->fruit.getRadius() * 4 + 1);

	//When snake eats fruit snake becomes bigger and fruit respawns
	if (this->snakeHead.getBounds().intersects(this->fruit.getBounds()))
	{
		this->snakeBody.push_back(Snake());

		this->fruit.setPosition(
			static_cast<float>(this->fruit.getRadius() * 2 + rand() % correctX),
			static_cast<float>(this->fruit.getRadius() * 2 + rand() % correctY));
	}
}

void Game::updateTail()
{
	//Had to use this, because otherwise it crashes becouse of access to vector which is out of range
	if (this->snakeBody.size() > 0)
	{
		for (int i = this->snakeBody.size() - 1; i > 0; --i)
		{
			this->snakeBody[i].setPosition(this->snakeBody[i - 1].getPosition());
		}

		this->snakeBody[0].setPosition(this->snakeHead.getPosition());
	}
}

void Game::update()
{
	while (this->window.pollEvent(this->ev))
	{
		if (this->ev.type == sf::Event::Closed)
			this->window.close();
		else if (this->ev.type == sf::Event::KeyPressed && this->ev.key.code == sf::Keyboard::Escape)
			this->window.close();
	}

	if (running)
	{	
		this->snakeHead.update();
		this->updateInput();
		this->updateCollision();
		this->updateEating();
	}
}

void Game::renderWorldBackground()
{
	this->window.draw(this->worldBackground);
}

void Game::renderSnake()
{
	sf::Vector2f buf(0.f, 0.f);
	this->snakeHead.render(this->window);

	//Render and add tail if snakeHead ate fruit
	for (int i = 0; i < this->snakeBody.size(); ++i)
	{
		//Using if for not to render start position of the snakeBody
		if (this->snakeBody[i].getPosition() != buf)
		{
			this->snakeBody[i].render(this->window);
		}
	}
}

void Game::render()
{
	this->window.clear();

	this->renderWorldBackground();
	this->renderSnake();
	this->fruit.render(this->window);

	this->window.display();
}
