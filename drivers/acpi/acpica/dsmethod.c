<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: dsmethod - Parser/Interpreter पूर्णांकerface - control method parsing
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acdispat.h"
#समावेश "acinterp.h"
#समावेश "acnamesp.h"
#समावेश "acparser.h"
#समावेश "amlcode.h"
#समावेश "acdebug.h"

#घोषणा _COMPONENT          ACPI_DISPATCHER
ACPI_MODULE_NAME("dsmethod")

/* Local prototypes */
अटल acpi_status
acpi_ds_detect_named_opcodes(काष्ठा acpi_walk_state *walk_state,
			     जोड़ acpi_parse_object **out_op);

अटल acpi_status
acpi_ds_create_method_mutex(जोड़ acpi_opeअक्रम_object *method_desc);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_स्वतः_serialize_method
 *
 * PARAMETERS:  node                        - Namespace Node of the method
 *              obj_desc                    - Method object attached to node
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Parse a control method AML to scan क्रम control methods that
 *              need serialization due to the creation of named objects.
 *
 * NOTE: It is a bit of overसमाप्त to mark all such methods serialized, since
 * there is only a problem अगर the method actually blocks during execution.
 * A blocking operation is, क्रम example, a Sleep() operation, or any access
 * to an operation region. However, it is probably not possible to easily
 * detect whether a method will block or not, so we simply mark all suspicious
 * methods as serialized.
 *
 * NOTE2: This code is essentially a generic routine क्रम parsing a single
 * control method.
 *
 ******************************************************************************/

acpi_status
acpi_ds_स्वतः_serialize_method(काष्ठा acpi_namespace_node *node,
			      जोड़ acpi_opeअक्रम_object *obj_desc)
अणु
	acpi_status status;
	जोड़ acpi_parse_object *op = शून्य;
	काष्ठा acpi_walk_state *walk_state;

	ACPI_FUNCTION_TRACE_PTR(ds_स्वतः_serialize_method, node);

	ACPI_DEBUG_PRINT((ACPI_DB_PARSE,
			  "Method auto-serialization parse [%4.4s] %p\n",
			  acpi_ut_get_node_name(node), node));

	/* Create/Init a root op क्रम the method parse tree */

	op = acpi_ps_alloc_op(AML_METHOD_OP, obj_desc->method.aml_start);
	अगर (!op) अणु
		वापस_ACPI_STATUS(AE_NO_MEMORY);
	पूर्ण

	acpi_ps_set_name(op, node->name.पूर्णांकeger);
	op->common.node = node;

	/* Create and initialize a new walk state */

	walk_state =
	    acpi_ds_create_walk_state(node->owner_id, शून्य, शून्य, शून्य);
	अगर (!walk_state) अणु
		acpi_ps_मुक्त_op(op);
		वापस_ACPI_STATUS(AE_NO_MEMORY);
	पूर्ण

	status = acpi_ds_init_aml_walk(walk_state, op, node,
				       obj_desc->method.aml_start,
				       obj_desc->method.aml_length, शून्य, 0);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_ds_delete_walk_state(walk_state);
		acpi_ps_मुक्त_op(op);
		वापस_ACPI_STATUS(status);
	पूर्ण

	walk_state->descending_callback = acpi_ds_detect_named_opcodes;

	/* Parse the method, scan क्रम creation of named objects */

	status = acpi_ps_parse_aml(walk_state);

	acpi_ps_delete_parse_tree(op);
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_detect_named_opcodes
 *
 * PARAMETERS:  walk_state      - Current state of the parse tree walk
 *              out_op          - Unused, required क्रम parser पूर्णांकerface
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Descending callback used during the loading of ACPI tables.
 *              Currently used to detect methods that must be marked serialized
 *              in order to aव्योम problems with the creation of named objects.
 *
 ******************************************************************************/

अटल acpi_status
acpi_ds_detect_named_opcodes(काष्ठा acpi_walk_state *walk_state,
			     जोड़ acpi_parse_object **out_op)
