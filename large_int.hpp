#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

/* NON-CLASS FUNCTION FOR PROPER EXECUTION */
string add_allvec(vector<vector<int>> &v)
{
    vector<int> result = *(v.end() - 1);
    for (int i = v.size() - 2; i >= 0; --i)
    {
        int sum, carry = 0, idx = 0;
        for (idx; idx < v[i].size(); ++idx)
        {
            sum = result[idx] + v[i][idx];
            result[idx] = (sum + carry) % 10;
            carry = (sum + carry) / 10;
        }
        while (carry > 0)
        {
            if (idx == result.size())
            {
                result.push_back(carry);
                break;
            }
            else
            {
                sum = result[idx] + carry;
                result[idx] = sum % 10;
                carry = sum / 10;
                ++idx;
            }
        }
    }
    string digits;
    for (auto i = result.rbegin(); i != result.rend(); ++i)
    {
        digits.push_back(char(*i + '0'));
    }
    return digits;
}

void str_to_ull(unsigned long long int &num, const string &str)
{
    num = int(*str.begin() - '0');
    for (auto it = str.begin() + 1; it != str.end(); ++it)
    {
        num = num * 10 + int(*it - '0');
    }
}

// Creating the large int class
class large_int
{
private:
    vector<int> num;
    int size;
    char sign;
    string digits;

    /* OVERLOADING INPUT AND OUTPUT OPERATORS */
    friend ostream &operator<<(ostream &, const large_int &);
    friend istream &operator>>(const istream &, large_int &);

    /* OVERLOADING EQUALITY AND RELATIONAL OPERATORS */
    friend bool operator==(const large_int &, const large_int &);
    friend bool operator!=(const large_int &, const large_int &);
    friend bool operator>(const large_int &, const large_int &);
    friend bool operator<(const large_int &, const large_int &);
    friend bool operator>=(const large_int &, const large_int &);
    friend bool operator<=(const large_int &, const large_int &);

    /* OVERLOADING ARITHMETIC OPERATORS */
    friend large_int operator+(const large_int &, const large_int &);
    friend large_int operator-(const large_int &, const large_int &);
    friend large_int operator*(const large_int &, const large_int &);
    friend large_int operator/(const large_int &, const large_int &);
    friend large_int operator%(const large_int &, const large_int &);
    friend large_int operator^(const large_int &, const large_int &);

    /* ADDITIONAL FRIEND FUNCTIONS */
    friend large_int abs(const large_int &);

    /* SUPPORTING FUNCTIONS */
    void add_1()
    {
        int sum = 0;
        for (int i = 0; i < size; ++i)
        {
            sum = num[i] + 1;
            if (sum == 10)
            {
                num[i] = 0;
                continue;
            }
            num[i] = sum;
            sum = 0;
            break;
        }
        if (sum)
        {
            num.push_back(1);
            size += 1;
        }
        digits = "";
        for (auto idx = num.rbegin(); idx != num.rend(); ++idx)
        {
            digits.push_back(char(*idx + '0'));
        }
    }

    void sub_1()
    {
        int diff, carry = 0, idx = 0;
        while (idx < size)
        {
            diff = num[idx] - 1;
            if (diff >= 0)
            {
                num[idx] = diff;
                break;
            }
            num[idx] = diff + 10;
            ++idx;
        }
        if (*(num.end() - 1) == 0)
        {
            if (size > 1)
            {
                num.pop_back();
            }
            size -= 1;
        }
        digits = "";
        for (auto idx = num.rbegin(); idx != num.rend(); ++idx)
        {
            digits.push_back(char(*idx + '0'));
        }
    }

    // Defining add as const member function as it dose not modify the object on which it is called
    string add(const large_int &obj) const
    {
        string str;
        vector<int> v = num;
        int sum, carry = 0, idx = 0;
        for (idx; idx < obj.num.size(); ++idx)
        {
            sum = v[idx] + obj.num[idx];
            v[idx] = (sum + carry) % 10;
            carry = (sum + carry) / 10;
        }
        while (carry > 0)
        {
            if (idx == v.size())
            {
                v.push_back(carry);
                break;
            }
            else
            {
                sum = v[idx] + carry;
                v[idx] = sum % 10;
                carry = sum / 10;
                ++idx;
            }
        }
        for (auto i = v.rbegin(); i != v.rend(); ++i)
        {
            str.push_back(char(*i + '0'));
        }
        return str;
    }

