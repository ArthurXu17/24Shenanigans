#include <iostream>
#include "solver.cc"
#include "cardGenerator.cc"
#include <unordered_set>
#include <ctime>
#include <string>
#include <fstream>

string getSolutionString(vector<int>& nums, char op1, char op2, char op3, vector<int> perms, int parenthesis) {
    /*
    - (a # b) # (c # d)
    - ((a # b) # c) # d
    - (a # (b # c)) # d)
    - a # ((b # c) # d)
    - a # (b # (c # d))
    */
    string a = to_string(nums[perms[0]]);
    string b = to_string(nums[perms[1]]);
    string c = to_string(nums[perms[2]]);
    string d = to_string(nums[perms[3]]);

    if (parenthesis == 1) {
        return "(" + a + " " + op1 + " " + b + ") " + op2 + " (" + c + " " + op3 + " " + d + ")";
    } else if (parenthesis == 2) {
        return "((" + a + " " + op1 + " " + b + ") " + op2 + " " + c + ") " + op3 + " " + d;
    } else if (parenthesis == 3) {
        return "(" + a + " " + op1 + " (" + b + " " + op2 + " " + c + ")) " + op3 + " " + d;
    } else if (parenthesis == 4) {
        return a + " " + op1 + " ((" + b + " " + op2 + " " + c + ") " + op3 + " " + d + ")";
    } else if (parenthesis == 5) {
        return a + " " + op1 + " (" + b + " " + op2 + " (" + c + " " + op3 + " " + d + "))";
    } else {
        return "Error";
    }
}

void solveBase24() {
    DoubleSolver solver = DoubleSolver();
    CardGenerator generator = CardGenerator(1,13,4);
    auto result = generator.allSets();
    cout<<result.size()<<endl;
    std::ofstream outputFile;
    outputFile.open("base24Results.csv");
    int totalSuccess = 0;
    for (auto & vec : result) {
        outputFile<<vec[0]<<","<<vec[1]<<","<<vec[2]<<","<<vec[3]<<",";
        if (solver.judgePoint24(vec)) {
            totalSuccess++;
            outputFile<<getSolutionString(vec, 
                                          solver.get_op1(), 
                                          solver.get_op2(),
                                          solver.get_op3(),
                                          solver.get_perm(),
                                          solver.get_parenthesis())<<"\n";
        } else {
            outputFile<<"Not possible :(\n";
        }
    }
    cout<<totalSuccess<<endl;
    outputFile.close();
}

int main() {
    solveBase24();
}