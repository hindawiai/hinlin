<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: exoparg1 - AML execution - opcodes with 1 argument
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acparser.h"
#समावेश "acdispat.h"
#समावेश "acinterp.h"
#समावेश "amlcode.h"
#समावेश "acnamesp.h"

#घोषणा _COMPONENT          ACPI_EXECUTER
ACPI_MODULE_NAME("exoparg1")

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
 *                    required क्रम this opcode type (0 through 6 args).
 * yT - TARGETS:      The number of tarमाला_लो (output opeअक्रमs) that are required
 *                    क्रम this opcode type (0, 1, or 2 tarमाला_लो).
 * zR - RETURN VALUE: Indicates whether this opcode type वापसs a value
 *                    as the function वापस (0 or 1).
 *
 * The AcpiExOpcode* functions are called via the Dispatcher component with
 * fully resolved opeअक्रमs.
!*/
/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_opcode_0A_0T_1R
 *
 * PARAMETERS:  walk_state          - Current state (contains AML opcode)
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Execute चालक with no opeअक्रमs, one वापस value
 *
 ******************************************************************************/
acpi_status acpi_ex_opcode_0A_0T_1R(काष्ठा acpi_walk_state *walk_state)
अणु
	acpi_status status = AE_OK;
	जोड़ acpi_opeअक्रम_object *वापस_desc = शून्य;

	ACPI_FUNCTION_TRACE_STR(ex_opcode_0A_0T_1R,
				acpi_ps_get_opcode_name(walk_state->opcode));

	/* Examine the AML opcode */

	चयन (walk_state->opcode) अणु
	हाल AML_TIMER_OP:	/*  Timer () */

		/* Create a वापस object of type Integer */

		वापस_desc =
		    acpi_ut_create_पूर्णांकeger_object(acpi_os_get_समयr());
		अगर (!वापस_desc) अणु
			status = AE_NO_MEMORY;
			जाओ cleanup;
		पूर्ण
		अवरोध;

	शेष:		/*  Unknown opcode  */

		ACPI_ERROR((AE_INFO, "Unknown AML opcode 0x%X",
			    walk_state->opcode));
		status = AE_AML_BAD_OPCODE;
		अवरोध;
	पूर्ण

cleanup:

	/* Delete वापस object on error */

	अगर ((ACPI_FAILURE(status)) || walk_state->result_obj) अणु
		acpi_ut_हटाओ_reference(वापस_desc);
		walk_state->result_obj = शून्य;
	पूर्ण अन्यथा अणु
		/* Save the वापस value */

		walk_state->result_obj = वापस_desc;
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_opcode_1A_0T_0R
 *
 * PARAMETERS:  walk_state          - Current state (contains AML opcode)
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Execute Type 1 monadic चालक with numeric opeअक्रम on
 *              object stack
 *
 ******************************************************************************/

acpi_status acpi_ex_opcode_1A_0T_0R(काष्ठा acpi_walk_state *walk_state)
अणु
	जोड़ acpi_opeअक्रम_object **opeअक्रम = &walk_state->opeअक्रमs[0];
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TRACE_STR(ex_opcode_1A_0T_0R,
				acpi_ps_get_opcode_name(walk_state->opcode));

	/* Examine the AML opcode */

	चयन (walk_state->opcode) अणु
	हाल AML_RELEASE_OP:	/*  Release (mutex_object) */

		status = acpi_ex_release_mutex(opeअक्रम[0], walk_state);
		अवरोध;

	हाल AML_RESET_OP:	/*  Reset (event_object) */

		status = acpi_ex_प्रणाली_reset_event(opeअक्रम[0]);
		अवरोध;

	हाल AML_SIGNAL_OP:	/*  Signal (event_object) */

		status = acpi_ex_प्रणाली_संकेत_event(opeअक्रम[0]);
		अवरोध;

	हाल AML_SLEEP_OP:	/*  Sleep (msec_समय) */

		status = acpi_ex_प्रणाली_करो_sleep(opeअक्रम[0]->पूर्णांकeger.value);
		अवरोध;

	हाल AML_STALL_OP:	/*  Stall (usec_समय) */

		status =
		    acpi_ex_प्रणाली_करो_stall((u32) opeअक्रम[0]->पूर्णांकeger.value);
		अवरोध;

	हाल AML_UNLOAD_OP:	/*  Unload (Handle) */

		status = acpi_ex_unload_table(opeअक्रम[0]);
		अवरोध;

	शेष:		/*  Unknown opcode  */

		ACPI_ERROR((AE_INFO, "Unknown AML opcode 0x%X",
			    walk_state->opcode));
		status = AE_AML_BAD_OPCODE;
		अवरोध;
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_opcode_1A_1T_0R
 *
 * PARAMETERS:  walk_state          - Current state (contains AML opcode)
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Execute opcode with one argument, one target, and no
 *              वापस value.
 *
 ******************************************************************************/

