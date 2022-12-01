#include <iostream>
#include <algorithm>
#include <iterator>
#include <chrono>
#include <vector>
#include <fstream>

using namespace std;
using namespace chrono;

// int solve (vector<int>& list1, vector<int>& list2) {
//     const int length1 = list1.size();
//     const int length2 = list2.size();
//     int result1[length1] = {};
//     int result2[length2] = {};

//     // Initialise arrays with 1, minimal stack is from every element equal to 1
//     fill(result1, result1 + length1, 1);
//     fill(result2, result2 + length2, 1);


//     // Check first list
//     for (int i = 1; i < length1; i++) {
//         for (int j = 0; j < i; j++) 
//             if (list1[j] > list1[i] && result1[j] + 1 > result1[i]) {
//                 result1[i] = result1[j] + 1;
//             }
//     }

//     // Continue on the second
//     for (int i = 0; i < length2; i++) {
//         // Compare with first list elements
//         for (int j = 0; j < length1; j++) 
//             if (list1[j] > list2[i] && result1[j] + 1 > result2[i]) {
//                 result2[i] = result1[j] + 1;
//             }
//         // Compare with second list elements
//         for (int j = 0; j < i; j++) 
//             if (list2[j] > list2[i] && result2[j] + 1 > result2[i]) {
//                 result2[i] = result2[j] + 1;
//             }
//     }
//     int const* max1 = max_element(result1, result1+length1);
//     int const* max2 = max_element(result2, result2+length2);
//     return *max1 > *max2 ? *max1 : *max2;
// }

// Binary search (note boundaries in the caller)
int CeilIndex(vector<int>& v, int l, int r, int key)
{
    while (r - l > 1) {
        int m = l + (r - l) / 2;
        if (v[m] <= key)
            r = m;
        else
            l = m;
    }
    return r;
}
 
int solve(vector<int>& list1)
{
    if (list1.empty())
        return 0;
 
    vector<int> tail(list1.size(), 0);
    int length = 1; // always points empty slot in tail
 
    tail[0] = list1[0];
    for (size_t i = 1; i < list1.size(); i++) {
        // new smallest value
        if (list1[i] > tail[0])
            tail[0] = list1[i];
 
        // v[i] extends largest subsequence
        else if (list1[i] < tail[length - 1])
            tail[length++] = list1[i];
 
        // v[i] will become end candidate of an existing
        // subsequence or Throw away larger elements in all
        // LIS, to make room for upcoming greater elements
        // than v[i] (and also, v[i] would have already
        // appeared in one of LIS, identify the location
        // and replace it)
        else
            tail[CeilIndex(tail, -1, length - 1, list1[i])] = list1[i];
    }
    return length;
}

int get_longest_sequence (vector<int>& list1, vector<int>& list2){
    // int val1 = solve(list1, list2);
    // int val2 = solve(list2, list1);

    vector<int> temp = list1;
    list1.insert(list1.end(), list2.begin(), list2.end());
    list2.insert(list2.end(), temp.begin(), temp.end());
    int val1 = solve(list1);
    int val2 = solve(list2);
    return val1 > val2 ? val1 : val2;
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
    vector<int> list1;
    vector<int> list2;

    // Active code switcher: add or take the first next slash to toggle code
    //*     
    string filename = "C:\\Users\\DiunR\\OneDrive\\Radboud\\And\\AnD-Project2\\examples\\29.in";
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
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;
    return 0;
}