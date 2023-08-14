#include <stdlib.h>
#include <stdio.h>
typedef enum {COMMAND, ARGUMENT, REDIRECTION, PIPE, SPECIAL} TokenType;
typedef enum {START, IN_WORD, IN_QUOTE} TokenizerState;

typedef struct {
    char* value;
    TokenType type;
} Token;

typedef struct {
    Token* tokens;
    int count;
} TokenList;

int tokenizer(const char* input, TokenList* result);
void printTokens(TokenList *tokenList);
const char* tokenTypeToString(TokenType type);
