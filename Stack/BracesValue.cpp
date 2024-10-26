#include <iostream>
#include <string>
#include <stack>

bool isValid(std::string s)
{
    std::stack<char> st;
    for (const auto &ch : s)
    {
        if (ch == '{' || ch == '[' || ch == '(')
        {
            st.push(ch);
        }
        else
        {
            // 栈里要有元素
            if (!st.empty())
            {
                // 遇到右括号了
                char tmp_c = st.top();
                st.pop();
                // 找不是的好找
                if (ch == ']' && tmp_c != '[' || ch == '}' && tmp_c != '{' || ch == ')' && tmp_c != '(')
                {
                    return false;
                }
            }
            else
            {
                //若栈内无元素，但是要匹配了，说明一定是不合法了。
                return false;
            }
        }
    }
    // 若栈空，则说明都匹配正确了。
    if (st.empty())
        return true;
    else
        return false;
}
