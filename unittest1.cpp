#include "stdafx.h"
#include "CppUnitTest.h"
#include "D:\Programming\listat\primegenerator.h"
#include "D:\Programming\listat\primegenerator.cpp"
#include "D:\Programming\listat\xmlparser.h"
#include "D:\Programming\listat\xmlparser.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(PrimeGeneratorTest)
	{
	public:

		TEST_METHOD(SimpleValuesTesting)
		{
			PrimeGenerator pg;
			auto primes = pg.getPrimesInterval(2, 3);
			std::set<int> expected = { 2, 3 };
			Assert::IsTrue(primes == expected);
			primes = pg.getPrimesInterval(3, 2);
			Assert::IsTrue(primes == expected);
			primes = pg.getPrimesInterval(100, 110);
			expected = { 101, 103, 107, 109 };
			Assert::IsTrue(primes == expected);
		}
		TEST_METHOD(NegativeValuesTesting)
		{
			PrimeGenerator pg;
			auto primes = pg.getPrimesInterval(-500000, 3);
			std::set<int> expected = { 2, 3 };
			Assert::IsTrue(primes == expected);
			primes = pg.getPrimesInterval(-10, 0);
			expected.clear();
			Assert::IsTrue(primes == expected);
		}
	};
	TEST_CLASS(XMLParserTest)
	{
		TEST_METHOD(simpleXMLParserTesting)
		{	
			std::string text = "<root>\n <intervals>\n  <interval>\n   <low> 2 </low>\n   <high> 3 </high>\n  </interval>\n </intervals>\n</root>";
			std::ofstream in;
			in.open("input.xml");
			if (in.is_open())
			{
				in << text << std::endl;
			}
			in.close();
			XMLParser xml("input.xml");
			auto intervals = xml.getIntervals();
			std::pair<int, int> expected = { 2, 3 };
			Assert::IsTrue(intervals.at(0) == expected);
		}

		TEST_METHOD(TestWithNegativeValues)
		{
			std::string text = "<root>\n <intervals>\n  <interval>\n   <low> -2 </low>\n   <high> 3 </high>\n  </interval>\n </intervals>\n</root>";
			std::ofstream in;
			in.open("input.xml");
			if (in.is_open())
			{
				in << text << std::endl;
			}
			in.close();
			XMLParser xml("input.xml");
			auto intervals = xml.getIntervals();
			std::pair<int, int> expected = { -2, 3 };
			Assert::IsTrue(intervals.at(0) == expected);
		}

		TEST_METHOD(TestWithMissedValues)
		{
			std::string text = "<root>\n <intervals>\n  <interval>\n   <low>  </low>\n   <high> 3 </high>\n  </interval>\n </intervals>\n</root>";
			std::ofstream in;
			in.open("input.xml");
			if (in.is_open())
			{
				in << text << std::endl;
			}
			in.close();
			XMLParser xml("input.xml");
			auto intervals = xml.getIntervals();
			std::pair<int, int> expected = { 0, 0 };
			Assert::IsTrue(intervals.at(0) == expected);
		}

		TEST_METHOD(TestWithFloatValues)
		{
			std::string text = "<root>\n <intervals>\n  <interval>\n  <low> -2.56 </low>\n   <high> 3.768456 </high>\n  </interval>\n </intervals>\n</root>";
			std::ofstream in;
			in.open("input.xml");
			if (in.is_open())
			{
				in << text << std::endl;
			}
			in.close();
			XMLParser xml("input.xml");
			auto intervals = xml.getIntervals();
			std::pair<int, int> expected = { -2, 3 };
			Assert::IsTrue(intervals.at(0) == expected);
		}
	};
}
