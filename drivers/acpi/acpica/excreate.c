<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: excreate - Named object creation
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acinterp.h"
#समावेश "amlcode.h"
#समावेश "acnamesp.h"

#घोषणा _COMPONENT          ACPI_EXECUTER
ACPI_MODULE_NAME("excreate")
/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_create_alias
 *
 * PARAMETERS:  walk_state           - Current state, contains opeअक्रमs
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Create a new named alias
 *
 ******************************************************************************/
acpi_status acpi_ex_create_alias(काष्ठा acpi_walk_state *walk_state)
अणु
	काष्ठा acpi_namespace_node *target_node;
	काष्ठा acpi_namespace_node *alias_node;
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TRACE(ex_create_alias);

	/* Get the source/alias opeअक्रमs (both namespace nodes) */

	alias_node = (काष्ठा acpi_namespace_node *)walk_state->opeअक्रमs[0];
	target_node = (काष्ठा acpi_namespace_node *)walk_state->opeअक्रमs[1];

	अगर ((target_node->type == ACPI_TYPE_LOCAL_ALIAS) ||
	    (target_node->type == ACPI_TYPE_LOCAL_METHOD_ALIAS)) अणु
		/*
		 * Dereference an existing alias so that we करोn't create a chain
		 * of aliases. With this code, we guarantee that an alias is
		 * always exactly one level of indirection away from the
		 * actual aliased name.
		 */
		target_node =
		    ACPI_CAST_PTR(काष्ठा acpi_namespace_node,
				  target_node->object);
	पूर्ण

	/* Ensure that the target node is valid */

	अगर (!target_node) अणु
		वापस_ACPI_STATUS(AE_शून्य_OBJECT);
	पूर्ण

	/* Conकाष्ठा the alias object (a namespace node) */

	चयन (target_node->type) अणु
	हाल ACPI_TYPE_METHOD:
		/*
		 * Control method aliases need to be dअगरferentiated with
		 * a special type
		 */
		alias_node->type = ACPI_TYPE_LOCAL_METHOD_ALIAS;
		अवरोध;

	शेष:
		/*
		 * All other object types.
		 *
		 * The new alias has the type ALIAS and poपूर्णांकs to the original
		 * NS node, not the object itself.
		 */
		alias_node->type = ACPI_TYPE_LOCAL_ALIAS;
		alias_node->object =
		    ACPI_CAST_PTR(जोड़ acpi_opeअक्रम_object, target_node);
		अवरोध;
	पूर्ण

	/* Since both opeअक्रमs are Nodes, we करोn't need to delete them */

	alias_node->object =
	    ACPI_CAST_PTR(जोड़ acpi_opeअक्रम_object, target_node);
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_create_event
 *
 * PARAMETERS:  walk_state          - Current state
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Create a new event object
 *
 ******************************************************************************/

acpi_status acpi_ex_create_event(काष्ठा acpi_walk_state *walk_state)
अणु
	acpi_status status;
	जोड़ acpi_opeअक्रम_object *obj_desc;

	ACPI_FUNCTION_TRACE(ex_create_event);

	obj_desc = acpi_ut_create_पूर्णांकernal_object(ACPI_TYPE_EVENT);
	अगर (!obj_desc) अणु
		status = AE_NO_MEMORY;
		जाओ cleanup;
	पूर्ण

	/*
	 * Create the actual OS semaphore, with zero initial units -- meaning
	 * that the event is created in an unसंकेतled state
	 */
	status = acpi_os_create_semaphore(ACPI_NO_UNIT_LIMIT, 0,
					  &obj_desc->event.os_semaphore);
	अगर (ACPI_FAILURE(status)) अणु
		जाओ cleanup;
	पूर्ण

	/* Attach object to the Node */

	status = acpi_ns_attach_object((काष्ठा acpi_namespace_node *)
				       walk_state->opeअक्रमs[0], obj_desc,
				       ACPI_TYPE_EVENT);

cleanup:
	/*
	 * Remove local reference to the object (on error, will cause deletion
	 * of both object and semaphore अगर present.)
	 */
	acpi_ut_हटाओ_reference(obj_desc);
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_create_mutex
 *
 * PARAMETERS:  walk_state          - Current state
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Create a new mutex object
 *
 *              Mutex (Name[0], sync_level[1])
 *
 ******************************************************************************/

acpi_status acpi_ex_create_mutex(काष्ठा acpi_walk_state *walk_state)
अणु
	acpi_status status = AE_OK;
	जोड़ acpi_opeअक्रम_object *obj_desc;

	ACPI_FUNCTION_TRACE_PTR(ex_create_mutex, ACPI_WALK_OPERANDS);

	/* Create the new mutex object */

	obj_desc = acpi_ut_create_पूर्णांकernal_object(ACPI_TYPE_MUTEX);
	अगर (!obj_desc) अणु
		status = AE_NO_MEMORY;
		जाओ cleanup;
	पूर्ण

	/* Create the actual OS Mutex */

	status = acpi_os_create_mutex(&obj_desc->mutex.os_mutex);
	अगर (ACPI_FAILURE(status)) अणु
		जाओ cleanup;
	पूर्ण

	/* Init object and attach to NS node */

	obj_desc->mutex.sync_level = (u8)walk_state->opeअक्रमs[1]->पूर्णांकeger.value;
	obj_desc->mutex.node =
	    (काष्ठा acpi_namespace_node *)walk_state->opeअक्रमs[0];

	status =
	    acpi_ns_attach_object(obj_desc->mutex.node, obj_desc,
				  ACPI_TYPE_MUTEX);

cleanup:
	/*
	 * Remove local reference to the object (on error, will cause deletion
	 * of both object and semaphore अगर present.)
	 */
	acpi_ut_हटाओ_reference(obj_desc);
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_create_region
 *
 * PARAMETERS:  aml_start           - Poपूर्णांकer to the region declaration AML
 *              aml_length          - Max length of the declaration AML
 *              space_id            - Address space ID क्रम the region
 *              walk_state          - Current state
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Create a new operation region object
 *
 ******************************************************************************/

acpi_status
acpi_ex_create_region(u8 * aml_start,
		      u32 aml_length,
		      u8 space_id, काष्ठा acpi_walk_state *walk_state)
अणु
	acpi_status status;
	जोड़ acpi_opeअक्रम_object *obj_desc;
	काष्ठा acpi_namespace_node *node;
	जोड़ acpi_opeअक्रम_object *region_obj2;

	ACPI_FUNCTION_TRACE(ex_create_region);

	/* Get the Namespace Node */

	node = walk_state->op->common.node;

	/*
	 * If the region object is alपढ़ोy attached to this node,
	 * just वापस
	 */
	अगर (acpi_ns_get_attached_object(node)) अणु
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	/*
	 * Space ID must be one of the predefined IDs, or in the user-defined
	 * range
	 */
	अगर (!acpi_is_valid_space_id(space_id)) अणु
		/*
		 * Prपूर्णांक an error message, but जारी. We करोn't want to पात
		 * a table load क्रम this exception. Instead, अगर the region is
		 * actually used at runसमय, पात the executing method.
		 */
		ACPI_ERROR((AE_INFO,
			    "Invalid/unknown Address Space ID: 0x%2.2X",
			    space_id));
	पूर्ण

	ACPI_DEBUG_PRINT((ACPI_DB_LOAD, "Region Type - %s (0x%X)\n",
			  acpi_ut_get_region_name(space_id), space_id));

	/* Create the region descriptor */

	obj_desc = acpi_ut_create_पूर्णांकernal_object(ACPI_TYPE_REGION);
	अगर (!obj_desc) अणु
		status = AE_NO_MEMORY;
		जाओ cleanup;
	पूर्ण

	/*
	 * Remember location in AML stream of address & length
	 * opeअक्रमs since they need to be evaluated at run समय.
	 */
	region_obj2 = acpi_ns_get_secondary_object(obj_desc);
	region_obj2->extra.aml_start = aml_start;
	region_obj2->extra.aml_length = aml_length;
	region_obj2->extra.method_REG = शून्य;
	अगर (walk_state->scope_info) अणु
		region_obj2->extra.scope_node =
		    walk_state->scope_info->scope.node;
	पूर्ण अन्यथा अणु
		region_obj2->extra.scope_node = node;
	पूर्ण

	/* Init the region from the opeअक्रमs */

	obj_desc->region.space_id = space_id;
	obj_desc->region.address = 0;
	obj_desc->region.length = 0;
	obj_desc->region.node = node;
	obj_desc->region.handler = शून्य;
	obj_desc->common.flags &=
	    ~(AOPOBJ_SETUP_COMPLETE | AOPOBJ_REG_CONNECTED |
	      AOPOBJ_OBJECT_INITIALIZED);

	/* Install the new region object in the parent Node */

	status = acpi_ns_attach_object(node, obj_desc, ACPI_TYPE_REGION);

cleanup:

	/* Remove local reference to the object */

	acpi_ut_हटाओ_reference(obj_desc);
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_create_processor
 *
 * PARAMETERS:  walk_state          - Current state
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Create a new processor object and populate the fields
 *
 *              Processor (Name[0], cpu_ID[1], pblock_addr[2], pblock_length[3])
 *
 ******************************************************************************/

