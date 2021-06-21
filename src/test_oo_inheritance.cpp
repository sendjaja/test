#include "test_oo_inheritance.h"
using namespace std;
/*
Object
This is the basic unit of object oriented programming. That is both data and function that operate on data are bundled as a unit called as object.

Class
When you define a class, you define a blueprint for an object. This doesn't actually define any data, but it does define what the class name means, that is, what an object of the class will consist of and what operations can be performed on such an object.

Abstraction
Data abstraction refers to, providing only essential information to the outside world and hiding their background details, i.e., to represent the needed information in program without presenting the details.

For example, a database system hides certain details of how data is stored and created and maintained. Similar way, C++ classes provides different methods to the outside world without giving internal detail about those methods and data.

Encapsulation
Encapsulation is placing the data and the functions that work on that data in the same place. While working with procedural languages, it is not always clear which functions work on which variables but object-oriented programming provides you framework to place the data and the relevant functions together in the same object.

Inheritance
One of the most useful aspects of object-oriented programming is code reusability. As the name suggests Inheritance is the process of forming a new class from an existing class that is from the existing class called as base class, new class is formed called as derived class.

This is a very important concept of object-oriented programming since this feature helps to reduce the code size.

Polymorphism
The ability to use an operator or function in different ways in other words giving different meaning or functions to the operators or functions is called polymorphism. Poly refers to many. That is a single function or an operator functioning in many ways different upon the usage is called polymorphism.

Overloading
The concept of overloading is also a branch of polymorphism. When the exiting operator or function is made to operate on new data type, it is said to be overloaded.
*/

/*
// C++ Implementation to show that a derived class
// doesn’t inherit access to private data members.
// However, it does inherit a full parent object
class A
{
public:
	int x;
protected:
	int y;
private:
	int z;
};

class B : public A
{
	// x is public
	// y is protected
	// z is not accessible from B
};

class C : protected A
{
	// x is protected
	// y is protected
	// z is not accessible from C
};

class D : private A // 'private' is default for classes
{
	// x is private
	// y is private
	// z is not accessible from D
};
*/

class person
{
private:
    char name[20];
    unsigned int id = 0;
protected:
public:
    unsigned int getID(){ return id; }
};

class student : public person
{
private:
    unsigned int studentID;
protected:
public:
    unsigned int getStudentID() { return studentID; }
};

class teacher : public person
{
private:
    unsigned int teacherID;
protected:
public:
    unsigned int getTeacherID() { return teacherID;}
};

int test_oo_inheritance()
{
    person p1; // p1 is a object
    cout << "person ID: " << p1.getID() << endl;
    return 0;
}
