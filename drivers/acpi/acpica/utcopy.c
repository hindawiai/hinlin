<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: utcopy - Internal to बाह्यal object translation utilities
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acnamesp.h"


#घोषणा _COMPONENT          ACPI_UTILITIES
ACPI_MODULE_NAME("utcopy")

/* Local prototypes */
अटल acpi_status
acpi_ut_copy_isimple_to_esimple(जोड़ acpi_opeअक्रम_object *पूर्णांकernal_object,
				जोड़ acpi_object *बाह्यal_object,
				u8 *data_space, acpi_size *buffer_space_used);

अटल acpi_status
acpi_ut_copy_ielement_to_ielement(u8 object_type,
				  जोड़ acpi_opeअक्रम_object *source_object,
				  जोड़ acpi_generic_state *state,
				  व्योम *context);

अटल acpi_status
acpi_ut_copy_ipackage_to_epackage(जोड़ acpi_opeअक्रम_object *पूर्णांकernal_object,
				  u8 *buffer, acpi_size *space_used);

अटल acpi_status
acpi_ut_copy_esimple_to_isimple(जोड़ acpi_object *user_obj,
				जोड़ acpi_opeअक्रम_object **वापस_obj);

अटल acpi_status
acpi_ut_copy_epackage_to_ipackage(जोड़ acpi_object *बाह्यal_object,
				  जोड़ acpi_opeअक्रम_object **पूर्णांकernal_object);

अटल acpi_status
acpi_ut_copy_simple_object(जोड़ acpi_opeअक्रम_object *source_desc,
			   जोड़ acpi_opeअक्रम_object *dest_desc);

अटल acpi_status
acpi_ut_copy_ielement_to_eelement(u8 object_type,
				  जोड़ acpi_opeअक्रम_object *source_object,
				  जोड़ acpi_generic_state *state,
				  व्योम *context);

अटल acpi_status
acpi_ut_copy_ipackage_to_ipackage(जोड़ acpi_opeअक्रम_object *source_obj,
				  जोड़ acpi_opeअक्रम_object *dest_obj,
				  काष्ठा acpi_walk_state *walk_state);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_copy_isimple_to_esimple
 *
 * PARAMETERS:  पूर्णांकernal_object     - Source object to be copied
 *              बाह्यal_object     - Where to वापस the copied object
 *              data_space          - Where object data is वापसed (such as
 *                                    buffer and string data)
 *              buffer_space_used   - Length of data_space that was used
 *
 * RETURN:      Status
 *
 * DESCRIPTION: This function is called to copy a simple पूर्णांकernal object to
 *              an बाह्यal object.
 *
 *              The data_space buffer is assumed to have sufficient space क्रम
 *              the object.
 *
 ******************************************************************************/

अटल acpi_status
acpi_ut_copy_isimple_to_esimple(जोड़ acpi_opeअक्रम_object *पूर्णांकernal_object,
				जोड़ acpi_object *बाह्यal_object,
				u8 *data_space, acpi_size *buffer_space_used)
