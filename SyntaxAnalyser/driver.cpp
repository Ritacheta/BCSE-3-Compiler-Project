#include "./LexicalAnalyser/lexical_analyser.h"
#include "./Parser/parser.h"
#include "inter.h"

using namespace std;

int main(int argc, char* argv[]) {
    string filename;
    if (argc != 2) {
        filename = "./input/input.cpp";
    } else {
        filename = argv[1];
    }
    convertToChar(filename);
    cout << "Compiler Design\n";
    if (!lex("./input/converted_input.txt")) return 0;
    string s = printint(tokens);
    cout<<"\nOutput From the Lexical Analyser: "<<s<<endl;
    if (s == "") return 0;
    if (parse(s))
        cout << "Result:\n The Program is Syntactically Correct!!!\n\n";
    else
        cout << "Result:\n Error during parsing!!\n\n";
    return 0;
}