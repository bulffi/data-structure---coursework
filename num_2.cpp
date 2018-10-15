#include<iostream>
#include<forward_list>
#include<string>
using namespace std;

bool add_numbers(forward_list<int>& ptr_to_add)
//require a forwardList
{
	int previous = 0;
	int tempt;
	auto inter_to_add = ptr_to_add.before_begin();
	while (cin>>tempt)
	{
		if (tempt >= previous)
		{
			ptr_to_add.insert_after(inter_to_add,tempt);
			previous = tempt;
			inter_to_add++;
		}
		else
		{
			if (tempt == -1)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}
	return 0;

}


int main()
{
	forward_list<int> first;
	forward_list<int> second;
	forward_list<int> target;
	while (true)
	{
		if (add_numbers(first) && add_numbers(second))
		{
			auto itr_first = first.begin();
			auto itr_second = second.begin();
			auto itr_target = target.before_begin();
			while (itr_first!=first.end() && itr_second!=second.end())
			{
				int num_first = *itr_first;
				int num_second = *itr_second;
				if (num_first > num_second)
				{
					itr_second++;
				}
				else if (num_first < num_second)
				{
					itr_first++;
				}
				else
				{
					target.insert_after(itr_target, num_first);
					itr_first++;
					itr_second++;
					itr_target++;
					
				}
			}
			if (!target.empty())
			{
				for (int& ele : target)
				{
					cout << ele <<' ';
				}
				cout << endl;
			}
			else
			{
				cout << "NULL" << endl;
			}
			
			first.clear();
			second.clear();
			target.clear();
			cout << "已经完成处理，是否继续？（y/n）" << endl;
			string option;
			cin >> option;
			if (option.empty())
			{
				exit(0);
			}
			else
			{
				if (option[0] == 'y' || option[0] == 'Y')
				{
					continue;
				}
				else
				{
					exit(0);
				}
			}

		}
		else
		{
			cout << "输入格式有误，请重新输入" << endl;
			first.clear();
			second.clear();
		}
	}




}