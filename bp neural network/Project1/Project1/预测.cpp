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
}input_layer[4], hidden_layer[10], output_layer[3];//��������������㣬���ز������� 

struct temp
{
	double element[4];
	int title;
}ele[75];
//����ȫ�ֱ��� 
int num_input = 4;
int num_hidden = 10;
int num_output = 3;
double avg = 0;
double space = 0.01;//�ݶ��½������е�ѧϰ�� 
double standard = 0;
int num = 0;
int num2 = 0;
int num_eq = 0;
int cmptit[75];
double ans[10];
int snum = 0;
//��ʼ��Ȩ�� ������(-1,+1)���������� 
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
//���ȱ��� 
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

//����s�ͼ�Ծ����
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
//���ز��������� 
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

//�������ز�Ȩ�� 
void re_nodeWeight(Node output_layer[], int num_output, Node hidden_layer[], int num_hidden) {

	for (int i = 0; i < num_output; i++) {
		for (int j = 0; j < num_hidden; j++) {
			output_layer[i].weight[j] = output_layer[i].weight[j] +
				space*output_layer[i].dev*hidden_layer[j].values;
		}
	}
}
//������������� 
void Cnt_Output_deviation(Node output_layer[], int num_output) {
	for (int i = 0; i < num_output; i++) {
		output_layer[i].dev = output_layer[i].values*
			(1 - output_layer[i].values)*(output_layer[i].t - output_layer[i].values);
	}
}
//�������Ȩ�� 
void re_b_Weight(Node output_layer[], int num_output) {

	for (int i = 0; i < num_output; i++) {
		output_layer[i].wb = output_layer[i].wb + space*output_layer[i].dev;
	}
}

//ѵ������ 
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

//���ࣺԤ����Լ��������ı�ǩ 
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
//���Լ� 
void Test(temp ele[]) {
	for (int i = 0; i<4; i++)
		input_layer[i].values = ele[num2].element[i];
	Cnt_sigmoid(hidden_layer, num_hidden, input_layer, num_input);
	Cnt_sigmoid(output_layer, num_output, hidden_layer, num_hidden);
	Cmp_Y(output_layer, num_output);
	num2++;
}
//׼ȷ�ʼ��� 
void Cmp_num() {
	for (int i = 0; i < 75; i++) {
		if (cmptit[i] == ele[i].title) {
			num_eq++;
		}
	}
	double emmmm = (double)(num_eq) / 75.0;//׼ȷ�ʼ��� 
	cout << "accuracy��" << emmmm << endl;
	ans[snum] = emmmm;
	snum++;
	avg += emmmm;
}
 
int main() {
	for (int y = 0; y < 10; y++) {
		cout << "���е�" << y + 1 << "�ζ���ѵ��" << endl;
		freopen("Iris-train.txt", "r", stdin);
		for (int i = 0; i < 75; i++) {
			cin >> ele[i].element[0] >> ele[i].element[1] >> ele[i].element[2] >> ele[i].element[3] >> ele[i].title;//���ζ�ȡѵ�������ĸ�������ʵ����� 
		}
		int number = 0;
		init(hidden_layer, output_layer);
		for (int i = 0; i < 900; i++) {
			Train(ele);
			num = 0;
		}
		freopen("Iris-test.txt", "r", stdin);
		for (int i = 0; i < 75; i++) {
    	cin >> ele[i].element[0] >> ele[i].element[1] >> ele[i].element[2] >> ele[i].element[3] >> ele[i].title;//���ζ�ȡ���Լ����ĸ�������ʵ����� 
		}
		for (int i = 0; i<75; i++)
		Test(ele);
		Cmp_num();
		num = 0;//��¼ѵ���ڼ�������
		num2 = 0;//��¼�������ݵڼ���
		num_eq = 0;//Ԥ��ֵ�����ȵĸ���
	}
	cout << "average accuracy��" << avg / 10.0 << endl;
	double mm = avg / 10.0;
	for (int i = 0; i < 10; i++) {
	standard += (ans[i] - mm)*(ans[i] - mm);
	}
	cout << "��׼�" << sqrt(standard) << endl;
	Sleep(5000);
	system("pause");
	return 0;
}

