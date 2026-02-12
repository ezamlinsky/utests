/*
################################################################################
# Encoding: UTF-8                                                  Tab size: 4 #
#                                                                              #
#                  UNIT TESTS FOR BIT FIELD SEARCH OPERATIONS                  #
#                                                                              #
# Ordnung muss sein!                             Moveleft (Ɔ) Eugene Zamlinsky #
################################################################################
*/
# pragma	once

//****************************************************************************//
//      Test function for find bit operations                                 //
//****************************************************************************//
template <typename R, typename T>
void TestFindBit (
	R (*func)(const T target[], size_t spos, size_t epos),
	R (*ref)(const T target[], size_t spos, size_t epos)
){
	// Create an array of target size
	RandomArray <T> array (BUFFER_SIZE, SEED, MAX_VALUE);

	// Run the test in many rounds with random offset and element count
	for (size_t i = 0; i < ROUNDS; i++) {

		// Get a random offset inside the array and a random number of elements
		// to work with
		size_t offset = array.Offset ();
		size_t spos = array.Count (offset);
		size_t epos = array.Count (offset);

		// Do many tries with the same offset and element count, but different data
		for (size_t j = 0; j < TRIES; j++) {

			// Populate the array with random data
			array.Populate ();

			// Make a copy for the reference implementation of the function
			RandomArray <T> reference (array);

			// Apply the operation to the array data. Both the testing and the reference
			R computed_value = func (array.Data() + offset, spos, epos);
			R correct_value = ref (reference.Data() + offset, spos, epos);

			// Compare the result values
			array.CheckResult (computed_value, correct_value, EPSILON);
		}
	}
}

//****************************************************************************//
//      Reference implementation of the functions                             //
//****************************************************************************//

//============================================================================//
//      Forward direction search                                              //
//============================================================================//

// Searching for a set bit
template <typename T>
size_t FindSetBitFwd (const T array[], size_t spos, size_t epos) {
	for (size_t i = spos; i < epos; ++i) {
		const size_t pos = i;
		const size_t index = pos / (sizeof (T) * 8);
		const int bit = pos % (sizeof (T) * 8);
		if (array [index] & (1ULL << bit))
			return pos;
	}
	return static_cast <size_t> (-1);
}

// Searching for a reset bit
template <typename T>
size_t FindResetBitFwd (const T array[], size_t spos, size_t epos) {
	for (size_t i = spos; i < epos; ++i) {
		const size_t pos = i;
		const size_t index = pos / (sizeof (T) * 8);
		const int bit = pos % (sizeof (T) * 8);
		if (~(array [index]) & (1ULL << bit))
			return pos;
	}
	return static_cast <size_t> (-1);
}

//============================================================================//
//      Backward direction search                                             //
//============================================================================//

// Searching for a set bit
template <typename T>
size_t FindSetBitBwd (const T array[], size_t spos, size_t epos) {
	for (size_t i = epos; i > spos; --i) {
		const size_t pos = i - 1;
		const size_t index = pos / (sizeof (T) * 8);
		const int bit = pos % (sizeof (T) * 8);
		if (array [index] & (1ULL << bit))
			return pos;
	}
	return static_cast <size_t> (-1);
}

// Searching for a reset bit
template <typename T>
size_t FindResetBitBwd (const T array[], size_t spos, size_t epos) {
	for (size_t i = epos; i > spos; --i) {
		const size_t pos = i - 1;
		const size_t index = pos / (sizeof (T) * 8);
		const int bit = pos % (sizeof (T) * 8);
		if (~array [index] & (1ULL << bit))
			return pos;
	}
	return static_cast <size_t> (-1);
}

//============================================================================//
//      Bit counting                                                          //
//============================================================================//
template <typename T>
size_t CountBits (const T array[], size_t spos, size_t epos) {
	size_t count = 0;
	for (size_t i = spos; i < epos; ++i) {
		const size_t pos = i;
		const size_t index = pos / (sizeof (T) * 8);
		const int bit = pos % (sizeof (T) * 8);
		if (array [index] & (1ULL << bit))
			count++;
	}
	return count;
}

//============================================================================//
//      Check for a set bit in the bit field range                            //
//============================================================================//
template <typename T>
bool CheckSetBit (const T array[], size_t spos, size_t epos){
	return FindSetBitFwd (array, spos, epos) != static_cast <size_t> (-1);
}

//============================================================================//
//      Check for a reset bit in the bit field range                          //
//============================================================================//
template <typename T>
bool CheckResetBit (const T array[], size_t spos, size_t epos){
	return FindResetBitFwd (array, spos, epos) != static_cast <size_t> (-1);
}

