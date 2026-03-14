/*
################################################################################
# Encoding: UTF-8                                                  Tab size: 4 #
#                                                                              #
#                     UNIT TESTS FOR ARRAY HASH FUNCTIONS                      #
#                                                                              #
# Ordnung muss sein!                             Copyleft (Ɔ) Eugene Zamlinsky #
################################################################################
*/
# pragma	once

//****************************************************************************//
//      Test a hash function                                                  //
//****************************************************************************//
template <typename R, typename T>
void TestHash (
	R (*func)(const T target[], size_t size)
){
	R default_value = func (nullptr, 0);
	R prev_value = 0;

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

			// Apply the operation to the array data
			R computed_value = func (array.Data() + offset, count);

			// Check if array is empty
			if (!count) {

				// Compare if empty array always have the same hash value
				if (computed_value != default_value) {
					throw runtime_error ("    Mismatch hash value: Got '" +
					to_string (computed_value) + "' Expected '" +
					to_string (default_value) + "'");
				}
			} else {

				// Compare the previous and current value if they match
				if (prev_value == computed_value) {
					throw runtime_error ("    Found a collision for " +
					to_string (count) + " long array");
				}

				// Update the previous value
				prev_value = computed_value;
			}
		}
	}
}

//****************************************************************************//
//      Unit test routines                                                    //
//****************************************************************************//

//============================================================================//
//      32-bit hash functions                                                 //
//============================================================================//
void TestHash32 (void) {

	// Show the stage info
	StageInfo ("Array::Hash32", BUFFER_SIZE, ROUNDS, TRIES);

	// Unsigned integer types
	TestHash <uint32_t, uint8_t> (Array::Hash32);
	TestHash <uint32_t, uint16_t> (Array::Hash32);
	TestHash <uint32_t, uint32_t> (Array::Hash32);
	TestHash <uint32_t, uint64_t> (Array::Hash32);

	// Unsigned integer types
	TestHash <uint32_t, sint8_t> (Array::Hash32);
	TestHash <uint32_t, sint16_t> (Array::Hash32);
	TestHash <uint32_t, sint32_t> (Array::Hash32);
	TestHash <uint32_t, sint64_t> (Array::Hash32);

	// Floating-point types
	TestHash <uint32_t, flt32_t> (Array::Hash32);
	TestHash <uint32_t, flt64_t> (Array::Hash32);

	// Other types
	TestHash <uint32_t, size_t> (Array::Hash32);
}

//============================================================================//
//      64-bit hash functions                                                 //
//============================================================================//
void TestHash64 (void) {

	// Show the stage info
	StageInfo ("Array::Hash64", BUFFER_SIZE, ROUNDS, TRIES);

	// Unsigned integer types
	TestHash <uint64_t, uint8_t> (Array::Hash64);
	TestHash <uint64_t, uint16_t> (Array::Hash64);
	TestHash <uint64_t, uint32_t> (Array::Hash64);
	TestHash <uint64_t, uint64_t> (Array::Hash64);

	// Unsigned integer types
	TestHash <uint64_t, sint8_t> (Array::Hash64);
	TestHash <uint64_t, sint16_t> (Array::Hash64);
	TestHash <uint64_t, sint32_t> (Array::Hash64);
	TestHash <uint64_t, sint64_t> (Array::Hash64);

	// Floating-point types
	TestHash <uint64_t, flt32_t> (Array::Hash64);
	TestHash <uint64_t, flt64_t> (Array::Hash64);

	// Other types
	TestHash <uint64_t, size_t> (Array::Hash64);
}

/*
################################################################################
#                                 END OF FILE                                  #
################################################################################
*/
