<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: psxface - Parser बाह्यal पूर्णांकerfaces
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acparser.h"
#समावेश "acdispat.h"
#समावेश "acinterp.h"
#समावेश "actables.h"
#समावेश "acnamesp.h"

#घोषणा _COMPONENT          ACPI_PARSER
ACPI_MODULE_NAME("psxface")

/* Local Prototypes */
अटल व्योम
acpi_ps_update_parameter_list(काष्ठा acpi_evaluate_info *info, u16 action);

/*******************************************************************************
 *
 * FUNCTION:    acpi_debug_trace
 *
 * PARAMETERS:  method_name     - Valid ACPI name string
 *              debug_level     - Optional level mask. 0 to use शेष
 *              debug_layer     - Optional layer mask. 0 to use शेष
 *              flags           - bit 1: one shot(1) or persistent(0)
 *
 * RETURN:      Status
 *
 * DESCRIPTION: External पूर्णांकerface to enable debug tracing during control
 *              method execution
 *
 ******************************************************************************/

acpi_status
acpi_debug_trace(स्थिर अक्षर *name, u32 debug_level, u32 debug_layer, u32 flags)
अणु
	acpi_status status;

	status = acpi_ut_acquire_mutex(ACPI_MTX_NAMESPACE);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	acpi_gbl_trace_method_name = name;
	acpi_gbl_trace_flags = flags;
	acpi_gbl_trace_dbg_level = debug_level;
	acpi_gbl_trace_dbg_layer = debug_layer;
	status = AE_OK;

	(व्योम)acpi_ut_release_mutex(ACPI_MTX_NAMESPACE);
	वापस (status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_execute_method
 *
 * PARAMETERS:  info            - Method info block, contains:
 *                  node            - Method Node to execute
 *                  obj_desc        - Method object
 *                  parameters      - List of parameters to pass to the method,
 *                                    terminated by शून्य. Params itself may be
 *                                    शून्य अगर no parameters are being passed.
 *                  वापस_object   - Where to put method's वापस value (अगर
 *                                    any). If शून्य, no value is वापसed.
 *                  parameter_type  - Type of Parameter list
 *                  वापस_object   - Where to put method's वापस value (अगर
 *                                    any). If शून्य, no value is वापसed.
 *                  pass_number     - Parse or execute pass
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Execute a control method
 *
 ******************************************************************************/

acpi_status acpi_ps_execute_method(काष्ठा acpi_evaluate_info *info)
अणु
	acpi_status status;
	जोड़ acpi_parse_object *op;
	काष्ठा acpi_walk_state *walk_state;

	ACPI_FUNCTION_TRACE(ps_execute_method);

	/* Quick validation of DSDT header */

	acpi_tb_check_dsdt_header();

	/* Validate the Info and method Node */

	अगर (!info || !info->node) अणु
		वापस_ACPI_STATUS(AE_शून्य_ENTRY);
	पूर्ण

	/* Init क्रम new method, रुको on concurrency semaphore */

	status =
	    acpi_ds_begin_method_execution(info->node, info->obj_desc, शून्य);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/*
	 * The caller "owns" the parameters, so give each one an extra reference
	 */
	acpi_ps_update_parameter_list(info, REF_INCREMENT);

	/*
	 * Execute the method. Perक्रमms parse simultaneously
	 */
	ACPI_DEBUG_PRINT((ACPI_DB_PARSE,
			  "**** Begin Method Parse/Execute [%4.4s] **** Node=%p Obj=%p\n",
			  info->node->name.ascii, info->node, info->obj_desc));

	/* Create and init a Root Node */

	op = acpi_ps_create_scope_op(info->obj_desc->method.aml_start);
	अगर (!op) अणु
		status = AE_NO_MEMORY;
		जाओ cleanup;
	पूर्ण

	/* Create and initialize a new walk state */

	info->pass_number = ACPI_IMODE_EXECUTE;
	walk_state =
	    acpi_ds_create_walk_state(info->obj_desc->method.owner_id, शून्य,
				      शून्य, शून्य);
	अगर (!walk_state) अणु
		status = AE_NO_MEMORY;
		जाओ cleanup;
	पूर्ण

	status = acpi_ds_init_aml_walk(walk_state, op, info->node,
				       info->obj_desc->method.aml_start,
				       info->obj_desc->method.aml_length, info,
				       info->pass_number);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_ds_delete_walk_state(walk_state);
		जाओ cleanup;
	पूर्ण

	walk_state->method_pathname = info->full_pathname;
	walk_state->method_is_nested = FALSE;

	अगर (info->obj_desc->method.info_flags & ACPI_METHOD_MODULE_LEVEL) अणु
		walk_state->parse_flags |= ACPI_PARSE_MODULE_LEVEL;
	पूर्ण

	/* Invoke an पूर्णांकernal method अगर necessary */

	अगर (info->obj_desc->method.info_flags & ACPI_METHOD_INTERNAL_ONLY) अणु
		status =
		    info->obj_desc->method.dispatch.implementation(walk_state);
		info->वापस_object = walk_state->वापस_desc;

		/* Cleanup states */

		acpi_ds_scope_stack_clear(walk_state);
		acpi_ps_cleanup_scope(&walk_state->parser_state);
		acpi_ds_terminate_control_method(walk_state->method_desc,
						 walk_state);
		acpi_ds_delete_walk_state(walk_state);
		जाओ cleanup;
	पूर्ण

	/*
	 * Start method evaluation with an implicit वापस of zero.
	 * This is करोne क्रम Winकरोws compatibility.
	 */
	अगर (acpi_gbl_enable_पूर्णांकerpreter_slack) अणु
		walk_state->implicit_वापस_obj =
		    acpi_ut_create_पूर्णांकeger_object((u64) 0);
		अगर (!walk_state->implicit_वापस_obj) अणु
			status = AE_NO_MEMORY;
			acpi_ds_delete_walk_state(walk_state);
			जाओ cleanup;
		पूर्ण
	पूर्ण

	/* Parse the AML */

	status = acpi_ps_parse_aml(walk_state);

	/* walk_state was deleted by parse_aml */

