<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: exstoren - AML Interpreter object store support,
 *                        Store to Node (namespace object)
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acinterp.h"
#समावेश "amlcode.h"

#घोषणा _COMPONENT          ACPI_EXECUTER
ACPI_MODULE_NAME("exstoren")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_resolve_object
 *
 * PARAMETERS:  source_desc_ptr     - Poपूर्णांकer to the source object
 *              target_type         - Current type of the target
 *              walk_state          - Current walk state
 *
 * RETURN:      Status, resolved object in source_desc_ptr.
 *
 * DESCRIPTION: Resolve an object. If the object is a reference, dereference
 *              it and वापस the actual object in the source_desc_ptr.
 *
 ******************************************************************************/
acpi_status
acpi_ex_resolve_object(जोड़ acpi_opeअक्रम_object **source_desc_ptr,
		       acpi_object_type target_type,
		       काष्ठा acpi_walk_state *walk_state)
अणु
	जोड़ acpi_opeअक्रम_object *source_desc = *source_desc_ptr;
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TRACE(ex_resolve_object);

	/* Ensure we have a Target that can be stored to */

	चयन (target_type) अणु
	हाल ACPI_TYPE_BUFFER_FIELD:
	हाल ACPI_TYPE_LOCAL_REGION_FIELD:
	हाल ACPI_TYPE_LOCAL_BANK_FIELD:
	हाल ACPI_TYPE_LOCAL_INDEX_FIELD:
		/*
		 * These हालs all require only Integers or values that
		 * can be converted to Integers (Strings or Buffers)
		 */
	हाल ACPI_TYPE_INTEGER:
	हाल ACPI_TYPE_STRING:
	हाल ACPI_TYPE_BUFFER:
		/*
		 * Stores पूर्णांकo a Field/Region or पूर्णांकo a Integer/Buffer/String
		 * are all essentially the same. This हाल handles the
		 * "interchangeable" types Integer, String, and Buffer.
		 */
		अगर (source_desc->common.type == ACPI_TYPE_LOCAL_REFERENCE) अणु

			/* Resolve a reference object first */

			status =
			    acpi_ex_resolve_to_value(source_desc_ptr,
						     walk_state);
			अगर (ACPI_FAILURE(status)) अणु
				अवरोध;
			पूर्ण
		पूर्ण

		/* For copy_object, no further validation necessary */

		अगर (walk_state->opcode == AML_COPY_OBJECT_OP) अणु
			अवरोध;
		पूर्ण

		/* Must have a Integer, Buffer, or String */

		अगर ((source_desc->common.type != ACPI_TYPE_INTEGER) &&
		    (source_desc->common.type != ACPI_TYPE_BUFFER) &&
		    (source_desc->common.type != ACPI_TYPE_STRING) &&
		    !((source_desc->common.type == ACPI_TYPE_LOCAL_REFERENCE) &&
		      (source_desc->reference.class == ACPI_REFCLASS_TABLE))) अणु

			/* Conversion successful but still not a valid type */

			ACPI_ERROR((AE_INFO,
				    "Cannot assign type [%s] to [%s] (must be type Int/Str/Buf)",
				    acpi_ut_get_object_type_name(source_desc),
				    acpi_ut_get_type_name(target_type)));

			status = AE_AML_OPERAND_TYPE;
		पूर्ण
		अवरोध;

	हाल ACPI_TYPE_LOCAL_ALIAS:
	हाल ACPI_TYPE_LOCAL_METHOD_ALIAS:
		/*
		 * All aliases should have been resolved earlier, during the
		 * opeअक्रम resolution phase.
		 */
		ACPI_ERROR((AE_INFO, "Store into an unresolved Alias object"));
		status = AE_AML_INTERNAL;
		अवरोध;

	हाल ACPI_TYPE_PACKAGE:
	शेष:
		/*
		 * All other types than Alias and the various Fields come here,
		 * including the untyped हाल - ACPI_TYPE_ANY.
		 */
		अवरोध;
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_store_object_to_object
 *
 * PARAMETERS:  source_desc         - Object to store
 *              dest_desc           - Object to receive a copy of the source
 *              new_desc            - New object अगर dest_desc is obsoleted
 *              walk_state          - Current walk state
 *
 * RETURN:      Status
 *
 * DESCRIPTION: "Store" an object to another object. This may include
 *              converting the source type to the target type (implicit
 *              conversion), and a copy of the value of the source to
 *              the target.
 *
 *              The Assignment of an object to another (not named) object
 *              is handled here.
 *              The Source passed in will replace the current value (अगर any)
 *              with the input value.
 *
 *              When storing पूर्णांकo an object the data is converted to the
 *              target object type then stored in the object. This means
 *              that the target object type (क्रम an initialized target) will
 *              not be changed by a store operation.
 *
 *              This module allows destination types of Number, String,
 *              Buffer, and Package.
 *
 *              Assumes parameters are alपढ़ोy validated. NOTE: source_desc
 *              resolution (from a reference object) must be perक्रमmed by
 *              the caller अगर necessary.
 *
 ******************************************************************************/

