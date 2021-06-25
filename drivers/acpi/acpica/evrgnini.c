<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: evrgnini- ACPI address_space (op_region) init
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acevents.h"
#समावेश "acnamesp.h"
#समावेश "acinterp.h"

#घोषणा _COMPONENT          ACPI_EVENTS
ACPI_MODULE_NAME("evrgnini")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_प्रणाली_memory_region_setup
 *
 * PARAMETERS:  handle              - Region we are पूर्णांकerested in
 *              function            - Start or stop
 *              handler_context     - Address space handler context
 *              region_context      - Region specअगरic context
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Setup a प्रणाली_memory operation region
 *
 ******************************************************************************/
acpi_status
acpi_ev_प्रणाली_memory_region_setup(acpi_handle handle,
				   u32 function,
				   व्योम *handler_context, व्योम **region_context)
अणु
	जोड़ acpi_opeअक्रम_object *region_desc =
	    (जोड़ acpi_opeअक्रम_object *)handle;
	काष्ठा acpi_mem_space_context *local_region_context;
	काष्ठा acpi_mem_mapping *mm;

	ACPI_FUNCTION_TRACE(ev_प्रणाली_memory_region_setup);

	अगर (function == ACPI_REGION_DEACTIVATE) अणु
		अगर (*region_context) अणु
			local_region_context =
			    (काष्ठा acpi_mem_space_context *)*region_context;

			/* Delete memory mappings अगर present */

			जबतक (local_region_context->first_mm) अणु
				mm = local_region_context->first_mm;
				local_region_context->first_mm = mm->next_mm;
				acpi_os_unmap_memory(mm->logical_address,
						     mm->length);
				ACPI_FREE(mm);
			पूर्ण
			ACPI_FREE(local_region_context);
			*region_context = शून्य;
		पूर्ण
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	/* Create a new context */

	local_region_context =
	    ACPI_ALLOCATE_ZEROED(माप(काष्ठा acpi_mem_space_context));
	अगर (!(local_region_context)) अणु
		वापस_ACPI_STATUS(AE_NO_MEMORY);
	पूर्ण

	/* Save the region length and address क्रम use in the handler */

	local_region_context->length = region_desc->region.length;
	local_region_context->address = region_desc->region.address;

	*region_context = local_region_context;
	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_io_space_region_setup
 *
 * PARAMETERS:  handle              - Region we are पूर्णांकerested in
 *              function            - Start or stop
 *              handler_context     - Address space handler context
 *              region_context      - Region specअगरic context
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Setup a IO operation region
 *
 ******************************************************************************/

acpi_status
acpi_ev_io_space_region_setup(acpi_handle handle,
			      u32 function,
			      व्योम *handler_context, व्योम **region_context)
अणु
	ACPI_FUNCTION_TRACE(ev_io_space_region_setup);

	अगर (function == ACPI_REGION_DEACTIVATE) अणु
		*region_context = शून्य;
	पूर्ण अन्यथा अणु
		*region_context = handler_context;
	पूर्ण

	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_pci_config_region_setup
 *
 * PARAMETERS:  handle              - Region we are पूर्णांकerested in
 *              function            - Start or stop
 *              handler_context     - Address space handler context
 *              region_context      - Region specअगरic context
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Setup a PCI_Config operation region
 *
 * MUTEX:       Assumes namespace is not locked
 *
 ******************************************************************************/

acpi_status
acpi_ev_pci_config_region_setup(acpi_handle handle,
				u32 function,
				व्योम *handler_context, व्योम **region_context)
