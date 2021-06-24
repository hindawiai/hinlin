<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: nspredef - Validation of ACPI predefined methods and objects
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#घोषणा ACPI_CREATE_PREDEFINED_TABLE

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acnamesp.h"
#समावेश "acpredef.h"

#घोषणा _COMPONENT          ACPI_NAMESPACE
ACPI_MODULE_NAME("nspredef")

/*******************************************************************************
 *
 * This module validates predefined ACPI objects that appear in the namespace,
 * at the समय they are evaluated (via acpi_evaluate_object). The purpose of this
 * validation is to detect problems with BIOS-exposed predefined ACPI objects
 * beक्रमe the results are वापसed to the ACPI-related drivers.
 *
 * There are several areas that are validated:
 *
 *  1) The number of input arguments as defined by the method/object in the
 *     ASL is validated against the ACPI specअगरication.
 *  2) The type of the वापस object (अगर any) is validated against the ACPI
 *     specअगरication.
 *  3) For वापसed package objects, the count of package elements is
 *     validated, as well as the type of each package element. Nested
 *     packages are supported.
 *
 * For any problems found, a warning message is issued.
 *
 ******************************************************************************/
/* Local prototypes */
अटल acpi_status
acpi_ns_check_reference(काष्ठा acpi_evaluate_info *info,
			जोड़ acpi_opeअक्रम_object *वापस_object);

अटल u32 acpi_ns_get_biपंचांगapped_type(जोड़ acpi_opeअक्रम_object *वापस_object);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_check_वापस_value
 *
 * PARAMETERS:  node            - Namespace node क्रम the method/object
 *              info            - Method execution inक्रमmation block
 *              user_param_count - Number of parameters actually passed
 *              वापस_status   - Status from the object evaluation
 *              वापस_object_ptr - Poपूर्णांकer to the object वापसed from the
 *                                evaluation of a method or object
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Check the value वापसed from a predefined name.
 *
 ******************************************************************************/

acpi_status
acpi_ns_check_वापस_value(काष्ठा acpi_namespace_node *node,
			   काष्ठा acpi_evaluate_info *info,
			   u32 user_param_count,
			   acpi_status वापस_status,
			   जोड़ acpi_opeअक्रम_object **वापस_object_ptr)
अणु
	acpi_status status;
	स्थिर जोड़ acpi_predefined_info *predefined;

	ACPI_FUNCTION_TRACE(ns_check_वापस_value);

	/* If not a predefined name, we cannot validate the वापस object */

	predefined = info->predefined;
	अगर (!predefined) अणु
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	/*
	 * If the method failed or did not actually वापस an object, we cannot
	 * validate the वापस object
	 */
	अगर ((वापस_status != AE_OK) && (वापस_status != AE_CTRL_RETURN_VALUE)) अणु
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	/*
	 * Return value validation and possible repair.
	 *
	 * 1) Don't perक्रमm वापस value validation/repair अगर this feature
	 * has been disabled via a global option.
	 *
	 * 2) We have a वापस value, but अगर one wasn't expected, just निकास,
	 * this is not a problem. For example, अगर the "Implicit Return"
	 * feature is enabled, methods will always वापस a value.
	 *
	 * 3) If the वापस value can be of any type, then we cannot perक्रमm
	 * any validation, just निकास.
	 */
	अगर (acpi_gbl_disable_स्वतः_repair ||
	    (!predefined->info.expected_btypes) ||
	    (predefined->info.expected_btypes == ACPI_RTYPE_ALL)) अणु
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	/*
	 * Check that the type of the मुख्य वापस object is what is expected
	 * क्रम this predefined name
	 */
	status = acpi_ns_check_object_type(info, वापस_object_ptr,
					   predefined->info.expected_btypes,
					   ACPI_NOT_PACKAGE_ELEMENT);
	अगर (ACPI_FAILURE(status)) अणु
		जाओ निकास;
	पूर्ण

	/*
	 *
	 * 4) If there is no वापस value and it is optional, just वापस
	 * AE_OK (_WAK).
	 */
	अगर (!(*वापस_object_ptr)) अणु
		जाओ निकास;
	पूर्ण

	/*
	 * For वापसed Package objects, check the type of all sub-objects.
	 * Note: Package may have been newly created by call above.
	 */
	अगर ((*वापस_object_ptr)->common.type == ACPI_TYPE_PACKAGE) अणु
		info->parent_package = *वापस_object_ptr;
		status = acpi_ns_check_package(info, वापस_object_ptr);
		अगर (ACPI_FAILURE(status)) अणु

			/* We might be able to fix some errors */

			अगर ((status != AE_AML_OPERAND_TYPE) &&
			    (status != AE_AML_OPERAND_VALUE)) अणु
				जाओ निकास;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * The वापस object was OK, or it was successfully repaired above.
	 * Now make some additional checks such as verअगरying that package
	 * objects are sorted correctly (अगर required) or buffer objects have
	 * the correct data width (bytes vs. dwords). These repairs are
	 * perक्रमmed on a per-name basis, i.e., the code is specअगरic to
	 * particular predefined names.
	 */
	status = acpi_ns_complex_repairs(info, node, status, वापस_object_ptr);

