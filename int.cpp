#include <iostream>
#include <stack>
#include <string>
#include <cmath>

using namespace std;

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int getOperatorPrecedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    else if (op == '*' || op == '/')
        return 2;
    return 0;
}

double applyOperation(double a, double b, char op) {
    switch (op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
        default:
            return 0;
    }
}

double evaluateExpression(const string& expression) {
    stack<double> values;
    stack<char> operators;

    for (int i = 0; i < expression.length(); i++) {
        if (expression[i] == ' ')
            continue;

        if (isdigit(expression[i])) {
            double num = 0;
            while (i < expression.length() && isdigit(expression[i])) {
                num = num * 10 + (expression[i] - '0');
                i++;
            }
            i--;
            values.push(num);
        } else if (expression[i] == '(') {
            operators.push(expression[i]);
        } else if (expression[i] == ')') {
            while (!operators.empty() && operators.top() != '(') {
                double operand2 = values.top();
                values.pop();

                double operand1 = values.top();
                values.pop();

                char op = operators.top();
                operators.pop();

                values.push(applyOperation(operand1, operand2, op));
            }
            operators.pop();
        } else if (isOperator(expression[i])) {
            while (!operators.empty() && getOperatorPrecedence(operators.top()) >= getOperatorPrecedence(expression[i])) {
                double operand2 = values.top();
                values.pop();

                double operand1 = values.top();
                values.pop();

                char op = operators.top();
                operators.pop();

                values.push(applyOperation(operand1, operand2, op));
            }
            operators.push(expression[i]);
        }
    }

    while (!operators.empty()) {
        double operand2 = values.top();
        values.pop();

        double operand1 = values.top();
        values.pop();

        char op = operators.top();
        operators.pop();

        values.push(applyOperation(operand1, operand2, op));
    }

    return values.top();
}

int main() {
    string expression;
    cout << "Введите арифметическое выражение: ";
    getline(cin, expression);

    double result = evaluateExpression(expression);
    cout << "Результат: " << result << endl;

    return 0;
}