cleanup:
	acpi_ps_delete_parse_tree(op);

	/* Take away the extra reference that we gave the parameters above */

	acpi_ps_update_parameter_list(info, REF_DECREMENT);

	/* Exit now अगर error above */

	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/*
	 * If the method has वापसed an object, संकेत this to the caller with
	 * a control exception code
	 */
	अगर (info->वापस_object) अणु
		ACPI_DEBUG_PRINT((ACPI_DB_PARSE, "Method returned ObjDesc=%p\n",
				  info->वापस_object));
		ACPI_DUMP_STACK_ENTRY(info->वापस_object);

		status = AE_CTRL_RETURN_VALUE;
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_execute_table
 *
 * PARAMETERS:  info            - Method info block, contains:
 *              node            - Node to where the is entered पूर्णांकo the
 *                                namespace
 *              obj_desc        - Pseuकरो method object describing the AML
 *                                code of the entire table
 *              pass_number     - Parse or execute pass
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Execute a table
 *
 ******************************************************************************/

acpi_status acpi_ps_execute_table(काष्ठा acpi_evaluate_info *info)
अणु
	acpi_status status;
	जोड़ acpi_parse_object *op = शून्य;
	काष्ठा acpi_walk_state *walk_state = शून्य;

	ACPI_FUNCTION_TRACE(ps_execute_table);

	/* Create and init a Root Node */

	op = acpi_ps_create_scope_op(info->obj_desc->method.aml_start);
	अगर (!op) अणु
		status = AE_NO_MEMORY;
		जाओ cleanup;
	पूर्ण

	/* Create and initialize a new walk state */

	walk_state =
	    acpi_ds_create_walk_state(info->obj_desc->method.owner_id, शून्य,
				      शून्य, शून्य);
	अगर (!walk_state) अणु
		status = AE_NO_MEMORY;
		जाओ cleanup;
	पूर्ण

	status = acpi_ds_init_aml_walk(walk_state, op, info->node,
				       info->obj_desc->method.aml_start,
				       info->obj_desc->method.aml_length, info,
				       info->pass_number);
	अगर (ACPI_FAILURE(status)) अणु
		जाओ cleanup;
	पूर्ण

	walk_state->method_pathname = info->full_pathname;
	walk_state->method_is_nested = FALSE;

	अगर (info->obj_desc->method.info_flags & ACPI_METHOD_MODULE_LEVEL) अणु
		walk_state->parse_flags |= ACPI_PARSE_MODULE_LEVEL;
	पूर्ण

	/* Info->Node is the शेष location to load the table  */

	अगर (info->node && info->node != acpi_gbl_root_node) अणु
		status =
		    acpi_ds_scope_stack_push(info->node, ACPI_TYPE_METHOD,
					     walk_state);
		अगर (ACPI_FAILURE(status)) अणु
			जाओ cleanup;
		पूर्ण
	पूर्ण

	/*
	 * Parse the AML, walk_state will be deleted by parse_aml
	 */
	acpi_ex_enter_पूर्णांकerpreter();
	status = acpi_ps_parse_aml(walk_state);
	acpi_ex_निकास_पूर्णांकerpreter();
	walk_state = शून्य;

cleanup:
	अगर (walk_state) अणु
		acpi_ds_delete_walk_state(walk_state);
	पूर्ण
	अगर (op) अणु
		acpi_ps_delete_parse_tree(op);
	पूर्ण
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_update_parameter_list
 *
 * PARAMETERS:  info            - See काष्ठा acpi_evaluate_info
 *                                (Used: parameter_type and Parameters)
 *              action          - Add or Remove reference
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Update reference count on all method parameter objects
 *
 ******************************************************************************/

अटल व्योम
acpi_ps_update_parameter_list(काष्ठा acpi_evaluate_info *info, u16 action)
अणु
	u32 i;

	अगर (info->parameters) अणु

		/* Update reference count क्रम each parameter */

		क्रम (i = 0; info->parameters[i]; i++) अणु

			/* Ignore errors, just करो them all */

			(व्योम)acpi_ut_update_object_reference(info->
							      parameters[i],
							      action);
		पूर्ण
	पूर्ण
पूर्ण
