/*
################################################################################
# Encoding: UTF-8                                                  Tab size: 4 #
#                                                                              #
#                  UNIT TESTS FOR REVERSING OF ARRAY ELEMENTS                  #
#                                                                              #
# Ordnung muss sein!                             Copyleft (Ɔ) Eugene Zamlinsky #
################################################################################
*/
# pragma	once

//****************************************************************************//
//      Reference implementation of the function                              //
//****************************************************************************//
template <typename T>
void Reverse (T array[], size_t size){
	for (size_t i = 0; i < size / 2; i++) {
		T t1 = array[i];
		T t2 = array[size - 1 - i];
		array[i] = t2;
		array[size - 1 - i] = t1;
	}
}

//****************************************************************************//
//      Unit test routine                                                     //
//****************************************************************************//
void TestReverse (void) {

	// Show the stage info
	StageInfo ("Array::Reverse", BUFFER_SIZE, ROUNDS, TRIES);

	// Unsigned integer types
	TestUnary <uint8_t> (Array::Reverse, Reverse);
	TestUnary <uint16_t> (Array::Reverse, Reverse);
	TestUnary <uint32_t> (Array::Reverse, Reverse);
	TestUnary <uint64_t> (Array::Reverse, Reverse);

	// Signed integer types
	TestUnary <sint8_t> (Array::Reverse, Reverse);
	TestUnary <sint16_t> (Array::Reverse, Reverse);
	TestUnary <sint32_t> (Array::Reverse, Reverse);
	TestUnary <sint64_t> (Array::Reverse, Reverse);

	// Floating-point types
	TestUnary <flt32_t> (Array::Reverse, Reverse);
	TestUnary <flt64_t> (Array::Reverse, Reverse);

	// Other types
	TestUnary <size_t> (Array::Reverse, Reverse);
}
/*
################################################################################
#                                 END OF FILE                                  #
################################################################################
*/
