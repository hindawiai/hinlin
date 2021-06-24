<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: exmisc - ACPI AML (p-code) execution - specअगरic opcodes
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acinterp.h"
#समावेश "amlcode.h"

#घोषणा _COMPONENT          ACPI_EXECUTER
ACPI_MODULE_NAME("exmisc")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_get_object_reference
 *
 * PARAMETERS:  obj_desc            - Create a reference to this object
 *              वापस_desc         - Where to store the reference
 *              walk_state          - Current state
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Obtain and वापस a "reference" to the target object
 *              Common code क्रम the ref_of_op and the cond_ref_of_op.
 *
 ******************************************************************************/
acpi_status
acpi_ex_get_object_reference(जोड़ acpi_opeअक्रम_object *obj_desc,
			     जोड़ acpi_opeअक्रम_object **वापस_desc,
			     काष्ठा acpi_walk_state *walk_state)
अणु
	जोड़ acpi_opeअक्रम_object *reference_obj;
	जोड़ acpi_opeअक्रम_object *referenced_obj;

	ACPI_FUNCTION_TRACE_PTR(ex_get_object_reference, obj_desc);

	*वापस_desc = शून्य;

	चयन (ACPI_GET_DESCRIPTOR_TYPE(obj_desc)) अणु
	हाल ACPI_DESC_TYPE_OPERAND:

		अगर (obj_desc->common.type != ACPI_TYPE_LOCAL_REFERENCE) अणु
			वापस_ACPI_STATUS(AE_AML_OPERAND_TYPE);
		पूर्ण

		/*
		 * Must be a reference to a Local or Arg
		 */
		चयन (obj_desc->reference.class) अणु
		हाल ACPI_REFCLASS_LOCAL:
		हाल ACPI_REFCLASS_ARG:
		हाल ACPI_REFCLASS_DEBUG:

			/* The referenced object is the pseuकरो-node क्रम the local/arg */

			referenced_obj = obj_desc->reference.object;
			अवरोध;

		शेष:

			ACPI_ERROR((AE_INFO, "Invalid Reference Class 0x%2.2X",
				    obj_desc->reference.class));
			वापस_ACPI_STATUS(AE_AML_OPERAND_TYPE);
		पूर्ण
		अवरोध;

	हाल ACPI_DESC_TYPE_NAMED:
		/*
		 * A named reference that has alपढ़ोy been resolved to a Node
		 */
		referenced_obj = obj_desc;
		अवरोध;

	शेष:

		ACPI_ERROR((AE_INFO, "Invalid descriptor type 0x%X",
			    ACPI_GET_DESCRIPTOR_TYPE(obj_desc)));
		वापस_ACPI_STATUS(AE_TYPE);
	पूर्ण

	/* Create a new reference object */

	reference_obj =
	    acpi_ut_create_पूर्णांकernal_object(ACPI_TYPE_LOCAL_REFERENCE);
	अगर (!reference_obj) अणु
		वापस_ACPI_STATUS(AE_NO_MEMORY);
	पूर्ण

	reference_obj->reference.class = ACPI_REFCLASS_REFOF;
	reference_obj->reference.object = referenced_obj;
	*वापस_desc = reference_obj;

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
			  "Object %p Type [%s], returning Reference %p\n",
			  obj_desc, acpi_ut_get_object_type_name(obj_desc),
			  *वापस_desc));

	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_करो_math_op
 *
 * PARAMETERS:  opcode              - AML opcode
 *              पूर्णांकeger0            - Integer opeअक्रम #0
 *              पूर्णांकeger1            - Integer opeअक्रम #1
 *
 * RETURN:      Integer result of the operation
 *
 * DESCRIPTION: Execute a math AML opcode. The purpose of having all of the
 *              math functions here is to prevent a lot of poपूर्णांकer dereferencing
 *              to obtain the opeअक्रमs.
 *
 ******************************************************************************/

