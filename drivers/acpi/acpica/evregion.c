<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: evregion - Operation Region support
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
ACPI_MODULE_NAME("evregion")

बाह्य u8 acpi_gbl_शेष_address_spaces[];

/* Local prototypes */

अटल व्योम
acpi_ev_execute_orphan_reg_method(काष्ठा acpi_namespace_node *device_node,
				  acpi_adr_space_type space_id);

अटल acpi_status
acpi_ev_reg_run(acpi_handle obj_handle,
		u32 level, व्योम *context, व्योम **वापस_value);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_initialize_op_regions
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Execute _REG methods क्रम all Operation Regions that have
 *              an installed शेष region handler.
 *
 ******************************************************************************/

acpi_status acpi_ev_initialize_op_regions(व्योम)
अणु
	acpi_status status;
	u32 i;

	ACPI_FUNCTION_TRACE(ev_initialize_op_regions);

	status = acpi_ut_acquire_mutex(ACPI_MTX_NAMESPACE);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Run the _REG methods क्रम op_regions in each शेष address space */

	क्रम (i = 0; i < ACPI_NUM_DEFAULT_SPACES; i++) अणु
		/*
		 * Make sure the installed handler is the DEFAULT handler. If not the
		 * शेष, the _REG methods will have alपढ़ोy been run (when the
		 * handler was installed)
		 */
		अगर (acpi_ev_has_शेष_handler(acpi_gbl_root_node,
						acpi_gbl_शेष_address_spaces
						[i])) अणु
			acpi_ev_execute_reg_methods(acpi_gbl_root_node,
						    acpi_gbl_शेष_address_spaces
						    [i], ACPI_REG_CONNECT);
		पूर्ण
	पूर्ण

	(व्योम)acpi_ut_release_mutex(ACPI_MTX_NAMESPACE);
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_address_space_dispatch
 *
 * PARAMETERS:  region_obj          - Internal region object
 *              field_obj           - Corresponding field. Can be शून्य.
 *              function            - Read or Write operation
 *              region_offset       - Where in the region to पढ़ो or ग_लिखो
 *              bit_width           - Field width in bits (8, 16, 32, or 64)
 *              value               - Poपूर्णांकer to in or out value, must be
 *                                    a full 64-bit पूर्णांकeger
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Dispatch an address space or operation region access to
 *              a previously installed handler.
 *
 * NOTE: During early initialization, we always install the शेष region
 * handlers क्रम Memory, I/O and PCI_Config. This ensures that these operation
 * region address spaces are always available as per the ACPI specअगरication.
 * This is especially needed in order to support the execution of
 * module-level AML code during loading of the ACPI tables.
 *
 ******************************************************************************/

acpi_status
acpi_ev_address_space_dispatch(जोड़ acpi_opeअक्रम_object *region_obj,
			       जोड़ acpi_opeअक्रम_object *field_obj,
			       u32 function,
			       u32 region_offset, u32 bit_width, u64 *value)
