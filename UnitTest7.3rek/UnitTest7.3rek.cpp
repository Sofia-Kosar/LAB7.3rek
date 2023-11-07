#include "pch.h"
#include "CppUnitTest.h"
#include "../LAB7.3rek/LAB7.3rek.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest73rek
{
	TEST_CLASS(UnitTest73rek)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			const int Count = 3;
			int** testArray = new int* [Count];
			for (int i = 0; i < Count; ++i) {
				testArray[i] = new int[Count];
				for (int j = 0; j < Count; ++j) {
					testArray[i][j] = i * Count + j; // Заповнення масиву значеннями
				}
			}

			int row = 0, col = 0, result = 0;
			GetAbsSumRecursive(testArray, Count, row, col, result);
			Assert::AreEqual(result, 8);

			for (int i = 0; i < Count; ++i) {
				delete[] testArray[i];
			}
			delete[] testArray;
		}
	};
}
