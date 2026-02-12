/*
################################################################################
# Encoding: UTF-8                                                  Tab size: 4 #
#                                                                              #
#                UNIT TESTS FOR ARRAY INITIALIZATION FUNCTIONS                 #
#                                                                              #
# Ordnung muss sein!                             Copyleft (Ɔ) Eugene Zamlinsky #
################################################################################
*/
# pragma	once

//****************************************************************************//
//      Reference implementation of the function                              //
//****************************************************************************//
template <typename T>
void Init (T array[], size_t size, T value) {
	for (size_t i = 0; i < size; ++i)
		array[i] = value;
}

//****************************************************************************//
//      Unit test routine                                                     //
//****************************************************************************//
void TestInit (void) {

	// Show the stage info
	StageInfo ("Array::Init", BUFFER_SIZE, ROUNDS, TRIES);

	// Unsigned integer types
	TestScalar <uint8_t> (Array::Init, Init);
	TestScalar <uint16_t> (Array::Init, Init);
	TestScalar <uint32_t> (Array::Init, Init);
	TestScalar <uint64_t> (Array::Init, Init);

	// Signed integer types
	TestScalar <sint8_t> (Array::Init, Init);
	TestScalar <sint16_t> (Array::Init, Init);
	TestScalar <sint32_t> (Array::Init, Init);
	TestScalar <sint64_t> (Array::Init, Init);

	// Floating-point types
	TestScalar <flt32_t> (Array::Init, Init);
	TestScalar <flt64_t> (Array::Init, Init);

	// Other types
	TestScalar <size_t> (Array::Init, Init);
}
/*
################################################################################
#                                 END OF FILE                                  #
################################################################################
*/
