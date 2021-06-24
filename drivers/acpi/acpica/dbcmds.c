<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/*******************************************************************************
 *
 * Module Name: dbcmds - Miscellaneous debug commands and output routines
 *
 ******************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acevents.h"
#समावेश "acdebug.h"
#समावेश "acnamesp.h"
#समावेश "acresrc.h"
#समावेश "actables.h"

#घोषणा _COMPONENT          ACPI_CA_DEBUGGER
ACPI_MODULE_NAME("dbcmds")

/* Local prototypes */
अटल व्योम
acpi_dm_compare_aml_resources(u8 *aml1_buffer,
			      acpi_rsdesc_size aml1_buffer_length,
			      u8 *aml2_buffer,
			      acpi_rsdesc_size aml2_buffer_length);

अटल acpi_status
acpi_dm_test_resource_conversion(काष्ठा acpi_namespace_node *node, अक्षर *name);

अटल acpi_status
acpi_db_resource_callback(काष्ठा acpi_resource *resource, व्योम *context);

अटल acpi_status
acpi_db_device_resources(acpi_handle obj_handle,
			 u32 nesting_level, व्योम *context, व्योम **वापस_value);

अटल व्योम acpi_db_करो_one_sleep_state(u8 sleep_state);

अटल अक्षर *acpi_db_trace_method_name = शून्य;

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_convert_to_node
 *
 * PARAMETERS:  in_string           - String to convert
 *
 * RETURN:      Poपूर्णांकer to a NS node
 *
 * DESCRIPTION: Convert a string to a valid NS poपूर्णांकer. Handles numeric or
 *              alphanumeric strings.
 *
 ******************************************************************************/

काष्ठा acpi_namespace_node *acpi_db_convert_to_node(अक्षर *in_string)
अणु
	काष्ठा acpi_namespace_node *node;
	acpi_size address;

	अगर ((*in_string >= 0x30) && (*in_string <= 0x39)) अणु

		/* Numeric argument, convert */

		address = म_से_अदीर्घ(in_string, शून्य, 16);
		node = ACPI_TO_POINTER(address);
		अगर (!acpi_os_पढ़ोable(node, माप(काष्ठा acpi_namespace_node))) अणु
			acpi_os_म_लिखो("Address %p is invalid", node);
			वापस (शून्य);
		पूर्ण

		/* Make sure poपूर्णांकer is valid NS node */

		अगर (ACPI_GET_DESCRIPTOR_TYPE(node) != ACPI_DESC_TYPE_NAMED) अणु
			acpi_os_म_लिखो
			    ("Address %p is not a valid namespace node [%s]\n",
			     node, acpi_ut_get_descriptor_name(node));
			वापस (शून्य);
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Alpha argument: The parameter is a name string that must be
		 * resolved to a Namespace object.
		 */
		node = acpi_db_local_ns_lookup(in_string);
		अगर (!node) अणु
			acpi_os_म_लिखो
			    ("Could not find [%s] in namespace, defaulting to root node\n",
			     in_string);
			node = acpi_gbl_root_node;
		पूर्ण
	पूर्ण

	वापस (node);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_sleep
 *
 * PARAMETERS:  object_arg          - Desired sleep state (0-5). शून्य means
 *                                    invoke all possible sleep states.
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Simulate sleep/wake sequences
 *
 ******************************************************************************/

acpi_status acpi_db_sleep(अक्षर *object_arg)
अणु
	u8 sleep_state;
	u32 i;

	ACPI_FUNCTION_TRACE(acpi_db_sleep);

	/* Null input (no arguments) means to invoke all sleep states */

	अगर (!object_arg) अणु
		acpi_os_म_लिखो("Invoking all possible sleep states, 0-%d\n",
			       ACPI_S_STATES_MAX);

		क्रम (i = 0; i <= ACPI_S_STATES_MAX; i++) अणु
			acpi_db_करो_one_sleep_state((u8)i);
		पूर्ण

		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	/* Convert argument to binary and invoke the sleep state */

	sleep_state = (u8)म_से_अदीर्घ(object_arg, शून्य, 0);
	acpi_db_करो_one_sleep_state(sleep_state);
	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_करो_one_sleep_state
 *
 * PARAMETERS:  sleep_state         - Desired sleep state (0-5)
 *
 * RETURN:      None
 *
 * DESCRIPTION: Simulate a sleep/wake sequence
 *
 ******************************************************************************/

अटल व्योम acpi_db_करो_one_sleep_state(u8 sleep_state)
अणु
	acpi_status status;
	u8 sleep_type_a;
	u8 sleep_type_b;

	/* Validate parameter */

	अगर (sleep_state > ACPI_S_STATES_MAX) अणु
		acpi_os_म_लिखो("Sleep state %d out of range (%d max)\n",
			       sleep_state, ACPI_S_STATES_MAX);
		वापस;
	पूर्ण

	acpi_os_म_लिखो("\n---- Invoking sleep state S%d (%s):\n",
		       sleep_state, acpi_gbl_sleep_state_names[sleep_state]);

	/* Get the values क्रम the sleep type रेजिस्टरs (क्रम display only) */

	status =
	    acpi_get_sleep_type_data(sleep_state, &sleep_type_a, &sleep_type_b);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_os_म_लिखो("Could not evaluate [%s] method, %s\n",
			       acpi_gbl_sleep_state_names[sleep_state],
			       acpi_क्रमmat_exception(status));
		वापस;
	पूर्ण

	acpi_os_म_लिखो
	    ("Register values for sleep state S%d: Sleep-A: %.2X, Sleep-B: %.2X\n",
	     sleep_state, sleep_type_a, sleep_type_b);

	/* Invoke the various sleep/wake पूर्णांकerfaces */

	acpi_os_म_लिखो("**** Sleep: Prepare to sleep (S%d) ****\n",
		       sleep_state);
	status = acpi_enter_sleep_state_prep(sleep_state);
	अगर (ACPI_FAILURE(status)) अणु
		जाओ error_निकास;
	पूर्ण

	acpi_os_म_लिखो("**** Sleep: Going to sleep (S%d) ****\n", sleep_state);
	status = acpi_enter_sleep_state(sleep_state);
	अगर (ACPI_FAILURE(status)) अणु
		जाओ error_निकास;
	पूर्ण

	acpi_os_म_लिखो("**** Wake: Prepare to return from sleep (S%d) ****\n",
		       sleep_state);
	status = acpi_leave_sleep_state_prep(sleep_state);
	अगर (ACPI_FAILURE(status)) अणु
		जाओ error_निकास;
	पूर्ण

	acpi_os_म_लिखो("**** Wake: Return from sleep (S%d) ****\n",
		       sleep_state);
	status = acpi_leave_sleep_state(sleep_state);
	अगर (ACPI_FAILURE(status)) अणु
		जाओ error_निकास;
	पूर्ण

	वापस;

error_निकास:
	ACPI_EXCEPTION((AE_INFO, status, "During invocation of sleep state S%d",
			sleep_state));
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_display_locks
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: Display inक्रमmation about पूर्णांकernal mutexes.
 *
 ******************************************************************************/

व्योम acpi_db_display_locks(व्योम)
अणु
	u32 i;

	क्रम (i = 0; i < ACPI_MAX_MUTEX; i++) अणु
		acpi_os_म_लिखो("%26s : %s\n", acpi_ut_get_mutex_name(i),
			       acpi_gbl_mutex_info[i].thपढ़ो_id ==
			       ACPI_MUTEX_NOT_ACQUIRED ? "Locked" : "Unlocked");
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_display_table_info
 *
 * PARAMETERS:  table_arg           - Name of table to be displayed
 *
 * RETURN:      None
 *
 * DESCRIPTION: Display inक्रमmation about loaded tables. Current
 *              implementation displays all loaded tables.
 *
 ******************************************************************************/

व्योम acpi_db_display_table_info(अक्षर *table_arg)
अणु
	u32 i;
	काष्ठा acpi_table_desc *table_desc;
	acpi_status status;

	/* Header */

	acpi_os_म_लिखो("Idx ID  Status Type                    "
		       "TableHeader (Sig, Address, Length, Misc)\n");

	/* Walk the entire root table list */

	क्रम (i = 0; i < acpi_gbl_root_table_list.current_table_count; i++) अणु
		table_desc = &acpi_gbl_root_table_list.tables[i];

		/* Index and Table ID */

		acpi_os_म_लिखो("%3u %.2u ", i, table_desc->owner_id);

		/* Decode the table flags */

		अगर (!(table_desc->flags & ACPI_TABLE_IS_LOADED)) अणु
			acpi_os_म_लिखो("NotLoaded ");
		पूर्ण अन्यथा अणु
			acpi_os_म_लिखो(" Loaded ");
		पूर्ण

		चयन (table_desc->flags & ACPI_TABLE_ORIGIN_MASK) अणु
		हाल ACPI_TABLE_ORIGIN_EXTERNAL_VIRTUAL:

			acpi_os_म_लिखो("External/virtual ");
			अवरोध;

		हाल ACPI_TABLE_ORIGIN_INTERNAL_PHYSICAL:

			acpi_os_म_लिखो("Internal/physical ");
			अवरोध;

		हाल ACPI_TABLE_ORIGIN_INTERNAL_VIRTUAL:

			acpi_os_म_लिखो("Internal/virtual ");
			अवरोध;

		शेष:

			acpi_os_म_लिखो("INVALID TYPE    ");
			अवरोध;
		पूर्ण

		/* Make sure that the table is mapped */

		status = acpi_tb_validate_table(table_desc);
		अगर (ACPI_FAILURE(status)) अणु
			वापस;
		पूर्ण

		/* Dump the table header */

		अगर (table_desc->poपूर्णांकer) अणु
			acpi_tb_prपूर्णांक_table_header(table_desc->address,
						   table_desc->poपूर्णांकer);
		पूर्ण अन्यथा अणु
			/* If the poपूर्णांकer is null, the table has been unloaded */

			ACPI_INFO(("%4.4s - Table has been unloaded",
				   table_desc->signature.ascii));
		पूर्ण
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_unload_acpi_table
 *
 * PARAMETERS:  object_name         - Namespace pathname क्रम an object that
 *                                    is owned by the table to be unloaded
 *
 * RETURN:      None
 *
 * DESCRIPTION: Unload an ACPI table, via any namespace node that is owned
 *              by the table.
 *
 ******************************************************************************/

