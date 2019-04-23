class LRUCache
{
public:
    LRUCache(int cap){
        capacity = cap;
    }
    
    int get(int key){
        const auto it = m.find(key);
        if (it == m.end()) 
        {
            return -1;
        }

        // move this key to the front of the cache
        cache.splice(cache.begin(), cache, it->second);
        return it->second->second;

    }

    void put(int key, int value)
    {
        const auto it = m.find(key);
        // key already exists
        if (it != m.end())
        {
            it->second->second = value;
            cache.splice(cache.begin(), cache, it->second);
            return;
        }
        // reached the capacity , remove the oldest entry
        if (cache.size() == capacity)
         {
             // back() return the value of list, type is a pair
             const auto &node = cache.back();
             // node is a reference of pair. so only can be // used with .
             m.erase(node.first);
             // can't erase list before erase hashmap
             cache.pop_back();
         }
        // insert the entry to the front of cache and updating the mapping
        cache.emplace_front(key, value);
        m[key] = cache.begin();

    }
private:
    int capacity;
    list<pair<int, int>> cache;
    unordered_map<int, list<pair<int, int>::iterator> m;
}