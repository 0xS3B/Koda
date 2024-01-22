#include "ast.h"

#include <stdlib.h>

ast_node_t* ast_new_node(ast_type_t type) {
    ast_node_t* node = malloc(sizeof(ast_node_t));
    node->type = type;
    return node;
}