<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: nsxfname - Public पूर्णांकerfaces to the ACPI subप्रणाली
 *                         ACPI Namespace oriented पूर्णांकerfaces
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#घोषणा EXPORT_ACPI_INTERFACES

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acnamesp.h"
#समावेश "acparser.h"
#समावेश "amlcode.h"

#घोषणा _COMPONENT          ACPI_NAMESPACE
ACPI_MODULE_NAME("nsxfname")

/* Local prototypes */
अटल अक्षर *acpi_ns_copy_device_id(काष्ठा acpi_pnp_device_id *dest,
				    काष्ठा acpi_pnp_device_id *source,
				    अक्षर *string_area);

/******************************************************************************
 *
 * FUNCTION:    acpi_get_handle
 *
 * PARAMETERS:  parent          - Object to search under (search scope).
 *              pathname        - Poपूर्णांकer to an asciiz string containing the
 *                                name
 *              ret_handle      - Where the वापस handle is वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: This routine will search क्रम a caller specअगरied name in the
 *              name space. The caller can restrict the search region by
 *              specअगरying a non शून्य parent. The parent value is itself a
 *              namespace handle.
 *
 ******************************************************************************/

acpi_status
acpi_get_handle(acpi_handle parent,
		acpi_string pathname, acpi_handle *ret_handle)
अणु
	acpi_status status;
	काष्ठा acpi_namespace_node *node = शून्य;
	काष्ठा acpi_namespace_node *prefix_node = शून्य;

	ACPI_FUNCTION_ENTRY();

	/* Parameter Validation */

	अगर (!ret_handle || !pathname) अणु
		वापस (AE_BAD_PARAMETER);
	पूर्ण

	/* Convert a parent handle to a prefix node */

	अगर (parent) अणु
		prefix_node = acpi_ns_validate_handle(parent);
		अगर (!prefix_node) अणु
			वापस (AE_BAD_PARAMETER);
		पूर्ण
	पूर्ण

	/*
	 * Valid हालs are:
	 * 1) Fully qualअगरied pathname
	 * 2) Parent + Relative pathname
	 *
	 * Error क्रम <null Parent + relative path>
	 */
	अगर (ACPI_IS_ROOT_PREFIX(pathname[0])) अणु

		/* Pathname is fully qualअगरied (starts with '\') */

		/* Special हाल क्रम root-only, since we can't search क्रम it */

		अगर (!म_भेद(pathname, ACPI_NS_ROOT_PATH)) अणु
			*ret_handle =
			    ACPI_CAST_PTR(acpi_handle, acpi_gbl_root_node);
			वापस (AE_OK);
		पूर्ण
	पूर्ण अन्यथा अगर (!prefix_node) अणु

		/* Relative path with null prefix is disallowed */

		वापस (AE_BAD_PARAMETER);
	पूर्ण

	/* Find the Node and convert to a handle */

	status =
	    acpi_ns_get_node(prefix_node, pathname, ACPI_NS_NO_UPSEARCH, &node);
	अगर (ACPI_SUCCESS(status)) अणु
		*ret_handle = ACPI_CAST_PTR(acpi_handle, node);
	पूर्ण

	वापस (status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_get_handle)

/******************************************************************************
 *
 * FUNCTION:    acpi_get_name
 *
 * PARAMETERS:  handle          - Handle to be converted to a pathname
 *              name_type       - Full pathname or single segment
 *              buffer          - Buffer क्रम वापसed path
 *
 * RETURN:      Poपूर्णांकer to a string containing the fully qualअगरied Name.
 *
 * DESCRIPTION: This routine वापसs the fully qualअगरied name associated with
 *              the Handle parameter. This and the acpi_pathname_to_handle are
 *              complementary functions.
 *
 ******************************************************************************/
