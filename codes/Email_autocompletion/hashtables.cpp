#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Hash {
private:
    int BUCKET;                          // Total number of buckets
    vector<vector<int>> table;          // Vector of chains (buckets)

    // Hash function: returns bucket index
    int hashFunction(int key) {
        return key % BUCKET;
    }

public:
    // Constructor to initialize hash table
    Hash(int b) {
        BUCKET = b;
        table.resize(BUCKET);
    }

    // Inserts a key into the hash table
    void insertItem(int key) {
        int index = hashFunction(key);
        table[index].push_back(key);
        cout << "Inserted key " << key << " into bucket " << index << ".\n";
    }

    // Deletes a key from the hash table if present
    void deleteItem(int key) {
        int index = hashFunction(key);
        auto& chain = table[index];
        auto it = find(chain.begin(), chain.end(), key);
        if (it != chain.end()) {
            chain.erase(it);
            cout << "Deleted key " << key << " from bucket " << index << ".\n";
        } else {
            cout << "Key " << key << " not found in bucket " << index << ".\n";
        }
    }

    // Displays the current state of the hash table
    void displayHash() {
        cout << "\nCurrent Hash Table State:\n";
        for (int i = 0; i < BUCKET; ++i) {
            cout << "Bucket " << i << ":";
            for (int key : table[i]) {
                cout << " " << key;
            }
            cout << endl;
        }
        cout << endl;
    }
};

int main() {
    int bucketCount;
    cout << "Enter the number of buckets in hash table: ";
    cin >> bucketCount;

    Hash hashTable(bucketCount);

    int n;
    cout << "Enter number of keys to insert: ";
    cin >> n;

    cout << "Enter " << n << " keys:\n";
    for (int i = 0; i < n; ++i) {
        int key;
        cin >> key;
        hashTable.insertItem(key);
    }

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Insert key\n2. Delete key\n3. Display hash table\n4. Exit\n";
        cout << "Enter your choice: ";
        int choice; cin >> choice;

        if (choice == 1) {
            int key;
            cout << "Enter key to insert: ";
            cin >> key;
            hashTable.insertItem(key);
        } else if (choice == 2) {
            int key;
            cout << "Enter key to delete: ";
            cin >> key;
            hashTable.deleteItem(key);
        } else if (choice == 3) {
            hashTable.displayHash();
        } else if (choice == 4) {
            cout << "Exiting...\n";
            break;
        } else {
            cout << "Invalid choice, try again.\n";
        }
    }

    return 0;
}
