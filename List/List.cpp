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
    if (p == nullptr)
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
// 合并两个有序单链表，输出合并后的有序单链表。有序链表直接在List1上进行合并
void mergeTwoLists(LinkedList &list1, LinkedList &list2)
{
    Node *p = list1.head->next;
    Node *q = list2.head->next;
    // 指向合并后新链表的最后一个元素，
    // 起始位置应该位于List1的头结点位置，而不是list.head->next
    // 因为你也不能确定list.head->next的数字是否符合新链表的起始位置。
    Node *last = list1.head;
    list2.head->next = nullptr;
    while (p->next != nullptr && q->next != nullptr)
    {
        if (p->data < q->data)
        {
            last->next = p;
            p = p->next;
        }
        else
        {
            last->next = q;
            q = q->next;
        }
        last = last->next;
    }
    if (p != nullptr)
    {
        last->next = p;
    }
    if (q != nullptr)
    {
        last->next = q;
    }
}

// 判断输入单链表是否有环
bool hasCycle(Node *head, int &pos)
{
    // 解法采用快慢指针。快慢指针能够相遇就是有环
    // 通过数学计算可得环的入口位置。
    Node *fast = head;
    Node *slow = head;

    Node *x = head;
    pos = 0;
    while (fast != nullptr && fast->next != nullptr)
    {
        fast = fast->next->next;
        slow = slow->next;
        if (fast == slow)
        {
            // 说明有环了
            while (x != slow)
            {
                x = x->next;
                slow = slow->next;
                pos++;
                if (x == slow)
                {
                    break;
                }
            }
            return true;
        }
    }
    return false;
}
// 判断两个链表是否相交，返回相交的起始节点，如果没有则返回nullptr
Node *getIntersectionNode(int& intersectVal, Node *listA, Node *listB)
{
    //获取两个链表的长度，长的链表先跑长的位置，等到走到同一个位置就是相交位置。
    Node* l1 = listA->next;
    Node* l2 = listB->next;
    int temp1 = 0;
    int temp2 = 0;
    int n = 0;
    while (l1 != nullptr)
    {
        l1 = l1->next;
        temp1++;
    }
    while (l2 != nullptr)
    {
        l2 = l2->next;
        temp2++;
    }
    l1 = listA;
    l2 = listB;
    if(temp1 > temp2)
    {
        n = temp1 - temp2;
        
        for (int i = 0;i < n;i++)
        {
            l1 = l1->next;
        }
    }
    else
    {
        n = temp2 - temp1;
        for (int i = 0;i < n;i++)
        {
            l2 = l2->next;
        }
    }
    while (l1 != nullptr && l2 != nullptr)
    {
        l1 = l1->next;
        l2 = l2->next;
        if(l1 == l2)
        {
            intersectVal = l1->data;
            return l1;
        }
    }
    return nullptr;
}
int main()
{
    Node head1;
    Node n1(25),n2(67),n3(32),n4(18);
    head1.next = &n1;
    n1.next = &n2;
    n2.next = &n3;
    n3.next = &n4;
    n4.next = nullptr;

    Node head2;
    Node m1(1),m2(3),m3(4),m4(9);
    head2.next = &m1;
    m1.next = &m2;
    m2.next = &m3;
    m3.next = &m4;
    m4.next = &n3;

    int value = 0;

    auto node = getIntersectionNode(value,&head1,&head2);
    if(node != nullptr)
    {
        std::cout << "两链表相交，交点值为 " << value << std::endl;
    }
    
}
// int main()
// {
//     Node head;
//     Node n1(25),n2(67),n3(32),n4(18);
//     head.next = &n1;
//     n1.next = &n2;
//     n2.next = &n3;
//     n3.next = &n4;
//     n4.next = &n2;

//     int pos = 0;
//     if(hasCycle(&head,pos))
//     {
//         std::cout << "存在环，环的入口位置为" << pos << std::endl;
//     }
// }

// int main()
// {
//     int arr[] = {1, 2, 4, 6, 7};
//     int brr[] = {1, 3, 4, 9};
//     LinkedList list1;
//     LinkedList list2;
//     for (auto i : arr)
//     {
//         list1.insertAtTail(i);
//     }
//     for (auto i : brr)
//     {
//         list2.insertAtTail(i);
//     }

//     list1.printList();
//     list2.printList();
//     mergeTwoLists(list1, list2);

//     list1.printList();
// }
