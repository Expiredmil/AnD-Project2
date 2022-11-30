#include <iostream>
#include <array>
#include <chrono>
#include <vector>
#include <fstream>

using namespace std;
using namespace std::chrono;

int max_in_arrays (int arr1[], int size1, int arr2[], int size2) {
    int max = 0;
    int val = 0;

    // Check first array
    for (int i = 0; i < size1; i++) {
        val = arr1[i];
        if (val > max) 
            max = val;
    }

    // Check second array
    for (int i = 0; i < size2; i++) {
        val = arr2[i];
        if (val > max) 
            max = val;
    }

    return max;
}

int solve (vector<int>& list1, vector<int>& list2) {
    int length1 = list1.size();
    int length2 = list2.size();
    int result1[length1];
    int result2[length2];

    // Initialise arrays with 1, minimal stack is from every element equal to 1
    fill(result1, result1 + length1, 1);
    fill(result2, result2 + length2, 1);

    // Check first list
    for (int i = 1; i < length1; i++) {
        for (int j = 0; j < i; j++) {
            if (list1[j] > list1[i] && result1[j] + 1 > result1[i])
                result1[i] = result1[j] + 1;
        }
    }

    // Continue on the second
    for (int i = 0; i < length2; i++) {
        // Compare with first list elements
        for (int j = 0; j < length1; j++) {
            if (list1[j] > list2[i] && result1[j] + 1 > result2[i])
                result2[i] = result1[j] + 1;
        }
        // Compare with second list elements
        for (int j = 0; j < i; j++) {
            if (list2[j] > list2[i] && result2[j] + 1 > result2[i])
                result2[i] = result2[j] + 1;
        }
    }

    return max_in_arrays(result1, length1, result2, length2);
}


int get_longest_sequence (vector<int>& list1, vector<int>& list2){
    int val1 = solve(list1, list2);
    int val2 = solve(list2, list1);
    return val1 > val2 ? val1 : val2;
}

void get_from_file (string& file, int& N, int& M, vector<int>& list1, vector<int>& list2) {
    ifstream infile;
    infile.open(file);
    if (infile.is_open()) {
        string value;
        infile >> value;

        // Get the lengths N and M
        N = stoi(value.c_str());
        infile >> value;
        M = stoi(value.c_str());

        // Make the first list
        for (int i = 0; i < N; i++)
        {
            infile >> value;
            list1.push_back(stoi(value.c_str()));            
        }
        // Make the second list
        for (int i = 0; i < M; i++)
        {
            infile >> value;
            list2.push_back(stoi(value.c_str()));            
        }

        infile.close();
        if (infile.is_open())
            cout << "Couldn't close the file!" << endl;
    }
    else
        cout << "couldn't open file!" << endl;
}

int main()
{
    int N, M;
    vector<int> list1;
    vector<int> list2;

    // Active code switcher: add or take the first next slash to toggle code
    //*     
    string filename = "C:\\Users\\DiunR\\OneDrive\\Radboud\\And\\AnD-Project2\\examples\\2.in";
    get_from_file(filename, N, M, list1, list2);
    
    /*/  
    cin >> N >> M;
    int temp;
    for(int n = 0; n < N; n++){
        cin >> temp;
        list1.push_back(temp);
    }
    for(int m = 0; m < M; m++){
        cin >> temp;
        list2.push_back(temp);
    } 
    //*/ 

    // Get starting timepoint
    auto start = high_resolution_clock::now();

    cout << get_longest_sequence(list1,list2) << endl;
    // Get ending timepoint
    auto stop = high_resolution_clock::now();

    // Calculate duraction with the start time and end time
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Time taken by function: "
         << duration.count() << " milliseconds" << endl;
    return 0;
}