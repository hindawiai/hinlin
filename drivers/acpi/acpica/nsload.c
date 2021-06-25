<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: nsload - namespace loading/expanding/contracting procedures
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acnamesp.h"
#समावेश "acdispat.h"
#समावेश "actables.h"
#समावेश "acinterp.h"

#घोषणा _COMPONENT          ACPI_NAMESPACE
ACPI_MODULE_NAME("nsload")

/* Local prototypes */
#अगर_घोषित ACPI_FUTURE_IMPLEMENTATION
acpi_status acpi_ns_unload_namespace(acpi_handle handle);

अटल acpi_status acpi_ns_delete_subtree(acpi_handle start_handle);
#पूर्ण_अगर

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_load_table
 *
 * PARAMETERS:  table_index     - Index क्रम table to be loaded
 *              node            - Owning NS node
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Load one ACPI table पूर्णांकo the namespace
 *
 ******************************************************************************/

acpi_status
acpi_ns_load_table(u32 table_index, काष्ठा acpi_namespace_node *node)
अणु
	acpi_status status;

	ACPI_FUNCTION_TRACE(ns_load_table);

	/* If table alपढ़ोy loaded पूर्णांकo namespace, just वापस */

	अगर (acpi_tb_is_table_loaded(table_index)) अणु
		status = AE_ALREADY_EXISTS;
		जाओ unlock;
	पूर्ण

	ACPI_DEBUG_PRINT((ACPI_DB_INFO,
			  "**** Loading table into namespace ****\n"));

	status = acpi_tb_allocate_owner_id(table_index);
	अगर (ACPI_FAILURE(status)) अणु
		जाओ unlock;
	पूर्ण

	/*
	 * Parse the table and load the namespace with all named
	 * objects found within. Control methods are NOT parsed
	 * at this समय. In fact, the control methods cannot be
	 * parsed until the entire namespace is loaded, because
	 * अगर a control method makes a क्रमward reference (call)
	 * to another control method, we can't जारी parsing
	 * because we करोn't know how many arguments to parse next!
	 */
	status = acpi_ns_parse_table(table_index, node);
	अगर (ACPI_SUCCESS(status)) अणु
		acpi_tb_set_table_loaded_flag(table_index, TRUE);
	पूर्ण अन्यथा अणु
		/*
		 * On error, delete any namespace objects created by this table.
		 * We cannot initialize these objects, so delete them. There are
		 * a couple of especially bad हालs:
		 * AE_ALREADY_EXISTS - namespace collision.
		 * AE_NOT_FOUND - the target of a Scope चालक करोes not
		 * exist. This target of Scope must alपढ़ोy exist in the
		 * namespace, as per the ACPI specअगरication.
		 */
		acpi_ns_delete_namespace_by_owner(acpi_gbl_root_table_list.
						  tables[table_index].owner_id);

		acpi_tb_release_owner_id(table_index);
		वापस_ACPI_STATUS(status);
	पूर्ण

unlock:
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/*
	 * Now we can parse the control methods. We always parse
	 * them here क्रम a sanity check, and अगर configured क्रम
	 * just-in-समय parsing, we delete the control method
	 * parse trees.
	 */
	ACPI_DEBUG_PRINT((ACPI_DB_INFO,
			  "**** Begin Table Object Initialization\n"));

	acpi_ex_enter_पूर्णांकerpreter();
	status = acpi_ds_initialize_objects(table_index, node);
	acpi_ex_निकास_पूर्णांकerpreter();

	ACPI_DEBUG_PRINT((ACPI_DB_INFO,
			  "**** Completed Table Object Initialization\n"));

	वापस_ACPI_STATUS(status);
पूर्ण

#अगर_घोषित ACPI_OBSOLETE_FUNCTIONS
/*******************************************************************************
 *
 * FUNCTION:    acpi_load_namespace
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Load the name space from what ever is poपूर्णांकed to by DSDT.
 *              (DSDT poपूर्णांकs to either the BIOS or a buffer.)
 *
 ******************************************************************************/

