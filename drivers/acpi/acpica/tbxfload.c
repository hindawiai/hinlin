<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: tbxfload - Table load/unload बाह्यal पूर्णांकerfaces
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#घोषणा EXPORT_ACPI_INTERFACES

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acnamesp.h"
#समावेश "actables.h"
#समावेश "acevents.h"

#घोषणा _COMPONENT          ACPI_TABLES
ACPI_MODULE_NAME("tbxfload")

/*******************************************************************************
 *
 * FUNCTION:    acpi_load_tables
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Load the ACPI tables from the RSDT/XSDT
 *
 ******************************************************************************/
acpi_status ACPI_INIT_FUNCTION acpi_load_tables(व्योम)
अणु
	acpi_status status;

	ACPI_FUNCTION_TRACE(acpi_load_tables);

	/*
	 * Install the शेष operation region handlers. These are the
	 * handlers that are defined by the ACPI specअगरication to be
	 * "always accessible" -- namely, प्रणाली_memory, प्रणाली_IO, and
	 * PCI_Config. This also means that no _REG methods need to be
	 * run क्रम these address spaces. We need to have these handlers
	 * installed beक्रमe any AML code can be executed, especially any
	 * module-level code (11/2015).
	 * Note that we allow OSPMs to install their own region handlers
	 * between acpi_initialize_subप्रणाली() and acpi_load_tables() to use
	 * their customized शेष region handlers.
	 */
	status = acpi_ev_install_region_handlers();
	अगर (ACPI_FAILURE(status)) अणु
		ACPI_EXCEPTION((AE_INFO, status,
				"During Region initialization"));
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Load the namespace from the tables */

	status = acpi_tb_load_namespace();

	/* Don't let single failures पात the load */

	अगर (status == AE_CTRL_TERMINATE) अणु
		status = AE_OK;
	पूर्ण

	अगर (ACPI_FAILURE(status)) अणु
		ACPI_EXCEPTION((AE_INFO, status,
				"While loading namespace from ACPI tables"));
	पूर्ण

	/*
	 * Initialize the objects in the namespace that reमुख्य uninitialized.
	 * This runs the executable AML that may be part of the declaration of
	 * these name objects:
	 *     operation_regions, buffer_fields, Buffers, and Packages.
	 *
	 */
	status = acpi_ns_initialize_objects();
	अगर (ACPI_SUCCESS(status)) अणु
		acpi_gbl_namespace_initialized = TRUE;
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL_INIT(acpi_load_tables)

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_load_namespace
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Load the namespace from the DSDT and all SSDTs/PSDTs found in
 *              the RSDT/XSDT.
 *
 ******************************************************************************/
