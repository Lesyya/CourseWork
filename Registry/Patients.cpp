#define _CRT_SECURE_NO_WARNINGS
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
#include "Patients.h"

using namespace std;

Patients::Patients(string name) :Person(name) {}

vector <Card> Patients::CheckCard(bool& found_card)
{
	ifstream file;
	vector <string> _cards;
	_cards = FindFiles("Registry/Patients/Cards");
	vector <Card> _patient_card;
	for (int i = 0; i < _cards.size(); i++)
	{
		if (_name == _cards[i])
		{
			file.open("../Registry/Patients/Cards/" + _name + ".txt");
			found_card = true;
			string buff;
			while (!file.eof())
			{
				Card findCart;

				getline(file, buff, ',');
				findCart.doctorName = buff;

				getline(file, buff, ',');
				findCart.diagnosis = buff;

				getline(file, buff, ',');
				findCart.meetTime = StringToTime(buff);

				getline(file, buff, '\n');
				findCart.meetDay = StringToDate(buff);

				_patient_card.push_back(findCart);
			}
		}
	}
	file.close();
	return _patient_card;
}

vector<Schedule> Patients::CheckWorkSchedule()
{
	ifstream file;
	vector<Schedule> schedule;

	file.open("../Registry/Doctors/Work time.txt");

	if (!file.is_open())
	{
		cout << "ERROR";
	}
	string buff;
	while (!file.eof())
	{
		Schedule newSchedule;

		getline(file, buff, ',');
		newSchedule.doctorName = buff;

		getline(file, buff, ',');
		newSchedule.specialty = buff;

		getline(file, buff, ',');
		newSchedule.startReception = StringToTime(buff);

		getline(file, buff, ',');
		newSchedule.endReception = StringToTime(buff);

		getline(file, buff, ',');
		newSchedule.day1 = stoi(buff);

		getline(file, buff, ',');
		newSchedule.day2 = stoi(buff);

		getline(file, buff, '\n');
		newSchedule.day3 = stoi(buff);

		schedule.push_back(newSchedule);
	}
	file.close();
	return schedule;
}

void Patients::MakeAppointment(string d_name, string time, string data)
{
	fstream file;
	file.open("Doctors/Records.txt", ofstream::app);
	if (!file.is_open())
	{
		cout << "ERROE";
	}
	if (file.is_open())
	{
		long file_size;
		file.seekg(0, ifstream::end);
		file_size = file.tellg();
		if (file_size == 0)
		{
			file << d_name << "," << _name << "," << time << "," << data;
		}
		else
		{
			file << "\n" << d_name << "," << _name << "," << time << "," << data;
		}
	}
	file.close();
}
