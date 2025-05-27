#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    TreeNode* BuildBinaryTree(vector<int>& preorder, int prestart, int preend,
                              vector<int>& inorder, int instart, int inend, map<int, int>& inx) {
        if (prestart > preend || instart > inend) return nullptr;
        TreeNode* root = new TreeNode(preorder[prestart]);
        int index = inx[root->val];
        int left = index - instart;
        root->left = BuildBinaryTree(preorder, prestart + 1, prestart + left, inorder, instart, index - 1, inx);
        root->right = BuildBinaryTree(preorder, prestart + left + 1, preend, inorder, index + 1, inend, inx);
        return root;
    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        map<int, int> inx;
        for (int x = 0; x < inorder.size(); ++x) inx[inorder[x]] = x;
        return BuildBinaryTree(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1, inx);
    }
};

// Helper function to print tree in level order (as per example output)
void printTree(TreeNode* root) {
    if (!root) {
        cout << "[]" << endl;
        return;
    }
    queue<TreeNode*> q;
    q.push(root);
    vector<string> res;
    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();
        if (node) {
            res.push_back(to_string(node->val));
            q.push(node->left);
            q.push(node->right);
        } else {
            res.push_back("null");
        }
    }
    // Remove trailing "null"s
    while (!res.empty() && res.back() == "null") res.pop_back();
    cout << "[";
    for (size_t i = 0; i < res.size(); ++i) {
        if (i) cout << ",";
        cout << res[i];
    }
    cout << "]" << endl;
}

// Helper to parse input string like "[3,9,20,15,7]"
vector<int> parseInput(const string& s) {
    vector<int> res;
    string t = s;
    t.erase(remove(t.begin(), t.end(), '['), t.end());
    t.erase(remove(t.begin(), t.end(), ']'), t.end());
    stringstream ss(t);
    string item;
    while (getline(ss, item, ',')) {
        // Remove whitespace
        item.erase(remove_if(item.begin(), item.end(), ::isspace), item.end());
        if (!item.empty())
            res.push_back(stoi(item));
    }
    return res;
}

int main() {
    vector<pair<string, string>> inputs = {
        {"[3,9,20,15,7]", "[9,3,15,20,7]"},
        {"[-1]", "[-1]"}
    };

    Solution solution;

    for (const auto& input : inputs) {
        cout << "Input: preorder = " << input.first << ", inorder = " << input.second << endl;
        vector<int> preorder = parseInput(input.first);
        vector<int> inorder = parseInput(input.second);
        TreeNode* root = solution.buildTree(preorder, inorder);
        cout << "Output: ";
        printTree(root);
    }
    return 0;
}
