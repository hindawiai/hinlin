<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/*******************************************************************************
 *
 * Module Name: dbxface - AML Debugger बाह्यal पूर्णांकerfaces
 *
 ******************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "amlcode.h"
#समावेश "acdebug.h"
#समावेश "acinterp.h"
#समावेश "acparser.h"

#घोषणा _COMPONENT          ACPI_CA_DEBUGGER
ACPI_MODULE_NAME("dbxface")

/* Local prototypes */
अटल acpi_status
acpi_db_start_command(काष्ठा acpi_walk_state *walk_state,
		      जोड़ acpi_parse_object *op);

#अगर_घोषित ACPI_OBSOLETE_FUNCTIONS
व्योम acpi_db_method_end(काष्ठा acpi_walk_state *walk_state);
#पूर्ण_अगर

#अगर_घोषित ACPI_DISASSEMBLER
अटल जोड़ acpi_parse_object *acpi_db_get_display_op(काष्ठा acpi_walk_state
						       *walk_state,
						       जोड़ acpi_parse_object
						       *op);
#पूर्ण_अगर

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_start_command
 *
 * PARAMETERS:  walk_state      - Current walk
 *              op              - Current executing Op, from AML पूर्णांकerpreter
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Enter debugger command loop
 *
 ******************************************************************************/

अटल acpi_status
acpi_db_start_command(काष्ठा acpi_walk_state *walk_state,
		      जोड़ acpi_parse_object *op)
अणु
	acpi_status status;

	/* TBD: [Investigate] are there namespace locking issues here? */

	/* acpi_ut_release_mutex (ACPI_MTX_NAMESPACE); */

	/* Go पूर्णांकo the command loop and aरुको next user command */

	acpi_gbl_method_executing = TRUE;
	status = AE_CTRL_TRUE;

	जबतक (status == AE_CTRL_TRUE) अणु

		/* Notअगरy the completion of the command */

		status = acpi_os_notअगरy_command_complete();
		अगर (ACPI_FAILURE(status)) अणु
			जाओ error_निकास;
		पूर्ण

		/* Wait the पढ़ोiness of the command */

		status = acpi_os_रुको_command_पढ़ोy();
		अगर (ACPI_FAILURE(status)) अणु
			जाओ error_निकास;
		पूर्ण

		status =
		    acpi_db_command_dispatch(acpi_gbl_db_line_buf, walk_state,
					     op);
	पूर्ण

	/* acpi_ut_acquire_mutex (ACPI_MTX_NAMESPACE); */

