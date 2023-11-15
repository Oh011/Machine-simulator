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

void cpu::AND(char t, string s1, string s2) {

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

    // Temporary variable to store the result of AND operation.
    string temp;

    // Perform bitwise AND operation on each pair of corresponding bits.
    for (int i = 0; i < 8; ++i) {
        if (num1[i] == '1' && num2[i] == '1')
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

void cpu::XOR(char t, string s1, string s2) {
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

    // Temporary variable to store the result of XOR operation.
    string temp;

    // Perform bitwise XOR operation on each pair of corresponding bits.
    for (int i = 0; i < 8; ++i) {
        if (num1[i] == num2[i])
            temp.push_back('0');
        else
            temp.push_back('1');
    }

    // Register identifier and register name construction.
    char temp2 = t;
    string n = "R";
    n.push_back(temp2);

    // Store the result in the specified register after converting it to hexadecimal.
    reg[n].content = binary_to_hexa(temp);
}


int char_to_int(char x) {
    // Use a switch statement to map each hexadecimal character to its corresponding integer value.
    switch (x) {
        case '0':
            return 0;

        case '1':
            return 1;

        case '2':
            return 2;

        case '3':
            return 3;

        case '4':
            return 4;

        case '5':
            return 5;

        case '6':
            return 6;

        case '7':
            return 7;

        case '8':
            return 8;

        case '9':
            return 9;

        case 'A':
            return 10;

        case 'B':
            return 11;

        case 'C':
            return 12;

        case 'D':
            return 13;

        case 'E':
            return 14;

        case 'F':
            return 15;

            // Handle the case where the input is not a valid hexadecimal character.
        default:
            return -1; // Return -1 to indicate an error or an invalid input.
    }
}


char int_to_char(int x) {

    // Use a switch statement to map each integer to its corresponding hexadecimal character.
    switch (x) {
        case 0:
            return '0';

        case 1:
            return '1';

        case 2:
            return '2';

        case 3:
            return '3';

        case 4:
            return '4';

        case 5:
            return '5';

        case 6:
            return '6';

        case 7:
            return '7';

        case 8:
            return '8';

        case 9:
            return '9';

        case 10:
            return 'A';

        case 11:
            return 'B';

        case 12:
            return 'C';

        case 13:
            return 'D';

        case 14:
            return 'E';

        case 15:
            return 'F';


    }
    return 0;
}


void fun(string s1, string s2, string &temp1_s1, string &temp2_s1, string &temp1_s2, string &temp2_s2) {

    // Convert the first character of the first hexa number value to a 4-bit binary string.

    temp1_s1 = decimal_to_binary(char_to_int(s1[1]));


    // Ensure that the binary string is exactly 4 bits long.
    while (temp1_s1.size() < 4)
        temp1_s1.insert(0, "0");

    while (temp1_s1.size() > 4)
        temp1_s1.erase(0, 1);



    // Convert the second character of the first hexa number value to a 4-bit binary string.
    temp2_s1 = decimal_to_binary(char_to_int(s1[0]));


    // Ensure that the binary string is exactly 4 bits long.
    while (temp2_s1.size() < 4)
        temp2_s1.insert(0, "0");

    while (temp2_s1.size() > 4)
        temp2_s1.erase(0, 1);



    // Convert the first character of the second hexa number value to a 4-bit binary string
    temp1_s2 = decimal_to_binary(char_to_int(s2[1]));



    // Ensure that the binary string is exactly 4 bits long.
    while (temp1_s2.size() < 4)
        temp1_s2.insert(0, "0");

    while (temp1_s2.size() > 4)
        temp1_s2.erase(0, 1);


    // Convert the second character of the second hexa number value to a 4-bit binary string
    temp2_s2 = decimal_to_binary(char_to_int(s2[0]));

    // Ensure that the binary string is exactly 4 bits long.
    while (temp2_s2.size() < 4)
        temp2_s2.insert(0, "0");

    while (temp2_s2.size() > 4)
        temp2_s2.erase(0, 1);
}

void machine::load_program(fstream &file) {
     ram.load_memory(file);
}

machine::machine() {

}

void machine::show() {

    // Display the data input window header.
    cout << "data input window:\n";

    // Display the data in the data input window.
    for(auto i:ram.data_input)
        cout << i << " ";

    // Display separator line.
    cout << "\n========================================================================"
            "=================\n";

    // Initialize counters.
    int count = 0;
    int count2 = 1;
    int countr = 0;

    // Display column headers and program counter (PC).
    cout << "  0   1   2   3   4   5   6   7   8   9   A   B   C   D   E   F    "
            "| PC=" << z.program_counter << "         |\n";
    ++count2;

    // Iterate over memory cells.
    for (auto i: ram.cells) {

        // Display row index.
        if (count == 0)
            cout << int_to_char(count2-2) << " ";

        // Display memory cell content.
        if (count < 16) {
            if (i.second.size() == 1)
                cout << "0" << i.second << "  ";
            else
                cout << i.second << "  ";
        }

        ++count;

        // Display Instruction Register (IR) when the first row is complete.
        if (count == 16 && count2 == 2) {
            if (z.IR.content.size() == 1)
                cout << " | IR=" << "0" << z.IR.content << "      |\n";
            else
                cout << " | IR=" << z.IR.content << "       |\n";

            count = 0;
            ++count2;
        }

            // Display register values when all rows are complete.
        else if (count == 16 && count2 > 2) {
            // Display register values.
            if (countr < 16) {
                string temp1 = "R";
                string temp2 = "R";

                temp1.push_back(int_to_char(countr));
                cout << " | " << temp1 << ":" << z.reg[temp1].content << "  ";

                ++countr;

                temp2.push_back(int_to_char(countr));
                cout << temp2 << ":" << z.reg[temp2].content << "  |\n";

                ++countr;
                count = 0;

                ++count2;
            }
                // Display an empty row when all registers have been shown.
            else {
                cout << " |               |\n";
                ++count2;
                count = 0;
            }
        }
    }

    // Display separator line.
    cout << "========================================================================"
            "=================\n";
}

int cpu::fetch(memory  &x) {

    // get the content of the memory cell pointed by the program counter
    string temp = x.cells[program_counter];

    // Continue fetching until a complete instruction is obtained not a stored data.
    while (temp.size() == 2) {
        string temp2 = temp;

        // Move the program counter to the next memory address
        program_counter = *(find(v1.begin(), v1.end(), program_counter) + 1);
        temp = x.cells[program_counter];



         //Check for the end of program
        if (temp == "00" && temp2 == "00") {
            program_counter = *(find(v1.begin(), v1.end(), program_counter) -1);
            return -1; // End of program
        }

    }

    // If a single character instruction is found,
    // get the content of the next two memory cells to form the complete instruction.

    if (temp.size() == 1) {

        // get the next two memory cells to form the complete instruction
        temp.append(x.cells[*(find(v1.begin(), v1.end(), program_counter) + 1)]);
        temp.append(x.cells[*(find(v1.begin(), v1.end(), program_counter) + 2)]);

        // Load the complete instruction into the instruction register
        IR.load_instruction_registers(temp);

        // Decode and execute the instruction
        return decode(x);
    }

    return -1;
}

void machine::menu(){

    int option;

    // Display a menu to the user asking if they want to load a program from a file
    cout<<"Do you want to load a program from a file? :\n"
          "1-yes\n"
          "0-no\n";

    // Get user input for the option
    cin >> option;

    // Validate the user input, ensuring it's either 0 or 1
    while (option != 0 && option != 1){

        cout<<"invalid option:\n";
        cout<<"enter a valid option\n";
        cout<<"1-yes\n"
              "0-no\n";

        cin >> option;
    }

    // If the user chooses not to load a program, return from the function
    if(option == 0)
        return;

        // If the user chooses to load a program
    else if (option == 1){

        fstream  file;
        string f;

        // let the user enter the name of the file
        cout<<"enter the name of the file:\n";
        cin >> f;

        // Open the file with a specified path
        file.open(R"(C:\oop\A2_Task3_ s17,s18 _20210066- 20221245 - 20220235\)" + f + ".txt");

        // Retry opening the file until it succeeds
        while (file.fail()){

            cout<<"enter the name of the right file:\n";
            cin>>f;

            file.open(R"(C:\oop\A2_Task3_ s17,s18 _20210066- 20221245 - 20220235\)" + f + ".txt");
        }

        // Load the program from the file
        load_program(file);



        // Continue running the program until the fetch returns -1
        while (z.fetch(ram)==1) {

            cout<<"do you want to show the memory and cpu register content:\n"
                  "1-yes\n"
                  "0-no\n";

            // Get user input for displaying the machine state
            cin >> option;

            if (option == 1) {

                // Display the state of the machine
                cout<<"======================================================================================="
                      "=====\n";
                show();
            }
            else
                continue;


        }

        cout<<"======================================================================================="
              "====================\n";

        cout<<"do you want to show the memory and cpu register content:\n"
              "1-yes\n"
              "0-no\n";


        if (option == 1) {

            // Display the state of the machine
            cout<<"======================================================================================="
                  "=====\n";
            show();
        }

        return;
    }
}

void memory::load_memory(fstream &file) {

    string temp;

    // Loop through each memory cell in the 'cells' map
    for (auto &i : cells) {

        // Read the content from the file into the 'temp' variable
        file >> temp;

        // Store the content of each string in the file in a separate vector 'data_input'
        //to use it in data input window
        data_input.push_back(temp);

        if (temp.size()==3)
            cells[i.first] = temp.substr(2, 1);

        // Update the content of the memory cell, taking only the last two characters of 'temp'
        //  because the file contains hexadecimal values, and only the last two characters are used

        else
            cells[i.first] = temp.substr(2, 2);

        // Break the loop if the end of the file is reached
        if (file.eof())
            break;
    }
}
