#include <iostream>
#include<fstream>
#include<array>
#include<cstdlib>
#include<iomanip>
#include<vector>
#include<iterator>
#include<windows.h>
#include "Doctor.h"
#include"Patient.h"
using namespace std;
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

string HSaddress = " CODE county, C++ city";
string HSname = "DEBUG HOSPITAL";
int HSyear = 1983;
int HSmonth = 01;
int HSday = 01;//ҽԺ����

int id;
char first[11];
char last[16];
int sex;
int job;
int byear, bmonth, bday;
int syear, smonth, sday;
const int D[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };//days
vector<int>doc = { 0 };

bool checkdocid(int a)//���id�Ƿ����
{
	for (int i = 0; i < doc.size(); i++)
	{
		if (doc[i] == a)
			return true;//id���ڷ�����
	}
	return false;
}
void inputid(int a)
{
	for (int i = 0; i < doc.size(); i++)
	{
		if (doc[i] == 0)//��0Ԫ���滻����ʡ�ռ�
		{
			doc[i] = a;
			return;
		}
	}
	doc.push_back(a);//��ǰ��һֱû�п�λʱ�ٽ��в�λ
	return;
}
bool leapyear(int t)//�ж�������
{
	if (t % 400 == 0 || (t % 100 != 0 && t % 4 == 0))return true;
	else return false;
}

