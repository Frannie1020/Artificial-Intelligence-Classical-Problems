#include<Windows.h>
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include <fstream>
#include<map>
#include <algorithm>
#include<cmath>

using namespace std;

struct Node
{
	double weight[10];
	double wb;
	double values;
	double t;
	double dev;
}input_layer[4], hidden_layer[10], output_layer[3];//定义向量：输入层，隐藏层和输出层 

struct temp
{
	double element[4];
	int title;
}ele[75];
//定义全局变量 
int num_input = 4;
int num_hidden = 10;
int num_output = 3;
double avg = 0;
double space = 0.01;//梯度下降过程中的学习率 
double standard = 0;
int num = 0;
int num2 = 0;
int num_eq = 0;
int cmptit[75];
double ans[10];
int snum = 0;
//初始化权重 ，生成(-1,+1)区间的随机数 
void init(Node hidden_layer[], Node output_layer[]) {
	
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 4; j++) {   
			hidden_layer[i].weight[j] = (rand() % 200 - 100) / 100.0;
		}
		hidden_layer[i].wb = 1;
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 10; j++) {  
			output_layer[i].weight[j] = (rand() % 200 - 100) / 100.0;
		}
		output_layer[i].wb = 1;
	}
}
//独热编码 
void judgement(temp ele[], Node output_layer[]) {
	if (ele[num].title == 0) {
		output_layer[0].t = 1;
		output_layer[1].t = 0;
		output_layer[2].t = 0;
	}
	else if (ele[num].title == 1) {
		output_layer[0].t = 0;
		output_layer[1].t = 1;
		output_layer[2].t = 0;
	}
	else if (ele[num].title == 2) {
		output_layer[0].t = 0;
		output_layer[1].t = 0;
		output_layer[2].t = 1;
	}
}

//计算s型激跃函数
void Cnt_sigmoid(Node hidden_layer[], int num_hidden, Node input_layer[], int num_input) {

	double m;
	for (int i = 0; i < num_hidden; i++) {
		m = 0;
		for (int j = 0; j < num_input; j++) {
			m += hidden_layer[i].weight[j] * input_layer[j].values;
		}
		hidden_layer[i].values = 1.0 / (1 + exp(-(m + hidden_layer[i].wb)));
	}
}
//隐藏层误差项计算 
void Cnt_Hidden_deviation(Node hidden_layer[], int num_hidden, Node output_layer[], int num_output) {
	double m;
	for (int i = 0; i < num_hidden; i++) {
		m = 0;
		for (int j = 0; j < num_output; j++) {
			m += output_layer[j].weight[i] * output_layer[j].dev;
		}
		hidden_layer[i].dev = hidden_layer[i].values*
			(1 - hidden_layer[i].values)*m;
	}
}

//更新隐藏层权重 
void re_nodeWeight(Node output_layer[], int num_output, Node hidden_layer[], int num_hidden) {

	for (int i = 0; i < num_output; i++) {
		for (int j = 0; j < num_hidden; j++) {
			output_layer[i].weight[j] = output_layer[i].weight[j] +
				space*output_layer[i].dev*hidden_layer[j].values;
		}
	}
}
//输出层误差项计算 
void Cnt_Output_deviation(Node output_layer[], int num_output) {
	for (int i = 0; i < num_output; i++) {
		output_layer[i].dev = output_layer[i].values*
			(1 - output_layer[i].values)*(output_layer[i].t - output_layer[i].values);
	}
}
//更新输出权重 
void re_b_Weight(Node output_layer[], int num_output) {

	for (int i = 0; i < num_output; i++) {
		output_layer[i].wb = output_layer[i].wb + space*output_layer[i].dev;
	}
}

