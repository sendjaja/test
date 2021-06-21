#include <test_unique_name.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

/* Implement the unique_names method. When passed two vector of names, it will return a vector containing the names that 
 * appear in either or both vectors. The returned vector should have no duplicates.
 */
std::vector<std::string> unique_names(const std::vector<std::string>& names1, const std::vector<std::string>& names2)
{
    //throw std::logic_error("Waiting to be implemented");

    std::vector<std::string> ret;
    // std::vector<std::string>::iterator ret1;
    ret.insert(ret.end(), names1.begin(), names1.end());
    ret.insert(ret.end(), names2.begin(), names2.end());
    // ret.insert(ret.end(), names1.begin(), names1.end());

    std::sort(ret.begin(), ret.end());

    for(auto element : ret)
    {
        std::cout << element << ' '; // should print Ava Emma Olivia Sophia
    }
    std::cout << std::endl;

    std::vector<std::string>::iterator uniq;
    uniq = std::unique(ret.begin(), ret.end() + 6);

    ret.resize(std::distance(ret.begin(), uniq));

    return ret;
}

int test_unique_name()
{
    std::vector<std::string> names1 = {"Ava", "Emma", "Olivia"};
    std::vector<std::string> names2 = {"Olivia", "Sophia", "Emma"};

    std::vector<std::string> result = unique_names(names1, names2);
    std::cout << std::endl;

    result.resize(std::distance(result.begin(), result.end()));

    for(auto element : result)
    {
        std::cout << element << ' '; // should print Ava Emma Olivia Sophia
        fflush(stdout);
    }

    return 0;
}