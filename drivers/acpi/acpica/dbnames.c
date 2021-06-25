<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/*******************************************************************************
 *
 * Module Name: dbnames - Debugger commands क्रम the acpi namespace
 *
 ******************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acnamesp.h"
#समावेश "acdebug.h"
#समावेश "acpredef.h"
#समावेश "acinterp.h"

#घोषणा _COMPONENT          ACPI_CA_DEBUGGER
ACPI_MODULE_NAME("dbnames")

/* Local prototypes */
अटल acpi_status
acpi_db_walk_and_match_name(acpi_handle obj_handle,
			    u32 nesting_level,
			    व्योम *context, व्योम **वापस_value);

अटल acpi_status
acpi_db_walk_क्रम_predefined_names(acpi_handle obj_handle,
				  u32 nesting_level,
				  व्योम *context, व्योम **वापस_value);

अटल acpi_status
acpi_db_walk_क्रम_specअगरic_objects(acpi_handle obj_handle,
				  u32 nesting_level,
				  व्योम *context, व्योम **वापस_value);

अटल acpi_status
acpi_db_walk_क्रम_object_counts(acpi_handle obj_handle,
			       u32 nesting_level,
			       व्योम *context, व्योम **वापस_value);

अटल acpi_status
acpi_db_पूर्णांकegrity_walk(acpi_handle obj_handle,
		       u32 nesting_level, व्योम *context, व्योम **वापस_value);

अटल acpi_status
acpi_db_walk_क्रम_references(acpi_handle obj_handle,
			    u32 nesting_level,
			    व्योम *context, व्योम **वापस_value);

अटल acpi_status
acpi_db_bus_walk(acpi_handle obj_handle,
		 u32 nesting_level, व्योम *context, व्योम **वापस_value);

/*
 * Arguments क्रम the Objects command
 * These object types map directly to the ACPI_TYPES
 */
अटल काष्ठा acpi_db_argument_info acpi_db_object_types[] = अणु
	अणु"ANY"पूर्ण,
	अणु"INTEGERS"पूर्ण,
	अणु"STRINGS"पूर्ण,
	अणु"BUFFERS"पूर्ण,
	अणु"PACKAGES"पूर्ण,
	अणु"FIELDS"पूर्ण,
	अणु"DEVICES"पूर्ण,
	अणु"EVENTS"पूर्ण,
	अणु"METHODS"पूर्ण,
	अणु"MUTEXES"पूर्ण,
	अणु"REGIONS"पूर्ण,
	अणु"POWERRESOURCES"पूर्ण,
	अणु"PROCESSORS"पूर्ण,
	अणु"THERMALZONES"पूर्ण,
	अणु"BUFFERFIELDS"पूर्ण,
	अणु"DDBHANDLES"पूर्ण,
	अणु"DEBUG"पूर्ण,
	अणु"REGIONFIELDS"पूर्ण,
	अणु"BANKFIELDS"पूर्ण,
	अणु"INDEXFIELDS"पूर्ण,
	अणु"REFERENCES"पूर्ण,
	अणु"ALIASES"पूर्ण,
	अणु"METHODALIASES"पूर्ण,
	अणु"NOTIFY"पूर्ण,
	अणु"ADDRESSHANDLER"पूर्ण,
	अणु"RESOURCE"पूर्ण,
	अणु"RESOURCEFIELD"पूर्ण,
	अणु"SCOPES"पूर्ण,
	अणुशून्यपूर्ण			/* Must be null terminated */
पूर्ण;

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_set_scope
 *
 * PARAMETERS:  name                - New scope path
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Set the "current scope" as मुख्यtained by this utility.
 *              The scope is used as a prefix to ACPI paths.
 *
 ******************************************************************************/

