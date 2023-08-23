#include "lexer.h"
#define MAX_INPUT_SIZE 1024
int main() {
    char input[MAX_INPUT_SIZE];
    TokenList tokenList;
    printf("***************\n--BOOGS SHELL--\n***************\n");
    while (1) {
        printf("mindset> ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Error occured reading input\n");
            continue;
        }
        // Remove newline character
        if (input[strlen(input) - 1] == '\n') {
            input[strlen(input) - 1] = '\0';
        }
        if (strcmp(input, "exit") == 0) {
            break; // Exit the shell
        }
        if (tokenizer(input, &tokenList) == 0) {
            printTokens(&tokenList);
        }
        else {
            printf("tokenizer error!");
        }
        // Free the memory allocated for the tokens
        for (int i = 0; i < tokenList.count; i++) {
            free(tokenList.tokens[i].value);
        }
        free(tokenList.tokens);
    }
    return 0;
}