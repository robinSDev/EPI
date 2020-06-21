#include <cassert>   //for test
#include <stdexcept> //for length_error
#include <stack>
#include <iostream>
#include <vector> //for test data
using namespace std;

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

private:
    stack<int> element_;
    stack<pair<int, int>> stack_of_max_with_count_;
};

int test1(vector<int> &v)
{
    Stack s;
    for (const int &i : v)
    {
        s.Push(i);
        //cout << "pushed: " << i << ",   s.Top(): " << s.Top() << ",   s.Max():  " << s.Max() << endl;
        assert((s.Top() == s.Max()) and (s.Top() == i) and (i == s.Max()));
    }
    return 0;
}

int test2(vector<int> &v)
{
    Stack s;
    for (const int &i : v)
    {
        s.Push(i);
        assert((s.Top() == i) and (s.Max() == 10));
    }
    return 0;
}

int test3(vector<int> &v)
{
    Stack s;
    for (const int &i : v)
    {
        s.Push(i);
    }
    int x = 11;
    for(unsigned i=0; i<v.size(); ++i)
    {
        //cout << "x: " << x << ",   s.Top(): " << s.Top() << ",   s.Max():  " << s.Max() << endl;
        assert((s.Top() == s.Max()) and (s.Top() == x) and (x == s.Max()));
        s.Pop();
        --x;
    }
    return 0;
}

int main(int argc, char const *argv[])
{
    vector<int> a = {1, 2, 3, 6, 7, 8, 9, 10, 11}, b = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, c = {1,2,3,4,5,6,7,8,9,10,11};
    assert((test1(a) or test2(b) or test3(c)) == 0);
    return 0;
}
