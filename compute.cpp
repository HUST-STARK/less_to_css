/*************************************************************************
	> File Name: compute.cpp
	> Author: 
	> Mail: 
	> Created Time: 2015年10月25日 星期日 14时56分46秒
 ************************************************************************/

#include<iostream>
using namespace std;

struct var {
    bool is_stable;
    int type;
    vector<Var*> son;
    int _int;
    float _float;
    string _color;
    string _string;
    int comment_var;
    Var() {};
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
