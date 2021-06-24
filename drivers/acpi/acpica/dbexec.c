<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/*******************************************************************************
 *
 * Module Name: dbexec - debugger control method execution
 *
 ******************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acdebug.h"
#समावेश "acnamesp.h"

#घोषणा _COMPONENT          ACPI_CA_DEBUGGER
ACPI_MODULE_NAME("dbexec")

अटल काष्ठा acpi_db_method_info acpi_gbl_db_method_info;

/* Local prototypes */

अटल acpi_status
acpi_db_execute_method(काष्ठा acpi_db_method_info *info,
		       काष्ठा acpi_buffer *वापस_obj);

अटल acpi_status acpi_db_execute_setup(काष्ठा acpi_db_method_info *info);

अटल u32 acpi_db_get_outstanding_allocations(व्योम);

अटल व्योम ACPI_SYSTEM_XFACE acpi_db_method_thपढ़ो(व्योम *context);

अटल acpi_status
acpi_db_execution_walk(acpi_handle obj_handle,
		       u32 nesting_level, व्योम *context, व्योम **वापस_value);

अटल व्योम ACPI_SYSTEM_XFACE acpi_db_single_execution_thपढ़ो(व्योम *context);

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_delete_objects
 *
 * PARAMETERS:  count               - Count of objects in the list
 *              objects             - Array of ACPI_OBJECTs to be deleted
 *
 * RETURN:      None
 *
 * DESCRIPTION: Delete a list of ACPI_OBJECTS. Handles packages and nested
 *              packages via recursion.
 *
 ******************************************************************************/

व्योम acpi_db_delete_objects(u32 count, जोड़ acpi_object *objects)
अणु
	u32 i;

	क्रम (i = 0; i < count; i++) अणु
		चयन (objects[i].type) अणु
		हाल ACPI_TYPE_BUFFER:

			ACPI_FREE(objects[i].buffer.poपूर्णांकer);
			अवरोध;

		हाल ACPI_TYPE_PACKAGE:

			/* Recursive call to delete package elements */

			acpi_db_delete_objects(objects[i].package.count,
					       objects[i].package.elements);

			/* Free the elements array */

			ACPI_FREE(objects[i].package.elements);
			अवरोध;

		शेष:

			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_execute_method
 *
 * PARAMETERS:  info            - Valid info segment
 *              वापस_obj      - Where to put वापस object
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Execute a control method. Used to evaluate objects via the
 *              "EXECUTE" or "EVALUATE" commands.
 *
 ******************************************************************************/

अटल acpi_status
acpi_db_execute_method(काष्ठा acpi_db_method_info *info,
		       काष्ठा acpi_buffer *वापस_obj)
