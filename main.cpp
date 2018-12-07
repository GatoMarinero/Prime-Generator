#include <iostream>
#include "xmlProcessor.h"
#include "primegenerator.h"

using namespace std;

int main(int args, char* argv[])
{	
	std::string filename;
	if (args != 2 )
		filename = "input.xml";
	else
		filename = argv[1];
    xmlProcessor xml(filename);
	xml.run();
    return 0;
}

