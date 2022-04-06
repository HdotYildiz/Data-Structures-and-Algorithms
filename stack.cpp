#include <iostream>

using namespace std;

class StackArray
{
private:
    int* array_;
    size_t array_size_=0;
    int top_index_=-1;

public:
	StackArray(int maxsize){
		array_ = new int[maxsize];
        array_size_ = maxsize;
	}

    void push(int data){
        if(top_index_ == array_size_ - 1){
            cout << "Error: Stack overflowed. Value was not pushed.";
            return;
        }
        array_[++top_index_] = data;

        cout << top_index_ << " " << array_size_ << " \n";
    }

    void pop(){
        if(top_index_ == -1){
            cout << "Error: No element left to pop.";
            return;
        } 
        top_index_--;
    }
    
    int top(){
        if(top_index_ == -1) throw "Error: No element in stack.";

        return array_[top_index_];
    }

    bool is_empty(){
        return top_index_ == -1;
    }

    void print(){
        cout << "-s-\n";
        for(int i=0; i<=top_index_; i++)
            cout << array_[i] << " ";
        cout << "\n---\n";
    }
};

class StackLinkedList
{
private:
    struct Node
    {
        int payload;
        Node* next=nullptr;
    };
    Node* head_adr=nullptr;
public:
    void push(int data){
        Node* new_node = new Node();
        new_node->payload = data;
        new_node->next = head_adr;
        head_adr = new_node;
    }

    void pop(){
        if(head_adr == nullptr){
            cout << "Error: Nothing to pop, stack is empty";
        }

        Node* tmp = head_adr;
        head_adr = head_adr->next;
        delete tmp;
    }
    
    int top(){
        if(head_adr == nullptr) throw "Error: stack is empty";

        Node* top_node = head_adr;
        return top_node->payload;
    }

    void print(){
        Node* tmp = head_adr;

        cout << "-sll-\n";
        while(tmp != nullptr){
            cout << tmp->payload << " ";
            tmp = tmp->next;
        }
        cout << "\n---\n";
    }

    bool is_empty(){
        return head_adr == nullptr;
    }
};



int main()
{
    //StackArray a(10);
    StackLinkedList a;

    for(int i=0; i<5; i++) a.push(i*2);
    a.print();
    a.pop();
    a.print();
    cout << a.is_empty() << " " << a.top();
}