#pragma once

#include <vector>
#include <string>

using namespace std;

enum TokenType
{
    WHITESPACE, // No token ever has this type.
    IDENTIFIER,
    ERROR,
    INTEGER_LITERAL,
    STRING_LITERAL,
    OPERATOR,
    STRING_ESCAPE_SEQUENCE,
    POTENTIAL_COMMENT,
    COMMENT,
    COMMA,
    REGISTER
};

static const char *sTokenTypeStrings[] = {
    "WHITESPACE",
    "IDENTIFIER",
    "ERROR",
    "INTEGER_LITERAL",
    "STRING_LITERAL",
    "OPERATOR",
    "STRING_ESCAPE_SEQUENCE",
    "POTENTIAL_COMMENT",
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
    vector<Token> parse(const std::string &inProgram)
    {
        vector<Token> tokens;
        Token currentToken;

        for (char currCh : inProgram)
        {
            if (currentToken.tType == COMMENT)
            {
                switch (currCh)
                {
                case '\n':
                    endToken(currentToken, tokens);
                    currentToken.tType = WHITESPACE;
                    break;
                default:
                    currentToken.text.append(1, currCh);
                    break;
                }
                continue;
            }

            switch (currCh)
            {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                if (currentToken.tType == WHITESPACE)
                {
                    currentToken.tType = INTEGER_LITERAL;
                    currentToken.text.append(1, currCh);
                }
                else
                {
                    currentToken.text.append(1, currCh);
                }
                break;

            case ',':
                endToken(currentToken, tokens);
                currentToken.tType = COMMA;
                currentToken.text.append(1, currCh);
                endToken(currentToken, tokens);
                currentToken.tType = WHITESPACE;
                break;

            case ' ':
            case '\t':
                endToken(currentToken, tokens);
                currentToken.tType = WHITESPACE;
                break;

            case '\r':
                currentToken.text.append(1, currCh);
                break;
            case '\n':
                endToken(currentToken, tokens);
                currentToken.tType = WHITESPACE;
                break;

            case '#':

                endToken(currentToken, tokens);
                currentToken.tType = COMMENT;
                break;

            default:
                if (currentToken.tType == WHITESPACE)
                {
                    currentToken.tType = IDENTIFIER;
                    currentToken.text.append(1, currCh);
                }
                else if (currentToken.tType == INTEGER_LITERAL)
                {
                    currentToken.tType=ERROR;
                    currentToken.text.append(1, currCh);
                }
                else
                {
                    currentToken.text.append(1, currCh);
                }
                break;
            }
        }

        endToken(currentToken, tokens);

        return tokens;
    }

private:
    void endToken(Token &token, vector<Token> &tokens)
    {
        if (token.tType == COMMENT)
        {
            // cout << "Ignoring comment " << token.mText << endl;
            tokens.push_back(token);
        }
        else if(token.tType==IDENTIFIER && token.text.size() ==2 && (token.text[0] == 'a' || token.text[0]== 'x') && (token.text[1] >= '0' && token.text[1] <= '9'))
        {
            token.tType = REGISTER;
            tokens.push_back(token);
        }
        else if (token.tType != WHITESPACE)
        {
            tokens.push_back(token);
        }
        token.tType = WHITESPACE;
        token.text.erase();
    }
};
