#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
#define LL long long
#define eps 1e-8

#define INT         0
#define FLOAT       1
#define COLOR       2
#define STRING      3
#define OPERATOR    4

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
//输入数据缓冲
vector<char> buf;
//单词表
vector<Word> words;
//注释表
vector<Comment> comments;

void read(){
//将文件中所有字符读到buf中
}

void get_words(){
//将单词读入到words中
};

void turn(){
//将单词处理成变量储存
    int pos = 0, len = words.size();
    while(pos < len){
        int type = words[pos++].type;
        if(type == "标签"){

        }
    }
}
int main(){
    freopen("in.txt", "r", stdin);
    //将less读入到buf中
    read();
    //将每个单词读入到words中
    get_words();

    turn();



}
