#include<iostream>
#include<fstream>
#include<cstring>
#include<iomanip>
#include<string>
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
struct Mark
{
	double midtermMark;
	double finalMark;
	double otherMark;
	//Total Mark, GPA will be calculated by program (Code)
};
struct CourseInfo
{
	string courseID;
	string courseName;
	string teacherName;
	int credits;
	int maxStudents = 50;
	Session lession1, lession2;			//A course has 2 lession
	Mark mark;
	CourseInfo* cNext;
};
struct NodeCourse
{
	string SchoolYear;
	int Semester;
	CourseInfo* info;
	NodeCourse* pNext;
};
struct ListCourse
{
	NodeCourse* pHead;
	NodeCourse* pTail;
};
struct Student
{
	//Add by file
	int no;
	string studentID;
	string firstName;
	string lastName;
	int gender;
	Date dob;
	string socialID;

	//Add After Registration
	string _class;
	ListCourse _course;
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
struct Class
{
	string className;
	int numberStudents;
	List classStudents;
};
struct Staff
{
	string username;
	string password;
	string staffName;
	int gender;
	Date dob;
	string qualif;
};
NodeCourse* CreateNode_Course(CourseInfo x);
void addTail_Course(ListCourse& l, NodeCourse* p);
void CreateList_Course(ListCourse l);
void saveFile(string cl);
Student loadFile(string cl, string id);
int findClass(string username, string password, string& cl);
void Doc_Ngay_DKHP(ifstream& filein, Date& dateBegin, Date& dateEnd);
void Doc_Thong_Tin_1_Mon(ifstream& filein, CourseInfo& course_info);
void Doc_Danh_Sach_Mon(ifstream& filein, ListCourse& l);
void Xuat_Mon(CourseInfo c);
void Xuat_Danh_Sach_Mon(ifstream& filein, ListCourse l);
void Enroll_Course();


