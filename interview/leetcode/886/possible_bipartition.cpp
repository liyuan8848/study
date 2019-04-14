// Solution with DFS

class Solution {
    public:
    bool possibleBipartition(int N, vector<vector<int>> &dislikes){
        g_= vector<vector<int>>(N);
        for (const auto &d : dislikes){

            g_[d[0]-1].push_back(d[1]-1);
            g_[d[1]-1].push_back(d[0]-1);
        }
        colors_ = vector<int>(N, 0); // 0 : unknown, 1 : red -1 : blue
        for (int i = 0; i < N; i++)
        {
            if (colors_[i] == 0 && !dfs(i, 1)) return false;
        }
        return true;
    }

    private:
        vector<vector<int>> g_;
        vector<int> colors_;
        bool dfs (int cur, int color) {

            colors_[cur] = color;
            for (int next : g_[cur]){
                if (colors_[next] == color) return false;
                if (colors_[next]==0 && !dfs(next, -color)) return false;
            }
            return true;
        }
};



// Solution with BFS
class Solution {

public: 
    bool possibleBipartition(int N, vector<vector<int>> &dislikes){

        vector<vector<int >> g(N);
        for (const auto& d: dislikes )
        {
            g[d[0]-1].push_back(d[1]-1);
            g[d[1]-1].push_back(d[0]-1);

        }

        queue<int> q;

        vector<int> colors(N, 0); // 0 : unknown, 1, red, -1 : blue

        for (int i = 0; i < N; i++){

            if (colors[i]!=0) continue;
            q.push(i);

            colors[i] = 1;
            while (!q.empty())
            {
                int cur = q.front(); q.pop();
                for (int next : g[cur]){

                    if (colors[next] == colors[cur]) return false;
                    if (colors[next] != 0) continue;
                    colors[next] = -colors[cur];
                    q.push(next);

                }

            }
        }
            return true;

    }



};