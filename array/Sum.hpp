/*
################################################################################
# Encoding: UTF-8                                                  Tab size: 4 #
#                                                                              #
#             UNIT TESTS FOR ARRAY NUMERICAL INTEGRATION FUNCTIONS             #
#                                                                              #
# Ordnung muss sein!                             Copyleft (Ɔ) Eugene Zamlinsky #
################################################################################
*/
# pragma	once

//****************************************************************************//
//      Test a function with no arguments                                     //
//****************************************************************************//
template <typename R, typename T>
void TestFunc0 (
	R (*func)(const T target[], size_t size),
	R (*ref)(const T target[], size_t size)
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
			R computed_value = func (array.Data() + offset, count);
			R correct_value = ref (reference.Data() + offset, count);

			// Compare the result values
			array.CheckResult (computed_value, correct_value, EPSILON);
		}
	}
}
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
template <typename T>
void TestFunc0 (
	T (*func)(const T target[], const T source[], size_t size),
	T (*ref)(const T target[], const T source[], size_t size)
){
	// Create arrays of the target size
	RandomArray <T> target (BUFFER_SIZE, SEED, MAX_VALUE);
	RandomArray <T> source (BUFFER_SIZE, SEED, MAX_VALUE);

	// Run the test in many rounds with a random offset and element count
	for (size_t i = 0; i < ROUNDS; i++) {

		// Get a random offset inside the arrays and a random number of elements
		// to work with
		size_t toffset = target.Offset ();
		size_t soffset = source.Offset ();
		size_t tcount = target.Count (toffset);
		size_t scount = source.Count (soffset);
		size_t count = min (tcount, scount);

		// Do many tries with the same offset and element count, but different data
		for (size_t j = 0; j < TRIES; j++) {

			// Populate both arrays with random data
			target.Populate ();
			source.Populate ();

			// Make a copy for the reference implementation of the function
			RandomArray <T> treference (target);
			RandomArray <T> sreference (source);

			// Apply the operation to the array data. Both the testing and the reference
			T computed_value = func (target.Data() + toffset, source.Data() + soffset, count);
			T correct_value = ref (treference.Data() + toffset, sreference.Data() + soffset, count);

			// Compare the result values
			target.CheckResult (computed_value, correct_value, EPSILON);
		}
	}
}

