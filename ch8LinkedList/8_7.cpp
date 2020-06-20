#include "./singly_LL_SharedPtr.hpp"
#include <memory>
using namespace std;

void delete_non_tail_node(const shared_ptr<SLL_Node<int>> &nodeToDelete)
{
    try
    {
        if (nodeToDelete == nullptr or nodeToDelete->next == nullptr)
            throw std::invalid_argument("A null or tail node supplied as argument.");
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "invalid_argument: " << e.what() << '\n';
        return;
    }

    nodeToDelete->data = nodeToDelete->next->data;
    nodeToDelete->next = nodeToDelete->next->next;
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

    print_singly_linked_list(L1);
    delete_non_tail_node(L1->next->next);
    print_singly_linked_list(L1);

    delete_non_tail_node(L1->next->next->next->next); //should throw invalid argument
    return 0;
}