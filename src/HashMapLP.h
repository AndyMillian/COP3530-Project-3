#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>
using namespace std;

template <typename KeyType, typename ValueType>
class HashMapLP {
private:
    static const size_t bucket_ct = 1000;
    typedef pair<KeyType, ValueType> KeyValuePair;
    typedef vector<KeyValuePair> Buckets;
    Buckets buckets;
    size_t size;
    size_t hashFunction(const KeyType& key) const {
        size_t hashValue = 0;
        size_t i= 0;
        for (char c : key) {
            hashValue += c*(pow(2, i));
            i++;
        }
        return hashValue % buckets.size();
    }
public:
    HashMapLP() : size(0), buckets(bucket_ct) {}
    void insert(const KeyType& key, const ValueType& value) {
        size_t i = hashFunction(key);
        size_t step = 1; 
        while (buckets[i].first != KeyType() && buckets[i].first != key) {
            i = (i + step) % buckets.size();
        }
        if (buckets[i].first == key) {
            return;
        }
        buckets[i] = make_pair(key, value);
        size++;
    }
    bool search(const KeyType& key, ValueType& value) const {
        auto start = chrono::high_resolution_clock::now();
        size_t i = hashFunction(key);
        size_t step = 1;
        while (buckets[i].first != KeyType() && buckets[i].first != key) {
            i = (i + step) % buckets.size();
        }
        if (buckets[i].first == key) {
            value = buckets[i].second;
            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
            cout << "L.P. Search time: " << duration << " us" << endl;
            return true;
        }
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
        cout << "L.P. Search time: " << duration << " us" << endl;
        return false;
    }
    bool remove(const KeyType& key) {
        auto start = chrono::high_resolution_clock::now();
        size_t i = hashFunction(key);
        size_t step = 1;
        while (buckets[i].first != KeyType() && buckets[i].first != key) {
            i = (i + step) % buckets.size();
        }
        if (buckets[i].first == key) {
            buckets[i] = make_pair(KeyType(), ValueType()); 
            size--;
            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
            cout << "L.P. Remove time: " << duration << " us" << endl;
            return true;
        }
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
        cout << "L.P. Remove time: " << duration << " us" << endl;
        return false;
    }
    void removeAll() {
        auto start = chrono::high_resolution_clock::now();
        buckets.clear();
        size = 0;
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
        cout << "L.P. Remove time: " << duration << " us" << endl;
    }

    bool isEmpty() const {
        return size == 0;
    }

    size_t getSize() const {
        return size;
    }
};
