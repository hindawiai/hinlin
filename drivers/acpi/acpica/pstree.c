<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: pstree - Parser op tree manipulation/traversal/search
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acparser.h"
#समावेश "amlcode.h"
#समावेश "acconvert.h"

#घोषणा _COMPONENT          ACPI_PARSER
ACPI_MODULE_NAME("pstree")

/* Local prototypes */
#अगर_घोषित ACPI_OBSOLETE_FUNCTIONS
जोड़ acpi_parse_object *acpi_ps_get_child(जोड़ acpi_parse_object *op);
#पूर्ण_अगर

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_get_arg
 *
 * PARAMETERS:  op              - Get an argument क्रम this op
 *              argn            - Nth argument to get
 *
 * RETURN:      The argument (as an Op object). शून्य अगर argument करोes not exist
 *
 * DESCRIPTION: Get the specअगरied op's argument.
 *
 ******************************************************************************/

जोड़ acpi_parse_object *acpi_ps_get_arg(जोड़ acpi_parse_object *op, u32 argn)
अणु
	जोड़ acpi_parse_object *arg = शून्य;
	स्थिर काष्ठा acpi_opcode_info *op_info;

	ACPI_FUNCTION_ENTRY();

/*
	अगर (Op->Common.aml_opcode == AML_INT_CONNECTION_OP)
	अणु
		वापस (Op->Common.Value.Arg);
	पूर्ण
*/
	/* Get the info काष्ठाure क्रम this opcode */

	op_info = acpi_ps_get_opcode_info(op->common.aml_opcode);
	अगर (op_info->class == AML_CLASS_UNKNOWN) अणु

		/* Invalid opcode or ASCII अक्षरacter */

		वापस (शून्य);
	पूर्ण

	/* Check अगर this opcode requires argument sub-objects */

	अगर (!(op_info->flags & AML_HAS_ARGS)) अणु

		/* Has no linked argument objects */

		वापस (शून्य);
	पूर्ण

	/* Get the requested argument object */

	arg = op->common.value.arg;
	जबतक (arg && argn) अणु
		argn--;
		arg = arg->common.next;
	पूर्ण

	वापस (arg);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_append_arg
 *
 * PARAMETERS:  op              - Append an argument to this Op.
 *              arg             - Argument Op to append
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Append an argument to an op's argument list (a शून्य arg is OK)
 *
 ******************************************************************************/

व्योम
acpi_ps_append_arg(जोड़ acpi_parse_object *op, जोड़ acpi_parse_object *arg)
अणु
	जोड़ acpi_parse_object *prev_arg;
	स्थिर काष्ठा acpi_opcode_info *op_info;

	ACPI_FUNCTION_TRACE(ps_append_arg);

	अगर (!op) अणु
		वापस_VOID;
	पूर्ण

	/* Get the info काष्ठाure क्रम this opcode */

	op_info = acpi_ps_get_opcode_info(op->common.aml_opcode);
	अगर (op_info->class == AML_CLASS_UNKNOWN) अणु

		/* Invalid opcode */

		ACPI_ERROR((AE_INFO, "Invalid AML Opcode: 0x%2.2X",
			    op->common.aml_opcode));
		वापस_VOID;
	पूर्ण

	/* Check अगर this opcode requires argument sub-objects */

	अगर (!(op_info->flags & AML_HAS_ARGS)) अणु

		/* Has no linked argument objects */

		वापस_VOID;
	पूर्ण

	/* Append the argument to the linked argument list */

	अगर (op->common.value.arg) अणु

		/* Append to existing argument list */

		prev_arg = op->common.value.arg;
		जबतक (prev_arg->common.next) अणु
			prev_arg = prev_arg->common.next;
		पूर्ण
		prev_arg->common.next = arg;
	पूर्ण अन्यथा अणु
		/* No argument list, this will be the first argument */

		op->common.value.arg = arg;
	पूर्ण

	/* Set the parent in this arg and any args linked after it */

	जबतक (arg) अणु
		arg->common.parent = op;
		arg = arg->common.next;

		op->common.arg_list_length++;
	पूर्ण

	वापस_VOID;
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_get_depth_next
 *
 * PARAMETERS:  origin          - Root of subtree to search
 *              op              - Last (previous) Op that was found
 *
 * RETURN:      Next Op found in the search.
 *
 * DESCRIPTION: Get next op in tree (walking the tree in depth-first order)
 *              Return शून्य when reaching "origin" or when walking up from root
 *
 ******************************************************************************/

