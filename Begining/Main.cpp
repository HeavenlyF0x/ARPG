#include <SFML/Graphics.hpp>
#include <iostream>
#include "Settings.h"
#include "Menu.h"
#include <list>


using namespace sf;

int main()
{
	Settings GameSettings = Settings();
	RenderWindow window(sf::VideoMode(std::stof(GameSettings.SettMap[GameSettings.SettMapParam.WINDOWWIDTH]), std::stof(GameSettings.SettMap[GameSettings.SettMapParam.WINDOWHEIGH])),
		GameSettings.SettMap[GameSettings.SettMapParam.WINDOWTITLE], stoi(GameSettings.SettMap[GameSettings.SettMapParam.SCREENMODE]));
	
	int ISelector = 0;

	list<string> MainMenuList = {"Game", "Settings", "Exit"};
	Menu MainMenu(window, MainMenuList, Vector2f(window.getSize().x / 2, window.getSize().y / 4), 70, 70);
	MainMenu.View();
	
	list<string> GameMenuList = {"New game", "Contine", "Load game", "Back"};
	Menu GameMenu(window, GameMenuList, Vector2f(0, 0), 120, 120);

	list<string> SettingsParamMenuList = {"Screen mode: ", "Screen resolution: ", "Back"};
	Menu SettingsParamMenu(window, SettingsParamMenuList, Vector2f(window.getSize().x/4, window.getSize().y / 4), 50, 50);

	list<string> SettingsValueMenuList = {GameSettings.SettMap[GameSettings.SettMapParam.SCREENMODE], GameSettings.SettMap[GameSettings.SettMapParam.WINDOWWIDTH] + "x" + GameSettings.SettMap[GameSettings.SettMapParam.WINDOWHEIGH] };
	Menu SettingsValueMenu(window, SettingsValueMenuList, Vector2f(window.getSize().x - window.getSize().x / 4, window.getSize().y / 4), 50, 50);
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
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					switch (MainMenu.ISelector)
					{
					case 0: { //Game in main menu
						MainMenu.Hide();
						GameMenu.View();
						switch (GameMenu.ISelector)
						{
						case 3: {//back
							GameMenu.Hide();
							MainMenu.View();
							break;
						}
						default:
							break;
						}
						break;
					}
					case 1: { //Settings in main menu
						MainMenu.Hide();
						SettingsParamMenu.View();
						SettingsValueMenu.View();
						switch (SettingsParamMenu.ISelector)
						{
						case 2: {//back
							SettingsParamMenu.Hide();
							SettingsValueMenu.Hide();
							MainMenu.View();
							break;
						}
						default:
							break;
						}
						break;
					}
					case 2: { //Exit in Main menu
						window.close();
						break;
					}
					default:
						break;
					}
				}
				MainMenu.MenuSelector();
				GameMenu.MenuSelector();
				SettingsParamMenu.MenuSelector();
				SettingsValueMenu.MenuSelector();

				if (Keyboard::isKeyPressed(Keyboard::Enter) || Keyboard::isKeyPressed(Keyboard::Space))
				{
					switch (MainMenu.ISelector)
					{
					case 0: { //Game in main menu
						MainMenu.Hide();
						GameMenu.View();
						switch (GameMenu.ISelector)
						{
						case 3: {//back
							GameMenu.Hide();
							MainMenu.View();
							break;
						}
						default:
							break;
						}
						break;
					}
					case 1: { //Settings in main menu
						MainMenu.Hide();
						SettingsParamMenu.View();
						SettingsValueMenu.View();
						switch (SettingsParamMenu.ISelector)
						{
						case 2: {
							SettingsParamMenu.Hide();
							SettingsValueMenu.Hide();
							MainMenu.View();
							break;
						}
						default:
							break;
						}
						break;
					}
					case 2: { //Exit in Main menu
						window.close();
						break;
					}
					default:
						break;
					}
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
			MainMenu.ViewMenu();
			GameMenu.ViewMenu();
			SettingsParamMenu.ViewMenu();
			SettingsValueMenu.ViewMenu();
				break;
			}
		}
		//window.draw(text);
		window.display();
		std::cout << "Main: " << MainMenu.ISelector << " Game: " << GameMenu.ISelector << " SettParam: " << SettingsParamMenu.ISelector << " SettValue: " << SettingsValueMenu.ISelector << endl;
	}
	//system("pause");
	return 0;
}