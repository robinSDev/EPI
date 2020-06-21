#include <algorithm>
#include <cassert>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

string ShortestEquivalentPath(const string &path)
{
    if (path.empty())
    {
        throw invalid_argument("Empty string is not a valid path.");
    }

    vector<string> path_names; // Uses vector as a stack.
    // Special case: starts with "/", which is an absolute path.
    if (path.front() == '/')
    {
        path_names.emplace_back("/");
    }

    stringstream ss(path);
    string token;
    while (getline(ss, token, '/'))
    {
        if (token == "..")
        {
            if (path_names.empty() || path_names.back() == "..")
            {
                path_names.emplace_back(token);
            }
            else
            {
                if (path_names.back() == "/") //this is an absolute path string, this path is invalid
                {
                    throw invalid_argument("Path error");
                }
                path_names.pop_back(); //go to parent directory
            }
        }
        else if (token != "." && token != "") //not cwd and not an empty string
        {                                     // Must be a name.
            path_names.emplace_back(token);
        }
    }

    string result;
    if (!path_names.empty())
    {
        result = path_names.front();                //get 0th index
        for (int i = 1; i < path_names.size(); ++i) //this is why vector was used as stack
        {
            if (i == 1 && result == "/")
            { // Avoid starting "//".
                result += path_names[i];
            }
            else
            {
                result += "/" + path_names[i];
            }
        }
    }
    return result;
}

int main(int argc, char *argv[])
{
    assert(ShortestEquivalentPath("123/456") == string("123/456"));
    assert(ShortestEquivalentPath("/123/456") == string("/123/456"));
    assert(ShortestEquivalentPath("usr/lib/../bin/gcc") ==
           string("usr/bin/gcc"));
    assert(ShortestEquivalentPath("./../") == string(".."));
    assert(ShortestEquivalentPath("../../local") == string("../../local"));
    assert(ShortestEquivalentPath("./.././../local") == string("../../local"));
    assert(ShortestEquivalentPath("/foo/../foo/./../") == string("/"));
    try
    {
        ShortestEquivalentPath("/foo.txt");
    }
    catch (const exception &e)
    {
        cout << e.what() << endl;
    }
    try
    {
        ShortestEquivalentPath("");
        assert(false);
    }
    catch (const exception &e)
    {
        cout << e.what() << endl; //Empty string is not a valid path.
    }
    try
    {
        ShortestEquivalentPath("/..");
    }
    catch (const exception &e)
    {
        cout << e.what() << endl; //Path error, //this is an absolute path string, this path is invalid
    }
    try
    {
        ShortestEquivalentPath("/cpp_name/bin/");
    }
    catch (const exception &e)
    {
        cout << e.what() << endl;
    }
    assert(ShortestEquivalentPath("scripts//./../scripts/awkscripts/././") ==
           string("scripts/awkscripts"));
    return 0;
}