#include "test_overload_function.h"

/*
User Interface contains two types of user input controls: TextInput, which accepts all characters and NumericInput, which accepts only digits.
Implement the following methods
add on class TextInput - addds the given character to the current value
getValue on class TextInput - returns the current value
add on class NumericInput - overrides the base class method so that each non-numeric character is ignored
*/

class TextInput
{
private:
    std::string value = "";
public:
    virtual void add(char c)
    {
        value.push_back(c);
    }

    virtual std::string getValue() {
        return value;
    }
};

class NumericInput : public TextInput
{
private:
    std::string NumericValue = "";
public:
    void add(char c)
    {
        if((c >= '0') && (c <= '9'))
        NumericValue.push_back(c);
    }

    std::string getValue() {
        return NumericValue;
    }
};

/* The following code should output "10": */
int test_overload_function()
{
    TextInput* input = new NumericInput();
    input->add('1');
    input->add('a');
    input->add('0');
    std::cout << input->getValue() << endl;

    return 0;
}