अणु
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TRACE(ut_copy_isimple_to_esimple);

	*buffer_space_used = 0;

	/*
	 * Check क्रम शून्य object हाल (could be an uninitialized
	 * package element)
	 */
	अगर (!पूर्णांकernal_object) अणु
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	/* Always clear the बाह्यal object */

	स_रखो(बाह्यal_object, 0, माप(जोड़ acpi_object));

	/*
	 * In general, the बाह्यal object will be the same type as
	 * the पूर्णांकernal object
	 */
	बाह्यal_object->type = पूर्णांकernal_object->common.type;

	/* However, only a limited number of बाह्यal types are supported */

	चयन (पूर्णांकernal_object->common.type) अणु
	हाल ACPI_TYPE_STRING:

		बाह्यal_object->string.poपूर्णांकer = (अक्षर *)data_space;
		बाह्यal_object->string.length = पूर्णांकernal_object->string.length;
		*buffer_space_used = ACPI_ROUND_UP_TO_NATIVE_WORD((acpi_size)
								  पूर्णांकernal_object->
								  string.
								  length + 1);

		स_नकल((व्योम *)data_space,
		       (व्योम *)पूर्णांकernal_object->string.poपूर्णांकer,
		       (acpi_size)पूर्णांकernal_object->string.length + 1);
		अवरोध;

	हाल ACPI_TYPE_BUFFER:

		बाह्यal_object->buffer.poपूर्णांकer = data_space;
		बाह्यal_object->buffer.length = पूर्णांकernal_object->buffer.length;
		*buffer_space_used =
		    ACPI_ROUND_UP_TO_NATIVE_WORD(पूर्णांकernal_object->string.
						 length);

		स_नकल((व्योम *)data_space,
		       (व्योम *)पूर्णांकernal_object->buffer.poपूर्णांकer,
		       पूर्णांकernal_object->buffer.length);
		अवरोध;

	हाल ACPI_TYPE_INTEGER:

		बाह्यal_object->पूर्णांकeger.value = पूर्णांकernal_object->पूर्णांकeger.value;
		अवरोध;

	हाल ACPI_TYPE_LOCAL_REFERENCE:

		/* This is an object reference. */

		चयन (पूर्णांकernal_object->reference.class) अणु
		हाल ACPI_REFCLASS_NAME:
			/*
			 * For namepath, वापस the object handle ("reference")
			 * We are referring to the namespace node
			 */
			बाह्यal_object->reference.handle =
			    पूर्णांकernal_object->reference.node;
			बाह्यal_object->reference.actual_type =
			    acpi_ns_get_type(पूर्णांकernal_object->reference.node);
			अवरोध;

		शेष:

			/* All other reference types are unsupported */

			वापस_ACPI_STATUS(AE_TYPE);
		पूर्ण
		अवरोध;

	हाल ACPI_TYPE_PROCESSOR:

		बाह्यal_object->processor.proc_id =
		    पूर्णांकernal_object->processor.proc_id;
		बाह्यal_object->processor.pblk_address =
		    पूर्णांकernal_object->processor.address;
		बाह्यal_object->processor.pblk_length =
		    पूर्णांकernal_object->processor.length;
		अवरोध;

	हाल ACPI_TYPE_POWER:

		बाह्यal_object->घातer_resource.प्रणाली_level =
		    पूर्णांकernal_object->घातer_resource.प्रणाली_level;

		बाह्यal_object->घातer_resource.resource_order =
		    पूर्णांकernal_object->घातer_resource.resource_order;
		अवरोध;

	शेष:
		/*
		 * There is no corresponding बाह्यal object type
		 */
		ACPI_ERROR((AE_INFO,
			    "Unsupported object type, cannot convert to external object: %s",
			    acpi_ut_get_type_name(पूर्णांकernal_object->common.
						  type)));

		वापस_ACPI_STATUS(AE_SUPPORT);
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_copy_ielement_to_eelement
 *
 * PARAMETERS:  acpi_pkg_callback
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Copy one package element to another package element
 *
 ******************************************************************************/

अटल acpi_status
acpi_ut_copy_ielement_to_eelement(u8 object_type,
				  जोड़ acpi_opeअक्रम_object *source_object,
				  जोड़ acpi_generic_state *state,
				  व्योम *context)
