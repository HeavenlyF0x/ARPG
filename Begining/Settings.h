#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <map>

using namespace std;



class Settings
{
public:
	map <string, string> SettMap; //для хранения стандартных параметров

	Settings();
	~Settings();

	void SaveSettingInFile();
	int getWindowWidth();
	void setWindowWidth(int _value);
	int getWindowHeigh();
	void setWindowHeigh(int _value);
	int getScreenModeInt();
	string getScreenModeStr();
	void setScreenMode(string _value);
	void setScreenMode(int _value);
	string getWindowTitle();
	string nextScreenMode(string _value, string cap);
	string nextWindowResolution(string _value, string cap);
	void setWindowResolution(string _value);
private:
	const string WINDOW_WIDTH = "WindowWidth";
	const string WINDOW_HEIGH = "WindowHeigh";
	const string WINDOW_TITLE = "WindowTitle";
	const string SCREEN_MODE = "ScreenMode";

	const string SETTING_FILE_NAME = "Settings.ini";
	
	const string SCREEN_MODE_FULLSCREEN = "Fullscreen"; //8
	const string SCREEN_MDOE_BORDERLESS = "Borderless"; //0
	const string SCREEN_MODE_BORDER = "Border"; //7 или другое
	
	const string SCREEN_RESOLUTION_ARR[6] = { "1920x1080", "1280x960", "1280x720", "1200x800", "1024x768", "800x600" };

	bool CheckSettingsFile(); //Проверяет наличие файла с настройками, возвращает false - если его нет, true - если он есть и он доступен.
	int LoadSettingsFromFile(); //Чтение файа настрое и загрузка параметров в Settings.SettMap
};

Settings::Settings() 
{
	SettMap = { //Стандартные параметры
	    {WINDOW_WIDTH, "1280"},
	    {WINDOW_HEIGH, "1024"},
	    {WINDOW_TITLE, "ARPG"},
		{SCREEN_MODE, "Border"} //None - 0 , без рамки не на весь экран (Borderless); Fullscreen - 8 - фуллскрин; Border - 7 - оконный с рамкой
	};
	if(CheckSettingsFile())
		LoadSettingsFromFile();
	else
		SaveSettingInFile();
}

Settings::~Settings()
{
}

bool Settings::CheckSettingsFile() //
{
	ofstream file(SETTING_FILE_NAME, ios::_Nocreate);
	if (!file.is_open()) 
	{
		file.close();				
		return false;
	}
	else
	{
		file.close();
		return true;
	}
}

int Settings::LoadSettingsFromFile() 
{
	ifstream file(SETTING_FILE_NAME);
	while (!file.eof())
	{
		string SettingString, SParam, SValue;
		file >> SettingString; // читаем строку из файла и парсим её на парамерт и его значение
		if (SettingString != "")
		{
			bool BItsValue = false;
			for (int i = 0; i < SettingString.size(); i++)
			{
				if (!BItsValue)
				{
					if (SettingString[i] != '=')
						SParam += SettingString[i];
					else
						BItsValue = true;
				}
				else
					SValue += SettingString[i];
			}
			BItsValue = false; //Закончили парсить
			if(SValue != "")
				SettMap[SParam] = SValue;
		}
	}
	file.close();
	return 0;
}

void Settings::SaveSettingInFile()
{
	ofstream file(SETTING_FILE_NAME);
	for (auto it = SettMap.begin(); it != SettMap.end(); it++)
	if(it->first != WINDOW_TITLE) //не пишем в файл settings.ini заголовок окна программы, ибо нечего ему там делать.
		file << it->first << "=" << it->second << endl;
	file.close();
}

inline int Settings::getWindowWidth()
{
	return stoi(SettMap[WINDOW_WIDTH]);
}

inline void Settings::setWindowWidth(int _value)
{
	SettMap[WINDOW_WIDTH] = to_string(_value);
}

inline int Settings::getWindowHeigh()
{
	return stoi(SettMap[WINDOW_HEIGH]);
}

inline void Settings::setWindowHeigh(int _value)
{
	SettMap[WINDOW_HEIGH] = to_string(_value);
}

inline int Settings::getScreenModeInt()
{
	if (SettMap[SCREEN_MODE] == SCREEN_MODE_FULLSCREEN)
		return 8;
	else if (SettMap[SCREEN_MODE] == SCREEN_MDOE_BORDERLESS)
		return 0;
	else return 7; //Title bar + fixed border
}

inline string Settings::getScreenModeStr()
{
	return SettMap[SCREEN_MODE];
}

inline void Settings::setScreenMode(string _value)
{
	SettMap[SCREEN_MODE] = _value;
}

inline void Settings::setScreenMode(int _value)
{
	switch (_value)
	{
	case 0:
		SettMap[SCREEN_MODE] = SCREEN_MDOE_BORDERLESS;
		break;
	case 8:
		SettMap[SCREEN_MODE] = SCREEN_MODE_FULLSCREEN;
		break;
	default:
		SettMap[SCREEN_MODE] = SCREEN_MODE_BORDER;
		break;
	}
}

inline string Settings::getWindowTitle()
{
	return SettMap[WINDOW_TITLE];
}

inline string Settings::nextScreenMode(string _value, string cap)
{
	string value = _value;
	value.erase(0, cap.size());
	if (value == SCREEN_MDOE_BORDERLESS)
		return SCREEN_MODE_BORDER;
	if (value == SCREEN_MODE_BORDER)
		return SCREEN_MODE_FULLSCREEN;
	if (value == SCREEN_MODE_FULLSCREEN)
		return SCREEN_MDOE_BORDERLESS;
}

inline string Settings::nextWindowResolution(string _value, string cap)
{
	string value = _value;
	value.erase(0, cap.size());
	if (value == SCREEN_RESOLUTION_ARR[0])
		return SCREEN_RESOLUTION_ARR[1];
	else if (value == SCREEN_RESOLUTION_ARR[1])
		return SCREEN_RESOLUTION_ARR[2];
	else if (value == SCREEN_RESOLUTION_ARR[2])
		return SCREEN_RESOLUTION_ARR[3];
	else if (value == SCREEN_RESOLUTION_ARR[3])
		return SCREEN_RESOLUTION_ARR[4];
	else if (value == SCREEN_RESOLUTION_ARR[4])
		return SCREEN_RESOLUTION_ARR[5];
	else 
		return SCREEN_RESOLUTION_ARR[0];

}

inline void Settings::setWindowResolution(string _value)
{
	string value = _value;
	setWindowWidth(stoi(value.substr(0, value.find('x'))));
	setWindowHeigh(stoi(value.erase(0, value.find('x')+1)));
}
