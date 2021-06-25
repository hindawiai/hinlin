<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: utbuffer - Buffer dump routines
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"

#घोषणा _COMPONENT          ACPI_UTILITIES
ACPI_MODULE_NAME("utbuffer")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_dump_buffer
 *
 * PARAMETERS:  buffer              - Buffer to dump
 *              count               - Amount to dump, in bytes
 *              display             - BYTE, WORD, DWORD, or QWORD display:
 *                                      DB_BYTE_DISPLAY
 *                                      DB_WORD_DISPLAY
 *                                      DB_DWORD_DISPLAY
 *                                      DB_QWORD_DISPLAY
 *              base_offset         - Beginning buffer offset (display only)
 *
 * RETURN:      None
 *
 * DESCRIPTION: Generic dump buffer in both hex and ascii.
 *
 ******************************************************************************/
व्योम acpi_ut_dump_buffer(u8 *buffer, u32 count, u32 display, u32 base_offset)
अणु
	u32 i = 0;
	u32 j;
	u32 temp32;
	u8 buf_अक्षर;
	u32 display_data_only = display & DB_DISPLAY_DATA_ONLY;

	display &= ~DB_DISPLAY_DATA_ONLY;
	अगर (!buffer) अणु
		acpi_os_म_लिखो("Null Buffer Pointer in DumpBuffer!\n");
		वापस;
	पूर्ण

	अगर ((count < 4) || (count & 0x01)) अणु
		display = DB_BYTE_DISPLAY;
	पूर्ण

	/* Nasty little dump buffer routine! */

	जबतक (i < count) अणु

		/* Prपूर्णांक current offset */

		अगर (!display_data_only) अणु
			acpi_os_म_लिखो("%8.4X: ", (base_offset + i));
		पूर्ण

		/* Prपूर्णांक 16 hex अक्षरs */

		क्रम (j = 0; j < 16;) अणु
			अगर (i + j >= count) अणु

				/* Dump fill spaces */

				acpi_os_म_लिखो("%*s", ((display * 2) + 1), " ");
				j += display;
				जारी;
			पूर्ण

			चयन (display) अणु
			हाल DB_BYTE_DISPLAY:
			शेष:	/* Default is BYTE display */

				acpi_os_म_लिखो("%02X ",
					       buffer[(acpi_size)i + j]);
				अवरोध;

			हाल DB_WORD_DISPLAY:

				ACPI_MOVE_16_TO_32(&temp32,
						   &buffer[(acpi_size)i + j]);
				acpi_os_म_लिखो("%04X ", temp32);
				अवरोध;

			हाल DB_DWORD_DISPLAY:

				ACPI_MOVE_32_TO_32(&temp32,
						   &buffer[(acpi_size)i + j]);
				acpi_os_म_लिखो("%08X ", temp32);
				अवरोध;

			हाल DB_QWORD_DISPLAY:

				ACPI_MOVE_32_TO_32(&temp32,
						   &buffer[(acpi_size)i + j]);
				acpi_os_म_लिखो("%08X", temp32);

				ACPI_MOVE_32_TO_32(&temp32,
						   &buffer[(acpi_size)i + j +
							   4]);
				acpi_os_म_लिखो("%08X ", temp32);
				अवरोध;
			पूर्ण

			j += display;
		पूर्ण

		/*
		 * Prपूर्णांक the ASCII equivalent अक्षरacters but watch out क्रम the bad
		 * unprपूर्णांकable ones (prपूर्णांकable अक्षरs are 0x20 through 0x7E)
		 */
		अगर (!display_data_only) अणु
			acpi_os_म_लिखो(" ");
			क्रम (j = 0; j < 16; j++) अणु
				अगर (i + j >= count) अणु
					acpi_os_म_लिखो("\n");
					वापस;
				पूर्ण

				/*
				 * Add comment अक्षरacters so rest of line is ignored when
				 * compiled
				 */
				अगर (j == 0) अणु
					acpi_os_म_लिखो("// ");
				पूर्ण

				buf_अक्षर = buffer[(acpi_size)i + j];
				अगर (है_छाप(buf_अक्षर)) अणु
					acpi_os_म_लिखो("%c", buf_अक्षर);
				पूर्ण अन्यथा अणु
					acpi_os_म_लिखो(".");
				पूर्ण
			पूर्ण

			/* Done with that line. */

			acpi_os_म_लिखो("\n");
		पूर्ण
		i += 16;
	पूर्ण

	वापस;
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_debug_dump_buffer
 *
 * PARAMETERS:  buffer              - Buffer to dump
 *              count               - Amount to dump, in bytes
 *              display             - BYTE, WORD, DWORD, or QWORD display:
 *                                      DB_BYTE_DISPLAY
 *                                      DB_WORD_DISPLAY
 *                                      DB_DWORD_DISPLAY
 *                                      DB_QWORD_DISPLAY
 *              component_ID        - Caller's component ID
 *
 * RETURN:      None
 *
 * DESCRIPTION: Generic dump buffer in both hex and ascii.
 *
 ******************************************************************************/

