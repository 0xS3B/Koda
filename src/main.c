#include "lexer/lexer.h"
#include "parser/parser.h"

#include <stdio.h>
#include <stdlib.h>

void print_usage() {
    printf("Usage: ./koda.out [file.kd]\n");
}

int main(int argc, char *argv[]) {
    if(argv[1] == NULL) {
        print_usage();
        return 1;
    }

    char* file_content = NULL;
    FILE* file_ptr = fopen(argv[1], "r");

    if(file_ptr == NULL) {
        perror("Error opening file");
        print_usage();
        return 1;
    }

    fseek(file_ptr, 0, SEEK_END);
    long file_size = ftell(file_ptr);
    fseek(file_ptr, 0, SEEK_SET);

    file_content = calloc(file_size, sizeof(char)); // + 1 for the null terminator

    if(file_content == NULL) {
        perror("Memory allocation error");
        fclose(file_ptr);
        return 1;
    }

    fread(file_content, file_size, 1, file_ptr);


    lexer_t* lexer = lexer_init(file_content);
    parser_t* parser = parser_init(lexer);
    ast_node_t* prog = parser_parse(parser); // the start of the program

    token_t* token = NULL;

    // test
    while((token = parser->current_token) != NULL && token->type != TOKEN_EOF) {
        parser_consume(parser, token->type);
    }
    
    free(file_content);
    fclose(file_ptr);

    return 0;
}