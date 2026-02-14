/*
################################################################################
# Encoding: UTF-8                                                  Tab size: 4 #
#                                                                              #
#           UNIT TESTS FOR ARITHMETIC OPERATIONS OVER ARRAY ELEMENTS           #
#                                                                              #
# Ordnung muss sein!                             Copyleft (Ɔ) Eugene Zamlinsky #
################################################################################
*/
# pragma	once
# include	<limits>
# include	<bit>
# include	<cmath>

//****************************************************************************//
//      Test unary operation                                                  //
//****************************************************************************//
template <typename T>
void TestUnary (
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
//      Test fused operation                                                  //
//****************************************************************************//
template <typename T>
void TestFused (
	void (*func)(T target[], const T source[], size_t size, T value),
	void (*ref)(T target[], const T source[], size_t size, T value)
){
	// Create an array of the target size
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

		// Create a random scalar value for the test
		T value = source.RandomValue();

		// Do many tries with the same offset and element count, but different data
		for (size_t j = 0; j < TRIES; j++) {

			// Populate both arrays with random data
			target.Populate ();
			source.Populate ();

			// Make a copy for the reference implementation of the function
			RandomArray <T> treference (target);
			RandomArray <T> sreference (source);

			// Apply the operation to the array data. Both the testing and the reference
			func (target.Data() + toffset, source.Data() + soffset, count, value);
			ref (treference.Data() + toffset, sreference.Data() + soffset, count, value);

			// Compare arrays for different elements
			target.Compare (treference, EPSILON);
			source.Compare (sreference, EPSILON);
		}
	}
}

//****************************************************************************//
//      Reference implementation of the functions                             //
//****************************************************************************//
template <typename T>
T reverse_bits (T value) {
	T result = 0;
	constexpr int num_bits = numeric_limits <T>::digits;
	for (int i = 0; i < num_bits; ++i) {
		result |= (value & 1) << (num_bits - 1 - i);
		value >>= 1;
	}
	return result;
}

template <typename T>
T bits_count (T value) {
	T result = 0;
	constexpr int num_bits = numeric_limits <T>::digits;
	for (int i = 0; i < num_bits; ++i) {
		if (value & 1) result++;
		value >>= 1;
	}
	return result;
}

//============================================================================//
//      Bitwise operations                                                    //
//============================================================================//

// Byte swap
template <typename T>
void ByteSwap (T array[], size_t size) {
	for (size_t i = 0; i < size; ++i)
		array[i] = byteswap (array[i]);
}

// Bit reversal permutation
template <typename T>
void BitReverse (T array[], size_t size) {
	for (size_t i = 0; i < size; ++i)
		array[i] = reverse_bits (array[i]);
}

// Population count
template <typename T>
void PopCount (T array[], size_t size) {
	for (size_t i = 0; i < size; ++i)
		array[i] = bits_count (array[i]);
}

// Bitwise NOT
template <typename T>
void Not (T array[], size_t size) {
	for (size_t i = 0; i < size; ++i)
		array[i] = ~array[i];
}

// Scalar bitwise AND
template <typename T>
void AndScalar (T array[], size_t size, T value) {
	for (size_t i = 0; i < size; ++i)
		array[i] &= value;
}

// Vector bitwise AND
template <typename T>
void AndVector (T target[], const T source[], size_t size) {
	for (size_t i = 0; i < size; ++i)
		target[i] &= source[i];
}

// Scalar bitwise OR
template <typename T>
void OrScalar (T array[], size_t size, T value) {
	for (size_t i = 0; i < size; ++i)
		array[i] |= value;
}

// Vector bitwise OR
template <typename T>
void OrVector (T target[], const T source[], size_t size) {
	for (size_t i = 0; i < size; ++i)
		target[i] |= source[i];
}

// Scalar bitwise XOR
template <typename T>
void XorScalar (T array[], size_t size, T value) {
	for (size_t i = 0; i < size; ++i)
		array[i] ^= value;
}

// Vector bitwise XOR
template <typename T>
void XorVector (T target[], const T source[], size_t size) {
	for (size_t i = 0; i < size; ++i)
		target[i] ^= source[i];
}

//============================================================================//
//      Arithmetic operations                                                 //
//============================================================================//

// Negative value
template <typename T>
void Neg (T array[], size_t size) {
	for (size_t i = 0; i < size; ++i)
		array[i] = -array[i];
}

