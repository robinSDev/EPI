#include <bits/stdc++.h>
using namespace std;

vector<char> topKFrequent(vector<char> &nums, int k)
{
    unordered_map<int, char> map;
    for (int num : nums)
    {
        map[num]++;
    }

    vector<char> res;
    // pair<first, second>: first is frequency,  second is number
    priority_queue<pair<int, char>> pq;
    for (auto it = map.begin(); it != map.end(); it++)
    {
        pq.push(make_pair(it->second, it->first));
        if (pq.size() > (int)map.size() - k)
        {
            res.push_back(pq.top().second);
            pq.pop();
        }
    }
    return res;
}
int main(int argc, char const *argv[])
{
    vector<char> pages = {'a', 'b', 'c', 'd', 'e', 'a', 'b', 'c', 'd', 'a', 'b', 'a', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

    vector<char> res = topKFrequent(pages, 4);
    for (char c : res)
        cout << c << " ";

    return 0;
}