acpi_status
acpi_get_name(acpi_handle handle, u32 name_type, काष्ठा acpi_buffer *buffer)
अणु
	acpi_status status;

	/* Parameter validation */

	अगर (name_type > ACPI_NAME_TYPE_MAX) अणु
		वापस (AE_BAD_PARAMETER);
	पूर्ण

	status = acpi_ut_validate_buffer(buffer);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	/*
	 * Wants the single segment ACPI name.
	 * Validate handle and convert to a namespace Node
	 */
	status = acpi_ut_acquire_mutex(ACPI_MTX_NAMESPACE);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	अगर (name_type == ACPI_FULL_PATHNAME ||
	    name_type == ACPI_FULL_PATHNAME_NO_TRAILING) अणु

		/* Get the full pathname (From the namespace root) */

		status = acpi_ns_handle_to_pathname(handle, buffer,
						    name_type ==
						    ACPI_FULL_PATHNAME ? FALSE :
						    TRUE);
	पूर्ण अन्यथा अणु
		/* Get the single name */

		status = acpi_ns_handle_to_name(handle, buffer);
	पूर्ण

	(व्योम)acpi_ut_release_mutex(ACPI_MTX_NAMESPACE);
	वापस (status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_get_name)

/******************************************************************************
 *
 * FUNCTION:    acpi_ns_copy_device_id
 *
 * PARAMETERS:  dest                - Poपूर्णांकer to the destination PNP_DEVICE_ID
 *              source              - Poपूर्णांकer to the source PNP_DEVICE_ID
 *              string_area         - Poपूर्णांकer to where to copy the dest string
 *
 * RETURN:      Poपूर्णांकer to the next string area
 *
 * DESCRIPTION: Copy a single PNP_DEVICE_ID, including the string data.
 *
 ******************************************************************************/
अटल अक्षर *acpi_ns_copy_device_id(काष्ठा acpi_pnp_device_id *dest,
				    काष्ठा acpi_pnp_device_id *source,
				    अक्षर *string_area)
अणु
	/* Create the destination PNP_DEVICE_ID */

	dest->string = string_area;
	dest->length = source->length;

	/* Copy actual string and वापस a poपूर्णांकer to the next string area */

	स_नकल(string_area, source->string, source->length);
	वापस (string_area + source->length);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_get_object_info
 *
 * PARAMETERS:  handle              - Object Handle
 *              वापस_buffer       - Where the info is वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Returns inक्रमmation about an object as gleaned from the
 *              namespace node and possibly by running several standard
 *              control methods (Such as in the हाल of a device.)
 *
 * For Device and Processor objects, run the Device _HID, _UID, _CID,
 * _CLS, _ADR, _sx_w, and _sx_d methods.
 *
 * Note: Allocates the वापस buffer, must be मुक्तd by the caller.
 *
 * Note: This पूर्णांकerface is पूर्णांकended to be used during the initial device
 * discovery namespace traversal. Thereक्रमe, no complex methods can be
 * executed, especially those that access operation regions. Thereक्रमe, करो
 * not add any additional methods that could cause problems in this area.
 * Because of this reason support क्रम the following methods has been हटाओd:
 * 1) _SUB method was हटाओd (11/2015)
 * 2) _STA method was हटाओd (02/2018)
 *
 ******************************************************************************/

acpi_status
acpi_get_object_info(acpi_handle handle,
		     काष्ठा acpi_device_info **वापस_buffer)
