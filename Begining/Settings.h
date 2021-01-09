#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
//#include <Windows.h>

using namespace std;


//TCHAR SettingsPath[] = L"C:\\Users\\\\Documents\\ARPG";
//TCHAR SettingFile[] = L"Settings.ini";
class Settings //��������� �� ���������
{
public:
	int WindowWidth;
	int WindowHeigh;
	char SettingFile[14] = "Settings.ini";

	Settings();
	~Settings();
private:
	bool CheckSettingsFile();
	int CreateSettingsFile();
	int LoadSettingsFromFile();
};

Settings::Settings() 
{
	LoadSettingsFromFile();
}

Settings::~Settings()
{
}

bool Settings::CheckSettingsFile()//�������� ������� ����� � ������������, ���� ��� ���, ����� false
{
	ofstream file(SettingFile, ios::_Nocreate);
	if (!file.is_open()) 
	{
		//���� ����� � ����������� ���, ������ ���, ��������� ���������� ����������� � ������
	}
	LoadSettingsFromFile();
	file.close();
}

int Settings::CreateSettingsFile() //���� ����� � ����������� ���, ������ ��� � ��������� ���������� �����������
{
	//CreateDirectory(SettingsPath, NULL);
	if (!CheckSettingsFile())
	{
		ofstream file(SettingFile);
		file << "WindowWidth=";
		file << "WindowHeigh=";
		file.close();
	}
	return 0;
}

int Settings::LoadSettingsFromFile() //������ ���� � ��������
{

}