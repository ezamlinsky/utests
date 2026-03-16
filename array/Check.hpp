/*
################################################################################
# Encoding: UTF-8                                                  Tab size: 4 #
#                                                                              #
#                     UNIT TESTS FOR ARRAY CHECK FUNCTIONS                     #
#                                                                              #
# Ordnung muss sein!                             Copyleft (Ɔ) Eugene Zamlinsky #
################################################################################
*/
# pragma	once

//****************************************************************************//
//      Test function for operations with regular arrays                      //
//****************************************************************************//
template <typename R, typename T>
void TestCheck (
	R (*func)(const T array[], size_t size),
	R (*ref)(const T array[], size_t size)
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

			// Sort the array in random order
			array.Sort (i % 2);

			// Apply the operation to the array dat
			R computed_value = func (array.Data() + offset, count);
			R correct_value = ref (array.Data() + offset, count);

			// Compare the result values
			array.CheckResult (computed_value, correct_value, EPSILON);
		}
	}
}
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
template <typename R, typename T>
void TestCheck (
	R (*func)(const T array1[], const T array2[], size_t size),
	R (*ref)(const T array1[], const T array2[], size_t size)
){
	// Create an array of the target size
	RandomArray <T> array1 (BUFFER_SIZE, SEED, MAX_VALUE);
	RandomArray <T> array2 (BUFFER_SIZE, SEED, MAX_VALUE);

	// Run the test in many rounds with a random offset and element count
	for (size_t i = 0; i < ROUNDS; i++) {

		// Get a random offset inside the array and a random number of elements
		// to work with
		size_t offset1 = array1.Offset ();
		size_t offset2 = array1.Offset ();
		size_t count1 = array1.Count (offset1);
		size_t count2 = array1.Count (offset2);
		size_t count = min (count1, count2);

		// Do many tries with the same offset and element count, but different data
		for (size_t j = 0; j < TRIES; j++) {

			// Populate the arrays with random data
			array1.Populate ();
			array2.Populate ();

			// Apply the operation to the array data. Both the testing and the reference
			R computed_value = func (array1.Data() + offset1, array2.Data() + offset2, count);
			R correct_value = ref (array1.Data() + offset1, array2.Data() + offset2, count);

			// Compare the result values
			array1.CheckResult (computed_value, correct_value, EPSILON);
		}
	}
}

//****************************************************************************//
//      Test function for operations with object arrays                       //
//****************************************************************************//
void TestCheckObj (
	size_t (*func)(const void* array[], size_t size, Cmp func),
	size_t (*ref)(const sint64_t array[], size_t size)
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

			// Populate the arrays with random data
			array.Populate ();

			// Sort the array in random order
			array.Sort (i % 2);

			// Apply the operation to the array data
			size_t computed_value = func (reinterpret_cast <const void**> (array.Data() + offset), count, KeyCmp);
			size_t correct_value = ref (array.Data() + offset, count);

			// Compare the result values
			array.CheckResult (computed_value, correct_value, EPSILON);
		}
	}
}
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
void TestCheckObj (
	size_t (*func)(const void* array1[], const void* array2[], size_t size, Cmp func),
	size_t (*ref)(const sint64_t array1[], const sint64_t array2[], size_t size)
){
	// Create an array of the target size
	RandomArray <sint64_t> array1 (BUFFER_SIZE, SEED, MAX_VALUE);
	RandomArray <sint64_t> array2 (BUFFER_SIZE, SEED, MAX_VALUE);

	// Run the test in many rounds with a random offset and element count
	for (size_t i = 0; i < ROUNDS; i++) {

		// Get a random offset inside the array and a random number of elements
		// to work with
		size_t offset1 = array1.Offset ();
		size_t offset2 = array1.Offset ();
		size_t count1 = array1.Count (offset1);
		size_t count2 = array1.Count (offset2);
		size_t count = min (count1, count2);

		// Do many tries with the same offset and element count, but different data
		for (size_t j = 0; j < TRIES; j++) {

			// Populate the arrays with random data
			array1.Populate ();
			array2.Populate ();

			// Apply the operation to the array data. Both the testing and the reference
			size_t computed_value = func (reinterpret_cast <const void**> (array1.Data() + offset1), reinterpret_cast <const void**> (array2.Data() + offset2), count, KeyCmp);
			size_t correct_value = ref (array1.Data() + offset1, array2.Data() + offset2, count);

			// Compare the result values
			array1.CheckResult (computed_value, correct_value, EPSILON);
		}
	}
}

//****************************************************************************//
//      Reference implementation of the functions                             //
//****************************************************************************//

// Check for differences
template <typename R, typename T>
R CheckDiff (const T array1[], const T array2[], size_t size){
	for (size_t i = 0; i < size; i++)
		if (array1[i] != array2[i])
			return i;
	return static_cast <R> (-1);
}

// Check for duplicate values
template <typename R, typename T>
R CheckDup (const T array[], size_t size){
	const T *ptr = array + 1;
	if (size > 1)
		for (size_t i = 0; i < size - 1; i++)
			if (array[i] == ptr[i])
				return i;
	return static_cast <R> (-1);
}

// Check for ascending sort order
template <typename R, typename T>
R CheckSortAsc (const T array[], size_t size){
	const T *ptr = array + 1;
	if (size > 1)
		for (size_t i = 0; i < size - 1; i++)
			if (array[i] > ptr[i])
				return i;
	return static_cast <R> (-1);
}

