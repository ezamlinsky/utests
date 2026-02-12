/*
################################################################################
# Encoding: UTF-8                                                  Tab size: 4 #
#                                                                              #
#               UNIT TESTS FOR ARRAY DUPLICATE VALUES EXTRACTORS               #
#                                                                              #
# Ordnung muss sein!                             Moveleft (Ɔ) Eugene Zamlinsky #
################################################################################
*/
# pragma	once

//****************************************************************************//
//      Test function for regular operations                                  //
//****************************************************************************//
template <typename T>
void TestDuplicates (
	size_t (*func)(T unique[], size_t count[], const T array[], size_t size),
	size_t (*ref)(T unique[], size_t count[], const T array[], size_t size)
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

			// Create arrays for counters
			RandomArray <size_t> func_counter (BUFFER_SIZE, SEED, MAX_VALUE);
			RandomArray <size_t> ref_counter (BUFFER_SIZE, SEED, MAX_VALUE);

			// Apply the operation to the array data. Both the testing and the reference
			size_t computed_value = func (func_output.Data(), func_counter.Data(), array.Data() + offset, count);
			size_t correct_value = ref (ref_output.Data(), ref_counter.Data(), array.Data() + offset, count);

			// Compare the result values
			array.CheckResult (computed_value, correct_value, EPSILON);

			// Compare arrays for different elements
			func_output.Compare (ref_output, EPSILON, correct_value);
			func_counter.Compare (ref_counter, EPSILON, correct_value);
		}
	}
}

//****************************************************************************//
//      Test function for object array operations                             //
//****************************************************************************//
void TestDuplicatesObj (
	size_t (*func)(const void* unique[], size_t count[], const void* array[], size_t size, Cmp func),
	size_t (*ref)(sint64_t unique[], size_t count[], const sint64_t array[], size_t size)
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

			// Create arrays for counters
			RandomArray <size_t> func_counter (BUFFER_SIZE, SEED, MAX_VALUE);
			RandomArray <size_t> ref_counter (BUFFER_SIZE, SEED, MAX_VALUE);

			// Apply the operation to the array data. Both the testing and the reference
			size_t computed_value = func (reinterpret_cast <const void**> (func_output.Data()), func_counter.Data(), reinterpret_cast <const void**> (array.Data() + offset), count, KeyCmp);
			size_t correct_value = ref (ref_output.Data(), ref_counter.Data(), array.Data() + offset, count);

			// Compare the result values
			array.CheckResult (computed_value, correct_value, EPSILON);

			// Compare arrays for different elements
			func_output.Compare (ref_output, EPSILON, correct_value);
			func_counter.Compare (ref_counter, EPSILON, correct_value);
		}
	}
}

//****************************************************************************//
//      Reference implementation of the functions                             //
//****************************************************************************//
template <typename T>
size_t Duplicates (T unique[], size_t count[], const T array[], size_t size){
	if (size) {
		T value = array[0];
		size_t total = 1;
		size_t usize = 0;
		for (size_t i = 1; i < size; i++) {
			if (array[i] != value) {
				unique[0] = value;
				unique++;
				count[0] = total;
				count++;
				value = array[i];
				total = 1;
				usize++;
			}
			else
				total++;
		}
		unique[0] = value;
		count[0] = total;
		usize++;
		return usize;
	}
	else
		return 0;
}

//****************************************************************************//
//      Unit test routines                                                    //
//****************************************************************************//

//============================================================================//
//      Duplicates elements                                                   //
//============================================================================//
void TestDuplicates (void) {

	// Show the stage info
	StageInfo ("Array::Duplicates", BUFFER_SIZE, ROUNDS, TRIES);

	// Unsigned integer types
	TestDuplicates <uint8_t> (Array::Duplicates, Duplicates);
	TestDuplicates <uint16_t> (Array::Duplicates, Duplicates);
	TestDuplicates <uint32_t> (Array::Duplicates, Duplicates);
	TestDuplicates <uint64_t> (Array::Duplicates, Duplicates);

	// Signed integer types
	TestDuplicates <sint8_t> (Array::Duplicates, Duplicates);
	TestDuplicates <sint16_t> (Array::Duplicates, Duplicates);
	TestDuplicates <sint32_t> (Array::Duplicates, Duplicates);
	TestDuplicates <sint64_t> (Array::Duplicates, Duplicates);

	// Other types
	TestDuplicates <size_t> (Array::Duplicates, Duplicates);
}

//============================================================================//
//      Duplicates objects                                                    //
//============================================================================//
void TestDuplicatesObj (void) {

	// Show the stage info
	StageInfo ("Array::DuplicatesObj", BUFFER_SIZE, ROUNDS, TRIES);

	// Object array
	TestDuplicatesObj (Array::DuplicatesObj, Duplicates);
}

/*
################################################################################
#                                 END OF FILE                                  #
################################################################################
*/
