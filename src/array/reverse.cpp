#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

void reverse(char str[], int length) {
   for(int i=0, j=length-1; i<j; i++,j--) {
       char tmp = str[i];
       str[i]=str[j];
       str[j]=tmp;
   }
   str[length]=0;
}


int main() {
   string text;

   cout << endl << "Enter the text to reverse: ";
   std::getline(cin, text);
   char* buffer = NULL;
   
   try { 
      buffer = new char[text.length()+1];
      for(int i=0;i<text.length(); i++) {
          buffer[i]=text.c_str()[i];
      }
      buffer[text.length()]=0;

      reverse(buffer,text.length());
      cout << "The reverse is: '" << buffer << "'" << endl;
  }
  catch(exception e) {
      if( buffer != NULL ) {
          delete buffer;
      }
      throw e;
  }

  delete buffer;

  cout << endl << endl;

  return 0;
}