अणु
	काष्ठा acpi_namespace_node *node;
	काष्ठा acpi_device_info *info;
	काष्ठा acpi_pnp_device_id_list *cid_list = शून्य;
	काष्ठा acpi_pnp_device_id *hid = शून्य;
	काष्ठा acpi_pnp_device_id *uid = शून्य;
	काष्ठा acpi_pnp_device_id *cls = शून्य;
	अक्षर *next_id_string;
	acpi_object_type type;
	acpi_name name;
	u8 param_count = 0;
	u16 valid = 0;
	u32 info_size;
	u32 i;
	acpi_status status;

	/* Parameter validation */

	अगर (!handle || !वापस_buffer) अणु
		वापस (AE_BAD_PARAMETER);
	पूर्ण

	status = acpi_ut_acquire_mutex(ACPI_MTX_NAMESPACE);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	node = acpi_ns_validate_handle(handle);
	अगर (!node) अणु
		(व्योम)acpi_ut_release_mutex(ACPI_MTX_NAMESPACE);
		वापस (AE_BAD_PARAMETER);
	पूर्ण

	/* Get the namespace node data जबतक the namespace is locked */

	info_size = माप(काष्ठा acpi_device_info);
	type = node->type;
	name = node->name.पूर्णांकeger;

	अगर (node->type == ACPI_TYPE_METHOD) अणु
		param_count = node->object->method.param_count;
	पूर्ण

	status = acpi_ut_release_mutex(ACPI_MTX_NAMESPACE);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	अगर ((type == ACPI_TYPE_DEVICE) || (type == ACPI_TYPE_PROCESSOR)) अणु
		/*
		 * Get extra info क्रम ACPI Device/Processor objects only:
		 * Run the Device _HID, _UID, _CLS, and _CID methods.
		 *
		 * Note: none of these methods are required, so they may or may
		 * not be present क्रम this device. The Info->Valid bitfield is used
		 * to indicate which methods were found and run successfully.
		 */

		/* Execute the Device._HID method */

		status = acpi_ut_execute_HID(node, &hid);
		अगर (ACPI_SUCCESS(status)) अणु
			info_size += hid->length;
			valid |= ACPI_VALID_HID;
		पूर्ण

		/* Execute the Device._UID method */

		status = acpi_ut_execute_UID(node, &uid);
		अगर (ACPI_SUCCESS(status)) अणु
			info_size += uid->length;
			valid |= ACPI_VALID_UID;
		पूर्ण

		/* Execute the Device._CID method */

		status = acpi_ut_execute_CID(node, &cid_list);
		अगर (ACPI_SUCCESS(status)) अणु

			/* Add size of CID strings and CID poपूर्णांकer array */

			info_size +=
			    (cid_list->list_size -
			     माप(काष्ठा acpi_pnp_device_id_list));
			valid |= ACPI_VALID_CID;
		पूर्ण

		/* Execute the Device._CLS method */

		status = acpi_ut_execute_CLS(node, &cls);
		अगर (ACPI_SUCCESS(status)) अणु
			info_size += cls->length;
			valid |= ACPI_VALID_CLS;
		पूर्ण
	पूर्ण

	/*
	 * Now that we have the variable-length data, we can allocate the
	 * वापस buffer
	 */
	info = ACPI_ALLOCATE_ZEROED(info_size);
	अगर (!info) अणु
		status = AE_NO_MEMORY;
		जाओ cleanup;
	पूर्ण

	/* Get the fixed-length data */

	अगर ((type == ACPI_TYPE_DEVICE) || (type == ACPI_TYPE_PROCESSOR)) अणु
		/*
		 * Get extra info क्रम ACPI Device/Processor objects only:
		 * Run the _ADR and, sx_w, and _sx_d methods.
		 *
		 * Notes: none of these methods are required, so they may or may
		 * not be present क्रम this device. The Info->Valid bitfield is used
		 * to indicate which methods were found and run successfully.
		 */

		/* Execute the Device._ADR method */

		status = acpi_ut_evaluate_numeric_object(METHOD_NAME__ADR, node,
							 &info->address);
		अगर (ACPI_SUCCESS(status)) अणु
			valid |= ACPI_VALID_ADR;
		पूर्ण

		/* Execute the Device._sx_w methods */

		status = acpi_ut_execute_घातer_methods(node,
						       acpi_gbl_lowest_dstate_names,
						       ACPI_NUM_sx_w_METHODS,
						       info->lowest_dstates);
		अगर (ACPI_SUCCESS(status)) अणु
			valid |= ACPI_VALID_SXWS;
		पूर्ण

		/* Execute the Device._sx_d methods */

		status = acpi_ut_execute_घातer_methods(node,
						       acpi_gbl_highest_dstate_names,
						       ACPI_NUM_sx_d_METHODS,
						       info->highest_dstates);
		अगर (ACPI_SUCCESS(status)) अणु
			valid |= ACPI_VALID_SXDS;
		पूर्ण
	पूर्ण

	/*
	 * Create a poपूर्णांकer to the string area of the वापस buffer.
	 * Poपूर्णांक to the end of the base काष्ठा acpi_device_info काष्ठाure.
	 */
	next_id_string = ACPI_CAST_PTR(अक्षर, info->compatible_id_list.ids);
	अगर (cid_list) अणु

		/* Poपूर्णांक past the CID PNP_DEVICE_ID array */

		next_id_string +=
		    ((acpi_size)cid_list->count *
		     माप(काष्ठा acpi_pnp_device_id));
	पूर्ण

	/*
	 * Copy the HID, UID, and CIDs to the वापस buffer. The variable-length
	 * strings are copied to the reserved area at the end of the buffer.
	 *
	 * For HID and CID, check अगर the ID is a PCI Root Bridge.
	 */
	अगर (hid) अणु
		next_id_string = acpi_ns_copy_device_id(&info->hardware_id,
							hid, next_id_string);

		अगर (acpi_ut_is_pci_root_bridge(hid->string)) अणु
			info->flags |= ACPI_PCI_ROOT_BRIDGE;
		पूर्ण
	पूर्ण

	अगर (uid) अणु
		next_id_string = acpi_ns_copy_device_id(&info->unique_id,
							uid, next_id_string);
	पूर्ण

	अगर (cid_list) अणु
		info->compatible_id_list.count = cid_list->count;
		info->compatible_id_list.list_size = cid_list->list_size;

		/* Copy each CID */

		क्रम (i = 0; i < cid_list->count; i++) अणु
			next_id_string =
			    acpi_ns_copy_device_id(&info->compatible_id_list.
						   ids[i], &cid_list->ids[i],
						   next_id_string);

			अगर (acpi_ut_is_pci_root_bridge(cid_list->ids[i].string)) अणु
				info->flags |= ACPI_PCI_ROOT_BRIDGE;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (cls) अणु
		(व्योम)acpi_ns_copy_device_id(&info->class_code,
					     cls, next_id_string);
	पूर्ण

	/* Copy the fixed-length data */

	info->info_size = info_size;
	info->type = type;
	info->name = name;
	info->param_count = param_count;
	info->valid = valid;

	*वापस_buffer = info;
	status = AE_OK;

