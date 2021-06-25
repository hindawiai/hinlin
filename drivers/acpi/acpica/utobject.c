<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: utobject - ACPI object create/delete/size/cache routines
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश <linux/kmemleak.h>
#समावेश "accommon.h"
#समावेश "acnamesp.h"

#घोषणा _COMPONENT          ACPI_UTILITIES
ACPI_MODULE_NAME("utobject")

/* Local prototypes */
अटल acpi_status
acpi_ut_get_simple_object_size(जोड़ acpi_opeअक्रम_object *obj,
			       acpi_size *obj_length);

अटल acpi_status
acpi_ut_get_package_object_size(जोड़ acpi_opeअक्रम_object *obj,
				acpi_size *obj_length);

अटल acpi_status
acpi_ut_get_element_length(u8 object_type,
			   जोड़ acpi_opeअक्रम_object *source_object,
			   जोड़ acpi_generic_state *state, व्योम *context);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_create_पूर्णांकernal_object_dbg
 *
 * PARAMETERS:  module_name         - Source file name of caller
 *              line_number         - Line number of caller
 *              component_id        - Component type of caller
 *              type                - ACPI Type of the new object
 *
 * RETURN:      A new पूर्णांकernal object, null on failure
 *
 * DESCRIPTION: Create and initialize a new पूर्णांकernal object.
 *
 * NOTE:        We always allocate the worst-हाल object descriptor because
 *              these objects are cached, and we want them to be
 *              one-size-satisfies-any-request. This in itself may not be
 *              the most memory efficient, but the efficiency of the object
 *              cache should more than make up क्रम this!
 *
 ******************************************************************************/

जोड़ acpi_opeअक्रम_object *acpi_ut_create_पूर्णांकernal_object_dbg(स्थिर अक्षर
							      *module_name,
							      u32 line_number,
							      u32 component_id,
							      acpi_object_type
							      type)
अणु
	जोड़ acpi_opeअक्रम_object *object;
	जोड़ acpi_opeअक्रम_object *second_object;

	ACPI_FUNCTION_TRACE_STR(ut_create_पूर्णांकernal_object_dbg,
				acpi_ut_get_type_name(type));

	/* Allocate the raw object descriptor */

	object =
	    acpi_ut_allocate_object_desc_dbg(module_name, line_number,
					     component_id);
	अगर (!object) अणु
		वापस_PTR(शून्य);
	पूर्ण
	kmemleak_not_leak(object);

	चयन (type) अणु
	हाल ACPI_TYPE_REGION:
	हाल ACPI_TYPE_BUFFER_FIELD:
	हाल ACPI_TYPE_LOCAL_BANK_FIELD:

		/* These types require a secondary object */

		second_object =
		    acpi_ut_allocate_object_desc_dbg(module_name, line_number,
						     component_id);
		अगर (!second_object) अणु
			acpi_ut_delete_object_desc(object);
			वापस_PTR(शून्य);
		पूर्ण

		second_object->common.type = ACPI_TYPE_LOCAL_EXTRA;
		second_object->common.reference_count = 1;

		/* Link the second object to the first */

		object->common.next_object = second_object;
		अवरोध;

	शेष:

		/* All others have no secondary object */
		अवरोध;
	पूर्ण

	/* Save the object type in the object descriptor */

	object->common.type = (u8) type;

	/* Init the reference count */

	object->common.reference_count = 1;

	/* Any per-type initialization should go here */

	वापस_PTR(object);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_create_package_object
 *
 * PARAMETERS:  count               - Number of package elements
 *
 * RETURN:      Poपूर्णांकer to a new Package object, null on failure
 *
 * DESCRIPTION: Create a fully initialized package object
 *
 ******************************************************************************/