acpi_status acpi_tb_load_namespace(व्योम)
अणु
	acpi_status status;
	u32 i;
	काष्ठा acpi_table_header *new_dsdt;
	काष्ठा acpi_table_desc *table;
	u32 tables_loaded = 0;
	u32 tables_failed = 0;

	ACPI_FUNCTION_TRACE(tb_load_namespace);

	(व्योम)acpi_ut_acquire_mutex(ACPI_MTX_TABLES);

	/*
	 * Load the namespace. The DSDT is required, but any SSDT and
	 * PSDT tables are optional. Verअगरy the DSDT.
	 */
	table = &acpi_gbl_root_table_list.tables[acpi_gbl_dsdt_index];

	अगर (!acpi_gbl_root_table_list.current_table_count ||
	    !ACPI_COMPARE_NAMESEG(table->signature.ascii, ACPI_SIG_DSDT) ||
	    ACPI_FAILURE(acpi_tb_validate_table(table))) अणु
		status = AE_NO_ACPI_TABLES;
		जाओ unlock_and_निकास;
	पूर्ण

	/*
	 * Save the DSDT poपूर्णांकer क्रम simple access. This is the mapped memory
	 * address. We must take care here because the address of the .Tables
	 * array can change dynamically as tables are loaded at run-समय. Note:
	 * .Poपूर्णांकer field is not validated until after call to acpi_tb_validate_table.
	 */
	acpi_gbl_DSDT = table->poपूर्णांकer;

	/*
	 * Optionally copy the entire DSDT to local memory (instead of simply
	 * mapping it.) There are some BIOSs that corrupt or replace the original
	 * DSDT, creating the need क्रम this option. Default is FALSE, करो not copy
	 * the DSDT.
	 */
	अगर (acpi_gbl_copy_dsdt_locally) अणु
		new_dsdt = acpi_tb_copy_dsdt(acpi_gbl_dsdt_index);
		अगर (new_dsdt) अणु
			acpi_gbl_DSDT = new_dsdt;
		पूर्ण
	पूर्ण

	/*
	 * Save the original DSDT header क्रम detection of table corruption
	 * and/or replacement of the DSDT from outside the OS.
	 */
	स_नकल(&acpi_gbl_original_dsdt_header, acpi_gbl_DSDT,
	       माप(काष्ठा acpi_table_header));

	/* Load and parse tables */

	(व्योम)acpi_ut_release_mutex(ACPI_MTX_TABLES);
	status = acpi_ns_load_table(acpi_gbl_dsdt_index, acpi_gbl_root_node);
	(व्योम)acpi_ut_acquire_mutex(ACPI_MTX_TABLES);
	अगर (ACPI_FAILURE(status)) अणु
		ACPI_EXCEPTION((AE_INFO, status, "[DSDT] table load failed"));
		tables_failed++;
	पूर्ण अन्यथा अणु
		tables_loaded++;
	पूर्ण

	/* Load any SSDT or PSDT tables. Note: Loop leaves tables locked */

	क्रम (i = 0; i < acpi_gbl_root_table_list.current_table_count; ++i) अणु
		table = &acpi_gbl_root_table_list.tables[i];

		अगर (!table->address ||
		    (!ACPI_COMPARE_NAMESEG
		     (table->signature.ascii, ACPI_SIG_SSDT)
		     && !ACPI_COMPARE_NAMESEG(table->signature.ascii,
					      ACPI_SIG_PSDT)
		     && !ACPI_COMPARE_NAMESEG(table->signature.ascii,
					      ACPI_SIG_OSDT))
		    || ACPI_FAILURE(acpi_tb_validate_table(table))) अणु
			जारी;
		पूर्ण

		/* Ignore errors जबतक loading tables, get as many as possible */

		(व्योम)acpi_ut_release_mutex(ACPI_MTX_TABLES);
		status = acpi_ns_load_table(i, acpi_gbl_root_node);
		(व्योम)acpi_ut_acquire_mutex(ACPI_MTX_TABLES);
		अगर (ACPI_FAILURE(status)) अणु
			ACPI_EXCEPTION((AE_INFO, status,
					"(%4.4s:%8.8s) while loading table",
					table->signature.ascii,
					table->poपूर्णांकer->oem_table_id));

			tables_failed++;

			ACPI_DEBUG_PRINT_RAW((ACPI_DB_INIT,
					      "Table [%4.4s:%8.8s] (id FF) - Table namespace load failed\n\n",
					      table->signature.ascii,
					      table->poपूर्णांकer->oem_table_id));
		पूर्ण अन्यथा अणु
			tables_loaded++;
		पूर्ण
	पूर्ण

	अगर (!tables_failed) अणु
		ACPI_INFO(("%u ACPI AML tables successfully acquired and loaded", tables_loaded));
	पूर्ण अन्यथा अणु
		ACPI_ERROR((AE_INFO,
			    "%u table load failures, %u successful",
			    tables_failed, tables_loaded));

		/* Indicate at least one failure */

		status = AE_CTRL_TERMINATE;
	पूर्ण

#अगर_घोषित ACPI_APPLICATION
	ACPI_DEBUG_PRINT_RAW((ACPI_DB_INIT, "\n"));
#पूर्ण_अगर

unlock_and_निकास:
	(व्योम)acpi_ut_release_mutex(ACPI_MTX_TABLES);
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_install_table
 *
 * PARAMETERS:  address             - Address of the ACPI table to be installed.
 *              physical            - Whether the address is a physical table
 *                                    address or not
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Dynamically install an ACPI table.
 *              Note: This function should only be invoked after
 *                    acpi_initialize_tables() and beक्रमe acpi_load_tables().
 *
 ******************************************************************************/

acpi_status ACPI_INIT_FUNCTION
acpi_install_table(acpi_physical_address address, u8 physical)
अणु
	acpi_status status;
	u8 flags;
	u32 table_index;

	ACPI_FUNCTION_TRACE(acpi_install_table);

	अगर (physical) अणु
		flags = ACPI_TABLE_ORIGIN_INTERNAL_PHYSICAL;
	पूर्ण अन्यथा अणु
		flags = ACPI_TABLE_ORIGIN_EXTERNAL_VIRTUAL;
	पूर्ण

	status = acpi_tb_install_standard_table(address, flags,
						FALSE, FALSE, &table_index);

	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL_INIT(acpi_install_table)

/*******************************************************************************
 *
 * FUNCTION:    acpi_load_table
 *
 * PARAMETERS:  table               - Poपूर्णांकer to a buffer containing the ACPI
 *                                    table to be loaded.
 *              table_idx           - Poपूर्णांकer to a u32 क्रम storing the table
 *                                    index, might be शून्य
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Dynamically load an ACPI table from the caller's buffer. Must
 *              be a valid ACPI table with a valid ACPI table header.
 *              Note1: Mainly पूर्णांकended to support hotplug addition of SSDTs.
 *              Note2: Does not copy the incoming table. User is responsible
 *              to ensure that the table is not deleted or unmapped.
 *
 ******************************************************************************/
