<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: exoparg2 - AML execution - opcodes with 2 arguments
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acparser.h"
#समावेश "acinterp.h"
#समावेश "acevents.h"
#समावेश "amlcode.h"

#घोषणा _COMPONENT          ACPI_EXECUTER
ACPI_MODULE_NAME("exoparg2")

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
/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_opcode_2A_0T_0R
 *
 * PARAMETERS:  walk_state          - Current walk state
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Execute opcode with two arguments, no target, and no वापस
 *              value.
 *
 * ALLOCATION:  Deletes both opeअक्रमs
 *
 ******************************************************************************/
acpi_status acpi_ex_opcode_2A_0T_0R(काष्ठा acpi_walk_state *walk_state)
अणु
	जोड़ acpi_opeअक्रम_object **opeअक्रम = &walk_state->opeअक्रमs[0];
	काष्ठा acpi_namespace_node *node;
	u32 value;
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TRACE_STR(ex_opcode_2A_0T_0R,
				acpi_ps_get_opcode_name(walk_state->opcode));

	/* Examine the opcode */

	चयन (walk_state->opcode) अणु
	हाल AML_NOTIFY_OP:	/* Notअगरy (notअगरy_object, notअगरy_value) */

		/* The first opeअक्रम is a namespace node */

		node = (काष्ठा acpi_namespace_node *)opeअक्रम[0];

		/* Second value is the notअगरy value */

		value = (u32) opeअक्रम[1]->पूर्णांकeger.value;

		/* Are notअगरies allowed on this object? */

		अगर (!acpi_ev_is_notअगरy_object(node)) अणु
			ACPI_ERROR((AE_INFO,
				    "Unexpected notify object type [%s]",
				    acpi_ut_get_type_name(node->type)));

			status = AE_AML_OPERAND_TYPE;
			अवरोध;
		पूर्ण

		/*
		 * Dispatch the notअगरy to the appropriate handler
		 * NOTE: the request is queued क्रम execution after this method
		 * completes. The notअगरy handlers are NOT invoked synchronously
		 * from this thपढ़ो -- because handlers may in turn run other
		 * control methods.
		 */
		status = acpi_ev_queue_notअगरy_request(node, value);
		अवरोध;

	शेष:

		ACPI_ERROR((AE_INFO, "Unknown AML opcode 0x%X",
			    walk_state->opcode));
		status = AE_AML_BAD_OPCODE;
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_opcode_2A_2T_1R
 *
 * PARAMETERS:  walk_state          - Current walk state
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Execute a dyadic चालक (2 opeअक्रमs) with 2 output tarमाला_लो
 *              and one implicit वापस value.
 *
 ******************************************************************************/

acpi_status acpi_ex_opcode_2A_2T_1R(काष्ठा acpi_walk_state *walk_state)
अणु
	जोड़ acpi_opeअक्रम_object **opeअक्रम = &walk_state->opeअक्रमs[0];
	जोड़ acpi_opeअक्रम_object *वापस_desc1 = शून्य;
	जोड़ acpi_opeअक्रम_object *वापस_desc2 = शून्य;
	acpi_status status;

	ACPI_FUNCTION_TRACE_STR(ex_opcode_2A_2T_1R,
				acpi_ps_get_opcode_name(walk_state->opcode));

	/* Execute the opcode */

	चयन (walk_state->opcode) अणु
	हाल AML_DIVIDE_OP:

		/* Divide (Dividend, Divisor, reमुख्यder_result quotient_result) */

		वापस_desc1 =
		    acpi_ut_create_पूर्णांकernal_object(ACPI_TYPE_INTEGER);
		अगर (!वापस_desc1) अणु
			status = AE_NO_MEMORY;
			जाओ cleanup;
		पूर्ण

		वापस_desc2 =
		    acpi_ut_create_पूर्णांकernal_object(ACPI_TYPE_INTEGER);
		अगर (!वापस_desc2) अणु
			status = AE_NO_MEMORY;
			जाओ cleanup;
		पूर्ण

		/* Quotient to वापस_desc1, reमुख्यder to वापस_desc2 */

		status = acpi_ut_भागide(opeअक्रम[0]->पूर्णांकeger.value,
					opeअक्रम[1]->पूर्णांकeger.value,
					&वापस_desc1->पूर्णांकeger.value,
					&वापस_desc2->पूर्णांकeger.value);
		अगर (ACPI_FAILURE(status)) अणु
			जाओ cleanup;
		पूर्ण
		अवरोध;

	शेष:

		ACPI_ERROR((AE_INFO, "Unknown AML opcode 0x%X",
			    walk_state->opcode));

		status = AE_AML_BAD_OPCODE;
		जाओ cleanup;
	पूर्ण

	/* Store the results to the target reference opeअक्रमs */

	status = acpi_ex_store(वापस_desc2, opeअक्रम[2], walk_state);
	अगर (ACPI_FAILURE(status)) अणु
		जाओ cleanup;
	पूर्ण

	status = acpi_ex_store(वापस_desc1, opeअक्रम[3], walk_state);
	अगर (ACPI_FAILURE(status)) अणु
		जाओ cleanup;
	पूर्ण

