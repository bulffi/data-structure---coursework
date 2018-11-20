#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<ostream>
#include<istream>
#include<algorithm>
using namespace std;


class edge
{
public:
	edge()=default;
	~edge()=default;
	friend ostream& operator<<(ostream& out, const edge & target);
	friend istream& operator>>(istream& in, edge& target);
	string get_from() const { return from; }
	string get_to() const { return to; }
	int get_cost() const { return cost; }
	//bool operator<(const edge& target)
	//{
	//	return cost < target.get_cost();
	//}
private:
	string from;
	string to;
	int cost;
};

istream& operator>>(istream& in, edge& target)
{
	in >> target.from >> target.to >> target.cost;
	return in;

}
ostream& operator<<(ostream& out, const edge & target)
{
	out << target.from << "-<" << target.cost << ">->" << target.to;
	return out;
}


class graph
{
public:
	graph()=default;
	~graph()=default;
	bool add_new_edge(const edge& target);
	bool find_minia();
	vector<edge> get_minia() const { return minia_tree; }
	void set_first_name(string name) { the_first_name = name; }
private:
	map< string, vector<edge>> my_graph; // name < to , cost >
	map< string, bool> if_in_set; //judge if in
	vector<edge> minia_tree; //outcome
	string the_first_name;

};

bool comp(edge fir, edge second)
{
	return fir.get_cost() < second.get_cost();
}
bool graph::find_minia()
{
	int num_in_set = 1;
	auto current = my_graph[the_first_name];
	if_in_set[the_first_name] = true;
	int min_cost = INT_MAX;
	edge best_choice;
	vector<edge> waiting;
	while (num_in_set < my_graph.size())
	{
		for (auto way : current)
		{
			if (!if_in_set[way.get_to()]|| way.get_to()==the_first_name)
			{
				waiting.push_back(way);
			}
		}
		sort(waiting.begin(), waiting.end(),comp);
		for (auto fir=waiting.begin();fir<waiting.end();fir++)
		{
			if (waiting.empty())
			{
				return false;
			}
			if (!if_in_set[(*fir).get_to()])
			{
				best_choice = *fir;
				waiting.erase(fir);
				break;
			}
			
		}
		minia_tree.push_back(best_choice);
		if_in_set[best_choice.get_to()] = true;
		current = my_graph[best_choice.get_to()];
		num_in_set++;
	}
	
	return true;
}

bool graph::add_new_edge(const edge& target)
{
	for (auto way : my_graph[target.get_from()])
	{
		if (way.get_to() == target.get_to())
		{
			return false;
		}
	}
	my_graph[target.get_from()].push_back(target);
	my_graph[target.get_to()].push_back(target);
	if_in_set[target.get_from()] = false;
	if_in_set[target.get_to()] = false;
	return true;

}

int main()
{
	edge tempt;
	graph neighbor;
	bool if_first = true;
	cout << "**              电网造价模拟系统               **" << endl;
	cout << "================================================" << endl;
	cout << "**           A---输入电网的边                  **" << endl;
	cout << "**           B---构造最小生成树                **" << endl;
	cout << "**           C---显示最小生成树                **" << endl;
	cout << "**           E---退出程序                      **" << endl;
	cout << "================================================" << endl;
	char choice;
	cout <<endl << "请选择操作:";
	cin >> choice;
	while (choice != 'E')
	{
		switch (choice)
		{
		case 'A':
		{
			cout << "请输入两个顶点以及边长:（以 ？来命名起点作为结束）";
			while (cin >> tempt)
			{
				if (tempt.get_from() == "?")
				{
					break;
				}
				if (neighbor.add_new_edge(tempt))
				{
					if (if_first)
					{
						neighbor.set_first_name(tempt.get_from());
						if_first = false;
					}
				}
				else
				{
					cerr << "wrong input" << endl;
				}
				cout << "请输入两个顶点以及边长:";
			}
		}break;
		case'B':
		{
			if (neighbor.find_minia())
			{
				cout << "生成Prime最小生成树" << endl;
			}
			else
			{
				cout << "不是连通图" << endl;
			}
		}break;
		case'C':
		{
			cout << "最小生成树的顶点及边为：" << endl << endl;
			for (auto way : neighbor.get_minia())
			{
				cout << way << "      ";
			}
			cout << endl;
		}break;
		default:
			break;
		}
		cout <<endl<< "请选择操作：";
		cin >> choice;
	}
	

	

	
	return 0;
}