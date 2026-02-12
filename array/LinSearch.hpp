/*
################################################################################
# Encoding: UTF-8                                                  Tab size: 4 #
#                                                                              #
#                 UNIT TESTS FOR ARRAY LINEAR SEARCH FUNCTIONS                 #
#                                                                              #
# Ordnung muss sein!                             Moveleft (Ɔ) Eugene Zamlinsky #
################################################################################
*/
# pragma	once

//****************************************************************************//
//      Key compare function for an object array                              //
//****************************************************************************//
sint64_t KeyCmp (const void *key1, const void *key2) {
	const sint64_t val1 = reinterpret_cast <const size_t> (key1);
	const sint64_t val2 = reinterpret_cast <const size_t> (key2);
	return (val1 > val2) - (val1 < val2);
}

//****************************************************************************//
//      Test function for regular array linear search operations              //
//****************************************************************************//
template <typename R, typename T>
void TestLinSearch (
	R (*func)(const T target[], size_t size, T value),
	R (*ref)(const T target[], size_t size, T value)
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
//      Test function for object array linear search operations               //
//****************************************************************************//
void TestLinObjSearch (
	size_t (*func)(const void* array[], size_t size, const void *value, Cmp func),
	size_t (*ref)(const sint64_t target[], size_t size, sint64_t value)
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

// Forward direction search
template <typename R, typename T>
R FindFwd (const T array[], size_t size, T value){
	for (size_t i = 0; i < size; i++)
		if (array[i] == value)
			return i;
	return static_cast <R> (-1);
}

// Backward direction search
template <typename R, typename T>
R FindBwd (const T array[], size_t size, T value){
	for (size_t i = 0; i < size; i++)
		if (array[size - 1 - i] == value)
			return size - 1 - i;
	return static_cast <R> (-1);
}

//****************************************************************************//
//      Unit test routines                                                    //
//****************************************************************************//

//============================================================================//
//      Regular array search                                                  //
//============================================================================//
# define	LIN_FIND_ARRAY(func)												\
void Test##func (void) {														\
	StageInfo ("Array::" # func, BUFFER_SIZE, ROUNDS, TRIES);					\
	TestLinSearch <size_t, uint8_t> (Array::func, func);						\
	TestLinSearch <size_t, uint16_t> (Array::func, func);						\
	TestLinSearch <size_t, uint32_t> (Array::func, func);						\
	TestLinSearch <size_t, uint64_t> (Array::func, func);						\
	TestLinSearch <size_t, sint8_t> (Array::func, func);						\
	TestLinSearch <size_t, sint16_t> (Array::func, func);						\
	TestLinSearch <size_t, sint32_t> (Array::func, func);						\
	TestLinSearch <size_t, sint64_t> (Array::func, func);						\
	TestLinSearch <size_t, size_t> (Array::func, func);							\
}

// Forward direction search
LIN_FIND_ARRAY (FindFwd)

// Backward direction search
LIN_FIND_ARRAY (FindBwd)

//============================================================================//
//      Object array search                                                   //
//============================================================================//
# define	LIN_FIND_OBJ(func,ref)												\
void Test##func (void) {														\
	StageInfo ("Array::" # func, BUFFER_SIZE, ROUNDS, TRIES);					\
	TestLinObjSearch (Array::func, ref);										\
}

// Forward direction search
LIN_FIND_OBJ (FindObjFwd, FindFwd)

// Backward direction search
LIN_FIND_OBJ (FindObjBwd, FindBwd)

/*
################################################################################
#                                 END OF FILE                                  #
################################################################################
*/