    // Defining sub as const member function as it dose not modify the object on which it is called
    string sub(const large_int &obj) const
    {
        string str;
        vector<int> v = num;
        int diff, carry = 0, idx = 0;
        for (idx; idx < obj.num.size(); ++idx)
        {
            diff = v[idx] - obj.num[idx];
            if ((diff + carry) < 0)
            {
                v[idx] = diff + carry + 10;
                carry = -1;
            }
            else
            {
                v[idx] = diff + carry;
                carry = 0;
            }
        }
        if (carry == -1)
        {
            v[idx] += carry;
        }
        for (int i = v.size() - 1; i > 0; --i)
        {
            if (v[i] != 0)
            {
                break;
            }
            v.pop_back();
        }
        for (auto i = v.rbegin(); i != v.rend(); ++i)
        {
            str.push_back(char(*i + '0'));
        }
        return str;
    }

public:
    // Initializing a default constructor
    large_int()
    {
        num = {0};
        size = 0;
        digits = "0";
        sign = '+';
    }

    /* Overloading different types for constructor */

    // Defining a copy constuctor
    large_int(const large_int &obj)
    {
        num = obj.num;
        size = obj.size;
        sign = obj.sign;
        digits = obj.digits;
    }

    // Constructor to initialize the object using string
    large_int(const string &s_in)
    {
        string s = s_in;
        bool isDigit = true;
        // Checking if the string entered is a valid one
        if (s[0] == '-' || s[0] == '+' || (s[0] >= '0' && s[0] <= '9'))
        {
            if (s[0] == '-')
            {
                sign = '-';
                s.erase(s.begin());
            }
            else if (s[0] == '+')
            {
                sign = '+';
                s.erase(s.begin());
            }
            else
            {
                sign = '+';
            }
        }
        else
        {
            isDigit = false;
        }
        for (int i = 0; i < s.length(); ++i)
        {
            if (!(s[i] >= '0' && s[i] <= '9'))
            {
                isDigit = false;
            }
        }
        if (!isDigit)
        {
            cerr << "Invalid input..";
            exit(1);
        }
        for (auto i = s.rbegin(); i != s.rend(); ++i)
        {
            num.push_back(int((*i) - '0'));
        }
        size = num.size();
        digits = s;
    }

    // Using the delegating constructor
    large_int(const char *s_in) : large_int(string(s_in)) {}

    // Constructor to initialize the object using signed int
    large_int(long long int n)
    {
        int digit;
        string str;
        sign = (n >= 0) ? '+' : '-';
        n = abs(n);
        while (n)
        {
            digit = n % 10;
            num.push_back(digit);
            str.push_back(char(digit + '0'));
            n /= 10;
        }
        reverse(str.begin(), str.end());
        digits = str;
        size = num.size();
    }

    /* OVERLOADING PREFIX INCREMENT AND DECREMENT */
    large_int &operator++()
    {
        if (sign == '+')
        {
            add_1();
        }
        else
        {
            if (digits == "0")
            {
                sign = '+';
                digits = "1";
                num = {1};
                size = 1;
            }
            else
            {
                sub_1();
            }
        }
    }

    large_int &operator--()
    {
        if (sign == '-')
        {
            add_1();
        }
        else
        {
            if (digits == "0")
            {
                sign = '-';
                num = {1};
                size = 1;
                digits = "1";
            }
            else
            {
                sub_1();
            }
        }
    }

    /* OVERLOADING POSTFIX INCREMENT AND DECREMENT */
    large_int operator++(int)
    {
        large_int temp = *this;
        ++*this;
        return temp;
    }

