#include "parser.h"

#include <stdio.h>
#include <stdlib.h>

parser_t* parser_init(lexer_t* lexer) {
    parser_t* parser = malloc(sizeof(parser_t)); 

    parser->lexer = lexer;
    parser->current_token = lexer_get_token(lexer);

    return parser;
}

// check if the syntax is correct
void parser_consume(parser_t* parser, token_type_t token_type) {
    if(parser->current_token->type == token_type) {
        printf("TOKEN: value: %s, type: %d\n", parser->current_token->value, parser->current_token->type);
        parser->current_token = lexer_get_token(parser->lexer);
    } else {
        printf("Unexpected token '%s'\n", parser->current_token->value);
        exit(1);
    }
}

ast_node_t* parser_parse(parser_t* parser) {
    ast_node_t* prog = ast_new_node(AST_PROG);
    prog->c1 = NULL; // todo: parser_statement
    return prog;
}

ast_node_t* parser_statement(parser_t* parser) {
    // todo: conditions pour savoir quel token c'est pour cree un ast_node qui return node
}