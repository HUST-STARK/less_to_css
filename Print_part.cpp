#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <map>
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
#define WORD_NAME   3   //函数名或类名或属性名或颜色常量
#define WORD_OB     4   //左大括号 opening brace
#define WORD_CB     5   //右大括号 closing brace
#define WORD_STR    6   //字符串(待处理,中间可能还有变量)
#define WORD_EQU    7   //等于号
#define WORD_COMMA  8   //逗号
#define WORD_OP     9   //左小括号
#define WORD_CP     10  //右小括号
#define WORD_SEM    11  //分号
#define WORD_PLUS   12  //加号            +
#define WORD_MUL    13  //乘号            *
#define WORD_MIN    14  //减号            -
#define WORD_DIV    15  //除号or斜杠      /
#define WORD_CMT    16  //块注释
using namespace std;

/*注释*/
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
    Var(int comment_var = -1) :comment_var(comment_var){};
};

struct Property{
    string name;
    int comment_name;
    Var *value;
    Property(string name = "", int comment_name = -1, Var *value = NULL) :name(name), comment_name(comment_name), value(value){};
};

struct Class{
    string title;
    int comment_title;
    vector<Property> value;
    int comment_class;
    Class(int comment_title = -1, int comment_class = -1) :comment_title(comment_title), comment_class(comment_class){};
};

struct Word{
    int type;
    string value;
    Word(int type = 0, string value = "") :type(type), value(value){};
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
    char ch;
    while (~scanf("%c", &ch)){
        buf.push_back(ch);
    }
}

bool isnumber(char ch){
    return ch >= '0' && ch <= '9';
}

void scaner(int& pos, int len, int last_type){
    string token;
    char ch = buf[pos++];
    while (ch == ' ' || ch == '\t' || ch == '\n'){
        ch = buf[pos++];
        if (pos >= len) return;
    }
    bool flag = false;
    int type;
    while (ch != 0){
        if (!flag){
            token.clear();
        }
        if(isnumber(ch)){
            while(isnumber(ch) || ch == '.'){
                token.push_back(ch);
                ch = buf[pos++];
            }
            pos--;
            type = WORD_NUM;
            break;
        }
        if (ch == '@'){
            token.push_back(ch);
            ch = buf[pos++];
            while (isalnum(ch) || ch == '-' || ch == '_'){
                token.push_back(ch);
                ch = buf[pos++];
            }
            pos--;
            type = WORD_VAR;
            break;
        }
        if (ch == '#' || ch == '.'){
            token.push_back(ch);
            ch = buf[pos++];
            while (isalnum(ch)){
                token.push_back(ch);
                ch = buf[pos++];
            }
            pos--;
            type = WORD_NAME;
            break;
        }
        if (((ch == '_' || ch == '-') && isalnum(buf[pos])) || isalnum(ch)){
            while (ch == '-' || ch == '_' || isalnum(ch)){
                token.push_back(ch);
                ch = buf[pos++];
            }
            pos--;
            type = WORD_NAME;
            break;
        }
        if (ch == '/'){
            if (buf[pos] == '*'){
                token.push_back(ch);
                token.push_back(buf[pos++]);
                ch = buf[pos++];
                while (buf[pos - 1] != '*' || buf[pos] != '/'){
                    token.push_back(ch);
                    ch = buf[pos++];
                }
                type = WORD_CMT;
                break;
            }
            else if (buf[pos] == '/'){
                while (buf[pos++] != '\n'){
                }
                return;
            }
        }
        if (ch == '"'){
            token.push_back(ch);
            ch = buf[pos++];
            while (ch != '"'){
                token.push_back(ch);
                ch = buf[pos++];
            }
            type = WORD_STR;
            break;
        }
        if (ch == '+' || ch == '-'){
            token.push_back(ch);
            if (last_type != WORD_NUM && last_type != WORD_VAR && isnumber(buf[pos])){
                flag = true;
                continue;
            }
            break;
        }
        switch (ch){
        case '=':
            type = WORD_EQU;
            break;
        case '{':
            type = WORD_OB;
            break;
        case '}':
            type = WORD_CB;
            break;
        case '(':
            type = WORD_OP;
            break;
        case ')':
            type = WORD_CP;
            break;
        case ':':
            type = WORD_COLON;
            break;
        case ';':
            type = WORD_SEM;
            break;
        case '*':
            type = WORD_MUL;
            break;
        case '/':
            type = WORD_DIV;
            break;
        }
        token.push_back(ch);
        break;
    }
    words.push_back(Word(type, token));
    cout << type << "     " << token << endl;
}

void get_words(){
    //将单词读入到words中
    int pos = 0, len = buf.size();
    int last_type = INF;
    while (pos < len){
        scaner(pos, len, last_type);
        last_type = words[words.size() - 1].type;
    }
};

void deal_var(int& pos){

}

void deal_class(int& pos){
    //带括号处理变量,遇到变量还是可以调用deal_var();

}

