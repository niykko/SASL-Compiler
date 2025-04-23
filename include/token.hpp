#pragma once
#include "token_types.hpp"
#include <iostream>


class TokenBase
{
public:
    TokenBase(TokenPosition pos) : tokenPosition(std::move(pos)) {};
    virtual TokenType getType() const = 0; 
    virtual ~TokenBase() = default;
    virtual void print()
    {
        std::cout << "This is a virtual call." << "\n";
    }
    TokenPosition tokenPosition;
};

template <TokenType T>
class Token : public TokenBase
{
public:
    Token(TokenPosition p) : TokenBase(p) {};
    static constexpr TokenType type = T;

    TokenType getType() const override { return type; }
    void print() override
    {
        PrintPosition(tokenPosition);
        std::cout << "TokenType: " << TokenTypeToString(type) << "\n";
    }
};

template <>
class Token<TokenType::KEYWORD> : public TokenBase
{
public:
    Token(KeywordType k, TokenPosition pos) : TokenBase(pos), subtype(std::move(k)) {};
    static constexpr TokenType type = TokenType::KEYWORD;

    KeywordType subtype;

    TokenType getType() const override { return type; }
    void print() override
    {
        PrintPosition(tokenPosition);
        std::cout << "TokenType: " << TokenTypeToString(type) << ", KeywordType: " << KeywordTypeToString(subtype) << "\n";
    }
};

template <>
class Token<TokenType::SYMBOL> : public TokenBase
{
public:
    Token(SymbolType s, TokenPosition pos) : TokenBase(pos), subtype(std::move(s)) {};
    static constexpr TokenType type = TokenType::SYMBOL;

    SymbolType subtype;

    TokenType getType() const override { return type; }
    void print() override
    {
        PrintPosition(tokenPosition);
        std::cout << "TokenType: " << TokenTypeToString(type) << ", SymbolType: " << SymbolTypeToString(subtype) << "\n";
    }
};

template <>
class Token<TokenType::CONSTANT> : public TokenBase
{
public:
    using ValueType = std::variant<bool, int, std::string>;
    Token(ValueType value, ConstantType c, TokenPosition pos) : TokenBase(pos), val(std::move(value)), subtype(std::move(c)) {}
    static constexpr TokenType type = TokenType::CONSTANT;

    ValueType val;
    ConstantType subtype;

    TokenType getType() const override { return type; }

    void print() override
    {
        PrintPosition(tokenPosition);
        std::cout << "TokenType: " << TokenTypeToString(type) << ", Subtype: " << ConstantTypeToString(subtype) << ", Value: ";
        std::visit([](auto &&arg)
                   { std::cout << arg << '\n'; }, val);
    }
};

template <>
class Token<TokenType::IDENTIFIER> : public TokenBase
{
public:
    Token(std::string identifier, TokenPosition pos) : TokenBase(pos), id(std::move(identifier)) {};
    static constexpr TokenType type = TokenType::IDENTIFIER;

    std::string id;

    TokenType getType() const override { return type; }
    void print() override
    {
        PrintPosition(tokenPosition);
        std::cout << "TokenType: " << TokenTypeToString(type) << ", ID: " << id << "\n";
    }
};


template <>
class Token<TokenType::COMMENT> : public TokenBase
{
public:
    Token(std::string comment, TokenPosition pos) : TokenBase(pos), com(std::move(comment)) {};
    static constexpr TokenType type = TokenType::COMMENT;

    std::string com;

    TokenType getType() const override { return type; }
    void print() override
    {
        PrintPosition(tokenPosition);
        std::cout << "TokenType: " << TokenTypeToString(type) << ", Comment: " << com << "\n";
    }
};