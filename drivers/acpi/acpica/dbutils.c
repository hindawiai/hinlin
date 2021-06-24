<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/*******************************************************************************
 *
 * Module Name: dbutils - AML debugger utilities
 *
 ******************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acnamesp.h"
#समावेश "acdebug.h"

#घोषणा _COMPONENT          ACPI_CA_DEBUGGER
ACPI_MODULE_NAME("dbutils")

/* Local prototypes */
#अगर_घोषित ACPI_OBSOLETE_FUNCTIONS
acpi_status acpi_db_second_pass_parse(जोड़ acpi_parse_object *root);

व्योम acpi_db_dump_buffer(u32 address);
#पूर्ण_अगर

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_match_argument
 *
 * PARAMETERS:  user_argument           - User command line
 *              arguments               - Array of commands to match against
 *
 * RETURN:      Index पूर्णांकo command array or ACPI_TYPE_NOT_FOUND अगर not found
 *
 * DESCRIPTION: Search command array क्रम a command match
 *
 ******************************************************************************/

acpi_object_type
acpi_db_match_argument(अक्षर *user_argument,
		       काष्ठा acpi_db_argument_info *arguments)
अणु
	u32 i;

	अगर (!user_argument || user_argument[0] == 0) अणु
		वापस (ACPI_TYPE_NOT_FOUND);
	पूर्ण

	क्रम (i = 0; arguments[i].name; i++) अणु
		अगर (म_माला(ACPI_CAST_PTR(अक्षर, arguments[i].name),
			   ACPI_CAST_PTR(अक्षर,
					 user_argument)) == arguments[i].name) अणु
			वापस (i);
		पूर्ण
	पूर्ण

	/* Argument not recognized */

	वापस (ACPI_TYPE_NOT_FOUND);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_set_output_destination
 *
 * PARAMETERS:  output_flags        - Current flags word
 *
 * RETURN:      None
 *
 * DESCRIPTION: Set the current destination क्रम debugger output. Also sets
 *              the debug output level accordingly.
 *
 ******************************************************************************/

व्योम acpi_db_set_output_destination(u32 output_flags)
अणु

	acpi_gbl_db_output_flags = (u8)output_flags;

	अगर ((output_flags & ACPI_DB_REसूचीECTABLE_OUTPUT) &&
	    acpi_gbl_db_output_to_file) अणु
		acpi_dbg_level = acpi_gbl_db_debug_level;
	पूर्ण अन्यथा अणु
		acpi_dbg_level = acpi_gbl_db_console_debug_level;
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_dump_बाह्यal_object
 *
 * PARAMETERS:  obj_desc        - External ACPI object to dump
 *              level           - Nesting level.
 *
 * RETURN:      None
 *
 * DESCRIPTION: Dump the contents of an ACPI बाह्यal object
 *
 ******************************************************************************/