व्योम acpi_db_set_scope(अक्षर *name)
अणु
	acpi_status status;
	काष्ठा acpi_namespace_node *node;

	अगर (!name || name[0] == 0) अणु
		acpi_os_म_लिखो("Current scope: %s\n", acpi_gbl_db_scope_buf);
		वापस;
	पूर्ण

	acpi_db_prep_namestring(name);

	अगर (ACPI_IS_ROOT_PREFIX(name[0])) अणु

		/* Validate new scope from the root */

		status = acpi_ns_get_node(acpi_gbl_root_node, name,
					  ACPI_NS_NO_UPSEARCH, &node);
		अगर (ACPI_FAILURE(status)) अणु
			जाओ error_निकास;
		पूर्ण

		acpi_gbl_db_scope_buf[0] = 0;
	पूर्ण अन्यथा अणु
		/* Validate new scope relative to old scope */

		status = acpi_ns_get_node(acpi_gbl_db_scope_node, name,
					  ACPI_NS_NO_UPSEARCH, &node);
		अगर (ACPI_FAILURE(status)) अणु
			जाओ error_निकास;
		पूर्ण
	पूर्ण

	/* Build the final pathname */

	अगर (acpi_ut_safe_म_जोड़ो
	    (acpi_gbl_db_scope_buf, माप(acpi_gbl_db_scope_buf), name)) अणु
		status = AE_BUFFER_OVERFLOW;
		जाओ error_निकास;
	पूर्ण

	अगर (acpi_ut_safe_म_जोड़ो
	    (acpi_gbl_db_scope_buf, माप(acpi_gbl_db_scope_buf), "\\")) अणु
		status = AE_BUFFER_OVERFLOW;
		जाओ error_निकास;
	पूर्ण

	acpi_gbl_db_scope_node = node;
	acpi_os_म_लिखो("New scope: %s\n", acpi_gbl_db_scope_buf);
	वापस;

error_निकास:

	acpi_os_म_लिखो("Could not attach scope: %s, %s\n",
		       name, acpi_क्रमmat_exception(status));
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_dump_namespace
 *
 * PARAMETERS:  start_arg       - Node to begin namespace dump
 *              depth_arg       - Maximum tree depth to be dumped
 *
 * RETURN:      None
 *
 * DESCRIPTION: Dump entire namespace or a subtree. Each node is displayed
 *              with type and other inक्रमmation.
 *
 ******************************************************************************/

व्योम acpi_db_dump_namespace(अक्षर *start_arg, अक्षर *depth_arg)
अणु
	acpi_handle subtree_entry = acpi_gbl_root_node;
	u32 max_depth = ACPI_UINT32_MAX;

	/* No argument given, just start at the root and dump entire namespace */

	अगर (start_arg) अणु
		subtree_entry = acpi_db_convert_to_node(start_arg);
		अगर (!subtree_entry) अणु
			वापस;
		पूर्ण

		/* Now we can check क्रम the depth argument */

		अगर (depth_arg) अणु
			max_depth = म_से_अदीर्घ(depth_arg, शून्य, 0);
		पूर्ण
	पूर्ण

	acpi_db_set_output_destination(ACPI_DB_DUPLICATE_OUTPUT);

	अगर (((काष्ठा acpi_namespace_node *)subtree_entry)->parent) अणु
		acpi_os_म_लिखो("ACPI Namespace (from %4.4s (%p) subtree):\n",
			       ((काष्ठा acpi_namespace_node *)subtree_entry)->
			       name.ascii, subtree_entry);
	पूर्ण अन्यथा अणु
		acpi_os_म_लिखो("ACPI Namespace (from %s):\n",
			       ACPI_NAMESPACE_ROOT);
	पूर्ण

	/* Display the subtree */

	acpi_db_set_output_destination(ACPI_DB_REसूचीECTABLE_OUTPUT);
	acpi_ns_dump_objects(ACPI_TYPE_ANY, ACPI_DISPLAY_SUMMARY, max_depth,
			     ACPI_OWNER_ID_MAX, subtree_entry);
	acpi_db_set_output_destination(ACPI_DB_CONSOLE_OUTPUT);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_dump_namespace_paths
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: Dump entire namespace with full object pathnames and object
 *              type inक्रमmation. Alternative to "namespace" command.
 *
 ******************************************************************************/

व्योम acpi_db_dump_namespace_paths(व्योम)
अणु

	acpi_db_set_output_destination(ACPI_DB_DUPLICATE_OUTPUT);
	acpi_os_म_लिखो("ACPI Namespace (from root):\n");

	/* Display the entire namespace */

	acpi_db_set_output_destination(ACPI_DB_REसूचीECTABLE_OUTPUT);
	acpi_ns_dump_object_paths(ACPI_TYPE_ANY, ACPI_DISPLAY_SUMMARY,
				  ACPI_UINT32_MAX, ACPI_OWNER_ID_MAX,
				  acpi_gbl_root_node);

	acpi_db_set_output_destination(ACPI_DB_CONSOLE_OUTPUT);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_dump_namespace_by_owner
 *
 * PARAMETERS:  owner_arg       - Owner ID whose nodes will be displayed
 *              depth_arg       - Maximum tree depth to be dumped
 *
 * RETURN:      None
 *
 * DESCRIPTION: Dump elements of the namespace that are owned by the owner_id.
 *
 ******************************************************************************/