// Absolute value
template <typename T>
void Abs (T array[], size_t size) {
	for (size_t i = 0; i < size; ++i)
		array[i] = array[i] < 0 ? -array[i] : array[i];
}

// Negative absolute value
template <typename T>
void NegAbs (T array[], size_t size) {
	for (size_t i = 0; i < size; ++i)
		array[i] = array[i] > 0 ? -array[i] : array[i];
}

// Number sign
template <typename T>
void Sign (T array[], size_t size) {
	for (size_t i = 0; i < size; ++i)
		array[i] = (array[i] > T(0)) - (array[i] < T(0));
}

// Square
template <typename T>
void Sqr (T array[], size_t size) {
	for (size_t i = 0; i < size; ++i)
		array[i] = array[i] * array[i];
}

// Square root
template <typename T>
void Sqrt (T array[], size_t size) {
	for (size_t i = 0; i < size; ++i)
		array[i] = sqrt (array[i]);
}

// Scalar addition
template <typename T>
void AddScalar (T array[], size_t size, T value) {
	for (size_t i = 0; i < size; ++i)
		array[i] += value;
}

// Vector addition
template <typename T>
void AddVector (T target[], const T source[], size_t size) {
	for (size_t i = 0; i < size; ++i)
		target[i] += source[i];
}

// Scalar subtraction
template <typename T>
void SubScalar (T array[], size_t size, T value) {
	for (size_t i = 0; i < size; ++i)
		array[i] -= value;
}

// Vector subtraction
template <typename T>
void SubVector (T target[], const T source[], size_t size) {
	for (size_t i = 0; i < size; ++i)
		target[i] -= source[i];
}

// Scalar reverse subtraction
template <typename T>
void ReverseSubScalar (T array[], size_t size, T value) {
	for (size_t i = 0; i < size; ++i)
		array[i] = value - array[i];
}

// Vector reverse subtraction
template <typename T>
void ReverseSubVector (T target[], const T source[], size_t size) {
	for (size_t i = 0; i < size; ++i)
		target[i] = source[i] - target[i];
}

// Scalar multiplication
template <typename T>
void MulScalar (T array[], size_t size, T value) {
	for (size_t i = 0; i < size; ++i)
		array[i] *= value;
}

// Vector multiplication
template <typename T>
void MulVector (T target[], const T source[], size_t size) {
	for (size_t i = 0; i < size; ++i)
		target[i] *= source[i];
}

// Scalar division
template <typename T>
void DivScalar (T array[], size_t size, T value) {
	for (size_t i = 0; i < size; ++i)
		array[i] /= value;
}

// Vector division
template <typename T>
void DivVector (T target[], const T source[], size_t size) {
	for (size_t i = 0; i < size; ++i)
		target[i] /= source[i];
}

// Scalar reverse division
template <typename T>
void ReverseDivScalar (T array[], size_t size, T value) {
	for (size_t i = 0; i < size; ++i)
		array[i] = value / array[i];
}

// Vector reverse division
template <typename T>
void ReverseDivVector (T target[], const T source[], size_t size) {
	for (size_t i = 0; i < size; ++i)
		target[i] = source[i] / target[i];
}

//============================================================================//
//      Fused arithmetic operations                                           //
//============================================================================//

// Fused addition
template <typename T>
void FusedAdd (T target[], const T source[], size_t size, T value) {
	for (size_t i = 0; i < size; ++i)
		target[i] += source[i] * value;
}

// Fused subtraction
template <typename T>
void FusedSub (T target[], const T source[], size_t size, T value) {
	for (size_t i = 0; i < size; ++i)
		target[i] -= source[i] * value;
}

//****************************************************************************//
//      Unit test routines                                                    //
//****************************************************************************//

