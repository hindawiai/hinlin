<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: nsprepkg - Validation of package objects क्रम predefined names
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acnamesp.h"
#समावेश "acpredef.h"

#घोषणा _COMPONENT          ACPI_NAMESPACE
ACPI_MODULE_NAME("nsprepkg")

/* Local prototypes */
अटल acpi_status
acpi_ns_check_package_list(काष्ठा acpi_evaluate_info *info,
			   स्थिर जोड़ acpi_predefined_info *package,
			   जोड़ acpi_opeअक्रम_object **elements, u32 count);

अटल acpi_status
acpi_ns_check_package_elements(काष्ठा acpi_evaluate_info *info,
			       जोड़ acpi_opeअक्रम_object **elements,
			       u8 type1,
			       u32 count1,
			       u8 type2, u32 count2, u32 start_index);

अटल acpi_status
acpi_ns_custom_package(काष्ठा acpi_evaluate_info *info,
		       जोड़ acpi_opeअक्रम_object **elements, u32 count);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_check_package
 *
 * PARAMETERS:  info                - Method execution inक्रमmation block
 *              वापस_object_ptr   - Poपूर्णांकer to the object वापसed from the
 *                                    evaluation of a method or object
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Check a वापसed package object क्रम the correct count and
 *              correct type of all sub-objects.
 *
 ******************************************************************************/

acpi_status
acpi_ns_check_package(काष्ठा acpi_evaluate_info *info,
		      जोड़ acpi_opeअक्रम_object **वापस_object_ptr)
