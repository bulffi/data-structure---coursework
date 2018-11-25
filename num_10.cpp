#include<cstdlib>
#include<ctime>
#include<iostream>
#include<vector>
#include<chrono>
using namespace std;
class my_int
{
public:
	my_int(int num)
	{
		number = num;
	}
	int get_digit(int dimension)
	{
		int answer;
		int tempt = number;
		int remainder;
		for (size_t i = 0; i < dimension; i++)
		{
			tempt /= 10;
		}
		remainder = tempt % 10;
		return remainder;
	}
	~my_int()=default;

private:
	int number;
};

void swap(vector<int>& target,int pos_left, int pos_right)
{
	int tempt = target[pos_left];
	target[pos_left] = target[pos_right];
	target[pos_right] = tempt;
}
int bubble_sort(vector<int>& target)
{
	int count = 0;
	for (int i = target.size()-1; i > 0; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if (target[j] > target[j + 1])
			{
				swap(target, j, j + 1);
				count++;
			}
		}
	}
	return count;
}
int choose_sort(vector<int>& target)
{
	int count = 0;
	int current_min = INT_MAX;
	int cur_min_pos = 0;
	for (size_t i = 0; i < target.size()-1; i++)
	{
		current_min = target[i];
		cur_min_pos = i;
		for (size_t j = i+1; j < target.size(); j++)
		{
			if (target[j] < current_min)
			{
				current_min = target[j];
				cur_min_pos = j;
			}
		}
		if (cur_min_pos != i)
		{
			swap(target, cur_min_pos, i);
			count++;
		}
	}

	return count;
}
int insert_sort(vector<int>& target)
{
	int count = 0;
	for (size_t i = 1; i < target.size(); i++)
	{
		for (int j = i; j > 0; j--)
		{
			if (target[j] > target[j - 1])
			{
				break;
			}
			else
			{
				swap(target, j, j - 1);
				count++;
			}
		}
	}

	return count;
}
int shell_sort(vector<int>& target)
{
	int count = 0;
	int gap = target.size() / 3;
	while (gap > 1)
	{
		for (size_t i = 0; i < gap; i++)
		{
			for (size_t j = i; j < target.size(); j += gap)
			{
				for (int k = j; k >= gap; k -= gap)
				{
					if (target[k] > target[k - gap])
					{
						break;
					}
					else
					{
						swap(target, k, k - gap);
						count++;
					}
				}
			}
		}
		gap = gap / 3 + 1;
	}
	count += insert_sort(target);
	return count;
}
int my_partition(vector<int>&target, int start, int end,int& count)//count only++!!
{//return the position adjusted
	int to_be_adjust = target[start];
	int cut_point = start;
	for (size_t i = start + 1; i < end; i++)
	{
		if (target[i] >= to_be_adjust)
		{
			;
		}
		else
		{
			cut_point++;
			if (cut_point != i)
			{
				swap(target, cut_point, i);
				count++;
			}
		}
	}
	swap(target, start, cut_point);
	count++;
	return cut_point;

}
void my_quick_sort(vector<int>& target, int start, int end, int& count)
{
	if (end > start)
	{
		int cut_point = my_partition(target, start, end, count);
		my_quick_sort(target, start, cut_point, count);
		my_quick_sort(target, cut_point + 1, end, count);
	}

}
int quick_sort(vector<int>& target)
{
	int count = 0;
	//partition
	my_quick_sort(target, 0, target.size(),count);
	//sort
	//count += insert_sort(target);
	return count;
}
int shitf_down(vector<int>& target, int start,int end)
{
	int count = 0;
	while (start < end)
	{
		int max_child = start * 2 + 1;
		if (max_child > end)
		{
			break;
		}
		if (start * 2 + 2 < end && target[start * 2 + 2] > target[max_child])
		{
			max_child = start * 2 + 2;
		}//choose a min one
		if (target[max_child] > target[start])
		{
			swap(target, max_child, start);
			count++;
		}
		start = max_child;
	}
	
	return count;
}
int heap_sort(vector<int>& target)
{
	int count = 0;
	for (int i = target.size() / 2; i >= 0; i--)
	{
		count += shitf_down(target, i, target.size());
	}
	for (int i = target.size() - 1; i > 0; i--)
	{
		swap(target, 0, i);
		count++;
		count += shitf_down(target, 0, i-1);
	}

	return count;
}
int my_merge(vector<int>& list_1, vector<int>& list_2, int left, int right)
{
	int count = 0;
	int mid = (left + right) / 2;
	for (size_t i = left; i < right; i++)
	{
		list_2[i] = list_1[i];
	}
	int pos_1 = left;
	int pos_2 = mid;
	int cur_pos = left;
	while (pos_1 < mid && pos_2 < right)
	{
		count++;
		if (list_2[pos_1] < list_2[pos_2])
		{
			list_1[cur_pos++] = list_2[pos_1++];
		}
		else 
		{
			list_1[cur_pos++] = list_2[pos_2++];
		}

	}
	while (pos_1<mid)
	{
		count++;
		list_1[cur_pos++] = list_2[pos_1++];
	} 
	while (pos_2<right)
	{
		count++;
		list_1[cur_pos++] = list_2[pos_2++];
	}
	return count;
}

