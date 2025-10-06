#include <string>
#include <stack>
#include <iostream>

using namespace std;

bool parseParens( const char array[], int n) {
    
    // The variable formerly known as "aStack".  Naming is important
    // and clarifies the purpose - to track opening parens that need
    // to be resolved.
    stack<char> openingParensToMatch;
	    
    if( n == 0 ) {
        return true; // Degenerate case - string is empty, 
                     // thus no paren mismatches.
    }
    else if ( n<0 ) {
        throw new logic_error("Invalid state, parseParent expects n>=0");
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
           }
           ++currentPos;
        } while ( currentPos < n );

        bool allParensResolved = openingParensToMatch.size()==0;
        return allParensResolved;
}

int main() {

   string expr;

   // Print an input propmt for the user.
   cout << endl << "Enter the expression: ";

   // Accept the input from the keybord, store the result when 
   // user preses <enter> in the variable "expr".
   cin >> expr;

   // Print a new line to put some space between the input and the
   // next output;
   cout << endl;


   // Test the input, then print the result to the screen.
   if(parseParens(expr.c_str(), expr.length())) {
       cout << "The expression has matching parenthesis." << endl;
   } 
   else { 
       cout << "The expression has a parentheis mismatch." << endl;
   }

   return 0;
}

