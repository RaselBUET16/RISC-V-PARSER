#include "Tokenizer.hpp"
#include<iostream>

using namespace std;
void printVector(vector<Token> tokens)
{
    for(Token currToken : tokens)
    {
        cout<<currToken.text<<" "<<sTokenTypeStrings[currToken.tType]<<endl;
    }
    cout<<endl;
}
int main( int argc, char* argv[] )
{
    FILE *fp = fopen("INPUTFILE.txt", "r");
    //read line of the file
    char line[256];
    Tokenizer tokenizer;
    vector<Token> tokens;
    while (fgets(line, sizeof(line), fp))
    {
        cout << line;
        tokens=tokenizer.parse(line);
        printVector(tokens);
    }
}