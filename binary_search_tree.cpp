/*
BinarySearchTree abstract data type:
    A binary tree in which for each node, the value of all the nodes in the left tree are smaller 
    and all the right higher
*/
#include <iostream>
#include <queue> // used in level order traversal

using namespace std;

class BinarySearchTree
{
private:
    struct Node
    {
        Node* left=nullptr;
        int payload=-1;
        Node* right=nullptr;
    };
    
public:
    Node* head_adr_=nullptr;

public:
    void InsertIterative(int data){
        Node* new_node = new Node();
        new_node->payload = data;

        if(head_adr_ == nullptr){
            head_adr_ = new_node;
            return;
        }
        
        Node* tmp = head_adr_;
        while(tmp->left != nullptr || tmp->right != nullptr){
            if(data > tmp->payload){
                if(tmp->right != nullptr){
                    tmp = tmp->right;
                }else{
                    tmp->right = new_node;
                    break;
                }
            }
            else{
                if(tmp->left != nullptr){
                    tmp = tmp->left;
                }else{
                    tmp->left = new_node;
                    break;
                }
            }
        }
    }

    Node* InsertRecursive(Node* root, int data){
        if(root == nullptr){
            Node* new_node = new Node();
            new_node->payload = data;
            root = new_node;
        }else if(data > root->payload){
            root->right = InsertRecursive(root->right, data);
        }else{
            root->left = InsertRecursive(root->left, data);
        }

        return root;
    }

    bool Search(Node* root, int value){
        if(root == nullptr){
            return false;
        }else if(value == root->payload){
            return true;
        }else if(value > root->payload){
            return Search(root->right, value);
        }else{
            return Search(root->left, value);
        }
    }

    Node* DeleteNode(Node* root, int data){
        if(root == nullptr) return root;
        else if(data < root->payload){
            root->left = DeleteNode(root->left, data);
        }else if(data > root->payload){
            root->left = DeleteNode(root->right, data);
        }else{
            if(root->left == nullptr && root->right == nullptr){
                delete root;
                root = nullptr;
            }else if(root->left == nullptr){
                Node* tmp = root;
                root = root->right;
                delete tmp;
            }else if(root->right == nullptr){
                Node* tmp = root;
                root = root->left;
                delete tmp;
            }else{
                Node* tmp = FindMinNode(root->right);
                root->payload = tmp->payload;
                root->right = DeleteNode(root->right, root->payload);
            }
        }

        return root;
    }

    Node* FindMinNode(Node* root){
        while(root->left != nullptr) root = root->left;
        return root;
    }

    // Time complexity of O(height)
    int GetInorderSuccessor(int value){ 
        Node* tmp = head_adr_;
        while(tmp != nullptr){
            if(value > tmp->payload){
                tmp = tmp->right;
            }else if(value < tmp->payload){
                tmp = tmp->left;
            }else{
                break;
            }
        }

        if(tmp->right != nullptr){
            return GetMinIterative(tmp->right);
        }else{
            Node* parent_node = nullptr;
            tmp = head_adr_;
            while(tmp->payload != value){
                if(value > tmp->payload){
                    tmp = tmp->right;
                }else if(value < tmp->payload){
                    parent_node = tmp;
                    tmp = tmp->left;
                }
            }

            return parent_node->payload;
        }
    }

    int GetMinRecursive(Node* root){
        if(root == nullptr){
            cout << "Tree is empty";
            return -1;
        }else if(root->left != nullptr){
            return GetMinRecursive(root->left);
        }else{
            return root->payload;
        } 
    }

    int GetMaxRecursive(Node* root){
        if(root == nullptr){
            cout << "Tree is empty";
            return -1;
        }else if(root->right != nullptr){
            return GetMaxRecursive(root->right);
        }else{
            return root->payload;
        } 
    }

    int GetMinIterative(Node* root){
        if(root == nullptr){
            cout << "Tree is empty";
            return -1;
        }

        while(root->left != nullptr) root = root->left;
        return root->payload;
    }

    int GetMaxIterative(Node* root){
        if(root == nullptr){
            cout << "Tree is empty";
            return -1;
        }

        while(root->right != nullptr) root = root->right;
        return root->payload;
    }

    // Worst case time complexity: O(N)
    int FindHeight(Node* root){
        if(root == nullptr) return -1;

        int leftheight = FindHeight(root->left);
        int rightheight = FindHeight(root->right);

        return leftheight > rightheight ? leftheight+1 : rightheight+1;
    }

    // Breadth first search: Time = O(N), Space = O(1) at best O(N) at worst "N/2"
    void LevelOrderTraversal(){
        queue<Node*> q;
        q.push(head_adr_);

        cout << "Level order traversal:" << endl;
        Node* tmp = nullptr;
        while(!q.empty()){
            tmp = q.front();
            q.pop();

            if(tmp != nullptr){
                cout << tmp->payload << " ";
                q.push(tmp->left);
                q.push(tmp->right);
            }
        }

        cout << endl;
    }

    /* Depth functions are time O(N). space = O(h) however in a linked list type tree this is N, on average it's O(log(N))*/
    void DepthOrderTraversalPreorder(Node* root){ // <read><left><right>
        if(root == nullptr) return;
        cout << root->payload << " ";

        DepthOrderTraversalPreorder(root->left);
        DepthOrderTraversalPreorder(root->right);
    }

    void DepthOrderTraversalInorder(Node* root){ // <left><read><right>
        if(root == nullptr) return;

        DepthOrderTraversalInorder(root->left);
        cout << root->payload << " ";
        DepthOrderTraversalInorder(root->right);
    }