व्योम acpi_db_unload_acpi_table(अक्षर *object_name)
अणु
	काष्ठा acpi_namespace_node *node;
	acpi_status status;

	/* Translate name to an Named object */

	node = acpi_db_convert_to_node(object_name);
	अगर (!node) अणु
		वापस;
	पूर्ण

	status = acpi_unload_parent_table(ACPI_CAST_PTR(acpi_handle, node));
	अगर (ACPI_SUCCESS(status)) अणु
		acpi_os_म_लिखो("Parent of [%s] (%p) unloaded and uninstalled\n",
			       object_name, node);
	पूर्ण अन्यथा अणु
		acpi_os_म_लिखो("%s, while unloading parent table of [%s]\n",
			       acpi_क्रमmat_exception(status), object_name);
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_send_notअगरy
 *
 * PARAMETERS:  name                - Name of ACPI object where to send notअगरy
 *              value               - Value of the notअगरy to send.
 *
 * RETURN:      None
 *
 * DESCRIPTION: Send an ACPI notअगरication. The value specअगरied is sent to the
 *              named object as an ACPI notअगरy.
 *
 ******************************************************************************/

व्योम acpi_db_send_notअगरy(अक्षर *name, u32 value)
अणु
	काष्ठा acpi_namespace_node *node;
	acpi_status status;

	/* Translate name to an Named object */

	node = acpi_db_convert_to_node(name);
	अगर (!node) अणु
		वापस;
	पूर्ण

	/* Dispatch the notअगरy अगर legal */

	अगर (acpi_ev_is_notअगरy_object(node)) अणु
		status = acpi_ev_queue_notअगरy_request(node, value);
		अगर (ACPI_FAILURE(status)) अणु
			acpi_os_म_लिखो("Could not queue notify\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		acpi_os_म_लिखो("Named object [%4.4s] Type %s, "
			       "must be Device/Thermal/Processor type\n",
			       acpi_ut_get_node_name(node),
			       acpi_ut_get_type_name(node->type));
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_display_पूर्णांकerfaces
 *
 * PARAMETERS:  action_arg          - Null, "install", or "remove"
 *              पूर्णांकerface_name_arg  - Name क्रम install/हटाओ options
 *
 * RETURN:      None
 *
 * DESCRIPTION: Display or modअगरy the global _OSI पूर्णांकerface list
 *
 ******************************************************************************/

व्योम acpi_db_display_पूर्णांकerfaces(अक्षर *action_arg, अक्षर *पूर्णांकerface_name_arg)
अणु
	काष्ठा acpi_पूर्णांकerface_info *next_पूर्णांकerface;
	अक्षर *sub_string;
	acpi_status status;

	/* If no arguments, just display current पूर्णांकerface list */

	अगर (!action_arg) अणु
		(व्योम)acpi_os_acquire_mutex(acpi_gbl_osi_mutex,
					    ACPI_WAIT_FOREVER);

		next_पूर्णांकerface = acpi_gbl_supported_पूर्णांकerfaces;
		जबतक (next_पूर्णांकerface) अणु
			अगर (!(next_पूर्णांकerface->flags & ACPI_OSI_INVALID)) अणु
				acpi_os_म_लिखो("%s\n", next_पूर्णांकerface->name);
			पूर्ण

			next_पूर्णांकerface = next_पूर्णांकerface->next;
		पूर्ण

		acpi_os_release_mutex(acpi_gbl_osi_mutex);
		वापस;
	पूर्ण

	/* If action_arg exists, so must पूर्णांकerface_name_arg */

	अगर (!पूर्णांकerface_name_arg) अणु
		acpi_os_म_लिखो("Missing Interface Name argument\n");
		वापस;
	पूर्ण

	/* Upperहाल the action क्रम match below */

	acpi_ut_strupr(action_arg);

	/* install - install an पूर्णांकerface */

	sub_string = म_माला("INSTALL", action_arg);
	अगर (sub_string) अणु
		status = acpi_install_पूर्णांकerface(पूर्णांकerface_name_arg);
		अगर (ACPI_FAILURE(status)) अणु
			acpi_os_म_लिखो("%s, while installing \"%s\"\n",
				       acpi_क्रमmat_exception(status),
				       पूर्णांकerface_name_arg);
		पूर्ण
		वापस;
	पूर्ण

	/* हटाओ - हटाओ an पूर्णांकerface */

	sub_string = म_माला("REMOVE", action_arg);
	अगर (sub_string) अणु
		status = acpi_हटाओ_पूर्णांकerface(पूर्णांकerface_name_arg);
		अगर (ACPI_FAILURE(status)) अणु
			acpi_os_म_लिखो("%s, while removing \"%s\"\n",
				       acpi_क्रमmat_exception(status),
				       पूर्णांकerface_name_arg);
		पूर्ण
		वापस;
	पूर्ण

	/* Invalid action_arg */

	acpi_os_म_लिखो("Invalid action argument: %s\n", action_arg);
	वापस;
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_display_ढाँचा
 *
 * PARAMETERS:  buffer_arg          - Buffer name or address
 *
 * RETURN:      None
 *
 * DESCRIPTION: Dump a buffer that contains a resource ढाँचा
 *
 ******************************************************************************/

