<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: nsrepair - Repair क्रम objects वापसed by predefined methods
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
ACPI_MODULE_NAME("nsrepair")

/*******************************************************************************
 *
 * This module attempts to repair or convert objects वापसed by the
 * predefined methods to an object type that is expected, as per the ACPI
 * specअगरication. The need क्रम this code is dictated by the many machines that
 * वापस incorrect types क्रम the standard predefined methods. Perक्रमming these
 * conversions here, in one place, eliminates the need क्रम inभागidual ACPI
 * device drivers to करो the same. Note: Most of these conversions are dअगरferent
 * than the पूर्णांकernal object conversion routines used क्रम implicit object
 * conversion.
 *
 * The following conversions can be perक्रमmed as necessary:
 *
 * Integer -> String
 * Integer -> Buffer
 * String  -> Integer
 * String  -> Buffer
 * Buffer  -> Integer
 * Buffer  -> String
 * Buffer  -> Package of Integers
 * Package -> Package of one Package
 *
 * Additional conversions that are available:
 *  Convert a null वापस or zero वापस value to an end_tag descriptor
 *  Convert an ASCII string to a Unicode buffer
 *
 * An incorrect standalone object is wrapped with required outer package
 *
 * Additional possible repairs:
 * Required package elements that are शून्य replaced by Integer/String/Buffer
 *
 ******************************************************************************/
/* Local prototypes */
अटल स्थिर काष्ठा acpi_simple_repair_info *acpi_ns_match_simple_repair(काष्ठा
									 acpi_namespace_node
									 *node,
									 u32
									 वापस_btype,
									 u32
									 package_index);

/*
 * Special but simple repairs क्रम some names.
 *
 * 2nd argument: Unexpected types that can be repaired
 */
अटल स्थिर काष्ठा acpi_simple_repair_info acpi_object_repair_info[] = अणु
	/* Resource descriptor conversions */

	अणु"_CRS",
	 ACPI_RTYPE_INTEGER | ACPI_RTYPE_STRING | ACPI_RTYPE_BUFFER |
	 ACPI_RTYPE_NONE,
	 ACPI_NOT_PACKAGE_ELEMENT,
	 acpi_ns_convert_to_resourceपूर्ण,
	अणु"_DMA",
	 ACPI_RTYPE_INTEGER | ACPI_RTYPE_STRING | ACPI_RTYPE_BUFFER |
	 ACPI_RTYPE_NONE,
	 ACPI_NOT_PACKAGE_ELEMENT,
	 acpi_ns_convert_to_resourceपूर्ण,
	अणु"_PRS",
	 ACPI_RTYPE_INTEGER | ACPI_RTYPE_STRING | ACPI_RTYPE_BUFFER |
	 ACPI_RTYPE_NONE,
	 ACPI_NOT_PACKAGE_ELEMENT,
	 acpi_ns_convert_to_resourceपूर्ण,

	/* Object reference conversions */

	अणु"_DEP", ACPI_RTYPE_STRING, ACPI_ALL_PACKAGE_ELEMENTS,
	 acpi_ns_convert_to_referenceपूर्ण,

	/* Unicode conversions */

	अणु"_MLS", ACPI_RTYPE_STRING, 1,
	 acpi_ns_convert_to_unicodeपूर्ण,
	अणु"_STR", ACPI_RTYPE_STRING | ACPI_RTYPE_BUFFER,
	 ACPI_NOT_PACKAGE_ELEMENT,
	 acpi_ns_convert_to_unicodeपूर्ण,
	अणुअणु0, 0, 0, 0पूर्ण, 0, 0, शून्यपूर्ण	/* Table terminator */
पूर्ण;

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_simple_repair
 *
 * PARAMETERS:  info                - Method execution inक्रमmation block
 *              expected_btypes     - Object types expected
 *              package_index       - Index of object within parent package (अगर
 *                                    applicable - ACPI_NOT_PACKAGE_ELEMENT
 *                                    otherwise)
 *              वापस_object_ptr   - Poपूर्णांकer to the object वापसed from the
 *                                    evaluation of a method or object
 *
 * RETURN:      Status. AE_OK अगर repair was successful.
 *
 * DESCRIPTION: Attempt to repair/convert a वापस object of a type that was
 *              not expected.
 *
 ******************************************************************************/

