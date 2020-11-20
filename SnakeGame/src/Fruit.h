#pragma once
class Fruit
{
private:
	//Defining fruit
	sf::CircleShape fruit;
	int posX;
	int posY;

	//Private functions
	void initVariables();
	void initShape();
public:
	//Con/des
	Fruit();
	~Fruit();

	//Accessors
	const sf::FloatRect getBounds() const;
	const float getRadius() const;
	void setPosition(const float posX, const float posY);

	//Functions
	void update();
	void render(sf::RenderTarget& target);
};

