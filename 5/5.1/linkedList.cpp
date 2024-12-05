#include "linkedList.h"
#include <iostream>
#include <vector>

class LinkedList{

    private:
        Node* firstNode;
        int length;

    public:

        LinkedList(int firstValue){
            firstNode = new Node();
            firstNode->value = firstValue;
            length = 1;
        }

        LinkedList(const LinkedList& other) {
            if (other.firstNode == nullptr) {
                firstNode = nullptr;
                length = 0;
                return;
            }

            firstNode = new Node();
            firstNode->value = other.firstNode->value;

            Node* currentNode = firstNode;
            Node* otherNode = other.firstNode->nextNode;

            while (otherNode != nullptr) {
                Node* newNode = new Node();
                newNode->value = otherNode->value;
                currentNode->nextNode = newNode;

                currentNode = newNode;
                otherNode = otherNode->nextNode;
            }

            currentNode->nextNode = nullptr;
            length = other.length;
        }

        ~LinkedList() {
            Node* currentNode = firstNode;
            while (currentNode != nullptr) {
                Node* nextNode = currentNode->nextNode;
                delete currentNode; 
                currentNode = nextNode; 
            }
        }

        void display(){
            Node* currentNode = firstNode;
            std::cout << currentNode->value;
            for(int i = 1; i < length; i++){
                currentNode = currentNode->nextNode;
                std::cout << " -> " << currentNode->value;
            }
            std::cout << '\n';
        }

        void addFirstNode(int value){
            Node* newNode = new Node();
            newNode->value = value;
            newNode->nextNode = firstNode;
            firstNode = newNode;
            length++;
        }

        void addLastNode(int value){
            Node* currentNode = firstNode;
            for(int i = 1; i < length; i++){
                currentNode = currentNode->nextNode;
            }

            Node* lastNode = currentNode;
            Node* newNode = new Node();
            newNode->value = value;
            lastNode->nextNode = newNode;
            length++;
        }

        void addNodeAtIndex(int value, int index){

            if (index == 0){
                this->addFirstNode(value);
                return;
            }

            Node* currentNode = firstNode;
            for(int i = 1; i < index; i++){
                currentNode = currentNode->nextNode;
            }

            Node* newNode = new Node();
            newNode->value = value;
            newNode->nextNode = currentNode->nextNode;
            currentNode->nextNode = newNode;
            length++;
        }

        int find(int value){

            if (firstNode->value == value) return 0;

            Node* currentNode = firstNode;
            for(int i = 1; i < length; i++){
                currentNode = currentNode->nextNode;
                if (currentNode->value == value) return i;
            }

            return -1;
        }

        int at(int index){

            if (index == 0) return firstNode->value;

            Node* currentNode = firstNode;

            for(int i = 0; i < index; i++){
                currentNode = currentNode->nextNode;
            }

            return currentNode->value;
        }

        int getLength(){return length;}

};

// int main(){

//     std::vector<LinkedList> list;
//     list.push_back(LinkedList(4));
//     list.at(0).addLastNode(5);
//     list.at(0).display();
//     std::cout << list.at(0).find(456) << '\n';
//     list.at(0).addNodeAtIndex(456, 0);
//     list.at(0).display();

//     return 0;
// }