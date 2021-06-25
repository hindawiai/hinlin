<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/*******************************************************************************
 *
 * Module Name: dbdisply - debug display commands
 *
 ******************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "amlcode.h"
#समावेश "acdispat.h"
#समावेश "acnamesp.h"
#समावेश "acparser.h"
#समावेश "acinterp.h"
#समावेश "acevents.h"
#समावेश "acdebug.h"

#घोषणा _COMPONENT          ACPI_CA_DEBUGGER
ACPI_MODULE_NAME("dbdisply")

/* Local prototypes */
अटल व्योम acpi_db_dump_parser_descriptor(जोड़ acpi_parse_object *op);

अटल व्योम *acpi_db_get_poपूर्णांकer(व्योम *target);

अटल acpi_status
acpi_db_display_non_root_handlers(acpi_handle obj_handle,
				  u32 nesting_level,
				  व्योम *context, व्योम **वापस_value);

/*
 * System handler inक्रमmation.
 * Used क्रम Handlers command, in acpi_db_display_handlers.
 */
#घोषणा ACPI_PREDEFINED_PREFIX          "%25s (%.2X) : "
#घोषणा ACPI_HANDLER_NAME_STRING               "%30s : "
#घोषणा ACPI_HANDLER_PRESENT_STRING                    "%-9s (%p)\n"
#घोषणा ACPI_HANDLER_PRESENT_STRING2                   "%-9s (%p)"
#घोषणा ACPI_HANDLER_NOT_PRESENT_STRING                "%-9s\n"

/* All predefined Address Space IDs */

अटल acpi_adr_space_type acpi_gbl_space_id_list[] = अणु
	ACPI_ADR_SPACE_SYSTEM_MEMORY,
	ACPI_ADR_SPACE_SYSTEM_IO,
	ACPI_ADR_SPACE_PCI_CONFIG,
	ACPI_ADR_SPACE_EC,
	ACPI_ADR_SPACE_SMBUS,
	ACPI_ADR_SPACE_CMOS,
	ACPI_ADR_SPACE_PCI_BAR_TARGET,
	ACPI_ADR_SPACE_IPMI,
	ACPI_ADR_SPACE_GPIO,
	ACPI_ADR_SPACE_GSBUS,
	ACPI_ADR_SPACE_PLATFORM_COMM,
	ACPI_ADR_SPACE_PLATFORM_RT,
	ACPI_ADR_SPACE_DATA_TABLE,
	ACPI_ADR_SPACE_FIXED_HARDWARE
पूर्ण;

/* Global handler inक्रमmation */

प्रकार काष्ठा acpi_handler_info अणु
	व्योम *handler;
	अक्षर *name;

पूर्ण acpi_handler_info;

अटल काष्ठा acpi_handler_info acpi_gbl_handler_list[] = अणु
	अणु&acpi_gbl_global_notअगरy[0].handler, "System Notifications"पूर्ण,
	अणु&acpi_gbl_global_notअगरy[1].handler, "Device Notifications"पूर्ण,
	अणु&acpi_gbl_table_handler, "ACPI Table Events"पूर्ण,
	अणु&acpi_gbl_exception_handler, "Control Method Exceptions"पूर्ण,
	अणु&acpi_gbl_पूर्णांकerface_handler, "OSI Invocations"पूर्ण
पूर्ण;

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_get_poपूर्णांकer
 *
 * PARAMETERS:  target          - Poपूर्णांकer to string to be converted
 *
 * RETURN:      Converted poपूर्णांकer
 *
 * DESCRIPTION: Convert an ascii poपूर्णांकer value to a real value
 *
 ******************************************************************************/

अटल व्योम *acpi_db_get_poपूर्णांकer(व्योम *target)
अणु
	व्योम *obj_ptr;
	acpi_size address;

	address = म_से_अदीर्घ(target, शून्य, 16);
	obj_ptr = ACPI_TO_POINTER(address);
	वापस (obj_ptr);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_dump_parser_descriptor
 *
 * PARAMETERS:  op              - A parser Op descriptor
 *
 * RETURN:      None
 *
 * DESCRIPTION: Display a क्रमmatted parser object
 *
 ******************************************************************************/

