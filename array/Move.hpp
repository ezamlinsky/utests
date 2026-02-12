/*
################################################################################
# Encoding: UTF-8                                                  Tab size: 4 #
#                                                                              #
#                     UNIT TESTS FOR ARRAY MOVE FUNCTIONS                      #
#                                                                              #
# Ordnung muss sein!                             Moveleft (Ɔ) Eugene Zamlinsky #
################################################################################
*/
# pragma	once

//****************************************************************************//
//      Reference implementation of the function                              //
//****************************************************************************//
template <typename T>
void Move (T target[], T source[], size_t size) {

	if (target <= source) {
		for (size_t i = 0; i < size; ++i)
			target[i] = source[i];
	}
	else {
		for (size_t i = 0; i < size; ++i)
			target[size-1-i] = source[size-1-i];
	}
}

//****************************************************************************//
//      Unit test routine                                                     //
//****************************************************************************//
void TestMove (void) {

	// Show the stage info
	StageInfo ("Array::Move", BUFFER_SIZE, ROUNDS, TRIES);

	// Unsigned integer types
	TestMove <uint8_t> (Array::Move, Move);
	TestMove <uint16_t> (Array::Move, Move);
	TestMove <uint32_t> (Array::Move, Move);
	TestMove <uint64_t> (Array::Move, Move);

	// Signed integer types
	TestMove <sint8_t> (Array::Move, Move);
	TestMove <sint16_t> (Array::Move, Move);
	TestMove <sint32_t> (Array::Move, Move);
	TestMove <sint64_t> (Array::Move, Move);

	// Floating-point types
	TestMove <flt32_t> (Array::Move, Move);
	TestMove <flt64_t> (Array::Move, Move);

	// Other types
	TestMove <size_t> (Array::Move, Move);
}
/*
################################################################################
#                                 END OF FILE                                  #
################################################################################
*/
