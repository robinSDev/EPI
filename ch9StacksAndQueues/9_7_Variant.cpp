//Solving the same problem as 9.7, but the input order is now west to east
//This one is comparitively easy, no stack or queue would be used.

#include <bits/stdc++.h>

using namespace std;

vector<int> ExamineBuildingsWithSunset(istringstream *sin)
{
    int building_idx = 0, building_height, prev_max_building_height = INT_MIN;
    vector<int> buildings_with_sunset;
    while (*sin >> building_height)
    {
        if(building_height > prev_max_building_height)
        {
            buildings_with_sunset.emplace_back(building_idx);
            prev_max_building_height = building_height;
        }//else: this building can still view the sunset on windows facing west
        ++building_idx;
    }

    return buildings_with_sunset;
}

int main(int argc, char *argv[])
{
    default_random_engine gen((random_device())());
    for (int times = 0; times < 5; ++times)
    {
        int n;
        if (argc == 2)
        {
            n = atoi(argv[1]);
        }
        else
        {
            uniform_int_distribution<int> dis(1, 100);
            n = dis(gen);
        }
        stringstream ss;
        vector<int> heights;
        for (int i = 0; i < n; ++i)
        {
            uniform_int_distribution<int> dis(1, 2 * n);
            int height = dis(gen);
            ss << height << ' ';
            cout << height << ' ';
            heights.emplace_back(height);
        }
        cout << endl;
        istringstream sin(ss.str());
        auto res = ExamineBuildingsWithSunset(&sin);
        cout << res[0] << ' ' << heights[res[0]] << endl;
        for (int i = 1; i < res.size(); ++i)
        {
            cout << res[i] << ' ' << heights[res[i]] << endl;
            assert(heights[res[i - 1]] < heights[res[i]]);
        }
        cout << "-------------------------------------\n\n";
    }
    return 0;
}