व्योम acpi_db_dump_namespace_by_owner(अक्षर *owner_arg, अक्षर *depth_arg)
अणु
	acpi_handle subtree_entry = acpi_gbl_root_node;
	u32 max_depth = ACPI_UINT32_MAX;
	acpi_owner_id owner_id;

	owner_id = (acpi_owner_id)म_से_अदीर्घ(owner_arg, शून्य, 0);

	/* Now we can check क्रम the depth argument */

	अगर (depth_arg) अणु
		max_depth = म_से_अदीर्घ(depth_arg, शून्य, 0);
	पूर्ण

	acpi_db_set_output_destination(ACPI_DB_DUPLICATE_OUTPUT);
	acpi_os_म_लिखो("ACPI Namespace by owner %X:\n", owner_id);

	/* Display the subtree */

	acpi_db_set_output_destination(ACPI_DB_REसूचीECTABLE_OUTPUT);
	acpi_ns_dump_objects(ACPI_TYPE_ANY, ACPI_DISPLAY_SUMMARY, max_depth,
			     owner_id, subtree_entry);
	acpi_db_set_output_destination(ACPI_DB_CONSOLE_OUTPUT);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_walk_and_match_name
 *
 * PARAMETERS:  Callback from walk_namespace
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Find a particular name/names within the namespace. Wildcards
 *              are supported -- '?' matches any अक्षरacter.
 *
 ******************************************************************************/

अटल acpi_status
acpi_db_walk_and_match_name(acpi_handle obj_handle,
			    u32 nesting_level,
			    व्योम *context, व्योम **वापस_value)
अणु
	acpi_status status;
	अक्षर *requested_name = (अक्षर *)context;
	u32 i;
	काष्ठा acpi_buffer buffer;
	काष्ठा acpi_walk_info info;

	/* Check क्रम a name match */

	क्रम (i = 0; i < 4; i++) अणु

		/* Wildcard support */

		अगर ((requested_name[i] != '?') &&
		    (requested_name[i] != ((काष्ठा acpi_namespace_node *)
					   obj_handle)->name.ascii[i])) अणु

			/* No match, just निकास */

			वापस (AE_OK);
		पूर्ण
	पूर्ण

	/* Get the full pathname to this object */

	buffer.length = ACPI_ALLOCATE_LOCAL_BUFFER;
	status = acpi_ns_handle_to_pathname(obj_handle, &buffer, TRUE);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_os_म_लिखो("Could Not get pathname for object %p\n",
			       obj_handle);
	पूर्ण अन्यथा अणु
		info.count = 0;
		info.owner_id = ACPI_OWNER_ID_MAX;
		info.debug_level = ACPI_UINT32_MAX;
		info.display_type = ACPI_DISPLAY_SUMMARY | ACPI_DISPLAY_SHORT;

		acpi_os_म_लिखो("%32s", (अक्षर *)buffer.poपूर्णांकer);
		(व्योम)acpi_ns_dump_one_object(obj_handle, nesting_level, &info,
					      शून्य);
		ACPI_FREE(buffer.poपूर्णांकer);
	पूर्ण

	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_find_name_in_namespace
 *
 * PARAMETERS:  name_arg        - The 4-अक्षरacter ACPI name to find.
 *                                wildcards are supported.
 *
 * RETURN:      None
 *
 * DESCRIPTION: Search the namespace क्रम a given name (with wildcards)
 *
 ******************************************************************************/

