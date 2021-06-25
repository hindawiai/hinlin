<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/*******************************************************************************
 *
 * Module Name: utstring - Common functions क्रम strings and अक्षरacters
 *
 ******************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acnamesp.h"

#घोषणा _COMPONENT          ACPI_UTILITIES
ACPI_MODULE_NAME("utstring")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_prपूर्णांक_string
 *
 * PARAMETERS:  string          - Null terminated ASCII string
 *              max_length      - Maximum output length. Used to स्थिरrain the
 *                                length of strings during debug output only.
 *
 * RETURN:      None
 *
 * DESCRIPTION: Dump an ASCII string with support क्रम ACPI-defined escape
 *              sequences.
 *
 ******************************************************************************/
व्योम acpi_ut_prपूर्णांक_string(अक्षर *string, u16 max_length)
अणु
	u32 i;

	अगर (!string) अणु
		acpi_os_म_लिखो("<\"NULL STRING PTR\">");
		वापस;
	पूर्ण

	acpi_os_म_लिखो("\"");
	क्रम (i = 0; (i < max_length) && string[i]; i++) अणु

		/* Escape sequences */

		चयन (string[i]) अणु
		हाल 0x07:

			acpi_os_म_लिखो("\\a");	/* BELL */
			अवरोध;

		हाल 0x08:

			acpi_os_म_लिखो("\\b");	/* BACKSPACE */
			अवरोध;

		हाल 0x0C:

			acpi_os_म_लिखो("\\f");	/* FORMFEED */
			अवरोध;

		हाल 0x0A:

			acpi_os_म_लिखो("\\n");	/* LINEFEED */
			अवरोध;

		हाल 0x0D:

			acpi_os_म_लिखो("\\r");	/* CARRIAGE RETURN */
			अवरोध;

		हाल 0x09:

			acpi_os_म_लिखो("\\t");	/* HORIZONTAL TAB */
			अवरोध;

		हाल 0x0B:

			acpi_os_म_लिखो("\\v");	/* VERTICAL TAB */
			अवरोध;

		हाल '\'':	/* Single Quote */
		हाल '\"':	/* Double Quote */
		हाल '\\':	/* Backslash */

			acpi_os_म_लिखो("\\%c", (पूर्णांक)string[i]);
			अवरोध;

		शेष:

			/* Check क्रम prपूर्णांकable अक्षरacter or hex escape */

			अगर (है_छाप((पूर्णांक)string[i])) अणु
				/* This is a normal अक्षरacter */

				acpi_os_म_लिखो("%c", (पूर्णांक)string[i]);
			पूर्ण अन्यथा अणु
				/* All others will be Hex escapes */

				acpi_os_म_लिखो("\\x%2.2X", (s32)string[i]);
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	acpi_os_म_लिखो("\"");

	अगर (i == max_length && string[i]) अणु
		acpi_os_म_लिखो("...");
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_repair_name
 *
 * PARAMETERS:  name            - The ACPI name to be repaired
 *
 * RETURN:      Repaired version of the name
 *
 * DESCRIPTION: Repair an ACPI name: Change invalid अक्षरacters to '*' and
 *              वापस the new name. NOTE: the Name parameter must reside in
 *              पढ़ो/ग_लिखो memory, cannot be a स्थिर.
 *
 * An ACPI Name must consist of valid ACPI अक्षरacters. We will repair the name
 * अगर necessary because we करोn't want to पात because of this, but we want
 * all namespace names to be prपूर्णांकable. A warning message is appropriate.
 *
 * This issue came up because there are in fact machines that exhibit
 * this problem, and we want to be able to enable ACPI support क्रम them,
 * even though there are a few bad names.
 *
 ******************************************************************************/

व्योम acpi_ut_repair_name(अक्षर *name)
अणु
	u32 i;
	u8 found_bad_अक्षर = FALSE;
	u32 original_name;

	ACPI_FUNCTION_NAME(ut_repair_name);

	/*
	 * Special हाल क्रम the root node. This can happen अगर we get an
	 * error during the execution of module-level code.
	 */
	अगर (ACPI_COMPARE_NAMESEG(name, ACPI_ROOT_PATHNAME)) अणु
		वापस;
	पूर्ण

	ACPI_COPY_NAMESEG(&original_name, name);

	/* Check each अक्षरacter in the name */

	क्रम (i = 0; i < ACPI_NAMESEG_SIZE; i++) अणु
		अगर (acpi_ut_valid_name_अक्षर(name[i], i)) अणु
			जारी;
		पूर्ण

		/*
		 * Replace a bad अक्षरacter with something prपूर्णांकable, yet technically
		 * still invalid. This prevents any collisions with existing "good"
		 * names in the namespace.
		 */
		name[i] = '*';
		found_bad_अक्षर = TRUE;
	पूर्ण

	अगर (found_bad_अक्षर) अणु

		/* Report warning only अगर in strict mode or debug mode */

		अगर (!acpi_gbl_enable_पूर्णांकerpreter_slack) अणु
			ACPI_WARNING((AE_INFO,
				      "Invalid character(s) in name (0x%.8X), repaired: [%4.4s]",
				      original_name, name));
		पूर्ण अन्यथा अणु
			ACPI_DEBUG_PRINT((ACPI_DB_INFO,
					  "Invalid character(s) in name (0x%.8X), repaired: [%4.4s]",
					  original_name, name));
		पूर्ण
	पूर्ण
पूर्ण

#अगर defined ACPI_ASL_COMPILER || defined ACPI_EXEC_APP
/*******************************************************************************
 *
 * FUNCTION:    ut_convert_backslashes
 *
 * PARAMETERS:  pathname        - File pathname string to be converted
 *
 * RETURN:      Modअगरies the input Pathname
 *
 * DESCRIPTION: Convert all backslashes (0x5C) to क्रमward slashes (0x2F) within
 *              the entire input file pathname string.
 *
 ******************************************************************************/

व्योम ut_convert_backslashes(अक्षर *pathname)
अणु

	अगर (!pathname) अणु
		वापस;
	पूर्ण

	जबतक (*pathname) अणु
		अगर (*pathname == '\\') अणु
			*pathname = '/';
		पूर्ण

		pathname++;
	पूर्ण
पूर्ण
#पूर्ण_अगर
