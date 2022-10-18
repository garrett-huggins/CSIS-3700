#include <iostream>
#include <cctype>
#include "dictionary.h"
#include "stack.h"

// global value struct
struct Value {
    std::string name;
    Fraction val;
};

Fraction doOperation(Value lhs, char op, Value rhs); //func prototype
bool hasPrecedence(char a, char b); //func prototype

int main() {
    Dictionary vars;

    // global stacks
    Stack <Value>numStack;
    Stack <char>opStack;

    std::string line; //input line

    while (std::getline(std::cin, line)) {

        //process each line
        numStack.clear();
        opStack.clear();
        opStack.push('$');
        int32_t first = 0;
        Value num;
        char op;
        Value rhs;
        Value lhs;

        while (first < line.length()) {
            if (isdigit(line[first])) {
                num.name = ""; //clear out name to check num
                num.val = 0; //num is structure
                while (isdigit(line[first])) {
                    num.val = num.val * 10 + line[first] - '0'; //0 ascii 48
                    first++;
                }
                numStack.push(num);
            }
            else if (isalpha(line[first])) {
                num.name = "";
                while (isalpha(line[first])) {
                    num.name = num.name + line[first]; //create string
                    first++;
                }
                numStack.push(num);
            }
            else if (line[first] == '(') {
                opStack.push('(');
                first++;
            }
            else if (line[first] == ')') {
                while (opStack.peek() != '(') {

                    //perform top operation
                    op = opStack.pop();     //operation
                    rhs = numStack.pop();   //right hand operand
                    lhs = numStack.pop();   //left hand operand
                
                    if (op == '=') {
                        vars.add(lhs.name, rhs.val);
                    } else {
                        Fraction numValue = doOperation(lhs, op, rhs);
                        Value res;
                        res.name = "";
                        res.val = numValue;
                        numStack.push(res);
                    }

               }
               opStack.pop();
               first++; 
            }
            else if (line[first] == '+' || line[first] == '-' || line[first] == '*' || line[first] == '/') {
                while (hasPrecedence(opStack.peek(), line[first])) {
                    
                //    //perform top operation
                //     op = opStack.pop();     //operation
                //     rhs = numStack.pop();   //right hand operand
                //     lhs = numStack.pop();   //left hand operand
                
                //     if (op == '=') {
                //         vars.add(lhs.name, rhs.val);
                //     } else {
                //         Fraction numValue = doOperation(lhs, op, rhs);
                //         Value res;
                //         res.name = "";
                //         res.val = numValue;
                //         numStack.push(res);
                //     }
                }
                opStack.push(line[first]);
                first++; 
            }
            else if (line[first] == '#') {
                return 0;
            }
            else {
                first++;
            }
            std::cout << line[first] << std::endl;
        }

        while (opStack.peek() != '$') {
            //perform top operation
        }

        //return numStack.peek();
        std::cout << numStack.peek().val << std::endl;
    }
    
    
    return 0;
}

bool hasPrecedence(char a, char b) {
	if (a == '+' || a == '/') {
		return true;
	}
	if (a == '(' || a == '=' || a == '$') {
		return false;
	}
	return b == '+' || b == '-' || b == '=';
}

Fraction doOperation(Value lhs, char op, Value rhs) {
    Fraction res;
    switch (op) {
        case '+':
            res = lhs.val + rhs.val;
            break;
        case '-':
            res = lhs.val - rhs.val;
            break;
        case '*':
            res = lhs.val * rhs.val;
            break;
        case '/':
            res = lhs.val / rhs.val;
            break;
    }
    return res;
}