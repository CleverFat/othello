#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
#include<cstdlib>
#include<string>
using namespace std;
const int inf=2<<20;
char playerSB;
char AISB;
int solve(char map[][8],int alpha,int beta,int level,int id);

void splash_screen(char map[][8]);

vector<string> markMov(char map[][8],int playerID);

//标记下一步可以下的点
bool isValidMov(char map[][8],int row,int col,int id);

bool isValidInput(string input,vector<string> valid_set);

//判断每一步输入是否合理，输入为一个输入语句，和一个储存有合理语句的向量
void removeMarks(char map[][8]);

void play(char map[][8]);
void mapreverse(char map[][8],int x,int y,char tar)
{
    int mov[8][2]={0,1,1,0,-1,0,0,-1,1,1,1,-1,-1,1,-1,-1};
    if(tar=='B')
    {
        for(int i=0;i<8;i++)
        {
            int curx=x+mov[i][0];
            int cury=y+mov[i][1];
            int flg=0;
            if(map[curx][cury]!='W') continue;
            while(curx>=0&&cury>=0&&curx<8&&cury<8)
            {
                if(map[curx][cury]=='B')
                {
                    flg=1;
                    break;
                }
                if(map[curx][cury]!='W') break;
                curx+=mov[i][0];
                cury+=mov[i][1];
            }
            curx=x+mov[i][0];
            cury=y+mov[i][1];
            if(flg)
            while(curx>=0&&cury>=0&&curx<8&&cury<8)
            {
                if(map[curx][cury]=='W') map[curx][cury]='B';
                else break;
                curx+=mov[i][0];
                cury+=mov[i][1];
            }
        }
    }
    else if(tar=='W')
    {
        for(int i=0;i<8;i++)
        {
            int curx=x+mov[i][0];
            int cury=y+mov[i][1];
            int flg=0;
            if(map[curx][cury]!='B') continue;
            while(curx>=0&&cury>=0&&curx<8&&cury<8)
            {
                if(map[curx][cury]=='W')
                {
                    flg=1;
                    break;
                }
                if(map[curx][cury]!='B') break;
                curx+=mov[i][0];
                cury+=mov[i][1];
            }
            curx=x+mov[i][0];
            cury=y+mov[i][1];
            if(flg)
            while(curx>=0&&cury>=0&&curx<8&&cury<8)
            {
                if(map[curx][cury]=='B') map[curx][cury]='W';
                else break;
                curx+=mov[i][0];
                cury+=mov[i][1];
            }
        }
    }
}
int Eval(char map[][8]);
int main()
{
    char m[8][8];
    for(int i=0;i<8;i++)
    for(int j=0;j<8;j++)
    m[i][j]=' ';
    m[3][3]='W';
    m[3][4]='B';
    m[4][3]='B';
    m[4][4]='W';
    //m[5][3]='B';
    //mapreverse(m,5,3,'B');
    //vector<string> s=markMov(m,1);
    //splash_screen(m);

    play(m);
    int B_count=0;
    int W_count=0;
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
        if(m[i][j]=='B') B_count++;
        else if(m[i][j]=='W') W_count++;
    cout<<"Black number: "<<B_count<<" White number: "<<W_count<<endl;
    if(B_count>W_count) cout<<"Black has won!\n";
    else cout<<"White has won!\n";
}