//****************************************************************************//
//      Unit test routines                                                    //
//****************************************************************************//

//============================================================================//
//      Forward direction search                                              //
//============================================================================//

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//      Searching for a set bit                                               //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void TestFindSetBitFwd (void) {

	// Show the stage info
	StageInfo ("BitField::FindSetBitFwd", BUFFER_SIZE, ROUNDS, TRIES);

	// Unsigned integer types
	TestFindBit <size_t, uint8_t> (BitField::FindSetBitFwd, FindSetBitFwd);
	TestFindBit <size_t, uint16_t> (BitField::FindSetBitFwd, FindSetBitFwd);
	TestFindBit <size_t, uint32_t> (BitField::FindSetBitFwd, FindSetBitFwd);
	TestFindBit <size_t, uint64_t> (BitField::FindSetBitFwd, FindSetBitFwd);

	// Signed integer types
	TestFindBit <size_t, sint8_t> (BitField::FindSetBitFwd, FindSetBitFwd);
	TestFindBit <size_t, sint16_t> (BitField::FindSetBitFwd, FindSetBitFwd);
	TestFindBit <size_t, sint32_t> (BitField::FindSetBitFwd, FindSetBitFwd);
	TestFindBit <size_t, sint64_t> (BitField::FindSetBitFwd, FindSetBitFwd);

	// Other types
	TestFindBit <size_t, size_t> (BitField::FindSetBitFwd, FindSetBitFwd);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//      Searching for a reset bit                                             //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void TestFindResetBitFwd (void) {

	// Show the stage info
	StageInfo ("BitField::FindResetBitFwd", BUFFER_SIZE, ROUNDS, TRIES);

	// Unsigned integer types
	TestFindBit <size_t, uint8_t> (BitField::FindResetBitFwd, FindResetBitFwd);
	TestFindBit <size_t, uint16_t> (BitField::FindResetBitFwd, FindResetBitFwd);
	TestFindBit <size_t, uint32_t> (BitField::FindResetBitFwd, FindResetBitFwd);
	TestFindBit <size_t, uint64_t> (BitField::FindResetBitFwd, FindResetBitFwd);

	// Signed integer types
	TestFindBit <size_t, sint8_t> (BitField::FindResetBitFwd, FindResetBitFwd);
	TestFindBit <size_t, sint16_t> (BitField::FindResetBitFwd, FindResetBitFwd);
	TestFindBit <size_t, sint32_t> (BitField::FindResetBitFwd, FindResetBitFwd);
	TestFindBit <size_t, sint64_t> (BitField::FindResetBitFwd, FindResetBitFwd);

	// Other types
	TestFindBit <size_t, size_t> (BitField::FindResetBitFwd, FindResetBitFwd);
}

//============================================================================//
//      Backward direction search                                             //
//============================================================================//

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//      Searching for a set bit                                               //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void TestFindSetBitBwd (void) {

	// Show the stage info
	StageInfo ("BitField::FindSetBitBwd", BUFFER_SIZE, ROUNDS, TRIES);

	// Unsigned integer types
	TestFindBit <size_t, uint8_t> (BitField::FindSetBitBwd, FindSetBitBwd);
	TestFindBit <size_t, uint16_t> (BitField::FindSetBitBwd, FindSetBitBwd);
	TestFindBit <size_t, uint32_t> (BitField::FindSetBitBwd, FindSetBitBwd);
	TestFindBit <size_t, uint64_t> (BitField::FindSetBitBwd, FindSetBitBwd);

	// Signed integer types
	TestFindBit <size_t, sint8_t> (BitField::FindSetBitBwd, FindSetBitBwd);
	TestFindBit <size_t, sint16_t> (BitField::FindSetBitBwd, FindSetBitBwd);
	TestFindBit <size_t, sint32_t> (BitField::FindSetBitBwd, FindSetBitBwd);
	TestFindBit <size_t, sint64_t> (BitField::FindSetBitBwd, FindSetBitBwd);

	// Other types
	TestFindBit <size_t, size_t> (BitField::FindSetBitBwd, FindSetBitBwd);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//      Searching for a reset bit                                             //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void TestFindResetBitBwd (void) {

	// Show the stage info
	StageInfo ("BitField::FindResetBitBwd", BUFFER_SIZE, ROUNDS, TRIES);

	// Unsigned integer types
	TestFindBit <size_t, uint8_t> (BitField::FindResetBitBwd, FindResetBitBwd);
	TestFindBit <size_t, uint16_t> (BitField::FindResetBitBwd, FindResetBitBwd);
	TestFindBit <size_t, uint32_t> (BitField::FindResetBitBwd, FindResetBitBwd);
	TestFindBit <size_t, uint64_t> (BitField::FindResetBitBwd, FindResetBitBwd);

	// Signed integer types
	TestFindBit <size_t, sint8_t> (BitField::FindResetBitBwd, FindResetBitBwd);
	TestFindBit <size_t, sint16_t> (BitField::FindResetBitBwd, FindResetBitBwd);
	TestFindBit <size_t, sint32_t> (BitField::FindResetBitBwd, FindResetBitBwd);
	TestFindBit <size_t, sint64_t> (BitField::FindResetBitBwd, FindResetBitBwd);

	// Other types
	TestFindBit <size_t, size_t> (BitField::FindResetBitBwd, FindResetBitBwd);
}

