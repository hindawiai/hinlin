<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: nsconvert - Object conversions क्रम objects वापसed by
 *                          predefined methods
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acnamesp.h"
#समावेश "acinterp.h"
#समावेश "acpredef.h"
#समावेश "amlresrc.h"

#घोषणा _COMPONENT          ACPI_NAMESPACE
ACPI_MODULE_NAME("nsconvert")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_convert_to_पूर्णांकeger
 *
 * PARAMETERS:  original_object     - Object to be converted
 *              वापस_object       - Where the new converted object is वापसed
 *
 * RETURN:      Status. AE_OK अगर conversion was successful.
 *
 * DESCRIPTION: Attempt to convert a String/Buffer object to an Integer.
 *
 ******************************************************************************/
acpi_status
acpi_ns_convert_to_पूर्णांकeger(जोड़ acpi_opeअक्रम_object *original_object,
			   जोड़ acpi_opeअक्रम_object **वापस_object)
अणु
	जोड़ acpi_opeअक्रम_object *new_object;
	acpi_status status;
	u64 value = 0;
	u32 i;

	चयन (original_object->common.type) अणु
	हाल ACPI_TYPE_STRING:

		/* String-to-Integer conversion */

		status =
		    acpi_ut_म_से_अदीर्घ64(original_object->string.poपूर्णांकer, &value);
		अगर (ACPI_FAILURE(status)) अणु
			वापस (status);
		पूर्ण
		अवरोध;

	हाल ACPI_TYPE_BUFFER:

		/* Buffer-to-Integer conversion. Max buffer size is 64 bits. */

		अगर (original_object->buffer.length > 8) अणु
			वापस (AE_AML_OPERAND_TYPE);
		पूर्ण

		/* Extract each buffer byte to create the पूर्णांकeger */

		क्रम (i = 0; i < original_object->buffer.length; i++) अणु
			value |= ((u64)
				  original_object->buffer.poपूर्णांकer[i] << (i *
									 8));
		पूर्ण
		अवरोध;

	शेष:

		वापस (AE_AML_OPERAND_TYPE);
	पूर्ण

	new_object = acpi_ut_create_पूर्णांकeger_object(value);
	अगर (!new_object) अणु
		वापस (AE_NO_MEMORY);
	पूर्ण

	*वापस_object = new_object;
	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_convert_to_string
 *
 * PARAMETERS:  original_object     - Object to be converted
 *              वापस_object       - Where the new converted object is वापसed
 *
 * RETURN:      Status. AE_OK अगर conversion was successful.
 *
 * DESCRIPTION: Attempt to convert a Integer/Buffer object to a String.
 *
 ******************************************************************************/

acpi_status
acpi_ns_convert_to_string(जोड़ acpi_opeअक्रम_object *original_object,
			  जोड़ acpi_opeअक्रम_object **वापस_object)
अणु
	जोड़ acpi_opeअक्रम_object *new_object;
	acpi_size length;
	acpi_status status;

	चयन (original_object->common.type) अणु
	हाल ACPI_TYPE_INTEGER:
		/*
		 * Integer-to-String conversion. Commonly, convert
		 * an पूर्णांकeger of value 0 to a शून्य string. The last element of
		 * _BIF and _BIX packages occasionally need this fix.
		 */
		अगर (original_object->पूर्णांकeger.value == 0) अणु

			/* Allocate a new शून्य string object */

			new_object = acpi_ut_create_string_object(0);
			अगर (!new_object) अणु
				वापस (AE_NO_MEMORY);
			पूर्ण
		पूर्ण अन्यथा अणु
			status = acpi_ex_convert_to_string(original_object,
							   &new_object,
							   ACPI_IMPLICIT_CONVERT_HEX);
			अगर (ACPI_FAILURE(status)) अणु
				वापस (status);
			पूर्ण
		पूर्ण
		अवरोध;

	हाल ACPI_TYPE_BUFFER:
		/*
		 * Buffer-to-String conversion. Use a to_string
		 * conversion, no transक्रमm perक्रमmed on the buffer data. The best
		 * example of this is the _BIF method, where the string data from
		 * the battery is often (incorrectly) वापसed as buffer object(s).
		 */
		length = 0;
		जबतक ((length < original_object->buffer.length) &&
		       (original_object->buffer.poपूर्णांकer[length])) अणु
			length++;
		पूर्ण

		/* Allocate a new string object */

		new_object = acpi_ut_create_string_object(length);
		अगर (!new_object) अणु
			वापस (AE_NO_MEMORY);
		पूर्ण

		/*
		 * Copy the raw buffer data with no transक्रमm. String is alपढ़ोy शून्य
		 * terminated at Length+1.
		 */
		स_नकल(new_object->string.poपूर्णांकer,
		       original_object->buffer.poपूर्णांकer, length);
		अवरोध;

	शेष:

		वापस (AE_AML_OPERAND_TYPE);
	पूर्ण

	*वापस_object = new_object;
	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_convert_to_buffer
 *
 * PARAMETERS:  original_object     - Object to be converted
 *              वापस_object       - Where the new converted object is वापसed
 *
 * RETURN:      Status. AE_OK अगर conversion was successful.
 *
 * DESCRIPTION: Attempt to convert a Integer/String/Package object to a Buffer.
 *
 ******************************************************************************/

