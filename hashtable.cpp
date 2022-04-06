#include <iostream>
#include <list>
#include <tuple>

using namespace std;

class HashTable
{
private:
    list<tuple<string, int>>* array_;
    int max_size_=0;

public:
	HashTable(int maxsize){
		array_ = new list<tuple<string, int>>[maxsize];
        max_size_ = maxsize;
	}

    int GetHashcode(string key){
        int ascii_sum = 0; 
        for(char c: key){
            ascii_sum += (int)c;
        }

        return ascii_sum;
    }

    int hashcode_to_index(int hashcode){
        return hashcode%max_size_;
    }

    int hash(string key){
        int hashcode = GetHashcode(key);
        return hashcode_to_index(hashcode);
    }

    void put(string key, int value){
        int index = hash(key);
        auto ll = array_[index];

        // Replace value if key is already present
        bool already_present = false;
        for(auto& n : ll) {
            if(get<0>(n) == key){
                already_present = true;
                get<1>(n) = value;
            }
        }

        if(!already_present){
            ll.push_front(tuple<string, int>(key, value));
        }
        
        array_[index] = ll;
    }

    int GetValue(string key){
        auto ll = array_[hash(key)];

        for(auto n : ll) {
            if(get<0>(n) == key)
                return get<1>(n);
        }

        return -1;
    }

    void Print(){
        cout << "-ht-\n";
        for(int i=0; i<=max_size_-1; i++){
            cout << i << "\n";
            for(auto n : array_[i])
                cout << get<0>(n) << " - " << get<1>(n) << " | ";

            cout << endl;
        }

        cout << "\n---\n";
    }
};

int main()
{
    HashTable a(10);

    a.put("Dennis", 10);
    a.put("Dave", 15);
    a.put("Flenis", 20);
    a.put("Daan", 25);
    a.put("Dave", 16);

    a.Print();

    cout << "Daan: " << a.GetValue("Daan") << endl;
    cout << "Dave: " << a.GetValue("Dave") << endl;
    cout << "Dennis: " << a.GetValue("Dennis") << endl;
}