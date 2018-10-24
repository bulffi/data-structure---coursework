#include<iostream>
#include<string>
#include<vector>
#include<istream>
#include<map>
#include<sstream>
using namespace std;
typedef pair<int, int> precedence;
map<char,precedence> order=
{
	{'(',make_pair(1,6)},
	{')',make_pair(6,1)},
	{'+',make_pair(3,2)},
	{'-',make_pair(3,2)},
	{'*',make_pair(5,4)},
	{'/',make_pair(5,4)},///second->out
	{'#',make_pair(0,0)},///first->in

};
int main()
{
	string tempt;
	getline(cin, tempt);
	istringstream target(tempt +'#'+'$');
	vector<char> symbols;
	symbols.push_back('#');
	bool if_opper = true;
	double number_to_calcu = 0;
	do
	{
		char next_sym = target.peek();
		if (next_sym == ' ')
		{
			target.get();
			continue;
		}
		if (next_sym > '0'&& next_sym < '9')
		{
			target >> number_to_calcu;
			cout << number_to_calcu << " ";
			if_opper = false;
		}
		else if (next_sym == '+' || next_sym == '-')
		{
			if ((symbols.back() == '#' || symbols.back() == '(' )&&if_opper)
			{
				target >> number_to_calcu;
				cout << number_to_calcu << " ";
				if_opper = false;
			}
			else
			{
				if (order[next_sym].second > order[symbols.back()].first)
				{
					symbols.push_back(target.get());
				}
				else
				{
					while (order[next_sym].second < order[symbols.back()].first)
					{
						char out_put = symbols.back();
						cout << out_put << " ";
						symbols.pop_back();
					}
				}
			}
		}
		else
		{
			if (order[next_sym].second > order[symbols.back()].first)
			{
				if (next_sym == '(')
				{
					if_opper = true;
				}
				symbols.push_back(target.get());
			}
			else
			{
				while (order[next_sym].second <= order[symbols.back()].first)
				{
					if (order[next_sym].second == order[symbols.back()].first)
					{
						symbols.pop_back();
						break;
					}
					else
					{
						char out_put = symbols.back();
						cout << out_put;
						if (symbols.size() != 2)
						{
							cout << " ";
						}
						symbols.pop_back();
					}
				}
				if (next_sym != ')' && next_sym != '#')
				{
					symbols.push_back(target.get());
				}
				else 
				{
					target.get();
				}
			}
		}

	} while (target.peek()!='$');
	



	return 0;
}