//****************************************************************************//
//      Test a function with 1 argument                                       //
//****************************************************************************//
template <typename R, typename T>
void TestFunc1 (
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
//      Test a function with 2 arguments                                      //
//****************************************************************************//
template <typename T>
void TestFunc2 (
	T (*func)(const T target[], const T source[], size_t size, T value1, T value2),
	T (*ref)(const T target[], const T source[], size_t size, T value1, T value2)
){
	// Create arrays of the target size
	RandomArray <T> target (BUFFER_SIZE, SEED, MAX_VALUE);
	RandomArray <T> source (BUFFER_SIZE, SEED, MAX_VALUE);

	// Run the test in many rounds with a random offset and element count
	for (size_t i = 0; i < ROUNDS; i++) {

		// Get a random offset inside the arrays and a random number of elements
		// to work with
		size_t toffset = target.Offset ();
		size_t soffset = source.Offset ();
		size_t tcount = target.Count (toffset);
		size_t scount = source.Count (soffset);
		size_t count = min (tcount, scount);

		// Create random scalar values for the test
		T value1 = target.RandomValue();
		T value2 = source.RandomValue();

		// Do many tries with the same offset and element count, but different data
		for (size_t j = 0; j < TRIES; j++) {

			// Populate both arrays with random data
			target.Populate ();
			source.Populate ();

			// Make a copy for the reference implementation of the function
			RandomArray <T> treference (target);
			RandomArray <T> sreference (source);

			// Apply the operation to the array data. Both the testing and the reference
			T computed_value = func (target.Data() + toffset, source.Data() + soffset, count, value1, value2);
			T correct_value = ref (treference.Data() + toffset, sreference.Data() + soffset, count, value1, value2);

			// Compare the result values
			target.CheckResult (computed_value, correct_value, EPSILON);
		}
	}
}

//****************************************************************************//
//      Reference implementation of the functions                             //
//****************************************************************************//

// Sum of values
template <typename T>
T Sum (const T array[], size_t size) {
	T sum = 0;
	for (size_t i = 0; i < size; i++)
		sum += array[i];
	return sum;
}

// Sum of absolute values
template <typename T>
T SumAbs (const T array[], size_t size){
	T sum = 0;
	for (size_t i = 0; i < size; i++)
		sum += fabs (array[i]);
	return sum;
}

// Sum of squared values
template <typename T>
T SumSqr (const T array[], size_t size){
	T sum = 0;
	for (size_t i = 0; i < size; i++)
		sum += array[i] * array[i];
	return sum;
}

// Sum of multiplied values
template <typename T>
T SumMul (const T array1[], const T array2[], size_t size){
	T sum = 0;
	for (size_t i = 0; i < size; i++)
		sum += array1[i] * array2[i];
	return sum;
}

// Sum of signed differences
template <typename T>
T SumDiff (const T array[], size_t size, T value){
	T sum = 0;
	for (size_t i = 0; i < size; i++)
		sum += array[i] - value;
	return sum;
}

// Sum of absolute differences
template <typename T>
T SumAbsDiff (const T array[], size_t size, T value){
	T sum = 0;
	for (size_t i = 0; i < size; i++)
		sum += fabs (array[i] - value);
	return sum;
}

// Sum of squared differences
template <typename T>
T SumSqrDiff (const T array[], size_t size, T value){
	T sum = 0;
	for (size_t i = 0; i < size; i++) {
		const T diff = array[i] - value;
		sum += diff * diff;
	}
	return sum;
}

// Sum of multiplied differences
template <typename T>
T SumMulDiff (const T array1[], const T array2[], size_t size, T value1, T value2){
	T sum = 0;
	for (size_t i = 0; i < size; i++) {
		const T diff1 = array1[i] - value1;
		const T diff2 = array2[i] - value2;
		sum += diff1 * diff2;
	}
	return sum;
}

// Sum of signed distances
template <typename T>
T SumDist (const T array1[], const T array2[], size_t size){
	T sum = 0;
	for (size_t i = 0; i < size; i++)
		sum += array1[i] - array2[i];
	return sum;
}

// Sum of absolute distances
template <typename T>
T SumAbsDist (const T array1[], const T array2[], size_t size){
	T sum = 0;
	for (size_t i = 0; i < size; i++)
		sum += fabs (array1[i] - array2[i]);
	return sum;
}

// Sum of squared distances
template <typename T>
T SumSqrDist (const T array1[], const T array2[], size_t size){
	T sum = 0;
	for (size_t i = 0; i < size; i++) {
		const T diff = array1[i] - array2[i];
		sum += diff * diff;
	}
	return sum;
}

//****************************************************************************//
//      Unit test routines                                                    //
//****************************************************************************//

//============================================================================//
//      Sum of values                                                         //
//============================================================================//
void TestSum (void) {

	// Show the stage info
	StageInfo ("Array::Sum", BUFFER_SIZE, ROUNDS, TRIES);

	// Floating-point types
	TestFunc0 <flt32_t> (Array::Sum, Sum);
	TestFunc0 <flt64_t> (Array::Sum, Sum);
}

//============================================================================//
//      Sum of absolute values                                                //
//============================================================================//
void TestSumAbs (void) {

	// Show the stage info
	StageInfo ("Array::SumAbs", BUFFER_SIZE, ROUNDS, TRIES);

	// Floating-point types
	TestFunc0 <flt32_t> (Array::SumAbs, SumAbs);
	TestFunc0 <flt64_t> (Array::SumAbs, SumAbs);
}

//============================================================================//
//      Sum of squared values                                                 //
//============================================================================//
void TestSumSqr (void) {

	// Show the stage info
	StageInfo ("Array::SumSqr", BUFFER_SIZE, ROUNDS, TRIES);

	// Floating-point types
	TestFunc0 <flt32_t> (Array::SumSqr, SumSqr);
	TestFunc0 <flt64_t> (Array::SumSqr, SumSqr);
}

//============================================================================//
//      Sum of multiplied values                                              //
//============================================================================//
void TestSumMul (void) {

	// Show the stage info
	StageInfo ("Array::SumMul", BUFFER_SIZE, ROUNDS, TRIES);

	// Floating-point types
	TestFunc0 <flt32_t> (Array::SumMul, SumMul);
	TestFunc0 <flt64_t> (Array::SumMul, SumMul);
}

//============================================================================//
//      Sum of signed differences                                             //
//============================================================================//
void TestSumDiff (void) {

	// Show the stage info
	StageInfo ("Array::SumDiff", BUFFER_SIZE, ROUNDS, TRIES);

	// Floating-point types
	TestFunc1 <flt32_t> (Array::SumDiff, SumDiff);
	TestFunc1 <flt64_t> (Array::SumDiff, SumDiff);
}

//============================================================================//
//      Sum of absolute differences                                           //
//============================================================================//
void TestSumAbsDiff (void) {

	// Show the stage info
	StageInfo ("Array::SumAbsDiff", BUFFER_SIZE, ROUNDS, TRIES);

	// Floating-point types
	TestFunc1 <flt32_t> (Array::SumAbsDiff, SumAbsDiff);
	TestFunc1 <flt64_t> (Array::SumAbsDiff, SumAbsDiff);
}

//============================================================================//
//      Sum of squared differences                                            //
//============================================================================//
void TestSumSqrDiff (void) {

	// Show the stage info
	StageInfo ("Array::SumSqrDiff", BUFFER_SIZE, ROUNDS, TRIES);

	// Floating-point types
	TestFunc1 <flt32_t> (Array::SumSqrDiff, SumSqrDiff);
	TestFunc1 <flt64_t> (Array::SumSqrDiff, SumSqrDiff);
}

//============================================================================//
//      Sum of multiplied differences                                         //
//============================================================================//
void TestSumMulDiff (void) {

	// Show the stage info
	StageInfo ("Array::SumMulDiff", BUFFER_SIZE, ROUNDS, TRIES);

	// Floating-point types
	TestFunc2 <flt32_t> (Array::SumMulDiff, SumMulDiff);
	TestFunc2 <flt64_t> (Array::SumMulDiff, SumMulDiff);
}

//============================================================================//
//      Sum of signed distances                                               //
//============================================================================//
void TestSumDist (void) {

	// Show the stage info
	StageInfo ("Array::SumDist", BUFFER_SIZE, ROUNDS, TRIES);

	// Floating-point types
	TestFunc0 <flt32_t> (Array::SumDist, SumDist);
	TestFunc0 <flt64_t> (Array::SumDist, SumDist);
}

//============================================================================//
//      Sum of absolute distances                                             //
//============================================================================//
void TestSumAbsDist (void) {

	// Show the stage info
	StageInfo ("Array::SumAbsDist", BUFFER_SIZE, ROUNDS, TRIES);

	// Floating-point types
	TestFunc0 <flt32_t> (Array::SumAbsDist, SumAbsDist);
	TestFunc0 <flt64_t> (Array::SumAbsDist, SumAbsDist);
}

//============================================================================//
//      Sum of squared distances                                              //
//============================================================================//
void TestSumSqrDist (void) {

	// Show the stage info
	StageInfo ("Array::SumSqrDist", BUFFER_SIZE, ROUNDS, TRIES);

	// Floating-point types
	TestFunc0 <flt32_t> (Array::SumSqrDist, SumSqrDist);
	TestFunc0 <flt64_t> (Array::SumSqrDist, SumSqrDist);
}

/*
################################################################################
#                                 END OF FILE                                  #
################################################################################
*/
