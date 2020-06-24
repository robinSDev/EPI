//https://github.com/adnanaziz/epicode/blob/master/cpp/sum-root-to-leaf-binary-tree.cc

#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct BinaryTreeNode
{
    T data;
    unique_ptr<BinaryTreeNode<T>> left, right;
};

int SumRootToLeafHelper(const unique_ptr<BinaryTreeNode<int>>&, int);

int SumRootToLeaf(const unique_ptr<BinaryTreeNode<int>> &tree)
{
    return SumRootToLeafHelper(tree, 0);
}

int SumRootToLeafHelper(const unique_ptr<BinaryTreeNode<int>> &tree,
                        int partial_path_sum)
{
    if (tree == nullptr)
    {
        return 0;
    }

    partial_path_sum = partial_path_sum * 2 + tree->data;
    if (tree->left == nullptr && tree->right == nullptr)
    { // Leaf.
        return partial_path_sum;
    }
    // Non-leaf.
    return SumRootToLeafHelper(tree->left, partial_path_sum) +
           SumRootToLeafHelper(tree->right, partial_path_sum);
}

int main(int argc, char **argv)
{
    //      1
    //    1   0
    //  0    1 0
    unique_ptr<BinaryTreeNode<int>> root = make_unique<BinaryTreeNode<int>>(
        BinaryTreeNode<int>{1, nullptr, nullptr});
    assert(SumRootToLeaf(root) == 1);
    root->left = make_unique<BinaryTreeNode<int>>(
        BinaryTreeNode<int>{1, nullptr, nullptr});
    assert(SumRootToLeaf(root) == 3);
    root->left->left = make_unique<BinaryTreeNode<int>>(
        BinaryTreeNode<int>{0, nullptr, nullptr});
    assert(SumRootToLeaf(root) == 6);
    root->right = make_unique<BinaryTreeNode<int>>(
        BinaryTreeNode<int>{0, nullptr, nullptr});
    assert(SumRootToLeaf(root) == 8);
    root->right->left = make_unique<BinaryTreeNode<int>>(
        BinaryTreeNode<int>{1, nullptr, nullptr});
    assert(SumRootToLeaf(root) == 11);
    root->right->right = make_unique<BinaryTreeNode<int>>(
        BinaryTreeNode<int>{0, nullptr, nullptr});
    assert(SumRootToLeaf(root) == 15);
    return 0;
}