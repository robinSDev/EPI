#include "./singly_linked_list.hpp"
#include <iostream>
using namespace std;

template <typename T>
SLL_Node<T> *reverse_SLL_subList(SLL_Node<T> *head, unsigned start, unsigned finish)
{
    try
    {
        if (start == finish or start > finish)
            throw std::invalid_argument("Here, start == finish or start > finish");
        else if (!head)
            throw std::invalid_argument("Here, the header supplied was pointing to null");
    }
    catch (const std::invalid_argument &ia)
    {
        std::cerr << "Invalid argument: " << ia.what() << '\n';
        return head;
    }

    SLL_Node<T> *dummy_head = new SLL_Node<T>;
    dummy_head->next = head;
    SLL_Node<T> *subList_head = dummy_head;

    unsigned k = 1;
    while (k++ < start)
        subList_head = subList_head->next;

    //subList_head stays at the ('start'- 1) position
    //if start was 1, then subList_head stays at dummy_head
    cout << "subList_head -> data : " << subList_head->data << endl;

    //subList_iter points to actuals start of subList
    SLL_Node<T> *subList_iter = subList_head->next;
    SLL_Node<T> *temp;
    //reverse subList
    while (start++ < finish and subList_iter->next)
    {
        temp = subList_iter->next;       // let temp point to the next provided by subList_iter
        subList_iter->next = temp->next; // Update the next of subList_iter to the next provided by temp
        temp->next = subList_head->next; // Update the next of temp by pointing it to next of subList_head
        subList_head->next = temp;       // Update current front of the sublist by attaching it to next of subList_head / dummy_head
    }
    if (start < finish)
        cout << "The supplied 'finish' parameter was greater than the length of the linked list. "
             << "So the list was sorted from the supplier 'start' till the end\n";
    return dummy_head->next;
}

int main(int argc, char const *argv[])
{
    vector<int> v1 = {1, 2, 3, 4, 5, 10, 9, 8, 7, 6, 11, 12, 13, 14, 15};
    LinkedList<int> l1(v1);
    print_singly_linked_list(l1.head);

    l1.head = reverse_SLL_subList(l1.head, 6, 10);
    print_singly_linked_list(l1.head);

    l1.head = reverse_SLL_subList(l1.head, 1, 15);
    print_singly_linked_list(l1.head);

    l1.head = reverse_SLL_subList(l1.head, 1, 25);
    print_singly_linked_list(l1.head);

    l1.head = reverse_SLL_subList(l1.head, -100, 25);
    print_singly_linked_list(l1.head);

    return 0;
}
