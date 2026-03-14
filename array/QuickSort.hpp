/*
################################################################################
# Encoding: UTF-8                                                  Tab size: 4 #
#                                                                              #
#                   UNIT TESTS FOR THE QUICK SORT ALGORITHM                    #
#                                                                              #
# Ordnung muss sein!                             Copyleft (Ɔ) Eugene Zamlinsky #
################################################################################
*/
# pragma	once

//****************************************************************************//
//      Test function for regular array sorting                               //
//****************************************************************************//
template <typename T>
void TestQuickSort (
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
//      Test function for key array sorting                                   //
//****************************************************************************//
template <typename T>
void TestQuickSortKey (
	void (*func)(T key[], const void* ptr[], size_t size),
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

			// Create array of connected values
			RandomArray <size_t> ptr (array);

			// Apply the operation to the array data. Both the testing and the reference
			func (array.Data() + offset, reinterpret_cast <const void**> (ptr.Data() + offset), count);
			ref (reference.Data() + offset, count);

			// Compare arrays for different elements
			array.Compare (reference, EPSILON);

			// Check the connection between keys and values
			ptr.CheckValues (array);
		}
	}
}

//****************************************************************************//
//      Test function for object array sorting                                //
//****************************************************************************//
void TestQuickSortObj (
	void (*func)(const void* array[], size_t size, Cmp func),
	void (*ref)(sint64_t target[], size_t size)
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

			// Make a copy for the reference implementation of the function
			RandomArray <sint64_t> reference (array);

			// Apply the operation to the array data. Both the testing and the reference
			func (reinterpret_cast <const void**> (array.Data() + offset), count, KeyCmp);
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
void QuickSortAsc (T array[], size_t size){
	sort (array, array + size, CmpAsc <T>);
}

// Descending sort order
template <typename T>
void QuickSortDsc (T array[], size_t size){
	sort (array, array + size, CmpDsc <T>);
}

//****************************************************************************//
//      Unit test routines                                                    //
//****************************************************************************//

//============================================================================//
//      Regular array sorting                                                 //
//============================================================================//
# define	QUICK_SORT_ARRAY(func)												\
void Test##func (void) {														\
	StageInfo ("Array::" # func, BUFFER_SIZE, ROUNDS, TRIES);					\
	TestQuickSort <uint8_t> (Array::func, func);								\
	TestQuickSort <uint16_t> (Array::func, func);								\
	TestQuickSort <uint32_t> (Array::func, func);								\
	TestQuickSort <sint8_t> (Array::func, func);								\
	TestQuickSort <sint16_t> (Array::func, func);								\
	TestQuickSort <sint32_t> (Array::func, func);								\
	TestQuickSort <flt32_t> (Array::func, func);								\
}

// Ascending sort order
QUICK_SORT_ARRAY (QuickSortAsc)

// Descending sort order
QUICK_SORT_ARRAY (QuickSortDsc)

//============================================================================//
//      Key array sorting                                                     //
//============================================================================//
# define	QUICK_SORT_KEY(func,ref)											\
void Test##func (void) {														\
	StageInfo ("Array::" # func, BUFFER_SIZE, ROUNDS, TRIES);					\
	TestQuickSortKey <uint8_t> (Array::func, ref);								\
	TestQuickSortKey <uint16_t> (Array::func, ref);								\
	TestQuickSortKey <uint32_t> (Array::func, ref);								\
	TestQuickSortKey <uint64_t> (Array::func, ref);								\
	TestQuickSortKey <sint8_t> (Array::func, ref);								\
	TestQuickSortKey <sint16_t> (Array::func, ref);								\
	TestQuickSortKey <sint32_t> (Array::func, ref);								\
	TestQuickSortKey <sint64_t> (Array::func, ref);								\
	TestQuickSortKey <flt32_t> (Array::func, ref);								\
	TestQuickSortKey <flt64_t> (Array::func, ref);								\
	TestQuickSortKey <size_t> (Array::func, ref);								\
}

// Ascending sort order
QUICK_SORT_KEY (QuickSortKeyAsc, QuickSortAsc)

// Descending sort order
QUICK_SORT_KEY (QuickSortKeyDsc, QuickSortDsc)

//============================================================================//
//      Object array sorting                                                  //
//============================================================================//
# define	QUICK_SORT_OBJ(func,ref)											\
void Test##func (void) {														\
	StageInfo ("Array::" # func, BUFFER_SIZE, ROUNDS, TRIES);					\
	TestQuickSortObj (Array::func, ref);										\
}

// Forward direction search
QUICK_SORT_OBJ (QuickSortObjAsc, QuickSortAsc)

// Backward direction search
QUICK_SORT_OBJ (QuickSortObjDsc, QuickSortDsc)

/*
################################################################################
#                                 END OF FILE                                  #
################################################################################
*/
