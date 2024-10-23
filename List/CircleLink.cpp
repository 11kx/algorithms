#include <iostream>

struct Node
{
    int data;
    Node *next;
    Node(int x = 0) : data(x), next(nullptr) {}
    Node(int x, Node *next) : data(x), next(next) {}
};

class CircleLink
{
public:
    CircleLink()
    {
        head = new Node;
        tail = head;
        head->next = head;
    }
    ~CircleLink()
    {
        Node *p = head->next;
        while (p != head)
        {
            head->next = p->next;
            delete p;
            p = head->next;
        }
        delete head;
    }
    // 头插法
    void InsertAtHead(int val)
    {
        Node *newNode = new Node(val); // 创建新节点
        if (head->next == head)
        {
            tail = newNode;
            head->next = newNode;
            newNode->next = head;
        }
        else{
            newNode->next = head->next;
            head->next = newNode;
        }
    }
    // 尾插法
    void insertAtTail(int val)
    {
        Node *newNode = new Node(val); // 创建新节点

        tail->next = newNode; // 将新节点插入到链表尾部
        newNode->next = head;
        tail = newNode;
    }

    // 打印链表中的元素（跳过头结点）
    void printList() const
    {
        Node *temp = head->next; // 跳过头结点
        while (temp != head)
        {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }

private:
    Node *head;
    Node *tail;
};

int main()
{
    CircleLink clink;
    for (int i = 0; i < 5; i++)
    {
        clink.InsertAtHead(i);
    }

    clink.printList();
}