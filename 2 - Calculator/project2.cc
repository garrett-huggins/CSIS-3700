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
                //std::cout << "WE FOUND A LETTER" << std::endl; TEST

                // FIND OUT IF NAME IS IN DICTIONARY

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
            else if (line[first] == '+' || line[first] == '=' || line[first] == '-' || line[first] == '*' || line[first] == '/') {
                // if (line[first] == '=') {
                //         res.name = lhs.name;
                //         res.val = rhs.val;
                //         vars.add(lhs.name, rhs.val);
                //         numStack.push(res);
                // }
                std::cout << "MADE IT INSIDE FIRST OP" << std::endl;

                while (hasPrecedence(opStack.peek(), line[first])) {
                    
                    std::cout << "MADE IT INSIDE OP" << std::endl;
                   //perform top operation
                    op = opStack.pop();     //operation
                    rhs = numStack.pop();   //right hand operand
                    lhs = numStack.pop();   //left hand operand
                    Value res;

                    if (op == '=') {
                        res.name = lhs.name;
                        res.val = rhs.val;
                        std::cout << "var name: " << lhs.name << std::endl;
                        std::cout << "value: " << rhs.val << std::endl;
                        vars.add(lhs.name, rhs.val);
                        numStack.push(res);
                    } else {
                        if (rhs.name != "") {
                        rhs.val = vars.search(rhs.name);
                        }
                        if (lhs.name != "") {
                            lhs.val = vars.search(lhs.name);
                        }
                        Fraction numValue = doOperation(lhs, op, rhs);
                        res.name = "";
                        res.val = numValue;
                        numStack.push(res);
                    }
                    
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
            //std::cout << line[first] << std::endl;
        }
        
        while (opStack.peek() != '$') {
            //perform top operation
            op = opStack.pop();     //operation
            rhs = numStack.pop();   //right hand operand
            lhs = numStack.pop();   //left hand operand
            Value res;

            std::cout << "MADE IT $ OP" << std::endl;

            if (op == '=') {
                res.name = lhs.name;
                res.val = rhs.val;
                std::cout << "var name: " << lhs.name << std::endl;
                std::cout << "value: " << rhs.val << std::endl;
                vars.add(lhs.name, rhs.val);
                numStack.push(res);
            } else {
                if (rhs.name != "") {
                rhs.val = vars.search(rhs.name);
                }
                if (lhs.name != "") {
                    lhs.val = vars.search(lhs.name);
                }
                Fraction numValue = doOperation(lhs, op, rhs);
                res.name = "";
                res.val = numValue;
                numStack.push(res);
            }
        }

        //return numStack.peek();
        //std::cout << numStack.peek().name << std::endl;
        std::cout << numStack.peek().val << std::endl;
        //vars.add("vars", 25);

        //std::cout << vars.search("vars") << std::endl;
    }
    
    
    return 0;
}

bool hasPrecedence(char a, char b) {
	if (a == '*' || a == '/') {
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