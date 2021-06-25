<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: tbdata - Table manager data काष्ठाure functions
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acnamesp.h"
#समावेश "actables.h"
#समावेश "acevents.h"

#घोषणा _COMPONENT          ACPI_TABLES
ACPI_MODULE_NAME("tbdata")

/* Local prototypes */
अटल acpi_status
acpi_tb_check_duplication(काष्ठा acpi_table_desc *table_desc, u32 *table_index);

अटल u8
acpi_tb_compare_tables(काष्ठा acpi_table_desc *table_desc, u32 table_index);

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_compare_tables
 *
 * PARAMETERS:  table_desc          - Table 1 descriptor to be compared
 *              table_index         - Index of table 2 to be compared
 *
 * RETURN:      TRUE अगर both tables are identical.
 *
 * DESCRIPTION: This function compares a table with another table that has
 *              alपढ़ोy been installed in the root table list.
 *
 ******************************************************************************/

अटल u8
acpi_tb_compare_tables(काष्ठा acpi_table_desc *table_desc, u32 table_index)
अणु
	acpi_status status = AE_OK;
	u8 is_identical;
	काष्ठा acpi_table_header *table;
	u32 table_length;
	u8 table_flags;

	status =
	    acpi_tb_acquire_table(&acpi_gbl_root_table_list.tables[table_index],
				  &table, &table_length, &table_flags);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (FALSE);
	पूर्ण

	/*
	 * Check क्रम a table match on the entire table length,
	 * not just the header.
	 */
	is_identical = (u8)((table_desc->length != table_length ||
			     स_भेद(table_desc->poपूर्णांकer, table, table_length)) ?
			    FALSE : TRUE);

	/* Release the acquired table */

	acpi_tb_release_table(table, table_length, table_flags);
	वापस (is_identical);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_init_table_descriptor
 *
 * PARAMETERS:  table_desc              - Table descriptor
 *              address                 - Physical address of the table
 *              flags                   - Allocation flags of the table
 *              table                   - Poपूर्णांकer to the table
 *
 * RETURN:      None
 *
 * DESCRIPTION: Initialize a new table descriptor
 *
 ******************************************************************************/

व्योम
acpi_tb_init_table_descriptor(काष्ठा acpi_table_desc *table_desc,
			      acpi_physical_address address,
			      u8 flags, काष्ठा acpi_table_header *table)
अणु

	/*
	 * Initialize the table descriptor. Set the poपूर्णांकer to शून्य, since the
	 * table is not fully mapped at this समय.
	 */
	स_रखो(table_desc, 0, माप(काष्ठा acpi_table_desc));
	table_desc->address = address;
	table_desc->length = table->length;
	table_desc->flags = flags;
	ACPI_MOVE_32_TO_32(table_desc->signature.ascii, table->signature);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_acquire_table
 *
 * PARAMETERS:  table_desc          - Table descriptor
 *              table_ptr           - Where table is वापसed
 *              table_length        - Where table length is वापसed
 *              table_flags         - Where table allocation flags are वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Acquire an ACPI table. It can be used क्रम tables not
 *              मुख्यtained in the acpi_gbl_root_table_list.
 *
 ******************************************************************************/

acpi_status
acpi_tb_acquire_table(काष्ठा acpi_table_desc *table_desc,
		      काष्ठा acpi_table_header **table_ptr,
		      u32 *table_length, u8 *table_flags)
