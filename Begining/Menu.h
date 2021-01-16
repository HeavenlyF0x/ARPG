#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Settings.h"

using namespace sf;

class Menu //на когда-нибудь
{
public:
	Vector2f MenuPos;
	float StringGap;
	Font font;
	Text text;
	int ISelector;
	bool visible;

	//Menu();
	Menu(RenderWindow& _window, vector<string> MenuList, Vector2f _MenuPos, float _StringGap, float _FontSize);
	~Menu();
	int ViewMenu();
	int MenuSelector();
	bool View();
	bool Hide();
	void setMenuList(vector<string> _MenuList);
	//void StartMenuControl();

	
private:
	RenderWindow& window;
	vector<string> MenuList;
};

//Menu::Menu()
//{
//}

Menu::Menu(RenderWindow& _window, vector<string> _MenuList, Vector2f _MenuPos, float _StringGap, float _FontSize) : window(_window)
{
	MenuList = _MenuList;
	MenuPos = _MenuPos;
	StringGap = _StringGap;
	font.loadFromFile("calibri.ttf");
	//font.loadFromFile("COLONNA.TTF");
	visible = false;
	ISelector = -1;
	text.setCharacterSize(_FontSize);
}

Menu::~Menu()
{
}

int Menu::ViewMenu()
{
	if (visible)
	{
		text.setFont(font);
		//text.setCharacterSize(StringGap);
		text.setPosition(MenuPos);
		int iter = 0;
		///////////////////
		RectangleShape DebugRect;
		DebugRect.setOutlineColor(Color::Yellow);
		DebugRect.setFillColor(Color::Black);
		DebugRect.setOutlineThickness(1);
		///////////////////
		for (string SMenuString : MenuList)
		{
			if (iter == ISelector)
				text.setFillColor(Color::Green);
			else text.setFillColor(Color::White);
			text.setString(SMenuString);
			if (Mouse::getPosition().x - window.getPosition().x > text.getPosition().x && Mouse::getPosition().x - window.getPosition().x < text.getPosition().x + text.getLocalBounds().width &&
				Mouse::getPosition().y - window.getPosition().y > text.getPosition().y && Mouse::getPosition().y - window.getPosition().y < text.getPosition().y + text.getCharacterSize())
			{
				text.setFillColor(Color::Red);
				ISelector = iter;
			}
			else
			{
				//ISelector = -1; 
				//text.setFillColor(Color::Blue);
			}
			DebugRect.setPosition(text.getPosition());
			DebugRect.setSize(Vector2f(text.getLocalBounds().width, text.getCharacterSize()));
			//DebugRect.setSize(Vector2f(text.getLocalBounds().width, text.getLocalBounds().height));
			window.draw(DebugRect);
			window.draw(text);
			//window.draw(RectangleShape(Vector2f(50, 50)));
			text.move(0, StringGap);
			//text.setPosition(0, StringGap*(iter));
			iter++;
		}
	}
	return 0;
}

int Menu::MenuSelector()
{
	if (visible)
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
	}
	return ISelector;
}

bool Menu::View()
{
	visible = true;
	return visible;
}

bool Menu::Hide()
{
	visible = false;
	//ISelector = -1;
	return visible;
}
void Menu::setMenuList(vector<string> _MenuList)
{
	MenuList = _MenuList;
	ISelector = -1;
}