//训练数据 
void Train(temp ele[]) {
	for (int y = 0; y < 75; y++) {
		judgement(ele, output_layer);
		for (int i = 0; i<4; i++)
			input_layer[i].values = ele[num].element[i];
		Cnt_sigmoid(hidden_layer, num_hidden, input_layer, num_input);
		Cnt_sigmoid(output_layer, num_output, hidden_layer, num_hidden);
		Cnt_Output_deviation(output_layer, num_output);
		Cnt_Hidden_deviation(hidden_layer, num_hidden, output_layer, num_output);
		re_nodeWeight(output_layer, num_output, hidden_layer, num_hidden);
		re_nodeWeight(hidden_layer, num_hidden, input_layer, num_input);
		re_b_Weight(output_layer, num_output);
		re_b_Weight(hidden_layer, num_hidden);
		num++;
	}
}

//分类：预测测试集中样本的标签 
void Cmp_Y(Node output_layer[], int num_output) {

	double max = -1;
	int tit = 0;
	for (int i = 0; i < num_output; i++) {
		if (max <= output_layer[i].values) {
			max = output_layer[i].values;
			tit = i;
		}
	}

	for (int i = 0; i < num_output; i++) {
		if (tit == i)
		output_layer[i].t = 1;
		else
		output_layer[i].t = 0;
	;
	}
   // for (int i = 0; i < 75; i++) { 
	if (output_layer[0].t == 1 && output_layer[1].t == 0 && output_layer[2].t == 0) {
		cmptit[num2] = 0;
	//	cout<<i+1<<":"<<cmptit[num2]<<endl ;
	}
	//	for (int i = 0; i <75; i++) { 
	if (output_layer[0].t == 0 && output_layer[1].t == 1 && output_layer[2].t == 0) {
		cmptit[num2] = 1;
	//	cout<<i+1<<":"<<cmptit[num2]<<endl;
	}
	//	for (int i = 0; i <75; i++) { 
	if (output_layer[0].t == 0 && output_layer[1].t == 0 && output_layer[2].t == 1) {
		cmptit[num2] = 2;
	//	cout<<i+1<<":"<<cmptit[num2]<<endl ;
	}
}
//测试集 
void Test(temp ele[]) {
	for (int i = 0; i<4; i++)
		input_layer[i].values = ele[num2].element[i];
	Cnt_sigmoid(hidden_layer, num_hidden, input_layer, num_input);
	Cnt_sigmoid(output_layer, num_output, hidden_layer, num_hidden);
	Cmp_Y(output_layer, num_output);
	num2++;
}
//准确率计算 
void Cmp_num() {
	for (int i = 0; i < 75; i++) {
		if (cmptit[i] == ele[i].title) {
			num_eq++;
		}
	}
	double emmmm = (double)(num_eq) / 75.0;//准确率计算 
	cout << "accuracy：" << emmmm << endl;
	ans[snum] = emmmm;
	snum++;
	avg += emmmm;
}
 
int main() {
	for (int y = 0; y < 10; y++) {
		cout << "进行第" << y + 1 << "次独立训练" << endl;
		freopen("Iris-train.txt", "r", stdin);
		for (int i = 0; i < 75; i++) {
			cin >> ele[i].element[0] >> ele[i].element[1] >> ele[i].element[2] >> ele[i].element[3] >> ele[i].title;//依次读取训练集的四个特征和实际类别 
		}
		int number = 0;
		init(hidden_layer, output_layer);
		for (int i = 0; i < 900; i++) {
			Train(ele);
			num = 0;
		}
		freopen("Iris-test.txt", "r", stdin);
		for (int i = 0; i < 75; i++) {
    	cin >> ele[i].element[0] >> ele[i].element[1] >> ele[i].element[2] >> ele[i].element[3] >> ele[i].title;//依次读取测试集的四个特征和实际类别 
		}
		for (int i = 0; i<75; i++)
		Test(ele);
		Cmp_num();
		num = 0;//记录训练第几组数据
		num2 = 0;//记录测试数据第几组
		num_eq = 0;//预测值与答案相等的个数
	}
	cout << "average accuracy：" << avg / 10.0 << endl;
	double mm = avg / 10.0;
	for (int i = 0; i < 10; i++) {
	standard += (ans[i] - mm)*(ans[i] - mm);
	}
	cout << "标准差：" << sqrt(standard) << endl;
	Sleep(5000);
	system("pause");
	return 0;
}

