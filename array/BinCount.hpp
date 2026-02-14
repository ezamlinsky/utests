/*
################################################################################
# Encoding: UTF-8                                                  Tab size: 4 #
#                                                                              #
#                UNIT TESTS FOR ARRAY BINARY COUNTING FUNCTIONS                #
#                                                                              #
# Ordnung muss sein!                             Copyleft (Ɔ) Eugene Zamlinsky #
################################################################################
*/
# pragma	once

//****************************************************************************//
//      Test function for regular array linear search operations              //
//****************************************************************************//
template <typename R, typename T>
void TestBinCount (
	R (*func)(const T target[], size_t size, T value),
	R (*ref)(const T target[], size_t size, T value),
	bool reverse_order
){
	// Create an array of the target size
	RandomArray <T> array (BUFFER_SIZE, SEED, MAX_VALUE);

	// Run the test in many rounds with a random offset and element count
	for (size_t i = 0; i < ROUNDS; i++) {

		// Get a random offset inside the array and a random number of elements
		// to work with
		size_t offset = array.Offset ();
		size_t count = array.Count (offset);

		// Create a random scalar value for the test
		T value = array.RandomValue();

		// Do many tries with the same offset and element count, but different data
		for (size_t j = 0; j < TRIES; j++) {

			// Populate the array with random data
			array.Populate ();

			// Sort the array in the target order
			array.Sort (reverse_order);

			// Make a copy for the reference implementation of the function
			RandomArray <T> reference (array);

			// Apply the operation to the array data. Both the testing and the reference
			R computed_value = func (array.Data() + offset, count, value);
			R correct_value = ref (reference.Data() + offset, count, value);

			// Compare the result values
			array.CheckResult (computed_value, correct_value, EPSILON);
		}
	}
}

//****************************************************************************//
//      Test function for object array linear search operations               //
//****************************************************************************//
void TestBinObjCount (
	size_t (*func)(const void* array[], size_t size, const void *value, Cmp func),
	size_t (*ref)(const sint64_t target[], size_t size, sint64_t value),
	bool reverse_order
){
	// Create an array of the target size
	RandomArray <sint64_t> array (BUFFER_SIZE, SEED, MAX_VALUE);

	// Run the test in many rounds with a random offset and element count
	for (size_t i = 0; i < ROUNDS; i++) {

		// Get a random offset inside the array and a random number of elements
		// to work with
		size_t offset = array.Offset ();
		size_t count = array.Count (offset);

		// Create a random scalar value for the test
		sint64_t value = array.RandomValue();

		// Do many tries with the same offset and element count, but different data
		for (size_t j = 0; j < TRIES; j++) {

			// Populate the array with random data
			array.Populate ();

			// Sort the array in the target order
			array.Sort (reverse_order);

			// Make a copy for the reference implementation of the function
			RandomArray <sint64_t> reference (array);

			// Apply the operation to the array data. Both the testing and the reference
			size_t computed_value = func (reinterpret_cast <const void**> (array.Data() + offset), count, reinterpret_cast <const void*> (value), KeyCmp);
			size_t correct_value = ref (reference.Data() + offset, count, value);

			// Compare the result values
			array.CheckResult (computed_value, correct_value, EPSILON);
		}
	}
}

//****************************************************************************//
//      Unit test routines                                                    //
//****************************************************************************//

//============================================================================//
//      Element counting                                                      //
//============================================================================//

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//      Ascending sort order                                                  //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void TestCountAsc (void) {

	// Show the stage info
	StageInfo ("Array::CountAsc", BUFFER_SIZE, ROUNDS, TRIES);

	// Unsigned integer types
	TestBinCount <size_t, uint8_t> (Array::CountAsc, Count, false);
	TestBinCount <size_t, uint16_t> (Array::CountAsc, Count, false);
	TestBinCount <size_t, uint32_t> (Array::CountAsc, Count, false);
	TestBinCount <size_t, uint64_t> (Array::CountAsc, Count, false);

	// Signed integer types
	TestBinCount <size_t, sint8_t> (Array::CountAsc, Count, false);
	TestBinCount <size_t, sint16_t> (Array::CountAsc, Count, false);
	TestBinCount <size_t, sint32_t> (Array::CountAsc, Count, false);
	TestBinCount <size_t, sint64_t> (Array::CountAsc, Count, false);

	// Other types
	TestBinCount <size_t, size_t> (Array::CountAsc, Count, false);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//      Descending sort order                                                 //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void TestCountDsc (void) {

	// Show the stage info
	StageInfo ("Array::CountDsc", BUFFER_SIZE, ROUNDS, TRIES);

	// Unsigned integer types
	TestBinCount <size_t, uint8_t> (Array::CountDsc, Count, true);
	TestBinCount <size_t, uint16_t> (Array::CountDsc, Count, true);
	TestBinCount <size_t, uint32_t> (Array::CountDsc, Count, true);
	TestBinCount <size_t, uint64_t> (Array::CountDsc, Count, true);

	// Signed integer types
	TestBinCount <size_t, sint8_t> (Array::CountDsc, Count, true);
	TestBinCount <size_t, sint16_t> (Array::CountDsc, Count, true);
	TestBinCount <size_t, sint32_t> (Array::CountDsc, Count, true);
	TestBinCount <size_t, sint64_t> (Array::CountDsc, Count, true);

	// Other types
	TestBinCount <size_t, size_t> (Array::CountDsc, Count, true);
}

//============================================================================//
//      Object counting                                                       //
//============================================================================//

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//      Ascending sort order                                                  //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void TestCountObjAsc (void) {

	// Show the stage info
	StageInfo ("Array::CountObjAsc", BUFFER_SIZE, ROUNDS, TRIES);

	// Object array
	TestBinObjCount (Array::CountObjAsc, Count, false);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//      Descending sort order                                                 //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void TestCountObjDsc (void) {

	// Show the stage info
	StageInfo ("Array::CountObjDsc", BUFFER_SIZE, ROUNDS, TRIES);

	// Object array
	TestBinObjCount (Array::CountObjDsc, Count, true);
}

/*
################################################################################
#                                 END OF FILE                                  #
################################################################################
*/
