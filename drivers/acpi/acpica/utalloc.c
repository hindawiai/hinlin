<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: utalloc - local memory allocation routines
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acdebug.h"

#घोषणा _COMPONENT          ACPI_UTILITIES
ACPI_MODULE_NAME("utalloc")

#अगर !defined (USE_NATIVE_ALLOCATE_ZEROED)
/*******************************************************************************
 *
 * FUNCTION:    acpi_os_allocate_zeroed
 *
 * PARAMETERS:  size                - Size of the allocation
 *
 * RETURN:      Address of the allocated memory on success, शून्य on failure.
 *
 * DESCRIPTION: Subप्रणाली equivalent of सुस्मृति. Allocate and zero memory.
 *              This is the शेष implementation. Can be overridden via the
 *              USE_NATIVE_ALLOCATE_ZEROED flag.
 *
 ******************************************************************************/
व्योम *acpi_os_allocate_zeroed(acpi_size size)
अणु
	व्योम *allocation;

	ACPI_FUNCTION_ENTRY();

	allocation = acpi_os_allocate(size);
	अगर (allocation) अणु

		/* Clear the memory block */

		स_रखो(allocation, 0, size);
	पूर्ण

	वापस (allocation);
पूर्ण

#पूर्ण_अगर				/* !USE_NATIVE_ALLOCATE_ZEROED */

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_create_caches
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Create all local caches
 *
 ******************************************************************************/

acpi_status acpi_ut_create_caches(व्योम)
अणु
	acpi_status status;

	/* Object Caches, क्रम frequently used objects */

	status =
	    acpi_os_create_cache("Acpi-Namespace",
				 माप(काष्ठा acpi_namespace_node),
				 ACPI_MAX_NAMESPACE_CACHE_DEPTH,
				 &acpi_gbl_namespace_cache);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	status =
	    acpi_os_create_cache("Acpi-State", माप(जोड़ acpi_generic_state),
				 ACPI_MAX_STATE_CACHE_DEPTH,
				 &acpi_gbl_state_cache);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	status =
	    acpi_os_create_cache("Acpi-Parse",
				 माप(काष्ठा acpi_parse_obj_common),
				 ACPI_MAX_PARSE_CACHE_DEPTH,
				 &acpi_gbl_ps_node_cache);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	status =
	    acpi_os_create_cache("Acpi-ParseExt",
				 माप(काष्ठा acpi_parse_obj_named),
				 ACPI_MAX_EXTPARSE_CACHE_DEPTH,
				 &acpi_gbl_ps_node_ext_cache);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	status =
	    acpi_os_create_cache("Acpi-Operand",
				 माप(जोड़ acpi_opeअक्रम_object),
				 ACPI_MAX_OBJECT_CACHE_DEPTH,
				 &acpi_gbl_opeअक्रम_cache);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण
#अगर_घोषित ACPI_ASL_COMPILER
	/*
	 * For use with the ASL-/ASL+ option. This cache keeps track of regular
	 * 0xA9 0x01 comments.
	 */
	status =
	    acpi_os_create_cache("Acpi-Comment",
				 माप(काष्ठा acpi_comment_node),
				 ACPI_MAX_COMMENT_CACHE_DEPTH,
				 &acpi_gbl_reg_comment_cache);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	/*
	 * This cache keeps track of the starting addresses of where the comments
	 * lie. This helps prevent duplication of comments.
	 */
	status =
	    acpi_os_create_cache("Acpi-Comment-Addr",
				 माप(काष्ठा acpi_comment_addr_node),
				 ACPI_MAX_COMMENT_CACHE_DEPTH,
				 &acpi_gbl_comment_addr_cache);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	/*
	 * This cache will be used क्रम nodes that represent files.
	 */
	status =
	    acpi_os_create_cache("Acpi-File", माप(काष्ठा acpi_file_node),
				 ACPI_MAX_COMMENT_CACHE_DEPTH,
				 &acpi_gbl_file_cache);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित ACPI_DBG_TRACK_ALLOCATIONS

	/* Memory allocation lists */

	status = acpi_ut_create_list("Acpi-Global", 0, &acpi_gbl_global_list);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	status =
	    acpi_ut_create_list("Acpi-Namespace",
				माप(काष्ठा acpi_namespace_node),
				&acpi_gbl_ns_node_list);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण
#पूर्ण_अगर

	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_delete_caches
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Purge and delete all local caches
 *
 ******************************************************************************/

acpi_status acpi_ut_delete_caches(व्योम)
अणु
#अगर_घोषित ACPI_DBG_TRACK_ALLOCATIONS
	अक्षर buffer[7];

	अगर (acpi_gbl_display_final_mem_stats) अणु
		म_नकल(buffer, "MEMORY");
		(व्योम)acpi_db_display_statistics(buffer);
	पूर्ण