जोड़ acpi_opeअक्रम_object *acpi_ut_create_package_object(u32 count)
अणु
	जोड़ acpi_opeअक्रम_object *package_desc;
	जोड़ acpi_opeअक्रम_object **package_elements;

	ACPI_FUNCTION_TRACE_U32(ut_create_package_object, count);

	/* Create a new Package object */

	package_desc = acpi_ut_create_पूर्णांकernal_object(ACPI_TYPE_PACKAGE);
	अगर (!package_desc) अणु
		वापस_PTR(शून्य);
	पूर्ण

	/*
	 * Create the element array. Count+1 allows the array to be null
	 * terminated.
	 */
	package_elements = ACPI_ALLOCATE_ZEROED(((acpi_size)count +
						 1) * माप(व्योम *));
	अगर (!package_elements) अणु
		ACPI_FREE(package_desc);
		वापस_PTR(शून्य);
	पूर्ण

	package_desc->package.count = count;
	package_desc->package.elements = package_elements;
	वापस_PTR(package_desc);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_create_पूर्णांकeger_object
 *
 * PARAMETERS:  initial_value       - Initial value क्रम the पूर्णांकeger
 *
 * RETURN:      Poपूर्णांकer to a new Integer object, null on failure
 *
 * DESCRIPTION: Create an initialized पूर्णांकeger object
 *
 ******************************************************************************/

जोड़ acpi_opeअक्रम_object *acpi_ut_create_पूर्णांकeger_object(u64 initial_value)
अणु
	जोड़ acpi_opeअक्रम_object *पूर्णांकeger_desc;

	ACPI_FUNCTION_TRACE(ut_create_पूर्णांकeger_object);

	/* Create and initialize a new पूर्णांकeger object */

	पूर्णांकeger_desc = acpi_ut_create_पूर्णांकernal_object(ACPI_TYPE_INTEGER);
	अगर (!पूर्णांकeger_desc) अणु
		वापस_PTR(शून्य);
	पूर्ण

	पूर्णांकeger_desc->पूर्णांकeger.value = initial_value;
	वापस_PTR(पूर्णांकeger_desc);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_create_buffer_object
 *
 * PARAMETERS:  buffer_size            - Size of buffer to be created
 *
 * RETURN:      Poपूर्णांकer to a new Buffer object, null on failure
 *
 * DESCRIPTION: Create a fully initialized buffer object
 *
 ******************************************************************************/

जोड़ acpi_opeअक्रम_object *acpi_ut_create_buffer_object(acpi_size buffer_size)
अणु
	जोड़ acpi_opeअक्रम_object *buffer_desc;
	u8 *buffer = शून्य;

	ACPI_FUNCTION_TRACE_U32(ut_create_buffer_object, buffer_size);

	/* Create a new Buffer object */

	buffer_desc = acpi_ut_create_पूर्णांकernal_object(ACPI_TYPE_BUFFER);
	अगर (!buffer_desc) अणु
		वापस_PTR(शून्य);
	पूर्ण

	/* Create an actual buffer only अगर size > 0 */

	अगर (buffer_size > 0) अणु

		/* Allocate the actual buffer */

		buffer = ACPI_ALLOCATE_ZEROED(buffer_size);
		अगर (!buffer) अणु
			ACPI_ERROR((AE_INFO, "Could not allocate size %u",
				    (u32)buffer_size));

			acpi_ut_हटाओ_reference(buffer_desc);
			वापस_PTR(शून्य);
		पूर्ण
	पूर्ण

	/* Complete buffer object initialization */

	buffer_desc->buffer.flags |= AOPOBJ_DATA_VALID;
	buffer_desc->buffer.poपूर्णांकer = buffer;
	buffer_desc->buffer.length = (u32) buffer_size;

	/* Return the new buffer descriptor */

	वापस_PTR(buffer_desc);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_create_string_object
 *
 * PARAMETERS:  string_size         - Size of string to be created. Does not
 *                                    include शून्य terminator, this is added
 *                                    स्वतःmatically.
 *
 * RETURN:      Poपूर्णांकer to a new String object
 *
 * DESCRIPTION: Create a fully initialized string object
 *
 ******************************************************************************/

