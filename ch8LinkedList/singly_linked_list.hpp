#ifndef SINGLY_LINKED_LIST_HPP
#define SINGLY_LINKED_LIST_HPP
#pragma once
#include <iostream>
#include <vector>
#include <unordered_set>
using std::unordered_set;
using std::cout;
using std::endl;
using std::vector;

template <typename T>
struct SLL_Node
{
    T data;
    SLL_Node *next;
    SLL_Node(int d) { data = d; next = nullptr;}
    SLL_Node() { next = nullptr; }
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

    ~LinkedList()
    {   //hash set for those lists which contain cycle
        if (!head)
            return;
        unordered_set<SLL_Node<T>*> set_of_ptrs;
        SLL_Node<T> *trav = head, *nextNodePtr = nullptr;
        while (trav and set_of_ptrs.find(trav) == set_of_ptrs.end())
        {
            set_of_ptrs.insert(trav);
            nextNodePtr = trav->next;
            delete trav;
            trav = nextNodePtr;
        }
    }
    void insert(const T &data)
    {
        SLL_Node<T> *n = new SLL_Node<T>(data);
        if (!head)
            head = tail = n;
        else
        {
            tail->next = n;
            tail = n;
        }
    }

    SLL_Node<T> *head = nullptr, *tail = nullptr;
};

template <typename T>
void print_singly_linked_list(SLL_Node<T> *&head)
{
    if (!head)
    {
        cout << "The list is empty\n";
        return;
    }
    SLL_Node<T> *trav = head;
    while (trav)
    {
        cout << trav->data << " ";
        trav = trav->next;
    }
    cout << endl;
}

//TODO
template <typename T>
void sort_singly_linked_list(SLL_Node<T> *head)
{
}

#endif