अणु
	acpi_status status;
	acpi_adr_space_handler handler;
	acpi_adr_space_setup region_setup;
	जोड़ acpi_opeअक्रम_object *handler_desc;
	जोड़ acpi_opeअक्रम_object *region_obj2;
	व्योम *region_context = शून्य;
	काष्ठा acpi_connection_info *context;
	acpi_mutex context_mutex;
	u8 context_locked;
	acpi_physical_address address;

	ACPI_FUNCTION_TRACE(ev_address_space_dispatch);

	region_obj2 = acpi_ns_get_secondary_object(region_obj);
	अगर (!region_obj2) अणु
		वापस_ACPI_STATUS(AE_NOT_EXIST);
	पूर्ण

	/* Ensure that there is a handler associated with this region */

	handler_desc = region_obj->region.handler;
	अगर (!handler_desc) अणु
		ACPI_ERROR((AE_INFO,
			    "No handler for Region [%4.4s] (%p) [%s]",
			    acpi_ut_get_node_name(region_obj->region.node),
			    region_obj,
			    acpi_ut_get_region_name(region_obj->region.
						    space_id)));

		वापस_ACPI_STATUS(AE_NOT_EXIST);
	पूर्ण

	context = handler_desc->address_space.context;
	context_mutex = handler_desc->address_space.context_mutex;
	context_locked = FALSE;

	/*
	 * It may be the हाल that the region has never been initialized.
	 * Some types of regions require special init code
	 */
	अगर (!(region_obj->region.flags & AOPOBJ_SETUP_COMPLETE)) अणु

		/* This region has not been initialized yet, करो it */

		region_setup = handler_desc->address_space.setup;
		अगर (!region_setup) अणु

			/* No initialization routine, निकास with error */

			ACPI_ERROR((AE_INFO,
				    "No init routine for region(%p) [%s]",
				    region_obj,
				    acpi_ut_get_region_name(region_obj->region.
							    space_id)));
			वापस_ACPI_STATUS(AE_NOT_EXIST);
		पूर्ण

		/*
		 * We must निकास the पूर्णांकerpreter because the region setup will
		 * potentially execute control methods (क्रम example, the _REG method
		 * क्रम this region)
		 */
		acpi_ex_निकास_पूर्णांकerpreter();

		status = region_setup(region_obj, ACPI_REGION_ACTIVATE,
				      context, &region_context);

		/* Re-enter the पूर्णांकerpreter */

		acpi_ex_enter_पूर्णांकerpreter();

		/* Check क्रम failure of the Region Setup */

		अगर (ACPI_FAILURE(status)) अणु
			ACPI_EXCEPTION((AE_INFO, status,
					"During region initialization: [%s]",
					acpi_ut_get_region_name(region_obj->
								region.
								space_id)));
			वापस_ACPI_STATUS(status);
		पूर्ण

		/* Region initialization may have been completed by region_setup */

		अगर (!(region_obj->region.flags & AOPOBJ_SETUP_COMPLETE)) अणु
			region_obj->region.flags |= AOPOBJ_SETUP_COMPLETE;

			/*
			 * Save the वापसed context क्रम use in all accesses to
			 * the handler क्रम this particular region
			 */
			अगर (!(region_obj2->extra.region_context)) अणु
				region_obj2->extra.region_context =
				    region_context;
			पूर्ण
		पूर्ण
	पूर्ण

	/* We have everything we need, we can invoke the address space handler */

	handler = handler_desc->address_space.handler;
	address = (region_obj->region.address + region_offset);

	ACPI_DEBUG_PRINT((ACPI_DB_OPREGION,
			  "Handler %p (@%p) Address %8.8X%8.8X [%s]\n",
			  &region_obj->region.handler->address_space, handler,
			  ACPI_FORMAT_UINT64(address),
			  acpi_ut_get_region_name(region_obj->region.
						  space_id)));

	अगर (!(handler_desc->address_space.handler_flags &
	      ACPI_ADDR_HANDLER_DEFAULT_INSTALLED)) अणु
		/*
		 * For handlers other than the शेष (supplied) handlers, we must
		 * निकास the पूर्णांकerpreter because the handler *might* block -- we करोn't
		 * know what it will करो, so we can't hold the lock on the पूर्णांकerpreter.
		 */
		acpi_ex_निकास_पूर्णांकerpreter();
	पूर्ण

	/*
	 * Special handling क्रम generic_serial_bus and general_purpose_io:
	 * There are three extra parameters that must be passed to the
	 * handler via the context:
	 *   1) Connection buffer, a resource ढाँचा from Connection() op
	 *   2) Length of the above buffer
	 *   3) Actual access length from the access_as() op
	 *
	 * Since we pass these extra parameters via the context, which is
	 * shared between thपढ़ोs, we must lock the context to aव्योम these
	 * parameters being changed from another thपढ़ो beक्रमe the handler
	 * has completed running.
	 *
	 * In addition, क्रम general_purpose_io, the Address and bit_width fields
	 * are defined as follows:
	 *   1) Address is the pin number index of the field (bit offset from
	 *      the previous Connection)
	 *   2) bit_width is the actual bit length of the field (number of pins)
	 */
	अगर ((region_obj->region.space_id == ACPI_ADR_SPACE_GSBUS ||
	     region_obj->region.space_id == ACPI_ADR_SPACE_GPIO) &&
	    context && field_obj) अणु

		status =
		    acpi_os_acquire_mutex(context_mutex, ACPI_WAIT_FOREVER);
		अगर (ACPI_FAILURE(status)) अणु
			जाओ re_enter_पूर्णांकerpreter;
		पूर्ण

		context_locked = TRUE;

		/* Get the Connection (resource_ढाँचा) buffer */

		context->connection = field_obj->field.resource_buffer;
		context->length = field_obj->field.resource_length;
		context->access_length = field_obj->field.access_length;

		अगर (region_obj->region.space_id == ACPI_ADR_SPACE_GPIO) अणु
			address = field_obj->field.pin_number_index;
			bit_width = field_obj->field.bit_length;
		पूर्ण
	पूर्ण

	/* Call the handler */

	status = handler(function, address, bit_width, value, context,
			 region_obj2->extra.region_context);

	अगर (context_locked) अणु
		acpi_os_release_mutex(context_mutex);
	पूर्ण

	अगर (ACPI_FAILURE(status)) अणु
		ACPI_EXCEPTION((AE_INFO, status, "Returned by Handler for [%s]",
				acpi_ut_get_region_name(region_obj->region.
							space_id)));

		/*
		 * Special हाल क्रम an EC समयout. These are seen so frequently
		 * that an additional error message is helpful
		 */
		अगर ((region_obj->region.space_id == ACPI_ADR_SPACE_EC) &&
		    (status == AE_TIME)) अणु
			ACPI_ERROR((AE_INFO,
				    "Timeout from EC hardware or EC device driver"));
		पूर्ण
	पूर्ण

