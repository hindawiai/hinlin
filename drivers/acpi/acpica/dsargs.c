<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: dsargs - Support क्रम execution of dynamic arguments क्रम अटल
 *                       objects (regions, fields, buffer fields, etc.)
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acparser.h"
#समावेश "amlcode.h"
#समावेश "acdispat.h"
#समावेश "acnamesp.h"

#घोषणा _COMPONENT          ACPI_DISPATCHER
ACPI_MODULE_NAME("dsargs")

/* Local prototypes */
अटल acpi_status
acpi_ds_execute_arguments(काष्ठा acpi_namespace_node *node,
			  काष्ठा acpi_namespace_node *scope_node,
			  u32 aml_length, u8 *aml_start);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_execute_arguments
 *
 * PARAMETERS:  node                - Object NS node
 *              scope_node          - Parent NS node
 *              aml_length          - Length of executable AML
 *              aml_start           - Poपूर्णांकer to the AML
 *
 * RETURN:      Status.
 *
 * DESCRIPTION: Late (deferred) execution of region or field arguments
 *
 ******************************************************************************/

अटल acpi_status
acpi_ds_execute_arguments(काष्ठा acpi_namespace_node *node,
			  काष्ठा acpi_namespace_node *scope_node,
			  u32 aml_length, u8 *aml_start)
अणु
	acpi_status status;
	जोड़ acpi_parse_object *op;
	काष्ठा acpi_walk_state *walk_state;

	ACPI_FUNCTION_TRACE_PTR(ds_execute_arguments, aml_start);

	/* Allocate a new parser op to be the root of the parsed tree */

	op = acpi_ps_alloc_op(AML_INT_EVAL_SUBTREE_OP, aml_start);
	अगर (!op) अणु
		वापस_ACPI_STATUS(AE_NO_MEMORY);
	पूर्ण

	/* Save the Node क्रम use in acpi_ps_parse_aml */

	op->common.node = scope_node;

	/* Create and initialize a new parser state */

	walk_state = acpi_ds_create_walk_state(0, शून्य, शून्य, शून्य);
	अगर (!walk_state) अणु
		status = AE_NO_MEMORY;
		जाओ cleanup;
	पूर्ण

	status = acpi_ds_init_aml_walk(walk_state, op, शून्य, aml_start,
				       aml_length, शून्य, ACPI_IMODE_LOAD_PASS1);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_ds_delete_walk_state(walk_state);
		जाओ cleanup;
	पूर्ण

	/* Mark this parse as a deferred opcode */

	walk_state->parse_flags = ACPI_PARSE_DEFERRED_OP;
	walk_state->deferred_node = node;

	/* Pass1: Parse the entire declaration */

	status = acpi_ps_parse_aml(walk_state);
	अगर (ACPI_FAILURE(status)) अणु
		जाओ cleanup;
	पूर्ण

	/* Get and init the Op created above */

	op->common.node = node;
	acpi_ps_delete_parse_tree(op);

	/* Evaluate the deferred arguments */

	op = acpi_ps_alloc_op(AML_INT_EVAL_SUBTREE_OP, aml_start);
	अगर (!op) अणु
		वापस_ACPI_STATUS(AE_NO_MEMORY);
	पूर्ण

	op->common.node = scope_node;

	/* Create and initialize a new parser state */

	walk_state = acpi_ds_create_walk_state(0, शून्य, शून्य, शून्य);
	अगर (!walk_state) अणु
		status = AE_NO_MEMORY;
		जाओ cleanup;
	पूर्ण

	/* Execute the opcode and arguments */

	status = acpi_ds_init_aml_walk(walk_state, op, शून्य, aml_start,
				       aml_length, शून्य, ACPI_IMODE_EXECUTE);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_ds_delete_walk_state(walk_state);
		जाओ cleanup;
	पूर्ण

	/* Mark this execution as a deferred opcode */

	walk_state->deferred_node = node;
	status = acpi_ps_parse_aml(walk_state);

cleanup:
	acpi_ps_delete_parse_tree(op);
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_get_buffer_field_arguments
 *
 * PARAMETERS:  obj_desc        - A valid buffer_field object
 *
 * RETURN:      Status.
 *
 * DESCRIPTION: Get buffer_field Buffer and Index. This implements the late
 *              evaluation of these field attributes.
 *
 ******************************************************************************/

acpi_status
acpi_ds_get_buffer_field_arguments(जोड़ acpi_opeअक्रम_object *obj_desc)
अणु
	जोड़ acpi_opeअक्रम_object *extra_desc;
	काष्ठा acpi_namespace_node *node;
	acpi_status status;

	ACPI_FUNCTION_TRACE_PTR(ds_get_buffer_field_arguments, obj_desc);

	अगर (obj_desc->common.flags & AOPOBJ_DATA_VALID) अणु
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	/* Get the AML poपूर्णांकer (method object) and buffer_field node */

	extra_desc = acpi_ns_get_secondary_object(obj_desc);
	node = obj_desc->buffer_field.node;

	ACPI_DEBUG_EXEC(acpi_ut_display_init_pathname
			(ACPI_TYPE_BUFFER_FIELD, node, शून्य));

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC, "[%4.4s] BufferField Arg Init\n",
			  acpi_ut_get_node_name(node)));

	/* Execute the AML code क्रम the term_arg arguments */

	status = acpi_ds_execute_arguments(node, node->parent,
					   extra_desc->extra.aml_length,
					   extra_desc->extra.aml_start);
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_get_bank_field_arguments
 *
 * PARAMETERS:  obj_desc        - A valid bank_field object
 *
 * RETURN:      Status.
 *
 * DESCRIPTION: Get bank_field bank_value. This implements the late
 *              evaluation of these field attributes.
 *
 ******************************************************************************/

