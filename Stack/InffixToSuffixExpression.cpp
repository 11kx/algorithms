#include <iostream>
#include <string>
#include <stack>

using namespace std;
bool priority(char left,char right)
{
    if((left=='*' || left == '/') && (right == '+' || right == '-')){
        return true;
    }
    if(left == '('){
        return true;
    }
    if(right == ')'){
        return false;
    }
    return false;
}
string inffixToSuffix(const string& inffix)
{
    //1.数字直接输出到结果
    //2.(直接入栈 。若栈空，符号直接入栈
    //3.当前符号与栈顶符号进行比较优先级
        //当前符号 > 栈顶符号 当前符号入栈，结束
        //当前符号 < 栈顶符号 栈顶符号出栈输出，继续比较
            //栈内符号输出
            //若）则一直输出到(
    stack<char> s;
    string result;
    for(const auto & ch : inffix) {
        if(ch >= '0' && ch <= '9'){
            result.push_back(ch);
        }
        else
        {
            if(s.empty() || ch == '(') {
                s.push(ch);
            }
            else {
                char topch = s.top();
                //比较符号优先级 true ch > topch
                if(priority(ch,topch))
                {
                    s.push(ch);
                }else {
                    while(!s.empty()){
                        //继续比较，直到当前符号比栈顶符号优先级大
                        topch = s.top();
                        if(priority(ch,topch)) {
                            s.push(ch);
                            break;
                        }
                        else{
                            s.pop();   
                            if(topch == '('){
                                break;
                            }
                            result.push_back(topch);
                        }
                    }
                    s.push(ch);
                }
            }
        }
    }
    while (!s.empty())
    {
        result.push_back(s.top());
        s.pop();
    }
    return result;
}

int main()
{
    string inffix = "2+10/2+2";
    string suffix = inffixToSuffix(inffix);
    std::cout << suffix << endl;
}
