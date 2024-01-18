#include "lexer/lexer.h"

#include <stdio.h>
#include <stdlib.h>

int main() {
    char* file_content = NULL;
    FILE* file_ptr = fopen("./examples/main.x", "r");

    if(file_ptr == NULL) {
        perror("Error opening file");
        return 1;
    }

    fseek(file_ptr, 0, SEEK_END);
    long file_size = ftell(file_ptr);
    fseek(file_ptr, 0, SEEK_SET);

    file_content = (char*) calloc(1, file_size + 1); // + 1 for the null terminator

    if(file_content == NULL) {
        perror("Memory allocation error");
        fclose(file_ptr);
        return 1;
    }

    fread(file_content, file_size, 1, file_ptr);

    lexer_t* lexer = lexer_init(file_content);
    token_t* token = NULL;

    while((token = lexer_get_token(lexer)) != NULL) {
        printf("TOKEN: value: %s, type: %d\n", token->value, token->type);
        lexer_next_char(lexer);
    }

    free(file_content);
    fclose(file_ptr);

    return 0;
}