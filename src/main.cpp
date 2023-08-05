#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include "HashMapSC.h"
#include "HashMapLP.h"
using namespace std;
string removeQuotes(const string& str) {
    string result;
    for (char c : str) {
        if (c != '"') {
            result += c;
        }
    }
    return result;
}
string getColumnValue(const string& line, int column) {
    istringstream iss(line);
    string value;
    int currentColumn = 1; 
    while (getline(iss, value, ',')) {
        if (currentColumn == column) {
            return value;
        }
        currentColumn++;
    }
    return "";
}
int main() {
    HashMapSC<string, string> mapSC;
    HashMapLP<string, string> mapLP;
    int ct=0;
    ifstream file("classics.csv");
    if (!file) {
        cerr << "Failed to open the file." << endl;
        return 1;
    }
    string line;
    auto start1 = chrono::high_resolution_clock::now();
    while (getline(file, line)) {
        string key = getColumnValue(line, 1);
        string value = getColumnValue(line, 2);
        if (!key.empty() && !value.empty()) {
            mapSC.insert(removeQuotes(key), removeQuotes(value));
        }
    }
    auto end1 = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end1 - start1).count();
    cout << "S.C. Insert time: " << duration << " us" << endl;
    cout << "S.C. Size: " << mapSC.getSize() << endl;
    file.close();
    ifstream file2("classics.csv");
    if (!file2) {
        cerr << "Failed to open the file." << endl;
        return 1;
    }
    string line2;
    auto start2 = chrono::high_resolution_clock::now();
    while (getline(file2, line)) {
        string key = getColumnValue(line, 1);
        string value = getColumnValue(line, 2);
        if (!key.empty() && !value.empty()) {
            mapLP.insert(removeQuotes(key), removeQuotes(value));
        }
    }
    auto end2 = chrono::high_resolution_clock::now();
    auto duration2 = chrono::duration_cast<chrono::microseconds>(end2 - start2).count();
    cout << "L.P. Insert time: " << duration2 << " us" << endl;
    cout << "L.P. Size: " << mapLP.getSize() << endl;
    file2.close();
    string author; 
    int input;
    do {
        cout << "1. Search for book\n2. Remove book\n3. Remove All\n4. Check size\n5. Quit" << endl;
        cin >> input;
        cin.ignore();

        if (input == 1 || input == 2|| input == 3 || input == 4) {
            string title;
            if (input == 1 || input == 2){
                    cout << "Enter book title: ";
                    getline(cin, title);
            }
            if (input == 1) {
                if (mapSC.search(title, author) && mapLP.search(title, author)) {
                    cout << title << " by " << author << " is in the hashmap." << endl;
                } else {
                    cout << title << " not found in the map." << endl;
                }
            } else if (input == 2) {
                mapSC.remove(title);
                mapLP.remove(title);
            }
            else if (input == 3) {
                mapSC.removeAll();
                mapLP.removeAll();
            }
            else if (input == 4) {
                cout << "S.C. Size: " << mapSC.getSize() << endl;
                cout << "L.P. Size: " << mapLP.getSize() << endl;
            }
        }
    } while (input == 1 || input == 2 || input == 3 || input == 4);
}