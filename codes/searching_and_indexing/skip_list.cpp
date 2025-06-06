#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#define MAX_LEVEL 6
const float P = 0.5;

using namespace std;

/*
 * Skip Node Declaration
 */
struct snode {
    int value;
    snode** forw;

    snode(int level, int &value) {
        forw = new snode*[level + 1];
        memset(forw, 0, sizeof(snode*) * (level + 1));
        this->value = value;
    }

    ~snode() {
        delete[] forw;
    }
};

/*
 * Skip List Declaration
 */
struct skiplist {
    snode* header;
    int level;
    int value; // This was unnecessary, but keeping it for consistency

    skiplist() {
        value = -1;
        header = new snode(MAX_LEVEL, value);
        level = 0;
    }

    ~skiplist() {
        delete header;
    }

    int random_level() {
        int lvl = 0;
        while (((float)rand() / RAND_MAX) < P && lvl < MAX_LEVEL)
            lvl++;
        return lvl;
    }

    void insert_element(int &value) {
        snode* current = header;
        snode* update[MAX_LEVEL + 1];
        memset(update, 0, sizeof(snode*) * (MAX_LEVEL + 1));

        for (int i = level; i >= 0; i--) {
            while (current->forw[i] != nullptr && current->forw[i]->value < value) {
                current = current->forw[i];
            }
            update[i] = current;
        }

        current = current->forw[0];

        if (current == nullptr || current->value != value) {
            int rlevel = random_level();

            if (rlevel > level) {
                for (int i = level + 1; i <= rlevel; i++) {
                    update[i] = header;
                }
                level = rlevel;
            }

            snode* n = new snode(rlevel, value);
            for (int i = 0; i <= rlevel; i++) {
                n->forw[i] = update[i]->forw[i];
                update[i]->forw[i] = n;
            }

            cout << "Successfully inserted: " << value << endl;
        } else {
            cout << "Element already exists!" << endl;
        }
    }

    void delete_element(int &value) {
        snode* current = header;
        snode* update[MAX_LEVEL + 1];
        memset(update, 0, sizeof(snode*) * (MAX_LEVEL + 1));

        for (int i = level; i >= 0; i--) {
            while (current->forw[i] != nullptr && current->forw[i]->value < value) {
                current = current->forw[i];
            }
            update[i] = current;
        }

        current = current->forw[0];

        if (current != nullptr && current->value == value) {
            for (int i = 0; i <= level; i++) {
                if (update[i]->forw[i] != current)
                    break;
                update[i]->forw[i] = current->forw[i];
            }

            delete current;

            while (level > 0 && header->forw[level] == nullptr) {
                level--;
            }

            cout << "Successfully deleted: " << value << endl;
        } else {
            cout << "Element not found!" << endl;
        }
    }

    bool contains(int &value) {
        snode* current = header;
        for (int i = level; i >= 0; i--) {
            while (current->forw[i] && current->forw[i]->value < value) {
                current = current->forw[i];
            }
        }

        current = current->forw[0];

        return current && current->value == value;
    }

    void display() {
        cout << "\n*****Skip List*****" << endl;
        for (int i = 0; i <= level; i++) {
            snode* node = header->forw[i];
            cout << "Level " << i << ": ";
            while (node != nullptr) {
                cout << node->value << " ";
                node = node->forw[i];
            }
            cout << endl;
        }
    }
};

/*
 * Main: Contains Menu
 */
int main() {
    skiplist ss;
    int choice, n;

    while (true) {
        cout << "\n-----------------------" << endl;
        cout << "Operations on Skip List" << endl;
        cout << "-----------------------" << endl;
        cout << "1. Insert Element" << endl;
        cout << "2. Delete Element" << endl;
        cout << "3. Search Element" << endl;
        cout << "4. Display List" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter the element to be inserted: ";
            cin >> n;
            ss.insert_element(n);
            break;
        case 2:
            cout << "Enter the element to be deleted: ";
            cin >> n;
            ss.delete_element(n);
            break;
        case 3:
            cout << "Enter the element to search: ";
            cin >> n;
            if (ss.contains(n))
                cout << "Element found!" << endl;
            else
                cout << "Element not found!" << endl;
            break;
        case 4:
            ss.display();
            break;
        case 5:
            exit(0);
        default:
            cout << "Invalid choice!" << endl;
        }
    }

    return 0;
}
