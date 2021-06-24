<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/*******************************************************************************
 *
 * Module Name: utम_से_अदीर्घ64 - String-to-पूर्णांकeger conversion support क्रम both
 *                            64-bit and 32-bit पूर्णांकegers
 *
 ******************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"

#घोषणा _COMPONENT          ACPI_UTILITIES
ACPI_MODULE_NAME("utstrtoul64")

/*******************************************************************************
 *
 * This module contains the top-level string to 64/32-bit अचिन्हित पूर्णांकeger
 * conversion functions:
 *
 *  1) A standard म_से_अदीर्घ() function that supports 64-bit पूर्णांकegers, base
 *     8/10/16, with पूर्णांकeger overflow support. This is used मुख्यly by the
 *     iASL compiler, which implements tighter स्थिरraपूर्णांकs on पूर्णांकeger
 *     स्थिरants than the runसमय (पूर्णांकerpreter) पूर्णांकeger-to-string conversions.
 *  2) Runसमय "Explicit conversion" as defined in the ACPI specअगरication.
 *  3) Runसमय "Implicit conversion" as defined in the ACPI specअगरication.
 *
 * Current users of this module:
 *
 *  iASL        - Preprocessor (स्थिरants and math expressions)
 *  iASL        - Main parser, conversion of स्थिरants to पूर्णांकegers
 *  iASL        - Data Table Compiler parser (स्थिरants and math expressions)
 *  पूर्णांकerpreter - Implicit and explicit conversions, GPE method names
 *  पूर्णांकerpreter - Repair code क्रम वापस values from predefined names
 *  debugger    - Command line input string conversion
 *  acpi_dump   - ACPI table physical addresses
 *  acpi_exec   - Support क्रम namespace overrides
 *
 * Notes concerning users of these पूर्णांकerfaces:
 *
 * acpi_gbl_पूर्णांकeger_byte_width is used to set the 32/64 bit limit क्रम explicit
 * and implicit conversions. This global must be set to the proper width.
 * For the core ACPICA code, the width depends on the DSDT version. For the
 * acpi_ut_म_से_अदीर्घ64 पूर्णांकerface, all conversions are 64 bits. This पूर्णांकerface is
 * used primarily क्रम iASL, where the शेष width is 64 bits क्रम all parsers,
 * but error checking is perक्रमmed later to flag हालs where a 64-bit स्थिरant
 * is wrongly defined in a 32-bit DSDT/SSDT.
 *
 * In ACPI, the only place where octal numbers are supported is within
 * the ASL language itself. This is implemented via the मुख्य acpi_ut_म_से_अदीर्घ64
 * पूर्णांकerface. According the ACPI specअगरication, there is no ACPI runसमय
 * support (explicit/implicit) क्रम octal string conversions.
 *
 ******************************************************************************/
/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_म_से_अदीर्घ64
 *
 * PARAMETERS:  string                  - Null terminated input string,
 *                                        must be a valid poपूर्णांकer
 *              वापस_value            - Where the converted पूर्णांकeger is
 *                                        वापसed. Must be a valid poपूर्णांकer
 *
 * RETURN:      Status and converted पूर्णांकeger. Returns an exception on a
 *              64-bit numeric overflow
 *
 * DESCRIPTION: Convert a string पूर्णांकo an अचिन्हित पूर्णांकeger. Always perक्रमms a
 *              full 64-bit conversion, regardless of the current global
 *              पूर्णांकeger width. Supports Decimal, Hex, and Octal strings.
 *
 * Current users of this function:
 *
 *  iASL        - Preprocessor (स्थिरants and math expressions)
 *  iASL        - Main ASL parser, conversion of ASL स्थिरants to पूर्णांकegers
 *  iASL        - Data Table Compiler parser (स्थिरants and math expressions)
 *  पूर्णांकerpreter - Repair code क्रम वापस values from predefined names
 *  acpi_dump   - ACPI table physical addresses
 *  acpi_exec   - Support क्रम namespace overrides
 *
 ******************************************************************************/