व्योम acpi_db_display_ढाँचा(अक्षर *buffer_arg)
अणु
	काष्ठा acpi_namespace_node *node;
	acpi_status status;
	काष्ठा acpi_buffer वापस_buffer;

	/* Translate buffer_arg to an Named object */

	node = acpi_db_convert_to_node(buffer_arg);
	अगर (!node || (node == acpi_gbl_root_node)) अणु
		acpi_os_म_लिखो("Invalid argument: %s\n", buffer_arg);
		वापस;
	पूर्ण

	/* We must have a buffer object */

	अगर (node->type != ACPI_TYPE_BUFFER) अणु
		acpi_os_म_लिखो
		    ("Not a Buffer object, cannot be a template: %s\n",
		     buffer_arg);
		वापस;
	पूर्ण

	वापस_buffer.length = ACPI_DEBUG_BUFFER_SIZE;
	वापस_buffer.poपूर्णांकer = acpi_gbl_db_buffer;

	/* Attempt to convert the raw buffer to a resource list */

	status = acpi_rs_create_resource_list(node->object, &वापस_buffer);

	acpi_db_set_output_destination(ACPI_DB_REसूचीECTABLE_OUTPUT);
	acpi_dbg_level |= ACPI_LV_RESOURCES;

	अगर (ACPI_FAILURE(status)) अणु
		acpi_os_म_लिखो
		    ("Could not convert Buffer to a resource list: %s, %s\n",
		     buffer_arg, acpi_क्रमmat_exception(status));
		जाओ dump_buffer;
	पूर्ण

	/* Now we can dump the resource list */

	acpi_rs_dump_resource_list(ACPI_CAST_PTR(काष्ठा acpi_resource,
						 वापस_buffer.poपूर्णांकer));

dump_buffer:
	acpi_os_म_लिखो("\nRaw data buffer:\n");
	acpi_ut_debug_dump_buffer((u8 *)node->object->buffer.poपूर्णांकer,
				  node->object->buffer.length,
				  DB_BYTE_DISPLAY, ACPI_UINT32_MAX);

	acpi_db_set_output_destination(ACPI_DB_CONSOLE_OUTPUT);
	वापस;
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_dm_compare_aml_resources
 *
 * PARAMETERS:  aml1_buffer         - Contains first resource list
 *              aml1_buffer_length  - Length of first resource list
 *              aml2_buffer         - Contains second resource list
 *              aml2_buffer_length  - Length of second resource list
 *
 * RETURN:      None
 *
 * DESCRIPTION: Compare two AML resource lists, descriptor by descriptor (in
 *              order to isolate a miscompare to an inभागidual resource)
 *
 ******************************************************************************/

अटल व्योम
acpi_dm_compare_aml_resources(u8 *aml1_buffer,
			      acpi_rsdesc_size aml1_buffer_length,
			      u8 *aml2_buffer,
			      acpi_rsdesc_size aml2_buffer_length)
