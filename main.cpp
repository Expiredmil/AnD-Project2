#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>

using namespace std;
using namespace chrono;

// Binary search (note boundaries in the caller)
int CeilIndex(vector<int>& tail, int  length, int range, int& key)
{
    while (range - length > 1) {
        int x = length + (range - length) / 2;
        if (tail[x] <= key) 
            range = x; // Found an end tail that satisfies
        else
            length = x; // Look at the rest of the tail list
    }
    return range;
}

vector<int> merge_tail (vector<int>& tail1, vector<int>& tail2) {
    int len1 = tail1.size();
    int len2 = tail2.size();
    int range = len1 > len2 ? len2 : len1;
    vector<int> result = len1 > len2 ? tail1 : tail2; // Copy the longest tail vector
    
    // Compare every element in range and keep the bigger element
    for (int i = 0; i < range; i++) {
        if (tail1[i] > tail2[i]) 
            result[i] = tail1[i];
        else 
            result[i] = tail2[i];
    }
    return result;
}

vector<int> try_add_tail(vector<vector<vector<int>>>& tail, int n, int m, int& value) {
    vector<int> result = tail[n][m]; // Copy of tail vector at indices n and m
    int empty = tail[n][m].size();  // Index of empty index

    // New smallest value
    if (value > result[0])
        result[0] = value;
    // Value becomes a new end tail
    else if (value < result.back())
        result.push_back(value);
    // Value will become end candidate of an existing
    // subsequence or Throw away larger elements in all
    // LIS, to make room for upcoming greater elements
    // than value
    else 
        result[CeilIndex(result, -1, empty, value)] = value;
    return result;
}

int get_longest_sequence (vector<int>& list1, vector<int>& list2){
    int N = list1.size(); // Amount of pallets in stream 1 
    int M = list2.size(); // Amount of pallets in stream 2

    // Initialise matrix with vector containing 0
    vector<int> temp = {0};
    vector<vector<int>> temp2 (M, temp);
    vector<vector<vector<int>>> tail(N, temp2); // 2d matrix of N * M containing tail lists

    // Algorithm: at every cell in the matrix,
    // generate the tail lists from the top and/or left tail lists
    for (int n = 0; n < N; ++n) {
        for (int m = 0; m < M; ++m) {
            // Top left corner
            if (n == 0 && m == 0)
                continue;
            // Left most column
            if (n == 0) {
                auto top = try_add_tail(tail, n, m-1, list2[m]);
                tail[n][m] = top;
            }
            // Top row
            else if (m == 0) {
                auto left = try_add_tail(tail, n-1, m, list1[n]);
                tail[n][m] = left;
            }
            // The rest
            else {
                auto top = try_add_tail(tail, n, m-1, list2[m]);
                auto left = try_add_tail(tail, n-1, m, list1[n]);
                auto merge = merge_tail(top, left);
                tail[n][m] = merge;
            }
        }
    } 
    return tail[N-1][M-1].size();
}

void get_from_file (string& file, int& N, int& M, vector<int>& list1, vector<int>& list2) {
    ifstream infile;
    infile.open(file);
    if (infile.is_open()) {
        string value;

        // Get the lengths N and M
        infile >> value;
        N = stoi(value.c_str());
        infile >> value;
        M = stoi(value.c_str());

        // Make the first list
        for (int i = 0; i < N; i++) {
            infile >> value;
            list1.push_back(stoi(value.c_str()));            
        }
        // Make the second list
        for (int i = 0; i < M; i++) {
            infile >> value;
            list2.push_back(stoi(value.c_str()));            
        }

        infile.close();
        if (infile.is_open())
            cout << "Couldn't close the file!" << endl;
    }
    else
        cout << "Couldn't open file!" << endl;
}

int main()
{
    int N, M;
    vector<int> list1 = {0}; // Stream 1
    vector<int> list2 = {0}; // Stream 2
    // Active code switcher: add or remove the first slash to toggle code
    //*     
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
    /*/  
    string filename = "C:\\Users\\DiunR\\OneDrive\\Radboud\\And\\AnD-Project2\\examples\\27.in";
    get_from_file(filename, N, M, list1, list2);
    //*/ 

    // Get starting timepoint
    // auto start = high_resolution_clock::now();

    cout << get_longest_sequence(list1,list2) << endl;

    // Get ending timepoint
    // auto stop = high_resolution_clock::now();

    // Calculate duraction with the start time and end time
    // auto duration = duration_cast<milliseconds>(stop - start);
    // cout << "Time taken by function: "
    //      << duration.count() << " milliseconds" << endl;
    return 0;
}