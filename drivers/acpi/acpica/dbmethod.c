<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/*******************************************************************************
 *
 * Module Name: dbmethod - Debug commands क्रम control methods
 *
 ******************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acdispat.h"
#समावेश "acnamesp.h"
#समावेश "acdebug.h"
#समावेश "acparser.h"
#समावेश "acpredef.h"

#घोषणा _COMPONENT          ACPI_CA_DEBUGGER
ACPI_MODULE_NAME("dbmethod")

/* Local prototypes */
अटल acpi_status
acpi_db_walk_क्रम_execute(acpi_handle obj_handle,
			 u32 nesting_level, व्योम *context, व्योम **वापस_value);

अटल acpi_status acpi_db_evaluate_object(काष्ठा acpi_namespace_node *node);

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_set_method_अवरोधpoपूर्णांक
 *
 * PARAMETERS:  location            - AML offset of अवरोधpoपूर्णांक
 *              walk_state          - Current walk info
 *              op                  - Current Op (from parse walk)
 *
 * RETURN:      None
 *
 * DESCRIPTION: Set a अवरोधpoपूर्णांक in a control method at the specअगरied
 *              AML offset
 *
 ******************************************************************************/

व्योम
acpi_db_set_method_अवरोधpoपूर्णांक(अक्षर *location,
			      काष्ठा acpi_walk_state *walk_state,
			      जोड़ acpi_parse_object *op)
अणु
	u32 address;
	u32 aml_offset;

	अगर (!op) अणु
		acpi_os_म_लिखो("There is no method currently executing\n");
		वापस;
	पूर्ण

	/* Get and verअगरy the अवरोधpoपूर्णांक address */

	address = म_से_अदीर्घ(location, शून्य, 16);
	aml_offset = (u32)ACPI_PTR_DIFF(op->common.aml,
					walk_state->parser_state.aml_start);
	अगर (address <= aml_offset) अणु
		acpi_os_म_लिखो("Breakpoint %X is beyond current address %X\n",
			       address, aml_offset);
	पूर्ण

	/* Save अवरोधpoपूर्णांक in current walk */

	walk_state->user_अवरोधpoपूर्णांक = address;
	acpi_os_म_लिखो("Breakpoint set at AML offset %X\n", address);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_set_method_call_अवरोधpoपूर्णांक
 *
 * PARAMETERS:  op                  - Current Op (from parse walk)
 *
 * RETURN:      None
 *
 * DESCRIPTION: Set a अवरोधpoपूर्णांक in a control method at the specअगरied
 *              AML offset
 *
 ******************************************************************************/

व्योम acpi_db_set_method_call_अवरोधpoपूर्णांक(जोड़ acpi_parse_object *op)
अणु

	अगर (!op) अणु
		acpi_os_म_लिखो("There is no method currently executing\n");
		वापस;
	पूर्ण

	acpi_gbl_step_to_next_call = TRUE;
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_set_method_data
 *
 * PARAMETERS:  type_arg        - L क्रम local, A क्रम argument
 *              index_arg       - which one
 *              value_arg       - Value to set.
 *
 * RETURN:      None
 *
 * DESCRIPTION: Set a local or argument क्रम the running control method.
 *              NOTE: only object supported is Number.
 *
 ******************************************************************************/

