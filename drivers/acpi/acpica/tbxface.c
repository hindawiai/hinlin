<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: tbxface - ACPI table-oriented बाह्यal पूर्णांकerfaces
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#घोषणा EXPORT_ACPI_INTERFACES

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "actables.h"

#घोषणा _COMPONENT          ACPI_TABLES
ACPI_MODULE_NAME("tbxface")

/*******************************************************************************
 *
 * FUNCTION:    acpi_allocate_root_table
 *
 * PARAMETERS:  initial_table_count - Size of initial_table_array, in number of
 *                                    काष्ठा acpi_table_desc काष्ठाures
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Allocate a root table array. Used by iASL compiler and
 *              acpi_initialize_tables.
 *
 ******************************************************************************/
acpi_status acpi_allocate_root_table(u32 initial_table_count)
अणु

	acpi_gbl_root_table_list.max_table_count = initial_table_count;
	acpi_gbl_root_table_list.flags = ACPI_ROOT_ALLOW_RESIZE;

	वापस (acpi_tb_resize_root_table_list());
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_initialize_tables
 *
 * PARAMETERS:  initial_table_array - Poपूर्णांकer to an array of pre-allocated
 *                                    काष्ठा acpi_table_desc काष्ठाures. If शून्य, the
 *                                    array is dynamically allocated.
 *              initial_table_count - Size of initial_table_array, in number of
 *                                    काष्ठा acpi_table_desc काष्ठाures
 *              allow_resize        - Flag to tell Table Manager अगर resize of
 *                                    pre-allocated array is allowed. Ignored
 *                                    अगर initial_table_array is शून्य.
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Initialize the table manager, get the RSDP and RSDT/XSDT.
 *
 * NOTE:        Allows अटल allocation of the initial table array in order
 *              to aव्योम the use of dynamic memory in confined environments
 *              such as the kernel boot sequence where it may not be available.
 *
 *              If the host OS memory managers are initialized, use शून्य क्रम
 *              initial_table_array, and the table will be dynamically allocated.
 *
 ******************************************************************************/

acpi_status ACPI_INIT_FUNCTION
acpi_initialize_tables(काष्ठा acpi_table_desc *initial_table_array,
		       u32 initial_table_count, u8 allow_resize)
अणु
	acpi_physical_address rsdp_address;
	acpi_status status;

	ACPI_FUNCTION_TRACE(acpi_initialize_tables);

	/*
	 * Setup the Root Table Array and allocate the table array
	 * अगर requested
	 */
	अगर (!initial_table_array) अणु
		status = acpi_allocate_root_table(initial_table_count);
		अगर (ACPI_FAILURE(status)) अणु
			वापस_ACPI_STATUS(status);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Root Table Array has been अटलally allocated by the host */

		स_रखो(initial_table_array, 0,
		       (acpi_size)initial_table_count *
		       माप(काष्ठा acpi_table_desc));

		acpi_gbl_root_table_list.tables = initial_table_array;
		acpi_gbl_root_table_list.max_table_count = initial_table_count;
		acpi_gbl_root_table_list.flags = ACPI_ROOT_ORIGIN_UNKNOWN;
		अगर (allow_resize) अणु
			acpi_gbl_root_table_list.flags |=
			    ACPI_ROOT_ALLOW_RESIZE;
		पूर्ण
	पूर्ण

	/* Get the address of the RSDP */

	rsdp_address = acpi_os_get_root_poपूर्णांकer();
	अगर (!rsdp_address) अणु
		वापस_ACPI_STATUS(AE_NOT_FOUND);
	पूर्ण

	/*
	 * Get the root table (RSDT or XSDT) and extract all entries to the local
	 * Root Table Array. This array contains the inक्रमmation of the RSDT/XSDT
	 * in a common, more usable क्रमmat.
	 */
	status = acpi_tb_parse_root_table(rsdp_address);
	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL_INIT(acpi_initialize_tables)

/*******************************************************************************
 *
 * FUNCTION:    acpi_पुनः_स्मृतिate_root_table
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Reallocate Root Table List पूर्णांकo dynamic memory. Copies the
 *              root list from the previously provided scratch area. Should
 *              be called once dynamic memory allocation is available in the
 *              kernel.
 *
 ******************************************************************************/
