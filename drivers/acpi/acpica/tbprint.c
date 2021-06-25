<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: tbprपूर्णांक - Table output utilities
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "actables.h"

#घोषणा _COMPONENT          ACPI_TABLES
ACPI_MODULE_NAME("tbprint")

/* Local prototypes */
अटल व्योम acpi_tb_fix_string(अक्षर *string, acpi_size length);

अटल व्योम
acpi_tb_cleanup_table_header(काष्ठा acpi_table_header *out_header,
			     काष्ठा acpi_table_header *header);

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_fix_string
 *
 * PARAMETERS:  string              - String to be repaired
 *              length              - Maximum length
 *
 * RETURN:      None
 *
 * DESCRIPTION: Replace every non-prपूर्णांकable or non-ascii byte in the string
 *              with a question mark '?'.
 *
 ******************************************************************************/

अटल व्योम acpi_tb_fix_string(अक्षर *string, acpi_size length)
अणु

	जबतक (length && *string) अणु
		अगर (!है_छाप((पूर्णांक)*string)) अणु
			*string = '?';
		पूर्ण

		string++;
		length--;
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_cleanup_table_header
 *
 * PARAMETERS:  out_header          - Where the cleaned header is वापसed
 *              header              - Input ACPI table header
 *
 * RETURN:      Returns the cleaned header in out_header
 *
 * DESCRIPTION: Copy the table header and ensure that all "string" fields in
 *              the header consist of prपूर्णांकable अक्षरacters.
 *
 ******************************************************************************/

अटल व्योम
acpi_tb_cleanup_table_header(काष्ठा acpi_table_header *out_header,
			     काष्ठा acpi_table_header *header)
अणु

	स_नकल(out_header, header, माप(काष्ठा acpi_table_header));

	acpi_tb_fix_string(out_header->signature, ACPI_NAMESEG_SIZE);
	acpi_tb_fix_string(out_header->oem_id, ACPI_OEM_ID_SIZE);
	acpi_tb_fix_string(out_header->oem_table_id, ACPI_OEM_TABLE_ID_SIZE);
	acpi_tb_fix_string(out_header->asl_compiler_id, ACPI_NAMESEG_SIZE);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_prपूर्णांक_table_header
 *
 * PARAMETERS:  address             - Table physical address
 *              header              - Table header
 *
 * RETURN:      None
 *
 * DESCRIPTION: Prपूर्णांक an ACPI table header. Special हालs क्रम FACS and RSDP.
 *
 ******************************************************************************/

व्योम
acpi_tb_prपूर्णांक_table_header(acpi_physical_address address,
			   काष्ठा acpi_table_header *header)
अणु
	काष्ठा acpi_table_header local_header;

	अगर (ACPI_COMPARE_NAMESEG(header->signature, ACPI_SIG_FACS)) अणु

		/* FACS only has signature and length fields */

		ACPI_INFO(("%-4.4s 0x%8.8X%8.8X %06X",
			   header->signature, ACPI_FORMAT_UINT64(address),
			   header->length));
	पूर्ण अन्यथा अगर (ACPI_VALIDATE_RSDP_SIG(header->signature)) अणु

		/* RSDP has no common fields */

		स_नकल(local_header.oem_id,
		       ACPI_CAST_PTR(काष्ठा acpi_table_rsdp, header)->oem_id,
		       ACPI_OEM_ID_SIZE);
		acpi_tb_fix_string(local_header.oem_id, ACPI_OEM_ID_SIZE);

		ACPI_INFO(("RSDP 0x%8.8X%8.8X %06X (v%.2d %-6.6s)",
			   ACPI_FORMAT_UINT64(address),
			   (ACPI_CAST_PTR(काष्ठा acpi_table_rsdp, header)->
			    revision >
			    0) ? ACPI_CAST_PTR(काष्ठा acpi_table_rsdp,
					       header)->length : 20,
			   ACPI_CAST_PTR(काष्ठा acpi_table_rsdp,
					 header)->revision,
			   local_header.oem_id));
	पूर्ण अन्यथा अणु
		/* Standard ACPI table with full common header */

		acpi_tb_cleanup_table_header(&local_header, header);

		ACPI_INFO(("%-4.4s 0x%8.8X%8.8X"
			   " %06X (v%.2d %-6.6s %-8.8s %08X %-4.4s %08X)",
			   local_header.signature, ACPI_FORMAT_UINT64(address),
			   local_header.length, local_header.revision,
			   local_header.oem_id, local_header.oem_table_id,
			   local_header.oem_revision,
			   local_header.asl_compiler_id,
			   local_header.asl_compiler_revision));
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_validate_checksum
 *
 * PARAMETERS:  table               - ACPI table to verअगरy
 *              length              - Length of entire table
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Verअगरies that the table checksums to zero. Optionally वापसs
 *              exception on bad checksum.
 *
 ******************************************************************************/

acpi_status acpi_tb_verअगरy_checksum(काष्ठा acpi_table_header *table, u32 length)
अणु
	u8 checksum;

	/*
	 * FACS/S3PT:
	 * They are the odd tables, have no standard ACPI header and no checksum
	 */

	अगर (ACPI_COMPARE_NAMESEG(table->signature, ACPI_SIG_S3PT) ||
	    ACPI_COMPARE_NAMESEG(table->signature, ACPI_SIG_FACS)) अणु
		वापस (AE_OK);
	पूर्ण

	/* Compute the checksum on the table */

	checksum = acpi_tb_checksum(ACPI_CAST_PTR(u8, table), length);

	/* Checksum ok? (should be zero) */

	अगर (checksum) अणु
		ACPI_BIOS_WARNING((AE_INFO,
				   "Incorrect checksum in table [%4.4s] - 0x%2.2X, "
				   "should be 0x%2.2X",
				   table->signature, table->checksum,
				   (u8)(table->checksum - checksum)));

#अगर (ACPI_CHECKSUM_ABORT)
		वापस (AE_BAD_CHECKSUM);
#पूर्ण_अगर
	पूर्ण

	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_checksum
 *
 * PARAMETERS:  buffer          - Poपूर्णांकer to memory region to be checked
 *              length          - Length of this memory region
 *
 * RETURN:      Checksum (u8)
 *
 * DESCRIPTION: Calculates circular checksum of memory region.
 *
 ******************************************************************************/

u8 acpi_tb_checksum(u8 *buffer, u32 length)
अणु
	u8 sum = 0;
	u8 *end = buffer + length;

	जबतक (buffer < end) अणु
		sum = (u8)(sum + *(buffer++));
	पूर्ण

	वापस (sum);
पूर्ण
