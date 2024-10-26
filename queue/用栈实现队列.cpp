#include <stack>
class MyQueue {
public:
       MyQueue() {
        
    }
    
    void push(int x) {
        s1.push(x);
    }
    
    int pop() {
        while(!s1.empty())
        {
            s2.push(s1.top());
            s1.pop();
        }
        int tmp = s2.top();
        s2.pop();
        while(!s2.empty())
        {
            s1.push(s2.top());
            s2.pop();
        }
        return tmp;
    }
    
    int peek() {
        while(!s1.empty())
        {
            s2.push(s1.top());
            s1.pop();
        }
        int tmp = s2.top();
        while(!s2.empty())
        {
            s1.push(s2.top());
            s2.pop();
        }
        return tmp;
    }
    
    bool empty() {
        return s1.empty() && s2.empty();
    }
private:
    std::stack<int> s1;
    std::stack<int> s2;
};