acpi_status acpi_ex_create_processor(काष्ठा acpi_walk_state *walk_state)
अणु
	जोड़ acpi_opeअक्रम_object **opeअक्रम = &walk_state->opeअक्रमs[0];
	जोड़ acpi_opeअक्रम_object *obj_desc;
	acpi_status status;

	ACPI_FUNCTION_TRACE_PTR(ex_create_processor, walk_state);

	/* Create the processor object */

	obj_desc = acpi_ut_create_पूर्णांकernal_object(ACPI_TYPE_PROCESSOR);
	अगर (!obj_desc) अणु
		वापस_ACPI_STATUS(AE_NO_MEMORY);
	पूर्ण

	/* Initialize the processor object from the opeअक्रमs */

	obj_desc->processor.proc_id = (u8) opeअक्रम[1]->पूर्णांकeger.value;
	obj_desc->processor.length = (u8) opeअक्रम[3]->पूर्णांकeger.value;
	obj_desc->processor.address =
	    (acpi_io_address)opeअक्रम[2]->पूर्णांकeger.value;

	/* Install the processor object in the parent Node */

	status = acpi_ns_attach_object((काष्ठा acpi_namespace_node *)opeअक्रम[0],
				       obj_desc, ACPI_TYPE_PROCESSOR);

	/* Remove local reference to the object */

	acpi_ut_हटाओ_reference(obj_desc);
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_create_घातer_resource
 *
 * PARAMETERS:  walk_state          - Current state
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Create a new घातer_resource object and populate the fields
 *
 *              घातer_resource (Name[0], प्रणाली_level[1], resource_order[2])
 *
 ******************************************************************************/

acpi_status acpi_ex_create_घातer_resource(काष्ठा acpi_walk_state *walk_state)
अणु
	जोड़ acpi_opeअक्रम_object **opeअक्रम = &walk_state->opeअक्रमs[0];
	acpi_status status;
	जोड़ acpi_opeअक्रम_object *obj_desc;

	ACPI_FUNCTION_TRACE_PTR(ex_create_घातer_resource, walk_state);

	/* Create the घातer resource object */

	obj_desc = acpi_ut_create_पूर्णांकernal_object(ACPI_TYPE_POWER);
	अगर (!obj_desc) अणु
		वापस_ACPI_STATUS(AE_NO_MEMORY);
	पूर्ण

	/* Initialize the घातer object from the opeअक्रमs */

	obj_desc->घातer_resource.प्रणाली_level = (u8) opeअक्रम[1]->पूर्णांकeger.value;
	obj_desc->घातer_resource.resource_order =
	    (u16) opeअक्रम[2]->पूर्णांकeger.value;

	/* Install the  घातer resource object in the parent Node */

	status = acpi_ns_attach_object((काष्ठा acpi_namespace_node *)opeअक्रम[0],
				       obj_desc, ACPI_TYPE_POWER);

	/* Remove local reference to the object */

	acpi_ut_हटाओ_reference(obj_desc);
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_create_method
 *
 * PARAMETERS:  aml_start       - First byte of the method's AML
 *              aml_length      - AML byte count क्रम this method
 *              walk_state      - Current state
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Create a new method object
 *
 ******************************************************************************/

acpi_status
acpi_ex_create_method(u8 * aml_start,
		      u32 aml_length, काष्ठा acpi_walk_state *walk_state)
अणु
	जोड़ acpi_opeअक्रम_object **opeअक्रम = &walk_state->opeअक्रमs[0];
	जोड़ acpi_opeअक्रम_object *obj_desc;
	acpi_status status;
	u8 method_flags;

	ACPI_FUNCTION_TRACE_PTR(ex_create_method, walk_state);

	/* Create a new method object */

	obj_desc = acpi_ut_create_पूर्णांकernal_object(ACPI_TYPE_METHOD);
	अगर (!obj_desc) अणु
		status = AE_NO_MEMORY;
		जाओ निकास;
	पूर्ण

	/* Save the method's AML poपूर्णांकer and length  */

	obj_desc->method.aml_start = aml_start;
	obj_desc->method.aml_length = aml_length;
	obj_desc->method.node = opeअक्रम[0];

	/*
	 * Disassemble the method flags. Split off the arg_count, Serialized
	 * flag, and sync_level क्रम efficiency.
	 */
	method_flags = (u8)opeअक्रम[1]->पूर्णांकeger.value;
	obj_desc->method.param_count = (u8)
	    (method_flags & AML_METHOD_ARG_COUNT);

	/*
	 * Get the sync_level. If method is serialized, a mutex will be
	 * created क्रम this method when it is parsed.
	 */
	अगर (method_flags & AML_METHOD_SERIALIZED) अणु
		obj_desc->method.info_flags = ACPI_METHOD_SERIALIZED;

		/*
		 * ACPI 1.0: sync_level = 0
		 * ACPI 2.0: sync_level = sync_level in method declaration
		 */
		obj_desc->method.sync_level = (u8)
		    ((method_flags & AML_METHOD_SYNC_LEVEL) >> 4);
	पूर्ण

	/* Attach the new object to the method Node */

	status = acpi_ns_attach_object((काष्ठा acpi_namespace_node *)opeअक्रम[0],
				       obj_desc, ACPI_TYPE_METHOD);

	/* Remove local reference to the object */

	acpi_ut_हटाओ_reference(obj_desc);

निकास:
	/* Remove a reference to the opeअक्रम */

	acpi_ut_हटाओ_reference(opeअक्रम[1]);
	वापस_ACPI_STATUS(status);
पूर्ण
