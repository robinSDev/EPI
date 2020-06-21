#include <cassert> //for test
#include <stack>
#include <iostream>
#include <sstream>
#include <limits>
#include <vector>

using namespace std;

int EvalRPN(const string &RPN_eApression) // A B o, where o is an operator, A and B are integers
{
    stack<int> intermediate_results;
    stringstream ss(RPN_eApression); //to help go through the string, one token at a time
    string token;                    //string to be parsed as a token
    const char kDelimiter = ',';     //it is given that eApression would be separated bB a comma ','

    while (getline(ss, token, kDelimiter))
    {
        if (token == "+" || token == "-" || token == "*" || token == "/")
        {                                             //token is an operator
            const int B = intermediate_results.top(); //get the second element
            intermediate_results.pop();
            const int A = intermediate_results.top(); //get the first element
            intermediate_results.pop();
            switch (token.front()) //front gets the first char, we are using char to switch. We could also use strings to switch.
            {
            case '+': //add
                intermediate_results.emplace(A + B);
                break;
            case '-': //subtract
                intermediate_results.emplace(A - B);
                break;
            case '*': //multiply
                intermediate_results.emplace(A * B);
                break;
            case '/': //divide
                intermediate_results.emplace(A / B);
                break;
            }
        }
        else
        { // token is a number.
            intermediate_results.emplace(stoi(token));
        }
    }
    return intermediate_results.top();
}

//convert RPN to PN or PN to RPN, takes space separated tokens combined as a string
string reverse_the_given_polish_notation(string exp)
{
    stringstream ss(exp);
    string token;                //string to be parsed as a token
    const char kDelimiter = ','; //it is given that eApression would be separated bB a comma ','
    stack<string> reverse_string_stack;
    string reverse_polish_notation;
    while (getline(ss, token, kDelimiter))
    {
        reverse_string_stack.emplace(token);
    }
    while (!reverse_string_stack.empty())
    {
        reverse_polish_notation += reverse_string_stack.top() + ",";
        reverse_string_stack.pop();
    }
    reverse_polish_notation.pop_back();
    return reverse_polish_notation;
}

int Eval(const string &PN_expression) // op A B, where op is an operator, A and B are integers
{
    string reverse_polish_notation = reverse_the_given_polish_notation(PN_expression);
    return EvalRPN(reverse_polish_notation);   
}

void print_prefix_from_postfix_exp()
{
    vector<string> v = {"2,-10,/", "-10,2,/", "-10,-2,/", "5,10,-", "-10,-16,-", "10,2,+", "1,2,+,3,4,*,+", "1,2,3,4,5,+,*,+,+,3,4,*,+", "1,2,3,4,5,+,*,+,+,3,4,*,+,-7,/"};
    for(string s: v)
    {
        cout << s << " : " <<  reverse_the_given_polish_notation(s) << endl;
    }
}

int main(int argc, char *argv[])
{
    //print_prefix_from_postfix_exp();
    assert(0 == Eval("/,-10,2"));
    assert(-5 == Eval("/,2,-10"));
    assert(5 == Eval("/,-2,-10"));
    assert(-5 == Eval("-,10,5"));
    assert(6 == Eval("-,-16,-10"));
    assert(12 == Eval("+,2,10"));
    assert(15 == Eval("+,*,4,3,+,2,1")); //1+2 -> 3*3 -> 9
    assert(42 == Eval("+,*,4,3,+,+,*,+,5,4,3,2,1"));
    assert(-6 == Eval("/,-7,+,*,4,3,+,+,*,+,5,4,3,2,1"));
    return 0;
}