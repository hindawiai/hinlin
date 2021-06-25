<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: exoparg6 - AML execution - opcodes with 6 arguments
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acinterp.h"
#समावेश "acparser.h"
#समावेश "amlcode.h"

#घोषणा _COMPONENT          ACPI_EXECUTER
ACPI_MODULE_NAME("exoparg6")

/*!
 * Naming convention क्रम AML पूर्णांकerpreter execution routines.
 *
 * The routines that begin execution of AML opcodes are named with a common
 * convention based upon the number of arguments, the number of target opeअक्रमs,
 * and whether or not a value is वापसed:
 *
 *      AcpiExOpcode_xA_yT_zR
 *
 * Where:
 *
 * xA - ARGUMENTS:    The number of arguments (input opeअक्रमs) that are
 *                    required क्रम this opcode type (1 through 6 args).
 * yT - TARGETS:      The number of tarमाला_लो (output opeअक्रमs) that are required
 *                    क्रम this opcode type (0, 1, or 2 tarमाला_लो).
 * zR - RETURN VALUE: Indicates whether this opcode type वापसs a value
 *                    as the function वापस (0 or 1).
 *
 * The AcpiExOpcode* functions are called via the Dispatcher component with
 * fully resolved opeअक्रमs.
!*/
/* Local prototypes */
अटल u8
acpi_ex_करो_match(u32 match_op,
		 जोड़ acpi_opeअक्रम_object *package_obj,
		 जोड़ acpi_opeअक्रम_object *match_obj);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_करो_match
 *
 * PARAMETERS:  match_op        - The AML match opeअक्रम
 *              package_obj     - Object from the target package
 *              match_obj       - Object to be matched
 *
 * RETURN:      TRUE अगर the match is successful, FALSE otherwise
 *
 * DESCRIPTION: Implements the low-level match क्रम the ASL Match चालक.
 *              Package elements will be implicitly converted to the type of
 *              the match object (Integer/Buffer/String).
 *
 ******************************************************************************/

अटल u8
acpi_ex_करो_match(u32 match_op,
		 जोड़ acpi_opeअक्रम_object *package_obj,
		 जोड़ acpi_opeअक्रम_object *match_obj)
अणु
	u8 logical_result = TRUE;
	acpi_status status;

	/*
	 * Note: Since the package_obj/match_obj ordering is opposite to that of
	 * the standard logical चालकs, we have to reverse them when we call
	 * करो_logical_op in order to make the implicit conversion rules work
	 * correctly. However, this means we have to flip the entire equation
	 * also. A bit ugly perhaps, but overall, better than fussing the
	 * parameters around at runसमय, over and over again.
	 *
	 * Below, P[i] refers to the package element, M refers to the Match object.
	 */
	चयन (match_op) अणु
	हाल MATCH_MTR:

		/* Always true */

		अवरोध;

	हाल MATCH_MEQ:
		/*
		 * True अगर equal: (P[i] == M)
		 * Change to:     (M == P[i])
		 */
		status =
		    acpi_ex_करो_logical_op(AML_LOGICAL_EQUAL_OP, match_obj,
					  package_obj, &logical_result);
		अगर (ACPI_FAILURE(status)) अणु
			वापस (FALSE);
		पूर्ण
		अवरोध;

	हाल MATCH_MLE:
		/*
		 * True अगर less than or equal: (P[i] <= M) (P[i] not_greater than M)
		 * Change to:                  (M >= P[i]) (M not_less than P[i])
		 */
		status =
		    acpi_ex_करो_logical_op(AML_LOGICAL_LESS_OP, match_obj,
					  package_obj, &logical_result);
		अगर (ACPI_FAILURE(status)) अणु
			वापस (FALSE);
		पूर्ण
		logical_result = (u8) ! logical_result;
		अवरोध;

	हाल MATCH_MLT:
		/*
		 * True अगर less than: (P[i] < M)
		 * Change to:         (M > P[i])
		 */
		status =
		    acpi_ex_करो_logical_op(AML_LOGICAL_GREATER_OP, match_obj,
					  package_obj, &logical_result);
		अगर (ACPI_FAILURE(status)) अणु
			वापस (FALSE);
		पूर्ण
		अवरोध;

	हाल MATCH_MGE:
		/*
		 * True अगर greater than or equal: (P[i] >= M) (P[i] not_less than M)
		 * Change to:                     (M <= P[i]) (M not_greater than P[i])
		 */
		status =
		    acpi_ex_करो_logical_op(AML_LOGICAL_GREATER_OP, match_obj,
					  package_obj, &logical_result);
		अगर (ACPI_FAILURE(status)) अणु
			वापस (FALSE);
		पूर्ण
		logical_result = (u8) ! logical_result;
		अवरोध;

	हाल MATCH_MGT:
		/*
		 * True अगर greater than: (P[i] > M)
		 * Change to:            (M < P[i])
		 */
		status =
		    acpi_ex_करो_logical_op(AML_LOGICAL_LESS_OP, match_obj,
					  package_obj, &logical_result);
		अगर (ACPI_FAILURE(status)) अणु
			वापस (FALSE);
		पूर्ण
		अवरोध;

	शेष:

		/* Undefined */

		वापस (FALSE);
	पूर्ण

	वापस (logical_result);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_opcode_6A_0T_1R
 *
 * PARAMETERS:  walk_state          - Current walk state
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Execute opcode with 6 arguments, no target, and a वापस value
 *
 ******************************************************************************/

