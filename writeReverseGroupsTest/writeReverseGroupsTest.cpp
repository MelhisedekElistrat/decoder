#include "pch.h"
#include "CppUnitTest.h"
#include "../decoder/decoder.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace writeReverseGroupsTest
{
	TEST_CLASS(writeReverseGroupsTest)
	{
	public:
		
		TEST_METHOD(typicalTest)
		{
			std::vector<std::string> arrayOfStringsForReverse = {
				"ab",
				"ob",
				"a"
			};

			std::string endString = writeReverseGroups(arrayOfStringsForReverse);

			std::string exp_endString = "aobab";

			Assert::AreEqual(endString, exp_endString);
		}

		TEST_METHOD(oneGroup)
		{
			std::vector<std::string> arrayOfStringsForReverse = { "aboba" };

			std::string endString = writeReverseGroups(arrayOfStringsForReverse);

			std::string exp_endString = "aboba";

			Assert::AreEqual(endString, exp_endString);
		}


		TEST_METHOD(manyGroups)
		{
			std::vector<std::string> arrayOfStringsForReverse = { "abc", "def", "ghi", "jkl", "mno",
				"pqr", "stu", "vwx", "yza", "bcd", "efg", "hij", "klm", "nop", "qrs", "tuv", "wxy", "z" };

			std::string endString = writeReverseGroups(arrayOfStringsForReverse);

			std::string exp_endString = "zwxytuvqrsnopklmhijefgbcdyzavwxstupqrmnojklghidefabc";

			Assert::AreEqual(endString, exp_endString);
		}

		TEST_METHOD(lastGroupWithMaxNumbSymbols)
		{
			std::vector<std::string> arrayOfStringsForReverse = { "abc", "dec" };

			std::string endString = writeReverseGroups(arrayOfStringsForReverse);

			std::string exp_endString = "decabc";

			Assert::AreEqual(endString, exp_endString);
		}

		TEST_METHOD(lastGroupWithNotMaxNumbSymbols)
		{
			std::vector<std::string> arrayOfStringsForReverse = {
				"abc",
				"de"
			};

			std::string endString = writeReverseGroups(arrayOfStringsForReverse);

			std::string exp_endString = "deabc";

			Assert::AreEqual(endString, exp_endString);
		}

		TEST_METHOD(stringsWithSpaces)
		{
			std::vector<std::string> arrayOfStringsForReverse = {
				"  ",
				"  ",
				"  ",
				"  ",
			};

			std::string endString = writeReverseGroups(arrayOfStringsForReverse);

			std::string exp_endString = "        ";

			Assert::AreEqual(endString, exp_endString);
		}

		TEST_METHOD(stringsWithNotSpaces)
		{
			std::vector<std::string> arrayOfStringsForReverse = {
				"fr56",
				"4thm",
				"v35g",
				";45.",
				"/,49",
				"rj4"
			};

			std::string endString = writeReverseGroups(arrayOfStringsForReverse);

			std::string exp_endString = "rj4/,49;45.v35g4thmfr56";

			Assert::AreEqual(endString, exp_endString);
		}

		TEST_METHOD(stringsIsCyrillicBesadesLastSymbol)
		{
			std::vector<std::string> arrayOfStringsForReverse = {
				"аб",
				"сд"
			};

			std::string endString = writeReverseGroups(arrayOfStringsForReverse);

			std::string exp_endString = "сдаб";

			Assert::AreEqual(endString, exp_endString);
		}

		TEST_METHOD(stringsIsNotCyrillic)
		{
			std::vector<std::string> arrayOfStringsForReverse = {
				"ab",
				"ob",
				"us"
			};

			std::string endString = writeReverseGroups(arrayOfStringsForReverse);

			std::string exp_endString = "usobab";

			Assert::AreEqual(endString, exp_endString);
		}
	};
}