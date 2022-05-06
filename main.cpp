#include "Tokenizer.hpp"
#include "InstructionSet.hpp"
#include<iostream>

using namespace std;
void printVector(vector<Token> tokens)
{
    for(Token currToken : tokens)
    {
        cout<<sTokenTypeStrings[currToken.tType]<<" ";;
    }
    cout<<endl;
}
int main( int argc, char* argv[] )
{
    FILE *fp = fopen(argv[0], "r");
    if(fp == NULL)
    {
        cout<<"File not found"<<endl;
        return 0;
    }
    //read line of the file
    char line[256];
    Tokenizer tokenizer;
    vector<Token> tokens;
    InstructionSet instructionSet;
    while (fgets(line, sizeof(line), fp))
    {
        //tokenize line
        tokens=tokenizer.parse(line);
        //add to instruction set
        instructionSet.addInstruction(tokens);
    }
    instructionSet.printInstructionSet();
}