#include "pch.h"
#include "CppUnitTest.h"
#include "../decoder/decoder.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace writeGroupsToArrayStringsTest
{
	TEST_CLASS(writeGroupsToArrayStringsTest)
	{
	public:
		
		TEST_METHOD(typicalTest)
		{
			std::string stringForReverseGroups = "aboba";
			int numbSymbolsInGroup = 2;
			int numbGroups = 3;
			std::vector<std::string> arrayOfStringsForReverse = writeGroupsToArrayStrings(stringForReverseGroups, numbSymbolsInGroup, numbGroups);

			std::vector<std::string> exp_arrayOfStringsForReverse = {
				"ab", 
				"ob", 
				"a"				
			};

			for(int i = 0; i < numbGroups; i++)
				Assert::AreEqual(arrayOfStringsForReverse[i], exp_arrayOfStringsForReverse[i]);
		}

		TEST_METHOD(oneGroup)
		{
			std::string stringForReverseGroups = "aboba";
			int numbSymbolsInGroup = 15;
			int numbGroups = 1;
			std::vector<std::string> arrayOfStringsForReverse = writeGroupsToArrayStrings(stringForReverseGroups, numbSymbolsInGroup, numbGroups);

			std::vector<std::string> exp_arrayOfStringsForReverse = { "aboba" };

			for (int i = 0; i < numbGroups; i++)
				Assert::AreEqual(arrayOfStringsForReverse[i], exp_arrayOfStringsForReverse[i]);
		}

		TEST_METHOD(manyGroups)
		{
			std::string stringForReverseGroups = "abobasad";
			int numbSymbolsInGroup = 2;
			int numbGroups = 4;
			std::vector<std::string> arrayOfStringsForReverse = writeGroupsToArrayStrings(stringForReverseGroups, numbSymbolsInGroup, numbGroups);

			std::vector<std::string> exp_arrayOfStringsForReverse = {
				"ab", 
				"ob", 
				"as", 
				"ad" 
			};

			for (int i = 0; i < numbGroups; i++)
				Assert::AreEqual(arrayOfStringsForReverse[i], exp_arrayOfStringsForReverse[i]);
		}

		TEST_METHOD(inLastGroupSymbolsLess)
		{
			std::string stringForReverseGroups = "NeAboba";
			int numbSymbolsInGroup = 15;
			int numbGroups = 1;
			std::vector<std::string> arrayOfStringsForReverse = writeGroupsToArrayStrings(stringForReverseGroups, numbSymbolsInGroup, numbGroups);

			std::vector<std::string> exp_arrayOfStringsForReverse = { "NeAboba" };

			for (int i = 0; i < numbGroups; i++)
				Assert::AreEqual(arrayOfStringsForReverse[i], exp_arrayOfStringsForReverse[i]);
		}

		TEST_METHOD(inLastGroupStrictNumberOfSymbols)
		{
			std::string stringForReverseGroups = "abobasad";
			int numbSymbolsInGroup = 4;
			int numbGroups = 2;
			std::vector<std::string> arrayOfStringsForReverse = writeGroupsToArrayStrings(stringForReverseGroups, numbSymbolsInGroup, numbGroups);

			std::vector<std::string> exp_arrayOfStringsForReverse = { 
				"abob",
				"asad"				
			};

			for (int i = 0; i < numbGroups; i++)
				Assert::AreEqual(arrayOfStringsForReverse[i], exp_arrayOfStringsForReverse[i]);
		}

		TEST_METHOD(stringsWithSpaces)
		{
			std::string stringForReverseGroups = "        ";
			int numbSymbolsInGroup = 2;
			int numbGroups = 4;
			std::vector<std::string> arrayOfStringsForReverse = writeGroupsToArrayStrings(stringForReverseGroups, numbSymbolsInGroup, numbGroups);

			std::vector<std::string> exp_arrayOfStringsForReverse = {
				"  ",
				"  ",
				"  ",
				"  "
			};

			for (int i = 0; i < numbGroups; i++)
				Assert::AreEqual(arrayOfStringsForReverse[i], exp_arrayOfStringsForReverse[i]);
		}

		TEST_METHOD(stringWithNotSpaces)
		{
			std::string stringForReverseGroups = "fr564  mv35 ;45./,4 rj4a";
			int numbSymbolsInGroup = 4;
			int numbGroups = 6;
			std::vector<std::string> arrayOfStringsForReverse = writeGroupsToArrayStrings(stringForReverseGroups, numbSymbolsInGroup, numbGroups);

			std::vector<std::string> exp_arrayOfStringsForReverse = {
				"fr56",
				"4  m",
				"v35 ",
				";45.",
				"/,4 ",
				"rj4a"
			};

			for (int i = 0; i < numbGroups; i++)
				Assert::AreEqual(arrayOfStringsForReverse[i], exp_arrayOfStringsForReverse[i]);
		}

		TEST_METHOD(stringInCyrillicBesadesLastSymbol)
		{
			std::string stringForReverseGroups = "абсд";
			int numbSymbolsInGroup = 2;
			int numbGroups = 2;
			std::vector<std::string> arrayOfStringsForReverse = writeGroupsToArrayStrings(stringForReverseGroups, numbSymbolsInGroup, numbGroups);

			std::vector<std::string> exp_arrayOfStringsForReverse = {
				"аб",
				"сд",
			};

			for (int i = 0; i < numbGroups; i++)
				Assert::AreEqual(arrayOfStringsForReverse[i], exp_arrayOfStringsForReverse[i]);
		}

		TEST_METHOD(stringInNotCyrillic)
		{
			std::string stringForReverseGroups = "abcd";
			int numbSymbolsInGroup = 2;
			int numbGroups = 2;
			std::vector<std::string> arrayOfStringsForReverse = writeGroupsToArrayStrings(stringForReverseGroups, numbSymbolsInGroup, numbGroups);

			std::vector<std::string> exp_arrayOfStringsForReverse = {
				"ab",
				"cd",
			};

			for (int i = 0; i < numbGroups; i++)
				Assert::AreEqual(arrayOfStringsForReverse[i], exp_arrayOfStringsForReverse[i]);
		}

		TEST_METHOD(lastSymbolSpanEntireString)
		{
			std::string stringForReverseGroups = "абвгe";
			int numbSymbolsInGroup = 5;
			int numbGroups = 1;
			std::vector<std::string> arrayOfStringsForReverse = writeGroupsToArrayStrings(stringForReverseGroups, numbSymbolsInGroup, numbGroups);

			std::vector<std::string> exp_arrayOfStringsForReverse = {
				"абвгe"
			};

			for (int i = 0; i < numbGroups; i++)
				Assert::AreEqual(arrayOfStringsForReverse[i], exp_arrayOfStringsForReverse[i]);
		}

		TEST_METHOD(lastSymbolNotSpanEntireString)
		{
			std::string stringForReverseGroups = "hjtdjrm";
			int numbSymbolsInGroup = 6;
			int numbGroups = 2;
			std::vector<std::string> arrayOfStringsForReverse = writeGroupsToArrayStrings(stringForReverseGroups, numbSymbolsInGroup, numbGroups);

			std::vector<std::string> exp_arrayOfStringsForReverse = {
				"hjtdjr",
				"m"
			};

			for (int i = 0; i < numbGroups; i++)
				Assert::AreEqual(arrayOfStringsForReverse[i], exp_arrayOfStringsForReverse[i]);
		}
	};
}
