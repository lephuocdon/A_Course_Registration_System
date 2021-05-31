#include<iostream>
#include<fstream>
#include<cstring>
#include<time.h>
using namespace std;
struct Date
{
	int dd;
	int mm;
	int yy;
};
struct Session
{
	string day;			//Mon, Tue, Wed, Thu, Fri, Sat
	string period;		//S1, S2, S3, S4
};
struct CourseInfo
{
	string courseID;
	string courseName;
	string teacherName;
	int credits;
	int maxStudents = 50;
	Session lession1, lession2;			//A course has 2 lession
	CourseInfo* Next;
};
struct Staff
{
	string userName;
	string password;
	string staffName;
	int gender;
	Date dob;
	string qualif;
};
struct Student
{
	//Add by file
	int No;
	string studentID;
	string firstName;
	string lastName;
	string gender;
	Date dob;
	string socialID;

	//Student After Registration
	string _class;
	CourseInfo* _pHead;
};
struct Node
{
	Student info;
	Node* pNext;
};
struct List
{
	Node* pHead;
	Node* pTail;
};
struct Course
{
	CourseInfo info;
	List courseStudents;
};
struct Class
{
	string className;
	int numberStudents;
	List classStudents;
};