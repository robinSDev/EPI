#ifndef SINGLY_LL_SHAREDPTR_HPP_
#define SINGLY_LL_SHAREDPTR_HPP_
#pragma once
#include <iostream>
#include <vector>
#include <unordered_set>
#include <memory>
using namespace std;

template <typename T>
struct SLL_Node
{
    T data;
    shared_ptr<SLL_Node<T>> next;
};

template <typename T>
class LinkedList
{
public:
    LinkedList(const vector<T> &stream)
    {
        for (const T &i : stream)
            insert(i);
    }

    void insert(const T &data)
    {
        shared_ptr<SLL_Node<T>> n = make_shared<SLL_Node<T>>(SLL_Node<int>{data, nullptr});
        if (!head)
            head = tail = n;
        else
        {
            tail->next = n;
            tail = n;
        }
    }

    shared_ptr<SLL_Node<T>> head = nullptr, tail = nullptr;
};

template <typename T>
void print_singly_linked_list(shared_ptr<SLL_Node<T>> &head)
{
    if (!head)
    {
        cout << "The list is empty\n";
        return;
    }
    shared_ptr<SLL_Node<T>> trav = head;
    while (trav)
    {
        cout << trav->data << " ";
        trav = trav->next;
    }
    cout << endl;
};
#endif //SINGLY_LL_SHAREDPTR_HPP_