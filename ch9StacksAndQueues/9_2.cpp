#include <cassert> //for test
#include <stack>
#include <iostream>
#include <sstream>
using namespace std;

int Eval(const string &RPN_expression) // A B o, where o is an operator, A and B are integers
{
    stack<int> intermediate_results;
    stringstream ss(RPN_expression); //to help go through the string, one token at a time
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

int main(int argc, char *argv[])
{
    assert(0 == Eval("2,-10,/"));
    assert(-5 == Eval("-10,2,/"));
    assert(5 == Eval("-10,-2,/"));
    assert(-5 == Eval("5,10,-"));
    assert(6 == Eval("-10,-16,-"));
    assert(12 == Eval("10,2,+"));
    assert(15 == Eval("1,2,+,3,4,*,+"));
    assert(42 == Eval("1,2,3,4,5,+,*,+,+,3,4,*,+"));
    assert(-6 == Eval("1,2,3,4,5,+,*,+,+,3,4,*,+,-7,/"));
    return 0;
}