अणु

	ACPI_FUNCTION_NAME(acpi_ds_detect_named_opcodes);

	/* We are only पूर्णांकerested in opcodes that create a new name */

	अगर (!
	    (walk_state->op_info->
	     flags & (AML_NAMED | AML_CREATE | AML_FIELD))) अणु
		वापस (AE_OK);
	पूर्ण

	/*
	 * At this poपूर्णांक, we know we have a Named object opcode.
	 * Mark the method as serialized. Later code will create a mutex क्रम
	 * this method to enक्रमce serialization.
	 *
	 * Note, ACPI_METHOD_IGNORE_SYNC_LEVEL flag means that we will ignore the
	 * Sync Level mechanism क्रम this method, even though it is now serialized.
	 * Otherwise, there can be conflicts with existing ASL code that actually
	 * uses sync levels.
	 */
	walk_state->method_desc->method.sync_level = 0;
	walk_state->method_desc->method.info_flags |=
	    (ACPI_METHOD_SERIALIZED | ACPI_METHOD_IGNORE_SYNC_LEVEL);

	ACPI_DEBUG_PRINT((ACPI_DB_INFO,
			  "Method serialized [%4.4s] %p - [%s] (%4.4X)\n",
			  walk_state->method_node->name.ascii,
			  walk_state->method_node, walk_state->op_info->name,
			  walk_state->opcode));

	/* Abort the parse, no need to examine this method any further */

	वापस (AE_CTRL_TERMINATE);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_method_error
 *
 * PARAMETERS:  status          - Execution status
 *              walk_state      - Current state
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Called on method error. Invoke the global exception handler अगर
 *              present, dump the method data अगर the debugger is configured
 *
 *              Note: Allows the exception handler to change the status code
 *
 ******************************************************************************/

acpi_status
acpi_ds_method_error(acpi_status status, काष्ठा acpi_walk_state *walk_state)
अणु
	u32 aml_offset;
	acpi_name name = 0;

	ACPI_FUNCTION_ENTRY();

	/* Ignore AE_OK and control exception codes */

	अगर (ACPI_SUCCESS(status) || (status & AE_CODE_CONTROL)) अणु
		वापस (status);
	पूर्ण

	/* Invoke the global exception handler */

	अगर (acpi_gbl_exception_handler) अणु

		/* Exit the पूर्णांकerpreter, allow handler to execute methods */

		acpi_ex_निकास_पूर्णांकerpreter();

		/*
		 * Handler can map the exception code to anything it wants, including
		 * AE_OK, in which हाल the executing method will not be पातed.
		 */
		aml_offset = (u32)ACPI_PTR_DIFF(walk_state->aml,
						walk_state->parser_state.
						aml_start);

		अगर (walk_state->method_node) अणु
			name = walk_state->method_node->name.पूर्णांकeger;
		पूर्ण अन्यथा अगर (walk_state->deferred_node) अणु
			name = walk_state->deferred_node->name.पूर्णांकeger;
		पूर्ण

		status = acpi_gbl_exception_handler(status, name,
						    walk_state->opcode,
						    aml_offset, शून्य);
		acpi_ex_enter_पूर्णांकerpreter();
	पूर्ण

	acpi_ds_clear_implicit_वापस(walk_state);

	अगर (ACPI_FAILURE(status)) अणु
		acpi_ds_dump_method_stack(status, walk_state, walk_state->op);

		/* Display method locals/args अगर debugger is present */

#अगर_घोषित ACPI_DEBUGGER
		acpi_db_dump_method_info(status, walk_state);
