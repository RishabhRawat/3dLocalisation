#ifndef FILEREADER_H
#define FILEREADER_H
#include <cstring>
#include <vector>
#include <fstream>

class fileReader
{
private:
    std::ifstream myfile;
    std::vector<std::vector<std::string>> data;
    int countSubstring(const std::string& str, const std::string& sub);
public:
    fileReader(const char * filename);
    fileReader();
    void open(const char *filename);
    std::vector<std::string> operator [](int index){
        return data[index];
    }
    inline int getLength(){return data.size();}
};

#endif // FILEREADER_H
