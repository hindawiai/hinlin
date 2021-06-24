<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: nsinit - namespace initialization
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acnamesp.h"
#समावेश "acdispat.h"
#समावेश "acinterp.h"
#समावेश "acevents.h"

#घोषणा _COMPONENT          ACPI_NAMESPACE
ACPI_MODULE_NAME("nsinit")

/* Local prototypes */
अटल acpi_status
acpi_ns_init_one_object(acpi_handle obj_handle,
			u32 level, व्योम *context, व्योम **वापस_value);

अटल acpi_status
acpi_ns_init_one_device(acpi_handle obj_handle,
			u32 nesting_level, व्योम *context, व्योम **वापस_value);

अटल acpi_status
acpi_ns_find_ini_methods(acpi_handle obj_handle,
			 u32 nesting_level, व्योम *context, व्योम **वापस_value);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_initialize_objects
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Walk the entire namespace and perक्रमm any necessary
 *              initialization on the objects found therein
 *
 ******************************************************************************/

acpi_status acpi_ns_initialize_objects(व्योम)
अणु
	acpi_status status;
	काष्ठा acpi_init_walk_info info;

	ACPI_FUNCTION_TRACE(ns_initialize_objects);

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
			  "[Init] Completing Initialization of ACPI Objects\n"));
	ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
			  "**** Starting initialization of namespace objects ****\n"));
	ACPI_DEBUG_PRINT_RAW((ACPI_DB_INIT,
			      "Final data object initialization: "));

	/* Clear the info block */

	स_रखो(&info, 0, माप(काष्ठा acpi_init_walk_info));

	/* Walk entire namespace from the supplied root */

	/*
	 * TBD: will become ACPI_TYPE_PACKAGE as this type object
	 * is now the only one that supports deferred initialization
	 * (क्रमward references).
	 */
	status = acpi_walk_namespace(ACPI_TYPE_ANY, ACPI_ROOT_OBJECT,
				     ACPI_UINT32_MAX, acpi_ns_init_one_object,
				     शून्य, &info, शून्य);
	अगर (ACPI_FAILURE(status)) अणु
		ACPI_EXCEPTION((AE_INFO, status, "During WalkNamespace"));
	पूर्ण

	ACPI_DEBUG_PRINT_RAW((ACPI_DB_INIT,
			      "Namespace contains %u (0x%X) objects\n",
			      info.object_count, info.object_count));

	ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
			  "%u Control Methods found\n%u Op Regions found\n",
			  info.method_count, info.op_region_count));

	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_initialize_devices
 *
 * PARAMETERS:  None
 *
 * RETURN:      acpi_status
 *
 * DESCRIPTION: Walk the entire namespace and initialize all ACPI devices.
 *              This means running _INI on all present devices.
 *
 *              Note: We install PCI config space handler on region access,
 *              not here.
 *
 ******************************************************************************/