acpi_status
acpi_ns_simple_repair(काष्ठा acpi_evaluate_info *info,
		      u32 expected_btypes,
		      u32 package_index,
		      जोड़ acpi_opeअक्रम_object **वापस_object_ptr)
अणु
	जोड़ acpi_opeअक्रम_object *वापस_object = *वापस_object_ptr;
	जोड़ acpi_opeअक्रम_object *new_object = शून्य;
	acpi_status status;
	स्थिर काष्ठा acpi_simple_repair_info *predefined;

	ACPI_FUNCTION_NAME(ns_simple_repair);

	/*
	 * Special repairs क्रम certain names that are in the repair table.
	 * Check अगर this name is in the list of repairable names.
	 */
	predefined = acpi_ns_match_simple_repair(info->node,
						 info->वापस_btype,
						 package_index);
	अगर (predefined) अणु
		अगर (!वापस_object) अणु
			ACPI_WARN_PREDEFINED((AE_INFO, info->full_pathname,
					      ACPI_WARN_ALWAYS,
					      "Missing expected return value"));
		पूर्ण

		status = predefined->object_converter(info->node, वापस_object,
						      &new_object);
		अगर (ACPI_FAILURE(status)) अणु

			/* A fatal error occurred during a conversion */

			ACPI_EXCEPTION((AE_INFO, status,
					"During return object analysis"));
			वापस (status);
		पूर्ण
		अगर (new_object) अणु
			जाओ object_repaired;
		पूर्ण
	पूर्ण

	/*
	 * Do not perक्रमm simple object repair unless the वापस type is not
	 * expected.
	 */
	अगर (info->वापस_btype & expected_btypes) अणु
		वापस (AE_OK);
	पूर्ण

	/*
	 * At this poपूर्णांक, we know that the type of the वापसed object was not
	 * one of the expected types क्रम this predefined name. Attempt to
	 * repair the object by converting it to one of the expected object
	 * types क्रम this predefined name.
	 */

	/*
	 * If there is no वापस value, check अगर we require a वापस value क्रम
	 * this predefined name. Either one वापस value is expected, or none,
	 * क्रम both methods and other objects.
	 *
	 * Try to fix अगर there was no वापस object. Warning अगर failed to fix.
	 */
	अगर (!वापस_object) अणु
		अगर (expected_btypes && (!(expected_btypes & ACPI_RTYPE_NONE))) अणु
			अगर (package_index != ACPI_NOT_PACKAGE_ELEMENT) अणु
				ACPI_WARN_PREDEFINED((AE_INFO,
						      info->full_pathname,
						      ACPI_WARN_ALWAYS,
						      "Found unexpected NULL package element"));

				status =
				    acpi_ns_repair_null_element(info,
								expected_btypes,
								package_index,
								वापस_object_ptr);
				अगर (ACPI_SUCCESS(status)) अणु
					वापस (AE_OK);	/* Repair was successful */
				पूर्ण
			पूर्ण अन्यथा अणु
				ACPI_WARN_PREDEFINED((AE_INFO,
						      info->full_pathname,
						      ACPI_WARN_ALWAYS,
						      "Missing expected return value"));
			पूर्ण

			वापस (AE_AML_NO_RETURN_VALUE);
		पूर्ण
	पूर्ण

	अगर (expected_btypes & ACPI_RTYPE_INTEGER) अणु
		status = acpi_ns_convert_to_पूर्णांकeger(वापस_object, &new_object);
		अगर (ACPI_SUCCESS(status)) अणु
			जाओ object_repaired;
		पूर्ण
	पूर्ण
	अगर (expected_btypes & ACPI_RTYPE_STRING) अणु
		status = acpi_ns_convert_to_string(वापस_object, &new_object);
		अगर (ACPI_SUCCESS(status)) अणु
			जाओ object_repaired;
		पूर्ण
	पूर्ण
	अगर (expected_btypes & ACPI_RTYPE_BUFFER) अणु
		status = acpi_ns_convert_to_buffer(वापस_object, &new_object);
		अगर (ACPI_SUCCESS(status)) अणु
			जाओ object_repaired;
		पूर्ण
	पूर्ण
	अगर (expected_btypes & ACPI_RTYPE_PACKAGE) अणु
		/*
		 * A package is expected. We will wrap the existing object with a
		 * new package object. It is often the हाल that अगर a variable-length
		 * package is required, but there is only a single object needed, the
		 * BIOS will वापस that object instead of wrapping it with a Package
		 * object. Note: after the wrapping, the package will be validated
		 * क्रम correct contents (expected object type or types).
		 */
		status =
		    acpi_ns_wrap_with_package(info, वापस_object, &new_object);
		अगर (ACPI_SUCCESS(status)) अणु
			/*
			 * The original object just had its reference count
			 * incremented क्रम being inserted पूर्णांकo the new package.
			 */
			*वापस_object_ptr = new_object;	/* New Package object */
			info->वापस_flags |= ACPI_OBJECT_REPAIRED;
			वापस (AE_OK);
		पूर्ण
	पूर्ण

	/* We cannot repair this object */

	वापस (AE_AML_OPERAND_TYPE);

