#include"Course_Registration_System.h"
using namespace std;
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

//Khởi tạo danh sách của khoá học
void CreateList_Course(ListCourse l)
{
	l.pHead = NULL;
	l.pTail = NULL;
}
void saveFile(string cl)
{
	ofstream outfile(cl + ".txt", ofstream::binary);
	outfile.write((char*)STUDENTS, sizeof(STUDENTS));
	outfile.close();
}
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
Student loadFile(string cl, string id)
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
}
//Đăng ký môn 
void Enroll_Course()
{
	//Xuất danh sách môn ra màn hình

}
//View list môn đã đăng ký

//Huỷ môn đã đăng ký

//View bảng điểmm