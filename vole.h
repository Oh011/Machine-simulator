#ifndef A2_TASK3_S17_S18_20210066_20221245_20220235_VOLE_H
#define A2_TASK3_S17_S18_20210066_20221245_20220235_VOLE_H


#include "bits/stdc++.h"
using namespace std;





// Class representing the memory of the machine.
class memory {
private:

    // Map to store cells of memory with their content.
    map<string, string> cells;

    // Vector to store the data taken to show in data input window as strings.
    vector<string> data_input;

public:

    // Constructor for memory class, initializes memory cells.
    memory();

    // Function to load memory from a file.
    void load_memory(fstream &file);


    friend class machine;
    friend class cpu;
};


// Class representing general-purpose registers.
class registers {
protected:
    // Content of the register.
    string content;

public:

    registers();

    // Function to load content into the registers.

    void load_registers(string r);


    friend class machine;
    friend class cpu;
};


// Class representing the instruction register, inheriting from the registers class.
class instruction_register : public registers {

public:
    // Constructor for the instruction_register class.
    instruction_register();

    // Function to load content into the instruction register.
    void load_instruction_registers(string r);


    friend class cpu;
};



// Class representing the central processing unit.
class cpu {

    // Map to store registers with their addresses.
    map<string, registers> reg;

    instruction_register IR;

    // Program counter, indicating the address of the next instruction.
    string program_counter;

    // Vector to store all the addresses of memory cells so the program counter uses it.
    vector<string> v1;

public:

    cpu();

    // Function to fetch an instruction from memory.

    int fetch(memory &x);

    // Function to decode an instruction and execute it.

    int decode(memory &x);

    // Function to perform addition operation.

    void ADD(char t, string s1, string s2);

    // Function to perform bitwise OR operation.

    void OR(char t, string x1, string x2);

    // Function to perform bitwise AND operation.
    void AND(char t, string x1, string x2);

    // Function to perform bitwise XOR operation.
    void XOR(char t, string x1, string x2);

    // Function to rotate a binary string to the right by a specified number of positions.
    string rotate(int y, string s1);


    friend class machine;
    friend class memory;
};


// Class representing the entire machine.

class machine {

    memory ram;

    cpu z;

public:

    // Function to load a program into memory from a file.
    void load_program(fstream &file);


    explicit machine();

    // Function to display the content of memory.
    void show();

    // Function to display a menu and interact with the user.
    void menu();

    friend class memory;
    friend class cpu;
};

// Function to convert a character to an integer.
int char_to_int(char x);

// Function to convert an integer to a character to be used by hexadecimal digits in memory ,
// registers.

char int_to_char(int x);

// Function to convert a binary string to a hexadecimal string.
string binary_to_hexa(string x);

// Function to convert a decimal integer to a binary string.
string decimal_to_binary(int x);

// this Function converts hexa digits of the registers content
// after converting every hexa digit to decimal then to binary
// and perform  transformation on two binary strings.
void fun(string s1, string s2, string &temp1_s1, string &temp2_s1, string &temp1_s2, string &temp2_s2);


#endif //A2_TASK3_S17_S18_20210066_20221245_20220235_VOLE_
