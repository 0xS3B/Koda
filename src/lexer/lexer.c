#include "lexer.h"

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <stdio.h>

lexer_t* lexer_init(char* source) {
    lexer_t* lexer = calloc(1, sizeof(lexer_t));

    lexer->position = 0;
    lexer->c = source[lexer->position];    
    lexer->source = source;

    return lexer;
}

// token
token_t* lexer_create_token(token_type_t type, char* value) {
    token_t* token = calloc(1, sizeof(token_t));

    token->type = type;
    token->value = value;

    return token;
}

token_t* lexer_get_token(lexer_t* lexer) {
    if(lexer->c == '\0') 
        return lexer_create_token(TOKEN_EOF, "\0");
        
    if(lexer->c == ' ' || lexer->c == '\n')
        lexer_skip_space(lexer);

    if(isalnum(lexer->c))
        return lexer_get_id(lexer);

    if(lexer->c == '"')
        return lexer_get_string(lexer);


    token_t* token = NULL;

    switch(lexer->c)
    {
        case '+': token = lexer_create_token(TOKEN_ADD, lexer_get_current_char(lexer)); break;
        case ',': token = lexer_create_token(TOKEN_COMMA, lexer_get_current_char(lexer)); break;
        case '/': token = lexer_create_token(TOKEN_DIV, lexer_get_current_char(lexer)); break;
        case '=': token = lexer_create_token(TOKEN_EQUAL, lexer_get_current_char(lexer)); break;
        case '(': token = lexer_create_token(TOKEN_LPAREN, lexer_get_current_char(lexer)); break;
        case '*': token = lexer_create_token(TOKEN_MUL, lexer_get_current_char(lexer)); break;
        case ')': token = lexer_create_token(TOKEN_RPAREN, lexer_get_current_char(lexer)); break;
        case '-': token = lexer_create_token(TOKEN_SUB, lexer_get_current_char(lexer)); break;
        case ';': token = lexer_create_token(TOKEN_SEMICOLON, lexer_get_current_char(lexer)); break;
    }

    lexer_next_char(lexer);
    return token;
}

token_t* lexer_get_id(lexer_t* lexer) {
    char* id = calloc(1, sizeof(char));
    id[0] = '\0';

    while(isalnum(lexer->c)) {
        char* c = lexer_get_current_char(lexer);
        id = realloc(id, strlen(id) + 2 * sizeof(char)); // 2 = strlen(c)
        strcat(id, c);

        lexer_next_char(lexer);
    }

    return lexer_create_token(TOKEN_ID, id);
}

token_t* lexer_get_string(lexer_t* lexer) {
    char* string = calloc(1, sizeof(char));
    string[0] = '\0';

    // skip the first "
    lexer_next_char(lexer);

    while(lexer->c != '"') {
        char* c = lexer_get_current_char(lexer);
        string = realloc(string, strlen(string) + 2 * sizeof(char)); // 2 = strlen(c)
        strcat(string, c);

        lexer_next_char(lexer);
    }

    // skip the last "
    lexer_next_char(lexer);

    return lexer_create_token(TOKEN_STRING, string);
}
// end token


// char
void lexer_next_char(lexer_t* lexer) {
    if(lexer->c != '\0' && lexer->position < strlen(lexer->source)) {
        lexer->position++;
        lexer->c = lexer->source[lexer->position];
    }
}

char* lexer_get_current_char(lexer_t* lexer) {
    char* string = calloc(2, sizeof(char));

    // transform the char into a string
    string[0] = lexer->c;
    string[1] = '\0';

    return string;
}

void lexer_skip_space(lexer_t* lexer) {
    while(lexer->c == ' ' || lexer->c == '\n') {
        lexer_next_char(lexer);
    }
}
// end char