<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: nsrepair2 - Repair क्रम objects वापसed by specअगरic
 *                          predefined methods
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acnamesp.h"

#घोषणा _COMPONENT          ACPI_NAMESPACE
ACPI_MODULE_NAME("nsrepair2")

/*
 * Inक्रमmation काष्ठाure and handler क्रम ACPI predefined names that can
 * be repaired on a per-name basis.
 */
प्रकार
acpi_status (*acpi_repair_function) (काष्ठा acpi_evaluate_info * info,
				     जोड़ acpi_opeअक्रम_object **
				     वापस_object_ptr);

प्रकार काष्ठा acpi_repair_info अणु
	अक्षर name[ACPI_NAMESEG_SIZE];
	acpi_repair_function repair_function;

पूर्ण acpi_repair_info;

/* Local prototypes */

अटल स्थिर काष्ठा acpi_repair_info *acpi_ns_match_complex_repair(काष्ठा
								   acpi_namespace_node
								   *node);

अटल acpi_status
acpi_ns_repair_ALR(काष्ठा acpi_evaluate_info *info,
		   जोड़ acpi_opeअक्रम_object **वापस_object_ptr);

अटल acpi_status
acpi_ns_repair_CID(काष्ठा acpi_evaluate_info *info,
		   जोड़ acpi_opeअक्रम_object **वापस_object_ptr);

अटल acpi_status
acpi_ns_repair_CST(काष्ठा acpi_evaluate_info *info,
		   जोड़ acpi_opeअक्रम_object **वापस_object_ptr);

अटल acpi_status
acpi_ns_repair_FDE(काष्ठा acpi_evaluate_info *info,
		   जोड़ acpi_opeअक्रम_object **वापस_object_ptr);

अटल acpi_status
acpi_ns_repair_HID(काष्ठा acpi_evaluate_info *info,
		   जोड़ acpi_opeअक्रम_object **वापस_object_ptr);

अटल acpi_status
acpi_ns_repair_PRT(काष्ठा acpi_evaluate_info *info,
		   जोड़ acpi_opeअक्रम_object **वापस_object_ptr);

अटल acpi_status
acpi_ns_repair_PSS(काष्ठा acpi_evaluate_info *info,
		   जोड़ acpi_opeअक्रम_object **वापस_object_ptr);

अटल acpi_status
acpi_ns_repair_TSS(काष्ठा acpi_evaluate_info *info,
		   जोड़ acpi_opeअक्रम_object **वापस_object_ptr);

अटल acpi_status
acpi_ns_check_sorted_list(काष्ठा acpi_evaluate_info *info,
			  जोड़ acpi_opeअक्रम_object *वापस_object,
			  u32 start_index,
			  u32 expected_count,
			  u32 sort_index,
			  u8 sort_direction, अक्षर *sort_key_name);

/* Values क्रम sort_direction above */

#घोषणा ACPI_SORT_ASCENDING     0
#घोषणा ACPI_SORT_DESCENDING    1

अटल व्योम
acpi_ns_हटाओ_element(जोड़ acpi_opeअक्रम_object *obj_desc, u32 index);

अटल व्योम
acpi_ns_sort_list(जोड़ acpi_opeअक्रम_object **elements,
		  u32 count, u32 index, u8 sort_direction);

/*
 * This table contains the names of the predefined methods क्रम which we can
 * perक्रमm more complex repairs.
 *
 * As necessary:
 *
 * _ALR: Sort the list ascending by ambient_illuminance
 * _CID: Strings: upperहाल all, हटाओ any leading asterisk
 * _CST: Sort the list ascending by C state type
 * _FDE: Convert Buffer of BYTEs to a Buffer of DWORDs
 * _GTM: Convert Buffer of BYTEs to a Buffer of DWORDs
 * _HID: Strings: upperहाल all, हटाओ any leading asterisk
 * _PRT: Fix reversed source_name and source_index
 * _PSS: Sort the list descending by Power
 * _TSS: Sort the list descending by Power
 *
 * Names that must be packages, but cannot be sorted:
 *
 * _BCL: Values are tied to the Package index where they appear, and cannot
 * be moved or sorted. These index values are used क्रम _BQC and _BCM.
 * However, we can fix the हाल where a buffer is वापसed, by converting
 * it to a Package of पूर्णांकegers.
 */
