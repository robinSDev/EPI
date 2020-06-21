#include <cassert>
#include <memory>
#include <stack>
#include <iostream>
#include <unordered_set>
using namespace std;

class PostingListNode
{
public:
    int order;
    shared_ptr<PostingListNode> next, jump;
};

// @include
void SetJumpOrder(const shared_ptr<PostingListNode> &L)
{
    stack<shared_ptr<PostingListNode>> s;
    int order = 0;
    s.emplace(L);
    while (!s.empty())
    {
        auto curr = s.top();
        s.pop();
        if (curr && curr->order == -1)
        {
            curr->order = order++;
            // Stack is last-in, first-out, and we want to process
            // the jump node first, so push next, then push jump.
            s.emplace(curr->next);
            s.emplace(curr->jump);
        }
    }
}

void SetJumpOrderHelper(const shared_ptr<PostingListNode> &L, int *order)
{
    if (L && L->order == -1)
    {
        L->order = (*order)++;
        SetJumpOrderHelper(L->jump, order);
        SetJumpOrderHelper(L->next, order);
    }
}

void SetJumpOrderRecursive(const shared_ptr<PostingListNode> &L)
{
    SetJumpOrderHelper(L, new int(0));
}

void PrintWithNext(shared_ptr<PostingListNode> L)
{
    while (L)
    {
        cout << L->order << " -> ";
        L = L->next;
    }
    cout << endl;
}

void PrintWithJumporNext(shared_ptr<PostingListNode> L)
{
    unordered_set<shared_ptr<PostingListNode>> hs;
    while (L and hs.find(L) == hs.end())
    {
        cout << L->order << " -> ";
        hs.insert(L);
        if ((L->jump) == nullptr)
            L = L->next;
        else
            L = L->jump;
    }
    cout << endl;
}

int testRec()
{
    shared_ptr<PostingListNode> L = nullptr, curr;
    curr = L;
    // Build a linked list L->1->2->3->4->5->nullptr.
    for (size_t i = 0; i < 5; ++i)
    {
        shared_ptr<PostingListNode> temp =
            make_shared<PostingListNode>(PostingListNode{-1, nullptr, nullptr});
        if (curr)
        {
            curr->next = temp;
            curr = temp;
        }
        else
        {
            curr = L = temp;
        }
    }
    L->jump = nullptr;                   // no jump from 1
    L->next->jump = L->next->next->next; // 2's jump points to 4
    L->next->next->jump = L;             // 3's jump points to 1
    L->next->next->next->jump = nullptr; // no jump from 4
    L->next->next->next->next->jump =
        L->next->next->next->next; // 5's jump points to 5
    PrintWithNext(L);
    PrintWithJumporNext(L);
    shared_ptr<PostingListNode> temp = L;
    SetJumpOrder(L);
    // output the jump-first order, it should be 0, 1, 4, 2, 3
    assert(temp->order == 0);
    temp = temp->next;
    assert(temp->order == 1);
    temp = temp->next;
    assert(temp->order == 4);
    temp = temp->next;
    assert(temp->order == 2);
    temp = temp->next;
    assert(temp->order == 3);
    PrintWithNext(L);
    PrintWithJumporNext(L);
    return 0;
}

int testItr()
{
    shared_ptr<PostingListNode> L = nullptr, curr;
    curr = L;
    // Build a linked list L->1->2->3->4->5->nullptr.
    for (size_t i = 0; i < 5; ++i)
    {
        shared_ptr<PostingListNode> temp =
            make_shared<PostingListNode>(PostingListNode{-1, nullptr, nullptr});
        if (curr)
        {
            curr->next = temp;
            curr = temp;
        }
        else
        {
            curr = L = temp;
        }
    }
    L->jump = nullptr;                   // no jump from 1
    L->next->jump = L->next->next->next; // 2's jump points to 4
    L->next->next->jump = L;             // 3's jump points to 1
    L->next->next->next->jump = nullptr; // no jump from 4
    L->next->next->next->next->jump =
        L->next->next->next->next; // 5's jump points to 5
    PrintWithNext(L);
    PrintWithJumporNext(L);
    shared_ptr<PostingListNode> temp = L;
    SetJumpOrder(L);
    // output the jump-first order, it should be 0, 1, 4, 2, 3
    assert(temp->order == 0);
    temp = temp->next;
    assert(temp->order == 1);
    temp = temp->next;
    assert(temp->order == 4);
    temp = temp->next;
    assert(temp->order == 2);
    temp = temp->next;
    assert(temp->order == 3);
    PrintWithNext(L);
    PrintWithJumporNext(L);
    return 0;
}
int main(int argc, char *argv[])
{
    assert((testItr() or testRec()) == 0);
}