re_enter_पूर्णांकerpreter:
	अगर (!(handler_desc->address_space.handler_flags &
	      ACPI_ADDR_HANDLER_DEFAULT_INSTALLED)) अणु
		/*
		 * We just वापसed from a non-शेष handler, we must re-enter the
		 * पूर्णांकerpreter
		 */
		acpi_ex_enter_पूर्णांकerpreter();
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_detach_region
 *
 * PARAMETERS:  region_obj          - Region Object
 *              acpi_ns_is_locked   - Namespace Region Alपढ़ोy Locked?
 *
 * RETURN:      None
 *
 * DESCRIPTION: Break the association between the handler and the region
 *              this is a two way association.
 *
 ******************************************************************************/

व्योम
acpi_ev_detach_region(जोड़ acpi_opeअक्रम_object *region_obj,
		      u8 acpi_ns_is_locked)
अणु
	जोड़ acpi_opeअक्रम_object *handler_obj;
	जोड़ acpi_opeअक्रम_object *obj_desc;
	जोड़ acpi_opeअक्रम_object *start_desc;
	जोड़ acpi_opeअक्रम_object **last_obj_ptr;
	acpi_adr_space_setup region_setup;
	व्योम **region_context;
	जोड़ acpi_opeअक्रम_object *region_obj2;
	acpi_status status;

	ACPI_FUNCTION_TRACE(ev_detach_region);

	region_obj2 = acpi_ns_get_secondary_object(region_obj);
	अगर (!region_obj2) अणु
		वापस_VOID;
	पूर्ण
	region_context = &region_obj2->extra.region_context;

	/* Get the address handler from the region object */

	handler_obj = region_obj->region.handler;
	अगर (!handler_obj) अणु

		/* This region has no handler, all करोne */

		वापस_VOID;
	पूर्ण

	/* Find this region in the handler's list */

	obj_desc = handler_obj->address_space.region_list;
	start_desc = obj_desc;
	last_obj_ptr = &handler_obj->address_space.region_list;

	जबतक (obj_desc) अणु

		/* Is this the correct Region? */

		अगर (obj_desc == region_obj) अणु
			ACPI_DEBUG_PRINT((ACPI_DB_OPREGION,
					  "Removing Region %p from address handler %p\n",
					  region_obj, handler_obj));

			/* This is it, हटाओ it from the handler's list */

			*last_obj_ptr = obj_desc->region.next;
			obj_desc->region.next = शून्य;	/* Must clear field */

			अगर (acpi_ns_is_locked) अणु
				status =
				    acpi_ut_release_mutex(ACPI_MTX_NAMESPACE);
				अगर (ACPI_FAILURE(status)) अणु
					वापस_VOID;
				पूर्ण
			पूर्ण

			/* Now stop region accesses by executing the _REG method */

			status =
			    acpi_ev_execute_reg_method(region_obj,
						       ACPI_REG_DISCONNECT);
			अगर (ACPI_FAILURE(status)) अणु
				ACPI_EXCEPTION((AE_INFO, status,
						"from region _REG, [%s]",
						acpi_ut_get_region_name
						(region_obj->region.space_id)));
			पूर्ण

			अगर (acpi_ns_is_locked) अणु
				status =
				    acpi_ut_acquire_mutex(ACPI_MTX_NAMESPACE);
				अगर (ACPI_FAILURE(status)) अणु
					वापस_VOID;
				पूर्ण
			पूर्ण

			/*
			 * If the region has been activated, call the setup handler with
			 * the deactivate notअगरication
			 */
			अगर (region_obj->region.flags & AOPOBJ_SETUP_COMPLETE) अणु
				region_setup = handler_obj->address_space.setup;
				status =
				    region_setup(region_obj,
						 ACPI_REGION_DEACTIVATE,
						 handler_obj->address_space.
						 context, region_context);

				/*
				 * region_context should have been released by the deactivate
				 * operation. We करोn't need access to it anymore here.
				 */
				अगर (region_context) अणु
					*region_context = शून्य;
				पूर्ण

				/* Init routine may fail, Just ignore errors */

				अगर (ACPI_FAILURE(status)) अणु
					ACPI_EXCEPTION((AE_INFO, status,
							"from region handler - deactivate, [%s]",
							acpi_ut_get_region_name
							(region_obj->region.
							 space_id)));
				पूर्ण

				region_obj->region.flags &=
				    ~(AOPOBJ_SETUP_COMPLETE);
			पूर्ण

			/*
			 * Remove handler reference in the region
			 *
			 * NOTE: this करोesn't mean that the region goes away, the region
			 * is just inaccessible as indicated to the _REG method
			 *
			 * If the region is on the handler's list, this must be the
			 * region's handler
			 */
			region_obj->region.handler = शून्य;
			acpi_ut_हटाओ_reference(handler_obj);

			वापस_VOID;
		पूर्ण

		/* Walk the linked list of handlers */

		last_obj_ptr = &obj_desc->region.next;
		obj_desc = obj_desc->region.next;

		/* Prevent infinite loop अगर list is corrupted */

		अगर (obj_desc == start_desc) अणु
			ACPI_ERROR((AE_INFO,
				    "Circular handler list in region object %p",
				    region_obj));
			वापस_VOID;
		पूर्ण
	पूर्ण

	/* If we get here, the region was not in the handler's region list */

	ACPI_DEBUG_PRINT((ACPI_DB_OPREGION,
			  "Cannot remove region %p from address handler %p\n",
			  region_obj, handler_obj));

	वापस_VOID;
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_attach_region
 *
 * PARAMETERS:  handler_obj         - Handler Object
 *              region_obj          - Region Object
 *              acpi_ns_is_locked   - Namespace Region Alपढ़ोy Locked?
 *
 * RETURN:      None
 *
 * DESCRIPTION: Create the association between the handler and the region
 *              this is a two way association.
 *
 ******************************************************************************/