    large_int operator--(int)
    {
        large_int temp = *this;
        ++*this;
        return temp;
    }

    /* OVERLOADING URNARY OPERATORS */
    large_int operator-()
    {
        large_int temp;
        if (sign == '+')
        {
            temp = '-' + digits;
        }
        else
        {
            temp = digits;
        }
        return temp;
    }
};

/* DEFINATION OF EXTRA FUNCTIONS */
large_int abs(const large_int &obj)
{
    large_int temp = obj.digits;
    return temp;
}

/* DEFINATION OF IN/OUT OVERLOADED OPERATORS */
ostream &operator<<(ostream &os, const large_int &obj)
{
    string disp_str = obj.digits;
    if (obj.sign == '-')
    {
        disp_str = '-' + disp_str;
    }
    os << disp_str;
    return os;
}

istream &operator>>(istream &is, large_int &obj)
{
    string temp;
    is >> temp;
    // Checking if the read was sucessfull else giving the default state to the object
    if (is)
    {
        large_int obj_new(temp);
        obj = obj_new;
    }
    else
    {
        obj = large_int();
    }
    return is;
}

/* DEFINATION OF EQUALITY AND RELATIONAL OPERATORS */
bool operator==(const large_int &obj1, const large_int &obj2)
{
    return obj1.digits == obj2.digits && obj1.sign == obj2.sign;
}

bool operator!=(const large_int &obj1, const large_int &obj2)
{
    return !(obj1 == obj2);
}

bool operator>(const large_int &obj1, const large_int &obj2)
{
    if (obj1.sign == obj2.sign)
    {
        if (obj1.size == obj2.size)
        {
            if (obj1.sign == '+')
            {
                return obj1.digits > obj2.digits;
            }
            else
            {
                return obj1.digits < obj2.digits;
            }
        }
        else
        {
            if (obj1.sign == '+')
            {
                return obj1.size > obj2.size;
            }
            else
            {
                return obj1.size < obj2.size;
            }
        }
    }
    else
    {
        if (obj1.sign == '-')
        {
            return false;
        }
        else
        {
            return true;
        }
    }
}

bool operator<(const large_int &obj1, const large_int &obj2)
{
    return !(obj1 > obj2 || obj1 == obj2);
}

bool operator<=(const large_int &obj1, const large_int &obj2)
{
    return (obj1 < obj2) || (obj1 == obj2);
}

bool operator>=(const large_int &obj1, const large_int &obj2)
{
    return (obj1 > obj2) || (obj1 == obj2);
}

/* DEFINATION OF ARITHMETIC OPERATORS */
large_int operator+(const large_int &obj1, const large_int &obj2)
{
    large_int temp;
    if (obj1.sign == obj2.sign)
    {
        if (obj1.sign == '+')
        {
            if (obj1 > obj2)
            {
                temp = obj1.add(obj2);
            }
            else
            {
                temp = obj2.add(obj1);
            }
        }
        else
        {
            if (obj1 < obj2)
            {
                temp = '-' + obj1.add(obj2);
            }
            else
            {
                temp = '-' + obj2.add(obj1);
            }
        }
    }
    else
    {
        if (abs(obj1) > abs(obj2))
        {
            if (obj1.sign == '-')
            {
                temp = '-' + obj1.sub(obj2);
            }
            else
            {
                temp = obj1.sub(obj2);
            }
        }
        else
        {
            if (obj2.sign == '-')
            {
                temp = '-' + obj2.sub(obj1);
            }
            else
            {
                temp = obj2.sub(obj1);
            }
        }
    }
    return temp;
}

