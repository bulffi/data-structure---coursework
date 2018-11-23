#include<iostream>
#include<vector>
#include<list>
using namespace std;


class edge
{
public:
	edge()=default;
	~edge()=default;
	friend ostream& operator<<(ostream& out, const edge & target);
	friend istream& operator>>(istream& in, edge& target);
	int get_from() const { return from; }
	int get_to() const { return to; }
	int get_cost() const { return cost; }
	//bool operator<(const edge& target)
	//{
	//	return cost < target.get_cost();
	//}
private:
	int from;
	int to;
	int cost;
};

istream& operator>>(istream& in, edge& target)
{
	in >> target.from >> target.to >> target.cost;
	--target.from;
	--target.to;
	return in;

}
ostream& operator<<(ostream& out, const edge & target)
{
	out << target.from+1 <<" -> "<< target.to+1;
	return out;
}


class graph
{
public:
	graph(int num_ver);
	~graph()=default;
	bool add_edge(const edge& target);
	bool topo_sort();
	bool find_time_space();
	bool find_critical();
	int get_min_time() { return minia_time; }
	void show_citical()
	{
		for (auto way : critical_road)
		{
			cout << way << endl;
		}
	}
private:
	vector<list<edge>> my_graph;
	vector<int> num_in;
	size_t num_vertex;
	vector<int> topo_sorted;
	vector<int> early_time;
	vector<int> late_time;
	vector<edge> critical_road;
	int minia_time;
};
bool graph::find_critical()
{
	for (size_t i = 0; i < num_vertex; i++)
	{
		for (auto way : my_graph[i])
		{
			if (early_time[i] == late_time[way.get_to()] - way.get_cost())
			{
				critical_road.push_back(way);
			}
		}
	}
	return true;
}
bool graph::find_time_space()
{
	for (size_t i = 0; i < my_graph.size(); i++)
	{
		int k = topo_sorted[i];
		for (auto way : my_graph[k])
		{
			if (early_time[k] + way.get_cost() > early_time[way.get_to()])
			{
				early_time[way.get_to()] = early_time[k] + way.get_cost();
			}
		}

	}
	minia_time = early_time.back();
	for (size_t i = 0; i < my_graph.size(); i++)
	{
		late_time[i] = INT_MAX;
	}
	late_time[my_graph.size()-1] = early_time[my_graph.size()-1];
	for (int i = my_graph.size() - 2; i >= 0; i--)
	{
		int k = topo_sorted[i];
		for (auto way : my_graph[k])
		{
			if (late_time[k] > late_time[way.get_to()] - way.get_cost())
			{
				late_time[k] = late_time[way.get_to()] - way.get_cost();
			}
		}
	}
	return true;

}
bool graph::topo_sort()
{
	int num_been_sorted = 0;
	vector<int> tempt_stack;
	vector<bool> already_in;
	already_in.resize(num_vertex);
	while (num_been_sorted<num_vertex)
	{
		for (size_t i = 0; i < num_vertex; i++)
		{
			if (num_in[i] == 0&&!already_in[i])
			{
				tempt_stack.push_back(i);
			}
		}
		if (tempt_stack.empty())
		{
			return false;
		}
		else
		{
			int tempt = tempt_stack.back();
			topo_sorted.push_back(tempt);
			tempt_stack.pop_back();
			already_in[tempt] = true;
			for (auto way : my_graph[tempt])
			{
				num_in[way.get_to()]--;
			}
			num_been_sorted++;
		}
	}
	return true;
}
bool graph::add_edge(const edge& target)
{
	if (target.get_from() >= 0 && target.get_to() < num_vertex)
	{
		for (auto way : my_graph[target.get_from()])
		{
			if (way.get_to() == target.get_to())
			{
				return false;
			}
		}
		my_graph[target.get_from()].push_front(target);
		num_in[target.get_to()]++;
		return true;
	}
	return false;
}
graph::graph(int number_vertex)
{
	my_graph.resize(number_vertex);
	num_in.resize(number_vertex);
	early_time.resize(number_vertex);
	late_time.resize(number_vertex);
	for (size_t i = 0; i < number_vertex; i++)
	{
		num_in[i] = 0;
	}
	num_vertex = number_vertex;
}
bool comp(edge fir, edge second)
{
	return fir.get_cost() < second.get_cost();
}

int main()
{
	int num_vertex;
	int num_egde;
	cin >> num_vertex >> num_egde;
	graph test(num_vertex);
	edge tempt;
	for (int i = 0; i < num_egde; i++)
	{
		cin >> tempt;
		test.add_edge(tempt);
	}
	if (test.topo_sort())
	{
		test.find_time_space();
		test.find_critical();
		cout << test.get_min_time() << endl;
		test.show_citical();
	}
	else
	{
		cout << 0 << endl;
	}

	return 0;
}