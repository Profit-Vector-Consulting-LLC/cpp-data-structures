#include <string>
#include <stack>
#include <stdexcept>
#include <iostream>

using namespace std;

bool parseParen( const char *array, int n) {
    
    // The variable formerly known as "aStack".  Naming is important
    // and clarifies the purpose - to track opening parens that need
    // to be resolved.
    stack<char> openingParensToMatch;
    
    if( n == 0 ) {
        return true; // Degenerate case - string is empty, 
                     // thus no paren mismatches.
    }
    else if ( n<0 ) {
       throw new runtime_error("Invalid state, parseParent expects n>=0");
    }

    int currentPos = 0;
    // Traverse the characters from left to right, finding 
    // each matching pair or quitting if we find a mismatch.
    do {
       // Grab the current character to process.
       char currentChar = array[currentPos];
       switch(currentChar) {
          case '(': 
                 
		        openingParensToMatch.push(currentChar);
                break;
 
          case ')':
                if( openingParensToMatch.size() > 0 ) {
                   // We encountered a closing parenthesis with a 
                   // matching open.  Clear the open paren from the stack.
                   openingParensToMatch.pop();
                }
                else {
                   // We encountered a closing parenthesis without a 
                   // matching opening one.  Once this happens there's
                   // no way to recover, exit with answer of false.
                   return false; 
                }
                break;
	        default: 

                string message = "Unexpected character ";
                        message += currentChar;
                        message += " found at position ";
                        message += currentPos+1;
                        message += ".";
                throw new invalid_argument(message); 
       }
       ++currentPos;
    } while ( currentPos < n );

    bool allParensResolved = openingParensToMatch.size()==0;
    return allParensResolved;
}

int main () {

   string expr;

   // Print an input propmt for the user.
   cout << "Enter the expression: ";

   // Accept the input from the keybord, store the result when 
   // user preses <enter> in the variable "expr".
   cin >> expr;

   // Print a new line to put some space between the input and the
   // next output;
   cout << endl;


   // The "try" keyword tells us that we may throw an error that will
   // break the normal flow of the program.  In this case if the user
   // enters anything other than ( or ) and we try to process it, we'll
   // throw a kind of error called an Exception. The code we'll test for the
   // exception is inside the curly braces after the "try" keyword.  
   // We can handle the error in the "catch" block (or code between curly braces
   // that follows the "try" block.
   try { 

       // Test the input, then print the result to the screen.

       const char* val = expr.c_str();
       int n = expr.length();
       if( parseParen(val, n) ) {
           cout << "The expression has matching parenthesis." << endl;
       } 
       else { 
           cout << "The expression has a parentheis mismatch." << endl;
       }
   }
   catch(exception e) {
       //Whoops! User entered something unexpected! print the error message to the "standard error" output stream and quit with return code <> 0 (program encountered an error.
       cerr << "ERROR: " << e.what() << endl;
       return 1;
   }    

   // User provided valid input, return 0, meaning no error.
   return 0;
}