//============================================================================//
//      Bitwise operations                                                    //
//============================================================================//

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//      Byte swap                                                             //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void TestByteSwap (void) {

	// Show the stage info
	StageInfo ("Array::ByteSwap", BUFFER_SIZE, ROUNDS, TRIES);

	// Unsigned integer types
	TestUnary <uint8_t> (Array::ByteSwap, ByteSwap);
	TestUnary <uint16_t> (Array::ByteSwap, ByteSwap);
	TestUnary <uint32_t> (Array::ByteSwap, ByteSwap);
	TestUnary <uint64_t> (Array::ByteSwap, ByteSwap);

	// Signed integer types
	TestUnary <sint8_t> (Array::ByteSwap, ByteSwap);
	TestUnary <sint16_t> (Array::ByteSwap, ByteSwap);
	TestUnary <sint32_t> (Array::ByteSwap, ByteSwap);
	TestUnary <sint64_t> (Array::ByteSwap, ByteSwap);

	// Other types
	TestUnary <size_t> (Array::ByteSwap, ByteSwap);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//      Bit reversal permutation                                              //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void TestBitReverse (void) {

	// Show the stage info
	StageInfo ("Array::BitReverse", BUFFER_SIZE, ROUNDS, TRIES);

	// Unsigned integer types
	TestUnary <uint8_t> (Array::BitReverse, BitReverse);
	TestUnary <uint16_t> (Array::BitReverse, BitReverse);
	TestUnary <uint32_t> (Array::BitReverse, BitReverse);
	TestUnary <uint64_t> (Array::BitReverse, BitReverse);

	// Signed integer types
//	TestUnary <sint8_t> (Array::BitReverse, BitReverse);
//	TestUnary <sint16_t> (Array::BitReverse, BitReverse);
//	TestUnary <sint32_t> (Array::BitReverse, BitReverse);
//	TestUnary <sint64_t> (Array::BitReverse, BitReverse);

	// Other types
	TestUnary <size_t> (Array::BitReverse, BitReverse);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//      Population count                                                      //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void TestPopCount (void) {

	// Show the stage info
	StageInfo ("Array::PopCount", BUFFER_SIZE, ROUNDS, TRIES);

	// Unsigned integer types
	TestUnary <uint8_t> (Array::PopCount, PopCount);
	TestUnary <uint16_t> (Array::PopCount, PopCount);
	TestUnary <uint32_t> (Array::PopCount, PopCount);
	TestUnary <uint64_t> (Array::PopCount, PopCount);

	// Signed integer types
