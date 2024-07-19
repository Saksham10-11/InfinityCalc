#include <iostream>
#include <chrono>
#include "large_int.hpp"
using namespace std;

/*
1) Constructor {long long int } <-- checked
2) Constructor {const char*[] } <-- checked
3) Constructor {string } <-- checked
4) Extraction operator <-- checked
5) Insertion operator <-- checked
6) Equality operators {==,!=} <-- checked
7) Relational operators {<,>} <-- checked
8) Relational operators {<=,>=} <-- checked
9) Private add_1 <-- checked
10) Private sub_1 <-- checked
11) Operator prefix (--,++) <-- checked
11) Private add <-- checked
12) Private sub <-- checked
13) abs function <-- checked
14) Arithmetic operator {+,-} <-- checked
15) Operator postfix {--,++} <-- checked
16) Arithmetic operator {*,/} <-- checked
17) Power operator {^} <-- checked
18) Modulus operator <-- checked
19) Supporting functions <-- checked
*/

int main()
{
    /* Different types of object intializations */
    large_int l1;                       //<-- Default initialization , initialized to zero
    large_int l2 = -45684849;           //<-- Initialization using signed or unsigned integer
    large_int l3 = l2;                  //<-- Copy constructor , copies object l2 in l3
    large_int l4 = "-8919879872878498"; //<-- Initialization using string

    /* Overloaded cin and cout operators */
    cout << "Initial value of L2 : ";
    cout << l2 << endl;
    cout << "Enter the value to store in L2 : ";
    cin >> l2;
    cout << "The value of L2 after updation : ";
    cout << l2 << endl;
    ;

    /* Pre&Post increment operators */
    ++l1;
    --l2;
    l1++;
    l2--;
    cout << "The values after corresponding increment and decrement are :" << endl;
    cout << l1 << " " << l2 << endl;

    /* Overloaded Unary {-} operator */
    large_int l5 = -l4;
    cout << "The value of l5 : ";
    cout << l5 << endl;

    /* abs function to get the absolute value of object */
    cout << "The absolute value L4 is : ";
    cout << abs(l4) << endl;

    /* Overloaded relational operators */
    cout << "The values of various comparisons : " << endl;
    cout << (l1 == l2) << endl;
    cout << (l1 != l2) << endl;
    cout << (l1 >= l2) << endl;
    cout << (l1 <= l2) << endl;
    cout << (l1 > l2) << endl;
    cout << (l1 < l2) << endl;

    /* Overloaded arithmetic operators */
    cout << "The addition of large numbers : ";
    cout << l4 + l2 << endl;
    cout << "The subtraction of large numbers : ";
    cout << l4 - l2 << endl;
    cout << "The multiplication of large numbers : ";
    cout << l4 * l2 << endl;
    cout << "The division of large numbers : ";
    cout << l4 / l2 << endl;

    /* Overloaded modulus operator  */
    cout << "The remainder when l4 is divided by l3 is : ";
    cout << l4 % l3 << endl;

    /* Overloaded coustom power operator */
    cout << "The result of the L4 raised to the power 987 is : " << endl;
    cout << (l4 ^ 987);

    /* Optimized power funciton for large_int class */
    cout << "The optimized resutl of L4 raised to the power 197 is : " << endl;

    return 0;
}