// Check for descending sort order
template <typename R, typename T>
R CheckSortDsc (const T array[], size_t size){
	const T *ptr = array + 1;
	if (size > 1)
		for (size_t i = 0; i < size - 1; i++)
			if (array[i] < ptr[i])
				return i;
	return static_cast <R> (-1);
}

// Check for infinite values
template <typename R, typename T>
R CheckInf (const T array[], size_t size){
	for (size_t i = 0; i < size; i++)
		if (isinf(array[i]))
			return i;
	return static_cast <R> (-1);
}

// Check for NaN values
template <typename R, typename T>
R CheckNaN (const T array[], size_t size){
	for (size_t i = 0; i < size; i++)
		if (isnan(array[i]))
			return i;
	return static_cast <R> (-1);
}

//****************************************************************************//
//      Unit test routines                                                    //
//****************************************************************************//

//============================================================================//
//      Regular array check                                                   //
//============================================================================//
# define	CHECK_ARRAY(func)													\
void Test##func (void) {														\
	StageInfo ("Array::" # func, BUFFER_SIZE, ROUNDS, TRIES);					\
	TestCheck <size_t, uint8_t> (Array::func, func);							\
	TestCheck <size_t, uint16_t> (Array::func, func);							\
	TestCheck <size_t, uint32_t> (Array::func, func);							\
	TestCheck <size_t, uint64_t> (Array::func, func);							\
	TestCheck <size_t, sint8_t> (Array::func, func);							\
	TestCheck <size_t, sint16_t> (Array::func, func);							\
	TestCheck <size_t, sint32_t> (Array::func, func);							\
	TestCheck <size_t, sint64_t> (Array::func, func);							\
	TestCheck <size_t, flt32_t> (Array::func, func);							\
	TestCheck <size_t, flt64_t> (Array::func, func);							\
	TestCheck <size_t, size_t> (Array::func, func);								\
}

//============================================================================//
//      Object array check                                                    //
//============================================================================//
# define	CHECK_OBJ(func,ref)													\
void Test##func (void) {														\
	StageInfo ("Array::" # func, BUFFER_SIZE, ROUNDS, TRIES);					\
	TestCheckObj (Array::func, ref);											\
}

//============================================================================//
//      Check for differences                                                 //
//============================================================================//

// Regular array check
void TestCheckDiff (void) {

	// Show the stage info
	StageInfo ("Array::CheckDiff", BUFFER_SIZE, ROUNDS, TRIES);

	// Unsigned integer types
	TestCheck <size_t, uint8_t> (Array::CheckDiff, CheckDiff);
	TestCheck <size_t, uint16_t> (Array::CheckDiff, CheckDiff);
	TestCheck <size_t, uint32_t> (Array::CheckDiff, CheckDiff);
	TestCheck <size_t, uint64_t> (Array::CheckDiff, CheckDiff);

	// Signed integer types
	TestCheck <size_t, sint8_t> (Array::CheckDiff, CheckDiff);
	TestCheck <size_t, sint16_t> (Array::CheckDiff, CheckDiff);
	TestCheck <size_t, sint32_t> (Array::CheckDiff, CheckDiff);
	TestCheck <size_t, sint64_t> (Array::CheckDiff, CheckDiff);

	// Floating-point type
	TestCheck <size_t, flt32_t> (Array::CheckDiff, CheckDiff);
	TestCheck <size_t, flt64_t> (Array::CheckDiff, CheckDiff);

	// Other types
	TestCheck <size_t, size_t> (Array::CheckDiff, CheckDiff);
}

// Object array check
void TestCheckDiffObj (void) {

	// Show the stage info
	StageInfo ("Array::CheckDiffObj", BUFFER_SIZE, ROUNDS, TRIES);

	// Object array check
	TestCheckObj (Array::CheckDiffObj, CheckDiff);
}

//============================================================================//
//      Check for duplicate values                                            //
//============================================================================//

// Regular array check
CHECK_ARRAY (CheckDup)

// Object array check
CHECK_OBJ (CheckDupObj, CheckDup)

//============================================================================//
//      Check for ascending sort order                                        //
//============================================================================//

// Regular array check
CHECK_ARRAY (CheckSortAsc)

// Object array check
CHECK_OBJ (CheckSortObjAsc, CheckSortAsc)

//============================================================================//
//      Check for descending sort order                                       //
//============================================================================//

// Regular array check
CHECK_ARRAY (CheckSortDsc)

// Object array check
CHECK_OBJ (CheckSortObjDsc, CheckSortDsc)

//============================================================================//
//      Check for infinite values                                             //
//============================================================================//
void TestCheckInf (void) {

	// Show the stage info
	StageInfo ("Array::CheckInf", BUFFER_SIZE, ROUNDS, TRIES);

	// Floating-point type
	TestCheck <size_t, flt32_t> (Array::CheckInf, CheckInf);
	TestCheck <size_t, flt64_t> (Array::CheckInf, CheckInf);
}

//============================================================================//
//      Check for NaN values                                                  //
//============================================================================//
void TestCheckNaN (void) {

	// Show the stage info
	StageInfo ("Array::CheckNaN", BUFFER_SIZE, ROUNDS, TRIES);

	// Floating-point type
	TestCheck <size_t, flt32_t> (Array::CheckNaN, CheckNaN);
	TestCheck <size_t, flt64_t> (Array::CheckNaN, CheckNaN);
}
/*
################################################################################
#                                 END OF FILE                                  #
################################################################################
*/