अणु
	काष्ठा acpi_table_header *table = शून्य;

	चयन (table_desc->flags & ACPI_TABLE_ORIGIN_MASK) अणु
	हाल ACPI_TABLE_ORIGIN_INTERNAL_PHYSICAL:

		table =
		    acpi_os_map_memory(table_desc->address, table_desc->length);
		अवरोध;

	हाल ACPI_TABLE_ORIGIN_INTERNAL_VIRTUAL:
	हाल ACPI_TABLE_ORIGIN_EXTERNAL_VIRTUAL:

		table = ACPI_CAST_PTR(काष्ठा acpi_table_header,
				      ACPI_PHYSADDR_TO_PTR(table_desc->
							   address));
		अवरोध;

	शेष:

		अवरोध;
	पूर्ण

	/* Table is not valid yet */

	अगर (!table) अणु
		वापस (AE_NO_MEMORY);
	पूर्ण

	/* Fill the वापस values */

	*table_ptr = table;
	*table_length = table_desc->length;
	*table_flags = table_desc->flags;
	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_release_table
 *
 * PARAMETERS:  table               - Poपूर्णांकer क्रम the table
 *              table_length        - Length क्रम the table
 *              table_flags         - Allocation flags क्रम the table
 *
 * RETURN:      None
 *
 * DESCRIPTION: Release a table. The inverse of acpi_tb_acquire_table().
 *
 ******************************************************************************/

व्योम
acpi_tb_release_table(काष्ठा acpi_table_header *table,
		      u32 table_length, u8 table_flags)
अणु

	चयन (table_flags & ACPI_TABLE_ORIGIN_MASK) अणु
	हाल ACPI_TABLE_ORIGIN_INTERNAL_PHYSICAL:

		acpi_os_unmap_memory(table, table_length);
		अवरोध;

	हाल ACPI_TABLE_ORIGIN_INTERNAL_VIRTUAL:
	हाल ACPI_TABLE_ORIGIN_EXTERNAL_VIRTUAL:
	शेष:

		अवरोध;
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_acquire_temp_table
 *
 * PARAMETERS:  table_desc          - Table descriptor to be acquired
 *              address             - Address of the table
 *              flags               - Allocation flags of the table
 *
 * RETURN:      Status
 *
 * DESCRIPTION: This function validates the table header to obtain the length
 *              of a table and fills the table descriptor to make its state as
 *              "INSTALLED". Such a table descriptor is only used क्रम verअगरied
 *              installation.
 *
 ******************************************************************************/

acpi_status
acpi_tb_acquire_temp_table(काष्ठा acpi_table_desc *table_desc,
			   acpi_physical_address address, u8 flags)
अणु
	काष्ठा acpi_table_header *table_header;

	चयन (flags & ACPI_TABLE_ORIGIN_MASK) अणु
	हाल ACPI_TABLE_ORIGIN_INTERNAL_PHYSICAL:

		/* Get the length of the full table from the header */

		table_header =
		    acpi_os_map_memory(address,
				       माप(काष्ठा acpi_table_header));
		अगर (!table_header) अणु
			वापस (AE_NO_MEMORY);
		पूर्ण

		acpi_tb_init_table_descriptor(table_desc, address, flags,
					      table_header);
		acpi_os_unmap_memory(table_header,
				     माप(काष्ठा acpi_table_header));
		वापस (AE_OK);

	हाल ACPI_TABLE_ORIGIN_INTERNAL_VIRTUAL:
	हाल ACPI_TABLE_ORIGIN_EXTERNAL_VIRTUAL:

		table_header = ACPI_CAST_PTR(काष्ठा acpi_table_header,
					     ACPI_PHYSADDR_TO_PTR(address));
		अगर (!table_header) अणु
			वापस (AE_NO_MEMORY);
		पूर्ण

		acpi_tb_init_table_descriptor(table_desc, address, flags,
					      table_header);
		वापस (AE_OK);

	शेष:

		अवरोध;
	पूर्ण

	/* Table is not valid yet */

	वापस (AE_NO_MEMORY);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_release_temp_table
 *
 * PARAMETERS:  table_desc          - Table descriptor to be released
 *
 * RETURN:      Status
 *
 * DESCRIPTION: The inverse of acpi_tb_acquire_temp_table().
 *
 *****************************************************************************/