acpi_status acpi_db_find_name_in_namespace(अक्षर *name_arg)
अणु
	अक्षर acpi_name[5] = "____";
	अक्षर *acpi_name_ptr = acpi_name;

	अगर (म_माप(name_arg) > ACPI_NAMESEG_SIZE) अणु
		acpi_os_म_लिखो("Name must be no longer than 4 characters\n");
		वापस (AE_OK);
	पूर्ण

	/* Pad out name with underscores as necessary to create a 4-अक्षर name */

	acpi_ut_strupr(name_arg);
	जबतक (*name_arg) अणु
		*acpi_name_ptr = *name_arg;
		acpi_name_ptr++;
		name_arg++;
	पूर्ण

	/* Walk the namespace from the root */

	(व्योम)acpi_walk_namespace(ACPI_TYPE_ANY, ACPI_ROOT_OBJECT,
				  ACPI_UINT32_MAX, acpi_db_walk_and_match_name,
				  शून्य, acpi_name, शून्य);

	acpi_db_set_output_destination(ACPI_DB_CONSOLE_OUTPUT);
	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_walk_क्रम_predefined_names
 *
 * PARAMETERS:  Callback from walk_namespace
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Detect and display predefined ACPI names (names that start with
 *              an underscore)
 *
 ******************************************************************************/

अटल acpi_status
acpi_db_walk_क्रम_predefined_names(acpi_handle obj_handle,
				  u32 nesting_level,
				  व्योम *context, व्योम **वापस_value)
अणु
	काष्ठा acpi_namespace_node *node =
	    (काष्ठा acpi_namespace_node *)obj_handle;
	u32 *count = (u32 *)context;
	स्थिर जोड़ acpi_predefined_info *predefined;
	स्थिर जोड़ acpi_predefined_info *package = शून्य;
	अक्षर *pathname;
	अक्षर string_buffer[48];

	predefined = acpi_ut_match_predefined_method(node->name.ascii);
	अगर (!predefined) अणु
		वापस (AE_OK);
	पूर्ण

	pathname = acpi_ns_get_normalized_pathname(node, TRUE);
	अगर (!pathname) अणु
		वापस (AE_OK);
	पूर्ण

	/* If method वापसs a package, the info is in the next table entry */

	अगर (predefined->info.expected_btypes & ACPI_RTYPE_PACKAGE) अणु
		package = predefined + 1;
	पूर्ण

	acpi_ut_get_expected_वापस_types(string_buffer,
					  predefined->info.expected_btypes);

	acpi_os_म_लिखो("%-32s Arguments %X, Return Types: %s", pathname,
		       METHOD_GET_ARG_COUNT(predefined->info.argument_list),
		       string_buffer);

	अगर (package) अणु
		acpi_os_म_लिखो(" (PkgType %2.2X, ObjType %2.2X, Count %2.2X)",
			       package->ret_info.type,
			       package->ret_info.object_type1,
			       package->ret_info.count1);
	पूर्ण

	acpi_os_म_लिखो("\n");

	/* Check that the declared argument count matches the ACPI spec */

	acpi_ns_check_acpi_compliance(pathname, node, predefined);

	ACPI_FREE(pathname);
	(*count)++;
	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_check_predefined_names
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: Validate all predefined names in the namespace
 *
 ******************************************************************************/

व्योम acpi_db_check_predefined_names(व्योम)
अणु
	u32 count = 0;

	/* Search all nodes in namespace */

	(व्योम)acpi_walk_namespace(ACPI_TYPE_ANY, ACPI_ROOT_OBJECT,
				  ACPI_UINT32_MAX,
				  acpi_db_walk_क्रम_predefined_names, शून्य,
				  (व्योम *)&count, शून्य);

	acpi_os_म_लिखो("Found %u predefined names in the namespace\n", count);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_walk_क्रम_object_counts
 *
 * PARAMETERS:  Callback from walk_namespace
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Display लघु info about objects in the namespace
 *
 ******************************************************************************/

अटल acpi_status
acpi_db_walk_क्रम_object_counts(acpi_handle obj_handle,
			       u32 nesting_level,
			       व्योम *context, व्योम **वापस_value)
अणु
	काष्ठा acpi_object_info *info = (काष्ठा acpi_object_info *)context;
	काष्ठा acpi_namespace_node *node =
	    (काष्ठा acpi_namespace_node *)obj_handle;

	अगर (node->type > ACPI_TYPE_NS_NODE_MAX) अणु
		acpi_os_म_लिखो("[%4.4s]: Unknown object type %X\n",
			       node->name.ascii, node->type);
	पूर्ण अन्यथा अणु
		info->types[node->type]++;
	पूर्ण

	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_walk_क्रम_fields
 *
 * PARAMETERS:  Callback from walk_namespace
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Display लघु info about objects in the namespace
 *
 ******************************************************************************/