acpi_status acpi_ex_opcode_6A_0T_1R(काष्ठा acpi_walk_state *walk_state)
अणु
	जोड़ acpi_opeअक्रम_object **opeअक्रम = &walk_state->opeअक्रमs[0];
	जोड़ acpi_opeअक्रम_object *वापस_desc = शून्य;
	acpi_status status = AE_OK;
	u64 index;
	जोड़ acpi_opeअक्रम_object *this_element;

	ACPI_FUNCTION_TRACE_STR(ex_opcode_6A_0T_1R,
				acpi_ps_get_opcode_name(walk_state->opcode));

	चयन (walk_state->opcode) अणु
	हाल AML_MATCH_OP:
		/*
		 * Match (search_pkg[0], match_op1[1], match_obj1[2],
		 *                      match_op2[3], match_obj2[4], start_index[5])
		 */

		/* Validate both Match Term Operators (MTR, MEQ, etc.) */

		अगर ((opeअक्रम[1]->पूर्णांकeger.value > MAX_MATCH_OPERATOR) ||
		    (opeअक्रम[3]->पूर्णांकeger.value > MAX_MATCH_OPERATOR)) अणु
			ACPI_ERROR((AE_INFO, "Match operator out of range"));
			status = AE_AML_OPERAND_VALUE;
			जाओ cleanup;
		पूर्ण

		/* Get the package start_index, validate against the package length */

		index = opeअक्रम[5]->पूर्णांकeger.value;
		अगर (index >= opeअक्रम[0]->package.count) अणु
			ACPI_ERROR((AE_INFO,
				    "Index (0x%8.8X%8.8X) beyond package end (0x%X)",
				    ACPI_FORMAT_UINT64(index),
				    opeअक्रम[0]->package.count));
			status = AE_AML_PACKAGE_LIMIT;
			जाओ cleanup;
		पूर्ण

		/* Create an पूर्णांकeger क्रम the वापस value */
		/* Default वापस value is ACPI_UINT64_MAX अगर no match found */

		वापस_desc = acpi_ut_create_पूर्णांकeger_object(ACPI_UINT64_MAX);
		अगर (!वापस_desc) अणु
			status = AE_NO_MEMORY;
			जाओ cleanup;

		पूर्ण

		/*
		 * Examine each element until a match is found. Both match conditions
		 * must be satisfied क्रम a match to occur. Within the loop,
		 * "continue" signअगरies that the current element करोes not match
		 * and the next should be examined.
		 *
		 * Upon finding a match, the loop will terminate via "break" at
		 * the bottom. If it terminates "normally", match_value will be
		 * ACPI_UINT64_MAX (Ones) (its initial value) indicating that no
		 * match was found.
		 */
		क्रम (; index < opeअक्रम[0]->package.count; index++) अणु

			/* Get the current package element */

			this_element = opeअक्रम[0]->package.elements[index];

			/* Treat any uninitialized (शून्य) elements as non-matching */

			अगर (!this_element) अणु
				जारी;
			पूर्ण

			/*
			 * Both match conditions must be satisfied. Execution of a जारी
			 * (proceed to next iteration of enclosing क्रम loop) signअगरies a
			 * non-match.
			 */
			अगर (!acpi_ex_करो_match((u32) opeअक्रम[1]->पूर्णांकeger.value,
					      this_element, opeअक्रम[2])) अणु
				जारी;
			पूर्ण

			अगर (!acpi_ex_करो_match((u32) opeअक्रम[3]->पूर्णांकeger.value,
					      this_element, opeअक्रम[4])) अणु
				जारी;
			पूर्ण

			/* Match found: Index is the वापस value */

			वापस_desc->पूर्णांकeger.value = index;
			अवरोध;
		पूर्ण
		अवरोध;

	हाल AML_LOAD_TABLE_OP:

		status = acpi_ex_load_table_op(walk_state, &वापस_desc);
		अवरोध;

	शेष:

		ACPI_ERROR((AE_INFO, "Unknown AML opcode 0x%X",
			    walk_state->opcode));

		status = AE_AML_BAD_OPCODE;
		जाओ cleanup;
	पूर्ण

cleanup:

	/* Delete वापस object on error */

	अगर (ACPI_FAILURE(status)) अणु
		acpi_ut_हटाओ_reference(वापस_desc);
	पूर्ण

	/* Save वापस object on success */

	अन्यथा अणु
		walk_state->result_obj = वापस_desc;
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण
