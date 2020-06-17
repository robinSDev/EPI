#include "./singly_linked_list.hpp"
using namespace std;

template <typename T>
SLL_Node<T> *reverse_singly_linked_list(SLL_Node<T> *head)
{
    SLL_Node<T> *curr = head, *prev = nullptr, *nextNodePtr = nullptr;
    while (curr)
    {
        nextNodePtr = curr->next; //save next node's address
        curr->next = prev;        //make this node point to previous node, first node would point to nullptr
        prev = curr;              //make prev point to curr node's address
        curr = nextNodePtr;       //update the curr to next node in the original list
    }
    return prev;
}

int main(int argc, char const *argv[])
{
    vector<int> v1 = {1, 3, 5, 7, 9, 11}, v2 = {2, 4, 6, 8, 10, 12};
    LinkedList<int> l1(v1), l2(v2);
    print_singly_linked_list(l1.head);
    print_singly_linked_list(l2.head);

    l1.head = reverse_singly_linked_list(l1.head);
    l2.head = reverse_singly_linked_list(l2.head);

    print_singly_linked_list(l1.head);
    print_singly_linked_list(l2.head);
    return 0;
}
