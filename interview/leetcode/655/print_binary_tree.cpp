class Solution {
    public: 
    vector<vector<string>> printTree(TreeNode* root){

        int h = getHeight(root);
        int w = 1 << h -1; // 2^h -1;
        vector<vector<string>> ans(h, vector<string> (w, ""));

        fill(root, ans, 0,0,w-1);
        return ans;


    }

    private: 
    int getHeight(TreeNode* root)
    {
        if (root == nullptr) return 0;

        return 1 + max(getHeight(root->left), getHeight(root->right));
    }

    void fill(TreeNode* root, vector<vector<string>>& ans, int h, int l, int r){

        if (root == nullptr) return;

        int mid = l + (r-1)/2;
        ans[h][mid] = std::to_string(root->val);
        fill(root->left, ans, h+1, l, mid-1);
        fill(root->right, and, h+1, mid+1, r);

    }

};