acpi_status
acpi_ds_get_bank_field_arguments(जोड़ acpi_opeअक्रम_object *obj_desc)
अणु
	जोड़ acpi_opeअक्रम_object *extra_desc;
	काष्ठा acpi_namespace_node *node;
	acpi_status status;

	ACPI_FUNCTION_TRACE_PTR(ds_get_bank_field_arguments, obj_desc);

	अगर (obj_desc->common.flags & AOPOBJ_DATA_VALID) अणु
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	/* Get the AML poपूर्णांकer (method object) and bank_field node */

	extra_desc = acpi_ns_get_secondary_object(obj_desc);
	node = obj_desc->bank_field.node;

	ACPI_DEBUG_EXEC(acpi_ut_display_init_pathname
			(ACPI_TYPE_LOCAL_BANK_FIELD, node, शून्य));

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC, "[%4.4s] BankField Arg Init\n",
			  acpi_ut_get_node_name(node)));

	/* Execute the AML code क्रम the term_arg arguments */

	status = acpi_ds_execute_arguments(node, node->parent,
					   extra_desc->extra.aml_length,
					   extra_desc->extra.aml_start);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	status = acpi_ut_add_address_range(obj_desc->region.space_id,
					   obj_desc->region.address,
					   obj_desc->region.length, node);
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_get_buffer_arguments
 *
 * PARAMETERS:  obj_desc        - A valid Buffer object
 *
 * RETURN:      Status.
 *
 * DESCRIPTION: Get Buffer length and initializer byte list. This implements
 *              the late evaluation of these attributes.
 *
 ******************************************************************************/

acpi_status acpi_ds_get_buffer_arguments(जोड़ acpi_opeअक्रम_object *obj_desc)
अणु
	काष्ठा acpi_namespace_node *node;
	acpi_status status;

	ACPI_FUNCTION_TRACE_PTR(ds_get_buffer_arguments, obj_desc);

	अगर (obj_desc->common.flags & AOPOBJ_DATA_VALID) अणु
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	/* Get the Buffer node */

	node = obj_desc->buffer.node;
	अगर (!node) अणु
		ACPI_ERROR((AE_INFO,
			    "No pointer back to namespace node in buffer object %p",
			    obj_desc));
		वापस_ACPI_STATUS(AE_AML_INTERNAL);
	पूर्ण

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC, "Buffer Arg Init\n"));

	/* Execute the AML code क्रम the term_arg arguments */

	status = acpi_ds_execute_arguments(node, node,
					   obj_desc->buffer.aml_length,
					   obj_desc->buffer.aml_start);
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_get_package_arguments
 *
 * PARAMETERS:  obj_desc        - A valid Package object
 *
 * RETURN:      Status.
 *
 * DESCRIPTION: Get Package length and initializer byte list. This implements
 *              the late evaluation of these attributes.
 *
 ******************************************************************************/

acpi_status acpi_ds_get_package_arguments(जोड़ acpi_opeअक्रम_object *obj_desc)
अणु
	काष्ठा acpi_namespace_node *node;
	acpi_status status;

	ACPI_FUNCTION_TRACE_PTR(ds_get_package_arguments, obj_desc);

	अगर (obj_desc->common.flags & AOPOBJ_DATA_VALID) अणु
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	/* Get the Package node */

	node = obj_desc->package.node;
	अगर (!node) अणु
		ACPI_ERROR((AE_INFO,
			    "No pointer back to namespace node in package %p",
			    obj_desc));
		वापस_ACPI_STATUS(AE_AML_INTERNAL);
	पूर्ण

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC, "Package Argument Init, AML Ptr: %p\n",
			  obj_desc->package.aml_start));

	/* Execute the AML code क्रम the term_arg arguments */

	status = acpi_ds_execute_arguments(node, node,
					   obj_desc->package.aml_length,
					   obj_desc->package.aml_start);

	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_get_region_arguments
 *
 * PARAMETERS:  obj_desc        - A valid region object
 *
 * RETURN:      Status.
 *
 * DESCRIPTION: Get region address and length. This implements the late
 *              evaluation of these region attributes.
 *
 ******************************************************************************/

acpi_status acpi_ds_get_region_arguments(जोड़ acpi_opeअक्रम_object *obj_desc)
अणु
	काष्ठा acpi_namespace_node *node;
	acpi_status status;
	जोड़ acpi_opeअक्रम_object *extra_desc;

	ACPI_FUNCTION_TRACE_PTR(ds_get_region_arguments, obj_desc);

	अगर (obj_desc->region.flags & AOPOBJ_DATA_VALID) अणु
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	extra_desc = acpi_ns_get_secondary_object(obj_desc);
	अगर (!extra_desc) अणु
		वापस_ACPI_STATUS(AE_NOT_EXIST);
	पूर्ण

	/* Get the Region node */

	node = obj_desc->region.node;

	ACPI_DEBUG_EXEC(acpi_ut_display_init_pathname
			(ACPI_TYPE_REGION, node, शून्य));

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
			  "[%4.4s] OpRegion Arg Init at AML %p\n",
			  acpi_ut_get_node_name(node),
			  extra_desc->extra.aml_start));

	/* Execute the argument AML */

	status = acpi_ds_execute_arguments(node, extra_desc->extra.scope_node,
					   extra_desc->extra.aml_length,
					   extra_desc->extra.aml_start);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	status = acpi_ut_add_address_range(obj_desc->region.space_id,
					   obj_desc->region.address,
					   obj_desc->region.length, node);
	वापस_ACPI_STATUS(status);
पूर्ण