अणु
	u8 *aml1;
	u8 *aml2;
	u8 *aml1_end;
	u8 *aml2_end;
	acpi_rsdesc_size aml1_length;
	acpi_rsdesc_size aml2_length;
	acpi_rsdesc_size offset = 0;
	u8 resource_type;
	u32 count = 0;
	u32 i;

	/* Compare overall buffer sizes (may be dअगरferent due to size rounding) */

	अगर (aml1_buffer_length != aml2_buffer_length) अणु
		acpi_os_म_लिखो("**** Buffer length mismatch in converted "
			       "AML: Original %X, New %X ****\n",
			       aml1_buffer_length, aml2_buffer_length);
	पूर्ण

	aml1 = aml1_buffer;
	aml2 = aml2_buffer;
	aml1_end = aml1_buffer + aml1_buffer_length;
	aml2_end = aml2_buffer + aml2_buffer_length;

	/* Walk the descriptor lists, comparing each descriptor */

	जबतक ((aml1 < aml1_end) && (aml2 < aml2_end)) अणु

		/* Get the lengths of each descriptor */

		aml1_length = acpi_ut_get_descriptor_length(aml1);
		aml2_length = acpi_ut_get_descriptor_length(aml2);
		resource_type = acpi_ut_get_resource_type(aml1);

		/* Check क्रम descriptor length match */

		अगर (aml1_length != aml2_length) अणु
			acpi_os_म_लिखो
			    ("**** Length mismatch in descriptor [%.2X] type %2.2X, "
			     "Offset %8.8X Len1 %X, Len2 %X ****\n", count,
			     resource_type, offset, aml1_length, aml2_length);
		पूर्ण

		/* Check क्रम descriptor byte match */

		अन्यथा अगर (स_भेद(aml1, aml2, aml1_length)) अणु
			acpi_os_म_लिखो
			    ("**** Data mismatch in descriptor [%.2X] type %2.2X, "
			     "Offset %8.8X ****\n", count, resource_type,
			     offset);

			क्रम (i = 0; i < aml1_length; i++) अणु
				अगर (aml1[i] != aml2[i]) अणु
					acpi_os_म_लिखो
					    ("Mismatch at byte offset %.2X: is %2.2X, "
					     "should be %2.2X\n", i, aml2[i],
					     aml1[i]);
				पूर्ण
			पूर्ण
		पूर्ण

		/* Exit on end_tag descriptor */

		अगर (resource_type == ACPI_RESOURCE_NAME_END_TAG) अणु
			वापस;
		पूर्ण

		/* Poपूर्णांक to next descriptor in each buffer */

		count++;
		offset += aml1_length;
		aml1 += aml1_length;
		aml2 += aml2_length;
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_dm_test_resource_conversion
 *
 * PARAMETERS:  node                - Parent device node
 *              name                - resource method name (_CRS)
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Compare the original AML with a conversion of the AML to
 *              पूर्णांकernal resource list, then back to AML.
 *
 ******************************************************************************/

अटल acpi_status
acpi_dm_test_resource_conversion(काष्ठा acpi_namespace_node *node, अक्षर *name)
अणु
	acpi_status status;
	काष्ठा acpi_buffer वापस_buffer;
	काष्ठा acpi_buffer resource_buffer;
	काष्ठा acpi_buffer new_aml;
	जोड़ acpi_object *original_aml;

	acpi_os_म_लिखो("Resource Conversion Comparison:\n");

	new_aml.length = ACPI_ALLOCATE_LOCAL_BUFFER;
	वापस_buffer.length = ACPI_ALLOCATE_LOCAL_BUFFER;
	resource_buffer.length = ACPI_ALLOCATE_LOCAL_BUFFER;

	/* Get the original _CRS AML resource ढाँचा */

	status = acpi_evaluate_object(node, name, शून्य, &वापस_buffer);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_os_म_लिखो("Could not obtain %s: %s\n",
			       name, acpi_क्रमmat_exception(status));
		वापस (status);
	पूर्ण

	/* Get the AML resource ढाँचा, converted to पूर्णांकernal resource काष्ठाs */

	status = acpi_get_current_resources(node, &resource_buffer);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_os_म_लिखो("AcpiGetCurrentResources failed: %s\n",
			       acpi_क्रमmat_exception(status));
		जाओ निकास1;
	पूर्ण

	/* Convert पूर्णांकernal resource list to बाह्यal AML resource ढाँचा */

	status = acpi_rs_create_aml_resources(&resource_buffer, &new_aml);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_os_म_लिखो("AcpiRsCreateAmlResources failed: %s\n",
			       acpi_क्रमmat_exception(status));
		जाओ निकास2;
	पूर्ण

	/* Compare original AML to the newly created AML resource list */

	original_aml = वापस_buffer.poपूर्णांकer;

	acpi_dm_compare_aml_resources(original_aml->buffer.poपूर्णांकer,
				      (acpi_rsdesc_size)original_aml->buffer.
				      length, new_aml.poपूर्णांकer,
				      (acpi_rsdesc_size)new_aml.length);

	/* Cleanup and निकास */

	ACPI_FREE(new_aml.poपूर्णांकer);
निकास2:
	ACPI_FREE(resource_buffer.poपूर्णांकer);