अणु
	acpi_status status;
	काष्ठा acpi_object_list param_objects;
	जोड़ acpi_object params[ACPI_DEBUGGER_MAX_ARGS + 1];
	u32 i;

	ACPI_FUNCTION_TRACE(db_execute_method);

	अगर (acpi_gbl_db_output_to_file && !acpi_dbg_level) अणु
		acpi_os_म_लिखो("Warning: debug output is not enabled!\n");
	पूर्ण

	param_objects.count = 0;
	param_objects.poपूर्णांकer = शून्य;

	/* Pass through any command-line arguments */

	अगर (info->args && info->args[0]) अणु

		/* Get arguments passed on the command line */

		क्रम (i = 0; (info->args[i] && *(info->args[i])); i++) अणु

			/* Convert input string (token) to an actual जोड़ acpi_object */

			status = acpi_db_convert_to_object(info->types[i],
							   info->args[i],
							   &params[i]);
			अगर (ACPI_FAILURE(status)) अणु
				ACPI_EXCEPTION((AE_INFO, status,
						"While parsing method arguments"));
				जाओ cleanup;
			पूर्ण
		पूर्ण

		param_objects.count = i;
		param_objects.poपूर्णांकer = params;
	पूर्ण

	/* Prepare क्रम a वापस object of arbitrary size */

	वापस_obj->poपूर्णांकer = acpi_gbl_db_buffer;
	वापस_obj->length = ACPI_DEBUG_BUFFER_SIZE;

	/* Do the actual method execution */

	acpi_gbl_method_executing = TRUE;
	status = acpi_evaluate_object(शून्य, info->pathname,
				      &param_objects, वापस_obj);

	acpi_gbl_cm_single_step = FALSE;
	acpi_gbl_method_executing = FALSE;

	अगर (ACPI_FAILURE(status)) अणु
		अगर ((status == AE_ABORT_METHOD) || acpi_gbl_पात_method) अणु

			/* Clear the पात and fall back to the debugger prompt */

			ACPI_EXCEPTION((AE_INFO, status,
					"Aborting top-level method"));

			acpi_gbl_पात_method = FALSE;
			status = AE_OK;
			जाओ cleanup;
		पूर्ण

		ACPI_EXCEPTION((AE_INFO, status,
				"while executing %s from AML Debugger",
				info->pathname));

		अगर (status == AE_BUFFER_OVERFLOW) अणु
			ACPI_ERROR((AE_INFO,
				    "Possible buffer overflow within AML Debugger "
				    "buffer (size 0x%X needed 0x%X)",
				    ACPI_DEBUG_BUFFER_SIZE,
				    (u32)वापस_obj->length));
		पूर्ण
	पूर्ण

cleanup:
	acpi_db_delete_objects(param_objects.count, params);
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_execute_setup
 *
 * PARAMETERS:  info            - Valid method info
 *
 * RETURN:      None
 *
 * DESCRIPTION: Setup info segment prior to method execution
 *
 ******************************************************************************/

अटल acpi_status acpi_db_execute_setup(काष्ठा acpi_db_method_info *info)
अणु
	acpi_status status;

	ACPI_FUNCTION_NAME(db_execute_setup);

	/* Concatenate the current scope to the supplied name */

	info->pathname[0] = 0;
	अगर ((info->name[0] != '\\') && (info->name[0] != '/')) अणु
		अगर (acpi_ut_safe_म_जोड़ो(info->pathname, माप(info->pathname),
					acpi_gbl_db_scope_buf)) अणु
			status = AE_BUFFER_OVERFLOW;
			जाओ error_निकास;
		पूर्ण
	पूर्ण

	अगर (acpi_ut_safe_म_जोड़ो(info->pathname, माप(info->pathname),
				info->name)) अणु
		status = AE_BUFFER_OVERFLOW;
		जाओ error_निकास;
	पूर्ण

	acpi_db_prep_namestring(info->pathname);

	acpi_db_set_output_destination(ACPI_DB_DUPLICATE_OUTPUT);
	acpi_os_म_लिखो("Evaluating %s\n", info->pathname);

	अगर (info->flags & EX_SINGLE_STEP) अणु
		acpi_gbl_cm_single_step = TRUE;
		acpi_db_set_output_destination(ACPI_DB_CONSOLE_OUTPUT);
	पूर्ण

	अन्यथा अणु
		/* No single step, allow redirection to a file */

		acpi_db_set_output_destination(ACPI_DB_REसूचीECTABLE_OUTPUT);
	पूर्ण

	वापस (AE_OK);

error_निकास:

	ACPI_EXCEPTION((AE_INFO, status, "During setup for method execution"));
	वापस (status);
पूर्ण

#अगर_घोषित ACPI_DBG_TRACK_ALLOCATIONS
u32 acpi_db_get_cache_info(काष्ठा acpi_memory_list *cache)
अणु

	वापस (cache->total_allocated - cache->total_मुक्तd -
		cache->current_depth);
पूर्ण
#पूर्ण_अगर

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_get_outstanding_allocations
 *
 * PARAMETERS:  None
 *
 * RETURN:      Current global allocation count minus cache entries
 *
 * DESCRIPTION: Determine the current number of "outstanding" allocations --
 *              those allocations that have not been मुक्तd and also are not
 *              in one of the various object caches.
 *
 ******************************************************************************/

