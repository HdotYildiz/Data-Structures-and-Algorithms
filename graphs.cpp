#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <queue>

using namespace std;

class Graph
{
private:
    map<string, vector<string>> nodes_; // Adjecency List
    
public:
    void AddNode(const string& name, vector<string> edges){
        nodes_[name] = edges;
    }

    void PrintAdjecencyList(){
        for(const auto& node: nodes_) {
            cout << node.first << " = ";
            for(const string& edge: node.second){
                cout << edge << " ";
            }
            cout << endl;
        }
    }

    // Breadth First Search
    bool BFS(const string& head, const string& target){
        map<string, bool> visited_flags; // Used to check for hit notes in case of cycles
        for(const auto& node: nodes_)
            visited_flags[node.first] = false;

        queue<string> bf; 
        bf.push(head);

        while(!bf.empty()){
            for(const string& n: nodes_[bf.front()]){
                if(n == target) return true;
                if(!visited_flags[n]) bf.push(n);
            }
            bf.pop();
        }

        return false;
    }

    // Depth First Search
    bool InfixSearch(const string& head, const string& target){
        if(head == target) return true;

        for(const string& edge: nodes_[head]){
            if(InfixSearch(edge, target))
                return true;
        }

        return false;
    }
};

int main(){
    Graph g;
    g.AddNode("A", {"B", "C"});
    g.AddNode("B", {"C"});
    g.AddNode("C", {});
    g.PrintAdjecencyList();

    cout << "C is reachable from A: " << g.InfixSearch("A", "C") << " DFS|BFS " << g.BFS("A", "C") << endl;
    cout << "A is reachable from C: " << g.InfixSearch("C", "A") << " DFS|BFS " << g.BFS("C", "A") << endl;
    cout << "D is reachable from A: " << g.InfixSearch("A", "D") << " DFS|BFS " << g.BFS("A", "D") << endl;
}