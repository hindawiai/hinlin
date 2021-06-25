<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: pswalk - Parser routines to walk parsed op tree(s)
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acparser.h"

#घोषणा _COMPONENT          ACPI_PARSER
ACPI_MODULE_NAME("pswalk")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_delete_parse_tree
 *
 * PARAMETERS:  subtree_root        - Root of tree (or subtree) to delete
 *
 * RETURN:      None
 *
 * DESCRIPTION: Delete a portion of or an entire parse tree.
 *
 ******************************************************************************/
#समावेश "amlcode.h"
व्योम acpi_ps_delete_parse_tree(जोड़ acpi_parse_object *subtree_root)
अणु
	जोड़ acpi_parse_object *op = subtree_root;
	जोड़ acpi_parse_object *next = शून्य;
	जोड़ acpi_parse_object *parent = शून्य;
	u32 level = 0;

	ACPI_FUNCTION_TRACE_PTR(ps_delete_parse_tree, subtree_root);

	ACPI_DEBUG_PRINT((ACPI_DB_PARSE_TREES, " root %p\n", subtree_root));

	/* Visit all nodes in the subtree */

	जबतक (op) अणु
		अगर (op != parent) अणु

			/* This is the descending हाल */

			अगर (ACPI_IS_DEBUG_ENABLED
			    (ACPI_LV_PARSE_TREES, _COMPONENT)) अणु

				/* This debug option will prपूर्णांक the entire parse tree */

				acpi_os_म_लिखो("      %*.s%s %p", (level * 4),
					       " ",
					       acpi_ps_get_opcode_name(op->
								       common.
								       aml_opcode),
					       op);

				अगर (op->named.aml_opcode == AML_INT_NAMEPATH_OP) अणु
					acpi_os_म_लिखो("  %4.4s",
						       op->common.value.string);
				पूर्ण
				अगर (op->named.aml_opcode == AML_STRING_OP) अणु
					acpi_os_म_लिखो("  %s",
						       op->common.value.string);
				पूर्ण
				acpi_os_म_लिखो("\n");
			पूर्ण

			/* Look क्रम an argument or child of the current op */

			next = acpi_ps_get_arg(op, 0);
			अगर (next) अणु

				/* Still going करोwnward in tree (Op is not completed yet) */

				op = next;
				level++;
				जारी;
			पूर्ण
		पूर्ण

		/* No more children, this Op is complete. */

		next = op->common.next;
		parent = op->common.parent;

		acpi_ps_मुक्त_op(op);

		/* If we are back to the starting poपूर्णांक, the walk is complete. */

		अगर (op == subtree_root) अणु
			वापस_VOID;
		पूर्ण

		अगर (next) अणु
			op = next;
		पूर्ण अन्यथा अणु
			level--;
			op = parent;
		पूर्ण
	पूर्ण

	वापस_VOID;
पूर्ण