void DoctorAdd()
{
	cout << "Please enter a new ID number: " << endl;
	cin >> id;
	while (id == 0 || checkdocid(id))
	{
		cout << "Wrong input. Please enter the RIGHT number: ";
		cin >> id;
	}

	if (id)
	{
		inputid(id);
	}//ȷ������id��Ч���ŵ�doc��

	Doctor d;
	ofstream outHospital("Hospital.txt", ios::ate | ios::in | ios::binary);
	if (!outHospital)
	{
		cerr << "File could not be opened." << endl;
		exit(EXIT_FAILURE);
	}
	cout << "Enter the firstname,lastname: " << endl;
	cin >> first >> last;

	cout << "Enter the year of birthday (in NUMBERS): ";//��������
	cin >> byear;
	while (!(byear >= 1900 && byear <= 2010))
	{
		cout << "Year is out of range for current month and year. Input the right one:\n";
		cin >> byear;
	}
	cout << "Enter the month of birthday (in NUMBERS): ";
	cin >> bmonth;
	while (!(bmonth >= 1 && bmonth <= 12))
	{
		cout << "Month is out of range for current month and year. Input the right one:\n";
		cin >> bmonth;
	}
	cout << "Enter the day of birthday (in NUMBERS): ";
	cin >> bday;
	while (!(bmonth == 2 && leapyear(byear) && bday >= 1 && bday <= 29) && !(bday >= 1 && bday <= D[bmonth]))//��2�»�����
	{
		cout << "Day is out of range for current month and year. Input the right one: \n";
		cin >> bday;
	}
	cout << "Enter the year of job starting date(in NUMBERS): ";//������ְʱ��
	cin >> syear;
	while (!(syear >= 1920 && syear <= 2019))
	{
		cout << "Year is out of range for current month and year. Input the right one:\n";
		cin >> syear;
	}
	cout << "Enter the month of job starting date (in NUMBERS): ";
	cin >> smonth;
	while (!(smonth >= 1 && smonth <= 12))
	{
		cout << "Month is out of range for current month and year. Input the right one: \n";
		cin >> smonth;
	}
	cout << "Enter the day of job starting date(in NUMBERS): ";
	cin >> sday;
	while (!(smonth == 2 && leapyear(syear) && sday >= 1 && sday <= 29) && !(sday >= 1 && sday <= D[bmonth]))
	{
		cout << "Day is out of range for current month and year. Input the right one: \n";
		cin >> sday;
	}

	cout << "Sex? (1 for male, 2 for female): ";
	cin >> sex;
	while (sex != 1 && sex != 2)
	{
		cout << "Wrong input. Please enter the RIGHT number: ";
		cin >> sex;
	}
	cout << "Job? �����ڿ�������11;   �����ڿ�������12;   ���ڿ�������13;  ��Ѫ���ڿ�������14\n"
		<< "    ��ͨ���������21;   �����������22;   �������������23;  �����������24\n"
		<< "    ���Ǻ��������31;   �ۿ�������32;       ��ǻ��������33\n"
		<< "    ��ҽ������������41; ��ҽ��Ħ��������42; ��ҽȫ��������43\n";
	cin >> job;
	while (job != 11 && job != 12 && job != 13 && job != 14 && job != 21 && job != 22 && job != 23 && job != 24
		&& job != 31 && job != 32 && job != 33 && job != 41 && job != 42 && job != 43)
	{
		cout << "Wrong input. Please enter the RIGHT number: ";
		cin >> job;
	}//������Ϣ������
	d.setbirthdate(bmonth, byear);
	d.setbday(bday);
	d.setstartdate(smonth, syear);
	d.setsday(sday);
	d.setfirst(first);
	d.setlast(last);
	d.setid(id);
	d.setsex(sex);
	d.setjob(job);
	outHospital.seekp((d.getid() - 1) * sizeof(Doctor));
	outHospital.write(reinterpret_cast<const char*>(&d), sizeof(Doctor));
	outHospital.close();
	cout << "Add finished.\n" << endl;
}
void DoctorChange()
{
	int changeid;
	Doctor d;
	int choice;
	cout << "Enter the ID to change(0 to end changing process):  \n";
	cin >> changeid;
	if (changeid == 0)return;
	if (changeid != 0)
	{
		while (!checkdocid(changeid))//ȷ��ID������ȷ,id������ʱ��������
		{
			cout << "Wrong input. Please enter the RIGHT number: ";
			cin >> changeid;
		}
		fstream inoutdoctor("Hospital.txt", ios::in | ios::ate | ios::out | ios::binary);//ָ�붨λ�ļ�β
		if (!inoutdoctor)
		{
			cerr << "File could not be opened." << endl;
			exit(EXIT_FAILURE);
		}
		cout << "Which information do u wanna change?\n"
			<< " Enter 1 for first name; Enter 2 for last name; Enter 3 for job(0 TO END):  " << endl;

		cin >> choice;
		while (choice != 1 && choice != 2 && choice != 3 && choice != 0)
		{
			cout << "wrong input. enter the right number: ";
			cin >> choice;
		}
		switch (choice)
		{
		case 0:
		{
			changeid = 0;
			cout << "CANCELLED\n";
			break; }
		case 1://first name
		{
			Doctor p;
			inoutdoctor.seekg((changeid - 1) * sizeof(Doctor));
			inoutdoctor.read(reinterpret_cast<char*>(&d), sizeof(Doctor));
			cout << "Input new first name: ";
			cin >> first;
			p.setfirst(first);
			p.setlast(d.getlast());
			p.setbirthdate(d.getbmonth(), d.getbyear());
			p.setbday(d.getbday());
			p.setstartdate(d.getsmonth(), d.getsyear());
			p.setsday(d.getsday());
			p.setid(changeid);
			p.setsex(d.getsex());
			p.setjob(d.getjob());
			inoutdoctor.seekp((changeid - 1) * sizeof(Doctor));
			inoutdoctor.write(reinterpret_cast<const char*>(&p), sizeof(Doctor)); inoutdoctor.close();
			//cout << "which information do u wanna change?(0 to end changing process)\n"
			//	<< "1:firstname; 2:lastname; 3:job;(0 TO END)" << endl;
			//cin >> choice;
			break;
		}
		case 2://last name
		{
			Doctor q;
			inoutdoctor.seekg((changeid - 1) * sizeof(Doctor));
			inoutdoctor.read(reinterpret_cast<char*>(&d), sizeof(Doctor));
			cout << "Input new last name: ";
			cin >> last;
			q.setlast(last);
			q.setfirst(d.getfirst());
			q.setbirthdate(d.getbmonth(), d.getbyear());
			q.setbday(d.getbday());
			q.setstartdate(d.getsmonth(), d.getsyear());
			q.setsday(d.getsday());
			q.setid(changeid);
			q.setsex(d.getsex());
			q.setjob(d.getjob());
			inoutdoctor.seekp((changeid - 1) * sizeof(Doctor));
			inoutdoctor.write(reinterpret_cast<const char*>(&q), sizeof(Doctor)); inoutdoctor.close();
			//cout << "which information do u wanna change?(0 to end changing process)\n"
			//<< "1:firstname; 2:lastname; 3:job;(0 TO END)" << endl;
			//cin >> choice;
			break;
		}
		case 3://job
		{
			Doctor r;
			inoutdoctor.seekg((changeid - 1) * sizeof(Doctor));
			inoutdoctor.read(reinterpret_cast<char*>(&d), sizeof(Doctor));
			cout << "Input new job number:\n"
				<< "�����ڿ�������11;   �����ڿ�������12;   ���ڿ�������13;  ��Ѫ���ڿ�������14\n"
				<< "��ͨ���������21;   �����������22;   �������������23;  �����������24\n"
				<< "���Ǻ��������31;   �ۿ�������32;       ��ǻ��������33\n"
				<< "��ҽ������������41; ��ҽ��Ħ��������42; ��ҽȫ��������43\n";
			cin >> job;
			while (job != 11 && job != 12 && job != 13 && job != 14 && job != 21 && job != 22 && job != 23 && job != 24
				&& job != 31 && job != 32 && job != 33 && job != 41 && job != 42 && job != 43)
			{
				cout << "Wrong input. Please enter the RIGHT number: ";
				cin >> job;
			}
			r.setfirst(d.getfirst());
			r.setlast(d.getlast());
			r.setbirthdate(d.getbmonth(), d.getbyear());
			r.setbday(d.getbday());
			r.setstartdate(d.getsmonth(), d.getsyear());
			r.setsday(d.getsday());
			r.setid(changeid);
			r.setsex(d.getsex());
			r.setjob(job);
			inoutdoctor.seekp((changeid - 1) * sizeof(Doctor));
			inoutdoctor.write(reinterpret_cast<const char*>(&r), sizeof(Doctor)); inoutdoctor.close();
			//cout << "which information do u wanna change?(0 to end changing process)\n"
			//<< "1:firstname; 2:lastname; 3:job(0 TO END)" << endl;
			//cin >> choice;
			break;
		}
		default: break;
		}
	}
	cout << "CHANGED\n\n";

	return;
}
void DoctorDelete()
{
	int deletenumber;
	Doctor d;
	Doctor blank;
	cout << "Enter the ID number to delete: ";
	cin >> deletenumber;
	while (!checkdocid(deletenumber) || deletenumber == 0)
	{
		cout << "Wrong input. Please enter the RIGHT number: ";
		cin >> deletenumber;
	}
	if (checkdocid(deletenumber))//��check��������Ӧ����ɾȥ
	{
		for (int i = 0; i < doc.size(); i++)
		{
			if (doc[i] == deletenumber)doc[i] = 0;
		}
	}
	fstream inoutDoctor("Hospital.txt", ios::in | ios::ate | ios::out | ios::binary);
	if (!inoutDoctor)
	{
		cerr << "File could not be opened." << endl;
		exit(EXIT_FAILURE);
	}
	inoutDoctor.seekg((deletenumber - 1) * sizeof(Doctor));
	inoutDoctor.read(reinterpret_cast<char*>(&d), sizeof(Doctor));
	blank.setfirst("DELETED");
	blank.setlast("DELETED");
	inoutDoctor.seekp((deletenumber - 1) * sizeof(Doctor));
	inoutDoctor.write(reinterpret_cast<const char*>(&blank), sizeof(Doctor));
	inoutDoctor.close();
	cout << "DELETED\n\n";
}
void DoctorPrint()
{
	Doctor m;
	ifstream inhospital("Hospital.txt", ios::in | ios::binary);
	if (!inhospital)
	{
		cerr << "File could not be opened." << endl;
		exit(EXIT_FAILURE);
	}
	//cout << "****************" << HSname << "**************" << endl;
	//cout << "                                     ----" << "Located in " << HSaddress << endl;
	//cout << "The hospital was founded in " << HSyear << "--" << HSmonth << "--" << HSday << endl;
	cout << "\n------------Basic information of all Doctors-------------\n" << left << setw(10) << "ID"
		<< setw(11) << "First Name" << setw(16) << "Last Name"
		<< setw(9) << "Sex" << setw(12) << "Job" << setw(6) << right << fixed << showpoint << "Birthday(Y--M--D)"
		<< setw(8) << "   Hire Date(Y--M--D)" << endl;

	inhospital.read(reinterpret_cast<char*>(&m), sizeof(Doctor));
	while (inhospital && !inhospital.eof())
	{
		if (m.getid() != 0)
		{
			cout << left << setw(10) << m.getid() << setw(11) << m.getfirst()
				<< setw(16) << m.getlast() << setw(9) << (m.getsex() == 1 ? "Male" : "Female") << setw(12);
			switch (m.getjob())
			{
			case 11:
			{
				cout << "�����ڿ�";
				break;
			}
			case 12:
			{
				cout << "�����ڿ�";
				break;
			}
			case 13:
			{
				cout << "���ڿ�";
				break;
			}
			case 14:
			{
				cout << "��Ѫ���ڿ�";
				break;
			}
			case 21:
			{
				cout << "��ͨ���";
				break;
			}
			case 22:
			{
				cout << "�����";
				break;
			}
			case 23:
			{
				cout << "�������";
				break;
			}
			case 24:
			{
				cout << "�����";
				break;
			}
			case 31:
			{
				cout << "���Ǻ��";
				break;
			}
			case 32:
			{
				cout << "�ۿ�";
				break;
			}
			case 33:
			{
				cout << " ��ǻ��";
				break;
			}
			case 41:
			{
				cout << "��ҽ������";
				break;
			}
			case 42:
			{
				cout << "��ҽ��Ħ��";
				break;
			}
			case 43:
			{
				cout << "��ҽȫ��";
				break;
			}
			default:break;
			}
			cout << setw(6) << right << fixed
				<< showpoint << m.getbyear() << "--" << m.getbmonth() << "--" << m.getbday()
				<< setw(15) << m.getsyear() << "--" << m.getsmonth() << "--" << m.getsday() << endl;

		}
		inhospital.read(reinterpret_cast<char*>(&m), sizeof(Doctor));
	}
	inhospital.close();
}
void cleandocdata()
{
	cout << "Input the code: ";
	int code;
	cin >> code;
	if (code != 111111)
	{
		cout << "U don't have the right.\n";
		return;
	}
	if (code == 111111)
	{
		fstream inoutDoctor("Hospital.txt", ios::out | ios::binary);
		if (!inoutDoctor)
		{
			cerr << "File could not be opened." << endl;
			exit(EXIT_FAILURE);
		}
		inoutDoctor.close();
		cout << "ALL data is DELETED.\n\n";
	}
}
void setVectordoc()//��ÿ�δ��Ժ���ļ�����id����doc
{
	ifstream inDoctor("Hospital.txt", ios::in | ios::binary);
	if (!inDoctor)
	{
		ofstream doctor("Hospital.txt");//����Ĵ��룬�����ж��ļ��Ƿ���ڣ��������򴴽�
	}
	Doctor m;
	inDoctor.read(reinterpret_cast<char*>(&m), sizeof(Doctor));
	while (inDoctor && !inDoctor.eof())
	{
		if (m.getid() != 0)
		{
			doc.push_back(m.getid());
			sort(doc.begin(), doc.end());//ɾ��doc�е��ظ�Ԫ��
			vector<int>::iterator ite = unique(doc.begin(), doc.end());
			doc.erase(ite, doc.end());
		}
		inDoctor.read(reinterpret_cast<char*>(&m), sizeof(Doctor));
	}
}