जोड़ acpi_parse_object *acpi_ps_get_depth_next(जोड़ acpi_parse_object *origin,
						जोड़ acpi_parse_object *op)
अणु
	जोड़ acpi_parse_object *next = शून्य;
	जोड़ acpi_parse_object *parent;
	जोड़ acpi_parse_object *arg;

	ACPI_FUNCTION_ENTRY();

	अगर (!op) अणु
		वापस (शून्य);
	पूर्ण

	/* Look क्रम an argument or child */

	next = acpi_ps_get_arg(op, 0);
	अगर (next) अणु
		ASL_CV_LABEL_खाताNODE(next);
		वापस (next);
	पूर्ण

	/* Look क्रम a sibling */

	next = op->common.next;
	अगर (next) अणु
		ASL_CV_LABEL_खाताNODE(next);
		वापस (next);
	पूर्ण

	/* Look क्रम a sibling of parent */

	parent = op->common.parent;

	जबतक (parent) अणु
		arg = acpi_ps_get_arg(parent, 0);
		जबतक (arg && (arg != origin) && (arg != op)) अणु

			ASL_CV_LABEL_खाताNODE(arg);
			arg = arg->common.next;
		पूर्ण

		अगर (arg == origin) अणु

			/* Reached parent of origin, end search */

			वापस (शून्य);
		पूर्ण

		अगर (parent->common.next) अणु

			/* Found sibling of parent */

			ASL_CV_LABEL_खाताNODE(parent->common.next);
			वापस (parent->common.next);
		पूर्ण

		op = parent;
		parent = parent->common.parent;
	पूर्ण

	ASL_CV_LABEL_खाताNODE(next);
	वापस (next);
पूर्ण

#अगर_घोषित ACPI_OBSOLETE_FUNCTIONS
/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_get_child
 *
 * PARAMETERS:  op              - Get the child of this Op
 *
 * RETURN:      Child Op, Null अगर none is found.
 *
 * DESCRIPTION: Get op's children or शून्य अगर none
 *
 ******************************************************************************/

जोड़ acpi_parse_object *acpi_ps_get_child(जोड़ acpi_parse_object *op)
अणु
	जोड़ acpi_parse_object *child = शून्य;

	ACPI_FUNCTION_ENTRY();

	चयन (op->common.aml_opcode) अणु
	हाल AML_SCOPE_OP:
	हाल AML_ELSE_OP:
	हाल AML_DEVICE_OP:
	हाल AML_THERMAL_ZONE_OP:
	हाल AML_INT_METHODCALL_OP:

		child = acpi_ps_get_arg(op, 0);
		अवरोध;

	हाल AML_BUFFER_OP:
	हाल AML_PACKAGE_OP:
	हाल AML_VARIABLE_PACKAGE_OP:
	हाल AML_METHOD_OP:
	हाल AML_IF_OP:
	हाल AML_WHILE_OP:
	हाल AML_FIELD_OP:

		child = acpi_ps_get_arg(op, 1);
		अवरोध;

	हाल AML_POWER_RESOURCE_OP:
	हाल AML_INDEX_FIELD_OP:

		child = acpi_ps_get_arg(op, 2);
		अवरोध;

	हाल AML_PROCESSOR_OP:
	हाल AML_BANK_FIELD_OP:

		child = acpi_ps_get_arg(op, 3);
		अवरोध;

	शेष:

		/* All others have no children */

		अवरोध;
	पूर्ण

	वापस (child);
पूर्ण
#पूर्ण_अगर
