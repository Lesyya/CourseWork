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
#include "Doctors.h"

Doctors::Doctors(string name) :Person(name) {}

vector <Card> Doctors::CheckCard(bool& found_card, string patient_name)
{
	ifstream file;
	vector <string> _cards;
	_cards = FindFiles("Registry/Patients/Cards");
	vector <Card> _patient_card;
	for (int i = 0; i < _cards.size(); i++)
	{
		if (patient_name == _cards[i])
		{
			file.open("../Registry/Patients/Cards/" + patient_name + ".txt");
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

void Doctors::CreateCard(string _patient_name)
{
	ofstream create("Patients/Cards/" + _patient_name + ".txt");
}

void Doctors::WriteDiagnosis(string patient_name, string diagnosis, string time, string data)
{
	fstream file;
	file.open("Patients/Cards/" + patient_name + ".txt", ofstream::app);
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
			file << _name << "," << diagnosis << "," << time << "," << data;
		}
		else
		{
			file << "\n" << _name << "," << diagnosis << "," << time << "," << data;
		}
	}
	file.close();
}
