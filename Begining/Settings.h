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
};

class Settings //��������� �� ���������
{
public:
	MapParamStruct SettMapParam;
	map <string, string> SettMap; //��� �������� ����������� ����������

	Settings();
	~Settings();
private:
	string SettingFile = "Settings.ini";
	int CheckSettingsFile(); //��������� ������� ����� � �����������, ���� ��� ���, �� ������� � ��������� ������������ ����������� (Settings.SettMap), ���� �� ���� ��������� LoadSettingsFromFile()
	int LoadSettingsFromFile();//������ ���� ������� � �������� ���������� � Settings.SettMap
	
};

Settings::Settings() 
{
	SettMap = { //����������� ���������
	   {SettMapParam.WINDOWHEIGH, "800"},
	   {SettMapParam.WINDOWWIDTH, "600"},
	   {SettMapParam.WINDOWTITLE, "Paxamet's ARPG"}
	};
	CheckSettingsFile();
}

Settings::~Settings()
{
}

int Settings::CheckSettingsFile() //
{
	ofstream file(SettingFile, ios::_Nocreate);
	if (!file.is_open()) 
	{
		file.close();
		//���� ����� � ����������� ���, ������ ���, ��������� ���������� ����������� � ������
		ofstream file(SettingFile);
		for (auto it = SettMap.begin(); it != SettMap.end(); it++) 
			file << it->first << "=" << it->second << endl;
		//file << "WindowWidth=" << SettMap["WindowWidth"] << endl;
		//file << "WindowHeigh=" << SettMap["WindowHeigh"] << endl;
		//file << "WindowTitle=" << SettMap["WindowTitle"] << endl;
		file.close();
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
		file >> SettingString; // ������ ������ �� ����� � ������ � �� �������� � ��� ��������
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
		BItsValue = false; //��������� �������
		SettMap[SParam] = SValue;
		//std::cout << SParam << "=" << SValue << std::endl;
	}
	file.close();
	return 0;
}