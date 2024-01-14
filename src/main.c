#include "lexer/lexer.h"

#include <stdio.h>

int main() {
    lexer_t* lexer = lexer_init(
        "var name = \"seb\";\n"
        "print(name);\n"
    );

    token_t* token = NULL;

    while((token = lexer_get_token(lexer)) != NULL) {
        printf("TOKEN: value: %s, type: %d\n", token->value, token->type);
        lexer_next_char(lexer);
    }

    return 0;
}