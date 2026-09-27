#include <iostream>
#include <string>
#include <cctype>

using namespace std;

bool extractIPv4(const std::string& str, unsigned long& outAddress, int& outPort)
{
    outAddress = 0;
    outPort = -1;

    for (int i = 0; i < str.length(); i++)
    {
        if (isdigit(str[i]))
        {
            // Don't start in the middle of another token
            if (i > 0 && (isdigit(str[i - 1]) || str[i - 1] == '.' || str[i - 1] == ':'))
            {
                continue;
            }

            int j = i;
            int octets[4];
            bool valid = true;

            // Loop through all 4 octets
            for (int octet = 0; octet < 4; octet++)
            {
                int value = 0;
                int digitCount = 0;
                int octetStart = j;

                // Build the octet value character by character
                while (j < str.length() && isdigit(str[j]))
                {
                    value = value * 10 + (str[j] - '0');
                    digitCount++;
                    j++;
                }

                // Must contain 1-3 digits
                if (digitCount < 1 || digitCount > 3)
                {
                    valid = false;
                    break;
                }

                // Must be between 0 and 255
                if (value > 255)
                {
                    valid = false;
                    break;
                }

                // Cannot have a leading zero unless it is just 0
                if (digitCount > 1 && str[octetStart] == '0')
                {
                    valid = false;
                    break;
                }

                // Save this octet
                octets[octet] = value;

                // First three octets must be followed by a period
                if (octet < 3)
                {
                    if (j >= str.length() || str[j] != '.')
                    {
                        valid = false;
                        break;
                    }

                    j++; // move past the period
                }
            }
            if (!valid)
            {
                continue;
            }

            // There cannot be another period after the fourth octet
            if (j < str.length() && str[j] == '.')
            {
                continue;
            }
            // Check if a port is present
            if (j < str.length() && str[j] == ':')
            {
                j++; // move past the colon

                int portStart = j;
                int portValue = 0;
                int portDigits = 0;

                // Build the port value character by character
                while (j < str.length() && isdigit(str[j]))
                {
                    portValue = portValue * 10 + (str[j] - '0');
                    portDigits++;
                    j++;
                }

                // Port must have 1-5 digits
                if (portDigits < 1 || portDigits > 5)
                {
                    continue;
                }

                // Port must be between 0 and 65535
                if (portValue > 65535)
                {
                    continue;
                }

                // Port cannot have a leading zero unless it is just 0
                if (portDigits > 1 && str[portStart] == '0')
                {
                    continue;
                }
              

                // Port cannot be followed by another period or colon
                if (j < str.length() && (str[j] == '.' || str[j] == ':'))
                {
                    continue;
                }
                outPort = portValue;
            }

            // Build the 32-bit address from the four octets
            outAddress = ((unsigned long)octets[0] << 24)
                       | ((unsigned long)octets[1] << 16)
                       | ((unsigned long)octets[2] << 8)
                       | (unsigned long)octets[3];

            return true;
        
                  }
                }

    return false; // finishes loop without finding anything valid
}
int main()
{
    string input;

    while (true)
    {
        cout << "Enter a string (or 'END' to quit): ";
        getline(cin, input);

        if (input == "END")
        {
            cout << "Program terminated." << endl;
            break;
        }

        unsigned long address;
        int port;

        bool found = extractIPv4(input, address, port);

        // Check if a valid IPv4 address was found
        if (!found)
        {
            cout << "Invalid input: no valid IPv4 address found" << endl;
        }
        else{
            unsigned long first = (address >> 24) & 255;
            unsigned long second = (address >> 16) & 255;
            unsigned long third = (address >> 8) & 255;
            unsigned long fourth = address & 255;

            cout << "Extracted IPv4 address: "
                << first << "."
                << second << "."
                << third << "."
                << fourth
                << " (decimal value: " << address
                << ", port: ";

            if (port == -1)
            {
                cout << "none";
            }
            else
            {
                cout << port;
            }

            cout << ")" << endl;
        }
    } 
    return 0;

}