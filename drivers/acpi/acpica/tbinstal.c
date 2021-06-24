<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: tbinstal - ACPI table installation and removal
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "actables.h"

#घोषणा _COMPONENT          ACPI_TABLES
ACPI_MODULE_NAME("tbinstal")

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_install_table_with_override
 *
 * PARAMETERS:  new_table_desc          - New table descriptor to install
 *              override                - Whether override should be perक्रमmed
 *              table_index             - Where the table index is वापसed
 *
 * RETURN:      None
 *
 * DESCRIPTION: Install an ACPI table पूर्णांकo the global data काष्ठाure. The
 *              table override mechanism is called to allow the host
 *              OS to replace any table beक्रमe it is installed in the root
 *              table array.
 *
 ******************************************************************************/
व्योम
acpi_tb_install_table_with_override(काष्ठा acpi_table_desc *new_table_desc,
				    u8 override, u32 *table_index)
अणु
	u32 i;
	acpi_status status;

	status = acpi_tb_get_next_table_descriptor(&i, शून्य);
	अगर (ACPI_FAILURE(status)) अणु
		वापस;
	पूर्ण

	/*
	 * ACPI Table Override:
	 *
	 * Beक्रमe we install the table, let the host OS override it with a new
	 * one अगर desired. Any table within the RSDT/XSDT can be replaced,
	 * including the DSDT which is poपूर्णांकed to by the FADT.
	 */
	अगर (override) अणु
		acpi_tb_override_table(new_table_desc);
	पूर्ण

	acpi_tb_init_table_descriptor(&acpi_gbl_root_table_list.tables[i],
				      new_table_desc->address,
				      new_table_desc->flags,
				      new_table_desc->poपूर्णांकer);

	acpi_tb_prपूर्णांक_table_header(new_table_desc->address,
				   new_table_desc->poपूर्णांकer);

	/* This synchronizes acpi_gbl_dsdt_index */

	*table_index = i;

	/* Set the global पूर्णांकeger width (based upon revision of the DSDT) */

	अगर (i == acpi_gbl_dsdt_index) अणु
		acpi_ut_set_पूर्णांकeger_width(new_table_desc->poपूर्णांकer->revision);
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_install_standard_table
 *
 * PARAMETERS:  address             - Address of the table (might be a भव
 *                                    address depending on the table_flags)
 *              flags               - Flags क्रम the table
 *              reload              - Whether reload should be perक्रमmed
 *              override            - Whether override should be perक्रमmed
 *              table_index         - Where the table index is वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: This function is called to verअगरy and install an ACPI table.
 *              When this function is called by "Load" or "LoadTable" opcodes,
 *              or by acpi_load_table() API, the "Reload" parameter is set.
 *              After successfully वापसing from this function, table is
 *              "INSTALLED" but not "VALIDATED".
 *
 ******************************************************************************/

acpi_status
acpi_tb_install_standard_table(acpi_physical_address address,
			       u8 flags,
			       u8 reload, u8 override, u32 *table_index)
अणु
	u32 i;
	acpi_status status = AE_OK;
	काष्ठा acpi_table_desc new_table_desc;

	ACPI_FUNCTION_TRACE(tb_install_standard_table);

	/* Acquire a temporary table descriptor क्रम validation */

	status = acpi_tb_acquire_temp_table(&new_table_desc, address, flags);
	अगर (ACPI_FAILURE(status)) अणु
		ACPI_ERROR((AE_INFO,
			    "Could not acquire table length at %8.8X%8.8X",
			    ACPI_FORMAT_UINT64(address)));
		वापस_ACPI_STATUS(status);
	पूर्ण

	/*
	 * Optionally करो not load any SSDTs from the RSDT/XSDT. This can
	 * be useful क्रम debugging ACPI problems on some machines.
	 */
	अगर (!reload &&
	    acpi_gbl_disable_ssdt_table_install &&
	    ACPI_COMPARE_NAMESEG(&new_table_desc.signature, ACPI_SIG_SSDT)) अणु
		ACPI_INFO(("Ignoring installation of %4.4s at %8.8X%8.8X",
			   new_table_desc.signature.ascii,
			   ACPI_FORMAT_UINT64(address)));
		जाओ release_and_निकास;
	पूर्ण

	/* Acquire the table lock */

	(व्योम)acpi_ut_acquire_mutex(ACPI_MTX_TABLES);

	/* Validate and verअगरy a table beक्रमe installation */

	status = acpi_tb_verअगरy_temp_table(&new_table_desc, शून्य, &i);
	अगर (ACPI_FAILURE(status)) अणु
		अगर (status == AE_CTRL_TERMINATE) अणु
			/*
			 * Table was unloaded, allow it to be reloaded.
			 * As we are going to वापस AE_OK to the caller, we should
			 * take the responsibility of मुक्तing the input descriptor.
			 * Refill the input descriptor to ensure
			 * acpi_tb_install_table_with_override() can be called again to
			 * indicate the re-installation.
			 */
			acpi_tb_uninstall_table(&new_table_desc);
			(व्योम)acpi_ut_release_mutex(ACPI_MTX_TABLES);
			*table_index = i;
			वापस_ACPI_STATUS(AE_OK);
		पूर्ण
		जाओ unlock_and_निकास;
	पूर्ण

	/* Add the table to the global root table list */

	acpi_tb_install_table_with_override(&new_table_desc, override,
					    table_index);

	/* Invoke table handler */

	(व्योम)acpi_ut_release_mutex(ACPI_MTX_TABLES);
	acpi_tb_notअगरy_table(ACPI_TABLE_EVENT_INSTALL, new_table_desc.poपूर्णांकer);
	(व्योम)acpi_ut_acquire_mutex(ACPI_MTX_TABLES);