acpi_status acpi_ns_initialize_devices(u32 flags)
अणु
	acpi_status status = AE_OK;
	काष्ठा acpi_device_walk_info info;
	acpi_handle handle;

	ACPI_FUNCTION_TRACE(ns_initialize_devices);

	अगर (!(flags & ACPI_NO_DEVICE_INIT)) अणु
		ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
				  "[Init] Initializing ACPI Devices\n"));

		/* Init counters */

		info.device_count = 0;
		info.num_STA = 0;
		info.num_INI = 0;

		ACPI_DEBUG_PRINT_RAW((ACPI_DB_INIT,
				      "Initializing Device/Processor/Thermal objects "
				      "and executing _INI/_STA methods:\n"));

		/* Tree analysis: find all subtrees that contain _INI methods */

		status = acpi_ns_walk_namespace(ACPI_TYPE_ANY, ACPI_ROOT_OBJECT,
						ACPI_UINT32_MAX, FALSE,
						acpi_ns_find_ini_methods, शून्य,
						&info, शून्य);
		अगर (ACPI_FAILURE(status)) अणु
			जाओ error_निकास;
		पूर्ण

		/* Allocate the evaluation inक्रमmation block */

		info.evaluate_info =
		    ACPI_ALLOCATE_ZEROED(माप(काष्ठा acpi_evaluate_info));
		अगर (!info.evaluate_info) अणु
			status = AE_NO_MEMORY;
			जाओ error_निकास;
		पूर्ण

		/*
		 * Execute the "global" _INI method that may appear at the root.
		 * This support is provided क्रम Winकरोws compatibility (Vista+) and
		 * is not part of the ACPI specअगरication.
		 */
		info.evaluate_info->prefix_node = acpi_gbl_root_node;
		info.evaluate_info->relative_pathname = METHOD_NAME__INI;
		info.evaluate_info->parameters = शून्य;
		info.evaluate_info->flags = ACPI_IGNORE_RETURN_VALUE;

		status = acpi_ns_evaluate(info.evaluate_info);
		अगर (ACPI_SUCCESS(status)) अणु
			info.num_INI++;
		पूर्ण

		/*
		 * Execute \_SB._INI.
		 * There appears to be a strict order requirement क्रम \_SB._INI,
		 * which should be evaluated beक्रमe any _REG evaluations.
		 */
		status = acpi_get_handle(शून्य, "\\_SB", &handle);
		अगर (ACPI_SUCCESS(status)) अणु
			स_रखो(info.evaluate_info, 0,
			       माप(काष्ठा acpi_evaluate_info));
			info.evaluate_info->prefix_node = handle;
			info.evaluate_info->relative_pathname =
			    METHOD_NAME__INI;
			info.evaluate_info->parameters = शून्य;
			info.evaluate_info->flags = ACPI_IGNORE_RETURN_VALUE;

			status = acpi_ns_evaluate(info.evaluate_info);
			अगर (ACPI_SUCCESS(status)) अणु
				info.num_INI++;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * Run all _REG methods
	 *
	 * Note: Any objects accessed by the _REG methods will be स्वतःmatically
	 * initialized, even अगर they contain executable AML (see the call to
	 * acpi_ns_initialize_objects below).
	 *
	 * Note: According to the ACPI specअगरication, we actually needn't execute
	 * _REG क्रम प्रणाली_memory/प्रणाली_io operation regions, but क्रम PCI_Config
	 * operation regions, it is required to evaluate _REG क्रम those on a PCI
	 * root bus that करोesn't contain _BBN object. So this code is kept here
	 * in order not to अवरोध things.
	 */
	अगर (!(flags & ACPI_NO_ADDRESS_SPACE_INIT)) अणु
		ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
				  "[Init] Executing _REG OpRegion methods\n"));

		status = acpi_ev_initialize_op_regions();
		अगर (ACPI_FAILURE(status)) अणु
			जाओ error_निकास;
		पूर्ण
	पूर्ण

	अगर (!(flags & ACPI_NO_DEVICE_INIT)) अणु

		/* Walk namespace to execute all _INIs on present devices */

		status = acpi_ns_walk_namespace(ACPI_TYPE_ANY, ACPI_ROOT_OBJECT,
						ACPI_UINT32_MAX, FALSE,
						acpi_ns_init_one_device, शून्य,
						&info, शून्य);

		/*
		 * Any _OSI requests should be completed by now. If the BIOS has
		 * requested any Winकरोws OSI strings, we will always truncate
		 * I/O addresses to 16 bits -- क्रम Winकरोws compatibility.
		 */
		अगर (acpi_gbl_osi_data >= ACPI_OSI_WIN_2000) अणु
			acpi_gbl_truncate_io_addresses = TRUE;
		पूर्ण

		ACPI_FREE(info.evaluate_info);
		अगर (ACPI_FAILURE(status)) अणु
			जाओ error_निकास;
		पूर्ण

		ACPI_DEBUG_PRINT_RAW((ACPI_DB_INIT,
				      "    Executed %u _INI methods requiring %u _STA executions "
				      "(examined %u objects)\n",
				      info.num_INI, info.num_STA,
				      info.device_count));
	पूर्ण

	वापस_ACPI_STATUS(status);

error_निकास:
	ACPI_EXCEPTION((AE_INFO, status, "During device initialization"));
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_init_one_package
 *
 * PARAMETERS:  obj_handle      - Node
 *              level           - Current nesting level
 *              context         - Not used
 *              वापस_value    - Not used
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Callback from acpi_walk_namespace. Invoked क्रम every package
 *              within the namespace. Used during dynamic load of an SSDT.
 *
 ******************************************************************************/

acpi_status
acpi_ns_init_one_package(acpi_handle obj_handle,
			 u32 level, व्योम *context, व्योम **वापस_value)