व्योम acpi_db_set_method_data(अक्षर *type_arg, अक्षर *index_arg, अक्षर *value_arg)
अणु
	अक्षर type;
	u32 index;
	u32 value;
	काष्ठा acpi_walk_state *walk_state;
	जोड़ acpi_opeअक्रम_object *obj_desc;
	acpi_status status;
	काष्ठा acpi_namespace_node *node;

	/* Validate type_arg */

	acpi_ut_strupr(type_arg);
	type = type_arg[0];
	अगर ((type != 'L') && (type != 'A') && (type != 'N')) अणु
		acpi_os_म_लिखो("Invalid SET operand: %s\n", type_arg);
		वापस;
	पूर्ण

	value = म_से_अदीर्घ(value_arg, शून्य, 16);

	अगर (type == 'N') अणु
		node = acpi_db_convert_to_node(index_arg);
		अगर (!node) अणु
			वापस;
		पूर्ण

		अगर (node->type != ACPI_TYPE_INTEGER) अणु
			acpi_os_म_लिखो("Can only set Integer nodes\n");
			वापस;
		पूर्ण
		obj_desc = node->object;
		obj_desc->पूर्णांकeger.value = value;
		वापस;
	पूर्ण

	/* Get the index and value */

	index = म_से_अदीर्घ(index_arg, शून्य, 16);

	walk_state = acpi_ds_get_current_walk_state(acpi_gbl_current_walk_list);
	अगर (!walk_state) अणु
		acpi_os_म_लिखो("There is no method currently executing\n");
		वापस;
	पूर्ण

	/* Create and initialize the new object */

	obj_desc = acpi_ut_create_पूर्णांकeger_object((u64)value);
	अगर (!obj_desc) अणु
		acpi_os_म_लिखो("Could not create an internal object\n");
		वापस;
	पूर्ण

	/* Store the new object पूर्णांकo the target */

	चयन (type) अणु
	हाल 'A':

		/* Set a method argument */

		अगर (index > ACPI_METHOD_MAX_ARG) अणु
			acpi_os_म_लिखो("Arg%u - Invalid argument name\n",
				       index);
			जाओ cleanup;
		पूर्ण

		status = acpi_ds_store_object_to_local(ACPI_REFCLASS_ARG,
						       index, obj_desc,
						       walk_state);
		अगर (ACPI_FAILURE(status)) अणु
			जाओ cleanup;
		पूर्ण

		obj_desc = walk_state->arguments[index].object;

		acpi_os_म_लिखो("Arg%u: ", index);
		acpi_db_display_पूर्णांकernal_object(obj_desc, walk_state);
		अवरोध;

	हाल 'L':

		/* Set a method local */

		अगर (index > ACPI_METHOD_MAX_LOCAL) अणु
			acpi_os_म_लिखो
			    ("Local%u - Invalid local variable name\n", index);
			जाओ cleanup;
		पूर्ण

		status = acpi_ds_store_object_to_local(ACPI_REFCLASS_LOCAL,
						       index, obj_desc,
						       walk_state);
		अगर (ACPI_FAILURE(status)) अणु
			जाओ cleanup;
		पूर्ण

		obj_desc = walk_state->local_variables[index].object;

		acpi_os_म_लिखो("Local%u: ", index);
		acpi_db_display_पूर्णांकernal_object(obj_desc, walk_state);
		अवरोध;

	शेष:

		अवरोध;
	पूर्ण

cleanup:
	acpi_ut_हटाओ_reference(obj_desc);
पूर्ण

#अगर_घोषित ACPI_DISASSEMBLER
/*******************************************************************************
 *
 * FUNCTION:    acpi_db_disassemble_aml
 *
 * PARAMETERS:  statements          - Number of statements to disassemble
 *              op                  - Current Op (from parse walk)
 *
 * RETURN:      None
 *
 * DESCRIPTION: Display disassembled AML (ASL) starting from Op क्रम the number
 *              of statements specअगरied.
 *
 ******************************************************************************/

व्योम acpi_db_disassemble_aml(अक्षर *statements, जोड़ acpi_parse_object *op)
अणु
	u32 num_statements = 8;

	अगर (!op) अणु
		acpi_os_म_लिखो("There is no method currently executing\n");
		वापस;
	पूर्ण

	अगर (statements) अणु
		num_statements = म_से_अदीर्घ(statements, शून्य, 0);
	पूर्ण

	acpi_dm_disassemble(शून्य, op, num_statements);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_disassemble_method
 *
 * PARAMETERS:  name            - Name of control method
 *
 * RETURN:      None
 *
 * DESCRIPTION: Display disassembled AML (ASL) starting from Op क्रम the number
 *              of statements specअगरied.
 *
 ******************************************************************************/