cleanup:
	/*
	 * Since the reमुख्यder is not वापसed indirectly, हटाओ a reference to
	 * it. Only the quotient is वापसed indirectly.
	 */
	acpi_ut_हटाओ_reference(वापस_desc2);

	अगर (ACPI_FAILURE(status)) अणु

		/* Delete the वापस object */

		acpi_ut_हटाओ_reference(वापस_desc1);
	पूर्ण

	/* Save वापस object (the reमुख्यder) on success */

	अन्यथा अणु
		walk_state->result_obj = वापस_desc1;
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_opcode_2A_1T_1R
 *
 * PARAMETERS:  walk_state          - Current walk state
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Execute opcode with two arguments, one target, and a वापस
 *              value.
 *
 ******************************************************************************/

acpi_status acpi_ex_opcode_2A_1T_1R(काष्ठा acpi_walk_state *walk_state)
अणु
	जोड़ acpi_opeअक्रम_object **opeअक्रम = &walk_state->opeअक्रमs[0];
	जोड़ acpi_opeअक्रम_object *वापस_desc = शून्य;
	u64 index;
	acpi_status status = AE_OK;
	acpi_size length = 0;

	ACPI_FUNCTION_TRACE_STR(ex_opcode_2A_1T_1R,
				acpi_ps_get_opcode_name(walk_state->opcode));

	/* Execute the opcode */

	अगर (walk_state->op_info->flags & AML_MATH) अणु

		/* All simple math opcodes (add, etc.) */

		वापस_desc = acpi_ut_create_पूर्णांकernal_object(ACPI_TYPE_INTEGER);
		अगर (!वापस_desc) अणु
			status = AE_NO_MEMORY;
			जाओ cleanup;
		पूर्ण

		वापस_desc->पूर्णांकeger.value =
		    acpi_ex_करो_math_op(walk_state->opcode,
				       opeअक्रम[0]->पूर्णांकeger.value,
				       opeअक्रम[1]->पूर्णांकeger.value);
		जाओ store_result_to_target;
	पूर्ण

	चयन (walk_state->opcode) अणु
	हाल AML_MOD_OP:	/* Mod (Dividend, Divisor, reमुख्यder_result (ACPI 2.0) */

		वापस_desc = acpi_ut_create_पूर्णांकernal_object(ACPI_TYPE_INTEGER);
		अगर (!वापस_desc) अणु
			status = AE_NO_MEMORY;
			जाओ cleanup;
		पूर्ण

		/* वापस_desc will contain the reमुख्यder */

		status = acpi_ut_भागide(opeअक्रम[0]->पूर्णांकeger.value,
					opeअक्रम[1]->पूर्णांकeger.value,
					शून्य, &वापस_desc->पूर्णांकeger.value);
		अवरोध;

	हाल AML_CONCATENATE_OP:	/* Concatenate (Data1, Data2, Result) */

		status =
		    acpi_ex_करो_concatenate(opeअक्रम[0], opeअक्रम[1], &वापस_desc,
					   walk_state);
		अवरोध;

	हाल AML_TO_STRING_OP:	/* to_string (Buffer, Length, Result) (ACPI 2.0) */
		/*
		 * Input object is guaranteed to be a buffer at this poपूर्णांक (it may have
		 * been converted.)  Copy the raw buffer data to a new object of
		 * type String.
		 */

		/*
		 * Get the length of the new string. It is the smallest of:
		 * 1) Length of the input buffer
		 * 2) Max length as specअगरied in the to_string चालक
		 * 3) Length of input buffer up to a zero byte (null terminator)
		 *
		 * NOTE: A length of zero is ok, and will create a zero-length, null
		 *       terminated string.
		 */
		जबतक ((length < opeअक्रम[0]->buffer.length) &&	/* Length of input buffer */
		       (length < opeअक्रम[1]->पूर्णांकeger.value) &&	/* Length opeअक्रम */
		       (opeअक्रम[0]->buffer.poपूर्णांकer[length])) अणु	/* Null terminator */
			length++;
		पूर्ण

		/* Allocate a new string object */

		वापस_desc = acpi_ut_create_string_object(length);
		अगर (!वापस_desc) अणु
			status = AE_NO_MEMORY;
			जाओ cleanup;
		पूर्ण

		/*
		 * Copy the raw buffer data with no transक्रमm.
		 * (शून्य terminated alपढ़ोy)
		 */
		स_नकल(वापस_desc->string.poपूर्णांकer,
		       opeअक्रम[0]->buffer.poपूर्णांकer, length);
		अवरोध;

	हाल AML_CONCATENATE_TEMPLATE_OP:

		/* concatenate_res_ढाँचा (Buffer, Buffer, Result) (ACPI 2.0) */

		status =
		    acpi_ex_concat_ढाँचा(opeअक्रम[0], opeअक्रम[1],
					    &वापस_desc, walk_state);
		अवरोध;

	हाल AML_INDEX_OP:	/* Index (Source Index Result) */

		/* Create the पूर्णांकernal वापस object */

		वापस_desc =
		    acpi_ut_create_पूर्णांकernal_object(ACPI_TYPE_LOCAL_REFERENCE);
		अगर (!वापस_desc) अणु
			status = AE_NO_MEMORY;
			जाओ cleanup;
		पूर्ण

		/* Initialize the Index reference object */

		index = opeअक्रम[1]->पूर्णांकeger.value;
		वापस_desc->reference.value = (u32) index;
		वापस_desc->reference.class = ACPI_REFCLASS_INDEX;

		/*
		 * At this poपूर्णांक, the Source opeअक्रम is a String, Buffer, or Package.
		 * Verअगरy that the index is within range.
		 */
		चयन ((opeअक्रम[0])->common.type) अणु
		हाल ACPI_TYPE_STRING:

			अगर (index >= opeअक्रम[0]->string.length) अणु
				length = opeअक्रम[0]->string.length;
				status = AE_AML_STRING_LIMIT;
			पूर्ण

			वापस_desc->reference.target_type =
			    ACPI_TYPE_BUFFER_FIELD;
			वापस_desc->reference.index_poपूर्णांकer =
			    &(opeअक्रम[0]->buffer.poपूर्णांकer[index]);
			अवरोध;

		हाल ACPI_TYPE_BUFFER:

			अगर (index >= opeअक्रम[0]->buffer.length) अणु
				length = opeअक्रम[0]->buffer.length;
				status = AE_AML_BUFFER_LIMIT;
			पूर्ण

			वापस_desc->reference.target_type =
			    ACPI_TYPE_BUFFER_FIELD;
			वापस_desc->reference.index_poपूर्णांकer =
			    &(opeअक्रम[0]->buffer.poपूर्णांकer[index]);
			अवरोध;

		हाल ACPI_TYPE_PACKAGE:

			अगर (index >= opeअक्रम[0]->package.count) अणु
				length = opeअक्रम[0]->package.count;
				status = AE_AML_PACKAGE_LIMIT;
			पूर्ण

			वापस_desc->reference.target_type = ACPI_TYPE_PACKAGE;
			वापस_desc->reference.where =
			    &opeअक्रम[0]->package.elements[index];
			अवरोध;

		शेष:

			ACPI_ERROR((AE_INFO,
				    "Invalid object type: %X",
				    (opeअक्रम[0])->common.type));
			status = AE_AML_INTERNAL;
			जाओ cleanup;
		पूर्ण

		/* Failure means that the Index was beyond the end of the object */

		अगर (ACPI_FAILURE(status)) अणु
			ACPI_BIOS_EXCEPTION((AE_INFO, status,
					     "Index (0x%X%8.8X) is beyond end of object (length 0x%X)",
					     ACPI_FORMAT_UINT64(index),
					     (u32)length));
			जाओ cleanup;
		पूर्ण

		/*
		 * Save the target object and add a reference to it क्रम the lअगरe
		 * of the index
		 */
		वापस_desc->reference.object = opeअक्रम[0];
		acpi_ut_add_reference(opeअक्रम[0]);

		/* Store the reference to the Target */

		status = acpi_ex_store(वापस_desc, opeअक्रम[2], walk_state);

		/* Return the reference */

		walk_state->result_obj = वापस_desc;
		जाओ cleanup;

	शेष:

		ACPI_ERROR((AE_INFO, "Unknown AML opcode 0x%X",
			    walk_state->opcode));
		status = AE_AML_BAD_OPCODE;
		अवरोध;
	पूर्ण

