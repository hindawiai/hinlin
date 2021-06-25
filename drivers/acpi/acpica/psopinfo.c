<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: psopinfo - AML opcode inक्रमmation functions and dispatch tables
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acparser.h"
#समावेश "acopcode.h"
#समावेश "amlcode.h"

#घोषणा _COMPONENT          ACPI_PARSER
ACPI_MODULE_NAME("psopinfo")

अटल स्थिर u8 acpi_gbl_argument_count[] =
    अणु 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 6 पूर्ण;

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_get_opcode_info
 *
 * PARAMETERS:  opcode              - The AML opcode
 *
 * RETURN:      A poपूर्णांकer to the info about the opcode.
 *
 * DESCRIPTION: Find AML opcode description based on the opcode.
 *              NOTE: This procedure must ALWAYS वापस a valid poपूर्णांकer!
 *
 ******************************************************************************/

स्थिर काष्ठा acpi_opcode_info *acpi_ps_get_opcode_info(u16 opcode)
अणु
#अगर_घोषित ACPI_DEBUG_OUTPUT
	स्थिर अक्षर *opcode_name = "Unknown AML opcode";
#पूर्ण_अगर

	ACPI_FUNCTION_NAME(ps_get_opcode_info);

	/*
	 * Detect normal 8-bit opcode or extended 16-bit opcode
	 */
	अगर (!(opcode & 0xFF00)) अणु

		/* Simple (8-bit) opcode: 0-255, can't index beyond table  */

		वापस (&acpi_gbl_aml_op_info
			[acpi_gbl_लघु_op_index[(u8)opcode]]);
	पूर्ण

	अगर (((opcode & 0xFF00) == AML_EXTENDED_OPCODE) &&
	    (((u8)opcode) <= MAX_EXTENDED_OPCODE)) अणु

		/* Valid extended (16-bit) opcode */

		वापस (&acpi_gbl_aml_op_info
			[acpi_gbl_दीर्घ_op_index[(u8)opcode]]);
	पूर्ण
#अगर defined ACPI_ASL_COMPILER && defined ACPI_DEBUG_OUTPUT
#समावेश "asldefine.h"

	चयन (opcode) अणु
	हाल AML_RAW_DATA_BYTE:
		opcode_name = "-Raw Data Byte-";
		अवरोध;

	हाल AML_RAW_DATA_WORD:
		opcode_name = "-Raw Data Word-";
		अवरोध;

	हाल AML_RAW_DATA_DWORD:
		opcode_name = "-Raw Data Dword-";
		अवरोध;

	हाल AML_RAW_DATA_QWORD:
		opcode_name = "-Raw Data Qword-";
		अवरोध;

	हाल AML_RAW_DATA_BUFFER:
		opcode_name = "-Raw Data Buffer-";
		अवरोध;

	हाल AML_RAW_DATA_CHAIN:
		opcode_name = "-Raw Data Buffer Chain-";
		अवरोध;

	हाल AML_PACKAGE_LENGTH:
		opcode_name = "-Package Length-";
		अवरोध;

	हाल AML_UNASSIGNED_OPCODE:
		opcode_name = "-Unassigned Opcode-";
		अवरोध;

	हाल AML_DEFAULT_ARG_OP:
		opcode_name = "-Default Arg-";
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
#पूर्ण_अगर

	/* Unknown AML opcode */

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC, "%s [%4.4X]\n", opcode_name, opcode));

	वापस (&acpi_gbl_aml_op_info[_UNK]);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_get_opcode_name
 *
 * PARAMETERS:  opcode              - The AML opcode
 *
 * RETURN:      A poपूर्णांकer to the name of the opcode (ASCII String)
 *              Note: Never वापसs शून्य.
 *
 * DESCRIPTION: Translate an opcode पूर्णांकo a human-पढ़ोable string
 *
 ******************************************************************************/

स्थिर अक्षर *acpi_ps_get_opcode_name(u16 opcode)
अणु
#अगर defined(ACPI_DISASSEMBLER) || defined (ACPI_DEBUG_OUTPUT)

	स्थिर काष्ठा acpi_opcode_info *op;

	op = acpi_ps_get_opcode_info(opcode);

	/* Always guaranteed to वापस a valid poपूर्णांकer */

	वापस (op->name);

#अन्यथा
	वापस ("OpcodeName unavailable");

