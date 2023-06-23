#include <iostream>
#include <vector>
#include <stdio.h>
using namespace std;
 
vector<string> visit;//���ݿ�·������ 
 
int numofchurch, numofwild, boatload;     //�ֱ��ʾ����ʿ������M��Ұ��������C�����ؿ���B
int totalanswer = 0;                      //�ⷨ��Ŀ
 
bool check(int M, int C, int flag)//�жϷǷ�����ĺ��� 
{
    if((flag!=0) && (flag!=1))
        return false;
    if(M<0 || C<0 || numofchurch-M<0 || numofwild-C<0)           //2����ʼ����������������С��0
        return false;
    if((M&&M<C) || ((numofchurch-M)&&(numofchurch-M)<(numofwild-C)))               //3���κ�һ���д���ʿ�Ҵ���ʿ����С��Ұ������
        return false;
    char s[30];
    sprintf(s, "��%d %d %d��", M,C,flag);
    for(int i=0; i<visit.size(); i++)          //4����·�����֮ǰ���ֹ�
        if(s == visit[i])
            return false;
    visit.push_back(s);
    return true;
}
 
void path(int M, int C, int flag)
{
    if((M==0) && (C==0) && (flag==0))
    {
        totalanswer++;
        cout<<"��"<<totalanswer<<"�ַ�����"<<endl<<endl;
        for(int i=0; i<visit.size(); i++)
            cout<<visit[i]<<endl<<endl;
        return;
    }
 
    int i, j, k;//���̵ݹ��㷨 
    for(i=boatload; i>0;i--)          //����������i����
    {
        for(j=i; j>=0;j--)        //jΪ���͵Ĵ���ʿ����
        {
            k = i-j;                 //kΪ���͵�Ұ����
            if(check(M-j, C-k, flag-1))
            {
                path(M-j, C-k, flag-1);
                visit.pop_back();
            }
            else if(check(M+j, C+k, flag+1))
            {
                path(M+j, C+k, flag+1);
                visit.pop_back();
 
 
            }
        }
    }
}
 
 
int main()
{
    int flag=1;                         //flag=1��ʾ������
    char s[30];
    cout<<"���봫��ʿ����Ұ�����ʹ��ؿ�����"<<endl;
    cin>>numofchurch>>numofwild>>boatload;
    sprintf(s, "��%d %d %d��", numofchurch,numofwild,flag);
    visit.push_back(s);
    path(numofchurch, numofwild, flag);
    if(totalanswer!=0)
        cout<<"Total answer: "<<totalanswer<<endl;
    else
        cout<<"FAIL!"<<endl;
}