निकास:
	/*
	 * If the object validation failed or अगर we successfully repaired one
	 * or more objects, mark the parent node to suppress further warning
	 * messages during the next evaluation of the same method/object.
	 */
	अगर (ACPI_FAILURE(status) || (info->वापस_flags & ACPI_OBJECT_REPAIRED)) अणु
		node->flags |= ANOBJ_EVALUATED;
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_check_object_type
 *
 * PARAMETERS:  info            - Method execution inक्रमmation block
 *              वापस_object_ptr - Poपूर्णांकer to the object वापसed from the
 *                                evaluation of a method or object
 *              expected_btypes - Biपंचांगap of expected वापस type(s)
 *              package_index   - Index of object within parent package (अगर
 *                                applicable - ACPI_NOT_PACKAGE_ELEMENT
 *                                otherwise)
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Check the type of the वापस object against the expected object
 *              type(s). Use of Btype allows multiple expected object types.
 *
 ******************************************************************************/

acpi_status
acpi_ns_check_object_type(काष्ठा acpi_evaluate_info *info,
			  जोड़ acpi_opeअक्रम_object **वापस_object_ptr,
			  u32 expected_btypes, u32 package_index)
अणु
	जोड़ acpi_opeअक्रम_object *वापस_object = *वापस_object_ptr;
	acpi_status status = AE_OK;
	अक्षर type_buffer[96];	/* Room क्रम 10 types */

	/* A Namespace node should not get here, but make sure */

	अगर (वापस_object &&
	    ACPI_GET_DESCRIPTOR_TYPE(वापस_object) == ACPI_DESC_TYPE_NAMED) अणु
		ACPI_WARN_PREDEFINED((AE_INFO, info->full_pathname,
				      info->node_flags,
				      "Invalid return type - Found a Namespace node [%4.4s] type %s",
				      वापस_object->node.name.ascii,
				      acpi_ut_get_type_name(वापस_object->node.
							    type)));
		वापस (AE_AML_OPERAND_TYPE);
	पूर्ण

	/*
	 * Convert the object type (ACPI_TYPE_xxx) to a biपंचांगapped object type.
	 * The biपंचांगapped type allows multiple possible वापस types.
	 *
	 * Note, the हालs below must handle all of the possible types वापसed
	 * from all of the predefined names (including elements of वापसed
	 * packages)
	 */
	info->वापस_btype = acpi_ns_get_biपंचांगapped_type(वापस_object);
	अगर (info->वापस_btype == ACPI_RTYPE_ANY) अणु

		/* Not one of the supported objects, must be incorrect */
		जाओ type_error_निकास;
	पूर्ण

	/* For reference objects, check that the reference type is correct */

	अगर ((info->वापस_btype & expected_btypes) == ACPI_RTYPE_REFERENCE) अणु
		status = acpi_ns_check_reference(info, वापस_object);
		वापस (status);
	पूर्ण

	/* Attempt simple repair of the वापसed object अगर necessary */

	status = acpi_ns_simple_repair(info, expected_btypes,
				       package_index, वापस_object_ptr);
	अगर (ACPI_SUCCESS(status)) अणु
		वापस (AE_OK);	/* Successful repair */
	पूर्ण

