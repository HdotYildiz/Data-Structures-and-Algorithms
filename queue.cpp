#include <iostream>

using namespace std;

class QueueArray
{
private:
    int* array_;
    int array_size_=0;
    int head_index_=0;
    int tail_index_=-1;

public:
	QueueArray(int maxsize){
		array_ = new int[maxsize];
        array_size_ = maxsize;
	}
public:
    void push(int data){
        if(is_full()){
            printf("Full queue.");
            return;
        }
        
        tail_index_ = (tail_index_ + 1) % array_size_;
        array_[tail_index_] = data;
    }

    int pop(){
        if(is_empty()) return -1;
        head_index_ = (head_index_ + 1) % array_size_;
        return array_[head_index_];
    }

    void print(){
        if(tail_index_ < 0) return;

        cout << "-s-\n";
        for(int i=head_index_; i != tail_index_; i++ % array_size_){
            cout << array_[i] << " ";
        }
        cout << "\n---\n";
    }

    int next(){
        if(tail_index_ < 0) return -1;
        return array_[head_index_];
    }

    bool is_empty(){
        return head_index_ == tail_index_;
    }

    bool is_full(){
        return head_index_ == (tail_index_+1) && tail_index_ > 0;
    }
};

class QueueLinkedList
{
private:
    struct Node
    {
        int payload=-1;
        Node* next=nullptr;
    };
    Node* head_adr=nullptr;
    Node* tail_adr=nullptr;
public:
    void push(int data){
        Node* new_node = new Node();
        new_node->payload = data;
        new_node->next = nullptr;

        if(!is_empty()){
            tail_adr->next = new_node;
            tail_adr = new_node;
        }else{
            tail_adr = head_adr = new_node;
        }
    }

    int pop(){
        if(is_empty()) return -1;

        int top_value = head_adr->payload;

        Node* tmp = head_adr;
        head_adr = head_adr->next;
        delete tmp;

        if(head_adr == nullptr) tail_adr = nullptr;

        return top_value;
    }

    void print(){
        Node* tmp = head_adr;

        cout << "-qll-\n";
        while(tmp != nullptr){
            cout << tmp->payload << " ";
            tmp = tmp->next;
        }
        cout << "\n---\n";
    }

    int next(){
        if(head_adr == nullptr) return -1;
        return head_adr->payload;
    }

    bool is_empty(){
        return head_adr == nullptr && tail_adr == nullptr;
    }
};

int main()
{
    //QueueArray a(10);
    QueueLinkedList a;

    for(int i=0; i<6; i++) a.push(i*2);
    a.print();
    a.pop();
    a.print();
    for(int i=0; i<3; i++) a.push(i*2);
    a.print();
    cout << a.is_empty() << " " << a.next();
}