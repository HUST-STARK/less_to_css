1. ��ע�ͱ���,��ע��ɾ��
2. ������ʶ�� @ ���Ϳ�����int, float, color, string
3. ����������  + - * /  �ַ�������
4. Ƕ��
5. ����������
6. �̳к��Զ��庯��

#define INT         0
#define FLOAT       1
#define COLOR       2
#define STRING      3
#define OPERATOR    4

//����
struct Var{
    bool is_stable;
    int type;
    vector<*Var> son;
    int _int;
    float _float;
    string _string;
}
//css����
struct Property{
    string name;
    Var *value;
};
//css��
struct Class{
    vector<Property> value;
};

//��ע��
bool block_comment(){
    //����ע�Ϳ�
    program();
}
//��ע��
bool line_comment(){
    //����һ��
    program();
}
//����
bool program(){
    if(syn == "//"){
        line_comment();
    }
    if(syn == "/*"){
        block_comment();
    }
    if(syn == ��ǩ){
        *p = new
    }
}
int main(){
    //���뵥��
    syn = scaner();
    program();
}

���� => ���� *
���� => ��ע�� | ��ע�� | ������ֵ | ��
�� => (. | # | none) ��ʶ��[(����*)] { [������ֵ | ���Զ��� | ��]* }
������ֵ => ����: ���ʽ
���Զ��� => ��ʶ��: ���ʽ