व्योम acpi_db_dump_बाह्यal_object(जोड़ acpi_object *obj_desc, u32 level)
अणु
	u32 i;

	अगर (!obj_desc) अणु
		acpi_os_म_लिखो("[Null Object]\n");
		वापस;
	पूर्ण

	क्रम (i = 0; i < level; i++) अणु
		acpi_os_म_लिखो(" ");
	पूर्ण

	चयन (obj_desc->type) अणु
	हाल ACPI_TYPE_ANY:

		acpi_os_म_लिखो("[Null Object] (Type=0)\n");
		अवरोध;

	हाल ACPI_TYPE_INTEGER:

		acpi_os_म_लिखो("[Integer] = %8.8X%8.8X\n",
			       ACPI_FORMAT_UINT64(obj_desc->पूर्णांकeger.value));
		अवरोध;

	हाल ACPI_TYPE_STRING:

		acpi_os_म_लिखो("[String] Length %.2X = ",
			       obj_desc->string.length);
		acpi_ut_prपूर्णांक_string(obj_desc->string.poपूर्णांकer, ACPI_UINT8_MAX);
		acpi_os_म_लिखो("\n");
		अवरोध;

	हाल ACPI_TYPE_BUFFER:

		acpi_os_म_लिखो("[Buffer] Length %.2X = ",
			       obj_desc->buffer.length);
		अगर (obj_desc->buffer.length) अणु
			अगर (obj_desc->buffer.length > 16) अणु
				acpi_os_म_लिखो("\n");
			पूर्ण

			acpi_ut_debug_dump_buffer(ACPI_CAST_PTR
						  (u8,
						   obj_desc->buffer.poपूर्णांकer),
						  obj_desc->buffer.length,
						  DB_BYTE_DISPLAY, _COMPONENT);
		पूर्ण अन्यथा अणु
			acpi_os_म_लिखो("\n");
		पूर्ण
		अवरोध;

	हाल ACPI_TYPE_PACKAGE:

		acpi_os_म_लिखो("[Package] Contains %u Elements:\n",
			       obj_desc->package.count);

		क्रम (i = 0; i < obj_desc->package.count; i++) अणु
			acpi_db_dump_बाह्यal_object(&obj_desc->package.
						     elements[i], level + 1);
		पूर्ण
		अवरोध;

	हाल ACPI_TYPE_LOCAL_REFERENCE:

		acpi_os_म_लिखो("[Object Reference] = ");
		acpi_db_display_पूर्णांकernal_object(obj_desc->reference.handle,
						शून्य);
		अवरोध;

	हाल ACPI_TYPE_PROCESSOR:

		acpi_os_म_लिखो("[Processor]\n");
		अवरोध;

	हाल ACPI_TYPE_POWER:

		acpi_os_म_लिखो("[Power Resource]\n");
		अवरोध;

	शेष:

		acpi_os_म_लिखो("[Unknown Type] %X\n", obj_desc->type);
		अवरोध;
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_prep_namestring
 *
 * PARAMETERS:  name            - String to prepare
 *
 * RETURN:      None
 *
 * DESCRIPTION: Translate all क्रमward slashes and करोts to backslashes.
 *
 ******************************************************************************/

व्योम acpi_db_prep_namestring(अक्षर *name)
अणु

	अगर (!name) अणु
		वापस;
	पूर्ण

	acpi_ut_strupr(name);

	/* Convert a leading क्रमward slash to a backslash */

	अगर (*name == '/') अणु
		*name = '\\';
	पूर्ण

	/* Ignore a leading backslash, this is the root prefix */

	अगर (ACPI_IS_ROOT_PREFIX(*name)) अणु
		name++;
	पूर्ण

	/* Convert all slash path separators to करोts */

	जबतक (*name) अणु
		अगर ((*name == '/') || (*name == '\\')) अणु
			*name = '.';
		पूर्ण

		name++;
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_local_ns_lookup
 *
 * PARAMETERS:  name            - Name to lookup
 *
 * RETURN:      Poपूर्णांकer to a namespace node, null on failure
 *
 * DESCRIPTION: Lookup a name in the ACPI namespace
 *
 * Note: Currently begins search from the root. Could be enhanced to use
 * the current prefix (scope) node as the search beginning poपूर्णांक.
 *
 ******************************************************************************/

काष्ठा acpi_namespace_node *acpi_db_local_ns_lookup(अक्षर *name)
अणु
	अक्षर *पूर्णांकernal_path;
	acpi_status status;
	काष्ठा acpi_namespace_node *node = शून्य;

	acpi_db_prep_namestring(name);

	/* Build an पूर्णांकernal namestring */

	status = acpi_ns_पूर्णांकernalize_name(name, &पूर्णांकernal_path);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_os_म_लिखो("Invalid namestring: %s\n", name);
		वापस (शून्य);
	पूर्ण

	/*
	 * Lookup the name.
	 * (Uses root node as the search starting poपूर्णांक)
	 */
	status = acpi_ns_lookup(शून्य, पूर्णांकernal_path, ACPI_TYPE_ANY,
				ACPI_IMODE_EXECUTE,
				ACPI_NS_NO_UPSEARCH | ACPI_NS_DONT_OPEN_SCOPE,
				शून्य, &node);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_os_म_लिखो("Could not locate name: %s, %s\n",
			       name, acpi_क्रमmat_exception(status));
	पूर्ण

	ACPI_FREE(पूर्णांकernal_path);
	वापस (node);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_uपूर्णांक32_to_hex_string
 *
 * PARAMETERS:  value           - The value to be converted to string
 *              buffer          - Buffer क्रम result (not less than 11 bytes)
 *
 * RETURN:      None
 *
 * DESCRIPTION: Convert the अचिन्हित 32-bit value to the hexadecimal image
 *
 * NOTE: It is the caller's responsibility to ensure that the length of buffer
 *       is sufficient.
 *
 ******************************************************************************/

