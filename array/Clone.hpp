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
//      Test the clone function                                               //
//****************************************************************************//
template <typename T>
void TestClone (
	void (*func)(T array[], size_t size, size_t psize),
	void (*ref)(T array[], size_t size, size_t psize)
){
	// Create an array of the target size
	RandomArray <T> array (BUFFER_SIZE, SEED, MAX_VALUE);

	// Run the test in many rounds with a random offset and element count
	for (size_t i = 0; i < ROUNDS; i++) {

		// Get a random offset inside the array and a random number of elements
		// to work with
		size_t psize = array.Offset ();
		size_t count = array.Count (psize);

		// Do many tries with the same offset and element count, but different data
		for (size_t j = 0; j < TRIES; j++) {

			// Populate the array with random data
			array.Populate ();

			// Make a copy for the reference implementation of the function
			RandomArray <T> reference (array);

			// Apply the operation to the array data. Both the testing and the reference
			func (array.Data(), count, psize);
			ref (reference.Data(), count, psize);

			// Compare arrays for different elements
			array.Compare (reference, EPSILON);
		}
	}
}

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
