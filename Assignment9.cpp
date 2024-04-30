#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

struct Quadruple {
    string operation;
    string operand1;
    string operand2;
    string result;
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
        return 3;
    else if (op == '/')
        return 2;
    else if (op == '*' || op == '+' || op == '-')
        return 1;
    else
        return -1;
}

vector<Quadruple> convertToQuadruples(const string &expression) {
    stack<char> operators;
    stack<string> operands;
    vector<Quadruple> quadruples;
    unordered_map<string, string> tempVariables;
    int tempVarCount = 0;

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
                string tempVar = "t" + to_string(tempVarCount++);
                tempVariables[tempVar] = op1 + " " + op + " " + op2;
                operands.push(tempVar);
                quadruples.push_back({string(1, op), op1, op2, tempVar});
            }
            operators.pop(); // pop '('
        } else if (isOperator(c)) {
            if (c == '~') { // Handle unary operator '~'
                string op2 = operands.top(); // Operand 2
                operands.pop();
                string op1 = "NULL"; // Operand 1 as NULL
                char op = c;
                string tempVar = "t" + to_string(tempVarCount++);
                tempVariables[tempVar] = op1 + " " + op + " " + op2;
                operands.push(tempVar);
                quadruples.push_back({string(1, op), op1, op2, tempVar});
            } else {
                while (!operators.empty() && precedence(operators.top()) >= precedence(c)) {
                    string op2 = operands.top();
                    operands.pop();
                    string op1 = operands.top();
                    operands.pop();
                    char op = operators.top();
                    operators.pop();
                    string tempVar = "t" + to_string(tempVarCount++);
                    tempVariables[tempVar] = op1 + " " + op + " " + op2;
                    operands.push(tempVar);
                    quadruples.push_back({string(1, op), op1, op2, tempVar});
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
        string tempVar = "t" + to_string(tempVarCount++);
        tempVariables[tempVar] = op1 + " " + op + " " + op2;
        operands.push(tempVar);
        quadruples.push_back({string(1, op), op1, op2, tempVar});
    }

    return quadruples;
}

int main() {
    string expression = "a = b * - c + b * - c";
    // cout << "Expression size: " << expression.size() << endl;

    string left = "";
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
            else
                left.push_back(c);
        }
    }

    if (flag)
        expression = right;
    else
        expression = left;

    // Print the strings
    // cout << "Expression: " << expression << endl;
    // cout << "Left: " << left << endl;
    // cout << "Right: " << right << endl;

    // Replace '-' following an operator with '~'
    for (int i = 0; i < expression.size() - 1; i++) {
        if (isOperator(expression[i]) && expression[i + 1] == '-') {
            expression[i + 1] = '~';
        }
    }

    // Print the modified expression
    // cout << "Modified Expression: " << expression << endl;

    vector<Quadruple> quadruples = convertToQuadruples(expression);
    
    string result;
    cout << "Quadruples:" << endl;
    for (const auto &quad : quadruples) {
    string operation = quad.operation;
    if (operation == "~") {
        operation = "-"; // Replace unary minus operator '~' with '-'
    }
        result = quad.result;
        cout << "(" << operation << ", " << quad.operand1 << ", " << quad.operand2 << ", " << quad.result << ")" << endl;
    }
    if(flag){
        cout<<"(=, "<<right[0]<<", "<<result<<" ,NULL)";
    }

    return 0;
}
