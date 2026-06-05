#include "../../include/compiler/compiler.hpp"

#include "../../include/lexer/lexer.hpp"
#include "../../include/parser/parser.hpp"

#include "../../include/semantic/analyzer.hpp"

#include "../../include/ir/ir_builder.hpp"

#include "../../include/codegen/x64_backend.hpp"
#include "../../include/codegen/pe_writer.hpp"

namespace riven
{

bool Compiler::compile(
    const std::string& source,
    const std::string& output
)
{
    Lexer lexer(
        source
    );

    auto tokens =
        lexer.tokenize();

    Parser parser(
        tokens
    );

    auto program =
        parser.parse();

    SemanticAnalyzer analyzer;

    analyzer.analyze(
        program.get()
    );

    IRBuilder builder;

    auto module =
        builder.build(
            program.get()
        );

    X64Backend backend;

    auto code =
        backend.generate(
            module
        );

    PEWriter writer;

    return writer.write(
        output,
        code
    );
}

}
