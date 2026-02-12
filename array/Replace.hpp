/*
################################################################################
# Encoding: UTF-8                                                  Tab size: 4 #
#                                                                              #
#                  UNIT TESTS FOR REPLACING OF ARRAY ELEMENTS                  #
#                                                                              #
# Ordnung muss sein!                             Copyleft (Ɔ) Eugene Zamlinsky #
################################################################################
*/
# pragma	once

//****************************************************************************//
//      Test the replace function                                             //
//****************************************************************************//
template <typename T>
void TestReplace (
	void (*func)(T target[], size_t size, T value1, T value2),
	void (*ref)(T target[], size_t size, T value1, T value2)
){
	// Create an array the target size
	RandomArray <T> array (BUFFER_SIZE, SEED, MAX_VALUE);

	// Run the test in many rounds with a random offset and element count
	for (size_t i = 0; i < ROUNDS; i++) {

		// Get a random offset inside the array and a random number of elements
		// to work with
		size_t offset = array.Offset ();
		size_t count = array.Count (offset);

		// Create random scalar values for the test
		T value1 = array.RandomValue();
		T value2 = array.RandomValue();

		// Do many tries with the same offset and element count, but different data
		for (size_t j = 0; j < TRIES; j++) {

			// Populate the array with random data
			array.Populate ();

			// Make a copy for the reference implementation of the function
			RandomArray <T> reference (array);

			// Apply the operation to the array data. Both the testing and the reference
			func (array.Data() + offset, count, value1, value2);
			ref (reference.Data() + offset, count, value1, value2);

			// Compare arrays for different elements
			array.Compare (reference, EPSILON);
		}
	}
}

//****************************************************************************//
//      Test function for object array replace function                       //
//****************************************************************************//
void TestReplaceObj (
	void (*func)(const void* array[], size_t size, const void *pattern, const void *value, Cmp func),
	void (*ref)(sint64_t array[], size_t size, sint64_t value1, sint64_t value2)
){
	// Create an array of the target size
	RandomArray <sint64_t> array (BUFFER_SIZE, SEED, MAX_VALUE);

	// Run the test in many rounds with a random offset and element count
	for (size_t i = 0; i < ROUNDS; i++) {

		// Get a random offset inside the array and a random number of elements
		// to work with
		size_t offset = array.Offset ();
		size_t count = array.Count (offset);

		// Create random scalar values for the test
		sint64_t value1 = array.RandomValue();
		sint64_t value2 = array.RandomValue();

		// Do many tries with the same offset and element count, but different data
		for (size_t j = 0; j < TRIES; j++) {

			// Populate the array with random data
			array.Populate ();

			// Make a copy for the reference implementation of the function
			RandomArray <sint64_t> reference (array);

			// Apply the operation to the array data. Both the testing and the reference
			func (reinterpret_cast <const void**> (array.Data() + offset), count, reinterpret_cast <const void*> (value1), reinterpret_cast <const void*> (value2), KeyCmp);
			ref (reference.Data() + offset, count, value1, value2);

			// Compare arrays for different elements
			array.Compare (reference, EPSILON);
		}
	}
}

//****************************************************************************//
//      Reference implementation of the function                              //
//****************************************************************************//
template <typename T>
void Replace (T array[], size_t size, T pattern, T value){
	for (size_t i = 0; i < size; i++)
		if (array[i] == pattern)
			array[i] = value;
}

//****************************************************************************//
//      Unit test routine                                                     //
//****************************************************************************//

//============================================================================//
//      Element replacing                                                     //
//============================================================================//
void TestReplace (void) {

	// Show the stage info
	StageInfo ("Array::Replace", BUFFER_SIZE, ROUNDS, TRIES);

	// Unsigned integer types
	TestReplace <uint8_t> (Array::Replace, Replace);
	TestReplace <uint16_t> (Array::Replace, Replace);
	TestReplace <uint32_t> (Array::Replace, Replace);
	TestReplace <uint64_t> (Array::Replace, Replace);

	// Signed integer types
	TestReplace <sint8_t> (Array::Replace, Replace);
	TestReplace <sint16_t> (Array::Replace, Replace);
	TestReplace <sint32_t> (Array::Replace, Replace);
	TestReplace <sint64_t> (Array::Replace, Replace);

	// Other types
	TestReplace <size_t> (Array::Replace, Replace);
}

//============================================================================//
//      Object replacing                                                      //
//============================================================================//
void TestReplaceObj (void) {

	// Show the stage info
	StageInfo ("Array::ReplaceObj", BUFFER_SIZE, ROUNDS, TRIES);

	// Object array
	TestReplaceObj (Array::ReplaceObj, Replace);
}
/*
################################################################################
#                                 END OF FILE                                  #
################################################################################
*/
