#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// A Node struct to keep track of nodes within the binary tree
struct Node {
    int num;
	Node* left;
	Node* right;

	// Default constructor
	Node() {
		left = nullptr;
		right = nullptr;
	}
    // Constructor initialized with bid
	Node(int x) : Node() {
		this->num = x;
	}
};

// BinaryTree class stores, implements, adds, and sorts elements
class BinaryTree {

private:
    Node* root;
    vector<int> elements;
    vector<Node*> tree;

    void addNode(Node* node, int x);
    void inOrder(Node* node);
    void preOrder(Node* node);
    void postOrder(Node* node);
    void levelOrder(Node* node);
    void printCurrentLevel(Node* root, int level);
    int height(Node* node);

public:
    BinaryTree();
    void InOrder();
    void Insert(int x);
    void PreOrder();
    void PostOrder();
    void LevelOrder();
};

/**
 * Constructor for new binary tree
 */
BinaryTree::BinaryTree() {
    // initialize housekeeping variables
	root = nullptr;
}

/**
 * Sorts binary tree through in-order traversal
 */
void BinaryTree::InOrder() {
	cout << "In-Order: ";
    this->inOrder(root);
    cout << endl;
}

/**
 * Sorts binary tree through pre-order traversal
 */
void BinaryTree::PreOrder() {
	cout << "Pre-Order: ";
    this->preOrder(root);
    cout << endl;
}

/**
 * Sorts binary tree through post-order traversal
 */
void BinaryTree::PostOrder() {
	cout << "Post-Order: ";
    this->postOrder(root);
    cout << endl;
}

/**
 * Sorts binary tree by level-order traversal
 */
void BinaryTree::LevelOrder() {
    cout << "Level-Order: ";
    this->levelOrder(root);
    cout << endl;
}

/**
 * Inserts new node into binary tree by calling addNode function
 * @param x value to be assigned to node
 */
void BinaryTree::Insert(int x) {
	if (root == nullptr) {
		root = new Node(x);
        elements.push_back(x);
        tree.push_back(root);
	}
	else {
		this->addNode(root, x);
	}
}

/**
 * Determines where new node should be added in tree, whether in left or right subtree
 * @param node - starts at root but iterates until at correct empty node
 * @param x value of integer to be assign to node
 */
void BinaryTree::addNode(Node* node, int x) {
	// Add to left subtree
	if (node->num > x) {
		if (node->left == nullptr) {
			node->left = new Node(x);
            elements.push_back(x);
            tree.push_back(node->left);
		}
		else {
			this->addNode(node->left, x);
		}
	}
	// Add to right subtree
	else {
		if (node->right == nullptr) {
			node->right = new Node(x);
            elements.push_back(x);
            tree.push_back(node->right);
		}
		else {
			this->addNode(node->right, x);
		}
	}
}

/**
 * Implements in-order traversal and prints nodes in that in-order order
 * @param node starts with root and then changes with each iteration
 */
void BinaryTree::inOrder(Node* node) {
    if (node != nullptr) {
		inOrder(node->left);
		cout << node->num << (node->num == *max_element(elements.begin(), elements.end()) ? "" : " ");
		inOrder(node->right);
   }
}

/**
 * Implements pre-order traversal and prints nodes in order of pre-order
 * @param node starts with root and thenn changes each iteration
 */
void BinaryTree::preOrder(Node* node) {
    vector<int> numbers;
    if (node != nullptr) {
        if (node != root) {
            cout << " ";
        }
        cout << node->num;

        preOrder(node->left);
        preOrder(node->right);
    }
}

/**
 * Implements post-order traversal and prints nodes in that order
 * @param node starts with root node and then changes each iteration
 */
void BinaryTree::postOrder(Node* node) {
    if (node != nullptr) {
        postOrder(node->left);
        postOrder(node->right);
        cout << node->num  << (node == root ? "" : " ");
    }
}

/**
 * Implements level-order traversal through calls to height printCurrentLevel
 * @param node - root node
 */
void BinaryTree::levelOrder(Node* node)
{
    int h = height(node);
    int i;
    for (i = 1; i <= h; i++)
        printCurrentLevel(node, i);
}

/**
 * Prints node on the current level of iteration
 * @param node starts with root node but changes each iteration
 * @param level current level of iteration
 */
void BinaryTree::printCurrentLevel(Node* node, int level) {
    if (node == nullptr) {
        return;
    }
    if (level == 1) {
        tree.pop_back();
        cout << node->num << (tree.size() == 0 ? "" : " ");
    }
    else if (level > 1) {
        printCurrentLevel(node->left, level - 1);
        printCurrentLevel(node->right, level - 1);
    }
}

/**
 * Compute the height of the binary tree
 * @param node of the root node
 * @return height of the tree
 */
int BinaryTree::height(Node* node) {
    if (node == nullptr)
        return 0;
    else {
        // Compute the height of each subtree
        int lheight = height(node->left);
        int rheight = height(node->right);

        // Use the larger one to assign height of tree
        if (lheight > rheight) {
            return (lheight + 1);
        }
        else {
            return (rheight + 1);
        }
    }
}


int main() {
    int n;
    cin >> n; cin.ignore();
    BinaryTree* bt;
    bt = new BinaryTree();
    for (int i = 0; i < n; i++) {
        int vi;
        cin >> vi; cin.ignore();
        bt->Insert(vi);
    }
    bt->PreOrder();
    bt->InOrder();
    bt->PostOrder();
    bt->LevelOrder();
}
