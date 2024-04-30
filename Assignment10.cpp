#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

struct Triple {
    string operation;
    string operand1;
    string operand2;
};

void print(string expression) {
    for (auto c : expression) {
        cout << c;
    }
    cout << endl;
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '~';
}

int precedence(char op) {
    if (op == '~')
        return 4;
    else if (op == '/')
        return 3;
    else if (op == '*' )
        return 2;
    else if (op == '+' )
        return 1;
    else if (op == '-')
        return 0;
    else
        return -1;
}

vector<Triple> convertToTriples(const string &expression, int index) {
    stack<char> operators;
    stack<string> operands;
    vector<Triple> triples;
    int tempVarCount = index;

    for (int i = 0; i < expression.length(); ++i) {
        char c = expression[i];

        if (c == ' ')
            continue;

        if (isdigit(c)) {
            string operand;
            while (isdigit(c)) {
                operand += c;
                c = expression[++i];
            }
            operands.push(operand);
            i--;
        } else if (isalpha(c)) {
            string operand;
            while (isalpha(c)) {
                operand += c;
                c = expression[++i];
            }
            operands.push(operand);
            i--;
        } else if (c == '(') {
            operators.push(c);
        } else if (c == ')') {
            while (!operators.empty() && operators.top() != '(') {
                string op2 = operands.top();
                operands.pop();
                string op1 = operands.top();
                operands.pop();
                char op = operators.top();
                operators.pop();
                string tempVar = to_string(tempVarCount++);
                operands.push(tempVar);
                triples.push_back({string(1, op), op1, op2});
            }
            operators.pop(); // pop '('
        } else if (isOperator(c)) {
            if (c == '~') { // Handle unary operator '~'
                string op2 = operands.top(); // Operand 2
                operands.pop();
                string op1 = "NULL"; // Operand 1 as NULL
                char op = c;
                string tempVar = to_string(tempVarCount++);
                operands.push(tempVar);
                triples.push_back({string(1, op), op1, op2});
            } else {
                while (!operators.empty() && precedence(operators.top()) >= precedence(c)) {
                    string op2 = operands.top();
                    operands.pop();
                    string op1 = operands.top();
                    operands.pop();
                    char op = operators.top();
                    operators.pop();
                    string tempVar =  to_string(tempVarCount++);
                    operands.push(tempVar);
                    triples.push_back({string(1, op), op1, op2});
                }
                operators.push(c);
            }
        }
    }

    while (!operators.empty()) {
        string op2 = operands.top();
        operands.pop();
        string op1 = operands.top();
        operands.pop();
        char op = operators.top();
        operators.pop();
        string tempVar = to_string(tempVarCount++);
        operands.push(tempVar);
        triples.push_back({string(1, op), op1, op2});
    }

    return triples;
}

int main() {
    string expression = "a = b * - c + b * - c";
    cout<<isOperator('~');    
    // Extracting the right side of the expression
    string right = "";
    bool flag = false;
    for (auto c : expression) {
        if (c == '=') {
            flag = true;
            continue;
        } else if (c == ' ')
            continue;
        else {
            if (flag)
                right.push_back(c);
        }
    }

    // Modify the expression to process only the right side
    expression = right;

    // Replace '-' following an operator with '~'
    for (int i = 0; i < expression.size() - 1; i++) {
        if (isOperator(expression[i]) && expression[i + 1] == '-') {
            expression[i + 1] = '~';
        }
    }
    // cout<<"HELLOW"<<endl;
    int index = 0;
    // for(auto i:expression){
    //     cout<<i<<" ";
    // }
    cout << "Triples:" << endl;
    for(int i=0; i<expression.size()-1; i++){
        // cout<<isOperator(expression[i]) =='~'<<endl;
        if(expression[i] =='~'){
            cout <<index<< ". (" << "-" << ", " << expression[i+1] <<", NULL" << ")" << endl;
            expression[i] = ' ';
            expression[i+1]='0'+index;
            index++;
        }
    }
    // cout<<"HIII"<<" ";

    // Convert expression to triples
    vector<Triple> triples = convertToTriples(expression,index);
    
    // Output the triples

    for (const auto &triple : triples) {
        cout <<index<< ". (" << triple.operation << ", " << triple.operand1 << ", " << triple.operand2 << ")" << endl;
        index = index+1;
    }

    return 0;
}
