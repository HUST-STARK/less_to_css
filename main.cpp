#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
#define LL long long
#define eps 1e-8

#define INT         0
#define FLOAT       1
#define COLOR       2
#define STRING      3
#define OPERATOR    4

//word中type的定义
#define WORD_VAR    0   //变量
#define WORD_COLON  1   //冒号
#define WORD_NUM    2   //数字
#define WORD_TITLE  3   //函数名或类名或属性名或颜色常量
#define WORD_OB     4   //左大括号 opening brace
#define WORD_CB     5   //右大括号 closing brace
#define WORD_STR    6   //字符串(待处理,中间可能还有变量)
#define WORD_EQU    7   //等于号
#define WORD_COMMA  8   //逗号
#define WORD_OP     9   //左小括号
#define WORD_CP     10  //右小括号
#define WORD_SEM    11  //分号

using namespace std;


struct Comment{
    vector<string> value;
    Comment(){
        this->value.clear();
    }
};
struct Var{
    bool is_stable;
    int type;
    vector<Var*> son;
    int _int;
    float _float;
    string _color;
    string _string;
    int comment_var;
    Var(){};
};

struct Property{
    string name;
    int comment_name;
    Var *value;
    Property(string name = "", int comment_name = -1, Var *value = NULL):name(name), comment_name(comment_name), value(value){};
};

struct Class{
    string title;
    int comment_title;
    vector<Property> value;
    int comment_class;
};

struct Word{
    int type;
    string value;
};
//单词表中的位置
struct Pos{
    int pos_begin, pos_end;
};
//存函数在单词表中的位置
vector<Pos> pos_of_func;

map<string, int> map_func;
//输入数据缓冲
vector<char> buf;
//单词表
vector<Word> words;
//注释表
vector<Comment> comments;
//css类表
vector<Class> res;

void init(){
//初始化变量
}
void read(){
//将文件中所有字符读到buf中

}

void get_words(){
//将单词读入到words中

};
void deal_var(int& pos){

}

void deal_class(int& pos){
    //带括号处理变量,遇到变量还是可以调用deal_var();

}

void turn(){
//将单词处理成变量储存
    int pos = 0, len = words.size();
    while(pos < len){
        int type = words[pos++].type;
        //碰到变量
        if(type == WORD_VAR){
                deal_var(pos);
        } else if(type == WORD_TITLE){
                //处理类(包括函数)
                deal_class(pos);
        }
    }
}
void print(){
    //程序开头有注释,先行输出
    int m = res.size();
    //输出每个类中的各个属性
    for(int i = 0; i < m; i++){

    }
}

int main(){
    freopen("in.txt", "r", stdin);
    //初始化
    init();
    //将less读入到buf中
    read();
    //将每个单词读入到words中
    get_words();
    //转换
    turn();
    //输出
    print();

}
