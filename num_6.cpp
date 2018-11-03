#include<iostream>
#include<string>
#include<vector>
using namespace std;

class family
{
public:
	string key()
	{
		return name;
	}
	family() = default;
	family(string key_name)
	{
		name = key_name;
	}

	string name;
};


template<typename T>
class treeNode
{
public:
	treeNode() = default;
	treeNode(string key)
	{
		data = T(key);
	}
	T data;
	treeNode *left = nullptr;
	treeNode *right = nullptr;
};


template<typename T>
class Tree
{
public:
	Tree(string tempt);
	bool to_delete(treeNode<T> *root);
	treeNode<T>* the_root()
	{
		return root;
	}
	bool find(treeNode<T>*the_root,string key,treeNode<T> *&result);
	bool add(treeNode<T>*position,int type,string key);/// 1->child 0->brother
	int find_father(treeNode<T>*position, treeNode<T>*target,treeNode<T>*&result)///1->左儿子 2->右儿子
	{
		treeNode<T>* tempt = position;
		int retu = 0;
		if (tempt->left==target)
		{
			result = tempt;
			retu = 1;
		}
		else if (tempt->right == target)
		{
			result = tempt;
			retu = 2;
		}
		else
		{
			tempt = tempt->left;
			while (tempt && ! (retu = find_father(tempt,target,result)))
			{
				tempt = tempt->right;
			}
		}
		return retu;

	}
	
	~Tree();

private:
	treeNode<T> *root = nullptr;
};

template<typename T>
bool Tree<T>::to_delete(treeNode<T> *root_to_delete)
{
	if (root_to_delete)
	{
		to_delete(root_to_delete->left);
		to_delete(root_to_delete->right);

		delete root_to_delete;
	}
	return true;
}

template<typename T>
bool Tree<T>::add(treeNode<T>* pos, int type,string key)
{
	treeNode<T>* position=pos;
	if (type)
	{
		if (position->left)
		{
			treeNode<T>* first_child = position->left;
			while (first_child->right)
			{
				first_child = first_child->right;
			}
			first_child->right = new treeNode<T>(key);
		}
		else
		{
			position->left = new treeNode<T>(key);
		}
	}
	else
	{
		while (position->right)
		{
			position = position->right;
		}
		position->right = new treeNode<T>(key);
	}

	return true;
}


template<typename T>
bool Tree<T>::find(treeNode<T>* the_root,string key, treeNode<T>*& result)
{
	treeNode<T>* tempt = the_root;
	bool outcome=false;
	if (the_root->data.key() == key)
	{
		result = the_root;
		outcome = true;
	}
	else
	{
		tempt = tempt->left;
		while (tempt && !(outcome=find(tempt,key,result)))
		{
			tempt = tempt->right;
		}
	}

	return outcome;
	
}

template<typename T>
Tree<T>::Tree(string tempt)
{
	root = new treeNode<T>(tempt);
}
template<typename T>
Tree<T>::~Tree()
{
	to_delete(root);
}

int main()
{
	cout << "**                家谱管理系统               " << endl;
	cout << "================================================" << endl;
	cout << "               请选择要执行的操作             " << endl;
	cout << "                  A --- 完善家谱             " << endl;
	cout << "                  B --- 添加家庭成员         " << endl;
	cout << "                  C --- 解散局部家庭         " << endl;
	cout << "                  D --- 更改局部家庭成员姓名  " << endl;
	cout << "                  E --- 推出程序             " << endl;
	cout << "================================================" << endl;
	cout << "首先建立一个家庭\n请输入祖先的姓名： ";
	string tempt;
	
	cin >> tempt;
	Tree<family> family_tree(tempt);
	cout << "此家谱的祖先是： " << tempt << endl << endl;;
	char choice;
	cout << "请选择要执行的操作: ";
	while (cin>>choice)
	{
		switch (choice)
		{
		case 'A':
		{
			cout << "请输入要建立家庭的人的姓名： ";
			string name;
			cin >> name;
			treeNode<family>* result;
			if (family_tree.find(family_tree.the_root(), name, result))
			{
				cout << "请输入要加入" <<name<<"的儿女的个数: ";
				int num;
				cin >> num;
				cout << "请依次输入" <<name<<"的儿女的姓名: ";
				vector<string> names_to_add;
				for (int i = 0; i < num; i++)
				{
					string name_of_child;
					cin >> name_of_child;
					names_to_add.push_back(name_of_child);
					family_tree.add(result, 1, name_of_child);
				}
				cout << name<<"的第一代子孙是: ";
				result = result->left;
				while (result)
				{
					cout << result->data.key() << "    ";
					result = result->right;
				}
				cout << endl;

			}
			else
			{
				cout << "查无此人" << endl;
			}
		}break;
		case 'B':
		{
			cout << "请输入要添加儿子的人的姓名: ";
			string name;
			cin >> name;
			treeNode<family>* result;
			if (family_tree.find(family_tree.the_root(), name, result))
			{
				cout << "请输入" <<name<<"的儿女的姓名: ";
				string name_to_add;
				cin >> name_to_add;
				family_tree.add(result, 1, name_to_add);
				cout << name << "的第一代子孙是: ";
				result = result->left;
				while (result)
				{
					cout << result->data.key() << "    ";
					result = result->right;
				}
				cout << endl;
			}
			else
			{
				cout << "查无此人" << endl;
			}

		}break;
		case 'C':
		{
			cout << "请输入要解散的家庭的人的姓名: ";
			string name;
			cin >> name;
			treeNode<family>* result;
			if (family_tree.find(family_tree.the_root(), name, result))
			{
				cout << name << "的第一代子孙是: ";
				treeNode<family>*tempt = result;
				tempt = tempt->left;
				while (tempt)
				{
					cout << tempt->data.key() << "   ";
					tempt = tempt->right;
				}
				cout << endl;
				treeNode<family>* father;
				int outcome = family_tree.find_father(family_tree.the_root(),result, father);
				if (outcome == 1)
				{
					father->left = result->right;
				}
				else if (outcome == 2)
				{
					father->right = result->right;
				}
				family_tree.to_delete(result->left);
				delete result;
			}
			else
			{
				cout << "查无此人" << endl;
			}

		}break;
		case 'D':
		{
			cout << "请输入要更改姓名的人的目前姓名: ";
			string name;
			cin >> name;
			treeNode<family>* result;
			if (family_tree.find(family_tree.the_root(), name, result))
			{
				cout << "请输入更改后的姓名: ";
				string name_to_modify;
				cin >> name_to_modify;
				result->data.name = name_to_modify;
				cout <<name<< "已经更名为" <<name_to_modify<< endl;
			}
			else
			{
				cout << "查无此人" << endl;
			}
		}break;
		case 'E': return 0;
		default:
			break;
		}
		cout << endl << "请选择要执行的操作: ";
	}

	return 0;
}