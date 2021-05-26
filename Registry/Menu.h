#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include <windows.h>
#include <string>
#include <io.h>
#include <vector>
#include <stdlib.h>
#include <cstdlib>
#include <windows.h>
#include <fstream>
#include <direct.h>
#include <cstring>
#include <sstream>
#include <iomanip>
#include "AdditionalStructures.h"
#include <ctime>
#include "Person.h"
#include "Doctors.h"
#include "Patients.h"
using namespace std;

class Menu
{
public:
	Menu();

	void Start();

	void PatientMenu(string name);

	void DoctorMenu(string name);

	string CheckName(string name, string user);

	int CheckData(string data, bool& year);

	void GoldColor(string message);

	void GreenColor(string message);

	void RedColor(string message);

private:
	string _name;
	string number;
	string message;
};

