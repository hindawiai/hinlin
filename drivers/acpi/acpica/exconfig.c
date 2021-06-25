<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: exconfig - Namespace reconfiguration (Load/Unload opcodes)
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acinterp.h"
#समावेश "acnamesp.h"
#समावेश "actables.h"
#समावेश "acdispat.h"
#समावेश "acevents.h"
#समावेश "amlcode.h"

#घोषणा _COMPONENT          ACPI_EXECUTER
ACPI_MODULE_NAME("exconfig")

/* Local prototypes */
अटल acpi_status
acpi_ex_add_table(u32 table_index, जोड़ acpi_opeअक्रम_object **ddb_handle);

अटल acpi_status
acpi_ex_region_पढ़ो(जोड़ acpi_opeअक्रम_object *obj_desc,
		    u32 length, u8 *buffer);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_add_table
 *
 * PARAMETERS:  table               - Poपूर्णांकer to raw table
 *              parent_node         - Where to load the table (scope)
 *              ddb_handle          - Where to वापस the table handle.
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Common function to Install and Load an ACPI table with a
 *              वापसed table handle.
 *
 ******************************************************************************/

अटल acpi_status
acpi_ex_add_table(u32 table_index, जोड़ acpi_opeअक्रम_object **ddb_handle)
अणु
	जोड़ acpi_opeअक्रम_object *obj_desc;

	ACPI_FUNCTION_TRACE(ex_add_table);

	/* Create an object to be the table handle */

	obj_desc = acpi_ut_create_पूर्णांकernal_object(ACPI_TYPE_LOCAL_REFERENCE);
	अगर (!obj_desc) अणु
		वापस_ACPI_STATUS(AE_NO_MEMORY);
	पूर्ण

	/* Init the table handle */

	obj_desc->common.flags |= AOPOBJ_DATA_VALID;
	obj_desc->reference.class = ACPI_REFCLASS_TABLE;
	obj_desc->reference.value = table_index;
	*ddb_handle = obj_desc;
	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_load_table_op
 *
 * PARAMETERS:  walk_state          - Current state with opeअक्रमs
 *              वापस_desc         - Where to store the वापस object
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Load an ACPI table from the RSDT/XSDT
 *
 ******************************************************************************/

acpi_status
acpi_ex_load_table_op(काष्ठा acpi_walk_state *walk_state,
		      जोड़ acpi_opeअक्रम_object **वापस_desc)
