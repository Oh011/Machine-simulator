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
