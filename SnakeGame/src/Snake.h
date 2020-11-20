#pragma once
enum MOVEMENT_STATES { IDLE, RIGHT, LEFT, UP, DOWN };

class Snake
{
private:
	sf::RectangleShape snake;

	//Movement
	short MovementState;
	float movementSpeed;

	void initShape();
	void initVariables();
public:
	Snake(float posX, float posY);
	~Snake();

	//Accessors
	const sf::FloatRect getBounds() const;

	//Modifiers
	void setPosition(const float X, const float Y);
	const sf::Vector2f& getPosition() const;
	const sf::Vector2f& getSize() const;

	const int getMovementState() const;

	//Functions
	void move(const float dirX, const float dirY);
	void updateDirection();
	void update();
	void render(sf::RenderTarget& target);
};

