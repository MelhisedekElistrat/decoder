#include "pch.h"
#include "CppUnitTest.h"
#include "../decoder/decoder.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace decodingStringsTest
{
	TEST_CLASS(decodingStringsTest)
	{
	public:
		
		TEST_METHOD(typicalTest)
		{
			std::string str = "fnjrnfkd";

			bool correctInput = decodingString(str);

			Assert::IsTrue(correctInput);

			std::string exp_str = "fkfnjrn";

			Assert::AreEqual(str, exp_str);
		}

		TEST_METHOD(stringWithSpaces)
		{
			std::string str = "           d";

			bool correctInput = decodingString(str);

			Assert::IsTrue(correctInput);

			std::string exp_str = "           ";

			Assert::AreEqual(str, exp_str);
		}

		TEST_METHOD(stringWithNotSpaces)
		{
			std::string str = "dncjjcnkF";

			bool correctInput = decodingString(str);

			Assert::IsTrue(correctInput);

			std::string exp_str = "kdncjjcn";

			Assert::AreEqual(str, exp_str);
		}

		TEST_METHOD(lastLetterIsUpper)
		{
			std::string str = "abcdA";

			bool correctInput = decodingString(str);

			Assert::IsTrue(correctInput);

			std::string exp_str = "cdab";

			Assert::AreEqual(str, exp_str);
		}

		TEST_METHOD(lastLetterIsLower)
		{
			std::string str = "abcda";

			bool correctInput = decodingString(str);

			Assert::IsTrue(correctInput);

			std::string exp_str = "cdab";

			Assert::AreEqual(str, exp_str);
		}

		TEST_METHOD(stringIsCyrillicBesidesLastSymbol)
		{
			std::string str = "абдгa";

			bool correctInput = decodingString(str);

			Assert::IsTrue(correctInput);

			std::string exp_str = "дгаб";

			Assert::AreEqual(str, exp_str);
		}

		TEST_METHOD(lastSymbolSpanEntireString)
		{
			std::string str = "abcdv";

			bool correctInput = decodingString(str);

			Assert::IsTrue(correctInput);

			std::string exp_str = "abcd";

			Assert::AreEqual(str, exp_str);
		}

		TEST_METHOD(lastSymbolSpanNotEntireString)
		{
			std::string str = "abcda";

			bool correctInput = decodingString(str);

			Assert::IsTrue(correctInput);

			std::string exp_str = "cdab";

			Assert::AreEqual(str, exp_str);
		}

		TEST_METHOD(falseResult)
		{
			std::string str = "abcde2";

			bool correctInput = decodingString(str);

			Assert::IsTrue(!correctInput);
		}
	};
}