cleanup:
	अगर (hid) अणु
		ACPI_FREE(hid);
	पूर्ण
	अगर (uid) अणु
		ACPI_FREE(uid);
	पूर्ण
	अगर (cid_list) अणु
		ACPI_FREE(cid_list);
	पूर्ण
	अगर (cls) अणु
		ACPI_FREE(cls);
	पूर्ण
	वापस (status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_get_object_info)

/******************************************************************************
 *
 * FUNCTION:    acpi_install_method
 *
 * PARAMETERS:  buffer         - An ACPI table containing one control method
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Install a control method पूर्णांकo the namespace. If the method
 *              name alपढ़ोy exists in the namespace, it is overwritten. The
 *              input buffer must contain a valid DSDT or SSDT containing a
 *              single control method.
 *
 ******************************************************************************/
acpi_status acpi_install_method(u8 *buffer)
अणु
	काष्ठा acpi_table_header *table =
	    ACPI_CAST_PTR(काष्ठा acpi_table_header, buffer);
	u8 *aml_buffer;
	u8 *aml_start;
	अक्षर *path;
	काष्ठा acpi_namespace_node *node;
	जोड़ acpi_opeअक्रम_object *method_obj;
	काष्ठा acpi_parse_state parser_state;
	u32 aml_length;
	u16 opcode;
	u8 method_flags;
	acpi_status status;

	/* Parameter validation */

	अगर (!buffer) अणु
		वापस (AE_BAD_PARAMETER);
	पूर्ण

	/* Table must be a DSDT or SSDT */

	अगर (!ACPI_COMPARE_NAMESEG(table->signature, ACPI_SIG_DSDT) &&
	    !ACPI_COMPARE_NAMESEG(table->signature, ACPI_SIG_SSDT)) अणु
		वापस (AE_BAD_HEADER);
	पूर्ण

	/* First AML opcode in the table must be a control method */

	parser_state.aml = buffer + माप(काष्ठा acpi_table_header);
	opcode = acpi_ps_peek_opcode(&parser_state);
	अगर (opcode != AML_METHOD_OP) अणु
		वापस (AE_BAD_PARAMETER);
	पूर्ण

	/* Extract method inक्रमmation from the raw AML */

	parser_state.aml += acpi_ps_get_opcode_size(opcode);
	parser_state.pkg_end = acpi_ps_get_next_package_end(&parser_state);
	path = acpi_ps_get_next_namestring(&parser_state);

	method_flags = *parser_state.aml++;
	aml_start = parser_state.aml;
	aml_length = (u32)ACPI_PTR_DIFF(parser_state.pkg_end, aml_start);

	/*
	 * Allocate resources up-front. We करोn't want to have to delete a new
	 * node from the namespace अगर we cannot allocate memory.
	 */
	aml_buffer = ACPI_ALLOCATE(aml_length);
	अगर (!aml_buffer) अणु
		वापस (AE_NO_MEMORY);
	पूर्ण

	method_obj = acpi_ut_create_पूर्णांकernal_object(ACPI_TYPE_METHOD);
	अगर (!method_obj) अणु
		ACPI_FREE(aml_buffer);
		वापस (AE_NO_MEMORY);
	पूर्ण

	/* Lock namespace क्रम acpi_ns_lookup, we may be creating a new node */

	status = acpi_ut_acquire_mutex(ACPI_MTX_NAMESPACE);
	अगर (ACPI_FAILURE(status)) अणु
		जाओ error_निकास;
	पूर्ण

	/* The lookup either वापसs an existing node or creates a new one */

	status =
	    acpi_ns_lookup(शून्य, path, ACPI_TYPE_METHOD, ACPI_IMODE_LOAD_PASS1,
			   ACPI_NS_DONT_OPEN_SCOPE | ACPI_NS_ERROR_IF_FOUND,
			   शून्य, &node);

	(व्योम)acpi_ut_release_mutex(ACPI_MTX_NAMESPACE);

	अगर (ACPI_FAILURE(status)) अणु	/* ns_lookup */
		अगर (status != AE_ALREADY_EXISTS) अणु
			जाओ error_निकास;
		पूर्ण

		/* Node existed previously, make sure it is a method node */

		अगर (node->type != ACPI_TYPE_METHOD) अणु
			status = AE_TYPE;
			जाओ error_निकास;
		पूर्ण
	पूर्ण

	/* Copy the method AML to the local buffer */

	स_नकल(aml_buffer, aml_start, aml_length);

	/* Initialize the method object with the new method's inक्रमmation */

	method_obj->method.aml_start = aml_buffer;
	method_obj->method.aml_length = aml_length;

	method_obj->method.param_count = (u8)
	    (method_flags & AML_METHOD_ARG_COUNT);

	अगर (method_flags & AML_METHOD_SERIALIZED) अणु
		method_obj->method.info_flags = ACPI_METHOD_SERIALIZED;

		method_obj->method.sync_level = (u8)
		    ((method_flags & AML_METHOD_SYNC_LEVEL) >> 4);
	पूर्ण

	/*
	 * Now that it is complete, we can attach the new method object to
	 * the method Node (detaches/deletes any existing object)
	 */
	status = acpi_ns_attach_object(node, method_obj, ACPI_TYPE_METHOD);

	/*
	 * Flag indicates AML buffer is dynamic, must be deleted later.
	 * Must be set only after attach above.
	 */
	node->flags |= ANOBJ_ALLOCATED_BUFFER;

	/* Remove local reference to the method object */

	acpi_ut_हटाओ_reference(method_obj);
	वापस (status);

error_निकास:

	ACPI_FREE(aml_buffer);
	ACPI_FREE(method_obj);
	वापस (status);
पूर्ण
ACPI_EXPORT_SYMBOL(acpi_install_method)
