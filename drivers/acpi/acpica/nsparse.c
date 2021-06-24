<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: nsparse - namespace पूर्णांकerface to AML parser
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acnamesp.h"
#समावेश "acparser.h"
#समावेश "acdispat.h"
#समावेश "actables.h"
#समावेश "acinterp.h"

#घोषणा _COMPONENT          ACPI_NAMESPACE
ACPI_MODULE_NAME("nsparse")

/*******************************************************************************
 *
 * FUNCTION:    ns_execute_table
 *
 * PARAMETERS:  table_desc      - An ACPI table descriptor क्रम table to parse
 *              start_node      - Where to enter the table पूर्णांकo the namespace
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Load ACPI/AML table by executing the entire table as a single
 *              large control method.
 *
 * NOTE: The poपूर्णांक of this is to execute any module-level code in-place
 * as the table is parsed. Some AML code depends on this behavior.
 *
 * It is a run-समय option at this समय, but will eventually become
 * the शेष.
 *
 * Note: This causes the table to only have a single-pass parse.
 * However, this is compatible with other ACPI implementations.
 *
 ******************************************************************************/
acpi_status
acpi_ns_execute_table(u32 table_index, काष्ठा acpi_namespace_node *start_node)
अणु
	acpi_status status;
	काष्ठा acpi_table_header *table;
	acpi_owner_id owner_id;
	काष्ठा acpi_evaluate_info *info = शून्य;
	u32 aml_length;
	u8 *aml_start;
	जोड़ acpi_opeअक्रम_object *method_obj = शून्य;

	ACPI_FUNCTION_TRACE(ns_execute_table);

	status = acpi_get_table_by_index(table_index, &table);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Table must consist of at least a complete header */

	अगर (table->length < माप(काष्ठा acpi_table_header)) अणु
		वापस_ACPI_STATUS(AE_BAD_HEADER);
	पूर्ण

	aml_start = (u8 *)table + माप(काष्ठा acpi_table_header);
	aml_length = table->length - माप(काष्ठा acpi_table_header);

	status = acpi_tb_get_owner_id(table_index, &owner_id);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Create, initialize, and link a new temporary method object */

	method_obj = acpi_ut_create_पूर्णांकernal_object(ACPI_TYPE_METHOD);
	अगर (!method_obj) अणु
		वापस_ACPI_STATUS(AE_NO_MEMORY);
	पूर्ण

	/* Allocate the evaluation inक्रमmation block */

	info = ACPI_ALLOCATE_ZEROED(माप(काष्ठा acpi_evaluate_info));
	अगर (!info) अणु
		status = AE_NO_MEMORY;
		जाओ cleanup;
	पूर्ण

	ACPI_DEBUG_PRINT_RAW((ACPI_DB_PARSE,
			      "%s: Create table pseudo-method for [%4.4s] @%p, method %p\n",
			      ACPI_GET_FUNCTION_NAME, table->signature, table,
			      method_obj));

	method_obj->method.aml_start = aml_start;
	method_obj->method.aml_length = aml_length;
	method_obj->method.owner_id = owner_id;
	method_obj->method.info_flags |= ACPI_METHOD_MODULE_LEVEL;

	info->pass_number = ACPI_IMODE_EXECUTE;
	info->node = start_node;
	info->obj_desc = method_obj;
	info->node_flags = info->node->flags;
	info->full_pathname = acpi_ns_get_normalized_pathname(info->node, TRUE);
	अगर (!info->full_pathname) अणु
		status = AE_NO_MEMORY;
		जाओ cleanup;
	पूर्ण

	/* Optional object evaluation log */

	ACPI_DEBUG_PRINT_RAW((ACPI_DB_EVALUATION,
			      "%-26s:  (Definition Block level)\n",
			      "Module-level evaluation"));

	status = acpi_ps_execute_table(info);

	/* Optional object evaluation log */

	ACPI_DEBUG_PRINT_RAW((ACPI_DB_EVALUATION,
			      "%-26s:  (Definition Block level)\n",
			      "Module-level complete"));

cleanup:
	अगर (info) अणु
		ACPI_FREE(info->full_pathname);
		info->full_pathname = शून्य;
	पूर्ण
	ACPI_FREE(info);
	acpi_ut_हटाओ_reference(method_obj);
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    ns_one_complete_parse
 *
 * PARAMETERS:  pass_number             - 1 or 2
 *              table_desc              - The table to be parsed.
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Perक्रमm one complete parse of an ACPI/AML table.
 *
 ******************************************************************************/