object_repaired:

	/* Object was successfully repaired */

	अगर (package_index != ACPI_NOT_PACKAGE_ELEMENT) अणु

		/* Update reference count of new object */

		अगर (!(info->वापस_flags & ACPI_OBJECT_WRAPPED)) अणु
			new_object->common.reference_count =
			    वापस_object->common.reference_count;
		पूर्ण

		ACPI_DEBUG_PRINT((ACPI_DB_REPAIR,
				  "%s: Converted %s to expected %s at Package index %u\n",
				  info->full_pathname,
				  acpi_ut_get_object_type_name(वापस_object),
				  acpi_ut_get_object_type_name(new_object),
				  package_index));
	पूर्ण अन्यथा अणु
		ACPI_DEBUG_PRINT((ACPI_DB_REPAIR,
				  "%s: Converted %s to expected %s\n",
				  info->full_pathname,
				  acpi_ut_get_object_type_name(वापस_object),
				  acpi_ut_get_object_type_name(new_object)));
	पूर्ण

	/* Delete old object, install the new वापस object */

	acpi_ut_हटाओ_reference(वापस_object);
	*वापस_object_ptr = new_object;
	info->वापस_flags |= ACPI_OBJECT_REPAIRED;
	वापस (AE_OK);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_ns_match_simple_repair
 *
 * PARAMETERS:  node                - Namespace node क्रम the method/object
 *              वापस_btype        - Object type that was वापसed
 *              package_index       - Index of object within parent package (अगर
 *                                    applicable - ACPI_NOT_PACKAGE_ELEMENT
 *                                    otherwise)
 *
 * RETURN:      Poपूर्णांकer to entry in repair table. शून्य indicates not found.
 *
 * DESCRIPTION: Check an object name against the repairable object list.
 *
 *****************************************************************************/

अटल स्थिर काष्ठा acpi_simple_repair_info *acpi_ns_match_simple_repair(काष्ठा
									 acpi_namespace_node
									 *node,
									 u32
									 वापस_btype,
									 u32
									 package_index)
