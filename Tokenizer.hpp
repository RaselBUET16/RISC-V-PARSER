#pragma once

#include <vector>
#include <string>

using namespace std;

enum TokenType
{
    WHITESPACE, // No token ever has this type.
    IDENTIFIER,
    INTEGER_LITERAL,
    STRING_LITERAL,
    COMMENT,
    COMMA,
    REGISTER
};

static const char *sTokenTypeStrings[] = {
    "WHITESPACE",
    "IDENTIFIER",
    "INTEGER_LITERAL",
    "STRING_LITERAL",
    "COMMENT",
    "COMMA",
    "REGISTER"};

class Token
{
public:
    enum TokenType tType
    {
        WHITESPACE
    };
    string text;
};

class Tokenizer
{
public:
    vector<Token> parse(const std::string &inProgram);

private:
    void endToken(Token &token, vector<Token> &tokens);
};