अटल व्योम acpi_db_dump_parser_descriptor(जोड़ acpi_parse_object *op)
अणु
	स्थिर काष्ठा acpi_opcode_info *info;

	info = acpi_ps_get_opcode_info(op->common.aml_opcode);

	acpi_os_म_लिखो("Parser Op Descriptor:\n");
	acpi_os_म_लिखो("%20.20s : %4.4X\n", "Opcode", op->common.aml_opcode);

	ACPI_DEBUG_ONLY_MEMBERS(acpi_os_म_लिखो("%20.20s : %s\n", "Opcode Name",
					       info->name));

	acpi_os_म_लिखो("%20.20s : %p\n", "Value/ArgList", op->common.value.arg);
	acpi_os_म_लिखो("%20.20s : %p\n", "Parent", op->common.parent);
	acpi_os_म_लिखो("%20.20s : %p\n", "NextOp", op->common.next);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_decode_and_display_object
 *
 * PARAMETERS:  target          - String with object to be displayed. Names
 *                                and hex poपूर्णांकers are supported.
 *              output_type     - Byte, Word, Dword, or Qword (B|W|D|Q)
 *
 * RETURN:      None
 *
 * DESCRIPTION: Display a क्रमmatted ACPI object
 *
 ******************************************************************************/

व्योम acpi_db_decode_and_display_object(अक्षर *target, अक्षर *output_type)
अणु
	व्योम *obj_ptr;
	काष्ठा acpi_namespace_node *node;
	जोड़ acpi_opeअक्रम_object *obj_desc;
	u32 display = DB_BYTE_DISPLAY;
	अक्षर buffer[80];
	काष्ठा acpi_buffer ret_buf;
	acpi_status status;
	u32 size;

	अगर (!target) अणु
		वापस;
	पूर्ण

	/* Decode the output type */

	अगर (output_type) अणु
		acpi_ut_strupr(output_type);
		अगर (output_type[0] == 'W') अणु
			display = DB_WORD_DISPLAY;
		पूर्ण अन्यथा अगर (output_type[0] == 'D') अणु
			display = DB_DWORD_DISPLAY;
		पूर्ण अन्यथा अगर (output_type[0] == 'Q') अणु
			display = DB_QWORD_DISPLAY;
		पूर्ण
	पूर्ण

	ret_buf.length = माप(buffer);
	ret_buf.poपूर्णांकer = buffer;

	/* Dअगरferentiate between a number and a name */

	अगर ((target[0] >= 0x30) && (target[0] <= 0x39)) अणु
		obj_ptr = acpi_db_get_poपूर्णांकer(target);
		अगर (!acpi_os_पढ़ोable(obj_ptr, 16)) अणु
			acpi_os_म_लिखो
			    ("Address %p is invalid in this address space\n",
			     obj_ptr);
			वापस;
		पूर्ण

		/* Decode the object type */

		चयन (ACPI_GET_DESCRIPTOR_TYPE(obj_ptr)) अणु
		हाल ACPI_DESC_TYPE_NAMED:

			/* This is a namespace Node */

			अगर (!acpi_os_पढ़ोable
			    (obj_ptr, माप(काष्ठा acpi_namespace_node))) अणु
				acpi_os_म_लिखो
				    ("Cannot read entire Named object at address %p\n",
				     obj_ptr);
				वापस;
			पूर्ण

			node = obj_ptr;
			जाओ dump_node;

		हाल ACPI_DESC_TYPE_OPERAND:

			/* This is a ACPI OPERAND OBJECT */

			अगर (!acpi_os_पढ़ोable
			    (obj_ptr, माप(जोड़ acpi_opeअक्रम_object))) अणु
				acpi_os_म_लिखो
				    ("Cannot read entire ACPI object at address %p\n",
				     obj_ptr);
				वापस;
			पूर्ण

			acpi_ut_debug_dump_buffer(obj_ptr,
						  माप(जोड़
							 acpi_opeअक्रम_object),
						  display, ACPI_UINT32_MAX);
			acpi_ex_dump_object_descriptor(obj_ptr, 1);
			अवरोध;

		हाल ACPI_DESC_TYPE_PARSER:

			/* This is a Parser Op object */

			अगर (!acpi_os_पढ़ोable
			    (obj_ptr, माप(जोड़ acpi_parse_object))) अणु
				acpi_os_म_लिखो
				    ("Cannot read entire Parser object at address %p\n",
				     obj_ptr);
				वापस;
			पूर्ण

			acpi_ut_debug_dump_buffer(obj_ptr,
						  माप(जोड़
							 acpi_parse_object),
						  display, ACPI_UINT32_MAX);
			acpi_db_dump_parser_descriptor((जोड़ acpi_parse_object
							*)obj_ptr);
			अवरोध;

		शेष:

			/* Is not a recognizable object */

			acpi_os_म_लिखो
			    ("Not a known ACPI internal object, descriptor type %2.2X\n",
			     ACPI_GET_DESCRIPTOR_TYPE(obj_ptr));

			size = 16;
			अगर (acpi_os_पढ़ोable(obj_ptr, 64)) अणु
				size = 64;
			पूर्ण

			/* Just dump some memory */

			acpi_ut_debug_dump_buffer(obj_ptr, size, display,
						  ACPI_UINT32_MAX);
			अवरोध;
		पूर्ण

		वापस;
	पूर्ण

	/* The parameter is a name string that must be resolved to a Named obj */

	node = acpi_db_local_ns_lookup(target);
	अगर (!node) अणु
		वापस;
	पूर्ण

