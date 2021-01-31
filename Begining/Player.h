#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

const int TILE_SIZE = 32;

class Player
{
public:
	Player(RenderWindow& window);
	~Player();
	void DrawPlayer();
	void PlayerControl(Event &event);
private:
	Vector2f Position, Size, Destination;
	RectangleShape HitBox;
	RenderWindow& win;
	float Speed;
	void Move();
	
};

Player::Player(RenderWindow& window) : win(window)
{
	Destination = Position = { 0, 0 };
	Size = { 16, 16 };
	Speed = 3.0f;
	HitBox.setOrigin(Size/2.0f);
	HitBox.setFillColor(Color::Blue);
	HitBox.setPosition(Position);
	HitBox.setSize(Size);
	HitBox.setOutlineColor(Color::Yellow);
	HitBox.setOutlineThickness(1);
}

Player::~Player()
{
}

inline void Player::DrawPlayer()
{
	Move();
	win.draw(HitBox);
}

inline void Player::PlayerControl(Event& event)
{
	if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
	{
		Destination =  Vector2f(Mouse::getPosition().x - win.getPosition().x, Mouse::getPosition().y - win.getPosition().y);
	}
}

inline void Player::Move()
{
	if (Position != Destination)
	{
		if (Position.x > Destination.x)
			Position.x -= Speed;
		if (Position.x < Destination.x)
			Position.x += Speed;
		if (Position.y > Destination.y)
			Position.y -= Speed;
		if (Position.y < Destination.y)
			Position.y += Speed;
		HitBox.setPosition(Position);
		//std::cout << "Destination:\t" << Destination.x << ":" << Destination.y << "\tPosition:\t" << Position.x << ":" << Position.y << endl;
	}
}