acpi_status ACPI_INIT_FUNCTION acpi_पुनः_स्मृतिate_root_table(व्योम)
अणु
	acpi_status status;
	काष्ठा acpi_table_desc *table_desc;
	u32 i, j;

	ACPI_FUNCTION_TRACE(acpi_पुनः_स्मृतिate_root_table);

	/*
	 * If there are tables unverअगरied, it is required to पुनः_स्मृतिate the
	 * root table list to clean up invalid table entries. Otherwise only
	 * पुनः_स्मृतिate the root table list अगर the host provided a अटल buffer
	 * क्रम the table array in the call to acpi_initialize_tables().
	 */
	अगर ((acpi_gbl_root_table_list.flags & ACPI_ROOT_ORIGIN_ALLOCATED) &&
	    acpi_gbl_enable_table_validation) अणु
		वापस_ACPI_STATUS(AE_SUPPORT);
	पूर्ण

	(व्योम)acpi_ut_acquire_mutex(ACPI_MTX_TABLES);

	/*
	 * Ensure OS early boot logic, which is required by some hosts. If the
	 * table state is reported to be wrong, developers should fix the
	 * issue by invoking acpi_put_table() क्रम the reported table during the
	 * early stage.
	 */
	क्रम (i = 0; i < acpi_gbl_root_table_list.current_table_count; ++i) अणु
		table_desc = &acpi_gbl_root_table_list.tables[i];
		अगर (table_desc->poपूर्णांकer) अणु
			ACPI_ERROR((AE_INFO,
				    "Table [%4.4s] is not invalidated during early boot stage",
				    table_desc->signature.ascii));
		पूर्ण
	पूर्ण

	अगर (!acpi_gbl_enable_table_validation) अणु
		/*
		 * Now it's safe to करो full table validation. We can करो deferred
		 * table initialization here once the flag is set.
		 */
		acpi_gbl_enable_table_validation = TRUE;
		क्रम (i = 0; i < acpi_gbl_root_table_list.current_table_count;
		     ++i) अणु
			table_desc = &acpi_gbl_root_table_list.tables[i];
			अगर (!(table_desc->flags & ACPI_TABLE_IS_VERIFIED)) अणु
				status =
				    acpi_tb_verअगरy_temp_table(table_desc, शून्य,
							      &j);
				अगर (ACPI_FAILURE(status)) अणु
					acpi_tb_uninstall_table(table_desc);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	acpi_gbl_root_table_list.flags |= ACPI_ROOT_ALLOW_RESIZE;
	status = acpi_tb_resize_root_table_list();
	acpi_gbl_root_table_list.flags |= ACPI_ROOT_ORIGIN_ALLOCATED;

	(व्योम)acpi_ut_release_mutex(ACPI_MTX_TABLES);
	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL_INIT(acpi_पुनः_स्मृतिate_root_table)

/*******************************************************************************
 *
 * FUNCTION:    acpi_get_table_header
 *
 * PARAMETERS:  signature           - ACPI signature of needed table
 *              instance            - Which instance (क्रम SSDTs)
 *              out_table_header    - The poपूर्णांकer to the where the table header
 *                                    is वापसed
 *
 * RETURN:      Status and a copy of the table header
 *
 * DESCRIPTION: Finds and वापसs an ACPI table header. Caller provides the
 *              memory where a copy of the header is to be वापसed
 *              (fixed length).
 *
 ******************************************************************************/
acpi_status
acpi_get_table_header(अक्षर *signature,
		      u32 instance, काष्ठा acpi_table_header *out_table_header)