dump_node:
	/* Now dump the NS node */

	status = acpi_get_name(node, ACPI_FULL_PATHNAME_NO_TRAILING, &ret_buf);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_os_म_लिखो("Could not convert name to pathname\n");
	पूर्ण

	अन्यथा अणु
		acpi_os_म_लिखो("Object %p: Namespace Node - Pathname: %s\n",
			       node, (अक्षर *)ret_buf.poपूर्णांकer);
	पूर्ण

	अगर (!acpi_os_पढ़ोable(node, माप(काष्ठा acpi_namespace_node))) अणु
		acpi_os_म_लिखो("Invalid Named object at address %p\n", node);
		वापस;
	पूर्ण

	acpi_ut_debug_dump_buffer((व्योम *)node,
				  माप(काष्ठा acpi_namespace_node), display,
				  ACPI_UINT32_MAX);
	acpi_ex_dump_namespace_node(node, 1);

	obj_desc = acpi_ns_get_attached_object(node);
	अगर (obj_desc) अणु
		acpi_os_म_लिखो("\nAttached Object %p:", obj_desc);
		अगर (!acpi_os_पढ़ोable
		    (obj_desc, माप(जोड़ acpi_opeअक्रम_object))) अणु
			acpi_os_म_लिखो
			    ("Invalid internal ACPI Object at address %p\n",
			     obj_desc);
			वापस;
		पूर्ण

		अगर (ACPI_GET_DESCRIPTOR_TYPE(((काष्ठा acpi_namespace_node *)
					      obj_desc)) ==
		    ACPI_DESC_TYPE_NAMED) अणु
			acpi_os_म_लिखो(" Namespace Node - ");
			status =
			    acpi_get_name((काष्ठा acpi_namespace_node *)
					  obj_desc,
					  ACPI_FULL_PATHNAME_NO_TRAILING,
					  &ret_buf);
			अगर (ACPI_FAILURE(status)) अणु
				acpi_os_म_लिखो
				    ("Could not convert name to pathname\n");
			पूर्ण अन्यथा अणु
				acpi_os_म_लिखो("Pathname: %s",
					       (अक्षर *)ret_buf.poपूर्णांकer);
			पूर्ण

			acpi_os_म_लिखो("\n");
			acpi_ut_debug_dump_buffer((व्योम *)obj_desc,
						  माप(काष्ठा
							 acpi_namespace_node),
						  display, ACPI_UINT32_MAX);
		पूर्ण अन्यथा अणु
			acpi_os_म_लिखो("\n");
			acpi_ut_debug_dump_buffer((व्योम *)obj_desc,
						  माप(जोड़
							 acpi_opeअक्रम_object),
						  display, ACPI_UINT32_MAX);
		पूर्ण

		acpi_ex_dump_object_descriptor(obj_desc, 1);
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_display_method_info
 *
 * PARAMETERS:  start_op        - Root of the control method parse tree
 *
 * RETURN:      None
 *
 * DESCRIPTION: Display inक्रमmation about the current method
 *
 ******************************************************************************/

