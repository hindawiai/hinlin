<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: psutils - Parser miscellaneous utilities (Parser only)
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
ACPI_MODULE_NAME("psutils")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_create_scope_op
 *
 * PARAMETERS:  None
 *
 * RETURN:      A new Scope object, null on failure
 *
 * DESCRIPTION: Create a Scope and associated namepath op with the root name
 *
 ******************************************************************************/
जोड़ acpi_parse_object *acpi_ps_create_scope_op(u8 *aml)
अणु
	जोड़ acpi_parse_object *scope_op;

	scope_op = acpi_ps_alloc_op(AML_SCOPE_OP, aml);
	अगर (!scope_op) अणु
		वापस (शून्य);
	पूर्ण

	scope_op->named.name = ACPI_ROOT_NAME;
	वापस (scope_op);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_init_op
 *
 * PARAMETERS:  op              - A newly allocated Op object
 *              opcode          - Opcode to store in the Op
 *
 * RETURN:      None
 *
 * DESCRIPTION: Initialize a parse (Op) object
 *
 ******************************************************************************/

व्योम acpi_ps_init_op(जोड़ acpi_parse_object *op, u16 opcode)
अणु
	ACPI_FUNCTION_ENTRY();

	op->common.descriptor_type = ACPI_DESC_TYPE_PARSER;
	op->common.aml_opcode = opcode;

	ACPI_DISASM_ONLY_MEMBERS(acpi_ut_safe_म_नकलन(op->common.aml_op_name,
						      (acpi_ps_get_opcode_info
						       (opcode))->name,
						      माप(op->common.
							     aml_op_name)));
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_alloc_op
 *
 * PARAMETERS:  opcode          - Opcode that will be stored in the new Op
 *              aml             - Address of the opcode
 *
 * RETURN:      Poपूर्णांकer to the new Op, null on failure
 *
 * DESCRIPTION: Allocate an acpi_op, choose op type (and thus size) based on
 *              opcode. A cache of opcodes is available क्रम the pure
 *              GENERIC_OP, since this is by far the most commonly used.
 *
 ******************************************************************************/

जोड़ acpi_parse_object *acpi_ps_alloc_op(u16 opcode, u8 *aml)
अणु
	जोड़ acpi_parse_object *op;
	स्थिर काष्ठा acpi_opcode_info *op_info;
	u8 flags = ACPI_PARSEOP_GENERIC;

	ACPI_FUNCTION_ENTRY();

	op_info = acpi_ps_get_opcode_info(opcode);

	/* Determine type of parse_op required */

	अगर (op_info->flags & AML_DEFER) अणु
		flags = ACPI_PARSEOP_DEFERRED;
	पूर्ण अन्यथा अगर (op_info->flags & AML_NAMED) अणु
		flags = ACPI_PARSEOP_NAMED_OBJECT;
	पूर्ण अन्यथा अगर (opcode == AML_INT_BYTELIST_OP) अणु
		flags = ACPI_PARSEOP_BYTELIST;
	पूर्ण

	/* Allocate the minimum required size object */

	अगर (flags == ACPI_PARSEOP_GENERIC) अणु

		/* The generic op (शेष) is by far the most common (16 to 1) */

		op = acpi_os_acquire_object(acpi_gbl_ps_node_cache);
	पूर्ण अन्यथा अणु
		/* Extended parseop */

		op = acpi_os_acquire_object(acpi_gbl_ps_node_ext_cache);
	पूर्ण

	/* Initialize the Op */

	अगर (op) अणु
		acpi_ps_init_op(op, opcode);
		op->common.aml = aml;
		op->common.flags = flags;
		ASL_CV_CLEAR_OP_COMMENTS(op);

		अगर (opcode == AML_SCOPE_OP) अणु
			acpi_gbl_current_scope = op;
		पूर्ण

		अगर (acpi_gbl_capture_comments) अणु
			ASL_CV_TRANSFER_COMMENTS(op);
		पूर्ण
	पूर्ण

	वापस (op);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_मुक्त_op
 *
 * PARAMETERS:  op              - Op to be मुक्तd
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Free an Op object. Either put it on the GENERIC_OP cache list
 *              or actually मुक्त it.
 *
 ******************************************************************************/

व्योम acpi_ps_मुक्त_op(जोड़ acpi_parse_object *op)
अणु
	ACPI_FUNCTION_NAME(ps_मुक्त_op);

	ASL_CV_CLEAR_OP_COMMENTS(op);
	अगर (op->common.aml_opcode == AML_INT_RETURN_VALUE_OP) अणु
		ACPI_DEBUG_PRINT((ACPI_DB_ALLOCATIONS,
				  "Free retval op: %p\n", op));
	पूर्ण

	अगर (op->common.flags & ACPI_PARSEOP_GENERIC) अणु
		(व्योम)acpi_os_release_object(acpi_gbl_ps_node_cache, op);
	पूर्ण अन्यथा अणु
		(व्योम)acpi_os_release_object(acpi_gbl_ps_node_ext_cache, op);
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    Utility functions
 *
 * DESCRIPTION: Low level अक्षरacter and object functions
 *
 ******************************************************************************/

/*
 * Is "c" a namestring lead अक्षरacter?
 */
u8 acpi_ps_is_leading_अक्षर(u32 c)
अणु
	वापस ((u8) (c == '_' || (c >= 'A' && c <= 'Z')));
पूर्ण

/*
 * Get op's name (4-byte name segment) or 0 अगर unnamed
 */
u32 acpi_ps_get_name(जोड़ acpi_parse_object * op)
अणु

	/* The "generic" object has no name associated with it */

	अगर (op->common.flags & ACPI_PARSEOP_GENERIC) अणु
		वापस (0);
	पूर्ण

	/* Only the "Extended" parse objects have a name */

	वापस (op->named.name);
पूर्ण

/*
 * Set op's name
 */
व्योम acpi_ps_set_name(जोड़ acpi_parse_object *op, u32 name)
अणु

	/* The "generic" object has no name associated with it */

	अगर (op->common.flags & ACPI_PARSEOP_GENERIC) अणु
		वापस;
	पूर्ण

	op->named.name = name;
पूर्ण
