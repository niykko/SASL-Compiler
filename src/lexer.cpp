
//===----------------------------------------------------------------------===//
//
//                              SASL Lexer
//
//===----------------------------------------------------------------------===//

#include "lexer.hpp"

Lexer::Lexer(std::string input) : source(std::move(input))
{
    position = {1, 0};
    tokenStart = {1, 0};
};

void Lexer::skipwhitespace()
{
    position.column++;
    source.erase(0, 1);
};

void Lexer::skipnewline()
{
    position.line++;
    position.column = 0;
    source.erase(0, 1);
};

void Lexer::skip()
{
    while (!source.empty())
    {
        std::smatch match;
        if (std::regex_search(source, match, WhitespaceRegex))
        {
            skipwhitespace();
            continue;
        }
        else if (std::regex_search(source, match, NewlineRegex))
        {
            skipnewline();
            continue;
        }
        else
        {
            break;
        }
    };
};

void Lexer::consume(size_t count)
{
    tokenStart = position;
    position.column += count;
    source = source.substr(count);
};

void Lexer::consume_comment(size_t count, std::pair<CommentType, std::regex> comment)
{
    if (comment.first == SINGLE_LINE)
    {
        tokenStart = position;
        position.column += count;
        source = source.substr(count);
    }
    else if (comment.first == MULTI_LINE)
    {
        tokenStart = position;
        size_t newlines = 0;
        size_t lastNewlinePos = std::string::npos;

        for (size_t i = 0; i < count; ++i)
        {
            if (source[i] == '\n')
            {
            newlines++;
            lastNewlinePos = i;
            }
        }

        position.line += newlines;
        if (newlines > 0)
        {
            position.column = count - lastNewlinePos - 1;
        }
        else
        {
            position.column += count;
        }
        source = source.substr(count);
    }
};


std::unique_ptr<TokenBase> Lexer::lookahead()
{
    skip();
    // End of file
    if (source.empty() || ((source[0] == '\n') && source.length() == 1))
    {
        return make_unique<Token<TokenType::SPECIAL>>(position);
    }
    else
    {
        std::smatch match;

        // Comment
        for (std::pair<CommentType, std::regex> Comment : CommentRegister)
        {
            if (std::regex_search(source, match, Comment.second))
            {
                std::string val = match.str(0);
                consume_comment(val.length(), Comment);
                return make_unique<Token<TokenType::COMMENT>>(val, tokenStart);
            }
        };

        // Keyword
        for (std::pair<KeywordType, std::regex> Keyword : KeywordRegister)
        {
            if (std::regex_search(source, match, Keyword.second))
            {
                std::string val = match.str(0);
                consume(match.length());
                return make_unique<Token<TokenType::KEYWORD>>(Keyword.first, tokenStart);
            }
        };

        // Symbol
        for (std::pair<SymbolType, std::regex> Symbol : SymbolRegister)
        {
            if (std::regex_search(source, match, Symbol.second))
            {
                std::string val = match.str(0);
                consume(match.length());
                return make_unique<Token<TokenType::SYMBOL>>(Symbol.first, tokenStart);
            }
        };

        // Constant
        for (std::pair<ConstantType, std::regex> Constant : ConstantRegister)
        {
            if (std::regex_search(source, match, Constant.second))
            {
                std::string val = match.str(0);
                consume(match.length());
                if (Constant.first == BOOL)
                {
                    return make_unique<Token<TokenType::CONSTANT>>(val == "true", Constant.first, tokenStart);
                }
                else if (Constant.first == INT)
                {
                    return make_unique<Token<TokenType::CONSTANT>>(std::stoi(val), Constant.first, tokenStart);
                }
                else if (Constant.first == STRING)
                {
                    return make_unique<Token<TokenType::CONSTANT>>(std::move(val), Constant.first, tokenStart);
                }
            }
        };

        // Identifier
        if (std::regex_search(source, match, IdentifierRegex))
        {
            std::string val = match.str(0);
            consume(match.length());
            return make_unique<Token<TokenType::IDENTIFIER>>(val, tokenStart);
        }
    }

    std::cout << "return nullptr\n";
    return nullptr;
};


std::vector<std::unique_ptr<TokenBase>> Lexer::feast() {
    std::vector<std::unique_ptr<TokenBase>> tokens;
    while (true) {
        auto token = lookahead();
        if (token->getType() == TokenType::SPECIAL) {
            break;
        }
        tokens.push_back(std::move(token));
    }
    return tokens;
};