store_result_to_target:

	अगर (ACPI_SUCCESS(status)) अणु
		/*
		 * Store the result of the operation (which is now in वापस_desc) पूर्णांकo
		 * the Target descriptor.
		 */
		status = acpi_ex_store(वापस_desc, opeअक्रम[2], walk_state);
		अगर (ACPI_FAILURE(status)) अणु
			जाओ cleanup;
		पूर्ण

		अगर (!walk_state->result_obj) अणु
			walk_state->result_obj = वापस_desc;
		पूर्ण
	पूर्ण

cleanup:

	/* Delete वापस object on error */

	अगर (ACPI_FAILURE(status)) अणु
		acpi_ut_हटाओ_reference(वापस_desc);
		walk_state->result_obj = शून्य;
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_opcode_2A_0T_1R
 *
 * PARAMETERS:  walk_state          - Current walk state
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Execute opcode with 2 arguments, no target, and a वापस value
 *
 ******************************************************************************/

acpi_status acpi_ex_opcode_2A_0T_1R(काष्ठा acpi_walk_state *walk_state)
अणु
	जोड़ acpi_opeअक्रम_object **opeअक्रम = &walk_state->opeअक्रमs[0];
	जोड़ acpi_opeअक्रम_object *वापस_desc = शून्य;
	acpi_status status = AE_OK;
	u8 logical_result = FALSE;

	ACPI_FUNCTION_TRACE_STR(ex_opcode_2A_0T_1R,
				acpi_ps_get_opcode_name(walk_state->opcode));

	/* Create the पूर्णांकernal वापस object */

	वापस_desc = acpi_ut_create_पूर्णांकernal_object(ACPI_TYPE_INTEGER);
	अगर (!वापस_desc) अणु
		status = AE_NO_MEMORY;
		जाओ cleanup;
	पूर्ण

	/* Execute the Opcode */

	अगर (walk_state->op_info->flags & AML_LOGICAL_NUMERIC) अणु

		/* logical_op (Opeअक्रम0, Opeअक्रम1) */

		status = acpi_ex_करो_logical_numeric_op(walk_state->opcode,
						       opeअक्रम[0]->पूर्णांकeger.
						       value,
						       opeअक्रम[1]->पूर्णांकeger.
						       value, &logical_result);
		जाओ store_logical_result;
	पूर्ण अन्यथा अगर (walk_state->op_info->flags & AML_LOGICAL) अणु

		/* logical_op (Opeअक्रम0, Opeअक्रम1) */

		status = acpi_ex_करो_logical_op(walk_state->opcode, opeअक्रम[0],
					       opeअक्रम[1], &logical_result);
		जाओ store_logical_result;
	पूर्ण

	चयन (walk_state->opcode) अणु
	हाल AML_ACQUIRE_OP:	/* Acquire (mutex_object, Timeout) */

		status =
		    acpi_ex_acquire_mutex(opeअक्रम[1], opeअक्रम[0], walk_state);
		अगर (status == AE_TIME) अणु
			logical_result = TRUE;	/* TRUE = Acquire समयd out */
			status = AE_OK;
		पूर्ण
		अवरोध;

	हाल AML_WAIT_OP:	/* Wait (event_object, Timeout) */

		status = acpi_ex_प्रणाली_रुको_event(opeअक्रम[1], opeअक्रम[0]);
		अगर (status == AE_TIME) अणु
			logical_result = TRUE;	/* TRUE, Wait समयd out */
			status = AE_OK;
		पूर्ण
		अवरोध;

	शेष:

		ACPI_ERROR((AE_INFO, "Unknown AML opcode 0x%X",
			    walk_state->opcode));

		status = AE_AML_BAD_OPCODE;
		जाओ cleanup;
	पूर्ण

store_logical_result:
	/*
	 * Set वापस value to according to logical_result. logical TRUE (all ones)
	 * Default is FALSE (zero)
	 */
	अगर (logical_result) अणु
		वापस_desc->पूर्णांकeger.value = ACPI_UINT64_MAX;
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