अणु
	स्थिर काष्ठा acpi_simple_repair_info *this_name;

	/* Search info table क्रम a repairable predefined method/object name */

	this_name = acpi_object_repair_info;
	जबतक (this_name->object_converter) अणु
		अगर (ACPI_COMPARE_NAMESEG(node->name.ascii, this_name->name)) अणु

			/* Check अगर we can actually repair this name/type combination */

			अगर ((वापस_btype & this_name->unexpected_btypes) &&
			    (this_name->package_index ==
			     ACPI_ALL_PACKAGE_ELEMENTS
			     || package_index == this_name->package_index)) अणु
				वापस (this_name);
			पूर्ण

			वापस (शून्य);
		पूर्ण

		this_name++;
	पूर्ण

	वापस (शून्य);		/* Name was not found in the repair table */
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_repair_null_element
 *
 * PARAMETERS:  info                - Method execution inक्रमmation block
 *              expected_btypes     - Object types expected
 *              package_index       - Index of object within parent package (अगर
 *                                    applicable - ACPI_NOT_PACKAGE_ELEMENT
 *                                    otherwise)
 *              वापस_object_ptr   - Poपूर्णांकer to the object वापसed from the
 *                                    evaluation of a method or object
 *
 * RETURN:      Status. AE_OK अगर repair was successful.
 *
 * DESCRIPTION: Attempt to repair a शून्य element of a वापसed Package object.
 *
 ******************************************************************************/

acpi_status
acpi_ns_repair_null_element(काष्ठा acpi_evaluate_info *info,
			    u32 expected_btypes,
			    u32 package_index,
			    जोड़ acpi_opeअक्रम_object **वापस_object_ptr)
अणु
	जोड़ acpi_opeअक्रम_object *वापस_object = *वापस_object_ptr;
	जोड़ acpi_opeअक्रम_object *new_object;

	ACPI_FUNCTION_NAME(ns_repair_null_element);

	/* No repair needed अगर वापस object is non-शून्य */

	अगर (वापस_object) अणु
		वापस (AE_OK);
	पूर्ण

	/*
	 * Attempt to repair a शून्य element of a Package object. This applies to
	 * predefined names that वापस a fixed-length package and each element
	 * is required. It करोes not apply to variable-length packages where शून्य
	 * elements are allowed, especially at the end of the package.
	 */
	अगर (expected_btypes & ACPI_RTYPE_INTEGER) अणु

		/* Need an पूर्णांकeger - create a zero-value पूर्णांकeger */

		new_object = acpi_ut_create_पूर्णांकeger_object((u64)0);
	पूर्ण अन्यथा अगर (expected_btypes & ACPI_RTYPE_STRING) अणु

		/* Need a string - create a शून्य string */

		new_object = acpi_ut_create_string_object(0);
	पूर्ण अन्यथा अगर (expected_btypes & ACPI_RTYPE_BUFFER) अणु

		/* Need a buffer - create a zero-length buffer */

		new_object = acpi_ut_create_buffer_object(0);
	पूर्ण अन्यथा अणु
		/* Error क्रम all other expected types */

		वापस (AE_AML_OPERAND_TYPE);
	पूर्ण

	अगर (!new_object) अणु
		वापस (AE_NO_MEMORY);
	पूर्ण

	/* Set the reference count according to the parent Package object */

	new_object->common.reference_count =
	    info->parent_package->common.reference_count;

	ACPI_DEBUG_PRINT((ACPI_DB_REPAIR,
			  "%s: Converted NULL package element to expected %s at index %u\n",
			  info->full_pathname,
			  acpi_ut_get_object_type_name(new_object),
			  package_index));

	*वापस_object_ptr = new_object;
	info->वापस_flags |= ACPI_OBJECT_REPAIRED;
	वापस (AE_OK);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_ns_हटाओ_null_elements
 *
 * PARAMETERS:  info                - Method execution inक्रमmation block
 *              package_type        - An acpi_वापस_package_types value
 *              obj_desc            - A Package object
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Remove all शून्य package elements from packages that contain
 *              a variable number of subpackages. For these types of
 *              packages, शून्य elements can be safely हटाओd.
 *
 *****************************************************************************/

व्योम
acpi_ns_हटाओ_null_elements(काष्ठा acpi_evaluate_info *info,
			     u8 package_type,
			     जोड़ acpi_opeअक्रम_object *obj_desc)
