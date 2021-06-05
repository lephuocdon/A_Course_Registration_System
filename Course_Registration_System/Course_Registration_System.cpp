#include"Course_Registration_System.h"
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
void Xuat_Danh_Sach_Mon(ifstream &filein, ListCourse l)
{
	Date dateBegin, dateEnd;
	Doc_Ngay_DKHP(filein, dateBegin, dateEnd);
	cout << "Date Begin: " << dateBegin.dd << "/" << dateBegin.mm << endl;
	cout << "Date End  : " << dateEnd.dd << "/" << dateEnd.mm << endl << endl;
	cout << "-----------------------------------List of Courses-----------------------------------" << endl;

}
void Enroll_Course()
{
	//Xuất danh sách môn ra màn hình

}
//View list môn đã đăng ký

//Huỷ môn đã đăng ký

//View bảng điểmm