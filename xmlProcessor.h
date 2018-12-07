#ifndef XMLPROCESSOR_H
#define XMLPROCESSOR_H

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <exception>
#include <future>

#include "primegenerator.h"
#include "xmlparser.h"


class xmlProcessor
{
public:
	xmlProcessor(std::string filename);
	void run();
private:
    void generateXml(const std::set<int>& values) const;
	std::string _filename;
};

#endif // XMLPROCESSOR_H
