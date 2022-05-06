#pragma once

#include<iostream>
#include "Instruction.hpp"
#include "Tokenizer.hpp"

using namespace std;

class InstructionSet{
public:
    vector<Instruction> instructions;
    void addInstruction(vector<Token> tokens);
    void printInstructionSet(FILE *fp);
};