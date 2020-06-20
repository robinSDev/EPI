#include "./singly_LL_SharedPtr.hpp"
#include <iostream>
#include <vector>
#include <memory>
#include <cassert>
#include <unordered_set>
using namespace std;

//Solution other than the one in the book
//Time Complexity: O(m),
//where m is the number of nodes to reach the overlapping node of that list whose head is further from the overlapping node than the other list
//Space Complexity: O(m), consumed by unordered_set

shared_ptr<SLL_Node<int>> overlapping_node_hm(shared_ptr<SLL_Node<int>> L1, shared_ptr<SLL_Node<int>> L2)
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

    unordered_set<shared_ptr<SLL_Node<int>>> set_of_ptrs;
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

int Length(shared_ptr<SLL_Node<int>> head);

void AdvanceListByK(int k, shared_ptr<SLL_Node<int>> *head);

shared_ptr<SLL_Node<int>> OverlappingNoCycleLists(shared_ptr<SLL_Node<int>> L1, shared_ptr<SLL_Node<int>> L2);

shared_ptr<SLL_Node<int>> HasCycle(shared_ptr<SLL_Node<int>> &head);

// Calculates the distance between a and b.

int Distance(shared_ptr<SLL_Node<int>> a, shared_ptr<SLL_Node<int>> b)
{
    int dis = 0;
    while (a != b)
    {
        a = a->next, ++dis;
    }
    return dis;
}


shared_ptr<SLL_Node<int>> OverlappingLists(shared_ptr<SLL_Node<int>> L1,
                                         shared_ptr<SLL_Node<int>> L2)
{
    // Store the start of cycle if any.
    auto root1 = HasCycle(L1), root2 = HasCycle(L2);

    if (!root1 && !root2)
    {
        // Both lists don't have cycles.
        return OverlappingNoCycleLists(L1, L2);
    }
    else if ((root1 && !root2) || (!root1 && root2))
    {
        // One list has cycle, and one list has no cycle.
        return nullptr;
    }
    // Both lists have cycles.
    auto temp = root2;
    do
    {
        temp = temp->next;
    } while (temp != root1 && temp != root2);

    // L1 and L2 do not end in the same cycle.
    if (temp != root1)
    {
        return nullptr; // Cycles are disjoint.
    }

    // L1 and L2 end in the same cycle, locate the overlapping node if they
    // first overlap before cycle starts.
    int stem1_length = Distance(L1, root1), stem2_length = Distance(L2, root2);
    AdvanceListByK(abs(stem1_length - stem2_length),
                   stem1_length > stem2_length ? &L1 : &L2);
    while (L1 != L2 && L1 != root1 && L2 != root2)
    {
        L1 = L1->next, L2 = L2->next;
    }

    // If L1 == L2 before reaching root1, it means the overlap first occurs
    // before the cycle starts; otherwise, the first overlapping node is not
    // unique, so we can return any node on the cycle.
    return L1 == L2 ? L1 : root1;
}

int test1()
{
    vector<int> a = {1, 2, 3, 6, 7, 8, 9, 10, 11}, b = {4, 5}, c = {12, 13, 14, 15, 16, 17, 18, 19};
    LinkedList<int> l1(a), l2(b), l3(c);
    //create cycle in l1
    l1.tail->next = l1.head;

    //overlap l1 and l2
    l2.tail->next = l1.head->next->next->next; //atach 5 to 6
    l2.tail = l1.tail;                         //update l2's tail pointer

    cout << "l1.head->next->next->next: " << l1.head->next->next->next->data << endl;
    cout << overlapping_node_hm(l1.head, l2.head)->data << endl;
    cout << OverlappingLists(l1.head, l2.head)->data << endl;

    //negative test for, both should return 0
    cout << ((overlapping_node_hm(l1.head, l3.head) == nullptr) ? 0 : 1) << endl;
    cout << ((OverlappingLists(l1.head, l3.head) == nullptr) ? 0 : 1);

    return 0;
}

