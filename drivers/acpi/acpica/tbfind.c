<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: tbfind   - find table
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "actables.h"

#घोषणा _COMPONENT          ACPI_TABLES
ACPI_MODULE_NAME("tbfind")

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_find_table
 *
 * PARAMETERS:  signature           - String with ACPI table signature
 *              oem_id              - String with the table OEM ID
 *              oem_table_id        - String with the OEM Table ID
 *              table_index         - Where the table index is वापसed
 *
 * RETURN:      Status and table index
 *
 * DESCRIPTION: Find an ACPI table (in the RSDT/XSDT) that matches the
 *              Signature, OEM ID and OEM Table ID. Returns an index that can
 *              be used to get the table header or entire table.
 *
 ******************************************************************************/
acpi_status
acpi_tb_find_table(अक्षर *signature,
		   अक्षर *oem_id, अक्षर *oem_table_id, u32 *table_index)
अणु
	acpi_status status = AE_OK;
	काष्ठा acpi_table_header header;
	u32 i;

	ACPI_FUNCTION_TRACE(tb_find_table);

	/* Validate the input table signature */

	अगर (!acpi_ut_valid_nameseg(signature)) अणु
		वापस_ACPI_STATUS(AE_BAD_SIGNATURE);
	पूर्ण

	/* Don't allow the OEM strings to be too दीर्घ */

	अगर ((म_माप(oem_id) > ACPI_OEM_ID_SIZE) ||
	    (म_माप(oem_table_id) > ACPI_OEM_TABLE_ID_SIZE)) अणु
		वापस_ACPI_STATUS(AE_AML_STRING_LIMIT);
	पूर्ण

	/* Normalize the input strings */

	स_रखो(&header, 0, माप(काष्ठा acpi_table_header));
	ACPI_COPY_NAMESEG(header.signature, signature);
	म_नकलन(header.oem_id, oem_id, ACPI_OEM_ID_SIZE);
	म_नकलन(header.oem_table_id, oem_table_id, ACPI_OEM_TABLE_ID_SIZE);

	/* Search क्रम the table */

	(व्योम)acpi_ut_acquire_mutex(ACPI_MTX_TABLES);
	क्रम (i = 0; i < acpi_gbl_root_table_list.current_table_count; ++i) अणु
		अगर (स_भेद(&(acpi_gbl_root_table_list.tables[i].signature),
			   header.signature, ACPI_NAMESEG_SIZE)) अणु

			/* Not the requested table */

			जारी;
		पूर्ण

		/* Table with matching signature has been found */

		अगर (!acpi_gbl_root_table_list.tables[i].poपूर्णांकer) अणु

			/* Table is not currently mapped, map it */

			status =
			    acpi_tb_validate_table(&acpi_gbl_root_table_list.
						   tables[i]);
			अगर (ACPI_FAILURE(status)) अणु
				जाओ unlock_and_निकास;
			पूर्ण

			अगर (!acpi_gbl_root_table_list.tables[i].poपूर्णांकer) अणु
				जारी;
			पूर्ण
		पूर्ण

		/* Check क्रम table match on all IDs */

		अगर (!स_भेद
		    (acpi_gbl_root_table_list.tables[i].poपूर्णांकer->signature,
		     header.signature, ACPI_NAMESEG_SIZE) && (!oem_id[0]
							      ||
							      !स_भेद
							      (acpi_gbl_root_table_list.
							       tables[i].
							       poपूर्णांकer->oem_id,
							       header.oem_id,
							       ACPI_OEM_ID_SIZE))
		    && (!oem_table_id[0]
			|| !स_भेद(acpi_gbl_root_table_list.tables[i].poपूर्णांकer->
				   oem_table_id, header.oem_table_id,
				   ACPI_OEM_TABLE_ID_SIZE))) अणु
			*table_index = i;

			ACPI_DEBUG_PRINT((ACPI_DB_TABLES,
					  "Found table [%4.4s]\n",
					  header.signature));
			जाओ unlock_and_निकास;
		पूर्ण
	पूर्ण
	status = AE_NOT_FOUND;

unlock_and_निकास:
	(व्योम)acpi_ut_release_mutex(ACPI_MTX_TABLES);
	वापस_ACPI_STATUS(status);
पूर्ण