acpi_status acpi_load_table(काष्ठा acpi_table_header *table, u32 *table_idx)
अणु
	acpi_status status;
	u32 table_index;

	ACPI_FUNCTION_TRACE(acpi_load_table);

	/* Parameter validation */

	अगर (!table) अणु
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	/* Install the table and load it पूर्णांकo the namespace */

	ACPI_INFO(("Host-directed Dynamic ACPI Table Load:"));
	status = acpi_tb_install_and_load_table(ACPI_PTR_TO_PHYSADDR(table),
						ACPI_TABLE_ORIGIN_EXTERNAL_VIRTUAL,
						FALSE, &table_index);
	अगर (table_idx) अणु
		*table_idx = table_index;
	पूर्ण

	अगर (ACPI_SUCCESS(status)) अणु

		/* Complete the initialization/resolution of new objects */

		acpi_ns_initialize_objects();
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_load_table)

/*******************************************************************************
 *
 * FUNCTION:    acpi_unload_parent_table
 *
 * PARAMETERS:  object              - Handle to any namespace object owned by
 *                                    the table to be unloaded
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Via any namespace object within an SSDT or OEMx table, unloads
 *              the table and deletes all namespace objects associated with
 *              that table. Unloading of the DSDT is not allowed.
 *              Note: Mainly पूर्णांकended to support hotplug removal of SSDTs.
 *
 ******************************************************************************/
acpi_status acpi_unload_parent_table(acpi_handle object)
अणु
	काष्ठा acpi_namespace_node *node =
	    ACPI_CAST_PTR(काष्ठा acpi_namespace_node, object);
	acpi_status status = AE_NOT_EXIST;
	acpi_owner_id owner_id;
	u32 i;

	ACPI_FUNCTION_TRACE(acpi_unload_parent_table);

	/* Parameter validation */

	अगर (!object) अणु
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	/*
	 * The node owner_id is currently the same as the parent table ID.
	 * However, this could change in the future.
	 */
	owner_id = node->owner_id;
	अगर (!owner_id) अणु

		/* owner_id==0 means DSDT is the owner. DSDT cannot be unloaded */

		वापस_ACPI_STATUS(AE_TYPE);
	पूर्ण

	/* Must acquire the table lock during this operation */

	status = acpi_ut_acquire_mutex(ACPI_MTX_TABLES);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Find the table in the global table list */

	क्रम (i = 0; i < acpi_gbl_root_table_list.current_table_count; i++) अणु
		अगर (owner_id != acpi_gbl_root_table_list.tables[i].owner_id) अणु
			जारी;
		पूर्ण

		/*
		 * Allow unload of SSDT and OEMx tables only. Do not allow unload
		 * of the DSDT. No other types of tables should get here, since
		 * only these types can contain AML and thus are the only types
		 * that can create namespace objects.
		 */
		अगर (ACPI_COMPARE_NAMESEG
		    (acpi_gbl_root_table_list.tables[i].signature.ascii,
		     ACPI_SIG_DSDT)) अणु
			status = AE_TYPE;
			अवरोध;
		पूर्ण

		(व्योम)acpi_ut_release_mutex(ACPI_MTX_TABLES);
		status = acpi_tb_unload_table(i);
		(व्योम)acpi_ut_acquire_mutex(ACPI_MTX_TABLES);
		अवरोध;
	पूर्ण

	(व्योम)acpi_ut_release_mutex(ACPI_MTX_TABLES);
	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_unload_parent_table)
/*******************************************************************************
 *
 * FUNCTION:    acpi_unload_table
 *
 * PARAMETERS:  table_index         - Index as वापसed by acpi_load_table
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Via the table_index representing an SSDT or OEMx table, unloads
 *              the table and deletes all namespace objects associated with
 *              that table. Unloading of the DSDT is not allowed.
 *              Note: Mainly पूर्णांकended to support hotplug removal of SSDTs.
 *
 ******************************************************************************/
acpi_status acpi_unload_table(u32 table_index)
अणु
	acpi_status status;

	ACPI_FUNCTION_TRACE(acpi_unload_table);

	अगर (table_index == 1) अणु

		/* table_index==1 means DSDT is the owner. DSDT cannot be unloaded */

		वापस_ACPI_STATUS(AE_TYPE);
	पूर्ण

	status = acpi_tb_unload_table(table_index);
	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_unload_table)
