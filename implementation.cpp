#include "vole.h"
#include "bits/stdc++.h"

using namespace std;



memory::memory() {

    int count1 = 48;
    int count2 = 48;
    string temp;

    // Loop over 16 rows in memory
    for (int i = 0; i <16; ++i) {

        temp.push_back(char(count1));

        // Loop over 16 columns in each row
        for (int j = 0; j <16; ++j) {

            temp.push_back(char(count2));

            // Initialize each cell in memory with "00"
            cells[temp] = "00";

            // Update the second character in the cell's address
            if (char(count2) == '9')
                count2 += 8;
            else
                ++count2;

            temp.pop_back(); // Remove the last character for the next iteration

        }

        // Update the first character in the cell's address
        if (char(count1) == '9')
            count1 += 8;
        else
            ++count1;

        count2 = 48; // Reset the second character
        temp = "";   // Reset the temporary string for the next row
    }
}






string decimal_to_binary(int x) {

    // Base case: If the decimal number is 0, return "0" in binary representation.
    if (x == 0)
        return "0";

    // Recursive case: Convert the quotient (x / 2) to binary and add the remainder (x % 2).
    // This makes the binary representation from right to left.
    return decimal_to_binary(x / 2) + to_string(x % 2);
}
