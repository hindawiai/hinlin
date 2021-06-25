<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/*******************************************************************************
 *
 * Module Name: utdelete - object deletion and reference count utilities
 *
 ******************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acinterp.h"
#समावेश "acnamesp.h"
#समावेश "acevents.h"

#घोषणा _COMPONENT          ACPI_UTILITIES
ACPI_MODULE_NAME("utdelete")

/* Local prototypes */
अटल व्योम acpi_ut_delete_पूर्णांकernal_obj(जोड़ acpi_opeअक्रम_object *object);

अटल व्योम
acpi_ut_update_ref_count(जोड़ acpi_opeअक्रम_object *object, u32 action);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_delete_पूर्णांकernal_obj
 *
 * PARAMETERS:  object         - Object to be deleted
 *
 * RETURN:      None
 *
 * DESCRIPTION: Low level object deletion, after reference counts have been
 *              updated (All reference counts, including sub-objects!)
 *
 ******************************************************************************/

अटल व्योम acpi_ut_delete_पूर्णांकernal_obj(जोड़ acpi_opeअक्रम_object *object)
अणु
	व्योम *obj_poपूर्णांकer = शून्य;
	जोड़ acpi_opeअक्रम_object *handler_desc;
	जोड़ acpi_opeअक्रम_object *second_desc;
	जोड़ acpi_opeअक्रम_object *next_desc;
	जोड़ acpi_opeअक्रम_object *start_desc;
	जोड़ acpi_opeअक्रम_object **last_obj_ptr;

	ACPI_FUNCTION_TRACE_PTR(ut_delete_पूर्णांकernal_obj, object);

	अगर (!object) अणु
		वापस_VOID;
	पूर्ण

	/*
	 * Must delete or मुक्त any poपूर्णांकers within the object that are not
	 * actual ACPI objects (क्रम example, a raw buffer poपूर्णांकer).
	 */
	चयन (object->common.type) अणु
	हाल ACPI_TYPE_STRING:

		ACPI_DEBUG_PRINT((ACPI_DB_ALLOCATIONS,
				  "**** String %p, ptr %p\n", object,
				  object->string.poपूर्णांकer));

		/* Free the actual string buffer */

		अगर (!(object->common.flags & AOPOBJ_STATIC_POINTER)) अणु

			/* But only अगर it is NOT a poपूर्णांकer पूर्णांकo an ACPI table */

			obj_poपूर्णांकer = object->string.poपूर्णांकer;
		पूर्ण
		अवरोध;

	हाल ACPI_TYPE_BUFFER:

		ACPI_DEBUG_PRINT((ACPI_DB_ALLOCATIONS,
				  "**** Buffer %p, ptr %p\n", object,
				  object->buffer.poपूर्णांकer));

		/* Free the actual buffer */

		अगर (!(object->common.flags & AOPOBJ_STATIC_POINTER)) अणु

			/* But only अगर it is NOT a poपूर्णांकer पूर्णांकo an ACPI table */

			obj_poपूर्णांकer = object->buffer.poपूर्णांकer;
		पूर्ण
		अवरोध;

	हाल ACPI_TYPE_PACKAGE:

		ACPI_DEBUG_PRINT((ACPI_DB_ALLOCATIONS,
				  " **** Package of count %X\n",
				  object->package.count));

		/*
		 * Elements of the package are not handled here, they are deleted
		 * separately
		 */

		/* Free the (variable length) element poपूर्णांकer array */

		obj_poपूर्णांकer = object->package.elements;
		अवरोध;

		/*
		 * These objects have a possible list of notअगरy handlers.
		 * Device object also may have a GPE block.
		 */
	हाल ACPI_TYPE_DEVICE:

		अगर (object->device.gpe_block) अणु
			(व्योम)acpi_ev_delete_gpe_block(object->device.
						       gpe_block);
		पूर्ण

		ACPI_FALLTHROUGH;

	हाल ACPI_TYPE_PROCESSOR:
	हाल ACPI_TYPE_THERMAL:

		/* Walk the address handler list क्रम this object */

		handler_desc = object->common_notअगरy.handler;
		जबतक (handler_desc) अणु
			next_desc = handler_desc->address_space.next;
			acpi_ut_हटाओ_reference(handler_desc);
			handler_desc = next_desc;
		पूर्ण
		अवरोध;

	हाल ACPI_TYPE_MUTEX:

		ACPI_DEBUG_PRINT((ACPI_DB_ALLOCATIONS,
				  "***** Mutex %p, OS Mutex %p\n",
				  object, object->mutex.os_mutex));

		अगर (object == acpi_gbl_global_lock_mutex) अणु

			/* Global Lock has extra semaphore */

			(व्योम)
			    acpi_os_delete_semaphore
			    (acpi_gbl_global_lock_semaphore);
			acpi_gbl_global_lock_semaphore = शून्य;

			acpi_os_delete_mutex(object->mutex.os_mutex);
			acpi_gbl_global_lock_mutex = शून्य;
		पूर्ण अन्यथा अणु
			acpi_ex_unlink_mutex(object);
			acpi_os_delete_mutex(object->mutex.os_mutex);
		पूर्ण
		अवरोध;

	हाल ACPI_TYPE_EVENT:

		ACPI_DEBUG_PRINT((ACPI_DB_ALLOCATIONS,
				  "***** Event %p, OS Semaphore %p\n",
				  object, object->event.os_semaphore));

		(व्योम)acpi_os_delete_semaphore(object->event.os_semaphore);
		object->event.os_semaphore = शून्य;
		अवरोध;

	हाल ACPI_TYPE_METHOD:

		ACPI_DEBUG_PRINT((ACPI_DB_ALLOCATIONS,
				  "***** Method %p\n", object));

		/* Delete the method mutex अगर it exists */

		अगर (object->method.mutex) अणु
			acpi_os_delete_mutex(object->method.mutex->mutex.
					     os_mutex);
			acpi_ut_delete_object_desc(object->method.mutex);
			object->method.mutex = शून्य;
		पूर्ण

		अगर (object->method.node) अणु
			object->method.node = शून्य;
		पूर्ण
		अवरोध;

	हाल ACPI_TYPE_REGION:

		ACPI_DEBUG_PRINT((ACPI_DB_ALLOCATIONS,
				  "***** Region %p\n", object));

		/*
		 * Update address_range list. However, only permanent regions
		 * are installed in this list. (Not created within a method)
		 */
		अगर (!(object->region.node->flags & ANOBJ_TEMPORARY)) अणु
			acpi_ut_हटाओ_address_range(object->region.space_id,
						     object->region.node);
		पूर्ण

		second_desc = acpi_ns_get_secondary_object(object);
		अगर (second_desc) अणु
			/*
			 * Free the region_context अगर and only अगर the handler is one of the
			 * शेष handlers -- and thereक्रमe, we created the context object
			 * locally, it was not created by an बाह्यal caller.
			 */
			handler_desc = object->region.handler;
			अगर (handler_desc) अणु
				next_desc =
				    handler_desc->address_space.region_list;
				start_desc = next_desc;
				last_obj_ptr =
				    &handler_desc->address_space.region_list;

				/* Remove the region object from the handler list */

				जबतक (next_desc) अणु
					अगर (next_desc == object) अणु
						*last_obj_ptr =
						    next_desc->region.next;
						अवरोध;
					पूर्ण

					/* Walk the linked list of handlers */

					last_obj_ptr = &next_desc->region.next;
					next_desc = next_desc->region.next;

					/* Prevent infinite loop अगर list is corrupted */

					अगर (next_desc == start_desc) अणु
						ACPI_ERROR((AE_INFO,
							    "Circular region list in address handler object %p",
							    handler_desc));
						वापस_VOID;
					पूर्ण
				पूर्ण

				अगर (handler_desc->address_space.handler_flags &
				    ACPI_ADDR_HANDLER_DEFAULT_INSTALLED) अणु

					/* Deactivate region and मुक्त region context */

					अगर (handler_desc->address_space.setup) अणु
						(व्योम)handler_desc->
						    address_space.setup(object,
									ACPI_REGION_DEACTIVATE,
									handler_desc->
									address_space.
									context,
									&second_desc->
									extra.
									region_context);
					पूर्ण
				पूर्ण

				acpi_ut_हटाओ_reference(handler_desc);
			पूर्ण

			/* Now we can मुक्त the Extra object */

			acpi_ut_delete_object_desc(second_desc);
		पूर्ण
		अगर (object->field.पूर्णांकernal_pcc_buffer) अणु
			ACPI_FREE(object->field.पूर्णांकernal_pcc_buffer);
		पूर्ण

		अवरोध;

	हाल ACPI_TYPE_BUFFER_FIELD:

		ACPI_DEBUG_PRINT((ACPI_DB_ALLOCATIONS,
				  "***** Buffer Field %p\n", object));

		second_desc = acpi_ns_get_secondary_object(object);
		अगर (second_desc) अणु
			acpi_ut_delete_object_desc(second_desc);
		पूर्ण
		अवरोध;

	हाल ACPI_TYPE_LOCAL_BANK_FIELD:

		ACPI_DEBUG_PRINT((ACPI_DB_ALLOCATIONS,
				  "***** Bank Field %p\n", object));

		second_desc = acpi_ns_get_secondary_object(object);
		अगर (second_desc) अणु
			acpi_ut_delete_object_desc(second_desc);
		पूर्ण
		अवरोध;

	हाल ACPI_TYPE_LOCAL_ADDRESS_HANDLER:

		ACPI_DEBUG_PRINT((ACPI_DB_ALLOCATIONS,
				  "***** Address handler %p\n", object));

		acpi_os_delete_mutex(object->address_space.context_mutex);
		अवरोध;

	शेष:

		अवरोध;
	पूर्ण

	/* Free any allocated memory (poपूर्णांकer within the object) found above */

	अगर (obj_poपूर्णांकer) अणु
		ACPI_DEBUG_PRINT((ACPI_DB_ALLOCATIONS,
				  "Deleting Object Subptr %p\n", obj_poपूर्णांकer));
		ACPI_FREE(obj_poपूर्णांकer);
	पूर्ण

	/* Now the object can be safely deleted */

	ACPI_DEBUG_PRINT_RAW((ACPI_DB_ALLOCATIONS,
			      "%s: Deleting Object %p [%s]\n",
			      ACPI_GET_FUNCTION_NAME, object,
			      acpi_ut_get_object_type_name(object)));

	acpi_ut_delete_object_desc(object);
	वापस_VOID;
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_delete_पूर्णांकernal_object_list
 *
 * PARAMETERS:  obj_list        - Poपूर्णांकer to the list to be deleted
 *
 * RETURN:      None
 *
 * DESCRIPTION: This function deletes an पूर्णांकernal object list, including both
 *              simple objects and package objects
 *
 ******************************************************************************/