void my_merge_sort(vector<int>& list_1, vector<int>& list_2, int left, int right,int& count)
{
	if (left < right)
	{
		int mid = (left + right) / 2;
		my_merge_sort(list_1, list_2, left, mid, count);
		my_merge_sort(list_1, list_2, mid + 1, right, count);
		count += my_merge(list_1, list_2, left, right);
	}
}
int merge_sort(vector<int>& target)
{
	int count = 0;
	vector<int>list_2 = target;
	my_merge_sort(target, list_2, 0, target.size(), count);
	return count;
}
void LSD_sort(vector<my_int>& target, int digit)
{
	vector<vector<my_int>> link_array;
	link_array.resize(10);
	for (size_t i = 0; i < digit; i++)// 从低位向高位 0-》n-1
	{
		for (size_t j = 0; j < target.size(); j++)
		{
			link_array[target[j].get_digit(i)].push_back(target[j]);
		}
		target.clear();
		for (auto& dig : link_array)
		{
			for (auto num : dig)
			{
				target.push_back(num);
			}
			dig.clear();
		}
	}
}

int main()
{
	cout << "**                   排序算法比较                 **"<< endl;
	cout << "===================================================" << endl;
	cout << "**                  1 --- 冒泡排序                **" << endl;
	cout << "**                  2 --- 选择排序                **" << endl;
	cout << "**                  3 --- 直接插入排序            **" << endl;
	cout << "**                  4 --- 希尔排序                **" << endl;
	cout << "**                  5 --- 快速排序                **" << endl;
	cout << "**                  6 --- 堆排序                  **" << endl;
	cout << "**                  7 --- 归并排序                **" << endl;
	cout << "**                  8 --- 基数排序                **" << endl;
	cout << "**                  9 --- 退出程序                **" << endl;
	cout << "====================================================" << endl;
	cout << endl;
	cout << "请输入要产生的随机数的个数： ";
	int num_rand = 0;
	cin >> num_rand;
	

	int choice;
	cout << "请选择排序算法：           ";
	cin >> choice;
	while (choice!=9)
	{
		switch (choice)
		{
			case 1: 
			{
				vector<int> target;
				srand(static_cast<unsigned int>(time(0)));
				for (size_t i = 0; i < num_rand; i++)
				{
					int current = rand();
					target.push_back(current);
					srand(static_cast<unsigned int>(current));

				}
				int a = RAND_MAX;
				clock_t t1 = clock();
				int count = bubble_sort(target);
				cout << "冒泡排序所用时间：        " << (clock() - t1) * 1.0 / CLOCKS_PER_SEC * 1000 << endl;
				cout << "冒泡排序交换次数：        " << count << endl;
			}break;
			case 2:
			{
				vector<int> target;
				srand(static_cast<unsigned int>(time(0)));
				for (size_t i = 0; i < num_rand; i++)
				{
					int current = rand();
					target.push_back(current);
					srand(static_cast<unsigned int>(current));

				}
				int a = RAND_MAX;
				clock_t t1 = clock();
				int count = choose_sort(target);
				cout << "选择排序所用时间：        " << (clock() - t1) * 1.0 / CLOCKS_PER_SEC * 1000 << endl;
				cout << "选择排序交换次数：        " << count << endl;
			}break;
			case 3:
			{
				vector<int> target;
				srand(static_cast<unsigned int>(time(0)));
				for (size_t i = 0; i < num_rand; i++)
				{
					int current = rand();
					target.push_back(current);
					srand(static_cast<unsigned int>(current));

				}
				int a = RAND_MAX;
				clock_t t1 = clock();
				int count = insert_sort(target);
				cout << "插入排序所用时间：        " << (clock() - t1) * 1.0 / CLOCKS_PER_SEC * 1000 << endl;
				cout << "插入排序交换次数：        " << count << endl;
			}break;
			case 4:
			{
				vector<int> target;
				srand(static_cast<unsigned int>(time(0)));
				for (size_t i = 0; i < num_rand; i++)
				{
					int current = rand();
					target.push_back(current);
					srand(static_cast<unsigned int>(current));

				}
				int a = RAND_MAX;
				clock_t t1 = clock();
				int count = shell_sort(target);
				cout << "希尔排序所用时间：        " << (clock() - t1) * 1.0 / CLOCKS_PER_SEC * 1000 << endl;
				cout << "希尔排序交换次数：        " << count << endl;
			}break;
			case 5:
			{
				vector<int> target;
				srand(static_cast<unsigned int>(time(0)));
				for (size_t i = 0; i < num_rand; i++)
				{
					int current = rand();
					target.push_back(current);
					srand(static_cast<unsigned int>(current));

				}
				int a = RAND_MAX;
				clock_t t1 = clock();
				int count = quick_sort(target);
				cout << "快速排序所用时间：        " << (clock() - t1) * 1.0 / CLOCKS_PER_SEC * 1000 << endl;
				cout << "快速排序交换次数：        " << count << endl;
			}break;
			case 6:
			{
				vector<int> target;
				srand(static_cast<unsigned int>(time(0)));
				for (size_t i = 0; i < num_rand; i++)
				{
					int current = rand();
					target.push_back(current);
					srand(static_cast<unsigned int>(current));

				}
				int a = RAND_MAX;
				clock_t t1 = clock();
				int count = heap_sort(target);
				cout << "堆排序所用时间：          " << (clock() - t1) * 1.0 / CLOCKS_PER_SEC * 1000 << endl;
				cout << "堆排序交换次数：          " << count << endl;
			}break;
			case 7:
			{
				vector<int> target;
				srand(static_cast<unsigned int>(time(0)));
				for (size_t i = 0; i < num_rand; i++)
				{
					int current = rand();
					target.push_back(current);
					srand(static_cast<unsigned int>(current));

				}
				int a = RAND_MAX;
				clock_t t1 = clock();
				int count = merge_sort(target);
				cout << "归并排序所用时间：        " << (clock() - t1) * 1.0 / CLOCKS_PER_SEC * 1000 << endl;
				cout << "归并排序交换次数：        " << count << endl;
			}break;
			case 8:
			{
				vector<my_int> target;
				srand(static_cast<unsigned int>(time(0)));
				for (size_t i = 0; i < num_rand; i++)
				{
					int current = rand();
					target.push_back(current);
					srand(static_cast<unsigned int>(current));

				}
				int a = RAND_MAX;
				clock_t t1 = clock();
				int count = 0;
				LSD_sort(target, 5);
				cout << "基数排序所用时间：        "<<(clock() - t1) * 1.0 / CLOCKS_PER_SEC * 1000 << endl;
				cout << "基数排序不存在交换的过程！ " << count << endl;
			}break;
			default:
				break;
		}
		cout << endl;
		cout << "请选择排序算法：           ";
		cin >> choice;
	}
	
	return 0;
}