व्योम acpi_tb_release_temp_table(काष्ठा acpi_table_desc *table_desc)
अणु

	/*
	 * Note that the .Address is मुख्यtained by the callers of
	 * acpi_tb_acquire_temp_table(), thus करो not invoke acpi_tb_uninstall_table()
	 * where .Address will be मुक्तd.
	 */
	acpi_tb_invalidate_table(table_desc);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_tb_validate_table
 *
 * PARAMETERS:  table_desc          - Table descriptor
 *
 * RETURN:      Status
 *
 * DESCRIPTION: This function is called to validate the table, the वापसed
 *              table descriptor is in "VALIDATED" state.
 *
 *****************************************************************************/

acpi_status acpi_tb_validate_table(काष्ठा acpi_table_desc *table_desc)
अणु
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TRACE(tb_validate_table);

	/* Validate the table अगर necessary */

	अगर (!table_desc->poपूर्णांकer) अणु
		status = acpi_tb_acquire_table(table_desc, &table_desc->poपूर्णांकer,
					       &table_desc->length,
					       &table_desc->flags);
		अगर (!table_desc->poपूर्णांकer) अणु
			status = AE_NO_MEMORY;
		पूर्ण
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_invalidate_table
 *
 * PARAMETERS:  table_desc          - Table descriptor
 *
 * RETURN:      None
 *
 * DESCRIPTION: Invalidate one पूर्णांकernal ACPI table, this is the inverse of
 *              acpi_tb_validate_table().
 *
 ******************************************************************************/

व्योम acpi_tb_invalidate_table(काष्ठा acpi_table_desc *table_desc)
अणु

	ACPI_FUNCTION_TRACE(tb_invalidate_table);

	/* Table must be validated */

	अगर (!table_desc->poपूर्णांकer) अणु
		वापस_VOID;
	पूर्ण

	acpi_tb_release_table(table_desc->poपूर्णांकer, table_desc->length,
			      table_desc->flags);
	table_desc->poपूर्णांकer = शून्य;

	वापस_VOID;
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_tb_validate_temp_table
 *
 * PARAMETERS:  table_desc          - Table descriptor
 *
 * RETURN:      Status
 *
 * DESCRIPTION: This function is called to validate the table, the वापसed
 *              table descriptor is in "VALIDATED" state.
 *
 *****************************************************************************/

acpi_status acpi_tb_validate_temp_table(काष्ठा acpi_table_desc *table_desc)
अणु

	अगर (!table_desc->poपूर्णांकer && !acpi_gbl_enable_table_validation) अणु
		/*
		 * Only validates the header of the table.
		 * Note that Length contains the size of the mapping after invoking
		 * this work around, this value is required by
		 * acpi_tb_release_temp_table().
		 * We can करो this because in acpi_init_table_descriptor(), the Length
		 * field of the installed descriptor is filled with the actual
		 * table length obtaining from the table header.
		 */
		table_desc->length = माप(काष्ठा acpi_table_header);
	पूर्ण

	वापस (acpi_tb_validate_table(table_desc));
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_check_duplication
 *
 * PARAMETERS:  table_desc          - Table descriptor
 *              table_index         - Where the table index is वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Aव्योम installing duplicated tables. However table override and
 *              user aided dynamic table load is allowed, thus comparing the
 *              address of the table is not sufficient, and checking the entire
 *              table content is required.
 *
 ******************************************************************************/

