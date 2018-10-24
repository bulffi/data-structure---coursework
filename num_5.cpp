#include<iostream>
#include<list>

using namespace std;

int main()
{
	list<int> A_line;
	list<int> B_line;
	int number;
	int tempt;
	cin >> number;
	for (int i = 0; i < number; i++)
	{
		cin >> tempt;
		if (tempt % 2)
		{
			A_line.push_back(tempt);
		}
		else
		{
			B_line.push_back(tempt);
		}
	}
	while (A_line.size()>=2 && B_line.size())
	{
		int A_out;
		int B_out;
		for (size_t i = 0; i < 2; i++)
		{
			A_out = A_line.front();
			cout << A_out<<" ";
			A_line.pop_front();
		}
		B_out = B_line.front();
		cout << B_out<<" ";
		B_line.pop_front();
	
	}
	for (auto client : A_line)
	{
		cout << client<<" ";
	}
	for (auto client : B_line)
	{
		cout << client<<" ";
	}

	return 0;
}