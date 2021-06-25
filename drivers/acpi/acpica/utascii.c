<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: utascii - Utility ascii functions
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_valid_nameseg
 *
 * PARAMETERS:  name            - The name or table signature to be examined.
 *                                Four अक्षरacters, करोes not have to be a
 *                                शून्य terminated string.
 *
 * RETURN:      TRUE अगर signature is has 4 valid ACPI अक्षरacters
 *
 * DESCRIPTION: Validate an ACPI table signature.
 *
 ******************************************************************************/

u8 acpi_ut_valid_nameseg(अक्षर *name)
अणु
	u32 i;

	/* Validate each अक्षरacter in the signature */

	क्रम (i = 0; i < ACPI_NAMESEG_SIZE; i++) अणु
		अगर (!acpi_ut_valid_name_अक्षर(name[i], i)) अणु
			वापस (FALSE);
		पूर्ण
	पूर्ण

	वापस (TRUE);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_valid_name_अक्षर
 *
 * PARAMETERS:  अक्षर            - The अक्षरacter to be examined
 *              position        - Byte position (0-3)
 *
 * RETURN:      TRUE अगर the अक्षरacter is valid, FALSE otherwise
 *
 * DESCRIPTION: Check क्रम a valid ACPI अक्षरacter. Must be one of:
 *              1) Upper हाल alpha
 *              2) numeric
 *              3) underscore
 *
 *              We allow a '!' as the last अक्षरacter because of the ASF! table
 *
 ******************************************************************************/

u8 acpi_ut_valid_name_अक्षर(अक्षर अक्षरacter, u32 position)
अणु

	अगर (!((अक्षरacter >= 'A' && character <= 'Z') ||
	      (अक्षरacter >= '0' && character <= '9') || (character == '_'))) अणु

		/* Allow a '!' in the last position */

		अगर (अक्षरacter == '!' && position == 3) अणु
			वापस (TRUE);
		पूर्ण

		वापस (FALSE);
	पूर्ण

	वापस (TRUE);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_check_and_repair_ascii
 *
 * PARAMETERS:  name                - Ascii string
 *              count               - Number of अक्षरacters to check
 *
 * RETURN:      None
 *
 * DESCRIPTION: Ensure that the requested number of अक्षरacters are prपूर्णांकable
 *              Ascii अक्षरacters. Sets non-prपूर्णांकable and null अक्षरs to <space>.
 *
 ******************************************************************************/

व्योम acpi_ut_check_and_repair_ascii(u8 *name, अक्षर *repaired_name, u32 count)
अणु
	u32 i;

	क्रम (i = 0; i < count; i++) अणु
		repaired_name[i] = (अक्षर)name[i];

		अगर (!name[i]) अणु
			वापस;
		पूर्ण
		अगर (!है_छाप(name[i])) अणु
			repaired_name[i] = ' ';
		पूर्ण
	पूर्ण
पूर्ण
