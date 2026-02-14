/*
################################################################################
# Encoding: UTF-8                                                  Tab size: 4 #
#                                                                              #
#                        UNIT TESTS FOR ARRAY FUNCTIONS                        #
#                                                                              #
# Ordnung muss sein!                             Copyleft (Ɔ) Eugene Zamlinsky #
################################################################################
*/
# include	<Array.h>
# include	"RandomArray.hpp"
# include	"Common.hpp"
# include	"array/Init.hpp"
# include	"array/Copy.hpp"
# include	"array/Move.hpp"
# include	"array/Clone.hpp"
# include	"array/Convert.hpp"
# include	"array/Operations.hpp"
# include	"array/Round.hpp"
# include	"array/Sum.hpp"
# include	"array/MinMax.hpp"
# include	"array/LinSearch.hpp"
# include	"array/BinSearch.hpp"
# include	"array/LinCount.hpp"
# include	"array/BinCount.hpp"
# include	"array/Replace.hpp"
# include	"array/Reverse.hpp"
# include	"array/Unique.hpp"
# include	"array/Dups.hpp"


# include	"array/RadixSort.hpp"

//****************************************************************************//
//      Run all the unit-test functions                                       //
//****************************************************************************//
int main()
try {

	// Initialization
	TestInit();

	// Copying arrays
	TestCopy();

	// Moving arrays
	TestMove();

	// Pattern cloning
	TestClone();

	// Data conversion
	TestConvert();

	// Bitwise operations
	TestByteSwap();
	TestBitReverse();
	TestPopCount();
	TestNot();
	TestAndScalar();
	TestAndVector();
	TestOrScalar();
	TestOrVector();
	TestXorScalar();
	TestXorVector();

	// Arithmetic operations
	TestNeg();
	TestAbs();
	TestNegAbs();
	TestSign();
	TestSqr();
	TestSqrt();
	TestAddScalar();
	TestAddVector();
	TestSubScalar();
	TestSubVector();
	TestReverseSubScalar();
	TestReverseSubVector();
	TestMulScalar();
	TestMulVector();
	TestDivScalar();
	TestDivVector();
	TestReverseDivScalar();
	TestReverseDivVector();

	// Fused arithmetic operations
	TestFusedAdd();
	TestFusedSub();

	// Rounding
	TestRoundDown();
	TestRoundUp();
	TestRoundInt();
	TestRoundEven();
	TestRound();
	TestTruncate();
	TestFrac();

	// Numerical integration
	TestSum();
	TestSumAbs();
	TestSumSqr();
	TestSumMul();
	TestSumDiff();
	TestSumAbsDiff();
	TestSumSqrDiff();
	TestSumMulDiff();

	TestSumDist();
	TestSumAbsDist();
	TestSumSqrDist();

	// Minimum and maximum absolute value
	TestMinAbs();
	TestMaxAbs();
	TestMinMaxAbs();

	// Minimum and maximum value
	TestMin();
	TestMax();
	TestMinMax();

	// Linear array search
	TestFindFwd();
	TestFindBwd();
	TestFindObjFwd();
	TestFindObjBwd();

	// Binary array search
	TestFindFirstEqualAsc();
	TestFindLastEqualAsc();
	TestFindGreatAsc();
	TestFindGreatOrEqualAsc();
	TestFindLessAsc();
	TestFindLessOrEqualAsc();
	TestFindFirstEqualDsc();
	TestFindLastEqualDsc();
	TestFindLessDsc();
	TestFindLessOrEqualDsc();
	TestFindGreatDsc();
	TestFindGreatOrEqualDsc();
	TestFindFirstEqualObjAsc();
	TestFindLastEqualObjAsc();
	TestFindGreatObjAsc();
	TestFindGreatOrEqualObjAsc();
	TestFindLessObjAsc();
	TestFindLessOrEqualObjAsc();
	TestFindFirstEqualObjDsc();
	TestFindLastEqualObjDsc();
	TestFindLessObjDsc();
	TestFindLessOrEqualObjDsc();
	TestFindGreatObjDsc();
	TestFindGreatOrEqualObjDsc();

	// Counting
	TestCount();
	TestCountObj();
	TestCountAsc();
	TestCountDsc();
	TestCountObjAsc();
	TestCountObjDsc();

	// Replacing
	TestReplace();
	TestReplaceObj();

	// Order reversing
	TestReverse();

	// Unique values
	TestUnique();
	TestUniqueObj();

	// Duplicate elements
	TestDuplicates();
	TestDuplicatesObj();

	// Radix sort
	TestRadixSortAsc();
	TestRadixSortDsc();
	TestRadixSortKeyAsc();
	TestRadixSortKeyDsc();

	// Everything is OK
	cout << "\nSUCCESS: All the tests have been passed!" << endl;
	return 0;
}
catch (const runtime_error &ex) {

	// Something failed
	cerr << ex.what() << endl;
	return 1;
}

/*
################################################################################
#                                 END OF FILE                                  #
################################################################################
*/