अणु
	acpi_status status;
	जोड़ acpi_opeअक्रम_object **opeअक्रम = &walk_state->opeअक्रमs[0];
	काष्ठा acpi_namespace_node *parent_node;
	काष्ठा acpi_namespace_node *start_node;
	काष्ठा acpi_namespace_node *parameter_node = शून्य;
	जोड़ acpi_opeअक्रम_object *ddb_handle;
	u32 table_index;

	ACPI_FUNCTION_TRACE(ex_load_table_op);

	/* Find the ACPI table in the RSDT/XSDT */

	acpi_ex_निकास_पूर्णांकerpreter();
	status = acpi_tb_find_table(opeअक्रम[0]->string.poपूर्णांकer,
				    opeअक्रम[1]->string.poपूर्णांकer,
				    opeअक्रम[2]->string.poपूर्णांकer, &table_index);
	acpi_ex_enter_पूर्णांकerpreter();
	अगर (ACPI_FAILURE(status)) अणु
		अगर (status != AE_NOT_FOUND) अणु
			वापस_ACPI_STATUS(status);
		पूर्ण

		/* Table not found, वापस an Integer=0 and AE_OK */

		ddb_handle = acpi_ut_create_पूर्णांकeger_object((u64) 0);
		अगर (!ddb_handle) अणु
			वापस_ACPI_STATUS(AE_NO_MEMORY);
		पूर्ण

		*वापस_desc = ddb_handle;
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	/* Default nodes */

	start_node = walk_state->scope_info->scope.node;
	parent_node = acpi_gbl_root_node;

	/* root_path (optional parameter) */

	अगर (opeअक्रम[3]->string.length > 0) अणु
		/*
		 * Find the node referenced by the root_path_string. This is the
		 * location within the namespace where the table will be loaded.
		 */
		status = acpi_ns_get_node_unlocked(start_node,
						   opeअक्रम[3]->string.poपूर्णांकer,
						   ACPI_NS_SEARCH_PARENT,
						   &parent_node);
		अगर (ACPI_FAILURE(status)) अणु
			वापस_ACPI_STATUS(status);
		पूर्ण
	पूर्ण

	/* parameter_path (optional parameter) */

	अगर (opeअक्रम[4]->string.length > 0) अणु
		अगर ((opeअक्रम[4]->string.poपूर्णांकer[0] != AML_ROOT_PREFIX) &&
		    (opeअक्रम[4]->string.poपूर्णांकer[0] != AML_PARENT_PREFIX)) अणु
			/*
			 * Path is not असलolute, so it will be relative to the node
			 * referenced by the root_path_string (or the NS root अगर omitted)
			 */
			start_node = parent_node;
		पूर्ण

		/* Find the node referenced by the parameter_path_string */

		status = acpi_ns_get_node_unlocked(start_node,
						   opeअक्रम[4]->string.poपूर्णांकer,
						   ACPI_NS_SEARCH_PARENT,
						   &parameter_node);
		अगर (ACPI_FAILURE(status)) अणु
			वापस_ACPI_STATUS(status);
		पूर्ण
	पूर्ण

	/* Load the table पूर्णांकo the namespace */

	ACPI_INFO(("Dynamic OEM Table Load:"));
	acpi_ex_निकास_पूर्णांकerpreter();
	status = acpi_tb_load_table(table_index, parent_node);
	acpi_ex_enter_पूर्णांकerpreter();
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	status = acpi_ex_add_table(table_index, &ddb_handle);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Complete the initialization/resolution of new objects */

	acpi_ex_निकास_पूर्णांकerpreter();
	acpi_ns_initialize_objects();
	acpi_ex_enter_पूर्णांकerpreter();

	/* Parameter Data (optional) */

	अगर (parameter_node) अणु

		/* Store the parameter data पूर्णांकo the optional parameter object */

		status = acpi_ex_store(opeअक्रम[5],
				       ACPI_CAST_PTR(जोड़ acpi_opeअक्रम_object,
						     parameter_node),
				       walk_state);
		अगर (ACPI_FAILURE(status)) अणु
			(व्योम)acpi_ex_unload_table(ddb_handle);

			acpi_ut_हटाओ_reference(ddb_handle);
			वापस_ACPI_STATUS(status);
		पूर्ण
	पूर्ण

	*वापस_desc = ddb_handle;
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_region_पढ़ो
 *
 * PARAMETERS:  obj_desc        - Region descriptor
 *              length          - Number of bytes to पढ़ो
 *              buffer          - Poपूर्णांकer to where to put the data
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Read data from an operation region. The पढ़ो starts from the
 *              beginning of the region.
 *
 ******************************************************************************/

अटल acpi_status
acpi_ex_region_पढ़ो(जोड़ acpi_opeअक्रम_object *obj_desc, u32 length, u8 *buffer)
अणु
	acpi_status status;
	u64 value;
	u32 region_offset = 0;
	u32 i;

	/* Bytewise पढ़ोs */

	क्रम (i = 0; i < length; i++) अणु
		status =
		    acpi_ev_address_space_dispatch(obj_desc, शून्य, ACPI_READ,
						   region_offset, 8, &value);
		अगर (ACPI_FAILURE(status)) अणु
			वापस (status);
		पूर्ण

		*buffer = (u8)value;
		buffer++;
		region_offset++;
	पूर्ण

	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_load_op
 *
 * PARAMETERS:  obj_desc        - Region or Buffer/Field where the table will be
 *                                obtained
 *              target          - Where a handle to the table will be stored
 *              walk_state      - Current state
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Load an ACPI table from a field or operation region
 *
 * NOTE: Region Fields (Field, bank_field, index_fields) are resolved to buffer
 *       objects beक्रमe this code is reached.
 *
 *       If source is an operation region, it must refer to प्रणाली_memory, as
 *       per the ACPI specअगरication.
 *
 ******************************************************************************/

acpi_status
acpi_ex_load_op(जोड़ acpi_opeअक्रम_object *obj_desc,
		जोड़ acpi_opeअक्रम_object *target,
		काष्ठा acpi_walk_state *walk_state)
