<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: psscope - Parser scope stack management routines
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acparser.h"

#घोषणा _COMPONENT          ACPI_PARSER
ACPI_MODULE_NAME("psscope")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_get_parent_scope
 *
 * PARAMETERS:  parser_state        - Current parser state object
 *
 * RETURN:      Poपूर्णांकer to an Op object
 *
 * DESCRIPTION: Get parent of current op being parsed
 *
 ******************************************************************************/
जोड़ acpi_parse_object *acpi_ps_get_parent_scope(काष्ठा acpi_parse_state
						  *parser_state)
अणु

	वापस (parser_state->scope->parse_scope.op);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_has_completed_scope
 *
 * PARAMETERS:  parser_state        - Current parser state object
 *
 * RETURN:      Boolean, TRUE = scope completed.
 *
 * DESCRIPTION: Is parsing of current argument complete?  Determined by
 *              1) AML poपूर्णांकer is at or beyond the end of the scope
 *              2) The scope argument count has reached zero.
 *
 ******************************************************************************/

u8 acpi_ps_has_completed_scope(काष्ठा acpi_parse_state * parser_state)
अणु

	वापस ((u8)
		((parser_state->aml >= parser_state->scope->parse_scope.arg_end
		  || !parser_state->scope->parse_scope.arg_count)));
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_init_scope
 *
 * PARAMETERS:  parser_state        - Current parser state object
 *              root                - the Root Node of this new scope
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Allocate and init a new scope object
 *
 ******************************************************************************/

acpi_status
acpi_ps_init_scope(काष्ठा acpi_parse_state * parser_state,
		   जोड़ acpi_parse_object * root_op)
अणु
	जोड़ acpi_generic_state *scope;

	ACPI_FUNCTION_TRACE_PTR(ps_init_scope, root_op);

	scope = acpi_ut_create_generic_state();
	अगर (!scope) अणु
		वापस_ACPI_STATUS(AE_NO_MEMORY);
	पूर्ण

	scope->common.descriptor_type = ACPI_DESC_TYPE_STATE_RPSCOPE;
	scope->parse_scope.op = root_op;
	scope->parse_scope.arg_count = ACPI_VAR_ARGS;
	scope->parse_scope.arg_end = parser_state->aml_end;
	scope->parse_scope.pkg_end = parser_state->aml_end;

	parser_state->scope = scope;
	parser_state->start_op = root_op;

	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_push_scope
 *
 * PARAMETERS:  parser_state        - Current parser state object
 *              op                  - Current op to be pushed
 *              reमुख्यing_args      - List of args reमुख्यing
 *              arg_count           - Fixed or variable number of args
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Push current op to begin parsing its argument
 *
 ******************************************************************************/

acpi_status
acpi_ps_push_scope(काष्ठा acpi_parse_state *parser_state,
		   जोड़ acpi_parse_object *op,
		   u32 reमुख्यing_args, u32 arg_count)
अणु
	जोड़ acpi_generic_state *scope;

	ACPI_FUNCTION_TRACE_PTR(ps_push_scope, op);

	scope = acpi_ut_create_generic_state();
	अगर (!scope) अणु
		वापस_ACPI_STATUS(AE_NO_MEMORY);
	पूर्ण

	scope->common.descriptor_type = ACPI_DESC_TYPE_STATE_PSCOPE;
	scope->parse_scope.op = op;
	scope->parse_scope.arg_list = reमुख्यing_args;
	scope->parse_scope.arg_count = arg_count;
	scope->parse_scope.pkg_end = parser_state->pkg_end;

	/* Push onto scope stack */

	acpi_ut_push_generic_state(&parser_state->scope, scope);

	अगर (arg_count == ACPI_VAR_ARGS) अणु

		/* Multiple arguments */

		scope->parse_scope.arg_end = parser_state->pkg_end;
	पूर्ण अन्यथा अणु
		/* Single argument */

		scope->parse_scope.arg_end = ACPI_TO_POINTER(ACPI_MAX_PTR);
	पूर्ण

	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_pop_scope
 *
 * PARAMETERS:  parser_state        - Current parser state object
 *              op                  - Where the popped op is वापसed
 *              arg_list            - Where the popped "next argument" is
 *                                    वापसed
 *              arg_count           - Count of objects in arg_list
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Return to parsing a previous op
 *
 ******************************************************************************/

व्योम
acpi_ps_pop_scope(काष्ठा acpi_parse_state *parser_state,
		  जोड़ acpi_parse_object **op, u32 * arg_list, u32 * arg_count)
अणु
	जोड़ acpi_generic_state *scope = parser_state->scope;

	ACPI_FUNCTION_TRACE(ps_pop_scope);

	/* Only pop the scope अगर there is in fact a next scope */

	अगर (scope->common.next) अणु
		scope = acpi_ut_pop_generic_state(&parser_state->scope);

		/* Return to parsing previous op */

		*op = scope->parse_scope.op;
		*arg_list = scope->parse_scope.arg_list;
		*arg_count = scope->parse_scope.arg_count;
		parser_state->pkg_end = scope->parse_scope.pkg_end;

		/* All करोne with this scope state काष्ठाure */

		acpi_ut_delete_generic_state(scope);
	पूर्ण अन्यथा अणु
		/* Empty parse stack, prepare to fetch next opcode */

		*op = शून्य;
		*arg_list = 0;
		*arg_count = 0;
	पूर्ण

	ACPI_DEBUG_PRINT((ACPI_DB_PARSE,
			  "Popped Op %p Args %X\n", *op, *arg_count));
	वापस_VOID;
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_cleanup_scope
 *
 * PARAMETERS:  parser_state        - Current parser state object
 *
 * RETURN:      None
 *
 * DESCRIPTION: Destroy available list, reमुख्यing stack levels, and वापस
 *              root scope
 *
 ******************************************************************************/

व्योम acpi_ps_cleanup_scope(काष्ठा acpi_parse_state *parser_state)
अणु
	जोड़ acpi_generic_state *scope;

	ACPI_FUNCTION_TRACE_PTR(ps_cleanup_scope, parser_state);

	अगर (!parser_state) अणु
		वापस_VOID;
	पूर्ण

	/* Delete anything on the scope stack */

	जबतक (parser_state->scope) अणु
		scope = acpi_ut_pop_generic_state(&parser_state->scope);
		acpi_ut_delete_generic_state(scope);
	पूर्ण

	वापस_VOID;
पूर्ण
