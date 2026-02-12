/*
################################################################################
# Encoding: UTF-8                                                  Tab size: 4 #
#                                                                              #
#                     UNIT TESTS FOR BIT FIELD OPERATIONS                      #
#                                                                              #
# Ordnung muss sein!                             Moveleft (Ɔ) Eugene Zamlinsky #
################################################################################
*/
# pragma	once

//****************************************************************************//
//      Test function for bit extract function                                //
//****************************************************************************//
template <typename T>
void TestGetBit (
	bool (*func)(const T array[], size_t size),
	bool (*ref)(const T array[], size_t size)
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

			// Make a copy for the reference implementation of the function
			RandomArray <T> reference (array);

			// Apply the operation to the array data. Both the testing and the reference
			bool computed_value = func (array.Data() + offset, count);
			bool correct_value = ref (reference.Data() + offset, count);

			// Compare the result values
			array.CheckResult (computed_value, correct_value, EPSILON);
		}
	}
}

//****************************************************************************//
//      Test unary bit operations                                             //
//****************************************************************************//
template <typename T>
void TestBitUnary (
	void (*func)(T array[], size_t size),
	void (*ref)(T array[], size_t size)
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

			// Make a copy for the reference implementation of the function
			RandomArray <T> reference (array);

			// Apply the operation to the array data. Both the testing and the reference
			func (array.Data() + offset, count);
			ref (reference.Data() + offset, count);

			// Compare arrays for different elements
			array.Compare (reference, EPSILON);
		}
	}
}

//****************************************************************************//
//      Test function for bit change operations                               //
//****************************************************************************//
template <typename T>
void TestChangeBits (
	void (*func)(T target[], size_t spos, size_t epos),
	void (*ref)(T target[], size_t spos, size_t epos)
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
			func (array.Data() + offset, spos, epos);
			ref (reference.Data() + offset, spos, epos);

			// Compare arrays for different elements
			array.Compare (reference, EPSILON);
		}
	}
}

//****************************************************************************//
//      Reference implementation of the functions                             //
//****************************************************************************//

//============================================================================//
//      Get bit value from bit field                                          //
//============================================================================//
template <typename T>
bool GetBit (const T array[], size_t index) {
	const unsigned char *ptr = reinterpret_cast <const unsigned char*> (array);
	size_t bit_index = index & 0x7;
	unsigned char mask = 1 << bit_index;
	index >>= 3;
	return ptr[index] & mask;
}

//============================================================================//
//      Set bit value in bit field                                            //
//============================================================================//
template <typename T>
void SetBit (T array[], size_t index) {
	unsigned char *ptr = reinterpret_cast <unsigned char*> (array);
	size_t bit_index = index & 0x7;
	unsigned char mask = 1 << bit_index;
	index >>= 3;
	ptr[index] |= mask;
}
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
template <typename T>
void SetBits (T array[], size_t spos, size_t epos) {
	for (size_t i = spos; i < epos; ++i)
		SetBit (array, i);
}

//============================================================================//
//      Reset bit value in bit field                                          //
//============================================================================//
template <typename T>
void ResetBit (T array[], size_t index) {
	unsigned char *ptr = reinterpret_cast <unsigned char*> (array);
	size_t bit_index = index & 0x7;
	unsigned char mask = 1 << bit_index;
	index >>= 3;
	ptr[index] &= ~mask;
}
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
template <typename T>
void ResetBits (T array[], size_t spos, size_t epos) {
	for (size_t i = spos; i < epos; ++i)
		ResetBit (array, i);
}

//============================================================================//
//      Invert bit value in bit field                                         //
//============================================================================//
template <typename T>
void InvertBit (T array[], size_t index) {
	unsigned char *ptr = reinterpret_cast <unsigned char*> (array);
	size_t bit_index = index & 0x7;
	unsigned char mask = 1 << bit_index;
	index >>= 3;
	ptr[index] ^= mask;
}
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
template <typename T>
void InvertBits (T array[], size_t spos, size_t epos) {
	for (size_t i = spos; i < epos; ++i)
		InvertBit (array, i);
}

//****************************************************************************//
//      Unit test routines                                                    //
//****************************************************************************//

//============================================================================//
//      Get bit value from a bit field                                        //
//============================================================================//
void TestGetBit (void) {

	// Show the stage info
	StageInfo ("BitField::GetBit", BUFFER_SIZE, ROUNDS, TRIES);

	// Unsigned integer types
	TestGetBit <uint8_t> (BitField::GetBit, GetBit);
	TestGetBit <uint16_t> (BitField::GetBit, GetBit);
	TestGetBit <uint32_t> (BitField::GetBit, GetBit);
	TestGetBit <uint64_t> (BitField::GetBit, GetBit);

	// Signed integer types
	TestGetBit <sint8_t> (BitField::GetBit, GetBit);
	TestGetBit <sint16_t> (BitField::GetBit, GetBit);
	TestGetBit <sint32_t> (BitField::GetBit, GetBit);
	TestGetBit <sint64_t> (BitField::GetBit, GetBit);

	// Other types
	TestGetBit <size_t> (BitField::GetBit, GetBit);
}

//============================================================================//
//      Set bit value in a bit field                                          //
//============================================================================//
void TestSetBit (void) {

	// Show the stage info
	StageInfo ("BitField::SetBit", BUFFER_SIZE, ROUNDS, TRIES);

	// Unsigned integer types
	TestBitUnary <uint8_t> (BitField::SetBit, SetBit);
	TestBitUnary <uint16_t> (BitField::SetBit, SetBit);
	TestBitUnary <uint32_t> (BitField::SetBit, SetBit);
	TestBitUnary <uint64_t> (BitField::SetBit, SetBit);

	// Signed integer types
	TestBitUnary <sint8_t> (BitField::SetBit, SetBit);
	TestBitUnary <sint16_t> (BitField::SetBit, SetBit);
	TestBitUnary <sint32_t> (BitField::SetBit, SetBit);
	TestBitUnary <sint64_t> (BitField::SetBit, SetBit);

	// Other types
	TestBitUnary <size_t> (BitField::SetBit, SetBit);
}