अटल स्थिर काष्ठा acpi_repair_info acpi_ns_repairable_names[] = अणु
	अणु"_ALR", acpi_ns_repair_ALRपूर्ण,
	अणु"_CID", acpi_ns_repair_CIDपूर्ण,
	अणु"_CST", acpi_ns_repair_CSTपूर्ण,
	अणु"_FDE", acpi_ns_repair_FDEपूर्ण,
	अणु"_GTM", acpi_ns_repair_FDEपूर्ण,	/* _GTM has same repair as _FDE */
	अणु"_HID", acpi_ns_repair_HIDपूर्ण,
	अणु"_PRT", acpi_ns_repair_PRTपूर्ण,
	अणु"_PSS", acpi_ns_repair_PSSपूर्ण,
	अणु"_TSS", acpi_ns_repair_TSSपूर्ण,
	अणुअणु0, 0, 0, 0पूर्ण, शून्यपूर्ण	/* Table terminator */
पूर्ण;

#घोषणा ACPI_FDE_FIELD_COUNT        5
#घोषणा ACPI_FDE_BYTE_BUFFER_SIZE   5
#घोषणा ACPI_FDE_DWORD_BUFFER_SIZE  (ACPI_FDE_FIELD_COUNT * (u32) माप (u32))

/******************************************************************************
 *
 * FUNCTION:    acpi_ns_complex_repairs
 *
 * PARAMETERS:  info                - Method execution inक्रमmation block
 *              node                - Namespace node क्रम the method/object
 *              validate_status     - Original status of earlier validation
 *              वापस_object_ptr   - Poपूर्णांकer to the object वापसed from the
 *                                    evaluation of a method or object
 *
 * RETURN:      Status. AE_OK अगर repair was successful. If name is not
 *              matched, validate_status is वापसed.
 *
 * DESCRIPTION: Attempt to repair/convert a वापस object of a type that was
 *              not expected.
 *
 *****************************************************************************/

acpi_status
acpi_ns_complex_repairs(काष्ठा acpi_evaluate_info *info,
			काष्ठा acpi_namespace_node *node,
			acpi_status validate_status,
			जोड़ acpi_opeअक्रम_object **वापस_object_ptr)
अणु
	स्थिर काष्ठा acpi_repair_info *predefined;
	acpi_status status;

	ACPI_FUNCTION_TRACE(ns_complex_repairs);

	/* Check अगर this name is in the list of repairable names */

	predefined = acpi_ns_match_complex_repair(node);
	अगर (!predefined) अणु
		वापस_ACPI_STATUS(validate_status);
	पूर्ण

	status = predefined->repair_function(info, वापस_object_ptr);
	वापस_ACPI_STATUS(status);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_ns_match_complex_repair
 *
 * PARAMETERS:  node                - Namespace node क्रम the method/object
 *
 * RETURN:      Poपूर्णांकer to entry in repair table. शून्य indicates not found.
 *
 * DESCRIPTION: Check an object name against the repairable object list.
 *
 *****************************************************************************/

अटल स्थिर काष्ठा acpi_repair_info *acpi_ns_match_complex_repair(काष्ठा
								   acpi_namespace_node
								   *node)
अणु
	स्थिर काष्ठा acpi_repair_info *this_name;

	/* Search info table क्रम a repairable predefined method/object name */

	this_name = acpi_ns_repairable_names;
	जबतक (this_name->repair_function) अणु
		अगर (ACPI_COMPARE_NAMESEG(node->name.ascii, this_name->name)) अणु
			वापस (this_name);
		पूर्ण

		this_name++;
	पूर्ण

	वापस (शून्य);		/* Not found */
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_ns_repair_ALR
 *
 * PARAMETERS:  info                - Method execution inक्रमmation block
 *              वापस_object_ptr   - Poपूर्णांकer to the object वापसed from the
 *                                    evaluation of a method or object
 *
 * RETURN:      Status. AE_OK अगर object is OK or was repaired successfully
 *
 * DESCRIPTION: Repair क्रम the _ALR object. If necessary, sort the object list
 *              ascending by the ambient illuminance values.
 *
 *****************************************************************************/

अटल acpi_status
acpi_ns_repair_ALR(काष्ठा acpi_evaluate_info *info,
		   जोड़ acpi_opeअक्रम_object **वापस_object_ptr)