व्योम acpi_db_display_method_info(जोड़ acpi_parse_object *start_op)
अणु
	काष्ठा acpi_walk_state *walk_state;
	जोड़ acpi_opeअक्रम_object *obj_desc;
	काष्ठा acpi_namespace_node *node;
	जोड़ acpi_parse_object *root_op;
	जोड़ acpi_parse_object *op;
	स्थिर काष्ठा acpi_opcode_info *op_info;
	u32 num_ops = 0;
	u32 num_opeअक्रमs = 0;
	u32 num_चालकs = 0;
	u32 num_reमुख्यing_ops = 0;
	u32 num_reमुख्यing_opeअक्रमs = 0;
	u32 num_reमुख्यing_चालकs = 0;
	u8 count_reमुख्यing = FALSE;

	walk_state = acpi_ds_get_current_walk_state(acpi_gbl_current_walk_list);
	अगर (!walk_state) अणु
		acpi_os_म_लिखो("There is no method currently executing\n");
		वापस;
	पूर्ण

	obj_desc = walk_state->method_desc;
	node = walk_state->method_node;

	acpi_os_म_लिखो("Currently executing control method is [%4.4s]\n",
		       acpi_ut_get_node_name(node));
	acpi_os_म_लिखो("%X Arguments, SyncLevel = %X\n",
		       (u32)obj_desc->method.param_count,
		       (u32)obj_desc->method.sync_level);

	root_op = start_op;
	जबतक (root_op->common.parent) अणु
		root_op = root_op->common.parent;
	पूर्ण

	op = root_op;

	जबतक (op) अणु
		अगर (op == start_op) अणु
			count_reमुख्यing = TRUE;
		पूर्ण

		num_ops++;
		अगर (count_reमुख्यing) अणु
			num_reमुख्यing_ops++;
		पूर्ण

		/* Decode the opcode */

		op_info = acpi_ps_get_opcode_info(op->common.aml_opcode);
		चयन (op_info->class) अणु
		हाल AML_CLASS_ARGUMENT:

			अगर (count_reमुख्यing) अणु
				num_reमुख्यing_opeअक्रमs++;
			पूर्ण

			num_opeअक्रमs++;
			अवरोध;

		हाल AML_CLASS_UNKNOWN:

			/* Bad opcode or ASCII अक्षरacter */

			जारी;

		शेष:

			अगर (count_reमुख्यing) अणु
				num_reमुख्यing_चालकs++;
			पूर्ण

			num_चालकs++;
			अवरोध;
		पूर्ण

		op = acpi_ps_get_depth_next(start_op, op);
	पूर्ण

	acpi_os_म_लिखो
	    ("Method contains:       %X AML Opcodes - %X Operators, %X Operands\n",
	     num_ops, num_चालकs, num_opeअक्रमs);

	acpi_os_म_लिखो
	    ("Remaining to execute:  %X AML Opcodes - %X Operators, %X Operands\n",
	     num_reमुख्यing_ops, num_reमुख्यing_चालकs,
	     num_reमुख्यing_opeअक्रमs);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_display_locals
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: Display all locals क्रम the currently running control method
 *
 ******************************************************************************/

व्योम acpi_db_display_locals(व्योम)
अणु
	काष्ठा acpi_walk_state *walk_state;

	walk_state = acpi_ds_get_current_walk_state(acpi_gbl_current_walk_list);
	अगर (!walk_state) अणु
		acpi_os_म_लिखो("There is no method currently executing\n");
		वापस;
	पूर्ण

	acpi_db_decode_locals(walk_state);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_display_arguments
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: Display all arguments क्रम the currently running control method
 *
 ******************************************************************************/

व्योम acpi_db_display_arguments(व्योम)
अणु
	काष्ठा acpi_walk_state *walk_state;

	walk_state = acpi_ds_get_current_walk_state(acpi_gbl_current_walk_list);
	अगर (!walk_state) अणु
		acpi_os_म_लिखो("There is no method currently executing\n");
		वापस;
	पूर्ण

	acpi_db_decode_arguments(walk_state);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_display_results
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: Display current contents of a method result stack
 *
 ******************************************************************************/

व्योम acpi_db_display_results(व्योम)
अणु
	u32 i;
	काष्ठा acpi_walk_state *walk_state;
	जोड़ acpi_opeअक्रम_object *obj_desc;
	u32 result_count = 0;
	काष्ठा acpi_namespace_node *node;
	जोड़ acpi_generic_state *frame;
	u32 index;		/* Index onto current frame */

	walk_state = acpi_ds_get_current_walk_state(acpi_gbl_current_walk_list);
	अगर (!walk_state) अणु
		acpi_os_म_लिखो("There is no method currently executing\n");
		वापस;
	पूर्ण

	node = walk_state->method_node;

	अगर (walk_state->results) अणु
		result_count = walk_state->result_count;
	पूर्ण

	acpi_os_म_लिखो("Method [%4.4s] has %X stacked result objects\n",
		       acpi_ut_get_node_name(node), result_count);

	/* From the top element of result stack */

	frame = walk_state->results;
	index = (result_count - 1) % ACPI_RESULTS_FRAME_OBJ_NUM;

	क्रम (i = 0; i < result_count; i++) अणु
		obj_desc = frame->results.obj_desc[index];
		acpi_os_म_लिखो("Result%u: ", i);
		acpi_db_display_पूर्णांकernal_object(obj_desc, walk_state);

		अगर (index == 0) अणु
			frame = frame->results.next;
			index = ACPI_RESULTS_FRAME_OBJ_NUM;
		पूर्ण

		index--;
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_display_calling_tree
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: Display current calling tree of nested control methods
 *
 ******************************************************************************/