#पूर्ण_अगर
	पूर्ण

	वापस (status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_create_method_mutex
 *
 * PARAMETERS:  obj_desc            - The method object
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Create a mutex object क्रम a serialized control method
 *
 ******************************************************************************/

अटल acpi_status
acpi_ds_create_method_mutex(जोड़ acpi_opeअक्रम_object *method_desc)
अणु
	जोड़ acpi_opeअक्रम_object *mutex_desc;
	acpi_status status;

	ACPI_FUNCTION_TRACE(ds_create_method_mutex);

	/* Create the new mutex object */

	mutex_desc = acpi_ut_create_पूर्णांकernal_object(ACPI_TYPE_MUTEX);
	अगर (!mutex_desc) अणु
		वापस_ACPI_STATUS(AE_NO_MEMORY);
	पूर्ण

	/* Create the actual OS Mutex */

	status = acpi_os_create_mutex(&mutex_desc->mutex.os_mutex);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_ut_delete_object_desc(mutex_desc);
		वापस_ACPI_STATUS(status);
	पूर्ण

	mutex_desc->mutex.sync_level = method_desc->method.sync_level;
	method_desc->method.mutex = mutex_desc;
	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_begin_method_execution
 *
 * PARAMETERS:  method_node         - Node of the method
 *              obj_desc            - The method object
 *              walk_state          - current state, शून्य अगर not yet executing
 *                                    a method.
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Prepare a method क्रम execution. Parses the method अगर necessary,
 *              increments the thपढ़ो count, and रुकोs at the method semaphore
 *              क्रम clearance to execute.
 *
 ******************************************************************************/

acpi_status
acpi_ds_begin_method_execution(काष्ठा acpi_namespace_node *method_node,
			       जोड़ acpi_opeअक्रम_object *obj_desc,
			       काष्ठा acpi_walk_state *walk_state)
अणु
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TRACE_PTR(ds_begin_method_execution, method_node);

	अगर (!method_node) अणु
		वापस_ACPI_STATUS(AE_शून्य_ENTRY);
	पूर्ण

	acpi_ex_start_trace_method(method_node, obj_desc, walk_state);

	/* Prevent wraparound of thपढ़ो count */

	अगर (obj_desc->method.thपढ़ो_count == ACPI_UINT8_MAX) अणु
		ACPI_ERROR((AE_INFO,
			    "Method reached maximum reentrancy limit (255)"));
		वापस_ACPI_STATUS(AE_AML_METHOD_LIMIT);
	पूर्ण

	/*
	 * If this method is serialized, we need to acquire the method mutex.
	 */
	अगर (obj_desc->method.info_flags & ACPI_METHOD_SERIALIZED) अणु
		/*
		 * Create a mutex क्रम the method अगर it is defined to be Serialized
		 * and a mutex has not alपढ़ोy been created. We defer the mutex creation
		 * until a method is actually executed, to minimize the object count
		 */
		अगर (!obj_desc->method.mutex) अणु
			status = acpi_ds_create_method_mutex(obj_desc);
			अगर (ACPI_FAILURE(status)) अणु
				वापस_ACPI_STATUS(status);
			पूर्ण
		पूर्ण

		/*
		 * The current_sync_level (per-thपढ़ो) must be less than or equal to
		 * the sync level of the method. This mechanism provides some
		 * deadlock prevention.
		 *
		 * If the method was स्वतः-serialized, we just ignore the sync level
		 * mechanism, because स्वतः-serialization of methods can पूर्णांकerfere
		 * with ASL code that actually uses sync levels.
		 *
		 * Top-level method invocation has no walk state at this poपूर्णांक
		 */
		अगर (walk_state &&
		    (!(obj_desc->method.
		       info_flags & ACPI_METHOD_IGNORE_SYNC_LEVEL))
		    && (walk_state->thपढ़ो->current_sync_level >
			obj_desc->method.mutex->mutex.sync_level)) अणु
			ACPI_ERROR((AE_INFO,
				    "Cannot acquire Mutex for method [%4.4s]"
				    ", current SyncLevel is too large (%u)",
				    acpi_ut_get_node_name(method_node),
				    walk_state->thपढ़ो->current_sync_level));

			वापस_ACPI_STATUS(AE_AML_MUTEX_ORDER);
		पूर्ण

		/*
		 * Obtain the method mutex अगर necessary. Do not acquire mutex क्रम a
		 * recursive call.
		 */
		अगर (!walk_state ||
		    !obj_desc->method.mutex->mutex.thपढ़ो_id ||
		    (walk_state->thपढ़ो->thपढ़ो_id !=
		     obj_desc->method.mutex->mutex.thपढ़ो_id)) अणु
			/*
			 * Acquire the method mutex. This releases the पूर्णांकerpreter अगर we
			 * block (and reacquires it beक्रमe it वापसs)
			 */
			status =
			    acpi_ex_प्रणाली_रुको_mutex(obj_desc->method.mutex->
						      mutex.os_mutex,
						      ACPI_WAIT_FOREVER);
			अगर (ACPI_FAILURE(status)) अणु
				वापस_ACPI_STATUS(status);
			पूर्ण

			/* Update the mutex and walk info and save the original sync_level */

			अगर (walk_state) अणु
				obj_desc->method.mutex->mutex.
				    original_sync_level =
				    walk_state->thपढ़ो->current_sync_level;

				obj_desc->method.mutex->mutex.thपढ़ो_id =
				    walk_state->thपढ़ो->thपढ़ो_id;

				/*
				 * Update the current sync_level only अगर this is not an स्वतः-
				 * serialized method. In the स्वतः हाल, we have to ignore
				 * the sync level क्रम the method mutex (created क्रम the
				 * स्वतः-serialization) because we have no idea of what the
				 * sync level should be. Thereक्रमe, just ignore it.
				 */
				अगर (!(obj_desc->method.info_flags &
				      ACPI_METHOD_IGNORE_SYNC_LEVEL)) अणु
					walk_state->thपढ़ो->current_sync_level =
					    obj_desc->method.sync_level;
				पूर्ण
			पूर्ण अन्यथा अणु
				obj_desc->method.mutex->mutex.
				    original_sync_level =
				    obj_desc->method.mutex->mutex.sync_level;

				obj_desc->method.mutex->mutex.thपढ़ो_id =
				    acpi_os_get_thपढ़ो_id();
			पूर्ण
		पूर्ण

		/* Always increase acquisition depth */

		obj_desc->method.mutex->mutex.acquisition_depth++;
	पूर्ण

	/*
	 * Allocate an Owner ID क्रम this method, only अगर this is the first thपढ़ो
	 * to begin concurrent execution. We only need one owner_id, even अगर the
	 * method is invoked recursively.
	 */
	अगर (!obj_desc->method.owner_id) अणु
		status = acpi_ut_allocate_owner_id(&obj_desc->method.owner_id);
		अगर (ACPI_FAILURE(status)) अणु
			जाओ cleanup;
		पूर्ण
	पूर्ण

	/*
	 * Increment the method parse tree thपढ़ो count since it has been
	 * reentered one more समय (even अगर it is the same thपढ़ो)
	 */
	obj_desc->method.thपढ़ो_count++;
	acpi_method_count++;
	वापस_ACPI_STATUS(status);

cleanup:
	/* On error, must release the method mutex (अगर present) */

	अगर (obj_desc->method.mutex) अणु
		acpi_os_release_mutex(obj_desc->method.mutex->mutex.os_mutex);
	पूर्ण
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_call_control_method
 *
 * PARAMETERS:  thपढ़ो              - Info क्रम this thपढ़ो
 *              this_walk_state     - Current walk state
 *              op                  - Current Op to be walked
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Transfer execution to a called control method
 *
 ******************************************************************************/

acpi_status
acpi_ds_call_control_method(काष्ठा acpi_thपढ़ो_state *thपढ़ो,
			    काष्ठा acpi_walk_state *this_walk_state,
			    जोड़ acpi_parse_object *op)
अणु
	acpi_status status;
	काष्ठा acpi_namespace_node *method_node;
	काष्ठा acpi_walk_state *next_walk_state = शून्य;
	जोड़ acpi_opeअक्रम_object *obj_desc;
	काष्ठा acpi_evaluate_info *info;
	u32 i;

	ACPI_FUNCTION_TRACE_PTR(ds_call_control_method, this_walk_state);

	ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
			  "Calling method %p, currentstate=%p\n",
			  this_walk_state->prev_op, this_walk_state));

	/*
	 * Get the namespace entry क्रम the control method we are about to call
	 */
	method_node = this_walk_state->method_call_node;
	अगर (!method_node) अणु
		वापस_ACPI_STATUS(AE_शून्य_ENTRY);
	पूर्ण

	obj_desc = acpi_ns_get_attached_object(method_node);
	अगर (!obj_desc) अणु
		वापस_ACPI_STATUS(AE_शून्य_OBJECT);
	पूर्ण

	/* Init क्रम new method, possibly रुको on method mutex */

	status =
	    acpi_ds_begin_method_execution(method_node, obj_desc,
					   this_walk_state);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Begin method parse/execution. Create a new walk state */

	next_walk_state =
	    acpi_ds_create_walk_state(obj_desc->method.owner_id, शून्य, obj_desc,
				      thपढ़ो);
	अगर (!next_walk_state) अणु
		status = AE_NO_MEMORY;
		जाओ cleanup;
	पूर्ण

	/*
	 * The resolved arguments were put on the previous walk state's opeअक्रम
	 * stack. Opeअक्रमs on the previous walk state stack always
	 * start at index 0. Also, null terminate the list of arguments
	 */
	this_walk_state->opeअक्रमs[this_walk_state->num_opeअक्रमs] = शून्य;

	/*
	 * Allocate and initialize the evaluation inक्रमmation block
	 * TBD: this is somewhat inefficient, should change पूर्णांकerface to
	 * ds_init_aml_walk. For now, keeps this काष्ठा off the CPU stack
	 */
	info = ACPI_ALLOCATE_ZEROED(माप(काष्ठा acpi_evaluate_info));
	अगर (!info) अणु
		status = AE_NO_MEMORY;
		जाओ cleanup;
	पूर्ण

	info->parameters = &this_walk_state->opeअक्रमs[0];

	status = acpi_ds_init_aml_walk(next_walk_state, शून्य, method_node,
				       obj_desc->method.aml_start,
				       obj_desc->method.aml_length, info,
				       ACPI_IMODE_EXECUTE);

	ACPI_FREE(info);
	अगर (ACPI_FAILURE(status)) अणु
		जाओ cleanup;
	पूर्ण

	next_walk_state->method_nesting_depth =
	    this_walk_state->method_nesting_depth + 1;

	/*
	 * Delete the opeअक्रमs on the previous walkstate opeअक्रम stack
	 * (they were copied to new objects)
	 */
	क्रम (i = 0; i < obj_desc->method.param_count; i++) अणु
		acpi_ut_हटाओ_reference(this_walk_state->opeअक्रमs[i]);
		this_walk_state->opeअक्रमs[i] = शून्य;
	पूर्ण

	/* Clear the opeअक्रम stack */

	this_walk_state->num_opeअक्रमs = 0;

	ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
			  "**** Begin nested execution of [%4.4s] **** WalkState=%p\n",
			  method_node->name.ascii, next_walk_state));

	this_walk_state->method_pathname =
	    acpi_ns_get_normalized_pathname(method_node, TRUE);
	this_walk_state->method_is_nested = TRUE;

	/* Optional object evaluation log */

	ACPI_DEBUG_PRINT_RAW((ACPI_DB_EVALUATION,
			      "%-26s:  %*s%s\n", "   Nested method call",
			      next_walk_state->method_nesting_depth * 3, " ",
			      &this_walk_state->method_pathname[1]));

	/* Invoke an पूर्णांकernal method अगर necessary */

	अगर (obj_desc->method.info_flags & ACPI_METHOD_INTERNAL_ONLY) अणु
		status =
		    obj_desc->method.dispatch.implementation(next_walk_state);
		अगर (status == AE_OK) अणु
			status = AE_CTRL_TERMINATE;
		पूर्ण
	पूर्ण

	वापस_ACPI_STATUS(status);

cleanup:

	/* On error, we must terminate the method properly */

	acpi_ds_terminate_control_method(obj_desc, next_walk_state);
	acpi_ds_delete_walk_state(next_walk_state);

	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_restart_control_method
 *
 * PARAMETERS:  walk_state          - State क्रम preempted method (caller)
 *              वापस_desc         - Return value from the called method
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Restart a method that was preempted by another (nested) method
 *              invocation. Handle the वापस value (अगर any) from the callee.
 *
 ******************************************************************************/

acpi_status
acpi_ds_restart_control_method(काष्ठा acpi_walk_state *walk_state,
			       जोड़ acpi_opeअक्रम_object *वापस_desc)
अणु
	acpi_status status;
	पूर्णांक same_as_implicit_वापस;

	ACPI_FUNCTION_TRACE_PTR(ds_restart_control_method, walk_state);

	ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
			  "****Restart [%4.4s] Op %p ReturnValueFromCallee %p\n",
			  acpi_ut_get_node_name(walk_state->method_node),
			  walk_state->method_call_op, वापस_desc));

	ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
			  "    ReturnFromThisMethodUsed?=%X ResStack %p Walk %p\n",
			  walk_state->वापस_used,
			  walk_state->results, walk_state));

	/* Did the called method वापस a value? */

	अगर (वापस_desc) अणु

		/* Is the implicit वापस object the same as the वापस desc? */

		same_as_implicit_वापस =
		    (walk_state->implicit_वापस_obj == वापस_desc);

		/* Are we actually going to use the वापस value? */

		अगर (walk_state->वापस_used) अणु

			/* Save the वापस value from the previous method */

			status = acpi_ds_result_push(वापस_desc, walk_state);
			अगर (ACPI_FAILURE(status)) अणु
				acpi_ut_हटाओ_reference(वापस_desc);
				वापस_ACPI_STATUS(status);
			पूर्ण

			/*
			 * Save as THIS method's वापस value in हाल it is वापसed
			 * immediately to yet another method
			 */
			walk_state->वापस_desc = वापस_desc;
		पूर्ण

		/*
		 * The following code is the optional support क्रम the so-called
		 * "implicit return". Some AML code assumes that the last value of the
		 * method is "implicitly" वापसed to the caller, in the असलence of an
		 * explicit वापस value.
		 *
		 * Just save the last result of the method as the वापस value.
		 *
		 * NOTE: this is optional because the ASL language करोes not actually
		 * support this behavior.
		 */
		अन्यथा अगर (!acpi_ds_करो_implicit_वापस
			 (वापस_desc, walk_state, FALSE)
			 || same_as_implicit_वापस) अणु
			/*
			 * Delete the वापस value अगर it will not be used by the
			 * calling method or हटाओ one reference अगर the explicit वापस
			 * is the same as the implicit वापस value.
			 */
			acpi_ut_हटाओ_reference(वापस_desc);
		पूर्ण
	पूर्ण

	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_terminate_control_method
 *
 * PARAMETERS:  method_desc         - Method object
 *              walk_state          - State associated with the method
 *
 * RETURN:      None
 *
 * DESCRIPTION: Terminate a control method. Delete everything that the method
 *              created, delete all locals and arguments, and delete the parse
 *              tree अगर requested.
 *
 * MUTEX:       Interpreter is locked
 *
 ******************************************************************************/