//============================================================================//
//      Bit counting                                                          //
//============================================================================//
void TestCountBits (void) {

	// Show the stage info
	StageInfo ("BitField::CountBits", BUFFER_SIZE, ROUNDS, TRIES);

	// Unsigned integer types
	TestFindBit <size_t, uint8_t> (BitField::CountBits, CountBits);
	TestFindBit <size_t, uint16_t> (BitField::CountBits, CountBits);
	TestFindBit <size_t, uint32_t> (BitField::CountBits, CountBits);
	TestFindBit <size_t, uint64_t> (BitField::CountBits, CountBits);

	// Signed integer types
	TestFindBit <size_t, sint8_t> (BitField::CountBits, CountBits);
	TestFindBit <size_t, sint16_t> (BitField::CountBits, CountBits);
	TestFindBit <size_t, sint32_t> (BitField::CountBits, CountBits);
	TestFindBit <size_t, sint64_t> (BitField::CountBits, CountBits);

	// Other types
	TestFindBit <size_t, size_t> (BitField::CountBits, CountBits);
}

//============================================================================//
//      Check for a set bit in the bit field range                            //
//============================================================================//
void TestCheckSetBit (void) {

	// Show the stage info
	StageInfo ("BitField::CheckSetBit", BUFFER_SIZE, ROUNDS, TRIES);

	// Unsigned integer types
	TestFindBit <bool, uint8_t> (BitField::CheckSetBit, CheckSetBit);
	TestFindBit <bool, uint16_t> (BitField::CheckSetBit, CheckSetBit);
	TestFindBit <bool, uint32_t> (BitField::CheckSetBit, CheckSetBit);
	TestFindBit <bool, uint64_t> (BitField::CheckSetBit, CheckSetBit);

	// Signed integer types
	TestFindBit <bool, sint8_t> (BitField::CheckSetBit, CheckSetBit);
	TestFindBit <bool, sint16_t> (BitField::CheckSetBit, CheckSetBit);
	TestFindBit <bool, sint32_t> (BitField::CheckSetBit, CheckSetBit);
	TestFindBit <bool, sint64_t> (BitField::CheckSetBit, CheckSetBit);

	// Other types
	TestFindBit <bool, size_t> (BitField::CheckSetBit, CheckSetBit);
}

//============================================================================//
//      Check for a reset bit in the bit field range                          //
//============================================================================//
void TestCheckResetBit (void) {

	// Show the stage info
	StageInfo ("BitField::CheckResetBit", BUFFER_SIZE, ROUNDS, TRIES);

	// Unsigned integer types
	TestFindBit <bool, uint8_t> (BitField::CheckResetBit, CheckResetBit);
	TestFindBit <bool, uint16_t> (BitField::CheckResetBit, CheckResetBit);
	TestFindBit <bool, uint32_t> (BitField::CheckResetBit, CheckResetBit);
	TestFindBit <bool, uint64_t> (BitField::CheckResetBit, CheckResetBit);

	// Signed integer types
	TestFindBit <bool, sint8_t> (BitField::CheckResetBit, CheckResetBit);
	TestFindBit <bool, sint16_t> (BitField::CheckResetBit, CheckResetBit);
	TestFindBit <bool, sint32_t> (BitField::CheckResetBit, CheckResetBit);
	TestFindBit <bool, sint64_t> (BitField::CheckResetBit, CheckResetBit);

	// Other types
	TestFindBit <bool, size_t> (BitField::CheckResetBit, CheckResetBit);
}
/*
################################################################################
#                                 END OF FILE                                  #
################################################################################
*/
