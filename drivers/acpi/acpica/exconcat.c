<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: exconcat - Concatenate-type AML चालकs
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acinterp.h"
#समावेश "amlresrc.h"

#घोषणा _COMPONENT          ACPI_EXECUTER
ACPI_MODULE_NAME("exconcat")

/* Local Prototypes */
अटल acpi_status
acpi_ex_convert_to_object_type_string(जोड़ acpi_opeअक्रम_object *obj_desc,
				      जोड़ acpi_opeअक्रम_object **result_desc);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_करो_concatenate
 *
 * PARAMETERS:  opeअक्रम0            - First source object
 *              opeअक्रम1            - Second source object
 *              actual_वापस_desc  - Where to place the वापस object
 *              walk_state          - Current walk state
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Concatenate two objects with the ACPI-defined conversion
 *              rules as necessary.
 * NOTE:
 * Per the ACPI spec (up to 6.1), Concatenate only supports Integer,
 * String, and Buffer objects. However, we support all objects here
 * as an extension. This improves the usefulness of both Concatenate
 * and the Prपूर्णांकf/Fम_लिखो macros. The extension वापसs a string
 * describing the object type क्रम the other objects.
 * 02/2016.
 *
 ******************************************************************************/

acpi_status
acpi_ex_करो_concatenate(जोड़ acpi_opeअक्रम_object *opeअक्रम0,
		       जोड़ acpi_opeअक्रम_object *opeअक्रम1,
		       जोड़ acpi_opeअक्रम_object **actual_वापस_desc,
		       काष्ठा acpi_walk_state *walk_state)