acpi_status acpi_ex_opcode_1A_1T_0R(काष्ठा acpi_walk_state *walk_state)
अणु
	acpi_status status = AE_OK;
	जोड़ acpi_opeअक्रम_object **opeअक्रम = &walk_state->opeअक्रमs[0];

	ACPI_FUNCTION_TRACE_STR(ex_opcode_1A_1T_0R,
				acpi_ps_get_opcode_name(walk_state->opcode));

	/* Examine the AML opcode */

	चयन (walk_state->opcode) अणु
	हाल AML_LOAD_OP:

		status = acpi_ex_load_op(opeअक्रम[0], opeअक्रम[1], walk_state);
		अवरोध;

	शेष:		/* Unknown opcode */

		ACPI_ERROR((AE_INFO, "Unknown AML opcode 0x%X",
			    walk_state->opcode));
		status = AE_AML_BAD_OPCODE;
		जाओ cleanup;
	पूर्ण

cleanup:

	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_opcode_1A_1T_1R
 *
 * PARAMETERS:  walk_state          - Current state (contains AML opcode)
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Execute opcode with one argument, one target, and a
 *              वापस value.
 *
 ******************************************************************************/

acpi_status acpi_ex_opcode_1A_1T_1R(काष्ठा acpi_walk_state *walk_state)
अणु
	acpi_status status = AE_OK;
	जोड़ acpi_opeअक्रम_object **opeअक्रम = &walk_state->opeअक्रमs[0];
	जोड़ acpi_opeअक्रम_object *वापस_desc = शून्य;
	जोड़ acpi_opeअक्रम_object *वापस_desc2 = शून्य;
	u32 temp32;
	u32 i;
	u64 घातer_of_ten;
	u64 digit;

	ACPI_FUNCTION_TRACE_STR(ex_opcode_1A_1T_1R,
				acpi_ps_get_opcode_name(walk_state->opcode));

	/* Examine the AML opcode */

	चयन (walk_state->opcode) अणु
	हाल AML_BIT_NOT_OP:
	हाल AML_FIND_SET_LEFT_BIT_OP:
	हाल AML_FIND_SET_RIGHT_BIT_OP:
	हाल AML_FROM_BCD_OP:
	हाल AML_TO_BCD_OP:
	हाल AML_CONDITIONAL_REF_OF_OP:

		/* Create a वापस object of type Integer क्रम these opcodes */

		वापस_desc = acpi_ut_create_पूर्णांकernal_object(ACPI_TYPE_INTEGER);
		अगर (!वापस_desc) अणु
			status = AE_NO_MEMORY;
			जाओ cleanup;
		पूर्ण

		चयन (walk_state->opcode) अणु
		हाल AML_BIT_NOT_OP:	/* Not (Opeअक्रम, Result)  */

			वापस_desc->पूर्णांकeger.value = ~opeअक्रम[0]->पूर्णांकeger.value;
			अवरोध;

		हाल AML_FIND_SET_LEFT_BIT_OP:	/* find_set_left_bit (Opeअक्रम, Result) */

			वापस_desc->पूर्णांकeger.value = opeअक्रम[0]->पूर्णांकeger.value;

			/*
			 * Acpi specअगरication describes Integer type as a little
			 * endian अचिन्हित value, so this boundary condition is valid.
			 */
			क्रम (temp32 = 0; वापस_desc->पूर्णांकeger.value &&
			     temp32 < ACPI_INTEGER_BIT_SIZE; ++temp32) अणु
				वापस_desc->पूर्णांकeger.value >>= 1;
			पूर्ण

			वापस_desc->पूर्णांकeger.value = temp32;
			अवरोध;

		हाल AML_FIND_SET_RIGHT_BIT_OP:	/* find_set_right_bit (Opeअक्रम, Result) */

			वापस_desc->पूर्णांकeger.value = opeअक्रम[0]->पूर्णांकeger.value;

			/*
			 * The Acpi specअगरication describes Integer type as a little
			 * endian अचिन्हित value, so this boundary condition is valid.
			 */
			क्रम (temp32 = 0; वापस_desc->पूर्णांकeger.value &&
			     temp32 < ACPI_INTEGER_BIT_SIZE; ++temp32) अणु
				वापस_desc->पूर्णांकeger.value <<= 1;
			पूर्ण

			/* Since the bit position is one-based, subtract from 33 (65) */

			वापस_desc->पूर्णांकeger.value =
			    temp32 ==
			    0 ? 0 : (ACPI_INTEGER_BIT_SIZE + 1) - temp32;
			अवरोध;

		हाल AML_FROM_BCD_OP:	/* from_bcd (BCDValue, Result) */
			/*
			 * The 64-bit ACPI पूर्णांकeger can hold 16 4-bit BCD अक्षरacters
			 * (अगर table is 32-bit, पूर्णांकeger can hold 8 BCD अक्षरacters)
			 * Convert each 4-bit BCD value
			 */
			घातer_of_ten = 1;
			वापस_desc->पूर्णांकeger.value = 0;
			digit = opeअक्रम[0]->पूर्णांकeger.value;

			/* Convert each BCD digit (each is one nybble wide) */

			क्रम (i = 0;
			     (i < acpi_gbl_पूर्णांकeger_nybble_width) && (digit > 0);
			     i++) अणु

				/* Get the least signअगरicant 4-bit BCD digit */

				temp32 = ((u32) digit) & 0xF;

				/* Check the range of the digit */

				अगर (temp32 > 9) अणु
					ACPI_ERROR((AE_INFO,
						    "BCD digit too large (not decimal): 0x%X",
						    temp32));

					status = AE_AML_NUMERIC_OVERFLOW;
					जाओ cleanup;
				पूर्ण

				/* Sum the digit पूर्णांकo the result with the current घातer of 10 */

				वापस_desc->पूर्णांकeger.value +=
				    (((u64) temp32) * घातer_of_ten);

				/* Shअगरt to next BCD digit */

				digit >>= 4;

				/* Next घातer of 10 */

				घातer_of_ten *= 10;
			पूर्ण
			अवरोध;

		हाल AML_TO_BCD_OP:	/* to_bcd (Opeअक्रम, Result) */

			वापस_desc->पूर्णांकeger.value = 0;
			digit = opeअक्रम[0]->पूर्णांकeger.value;

			/* Each BCD digit is one nybble wide */

			क्रम (i = 0;
			     (i < acpi_gbl_पूर्णांकeger_nybble_width) && (digit > 0);
			     i++) अणु
				(व्योम)acpi_ut_लघु_भागide(digit, 10, &digit,
							   &temp32);

				/*
				 * Insert the BCD digit that resides in the
				 * reमुख्यder from above
				 */
				वापस_desc->पूर्णांकeger.value |=
				    (((u64) temp32) << ACPI_MUL_4(i));
			पूर्ण

			/* Overflow अगर there is any data left in Digit */

			अगर (digit > 0) अणु
				ACPI_ERROR((AE_INFO,
					    "Integer too large to convert to BCD: 0x%8.8X%8.8X",
					    ACPI_FORMAT_UINT64(opeअक्रम[0]->
							       पूर्णांकeger.value)));
				status = AE_AML_NUMERIC_OVERFLOW;
				जाओ cleanup;
			पूर्ण
			अवरोध;

		हाल AML_CONDITIONAL_REF_OF_OP:	/* cond_ref_of (source_object, Result) */
			/*
			 * This op is a little strange because the पूर्णांकernal वापस value is
			 * dअगरferent than the वापस value stored in the result descriptor
			 * (There are really two वापस values)
			 */
			अगर ((काष्ठा acpi_namespace_node *)opeअक्रम[0] ==
			    acpi_gbl_root_node) अणु
				/*
				 * This means that the object करोes not exist in the namespace,
				 * वापस FALSE
				 */
				वापस_desc->पूर्णांकeger.value = 0;
				जाओ cleanup;
			पूर्ण

			/* Get the object reference, store it, and हटाओ our reference */

			status = acpi_ex_get_object_reference(opeअक्रम[0],
							      &वापस_desc2,
							      walk_state);
			अगर (ACPI_FAILURE(status)) अणु
				जाओ cleanup;
			पूर्ण

			status =
			    acpi_ex_store(वापस_desc2, opeअक्रम[1], walk_state);
			acpi_ut_हटाओ_reference(वापस_desc2);

			/* The object exists in the namespace, वापस TRUE */

			वापस_desc->पूर्णांकeger.value = ACPI_UINT64_MAX;
			जाओ cleanup;

		शेष:

			/* No other opcodes get here */

			अवरोध;
		पूर्ण
		अवरोध;

	हाल AML_STORE_OP:	/* Store (Source, Target) */
		/*
		 * A store opeअक्रम is typically a number, string, buffer or lvalue
		 * Be careful about deleting the source object,
		 * since the object itself may have been stored.
		 */
		status = acpi_ex_store(opeअक्रम[0], opeअक्रम[1], walk_state);
		अगर (ACPI_FAILURE(status)) अणु
			वापस_ACPI_STATUS(status);
		पूर्ण

		/* It is possible that the Store alपढ़ोy produced a वापस object */

		अगर (!walk_state->result_obj) अणु
			/*
			 * Normally, we would हटाओ a reference on the Opeअक्रम[0]
			 * parameter; But since it is being used as the पूर्णांकernal वापस
			 * object (meaning we would normally increment it), the two
			 * cancel out, and we simply करोn't करो anything.
			 */
			walk_state->result_obj = opeअक्रम[0];
			walk_state->opeअक्रमs[0] = शून्य;	/* Prevent deletion */
		पूर्ण
		वापस_ACPI_STATUS(status);

		/*
		 * ACPI 2.0 Opcodes
		 */
	हाल AML_COPY_OBJECT_OP:	/* copy_object (Source, Target) */

		status =
		    acpi_ut_copy_iobject_to_iobject(opeअक्रम[0], &वापस_desc,
						    walk_state);
		अवरोध;

	हाल AML_TO_DECIMAL_STRING_OP:	/* to_decimal_string (Data, Result) */

		status =
		    acpi_ex_convert_to_string(opeअक्रम[0], &वापस_desc,
					      ACPI_EXPLICIT_CONVERT_DECIMAL);
		अगर (वापस_desc == opeअक्रम[0]) अणु

			/* No conversion perक्रमmed, add ref to handle वापस value */

			acpi_ut_add_reference(वापस_desc);
		पूर्ण
		अवरोध;

	हाल AML_TO_HEX_STRING_OP:	/* to_hex_string (Data, Result) */

		status =
		    acpi_ex_convert_to_string(opeअक्रम[0], &वापस_desc,
					      ACPI_EXPLICIT_CONVERT_HEX);
		अगर (वापस_desc == opeअक्रम[0]) अणु

			/* No conversion perक्रमmed, add ref to handle वापस value */

			acpi_ut_add_reference(वापस_desc);
		पूर्ण
		अवरोध;

	हाल AML_TO_BUFFER_OP:	/* to_buffer (Data, Result) */

		status = acpi_ex_convert_to_buffer(opeअक्रम[0], &वापस_desc);
		अगर (वापस_desc == opeअक्रम[0]) अणु

			/* No conversion perक्रमmed, add ref to handle वापस value */

			acpi_ut_add_reference(वापस_desc);
		पूर्ण
		अवरोध;

	हाल AML_TO_INTEGER_OP:	/* to_पूर्णांकeger (Data, Result) */

		/* Perक्रमm "explicit" conversion */

		status =
		    acpi_ex_convert_to_पूर्णांकeger(opeअक्रम[0], &वापस_desc, 0);
		अगर (वापस_desc == opeअक्रम[0]) अणु

			/* No conversion perक्रमmed, add ref to handle वापस value */

			acpi_ut_add_reference(वापस_desc);
		पूर्ण
		अवरोध;

	हाल AML_SHIFT_LEFT_BIT_OP:	/* shअगरt_left_bit (Source, bit_num) */
	हाल AML_SHIFT_RIGHT_BIT_OP:	/* shअगरt_right_bit (Source, bit_num) */

		/* These are two obsolete opcodes */

		ACPI_ERROR((AE_INFO,
			    "%s is obsolete and not implemented",
			    acpi_ps_get_opcode_name(walk_state->opcode)));
		status = AE_SUPPORT;
		जाओ cleanup;

	शेष:		/* Unknown opcode */

		ACPI_ERROR((AE_INFO, "Unknown AML opcode 0x%X",
			    walk_state->opcode));
		status = AE_AML_BAD_OPCODE;
		जाओ cleanup;
	पूर्ण

	अगर (ACPI_SUCCESS(status)) अणु

		/* Store the वापस value computed above पूर्णांकo the target object */

		status = acpi_ex_store(वापस_desc, opeअक्रम[1], walk_state);
	पूर्ण