    void DepthOrderTraversalPostorder(Node* root){ // <left><right><read>
        if(root == nullptr) return;

        DepthOrderTraversalPostorder(root->left);
        DepthOrderTraversalPostorder(root->right);
        cout << root->payload << " ";
    }

    bool CheckIfBSTIterative(){
        queue<Node*> q;
        q.push(head_adr_);

        Node* tmp = nullptr;
        Node* leftnode = nullptr;
        Node* rightnode = nullptr;
        while(!q.empty()){
            tmp = q.front();
            q.pop();

            if(tmp != nullptr){
                leftnode = tmp->left;
                rightnode = tmp->right;

                if(leftnode != nullptr){
                    if(leftnode->payload > tmp->payload)
                        return false;
                    
                    q.push(leftnode);
                }

                if(rightnode != nullptr){
                    if(rightnode->payload < tmp->payload)
                        return false;
                    
                    q.push(rightnode);
                }
            }
        }

        return true;
    }

    // Inorder traversal, using this the list should be sorted. So using prev we can find out if it is.
    int prev = 0;
    bool CheckIfBSTRecursive(Node* root){
        if(root == nullptr) return true;
        if(!CheckIfBSTRecursive(root->left)) return false;
        
        if(prev != 0 && prev >= root->payload) return false;
        prev = root->payload;
        CheckIfBSTRecursive(root->right);
    }

    // Alternative version to CheckIfBSTRecursive() 
    bool CheckIfBSTRecursiveAlternativeUtility(Node* root, int min_value, int max_value){
        if(root == nullptr) return true;
        if(root->payload > min_value &&
           root->payload < max_value &&
           CheckIfBSTRecursiveAlternativeUtility(root->left, min_value, root->payload) &&
           CheckIfBSTRecursiveAlternativeUtility(root->right, root->payload, max_value))
           return true;

        return false;
    }

    // Time complexity: O(N)
    bool CheckIfBSTRecursiveAlternative(){
        return CheckIfBSTRecursiveAlternativeUtility(head_adr_, INT32_MIN, INT32_MAX);
    }

    // Time complexity: O(N^2) very expensive method, just for demo
    bool CheckIfBSTExpensive(Node* root){ 
        if(root == nullptr) return true;
        if(IsSubtreeLesser(root->left, root->payload) &&
           IsSubtreeGreater(root->right, root->payload) &&
           CheckIfBSTExpensive(root->left) &&
           CheckIfBSTExpensive(root->right))
           return true;

        return false;
    }

    bool IsSubtreeLesser(Node* root, int value){
        if(root == nullptr) return true;
        if(root->payload < value &&
           IsSubtreeLesser(root->left, value) &&
           IsSubtreeLesser(root->right, value))
           return true;

        return false;
    }

    bool IsSubtreeGreater(Node* root, int value){
        if(root == nullptr) return true;
        if(root->payload > value &&
           IsSubtreeGreater(root->left, value) &&
           IsSubtreeGreater(root->right, value))
           return true;

        return false;
    }
};

int main()
{
    BinarySearchTree a;
    
    a.head_adr_ = a.InsertRecursive(a.head_adr_, 8);
    a.head_adr_ = a.InsertRecursive(a.head_adr_, 3);
    a.head_adr_ = a.InsertRecursive(a.head_adr_, 9);
    a.head_adr_ = a.InsertRecursive(a.head_adr_, 5);
    a.head_adr_ = a.InsertRecursive(a.head_adr_, 12);
    a.head_adr_ = a.InsertRecursive(a.head_adr_, 2);

    cout << "\n Searches: " << endl;
    cout << a.Search(a.head_adr_, 8) << " " << a.Search(a.head_adr_, 7) << endl;

    cout << "\n Min/max/height: " << endl;
    cout << a.GetMinRecursive(a.head_adr_) << " " << a.GetMaxRecursive(a.head_adr_) << endl;
    cout << a.GetMinIterative(a.head_adr_) << " " << a.GetMaxIterative(a.head_adr_) << endl;
    cout << "Height: " << a.FindHeight(a.head_adr_) << endl;

    a.LevelOrderTraversal();

    cout << "\nDOT preorder: " << endl;
    a.DepthOrderTraversalPreorder(a.head_adr_);
    cout << "\nDOT inorder: " << endl;
    a.DepthOrderTraversalInorder(a.head_adr_);
    cout << "\nDOT postorder: " << endl;
    a.DepthOrderTraversalPostorder(a.head_adr_);

    a.head_adr_->payload = 15;
    cout << "\n\nIs BST: " << a.CheckIfBSTIterative() << " rec; " << a.CheckIfBSTExpensive(a.head_adr_) << " " << a.CheckIfBSTRecursiveAlternative();
    a.head_adr_->payload = 8;
    cout << "\nIs BST: " << a.CheckIfBSTIterative() << " rec; " << a.CheckIfBSTExpensive(a.head_adr_) << " " << a.CheckIfBSTRecursiveAlternative() << endl;

    cout << "\nDelete cell: " << endl;
    a.DeleteNode(a.head_adr_, 3);
    a.DepthOrderTraversalInorder(a.head_adr_);

    a.head_adr_ = a.InsertRecursive(a.head_adr_, 7);
    a.head_adr_ = a.InsertRecursive(a.head_adr_, 6);
    a.head_adr_ = a.InsertRecursive(a.head_adr_, 1);
    cout << "\n\nInorder succesor: " << a.GetInorderSuccessor(7) << endl;
}