अटल u32 acpi_db_get_outstanding_allocations(व्योम)
अणु
	u32 outstanding = 0;

#अगर_घोषित ACPI_DBG_TRACK_ALLOCATIONS

	outstanding += acpi_db_get_cache_info(acpi_gbl_state_cache);
	outstanding += acpi_db_get_cache_info(acpi_gbl_ps_node_cache);
	outstanding += acpi_db_get_cache_info(acpi_gbl_ps_node_ext_cache);
	outstanding += acpi_db_get_cache_info(acpi_gbl_opeअक्रम_cache);
#पूर्ण_अगर

	वापस (outstanding);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_execution_walk
 *
 * PARAMETERS:  WALK_CALLBACK
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Execute a control method. Name is relative to the current
 *              scope.
 *
 ******************************************************************************/

अटल acpi_status
acpi_db_execution_walk(acpi_handle obj_handle,
		       u32 nesting_level, व्योम *context, व्योम **वापस_value)
अणु
	जोड़ acpi_opeअक्रम_object *obj_desc;
	काष्ठा acpi_namespace_node *node =
	    (काष्ठा acpi_namespace_node *)obj_handle;
	काष्ठा acpi_buffer वापस_obj;
	acpi_status status;

	obj_desc = acpi_ns_get_attached_object(node);
	अगर (obj_desc->method.param_count) अणु
		वापस (AE_OK);
	पूर्ण

	वापस_obj.poपूर्णांकer = शून्य;
	वापस_obj.length = ACPI_ALLOCATE_BUFFER;

	acpi_ns_prपूर्णांक_node_pathname(node, "Evaluating");

	/* Do the actual method execution */

	acpi_os_म_लिखो("\n");
	acpi_gbl_method_executing = TRUE;

	status = acpi_evaluate_object(node, शून्य, शून्य, &वापस_obj);

	acpi_gbl_method_executing = FALSE;

	acpi_os_म_लिखो("Evaluation of [%4.4s] returned %s\n",
		       acpi_ut_get_node_name(node),
		       acpi_क्रमmat_exception(status));

	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_execute
 *
 * PARAMETERS:  name                - Name of method to execute
 *              args                - Parameters to the method
 *              Types               -
 *              flags               - single step/no single step
 *
 * RETURN:      None
 *
 * DESCRIPTION: Execute a control method. Name is relative to the current
 *              scope. Function used क्रम the "EXECUTE", "EVALUATE", and
 *              "ALL" commands
 *
 ******************************************************************************/

व्योम
acpi_db_execute(अक्षर *name, अक्षर **args, acpi_object_type *types, u32 flags)
अणु
	acpi_status status;
	काष्ठा acpi_buffer वापस_obj;
	अक्षर *name_string;

#अगर_घोषित ACPI_DEBUG_OUTPUT
	u32 previous_allocations;
	u32 allocations;
#पूर्ण_अगर

	/*
	 * Allow one execution to be perक्रमmed by debugger or single step
	 * execution will be dead locked by the पूर्णांकerpreter mutexes.
	 */
	अगर (acpi_gbl_method_executing) अणु
		acpi_os_म_लिखो("Only one debugger execution is allowed.\n");
		वापस;
	पूर्ण
#अगर_घोषित ACPI_DEBUG_OUTPUT
	/* Memory allocation tracking */

	previous_allocations = acpi_db_get_outstanding_allocations();