int main()
{
	int n = 0;
	cout << "������봦��ҽ������Ϣ��������1.\n" << "������봦���ߵ���Ϣ��������2��" << endl;
	cin >> n;
	if (n == 1)
	{
		setVectordoc();

		cout << "\n\n\n\n\n                       " << HSname << endl;
		cout << "                                                     ----" << "Located in " << HSaddress << endl;
		cout << "The hospital was founded in " << HSyear << "--" << HSmonth << "--" << HSday << endl;
		cout << "\t\t ��**��** Welcome to the Hospital Information Management System **��**��" << endl;
		cout << "\n";
		cout << "\t\t              ��********��**********��***********��********��\n";
		cout << "\t\t              ��                                           ��\n";
		cout << "\t\t              ��                                           ��\n";
		cout << "\t\t              ��     1.Add                 2.Change        ��\n";
		cout << "\t\t              ��     3.Delete              4.Print         ��\n";
		cout << "\t\t              ��                                           ��\n";
		cout << "\t\t              ��                                           ��\n";
		cout << "\t\t              �������**********��***********�������\n";

		int choose = 0;
		cin >> choose;
		system("cls");
		while (choose != -1)
		{
			switch (choose)
			{
			case 1:
			{
				DoctorAdd(); break;
			}
			case 2:
			{
				DoctorChange(); break;
			}
			case 3:
			{
				DoctorDelete(); break;
			}
			case 4:
			{
				DoctorPrint(); break;
			}
			case 5:
			{
				cleandocdata(); break;//
			}
			default: break;
			}
			cout << endl << endl << endl;
			cout << "\t\t ��**��** Welcome to the Hospital Information Management System **��**��" << endl;
			cout << "\t\t            ��********��**********��***********��********��\n";
			cout << "\t\t            ��                                           ��\n";
			cout << "\t\t            ��                                           ��\n";
			cout << "\t\t            ��     1.Add                 2.Change        ��\n";
			cout << "\t\t            ��     3.Delete              4.Print         ��\n";
			cout << "\t\t            ��              5.clean data                 ��\n";
			cout << "\t\t            ��                                           ��\n";
			cout << "\t\t            �������**********��***********�������\n";
			cin >> choose;
			system("cls");
		}
		return 0;
		system("pause");
	}
	else
	{
		PatientDataBase a;
		int n, q;
		char s;
		for (;;)
		{
			system("cls");

			cout << "\n\n\n\n\n                       " << HSname << endl;
			cout << "                                                     ----" << "Located in " << HSaddress << endl;
			cout << "The hospital was founded in " << HSyear << "--" << HSmonth << "--" << HSday << endl;
			cout << "\t\t ��**��** Welcome to the Hospital Information Management System **��**��" << endl;
			cout << "\t\t            ��********��**********��***********��********��\n";
			cout << "                     1  ɾ�����в�����Ϣ       " << endl;
			cout << "                     2  ��Ӳ�����¼           " << endl;
			cout << "                     3  ����ɾ��ָ��������Ϣ   " << endl;
			cout << "                     4  �����޸�ָ��������Ϣ   " << endl;
			cout << "                     5  ����ָ��������Ϣ       " << endl;
			cout << "                     6  ��ʾ������Ϣ           " << endl;
			cout << "                     7  ����������Ϣ           " << endl;
			cout << "                     0  �˳�����               " << endl;
			cout << "\t\t            �������**********��***********�������\n";

			cin >> n;
			switch (n)
			{
			case 1:a.clear();
				system("pause"); break;
			case 2:a.PatientAdd();
				system("pause");
				break;
			case 3:a.PatientDelete();
				system("pause");
				break;
			case 4:a.PatientChange();
				system("pause");
				break;
			case 5:cout << "��ѡ���ѯ��ʽ(0:ID,1:ҽ��ǩ��)" << endl;
				cin >> q;
				if (q)
					a.queryDS();
				else
					a.queryID();
				system("pause");
				break;
			case 6:a.disp();
				system("pause"); break;
			case 7:a.writetofile();
				system("pause"); break;
			case 0:if (a.quit() != 'y')
				continue;
				  else break;
			}
			if (n == 0) break;
		}
		cout << "��������˳�����ллʹ��" << endl;
		a.~PatientDataBase();
		exit(0);
	}
}
