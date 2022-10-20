#include <iostream>
#include <cctype>
#include "dictionary.h"
#include "stack.h"

// global Value struct
// *Value struct needed for doOperation*
struct Value {
    std::string name;
    Fraction val;
};

Fraction doOperation(Value lhs, char op, Value rhs); //func prototype
bool hasPrecedence(char a, char b); //func prototype

int main() {
    // variable assignment dictionary
    Dictionary vars;

    // global stacks
    Stack <Value>numStack;
    Stack <char>opStack;

    std::string line; //input line

    // MAIN INPUT LOOP 
    while (std::getline(std::cin, line)) {

        //process each line
        numStack.clear();
        opStack.clear();
        opStack.push('$');
        
        int32_t first = 0;  // line index
        char op;            // stack operation
        Value num;          // stack value
        Value rhs;          // right hand side value
        Value lhs;          // left hand side value

        while (first < line.length()) {
            if (isdigit(line[first])) {
                num.name = "";  //assign no name for just values
                num.val = 0;    //initial value
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
                    Value res;              //result value

                    // check dictionary
                    if (rhs.name != "") {
                        rhs.val = vars.search(rhs.name);
                    }
                    if (lhs.name != "") {
                        lhs.val = vars.search(lhs.name);
                    }
                    // assign result values
                    Fraction numValue = doOperation(lhs, op, rhs);
                    res.name = "";
                    res.val = numValue;
                    numStack.push(res);

               }
               opStack.pop();
               first++; 
            }
            else if (line[first] == '+' || line[first] == '=' || line[first] == '-' || line[first] == '*' || line[first] == '/') {

                while (hasPrecedence(opStack.peek(), line[first])) {
                    
                    //perform top operation
                    op = opStack.pop();     //operation
                    rhs = numStack.pop();   //right hand operand
                    lhs = numStack.pop();   //left hand operand
                    Value res;              //result value

                    // check dictionary
                    if (rhs.name != "") {
                    rhs.val = vars.search(rhs.name);
                    }
                    if (lhs.name != "") {
                        lhs.val = vars.search(lhs.name);
                    }
                    // assign result values
                    Fraction numValue = doOperation(lhs, op, rhs);
                    res.name = "";
                    res.val = numValue;
                    numStack.push(res);
                }
                opStack.push(line[first]);
                first++; 
            }
            // terminate if user enters '#'
            else if (line[first] == '#') {
                return 0;
            }
            else {
                first++;
            }
        }
        
        while (opStack.peek() != '$') {
            //perform top operation
            op = opStack.pop();     //operation
            rhs = numStack.pop();   //right hand operand
            lhs = numStack.pop();   //left hand operand
            Value res;              //result value

            if (op == '=') {
                // check if assigning a variable
                if (rhs.name != "") {
                    rhs.val = vars.search(rhs.name);
                }
                
                // assign result values
                res.name = lhs.name;
                res.val = rhs.val;
                vars.add(lhs.name, rhs.val);    // can update if key already exists
                numStack.push(res);
            } else {
                // check dictionary
                if (rhs.name != "") {
                rhs.val = vars.search(rhs.name);
                }
                if (lhs.name != "") {
                    lhs.val = vars.search(lhs.name);
                }
                // assign result values
                Fraction numValue = doOperation(lhs, op, rhs);
                res.name = "";
                res.val = numValue;
                numStack.push(res);
            }
        }
        std::cout << numStack.peek().val << std::endl; // answer output
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
            // cant divide by zero
            if (rhs.val == 0) {
                 throw std::invalid_argument( "Can't divide by zero" );
            }
            res = lhs.val / rhs.val;
            break;
    }
    return res;
}