<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: cmfsize - Common get file size function
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acapps.h"

#घोषणा _COMPONENT          ACPI_TOOLS
ACPI_MODULE_NAME("cmfsize")

/*******************************************************************************
 *
 * FUNCTION:    cm_get_file_size
 *
 * PARAMETERS:  file                    - Open file descriptor
 *
 * RETURN:      File Size. On error, -1 (ACPI_UINT32_MAX)
 *
 * DESCRIPTION: Get the size of a file. Uses seek-to-खातापूर्ण. File must be खोलो.
 *              Does not disturb the current file poपूर्णांकer.
 *
 ******************************************************************************/
u32 cm_get_file_size(ACPI_खाता file)
अणु
	दीर्घ file_size;
	दीर्घ current_offset;
	acpi_status status;

	/* Save the current file poपूर्णांकer, seek to खातापूर्ण to obtain file size */

	current_offset = ख_बताओ(file);
	अगर (current_offset < 0) अणु
		जाओ offset_error;
	पूर्ण

	status = ख_जाओ(file, 0, अंत_से);
	अगर (ACPI_FAILURE(status)) अणु
		जाओ seek_error;
	पूर्ण

	file_size = ख_बताओ(file);
	अगर (file_size < 0) अणु
		जाओ offset_error;
	पूर्ण

	/* Restore original file poपूर्णांकer */

	status = ख_जाओ(file, current_offset, शुरू_से);
	अगर (ACPI_FAILURE(status)) अणु
		जाओ seek_error;
	पूर्ण

	वापस ((u32)file_size);

offset_error:
	ख_लिखो(मानक_त्रुटि, "Could not get file offset\n");
	वापस (ACPI_UINT32_MAX);

seek_error:
	ख_लिखो(मानक_त्रुटि, "Could not set file offset\n");
	वापस (ACPI_UINT32_MAX);
पूर्ण
