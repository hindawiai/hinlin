<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: utids - support क्रम device Ids - HID, UID, CID, SUB, CLS
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acinterp.h"

#घोषणा _COMPONENT          ACPI_UTILITIES
ACPI_MODULE_NAME("utids")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_execute_HID
 *
 * PARAMETERS:  device_node         - Node क्रम the device
 *              वापस_id           - Where the string HID is वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Executes the _HID control method that वापसs the hardware
 *              ID of the device. The HID is either an 32-bit encoded EISAID
 *              Integer or a String. A string is always वापसed. An EISAID
 *              is converted to a string.
 *
 *              NOTE: Internal function, no parameter validation
 *
 ******************************************************************************/
acpi_status
acpi_ut_execute_HID(काष्ठा acpi_namespace_node *device_node,
		    काष्ठा acpi_pnp_device_id **वापस_id)
अणु
	जोड़ acpi_opeअक्रम_object *obj_desc;
	काष्ठा acpi_pnp_device_id *hid;
	u32 length;
	acpi_status status;

	ACPI_FUNCTION_TRACE(ut_execute_HID);

	status = acpi_ut_evaluate_object(device_node, METHOD_NAME__HID,
					 ACPI_BTYPE_INTEGER | ACPI_BTYPE_STRING,
					 &obj_desc);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Get the size of the String to be वापसed, includes null terminator */

	अगर (obj_desc->common.type == ACPI_TYPE_INTEGER) अणु
		length = ACPI_EISAID_STRING_SIZE;
	पूर्ण अन्यथा अणु
		length = obj_desc->string.length + 1;
	पूर्ण

	/* Allocate a buffer क्रम the HID */

	hid =
	    ACPI_ALLOCATE_ZEROED(माप(काष्ठा acpi_pnp_device_id) +
				 (acpi_size)length);
	अगर (!hid) अणु
		status = AE_NO_MEMORY;
		जाओ cleanup;
	पूर्ण

	/* Area क्रम the string starts after PNP_DEVICE_ID काष्ठा */

	hid->string =
	    ACPI_ADD_PTR(अक्षर, hid, माप(काष्ठा acpi_pnp_device_id));

	/* Convert EISAID to a string or simply copy existing string */

	अगर (obj_desc->common.type == ACPI_TYPE_INTEGER) अणु
		acpi_ex_eisa_id_to_string(hid->string, obj_desc->पूर्णांकeger.value);
	पूर्ण अन्यथा अणु
		म_नकल(hid->string, obj_desc->string.poपूर्णांकer);
	पूर्ण

	hid->length = length;
	*वापस_id = hid;

cleanup:

	/* On निकास, we must delete the वापस object */

	acpi_ut_हटाओ_reference(obj_desc);
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_execute_UID
 *
 * PARAMETERS:  device_node         - Node क्रम the device
 *              वापस_id           - Where the string UID is वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Executes the _UID control method that वापसs the unique
 *              ID of the device. The UID is either a 64-bit Integer (NOT an
 *              EISAID) or a string. Always वापसs a string. A 64-bit पूर्णांकeger
 *              is converted to a decimal string.
 *
 *              NOTE: Internal function, no parameter validation
 *
 ******************************************************************************/

acpi_status
acpi_ut_execute_UID(काष्ठा acpi_namespace_node *device_node,
		    काष्ठा acpi_pnp_device_id **वापस_id)
अणु
	जोड़ acpi_opeअक्रम_object *obj_desc;
	काष्ठा acpi_pnp_device_id *uid;
	u32 length;
	acpi_status status;

	ACPI_FUNCTION_TRACE(ut_execute_UID);

	status = acpi_ut_evaluate_object(device_node, METHOD_NAME__UID,
					 ACPI_BTYPE_INTEGER | ACPI_BTYPE_STRING,
					 &obj_desc);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Get the size of the String to be वापसed, includes null terminator */

	अगर (obj_desc->common.type == ACPI_TYPE_INTEGER) अणु
		length = ACPI_MAX64_DECIMAL_DIGITS + 1;
	पूर्ण अन्यथा अणु
		length = obj_desc->string.length + 1;
	पूर्ण

	/* Allocate a buffer क्रम the UID */

	uid =
	    ACPI_ALLOCATE_ZEROED(माप(काष्ठा acpi_pnp_device_id) +
				 (acpi_size)length);
	अगर (!uid) अणु
		status = AE_NO_MEMORY;
		जाओ cleanup;
	पूर्ण

	/* Area क्रम the string starts after PNP_DEVICE_ID काष्ठा */

	uid->string =
	    ACPI_ADD_PTR(अक्षर, uid, माप(काष्ठा acpi_pnp_device_id));

	/* Convert an Integer to string, or just copy an existing string */

	अगर (obj_desc->common.type == ACPI_TYPE_INTEGER) अणु
		acpi_ex_पूर्णांकeger_to_string(uid->string, obj_desc->पूर्णांकeger.value);
	पूर्ण अन्यथा अणु
		म_नकल(uid->string, obj_desc->string.poपूर्णांकer);
	पूर्ण

	uid->length = length;
	*वापस_id = uid;

