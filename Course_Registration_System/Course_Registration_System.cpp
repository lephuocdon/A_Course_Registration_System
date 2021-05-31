#include"Manager.h"
using namespace std;
Course* CreateNode_Course(CourseInfo x)
{
	Course* p = new Course;
	if (p == NULL)
	{
		cout << "\nCap phat that bai !";
		return NULL;
	}
	//strcpy(p->courseID, x.courseID);
	p->info = x;
	p->info.Next = NULL;
	return p;
}
//Khởi tạo danh sách của khoá học
void CreateList(List_Course l)
{
	l.Head = NULL;
	l.Tail = NULL;
}
void registration_session(List_Course l)
{
	string mahp;
	//Xuất ra danh sách các môn học để students đăng ký 
	cout << "Nhap ma hoc phan ban muon dang ky: ";
	getline(cin, mahp);
	if (l.Head != NULL)
	{
		CourseInfo* k = l.Head;
		while (k != NULL)
		{
			if (strcmp(k->courseID, mahp) == 0)
			{

			}
			else
			{

			}
		}
	}

}