अणु
	acpi_status status = AE_OK;
	u64 pci_value;
	काष्ठा acpi_pci_id *pci_id = *region_context;
	जोड़ acpi_opeअक्रम_object *handler_obj;
	काष्ठा acpi_namespace_node *parent_node;
	काष्ठा acpi_namespace_node *pci_root_node;
	काष्ठा acpi_namespace_node *pci_device_node;
	जोड़ acpi_opeअक्रम_object *region_obj =
	    (जोड़ acpi_opeअक्रम_object *)handle;

	ACPI_FUNCTION_TRACE(ev_pci_config_region_setup);

	handler_obj = region_obj->region.handler;
	अगर (!handler_obj) अणु
		/*
		 * No installed handler. This shouldn't happen because the dispatch
		 * routine checks beक्रमe we get here, but we check again just in हाल.
		 */
		ACPI_DEBUG_PRINT((ACPI_DB_OPREGION,
				  "Attempting to init a region %p, with no handler\n",
				  region_obj));
		वापस_ACPI_STATUS(AE_NOT_EXIST);
	पूर्ण

	*region_context = शून्य;
	अगर (function == ACPI_REGION_DEACTIVATE) अणु
		अगर (pci_id) अणु
			ACPI_FREE(pci_id);
		पूर्ण
		वापस_ACPI_STATUS(status);
	पूर्ण

	parent_node = region_obj->region.node->parent;

	/*
	 * Get the _SEG and _BBN values from the device upon which the handler
	 * is installed.
	 *
	 * We need to get the _SEG and _BBN objects relative to the PCI BUS device.
	 * This is the device the handler has been रेजिस्टरed to handle.
	 */

	/*
	 * If the address_space.Node is still poपूर्णांकing to the root, we need
	 * to scan upward क्रम a PCI Root bridge and re-associate the op_region
	 * handlers with that device.
	 */
	अगर (handler_obj->address_space.node == acpi_gbl_root_node) अणु

		/* Start search from the parent object */

		pci_root_node = parent_node;
		जबतक (pci_root_node != acpi_gbl_root_node) अणु

			/* Get the _HID/_CID in order to detect a root_bridge */

			अगर (acpi_ev_is_pci_root_bridge(pci_root_node)) अणु

				/* Install a handler क्रम this PCI root bridge */

				status = acpi_install_address_space_handler((acpi_handle)pci_root_node, ACPI_ADR_SPACE_PCI_CONFIG, ACPI_DEFAULT_HANDLER, शून्य, शून्य);
				अगर (ACPI_FAILURE(status)) अणु
					अगर (status == AE_SAME_HANDLER) अणु
						/*
						 * It is OK अगर the handler is alपढ़ोy installed on the
						 * root bridge. Still need to वापस a context object
						 * क्रम the new PCI_Config operation region, however.
						 */
					पूर्ण अन्यथा अणु
						ACPI_EXCEPTION((AE_INFO, status,
								"Could not install PciConfig handler "
								"for Root Bridge %4.4s",
								acpi_ut_get_node_name
								(pci_root_node)));
					पूर्ण
				पूर्ण
				अवरोध;
			पूर्ण

			pci_root_node = pci_root_node->parent;
		पूर्ण

		/* PCI root bridge not found, use namespace root node */
	पूर्ण अन्यथा अणु
		pci_root_node = handler_obj->address_space.node;
	पूर्ण

	/*
	 * If this region is now initialized, we are करोne.
	 * (install_address_space_handler could have initialized it)
	 */
	अगर (region_obj->region.flags & AOPOBJ_SETUP_COMPLETE) अणु
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	/* Region is still not initialized. Create a new context */

	pci_id = ACPI_ALLOCATE_ZEROED(माप(काष्ठा acpi_pci_id));
	अगर (!pci_id) अणु
		वापस_ACPI_STATUS(AE_NO_MEMORY);
	पूर्ण

	/*
	 * For PCI_Config space access, we need the segment, bus, device and
	 * function numbers. Acquire them here.
	 *
	 * Find the parent device object. (This allows the operation region to be
	 * within a subscope under the device, such as a control method.)
	 */
	pci_device_node = region_obj->region.node;
	जबतक (pci_device_node && (pci_device_node->type != ACPI_TYPE_DEVICE)) अणु
		pci_device_node = pci_device_node->parent;
	पूर्ण

	अगर (!pci_device_node) अणु
		ACPI_FREE(pci_id);
		वापस_ACPI_STATUS(AE_AML_OPERAND_TYPE);
	पूर्ण

	/*
	 * Get the PCI device and function numbers from the _ADR object
	 * contained in the parent's scope.
	 */
	status = acpi_ut_evaluate_numeric_object(METHOD_NAME__ADR,
						 pci_device_node, &pci_value);

	/*
	 * The शेष is zero, and since the allocation above zeroed the data,
	 * just करो nothing on failure.
	 */
	अगर (ACPI_SUCCESS(status)) अणु
		pci_id->device = ACPI_HIWORD(ACPI_LODWORD(pci_value));
		pci_id->function = ACPI_LOWORD(ACPI_LODWORD(pci_value));
	पूर्ण

	/* The PCI segment number comes from the _SEG method */

	status = acpi_ut_evaluate_numeric_object(METHOD_NAME__SEG,
						 pci_root_node, &pci_value);
	अगर (ACPI_SUCCESS(status)) अणु
		pci_id->segment = ACPI_LOWORD(pci_value);
	पूर्ण

	/* The PCI bus number comes from the _BBN method */

	status = acpi_ut_evaluate_numeric_object(METHOD_NAME__BBN,
						 pci_root_node, &pci_value);
	अगर (ACPI_SUCCESS(status)) अणु
		pci_id->bus = ACPI_LOWORD(pci_value);
	पूर्ण

	/* Complete/update the PCI ID क्रम this device */

	status =
	    acpi_hw_derive_pci_id(pci_id, pci_root_node,
				  region_obj->region.node);
	अगर (ACPI_FAILURE(status)) अणु
		ACPI_FREE(pci_id);
		वापस_ACPI_STATUS(status);
	पूर्ण

	*region_context = pci_id;
	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_is_pci_root_bridge
 *
 * PARAMETERS:  node            - Device node being examined
 *
 * RETURN:      TRUE अगर device is a PCI/PCI-Express Root Bridge
 *
 * DESCRIPTION: Determine अगर the input device represents a PCI Root Bridge by
 *              examining the _HID and _CID क्रम the device.
 *
 ******************************************************************************/

