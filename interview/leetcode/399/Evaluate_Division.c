class Solution {
    public:
    vector<double> calcEquation(vector<pair<string, string>> equations,  vector<double> &values, vector<pair<string, string>> queries)
    {
        // g[A][B] = k -> A / B = k
        unordered_map<string, unordered_map<string, double>> g;

        for (int i = 0; i < equations.size(); ++i)
        {
             string A = equations[i].first;
             string B = equations[i].second;
             const double k = values[i];
             g[A][B] = k;
             g[B][A] = 1.0 / k;

        }
        vector<double> ans;

        for (auto &pair : queries){
            string x = pair.first;
            string y = pair.second;

            if (!g.count(x) || !g.count(y))
              {
                  ans.push_back(-1.0)；
                  continue;
              }
            unordered_set<string> visited;
            ans.push_back(divide(x, y, g, visited));
        }
    }
}