#pragma once

#include <stdint.h>

#include "lexer/lexer.h"
#include "ast.h"

typedef struct {
    lexer_t* lexer;
    token_t* current_token;
} parser_t;

parser_t* parser_init(lexer_t* lexer);

void parser_consume(parser_t* parser, token_type_t token_type);

ast_node_t* parser_parse(parser_t* parser);
ast_node_t* parser_statement(parser_t* parser);