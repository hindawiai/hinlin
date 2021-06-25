<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: uthex -- Hex/ASCII support functions
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"

#घोषणा _COMPONENT          ACPI_COMPILER
ACPI_MODULE_NAME("uthex")

/* Hex to ASCII conversion table */
अटल स्थिर अक्षर acpi_gbl_hex_to_ascii[] = अणु
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D',
	    'E', 'F'
पूर्ण;

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_hex_to_ascii_अक्षर
 *
 * PARAMETERS:  पूर्णांकeger             - Contains the hex digit
 *              position            - bit position of the digit within the
 *                                    पूर्णांकeger (multiple of 4)
 *
 * RETURN:      The converted Ascii अक्षरacter
 *
 * DESCRIPTION: Convert a hex digit to an Ascii अक्षरacter
 *
 ******************************************************************************/

अक्षर acpi_ut_hex_to_ascii_अक्षर(u64 पूर्णांकeger, u32 position)
अणु
	u64 index;

	acpi_ut_लघु_shअगरt_right(पूर्णांकeger, position, &index);
	वापस (acpi_gbl_hex_to_ascii[index & 0xF]);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_ascii_to_hex_byte
 *
 * PARAMETERS:  two_ascii_अक्षरs             - Poपूर्णांकer to two ASCII अक्षरacters
 *              वापस_byte                 - Where converted byte is वापसed
 *
 * RETURN:      Status and converted hex byte
 *
 * DESCRIPTION: Perक्रमm ascii-to-hex translation, exactly two ASCII अक्षरacters
 *              to a single converted byte value.
 *
 ******************************************************************************/

acpi_status acpi_ut_ascii_to_hex_byte(अक्षर *two_ascii_अक्षरs, u8 *वापस_byte)
अणु

	/* Both ASCII अक्षरacters must be valid hex digits */

	अगर (!है_षष्ठादशक((पूर्णांक)two_ascii_अक्षरs[0]) ||
	    !है_षष्ठादशक((पूर्णांक)two_ascii_अक्षरs[1])) अणु
		वापस (AE_BAD_HEX_CONSTANT);
	पूर्ण

	*वापस_byte =
	    acpi_ut_ascii_अक्षर_to_hex(two_ascii_अक्षरs[1]) |
	    (acpi_ut_ascii_अक्षर_to_hex(two_ascii_अक्षरs[0]) << 4);

	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_ascii_अक्षर_to_hex
 *
 * PARAMETERS:  hex_अक्षर                - Hex अक्षरacter in Ascii. Must be:
 *                                        0-9 or A-F or a-f
 *
 * RETURN:      The binary value of the ascii/hex अक्षरacter
 *
 * DESCRIPTION: Perक्रमm ascii-to-hex translation
 *
 ******************************************************************************/

u8 acpi_ut_ascii_अक्षर_to_hex(पूर्णांक hex_अक्षर)
अणु

	/* Values 0-9 */

	अगर (hex_अक्षर <= '9') अणु
		वापस ((u8)(hex_अक्षर - '0'));
	पूर्ण

	/* Upper हाल A-F */

	अगर (hex_अक्षर <= 'F') अणु
		वापस ((u8)(hex_अक्षर - 0x37));
	पूर्ण

	/* Lower हाल a-f */

	वापस ((u8)(hex_अक्षर - 0x57));
पूर्ण
