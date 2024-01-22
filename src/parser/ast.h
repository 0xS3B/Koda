#pragma once

#include <stdint.h>

typedef enum {
    AST_ADD,
    AST_DIV,
    AST_MUL,
    AST_NUM,
    AST_PROG,
    AST_SUB,
} ast_type_t;

typedef struct ast_node_s {
    ast_type_t type;
    struct ast_node_s *c1, *c2; // child
    union {
        int num;
        char* id;
    };
} ast_node_t;

ast_node_t* ast_new_node(ast_type_t type);