व्योम acpi_db_display_calling_tree(व्योम)
अणु
	काष्ठा acpi_walk_state *walk_state;
	काष्ठा acpi_namespace_node *node;

	walk_state = acpi_ds_get_current_walk_state(acpi_gbl_current_walk_list);
	अगर (!walk_state) अणु
		acpi_os_म_लिखो("There is no method currently executing\n");
		वापस;
	पूर्ण

	acpi_os_म_लिखो("Current Control Method Call Tree\n");

	जबतक (walk_state) अणु
		node = walk_state->method_node;
		acpi_os_म_लिखो("  [%4.4s]\n", acpi_ut_get_node_name(node));

		walk_state = walk_state->next;
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_display_object_type
 *
 * PARAMETERS:  object_arg      - User entered NS node handle
 *
 * RETURN:      None
 *
 * DESCRIPTION: Display type of an arbitrary NS node
 *
 ******************************************************************************/

व्योम acpi_db_display_object_type(अक्षर *object_arg)
अणु
	acpi_size arg;
	acpi_handle handle;
	काष्ठा acpi_device_info *info;
	acpi_status status;
	u32 i;

	arg = म_से_अदीर्घ(object_arg, शून्य, 16);
	handle = ACPI_TO_POINTER(arg);

	status = acpi_get_object_info(handle, &info);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_os_म_लिखो("Could not get object info, %s\n",
			       acpi_क्रमmat_exception(status));
		वापस;
	पूर्ण

	acpi_os_म_लिखो("ADR: %8.8X%8.8X, Flags: %X\n",
		       ACPI_FORMAT_UINT64(info->address), info->flags);

	acpi_os_म_लिखो("S1D-%2.2X S2D-%2.2X S3D-%2.2X S4D-%2.2X\n",
		       info->highest_dstates[0], info->highest_dstates[1],
		       info->highest_dstates[2], info->highest_dstates[3]);

	acpi_os_म_लिखो("S0W-%2.2X S1W-%2.2X S2W-%2.2X S3W-%2.2X S4W-%2.2X\n",
		       info->lowest_dstates[0], info->lowest_dstates[1],
		       info->lowest_dstates[2], info->lowest_dstates[3],
		       info->lowest_dstates[4]);

	अगर (info->valid & ACPI_VALID_HID) अणु
		acpi_os_म_लिखो("HID: %s\n", info->hardware_id.string);
	पूर्ण

	अगर (info->valid & ACPI_VALID_UID) अणु
		acpi_os_म_लिखो("UID: %s\n", info->unique_id.string);
	पूर्ण

	अगर (info->valid & ACPI_VALID_CID) अणु
		क्रम (i = 0; i < info->compatible_id_list.count; i++) अणु
			acpi_os_म_लिखो("CID %u: %s\n", i,
				       info->compatible_id_list.ids[i].string);
		पूर्ण
	पूर्ण

	ACPI_FREE(info);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_display_result_object
 *
 * PARAMETERS:  obj_desc        - Object to be displayed
 *              walk_state      - Current walk state
 *
 * RETURN:      None
 *
 * DESCRIPTION: Display the result of an AML opcode
 *
 * Note: Currently only displays the result object अगर we are single stepping.
 * However, this output may be useful in other contexts and could be enabled
 * to करो so अगर needed.
 *
 ******************************************************************************/

व्योम
acpi_db_display_result_object(जोड़ acpi_opeअक्रम_object *obj_desc,
			      काष्ठा acpi_walk_state *walk_state)
अणु

#अगर_अघोषित ACPI_APPLICATION
	अगर (acpi_gbl_db_thपढ़ो_id != acpi_os_get_thपढ़ो_id()) अणु
		वापस;
	पूर्ण
#पूर्ण_अगर

	/* Only display अगर single stepping */

	अगर (!acpi_gbl_cm_single_step) अणु
		वापस;
	पूर्ण

	acpi_os_म_लिखो("ResultObj: ");
	acpi_db_display_पूर्णांकernal_object(obj_desc, walk_state);
	acpi_os_म_लिखो("\n");
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_display_argument_object
 *
 * PARAMETERS:  obj_desc        - Object to be displayed
 *              walk_state      - Current walk state
 *
 * RETURN:      None
 *
 * DESCRIPTION: Display the result of an AML opcode
 *
 ******************************************************************************/

व्योम
acpi_db_display_argument_object(जोड़ acpi_opeअक्रम_object *obj_desc,
				काष्ठा acpi_walk_state *walk_state)
अणु

#अगर_अघोषित ACPI_APPLICATION
	अगर (acpi_gbl_db_thपढ़ो_id != acpi_os_get_thपढ़ो_id()) अणु
		वापस;
	पूर्ण
#पूर्ण_अगर

	अगर (!acpi_gbl_cm_single_step) अणु
		वापस;
	पूर्ण

	acpi_os_म_लिखो("ArgObj:  ");
	acpi_db_display_पूर्णांकernal_object(obj_desc, walk_state);
