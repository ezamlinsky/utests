/*
################################################################################
# Encoding: UTF-8                                                  Tab size: 4 #
#                                                                              #
#                   UNIT TESTS FOR THE RADIX SORT ALGORITHM                    #
#                                                                              #
# Ordnung muss sein!                             Copyleft (Ɔ) Eugene Zamlinsky #
################################################################################
*/
# pragma	once

//****************************************************************************//
//      Test function for regular array sorting                               //
//****************************************************************************//
template <typename T>
void TestRadixSort (
	void (*func)(T array[], T temp[], size_t size),
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

			// Create a temporary array needed for the sort
			RandomArray <T> temp (BUFFER_SIZE, SEED, MAX_VALUE);

			// Apply the operation to the array data. Both the testing and the reference
			func (array.Data() + offset, temp.Data(), count);
			ref (reference.Data() + offset, count);

			// Compare arrays for different elements
			array.Compare (reference, EPSILON);
		}
	}
}

//****************************************************************************//
//      Test function for key array sorting                                   //
//****************************************************************************//
template <typename T>
void TestRadixSortKey (
	void (*func)(T key[], const void* ptr[], T tkey[], const void* tptr[], size_t size),
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

			// Create temporary arrays needed for the sort
			RandomArray <T> temp (BUFFER_SIZE, SEED, MAX_VALUE);
			RandomArray <size_t> ptr (BUFFER_SIZE, SEED, MAX_VALUE);
			RandomArray <size_t> tptr (BUFFER_SIZE, SEED, MAX_VALUE);

			// Apply the operation to the array data. Both the testing and the reference
			func (array.Data() + offset, reinterpret_cast <const void**> (ptr.Data()), temp.Data(), reinterpret_cast <const void**> (tptr.Data()), count);
			ref (reference.Data() + offset, count);

			// Compare arrays for different elements
			array.Compare (reference, EPSILON);
		}
	}
}

//============================================================================//
//      Regular array sorting                                                 //
//============================================================================//

// Ascending sort order
template <typename T>
void RadixSortAsc (T array[], size_t size){
	sort (array, array + size, CmpAsc <T>);
}

// Descending sort order
template <typename T>
void RadixSortDsc (T array[], size_t size){
	sort (array, array + size, CmpDsc <T>);
}

//****************************************************************************//
//      Unit test routines                                                    //
//****************************************************************************//

//============================================================================//
//      Regular array sorting                                                 //
//============================================================================//
# define	RADIX_SORT_ARRAY(func)												\
void Test##func (void) {														\
	StageInfo ("Array::" # func, BUFFER_SIZE, ROUNDS, TRIES);					\
	TestRadixSort <uint8_t> (Array::func, func);								\
	TestRadixSort <uint16_t> (Array::func, func);								\
	TestRadixSort <uint32_t> (Array::func, func);								\
	TestRadixSort <uint64_t> (Array::func, func);								\
	TestRadixSort <sint8_t> (Array::func, func);								\
	TestRadixSort <sint16_t> (Array::func, func);								\
	TestRadixSort <sint32_t> (Array::func, func);								\
	TestRadixSort <sint64_t> (Array::func, func);								\
	TestRadixSort <flt32_t> (Array::func, func);								\
	TestRadixSort <flt64_t> (Array::func, func);								\
	TestRadixSort <size_t> (Array::func, func);									\
}

// Ascending sort order
RADIX_SORT_ARRAY (RadixSortAsc)

// Descending sort order
RADIX_SORT_ARRAY (RadixSortDsc)

//============================================================================//
//      Key array sorting                                                     //
//============================================================================//
# define	RADIX_SORT_KEY(func,ref)											\
void Test##func (void) {														\
	StageInfo ("Array::" # func, BUFFER_SIZE, ROUNDS, TRIES);					\
	TestRadixSortKey <uint8_t> (Array::func, ref);								\
	TestRadixSortKey <uint16_t> (Array::func, ref);								\
	TestRadixSortKey <uint32_t> (Array::func, ref);								\
	TestRadixSortKey <uint64_t> (Array::func, ref);								\
	TestRadixSortKey <sint8_t> (Array::func, ref);								\
	TestRadixSortKey <sint16_t> (Array::func, ref);								\
	TestRadixSortKey <sint32_t> (Array::func, ref);								\
	TestRadixSortKey <sint64_t> (Array::func, ref);								\
	TestRadixSortKey <flt32_t> (Array::func, ref);								\
	TestRadixSortKey <flt64_t> (Array::func, ref);								\
	TestRadixSortKey <size_t> (Array::func, ref);								\
}

// Ascending sort order
RADIX_SORT_KEY (RadixSortKeyAsc, RadixSortAsc)

// Descending sort order
RADIX_SORT_KEY (RadixSortKeyDsc, RadixSortDsc)

/*
################################################################################
#                                 END OF FILE                                  #
################################################################################
*/
