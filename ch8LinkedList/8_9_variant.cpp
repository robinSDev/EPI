#include "./singly_LL_SharedPtr.hpp"
#include <memory>
using namespace std;

void RemoveNodeIfMoreThan_m_InstancesExits(const shared_ptr<SLL_Node<int>> &L, int m)
{
    auto iter = L;
    while (iter)
    {
        int dup_count = 1;
        //uses next distinct to find the next distinct values
        auto next_distinct = iter->next;
        while (next_distinct && next_distinct->data == iter->data)
        {
            next_distinct = next_distinct->next;
            ++dup_count;
        }
        if(dup_count > m)
            iter->next = next_distinct;
        iter = next_distinct;
    }
}

int main(int argc, char const *argv[])
{
    shared_ptr<SLL_Node<int>> L1;

    //create a sorted list
    L1 = make_shared<SLL_Node<int>>(SLL_Node<int>{
        1, make_shared<SLL_Node<int>>(SLL_Node<int>{
               2, make_shared<SLL_Node<int>>(SLL_Node<int>{
                      2, make_shared<SLL_Node<int>>(SLL_Node<int>{
                             4, make_shared<SLL_Node<int>>(SLL_Node<int>{
                                    4, make_shared<SLL_Node<int>>(SLL_Node<int>{
                                           5, make_shared<SLL_Node<int>>(SLL_Node<int>{
                                                  5, make_shared<SLL_Node<int>>(SLL_Node<int>{
                                                         5, nullptr})})})})})})})});

    print_singly_linked_list(L1); //1 2 2 4 4 5 5
    RemoveNodeIfMoreThan_m_InstancesExits(L1, 2);
    print_singly_linked_list(L1); //1 2 4 5

    return 0;
}