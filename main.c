#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 3000

// Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// Build tree from preorder and inorder arrays
struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize) {
    if (preorderSize <= 0 || inorderSize <= 0)
        return NULL;

    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = preorder[0];
    root->left = root->right = NULL;

    int i = 0;
    for (; i < inorderSize; ++i) {
        if (inorder[i] == root->val)
            break;
    }
    root->left = buildTree(preorder + 1, i, inorder, i);
    root->right = buildTree(preorder + i + 1, preorderSize - i - 1, inorder + i + 1, inorderSize - i - 1);
    return root;
}

// Helper to parse input string like "[3,9,20,15,7]" into array
int parseInput(const char* s, int* arr) {
    int n = 0;
    int i = 0, sign = 1, num = 0, inNum = 0;
    while (s[i]) {
        if (s[i] == '-' || (s[i] >= '0' && s[i] <= '9')) {
            sign = 1;
            if (s[i] == '-') {
                sign = -1;
                ++i;
            }
            num = 0;
            inNum = 0;
            while (s[i] >= '0' && s[i] <= '9') {
                num = num * 10 + (s[i] - '0');
                ++i;
                inNum = 1;
            }
            if (inNum) arr[n++] = num * sign;
        } else {
            ++i;
        }
    }
    return n;
}

// Helper to print tree in level order (as per example output)
void printTree(struct TreeNode* root) {
    if (!root) {
        printf("[]\n");
        return;
    }
    struct TreeNode* queue[MAX_NODES];
    int front = 0, rear = 0;
    char* res[MAX_NODES];
    int res_len = 0;
    queue[rear++] = root;
    while (front < rear) {
        struct TreeNode* node = queue[front++];
        if (node) {
            char* buf = (char*)malloc(16);
            sprintf(buf, "%d", node->val);
            res[res_len++] = buf;
            queue[rear++] = node->left;
            queue[rear++] = node->right;
        } else {
            res[res_len++] = strdup("null");
        }
    }
    // Remove trailing "null"s
    while (res_len > 0 && strcmp(res[res_len-1], "null") == 0)
        res_len--;
    printf("[");
    for (int i = 0; i < res_len; ++i) {
        if (i) printf(",");
        printf("%s", res[i]);
        free(res[i]);
    }
    printf("]\n");
}

// Helper to free the memory of a tree
void deleteTree(struct TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}

int main() {
    const char* preorderInputs[] = {
        "[3,9,20,15,7]",
        "[-1]"
    };
    const char* inorderInputs[] = {
        "[9,3,15,20,7]",
        "[-1]"
    };
    int num_cases = sizeof(preorderInputs) / sizeof(preorderInputs[0]);

    for (int i = 0; i < num_cases; ++i) {
        printf("Input: preorder = %s, inorder = %s\n", preorderInputs[i], inorderInputs[i]);
        int preorder[MAX_NODES], inorder[MAX_NODES];
        int preSize = parseInput(preorderInputs[i], preorder);
        int inSize = parseInput(inorderInputs[i], inorder);
        struct TreeNode* root = buildTree(preorder, preSize, inorder, inSize);
        printf("Output: ");
        printTree(root);
        deleteTree(root);
    }
    return 0;
}
