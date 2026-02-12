/*
################################################################################
# Encoding: UTF-8                                                  Tab size: 4 #
#                                                                              #
#                  UNIT TESTS FOR ARRAY MIN AND MAX FUNCTIONS                  #
#                                                                              #
# Ordnung muss sein!                             Moveleft (Ɔ) Eugene Zamlinsky #
################################################################################
*/
# pragma	once
# include	<algorithm>

//****************************************************************************//
//      Test the min and max function                                         //
//****************************************************************************//
template <typename T, typename R>
void TestMinMax (
	void (*func)(const T target[], size_t size, R &min, R &max),
	void (*ref)(const T target[], size_t size, R &min, R &max)
){
	// Create an array of the target size
	random_device rd;
	mt19937 gen (rd());
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
			R computed_min, computed_max;
			R correct_min, correct_max;
			func (array.Data() + offset, count, computed_min, computed_max);
			ref (reference.Data() + offset, count, correct_min, correct_max);

			// Compare the min value
			array.CheckResult (computed_min, correct_min, EPSILON);
			array.CheckResult (computed_max, correct_max, EPSILON);
		}
	}
}

//****************************************************************************//
//      Reference implementation of the functions                             //
//****************************************************************************//
template <typename T>
inline bool cmp_abs (
	const T& a,				// The first value
	const T& b				// The second value
){
	return fabs (a) < fabs (b);
}

// Minimum value
template <typename T>
T Min (const T array[], size_t size){
	if (size)
		return *min_element (array, array + size);
	else {
		if constexpr (is_integral_v <T>)
			return 0;
		else
			return NAN;
	}
}

// Maximum value
template <typename T>
T Max (const T array[], size_t size){
	if (size)
		return *max_element (array, array + size);
	else {
		if constexpr (is_integral_v <T>)
			return 0;
		else
			return NAN;
	}
}

// Both minimum and maximum values
template <typename T>
void MinMax (
	const T array[], size_t size, T &min, T &max
){
	using namespace std;
	if (size) {
		auto bounds = minmax_element (array, array + size);
		min = *bounds.first;
		max = *bounds.second;
	}
	else {
		if constexpr (is_integral_v <T>) {
			min = 0;
			max = 0;
		}
		else {
			min = NAN;
			max = NAN;
		}
	}
}

// Minimum absolute value
template <typename R, typename T>
R MinAbs (const T array[], size_t size){
	if (size)
		return fabs (*min_element (array, array + size, cmp_abs<T>));
	else {
		if constexpr (is_integral_v <T>)
			return 0;
		else
			return NAN;
	}
}

// Maximum absolute value
template <typename R, typename T>
R MaxAbs (const T array[], size_t size){
	if (size)
		return fabs (*max_element (array, array + size, cmp_abs<T>));
	else {
		if constexpr (is_integral_v <T>)
			return 0;
		else
			return NAN;
	}
}

// Both minimum and maximum absolute values
template <typename T, typename R>
void MinMaxAbs (
	const T array[], size_t size, R &min, R &max
){
	using namespace std;
	if (size) {
		auto bounds = minmax_element (array, array + size, cmp_abs<T>);
		min = fabs (*bounds.first);
		max = fabs (*bounds.second);
	}
	else {
		if constexpr (is_integral_v <T>) {
			min = 0;
			max = 0;
		}
		else {
			min = NAN;
			max = NAN;
		}
	}
}

//****************************************************************************//
//      Unit test routines                                                    //
//****************************************************************************//

//============================================================================//
//      Minimum value                                                         //
//============================================================================//
void TestMin (void) {

	// Show the stage info
	StageInfo ("Array::Min", BUFFER_SIZE, ROUNDS, TRIES);

	// Unsigned integer types
	TestFunc0 <uint8_t> (Array::Min, Min);
	TestFunc0 <uint16_t> (Array::Min, Min);
	TestFunc0 <uint32_t> (Array::Min, Min);
//	TestFunc0 <uint64_t> (Array::Min, Min);

	// Signed integer types
	TestFunc0 <sint8_t> (Array::Min, Min);
	TestFunc0 <sint16_t> (Array::Min, Min);
	TestFunc0 <sint32_t> (Array::Min, Min);
//	TestFunc0 <sint64_t> (Array::Min, Min);

	// Floating-point types
	TestFunc0 <flt32_t> (Array::Min, Min);
	TestFunc0 <flt64_t> (Array::Min, Min);
}

