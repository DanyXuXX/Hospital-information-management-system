#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#ifndef PATIENT_H
#define PATIENT_H
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
using namespace std;
class Date                    //日期类
{
	int year;
	int month;
	int day;
public:
	Date(int a = 2015, int b = 5, int c = 20)
	{
		year = a;
		month = b;
		day = c;
	}
	int getyear() { return year; }
	int getmonth() { return month; }
	int getday() { return day; }
	int setyear(int y) { year = y; }
	int setmonth(int m) { month = m; }
	int setday(int d) { day = d; }
	friend class PatientDataBase;
};
class MedicalRecord
{
private:
	int ID;
	char last[15];
	char first[10];
	char sex[5];
	int age;
	Date date;
	char diagnose[20];//诊断
	char advice[20]; //意见
	char DS[20];     //医生签名


public:
	MedicalRecord(int IDp = 0, const char* lastp = "", const char* firstp = "", const char* sexp = "", int agep = 0, int a = 2015, int b = 5, int c = 21, const char* MHp = "",
		const char* diagnosep = "", const char* advicep = "", const char* DSp = "")
	{
		date = Date(a, b, c);
		ID = IDp;
		strcpy(first, firstp);
		strcpy(last, lastp);
		strcpy(sex, sexp);
		age = agep;
		strcpy(diagnose, diagnosep);
		strcpy(advice, advicep);
		strcpy(DS, DSp);


	}
	int getID() { return ID; }
	char* getlast() { return last; }
	char* getfirst() { return first; }
	char* getsex() { return sex; }
	int getage() { return age; }
	Date* getdate() { return &date; }
	char* getdiagnose() { return diagnose; }
	char* getadvice() { return advice; }
	char* getDS() { return DS; }
	void setID(int IDp) { ID = IDp; }
	void setfirst(const char* a)
	{
		strcpy(first, a);
	}
	void setlast(const char* a)
	{
		strcpy(last, a);
	}
	void setsex(const char* sexp)
	{
		strcpy(sex, sexp);
	}
	void setage(int agep)
	{
		age = agep;
	}
	void setdate(Date datep)
	{
		date = datep;
	}
	void setdiagnose(char* diagnosep)
	{
		strcpy(diagnose, diagnosep);
	}
	void setadvice(char* advicep)
	{
		strcpy(advice, advicep);
	}
	void setDS(char* DSp)
	{
		strcpy(DS, DSp);
	}

	void disp()
	{
		cout << "********************************************************************************" << endl;
		cout << "ID:" << ID << endl << "firstname:" << first << setw(10) << "lastname" << last << endl << "sex:" << sex << endl;
		cout << "age:" << age << endl << "date:" << date.getyear() << "/" << date.getmonth() << "/" << date.getday() << endl;
		cout << "DS:" << DS << endl;
		cout << "********************************************************************************" << endl;
	} //病历信息显示
	friend class PatientDataBase;
};
class PatientDataBase
{
	int nElem;//病历信息表中的元素个数
	int maxNum;//最多纪录
	MedicalRecord* MR;//指向病历信息的指针
public:
	PatientDataBase(int n = 15)
	{
		maxNum = n;
		if (n)
			MR = new MedicalRecord[n];
		else
			MR = 0;
		fstream in("patient.txt", ios::in | ios::binary);
		if (!in)
		{
			cout << "病例加载失败." << endl;
			exit(1);
		}
		int i = 0;
		char meanless[200];
		in.getline(meanless, 200);
		while (!in.eof())
		{
			in >> MR[i].ID >> MR[i].first >> MR[i].last >> MR[i].sex >> MR[i].age >> MR[i].date.year >> MR[i].date.month;
			in >> MR[i].date.day >> MR[i].diagnose >> MR[i].advice >> MR[i].DS;
			i++;
		}
		in.close();
		nElem = i;
	}   //构造函数，初始化病历信息表，将patien.txt文件中数据读到MR[]中

