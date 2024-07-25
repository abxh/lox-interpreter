#pragma once

#include <assert.h>
#include <charconv>
#include <cstdlib>
#include <string_view>
#include <variant>

enum TokenType {
    // Single-char tokens:
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,
    COMMA,
    DOT,
    MINUS,
    PLUS,
    SEMICOLON,
    SLASH,
    STAR,

    // One or two char tokens:
    BANG,
    BANG_EQUAL,
    EQUAL_EQUAL,
    GREATER_THAN,
    GREATER_THAN_OR_EQUAL,
    LESS_THAN,
    LESS_THAN_OR_EQUAL,

    // literals:
    IDENTIFIER,
    STRING,
    NUMBER,

    // keywords:
    AND,
    CLASS,
    ELSE,
    FALSE,
    FUN,
    FOR,
    IF,
    NIL,
    OR,
    PRINT,
    RETURN,
    SUPER,
    THIS,
    TRUE,
    VAR,
    WHILE,

    END_OF_FILE,
};

class Token {
public:
    const TokenType token_type;
    const std::string_view lexeme;

    Token(TokenType token_type, std::string_view lexeme)
        : token_type(token_type)
        , lexeme(lexeme){};

    std::variant<std::nullptr_t, double, std::string_view> get_object() {
        // return a typesafe tagged union of sorts.

        switch (token_type) {
        case STRING:
            assert(lexeme.at(0) == '"');
            assert(lexeme.at(lexeme.length() - 1) == '"');

            return lexeme.substr(1, lexeme.length() - 2);
        case NUMBER: {
            double dbl;
            auto result = std::from_chars(lexeme.data(), lexeme.data() + lexeme.size(), dbl);

            assert(result.ec == std::errc());
            return dbl;
        }
        default:
            break;
        }

        return nullptr;
    }
};
