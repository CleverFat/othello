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
vector<string> isMovable(char map[][8],int playerID);
//检测是否为终局
int eval(char map[][8]);
int main()
{
    char m[8][8];
    for(int i=0;i<8;i++)
    for(int j=0;j<8;j++)
    m[i][j]=' ';
    m[4][6]='k';
    splash_screen(m);
}


void splash_screen(char map[][8])
{
    cout<<"   1   2   3   4   5   6   7   8  "<<endl;
    for(int i=0;i<8;i++)
    {
        cout<<"  --- --- --- --- --- --- --- ---"<<endl;
        char c='A'+i;
        cout<<c<<"|";
        for(int j=0;j<8;j++)
        {
            cout<<' '<<map[i][j]<<" |";
        }
        cout<<endl;
    }
    cout<<"  --- --- --- --- --- --- --- --- "<<endl;
}
vector<string> markMov(char map[][8])
{
    vector<string> rt;
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(map[i][j]!=' ') continue;
            if(isValidMov(map,i,j))
            {
                string s;
                char c='A';
                s+=(c+i);
                s+=('0'+j);
                rt.push_back(s);
                map[i][j]='*';
            }
        }
    }
    return rt;
}
bool isValidMov(char map[][8],int row,int col)
{
    bool flag=false;
    int mov[8][2]={0,1,1,0,-1,0,0,-1,1,1,1,-1,-1,1,-1,-1};
    for(int i=0;i<8;i++)
    {
        int cur_row=row;
        int cur_col=col;
        cur_row+=mov[i][0];
        cur_col+=mov[i][1];
        if(cur_col>7||cur_row>7||cur_row<0||cur_col<0) continue;
        char tmp=map[cur_row][cur_col];
        if (tmp==' '||tmp=='*') continue;
        if(tmp=='B')
        {
            while(cur_row>0&&cur_col>0&&cur_row<8&&cur_col<8)
            {
                cur_row+=mov[i][0];
                cur_col+=mov[i][1];
                if(map[cur_row][cur_col]=='W')
                {
                    flag=true;
                    return flag;
                }
            }
        }
        else if(tmp=='W')
        {
            while(cur_row>0&&cur_col>0&&cur_row<8&&cur_col<8)
            {
                cur_row+=mov[i][0];
                cur_col+=mov[i][1];
                if(map[cur_row][cur_col]=='B')
                {
                    flag=true;
                    return flag;
                }
            }
        }
    }
    return flag;
}
bool isMovable(char map[][8],int playerID)
{

}