अणु
	जोड़ acpi_opeअक्रम_object *ddb_handle;
	काष्ठा acpi_table_header *table_header;
	काष्ठा acpi_table_header *table;
	u32 table_index;
	acpi_status status;
	u32 length;

	ACPI_FUNCTION_TRACE(ex_load_op);

	/* Source Object can be either an op_region or a Buffer/Field */

	चयन (obj_desc->common.type) अणु
	हाल ACPI_TYPE_REGION:

		ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
				  "Load table from Region %p\n", obj_desc));

		/* Region must be प्रणाली_memory (from ACPI spec) */

		अगर (obj_desc->region.space_id != ACPI_ADR_SPACE_SYSTEM_MEMORY) अणु
			वापस_ACPI_STATUS(AE_AML_OPERAND_TYPE);
		पूर्ण

		/*
		 * If the Region Address and Length have not been previously
		 * evaluated, evaluate them now and save the results.
		 */
		अगर (!(obj_desc->common.flags & AOPOBJ_DATA_VALID)) अणु
			status = acpi_ds_get_region_arguments(obj_desc);
			अगर (ACPI_FAILURE(status)) अणु
				वापस_ACPI_STATUS(status);
			पूर्ण
		पूर्ण

		/* Get the table header first so we can get the table length */

		table_header = ACPI_ALLOCATE(माप(काष्ठा acpi_table_header));
		अगर (!table_header) अणु
			वापस_ACPI_STATUS(AE_NO_MEMORY);
		पूर्ण

		status =
		    acpi_ex_region_पढ़ो(obj_desc,
					माप(काष्ठा acpi_table_header),
					ACPI_CAST_PTR(u8, table_header));
		length = table_header->length;
		ACPI_FREE(table_header);

		अगर (ACPI_FAILURE(status)) अणु
			वापस_ACPI_STATUS(status);
		पूर्ण

		/* Must have at least an ACPI table header */

		अगर (length < माप(काष्ठा acpi_table_header)) अणु
			वापस_ACPI_STATUS(AE_INVALID_TABLE_LENGTH);
		पूर्ण

		/*
		 * The original implementation simply mapped the table, with no copy.
		 * However, the memory region is not guaranteed to reमुख्य stable and
		 * we must copy the table to a local buffer. For example, the memory
		 * region is corrupted after suspend on some machines. Dynamically
		 * loaded tables are usually small, so this overhead is minimal.
		 *
		 * The latest implementation (5/2009) करोes not use a mapping at all.
		 * We use the low-level operation region पूर्णांकerface to पढ़ो the table
		 * instead of the obvious optimization of using a direct mapping.
		 * This मुख्यtains a consistent use of operation regions across the
		 * entire subप्रणाली. This is important अगर additional processing must
		 * be perक्रमmed in the (possibly user-installed) operation region
		 * handler. For example, acpi_exec and ASLTS depend on this.
		 */

		/* Allocate a buffer क्रम the table */

		table = ACPI_ALLOCATE(length);
		अगर (!table) अणु
			वापस_ACPI_STATUS(AE_NO_MEMORY);
		पूर्ण

		/* Read the entire table */

		status = acpi_ex_region_पढ़ो(obj_desc, length,
					     ACPI_CAST_PTR(u8, table));
		अगर (ACPI_FAILURE(status)) अणु
			ACPI_FREE(table);
			वापस_ACPI_STATUS(status);
		पूर्ण
		अवरोध;

	हाल ACPI_TYPE_BUFFER:	/* Buffer or resolved region_field */

		ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
				  "Load table from Buffer or Field %p\n",
				  obj_desc));

		/* Must have at least an ACPI table header */

		अगर (obj_desc->buffer.length < माप(काष्ठा acpi_table_header)) अणु
			वापस_ACPI_STATUS(AE_INVALID_TABLE_LENGTH);
		पूर्ण

		/* Get the actual table length from the table header */

		table_header =
		    ACPI_CAST_PTR(काष्ठा acpi_table_header,
				  obj_desc->buffer.poपूर्णांकer);
		length = table_header->length;

		/* Table cannot extend beyond the buffer */

		अगर (length > obj_desc->buffer.length) अणु
			वापस_ACPI_STATUS(AE_AML_BUFFER_LIMIT);
		पूर्ण
		अगर (length < माप(काष्ठा acpi_table_header)) अणु
			वापस_ACPI_STATUS(AE_INVALID_TABLE_LENGTH);
		पूर्ण

		/*
		 * Copy the table from the buffer because the buffer could be
		 * modअगरied or even deleted in the future
		 */
		table = ACPI_ALLOCATE(length);
		अगर (!table) अणु
			वापस_ACPI_STATUS(AE_NO_MEMORY);
		पूर्ण

		स_नकल(table, table_header, length);
		अवरोध;

	शेष:

		वापस_ACPI_STATUS(AE_AML_OPERAND_TYPE);
	पूर्ण

	/* Install the new table पूर्णांकo the local data काष्ठाures */

	ACPI_INFO(("Dynamic OEM Table Load:"));
	acpi_ex_निकास_पूर्णांकerpreter();
	status = acpi_tb_install_and_load_table(ACPI_PTR_TO_PHYSADDR(table),
						ACPI_TABLE_ORIGIN_INTERNAL_VIRTUAL,
						TRUE, &table_index);
	acpi_ex_enter_पूर्णांकerpreter();
	अगर (ACPI_FAILURE(status)) अणु

		/* Delete allocated table buffer */

		ACPI_FREE(table);
		वापस_ACPI_STATUS(status);
	पूर्ण

	/*
	 * Add the table to the namespace.
	 *
	 * Note: Load the table objects relative to the root of the namespace.
	 * This appears to go against the ACPI specअगरication, but we करो it क्रम
	 * compatibility with other ACPI implementations.
	 */
	status = acpi_ex_add_table(table_index, &ddb_handle);
	अगर (ACPI_FAILURE(status)) अणु

		/* On error, table_ptr was deallocated above */

		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Complete the initialization/resolution of new objects */

	acpi_ex_निकास_पूर्णांकerpreter();
	acpi_ns_initialize_objects();
	acpi_ex_enter_पूर्णांकerpreter();

	/* Store the ddb_handle पूर्णांकo the Target opeअक्रम */

	status = acpi_ex_store(ddb_handle, target, walk_state);
	अगर (ACPI_FAILURE(status)) अणु
		(व्योम)acpi_ex_unload_table(ddb_handle);

		/* table_ptr was deallocated above */

		acpi_ut_हटाओ_reference(ddb_handle);
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Remove the reference by added by acpi_ex_store above */

	acpi_ut_हटाओ_reference(ddb_handle);
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_unload_table
 *
 * PARAMETERS:  ddb_handle          - Handle to a previously loaded table
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Unload an ACPI table
 *
 ******************************************************************************/

