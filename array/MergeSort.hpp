/*
################################################################################
# Encoding: UTF-8                                                  Tab size: 4 #
#                                                                              #
#                   UNIT TESTS FOR THE MERGE SORT ALGORITHM                    #
#                                                                              #
# Ordnung muss sein!                             Copyleft (Ɔ) Eugene Zamlinsky #
################################################################################
*/
# pragma	once

//****************************************************************************//
//      Test function for regular array sorting                               //
//****************************************************************************//
template <typename T>
void TestMergeSort (
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
			func (array.Data() + offset, temp.Data() + offset, count);
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
void TestMergeSortKey (
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
			RandomArray <size_t> ptr (array);
			RandomArray <size_t> tptr (BUFFER_SIZE, SEED, MAX_VALUE);

			// Apply the operation to the array data. Both the testing and the reference
			func (array.Data() + offset, reinterpret_cast <const void**> (ptr.Data() + offset), temp.Data(), reinterpret_cast <const void**> (tptr.Data()), count);
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
void TestMergeSortObj (
	void (*func)(const void* array[], const void* temp[], size_t size, Cmp func),
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

			// Create a temporary array needed for the sort
			RandomArray <sint64_t> temp (BUFFER_SIZE, SEED, MAX_VALUE);

			// Apply the operation to the array data. Both the testing and the reference
			func (reinterpret_cast <const void**> (array.Data() + offset), reinterpret_cast <const void**> (temp.Data() + offset), count, KeyCmp);
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
void MergeSortAsc (T array[], size_t size){
	sort (array, array + size, CmpAsc <T>);
}

// Descending sort order
template <typename T>
void MergeSortDsc (T array[], size_t size){
	sort (array, array + size, CmpDsc <T>);
}

//****************************************************************************//
//      Unit test routines                                                    //
//****************************************************************************//

//============================================================================//
//      Regular array sorting                                                 //
//============================================================================//
# define	MERGE_SORT_ARRAY(func)												\
void Test##func (void) {														\
	StageInfo ("Array::" # func, BUFFER_SIZE, ROUNDS, TRIES);					\
	TestMergeSort <uint8_t> (Array::func, func);								\
	TestMergeSort <uint16_t> (Array::func, func);								\
	TestMergeSort <uint32_t> (Array::func, func);								\
	TestMergeSort <sint8_t> (Array::func, func);								\
	TestMergeSort <sint16_t> (Array::func, func);								\
	TestMergeSort <sint32_t> (Array::func, func);								\
	TestMergeSort <flt32_t> (Array::func, func);								\
}

// Ascending sort order
MERGE_SORT_ARRAY (MergeSortAsc)

// Descending sort order
MERGE_SORT_ARRAY (MergeSortDsc)

//============================================================================//
//      Key array sorting                                                     //
//============================================================================//
# define	MERGE_SORT_KEY(func,ref)											\
void Test##func (void) {														\
	StageInfo ("Array::" # func, BUFFER_SIZE, ROUNDS, TRIES);					\
	TestMergeSortKey <uint8_t> (Array::func, ref);								\
	TestMergeSortKey <uint16_t> (Array::func, ref);								\
	TestMergeSortKey <uint32_t> (Array::func, ref);								\
	TestMergeSortKey <uint64_t> (Array::func, ref);								\
	TestMergeSortKey <sint8_t> (Array::func, ref);								\
	TestMergeSortKey <sint16_t> (Array::func, ref);								\
	TestMergeSortKey <sint32_t> (Array::func, ref);								\
	TestMergeSortKey <sint64_t> (Array::func, ref);								\
	TestMergeSortKey <flt32_t> (Array::func, ref);								\
	TestMergeSortKey <flt64_t> (Array::func, ref);								\
	TestMergeSortKey <size_t> (Array::func, ref);								\
}

// Ascending sort order
MERGE_SORT_KEY (MergeSortKeyAsc, MergeSortAsc)

// Descending sort order
MERGE_SORT_KEY (MergeSortKeyDsc, MergeSortDsc)

//============================================================================//
//      Object array sorting                                                  //
//============================================================================//
# define	MERGE_SORT_OBJ(func,ref)											\
void Test##func (void) {														\
	StageInfo ("Array::" # func, BUFFER_SIZE, ROUNDS, TRIES);					\
	TestMergeSortObj (Array::func, ref);										\
}

// Forward direction search
MERGE_SORT_OBJ (MergeSortObjAsc, MergeSortAsc)

// Backward direction search
MERGE_SORT_OBJ (MergeSortObjDsc, MergeSortDsc)

/*
################################################################################
#                                 END OF FILE                                  #
################################################################################
*/
