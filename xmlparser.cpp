#include "xmlparser.h"

XMLParser::XMLParser(std::string filename)
{
    std::string text;
    char c;
    std::ifstream in( filename );
    if ( !in )
    {
        std::cout << filename << " not found";
        exit( 1 );
    }
    while ( in.get( c ) )
    {
        text += c;
    }
    in.close();
    auto lowLimits = getData(text,"low");
    auto highLimits = getData(text,"high");
    for (size_t i=0;i<lowLimits.size();++i )
    {
		try
		{
			int low = std::stoi(lowLimits[i]);
			int high = std::stoi(highLimits[i]);
			intervals.push_back({ low, high });
		}
		catch (std::exception e)
		{
			std::cout << "Missed argument in interval " << std::endl;
			intervals.push_back({ 0, 0 });
		}
    }
    std::cout<<"File "<<filename<<" have been parsed"<<std::endl;
}


std::vector<std::pair<int,int>> XMLParser::getIntervals()
{
     return intervals;
}

std::string XMLParser::stripString( std::string str)
{
    std::string striped = "";
    for (size_t i = 0 ; i < str.length(); ++i)
    {
		if (str[i] == '.')
			break;
        if(std::isalnum(str[i]))
            striped += str[i];
    }
	if (str.find('-') != std::string::npos)
		striped = "-" + striped;
    return striped;
}

std::vector<std::string> XMLParser::getData( const std::string &text,const std::string& tag )
{
    std::vector<std::string> collection;
    size_t position = 0, start;
    while ( true )
    {
        start = text.find( "<" + tag, position );
        if ( start == std::string::npos )
            return collection;
        start = text.find( ">" , start );
        start++;
        position = text.find( "</" + tag, start );
        if ( position == std::string::npos )
            return collection;
        collection.push_back( stripString(text.substr( start, position - start )) );
    }
}

