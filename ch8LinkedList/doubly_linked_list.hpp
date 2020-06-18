#ifndef DOUBLY_LINKED_LIST_HPP
#define DOUBLY_LINKED_LIST_HPP
#pragma once
#include <vector>
#include <iostream>
using std::cout;
using std::endl;
using std::vector;

template <typename T>
struct DLL_Node
{
    T data;
    DLL_Node<T> *prev, *next;

    DLL_Node<T>(const T &data)
    {
        this->data = data;
        prev = next = nullptr;
    }
    DLL_Node<T>() { prev = next = nullptr; }
};

template <typename T>
class DoublyLinkedList
{
public:
    DLL_Node<T> *head = nullptr, *tail = nullptr;

    void push_back(const T &data)
    {
        DLL_Node<T> *newNode = new DLL_Node<T>(data);
        if (!head)
        {
            head = tail = newNode;
            return;
        }
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }

    DoublyLinkedList(const vector<T> &stream)
    {
        DLL_Node<T> *head = nullptr;
        for (const int &i : stream)
        {
            push_back(i);
        }
    }
};

template <typename T>
void print_doubly_linked_list(DLL_Node<T> *head)
{
    if (!head)
    {
        cout << "The list is empty\n";
        return;
    }
    DLL_Node<T> *trav = head;
    while (trav)
    {
        cout << trav->data << " <-> ";
        trav = trav->next;
    }
    cout << endl;
}
#endif