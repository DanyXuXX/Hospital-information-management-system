
#include<iostream>
#include<array>
#include<iomanip>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)


#ifndef DOCTOR_H
#define DOCTOR_H
class Doctor
{
private:
	int id, job, sex;
	char last[15];
	char first[10];
	int byear, bmonth, bday;
	int syear, smonth, sday;
public:
	Doctor(int i = 0, int s = 0, int j = 0, const char* b = " ", const char* c = " ", int by = 1900, int bm = 1,
		int bd = 1, int sy = 1920, int sm = 1, int sd = 1);
	bool leapyear(int);
	void setbirthdate(int, int);
	void setbday(int);
	void setstartdate(int, int);
	void setsday(int);
	void setfirst(const char*);
	void setlast(const char*);
	void setid(int);
	void setsex(int);
	void setjob(int);
	char* getfirst();
	char* getlast();
	int getid();
	int getsex();
	int getjob();
	int getbyear();
	int getbmonth();
	int getbday();
	int getsyear();
	int getsmonth();
	int getsday();
};
#endif



