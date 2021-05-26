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
#include "Menu.h"
#include "Patients.h"
#include "Doctors.h"
using namespace std;

Menu::Menu()
{
	_name = "\0";
	number = 6;
}

void Menu:: Start()
	{
		string User;
		message = "Hello, User!";
		GoldColor(message);
		cout << "Choose who you are:\n1-Patient 2-Doctor\n";
		cin >> User;
		bool user = false;
		while (user == false)
			if (User == "1")
			{
				system("cls");
				message = "Hello, Patient!";
				GoldColor(message);
				string name;
				string client = "your name";
				name = CheckName(name, client);
				PatientMenu(name);
				user = true;
			}
			else if (User == "2")
			{
				system("cls");
				message = "Hello, Doctor!";
				GoldColor(message);
				string name;
				string client = "your name";
				name = CheckName(name, client);
				DoctorMenu(name);
				user = true;
			}
			else
			{
				message = "Error User";
				RedColor(message);
				user = false;
				cin >> User;
			}
	}

void Menu::PatientMenu(string name)
	{
		_name = name;
		Patients user(_name);
		system("cls");
		message = "Hello," + _name;
		GoldColor(message);

		while (number != "0")
		{
			cout << "\nChoose what to do next\n";
			cout << "1-Check my card\n";
			cout << "2-Check which doctors are present now\n";
			cout << "3-Check work schedule\n";
			cout << "4-Make an appointment\n";
			cout << "5-Check if I have an appointments\n";
			cout << "0-Exit\n";
			cin >> number;
			system("cls");
			message = "Hello," + _name;
			GoldColor(message);

			if (number == "1")
			{
				bool value = false;
				bool& found_card = value;
				vector <Card> patient_card;
				patient_card = user.CheckCard(found_card);
				if (found_card == false)
				{
					message = "Card not found. Visit the doctor and then you can start a card";
					RedColor(message);
				}
				else
				{
					message = "Here is your card:";
					GreenColor(message);
					cout << setw(25) << "~Doctor~";
					cout << setw(25) << "~Diagnosis~";
					cout << setw(25) << "~Visit time~";
					cout << setw(25) << "~Day~" << endl;
					for (int i = 0; i < patient_card.size(); i++)
					{
						cout << setw(25) << patient_card[i].doctorName;
						cout << setw(25) << patient_card[i].diagnosis;
						cout << setw(22) << patient_card[i].meetTime.hours << ':' << setw(2) << patient_card[i].meetTime.minutes;
						cout << setw(17) << patient_card[i].meetDay.day << '.' << setw(2) << patient_card[i].meetDay.mounth << '.' << setw(4) << patient_card[i].meetDay.year << endl;
					}
				}
			}
			else if (number == "2")
			{
				vector<Schedule> schedule;
				schedule = user.CheckWorkSchedule();
				time_t now = time(0);
				tm* ltm = localtime(&now);
				bool value = false;
				for (int i = 0; i < schedule.size(); i++)
				{
					if (schedule[i].startReception.hours <= ltm->tm_hour && schedule[i].endReception.hours > ltm->tm_hour && (schedule[i].day1 == ltm->tm_wday || schedule[i].day2 == ltm->tm_wday || schedule[i].day3 == ltm->tm_wday))
					{
						value = true;
						system("cls");
						cout << "1-Mon, 2-Tues, 3-Wed, 4-Thurs, 5-Fri, 6-Satur, 0-Sun" << endl;
						cout << "\n" << setw(30) << "~Doctor~";
						cout << setw(30) << "~Specialty~";
						cout << setw(25) << "~Work from~";
						cout << setw(25) << "~To~";
						cout << setw(25) << "~Days~" << endl;
						cout << setw(30) << schedule[i].doctorName;
						cout << setw(30) << schedule[i].specialty;
						cout << setw(22) << schedule[i].startReception.hours << ':' << setw(2) << schedule[i].startReception.minutes;
						cout << setw(22) << schedule[i].endReception.hours << ':' << setw(2) << schedule[i].endReception.minutes;
						cout << setw(17) << schedule[i].day1 << ',' << setw(2) << schedule[i].day2 << ',' << setw(2) << schedule[i].day3 << endl;
					}
				}
				if (value == false)
				{
					message = "Unfortunately not a single doctor is working now.";
					RedColor(message);
				}
			}
			else if (number == "3")
			{
				system("cls");
				int num;
				cout << "To find out the schedule of a particular doctor?\n1-Yes 2-No\n";
				cin >> num;
				if (num == 1)
				{
					bool value = false;
					string doc_name;
					system("cls");
					string client = "the full name of the doctor";
					doc_name = CheckName(doc_name, client);
					vector<Schedule> schedule;
					schedule = user.CheckWorkSchedule();
					for (int i = 0; i < schedule.size(); i++)
					{
						if (doc_name == schedule[i].doctorName)
						{
							value = true;
							system("cls");
							cout << "1-Mon, 2-Tues, 3-Wed, 4-Thurs, 5-Fri, 6-Satur, 0-Sun" << endl;
							cout << "\n" << setw(30) << "~Doctor~";
							cout << setw(30) << "~Specialty~";
							cout << setw(25) << "~Work from~";
							cout << setw(25) << "~To~";
							cout << setw(25) << "~Days~" << endl;
							cout << setw(30) << schedule[i].doctorName;
							cout << setw(30) << schedule[i].specialty;
							cout << setw(22) << schedule[i].startReception.hours << ':' << setw(2) << schedule[i].startReception.minutes;
							cout << setw(22) << schedule[i].endReception.hours << ':' << setw(2) << schedule[i].endReception.minutes;
							cout << setw(17) << schedule[i].day1 << ',' << setw(2) << schedule[i].day2 << ',' << setw(2) << schedule[i].day3 << endl;
						}
					}

					if (value == false)
					{
						string message = "Doctor with that name does not work in our hospital";
						RedColor(message);
					}

				}
				else if (num == 2)
				{
					vector<Schedule> schedule;
					schedule = user.CheckWorkSchedule();
					system("cls");
					cout << "1-Mon, 2-Tues, 3-Wed, 4-Thurs, 5-Fri, 6-Satur, 0-Sun" << endl;
					cout << "\n" << setw(30) << "~Doctor~";
					cout << setw(30) << "~Specialty~";
					cout << setw(25) << "~Work from~";
					cout << setw(25) << "~To~";
					cout << setw(25) << "~Days~" << endl;

					for (int i = 0; i < schedule.size(); i++)
					{
						cout << setw(30) << schedule[i].doctorName;
						cout << setw(30) << schedule[i].specialty;
						cout << setw(22) << schedule[i].startReception.hours << ':' << setw(2) << schedule[i].startReception.minutes;
						cout << setw(22) << schedule[i].endReception.hours << ':' << setw(2) << schedule[i].endReception.minutes;
						cout << setw(17) << schedule[i].day1 << ',' << setw(2) << schedule[i].day2 << ',' << setw(4) << schedule[i].day3 << endl;
					}
				}
				else
				{
					message = "Error number";
					RedColor(message);
				}
			}
			else if (number == "4")
			{
				bool value = false;
				string doctor_name;
				string client = "the full name of the doctor";
				doctor_name = CheckName(doctor_name, client);
				vector<Schedule> schedule;
				schedule = user.CheckWorkSchedule();
				for (int i = 0; i < schedule.size(); i++)
				{
					if (doctor_name == schedule[i].doctorName)
					{
						value = true;
						system("cls");
						cout << "1-Mon, 2-Tues, 3-Wed, 4-Thurs, 5-Fri, 6-Satur, 0-Sun" << endl;
						cout << "\n" << setw(30) << "~Doctor~";
						cout << setw(30) << "~Specialty~";
						cout << setw(25) << "~Work from~";
						cout << setw(25) << "~To~";
						cout << setw(25) << "~Days~" << endl;
						cout << setw(30) << schedule[i].doctorName;
						cout << setw(30) << schedule[i].specialty;
						cout << setw(22) << schedule[i].startReception.hours << ':' << setw(2) << schedule[i].startReception.minutes;
						cout << setw(22) << schedule[i].endReception.hours << ':' << setw(2) << schedule[i].endReception.minutes;
						cout << setw(19) << schedule[i].day1 << ',' << setw(2) << schedule[i].day2 << ',' << setw(2) << schedule[i].day3 << endl;

						cout << "\nTime already taken:\n";
						vector<Note> records;
						records = user.CheckRecords();
						for (int i = 0; i < records.size(); i++)
						{
							if (doctor_name == records[i].doctorName)
							{
								cout << setw(22) << "~Time~";
								cout << setw(22) << "~Days~" << endl;
								cout << setw(19) << records[i].meetTime.hours << "." << records[i].meetTime.minutes;
								cout << setw(15) << records[i].meetDay.day << "." << records[i].meetDay.mounth << "." << records[i].meetDay.year << endl;
							}
						}

						string data;
						int day;
						bool meetDay = false;
						while (meetDay == false)
						{
							cout << "\nEnter data of admission: For example - 10.05.2021\n";
							cin >> data;
							bool year_check = true;
							bool& year = year_check;
							day = CheckData(data, year);
							if (year == true && (day == schedule[i].day1 || day == schedule[i].day2 || day == schedule[i].day3))
							{
								meetDay = true;
								string time;
								int houre, minute;
								bool period = false;
								bool check = false;
								while (period == false)
								{
									cout << "Enter the time of admission with a difference of half an hour relative to the time already taken : For example - 10.05.2021\n";
									cin >> time;
									houre = stoi(time.substr(0, 2));
									minute = stoi(time.substr(3, 2));
									if (houre >= schedule[i].startReception.hours && houre < schedule[i].endReception.hours)
									{
										period = true;
										check = true;

										for (int i = 0; i < records.size(); i++)
										{
											if (doctor_name == records[i].doctorName && houre == records[i].meetTime.hours && (((records[i].meetTime.minutes == 0) && (minute < 30)) || ((records[i].meetTime.minutes == 30) && (minute != 0))))
											{
												period = false;
												cout << "This time is already taken. Please choose another time.\n";
											}
										}

										if (period == true)
										{
											user.MakeAppointment(doctor_name, time, data);
											message = "Record is recorded";
											GreenColor(message);
										}

									}
									if (check == false)
									{
										period = false;
										cout << "This Doctor don't work at this time. Please choose another time.\n";
									}
								}
							}
							else
							{
								cout << "This Doctor don't work at this day. Please choose another day.";
							}
						}
					}
				}

				if (value == false)
				{
					message = "Doctor with that name does not work in our hospital";
					RedColor(message);
				}
			}

			else if (number == "5")
			{
				vector<Note> records;
				bool value = false;
				records = user.CheckRecords();
				for (int i = 0; i < records.size(); i++)
				{
					if (_name == records[i].patientName)
					{
						value = true;
						message = "Here is your records:";
						GreenColor(message);
						cout << endl;
						cout << setw(35) << "~Doctor~";
						cout << setw(35) << "~Patient~";
						cout << setw(22) << "~Time~";
						cout << setw(22) << "~Days~" << endl;
						cout << setw(35) << records[i].doctorName;
						cout << setw(35) << records[i].patientName;
						cout << setw(19) << records[i].meetTime.hours << "." << records[i].meetTime.minutes;
						cout << setw(15) << records[i].meetDay.day << "." << records[i].meetDay.mounth << "." << records[i].meetDay.year << endl;
					}
				}
				if (value == false)
				{
					message = "You don't have an appointment yet";
					RedColor(message);
				}
			}
			else if (number == "0")
			{
				system("cls");
				message = "Good bye," + _name;
				GoldColor(message);
				exit(0);
			}
			else
			{
				message = "Error number";
				RedColor(message);
			}
		}
	}

