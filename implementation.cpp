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






int cpu::decode(memory &x) {


    // Switch statement based on the opcode (first character of the instruction)

        switch (IR.content[0]) {

            case '1': {

                // Instruction: Load content from memory to register
                char temp = IR.content[1];
                string t = "R";

                string t2 = IR.content.substr(2, 2);
                t.push_back(temp);

                reg[t].content = x.cells[t2];

                // Move to the next instruction in memory
                program_counter = *(find(v1.begin(), v1.end(), program_counter) + 3);

                return 1; // Successful execution
            }





            case '4': {

                // Instruction: Move content from one register to another
                char temp1 = IR.content[2];
                char temp2 = IR.content[3];

                string t1 = "R";
                string t2 = "R";


                reg[t2].content = reg[t1].content;
                reg[t1].content = "00";

                // Move to the next instruction in memory
                program_counter = *(find(v1.begin(), v1.end(), program_counter) + 3);

                return 1; // Successful execution
            }






                

string decimal_to_binary(int x) {

    // Base case: If the decimal number is 0, return "0" in binary representation.
    if (x == 0)
        return "0";

    // Recursive case: Convert the quotient (x / 2) to binary and add the remainder (x % 2).
    // This makes the binary representation from right to left.
    return decimal_to_binary(x / 2) + to_string(x % 2);
}

void cpu::ADD(char t, string s1, string s2) {

    // Variables to store the two hexadecimal digits in the form of binary strings.
    string temp1_s1;
    string temp2_s1;
    string temp1_s2;
    string temp2_s2;

    // this Function converts hexa digits of the registers content
    // after converting every hexa digit to decimal then to binary
    // and perform  transformation on two binary strings.
    fun(s1, s2, temp1_s1, temp2_s1, temp1_s2, temp2_s2);

    // add the two  digits after converting each digit from hexa to binary.
    // to obtain complete binary numbers.
    string num1 = temp2_s1.append(temp1_s1);
    string num2 = temp2_s2.append(temp1_s2);



    // Variables for binary addition.
    int rem = 0; // Remainder
    int sum = 0; // Sum of corresponding bits
    string add; // Result of addition

    // Perform binary addition from right to left.

    for (int i = 8; i >= 0; --i) {
        sum = (int(num1[i]) - 48) + (int(num2[i]) - 48) + rem;

        // Update result and remainder based on the sum.
        if (sum == 0) {
            add.push_back('0');
            rem = 0;
        } else if (sum == 1) {
            add.push_back('1');
            rem = 0;
        } else if (sum == 2) {
            add.push_back('0');
            rem = 1;
        } else if (sum == 3) {
            add.push_back('1');
            rem = 1;
        }
    }

    // Reverse the result to obtain the correct binary addition.
    std::reverse(add.begin(), add.end());

    // Check for overflow conditions.
    if (add[0] == '1' && (num1[0] == '0' && num2[0] == '0'))
        cout << "overflow has occurred\n";
    else if (add[0] == '0' && (num1[0] == '1' && num2[0] == '1'))
        cout << "overflow has occurred\n";

    // Store the result in the specified register after converting it to hexadecimal.
    string n = "R";
    n.push_back(t);
    reg[n].content = binary_to_hexa(add);

    return;
}


// Performs bitwise OR operation on two binary strings and stores the result
