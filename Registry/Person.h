#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include <windows.h>
#include <string>
#include <io.h>
#include <vector>
#include <direct.h>
#include "AdditionalStructures.h"

class Person
{
protected:
	string _name;
public:

	Person(string name);

	vector <Note> CheckRecords();

	vector<string> FindFiles(string directory);

	Time StringToTime(string strTime);

	Date StringToDate(string strDate);
};