cleanup:

	/* On निकास, we must delete the वापस object */

	acpi_ut_हटाओ_reference(obj_desc);
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_execute_CID
 *
 * PARAMETERS:  device_node         - Node क्रम the device
 *              वापस_cid_list     - Where the CID list is वापसed
 *
 * RETURN:      Status, list of CID strings
 *
 * DESCRIPTION: Executes the _CID control method that वापसs one or more
 *              compatible hardware IDs क्रम the device.
 *
 *              NOTE: Internal function, no parameter validation
 *
 * A _CID method can वापस either a single compatible ID or a package of
 * compatible IDs. Each compatible ID can be one of the following:
 * 1) Integer (32 bit compressed EISA ID) or
 * 2) String (PCI ID क्रमmat, e.g. "PCI\VEN_vvvv&DEV_dddd&SUBSYS_ssssssss")
 *
 * The Integer CIDs are converted to string क्रमmat by this function.
 *
 ******************************************************************************/

acpi_status
acpi_ut_execute_CID(काष्ठा acpi_namespace_node *device_node,
		    काष्ठा acpi_pnp_device_id_list **वापस_cid_list)
अणु
	जोड़ acpi_opeअक्रम_object **cid_objects;
	जोड़ acpi_opeअक्रम_object *obj_desc;
	काष्ठा acpi_pnp_device_id_list *cid_list;
	अक्षर *next_id_string;
	u32 string_area_size;
	u32 length;
	u32 cid_list_size;
	acpi_status status;
	u32 count;
	u32 i;

	ACPI_FUNCTION_TRACE(ut_execute_CID);

	/* Evaluate the _CID method क्रम this device */

	status = acpi_ut_evaluate_object(device_node, METHOD_NAME__CID,
					 ACPI_BTYPE_INTEGER | ACPI_BTYPE_STRING
					 | ACPI_BTYPE_PACKAGE, &obj_desc);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/*
	 * Get the count and size of the वापसed _CIDs. _CID can वापस either
	 * a Package of Integers/Strings or a single Integer or String.
	 * Note: This section also validates that all CID elements are of the
	 * correct type (Integer or String).
	 */
	अगर (obj_desc->common.type == ACPI_TYPE_PACKAGE) अणु
		count = obj_desc->package.count;
		cid_objects = obj_desc->package.elements;
	पूर्ण अन्यथा अणु		/* Single Integer or String CID */

		count = 1;
		cid_objects = &obj_desc;
	पूर्ण

	string_area_size = 0;
	क्रम (i = 0; i < count; i++) अणु

		/* String lengths include null terminator */

		चयन (cid_objects[i]->common.type) अणु
		हाल ACPI_TYPE_INTEGER:

			string_area_size += ACPI_EISAID_STRING_SIZE;
			अवरोध;

		हाल ACPI_TYPE_STRING:

			string_area_size += cid_objects[i]->string.length + 1;
			अवरोध;

		शेष:

			status = AE_TYPE;
			जाओ cleanup;
		पूर्ण
	पूर्ण

	/*
	 * Now that we know the length of the CIDs, allocate वापस buffer:
	 * 1) Size of the base काष्ठाure +
	 * 2) Size of the CID PNP_DEVICE_ID array +
	 * 3) Size of the actual CID strings
	 */
	cid_list_size = माप(काष्ठा acpi_pnp_device_id_list) +
	    (count * माप(काष्ठा acpi_pnp_device_id)) + string_area_size;

	cid_list = ACPI_ALLOCATE_ZEROED(cid_list_size);
	अगर (!cid_list) अणु
		status = AE_NO_MEMORY;
		जाओ cleanup;
	पूर्ण

	/* Area क्रम CID strings starts after the CID PNP_DEVICE_ID array */

	next_id_string = ACPI_CAST_PTR(अक्षर, cid_list->ids) +
	    ((acpi_size)count * माप(काष्ठा acpi_pnp_device_id));

	/* Copy/convert the CIDs to the वापस buffer */

	क्रम (i = 0; i < count; i++) अणु
		अगर (cid_objects[i]->common.type == ACPI_TYPE_INTEGER) अणु

			/* Convert the Integer (EISAID) CID to a string */

			acpi_ex_eisa_id_to_string(next_id_string,
						  cid_objects[i]->पूर्णांकeger.
						  value);
			length = ACPI_EISAID_STRING_SIZE;
		पूर्ण अन्यथा अणु	/* ACPI_TYPE_STRING */
			/* Copy the String CID from the वापसed object */
			म_नकल(next_id_string, cid_objects[i]->string.poपूर्णांकer);
			length = cid_objects[i]->string.length + 1;
		पूर्ण

		cid_list->ids[i].string = next_id_string;
		cid_list->ids[i].length = length;
		next_id_string += length;
	पूर्ण

	/* Finish the CID list */

	cid_list->count = count;
	cid_list->list_size = cid_list_size;
	*वापस_cid_list = cid_list;