type_error_निकास:

	/* Create a string with all expected types क्रम this predefined object */

	acpi_ut_get_expected_वापस_types(type_buffer, expected_btypes);

	अगर (!वापस_object) अणु
		ACPI_WARN_PREDEFINED((AE_INFO, info->full_pathname,
				      info->node_flags,
				      "Expected return object of type %s",
				      type_buffer));
	पूर्ण अन्यथा अगर (package_index == ACPI_NOT_PACKAGE_ELEMENT) अणु
		ACPI_WARN_PREDEFINED((AE_INFO, info->full_pathname,
				      info->node_flags,
				      "Return type mismatch - found %s, expected %s",
				      acpi_ut_get_object_type_name
				      (वापस_object), type_buffer));
	पूर्ण अन्यथा अणु
		ACPI_WARN_PREDEFINED((AE_INFO, info->full_pathname,
				      info->node_flags,
				      "Return Package type mismatch at index %u - "
				      "found %s, expected %s", package_index,
				      acpi_ut_get_object_type_name
				      (वापस_object), type_buffer));
	पूर्ण

	वापस (AE_AML_OPERAND_TYPE);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_check_reference
 *
 * PARAMETERS:  info            - Method execution inक्रमmation block
 *              वापस_object   - Object वापसed from the evaluation of a
 *                                method or object
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Check a वापसed reference object क्रम the correct reference
 *              type. The only reference type that can be वापसed from a
 *              predefined method is a named reference. All others are invalid.
 *
 ******************************************************************************/

अटल acpi_status
acpi_ns_check_reference(काष्ठा acpi_evaluate_info *info,
			जोड़ acpi_opeअक्रम_object *वापस_object)
अणु

	/*
	 * Check the reference object क्रम the correct reference type (opcode).
	 * The only type of reference that can be converted to a जोड़ acpi_object is
	 * a reference to a named object (reference class: NAME)
	 */
	अगर (वापस_object->reference.class == ACPI_REFCLASS_NAME) अणु
		वापस (AE_OK);
	पूर्ण

	ACPI_WARN_PREDEFINED((AE_INFO, info->full_pathname, info->node_flags,
			      "Return type mismatch - unexpected reference object type [%s] %2.2X",
			      acpi_ut_get_reference_name(वापस_object),
			      वापस_object->reference.class));

	वापस (AE_AML_OPERAND_TYPE);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_get_biपंचांगapped_type
 *
 * PARAMETERS:  वापस_object   - Object वापसed from method/obj evaluation
 *
 * RETURN:      Object वापस type. ACPI_RTYPE_ANY indicates that the object
 *              type is not supported. ACPI_RTYPE_NONE indicates that no
 *              object was वापसed (वापस_object is शून्य).
 *
 * DESCRIPTION: Convert object type पूर्णांकo a biपंचांगapped object वापस type.
 *
 ******************************************************************************/

अटल u32 acpi_ns_get_biपंचांगapped_type(जोड़ acpi_opeअक्रम_object *वापस_object)
अणु
	u32 वापस_btype;

	अगर (!वापस_object) अणु
		वापस (ACPI_RTYPE_NONE);
	पूर्ण

	/* Map acpi_object_type to पूर्णांकernal biपंचांगapped type */

	चयन (वापस_object->common.type) अणु
	हाल ACPI_TYPE_INTEGER:

		वापस_btype = ACPI_RTYPE_INTEGER;
		अवरोध;

	हाल ACPI_TYPE_BUFFER:

		वापस_btype = ACPI_RTYPE_BUFFER;
		अवरोध;

	हाल ACPI_TYPE_STRING:

		वापस_btype = ACPI_RTYPE_STRING;
		अवरोध;

	हाल ACPI_TYPE_PACKAGE:

		वापस_btype = ACPI_RTYPE_PACKAGE;
		अवरोध;

	हाल ACPI_TYPE_LOCAL_REFERENCE:

		वापस_btype = ACPI_RTYPE_REFERENCE;
		अवरोध;

	शेष:

		/* Not one of the supported objects, must be incorrect */

		वापस_btype = ACPI_RTYPE_ANY;
		अवरोध;
	पूर्ण

	वापस (वापस_btype);
पूर्ण
