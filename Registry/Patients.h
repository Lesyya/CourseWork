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
using namespace std;

class Patients :public Person
{
public:
	Patients(string name);

	vector <Card> CheckCard(bool& found_card);

	vector<Schedule> CheckWorkSchedule();

	void MakeAppointment(string d_name, string time, string data);
};