अटल acpi_status
acpi_db_walk_क्रम_fields(acpi_handle obj_handle,
			u32 nesting_level, व्योम *context, व्योम **वापस_value)
अणु
	जोड़ acpi_object *ret_value;
	काष्ठा acpi_region_walk_info *info =
	    (काष्ठा acpi_region_walk_info *)context;
	काष्ठा acpi_buffer buffer;
	acpi_status status;
	काष्ठा acpi_namespace_node *node = acpi_ns_validate_handle(obj_handle);

	अगर (!node) अणु
		वापस (AE_OK);
	पूर्ण
	अगर (node->object->field.region_obj->region.space_id !=
	    info->address_space_id) अणु
		वापस (AE_OK);
	पूर्ण

	info->count++;

	/* Get and display the full pathname to this object */

	buffer.length = ACPI_ALLOCATE_LOCAL_BUFFER;
	status = acpi_ns_handle_to_pathname(obj_handle, &buffer, TRUE);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_os_म_लिखो("Could Not get pathname for object %p\n",
			       obj_handle);
		वापस (AE_OK);
	पूर्ण

	acpi_os_म_लिखो("%s ", (अक्षर *)buffer.poपूर्णांकer);
	ACPI_FREE(buffer.poपूर्णांकer);

	buffer.length = ACPI_ALLOCATE_LOCAL_BUFFER;
	acpi_evaluate_object(obj_handle, शून्य, शून्य, &buffer);

	/*
	 * Since this is a field unit, surround the output in braces
	 */
	acpi_os_म_लिखो("{");

	ret_value = (जोड़ acpi_object *)buffer.poपूर्णांकer;
	चयन (ret_value->type) अणु
	हाल ACPI_TYPE_INTEGER:

		acpi_os_म_लिखो("%8.8X%8.8X",
			       ACPI_FORMAT_UINT64(ret_value->पूर्णांकeger.value));
		अवरोध;

	हाल ACPI_TYPE_BUFFER:

		acpi_ut_dump_buffer(ret_value->buffer.poपूर्णांकer,
				    ret_value->buffer.length,
				    DB_DISPLAY_DATA_ONLY | DB_BYTE_DISPLAY, 0);
		अवरोध;

	शेष:

		अवरोध;
	पूर्ण
	acpi_os_म_लिखो("}\n");

	ACPI_FREE(buffer.poपूर्णांकer);

	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_walk_क्रम_specअगरic_objects
 *
 * PARAMETERS:  Callback from walk_namespace
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Display लघु info about objects in the namespace
 *
 ******************************************************************************/

अटल acpi_status
acpi_db_walk_क्रम_specअगरic_objects(acpi_handle obj_handle,
				  u32 nesting_level,
				  व्योम *context, व्योम **वापस_value)
अणु
	काष्ठा acpi_walk_info *info = (काष्ठा acpi_walk_info *)context;
	काष्ठा acpi_buffer buffer;
	acpi_status status;

	info->count++;

	/* Get and display the full pathname to this object */

	buffer.length = ACPI_ALLOCATE_LOCAL_BUFFER;
	status = acpi_ns_handle_to_pathname(obj_handle, &buffer, TRUE);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_os_म_लिखो("Could Not get pathname for object %p\n",
			       obj_handle);
		वापस (AE_OK);
	पूर्ण

	acpi_os_म_लिखो("%32s", (अक्षर *)buffer.poपूर्णांकer);
	ACPI_FREE(buffer.poपूर्णांकer);

	/* Dump लघु info about the object */

	(व्योम)acpi_ns_dump_one_object(obj_handle, nesting_level, info, शून्य);
	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_display_objects
 *
 * PARAMETERS:  obj_type_arg        - Type of object to display
 *              display_count_arg   - Max depth to display
 *
 * RETURN:      None
 *
 * DESCRIPTION: Display objects in the namespace of the requested type
 *
 ******************************************************************************/

