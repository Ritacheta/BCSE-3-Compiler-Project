#include <bits/stdc++.h>
using namespace std;

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

class SymbolTable{

};

class Analyzer {
    string filename;
    vector<string> keywords;
    vector<string> symbols;

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

    void run_scan() {
        vector<vector<Token>> lines;
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
        vector<Token>* line = new vector<Token>;
        // iterate through tokens
        for (auto it : contents) {
            if (((sym.back() >= 'A' && sym.back() <= 'Z') || (sym.back() >= 'a' && sym.back() <= 'z') || (sym.back() >= '0' && sym.back() <= '9')) &&
                ((it >= 'A' && it <= 'Z') || (it >= 'a' && it <= 'z') || (it >= '0' && it <= '9'))) {
                sym.append(string(1, it));
                continue;
            } else {
                if (is_keyword(sym)) {
                    line->push_back(Token(sym, ln, 'K'));
                } else if (is_symbol(sym)) {
                    line->push_back(Token(sym, ln, 'S'));
                } else if (is_num(sym)) {
                    line->push_back(Token(sym, ln, 'N'));
                } else if (is_id(sym)) {
                    line->push_back(Token(sym, ln, 'I'));
                } else if (sym.length() > 0) {
                    cout << "Couldn't identify :" << sym << "\n";
                }
                sym = "";
                if (!(it == ' ' || it == '\n')) sym.append(string(1, it));
            }
            if (it == '\n') {
                ln++;
                lines.push_back(*line);
                line = new vector<Token>;
            }
        }
        for (auto it : lines) {
            for (auto j : it) {
                cout << j.get_token() << " " << j.get_type() << " " << j.get_line_no() << "\n";
            }
            // cout<<endl;
        }
    }
};

int main() {
    Analyzer lexical = Analyzer("test.txt");
    lexical.run_scan();
    return 0;
}