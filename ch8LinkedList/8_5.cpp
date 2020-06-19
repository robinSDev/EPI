#include "./singly_linked_list.hpp"
#include <iostream>
#include <vector>
using namespace std;

//Solution other than the one in the book
//Time Complexity: O(m),
//where m is the number of nodes to reach the overlapping node of that list whose head is further from the overlapping node than the other list
//Space Complexity: O(m), consumed by unordered_set
template <typename T>
SLL_Node<T> *overlapping_node_hm(SLL_Node<T> *L1, SLL_Node<T> *L2)
{
    try
    {
        if (!L1 || !L2)
            throw std::invalid_argument("One of the supplied argument as list head is a nullptr.");
    }
    catch (const std::invalid_argument &ia)
    {
        std::cerr << "Invalid argument: " << ia.what() << '\n';
        return nullptr;
    }

    unordered_set<SLL_Node<T> *> set_of_ptrs;
    while (L1 && L2)
    {
        if (L1 == L2)
            return L1;
        auto it1 = set_of_ptrs.find(L1);
        if (it1 != set_of_ptrs.end())
            return L1;
        auto it2 = set_of_ptrs.find(L2);
        if (it2 != set_of_ptrs.end())
            return L2;
        set_of_ptrs.insert(L1), set_of_ptrs.insert(L2);
        L1 = L1->next;
        L2 = L2->next;
    }
    return nullptr; //no overlap found
}

//Solution from the book
template <typename T>
int Length(SLL_Node<T> *head)
{
    int count = 0;
    while (head)
    {
        head = head->next;
        ++count;
    }
    return count;
}
template <typename T>
void AdvanceListByK(int k, SLL_Node<T> **head)
{
    while (k--)
    {
        *head = (*head)->next;
    }
}
//TC: O(n), n: total number of nodes in both lists combined
//SC: O(1)
template<typename T>
SLL_Node<T> *OverlappingNoCycle(SLL_Node<T> *L1, SLL_Node<T> *L2)
{
    int L1_len = Length(L1), L2_len = Length(L2);
    //Advance the longer list by the difference in length of the two lists
    AdvanceListByK(abs(L1_len - L2_len), L1_len > L2_len ? &L1 : &L2);

    while(L1 and L2 and L1 not_eq L2) 
    {
        L1 = L1->next, L2 = L2->next;
    }
    return L1; //if it return nullptr, it would mean there is no overlap here
}


int main(int argc, char const *argv[])
{
    vector<int> a = {1, 2, 3, 6, 7, 8, 9, 10, 11}, b = {4, 5}, c = {12,13,14,15,16,17,18,19};
    LinkedList<int> l1(a), l2(b), l3(c);
    l2.tail->next = l1.head->next->next->next; //atach 5 to 6
    l2.tail = l1.tail;                         //update l2's tail pointer

    cout << "l1.head->next->next->next: " << l1.head->next->next->next << endl;
    cout << overlapping_node_hm(l1.head, l2.head) << endl;
    cout << OverlappingNoCycle(l1.head, l2.head) << endl;

    //negative test for, both should return 0
    cout << ((overlapping_node_hm(l1.head, l3.head) == nullptr) ? 0 : 1 )<< endl;
    cout << ((OverlappingNoCycle(l1.head, l3.head) == nullptr) ? 0 : 1);

    return 0;
}
