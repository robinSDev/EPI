#include "./singly_LL_SharedPtr.hpp"
#include <memory>
using namespace std;

void delete_Kth_node_from_last(const shared_ptr<SLL_Node<int>> &head, int k)
{
    shared_ptr<SLL_Node<int>> dummy_head = make_shared<SLL_Node<int>>(SLL_Node<int>{0, head});
    shared_ptr<SLL_Node<int>> ahead = head, behind = dummy_head;
    while (k--)
    {
        ahead = ahead->next;
    }

    //move 'ahead' and 'behind' in tandem order
    while (ahead)
    {
        ahead = ahead->next;
        behind = behind->next;
    }

    behind->data = behind->next->data;
    behind->next = behind->next->next;
}

int main(int argc, char const *argv[])
{
    shared_ptr<SLL_Node<int>> L1;

    L1 = make_shared<SLL_Node<int>>(SLL_Node<int>{
        1, make_shared<SLL_Node<int>>(SLL_Node<int>{
               2, make_shared<SLL_Node<int>>(SLL_Node<int>{
                      3, make_shared<SLL_Node<int>>(SLL_Node<int>{
                             4, make_shared<SLL_Node<int>>(SLL_Node<int>{
                                    5, make_shared<SLL_Node<int>>(
                                           SLL_Node<int>{6, nullptr})})})})})});

    print_singly_linked_list(L1); //1 2 3 4 5 6
    delete_Kth_node_from_last(L1, 5);
    print_singly_linked_list(L1); //2 3 4 5 6

    delete_Kth_node_from_last(L1, 4);
    print_singly_linked_list(L1); //3 4 5 6

    delete_Kth_node_from_last(L1, 4);
    print_singly_linked_list(L1); //3 4 5 6

    return 0;
}