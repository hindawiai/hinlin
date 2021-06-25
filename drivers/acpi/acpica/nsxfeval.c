<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/*******************************************************************************
 *
 * Module Name: nsxfeval - Public पूर्णांकerfaces to the ACPI subप्रणाली
 *                         ACPI Object evaluation पूर्णांकerfaces
 *
 ******************************************************************************/

#घोषणा EXPORT_ACPI_INTERFACES

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acnamesp.h"
#समावेश "acinterp.h"

#घोषणा _COMPONENT          ACPI_NAMESPACE
ACPI_MODULE_NAME("nsxfeval")

/* Local prototypes */
अटल व्योम acpi_ns_resolve_references(काष्ठा acpi_evaluate_info *info);

/*******************************************************************************
 *
 * FUNCTION:    acpi_evaluate_object_typed
 *
 * PARAMETERS:  handle              - Object handle (optional)
 *              pathname            - Object pathname (optional)
 *              बाह्यal_params     - List of parameters to pass to a method,
 *                                    terminated by शून्य. May be शून्य
 *                                    अगर no parameters are being passed.
 *              वापस_buffer       - Where to put the object's वापस value (अगर
 *                                    any). If शून्य, no value is वापसed.
 *              वापस_type         - Expected type of वापस object
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Find and evaluate the given object, passing the given
 *              parameters अगर necessary. One of "Handle" or "Pathname" must
 *              be valid (non-null)
 *
 ******************************************************************************/

acpi_status
acpi_evaluate_object_typed(acpi_handle handle,
			   acpi_string pathname,
			   काष्ठा acpi_object_list *बाह्यal_params,
			   काष्ठा acpi_buffer *वापस_buffer,
			   acpi_object_type वापस_type)
अणु
	acpi_status status;
	u8 मुक्त_buffer_on_error = FALSE;
	acpi_handle target_handle;
	अक्षर *full_pathname;

	ACPI_FUNCTION_TRACE(acpi_evaluate_object_typed);

	/* Return buffer must be valid */

	अगर (!वापस_buffer) अणु
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	अगर (वापस_buffer->length == ACPI_ALLOCATE_BUFFER) अणु
		मुक्त_buffer_on_error = TRUE;
	पूर्ण

	/* Get a handle here, in order to build an error message अगर needed */

	target_handle = handle;
	अगर (pathname) अणु
		status = acpi_get_handle(handle, pathname, &target_handle);
		अगर (ACPI_FAILURE(status)) अणु
			वापस_ACPI_STATUS(status);
		पूर्ण
	पूर्ण

	full_pathname = acpi_ns_get_बाह्यal_pathname(target_handle);
	अगर (!full_pathname) अणु
		वापस_ACPI_STATUS(AE_NO_MEMORY);
	पूर्ण

	/* Evaluate the object */

	status = acpi_evaluate_object(target_handle, शून्य, बाह्यal_params,
				      वापस_buffer);
	अगर (ACPI_FAILURE(status)) अणु
		जाओ निकास;
	पूर्ण

	/* Type ANY means "don't care about return value type" */

	अगर (वापस_type == ACPI_TYPE_ANY) अणु
		जाओ निकास;
	पूर्ण

	अगर (वापस_buffer->length == 0) अणु

		/* Error because caller specअगरically asked क्रम a वापस value */

		ACPI_ERROR((AE_INFO, "%s did not return any object",
			    full_pathname));
		status = AE_शून्य_OBJECT;
		जाओ निकास;
	पूर्ण

	/* Examine the object type वापसed from evaluate_object */

	अगर (((जोड़ acpi_object *)वापस_buffer->poपूर्णांकer)->type == वापस_type) अणु
		जाओ निकास;
	पूर्ण

	/* Return object type करोes not match requested type */

	ACPI_ERROR((AE_INFO,
		    "Incorrect return type from %s - received [%s], requested [%s]",
		    full_pathname,
		    acpi_ut_get_type_name(((जोड़ acpi_object *)वापस_buffer->
					   poपूर्णांकer)->type),
		    acpi_ut_get_type_name(वापस_type)));

	अगर (मुक्त_buffer_on_error) अणु
		/*
		 * Free a buffer created via ACPI_ALLOCATE_BUFFER.
		 * Note: We use acpi_os_मुक्त here because acpi_os_allocate was used
		 * to allocate the buffer. This purposefully bypasses the
		 * (optionally enabled) allocation tracking mechanism since we
		 * only want to track पूर्णांकernal allocations.
		 */
		acpi_os_मुक्त(वापस_buffer->poपूर्णांकer);
		वापस_buffer->poपूर्णांकer = शून्य;
	पूर्ण

	वापस_buffer->length = 0;
	status = AE_TYPE;

निकास:
	ACPI_FREE(full_pathname);
	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_evaluate_object_typed)

/*******************************************************************************
 *
 * FUNCTION:    acpi_evaluate_object
 *
 * PARAMETERS:  handle              - Object handle (optional)
 *              pathname            - Object pathname (optional)
 *              बाह्यal_params     - List of parameters to pass to method,
 *                                    terminated by शून्य. May be शून्य
 *                                    अगर no parameters are being passed.
 *              वापस_buffer       - Where to put method's वापस value (अगर
 *                                    any). If शून्य, no value is वापसed.
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Find and evaluate the given object, passing the given
 *              parameters अगर necessary. One of "Handle" or "Pathname" must
 *              be valid (non-null)
 *
 ******************************************************************************/
acpi_status
acpi_evaluate_object(acpi_handle handle,
		     acpi_string pathname,
		     काष्ठा acpi_object_list *बाह्यal_params,
		     काष्ठा acpi_buffer *वापस_buffer)
अणु
	acpi_status status;
	काष्ठा acpi_evaluate_info *info;
	acpi_size buffer_space_needed;
	u32 i;

	ACPI_FUNCTION_TRACE(acpi_evaluate_object);

	/* Allocate and initialize the evaluation inक्रमmation block */

	info = ACPI_ALLOCATE_ZEROED(माप(काष्ठा acpi_evaluate_info));
	अगर (!info) अणु
		वापस_ACPI_STATUS(AE_NO_MEMORY);
	पूर्ण

	/* Convert and validate the device handle */

	info->prefix_node = acpi_ns_validate_handle(handle);
	अगर (!info->prefix_node) अणु
		status = AE_BAD_PARAMETER;
		जाओ cleanup;
	पूर्ण

	/*
	 * Get the actual namespace node क्रम the target object.
	 * Handles these हालs:
	 *
	 * 1) Null node, valid pathname from root (असलolute path)
	 * 2) Node and valid pathname (path relative to Node)
	 * 3) Node, Null pathname
	 */
	अगर ((pathname) && (ACPI_IS_ROOT_PREFIX(pathname[0]))) अणु

		/* The path is fully qualअगरied, just evaluate by name */

		info->prefix_node = शून्य;
	पूर्ण अन्यथा अगर (!handle) अणु
		/*
		 * A handle is optional अगरf a fully qualअगरied pathname is specअगरied.
		 * Since we've alपढ़ोy handled fully qualअगरied names above, this is
		 * an error.
		 */
		अगर (!pathname) अणु
			ACPI_DEBUG_PRINT((ACPI_DB_INFO,
					  "Both Handle and Pathname are NULL"));
		पूर्ण अन्यथा अणु
			ACPI_DEBUG_PRINT((ACPI_DB_INFO,
					  "Null Handle with relative pathname [%s]",
					  pathname));
		पूर्ण

		status = AE_BAD_PARAMETER;
		जाओ cleanup;
	पूर्ण

	info->relative_pathname = pathname;

	/*
	 * Convert all बाह्यal objects passed as arguments to the
	 * पूर्णांकernal version(s).
	 */
	अगर (बाह्यal_params && बाह्यal_params->count) अणु
		info->param_count = (u16)बाह्यal_params->count;

		/* Warn on impossible argument count */

		अगर (info->param_count > ACPI_METHOD_NUM_ARGS) अणु
			ACPI_WARN_PREDEFINED((AE_INFO, pathname,
					      ACPI_WARN_ALWAYS,
					      "Excess arguments (%u) - using only %u",
					      info->param_count,
					      ACPI_METHOD_NUM_ARGS));

			info->param_count = ACPI_METHOD_NUM_ARGS;
		पूर्ण

		/*
		 * Allocate a new parameter block क्रम the पूर्णांकernal objects
		 * Add 1 to count to allow क्रम null terminated पूर्णांकernal list
		 */
		info->parameters = ACPI_ALLOCATE_ZEROED(((acpi_size)info->
							 param_count +
							 1) * माप(व्योम *));
		अगर (!info->parameters) अणु
			status = AE_NO_MEMORY;
			जाओ cleanup;
		पूर्ण

		/* Convert each बाह्यal object in the list to an पूर्णांकernal object */

		क्रम (i = 0; i < info->param_count; i++) अणु
			status =
			    acpi_ut_copy_eobject_to_iobject(&बाह्यal_params->
							    poपूर्णांकer[i],
							    &info->
							    parameters[i]);
			अगर (ACPI_FAILURE(status)) अणु
				जाओ cleanup;
			पूर्ण
		पूर्ण

		info->parameters[info->param_count] = शून्य;
	पूर्ण

#अगर_घोषित _FUTURE_FEATURE

	/*
	 * Begin incoming argument count analysis. Check क्रम too few args
	 * and too many args.
	 */
	चयन (acpi_ns_get_type(info->node)) अणु
	हाल ACPI_TYPE_METHOD:

		/* Check incoming argument count against the method definition */

		अगर (info->obj_desc->method.param_count > info->param_count) अणु
			ACPI_ERROR((AE_INFO,
				    "Insufficient arguments (%u) - %u are required",
				    info->param_count,
				    info->obj_desc->method.param_count));

			status = AE_MISSING_ARGUMENTS;
			जाओ cleanup;
		पूर्ण

		अन्यथा अगर (info->obj_desc->method.param_count < info->param_count) अणु
			ACPI_WARNING((AE_INFO,
				      "Excess arguments (%u) - only %u are required",
				      info->param_count,
				      info->obj_desc->method.param_count));

			/* Just pass the required number of arguments */

			info->param_count = info->obj_desc->method.param_count;
		पूर्ण

		/*
		 * Any incoming बाह्यal objects to be passed as arguments to the
		 * method must be converted to पूर्णांकernal objects
		 */
		अगर (info->param_count) अणु
			/*
			 * Allocate a new parameter block क्रम the पूर्णांकernal objects
			 * Add 1 to count to allow क्रम null terminated पूर्णांकernal list
			 */
			info->parameters = ACPI_ALLOCATE_ZEROED(((acpi_size)
								 info->
								 param_count +
								 1) *
								माप(व्योम *));
			अगर (!info->parameters) अणु
				status = AE_NO_MEMORY;
				जाओ cleanup;
			पूर्ण

			/* Convert each बाह्यal object in the list to an पूर्णांकernal object */

			क्रम (i = 0; i < info->param_count; i++) अणु
				status =
				    acpi_ut_copy_eobject_to_iobject
				    (&बाह्यal_params->poपूर्णांकer[i],
				     &info->parameters[i]);
				अगर (ACPI_FAILURE(status)) अणु
					जाओ cleanup;
				पूर्ण
			पूर्ण

			info->parameters[info->param_count] = शून्य;
		पूर्ण
		अवरोध;

	शेष:

		/* Warn अगर arguments passed to an object that is not a method */

		अगर (info->param_count) अणु
			ACPI_WARNING((AE_INFO,
				      "%u arguments were passed to a non-method ACPI object",
				      info->param_count));
		पूर्ण
		अवरोध;
	पूर्ण

#पूर्ण_अगर

	/* Now we can evaluate the object */

	status = acpi_ns_evaluate(info);

	/*
	 * If we are expecting a वापस value, and all went well above,
	 * copy the वापस value to an बाह्यal object.
	 */
	अगर (!वापस_buffer) अणु
		जाओ cleanup_वापस_object;
	पूर्ण

	अगर (!info->वापस_object) अणु
		वापस_buffer->length = 0;
		जाओ cleanup;
	पूर्ण

	अगर (ACPI_GET_DESCRIPTOR_TYPE(info->वापस_object) ==
	    ACPI_DESC_TYPE_NAMED) अणु
		/*
		 * If we received a NS Node as a वापस object, this means that
		 * the object we are evaluating has nothing पूर्णांकeresting to
		 * वापस (such as a mutex, etc.)  We वापस an error because
		 * these types are essentially unsupported by this पूर्णांकerface.
		 * We करोn't check up front because this makes it easier to add
		 * support क्रम various types at a later date अगर necessary.
		 */
		status = AE_TYPE;
		info->वापस_object = शून्य;	/* No need to delete a NS Node */
		वापस_buffer->length = 0;
	पूर्ण

	अगर (ACPI_FAILURE(status)) अणु
		जाओ cleanup_वापस_object;
	पूर्ण

	/* Dereference Index and ref_of references */

	acpi_ns_resolve_references(info);

	/* Get the size of the वापसed object */

	status = acpi_ut_get_object_size(info->वापस_object,
					 &buffer_space_needed);
	अगर (ACPI_SUCCESS(status)) अणु

		/* Validate/Allocate/Clear caller buffer */

		status = acpi_ut_initialize_buffer(वापस_buffer,
						   buffer_space_needed);
		अगर (ACPI_FAILURE(status)) अणु
			/*
			 * Caller's buffer is too small or a new one can't
			 * be allocated
			 */
			ACPI_DEBUG_PRINT((ACPI_DB_INFO,
					  "Needed buffer size %X, %s\n",
					  (u32)buffer_space_needed,
					  acpi_क्रमmat_exception(status)));
		पूर्ण अन्यथा अणु
			/* We have enough space क्रम the object, build it */

			status =
			    acpi_ut_copy_iobject_to_eobject(info->वापस_object,
							    वापस_buffer);
		पूर्ण
	पूर्ण

cleanup_वापस_object:

	अगर (info->वापस_object) अणु
		/*
		 * Delete the पूर्णांकernal वापस object. NOTE: Interpreter must be
		 * locked to aव्योम race condition.
		 */
		acpi_ex_enter_पूर्णांकerpreter();

		/* Remove one reference on the वापस object (should delete it) */

		acpi_ut_हटाओ_reference(info->वापस_object);
		acpi_ex_निकास_पूर्णांकerpreter();
	पूर्ण

cleanup:

	/* Free the input parameter list (अगर we created one) */

	अगर (info->parameters) अणु

		/* Free the allocated parameter block */

		acpi_ut_delete_पूर्णांकernal_object_list(info->parameters);
	पूर्ण

	ACPI_FREE(info);
	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_evaluate_object)

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_resolve_references
 *
 * PARAMETERS:  info                    - Evaluation info block
 *
 * RETURN:      Info->वापस_object is replaced with the dereferenced object
 *
 * DESCRIPTION: Dereference certain reference objects. Called beक्रमe an
 *              पूर्णांकernal वापस object is converted to an बाह्यal जोड़ acpi_object.
 *
 * Perक्रमms an स्वतःmatic dereference of Index and ref_of reference objects.
 * These reference objects are not supported by the जोड़ acpi_object, so this is a
 * last resort efक्रमt to वापस something useful. Also, provides compatibility
 * with other ACPI implementations.
 *
 * NOTE: करोes not handle references within वापसed package objects or nested
 * references, but this support could be added later अगर found to be necessary.
 *
 ******************************************************************************/
अटल व्योम acpi_ns_resolve_references(काष्ठा acpi_evaluate_info *info)
अणु
	जोड़ acpi_opeअक्रम_object *obj_desc = शून्य;
	काष्ठा acpi_namespace_node *node;

	/* We are पूर्णांकerested in reference objects only */

	अगर ((info->वापस_object)->common.type != ACPI_TYPE_LOCAL_REFERENCE) अणु
		वापस;
	पूर्ण

	/*
	 * Two types of references are supported - those created by Index and
	 * ref_of चालकs. A name reference (AML_NAMEPATH_OP) can be converted
	 * to a जोड़ acpi_object, so it is not dereferenced here. A ddb_handle
	 * (AML_LOAD_OP) cannot be dereferenced, nor can it be converted to
	 * a जोड़ acpi_object.
	 */
	चयन (info->वापस_object->reference.class) अणु
	हाल ACPI_REFCLASS_INDEX:

		obj_desc = *(info->वापस_object->reference.where);
		अवरोध;

	हाल ACPI_REFCLASS_REFOF:

		node = info->वापस_object->reference.object;
		अगर (node) अणु
			obj_desc = node->object;
		पूर्ण
		अवरोध;

	शेष:

		वापस;
	पूर्ण

	/* Replace the existing reference object */

	अगर (obj_desc) अणु
		acpi_ut_add_reference(obj_desc);
		acpi_ut_हटाओ_reference(info->वापस_object);
		info->वापस_object = obj_desc;
	पूर्ण

	वापस;
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_walk_namespace
 *
 * PARAMETERS:  type                - acpi_object_type to search क्रम
 *              start_object        - Handle in namespace where search begins
 *              max_depth           - Depth to which search is to reach
 *              descending_callback - Called during tree descent
 *                                    when an object of "Type" is found
 *              ascending_callback  - Called during tree ascent
 *                                    when an object of "Type" is found
 *              context             - Passed to user function(s) above
 *              वापस_value        - Location where वापस value of
 *                                    user_function is put अगर terminated early
 *
 * RETURNS      Return value from the user_function अगर terminated early.
 *              Otherwise, वापसs शून्य.
 *
 * DESCRIPTION: Perक्रमms a modअगरied depth-first walk of the namespace tree,
 *              starting (and ending) at the object specअगरied by start_handle.
 *              The callback function is called whenever an object that matches
 *              the type parameter is found. If the callback function वापसs
 *              a non-zero value, the search is terminated immediately and this
 *              value is वापसed to the caller.
 *
 *              The poपूर्णांक of this procedure is to provide a generic namespace
 *              walk routine that can be called from multiple places to
 *              provide multiple services; the callback function(s) can be
 *              tailored to each task, whether it is a prपूर्णांक function,
 *              a compare function, etc.
 *
 ******************************************************************************/

acpi_status
acpi_walk_namespace(acpi_object_type type,
		    acpi_handle start_object,
		    u32 max_depth,
		    acpi_walk_callback descending_callback,
		    acpi_walk_callback ascending_callback,
		    व्योम *context, व्योम **वापस_value)
