#pragma once

#include <stdint.h>

typedef struct {
    uint32_t position;
    char c;
    char* source;
} lexer_t;

lexer_t* lexer_init(char* source);


// token
typedef enum {
    TOKEN_ADD,
    TOKEN_DIV,
    TOKEN_EQUAL,
    TOKEN_FALSE,
    TOKEN_ID,
    TOKEN_IF,
    TOKEN_LPAREN,
    TOKEN_MUL,
    TOKEN_RPAREN,
    TOKEN_SUB,
    TOKEN_SEMICOLON,
    TOKEN_STRING,
    TOKEN_TRUE,
} token_type;

typedef struct {
    token_type type;
    char* value;
} token_t;

token_t* create_token(token_type type, char* value);
token_t* lexer_get_token(lexer_t* lexer);
token_t* lexer_get_id(lexer_t* lexer);
token_t* lexer_get_string(lexer_t* lexer);
// end token


// char
void lexer_next_char(lexer_t* lexer);
char* lexer_get_current_char(lexer_t* lexer);
void lexer_skip_space(lexer_t* lexer);
// end char