अणु
	acpi_status status;
	जोड़ acpi_opeअक्रम_object *obj_desc;
	काष्ठा acpi_namespace_node *node =
	    (काष्ठा acpi_namespace_node *)obj_handle;

	obj_desc = acpi_ns_get_attached_object(node);
	अगर (!obj_desc) अणु
		वापस (AE_OK);
	पूर्ण

	/* Exit अगर package is alपढ़ोy initialized */

	अगर (obj_desc->package.flags & AOPOBJ_DATA_VALID) अणु
		वापस (AE_OK);
	पूर्ण

	status = acpi_ds_get_package_arguments(obj_desc);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (AE_OK);
	पूर्ण

	status =
	    acpi_ut_walk_package_tree(obj_desc, शून्य,
				      acpi_ds_init_package_element, शून्य);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (AE_OK);
	पूर्ण

	obj_desc->package.flags |= AOPOBJ_DATA_VALID;
	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_init_one_object
 *
 * PARAMETERS:  obj_handle      - Node
 *              level           - Current nesting level
 *              context         - Poपूर्णांकs to a init info काष्ठा
 *              वापस_value    - Not used
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Callback from acpi_walk_namespace. Invoked क्रम every object
 *              within the namespace.
 *
 *              Currently, the only objects that require initialization are:
 *              1) Methods
 *              2) Op Regions
 *
 ******************************************************************************/

अटल acpi_status
acpi_ns_init_one_object(acpi_handle obj_handle,
			u32 level, व्योम *context, व्योम **वापस_value)
अणु
	acpi_object_type type;
	acpi_status status = AE_OK;
	काष्ठा acpi_init_walk_info *info =
	    (काष्ठा acpi_init_walk_info *)context;
	काष्ठा acpi_namespace_node *node =
	    (काष्ठा acpi_namespace_node *)obj_handle;
	जोड़ acpi_opeअक्रम_object *obj_desc;

	ACPI_FUNCTION_NAME(ns_init_one_object);

	info->object_count++;

	/* And even then, we are only पूर्णांकerested in a few object types */

	type = acpi_ns_get_type(obj_handle);
	obj_desc = acpi_ns_get_attached_object(node);
	अगर (!obj_desc) अणु
		वापस (AE_OK);
	पूर्ण

	/* Increment counters क्रम object types we are looking क्रम */

	चयन (type) अणु
	हाल ACPI_TYPE_REGION:

		info->op_region_count++;
		अवरोध;

	हाल ACPI_TYPE_BUFFER_FIELD:

		info->field_count++;
		अवरोध;

	हाल ACPI_TYPE_LOCAL_BANK_FIELD:

		info->field_count++;
		अवरोध;

	हाल ACPI_TYPE_BUFFER:

		info->buffer_count++;
		अवरोध;

	हाल ACPI_TYPE_PACKAGE:

		info->package_count++;
		अवरोध;

	शेष:

		/* No init required, just निकास now */

		वापस (AE_OK);
	पूर्ण

	/* If the object is alपढ़ोy initialized, nothing अन्यथा to करो */

	अगर (obj_desc->common.flags & AOPOBJ_DATA_VALID) अणु
		वापस (AE_OK);
	पूर्ण

	/* Must lock the पूर्णांकerpreter beक्रमe executing AML code */

	acpi_ex_enter_पूर्णांकerpreter();

	/*
	 * Only initialization of Package objects can be deferred, in order
	 * to support क्रमward references.
	 */
	चयन (type) अणु
	हाल ACPI_TYPE_LOCAL_BANK_FIELD:

		/* TBD: bank_fields करो not require deferred init, हटाओ this code */

		info->field_init++;
		status = acpi_ds_get_bank_field_arguments(obj_desc);
		अवरोध;

	हाल ACPI_TYPE_PACKAGE:

		/* Complete the initialization/resolution of the package object */

		info->package_init++;
		status =
		    acpi_ns_init_one_package(obj_handle, level, शून्य, शून्य);
		अवरोध;

	शेष:

		/* No other types should get here */

		status = AE_TYPE;
		ACPI_EXCEPTION((AE_INFO, status,
				"Opcode is not deferred [%4.4s] (%s)",
				acpi_ut_get_node_name(node),
				acpi_ut_get_type_name(type)));
		अवरोध;
	पूर्ण

	अगर (ACPI_FAILURE(status)) अणु
		ACPI_EXCEPTION((AE_INFO, status,
				"Could not execute arguments for [%4.4s] (%s)",
				acpi_ut_get_node_name(node),
				acpi_ut_get_type_name(type)));
	पूर्ण

	/*
	 * We ignore errors from above, and always वापस OK, since we करोn't want
	 * to पात the walk on any single error.
	 */
	acpi_ex_निकास_पूर्णांकerpreter();
	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_find_ini_methods
 *
 * PARAMETERS:  acpi_walk_callback
 *
 * RETURN:      acpi_status
 *
 * DESCRIPTION: Called during namespace walk. Finds objects named _INI under
 *              device/processor/thermal objects, and marks the entire subtree
 *              with a SUBTREE_HAS_INI flag. This flag is used during the
 *              subsequent device initialization walk to aव्योम entire subtrees
 *              that करो not contain an _INI.
 *
 ******************************************************************************/