acpi_status
acpi_ns_convert_to_buffer(जोड़ acpi_opeअक्रम_object *original_object,
			  जोड़ acpi_opeअक्रम_object **वापस_object)
अणु
	जोड़ acpi_opeअक्रम_object *new_object;
	acpi_status status;
	जोड़ acpi_opeअक्रम_object **elements;
	u32 *dword_buffer;
	u32 count;
	u32 i;

	चयन (original_object->common.type) अणु
	हाल ACPI_TYPE_INTEGER:
		/*
		 * Integer-to-Buffer conversion.
		 * Convert the Integer to a packed-byte buffer. _MAT and other
		 * objects need this someबार, अगर a पढ़ो has been perक्रमmed on a
		 * Field object that is less than or equal to the global पूर्णांकeger
		 * size (32 or 64 bits).
		 */
		status =
		    acpi_ex_convert_to_buffer(original_object, &new_object);
		अगर (ACPI_FAILURE(status)) अणु
			वापस (status);
		पूर्ण
		अवरोध;

	हाल ACPI_TYPE_STRING:

		/* String-to-Buffer conversion. Simple data copy */

		new_object = acpi_ut_create_buffer_object
		    (original_object->string.length);
		अगर (!new_object) अणु
			वापस (AE_NO_MEMORY);
		पूर्ण

		स_नकल(new_object->buffer.poपूर्णांकer,
		       original_object->string.poपूर्णांकer,
		       original_object->string.length);
		अवरोध;

	हाल ACPI_TYPE_PACKAGE:
		/*
		 * This हाल is often seen क्रम predefined names that must वापस a
		 * Buffer object with multiple DWORD पूर्णांकegers within. For example,
		 * _FDE and _GTM. The Package can be converted to a Buffer.
		 */

		/* All elements of the Package must be पूर्णांकegers */

		elements = original_object->package.elements;
		count = original_object->package.count;

		क्रम (i = 0; i < count; i++) अणु
			अगर ((!*elements) ||
			    ((*elements)->common.type != ACPI_TYPE_INTEGER)) अणु
				वापस (AE_AML_OPERAND_TYPE);
			पूर्ण
			elements++;
		पूर्ण

		/* Create the new buffer object to replace the Package */

		new_object = acpi_ut_create_buffer_object(ACPI_MUL_4(count));
		अगर (!new_object) अणु
			वापस (AE_NO_MEMORY);
		पूर्ण

		/* Copy the package elements (पूर्णांकegers) to the buffer as DWORDs */

		elements = original_object->package.elements;
		dword_buffer = ACPI_CAST_PTR(u32, new_object->buffer.poपूर्णांकer);

		क्रम (i = 0; i < count; i++) अणु
			*dword_buffer = (u32)(*elements)->पूर्णांकeger.value;
			dword_buffer++;
			elements++;
		पूर्ण
		अवरोध;

	शेष:

		वापस (AE_AML_OPERAND_TYPE);
	पूर्ण

	*वापस_object = new_object;
	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_convert_to_unicode
 *
 * PARAMETERS:  scope               - Namespace node क्रम the method/object
 *              original_object     - ASCII String Object to be converted
 *              वापस_object       - Where the new converted object is वापसed
 *
 * RETURN:      Status. AE_OK अगर conversion was successful.
 *
 * DESCRIPTION: Attempt to convert a String object to a Unicode string Buffer.
 *
 ******************************************************************************/

acpi_status
acpi_ns_convert_to_unicode(काष्ठा acpi_namespace_node *scope,
			   जोड़ acpi_opeअक्रम_object *original_object,
			   जोड़ acpi_opeअक्रम_object **वापस_object)
अणु
	जोड़ acpi_opeअक्रम_object *new_object;
	अक्षर *ascii_string;
	u16 *unicode_buffer;
	u32 unicode_length;
	u32 i;

	अगर (!original_object) अणु
		वापस (AE_OK);
	पूर्ण

	/* If a Buffer was वापसed, it must be at least two bytes दीर्घ */

	अगर (original_object->common.type == ACPI_TYPE_BUFFER) अणु
		अगर (original_object->buffer.length < 2) अणु
			वापस (AE_AML_OPERAND_VALUE);
		पूर्ण

		*वापस_object = शून्य;
		वापस (AE_OK);
	पूर्ण

	/*
	 * The original object is an ASCII string. Convert this string to
	 * a unicode buffer.
	 */
	ascii_string = original_object->string.poपूर्णांकer;
	unicode_length = (original_object->string.length * 2) + 2;

	/* Create a new buffer object क्रम the Unicode data */

	new_object = acpi_ut_create_buffer_object(unicode_length);
	अगर (!new_object) अणु
		वापस (AE_NO_MEMORY);
	पूर्ण

	unicode_buffer = ACPI_CAST_PTR(u16, new_object->buffer.poपूर्णांकer);

	/* Convert ASCII to Unicode */

	क्रम (i = 0; i < original_object->string.length; i++) अणु
		unicode_buffer[i] = (u16)ascii_string[i];
	पूर्ण

	*वापस_object = new_object;
	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_convert_to_resource
 *
 * PARAMETERS:  scope               - Namespace node क्रम the method/object
 *              original_object     - Object to be converted
 *              वापस_object       - Where the new converted object is वापसed
 *
 * RETURN:      Status. AE_OK अगर conversion was successful
 *
 * DESCRIPTION: Attempt to convert a Integer object to a resource_ढाँचा
 *              Buffer.
 *
 ******************************************************************************/

