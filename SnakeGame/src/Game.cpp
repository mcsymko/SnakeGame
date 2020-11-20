#include "stdafx.h"
#include "Game.h"

void Game::initVariables()
{
	this->running = true;
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
		static_cast<float>(rand() % 50),
		static_cast<float>(rand() % 37));
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
	//Movement
	if (this->snake[0].getMovementState() == LEFT)
	{
		this->snake[0].move(-3.f, 0.f);
	}
	else if (this->snake[0].getMovementState() == RIGHT)
	{
		this->snake[0].move(3.f, 0.f);
	}
	else if (this->snake[0].getMovementState() == UP)
	{
		this->snake[0].move(0.f, -3.f);
	}
	else if (this->snake[0].getMovementState() == DOWN)
	{
		this->snake[0].move(0.f, 3.f);
	}
}

void Game::updateCollision()
{
	//If snake touches the wall game is over
	if (this->snake[0].getBounds().left < 0.f)
	{
		this->snake[0].setPosition(0.f, this->snake[0].getBounds().top);
		this->running = false;
	}
	else if (this->snake[0].getBounds().left + this->snake[0].getBounds().width > this->window.getSize().x)
	{
		this->snake[0].setPosition(this->window.getSize().x - this->snake[0].getBounds().width, this->snake[0].getBounds().top);
		this->running = false;
	}
	if (this->snake[0].getBounds().top < 0.f)
	{
		this->snake[0].setPosition(this->snake[0].getBounds().left, 0.f);
		this->running = false;
	}
	else if (this->snake[0].getBounds().top + this->snake[0].getBounds().height > this->window.getSize().y)
	{
		this->snake[0].setPosition(this->snake[0].getBounds().left, this->window.getSize().y - this->snake[0].getBounds().height);
		this->running = false;
	}
}

void Game::updateEating()
{
	//Setting correct variables for random positioning and inside the map
	int correctX = this->window.getSize().x - static_cast<int>(this->fruit.getRadius() * 4 + 1);
	int correctY = this->window.getSize().y - static_cast<int>(this->fruit.getRadius() * 4 + 1);

	//When snake eats fruit snake becomes bigger and fruit respawns
	if (this->snake[0].getBounds().intersects(this->fruit.getBounds()))
	{
		this->snake.push_back(Snake(this->snake[0].getPosition().x, this->snake[0].getPosition().y));

		this->fruit.setPosition(
			static_cast<float>(this->fruit.getRadius() * 2 + rand() % correctX),
			static_cast<float>(this->fruit.getRadius() * 2 + rand() % correctY));
	}
}

void Game::updateTail()
{
	for (int i = this->snake.size(); i > 0; i--)
	{
		this->snake[i].setPosition(this->snake[i - 1].getPosition().x, this->snake[i - 1].getPosition().y);
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
		this->updateTail();
		this->snake[0].updateDirection();
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
	for (auto& i : snake)
	{
		i.render(this->window);
	}
}

void Game::render()
{
	this->window.clear();

	this->renderWorldBackground();

	this->renderSnake();
	this->fruit.render(this->window);
	//Works!
	this->window.display();
}
