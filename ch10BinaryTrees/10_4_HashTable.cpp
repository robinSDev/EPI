//https://github.com/adnanaziz/epicode/blob/master/cpp/Lowest_common_ancestor_hash.cc
#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct BinaryTreeNode
{
    T data;
    unique_ptr<BinaryTreeNode<T>> left, right;
    BinaryTreeNode<T> *parent;
};

BinaryTreeNode<int> *LCA(const unique_ptr<BinaryTreeNode<int>> &node_0,
                         const unique_ptr<BinaryTreeNode<int>> &node_1)
{
    auto *iter_0 = node_0.get(), *iter_1 = node_1.get();
    unordered_set<const BinaryTreeNode<int> *> nodes_on_path_to_root;
    while (iter_0 || iter_1)
    {
        // Ascend tree in tandem for these two nodes.
        if (iter_0)
        {
            if (nodes_on_path_to_root.emplace(iter_0).second == false)
            {
                return iter_0;
            }
            iter_0 = iter_0->parent;
        }
        if (iter_1)
        {
            if (nodes_on_path_to_root.emplace(iter_1).second == false)
            {
                return iter_1;
            }
            iter_1 = iter_1->parent;
        }
    }
    throw invalid_argument("node_0 and node_1 are not in the same tree");
}
// @exclude

int main(int argc, char *argv[])
{
    //      3
    //    2   5
    //  1    4 6
    unique_ptr<BinaryTreeNode<int>> root = make_unique<BinaryTreeNode<int>>(
        BinaryTreeNode<int>{3, nullptr, nullptr});
    root->parent = nullptr;
    root->left = make_unique<BinaryTreeNode<int>>(
        BinaryTreeNode<int>{2, nullptr, nullptr});
    root->left->parent = root.get();
    root->left->left = make_unique<BinaryTreeNode<int>>(
        BinaryTreeNode<int>{1, nullptr, nullptr});
    root->left->left->parent = root->left.get();
    root->right = make_unique<BinaryTreeNode<int>>(
        BinaryTreeNode<int>{5, nullptr, nullptr});
    root->right->parent = root.get();
    root->right->left = make_unique<BinaryTreeNode<int>>(
        BinaryTreeNode<int>{4, nullptr, nullptr});
    root->right->left->parent = root->right.get();
    root->right->right = make_unique<BinaryTreeNode<int>>(
        BinaryTreeNode<int>{6, nullptr, nullptr});
    root->right->right->parent = root->right.get();

    // should output 3
    assert(LCA(root->left, root->right)->data == 3);
    cout << (LCA(root->left, root->right))->data << endl;
    // should output 5
    assert(LCA(root->right->left, root->right->right)->data == 5);
    cout << (LCA(root->right->left, root->right->right)->data) << endl;
    return 0;
}