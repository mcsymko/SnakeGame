#include "stdafx.h"
#include "Fruit.h"

void Fruit::initVariables()
{

}

void Fruit::initShape()
{
	this->fruit.setFillColor(sf::Color::Red);
	this->fruit.setRadius(15.f);
}

Fruit::Fruit()
{
	this->initVariables();
	this->initShape();
}

Fruit::~Fruit()
{

}

const sf::FloatRect Fruit::getBounds() const
{
	return this->fruit.getGlobalBounds();
}

const float Fruit::getRadius() const
{
	return this->fruit.getRadius();
}

void Fruit::setPosition(const float posX, const float posY)
{
	this->fruit.setPosition(posX, posY);
}

void Fruit::update()
{

}

void Fruit::render(sf::RenderTarget& target)
{
	target.draw(this->fruit);
}