acpi_status acpi_db_display_objects(अक्षर *obj_type_arg, अक्षर *display_count_arg)
अणु
	काष्ठा acpi_walk_info info;
	acpi_object_type type;
	काष्ठा acpi_object_info *object_info;
	u32 i;
	u32 total_objects = 0;

	/* No argument means display summary/count of all object types */

	अगर (!obj_type_arg) अणु
		object_info =
		    ACPI_ALLOCATE_ZEROED(माप(काष्ठा acpi_object_info));

		/* Walk the namespace from the root */

		(व्योम)acpi_walk_namespace(ACPI_TYPE_ANY, ACPI_ROOT_OBJECT,
					  ACPI_UINT32_MAX,
					  acpi_db_walk_क्रम_object_counts, शून्य,
					  (व्योम *)object_info, शून्य);

		acpi_os_म_लिखो("\nSummary of namespace objects:\n\n");

		क्रम (i = 0; i < ACPI_TOTAL_TYPES; i++) अणु
			acpi_os_म_लिखो("%8u %s\n", object_info->types[i],
				       acpi_ut_get_type_name(i));

			total_objects += object_info->types[i];
		पूर्ण

		acpi_os_म_लिखो("\n%8u Total namespace objects\n\n",
			       total_objects);

		ACPI_FREE(object_info);
		वापस (AE_OK);
	पूर्ण

	/* Get the object type */

	type = acpi_db_match_argument(obj_type_arg, acpi_db_object_types);
	अगर (type == ACPI_TYPE_NOT_FOUND) अणु
		acpi_os_म_लिखो("Invalid or unsupported argument\n");
		वापस (AE_OK);
	पूर्ण

	acpi_db_set_output_destination(ACPI_DB_DUPLICATE_OUTPUT);
	acpi_os_म_लिखो
	    ("Objects of type [%s] defined in the current ACPI Namespace:\n",
	     acpi_ut_get_type_name(type));

	acpi_db_set_output_destination(ACPI_DB_REसूचीECTABLE_OUTPUT);

	info.count = 0;
	info.owner_id = ACPI_OWNER_ID_MAX;
	info.debug_level = ACPI_UINT32_MAX;
	info.display_type = ACPI_DISPLAY_SUMMARY | ACPI_DISPLAY_SHORT;

	/* Walk the namespace from the root */

	(व्योम)acpi_walk_namespace(type, ACPI_ROOT_OBJECT, ACPI_UINT32_MAX,
				  acpi_db_walk_क्रम_specअगरic_objects, शून्य,
				  (व्योम *)&info, शून्य);

	acpi_os_म_लिखो
	    ("\nFound %u objects of type [%s] in the current ACPI Namespace\n",
	     info.count, acpi_ut_get_type_name(type));

	acpi_db_set_output_destination(ACPI_DB_CONSOLE_OUTPUT);
	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_display_fields
 *
 * PARAMETERS:  obj_type_arg        - Type of object to display
 *              display_count_arg   - Max depth to display
 *
 * RETURN:      None
 *
 * DESCRIPTION: Display objects in the namespace of the requested type
 *
 ******************************************************************************/

acpi_status acpi_db_display_fields(u32 address_space_id)
अणु
	काष्ठा acpi_region_walk_info info;

	info.count = 0;
	info.owner_id = ACPI_OWNER_ID_MAX;
	info.debug_level = ACPI_UINT32_MAX;
	info.display_type = ACPI_DISPLAY_SUMMARY | ACPI_DISPLAY_SHORT;
	info.address_space_id = address_space_id;

	/* Walk the namespace from the root */

	(व्योम)acpi_walk_namespace(ACPI_TYPE_LOCAL_REGION_FIELD,
				  ACPI_ROOT_OBJECT, ACPI_UINT32_MAX,
				  acpi_db_walk_क्रम_fields, शून्य, (व्योम *)&info,
				  शून्य);

	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_पूर्णांकegrity_walk
 *
 * PARAMETERS:  Callback from walk_namespace
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Examine one NS node क्रम valid values.
 *
 ******************************************************************************/

अटल acpi_status
acpi_db_पूर्णांकegrity_walk(acpi_handle obj_handle,
		       u32 nesting_level, व्योम *context, व्योम **वापस_value)
