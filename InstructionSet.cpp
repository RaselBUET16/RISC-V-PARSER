#include "InstructionSet.hpp"
#include <iostream>
using namespace std;

void InstructionSet::addInstruction(vector<Token> tokens)
{
    if (tokens.size() > 0)
        instructions.push_back(Instruction(tokens));
}

void InstructionSet::printInstructionSet(FILE *fp)
{
    for (Instruction instruction : instructions)
    {
        instruction.printInstruction(fp);
        instruction.printValidity(fp);
    }
}