अणु
	जोड़ acpi_opeअक्रम_object *local_opeअक्रम0 = opeअक्रम0;
	जोड़ acpi_opeअक्रम_object *local_opeअक्रम1 = opeअक्रम1;
	जोड़ acpi_opeअक्रम_object *temp_opeअक्रम1 = शून्य;
	जोड़ acpi_opeअक्रम_object *वापस_desc;
	अक्षर *buffer;
	acpi_object_type opeअक्रम0_type;
	acpi_object_type opeअक्रम1_type;
	acpi_status status;

	ACPI_FUNCTION_TRACE(ex_करो_concatenate);

	/* Opeअक्रम 0 preprocessing */

	चयन (opeअक्रम0->common.type) अणु
	हाल ACPI_TYPE_INTEGER:
	हाल ACPI_TYPE_STRING:
	हाल ACPI_TYPE_BUFFER:

		opeअक्रम0_type = opeअक्रम0->common.type;
		अवरोध;

	शेष:

		/* For all other types, get the "object type" string */

		status =
		    acpi_ex_convert_to_object_type_string(opeअक्रम0,
							  &local_opeअक्रम0);
		अगर (ACPI_FAILURE(status)) अणु
			जाओ cleanup;
		पूर्ण

		opeअक्रम0_type = ACPI_TYPE_STRING;
		अवरोध;
	पूर्ण

	/* Opeअक्रम 1 preprocessing */

	चयन (opeअक्रम1->common.type) अणु
	हाल ACPI_TYPE_INTEGER:
	हाल ACPI_TYPE_STRING:
	हाल ACPI_TYPE_BUFFER:

		opeअक्रम1_type = opeअक्रम1->common.type;
		अवरोध;

	शेष:

		/* For all other types, get the "object type" string */

		status =
		    acpi_ex_convert_to_object_type_string(opeअक्रम1,
							  &local_opeअक्रम1);
		अगर (ACPI_FAILURE(status)) अणु
			जाओ cleanup;
		पूर्ण

		opeअक्रम1_type = ACPI_TYPE_STRING;
		अवरोध;
	पूर्ण

	/*
	 * Convert the second opeअक्रम अगर necessary. The first opeअक्रम (0)
	 * determines the type of the second opeअक्रम (1) (See the Data Types
	 * section of the ACPI specअगरication). Both object types are
	 * guaranteed to be either Integer/String/Buffer by the opeअक्रम
	 * resolution mechanism.
	 */
	चयन (opeअक्रम0_type) अणु
	हाल ACPI_TYPE_INTEGER:

		status =
		    acpi_ex_convert_to_पूर्णांकeger(local_opeअक्रम1, &temp_opeअक्रम1,
					       ACPI_IMPLICIT_CONVERSION);
		अवरोध;

	हाल ACPI_TYPE_BUFFER:

		status =
		    acpi_ex_convert_to_buffer(local_opeअक्रम1, &temp_opeअक्रम1);
		अवरोध;

	हाल ACPI_TYPE_STRING:

		चयन (opeअक्रम1_type) अणु
		हाल ACPI_TYPE_INTEGER:
		हाल ACPI_TYPE_STRING:
		हाल ACPI_TYPE_BUFFER:

			/* Other types have alपढ़ोy been converted to string */

			status =
			    acpi_ex_convert_to_string(local_opeअक्रम1,
						      &temp_opeअक्रम1,
						      ACPI_IMPLICIT_CONVERT_HEX);
			अवरोध;

		शेष:

			status = AE_OK;
			अवरोध;
		पूर्ण
		अवरोध;

	शेष:

		ACPI_ERROR((AE_INFO, "Invalid object type: 0x%X",
			    opeअक्रम0->common.type));
		status = AE_AML_INTERNAL;
	पूर्ण

	अगर (ACPI_FAILURE(status)) अणु
		जाओ cleanup;
	पूर्ण

	/* Take care with any newly created opeअक्रम objects */

	अगर ((local_opeअक्रम1 != opeअक्रम1) && (local_opeअक्रम1 != temp_opeअक्रम1)) अणु
		acpi_ut_हटाओ_reference(local_opeअक्रम1);
	पूर्ण

	local_opeअक्रम1 = temp_opeअक्रम1;

	/*
	 * Both opeअक्रमs are now known to be the same object type
	 * (Both are Integer, String, or Buffer), and we can now perक्रमm
	 * the concatenation.
	 *
	 * There are three हालs to handle, as per the ACPI spec:
	 *
	 * 1) Two Integers concatenated to produce a new Buffer
	 * 2) Two Strings concatenated to produce a new String
	 * 3) Two Buffers concatenated to produce a new Buffer
	 */
	चयन (opeअक्रम0_type) अणु
	हाल ACPI_TYPE_INTEGER:

		/* Result of two Integers is a Buffer */
		/* Need enough buffer space क्रम two पूर्णांकegers */

		वापस_desc = acpi_ut_create_buffer_object((acpi_size)
							   ACPI_MUL_2
							   (acpi_gbl_पूर्णांकeger_byte_width));
		अगर (!वापस_desc) अणु
			status = AE_NO_MEMORY;
			जाओ cleanup;
		पूर्ण

		buffer = (अक्षर *)वापस_desc->buffer.poपूर्णांकer;

		/* Copy the first पूर्णांकeger, LSB first */

		स_नकल(buffer, &opeअक्रम0->पूर्णांकeger.value,
		       acpi_gbl_पूर्णांकeger_byte_width);

		/* Copy the second पूर्णांकeger (LSB first) after the first */

		स_नकल(buffer + acpi_gbl_पूर्णांकeger_byte_width,
		       &local_opeअक्रम1->पूर्णांकeger.value,
		       acpi_gbl_पूर्णांकeger_byte_width);
		अवरोध;

	हाल ACPI_TYPE_STRING:

		/* Result of two Strings is a String */

		वापस_desc = acpi_ut_create_string_object(((acpi_size)
							    local_opeअक्रम0->
							    string.length +
							    local_opeअक्रम1->
							    string.length));
		अगर (!वापस_desc) अणु
			status = AE_NO_MEMORY;
			जाओ cleanup;
		पूर्ण

		buffer = वापस_desc->string.poपूर्णांकer;

		/* Concatenate the strings */

		म_नकल(buffer, local_opeअक्रम0->string.poपूर्णांकer);
		म_जोड़ो(buffer, local_opeअक्रम1->string.poपूर्णांकer);
		अवरोध;

	हाल ACPI_TYPE_BUFFER:

		/* Result of two Buffers is a Buffer */

		वापस_desc = acpi_ut_create_buffer_object(((acpi_size)
							    opeअक्रम0->buffer.
							    length +
							    local_opeअक्रम1->
							    buffer.length));
		अगर (!वापस_desc) अणु
			status = AE_NO_MEMORY;
			जाओ cleanup;
		पूर्ण

		buffer = (अक्षर *)वापस_desc->buffer.poपूर्णांकer;

		/* Concatenate the buffers */

		स_नकल(buffer, opeअक्रम0->buffer.poपूर्णांकer,
		       opeअक्रम0->buffer.length);
		स_नकल(buffer + opeअक्रम0->buffer.length,
		       local_opeअक्रम1->buffer.poपूर्णांकer,
		       local_opeअक्रम1->buffer.length);
		अवरोध;

	शेष:

		/* Invalid object type, should not happen here */

		ACPI_ERROR((AE_INFO, "Invalid object type: 0x%X",
			    opeअक्रम0->common.type));
		status = AE_AML_INTERNAL;
		जाओ cleanup;
	पूर्ण

	*actual_वापस_desc = वापस_desc;

