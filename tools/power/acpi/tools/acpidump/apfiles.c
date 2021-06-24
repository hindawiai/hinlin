<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: apfiles - File-related functions क्रम acpidump utility
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश "acpidump.h"

/* Local prototypes */

अटल पूर्णांक ap_is_existing_file(अक्षर *pathname);

/******************************************************************************
 *
 * FUNCTION:    ap_is_existing_file
 *
 * PARAMETERS:  pathname            - Output filename
 *
 * RETURN:      0 on success
 *
 * DESCRIPTION: Query क्रम file overग_लिखो अगर it alपढ़ोy exists.
 *
 ******************************************************************************/

अटल पूर्णांक ap_is_existing_file(अक्षर *pathname)
अणु
#अगर !defined(_GNU_EFI) && !defined(_EDK2_EFI)
	काष्ठा stat stat_info;
	पूर्णांक in_अक्षर;

	अगर (!stat(pathname, &stat_info)) अणु
		ख_लिखो(मानक_त्रुटि,
			"Target path already exists, overwrite? [y|n] ");

		in_अक्षर = ख_अक्षर_लो(मानक_निवेश);
		अगर (in_अक्षर == '\n') अणु
			in_अक्षर = ख_अक्षर_लो(मानक_निवेश);
		पूर्ण

		अगर (in_अक्षर != 'y' && in_char != 'Y') अणु
			वापस (-1);
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	वापस (0);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    ap_खोलो_output_file
 *
 * PARAMETERS:  pathname            - Output filename
 *
 * RETURN:      Open file handle
 *
 * DESCRIPTION: Open a text output file क्रम acpidump. Checks अगर file alपढ़ोy
 *              exists.
 *
 ******************************************************************************/

पूर्णांक ap_खोलो_output_file(अक्षर *pathname)
अणु
	ACPI_खाता file;

	/* If file exists, prompt क्रम overग_लिखो */

	अगर (ap_is_existing_file(pathname) != 0) अणु
		वापस (-1);
	पूर्ण

	/* Poपूर्णांक मानक_निकास to the file */

	file = ख_खोलो(pathname, "w");
	अगर (!file) अणु
		ख_लिखो(मानक_त्रुटि, "Could not open output file: %s\n", pathname);
		वापस (-1);
	पूर्ण

	/* Save the file and path */

	gbl_output_file = file;
	gbl_output_filename = pathname;
	वापस (0);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    ap_ग_लिखो_to_binary_file
 *
 * PARAMETERS:  table               - ACPI table to be written
 *              instance            - ACPI table instance no. to be written
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Write an ACPI table to a binary file. Builds the output
 *              filename from the table signature.
 *
 ******************************************************************************/

पूर्णांक ap_ग_लिखो_to_binary_file(काष्ठा acpi_table_header *table, u32 instance)
अणु
	अक्षर filename[ACPI_NAMESEG_SIZE + 16];
	अक्षर instance_str[16];
	ACPI_खाता file;
	acpi_size actual;
	u32 table_length;

	/* Obtain table length */

	table_length = ap_get_table_length(table);

	/* Conकाष्ठा lower-हाल filename from the table local signature */

	अगर (ACPI_VALIDATE_RSDP_SIG(table->signature)) अणु
		ACPI_COPY_NAMESEG(filename, ACPI_RSDP_NAME);
	पूर्ण अन्यथा अणु
		ACPI_COPY_NAMESEG(filename, table->signature);
	पूर्ण

	filename[0] = (अक्षर)छोटे((पूर्णांक)filename[0]);
	filename[1] = (अक्षर)छोटे((पूर्णांक)filename[1]);
	filename[2] = (अक्षर)छोटे((पूर्णांक)filename[2]);
	filename[3] = (अक्षर)छोटे((पूर्णांक)filename[3]);
	filename[ACPI_NAMESEG_SIZE] = 0;

	/* Handle multiple SSDts - create dअगरferent filenames क्रम each */

	अगर (instance > 0) अणु
		snम_लिखो(instance_str, माप(instance_str), "%u", instance);
		म_जोड़ो(filename, instance_str);
	पूर्ण

	म_जोड़ो(filename, खाता_SUFFIX_BINARY_TABLE);

	अगर (gbl_verbose_mode) अणु
		ख_लिखो(मानक_त्रुटि,
			"Writing [%4.4s] to binary file: %s 0x%X (%u) bytes\n",
			table->signature, filename, table->length,
			table->length);
	पूर्ण

	/* Open the file and dump the entire table in binary mode */

	file = ख_खोलो(filename, "wb");
	अगर (!file) अणु
		ख_लिखो(मानक_त्रुटि, "Could not open output file: %s\n", filename);
		वापस (-1);
	पूर्ण

	actual = ख_डालो(table, 1, table_length, file);
	अगर (actual != table_length) अणु
		ख_लिखो(मानक_त्रुटि, "Error writing binary output file: %s\n",
			filename);
		ख_बंद(file);
		वापस (-1);
	पूर्ण

	ख_बंद(file);
	वापस (0);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    ap_get_table_from_file
 *
 * PARAMETERS:  pathname            - File containing the binary ACPI table
 *              out_file_size       - Where the file size is वापसed
 *
 * RETURN:      Buffer containing the ACPI table. शून्य on error.
 *
 * DESCRIPTION: Open a file and पढ़ो it entirely पूर्णांकo a new buffer
 *
 ******************************************************************************/

काष्ठा acpi_table_header *ap_get_table_from_file(अक्षर *pathname,
						 u32 *out_file_size)
अणु
	काष्ठा acpi_table_header *buffer = शून्य;
	ACPI_खाता file;
	u32 file_size;
	acpi_size actual;

	/* Must use binary mode */

	file = ख_खोलो(pathname, "rb");
	अगर (!file) अणु
		ख_लिखो(मानक_त्रुटि, "Could not open input file: %s\n", pathname);
		वापस (शून्य);
	पूर्ण

	/* Need file size to allocate a buffer */

	file_size = cm_get_file_size(file);
	अगर (file_size == ACPI_UINT32_MAX) अणु
		ख_लिखो(मानक_त्रुटि,
			"Could not get input file size: %s\n", pathname);
		जाओ cleanup;
	पूर्ण

	/* Allocate a buffer क्रम the entire file */

	buffer = ACPI_ALLOCATE_ZEROED(file_size);
	अगर (!buffer) अणु
		ख_लिखो(मानक_त्रुटि,
			"Could not allocate file buffer of size: %u\n",
			file_size);
		जाओ cleanup;
	पूर्ण

	/* Read the entire file */

	actual = ख_पढ़ो(buffer, 1, file_size, file);
	अगर (actual != file_size) अणु
		ख_लिखो(मानक_त्रुटि, "Could not read input file: %s\n", pathname);
		ACPI_FREE(buffer);
		buffer = शून्य;
		जाओ cleanup;
	पूर्ण

	*out_file_size = file_size;

cleanup:
	ख_बंद(file);
	वापस (buffer);
पूर्ण
