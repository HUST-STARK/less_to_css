#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
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
#define WORD_NAME  3   //函数名或类名或属性名或颜色常量
#define WORD_OB     4   //左大括号 opening brace
#define WORD_CB     5   //右大括号 closing brace
#define WORD_STR    6   //字符串(待处理,中间可能还有变量)
#define WORD_EQU    7   //等于号
#define WORD_COMMA  8   //逗号
#define WORD_OP     9   //左小括号
#define WORD_CP     10  //右小括号
#define WORD_SEM    11  //分号
#define WORD_PLUS	12	//加号			+
#define WORD_MUL	13	//乘号			*
#define WORD_MIN	14	//减号			-
#define WORD_DIV	15	//除号or斜杠		/
#define WORD_CMT	16	//块注释
using namespace std;

//输入数据缓冲
vector<char> buf;
struct Word{
	int type;
	string value;
	Word(int type = 0, string value = "") :type(type), value(value){};
};
//单词表
vector<Word> words;

struct Comment{
	vector<string> value;
	Comment(int &pos){
		while (words[pos].type == WORD_CMT){
			this->value.push_back(words[pos++].value);
		}
	}
};

struct Var{
	bool is_stable;
	int type;
	vector<Var*> son;
	double _double;
	string _color;
	string _string;
	int comment_var;
	Var(){
		son.clear();
		is_stable = false;
		comment_var = -1;
	};
	Var(string _string, int type){
		this->is_stable = true;
		comment_var = -1;
		this->type = type;
		if (type == WORD_NUM){
			//小数待处理
			stringstream ss(_string);
			ss >> this->_double;
		}
		else{
			this->_string = _string;
		}
	}
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
	Class(string title = "", int comment_title = -1, int comment_class = -1):title(title), comment_title(comment_title), comment_class(comment_class){
		this->value.clear();
	};
};

struct mVar{
	Var* value;
	string name;
	int scope;
	mVar(Var* v = NULL, string name = "", int scope = -1){
		this->value = v;
		this->name = name;
		this->scope = scope;
	}
};
vector<mVar> var;
//单词表中的位置
struct Pos{
	string name;
	int pos_begin, pos_end;
	Pos(string name = "", int a = 0, int b = 0){
		this->name = name;
		this->pos_begin = a;
		this->pos_end = b;
	}
};
//存函数在单词表中的位置
vector<Pos> pos_of_func, func_temp;

map<string, int> map_func;


//注释表
vector<Comment> comments;
//css类表
vector<Class*> res;

