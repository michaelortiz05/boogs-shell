#define TOKEN_SIZE 10
#define TOKEN_LIST 10
#include "parser.h"

int tokenizer(const char* input, TokenList* result) {
    int tokenListSize = TOKEN_LIST;
    int tokenSize = TOKEN_SIZE;
    int tokenIndex = 0;
    int tokenCount = 0;
    result->tokens = calloc(tokenListSize, sizeof(Token));
    char* token = calloc(tokenSize, sizeof(char));
    TokenizerState state = START;
    TokenType currentType = COMMAND;
    const char* cPtr = input;
    while (*cPtr != '\0') {
        if (tokenCount >= tokenListSize) {
            tokenListSize *= 2;
            result->tokens = realloc(result->tokens, tokenListSize * sizeof(Token));
            if (result->tokens == NULL)
                return -1; // Memory allocation failure
        }
        if (tokenIndex >= tokenSize) {
            tokenSize *= 2;
            token = realloc(token, tokenSize * sizeof(char));
            if (token == NULL)
                return -1; // Memory allocation failure
        }
        switch (state) {
            case START:
                if (*cPtr == ' ') {
                    cPtr++;
                    continue;
                }
                else {
                    state = IN_WORD;
                    continue;
                }
                break;
            case IN_WORD:
                if (*cPtr == '|') {
                    currentType = PIPE;
                }
                else if (*cPtr == '>') {
                    currentType = REDIRECTION;
                }
                // More conditions for other token types as needed...

                if (*cPtr == ' ' || *cPtr == '|' || *cPtr == '>') {
                    result->tokens[tokenCount++] = (Token){strdup(token), currentType};
                    tokenSize = TOKEN_SIZE;
                    token = calloc(tokenSize, sizeof(char));
                    tokenIndex = 0;
                    state = START;
                    currentType = *cPtr == ' ' || *cPtr == '>' ? ARGUMENT : COMMAND;
                }
                else if (*cPtr == '"') {
                    currentType = ARGUMENT;
                    state = IN_QUOTE;
                    token[tokenIndex++] = *cPtr;
                }
                else {
                    token[tokenIndex++] = *cPtr;
                }
                break;
            case IN_QUOTE:
                if (*cPtr == '"') {
                    token[tokenIndex++] = *cPtr;
                    result->tokens[tokenCount++] = (Token){strdup(token), currentType};
                    state = START;
                    tokenSize = TOKEN_SIZE;
                    token = calloc(tokenSize, sizeof(char));
                    tokenIndex = 0;
                }
                else {
                    token[tokenIndex++] = *cPtr;
                }
                break;
        }
        cPtr++;
    }

    if (tokenIndex > 0) {
        result->tokens[tokenCount++] = (Token){strdup(token), currentType};
    }
    free(token); // Free token buffer
    result->count = tokenCount;
    return 0;
}

const char* tokenTypeToString(TokenType type) {
    switch (type) {
        case COMMAND: return "COMMAND";
        case ARGUMENT: return "ARGUMENT";
        case REDIRECTION: return "REDIRECTION";
        case PIPE: return "PIPE";
        case SPECIAL: return "SPECIAL";
        default: return "UNKNOWN";
    }
}

void printTokens(TokenList *tokenList) {
    for (int i = 0; i < tokenList->count; i++) {
        printf("%s{%s} ", tokenTypeToString(tokenList->tokens[i].type), tokenList->tokens[i].value);
    }
    printf("\n");
}

