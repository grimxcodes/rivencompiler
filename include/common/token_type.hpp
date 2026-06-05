#pragma once

namespace riven
{

enum class TokenType
{
    EndOfFile,
    Invalid,

    Identifier,
    Number,
    String,

    Riven,
    Core,

    ConsistOf,

    Firm,

    Craft,
    Returns,

    Frame,
    Boot,

    Open,
    Hidden,

    If,
    AltIf,
    Else,

    Flow,
    During,

    Spark,
    Sync,

    Ref,
    Ptr,

    Raw,

    Rise,
    Drop,

    Imprint,
    Scanq,

    Fetch,

    Attack,
    Resc,

    Correct,
    Incorrect,

    Emp,

    Assign,

    Equal,
    NotEqual,

    Greater,
    Less,

    GreaterEqual,
    LessEqual,

    Plus,
    Minus,
    Star,
    Slash,

    And,
    Or,
    Not,

    Increment,
    Decrement,

    LeftParen,
    RightParen,

    LeftBrace,
    RightBrace,

    LeftBracket,
    RightBracket,

    Comma,
    Dot,
    Semicolon
};

}