//	TestUnary <sint8_t> (Array::PopCount, PopCount);
//	TestUnary <sint16_t> (Array::PopCount, PopCount);
//	TestUnary <sint32_t> (Array::PopCount, PopCount);
//	TestUnary <sint64_t> (Array::PopCount, PopCount);

	// Other types
	TestUnary <size_t> (Array::PopCount, PopCount);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//      Bitwise NOT                                                           //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void TestNot (void) {

	// Show the stage info
	StageInfo ("Array::Not", BUFFER_SIZE, ROUNDS, TRIES);

	// Unsigned integer types
	TestUnary <uint8_t> (Array::Not, Not);
	TestUnary <uint16_t> (Array::Not, Not);
	TestUnary <uint32_t> (Array::Not, Not);
	TestUnary <uint64_t> (Array::Not, Not);

	// Signed integer types
	TestUnary <sint8_t> (Array::Not, Not);
	TestUnary <sint16_t> (Array::Not, Not);
	TestUnary <sint32_t> (Array::Not, Not);
	TestUnary <sint64_t> (Array::Not, Not);

	// Other types
	TestUnary <size_t> (Array::Not, Not);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//      Scalar bitwise AND                                                    //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void TestAndScalar (void) {

	// Show the stage info
	StageInfo ("Array::AndScalar", BUFFER_SIZE, ROUNDS, TRIES);

	// Unsigned integer types
	TestScalar <uint8_t> (Array::AndScalar, AndScalar);
	TestScalar <uint16_t> (Array::AndScalar, AndScalar);
	TestScalar <uint32_t> (Array::AndScalar, AndScalar);
	TestScalar <uint64_t> (Array::AndScalar, AndScalar);

	// Signed integer types
	TestScalar <sint8_t> (Array::AndScalar, AndScalar);
	TestScalar <sint16_t> (Array::AndScalar, AndScalar);
	TestScalar <sint32_t> (Array::AndScalar, AndScalar);
	TestScalar <sint64_t> (Array::AndScalar, AndScalar);

	// Other types
	TestScalar <size_t> (Array::AndScalar, AndScalar);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//      Vector bitwise AND                                                    //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void TestAndVector (void) {

	// Show the stage info
	StageInfo ("Array::AndVector", BUFFER_SIZE, ROUNDS, TRIES);

	// Unsigned integer types
	TestVector <uint8_t> (Array::AndVector, AndVector);
	TestVector <uint16_t> (Array::AndVector, AndVector);
	TestVector <uint32_t> (Array::AndVector, AndVector);
	TestVector <uint64_t> (Array::AndVector, AndVector);

	// Signed integer types
	TestVector <sint8_t> (Array::AndVector, AndVector);
	TestVector <sint16_t> (Array::AndVector, AndVector);
	TestVector <sint32_t> (Array::AndVector, AndVector);
	TestVector <sint64_t> (Array::AndVector, AndVector);

	// Other types
	TestVector <size_t> (Array::AndVector, AndVector);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//      Scalar bitwise OR                                                     //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void TestOrScalar (void) {

	// Show the stage info
	StageInfo ("Array::OrScalar", BUFFER_SIZE, ROUNDS, TRIES);

	// Unsigned integer types
	TestScalar <uint8_t> (Array::OrScalar, OrScalar);
	TestScalar <uint16_t> (Array::OrScalar, OrScalar);
	TestScalar <uint32_t> (Array::OrScalar, OrScalar);
	TestScalar <uint64_t> (Array::OrScalar, OrScalar);

	// Signed integer types
	TestScalar <sint8_t> (Array::OrScalar, OrScalar);
	TestScalar <sint16_t> (Array::OrScalar, OrScalar);
	TestScalar <sint32_t> (Array::OrScalar, OrScalar);
	TestScalar <sint64_t> (Array::OrScalar, OrScalar);

	// Other types
	TestScalar <size_t> (Array::OrScalar, OrScalar);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//      Vector bitwise OR                                                     //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void TestOrVector (void) {

	// Show the stage info
	StageInfo ("Array::OrVector", BUFFER_SIZE, ROUNDS, TRIES);

	// Unsigned integer types
	TestVector <uint8_t> (Array::OrVector, OrVector);
	TestVector <uint16_t> (Array::OrVector, OrVector);
	TestVector <uint32_t> (Array::OrVector, OrVector);
	TestVector <uint64_t> (Array::OrVector, OrVector);

	// Signed integer types
	TestVector <sint8_t> (Array::OrVector, OrVector);
	TestVector <sint16_t> (Array::OrVector, OrVector);
	TestVector <sint32_t> (Array::OrVector, OrVector);
	TestVector <sint64_t> (Array::OrVector, OrVector);

	// Other types
	TestVector <size_t> (Array::OrVector, OrVector);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//      Scalar bitwise XOR                                                    //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void TestXorScalar (void) {

	// Show the stage info
	StageInfo ("Array::XorScalar", BUFFER_SIZE, ROUNDS, TRIES);

	// Unsigned integer types
	TestScalar <uint8_t> (Array::XorScalar, XorScalar);
	TestScalar <uint16_t> (Array::XorScalar, XorScalar);
	TestScalar <uint32_t> (Array::XorScalar, XorScalar);
	TestScalar <uint64_t> (Array::XorScalar, XorScalar);

	// Signed integer types
	TestScalar <sint8_t> (Array::XorScalar, XorScalar);
	TestScalar <sint16_t> (Array::XorScalar, XorScalar);
	TestScalar <sint32_t> (Array::XorScalar, XorScalar);
	TestScalar <sint64_t> (Array::XorScalar, XorScalar);

	// Other types
	TestScalar <size_t> (Array::XorScalar, XorScalar);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//      Vector bitwise XOR                                                    //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void TestXorVector (void) {

	// Show the stage info
	StageInfo ("Array::XorVector", BUFFER_SIZE, ROUNDS, TRIES);

	// Unsigned integer types
	TestVector <uint8_t> (Array::XorVector, XorVector);
	TestVector <uint16_t> (Array::XorVector, XorVector);
	TestVector <uint32_t> (Array::XorVector, XorVector);
	TestVector <uint64_t> (Array::XorVector, XorVector);

	// Signed integer types
	TestVector <sint8_t> (Array::XorVector, XorVector);
	TestVector <sint16_t> (Array::XorVector, XorVector);
	TestVector <sint32_t> (Array::XorVector, XorVector);
	TestVector <sint64_t> (Array::XorVector, XorVector);

	// Other types
	TestVector <size_t> (Array::XorVector, XorVector);
}

