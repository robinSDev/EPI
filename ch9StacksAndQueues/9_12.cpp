#include <bits/stdc++.h>
using namespace std;

class Queue_MaxAPI_BF
{
public:
    void Enqueue(int x) { data_.emplace_back(x); }

    int Dequeue()
    {
        if (data_.empty())
        {
            throw length_error("empty queue");
        }
        const int val = data_.front();
        data_.pop_front();
        return val;
    }

    int Max() const
    {
        if (data_.empty())
        {
            throw length_error("Cannot perform Max() on empty queue.");
        }
        return *max_element(data_.begin(), data_.end());
    }

private:
    list<int> data_;
};


template <typename T>
class QueueWithMax_Deque
{
public:
    void Enqueue(const T &x)
    {
        entries_.emplace(x);
        // Eliminate dominated elements in candidates_for_max_.
        while (!candidates_for_max_.empty())
        {
            if (candidates_for_max_.back() >= x)
            {
                break;
            }
            candidates_for_max_.pop_back();
        }
        candidates_for_max_.emplace_back(x);
    }

    T Dequeue()
    {
        if (!entries_.empty())
        {
            T result = entries_.front();
            if (result == candidates_for_max_.front())
            {
                candidates_for_max_.pop_front();
            }
            entries_.pop();
            return result;
        }
        throw length_error("empty queue");
    }

    const T &Max() const
    {
        if (!candidates_for_max_.empty())
        {
            return candidates_for_max_.front();
        }
        throw length_error("empty queue");
    }
    // @exclude
    T &Head() { return entries_.front(); }

    const T &Head() const { return entries_.front(); }
    // @include

private:
    queue<T> entries_;
    deque<T> candidates_for_max_;
};


class Stack
{
public:
    void Push(int data)
    {
        element_.emplace(data); //update element_ stack
        //update stack_of_max_with_count_ stack
        if (stack_of_max_with_count_.empty())
        {
            stack_of_max_with_count_.emplace(make_pair(data, 1));
            return;
        }
        pair<int, int> &curr_max_with_count = stack_of_max_with_count_.top();
        if (data == curr_max_with_count.first) //increase frequency count of curr max
        {
            int &count = curr_max_with_count.second;
            ++count;
        }
        else if (data > curr_max_with_count.first) //add a new max
        {
            stack_of_max_with_count_.emplace(make_pair(data, 1));
        }
    }

    int Top()
    {
        if (element_.empty())
            throw std::length_error("The stack is empty. Top()");
        return element_.top();
    }

    int Pop()
    {
        if (element_.empty())
            throw std::length_error("The stack is empty. Pop(");
        int popped_val = element_.top(); //store current top value
        element_.pop();                  //update element_ stack

        //update stack_of_max_with_count_ stack
        pair<int, int> &curr_max_with_count = stack_of_max_with_count_.top();
        if (popped_val == curr_max_with_count.first)
        {
            int &count = curr_max_with_count.second;
            --count;

            if (count == 0)
                stack_of_max_with_count_.pop();
        }

        return popped_val;
    }

    int Max()
    {
        if (stack_of_max_with_count_.empty())
            throw std::length_error("The stack is empty. Max()");
        return stack_of_max_with_count_.top().first;
    }

    bool Empty()
    {
        return element_.empty();
    }

private:
    stack<int> element_;
    stack<pair<int, int>> stack_of_max_with_count_;
};



class QueueWithMax_TwoStacksWithMax
{
public:
    void Enqueue(int x) { enqueue_.Push(x); }

    int Dequeue()
    {
        if (dequeue_.Empty())
        {
            while (!enqueue_.Empty())
            {
                dequeue_.Push(enqueue_.Pop());
            }
        }
        if (!dequeue_.Empty())
        {
            return dequeue_.Pop();
        }
        throw length_error("empty queue");
    }

    int Max()
    {
        if (!enqueue_.Empty())
        {
            return dequeue_.Empty() ? enqueue_.Max()
                                    : max(enqueue_.Max(), dequeue_.Max());
        }
        if (!dequeue_.Empty())
        {
            return dequeue_.Max();
        }
        throw length_error("empty queue");
    }

private:
    Stack enqueue_, dequeue_;
};

template <typename T>
int test(T Q)
{
    Q.Enqueue(11);
    Q.Enqueue(2);
    assert(11 == Q.Max());
    assert(11 == Q.Dequeue());
    assert(2 == Q.Max());
    assert(2 == Q.Dequeue());
    Q.Enqueue(3);
    assert(3 == Q.Max());
    assert(3 == Q.Dequeue());
    Q.Enqueue(numeric_limits<int>::max() - 1);
    Q.Enqueue(numeric_limits<int>::max());
    Q.Enqueue(-2);
    Q.Enqueue(-1);
    Q.Enqueue(-1);
    Q.Enqueue(numeric_limits<int>::min());
    assert(numeric_limits<int>::max() == Q.Max());
    assert(numeric_limits<int>::max() - 1 == Q.Dequeue());
    assert(numeric_limits<int>::max() == Q.Max());
    assert(numeric_limits<int>::max() == Q.Dequeue());
    assert(-1 == Q.Max());
    assert(-2 == Q.Dequeue());
    assert(-1 == Q.Max());
    assert(-1 == Q.Dequeue());
    assert(-1 == Q.Dequeue());
    assert(numeric_limits<int>::min() == Q.Max());
    assert(numeric_limits<int>::min() == Q.Dequeue());
    try
    {
        cout << "Q is empty, Max() call should except = " << Q.Max();
        assert(false);
    }
    catch (const exception &e)
    {
        cout << e.what() << endl;
    }
    Q.Enqueue(1);
    Q.Enqueue(2);
    assert(2 == Q.Max());
    assert(1 == Q.Dequeue());
    assert(2 == Q.Max());
    assert(2 == Q.Dequeue());
    Q.Enqueue(3);
    assert(3 == Q.Max());
    assert(3 == Q.Dequeue());
    try
    {
        Q.Max();
    }
    catch (const exception &e)
    {
        cout << e.what() << endl;
    }
    try
    {
        Q.Dequeue();
    }
    catch (const exception &e)
    {
        cout << e.what() << endl;
    }
    return 0;
}

int main(int argc, char const *argv[])
{
    Queue_MaxAPI_BF Q1;
    QueueWithMax_Deque<int> Q2;
    QueueWithMax_TwoStacksWithMax Q3;
    assert((test(Q1) or test(Q2) or test(Q3)) == 0);
    return 0;
}