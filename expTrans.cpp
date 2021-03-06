#include <include/Bigint.h>
#include <stack>
#include <cctype>

inline static int getPriority(char ch) {return (ch == '+' || ch == '-') ? 1 : 2;}
//Do not inline this function!
bool isOpt(char ch) {return ch == '+'||ch == '-'||ch == '*'||ch == '/'; }

inline static Biginteger calc(const Biginteger &num1,const Biginteger &num2,char opt) {
    switch (opt) {
        case '+':
            return num1.Add(num2);
        case '-':
            return num1.Subt(num2);
        case '*':
            return num1.Multiply(num2);
        case '/':
            Biginteger half(num2.Divide("2"));
            Biginteger num3 = (num1 >= "0") ? num1.Add(half) : num1.Subt(half);
            return num3.Divide(num2);
    }
    throw NumberFormatException(opt);
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
        if (!isdigit(now)) {
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
 * @return 后缀表达式 suffixExp 的结果
 */
Biginteger calcSufExpression(const string &suffixExp) {
    std::stack<Biginteger> number; //操作数栈
    int i = 0,len = suffixExp.length();
    if(suffixExp[0] == '-') {
        int j = 1;
        while (i + j < len && isdigit(suffixExp[i + j]))
            j++;
        Biginteger now(suffixExp.substr(i, j));
        number.push(now);
        i += j;
    }
    while (true) {
        while (isblank(suffixExp[i])&&i < len) {
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
        if (i >= len)   break;
        int j = 0;
        while (i + j < len && isdigit(suffixExp[i + j]))
            j++;
        Biginteger now(suffixExp.substr(i, j));
        number.push(now);
        i += j;
    }
    if(number.size() > 1)
        throw NumberFormatException();
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
