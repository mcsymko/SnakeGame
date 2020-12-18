#pragma once
enum MOVEMENT_STATES { IDLE, RIGHT, LEFT, UP, DOWN };

class Snake
{
public:
	Snake();
	~Snake();

	//Accessors
	const sf::FloatRect getBounds() const;

	//Modifiers
	void setPosition(sf::Vector2f position);
	const sf::Vector2f& getPosition() const;
	const sf::Vector2f& getSize() const;

	const int getMovementState() const;

	//Functions
	void move(const float dirX, const float dirY);
	void updateDirection();
	void update();
	void render(sf::RenderTarget& target);

private:
	sf::RectangleShape snake;

	//Movement
	short MovementState;
	float movementSpeed;

	void initShape();
	void initVariables();
};