जोड़ acpi_opeअक्रम_object *acpi_ut_create_string_object(acpi_size string_size)
अणु
	जोड़ acpi_opeअक्रम_object *string_desc;
	अक्षर *string;

	ACPI_FUNCTION_TRACE_U32(ut_create_string_object, string_size);

	/* Create a new String object */

	string_desc = acpi_ut_create_पूर्णांकernal_object(ACPI_TYPE_STRING);
	अगर (!string_desc) अणु
		वापस_PTR(शून्य);
	पूर्ण

	/*
	 * Allocate the actual string buffer -- (Size + 1) क्रम शून्य terminator.
	 * NOTE: Zero-length strings are शून्य terminated
	 */
	string = ACPI_ALLOCATE_ZEROED(string_size + 1);
	अगर (!string) अणु
		ACPI_ERROR((AE_INFO, "Could not allocate size %u",
			    (u32)string_size));

		acpi_ut_हटाओ_reference(string_desc);
		वापस_PTR(शून्य);
	पूर्ण

	/* Complete string object initialization */

	string_desc->string.poपूर्णांकer = string;
	string_desc->string.length = (u32) string_size;

	/* Return the new string descriptor */

	वापस_PTR(string_desc);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_valid_पूर्णांकernal_object
 *
 * PARAMETERS:  object              - Object to be validated
 *
 * RETURN:      TRUE अगर object is valid, FALSE otherwise
 *
 * DESCRIPTION: Validate a poपूर्णांकer to be of type जोड़ acpi_opeअक्रम_object
 *
 ******************************************************************************/

u8 acpi_ut_valid_पूर्णांकernal_object(व्योम *object)
अणु

	ACPI_FUNCTION_NAME(ut_valid_पूर्णांकernal_object);

	/* Check क्रम a null poपूर्णांकer */

	अगर (!object) अणु
		ACPI_DEBUG_PRINT((ACPI_DB_EXEC, "**** Null Object Ptr\n"));
		वापस (FALSE);
	पूर्ण

	/* Check the descriptor type field */

	चयन (ACPI_GET_DESCRIPTOR_TYPE(object)) अणु
	हाल ACPI_DESC_TYPE_OPERAND:

		/* The object appears to be a valid जोड़ acpi_opeअक्रम_object */

		वापस (TRUE);

	शेष:

		ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
				  "%p is not an ACPI operand obj [%s]\n",
				  object, acpi_ut_get_descriptor_name(object)));
		अवरोध;
	पूर्ण

	वापस (FALSE);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_allocate_object_desc_dbg
 *
 * PARAMETERS:  module_name         - Caller's module name (क्रम error output)
 *              line_number         - Caller's line number (क्रम error output)
 *              component_id        - Caller's component ID (क्रम error output)
 *
 * RETURN:      Poपूर्णांकer to newly allocated object descriptor. Null on error
 *
 * DESCRIPTION: Allocate a new object descriptor. Gracefully handle
 *              error conditions.
 *
 ******************************************************************************/

व्योम *acpi_ut_allocate_object_desc_dbg(स्थिर अक्षर *module_name,
				       u32 line_number, u32 component_id)
अणु
	जोड़ acpi_opeअक्रम_object *object;

	ACPI_FUNCTION_TRACE(ut_allocate_object_desc_dbg);

	object = acpi_os_acquire_object(acpi_gbl_opeअक्रम_cache);
	अगर (!object) अणु
		ACPI_ERROR((module_name, line_number,
			    "Could not allocate an object descriptor"));

		वापस_PTR(शून्य);
	पूर्ण

	/* Mark the descriptor type */

	ACPI_SET_DESCRIPTOR_TYPE(object, ACPI_DESC_TYPE_OPERAND);

	ACPI_DEBUG_PRINT((ACPI_DB_ALLOCATIONS, "%p Size %X\n",
			  object, (u32) माप(जोड़ acpi_opeअक्रम_object)));

	वापस_PTR(object);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_delete_object_desc
 *
 * PARAMETERS:  object          - An Acpi पूर्णांकernal object to be deleted
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Free an ACPI object descriptor or add it to the object cache
 *
 ******************************************************************************/

व्योम acpi_ut_delete_object_desc(जोड़ acpi_opeअक्रम_object *object)
अणु
	ACPI_FUNCTION_TRACE_PTR(ut_delete_object_desc, object);

	/* Object must be of type जोड़ acpi_opeअक्रम_object */

	अगर (ACPI_GET_DESCRIPTOR_TYPE(object) != ACPI_DESC_TYPE_OPERAND) अणु
		ACPI_ERROR((AE_INFO,
			    "%p is not an ACPI Operand object [%s]", object,
			    acpi_ut_get_descriptor_name(object)));
		वापस_VOID;
	पूर्ण

	(व्योम)acpi_os_release_object(acpi_gbl_opeअक्रम_cache, object);
	वापस_VOID;
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_get_simple_object_size
 *
 * PARAMETERS:  पूर्णांकernal_object    - An ACPI opeअक्रम object
 *              obj_length         - Where the length is वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: This function is called to determine the space required to
 *              contain a simple object क्रम वापस to an बाह्यal user.
 *
 *              The length includes the object काष्ठाure plus any additional
 *              needed space.
 *
 ******************************************************************************/

