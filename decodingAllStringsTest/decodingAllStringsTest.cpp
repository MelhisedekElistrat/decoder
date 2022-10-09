#include "pch.h"
#include "CppUnitTest.h"
#include "../decoder/decoder.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace decodingAllStringsTest
{
	TEST_CLASS(decodingAllStringsTest)
	{
	public:
		
		TEST_METHOD(typeTest)
		{
			std::vector<std::string> vectStr = {
				"abcdA",
				"    v",
				"аоуьалуьвd"
			};

			decodingAllStrings(vectStr);

			std::vector<std::string> exp_vectStr = {
				"cdab",
				"    ",
				"луьваоуьа"
			};

			int exp_size_vect = exp_vectStr.size();

			int size_vect = vectStr.size();

			Assert::AreEqual(exp_size_vect, size_vect);

			for (int i = 0; i < size_vect; i++)
				Assert::AreEqual(exp_vectStr[i], vectStr[i]);
		}

		TEST_METHOD(stringsWithSpaces)
		{
			std::vector<std::string> vectStr = {
				"    A",
				"    v",
				"         d"
			};

			decodingAllStrings(vectStr);

			std::vector<std::string> exp_vectStr = {
				"    ",
				"    ",
				"         "
			};

			int exp_size_vect = exp_vectStr.size();

			int size_vect = vectStr.size();

			Assert::AreEqual(exp_size_vect, size_vect);

			for (int i = 0; i < size_vect; i++)
				Assert::AreEqual(exp_vectStr[i], vectStr[i]);
		}

		TEST_METHOD(stringsWithNotSpaces)
		{
			std::vector<std::string> vectStr = {
				"abcdA",
				"deffv",
				"abcdA"

			};

			decodingAllStrings(vectStr);

			std::vector<std::string> exp_vectStr = {
				"cdab",
				"deff",
				"cdab"
			};

			int exp_size_vect = exp_vectStr.size();

			int size_vect = vectStr.size();

			Assert::AreEqual(exp_size_vect, size_vect);

			for (int i = 0; i < size_vect; i++)
				Assert::AreEqual(exp_vectStr[i], vectStr[i]);
		}

		TEST_METHOD(lastLetterIsUpper)
		{
			std::vector<std::string> vectStr = {
				"abcdA",
				"deffV",
				"abcdA"
			};

			decodingAllStrings(vectStr);

			std::vector<std::string> exp_vectStr = {
				"cdab",
				"deff",
				"cdab"
			};

			int exp_size_vect = exp_vectStr.size();

			int size_vect = vectStr.size();

			Assert::AreEqual(exp_size_vect, size_vect);

			for (int i = 0; i < size_vect; i++)
				Assert::AreEqual(exp_vectStr[i], vectStr[i]);
		}

		TEST_METHOD(lastLetterIsLower)
		{
			std::vector<std::string> vectStr = {
				"abcdA",
				"deffv",
				"abcdA"

			};

			decodingAllStrings(vectStr);

			std::vector<std::string> exp_vectStr = {
				"cdab",	
				"deff",
				"cdab"
			};

			int exp_size_vect = exp_vectStr.size();

			int size_vect = vectStr.size();

			Assert::AreEqual(exp_size_vect, size_vect);

			for (int i = 0; i < size_vect; i++)
				Assert::AreEqual(exp_vectStr[i], vectStr[i]);
		}

		TEST_METHOD(stringsIsCyrillicBesidesLastSymbol)
		{
			std::vector<std::string> vectStr = {
				"абвгa",
				"деффv",
				"абдгa"
			};

			decodingAllStrings(vectStr);

			std::vector<std::string> exp_vectStr = {
				"вгаб",
				"дефф",
				"дгаб"
			};

			int exp_size_vect = exp_vectStr.size();

			int size_vect = vectStr.size();

			Assert::AreEqual(exp_size_vect, size_vect);

			for (int i = 0; i < size_vect; i++)
				Assert::AreEqual(exp_vectStr[i], vectStr[i]);
		}

		TEST_METHOD(additionalTest)
		{
			std::vector<std::string> vectStr = {
				"agnton Sinket ise ag TleAla",
				"Weinn'n  keibt'se gi TagAllec",
				" Tage alleollst du sAberd",
				"einr s mi zuiebt lechRb"
			};

			decodingAllStrings(vectStr);

			std::vector<std::string> exp_vectStr = {
				"Alle Tage ist kein Sonntag",
				"Alle Tage gibt's kein'n Wein",
				"Aber du sollst alle Tage",
				"Recht lieb zu mir sein"
			};

			int exp_size_vect = exp_vectStr.size();

			int size_vect = vectStr.size();

			Assert::AreEqual(exp_size_vect, size_vect);

			for (int i = 0; i < size_vect; i++)
				Assert::AreEqual(exp_vectStr[i], vectStr[i]);
		}
	};
}