error_निकास:
	अगर (ACPI_FAILURE(status) && status != AE_CTRL_TERMINATE) अणु
		ACPI_EXCEPTION((AE_INFO, status,
				"While parsing/handling command line"));
	पूर्ण
	वापस (status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_संकेत_अवरोध_poपूर्णांक
 *
 * PARAMETERS:  walk_state      - Current walk
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Called क्रम AML_BREAKPOINT_OP
 *
 ******************************************************************************/

व्योम acpi_db_संकेत_अवरोध_poपूर्णांक(काष्ठा acpi_walk_state *walk_state)
अणु

#अगर_अघोषित ACPI_APPLICATION
	अगर (acpi_gbl_db_thपढ़ो_id != acpi_os_get_thपढ़ो_id()) अणु
		वापस;
	पूर्ण
#पूर्ण_अगर

	/*
	 * Set the single-step flag. This will cause the debugger (अगर present)
	 * to अवरोध to the console within the AML debugger at the start of the
	 * next AML inकाष्ठाion.
	 */
	acpi_gbl_cm_single_step = TRUE;
	acpi_os_म_लिखो("**break** Executed AML BreakPoint opcode\n");
पूर्ण

#अगर_घोषित ACPI_DISASSEMBLER
/*******************************************************************************
 *
 * FUNCTION:    acpi_db_get_display_op
 *
 * PARAMETERS:  walk_state      - Current walk
 *              op              - Current executing op (from aml पूर्णांकerpreter)
 *
 * RETURN:      Opcode to display
 *
 * DESCRIPTION: Find the opcode to display during single stepping
 *
 ******************************************************************************/

अटल जोड़ acpi_parse_object *acpi_db_get_display_op(काष्ठा acpi_walk_state
						       *walk_state,
						       जोड़ acpi_parse_object
						       *op)
अणु
	जोड़ acpi_parse_object *display_op;
	जोड़ acpi_parse_object *parent_op;

	display_op = op;
	parent_op = op->common.parent;
	अगर (parent_op) अणु
		अगर ((walk_state->control_state) &&
		    (walk_state->control_state->common.state ==
		     ACPI_CONTROL_PREDICATE_EXECUTING)) अणु
			/*
			 * We are executing the predicate of an IF or WHILE statement
			 * Search upwards क्रम the containing IF or WHILE so that the
			 * entire predicate can be displayed.
			 */
			जबतक (parent_op) अणु
				अगर ((parent_op->common.aml_opcode == AML_IF_OP)
				    || (parent_op->common.aml_opcode ==
					AML_WHILE_OP)) अणु
					display_op = parent_op;
					अवरोध;
				पूर्ण
				parent_op = parent_op->common.parent;
			पूर्ण
		पूर्ण अन्यथा अणु
			जबतक (parent_op) अणु
				अगर ((parent_op->common.aml_opcode == AML_IF_OP)
				    || (parent_op->common.aml_opcode ==
					AML_ELSE_OP)
				    || (parent_op->common.aml_opcode ==
					AML_SCOPE_OP)
				    || (parent_op->common.aml_opcode ==
					AML_METHOD_OP)
				    || (parent_op->common.aml_opcode ==
					AML_WHILE_OP)) अणु
					अवरोध;
				पूर्ण
				display_op = parent_op;
				parent_op = parent_op->common.parent;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस display_op;
पूर्ण
#पूर्ण_अगर

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_single_step
 *
 * PARAMETERS:  walk_state      - Current walk
 *              op              - Current executing op (from aml पूर्णांकerpreter)
 *              opcode_class    - Class of the current AML Opcode
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Called just beक्रमe execution of an AML opcode.
 *
 ******************************************************************************/

acpi_status
acpi_db_single_step(काष्ठा acpi_walk_state *walk_state,
		    जोड़ acpi_parse_object *op, u32 opcode_class)
अणु
	जोड़ acpi_parse_object *next;
	acpi_status status = AE_OK;
	u32 original_debug_level;
	u32 aml_offset;

	ACPI_FUNCTION_ENTRY();

#अगर_अघोषित ACPI_APPLICATION
	अगर (acpi_gbl_db_thपढ़ो_id != acpi_os_get_thपढ़ो_id()) अणु
		वापस (AE_OK);
	पूर्ण
#पूर्ण_अगर

	/* Check the पात flag */

	अगर (acpi_gbl_पात_method) अणु
		acpi_gbl_पात_method = FALSE;
		वापस (AE_ABORT_METHOD);
	पूर्ण

	aml_offset = (u32)ACPI_PTR_DIFF(op->common.aml,
					walk_state->parser_state.aml_start);

	/* Check क्रम single-step अवरोधpoपूर्णांक */

	अगर (walk_state->method_अवरोधpoपूर्णांक &&
	    (walk_state->method_अवरोधpoपूर्णांक <= aml_offset)) अणु

		/* Check अगर the अवरोधpoपूर्णांक has been reached or passed */
		/* Hit the अवरोधpoपूर्णांक, resume single step, reset अवरोधpoपूर्णांक */

		acpi_os_म_लिखो("***Break*** at AML offset %X\n", aml_offset);
		acpi_gbl_cm_single_step = TRUE;
		acpi_gbl_step_to_next_call = FALSE;
		walk_state->method_अवरोधpoपूर्णांक = 0;
	पूर्ण

	/* Check क्रम user अवरोधpoपूर्णांक (Must be on exact Aml offset) */

	अन्यथा अगर (walk_state->user_अवरोधpoपूर्णांक &&
		 (walk_state->user_अवरोधpoपूर्णांक == aml_offset)) अणु
		acpi_os_म_लिखो("***UserBreakpoint*** at AML offset %X\n",
			       aml_offset);
		acpi_gbl_cm_single_step = TRUE;
		acpi_gbl_step_to_next_call = FALSE;
		walk_state->method_अवरोधpoपूर्णांक = 0;
	पूर्ण

	/*
	 * Check अगर this is an opcode that we are पूर्णांकerested in --
	 * namely, opcodes that have arguments
	 */
	अगर (op->common.aml_opcode == AML_INT_NAMEDFIELD_OP) अणु
		वापस (AE_OK);
	पूर्ण

	चयन (opcode_class) अणु
	हाल AML_CLASS_UNKNOWN:
	हाल AML_CLASS_ARGUMENT:	/* स्थिरants, literals, etc. करो nothing */

		वापस (AE_OK);

	शेष:

		/* All other opcodes -- जारी */
		अवरोध;
	पूर्ण

	/*
	 * Under certain debug conditions, display this opcode and its opeअक्रमs
	 */
	अगर ((acpi_gbl_db_output_to_file) ||
	    (acpi_gbl_cm_single_step) || (acpi_dbg_level & ACPI_LV_PARSE)) अणु
		अगर ((acpi_gbl_db_output_to_file) ||
		    (acpi_dbg_level & ACPI_LV_PARSE)) अणु
			acpi_os_म_लिखो
			    ("\nAML Debug: Next AML Opcode to execute:\n");
		पूर्ण

		/*
		 * Display this op (and only this op - zero out the NEXT field
		 * temporarily, and disable parser trace output क्रम the duration of
		 * the display because we करोn't want the extraneous debug output)
		 */
		original_debug_level = acpi_dbg_level;
		acpi_dbg_level &= ~(ACPI_LV_PARSE | ACPI_LV_FUNCTIONS);
		next = op->common.next;
		op->common.next = शून्य;

		/* Now we can disassemble and display it */

#अगर_घोषित ACPI_DISASSEMBLER
		acpi_dm_disassemble(walk_state,
				    acpi_db_get_display_op(walk_state, op),
				    ACPI_UINT32_MAX);
#अन्यथा
		/*
		 * The AML Disassembler is not configured - at least we can
		 * display the opcode value and name
		 */
		acpi_os_म_लिखो("AML Opcode: %4.4X %s\n", op->common.aml_opcode,
			       acpi_ps_get_opcode_name(op->common.aml_opcode));
#पूर्ण_अगर

		अगर ((op->common.aml_opcode == AML_IF_OP) ||
		    (op->common.aml_opcode == AML_WHILE_OP)) अणु
			अगर (walk_state->control_state->common.value) अणु
				acpi_os_म_लिखो
				    ("Predicate = [True], IF block was executed\n");
			पूर्ण अन्यथा अणु
				acpi_os_म_लिखो
				    ("Predicate = [False], Skipping IF block\n");
			पूर्ण
		पूर्ण अन्यथा अगर (op->common.aml_opcode == AML_ELSE_OP) अणु
			acpi_os_म_लिखो
			    ("Predicate = [False], ELSE block was executed\n");
		पूर्ण

		/* Restore everything */

		op->common.next = next;
		acpi_os_म_लिखो("\n");
		अगर ((acpi_gbl_db_output_to_file) ||
		    (acpi_dbg_level & ACPI_LV_PARSE)) अणु
			acpi_os_म_लिखो("\n");
		पूर्ण
		acpi_dbg_level = original_debug_level;
	पूर्ण

	/* If we are not single stepping, just जारी executing the method */

	अगर (!acpi_gbl_cm_single_step) अणु
		वापस (AE_OK);
	पूर्ण

	/*
	 * If we are executing a step-to-call command,
	 * Check अगर this is a method call.
	 */
	अगर (acpi_gbl_step_to_next_call) अणु
		अगर (op->common.aml_opcode != AML_INT_METHODCALL_OP) अणु

			/* Not a method call, just keep executing */

			वापस (AE_OK);
		पूर्ण

		/* Found a method call, stop executing */

		acpi_gbl_step_to_next_call = FALSE;
	पूर्ण

	/*
	 * If the next opcode is a method call, we will "step over" it
	 * by शेष.
	 */
	अगर (op->common.aml_opcode == AML_INT_METHODCALL_OP) अणु

		/* Force no more single stepping जबतक executing called method */

		acpi_gbl_cm_single_step = FALSE;

		/*
		 * Set the अवरोधpoपूर्णांक on/beक्रमe the call, it will stop execution
		 * as soon as we वापस
		 */
		walk_state->method_अवरोधpoपूर्णांक = 1;	/* Must be non-zero! */
	पूर्ण

	acpi_ex_निकास_पूर्णांकerpreter();
	status = acpi_db_start_command(walk_state, op);
	acpi_ex_enter_पूर्णांकerpreter();

	/* User commands complete, जारी execution of the पूर्णांकerrupted method */

	वापस (status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_initialize_debugger
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Init and start debugger
 *
 ******************************************************************************/

acpi_status acpi_initialize_debugger(व्योम)
अणु
	acpi_status status;

	ACPI_FUNCTION_TRACE(acpi_initialize_debugger);

	/* Init globals */

	acpi_gbl_db_buffer = शून्य;
	acpi_gbl_db_filename = शून्य;
	acpi_gbl_db_output_to_file = FALSE;

	acpi_gbl_db_debug_level = ACPI_LV_VERBOSITY2;
	acpi_gbl_db_console_debug_level = ACPI_NORMAL_DEFAULT | ACPI_LV_TABLES;
	acpi_gbl_db_output_flags = ACPI_DB_CONSOLE_OUTPUT;

	acpi_gbl_db_opt_no_ini_methods = FALSE;
	acpi_gbl_db_opt_no_region_support = FALSE;

	acpi_gbl_db_buffer = acpi_os_allocate(ACPI_DEBUG_BUFFER_SIZE);
	अगर (!acpi_gbl_db_buffer) अणु
		वापस_ACPI_STATUS(AE_NO_MEMORY);
	पूर्ण
	स_रखो(acpi_gbl_db_buffer, 0, ACPI_DEBUG_BUFFER_SIZE);

	/* Initial scope is the root */

	acpi_gbl_db_scope_buf[0] = AML_ROOT_PREFIX;
	acpi_gbl_db_scope_buf[1] = 0;
	acpi_gbl_db_scope_node = acpi_gbl_root_node;

	/* Initialize user commands loop */

	acpi_gbl_db_terminate_loop = FALSE;

	/*
	 * If configured क्रम multi-thपढ़ो support, the debug executor runs in
	 * a separate thपढ़ो so that the front end can be in another address
	 * space, environment, or even another machine.
	 */
	अगर (acpi_gbl_debugger_configuration & DEBUGGER_MULTI_THREADED) अणु

		/* These were created with one unit, grab it */

		status = acpi_os_initialize_debugger();
		अगर (ACPI_FAILURE(status)) अणु
			acpi_os_म_लिखो("Could not get debugger mutex\n");
			वापस_ACPI_STATUS(status);
		पूर्ण

		/* Create the debug execution thपढ़ो to execute commands */

		acpi_gbl_db_thपढ़ोs_terminated = FALSE;
		status = acpi_os_execute(OSL_DEBUGGER_MAIN_THREAD,
					 acpi_db_execute_thपढ़ो, शून्य);
		अगर (ACPI_FAILURE(status)) अणु
			ACPI_EXCEPTION((AE_INFO, status,
					"Could not start debugger thread"));
			acpi_gbl_db_thपढ़ोs_terminated = TRUE;
			वापस_ACPI_STATUS(status);
		पूर्ण
	पूर्ण अन्यथा अणु
		acpi_gbl_db_thपढ़ो_id = acpi_os_get_thपढ़ो_id();
	पूर्ण

	वापस_ACPI_STATUS(AE_OK);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_initialize_debugger)

/*******************************************************************************
 *
 * FUNCTION:    acpi_terminate_debugger
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: Stop debugger
 *
 ******************************************************************************/
व्योम acpi_terminate_debugger(व्योम)
अणु

	/* Terminate the AML Debugger */

	acpi_gbl_db_terminate_loop = TRUE;

	अगर (acpi_gbl_debugger_configuration & DEBUGGER_MULTI_THREADED) अणु

		/* Wait the AML Debugger thपढ़ोs */

		जबतक (!acpi_gbl_db_thपढ़ोs_terminated) अणु
			acpi_os_sleep(100);
		पूर्ण

		acpi_os_terminate_debugger();
	पूर्ण

	अगर (acpi_gbl_db_buffer) अणु
		acpi_os_मुक्त(acpi_gbl_db_buffer);
		acpi_gbl_db_buffer = शून्य;
	पूर्ण

	/* Ensure that debug output is now disabled */

	acpi_gbl_db_output_flags = ACPI_DB_DISABLE_OUTPUT;
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_terminate_debugger)

/*******************************************************************************
 *
 * FUNCTION:    acpi_set_debugger_thपढ़ो_id
 *
 * PARAMETERS:  thपढ़ो_id       - Debugger thपढ़ो ID
 *
 * RETURN:      None
 *
 * DESCRIPTION: Set debugger thपढ़ो ID
 *
 ******************************************************************************/
व्योम acpi_set_debugger_thपढ़ो_id(acpi_thपढ़ो_id thपढ़ो_id)
अणु
	acpi_gbl_db_thपढ़ो_id = thपढ़ो_id;
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_set_debugger_thपढ़ो_id)
