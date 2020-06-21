// https://github.com/adnanaziz/epicode/blob/master/cpp/valid-parentheses.cc

#include <cassert>
#include <iostream>
#include <stack>
#include <string>

using std::boolalpha;
using std::cout;
using std::endl;
using std::stack;
using std::string;

bool IsWellFormed(const string &s)
{
    stack<char> left_chars;
    for (int i = 0; i < s.size(); ++i)
    {
        if (s[i] == '(' || s[i] == '{' || s[i] == '[')
        {
            left_chars.emplace(s[i]);
        }
        else
        {
            if (left_chars.empty())
            {
                return false; // Unmatched right char.
            }
            if ((s[i] == ')' && left_chars.top() != '(') ||
                (s[i] == '}' && left_chars.top() != '{') ||
                (s[i] == ']' && left_chars.top() != '['))
            {
                return false; // Mismatched chars.
            }
            left_chars.pop();
        }
    }
    return left_chars.empty();
}

void small_test()
{
    assert(IsWellFormed("()"));
    assert(IsWellFormed("()[]{}"));
    assert(IsWellFormed("[()[]]{}"));
    assert(IsWellFormed("(()[]{()[]{}{}})"));
    assert(!IsWellFormed("([)]"));
    assert(!IsWellFormed("["));
    assert(!IsWellFormed("(()[]{()[]{})({}})"));
}

bool IsWellFormedWithOtherChars(const string &s)
{
    stack<char> left_chars;
    for (int i = 0; i < s.size(); ++i)
    {
        if (s[i] == '(' || s[i] == '{' || s[i] == '[')
        {
            left_chars.emplace(s[i]);
        }
        else if (s[i] == ')' || s[i] == '}' || s[i] == ']')
        {
            if (left_chars.empty())
            {
                return false; // Unmatched right char.
            }
            if ((s[i] == ')' && left_chars.top() != '(') ||
                (s[i] == '}' && left_chars.top() != '{') ||
                (s[i] == ']' && left_chars.top() != '['))
            {
                return false; // Mismatched chars.
            }
            left_chars.pop();
        }
        //some other chars detected, leave them unattended
    }
    return left_chars.empty();
}

void exp_test()
{
    assert(IsWellFormedWithOtherChars("(abcd)"));
    assert(IsWellFormedWithOtherChars("(abcd)[123]{xyz}"));
    assert(IsWellFormedWithOtherChars("[(xyz)abc[1230]]{}"));
    assert(IsWellFormedWithOtherChars("(()[abc]{()[xyz]{}{}})"));
    assert(!IsWellFormedWithOtherChars("([)]"));
    assert(!IsWellFormedWithOtherChars("asdasd["));
    assert(!IsWellFormedWithOtherChars("(()[]{()[]{})({}})"));
}

int main(int argc, char **argv)
{
    small_test();
    exp_test();
    return 0;
}