acpi_status
acpi_ev_attach_region(जोड़ acpi_opeअक्रम_object *handler_obj,
		      जोड़ acpi_opeअक्रम_object *region_obj,
		      u8 acpi_ns_is_locked)
अणु

	ACPI_FUNCTION_TRACE(ev_attach_region);

	/* Install the region's handler */

	अगर (region_obj->region.handler) अणु
		वापस_ACPI_STATUS(AE_ALREADY_EXISTS);
	पूर्ण

	ACPI_DEBUG_PRINT((ACPI_DB_OPREGION,
			  "Adding Region [%4.4s] %p to address handler %p [%s]\n",
			  acpi_ut_get_node_name(region_obj->region.node),
			  region_obj, handler_obj,
			  acpi_ut_get_region_name(region_obj->region.
						  space_id)));

	/* Link this region to the front of the handler's list */

	region_obj->region.next = handler_obj->address_space.region_list;
	handler_obj->address_space.region_list = region_obj;
	region_obj->region.handler = handler_obj;
	acpi_ut_add_reference(handler_obj);

	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_execute_reg_method
 *
 * PARAMETERS:  region_obj          - Region object
 *              function            - Passed to _REG: On (1) or Off (0)
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Execute _REG method क्रम a region
 *
 ******************************************************************************/