#पूर्ण_अगर

	अगर (*name == '*') अणु
		(व्योम)acpi_walk_namespace(ACPI_TYPE_METHOD, ACPI_ROOT_OBJECT,
					  ACPI_UINT32_MAX,
					  acpi_db_execution_walk, शून्य, शून्य,
					  शून्य);
		वापस;
	पूर्ण

	अगर ((flags & EX_ALL) && (म_माप(name) > 4)) अणु
		acpi_os_म_लिखो("Input name (%s) must be a 4-char NameSeg\n",
			       name);
		वापस;
	पूर्ण

	name_string = ACPI_ALLOCATE(म_माप(name) + 1);
	अगर (!name_string) अणु
		वापस;
	पूर्ण

	स_रखो(&acpi_gbl_db_method_info, 0, माप(काष्ठा acpi_db_method_info));
	म_नकल(name_string, name);
	acpi_ut_strupr(name_string);

	/* Subcommand to Execute all predefined names in the namespace */

	अगर (!म_भेदन(name_string, "PREDEF", 6)) अणु
		acpi_db_evaluate_predefined_names();
		ACPI_FREE(name_string);
		वापस;
	पूर्ण

	/* Command (ALL <nameseg>) to execute all methods of a particular name */

	अन्यथा अगर (flags & EX_ALL) अणु
		acpi_gbl_db_method_info.name = name_string;
		वापस_obj.poपूर्णांकer = शून्य;
		वापस_obj.length = ACPI_ALLOCATE_BUFFER;
		acpi_db_evaluate_all(name_string);
		ACPI_FREE(name_string);
		वापस;
	पूर्ण अन्यथा अणु
		acpi_gbl_db_method_info.name = name_string;
		acpi_gbl_db_method_info.args = args;
		acpi_gbl_db_method_info.types = types;
		acpi_gbl_db_method_info.flags = flags;

		वापस_obj.poपूर्णांकer = शून्य;
		वापस_obj.length = ACPI_ALLOCATE_BUFFER;
	पूर्ण

	status = acpi_db_execute_setup(&acpi_gbl_db_method_info);
	अगर (ACPI_FAILURE(status)) अणु
		ACPI_FREE(name_string);
		वापस;
	पूर्ण

	/* Get the NS node, determines existence also */

	status = acpi_get_handle(शून्य, acpi_gbl_db_method_info.pathname,
				 &acpi_gbl_db_method_info.method);
	अगर (ACPI_SUCCESS(status)) अणु
		status = acpi_db_execute_method(&acpi_gbl_db_method_info,
						&वापस_obj);
	पूर्ण
	ACPI_FREE(name_string);

	/*
	 * Allow any handlers in separate thपढ़ोs to complete.
	 * (Such as Notअगरy handlers invoked from AML executed above).
	 */
	acpi_os_sleep((u64)10);

#अगर_घोषित ACPI_DEBUG_OUTPUT

	/* Memory allocation tracking */

	allocations =
	    acpi_db_get_outstanding_allocations() - previous_allocations;

	acpi_db_set_output_destination(ACPI_DB_DUPLICATE_OUTPUT);

	अगर (allocations > 0) अणु
		acpi_os_म_लिखो
		    ("0x%X Outstanding allocations after evaluation of %s\n",
		     allocations, acpi_gbl_db_method_info.pathname);
	पूर्ण
#पूर्ण_अगर

	अगर (ACPI_FAILURE(status)) अणु
		acpi_os_म_लिखो("Evaluation of %s failed with status %s\n",
			       acpi_gbl_db_method_info.pathname,
			       acpi_क्रमmat_exception(status));
	पूर्ण अन्यथा अणु
		/* Display a वापस object, अगर any */

		अगर (वापस_obj.length) अणु
			acpi_os_म_लिखो("Evaluation of %s returned object %p, "
				       "external buffer length %X\n",
				       acpi_gbl_db_method_info.pathname,
				       वापस_obj.poपूर्णांकer,
				       (u32)वापस_obj.length);

			acpi_db_dump_बाह्यal_object(वापस_obj.poपूर्णांकer, 1);
			acpi_os_म_लिखो("\n");

			/* Dump a _PLD buffer अगर present */

			अगर (ACPI_COMPARE_NAMESEG
			    ((ACPI_CAST_PTR
			      (काष्ठा acpi_namespace_node,
			       acpi_gbl_db_method_info.method)->name.ascii),
			     METHOD_NAME__PLD)) अणु
				acpi_db_dump_pld_buffer(वापस_obj.poपूर्णांकer);
			पूर्ण
		पूर्ण अन्यथा अणु
			acpi_os_म_लिखो
			    ("No object was returned from evaluation of %s\n",
			     acpi_gbl_db_method_info.pathname);
		पूर्ण
	पूर्ण

	acpi_db_set_output_destination(ACPI_DB_CONSOLE_OUTPUT);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_method_thपढ़ो
 *
 * PARAMETERS:  context             - Execution info segment
 *
 * RETURN:      None
 *
 * DESCRIPTION: Debugger execute thपढ़ो. Waits क्रम a command line, then
 *              simply dispatches it.
 *
 ******************************************************************************/

