/*
################################################################################
# Encoding: UTF-8                                                  Tab size: 4 #
#                                                                              #
#                UNIT TESTS FOR ARRAY PATTERN CLONING FUNCTIONS                #
#                                                                              #
# Ordnung muss sein!                             Copyleft (Ɔ) Eugene Zamlinsky #
################################################################################
*/
# pragma	once

//****************************************************************************//
//      Reference implementation of the function                              //
//****************************************************************************//
template <typename T>
void Clone (T source[], size_t size, size_t psize) {
	if (size > psize) {
		size -= psize;
		T *target = source + psize;
		for (size_t i = 0; i < size; ++i)
			target[i] = source[i];
	}
}

//****************************************************************************//
//      Unit test routine                                                     //
//****************************************************************************//
void TestClone (void) {

	// Show the stage info
	StageInfo ("Array::Clone", BUFFER_SIZE, ROUNDS, TRIES);

	// Unsigned integer types
	TestClone <uint8_t> (Array::Clone, Clone);
	TestClone <uint16_t> (Array::Clone, Clone);
	TestClone <uint32_t> (Array::Clone, Clone);
	TestClone <uint64_t> (Array::Clone, Clone);

	// Signed integer types
	TestClone <sint8_t> (Array::Clone, Clone);
	TestClone <sint16_t> (Array::Clone, Clone);
	TestClone <sint32_t> (Array::Clone, Clone);
	TestClone <sint64_t> (Array::Clone, Clone);

	// Floating-point types
	TestClone <flt32_t> (Array::Clone, Clone);
	TestClone <flt64_t> (Array::Clone, Clone);

	// Other types
	TestClone <size_t> (Array::Clone, Clone);
}
/*
################################################################################
#                                 END OF FILE                                  #
################################################################################
*/