#पूर्ण_अगर
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_get_argument_count
 *
 * PARAMETERS:  op_type             - Type associated with the AML opcode
 *
 * RETURN:      Argument count
 *
 * DESCRIPTION: Obtain the number of expected arguments क्रम an AML opcode
 *
 ******************************************************************************/

u8 acpi_ps_get_argument_count(u32 op_type)
अणु

	अगर (op_type <= AML_TYPE_EXEC_6A_0T_1R) अणु
		वापस (acpi_gbl_argument_count[op_type]);
	पूर्ण

	वापस (0);
पूर्ण

/*
 * This table is directly indexed by the opcodes It वापसs
 * an index पूर्णांकo the opcode table (acpi_gbl_aml_op_info)
 */
स्थिर u8 acpi_gbl_लघु_op_index[256] = अणु
/*              0     1     2     3     4     5     6     7  */
/*              8     9     A     B     C     D     E     F  */
/* 0x00 */ 0x00, 0x01, _UNK, _UNK, _UNK, _UNK, 0x02, _UNK,
/* 0x08 */ 0x03, _UNK, 0x04, 0x05, 0x06, 0x07, 0x6E, _UNK,
/* 0x10 */ 0x08, 0x09, 0x0a, 0x6F, 0x0b, 0x81, _UNK, _UNK,
/* 0x18 */ _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0x20 */ _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0x28 */ _UNK, _UNK, _UNK, _UNK, _UNK, 0x63, _PFX, _PFX,
/* 0x30 */ 0x67, 0x66, 0x68, 0x65, 0x69, 0x64, 0x6A, 0x7D,
/* 0x38 */ 0x7F, 0x80, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0x40 */ _UNK, _ASC, _ASC, _ASC, _ASC, _ASC, _ASC, _ASC,
/* 0x48 */ _ASC, _ASC, _ASC, _ASC, _ASC, _ASC, _ASC, _ASC,
/* 0x50 */ _ASC, _ASC, _ASC, _ASC, _ASC, _ASC, _ASC, _ASC,
/* 0x58 */ _ASC, _ASC, _ASC, _UNK, _PFX, _UNK, _PFX, _ASC,
/* 0x60 */ 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13,
/* 0x68 */ 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, _UNK,
/* 0x70 */ 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x22,
/* 0x78 */ 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a,
/* 0x80 */ 0x2b, 0x2c, 0x2d, 0x2e, 0x70, 0x71, 0x2f, 0x30,
/* 0x88 */ 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x72,
/* 0x90 */ 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x73, 0x74,
/* 0x98 */ 0x75, 0x76, _UNK, _UNK, 0x77, 0x78, 0x79, 0x7A,
/* 0xA0 */ 0x3e, 0x3f, 0x40, 0x41, 0x42, 0x43, 0x60, 0x61,
/* 0xA8 */ 0x62, 0x82, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0xB0 */ _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0xB8 */ _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0xC0 */ _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0xC8 */ _UNK, _UNK, _UNK, _UNK, 0x44, _UNK, _UNK, _UNK,
/* 0xD0 */ _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0xD8 */ _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0xE0 */ _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0xE8 */ _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0xF0 */ _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0xF8 */ _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, 0x45,
पूर्ण;

/*
 * This table is indexed by the second opcode of the extended opcode
 * pair. It वापसs an index पूर्णांकo the opcode table (acpi_gbl_aml_op_info)
 */
स्थिर u8 acpi_gbl_दीर्घ_op_index[NUM_EXTENDED_OPCODE] = अणु
/*              0     1     2     3     4     5     6     7  */
/*              8     9     A     B     C     D     E     F  */
/* 0x00 */ _UNK, 0x46, 0x47, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0x08 */ _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0x10 */ _UNK, _UNK, 0x48, 0x49, _UNK, _UNK, _UNK, _UNK,
/* 0x18 */ _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, 0x7B,
/* 0x20 */ 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f, 0x50, 0x51,
/* 0x28 */ 0x52, 0x53, 0x54, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0x30 */ 0x55, 0x56, 0x57, 0x7e, _UNK, _UNK, _UNK, _UNK,
/* 0x38 */ _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0x40 */ _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0x48 */ _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0x50 */ _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0x58 */ _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0x60 */ _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0x68 */ _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0x70 */ _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0x78 */ _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK, _UNK,
/* 0x80 */ 0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f,
/* 0x88 */ 0x7C,
पूर्ण;
