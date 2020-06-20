#include <cassert>
#include "./singly_LL_SharedPtr.hpp"
#include <memory>
#include <stack>
using namespace std;

shared_ptr<SLL_Node<int>> AddTwoNumbers(shared_ptr<SLL_Node<int>> L1,
                                        shared_ptr<SLL_Node<int>> L2)
{
    shared_ptr<SLL_Node<int>> dummy_head(new SLL_Node<int>);
    auto place_iter = dummy_head;
    int carry = 0;
    while (L1 || L2)
    {
        int sum = carry;
        if (L1)
        {
            sum += L1->data;
            L1 = L1->next;
        }
        if (L2)
        {
            sum += L2->data;
            L2 = L2->next;
        }
        int digit = sum % 10;
        place_iter->next =
            make_shared<SLL_Node<int>>(SLL_Node<int>{digit, nullptr});
        carry = sum / 10, place_iter = place_iter->next;
    }
    // carry cannot exceed 1, so we never need to add more than one node.
    if (carry)
    {
        place_iter->next =
            make_shared<SLL_Node<int>>(SLL_Node<int>{carry, nullptr});
    }
    return dummy_head->next;
}

int test1()
{
    shared_ptr<SLL_Node<int>> L;
    L = make_shared<SLL_Node<int>>(SLL_Node<int>{
        2, make_shared<SLL_Node<int>>(SLL_Node<int>{
               4, make_shared<SLL_Node<int>>(SLL_Node<int>{
                      3, nullptr})})});
    shared_ptr<SLL_Node<int>> R;
    R = make_shared<SLL_Node<int>>(SLL_Node<int>{0, nullptr});
    auto S = AddTwoNumbers(L, R);
    assert(S->data == 2 && S->next->data == 4 && S->next->next->data == 3);
    return 0;
}

int test2()
{
    shared_ptr<SLL_Node<int>> L, R, S;
    L = make_shared<SLL_Node<int>>(SLL_Node<int>{
        3, make_shared<SLL_Node<int>>(SLL_Node<int>{
               4, make_shared<SLL_Node<int>>(SLL_Node<int>{
                      2, nullptr})})});
    R = make_shared<SLL_Node<int>>(SLL_Node<int>{
        7, make_shared<SLL_Node<int>>(SLL_Node<int>{
               5, make_shared<SLL_Node<int>>(SLL_Node<int>{
                      7, nullptr})})});
    S = AddTwoNumbers(L, R);

    assert(S->data == 0 && S->next->data == 0 && S->next->next->data == 0 &&
           S->next->next->next->data == 1);
    return 0;
}

int test3()
{
    shared_ptr<SLL_Node<int>> L, R, S;
    L = make_shared<SLL_Node<int>>(SLL_Node<int>{1, nullptr});
    R = make_shared<SLL_Node<int>>(SLL_Node<int>{1, nullptr});
    S = AddTwoNumbers(L, R);
    assert(S->data == 2 && S->next == nullptr);
    return 0;
}

int test4()
{
    shared_ptr<SLL_Node<int>> L, R, S;
    L = make_shared<SLL_Node<int>>(SLL_Node<int>{5, nullptr});
    R = make_shared<SLL_Node<int>>(SLL_Node<int>{5, nullptr});
    S = AddTwoNumbers(L, R);
    assert(S->data == 0 && S->next->data == 1 && S->next->next == nullptr);
    return 0;
}

int main(int argc, char *argv[])
{
    assert((test1() and test2() and test3() and test4()) == 0);
    return 0;
}