अटल व्योम ACPI_SYSTEM_XFACE acpi_db_method_thपढ़ो(व्योम *context)
अणु
	acpi_status status;
	काष्ठा acpi_db_method_info *info = context;
	काष्ठा acpi_db_method_info local_info;
	u32 i;
	u8 allow;
	काष्ठा acpi_buffer वापस_obj;

	/*
	 * acpi_gbl_db_method_info.Arguments will be passed as method arguments.
	 * Prevent acpi_gbl_db_method_info from being modअगरied by multiple thपढ़ोs
	 * concurrently.
	 *
	 * Note: The arguments we are passing are used by the ASL test suite
	 * (aslts). Do not change them without updating the tests.
	 */
	(व्योम)acpi_os_रुको_semaphore(info->info_gate, 1, ACPI_WAIT_FOREVER);

	अगर (info->init_args) अणु
		acpi_db_uपूर्णांक32_to_hex_string(info->num_created,
					     info->index_of_thपढ़ो_str);
		acpi_db_uपूर्णांक32_to_hex_string((u32)acpi_os_get_thपढ़ो_id(),
					     info->id_of_thपढ़ो_str);
	पूर्ण

	अगर (info->thपढ़ोs && (info->num_created < info->num_thपढ़ोs)) अणु
		info->thपढ़ोs[info->num_created++] = acpi_os_get_thपढ़ो_id();
	पूर्ण

	local_info = *info;
	local_info.args = local_info.arguments;
	local_info.arguments[0] = local_info.num_thपढ़ोs_str;
	local_info.arguments[1] = local_info.id_of_thपढ़ो_str;
	local_info.arguments[2] = local_info.index_of_thपढ़ो_str;
	local_info.arguments[3] = शून्य;

	local_info.types = local_info.arg_types;

	(व्योम)acpi_os_संकेत_semaphore(info->info_gate, 1);

	क्रम (i = 0; i < info->num_loops; i++) अणु
		status = acpi_db_execute_method(&local_info, &वापस_obj);
		अगर (ACPI_FAILURE(status)) अणु
			acpi_os_म_लिखो
			    ("%s During evaluation of %s at iteration %X\n",
			     acpi_क्रमmat_exception(status), info->pathname, i);
			अगर (status == AE_ABORT_METHOD) अणु
				अवरोध;
			पूर्ण
		पूर्ण
#अगर 0
		अगर ((i % 100) == 0) अणु
			acpi_os_म_लिखो("%u loops, Thread 0x%x\n",
				       i, acpi_os_get_thपढ़ो_id());
		पूर्ण

		अगर (वापस_obj.length) अणु
			acpi_os_म_लिखो
			    ("Evaluation of %s returned object %p Buflen %X\n",
			     info->pathname, वापस_obj.poपूर्णांकer,
			     (u32)वापस_obj.length);
			acpi_db_dump_बाह्यal_object(वापस_obj.poपूर्णांकer, 1);
		पूर्ण
