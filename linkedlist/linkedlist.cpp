#include <iostream>
#include <string>

using namespace std;

template <class T> class Node {
	public:
     	    Node<T> *next, *prev;
            T value;

            Node<T>(T t) {
	       next = (Node<T>*)NULL;
               prev = (Node<T>*)NULL;
               value = t;
            }

            Node<T>(Node<T> *next, Node<T> *prev, T value) {
	       this->next=next;
               this->prev=prev;
               this->value=value;
            }
};      

template <class T> class LinkedList {
       protected:        
            Node<T> *first, *last; 

       public:
	    LinkedList<T>() {
	       first = last = (Node<T>*)NULL;
	    }

	    ~LinkedList<T>() {
	       //Individually free each node.  
	       Node<T> *current = this->first;
	       while(current != (Node<T>*)NULL) {
		    Node<T> *next = current->next;
		    try {
		       delete current;
		    } catch(exception e) {
		       cerr << e.what() << endl;
		    }
		    current=next;
	       }
	    }

            Node<T>* getFirst() {
	       return first;
            }	  

            bool isEmpty() {
	       return first == (Node<T>*)NULL;
	    }

            LinkedList<T>& append(LinkedList& toAppend) {
	       Node<T>* current = toAppend.first;
	      
	       while(current != (Node<T>*)NULL) {
		  this->append(current->value);
		  current = current->next;
	       } 
               return *this;
            }

	    LinkedList<T>& append(T val) {
	       Node<T> *newVal = new Node<T>(val);
	       if(first==((Node<T>*)NULL)) { 
                   first = newVal;
		   last = newVal;
	       }
	       else {
	           last->next=newVal;
		   newVal->prev=last;
		   last = newVal;
	       }
	       return *this;
	    }

	    
            LinkedList<T>& removeFirstOf(T toRemove) {
	       Node<T>* current = this->first;
	      
	       while(current != (Node<T>*)NULL) {
		   if(current->value == toRemove) {
		      Node<T>*curPrev, *curNext;
		      curPrev = current->prev;
		      curNext = current->next;

		      if(curPrev !=(Node<T>*)NULL) {
			 curPrev->next = curNext;
		      }
		      if(curNext != (Node<T>*)NULL) {
                         curNext->prev = curPrev;
		      }
		      if( current == this->first) {
			 this->first = curNext;
		      }
		      if( current == this->last) {
                         this->last = curPrev;
		      }

		      delete current;
		      current=(Node<T>*)NULL;
		   }
		   else {
		      current = current->next;
		   }
	       }

               return *this;
            }

	    LinkedList<T>& sort() {
		   Node<T> *current, *temp;
		   
		   bool orderChanged;
		   do {
		       current = this->first;
                       orderChanged = false;
		       while( current != (Node<T>*)NULL) { 
		           temp = current->next;
		           if(temp != (Node<T>*)NULL) {
			       if(temp->value < current->value ){
				   // The nodes are out of order switch current and current->next (nodes "b" and "c" below).
				   Node<T> *a, *b, *c, *d;
				   a = current->prev;
				   b = current;
				   c = current->next;
				   d = (current->next == (Node<T>*)NULL ? current->next : current->next->next);

				   //Note only b and c (the current and next items) are guaranteed to be non-null.
				   //The following code is generalizdd to work in all null scenarios, but
				   //we must first test for null on a and d before dereferencing them.

				   //Rewire the nexts so that they are traversed in a c b d order now, instead of a b c d.
				   if (a != (Node<T>*)NULL) {
				       a->next = c;
				   }
				   c->next = b;
				   b->next = d;

				   //Rewire the prevs so that they are traversed in d b c a ordewr now instead of d c b a.
				   c->prev = a;
				   b->prev = c;
				   if( d != (Node<T>*)NULL) {
				       d->prev = b; 
				   }
				   orderChanged = true;

				   //Now, fix up first and last in case we switched out the end or the begginning.
				   //Note only b and c "move" so these are the only two we have to check against.
				   if(this->first == b) {
					   // b used to be the first node in the list, but it switched with c thus 
					   // c is the new first.
					   this->first=c;
				   }
				   if( this->last == c) {
					   // c used to be the last node in the list, but it switched with b thus
					   // b is the new last.
					   this->last=b;
				   }
				   //Note: since c now preceeds b, it's impossible for c to be the end node or
				   //b to be the begging, so we need not test these conditions.
			       }
			   }
		           current = current->next;
			} 
		   } while(orderChanged);
		   return *this;
	    }

	    void streamIt(std::ostream& sout) {
		    Node<T>* current = this->first;
		    while ( current != (Node<T>*)NULL ) {
			sout << current->value << ((current->next != (Node<T>*)NULL) ? ", " : "");
			current = current->next;
		    }
	    }

	    void streamItBackwards(std::ostream& sout) {
		    Node<T>* current = this->last;
		    while ( current != (Node<T>*)NULL ) {
			sout << current->value << ((current->prev!= (Node<T>*)NULL) ? ", " : "");
			current = current->prev;
		    }
	    }

};

int main() {
   LinkedList<string> theList;
   LinkedList<string> theSecondList;
   
   theSecondList.append("3").append("17").append("test");
   
   theList.append("123");
   theList.append("444");
   theList.append("27");
   theList.append("41");
   theList.streamIt(cout);
   cout << endl << endl;

   cout << "BACKWARDS: ";
   theList.streamItBackwards(cout);
   cout << endl << endl;
   
   theList.removeFirstOf("27");
   theList.streamIt(cout);
   cout << endl << endl;

   cout << "BACKWARDS: ";
   theList.streamItBackwards(cout);
   cout << endl << endl;
   
   theList.removeFirstOf("41");
   theList.streamIt(cout);
   cout << endl << endl;

   cout << "BACKWARDS: ";
   theList.streamItBackwards(cout);
   cout << endl << endl;


   theList.append(theSecondList);
   theList.streamIt(cout);
   cout<< endl << endl;
   
   LinkedList<string> sortList1;

   sortList1.sort();
   cout << "Sorted empty list: ";
   sortList1.streamIt(cout);
   cout << endl << endl;

   cout << "Sorted empty list BACKWARDS: ";
   sortList1.streamItBackwards(cout);
   cout << endl << endl;

   sortList1.append("15");
   sortList1.sort();

   cout << "Sorted one item list: ";
   sortList1.streamIt(cout);
   cout << endl << endl;

   cout << "Sorted one item list BACKWARDS: ";
   sortList1.streamItBackwards(cout);
   cout << endl << endl;
   
   sortList1.append("015");
   sortList1.sort();

   cout << "Sorted two item list: ";
   sortList1.streamIt(cout);
   cout << endl << endl;

   cout << "Sorted two item list BACKWARDS: ";
   sortList1.streamItBackwards(cout);
   cout << endl << endl;

   theList.sort();
   cout << "Sorted main list: ";
   theList.streamIt(cout);
   cout << endl << endl;

   cout << "Sorted main list BACKWARDS: ";
   theList.streamItBackwards(cout);
   cout << endl << endl;
   return 0;
}