void Menu::DoctorMenu(string name)
	{
		_name = name;
		Doctors user(_name);
		system("cls");
		message = "Hello," + _name;
		GoldColor(message);

		while (number != "0")
		{

			cout << "\nChoose what to do next\n";
			cout << "1-Check patient card\n";
			cout << "2-Write diagnose\n";
			cout << "3-Check if I have an appointments\n";
			cout << "0-Exit\n";
			cin >> number;
			system("cls");
			message = "Hello," + _name;
			GoldColor(message);;
			if (number == "1")
			{
				bool value = false;
				bool& found_card = value;
				string patient_name;
				string client = "the full name of the patient";
				patient_name = CheckName(patient_name, client);
				vector <Card> patient_card;
				patient_card = user.CheckCard(found_card, patient_name);
				if (found_card == true)
				{
					system("cls");
					message = "Here is patient card:";
					GreenColor(message);
					cout << setw(25) << "~Doctor~";
					cout << setw(25) << "~Diagnosis~";
					cout << setw(25) << "~Visit time~";
					cout << setw(25) << "~Day~" << endl;
					for (int i = 0; i < patient_card.size(); i++)
					{
						cout << setw(25) << patient_card[i].doctorName;
						cout << setw(25) << patient_card[i].diagnosis;
						cout << setw(22) << patient_card[i].meetTime.hours << ':' << setw(2) << patient_card[i].meetTime.minutes;
						cout << setw(17) << patient_card[i].meetDay.day << '.' << setw(2) << patient_card[i].meetDay.mounth << '.' << setw(4) << patient_card[i].meetDay.year << endl;
					}
				}
				else if (found_card == false)
				{
					message = "This patient does not have a card yet.";
					RedColor(message);
				}
			}
			else if (number == "2")
			{
				bool value = false;
				bool& found_card = value;
				string patient_name;
				string client = "the full name of the patient";
				patient_name = CheckName(patient_name, client);
				vector <Card> patient_card;
				patient_card = user.CheckCard(found_card, patient_name);
				if (found_card == true)
				{
					string diagnosis;
					string time;
					string data;
					cout << "Enter patient diagnose:\n";
					cin >> diagnosis;
					cout << "Enter time of admission: For example - 09.30\n";
					cin >> time;
					cout << "Enter data of admission: For example - 10.05.2021\n";
					cin >> data;
					user.WriteDiagnosis(patient_name, diagnosis, time, data);
					message = "Diagnosis recorded\n";
					GreenColor(message);
				}
				else if (found_card == false)
				{
					message = "Card not found.";
					RedColor(message);
					int value;
					cout << "Create new card for patient " + patient_name + "?\n1-Yes 2-No\n";
					cin >> value;
					if (value == 1)
					{
						user.CreateCard(patient_name);
						message = "Card for patient " + patient_name + " created";
						GreenColor(message);
						string diagnosis;
						string time;
						string data;
						cout << "Enter patient diagnose:\n";
						cin >> diagnosis;
						cout << "Enter time of admission: For example - 09.30\n";
						cin >> time;
						cout << "Enter data of admission: For example - 10.05.2021\n";
						cin >> data;
						user.WriteDiagnosis(patient_name, diagnosis, time, data);
						message = "Diagnosis recorded";
						GreenColor(message);
					}
					else
					{
						continue;
					}
				}
			}
			else if (number == "3")
			{
				vector<Note> records;
				bool value = false;
				records = user.CheckRecords();
				for (int i = 0; i < records.size(); i++)
				{
					if (_name == records[i].doctorName)
					{
						value = true;
						cout << endl;
						cout << setw(35) << "~Doctor~";
						cout << setw(35) << "~Patient~";
						cout << setw(22) << "~Time~";
						cout << setw(22) << "~Days~" << endl;
						cout << setw(35) << records[i].doctorName;
						cout << setw(35) << records[i].patientName;
						cout << setw(19) << records[i].meetTime.hours << "." << records[i].meetTime.minutes;
						cout << setw(15) << records[i].meetDay.day << "." << records[i].meetDay.mounth << "." << records[i].meetDay.year << endl;
					}
				}
				if (value == false)
				{
					message = "You don't have an appointment yet";
					RedColor(message);
				}
			}
			else if (number == "0")
			{
				system("cls");
				message = "Good bye," + _name;
				GoldColor(message);
				exit(0);
			}
			else
			{
				message = "Error number";
				RedColor(message);
			}
		}
	}