व्योम
acpi_ut_debug_dump_buffer(u8 *buffer, u32 count, u32 display, u32 component_id)
अणु

	/* Only dump the buffer अगर tracing is enabled */

	अगर (!((ACPI_LV_TABLES & acpi_dbg_level) &&
	      (component_id & acpi_dbg_layer))) अणु
		वापस;
	पूर्ण

	acpi_ut_dump_buffer(buffer, count, display, 0);
पूर्ण

#अगर_घोषित ACPI_APPLICATION
/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_dump_buffer_to_file
 *
 * PARAMETERS:  file                - File descriptor
 *              buffer              - Buffer to dump
 *              count               - Amount to dump, in bytes
 *              display             - BYTE, WORD, DWORD, or QWORD display:
 *                                      DB_BYTE_DISPLAY
 *                                      DB_WORD_DISPLAY
 *                                      DB_DWORD_DISPLAY
 *                                      DB_QWORD_DISPLAY
 *              base_offset         - Beginning buffer offset (display only)
 *
 * RETURN:      None
 *
 * DESCRIPTION: Generic dump buffer in both hex and ascii to a file.
 *
 ******************************************************************************/

व्योम
acpi_ut_dump_buffer_to_file(ACPI_खाता file,
			    u8 *buffer, u32 count, u32 display, u32 base_offset)
अणु
	u32 i = 0;
	u32 j;
	u32 temp32;
	u8 buf_अक्षर;

	अगर (!buffer) अणु
		ख_लिखो(file, "Null Buffer Pointer in DumpBuffer!\n");
		वापस;
	पूर्ण

	अगर ((count < 4) || (count & 0x01)) अणु
		display = DB_BYTE_DISPLAY;
	पूर्ण

	/* Nasty little dump buffer routine! */

	जबतक (i < count) अणु

		/* Prपूर्णांक current offset */

		ख_लिखो(file, "%8.4X: ", (base_offset + i));

		/* Prपूर्णांक 16 hex अक्षरs */

		क्रम (j = 0; j < 16;) अणु
			अगर (i + j >= count) अणु

				/* Dump fill spaces */

				ख_लिखो(file, "%*s", ((display * 2) + 1), " ");
				j += display;
				जारी;
			पूर्ण

			चयन (display) अणु
			हाल DB_BYTE_DISPLAY:
			शेष:	/* Default is BYTE display */

				ख_लिखो(file, "%02X ",
					buffer[(acpi_size)i + j]);
				अवरोध;

			हाल DB_WORD_DISPLAY:

				ACPI_MOVE_16_TO_32(&temp32,
						   &buffer[(acpi_size)i + j]);
				ख_लिखो(file, "%04X ", temp32);
				अवरोध;

			हाल DB_DWORD_DISPLAY:

				ACPI_MOVE_32_TO_32(&temp32,
						   &buffer[(acpi_size)i + j]);
				ख_लिखो(file, "%08X ", temp32);
				अवरोध;

			हाल DB_QWORD_DISPLAY:

				ACPI_MOVE_32_TO_32(&temp32,
						   &buffer[(acpi_size)i + j]);
				ख_लिखो(file, "%08X", temp32);

				ACPI_MOVE_32_TO_32(&temp32,
						   &buffer[(acpi_size)i + j +
							   4]);
				ख_लिखो(file, "%08X ", temp32);
				अवरोध;
			पूर्ण

			j += display;
		पूर्ण

		/*
		 * Prपूर्णांक the ASCII equivalent अक्षरacters but watch out क्रम the bad
		 * unprपूर्णांकable ones (prपूर्णांकable अक्षरs are 0x20 through 0x7E)
		 */
		ख_लिखो(file, " ");
		क्रम (j = 0; j < 16; j++) अणु
			अगर (i + j >= count) अणु
				ख_लिखो(file, "\n");
				वापस;
			पूर्ण

			buf_अक्षर = buffer[(acpi_size)i + j];
			अगर (है_छाप(buf_अक्षर)) अणु
				ख_लिखो(file, "%c", buf_अक्षर);
			पूर्ण अन्यथा अणु
				ख_लिखो(file, ".");
			पूर्ण
		पूर्ण

		/* Done with that line. */

		ख_लिखो(file, "\n");
		i += 16;
	पूर्ण

	वापस;
पूर्ण
#पूर्ण_अगर