u64 acpi_ex_करो_math_op(u16 opcode, u64 पूर्णांकeger0, u64 पूर्णांकeger1)
अणु

	ACPI_FUNCTION_ENTRY();

	चयन (opcode) अणु
	हाल AML_ADD_OP:	/* Add (Integer0, Integer1, Result) */

		वापस (पूर्णांकeger0 + पूर्णांकeger1);

	हाल AML_BIT_AND_OP:	/* And (Integer0, Integer1, Result) */

		वापस (पूर्णांकeger0 & पूर्णांकeger1);

	हाल AML_BIT_न_अंकD_OP:	/* NAnd (Integer0, Integer1, Result) */

		वापस (~(पूर्णांकeger0 & पूर्णांकeger1));

	हाल AML_BIT_OR_OP:	/* Or (Integer0, Integer1, Result) */

		वापस (पूर्णांकeger0 | पूर्णांकeger1);

	हाल AML_BIT_NOR_OP:	/* NOr (Integer0, Integer1, Result) */

		वापस (~(पूर्णांकeger0 | पूर्णांकeger1));

	हाल AML_BIT_XOR_OP:	/* XOr (Integer0, Integer1, Result) */

		वापस (पूर्णांकeger0 ^ पूर्णांकeger1);

	हाल AML_MULTIPLY_OP:	/* Multiply (Integer0, Integer1, Result) */

		वापस (पूर्णांकeger0 * पूर्णांकeger1);

	हाल AML_SHIFT_LEFT_OP:	/* shअगरt_left (Opeअक्रम, shअगरt_count, Result) */

		/*
		 * We need to check अगर the shअगरtcount is larger than the पूर्णांकeger bit
		 * width since the behavior of this is not well-defined in the C language.
		 */
		अगर (पूर्णांकeger1 >= acpi_gbl_पूर्णांकeger_bit_width) अणु
			वापस (0);
		पूर्ण
		वापस (पूर्णांकeger0 << पूर्णांकeger1);

	हाल AML_SHIFT_RIGHT_OP:	/* shअगरt_right (Opeअक्रम, shअगरt_count, Result) */

		/*
		 * We need to check अगर the shअगरtcount is larger than the पूर्णांकeger bit
		 * width since the behavior of this is not well-defined in the C language.
		 */
		अगर (पूर्णांकeger1 >= acpi_gbl_पूर्णांकeger_bit_width) अणु
			वापस (0);
		पूर्ण
		वापस (पूर्णांकeger0 >> पूर्णांकeger1);

	हाल AML_SUBTRACT_OP:	/* Subtract (Integer0, Integer1, Result) */

		वापस (पूर्णांकeger0 - पूर्णांकeger1);

	शेष:

		वापस (0);
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_करो_logical_numeric_op
 *
 * PARAMETERS:  opcode              - AML opcode
 *              पूर्णांकeger0            - Integer opeअक्रम #0
 *              पूर्णांकeger1            - Integer opeअक्रम #1
 *              logical_result      - TRUE/FALSE result of the operation
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Execute a logical "Numeric" AML opcode. For these Numeric
 *              चालकs (LAnd and LOr), both opeअक्रमs must be पूर्णांकegers.
 *
 *              Note: cleanest machine code seems to be produced by the code
 *              below, rather than using statements of the क्रमm:
 *                  Result = (Integer0 && Integer1);
 *
 ******************************************************************************/

acpi_status
acpi_ex_करो_logical_numeric_op(u16 opcode,
			      u64 पूर्णांकeger0, u64 पूर्णांकeger1, u8 *logical_result)