अटल acpi_status
acpi_tb_check_duplication(काष्ठा acpi_table_desc *table_desc, u32 *table_index)
अणु
	u32 i;

	ACPI_FUNCTION_TRACE(tb_check_duplication);

	/* Check अगर table is alपढ़ोy रेजिस्टरed */

	क्रम (i = 0; i < acpi_gbl_root_table_list.current_table_count; ++i) अणु

		/* Do not compare with unverअगरied tables */

		अगर (!
		    (acpi_gbl_root_table_list.tables[i].
		     flags & ACPI_TABLE_IS_VERIFIED)) अणु
			जारी;
		पूर्ण

		/*
		 * Check क्रम a table match on the entire table length,
		 * not just the header.
		 */
		अगर (!acpi_tb_compare_tables(table_desc, i)) अणु
			जारी;
		पूर्ण

		/*
		 * Note: the current mechanism करोes not unरेजिस्टर a table अगर it is
		 * dynamically unloaded. The related namespace entries are deleted,
		 * but the table reमुख्यs in the root table list.
		 *
		 * The assumption here is that the number of dअगरferent tables that
		 * will be loaded is actually small, and there is minimal overhead
		 * in just keeping the table in हाल it is needed again.
		 *
		 * If this assumption changes in the future (perhaps on large
		 * machines with many table load/unload operations), tables will
		 * need to be unरेजिस्टरed when they are unloaded, and slots in the
		 * root table list should be reused when empty.
		 */
		अगर (acpi_gbl_root_table_list.tables[i].flags &
		    ACPI_TABLE_IS_LOADED) अणु

			/* Table is still loaded, this is an error */

			वापस_ACPI_STATUS(AE_ALREADY_EXISTS);
		पूर्ण अन्यथा अणु
			*table_index = i;
			वापस_ACPI_STATUS(AE_CTRL_TERMINATE);
		पूर्ण
	पूर्ण

	/* Indicate no duplication to the caller */

	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_tb_verअगरy_temp_table
 *
 * PARAMETERS:  table_desc          - Table descriptor
 *              signature           - Table signature to verअगरy
 *              table_index         - Where the table index is वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: This function is called to validate and verअगरy the table, the
 *              वापसed table descriptor is in "VALIDATED" state.
 *              Note that 'TableIndex' is required to be set to !शून्य to
 *              enable duplication check.
 *
 *****************************************************************************/

acpi_status
acpi_tb_verअगरy_temp_table(काष्ठा acpi_table_desc *table_desc,
			  अक्षर *signature, u32 *table_index)
अणु
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TRACE(tb_verअगरy_temp_table);

	/* Validate the table */

	status = acpi_tb_validate_temp_table(table_desc);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(AE_NO_MEMORY);
	पूर्ण

	/* If a particular signature is expected (DSDT/FACS), it must match */

	अगर (signature &&
	    !ACPI_COMPARE_NAMESEG(&table_desc->signature, signature)) अणु
		ACPI_BIOS_ERROR((AE_INFO,
				 "Invalid signature 0x%X for ACPI table, expected [%s]",
				 table_desc->signature.पूर्णांकeger, signature));
		status = AE_BAD_SIGNATURE;
		जाओ invalidate_and_निकास;
	पूर्ण

	अगर (acpi_gbl_enable_table_validation) अणु

		/* Verअगरy the checksum */

		status =
		    acpi_tb_verअगरy_checksum(table_desc->poपूर्णांकer,
					    table_desc->length);
		अगर (ACPI_FAILURE(status)) अणु
			ACPI_EXCEPTION((AE_INFO, AE_NO_MEMORY,
					"%4.4s 0x%8.8X%8.8X"
					" Attempted table install failed",
					acpi_ut_valid_nameseg(table_desc->
							      signature.
							      ascii) ?
					table_desc->signature.ascii : "????",
					ACPI_FORMAT_UINT64(table_desc->
							   address)));

			जाओ invalidate_and_निकास;
		पूर्ण

		/* Aव्योम duplications */

		अगर (table_index) अणु
			status =
			    acpi_tb_check_duplication(table_desc, table_index);
			अगर (ACPI_FAILURE(status)) अणु
				अगर (status != AE_CTRL_TERMINATE) अणु
					ACPI_EXCEPTION((AE_INFO, status,
							"%4.4s 0x%8.8X%8.8X"
							" Table is already loaded",
							acpi_ut_valid_nameseg
							(table_desc->signature.
							 ascii) ? table_desc->
							signature.
							ascii : "????",
							ACPI_FORMAT_UINT64
							(table_desc->address)));
				पूर्ण

				जाओ invalidate_and_निकास;
			पूर्ण
		पूर्ण

		table_desc->flags |= ACPI_TABLE_IS_VERIFIED;
	पूर्ण

	वापस_ACPI_STATUS(status);

