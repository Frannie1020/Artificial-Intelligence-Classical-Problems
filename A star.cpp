#include <iostream>
#include <vector>
#include <string>
#define col 3
#define row 3
#define maxnum 10000
#define maxdistance 10000
using namespace std;
//f(n)=g(n)+h(n);g(n)为当前和目标状态中数字相异的个数，h(n)为当前已经移动的步数 
class node {
public:
	int number[row][col];//数组表示输入输出 
	string str;//表示移动方向上下左右 
	int distances;//g(n)为距离 
	int depth;//h(n)
	int findex;

	node() {

	}
	int dis();//计算并返回distances 
	void voluation(int index);//赋值 
	bool isend();//判断是否为目标状态 
	bool isequal(node q);//当前的节点与节点q是否相等 
};
vector <node> v;//存储节点 
node father, intent;//定义初始状态和目标状态
void node::voluation(int index) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			number[i][j] = v[index].number[i][j];
		}
	}
}
int node::dis() {//g(n) 
	int s = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (number[i][j] != intent.number[i][j]) {
				s = s + 1;
			}
		}
	}
	distances = s;
	return s;
}

bool node::isend() {//判断是否为目标状态 
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (number[i][j] != intent.number[i][j]) {
				return false;
			}
		}
	}
	return true;
}
bool node::isequal(node q) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (number[i][j] != q.number[i][j]) {
				return false;
			}
		}
	}
	return true;
}
bool isexpansive(node &n) {//判断n是否可以扩展，即判断v内是否有节点和n相等
	for (int i = 0; i < v.size(); i++) {
		if (v[i].isequal(n)) {
			return false;
		}
	}
	return true;
}
bool isempty() {//判断v是否还有可访问的点
	for (int i = 0; i < v.size(); i++) {
		if (v[i].distances != maxnum) {
			return false;
		}
	}
	return true;
}
int find_min() {//在v中寻找评估值最小的节点作为下一步的扩展节点
	int min_x = maxnum;
	int index_min;
	for (int i = 0; i < v.size(); i++) {
		if (v[i].distances + v[i].depth < min_x) {
			index_min = i;
			min_x = v[i].distances + v[i].depth;
		}
	}
	return index_min;
}
void swap_t(int &a, int &b) {
	int t;
	t = a;
	a = b;
	b = t;
}
void breath(int index) {
	int index_x, index_y;
	int flag = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (v[index].number[i][j] == 0) {//寻找空格的位置[index_x][index_y]
				index_x = i;
				index_y = j;
				flag = 1;
				break;
			}
			if (flag == 1) {
				break;
			}
		}
	}
	node upnode, downnode, leftnode, rightnode;//方向 
	upnode.voluation(index);
	downnode.voluation(index);
	leftnode.voluation(index);
	rightnode.voluation(index);
	int up_dis = maxdistance;
	int down_dis = maxdistance;
	int left_dis = maxdistance;
	int right_dis = maxdistance;
	if (index_x > 0) {
		swap_t(upnode.number[index_x][index_y], upnode.number[index_x - 1][index_y]);
		if (isexpansive(upnode)) {
			up_dis = upnode.dis();
			upnode.findex = index;
			upnode.depth = v[index].depth + 1;
			upnode.str = "down";
			v.push_back(upnode);
		}
	}
	if (index_x < 2) {
		swap_t(downnode.number[index_x][index_y], downnode.number[index_x + 1][index_y]);
		if (isexpansive(downnode)) {
			down_dis = downnode.dis();
			downnode.findex = index;
			downnode.depth = v[index].depth + 1;
			downnode.str = "up";
			v.push_back(downnode);
		}
	}
	if (index_y > 0) {
		swap_t(leftnode.number[index_x][index_y], leftnode.number[index_x][index_y - 1]);
		if (isexpansive(leftnode)) {
			left_dis = leftnode.dis();
			leftnode.findex = index;
			leftnode.depth = v[index].depth + 1;
			leftnode.str = "right";
			v.push_back(leftnode);
		}
	}
	if (index_y < 2) {
		swap_t(rightnode.number[index_x][index_y], rightnode.number[index_x][index_y + 1]);
		if (isexpansive(rightnode)) {
			right_dis = rightnode.dis();
			rightnode.findex = index;
			rightnode.depth = v[index].depth + 1;
			rightnode.str = "left";
			v.push_back(rightnode);
		}
	}
	v[index].distances = maxnum;
}
ostream& operator<<(ostream& os, node& no)
{
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++)
			os << no.number[i][j] << ' ';
		os << endl;
	}
	return os;
}
void print(int index, vector<node>& rstep_v)//利用rstep_v输出从index到达目标节点的过程
{

	rstep_v.push_back(v[index]);
	index = v[index].findex;
	while (index != 0)
	{
		rstep_v.push_back(v[index]);//把过程中所有的节点保存在rstep_v中
		index = v[index].findex;
	}


	for (int i = rstep_v.size() - 1; i >= 0; i--) {
		cout << "Step " << rstep_v.size() - i <<":"<< endl;
		node p = rstep_v[i];
		cout << p.str << endl;
		cout << p << endl;
	}
}
void process() {
	while (1) {
		int t = 0;
		if (isempty()) {
			cout << "error" << endl;
			exit(-1);
		}

		else {
			int best = find_min();
			node temp = v[best];
			if (temp.isend()) {
				t = 1;
				vector<node> rstep_v;
				print(best, rstep_v);

			}
			else {
				breath(best);
			}
		}
		if (t)
			break;
	}
}

int main()
{
	cout << "输入起始数据:" << endl;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cin >> father.number[i][j];
		}
	}
	father.findex = 0;
	father.depth = 0;
	cout << "输入目标数据:" << endl;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cin >> intent.number[i][j];
		}
	}
	cout<<"移动过程："<<endl; 
	v.push_back(father);
	process();
	cout<<"移动结束!"<<endl; 
	return 0;
}