acpi_status acpi_ut_म_से_अदीर्घ64(अक्षर *string, u64 *वापस_value)
अणु
	acpi_status status = AE_OK;
	u8 original_bit_width;
	u32 base = 10;		/* Default is decimal */

	ACPI_FUNCTION_TRACE_STR(ut_म_से_अदीर्घ64, string);

	*वापस_value = 0;

	/* A शून्य वापस string वापसs a value of zero */

	अगर (*string == 0) अणु
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	अगर (!acpi_ut_हटाओ_whitespace(&string)) अणु
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	/*
	 * 1) Check क्रम a hex स्थिरant. A "0x" prefix indicates base 16.
	 */
	अगर (acpi_ut_detect_hex_prefix(&string)) अणु
		base = 16;
	पूर्ण

	/*
	 * 2) Check क्रम an octal स्थिरant, defined to be a leading zero
	 * followed by sequence of octal digits (0-7)
	 */
	अन्यथा अगर (acpi_ut_detect_octal_prefix(&string)) अणु
		base = 8;
	पूर्ण

	अगर (!acpi_ut_हटाओ_leading_zeros(&string)) अणु
		वापस_ACPI_STATUS(AE_OK);	/* Return value 0 */
	पूर्ण

	/*
	 * Force a full 64-bit conversion. The caller (usually iASL) must
	 * check क्रम a 32-bit overflow later as necessary (If current mode
	 * is 32-bit, meaning a 32-bit DSDT).
	 */
	original_bit_width = acpi_gbl_पूर्णांकeger_bit_width;
	acpi_gbl_पूर्णांकeger_bit_width = 64;

	/*
	 * Perक्रमm the base 8, 10, or 16 conversion. A 64-bit numeric overflow
	 * will वापस an exception (to allow iASL to flag the statement).
	 */
	चयन (base) अणु
	हाल 8:
		status = acpi_ut_convert_octal_string(string, वापस_value);
		अवरोध;

	हाल 10:
		status = acpi_ut_convert_decimal_string(string, वापस_value);
		अवरोध;

	हाल 16:
	शेष:
		status = acpi_ut_convert_hex_string(string, वापस_value);
		अवरोध;
	पूर्ण

	/* Only possible exception from above is a 64-bit overflow */

	acpi_gbl_पूर्णांकeger_bit_width = original_bit_width;
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_implicit_म_से_अदीर्घ64
 *
 * PARAMETERS:  string                  - Null terminated input string,
 *                                        must be a valid poपूर्णांकer
 *
 * RETURN:      Converted पूर्णांकeger
 *
 * DESCRIPTION: Perक्रमm a 64-bit conversion with restrictions placed upon
 *              an "implicit conversion" by the ACPI specअगरication. Used by
 *              many ASL चालकs that require an पूर्णांकeger opeअक्रम, and support
 *              an स्वतःmatic (implicit) conversion from a string opeअक्रम
 *              to the final पूर्णांकeger opeअक्रम. The major restriction is that
 *              only hex strings are supported.
 *
 * -----------------------------------------------------------------------------
 *
 * Base is always 16, either with or without the 0x prefix. Decimal and
 * Octal strings are not supported, as per the ACPI specअगरication.
 *
 * Examples (both are hex values):
 *      Add ("BA98", Arg0, Local0)
 *      Subtract ("0x12345678", Arg1, Local1)
 *
 * Conversion rules as extracted from the ACPI specअगरication:
 *
 *  The converted पूर्णांकeger is initialized to the value zero.
 *  The ASCII string is always पूर्णांकerpreted as a hexadecimal स्थिरant.
 *
 *  1)  According to the ACPI specअगरication, a "0x" prefix is not allowed.
 *      However, ACPICA allows this as an ACPI extension on general
 *      principle. (NO ERROR)
 *
 *  2)  The conversion terminates when the size of an पूर्णांकeger is reached
 *      (32 or 64 bits). There are no numeric overflow conditions. (NO ERROR)
 *
 *  3)  The first non-hex अक्षरacter terminates the conversion and वापसs
 *      the current accumulated value of the converted पूर्णांकeger (NO ERROR).
 *
 *  4)  Conversion of a null (zero-length) string to an पूर्णांकeger is
 *      technically not allowed. However, ACPICA allows this as an ACPI
 *      extension. The conversion वापसs the value 0. (NO ERROR)
 *
 * NOTE: There are no error conditions वापसed by this function. At
 * the minimum, a value of zero is वापसed.
 *
 * Current users of this function:
 *
 *  पूर्णांकerpreter - All runसमय implicit conversions, as per ACPI specअगरication
 *  iASL        - Data Table Compiler parser (स्थिरants and math expressions)
 *
 ******************************************************************************/

