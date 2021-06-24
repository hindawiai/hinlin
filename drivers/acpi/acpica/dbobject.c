<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/*******************************************************************************
 *
 * Module Name: dbobject - ACPI object decode and display
 *
 ******************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acnamesp.h"
#समावेश "acdebug.h"

#घोषणा _COMPONENT          ACPI_CA_DEBUGGER
ACPI_MODULE_NAME("dbobject")

/* Local prototypes */
अटल व्योम acpi_db_decode_node(काष्ठा acpi_namespace_node *node);

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_dump_method_info
 *
 * PARAMETERS:  status          - Method execution status
 *              walk_state      - Current state of the parse tree walk
 *
 * RETURN:      None
 *
 * DESCRIPTION: Called when a method has been पातed because of an error.
 *              Dumps the method execution stack, and the method locals/args,
 *              and disassembles the AML opcode that failed.
 *
 ******************************************************************************/

व्योम
acpi_db_dump_method_info(acpi_status status, काष्ठा acpi_walk_state *walk_state)
अणु
	काष्ठा acpi_thपढ़ो_state *thपढ़ो;
	काष्ठा acpi_namespace_node *node;

	node = walk_state->method_node;

	/* There are no locals or arguments क्रम the module-level code हाल */

	अगर (node == acpi_gbl_root_node) अणु
		वापस;
	पूर्ण

	/* Ignore control codes, they are not errors */

	अगर (ACPI_CNTL_EXCEPTION(status)) अणु
		वापस;
	पूर्ण

	/* We may be executing a deferred opcode */

	अगर (walk_state->deferred_node) अणु
		acpi_os_म_लिखो("Executing subtree for Buffer/Package/Region\n");
		वापस;
	पूर्ण

	/*
	 * If there is no Thपढ़ो, we are not actually executing a method.
	 * This can happen when the iASL compiler calls the पूर्णांकerpreter
	 * to perक्रमm स्थिरant folding.
	 */
	thपढ़ो = walk_state->thपढ़ो;
	अगर (!thपढ़ो) अणु
		वापस;
	पूर्ण

	/* Display the method locals and arguments */

	acpi_os_म_लिखो("\n");
	acpi_db_decode_locals(walk_state);
	acpi_os_म_लिखो("\n");
	acpi_db_decode_arguments(walk_state);
	acpi_os_म_लिखो("\n");
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_decode_पूर्णांकernal_object
 *
 * PARAMETERS:  obj_desc        - Object to be displayed
 *
 * RETURN:      None
 *
 * DESCRIPTION: Short display of an पूर्णांकernal object. Numbers/Strings/Buffers.
 *
 ******************************************************************************/

व्योम acpi_db_decode_पूर्णांकernal_object(जोड़ acpi_opeअक्रम_object *obj_desc)
अणु
	u32 i;

	अगर (!obj_desc) अणु
		acpi_os_म_लिखो(" Uninitialized");
		वापस;
	पूर्ण

	अगर (ACPI_GET_DESCRIPTOR_TYPE(obj_desc) != ACPI_DESC_TYPE_OPERAND) अणु
		acpi_os_म_लिखो(" %p [%s]", obj_desc,
			       acpi_ut_get_descriptor_name(obj_desc));
		वापस;
	पूर्ण

	acpi_os_म_लिखो(" %s", acpi_ut_get_object_type_name(obj_desc));

	चयन (obj_desc->common.type) अणु
	हाल ACPI_TYPE_INTEGER:

		acpi_os_म_लिखो(" %8.8X%8.8X",
			       ACPI_FORMAT_UINT64(obj_desc->पूर्णांकeger.value));
		अवरोध;

	हाल ACPI_TYPE_STRING:

		acpi_os_म_लिखो("(%u) \"%.60s",
			       obj_desc->string.length,
			       obj_desc->string.poपूर्णांकer);

		अगर (obj_desc->string.length > 60) अणु
			acpi_os_म_लिखो("...");
		पूर्ण अन्यथा अणु
			acpi_os_म_लिखो("\"");
		पूर्ण
		अवरोध;

	हाल ACPI_TYPE_BUFFER:

		acpi_os_म_लिखो("(%u)", obj_desc->buffer.length);
		क्रम (i = 0; (i < 8) && (i < obj_desc->buffer.length); i++) अणु
			acpi_os_म_लिखो(" %2.2X", obj_desc->buffer.poपूर्णांकer[i]);
		पूर्ण
		अवरोध;

	शेष:

		acpi_os_म_लिखो(" %p", obj_desc);
		अवरोध;
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_decode_node
 *
 * PARAMETERS:  node        - Object to be displayed
 *
 * RETURN:      None
 *
 * DESCRIPTION: Short display of a namespace node
 *
 ******************************************************************************/

