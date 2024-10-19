#include <iostream>
#include "solver.cc"
#include "cardGenerator.cc"
#include "multisubsetGenerator.cc"
#include <unordered_set>
#include <ctime>
#include <string>
#include <fstream>

typedef vector<vector<vector<vector<string>>>> map24;

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

vector<int> createStandardDeck(bool withJoker) {
    vector<int> deck;
    for (int i = 1; i <= 13; i++) {
        for (int j = 1; j <= 4; j++) {
            deck.push_back(i);
        }
    }
    if (withJoker) {
        deck.push_back(14);
        deck.push_back(14);
    }
    return deck;
}

void solveBase24(map24& baseSolutions) {
    vector<int> deck = createStandardDeck(true);
    DoubleSolver solver = DoubleSolver();
    MultisetGenerator generator = MultisetGenerator(deck,4);
    auto result = generator.allMultisets();
    cout<<result.size()<<endl;
    std::ofstream outputFile;
    outputFile.open("base24Results.csv");
    int totalSuccess = 0;
    for (auto & vec : result) {
        outputFile<<vec[0]<<","<<vec[1]<<","<<vec[2]<<","<<vec[3]<<",";
        if (solver.judgePoint24(vec)) {
            totalSuccess++;
            string solutionString = getSolutionString(vec, 
                                                      solver.get_op1(), 
                                                      solver.get_op2(),
                                                      solver.get_op3(),
                                                      solver.get_perm(),
                                                      solver.get_parenthesis());
            outputFile<<solutionString<<"\n";
            baseSolutions[vec[0]][vec[1]][vec[2]][vec[3]] = solutionString;
        } else {
            outputFile<<"Not possible :(\n";
        }
    }
    cout<<totalSuccess<<endl;
    outputFile.close();
}

unordered_set<int> convertVectorToSet(vector<int>& list) {
    return unordered_set<int>(list.begin(), list.end());
}

void solve8Choose4Style24(map24& baseSolutions) {
    // all subsets of 0 through 7
    vector<int> indices = {0,1,2,3,4,5,6,7};
    MultisetGenerator subsetGen = MultisetGenerator(indices, 4);
    vector<vector<int>> allSubsetsAsLists = subsetGen.allMultisets();
    /*vector<unordered_set<int>> allSubsets;
    transform(
        allSubsetsAsLists.begin(),
        allSubsetsAsLists.end(),
        allSubsets.begin(),
        convertVectorToSet
    );*/

    // all choices of 8 cards from deck
    vector<int> deck = createStandardDeck(true);
    DoubleSolver solver = DoubleSolver();
    MultisetGenerator generator = MultisetGenerator(deck,8);
    vector<vector<int>> result = generator.allMultisets();
    cout<<result.size()<<endl;
    // solve
    std::ofstream outputFile;
    outputFile.open("8Choose4Style24Results.csv");
    int totalSuccess = 0;
    int index = 0;
    for (auto & vec : result) {
        outputFile<<vec[0]<<","<<vec[1]<<","<<vec[2]<<","<<vec[3]<<","<<vec[4]<<","<<vec[5]<<","<<vec[6]<<","<<vec[7]<<",";
        if (index % 1000 == 0) {
            cout<<index<<endl;
        }
        bool hasSolution = false;
        // check all possible choices of partition
        for (auto & indicesSubset : allSubsetsAsLists) {
            vector<int> set1;
            vector<int> set2;
            for (int i = 0; i < 8; i++) {
                if (find(indicesSubset.begin(), indicesSubset.end(), i) != indicesSubset.end()) {
                    set1.push_back(vec[i]);
                } else {
                    set2.push_back(vec[i]);
                }
            }

            // set1 and set2 are sorted indices of bipartition of cards
            string solution1 = baseSolutions[set1[0]][set1[1]][set1[2]][set1[3]];
            string solution2 = baseSolutions[set2[0]][set2[1]][set2[2]][set2[3]];
            if (solution1 != "" && solution2 != "") {
                outputFile<<set1[0]<<" "<<set1[1]<<" "<<set1[2]<<" "<<set1[3]<<",";
                outputFile<<set2[0]<<" "<<set2[1]<<" "<<set2[2]<<" "<<set2[3]<<",";
                outputFile<<solution1<<","<<solution2<<"\n";
                totalSuccess++;
                hasSolution = true;
                break;
            } 
        }
        if (!hasSolution) {
            outputFile<<"No Solution :(\n"<<endl;
        }
        index++;
    }
    outputFile.close();
    cout<<"Total Hands: "<<result.size()<<endl;
    cout<<"Total Success: "<<totalSuccess<<endl;
}

int main() {
    map24 baseSolutions(15, vector<vector<vector<string>>>(
        15, vector<vector<string>>(
        15, vector<string>(15, ""))));

    solveBase24(baseSolutions);
    solve8Choose4Style24(baseSolutions);
}