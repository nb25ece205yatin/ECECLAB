#include <iostream>

class Base {
public:
    Base() : baseData_(new int(1)) {}

    ~Base() {
        delete baseData_;
        std::cout << "Base destructor called\n";
    }

private:
    int* baseData_;
};

class Derived : public Base {
public:
    Derived() : derivedData_(new int[4]{1, 2, 3, 4}) {
        std::cout << "Derived constructed with a dynamic allocation\n";
    }

    ~Derived() {
        delete[] derivedData_;
        std::cout << "Derived destructor called; derived allocation released\n";
    }

private:
    int* derivedData_;
};

class VirtualBase {
public:
    VirtualBase() : baseData_(new int(1)) {}

    virtual ~VirtualBase() {
        delete baseData_;
        std::cout << "VirtualBase destructor called\n";
    }

private:
    int* baseData_;
};

class VirtualDerived : public VirtualBase {
public:
    VirtualDerived() : derivedData_(new int[4]{1, 2, 3, 4}) {
        std::cout << "VirtualDerived constructed with a dynamic allocation\n";
    }

    ~VirtualDerived() override {
        delete[] derivedData_;
        std::cout << "VirtualDerived destructor called; derived allocation released\n";
    }

private:
    int* derivedData_;
};

void demonstrateNonVirtualDestructorCase() {
    std::cout << "Non-virtual destructor case:\n";
    Base* abandonedBasePointer = new Derived();
    std::cout << "The base destructor is non-virtual. Deleting this base pointer "
                 "would be undefined behavior, so it is intentionally left allocated "
                 "for LeakSanitizer to report.\n";
    (void)abandonedBasePointer;
}

int main() {
    demonstrateNonVirtualDestructorCase();
    std::cout << "Virtual destructor case:\n";
    VirtualBase* safeToDelete = new VirtualDerived();
    delete safeToDelete;
    std::cout << "The derived and base destructors both ran.\n";
    return 0;
}
