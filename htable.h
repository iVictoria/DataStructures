// Victoria Castillo - 111523171
// DSA 555 Lab 6

#define TABLE_SIZE 5
#define BUCKET_SIZE 4

using namespace std;

class Bucket {
    int bucket[TABLE_SIZE][BUCKET_SIZE] = { { 0 } };
    
public:
    Bucket();
    void insert_(int key, int value);
    void delete_(int key, int value);
    bool find(int key, int value);
    bool isFull(int key);
    bool isEmpty(int key);
    void display();
};

Bucket::Bucket() {
    
}

void Bucket::insert_(int key, int value) {
    
    if (isFull(key)) {
        cout << "This bucket is full!" << endl;
    }
    if (find(key, value)) {
        cout << "Not inserted - The value " << value << " exists in this key" << endl;
    }
    else {
        for (int i = 0; i < 4; i++) {
            if (bucket[key%TABLE_SIZE][i] == 0) {
                bucket[key%TABLE_SIZE][i] = value;
                break;
            }
        }
    }
}

void Bucket::delete_(int key, int value) {
    // find first if already exists
    if (find(key, value)) {
        for (int i = 0; i < 4; i++) {
            if (bucket[key%TABLE_SIZE][i] == value) {
                bucket[key%TABLE_SIZE][i] = 0;
                cout << "-- Deleted --" << endl;
            }
        }
    } else {
        cout << "Not deleted - value not found at key" << endl;
    }
    
}

bool Bucket::find(int key, int value) {
    bool rc = false;
    
    if (!isEmpty(key)) {
        for (int i = 0; i < TABLE_SIZE; i++) {
            if (bucket[key%TABLE_SIZE][i] == value) {
                rc = true;
            }
        }
    }
    return rc;
}

bool Bucket::isFull(int key) {
    bool rc = false;
    int count = 0;
    
    for (int i = 0; i < BUCKET_SIZE; i++) {
        if (bucket[key%TABLE_SIZE][i] != 0)
            count++;
    }
    
    if (count == BUCKET_SIZE)
        rc = true;
    
    return rc;
}

bool Bucket::isEmpty(int key) {
    bool rc = false;
    int count = 0;
    
    for (int i = 0; i < BUCKET_SIZE; i++) {
        if (bucket[key%TABLE_SIZE][i] == 0)
            count++;
    }
    
    if (count == BUCKET_SIZE)
        rc = true;
    
    return rc;
}


void Bucket::display() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        cout << "[" << i << "]:\t";
        for (int j = 0; j < BUCKET_SIZE; j++) {
            cout << bucket[i][j] << "\t";
        }
        cout << endl;
    }
}

class Node {
public:
    int key;
    int value;
    struct Node *next;
    
    Node (int key, int value) {
        this->key = key;
        this->value = value;
        this->next = nullptr;
    }
};

class Chain {
private:
    Node** table;
    
public:
    Chain();
    void insert_(int key, int value);
    void delete_(int key, int value);
    bool find(int key, int value);
    bool isEmpty(int key);
    void display();
    int HashFunc(int key);
    
};

Chain::Chain() {
    Node* front;
    table = new Node*[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        front = new Node(i, 0);
        table[i] = front;
    }
}

void Chain::insert_(int key, int value) {
    if (find(key, value)) {
        cout << "Not inserted - value exists at this key" << endl;
    } else {
        Node* new_node = new Node(key, value);
        Node* ptr = table[HashFunc(key)];
        Node* last = new Node(key, 0);
        if (isEmpty(key)) {
            table[HashFunc(key)]->next = new_node;
        }
        while (ptr != NULL) {
            last = ptr;
            ptr = ptr->next;
        }
        last->next = new_node;
        new_node->value = value;
        new_node->next = NULL;
        
    }
}

void Chain::delete_(int key, int value) {
    Node* prev = NULL;
    Node* temp = table[HashFunc(key)];
    if (!find(key, value)) {
        cout << "Not deleted - value not found at key" << endl;
    }
    
    if (find (key, value)) {
    while (temp->value != value) {
        prev = temp;
        temp = temp->next;
    }
    
    if (prev != NULL) {
        prev->next = temp->next;
    }
    delete temp;
    cout << "Deleted" << endl;
    }
}

bool Chain::find(int key, int value) {
    bool rc = false;
    if (isEmpty(key)) {
        rc = false;
    } else
    {
        Node *node = table[HashFunc(key)];
        while (node != NULL ) {
            if (node->value == value) {
                rc=true;
            }
            node = node->next;
        }
    }
    return rc;
}

bool Chain::isEmpty(int key) {
    bool rc = false;
    
    if (table[HashFunc(key)]->next == nullptr)
        rc = true;
    
    return rc;
}

int Chain::HashFunc(int key) {
    return key % TABLE_SIZE;
}

void Chain::display() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        cout << "[" << i << "]:\t";
        if (table[i] != NULL) {
            Node * temp = table[i];
            while (temp != NULL ) {
                if (temp->value > 0)
                cout << temp->value << "\t";
                temp = temp->next;
            }
        }
        cout << endl;
    }
}
