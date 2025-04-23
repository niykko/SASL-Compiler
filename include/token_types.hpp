#pragma once
#include <regex>
#include <iostream>

// Token Types
enum TokenType
{
    KEYWORD = 11,
    SYMBOL = 12,
    SPECIAL = 13,
    IDENTIFIER = 21,
    CONSTANT = 22,
    COMMENT = 23
};

constexpr const char *TokenTypeToString(TokenType type)
{
    switch (type)
    {
    case TokenType::KEYWORD:
        return "KEYWORD";
    case TokenType::SYMBOL:
        return "SYMBOL";
    case TokenType::SPECIAL:
        return "SPECIAL";
    case TokenType::IDENTIFIER:
        return "IDENTIFIER";
    case TokenType::CONSTANT:
        return "CONSTANT";
    case TokenType::COMMENT:
        return "COMMENT";
    default:
        return "UNKNOWN";
    }
};

struct TokenPosition
{
    int line;
    int column;
};

inline void PrintPosition(const TokenPosition &pos)
{
    std::cout << "[" << pos.line << "," << pos.column << "]";
};

// Keyword Types
enum KeywordType
{
    IF = 1,
    THEN = 2,
    ELSE = 3,
    DEF = 4,
    WHERE = 5,
    OR = 6,
    NOT = 7,
    HD = 8,
    TL = 9,
    NIL = 10,
};

inline std::pair<KeywordType, std::regex> KeywordRegister[]{
    {IF, std::regex(R"(^if)")},
    {THEN, std::regex(R"(^then)")},
    {ELSE, std::regex(R"(^else)")},
    {DEF, std::regex(R"(^def)")},
    {WHERE, std::regex(R"(^where)")},
    {OR, std::regex(R"(^or)")},
    {NOT, std::regex(R"(^not)")},
    {HD, std::regex(R"(^hd)")},
    {TL, std::regex(R"(^tl)")},
    {NIL, std::regex(R"(^nil)")},
};

inline constexpr const char *KeywordTypeToString(KeywordType type)
{
    switch (type)
    {
    case KeywordType::IF:
        return "IF";
    case KeywordType::THEN:
        return "THEN";
    case KeywordType::ELSE:
        return "ELSE";
    case KeywordType::DEF:
        return "DEF";
    case KeywordType::WHERE:
        return "WHERE";
    case KeywordType::OR:
        return "OR";
    case KeywordType::NOT:
        return "NOT";
    case KeywordType::HD:
        return "HD";
    case KeywordType::TL:
        return "TL";
    case KeywordType::NIL:
        return "NIL";
    default:
        return "UNKNOWN";
    }
};

// Symbol Types
enum SymbolType
{
    NOT_EQUALS = 1,
    GREATER_EQUALS = 2,
    GREATER = 3,
    LESS = 4,
    LESS_EQUALS = 5,
    EQUALS = 6,
    PLUS = 7,
    MINUS = 8,
    ASTERISK = 9,
    LEFT_PAREN = 10,
    RIGHT_PAREN = 11,
    LEFT_BRACKET = 12,
    RIGHT_BRACKET = 13,
    COMMA = 14,
    COLON = 15,
    SEMICOLON = 16,
    DOT = 17,
    SLASH = 18,
    BACKSLASH = 19
};

inline std::pair<SymbolType, std::regex> SymbolRegister[]{
    {NOT_EQUALS, std::regex(R"(^~=)")},
    {GREATER_EQUALS, std::regex(R"(^>=)")},
    {GREATER, std::regex(R"(^>)")},
    {LESS, std::regex(R"(^<)")},
    {LESS_EQUALS, std::regex(R"(^<=)")},
    {EQUALS, std::regex(R"(^=)")},
    {PLUS, std::regex(R"(^\+)")},
    {MINUS, std::regex(R"(^-)")},
    {ASTERISK, std::regex(R"(^\*)")},
    {LEFT_PAREN, std::regex(R"(^\()")},
    {RIGHT_PAREN, std::regex(R"(^\))")},
    {LEFT_BRACKET, std::regex(R"(^\[)")},
    {RIGHT_BRACKET, std::regex(R"(^\])")},
    {COMMA, std::regex(R"(^\,)")},
    {COLON, std::regex(R"(^:)")},
    {SEMICOLON, std::regex(R"(^;)")},
    {DOT, std::regex(R"(^\.)")},
    {SLASH, std::regex(R"(^/)")},
    {BACKSLASH, std::regex(R"(^\\)")},
};

constexpr const char *SymbolTypeToString(SymbolType type)
{
    switch (type)
    {
    case SymbolType::NOT_EQUALS:
        return "NOT_EQUALS";
    case SymbolType::GREATER_EQUALS:
        return "GREATER_EQUALS";
    case SymbolType::GREATER:
        return "GREATER";
    case SymbolType::LESS:
        return "LESS";
    case SymbolType::LESS_EQUALS:
        return "LESS_EQUALS";
    case SymbolType::EQUALS:
        return "EQUALS";
    case SymbolType::PLUS:
        return "PLUS";
    case SymbolType::MINUS:
        return "MINUS";
    case SymbolType::ASTERISK:
        return "ASTERISK";
    case SymbolType::LEFT_PAREN:
        return "LEFT_PAREN";
    case SymbolType::RIGHT_PAREN:
        return "RIGHT_PAREN";
    case SymbolType::LEFT_BRACKET:
        return "LEFT_BRACKET";
    case SymbolType::RIGHT_BRACKET:
        return "RIGHT_BRACKET";
    case SymbolType::COMMA:
        return "COMMA";
    case SymbolType::COLON:
        return "COLON";
    case SymbolType::SEMICOLON:
        return "SEMICOLON";
    case SymbolType::DOT:
        return "DOT";
    case SymbolType::SLASH:
        return "SLASH";
    case SymbolType::BACKSLASH:
        return "BACKSLASH";
    default:
        return "UNKNOWN_SYMBOL_TYPE";
    }
};

// Constant Types
enum ConstantType
{
    BOOL = 1,
    INT = 2,
    STRING = 3
};

inline std::pair<ConstantType, std::regex> ConstantRegister[]{
    {BOOL, std::regex(R"(\b^(?:true|false)\b)")},
    {INT, std::regex(R"(^\d+)")},
    {STRING, std::regex(R"(^\".*\")")}};

constexpr const char *ConstantTypeToString(ConstantType type)
{
    switch (type)
    {
    case ConstantType::BOOL:
        return "BOOL";
    case ConstantType::INT:
        return "INT";
    case ConstantType::STRING:
        return "STRING";
    default:
        return "UNKNOWN";
    }
};

// Comment Types
enum CommentType
{
    SINGLE_LINE = 1,
    MULTI_LINE = 2
};

inline std::pair<CommentType, std::regex> CommentRegister[]{
    {SINGLE_LINE, std::regex(R"(^\|\|[^\n]*)")},
    {MULTI_LINE, std::regex(R"(^\|\*([\s\S]*?)\*\|)")}
};

// Identifier Regex
inline const std::regex IdentifierRegex(R"(^[a-zA-Z_][a-zA-Z0-9_]*)");

// Whitespace Regex
inline const std::regex WhitespaceRegex(R"(^ )");

// Newline Regex
inline const std::regex NewlineRegex(R"(^\n)");