निकास1:
	ACPI_FREE(वापस_buffer.poपूर्णांकer);
	वापस (status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_resource_callback
 *
 * PARAMETERS:  acpi_walk_resource_callback
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Simple callback to exercise acpi_walk_resources and
 *              acpi_walk_resource_buffer.
 *
 ******************************************************************************/

अटल acpi_status
acpi_db_resource_callback(काष्ठा acpi_resource *resource, व्योम *context)
अणु

	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_device_resources
 *
 * PARAMETERS:  acpi_walk_callback
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Display the _PRT/_CRS/_PRS resources क्रम a device object.
 *
 ******************************************************************************/

अटल acpi_status
acpi_db_device_resources(acpi_handle obj_handle,
			 u32 nesting_level, व्योम *context, व्योम **वापस_value)
अणु
	काष्ठा acpi_namespace_node *node;
	काष्ठा acpi_namespace_node *prt_node = शून्य;
	काष्ठा acpi_namespace_node *crs_node = शून्य;
	काष्ठा acpi_namespace_node *prs_node = शून्य;
	काष्ठा acpi_namespace_node *aei_node = शून्य;
	अक्षर *parent_path;
	काष्ठा acpi_buffer वापस_buffer;
	acpi_status status;

	node = ACPI_CAST_PTR(काष्ठा acpi_namespace_node, obj_handle);
	parent_path = acpi_ns_get_normalized_pathname(node, TRUE);
	अगर (!parent_path) अणु
		वापस (AE_NO_MEMORY);
	पूर्ण

	/* Get handles to the resource methods क्रम this device */

	(व्योम)acpi_get_handle(node, METHOD_NAME__PRT,
			      ACPI_CAST_PTR(acpi_handle, &prt_node));
	(व्योम)acpi_get_handle(node, METHOD_NAME__CRS,
			      ACPI_CAST_PTR(acpi_handle, &crs_node));
	(व्योम)acpi_get_handle(node, METHOD_NAME__PRS,
			      ACPI_CAST_PTR(acpi_handle, &prs_node));
	(व्योम)acpi_get_handle(node, METHOD_NAME__AEI,
			      ACPI_CAST_PTR(acpi_handle, &aei_node));

	अगर (!prt_node && !crs_node && !prs_node && !aei_node) अणु
		जाओ cleanup;	/* Nothing to करो */
	पूर्ण

	acpi_os_म_लिखो("\nDevice: %s\n", parent_path);

	/* Prepare क्रम a वापस object of arbitrary size */

	वापस_buffer.poपूर्णांकer = acpi_gbl_db_buffer;
	वापस_buffer.length = ACPI_DEBUG_BUFFER_SIZE;

	/* _PRT */

	अगर (prt_node) अणु
		acpi_os_म_लिखो("Evaluating _PRT\n");

		status =
		    acpi_evaluate_object(prt_node, शून्य, शून्य, &वापस_buffer);
		अगर (ACPI_FAILURE(status)) अणु
			acpi_os_म_लिखो("Could not evaluate _PRT: %s\n",
				       acpi_क्रमmat_exception(status));
			जाओ get_crs;
		पूर्ण

		वापस_buffer.poपूर्णांकer = acpi_gbl_db_buffer;
		वापस_buffer.length = ACPI_DEBUG_BUFFER_SIZE;

		status = acpi_get_irq_routing_table(node, &वापस_buffer);
		अगर (ACPI_FAILURE(status)) अणु
			acpi_os_म_लिखो("GetIrqRoutingTable failed: %s\n",
				       acpi_क्रमmat_exception(status));
			जाओ get_crs;
		पूर्ण

		acpi_rs_dump_irq_list(ACPI_CAST_PTR(u8, acpi_gbl_db_buffer));
	पूर्ण

	/* _CRS */

get_crs:
	अगर (crs_node) अणु
		acpi_os_म_लिखो("Evaluating _CRS\n");

		वापस_buffer.poपूर्णांकer = acpi_gbl_db_buffer;
		वापस_buffer.length = ACPI_DEBUG_BUFFER_SIZE;

		status =
		    acpi_evaluate_object(crs_node, शून्य, शून्य, &वापस_buffer);
		अगर (ACPI_FAILURE(status)) अणु
			acpi_os_म_लिखो("Could not evaluate _CRS: %s\n",
				       acpi_क्रमmat_exception(status));
			जाओ get_prs;
		पूर्ण

		/* This code exercises the acpi_walk_resources पूर्णांकerface */

		status = acpi_walk_resources(node, METHOD_NAME__CRS,
					     acpi_db_resource_callback, शून्य);
		अगर (ACPI_FAILURE(status)) अणु
			acpi_os_म_लिखो("AcpiWalkResources failed: %s\n",
				       acpi_क्रमmat_exception(status));
			जाओ get_prs;
		पूर्ण

		/* Get the _CRS resource list (test ALLOCATE buffer) */

		वापस_buffer.poपूर्णांकer = शून्य;
		वापस_buffer.length = ACPI_ALLOCATE_LOCAL_BUFFER;

		status = acpi_get_current_resources(node, &वापस_buffer);
		अगर (ACPI_FAILURE(status)) अणु
			acpi_os_म_लिखो("AcpiGetCurrentResources failed: %s\n",
				       acpi_क्रमmat_exception(status));
			जाओ get_prs;
		पूर्ण

		/* This code exercises the acpi_walk_resource_buffer पूर्णांकerface */

		status = acpi_walk_resource_buffer(&वापस_buffer,
						   acpi_db_resource_callback,
						   शून्य);
		अगर (ACPI_FAILURE(status)) अणु
			acpi_os_म_लिखो("AcpiWalkResourceBuffer failed: %s\n",
				       acpi_क्रमmat_exception(status));
			जाओ end_crs;
		पूर्ण

		/* Dump the _CRS resource list */

		acpi_rs_dump_resource_list(ACPI_CAST_PTR(काष्ठा acpi_resource,
							 वापस_buffer.
							 poपूर्णांकer));

		/*
		 * Perक्रमm comparison of original AML to newly created AML. This
		 * tests both the AML->Resource conversion and the Resource->AML
		 * conversion.
		 */
		(व्योम)acpi_dm_test_resource_conversion(node, METHOD_NAME__CRS);

		/* Execute _SRS with the resource list */

		acpi_os_म_लिखो("Evaluating _SRS\n");

		status = acpi_set_current_resources(node, &वापस_buffer);
		अगर (ACPI_FAILURE(status)) अणु
			acpi_os_म_लिखो("AcpiSetCurrentResources failed: %s\n",
				       acpi_क्रमmat_exception(status));
			जाओ end_crs;
		पूर्ण

end_crs:
		ACPI_FREE(वापस_buffer.poपूर्णांकer);
	पूर्ण

	/* _PRS */

get_prs:
	अगर (prs_node) अणु
		acpi_os_म_लिखो("Evaluating _PRS\n");

		वापस_buffer.poपूर्णांकer = acpi_gbl_db_buffer;
		वापस_buffer.length = ACPI_DEBUG_BUFFER_SIZE;

		status =
		    acpi_evaluate_object(prs_node, शून्य, शून्य, &वापस_buffer);
		अगर (ACPI_FAILURE(status)) अणु
			acpi_os_म_लिखो("Could not evaluate _PRS: %s\n",
				       acpi_क्रमmat_exception(status));
			जाओ get_aei;
		पूर्ण

		वापस_buffer.poपूर्णांकer = acpi_gbl_db_buffer;
		वापस_buffer.length = ACPI_DEBUG_BUFFER_SIZE;

		status = acpi_get_possible_resources(node, &वापस_buffer);
		अगर (ACPI_FAILURE(status)) अणु
			acpi_os_म_लिखो("AcpiGetPossibleResources failed: %s\n",
				       acpi_क्रमmat_exception(status));
			जाओ get_aei;
		पूर्ण

		acpi_rs_dump_resource_list(ACPI_CAST_PTR
					   (काष्ठा acpi_resource,
					    acpi_gbl_db_buffer));
	पूर्ण

	/* _AEI */

get_aei:
	अगर (aei_node) अणु
		acpi_os_म_लिखो("Evaluating _AEI\n");

		वापस_buffer.poपूर्णांकer = acpi_gbl_db_buffer;
		वापस_buffer.length = ACPI_DEBUG_BUFFER_SIZE;

		status =
		    acpi_evaluate_object(aei_node, शून्य, शून्य, &वापस_buffer);
		अगर (ACPI_FAILURE(status)) अणु
			acpi_os_म_लिखो("Could not evaluate _AEI: %s\n",
				       acpi_क्रमmat_exception(status));
			जाओ cleanup;
		पूर्ण

		वापस_buffer.poपूर्णांकer = acpi_gbl_db_buffer;
		वापस_buffer.length = ACPI_DEBUG_BUFFER_SIZE;

		status = acpi_get_event_resources(node, &वापस_buffer);
		अगर (ACPI_FAILURE(status)) अणु
			acpi_os_म_लिखो("AcpiGetEventResources failed: %s\n",
				       acpi_क्रमmat_exception(status));
			जाओ cleanup;
		पूर्ण

		acpi_rs_dump_resource_list(ACPI_CAST_PTR
					   (काष्ठा acpi_resource,
					    acpi_gbl_db_buffer));
	पूर्ण

cleanup:
	ACPI_FREE(parent_path);
	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_display_resources
 *
 * PARAMETERS:  object_arg          - String object name or object poपूर्णांकer.
 *                                    शून्य or "*" means "display resources क्रम
 *                                    all devices"
 *
 * RETURN:      None
 *
 * DESCRIPTION: Display the resource objects associated with a device.
 *
 ******************************************************************************/

व्योम acpi_db_display_resources(अक्षर *object_arg)
अणु
	काष्ठा acpi_namespace_node *node;

	acpi_db_set_output_destination(ACPI_DB_REसूचीECTABLE_OUTPUT);
	acpi_dbg_level |= ACPI_LV_RESOURCES;

	/* Asterisk means "display resources for all devices" */

	अगर (!object_arg || (!म_भेद(object_arg, "*"))) अणु
		(व्योम)acpi_walk_namespace(ACPI_TYPE_DEVICE, ACPI_ROOT_OBJECT,
					  ACPI_UINT32_MAX,
					  acpi_db_device_resources, शून्य, शून्य,
					  शून्य);
	पूर्ण अन्यथा अणु
		/* Convert string to object poपूर्णांकer */

		node = acpi_db_convert_to_node(object_arg);
		अगर (node) अणु
			अगर (node->type != ACPI_TYPE_DEVICE) अणु
				acpi_os_म_लिखो
				    ("%4.4s: Name is not a device object (%s)\n",
				     node->name.ascii,
				     acpi_ut_get_type_name(node->type));
			पूर्ण अन्यथा अणु
				(व्योम)acpi_db_device_resources(node, 0, शून्य,
							       शून्य);
			पूर्ण
		पूर्ण
	पूर्ण

	acpi_db_set_output_destination(ACPI_DB_CONSOLE_OUTPUT);
पूर्ण

#अगर (!ACPI_REDUCED_HARDWARE)
/*******************************************************************************
 *
 * FUNCTION:    acpi_db_generate_gpe
 *
 * PARAMETERS:  gpe_arg             - Raw GPE number, ascii string
 *              block_arg           - GPE block number, ascii string
 *                                    0 or 1 क्रम FADT GPE blocks
 *
 * RETURN:      None
 *
 * DESCRIPTION: Simulate firing of a GPE
 *
 ******************************************************************************/

व्योम acpi_db_generate_gpe(अक्षर *gpe_arg, अक्षर *block_arg)
अणु
	u32 block_number = 0;
	u32 gpe_number;
	काष्ठा acpi_gpe_event_info *gpe_event_info;

	gpe_number = म_से_अदीर्घ(gpe_arg, शून्य, 0);

	/*
	 * If no block arg, or block arg == 0 or 1, use the FADT-defined
	 * GPE blocks.
	 */
	अगर (block_arg) अणु
		block_number = म_से_अदीर्घ(block_arg, शून्य, 0);
		अगर (block_number == 1) अणु
			block_number = 0;
		पूर्ण
	पूर्ण

	gpe_event_info =
	    acpi_ev_get_gpe_event_info(ACPI_TO_POINTER(block_number),
				       gpe_number);
	अगर (!gpe_event_info) अणु
		acpi_os_म_लिखो("Invalid GPE\n");
		वापस;
	पूर्ण

	(व्योम)acpi_ev_gpe_dispatch(शून्य, gpe_event_info, gpe_number);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_generate_sci
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: Simulate an SCI -- just call the SCI dispatch.
 *
 ******************************************************************************/

व्योम acpi_db_generate_sci(व्योम)
अणु
	acpi_ev_sci_dispatch();
पूर्ण

#पूर्ण_अगर				/* !ACPI_REDUCED_HARDWARE */

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_trace
 *
 * PARAMETERS:  enable_arg          - ENABLE/AML to enable tracer
 *                                    DISABLE to disable tracer
 *              method_arg          - Method to trace
 *              once_arg            - Whether trace once
 *
 * RETURN:      None
 *
 * DESCRIPTION: Control method tracing facility
 *
 ******************************************************************************/

व्योम acpi_db_trace(अक्षर *enable_arg, अक्षर *method_arg, अक्षर *once_arg)
अणु
	u32 debug_level = 0;
	u32 debug_layer = 0;
	u32 flags = 0;

	acpi_ut_strupr(enable_arg);
	acpi_ut_strupr(once_arg);

	अगर (method_arg) अणु
		अगर (acpi_db_trace_method_name) अणु
			ACPI_FREE(acpi_db_trace_method_name);
			acpi_db_trace_method_name = शून्य;
		पूर्ण

		acpi_db_trace_method_name =
		    ACPI_ALLOCATE(म_माप(method_arg) + 1);
		अगर (!acpi_db_trace_method_name) अणु
			acpi_os_म_लिखो("Failed to allocate method name (%s)\n",
				       method_arg);
			वापस;
		पूर्ण

		म_नकल(acpi_db_trace_method_name, method_arg);
	पूर्ण

	अगर (!म_भेद(enable_arg, "ENABLE") ||
	    !म_भेद(enable_arg, "METHOD") || !म_भेद(enable_arg, "OPCODE")) अणु
		अगर (!म_भेद(enable_arg, "ENABLE")) अणु

			/* Inherit current console settings */

			debug_level = acpi_gbl_db_console_debug_level;
			debug_layer = acpi_dbg_layer;
		पूर्ण अन्यथा अणु
			/* Restrict console output to trace poपूर्णांकs only */

			debug_level = ACPI_LV_TRACE_POINT;
			debug_layer = ACPI_EXECUTER;
		पूर्ण

		flags = ACPI_TRACE_ENABLED;

		अगर (!म_भेद(enable_arg, "OPCODE")) अणु
			flags |= ACPI_TRACE_OPCODE;
		पूर्ण

		अगर (once_arg && !म_भेद(once_arg, "ONCE")) अणु
			flags |= ACPI_TRACE_ONESHOT;
		पूर्ण
	पूर्ण

	(व्योम)acpi_debug_trace(acpi_db_trace_method_name,
			       debug_level, debug_layer, flags);
पूर्ण