अणु
	जोड़ acpi_opeअक्रम_object *वापस_object = *वापस_object_ptr;
	acpi_status status;

	status = acpi_ns_check_sorted_list(info, वापस_object, 0, 2, 1,
					   ACPI_SORT_ASCENDING,
					   "AmbientIlluminance");

	वापस (status);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_ns_repair_FDE
 *
 * PARAMETERS:  info                - Method execution inक्रमmation block
 *              वापस_object_ptr   - Poपूर्णांकer to the object वापसed from the
 *                                    evaluation of a method or object
 *
 * RETURN:      Status. AE_OK अगर object is OK or was repaired successfully
 *
 * DESCRIPTION: Repair क्रम the _FDE and _GTM objects. The expected वापस
 *              value is a Buffer of 5 DWORDs. This function repairs a common
 *              problem where the वापस value is a Buffer of BYTEs, not
 *              DWORDs.
 *
 *****************************************************************************/

अटल acpi_status
acpi_ns_repair_FDE(काष्ठा acpi_evaluate_info *info,
		   जोड़ acpi_opeअक्रम_object **वापस_object_ptr)
अणु
	जोड़ acpi_opeअक्रम_object *वापस_object = *वापस_object_ptr;
	जोड़ acpi_opeअक्रम_object *buffer_object;
	u8 *byte_buffer;
	u32 *dword_buffer;
	u32 i;

	ACPI_FUNCTION_NAME(ns_repair_FDE);

	चयन (वापस_object->common.type) अणु
	हाल ACPI_TYPE_BUFFER:

		/* This is the expected type. Length should be (at least) 5 DWORDs */

		अगर (वापस_object->buffer.length >= ACPI_FDE_DWORD_BUFFER_SIZE) अणु
			वापस (AE_OK);
		पूर्ण

		/* We can only repair अगर we have exactly 5 BYTEs */

		अगर (वापस_object->buffer.length != ACPI_FDE_BYTE_BUFFER_SIZE) अणु
			ACPI_WARN_PREDEFINED((AE_INFO,
					      info->full_pathname,
					      info->node_flags,
					      "Incorrect return buffer length %u, expected %u",
					      वापस_object->buffer.length,
					      ACPI_FDE_DWORD_BUFFER_SIZE));

			वापस (AE_AML_OPERAND_TYPE);
		पूर्ण

		/* Create the new (larger) buffer object */

		buffer_object =
		    acpi_ut_create_buffer_object(ACPI_FDE_DWORD_BUFFER_SIZE);
		अगर (!buffer_object) अणु
			वापस (AE_NO_MEMORY);
		पूर्ण

		/* Expand each byte to a DWORD */

		byte_buffer = वापस_object->buffer.poपूर्णांकer;
		dword_buffer = ACPI_CAST_PTR(u32,
					     buffer_object->buffer.poपूर्णांकer);

		क्रम (i = 0; i < ACPI_FDE_FIELD_COUNT; i++) अणु
			*dword_buffer = (u32) *byte_buffer;
			dword_buffer++;
			byte_buffer++;
		पूर्ण

		ACPI_DEBUG_PRINT((ACPI_DB_REPAIR,
				  "%s Expanded Byte Buffer to expected DWord Buffer\n",
				  info->full_pathname));
		अवरोध;

	शेष:

		वापस (AE_AML_OPERAND_TYPE);
	पूर्ण

	/* Delete the original वापस object, वापस the new buffer object */

	acpi_ut_हटाओ_reference(वापस_object);
	*वापस_object_ptr = buffer_object;

	info->वापस_flags |= ACPI_OBJECT_REPAIRED;
	वापस (AE_OK);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_ns_repair_CID
 *
 * PARAMETERS:  info                - Method execution inक्रमmation block
 *              वापस_object_ptr   - Poपूर्णांकer to the object वापसed from the
 *                                    evaluation of a method or object
 *
 * RETURN:      Status. AE_OK अगर object is OK or was repaired successfully
 *
 * DESCRIPTION: Repair क्रम the _CID object. If a string, ensure that all
 *              letters are upperहाल and that there is no leading asterisk.
 *              If a Package, ensure same क्रम all string elements.
 *
 *****************************************************************************/

