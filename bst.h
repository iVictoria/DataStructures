// Victoria Castillo
// 

#include <iostream>
#include <iomanip> 
#include <math.h>  
using namespace std;

template <typename T>
class BST {

	struct Node {
		T data_;
		Node* left_;
		Node* right_;
		Node(const T& data = T{}, Node* left = nullptr, Node* right = nullptr) {
			data_ = data;
			left_ = left;
			right_ = right;
		}
	};

	Node* root_;

	void treeLevel(Node* node, int level, int l, int depth, int low, int high, Node* tree) {

		if (node == nullptr)
			return;
		else if (level == 0) {
			
			tree[(high + low) / 2].data_ = node->data_;
			tree[(high + low) / 2].left_ = node->left_;
			tree[(high + low) / 2].right_ = node->right_;
		}
		else {
			treeLevel(node->left_, level - 1, l, depth, low, (high + low) / 2, tree);
			treeLevel(node->right_, level - 1, l, depth, ((high + low) / 2) + 1, high, tree);

		}
	}



	int maxDepth(Node* node) {

		int depth = 0;
		int leftDepth = 0;
		int rightDepth = 0;

		if (node != nullptr) {

			leftDepth = maxDepth(node->left_);
			rightDepth = maxDepth(node->right_);

			depth = (leftDepth > rightDepth) ? leftDepth + 1 : rightDepth + 1;

		}

		return depth;
	}

    /*************************************************************/
    /*                                                           */
    /*    Private Recursive Functions                            */
    /*                                                           */
    /*************************************************************/
    
    bool insertData(const T& data, Node*& subtree){
        bool rc = false;
        if (subtree == nullptr) {
            subtree = new Node(data);
            rc = true;
        }
        else if (data < subtree->data_){
            insertData(data, subtree->left_);
            rc = true;
        }
        else {
            insertData(data, subtree->right_);
            rc = true;
        }
        return rc;
    }
    
    bool exists(const T& data, Node*& subtree) {
        bool rc = false;
        
        if (subtree != nullptr) {
            if (data == subtree->data_) {
                rc = true;
            }
            else if (data < subtree->data_) {
                rc = exists(data, subtree->left_);
            }
            else {
                rc = exists(data, subtree->right_);
            }
        }
        
        return rc;
    }
    
    Node* minValueNode(Node*& subtree) {
        if (subtree->left_ == nullptr)
            return subtree;
        else
            return minValueNode(subtree->left_);
    }
    
    Node* removeData(const T& data, Node* subtree) {
        if (subtree == nullptr)
            return subtree;

        if (data < subtree->data_) {
            subtree->left_ = removeData(data, subtree->left_);
        }
        else if (data > subtree->data_)
            subtree->right_ = removeData(data, subtree->right_);
        else {
            if (subtree->left_ == nullptr) {
                if (subtree->right_ != nullptr) {
                    Node* temp = subtree->right_;
                    delete subtree;
                    return temp;
                } else return nullptr;
            } else if (subtree->right_ == nullptr) {
                if (subtree->left_ != nullptr) {
                    Node* temp = subtree->left_;
                    delete subtree;
                    return temp;
                } else return nullptr;
           }
            if (subtree->right_ != nullptr) {
                Node* temp = minValueNode(subtree->right_);
                subtree->data_ = temp->data_;
                subtree->right_ = removeData(temp->data_, subtree->right_);
            }
        }
        return subtree;
    }

    
    void printTreeInorder(const Node* subtree) const {
        if(subtree!=nullptr){
            printTreeInorder(subtree->left_);
            std::cout << subtree->data_ << " - ";
            printTreeInorder(subtree->right_);
        }
    }
    
    void printTreePreorder(const Node* subtree) const {
        if (subtree!=nullptr) {
            std::cout << subtree->data_ << " - ";
            printTreePreorder(subtree->left_);
            printTreePreorder(subtree->right_);
        }
    }
    