अणु
	acpi_status status = AE_OK;
	u8 local_result = FALSE;

	ACPI_FUNCTION_TRACE(ex_करो_logical_numeric_op);

	चयन (opcode) अणु
	हाल AML_LOGICAL_AND_OP:	/* LAnd (Integer0, Integer1) */

		अगर (पूर्णांकeger0 && पूर्णांकeger1) अणु
			local_result = TRUE;
		पूर्ण
		अवरोध;

	हाल AML_LOGICAL_OR_OP:	/* LOr (Integer0, Integer1) */

		अगर (पूर्णांकeger0 || पूर्णांकeger1) अणु
			local_result = TRUE;
		पूर्ण
		अवरोध;

	शेष:

		ACPI_ERROR((AE_INFO,
			    "Invalid numeric logical opcode: %X", opcode));
		status = AE_AML_INTERNAL;
		अवरोध;
	पूर्ण

	/* Return the logical result and status */

	*logical_result = local_result;
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_करो_logical_op
 *
 * PARAMETERS:  opcode              - AML opcode
 *              opeअक्रम0            - opeअक्रम #0
 *              opeअक्रम1            - opeअक्रम #1
 *              logical_result      - TRUE/FALSE result of the operation
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Execute a logical AML opcode. The purpose of having all of the
 *              functions here is to prevent a lot of poपूर्णांकer dereferencing
 *              to obtain the opeअक्रमs and to simplअगरy the generation of the
 *              logical value. For the Numeric चालकs (LAnd and LOr), both
 *              opeअक्रमs must be पूर्णांकegers. For the other logical चालकs,
 *              opeअक्रमs can be any combination of Integer/String/Buffer. The
 *              first opeअक्रम determines the type to which the second opeअक्रम
 *              will be converted.
 *
 *              Note: cleanest machine code seems to be produced by the code
 *              below, rather than using statements of the क्रमm:
 *                  Result = (Opeअक्रम0 == Opeअक्रम1);
 *
 ******************************************************************************/

acpi_status
acpi_ex_करो_logical_op(u16 opcode,
		      जोड़ acpi_opeअक्रम_object *opeअक्रम0,
		      जोड़ acpi_opeअक्रम_object *opeअक्रम1, u8 * logical_result)