अटल acpi_status
acpi_ns_repair_CID(काष्ठा acpi_evaluate_info *info,
		   जोड़ acpi_opeअक्रम_object **वापस_object_ptr)
अणु
	acpi_status status;
	जोड़ acpi_opeअक्रम_object *वापस_object = *वापस_object_ptr;
	जोड़ acpi_opeअक्रम_object **element_ptr;
	जोड़ acpi_opeअक्रम_object *original_element;
	u16 original_ref_count;
	u32 i;

	ACPI_FUNCTION_TRACE(ns_repair_CID);

	/* Check क्रम _CID as a simple string */

	अगर (वापस_object->common.type == ACPI_TYPE_STRING) अणु
		status = acpi_ns_repair_HID(info, वापस_object_ptr);
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Exit अगर not a Package */

	अगर (वापस_object->common.type != ACPI_TYPE_PACKAGE) अणु
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	/* Examine each element of the _CID package */

	element_ptr = वापस_object->package.elements;
	क्रम (i = 0; i < वापस_object->package.count; i++) अणु
		original_element = *element_ptr;
		original_ref_count = original_element->common.reference_count;

		status = acpi_ns_repair_HID(info, element_ptr);
		अगर (ACPI_FAILURE(status)) अणु
			वापस_ACPI_STATUS(status);
		पूर्ण

		अगर (original_element != *element_ptr) अणु

			/* Update reference count of new object */

			(*element_ptr)->common.reference_count =
			    original_ref_count;
		पूर्ण

		element_ptr++;
	पूर्ण

	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_ns_repair_CST
 *
 * PARAMETERS:  info                - Method execution inक्रमmation block
 *              वापस_object_ptr   - Poपूर्णांकer to the object वापसed from the
 *                                    evaluation of a method or object
 *
 * RETURN:      Status. AE_OK अगर object is OK or was repaired successfully
 *
 * DESCRIPTION: Repair क्रम the _CST object:
 *              1. Sort the list ascending by C state type
 *              2. Ensure type cannot be zero
 *              3. A subpackage count of zero means _CST is meaningless
 *              4. Count must match the number of C state subpackages
 *
 *****************************************************************************/

अटल acpi_status
acpi_ns_repair_CST(काष्ठा acpi_evaluate_info *info,
		   जोड़ acpi_opeअक्रम_object **वापस_object_ptr)
अणु
	जोड़ acpi_opeअक्रम_object *वापस_object = *वापस_object_ptr;
	जोड़ acpi_opeअक्रम_object **outer_elements;
	u32 outer_element_count;
	जोड़ acpi_opeअक्रम_object *obj_desc;
	acpi_status status;
	u8 removing;
	u32 i;

	ACPI_FUNCTION_NAME(ns_repair_CST);

	/*
	 * Check अगर the C-state type values are proportional.
	 */
	outer_element_count = वापस_object->package.count - 1;
	i = 0;
	जबतक (i < outer_element_count) अणु
		outer_elements = &वापस_object->package.elements[i + 1];
		removing = FALSE;

		अगर ((*outer_elements)->package.count == 0) अणु
			ACPI_WARN_PREDEFINED((AE_INFO,
					      info->full_pathname,
					      info->node_flags,
					      "SubPackage[%u] - removing entry due to zero count",
					      i));
			removing = TRUE;
			जाओ हटाओ_element;
		पूर्ण

		obj_desc = (*outer_elements)->package.elements[1];	/* Index1 = Type */
		अगर ((u32)obj_desc->पूर्णांकeger.value == 0) अणु
			ACPI_WARN_PREDEFINED((AE_INFO,
					      info->full_pathname,
					      info->node_flags,
					      "SubPackage[%u] - removing entry due to invalid Type(0)",
					      i));
			removing = TRUE;
		पूर्ण

हटाओ_element:
		अगर (removing) अणु
			acpi_ns_हटाओ_element(वापस_object, i + 1);
			outer_element_count--;
		पूर्ण अन्यथा अणु
			i++;
		पूर्ण
	पूर्ण

	/* Update top-level package count, Type "Integer" checked अन्यथाwhere */

	obj_desc = वापस_object->package.elements[0];
	obj_desc->पूर्णांकeger.value = outer_element_count;

	/*
	 * Entries (subpackages) in the _CST Package must be sorted by the
	 * C-state type, in ascending order.
	 */
	status = acpi_ns_check_sorted_list(info, वापस_object, 1, 4, 1,
					   ACPI_SORT_ASCENDING, "C-State Type");
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	वापस (AE_OK);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_ns_repair_HID
 *
 * PARAMETERS:  info                - Method execution inक्रमmation block
 *              वापस_object_ptr   - Poपूर्णांकer to the object वापसed from the
 *                                    evaluation of a method or object
 *
 * RETURN:      Status. AE_OK अगर object is OK or was repaired successfully
 *
 * DESCRIPTION: Repair क्रम the _HID object. If a string, ensure that all
 *              letters are upperहाल and that there is no leading asterisk.
 *
 *****************************************************************************/

अटल acpi_status
acpi_ns_repair_HID(काष्ठा acpi_evaluate_info *info,
		   जोड़ acpi_opeअक्रम_object **वापस_object_ptr)
अणु
	जोड़ acpi_opeअक्रम_object *वापस_object = *वापस_object_ptr;
	जोड़ acpi_opeअक्रम_object *new_string;
	अक्षर *source;
	अक्षर *dest;

	ACPI_FUNCTION_NAME(ns_repair_HID);

	/* We only care about string _HID objects (not पूर्णांकegers) */

	अगर (वापस_object->common.type != ACPI_TYPE_STRING) अणु
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	अगर (वापस_object->string.length == 0) अणु
		ACPI_WARN_PREDEFINED((AE_INFO,
				      info->full_pathname, info->node_flags,
				      "Invalid zero-length _HID or _CID string"));

		/* Return AE_OK anyway, let driver handle it */

		info->वापस_flags |= ACPI_OBJECT_REPAIRED;
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	/* It is simplest to always create a new string object */

	new_string = acpi_ut_create_string_object(वापस_object->string.length);
	अगर (!new_string) अणु
		वापस_ACPI_STATUS(AE_NO_MEMORY);
	पूर्ण

	/*
	 * Remove a leading asterisk अगर present. For some unknown reason, there
	 * are many machines in the field that contains IDs like this.
	 *
	 * Examples: "*PNP0C03", "*ACPI0003"
	 */
	source = वापस_object->string.poपूर्णांकer;
	अगर (*source == '*') अणु
		source++;
		new_string->string.length--;

		ACPI_DEBUG_PRINT((ACPI_DB_REPAIR,
				  "%s: Removed invalid leading asterisk\n",
				  info->full_pathname));
	पूर्ण

	/*
	 * Copy and upperहाल the string. From the ACPI 5.0 specअगरication:
	 *
	 * A valid PNP ID must be of the क्रमm "AAA####" where A is an upperहाल
	 * letter and # is a hex digit. A valid ACPI ID must be of the क्रमm
	 * "NNNN####" where N is an upperहाल letter or decimal digit, and
	 * # is a hex digit.
	 */
	क्रम (dest = new_string->string.poपूर्णांकer; *source; dest++, source++) अणु
		*dest = (अक्षर)बड़े((पूर्णांक)*source);
	पूर्ण

	acpi_ut_हटाओ_reference(वापस_object);
	*वापस_object_ptr = new_string;
	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_ns_repair_PRT
 *
 * PARAMETERS:  info                - Method execution inक्रमmation block
 *              वापस_object_ptr   - Poपूर्णांकer to the object वापसed from the
 *                                    evaluation of a method or object
 *
 * RETURN:      Status. AE_OK अगर object is OK or was repaired successfully
 *
 * DESCRIPTION: Repair क्रम the _PRT object. If necessary, fix reversed
 *              source_name and source_index field, a common BIOS bug.
 *
 *****************************************************************************/

अटल acpi_status
acpi_ns_repair_PRT(काष्ठा acpi_evaluate_info *info,
		   जोड़ acpi_opeअक्रम_object **वापस_object_ptr)
