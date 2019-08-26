//
//  lab6tester.cpp
//  lab06
//
//  Created by Victoria Castillo on 2019-06-20.
//  Copyright © 2019 Victoria Castillo. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include "htable.h"

using namespace std;

int main(int argc, const char * argv[]) {
    int opt;
    char ht;
    Bucket* b = new Bucket();
    Chain* c = new Chain();
    do {
        cout << "* * * * * DSA 555 Lab 6: Hash Tables * * * * * " <<endl;
        cout << "Type 'B' for Bucketing" << endl;
        cout << "Type 'C' for Chaining" << endl;
        cout << "Type 'X' to quit" << endl;
        cout << "Selection: ";
        cin >> ht;
        ht = toupper(ht);
        
        switch (ht) {
            case 'B' :
            case 'b': {
                do {
                    cout << endl;
                    cout << "-- BUCKETING -- " << endl;
                    cout << "1. Generate number of random key/value pairs" << endl;
                    cout << "2. Enter key/value pair manually" << endl;
                    cout << "3. Delete from key/value pair" << endl;
                    cout << "4. Print the bucket" << endl;
                    cout << "0. Exit" << endl;
                    cout << "Selection: ";
                    cin >> opt;
                    cout << endl;
                    switch (opt) {
                        case 1: {
                            int no;
                            int key;
                            int val;
                            cout << "Enter how many key/value pairs to generate: ";
                            cin >> no;
                            for (int i= 0; i < no; i++) {
                                key = rand()%100;
                                val = rand()%100;
                                cout << "Key: " << key << "\t Value: " << val << endl;
                                b->insert_(key, val);
                            }
                            break;
                        }
                        case 2: {
                            char yesNo;
                            do {
                                int key;
                                int value;
                                // insert code here...
                                cout << "Enter a key: ";
                                cin >> key;
                                cout << "Enter a value greater than 0: ";
                                cin >> value;
                                b->insert_(key, value);
                                cout << "Add another pair? (y/n): ";
                                cin >> yesNo;
                            } while (yesNo != 'n');
                            break;
                        }
                            
                        case 3: {
                            int key;
                            int value;
                            // insert code here...
                            cout << "Enter a key: ";
                            cin >> key;
                            cout << "Enter a value to delete: ";
                            cin >> value;
                            b->delete_(key, value);
                            break;
                        }
                        case 4: {
                            b->display();
                            break;
                        }
                            
                        default: {
                            break;
                        }
                            
                    }
                } while (opt != 0);
                continue;
            }
                
            case 'C':
            case 'c': {
                do {
                    cout << endl;
                    cout << "-- CHAINING --" << endl;
                    cout << "1. Generate number of random key/value pairs" << endl;
                    cout << "2. Enter key/value pair" << endl;
                    cout << "3. Delete from key/value pair" << endl;
                    cout << "4. Print the linked list" << endl;
                    cout << "0. Exit" << endl;
                    cout << "Select an option: ";
                    cin >> opt;
                    cout << endl;
                    switch (opt) {
                        case 1: {
                            int no;
                            int key;
                            int val;
                            cout << "Enter how many key/value pairs to generate: ";
                            cin >> no;
                            for (int i= 0; i < no; i++) {
                                key = rand()%100;
                                val = rand()%100;
                                cout << "Key: " << key << "\t Value: " << val << endl;
                                c->insert_(key, val);
                            }
                            break;
                        }
                        case 2: {
                            char yesNo;
                            do {
                                int key;
                                int value;
                                // insert code here...
                                cout << "Enter a key: ";
                                cin >> key;
                                cout << "Enter a value greater than 0: ";
                                cin >> value;
                                c->insert_(key, value);
                                cout << "Add another pair? (y/n): ";
                                cin >> yesNo;
                            } while (yesNo != 'n');
                            break;
                        }
                        case 3: {
                            int key;
                            int value;
                            // insert code here...
                            cout << "Enter a key: ";
                            cin >> key;
                            cout << "Enter a value to delete: ";
                            cin >> value;
                            c->delete_(key, value);
                            break;
                        }
                        case 4: {
                            c->display();
                            break;
                        }
                            
                        default: {
                            break;
                        }
                            
                    }
                } while (opt != 0);
                continue;
            }
        }
    } while (ht != 'X');
    return 0;
}

