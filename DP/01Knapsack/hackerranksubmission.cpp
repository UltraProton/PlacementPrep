//https://www.hackerrank.com/challenges/unbounded-knapsack/problem


#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

int zero_one_knapsack(vector<int> &weights, int W, int curr_idx){
    if(curr_idx>=weights.size() || W==0){
        return 0;
    }

    //* If the weight at curr_idx can't be included in the knapsack then we have only one option to ignore it
    if(weights[curr_idx] > W){
        return zero_one_knapsack(weights,W,curr_idx+1);
    }

    else{
        //include the weight at curr_idx in the knapsack
        int include_ans= weights[curr_idx]+ zero_one_knapsack(weights,W-weights[curr_idx],curr_idx);
        
        //* Even though we can include it but we want to get the ans without considering the current weight and its value
        //* because we may get a better value later if don't decrease our weight by including the value and weight in current
        //*call
        int exclude_ans= zero_one_knapsack(weights,W,curr_idx+1);

        return max(include_ans,exclude_ans);
    }

}

// Complete the unboundedKnapsack function below.
int unboundedKnapsack(int k, vector<int> arr) {

    return zero_one_knapsack(arr,k,0);

}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string nk_temp;
    getline(cin, nk_temp);

    vector<string> nk = split_string(nk_temp);

    int n = stoi(nk[0]);

    int k = stoi(nk[1]);

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split_string(arr_temp_temp);

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        int arr_item = stoi(arr_temp[i]);

        arr[i] = arr_item;
    }

    int result = unboundedKnapsack(k, arr);

    std::cout<<result<<endl;

    fout << result << "\n";

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
