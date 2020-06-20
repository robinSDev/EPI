#include "./singly_LL_SharedPtr.hpp"
#include <cassert>
#include <memory>
#include <stack>
using namespace std;

shared_ptr<SLL_Node<int>> ListPivoting(shared_ptr<SLL_Node<int>> L, int x)
{
    shared_ptr<SLL_Node<int>> less_head, equal_head, greater_head;
    less_head = make_shared<SLL_Node<int>>(SLL_Node<int> {0, nullptr});
    equal_head = make_shared<SLL_Node<int>>(SLL_Node<int> {0, nullptr});
    greater_head = make_shared<SLL_Node<int>>(SLL_Node<int> {0, nullptr});

    shared_ptr<SLL_Node<int>> less_iter = less_head, equal_iter = equal_head, greater_iter = greater_head;

    //Populates the three lists.
    shared_ptr<SLL_Node<int>> iter = L;

    while(iter)
    {
        shared_ptr<SLL_Node<int>> &next_node = (iter->data < x) ? less_iter : ((iter->data == x) ? equal_iter : greater_iter);
        next_node->next = iter;
        next_node = iter;
        iter = iter->next;   
    }
    
    //Combine the three lists.
    greater_iter->next = nullptr;
    equal_iter->next = greater_head->next;
    less_iter->next = equal_head->next;
    return less_head->next;
}

int main(int argc, char const *argv[])
{
    shared_ptr<SLL_Node<int>> L1, L2, L3;

    //create a sorted list
    L1 = make_shared<SLL_Node<int>>(SLL_Node<int>{
        1, make_shared<SLL_Node<int>>(SLL_Node<int>{
               2, make_shared<SLL_Node<int>>(SLL_Node<int>{
                      30, make_shared<SLL_Node<int>>(SLL_Node<int>{
                             40, make_shared<SLL_Node<int>>(SLL_Node<int>{
                                    50, make_shared<SLL_Node<int>>(SLL_Node<int>{
                                           60, make_shared<SLL_Node<int>>(SLL_Node<int>{
                                                  7, make_shared<SLL_Node<int>>(SLL_Node<int>{
                                                         8, nullptr})})})})})})})});

    L2 = make_shared<SLL_Node<int>>(SLL_Node<int>{
        1, make_shared<SLL_Node<int>>(SLL_Node<int>{
               2, make_shared<SLL_Node<int>>(SLL_Node<int>{
                      3, make_shared<SLL_Node<int>>(SLL_Node<int>{
                             4, make_shared<SLL_Node<int>>(SLL_Node<int>{
                                    4, make_shared<SLL_Node<int>>(SLL_Node<int>{
                                           3, make_shared<SLL_Node<int>>(SLL_Node<int>{
                                                  2, make_shared<SLL_Node<int>>(SLL_Node<int>{
                                                         1, nullptr})})})})})})})});

    L3 = make_shared<SLL_Node<int>>(SLL_Node<int>{
        7, make_shared<SLL_Node<int>>(SLL_Node<int>{
               6, make_shared<SLL_Node<int>>(SLL_Node<int>{
                      5, make_shared<SLL_Node<int>>(SLL_Node<int>{
                             4, make_shared<SLL_Node<int>>(SLL_Node<int>{
                                    3, make_shared<SLL_Node<int>>(SLL_Node<int>{
                                           2, make_shared<SLL_Node<int>>(SLL_Node<int>{
                                                  1, nullptr})})})})})})});

    print_singly_linked_list(L1);
    L1 = ListPivoting(L1,10);
    print_singly_linked_list(L1); //1 2 7 8 30 40 50 60

    print_singly_linked_list(L2);
    L2 = ListPivoting(L2,2);
    print_singly_linked_list(L2); //1 1 2 2 3 4 4 3

    print_singly_linked_list(L3);
    L3 = ListPivoting(L3,4);
    print_singly_linked_list(L3); //7 6 5 

    return 0;
}