अणु
	काष्ठा acpi_पूर्णांकegrity_info *info =
	    (काष्ठा acpi_पूर्णांकegrity_info *)context;
	काष्ठा acpi_namespace_node *node =
	    (काष्ठा acpi_namespace_node *)obj_handle;
	जोड़ acpi_opeअक्रम_object *object;
	u8 alias = TRUE;

	info->nodes++;

	/* Verअगरy the NS node, and dereference aliases */

	जबतक (alias) अणु
		अगर (ACPI_GET_DESCRIPTOR_TYPE(node) != ACPI_DESC_TYPE_NAMED) अणु
			acpi_os_म_लिखो
			    ("Invalid Descriptor Type for Node %p [%s] - "
			     "is %2.2X should be %2.2X\n", node,
			     acpi_ut_get_descriptor_name(node),
			     ACPI_GET_DESCRIPTOR_TYPE(node),
			     ACPI_DESC_TYPE_NAMED);
			वापस (AE_OK);
		पूर्ण

		अगर ((node->type == ACPI_TYPE_LOCAL_ALIAS) ||
		    (node->type == ACPI_TYPE_LOCAL_METHOD_ALIAS)) अणु
			node = (काष्ठा acpi_namespace_node *)node->object;
		पूर्ण अन्यथा अणु
			alias = FALSE;
		पूर्ण
	पूर्ण

	अगर (node->type > ACPI_TYPE_LOCAL_MAX) अणु
		acpi_os_म_लिखो("Invalid Object Type for Node %p, Type = %X\n",
			       node, node->type);
		वापस (AE_OK);
	पूर्ण

	अगर (!acpi_ut_valid_nameseg(node->name.ascii)) अणु
		acpi_os_म_लिखो("Invalid AcpiName for Node %p\n", node);
		वापस (AE_OK);
	पूर्ण

	object = acpi_ns_get_attached_object(node);
	अगर (object) अणु
		info->objects++;
		अगर (ACPI_GET_DESCRIPTOR_TYPE(object) != ACPI_DESC_TYPE_OPERAND) अणु
			acpi_os_म_लिखो
			    ("Invalid Descriptor Type for Object %p [%s]\n",
			     object, acpi_ut_get_descriptor_name(object));
		पूर्ण
	पूर्ण

	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_check_पूर्णांकegrity
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: Check entire namespace क्रम data काष्ठाure पूर्णांकegrity
 *
 ******************************************************************************/

व्योम acpi_db_check_पूर्णांकegrity(व्योम)
अणु
	काष्ठा acpi_पूर्णांकegrity_info info = अणु 0, 0 पूर्ण;

	/* Search all nodes in namespace */

	(व्योम)acpi_walk_namespace(ACPI_TYPE_ANY, ACPI_ROOT_OBJECT,
				  ACPI_UINT32_MAX, acpi_db_पूर्णांकegrity_walk, शून्य,
				  (व्योम *)&info, शून्य);

	acpi_os_म_लिखो("Verified %u namespace nodes with %u Objects\n",
		       info.nodes, info.objects);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_walk_क्रम_references
 *
 * PARAMETERS:  Callback from walk_namespace
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Check अगर this namespace object refers to the target object
 *              that is passed in as the context value.
 *
 * Note: Currently करोesn't check subobjects within the Node's object
 *
 ******************************************************************************/

अटल acpi_status
acpi_db_walk_क्रम_references(acpi_handle obj_handle,
			    u32 nesting_level,
			    व्योम *context, व्योम **वापस_value)
अणु
	जोड़ acpi_opeअक्रम_object *obj_desc =
	    (जोड़ acpi_opeअक्रम_object *)context;
	काष्ठा acpi_namespace_node *node =
	    (काष्ठा acpi_namespace_node *)obj_handle;

	/* Check क्रम match against the namespace node itself */

	अगर (node == (व्योम *)obj_desc) अणु
		acpi_os_म_लिखो("Object is a Node [%4.4s]\n",
			       acpi_ut_get_node_name(node));
	पूर्ण

	/* Check क्रम match against the object attached to the node */

	अगर (acpi_ns_get_attached_object(node) == obj_desc) अणु
		acpi_os_म_लिखो("Reference at Node->Object %p [%4.4s]\n",
			       node, acpi_ut_get_node_name(node));
	पूर्ण

	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_find_references
 *
 * PARAMETERS:  object_arg      - String with hex value of the object
 *
 * RETURN:      None
 *
 * DESCRIPTION: Search namespace क्रम all references to the input object
 *
 ******************************************************************************/

