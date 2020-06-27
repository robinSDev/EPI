#include <bits/stdc++.h>
using namespace std;

struct BinaryTreeNode
{
    int data;
    BinaryTreeNode *left, *right;
};

BinaryTreeNode *
createTreeHelper(const vector<int> &nums, int low, int high)
{
    if (low < high)
    {
        BinaryTreeNode *root = new BinaryTreeNode;
        int mid = low + (high - low) / 2;
        root->data = nums[mid];
        root->left = createTreeHelper(nums, low, mid);
        root->right = createTreeHelper(nums, mid + 1, high);
        return root;
    }
    return nullptr;
}

BinaryTreeNode *createTree(vector<int> &nums)
{
    BinaryTreeNode *root = nullptr;
    sort(nums.begin(), nums.end());
    int n = nums.size();
    int high = n - 1, low = 0u;
    return createTreeHelper(nums, low, high);
}

void preOrder(BinaryTreeNode *&root)
{
    if (root)
    {
        cout << root->data << " ";
        preOrder(root->left);
        preOrder(root->right);
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

static mt19937 mte(chrono::steady_clock::now().time_since_epoch().count());
vector<int> generate_random_vector_with_distinct_values(int size, int start, int end)
{
    unordered_set<int> hs;
    uniform_int_distribution<int> dis(start, end);
    while (size)
    {
        int val = dis(mte);
        if (hs.find(val) == hs.end()) 
        {
            hs.insert(val);
            --size;
        }
    }
    size = hs.size();
    vector<int> result(size);
    for (const auto& i : hs)
        result[--size] = i;
    return result;
}

vector<int> generate_random_vector(int size, int start, int end)
{
    uniform_int_distribution<int> dis(start, end);
    vector<int> result(size);
    while(size--)
        result[size] = dis(mte);
    return result;
}

int test1()
{
    vector<int> nums = generate_random_vector_with_distinct_values(20, 0, 50);
    BinaryTreeNode *root = createTree(nums);
    preOrder(root);
    cout << endl;
    inOrder(root);
    cout << endl;
    return 0;
}


int test2()
{
    vector<int> nums = generate_random_vector(20, 0, 50);
    BinaryTreeNode *root = createTree(nums);
    preOrder(root);
    cout << endl;
    inOrder(root);
    cout << endl;
    return 0;
}

int main(int argc, char const *argv[])
{
    assert((test1() or test2()) == 0);
    return 0;
}