acpi_status acpi_ns_load_namespace(व्योम)
अणु
	acpi_status status;

	ACPI_FUNCTION_TRACE(acpi_load_name_space);

	/* There must be at least a DSDT installed */

	अगर (acpi_gbl_DSDT == शून्य) अणु
		ACPI_ERROR((AE_INFO, "DSDT is not in memory"));
		वापस_ACPI_STATUS(AE_NO_ACPI_TABLES);
	पूर्ण

	/*
	 * Load the namespace. The DSDT is required,
	 * but the SSDT and PSDT tables are optional.
	 */
	status = acpi_ns_load_table_by_type(ACPI_TABLE_ID_DSDT);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Ignore exceptions from these */

	(व्योम)acpi_ns_load_table_by_type(ACPI_TABLE_ID_SSDT);
	(व्योम)acpi_ns_load_table_by_type(ACPI_TABLE_ID_PSDT);

	ACPI_DEBUG_PRINT_RAW((ACPI_DB_INIT,
			      "ACPI Namespace successfully loaded at root %p\n",
			      acpi_gbl_root_node));

	वापस_ACPI_STATUS(status);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित ACPI_FUTURE_IMPLEMENTATION
/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_delete_subtree
 *
 * PARAMETERS:  start_handle        - Handle in namespace where search begins
 *
 * RETURNS      Status
 *
 * DESCRIPTION: Walks the namespace starting at the given handle and deletes
 *              all objects, entries, and scopes in the entire subtree.
 *
 *              Namespace/Interpreter should be locked or the subप्रणाली should
 *              be in shutकरोwn beक्रमe this routine is called.
 *
 ******************************************************************************/

अटल acpi_status acpi_ns_delete_subtree(acpi_handle start_handle)
अणु
	acpi_status status;
	acpi_handle child_handle;
	acpi_handle parent_handle;
	acpi_handle next_child_handle;
	acpi_handle dummy;
	u32 level;

	ACPI_FUNCTION_TRACE(ns_delete_subtree);

	parent_handle = start_handle;
	child_handle = शून्य;
	level = 1;

	/*
	 * Traverse the tree of objects until we bubble back up
	 * to where we started.
	 */
	जबतक (level > 0) अणु

		/* Attempt to get the next object in this scope */

		status = acpi_get_next_object(ACPI_TYPE_ANY, parent_handle,
					      child_handle, &next_child_handle);

		child_handle = next_child_handle;

		/* Did we get a new object? */

		अगर (ACPI_SUCCESS(status)) अणु

			/* Check अगर this object has any children */

			अगर (ACPI_SUCCESS
			    (acpi_get_next_object
			     (ACPI_TYPE_ANY, child_handle, शून्य, &dummy))) अणु
				/*
				 * There is at least one child of this object,
				 * visit the object
				 */
				level++;
				parent_handle = child_handle;
				child_handle = शून्य;
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * No more children in this object, go back up to
			 * the object's parent
			 */
			level--;

			/* Delete all children now */

			acpi_ns_delete_children(child_handle);

			child_handle = parent_handle;
			status = acpi_get_parent(parent_handle, &parent_handle);
			अगर (ACPI_FAILURE(status)) अणु
				वापस_ACPI_STATUS(status);
			पूर्ण
		पूर्ण
	पूर्ण

	/* Now delete the starting object, and we are करोne */

	acpi_ns_हटाओ_node(child_handle);
	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 *  FUNCTION:       acpi_ns_unload_name_space
 *
 *  PARAMETERS:     handle          - Root of namespace subtree to be deleted
 *
 *  RETURN:         Status
 *
 *  DESCRIPTION:    Shrinks the namespace, typically in response to an unकरोcking
 *                  event. Deletes an entire subtree starting from (and
 *                  including) the given handle.
 *
 ******************************************************************************/

acpi_status acpi_ns_unload_namespace(acpi_handle handle)
अणु
	acpi_status status;

	ACPI_FUNCTION_TRACE(ns_unload_name_space);

	/* Parameter validation */

	अगर (!acpi_gbl_root_node) अणु
		वापस_ACPI_STATUS(AE_NO_NAMESPACE);
	पूर्ण

	अगर (!handle) अणु
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	/* This function करोes the real work */

	status = acpi_ns_delete_subtree(handle);
	वापस_ACPI_STATUS(status);
पूर्ण
#पूर्ण_अगर