invalidate_and_निकास:
	acpi_tb_invalidate_table(table_desc);
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_resize_root_table_list
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Expand the size of global table array
 *
 ******************************************************************************/

acpi_status acpi_tb_resize_root_table_list(व्योम)
अणु
	काष्ठा acpi_table_desc *tables;
	u32 table_count;
	u32 current_table_count, max_table_count;
	u32 i;

	ACPI_FUNCTION_TRACE(tb_resize_root_table_list);

	/* allow_resize flag is a parameter to acpi_initialize_tables */

	अगर (!(acpi_gbl_root_table_list.flags & ACPI_ROOT_ALLOW_RESIZE)) अणु
		ACPI_ERROR((AE_INFO,
			    "Resize of Root Table Array is not allowed"));
		वापस_ACPI_STATUS(AE_SUPPORT);
	पूर्ण

	/* Increase the Table Array size */

	अगर (acpi_gbl_root_table_list.flags & ACPI_ROOT_ORIGIN_ALLOCATED) अणु
		table_count = acpi_gbl_root_table_list.max_table_count;
	पूर्ण अन्यथा अणु
		table_count = acpi_gbl_root_table_list.current_table_count;
	पूर्ण

	max_table_count = table_count + ACPI_ROOT_TABLE_SIZE_INCREMENT;
	tables = ACPI_ALLOCATE_ZEROED(((acpi_size)max_table_count) *
				      माप(काष्ठा acpi_table_desc));
	अगर (!tables) अणु
		ACPI_ERROR((AE_INFO,
			    "Could not allocate new root table array"));
		वापस_ACPI_STATUS(AE_NO_MEMORY);
	पूर्ण

	/* Copy and मुक्त the previous table array */

	current_table_count = 0;
	अगर (acpi_gbl_root_table_list.tables) अणु
		क्रम (i = 0; i < table_count; i++) अणु
			अगर (acpi_gbl_root_table_list.tables[i].address) अणु
				स_नकल(tables + current_table_count,
				       acpi_gbl_root_table_list.tables + i,
				       माप(काष्ठा acpi_table_desc));
				current_table_count++;
			पूर्ण
		पूर्ण

		अगर (acpi_gbl_root_table_list.flags & ACPI_ROOT_ORIGIN_ALLOCATED) अणु
			ACPI_FREE(acpi_gbl_root_table_list.tables);
		पूर्ण
	पूर्ण

	acpi_gbl_root_table_list.tables = tables;
	acpi_gbl_root_table_list.max_table_count = max_table_count;
	acpi_gbl_root_table_list.current_table_count = current_table_count;
	acpi_gbl_root_table_list.flags |= ACPI_ROOT_ORIGIN_ALLOCATED;

	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_get_next_table_descriptor
 *
 * PARAMETERS:  table_index         - Where table index is वापसed
 *              table_desc          - Where table descriptor is वापसed
 *
 * RETURN:      Status and table index/descriptor.
 *
 * DESCRIPTION: Allocate a new ACPI table entry to the global table list
 *
 ******************************************************************************/

acpi_status
acpi_tb_get_next_table_descriptor(u32 *table_index,
				  काष्ठा acpi_table_desc **table_desc)