अणु
	जोड़ acpi_opeअक्रम_object *वापस_object = *वापस_object_ptr;
	स्थिर जोड़ acpi_predefined_info *package;
	जोड़ acpi_opeअक्रम_object **elements;
	acpi_status status = AE_OK;
	u32 expected_count;
	u32 count;
	u32 i;

	ACPI_FUNCTION_TRACE(ns_check_package);

	/* The package info क्रम this name is in the next table entry */

	package = info->predefined + 1;

	ACPI_DEBUG_PRINT((ACPI_DB_NAMES,
			  "%s Validating return Package of Type %X, Count %X\n",
			  info->full_pathname, package->ret_info.type,
			  वापस_object->package.count));

	/*
	 * For variable-length Packages, we can safely हटाओ all embedded
	 * and trailing शून्य package elements
	 */
	acpi_ns_हटाओ_null_elements(info, package->ret_info.type,
				     वापस_object);

	/* Extract package count and elements array */

	elements = वापस_object->package.elements;
	count = वापस_object->package.count;

	/*
	 * Most packages must have at least one element. The only exception
	 * is the variable-length package (ACPI_PTYPE1_VAR).
	 */
	अगर (!count) अणु
		अगर (package->ret_info.type == ACPI_PTYPE1_VAR) अणु
			वापस_ACPI_STATUS(AE_OK);
		पूर्ण

		ACPI_WARN_PREDEFINED((AE_INFO, info->full_pathname,
				      info->node_flags,
				      "Return Package has no elements (empty)"));

		वापस_ACPI_STATUS(AE_AML_OPERAND_VALUE);
	पूर्ण

	/*
	 * Decode the type of the expected package contents
	 *
	 * PTYPE1 packages contain no subpackages
	 * PTYPE2 packages contain subpackages
	 */
	चयन (package->ret_info.type) अणु
	हाल ACPI_PTYPE_CUSTOM:

		status = acpi_ns_custom_package(info, elements, count);
		अवरोध;

	हाल ACPI_PTYPE1_FIXED:
		/*
		 * The package count is fixed and there are no subpackages
		 *
		 * If package is too small, निकास.
		 * If package is larger than expected, issue warning but जारी
		 */
		expected_count =
		    package->ret_info.count1 + package->ret_info.count2;
		अगर (count < expected_count) अणु
			जाओ package_too_small;
		पूर्ण अन्यथा अगर (count > expected_count) अणु
			ACPI_DEBUG_PRINT((ACPI_DB_REPAIR,
					  "%s: Return Package is larger than needed - "
					  "found %u, expected %u\n",
					  info->full_pathname, count,
					  expected_count));
		पूर्ण

		/* Validate all elements of the वापसed package */

		status = acpi_ns_check_package_elements(info, elements,
							package->ret_info.
							object_type1,
							package->ret_info.
							count1,
							package->ret_info.
							object_type2,
							package->ret_info.
							count2, 0);
		अवरोध;

	हाल ACPI_PTYPE1_VAR:
		/*
		 * The package count is variable, there are no subpackages, and all
		 * elements must be of the same type
		 */
		क्रम (i = 0; i < count; i++) अणु
			status = acpi_ns_check_object_type(info, elements,
							   package->ret_info.
							   object_type1, i);
			अगर (ACPI_FAILURE(status)) अणु
				वापस_ACPI_STATUS(status);
			पूर्ण

			elements++;
		पूर्ण
		अवरोध;

	हाल ACPI_PTYPE1_OPTION:
		/*
		 * The package count is variable, there are no subpackages. There are
		 * a fixed number of required elements, and a variable number of
		 * optional elements.
		 *
		 * Check अगर package is at least as large as the minimum required
		 */
		expected_count = package->ret_info3.count;
		अगर (count < expected_count) अणु
			जाओ package_too_small;
		पूर्ण

		/* Variable number of sub-objects */

		क्रम (i = 0; i < count; i++) अणु
			अगर (i < package->ret_info3.count) अणु

				/* These are the required package elements (0, 1, or 2) */

				status =
				    acpi_ns_check_object_type(info, elements,
							      package->
							      ret_info3.
							      object_type[i],
							      i);
				अगर (ACPI_FAILURE(status)) अणु
					वापस_ACPI_STATUS(status);
				पूर्ण
			पूर्ण अन्यथा अणु
				/* These are the optional package elements */

				status =
				    acpi_ns_check_object_type(info, elements,
							      package->
							      ret_info3.
							      tail_object_type,
							      i);
				अगर (ACPI_FAILURE(status)) अणु
					वापस_ACPI_STATUS(status);
				पूर्ण
			पूर्ण

			elements++;
		पूर्ण
		अवरोध;

	हाल ACPI_PTYPE2_REV_FIXED:

		/* First element is the (Integer) revision */

		status =
		    acpi_ns_check_object_type(info, elements,
					      ACPI_RTYPE_INTEGER, 0);
		अगर (ACPI_FAILURE(status)) अणु
			वापस_ACPI_STATUS(status);
		पूर्ण

		elements++;
		count--;

		/* Examine the subpackages */

		status =
		    acpi_ns_check_package_list(info, package, elements, count);
		अवरोध;

	हाल ACPI_PTYPE2_PKG_COUNT:

		/* First element is the (Integer) count of subpackages to follow */

		status =
		    acpi_ns_check_object_type(info, elements,
					      ACPI_RTYPE_INTEGER, 0);
		अगर (ACPI_FAILURE(status)) अणु
			वापस_ACPI_STATUS(status);
		पूर्ण

		/*
		 * Count cannot be larger than the parent package length, but allow it
		 * to be smaller. The >= accounts क्रम the Integer above.
		 */
		expected_count = (u32)(*elements)->पूर्णांकeger.value;
		अगर (expected_count >= count) अणु
			जाओ package_too_small;
		पूर्ण

		count = expected_count;
		elements++;

		/* Examine the subpackages */

		status =
		    acpi_ns_check_package_list(info, package, elements, count);
		अवरोध;

	हाल ACPI_PTYPE2:
	हाल ACPI_PTYPE2_FIXED:
	हाल ACPI_PTYPE2_MIN:
	हाल ACPI_PTYPE2_COUNT:
	हाल ACPI_PTYPE2_FIX_VAR:
		/*
		 * These types all वापस a single Package that consists of a
		 * variable number of subpackages.
		 *
		 * First, ensure that the first element is a subpackage. If not,
		 * the BIOS may have incorrectly वापसed the object as a single
		 * package instead of a Package of Packages (a common error अगर
		 * there is only one entry). We may be able to repair this by
		 * wrapping the वापसed Package with a new outer Package.
		 */
		अगर (*elements
		    && ((*elements)->common.type != ACPI_TYPE_PACKAGE)) अणु

			/* Create the new outer package and populate it */

			status =
			    acpi_ns_wrap_with_package(info, वापस_object,
						      वापस_object_ptr);
			अगर (ACPI_FAILURE(status)) अणु
				वापस_ACPI_STATUS(status);
			पूर्ण

			/* Update locals to poपूर्णांक to the new package (of 1 element) */

			वापस_object = *वापस_object_ptr;
			elements = वापस_object->package.elements;
			count = 1;
		पूर्ण

		/* Examine the subpackages */

		status =
		    acpi_ns_check_package_list(info, package, elements, count);
		अवरोध;

	हाल ACPI_PTYPE2_VAR_VAR:
		/*
		 * Returns a variable list of packages, each with a variable list
		 * of objects.
		 */
		अवरोध;

	हाल ACPI_PTYPE2_UUID_PAIR:

		/* The package must contain pairs of (UUID + type) */

		अगर (count & 1) अणु
			expected_count = count + 1;
			जाओ package_too_small;
		पूर्ण

		जबतक (count > 0) अणु
			status = acpi_ns_check_object_type(info, elements,
							   package->ret_info.
							   object_type1, 0);
			अगर (ACPI_FAILURE(status)) अणु
				वापस_ACPI_STATUS(status);
			पूर्ण

			/* Validate length of the UUID buffer */

			अगर ((*elements)->buffer.length != 16) अणु
				ACPI_WARN_PREDEFINED((AE_INFO,
						      info->full_pathname,
						      info->node_flags,
						      "Invalid length for UUID Buffer"));
				वापस_ACPI_STATUS(AE_AML_OPERAND_VALUE);
			पूर्ण

			status = acpi_ns_check_object_type(info, elements + 1,
							   package->ret_info.
							   object_type2, 0);
			अगर (ACPI_FAILURE(status)) अणु
				वापस_ACPI_STATUS(status);
			पूर्ण

			elements += 2;
			count -= 2;
		पूर्ण
		अवरोध;

	शेष:

		/* Should not get here अगर predefined info table is correct */

		ACPI_WARN_PREDEFINED((AE_INFO, info->full_pathname,
				      info->node_flags,
				      "Invalid internal return type in table entry: %X",
				      package->ret_info.type));

		वापस_ACPI_STATUS(AE_AML_INTERNAL);
	पूर्ण

	वापस_ACPI_STATUS(status);

