<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/*******************************************************************************
 *
 * Module Name: utstrsuppt - Support functions क्रम string-to-पूर्णांकeger conversion
 *
 ******************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"

#घोषणा _COMPONENT          ACPI_UTILITIES
ACPI_MODULE_NAME("utstrsuppt")

/* Local prototypes */
अटल acpi_status
acpi_ut_insert_digit(u64 *accumulated_value, u32 base, पूर्णांक ascii_digit);

अटल acpi_status
acpi_ut_म_से_अदीर्घ_multiply64(u64 multiplicand, u32 base, u64 *out_product);

अटल acpi_status acpi_ut_म_से_अदीर्घ_add64(u64 addend1, u32 digit, u64 *out_sum);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_convert_octal_string
 *
 * PARAMETERS:  string                  - Null terminated input string
 *              वापस_value_ptr        - Where the converted value is वापसed
 *
 * RETURN:      Status and 64-bit converted पूर्णांकeger
 *
 * DESCRIPTION: Perक्रमms a base 8 conversion of the input string to an
 *              पूर्णांकeger value, either 32 or 64 bits.
 *
 * NOTE:        Maximum 64-bit अचिन्हित octal value is 01777777777777777777777
 *              Maximum 32-bit अचिन्हित octal value is 037777777777
 *
 ******************************************************************************/

acpi_status acpi_ut_convert_octal_string(अक्षर *string, u64 *वापस_value_ptr)
अणु
	u64 accumulated_value = 0;
	acpi_status status = AE_OK;

	/* Convert each ASCII byte in the input string */

	जबतक (*string) अणु
		/*
		 * Character must be ASCII 0-7, otherwise:
		 * 1) Runसमय: terminate with no error, per the ACPI spec
		 * 2) Compiler: वापस an error
		 */
		अगर (!(ACPI_IS_OCTAL_DIGIT(*string))) अणु
#अगर_घोषित ACPI_ASL_COMPILER
			status = AE_BAD_OCTAL_CONSTANT;