पूर्ण

#अगर (!ACPI_REDUCED_HARDWARE)
/*******************************************************************************
 *
 * FUNCTION:    acpi_db_display_gpes
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: Display the current GPE काष्ठाures
 *
 ******************************************************************************/

व्योम acpi_db_display_gpes(व्योम)
अणु
	काष्ठा acpi_gpe_block_info *gpe_block;
	काष्ठा acpi_gpe_xrupt_info *gpe_xrupt_info;
	काष्ठा acpi_gpe_event_info *gpe_event_info;
	काष्ठा acpi_gpe_रेजिस्टर_info *gpe_रेजिस्टर_info;
	अक्षर *gpe_type;
	काष्ठा acpi_gpe_notअगरy_info *notअगरy;
	u32 gpe_index;
	u32 block = 0;
	u32 i;
	u32 j;
	u32 count;
	अक्षर buffer[80];
	काष्ठा acpi_buffer ret_buf;
	acpi_status status;

	ret_buf.length = माप(buffer);
	ret_buf.poपूर्णांकer = buffer;

	block = 0;

	/* Walk the GPE lists */

	gpe_xrupt_info = acpi_gbl_gpe_xrupt_list_head;
	जबतक (gpe_xrupt_info) अणु
		gpe_block = gpe_xrupt_info->gpe_block_list_head;
		जबतक (gpe_block) अणु
			status = acpi_get_name(gpe_block->node,
					       ACPI_FULL_PATHNAME_NO_TRAILING,
					       &ret_buf);
			अगर (ACPI_FAILURE(status)) अणु
				acpi_os_म_लिखो
				    ("Could not convert name to pathname\n");
			पूर्ण

			अगर (gpe_block->node == acpi_gbl_fadt_gpe_device) अणु
				gpe_type = "FADT-defined GPE block";
			पूर्ण अन्यथा अणु
				gpe_type = "GPE Block Device";
			पूर्ण

			acpi_os_म_लिखो
			    ("\nBlock %u - Info %p  DeviceNode %p [%s] - %s\n",
			     block, gpe_block, gpe_block->node, buffer,
			     gpe_type);

			acpi_os_म_लिखो("    Registers:    %u (%u GPEs)\n",
				       gpe_block->रेजिस्टर_count,
				       gpe_block->gpe_count);

			acpi_os_म_लिखो
			    ("    GPE range:    0x%X to 0x%X on interrupt %u\n",
			     gpe_block->block_base_number,
			     gpe_block->block_base_number +
			     (gpe_block->gpe_count - 1),
			     gpe_xrupt_info->पूर्णांकerrupt_number);

			acpi_os_म_लिखो
			    ("    RegisterInfo: %p  Status %8.8X%8.8X Enable %8.8X%8.8X\n",
			     gpe_block->रेजिस्टर_info,
			     ACPI_FORMAT_UINT64(gpe_block->रेजिस्टर_info->
						status_address.address),
			     ACPI_FORMAT_UINT64(gpe_block->रेजिस्टर_info->
						enable_address.address));

			acpi_os_म_लिखो("  EventInfo:    %p\n",
				       gpe_block->event_info);

			/* Examine each GPE Register within the block */

			क्रम (i = 0; i < gpe_block->रेजिस्टर_count; i++) अणु
				gpe_रेजिस्टर_info =
				    &gpe_block->रेजिस्टर_info[i];

				acpi_os_म_लिखो("    Reg %u: (GPE %.2X-%.2X)  "
					       "RunEnable %2.2X WakeEnable %2.2X"
					       " Status %8.8X%8.8X Enable %8.8X%8.8X\n",
					       i,
					       gpe_रेजिस्टर_info->
					       base_gpe_number,
					       gpe_रेजिस्टर_info->
					       base_gpe_number +
					       (ACPI_GPE_REGISTER_WIDTH - 1),
					       gpe_रेजिस्टर_info->
					       enable_क्रम_run,
					       gpe_रेजिस्टर_info->
					       enable_क्रम_wake,
					       ACPI_FORMAT_UINT64
					       (gpe_रेजिस्टर_info->
						status_address.address),
					       ACPI_FORMAT_UINT64
					       (gpe_रेजिस्टर_info->
						enable_address.address));

				/* Now look at the inभागidual GPEs in this byte रेजिस्टर */

				क्रम (j = 0; j < ACPI_GPE_REGISTER_WIDTH; j++) अणु
					gpe_index =
					    (i * ACPI_GPE_REGISTER_WIDTH) + j;
					gpe_event_info =
					    &gpe_block->event_info[gpe_index];

					अगर (ACPI_GPE_DISPATCH_TYPE
					    (gpe_event_info->flags) ==
					    ACPI_GPE_DISPATCH_NONE) अणु

						/* This GPE is not used (no method or handler), ignore it */

						जारी;
					पूर्ण

					acpi_os_म_लिखो
					    ("        GPE %.2X: %p  RunRefs %2.2X Flags %2.2X (",
					     gpe_block->block_base_number +
					     gpe_index, gpe_event_info,
					     gpe_event_info->runसमय_count,
					     gpe_event_info->flags);

					/* Decode the flags byte */

					अगर (gpe_event_info->
					    flags & ACPI_GPE_LEVEL_TRIGGERED) अणु
						acpi_os_म_लिखो("Level, ");
					पूर्ण अन्यथा अणु
						acpi_os_म_लिखो("Edge, ");
					पूर्ण

					अगर (gpe_event_info->
					    flags & ACPI_GPE_CAN_WAKE) अणु
						acpi_os_म_लिखो("CanWake, ");
					पूर्ण अन्यथा अणु
						acpi_os_म_लिखो("RunOnly, ");
					पूर्ण

					चयन (ACPI_GPE_DISPATCH_TYPE
						(gpe_event_info->flags)) अणु
					हाल ACPI_GPE_DISPATCH_NONE:

						acpi_os_म_लिखो("NotUsed");
						अवरोध;

					हाल ACPI_GPE_DISPATCH_METHOD:

						acpi_os_म_लिखो("Method");
						अवरोध;

					हाल ACPI_GPE_DISPATCH_HANDLER:

						acpi_os_म_लिखो("Handler");
						अवरोध;

					हाल ACPI_GPE_DISPATCH_NOTIFY:

						count = 0;
						notअगरy =
						    gpe_event_info->dispatch.
						    notअगरy_list;
						जबतक (notअगरy) अणु
							count++;
							notअगरy = notअगरy->next;
						पूर्ण

						acpi_os_म_लिखो
						    ("Implicit Notify on %u devices",
						     count);
						अवरोध;

					हाल ACPI_GPE_DISPATCH_RAW_HANDLER:

						acpi_os_म_लिखो("RawHandler");
						अवरोध;

					शेष:

						acpi_os_म_लिखो("UNKNOWN: %X",
							       ACPI_GPE_DISPATCH_TYPE
							       (gpe_event_info->
								flags));
						अवरोध;
					पूर्ण

					acpi_os_म_लिखो(")\n");
				पूर्ण
			पूर्ण

			block++;
			gpe_block = gpe_block->next;
		पूर्ण

		gpe_xrupt_info = gpe_xrupt_info->next;
	पूर्ण