अणु
	acpi_status status = AE_OK;
	काष्ठा acpi_pkg_info *info = (काष्ठा acpi_pkg_info *)context;
	acpi_size object_space;
	u32 this_index;
	जोड़ acpi_object *target_object;

	ACPI_FUNCTION_ENTRY();

	this_index = state->pkg.index;
	target_object = (जोड़ acpi_object *)&((जोड़ acpi_object *)
					       (state->pkg.dest_object))->
	    package.elements[this_index];

	चयन (object_type) अणु
	हाल ACPI_COPY_TYPE_SIMPLE:
		/*
		 * This is a simple or null object
		 */
		status = acpi_ut_copy_isimple_to_esimple(source_object,
							 target_object,
							 info->मुक्त_space,
							 &object_space);
		अगर (ACPI_FAILURE(status)) अणु
			वापस (status);
		पूर्ण
		अवरोध;

	हाल ACPI_COPY_TYPE_PACKAGE:
		/*
		 * Build the package object
		 */
		target_object->type = ACPI_TYPE_PACKAGE;
		target_object->package.count = source_object->package.count;
		target_object->package.elements =
		    ACPI_CAST_PTR(जोड़ acpi_object, info->मुक्त_space);

		/*
		 * Pass the new package object back to the package walk routine
		 */
		state->pkg.this_target_obj = target_object;

		/*
		 * Save space क्रम the array of objects (Package elements)
		 * update the buffer length counter
		 */
		object_space = ACPI_ROUND_UP_TO_NATIVE_WORD((acpi_size)
							    target_object->
							    package.count *
							    माप(जोड़
								   acpi_object));
		अवरोध;

	शेष:

		वापस (AE_BAD_PARAMETER);
	पूर्ण

	info->मुक्त_space += object_space;
	info->length += object_space;
	वापस (status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_copy_ipackage_to_epackage
 *
 * PARAMETERS:  पूर्णांकernal_object     - Poपूर्णांकer to the object we are वापसing
 *              buffer              - Where the object is वापसed
 *              space_used          - Where the object length is वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: This function is called to place a package object in a user
 *              buffer. A package object by definition contains other objects.
 *
 *              The buffer is assumed to have sufficient space क्रम the object.
 *              The caller must have verअगरied the buffer length needed using
 *              the acpi_ut_get_object_size function beक्रमe calling this function.
 *
 ******************************************************************************/

अटल acpi_status
acpi_ut_copy_ipackage_to_epackage(जोड़ acpi_opeअक्रम_object *पूर्णांकernal_object,
				  u8 *buffer, acpi_size *space_used)
अणु
	जोड़ acpi_object *बाह्यal_object;
	acpi_status status;
	काष्ठा acpi_pkg_info info;

	ACPI_FUNCTION_TRACE(ut_copy_ipackage_to_epackage);

	/*
	 * First package at head of the buffer
	 */
	बाह्यal_object = ACPI_CAST_PTR(जोड़ acpi_object, buffer);

	/*
	 * Free space begins right after the first package
	 */
	info.length = ACPI_ROUND_UP_TO_NATIVE_WORD(माप(जोड़ acpi_object));
	info.मुक्त_space = buffer +
	    ACPI_ROUND_UP_TO_NATIVE_WORD(माप(जोड़ acpi_object));
	info.object_space = 0;
	info.num_packages = 1;

	बाह्यal_object->type = पूर्णांकernal_object->common.type;
	बाह्यal_object->package.count = पूर्णांकernal_object->package.count;
	बाह्यal_object->package.elements =
	    ACPI_CAST_PTR(जोड़ acpi_object, info.मुक्त_space);

	/*
	 * Leave room क्रम an array of ACPI_OBJECTS in the buffer
	 * and move the मुक्त space past it
	 */
	info.length += (acpi_size)बाह्यal_object->package.count *
	    ACPI_ROUND_UP_TO_NATIVE_WORD(माप(जोड़ acpi_object));
	info.मुक्त_space += बाह्यal_object->package.count *
	    ACPI_ROUND_UP_TO_NATIVE_WORD(माप(जोड़ acpi_object));

	status = acpi_ut_walk_package_tree(पूर्णांकernal_object, बाह्यal_object,
					   acpi_ut_copy_ielement_to_eelement,
					   &info);

	*space_used = info.length;
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_copy_iobject_to_eobject
 *
 * PARAMETERS:  पूर्णांकernal_object     - The पूर्णांकernal object to be converted
 *              ret_buffer          - Where the object is वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: This function is called to build an API object to be वापसed
 *              to the caller.
 *
 ******************************************************************************/

acpi_status
acpi_ut_copy_iobject_to_eobject(जोड़ acpi_opeअक्रम_object *पूर्णांकernal_object,
				काष्ठा acpi_buffer *ret_buffer)
अणु
	acpi_status status;

	ACPI_FUNCTION_TRACE(ut_copy_iobject_to_eobject);

	अगर (पूर्णांकernal_object->common.type == ACPI_TYPE_PACKAGE) अणु
		/*
		 * Package object:  Copy all subobjects (including
		 * nested packages)
		 */
		status = acpi_ut_copy_ipackage_to_epackage(पूर्णांकernal_object,
							   ret_buffer->poपूर्णांकer,
							   &ret_buffer->length);
	पूर्ण अन्यथा अणु
		/*
		 * Build a simple object (no nested objects)
		 */
		status = acpi_ut_copy_isimple_to_esimple(पूर्णांकernal_object,
							 ACPI_CAST_PTR(जोड़
								       acpi_object,
								       ret_buffer->
								       poपूर्णांकer),
							 ACPI_ADD_PTR(u8,
								      ret_buffer->
								      poपूर्णांकer,
								      ACPI_ROUND_UP_TO_NATIVE_WORD
								      (माप
								       (जोड़
									acpi_object))),
							 &ret_buffer->length);
		/*
		 * build simple करोes not include the object size in the length
		 * so we add it in here
		 */
		ret_buffer->length += माप(जोड़ acpi_object);
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_copy_esimple_to_isimple
 *
 * PARAMETERS:  बाह्यal_object     - The बाह्यal object to be converted
 *              ret_पूर्णांकernal_object - Where the पूर्णांकernal object is वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: This function copies an बाह्यal object to an पूर्णांकernal one.
 *              NOTE: Poपूर्णांकers can be copied, we करोn't need to copy data.
 *              (The poपूर्णांकers have to be valid in our address space no matter
 *              what we करो with them!)
 *
 ******************************************************************************/

अटल acpi_status
acpi_ut_copy_esimple_to_isimple(जोड़ acpi_object *बाह्यal_object,
				जोड़ acpi_opeअक्रम_object **ret_पूर्णांकernal_object)
अणु
	जोड़ acpi_opeअक्रम_object *पूर्णांकernal_object;

	ACPI_FUNCTION_TRACE(ut_copy_esimple_to_isimple);

	/*
	 * Simple types supported are: String, Buffer, Integer
	 */
	चयन (बाह्यal_object->type) अणु
	हाल ACPI_TYPE_STRING:
	हाल ACPI_TYPE_BUFFER:
	हाल ACPI_TYPE_INTEGER:
	हाल ACPI_TYPE_LOCAL_REFERENCE:

		पूर्णांकernal_object = acpi_ut_create_पूर्णांकernal_object((u8)
								 बाह्यal_object->
								 type);
		अगर (!पूर्णांकernal_object) अणु
			वापस_ACPI_STATUS(AE_NO_MEMORY);
		पूर्ण
		अवरोध;

	हाल ACPI_TYPE_ANY:	/* This is the हाल क्रम a शून्य object */

		*ret_पूर्णांकernal_object = शून्य;
		वापस_ACPI_STATUS(AE_OK);

	शेष:

		/* All other types are not supported */

		ACPI_ERROR((AE_INFO,
			    "Unsupported object type, cannot convert to internal object: %s",
			    acpi_ut_get_type_name(बाह्यal_object->type)));

		वापस_ACPI_STATUS(AE_SUPPORT);
	पूर्ण

	/* Must COPY string and buffer contents */

	चयन (बाह्यal_object->type) अणु
	हाल ACPI_TYPE_STRING:

		पूर्णांकernal_object->string.poपूर्णांकer =
		    ACPI_ALLOCATE_ZEROED((acpi_size)
					 बाह्यal_object->string.length + 1);

		अगर (!पूर्णांकernal_object->string.poपूर्णांकer) अणु
			जाओ error_निकास;
		पूर्ण

		स_नकल(पूर्णांकernal_object->string.poपूर्णांकer,
		       बाह्यal_object->string.poपूर्णांकer,
		       बाह्यal_object->string.length);

		पूर्णांकernal_object->string.length = बाह्यal_object->string.length;
		अवरोध;

	हाल ACPI_TYPE_BUFFER:

		पूर्णांकernal_object->buffer.poपूर्णांकer =
		    ACPI_ALLOCATE_ZEROED(बाह्यal_object->buffer.length);
		अगर (!पूर्णांकernal_object->buffer.poपूर्णांकer) अणु
			जाओ error_निकास;
		पूर्ण

		स_नकल(पूर्णांकernal_object->buffer.poपूर्णांकer,
		       बाह्यal_object->buffer.poपूर्णांकer,
		       बाह्यal_object->buffer.length);

		पूर्णांकernal_object->buffer.length = बाह्यal_object->buffer.length;

		/* Mark buffer data valid */

		पूर्णांकernal_object->buffer.flags |= AOPOBJ_DATA_VALID;
		अवरोध;

	हाल ACPI_TYPE_INTEGER:

		पूर्णांकernal_object->पूर्णांकeger.value = बाह्यal_object->पूर्णांकeger.value;
		अवरोध;

	हाल ACPI_TYPE_LOCAL_REFERENCE:

		/* An incoming reference is defined to be a namespace node */

		पूर्णांकernal_object->reference.class = ACPI_REFCLASS_REFOF;
		पूर्णांकernal_object->reference.object =
		    बाह्यal_object->reference.handle;
		अवरोध;

	शेष:

		/* Other types can't get here */

		अवरोध;
	पूर्ण

	*ret_पूर्णांकernal_object = पूर्णांकernal_object;
	वापस_ACPI_STATUS(AE_OK);

error_निकास:
	acpi_ut_हटाओ_reference(पूर्णांकernal_object);
	वापस_ACPI_STATUS(AE_NO_MEMORY);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_copy_epackage_to_ipackage
 *
 * PARAMETERS:  बाह्यal_object     - The बाह्यal object to be converted
 *              पूर्णांकernal_object     - Where the पूर्णांकernal object is वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Copy an बाह्यal package object to an पूर्णांकernal package.
 *              Handles nested packages.
 *
 ******************************************************************************/

अटल acpi_status
acpi_ut_copy_epackage_to_ipackage(जोड़ acpi_object *बाह्यal_object,
				  जोड़ acpi_opeअक्रम_object **पूर्णांकernal_object)
अणु
	acpi_status status = AE_OK;
	जोड़ acpi_opeअक्रम_object *package_object;
	जोड़ acpi_opeअक्रम_object **package_elements;
	u32 i;

	ACPI_FUNCTION_TRACE(ut_copy_epackage_to_ipackage);

	/* Create the package object */

	package_object =
	    acpi_ut_create_package_object(बाह्यal_object->package.count);
	अगर (!package_object) अणु
		वापस_ACPI_STATUS(AE_NO_MEMORY);
	पूर्ण

	package_elements = package_object->package.elements;

	/*
	 * Recursive implementation. Probably ok, since nested बाह्यal
	 * packages as parameters should be very rare.
	 */
	क्रम (i = 0; i < बाह्यal_object->package.count; i++) अणु
		status =
		    acpi_ut_copy_eobject_to_iobject(&बाह्यal_object->package.
						    elements[i],
						    &package_elements[i]);
		अगर (ACPI_FAILURE(status)) अणु

			/* Truncate package and delete it */

			package_object->package.count = i;
			package_elements[i] = शून्य;
			acpi_ut_हटाओ_reference(package_object);
			वापस_ACPI_STATUS(status);
		पूर्ण
	पूर्ण

	/* Mark package data valid */

	package_object->package.flags |= AOPOBJ_DATA_VALID;

	*पूर्णांकernal_object = package_object;
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_copy_eobject_to_iobject
 *
 * PARAMETERS:  बाह्यal_object     - The बाह्यal object to be converted
 *              पूर्णांकernal_object     - Where the पूर्णांकernal object is वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Converts an बाह्यal object to an पूर्णांकernal object.
 *
 ******************************************************************************/

acpi_status
acpi_ut_copy_eobject_to_iobject(जोड़ acpi_object *बाह्यal_object,
				जोड़ acpi_opeअक्रम_object **पूर्णांकernal_object)
अणु
	acpi_status status;

	ACPI_FUNCTION_TRACE(ut_copy_eobject_to_iobject);

	अगर (बाह्यal_object->type == ACPI_TYPE_PACKAGE) अणु
		status =
		    acpi_ut_copy_epackage_to_ipackage(बाह्यal_object,
						      पूर्णांकernal_object);
	पूर्ण अन्यथा अणु
		/*
		 * Build a simple object (no nested objects)
		 */
		status = acpi_ut_copy_esimple_to_isimple(बाह्यal_object,
							 पूर्णांकernal_object);
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_copy_simple_object
 *
 * PARAMETERS:  source_desc         - The पूर्णांकernal object to be copied
 *              dest_desc           - New target object
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Simple copy of one पूर्णांकernal object to another. Reference count
 *              of the destination object is preserved.
 *
 ******************************************************************************/

अटल acpi_status
acpi_ut_copy_simple_object(जोड़ acpi_opeअक्रम_object *source_desc,
			   जोड़ acpi_opeअक्रम_object *dest_desc)
अणु
	u16 reference_count;
	जोड़ acpi_opeअक्रम_object *next_object;
	acpi_status status;
	acpi_size copy_size;

	/* Save fields from destination that we करोn't want to overग_लिखो */

	reference_count = dest_desc->common.reference_count;
	next_object = dest_desc->common.next_object;

	/*
	 * Copy the entire source object over the destination object.
	 * Note: Source can be either an opeअक्रम object or namespace node.
	 */
	copy_size = माप(जोड़ acpi_opeअक्रम_object);
	अगर (ACPI_GET_DESCRIPTOR_TYPE(source_desc) == ACPI_DESC_TYPE_NAMED) अणु
		copy_size = माप(काष्ठा acpi_namespace_node);
	पूर्ण

	स_नकल(ACPI_CAST_PTR(अक्षर, dest_desc),
	       ACPI_CAST_PTR(अक्षर, source_desc), copy_size);

	/* Restore the saved fields */

	dest_desc->common.reference_count = reference_count;
	dest_desc->common.next_object = next_object;

	/* New object is not अटल, regardless of source */

	dest_desc->common.flags &= ~AOPOBJ_STATIC_POINTER;

	/* Handle the objects with extra data */

	चयन (dest_desc->common.type) अणु
	हाल ACPI_TYPE_BUFFER:
		/*
		 * Allocate and copy the actual buffer अगर and only अगर:
		 * 1) There is a valid buffer poपूर्णांकer
		 * 2) The buffer has a length > 0
		 */
		अगर ((source_desc->buffer.poपूर्णांकer) &&
		    (source_desc->buffer.length)) अणु
			dest_desc->buffer.poपूर्णांकer =
			    ACPI_ALLOCATE(source_desc->buffer.length);
			अगर (!dest_desc->buffer.poपूर्णांकer) अणु
				वापस (AE_NO_MEMORY);
			पूर्ण

			/* Copy the actual buffer data */

			स_नकल(dest_desc->buffer.poपूर्णांकer,
			       source_desc->buffer.poपूर्णांकer,
			       source_desc->buffer.length);
		पूर्ण
		अवरोध;

	हाल ACPI_TYPE_STRING:
		/*
		 * Allocate and copy the actual string अगर and only अगर:
		 * 1) There is a valid string poपूर्णांकer
		 * (Poपूर्णांकer to a शून्य string is allowed)
		 */
		अगर (source_desc->string.poपूर्णांकer) अणु
			dest_desc->string.poपूर्णांकer =
			    ACPI_ALLOCATE((acpi_size)source_desc->string.
					  length + 1);
			अगर (!dest_desc->string.poपूर्णांकer) अणु
				वापस (AE_NO_MEMORY);
			पूर्ण

			/* Copy the actual string data */

			स_नकल(dest_desc->string.poपूर्णांकer,
			       source_desc->string.poपूर्णांकer,
			       (acpi_size)source_desc->string.length + 1);
		पूर्ण
		अवरोध;

	हाल ACPI_TYPE_LOCAL_REFERENCE:
		/*
		 * We copied the reference object, so we now must add a reference
		 * to the object poपूर्णांकed to by the reference
		 *
		 * DDBHandle reference (from Load/load_table) is a special reference,
		 * it करोes not have a Reference.Object, so करोes not need to
		 * increase the reference count
		 */
		अगर (source_desc->reference.class == ACPI_REFCLASS_TABLE) अणु
			अवरोध;
		पूर्ण

		acpi_ut_add_reference(source_desc->reference.object);
		अवरोध;

	हाल ACPI_TYPE_REGION:
		/*
		 * We copied the Region Handler, so we now must add a reference
		 */
		अगर (dest_desc->region.handler) अणु
			acpi_ut_add_reference(dest_desc->region.handler);
		पूर्ण
		अवरोध;

		/*
		 * For Mutex and Event objects, we cannot simply copy the underlying
		 * OS object. We must create a new one.
		 */
	हाल ACPI_TYPE_MUTEX:

		status = acpi_os_create_mutex(&dest_desc->mutex.os_mutex);
		अगर (ACPI_FAILURE(status)) अणु
			वापस (status);
		पूर्ण
		अवरोध;

	हाल ACPI_TYPE_EVENT:

		status = acpi_os_create_semaphore(ACPI_NO_UNIT_LIMIT, 0,
						  &dest_desc->event.
						  os_semaphore);
		अगर (ACPI_FAILURE(status)) अणु
			वापस (status);
		पूर्ण
		अवरोध;

	शेष:

		/* Nothing to करो क्रम other simple objects */

		अवरोध;
	पूर्ण

	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_copy_ielement_to_ielement
 *
 * PARAMETERS:  acpi_pkg_callback
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Copy one package element to another package element
 *
 ******************************************************************************/

अटल acpi_status
acpi_ut_copy_ielement_to_ielement(u8 object_type,
				  जोड़ acpi_opeअक्रम_object *source_object,
				  जोड़ acpi_generic_state *state,
				  व्योम *context)
अणु
	acpi_status status = AE_OK;
	u32 this_index;
	जोड़ acpi_opeअक्रम_object **this_target_ptr;
	जोड़ acpi_opeअक्रम_object *target_object;

	ACPI_FUNCTION_ENTRY();

	this_index = state->pkg.index;
	this_target_ptr = (जोड़ acpi_opeअक्रम_object **)
	    &state->pkg.dest_object->package.elements[this_index];

	चयन (object_type) अणु
	हाल ACPI_COPY_TYPE_SIMPLE:

		/* A null source object indicates a (legal) null package element */

		अगर (source_object) अणु
			/*
			 * This is a simple object, just copy it
			 */
			target_object =
			    acpi_ut_create_पूर्णांकernal_object(source_object->
							   common.type);
			अगर (!target_object) अणु
				वापस (AE_NO_MEMORY);
			पूर्ण

			status =
			    acpi_ut_copy_simple_object(source_object,
						       target_object);
			अगर (ACPI_FAILURE(status)) अणु
				जाओ error_निकास;
			पूर्ण

			*this_target_ptr = target_object;
		पूर्ण अन्यथा अणु
			/* Pass through a null element */

			*this_target_ptr = शून्य;
		पूर्ण
		अवरोध;

	हाल ACPI_COPY_TYPE_PACKAGE:
		/*
		 * This object is a package - go करोwn another nesting level
		 * Create and build the package object
		 */
		target_object =
		    acpi_ut_create_package_object(source_object->package.count);
		अगर (!target_object) अणु
			वापस (AE_NO_MEMORY);
		पूर्ण

		target_object->common.flags = source_object->common.flags;

		/* Pass the new package object back to the package walk routine */

		state->pkg.this_target_obj = target_object;

		/* Store the object poपूर्णांकer in the parent package object */

		*this_target_ptr = target_object;
		अवरोध;

	शेष:

		वापस (AE_BAD_PARAMETER);
	पूर्ण

	वापस (status);

error_निकास:
	acpi_ut_हटाओ_reference(target_object);
	वापस (status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_copy_ipackage_to_ipackage
 *
 * PARAMETERS:  source_obj      - Poपूर्णांकer to the source package object
 *              dest_obj        - Where the पूर्णांकernal object is वापसed
 *              walk_state      - Current Walk state descriptor
 *
 * RETURN:      Status
 *
 * DESCRIPTION: This function is called to copy an पूर्णांकernal package object
 *              पूर्णांकo another पूर्णांकernal package object.
 *
 ******************************************************************************/

अटल acpi_status
acpi_ut_copy_ipackage_to_ipackage(जोड़ acpi_opeअक्रम_object *source_obj,
				  जोड़ acpi_opeअक्रम_object *dest_obj,
				  काष्ठा acpi_walk_state *walk_state)
अणु
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TRACE(ut_copy_ipackage_to_ipackage);

	dest_obj->common.type = source_obj->common.type;
	dest_obj->common.flags = source_obj->common.flags;
	dest_obj->package.count = source_obj->package.count;

	/*
	 * Create the object array and walk the source package tree
	 */
	dest_obj->package.elements = ACPI_ALLOCATE_ZEROED(((acpi_size)
							   source_obj->package.
							   count +
							   1) * माप(व्योम *));
	अगर (!dest_obj->package.elements) अणु
		ACPI_ERROR((AE_INFO, "Package allocation failure"));
		वापस_ACPI_STATUS(AE_NO_MEMORY);
	पूर्ण

	/*
	 * Copy the package element-by-element by walking the package "tree".
	 * This handles nested packages of arbitrary depth.
	 */
	status = acpi_ut_walk_package_tree(source_obj, dest_obj,
					   acpi_ut_copy_ielement_to_ielement,
					   walk_state);
	अगर (ACPI_FAILURE(status)) अणु

		/* On failure, delete the destination package object */

		acpi_ut_हटाओ_reference(dest_obj);
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_copy_iobject_to_iobject
 *
 * PARAMETERS:  source_desc         - The पूर्णांकernal object to be copied
 *              dest_desc           - Where the copied object is वापसed
 *              walk_state          - Current walk state
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Copy an पूर्णांकernal object to a new पूर्णांकernal object
 *
 ******************************************************************************/

acpi_status
acpi_ut_copy_iobject_to_iobject(जोड़ acpi_opeअक्रम_object *source_desc,
				जोड़ acpi_opeअक्रम_object **dest_desc,
				काष्ठा acpi_walk_state *walk_state)
अणु
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TRACE(ut_copy_iobject_to_iobject);

	/* Create the top level object */

	*dest_desc = acpi_ut_create_पूर्णांकernal_object(source_desc->common.type);
	अगर (!*dest_desc) अणु
		वापस_ACPI_STATUS(AE_NO_MEMORY);
	पूर्ण

	/* Copy the object and possible subobjects */

	अगर (source_desc->common.type == ACPI_TYPE_PACKAGE) अणु
		status =
		    acpi_ut_copy_ipackage_to_ipackage(source_desc, *dest_desc,
						      walk_state);
	पूर्ण अन्यथा अणु
		status = acpi_ut_copy_simple_object(source_desc, *dest_desc);
	पूर्ण

	/* Delete the allocated object अगर copy failed */

	अगर (ACPI_FAILURE(status)) अणु
		acpi_ut_हटाओ_reference(*dest_desc);
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण
