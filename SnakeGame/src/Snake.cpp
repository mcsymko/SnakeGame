#include "stdafx.h"
#include "Snake.h"

void Snake::initShape()
{
	this->snake.setSize(sf::Vector2f(35.f, 35.f));
	this->snake.setFillColor(sf::Color::Green);
}

void Snake::initVariables()
{
	this->MovementState = IDLE;
	this->movementSpeed = 3.f;
}

Snake::Snake(float posX, float posY)
{
	this->initVariables();
	this->initShape();
	this->snake.setPosition(posX, posY);
}

Snake::~Snake()
{

}

const sf::FloatRect Snake::getBounds() const
{
	return this->snake.getGlobalBounds();
}

void Snake::setPosition(const float X, const float Y)
{
	this->snake.setPosition(X, Y);
}

const sf::Vector2f& Snake::getPosition() const
{
	return this->snake.getPosition();
}

const sf::Vector2f& Snake::getSize() const
{
	return this->snake.getSize();
}

const int Snake::getMovementState() const
{
	return this->MovementState;
}

void Snake::move(const float dirX, const float dirY)
{
	this->snake.move(dirX * this->movementSpeed, dirY * this->movementSpeed);
}

void Snake::updateDirection()
{
	if (this->MovementState != RIGHT && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->MovementState = LEFT;
	else if (this->MovementState != LEFT && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->MovementState = RIGHT;
	else if (this->MovementState != DOWN && sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->MovementState = UP;
	else if (this->MovementState != UP && sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->MovementState = DOWN;
}

void Snake::update()
{
	this->updateDirection();
}

void Snake::render(sf::RenderTarget& target)
{
	target.draw(this->snake);
}
