#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP
#include <unordered_map>

#include "grammar/Grammar.hpp"
#include "grammar/TypesSet.hpp"

using SymbolsSet = TypesSet< Symbols, SymbolsHash >;

struct SymbolsSetHash
{
    std::size_t
    operator( )( const SymbolsSet& symbols_set ) const
    {
        std::size_t seed = 0;
        for ( auto& symbols : symbols_set )
        {
            seed ^= SymbolsHash{ }( symbols );
        }

        return seed;
    }
};

using SymbolSymbolsMap = std::unordered_map< SymbolPtr, SymbolsSet >;

using LocalResult = std::unordered_map< SymbolPtr, std::unordered_set< SymbolsSet, SymbolsSetHash > >;

SymbolSymbolsMap first_k( const Grammar& grammar, int k );
SymbolSymbolsMap follow_k( const Grammar& grammar, int k );
SymbolsSet first_k( const Grammar& grammar, int k, const Symbols& symbols );
SymbolsSet first_k( const Grammar& grammar,
                    int k,
                    Symbols::const_iterator it_begin,
                    Symbols::const_iterator it_end );

void expand_rules_sequence( const Grammar& grammar, std::ostream& os, const SyntaxRules& rules );

LocalResult local_k( const Grammar& grammar,
                     int k,
                     const SymbolPtr& from_symbol,
                     const SymbolPtr& to_symbol );

NonTerminals epsilon_non_terminals( const Grammar& grammar );
bool is_left_recursive( const Grammar& grammar, const NonTerminal& symbol );

std::ostream& operator<<( std::ostream& os, const SymbolsSet& symbols_set );
std::ostream& operator<<( std::ostream& os, const SymbolSymbolsMap& map );

#endif  // ALGORITHMS_HPP
