/*
 *  回溯法
 * */
#include <iostream>
#include <vector>

using namespace std;

void Combination_helper(vector<int> array, int begin, int &current, int target, vector<int>&path) {
    if (begin >= array.size())
        return;
    current += array[begin];
    path.push_back(array[begin]);
    if (current == target)
    {
        for (int i = 0; i < path.size(); i++)
            cout << path[i]<<' ';
        cout << endl;
    }
    Combination_helper(array, begin + 1, current, target, path);
    path.pop_back();
    current -= array[begin];

    for (int j = begin + 1; j < array.size();) {
        if (array[j] == array[begin])
            j++;
        else
            break;
    }
    Combination_helper(array, j, current, target, path);

}
int main() {
    vector<int> array({1,2,2,3,4,4,5, 5, 6, 6, 7 });
    
    cout<<"origin array: ";
    for(int i = 0; i < array.size(); i++) {
        cout<<array[i]<<' ';
    }
    cout<<endl;
    vector<int> path;
    int current = 0;
    Combination_helper(array, 0, current, 10, path);
    return 0;
}
