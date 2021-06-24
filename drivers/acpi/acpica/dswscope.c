<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: dswscope - Scope stack manipulation
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acdispat.h"

#घोषणा _COMPONENT          ACPI_DISPATCHER
ACPI_MODULE_NAME("dswscope")

/****************************************************************************
 *
 * FUNCTION:    acpi_ds_scope_stack_clear
 *
 * PARAMETERS:  walk_state      - Current state
 *
 * RETURN:      None
 *
 * DESCRIPTION: Pop (and मुक्त) everything on the scope stack except the
 *              root scope object (which reमुख्यs at the stack top.)
 *
 ***************************************************************************/
व्योम acpi_ds_scope_stack_clear(काष्ठा acpi_walk_state *walk_state)
अणु
	जोड़ acpi_generic_state *scope_info;

	ACPI_FUNCTION_NAME(ds_scope_stack_clear);

	जबतक (walk_state->scope_info) अणु

		/* Pop a scope off the stack */

		scope_info = walk_state->scope_info;
		walk_state->scope_info = scope_info->scope.next;

		ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
				  "Popped object type (%s)\n",
				  acpi_ut_get_type_name(scope_info->common.
							value)));

		acpi_ut_delete_generic_state(scope_info);
	पूर्ण
पूर्ण

/****************************************************************************
 *
 * FUNCTION:    acpi_ds_scope_stack_push
 *
 * PARAMETERS:  node            - Name to be made current
 *              type            - Type of frame being pushed
 *              walk_state      - Current state
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Push the current scope on the scope stack, and make the
 *              passed Node current.
 *
 ***************************************************************************/

acpi_status
acpi_ds_scope_stack_push(काष्ठा acpi_namespace_node *node,
			 acpi_object_type type,
			 काष्ठा acpi_walk_state *walk_state)
अणु
	जोड़ acpi_generic_state *scope_info;
	जोड़ acpi_generic_state *old_scope_info;

	ACPI_FUNCTION_TRACE(ds_scope_stack_push);

	अगर (!node) अणु

		/* Invalid scope   */

		ACPI_ERROR((AE_INFO, "Null scope parameter"));
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	/* Make sure object type is valid */

	अगर (!acpi_ut_valid_object_type(type)) अणु
		ACPI_WARNING((AE_INFO, "Invalid object type: 0x%X", type));
	पूर्ण

	/* Allocate a new scope object */

	scope_info = acpi_ut_create_generic_state();
	अगर (!scope_info) अणु
		वापस_ACPI_STATUS(AE_NO_MEMORY);
	पूर्ण

	/* Init new scope object */

	scope_info->common.descriptor_type = ACPI_DESC_TYPE_STATE_WSCOPE;
	scope_info->scope.node = node;
	scope_info->common.value = (u16) type;

	walk_state->scope_depth++;

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
			  "[%.2d] Pushed scope ",
			  (u32) walk_state->scope_depth));

	old_scope_info = walk_state->scope_info;
	अगर (old_scope_info) अणु
		ACPI_DEBUG_PRINT_RAW((ACPI_DB_EXEC,
				      "[%4.4s] (%s)",
				      acpi_ut_get_node_name(old_scope_info->
							    scope.node),
				      acpi_ut_get_type_name(old_scope_info->
							    common.value)));
	पूर्ण अन्यथा अणु
		ACPI_DEBUG_PRINT_RAW((ACPI_DB_EXEC, ACPI_NAMESPACE_ROOT));
	पूर्ण

	ACPI_DEBUG_PRINT_RAW((ACPI_DB_EXEC,
			      ", New scope -> [%4.4s] (%s)\n",
			      acpi_ut_get_node_name(scope_info->scope.node),
			      acpi_ut_get_type_name(scope_info->common.value)));

	/* Push new scope object onto stack */

	acpi_ut_push_generic_state(&walk_state->scope_info, scope_info);
	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/****************************************************************************
 *
 * FUNCTION:    acpi_ds_scope_stack_pop
 *
 * PARAMETERS:  walk_state      - Current state
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Pop the scope stack once.
 *
 ***************************************************************************/

acpi_status acpi_ds_scope_stack_pop(काष्ठा acpi_walk_state *walk_state)
अणु
	जोड़ acpi_generic_state *scope_info;
	जोड़ acpi_generic_state *new_scope_info;

	ACPI_FUNCTION_TRACE(ds_scope_stack_pop);

	/*
	 * Pop scope info object off the stack.
	 */
	scope_info = acpi_ut_pop_generic_state(&walk_state->scope_info);
	अगर (!scope_info) अणु
		वापस_ACPI_STATUS(AE_STACK_UNDERFLOW);
	पूर्ण

	walk_state->scope_depth--;

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
			  "[%.2d] Popped scope [%4.4s] (%s), New scope -> ",
			  (u32) walk_state->scope_depth,
			  acpi_ut_get_node_name(scope_info->scope.node),
			  acpi_ut_get_type_name(scope_info->common.value)));

	new_scope_info = walk_state->scope_info;
	अगर (new_scope_info) अणु
		ACPI_DEBUG_PRINT_RAW((ACPI_DB_EXEC, "[%4.4s] (%s)\n",
				      acpi_ut_get_node_name(new_scope_info->
							    scope.node),
				      acpi_ut_get_type_name(new_scope_info->
							    common.value)));
	पूर्ण अन्यथा अणु
		ACPI_DEBUG_PRINT_RAW((ACPI_DB_EXEC, "%s\n",
				      ACPI_NAMESPACE_ROOT));
	पूर्ण

	acpi_ut_delete_generic_state(scope_info);
	वापस_ACPI_STATUS(AE_OK);
पूर्ण
