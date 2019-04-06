class Solution{
public: 
vector<int> eventualSafeNodes(vector<vector<int>> &graph)
{  
    vector<state> states(graph.size(), UNKNOWN);
    ve ctor<int> ans;

    for (int i = 0; i < graph.size(); i++)
    {
        if (dfs(graph, i, states) == SAFE)
          ans.push_back(i);
    }

    return ans;


}
private:
    enum state {UNKNOWN, VISITING, UNSAFE, SAFE};

    state dfs(vector<vector<int>> &graph, int cur, vector<state> &states)
    {
        if (states[cur] == VISITING)
            return states[cur] = UNSAFE;
        if (states[cur] != UNKNOWN)
            return states[cur];
        states[cur] = VISITING;

        for (int next : graph[cur])
        {
            if (dfs(graph, next, states) == UNSAFE)
             return states[cur] = UNSAFE;
        }
        return states[cur] = SAFE;
    }
};