#include <iostream>
#include <string>

#define NODE_T_NULL ((Node<T>*)NULL)

#ifndef __LLDEBUG__ 
#define debugLog(x) 
#endif

using namespace std;

template <class T>
class Node {
   public:
    Node<T>*next, *prev;
    T value;

    Node<T>(T t) {
        next = NODE_T_NULL;
        prev = NODE_T_NULL;
        value = t;
    }

    Node<T>(Node<T>* next, Node<T>* prev, T value) {
        this->next = next;
        this->prev = prev;
        this->value = value;
    }
   private:
    Node<T>(const Node<T>& ) {
    }
};

template <class T>
class LinkedList {
   protected:
    Node<T>*first, *last;

   public:
    static bool debug;
    LinkedList<T>() { 
        first = last = NODE_T_NULL;
    }

    ~LinkedList<T>() {
        // Individually free each node.
        Node<T>* current = this->first;
        while (current != NODE_T_NULL) {
            Node<T>* next = current->next;
            try {
                delete current;
            } catch (exception e) {
                cerr << e.what() << endl;
            }
            current = next;
        }
    }

    Node<T>* getFirst() { return first; }

    bool isEmpty() { return first == NODE_T_NULL; }

    LinkedList<T>& append(LinkedList& toAppend) {
        debugLog("append list - before");
        Node<T>* current = toAppend.first;

        while (current != NODE_T_NULL) {
            this->append(current->value);
            current = current->next;
        }
        debugLog("append list - after");
        return *this;
    }

    LinkedList<T>& append(T val) {
        debugLog("append - before");
        Node<T>* newVal = new Node<T>(val);
        if (first == (NODE_T_NULL)) {
            first = newVal;
            last = newVal;
        } else {
            last->next = newVal;
            newVal->prev = last;
            last = newVal;
        }
        debugLog("append - after");
        return *this;
    }

    LinkedList<T>& removeFirstOf(T toRemove) {
        debugLog("removeFirstOf - before");
        Node<T>* current = this->first;

        while (current != NODE_T_NULL) {
            if (current->value == toRemove) {
                remove(current);
                current = NODE_T_NULL;
            } else {
                current = current->next;
            }
        }

        debugLog("removeFirstOf - after");
        return *this;
    }

    LinkedList<T>& sort() {
        Node<T>*current, *temp;

        bool orderChanged;
        debugLog("sort - before");
        do {
            current = this->first;
            orderChanged = false;
            while (current != NODE_T_NULL) {
                temp = current->next;
                if (temp != NODE_T_NULL) {
                    if (temp->value < current->value) {
                        // The nodes are out of order switch current and
                        // current->next (nodes "b" and "c" below).
                        Node<T>*a, *b, *c, *d;
                        a = current->prev;
                        b = current;
                        c = current->next;
                        d = (current->next == NODE_T_NULL
                                 ? current->next
                                 : current->next->next);

                        // Note only b and c (the current and next items) are
                        // guaranteed to be non-null. The following code is
                        // generalized to work in all null scenarios, but we
                        // must first test for null on a and d before
                        // dereferencing them.

                        // Rewire the nexts so that they are traversed in a c b
                        // d order now, instead of a b c d.
                        if (a != NODE_T_NULL) {
                            a->next = c;
                        }

                        c->next = b;
                        b->next = d;

                        // Rewire the prevs so that they are traversed in d b c
                        // a order now instead of d c b a.
                        c->prev = a;
                        b->prev = c;
                        if (d != NODE_T_NULL) {
                            d->prev = b;
                        }
                        orderChanged = true;

                        // Now, fix up first and last in case we switched out
                        // the end or the begginning. Note only b and c "move"
                        // so these are the only two we have to check against.
                        if (this->first == b) {
                            // b used to be the first node in the list, but it
                            // switched with c thus c is the new first.
                            this->first = c;
                        }
                        if (this->last == c) {
                            // c used to be the last node in the list, but it
                            // switched with b thus b is the new last.
                            this->last = b;
                        }
                        // Note: since c now preceeds b, it's impossible for c
                        // to be the end node or b to be the beginning, so we
                        // need not test these conditions.
                    }
                }
                current = current->next;
            }
        } while (orderChanged);
        debugLog("sort - after");
        return *this;
    }

    void streamIt(std::ostream& sout) {
        Node<T>* current = this->first;
        while (current != NODE_T_NULL) {
            sout << current->value
                 << ((current->next != NODE_T_NULL) ? ", " : "");
            current = current->next;
        }
        sout.flush();
    }

    void streamItBackwards(std::ostream& sout) {
        Node<T>* current = this->last;
        while (current != NODE_T_NULL) {
            sout << current->value
                 << ((current->prev != NODE_T_NULL) ? ", " : "");
            current = current->prev;
        }
        sout.flush();
    }

