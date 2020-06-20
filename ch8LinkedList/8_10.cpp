#include "./singly_LL_SharedPtr.hpp"
#include <memory>
using namespace std;

shared_ptr<SLL_Node<int>> CyclicRightShift_k_times(shared_ptr<SLL_Node<int>> &L, int k)
{
    if (!L)
        return L;

    //Compute the length of L and get its tail
    auto tail = L;
    int n = 1;
    while (tail->next)
    {
        tail = tail->next;
        ++n;
    }

    //important step
    k %= n; //check if k is multiple of n, only, if yes, return the original list, no need to rotate
    if (k == 0)
        return L;

    tail->next = L; //Makes a cycle by connecting tail to the next

    int steps_to_new_head = n - k;
    auto new_tail = tail;
    while (steps_to_new_head--)
        new_tail = new_tail->next;

    auto new_head = new_tail->next;
    new_tail->next = nullptr;
    return new_head;
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
    L1 = CyclicRightShift_k_times(L1, 8);
    print_singly_linked_list(L1); //1 2 3 4 5 6 7 8

    L1 = CyclicRightShift_k_times(L1, 2);
    print_singly_linked_list(L1); //7 8 1 2 3 4 5 6

    return 0;
}