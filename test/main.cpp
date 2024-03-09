#include "bounded_queue.h"
#include <vector>

//I cannot write a directive that would work, I wrote couple of them but they fail to build the project
//I just remove color
void print_test_result(bool expr) {
    if (expr) {
        std::cout << "PASSED" << std::endl;
    } else {
        std::cout << "FAILED" << std::endl;
    }
}

int count = 1;

//debug functions
template<typename T>
void deque_push(bounded_deque<T>& bd, const vector<T>& front = {}, const vector<T>& back = {},
                bool reset = true, bool reverse = false, bool verbose = true){
    if(reset) {
        bd.reset();
    }
    cout << (verbose?"DEQUE PUSH #" + to_string(count) + " BEGIN: \n":"");
    if(verbose)
        bd.printDeque();
    cout << (verbose?"<deque size: " + to_string(bd.size())  +">\n":"");
    cout << (verbose?"<front index: " + to_string(bd.front_index()) + ">\n":"");
    if(!reverse){
        if(!front.empty()) {
            for (const auto& x: front) {
                cout << (verbose?"//Pushing " + to_string(x) + " to front\n":"");
                bd.push_front(x);
            }
            cout << (verbose?"<deque size: " + to_string(bd.size())  +">\n":"");
            cout << (verbose?"<front index: " + to_string(bd.front_index()) + ">\n":"");
        }
        if(!back.empty()) {
            for (const auto& x: back) {
                cout << (verbose?"//Pushing " + to_string(x) + " to back\n":"");
                bd.push_back(x);
            }
            cout << (verbose?"<deque size: " + to_string(bd.size())  +">\n":"");
            cout << (verbose?"<front index: " + to_string(bd.front_index()) + ">\n":"");
        }
    } else {
        if(!back.empty()) {
            for (const auto& x: back) {
                cout << (verbose?"//Pushing " + to_string(x) + " to back\n":"");
                bd.push_back(x);
            }
            cout << (verbose?"<deque size: " + to_string(bd.size())  +">\n":"");
            cout << (verbose?"<front index: " + to_string(bd.front_index()) + ">\n":"");
        }
        if(!front.empty()) {
            for (const auto& x: front) {
                cout << (verbose?"//Pushing " + to_string(x) + " to front\n":"");
                bd.push_front(x);
            }
            cout << (verbose?"<deque size: " + to_string(bd.size())  +">\n":"");
            cout << (verbose?"<front index: " + to_string(bd.front_index()) + ">\n":"");
        }
    }
    if(verbose)
        bd.printDeque();
    cout << (verbose?"DEQUE PUSH #" + to_string(count++) + " END! \n----------------------------------\n":"");
}


template<typename T>
void deque_pop(bounded_deque<T>& bd, const int& front = 0, const int& back = 0,
               bool reset = false, bool reverse = false, bool verbose = true){
    if(reset) {
        bd.reset();
    }
    cout << (verbose?"DEQUE POP #" + to_string(count) + " BEGIN: \n":"");
    if(verbose)
        bd.printDeque();
    cout << (verbose?"<deque size: " + to_string(bd.size())  +">\n":"");
    cout << (verbose?"<front index: " + to_string(bd.front_index()) + ">\n":"");
    if(!reverse){
        if(!!front) {
            for (int i = 0; i < front; ++i) {
                auto pop = bd.pop_front();
                cout << (verbose?"//Popping " + to_string(pop) + " from front\n":"");
            }
            cout << (verbose?"<deque size: " + to_string(bd.size())  +">\n":"");
            cout << (verbose?"<front index: " + to_string(bd.front_index()) + ">\n":"");
        }
        if(!!back) {
            for (int i = 0; i < back; ++i) {
                auto pop = bd.pop_back();
                cout << (verbose?"//Popping " + to_string(pop) + " from back\n":"");
            }
            cout << (verbose?"<deque size: " + to_string(bd.size())  +">\n":"");
            cout << (verbose?"<front index: " + to_string(bd.front_index()) + ">\n":"");
        }
    } else {
        if(!!back) {
            for (int i = 0; i < back; ++i) {
                auto pop = bd.pop_back();
                cout << (verbose?"//Popping " + to_string(pop) + " from back\n":"");
            }
            cout << (verbose?"<deque size: " + to_string(bd.size())  +">\n":"");
            cout << (verbose?"<front index: " + to_string(bd.front_index()) + ">\n":"");
        }
        if(!!front) {
            for (int i = 0; i < front; ++i) {
                auto pop = bd.pop_front();
                cout << (verbose?"//Popping " + to_string(pop) + " from front\n":"");
            }
            cout << (verbose?"<deque size: " + to_string(bd.size())  +">\n":"");
            cout << (verbose?"<front index: " + to_string(bd.front_index()) + ">\n":"");
        }
    }
    if(verbose)
        bd.printDeque();
    cout << (verbose?"DEQUE POP #" + to_string(count++) + " END! \n----------------------------------\n":"");
}