u8 acpi_ev_is_pci_root_bridge(काष्ठा acpi_namespace_node *node)
अणु
	acpi_status status;
	काष्ठा acpi_pnp_device_id *hid;
	काष्ठा acpi_pnp_device_id_list *cid;
	u32 i;
	u8 match;

	/* Get the _HID and check क्रम a PCI Root Bridge */

	status = acpi_ut_execute_HID(node, &hid);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (FALSE);
	पूर्ण

	match = acpi_ut_is_pci_root_bridge(hid->string);
	ACPI_FREE(hid);

	अगर (match) अणु
		वापस (TRUE);
	पूर्ण

	/* The _HID did not match. Get the _CID and check क्रम a PCI Root Bridge */

	status = acpi_ut_execute_CID(node, &cid);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (FALSE);
	पूर्ण

	/* Check all _CIDs in the वापसed list */

	क्रम (i = 0; i < cid->count; i++) अणु
		अगर (acpi_ut_is_pci_root_bridge(cid->ids[i].string)) अणु
			ACPI_FREE(cid);
			वापस (TRUE);
		पूर्ण
	पूर्ण

	ACPI_FREE(cid);
	वापस (FALSE);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_pci_bar_region_setup
 *
 * PARAMETERS:  handle              - Region we are पूर्णांकerested in
 *              function            - Start or stop
 *              handler_context     - Address space handler context
 *              region_context      - Region specअगरic context
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Setup a pci_BAR operation region
 *
 * MUTEX:       Assumes namespace is not locked
 *
 ******************************************************************************/

acpi_status
acpi_ev_pci_bar_region_setup(acpi_handle handle,
			     u32 function,
			     व्योम *handler_context, व्योम **region_context)
अणु
	ACPI_FUNCTION_TRACE(ev_pci_bar_region_setup);

	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_cmos_region_setup
 *
 * PARAMETERS:  handle              - Region we are पूर्णांकerested in
 *              function            - Start or stop
 *              handler_context     - Address space handler context
 *              region_context      - Region specअगरic context
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Setup a CMOS operation region
 *
 * MUTEX:       Assumes namespace is not locked
 *
 ******************************************************************************/

acpi_status
acpi_ev_cmos_region_setup(acpi_handle handle,
			  u32 function,
			  व्योम *handler_context, व्योम **region_context)
अणु
	ACPI_FUNCTION_TRACE(ev_cmos_region_setup);

	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_शेष_region_setup
 *
 * PARAMETERS:  handle              - Region we are पूर्णांकerested in
 *              function            - Start or stop
 *              handler_context     - Address space handler context
 *              region_context      - Region specअगरic context
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Default region initialization
 *
 ******************************************************************************/

acpi_status
acpi_ev_शेष_region_setup(acpi_handle handle,
			     u32 function,
			     व्योम *handler_context, व्योम **region_context)