package_too_small:

	/* Error निकास क्रम the हाल with an incorrect package count */

	ACPI_WARN_PREDEFINED((AE_INFO, info->full_pathname, info->node_flags,
			      "Return Package is too small - found %u elements, expected %u",
			      count, expected_count));

	वापस_ACPI_STATUS(AE_AML_OPERAND_VALUE);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_check_package_list
 *
 * PARAMETERS:  info            - Method execution inक्रमmation block
 *              package         - Poपूर्णांकer to package-specअगरic info क्रम method
 *              elements        - Element list of parent package. All elements
 *                                of this list should be of type Package.
 *              count           - Count of subpackages
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Examine a list of subpackages
 *
 ******************************************************************************/

अटल acpi_status
acpi_ns_check_package_list(काष्ठा acpi_evaluate_info *info,
			   स्थिर जोड़ acpi_predefined_info *package,
			   जोड़ acpi_opeअक्रम_object **elements, u32 count)
अणु
	जोड़ acpi_opeअक्रम_object *sub_package;
	जोड़ acpi_opeअक्रम_object **sub_elements;
	acpi_status status;
	u32 expected_count;
	u32 i;
	u32 j;

	/*
	 * Validate each subpackage in the parent Package
	 *
	 * NOTE: assumes list of subpackages contains no शून्य elements.
	 * Any शून्य elements should have been हटाओd by earlier call
	 * to acpi_ns_हटाओ_null_elements.
	 */
	क्रम (i = 0; i < count; i++) अणु
		sub_package = *elements;
		sub_elements = sub_package->package.elements;
		info->parent_package = sub_package;

		/* Each sub-object must be of type Package */

		status = acpi_ns_check_object_type(info, &sub_package,
						   ACPI_RTYPE_PACKAGE, i);
		अगर (ACPI_FAILURE(status)) अणु
			वापस (status);
		पूर्ण

		/* Examine the dअगरferent types of expected subpackages */

		info->parent_package = sub_package;
		चयन (package->ret_info.type) अणु
		हाल ACPI_PTYPE2:
		हाल ACPI_PTYPE2_PKG_COUNT:
		हाल ACPI_PTYPE2_REV_FIXED:

			/* Each subpackage has a fixed number of elements */

			expected_count =
			    package->ret_info.count1 + package->ret_info.count2;
			अगर (sub_package->package.count < expected_count) अणु
				जाओ package_too_small;
			पूर्ण

			status =
			    acpi_ns_check_package_elements(info, sub_elements,
							   package->ret_info.
							   object_type1,
							   package->ret_info.
							   count1,
							   package->ret_info.
							   object_type2,
							   package->ret_info.
							   count2, 0);
			अगर (ACPI_FAILURE(status)) अणु
				वापस (status);
			पूर्ण
			अवरोध;

		हाल ACPI_PTYPE2_FIX_VAR:
			/*
			 * Each subpackage has a fixed number of elements and an
			 * optional element
			 */
			expected_count =
			    package->ret_info.count1 + package->ret_info.count2;
			अगर (sub_package->package.count < expected_count) अणु
				जाओ package_too_small;
			पूर्ण

			status =
			    acpi_ns_check_package_elements(info, sub_elements,
							   package->ret_info.
							   object_type1,
							   package->ret_info.
							   count1,
							   package->ret_info.
							   object_type2,
							   sub_package->package.
							   count -
							   package->ret_info.
							   count1, 0);
			अगर (ACPI_FAILURE(status)) अणु
				वापस (status);
			पूर्ण
			अवरोध;

		हाल ACPI_PTYPE2_VAR_VAR:
			/*
			 * Each subpackage has a fixed or variable number of elements
			 */
			अवरोध;

		हाल ACPI_PTYPE2_FIXED:

			/* Each subpackage has a fixed length */

			expected_count = package->ret_info2.count;
			अगर (sub_package->package.count < expected_count) अणु
				जाओ package_too_small;
			पूर्ण

			/* Check the type of each subpackage element */

			क्रम (j = 0; j < expected_count; j++) अणु
				status =
				    acpi_ns_check_object_type(info,
							      &sub_elements[j],
							      package->
							      ret_info2.
							      object_type[j],
							      j);
				अगर (ACPI_FAILURE(status)) अणु
					वापस (status);
				पूर्ण
			पूर्ण
			अवरोध;

		हाल ACPI_PTYPE2_MIN:

			/* Each subpackage has a variable but minimum length */

			expected_count = package->ret_info.count1;
			अगर (sub_package->package.count < expected_count) अणु
				जाओ package_too_small;
			पूर्ण

			/* Check the type of each subpackage element */

			status =
			    acpi_ns_check_package_elements(info, sub_elements,
							   package->ret_info.
							   object_type1,
							   sub_package->package.
							   count, 0, 0, 0);
			अगर (ACPI_FAILURE(status)) अणु
				वापस (status);
			पूर्ण
			अवरोध;

		हाल ACPI_PTYPE2_COUNT:
			/*
			 * First element is the (Integer) count of elements, including
			 * the count field (the ACPI name is num_elements)
			 */
			status = acpi_ns_check_object_type(info, sub_elements,
							   ACPI_RTYPE_INTEGER,
							   0);
			अगर (ACPI_FAILURE(status)) अणु
				वापस (status);
			पूर्ण

			/*
			 * Make sure package is large enough क्रम the Count and is
			 * is as large as the minimum size
			 */
			expected_count = (u32)(*sub_elements)->पूर्णांकeger.value;
			अगर (sub_package->package.count < expected_count) अणु
				जाओ package_too_small;
			पूर्ण

			अगर (sub_package->package.count <
			    package->ret_info.count1) अणु
				expected_count = package->ret_info.count1;
				जाओ package_too_small;
			पूर्ण

			अगर (expected_count == 0) अणु
				/*
				 * Either the num_entries element was originally zero or it was
				 * a शून्य element and repaired to an Integer of value zero.
				 * In either हाल, repair it by setting num_entries to be the
				 * actual size of the subpackage.
				 */
				expected_count = sub_package->package.count;
				(*sub_elements)->पूर्णांकeger.value = expected_count;
			पूर्ण

			/* Check the type of each subpackage element */

			status =
			    acpi_ns_check_package_elements(info,
							   (sub_elements + 1),
							   package->ret_info.
							   object_type1,
							   (expected_count - 1),
							   0, 0, 1);
			अगर (ACPI_FAILURE(status)) अणु
				वापस (status);
			पूर्ण
			अवरोध;

		शेष:	/* Should not get here, type was validated by caller */

			ACPI_ERROR((AE_INFO, "Invalid Package type: %X",
				    package->ret_info.type));
			वापस (AE_AML_INTERNAL);
		पूर्ण

		elements++;
	पूर्ण

	वापस (AE_OK);

