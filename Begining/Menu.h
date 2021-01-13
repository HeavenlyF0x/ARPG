#pragma once
#include <SFML/Graphics.hpp>
#include <list>

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
	Menu(RenderWindow& _window, list<string> _MenuList, Vector2f _MenuPos, float _StringGap, float _FontSize);
	~Menu();
	int ViewMenu();
	int MenuSelector();
	bool View();
	bool Hide();
private:
	RenderWindow& window;
	list<string> MenuList;
};

//Menu::Menu()
//{
//}

Menu::Menu(RenderWindow& _window, list<string> _MenuList, Vector2f _MenuPos, float _StringGap, float _FontSize) : window(_window)
{
	MenuList = _MenuList;
	MenuPos = _MenuPos;
	StringGap = _StringGap;
	font.loadFromFile("calibri.ttf");
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
		for (string SMenuString : MenuList)
		{
			if (iter == ISelector)
				text.setFillColor(Color::Green);
			else text.setFillColor(Color::White);
			text.setString(SMenuString);
			if (Mouse::getPosition().x - window.getPosition().x > text.getPosition().x && Mouse::getPosition().x - window.getPosition().x < text.getPosition().x + text.getLocalBounds().width &&
				Mouse::getPosition().y - window.getPosition().y > text.getPosition().y && Mouse::getPosition().y - window.getPosition().y < text.getPosition().y + text.getLocalBounds().height)
			{
				text.setFillColor(Color::Red);
				ISelector = iter;
			}
			else
			{
				//ISelector = -1; 
				//text.setFillColor(Color::Blue);
			}
			window.draw(text);
			text.move(0, StringGap);
			iter++;
		}
		//std::cout << "Select: " << ISelector << endl;
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