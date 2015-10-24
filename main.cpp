#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
#define LL long long
#define eps 1e-8

#define INT         0
#define FLOAT       1
#define COLOR       2
#define STRING      3
#define OPERATOR    4

//word��type�Ķ���
#define WORD_VAR    0   //����
#define WORD_COLON  1   //ð��
#define WORD_NUM    2   //����
#define WORD_TITLE  3   //������������������������ɫ����
#define WORD_OB     4   //������� opening brace
#define WORD_CB     5   //�Ҵ����� closing brace
#define WORD_STR    6   //�ַ���(������,�м���ܻ��б���)
#define WORD_EQU    7   //���ں�
#define WORD_COMMA  8   //����
#define WORD_OP     9   //��С����
#define WORD_CP     10  //��С����
#define WORD_SEM    11  //�ֺ�

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
//���ʱ��е�λ��
struct Pos{
    int pos_begin, pos_end;
};
//�溯���ڵ��ʱ��е�λ��
vector<Pos> pos_of_func;

map<string, int> map_func;
//�������ݻ���
vector<char> buf;
//���ʱ�
vector<Word> words;
//ע�ͱ�
vector<Comment> comments;
//css���
vector<Class> res;

void init(){
//��ʼ������
}
void read(){
//���ļ��������ַ�����buf��

}

void get_words(){
//�����ʶ��뵽words��

};
void deal_var(int& pos){

}

void deal_class(int& pos){
    //�����Ŵ������,�����������ǿ��Ե���deal_var();

}

void turn(){
//�����ʴ���ɱ�������
    int pos = 0, len = words.size();
    while(pos < len){
        int type = words[pos++].type;
        //��������
        if(type == WORD_VAR){
                deal_var(pos);
        } else if(type == WORD_TITLE){
                //������(��������)
                deal_class(pos);
        }
    }
}
void print(){
    //����ͷ��ע��,�������
    int m = res.size();
    //���ÿ�����еĸ�������
    for(int i = 0; i < m; i++){

    }
}

int main(){
    freopen("in.txt", "r", stdin);
    //��ʼ��
    init();
    //��less���뵽buf��
    read();
    //��ÿ�����ʶ��뵽words��
    get_words();
    //ת��
    turn();
    //���
    print();

}
