#pragma once
#include <iostream>

using namespace std;

template <typename T>
class smartpointer {
public:
    T* word;
    int* ref_count;

    smartpointer(T* w) : word(w), ref_count(new int(1)) {
    }

    smartpointer(smartpointer<T>& other) : ref_count(other.ref_count), word(other.word) {
        (*ref_count)++;
    }

    smartpointer& operator=(smartpointer<T>& other) {
        cleanup();
        ref_count = other.ref_count;
        (*ref_count)++;
        word = other.word;
        return *this;
    }

    ~smartpointer() {
        cleanup();
    }

    int getReferenceCount() {
        cout << "Reference Count [" <<  *ref_count << "]." << endl;
        return *ref_count;
    }

    void cleanup() {
        (*ref_count)--;
        if (*ref_count == 0) {
            delete word;
            delete ref_count;
            word = nullptr;
            ref_count = nullptr;
            cout << "Deleted." << endl;
        }
    }

};