#पूर्ण_अगर
	पूर्ण

	/* Signal our completion */

	allow = 0;
	(व्योम)acpi_os_रुको_semaphore(info->thपढ़ो_complete_gate,
				     1, ACPI_WAIT_FOREVER);
	info->num_completed++;

	अगर (info->num_completed == info->num_thपढ़ोs) अणु

		/* Do संकेत क्रम मुख्य thपढ़ो once only */
		allow = 1;
	पूर्ण

	(व्योम)acpi_os_संकेत_semaphore(info->thपढ़ो_complete_gate, 1);

	अगर (allow) अणु
		status = acpi_os_संकेत_semaphore(info->मुख्य_thपढ़ो_gate, 1);
		अगर (ACPI_FAILURE(status)) अणु
			acpi_os_म_लिखो
			    ("Could not signal debugger thread sync semaphore, %s\n",
			     acpi_क्रमmat_exception(status));
		पूर्ण
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_single_execution_thपढ़ो
 *
 * PARAMETERS:  context                 - Method info काष्ठा
 *
 * RETURN:      None
 *
 * DESCRIPTION: Create one thपढ़ो and execute a method
 *
 ******************************************************************************/

अटल व्योम ACPI_SYSTEM_XFACE acpi_db_single_execution_thपढ़ो(व्योम *context)
अणु
	काष्ठा acpi_db_method_info *info = context;
	acpi_status status;
	काष्ठा acpi_buffer वापस_obj;

	acpi_os_म_लिखो("\n");

	status = acpi_db_execute_method(info, &वापस_obj);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_os_म_लिखो("%s During evaluation of %s\n",
			       acpi_क्रमmat_exception(status), info->pathname);
		वापस;
	पूर्ण

	/* Display a वापस object, अगर any */

	अगर (वापस_obj.length) अणु
		acpi_os_म_लिखो("Evaluation of %s returned object %p, "
			       "external buffer length %X\n",
			       acpi_gbl_db_method_info.pathname,
			       वापस_obj.poपूर्णांकer, (u32)वापस_obj.length);

		acpi_db_dump_बाह्यal_object(वापस_obj.poपूर्णांकer, 1);
	पूर्ण

	acpi_os_म_लिखो("\nBackground thread completed\n%c ",
		       ACPI_DEBUGGER_COMMAND_PROMPT);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_create_execution_thपढ़ो
 *
 * PARAMETERS:  method_name_arg         - Control method to execute
 *              arguments               - Array of arguments to the method
 *              types                   - Corresponding array of object types
 *
 * RETURN:      None
 *
 * DESCRIPTION: Create a single thपढ़ो to evaluate a namespace object. Handles
 *              arguments passed on command line क्रम control methods.
 *
 ******************************************************************************/

व्योम
acpi_db_create_execution_thपढ़ो(अक्षर *method_name_arg,
				अक्षर **arguments, acpi_object_type *types)
अणु
	acpi_status status;
	u32 i;

	स_रखो(&acpi_gbl_db_method_info, 0, माप(काष्ठा acpi_db_method_info));
	acpi_gbl_db_method_info.name = method_name_arg;
	acpi_gbl_db_method_info.init_args = 1;
	acpi_gbl_db_method_info.args = acpi_gbl_db_method_info.arguments;
	acpi_gbl_db_method_info.types = acpi_gbl_db_method_info.arg_types;

	/* Setup method arguments, up to 7 (0-6) */

	क्रम (i = 0; (i < ACPI_METHOD_NUM_ARGS) && *arguments; i++) अणु
		acpi_gbl_db_method_info.arguments[i] = *arguments;
		arguments++;

		acpi_gbl_db_method_info.arg_types[i] = *types;
		types++;
	पूर्ण

	status = acpi_db_execute_setup(&acpi_gbl_db_method_info);
	अगर (ACPI_FAILURE(status)) अणु
		वापस;
	पूर्ण

	/* Get the NS node, determines existence also */

	status = acpi_get_handle(शून्य, acpi_gbl_db_method_info.pathname,
				 &acpi_gbl_db_method_info.method);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_os_म_लिखो("%s Could not get handle for %s\n",
			       acpi_क्रमmat_exception(status),
			       acpi_gbl_db_method_info.pathname);
		वापस;
	पूर्ण

	status = acpi_os_execute(OSL_DEBUGGER_EXEC_THREAD,
				 acpi_db_single_execution_thपढ़ो,
				 &acpi_gbl_db_method_info);
	अगर (ACPI_FAILURE(status)) अणु
		वापस;
	पूर्ण

	acpi_os_म_लिखो("\nBackground thread started\n");
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_create_execution_thपढ़ोs
 *
 * PARAMETERS:  num_thपढ़ोs_arg         - Number of thपढ़ोs to create
 *              num_loops_arg           - Loop count क्रम the thपढ़ो(s)
 *              method_name_arg         - Control method to execute
 *
 * RETURN:      None
 *
 * DESCRIPTION: Create thपढ़ोs to execute method(s)
 *
 ******************************************************************************/

