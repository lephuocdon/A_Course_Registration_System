﻿#include"Course_Registration_System.h"
using namespace std;
//Khởi tạo 1 NodeCourse
NodeCourse* CreateNode_Course(CourseInfo x)
{
	NodeCourse* p = new NodeCourse;
	if (p == NULL)
	{
		cout << "Failed to allocate memory!";
		return NULL;
	}
	else
	{
		p->info->courseID = x.courseID;
		p->info->courseName = x.courseName;
		p->info->credits = x.credits;
		p->info->lession1 = x.lession1;
		p->info->lession2 = x.lession2;
		p->info->mark = x.mark;
		p->info->maxStudents = x.maxStudents;
		p->info->teacherName = x.teacherName;
		p->pNext = NULL;
		return p;
	}
}
//Thêm vào cuối ListCourse
void addTail_Course(ListCourse& l, NodeCourse* p)
{
	if (l.pHead == NULL)
	{
		l.pHead = l.pTail = p;
	}
	else
	{
		l.pTail->pNext = p;
		l.pTail = p;
	}
}
//Khởi tạo danh sách của khoá học
void CreateList_Course(ListCourse l)
{
	l.pHead = NULL;
	l.pTail = NULL;
}
/*void saveFile(string cl)
{
	ofstream outfile(cl + ".txt", ofstream::binary);
	outfile.write((char*)STUDENTS, sizeof(STUDENTS));
	outfile.close();
}*/
int findClass(string username, string password, string &cl)
{
	string user, pass, class_name;
	ifstream fstu("StudentAccount.txt");
	if (!fstu.is_open())
	{
		cout << " Failed to open file StudentAccount.txt";
		return 0;
	}
	while (!fstu.eof())
	{
		getline(fstu, user, ',');
		getline(fstu, pass, ',');
		getline(fstu, class_name);
		if (user == username && pass == password)
		{
			cl = class_name;
			return 1;
		}
	}
}
/*Student loadFile(string cl, string id)
{
	int numberOfStudents = 0;
	ifstream infile(cl + ".txt", ifstream::binary);
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
}*/
//Đăng ký môn 
void Doc_Ngay_DKHP(ifstream& filein, Date &dateBegin, Date &dateEnd)
{
	filein >> dateBegin.dd;
	filein.seekg(1, 1); 
	filein >> dateBegin.mm;
	filein.seekg(1, 1);
	filein >> dateEnd.dd;
	filein.seekg(1, 1);
	filein >> dateEnd.mm;
}
void Doc_Thong_Tin_1_Mon(ifstream& filein, CourseInfo& course_info)
{
	getline(filein, course_info.courseID, ',');
	filein.seekg(1, 1);
	getline(filein, course_info.courseName, ',');
	filein.seekg(1, 1);
	filein >> course_info.credits;
	filein.seekg(1, 1);
	getline(filein, course_info.lession1.day, '-');
	filein.seekg(1, 1);
	getline(filein, course_info.lession1.period, ',');
	filein.seekg(1, 1);
	getline(filein, course_info.lession2.day, '-');
	filein.seekg(1, 1);
	getline(filein, course_info.lession2.period, ',');
	filein.seekg(1, 1);
	getline(filein, course_info.teacherName);
	string temp;
	getline(filein, temp);
}
void Doc_Danh_Sach_Mon(ifstream& filein, ListCourse& l)
{
	CreateList_Course(l);
	cin.ignore(12);
	while (!filein.eof())
	{
		//Đọc thông tin Môn
		CourseInfo course_info;
		Doc_Thong_Tin_1_Mon(filein,course_info);
		//Khởi tạo 1 NodeCourse
		NodeCourse* p = CreateNode_Course(course_info);
		//Thêm Môn vào Danh sách Môn
		addTail_Course(l, p);
	}
}
void Xuat_Mon(CourseInfo c)
{
	cout << left << setw(13) << c.courseID << setw(26) << c.courseName << setw(12) << c.credits;
	cout << left << setw(14) << c.lession1.day << "-" << c.lession1.period;
	cout << left << setw(13) << c.lession2.day << "-" << c.lession2.period << setw(25) << c.teacherName << endl;
}
void Xuat_Danh_Sach_Mon(ifstream& filein, ListCourse l)
{
	Date dateBegin, dateEnd;
	int dem = 1;
	Doc_Danh_Sach_Mon(filein, l);
	Doc_Ngay_DKHP(filein, dateBegin, dateEnd);
	cout << "Date Begin: " << dateBegin.dd << "/" << dateBegin.mm << endl;
	cout << "Date End  : " << dateEnd.dd << "/" << dateEnd.mm << endl << endl;
	cout << "-----------------------------------List of Courses-----------------------------------" << endl;
	cout << left << setw(13) << "Course ID" << setw(26) << "Course Name" << setw(12) << "Credits";
	cout << left << setw(14) << "Lession 1" << setw(13) << "Lession 2" << setw(25) << "Teacher Name" << endl;
	for (NodeCourse* k = l.pHead;k != NULL;k=k->pNext)
	{
		cout << left << setw(13) << k->info->courseID << setw(26) << k->info->courseName << setw(12) << k->info->credits;
		cout << left << setw(14) << k->info->lession1.day << "-" << k->info->lession1.period;
		cout << left << setw(13) << k->info->lession2.day << "-" << k->info->lession2.period << setw(25) << k->info->teacherName << endl;
	}

}
//Hàm kiểm tra xem số Courses mà Student đăng ký đã vượt quá 5 chưa
//Hàm trả về courseName dựa vào courseID nhập từ bàn phím
string Search_courseName(ListCourse l, string& course_ID)
{
	for (NodeCourse* k = l.pHead;k != NULL;k = k->pNext)
	{
		if (k->info->courseID == course_ID);
		return k->info->courseName;
	}
}
//Hàm đếm số lượng sinh viên có trong 1 Course
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
void Enroll_Course()
{
	ListCourse l;
	ifstream filein;
	NodeCourse* p = new NodeCourse;
	filein.open("2020-2021\\2\\ListCourse.csv", ios::in);
	Xuat_Danh_Sach_Mon(filein, l);
	filein.close();
	string s;
	cout << "Enter your Course ID you want to Enroll: ";
	getline(cin, s);
	for (NodeCourse* k = l.pHead;k != NULL;k = k->pNext)
	{
		if (k->info->courseID == s)
		{
			p = k;
		}
	}
	//Nếu nhập đúng => kiểm tra số lượng sinh viên hiện tại của môn và kiểm tra xem tối đa 5 môn chưa
	//Nhập sai: nhập lại
}
//View list môn đã đăng ký

//Huỷ môn đã đăng ký

//View bảng điểmm