acpi_status
acpi_ns_one_complete_parse(u32 pass_number,
			   u32 table_index,
			   काष्ठा acpi_namespace_node *start_node)
अणु
	जोड़ acpi_parse_object *parse_root;
	acpi_status status;
	u32 aml_length;
	u8 *aml_start;
	काष्ठा acpi_walk_state *walk_state;
	काष्ठा acpi_table_header *table;
	acpi_owner_id owner_id;

	ACPI_FUNCTION_TRACE(ns_one_complete_parse);

	status = acpi_get_table_by_index(table_index, &table);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Table must consist of at least a complete header */

	अगर (table->length < माप(काष्ठा acpi_table_header)) अणु
		वापस_ACPI_STATUS(AE_BAD_HEADER);
	पूर्ण

	aml_start = (u8 *)table + माप(काष्ठा acpi_table_header);
	aml_length = table->length - माप(काष्ठा acpi_table_header);

	status = acpi_tb_get_owner_id(table_index, &owner_id);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Create and init a Root Node */

	parse_root = acpi_ps_create_scope_op(aml_start);
	अगर (!parse_root) अणु
		वापस_ACPI_STATUS(AE_NO_MEMORY);
	पूर्ण

	/* Create and initialize a new walk state */

	walk_state = acpi_ds_create_walk_state(owner_id, शून्य, शून्य, शून्य);
	अगर (!walk_state) अणु
		acpi_ps_मुक्त_op(parse_root);
		वापस_ACPI_STATUS(AE_NO_MEMORY);
	पूर्ण

	status = acpi_ds_init_aml_walk(walk_state, parse_root, शून्य,
				       aml_start, aml_length, शून्य,
				       (u8)pass_number);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_ds_delete_walk_state(walk_state);
		जाओ cleanup;
	पूर्ण

	/* Found OSDT table, enable the namespace override feature */

	अगर (ACPI_COMPARE_NAMESEG(table->signature, ACPI_SIG_OSDT) &&
	    pass_number == ACPI_IMODE_LOAD_PASS1) अणु
		walk_state->namespace_override = TRUE;
	पूर्ण

	/* start_node is the शेष location to load the table */

	अगर (start_node && start_node != acpi_gbl_root_node) अणु
		status =
		    acpi_ds_scope_stack_push(start_node, ACPI_TYPE_METHOD,
					     walk_state);
		अगर (ACPI_FAILURE(status)) अणु
			acpi_ds_delete_walk_state(walk_state);
			जाओ cleanup;
		पूर्ण
	पूर्ण

	/* Parse the AML */

	ACPI_DEBUG_PRINT((ACPI_DB_PARSE,
			  "*PARSE* pass %u parse\n", pass_number));
	acpi_ex_enter_पूर्णांकerpreter();
	status = acpi_ps_parse_aml(walk_state);
	acpi_ex_निकास_पूर्णांकerpreter();

cleanup:
	acpi_ps_delete_parse_tree(parse_root);
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_parse_table
 *
 * PARAMETERS:  table_desc      - An ACPI table descriptor क्रम table to parse
 *              start_node      - Where to enter the table पूर्णांकo the namespace
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Parse AML within an ACPI table and वापस a tree of ops
 *
 ******************************************************************************/

acpi_status
acpi_ns_parse_table(u32 table_index, काष्ठा acpi_namespace_node *start_node)
अणु
	acpi_status status;

	ACPI_FUNCTION_TRACE(ns_parse_table);

	/*
	 * Executes the AML table as one large control method.
	 * The poपूर्णांक of this is to execute any module-level code in-place
	 * as the table is parsed. Some AML code depends on this behavior.
	 *
	 * Note: This causes the table to only have a single-pass parse.
	 * However, this is compatible with other ACPI implementations.
	 */
	ACPI_DEBUG_PRINT_RAW((ACPI_DB_PARSE,
			      "%s: **** Start table execution pass\n",
			      ACPI_GET_FUNCTION_NAME));

	status = acpi_ns_execute_table(table_index, start_node);

	वापस_ACPI_STATUS(status);
पूर्ण