acpi_status
acpi_ex_store_object_to_object(जोड़ acpi_opeअक्रम_object *source_desc,
			       जोड़ acpi_opeअक्रम_object *dest_desc,
			       जोड़ acpi_opeअक्रम_object **new_desc,
			       काष्ठा acpi_walk_state *walk_state)
अणु
	जोड़ acpi_opeअक्रम_object *actual_src_desc;
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TRACE_PTR(ex_store_object_to_object, source_desc);

	actual_src_desc = source_desc;
	अगर (!dest_desc) अणु
		/*
		 * There is no destination object (An uninitialized node or
		 * package element), so we can simply copy the source object
		 * creating a new destination object
		 */
		status =
		    acpi_ut_copy_iobject_to_iobject(actual_src_desc, new_desc,
						    walk_state);
		वापस_ACPI_STATUS(status);
	पूर्ण

	अगर (source_desc->common.type != dest_desc->common.type) अणु
		/*
		 * The source type करोes not match the type of the destination.
		 * Perक्रमm the "implicit conversion" of the source to the current type
		 * of the target as per the ACPI specअगरication.
		 *
		 * If no conversion perक्रमmed, actual_src_desc = source_desc.
		 * Otherwise, actual_src_desc is a temporary object to hold the
		 * converted object.
		 */
		status = acpi_ex_convert_to_target_type(dest_desc->common.type,
							source_desc,
							&actual_src_desc,
							walk_state);
		अगर (ACPI_FAILURE(status)) अणु
			वापस_ACPI_STATUS(status);
		पूर्ण

		अगर (source_desc == actual_src_desc) अणु
			/*
			 * No conversion was perक्रमmed. Return the source_desc as the
			 * new object.
			 */
			*new_desc = source_desc;
			वापस_ACPI_STATUS(AE_OK);
		पूर्ण
	पूर्ण

	/*
	 * We now have two objects of identical types, and we can perक्रमm a
	 * copy of the *value* of the source object.
	 */
	चयन (dest_desc->common.type) अणु
	हाल ACPI_TYPE_INTEGER:

		dest_desc->पूर्णांकeger.value = actual_src_desc->पूर्णांकeger.value;

		/* Truncate value अगर we are executing from a 32-bit ACPI table */

		(व्योम)acpi_ex_truncate_क्रम32bit_table(dest_desc);
		अवरोध;

	हाल ACPI_TYPE_STRING:

		status =
		    acpi_ex_store_string_to_string(actual_src_desc, dest_desc);
		अवरोध;

	हाल ACPI_TYPE_BUFFER:

		status =
		    acpi_ex_store_buffer_to_buffer(actual_src_desc, dest_desc);
		अवरोध;

	हाल ACPI_TYPE_PACKAGE:

		status =
		    acpi_ut_copy_iobject_to_iobject(actual_src_desc, &dest_desc,
						    walk_state);
		अवरोध;

	शेष:
		/*
		 * All other types come here.
		 */
		ACPI_WARNING((AE_INFO, "Store into type [%s] not implemented",
			      acpi_ut_get_object_type_name(dest_desc)));

		status = AE_NOT_IMPLEMENTED;
		अवरोध;
	पूर्ण

	अगर (actual_src_desc != source_desc) अणु

		/* Delete the पूर्णांकermediate (temporary) source object */

		acpi_ut_हटाओ_reference(actual_src_desc);
	पूर्ण

	*new_desc = dest_desc;
	वापस_ACPI_STATUS(status);
पूर्ण