अटल acpi_status
acpi_ns_find_ini_methods(acpi_handle obj_handle,
			 u32 nesting_level, व्योम *context, व्योम **वापस_value)
अणु
	काष्ठा acpi_device_walk_info *info =
	    ACPI_CAST_PTR(काष्ठा acpi_device_walk_info, context);
	काष्ठा acpi_namespace_node *node;
	काष्ठा acpi_namespace_node *parent_node;

	/* Keep count of device/processor/thermal objects */

	node = ACPI_CAST_PTR(काष्ठा acpi_namespace_node, obj_handle);
	अगर ((node->type == ACPI_TYPE_DEVICE) ||
	    (node->type == ACPI_TYPE_PROCESSOR) ||
	    (node->type == ACPI_TYPE_THERMAL)) अणु
		info->device_count++;
		वापस (AE_OK);
	पूर्ण

	/* We are only looking क्रम methods named _INI */

	अगर (!ACPI_COMPARE_NAMESEG(node->name.ascii, METHOD_NAME__INI)) अणु
		वापस (AE_OK);
	पूर्ण

	/*
	 * The only _INI methods that we care about are those that are
	 * present under Device, Processor, and Thermal objects.
	 */
	parent_node = node->parent;
	चयन (parent_node->type) अणु
	हाल ACPI_TYPE_DEVICE:
	हाल ACPI_TYPE_PROCESSOR:
	हाल ACPI_TYPE_THERMAL:

		/* Mark parent and bubble up the INI present flag to the root */

		जबतक (parent_node) अणु
			parent_node->flags |= ANOBJ_SUBTREE_HAS_INI;
			parent_node = parent_node->parent;
		पूर्ण
		अवरोध;

	शेष:

		अवरोध;
	पूर्ण

	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_init_one_device
 *
 * PARAMETERS:  acpi_walk_callback
 *
 * RETURN:      acpi_status
 *
 * DESCRIPTION: This is called once per device soon after ACPI is enabled
 *              to initialize each device. It determines अगर the device is
 *              present, and अगर so, calls _INI.
 *
 ******************************************************************************/

अटल acpi_status
acpi_ns_init_one_device(acpi_handle obj_handle,
			u32 nesting_level, व्योम *context, व्योम **वापस_value)
