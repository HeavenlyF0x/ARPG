#include <SFML/Graphics.hpp>
#include <iostream>
#include "Settings.h"
#include "Menu.h"
#include <list>
#include <map>
#include <vector>
#include "World.h"
#include "Player.h"

using namespace sf;

void main()
{
	Settings GameSettings;
	RenderWindow window(sf::VideoMode(GameSettings.getWindowWidth(), GameSettings.getWindowHeigh()), GameSettings.getWindowTitle(), GameSettings.getScreenModeInt());
	Event event;	
	Menu MainMenu(window);
	MainMenu.setDebugBoxView(true);
	int IMainProgramSelector = 1;
	//World world;
	Player player(window);

	Clock clock;
	
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 1200; 
		std::cout << time << std::endl;
		window.clear();
		while (window.pollEvent(event))///////отлов event'ов
		{
			if (event.type == Event::Closed) {
				window.close();
			}
			switch (IMainProgramSelector)
			{
			case 0:  //стартовое меню
				IMainProgramSelector = MainMenu.MainMenuChanger(event, GameSettings);
				break;
			case 1: //игровой процесс
			{
				player.PlayerControl(event);
			}
				break;
			default:
				break;
			}
			
		}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		switch (IMainProgramSelector)//////// отрисовка
		{
		case 0:  //стартовое меню
			MainMenu.DrawMenu();
			break;
		case 1: //игровой процесс
		{
			//world.DrawWorld(window);
			player.Update(time);
		}
			break;
		default:
			break;
		}
		window.display();
	}
}