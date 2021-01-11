#include <SFML/Graphics.hpp>
#include <iostream>
#include "Settings.h"


using namespace sf;

int main()
{
	Settings GameSettings = Settings();
	RenderWindow window(sf::VideoMode(std::stof(GameSettings.SettMap[GameSettings.SettMapParam.WINDOWWIDTH]), std::stof(GameSettings.SettMap[GameSettings.SettMapParam.WINDOWHEIGH])), GameSettings.SettMap[GameSettings.SettMapParam.WINDOWTITLE]);
	
	int ISelector = 0;

	int ISelectMenu = 0; //lock menu
	string MenuText[] = {
				"Main string",
				"Settings",
				"Quit" };

	Font font;
	font.loadFromFile("calibri.ttf");
	Text text;
	text.setFont(font);
	text.setCharacterSize(60);
	//text.setOrigin(text.getLocalBounds().width/2, 0);
	//text.getLocalBounds().width;
	//text.setStyle(Text::Bold);

	while (window.isOpen())
	{
		window.clear();
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) {
				window.close();
			}
			switch (ISelector)
			{
			case 0: {
				if (Keyboard::isKeyPressed(Keyboard::Up) && ISelectMenu > 0)
				{
					ISelectMenu--;
				}
				if (Keyboard::isKeyPressed(Keyboard::Down) && ISelectMenu < size(MenuText)-1)
				{
					ISelectMenu++;
				}
				if (Keyboard::isKeyPressed(Keyboard::Enter) || Keyboard::isKeyPressed(Keyboard::Space))
				{
					switch (ISelectMenu)
					{
					case 2: { //QUIT in Main menu
						window.close();
						break;
					}
					default:
						break;
					}
					std::cout << "Selected: " << MenuText[ISelectMenu] << std::endl;
				}
				break;
			}
			default:
				break;
			}
			
		}

		switch (ISelector)
		{
		case 0: 
			{ //main menu
				int IStartPosX = (window.getSize().x ) / 2 - text.getLocalBounds().width; // меню в середине экрана
				int IStartPosY = 0;
				int IStepPos = 60;
				text.setPosition(IStartPosX, IStartPosY);
				for (int i = 0; i < size(MenuText); i++)
				{
					if (i == ISelectMenu)
						text.setFillColor(Color::Green);
					else text.setFillColor(Color::White);
					text.setString(MenuText[i]);
					if (i != 0)
						//text.setPosition(IStartPosX , IStartPosY + IStepPos * i);
						text.move(0, IStepPos);
					window.draw(text);
					//std::cout << text.getLocalBounds().width << std::endl;
				}
				break;
			}
		}
		window.draw(text);
		window.display();
		//std::cout << Vector2f(text.getOrigin()).x << " " << Vector2f(text.getOrigin()).y << std::endl;
	}
	//system("pause");
	return 0;
}