/*
################################################################################
# Encoding: UTF-8                                                  Tab size: 4 #
#                                                                              #
#                     UNIT TESTS FOR ARRAY COPY FUNCTIONS                      #
#                                                                              #
# Ordnung muss sein!                             Copyleft (Ɔ) Eugene Zamlinsky #
################################################################################
*/
# pragma	once

//****************************************************************************//
//      Reference implementation of the function                              //
//****************************************************************************//
template <typename T>
void Copy (T target[], const T source[], size_t size) {
	for (size_t i = 0; i < size; ++i)
		target[i] = source[i];
}

//****************************************************************************//
//      Unit test routine                                                     //
//****************************************************************************//
void TestCopy (void) {

	// Show the stage info
	StageInfo ("Array::Copy", BUFFER_SIZE, ROUNDS, TRIES);

	// Unsigned integer types
	TestVector <uint8_t> (Array::Copy, Copy);
	TestVector <uint16_t> (Array::Copy, Copy);
	TestVector <uint32_t> (Array::Copy, Copy);
	TestVector <uint64_t> (Array::Copy, Copy);

	// Signed integer types
	TestVector <sint8_t> (Array::Copy, Copy);
	TestVector <sint16_t> (Array::Copy, Copy);
	TestVector <sint32_t> (Array::Copy, Copy);
	TestVector <sint64_t> (Array::Copy, Copy);

	// Floating-point types
	TestVector <flt32_t> (Array::Copy, Copy);
	TestVector <flt64_t> (Array::Copy, Copy);

	// Other types
	TestVector <size_t> (Array::Copy, Copy);
}
/*
################################################################################
#                                 END OF FILE                                  #
################################################################################
*/
