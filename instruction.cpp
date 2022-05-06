#include "Instruction.hpp"
#include <iostream>

using namespace std;

Instruction::OpMap Instruction::opcodeMap = { 
    { "add", 3 },
    { "sub", 3 },
    { "addi", 3 },
    { "subi", 3 },
    { "la", 2 },
    { "li", 2 },
    { "ecall", 0 }
}; 
Instruction::Instruction(vector<Token> tokens)
    {
        this->tokens = tokens;
        parse();
    }

void Instruction:: printInstruction(FILE *fp)
    {
        for (Token token : tokens)
        {
            // cout << token.text << " ";
            fprintf(fp, "%s ", token.text.c_str());
        }
    }
void Instruction:: printValidity(FILE *fp)
{
    // cout<<validity<<endl;
    fprintf(fp, "%s\n", validity.c_str());
}
void Instruction :: parse()
    {
        // if line has string_literal tokan,then it is invalid
        if(tokens.size() == 0)
        {
            validity = "invalid";
            return;
        }
        for (Token token : tokens)
        {
            if (token.tType == STRING_LITERAL)
            {
                validity = "invalid";
                return;
            }
        }
        opcode = tokens[0].text;
        //check whether valid opcode
        if (opcodeMap.find(opcode) == opcodeMap.end())
        {
            validity = "invalid";
            return;
        }
        if (opcode == "ecall" && tokens.size() == 1)
        {
            validity = "valid";
            return;
        }
        if (opcode == "add" || opcode == "sub" || opcode == "addi" || opcode == "subi")
        {
            if (tokens.size() == 6 && tokens[1].tType == REGISTER &&
                tokens[2].tType == COMMA &&
                (tokens[3].tType == REGISTER || tokens[3].tType == INTEGER_LITERAL || tokens[3].tType == IDENTIFIER) &&
                tokens[4].tType == COMMA &&
                (tokens[5].tType == REGISTER || tokens[5].tType == INTEGER_LITERAL || tokens[5].tType == IDENTIFIER))
            {
                validity = "valid";
                operands.push_back(tokens[1].text);
                operands.push_back(tokens[3].text);
                operands.push_back(tokens[5].text);
                return;
            }
        }

        if (opcode == "la" || opcode == "li")
        {
            if (tokens.size() == 4 && tokens[1].tType == REGISTER &&
                tokens[2].tType == COMMA &&
                (tokens[3].tType == INTEGER_LITERAL || tokens[3].tType == IDENTIFIER || tokens[3].tType == REGISTER))
            {
                validity = "valid";
                operands.push_back(tokens[1].text);
                operands.push_back(tokens[3].text);
                return;
            }
        }
        validity = "invalid";
    }