string Menu::CheckName(string name, string user)
	{
		bool value = false;
		int space = 0;
		while (value == false)
		{
			cout << "Enter " << user << " : For example - Petrenko Ivan Ivanovich" << endl;
			cin.ignore(32676, '\n');
			cin.clear();
			getline(cin, name);
			space = 0;
			if (name.size() != 0)
			{
				string help_name = name;
				size_t left = help_name.find_first_not_of(" ");
				size_t right = help_name.find_last_not_of(" ");
				name = help_name.substr(left, right - left + 1);

				for (int i = 0; i < name.size(); i++)
				{
					if (name[i] == ' ')
					{
						space++;
					}
				}
				if (space == 2)
				{
					value = true;
				}
				else
				{
					message = "Error name type";
					RedColor(message);
				}
			}
			else
			{
				message = "Error name type";
				RedColor(message);
			}
		}
		return name;
	}

int Menu::CheckData(string data, bool& year)
	{
		int d, m, y, d_i, m_i, y_i, ind;
		time_t now = time(0);
		tm* ltm = localtime(&now);

		d = stoi(data.substr(0, 2));
		m = stoi(data.substr(3, 2));
		y = stoi(data.substr(8, 2));

		if (y + 2000 < 1900 + ltm->tm_year || ((y + 2000) == 1900 + ltm->tm_year && m < 1 + ltm->tm_mon) || ((y + 2000) == 1900 + ltm->tm_year && m == 1 + ltm->tm_mon && d < ltm->tm_mday))
		{
			cout << "You can't make an appointment for day that has already been\n";
			year = false;
		}

		y_i = y / 12 + y % 12 + (y % 12) / 4;
		if (m == 5)
		{
			m_i = 0;
		}
		else if (m == 8)
		{
			m_i = 1;
		}
		else if (m == 2 || m == 3 || m == 11)
		{
			m_i = 2;
		}
		else if (m == 6)
		{
			m_i = 3;
		}
		else if (m == 9 || m == 12)
		{
			m_i = 4;
		}
		else if (m == 4 || m == 7)
		{
			m_i = 5;
		}
		else if (m == 1 || m == 10)
		{
			m_i = 6;
		}
		d_i = d;
		ind = (d_i + m_i + y_i) % 7;
		return ind;
	}

void Menu::GoldColor(string message)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		int color = 6; // Номер кольору
		SetConsoleTextAttribute(hConsole, color);

		cout << message << endl;

		color = 0xF; // Номер кольору
		SetConsoleTextAttribute(hConsole, color);
	}

void Menu::GreenColor(string message)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		int color = 2; // Номер кольору
		SetConsoleTextAttribute(hConsole, color);

		cout << message << endl;

		color = 0xF; // Номер кольору
		SetConsoleTextAttribute(hConsole, color);
	}

void Menu::RedColor(string message)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		int color = 4; // Номер кольору
		SetConsoleTextAttribute(hConsole, color);

		cout << message << endl;

		color = 0xF; // Номер кольору
		SetConsoleTextAttribute(hConsole, color);
	}

