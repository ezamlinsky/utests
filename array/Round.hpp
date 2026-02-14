/*
################################################################################
# Encoding: UTF-8                                                  Tab size: 4 #
#                                                                              #
#                     UNIT TESTS FOR ARRAY ROUND FUNCTIONS                     #
#                                                                              #
# Ordnung muss sein!                             Copyleft (Ɔ) Eugene Zamlinsky #
################################################################################
*/
# pragma	once

//****************************************************************************//
//      Reference implementation of the functions                             //
//****************************************************************************//

// Round down (floor)
template <typename T>
void RoundDown (T array[], size_t size) {
	for (size_t i = 0; i < size; ++i)
		array[i] = floor (array[i]);
}

// Round up (ceil)
template <typename T>
void RoundUp (T array[], size_t size) {
	for (size_t i = 0; i < size; ++i)
		array[i] = ceil (array[i]);
}

// Round to the nearest integer using the current rounding mode
template <typename T>
void RoundInt (T array[], size_t size) {
	for (size_t i = 0; i < size; ++i)
		array[i] = rint (array[i]);
}

// Round to the nearest even integer
template <typename T>
void RoundEven (T array[], size_t size) {
	for (size_t i = 0; i < size; ++i)
		array[i] = roundeven (array[i]);
}

// Round to the nearest integer away from zero
template <typename T>
void Round (T array[], size_t size) {
	for (size_t i = 0; i < size; ++i)
		array[i] = round (array[i]);
}

// Round to the nearest integer toward zero (truncation)
template <typename T>
void Truncate (T array[], size_t size) {
	for (size_t i = 0; i < size; ++i)
		array[i] = trunc (array[i]);
}

// Fractional part
template <typename T>
void Frac (T array[], size_t size) {
	for (size_t i = 0; i < size; ++i)
		array[i] = array[i] - trunc (array[i]);
}

//****************************************************************************//
//      Unit test routines                                                    //
//****************************************************************************//

//============================================================================//
//      Round down (floor)                                                    //
//============================================================================//
void TestRoundDown (void) {

	// Show the stage info
	StageInfo ("Array::RoundDown", BUFFER_SIZE, ROUNDS, TRIES);

	// Floating-point types
	TestUnary <flt32_t> (Array::RoundDown, RoundDown);
	TestUnary <flt64_t> (Array::RoundDown, RoundDown);
}

//============================================================================//
//      Round up (ceil)                                                       //
//============================================================================//
void TestRoundUp (void) {

	// Show the stage info
	StageInfo ("Array::RoundUp", BUFFER_SIZE, ROUNDS, TRIES);

	// Floating-point types
	TestUnary <flt32_t> (Array::RoundUp, RoundUp);
	TestUnary <flt64_t> (Array::RoundUp, RoundUp);
}

//============================================================================//
//      Round to the nearest integer using the current rounding mode          //
//============================================================================//
void TestRoundInt (void) {

	// Show the stage info
	StageInfo ("Array::RoundInt", BUFFER_SIZE, ROUNDS, TRIES);

	// Floating-point types
	TestUnary <flt32_t> (Array::RoundInt, RoundInt);
	TestUnary <flt64_t> (Array::RoundInt, RoundInt);
}

//============================================================================//
//      Round to the nearest even integer                                     //
//============================================================================//
void TestRoundEven (void) {

	// Show the stage info
	StageInfo ("Array::RoundEven", BUFFER_SIZE, ROUNDS, TRIES);

	// Floating-point types
	TestUnary <flt32_t> (Array::RoundEven, RoundEven);
	TestUnary <flt64_t> (Array::RoundEven, RoundEven);
}

//============================================================================//
//      Round to the nearest integer away from zero                           //
//============================================================================//
void TestRound (void) {

	// Show the stage info
	StageInfo ("Array::Round", BUFFER_SIZE, ROUNDS, TRIES);

	// Floating-point types
	TestUnary <flt32_t> (Array::Round, Round);
	TestUnary <flt64_t> (Array::Round, Round);
}

//============================================================================//
//      Round to the nearest integer toward zero (truncation)                 //
//============================================================================//
void TestTruncate (void) {

	// Show the stage info
	StageInfo ("Array::Truncate", BUFFER_SIZE, ROUNDS, TRIES);

	// Floating-point types
	TestUnary <flt32_t> (Array::Truncate, Truncate);
	TestUnary <flt64_t> (Array::Truncate, Truncate);
}

//============================================================================//
//      Fractional part                                                       //
//============================================================================//
void TestFrac (void) {

	// Show the stage info
	StageInfo ("Array::Frac", BUFFER_SIZE, ROUNDS, TRIES);

	// Floating-point types
	TestUnary <flt32_t> (Array::Frac, Frac);
	TestUnary <flt64_t> (Array::Frac, Frac);
}
/*
################################################################################
#                                 END OF FILE                                  #
################################################################################
*/
