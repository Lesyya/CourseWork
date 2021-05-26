#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <string>
#include <io.h>
#include <vector>
#include <stdlib.h>
#include <cstdlib>
#include <fstream>
#include <direct.h>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <ctime>
#include "Person.h"
#include "AdditionalStructures.h"

Person::Person(string name)
{
	_name = name;
}

vector <Note> Person::CheckRecords()
{
	ifstream file;
	vector <Note> records;
	file.open("../Registry/Doctors/Records.txt");
	if (!file.is_open())
	{
		cout << "ERROR";
	}
	string buff;
	while (!file.eof())
	{
		Note newNote;

		getline(file, buff, ',');
		newNote.doctorName = buff;

		getline(file, buff, ',');
		newNote.patientName = buff;

		getline(file, buff, ',');
		newNote.meetTime = StringToTime(buff);

		getline(file, buff, '\n');
		newNote.meetDay = StringToDate(buff);

		records.push_back(newNote);
	}
	file.close();
	return records;
}
vector<string> Person::FindFiles(string directory)
{
	vector<string> files;
	string out_path;
	_finddata_t data;
	char dir[40];
	char path[60] = "../";

	strcat(path, directory.c_str());
	out_path = (const char*)path;
	strcat(path, "/*.txt");

	intptr_t handle = _findfirst(path, &data);
	do
	{
		string temp = data.name;
		temp.erase(temp.size() - 4, 4);
		files.emplace_back(temp);
	} while (_findnext(handle, &data) == 0);
	_findclose(handle);
	//temp-name vector
	return files;
}
Time Person::StringToTime(string strTime) {
	Time time;
	int h, m;

	h = stoi(strTime.substr(0, 2));
	m = stoi(strTime.substr(3, 2));

	time = { h, m };

	return time;
}
Date Person::StringToDate(string strDate) {
	Date date;
	int d, m, y;

	d = stoi(strDate.substr(0, 2));
	m = stoi(strDate.substr(3, 2));
	y = stoi(strDate.substr(6, 4));

	date = { d,m,y };

	return date;
}
