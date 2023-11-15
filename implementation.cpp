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

            case '2': {

                // Instruction: Load immediate value to register
                char temp = IR.content[1];
                string t = "R";
                t.push_back(temp);

                // Load immediate value to register
                reg[t].content = IR.content.substr(2, 2);

                // Move to the next instruction in memory
                program_counter = *(find(v1.begin(), v1.end(), program_counter) + 3);

                return 1; // Successful execution
            }

            case '3': {

                // Instruction: Store content from register to memory

                char temp = IR.content[1];
                string t = "R";

                string t2 = IR.content.substr(2, 2);
                t.push_back(temp);

                if (t2=="00"){
                    cout<<reg[t].content<<'\n';
                    cout<<"======================================================================================="
                          "=====\n";
                    program_counter = *(find(v1.begin(), v1.end(), program_counter) + 3);
                    return 1;
                }


                x.cells[t2] = reg[t].content;

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

            case '5': {

                // Instruction: Add content of two registers and store in a third register
                char temp1 = IR.content[2];
                char temp2 = IR.content[3];

                string t1 = "R";
                t1.push_back(temp1);

                string t2 = "R";
                t2.push_back(temp2);



                // Perform addition and store result in a register
                ADD(IR.content[1], reg[t1].content, reg[t2].content);

                // Move to the next instruction in memory
                program_counter = *(find(v1.begin(), v1.end(), program_counter) + 3);

                return 1; // Successful execution
            }



            case '7': {

                // Instruction: Bitwise OR operation between two registers
                char temp1 = IR.content[2];
                char temp2 = IR.content[3];

                string t1 = "R";
                t1.push_back(temp1);

                string t2 = "R";
                t2.push_back(temp2);

                // Perform bitwise OR operation and store result in a register
                OR(IR.content[1], reg[t1].content, reg[t2].content);

                // Move to the next instruction in memory
                program_counter = *(find(v1.begin(), v1.end(), program_counter) + 3);

                return 1; // Successful execution
            }

            case '8': {

                // Instruction: Bitwise AND operation between two registers
                char temp1 = IR.content[2];
                char temp2 = IR.content[3];

                string t1 = "R";
                t1.push_back(temp1);

                string t2 = "R";
                t2.push_back(temp2);

                // Perform bitwise AND operation and store result in a register
                AND(IR.content[1], reg[t1].content, reg[t2].content);

                // Move to the next instruction in memory
                program_counter = *(find(v1.begin(), v1.end(), program_counter) + 3);

                return 1; // Successful execution
            }

            case '9': {

                // Instruction: Bitwise XOR operation between two registers
                char temp1 = IR.content[2];
                char temp2 = IR.content[3];

                string t1 = "R";
                t1.push_back(temp1);

                string t2 = "R";
                t2.push_back(temp2);

                // Perform bitwise XOR operation and store result in a register
                XOR(IR.content[1], reg[t1].content, reg[t2].content);

                // Move to the next instruction in memory
                program_counter = *(find(v1.begin(), v1.end(), program_counter) + 3);

                return 1; // Successful execution
            }


            case 'A': {

                // Instruction: Rotate the content of a register to the right
                char temp1 = IR.content[1];
                int y = int(IR.content[3]) - 1;

                string t1 = "R";
                t1.push_back(temp1);

                // Perform right rotation and store result in the same register
                reg[t1].content = rotate(y, reg[t1].content);

                // Move to the next instruction in memory
                program_counter = *(find(v1.begin(), v1.end(), program_counter) + 3);

                return 1; // Successful execution
            }


            case 'B': {

                // Instruction: Conditional jump based on the equality of two registers
                string t1 = "R";
                char temp1 = IR.content[1];
                t1.push_back(temp1);

                string t2 = "R";
                t2.push_back('0');

                // Compare contents of two registers, jump if equal
                if (reg[t1].content == reg[t2].content) {

                    string n = IR.content.substr(2, 2);
                    program_counter = n;

                    return 1; // Successful execution
                }

                program_counter = *(find(v1.begin(), v1.end(), program_counter) + 3);
                return 1;

            }

            case 'C': //Halt execution
                return -1;


        }


    return 1;

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










string binary_to_hexa(string x) {

    // Initialize an empty string to store the resulting hexadecimal value.
    string temp;

    // Variables to keep track of the power count and the sum during conversion.
    int pow_count = 0;
    int sum1 = 0;

    // Convert the first 4 bits of the binary string to decimal and then to hexadecimal.
    for (int i = 3; i >= 0; --i) {
        // If the current bit is '1', add the corresponding power of 2 to the sum.
        if (x[i] == '1')
            sum1 += pow(2, pow_count) * 1;

        // Move to the next power of 2.
        ++pow_count;
    }

    // Append the hexadecimal representation of the first 4 bits to the result string.
    temp.push_back(int_to_char(sum1));

    // Reset power count and sum for the next 4 bits.
    pow_count = 0;
    sum1 = 0;

    // Convert the last 4 bits of the binary string to decimal and then to hexadecimal.
    for (int i = 7; i >= 4; --i) {
        // If the current bit is '1', add the corresponding power of 2 to the sum.
        if (x[i] == '1')
            sum1 += pow(2, pow_count) * 1;

        // Move to the next power of 2.
        ++pow_count;
    }

    // Append the hexadecimal representation of the last 4 bits to the result string.
    temp.push_back(int_to_char(sum1));

    // Return the resulting hexadecimal string.
    return temp;
}


// Performs bitwise OR operation on two binary strings and stores the result
void cpu::OR(char t, string s1, string s2) {
    // Temporary variables to store binary representations of the operands.
    string temp1_s1;
    string temp2_s1;

    string temp1_s2;
    string temp2_s2;

    // this Function converts hexa digits of the registers content
    // after converting every hexa digit to decimal then to binary
    // and perform  transformation on two binary strings.
    fun(s1, s2, temp1_s1, temp2_s1, temp1_s2, temp2_s2);

    // Concatenate the binary representations to form complete binary numbers.
    string num1 = temp2_s1.append(temp1_s1);
    string num2 = temp2_s2.append(temp1_s2);

    // Temporary variable to store the result of OR operation.
    string temp;

    // Perform bitwise OR operation on each pair of corresponding bits.
    for (int i = 0; i < 8; ++i) {
        if (num1[i] == '1' || num2[i] == '1')
            temp.push_back('1');
        else
            temp.push_back('0');
    }

    // Register identifier and register name construction.
    char temp2 = t;
    string n = "R";
    n.push_back(temp2);

    // Store the result in the specified register after converting it to hexadecimal.
    reg[n].content = binary_to_hexa(temp);
}