#पूर्ण_अगर
			अवरोध;
		पूर्ण

		/* Convert and insert this octal digit पूर्णांकo the accumulator */

		status = acpi_ut_insert_digit(&accumulated_value, 8, *string);
		अगर (ACPI_FAILURE(status)) अणु
			status = AE_OCTAL_OVERFLOW;
			अवरोध;
		पूर्ण

		string++;
	पूर्ण

	/* Always वापस the value that has been accumulated */

	*वापस_value_ptr = accumulated_value;
	वापस (status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_convert_decimal_string
 *
 * PARAMETERS:  string                  - Null terminated input string
 *              वापस_value_ptr        - Where the converted value is वापसed
 *
 * RETURN:      Status and 64-bit converted पूर्णांकeger
 *
 * DESCRIPTION: Perक्रमms a base 10 conversion of the input string to an
 *              पूर्णांकeger value, either 32 or 64 bits.
 *
 * NOTE:        Maximum 64-bit अचिन्हित decimal value is 18446744073709551615
 *              Maximum 32-bit अचिन्हित decimal value is 4294967295
 *
 ******************************************************************************/

acpi_status acpi_ut_convert_decimal_string(अक्षर *string, u64 *वापस_value_ptr)
अणु
	u64 accumulated_value = 0;
	acpi_status status = AE_OK;

	/* Convert each ASCII byte in the input string */

	जबतक (*string) अणु
		/*
		 * Character must be ASCII 0-9, otherwise:
		 * 1) Runसमय: terminate with no error, per the ACPI spec
		 * 2) Compiler: वापस an error
		 */
		अगर (!है_अंक((पूर्णांक)*string)) अणु
#अगर_घोषित ACPI_ASL_COMPILER
			status = AE_BAD_DECIMAL_CONSTANT;
#पूर्ण_अगर
			अवरोध;
		पूर्ण

		/* Convert and insert this decimal digit पूर्णांकo the accumulator */

		status = acpi_ut_insert_digit(&accumulated_value, 10, *string);
		अगर (ACPI_FAILURE(status)) अणु
			status = AE_DECIMAL_OVERFLOW;
			अवरोध;
		पूर्ण

		string++;
	पूर्ण

	/* Always वापस the value that has been accumulated */

	*वापस_value_ptr = accumulated_value;
	वापस (status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_convert_hex_string
 *
 * PARAMETERS:  string                  - Null terminated input string
 *              वापस_value_ptr        - Where the converted value is वापसed
 *
 * RETURN:      Status and 64-bit converted पूर्णांकeger
 *
 * DESCRIPTION: Perक्रमms a base 16 conversion of the input string to an
 *              पूर्णांकeger value, either 32 or 64 bits.
 *
 * NOTE:        Maximum 64-bit अचिन्हित hex value is 0xFFFFFFFFFFFFFFFF
 *              Maximum 32-bit अचिन्हित hex value is 0xFFFFFFFF
 *
 ******************************************************************************/

acpi_status acpi_ut_convert_hex_string(अक्षर *string, u64 *वापस_value_ptr)
अणु
	u64 accumulated_value = 0;
	acpi_status status = AE_OK;

	/* Convert each ASCII byte in the input string */

	जबतक (*string) अणु
		/*
		 * Character must be ASCII A-F, a-f, or 0-9, otherwise:
		 * 1) Runसमय: terminate with no error, per the ACPI spec
		 * 2) Compiler: वापस an error
		 */
		अगर (!है_षष्ठादशक((पूर्णांक)*string)) अणु
#अगर_घोषित ACPI_ASL_COMPILER
			status = AE_BAD_HEX_CONSTANT;
#पूर्ण_अगर
			अवरोध;
		पूर्ण

		/* Convert and insert this hex digit पूर्णांकo the accumulator */

		status = acpi_ut_insert_digit(&accumulated_value, 16, *string);
		अगर (ACPI_FAILURE(status)) अणु
			status = AE_HEX_OVERFLOW;
			अवरोध;
		पूर्ण

		string++;
	पूर्ण

	/* Always वापस the value that has been accumulated */

	*वापस_value_ptr = accumulated_value;
	वापस (status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_हटाओ_leading_zeros
 *
 * PARAMETERS:  string                  - Poपूर्णांकer to input ASCII string
 *
 * RETURN:      Next अक्षरacter after any leading zeros. This अक्षरacter may be
 *              used by the caller to detect end-of-string.
 *
 * DESCRIPTION: Remove any leading zeros in the input string. Return the
 *              next अक्षरacter after the final ASCII zero to enable the caller
 *              to check क्रम the end of the string (शून्य terminator).
 *
 ******************************************************************************/

अक्षर acpi_ut_हटाओ_leading_zeros(अक्षर **string)
अणु

	जबतक (**string == ACPI_ASCII_ZERO) अणु
		*string += 1;
	पूर्ण

	वापस (**string);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_हटाओ_whitespace
 *
 * PARAMETERS:  string                  - Poपूर्णांकer to input ASCII string
 *
 * RETURN:      Next अक्षरacter after any whitespace. This अक्षरacter may be
 *              used by the caller to detect end-of-string.
 *
 * DESCRIPTION: Remove any leading whitespace in the input string. Return the
 *              next अक्षरacter after the final ASCII zero to enable the caller
 *              to check क्रम the end of the string (शून्य terminator).
 *
 ******************************************************************************/

अक्षर acpi_ut_हटाओ_whitespace(अक्षर **string)
अणु

	जबतक (है_खाली((u8)**string)) अणु
		*string += 1;
	पूर्ण

	वापस (**string);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_detect_hex_prefix
 *
 * PARAMETERS:  string                  - Poपूर्णांकer to input ASCII string
 *
 * RETURN:      TRUE अगर a "0x" prefix was found at the start of the string
 *
 * DESCRIPTION: Detect and हटाओ a hex "0x" prefix
 *
 ******************************************************************************/

u8 acpi_ut_detect_hex_prefix(अक्षर **string)
अणु
	अक्षर *initial_position = *string;

	acpi_ut_हटाओ_hex_prefix(string);
	अगर (*string != initial_position) अणु
		वापस (TRUE);	/* String is past leading 0x */
	पूर्ण

	वापस (FALSE);		/* Not a hex string */
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_हटाओ_hex_prefix
 *
 * PARAMETERS:  string                  - Poपूर्णांकer to input ASCII string
 *
 * RETURN:      none
 *
 * DESCRIPTION: Remove a hex "0x" prefix
 *
 ******************************************************************************/

व्योम acpi_ut_हटाओ_hex_prefix(अक्षर **string)
अणु
	अगर ((**string == ACPI_ASCII_ZERO) &&
	    (छोटे((पूर्णांक)*(*string + 1)) == 'x')) अणु
		*string += 2;	/* Go past the leading 0x */
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_detect_octal_prefix
 *
 * PARAMETERS:  string                  - Poपूर्णांकer to input ASCII string
 *
 * RETURN:      True अगर an octal "0" prefix was found at the start of the
 *              string
 *
 * DESCRIPTION: Detect and हटाओ an octal prefix (zero)
 *
 ******************************************************************************/

u8 acpi_ut_detect_octal_prefix(अक्षर **string)
अणु

	अगर (**string == ACPI_ASCII_ZERO) अणु
		*string += 1;	/* Go past the leading 0 */
		वापस (TRUE);
	पूर्ण

	वापस (FALSE);		/* Not an octal string */
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_insert_digit
 *
 * PARAMETERS:  accumulated_value       - Current value of the पूर्णांकeger value
 *                                        accumulator. The new value is
 *                                        वापसed here.
 *              base                    - Radix, either 8/10/16
 *              ascii_digit             - ASCII single digit to be inserted
 *
 * RETURN:      Status and result of the convert/insert operation. The only
 *              possible वापसed exception code is numeric overflow of
 *              either the multiply or add conversion operations.
 *
 * DESCRIPTION: Generic conversion and insertion function क्रम all bases:
 *
 *              1) Multiply the current accumulated/converted value by the
 *              base in order to make room क्रम the new अक्षरacter.
 *
 *              2) Convert the new अक्षरacter to binary and add it to the
 *              current accumulated value.
 *
 *              Note: The only possible exception indicates an पूर्णांकeger
 *              overflow (AE_NUMERIC_OVERFLOW)
 *
 ******************************************************************************/

अटल acpi_status
acpi_ut_insert_digit(u64 *accumulated_value, u32 base, पूर्णांक ascii_digit)
अणु
	acpi_status status;
	u64 product;

	/* Make room in the accumulated value क्रम the incoming digit */

	status = acpi_ut_म_से_अदीर्घ_multiply64(*accumulated_value, base, &product);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	/* Add in the new digit, and store the sum to the accumulated value */

	status =
	    acpi_ut_म_से_अदीर्घ_add64(product,
				  acpi_ut_ascii_अक्षर_to_hex(ascii_digit),
				  accumulated_value);

	वापस (status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_म_से_अदीर्घ_multiply64
 *
 * PARAMETERS:  multiplicand            - Current accumulated converted पूर्णांकeger
 *              base                    - Base/Radix
 *              out_product             - Where the product is वापसed
 *
 * RETURN:      Status and 64-bit product
 *
 * DESCRIPTION: Multiply two 64-bit values, with checking क्रम 64-bit overflow as
 *              well as 32-bit overflow अगर necessary (अगर the current global
 *              पूर्णांकeger width is 32).
 *
 ******************************************************************************/

अटल acpi_status
acpi_ut_म_से_अदीर्घ_multiply64(u64 multiplicand, u32 base, u64 *out_product)
अणु
	u64 product;
	u64 quotient;

	/* Exit अगर either opeअक्रम is zero */

	*out_product = 0;
	अगर (!multiplicand || !base) अणु
		वापस (AE_OK);
	पूर्ण

	/*
	 * Check क्रम 64-bit overflow beक्रमe the actual multiplication.
	 *
	 * Notes: 64-bit भागision is often not supported on 32-bit platक्रमms
	 * (it requires a library function), Thereक्रमe ACPICA has a local
	 * 64-bit भागide function. Also, Multiplier is currently only used
	 * as the radix (8/10/16), to the 64/32 भागide will always work.
	 */
	acpi_ut_लघु_भागide(ACPI_UINT64_MAX, base, &quotient, शून्य);
	अगर (multiplicand > quotient) अणु
		वापस (AE_NUMERIC_OVERFLOW);
	पूर्ण

	product = multiplicand * base;

	/* Check क्रम 32-bit overflow अगर necessary */

	अगर ((acpi_gbl_पूर्णांकeger_bit_width == 32) && (product > ACPI_UINT32_MAX)) अणु
		वापस (AE_NUMERIC_OVERFLOW);
	पूर्ण

	*out_product = product;
	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_म_से_अदीर्घ_add64
 *
 * PARAMETERS:  addend1                 - Current accumulated converted पूर्णांकeger
 *              digit                   - New hex value/अक्षर
 *              out_sum                 - Where sum is वापसed (Accumulator)
 *
 * RETURN:      Status and 64-bit sum
 *
 * DESCRIPTION: Add two 64-bit values, with checking क्रम 64-bit overflow as
 *              well as 32-bit overflow अगर necessary (अगर the current global
 *              पूर्णांकeger width is 32).
 *
 ******************************************************************************/

अटल acpi_status acpi_ut_म_से_अदीर्घ_add64(u64 addend1, u32 digit, u64 *out_sum)
अणु
	u64 sum;

	/* Check क्रम 64-bit overflow beक्रमe the actual addition */

	अगर ((addend1 > 0) && (digit > (ACPI_UINT64_MAX - addend1))) अणु
		वापस (AE_NUMERIC_OVERFLOW);
	पूर्ण

	sum = addend1 + digit;

	/* Check क्रम 32-bit overflow अगर necessary */

	अगर ((acpi_gbl_पूर्णांकeger_bit_width == 32) && (sum > ACPI_UINT32_MAX)) अणु
		वापस (AE_NUMERIC_OVERFLOW);
	पूर्ण

	*out_sum = sum;
	वापस (AE_OK);
पूर्ण
