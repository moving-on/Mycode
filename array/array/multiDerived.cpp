#include<iostream>
#include<string>
using namespace std;

class CEmployee
{
private:
	string name;
	int age;
	char gender;
public:
	CEmployee()
	{
		cout << "CEmployee constructor" << endl;
	}
	void PrintBasicInfo()
	{
		cout << "name:" << name << endl;
		cout << "age:" << age << endl;
		cout << "gender:" << gender << endl;
	}
	void SetBasicInfo(const string &name_, int age_, int gender_)
	{
		name = name_;
		age = age_;
		gender = gender_;
	}
};

class CSalesman :virtual public CEmployee
{
protected:
	int salesVolumn;
public:
	CSalesman(){ cout << "CSalesman constructor" << endl; }
};

class CManager :virtual public CEmployee
{
protected:
	int totalSubordinates;
public:
	CManager(){ cout << "CManager constructor" << endl; }
};

class CSaleManager :public CSalesman, public CManager
{
public:
	CSaleManager(){ cout << "CSaleManager constructor" << endl; }
	void SetInfo(int sv, int sn)
	{
		salesVolumn = sv;
		totalSubordinates = sn;
	}
	void PrintInfo()
	{
		PrintBasicInfo();
		cout << "Sales Volume" << salesVolumn<<endl;
		cout << "Total Subordinates" << totalSubordinates<<endl;
	}
};

int main()
{
	CSaleManager sm;
	sm.SetBasicInfo("Tom",24,'M');
	sm.SetInfo(10000, 20);
	sm.PrintInfo();
}