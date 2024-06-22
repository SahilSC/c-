struct A {
    int a;
    int b;
};

int main() {
    A *a1 = new A{};
    A *a2 = new A[100];

    //just match the constructor
    delete a1;
    delete[]a2;
}