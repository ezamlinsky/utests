/*
################################################################################
# Encoding: UTF-8                                                  Tab size: 4 #
#                                                                              #
#                UNIT TESTS FOR ARRAY DATA CONVERSION FUNCTIONS                #
#                                                                              #
# Ordnung muss sein!                             Copyleft (Ɔ) Eugene Zamlinsky #
################################################################################
*/
# pragma	once

//****************************************************************************//
//      Reference implementation of the functions                             //
//****************************************************************************//
# define	REF1(fname, ttype, stype)											\
void fname (ttype target[], const stype source[], size_t size){					\
	for (size_t i = 0; i < size; ++i)											\
		target[i] = source[i];													\
}
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
# define	REF2(fname, ttype, stype)											\
void fname (ttype target[], const stype source[], size_t size){					\
	for (size_t i = 0; i < size; ++i)											\
		target[i] = rint (source[i]);											\
}

//============================================================================//
//      Extension to wider signed integer types                               //
//============================================================================//

// Extend sint8_t to sint16_t
REF1 (ExtendToSint16, sint16_t, sint8_t)

// Extend uint8_t to sint16_t
REF1 (ExtendToSint16, sint16_t, uint8_t)

// Extend sint8_t to sint32_t
REF1 (ExtendToSint32, sint32_t, sint8_t)

// Extend uint8_t to sint32_t
REF1 (ExtendToSint32, sint32_t, uint8_t)

// Extend sint16_t to sint32_t
REF1 (ExtendToSint32, sint32_t, sint16_t)

// Extend uint16_t to sint32_t
REF1 (ExtendToSint32, sint32_t, uint16_t)

// Extend sint8_t to sint64_t
REF1 (ExtendToSint64, sint64_t, sint8_t)

// Extend uint8_t to sint64_t
REF1 (ExtendToSint64, sint64_t, uint8_t)

// Extend sint16_t to sint64_t
REF1 (ExtendToSint64, sint64_t, sint16_t)

// Extend uint16_t to sint64_t
REF1 (ExtendToSint64, sint64_t, uint16_t)

// Extend sint32_t to sint64_t
REF1 (ExtendToSint64, sint64_t, sint32_t)

// Extend uint32_t to sint64_t
REF1 (ExtendToSint64, sint64_t, uint32_t)

//============================================================================//
//      Conversion between floating-point types                               //
//============================================================================//

// Convert flt64_t to flt32_t
REF1 (ConvertToFlt32, flt32_t, flt64_t)

// Convert flt32_t to flt64_t
REF1 (ConvertToFlt64, flt64_t, flt32_t)

//============================================================================//
//      Conversion from signed integer types to floating-point types          //
//============================================================================//

// Convert sint32_t to flt32_t
REF1 (ConvertToFlt32, flt32_t, sint32_t)

// Convert sint64_t to flt32_t
REF1 (ConvertToFlt32, flt32_t, sint64_t)

// Convert sint32_t to flt64_t
REF1 (ConvertToFlt64, flt64_t, sint32_t)

// Convert sint64_t to flt64_t
REF1 (ConvertToFlt64, flt64_t, sint64_t)

//============================================================================//
//      Conversion from floating-point types to signed integer types          //
//============================================================================//

// Convert flt32_t to sint32_t
REF2 (ConvertToSint32, sint32_t, flt32_t)

// Truncate flt64_t to sint32_t
REF2 (ConvertToSint32, sint32_t, flt64_t)

// Truncate flt32_t to sint64_t
REF2 (ConvertToSint64, sint64_t, flt32_t)

// Truncate flt64_t to sint64_t
REF2 (ConvertToSint64, sint64_t, flt64_t)

//============================================================================//
//      Truncating from floating-point types to signed integer types          //
//============================================================================//

// Truncate flt32_t to sint32_t
REF1 (TruncateToSint32, sint32_t, flt32_t)

// Truncate flt64_t to sint32_t
REF1 (TruncateToSint32, sint32_t, flt64_t)

// Truncate flt32_t to sint64_t
REF1 (TruncateToSint64, sint64_t, flt32_t)

// Truncate flt64_t to sint64_t
REF1 (TruncateToSint64, sint64_t, flt64_t)

//****************************************************************************//
//      Unit test routine                                                     //
//****************************************************************************//
void TestConvert (void) {

	// Show the stage info
	StageInfo ("Array::Convert", BUFFER_SIZE, ROUNDS, TRIES);

	// Extension to wider signed integer types
	TestConvert <sint16_t, sint8_t> (Array::ExtendToSint16, ExtendToSint16);
	TestConvert <sint16_t, uint8_t> (Array::ExtendToSint16, ExtendToSint16);
	TestConvert <sint32_t, sint8_t> (Array::ExtendToSint32, ExtendToSint32);
	TestConvert <sint32_t, uint8_t> (Array::ExtendToSint32, ExtendToSint32);
	TestConvert <sint32_t, sint16_t> (Array::ExtendToSint32, ExtendToSint32);
	TestConvert <sint32_t, uint16_t> (Array::ExtendToSint32, ExtendToSint32);
	TestConvert <sint64_t, sint8_t> (Array::ExtendToSint64, ExtendToSint64);
	TestConvert <sint64_t, uint8_t> (Array::ExtendToSint64, ExtendToSint64);
	TestConvert <sint64_t, sint16_t> (Array::ExtendToSint64, ExtendToSint64);
	TestConvert <sint64_t, uint16_t> (Array::ExtendToSint64, ExtendToSint64);
	TestConvert <sint64_t, sint32_t> (Array::ExtendToSint64, ExtendToSint64);
	TestConvert <sint64_t, uint32_t> (Array::ExtendToSint64, ExtendToSint64);

	// Conversion between floating-point types
	TestConvert <flt32_t, flt64_t> (Array::ConvertToFlt32, ConvertToFlt32);
	TestConvert <flt64_t, flt32_t> (Array::ConvertToFlt64, ConvertToFlt64);

	// Conversion from signed integer types to floating-point types
	TestConvert <flt32_t, sint32_t> (Array::ConvertToFlt32, ConvertToFlt32);
//	TestConvert <flt32_t, sint64_t> (Array::ConvertToFlt32, ConvertToFlt32);
	TestConvert <flt64_t, sint32_t> (Array::ConvertToFlt64, ConvertToFlt64);
//	TestConvert <flt64_t, sint64_t> (Array::ConvertToFlt64, ConvertToFlt64);

	// Conversion from floating-point types to signed integer types
	TestConvert <sint32_t, flt32_t> (Array::ConvertToSint32, ConvertToSint32);
	TestConvert <sint32_t, flt64_t> (Array::ConvertToSint32, ConvertToSint32);
//	TestConvert <sint64_t, flt32_t> (Array::ConvertToSint64, ConvertToSint64);
//	TestConvert <sint64_t, flt64_t> (Array::ConvertToSint64, ConvertToSint64);

	// Truncating from floating-point types to signed integer types
	TestConvert <sint32_t, flt32_t> (Array::TruncateToSint32, TruncateToSint32);
	TestConvert <sint32_t, flt64_t> (Array::TruncateToSint32, TruncateToSint32);
//	TestConvert <sint64_t, flt32_t> (Array::TruncateToSint64, TruncateToSint64);
//	TestConvert <sint64_t, flt64_t> (Array::TruncateToSint64, TruncateToSint64);
}
/*
################################################################################
#                                 END OF FILE                                  #
################################################################################
*/