अणु
	जोड़ acpi_opeअक्रम_object *package_object = *वापस_object_ptr;
	जोड़ acpi_opeअक्रम_object **top_object_list;
	जोड़ acpi_opeअक्रम_object **sub_object_list;
	जोड़ acpi_opeअक्रम_object *obj_desc;
	जोड़ acpi_opeअक्रम_object *sub_package;
	u32 element_count;
	u32 index;

	/* Each element in the _PRT package is a subpackage */

	top_object_list = package_object->package.elements;
	element_count = package_object->package.count;

	/* Examine each subpackage */

	क्रम (index = 0; index < element_count; index++, top_object_list++) अणु
		sub_package = *top_object_list;
		sub_object_list = sub_package->package.elements;

		/* Check क्रम minimum required element count */

		अगर (sub_package->package.count < 4) अणु
			जारी;
		पूर्ण

		/*
		 * If the BIOS has erroneously reversed the _PRT source_name (index 2)
		 * and the source_index (index 3), fix it. _PRT is important enough to
		 * workaround this BIOS error. This also provides compatibility with
		 * other ACPI implementations.
		 */
		obj_desc = sub_object_list[3];
		अगर (!obj_desc || (obj_desc->common.type != ACPI_TYPE_INTEGER)) अणु
			sub_object_list[3] = sub_object_list[2];
			sub_object_list[2] = obj_desc;
			info->वापस_flags |= ACPI_OBJECT_REPAIRED;

			ACPI_WARN_PREDEFINED((AE_INFO,
					      info->full_pathname,
					      info->node_flags,
					      "PRT[%X]: Fixed reversed SourceName and SourceIndex",
					      index));
		पूर्ण
	पूर्ण

	वापस (AE_OK);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_ns_repair_PSS
 *
 * PARAMETERS:  info                - Method execution inक्रमmation block
 *              वापस_object_ptr   - Poपूर्णांकer to the object वापसed from the
 *                                    evaluation of a method or object
 *
 * RETURN:      Status. AE_OK अगर object is OK or was repaired successfully
 *
 * DESCRIPTION: Repair क्रम the _PSS object. If necessary, sort the object list
 *              by the CPU frequencies. Check that the घातer dissipation values
 *              are all proportional to CPU frequency (i.e., sorting by
 *              frequency should be the same as sorting by घातer.)
 *
 *****************************************************************************/

अटल acpi_status
acpi_ns_repair_PSS(काष्ठा acpi_evaluate_info *info,
		   जोड़ acpi_opeअक्रम_object **वापस_object_ptr)
अणु
	जोड़ acpi_opeअक्रम_object *वापस_object = *वापस_object_ptr;
	जोड़ acpi_opeअक्रम_object **outer_elements;
	u32 outer_element_count;
	जोड़ acpi_opeअक्रम_object **elements;
	जोड़ acpi_opeअक्रम_object *obj_desc;
	u32 previous_value;
	acpi_status status;
	u32 i;

	/*
	 * Entries (subpackages) in the _PSS Package must be sorted by घातer
	 * dissipation, in descending order. If it appears that the list is
	 * incorrectly sorted, sort it. We sort by cpu_frequency, since this
	 * should be proportional to the घातer.
	 */
	status = acpi_ns_check_sorted_list(info, वापस_object, 0, 6, 0,
					   ACPI_SORT_DESCENDING,
					   "CpuFrequency");
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	/*
	 * We now know the list is correctly sorted by CPU frequency. Check अगर
	 * the घातer dissipation values are proportional.
	 */
	previous_value = ACPI_UINT32_MAX;
	outer_elements = वापस_object->package.elements;
	outer_element_count = वापस_object->package.count;

	क्रम (i = 0; i < outer_element_count; i++) अणु
		elements = (*outer_elements)->package.elements;
		obj_desc = elements[1];	/* Index1 = घातer_dissipation */

		अगर ((u32)obj_desc->पूर्णांकeger.value > previous_value) अणु
			ACPI_WARN_PREDEFINED((AE_INFO,
					      info->full_pathname,
					      info->node_flags,
					      "SubPackage[%u,%u] - suspicious power dissipation values",
					      i - 1, i));
		पूर्ण

		previous_value = (u32) obj_desc->पूर्णांकeger.value;
		outer_elements++;
	पूर्ण

	वापस (AE_OK);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_ns_repair_TSS
 *
 * PARAMETERS:  info                - Method execution inक्रमmation block
 *              वापस_object_ptr   - Poपूर्णांकer to the object वापसed from the
 *                                    evaluation of a method or object
 *
 * RETURN:      Status. AE_OK अगर object is OK or was repaired successfully
 *
 * DESCRIPTION: Repair क्रम the _TSS object. If necessary, sort the object list
 *              descending by the घातer dissipation values.
 *
 *****************************************************************************/