int main() {
    cout << "TEST creating empty deque with capacity 5: ";
    bounded_deque<int> bd(5);
    print_test_result(bd.empty() && bd.max_size() == 5 && bd.front_index() == 0);


    cout << "TEST insert from both sides: ";
    deque_push(bd, vector<int> {1,7,3}, vector<int> {5,9},true,false, false);
    print_test_result(bd.full() && bd.front_index() == 3);


    cout << "TEST insert capacity-1 front and last back: ";
    deque_push(bd, vector<int> {1,7,88, 22}, vector<int> {9}, true, false, false);
    print_test_result(bd.full() && bd.front_index() == 2);


    cout << "TEST insert capacity-1 back and last front: ";
    deque_push(bd, vector<int> {194}, vector<int> {5,9,44,12}, true, true, false);
    print_test_result(bd.full() && bd.front_index() == 4);


    cout << "TEST insert from front only: ";
    deque_push(bd, vector<int> {10,75,32,87,34},{}, true,false,false);
    print_test_result(bd.full() && bd.front_index() == 1);


    cout << "TEST insert from back only: ";
    deque_push(bd, {}, vector<int> {10,75,32,87,34}, true, false,false);
    print_test_result(bd.full() && bd.front_index() == 0);


    cout << "TEST delete 2 from front, when front -> 0 (previous deque state used): ";
    deque_pop(bd,2,0, false, false, false);
    print_test_result(bd.size() == bd.max_size()-2 && bd.front_index() == 2);


    cout << "TEST delete remaining 3 elements from back, when front -> 2 (previous deque state used): ";
    deque_pop(bd, 0,3,false, false,false);
    print_test_result(bd.empty() && bd.front_index() == 2);


    cout << "TEST push 1 front + pop 1 back, when front -> 0, size = 0: ";
    deque_push(bd,{1},{}, true, false, false);
    deque_pop(bd,0,1, false, false,false);
    print_test_result(bd.empty() && bd.front_index() == 0);


    cout << "TEST push 1 front + pop 1 front, when front -> 0, size = 0: ";
    deque_push(bd,{1},{}, true,false, false);
    deque_pop(bd,1,0, false,false,false);
    print_test_result(bd.empty() && bd.front_index() == 0);


    cout << "TEST push 1 back + pop 1 back, when front -> 0, size = 0: ";
    deque_push(bd,{},{1}, true,false, false);
    deque_pop(bd,0,1, false,false,false);
    print_test_result(bd.empty() && bd.front_index() == 0);


    cout << "TEST push 1 back + pop 1 front, when front -> 0, size = 0: ";
    deque_push(bd,{},{1}, true,false, false);
    deque_pop(bd,1,0, false, false, false);
    print_test_result(bd.empty() && bd.front_index() == 0);


    cout << "TEST pop 1 front, when front -> 4, size = full: ";
    deque_push(bd,{2,4},{1,6,7}, true,false, false);
    deque_pop(bd,1,0, false, false, false);
    print_test_result(bd.size() == 4 && bd.front_index() == 0);


    cout << "TEST scenario push front 3 + push back 2 -> pop_front all -> make same push, when front -> 0, size = 0: ";
    deque_push(bd, vector<int> {1,7,3}, vector<int> {5,9}, true,false, false);
    deque_pop(bd, 5, 0, false, false, false);
    deque_push(bd, vector<int> {1,7,3}, vector<int> {5,9}, false, false, false);
    print_test_result(bd.full() && bd.front_index() == 0);


    cout << "TEST scenario push front 3 + push back 2 -> pop_back all -> make same push, when front -> 0, size = 0: ";
    deque_push(bd, vector<int> {1,7,3}, vector<int> {5,9}, true,false, false);
    deque_pop(bd, 0, 5, false, false, false);
    deque_push(bd, vector<int> {1,7,3}, vector<int> {5,9}, false, false, false);
    print_test_result(bd.full() && bd.front_index() == 1);


    cout << "TEST scenario full deque pop 2 from both sides alternating pops and then push back 3 elements,\n when front -> 1, size = full(previous deque state used): ";
    deque_pop(bd,1, 0, false, false, false);
    deque_pop(bd,0, 1, false, false, false);
    deque_pop(bd,1, 0, false, false, false);
    deque_pop(bd,0, 1, false, false, false);
    deque_push(bd, {},{99,88,77}, false, false,false);
    print_test_result(bd.size() == bd.max_size()-1 && bd.front_index() == 3);

    cout << "TEST pop 1 front check value, from [2,1,6,7,*4] (* indicates front index): ";
    deque_push(bd,{2,4},{1,6,7}, true,false, false);
    print_test_result(bd.pop_front() == 4 && bd.front_index() == 0 && bd.size() == bd.max_size()-1);

    cout << "TEST pop 1 back check value, from [2,1,6,7,*4] (* indicates front index): ";
    deque_push(bd,{2,4},{1,6,7}, true,false, false);
    print_test_result(bd.pop_back() == 7 && bd.front_index() == 4 && bd.size() == bd.max_size()-1);

    cout << "TEST pop 1 back check value, from [1,*5,4,3,2] (* indicates front index): ";
    deque_push(bd,{1,2,3,4,5}, {}, true,false, false);
    print_test_result(bd.pop_back() == 1 && bd.front_index() == 1 && bd.size() == bd.max_size()-1);

    cout << "TEST pop 1 front check value, from [*1,2,3,4,5] (* indicates front index): ";
    deque_push(bd,{},{1,2,3,4,5}, true,false, false);
    print_test_result(bd.pop_front() == 1 && bd.front_index() == 1 && bd.size() == bd.max_size()-1);

    cout << "TEST pop front from empty deque: ";
    try {
        deque_pop(bd,1,0,true,false, false);
        print_test_result(false);
    }catch (std::out_of_range){
        print_test_result(true);
    }


    cout << "TEST pop back from empty deque: ";
    try {
        deque_pop(bd,0,1,true,false, false);
        print_test_result(false);
    }catch (std::out_of_range){
        print_test_result(true);
    }

    cout << "TEST push front to full deque: ";
    try {
        deque_push(bd,{1,1,1,1,1,1},{},true,false, false);
        print_test_result(false);
    }catch (std::out_of_range){
        print_test_result(true);
    }

    cout << "TEST push back to full deque: ";
    try {
        deque_push(bd,{},{1,1,1,1,1,1},true,false, false);
        print_test_result(false);
    }catch (std::out_of_range){
        print_test_result(true);
    }

    cout << "TEST equals(==) operator, with copy constructor: ";
    {
        deque_push(bd, {3, 7, 9, 33, 90}, {}, true, false, false);
        bounded_deque<int> bd2(bd);
        print_test_result(bd == bd2);
    }

    cout << "TEST equals(==) operator, with copy operator: ";
    {
        deque_push(bd, {3, 7, 9, 33, 90}, {}, true, false, false);
        bounded_deque<int> bd2 = bd;
        print_test_result(bd == bd2);
    }

    cout << "TEST equals(==) operator, not same deques: ";
    {
        deque_push(bd, {3, 7, 9, 33, 90}, {}, true, false, false);
        bounded_deque<int> bd2 = bd;
        deque_pop(bd2,1,0,false, false,false);
        print_test_result(!(bd == bd2));
    }

    cout << "TEST equals(==) operator, same data different front indexes: ";
    {
        deque_push(bd, {1,2,3,4,5}, {}, true, false, false);
        bounded_deque<int> bd2 = bd;
        deque_push(bd2,{1,5},{2,3,4},true,false,false);
        print_test_result(!(bd == bd2));
    }

    cout << "TEST equals(!=) operator: ";
    {
        deque_push(bd, {3, 7, 9, 33, 90}, {}, true, false, false);
        bounded_deque<int> bd2 = bd;
        deque_pop(bd2,1,0,false, false,false);
        print_test_result(bd != bd2);
    }

    cout << "TEST equals(!=) operator, same deques: ";
    {
        deque_push(bd, {3, 7, 9, 33, 90}, {}, true, false, false);
        bounded_deque<int> bd2 = bd;
        print_test_result(!(bd != bd2));
    }


    cout << "TEST copy constructor, when popping from original doesn't change copy: ";
    {
        deque_push(bd, {3, 7, 9, 33, 90}, {}, true, false, false);
        bounded_deque<int> bd2(bd);
        deque_pop(bd, 1, 0, false, false, false);
        print_test_result(bd.front_index() == 2 && bd2.front_index() == 1 && bd.size() == bd.max_size() - 1 && bd2.full());
    }

    cout << "TEST copy constructor, when popping from copy doesn't change original: ";
    {
        deque_push(bd, {3, 7, 9, 33, 90}, {}, true, false, false);
        bounded_deque<int> bd2(bd);
        deque_pop(bd2, 1, 0, false, false, false);
        print_test_result(
                bd2.front_index() == 2 && bd.front_index() == 1 && bd.full() && bd2.size() == bd2.max_size() - 1);
    }

    cout << "TEST copy constructor, when pushing(front or back) into original doesn't change copy: ";
    {
        deque_push(bd, {3, 7, 9}, {}, true, false, false);
        bounded_deque<int> bd2(bd);
        deque_push(bd, {33}, {77}, false, false, false);
        print_test_result(bd.front_index() == 2 && bd2.front_index() == 3 && bd2.size() == 3 && bd.full());
    }

    cout << "TEST copy constructor, when pushing(front or back) into copy doesn't change original: ";
    {
        deque_push(bd, {3, 7, 9}, {}, true, false, false);
        bounded_deque<int> bd2(bd);
        deque_push(bd2, {33}, {77}, false, false, false);
        print_test_result(bd2.front_index() == 2 && bd.front_index() == 3 && bd.size() == 3 && bd2.full());
    }

    cout << "TEST copy constructor, copies same number of elements, elements and order(push_back): ";
    {
        deque_push(bd, {3, 7, 9, 33, 90}, {}, true, false, false);
        bounded_deque<int> bd2(bd);
        bool flag = true;
        try{
            while(!bd.empty() && !bd2.empty()){
                if(bd.pop_back() != bd2.pop_back())
                    flag = false;
                    break;
            }
        } catch(std::out_of_range){
            flag = false;
        }
        print_test_result(flag);
    }

    cout << "TEST copy constructor, copies same number of elements, elements and order(push_front): ";
    {
        deque_push(bd, {3, 7, 9, 33, 90}, {}, true, false, false);
        bounded_deque<int> bd2(bd);
        bool flag = true;
        try{
            while(!bd.empty() && !bd2.empty()){
                if(bd.pop_front() != bd2.pop_front())
                    flag = false;
                break;
            }
        } catch(std::out_of_range){
            flag = false;
        }
        print_test_result(flag);
    }

    ////
    cout << "TEST copy operator, when popping from original doesn't change copy: ";
    {
        deque_push(bd, {3, 7, 9, 33, 90}, {}, true, false, false);
        bounded_deque<int> bd2 = bd;
        deque_pop(bd, 1, 0, false, false, false);
        print_test_result(bd.front_index() == 2 && bd2.front_index() == 1 && bd.size() == bd.max_size() - 1 && bd2.full());
    }

    cout << "TEST copy operator, when popping from copy doesn't change original: ";
    {
        deque_push(bd, {3, 7, 9, 33, 90}, {}, true, false, false);
        bounded_deque<int> bd2 = bd;
        deque_pop(bd2, 1, 0, false, false, false);
        print_test_result(
                bd2.front_index() == 2 && bd.front_index() == 1 && bd.full() && bd2.size() == bd2.max_size() - 1);
    }

    cout << "TEST copy operator, when pushing(front or back) into original doesn't change copy: ";
    {
        deque_push(bd, {3, 7, 9}, {}, true, false, false);
        bounded_deque<int> bd2 = bd;
        deque_push(bd, {33}, {77}, false, false, false);
        print_test_result(bd.front_index() == 2 && bd2.front_index() == 3 && bd2.size() == 3 && bd.full());
    }

    cout << "TEST copy operator, when pushing(front or back) into copy doesn't change original: ";
    {
        deque_push(bd, {3, 7, 9}, {}, true, false, false);
        bounded_deque<int> bd2 = bd;
        deque_push(bd2, {33}, {77}, false, false, false);
        print_test_result(bd2.front_index() == 2 && bd.front_index() == 3 && bd.size() == 3 && bd2.full());
    }

    cout << "TEST copy operator, copies same number of elements, elements and order(push_back): ";
    {
        deque_push(bd, {3, 7, 9, 33, 90}, {}, true, false, false);
        bounded_deque<int> bd2 = bd;
        bool flag = true;
        try{
            while(!bd.empty() && !bd2.empty()){
                if(bd.pop_back() != bd2.pop_back())
                    flag = false;
                break;
            }
        } catch(std::out_of_range){
            flag = false;
        }
        print_test_result(flag);
    }

    cout << "TEST copy operator, copies same number of elements, elements and order(push_front): ";
    {
        deque_push(bd, {3, 7, 9, 33, 90}, {}, true, false, false);
        bounded_deque<int> bd2 = bd;
        bool flag = true;
        try{
            while(!bd.empty() && !bd2.empty()){
                if(bd.pop_front() != bd2.pop_front())
                    flag = false;
                break;
            }
        } catch(std::out_of_range){
            flag = false;
        }
        print_test_result(flag);
    }

    cout << "TEST copy operator, self assignment: ";
    {
        bounded_deque bdcpy(bd);
        int size = bdcpy.size();
        int front = bdcpy.front_index();
        int capacity = bdcpy.max_size();
        bdcpy = bdcpy;
        print_test_result(bdcpy.size() == size && bdcpy.front_index() == front && bdcpy.max_size() == capacity);
    }

    ////


    cout << "TEST move constructor, moves all values, clears initial deque: ";
    {
        bounded_deque bdcpy(bd);
        deque_push(bdcpy, {3, 7, 9, 33, 90}, {}, true, false, false);
        int size = bdcpy.size();
        int front = bdcpy.front_index();
        int capacity = bdcpy.max_size();
        bounded_deque<int> bd2(std::move(bdcpy));
        print_test_result(bd2.size() == size && bd2.max_size() == capacity && bd2.front_index() == front &&
        bdcpy.empty() && bdcpy.max_size() == 0 && bdcpy.front_index() == 0);
    }

    cout << "TEST move operator, moves all values, clears initial deque: ";
    {
        bounded_deque bdcpy(bd);
        deque_push(bd, {3, 7, 9, 33, 90}, {}, true, false, false);
        int size = bdcpy.size();
        int front = bdcpy.front_index();
        int capacity = bdcpy.max_size();
        bounded_deque<int> bd2 = std::move(bdcpy);
        print_test_result(bd2.size() == size && bd2.max_size() == capacity && bd2.front_index() == front &&
                          bdcpy.empty() && bdcpy.max_size() == 0 && bdcpy.front_index() == 0);
    }

    cout << "TEST move operator, self assignment: ";
    {
        bounded_deque bdcpy(bd);
        int size = bdcpy.size();
        int front = bdcpy.front_index();
        int capacity = bdcpy.max_size();
        bdcpy = std::move(bdcpy);
        print_test_result(bdcpy.size() == size && bdcpy.front_index() == front && bdcpy.max_size() == capacity);
    }
}