unlock_and_निकास:

	/* Release the table lock */

	(व्योम)acpi_ut_release_mutex(ACPI_MTX_TABLES);

release_and_निकास:

	/* Release the temporary table descriptor */

	acpi_tb_release_temp_table(&new_table_desc);
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_override_table
 *
 * PARAMETERS:  old_table_desc      - Validated table descriptor to be
 *                                    overridden
 *
 * RETURN:      None
 *
 * DESCRIPTION: Attempt table override by calling the OSL override functions.
 *              Note: If the table is overridden, then the entire new table
 *              is acquired and वापसed by this function.
 *              Beक्रमe/after invocation, the table descriptor is in a state
 *              that is "VALIDATED".
 *
 ******************************************************************************/

व्योम acpi_tb_override_table(काष्ठा acpi_table_desc *old_table_desc)
अणु
	acpi_status status;
	काष्ठा acpi_table_desc new_table_desc;
	काष्ठा acpi_table_header *table;
	acpi_physical_address address;
	u32 length;
	ACPI_ERROR_ONLY(अक्षर *override_type);

	/* (1) Attempt logical override (वापसs a logical address) */

	status = acpi_os_table_override(old_table_desc->poपूर्णांकer, &table);
	अगर (ACPI_SUCCESS(status) && table) अणु
		acpi_tb_acquire_temp_table(&new_table_desc,
					   ACPI_PTR_TO_PHYSADDR(table),
					   ACPI_TABLE_ORIGIN_EXTERNAL_VIRTUAL);
		ACPI_ERROR_ONLY(override_type = "Logical");
		जाओ finish_override;
	पूर्ण

	/* (2) Attempt physical override (वापसs a physical address) */

	status = acpi_os_physical_table_override(old_table_desc->poपूर्णांकer,
						 &address, &length);
	अगर (ACPI_SUCCESS(status) && address && length) अणु
		acpi_tb_acquire_temp_table(&new_table_desc, address,
					   ACPI_TABLE_ORIGIN_INTERNAL_PHYSICAL);
		ACPI_ERROR_ONLY(override_type = "Physical");
		जाओ finish_override;
	पूर्ण

	वापस;			/* There was no override */

finish_override:

	/*
	 * Validate and verअगरy a table beक्रमe overriding, no nested table
	 * duplication check as it's too complicated and unnecessary.
	 */
	status = acpi_tb_verअगरy_temp_table(&new_table_desc, शून्य, शून्य);
	अगर (ACPI_FAILURE(status)) अणु
		वापस;
	पूर्ण

	ACPI_INFO(("%4.4s 0x%8.8X%8.8X"
		   " %s table override, new table: 0x%8.8X%8.8X",
		   old_table_desc->signature.ascii,
		   ACPI_FORMAT_UINT64(old_table_desc->address),
		   override_type, ACPI_FORMAT_UINT64(new_table_desc.address)));

	/* We can now uninstall the original table */

	acpi_tb_uninstall_table(old_table_desc);

	/*
	 * Replace the original table descriptor and keep its state as
	 * "VALIDATED".
	 */
	acpi_tb_init_table_descriptor(old_table_desc, new_table_desc.address,
				      new_table_desc.flags,
				      new_table_desc.poपूर्णांकer);
	acpi_tb_validate_temp_table(old_table_desc);

	/* Release the temporary table descriptor */

	acpi_tb_release_temp_table(&new_table_desc);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_uninstall_table
 *
 * PARAMETERS:  table_desc          - Table descriptor
 *
 * RETURN:      None
 *
 * DESCRIPTION: Delete one पूर्णांकernal ACPI table
 *
 ******************************************************************************/

व्योम acpi_tb_uninstall_table(काष्ठा acpi_table_desc *table_desc)
अणु

	ACPI_FUNCTION_TRACE(tb_uninstall_table);

	/* Table must be installed */

	अगर (!table_desc->address) अणु
		वापस_VOID;
	पूर्ण

	acpi_tb_invalidate_table(table_desc);

	अगर ((table_desc->flags & ACPI_TABLE_ORIGIN_MASK) ==
	    ACPI_TABLE_ORIGIN_INTERNAL_VIRTUAL) अणु
		ACPI_FREE(ACPI_PHYSADDR_TO_PTR(table_desc->address));
	पूर्ण

	table_desc->address = ACPI_PTR_TO_PHYSADDR(शून्य);
	वापस_VOID;
पूर्ण
