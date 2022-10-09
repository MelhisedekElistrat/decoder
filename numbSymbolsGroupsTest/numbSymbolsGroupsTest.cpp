#include "pch.h"
#include "CppUnitTest.h"
#include "../decoder/decoder.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace numbSymbolsGroupsTest
{
	TEST_CLASS(numbSymbolsGroupsTest)
	{
	public:
		
		TEST_METHOD(typicalTest)
		{
			std::string str = "abobaA";

			int sizeGroups = numbSymbolsGroups(str);

			int exp_sizeGroups = 2;

			Assert::AreEqual(sizeGroups, exp_sizeGroups);
		}

		TEST_METHOD(stringIsSpaces)
		{
			std::string str = "           d";

			int sizeGroups = numbSymbolsGroups(str);

			int exp_sizeGroups = 5;

			Assert::AreEqual(sizeGroups, exp_sizeGroups);			
		}

		TEST_METHOD(stringWithNotSpaces)
		{
			std::string str = "dncjjcnkF";

			int sizeGroups = numbSymbolsGroups(str);

			int exp_sizeGroups = 7;

			Assert::AreEqual(sizeGroups, exp_sizeGroups);
		}

		TEST_METHOD(lastLetterIsUpper)
		{
			std::string str = "abcdA";

			int sizeGroups = numbSymbolsGroups(str);

			int exp_sizeGroups = 2;

			Assert::AreEqual(sizeGroups, exp_sizeGroups);
		}

		TEST_METHOD(lastLetterIsLower)
		{
			std::string str = "abcda";

			int sizeGroups = numbSymbolsGroups(str);

			int exp_sizeGroups = 2;

			Assert::AreEqual(sizeGroups, exp_sizeGroups);
		}

		TEST_METHOD(stringIsCyrillicBesidesLastSymbol)
		{
			std::string str = "абдгa";

			int sizeGroups = numbSymbolsGroups(str);

			int exp_sizeGroups = 2;

			Assert::AreEqual(sizeGroups, exp_sizeGroups);
		}

		TEST_METHOD(lastSymbolSpansEntireString)
		{
			std::string str = "abcdv";

			int sizeGroups = numbSymbolsGroups(str);

			int exp_sizeGroups = 23;

			Assert::AreEqual(sizeGroups, exp_sizeGroups);
		}

		TEST_METHOD(lastSymbolSpansNotEntireString)
		{
			std::string str = "abcda";

			int sizeGroups = numbSymbolsGroups(str);

			int exp_sizeGroups = 2;

			Assert::AreEqual(sizeGroups, exp_sizeGroups);
		}

		TEST_METHOD(lastSymbolIsNotLetterOfLatinAlphabet)
		{
			std::string str = "abcd~";

			int sizeGroups = numbSymbolsGroups(str);

			int exp_sizeGroups = 3456;

			Assert::AreEqual(sizeGroups, exp_sizeGroups);
		}
	};
}
