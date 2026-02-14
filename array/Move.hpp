/*
################################################################################
# Encoding: UTF-8                                                  Tab size: 4 #
#                                                                              #
#                     UNIT TESTS FOR ARRAY MOVE FUNCTIONS                      #
#                                                                              #
# Ordnung muss sein!                             Copyleft (Ɔ) Eugene Zamlinsky #
################################################################################
*/
# pragma	once

//****************************************************************************//
//      Test the move function                                                //
//****************************************************************************//
template <typename T>
void TestMove (
	void (*func)(T target[], T source[], size_t size),
	void (*ref)(T target[], T source[], size_t size)
){
	// Create an array of the target size
	RandomArray <T> array (BUFFER_SIZE, SEED, MAX_VALUE);

	// Run the test in many rounds with a random offset and element count
	for (size_t i = 0; i < ROUNDS; i++) {

		// Get a random offset inside the arrays and a random number of elements
		// to work with
		size_t toffset = array.Offset ();
		size_t soffset = array.Offset ();
		size_t tcount = array.Count (toffset);
		size_t scount = array.Count (soffset);
		size_t count = min (tcount, scount);

		// Do many tries with the same offset and element count, but different data
		for (size_t j = 0; j < TRIES; j++) {

			// Populate the array with random data
			array.Populate ();

			// Make a copy for the reference implementation of the function
			RandomArray <T> reference (array);

			// Apply the operation to the array data. Both the testing and the reference
			func (array.Data() + toffset, array.Data() + soffset, count);
			ref (reference.Data() + toffset, reference.Data() + soffset, count);

			// Compare arrays for different elements
			array.Compare (reference, EPSILON);
		}
	}
}

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