void turn(){
    //将单词处理成变量储存
    int pos = 0, len = words.size();
    while (pos < len){
        int type = words[pos++].type;
        //碰到变量
        if (type == WORD_VAR){
            deal_var(pos);
        }
        else if (type == WORD_NAME){
            //处理类(包括函数)
            deal_class(pos);
        }
    }
}

/*处理数值的计算*/
double compute_double(Var& v) {
    stack<double> value;
    stack<int> op;
    bool flag = false;

    for (vector<Var*>::iterator it = v.son.begin(); it != v.son.end(); it++) {
        if (  (*it)->is_stable == true ) {
            if ( (*it)->type != WORD_OP && (*it)->type != WORD_CP
               && (*it)->type != WORD_MUL && (*it)->type != WORD_DIV
                && (*it)->type != WORD_PLUS && (*it)->type != WORD_MIN) {
                    value.push( (*it)->_float );
                    flag = true;
                }
            else {
                op.push( (*it)->type );
            }
        } else {
            value.push( compute_double( *(*it) ));
        }
    }

    /*计算优先级较高的*/
    compute_prior:
    if (flag && !op.empty()
       && op.top() != WORD_MUL
       && op.top() != WORD_DIV ) {
        double y = value.top(); value.pop();
        double x = value.top(); value.pop();

        if ( op.top() == WORD_MUL ) {
            op.pop();
            value.push(x * y);
        } else {
            op.pop();
            value.push(x / y);
        }
    } else if ( !op.empty() && op.top() == WORD_CP) {
        op.pop();

        while (op.top() != WORD_OP) {
            double y = value.top(); value.pop();
            double x = value.top(); value.pop();
            if (op.top() == WORD_PLUS) {
                op.pop();
                value.push(x + y);
            } else {
                op.pop();
                value.push(x - y);
            }
        }
        flag = true;
        goto compute_prior;
    }

    while ( !op.empty() ) {
        double y = value.top(); value.pop();
        double x = value.top(); value.pop();
        int o = op.top(); op.pop();

        if (o == WORD_MUL) {
            value.push(x * y);
        } else if (o == WORD_DIV) {
            value.push(x / y);
        } else if (o == WORD_PLUS) {
            value.push(x + y);
        } else if (o == WORD_MIN) {
            value.push(x - y);
        }
    }
    return value.top();
}

/*解析网址*/
string compute_string(Var& v) {
    string ans = "";

    if (v.is_stable == true)
        return v._string;
    else {
        for (vector<Var*>::iterator it = v.son.begin(); it != v.son.end(); it++) {
            if ( (*it)->is_stable == true )
                ans += (*it)->_string;
            else
                ans += compute_string( *(*it) );
        }
    }

    return ans;
}

void print(){
    int m = res.size();

    /*输出每个类中的各个属性*/
    for (int i = 0; i < m; i++){
        Class& c = res[i];
        /*类名*/
        cout << c.title;
        cout << '{' << endl;

        /*跟在左大括号后面第一个属性变量之前的注释*/
        for (int i = 0; i < comments[c.comment_title].value.size(); i++) {
            cout << comments[c.comment_title].value[i] << endl;
        }

        /*输出类中的所有CSS属性*/
        for (int i = 0; i< c.value.size(); i++) {
            Property& p = c.value[i];
            cout << p.name << ':';

            /*属性名后面的注释*/
            if (p.comment_name != -1) {
                for (int j = 0; i < comments[p.comment_name].value.size(); j++) {
                    cout << comments[p.comment_name].value[j];
                }
            }

            /*输出属性值*/
            Var* v = p.value;
            if (v->is_stable == true){
                switch(v->type){
                    case INT: cout << v->_int << ';' << endl;
                    case FLOAT: cout << v->_float << ';' << endl;
                    case COLOR: cout << v->_color << ';' << endl;
                    case STRING: cout << v->_string << ';' << endl;
                }
            }
            /*变量先计算再输出*/
            else{
                if (v->type == INT)
                    cout << (int)compute_double(*v) << ';' << endl;
                if (v->type == FLOAT)
                    cout << compute_double(*v) << ';' << endl;
                if (v->type == STRING)
                    cout << compute_string(*v) << ';' << endl;
                if (v->type == COLOR) {
                    int tmp = compute_double(*v);
                    int pos = 6;
                    char tmp_16[7] = {'0'};
                    tmp_16[0]= '#';

                    while (tmp && pos >=1) {
                        char bit = tmp % 16;
                        if(bit < 10) tmp_16[pos] = bit+'0';
                        else tmp_16[pos] = bit-10+'a';

                        tmp /= 16;
                        pos --;
                    }

                    cout << tmp_16 << ';' <<endl;
                }

            }

            /*属性变量后的注释*/
            /*Var初始化：comments_var=-1*/
            if (v->comment_var != -1) {
                for (int j = 0; i < comments[v->comment_var].value.size(); j++) {
                    cout << comments[v->comment_var].value[j] << endl;
                }
            }

        }

        cout << '}' << endl;
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
    //turn();
    //输出
    //print();

}

