/*
################################################################################
# Encoding: UTF-8                                                  Tab size: 4 #
#                                                                              #
#                UNIT TESTS FOR ARRAY UNIQUE VALUES EXTRACTORS                 #
#                                                                              #
# Ordnung muss sein!                             Moveleft (Ɔ) Eugene Zamlinsky #
################################################################################
*/
# pragma	once

//****************************************************************************//
//      Test function for regular operations                                  //
//****************************************************************************//
template <typename T>
void TestUnique (
	size_t (*func)(T unique[], const T array[], size_t size),
	size_t (*ref)(T unique[], const T array[], size_t size)
){
	// Create an array of the target size
	RandomArray <T> array (BUFFER_SIZE, SEED, MAX_VALUE);

	// Run the test in many rounds with a random offset and element count
	for (size_t i = 0; i < ROUNDS; i++) {

		// Get a random offset inside the array and a random number of elements
		// to work with
		size_t offset = array.Offset ();
		size_t count = array.Count (offset);

		// Do many tries with the same offset and element count, but different data
		for (size_t j = 0; j < TRIES; j++) {

			// Populate the array with random data
			array.Populate ();

			// Sort the array in the target order
			array.Sort (false);

			// Create arrays for unique values
			RandomArray <T> func_output (BUFFER_SIZE, SEED, MAX_VALUE);
			RandomArray <T> ref_output (BUFFER_SIZE, SEED, MAX_VALUE);

			// Apply the operation to the array data. Both the testing and the reference
			size_t computed_value = func (func_output.Data(), array.Data() + offset, count);
			size_t correct_value = ref (ref_output.Data(), array.Data() + offset, count);

			// Compare the result values
			array.CheckResult (computed_value, correct_value, EPSILON);

			// Compare arrays for different elements
			func_output.Compare (ref_output, EPSILON, correct_value);
		}
	}
}

//****************************************************************************//
//      Test function for object array operations                             //
//****************************************************************************//
void TestUniqueObj (
	size_t (*func)(const void* unique[], const void* array[], size_t size, Cmp func),
	size_t (*ref)(sint64_t unique[], const sint64_t array[], size_t size)
){
	// Create an array of the target size
	RandomArray <sint64_t> array (BUFFER_SIZE, SEED, MAX_VALUE);

	// Run the test in many rounds with a random offset and element count
	for (size_t i = 0; i < ROUNDS; i++) {

		// Get a random offset inside the array and a random number of elements
		// to work with
		size_t offset = array.Offset ();
		size_t count = array.Count (offset);

		// Do many tries with the same offset and element count, but different data
		for (size_t j = 0; j < TRIES; j++) {

			// Populate the array with random data
			array.Populate ();

			// Sort the array in the target order
			array.Sort (false);

			// Create arrays for unique values
			RandomArray <sint64_t> func_output (BUFFER_SIZE, SEED, MAX_VALUE);
			RandomArray <sint64_t> ref_output (BUFFER_SIZE, SEED, MAX_VALUE);

			// Apply the operation to the array data. Both the testing and the reference
			size_t computed_value = func (reinterpret_cast <const void**> (func_output.Data()), reinterpret_cast <const void**> (array.Data() + offset), count, KeyCmp);
			size_t correct_value = ref (ref_output.Data(), array.Data() + offset, count);

			// Compare the result values
			array.CheckResult (computed_value, correct_value, EPSILON);

			// Compare arrays for different elements
			func_output.Compare (ref_output, EPSILON, correct_value);
		}
	}
}

//****************************************************************************//
//      Reference implementation of the functions                             //
//****************************************************************************//
template <typename T>
size_t Unique (T unique[], const T array[], size_t size){
    copy (array, array + size, unique);
	sort (unique, unique + size);
	return std::unique (unique, unique + size) - unique;
}

//****************************************************************************//
//      Unit test routines                                                    //
//****************************************************************************//

//============================================================================//
//      Unique elements                                                       //
//============================================================================//
void TestUnique (void) {

	// Show the stage info
	StageInfo ("Array::Unique", BUFFER_SIZE, ROUNDS, TRIES);

	// Unsigned integer types
	TestUnique <uint8_t> (Array::Unique, Unique);
	TestUnique <uint16_t> (Array::Unique, Unique);
	TestUnique <uint32_t> (Array::Unique, Unique);
	TestUnique <uint64_t> (Array::Unique, Unique);

	// Signed integer types
	TestUnique <sint8_t> (Array::Unique, Unique);
	TestUnique <sint16_t> (Array::Unique, Unique);
	TestUnique <sint32_t> (Array::Unique, Unique);
	TestUnique <sint64_t> (Array::Unique, Unique);

	// Other types
	TestUnique <size_t> (Array::Unique, Unique);
}

//============================================================================//
//      Unique objects                                                        //
//============================================================================//
void TestUniqueObj (void) {

	// Show the stage info
	StageInfo ("Array::UniqueObj", BUFFER_SIZE, ROUNDS, TRIES);

	// Object array
	TestUniqueObj (Array::UniqueObj, Unique);
}

/*
################################################################################
#                                 END OF FILE                                  #
################################################################################
*/
