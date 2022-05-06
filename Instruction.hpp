#pragma once

#include <iostream>
#include <map>
#include "Tokenizer.hpp"
using namespace std;
// map for opcodes
class Instruction
{
public:
    typedef std::map<std::string, int> OpMap;
    static OpMap opcodeMap;
    vector<Token> tokens;
    string opcode;
    vector<string> operands;
    string validity;
    Instruction(vector<Token> tokens);
    void printInstruction(FILE *fp);
    void printValidity(FILE *fp);
    void parse();
};