अटल व्योम acpi_db_decode_node(काष्ठा acpi_namespace_node *node)
अणु

	acpi_os_म_लिखो("<Node>          Name %4.4s",
		       acpi_ut_get_node_name(node));

	अगर (node->flags & ANOBJ_METHOD_ARG) अणु
		acpi_os_म_लिखो(" [Method Arg]");
	पूर्ण
	अगर (node->flags & ANOBJ_METHOD_LOCAL) अणु
		acpi_os_म_लिखो(" [Method Local]");
	पूर्ण

	चयन (node->type) अणु

		/* These types have no attached object */

	हाल ACPI_TYPE_DEVICE:

		acpi_os_म_लिखो(" Device");
		अवरोध;

	हाल ACPI_TYPE_THERMAL:

		acpi_os_म_लिखो(" Thermal Zone");
		अवरोध;

	शेष:

		acpi_db_decode_पूर्णांकernal_object(acpi_ns_get_attached_object
					       (node));
		अवरोध;
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_display_पूर्णांकernal_object
 *
 * PARAMETERS:  obj_desc        - Object to be displayed
 *              walk_state      - Current walk state
 *
 * RETURN:      None
 *
 * DESCRIPTION: Short display of an पूर्णांकernal object
 *
 ******************************************************************************/

व्योम
acpi_db_display_पूर्णांकernal_object(जोड़ acpi_opeअक्रम_object *obj_desc,
				काष्ठा acpi_walk_state *walk_state)
