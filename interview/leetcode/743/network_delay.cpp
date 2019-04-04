#include <queue>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int N, int K)
    {
        
        // constexpr int MAX_TIME = 101 * 100;
        // vector<int> dist(N, MAX_TIME);
        // dist[K - 1] = 0;
        // for (int i = 1; i < N; ++i)
        //     for (const auto& time : times) {
        //         int u = time[0] - 1, v = time[1] - 1, w = time[2];
        //         dist[v] = min(dist[v], dist[u] + w);
        //     }
        // int max_dist = *max_element(dist.begin(), dist.end());
        // return max_dist == MAX_TIME ? -1 : max_dist;
        
        int INF = 0x3f3f3f3f;
        // create a min heap
        // here pair <int, int> , the first is weight, the second is label of vertex
        priority_queue < pair<int, int>, vector<pair<int, int>>, greater< pair<int, int>> > pq;
        
        //create graph
        list<pair<int, int>> *adj;
        adj = new list<pair<int, int>>[N];
        for (int i = 0; i < times.size(); i++)
        {
            adj[times[i][0]-1].push_back(make_pair(times[i][2], times[i][1]-1));
        }
        
        //create a vector for distance and initialize all distances as infinite (INF)
        vector<int> dist(N, INF);
        // insert source in priority_queue and initialize its distance to 0
        dist[K-1] = 0;
        pq.push(make_pair(0,K-1));
        
        // looping till priority queue becomes empty
        while(!pq.empty())
        {
            
            int u = pq.top().second;
            pq.pop();
            
            for (auto i = adj[u].begin(); i!= adj[u].end(); i++)
            {
                int v = (*i).second;
                int weight = (*i).first;
                
                if (dist[v] > dist[u] + weight)
                {
                    dist[v] = dist[u] + weight;
                    pq.push(make_pair(dist[v], v));
                 }
            }
            
           
        }
        
         int res = *max_element(dist.begin(), dist.end());
              return res==INF ? -1 : res;
            
        
    }
          
};



int main()
{
    vector<vector<int>> input{{2,1,1},{2,3,1},{3,4,1}};

    int n = 4;
    int k = 2;

    cout << Solution().networkDelayTime(input, n, k) << endl;

   

}