#include <iostream>
#include <vector>

using namespace std;


template<typename T> 
class Heap
{
public:
	Heap()=default;
	~Heap()=default;
	bool deal_min(T &result);
	bool add_ele(const T& to_add);

private:
	vector<T> hp;
	void up_change();
	void down_change(int position);
};

template<typename T>
void Heap<T>::up_change()
{
	int current = hp.size()-1;
	int father = 0;
	int tempt = 0;
	bool first_time_root = true;
	do
	{
		father = (int)(current / 2);
		if (hp.at(father) > hp.at(current))
		{
			tempt = hp.at(father);
			hp.at(father) = hp.at(current);
			hp.at(current) = tempt;
		}
		if (father == 0)
		{
			first_time_root = false;
		}
		current = father;
	} while ((int)(current / 2) >= 0 && first_time_root);
}

template<typename T>
void Heap<T>::down_change(int position)
{
	int where_now = position;
	int left = where_now * 2 + 1;
	int right = where_now * 2 + 2;
	int smaller_son = 0;
	int tempt = 0;
	while (left<hp.size())
	{
		if (right < hp.size())
		{
			if (hp.at(left) < hp.at(right))
			{
				smaller_son = left;
			}
			else
			{
				smaller_son = right;
			}
		}
		else
		{
			smaller_son = left;
		}
		if (hp.at(smaller_son) < hp.at(where_now))
		{
			tempt = hp.at(where_now);
			hp.at(where_now) = hp.at(smaller_son);
			hp.at(smaller_son) = tempt;//swap
		}
		where_now = smaller_son;
		left = where_now * 2 + 1;
		right = where_now * 2 + 2;
	}
}
template<typename T>
bool Heap<T>::add_ele(const T& to_add)
{
	hp.push_back(to_add);
	up_change();
	return true;
}

template<typename T>
bool Heap<T>::deal_min(T &result)
{
	if (hp.empty())
	{
		return false;
	}
	else
	{
		result = hp.front();
		hp.front() = hp.back();
		hp.pop_back();
		for (int i = 0; 2 * i + 1 < hp.size(); i++)
		{
			down_change(i);
		}
		return true;
	}
}



int main()
{
	Heap<int> target;
	int num;
	cin >> num;
	for (int i = 0; i < num; i++)
	{
		int tempt;
		cin >> tempt;
		target.add_ele(tempt);
	}
	int cur_min;
	int next_min;
	int sum = 0;
	int current_sum = 0;

	while (target.deal_min(cur_min)&&target.deal_min(next_min))
	{
		current_sum = cur_min + next_min;
		target.add_ele(current_sum);
		sum += current_sum;
	}
	
	cout << sum;

	return 0;
}