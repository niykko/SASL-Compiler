//===----------------------------------------------------------------------===//
//
//                              SASL Lexer
//
//===----------------------------------------------------------------------===//

#pragma once
#include <token.hpp>
using std::make_unique;
using std::unique_ptr;

class Lexer
{
public:
    explicit Lexer(std::string);
    std::unique_ptr<TokenBase> lookahead();
    std::vector<std::unique_ptr<TokenBase>> feast();

private:
    std::string source;
    TokenPosition position;
    TokenPosition tokenStart;
    void consume(size_t count);
    void consume_comment(size_t count, std::pair<CommentType, std::regex> comment);
    void skipwhitespace();
    void skipnewline();
    void skipcomment(size_t count);
    void skip();
};