व्योम acpi_db_uपूर्णांक32_to_hex_string(u32 value, अक्षर *buffer)
अणु
	पूर्णांक i;

	अगर (value == 0) अणु
		म_नकल(buffer, "0");
		वापस;
	पूर्ण

	buffer[8] = '\0';

	क्रम (i = 7; i >= 0; i--) अणु
		buffer[i] = acpi_gbl_upper_hex_digits[value & 0x0F];
		value = value >> 4;
	पूर्ण
पूर्ण

#अगर_घोषित ACPI_OBSOLETE_FUNCTIONS
/*******************************************************************************
 *
 * FUNCTION:    acpi_db_second_pass_parse
 *
 * PARAMETERS:  root            - Root of the parse tree
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Second pass parse of the ACPI tables. We need to रुको until
 *              second pass to parse the control methods
 *
 ******************************************************************************/

acpi_status acpi_db_second_pass_parse(जोड़ acpi_parse_object *root)
अणु
	जोड़ acpi_parse_object *op = root;
	जोड़ acpi_parse_object *method;
	जोड़ acpi_parse_object *search_op;
	जोड़ acpi_parse_object *start_op;
	acpi_status status = AE_OK;
	u32 base_aml_offset;
	काष्ठा acpi_walk_state *walk_state;

	ACPI_FUNCTION_ENTRY();

	acpi_os_म_लिखो("Pass two parse ....\n");

	जबतक (op) अणु
		अगर (op->common.aml_opcode == AML_METHOD_OP) अणु
			method = op;

			/* Create a new walk state क्रम the parse */

			walk_state =
			    acpi_ds_create_walk_state(0, शून्य, शून्य, शून्य);
			अगर (!walk_state) अणु
				वापस (AE_NO_MEMORY);
			पूर्ण

			/* Init the Walk State */

			walk_state->parser_state.aml =
			    walk_state->parser_state.aml_start =
			    method->named.data;
			walk_state->parser_state.aml_end =
			    walk_state->parser_state.pkg_end =
			    method->named.data + method->named.length;
			walk_state->parser_state.start_scope = op;

			walk_state->descending_callback =
			    acpi_ds_load1_begin_op;
			walk_state->ascending_callback = acpi_ds_load1_end_op;

			/* Perक्रमm the AML parse */

			status = acpi_ps_parse_aml(walk_state);

			base_aml_offset =
			    (method->common.value.arg)->common.aml_offset + 1;
			start_op = (method->common.value.arg)->common.next;
			search_op = start_op;

			जबतक (search_op) अणु
				search_op->common.aml_offset += base_aml_offset;
				search_op =
				    acpi_ps_get_depth_next(start_op, search_op);
			पूर्ण
		पूर्ण

		अगर (op->common.aml_opcode == AML_REGION_OP) अणु

			/* TBD: [Investigate] this isn't quite the right thing to करो! */
			/*
			 *
			 * Method = (ACPI_DEFERRED_OP *) Op;
			 * Status = acpi_ps_parse_aml (Op, Method->Body, Method->body_length);
			 */
		पूर्ण

		अगर (ACPI_FAILURE(status)) अणु
			अवरोध;
		पूर्ण

		op = acpi_ps_get_depth_next(root, op);
	पूर्ण

	वापस (status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_dump_buffer
 *
 * PARAMETERS:  address             - Poपूर्णांकer to the buffer
 *
 * RETURN:      None
 *
 * DESCRIPTION: Prपूर्णांक a portion of a buffer
 *
 ******************************************************************************/

व्योम acpi_db_dump_buffer(u32 address)
अणु

	acpi_os_म_लिखो("\nLocation %X:\n", address);

	acpi_dbg_level |= ACPI_LV_TABLES;
	acpi_ut_debug_dump_buffer(ACPI_TO_POINTER(address), 64, DB_BYTE_DISPLAY,
				  ACPI_UINT32_MAX);
पूर्ण
#पूर्ण_अगर