int test2()
{
    shared_ptr<SLL_Node<int>> L1, L2;
    // L1: 1->2->3->4->5->6-
    //              ^  ^    |
    //              |  |____|
    // L2: 7->8-----
    L1 = make_shared<SLL_Node<int>>(SLL_Node<int>{
        1, make_shared<SLL_Node<int>>(SLL_Node<int>{
               2, make_shared<SLL_Node<int>>(SLL_Node<int>{
                      3, make_shared<SLL_Node<int>>(SLL_Node<int>{
                             4, make_shared<SLL_Node<int>>(SLL_Node<int>{
                                    5, make_shared<SLL_Node<int>>(
                                           SLL_Node<int>{6, nullptr})})})})})});
    L1->next->next->next->next->next->next = L1->next->next->next->next;

    L2 = make_shared<SLL_Node<int>>(SLL_Node<int>{
        7, make_shared<SLL_Node<int>>(SLL_Node<int>{8, nullptr})});
    L2->next->next = L1->next->next->next;
    assert(OverlappingLists(L1, L2)->data == 4);

    // L1: 1->2->3->4->5->6-
    //           ^     ^    |
    //           |     |____|
    // L2: 7->8---
    L2->next->next = L1->next->next;
    assert(OverlappingLists(L1, L2)->data == 3);
    return 0;
}

int test3()
{
    shared_ptr<SLL_Node<int>> L1, L2;
    // L1: 1->2->3->null
    L1 = make_shared<SLL_Node<int>>(SLL_Node<int>{
        1, make_shared<SLL_Node<int>>(SLL_Node<int>{
               2, make_shared<SLL_Node<int>>(SLL_Node<int>{3, nullptr})})});
    L2 = L1->next->next;
    assert(OverlappingLists(L1, L2)->data == 3);
    // L2: 4->5->null
    L2 = make_shared<SLL_Node<int>>(SLL_Node<int>{
        4, make_shared<SLL_Node<int>>(SLL_Node<int>{5, nullptr})});
    assert(!OverlappingLists(L1, L2));
    L1->next->next->next = L1;
    assert(!OverlappingLists(L1, L2));
    L2->next->next = L2;
    assert(!OverlappingLists(L1, L2));
    L2->next->next = L1;
    assert(OverlappingLists(L1, L2));
    return 0;
}

int main(int argc, char const *argv[])
{
    assert((test1() and test2() and test3())==0);
    return 0;
}


shared_ptr<SLL_Node<int>> HasCycle(shared_ptr<SLL_Node<int>> &head)
{
    shared_ptr<SLL_Node<int>> fast = head, slow = head;

    while (fast and fast->next and fast->next->next)
    {
        fast = fast->next->next;
        slow = slow->next;
        if (fast == slow)
        {
            //cycle found
            shared_ptr<SLL_Node<int>> cycle_length_calculator = fast;
            unsigned cycle_length = 0;
            do //let the 'cycle_length_calculator' go around in the cycle till it again reaches the start, i.e. 'slow'
            {
                ++cycle_length;
                cycle_length_calculator = cycle_length_calculator->next;
            } while (slow != cycle_length_calculator);
            cout << "cycle_length: " << cycle_length << endl;
            // If loop exists. Start slow from
            // head and fast from meeting point.
            slow = head;
            while (slow != fast)
            {
                slow = slow->next;
                fast = fast->next;
            }

            return slow;
        }
    }
    return nullptr; //no cycle
}


int Length(shared_ptr<SLL_Node<int>> head)
{
    int count = 0;
    while (head)
    {
        head = head->next;
        ++count;
    }
    return count;
}

void AdvanceListByK(int k, shared_ptr<SLL_Node<int>> *head)
{
    while (k--)
    {
        *head = (*head)->next;
    }
}
//TC: O(n), n: total number of nodes in both lists combined
//SC: O(1)

shared_ptr<SLL_Node<int>> OverlappingNoCycleLists(shared_ptr<SLL_Node<int>> L1, shared_ptr<SLL_Node<int>> L2)
{
    int L1_len = Length(L1), L2_len = Length(L2);
    //Advance the longer list by the difference in length of the two lists
    AdvanceListByK(abs(L1_len - L2_len), L1_len > L2_len ? &L1 : &L2);

    while (L1 and L2 and L1 not_eq L2)
    {
        L1 = L1->next, L2 = L2->next;
    }
    return L1; //if it return nullptr, it would mean there is no overlap here
}