    void printTreePostorder(const Node* subtree) const {
        if (subtree != nullptr) {
            printTreePostorder(subtree->left_);
            printTreePostorder(subtree->right_);
            std::cout << subtree->data_ << " - ";
        }
    }
    
    
    int maxTreeValue(Node* node) {
        if (node->right_ == nullptr)
            return node->data_;
        return maxTreeValue(node->right_);
    }

public:
	//create empty BST
	BST() {
		root_ = nullptr;
	}

	bool isEmpty() {
		//implement this function
        if (root_ == nullptr)
            return true;
        else
            return false;
	}

	bool insertData(const T& value) {
		return insertData(value, root_);
	}


	bool exists(const T value) {
		return exists(value, root_);
	}

	//removes a node with value from tree
	bool removeData(const T& value) {
        if (isEmpty())
            return false;
        
        // special remove cases if root
        // if last node to delete is root
        if (root_->data_ == value && root_->right_ == nullptr && root_->left_ == nullptr) {
            root_ = nullptr;
            return true;
        }
        else { // if root only has one branch
            if (root_->data_ == value && root_->right_ == nullptr && root_->left_ != nullptr) {
                root_ = root_->left_;
                return true;
            }
            else if (root_->data_ == value && root_->left_ == nullptr && root_->right_ != nullptr) {
                root_ = root_->right_;
                return true;
            }
            else { // all other cases
                Node* rm = removeData(value, root_);
                if (rm != nullptr) {
                    return true;
                } else
                    return false;
            }
        }
	}

	void printTreeInorder() const {
        printTreeInorder(root_);
		std::cout << std::endl;
	}


    void printTreePreorder() const {
        //implement this function
        printTreePreorder(root_);
        std::cout << std::endl;
        
    }
    
    void printTreePostorder() const {
        //implement this function
        printTreePostorder(root_);
        std::cout << std::endl;
        
    }
    
    int treeDepth() {
        return maxDepth(root_);
	}

	int maxTreeValue() {
		return maxTreeValue(root_);
	}

	int numberOfDigits(int num) {
		int digits = 0;
		while (num) {
			num /= 10;
			digits++;
		}
		return digits;
	}

	void displayTree() {

		int maxDpth = maxDepth(root_) + 1;
		const int dim = (int)pow(2, maxDpth) + 1;
		int max, maxData = -1;

		Node* tree = new  Node[dim];

		if (root_ != nullptr) {


			int hIndex = (int)pow(2, maxDpth) - 1;
			int lIndex = 0;

			int valueBefore = 0;
			for (int i = 0; i < maxDpth; i++) {
				for (int i = 0; i < dim; i++) {

					tree[i].data_ = 0;
					tree[i].left_ = nullptr;
					tree[i].right_ = nullptr;
				}

				treeLevel(root_, i, i, maxDpth, 0, pow(2, maxDpth), tree);

				int digits = 0;

				for (int i = 0; i < dim; i++) {

					if (tree[i].data_ != 0) {

						digits = numberOfDigits(tree[i].data_);

						cout << tree[i].data_;
					}
					else {
						if (digits > 1)
							while (digits > 0) {
								digits--;
							}

						else {
							digits = 0;
							cout << " ";
						}
					}
				}

				cout << endl;


				int space = 0;

				digits = 1;

				for (int i = 0; i < dim; i++) {

					if (tree[i].data_ != 0) {

						digits = numberOfDigits(tree[i].data_);

						if (tree[i].left_ != nullptr && tree[i].right_ != nullptr) {
							cout << "/\\";
							digits -= 2;
						}
						else if (tree[i].left_ != nullptr) {
							cout << "/ ";
							digits -= 2;
						}
						else if (tree[i].right_ != nullptr) {
							cout << " \\";
							digits -= 2;
						}
						else {
							cout << "  ";
							digits -= 2;
						}


					}
					else {
						if (digits > 0) {
							if (digits > 1)
								while (digits > 0) {
									digits--;
									cout << " ";
								}

							else {
								digits = 1;
								cout << " ";
							}
						}
						else {
							digits++;
							if (digits == 0)
								digits = 1;

						}
					}
				}


				cout << endl;

			}
		}
		else {
			cout << "Tree is empty" << endl;
		}



	}

	~BST() {};
};