package_too_small:

	/* The subpackage count was smaller than required */

	ACPI_WARN_PREDEFINED((AE_INFO, info->full_pathname, info->node_flags,
			      "Return SubPackage[%u] is too small - found %u elements, expected %u",
			      i, sub_package->package.count, expected_count));

	वापस (AE_AML_OPERAND_VALUE);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_custom_package
 *
 * PARAMETERS:  info                - Method execution inक्रमmation block
 *              elements            - Poपूर्णांकer to the package elements array
 *              count               - Element count क्रम the package
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Check a वापसed package object क्रम the correct count and
 *              correct type of all sub-objects.
 *
 * NOTE: Currently used क्रम the _BIX method only. When needed क्रम two or more
 * methods, probably a detect/dispatch mechanism will be required.
 *
 ******************************************************************************/

अटल acpi_status
acpi_ns_custom_package(काष्ठा acpi_evaluate_info *info,
		       जोड़ acpi_opeअक्रम_object **elements, u32 count)
अणु
	u32 expected_count;
	u32 version;
	acpi_status status = AE_OK;

	ACPI_FUNCTION_NAME(ns_custom_package);

	/* Get version number, must be Integer */

	अगर ((*elements)->common.type != ACPI_TYPE_INTEGER) अणु
		ACPI_WARN_PREDEFINED((AE_INFO, info->full_pathname,
				      info->node_flags,
				      "Return Package has invalid object type for version number"));
		वापस_ACPI_STATUS(AE_AML_OPERAND_TYPE);
	पूर्ण

	version = (u32)(*elements)->पूर्णांकeger.value;
	expected_count = 21;	/* Version 1 */

	अगर (version == 0) अणु
		expected_count = 20;	/* Version 0 */
	पूर्ण

	अगर (count < expected_count) अणु
		ACPI_WARN_PREDEFINED((AE_INFO, info->full_pathname,
				      info->node_flags,
				      "Return Package is too small - found %u elements, expected %u",
				      count, expected_count));
		वापस_ACPI_STATUS(AE_AML_OPERAND_VALUE);
	पूर्ण अन्यथा अगर (count > expected_count) अणु
		ACPI_DEBUG_PRINT((ACPI_DB_REPAIR,
				  "%s: Return Package is larger than needed - "
				  "found %u, expected %u\n",
				  info->full_pathname, count, expected_count));
	पूर्ण

	/* Validate all elements of the वापसed package */

	status = acpi_ns_check_package_elements(info, elements,
						ACPI_RTYPE_INTEGER, 16,
						ACPI_RTYPE_STRING, 4, 0);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Version 1 has a single trailing पूर्णांकeger */

	अगर (version > 0) अणु
		status = acpi_ns_check_package_elements(info, elements + 20,
							ACPI_RTYPE_INTEGER, 1,
							0, 0, 20);
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_check_package_elements
 *
 * PARAMETERS:  info            - Method execution inक्रमmation block
 *              elements        - Poपूर्णांकer to the package elements array
 *              type1           - Object type क्रम first group
 *              count1          - Count क्रम first group
 *              type2           - Object type क्रम second group
 *              count2          - Count क्रम second group
 *              start_index     - Start of the first group of elements
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Check that all elements of a package are of the correct object
 *              type. Supports up to two groups of dअगरferent object types.
 *
 ******************************************************************************/