अणु
	acpi_status status;

	ACPI_FUNCTION_TRACE(acpi_walk_namespace);

	/* Parameter validation */

	अगर ((type > ACPI_TYPE_LOCAL_MAX) ||
	    (!max_depth) || (!descending_callback && !ascending_callback)) अणु
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	/*
	 * Need to acquire the namespace पढ़ोer lock to prevent पूर्णांकerference
	 * with any concurrent table unloads (which causes the deletion of
	 * namespace objects). We cannot allow the deletion of a namespace node
	 * जबतक the user function is using it. The exception to this are the
	 * nodes created and deleted during control method execution -- these
	 * nodes are marked as temporary nodes and are ignored by the namespace
	 * walk. Thus, control methods can be executed जबतक holding the
	 * namespace deletion lock (and the user function can execute control
	 * methods.)
	 */
	status = acpi_ut_acquire_पढ़ो_lock(&acpi_gbl_namespace_rw_lock);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/*
	 * Lock the namespace around the walk. The namespace will be
	 * unlocked/locked around each call to the user function - since the user
	 * function must be allowed to make ACPICA calls itself (क्रम example, it
	 * will typically execute control methods during device क्रमागतeration.)
	 */
	status = acpi_ut_acquire_mutex(ACPI_MTX_NAMESPACE);
	अगर (ACPI_FAILURE(status)) अणु
		जाओ unlock_and_निकास;
	पूर्ण

	/* Now we can validate the starting node */

	अगर (!acpi_ns_validate_handle(start_object)) अणु
		status = AE_BAD_PARAMETER;
		जाओ unlock_and_निकास2;
	पूर्ण

	status = acpi_ns_walk_namespace(type, start_object, max_depth,
					ACPI_NS_WALK_UNLOCK,
					descending_callback, ascending_callback,
					context, वापस_value);

unlock_and_निकास2:
	(व्योम)acpi_ut_release_mutex(ACPI_MTX_NAMESPACE);

unlock_and_निकास:
	(व्योम)acpi_ut_release_पढ़ो_lock(&acpi_gbl_namespace_rw_lock);
	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_walk_namespace)

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_get_device_callback
 *
 * PARAMETERS:  Callback from acpi_get_device
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Takes callbacks from walk_namespace and filters out all non-
 *              present devices, or अगर they specअगरied a HID, it filters based
 *              on that.
 *
 ******************************************************************************/
अटल acpi_status
acpi_ns_get_device_callback(acpi_handle obj_handle,
			    u32 nesting_level,
			    व्योम *context, व्योम **वापस_value)
