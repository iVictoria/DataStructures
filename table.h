/*************************************************************/
/*                                                           */
/*    Assignment 1                                           */
/*    Victoria Castillo -                                    */
/*                                                           */
/*************************************************************/
#include <iostream>
#include <string>
#include <utility>
using namespace std;

template <class TYPE>
class Table {
public:
    Table() {}
    virtual bool update(const string& key, const TYPE& value) = 0;
    virtual bool remove(const string& key) = 0;
    virtual bool find(const string& key, TYPE& value) = 0;
    virtual int numRecords() const = 0;
    virtual bool isEmpty() const = 0;
    virtual ~Table() {}
};

template <class TYPE>
class SimpleTable :public Table<TYPE> {
    
    struct Record {
        TYPE data_;
        string key_;
        Record(const string& key, const TYPE& data) {
            key_ = key;
            data_ = data;
        }
        
    };
    
    Record** records_;   //the table
    int max_;           //capacity of the array
    int size_;          //current number of records held
    int search(const string& key);
    
public:
    SimpleTable(int capacity);
    virtual bool update(const string& key, const TYPE& value);
    virtual bool remove(const string& key);
    virtual bool find(const string& key, TYPE& value);
    virtual ~SimpleTable();
    virtual bool isEmpty() const { return size_ == 0; }
    virtual int numRecords() const { return size_; }
};


//returns index of where key is found.
template <class TYPE>
int SimpleTable<TYPE>::search(const string& key) {
    int rc = -1;
    for (int i = 0; i < size_; i++) {
        if (records_[i]->key_ == key) {
            rc = i;
        }
    }
    return rc;
}


template <class TYPE>
SimpleTable<TYPE>::SimpleTable(int capacity) : Table<TYPE>() {
    records_ = new Record * [capacity];
    max_ = capacity;
    size_ = 0;
}


template <class TYPE>
bool SimpleTable<TYPE>::update(const string& key, const TYPE& value) {
    int idx = search(key);
    if (idx == -1) {
        if (size_ < max_) {
            records_[size_++] = new Record(key, value);
            for (int i = 0; i < size_ - 1; i++) {
                for (int j = 0; j < size_ - 1 - i; j++) {
                    if (records_[j] > records_[j + 1]) {
                        Record* tmp = records_[j];
                        records_[j] = records_[j + 1];
                        records_[j + 1] = tmp;
                    }
                }
            }
        }
    }
    else {
        records_[idx]->data_ = value;
    }
    return true;
}

template <class TYPE>
bool SimpleTable<TYPE>::remove(const string& key) {
    int idx = search(key);
    if (idx != -1) {
        delete records_[idx];
        for (int i = idx; i < size_ - 1; i++) {
            records_[i] = records_[i + 1];
        }
        size_--;
        return true;
    }
    else {
        return false;
    }
}

template <class TYPE>
bool SimpleTable<TYPE>::find(const string& key, TYPE& value) {
    bool found = false;
    int idx = search(key);
    if (idx != -1) {
        if (records_[idx]->data_ == value) {
            found = true;
        }
        
    }
    
    return found;
}

template <class TYPE>
SimpleTable<TYPE>::~SimpleTable() {
    
}

/*************************************************************/
/*                                                           */
/*    Linear Probing Table                                   */
/*                                                           */
/*************************************************************/


template <class TYPE>
class LPTable :public Table<TYPE> {
    
    struct Record {
        TYPE data_;
        string key_;
        Record(const string& key, const TYPE& data) {
            key_ = key;
            data_ = data;
        }
        
    };
    
