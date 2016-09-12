//
//  main.cpp
//  CPPLinkedList
//  Created by William Rosmon on 9/4/16.
//  Copyright © 2016 William Rosmon. All rights reserved.
//

#include <ctime>
#include <iostream>
#include <sstream>
#include <cstdlib>


struct node {
    int number;
    node *next;
};

int main(int argc, const char * argv[]) {

    node *head = 0;
    node *tail = 0;
    int size = 0;
    srand(time(NULL));
    
    int numEntries = atoi(argv[1]);
    int searchNumber = atoi(argv[2]);
    head = new node;
        
    //std::cout << "Linked List has " << size << " entries";
    //std::cout << std::endl << "Enter number of entries: ";
    //std::cin >> numEntries;
    
    for(int i = 0; i < numEntries; i++) {
        if(size == 0) {
            head->number = rand() % 100;
            size++;
            head->next = new node;
            tail = head->next;
        } else {
            tail->number = rand() % 100;
            tail->next = new node;
            tail = tail->next;
            size++;
        }
    }
    clock_t begin, end;
    begin = clock();
    bool found = false;
    node *tempNode = head;
    for(int i = 0; i < size && !found; i++) {
        if(tempNode->number == searchNumber) {
            std::cout << "The number was found!";
            found = true;
        }
        tempNode = tempNode->next;
        //std::cout << tempNode->number << std::endl;
    }
    if(!found) {
        std::cout << "The number was not found";
    }
    end = clock();
    std::cout << (double (end - begin) / CLOCKS_PER_SEC);
    return 0;
}
