#include <bits/stdc++.h>

#include "lexical_scan.cpp"
using namespace std;

/*
    int - i
    char - c
    string - s
*/

class Identifier {
    string token;
    string type;
    int line_dec;
    vector<int> line_refs;

   public:
    Identifier(string tk, string ty, int dec) {
        token = tk;
        type = ty;
        line_dec = dec;
    }

    void add_ref(int line) { line_refs.push_back(line); }

    int get_line_dec() { return line_dec; }

    vector<int> get_line_refs() { return line_refs; }

    string get_token_name() { return token; }

    string get_type() { return type; }
};

class SymbolTable {
    vector<Identifier> table;

   public:
    void add_id(string token, string type, int line) {
        Identifier id(token, type, line);
        table.push_back(id);
    }

    int search_symbol_table(string id) {
        for (int i = 0; i < table.size(); i++) {
            if (table[i].get_token_name().compare(id) == 0) return i;
        }
        return -1;
    }

    void add_ids_from_tokens(vector<Token> tokens) {
        for (int i = 0; i <= tokens.size(); i++) {
            if (tokens[i].get_type() == 'I') {
                int token_id = search_symbol_table(tokens[i].get_token());
                if (set<string>{"int", "string", "char"}.count(tokens[i - 1].get_token()) > 0) {
                    if (token_id != -1) {
                        cout << tokens[i].get_token() << " defined again at line " << tokens[i].get_line_no() << endl;
                        cout << "First definition at " << table[token_id].get_line_dec() << endl;
                    } else {
                        add_id(tokens[i].get_token(), tokens[i - 1].get_token(), tokens[i].get_line_no());
                    }
                } else {
                    if (token_id != -1) {
                        table[token_id].add_ref(tokens[i].get_line_no());
                    } else {
                        cout << "No definition found for " << tokens[i].get_token() << " at line " << tokens[i].get_line_no() << endl;
                    }
                }
            }
        }
    }

    void print_symbol_table() {
        cout << "Symbol Table:\n";
        cout << "Token\tType\tDeclared\tReferenced\n";
        for (auto it : table) {
            cout << it.get_token_name() << "\t" << it.get_type() << "\t" << it.get_line_dec() << "\t\t";
            for (auto i : it.get_line_refs()) {
                cout << i << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    Analyzer lexical = Analyzer("test.txt");
    vector<Token> tokens = lexical.run_scan();
    SymbolTable table;
    table.add_ids_from_tokens(tokens);
    table.print_symbol_table();
    return 0;
}