cleanup:

	/* On निकास, we must delete the _CID वापस object */

	acpi_ut_हटाओ_reference(obj_desc);
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_execute_CLS
 *
 * PARAMETERS:  device_node         - Node क्रम the device
 *              वापस_id           - Where the _CLS is वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Executes the _CLS control method that वापसs PCI-defined
 *              class code of the device. The _CLS value is always a package
 *              containing PCI class inक्रमmation as a list of पूर्णांकegers.
 *              The वापसed string has क्रमmat "BBSSPP", where:
 *                BB = Base-class code
 *                SS = Sub-class code
 *                PP = Programming Interface code
 *
 ******************************************************************************/

acpi_status
acpi_ut_execute_CLS(काष्ठा acpi_namespace_node *device_node,
		    काष्ठा acpi_pnp_device_id **वापस_id)
अणु
	जोड़ acpi_opeअक्रम_object *obj_desc;
	जोड़ acpi_opeअक्रम_object **cls_objects;
	u32 count;
	काष्ठा acpi_pnp_device_id *cls;
	u32 length;
	acpi_status status;
	u8 class_code[3] = अणु 0, 0, 0 पूर्ण;

	ACPI_FUNCTION_TRACE(ut_execute_CLS);

	status = acpi_ut_evaluate_object(device_node, METHOD_NAME__CLS,
					 ACPI_BTYPE_PACKAGE, &obj_desc);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Get the size of the String to be वापसed, includes null terminator */

	length = ACPI_PCICLS_STRING_SIZE;
	cls_objects = obj_desc->package.elements;
	count = obj_desc->package.count;

	अगर (obj_desc->common.type == ACPI_TYPE_PACKAGE) अणु
		अगर (count > 0
		    && cls_objects[0]->common.type == ACPI_TYPE_INTEGER) अणु
			class_code[0] = (u8)cls_objects[0]->पूर्णांकeger.value;
		पूर्ण
		अगर (count > 1
		    && cls_objects[1]->common.type == ACPI_TYPE_INTEGER) अणु
			class_code[1] = (u8)cls_objects[1]->पूर्णांकeger.value;
		पूर्ण
		अगर (count > 2
		    && cls_objects[2]->common.type == ACPI_TYPE_INTEGER) अणु
			class_code[2] = (u8)cls_objects[2]->पूर्णांकeger.value;
		पूर्ण
	पूर्ण

	/* Allocate a buffer क्रम the CLS */

	cls =
	    ACPI_ALLOCATE_ZEROED(माप(काष्ठा acpi_pnp_device_id) +
				 (acpi_size)length);
	अगर (!cls) अणु
		status = AE_NO_MEMORY;
		जाओ cleanup;
	पूर्ण

	/* Area क्रम the string starts after PNP_DEVICE_ID काष्ठा */

	cls->string =
	    ACPI_ADD_PTR(अक्षर, cls, माप(काष्ठा acpi_pnp_device_id));

	/* Simply copy existing string */

	acpi_ex_pci_cls_to_string(cls->string, class_code);
	cls->length = length;
	*वापस_id = cls;

cleanup:

	/* On निकास, we must delete the वापस object */

	acpi_ut_हटाओ_reference(obj_desc);
	वापस_ACPI_STATUS(status);
पूर्ण
