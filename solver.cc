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

        char success_op1 = PLUS;
        char success_op2 = PLUS;
        char success_op3 = PLUS;
        int success_parenthesis = 0;
        vector<int> success_perm = {};

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

        void setSuccessOp(char op1, char op2, char op3) {
            success_op1 = op1;
            success_op2 = op2;
            success_op3 = op3;
        }

        bool checkAllEvaluations(int a, int b, int c, int d, char op1, char op2, char op3) {
            // (a # b) # (c # d)
            double result1 = evaluate(a,b,op1);
            double result2 = evaluate(c,d,op3);
            double result = evaluate(result1, result2, op2);
            if (resultValid(result)) {
                success_parenthesis = 1;
                return true;
            }

            // ((a # b) # c) # d
            result1 = evaluate(a,b,op1);
            result2 = evaluate(result1,c,op2);
            result = evaluate(result2, d, op3);
            if (resultValid(result)) {
                success_parenthesis = 2;
                return true;
            }

            // (a # (b # c)) # d)
            result1 = evaluate(b,c,op2);
            result2 = evaluate(a,result1,op1);
            result = evaluate(result2, d, op3);
            if (resultValid(result)) {
                success_parenthesis = 3;
                return true;
            }

            // a # ((b # c) # d)
            result1 = evaluate(b,c,op2);
            result2 = evaluate(result1,d,op3);
            result = evaluate(a, result2, op1);
            if (resultValid(result)) {
                success_parenthesis = 4;
                return true;
            }

            // a # (b # (c # d))
            result1 = evaluate(c,d,op3);
            result2 = evaluate(b,result1,op2);
            result = evaluate(a, result2, op1);
            if (resultValid(result)) {
                success_parenthesis = 5;
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
                                setSuccessOp(op1,op2,op3);
                                success_perm = perm;
                                return true;
                            }
                        }
                    }
                }
            }
            return false;
        }
    public:
        char get_op1 () {
            return success_op1;
        }
        char get_op2 () {
            return success_op2;
        }
        char get_op3 () {
            return success_op3;
        }
        int get_parenthesis() {
            return success_parenthesis;
        }
        vector<int> get_perm() {
            return success_perm;
        }
        bool judgePoint24(vector<int> cards) {
            std::vector<double> doubleVec(cards.begin(), cards.end());
            return solve(doubleVec);
        }
};

class Fraction {
    int num;
    int den;
    public:
        Fraction(int a): num{a}, den{1} {}
        int get_num() const {
            return num;
        }
        int get_den() const {
            return den;
        }
        Fraction& operator+=(const Fraction& rhs)
        {
            int new_num = num * rhs.den + den * rhs.num;
            int new_den = den * rhs.den;
            num = new_num;
            den = new_den;
            return *this;
        }
        Fraction& operator-=(const Fraction& rhs)
        {
            int new_num = num * rhs.den - den * rhs.num;
            int new_den = den * rhs.den;
            num = new_num;
            den = new_den;
            return *this;
        }
        Fraction& operator*=(const Fraction& rhs)
        {
            int new_num = num * rhs.num;
            int new_den = den * rhs.den;
            num = new_num;
            den = new_den;
            return *this;
        }
        Fraction& operator/=(const Fraction& rhs)
        {
            int new_num = num * rhs.den;
            int new_den = den * rhs.num;
            num = new_num;
            den = new_den;
            return *this;
        }
};

std::ostream& operator<<(std::ostream& out, const Fraction& f)
{
   return out << f.get_num() << '/' << f.get_den();
}

bool operator==(const Fraction& lhs, const Fraction& rhs)
{
    return lhs.get_num()*rhs.get_den() == lhs.get_den() * rhs.get_num();
}

bool operator!=(const Fraction& lhs, const Fraction& rhs)
{
    return !(lhs == rhs);
}


Fraction operator+(Fraction lhs, const Fraction& rhs)
{
    return lhs += rhs;
}

Fraction operator-(Fraction lhs, const Fraction& rhs)
{
    return lhs -= rhs;
}

Fraction operator*(Fraction lhs, const Fraction& rhs)
{
    return lhs *= rhs;
}

Fraction operator/(Fraction lhs, const Fraction& rhs)
{
    return lhs /= rhs;
}

class FractionSolver {
    const char PLUS = '+';
    const char MINUS = '-';
    const char MULT = '*';
    const char DIVIDE = '/';
    const Fraction GOAL = Fraction(24);
private:
    Fraction evaluate(Fraction a, Fraction b, char op, bool &divide_by_zero) {
        if (op == PLUS) {
            return a + b;
        } else if (op == MINUS) {
            return a - b;
        } else if (op == MULT) {
            return a * b;
        } else if (op == DIVIDE) {
            divide_by_zero = (b.get_num() == 0);
            return a / b;
        } else {
            assert(false);
            return 0;
        }
    }

    bool resultValid(Fraction result) {
        return result == GOAL;
    }

    bool checkAllEvaluations(Fraction a, Fraction b, Fraction c, Fraction d, char op1, char op2, char op3) {
        // (a # b) # (c # d)
        bool divide_by_zero = false;
        Fraction result1 = evaluate(a,b,op1,divide_by_zero);
        Fraction result2 = evaluate(c,d,op3,divide_by_zero);
        Fraction result = evaluate(result1, result2, op2,divide_by_zero);
        if (resultValid(result) && !divide_by_zero) {
            return true;
        }

        // ((a # b) # c) # d
        divide_by_zero = false;
        result1 = evaluate(a,b,op1,divide_by_zero);
        result2 = evaluate(result1,c,op2,divide_by_zero);
        result = evaluate(result2, d, op3,divide_by_zero);
        if (resultValid(result) && !divide_by_zero) {
            return true;
        }

        // (a # (b # c)) # d)
        divide_by_zero = false;
        result1 = evaluate(b,c,op2,divide_by_zero);
        result2 = evaluate(a,result1,op1,divide_by_zero);
        result = evaluate(result2, d, op3,divide_by_zero);
        if (resultValid(result) && !divide_by_zero) {
            return true;
        }

        // a # ((b # c) # d)
        divide_by_zero = false;
        result1 = evaluate(b,c,op2,divide_by_zero);
        result2 = evaluate(result1,d,op3,divide_by_zero);
        result = evaluate(a, result2, op1,divide_by_zero);
        if (resultValid(result) && !divide_by_zero) {
            return true;
        }

        // a # (b # (c # d))
        divide_by_zero = false;
        result1 = evaluate(c,d,op3,divide_by_zero);
        result2 = evaluate(b,result1,op2,divide_by_zero);
        result = evaluate(a, result2, op1,divide_by_zero);
        if (resultValid(result) && !divide_by_zero) {
            return true;
        }
        return false;
    }



    bool solve(vector<Fraction>& cards) {
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
            Fraction a = cards[perm[0]];
            Fraction b = cards[perm[1]];
            Fraction c = cards[perm[2]];
            Fraction d = cards[perm[3]];
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
    bool judgePoint24(vector<int>& cards) {
        std::vector<Fraction> FractionVec(cards.begin(), cards.end());
        std::vector<Fraction> test;
        for (auto & card : cards) {
            test.emplace_back(card);
        }
        return solve(FractionVec);
    }
};