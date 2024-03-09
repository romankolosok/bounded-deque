#ifndef CSC242_SP24_PROJECT1_BOUNDED_QUEUE_H
#define CSC242_SP24_PROJECT1_BOUNDED_QUEUE_H
#include <iostream>
using namespace std;

template<typename Object>
class bounded_deque{
public:
    explicit bounded_deque(int n): capacity{n}, sz{0}, front{0} {
        buffer = new Object[capacity];
    }

    ~bounded_deque() {
        delete[] buffer;
    }

    bounded_deque(const bounded_deque& bd): capacity{bd.capacity}, sz{bd.sz}, front{bd.front} {
        buffer = new Object[capacity];
        for(int i = 0; i < capacity; ++i){
            buffer[i] = bd.buffer[i];
        }
    }

    bounded_deque(bounded_deque&& bd) noexcept : capacity{bd.capacity}, sz{bd.sz}, front{bd.front}, buffer{bd.buffer}{
        bd.buffer = nullptr;
        bd.sz = 0;
        bd.capacity = 0;
        bd.front = 0;
    }

    bounded_deque& operator=(bounded_deque && bd){
        if(this != &bd) {
            delete[] buffer;
            buffer = bd.buffer;
            sz = bd.sz;
            capacity = bd.capacity;
            front = bd.front;

            bd.buffer = nullptr;
            bd.sz = 0;
            bd.capacity = 0;
            bd.front = 0;
        }
        return *this;
    }

    bounded_deque& operator=(const bounded_deque& bd){
        if(this != &bd) {
            bounded_deque copy = bd;
            std::swap(*this, copy);
        }
        return *this;
    }

    void reset() {
        sz = 0;
        front = 0;
    }


    int size() const{
        return sz;
    }

    int max_size() const {
        return capacity;
    }

    bool empty() const {
        return sz == 0;
    }

    bool full() const {
        return sz == capacity;
    }

    void push_front(const Object& x){
        if(full())
            throw std::out_of_range("pushing in full deque");
        if(front == 0){
            if(sz != 0){
                front = capacity - 1;
            }
        } else {
            if(sz != 0)
                --front;
        }
        buffer[front] = x;
        ++sz;
    }

    void push_back(const Object& x) {
        if(full())
            throw std::out_of_range("pushing in full deque");
        buffer[(front+sz)%capacity] = x;
        ++sz;
    }

    Object pop_back(){
        if(empty())
            throw std::out_of_range("popping from empty deque");
        --sz;
        Object data = buffer[(front+sz)%capacity];
        return data;
    }

    Object pop_front(){
        if(empty())
            throw std::out_of_range("popping from empty deque");
        Object data = buffer[front];
        --sz;
        if(sz > 0)
            front = (front+1)%capacity;

        return data;
    }

    int front_index() const{
        return front;
    }

    void printDeque() const{
        if(empty()){
            cout << "Empty deque\n";
            return;
        }
        for(int i = 0; i < capacity; ++i){
            if(i == front)
                cout << "*" << buffer[i] << " ";
            else
                cout << buffer[i] << " ";
        }
        cout << endl;
    };

    bool operator==(bounded_deque bd){
        if(bd.sz == this->sz && this->front == bd.front && this->capacity == bd.capacity){
            for(int i = this->front; i < (this->front+this->sz)%capacity; i=(i+1)%capacity){
                if(bd[i] != this->buffer[i])
                    return false;
            }
            return true;
        } else return false;
    }

    bool operator!=(bounded_deque bd){
        return !this->operator==(bd);
    }


private:
    int sz;
    int front;
    int capacity;
    Object* buffer;

    Object& operator[](int index){
        return buffer[index];
    }

};

#endif //CSC242_SP24_PROJECT1_BOUNDED_QUEUE_H
