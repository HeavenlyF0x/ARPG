#include <SFML/Graphics.hpp>
#include <iostream>
#include "Settings.h"
#include "Menu.h"
#include <list>
#include <map>


using namespace sf;

int main()
{
	Settings GameSettings = Settings();
	RenderWindow window(sf::VideoMode(std::stof(GameSettings.SettMap[GameSettings.SettMapParam.WINDOWWIDTH]), std::stof(GameSettings.SettMap[GameSettings.SettMapParam.WINDOWHEIGH])),
		GameSettings.SettMap[GameSettings.SettMapParam.WINDOWTITLE], stoi(GameSettings.SettMap[GameSettings.SettMapParam.SCREENMODE]));
	
	int IMainProgramSelector = 0;

	
	int IMenuSelector = 0;
	int ISelector = -1;

	list<string> MainMenuList = { "Game", "Settings", "Exit" };
	list<string> GameMenuList = { "New game", "Contine", "Load game", "Back" };
	list<string> SettingsMenuList = { "Screen mode: " + GameSettings.SettMap[GameSettings.SettMapParam.SCREENMODE], "Screen resolution: " + GameSettings.SettMap[GameSettings.SettMapParam.WINDOWWIDTH] + "x" + GameSettings.SettMap[GameSettings.SettMapParam.WINDOWHEIGH], "Back" };

	/*map<int, list<string>> MenuListMap =
	{
		{0, MainMenuList},
		{1, GameMenuList},
		{2, SettingsMenuList}
	};*/
	

	Menu MainMenu(window, MainMenuList, Vector2f(window.getSize().x/3, window.getSize().y/3), 70, 50);
	MainMenu.View();

	while (window.isOpen())
	{
		window.clear();
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) {
				window.close();
			}
			switch (IMainProgramSelector)
			{
			case 0: { //Тело стартового меню

				ISelector = MainMenu.MenuSelector();
				
				/*if (Mouse::isButtonPressed(Mouse::Left))
				{
					
				}*/

				if (Keyboard::isKeyPressed(Keyboard::Enter) || Keyboard::isKeyPressed(Keyboard::Space) || (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left))
				{
					switch (IMenuSelector)
					{
					case 0: //MainMenuList
					{
						switch (ISelector)
						{
						case 0: //Game
						{
							MainMenu.setMenuList(GameMenuList);
							IMenuSelector = 1;
							break;
						}
						case 1: //Settings
						{
							MainMenu.setMenuList(SettingsMenuList);
							IMenuSelector = 2;
							break;
						}
						case 2: //Exit
						{
							MainMenu.setMenuList(list<string>() = { "Yes", "No" });
							IMenuSelector = -1;
							break;
						}
						default:
							break;
						}
						break;
					}
					case 1: //GameMenuList = {"New game", "Contine", "Load game", "Back"};
					{
						switch (ISelector)
						{
						case 0: // new game
						{

							break;
						}
						case 1: //contine
						{

							break;
						}
						case 2: //Load game
						{

							break;
						}
						case 3: // back (to main menu)
						{
							MainMenu.setMenuList(MainMenuList);
							IMenuSelector = 0;
							break;
						}
						default:
							break;
						}
						break;
					}
					case 2: //SettingsMenuList
					{
						switch (ISelector)
						{
						case 2: //back (to main menu)
						{
							MainMenu.setMenuList(MainMenuList);
							IMenuSelector = 0;
							break;
						}
						default:
							break;
						}
						break;
					}
					case -1: // подтверждение выхода из программы
					{
						switch (ISelector)
						{
						case 0:
						{
							window.close();
						}
						case 1:
						{
							MainMenu.setMenuList(MainMenuList);
							IMenuSelector = 0;
							break;
						}
						default:
							break;
						}
						break;
					}
					default:
						break;
					}
				}
				break;
			}
			case 1: //Тело игрового процесса
			{
				
				break;
			}
			default:
				break;
			}
			
		}

		switch (IMainProgramSelector)
		{
		case 0: //Тело стартового меню
			{ 
				MainMenu.ViewMenu();
				break;
			}
		default:
			break;
		}
		//window.draw(text);
		window.display();
		//std::cout << "Main: " << MainMenu.ISelector << " Game: " << GameMenu.ISelector << " SettParam: " << SettingsParamMenu.ISelector << " SettValue: " << SettingsValueMenu.ISelector << endl;
	}
	//system("pause");

	return 0;
}