अणु
	acpi_status status;
	u32 i;

	/* Ensure that there is room क्रम the table in the Root Table List */

	अगर (acpi_gbl_root_table_list.current_table_count >=
	    acpi_gbl_root_table_list.max_table_count) अणु
		status = acpi_tb_resize_root_table_list();
		अगर (ACPI_FAILURE(status)) अणु
			वापस (status);
		पूर्ण
	पूर्ण

	i = acpi_gbl_root_table_list.current_table_count;
	acpi_gbl_root_table_list.current_table_count++;

	अगर (table_index) अणु
		*table_index = i;
	पूर्ण
	अगर (table_desc) अणु
		*table_desc = &acpi_gbl_root_table_list.tables[i];
	पूर्ण

	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_terminate
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: Delete all पूर्णांकernal ACPI tables
 *
 ******************************************************************************/

व्योम acpi_tb_terminate(व्योम)
अणु
	u32 i;

	ACPI_FUNCTION_TRACE(tb_terminate);

	(व्योम)acpi_ut_acquire_mutex(ACPI_MTX_TABLES);

	/* Delete the inभागidual tables */

	क्रम (i = 0; i < acpi_gbl_root_table_list.current_table_count; i++) अणु
		acpi_tb_uninstall_table(&acpi_gbl_root_table_list.tables[i]);
	पूर्ण

	/*
	 * Delete the root table array अगर allocated locally. Array cannot be
	 * mapped, so we करोn't need to check क्रम that flag.
	 */
	अगर (acpi_gbl_root_table_list.flags & ACPI_ROOT_ORIGIN_ALLOCATED) अणु
		ACPI_FREE(acpi_gbl_root_table_list.tables);
	पूर्ण

	acpi_gbl_root_table_list.tables = शून्य;
	acpi_gbl_root_table_list.flags = 0;
	acpi_gbl_root_table_list.current_table_count = 0;

	ACPI_DEBUG_PRINT((ACPI_DB_INFO, "ACPI Tables freed\n"));

	(व्योम)acpi_ut_release_mutex(ACPI_MTX_TABLES);
	वापस_VOID;
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_delete_namespace_by_owner
 *
 * PARAMETERS:  table_index         - Table index
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Delete all namespace objects created when this table was loaded.
 *
 ******************************************************************************/

acpi_status acpi_tb_delete_namespace_by_owner(u32 table_index)
अणु
	acpi_owner_id owner_id;
	acpi_status status;

	ACPI_FUNCTION_TRACE(tb_delete_namespace_by_owner);

	status = acpi_ut_acquire_mutex(ACPI_MTX_TABLES);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	अगर (table_index >= acpi_gbl_root_table_list.current_table_count) अणु

		/* The table index करोes not exist */

		(व्योम)acpi_ut_release_mutex(ACPI_MTX_TABLES);
		वापस_ACPI_STATUS(AE_NOT_EXIST);
	पूर्ण

	/* Get the owner ID क्रम this table, used to delete namespace nodes */

	owner_id = acpi_gbl_root_table_list.tables[table_index].owner_id;
	(व्योम)acpi_ut_release_mutex(ACPI_MTX_TABLES);

	/*
	 * Need to acquire the namespace ग_लिखोr lock to prevent पूर्णांकerference
	 * with any concurrent namespace walks. The पूर्णांकerpreter must be
	 * released during the deletion since the acquisition of the deletion
	 * lock may block, and also since the execution of a namespace walk
	 * must be allowed to use the पूर्णांकerpreter.
	 */
	status = acpi_ut_acquire_ग_लिखो_lock(&acpi_gbl_namespace_rw_lock);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	acpi_ns_delete_namespace_by_owner(owner_id);
	acpi_ut_release_ग_लिखो_lock(&acpi_gbl_namespace_rw_lock);
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_allocate_owner_id
 *
 * PARAMETERS:  table_index         - Table index
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Allocates owner_id in table_desc
 *
 ******************************************************************************/