acpi_status
acpi_ev_execute_reg_method(जोड़ acpi_opeअक्रम_object *region_obj, u32 function)
अणु
	काष्ठा acpi_evaluate_info *info;
	जोड़ acpi_opeअक्रम_object *args[3];
	जोड़ acpi_opeअक्रम_object *region_obj2;
	स्थिर acpi_name *reg_name_ptr =
	    ACPI_CAST_PTR(acpi_name, METHOD_NAME__REG);
	काष्ठा acpi_namespace_node *method_node;
	काष्ठा acpi_namespace_node *node;
	acpi_status status;

	ACPI_FUNCTION_TRACE(ev_execute_reg_method);

	अगर (!acpi_gbl_namespace_initialized ||
	    region_obj->region.handler == शून्य) अणु
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	region_obj2 = acpi_ns_get_secondary_object(region_obj);
	अगर (!region_obj2) अणु
		वापस_ACPI_STATUS(AE_NOT_EXIST);
	पूर्ण

	/*
	 * Find any "_REG" method associated with this region definition.
	 * The method should always be updated as this function may be
	 * invoked after a namespace change.
	 */
	node = region_obj->region.node->parent;
	status =
	    acpi_ns_search_one_scope(*reg_name_ptr, node, ACPI_TYPE_METHOD,
				     &method_node);
	अगर (ACPI_SUCCESS(status)) अणु
		/*
		 * The _REG method is optional and there can be only one per
		 * region definition. This will be executed when the handler is
		 * attached or हटाओd.
		 */
		region_obj2->extra.method_REG = method_node;
	पूर्ण
	अगर (region_obj2->extra.method_REG == शून्य) अणु
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	/* _REG(DISCONNECT) should be paired with _REG(CONNECT) */

	अगर ((function == ACPI_REG_CONNECT &&
	     region_obj->common.flags & AOPOBJ_REG_CONNECTED) ||
	    (function == ACPI_REG_DISCONNECT &&
	     !(region_obj->common.flags & AOPOBJ_REG_CONNECTED))) अणु
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	/* Allocate and initialize the evaluation inक्रमmation block */

	info = ACPI_ALLOCATE_ZEROED(माप(काष्ठा acpi_evaluate_info));
	अगर (!info) अणु
		वापस_ACPI_STATUS(AE_NO_MEMORY);
	पूर्ण

	info->prefix_node = region_obj2->extra.method_REG;
	info->relative_pathname = शून्य;
	info->parameters = args;
	info->flags = ACPI_IGNORE_RETURN_VALUE;

	/*
	 * The _REG method has two arguments:
	 *
	 * arg0 - Integer:
	 *  Operation region space ID Same value as region_obj->Region.space_id
	 *
	 * arg1 - Integer:
	 *  connection status 1 क्रम connecting the handler, 0 क्रम disconnecting
	 *  the handler (Passed as a parameter)
	 */
	args[0] =
	    acpi_ut_create_पूर्णांकeger_object((u64)region_obj->region.space_id);
	अगर (!args[0]) अणु
		status = AE_NO_MEMORY;
		जाओ cleanup1;
	पूर्ण

	args[1] = acpi_ut_create_पूर्णांकeger_object((u64)function);
	अगर (!args[1]) अणु
		status = AE_NO_MEMORY;
		जाओ cleanup2;
	पूर्ण

	args[2] = शून्य;		/* Terminate list */

	/* Execute the method, no वापस value */

	ACPI_DEBUG_EXEC(acpi_ut_display_init_pathname
			(ACPI_TYPE_METHOD, info->prefix_node, शून्य));

	status = acpi_ns_evaluate(info);
	acpi_ut_हटाओ_reference(args[1]);

	अगर (ACPI_FAILURE(status)) अणु
		जाओ cleanup2;
	पूर्ण

	अगर (function == ACPI_REG_CONNECT) अणु
		region_obj->common.flags |= AOPOBJ_REG_CONNECTED;
	पूर्ण अन्यथा अणु
		region_obj->common.flags &= ~AOPOBJ_REG_CONNECTED;
	पूर्ण