अणु
	काष्ठा acpi_get_devices_info *info = context;
	acpi_status status;
	काष्ठा acpi_namespace_node *node;
	u32 flags;
	काष्ठा acpi_pnp_device_id *hid;
	काष्ठा acpi_pnp_device_id_list *cid;
	u32 i;
	u8 found;
	पूर्णांक no_match;

	status = acpi_ut_acquire_mutex(ACPI_MTX_NAMESPACE);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	node = acpi_ns_validate_handle(obj_handle);
	status = acpi_ut_release_mutex(ACPI_MTX_NAMESPACE);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	अगर (!node) अणु
		वापस (AE_BAD_PARAMETER);
	पूर्ण

	/*
	 * First, filter based on the device HID and CID.
	 *
	 * 01/2010: For this हाल where a specअगरic HID is requested, we करोn't
	 * want to run _STA until we have an actual HID match. Thus, we will
	 * not unnecessarily execute _STA on devices क्रम which the caller
	 * करोesn't care about. Previously, _STA was executed unconditionally
	 * on all devices found here.
	 *
	 * A side-effect of this change is that now we will जारी to search
	 * क्रम a matching HID even under device trees where the parent device
	 * would have वापसed a _STA that indicates it is not present or
	 * not functioning (thus पातing the search on that branch).
	 */
	अगर (info->hid != शून्य) अणु
		status = acpi_ut_execute_HID(node, &hid);
		अगर (status == AE_NOT_FOUND) अणु
			वापस (AE_OK);
		पूर्ण अन्यथा अगर (ACPI_FAILURE(status)) अणु
			वापस (AE_CTRL_DEPTH);
		पूर्ण

		no_match = म_भेद(hid->string, info->hid);
		ACPI_FREE(hid);

		अगर (no_match) अणु
			/*
			 * HID करोes not match, attempt match within the
			 * list of Compatible IDs (CIDs)
			 */
			status = acpi_ut_execute_CID(node, &cid);
			अगर (status == AE_NOT_FOUND) अणु
				वापस (AE_OK);
			पूर्ण अन्यथा अगर (ACPI_FAILURE(status)) अणु
				वापस (AE_CTRL_DEPTH);
			पूर्ण

			/* Walk the CID list */

			found = FALSE;
			क्रम (i = 0; i < cid->count; i++) अणु
				अगर (म_भेद(cid->ids[i].string, info->hid) == 0) अणु

					/* Found a matching CID */

					found = TRUE;
					अवरोध;
				पूर्ण
			पूर्ण

			ACPI_FREE(cid);
			अगर (!found) अणु
				वापस (AE_OK);
			पूर्ण
		पूर्ण
	पूर्ण

	/* Run _STA to determine अगर device is present */

	status = acpi_ut_execute_STA(node, &flags);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (AE_CTRL_DEPTH);
	पूर्ण

	अगर (!(flags & ACPI_STA_DEVICE_PRESENT) &&
	    !(flags & ACPI_STA_DEVICE_FUNCTIONING)) अणु
		/*
		 * Don't examine the children of the device only when the
		 * device is neither present nor functional. See ACPI spec,
		 * description of _STA क्रम more inक्रमmation.
		 */
		वापस (AE_CTRL_DEPTH);
	पूर्ण

	/* We have a valid device, invoke the user function */

	status = info->user_function(obj_handle, nesting_level,
				     info->context, वापस_value);
	वापस (status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_get_devices
 *
 * PARAMETERS:  HID                 - HID to search क्रम. Can be शून्य.
 *              user_function       - Called when a matching object is found
 *              context             - Passed to user function
 *              वापस_value        - Location where वापस value of
 *                                    user_function is put अगर terminated early
 *
 * RETURNS      Return value from the user_function अगर terminated early.
 *              Otherwise, वापसs शून्य.
 *
 * DESCRIPTION: Perक्रमms a modअगरied depth-first walk of the namespace tree,
 *              starting (and ending) at the object specअगरied by start_handle.
 *              The user_function is called whenever an object of type
 *              Device is found. If the user function वापसs
 *              a non-zero value, the search is terminated immediately and this
 *              value is वापसed to the caller.
 *
 *              This is a wrapper क्रम walk_namespace, but the callback perक्रमms
 *              additional filtering. Please see acpi_ns_get_device_callback.
 *
 ******************************************************************************/

acpi_status
acpi_get_devices(स्थिर अक्षर *HID,
		 acpi_walk_callback user_function,
		 व्योम *context, व्योम **वापस_value)
अणु
	acpi_status status;
	काष्ठा acpi_get_devices_info info;

	ACPI_FUNCTION_TRACE(acpi_get_devices);

	/* Parameter validation */

	अगर (!user_function) अणु
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	/*
	 * We're going to call their callback from OUR callback, so we need
	 * to know what it is, and their context parameter.
	 */
	info.hid = HID;
	info.context = context;
	info.user_function = user_function;

	/*
	 * Lock the namespace around the walk.
	 * The namespace will be unlocked/locked around each call
	 * to the user function - since this function
	 * must be allowed to make Acpi calls itself.
	 */
	status = acpi_ut_acquire_mutex(ACPI_MTX_NAMESPACE);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	status = acpi_ns_walk_namespace(ACPI_TYPE_DEVICE, ACPI_ROOT_OBJECT,
					ACPI_UINT32_MAX, ACPI_NS_WALK_UNLOCK,
					acpi_ns_get_device_callback, शून्य,
					&info, वापस_value);

	(व्योम)acpi_ut_release_mutex(ACPI_MTX_NAMESPACE);
	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_get_devices)

/*******************************************************************************
 *
 * FUNCTION:    acpi_attach_data
 *
 * PARAMETERS:  obj_handle          - Namespace node
 *              handler             - Handler क्रम this attachment
 *              data                - Poपूर्णांकer to data to be attached
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Attach arbitrary data and handler to a namespace node.
 *
 ******************************************************************************/
acpi_status
acpi_attach_data(acpi_handle obj_handle,
		 acpi_object_handler handler, व्योम *data)
