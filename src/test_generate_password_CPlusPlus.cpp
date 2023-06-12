#include "test_generate_password_CPlusPlus.h"

// C++ program to generate all passwords for given characters
using namespace std;

// To keep track how many combination/times the generate function is being called
 int cnt;

// Recursive helper function, adds/removes characters
// until len is reached
string generate(char* arr, int i, string s, int len)
{
    // base case
    if (i == 0) // when len has been reached
    {
        // print it out
        cout << s << "\n";
        // increment the count
        cnt++;
        return s;
    }

    // iterate through the array
    for (int j = 0; j < len; j++) {

        // Create new string with next character
        // Call generate again until string has
        // reached its len
        string appended = s + arr[j];
        generate(arr, i - 1, appended, len);
    }

    return s;
}

// function to generate all possible passwords
void crack(char* arr, int len)
{
    // call for all required lengths
    for (int i = 1; i <= len; i++) {
        generate(arr, i, "", len);
    }
}

// Possible combinations = ( possible number of characters^Password length )from 1 to n
// int main(int argc, const char * argv[]) {
int test_generate_password_CPlusPlus() {
    // insert code here...
#ifdef FULL_HEX
    char arr[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
#else
    char arr[] = {'0', '1', '2', '3'};
#endif
    int len = sizeof(arr) / sizeof(arr[0]);
    crack(arr, len);

    cout << "There are = " << cnt << " combinations" << endl;
    return 0;
}