अणु
	u32 i;
	u32 j;
	काष्ठा acpi_table_header *header;

	/* Parameter validation */

	अगर (!signature || !out_table_header) अणु
		वापस (AE_BAD_PARAMETER);
	पूर्ण

	/* Walk the root table list */

	क्रम (i = 0, j = 0; i < acpi_gbl_root_table_list.current_table_count;
	     i++) अणु
		अगर (!ACPI_COMPARE_NAMESEG
		    (&(acpi_gbl_root_table_list.tables[i].signature),
		     signature)) अणु
			जारी;
		पूर्ण

		अगर (++j < instance) अणु
			जारी;
		पूर्ण

		अगर (!acpi_gbl_root_table_list.tables[i].poपूर्णांकer) अणु
			अगर ((acpi_gbl_root_table_list.tables[i].flags &
			     ACPI_TABLE_ORIGIN_MASK) ==
			    ACPI_TABLE_ORIGIN_INTERNAL_PHYSICAL) अणु
				header =
				    acpi_os_map_memory(acpi_gbl_root_table_list.
						       tables[i].address,
						       माप(काष्ठा
							      acpi_table_header));
				अगर (!header) अणु
					वापस (AE_NO_MEMORY);
				पूर्ण

				स_नकल(out_table_header, header,
				       माप(काष्ठा acpi_table_header));
				acpi_os_unmap_memory(header,
						     माप(काष्ठा
							    acpi_table_header));
			पूर्ण अन्यथा अणु
				वापस (AE_NOT_FOUND);
			पूर्ण
		पूर्ण अन्यथा अणु
			स_नकल(out_table_header,
			       acpi_gbl_root_table_list.tables[i].poपूर्णांकer,
			       माप(काष्ठा acpi_table_header));
		पूर्ण
		वापस (AE_OK);
	पूर्ण

	वापस (AE_NOT_FOUND);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_get_table_header)

/*******************************************************************************
 *
 * FUNCTION:    acpi_get_table
 *
 * PARAMETERS:  signature           - ACPI signature of needed table
 *              instance            - Which instance (क्रम SSDTs)
 *              out_table           - Where the poपूर्णांकer to the table is वापसed
 *
 * RETURN:      Status and poपूर्णांकer to the requested table
 *
 * DESCRIPTION: Finds and verअगरies an ACPI table. Table must be in the
 *              RSDT/XSDT.
 *              Note that an early stage acpi_get_table() call must be paired
 *              with an early stage acpi_put_table() call. otherwise the table
 *              poपूर्णांकer mapped by the early stage mapping implementation may be
 *              erroneously unmapped by the late stage unmapping implementation
 *              in an acpi_put_table() invoked during the late stage.
 *
 ******************************************************************************/
acpi_status
acpi_get_table(अक्षर *signature,
	       u32 instance, काष्ठा acpi_table_header ** out_table)
अणु
	u32 i;
	u32 j;
	acpi_status status = AE_NOT_FOUND;
	काष्ठा acpi_table_desc *table_desc;

	/* Parameter validation */

	अगर (!signature || !out_table) अणु
		वापस (AE_BAD_PARAMETER);
	पूर्ण

	/*
	 * Note that the following line is required by some OSPMs, they only
	 * check अगर the वापसed table is शून्य instead of the वापसed status
	 * to determined अगर this function is succeeded.
	 */
	*out_table = शून्य;

	(व्योम)acpi_ut_acquire_mutex(ACPI_MTX_TABLES);

	/* Walk the root table list */

	क्रम (i = 0, j = 0; i < acpi_gbl_root_table_list.current_table_count;
	     i++) अणु
		table_desc = &acpi_gbl_root_table_list.tables[i];

		अगर (!ACPI_COMPARE_NAMESEG(&table_desc->signature, signature)) अणु
			जारी;
		पूर्ण

		अगर (++j < instance) अणु
			जारी;
		पूर्ण

		status = acpi_tb_get_table(table_desc, out_table);
		अवरोध;
	पूर्ण

	(व्योम)acpi_ut_release_mutex(ACPI_MTX_TABLES);
	वापस (status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_get_table)

/*******************************************************************************
 *
 * FUNCTION:    acpi_put_table
 *
 * PARAMETERS:  table               - The poपूर्णांकer to the table
 *
 * RETURN:      None
 *
 * DESCRIPTION: Release a table वापसed by acpi_get_table() and its clones.
 *              Note that it is not safe अगर this function was invoked after an
 *              uninstallation happened to the original table descriptor.
 *              Currently there is no OSPMs' requirement to handle such
 *              situations.
 *
 ******************************************************************************/