अणु
	u8 type;

	acpi_os_म_लिखो("%p ", obj_desc);

	अगर (!obj_desc) अणु
		acpi_os_म_लिखो("<Null Object>\n");
		वापस;
	पूर्ण

	/* Decode the object type */

	चयन (ACPI_GET_DESCRIPTOR_TYPE(obj_desc)) अणु
	हाल ACPI_DESC_TYPE_PARSER:

		acpi_os_म_लिखो("<Parser> ");
		अवरोध;

	हाल ACPI_DESC_TYPE_NAMED:

		acpi_db_decode_node((काष्ठा acpi_namespace_node *)obj_desc);
		अवरोध;

	हाल ACPI_DESC_TYPE_OPERAND:

		type = obj_desc->common.type;
		अगर (type > ACPI_TYPE_LOCAL_MAX) अणु
			acpi_os_म_लिखो(" Type %X [Invalid Type]", (u32)type);
			वापस;
		पूर्ण

		/* Decode the ACPI object type */

		चयन (obj_desc->common.type) अणु
		हाल ACPI_TYPE_LOCAL_REFERENCE:

			acpi_os_म_लिखो("[%s] ",
				       acpi_ut_get_reference_name(obj_desc));

			/* Decode the reference */

			चयन (obj_desc->reference.class) अणु
			हाल ACPI_REFCLASS_LOCAL:

				acpi_os_म_लिखो("%X ",
					       obj_desc->reference.value);
				अगर (walk_state) अणु
					obj_desc = walk_state->local_variables
					    [obj_desc->reference.value].object;
					acpi_os_म_लिखो("%p", obj_desc);
					acpi_db_decode_पूर्णांकernal_object
					    (obj_desc);
				पूर्ण
				अवरोध;

			हाल ACPI_REFCLASS_ARG:

				acpi_os_म_लिखो("%X ",
					       obj_desc->reference.value);
				अगर (walk_state) अणु
					obj_desc = walk_state->arguments
					    [obj_desc->reference.value].object;
					acpi_os_म_लिखो("%p", obj_desc);
					acpi_db_decode_पूर्णांकernal_object
					    (obj_desc);
				पूर्ण
				अवरोध;

			हाल ACPI_REFCLASS_INDEX:

				चयन (obj_desc->reference.target_type) अणु
				हाल ACPI_TYPE_BUFFER_FIELD:

					acpi_os_म_लिखो("%p",
						       obj_desc->reference.
						       object);
					acpi_db_decode_पूर्णांकernal_object
					    (obj_desc->reference.object);
					अवरोध;

				हाल ACPI_TYPE_PACKAGE:

					acpi_os_म_लिखो("%p",
						       obj_desc->reference.
						       where);
					अगर (!obj_desc->reference.where) अणु
						acpi_os_म_लिखो
						    (" Uninitialized WHERE pointer");
					पूर्ण अन्यथा अणु
						acpi_db_decode_पूर्णांकernal_object(*
									       (obj_desc->
										reference.
										where));
					पूर्ण
					अवरोध;

				शेष:

					acpi_os_म_लिखो
					    ("Unknown index target type");
					अवरोध;
				पूर्ण
				अवरोध;

			हाल ACPI_REFCLASS_REFOF:

				अगर (!obj_desc->reference.object) अणु
					acpi_os_म_लिखो
					    ("Uninitialized reference subobject pointer");
					अवरोध;
				पूर्ण

				/* Reference can be to a Node or an Opeअक्रम object */

				चयन (ACPI_GET_DESCRIPTOR_TYPE
					(obj_desc->reference.object)) अणु
				हाल ACPI_DESC_TYPE_NAMED:

					acpi_db_decode_node(obj_desc->reference.
							    object);
					अवरोध;

				हाल ACPI_DESC_TYPE_OPERAND:

					acpi_db_decode_पूर्णांकernal_object
					    (obj_desc->reference.object);
					अवरोध;

				शेष:
					अवरोध;
				पूर्ण
				अवरोध;

			हाल ACPI_REFCLASS_NAME:

				acpi_db_decode_node(obj_desc->reference.node);
				अवरोध;

			हाल ACPI_REFCLASS_DEBUG:
			हाल ACPI_REFCLASS_TABLE:

				acpi_os_म_लिखो("\n");
				अवरोध;

			शेष:	/* Unknown reference class */

				acpi_os_म_लिखो("%2.2X\n",
					       obj_desc->reference.class);
				अवरोध;
			पूर्ण
			अवरोध;

		शेष:

			acpi_os_म_लिखो("<Obj>          ");
			acpi_db_decode_पूर्णांकernal_object(obj_desc);
			अवरोध;
		पूर्ण
		अवरोध;

	शेष:

		acpi_os_म_लिखो("<Not a valid ACPI Object Descriptor> [%s]",
			       acpi_ut_get_descriptor_name(obj_desc));
		अवरोध;
	पूर्ण

	acpi_os_म_लिखो("\n");
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_decode_locals
 *
 * PARAMETERS:  walk_state      - State क्रम current method
 *
 * RETURN:      None
 *
 * DESCRIPTION: Display all locals क्रम the currently running control method
 *
 ******************************************************************************/