    void remove(Node<T>* current) {
        Node<T>*curPrev, *curNext;
        curPrev = current->prev;
        curNext = current->next;

        if (curPrev != NODE_T_NULL) {
            curPrev->next = curNext;
        }
        if (curNext != NODE_T_NULL) {
            curNext->prev = curPrev;
        }
        if (current == this->first) {
            this->first = curNext;
        }
        if (current == this->last) {
            this->last = curPrev;
        }
        delete current;
    }

    void enqueue(T item) { 
        debugLog("enqueue - before");
        Node<T> *newNode = new Node<T>(item);
        newNode->prev=NODE_T_NULL;
        newNode->next=first;

        if( first != NODE_T_NULL ) {
            first->prev = newNode;
        }

        first=newNode;
        
        if(last==NODE_T_NULL) {
            last=newNode;
        }
        debugLog("enqueue - after");
    }

    T dequeue() {
        if( isEmpty() ) {
            throw new logic_error("Invalid dequeue request: queue is empty.");
        } 
        debugLog("dequeue - before");
        T retval = this->last->value;
        remove(this->last);
                    
        debugLog("dequeue - after");
        return retval;
    }

    void push(T item) { 
        debugLog("pop - before");
        Node<T> *newNode = new Node<T>(item);
        newNode->prev=NODE_T_NULL;
        newNode->next=first;
        first=newNode;
        if(last==NODE_T_NULL) {
            last=newNode;
        }
        debugLog("pop - after");
    }

    T pop() {
        debugLog("pop - before");
        if( isEmpty() ) {
            throw new logic_error("Invalid stack request: stack is empty.");
        }
        T retval = this->first->value;
        remove(this->first);
                    
        debugLog("pop - after");
        return retval;
    }
#ifdef __LLDEBUG__
    void debugLog(string logLabel) {
       cerr << "this: " << (long) this << endl;
       cerr << "Location: " << logLabel << endl;
       cerr << "    first: " << (long) first << endl;
       cerr << "    last:  " << (long) last << endl;
       cerr << "---------------------------" << endl;
       Node<T>*cur = first;
       while(cur != NODE_T_NULL ){
            cerr << "-> addr=" << (long)cur << ", value=" << cur->value << ", prev=" << (long)cur->prev << ", next=" << (long)cur->next << endl;
            cur = cur->next;
       }
       cerr << "==========" << endl;
    }
#endif
   private:
    LinkedList<T>(const LinkedList<T>&) {
    }
};


void printItForwardsAndBackwards(string label, LinkedList<string>& it, ostream& str) {
    str << "scenario: " << label << endl;
    str << "isEmpty() == " << it.isEmpty() << endl;
    it.streamIt(str);
    str << endl << endl;

    str << label << " BACKWARDS: " << endl;
    it.streamItBackwards(str);
    str << endl << endl;
    str << "==========" << endl;
}

int main() {
    LinkedList<string> theList;
    LinkedList<string> theSecondList;

    theSecondList.append("3").append("17").append("test");

    theList.append("123");
    theList.append("444");
    theList.append("27");
    theList.append("41");
    printItForwardsAndBackwards("theList", theList, cout);

    theList.removeFirstOf("27");
    printItForwardsAndBackwards("theList after removing 27", theList, cout);

    theList.removeFirstOf("41");
    printItForwardsAndBackwards("theList after removing 41", theList, cout);

    LinkedList<string> sortList1;

    sortList1.sort();
    printItForwardsAndBackwards("Empty sorted list", sortList1, cout);

    sortList1.append("15");
    sortList1.sort();
    printItForwardsAndBackwards("Sorted one item list", sortList1, cout);

    sortList1.append("015");
    sortList1.sort();
    printItForwardsAndBackwards("Sorted two item list", sortList1, cout);

    theList.sort();
    printItForwardsAndBackwards("Sorted main list", theList, cout);

    LinkedList<string> list2;

    cout << "push a, b, c" << endl;

    list2.push("a");
    list2.push("b"); 
    list2.push("c");

    printItForwardsAndBackwards("Stack containing a, b, c", list2, cout);
    cout << "list2 popped three times: " << list2.pop() << ", " << list2.pop() << ", " << list2.pop() << endl;
    cout << endl << endl;

    printItForwardsAndBackwards("Empty stack", list2, cout);

    LinkedList<string> list3;

    list3.enqueue("a");
    list3.enqueue("b"); 
    list3.enqueue("c");


    printItForwardsAndBackwards("Queue containing a, b, c ", list3, cout);

    cout << "Dequeue "<< list3.dequeue() << endl;

    printItForwardsAndBackwards("Queue with one dequeue call", list3, cout);
    cout << "Dequeue the rest: " << list3.dequeue() << ", " << list3.dequeue() << endl;
    
    list3.enqueue("d");
    printItForwardsAndBackwards("Queue emptied then one item added", list3, cout);
    cout << "Dequeue " << list3.dequeue() << endl;
    printItForwardsAndBackwards("Queue empty", list3, cout);

    return 0; 

};