//============================================================================//
//      Arithmetic operations                                                 //
//============================================================================//

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//      Negative value                                                        //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void TestNeg (void) {

	// Show the stage info
	StageInfo ("Array::Neg", BUFFER_SIZE, ROUNDS, TRIES);

	// Signed integer types
	TestUnary <sint8_t> (Array::Neg, Neg);
	TestUnary <sint16_t> (Array::Neg, Neg);
	TestUnary <sint32_t> (Array::Neg, Neg);
	TestUnary <sint64_t> (Array::Neg, Neg);

	// Floating-point types
	TestUnary <flt32_t> (Array::Neg, Neg);
	TestUnary <flt64_t> (Array::Neg, Neg);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//      Absolute value                                                        //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void TestAbs (void) {

	// Show the stage info
	StageInfo ("Array::Abs", BUFFER_SIZE, ROUNDS, TRIES);

	// Signed integer types
	TestUnary <sint8_t> (Array::Abs, Abs);
	TestUnary <sint16_t> (Array::Abs, Abs);
	TestUnary <sint32_t> (Array::Abs, Abs);
//	TestUnary <sint64_t> (Array::Abs, Abs);

	// Floating-point types
	TestUnary <flt32_t> (Array::Abs, Abs);
	TestUnary <flt64_t> (Array::Abs, Abs);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//      Negative absolute value                                               //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void TestNegAbs (void) {

	// Show the stage info
	StageInfo ("Array::NegAbs", BUFFER_SIZE, ROUNDS, TRIES);

	// Signed integer types
	TestUnary <sint8_t> (Array::NegAbs, NegAbs);
	TestUnary <sint16_t> (Array::NegAbs, NegAbs);
	TestUnary <sint32_t> (Array::NegAbs, NegAbs);