व्योम
acpi_ds_terminate_control_method(जोड़ acpi_opeअक्रम_object *method_desc,
				 काष्ठा acpi_walk_state *walk_state)
अणु

	ACPI_FUNCTION_TRACE_PTR(ds_terminate_control_method, walk_state);

	/* method_desc is required, walk_state is optional */

	अगर (!method_desc) अणु
		वापस_VOID;
	पूर्ण

	अगर (walk_state) अणु

		/* Delete all arguments and locals */

		acpi_ds_method_data_delete_all(walk_state);

		/*
		 * Delete any namespace objects created anywhere within the
		 * namespace by the execution of this method. Unless:
		 * 1) This method is a module-level executable code method, in which
		 *    हाल we want make the objects permanent.
		 * 2) There are other thपढ़ोs executing the method, in which हाल we
		 *    will रुको until the last thपढ़ो has completed.
		 */
		अगर (!(method_desc->method.info_flags & ACPI_METHOD_MODULE_LEVEL)
		    && (method_desc->method.thपढ़ो_count == 1)) अणु

			/* Delete any direct children of (created by) this method */

			(व्योम)acpi_ex_निकास_पूर्णांकerpreter();
			acpi_ns_delete_namespace_subtree(walk_state->
							 method_node);
			(व्योम)acpi_ex_enter_पूर्णांकerpreter();

			/*
			 * Delete any objects that were created by this method
			 * अन्यथाwhere in the namespace (अगर any were created).
			 * Use of the ACPI_METHOD_MODIFIED_NAMESPACE optimizes the
			 * deletion such that we करोn't have to perक्रमm an entire
			 * namespace walk क्रम every control method execution.
			 */
			अगर (method_desc->method.
			    info_flags & ACPI_METHOD_MODIFIED_NAMESPACE) अणु
				(व्योम)acpi_ex_निकास_पूर्णांकerpreter();
				acpi_ns_delete_namespace_by_owner(method_desc->
								  method.
								  owner_id);
				(व्योम)acpi_ex_enter_पूर्णांकerpreter();
				method_desc->method.info_flags &=
				    ~ACPI_METHOD_MODIFIED_NAMESPACE;
			पूर्ण
		पूर्ण

		/*
		 * If method is serialized, release the mutex and restore the
		 * current sync level क्रम this thपढ़ो
		 */
		अगर (method_desc->method.mutex) अणु

			/* Acquisition Depth handles recursive calls */

			method_desc->method.mutex->mutex.acquisition_depth--;
			अगर (!method_desc->method.mutex->mutex.acquisition_depth) अणु
				walk_state->thपढ़ो->current_sync_level =
				    method_desc->method.mutex->mutex.
				    original_sync_level;

				acpi_os_release_mutex(method_desc->method.
						      mutex->mutex.os_mutex);
				method_desc->method.mutex->mutex.thपढ़ो_id = 0;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Decrement the thपढ़ो count on the method */

	अगर (method_desc->method.thपढ़ो_count) अणु
		method_desc->method.thपढ़ो_count--;
	पूर्ण अन्यथा अणु
		ACPI_ERROR((AE_INFO, "Invalid zero thread count in method"));
	पूर्ण

	/* Are there any other thपढ़ोs currently executing this method? */

	अगर (method_desc->method.thपढ़ो_count) अणु
		/*
		 * Additional thपढ़ोs. Do not release the owner_id in this हाल,
		 * we immediately reuse it क्रम the next thपढ़ो executing this method
		 */
		ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
				  "*** Completed execution of one thread, %u threads remaining\n",
				  method_desc->method.thपढ़ो_count));
	पूर्ण अन्यथा अणु
		/* This is the only executing thपढ़ो क्रम this method */

		/*
		 * Support to dynamically change a method from not_serialized to
		 * Serialized अगर it appears that the method is incorrectly written and
		 * करोes not support multiple thपढ़ो execution. The best example of this
		 * is अगर such a method creates namespace objects and blocks. A second
		 * thपढ़ो will fail with an AE_ALREADY_EXISTS exception.
		 *
		 * This code is here because we must रुको until the last thपढ़ो निकासs
		 * beक्रमe marking the method as serialized.
		 */
		अगर (method_desc->method.
		    info_flags & ACPI_METHOD_SERIALIZED_PENDING) अणु
			अगर (walk_state) अणु
				ACPI_INFO(("Marking method %4.4s as Serialized "
					   "because of AE_ALREADY_EXISTS error",
					   walk_state->method_node->name.
					   ascii));
			पूर्ण

			/*
			 * Method tried to create an object twice and was marked as
			 * "pending serialized". The probable cause is that the method
			 * cannot handle reentrancy.
			 *
			 * The method was created as not_serialized, but it tried to create
			 * a named object and then blocked, causing the second thपढ़ो
			 * entrance to begin and then fail. Workaround this problem by
			 * marking the method permanently as Serialized when the last
			 * thपढ़ो निकासs here.
			 */
			method_desc->method.info_flags &=
			    ~ACPI_METHOD_SERIALIZED_PENDING;

			method_desc->method.info_flags |=
			    (ACPI_METHOD_SERIALIZED |
			     ACPI_METHOD_IGNORE_SYNC_LEVEL);
			method_desc->method.sync_level = 0;
		पूर्ण

		/* No more thपढ़ोs, we can मुक्त the owner_id */

		अगर (!
		    (method_desc->method.
		     info_flags & ACPI_METHOD_MODULE_LEVEL)) अणु
			acpi_ut_release_owner_id(&method_desc->method.owner_id);
		पूर्ण
	पूर्ण

	acpi_ex_stop_trace_method((काष्ठा acpi_namespace_node *)method_desc->
				  method.node, method_desc, walk_state);

	वापस_VOID;
पूर्ण
