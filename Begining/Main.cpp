#include <SFML/Graphics.hpp>
#include <iostream>
#include "Settings.h"


using namespace sf;

int main()
{
	

	Settings GameSettings = Settings();
	//CreateSettingsFile();
	
	RenderWindow window(sf::VideoMode(GameSettings., GameSettings.WindowWidth), "Begining by Paxamet");
	
	/*Image HeroImage;
	HeroImage.loadFromFile("images/hero.png");
	HeroImage.createMaskFromColor(Color(0,255,0));

	Texture HeroTexture;
	HeroTexture.loadFromImage(HeroImage);

	Sprite HeroSprite;
	HeroSprite.setTexture(HeroTexture);
	HeroSprite.setTextureRect(IntRect(0, 0, 64, 64));
	HeroSprite.setPosition(WinSettings.WindowWidth / 2, WinSettings.WindowHeigh / 2);*/

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) {
				window.close();
				//std::cout << "---shutdown program" << endl;
			}

			/*if (Keyboard::isKeyPressed(Keyboard::W)) 
			{
				HeroSprite.move(0, -0.5);
				HeroSprite.setRotation(0);
			}
			if (Keyboard::isKeyPressed(Keyboard::S))
			{
				HeroSprite.move(0, 0.5);
				HeroSprite.setRotation(180);
			}
			if (Keyboard::isKeyPressed(Keyboard::A))
			{
				HeroSprite.move(-0.5, 0);
				HeroSprite.setRotation(270);
			}
			if (Keyboard::isKeyPressed(Keyboard::D))
			{
				HeroSprite.move(0.5, 0);
				HeroSprite.setRotation(90);
			}

			if (Mouse::isButtonPressed(Mouse::Left))
			{
				HeroSprite.setPosition(Vector2f(Mouse::getPosition()));
			}*/

			//std::cout << "---Hero pos (x: " << HeroSprite.getPosition().x << ", y: " << HeroSprite.getPosition().y << ")\n";
		}
		window.clear();
		//window.draw(HeroSprite);
		window.display();
	
	}
	//system("pause");
	return 0;
}