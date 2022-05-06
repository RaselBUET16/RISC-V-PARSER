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
    FILE *fpIN = fopen("INPUTFILE.txt", "r");
    FILE *fpOUT=fopen("OUTPUTFILE.txt", "w");
    if(fpIN == NULL)
    {
        cout<<"File not found"<<endl;
        return 0;
    }
    //read line of the file
    char line[256];
    Tokenizer tokenizer;
    vector<Token> tokens;
    InstructionSet instructionSet;
    while (fgets(line, sizeof(line), fpIN))
    {
        //tokenize line
        tokens=tokenizer.parse(line);
        //add to instruction set
        instructionSet.addInstruction(tokens);
    }
    instructionSet.printInstructionSet(fpOUT);
    fclose(fpIN);
    fclose(fpOUT);
    return 0;
}