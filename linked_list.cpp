/* 
Abstract Data Type:
    Notes stored in non continues blocks of memory
    Contains two elements, the payload and link to next
    Only the adress to the head node is store in outer scope
*/

#include <iostream>
#include <stack> // Used in reverse_linked_list_stack

using namespace std;

class LinkedList
{
private:
    struct Node
    {
        int payload=-1;
        Node* next=nullptr;
    };

    Node* head_adr_ = nullptr;
public:
    Node* get_head_adr(){return head_adr_;}

    // Worst-case time complexity: O(N)
    Node* FindNodeByIndex(int n){
        Node* tmp = head_adr_;
        for(int i=1; i < n-1; i++){ // We start at i=1 because we're starting from head
            if(tmp == nullptr || tmp->next == nullptr) break; // returns last node on overflow
            tmp = tmp->next;
        }

        return tmp;
    }

    void insert(int data, int n=0){
        Node* newnode = new Node();
        newnode->payload = data;

        if(n < 2){
            newnode->next = head_adr_;
            head_adr_ = newnode;
            return;
        }

        Node* leftnode = FindNodeByIndex(n);

        newnode->next = leftnode->next;
        leftnode->next = newnode;
    };

    void Remove(int n){
        if(head_adr_ == nullptr) return;
        if(n < 2){
            Node* tmp = head_adr_;
            head_adr_ = head_adr_->next;
            delete tmp;
        }else{
            Node* leftnode = FindNodeByIndex(n);

            Node* node_to_delete = leftnode->next;
            leftnode->next = node_to_delete->next;
            delete node_to_delete;
        }
    };

    void ReverseLinkedListIterative(){
        if(head_adr_ == nullptr || head_adr_->next == nullptr) return;
        
        Node *prev_node, *curr_node, *next_node;
        prev_node = nullptr;
        curr_node = head_adr_;

        while(curr_node != nullptr){
            next_node = curr_node->next; 

            curr_node->next = prev_node;
            prev_node = curr_node;
            curr_node = next_node;
        }

        head_adr_ = prev_node;
    }

    void ReverseLinkedListRecursive(Node* prior_node){
        if(prior_node->next == nullptr){
            head_adr_ = prior_node;
            return;
        }

        Node* node = prior_node->next;
        ReverseLinkedListRecursive(node);

        node->next = prior_node;
        prior_node->next = nullptr;
    }

    void ReverseLinkedListStack(){
        //if(head_adr == nullptr) return;
        stack<Node*> s;
        Node* tmp = head_adr_;

        while(tmp != nullptr){
            s.push(tmp);
            tmp = tmp->next;
        }
        tmp = s.top();
        head_adr_ = tmp;

        while(!s.empty()){
            tmp->next = s.top();
            s.pop();
            tmp = tmp->next;
        }

        tmp->next = nullptr;
    }

    // Time complexity: O(N)
    void PrintList(){
        Node* tmp = head_adr_;

        cout << "-ll-\n";
        while(tmp != nullptr){
            cout << tmp->payload << " ";
            tmp = tmp->next;
        }
        cout << "\n---\n";
    };

    void PrintListRecursive(Node* node){
        if(node == nullptr) return;

        cout << node->payload << "\n";
        PrintListRecursive(node->next);
    }

    void PrintReversedListRecursive(Node* node){
        if(node == nullptr) return;

        PrintReversedListRecursive(node->next);
        cout << node->payload << "\n";
    }
};


int main()
{
    LinkedList a = LinkedList();

    for(int i=0; i<5; i++) a.insert(i*2);
    // a.Insert(3, 6);
    a.PrintList();
    // a.Remove(2);
    // a.PrintList();
    // a.Remove(1);
    // a.PrintList();
    // a.ReverseLinkedListIterative();
    // a.PrintList();
    //a.PrintReversedListRecursive(a.get_head_adr());
    //a.ReverseLinkedListRecursive(a.get_head_adr());
    //a.print_list();
    a.ReverseLinkedListStack();
    a.PrintList();
}