पूर्ण
#पूर्ण_अगर				/* !ACPI_REDUCED_HARDWARE */

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_display_handlers
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: Display the currently installed global handlers
 *
 ******************************************************************************/

व्योम acpi_db_display_handlers(व्योम)
अणु
	जोड़ acpi_opeअक्रम_object *obj_desc;
	जोड़ acpi_opeअक्रम_object *handler_obj;
	acpi_adr_space_type space_id;
	u32 i;

	/* Operation region handlers */

	acpi_os_म_लिखो("\nOperation Region Handlers at the namespace root:\n");

	obj_desc = acpi_ns_get_attached_object(acpi_gbl_root_node);
	अगर (obj_desc) अणु
		क्रम (i = 0; i < ACPI_ARRAY_LENGTH(acpi_gbl_space_id_list); i++) अणु
			space_id = acpi_gbl_space_id_list[i];

			acpi_os_म_लिखो(ACPI_PREDEFINED_PREFIX,
				       acpi_ut_get_region_name((u8)space_id),
				       space_id);

			handler_obj =
			    acpi_ev_find_region_handler(space_id,
							obj_desc->common_notअगरy.
							handler);
			अगर (handler_obj) अणु
				acpi_os_म_लिखो(ACPI_HANDLER_PRESENT_STRING,
					       (handler_obj->address_space.
						handler_flags &
						ACPI_ADDR_HANDLER_DEFAULT_INSTALLED)
					       ? "Default" : "User",
					       handler_obj->address_space.
					       handler);

				जाओ found_handler;
			पूर्ण

			/* There is no handler क्रम this space_id */

			acpi_os_म_लिखो("None\n");

