#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<iomanip>
#include<fstream>
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
	double gpa[3];

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
//Local Variable
Student STUDENTS[50];
NodeCourse* CreateNode_Course(CourseInfo* x)
{
	NodeCourse* p = new NodeCourse;
	p->info = x;
	p->pNext = NULL;
	return p;
}
//Thêm Node vào ListCourse
void addCourse(ListCourse& l, NodeCourse* p)
{
	if (l.pHead == NULL)
	{
		l.pHead = p;
		l.pTail = p;
	}
	else
	{
		l.pTail->pNext = p;
		l.pTail = p;
	}
}
// Hàm xoá 1 NodeCourse có id trùng với id nhập vào
void remove_NodeCourse(ListCourse& l, string id)
{
	NodeCourse* pDel = l.pHead; // tạo một node pDel để xóa
  //Nếu pDel == Null thì danh sách rỗng
	if (pDel == NULL) {
		cout << "List is empty!!";
	}
	//ngược lại thì xét điều kiện
	else {
		NodeCourse* pPre = NULL;
		//dùng vòng lặp while để tìm ra pDel và pPre (vị trí đứng trước pDel)
		while (pDel != NULL) {
			if (pDel->info->courseID == id) {
				break;
			}
			pPre = pDel;
			pDel = pDel->pNext;
		}
		//Nếu pDel == null tức là không tìm thấy số cần xóa
		if (pDel == NULL) {
			cout << "Don't find!!";
		}
		// Ngược lại tiếp tục xét điều kiện
		else {
			// Nếu pDel == l.pHead, tức là node cần xóa ở đầu danh sách
			if (pDel == l.pHead) {
				l.pHead = l.pHead->pNext;
				pDel->pNext = NULL;
				delete pDel;
				//pDel = NULL;
			}
			//Nếu pDel == l.pTail, tức là node cần xóa ở cuối danh sách
			else if (pDel->pNext == NULL) {
				l.pTail = pPre;
				pPre->pNext = NULL;
				delete pDel;
				//pDel = NULL;
			}
			// và trường hợp cuối cùng số muốn xóa nằm ở giữa danh sách
			else {
				pPre->pNext = pDel->pNext;
				pDel->pNext = NULL;
				delete pDel;
				//pDel = NULL;
			}
		}
	}
}
//Khởi tạo danh sách của khoá học
void CreateList_Course(ListCourse& l)
{
	l.pHead = NULL;
	l.pTail = NULL;
}
void saveFile(string cl)
{
	ofstream outfile("Class/" + cl + "_Mark.txt", ofstream::binary);
	outfile.write((char*)STUDENTS, sizeof(STUDENTS));
	outfile.close();
}
Student loadFile(string cl, string id)
{
	int numberOfStudents = 0;
	ifstream infile("Class/" + cl + "_Mark.txt", ifstream::binary);
	infile.seekg(0);
	infile.read((char*)STUDENTS, sizeof(STUDENTS));
	infile.close();
	for (int i = 0; i < 50; i++)
	{
		if (STUDENTS[i].studentID == id)
		{
			return STUDENTS[i];
		}
	}
}
void Doc_Ngay_DKHP(ifstream& filein, Date& dateBegin, Date& dateEnd)
{
	filein >> dateBegin.dd;
	filein.seekg(1, 1);
	filein >> dateBegin.mm;
	filein.seekg(1, 1);
	filein >> dateEnd.dd;
	filein.seekg(1, 1);
	filein >> dateEnd.mm;
	string s;
	getline(filein, s);
}
void Doc_Thong_Tin_1_Mon(ifstream& filein, CourseInfo*& course_info)
{
	getline(filein, course_info->courseID, ',');
	//filein.seekg(1, 1);
	getline(filein, course_info->courseName, ',');
	//filein.seekg(1, 1);
	filein >> course_info->credits;
	filein.seekg(1, 1);
	getline(filein, course_info->lession1.day, '-');
	filein.seekg(1, 1);
	getline(filein, course_info->lession1.period, ',');
	//	filein.seekg(1, 1);
	getline(filein, course_info->lession2.day, '-');
	filein.seekg(1, 1);
	getline(filein, course_info->lession2.period, ',');
	//	filein.seekg(1, 1);
	getline(filein, course_info->teacherName);
	//string temp;
	//getline(filein, temp);
}
void Doc_Danh_Sach_Mon(ifstream& filein, ListCourse& l)
{
	while (!filein.eof())
	{
		//Đọc thông tin Môn
		CourseInfo* course_info = new CourseInfo;
		Doc_Thong_Tin_1_Mon(filein, course_info);
		//Khởi tạo 1 NodeCourse
		NodeCourse* p = CreateNode_Course(course_info);
		//Thêm Môn vào Danh sách Môn
		addCourse(l, p);
	}
}
void Xuat_Mon(NodeCourse* k)
{
	cout << left << setw(14) << k->info->courseID << setw(36) << k->info->courseName << setw(12) << k->info->credits;
	cout << left << k->info->lession1.day << "-" << setw(10) << k->info->lession1.period;
	cout << k->info->lession2.day << "-" << setw(9) << k->info->lession2.period << setw(20) << k->info->teacherName << endl;
}
void Xuat_Danh_Sach_Mon(ifstream& filein, ListCourse& l)
{
	Date dateBegin, dateEnd;
	int dem = 1;
	Doc_Ngay_DKHP(filein, dateBegin, dateEnd);
	Doc_Danh_Sach_Mon(filein, l);
	cout << "Date Begin: " << dateBegin.dd << "/" << dateBegin.mm << endl;
	cout << "Date End  : " << dateEnd.dd << "/" << dateEnd.mm << endl << endl;
	cout << "-----------------------------------List of Courses-----------------------------------" << endl;
	cout << left << setw(14) << "Course ID" << setw(36) << "Course Name" << setw(12) << "Credits";
	cout << left << setw(14) << "Lession 1" << setw(13) << "Lession 2" << setw(25) << "Teacher Name" << endl;
	for (NodeCourse* k = l.pHead;k != NULL;k = k->pNext)
	{
		Xuat_Mon(k);
	}

}
int numberOfStudent_in_Course(string course_name)
{
	int numberOfStudents = 0;
	char c;
	ifstream infile;
	infile.open("2020-2021\\2\\" + course_name + ".csv", ios::in);
	infile.get(c);
	while (infile)
	{
		if (c = '\n')
		{
			numberOfStudents++;
		}
	}
	return numberOfStudents;
}
//Kiểm tra xem môn mới đăng ký có bị trùng tiết với môn đã đăng ký hay không
bool checkLession(NodeCourse* a, ListCourse l2)
{
	for (NodeCourse* k = l2.pHead;k != NULL;k = k->pNext)
	{
		if ((a->info->lession1.day == k->info->lession1.day && a->info->lession1.period == k->info->lession1.period) || (a->info->lession2.day == k->info->lession2.day && a->info->lession2.period == k->info->lession2.period))
			return false;
	}
	return true;
}
//Hàm đếm số môn trong List đăng ký
int Count_course_in_List(ListCourse l2)
{
	int dem = 0;
	for (NodeCourse* k = l2.pHead;k != NULL;k = k->pNext)
	{
		if (k != NULL)
			dem++;
	}
	return dem;
}
//Search Class from ID in file StudentAccount.txt
string searchClass(string id)
{
	//Search Class from ID in file StudentAccount.txt
	ifstream f("StudentAccount.txt");
	string s; unsigned int pos1 = -1, pos2 = -1;
	while (!f.eof())
	{
		getline(f, s, '\n');
		for (unsigned int i = 0; i < s.length(); i++)
		{
			if (s[i] == ',')
			{
				if (pos1 == -1)
				{
					pos1 = i;
				}
				else
				{
					pos2 = i;
					break;
				}
			}
		}
		if (id == s.substr(0, pos1))
		{
			return s.substr(pos2 + 1, s.length() - pos2 - 1);
		}
		pos1 = -1; pos2 = -1;
	}
	f.close();
}
// Đăng ký học phần
void Enroll_Course(ifstream& filein, ListCourse& l, ListCourse& l2, Student& S, string SY, int& SE)
{
	int check;
	char c;
	Xuat_Danh_Sach_Mon(filein, l);
	do
	{
		string s;
		check = 0;
		cout << "Enter your Course ID you want to Enroll: ";
		getline(cin, s);
		for (NodeCourse* k = l.pHead;k != NULL;k = k->pNext)
		{
			//Kiểm tra điều kiện đăng ký học phần có thoả mãn hay không
			if ((k->info->courseID == s) && (numberOfStudent_in_Course(k->info->courseName) < k->info->maxStudents) && (checkLession(k, l2)))
			{
				if (Count_course_in_List(l2) < 5)
				{
					if (numberOfStudent_in_Course(k->info->courseName) < k->info->maxStudents)
					{
						if (checkLession(k, l2))
						{
							NodeCourse* p = CreateNode_Course(k->info);
							addCourse(l2, p);
							check++;
							cout << "Enroll Success !!" << endl;
							cout << "Do you want to continue Enrollment: (Yes: y/Y or No:n/N) ";
							cin >> c;
							cin.ignore();
							break;
						}
						//Trùng lịch với môn đã đăng ký
						else
						{
							cout << "Coincide with the registered coursev!!" << endl;
							return;
						}
					}
					//Lớp đã đầy (50/50)
					else
					{
						cout << "Students in Course is FULL (50/50) !!" << endl;
						return;
					}
				}
				else
				{
					cout << "Sorry !! You were enrolled 05/05 Courses !!" << endl;
					return;
				}
			}
		}
		if (check == 0) cout << "Failed. Input again !!" << endl;
	} while (check == 0 || c == 'y' || c == 'Y');
	NodeCourse* p1 = S._course.pHead;
	while (p1->SchoolYear != SY && p1->Semester != SE)
	{
		p1 = p1->pNext;
	}
	NodeCourse* p2 = l2.pHead;
	p1->info = p2->info;
	while (p2->pNext != NULL)
	{
		p2 = p2->pNext;
		p1->info->cNext = p2->info;
		p1->info = p1->info->cNext;
	}
}
// Xem danh sách môn đã đăng ký
void viewListCourses(Student S, string SY, int SE)
{
	//Student
	cout << setw(10) << "Course ID" << setw(40) << "Course Name" << setw(13) << "Credits" << setw(10) << "Session 1" << setw(10) << "Session 2" << setw(25) << "Teacher Name" << endl;
	NodeCourse* p = S._course.pHead;
	while (p->SchoolYear != SY && p->Semester != SE)
	{
		p = p->pNext;
	}
	CourseInfo* c = p->info;
	while (c != NULL)
	{
		cout << setw(10) << c->courseID << setw(40) << c->courseName << setw(13) << c->credits << setw(10) << c->lession1.day + "-" + c->lession1.period << setw(10) << c->lession2.day + "-" + c->lession2.period << setw(25) << c->teacherName << endl;
		c = c->cNext;
	}
}
//Huỷ môn đã đăng ký
void Remove_a_Course_from_the_enrolled_List(Student& S, string SY, int SE)
{
	viewListCourses(S, SY, SE);
	int check = 0;
	do
	{
		string id;
		cout << "Enter your Course ID you want to Remove: ";
		getline(cin, id);
		for (NodeCourse* k = S._course.pHead;k != NULL;k = k->pNext)
		{
			if (k->info->courseID == id)
			{
				check++;
			}
		}
		if (check == 0)
		{
			cout << "Remove failed. Again !!" << endl;
		}
		else
		{
			remove_NodeCourse(S._course, id);
			viewListCourses(S, SY, SE);
		}
	} while (check == 0);
}
/*void main()
{
	ListCourse l, l2;
	Student S;
	string SY;
	int SE;
	CourseInfo* p = new CourseInfo;
	Date dateBegin, dateEnd;
	CreateList_Course(l);
	CreateList_Course(l2);
	ifstream filein;
	filein.open("ListCourse.csv", ios::in);
	Enroll_Course(filein, l, l2, S, SY, SE);
	filein.close();
	system("pause");
}*/
void view_ScoreBoard()
{
	string id, cl;
	Student S;
	string sy, _sy = "" ,se;
	cout << "School Year (Ex: 2020-2021): "; 
	getline(cin, sy);
	ifstream f("ListSchoolYear.txt");
	while (!f.eof())
	{
		getline(f, _sy, '\n');
		if (_sy == sy)
		{
			break;
		}
		_sy = "";
	}
	f.close();
	if (_sy == "")
	{
		cout << "This School Year doesn't exist!" << endl;
	}
	else
	{
		cout << "Semester: "; 
		getline(cin, se);
		ifstream f(sy + "/" + se + "/ListCourse.csv");
		if (!f.is_open())
		{
			cout << "This Semester doesn't exist!" << endl;
		}
		else
		{
			cl = searchClass(id);
			S = loadFile(cl, id);
			cout << "------------------------------------------------ScoreBoard----------------------------------------------" << endl;
			cout << left << setw(4) << "No" << setw(12) << "Course ID" << setw(33) << "Course Name" << setw(17) << "Midtream Mark" << setw(14) << "Final Mark" << setw(14) << "Other Mark" << setw(14) << "Total Mark" << endl;
			NodeCourse* p = S._course.pHead;
			while (p->SchoolYear != sy && p->Semester != atoi(se.c_str()));
			{
				p = p->pNext;
			}
			CourseInfo* c = p->info;
			int count = 1;
			while (c != NULL)
			{
				cout << left << setw(4) << count << setw(12) << c->courseID << setw(33) << c->courseName << setw(17) << setprecision(2) << c->mark.midtermMark << setw(14) << setprecision(2) << c->mark.finalMark << setw(14) << setprecision(2) << c->mark.otherMark;
				if ((c->mark.midtermMark * 0.5 + c->mark.finalMark * 0.5 + c->mark.otherMark) > 10.00)
				{
					cout << setw(14) << "10.00" << endl;
				}
				else
				{
					cout << setw(14) << setprecision(2) << c->mark.midtermMark * 0.5 + c->mark.finalMark * 0.5 + c->mark.otherMark << endl;
				}
				c = c->cNext;
			}
			cout << "GPA: " << S.gpa[atoi(se.c_str()) - 1] << endl;
		}
}
