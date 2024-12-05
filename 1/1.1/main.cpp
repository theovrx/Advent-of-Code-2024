#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

void selection_sort(int arr[1000]) {

    for (int i = 0; i < 999; i++) {

        int ind_min = i;
        
        for (int j = i + 1; j < 1000; j++) {
            if (arr[j] < arr[ind_min]) {
                ind_min = j;
            }
        }
        
        if (ind_min != i) {

            int temp = arr[i];
            arr[i] = arr[ind_min];
            arr[ind_min] = temp;
            
        }

    }

}

int main(){
    
    int list1[1000];
    int list2[1000];

    std::ifstream file("../input.txt");
    std::string line;
    int line_count = 0;

    while(std::getline(file, line)){
        
        int delimeter_pos = line.find("   ");
        list1[line_count] = std::stoi(line.substr(0, delimeter_pos));
        list2[line_count] = std::stoi(line.substr(delimeter_pos+3, delimeter_pos));
        line_count++;

    }

    selection_sort(list1);
    selection_sort(list2);

    int result = 0;
    for(int i = 0; i < 1000; i++) result += abs(list1[i] - list2[i]);

    std::cout << result << '\n';
    
    return 0;
}

// Need to sort the list then iterate through both list and find their difference

