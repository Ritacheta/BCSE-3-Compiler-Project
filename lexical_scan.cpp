#include <bits/stdc++.h>
using namespace std;

/*
    Keyword - K
    Identifier - I
    Symbol - S
    Value - V
*/

class Token {
    string token;
    int line_no;
    char type;

   public:
    Token(string symbol, int ln, char t) {
        token = string(symbol);
        line_no = ln;
        type = t;
    }

    string get_token() { return token; }

    char get_type() { return type; }

    int get_line_no() { return line_no; }
};

class Analyzer {
    string filename;
    vector<string> keywords;
    vector<string> symbols;
    vector<Token> lines;

   public:
    Analyzer(string fn, string keywordfile = "keywords.txt", string symbolfile = "symbols.txt") {
        filename = string(fn);
        // Read keywords and symbols
        ifstream fin = ifstream(keywordfile);
        char* symbol = new char[10];
        while (fin.getline(symbol, 10)) {
            keywords.push_back(symbol);
        }
        fin.close();
        fin = ifstream(symbolfile);
        while (fin.getline(symbol, 10)) {
            symbols.push_back(symbol);
        }
        fin.close();
    }

    bool is_keyword(string token) {
        for (auto it : keywords) {
            if (it == token) {
                return true;
            }
        }
        return false;
    }

    bool is_symbol(string token) {
        for (auto it : symbols) {
            if (it == token) {
                return true;
            }
        }
        return false;
    }

    bool is_id(string token) {
        if ((token[0] >= 'A' && token[0] <= 'Z') || (token[0] >= 'a' && token[0] <= 'z')) return true;
        return false;
    }

    bool is_num(string token) {
        if (token.length() == 0) return false;
        for (auto it : token) {
            if (!(it >= '0' && it <= '9')) {
                return false;
            }
        }
        return true;
    }

    vector<Token> run_scan() {
        // Read CPP file
        ifstream fin(filename);
        stringstream buffer;
        buffer << fin.rdbuf();
        string contents = buffer.str();
        fin.close();
        // Add a \n so that last character is read
        contents.append("\n");
        string sym;
        int ln = 1;  // line number
        char str_flag = '\0';
        // iterate through tokens
        for (auto it : contents) {
            if ((str_flag == '\'' || str_flag == '\"') && str_flag != it) {
                sym.append(string(1, it));
            } else if (((sym.back() >= 'A' && sym.back() <= 'Z') || (sym.back() >= 'a' && sym.back() <= 'z') ||
                        (sym.back() >= '0' && sym.back() <= '9')) &&
                       ((it >= 'A' && it <= 'Z') || (it >= 'a' && it <= 'z') || (it >= '0' && it <= '9'))) {
                sym.append(string(1, it));
            } else {
                if (str_flag == it) {
                    lines.push_back(Token(sym, ln, 'V'));
                } else if (is_keyword(sym)) {
                    lines.push_back(Token(sym, ln, 'K'));
                } else if (is_symbol(sym)) {
                    lines.push_back(Token(sym, ln, 'S'));
                } else if (is_num(sym)) {
                    lines.push_back(Token(sym, ln, 'V'));
                } else if (is_id(sym)) {
                    lines.push_back(Token(sym, ln, 'I'));
                } else if (sym.length() > 0) {
                    cout << "Couldn't identify : " << sym << "\n";
                }
                sym = "";
                if (!(it == ' ' || it == '\n')) sym.append(string(1, it));
                if (it == '\'' || it == '\"') {
                    if (str_flag != it){
                        lines.push_back(Token(sym, ln, 'S'));
                        sym = "";
                        str_flag = it;
                    }
                    else
                        str_flag = '\0';
                }
            }
            if (it == '\n') {
                ln++;
            }
        }
        return lines;
    }

    void print_tokens() {
        cout<<"Lexical Analyzer:\n";
        for (auto it : lines) {
            cout << it.get_token() << " " << it.get_type() << " " << it.get_line_no() << "\n";
        }
    }
};

int main() {
    Analyzer lexical = Analyzer("test.txt");
    lexical.run_scan();
    lexical.print_tokens();
    return 0;
}