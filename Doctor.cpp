#include<iostream>
#include<array>
#include<string>
#include<ctime>
#include"Doctor.h"
using namespace std;
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)



const int D[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };//days
Doctor::Doctor(int i, int s, int j, const char* b, const char* c, int by, int bm,
	int bd, int sy, int sm, int sd)//constructor
{
	setbirthdate(bm, by);
	setbday(bd);
	setstartdate(sm, sy);
	setsday(sd);
	setfirst(b);
	setlast(c);
	setid(i);
	setsex(s);
	setjob(j);
}
bool Doctor::leapyear(int t)//判断是闰年
{
	if (t % 400 == 0 || (t % 100 != 0 && t % 4 == 0))return true;
	else return false;
}

void Doctor::setbirthdate(int a, int c)
{
	if (a >= 1 && a <= 12)bmonth = a;
	else cout << "months must be 1-12\n";
	if (c >= 1900 && c <= 2100)byear = c;
	else cout << "years must be >=1900 and <=2100\n";

}
void  Doctor::setbday(int b)
{
	if ((bmonth == 2 && leapyear(byear) && b >= 1 && b <= 29) || (b >= 1 && b <= D[bmonth]))bday = b;
	else cout << "days is out of range for current month and year\n";

}
void  Doctor::setstartdate(int a, int c)
{
	if (a >= 1 && a <= 12)smonth = a;
	else cout << "months must be 1-12\n";
	if (c >= 1900 && c <= 2100)syear = c;
	else cout << "years must be >=1900 and <=2100\n";

}
void  Doctor::setsday(int b)
{
	if ((smonth == 2 && leapyear(syear) && b >= 1 && b <= 29) || (b >= 1 && b <= D[smonth]))sday = b;
	else cout << "days is out of range for current month and year\n";

}
void  Doctor::setfirst(const char* a) { strcpy(first, a); }//把a的地址赋值给first的首地址
void Doctor::setlast(const char* a) { strcpy(last, a); }
void Doctor::setid(int a) { id = a; }
void Doctor::setsex(int s)
{
	sex = s;
}
void Doctor::setjob(int a) { job = a; }

char* Doctor::getfirst() { return first; }
char* Doctor::getlast() { return last; }
int Doctor::getid() { return id; }
int Doctor::getsex() { return sex; }
int Doctor::getbyear() { return byear; }
int Doctor::getbmonth() { return bmonth; }
int Doctor::getbday() { return bday; }
int Doctor::getsyear() { return syear; }
int Doctor::getsmonth() { return smonth; }
int Doctor::getsday() { return sday; }
int Doctor::getjob() { return job; }
