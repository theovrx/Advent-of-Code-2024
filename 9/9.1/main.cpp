#include <iostream>
#include <string>
#include <fstream>
#include <list>

std::string data;

void loadData(){
    std::ifstream file("../input.txt");
    getline(file, data);
}

int ctoi(char number){
    if(int(number) < int('0') || int('9') < int(number)){
        std::cout << "ERROR! Entry is not a number.\n";
        return 0;
    }
    return int(number) - int('0');
}

std::list<int> addElNTimes(int number, int n, std::list<int> list){
    for(int i = 0; i < n; i++) list.push_back(number);
    return list;
}

std::list<int> computeDisk(){
    std::list<int> list;
    list = addElNTimes(0, ctoi(data[0]), list);

    for(int i = 0; i < (data.length()-1)/2; i++){
        list = addElNTimes(-1, ctoi(data[2*i+1]), list);
        list = addElNTimes(i+1, ctoi(data[2*i+2]), list);
    }
    return list;
}

std::list<int> arrangeStorage(std::list<int> disk){
    auto it = disk.begin();

    while (it != disk.end()) {

        if (*it == -1) {
            
            *it = disk.back();
            disk.pop_back();

            while (!disk.empty() && disk.back() == -1) disk.pop_back();

        } 

        else ++it;
    }

    return disk;
}

unsigned long long computeChecksum(std::list<int> disk){
    auto it = disk.begin();
    long index = 0;
    unsigned long long sum = 0;

    while(it != disk.end()){
        sum += index*(*it);
        ++index; ++it;
    }

    return sum;
}


int main(){
    std::list<int> disk;
    loadData();
    disk = computeDisk();
    disk = arrangeStorage(disk);
    std::cout << "Count: " << computeChecksum(disk) << '\n';
    return 0;
}