व्योम acpi_db_decode_locals(काष्ठा acpi_walk_state *walk_state)
अणु
	u32 i;
	जोड़ acpi_opeअक्रम_object *obj_desc;
	काष्ठा acpi_namespace_node *node;
	u8 display_locals = FALSE;

	node = walk_state->method_node;

	/* There are no locals क्रम the module-level code हाल */

	अगर (node == acpi_gbl_root_node) अणु
		वापस;
	पूर्ण

	अगर (!node) अणु
		acpi_os_म_लिखो
		    ("No method node (Executing subtree for buffer or opregion)\n");
		वापस;
	पूर्ण

	अगर (node->type != ACPI_TYPE_METHOD) अणु
		acpi_os_म_लिखो("Executing subtree for Buffer/Package/Region\n");
		वापस;
	पूर्ण

	/* Are any locals actually set? */

	क्रम (i = 0; i < ACPI_METHOD_NUM_LOCALS; i++) अणु
		obj_desc = walk_state->local_variables[i].object;
		अगर (obj_desc) अणु
			display_locals = TRUE;
			अवरोध;
		पूर्ण
	पूर्ण

	/* If any are set, only display the ones that are set */

	अगर (display_locals) अणु
		acpi_os_म_लिखो
		    ("\nInitialized Local Variables for Method [%4.4s]:\n",
		     acpi_ut_get_node_name(node));

		क्रम (i = 0; i < ACPI_METHOD_NUM_LOCALS; i++) अणु
			obj_desc = walk_state->local_variables[i].object;
			अगर (obj_desc) अणु
				acpi_os_म_लिखो("  Local%X: ", i);
				acpi_db_display_पूर्णांकernal_object(obj_desc,
								walk_state);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		acpi_os_म_लिखो
		    ("No Local Variables are initialized for Method [%4.4s]\n",
		     acpi_ut_get_node_name(node));
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_decode_arguments
 *
 * PARAMETERS:  walk_state      - State क्रम current method
 *
 * RETURN:      None
 *
 * DESCRIPTION: Display all arguments क्रम the currently running control method
 *
 ******************************************************************************/

व्योम acpi_db_decode_arguments(काष्ठा acpi_walk_state *walk_state)
अणु
	u32 i;
	जोड़ acpi_opeअक्रम_object *obj_desc;
	काष्ठा acpi_namespace_node *node;
	u8 display_args = FALSE;

	node = walk_state->method_node;

	/* There are no arguments क्रम the module-level code हाल */

	अगर (node == acpi_gbl_root_node) अणु
		वापस;
	पूर्ण

	अगर (!node) अणु
		acpi_os_म_लिखो
		    ("No method node (Executing subtree for buffer or opregion)\n");
		वापस;
	पूर्ण

	अगर (node->type != ACPI_TYPE_METHOD) अणु
		acpi_os_म_लिखो("Executing subtree for Buffer/Package/Region\n");
		वापस;
	पूर्ण

	/* Are any arguments actually set? */

	क्रम (i = 0; i < ACPI_METHOD_NUM_ARGS; i++) अणु
		obj_desc = walk_state->arguments[i].object;
		अगर (obj_desc) अणु
			display_args = TRUE;
			अवरोध;
		पूर्ण
	पूर्ण

	/* If any are set, only display the ones that are set */

	अगर (display_args) अणु
		acpi_os_म_लिखो("Initialized Arguments for Method [%4.4s]:  "
			       "(%X arguments defined for method invocation)\n",
			       acpi_ut_get_node_name(node),
			       node->object->method.param_count);

		क्रम (i = 0; i < ACPI_METHOD_NUM_ARGS; i++) अणु
			obj_desc = walk_state->arguments[i].object;
			अगर (obj_desc) अणु
				acpi_os_म_लिखो("  Arg%u:   ", i);
				acpi_db_display_पूर्णांकernal_object(obj_desc,
								walk_state);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		acpi_os_म_लिखो
		    ("No Arguments are initialized for method [%4.4s]\n",
		     acpi_ut_get_node_name(node));
	पूर्ण
पूर्ण
