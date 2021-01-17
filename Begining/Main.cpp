#include <SFML/Graphics.hpp>
#include <iostream>
#include "Settings.h"
#include "Menu.h"
#include <list>
#include <map>
#include <vector>


using namespace sf;

int main()
{
	Settings GameSettings = Settings();
	RenderWindow window(sf::VideoMode(std::stof(GameSettings.SettMap[GameSettings.SettMapParam.WINDOWWIDTH]), std::stof(GameSettings.SettMap[GameSettings.SettMapParam.WINDOWHEIGH])),
		GameSettings.SettMap[GameSettings.SettMapParam.WINDOWTITLE], stoi(GameSettings.SettMap[GameSettings.SettMapParam.SCREENMODE]));
	
	int IMainProgramSelector = 0;

	
	int IMenuSelector = 0;
	int ISelector = -1;

	vector<string> MainMenuList = { "Game", "Settings", "Exit" };
	vector<string> GameMenuList = { "New game", "Contine", "Load game", "Back" };
	/// SCREENMODE CRUTCH
	if (GameSettings.SettMap[GameSettings.SettMapParam.SCREENMODE] == "0")
		GameSettings.SettMap[GameSettings.SettMapParam.SCREENMODE] = "Borderless";
	else if (GameSettings.SettMap[GameSettings.SettMapParam.SCREENMODE] == "8")
		GameSettings.SettMap[GameSettings.SettMapParam.SCREENMODE] = "Fullscreen";
	//////
	vector<string> SettingsMenuList = {
		"Screen mode: " + GameSettings.SettMap[GameSettings.SettMapParam.SCREENMODE], 
		"Screen resolution: " + GameSettings.SettMap[GameSettings.SettMapParam.WINDOWWIDTH] + "x" + GameSettings.SettMap[GameSettings.SettMapParam.WINDOWHEIGH], 
		"Defaul settings",
		"Accept", 
		"Back" };

	string ScreenResolutionArr[] = { "1920x1080", "1280x960", "1280x720", "1200x800", "1024x768", "800x600" };

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
							MainMenu.setMenuList(vector<string>() = { "Yes", "No" });
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
						case 0: //screenmode
						{
							if (SettingsMenuList[0] == "Screen mode: Borderless")
								SettingsMenuList[0] = "Screen mode: Fullscreen";
							else if (SettingsMenuList[0] == "Screen mode: Fullscreen")
								SettingsMenuList[0] = "Screen mode: Borderless";
							else SettingsMenuList[0] = "Screen mode: Borderless";
							MainMenu.setMenuList(SettingsMenuList);
							break;
						}
						case 1://screen resolution
						{
							if (SettingsMenuList[1] == "Screen resolution: " + ScreenResolutionArr[0])
								SettingsMenuList[1] = "Screen resolution: " + ScreenResolutionArr[1];
							else if (SettingsMenuList[1] == "Screen resolution: " + ScreenResolutionArr[1])
								SettingsMenuList[1] = "Screen resolution: " + ScreenResolutionArr[2];
							else if (SettingsMenuList[1] == "Screen resolution: " + ScreenResolutionArr[2])
								SettingsMenuList[1] = "Screen resolution: " + ScreenResolutionArr[3];
							else if (SettingsMenuList[1] == "Screen resolution: " + ScreenResolutionArr[3])
								SettingsMenuList[1] = "Screen resolution: " + ScreenResolutionArr[4];
							else if (SettingsMenuList[1] == "Screen resolution: " + ScreenResolutionArr[4])
								SettingsMenuList[1] = "Screen resolution: " + ScreenResolutionArr[5];
							else if (SettingsMenuList[1] == "Screen resolution: " + ScreenResolutionArr[5])
								SettingsMenuList[1] = "Screen resolution: " + ScreenResolutionArr[0];
							else SettingsMenuList[1] = "Screen resolution: " + ScreenResolutionArr[0];
							MainMenu.setMenuList(SettingsMenuList);
							break;
						}
						case 3://Accept
						{
							string buff = SettingsMenuList[0];
							GameSettings.SettMap[GameSettings.SettMapParam.SCREENMODE] = buff.erase(0, string("Screen mode: ").size());
							buff = SettingsMenuList[1];
							buff.erase(0, string("Screen resolution: ").size());
							//.erase(0, string("Screen resolution: ").size())
							GameSettings.SettMap[GameSettings.SettMapParam.WINDOWWIDTH] = buff.erase(buff.find("x"), buff.size());
							buff = SettingsMenuList[1];
							GameSettings.SettMap[GameSettings.SettMapParam.WINDOWHEIGH] = buff.erase(0, SettingsMenuList[1].find("x") + 1);
							GameSettings.SaveNewSattings();
							MainMenu.setMenuList(MainMenuList);
							IMenuSelector = 0;
							break;
						}
						case 4: //back (to main menu)
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
							break;
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