cleanup2:
	acpi_ut_हटाओ_reference(args[0]);

cleanup1:
	ACPI_FREE(info);
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_execute_reg_methods
 *
 * PARAMETERS:  node            - Namespace node क्रम the device
 *              space_id        - The address space ID
 *              function        - Passed to _REG: On (1) or Off (0)
 *
 * RETURN:      None
 *
 * DESCRIPTION: Run all _REG methods क्रम the input Space ID;
 *              Note: assumes namespace is locked, or प्रणाली init समय.
 *
 ******************************************************************************/

व्योम
acpi_ev_execute_reg_methods(काष्ठा acpi_namespace_node *node,
			    acpi_adr_space_type space_id, u32 function)
अणु
	काष्ठा acpi_reg_walk_info info;

	ACPI_FUNCTION_TRACE(ev_execute_reg_methods);

	/*
	 * These address spaces करो not need a call to _REG, since the ACPI
	 * specअगरication defines them as: "must always be accessible". Since
	 * they never change state (never become unavailable), no need to ever
	 * call _REG on them. Also, a data_table is not a "real" address space,
	 * so करो not call _REG. September 2018.
	 */
	अगर ((space_id == ACPI_ADR_SPACE_SYSTEM_MEMORY) ||
	    (space_id == ACPI_ADR_SPACE_SYSTEM_IO) ||
	    (space_id == ACPI_ADR_SPACE_DATA_TABLE)) अणु
		वापस_VOID;
	पूर्ण

	info.space_id = space_id;
	info.function = function;
	info.reg_run_count = 0;

	ACPI_DEBUG_PRINT_RAW((ACPI_DB_NAMES,
			      "    Running _REG methods for SpaceId %s\n",
			      acpi_ut_get_region_name(info.space_id)));

	/*
	 * Run all _REG methods क्रम all Operation Regions क्रम this space ID. This
	 * is a separate walk in order to handle any पूर्णांकerdependencies between
	 * regions and _REG methods. (i.e. handlers must be installed क्रम all
	 * regions of this Space ID beक्रमe we can run any _REG methods)
	 */
	(व्योम)acpi_ns_walk_namespace(ACPI_TYPE_ANY, node, ACPI_UINT32_MAX,
				     ACPI_NS_WALK_UNLOCK, acpi_ev_reg_run, शून्य,
				     &info, शून्य);

	/*
	 * Special हाल क्रम EC and GPIO: handle "orphan" _REG methods with
	 * no region.
	 */
	अगर (space_id == ACPI_ADR_SPACE_EC || space_id == ACPI_ADR_SPACE_GPIO) अणु
		acpi_ev_execute_orphan_reg_method(node, space_id);
	पूर्ण

	ACPI_DEBUG_PRINT_RAW((ACPI_DB_NAMES,
			      "    Executed %u _REG methods for SpaceId %s\n",
			      info.reg_run_count,
			      acpi_ut_get_region_name(info.space_id)));

	वापस_VOID;
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_reg_run
 *
 * PARAMETERS:  walk_namespace callback
 *
 * DESCRIPTION: Run _REG method क्रम region objects of the requested spaceID
 *
 ******************************************************************************/

अटल acpi_status
acpi_ev_reg_run(acpi_handle obj_handle,
		u32 level, व्योम *context, व्योम **वापस_value)
