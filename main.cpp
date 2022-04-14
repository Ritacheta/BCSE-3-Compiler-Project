#include<bits/stdc++.h>

#include "lexical_scan.cpp"
#include "symbol_table.cpp"
using namespace std;

int main(){
    Analyzer lexical = Analyzer("test.txt");
    vector<Token> tokens = lexical.run_scan();
    SymbolTable table;
    table.add_ids_from_tokens(tokens);
    table.print_symbol_table();
    return 0;
}