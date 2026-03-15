/*
################################################################################
# Encoding: UTF-8                                                  Tab size: 4 #
#                                                                              #
#                    UNIT TESTS FOR ARRAY COMPARE FUNCTIONS                    #
#                                                                              #
# Ordnung muss sein!                             Copyleft (Ɔ) Eugene Zamlinsky #
################################################################################
*/
# pragma	once

//****************************************************************************//
//      Test function for operations with regular arrays                      //
//****************************************************************************//
template <typename R, typename T>
void TestCompare (
	R (*func)(const T array1[], const T array2[], size_t size),
	R (*ref)(const T array1[], const T array2[], size_t size)
){
	// Create an array of the target size
	RandomArray <T> array1 (BUFFER_SIZE, SEED, MAX_VALUE);
	RandomArray <T> array2 (BUFFER_SIZE, SEED, MAX_VALUE);

	// Run the test in many rounds with a random offset and element count
	for (size_t i = 0; i < ROUNDS; i++) {

		// Get a random offset inside the array and a random number of elements
		// to work with
		size_t offset1 = array1.Offset ();
		size_t offset2 = array1.Offset ();
		size_t count1 = array1.Count (offset1);
		size_t count2 = array1.Count (offset2);
		size_t count = min (count1, count2);

		// Do many tries with the same offset and element count, but different data
		for (size_t j = 0; j < TRIES; j++) {

			// Populate the arrays with random data
			array1.Populate ();
			array2.Populate ();

			// Apply the operation to the array data. Both the testing and the reference
			R computed_value = func (array1.Data() + offset1, array2.Data() + offset2, count);
			R correct_value = ref (array1.Data() + offset1, array2.Data() + offset2, count);

			// Compare the result values
			array1.CheckResult (computed_value, correct_value, EPSILON);
		}
	}
}

//****************************************************************************//
//      Test function for operations with object arrays                       //
//****************************************************************************//
void TestCompareObj (
	sint64_t (*func)(const void* array1[], const void* array2[], size_t size, Cmp func),
	sint64_t (*ref)(const sint64_t array1[], const sint64_t array2[], size_t size)
){
	// Create an array of the target size
	RandomArray <sint64_t> array1 (BUFFER_SIZE, SEED, MAX_VALUE);
	RandomArray <sint64_t> array2 (BUFFER_SIZE, SEED, MAX_VALUE);

	// Run the test in many rounds with a random offset and element count
	for (size_t i = 0; i < ROUNDS; i++) {

		// Get a random offset inside the array and a random number of elements
		// to work with
		size_t offset1 = array1.Offset ();
		size_t offset2 = array1.Offset ();
		size_t count1 = array1.Count (offset1);
		size_t count2 = array1.Count (offset2);
		size_t count = min (count1, count2);

		// Do many tries with the same offset and element count, but different data
		for (size_t j = 0; j < TRIES; j++) {

			// Populate the arrays with random data
			array1.Populate ();
			array2.Populate ();

			// Apply the operation to the array data. Both the testing and the reference
			sint64_t computed_value = func (reinterpret_cast <const void**> (array1.Data() + offset1), reinterpret_cast <const void**> (array2.Data() + offset2), count, KeyCmp);
			sint64_t correct_value = ref (array1.Data() + offset1, array2.Data() + offset2, count);

			// Compare the result values
			array1.CheckResult (computed_value, correct_value, EPSILON);
		}
	}
}

//****************************************************************************//
//      Reference implementation of the functions                             //
//****************************************************************************//
template <typename R, typename T>
R Compare (const T array1[], const T array2[], size_t size){
	for (size_t i = 0; i < size; i++)
		if (array1[i] != array2[i])
			return (array1[i] > array2[i]) - (array1[i] < array2[i]);
	return static_cast <R> (0);
}

//****************************************************************************//
//      Unit test routines                                                    //
//****************************************************************************//

//============================================================================//
//      Comparison of arrays                                                 //
//============================================================================//

// Regular array check
void TestCompare (void) {

	// Show the stage info
	StageInfo ("Array::Compare", BUFFER_SIZE, ROUNDS, TRIES);

	// Unsigned integer types
	TestCompare <sint64_t, uint8_t> (Array::Compare, Compare);
	TestCompare <sint64_t, uint16_t> (Array::Compare, Compare);
	TestCompare <sint64_t, uint32_t> (Array::Compare, Compare);
	TestCompare <sint64_t, uint64_t> (Array::Compare, Compare);

	// Signed integer types
	TestCompare <sint64_t, sint8_t> (Array::Compare, Compare);
	TestCompare <sint64_t, sint16_t> (Array::Compare, Compare);
	TestCompare <sint64_t, sint32_t> (Array::Compare, Compare);
	TestCompare <sint64_t, sint64_t> (Array::Compare, Compare);

	// Floating-point type
	TestCompare <sint64_t, flt32_t> (Array::Compare, Compare);
	TestCompare <sint64_t, flt64_t> (Array::Compare, Compare);

	// Other types
	TestCompare <sint64_t, size_t> (Array::Compare, Compare);
}

//============================================================================//
//      Object array comparison                                               //
//============================================================================//
void TestCompareObj (void) {

	// Show the stage info
	StageInfo ("Array::CompareObj", BUFFER_SIZE, ROUNDS, TRIES);

	// Object array check
	TestCompareObj (Array::CompareObj, Compare);
}

/*
################################################################################
#                                 END OF FILE                                  #
################################################################################
*/
