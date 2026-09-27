#include <iostream>
#include <string>
#include <cctype>

using namespace std;

bool extractIPv4(const std::string& str, unsigned long& outAddress, int& outPort)
{
    outAddress = 0;
    outPort=-1;

    for (int i = 0; i < str.length(); i++)
    {
        if (isdigit(str[i]))
        {
        // Don't start in the middle of another token
            if (i > 0 && (isdigit(str[i - 1]) || str[i - 1] == '.' || str[i - 1] == ':'))
            {
                continue;
            }
            int value =0;
            int digitCount= 0;
            int j = i;
            while (j < str.length() && isdigit(str[j])){
                value = value * 10 + (str[j] - '0');
                digitCount++;
                j++;
            }
            
            // Check that octet is not more than 3 digits
            if (digitCount > 3)
            {
                continue;
            }
            // Check that octet is between 0 and 255
            if (value > 255)
            {
                continue;
            }
            // Check for a leading zero
            if (digitCount > 1 && str[i] == '0')
            {
                continue;
            }
            // Check for a period after the first octet
            if (j >= str.length() || str[j] != '.')
            {
                continue;
            }
             // Move past the first period
            j++;

            // Save where the second octet begins
            int secondStart = j;

            int value2 = 0;
            int digitCount2 = 0;

            // Build the second octet
            while (j < str.length() && isdigit(str[j]))
            {
                value2 = value2 * 10 + (str[j] - '0');
                digitCount2++;
                j++;
            }

            // Check that second octet has 1-3 digits
            if (digitCount2 < 1 || digitCount2 > 3)
            {
                continue;
            }

            // Check that second octet is between 0 and 255
            if (value2 > 255)
            {
                continue;
            }

            // Check for a leading zero
            if (digitCount2 > 1 && str[secondStart] == '0')
            {
                continue;
            }

            // Check for a period after the second octet
            if (j >= str.length() || str[j] != '.')
            {
                continue;
            }
            // Temporary testing
            cout << "Valid first octet: " << value << endl;
            cout << "Valid second octet: " << value2 << endl;
        }

    }
    // cout << "invalid"<< endl; //remove later, used for testing
    return false; //finishes the loop wihtout finding anything valid
}

int main()
{
    string test = "a255.1.1.1";

    unsigned long address;
    int port;

    extractIPv4(test, address, port);

    return 0;
}