अटल acpi_status
acpi_ut_get_simple_object_size(जोड़ acpi_opeअक्रम_object *पूर्णांकernal_object,
			       acpi_size *obj_length)
अणु
	acpi_size length;
	acpi_size size;
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TRACE_PTR(ut_get_simple_object_size, पूर्णांकernal_object);

	/* Start with the length of the (बाह्यal) Acpi object */

	length = माप(जोड़ acpi_object);

	/* A शून्य object is allowed, can be a legal uninitialized package element */

	अगर (!पूर्णांकernal_object) अणु
	/*
		 * Object is शून्य, just वापस the length of जोड़ acpi_object
		 * (A शून्य जोड़ acpi_object is an object of all zeroes.)
	 */
		*obj_length = ACPI_ROUND_UP_TO_NATIVE_WORD(length);
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	/* A Namespace Node should never appear here */

	अगर (ACPI_GET_DESCRIPTOR_TYPE(पूर्णांकernal_object) == ACPI_DESC_TYPE_NAMED) अणु

		/* A namespace node should never get here */

		ACPI_ERROR((AE_INFO,
			    "Received a namespace node [%4.4s] "
			    "where an operand object is required",
			    ACPI_CAST_PTR(काष्ठा acpi_namespace_node,
					  पूर्णांकernal_object)->name.ascii));
		वापस_ACPI_STATUS(AE_AML_INTERNAL);
	पूर्ण

	/*
	 * The final length depends on the object type
	 * Strings and Buffers are packed right up against the parent object and
	 * must be accessed bytewise or there may be alignment problems on
	 * certain processors
	 */
	चयन (पूर्णांकernal_object->common.type) अणु
	हाल ACPI_TYPE_STRING:

		length += (acpi_size)पूर्णांकernal_object->string.length + 1;
		अवरोध;

	हाल ACPI_TYPE_BUFFER:

		length += (acpi_size)पूर्णांकernal_object->buffer.length;
		अवरोध;

	हाल ACPI_TYPE_INTEGER:
	हाल ACPI_TYPE_PROCESSOR:
	हाल ACPI_TYPE_POWER:

		/* No extra data क्रम these types */

		अवरोध;

	हाल ACPI_TYPE_LOCAL_REFERENCE:

		चयन (पूर्णांकernal_object->reference.class) अणु
		हाल ACPI_REFCLASS_NAME:
			/*
			 * Get the actual length of the full pathname to this object.
			 * The reference will be converted to the pathname to the object
			 */
			size =
			    acpi_ns_get_pathname_length(पूर्णांकernal_object->
							reference.node);
			अगर (!size) अणु
				वापस_ACPI_STATUS(AE_BAD_PARAMETER);
			पूर्ण

			length += ACPI_ROUND_UP_TO_NATIVE_WORD(size);
			अवरोध;

		शेष:
			/*
			 * No other reference opcodes are supported.
			 * Notably, Locals and Args are not supported, but this may be
			 * required eventually.
			 */
			ACPI_ERROR((AE_INFO,
				    "Cannot convert to external object - "
				    "unsupported Reference Class [%s] 0x%X in object %p",
				    acpi_ut_get_reference_name(पूर्णांकernal_object),
				    पूर्णांकernal_object->reference.class,
				    पूर्णांकernal_object));
			status = AE_TYPE;
			अवरोध;
		पूर्ण
		अवरोध;

	शेष:

		ACPI_ERROR((AE_INFO, "Cannot convert to external object - "
			    "unsupported type [%s] 0x%X in object %p",
			    acpi_ut_get_object_type_name(पूर्णांकernal_object),
			    पूर्णांकernal_object->common.type, पूर्णांकernal_object));
		status = AE_TYPE;
		अवरोध;
	पूर्ण

	/*
	 * Account क्रम the space required by the object rounded up to the next
	 * multiple of the machine word size. This keeps each object aligned
	 * on a machine word boundary. (preventing alignment faults on some
	 * machines.)
	 */
	*obj_length = ACPI_ROUND_UP_TO_NATIVE_WORD(length);
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_get_element_length
 *
 * PARAMETERS:  acpi_pkg_callback
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Get the length of one package element.
 *
 ******************************************************************************/