व्योम acpi_db_find_references(अक्षर *object_arg)
अणु
	जोड़ acpi_opeअक्रम_object *obj_desc;
	acpi_size address;

	/* Convert string to object poपूर्णांकer */

	address = म_से_अदीर्घ(object_arg, शून्य, 16);
	obj_desc = ACPI_TO_POINTER(address);

	/* Search all nodes in namespace */

	(व्योम)acpi_walk_namespace(ACPI_TYPE_ANY, ACPI_ROOT_OBJECT,
				  ACPI_UINT32_MAX, acpi_db_walk_क्रम_references,
				  शून्य, (व्योम *)obj_desc, शून्य);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_bus_walk
 *
 * PARAMETERS:  Callback from walk_namespace
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Display info about device objects that have a corresponding
 *              _PRT method.
 *
 ******************************************************************************/

अटल acpi_status
acpi_db_bus_walk(acpi_handle obj_handle,
		 u32 nesting_level, व्योम *context, व्योम **वापस_value)
अणु
	काष्ठा acpi_namespace_node *node =
	    (काष्ठा acpi_namespace_node *)obj_handle;
	acpi_status status;
	काष्ठा acpi_buffer buffer;
	काष्ठा acpi_namespace_node *temp_node;
	काष्ठा acpi_device_info *info;
	u32 i;

	अगर ((node->type != ACPI_TYPE_DEVICE) &&
	    (node->type != ACPI_TYPE_PROCESSOR)) अणु
		वापस (AE_OK);
	पूर्ण

	/* Exit अगर there is no _PRT under this device */

	status = acpi_get_handle(node, METHOD_NAME__PRT,
				 ACPI_CAST_PTR(acpi_handle, &temp_node));
	अगर (ACPI_FAILURE(status)) अणु
		वापस (AE_OK);
	पूर्ण

	/* Get the full path to this device object */

	buffer.length = ACPI_ALLOCATE_LOCAL_BUFFER;
	status = acpi_ns_handle_to_pathname(obj_handle, &buffer, TRUE);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_os_म_लिखो("Could Not get pathname for object %p\n",
			       obj_handle);
		वापस (AE_OK);
	पूर्ण

	status = acpi_get_object_info(obj_handle, &info);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (AE_OK);
	पूर्ण

	/* Display the full path */

	acpi_os_म_लिखो("%-32s Type %X", (अक्षर *)buffer.poपूर्णांकer, node->type);
	ACPI_FREE(buffer.poपूर्णांकer);

	अगर (info->flags & ACPI_PCI_ROOT_BRIDGE) अणु
		acpi_os_म_लिखो(" - Is PCI Root Bridge");
	पूर्ण
	acpi_os_म_लिखो("\n");

	/* _PRT info */

	acpi_os_म_लिखो("_PRT: %p\n", temp_node);

	/* Dump _ADR, _HID, _UID, _CID */

	अगर (info->valid & ACPI_VALID_ADR) अणु
		acpi_os_म_लिखो("_ADR: %8.8X%8.8X\n",
			       ACPI_FORMAT_UINT64(info->address));
	पूर्ण अन्यथा अणु
		acpi_os_म_लिखो("_ADR: <Not Present>\n");
	पूर्ण

	अगर (info->valid & ACPI_VALID_HID) अणु
		acpi_os_म_लिखो("_HID: %s\n", info->hardware_id.string);
	पूर्ण अन्यथा अणु
		acpi_os_म_लिखो("_HID: <Not Present>\n");
	पूर्ण

	अगर (info->valid & ACPI_VALID_UID) अणु
		acpi_os_म_लिखो("_UID: %s\n", info->unique_id.string);
	पूर्ण अन्यथा अणु
		acpi_os_म_लिखो("_UID: <Not Present>\n");
	पूर्ण

	अगर (info->valid & ACPI_VALID_CID) अणु
		क्रम (i = 0; i < info->compatible_id_list.count; i++) अणु
			acpi_os_म_लिखो("_CID: %s\n",
				       info->compatible_id_list.ids[i].string);
		पूर्ण
	पूर्ण अन्यथा अणु
		acpi_os_म_लिखो("_CID: <Not Present>\n");
	पूर्ण

	ACPI_FREE(info);
	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_get_bus_info
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: Display info about प्रणाली buses.
 *
 ******************************************************************************/

व्योम acpi_db_get_bus_info(व्योम)
अणु
	/* Search all nodes in namespace */

	(व्योम)acpi_walk_namespace(ACPI_TYPE_ANY, ACPI_ROOT_OBJECT,
				  ACPI_UINT32_MAX, acpi_db_bus_walk, शून्य, शून्य,
				  शून्य);
पूर्ण