acpi_status acpi_db_disassemble_method(अक्षर *name)
अणु
	acpi_status status;
	जोड़ acpi_parse_object *op;
	काष्ठा acpi_walk_state *walk_state;
	जोड़ acpi_opeअक्रम_object *obj_desc;
	काष्ठा acpi_namespace_node *method;

	method = acpi_db_convert_to_node(name);
	अगर (!method) अणु
		वापस (AE_BAD_PARAMETER);
	पूर्ण

	अगर (method->type != ACPI_TYPE_METHOD) अणु
		ACPI_ERROR((AE_INFO, "%s (%s): Object must be a control method",
			    name, acpi_ut_get_type_name(method->type)));
		वापस (AE_BAD_PARAMETER);
	पूर्ण

	obj_desc = method->object;

	op = acpi_ps_create_scope_op(obj_desc->method.aml_start);
	अगर (!op) अणु
		वापस (AE_NO_MEMORY);
	पूर्ण

	/* Create and initialize a new walk state */

	walk_state = acpi_ds_create_walk_state(0, op, शून्य, शून्य);
	अगर (!walk_state) अणु
		वापस (AE_NO_MEMORY);
	पूर्ण

	status = acpi_ds_init_aml_walk(walk_state, op, शून्य,
				       obj_desc->method.aml_start,
				       obj_desc->method.aml_length, शून्य,
				       ACPI_IMODE_LOAD_PASS1);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	status = acpi_ut_allocate_owner_id(&obj_desc->method.owner_id);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	walk_state->owner_id = obj_desc->method.owner_id;

	/* Push start scope on scope stack and make it current */

	status = acpi_ds_scope_stack_push(method, method->type, walk_state);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	/* Parse the entire method AML including deferred चालकs */

	walk_state->parse_flags &= ~ACPI_PARSE_DELETE_TREE;
	walk_state->parse_flags |= ACPI_PARSE_DISASSEMBLE;

	status = acpi_ps_parse_aml(walk_state);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	(व्योम)acpi_dm_parse_deferred_ops(op);

	/* Now we can disassemble the method */

	acpi_gbl_dm_opt_verbose = FALSE;
	acpi_dm_disassemble(शून्य, op, 0);
	acpi_gbl_dm_opt_verbose = TRUE;

	acpi_ps_delete_parse_tree(op);

	/* Method cleanup */

	acpi_ns_delete_namespace_subtree(method);
	acpi_ns_delete_namespace_by_owner(obj_desc->method.owner_id);
	acpi_ut_release_owner_id(&obj_desc->method.owner_id);
	वापस (AE_OK);
पूर्ण
#पूर्ण_अगर

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_evaluate_object
 *
 * PARAMETERS:  node                - Namespace node क्रम the object
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Main execution function क्रम the Evaluate/Execute/All debugger
 *              commands.
 *
 ******************************************************************************/

अटल acpi_status acpi_db_evaluate_object(काष्ठा acpi_namespace_node *node)
अणु
	अक्षर *pathname;
	u32 i;
	काष्ठा acpi_device_info *obj_info;
	काष्ठा acpi_object_list param_objects;
	जोड़ acpi_object params[ACPI_METHOD_NUM_ARGS];
	काष्ठा acpi_buffer वापस_obj;
	acpi_status status;

	pathname = acpi_ns_get_बाह्यal_pathname(node);
	अगर (!pathname) अणु
		वापस (AE_OK);
	पूर्ण

	/* Get the object info क्रम number of method parameters */

	status = acpi_get_object_info(node, &obj_info);
	अगर (ACPI_FAILURE(status)) अणु
		ACPI_FREE(pathname);
		वापस (status);
	पूर्ण

	param_objects.poपूर्णांकer = शून्य;
	param_objects.count = 0;

	अगर (obj_info->type == ACPI_TYPE_METHOD) अणु

		/* Setup शेष parameters */

		क्रम (i = 0; i < obj_info->param_count; i++) अणु
			params[i].type = ACPI_TYPE_INTEGER;
			params[i].पूर्णांकeger.value = 1;
		पूर्ण

		param_objects.poपूर्णांकer = params;
		param_objects.count = obj_info->param_count;
	पूर्ण

	ACPI_FREE(obj_info);
	वापस_obj.poपूर्णांकer = शून्य;
	वापस_obj.length = ACPI_ALLOCATE_BUFFER;

	/* Do the actual method execution */

	acpi_gbl_method_executing = TRUE;

	status = acpi_evaluate_object(node, शून्य, &param_objects, &वापस_obj);
	acpi_gbl_method_executing = FALSE;

	acpi_os_म_लिखो("%-32s returned %s\n", pathname,
		       acpi_क्रमmat_exception(status));
	अगर (वापस_obj.length) अणु
		acpi_os_म_लिखो("Evaluation of %s returned object %p, "
			       "external buffer length %X\n",
			       pathname, वापस_obj.poपूर्णांकer,
			       (u32)वापस_obj.length);

		acpi_db_dump_बाह्यal_object(वापस_obj.poपूर्णांकer, 1);
		acpi_os_म_लिखो("\n");
	पूर्ण

	ACPI_FREE(pathname);

	/* Ignore status from method execution */

	वापस (AE_OK);

	/* Update count, check अगर we have executed enough methods */

पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_walk_क्रम_execute
 *
 * PARAMETERS:  Callback from walk_namespace
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Batch execution function. Evaluates all "predefined" objects --
 *              the nameseg begins with an underscore.
 *
 ******************************************************************************/

अटल acpi_status
acpi_db_walk_क्रम_execute(acpi_handle obj_handle,
			 u32 nesting_level, व्योम *context, व्योम **वापस_value)
अणु
	काष्ठा acpi_namespace_node *node =
	    (काष्ठा acpi_namespace_node *)obj_handle;
	काष्ठा acpi_db_execute_walk *info =
	    (काष्ठा acpi_db_execute_walk *)context;
	acpi_status status;
	स्थिर जोड़ acpi_predefined_info *predefined;

	predefined = acpi_ut_match_predefined_method(node->name.ascii);
	अगर (!predefined) अणु
		वापस (AE_OK);
	पूर्ण

	अगर (node->type == ACPI_TYPE_LOCAL_SCOPE) अणु
		वापस (AE_OK);
	पूर्ण

	acpi_db_evaluate_object(node);

	/* Ignore status from object evaluation */

	status = AE_OK;

	/* Update count, check अगर we have executed enough methods */

	info->count++;
	अगर (info->count >= info->max_count) अणु
		status = AE_CTRL_TERMINATE;
	पूर्ण

	वापस (status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_walk_क्रम_execute_all
 *
 * PARAMETERS:  Callback from walk_namespace
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Batch execution function. Evaluates all objects whose path ends
 *              with the nameseg "Info->NameSeg". Used क्रम the "ALL" command.
 *
 ******************************************************************************/

अटल acpi_status
acpi_db_walk_क्रम_execute_all(acpi_handle obj_handle,
			     u32 nesting_level,
			     व्योम *context, व्योम **वापस_value)
अणु
	काष्ठा acpi_namespace_node *node =
	    (काष्ठा acpi_namespace_node *)obj_handle;
	काष्ठा acpi_db_execute_walk *info =
	    (काष्ठा acpi_db_execute_walk *)context;
	acpi_status status;

	अगर (!ACPI_COMPARE_NAMESEG(node->name.ascii, info->name_seg)) अणु
		वापस (AE_OK);
	पूर्ण

	अगर (node->type == ACPI_TYPE_LOCAL_SCOPE) अणु
		वापस (AE_OK);
	पूर्ण

	/* Now evaluate the input object (node) */

	acpi_db_evaluate_object(node);

	/* Ignore status from method execution */

	status = AE_OK;

	/* Update count of executed methods/objects */

	info->count++;
	वापस (status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_evaluate_predefined_names
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: Namespace batch execution. Execute predefined names in the
 *              namespace, up to the max count, अगर specअगरied.
 *
 ******************************************************************************/

व्योम acpi_db_evaluate_predefined_names(व्योम)
अणु
	काष्ठा acpi_db_execute_walk info;

	info.count = 0;
	info.max_count = ACPI_UINT32_MAX;

	/* Search all nodes in namespace */

	(व्योम)acpi_walk_namespace(ACPI_TYPE_ANY, ACPI_ROOT_OBJECT,
				  ACPI_UINT32_MAX, acpi_db_walk_क्रम_execute,
				  शून्य, (व्योम *)&info, शून्य);

	acpi_os_म_लिखो("Evaluated %u predefined names in the namespace\n",
		       info.count);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_evaluate_all
 *
 * PARAMETERS:  none_acpi_gbl_db_method_info
 *
 * RETURN:      None
 *
 * DESCRIPTION: Namespace batch execution. Implements the "ALL" command.
 *              Execute all namepaths whose final nameseg matches the
 *              input nameseg.
 *
 ******************************************************************************/

व्योम acpi_db_evaluate_all(अक्षर *name_seg)
अणु
	काष्ठा acpi_db_execute_walk info;

	info.count = 0;
	info.max_count = ACPI_UINT32_MAX;
	ACPI_COPY_NAMESEG(info.name_seg, name_seg);
	info.name_seg[ACPI_NAMESEG_SIZE] = 0;

	/* Search all nodes in namespace */

	(व्योम)acpi_walk_namespace(ACPI_TYPE_ANY, ACPI_ROOT_OBJECT,
				  ACPI_UINT32_MAX, acpi_db_walk_क्रम_execute_all,
				  शून्य, (व्योम *)&info, शून्य);

	acpi_os_म_लिखो("Evaluated %u names in the namespace\n", info.count);
पूर्ण
