#include <include/Bigint.h>
#include <stack>
#ifndef NDEBUG
#include <cassert>
#endif
inline static bool isDigit(char ch) {return ch >= '0'&&ch <= '9'; }
inline static int getPriority(char ch) {
    return (ch == '+' || ch == '-') ? 1 : 2;
}
inline static bool isOpt(char ch) {return ch == '+'||ch == '-'||ch == '*'||ch == '/'; }

Biginteger calc(const Biginteger &num1,const Biginteger &num2,char opt) {
    switch (opt) {
        case '+':
            return num1.Add(num2);
        case '-':
            return num1.Subt(num2);
        case '*':
            return num1.Multiply(num2);
        case '/':
            return num1.Divide(num2);
    }
}
/**
 * 将给定的中缀表达式转为后缀表达式
 * @param exp 给定的中缀表达式
 * @return 后缀表达式
 */
string toSuffixExp(const string &exp) {
    std::stack<char> opts;
    string res;
    int i = 0,len = exp.length();
    if(exp[0] == '-') {
        res += "-";
        i++;
    }
    else if(!isdigit(exp[0]))
        throw NumberFormatException(exp[0]);
    while (i < len) {
        while (isblank(exp[i])&&i < len) {
            i++;
        }
        char now = exp[i];
        if (i == len)    break;
        if (!isDigit(now)) {
            if (!isOpt(now)|| i == len - 1)
                throw NumberFormatException(now);
            else if (isOpt(exp[i + 1]))
                throw NumberFormatException(exp[i + 1]);
            while (!opts.empty()) {
                char top = opts.top();
                if (getPriority(now) > getPriority(top)) {
                    opts.push(now);
                    break;
                }
                opts.pop();
                res.append(1,top);
                res.append(1,' ');
            }
            if (opts.empty()) {
                opts.push(exp[i]);
            }
            i++;
            continue;
        }
        int j = 0;
        while (i + j < len&&isdigit(exp[i + j])) {
            j++;
        }
        res += exp.substr(i,j) + ' ';
        i += j;
    }
    while (!opts.empty()) {
        char top = opts.top();
        res.append(1,top);
        res.append(1,' ');
        opts.pop();
    }
    return res;
}

/**
 * 后缀表达式求值
 * @param suffixExp :后缀表达式
 * @param term 终止符，默认为'\\0'
 * @return 后缀表达式 suffixExp 的结果
 */
Biginteger calcSufExpression(const string &suffixExp, char term = 0) {
    std::stack<Biginteger> number; //操作数栈
    int i = 0;
    if(suffixExp[0] == '-') {
        int j = 1;
        while (suffixExp[i + j] != term && isdigit(suffixExp[i + j]))
            j++;
        Biginteger now(suffixExp.substr(i, j));
        number.push(now);
        i += j;
    }
    while (true) {
        while (isblank(suffixExp[i])&&suffixExp[i] != term) {
            i++;
        }
        if (isOpt(suffixExp[i])) {
            char opt = suffixExp[i];
            Biginteger num2(number.top());  //操作数2
            number.pop();
            Biginteger num1(number.top());  //操作数1
            number.pop();
            number.push(calc(num1,num2,opt));
            i++;
            continue;
        }
        if (suffixExp[i] == term)   break;
        int j = 0;
        while (suffixExp[i + j] != term && isdigit(suffixExp[i + j]))
            j++;
        Biginteger now(suffixExp.substr(i, j));
        number.push(now);
        i += j;
    }
#ifndef NDEBUG
    assert(number.size() == 1);
#endif
    return number.top();
}
/**
 * 表达式求值
 * @param exp :给定的表达式
 * @return 求得的结果
 */
Biginteger calcExpression(const string &exp) {
    return calcSufExpression(toSuffixExp(exp));
}
