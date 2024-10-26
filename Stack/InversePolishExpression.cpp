#include <vector>
#include <string>
#include <stack>
using namespace std;

int calc(int left,int right,char sign)
{
    switch (sign)
    {
    case '+':
        return left + right;
    case '-':
        return left - right;
    case '*':
        return left * right;
    case '/':
        return left / right;
    
    default:
        break;
    }
}


int evalRPN(vector<string>& tokens) {
    stack<int> st;
    for(const auto& s : tokens) {
        if(s.size() == 1 && 
            s[0] == '+' || s[0] == '-' ||
            s[0] == '*' || s[0] == '/') {
                //遇到运算符了
                //两个数字出栈
                int i_1, i_2;
                if(!st.empty()) {
                    i_2 = st.top();
                    st.pop();
                }
                if(!st.empty()) {
                    i_1 = st.top();
                    st.pop();
                }
                //计算结果，把计算结果也入栈
                st.push(calc(i_1,i_2,s[0]));
            }
        else {
            // 遇到数字，压栈
            st.push(stoi(s));
        }
    }
    return st.top();
}   