1. 块注释保留,行注释删掉
2. 变量标识符 @ 类型可以是int, float, color, string
3. 变量间运算  + - * /  字符串插入
4. 嵌套
5. 变量作用域
6. 继承和自定义函数

#define INT         0
#define FLOAT       1
#define COLOR       2
#define STRING      3
#define OPERATOR    4

//变量
struct Var{
    bool is_stable;
    int type;
    vector<*Var> son;
    int _int;
    float _float;
    string _string;
}
//css属性
struct Property{
    string name;
    Var *value;
};
//css类
struct Class{
    vector<Property> value;
};

//块注释
bool block_comment(){
    //读完注释块
    program();
}
//行注释
bool line_comment(){
    //读完一行
    program();
}
//程序
bool program(){
    if(syn == "//"){
        line_comment();
    }
    if(syn == "/*"){
        block_comment();
    }
    if(syn == 标签){
        *p = new
    }
}
int main(){
    //读入单词
    syn = scaner();
    program();
}

程序 => 语句块 *
语句块 => 行注释 | 块注释 | 变量赋值 | 类
类 => (. | # | none) 标识符[(参数*)] { [变量赋值 | 属性定义 | 类]* }
变量赋值 => 变量: 表达式
属性定义 => 标识符: 表达式

