<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: evhandler - Support क्रम Address Space handlers
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
ACPI_MODULE_NAME("evhandler")

/* Local prototypes */
अटल acpi_status
acpi_ev_install_handler(acpi_handle obj_handle,
			u32 level, व्योम *context, व्योम **वापस_value);

/* These are the address spaces that will get शेष handlers */

u8 acpi_gbl_शेष_address_spaces[ACPI_NUM_DEFAULT_SPACES] = अणु
	ACPI_ADR_SPACE_SYSTEM_MEMORY,
	ACPI_ADR_SPACE_SYSTEM_IO,
	ACPI_ADR_SPACE_PCI_CONFIG,
	ACPI_ADR_SPACE_DATA_TABLE
पूर्ण;

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_install_region_handlers
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Installs the core subप्रणाली शेष address space handlers.
 *
 ******************************************************************************/

acpi_status acpi_ev_install_region_handlers(व्योम)
अणु
	acpi_status status;
	u32 i;

	ACPI_FUNCTION_TRACE(ev_install_region_handlers);

	status = acpi_ut_acquire_mutex(ACPI_MTX_NAMESPACE);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/*
	 * All address spaces (PCI Config, EC, SMBus) are scope dependent and
	 * registration must occur क्रम a specअगरic device.
	 *
	 * In the हाल of the प्रणाली memory and IO address spaces there is
	 * currently no device associated with the address space. For these we
	 * use the root.
	 *
	 * We install the शेष PCI config space handler at the root so that
	 * this space is immediately available even though the we have not
	 * क्रमागतerated all the PCI Root Buses yet. This is to conक्रमm to the ACPI
	 * specअगरication which states that the PCI config space must be always
	 * available -- even though we are nowhere near पढ़ोy to find the PCI root
	 * buses at this poपूर्णांक.
	 *
	 * NOTE: We ignore AE_ALREADY_EXISTS because this means that a handler
	 * has alपढ़ोy been installed (via acpi_install_address_space_handler).
	 * Similar क्रम AE_SAME_HANDLER.
	 */
	क्रम (i = 0; i < ACPI_NUM_DEFAULT_SPACES; i++) अणु
		status = acpi_ev_install_space_handler(acpi_gbl_root_node,
						       acpi_gbl_शेष_address_spaces
						       [i],
						       ACPI_DEFAULT_HANDLER,
						       शून्य, शून्य);
		चयन (status) अणु
		हाल AE_OK:
		हाल AE_SAME_HANDLER:
		हाल AE_ALREADY_EXISTS:

			/* These exceptions are all OK */

			status = AE_OK;
			अवरोध;

		शेष:

			जाओ unlock_and_निकास;
		पूर्ण
	पूर्ण

unlock_and_निकास:
	(व्योम)acpi_ut_release_mutex(ACPI_MTX_NAMESPACE);
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_has_शेष_handler
 *
 * PARAMETERS:  node                - Namespace node क्रम the device
 *              space_id            - The address space ID
 *
 * RETURN:      TRUE अगर शेष handler is installed, FALSE otherwise
 *
 * DESCRIPTION: Check अगर the शेष handler is installed क्रम the requested
 *              space ID.
 *
 ******************************************************************************/

u8
acpi_ev_has_शेष_handler(काष्ठा acpi_namespace_node *node,
			    acpi_adr_space_type space_id)
अणु
	जोड़ acpi_opeअक्रम_object *obj_desc;
	जोड़ acpi_opeअक्रम_object *handler_obj;

	/* Must have an existing पूर्णांकernal object */

	obj_desc = acpi_ns_get_attached_object(node);
	अगर (obj_desc) अणु
		handler_obj = obj_desc->common_notअगरy.handler;

		/* Walk the linked list of handlers क्रम this object */

		जबतक (handler_obj) अणु
			अगर (handler_obj->address_space.space_id == space_id) अणु
				अगर (handler_obj->address_space.handler_flags &
				    ACPI_ADDR_HANDLER_DEFAULT_INSTALLED) अणु
					वापस (TRUE);
				पूर्ण
			पूर्ण

			handler_obj = handler_obj->address_space.next;
		पूर्ण
	पूर्ण

	वापस (FALSE);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_install_handler
 *
 * PARAMETERS:  walk_namespace callback
 *
 * DESCRIPTION: This routine installs an address handler पूर्णांकo objects that are
 *              of type Region or Device.
 *
 *              If the Object is a Device, and the device has a handler of
 *              the same type then the search is terminated in that branch.
 *
 *              This is because the existing handler is बंदr in proximity
 *              to any more regions than the one we are trying to install.
 *
 ******************************************************************************/

