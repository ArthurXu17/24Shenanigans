#include<iostream>
#include <cassert>
#include <math.h>
#include <vector>

using namespace std;

class DoubleSolver {
    private:
        const char PLUS = '+';
        const char MINUS = '-';
        const char MULT = '*';
        const char DIVIDE = '/';
        const int GOAL = 24;
        const double ERROR = 0.0001;

        double evaluate(double a, double b, char op) {
            if (op == PLUS) {
                return a + b;
            } else if (op == MINUS) {
                return a - b;
            } else if (op == MULT) {
                return a * b;
            } else if (op == DIVIDE) {
                return a / b;
            } else {
                assert(false);
                return 0;
            }
        }

        bool resultValid(double result) {
            return fabs(result - GOAL) < ERROR;
        }

        bool checkAllEvaluations(int a, int b, int c, int d, char op1, char op2, char op3) {
            // (a # b) # (c # d)
            double result1 = evaluate(a,b,op1);
            double result2 = evaluate(c,d,op3);
            double result = evaluate(result1, result2, op2);
            if (resultValid(result)) {
                return true;
            }

            // ((a # b) # c) # d
            result1 = evaluate(a,b,op1);
            result2 = evaluate(result1,c,op2);
            result = evaluate(result2, d, op3);
            if (resultValid(result)) {
                return true;
            }

            // (a # (b # c)) # d)
            result1 = evaluate(b,c,op2);
            result2 = evaluate(a,result1,op1);
            result = evaluate(result2, d, op3);
            if (resultValid(result)) {
                return true;
            }

            // a # ((b # c) # d)
            result1 = evaluate(b,c,op2);
            result2 = evaluate(result1,d,op3);
            result = evaluate(a, result2, op1);
            if (resultValid(result)) {
                return true;
            }

            // a # (b # (c # d))
            result1 = evaluate(c,d,op3);
            result2 = evaluate(b,result1,op2);
            result = evaluate(a, result2, op1);
            if (resultValid(result)) {
                return true;
            }
            return false;
        }

        bool solve(vector<double>& cards) {
            /*
            Consider all permutations of the cards (24)
            Consider all choices of binary operations (64)
            Consider all parenthesis orders (5)
            - (a # b) # (c # d)
            - ((a # b) # c) # d
            - (a # (b # c)) # d)
            - a # ((b # c) # d)
            - a # (b # (c # d))
            */
            vector<vector<int>> perms = {
                {0, 1, 2, 3},
                {0, 1, 3, 2},
                {0, 2, 1, 3},
                {0, 2, 3, 1},
                {0, 3, 1, 2},
                {0, 3, 2, 1},
                {1, 0, 2, 3},
                {1, 0, 3, 2},
                {1, 2, 0, 3},
                {1, 2, 3, 0},
                {1, 3, 0, 2},
                {1, 3, 2, 0},
                {2, 0, 1, 3},
                {2, 0, 3, 1},
                {2, 1, 0, 3},
                {2, 1, 3, 0},
                {2, 3, 0, 1},
                {2, 3, 1, 0},
                {3, 0, 1, 2},
                {3, 0, 2, 1},
                {3, 1, 0, 2},
                {3, 1, 2, 0},
                {3, 2, 0, 1},
                {3, 2, 1, 0}
            };
            vector<char> ops = {PLUS, MINUS, MULT, DIVIDE};
            // for each perm
            for (const auto & perm : perms) {
                double a = cards[perm[0]];
                double b = cards[perm[1]];
                double c = cards[perm[2]];
                double d = cards[perm[3]];
                for (const auto & op1 : ops) {
                    for (const auto & op2 : ops) {
                        for (const auto & op3 : ops) {
                            if (checkAllEvaluations(a,b,c,d,op1,op2,op3)) {
                                return true;
                            }
                        }
                    }
                }
            }
            return false;
        }
    public:
        bool judgePoint24(vector<int> cards) {
            std::vector<double> doubleVec(cards.begin(), cards.end());
            return solve(doubleVec);
        }
};