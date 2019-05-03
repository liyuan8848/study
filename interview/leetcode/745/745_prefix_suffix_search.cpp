
class WordFilter{
    public:
      WordFilter(const vector<string> &words){
    int index = 0;
    
    for (const string &word : words){
        int
         n = word.length();
        string prefix;
        for (int i = 0; i <=n; ++i){
            if (i > 0) prefix +=word[i-1];
            string suffix;
            for (int j = n; j >=0; --j){
                if (j!=n) suffix = word[j]+suffix;
                const string key = prefix +"_"+suffix;
                filters[key] = index;
            }
        }
        ++index;
    }
    }

    int f(string prefix, string suffix)
    {
        const string key = prefix + "_"+suffix;
        auto it = filters.find(key);
        if (it!=filter.end())
         {
             return it->second;
         }
        return -1;
      }
      private:
       unordered_map<string, int> filters;
}
