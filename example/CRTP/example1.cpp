#include <iostream>

using namespace std;

class Base {
public:
    virtual ~Base() {}
    virtual void Show() const = 0;
};

template <typename T>
class BaseCRTP : public Base {
public:
    void Show() const override final {
        showImpl();
        static_cast<const T&>(*this).showImpl();
    }

private:
    void showImpl() const {
        cout << "Base" << endl;
    }
};

class Derived : public BaseCRTP<Derived> {
    friend class BaseCRTP<Derived>;

private:
    void showImpl() const {
        cout << "Derived" << endl;
    }
};

void f(Base* b) {
    b->Show();
}

int main() {
    Derived d;
    d.Show();
    f(&d);

    return 0;
}