व्योम acpi_put_table(काष्ठा acpi_table_header *table)
अणु
	u32 i;
	काष्ठा acpi_table_desc *table_desc;

	ACPI_FUNCTION_TRACE(acpi_put_table);

	अगर (!table) अणु
		वापस_VOID;
	पूर्ण

	(व्योम)acpi_ut_acquire_mutex(ACPI_MTX_TABLES);

	/* Walk the root table list */

	क्रम (i = 0; i < acpi_gbl_root_table_list.current_table_count; i++) अणु
		table_desc = &acpi_gbl_root_table_list.tables[i];

		अगर (table_desc->poपूर्णांकer != table) अणु
			जारी;
		पूर्ण

		acpi_tb_put_table(table_desc);
		अवरोध;
	पूर्ण

	(व्योम)acpi_ut_release_mutex(ACPI_MTX_TABLES);
	वापस_VOID;
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_put_table)

/*******************************************************************************
 *
 * FUNCTION:    acpi_get_table_by_index
 *
 * PARAMETERS:  table_index         - Table index
 *              out_table           - Where the poपूर्णांकer to the table is वापसed
 *
 * RETURN:      Status and poपूर्णांकer to the requested table
 *
 * DESCRIPTION: Obtain a table by an index पूर्णांकo the global table list. Used
 *              पूर्णांकernally also.
 *
 ******************************************************************************/
acpi_status
acpi_get_table_by_index(u32 table_index, काष्ठा acpi_table_header **out_table)
अणु
	acpi_status status;

	ACPI_FUNCTION_TRACE(acpi_get_table_by_index);

	/* Parameter validation */

	अगर (!out_table) अणु
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	/*
	 * Note that the following line is required by some OSPMs, they only
	 * check अगर the वापसed table is शून्य instead of the वापसed status
	 * to determined अगर this function is succeeded.
	 */
	*out_table = शून्य;

	(व्योम)acpi_ut_acquire_mutex(ACPI_MTX_TABLES);

	/* Validate index */

	अगर (table_index >= acpi_gbl_root_table_list.current_table_count) अणु
		status = AE_BAD_PARAMETER;
		जाओ unlock_and_निकास;
	पूर्ण

	status =
	    acpi_tb_get_table(&acpi_gbl_root_table_list.tables[table_index],
			      out_table);

unlock_and_निकास:
	(व्योम)acpi_ut_release_mutex(ACPI_MTX_TABLES);
	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_get_table_by_index)

/*******************************************************************************
 *
 * FUNCTION:    acpi_install_table_handler
 *
 * PARAMETERS:  handler         - Table event handler
 *              context         - Value passed to the handler on each event
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Install a global table event handler.
 *
 ******************************************************************************/
acpi_status
acpi_install_table_handler(acpi_table_handler handler, व्योम *context)
अणु
	acpi_status status;

	ACPI_FUNCTION_TRACE(acpi_install_table_handler);

	अगर (!handler) अणु
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	status = acpi_ut_acquire_mutex(ACPI_MTX_EVENTS);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Don't allow more than one handler */

	अगर (acpi_gbl_table_handler) अणु
		status = AE_ALREADY_EXISTS;
		जाओ cleanup;
	पूर्ण

	/* Install the handler */

	acpi_gbl_table_handler = handler;
	acpi_gbl_table_handler_context = context;

cleanup:
	(व्योम)acpi_ut_release_mutex(ACPI_MTX_EVENTS);
	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_install_table_handler)

/*******************************************************************************
 *
 * FUNCTION:    acpi_हटाओ_table_handler
 *
 * PARAMETERS:  handler         - Table event handler that was installed
 *                                previously.
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Remove a table event handler
 *
 ******************************************************************************/
acpi_status acpi_हटाओ_table_handler(acpi_table_handler handler)
अणु
	acpi_status status;

	ACPI_FUNCTION_TRACE(acpi_हटाओ_table_handler);

	status = acpi_ut_acquire_mutex(ACPI_MTX_EVENTS);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Make sure that the installed handler is the same */

	अगर (!handler || handler != acpi_gbl_table_handler) अणु
		status = AE_BAD_PARAMETER;
		जाओ cleanup;
	पूर्ण

	/* Remove the handler */

	acpi_gbl_table_handler = शून्य;

cleanup:
	(व्योम)acpi_ut_release_mutex(ACPI_MTX_EVENTS);
	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_हटाओ_table_handler)