//============================================================================//
//      Maximum value                                                         //
//============================================================================//
void TestMax (void) {

	// Show the stage info
	StageInfo ("Array::Max", BUFFER_SIZE, ROUNDS, TRIES);

	// Unsigned integer types
	TestFunc0 <uint8_t> (Array::Max, Max);
	TestFunc0 <uint16_t> (Array::Max, Max);
	TestFunc0 <uint32_t> (Array::Max, Max);
//	TestFunc0 <uint64_t> (Array::Max, Max);

	// Signed integer types
	TestFunc0 <sint8_t> (Array::Max, Max);
	TestFunc0 <sint16_t> (Array::Max, Max);
	TestFunc0 <sint32_t> (Array::Max, Max);
//	TestFunc0 <sint64_t> (Array::Max, Max);

	// Floating-point types
	TestFunc0 <flt32_t> (Array::Max, Max);
	TestFunc0 <flt64_t> (Array::Max, Max);
}

//============================================================================//
//      Both minimum and maximum values                                       //
//============================================================================//
void TestMinMax (void) {

	// Show the stage info
	StageInfo ("Array::MinMax", BUFFER_SIZE, ROUNDS, TRIES);

	// Unsigned integer types
	TestMinMax <uint8_t, uint8_t> (Array::MinMax, MinMax);
	TestMinMax <uint16_t, uint16_t> (Array::MinMax, MinMax);
	TestMinMax <uint32_t, uint32_t> (Array::MinMax, MinMax);
//	TestMinMax <uint64_t, uint64_t> (Array::MinMax, MinMax);

	// Signed integer types
	TestMinMax <sint8_t, sint8_t> (Array::MinMax, MinMax);
	TestMinMax <sint16_t, sint16_t> (Array::MinMax, MinMax);
	TestMinMax <sint32_t, sint32_t> (Array::MinMax, MinMax);
//	TestMinMax <sint64_t, sint64_t> (Array::MinMax, MinMax);

	// Floating-point types
	TestMinMax <flt32_t, flt32_t> (Array::MinMax, MinMax);
	TestMinMax <flt64_t, flt64_t> (Array::MinMax, MinMax);
}

//============================================================================//
//      Minimum absolute value                                                //
//============================================================================//
void TestMinAbs (void) {

	// Show the stage info
	StageInfo ("Array::MinAbs", BUFFER_SIZE, ROUNDS, TRIES);

	// Signed integer types
	TestFunc0 <uint8_t, sint8_t> (Array::MinAbs, MinAbs);
	TestFunc0 <uint16_t, sint16_t> (Array::MinAbs, MinAbs);
	TestFunc0 <uint32_t, sint32_t> (Array::MinAbs, MinAbs);
//	TestFunc0 <uint64_t, sint64_t> (Array::MinAbs, MinAbs);

	// Floating-point types
	TestFunc0 <flt32_t, flt32_t> (Array::MinAbs, MinAbs);
	TestFunc0 <flt64_t, flt64_t> (Array::MinAbs, MinAbs);
}

//============================================================================//
//      Maximum absolute value                                                //
//============================================================================//
void TestMaxAbs (void) {

	// Show the stage info
	StageInfo ("Array::MaxAbs", BUFFER_SIZE, ROUNDS, TRIES);

	// Signed integer types
	TestFunc0 <uint8_t, sint8_t> (Array::MaxAbs, MaxAbs);
	TestFunc0 <uint16_t, sint16_t> (Array::MaxAbs, MaxAbs);
	TestFunc0 <uint32_t, sint32_t> (Array::MaxAbs, MaxAbs);
//	TestFunc0 <uint64_t, sint64_t> (Array::MaxAbs, MaxAbs);

	// Floating-point types
	TestFunc0 <flt32_t, flt32_t> (Array::MaxAbs, MaxAbs);
	TestFunc0 <flt64_t, flt64_t> (Array::MaxAbs, MaxAbs);
}

//============================================================================//
//      Both minimum and maximum absolute values                              //
//============================================================================//
void TestMinMaxAbs (void) {

	// Show the stage info
	StageInfo ("Array::MinMaxAbs", BUFFER_SIZE, ROUNDS, TRIES);

	// Signed integer types
	TestMinMax <sint8_t, uint8_t> (Array::MinMaxAbs, MinMaxAbs);
	TestMinMax <sint16_t, uint16_t> (Array::MinMaxAbs, MinMaxAbs);
	TestMinMax <sint32_t, uint32_t> (Array::MinMaxAbs, MinMaxAbs);
//	TestMinMax <sint64_t, uint64_t> (Array::MinMaxAbs, MinMaxAbs);

	// Floating-point types
	TestMinMax <flt32_t, flt32_t> (Array::MinMaxAbs, MinMaxAbs);
	TestMinMax <flt64_t, flt64_t> (Array::MinMaxAbs, MinMaxAbs);

}
/*
################################################################################
#                                 END OF FILE                                  #
################################################################################
*/
