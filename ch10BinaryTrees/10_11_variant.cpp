#include <bits/stdc++.h>
using namespace std;

struct BinaryTreeNode
{
    int data;
    BinaryTreeNode *left, *right;
};

// Reconstructs the subtree that is rooted at subtreeIdx.
BinaryTreeNode * ReconstructPostorderHelper(
    const vector<int *> &postorder, int *subtree_idx_pointer)
{
    int &subtree_idx = *subtree_idx_pointer;
    int *subtree_key = postorder[subtree_idx];
    --subtree_idx; //this differs from the preorder version
    if (subtree_key == nullptr)
    {
        return nullptr;
    }
    // Note that ReconstructPreorderHelper updates subtree_idx. So the order of
    // following two calls are critical.
    auto left_subtree =
        ReconstructPostorderHelper(postorder, subtree_idx_pointer);
    auto right_subtree =
        ReconstructPostorderHelper(postorder, subtree_idx_pointer);
    return new BinaryTreeNode({*subtree_key, move(left_subtree), move(right_subtree)});
}

BinaryTreeNode * ReconstructPostOrder(
    const vector<int *> &postorder)
{
    int subtree_idx_pointer = postorder.size() - 1; //this differs from the preorder version
    return ReconstructPostorderHelper(postorder, &subtree_idx_pointer);
}


void preOrder(BinaryTreeNode *&root)
{
    if (root)
    {
        cout << root->data << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
    else{
        cout << "null "; 
    }
}

void inOrder(BinaryTreeNode *&root)
{
    if (root)
    {
        inOrder(root->left);
        cout << root->data << " ";
        inOrder(root->right);
    }
}

static void SimpleTest()
{
    int A[] = {1, 2, 3};
    vector<int *> preorder = {A, nullptr, nullptr};
    reverse(preorder.begin(), preorder.end());
    auto &postorder = preorder;
    auto result = ReconstructPostOrder(postorder);
    preOrder(result);
    cout << endl;
    assert(result->data == 1);
    assert(result->left == nullptr);
    assert(result->right == nullptr);

    preorder = {A, nullptr, A + 1, nullptr, nullptr};
    reverse(preorder.begin(), preorder.end());
    result = ReconstructPostOrder(postorder);
    preOrder(result);
    cout << endl;
    assert(result->data == 1);
    assert(result->left == nullptr);
    assert(result->right->data == 2);

    preorder = {A, nullptr, A + 1, A + 2, nullptr, nullptr, nullptr};
    reverse(preorder.begin(), preorder.end());
    result = ReconstructPostOrder(postorder);
    preOrder(result);
    cout << endl;
    assert(result->data == 1);
    assert(result->left == nullptr);
    assert(result->right->data == 2);
    assert(result->right->left->data == 3);
    assert(result->right->right == nullptr);
}

int main(int argc, char *argv[])
{
    SimpleTest();
    
    return 0;
}