//	TestUnary <sint64_t> (Array::NegAbs, NegAbs);

	// Floating-point types
	TestUnary <flt32_t> (Array::NegAbs, NegAbs);
	TestUnary <flt64_t> (Array::NegAbs, NegAbs);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//      Number sign                                                           //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void TestSign (void) {

	// Show the stage info
	StageInfo ("Array::Sign", BUFFER_SIZE, ROUNDS, TRIES);

	// Signed integer types
	TestUnary <sint8_t> (Array::Sign, Sign);
	TestUnary <sint16_t> (Array::Sign, Sign);
	TestUnary <sint32_t> (Array::Sign, Sign);
	TestUnary <sint64_t> (Array::Sign, Sign);

	// Floating-point types
	TestUnary <flt32_t> (Array::Sign, Sign);
	TestUnary <flt64_t> (Array::Sign, Sign);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//      Square                                                                //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void TestSqr (void) {

	// Show the stage info
	StageInfo ("Array::Sqr", BUFFER_SIZE, ROUNDS, TRIES);

	// Floating-point types
	TestUnary <flt32_t> (Array::Sqr, Sqr);
	TestUnary <flt64_t> (Array::Sqr, Sqr);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//      Square root                                                           //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void TestSqrt (void) {

	// Show the stage info
	StageInfo ("Array::Sqrt", BUFFER_SIZE, ROUNDS, TRIES);

	// Floating-point types
	TestUnary <flt32_t> (Array::Sqrt, Sqrt);
	TestUnary <flt64_t> (Array::Sqrt, Sqrt);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//      Scalar addition                                                       //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void TestAddScalar (void) {

	// Show the stage info
	StageInfo ("Array::AddScalar", BUFFER_SIZE, ROUNDS, TRIES);

	// Unsigned integer types
	TestScalar <uint8_t> (Array::AddScalar, AddScalar);
	TestScalar <uint16_t> (Array::AddScalar, AddScalar);
	TestScalar <uint32_t> (Array::AddScalar, AddScalar);
	TestScalar <uint64_t> (Array::AddScalar, AddScalar);

	// Signed integer types
	TestScalar <sint8_t> (Array::AddScalar, AddScalar);
	TestScalar <sint16_t> (Array::AddScalar, AddScalar);
	TestScalar <sint32_t> (Array::AddScalar, AddScalar);
	TestScalar <sint64_t> (Array::AddScalar, AddScalar);

	// Floating-point types
	TestScalar <flt32_t> (Array::AddScalar, AddScalar);
	TestScalar <flt64_t> (Array::AddScalar, AddScalar);

	// Other types
	TestScalar <size_t> (Array::AddScalar, AddScalar);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//      Vector addition                                                       //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void TestAddVector (void) {

	// Show the stage info
	StageInfo ("Array::AddVector", BUFFER_SIZE, ROUNDS, TRIES);

	// Unsigned integer types
	TestVector <uint8_t> (Array::AddVector, AddVector);
	TestVector <uint16_t> (Array::AddVector, AddVector);
	TestVector <uint32_t> (Array::AddVector, AddVector);
	TestVector <uint64_t> (Array::AddVector, AddVector);

	// Signed integer types
	TestVector <sint8_t> (Array::AddVector, AddVector);
	TestVector <sint16_t> (Array::AddVector, AddVector);
	TestVector <sint32_t> (Array::AddVector, AddVector);
	TestVector <sint64_t> (Array::AddVector, AddVector);

	// Floating-point types
	TestVector <flt32_t> (Array::AddVector, AddVector);
	TestVector <flt64_t> (Array::AddVector, AddVector);

	// Other types
	TestVector <size_t> (Array::AddVector, AddVector);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//      Scalar subtraction                                                    //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void TestSubScalar (void) {

	// Show the stage info
	StageInfo ("Array::SubScalar", BUFFER_SIZE, ROUNDS, TRIES);

	// Unsigned integer types
	TestScalar <uint8_t> (Array::SubScalar, SubScalar);
	TestScalar <uint16_t> (Array::SubScalar, SubScalar);
	TestScalar <uint32_t> (Array::SubScalar, SubScalar);
	TestScalar <uint64_t> (Array::SubScalar, SubScalar);

	// Signed integer types
	TestScalar <sint8_t> (Array::SubScalar, SubScalar);
	TestScalar <sint16_t> (Array::SubScalar, SubScalar);
	TestScalar <sint32_t> (Array::SubScalar, SubScalar);
	TestScalar <sint64_t> (Array::SubScalar, SubScalar);

	// Floating-point types
	TestScalar <flt32_t> (Array::SubScalar, SubScalar);
	TestScalar <flt64_t> (Array::SubScalar, SubScalar);

	// Other types
	TestScalar <size_t> (Array::SubScalar, SubScalar);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//      Vector subtraction                                                    //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void TestSubVector (void) {

	// Show the stage info
	StageInfo ("Array::SubVector", BUFFER_SIZE, ROUNDS, TRIES);

	// Unsigned integer types
	TestVector <uint8_t> (Array::SubVector, SubVector);
	TestVector <uint16_t> (Array::SubVector, SubVector);
	TestVector <uint32_t> (Array::SubVector, SubVector);
	TestVector <uint64_t> (Array::SubVector, SubVector);

	// Signed integer types
	TestVector <sint8_t> (Array::SubVector, SubVector);
	TestVector <sint16_t> (Array::SubVector, SubVector);
	TestVector <sint32_t> (Array::SubVector, SubVector);
	TestVector <sint64_t> (Array::SubVector, SubVector);

	// Floating-point types
	TestVector <flt32_t> (Array::SubVector, SubVector);
	TestVector <flt64_t> (Array::SubVector, SubVector);

	// Other types
	TestVector <size_t> (Array::SubVector, SubVector);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//      Scalar reverse subtraction                                            //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void TestReverseSubScalar (void) {

	// Show the stage info
	StageInfo ("Array::ReverseSubScalar", BUFFER_SIZE, ROUNDS, TRIES);

	// Unsigned integer types
	TestScalar <uint8_t> (Array::ReverseSubScalar, ReverseSubScalar);
	TestScalar <uint16_t> (Array::ReverseSubScalar, ReverseSubScalar);
	TestScalar <uint32_t> (Array::ReverseSubScalar, ReverseSubScalar);
	TestScalar <uint64_t> (Array::ReverseSubScalar, ReverseSubScalar);

	// Signed integer types
	TestScalar <sint8_t> (Array::ReverseSubScalar, ReverseSubScalar);
	TestScalar <sint16_t> (Array::ReverseSubScalar, ReverseSubScalar);
	TestScalar <sint32_t> (Array::ReverseSubScalar, ReverseSubScalar);
	TestScalar <sint64_t> (Array::ReverseSubScalar, ReverseSubScalar);

	// Floating-point types
	TestScalar <flt32_t> (Array::ReverseSubScalar, ReverseSubScalar);
	TestScalar <flt64_t> (Array::ReverseSubScalar, ReverseSubScalar);

	// Other types
	TestScalar <size_t> (Array::ReverseSubScalar, ReverseSubScalar);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//      Vector reverse subtraction                                            //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void TestReverseSubVector (void) {

	// Show the stage info
	StageInfo ("Array::ReverseSubVector", BUFFER_SIZE, ROUNDS, TRIES);

	// Unsigned integer types
	TestVector <uint8_t> (Array::ReverseSubVector, ReverseSubVector);
	TestVector <uint16_t> (Array::ReverseSubVector, ReverseSubVector);
	TestVector <uint32_t> (Array::ReverseSubVector, ReverseSubVector);
	TestVector <uint64_t> (Array::ReverseSubVector, ReverseSubVector);

	// Signed integer types
	TestVector <sint8_t> (Array::ReverseSubVector, ReverseSubVector);
	TestVector <sint16_t> (Array::ReverseSubVector, ReverseSubVector);
	TestVector <sint32_t> (Array::ReverseSubVector, ReverseSubVector);
	TestVector <sint64_t> (Array::ReverseSubVector, ReverseSubVector);

	// Floating-point types
	TestVector <flt32_t> (Array::ReverseSubVector, ReverseSubVector);
	TestVector <flt64_t> (Array::ReverseSubVector, ReverseSubVector);

	// Other types
	TestVector <size_t> (Array::ReverseSubVector, ReverseSubVector);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//      Scalar multiplication                                                 //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void TestMulScalar (void) {

	// Show the stage info
	StageInfo ("Array::MulScalar", BUFFER_SIZE, ROUNDS, TRIES);

	// Floating-point types
	TestScalar <flt32_t> (Array::MulScalar, MulScalar);
	TestScalar <flt64_t> (Array::MulScalar, MulScalar);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//      Vector multiplication                                                 //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void TestMulVector (void) {

	// Show the stage info
	StageInfo ("Array::MulVector", BUFFER_SIZE, ROUNDS, TRIES);

	// Floating-point types
	TestVector <flt32_t> (Array::MulVector, MulVector);
	TestVector <flt64_t> (Array::MulVector, MulVector);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//      Scalar division                                                       //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void TestDivScalar (void) {

	// Show the stage info
	StageInfo ("Array::DivScalar", BUFFER_SIZE, ROUNDS, TRIES);

	// Floating-point types
	TestScalar <flt32_t> (Array::DivScalar, DivScalar);
	TestScalar <flt64_t> (Array::DivScalar, DivScalar);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//      Vector division                                                       //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void TestDivVector (void) {

	// Show the stage info
	StageInfo ("Array::DivVector", BUFFER_SIZE, ROUNDS, TRIES);

	// Floating-point types
	TestVector <flt32_t> (Array::DivVector, DivVector);
	TestVector <flt64_t> (Array::DivVector, DivVector);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//      Scalar reverse division                                               //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void TestReverseDivScalar (void) {

	// Show the stage info
	StageInfo ("Array::ReverseDivScalar", BUFFER_SIZE, ROUNDS, TRIES);

	// Floating-point types
	TestScalar <flt32_t> (Array::ReverseDivScalar, ReverseDivScalar);
	TestScalar <flt64_t> (Array::ReverseDivScalar, ReverseDivScalar);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//      Vector reverse division                                               //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void TestReverseDivVector (void) {

	// Show the stage info
	StageInfo ("Array::ReverseDivVector", BUFFER_SIZE, ROUNDS, TRIES);

	// Floating-point types
	TestVector <flt32_t> (Array::ReverseDivVector, ReverseDivVector);
	TestVector <flt64_t> (Array::ReverseDivVector, ReverseDivVector);
}

//============================================================================//
//      Fused arithmetic operations                                           //
//============================================================================//

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//      Fused addition                                                        //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void TestFusedAdd (void) {

	// Show the stage info
	StageInfo ("Array::FusedAdd", BUFFER_SIZE, ROUNDS, TRIES);

	// Floating-point types
	TestFused <flt32_t> (Array::FusedAdd, FusedAdd);
	TestFused <flt64_t> (Array::FusedAdd, FusedAdd);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//      Fused subtraction                                                     //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void TestFusedSub (void) {

	// Show the stage info
	StageInfo ("Array::FusedSub", BUFFER_SIZE, ROUNDS, TRIES);

	// Floating-point types
	TestFused <flt32_t> (Array::FusedSub, FusedSub);
	TestFused <flt64_t> (Array::FusedSub, FusedSub);
}

/*
################################################################################
#                                 END OF FILE                                  #
################################################################################
*/
