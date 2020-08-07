//Here is main function

#include <iostream>
#include <algorithm>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
#include <numeric>

using namespace std;

template<class T>
class ObjectPool {
public:
    T* Allocate(){
        if (waiting_objects.empty()) {
            T* object = new T;
            existing_objects.insert(object);
            return object;
        }
        return Retake();
    }

    T* TryAllocate() {
        if (waiting_objects.empty()) {
            return nullptr;
        }
        return Retake();
    }

    void Deallocate(T* object) {
        auto it = existing_objects.find(object);
        if (it == existing_objects.end()) {
            throw invalid_argument("Object is not exist");
        }
        waiting_objects.push(*it);
        existing_objects.erase(it);
    }

    ~ObjectPool() {
        while (!waiting_objects.empty()) {
            T* object_ptr = waiting_objects.front();
            delete object_ptr;
            waiting_objects.pop();
        }
        for (auto object_ptr : existing_objects) {
            delete object_ptr;
        }
    }
private:
    queue<T*> waiting_objects;
    set<T*> existing_objects;

    T* Retake() {
        T* object = waiting_objects.front();
        waiting_objects.pop();
        existing_objects.insert(object);
        return object;
    }
};


template<typename T>
void Swap(T* first, T* second) {
    T res = *first;
    *first = *second;
    *second = res;
}

template<typename T>
void SortPointers(vector<T*>& pointers) {
    sort(begin(pointers), end(pointers), [](T* first, T* second) {
        return *first < *second;
    });
}

template<typename T>
void ReversedCopy(T* src, size_t count, T* dst) {
    auto sourse_begin = src;
    auto sourse_end = src + count;
    auto dest_begin = dst;
    auto dest_end = dst + count;

    if (dest_begin >= sourse_end || dest_end <= sourse_begin) {
        reverse_copy(sourse_begin, sourse_end, dest_begin);
    }
    else if (dest_begin > sourse_begin) {
        for (size_t i = 0; sourse_begin + i < dest_begin; ++i) {
            *(dest_end - i - 1) = *(sourse_begin + i);
        }
        reverse(dest_begin, sourse_end);
    }
    else {
        for (size_t i = 0; dest_begin + i < sourse_begin; ++i) {
            *(dest_begin + i) = *(sourse_end - i - 1);
        }
        reverse(sourse_begin, dest_end);
    }
}

#include "tests.h"


int main()
{
    TestAll();
    std::cout << "Hello World!\n";
}
