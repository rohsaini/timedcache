#include <iostream>
#include <bits/stdc++.h> 
#include <unistd.h>

#define TIME_NOW ((uint32_t) time(NULL))

using namespace std;

template <typename key_DT, typename value_DT>
class timedCache {
  private:
      uint16_t                    _time_to_live;
      key_DT                      _latest_key;
      multimap<key_DT, value_DT>  _cachemap;
      typedef typename multimap<key_DT, value_DT>::iterator       ITER;
      typedef typename multimap<key_DT, value_DT>::const_iterator CONST_ITER;

      /*
       *  Checks if ttl of key is expired
       */
      bool has_expired(key_DT key) {
          auto elapsed = TIME_NOW - key;
          return (elapsed > _time_to_live);
      }

  public:
    timedCache(uint16_t ttl) {
        _time_to_live = ttl;
        _latest_key   = 0;
        _cachemap.clear();
    }

    ~timedCache() {
    }

    /*
     *  Inserts the key of type value_DT into cache
     */
    void insert(key_DT key, value_DT data) {
        _cachemap.insert({key, data});
        _latest_key = key;
    }

    /*
     *  Emplaces the key of type value_DT into cache
     */
    void emplace(key_DT key, value_DT data) {
        _cachemap.emplace(key, data);
        _latest_key = key;
    }

    /*
     *  Returns the last key added to cache
     */
    key_DT get_latest_key() {
        return _latest_key;
    }

    /*
     *  Returns the count of a valid key
     */
    uint32_t count (key_DT key) {
        int cnt = _cachemap.count(key);

        if (cnt && !has_expired(key)) {
            return cnt;
        }
        return 0;
    }

    /*
     *  Returns the size of cache map
     */
    uint64_t size() {
        return _cachemap.size();
    }

    /*
     *  Returns the max size of cache map
     */
    uint64_t max_size() {
        return _cachemap.max_size();
    }

    /*
     *  Returns True if cache is empty, otherwise False
     */
    bool empty() {
        return _cachemap.empty();
    }

    /*
     *  Clears the cache
     */
    void clear() {
        _cachemap.clear(); 
    }

    /*
     *  Returns the const iterator for lower bound of key
     */
    CONST_ITER lower_bound(key_DT key) {
        return _cachemap.lower_bound(key);
    }

    /*
     *  Returns the const iterator for upper bound of key
     */
    CONST_ITER upper_bound(key_DT key) {
        return _cachemap.upper_bound(key);
    }

    /*
     * Returns the const iterator for a key if key is valid
     */
    CONST_ITER get_elem_iter(key_DT key) {
        CONST_ITER iter = _cachemap.find(key);

        if ( iter != _cachemap.cend() && !has_expired(key)) {
            return iter;
        } else {
            return _cachemap.cend();
        }
    }

    /*
     *  Returns const begin iterator of cache map
     */
    CONST_ITER get_begin() {
        return _cachemap.cbegin();
    }

    /*
     *   Returns const end iterator of cache map
     */
    CONST_ITER get_end() {
        return _cachemap.cend();
    }

    /*
     *  Removes the expired entries from cache map
     */
    void remove_expired() {
        ITER iter_start = _cachemap.begin();
        ITER iter_end   = _cachemap.lower_bound(TIME_NOW - _time_to_live);

        _cachemap.erase(iter_start, iter_end);
    }
};
