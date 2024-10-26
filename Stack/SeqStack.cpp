#include <iostream>
#include <algorithm>

class SeqStack
{
public:
    SeqStack(int mcap = 5):mcap(mcap)
    {
        mstack = new int[mcap];
        mtop = 0;
    }
    ~SeqStack()
    {
        delete []mstack;
        mstack = nullptr;
    }
    //入栈
    void push(int value)
    {
        if(mtop == mcap)
            expand(2 * mcap);
        mstack[mtop++] = value;
    }
    //出栈
    void pop()
    {
        if(mtop == 0)
            throw "stack is empty";
        mtop--;
    }
    //获取栈顶元素
    int GetTop() const
    {
        if(mtop == 0)
            throw "stack is empty";
        return mstack[mtop - 1];
    }
    //判空
    bool empty()
    {
        return mtop == 0;
    }
    int size() const
    {
        return mtop;
    }
private:
    void expand(int cap)
    {
        int* stack = new int[cap];
        std::copy(mstack,mstack + mcap,stack);
        delete []mstack;
        mstack = stack;
        mcap = cap;
    }
private:
    int* mstack;
    int mtop;
    int mcap;
};

int main()
{
    SeqStack ss;
    for(int i = 0;i < 10;i++)
    {
        ss.push(i);
    }
    while(!ss.empty())
    {
        std::cout << ss.GetTop() << " ";
        ss.pop();
    }
    std::cout << std::endl;
}