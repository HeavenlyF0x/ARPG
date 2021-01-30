#pragma once
#include <SFML/Graphics.hpp>
#include<map>
#include "Settings.h"

using namespace std;

class World
{
public:
	World();
	~World();
	void DrawWorld(RenderWindow &_window);
	void ShowGrid(bool value);
private:
	map<int, sf::Color> TileSet;
	static const int WORLD_W = 30;
	static const int WORLD_H = 30;
	int world[WORLD_W][WORLD_H];
	void FillTestWorld();
	RectangleShape Tile;
	Vector2f TileSize = { 32, 32 };
	Vector2f BeginigWorld = { 0, 0};
	bool Grid;
};

World::World()
{
	TileSet = {
		{0, sf::Color::White},
		{1, sf::Color::Cyan}
	};
	FillTestWorld();
	Tile.setSize(TileSize);
	Tile.setOutlineColor(Color::Black);
	ShowGrid(true);
}

World::~World()
{
}

inline void World::DrawWorld(RenderWindow& _window)
{
	Grid?Tile.setOutlineThickness(1):Tile.setOutlineThickness(0);
	RenderWindow& win = _window;
	for (int x = 0; x < WORLD_W; x++)
		for (int y = 0; y < WORLD_H; y++)
		{
			Tile.setPosition(Vector2f(BeginigWorld.x + TileSize.x * x, BeginigWorld.y + TileSize.y * y));
			Tile.setFillColor(TileSet[world[x][y]]);
			//
			if (Mouse::getPosition().x - win.getPosition().x > BeginigWorld.x + TileSize.x * x && Mouse::getPosition().y - win.getPosition().y > BeginigWorld.y + TileSize.y * y &&
				Mouse::getPosition().x - win.getPosition().x < BeginigWorld.x + TileSize.x * (x + 1) && Mouse::getPosition().y - win.getPosition().y < BeginigWorld.y + TileSize.y * (y + 1))
			{
				Tile.setFillColor(Color::Red);

			//	cout << "X =\t" << x << "\tY = \t" << y << endl;
			}
			win.draw(Tile);
		}
}

inline void World::ShowGrid(bool value)
{
	value ? Grid = true : Grid = false;
}


inline void World::FillTestWorld()
{
	for (int x = 0; x < WORLD_W; x++)
		for (int y = 0; y < WORLD_H; y++)
			world[x][y] = 0;
	world[0][1] = 1;
	world[10][7] = 1;
}
