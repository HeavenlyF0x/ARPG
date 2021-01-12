#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <map>
//#include <Windows.h>

using namespace std;


//TCHAR SettingsPath[] = L"C:\\Users\\\\Documents\\ARPG";
//TCHAR SettingFile[] = L"Settings.ini";
struct MapParamStruct
{
	const string WINDOWWIDTH = "WindowWidth";
	const string WINDOWHEIGH = "WindowHeigh";
	const string WINDOWTITLE = "WindowTitle";
	const string SCREENMODE = "ScreenMode";
};

class Settings //Настройки по умолчанию
{
public:
	MapParamStruct SettMapParam;
	map <string, string> SettMap; //для хранения стандартных параметров

	Settings();
	~Settings();
private:
	string SettingFile = "Settings.ini";
	int CheckSettingsFile(); //Проверяет наличие файла с настройками, если его нет, то создает и заполняет стандратными настройками (Settings.SettMap), если он есть выполняет LoadSettingsFromFile()
	int LoadSettingsFromFile();//Чтение файа настрое и загрузка параметров в Settings.SettMap
	int SettMapParamScreenmodeCrutch();
};

Settings::Settings() 
{
	SettMap = { //Стандартные параметры
	    {SettMapParam.WINDOWWIDTH, "1280"},
	    {SettMapParam.WINDOWHEIGH, "1024"},
	    {SettMapParam.WINDOWTITLE, "Paxamet's ARPG"},
		{SettMapParam.SCREENMODE, "Borderless"} //None - 0 , без рамки не на весь экран (Borderless); Fullscreen - 8 - фуллскрин
	};
	CheckSettingsFile();
}

Settings::~Settings()
{
}

int Settings::SettMapParamScreenmodeCrutch() 
{
	if (SettMap[SettMapParam.SCREENMODE] == "Fullscreen")
		SettMap[SettMapParam.SCREENMODE] = "8";
	if (SettMap[SettMapParam.SCREENMODE] == "Borderless")
		SettMap[SettMapParam.SCREENMODE] = "0";
	return 0;
}

int Settings::CheckSettingsFile() //
{
	ofstream file(SettingFile, ios::_Nocreate);
	if (!file.is_open()) 
	{
		file.close();
		//Если файла с настройками нет, создаёт его, заполняет дефолтными параметрами и читаем
		ofstream file(SettingFile);
		for (auto it = SettMap.begin(); it != SettMap.end(); it++) 
			file << it->first << "=" << it->second << endl;
		//file << "WindowWidth=" << SettMap["WindowWidth"] << endl;
		//file << "WindowHeigh=" << SettMap["WindowHeigh"] << endl;
		//file << "WindowTitle=" << SettMap["WindowTitle"] << endl;
		file.close();
		
		SettMapParamScreenmodeCrutch();
		
	}
	else
	{
		file.close();
		LoadSettingsFromFile();
	}
	return 0;
}


int Settings::LoadSettingsFromFile() 
{
	ifstream file(SettingFile);
	while (!file.eof())
	{
		string SettingString, SParam, SValue;
		file >> SettingString; // читаем строку из файла и парсим её на парамерт и его значение
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
		SettMap[SParam] = SValue;
		//std::cout << SParam << "=" << SValue << std::endl;
	}
	file.close();
	
	SettMapParamScreenmodeCrutch();

	return 0;
}