व्योम
acpi_db_create_execution_thपढ़ोs(अक्षर *num_thपढ़ोs_arg,
				 अक्षर *num_loops_arg, अक्षर *method_name_arg)
अणु
	acpi_status status;
	u32 num_thपढ़ोs;
	u32 num_loops;
	u32 i;
	u32 size;
	acpi_mutex मुख्य_thपढ़ो_gate;
	acpi_mutex thपढ़ो_complete_gate;
	acpi_mutex info_gate;

	/* Get the arguments */

	num_thपढ़ोs = म_से_अदीर्घ(num_thपढ़ोs_arg, शून्य, 0);
	num_loops = म_से_अदीर्घ(num_loops_arg, शून्य, 0);

	अगर (!num_thपढ़ोs || !num_loops) अणु
		acpi_os_म_लिखो("Bad argument: Threads %X, Loops %X\n",
			       num_thपढ़ोs, num_loops);
		वापस;
	पूर्ण

	/*
	 * Create the semaphore क्रम synchronization of
	 * the created thपढ़ोs with the मुख्य thपढ़ो.
	 */
	status = acpi_os_create_semaphore(1, 0, &मुख्य_thपढ़ो_gate);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_os_म_लिखो("Could not create semaphore for "
			       "synchronization with the main thread, %s\n",
			       acpi_क्रमmat_exception(status));
		वापस;
	पूर्ण

	/*
	 * Create the semaphore क्रम synchronization
	 * between the created thपढ़ोs.
	 */
	status = acpi_os_create_semaphore(1, 1, &thपढ़ो_complete_gate);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_os_म_लिखो("Could not create semaphore for "
			       "synchronization between the created threads, %s\n",
			       acpi_क्रमmat_exception(status));

		(व्योम)acpi_os_delete_semaphore(मुख्य_thपढ़ो_gate);
		वापस;
	पूर्ण

	status = acpi_os_create_semaphore(1, 1, &info_gate);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_os_म_लिखो("Could not create semaphore for "
			       "synchronization of AcpiGbl_DbMethodInfo, %s\n",
			       acpi_क्रमmat_exception(status));

		(व्योम)acpi_os_delete_semaphore(thपढ़ो_complete_gate);
		(व्योम)acpi_os_delete_semaphore(मुख्य_thपढ़ो_gate);
		वापस;
	पूर्ण

	स_रखो(&acpi_gbl_db_method_info, 0, माप(काष्ठा acpi_db_method_info));

	/* Array to store IDs of thपढ़ोs */

	acpi_gbl_db_method_info.num_thपढ़ोs = num_thपढ़ोs;
	size = माप(acpi_thपढ़ो_id) * acpi_gbl_db_method_info.num_thपढ़ोs;

	acpi_gbl_db_method_info.thपढ़ोs = acpi_os_allocate(size);
	अगर (acpi_gbl_db_method_info.thपढ़ोs == शून्य) अणु
		acpi_os_म_लिखो("No memory for thread IDs array\n");
		(व्योम)acpi_os_delete_semaphore(मुख्य_thपढ़ो_gate);
		(व्योम)acpi_os_delete_semaphore(thपढ़ो_complete_gate);
		(व्योम)acpi_os_delete_semaphore(info_gate);
		वापस;
	पूर्ण
	स_रखो(acpi_gbl_db_method_info.thपढ़ोs, 0, size);

	/* Setup the context to be passed to each thपढ़ो */

	acpi_gbl_db_method_info.name = method_name_arg;
	acpi_gbl_db_method_info.flags = 0;
	acpi_gbl_db_method_info.num_loops = num_loops;
	acpi_gbl_db_method_info.मुख्य_thपढ़ो_gate = मुख्य_thपढ़ो_gate;
	acpi_gbl_db_method_info.thपढ़ो_complete_gate = thपढ़ो_complete_gate;
	acpi_gbl_db_method_info.info_gate = info_gate;

	/* Init arguments to be passed to method */

	acpi_gbl_db_method_info.init_args = 1;
	acpi_gbl_db_method_info.args = acpi_gbl_db_method_info.arguments;
	acpi_gbl_db_method_info.arguments[0] =
	    acpi_gbl_db_method_info.num_thपढ़ोs_str;
	acpi_gbl_db_method_info.arguments[1] =
	    acpi_gbl_db_method_info.id_of_thपढ़ो_str;
	acpi_gbl_db_method_info.arguments[2] =
	    acpi_gbl_db_method_info.index_of_thपढ़ो_str;
	acpi_gbl_db_method_info.arguments[3] = शून्य;

	acpi_gbl_db_method_info.types = acpi_gbl_db_method_info.arg_types;
	acpi_gbl_db_method_info.arg_types[0] = ACPI_TYPE_INTEGER;
	acpi_gbl_db_method_info.arg_types[1] = ACPI_TYPE_INTEGER;
	acpi_gbl_db_method_info.arg_types[2] = ACPI_TYPE_INTEGER;

	acpi_db_uपूर्णांक32_to_hex_string(num_thपढ़ोs,
				     acpi_gbl_db_method_info.num_thपढ़ोs_str);

	status = acpi_db_execute_setup(&acpi_gbl_db_method_info);
	अगर (ACPI_FAILURE(status)) अणु
		जाओ cleanup_and_निकास;
	पूर्ण

	/* Get the NS node, determines existence also */

	status = acpi_get_handle(शून्य, acpi_gbl_db_method_info.pathname,
				 &acpi_gbl_db_method_info.method);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_os_म_लिखो("%s Could not get handle for %s\n",
			       acpi_क्रमmat_exception(status),
			       acpi_gbl_db_method_info.pathname);
		जाओ cleanup_and_निकास;
	पूर्ण

	/* Create the thपढ़ोs */

	acpi_os_म_लिखो("Creating %X threads to execute %X times each\n",
		       num_thपढ़ोs, num_loops);

	क्रम (i = 0; i < (num_thपढ़ोs); i++) अणु
		status =
		    acpi_os_execute(OSL_DEBUGGER_EXEC_THREAD,
				    acpi_db_method_thपढ़ो,
				    &acpi_gbl_db_method_info);
		अगर (ACPI_FAILURE(status)) अणु
			अवरोध;
		पूर्ण
	पूर्ण

	/* Wait क्रम all thपढ़ोs to complete */

	(व्योम)acpi_os_रुको_semaphore(मुख्य_thपढ़ो_gate, 1, ACPI_WAIT_FOREVER);

	acpi_db_set_output_destination(ACPI_DB_DUPLICATE_OUTPUT);
	acpi_os_म_लिखो("All threads (%X) have completed\n", num_thपढ़ोs);
	acpi_db_set_output_destination(ACPI_DB_CONSOLE_OUTPUT);

cleanup_and_निकास:

	/* Cleanup and निकास */

	(व्योम)acpi_os_delete_semaphore(मुख्य_thपढ़ो_gate);
	(व्योम)acpi_os_delete_semaphore(thपढ़ो_complete_gate);
	(व्योम)acpi_os_delete_semaphore(info_gate);

	acpi_os_मुक्त(acpi_gbl_db_method_info.thपढ़ोs);
	acpi_gbl_db_method_info.thपढ़ोs = शून्य;
पूर्ण