अणु
	ACPI_FUNCTION_TRACE(ev_शेष_region_setup);

	अगर (function == ACPI_REGION_DEACTIVATE) अणु
		*region_context = शून्य;
	पूर्ण अन्यथा अणु
		*region_context = handler_context;
	पूर्ण

	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_initialize_region
 *
 * PARAMETERS:  region_obj      - Region we are initializing
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Initializes the region, finds any _REG methods and saves them
 *              क्रम execution at a later समय
 *
 *              Get the appropriate address space handler क्रम a newly
 *              created region.
 *
 *              This also perक्रमms address space specअगरic initialization. For
 *              example, PCI regions must have an _ADR object that contains
 *              a PCI address in the scope of the definition. This address is
 *              required to perक्रमm an access to PCI config space.
 *
 * MUTEX:       Interpreter should be unlocked, because we may run the _REG
 *              method क्रम this region.
 *
 * NOTE:        Possible incompliance:
 *              There is a behavior conflict in स्वतःmatic _REG execution:
 *              1. When the पूर्णांकerpreter is evaluating a method, we can only
 *                 स्वतःmatically run _REG क्रम the following हाल:
 *                   operation_region (OPR1, 0x80, 0x1000010, 0x4)
 *              2. When the पूर्णांकerpreter is loading a table, we can also
 *                 स्वतःmatically run _REG क्रम the following हाल:
 *                   operation_region (OPR1, 0x80, 0x1000010, 0x4)
 *              Though this may not be compliant to the de-facto standard, the
 *              logic is kept in order not to trigger regressions. And keeping
 *              this logic should be taken care by the caller of this function.
 *
 ******************************************************************************/

acpi_status acpi_ev_initialize_region(जोड़ acpi_opeअक्रम_object *region_obj)
अणु
	जोड़ acpi_opeअक्रम_object *handler_obj;
	जोड़ acpi_opeअक्रम_object *obj_desc;
	acpi_adr_space_type space_id;
	काष्ठा acpi_namespace_node *node;

	ACPI_FUNCTION_TRACE(ev_initialize_region);

	अगर (!region_obj) अणु
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	अगर (region_obj->common.flags & AOPOBJ_OBJECT_INITIALIZED) अणु
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	region_obj->common.flags |= AOPOBJ_OBJECT_INITIALIZED;

	node = region_obj->region.node->parent;
	space_id = region_obj->region.space_id;

	/*
	 * The following loop depends upon the root Node having no parent
	 * ie: acpi_gbl_root_node->Parent being set to शून्य
	 */
	जबतक (node) अणु

		/* Check to see अगर a handler exists */

		handler_obj = शून्य;
		obj_desc = acpi_ns_get_attached_object(node);
		अगर (obj_desc) अणु

			/* Can only be a handler अगर the object exists */

			चयन (node->type) अणु
			हाल ACPI_TYPE_DEVICE:
			हाल ACPI_TYPE_PROCESSOR:
			हाल ACPI_TYPE_THERMAL:

				handler_obj = obj_desc->common_notअगरy.handler;
				अवरोध;

			शेष:

				/* Ignore other objects */

				अवरोध;
			पूर्ण

			handler_obj =
			    acpi_ev_find_region_handler(space_id, handler_obj);
			अगर (handler_obj) अणु

				/* Found correct handler */

				ACPI_DEBUG_PRINT((ACPI_DB_OPREGION,
						  "Found handler %p for region %p in obj %p\n",
						  handler_obj, region_obj,
						  obj_desc));

				(व्योम)acpi_ev_attach_region(handler_obj,
							    region_obj, FALSE);

				/*
				 * Tell all users that this region is usable by
				 * running the _REG method
				 */
				acpi_ex_निकास_पूर्णांकerpreter();
				(व्योम)acpi_ev_execute_reg_method(region_obj,
								 ACPI_REG_CONNECT);
				acpi_ex_enter_पूर्णांकerpreter();
				वापस_ACPI_STATUS(AE_OK);
			पूर्ण
		पूर्ण

		/* This node करोes not have the handler we need; Pop up one level */

		node = node->parent;
	पूर्ण

	/*
	 * If we get here, there is no handler क्रम this region. This is not
	 * fatal because many regions get created beक्रमe a handler is installed
	 * क्रम said region.
	 */
	ACPI_DEBUG_PRINT((ACPI_DB_OPREGION,
			  "No handler for RegionType %s(%X) (RegionObj %p)\n",
			  acpi_ut_get_region_name(space_id), space_id,
			  region_obj));

	वापस_ACPI_STATUS(AE_OK);
पूर्ण
