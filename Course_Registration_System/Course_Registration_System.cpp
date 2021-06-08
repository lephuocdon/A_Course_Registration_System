#include"Course_Registration_System.h"
using namespace std;
//Khởi tạo 1 NodeCourse
NodeCourse* CreateNode_Course(CourseInfo* x)
{
	NodeCourse* p = new NodeCourse;
	/*p->info->courseID = x.courseID;
	p->info->courseName = x.courseName;
	p->info->credits = x.credits;
	p->info->lession1 = x.lession1;
	p->info->lession2 = x.lession2;
	p->info->mark = x.mark;
	p->info->maxStudents = x.maxStudents;
	p->info->teacherName = x.teacherName;*/
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
//Khởi tạo danh sách của khoá học
void removeHead(ListCourse& l)
{
	if (l.pHead == NULL)
	{
		cout << "Nothing to do ! ";
	}
	else
	{
		NodeCourse* temp = l.pHead;
		l.pHead = l.pHead->pNext;
		delete temp;
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
void Doc_Thong_Tin_1_Mon(ifstream& filein, CourseInfo*& course_info)
{
	getline(filein, course_info->courseID, ',');
	filein.seekg(1, 1);
	getline(filein, course_info->courseName, ',');
	filein.seekg(1, 1);
	filein >> course_info->credits;
	filein.seekg(1, 1);
	getline(filein, course_info->lession1.day, '-');
	filein.seekg(1, 1);
	getline(filein, course_info->lession1.period, ',');
	filein.seekg(1, 1);
	getline(filein, course_info->lession2.day, '-');
	filein.seekg(1, 1);
	getline(filein, course_info->lession2.period, ',');
	filein.seekg(1, 1);
	getline(filein, course_info->teacherName);
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
		CourseInfo* course_info;
		Doc_Thong_Tin_1_Mon(filein,course_info);
		//Khởi tạo 1 NodeCourse
		NodeCourse* p = CreateNode_Course(course_info);
		//Thêm Môn vào Danh sách Môn
		addCourse(l, p);
	}
}
void Xuat_Mon(NodeCourse* k)
{
	cout << left << setw(13) << k->info->courseID << setw(26) << k->info->courseName << setw(12) << k->info->credits;
	cout << left << setw(14) << k->info->lession1.day << "-" << k->info->lession1.period;
	cout << left << setw(13) << k->info->lession2.day << "-" << k->info->lession2.period << setw(25) << k->info->teacherName << endl;
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
		Xuat_Mon(k);
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
void Enroll_Course(ListCourse l, ListCourse& l2)
{
	ifstream filein;
	int check;
	char c;
	//NodeCourse* p = new NodeCourse;
	filein.open("2020-2021\\2\\ListCourse.csv", ios::in);
	Xuat_Danh_Sach_Mon(filein, l);
	filein.close();
	string s;
	do
	{
		do
		{
			check = 0;
			cout << "Enter your Course ID you want to Enroll: ";
			getline(cin, s);
			for (NodeCourse* k = l.pHead;k != NULL;k = k->pNext)
			{
				//Kiểm tra điều kiện đăng ký học phần có thoả mãn hay không
				if ((k->info->courseID == s) && (numberOfStudent_in_Course(k->info->courseName) < 50) && (checkLession(k, l2)) && (Count_course_in_List(l2) < 5))
				{
					NodeCourse* p = CreateNode_Course(k->info);
					addCourse(l2, p);
					check++;
					cout << "Enroll Success !!" << endl;
					cout << "Do you want to continue Enrollment: (Yes: y/Y or No:n/N) ";
					cin >> c;
					break;
				}
			}
			if (check == 0) cout << "Failed. Input again !!" << endl;
		} while (check == 0);
	}
	while ( c=='y' || c == 'Y');
}
//View list môn đã đăng ký
void View_List(ListCourse l)
{
	cout << left << setw(13) << "Course ID" << setw(26) << "Course Name" << setw(12) << "Credits";
	cout << left << setw(14) << "Lession 1" << setw(13) << "Lession 2" << setw(25) << "Teacher Name" << endl;
	for (NodeCourse* k = l.pHead;k != NULL;k = k->pNext)
	{
		Xuat_Mon(k);
	}
}
//Huỷ môn đã đăng ký
void Remove_a_Course_from_the_enrolled_List(ListCourse& l)
{
	View_List(l);
	string id;
	int check = 0;
	do
	{ 
		cout << "Enter your Course ID you want to Remove: ";
		getline(cin, id);
		for (NodeCourse* k = l.pHead;k != NULL;k = k->pNext)
		{
			if (k->info->courseID == id)
			{
				check++;
			}
		}
		if (check == 0)
		{
			cout << "Failed. Input again !!" << endl;
		}
		else
		{
			remove_NodeCourse(l, id);
			View_List(l);
		}
	} while (check == 0);

}
//View bảng điểmm