u64 acpi_ut_implicit_म_से_अदीर्घ64(अक्षर *string)
अणु
	u64 converted_पूर्णांकeger = 0;

	ACPI_FUNCTION_TRACE_STR(ut_implicit_म_से_अदीर्घ64, string);

	अगर (!acpi_ut_हटाओ_whitespace(&string)) अणु
		वापस_VALUE(0);
	पूर्ण

	/*
	 * Per the ACPI specअगरication, only hexadecimal is supported क्रम
	 * implicit conversions, and the "0x" prefix is "not allowed".
	 * However, allow a "0x" prefix as an ACPI extension.
	 */
	acpi_ut_हटाओ_hex_prefix(&string);

	अगर (!acpi_ut_हटाओ_leading_zeros(&string)) अणु
		वापस_VALUE(0);
	पूर्ण

	/*
	 * Ignore overflow as per the ACPI specअगरication. This is implemented by
	 * ignoring the वापस status from the conversion function called below.
	 * On overflow, the input string is simply truncated.
	 */
	acpi_ut_convert_hex_string(string, &converted_पूर्णांकeger);
	वापस_VALUE(converted_पूर्णांकeger);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_explicit_म_से_अदीर्घ64
 *
 * PARAMETERS:  string                  - Null terminated input string,
 *                                        must be a valid poपूर्णांकer
 *
 * RETURN:      Converted पूर्णांकeger
 *
 * DESCRIPTION: Perक्रमm a 64-bit conversion with the restrictions placed upon
 *              an "explicit conversion" by the ACPI specअगरication. The
 *              मुख्य restriction is that only hex and decimal are supported.
 *
 * -----------------------------------------------------------------------------
 *
 * Base is either 10 (शेष) or 16 (with 0x prefix). Octal (base 8) strings
 * are not supported, as per the ACPI specअगरication.
 *
 * Examples:
 *      to_पूर्णांकeger ("1000")     Decimal
 *      to_पूर्णांकeger ("0xABCD")   Hex
 *
 * Conversion rules as extracted from the ACPI specअगरication:
 *
 *  1)  The input string is either a decimal or hexadecimal numeric string.
 *      A hex value must be prefixed by "0x" or it is पूर्णांकerpreted as decimal.
 *
 *  2)  The value must not exceed the maximum of an पूर्णांकeger value
 *      (32 or 64 bits). The ACPI specअगरication states the behavior is
 *      "unpredictable", so ACPICA matches the behavior of the implicit
 *      conversion हाल. There are no numeric overflow conditions. (NO ERROR)
 *
 *  3)  Behavior on the first non-hex अक्षरacter is not defined by the ACPI
 *      specअगरication (क्रम the to_पूर्णांकeger चालक), so ACPICA matches the
 *      behavior of the implicit conversion हाल. It terminates the
 *      conversion and वापसs the current accumulated value of the converted
 *      पूर्णांकeger. (NO ERROR)
 *
 *  4)  Conversion of a null (zero-length) string to an पूर्णांकeger is
 *      technically not allowed. However, ACPICA allows this as an ACPI
 *      extension. The conversion वापसs the value 0. (NO ERROR)
 *
 * NOTE: There are no error conditions वापसed by this function. At the
 * minimum, a value of zero is वापसed.
 *
 * Current users of this function:
 *
 *  पूर्णांकerpreter - Runसमय ASL to_पूर्णांकeger चालक, as per the ACPI specअगरication
 *
 ******************************************************************************/

u64 acpi_ut_explicit_म_से_अदीर्घ64(अक्षर *string)
अणु
	u64 converted_पूर्णांकeger = 0;
	u32 base = 10;		/* Default is decimal */

	ACPI_FUNCTION_TRACE_STR(ut_explicit_म_से_अदीर्घ64, string);

	अगर (!acpi_ut_हटाओ_whitespace(&string)) अणु
		वापस_VALUE(0);
	पूर्ण

	/*
	 * Only Hex and Decimal are supported, as per the ACPI specअगरication.
	 * A "0x" prefix indicates hex; otherwise decimal is assumed.
	 */
	अगर (acpi_ut_detect_hex_prefix(&string)) अणु
		base = 16;
	पूर्ण

	अगर (!acpi_ut_हटाओ_leading_zeros(&string)) अणु
		वापस_VALUE(0);
	पूर्ण

	/*
	 * Ignore overflow as per the ACPI specअगरication. This is implemented by
	 * ignoring the वापस status from the conversion functions called below.
	 * On overflow, the input string is simply truncated.
	 */
	चयन (base) अणु
	हाल 10:
	शेष:
		acpi_ut_convert_decimal_string(string, &converted_पूर्णांकeger);
		अवरोध;

	हाल 16:
		acpi_ut_convert_hex_string(string, &converted_पूर्णांकeger);
		अवरोध;
	पूर्ण

	वापस_VALUE(converted_पूर्णांकeger);
पूर्ण