//============================================================================//
//      Set bits in the bit field range                                       //
//============================================================================//
void TestSetBits (void) {

	// Show the stage info
	StageInfo ("BitField::SetBits", BUFFER_SIZE, ROUNDS, TRIES);

	// Unsigned integer types
	TestChangeBits <uint8_t> (BitField::SetBits, SetBits);
	TestChangeBits <uint16_t> (BitField::SetBits, SetBits);
	TestChangeBits <uint32_t> (BitField::SetBits, SetBits);
	TestChangeBits <uint64_t> (BitField::SetBits, SetBits);

	// Signed integer types
	TestChangeBits <sint8_t> (BitField::SetBits, SetBits);
	TestChangeBits <sint16_t> (BitField::SetBits, SetBits);
	TestChangeBits <sint32_t> (BitField::SetBits, SetBits);
	TestChangeBits <sint64_t> (BitField::SetBits, SetBits);

	// Other types
	TestChangeBits <size_t> (BitField::SetBits, SetBits);
}

//============================================================================//
//      Reset bit value in a bit field                                        //
//============================================================================//
void TestResetBit (void) {

	// Show the stage info
	StageInfo ("BitField::ResetBit", BUFFER_SIZE, ROUNDS, TRIES);

	// Unsigned integer types
	TestBitUnary <uint8_t> (BitField::ResetBit, ResetBit);
	TestBitUnary <uint16_t> (BitField::ResetBit, ResetBit);
	TestBitUnary <uint32_t> (BitField::ResetBit, ResetBit);
	TestBitUnary <uint64_t> (BitField::ResetBit, ResetBit);

	// Signed integer types
	TestBitUnary <sint8_t> (BitField::ResetBit, ResetBit);
	TestBitUnary <sint16_t> (BitField::ResetBit, ResetBit);
	TestBitUnary <sint32_t> (BitField::ResetBit, ResetBit);
	TestBitUnary <sint64_t> (BitField::ResetBit, ResetBit);

	// Other types
	TestBitUnary <size_t> (BitField::ResetBit, ResetBit);
}

//============================================================================//
//      Reset bits in the bit field range                                     //
//============================================================================//
void TestResetBits (void) {

	// Show the stage info
	StageInfo ("BitField::ResetBits", BUFFER_SIZE, ROUNDS, TRIES);

	// Unsigned integer types
	TestChangeBits <uint8_t> (BitField::ResetBits, ResetBits);
	TestChangeBits <uint16_t> (BitField::ResetBits, ResetBits);
	TestChangeBits <uint32_t> (BitField::ResetBits, ResetBits);
	TestChangeBits <uint64_t> (BitField::ResetBits, ResetBits);

	// Signed integer types
	TestChangeBits <sint8_t> (BitField::ResetBits, ResetBits);
	TestChangeBits <sint16_t> (BitField::ResetBits, ResetBits);
	TestChangeBits <sint32_t> (BitField::ResetBits, ResetBits);
	TestChangeBits <sint64_t> (BitField::ResetBits, ResetBits);

	// Other types
	TestChangeBits <size_t> (BitField::ResetBits, ResetBits);
}

//============================================================================//
//      Invert bit value in a bit field                                       //
//============================================================================//
void TestInvertBit (void) {

	// Show the stage info
	StageInfo ("BitField::InvertBit", BUFFER_SIZE, ROUNDS, TRIES);

	// Unsigned integer types
	TestBitUnary <uint8_t> (BitField::InvertBit, InvertBit);
	TestBitUnary <uint16_t> (BitField::InvertBit, InvertBit);
	TestBitUnary <uint32_t> (BitField::InvertBit, InvertBit);
	TestBitUnary <uint64_t> (BitField::InvertBit, InvertBit);

	// Signed integer types
	TestBitUnary <sint8_t> (BitField::InvertBit, InvertBit);
	TestBitUnary <sint16_t> (BitField::InvertBit, InvertBit);
	TestBitUnary <sint32_t> (BitField::InvertBit, InvertBit);
	TestBitUnary <sint64_t> (BitField::InvertBit, InvertBit);

	// Other types
	TestBitUnary <size_t> (BitField::InvertBit, InvertBit);
}

//============================================================================//
//      Invert bits in the bit field range                                    //
//============================================================================//
void TestInvertBits (void) {

	// Show the stage info
	StageInfo ("BitField::InvertBits", BUFFER_SIZE, ROUNDS, TRIES);

	// Unsigned integer types
	TestChangeBits <uint8_t> (BitField::InvertBits, InvertBits);
	TestChangeBits <uint16_t> (BitField::InvertBits, InvertBits);
	TestChangeBits <uint32_t> (BitField::InvertBits, InvertBits);
	TestChangeBits <uint64_t> (BitField::InvertBits, InvertBits);

	// Signed integer types
	TestChangeBits <sint8_t> (BitField::InvertBits, InvertBits);
	TestChangeBits <sint16_t> (BitField::InvertBits, InvertBits);
	TestChangeBits <sint32_t> (BitField::InvertBits, InvertBits);
	TestChangeBits <sint64_t> (BitField::InvertBits, InvertBits);

	// Other types
	TestChangeBits <size_t> (BitField::InvertBits, InvertBits);
}

/*
################################################################################
#                                 END OF FILE                                  #
################################################################################
*/
