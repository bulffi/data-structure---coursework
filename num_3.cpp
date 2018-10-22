#include<iostream>
#include<vector>
using namespace std;

struct Direction
{
	int row_pos;
	int col_pos;
	Direction(int x, int y)
	{
		row_pos = x;
		col_pos = y;
	}
};
struct Point
{
	int row;
	int col;
	Point(int x,int y)
	{
		row = x;
		col = y;
	}
	Point()
	{
		row = -1;
		col = -1;
	}
};
Direction directions[8] = { {0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{1,
-1} };
class Maze
{
	int **ptr_maze = nullptr;/// 0-NO 1-YES
	int **ptr_have_been = nullptr;/// 0-NO 1-YES
	Point start;
	Point end;
	int row;
	int col;
	vector<Point> way_out;

public:
	friend istream& operator>>(istream&in, Maze& target);
	bool find_way_out();
	void show_me_the_way();
	~Maze()
	{
		for (int i = 0; i < row; i++)
		{
			delete []ptr_maze[i];
			delete []ptr_have_been[i];
		}
		delete[]ptr_have_been;
		delete[]ptr_maze;
	}
};

void Maze::show_me_the_way()
{
	for (auto pnt : way_out)
	{
		cout << "( " << pnt.row << " , " << pnt.col << " )" << endl;
	}
}
bool Maze::find_way_out()
{
	Point curen_posi = start;
	int dire = 0;
	ptr_have_been[curen_posi.row][curen_posi.col] = 1;
	way_out.emplace_back(curen_posi.row, curen_posi.row);
	do
	{
		int dire = 0;
		while (dire<8)
		{
			Point next_to_go;
			next_to_go.row = curen_posi.row + directions[dire].row_pos;
			next_to_go.col = curen_posi.col + directions[dire].col_pos;
			if (ptr_maze[next_to_go.row][next_to_go.col] && (!ptr_have_been[next_to_go.
row][next_to_go.col]))
			{
				way_out.emplace_back(next_to_go.row, next_to_go.col);
				if (next_to_go.col == end.col&&next_to_go.row == end.row)
				{
					return true;
				}
				ptr_have_been[next_to_go.row][next_to_go.col] = 1;
				curen_posi = next_to_go;
				dire = 0;
				continue;
			}
			dire++;
		}
		curen_posi = way_out.back();
		way_out.pop_back();
	} while (!way_out.empty());


	return false;
}

istream& operator>>(istream&in, Maze& target)
{
	cout << "请问您的迷宫有几行几列（请先输入行数 再输入列数）" << endl;
	int col;
	int row;
	cin >> row >> col;
	target.ptr_maze = new int*[row+2];
	for (int i = 0; i < row+2; i++)
	{
		target.ptr_maze[i] = new int[col+2];
	}
	for (int i = 0; i < row+2; i++)
	{
		for (int j = 0; j < col+2; j++)
		{
			target.ptr_maze[i][j] = 0;
		}
	}

	target.ptr_have_been = new int*[row + 2];
	for (int i = 0; i < row + 2; i++)
	{
		target.ptr_have_been[i] = new int[col + 2];
	}
	for (int i = 0; i < row + 2; i++)
	{
		for (int j = 0; j < col + 2; j++)
		{
			target.ptr_have_been[i][j] = 0;
		}
	}


	cout << "
输入您的迷宫时请注意，数字0代表不可经过，数字1代表可经过！请在相邻的两个数字之间插入一个空格！" << endl;	
	for (int i = 1; i <= row; i++)
	{
		printf("请输入第%d行\n", i);
		for (int j = 1; j <= col; j++)
		{
			cin >> target.ptr_maze[i][j];
		}
	}


	cout << "请输入起点" << endl;
	cin >> target.start.row >> target.start.col;
	while (!target.ptr_maze[target.start.row][target.start.col])
	{
		cout << "您输入的起点不是有效起点" << endl;
		cout << "请重新输入起点" << endl;
		cin >> target.start.row >> target.start.col;
	}
	cout << "请输入终点" << endl;			

	cin >> target.end.row >> target.end.col;
	while (!target.ptr_maze[target.end.row][target.end.col])
	{
		cout << "您输入的不是有效终点" << endl;
		cout << "请重新输入终点" << endl;
		cin >> target.end.row >> target.end.col;
	}


	return in;
}


int main()
{
	Maze maze;
	cin >> maze;
	if (maze.find_way_out())
	{
		maze.show_me_the_way();
	}
	else
	{
		cout << "no way out" << endl;
	}
	return 0;
}