अणु
	काष्ठा acpi_namespace_node *node;
	acpi_status status;

	/* Parameter validation */

	अगर (!obj_handle || !handler || !data) अणु
		वापस (AE_BAD_PARAMETER);
	पूर्ण

	status = acpi_ut_acquire_mutex(ACPI_MTX_NAMESPACE);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	/* Convert and validate the handle */

	node = acpi_ns_validate_handle(obj_handle);
	अगर (!node) अणु
		status = AE_BAD_PARAMETER;
		जाओ unlock_and_निकास;
	पूर्ण

	status = acpi_ns_attach_data(node, handler, data);

unlock_and_निकास:
	(व्योम)acpi_ut_release_mutex(ACPI_MTX_NAMESPACE);
	वापस (status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_attach_data)

/*******************************************************************************
 *
 * FUNCTION:    acpi_detach_data
 *
 * PARAMETERS:  obj_handle          - Namespace node handle
 *              handler             - Handler used in call to acpi_attach_data
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Remove data that was previously attached to a node.
 *
 ******************************************************************************/
acpi_status
acpi_detach_data(acpi_handle obj_handle, acpi_object_handler handler)
अणु
	काष्ठा acpi_namespace_node *node;
	acpi_status status;

	/* Parameter validation */

	अगर (!obj_handle || !handler) अणु
		वापस (AE_BAD_PARAMETER);
	पूर्ण

	status = acpi_ut_acquire_mutex(ACPI_MTX_NAMESPACE);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	/* Convert and validate the handle */

	node = acpi_ns_validate_handle(obj_handle);
	अगर (!node) अणु
		status = AE_BAD_PARAMETER;
		जाओ unlock_and_निकास;
	पूर्ण

	status = acpi_ns_detach_data(node, handler);

unlock_and_निकास:
	(व्योम)acpi_ut_release_mutex(ACPI_MTX_NAMESPACE);
	वापस (status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_detach_data)

/*******************************************************************************
 *
 * FUNCTION:    acpi_get_data_full
 *
 * PARAMETERS:  obj_handle          - Namespace node
 *              handler             - Handler used in call to attach_data
 *              data                - Where the data is वापसed
 *              callback            - function to execute beक्रमe वापसing
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Retrieve data that was previously attached to a namespace node
 *              and execute a callback beक्रमe वापसing.
 *
 ******************************************************************************/
acpi_status
acpi_get_data_full(acpi_handle obj_handle, acpi_object_handler handler,
		   व्योम **data, व्योम (*callback)(व्योम *))
अणु
	काष्ठा acpi_namespace_node *node;
	acpi_status status;

	/* Parameter validation */

	अगर (!obj_handle || !handler || !data) अणु
		वापस (AE_BAD_PARAMETER);
	पूर्ण

	status = acpi_ut_acquire_mutex(ACPI_MTX_NAMESPACE);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	/* Convert and validate the handle */

	node = acpi_ns_validate_handle(obj_handle);
	अगर (!node) अणु
		status = AE_BAD_PARAMETER;
		जाओ unlock_and_निकास;
	पूर्ण

	status = acpi_ns_get_attached_data(node, handler, data);
	अगर (ACPI_SUCCESS(status) && callback) अणु
		callback(*data);
	पूर्ण

unlock_and_निकास:
	(व्योम)acpi_ut_release_mutex(ACPI_MTX_NAMESPACE);
	वापस (status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_get_data_full)

/*******************************************************************************
 *
 * FUNCTION:    acpi_get_data
 *
 * PARAMETERS:  obj_handle          - Namespace node
 *              handler             - Handler used in call to attach_data
 *              data                - Where the data is वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Retrieve data that was previously attached to a namespace node.
 *
 ******************************************************************************/
acpi_status
acpi_get_data(acpi_handle obj_handle, acpi_object_handler handler, व्योम **data)
अणु
	वापस acpi_get_data_full(obj_handle, handler, data, शून्य);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_get_data)
