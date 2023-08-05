#include <iostream>
#include <vector>
#include <list>
#include <chrono>
#include <cmath>
using namespace std;
template <typename KeyType, typename ValueType>
class HashMapSC {
private:
    static const size_t bucket_ct = 100;
    typedef pair<KeyType, ValueType> KeyValuePair;
    typedef list<KeyValuePair> Bucket;
    typedef vector<Bucket> Buckets;
    Buckets buckets;
    size_t size;
    size_t hashFunction(const KeyType& key) const {
        size_t hashValue = 0;
        size_t i = 0;
        for (char c : key) {
            hashValue += c*(pow(2, i));
            i++;
        }
        return hashValue % buckets.size();
    }
public:
    HashMapSC() : size(0), buckets(bucket_ct) {}
    void insert(const KeyType& key, const ValueType& value) {
        size_t i = hashFunction(key);
        for (const auto& pair : buckets[i]) {
            if (pair.first == key) {
                return;
            }
        }
        buckets[i].push_back(make_pair(key, value));
        size++;
    }
    bool search(const KeyType& key, ValueType& value) const {
        auto start = chrono::high_resolution_clock::now();
        size_t i = hashFunction(key);
        if (size == 0) {
            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
            cout << "Hashmap is Empty\nS.C. Search time: " << duration << " us" << endl;
            return false;
        }
        for (const auto& pair : buckets[i]) {
            if (pair.first == key) {
                value = pair.second;
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
                cout << "S.C. Search time: " << duration << " us" << endl;
                return true;
            }
        }
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
        cout << "S.C Search time: " << duration << " us" << endl;
        return false;
    }
    bool remove(const KeyType& key) {
        auto start = chrono::high_resolution_clock::now();
        size_t i = hashFunction(key);
        for (auto it = buckets[i].begin(); it != buckets[i].end(); ++it) {
            if (it->first == key) {
                cout << "S.C. Removing " << key << endl;
                buckets[i].erase(it);
                size--;
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
                cout << "S.C. remove time: " << duration << " us" << endl;
                return true;
            }
        }
        cout << "Key not found. Cannot remove." << endl;
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
        cout << "S.C. remove time: " << duration << " us" << endl;
        return false;
    }
    void removeAll() {
        auto start = chrono::high_resolution_clock::now();
        buckets.clear();
        size = 0;
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
        cout << "S.C. Remove All Time: " << duration << " us" << endl;
    }
    bool isEmpty() const {
        return size == 0;
    }
    size_t getSize() const {
        return size;
    }
};