अटल acpi_status
acpi_ev_install_handler(acpi_handle obj_handle,
			u32 level, व्योम *context, व्योम **वापस_value)
अणु
	जोड़ acpi_opeअक्रम_object *handler_obj;
	जोड़ acpi_opeअक्रम_object *next_handler_obj;
	जोड़ acpi_opeअक्रम_object *obj_desc;
	काष्ठा acpi_namespace_node *node;
	acpi_status status;

	ACPI_FUNCTION_NAME(ev_install_handler);

	handler_obj = (जोड़ acpi_opeअक्रम_object *)context;

	/* Parameter validation */

	अगर (!handler_obj) अणु
		वापस (AE_OK);
	पूर्ण

	/* Convert and validate the device handle */

	node = acpi_ns_validate_handle(obj_handle);
	अगर (!node) अणु
		वापस (AE_BAD_PARAMETER);
	पूर्ण

	/*
	 * We only care about regions and objects that are allowed to have
	 * address space handlers
	 */
	अगर ((node->type != ACPI_TYPE_DEVICE) &&
	    (node->type != ACPI_TYPE_REGION) && (node != acpi_gbl_root_node)) अणु
		वापस (AE_OK);
	पूर्ण

	/* Check क्रम an existing पूर्णांकernal object */

	obj_desc = acpi_ns_get_attached_object(node);
	अगर (!obj_desc) अणु

		/* No object, just निकास */

		वापस (AE_OK);
	पूर्ण

	/* Devices are handled dअगरferent than regions */

	अगर (obj_desc->common.type == ACPI_TYPE_DEVICE) अणु

		/* Check अगर this Device alपढ़ोy has a handler क्रम this address space */

		next_handler_obj =
		    acpi_ev_find_region_handler(handler_obj->address_space.
						space_id,
						obj_desc->common_notअगरy.
						handler);
		अगर (next_handler_obj) अणु

			/* Found a handler, is it क्रम the same address space? */

			ACPI_DEBUG_PRINT((ACPI_DB_OPREGION,
					  "Found handler for region [%s] in device %p(%p) handler %p\n",
					  acpi_ut_get_region_name(handler_obj->
								  address_space.
								  space_id),
					  obj_desc, next_handler_obj,
					  handler_obj));

			/*
			 * Since the object we found it on was a device, then it means
			 * that someone has alपढ़ोy installed a handler क्रम the branch
			 * of the namespace from this device on. Just bail out telling
			 * the walk routine to not traverse this branch. This preserves
			 * the scoping rule क्रम handlers.
			 */
			वापस (AE_CTRL_DEPTH);
		पूर्ण

		/*
		 * As दीर्घ as the device didn't have a handler क्रम this space we
		 * करोn't care about it. We just ignore it and proceed.
		 */
		वापस (AE_OK);
	पूर्ण

	/* Object is a Region */

	अगर (obj_desc->region.space_id != handler_obj->address_space.space_id) अणु

		/* This region is क्रम a dअगरferent address space, just ignore it */

		वापस (AE_OK);
	पूर्ण

	/*
	 * Now we have a region and it is क्रम the handler's address space type.
	 *
	 * First disconnect region क्रम any previous handler (अगर any)
	 */
	acpi_ev_detach_region(obj_desc, FALSE);

	/* Connect the region to the new handler */

	status = acpi_ev_attach_region(handler_obj, obj_desc, FALSE);
	वापस (status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_find_region_handler
 *
 * PARAMETERS:  space_id        - The address space ID
 *              handler_obj     - Head of the handler object list
 *
 * RETURN:      Matching handler object. शून्य अगर space ID not matched
 *
 * DESCRIPTION: Search a handler object list क्रम a match on the address
 *              space ID.
 *
 ******************************************************************************/

जोड़ acpi_opeअक्रम_object *acpi_ev_find_region_handler(acpi_adr_space_type
						       space_id,
						       जोड़ acpi_opeअक्रम_object
						       *handler_obj)
अणु

	/* Walk the handler list क्रम this device */

	जबतक (handler_obj) अणु

		/* Same space_id indicates a handler is installed */

		अगर (handler_obj->address_space.space_id == space_id) अणु
			वापस (handler_obj);
		पूर्ण

		/* Next handler object */

		handler_obj = handler_obj->address_space.next;
	पूर्ण

	वापस (शून्य);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_install_space_handler
 *
 * PARAMETERS:  node            - Namespace node क्रम the device
 *              space_id        - The address space ID
 *              handler         - Address of the handler
 *              setup           - Address of the setup function
 *              context         - Value passed to the handler on each access
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Install a handler क्रम all op_regions of a given space_id.
 *              Assumes namespace is locked
 *
 ******************************************************************************/

acpi_status
acpi_ev_install_space_handler(काष्ठा acpi_namespace_node *node,
			      acpi_adr_space_type space_id,
			      acpi_adr_space_handler handler,
			      acpi_adr_space_setup setup, व्योम *context)
अणु
	जोड़ acpi_opeअक्रम_object *obj_desc;
	जोड़ acpi_opeअक्रम_object *handler_obj;
	acpi_status status = AE_OK;
	acpi_object_type type;
	u8 flags = 0;

	ACPI_FUNCTION_TRACE(ev_install_space_handler);

	/*
	 * This registration is valid क्रम only the types below and the root.
	 * The root node is where the शेष handlers get installed.
	 */
	अगर ((node->type != ACPI_TYPE_DEVICE) &&
	    (node->type != ACPI_TYPE_PROCESSOR) &&
	    (node->type != ACPI_TYPE_THERMAL) && (node != acpi_gbl_root_node)) अणु
		status = AE_BAD_PARAMETER;
		जाओ unlock_and_निकास;
	पूर्ण

	अगर (handler == ACPI_DEFAULT_HANDLER) अणु
		flags = ACPI_ADDR_HANDLER_DEFAULT_INSTALLED;

		चयन (space_id) अणु
		हाल ACPI_ADR_SPACE_SYSTEM_MEMORY:

			handler = acpi_ex_प्रणाली_memory_space_handler;
			setup = acpi_ev_प्रणाली_memory_region_setup;
			अवरोध;

		हाल ACPI_ADR_SPACE_SYSTEM_IO:

			handler = acpi_ex_प्रणाली_io_space_handler;
			setup = acpi_ev_io_space_region_setup;
			अवरोध;
#अगर_घोषित ACPI_PCI_CONFIGURED
		हाल ACPI_ADR_SPACE_PCI_CONFIG:

			handler = acpi_ex_pci_config_space_handler;
			setup = acpi_ev_pci_config_region_setup;
			अवरोध;
#पूर्ण_अगर
		हाल ACPI_ADR_SPACE_CMOS:

			handler = acpi_ex_cmos_space_handler;
			setup = acpi_ev_cmos_region_setup;
			अवरोध;
#अगर_घोषित ACPI_PCI_CONFIGURED
		हाल ACPI_ADR_SPACE_PCI_BAR_TARGET:

			handler = acpi_ex_pci_bar_space_handler;
			setup = acpi_ev_pci_bar_region_setup;
			अवरोध;
#पूर्ण_अगर
		हाल ACPI_ADR_SPACE_DATA_TABLE:

			handler = acpi_ex_data_table_space_handler;
			setup = शून्य;
			अवरोध;

		शेष:

			status = AE_BAD_PARAMETER;
			जाओ unlock_and_निकास;
		पूर्ण
	पूर्ण

	/* If the caller hasn't specअगरied a setup routine, use the शेष */

	अगर (!setup) अणु
		setup = acpi_ev_शेष_region_setup;
	पूर्ण

	/* Check क्रम an existing पूर्णांकernal object */

	obj_desc = acpi_ns_get_attached_object(node);
	अगर (obj_desc) अणु
		/*
		 * The attached device object alपढ़ोy exists. Now make sure
		 * the handler is not alपढ़ोy installed.
		 */
		handler_obj = acpi_ev_find_region_handler(space_id,
							  obj_desc->
							  common_notअगरy.
							  handler);

		अगर (handler_obj) अणु
			अगर (handler_obj->address_space.handler == handler) अणु
				/*
				 * It is (relatively) OK to attempt to install the SAME
				 * handler twice. This can easily happen with the
				 * PCI_Config space.
				 */
				status = AE_SAME_HANDLER;
				जाओ unlock_and_निकास;
			पूर्ण अन्यथा अणु
				/* A handler is alपढ़ोy installed */

				status = AE_ALREADY_EXISTS;
			पूर्ण

			जाओ unlock_and_निकास;
		पूर्ण
	पूर्ण अन्यथा अणु
		ACPI_DEBUG_PRINT((ACPI_DB_OPREGION,
				  "Creating object on Device %p while installing handler\n",
				  node));

		/* obj_desc करोes not exist, create one */

		अगर (node->type == ACPI_TYPE_ANY) अणु
			type = ACPI_TYPE_DEVICE;
		पूर्ण अन्यथा अणु
			type = node->type;
		पूर्ण

		obj_desc = acpi_ut_create_पूर्णांकernal_object(type);
		अगर (!obj_desc) अणु
			status = AE_NO_MEMORY;
			जाओ unlock_and_निकास;
		पूर्ण

		/* Init new descriptor */

		obj_desc->common.type = (u8)type;

		/* Attach the new object to the Node */

		status = acpi_ns_attach_object(node, obj_desc, type);

		/* Remove local reference to the object */

		acpi_ut_हटाओ_reference(obj_desc);

		अगर (ACPI_FAILURE(status)) अणु
			जाओ unlock_and_निकास;
		पूर्ण
	पूर्ण

	ACPI_DEBUG_PRINT((ACPI_DB_OPREGION,
			  "Installing address handler for region %s(%X) "
			  "on Device %4.4s %p(%p)\n",
			  acpi_ut_get_region_name(space_id), space_id,
			  acpi_ut_get_node_name(node), node, obj_desc));

	/*
	 * Install the handler
	 *
	 * At this poपूर्णांक there is no existing handler. Just allocate the object
	 * क्रम the handler and link it पूर्णांकo the list.
	 */
	handler_obj =
	    acpi_ut_create_पूर्णांकernal_object(ACPI_TYPE_LOCAL_ADDRESS_HANDLER);
	अगर (!handler_obj) अणु
		status = AE_NO_MEMORY;
		जाओ unlock_and_निकास;
	पूर्ण

	/* Init handler obj */

	status =
	    acpi_os_create_mutex(&handler_obj->address_space.context_mutex);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_ut_हटाओ_reference(handler_obj);
		जाओ unlock_and_निकास;
	पूर्ण

	handler_obj->address_space.space_id = (u8)space_id;
	handler_obj->address_space.handler_flags = flags;
	handler_obj->address_space.region_list = शून्य;
	handler_obj->address_space.node = node;
	handler_obj->address_space.handler = handler;
	handler_obj->address_space.context = context;
	handler_obj->address_space.setup = setup;

	/* Install at head of Device.address_space list */

	handler_obj->address_space.next = obj_desc->common_notअगरy.handler;

	/*
	 * The Device object is the first reference on the handler_obj.
	 * Each region that uses the handler adds a reference.
	 */
	obj_desc->common_notअगरy.handler = handler_obj;

	/*
	 * Walk the namespace finding all of the regions this handler will
	 * manage.
	 *
	 * Start at the device and search the branch toward the leaf nodes
	 * until either the leaf is encountered or a device is detected that
	 * has an address handler of the same type.
	 *
	 * In either हाल, back up and search करोwn the reमुख्यder of the branch
	 */
	status = acpi_ns_walk_namespace(ACPI_TYPE_ANY, node,
					ACPI_UINT32_MAX, ACPI_NS_WALK_UNLOCK,
					acpi_ev_install_handler, शून्य,
					handler_obj, शून्य);

unlock_and_निकास:
	वापस_ACPI_STATUS(status);
पूर्ण
