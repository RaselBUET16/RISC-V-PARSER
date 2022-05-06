#include<iostream>
#include "Instruction.hpp"
#include "Tokenizer.hpp"

using namespace std;

class InstructionSet{
public:
    vector<Instruction> instructions;
    void addInstruction(vector<Token> tokens){
        instructions.push_back(Instruction(tokens));
    }
    void printInstructionSet(){
        for(Instruction instruction:instructions){
            instruction.printInstruction();
            cout<<instruction.validity<<endl;
        }
    }
};