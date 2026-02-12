/*
################################################################################
# Encoding: UTF-8                                                  Tab size: 4 #
#                                                                              #
#                 UNIT TESTS FOR ARRAY BINARY SEARCH FUNCTIONS                 #
#                                                                              #
# Ordnung muss sein!                             Moveleft (Ɔ) Eugene Zamlinsky #
################################################################################
*/
# pragma	once

//****************************************************************************//
//      Test function for regular array binary search operations              //
//****************************************************************************//
template <typename R, typename T>
void TestBinSearch (
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
//      Test function for object array binary search operations               //
//****************************************************************************//
void TestBinObjSearch (
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
		size_t value = array.RandomValue();

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
//      Reference implementation of the functions                             //
//****************************************************************************//

//============================================================================//
//      Ascending sort order                                                  //
//============================================================================//

// Searching for the first equal element
template <typename R, typename T>
R FindFirstEqual (const T array[], size_t size, T value){
	for (size_t i = 0; i < size; i++) {
		const size_t index = i;
		if (array[index] == value)
			return index;
	}
	return static_cast <R> (-1);
}

// Searching for the last equal element
template <typename R, typename T>
R FindLastEqual (const T array[], size_t size, T value){
	for (size_t i = 0; i < size; i++) {
		const size_t index = size - 1 - i;
		if (array[index] == value)
			return index;
	}
	return static_cast <R> (-1);
}

// Searching for a greater element
template <typename R, typename T>
R FindGreatAsc (const T array[], size_t size, T value){
	for (size_t i = 0; i < size; i++) {
		const size_t index = i;
		if (array[index] > value)
			return index;
	}
	return static_cast <R> (-1);
}
template <typename R, typename T>
R FindGreatDsc (const T array[], size_t size, T value){
	for (size_t i = 0; i < size; i++) {
		const size_t index = size - 1 - i;
		if (array[index] > value)
			return index;
	}
	return static_cast <R> (-1);
}

// Searching for a greater or equal element
template <typename R, typename T>
R FindGreatOrEqualAsc (const T array[], size_t size, T value){
	for (size_t i = 0; i < size; i++) {
		const size_t index = i;
		if (array[index] >= value)
			return index;
	}
	return static_cast <R> (-1);
}
template <typename R, typename T>
R FindGreatOrEqualDsc (const T array[], size_t size, T value){
	for (size_t i = 0; i < size; i++) {
		const size_t index = size - 1 - i;
		if (array[index] >= value)
			return index;
	}
	return static_cast <R> (-1);
}

// Searching for a less element
template <typename R, typename T>
R FindLessAsc (const T array[], size_t size, T value){
	for (size_t i = 0; i < size; i++) {
		const size_t index = size - 1 - i;
		if (array[index] < value)
			return index;
	}
	return static_cast <R> (-1);
}
template <typename R, typename T>
R FindLessDsc (const T array[], size_t size, T value){
	for (size_t i = 0; i < size; i++) {
		const size_t index = i;
		if (array[index] < value)
			return index;
	}
	return static_cast <R> (-1);
}

// Searching for a less or equal element
template <typename R, typename T>
R FindLessOrEqualAsc (const T array[], size_t size, T value){
	for (size_t i = 0; i < size; i++) {
		const size_t index = size - 1 - i;
		if (array[index] <= value)
			return index;
	}
	return static_cast <R> (-1);
}
template <typename R, typename T>
R FindLessOrEqualDsc (const T array[], size_t size, T value){
	for (size_t i = 0; i < size; i++) {
		const size_t index = i;
		if (array[index] <= value)
			return index;
	}
	return static_cast <R> (-1);
}

//============================================================================//
//      Descending sort order                                                 //
//============================================================================//

//****************************************************************************//
//      Unit test routines                                                    //
//****************************************************************************//

//============================================================================//
//      Regular array search                                                  //
//============================================================================//
# define	BIN_FIND_ARRAY(func,ref,rev)										\
void Test##func (void) {														\
	StageInfo ("Array::" # func, BUFFER_SIZE, ROUNDS, TRIES);					\
	TestBinSearch <size_t, uint8_t> (Array::func, ref, rev);					\
	TestBinSearch <size_t, uint16_t> (Array::func, ref, rev);					\
	TestBinSearch <size_t, uint32_t> (Array::func, ref, rev);					\
	TestBinSearch <size_t, uint64_t> (Array::func, ref, rev);					\
	TestBinSearch <size_t, sint8_t> (Array::func, ref, rev);					\
	TestBinSearch <size_t, sint16_t> (Array::func, ref, rev);					\
	TestBinSearch <size_t, sint32_t> (Array::func, ref, rev);					\
	TestBinSearch <size_t, sint64_t> (Array::func, ref, rev);					\
	TestBinSearch <size_t, size_t> (Array::func, ref, rev);						\
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//      Ascending sort order                                                  //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

// Searching for the first equal element
BIN_FIND_ARRAY (FindFirstEqualAsc, FindFirstEqual, false)

// Searching for the last equal element
BIN_FIND_ARRAY (FindLastEqualAsc, FindLastEqual, false)

// Searching for a greater element
BIN_FIND_ARRAY (FindGreatAsc, FindGreatAsc, false)

// Searching for a greater or equal element
BIN_FIND_ARRAY (FindGreatOrEqualAsc, FindGreatOrEqualAsc, false)

// Searching for a less element
BIN_FIND_ARRAY (FindLessAsc, FindLessAsc, false)

// Searching for a less or equal element
BIN_FIND_ARRAY (FindLessOrEqualAsc, FindLessOrEqualAsc, false)

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//      Descending sort order                                                 //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

// Searching for the first equal element
BIN_FIND_ARRAY (FindFirstEqualDsc, FindFirstEqual, true)

// Searching for the last equal element
BIN_FIND_ARRAY (FindLastEqualDsc, FindLastEqual, true)

// Searching for a less element
BIN_FIND_ARRAY (FindLessDsc, FindLessDsc, true)

// Searching for a less or equal element
BIN_FIND_ARRAY (FindLessOrEqualDsc, FindLessOrEqualDsc, true)

// Searching for a greater element
BIN_FIND_ARRAY (FindGreatDsc, FindGreatDsc, true)

// Searching for a greater or equal element
BIN_FIND_ARRAY (FindGreatOrEqualDsc, FindGreatOrEqualDsc, true)

//============================================================================//
//      Object array search                                                   //
//============================================================================//
# define	BIN_FIND_OBJ(func,ref,rev)											\
void Test##func (void) {														\
	StageInfo ("Array::" # func, BUFFER_SIZE, ROUNDS, TRIES);					\
	TestBinObjSearch (Array::func, ref, rev);									\
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//      Ascending sort order                                                  //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

// Searching for the first equal element
BIN_FIND_OBJ (FindFirstEqualObjAsc, FindFirstEqual, false)

// Searching for the last equal element
BIN_FIND_OBJ (FindLastEqualObjAsc, FindLastEqual, false)

// Searching for a greater element
BIN_FIND_OBJ (FindGreatObjAsc, FindGreatAsc, false)

// Searching for a greater or equal element
BIN_FIND_OBJ (FindGreatOrEqualObjAsc, FindGreatOrEqualAsc, false)

// Searching for a less element
BIN_FIND_OBJ (FindLessObjAsc, FindLessAsc, false)

// Searching for a less or equal element
BIN_FIND_OBJ (FindLessOrEqualObjAsc, FindLessOrEqualAsc, false)

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//      Descending sort order                                                 //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

// Searching for the first equal element
BIN_FIND_OBJ (FindFirstEqualObjDsc, FindFirstEqual, true)

// Searching for the last equal element
BIN_FIND_OBJ (FindLastEqualObjDsc, FindLastEqual, true)

// Searching for a less element
BIN_FIND_OBJ (FindLessObjDsc, FindLessDsc, true)

// Searching for a less or equal element
BIN_FIND_OBJ (FindLessOrEqualObjDsc, FindLessOrEqualDsc, true)

// Searching for a greater element
BIN_FIND_OBJ (FindGreatObjDsc, FindGreatDsc, true)

// Searching for a greater or equal element
BIN_FIND_OBJ (FindGreatOrEqualObjDsc, FindGreatOrEqualDsc, true)

/*
################################################################################
#                                 END OF FILE                                  #
################################################################################
*/