found_handler:		;
		पूर्ण

		/* Find all handlers क्रम user-defined space_IDs */

		handler_obj = obj_desc->common_notअगरy.handler;
		जबतक (handler_obj) अणु
			अगर (handler_obj->address_space.space_id >=
			    ACPI_USER_REGION_BEGIN) अणु
				acpi_os_म_लिखो(ACPI_PREDEFINED_PREFIX,
					       "User-defined ID",
					       handler_obj->address_space.
					       space_id);
				acpi_os_म_लिखो(ACPI_HANDLER_PRESENT_STRING,
					       (handler_obj->address_space.
						handler_flags &
						ACPI_ADDR_HANDLER_DEFAULT_INSTALLED)
					       ? "Default" : "User",
					       handler_obj->address_space.
					       handler);
			पूर्ण

			handler_obj = handler_obj->address_space.next;
		पूर्ण
	पूर्ण
#अगर (!ACPI_REDUCED_HARDWARE)

	/* Fixed event handlers */

	acpi_os_म_लिखो("\nFixed Event Handlers:\n");

	क्रम (i = 0; i < ACPI_NUM_FIXED_EVENTS; i++) अणु
		acpi_os_म_लिखो(ACPI_PREDEFINED_PREFIX,
			       acpi_ut_get_event_name(i), i);
		अगर (acpi_gbl_fixed_event_handlers[i].handler) अणु
			acpi_os_म_लिखो(ACPI_HANDLER_PRESENT_STRING, "User",
				       acpi_gbl_fixed_event_handlers[i].
				       handler);
		पूर्ण अन्यथा अणु
			acpi_os_म_लिखो(ACPI_HANDLER_NOT_PRESENT_STRING, "None");
		पूर्ण
	पूर्ण

#पूर्ण_अगर				/* !ACPI_REDUCED_HARDWARE */

	/* Miscellaneous global handlers */

	acpi_os_म_लिखो("\nMiscellaneous Global Handlers:\n");

	क्रम (i = 0; i < ACPI_ARRAY_LENGTH(acpi_gbl_handler_list); i++) अणु
		acpi_os_म_लिखो(ACPI_HANDLER_NAME_STRING,
			       acpi_gbl_handler_list[i].name);

		अगर (acpi_gbl_handler_list[i].handler) अणु
			acpi_os_म_लिखो(ACPI_HANDLER_PRESENT_STRING, "User",
				       acpi_gbl_handler_list[i].handler);
		पूर्ण अन्यथा अणु
			acpi_os_म_लिखो(ACPI_HANDLER_NOT_PRESENT_STRING, "None");
		पूर्ण
	पूर्ण

	/* Other handlers that are installed throughout the namespace */

	acpi_os_म_लिखो("\nOperation Region Handlers for specific devices:\n");

	(व्योम)acpi_walk_namespace(ACPI_TYPE_DEVICE, ACPI_ROOT_OBJECT,
				  ACPI_UINT32_MAX,
				  acpi_db_display_non_root_handlers, शून्य, शून्य,
				  शून्य);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_display_non_root_handlers
 *
 * PARAMETERS:  acpi_walk_callback
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Display inक्रमmation about all handlers installed क्रम a
 *              device object.
 *
 ******************************************************************************/

अटल acpi_status
acpi_db_display_non_root_handlers(acpi_handle obj_handle,
				  u32 nesting_level,
				  व्योम *context, व्योम **वापस_value)
अणु
	काष्ठा acpi_namespace_node *node =
	    ACPI_CAST_PTR(काष्ठा acpi_namespace_node, obj_handle);
	जोड़ acpi_opeअक्रम_object *obj_desc;
	जोड़ acpi_opeअक्रम_object *handler_obj;
	अक्षर *pathname;

	obj_desc = acpi_ns_get_attached_object(node);
	अगर (!obj_desc) अणु
		वापस (AE_OK);
	पूर्ण

	pathname = acpi_ns_get_normalized_pathname(node, TRUE);
	अगर (!pathname) अणु
		वापस (AE_OK);
	पूर्ण

	/* Display all handlers associated with this device */

	handler_obj = obj_desc->common_notअगरy.handler;
	जबतक (handler_obj) अणु
		acpi_os_म_लिखो(ACPI_PREDEFINED_PREFIX,
			       acpi_ut_get_region_name((u8)handler_obj->
						       address_space.space_id),
			       handler_obj->address_space.space_id);

		acpi_os_म_लिखो(ACPI_HANDLER_PRESENT_STRING2,
			       (handler_obj->address_space.handler_flags &
				ACPI_ADDR_HANDLER_DEFAULT_INSTALLED) ? "Default"
			       : "User", handler_obj->address_space.handler);

		acpi_os_म_लिखो(" Device Name: %s (%p)\n", pathname, node);

		handler_obj = handler_obj->address_space.next;
	पूर्ण

	ACPI_FREE(pathname);
	वापस (AE_OK);
पूर्ण
