#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>

using namespace std;

int CreateSettingsFile() {
	ofstream file;
	file.open("C:/Users/Paxamet/Documents/ARPG/Settings.ini");
	return 0;
}

struct WindowSettings
{
	int WindowWidth = 800;
	int WindowHeigh = 600;
};