व्योम acpi_ut_delete_पूर्णांकernal_object_list(जोड़ acpi_opeअक्रम_object **obj_list)
अणु
	जोड़ acpi_opeअक्रम_object **पूर्णांकernal_obj;

	ACPI_FUNCTION_ENTRY();

	/* Walk the null-terminated पूर्णांकernal list */

	क्रम (पूर्णांकernal_obj = obj_list; *पूर्णांकernal_obj; पूर्णांकernal_obj++) अणु
		acpi_ut_हटाओ_reference(*पूर्णांकernal_obj);
	पूर्ण

	/* Free the combined parameter poपूर्णांकer list and object array */

	ACPI_FREE(obj_list);
	वापस;
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_update_ref_count
 *
 * PARAMETERS:  object          - Object whose ref count is to be updated
 *              action          - What to करो (REF_INCREMENT or REF_DECREMENT)
 *
 * RETURN:      None. Sets new reference count within the object
 *
 * DESCRIPTION: Modअगरy the reference count क्रम an पूर्णांकernal acpi object
 *
 ******************************************************************************/

अटल व्योम
acpi_ut_update_ref_count(जोड़ acpi_opeअक्रम_object *object, u32 action)
अणु
	u16 original_count;
	u16 new_count = 0;
	acpi_cpu_flags lock_flags;
	अक्षर *message;

	ACPI_FUNCTION_NAME(ut_update_ref_count);

	अगर (!object) अणु
		वापस;
	पूर्ण

	/*
	 * Always get the reference count lock. Note: Interpreter and/or
	 * Namespace is not always locked when this function is called.
	 */
	lock_flags = acpi_os_acquire_lock(acpi_gbl_reference_count_lock);
	original_count = object->common.reference_count;

	/* Perक्रमm the reference count action (increment, decrement) */

	चयन (action) अणु
	हाल REF_INCREMENT:

		new_count = original_count + 1;
		object->common.reference_count = new_count;
		acpi_os_release_lock(acpi_gbl_reference_count_lock, lock_flags);

		/* The current reference count should never be zero here */

		अगर (!original_count) अणु
			ACPI_WARNING((AE_INFO,
				      "Obj %p, Reference Count was zero before increment\n",
				      object));
		पूर्ण

		ACPI_DEBUG_PRINT((ACPI_DB_ALLOCATIONS,
				  "Obj %p Type %.2X [%s] Refs %.2X [Incremented]\n",
				  object, object->common.type,
				  acpi_ut_get_object_type_name(object),
				  new_count));
		message = "Incremement";
		अवरोध;

	हाल REF_DECREMENT:

		/* The current reference count must be non-zero */

		अगर (original_count) अणु
			new_count = original_count - 1;
			object->common.reference_count = new_count;
		पूर्ण

		acpi_os_release_lock(acpi_gbl_reference_count_lock, lock_flags);

		अगर (!original_count) अणु
			ACPI_WARNING((AE_INFO,
				      "Obj %p, Reference Count is already zero, cannot decrement\n",
				      object));
		पूर्ण

		ACPI_DEBUG_PRINT_RAW((ACPI_DB_ALLOCATIONS,
				      "%s: Obj %p Type %.2X Refs %.2X [Decremented]\n",
				      ACPI_GET_FUNCTION_NAME, object,
				      object->common.type, new_count));

		/* Actually delete the object on a reference count of zero */

		अगर (new_count == 0) अणु
			acpi_ut_delete_पूर्णांकernal_obj(object);
		पूर्ण
		message = "Decrement";
		अवरोध;

	शेष:

		acpi_os_release_lock(acpi_gbl_reference_count_lock, lock_flags);
		ACPI_ERROR((AE_INFO, "Unknown Reference Count action (0x%X)",
			    action));
		वापस;
	पूर्ण

	/*
	 * Sanity check the reference count, क्रम debug purposes only.
	 * (A deleted object will have a huge reference count)
	 */
	अगर (new_count > ACPI_MAX_REFERENCE_COUNT) अणु
		ACPI_WARNING((AE_INFO,
			      "Large Reference Count (0x%X) in object %p, Type=0x%.2X Operation=%s",
			      new_count, object, object->common.type, message));
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_update_object_reference
 *
 * PARAMETERS:  object              - Increment or decrement the ref count क्रम
 *                                    this object and all sub-objects
 *              action              - Either REF_INCREMENT or REF_DECREMENT
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Increment or decrement the object reference count
 *
 * Object references are incremented when:
 * 1) An object is attached to a Node (namespace object)
 * 2) An object is copied (all subobjects must be incremented)
 *
 * Object references are decremented when:
 * 1) An object is detached from an Node
 *
 ******************************************************************************/

