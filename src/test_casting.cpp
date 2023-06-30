#include "test_casting.h"

class B {};
class D : public B {};
class X {};

class Base
{
public:
    virtual void DoIt() = 0;    // pure virtual
    virtual ~Base() {};
};

class Foo : public Base
{
public:
    virtual void DoIt() { cout << "Foo" << endl; };
    void FooIt() { cout << "Fooing It..." << endl; }
};

class Bar : public Base
{
public :
    virtual void DoIt() { cout << "Bar" << endl; }
    void BarIt() { cout << "baring It..." << endl; }
};

void static_cast_sample() {
        D* d = new D;
        B* b = static_cast<B*>(d); // this works
        (void)b;        // silent the unused variable warning
//      X* x = static_cast<X*>(d); // ERROR - Won't compile
}

Base* CreateRandom()
{
    if( (rand()%2) == 0 )
        return new Foo;
    else
        return new Bar;
}

void dynamic_cast_sample() {
        for( int n = 0; n < 10; ++n )
            {
                Base* base = CreateRandom();

                base->DoIt();

                Bar* bar = dynamic_cast<Bar*>(base);
                Foo* foo = dynamic_cast<Foo*>(base);
                if( bar )
                    bar->BarIt();
                if( foo )
                    foo->FooIt();
            }
}

int test_casting()
{
        cout << "start casting sample code" << endl; // prints !!!Hello World!!!
        static_cast_sample();
        dynamic_cast_sample();
        printf("end casting sample code\n");
        return 0;
}
