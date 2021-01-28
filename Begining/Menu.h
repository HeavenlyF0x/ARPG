#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Settings.h"

using namespace sf;

vector<string> MainMenuArr[] = {
	{ "Game", "Settings", "Exit" }, //Главное меню
	{ "New game", "Contine", "Load game", "Back" },//Game
	{ "Screen mode: ", "Screen resolution: ", "Defaul settings", "Accept", "Back" }//Settings
};

class Menu //на когда-нибудь
{
public:
	//Menu();
	Menu(RenderWindow &_window);
	~Menu();
	void setDebugBoxView(bool _value);
	bool getDebugBoxView();	
	int MainMenuChanger(Event& event, Settings& settings);
	void DrawMenu();
	//////
	int getISelector();
	int getMainMenuSelector();
	//////
private:
	Vector2f MenuPos;
	float StringGap; // расстояние между строками меню в высоту
	Font font;
	vector<Text> text;
	vector<string> MenuList;
	int ISelector;
	int MainMenuSelector;
	bool visible;
	bool ViewDebugBox;
	RectangleShape DebugRect;
	RenderWindow& window;
	void setMenuList(vector<string> _MenuList);
	int MouseCollisionText();
	
	int MenuSelector();
};

//Menu::Menu()
//{
//}

Menu::Menu(RenderWindow& _window) : window(_window)
{
	
	MenuPos = Vector2f(window.getSize().x / 5, window.getSize().y / 5);
	StringGap = 50;
	font.loadFromFile("calibri.ttf");
	//font.loadFromFile("COLONNA.TTF");
	visible = true;
	ViewDebugBox = false;
	MainMenuSelector = 0;
	setMenuList(MainMenuArr[0]);
}

Menu::~Menu()
{
}

void Menu::DrawMenu()
{
	int iter = 0;
	if (ViewDebugBox)
	{
		DebugRect.setOutlineColor(Color::Yellow);
		DebugRect.setFillColor(Color::Black);
		DebugRect.setOutlineThickness(1);
	}
	for (Text Ttext : text)
	{
		if (iter == ISelector)
			Ttext.setFillColor(Color::Green);
		else Ttext.setFillColor(Color::White);
		if (ViewDebugBox)
		{
			DebugRect.setPosition(Ttext.getPosition());
			DebugRect.setSize(Vector2f(Ttext.getLocalBounds().width, Ttext.getCharacterSize()));
			window.draw(DebugRect);
		}
		window.draw(Ttext);
		iter++;
	}
}

int Menu::MenuSelector()
{
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			ISelector--;
			if (ISelector < 0)
				ISelector = 0;
		}
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			ISelector++;
			if (ISelector > MenuList.size() - 1)
				ISelector = MenuList.size() - 1;
		}
		MouseCollisionText();
	return ISelector;
}

void Menu::setMenuList(vector<string> _MenuList)
{
	MenuList = _MenuList;
	text.clear();
	for (int i = 0; i < MenuList.size(); i++)
	{
		text.push_back(Text(MenuList[i], font, StringGap));
		text[i].setPosition(Vector2f(MenuPos.x, MenuPos.y + ((StringGap+20) * i)));
	}
	ISelector = -1;
}

inline int Menu::MouseCollisionText()
{
	int iter = 0;
	for (Text Ttext : text)
	{
		if (Mouse::getPosition().x - window.getPosition().x > Ttext.getPosition().x && Mouse::getPosition().x - window.getPosition().x < Ttext.getPosition().x + Ttext.getLocalBounds().width &&
			Mouse::getPosition().y - window.getPosition().y > Ttext.getPosition().y && Mouse::getPosition().y - window.getPosition().y < Ttext.getPosition().y + Ttext.getCharacterSize())
			ISelector = iter;
		iter++;
	}
	return ISelector;
}

inline void Menu::setDebugBoxView(bool _value)
{
	ViewDebugBox = _value;
}

inline bool Menu::getDebugBoxView()
{
	return ViewDebugBox;
}

int Menu::MainMenuChanger(Event& event, Settings& settings)
{
	MenuSelector();
	if (Keyboard::isKeyPressed(Keyboard::Enter) || Keyboard::isKeyPressed(Keyboard::Space) || (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left))
	{
		switch (MainMenuSelector)
		{
		case 0: //MainMenuList
		{
			switch (ISelector)
			{
			case 0: //Game
			{
				setMenuList(MainMenuArr[1]);
				MainMenuSelector = 1;
				break;
			}
			case 1: //Settings
			{
				setMenuList(vector<string>({MainMenuArr[2][0] + settings.getScreenModeStr(), MainMenuArr[2][1] + to_string(settings.getWindowWidth()) + "x" + to_string(settings.getWindowHeigh()),
					MainMenuArr[2][2], MainMenuArr[2][3], MainMenuArr[2][4] }));
				MainMenuSelector = 2;
				break;
			}
			case 2: //Exit
			{
				setMenuList(vector<string>() = { "Yes", "No" });
				MainMenuSelector = -1;
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
				setMenuList(MainMenuArr[0]);
				MainMenuSelector = 0;
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
				text[0].setString(MainMenuArr[2][0] + settings.nextScreenMode(text[0].getString(), MainMenuArr[2][0]));
				break;
			}
			case 1://screen resolution
			{
				text[1].setString(MainMenuArr[2][1] + settings.nextWindowResolution(text[1].getString(), MainMenuArr[2][1]));
				break;
			}
			case 3://Accept
			{
				settings.setScreenMode(text[0].getString().substring(MainMenuArr[2][0].size(), text[0].getString().getSize() - MainMenuArr[2][0].size()));
				settings.setWindowResolution(text[1].getString().substring(MainMenuArr[2][1].size(), text[1].getString().getSize() - MainMenuArr[2][1].size()));
				settings.SaveSettingInFile();
				setMenuList(MainMenuArr[0]);
				MainMenuSelector = 0;
				break;
			}
			case 4: //back (to main menu)
			{
				setMenuList(MainMenuArr[0]);
				MainMenuSelector = 0;
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
				setMenuList(MainMenuArr[0]);
				MainMenuSelector = 0;
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
	return 0;
}

inline int Menu::getISelector()
{
	return ISelector;
}

inline int Menu::getMainMenuSelector()
{
	return MainMenuSelector;
}
