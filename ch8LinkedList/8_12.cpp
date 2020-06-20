#include "./singly_LL_SharedPtr.hpp"
#include <cassert>
#include <memory>
#include <stack>
using namespace std;

//TC: O(n + n/2) ~ O(n)
//SC: O(n/2) ~ O(n)
bool isPalindrome(shared_ptr<SLL_Node<int>> L)
{
    if (!L)
        return true;
    stack<shared_ptr<SLL_Node<int>>> s;
    auto fast = L, slow = L;
    while (fast and fast->next)
        fast = fast->next->next, slow = slow->next;
    auto &right_half_ptr = slow;
    while (right_half_ptr)
    {
        s.push(right_half_ptr);
        right_half_ptr = right_half_ptr->next;
    }
    while (!s.empty())
    {
        auto right_ptr = s.top();
        s.pop();
        if (right_ptr->data != L->data)
            return false;
        L = L->next;
    }
    return true;
}

//From the book
shared_ptr<SLL_Node<int>> ReverseLinkedList(shared_ptr<SLL_Node<int>> &L)
{
    //print_singly_linked_list(L);
    shared_ptr<SLL_Node<int>> curr = L, prev = nullptr;
    while (curr)
    {
        auto temp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = temp;
    }
    //print_singly_linked_list(prev);
    return prev;
}

bool IsLinkedListAPalindrome(shared_ptr<SLL_Node<int>> L)
{
    if (L == nullptr)
    {
        return true;
    }

    // Finds the second half of L.
    shared_ptr<SLL_Node<int>> slow = L, fast = L;
    while (fast && fast->next)
    {
        fast = fast->next->next, slow = slow->next;
    }

    // Compares the first half and the reversed second half lists.
    auto first_half_iter = L, second_half_iter = ReverseLinkedList(slow);
    while (second_half_iter && first_half_iter)
    {
        if (second_half_iter->data != first_half_iter->data)
        {
            return false;
        }
        second_half_iter = second_half_iter->next;
        first_half_iter = first_half_iter->next;
    }
    return true;
}

int main(int argc, char const *argv[])
{
    shared_ptr<SLL_Node<int>> L1, L2, L3;

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
        1, make_shared<SLL_Node<int>>(SLL_Node<int>{
               2, make_shared<SLL_Node<int>>(SLL_Node<int>{
                      3, make_shared<SLL_Node<int>>(SLL_Node<int>{
                             4, make_shared<SLL_Node<int>>(SLL_Node<int>{
                                    3, make_shared<SLL_Node<int>>(SLL_Node<int>{
                                           2, make_shared<SLL_Node<int>>(SLL_Node<int>{
                                                  1, nullptr})})})})})})});

    assert(isPalindrome(L1) == false);
    assert(isPalindrome(L2) == true);
    assert(isPalindrome(L3) == true);

    //book Solution
    assert(IsLinkedListAPalindrome(L1) == false);
    assert(IsLinkedListAPalindrome(L2) == true);
    assert(IsLinkedListAPalindrome(L3) == true);

    return 0;
}