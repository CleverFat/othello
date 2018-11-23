#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
#include<cstdlib>
using namespace std;
void splash_screen(char map[][8]);
void markMov(char map[][8]);
//标记下一步可以下的点
bool isValidMov(char map[][8],int row,int col);
bool isValidInput(string input,vector<string> valid_set);
//判断每一步输入是否合理，输入为一个输入语句，和一个储存有合理语句的向量
bool isFinalstate(char map[][8]);
//检测是否为终局
int eval(char map[][8]);
