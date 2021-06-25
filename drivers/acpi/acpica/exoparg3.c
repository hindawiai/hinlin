<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: exoparg3 - AML execution - opcodes with 3 arguments
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
ACPI_MODULE_NAME("exoparg3")

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
 * FUNCTION:    acpi_ex_opcode_3A_0T_0R
 *
 * PARAMETERS:  walk_state          - Current walk state
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Execute Triadic चालक (3 opeअक्रमs)
 *
 ******************************************************************************/
acpi_status acpi_ex_opcode_3A_0T_0R(काष्ठा acpi_walk_state *walk_state)
अणु
	जोड़ acpi_opeअक्रम_object **opeअक्रम = &walk_state->opeअक्रमs[0];
	काष्ठा acpi_संकेत_fatal_info *fatal;
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TRACE_STR(ex_opcode_3A_0T_0R,
				acpi_ps_get_opcode_name(walk_state->opcode));

	चयन (walk_state->opcode) अणु
	हाल AML_FATAL_OP:	/* Fatal (fatal_type fatal_code fatal_arg) */

		ACPI_DEBUG_PRINT((ACPI_DB_INFO,
				  "FatalOp: Type %X Code %X Arg %X "
				  "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n",
				  (u32)opeअक्रम[0]->पूर्णांकeger.value,
				  (u32)opeअक्रम[1]->पूर्णांकeger.value,
				  (u32)opeअक्रम[2]->पूर्णांकeger.value));

		fatal = ACPI_ALLOCATE(माप(काष्ठा acpi_संकेत_fatal_info));
		अगर (fatal) अणु
			fatal->type = (u32) opeअक्रम[0]->पूर्णांकeger.value;
			fatal->code = (u32) opeअक्रम[1]->पूर्णांकeger.value;
			fatal->argument = (u32) opeअक्रम[2]->पूर्णांकeger.value;
		पूर्ण

		/* Always संकेत the OS! */

		status = acpi_os_संकेत(ACPI_SIGNAL_FATAL, fatal);

		/* Might वापस जबतक OS is shutting करोwn, just जारी */

		ACPI_FREE(fatal);
		जाओ cleanup;

	हाल AML_EXTERNAL_OP:
		/*
		 * If the पूर्णांकerpreter sees this opcode, just ignore it. The External
		 * op is पूर्णांकended क्रम use by disassemblers in order to properly
		 * disassemble control method invocations. The opcode or group of
		 * opcodes should be surrounded by an "if (0)" clause to ensure that
		 * AML पूर्णांकerpreters never see the opcode. Thus, something is
		 * wrong अगर an बाह्यal opcode ever माला_लो here.
		 */
		ACPI_ERROR((AE_INFO, "Executed External Op"));
		status = AE_OK;
		जाओ cleanup;

	शेष:

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
 * FUNCTION:    acpi_ex_opcode_3A_1T_1R
 *
 * PARAMETERS:  walk_state          - Current walk state
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Execute Triadic चालक (3 opeअक्रमs)
 *
 ******************************************************************************/

acpi_status acpi_ex_opcode_3A_1T_1R(काष्ठा acpi_walk_state *walk_state)
अणु
	जोड़ acpi_opeअक्रम_object **opeअक्रम = &walk_state->opeअक्रमs[0];
	जोड़ acpi_opeअक्रम_object *वापस_desc = शून्य;
	अक्षर *buffer = शून्य;
	acpi_status status = AE_OK;
	u64 index;
	acpi_size length;

	ACPI_FUNCTION_TRACE_STR(ex_opcode_3A_1T_1R,
				acpi_ps_get_opcode_name(walk_state->opcode));

	चयन (walk_state->opcode) अणु
	हाल AML_MID_OP:	/* Mid (Source[0], Index[1], Length[2], Result[3]) */
		/*
		 * Create the वापस object. The Source opeअक्रम is guaranteed to be
		 * either a String or a Buffer, so just use its type.
		 */
		वापस_desc = acpi_ut_create_पूर्णांकernal_object((opeअक्रम[0])->
							     common.type);
		अगर (!वापस_desc) अणु
			status = AE_NO_MEMORY;
			जाओ cleanup;
		पूर्ण

		/* Get the Integer values from the objects */

		index = opeअक्रम[1]->पूर्णांकeger.value;
		length = (acpi_size)opeअक्रम[2]->पूर्णांकeger.value;

		/*
		 * If the index is beyond the length of the String/Buffer, or अगर the
		 * requested length is zero, वापस a zero-length String/Buffer
		 */
		अगर (index >= opeअक्रम[0]->string.length) अणु
			length = 0;
		पूर्ण

		/* Truncate request अगर larger than the actual String/Buffer */

		अन्यथा अगर ((index + length) > opeअक्रम[0]->string.length) अणु
			length =
			    (acpi_size)opeअक्रम[0]->string.length -
			    (acpi_size)index;
		पूर्ण

		/* Strings always have a sub-poपूर्णांकer, not so क्रम buffers */

		चयन ((opeअक्रम[0])->common.type) अणु
		हाल ACPI_TYPE_STRING:

			/* Always allocate a new buffer क्रम the String */

			buffer = ACPI_ALLOCATE_ZEROED((acpi_size)length + 1);
			अगर (!buffer) अणु
				status = AE_NO_MEMORY;
				जाओ cleanup;
			पूर्ण
			अवरोध;

		हाल ACPI_TYPE_BUFFER:

			/* If the requested length is zero, करोn't allocate a buffer */

			अगर (length > 0) अणु

				/* Allocate a new buffer क्रम the Buffer */

				buffer = ACPI_ALLOCATE_ZEROED(length);
				अगर (!buffer) अणु
					status = AE_NO_MEMORY;
					जाओ cleanup;
				पूर्ण
			पूर्ण
			अवरोध;

		शेष:	/* Should not happen */

			status = AE_AML_OPERAND_TYPE;
			जाओ cleanup;
		पूर्ण

		अगर (buffer) अणु

			/* We have a buffer, copy the portion requested */

			स_नकल(buffer,
			       opeअक्रम[0]->string.poपूर्णांकer + index, length);
		पूर्ण

		/* Set the length of the new String/Buffer */

		वापस_desc->string.poपूर्णांकer = buffer;
		वापस_desc->string.length = (u32) length;

		/* Mark buffer initialized */

		वापस_desc->buffer.flags |= AOPOBJ_DATA_VALID;
		अवरोध;

	शेष:

		ACPI_ERROR((AE_INFO, "Unknown AML opcode 0x%X",
			    walk_state->opcode));

		status = AE_AML_BAD_OPCODE;
		जाओ cleanup;
	पूर्ण

	/* Store the result in the target */

	status = acpi_ex_store(वापस_desc, opeअक्रम[3], walk_state);

cleanup:

	/* Delete वापस object on error */

	अगर (ACPI_FAILURE(status) || walk_state->result_obj) अणु
		acpi_ut_हटाओ_reference(वापस_desc);
		walk_state->result_obj = शून्य;
	पूर्ण अन्यथा अणु
		/* Set the वापस object and निकास */

		walk_state->result_obj = वापस_desc;
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण
