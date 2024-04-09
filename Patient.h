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
class Date                    //������
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
	char diagnose[20];//���
	char advice[20]; //���
	char DS[20];     //ҽ��ǩ��


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
	} //������Ϣ��ʾ
	friend class PatientDataBase;
};
class PatientDataBase
{
	int nElem;//������Ϣ���е�Ԫ�ظ���
	int maxNum;//����¼
	MedicalRecord* MR;//ָ������Ϣ��ָ��
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
			cout << "��������ʧ��." << endl;
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
	}   //���캯������ʼ��������Ϣ����patien.txt�ļ������ݶ���MR[]��

	~PatientDataBase()
	{
		delete[maxNum] MR;
	}//��������
	void writetofile()
	{
		fstream out("Patient.txt", ios::out);
		if (!out)
		{
			cout << "����д��ʧ��." << endl;
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
			if (nElem == 0) cout << "�����ݿ�д!" << endl;
			else cout << "����д��ɹ�!" << endl;
			out.close();
		}
	}
	void clear() //ɾ�����в�����Ϣ
	{
		char a;
		cout << "�Ƿ�ɾ����������y/n?" << endl;
		cin >> a;
		if (a == 'y')
		{
			for (int i = 0; i <= nElem - 1; i++)
				strcpy((char*)(&MR[i]), "");
			nElem = 0;
			cout << "����գ�" << endl;
		}
	}
	void PatientAdd() //��Ӳ�����¼
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
		ofstream outPatient("Patient.txt", ios::ate | ios::in | ios::binary);//û�����ɣ������ļ�β׷��ios::app|
		if (!outPatient)
		{
			cerr << "File could not be opened." << endl;
			exit(EXIT_FAILURE);
		}
		if (maxNum == nElem) cout << "�Ѵﵽ����¼���޷��������!" << endl;
		else
		{
			cout << "������ID" << endl;
			cin >> ID;
			cout << "����������" << endl;
			cin >> first;
			cin >> last;
			cout << "�������Ա�" << endl;
			cin >> sex;
			cout << "����������" << endl;
			cin >> age;
			cout << "�������������" << endl;
			cout << "��:";
			cin >> a;
			cout << "��:";
			cin >> b;
			cout << "��:";
			cin >> c;

			cout << "���������" << endl;
			cin >> diagnose;
			cout << "�����뽨��" << endl;
			cin >> advice;
			cout << "������ҽʦ����" << endl;
			cin >> DS;
			MR[nElem] = MedicalRecord(ID, first, last, sex, age, a, b, c, diagnose, advice, DS);
			nElem++;
			cout << "��ӳɹ�" << endl;
		}
	}
	void PatientDelete()//ɾ��������Ϣ
	{
		char a;
		int j = getorder();
		if (j == -1)  cout << "����ʧ�ܣ��ò��˲�����" << endl;
		else
		{
			cout << "�Ƿ�ȷ��ɾ��y/n?" << endl;
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
				cout << "ɾ���ɹ�" << endl;
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
		if (i == -1) { cout << "����ʧ�ܣ��ò��˲�����" << endl; }
		else
		{
			cout << "����������" << endl;
			cin >> first >> last;
			cout << "�������Ա�" << endl;
			cin >> sexp;
			cout << "����������" << endl;
			cin >> agep;
			cout << "����������" << endl;
			cout << "��:";
			cin >> a;
			cout << "��:";
			cin >> b;
			cout << "��:";
			cin >> c;
			cout << "���������" << endl;
			cin >> diagnosep;
			cout << "�����뽨��" << endl;
			cin >> advicep;
			cout << "������ҽʦ����" << endl;
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

			cout << "�޸ĳɹ���" << endl;
		}
	}
	void queryID() //���ղ����Ų��ң�˳�����
	{
		int ID;
		cout << "������ID" << ends;
		cin >> ID;
		for (int i = 0; i <= nElem - 1; i++)
		{
			if (MR[i].ID == ID)
			{
				MR[i].disp(); break;
			}

			if (i == nElem)
			{
				cout << "����ʧ�ܣ��ò��˲�����" << endl;
			}
		}
	}
	void queryDS() //����ҽ��ǩ�����ң��۰����
	{
		char DS[20];
		cout << "������DS" << ends;
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
			cout << "���ҽ���" << endl;
		}
	}
	void disp() //������в�����Ϣ
	{
		if (nElem != 0)
		{
			for (int i = 0; i <= (nElem - 1); i++)
				MR[i].disp();
		}
		else
			cout << "û�в��˼�¼��" << endl;

	}


	int getorder()
	{
		int IDp;
		cout << "������ID" << ends;
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
	}//�ò���ID��ò���˳��

	char quit()
	{
		char a, b;
		cout << "�Ƿ��˳�y/n?" << endl;
		cin >> a;
		if (a == 'y')
		{
			cout << "�Ƿ�������ı�y/n?" << endl;
			cin >> b;
			if (b == 'y')
			{
				writetofile();
			}
			cout << "�ټ�����ӭ�ٴι���." << endl;
		}
		return (a);
	}//����0���˳�

};
#endif
#pragma once