    Record** records_;   //the table
    int max_;           //capacity of the array
    int size_;          //current number of records held
    int capacity_;
    int search(const string& key);
    int hashCode(const string& key);
    
    
public:
    LPTable(int capacity, double maxLoadFactor);
    void printTable();
    virtual bool update(const string& key, const TYPE& value);
    virtual bool remove(const string& key);
    virtual bool find(const string& key, TYPE& value);
    virtual ~LPTable();
    virtual bool isEmpty() const { return size_ == 0; }
    virtual int numRecords() const  { return size_ ; }
    
};
template <class TYPE>
LPTable<TYPE>::LPTable(int capacity, double maxLoadFactor) : Table<TYPE>() {
    records_ = new Record * [capacity];
    capacity_ = capacity;
    max_ = capacity*maxLoadFactor;
    size_ = 0;
    
    for (int i = 0; i < max_; i++) {
        records_[i] = nullptr;
    }
}

// returns index of where key is found, -1 if not found
template <class TYPE>
int LPTable<TYPE>::search(const string & key) {
    int rc = -1;
    int idx = hashCode(key);
    
    while (records_[idx] != nullptr)
    {
        if (records_[idx]->key_.compare(key) == 0)
            rc = idx;
        idx++;
        idx %= capacity_;
    }
    
    return rc;
}

template <class TYPE>
int LPTable<TYPE>::hashCode(const string& key) {
    
    int hashCode_ = 0;
    
    for (int i = 0; i < key.length(); i++) {
        hashCode_ = hashCode_ + key[i];
    }
    
    int idx = hashCode_ % capacity_;
    
    return idx;
}

template <class TYPE>
bool LPTable<TYPE>::update(const string & key, const TYPE & value) {
    
    bool updated = false;
    int counter = 0;
    int idx = search(key);
    Record* temp = new Record(key, value);
    
    // only update value if exists, then end function
    if (idx > -1)
    {
        records_[idx]->data_++;
        return true;
    }
    else
        idx = hashCode(key); // get hashcode if new entry
    
    // check if filled at hashkey, and write at next to avoid collision
    while (records_[idx] != nullptr && records_[idx]->key_.compare(key) != 0 && !(records_[idx]->data_ == 0 && records_[idx]->key_ == "\0"))
    {
        idx++;
        idx %= capacity_; // using modulo to loop back to the start
        
        // count filled records and exit to avoid infinite loop
        counter++;
        if (counter > capacity_)
            return false;
    }
    
    // update at empty or deleted record
    if (records_[idx] == nullptr || (records_[idx]->data_ == 0 && records_[idx]->key_ == "\0"))
    {
        if (size_ < max_)
        {
            if (temp->data_ == 0) temp->data_ = 1;
            records_[idx] = temp;
            size_++;
            updated = true;
        }
    }
    return updated;
    
}

template <class TYPE>
bool LPTable<TYPE>::remove(const string & key) {
    
    bool removed = false;
    
    if (isEmpty())
        return removed;
    
    int idx = search(key);
    Record* delRec = new Record("\0", 0);

    while (records_[idx] != nullptr && idx > -1)
    {
        if (records_[idx]->key_.compare(key) == 0)
        {
            Record* temp = records_[idx];
            records_[idx] = delRec;
            delete temp;
            size_--;
            removed = true;
        }
        idx++;
        idx %= capacity_;
    }
    
    return removed;
}

template <class TYPE>
bool LPTable<TYPE>::find(const string & key, TYPE & value) {
    
    bool found = false;
    
    if (isEmpty())
        return found;
    
    int idx = search(key);
    
    if (idx != -1)
    {
        if (records_[idx]->key_.compare(key) == 0 && records_[idx]->data_ == value)
            found = true;
    }
    return found;
}


template <class TYPE>
void LPTable<TYPE>::printTable() {
    
    for (int i = 0; i < capacity_; i++)
        if (records_[i] == nullptr) {
            cout << "record " << i << ":\t" << "EMPTY" << endl;
        }
        else {
            if (records_[i]->key_ == "\0" && records_[i]->data_ == 0) {
                cout << "record " << i << ":\t" << "DELETED" << endl;
            }
            else {
                cout << "record " << i << ":\t(" << records_[i]-> key_ << " , " << records_[i]->data_ << ")" << endl;
            }
        }
    
    
}


template <class TYPE>
LPTable<TYPE>::~LPTable() {
    
}


