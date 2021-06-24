<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: apdump - Dump routines क्रम ACPI tables (acpidump)
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश "acpidump.h"

/* Local prototypes */

अटल पूर्णांक
ap_dump_table_buffer(काष्ठा acpi_table_header *table,
		     u32 instance, acpi_physical_address address);

/******************************************************************************
 *
 * FUNCTION:    ap_is_valid_header
 *
 * PARAMETERS:  table               - Poपूर्णांकer to table to be validated
 *
 * RETURN:      TRUE अगर the header appears to be valid. FALSE otherwise
 *
 * DESCRIPTION: Check क्रम a valid ACPI table header
 *
 ******************************************************************************/

u8 ap_is_valid_header(काष्ठा acpi_table_header *table)
अणु

	अगर (!ACPI_VALIDATE_RSDP_SIG(table->signature)) अणु

		/* Make sure signature is all ASCII and a valid ACPI name */

		अगर (!acpi_ut_valid_nameseg(table->signature)) अणु
			ख_लिखो(मानक_त्रुटि,
				"Table signature (0x%8.8X) is invalid\n",
				*(u32 *)table->signature);
			वापस (FALSE);
		पूर्ण

		/* Check क्रम minimum table length */

		अगर (table->length < माप(काष्ठा acpi_table_header)) अणु
			ख_लिखो(मानक_त्रुटि, "Table length (0x%8.8X) is invalid\n",
				table->length);
			वापस (FALSE);
		पूर्ण
	पूर्ण

	वापस (TRUE);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    ap_is_valid_checksum
 *
 * PARAMETERS:  table               - Poपूर्णांकer to table to be validated
 *
 * RETURN:      TRUE अगर the checksum appears to be valid. FALSE otherwise.
 *
 * DESCRIPTION: Check क्रम a valid ACPI table checksum.
 *
 ******************************************************************************/

u8 ap_is_valid_checksum(काष्ठा acpi_table_header *table)
अणु
	acpi_status status;
	काष्ठा acpi_table_rsdp *rsdp;

	अगर (ACPI_VALIDATE_RSDP_SIG(table->signature)) अणु
		/*
		 * Checksum क्रम RSDP.
		 * Note: Other checksums are computed during the table dump.
		 */
		rsdp = ACPI_CAST_PTR(काष्ठा acpi_table_rsdp, table);
		status = acpi_tb_validate_rsdp(rsdp);
	पूर्ण अन्यथा अणु
		status = acpi_tb_verअगरy_checksum(table, table->length);
	पूर्ण

	अगर (ACPI_FAILURE(status)) अणु
		ख_लिखो(मानक_त्रुटि, "%4.4s: Warning: wrong checksum in table\n",
			table->signature);
	पूर्ण

	वापस (AE_OK);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    ap_get_table_length
 *
 * PARAMETERS:  table               - Poपूर्णांकer to the table
 *
 * RETURN:      Table length
 *
 * DESCRIPTION: Obtain table length according to table signature.
 *
 ******************************************************************************/

u32 ap_get_table_length(काष्ठा acpi_table_header *table)
अणु
	काष्ठा acpi_table_rsdp *rsdp;

	/* Check अगर table is valid */

	अगर (!ap_is_valid_header(table)) अणु
		वापस (0);
	पूर्ण

	अगर (ACPI_VALIDATE_RSDP_SIG(table->signature)) अणु
		rsdp = ACPI_CAST_PTR(काष्ठा acpi_table_rsdp, table);
		वापस (acpi_tb_get_rsdp_length(rsdp));
	पूर्ण

	/* Normal ACPI table */

	वापस (table->length);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    ap_dump_table_buffer
 *
 * PARAMETERS:  table               - ACPI table to be dumped
 *              instance            - ACPI table instance no. to be dumped
 *              address             - Physical address of the table
 *
 * RETURN:      None
 *
 * DESCRIPTION: Dump an ACPI table in standard ASCII hex क्रमmat, with a
 *              header that is compatible with the acpi_xtract utility.
 *
 ******************************************************************************/

