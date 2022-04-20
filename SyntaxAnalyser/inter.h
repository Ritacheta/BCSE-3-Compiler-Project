#include <bits/stdc++.h>
using namespace std;
using std::regex_replace; using std::regex;

void convertToChar(string inputFile){
    ifstream ifile;
    ofstream ofile;
    ifile.open(inputFile);
    ofile.open("./input/converted_input.txt");
    string line;
    while(getline(ifile, line)){

        string ouput=regex_replace(line, regex("\\.gt."), ">");
        ouput=regex_replace(ouput, regex("\\.lt."), "<");
        ouput=regex_replace(ouput, regex("\\.eq."), "~");
        ouput=regex_replace(ouput, regex("\\.and."), "&");
        ouput=regex_replace(ouput, regex("\\.or."), "|");
        ofile<<ouput;
        ofile<<'\n';
    }
    ofile.close();
    ifile.close();
}