int cnt_scope;
void init(){
	//初始化变量
	cnt_scope = 0;
	var.clear();
	comments.clear();
	map_func.clear();
	pos_of_func.clear();
	res.clear();
	words.clear();
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

void scaner(int& pos, int len, int last_type, string name){
	string token;
	char ch = buf[pos++];
	while (ch == ' ' || ch == '\t' || ch == '\n'){
		if (pos >= len) return;
		ch = buf[pos++];

	}
	bool flag = false;
	int type;
	Pos pp;
	while (ch != 0){
		if (!flag){
			token.clear();
		}
		if (isnumber(ch)){
			while (isnumber(ch) || ch == '.'){
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
			func_temp.push_back(Pos(name, words.size() - 1, -1));
			type = WORD_OB;
			break;
		case '}':
			pp = func_temp[func_temp.size() - 1];
			pp.pos_end = words.size();
			pos_of_func.push_back(pp);
			map_func[pp.name] = pos_of_func.size() - 1;
			func_temp.erase(func_temp.end() - 1);
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
		case ',':
			type = WORD_COMMA;
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
	string name;
	while (pos < len){
		scaner(pos, len, last_type, name);
		last_type = words[words.size() - 1].type;
		if(last_type == WORD_NAME) name = words[words.size() - 1].value;
	}
};

int check_var(string name, int scope){
	//在变量表中遍历是否有作用域下的当前变量
	int k = -1;
	for (int i = 0; i < var.size(); i++){
		if (var[i].name != name) continue;
		if (var[i].scope == scope){
			k = i;
			break;
		}
		if (var[i].scope == 0){
			k = i;
		}
	}
	return k;
}
void merge_class(Class* p, Class *q){
	//合并父类p和子类q
	if (q->comment_title != -1){
		p->value[p->value.size() - 1].comment_name = p->comment_title;
	}
	for (int i = 0; i < q->value.size(); i++){
		p->value.push_back(q->value[i]);
	}
	if (q->value[q->value.size() - 1].comment_name != -1){
		p->value[p->value.size() - 1].comment_name = q->value[q->value.size() - 1].comment_name;
	}

}

Var* deal_var(int& pos, bool is_left, int scope, int sem_common){
	//is_left = true 时表示给变量赋值,否则是给属性赋值.
	Var* v;
	int k;
	if (is_left){
		string name = words[pos].value;
		k = check_var(name, scope);
		if (k == -1){
			v = new Var();
			var.push_back(mVar(v, name, scope));
		}
		else{
			v = var[k].value;
		}
		pos++;
	}
	else{
		v = new Var();
	}
	//处理赋值号右边的部分,到 ; 为止
	int type = words[pos].type;
	while (type != sem_common || (sem_common == WORD_COMMA && type == WORD_CP)){
		switch (type){
		case WORD_VAR:
			k = check_var(words[pos].value, scope);
			if (k == -1){
				var.push_back(mVar(new Var(), words[pos].value, scope));
			}
			//v->son.push_back(new  Var());
			v->son.push_back(var[var.size() - 1].value);
			break;
		case WORD_NUM:
			v->son.push_back(new Var(words[pos].value, WORD_NUM));
			break;
		case  WORD_PLUS:
			v->son.push_back(new Var("+", WORD_PLUS));
			break;
		case WORD_MIN:
			v->son.push_back(new Var("-", WORD_MIN));
			break;
		case  WORD_MUL:
			v->son.push_back(new Var("*", WORD_MUL));
			break;
		case WORD_DIV:
			v->son.push_back(new Var("*", WORD_DIV));
			break;
		case WORD_STR:
			string s = words[pos].value;
			string t;
			t.clear();
			for (int i = 0; i < s.size(); i++){
				if (i >= s.size() - 1 || s[i] != '@' || s[i + 1] == '{'){
					t.push_back(s[i]);
				}
				else{
					if (t.size() != 0){
						v->son.push_back(new Var(t, WORD_STR));
						t.clear();
					}
					i++;
					while (s[i] != '}'){
						t.push_back(s[i]);
					}
					k = check_var(t, scope);
					if (k == -1){
						var.push_back(mVar(new Var(), t, scope));
						k = var.size() - 1;
					}
					v->son.push_back(var[k].value);
				}
			}
			break;
		}
		pos++;
		type = words[pos].type;
	}
	pos++;
	if (words[pos].type == WORD_CMT){
		comments.push_back(Comment(pos));
		v->comment_var = comments.size() - 1;
	}
	return v;
}

void deal_func(int &pos, int scope){
	pos++;
	if (words[pos].type == WORD_CP){
		return;
	}
	while (words[pos].type != WORD_OB){
		deal_var(pos, true, scope, WORD_COMMA);
	}
}

Class* deal_class(int& pos, int scope, bool flag){
	//带括号处理变量,遇到变量还是可以调用deal_var();
	Class *p = new Class(words[pos - 1].value);
	if(flag)res.push_back(p);
	p->title = words[pos].value;
	//添加左大括号后面的注释
	pos++;
	if(words[pos].type == WORD_OP){
		deal_func(pos, scope);
	}
	pos++;
	if (words[pos].type == WORD_CMT){
		comments.push_back(Comment(pos));
		p->comment_class = comments.size() - 1;
	}
	while (words[pos].type != WORD_CB){
		int type = words[pos++].type;
		if (type == WORD_VAR){
			deal_var(pos, true, scope, WORD_SEM);
		}
		else if (type == WORD_NAME && words[pos].type != WORD_COLON){
			//遇到子类或者调用函数
			if (words[pos].type == WORD_SEM || words[pos].type == WORD_OP){
				//调用函数
				int pos2 = pos_of_func[map_func[words[pos - 1].value]].pos_begin;
				merge_class(p, deal_class(pos2, scope, false));
				while (words[pos].type != WORD_SEM){
					pos++;
				}
				pos++;
			}
			else{
				//嵌套子类
				cnt_scope++;
				Class* q = deal_class(pos, cnt_scope, true);
				merge_class(p, q);
				q->title = p->title + " " + q->title;
			}
			if (words[pos].type == WORD_CMT){

				//调用子类后面出现注释,合并子类后加到最后一个属性后面
				comments.push_back(Comment(pos));
				p->value[p->value.size() - 1].comment_name = comments.size();
			}
		}
		else if (type == WORD_NAME && words[pos].type == WORD_COLON){
			//遇到类中属性
			pos++;
			string name = words[pos - 2].value;
			Property pp = Property(name, -1, deal_var(pos, false, scope, WORD_SEM));
			p->value.push_back(pp);
			if (words[pos].type == WORD_CMT){
				//属性后出项注释
				comments.push_back(Comment(pos));
				pp.comment_name = comments.size();
			}
		}
	}
	return p;
}

void turn(){
	//将单词处理成变量储存
	int pos = 0, len = words.size();
	int scope = 0;
	while (words[pos].type == WORD_CMT){
		cout << words[pos++].value << endl;
	}
	while (pos < len){
		int type = words[pos++].type;
		//碰到变量
		if (type == WORD_VAR){
			--pos;
			deal_var(pos, true, cnt_scope, WORD_SEM);
		}
		else if (type == WORD_NAME && words[pos].type == WORD_OP){
			//函数不储存
			pos = pos_of_func[map_func[words[pos - 1].value]].pos_end + 1;
			continue;
		}
		else if (type == WORD_NAME && words[pos].type == WORD_OB){
			//处理类
			cnt_scope++;
			deal_class(--pos, cnt_scope, true);
		}
	}
}

void print(){
	//程序开头有注释,先行输出
	int m = res.size();
}

int main(){
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
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
