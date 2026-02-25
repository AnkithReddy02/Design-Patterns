#include <bits/stdc++.h>
using namespace std;

// Eviction policies represent the Strategy Pattern that we can inject in our
// Cache tier storage.
class IEvictionPolicy {
public:
    virtual void Put(int key) = 0;
    virtual void Get(int key) = 0;
    virtual int Evict() = 0;
    virtual void Remove(int key) = 0;
};

class LRUEvictionPolicy : public IEvictionPolicy {
public:
    void Put(int key) override {
        if (key_cache_map_.count(key)) {
            Get(key);
            return;
        }

        cache_.push_front(key);
        key_cache_map_[key] = cache_.begin();
        return;
    }

    void Get(int key) override {
        auto it = key_cache_map_.find(key);
        if (it == key_cache_map_.end()) return;

        cache_.erase(it->second);
        cache_.push_front(key);
        key_cache_map_[key] = cache_.begin();
    }

    int Evict() override {
        int key = cache_.back();
        cache_.pop_back();
        key_cache_map_.erase(key);
        return key;
    }

    void Remove(int key) override {
        auto it = key_cache_map_.find(key);
        if (it == key_cache_map_.end()) return;

        cache_.erase(it->second);
        key_cache_map_.erase(key);
    }

private:
    list<int> cache_;

    unordered_map<int, list<int>::iterator> key_cache_map_;
};

// This is chain of responsibility. 
// `next_cache_tier_` represents the storage next it should search the data
// for. It is the responsibility of each tier to pass on to the next tier.
class CacheTier {
public:
  CacheTier(
    const string& p_cache_tier_name,
    unique_ptr<CacheTier>&& p_next_cache_tier,
    const int max_storage_size,
    unique_ptr<IEvictionPolicy>&& p_eviction_policy) :
    cache_tier_name_(p_cache_tier_name),
    next_cache_tier_(move(p_next_cache_tier)),
    max_storage_size_(max_storage_size),
    eviction_policy_(move(p_eviction_policy)) {
    
  }
  
  void Put(int key, int value) {
    if ((storage_.size() == max_storage_size_) &&
        (storage_.find(key) == storage_.end())) {
        int evicted_key = eviction_policy_->Evict();
        int evicted_value = storage_[evicted_key];
        storage_.erase(evicted_key);
        
        if (next_cache_tier_) {
            next_cache_tier_->Put(evicted_key, evicted_value);
        }
    }
    
    eviction_policy_->Put(key);
    storage_[key] = value;
  }
  
  int Get(int key) {
    if (storage_.find(key) == storage_.end()) {
        if (next_cache_tier_) {
            int val =  next_cache_tier_->Get(key);
            
            if (val != -1) {
              Put(key, val);  // Promote
              return val;
            }
        }
        return -1;
    }
    
    
    eviction_policy_->Get(key);
    return storage_[key];
  }
  
  void PrintStorage() {
      
      cout << cache_tier_name_ << endl;
      
      cout << "===========================" << endl;
      for (auto x : storage_) {
          cout << x.first << ' ' << x.second << endl;
      }
      
      cout << "===========================" << endl;
      
      if (next_cache_tier_) {
          next_cache_tier_->PrintStorage();
      }
  }
  
private:
  unordered_map<int, int> storage_;
  
  string cache_tier_name_;
  
  unique_ptr<CacheTier> next_cache_tier_;
  
  int max_storage_size_;
  
  unique_ptr<IEvictionPolicy> eviction_policy_;
};

int main() {
    // TODO: We can make this a builder pattern.
    unique_ptr<CacheTier> hdd_cache_tier =
      make_unique<CacheTier>(
        "HDD", nullptr, 1, make_unique<LRUEvictionPolicy>());
    unique_ptr<CacheTier> ssd_cache_tier =
      make_unique<CacheTier>(
        "SSD", move(hdd_cache_tier), 1, make_unique<LRUEvictionPolicy>());
    unique_ptr<CacheTier> ram_cache_tier =
      make_unique<CacheTier>(
        "RAM", move(ssd_cache_tier), 3, make_unique<LRUEvictionPolicy>());
    
    
    ram_cache_tier->Put(1, 2);
    ram_cache_tier->Put(2, 3);
    ram_cache_tier->Put(3, 4);
    ram_cache_tier->Put(3, 6);   
    ram_cache_tier->Put(4, 5); 
    
    ram_cache_tier->PrintStorage();
    
    ram_cache_tier->Get(1); 
    
    ram_cache_tier->PrintStorage();
    
    
}