void splash_screen(char map[][8])
{
    cout<<"   0   1   2   3   4   5   6   7  "<<endl;
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
vector<string> markMov(char map[][8],int playerID)//0 for black 1 for white
{
    vector<string> rt;
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(map[i][j]!=' ') continue;
            if(isValidMov(map,i,j,playerID))
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
void play(char map[][8])
{
    removeMarks(map);
    int turn=1;
    cout<<"if you want to move first, enter 0, otherwise enter anything but 0\n"; //first mov is B, second is W
    string s;
    cin>>s;
    playerSB='W';
    AISB='B';
    if (s=="0")
    {
        playerSB='B';
        AISB='W';
        turn=0;
    }
    bool flg1=0,flg2=0;
    while(1)
    {
        if(!turn)
        {
            vector<string> posMovs=markMov(map,turn);
            splash_screen(map);
            if(posMovs.size()==0)
            {
                cout<<"No possible move for you, you have to wait\n";
                turn=!turn;
                removeMarks(map);
                flg1=1;
                continue;
            }
            cout<<"It's your turn,possible move has been marked, plz input something like 'A5'\n";
            string ss;
            cin>>ss;
            bool exist=false;
            for(int i=0;i<posMovs.size();i++)
                if(ss==posMovs[i]) exist=true;
            if(exist&&!flg1)
            {
                int i=ss[0]-'A';
                int j=ss[1]-'0';
                cout<<i<<"   "<<j<<endl;
                map[i][j]=playerSB;
                removeMarks(map);
                mapreverse(map,i,j,playerSB);
            }
            else 
            {
                cout<<"Invalid input\n";
                removeMarks(map);
                continue;
            }
        }
        else{
            splash_screen(map);
            cout<<"It's now ai's turn, ai is thinking...";
            char thismap[8][8];
            for(int i=0;i<8;i++)
                for(int j=0;j<8;j++)
                    thismap[i][j]=map[i][j];
            solve(map,-inf,inf,6,turn);
            flg2=false;
            for(int i=0;i<8;i++)
            {
                for(int j=0;j<8;j++)
                {
                    if(thismap[i][j]!=map[i][j]) flg2=true;
                }
            }
            if(!flg2&&flg1) return;
            if(!flg2)
            {
                cout<<"AI pass this round!\n";
                turn=!turn;
                continue;
            }
            flg1=0;
            cout<<"AI has done\n";

        }
        turn = !turn;
    }
}
bool isValidMov(char map[][8],int row,int col,int playerID)
{
    char player=playerID==0?'B':'W';
    char notplayer=playerID==0?'W':'B';
    bool flag=false;
    int mov[8][2]={0,1  ,1,0  ,-1,0  ,0,-1  ,1,1 ,1,-1 ,-1,1 ,-1,-1};
    for(int i=0;i<8;i++)
    {
        int cur_row=row;
        int cur_col=col;
        cur_row+=mov[i][0];
        cur_col+=mov[i][1];
        if(cur_col>7||cur_row>7||cur_row<0||cur_col<0) continue;
        char tmp=map[cur_row][cur_col];
        if (tmp!=notplayer) continue;
        while(cur_row>0&&cur_col>0&&cur_row<8&&cur_col<8)
        {
            cur_row+=mov[i][0];
            cur_col+=mov[i][1];
            if(map[cur_row][cur_col]==player)
            {
                flag=true;
                return flag;
            }
            if(map[cur_row][cur_col]!=notplayer) break;
        }
    }
    return flag;
}
void removeMarks(char map[][8])
{
    for(int i=0;i<8;i++)
    for(int j=0;j<8;j++)
    if(map[i][j]=='*') map[i][j]=' ';
    return ;
}
pair<int,int> string2pair(string s)
{
    int a , b;
    a=s[0]-'A';
    b=s[1]-'0';
    return make_pair(a,b);
}
struct Node{
    char map[8][8];
    int row;
    int col;
    int val;
};
int solve(char map[][8],int alpha,int beta,int level,int turn)
{

    int bestmov=0;
    int val;
    vector<string> possibleMovs=markMov(map,turn);
    if(level==0) return Eval(map);
    if(possibleMovs.size()==0) return(Eval(map));
    removeMarks(map);
    for(int i=0;i<possibleMovs.size();i++)
    {
        char thismap[8][8];
        for(int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
                thismap[i][j]=map[i][j];
        }
        pair<int,int> coord=string2pair(possibleMovs[i]);
        thismap[coord.first][coord.second]=level%2==0?AISB:playerSB;
        removeMarks(thismap);
        mapreverse(thismap,coord.first,coord.second,level%2==0?AISB:playerSB);
        if(level%2==0)
        {
            int res=solve(thismap,alpha,beta,level-1,turn);
            thismap[coord.first][coord.second]='*';
            if(res<alpha) break;
            else
            {

                alpha=res;
                bestmov=i;
            }
        }
        else{
            int res=solve(thismap,alpha,beta,level-1,turn);
            thismap[coord.first][coord.second]='*';
            if(res>beta) break;
            else
            {
                beta=res;
            }
        }
    }
 //   cout<<level<<' '<<turn<<endl;
    if(level==6)
    {
        string rt=possibleMovs[bestmov];
        pair<int,int> t=string2pair(rt);
        map[t.first][t.second]=AISB;
        mapreverse(map,t.first,t.second,AISB);
        cout<<rt<<endl;
    }
    return level%2==0?alpha:beta;
}
int Eval(char map[][8]){
    int scoremap[8][8];
    for(int i=0;i<8;i++)
    for(int j=0;j<8;j++)
        if(map[i][j]==AISB) scoremap[i][j]=1;
        else if(map[i][j]==' ')scoremap[i][j]=0;
        else scoremap[i][j]=-1;
    vector<string> s= markMov(map,AISB);
    int score;
    score+=400*s.size();
    score+=80*(scoremap[0][0]+scoremap[7][7]+scoremap[0][7]+scoremap[7][0]);
    score-=90*(scoremap[0][1]+scoremap[1][0]+scoremap[6][0]+scoremap[0][6]+scoremap[6][7]+scoremap[7][6]+scoremap[7][1]+scoremap[1][7]);
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
        {
            if(i==0||i==7||j==0||j==7)
                score+=(30*scoremap[i][j]);
            else score+=10*scoremap[i][j];
        }
    return score;
}