acpi_status
acpi_ns_convert_to_resource(काष्ठा acpi_namespace_node *scope,
			    जोड़ acpi_opeअक्रम_object *original_object,
			    जोड़ acpi_opeअक्रम_object **वापस_object)
अणु
	जोड़ acpi_opeअक्रम_object *new_object;
	u8 *buffer;

	/*
	 * We can fix the following हालs क्रम an expected resource ढाँचा:
	 * 1. No वापस value (पूर्णांकerpreter slack mode is disabled)
	 * 2. A "Return (Zero)" statement
	 * 3. A "Return empty buffer" statement
	 *
	 * We will वापस a buffer containing a single end_tag
	 * resource descriptor.
	 */
	अगर (original_object) अणु
		चयन (original_object->common.type) अणु
		हाल ACPI_TYPE_INTEGER:

			/* We can only repair an Integer==0 */

			अगर (original_object->पूर्णांकeger.value) अणु
				वापस (AE_AML_OPERAND_TYPE);
			पूर्ण
			अवरोध;

		हाल ACPI_TYPE_BUFFER:

			अगर (original_object->buffer.length) अणु

				/* Additional checks can be added in the future */

				*वापस_object = शून्य;
				वापस (AE_OK);
			पूर्ण
			अवरोध;

		हाल ACPI_TYPE_STRING:
		शेष:

			वापस (AE_AML_OPERAND_TYPE);
		पूर्ण
	पूर्ण

	/* Create the new buffer object क्रम the resource descriptor */

	new_object = acpi_ut_create_buffer_object(2);
	अगर (!new_object) अणु
		वापस (AE_NO_MEMORY);
	पूर्ण

	buffer = ACPI_CAST_PTR(u8, new_object->buffer.poपूर्णांकer);

	/* Initialize the Buffer with a single end_tag descriptor */

	buffer[0] = (ACPI_RESOURCE_NAME_END_TAG | ASL_RDESC_END_TAG_SIZE);
	buffer[1] = 0x00;

	*वापस_object = new_object;
	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_convert_to_reference
 *
 * PARAMETERS:  scope               - Namespace node क्रम the method/object
 *              original_object     - Object to be converted
 *              वापस_object       - Where the new converted object is वापसed
 *
 * RETURN:      Status. AE_OK अगर conversion was successful
 *
 * DESCRIPTION: Attempt to convert a Integer object to a object_reference.
 *              Buffer.
 *
 ******************************************************************************/

acpi_status
acpi_ns_convert_to_reference(काष्ठा acpi_namespace_node *scope,
			     जोड़ acpi_opeअक्रम_object *original_object,
			     जोड़ acpi_opeअक्रम_object **वापस_object)
अणु
	जोड़ acpi_opeअक्रम_object *new_object = शून्य;
	acpi_status status;
	काष्ठा acpi_namespace_node *node;
	जोड़ acpi_generic_state scope_info;
	अक्षर *name;

	ACPI_FUNCTION_NAME(ns_convert_to_reference);

	/* Convert path पूर्णांकo पूर्णांकernal presentation */

	status =
	    acpi_ns_पूर्णांकernalize_name(original_object->string.poपूर्णांकer, &name);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Find the namespace node */

	scope_info.scope.node =
	    ACPI_CAST_PTR(काष्ठा acpi_namespace_node, scope);
	status =
	    acpi_ns_lookup(&scope_info, name, ACPI_TYPE_ANY, ACPI_IMODE_EXECUTE,
			   ACPI_NS_SEARCH_PARENT | ACPI_NS_DONT_OPEN_SCOPE,
			   शून्य, &node);
	अगर (ACPI_FAILURE(status)) अणु

		/* Check अगर we are resolving a named reference within a package */

		ACPI_ERROR_NAMESPACE(&scope_info,
				     original_object->string.poपूर्णांकer, status);
		जाओ error_निकास;
	पूर्ण

	/* Create and init a new पूर्णांकernal ACPI object */

	new_object = acpi_ut_create_पूर्णांकernal_object(ACPI_TYPE_LOCAL_REFERENCE);
	अगर (!new_object) अणु
		status = AE_NO_MEMORY;
		जाओ error_निकास;
	पूर्ण
	new_object->reference.node = node;
	new_object->reference.object = node->object;
	new_object->reference.class = ACPI_REFCLASS_NAME;

	/*
	 * Increase reference of the object अगर needed (the object is likely a
	 * null क्रम device nodes).
	 */
	acpi_ut_add_reference(node->object);

error_निकास:
	ACPI_FREE(name);
	*वापस_object = new_object;
	वापस (status);
पूर्ण