अटल acpi_status
acpi_ns_check_package_elements(काष्ठा acpi_evaluate_info *info,
			       जोड़ acpi_opeअक्रम_object **elements,
			       u8 type1,
			       u32 count1,
			       u8 type2, u32 count2, u32 start_index)
अणु
	जोड़ acpi_opeअक्रम_object **this_element = elements;
	acpi_status status;
	u32 i;

	ACPI_FUNCTION_TRACE(ns_check_package_elements);

	/*
	 * Up to two groups of package elements are supported by the data
	 * काष्ठाure. All elements in each group must be of the same type.
	 * The second group can have a count of zero.
	 */
	क्रम (i = 0; i < count1; i++) अणु
		status = acpi_ns_check_object_type(info, this_element,
						   type1, i + start_index);
		अगर (ACPI_FAILURE(status)) अणु
			वापस_ACPI_STATUS(status);
		पूर्ण

		this_element++;
	पूर्ण

	क्रम (i = 0; i < count2; i++) अणु
		status = acpi_ns_check_object_type(info, this_element,
						   type2,
						   (i + count1 + start_index));
		अगर (ACPI_FAILURE(status)) अणु
			वापस_ACPI_STATUS(status);
		पूर्ण

		this_element++;
	पूर्ण

	वापस_ACPI_STATUS(AE_OK);
पूर्ण