अणु
	काष्ठा acpi_device_walk_info *walk_info =
	    ACPI_CAST_PTR(काष्ठा acpi_device_walk_info, context);
	काष्ठा acpi_evaluate_info *info = walk_info->evaluate_info;
	u32 flags;
	acpi_status status;
	काष्ठा acpi_namespace_node *device_node;

	ACPI_FUNCTION_TRACE(ns_init_one_device);

	/* We are पूर्णांकerested in Devices, Processors and thermal_zones only */

	device_node = ACPI_CAST_PTR(काष्ठा acpi_namespace_node, obj_handle);
	अगर ((device_node->type != ACPI_TYPE_DEVICE) &&
	    (device_node->type != ACPI_TYPE_PROCESSOR) &&
	    (device_node->type != ACPI_TYPE_THERMAL)) अणु
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	/*
	 * Because of an earlier namespace analysis, all subtrees that contain an
	 * _INI method are tagged.
	 *
	 * If this device subtree करोes not contain any _INI methods, we
	 * can निकास now and stop traversing this entire subtree.
	 */
	अगर (!(device_node->flags & ANOBJ_SUBTREE_HAS_INI)) अणु
		वापस_ACPI_STATUS(AE_CTRL_DEPTH);
	पूर्ण

	/*
	 * Run _STA to determine अगर this device is present and functioning. We
	 * must know this inक्रमmation क्रम two important reasons (from ACPI spec):
	 *
	 * 1) We can only run _INI अगर the device is present.
	 * 2) We must पात the device tree walk on this subtree अगर the device is
	 *    not present and is not functional (we will not examine the children)
	 *
	 * The _STA method is not required to be present under the device, we
	 * assume the device is present अगर _STA करोes not exist.
	 */
	ACPI_DEBUG_EXEC(acpi_ut_display_init_pathname
			(ACPI_TYPE_METHOD, device_node, METHOD_NAME__STA));

	status = acpi_ut_execute_STA(device_node, &flags);
	अगर (ACPI_FAILURE(status)) अणु

		/* Ignore error and move on to next device */

		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	/*
	 * Flags == -1 means that _STA was not found. In this हाल, we assume that
	 * the device is both present and functional.
	 *
	 * From the ACPI spec, description of _STA:
	 *
	 * "If a device object (including the processor object) करोes not have an
	 * _STA object, then OSPM assumes that all of the above bits are set (in
	 * other words, the device is present, ..., and functioning)"
	 */
	अगर (flags != ACPI_UINT32_MAX) अणु
		walk_info->num_STA++;
	पूर्ण

	/*
	 * Examine the PRESENT and FUNCTIONING status bits
	 *
	 * Note: ACPI spec करोes not seem to specअगरy behavior क्रम the present but
	 * not functioning हाल, so we assume functioning अगर present.
	 */
	अगर (!(flags & ACPI_STA_DEVICE_PRESENT)) अणु

		/* Device is not present, we must examine the Functioning bit */

		अगर (flags & ACPI_STA_DEVICE_FUNCTIONING) अणु
			/*
			 * Device is not present but is "functioning". In this हाल,
			 * we will not run _INI, but we जारी to examine the children
			 * of this device.
			 *
			 * From the ACPI spec, description of _STA: (note - no mention
			 * of whether to run _INI or not on the device in question)
			 *
			 * "_STA may वापस bit 0 clear (not present) with bit 3 set
			 * (device is functional). This हाल is used to indicate a valid
			 * device क्रम which no device driver should be loaded (क्रम example,
			 * a bridge device.) Children of this device may be present and
			 * valid. OSPM should जारी क्रमागतeration below a device whose
			 * _STA वापसs this bit combination"
			 */
			वापस_ACPI_STATUS(AE_OK);
		पूर्ण अन्यथा अणु
			/*
			 * Device is not present and is not functioning. We must पात the
			 * walk of this subtree immediately -- करोn't look at the children
			 * of such a device.
			 *
			 * From the ACPI spec, description of _INI:
			 *
			 * "If the _STA method indicates that the device is not present,
			 * OSPM will not run the _INI and will not examine the children
			 * of the device क्रम _INI methods"
			 */
			वापस_ACPI_STATUS(AE_CTRL_DEPTH);
		पूर्ण
	पूर्ण

	/*
	 * The device is present or is assumed present अगर no _STA exists.
	 * Run the _INI अगर it exists (not required to exist)
	 *
	 * Note: We know there is an _INI within this subtree, but it may not be
	 * under this particular device, it may be lower in the branch.
	 */
	अगर (!ACPI_COMPARE_NAMESEG(device_node->name.ascii, "_SB_") ||
	    device_node->parent != acpi_gbl_root_node) अणु
		ACPI_DEBUG_EXEC(acpi_ut_display_init_pathname
				(ACPI_TYPE_METHOD, device_node,
				 METHOD_NAME__INI));

		स_रखो(info, 0, माप(काष्ठा acpi_evaluate_info));
		info->prefix_node = device_node;
		info->relative_pathname = METHOD_NAME__INI;
		info->parameters = शून्य;
		info->flags = ACPI_IGNORE_RETURN_VALUE;

		status = acpi_ns_evaluate(info);
		अगर (ACPI_SUCCESS(status)) अणु
			walk_info->num_INI++;
		पूर्ण
#अगर_घोषित ACPI_DEBUG_OUTPUT
		अन्यथा अगर (status != AE_NOT_FOUND) अणु

			/* Ignore error and move on to next device */

			अक्षर *scope_name =
			    acpi_ns_get_normalized_pathname(device_node, TRUE);

			ACPI_EXCEPTION((AE_INFO, status,
					"during %s._INI execution",
					scope_name));
			ACPI_FREE(scope_name);
		पूर्ण
#पूर्ण_अगर
	पूर्ण

	/* Ignore errors from above */

	status = AE_OK;

	/*
	 * The _INI method has been run अगर present; call the Global Initialization
	 * Handler क्रम this device.
	 */
	अगर (acpi_gbl_init_handler) अणु
		status =
		    acpi_gbl_init_handler(device_node, ACPI_INIT_DEVICE_INI);
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण
