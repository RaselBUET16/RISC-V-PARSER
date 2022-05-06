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
                    currentToken.tType = STRING_LITERAL;
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
        else if (token.tType == IDENTIFIER)
        {
            if (token.text == "sp" || token.text == "ra" || token.text == "gp" || token.text == "tp")
            {
                token.tType = REGISTER;
                tokens.push_back(token);
            }
            else if (token.text.size() == 2)
            {
                if ((token.text[0] == 's' && token.text[1] >= '0' && token.text[1] <= '9') || (token.text[0] == 't' && token.text[1] >= '0' && token.text[1] <= '6') || (token.text[0] == 'a' && token.text[1] >= '0' && token.text[1] <= '7') || (token.text[0] == 'x' && token.text[1] >= '0' && token.text[1] <= '9'))
                {
                    token.tType = REGISTER;
                    tokens.push_back(token);
                }
                else
                {
                    tokens.push_back(token);
                }
            }
            else if (token.text.size() == 3)
            {
                if (token.text[0] == 's' && token.text[1] == '1' && (token.text[2] == 0 || token.text[2] == '1'))
                {
                    token.tType = REGISTER;
                    tokens.push_back(token);
                }
                else if (token.text[0] == 'x' && 
                (((token.text[1] == '1' || token.text[1] == '2') && (token.text[2] >= '0' && token.text[2] <= '9')) || (token.text[1] == '3' && (token.text[2] == '0' || token.text[2] == '1'))))
                {
                    token.tType = REGISTER;
                    tokens.push_back(token);
                }
                else
                {
                    tokens.push_back(token);
                }
            }
            else{
                tokens.push_back(token);
            }
        }
        else if (token.tType != WHITESPACE)
        {
            tokens.push_back(token);
        }
        token.tType = WHITESPACE;
        token.text.erase();
    }
};
