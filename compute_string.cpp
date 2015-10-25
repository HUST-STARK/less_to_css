#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <map>
#include <vector>
#include <list>
#include <string>
#include <iostream>
#define INF 0x3f3f3f3f
#define IN freopen("in", "r", stdin);

using namespace std;

string& trim(string &);
bool StringIsInteger(string &);
bool StringIsFloat(string &);
string& compute(string &);
int find_op(string &, int );
string format(string &);
string& combine(double , double , string &);
double val(string &, string &);


map<string, string> VAR;
int main() {
    IN;
    char c;
    while ((c = getchar()) != EOF) {
        if (c == '@') {
            string s;
            while (scanf("%c", &c) && c != ';') {
                s += c;
            }
            int colon_pos = s.find(':');
            if (colon_pos != -1) {
                string var = s.substr(0, colon_pos); var = trim(var);
                string value = s.substr(colon_pos + 1, value.length());  value = trim(value);
                
                if (value[0] == '@') {

                    value = value.substr(1, value.length());
                    value = compute(value);
                    VAR.erase(var);
                    VAR.insert(make_pair(var, value));
                } else { 
                    VAR.erase(var);
                    VAR.insert(make_pair(var, value));     
                }  
            }
        } else if (c == ':') {
            string s = "";
            while ((c = getchar()) != ';') 
                s += c;
            s = trim(s);
            string value = compute(s);
            cout<<value<<endl;
        }
    }

    return 0;
}

bool StringIsInteger(string &s) {
    for (int i = 0; i < s.size(); i++) {
        if ((s[i] > '9' || s[i] < '0'))
            return false;
    }
    return true;
}

bool StringIsFloat(string &s) {
    int cnt = 1;
    for (int i = 0; i < s.size(); i++) {
        if ((s[i] == '.')) cnt++;
        if ((s[i] > '9' || s[i] < '0') || cnt == 2) {
            return false;
        }
    }
    return true;
}
string& trim(string &s) {
    if (s.empty()) {
        return s;
    }
    s.erase(0, s.find_first_not_of(" "));
    s.erase(s.find_last_not_of(" ") + 1);
    return s;
}

string& compute(string &s) {

    if (s.find("url", 0) == 0) {
        int pos = 0;
        while ( (pos = s.find('@', 0)) != -1) {
            cout<<pos<<endl;
            int left_bracket = s.find('{', pos);
            int right_bracket = s.find('}', pos);
            cout<<right_bracket<<endl;
            string var = VAR[s.substr(left_bracket + 1, right_bracket - 1 - (left_bracket))];
            s = s.substr(0, pos) + var.substr(1, var.length() - 2) 
                + s.substr(right_bracket + 1, s.length() - (right_bracket + 1));
        }
    } else {
        while (s.find("(", 0) != -1) {
            int left_brace = s.find("(", 0);
            int right_brace = s.rfind(")", 0);
            string temp = s.substr(left_brace + 1, right_brace - 1 - left_brace);
            string value = compute(temp);
            s = s.substr(0, left_brace - 1) + value + s.substr(right_brace + 1, s.length() - right_brace - 1); 
        }
        int i = 0;
        while ( s.find('@', 0) != -1) {
            int pos = s.find('@', 0);
            int pos2 = find_op(s, pos); if (pos2 == INF) pos2 = s.length();
            string var = s.substr(pos + 1, pos2 - pos - 1);
            s = s.substr(0, pos) + VAR[trim(var)] + s.substr(pos2, s.length() - pos2);
        } 

        char op;
        int pos = 0;
        while ( pos != INF) {
            pos = find_op(s, pos);
            if (pos != INF)
                s = s.substr(0, pos - 1) + " " + s.substr(pos, 1) + " " + s.substr(pos + 1, s.length() - pos - 1);
            else 
                break;
            pos++;
        }

        while ( s.find('*', 0) != -1 ) {
            pos = s.find('*', 0);
            int left = s.rfind(' ', pos - 2);
            int right = s.find(' ', pos + 2);
            cout<<left<<" "<<right<<endl;
            string l = s.substr(left, pos - left - 1); l = trim(l);
            string r = s.substr(pos + 1, right - (pos + 1)); r = trim(r);
            cout<<l<<" "<<r<<endl;
            string form_left = format(l);
            string form_right = format(r);
            int value_left = val(l, form_left);
            int value_right = val(r, form_right);
            string value = combine(value_left, value_right, form);
            string s = s.substr(0, left) + value + s.substr(right, s.length() - right);  
        }
    }

    return s;
}


int find_op(string &s, int pos) {
    int pos2 = INF;
    int temp = s.find('-', pos);
    pos2 = (temp == -1) ? pos2 : min(temp, pos2);
    temp = s.find('+', pos);
    pos2 = (temp == -1) ? pos2 : min(temp, pos2);
    temp = s.find('*', pos);
    pos2 = (temp == -1) ? pos2 : min(temp, pos2); 
    temp = s.find('/', pos);
    pos2 = (temp == -1) ? pos2 : min(temp, pos2);

    return pos2;
}

string format(string &s) {
    if (s[0] == '#') 
        return "color";
    if (StringIsInteger(s))
        return "int";
    if (StringIsFloat(s)) 
        return "float";
    int pos = s.find("px", 0);
    if (pos == s.length() - 2)
        return "pixel";    
}

double val(string &s, string &form) {
    if (form == "int")
        return atoi(s.c_str());
    if (form == "float")
        return atof(s.c_str());
    if (form == "color") {
        string temp = s.substr(1, s.length() - 1);
        return stoul(temp, nullptr, 16);
    }
    if (form == "pixel") {
        string temp = s.substr(0, s.length() - 2);
        return atoi(s.c_str());
    }
}

string combine(double t, string &form) {
    if (form == "int") {
        string temp = to_string(t); 
        return temp;
    }
    if (form == "float") {
        string temp = to_string(t);
        return temp;
    }
    if (form == "color") {
        string temp = to_string((int)t); 
        temp = temp.ToString("X4");
    }