अटल पूर्णांक
ap_dump_table_buffer(काष्ठा acpi_table_header *table,
		     u32 instance, acpi_physical_address address)
अणु
	u32 table_length;

	table_length = ap_get_table_length(table);

	/* Prपूर्णांक only the header अगर requested */

	अगर (gbl_summary_mode) अणु
		acpi_tb_prपूर्णांक_table_header(address, table);
		वापस (0);
	पूर्ण

	/* Dump to binary file अगर requested */

	अगर (gbl_binary_mode) अणु
		वापस (ap_ग_लिखो_to_binary_file(table, instance));
	पूर्ण

	/*
	 * Dump the table with header क्रम use with acpixtract utility.
	 * Note: simplest to just always emit a 64-bit address. acpi_xtract
	 * utility can handle this.
	 */
	ख_लिखो(gbl_output_file, "%4.4s @ 0x%8.8X%8.8X\n",
		table->signature, ACPI_FORMAT_UINT64(address));

	acpi_ut_dump_buffer_to_file(gbl_output_file,
				    ACPI_CAST_PTR(u8, table), table_length,
				    DB_BYTE_DISPLAY, 0);
	ख_लिखो(gbl_output_file, "\n");
	वापस (0);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    ap_dump_all_tables
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Get all tables from the RSDT/XSDT (or at least all of the
 *              tables that we can possibly get).
 *
 ******************************************************************************/

पूर्णांक ap_dump_all_tables(व्योम)
अणु
	काष्ठा acpi_table_header *table;
	u32 instance = 0;
	acpi_physical_address address;
	acpi_status status;
	पूर्णांक table_status;
	u32 i;

	/* Get and dump all available ACPI tables */

	क्रम (i = 0; i < AP_MAX_ACPI_खाताS; i++) अणु
		status =
		    acpi_os_get_table_by_index(i, &table, &instance, &address);
		अगर (ACPI_FAILURE(status)) अणु

			/* AE_LIMIT means that no more tables are available */

			अगर (status == AE_LIMIT) अणु
				वापस (0);
			पूर्ण अन्यथा अगर (i == 0) अणु
				ख_लिखो(मानक_त्रुटि,
					"Could not get ACPI tables, %s\n",
					acpi_क्रमmat_exception(status));
				वापस (-1);
			पूर्ण अन्यथा अणु
				ख_लिखो(मानक_त्रुटि,
					"Could not get ACPI table at index %u, %s\n",
					i, acpi_क्रमmat_exception(status));
				जारी;
			पूर्ण
		पूर्ण

		table_status = ap_dump_table_buffer(table, instance, address);
		ACPI_FREE(table);

		अगर (table_status) अणु
			अवरोध;
		पूर्ण
	पूर्ण

	/* Something seriously bad happened अगर the loop terminates here */

	वापस (-1);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    ap_dump_table_by_address
 *
 * PARAMETERS:  ascii_address       - Address क्रम requested ACPI table
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Get an ACPI table via a physical address and dump it.
 *
 ******************************************************************************/

पूर्णांक ap_dump_table_by_address(अक्षर *ascii_address)
अणु
	acpi_physical_address address;
	काष्ठा acpi_table_header *table;
	acpi_status status;
	पूर्णांक table_status;
	u64 दीर्घ_address;

	/* Convert argument to an पूर्णांकeger physical address */

	status = acpi_ut_म_से_अदीर्घ64(ascii_address, &दीर्घ_address);
	अगर (ACPI_FAILURE(status)) अणु
		ख_लिखो(मानक_त्रुटि, "%s: Could not convert to a physical address\n",
			ascii_address);
		वापस (-1);
	पूर्ण

	address = (acpi_physical_address)दीर्घ_address;
	status = acpi_os_get_table_by_address(address, &table);
	अगर (ACPI_FAILURE(status)) अणु
		ख_लिखो(मानक_त्रुटि, "Could not get table at 0x%8.8X%8.8X, %s\n",
			ACPI_FORMAT_UINT64(address),
			acpi_क्रमmat_exception(status));
		वापस (-1);
	पूर्ण

	table_status = ap_dump_table_buffer(table, 0, address);
	ACPI_FREE(table);
	वापस (table_status);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    ap_dump_table_by_name
 *
 * PARAMETERS:  signature           - Requested ACPI table signature
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Get an ACPI table via a signature and dump it. Handles
 *              multiple tables with the same signature (SSDTs).
 *
 ******************************************************************************/

