#pragma once
#include <string>

using namespace std;

struct Time {
    int hours;
    int minutes;
};

struct Date {
    int day;
    int mounth;
    int year;
};

struct Note
{
    string doctorName;
    string patientName;
    Time meetTime;
    Date meetDay;
};

struct Card
{
    string doctorName;
    string diagnosis;
    Time meetTime;
    Date meetDay;
};

struct Schedule
{
    string doctorName;
    string specialty;
    Time startReception;
    Time endReception;
    int day1;
    int day2;
    int day3;
};

