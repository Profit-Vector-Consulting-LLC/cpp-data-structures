#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>

using namespace std;

template <class T>
class ArrayList {
   protected:
    int first, last, size;
    T *array;    

   public:
    ArrayList<T>(int size=100) { 
        first = size-1;
        last = 0; 
        this->size=size;
        array=new T[size];
    }

    ~ArrayList<T>() {
        delete [] array;
    }

    T operator[] (int i) {
        if(i>=size) {
            throw logic_error("Array out of bounds.");
        }
        return array[(i+last)%size];
    }
    
    int length() { 
        int len = 0;
        if( !isEmpty() ) {
            len = (first >= last) ? first-last+1 : size-last+first+1;
        }
        return len;
    }

    bool isEmpty() { return (first+1)%size==last; }
    bool isFull() { return size-1==length(); }

    ArrayList<T>& push(T item) {

       if( isFull() ) {
           ostringstream oss;
           oss << "push: while pushing item '" << item << "'.  The list is full."; 
           throw logic_error(oss.str());
       }
       first = (first+1)%size;
       array[first] = item;
       cerr<< "(first=" << first << ", last=" << last << ", length=" << length() << ")" <<endl;
       return *this;
    }

    T pop() {
        if(isEmpty()) {
           ostringstream oss;
           oss << "pop: while popping item at index " << first << ". The list is empty."; 
           throw logic_error(oss.str());
        }
        T retval = array[first];
        first = (first==0) ? size-1 : first-1;
        return retval;
    }

    ArrayList<T>& enqueue(T item) {
       
       if( isFull() ) {
           ostringstream oss;
           oss << "enqueue: while enqueuing item '" << item << "'. The list is full."; 
           throw logic_error(oss.str());
       }
       first = (first+1)%size;
       array[first] = item;
       cerr<< "(first=" << first << ", last=" << last << ", length=" << length() << ")" <<endl;
       return *this;
    }

    T dequeue() {
        if(isEmpty()) {
           ostringstream oss;
           oss << "dequeue: while dequeuing item at index " << last << ". The list is empty."; 
           throw logic_error(oss.str());
        }
        T retval = array[last];
        last = (last+1)%size;
        return retval;
    }
  private:
    ArrayList<T>(const ArrayList<T>&) {
    }

};

void printIt(string label, ArrayList<string>& it) {
    cout << label << ":" << endl;
    cout << "length: " << it.length() << endl;
    cout << "   ";
    for(int i=0; i<it.length(); i++) {
       cout << " '" << it[i] << "'";
    }
    cout <<endl;
    cout << "==========" << endl;
}

void printItBackwards(string label, ArrayList<string>& it) {
    cout << label << ":" << endl;
    cout << "length: " << it.length() << endl;
    cout << "   ";
    for(int i=it.length()-1; i>=0; i--) {
       cout << " '" << it[i] << "'";
    }
    cout <<endl;
    cout << "==========" << endl;
}

int main() {
    ArrayList<string> queue;
    
    try{ 
        queue.enqueue("a").enqueue("b").enqueue("c");
        printIt("Enqueued abc", queue);
        printItBackwards("Same thing backwards", queue);
        cout << endl;
        cout << queue.dequeue() << endl;
        cout << queue.dequeue() << endl;
        cout << "isEmpty == " << queue.isEmpty() << endl;
        cout << "isFull == " << queue.isFull() << endl;
        cout << queue.dequeue() << endl;
        cout << "isEmpty == " << queue.isEmpty() << endl;
        cout << "isFull == " << queue.isFull() << endl;
        cout << endl;
    } 
    catch(logic_error& e) {
        cerr << "Caught exception: " << e.what() << endl << endl;
    }

    ArrayList<string> stack;
    
    try{ 
        stack.push("a").push("b").push("c");
        printIt("Pushed abc", stack);
        printItBackwards("Same thing backwards", stack);
        cout << endl;
        cout << stack.pop() << endl;
        cout << stack.pop() << endl;
        cout << "isEmpty == " << stack.isEmpty() << endl;
        cout << "isFull == " << stack.isFull() << endl;
        cout << stack.pop() << endl;
        cout << "isEmpty == " << stack.isEmpty() << endl;
        cout << "isFull == " << stack.isFull() << endl;
        cout << endl;
    } 
    catch(logic_error& e) {
        cerr << "Caught exception: " << e.what() << endl << endl;
    }

    ArrayList<string> list;
    
    try{ 
        list.push("a").enqueue("b").push("c");
        printIt("Mixed apprach - abc", list);
        printItBackwards("Same thing backwards", list);
        cout << endl;
        cout << list.pop() << endl;
        cout << list.pop() << endl;
        cout << "isEmpty == " << list.isEmpty() << endl;
        cout << "isFull == " << list.isFull() << endl;
        cout << list.dequeue() << endl;
        cout << "isEmpty == " << list.isEmpty() << endl;
        cout << "isFull == " << list.isFull() << endl;
        cout << endl;
    } 
    catch(logic_error& e) {
        cerr << "Caught exception: " << e.what() << endl << endl;
    }


    ArrayList<string> tiny(3);
    
    try{ 
        stack.push("a").push("b").push("c");
        printIt("Pushed abc", stack);
        printItBackwards("Same thing backwards", stack);
        cout << endl;
        cout << "length() == " << stack.length() << endl;
        cout << "isEmpty == " << stack.isEmpty() << endl;
        cout << "isFull == " << stack.isFull() << endl;
        cout << stack.pop() << endl;
        cout << stack.pop() << endl;
        cout << stack.pop() << endl;
        cout << "length() == " << stack.length() << endl;
        cout << "isEmpty == " << stack.isEmpty() << endl;
        cout << "isFull == " << stack.isFull() << endl;
        cout << endl;
    } 
    catch(logic_error& e) {
        cerr << "Caught exception: " << e.what() << endl << endl;
    }


    return 0;
}