large_int operator-(const large_int &obj1, const large_int &obj2)
{
    large_int temp;
    if (obj1.sign == obj2.sign)
    {
        if (obj1.sign == '+')
        {
            if (obj1 > obj2)
            {
                temp = obj1.sub(obj2);
            }
            else
            {
                temp = '-' + obj2.sub(obj1);
            }
        }
        else
        {
            if (abs(obj1) < abs(obj2))
            {
                temp = obj2.sub(obj1);
            }
            else
            {
                temp = '-' + obj1.sub(obj2);
            }
        }
    }
    else
    {
        if (abs(obj1) > abs(obj2))
        {
            if (obj1.sign == '-')
            {
                temp = '-' + obj1.add(obj2);
            }
            else
            {
                temp = obj1.add(obj2);
            }
        }
        else
        {
            if (obj2.sign == '-')
            {
                temp = obj2.add(obj1);
            }
            else
            {
                temp = '-' + obj2.add(obj1);
            }
        }
    }
    return temp;
}

large_int operator*(const large_int &obj1, const large_int &obj2)
{
    vector<vector<int>> to_add;
    const large_int *big, *small;
    if (obj1.size > obj2.size)
    {
        big = &obj1;
        small = &obj2;
    }
    else
    {
        big = &obj2;
        small = &obj1;
    }
    int value, product, carry;
    for (int idx = 0; idx < (*small).size; ++idx)
    {
        vector<int> vec_temp;
        for (int j = 0; j < idx; ++j)
        {
            vec_temp.push_back(0);
        }
        carry = 0;
        for (int i = 0; i < (*big).size; ++i)
        {
            product = (*big).num[i] * (*small).num[idx];
            value = product + carry;
            vec_temp.push_back(value % 10);
            carry = value / 10;
        }
        if (carry)
        {
            vec_temp.push_back(carry);
        }
        to_add.push_back(vec_temp);
    }
    string result = add_allvec(to_add);
    large_int temp;
    if (obj1.sign == obj2.sign)
    {
        temp = result;
    }
    else
    {
        temp = '-' + result;
    }
    return temp;
}

large_int operator/(const large_int &obj1, const large_int &obj2)
{
    large_int temp;
    unsigned long long int divisor;
    str_to_ull(divisor, obj2.digits);
    string result;
    if (obj1.size < obj2.size)
    {
        result.push_back('0');
    }
    else
    {
        int index = 0;
        long long unsigned dividend = int(obj1.digits[index] - '0');
        while (dividend < divisor)
        {
            ++index;
            dividend = dividend * 10 + int(obj1.digits[index] - '0');
        }
        result += char(dividend / divisor + '0');
        ++index;
        while (index < obj1.size)
        {
            dividend = (dividend % divisor) * 10 + int(obj1.digits[index] - '0');
            result += char(dividend / divisor + '0');
            ++index;
        }
    }
    if (obj1.sign == obj2.sign || result == "0")
    {
        temp = result;
    }
    else
    {
        temp = '-' + result;
    }
    return temp;
}

large_int operator%(const large_int &obj1, const large_int &obj2)
{
    large_int temp;
    unsigned long long int dividend = 0, divisor = 0, remainder = 0;
    str_to_ull(divisor, obj2.digits);
    if (obj1.size < obj2.size)
    {
        str_to_ull(dividend, obj1.digits);
        remainder = dividend % divisor;
    }
    else
    {
        int index = 0;
        dividend = int(obj1.digits[index] - '0');
        while (dividend < divisor)
        {
            ++index;
            dividend = dividend * 10 + int(obj1.digits[index] - '0');
        }
        ++index;
        while (obj1.size > index)
        {
            dividend = (dividend % divisor) * 10 + int(obj1.digits[index] - '0');
            index++;
        }
        remainder = dividend % divisor;
    }
    if (obj1.sign == obj2.sign)
    {
        temp = remainder;
    }
    else
    {
        temp = remainder;
        temp = abs(obj2) - remainder;
    }
    return temp;
}

/* Defination of the power operator */
large_int operator^(const large_int &obj1, const large_int &obj2)
{
    large_int result = 1;
    for (large_int i = 1; i <= obj2; ++i)
    {
        result = result * obj1;
    }
    return result;
}

/* OVERLOADING THE FASTER POWER OPERATOR*/
large_int operator^(const large_int &obj, unsigned long long int &num)
{
    large_int result = 1;
    for (unsigned long long int i = 0; i < num; ++i)
    {
        result = result * obj;
    }
    return result;
}