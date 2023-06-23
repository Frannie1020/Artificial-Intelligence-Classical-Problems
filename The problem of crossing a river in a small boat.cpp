#include <iostream>
#include <vector>
#include <stdio.h>
using namespace std;
 
vector<string> visit;//数据库路径函数 
 
int numofchurch, numofwild, boatload;     //分别表示传教士总人数M，野人总人数C，船载客量B
int totalanswer = 0;                      //解法数目
 
bool check(int M, int C, int flag)//判断非法情况的函数 
{
    if((flag!=0) && (flag!=1))
        return false;
    if(M<0 || C<0 || numofchurch-M<0 || numofwild-C<0)           //2：起始和最终人数都不得小于0
        return false;
    if((M&&M<C) || ((numofchurch-M)&&(numofchurch-M)<(numofwild-C)))               //3：任何一岸有传教士且传教士人数小于野人人数
        return false;
    char s[30];
    sprintf(s, "（%d %d %d）", M,C,flag);
    for(int i=0; i<visit.size(); i++)          //4：此路径情况之前出现过
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
        cout<<"第"<<totalanswer<<"种方法："<<endl<<endl;
        for(int i=0; i<visit.size(); i++)
            cout<<visit[i]<<endl<<endl;
        return;
    }
 
    int i, j, k;//过程递归算法 
    for(i=boatload; i>0;i--)          //船本次载了i个人
    {
        for(j=i; j>=0;j--)        //j为运送的传教士人数
        {
            k = i-j;                 //k为运送的野人数
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
    int flag=1;                         //flag=1表示船在左岸
    char s[30];
    cout<<"输入传教士数、野人数和船载客量："<<endl;
    cin>>numofchurch>>numofwild>>boatload;
    sprintf(s, "（%d %d %d）", numofchurch,numofwild,flag);
    visit.push_back(s);
    path(numofchurch, numofwild, flag);
    if(totalanswer!=0)
        cout<<"Total answer: "<<totalanswer<<endl;
    else
        cout<<"FAIL!"<<endl;
}