acpi_status acpi_tb_allocate_owner_id(u32 table_index)
अणु
	acpi_status status = AE_BAD_PARAMETER;

	ACPI_FUNCTION_TRACE(tb_allocate_owner_id);

	(व्योम)acpi_ut_acquire_mutex(ACPI_MTX_TABLES);
	अगर (table_index < acpi_gbl_root_table_list.current_table_count) अणु
		status =
		    acpi_ut_allocate_owner_id(&
					      (acpi_gbl_root_table_list.
					       tables[table_index].owner_id));
	पूर्ण

	(व्योम)acpi_ut_release_mutex(ACPI_MTX_TABLES);
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_release_owner_id
 *
 * PARAMETERS:  table_index         - Table index
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Releases owner_id in table_desc
 *
 ******************************************************************************/

acpi_status acpi_tb_release_owner_id(u32 table_index)
अणु
	acpi_status status = AE_BAD_PARAMETER;

	ACPI_FUNCTION_TRACE(tb_release_owner_id);

	(व्योम)acpi_ut_acquire_mutex(ACPI_MTX_TABLES);
	अगर (table_index < acpi_gbl_root_table_list.current_table_count) अणु
		acpi_ut_release_owner_id(&
					 (acpi_gbl_root_table_list.
					  tables[table_index].owner_id));
		status = AE_OK;
	पूर्ण

	(व्योम)acpi_ut_release_mutex(ACPI_MTX_TABLES);
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_get_owner_id
 *
 * PARAMETERS:  table_index         - Table index
 *              owner_id            - Where the table owner_id is वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: वापसs owner_id क्रम the ACPI table
 *
 ******************************************************************************/

acpi_status acpi_tb_get_owner_id(u32 table_index, acpi_owner_id *owner_id)
अणु
	acpi_status status = AE_BAD_PARAMETER;

	ACPI_FUNCTION_TRACE(tb_get_owner_id);

	(व्योम)acpi_ut_acquire_mutex(ACPI_MTX_TABLES);
	अगर (table_index < acpi_gbl_root_table_list.current_table_count) अणु
		*owner_id =
		    acpi_gbl_root_table_list.tables[table_index].owner_id;
		status = AE_OK;
	पूर्ण

	(व्योम)acpi_ut_release_mutex(ACPI_MTX_TABLES);
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_is_table_loaded
 *
 * PARAMETERS:  table_index         - Index पूर्णांकo the root table
 *
 * RETURN:      Table Loaded Flag
 *
 ******************************************************************************/

u8 acpi_tb_is_table_loaded(u32 table_index)
अणु
	u8 is_loaded = FALSE;

	(व्योम)acpi_ut_acquire_mutex(ACPI_MTX_TABLES);
	अगर (table_index < acpi_gbl_root_table_list.current_table_count) अणु
		is_loaded = (u8)
		    (acpi_gbl_root_table_list.tables[table_index].flags &
		     ACPI_TABLE_IS_LOADED);
	पूर्ण

	(व्योम)acpi_ut_release_mutex(ACPI_MTX_TABLES);
	वापस (is_loaded);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_set_table_loaded_flag
 *
 * PARAMETERS:  table_index         - Table index
 *              is_loaded           - TRUE अगर table is loaded, FALSE otherwise
 *
 * RETURN:      None
 *
 * DESCRIPTION: Sets the table loaded flag to either TRUE or FALSE.
 *
 ******************************************************************************/

व्योम acpi_tb_set_table_loaded_flag(u32 table_index, u8 is_loaded)
अणु

	(व्योम)acpi_ut_acquire_mutex(ACPI_MTX_TABLES);
	अगर (table_index < acpi_gbl_root_table_list.current_table_count) अणु
		अगर (is_loaded) अणु
			acpi_gbl_root_table_list.tables[table_index].flags |=
			    ACPI_TABLE_IS_LOADED;
		पूर्ण अन्यथा अणु
			acpi_gbl_root_table_list.tables[table_index].flags &=
			    ~ACPI_TABLE_IS_LOADED;
		पूर्ण
	पूर्ण

	(व्योम)acpi_ut_release_mutex(ACPI_MTX_TABLES);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_load_table
 *
 * PARAMETERS:  table_index             - Table index
 *              parent_node             - Where table index is वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Load an ACPI table
 *
 ******************************************************************************/

