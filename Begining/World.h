#pragma once 
#include <SFML/Graphics.hpp>
#include <map>
const unsigned int WORLDMAXWIDTH = 50;
const unsigned int WORLDMAXHEIGH = 80;

using namespace sf;

class World
{
public:
	World();
	~World();
	void FillEmptryWorld();
	void DrawWorld(RenderWindow& window);
private:
	int world[WORLDMAXWIDTH][WORLDMAXWIDTH];
	Vector2f TileSize;
	Vector2f BeginigPosition;
	map<int, Vector3i> TileSet;
	RectangleShape Tile;
};

World::World()
{
	FillEmptryWorld();
	TileSize = Vector2f(32, 32);
	BeginigPosition = Vector2f(0, 0);
}

World::~World()
{
}

void World::FillEmptryWorld()
{
	for (int i = 0; i < WORLDMAXWIDTH; i++)
		for (int j = 0; j < WORLDMAXHEIGH; j++)
			world[i][j] = 0;
}

inline void World::DrawWorld(RenderWindow &window)
{
	for (int i = 0; i < WORLDMAXWIDTH; i++)
		for (int j = 0; j < WORLDMAXHEIGH; j++)
		{
			//window.draw();
		}
}