cleanup:
	अगर (local_opeअक्रम0 != opeअक्रम0) अणु
		acpi_ut_हटाओ_reference(local_opeअक्रम0);
	पूर्ण

	अगर (local_opeअक्रम1 != opeअक्रम1) अणु
		acpi_ut_हटाओ_reference(local_opeअक्रम1);
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_convert_to_object_type_string
 *
 * PARAMETERS:  obj_desc            - Object to be converted
 *              वापस_desc         - Where to place the वापस object
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Convert an object of arbitrary type to a string object that
 *              contains the namestring क्रम the object. Used क्रम the
 *              concatenate चालक.
 *
 ******************************************************************************/

अटल acpi_status
acpi_ex_convert_to_object_type_string(जोड़ acpi_opeअक्रम_object *obj_desc,
				      जोड़ acpi_opeअक्रम_object **result_desc)
अणु
	जोड़ acpi_opeअक्रम_object *वापस_desc;
	स्थिर अक्षर *type_string;

	type_string = acpi_ut_get_type_name(obj_desc->common.type);

	वापस_desc = acpi_ut_create_string_object(((acpi_size)म_माप(type_string) + 9));	/* 9 For "[ Object]" */
	अगर (!वापस_desc) अणु
		वापस (AE_NO_MEMORY);
	पूर्ण

	म_नकल(वापस_desc->string.poपूर्णांकer, "[");
	म_जोड़ो(वापस_desc->string.poपूर्णांकer, type_string);
	म_जोड़ो(वापस_desc->string.poपूर्णांकer, " Object]");

	*result_desc = वापस_desc;
	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_concat_ढाँचा
 *
 * PARAMETERS:  opeअक्रम0            - First source object
 *              opeअक्रम1            - Second source object
 *              actual_वापस_desc  - Where to place the वापस object
 *              walk_state          - Current walk state
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Concatenate two resource ढाँचाs
 *
 ******************************************************************************/

acpi_status
acpi_ex_concat_ढाँचा(जोड़ acpi_opeअक्रम_object *opeअक्रम0,
			जोड़ acpi_opeअक्रम_object *opeअक्रम1,
			जोड़ acpi_opeअक्रम_object **actual_वापस_desc,
			काष्ठा acpi_walk_state *walk_state)
अणु
	acpi_status status;
	जोड़ acpi_opeअक्रम_object *वापस_desc;
	u8 *new_buf;
	u8 *end_tag;
	acpi_size length0;
	acpi_size length1;
	acpi_size new_length;

	ACPI_FUNCTION_TRACE(ex_concat_ढाँचा);

	/*
	 * Find the end_tag descriptor in each resource ढाँचा.
	 * Note1: वापसed poपूर्णांकers poपूर्णांक TO the end_tag, not past it.
	 * Note2: zero-length buffers are allowed; treated like one end_tag
	 */

	/* Get the length of the first resource ढाँचा */

	status = acpi_ut_get_resource_end_tag(opeअक्रम0, &end_tag);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	length0 = ACPI_PTR_DIFF(end_tag, opeअक्रम0->buffer.poपूर्णांकer);

	/* Get the length of the second resource ढाँचा */

	status = acpi_ut_get_resource_end_tag(opeअक्रम1, &end_tag);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	length1 = ACPI_PTR_DIFF(end_tag, opeअक्रम1->buffer.poपूर्णांकer);

	/* Combine both lengths, minimum size will be 2 क्रम end_tag */

	new_length = length0 + length1 + माप(काष्ठा aml_resource_end_tag);

	/* Create a new buffer object क्रम the result (with one end_tag) */

	वापस_desc = acpi_ut_create_buffer_object(new_length);
	अगर (!वापस_desc) अणु
		वापस_ACPI_STATUS(AE_NO_MEMORY);
	पूर्ण

	/*
	 * Copy the ढाँचाs to the new buffer, 0 first, then 1 follows. One
	 * end_tag descriptor is copied from Opeअक्रम1.
	 */
	new_buf = वापस_desc->buffer.poपूर्णांकer;
	स_नकल(new_buf, opeअक्रम0->buffer.poपूर्णांकer, length0);
	स_नकल(new_buf + length0, opeअक्रम1->buffer.poपूर्णांकer, length1);

	/* Insert end_tag and set the checksum to zero, means "ignore checksum" */

	new_buf[new_length - 1] = 0;
	new_buf[new_length - 2] = ACPI_RESOURCE_NAME_END_TAG | 1;

	/* Return the completed resource ढाँचा */

	*actual_वापस_desc = वापस_desc;
	वापस_ACPI_STATUS(AE_OK);
पूर्ण
