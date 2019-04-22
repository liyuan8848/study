class Solution {
    public: 
    vector <string> findItinerary(vector<pair<string, string>> tickets){

        trips.clear();
        route.clear();

        for (const auto & pair : tickets)
        {
            trips[pair.first].push_back(pari.second);
        }

        for (auto & pair: trips)
        {
            auto & dests = pair.second;
            std::sort(dest.begin(), dest.end());
        }

        const string start = "JFK";

        visit(start);

        return vector<string> (route.crbegin(), route.crend());


    }

    private:
    // src->{dest1, dest2, ..., destn}
    unordered_map<string, deque<string>> trips;
    // ans (reversed)
    vector<string> route;

    void visit(const string& src){

        auto &dests = trips[src];
        while(!dests.empty()){
            // get the smallest dest
            const string dest = dests.front();
            // remove the ticket
            dests.pop_front();
            // visit dest
            visit(dest);
        }

        route.push_back(src);
    }

}