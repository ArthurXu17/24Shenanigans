#include <vector>
#include <iostream>

using namespace std;

void printVector(vector<int>& vec) {
    for (auto & n : vec) {
        cout<<n<<" ";
    }
    cout<<endl;
}