पूर्णांक ap_dump_table_by_name(अक्षर *signature)
अणु
	अक्षर local_signature[ACPI_NAMESEG_SIZE + 1];
	u32 instance;
	काष्ठा acpi_table_header *table;
	acpi_physical_address address;
	acpi_status status;
	पूर्णांक table_status;

	अगर (म_माप(signature) != ACPI_NAMESEG_SIZE) अणु
		ख_लिखो(मानक_त्रुटि,
			"Invalid table signature [%s]: must be exactly 4 characters\n",
			signature);
		वापस (-1);
	पूर्ण

	/* Table signatures are expected to be upperहाल */

	म_नकल(local_signature, signature);
	acpi_ut_strupr(local_signature);

	/* To be मित्रly, handle tables whose signatures करो not match the name */

	अगर (ACPI_COMPARE_NAMESEG(local_signature, "FADT")) अणु
		म_नकल(local_signature, ACPI_SIG_FADT);
	पूर्ण अन्यथा अगर (ACPI_COMPARE_NAMESEG(local_signature, "MADT")) अणु
		म_नकल(local_signature, ACPI_SIG_MADT);
	पूर्ण

	/* Dump all instances of this signature (to handle multiple SSDTs) */

	क्रम (instance = 0; instance < AP_MAX_ACPI_खाताS; instance++) अणु
		status = acpi_os_get_table_by_name(local_signature, instance,
						   &table, &address);
		अगर (ACPI_FAILURE(status)) अणु

			/* AE_LIMIT means that no more tables are available */

			अगर (status == AE_LIMIT) अणु
				वापस (0);
			पूर्ण

			ख_लिखो(मानक_त्रुटि,
				"Could not get ACPI table with signature [%s], %s\n",
				local_signature, acpi_क्रमmat_exception(status));
			वापस (-1);
		पूर्ण

		table_status = ap_dump_table_buffer(table, instance, address);
		ACPI_FREE(table);

		अगर (table_status) अणु
			अवरोध;
		पूर्ण
	पूर्ण

	/* Something seriously bad happened अगर the loop terminates here */

	वापस (-1);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    ap_dump_table_from_file
 *
 * PARAMETERS:  pathname            - File containing the binary ACPI table
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Dump an ACPI table from a binary file
 *
 ******************************************************************************/

पूर्णांक ap_dump_table_from_file(अक्षर *pathname)
अणु
	काष्ठा acpi_table_header *table;
	u32 file_size = 0;
	पूर्णांक table_status = -1;

	/* Get the entire ACPI table from the file */

	table = ap_get_table_from_file(pathname, &file_size);
	अगर (!table) अणु
		वापस (-1);
	पूर्ण

	अगर (!acpi_ut_valid_nameseg(table->signature)) अणु
		ख_लिखो(मानक_त्रुटि,
			"No valid ACPI signature was found in input file %s\n",
			pathname);
	पूर्ण

	/* File must be at least as दीर्घ as the table length */

	अगर (table->length > file_size) अणु
		ख_लिखो(मानक_त्रुटि,
			"Table length (0x%X) is too large for input file (0x%X) %s\n",
			table->length, file_size, pathname);
		जाओ निकास;
	पूर्ण

	अगर (gbl_verbose_mode) अणु
		ख_लिखो(मानक_त्रुटि,
			"Input file:  %s contains table [%4.4s], 0x%X (%u) bytes\n",
			pathname, table->signature, file_size, file_size);
	पूर्ण

	table_status = ap_dump_table_buffer(table, 0, 0);

निकास:
	ACPI_FREE(table);
	वापस (table_status);
पूर्ण
