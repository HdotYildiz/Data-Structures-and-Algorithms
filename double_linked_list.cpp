#include <iostream>

using namespace std;

class DoublyLinkedList
{
private:
    struct Node
    {
        Node* prev=nullptr;
        int payload=-1;
        Node* next=nullptr;
    };
    Node* head_adr = nullptr;
public:
    Node* get_head_adr(){return head_adr;}

    void InsertAtHead(int data){
        Node* new_node = new Node();
        new_node->payload = data;
        new_node->next = head_adr;
        new_node->prev = nullptr;

        if(head_adr != nullptr){
            head_adr->prev = new_node;
        }

        head_adr = new_node;
    }

    void InsertAtTail(int data){
        Node* new_node = new Node();
        new_node->payload = data;
        new_node->next = nullptr;

        if(head_adr == nullptr){
            new_node->prev = nullptr;
            return;
        }

        Node* tmp = head_adr;
        while(tmp->next != nullptr){
            tmp = tmp->next; 
        }

        tmp->next = new_node;
        new_node->prev = tmp;
    }

    void PrintList(){
        Node* tmp = head_adr;

        cout << "-dll-\n";
        while(tmp != nullptr){
            cout << tmp->payload << " ";
            tmp = tmp->next; 
        }
        cout << "\n---\n";
    }

    void PrintReversedIterative(Node* node){
        if(head_adr == nullptr) return;
        Node* tmp = head_adr;

        while(tmp != nullptr){
            tmp = tmp->next; 
        }

        while(tmp != nullptr){
            cout << tmp->payload << " ";
            tmp = tmp->prev;     
        }
    }

    void PrintReversedRecursive(Node* node){
        if(node == nullptr) return;

        PrintReversedRecursive(node->next);
        cout << node->payload << " ";
    }
};

int main()
{
    DoublyLinkedList a = DoublyLinkedList();

    for(int i=0; i<5; i++) a.InsertAtHead(i*2);
    a.PrintList();
    a.InsertAtTail(6);
    a.PrintList();
    a.PrintReversedRecursive(a.get_head_adr());
}