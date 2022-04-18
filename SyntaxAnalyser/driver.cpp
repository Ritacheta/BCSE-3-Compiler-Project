#include "./LexicalAnalyser/lexical_analyser.h"
#include "./Parser/parser.h"
#include "inter.h"

using namespace std;

int main(int argc, char* argv[]) {
    char* filename = new char[50];
    if(argc!=2) {
        strcpy(filename, "./input/input.cpp");
    }
    else {
        filename = argv[1];
    }
    cout<<"Compiler Design\n";
    if(!lex(filename)) return 0;
    string s = printint(tokens);
    if(s=="") return 0;
    if(parse(s)) cout<<"Result:\n The Program is Syntactically Correct!!!\n\n";
    else cout<<"Result:\n Error during parsing!!\n\n";
    return 0;
}