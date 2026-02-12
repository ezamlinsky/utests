/*
################################################################################
# Encoding: UTF-8                                                  Tab size: 4 #
#                                                                              #
#                  COMMON FUNCTIONS FOR THE ARRAY UNIT TESTS                   #
#                                                                              #
# Ordnung muss sein!                             Copyleft (Ɔ) Eugene Zamlinsky #
################################################################################
*/
# pragma	once
# define	BUFFER_SIZE		10000	// Size of the data buffer
# define	SEED			100		// Seed value for the random number generator
# define	ROUNDS			100		// Test rounds
# define	TRIES			3		// Tries in each round
# define	EPSILON			1.0e-4	// Epsilon for the compare function
# define	MAX_VALUE		10		// Max generated random value

using namespace std;

//****************************************************************************//
//      Show a summary (stage information) of the job we are doing            //
//****************************************************************************//
void StageInfo (
	const string &name,
	size_t size,
	size_t rounds,
	size_t tries
){
	// Show a summary (stage information) of the job we are doing now
	cout << "    Applying '\e[1m\e[32m" << name;
	cout << "\e[0m' to a " << size << "-long array in " << rounds << " rounds with ";
	cout << tries << " tries in each" << endl;
}

//****************************************************************************//
//      Test a scalar function                                                //
//****************************************************************************//
template <typename T>
void TestScalar (
	void (*func)(T array[], size_t size, T value),
	void (*ref)(T array[], size_t size, T value)
){
	// Create an array the target size
	RandomArray <T> array (BUFFER_SIZE, SEED, MAX_VALUE);

	// Run the test in many rounds with random offset and elements count
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
			func (array.Data() + offset, count, value);
			ref (reference.Data() + offset, count, value);

			// Compare arrays for different elements
			array.Compare (reference, EPSILON);
		}
	}
}

//****************************************************************************//
//      Test a vector function                                                //
//****************************************************************************//
template <typename T>
void TestVector (
	void (*func)(T target[], const T source[], size_t size),
	void (*ref)(T target[], const T source[], size_t size)
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
			func (target.Data() + toffset, source.Data() + soffset, count);
			ref (treference.Data() + toffset, sreference.Data() + soffset, count);

			// Compare arrays for different elements
			target.Compare (treference, EPSILON);
			source.Compare (sreference, EPSILON);
		}
	}
}

/*
################################################################################
#                                 END OF FILE                                  #
################################################################################
*/