acpi_status
acpi_ut_update_object_reference(जोड़ acpi_opeअक्रम_object *object, u16 action)
अणु
	acpi_status status = AE_OK;
	जोड़ acpi_generic_state *state_list = शून्य;
	जोड़ acpi_opeअक्रम_object *next_object = शून्य;
	जोड़ acpi_opeअक्रम_object *prev_object;
	जोड़ acpi_generic_state *state;
	u32 i;

	ACPI_FUNCTION_NAME(ut_update_object_reference);

	जबतक (object) अणु

		/* Make sure that this isn't a namespace handle */

		अगर (ACPI_GET_DESCRIPTOR_TYPE(object) == ACPI_DESC_TYPE_NAMED) अणु
			ACPI_DEBUG_PRINT((ACPI_DB_ALLOCATIONS,
					  "Object %p is NS handle\n", object));
			वापस (AE_OK);
		पूर्ण

		/*
		 * All sub-objects must have their reference count updated
		 * also. Dअगरferent object types have dअगरferent subobjects.
		 */
		चयन (object->common.type) अणु
		हाल ACPI_TYPE_DEVICE:
		हाल ACPI_TYPE_PROCESSOR:
		हाल ACPI_TYPE_POWER:
		हाल ACPI_TYPE_THERMAL:
			/*
			 * Update the notअगरy objects क्रम these types (अगर present)
			 * Two lists, प्रणाली and device notअगरy handlers.
			 */
			क्रम (i = 0; i < ACPI_NUM_NOTIFY_TYPES; i++) अणु
				prev_object =
				    object->common_notअगरy.notअगरy_list[i];
				जबतक (prev_object) अणु
					next_object =
					    prev_object->notअगरy.next[i];
					acpi_ut_update_ref_count(prev_object,
								 action);
					prev_object = next_object;
				पूर्ण
			पूर्ण
			अवरोध;

		हाल ACPI_TYPE_PACKAGE:
			/*
			 * We must update all the sub-objects of the package,
			 * each of whom may have their own sub-objects.
			 */
			क्रम (i = 0; i < object->package.count; i++) अणु
				/*
				 * Null package elements are legal and can be simply
				 * ignored.
				 */
				next_object = object->package.elements[i];
				अगर (!next_object) अणु
					जारी;
				पूर्ण

				चयन (next_object->common.type) अणु
				हाल ACPI_TYPE_INTEGER:
				हाल ACPI_TYPE_STRING:
				हाल ACPI_TYPE_BUFFER:
					/*
					 * For these very simple sub-objects, we can just
					 * update the reference count here and जारी.
					 * Greatly increases perक्रमmance of this operation.
					 */
					acpi_ut_update_ref_count(next_object,
								 action);
					अवरोध;

				शेष:
					/*
					 * For complex sub-objects, push them onto the stack
					 * क्रम later processing (this eliminates recursion.)
					 */
					status =
					    acpi_ut_create_update_state_and_push
					    (next_object, action, &state_list);
					अगर (ACPI_FAILURE(status)) अणु
						जाओ error_निकास;
					पूर्ण
					अवरोध;
				पूर्ण
			पूर्ण

			next_object = शून्य;
			अवरोध;

		हाल ACPI_TYPE_BUFFER_FIELD:

			next_object = object->buffer_field.buffer_obj;
			अवरोध;

		हाल ACPI_TYPE_LOCAL_BANK_FIELD:

			next_object = object->bank_field.bank_obj;
			status =
			    acpi_ut_create_update_state_and_push(object->
								 bank_field.
								 region_obj,
								 action,
								 &state_list);
			अगर (ACPI_FAILURE(status)) अणु
				जाओ error_निकास;
			पूर्ण
			अवरोध;

		हाल ACPI_TYPE_LOCAL_INDEX_FIELD:

			next_object = object->index_field.index_obj;
			status =
			    acpi_ut_create_update_state_and_push(object->
								 index_field.
								 data_obj,
								 action,
								 &state_list);
			अगर (ACPI_FAILURE(status)) अणु
				जाओ error_निकास;
			पूर्ण
			अवरोध;

		हाल ACPI_TYPE_LOCAL_REFERENCE:
			/*
			 * The target of an Index (a package, string, or buffer) or a named
			 * reference must track changes to the ref count of the index or
			 * target object.
			 */
			अगर ((object->reference.class == ACPI_REFCLASS_INDEX) ||
			    (object->reference.class == ACPI_REFCLASS_NAME)) अणु
				next_object = object->reference.object;
			पूर्ण
			अवरोध;

		हाल ACPI_TYPE_LOCAL_REGION_FIELD:
		हाल ACPI_TYPE_REGION:
		शेष:

			अवरोध;	/* No subobjects क्रम all other types */
		पूर्ण

		/*
		 * Now we can update the count in the मुख्य object. This can only
		 * happen after we update the sub-objects in हाल this causes the
		 * मुख्य object to be deleted.
		 */
		acpi_ut_update_ref_count(object, action);
		object = शून्य;

		/* Move on to the next object to be updated */

		अगर (next_object) अणु
			object = next_object;
			next_object = शून्य;
		पूर्ण अन्यथा अगर (state_list) अणु
			state = acpi_ut_pop_generic_state(&state_list);
			object = state->update.object;
			acpi_ut_delete_generic_state(state);
		पूर्ण
	पूर्ण

	वापस (AE_OK);

