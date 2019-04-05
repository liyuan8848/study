class Solution{

 public:
    int findCloestLeaf(TreeNode *root, int k){

        graph_.clear();
        start_ = nullptr;
        buldGraph(root, nullptr, k);
        queue<TreeNode *>q;
        q.push(start_);
        unordered_set<TreeNode *> visited;
        while(!q.empty())
        {

            int size = q.size();
            while(size>0)
            {
                TreeNode *curr = q.front();
                q.pop();
                visited.insert(curr);
                if (!curr->left && !curr->right) return curr->val;
                for (TreeNode *node :graph_[curr])
                   if (!visited.count(node)) q.push(node);
            }




        }
        return 0;
       
    }

private:
    unordered_map<TreeNode *, vector<TreeNode *>> graph_;
    TreeNode *start_;
    void buildGraph(TreeNode *node, TreeNode* parent, int k){
        if (*node) return;
        if (node->val == k) start_ = node;
        if (parent){
            graph_[node].push_back(parent);
            graph_[parent].push_back(node);
        }
        buildGraph(node->left, node, k);
        buildGraph(node->right, node, k);
    }

};