/*
BST Level order
Given a BST, print it in level order.

Solution
    Use a queue and insert left followed by right child into the queue
    Pop an element print it
    Insert a special node indicating end of level

Code
def level_order(root)
    return nil if root.nil?

    q = []
    q.push(root)

    while !q.empty?
        node = e.pop
        if node.data = -1 # End of level
            puts ''
            next
        end

        puts e.data
        q.insert(node.left)
        q.insert(node.right)
    end
end
Complexity: O(n) for visiting each node once
*/

#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct BinaryTreeNode
{
    T data;
    unique_ptr<BinaryTreeNode<T>> left, right;
};

vector<vector<int>> BinaryTreeDepthOrder(
    const unique_ptr<BinaryTreeNode<int>> &tree)
{
    queue<BinaryTreeNode<int> *> curr_depth_nodes({tree.get()});
    vector<vector<int>> result;

    while (!curr_depth_nodes.empty())
    {
        queue<BinaryTreeNode<int> *> next_depth_nodes;
        vector<int> this_level;
        while (!curr_depth_nodes.empty())
        {
            auto curr = curr_depth_nodes.front();
            curr_depth_nodes.pop();
            if (curr)
            {
                this_level.emplace_back(curr->data);

                // Defer the null checks to the null test above.
                next_depth_nodes.emplace(curr->left.get());
                next_depth_nodes.emplace(curr->right.get());
            }
        }

        if (!this_level.empty())
        {
            result.emplace_back(this_level);
        }
        curr_depth_nodes = next_depth_nodes;
    }
    return result;
}

//Variant 1
vector<vector<int>> BinaryTreeDepthOrderVar1(
    const unique_ptr<BinaryTreeNode<int>> &tree)
{
    queue<BinaryTreeNode<int> *> curr_depth_nodes({tree.get()});
    vector<vector<int>> result;
    bool store_left_to_right = true;
    while (!curr_depth_nodes.empty())
    {
        queue<BinaryTreeNode<int> *> next_depth_nodes;
        deque<int> this_level;
        while (!curr_depth_nodes.empty())
        {
            auto curr = curr_depth_nodes.front();
            curr_depth_nodes.pop();
            if (curr)
            {
                if (store_left_to_right)
                    this_level.emplace_back(curr->data);
                else
                    this_level.emplace_front(curr->data);

                // Defer the null checks to the null test above.
                next_depth_nodes.emplace(curr->left.get());
                next_depth_nodes.emplace(curr->right.get());
            }
        }

        if (!this_level.empty())
        {
            vector<int> temp(this_level.begin(), this_level.end());
            result.emplace_back(temp);
            store_left_to_right = !store_left_to_right;
        }
        curr_depth_nodes = next_depth_nodes;
    }
    return result;
}

//Variant 2
vector<vector<int>> BinaryTreeDepthOrderVar2(
    const unique_ptr<BinaryTreeNode<int>> &tree)
{
    queue<BinaryTreeNode<int> *> curr_depth_nodes({tree.get()});
    deque<vector<int>> result;

    while (!curr_depth_nodes.empty())
    {
        queue<BinaryTreeNode<int> *> next_depth_nodes;
        vector<int> this_level;
        while (!curr_depth_nodes.empty())
        {
            auto curr = curr_depth_nodes.front();
            curr_depth_nodes.pop();
            if (curr)
            {
                this_level.emplace_back(curr->data);

                // Defer the null checks to the null test above.
                next_depth_nodes.emplace(curr->left.get());
                next_depth_nodes.emplace(curr->right.get());
            }
        }

        if (!this_level.empty())
        {
            result.emplace_front(this_level);
        }
        curr_depth_nodes = next_depth_nodes;
    }
    return vector<vector<int>>(result.begin(), result.end());
}

vector<double> BinaryTreeDepthOrderVar3(
    const unique_ptr<BinaryTreeNode<int>> &tree)
{
    queue<BinaryTreeNode<int> *> curr_depth_nodes({tree.get()});
    vector<double> result;

    while (!curr_depth_nodes.empty())
    {
        queue<BinaryTreeNode<int> *> next_depth_nodes;
        double sum = 0.0;
        int count = 0;
        while (!curr_depth_nodes.empty())
        {
            auto curr = curr_depth_nodes.front();
            curr_depth_nodes.pop();
            if (curr)
            {
                sum += (curr->data);
                ++count;
                // Defer the null checks to the null test above.
                next_depth_nodes.emplace(curr->left.get());
                next_depth_nodes.emplace(curr->right.get());
            }
        }

        if (sum)
        {
            result.emplace_back(sum/count);
        }
        curr_depth_nodes = next_depth_nodes;
    }
    return result;
}

int main(int argc, char *argv[])
{
    //      3
    //    2   5
    //  1    4 6
    // 10
    // 13
    unique_ptr<BinaryTreeNode<int>> tree = make_unique<BinaryTreeNode<int>>(
        BinaryTreeNode<int>{3, nullptr, nullptr});
    tree->left = make_unique<BinaryTreeNode<int>>(
        BinaryTreeNode<int>{2, nullptr, nullptr});
    tree->left->left = make_unique<BinaryTreeNode<int>>(
        BinaryTreeNode<int>{1, nullptr, nullptr});
    tree->left->left->left = make_unique<BinaryTreeNode<int>>(
        BinaryTreeNode<int>{10, nullptr, nullptr});
    tree->left->left->right = make_unique<BinaryTreeNode<int>>(
        BinaryTreeNode<int>{11, nullptr, nullptr});
    tree->left->left->left->right = make_unique<BinaryTreeNode<int>>(
        BinaryTreeNode<int>{13, nullptr, nullptr});
    tree->right = make_unique<BinaryTreeNode<int>>(
        BinaryTreeNode<int>{5, nullptr, nullptr});
    tree->right->left = make_unique<BinaryTreeNode<int>>(
        BinaryTreeNode<int>{4, nullptr, nullptr});
    tree->right->right = make_unique<BinaryTreeNode<int>>(
        BinaryTreeNode<int>{6, nullptr, nullptr});
    // should output 3
    //               2 5
    //               1 4 6
    //               10
    //               13
    auto result = BinaryTreeDepthOrder(tree);
    vector<vector<int>> ideal_res = {{3}, {2, 5}, {1, 4, 6}, {10, 11}, {13}};
    assert(equal(ideal_res.begin(), ideal_res.end(), result.begin(),
                 result.end()));

    result = BinaryTreeDepthOrderVar1(tree);
    /*for (auto i : result)
    {
        for (auto j : i)
            cout << j << " ";
        cout << endl;
    }*/
    ideal_res = {{3}, {5, 2}, {1, 4, 6}, {11, 10}, {13}};
    assert(equal(ideal_res.begin(), ideal_res.end(), result.begin(),
                 result.end()));

    result = BinaryTreeDepthOrderVar2(tree);
    /*for (auto i : result)
    {
        for (auto j : i)
            cout << j << " ";
        cout << endl;
    }*/
    ideal_res = {{13}, {10, 11}, {1, 4, 6}, {2, 5}, {3}};
    assert(equal(ideal_res.begin(), ideal_res.end(), result.begin(),
                 result.end()));

    vector<double> var3res = BinaryTreeDepthOrderVar3(tree);
    
    /*for (auto i : var3res)
    {
       cout << setprecision(100) << i << "\n";
    }*/
    vector<double> res = {{3.0}, {3.5}, {3.666666666666666518636930049979127943515777587890625}, {10.5}, {13.0}};
    
    assert(equal(var3res.begin(), var3res.end(), res.begin(),
                 res.end()));

    return 0;
}