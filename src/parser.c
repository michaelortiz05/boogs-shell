#define TOKEN_SIZE 10
#define TOKEN_LIST 10
#include <stdlib.h>

typedef struct {
    char** tokens;
    int count;
} TokenList;

enum Tokens {COMMAND, ARGUMENT, REDIRECTION, PIPE, SPECIAL};
typedef enum {START, IN_WORD, IN_QUOTE} TokenizerState;

int tokenizer(const char* input, TokenList* result);

int tokenizer(const char* input, TokenList* result) {
    int tokenList = TOKEN_LIST;
    int tokenSize = TOKEN_SIZE;
    int tokenCount = 0;
    int tokenIndex = 0;
    const char* cPtr = input;
    TokenizerState state = START;
    result->tokens = calloc(tokenList, sizeof(char*));
    char* token = calloc(tokenSize, sizeof(char));
    while (*cPtr != '\0') {
        if (tokenCount >= tokenList) {
            tokenList *= 2;
            result->tokens = realloc(result->tokens, tokenList * sizeof(char*));
            if (result->tokens == NULL)
                return -1;
        }
        if (tokenIndex >= tokenSize) {
            tokenSize *= 2;
            token = realloc(token, tokenSize * sizeof(char));
            if (token == NULL)
                return -1;
        }
        if (state == START) {
            if (*cPtr == ' ') {
                cPtr++;
                continue;
            }
            else 
                state = IN_WORD;
        }
        if (state == IN_WORD) {
            if (*cPtr == ' ') {
                result->tokens[tokenCount++] = token;
                state = START;
                tokenSize = TOKEN_SIZE;
                token = calloc(tokenSize, sizeof(char));
                tokenIndex = 0;
            }
            else if (*cPtr == '"') {
                state = IN_QUOTE;
            }
            else
                token[tokenIndex++] = *cPtr;
        }
        if (state == IN_QUOTE) {
            if (*cPtr == '"') {
                result->tokens[tokenCount++] = token;
                state = START;
                tokenSize = TOKEN_SIZE;
                token = calloc(tokenSize, sizeof(char));
                tokenIndex = 0;
            }
            else
                token[tokenIndex++] = *cPtr;
        }
        cPtr++;
    }
    if (tokenIndex > 0) 
        result->tokens[tokenCount++] = token;
    free(token);
    result->count = tokenCount;
    return 0; // return status code
}