#pragma once
#include <SFML/Graphics.hpp>
#include<map>
#include "Settings.h"

using namespace std;

class World
{
public:
	World(RenderWindow& _window);
	~World();
	
private:
	RenderWindow& win;
};

World::World(RenderWindow& _window):win(_window)
{
	
}

World::~World()
{
}

