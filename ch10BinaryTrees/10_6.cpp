//https://github.com/adnanaziz/epicode/blob/master/cpp/path-sum-binary-tree.cc

#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct BinaryTreeNode
{
    T data;
    unique_ptr<BinaryTreeNode<T>> left, right;
};

bool HasPathSumHelper(const unique_ptr<BinaryTreeNode<int>>&, int, int);

bool HasPathSum(const unique_ptr<BinaryTreeNode<int>>& tree, int target_sum) {
  return HasPathSumHelper(tree, 0, target_sum);
}

bool HasPathSumHelper(const unique_ptr<BinaryTreeNode<int>>& node,
                      int partial_path_sum, int target_sum) {
  if (node == nullptr) {
    return false;
  }
  partial_path_sum += node->data;
  if (node->left == nullptr && node->right == nullptr) {  // Leaf.
    return partial_path_sum == target_sum;
  }
  // Non-leaf.
  return HasPathSumHelper(node->left, partial_path_sum, target_sum) ||
         HasPathSumHelper(node->right, partial_path_sum, target_sum);
}

int main(int argc, char** argv) {
  //      3
  //    2   5
  //  1    4 6
  unique_ptr<BinaryTreeNode<int>> tree = make_unique<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{3, nullptr, nullptr});
  assert(HasPathSum(tree, 3));
  tree->left = make_unique<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{2, nullptr, nullptr});
  assert(HasPathSum(tree, 5));
  tree->left->left = make_unique<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{1, nullptr, nullptr});
  assert(HasPathSum(tree, 6));
  tree->right = make_unique<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{5, nullptr, nullptr});
  assert(HasPathSum(tree, 8));
  assert(!HasPathSum(tree, 7));
  tree->right->left = make_unique<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{4, nullptr, nullptr});
  assert(HasPathSum(tree, 12));
  assert(!HasPathSum(tree, 1));
  assert(!HasPathSum(tree, 3));
  assert(!HasPathSum(tree, 5));
  tree->right->right = make_unique<BinaryTreeNode<int>>(
      BinaryTreeNode<int>{6, nullptr, nullptr});
  assert(HasPathSum(tree, 6));
  assert(!HasPathSum(tree, 7));
  assert(HasPathSum(tree, 14));
  assert(!HasPathSum(tree, -1));
  assert(!HasPathSum(tree, numeric_limits<int>::max()));
  assert(!HasPathSum(tree, numeric_limits<int>::min()));
  return 0;
}