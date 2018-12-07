#include "xmlProcessor.h"

xmlProcessor::xmlProcessor(std::string filename) : _filename(filename)
{
}

void xmlProcessor::run()
{
	PrimeGenerator pg;
	std::set<int> values;
	std::vector <std::future<std::set<int>>> treads;
	auto parser = XMLParser(_filename);
	std::vector<std::pair<int, int>> intervals = parser.getIntervals();
	for (auto it = intervals.begin(); it != intervals.end(); ++it)
	{
		treads.push_back(std::async([&pg, it](){
			std::set<int> primes = pg.getPrimesInterval(it->first, it->second);
			return primes;
		}));
	}
	for (auto it = treads.begin(); it != treads.end(); ++it)
	{
		std::set<int>primes = it->get();
		values.insert(primes.begin(), primes.end());
	}
	generateXml(values);
}

void xmlProcessor::generateXml(const std::set<int>& values) const
{
    std::string text="<root>\n <primes>";
    for (auto it = values.begin(); it != values.end(); ++it)
    {
        text=text + " " + std::to_string(*it);
    }
    text=text+" </primes>\n</root>";

    std::ofstream out;
    out.open("output.xml");
    if (out.is_open())
    {
        out << text << std::endl;
    }
    out.close();
    std::cout<<"Unique primes created in file output.xml"<<std::endl;
}
