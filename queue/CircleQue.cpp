#include <iostream>

using namespace std;
class Queue
{
public:
    Queue(int size = 10):cap_(size),size_(0),first_(0),rear_(0)
    {
        arr_ = new int[size];
    }
    ~Queue()
    {
        delete []arr_;
        arr_ = nullptr;
    }
    void Push(int value)
    {
        if((rear_ + 1) % cap_ == first_){
            expand(cap_ * 2);
        }
        arr_[rear_] = value;
        rear_ = (rear_ + 1 ) % cap_;
        size_++;
    }
    void Pop()
    {
        if(empty()){
            return;
        }
        first_ = (first_ + 1) % cap_;
        size_--;
    }
    int front()
    {
        if(empty()){
            throw "The queue is empty.";
        }
        return arr_[first_];
    }
    int back()
    {
        if(empty()){
            throw "The queue is empty.";
        }
        //考虑rear = 0的情况
        return arr_[(rear_ - 1 + cap_) % cap_];
    }
    int size() const
    {
        return size_;
    }
    bool empty() const 
    {
        return rear_ == first_;
    }
private:
    void expand(int size)
    {
        int* arr = new int[size];
        // 环形数组一定不能直接copy到新内存。
        for(int i = first_,j = 0; i != rear_;i = (i + 1)% cap_,j++)
        {
            arr[j] = arr_[i];
        }
        delete[] arr_;
        arr_ = arr;
        first_ = 0;
        rear_ = size_;
        cap_ = size;
    }
private:
    int* arr_;
    int cap_;
    int size_;
    int first_;
    int rear_;
};

int main()
{
    Queue q;
    for(int i = 0;i < 15;i++)
    {
        q.Push(i);
    }
    cout << "back " << q.back() << endl;

    std::cout << "size :" << q.size() << endl;
    if(q.empty())
    {
        cout << "循环队列为空" << endl;
    } else{
        cout << "循环队列不为空" << endl;
    }

}