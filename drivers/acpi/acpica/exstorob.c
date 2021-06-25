<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: exstorob - AML object store support, store to object
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acinterp.h"

#घोषणा _COMPONENT          ACPI_EXECUTER
ACPI_MODULE_NAME("exstorob")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_store_buffer_to_buffer
 *
 * PARAMETERS:  source_desc         - Source object to copy
 *              target_desc         - Destination object of the copy
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Copy a buffer object to another buffer object.
 *
 ******************************************************************************/
acpi_status
acpi_ex_store_buffer_to_buffer(जोड़ acpi_opeअक्रम_object *source_desc,
			       जोड़ acpi_opeअक्रम_object *target_desc)
अणु
	u32 length;
	u8 *buffer;

	ACPI_FUNCTION_TRACE_PTR(ex_store_buffer_to_buffer, source_desc);

	/* If Source and Target are the same, just वापस */

	अगर (source_desc == target_desc) अणु
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	/* We know that source_desc is a buffer by now */

	buffer = ACPI_CAST_PTR(u8, source_desc->buffer.poपूर्णांकer);
	length = source_desc->buffer.length;

	/*
	 * If target is a buffer of length zero or is a अटल buffer,
	 * allocate a new buffer of the proper length
	 */
	अगर ((target_desc->buffer.length == 0) ||
	    (target_desc->common.flags & AOPOBJ_STATIC_POINTER)) अणु
		target_desc->buffer.poपूर्णांकer = ACPI_ALLOCATE(length);
		अगर (!target_desc->buffer.poपूर्णांकer) अणु
			वापस_ACPI_STATUS(AE_NO_MEMORY);
		पूर्ण

		target_desc->buffer.length = length;
	पूर्ण

	/* Copy source buffer to target buffer */

	अगर (length <= target_desc->buffer.length) अणु

		/* Clear existing buffer and copy in the new one */

		स_रखो(target_desc->buffer.poपूर्णांकer, 0,
		       target_desc->buffer.length);
		स_नकल(target_desc->buffer.poपूर्णांकer, buffer, length);

#अगर_घोषित ACPI_OBSOLETE_BEHAVIOR
		/*
		 * NOTE: ACPI versions up to 3.0 specअगरied that the buffer must be
		 * truncated अगर the string is smaller than the buffer. However, "other"
		 * implementations of ACPI never did this and thus became the defacto
		 * standard. ACPI 3.0A changes this behavior such that the buffer
		 * is no दीर्घer truncated.
		 */

		/*
		 * OBSOLETE BEHAVIOR:
		 * If the original source was a string, we must truncate the buffer,
		 * according to the ACPI spec. Integer-to-Buffer and Buffer-to-Buffer
		 * copy must not truncate the original buffer.
		 */
		अगर (original_src_type == ACPI_TYPE_STRING) अणु

			/* Set the new length of the target */

			target_desc->buffer.length = length;
		पूर्ण
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		/* Truncate the source, copy only what will fit */

		स_नकल(target_desc->buffer.poपूर्णांकer, buffer,
		       target_desc->buffer.length);

		ACPI_DEBUG_PRINT((ACPI_DB_INFO,
				  "Truncating source buffer from %X to %X\n",
				  length, target_desc->buffer.length));
	पूर्ण

	/* Copy flags */

	target_desc->buffer.flags = source_desc->buffer.flags;
	target_desc->common.flags &= ~AOPOBJ_STATIC_POINTER;
	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_store_string_to_string
 *
 * PARAMETERS:  source_desc         - Source object to copy
 *              target_desc         - Destination object of the copy
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Copy a String object to another String object
 *
 ******************************************************************************/

acpi_status
acpi_ex_store_string_to_string(जोड़ acpi_opeअक्रम_object *source_desc,
			       जोड़ acpi_opeअक्रम_object *target_desc)
अणु
	u32 length;
	u8 *buffer;

	ACPI_FUNCTION_TRACE_PTR(ex_store_string_to_string, source_desc);

	/* If Source and Target are the same, just वापस */

	अगर (source_desc == target_desc) अणु
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	/* We know that source_desc is a string by now */

	buffer = ACPI_CAST_PTR(u8, source_desc->string.poपूर्णांकer);
	length = source_desc->string.length;

	/*
	 * Replace existing string value अगर it will fit and the string
	 * poपूर्णांकer is not a अटल poपूर्णांकer (part of an ACPI table)
	 */
	अगर ((length < target_desc->string.length) &&
	    (!(target_desc->common.flags & AOPOBJ_STATIC_POINTER))) अणु
		/*
		 * String will fit in existing non-अटल buffer.
		 * Clear old string and copy in the new one
		 */
		स_रखो(target_desc->string.poपूर्णांकer, 0,
		       (acpi_size)target_desc->string.length + 1);
		स_नकल(target_desc->string.poपूर्णांकer, buffer, length);
	पूर्ण अन्यथा अणु
		/*
		 * Free the current buffer, then allocate a new buffer
		 * large enough to hold the value
		 */
		अगर (target_desc->string.poपूर्णांकer &&
		    (!(target_desc->common.flags & AOPOBJ_STATIC_POINTER))) अणु

			/* Only मुक्त अगर not a poपूर्णांकer पूर्णांकo the DSDT */

			ACPI_FREE(target_desc->string.poपूर्णांकer);
		पूर्ण

		target_desc->string.poपूर्णांकer =
		    ACPI_ALLOCATE_ZEROED((acpi_size)length + 1);

		अगर (!target_desc->string.poपूर्णांकer) अणु
			वापस_ACPI_STATUS(AE_NO_MEMORY);
		पूर्ण

		target_desc->common.flags &= ~AOPOBJ_STATIC_POINTER;
		स_नकल(target_desc->string.poपूर्णांकer, buffer, length);
	पूर्ण

	/* Set the new target length */

	target_desc->string.length = length;
	वापस_ACPI_STATUS(AE_OK);
पूर्ण
