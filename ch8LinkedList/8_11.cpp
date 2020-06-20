#include "./singly_LL_SharedPtr.hpp"
#include <memory>
using namespace std;

shared_ptr<SLL_Node<int>> OddEvenMerge(shared_ptr<SLL_Node<int>> &L)
{
    if (!L)
        return L;

    auto even_list_head = L, odd_list_head = L->next;
    shared_ptr<SLL_Node<int>> prev_to_even_list_iter = nullptr;

    auto even_list_iter = even_list_head, odd_list_iter = odd_list_head;

    while (even_list_iter and odd_list_iter)
    {
        even_list_iter->next = odd_list_iter->next; // Update the next of even_list_iter
        prev_to_even_list_iter = even_list_iter;
        even_list_iter = even_list_iter->next;

        if (even_list_iter)
        {
            odd_list_iter->next = even_list_iter->next; // Update the next of odd_list_iter
            odd_list_iter = odd_list_iter->next;
        }
    }

    //Appends the odd list to the tail of even list.
    if (even_list_iter)
        even_list_iter->next = odd_list_head;
    else
        prev_to_even_list_iter->next = odd_list_head;
    return even_list_head;
}

int main(int argc, char const *argv[])
{
    shared_ptr<SLL_Node<int>> L1;

    //create a sorted list
    L1 = make_shared<SLL_Node<int>>(SLL_Node<int>{
        1, make_shared<SLL_Node<int>>(SLL_Node<int>{
               2, make_shared<SLL_Node<int>>(SLL_Node<int>{
                      3, make_shared<SLL_Node<int>>(SLL_Node<int>{
                             4, make_shared<SLL_Node<int>>(SLL_Node<int>{
                                    5, make_shared<SLL_Node<int>>(SLL_Node<int>{
                                           6, make_shared<SLL_Node<int>>(SLL_Node<int>{
                                                  7, make_shared<SLL_Node<int>>(SLL_Node<int>{
                                                         8, nullptr})})})})})})})});

    print_singly_linked_list(L1); //1 2 3 4 5 6 7 8
    L1 = OddEvenMerge(L1);
    print_singly_linked_list(L1); //1 3 5 7 2 4 6 8

    return 0;
}