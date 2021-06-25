<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/*******************************************************************************
 *
 * Module Name: utnonansi - Non-ansi C library functions
 *
 ******************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"

#घोषणा _COMPONENT          ACPI_UTILITIES
ACPI_MODULE_NAME("utnonansi")

/*
 * Non-ANSI C library functions - strlwr, strupr, stricmp, and "safe"
 * string functions.
 */
/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_strlwr (strlwr)
 *
 * PARAMETERS:  src_string      - The source string to convert
 *
 * RETURN:      None
 *
 * DESCRIPTION: Convert a string to lowerहाल
 *
 ******************************************************************************/
व्योम acpi_ut_strlwr(अक्षर *src_string)
अणु
	अक्षर *string;

	ACPI_FUNCTION_ENTRY();

	अगर (!src_string) अणु
		वापस;
	पूर्ण

	/* Walk entire string, lowercasing the letters */

	क्रम (string = src_string; *string; string++) अणु
		*string = (अक्षर)छोटे((पूर्णांक)*string);
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_strupr (strupr)
 *
 * PARAMETERS:  src_string      - The source string to convert
 *
 * RETURN:      None
 *
 * DESCRIPTION: Convert a string to upperहाल
 *
 ******************************************************************************/

व्योम acpi_ut_strupr(अक्षर *src_string)
अणु
	अक्षर *string;

	ACPI_FUNCTION_ENTRY();

	अगर (!src_string) अणु
		वापस;
	पूर्ण

	/* Walk entire string, uppercasing the letters */

	क्रम (string = src_string; *string; string++) अणु
		*string = (अक्षर)बड़े((पूर्णांक)*string);
	पूर्ण
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_ut_stricmp (stricmp)
 *
 * PARAMETERS:  string1             - first string to compare
 *              string2             - second string to compare
 *
 * RETURN:      पूर्णांक that signअगरies string relationship. Zero means strings
 *              are equal.
 *
 * DESCRIPTION: Case-insensitive string compare. Implementation of the
 *              non-ANSI stricmp function.
 *
 ******************************************************************************/

पूर्णांक acpi_ut_stricmp(अक्षर *string1, अक्षर *string2)
अणु
	पूर्णांक c1;
	पूर्णांक c2;

	करो अणु
		c1 = छोटे((पूर्णांक)*string1);
		c2 = छोटे((पूर्णांक)*string2);

		string1++;
		string2++;
	पूर्ण
	जबतक ((c1 == c2) && (c1));

	वापस (c1 - c2);
पूर्ण

#अगर defined (ACPI_DEBUGGER) || defined (ACPI_APPLICATION) || defined (ACPI_DEBUG_OUTPUT)
/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_safe_म_नकल, acpi_ut_safe_म_जोड़ो, acpi_ut_safe_म_जोड़न
 *
 * PARAMETERS:  Adds a "DestSize" parameter to each of the standard string
 *              functions. This is the size of the Destination buffer.
 *
 * RETURN:      TRUE अगर the operation would overflow the destination buffer.
 *
 * DESCRIPTION: Safe versions of standard Clib string functions. Ensure that
 *              the result of the operation will not overflow the output string
 *              buffer.
 *
 * NOTE:        These functions are typically only helpful क्रम processing
 *              user input and command lines. For most ACPICA code, the
 *              required buffer length is precisely calculated beक्रमe buffer
 *              allocation, so the use of these functions is unnecessary.
 *
 ******************************************************************************/

u8 acpi_ut_safe_म_नकल(अक्षर *dest, acpi_size dest_size, अक्षर *source)
अणु

	अगर (म_माप(source) >= dest_size) अणु
		वापस (TRUE);
	पूर्ण

	म_नकल(dest, source);
	वापस (FALSE);
पूर्ण

u8 acpi_ut_safe_म_जोड़ो(अक्षर *dest, acpi_size dest_size, अक्षर *source)
अणु

	अगर ((म_माप(dest) + म_माप(source)) >= dest_size) अणु
		वापस (TRUE);
	पूर्ण

	म_जोड़ो(dest, source);
	वापस (FALSE);
पूर्ण

u8
acpi_ut_safe_म_जोड़न(अक्षर *dest,
		     acpi_size dest_size,
		     अक्षर *source, acpi_size max_transfer_length)
अणु
	acpi_size actual_transfer_length;

	actual_transfer_length = ACPI_MIN(max_transfer_length, म_माप(source));

	अगर ((म_माप(dest) + actual_transfer_length) >= dest_size) अणु
		वापस (TRUE);
	पूर्ण

	म_जोड़न(dest, source, max_transfer_length);
	वापस (FALSE);
पूर्ण

व्योम acpi_ut_safe_म_नकलन(अक्षर *dest, अक्षर *source, acpi_size dest_size)
अणु
	/* Always terminate destination string */

	म_नकलन(dest, source, dest_size);
	dest[dest_size - 1] = 0;
पूर्ण

#पूर्ण_अगर
