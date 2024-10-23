#include <iostream>

struct Node
{
    int data;
    Node *pre;
    Node *next;
    Node(int value = 0) : data(value), pre(nullptr), next(nullptr) {}
};

class DoubleCircleLink
{
public:
    DoubleCircleLink()
    {
        head_ = new Node;
        head_->next = head_->pre = head_;
    }
    ~DoubleCircleLink()
    {
        Node* p = head_->next;
        while (p != head_)
        {
            head_->next = p->next;
            delete p;
            p = head_->next;
        }
        delete head_;
        head_ = nullptr;        
    }
    //头插法
    void insertAtHead(int value)
    {
        Node* p = new Node(value);
        p->next = head_->next;
        p->pre = head_;
        p->next->pre = p;
        head_->next = p;
    }
    //尾插法
    void insertAtTail(int value)
    {
        Node* p = head_->pre;
        Node* node = new Node(value);
        node->pre = p;
        node->next = head_;
        p->next = node;
        head_->pre = node;
    }
    //删除值为value的节点
    void Remove(int val)
    {
        Node* p = head_->next;
        while (p != head_)
        {
            if(p->data == val)
            {
                p->pre->next = p->next;
                p->next->pre = p->pre;
                delete p;
                return;
            }
            else
            {
                p = p->next;
            }
        }
    }
    //节点搜索
    bool Find(int value)
    {
        Node* p = head_->next;
        while (p != head_)
        {
            if(p->data == value)
            {
                return true;
            }
            else
            {
                p = p->next;
            }
        }
        return false;
    }
    void Show()
    {
        Node* p = head_->next;
        while (p != head_)
        {
            std::cout << p->data << " ";
            p = p->next;
        }
        std::cout << std::endl;
    }
private:
    Node *head_;
};

int main()
{
    DoubleCircleLink dcl;
    for(int i = 0;i < 10;i++)
    {
        dcl.insertAtTail(i);
    }
    dcl.Show();
    std::cout << dcl.Find(4) << std::endl;
    dcl.Remove(4);
    std::cout << dcl.Find(4) << std::endl;
}