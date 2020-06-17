#include "./singly_linked_list.hpp"
#include <vector> //for test data
using namespace std;

template <typename T>
void AppendNode(SLL_Node<T> *&node, SLL_Node<T> *&tail)
{
    tail->next = node; //append new node at the tail of the list
    tail = node;       //update the tail, as this new node is the current tail
    node = (node)->next; //move ahead in the list from with this function was called from
}

template <typename T>
SLL_Node<T> *mergeTwoSinglyLinkedList(SLL_Node<T> *L1, SLL_Node<T> *L2)
{
    SLL_Node<T> *dummy_head = new SLL_Node<T>(); //dummy head, not the actual head, its next would contain the actual head
    SLL_Node<T> *tail = dummy_head;

    while (L1 and L2)
    {
        AppendNode(L1->data <= L2->data ? L1 : L2, tail);
    }

    tail->next = L1 ? L1 : L2;
    return dummy_head->next;
}

int main(int argc, char const *argv[])
{
    vector<int> v1 = {1, 3, 5, 7, 9, 11}, v2 = {2, 4, 6, 8, 10, 12};
    LinkedList<int> l1(v1), l2(v2);
    print_singly_linked_list(l1.head);
    print_singly_linked_list(l2.head);

    SLL_Node<int> *head = mergeTwoSinglyLinkedList(l1.head, l2.head);
    print_singly_linked_list(head);

    return 0;
}
