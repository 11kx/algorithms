#include <iostream>

using namespace std;

class LinkQue
{
public:
    LinkQue()
    {
        head = new Node;
        head->next = head->pre = head;
        size_ = 0;
    }
    ~LinkQue()
    {
        Node* p = head->next;
        while (p != head)
        {
            head->next = p->next;
            p->next->pre = head;
            delete p;
            p = head->next;
        }
        delete head;
        head = nullptr;        
    }
    void push(int value)
    {
        //队列先进后出，自然是从队尾入
        Node* rear = head->pre;
        Node* tmp = new Node(value);
        tmp->next = head;
        tmp->pre = rear;
        rear->next = tmp;
        head->pre = tmp;
        size_++;
    }
    void pop()
    {
        Node* first = head->next;
        if(first == head){
            throw "The Link queue is empty.";
        }
        head->next = first->next;
        first->next->pre = head;
        delete first;
        size_--;
    }
    int front()
    {
        if(head->next == head){
            throw "The Link queue is empty.";
        }
        return head->next->data;
    }
    int back()
    {
         if(head->pre == head){
            throw "The Link queue is empty.";
        }
        return head->pre->data;
    }
    int size() const
    {
        return size_;
    }
    bool empty() const
    {
        return head->next == head;
    }

private:
    struct Node
    {
        Node(int data = 0):data(data),pre(nullptr),next(nullptr){ }
        int data;
        Node *pre;
        Node *next;
    };

    Node *head;
    int size_;
};

int main()
{
    LinkQue lq;
    for(int i = 0;i < 15;i++)
    {
        lq.push(i);
    }
    // for(int i = 0;i < 15;i++)
    // {
    //     cout << lq.front() << " "; 
    //     lq.pop();
    // }
    cout << endl;
     cout << "back " << lq.back() << endl;

    std::cout << "size :" << lq.size() << endl;
    if(lq.empty())
    {
        cout << "循环队列为空" << endl;
    } else{
        cout << "循环队列不为空" << endl;
    }
}