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
//�������ݻ���
vector<char> buf;
//���ʱ�
vector<Word> words;
//ע�ͱ�
vector<Comment> comments;

void read(){
//���ļ��������ַ�����buf��
}

void get_words(){
//�����ʶ��뵽words��
};

void turn(){
//�����ʴ���ɱ�������
    int pos = 0, len = words.size();
    while(pos < len){
        int type = words[pos++].type;
        if(type == "��ǩ"){

        }
    }
}
int main(){
    freopen("in.txt", "r", stdin);
    //��less���뵽buf��
    read();
    //��ÿ�����ʶ��뵽words��
    get_words();

    turn();



}