अणु
	जोड़ acpi_opeअक्रम_object **source;
	जोड़ acpi_opeअक्रम_object **dest;
	u32 count;
	u32 new_count;
	u32 i;

	ACPI_FUNCTION_NAME(ns_हटाओ_null_elements);

	/*
	 * We can safely हटाओ all शून्य elements from these package types:
	 * PTYPE1_VAR packages contain a variable number of simple data types.
	 * PTYPE2 packages contain a variable number of subpackages.
	 */
	चयन (package_type) अणु
	हाल ACPI_PTYPE1_VAR:
	हाल ACPI_PTYPE2:
	हाल ACPI_PTYPE2_COUNT:
	हाल ACPI_PTYPE2_PKG_COUNT:
	हाल ACPI_PTYPE2_FIXED:
	हाल ACPI_PTYPE2_MIN:
	हाल ACPI_PTYPE2_REV_FIXED:
	हाल ACPI_PTYPE2_FIX_VAR:
		अवरोध;

	शेष:
	हाल ACPI_PTYPE2_VAR_VAR:
	हाल ACPI_PTYPE1_FIXED:
	हाल ACPI_PTYPE1_OPTION:
		वापस;
	पूर्ण

	count = obj_desc->package.count;
	new_count = count;

	source = obj_desc->package.elements;
	dest = source;

	/* Examine all elements of the package object, हटाओ nulls */

	क्रम (i = 0; i < count; i++) अणु
		अगर (!*source) अणु
			new_count--;
		पूर्ण अन्यथा अणु
			*dest = *source;
			dest++;
		पूर्ण

		source++;
	पूर्ण

	/* Update parent package अगर any null elements were हटाओd */

	अगर (new_count < count) अणु
		ACPI_DEBUG_PRINT((ACPI_DB_REPAIR,
				  "%s: Found and removed %u NULL elements\n",
				  info->full_pathname, (count - new_count)));

		/* शून्य terminate list and update the package count */

		*dest = शून्य;
		obj_desc->package.count = new_count;
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_wrap_with_package
 *
 * PARAMETERS:  info                - Method execution inक्रमmation block
 *              original_object     - Poपूर्णांकer to the object to repair.
 *              obj_desc_ptr        - The new package object is वापसed here
 *
 * RETURN:      Status, new object in *obj_desc_ptr
 *
 * DESCRIPTION: Repair a common problem with objects that are defined to
 *              वापस a variable-length Package of sub-objects. If there is
 *              only one sub-object, some BIOS code mistakenly simply declares
 *              the single object instead of a Package with one sub-object.
 *              This function attempts to repair this error by wrapping a
 *              Package object around the original object, creating the
 *              correct and expected Package with one sub-object.
 *
 *              Names that can be repaired in this manner include:
 *              _ALR, _CSD, _HPX, _MLS, _PLD, _PRT, _PSS, _TRT, _TSS,
 *              _BCL, _DOD, _FIX, _Sx
 *
 ******************************************************************************/

acpi_status
acpi_ns_wrap_with_package(काष्ठा acpi_evaluate_info *info,
			  जोड़ acpi_opeअक्रम_object *original_object,
			  जोड़ acpi_opeअक्रम_object **obj_desc_ptr)
अणु
	जोड़ acpi_opeअक्रम_object *pkg_obj_desc;

	ACPI_FUNCTION_NAME(ns_wrap_with_package);

	/*
	 * Create the new outer package and populate it. The new
	 * package will have a single element, the lone sub-object.
	 */
	pkg_obj_desc = acpi_ut_create_package_object(1);
	अगर (!pkg_obj_desc) अणु
		वापस (AE_NO_MEMORY);
	पूर्ण

	pkg_obj_desc->package.elements[0] = original_object;

	ACPI_DEBUG_PRINT((ACPI_DB_REPAIR,
			  "%s: Wrapped %s with expected Package object\n",
			  info->full_pathname,
			  acpi_ut_get_object_type_name(original_object)));

	/* Return the new object in the object poपूर्णांकer */

	*obj_desc_ptr = pkg_obj_desc;
	info->वापस_flags |= ACPI_OBJECT_REPAIRED | ACPI_OBJECT_WRAPPED;
	वापस (AE_OK);
पूर्ण
