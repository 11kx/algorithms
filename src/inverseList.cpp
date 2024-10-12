#include <iostream>

struct Node
{
    int data;
    Node *next;
    Node() : data(0), next(nullptr) {}
    Node(int x) : data(x), next(nullptr) {}
    Node(int x, Node *next) : data(x), next(next) {}
};

// 链表类
class LinkedList
{
public:
    Node *head; // 头结点
    LinkedList()
    {
        head = new Node(); // 初始化时创建一个空的头结点
    }

    // 尾插法
    void insertAtTail(int val)
    {
        Node *newNode = new Node(val); // 创建新节点
        Node *temp = head;             // 从头结点开始

        // 遍历到链表的最后一个节点
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = newNode; // 将新节点插入到链表尾部
    }

    // 打印链表中的元素（跳过头结点）
    void printList() const
    {
        Node *temp = head->next; // 跳过头结点
        while (temp != nullptr)
        {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }

    // 析构函数，释放链表内存
    ~LinkedList()
    {
        Node *temp = head;
        while (temp != nullptr)
        {
            Node *next = temp->next;
            delete temp;
            temp = next;
        }
    }
};

// 核心就是头插法本身就有逆序，这里就采用头插法再将元素插入链表一遍
void inverseList(Node *head)
{
    Node *p = head->next;
    if(p == nullptr)
    {
        return;
    }
    head->next = nullptr;
    while (p != nullptr)
    {
        Node *q = p->next;
        p->next = head->next;
        head->next = p;
        p = q;
    }
}

int main()
{
    LinkedList list;
    list.insertAtTail(15);
    list.insertAtTail(27);
    list.insertAtTail(32);
    list.insertAtTail(45);

    list.printList();
    inverseList(list.head);

    list.printList();
}