	~PatientDataBase()
	{
		delete[maxNum] MR;
	}//析构函数
	void writetofile()
	{
		fstream out("Patient.txt", ios::out);
		if (!out)
		{
			cout << "病例写入失败." << endl;
			exit(2);
		}
		else {
			out << "ID       lastname    firstname        sex  age    date             diagnose            advice              DS              ";
			for (int i = 0; i < nElem; i++)
			{
				out << endl;
				out << setiosflags(ios::left) << setw(10) << MR[i].ID;
				out << setiosflags(ios::left) << setw(20) << MR[i].first;
				out << setiosflags(ios::left) << setw(20) << MR[i].last;
				out << setiosflags(ios::left) << setw(5) << MR[i].sex;
				out << setiosflags(ios::left) << setw(5) << MR[i].age;
				out << setiosflags(ios::left) << setw(5) << MR[i].date.year << setiosflags(ios::left) << setw(3) << MR[i].date.month << setiosflags(ios::left) << setw(7) << MR[i].date.day;
				out << setiosflags(ios::left) << setw(10) << MR[i].diagnose;
				out << setiosflags(ios::left) << setw(20) << MR[i].advice;
				out << setiosflags(ios::left) << setw(20) << MR[i].DS;

			}
			if (nElem == 0) cout << "无数据可写!" << endl;
			else cout << "数据写入成功!" << endl;
			out.close();
		}
	}
	void clear() //删除所有病历信息
	{
		char a;
		cout << "是否删除所有数据y/n?" << endl;
		cin >> a;
		if (a == 'y')
		{
			for (int i = 0; i <= nElem - 1; i++)
				strcpy((char*)(&MR[i]), "");
			nElem = 0;
			cout << "已清空！" << endl;
		}
	}
	void PatientAdd() //添加病历记录
	{
		int ID;
		char last[15];
		char first[10];
		char sex[5];
		int age;
		int a, b, c;
		char diagnose[20];
		char advice[20];
		char DS[20];
		ofstream outPatient("Patient.txt", ios::ate | ios::in | ios::binary);//没有生成，有在文件尾追加ios::app|
		if (!outPatient)
		{
			cerr << "File could not be opened." << endl;
			exit(EXIT_FAILURE);
		}
		if (maxNum == nElem) cout << "已达到最大记录数无法继续添加!" << endl;
		else
		{
			cout << "请输入ID" << endl;
			cin >> ID;
			cout << "请输入姓名" << endl;
			cin >> first;
			cin >> last;
			cout << "请输入性别" << endl;
			cin >> sex;
			cout << "请输入年龄" << endl;
			cin >> age;
			cout << "请输入就诊日期" << endl;
			cout << "年:";
			cin >> a;
			cout << "月:";
			cin >> b;
			cout << "日:";
			cin >> c;

			cout << "请输入诊断" << endl;
			cin >> diagnose;
			cout << "请输入建议" << endl;
			cin >> advice;
			cout << "请输入医师姓名" << endl;
			cin >> DS;
			MR[nElem] = MedicalRecord(ID, first, last, sex, age, a, b, c, diagnose, advice, DS);
			nElem++;
			cout << "添加成功" << endl;
		}
	}
	void PatientDelete()//删除病历信息
	{
		char a;
		int j = getorder();
		if (j == -1)  cout << "查找失败，该病人不存在" << endl;
		else
		{
			cout << "是否确定删除y/n?" << endl;
			cin >> a;
			if (a == 'y')
			{
				for (; j < nElem; j++)
				{
					MR[j].ID = MR[j + 1].ID;
					strcpy(MR[j].first, MR[j + 1].first);
					strcpy(MR[j].last, MR[j + 1].last);
					strcpy(MR[j].sex, MR[j + 1].sex);
					MR[j].age = MR[j + 1].age;
					MR[j].date = MR[j + 1].date;
					strcpy(MR[j].diagnose, MR[j + 1].diagnose);
					strcpy(MR[j].advice, MR[j + 1].advice);
					strcpy(MR[j].DS, MR[j + 1].DS);
				}
				cout << "删除成功" << endl;
				nElem -= 1;
			}
		}
	}
	void PatientChange()
	{
		char last[15];
		char first[10];
		char sexp[5];
		int agep;
		int a, b, c;
		char diagnosep[20];
		char advicep[20];
		char DSp[20];
		int i = getorder();
		if (i == -1) { cout << "查找失败，该病人不存在" << endl; }
		else
		{
			cout << "请输入姓名" << endl;
			cin >> first >> last;
			cout << "请输入性别" << endl;
			cin >> sexp;
			cout << "请输入年龄" << endl;
			cin >> agep;
			cout << "请输入日期" << endl;
			cout << "年:";
			cin >> a;
			cout << "月:";
			cin >> b;
			cout << "日:";
			cin >> c;
			cout << "请输入诊断" << endl;
			cin >> diagnosep;
			cout << "请输入建议" << endl;
			cin >> advicep;
			cout << "请输入医师姓名" << endl;
			cin >> DSp;
			MR[i].setfirst(first);
			MR[i].setlast(last);
			MR[i].setsex(sexp);
			MR[i].setage(agep);
			Date datep(a, b, c);
			MR[i].setdate(datep);
			MR[i].setdiagnose(diagnosep);
			MR[i].setadvice(advicep);
			MR[i].setDS(DSp);

			cout << "修改成功。" << endl;
		}
	}
	void queryID() //按照病历号查找，顺序查找
	{
		int ID;
		cout << "请输入ID" << ends;
		cin >> ID;
		for (int i = 0; i <= nElem - 1; i++)
		{
			if (MR[i].ID == ID)
			{
				MR[i].disp(); break;
			}

			if (i == nElem)
			{
				cout << "查找失败，该病人不存在" << endl;
			}
		}
	}
	void queryDS() //按照医生签名查找，折半查找
	{
		char DS[20];
		cout << "请输入DS" << ends;
		cin >> DS;
		int low = 0, mid, up = nElem - 1;
		while (low <= up)
		{
			mid = (low + up) / 2;
			if (strcmp(MR[mid].DS, DS) == 0)
			{
				MR[mid].disp(); low += 1;
			}
			else if (strcmp(MR[mid].DS, DS) == 1)
				up = mid - 1;
			else
				low = mid + 1;
		}
		if (low > up)
		{
			cout << "查找结束" << endl;
		}
	}
	void disp() //输出所有病历信息
	{
		if (nElem != 0)
		{
			for (int i = 0; i <= (nElem - 1); i++)
				MR[i].disp();
		}
		else
			cout << "没有病人记录！" << endl;

	}


	int getorder()
	{
		int IDp;
		cout << "请输入ID" << ends;
		cin >> IDp;
		int i = 0;
		while (i <= nElem)
		{
			if (MR[i].ID == IDp)
				break;
			i++;
		}
		if (i > nElem)
			return (-1);
		else
			return (i);
	}//用病人ID获得病人顺序

	char quit()
	{
		char a, b;
		cout << "是否退出y/n?" << endl;
		cin >> a;
		if (a == 'y')
		{
			cout << "是否输出成文本y/n?" << endl;
			cin >> b;
			if (b == 'y')
			{
				writetofile();
			}
			cout << "再见，欢迎再次光临." << endl;
		}
		return (a);
	}//功能0，退出

};
#endif
#pragma once