error_निकास:

	ACPI_EXCEPTION((AE_INFO, status,
			"Could not update object reference count"));

	/* Free any stacked Update State objects */

	जबतक (state_list) अणु
		state = acpi_ut_pop_generic_state(&state_list);
		acpi_ut_delete_generic_state(state);
	पूर्ण

	वापस (status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_add_reference
 *
 * PARAMETERS:  object          - Object whose reference count is to be
 *                                incremented
 *
 * RETURN:      None
 *
 * DESCRIPTION: Add one reference to an ACPI object
 *
 ******************************************************************************/

व्योम acpi_ut_add_reference(जोड़ acpi_opeअक्रम_object *object)
अणु

	ACPI_FUNCTION_NAME(ut_add_reference);

	/* Ensure that we have a valid object */

	अगर (!acpi_ut_valid_पूर्णांकernal_object(object)) अणु
		वापस;
	पूर्ण

	ACPI_DEBUG_PRINT((ACPI_DB_ALLOCATIONS,
			  "Obj %p Current Refs=%X [To Be Incremented]\n",
			  object, object->common.reference_count));

	/* Increment the reference count */

	(व्योम)acpi_ut_update_object_reference(object, REF_INCREMENT);
	वापस;
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_हटाओ_reference
 *
 * PARAMETERS:  object         - Object whose ref count will be decremented
 *
 * RETURN:      None
 *
 * DESCRIPTION: Decrement the reference count of an ACPI पूर्णांकernal object
 *
 ******************************************************************************/

व्योम acpi_ut_हटाओ_reference(जोड़ acpi_opeअक्रम_object *object)
अणु

	ACPI_FUNCTION_NAME(ut_हटाओ_reference);

	/*
	 * Allow a शून्य poपूर्णांकer to be passed in, just ignore it. This saves
	 * each caller from having to check. Also, ignore NS nodes.
	 */
	अगर (!object ||
	    (ACPI_GET_DESCRIPTOR_TYPE(object) == ACPI_DESC_TYPE_NAMED)) अणु
		वापस;
	पूर्ण

	/* Ensure that we have a valid object */

	अगर (!acpi_ut_valid_पूर्णांकernal_object(object)) अणु
		वापस;
	पूर्ण

	ACPI_DEBUG_PRINT_RAW((ACPI_DB_ALLOCATIONS,
			      "%s: Obj %p Current Refs=%X [To Be Decremented]\n",
			      ACPI_GET_FUNCTION_NAME, object,
			      object->common.reference_count));

	/*
	 * Decrement the reference count, and only actually delete the object
	 * अगर the reference count becomes 0. (Must also decrement the ref count
	 * of all subobjects!)
	 */
	(व्योम)acpi_ut_update_object_reference(object, REF_DECREMENT);
	वापस;
पूर्ण