अटल acpi_status
acpi_ns_repair_TSS(काष्ठा acpi_evaluate_info *info,
		   जोड़ acpi_opeअक्रम_object **वापस_object_ptr)
अणु
	जोड़ acpi_opeअक्रम_object *वापस_object = *वापस_object_ptr;
	acpi_status status;
	काष्ठा acpi_namespace_node *node;

	/*
	 * We can only sort the _TSS वापस package अगर there is no _PSS in the
	 * same scope. This is because अगर _PSS is present, the ACPI specअगरication
	 * dictates that the _TSS Power Dissipation field is to be ignored, and
	 * thereक्रमe some BIOSs leave garbage values in the _TSS Power field(s).
	 * In this हाल, it is best to just वापस the _TSS package as-is.
	 * (May, 2011)
	 */
	status = acpi_ns_get_node(info->node, "^_PSS",
				  ACPI_NS_NO_UPSEARCH, &node);
	अगर (ACPI_SUCCESS(status)) अणु
		वापस (AE_OK);
	पूर्ण

	status = acpi_ns_check_sorted_list(info, वापस_object, 0, 5, 1,
					   ACPI_SORT_DESCENDING,
					   "PowerDissipation");

	वापस (status);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_ns_check_sorted_list
 *
 * PARAMETERS:  info                - Method execution inक्रमmation block
 *              वापस_object       - Poपूर्णांकer to the top-level वापसed object
 *              start_index         - Index of the first subpackage
 *              expected_count      - Minimum length of each subpackage
 *              sort_index          - Subpackage entry to sort on
 *              sort_direction      - Ascending or descending
 *              sort_key_name       - Name of the sort_index field
 *
 * RETURN:      Status. AE_OK अगर the list is valid and is sorted correctly or
 *              has been repaired by sorting the list.
 *
 * DESCRIPTION: Check अगर the package list is valid and sorted correctly by the
 *              sort_index. If not, then sort the list.
 *
 *****************************************************************************/

अटल acpi_status
acpi_ns_check_sorted_list(काष्ठा acpi_evaluate_info *info,
			  जोड़ acpi_opeअक्रम_object *वापस_object,
			  u32 start_index,
			  u32 expected_count,
			  u32 sort_index,
			  u8 sort_direction, अक्षर *sort_key_name)
अणु
	u32 outer_element_count;
	जोड़ acpi_opeअक्रम_object **outer_elements;
	जोड़ acpi_opeअक्रम_object **elements;
	जोड़ acpi_opeअक्रम_object *obj_desc;
	u32 i;
	u32 previous_value;

	ACPI_FUNCTION_NAME(ns_check_sorted_list);

	/* The top-level object must be a package */

	अगर (वापस_object->common.type != ACPI_TYPE_PACKAGE) अणु
		वापस (AE_AML_OPERAND_TYPE);
	पूर्ण

	/*
	 * NOTE: assumes list of subpackages contains no शून्य elements.
	 * Any शून्य elements should have been हटाओd by earlier call
	 * to acpi_ns_हटाओ_null_elements.
	 */
	outer_element_count = वापस_object->package.count;
	अगर (!outer_element_count || start_index >= outer_element_count) अणु
		वापस (AE_AML_PACKAGE_LIMIT);
	पूर्ण

	outer_elements = &वापस_object->package.elements[start_index];
	outer_element_count -= start_index;

	previous_value = 0;
	अगर (sort_direction == ACPI_SORT_DESCENDING) अणु
		previous_value = ACPI_UINT32_MAX;
	पूर्ण

	/* Examine each subpackage */

	क्रम (i = 0; i < outer_element_count; i++) अणु

		/* Each element of the top-level package must also be a package */

		अगर ((*outer_elements)->common.type != ACPI_TYPE_PACKAGE) अणु
			वापस (AE_AML_OPERAND_TYPE);
		पूर्ण

		/* Each subpackage must have the minimum length */

		अगर ((*outer_elements)->package.count < expected_count) अणु
			वापस (AE_AML_PACKAGE_LIMIT);
		पूर्ण

		elements = (*outer_elements)->package.elements;
		obj_desc = elements[sort_index];

		अगर (obj_desc->common.type != ACPI_TYPE_INTEGER) अणु
			वापस (AE_AML_OPERAND_TYPE);
		पूर्ण

		/*
		 * The list must be sorted in the specअगरied order. If we detect a
		 * discrepancy, sort the entire list.
		 */
		अगर (((sort_direction == ACPI_SORT_ASCENDING) &&
		     (obj_desc->पूर्णांकeger.value < previous_value)) ||
		    ((sort_direction == ACPI_SORT_DESCENDING) &&
		     (obj_desc->पूर्णांकeger.value > previous_value))) अणु
			acpi_ns_sort_list(&वापस_object->package.
					  elements[start_index],
					  outer_element_count, sort_index,
					  sort_direction);

			info->वापस_flags |= ACPI_OBJECT_REPAIRED;

			ACPI_DEBUG_PRINT((ACPI_DB_REPAIR,
					  "%s: Repaired unsorted list - now sorted by %s\n",
					  info->full_pathname, sort_key_name));
			वापस (AE_OK);
		पूर्ण

		previous_value = (u32) obj_desc->पूर्णांकeger.value;
		outer_elements++;
	पूर्ण

	वापस (AE_OK);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_ns_sort_list
 *
 * PARAMETERS:  elements            - Package object element list
 *              count               - Element count क्रम above
 *              index               - Sort by which package element
 *              sort_direction      - Ascending or Descending sort
 *
 * RETURN:      None
 *
 * DESCRIPTION: Sort the objects that are in a package element list.
 *
 * NOTE: Assumes that all शून्य elements have been हटाओd from the package,
 *       and that all elements have been verअगरied to be of type Integer.
 *
 *****************************************************************************/