acpi_status
acpi_tb_load_table(u32 table_index, काष्ठा acpi_namespace_node *parent_node)
अणु
	काष्ठा acpi_table_header *table;
	acpi_status status;
	acpi_owner_id owner_id;

	ACPI_FUNCTION_TRACE(tb_load_table);

	/*
	 * Note: Now table is "INSTALLED", it must be validated beक्रमe
	 * using.
	 */
	status = acpi_get_table_by_index(table_index, &table);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	status = acpi_ns_load_table(table_index, parent_node);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/*
	 * Update GPEs क्रम any new _Lxx/_Exx methods. Ignore errors. The host is
	 * responsible क्रम discovering any new wake GPEs by running _PRW methods
	 * that may have been loaded by this table.
	 */
	status = acpi_tb_get_owner_id(table_index, &owner_id);
	अगर (ACPI_SUCCESS(status)) अणु
		acpi_ev_update_gpes(owner_id);
	पूर्ण

	/* Invoke table handler */

	acpi_tb_notअगरy_table(ACPI_TABLE_EVENT_LOAD, table);
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_install_and_load_table
 *
 * PARAMETERS:  address                 - Physical address of the table
 *              flags                   - Allocation flags of the table
 *              override                - Whether override should be perक्रमmed
 *              table_index             - Where table index is वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Install and load an ACPI table
 *
 ******************************************************************************/

acpi_status
acpi_tb_install_and_load_table(acpi_physical_address address,
			       u8 flags, u8 override, u32 *table_index)
अणु
	acpi_status status;
	u32 i;

	ACPI_FUNCTION_TRACE(tb_install_and_load_table);

	/* Install the table and load it पूर्णांकo the namespace */

	status = acpi_tb_install_standard_table(address, flags, TRUE,
						override, &i);
	अगर (ACPI_FAILURE(status)) अणु
		जाओ निकास;
	पूर्ण

	status = acpi_tb_load_table(i, acpi_gbl_root_node);

निकास:
	*table_index = i;
	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_tb_install_and_load_table)

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_unload_table
 *
 * PARAMETERS:  table_index             - Table index
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Unload an ACPI table
 *
 ******************************************************************************/

acpi_status acpi_tb_unload_table(u32 table_index)
अणु
	acpi_status status = AE_OK;
	काष्ठा acpi_table_header *table;

	ACPI_FUNCTION_TRACE(tb_unload_table);

	/* Ensure the table is still loaded */

	अगर (!acpi_tb_is_table_loaded(table_index)) अणु
		वापस_ACPI_STATUS(AE_NOT_EXIST);
	पूर्ण

	/* Invoke table handler */

	status = acpi_get_table_by_index(table_index, &table);
	अगर (ACPI_SUCCESS(status)) अणु
		acpi_tb_notअगरy_table(ACPI_TABLE_EVENT_UNLOAD, table);
	पूर्ण

	/* Delete the portion of the namespace owned by this table */

	status = acpi_tb_delete_namespace_by_owner(table_index);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	(व्योम)acpi_tb_release_owner_id(table_index);
	acpi_tb_set_table_loaded_flag(table_index, FALSE);
	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_tb_unload_table)

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_notअगरy_table
 *
 * PARAMETERS:  event               - Table event
 *              table               - Validated table poपूर्णांकer
 *
 * RETURN:      None
 *
 * DESCRIPTION: Notअगरy a table event to the users.
 *
 ******************************************************************************/

व्योम acpi_tb_notअगरy_table(u32 event, व्योम *table)
अणु
	/* Invoke table handler अगर present */

	अगर (acpi_gbl_table_handler) अणु
		(व्योम)acpi_gbl_table_handler(event, table,
					     acpi_gbl_table_handler_context);
	पूर्ण
पूर्ण
