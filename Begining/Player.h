#pragma once
#include <SFML/Graphics.hpp>
# define PI 3.14159265358979323846


using namespace sf;

const int TILE_SIZE = 32;

class Player
{
public:
	Player(RenderWindow& window);
	~Player();
	
	void PlayerControl(Event &event);
	int Ray(Vector2f begin, float angle);
	void Update(float time);
private:
	Vector2f Position, Size;
	RenderWindow& win;
	float Speed, Angle, LeftAngle, MiddleAngle, RightAngle, Fov, RotationSpeed;
	void Move(float time);
	CircleShape Body;
	float RayLength;

	float GradToRad(float Rad);
	void DrawPlayer();

	bool a, d;
	int RayCount;
	float UpTime;
};

Player::Player(RenderWindow& window) : win(window)
{
	Size = { 16, 16 };
	Position = { 400, 400 };
	Speed = 0.4f;
	RotationSpeed = 60.0f; //меньше - быстрее, больше - медленнее
	Body.setFillColor(Color::Color(255, 105, 0));
	Body.setPosition(Position);
	Body.setRadius(16);
	Body.setOrigin(Vector2f(Body.getRadius(), Body.getRadius()));
	RayLength = 128;
	Fov = PI / 2;// угол обзора
	RayCount = 10;

	Angle = PI / 4;
	//MiddleAngle = Angle;
	a = d = false;

	UpTime = 0;

}

Player::~Player()
{
}

inline void Player::DrawPlayer()
{
	win.draw(Body);
	for(float DeltAngel = LeftAngle; DeltAngel < RightAngle; DeltAngel += Fov/RayCount)
		Ray(Body.getPosition(), DeltAngel);
}

inline void Player::PlayerControl(Event& event)
{
	if (event.type == Event::KeyPressed && event.key.code == Keyboard::Left)		
		a = true;
	if (event.type ==Event::KeyPressed && event.key.code == Keyboard::Right)
		d = true;
	if (event.type == Event::KeyReleased && a)
		a = false;
	if (event.type == Event::KeyReleased && d)
		d = false;

	/*if(Keyboard::isKeyPressed(Keyboard::A))
		Angle -= PI / 60;
	if(Keyboard::isKeyPressed(Keyboard::D))
		Angle += PI / 60;*/
	
}



inline void Player::Move(float time)
{
	if (Keyboard::isKeyPressed(Keyboard::W))
		Body.move(0, -Speed*time);
	if (Keyboard::isKeyPressed(Keyboard::S))
		Body.move(0, Speed * time);
	if (Keyboard::isKeyPressed(Keyboard::A))
		Body.move(-Speed * time, 0);
	if (Keyboard::isKeyPressed(Keyboard::D))
		Body.move(Speed * time, 0);
}

inline float Player::GradToRad(float Rad)
{
	return Rad * PI / 180;
}

int Player::Ray(Vector2f begin, float angle)
{
	VertexArray ray(Lines, 2);
	ray[0].position = begin;
	ray[1].position = Vector2f(begin.x + RayLength * cos(angle), begin.y + RayLength * sin(angle));
	win.draw(ray);
	return 0;
}

inline void Player::Update(float time)
{
	UpTime += time;
	if (UpTime > 30)
	{
		UpTime = 0;
		if (a)
			Angle -= PI / RotationSpeed;
		if (d)
			Angle += PI / RotationSpeed;

	LeftAngle = Angle - Fov / 2;
	RightAngle = Angle + Fov / 2;
	}
	Move(time);
	DrawPlayer();
}
