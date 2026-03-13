#include <iostream>
#include <string>
#include <cmath> //for fmod
#include <iomanip> //for setprecision

using namespace std;
#define MAX 100

// Stack Class
template<typename T>
class Stack {
public:
	int top;
	T exp[MAX]; //Max size of stack
	Stack() { top = -1; };
	void push(T x) {
		if (top >= MAX - 1)
			cout << "Stack Overflow." << endl;
		else
			exp[++top] = x;
	};

	T pop() {
		if (top < 0) {
			return 0;
		}
		else {
			return exp[top--];
		}
	};

	int isEmpty() {
		if (top < 0)
			return 1;
		else
			return 0;
	};

	T peek() {
		if (top < 0) {
			return 0;
		}
		else {
			T x = exp[top];
			return x;
		}
	};
};

float power(float base, float exponent) {
	if (exponent == 0)
		return 1;
	else
		return (base * power(base, exponent - 1));
}

//Returns 1 if character1 and character2 are matching left and right brackets
int isMatchingPair(char character1, char character2) {
	if (character1 == '(' && character2 == ')')
		return 1;
	else if (character1 == '{' && character2 == '}')
		return 1;
	else if (character1 == '[' && character2 == ']')
		return 1;
	else
		return 0;
};

//Return 1 if expression has balanced Brackets
int areParenthesisBalanced(char exp[]) {
	int i = 0;
	//Declare an empty character stack
	Stack<char> s;
	//Traverse the given expression to check matching brackets
	while (exp[i]) {
		if (exp[i] == '{' || exp[i] == '(' || exp[i] == '[')
			s.push(exp[i]);
		if (exp[i] == '}' || exp[i] == ')' || exp[i] == ']') {
			if (s.top == -1)
				return 0;
			else if (!isMatchingPair(s.pop(), exp[i]))
				return 0;
		}
		i++;
	}
	//If there is something left in the stack it means there is
	//A starting bracket without a closing bracket -> not balanced
	if (s.top == -1)
		return 1; //return true
	else
		return 0; //return false
};

//Determine if the number of Operands is Valid or Invalid
string checkValidity(string statement) {
	int operands = 0;
	int operators = 0;
	string token;
	for (int i = 0; i < statement.length(); i++) {
		if (statement[i] == '^' || statement[i] == '*' || statement[i] == '/' || statement[i] == '%' || statement[i] == '+' || statement[i] == '-')
			operators++;
		if (isdigit(statement[i])) {
			operands++;
			if (i + 1 <= statement.length() && isdigit(statement[i + 1])) {
				i++;
				if (i + 2 <= statement.length() && isdigit(statement[i + 2]))
					i++;
			}
		}
	}
	if (operators == 0 && operands != 0)
		return "Error: Invalid number of Operators";
	else if (operands < (operators + 1))
		return "Error: Invalid number of Operands";
	else
		return "Valid";
}

//Function to convert an Infix expression to postfix expression
string toPostfix(string infix) {
	string postfix = ""; //New string to return at end
	Stack<char> tempStack[MAX]; //Create a Stack
	//Read expression left to right
	for (size_t i = 0; i < infix.length(); i++) {
		char currentPriority = tempStack->peek(); //Store Priority at the top of the stack
		if (infix[i] == ' ')
			continue;
		else if (infix[i] == '{' || infix[i] == '[' || infix[i] == '(') {
			//Encounter an Open Parenthesis, Append to stack immediately
			tempStack->push(infix[i]);
		}
		else if (infix[i] == '}') {
			while (tempStack->peek() != '{')  //Pop until opening parenthesis is found
				postfix = postfix + tempStack->pop() + ' ';
			tempStack->pop(); //Remove the opening parenthesis, do not append it
		}
		else if (infix[i] == ']') {
			while (tempStack->peek() != '[')
				postfix = postfix + tempStack->pop() + ' ';
			tempStack->pop(); //Remove the opening parenthesis, do not append it
		}
		else if (infix[i] == ')') {
			while (tempStack->peek() != '(')
				postfix = postfix + tempStack->pop() + ' ';
			tempStack->pop(); //Remove the opening parenthesis, do not append it
		}
		else if (infix[i] == '^') {
			if (currentPriority == '^') { //If priority at top of stack is same
				while (!(tempStack->isEmpty()))
					postfix = postfix + tempStack->pop() + ' ';
				tempStack->push(infix[i]);
			}
			else //If priority at top of stack is lower
				tempStack->push(infix[i]);
		}
		else if (infix[i] == '*' || infix[i] == '/' || infix[i] == '%') {
			//If priority at top of stack is the same or higher
			if (currentPriority == '^' || currentPriority == '*' || currentPriority == '/' || currentPriority == '%') {
				while (currentPriority != '+' && currentPriority != '-' && !(tempStack->isEmpty())) {
					postfix = postfix + tempStack->pop() + ' ';
					currentPriority = tempStack->peek();
				}
				tempStack->push(infix[i]);
			}
			//if priority at top of stack is lower
			else
				tempStack->push(infix[i]);
		}
		else if (infix[i] == '+' || infix[i] == '-') { //These operands are always lowest priority
			if (currentPriority == '^' || currentPriority == '*' || currentPriority == '/' || currentPriority == '%' || currentPriority == '+' || currentPriority == '-') {
				while (!(tempStack->isEmpty())) {
					postfix = postfix + tempStack->pop() + ' ';
					currentPriority = tempStack->peek();
				}
				tempStack->push(infix[i]);
			}
			else
				tempStack->push(infix[i]);
		}
		else if (isdigit(infix[i])) {
			while (isdigit(infix[i])) {
				postfix += infix[i];
				i++;
			}
			postfix += ' ';
			--i;
		}
	}
	while (!tempStack->isEmpty())
		postfix = postfix + tempStack->pop() + ' ';
	return postfix;
};