अटल acpi_status
acpi_ut_get_element_length(u8 object_type,
			   जोड़ acpi_opeअक्रम_object *source_object,
			   जोड़ acpi_generic_state *state, व्योम *context)
अणु
	acpi_status status = AE_OK;
	काष्ठा acpi_pkg_info *info = (काष्ठा acpi_pkg_info *)context;
	acpi_size object_space;

	चयन (object_type) अणु
	हाल ACPI_COPY_TYPE_SIMPLE:
		/*
		 * Simple object - just get the size (Null object/entry is handled
		 * here also) and sum it पूर्णांकo the running package length
		 */
		status =
		    acpi_ut_get_simple_object_size(source_object,
						   &object_space);
		अगर (ACPI_FAILURE(status)) अणु
			वापस (status);
		पूर्ण

		info->length += object_space;
		अवरोध;

	हाल ACPI_COPY_TYPE_PACKAGE:

		/* Package object - nothing much to करो here, let the walk handle it */

		info->num_packages++;
		state->pkg.this_target_obj = शून्य;
		अवरोध;

	शेष:

		/* No other types allowed */

		वापस (AE_BAD_PARAMETER);
	पूर्ण

	वापस (status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_get_package_object_size
 *
 * PARAMETERS:  पूर्णांकernal_object     - An ACPI पूर्णांकernal object
 *              obj_length          - Where the length is वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: This function is called to determine the space required to
 *              contain a package object क्रम वापस to an बाह्यal user.
 *
 *              This is moderately complex since a package contains other
 *              objects including packages.
 *
 ******************************************************************************/

अटल acpi_status
acpi_ut_get_package_object_size(जोड़ acpi_opeअक्रम_object *पूर्णांकernal_object,
				acpi_size *obj_length)
अणु
	acpi_status status;
	काष्ठा acpi_pkg_info info;

	ACPI_FUNCTION_TRACE_PTR(ut_get_package_object_size, पूर्णांकernal_object);

	info.length = 0;
	info.object_space = 0;
	info.num_packages = 1;

	status =
	    acpi_ut_walk_package_tree(पूर्णांकernal_object, शून्य,
				      acpi_ut_get_element_length, &info);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/*
	 * We have handled all of the objects in all levels of the package.
	 * just add the length of the package objects themselves.
	 * Round up to the next machine word.
	 */
	info.length +=
	    ACPI_ROUND_UP_TO_NATIVE_WORD(माप(जोड़ acpi_object)) *
	    (acpi_size)info.num_packages;

	/* Return the total package length */

	*obj_length = info.length;
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_get_object_size
 *
 * PARAMETERS:  पूर्णांकernal_object     - An ACPI पूर्णांकernal object
 *              obj_length          - Where the length will be वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: This function is called to determine the space required to
 *              contain an object क्रम वापस to an API user.
 *
 ******************************************************************************/

acpi_status
acpi_ut_get_object_size(जोड़ acpi_opeअक्रम_object *पूर्णांकernal_object,
			acpi_size *obj_length)
अणु
	acpi_status status;

	ACPI_FUNCTION_ENTRY();

	अगर ((ACPI_GET_DESCRIPTOR_TYPE(पूर्णांकernal_object) ==
	     ACPI_DESC_TYPE_OPERAND) &&
	    (पूर्णांकernal_object->common.type == ACPI_TYPE_PACKAGE)) अणु
		status =
		    acpi_ut_get_package_object_size(पूर्णांकernal_object,
						    obj_length);
	पूर्ण अन्यथा अणु
		status =
		    acpi_ut_get_simple_object_size(पूर्णांकernal_object, obj_length);
	पूर्ण

	वापस (status);
पूर्ण
