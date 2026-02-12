/*
################################################################################
# Encoding: UTF-8                                                  Tab size: 4 #
#                                                                              #
#                      UNIT TESTS FOR BITFIELD FUNCTIONS                       #
#                                                                              #
# Ordnung muss sein!                             Copyleft (Ɔ) Eugene Zamlinsky #
################################################################################
*/
# include	<BitField.h>
# include	"RandomArray.hpp"
# include	"Common.hpp"
# include	"bit_field/Bit.hpp"
# include	"bit_field/Search.hpp"

//****************************************************************************//
//      Run all the unit-test functions                                       //
//****************************************************************************//
int main()
try {

	// Bit field operations
	TestGetBit();
	TestSetBit();
	TestSetBits();
	TestResetBit();
	TestResetBits();
	TestInvertBit();
	TestInvertBits();

	// Search operations
	TestFindSetBitFwd();
	TestFindResetBitFwd();
	TestFindSetBitBwd();
	TestFindResetBitBwd();
	TestCountBits();
	TestCheckSetBit();
	TestCheckResetBit();

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