अणु
	जोड़ acpi_opeअक्रम_object *local_opeअक्रम1 = opeअक्रम1;
	u64 पूर्णांकeger0;
	u64 पूर्णांकeger1;
	u32 length0;
	u32 length1;
	acpi_status status = AE_OK;
	u8 local_result = FALSE;
	पूर्णांक compare;

	ACPI_FUNCTION_TRACE(ex_करो_logical_op);

	/*
	 * Convert the second opeअक्रम अगर necessary. The first opeअक्रम
	 * determines the type of the second opeअक्रम, (See the Data Types
	 * section of the ACPI 3.0+ specअगरication.)  Both object types are
	 * guaranteed to be either Integer/String/Buffer by the opeअक्रम
	 * resolution mechanism.
	 */
	चयन (opeअक्रम0->common.type) अणु
	हाल ACPI_TYPE_INTEGER:

		status = acpi_ex_convert_to_पूर्णांकeger(opeअक्रम1, &local_opeअक्रम1,
						    ACPI_IMPLICIT_CONVERSION);
		अवरोध;

	हाल ACPI_TYPE_STRING:

		status =
		    acpi_ex_convert_to_string(opeअक्रम1, &local_opeअक्रम1,
					      ACPI_IMPLICIT_CONVERT_HEX);
		अवरोध;

	हाल ACPI_TYPE_BUFFER:

		status = acpi_ex_convert_to_buffer(opeअक्रम1, &local_opeअक्रम1);
		अवरोध;

	शेष:

		ACPI_ERROR((AE_INFO,
			    "Invalid object type for logical operator: %X",
			    opeअक्रम0->common.type));
		status = AE_AML_INTERNAL;
		अवरोध;
	पूर्ण

	अगर (ACPI_FAILURE(status)) अणु
		जाओ cleanup;
	पूर्ण

	/*
	 * Two हालs: 1) Both Integers, 2) Both Strings or Buffers
	 */
	अगर (opeअक्रम0->common.type == ACPI_TYPE_INTEGER) अणु
		/*
		 * 1) Both opeअक्रमs are of type पूर्णांकeger
		 *    Note: local_opeअक्रम1 may have changed above
		 */
		पूर्णांकeger0 = opeअक्रम0->पूर्णांकeger.value;
		पूर्णांकeger1 = local_opeअक्रम1->पूर्णांकeger.value;

		चयन (opcode) अणु
		हाल AML_LOGICAL_EQUAL_OP:	/* LEqual (Opeअक्रम0, Opeअक्रम1) */

			अगर (पूर्णांकeger0 == पूर्णांकeger1) अणु
				local_result = TRUE;
			पूर्ण
			अवरोध;

		हाल AML_LOGICAL_GREATER_OP:	/* LGreater (Opeअक्रम0, Opeअक्रम1) */

			अगर (पूर्णांकeger0 > पूर्णांकeger1) अणु
				local_result = TRUE;
			पूर्ण
			अवरोध;

		हाल AML_LOGICAL_LESS_OP:	/* LLess (Opeअक्रम0, Opeअक्रम1) */

			अगर (पूर्णांकeger0 < पूर्णांकeger1) अणु
				local_result = TRUE;
			पूर्ण
			अवरोध;

		शेष:

			ACPI_ERROR((AE_INFO,
				    "Invalid comparison opcode: %X", opcode));
			status = AE_AML_INTERNAL;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * 2) Both opeअक्रमs are Strings or both are Buffers
		 *    Note: Code below takes advantage of common Buffer/String
		 *          object fields. local_opeअक्रम1 may have changed above. Use
		 *          स_भेद to handle nulls in buffers.
		 */
		length0 = opeअक्रम0->buffer.length;
		length1 = local_opeअक्रम1->buffer.length;

		/* Lexicographic compare: compare the data bytes */

		compare = स_भेद(opeअक्रम0->buffer.poपूर्णांकer,
				 local_opeअक्रम1->buffer.poपूर्णांकer,
				 (length0 > length1) ? length1 : length0);

		चयन (opcode) अणु
		हाल AML_LOGICAL_EQUAL_OP:	/* LEqual (Opeअक्रम0, Opeअक्रम1) */

			/* Length and all bytes must be equal */

			अगर ((length0 == length1) && (compare == 0)) अणु

				/* Length and all bytes match ==> TRUE */

				local_result = TRUE;
			पूर्ण
			अवरोध;

		हाल AML_LOGICAL_GREATER_OP:	/* LGreater (Opeअक्रम0, Opeअक्रम1) */

			अगर (compare > 0) अणु
				local_result = TRUE;
				जाओ cleanup;	/* TRUE */
			पूर्ण
			अगर (compare < 0) अणु
				जाओ cleanup;	/* FALSE */
			पूर्ण

			/* Bytes match (to लघुest length), compare lengths */

			अगर (length0 > length1) अणु
				local_result = TRUE;
			पूर्ण
			अवरोध;

		हाल AML_LOGICAL_LESS_OP:	/* LLess (Opeअक्रम0, Opeअक्रम1) */

			अगर (compare > 0) अणु
				जाओ cleanup;	/* FALSE */
			पूर्ण
			अगर (compare < 0) अणु
				local_result = TRUE;
				जाओ cleanup;	/* TRUE */
			पूर्ण

			/* Bytes match (to लघुest length), compare lengths */

			अगर (length0 < length1) अणु
				local_result = TRUE;
			पूर्ण
			अवरोध;

		शेष:

			ACPI_ERROR((AE_INFO,
				    "Invalid comparison opcode: %X", opcode));
			status = AE_AML_INTERNAL;
			अवरोध;
		पूर्ण
	पूर्ण

cleanup:

	/* New object was created अगर implicit conversion perक्रमmed - delete */

	अगर (local_opeअक्रम1 != opeअक्रम1) अणु
		acpi_ut_हटाओ_reference(local_opeअक्रम1);
	पूर्ण

	/* Return the logical result and status */

	*logical_result = local_result;
	वापस_ACPI_STATUS(status);
पूर्ण