cleanup:

	/* Delete वापस object on error */

	अगर (ACPI_FAILURE(status)) अणु
		acpi_ut_हटाओ_reference(वापस_desc);
	पूर्ण

	/* Save वापस object on success */

	अन्यथा अगर (!walk_state->result_obj) अणु
		walk_state->result_obj = वापस_desc;
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_opcode_1A_0T_1R
 *
 * PARAMETERS:  walk_state          - Current state (contains AML opcode)
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Execute opcode with one argument, no target, and a वापस value
 *
 ******************************************************************************/

acpi_status acpi_ex_opcode_1A_0T_1R(काष्ठा acpi_walk_state *walk_state)
अणु
	जोड़ acpi_opeअक्रम_object **opeअक्रम = &walk_state->opeअक्रमs[0];
	जोड़ acpi_opeअक्रम_object *temp_desc;
	जोड़ acpi_opeअक्रम_object *वापस_desc = शून्य;
	acpi_status status = AE_OK;
	u32 type;
	u64 value;

	ACPI_FUNCTION_TRACE_STR(ex_opcode_1A_0T_1R,
				acpi_ps_get_opcode_name(walk_state->opcode));

	/* Examine the AML opcode */

	चयन (walk_state->opcode) अणु
	हाल AML_LOGICAL_NOT_OP:	/* LNot (Opeअक्रम) */

		वापस_desc = acpi_ut_create_पूर्णांकeger_object((u64) 0);
		अगर (!वापस_desc) अणु
			status = AE_NO_MEMORY;
			जाओ cleanup;
		पूर्ण

		/*
		 * Set result to ONES (TRUE) अगर Value == 0. Note:
		 * वापस_desc->Integer.Value is initially == 0 (FALSE) from above.
		 */
		अगर (!opeअक्रम[0]->पूर्णांकeger.value) अणु
			वापस_desc->पूर्णांकeger.value = ACPI_UINT64_MAX;
		पूर्ण
		अवरोध;

	हाल AML_DECREMENT_OP:	/* Decrement (Opeअक्रम)  */
	हाल AML_INCREMENT_OP:	/* Increment (Opeअक्रम)  */
		/*
		 * Create a new पूर्णांकeger. Can't just get the base पूर्णांकeger and
		 * increment it because it may be an Arg or Field.
		 */
		वापस_desc = acpi_ut_create_पूर्णांकernal_object(ACPI_TYPE_INTEGER);
		अगर (!वापस_desc) अणु
			status = AE_NO_MEMORY;
			जाओ cleanup;
		पूर्ण

		/*
		 * Since we are expecting a Reference opeअक्रम, it can be either a
		 * NS Node or an पूर्णांकernal object.
		 */
		temp_desc = opeअक्रम[0];
		अगर (ACPI_GET_DESCRIPTOR_TYPE(temp_desc) ==
		    ACPI_DESC_TYPE_OPERAND) अणु

			/* Internal reference object - prevent deletion */

			acpi_ut_add_reference(temp_desc);
		पूर्ण

		/*
		 * Convert the Reference opeअक्रम to an Integer (This हटाओs a
		 * reference on the Opeअक्रम[0] object)
		 *
		 * NOTE:  We use LNOT_OP here in order to क्रमce resolution of the
		 * reference opeअक्रम to an actual पूर्णांकeger.
		 */
		status = acpi_ex_resolve_opeअक्रमs(AML_LOGICAL_NOT_OP,
						  &temp_desc, walk_state);
		अगर (ACPI_FAILURE(status)) अणु
			ACPI_EXCEPTION((AE_INFO, status,
					"While resolving operands for [%s]",
					acpi_ps_get_opcode_name(walk_state->
								opcode)));

			जाओ cleanup;
		पूर्ण

		/*
		 * temp_desc is now guaranteed to be an Integer object --
		 * Perक्रमm the actual increment or decrement
		 */
		अगर (walk_state->opcode == AML_INCREMENT_OP) अणु
			वापस_desc->पूर्णांकeger.value =
			    temp_desc->पूर्णांकeger.value + 1;
		पूर्ण अन्यथा अणु
			वापस_desc->पूर्णांकeger.value =
			    temp_desc->पूर्णांकeger.value - 1;
		पूर्ण

		/* Finished with this Integer object */

		acpi_ut_हटाओ_reference(temp_desc);

		/*
		 * Store the result back (indirectly) through the original
		 * Reference object
		 */
		status = acpi_ex_store(वापस_desc, opeअक्रम[0], walk_state);
		अवरोध;

	हाल AML_OBJECT_TYPE_OP:	/* object_type (source_object) */
		/*
		 * Note: The opeअक्रम is not resolved at this poपूर्णांक because we want to
		 * get the associated object, not its value. For example, we करोn't
		 * want to resolve a field_unit to its value, we want the actual
		 * field_unit object.
		 */

		/* Get the type of the base object */

		status =
		    acpi_ex_resolve_multiple(walk_state, opeअक्रम[0], &type,
					     शून्य);
		अगर (ACPI_FAILURE(status)) अणु
			जाओ cleanup;
		पूर्ण

		/* Allocate a descriptor to hold the type. */

		वापस_desc = acpi_ut_create_पूर्णांकeger_object((u64) type);
		अगर (!वापस_desc) अणु
			status = AE_NO_MEMORY;
			जाओ cleanup;
		पूर्ण
		अवरोध;

	हाल AML_SIZE_OF_OP:	/* size_of (source_object) */
		/*
		 * Note: The opeअक्रम is not resolved at this poपूर्णांक because we want to
		 * get the associated object, not its value.
		 */

		/* Get the base object */

		status =
		    acpi_ex_resolve_multiple(walk_state, opeअक्रम[0], &type,
					     &temp_desc);
		अगर (ACPI_FAILURE(status)) अणु
			जाओ cleanup;
		पूर्ण

		/*
		 * The type of the base object must be पूर्णांकeger, buffer, string, or
		 * package. All others are not supported.
		 *
		 * NOTE: Integer is not specअगरically supported by the ACPI spec,
		 * but is supported implicitly via implicit opeअक्रम conversion.
		 * rather than bother with conversion, we just use the byte width
		 * global (4 or 8 bytes).
		 */
		चयन (type) अणु
		हाल ACPI_TYPE_INTEGER:

			value = acpi_gbl_पूर्णांकeger_byte_width;
			अवरोध;

		हाल ACPI_TYPE_STRING:

			value = temp_desc->string.length;
			अवरोध;

		हाल ACPI_TYPE_BUFFER:

			/* Buffer arguments may not be evaluated at this poपूर्णांक */

			status = acpi_ds_get_buffer_arguments(temp_desc);
			value = temp_desc->buffer.length;
			अवरोध;

		हाल ACPI_TYPE_PACKAGE:

			/* Package arguments may not be evaluated at this poपूर्णांक */

			status = acpi_ds_get_package_arguments(temp_desc);
			value = temp_desc->package.count;
			अवरोध;

		शेष:

			ACPI_ERROR((AE_INFO,
				    "Operand must be Buffer/Integer/String/Package"
				    " - found type %s",
				    acpi_ut_get_type_name(type)));

			status = AE_AML_OPERAND_TYPE;
			जाओ cleanup;
		पूर्ण

		अगर (ACPI_FAILURE(status)) अणु
			जाओ cleanup;
		पूर्ण

		/*
		 * Now that we have the size of the object, create a result
		 * object to hold the value
		 */
		वापस_desc = acpi_ut_create_पूर्णांकeger_object(value);
		अगर (!वापस_desc) अणु
			status = AE_NO_MEMORY;
			जाओ cleanup;
		पूर्ण
		अवरोध;

	हाल AML_REF_OF_OP:	/* ref_of (source_object) */

		status =
		    acpi_ex_get_object_reference(opeअक्रम[0], &वापस_desc,
						 walk_state);
		अगर (ACPI_FAILURE(status)) अणु
			जाओ cleanup;
		पूर्ण
		अवरोध;

	हाल AML_DEREF_OF_OP:	/* deref_of (obj_reference | String) */

		/* Check क्रम a method local or argument, or standalone String */

		अगर (ACPI_GET_DESCRIPTOR_TYPE(opeअक्रम[0]) ==
		    ACPI_DESC_TYPE_NAMED) अणु
			temp_desc =
			    acpi_ns_get_attached_object((काष्ठा
							 acpi_namespace_node *)
							opeअक्रम[0]);
			अगर (temp_desc
			    && ((temp_desc->common.type == ACPI_TYPE_STRING)
				|| (temp_desc->common.type ==
				    ACPI_TYPE_LOCAL_REFERENCE))) अणु
				opeअक्रम[0] = temp_desc;
				acpi_ut_add_reference(temp_desc);
			पूर्ण अन्यथा अणु
				status = AE_AML_OPERAND_TYPE;
				जाओ cleanup;
			पूर्ण
		पूर्ण अन्यथा अणु
			चयन ((opeअक्रम[0])->common.type) अणु
			हाल ACPI_TYPE_LOCAL_REFERENCE:
				/*
				 * This is a deref_of (local_x | arg_x)
				 *
				 * Must resolve/dereference the local/arg reference first
				 */
				चयन (opeअक्रम[0]->reference.class) अणु
				हाल ACPI_REFCLASS_LOCAL:
				हाल ACPI_REFCLASS_ARG:

					/* Set Opeअक्रम[0] to the value of the local/arg */

					status =
					    acpi_ds_method_data_get_value
					    (opeअक्रम[0]->reference.class,
					     opeअक्रम[0]->reference.value,
					     walk_state, &temp_desc);
					अगर (ACPI_FAILURE(status)) अणु
						जाओ cleanup;
					पूर्ण

					/*
					 * Delete our reference to the input object and
					 * poपूर्णांक to the object just retrieved
					 */
					acpi_ut_हटाओ_reference(opeअक्रम[0]);
					opeअक्रम[0] = temp_desc;
					अवरोध;

				हाल ACPI_REFCLASS_REFOF:

					/* Get the object to which the reference refers */

					temp_desc =
					    opeअक्रम[0]->reference.object;
					acpi_ut_हटाओ_reference(opeअक्रम[0]);
					opeअक्रम[0] = temp_desc;
					अवरोध;

				शेष:

					/* Must be an Index op - handled below */
					अवरोध;
				पूर्ण
				अवरोध;

			हाल ACPI_TYPE_STRING:

				अवरोध;

			शेष:

				status = AE_AML_OPERAND_TYPE;
				जाओ cleanup;
			पूर्ण
		पूर्ण

		अगर (ACPI_GET_DESCRIPTOR_TYPE(opeअक्रम[0]) !=
		    ACPI_DESC_TYPE_NAMED) अणु
			अगर ((opeअक्रम[0])->common.type == ACPI_TYPE_STRING) अणु
				/*
				 * This is a deref_of (String). The string is a reference
				 * to a named ACPI object.
				 *
				 * 1) Find the owning Node
				 * 2) Dereference the node to an actual object. Could be a
				 *    Field, so we need to resolve the node to a value.
				 */
				status =
				    acpi_ns_get_node_unlocked(walk_state->
							      scope_info->scope.
							      node,
							      opeअक्रम[0]->
							      string.poपूर्णांकer,
							      ACPI_NS_SEARCH_PARENT,
							      ACPI_CAST_INसूचीECT_PTR
							      (काष्ठा
							       acpi_namespace_node,
							       &वापस_desc));
				अगर (ACPI_FAILURE(status)) अणु
					जाओ cleanup;
				पूर्ण

				status =
				    acpi_ex_resolve_node_to_value
				    (ACPI_CAST_INसूचीECT_PTR
				     (काष्ठा acpi_namespace_node, &वापस_desc),
				     walk_state);
				जाओ cleanup;
			पूर्ण
		पूर्ण

		/* Opeअक्रम[0] may have changed from the code above */

		अगर (ACPI_GET_DESCRIPTOR_TYPE(opeअक्रम[0]) ==
		    ACPI_DESC_TYPE_NAMED) अणु
			/*
			 * This is a deref_of (object_reference)
			 * Get the actual object from the Node (This is the dereference).
			 * This हाल may only happen when a local_x or arg_x is
			 * dereferenced above, or क्रम references to device and
			 * thermal objects.
			 */
			चयन (((काष्ठा acpi_namespace_node *)opeअक्रम[0])->
				type) अणु
			हाल ACPI_TYPE_DEVICE:
			हाल ACPI_TYPE_THERMAL:

				/* These types have no node subobject, वापस the NS node */

				वापस_desc = opeअक्रम[0];
				अवरोध;

			शेष:
				/* For most types, get the object attached to the node */

				वापस_desc = acpi_ns_get_attached_object((काष्ठा acpi_namespace_node *)opeअक्रम[0]);
				acpi_ut_add_reference(वापस_desc);
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * This must be a reference object produced by either the
			 * Index() or ref_of() चालक
			 */
			चयन (opeअक्रम[0]->reference.class) अणु
			हाल ACPI_REFCLASS_INDEX:
				/*
				 * The target type क्रम the Index चालक must be
				 * either a Buffer or a Package
				 */
				चयन (opeअक्रम[0]->reference.target_type) अणु
				हाल ACPI_TYPE_BUFFER_FIELD:

					temp_desc =
					    opeअक्रम[0]->reference.object;

					/*
					 * Create a new object that contains one element of the
					 * buffer -- the element poपूर्णांकed to by the index.
					 *
					 * NOTE: index पूर्णांकo a buffer is NOT a poपूर्णांकer to a
					 * sub-buffer of the मुख्य buffer, it is only a poपूर्णांकer to a
					 * single element (byte) of the buffer!
					 *
					 * Since we are वापसing the value of the buffer at the
					 * indexed location, we करोn't need to add an additional
					 * reference to the buffer itself.
					 */
					वापस_desc =
					    acpi_ut_create_पूर्णांकeger_object((u64)
									  temp_desc->buffer.poपूर्णांकer[opeअक्रम[0]->reference.value]);
					अगर (!वापस_desc) अणु
						status = AE_NO_MEMORY;
						जाओ cleanup;
					पूर्ण
					अवरोध;

				हाल ACPI_TYPE_PACKAGE:
					/*
					 * Return the referenced element of the package. We must
					 * add another reference to the referenced object, however.
					 */
					वापस_desc =
					    *(opeअक्रम[0]->reference.where);
					अगर (!वापस_desc) अणु
						/*
						 * Element is शून्य, करो not allow the dereference.
						 * This provides compatibility with other ACPI
						 * implementations.
						 */
						वापस_ACPI_STATUS
						    (AE_AML_UNINITIALIZED_ELEMENT);
					पूर्ण

					acpi_ut_add_reference(वापस_desc);
					अवरोध;

				शेष:

					ACPI_ERROR((AE_INFO,
						    "Unknown Index TargetType 0x%X in reference object %p",
						    opeअक्रम[0]->reference.
						    target_type, opeअक्रम[0]));

					status = AE_AML_OPERAND_TYPE;
					जाओ cleanup;
				पूर्ण
				अवरोध;

			हाल ACPI_REFCLASS_REFOF:

				वापस_desc = opeअक्रम[0]->reference.object;

				अगर (ACPI_GET_DESCRIPTOR_TYPE(वापस_desc) ==
				    ACPI_DESC_TYPE_NAMED) अणु
					वापस_desc =
					    acpi_ns_get_attached_object((काष्ठा
									 acpi_namespace_node
									 *)
									वापस_desc);
					अगर (!वापस_desc) अणु
						अवरोध;
					पूर्ण

					/*
					 * June 2013:
					 * buffer_fields/field_units require additional resolution
					 */
					चयन (वापस_desc->common.type) अणु
					हाल ACPI_TYPE_BUFFER_FIELD:
					हाल ACPI_TYPE_LOCAL_REGION_FIELD:
					हाल ACPI_TYPE_LOCAL_BANK_FIELD:
					हाल ACPI_TYPE_LOCAL_INDEX_FIELD:

						status =
						    acpi_ex_पढ़ो_data_from_field
						    (walk_state, वापस_desc,
						     &temp_desc);
						अगर (ACPI_FAILURE(status)) अणु
							जाओ cleanup;
						पूर्ण

						वापस_desc = temp_desc;
						अवरोध;

					शेष:

						/* Add another reference to the object */

						acpi_ut_add_reference
						    (वापस_desc);
						अवरोध;
					पूर्ण
				पूर्ण
				अवरोध;

			शेष:

				ACPI_ERROR((AE_INFO,
					    "Unknown class in reference(%p) - 0x%2.2X",
					    opeअक्रम[0],
					    opeअक्रम[0]->reference.class));

				status = AE_TYPE;
				जाओ cleanup;
			पूर्ण
		पूर्ण
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