अटल व्योम
acpi_ns_sort_list(जोड़ acpi_opeअक्रम_object **elements,
		  u32 count, u32 index, u8 sort_direction)
अणु
	जोड़ acpi_opeअक्रम_object *obj_desc1;
	जोड़ acpi_opeअक्रम_object *obj_desc2;
	जोड़ acpi_opeअक्रम_object *temp_obj;
	u32 i;
	u32 j;

	/* Simple bubble sort */

	क्रम (i = 1; i < count; i++) अणु
		क्रम (j = (count - 1); j >= i; j--) अणु
			obj_desc1 = elements[j - 1]->package.elements[index];
			obj_desc2 = elements[j]->package.elements[index];

			अगर (((sort_direction == ACPI_SORT_ASCENDING) &&
			     (obj_desc1->पूर्णांकeger.value >
			      obj_desc2->पूर्णांकeger.value))
			    || ((sort_direction == ACPI_SORT_DESCENDING)
				&& (obj_desc1->पूर्णांकeger.value <
				    obj_desc2->पूर्णांकeger.value))) अणु
				temp_obj = elements[j - 1];
				elements[j - 1] = elements[j];
				elements[j] = temp_obj;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_ns_हटाओ_element
 *
 * PARAMETERS:  obj_desc            - Package object element list
 *              index               - Index of element to हटाओ
 *
 * RETURN:      None
 *
 * DESCRIPTION: Remove the requested element of a package and delete it.
 *
 *****************************************************************************/

अटल व्योम
acpi_ns_हटाओ_element(जोड़ acpi_opeअक्रम_object *obj_desc, u32 index)
अणु
	जोड़ acpi_opeअक्रम_object **source;
	जोड़ acpi_opeअक्रम_object **dest;
	u32 count;
	u32 new_count;
	u32 i;

	ACPI_FUNCTION_NAME(ns_हटाओ_element);

	count = obj_desc->package.count;
	new_count = count - 1;

	source = obj_desc->package.elements;
	dest = source;

	/* Examine all elements of the package object, हटाओ matched index */

	क्रम (i = 0; i < count; i++) अणु
		अगर (i == index) अणु
			acpi_ut_हटाओ_reference(*source);	/* Remove one ref क्रम being in pkg */
			acpi_ut_हटाओ_reference(*source);
		पूर्ण अन्यथा अणु
			*dest = *source;
			dest++;
		पूर्ण

		source++;
	पूर्ण

	/* शून्य terminate list and update the package count */

	*dest = शून्य;
	obj_desc->package.count = new_count;
पूर्ण
