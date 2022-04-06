#include <iostream>

using namespace std;

class HeapMin
{
private:
    int* array_;
    int array_size_=0;
    size_t capacity_=0;

    int get_left_child_index(int parent_index){return parent_index*2 + 1;}
    int get_right_child_index(int parent_index){return parent_index*2 + 2;}
    int get_parent_index(int child_index){return (child_index-1) / 2;}

    bool has_left_child(int index){return get_left_child_index(index) < array_size_;}
    bool has_right_child(int index){return get_right_child_index(index) < array_size_;}
    bool has_parent(int index){return get_parent_index(index) > 0;}

    int left_child(int index){return array_[get_left_child_index(index)];}
    int right_child(int index){return array_[get_right_child_index(index)];}
    int parent(int index){return array_[get_parent_index(index)];}

    void swap(int index_one, int index_two){
        int tmp = array_[index_one];
        array_[index_one] = array_[index_two];
        array_[index_two] = tmp;
    }

    void EnsureExtraCapacity(){
        if(array_size_ == capacity_){
            capacity_ *= 2;

            int* new_array = new int[capacity_];
            for(int i=0; i<array_size_;i++){
                new_array[i] = array_[i];
            }

            delete array_;
            array_ = new_array;
        }
    }

public:
	HeapMin(int maxsize){
		array_ = new int[maxsize];
        capacity_ = maxsize;
	}

    int Peek(int index){
        if(array_size_ == 0) return -1;
        else return array_[0];
    }

    int Poll(){
        if(array_size_ == 0) return -1;
        int value = array_[0];
       
        array_[0] = array_[array_size_-1];
        array_size_--;
        HeapifyDown();

        return value;
    }

    void Add(int value){
        EnsureExtraCapacity();
        array_[array_size_] = value;
        array_size_++;

        HeapifyUp();
    }

    void HeapifyDown(){
        int index = 0;
        int child_index;

        while(has_left_child(index)){
            child_index = get_left_child_index(index);

            if(has_right_child(index) && right_child(index) < left_child(index)){
                child_index = get_right_child_index(index);
            }

            if(array_[child_index] < array_[index]){
                swap(child_index, index);
                index = child_index;
            }else{
                break;
            }
        }
    }

    void HeapifyUp(){
        int index = array_size_ - 1;
        int parent_index;

        while(has_parent(index) && parent(index) > array_[index]){
            parent_index = get_parent_index(index);
            swap(parent_index, index);
            index = parent_index;
        }
    }

    void Print(){
        cout << "-s-\n";
        for(int i=0; i<=array_size_-1; i++)
            cout << array_[i] << " ";
        cout << "\n---\n";
    }
};


int main()
{
    HeapMin a(10);

    for(int i=0; i<7; i++) a.Add(i*2);
    a.Print();
    cout << "Polled " << a.Poll() << endl;
    a.Print();
    cout << "Polled " << a.Poll() << endl;
    a.Print();
}