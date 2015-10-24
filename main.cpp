#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <map>
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
#define WORD_NAME  3   //������������������������ɫ����
#define WORD_OB     4   //������� opening brace
#define WORD_CB     5   //�Ҵ����� closing brace
#define WORD_STR    6   //�ַ���(������,�м���ܻ��б���)
#define WORD_EQU    7   //���ں�
#define WORD_COMMA  8   //����
#define WORD_OP     9   //��С����
#define WORD_CP     10  //��С����
#define WORD_SEM    11  //�ֺ�
#define WORD_PLUS	12	//�Ӻ�			+
#define WORD_MUL	13	//�˺�			*
#define WORD_MIN	14	//����			-
#define WORD_DIV	15	//����orб��		/
#define WORD_CMT	16	//��ע��
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
	Property(string name = "", int comment_name = -1, Var *value = NULL) :name(name), comment_name(comment_name), value(value){};
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
	Word(int type = 0, string value = "") :type(type), value(value){};
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
	//�����ʶ��뵽words��
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
	//�����Ŵ������,�����������ǿ��Ե���deal_var();

}

void turn(){
	//�����ʴ���ɱ�������
	int pos = 0, len = words.size();
	while (pos < len){
		int type = words[pos++].type;
		//��������
		if (type == WORD_VAR){
			deal_var(pos);
		}
		else if (type == WORD_NAME){
			//������(��������)
			deal_class(pos);
		}
	}
}
void print(){
	//����ͷ��ע��,�������
	int m = res.size();
	//���ÿ�����еĸ�������
	for (int i = 0; i < m; i++){
		Class& c = res[i];
		cout << c.title;
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
	//turn();
	//���
	//print();

}
