//============================================================================
// Name        : LinkedList.cpp
// Author      : Jordan Davis
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Lab 3-3 Lists and Searching
//============================================================================

#include <algorithm>
#include <iostream>
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

//============================================================================
// Linked-List class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a linked-list.
 */
class LinkedList {

private:
    struct Node {
		Bid bid;     // Create a private bid instance
		Node* next;

		// default constructor
		Node() {
			next = nullptr;
		}

		// Another constructor to initiate with bid struct
		Node(Bid aBid) {
			bid = aBid;
			next = nullptr;
		}
	};

	Node* head; // Create a node for the head of the LinkedList
	Node* tail; // Create a node for the tail of the LinkedList
	int size = 0; // Create int variable to store size of LinkedList

public:
    LinkedList();
    virtual ~LinkedList();
    void Append(Bid bid);
    void Prepend(Bid bid);
    void PrintList();
    void Remove(string bidId);
    Bid Search(string bidId);
    int Size();
};

/**
 * Default constructor
 */
LinkedList::LinkedList() {
	// Inititiate an empty LinkedList with the head and tail not pointing to anything
    head = nullptr;
	tail = nullptr;
}

/**
 * Destructor
 */
LinkedList::~LinkedList() {
}

/**
 * Append a new bid to the end of the list
 */
void LinkedList::Append(Bid bid) {
    Node* node = new Node(bid); // Create Node struct instance with bid arggument

	if (head == nullptr) {      // If LinkedList is empty, add new node as beginning of LinkedList
		head = node;
	}
	else {                      // If LinkedList is not empty, add new node to end of list and having previous
		if (tail != nullptr) {  // tail's next pointer point to new node
			tail->next = node;
		}
	}
	tail = node;
	size++;                     // Increment size of linked list
}

/**
 * Prepend a new bid to the start of the list
 */
void LinkedList::Prepend(Bid bid) {
    Node* node = new Node(bid);
	if (head != nullptr) {         // If LinkedList is not empty, point new node's next pointer towards the current head node
		node->next = head;

	}
	head = node;
	size++;                        // Increment size of linked list
}

/**
 * Simple output of all bids in the list
 */
void LinkedList::PrintList() {
    Node* currentPtr = head;

	// Loop through list by each node location and print bid information that is stored at that location
	while (currentPtr != nullptr) {
		cout << currentPtr->bid.bidId << ": " << currentPtr->bid.title << " | "
			 << currentPtr->bid.amount << " | " << 	currentPtr->bid.fund << endl;
		currentPtr = currentPtr->next;
	}
}

/**
 * Remove a specified bid
 *
 * @param bidId The bid id to remove from the list
 */
void LinkedList::Remove(string bidId) {
    if (head != nullptr) {
		if (head->bid.bidId.compare(bidId) == 0) {// If LinkedList isn't empty and the head is the specified bid: Make the next bid the head
			Node* tempNode = head->next;
			delete head;
			head = tempNode;
		}
	}

	Node* currentPtr = head;

	    // Iterate through LinkedList, search for specified bid
		while (currentPtr->next != nullptr) {
			if (currentPtr->next->bid.bidId.compare(bidId) == 0) {
				Node* tempNode = currentPtr->next; // Create temporary node to hold node to be removed
				currentPtr->next = tempNode->next; // Assign node before to be removed node's pointer to node after to be removed node
				delete tempNode;                   // Delete tempNode to recover that memory space

				size--;                            // Decrement linked list size

				return;
			}
			currentPtr = currentPtr->next;
		}

}

/**
 * Search for the specified bidId
 *
 * @param bidId The bid id to search for
 */
Bid LinkedList::Search(string bidId) {
    Node* currentPtr = head;

    // Iterate through LinkedList, find specified bid, and return the location
	while (currentPtr != nullptr) {
		if (currentPtr->bid.bidId.compare(bidId) == 0) {
			return currentPtr->bid;
		}
		currentPtr = currentPtr->next;
	}
	Bid noBid;
	return noBid; // Return empty Bid struct to indicate that no bid with the specified Id was found
}

/**
 * Returns the current size (number of elements) in the list
 */
int LinkedList::Size() {
    return size;
}

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount
         << " | " << bid.fund << endl;
    return;
}

/**
 * Prompt user for bid information
 *
 * @return Bid struct containing the bid info
 */
Bid getBid() {
    Bid bid;

    cout << "Enter Id: ";
    cin.ignore();
    getline(cin, bid.bidId);

    cout << "Enter title: ";
    getline(cin, bid.title);

    cout << "Enter fund: ";
    cin >> bid.fund;

    cout << "Enter amount: ";
    cin.ignore();
    string strAmount;
    getline(cin, strAmount);
    bid.amount = strToDouble(strAmount, '$');

    return bid;
}

/**
 * Load a CSV file containing bids into a LinkedList
 *
 * @return a LinkedList containing all the bids read
 */
void loadBids(string csvPath, LinkedList *list) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser
    csv::Parser file = csv::Parser(csvPath);

    try {
        // loop to read rows of a CSV file
        for (int i = 0; i < file.rowCount(); i++) {

            // initialize a bid using data from current row (i)
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            // add this bid to the end
            list->Append(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
	str.erase(remove(str.begin(), str.end(), '\"'), str.end());  // Added two lines to take out commas and quote marks of larger
	str.erase(remove(str.begin(), str.end(), ','), str.end());   // bid amounts so that they would display amount instead of 0
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 *
 * @param arg[1] path to CSV file to load from (optional)
 * @param arg[2] the bid Id to use when searching the list (optional)
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, bidKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "98109";
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
        bidKey = "98109";
    }

    clock_t ticks;

    LinkedList bidList;

    Bid bid;

    int choice = 0;
    while (choice != 9) {
    	// Display menu to user each iteration of loop
        cout << "Menu:" << endl;
        cout << "  1. Enter a Bid" << endl;
        cout << "  2. Load Bids" << endl;
        cout << "  3. Display All Bids" << endl;
        cout << "  4. Find Bid" << endl;
        cout << "  5. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        // Process user choice from menu
        switch (choice) {
        case 1:
        	// Enter a bid - run getBid method to get user input, add to linked list, and display result to user
            bid = getBid();
            bidList.Append(bid);
            displayBid(bid);

            break;

        case 2:
        	// Load Bids - While keeping track of time, load bids from file by using loadBids method
            ticks = clock();

            loadBids(csvPath, &bidList);

            cout << bidList.Size() << " bids read" << endl;

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " milliseconds" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 3:
        	// Display All Bids - Display bids by using PrintList method
            bidList.PrintList();

            break;

        case 4:
        	// Find Bid - While keeping track of time, search list by using bidKey in the Search method. Display message
        	// if not found or bid info if found
            ticks = clock();

            bid = bidList.Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            }
            else {
            	cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 5:
        	// Remove Bid - Remove bid from list by using Remove method
            bidList.Remove(bidKey);

            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}
