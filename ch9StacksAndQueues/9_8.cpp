/*Sort a stack
Given a stack that has elements in random order, sort it recursively without explicitly using another stack.
Solution
Sort
    Pop the top element
    recursively sort the stack, until its empty
    then insert popped element
Insert
    If stack is empty or top element is less than element to be inserted, then push element
    Else, pop the top of stack into f, and recursively insert e, and then push f onto the stack

Code
def sort_stack(s)
    if !s.empty?
        e = s.pop
        sort_stack(s)
        insert(e,s)
    end
end

def insert(s, e)
    if s.empty || s.top <= e
        s.push(e)
    else
        f = s.pop
        insert(s, e)
        s.push(f)
    end
end

Complexity
    Essentially we are creating another stack using recursion and re-inserting each element in its right place using a simple insertion sort like technique. Therefore time complexity O(n^2).
*/
#include <bits/stdc++.h>

using namespace std;

void Insert(int, stack<int> *);

//Sorting such that max element is at top
void Sort(stack<int> *S)
{
    if (!S->empty())
    {
        int val = S->top();
        S->pop();
        Sort(S);
        Insert(val, S);
    }
}

void Insert(int val, stack<int> *S)
{
    if (S->empty() || S->top() <= val)
    {
        S->push(val);
    }
    else
    {
        int f = S->top();
        S->pop();
        Insert(val, S);
        S->push(f);
    }
}

void SimpleTest()
{
    stack<int> S;
    S.push(1);
    Sort(&S);
    assert(S.top() == 1);
    S.push(0);
    Sort(&S);
    assert(S.top() == 1);
    S.pop();
    assert(S.top() == 0);
    S.pop();
    assert(S.empty());
    S.push(-1);
    S.push(1);
    S.push(0);
    Sort(&S);
    assert(S.top() == 1);
    S.pop();
    assert(S.top() == 0);
    S.pop();
    assert(S.top() == -1);
    S.pop();
    assert(S.empty());
}

int main(int argc, char *argv[])
{
    SimpleTest();
    default_random_engine gen((random_device())());
    for (int times = 0; times < 3; ++times)
    {
        int n;
        if (argc == 2)
        {
            n = atoi(argv[1]);
        }
        else
        {
            uniform_int_distribution<int> dis(1, 10000);
            n = dis(gen);
        }
        stack<int> S;
        uniform_int_distribution<int> dis(0, 999999);
        for (int i = 0; i < n; ++i)
        {
            S.push(dis(gen));
        }
        Sort(&S);
        int pre = numeric_limits<int>::max();
        while (!S.empty())
        {
            assert(pre >= S.top());
            cout << S.top() << endl;
            pre = S.top();
            S.pop();
        }
    }
    return 0;
}