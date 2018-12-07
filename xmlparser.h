#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>

class XMLParser
{
public:
    XMLParser(std::string filename);
    std::vector<std::pair<int,int>> getIntervals();
private:
    std::string stripString(std::string str);
    std::vector<std::string> getData(const std::string& text,const std::string &tag );
    std::vector<std::pair<int,int>> intervals;
};

#endif // XMLPARSER_H
