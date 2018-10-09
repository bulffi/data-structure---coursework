#include <iostream>
#include <list>
#include <string>

using namespace std;

class student
{
public:
	string name;
	string sex;
	string age;
	string number;
	string major;
	friend istream& operator >>(istream& in, student& stu);
	friend ostream& operator <<(ostream& out, const student& stu);
	student(const string& stu_number, const string& stu_name, const string& stu_sex,
		const string& stu_age, const string& stu_major)
	{
		name = stu_name;
		sex = stu_sex;
		age = stu_age;
		number = stu_number;
		major = stu_major;
	};
	student() {};
};
istream& operator >>(istream& in, student& stu)
{
	in >> stu.number >> stu.name >> stu.sex >> stu.age >> stu.major;
	return in;
}
ostream& operator <<(ostream& out, const student& stu)
{
	//printf("%10s %10s %10s %10s %10s\n", "考号", "姓名", "性别", "年龄", "报考类别");
	printf("%10s %10s %10s %10s %10s\n", stu.number.c_str(),stu.name.c_str(), stu.sex.c_str(), stu.age.c_str(), stu.major.c_str());

	return out;
}
template<typename T>
class List_node
{
public:
	T data;
	List_node<T> *next;
	string key;

	List_node(List_node<T> *ptr = nullptr) { next = ptr; };
	List_node(const T& item, const string& key_to, List_node<T> * ptr = nullptr)
	{
		data = item;
		key = key_to;
		next = ptr;
	}
};



template<typename T>
class List : public List_node<T>
{
	List_node<T> *ptr_first;
	int size;

public:
	template<typename T>
	friend ostream& operator<< (ostream& out, List<T>& my_list);
	List() :size(0)
	{
		ptr_first = new List_node<T>();
	};
	bool my_inserter(int position, const T& data,const string& key);
	bool my_dalete(int position);
	List_node<T>* my_search(const string& key);
	int size_of()
	{
		return size;
	};

};
template<typename T>
ostream& operator << (ostream& out, List<T>& my_list)
{
	List_node<T>* ptr_start = my_list.ptr_first;
	printf("%10s %10s %10s %10s %10s\n", "考号", "姓名", "性别", "年龄", "报考类别");
	if (my_list.size_of())
	{
		ptr_start = ptr_start->next;
		while (ptr_start)
		{
			out << ptr_start->data;
			ptr_start = ptr_start->next;
		}
	}
	
	return out;
}
template<typename T>
bool List<T>::my_dalete(int position)
{
	List_node<T> *ptr_start = ptr_first;
	if (position < 0 || position > size - 1)
		return false;

	for (int i = 0; i< position; i++)
	{
		ptr_start = ptr_start->next;
	}

	List_node<T> *ptr_delet = ptr_start->next;
	ptr_start->next = ptr_delet->next;
	delete ptr_delet;
	size--;
	return true;

}

template<typename T>
bool  List<T>::my_inserter(int position, const T& data,const string& key_to)
{
	List_node<T> *ptr_start = ptr_first;
	if (position<0 || position>size)
		return false;

	for (int i = 0; i< position; i++)
	{
		ptr_start = ptr_start->next;
	}

	List_node<T> *ptr_new = new List_node<T>(data,key_to);
	size++;
	ptr_new->next = ptr_start->next;
	ptr_start->next = ptr_new;

	return true;

}

template<typename T>
List_node<T>* List<T>::my_search(const string& key)
{
	List_node<T>* ptr_start = ptr_first;
	while (ptr_start&&ptr_start->key!=key)
	{
		ptr_start = ptr_start->next;
	}
	return ptr_start;
}



int main()
{
	int stu_number;
	cout << "首先请建立考生信息系统！" << endl << "请输入考生人数： " << endl;
	cin >> stu_number;
	cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别！" << endl;
	List<student> list_stu;
	for (int i = 0; i < stu_number; i++)
	{
		student tempt;
		cin >> tempt;
	//	cout << tempt;
		list_stu.my_inserter(list_stu.size_of(), tempt , tempt.number);
	}
	cout << list_stu;
	int option = 0;
	cout << "请选择您要进行的操作 （1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作"<< endl;
	do
	{
		cout << "请选择您要进行的操作： " << endl;
		cin >> option;
		switch (option)
		{
		case 1:
		{
			int posi;
			cout << "请输入你要插入的考生的位置： " << endl;
			cin >> posi;
			cout << "请依次输入要插入的考生的考号，姓名，性别，年龄及报考类别！" << endl;
			student tempt;
			cin >> tempt;
			list_stu.my_inserter(posi - 1, tempt, tempt.number);
			cout << list_stu;
		}break;
		case 2:
		{
			int posi;
			cout << "请输入你要删除的考生的位置： " << endl;
			cin >> posi;
			list_stu.my_dalete(posi-1);
			cout << list_stu;
		}break;
		case 3:
		{
			string posi;
			cout << "请输入你要找的考生的考号： " << endl;
			cin >> posi;
			if (list_stu.my_search(posi))
			{
				cout << "你要找的考生信息是： " << endl;
				cout << list_stu.my_search(posi)->data;
			}
			else
			{
				cout << "没有找到！" << endl;
			}
		}break;
		case 4:
		{
			string posi;
			cout << "请输入你要修改的考生的考号： " << endl;
			cin >> posi;
			if (list_stu.my_search(posi))
			{
				cout << "你要修改的考生信息是： " << endl;
				cout << list_stu.my_search(posi)->data;
				cout << "请依次输入要插入的考生的考号，姓名，性别，年龄及报考类别！" << endl;
				student tempt;
				cin >> tempt;
				list_stu.my_search(posi)->data = tempt;
				cout << list_stu;
			}
			else
			{
				cout << "没有找到！" << endl;
			}

		}break;
		case 5:
		{
			cout << list_stu;
		}break;
		default:
			break;
		}

	} while (option);

	system("pause");
	return 0;
}