//Performs calculations on a postfix expression using a stack
float arithmetic(string expression) {
	Stack<float> tempStack[MAX];
	string token;
	for (char& c : expression) {
		if (c != ' ')
			token = token + c;
		else {
			if (token[0] == '^' || token[0] == '*' || token[0] == '/' || token[0] == '%' || token[0] == '+' || token[0] == '-') {
				float newNum = 0;
				float operand1 = tempStack->pop();
				float operand2 = tempStack->pop();
				if (token[0] == '^')
					newNum = power(operand2, operand1);
				else if (token[0] == '*')
					newNum = operand2 * operand1;
				else if (token[0] == '/')
					newNum = operand2 / operand1;
				else if (token[0] == '%')
					newNum = fmod(operand2, operand1);
				else if (token[0] == '+')
					newNum = operand2 + operand1;
				else if (token[0] == '-')
					newNum = operand2 - operand1;
				tempStack->push(newNum);
			}
			else {
				float stringAsNum = stoi(token);
				tempStack->push(stringAsNum);
			}
			token.clear();
		}
	}
	return tempStack->pop();
};


int main() {
	string user_str;
	cout << "Program Started. Type 'End' to end program execution." << endl;

	//Collect User Input
	while (user_str != "End" || user_str != "end" || user_str != "END") {
		cout << "Input: ";
		getline(cin, user_str);
		string keep = user_str;
		if (user_str == "End" || user_str == "end" || user_str == "END")
			break;
		cout << endl;

		//Check if the input is valid.
		char invalidChar = 'a';
		char balance[MAX];
		int count = 0;
		for (char& c : user_str) {
			if (c == '(' || c == '[' || c == '{' || c == '}' || c == ']' || c == ')') {
				balance[count] = c;
				count++;
			}
			else if (c != '+' && c != '-' && c != '*' && c != '/' && c != '^' && c != '%' && c != ' ' && !isdigit(c)) {
				invalidChar = c;
			}
		}
		if (invalidChar != 'a') {
			cout << "Error: Invalid Character '" << invalidChar << "' in the Expression." << endl;
			cout << "Try new Input or Type 'End' to end program execution." << endl << endl;
			continue;
		}
		if (count != 0)
			if (areParenthesisBalanced(balance) == 0) {
				cout << "Error: Invalid Parentheses." << endl;
				cout << "Try new Input or Type 'End' to end program execution." << endl << endl;
				continue;
			}
		string message = checkValidity(user_str);
		if (message != "Valid") {
			cout << message << endl;
			cout << "Try new Input or Type 'End' to end program execution." << endl << endl;
			continue;
		}


		//If execution reaches this point, input should be valid.
		string newString = toPostfix(keep);
		cout << "Postfix Expression: " << newString << endl;
		cout << "Result: ";
		cout << fixed << setprecision(3) << arithmetic(newString) << endl;
		cout << endl;
	}
	return 0;
};
