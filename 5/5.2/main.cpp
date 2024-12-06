#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "linkedList.cpp"

//Only reason why I used linked lists instead of vector is because I implemented it before realising it was useless 

std::vector<std::string> rules;
std::vector<std::string> updates;

void loadData(std::vector<std::string> &rules, std::vector<std::string> &updates){

    std::ifstream file("../input.txt");
    std::string line;
    bool isRule = true;

    while(getline(file, line)){

        if (line == ""){
            isRule = false;
            continue;
        }

        if (isRule) rules.push_back(line);
        else updates.push_back(line);

    }
}

bool isSequenceValid(LinkedList &sequence, std::vector<std::string> rules){

    for (std::string rule: rules){
            int sep = rule.find('|');
            int before = std::stoi(rule.substr(0,sep));
            int after = std::stoi(rule.substr(sep+1));

            int indBefore = sequence.find(before);
            int indAfter = sequence.find(after);

            if(
                indBefore != -1 && indAfter != -1 
                && indBefore > indAfter
            ){
                // Can be optimized by implementing a "replace" method. We would iterate the list only 2 times instead of 4.
                sequence.display();
                sequence.popAt(indBefore);
                sequence.addNodeAtIndex(after, indBefore);
                sequence.popAt(indAfter);
                sequence.addNodeAtIndex(before, indAfter);
                sequence.display();
                return false;
            }
            
    }

    return true;

}

int main(){

    loadData(rules, updates);

    int result = 0;

    for (std::string update: updates){

        // First element
        int index = update.find_first_of(",");
        LinkedList sequence(std::stoi(update.substr(0,index)));
        update = update.substr(index + 1);

        // Next elements
        while(update.find_first_of(',') != update.npos){
            index = update.find_first_of(',');
            sequence.addLastNode(std::stoi(update.substr(0,index)));
            update = update.substr(index + 1);
        }

        // Last element
        index = update.find_first_of(',');
        sequence.addLastNode(std::stoi(update.substr(0,index)));

        if(!isSequenceValid(sequence, rules)){
            while (!isSequenceValid(sequence, rules)) std::cout << "bip...\n";
            result += sequence.at((sequence.getLength()-1)/2);
        } 

    }

    std::cout << "The result is: " << result << '\n';

    return 0;
}