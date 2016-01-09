#include "filereader.h"
#include <vector>
#include <cstring>
#include <fstream>
#include <sstream>
using namespace std;

vector<string> &split(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}

fileReader::fileReader(const char *filename) {
    open(filename);
}
void fileReader::open(const char *filename){
    myfile.open(filename);
    if(!myfile) {
        throw(22);
    }
    string nextString;
    while(getline(myfile,nextString)){
        if(nextString[0] == '#')
            continue;
        data.push_back(split(nextString,' '));
    }
}
fileReader::fileReader() {};