acpi_status acpi_ex_unload_table(जोड़ acpi_opeअक्रम_object *ddb_handle)
अणु
	acpi_status status = AE_OK;
	जोड़ acpi_opeअक्रम_object *table_desc = ddb_handle;
	u32 table_index;

	ACPI_FUNCTION_TRACE(ex_unload_table);

	/*
	 * Temporarily emit a warning so that the ASL क्रम the machine can be
	 * hopefully obtained. This is to say that the Unload() चालक is
	 * extremely rare अगर not completely unused.
	 */
	ACPI_WARNING((AE_INFO, "Received request to unload an ACPI table"));

	/*
	 * May 2018: Unload is no दीर्घer supported क्रम the following reasons:
	 * 1) A correct implementation on some hosts may not be possible.
	 * 2) Other ACPI implementations करो not correctly/fully support it.
	 * 3) It requires host device driver support which करोes not exist.
	 *    (To properly support namespace unload out from underneath.)
	 * 4) This AML चालक has never been seen in the field.
	 */
	ACPI_EXCEPTION((AE_INFO, AE_NOT_IMPLEMENTED,
			"AML Unload operator is not supported"));

	/*
	 * Validate the handle
	 * Although the handle is partially validated in acpi_ex_reconfiguration()
	 * when it calls acpi_ex_resolve_opeअक्रमs(), the handle is more completely
	 * validated here.
	 *
	 * Handle must be a valid opeअक्रम object of type reference. Also, the
	 * ddb_handle must still be marked valid (table has not been previously
	 * unloaded)
	 */
	अगर ((!ddb_handle) ||
	    (ACPI_GET_DESCRIPTOR_TYPE(ddb_handle) != ACPI_DESC_TYPE_OPERAND) ||
	    (ddb_handle->common.type != ACPI_TYPE_LOCAL_REFERENCE) ||
	    (!(ddb_handle->common.flags & AOPOBJ_DATA_VALID))) अणु
		वापस_ACPI_STATUS(AE_AML_OPERAND_TYPE);
	पूर्ण

	/* Get the table index from the ddb_handle */

	table_index = table_desc->reference.value;

	/*
	 * Release the पूर्णांकerpreter lock so that the table lock won't have
	 * strict order requirement against it.
	 */
	acpi_ex_निकास_पूर्णांकerpreter();
	status = acpi_tb_unload_table(table_index);
	acpi_ex_enter_पूर्णांकerpreter();

	/*
	 * Invalidate the handle. We करो this because the handle may be stored
	 * in a named object and may not be actually deleted until much later.
	 */
	अगर (ACPI_SUCCESS(status)) अणु
		ddb_handle->common.flags &= ~AOPOBJ_DATA_VALID;
	पूर्ण
	वापस_ACPI_STATUS(status);
पूर्ण