अणु
	जोड़ acpi_opeअक्रम_object *obj_desc;
	काष्ठा acpi_namespace_node *node;
	acpi_status status;
	काष्ठा acpi_reg_walk_info *info;

	info = ACPI_CAST_PTR(काष्ठा acpi_reg_walk_info, context);

	/* Convert and validate the device handle */

	node = acpi_ns_validate_handle(obj_handle);
	अगर (!node) अणु
		वापस (AE_BAD_PARAMETER);
	पूर्ण

	/*
	 * We only care about regions and objects that are allowed to have
	 * address space handlers
	 */
	अगर ((node->type != ACPI_TYPE_REGION) && (node != acpi_gbl_root_node)) अणु
		वापस (AE_OK);
	पूर्ण

	/* Check क्रम an existing पूर्णांकernal object */

	obj_desc = acpi_ns_get_attached_object(node);
	अगर (!obj_desc) अणु

		/* No object, just निकास */

		वापस (AE_OK);
	पूर्ण

	/* Object is a Region */

	अगर (obj_desc->region.space_id != info->space_id) अणु

		/* This region is क्रम a dअगरferent address space, just ignore it */

		वापस (AE_OK);
	पूर्ण

	info->reg_run_count++;
	status = acpi_ev_execute_reg_method(obj_desc, info->function);
	वापस (status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_execute_orphan_reg_method
 *
 * PARAMETERS:  device_node         - Namespace node क्रम an ACPI device
 *              space_id            - The address space ID
 *
 * RETURN:      None
 *
 * DESCRIPTION: Execute an "orphan" _REG method that appears under an ACPI
 *              device. This is a _REG method that has no corresponding region
 *              within the device's scope. ACPI tables depending on these
 *              "orphan" _REG methods have been seen क्रम both EC and GPIO
 *              Operation Regions. Presumably the Winकरोws ACPI implementation
 *              always calls the _REG method independent of the presence of
 *              an actual Operation Region with the correct address space ID.
 *
 *  MUTEX:      Assumes the namespace is locked
 *
 ******************************************************************************/

अटल व्योम
acpi_ev_execute_orphan_reg_method(काष्ठा acpi_namespace_node *device_node,
				  acpi_adr_space_type space_id)
अणु
	acpi_handle reg_method;
	काष्ठा acpi_namespace_node *next_node;
	acpi_status status;
	काष्ठा acpi_object_list args;
	जोड़ acpi_object objects[2];

	ACPI_FUNCTION_TRACE(ev_execute_orphan_reg_method);

	अगर (!device_node) अणु
		वापस_VOID;
	पूर्ण

	/* Namespace is currently locked, must release */

	(व्योम)acpi_ut_release_mutex(ACPI_MTX_NAMESPACE);

	/* Get a handle to a _REG method immediately under the EC device */

	status = acpi_get_handle(device_node, METHOD_NAME__REG, &reg_method);
	अगर (ACPI_FAILURE(status)) अणु
		जाओ निकास;	/* There is no _REG method present */
	पूर्ण

	/*
	 * Execute the _REG method only अगर there is no Operation Region in
	 * this scope with the Embedded Controller space ID. Otherwise, it
	 * will alपढ़ोy have been executed. Note, this allows क्रम Regions
	 * with other space IDs to be present; but the code below will then
	 * execute the _REG method with the embedded_control space_ID argument.
	 */
	next_node = acpi_ns_get_next_node(device_node, शून्य);
	जबतक (next_node) अणु
		अगर ((next_node->type == ACPI_TYPE_REGION) &&
		    (next_node->object) &&
		    (next_node->object->region.space_id == space_id)) अणु
			जाओ निकास;	/* Do not execute the _REG */
		पूर्ण

		next_node = acpi_ns_get_next_node(device_node, next_node);
	पूर्ण

	/* Evaluate the _REG(space_id,Connect) method */

	args.count = 2;
	args.poपूर्णांकer = objects;
	objects[0].type = ACPI_TYPE_INTEGER;
	objects[0].पूर्णांकeger.value = space_id;
	objects[1].type = ACPI_TYPE_INTEGER;
	objects[1].पूर्णांकeger.value = ACPI_REG_CONNECT;

	(व्योम)acpi_evaluate_object(reg_method, शून्य, &args, शून्य);

निकास:
	/* We ignore all errors from above, करोn't care */

	(व्योम)acpi_ut_acquire_mutex(ACPI_MTX_NAMESPACE);
	वापस_VOID;
पूर्ण
