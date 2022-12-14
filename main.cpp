#include <iostream>
#include <algorithm>
#include <iterator>
#include <chrono>
#include <vector>
#include <fstream>

using namespace std;
using namespace chrono;

// Binary search (note boundaries in the caller)
int CeilIndex(vector<vector<vector<int>>>& tail, int n, int m, int length, int range, int key)
{
    while (range - length > 1) {
        int x = length + (range - length) / 2;
        if (tail[n][m][x] <= key)
            range = x;
        else
            length = x;
    }
    return range;
}

vector<int> merge_tail (vector<int>& tail1, vector<int>& tail2) {
    int len1 = tail1.size();
    int len2 = tail2.size();
    int range = len1 > len2 ? len2 : len1;
    vector<int> result = len1 > len2 ? tail1 : tail2;
    
    for (int i = 0; i < range; i++) {
        if (tail1[i] > tail2[i]) 
            result[i] = tail1[i];
        else 
            result[i] = tail2[i];
    }
    return result;
}

vector<int> add_tail(vector<vector<vector<int>>>& tail, int n, int m, int& value) {
    vector<int> result = tail[n][m];
    int empty = tail[n][m].size();

    // new smallest value
    if (value > result[0])
        result[0] = value;
    // v[i] extends largest subsequence
    else if (value < result.back())
        result.push_back(value);
    // v[i] will become end candidate of an existing
    // subsequence or Throw away larger elements in all
    // LIS, to make room for upcoming greater elements
    // than v[i] (and also, v[i] would have already
    // appeared in one of LIS, identify the location
    // and replace it)
    else
        result[CeilIndex(tail, n, m, -1, empty, value)] = value;
    return result;
}

int get_longest_sequence (vector<int>& list1, vector<int>& list2){
    int N = list1.size();
    int M = list2.size();

    // Initialise matrix with vector containing 0
    vector<int> temp = {0};
    vector<vector<int>> temp2 (M, temp);
    vector<vector<vector<int>>> tail(N, temp2);

    for (int n = 0; n < N; ++n) {
        for (int m = 0; m < M; ++m) {
            if (n == 0 && m == 0)
                continue;
            if (n == 0) {
                auto top = add_tail(tail, n, m-1, list2[m]);
                tail[n][m] = top;
            }
            else if (m == 0) {
                auto left = add_tail(tail, n-1, m, list1[n]);
                tail[n][m] = left;
            }
            else {
                auto top = add_tail(tail, n, m-1, list2[m]);
                auto left = add_tail(tail, n-1, m, list1[n]);
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
    vector<int> list1 = {0};
    vector<int> list2 = {0};
    // Active code switcher: add or take the first next slash to toggle code
    /*     
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
    string filename = "C:\\Users\\DiunR\\OneDrive\\Radboud\\And\\AnD-Project2\\examples\\29.in";
    get_from_file(filename, N, M, list1, list2);
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