#पूर्ण_अगर

	(व्योम)acpi_os_delete_cache(acpi_gbl_namespace_cache);
	acpi_gbl_namespace_cache = शून्य;

	(व्योम)acpi_os_delete_cache(acpi_gbl_state_cache);
	acpi_gbl_state_cache = शून्य;

	(व्योम)acpi_os_delete_cache(acpi_gbl_opeअक्रम_cache);
	acpi_gbl_opeअक्रम_cache = शून्य;

	(व्योम)acpi_os_delete_cache(acpi_gbl_ps_node_cache);
	acpi_gbl_ps_node_cache = शून्य;

	(व्योम)acpi_os_delete_cache(acpi_gbl_ps_node_ext_cache);
	acpi_gbl_ps_node_ext_cache = शून्य;

#अगर_घोषित ACPI_ASL_COMPILER
	(व्योम)acpi_os_delete_cache(acpi_gbl_reg_comment_cache);
	acpi_gbl_reg_comment_cache = शून्य;

	(व्योम)acpi_os_delete_cache(acpi_gbl_comment_addr_cache);
	acpi_gbl_comment_addr_cache = शून्य;

	(व्योम)acpi_os_delete_cache(acpi_gbl_file_cache);
	acpi_gbl_file_cache = शून्य;
#पूर्ण_अगर

#अगर_घोषित ACPI_DBG_TRACK_ALLOCATIONS

	/* Debug only - display leftover memory allocation, अगर any */

	acpi_ut_dump_allocations(ACPI_UINT32_MAX, शून्य);

	/* Free memory lists */

	acpi_os_मुक्त(acpi_gbl_global_list);
	acpi_gbl_global_list = शून्य;

	acpi_os_मुक्त(acpi_gbl_ns_node_list);
	acpi_gbl_ns_node_list = शून्य;
#पूर्ण_अगर

	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_validate_buffer
 *
 * PARAMETERS:  buffer              - Buffer descriptor to be validated
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Perक्रमm parameter validation checks on an काष्ठा acpi_buffer
 *
 ******************************************************************************/

acpi_status acpi_ut_validate_buffer(काष्ठा acpi_buffer *buffer)
अणु

	/* Obviously, the काष्ठाure poपूर्णांकer must be valid */

	अगर (!buffer) अणु
		वापस (AE_BAD_PARAMETER);
	पूर्ण

	/* Special semantics क्रम the length */

	अगर ((buffer->length == ACPI_NO_BUFFER) ||
	    (buffer->length == ACPI_ALLOCATE_BUFFER) ||
	    (buffer->length == ACPI_ALLOCATE_LOCAL_BUFFER)) अणु
		वापस (AE_OK);
	पूर्ण

	/* Length is valid, the buffer poपूर्णांकer must be also */

	अगर (!buffer->poपूर्णांकer) अणु
		वापस (AE_BAD_PARAMETER);
	पूर्ण

	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_initialize_buffer
 *
 * PARAMETERS:  buffer              - Buffer to be validated
 *              required_length     - Length needed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Validate that the buffer is of the required length or
 *              allocate a new buffer. Returned buffer is always zeroed.
 *
 ******************************************************************************/

acpi_status
acpi_ut_initialize_buffer(काष्ठा acpi_buffer *buffer, acpi_size required_length)
अणु
	acpi_size input_buffer_length;

	/* Parameter validation */

	अगर (!buffer || !required_length) अणु
		वापस (AE_BAD_PARAMETER);
	पूर्ण

	/*
	 * Buffer->Length is used as both an input and output parameter. Get the
	 * input actual length and set the output required buffer length.
	 */
	input_buffer_length = buffer->length;
	buffer->length = required_length;

	/*
	 * The input buffer length contains the actual buffer length, or the type
	 * of buffer to be allocated by this routine.
	 */
	चयन (input_buffer_length) अणु
	हाल ACPI_NO_BUFFER:

		/* Return the exception (and the required buffer length) */

		वापस (AE_BUFFER_OVERFLOW);

	हाल ACPI_ALLOCATE_BUFFER:
		/*
		 * Allocate a new buffer. We directectly call acpi_os_allocate here to
		 * purposefully bypass the (optionally enabled) पूर्णांकernal allocation
		 * tracking mechanism since we only want to track पूर्णांकernal
		 * allocations. Note: The caller should use acpi_os_मुक्त to मुक्त this
		 * buffer created via ACPI_ALLOCATE_BUFFER.
		 */
		buffer->poपूर्णांकer = acpi_os_allocate(required_length);
		अवरोध;

	हाल ACPI_ALLOCATE_LOCAL_BUFFER:

		/* Allocate a new buffer with local पूर्णांकerface to allow tracking */

		buffer->poपूर्णांकer = ACPI_ALLOCATE(required_length);
		अवरोध;

	शेष:

		/* Existing buffer: Validate the size of the buffer */

		अगर (input_buffer_length < required_length) अणु
			वापस (AE_BUFFER_OVERFLOW);
		पूर्ण
		अवरोध;
	पूर्ण

	/* Validate allocation from above or input buffer poपूर्णांकer */

	अगर (!buffer->poपूर्णांकer) अणु
		वापस (AE_NO_MEMORY);
	पूर्ण

	/* Have a valid buffer, clear it */

	स_रखो(buffer->poपूर्णांकer, 0, required_length);
	वापस (AE_OK);
पूर्ण
