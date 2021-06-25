<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: nsdump - table dumping routines क्रम debug
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acnamesp.h"
#समावेश <acpi/acoutput.h>

#घोषणा _COMPONENT          ACPI_NAMESPACE
ACPI_MODULE_NAME("nsdump")

/* Local prototypes */
#अगर_घोषित ACPI_OBSOLETE_FUNCTIONS
व्योम acpi_ns_dump_root_devices(व्योम);

अटल acpi_status
acpi_ns_dump_one_device(acpi_handle obj_handle,
			u32 level, व्योम *context, व्योम **वापस_value);
#पूर्ण_अगर

#अगर defined(ACPI_DEBUG_OUTPUT) || defined(ACPI_DEBUGGER)

अटल acpi_status
acpi_ns_dump_one_object_path(acpi_handle obj_handle,
			     u32 level, व्योम *context, व्योम **वापस_value);

अटल acpi_status
acpi_ns_get_max_depth(acpi_handle obj_handle,
		      u32 level, व्योम *context, व्योम **वापस_value);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_prपूर्णांक_pathname
 *
 * PARAMETERS:  num_segments        - Number of ACPI name segments
 *              pathname            - The compressed (पूर्णांकernal) path
 *
 * RETURN:      None
 *
 * DESCRIPTION: Prपूर्णांक an object's full namespace pathname
 *
 ******************************************************************************/

व्योम acpi_ns_prपूर्णांक_pathname(u32 num_segments, स्थिर अक्षर *pathname)
अणु
	u32 i;

	ACPI_FUNCTION_NAME(ns_prपूर्णांक_pathname);

	/* Check अगर debug output enabled */

	अगर (!ACPI_IS_DEBUG_ENABLED(ACPI_LV_NAMES, ACPI_NAMESPACE)) अणु
		वापस;
	पूर्ण

	/* Prपूर्णांक the entire name */

	ACPI_DEBUG_PRINT((ACPI_DB_NAMES, "["));

	जबतक (num_segments) अणु
		क्रम (i = 0; i < 4; i++) अणु
			है_छाप((पूर्णांक)pathname[i]) ?
			    acpi_os_म_लिखो("%c", pathname[i]) :
			    acpi_os_म_लिखो("?");
		पूर्ण

		pathname += ACPI_NAMESEG_SIZE;
		num_segments--;
		अगर (num_segments) अणु
			acpi_os_म_लिखो(".");
		पूर्ण
	पूर्ण

	acpi_os_म_लिखो("]\n");
पूर्ण

#अगर_घोषित ACPI_OBSOLETE_FUNCTIONS
/* Not used at this समय, perhaps later */

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_dump_pathname
 *
 * PARAMETERS:  handle              - Object
 *              msg                 - Prefix message
 *              level               - Desired debug level
 *              component           - Caller's component ID
 *
 * RETURN:      None
 *
 * DESCRIPTION: Prपूर्णांक an object's full namespace pathname
 *              Manages allocation/मुक्तing of a pathname buffer
 *
 ******************************************************************************/

व्योम
acpi_ns_dump_pathname(acpi_handle handle,
		      स्थिर अक्षर *msg, u32 level, u32 component)
अणु

	ACPI_FUNCTION_TRACE(ns_dump_pathname);

	/* Do this only अगर the requested debug level and component are enabled */

	अगर (!ACPI_IS_DEBUG_ENABLED(level, component)) अणु
		वापस_VOID;
	पूर्ण

	/* Convert handle to a full pathname and prपूर्णांक it (with supplied message) */

	acpi_ns_prपूर्णांक_node_pathname(handle, msg);
	acpi_os_म_लिखो("\n");
	वापस_VOID;
पूर्ण
#पूर्ण_अगर

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_dump_one_object
 *
 * PARAMETERS:  obj_handle          - Node to be dumped
 *              level               - Nesting level of the handle
 *              context             - Passed पूर्णांकo walk_namespace
 *              वापस_value        - Not used
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Dump a single Node
 *              This procedure is a user_function called by acpi_ns_walk_namespace.
 *
 ******************************************************************************/

acpi_status
acpi_ns_dump_one_object(acpi_handle obj_handle,
			u32 level, व्योम *context, व्योम **वापस_value)
अणु
	काष्ठा acpi_walk_info *info = (काष्ठा acpi_walk_info *)context;
	काष्ठा acpi_namespace_node *this_node;
	जोड़ acpi_opeअक्रम_object *obj_desc = शून्य;
	acpi_object_type obj_type;
	acpi_object_type type;
	u32 bytes_to_dump;
	u32 dbg_level;
	u32 i;

	ACPI_FUNCTION_NAME(ns_dump_one_object);

	/* Is output enabled? */

	अगर (!(acpi_dbg_level & info->debug_level)) अणु
		वापस (AE_OK);
	पूर्ण

	अगर (!obj_handle) अणु
		ACPI_DEBUG_PRINT((ACPI_DB_INFO, "Null object handle\n"));
		वापस (AE_OK);
	पूर्ण

	this_node = acpi_ns_validate_handle(obj_handle);
	अगर (!this_node) अणु
		ACPI_DEBUG_PRINT((ACPI_DB_INFO, "Invalid object handle %p\n",
				  obj_handle));
		वापस (AE_OK);
	पूर्ण

	type = this_node->type;
	info->count++;

	/* Check अगर the owner matches */

	अगर ((info->owner_id != ACPI_OWNER_ID_MAX) &&
	    (info->owner_id != this_node->owner_id)) अणु
		वापस (AE_OK);
	पूर्ण

	अगर (!(info->display_type & ACPI_DISPLAY_SHORT)) अणु

		/* Indent the object according to the level */

		acpi_os_म_लिखो("%2d%*s", (u32) level - 1, (पूर्णांक)level * 2, " ");

		/* Check the node type and name */

		अगर (type > ACPI_TYPE_LOCAL_MAX) अणु
			ACPI_WARNING((AE_INFO,
				      "Invalid ACPI Object Type 0x%08X", type));
		पूर्ण

		acpi_os_म_लिखो("%4.4s", acpi_ut_get_node_name(this_node));
	पूर्ण

	/* Now we can prपूर्णांक out the pertinent inक्रमmation */

	acpi_os_म_लिखो(" %-12s %p %3.3X ",
		       acpi_ut_get_type_name(type), this_node,
		       this_node->owner_id);

	dbg_level = acpi_dbg_level;
	acpi_dbg_level = 0;
	obj_desc = acpi_ns_get_attached_object(this_node);
	acpi_dbg_level = dbg_level;

	/* Temp nodes are those nodes created by a control method */

	अगर (this_node->flags & ANOBJ_TEMPORARY) अणु
		acpi_os_म_लिखो("(T) ");
	पूर्ण

	चयन (info->display_type & ACPI_DISPLAY_MASK) अणु
	हाल ACPI_DISPLAY_SUMMARY:

		अगर (!obj_desc) अणु

			/* No attached object. Some types should always have an object */

			चयन (type) अणु
			हाल ACPI_TYPE_INTEGER:
			हाल ACPI_TYPE_PACKAGE:
			हाल ACPI_TYPE_BUFFER:
			हाल ACPI_TYPE_STRING:
			हाल ACPI_TYPE_METHOD:

				acpi_os_म_लिखो("<No attached object>");
				अवरोध;

			शेष:

				अवरोध;
			पूर्ण

			acpi_os_म_लिखो("\n");
			वापस (AE_OK);
		पूर्ण

		चयन (type) अणु
		हाल ACPI_TYPE_PROCESSOR:

			acpi_os_म_लिखो("ID %02X Len %02X Addr %8.8X%8.8X\n",
				       obj_desc->processor.proc_id,
				       obj_desc->processor.length,
				       ACPI_FORMAT_UINT64(obj_desc->processor.
							  address));
			अवरोध;

		हाल ACPI_TYPE_DEVICE:

			acpi_os_म_लिखो("Notify Object: %p\n", obj_desc);
			अवरोध;

		हाल ACPI_TYPE_METHOD:

			acpi_os_म_लिखो("Args %X Len %.4X Aml %p\n",
				       (u32) obj_desc->method.param_count,
				       obj_desc->method.aml_length,
				       obj_desc->method.aml_start);
			अवरोध;

		हाल ACPI_TYPE_INTEGER:

			acpi_os_म_लिखो("= %8.8X%8.8X\n",
				       ACPI_FORMAT_UINT64(obj_desc->पूर्णांकeger.
							  value));
			अवरोध;

		हाल ACPI_TYPE_PACKAGE:

			अगर (obj_desc->common.flags & AOPOBJ_DATA_VALID) अणु
				acpi_os_म_लिखो("Elements %.2X\n",
					       obj_desc->package.count);
			पूर्ण अन्यथा अणु
				acpi_os_म_लिखो("[Length not yet evaluated]\n");
			पूर्ण
			अवरोध;

		हाल ACPI_TYPE_BUFFER:

			अगर (obj_desc->common.flags & AOPOBJ_DATA_VALID) अणु
				acpi_os_म_लिखो("Len %.2X",
					       obj_desc->buffer.length);

				/* Dump some of the buffer */

				अगर (obj_desc->buffer.length > 0) अणु
					acpi_os_म_लिखो(" =");
					क्रम (i = 0;
					     (i < obj_desc->buffer.length
					      && i < 12); i++) अणु
						acpi_os_म_लिखो(" %2.2X",
							       obj_desc->buffer.
							       poपूर्णांकer[i]);
					पूर्ण
				पूर्ण
				acpi_os_म_लिखो("\n");
			पूर्ण अन्यथा अणु
				acpi_os_म_लिखो("[Length not yet evaluated]\n");
			पूर्ण
			अवरोध;

		हाल ACPI_TYPE_STRING:

			acpi_os_म_लिखो("Len %.2X ", obj_desc->string.length);
			acpi_ut_prपूर्णांक_string(obj_desc->string.poपूर्णांकer, 80);
			acpi_os_म_लिखो("\n");
			अवरोध;

		हाल ACPI_TYPE_REGION:

			acpi_os_म_लिखो("[%s]",
				       acpi_ut_get_region_name(obj_desc->region.
							       space_id));
			अगर (obj_desc->region.flags & AOPOBJ_DATA_VALID) अणु
				acpi_os_म_लिखो(" Addr %8.8X%8.8X Len %.4X\n",
					       ACPI_FORMAT_UINT64(obj_desc->
								  region.
								  address),
					       obj_desc->region.length);
			पूर्ण अन्यथा अणु
				acpi_os_म_लिखो
				    (" [Address/Length not yet evaluated]\n");
			पूर्ण
			अवरोध;

		हाल ACPI_TYPE_LOCAL_REFERENCE:

			acpi_os_म_लिखो("[%s]\n",
				       acpi_ut_get_reference_name(obj_desc));
			अवरोध;

		हाल ACPI_TYPE_BUFFER_FIELD:

			अगर (obj_desc->buffer_field.buffer_obj &&
			    obj_desc->buffer_field.buffer_obj->buffer.node) अणु
				acpi_os_म_लिखो("Buf [%4.4s]",
					       acpi_ut_get_node_name(obj_desc->
								     buffer_field.
								     buffer_obj->
								     buffer.
								     node));
			पूर्ण
			अवरोध;

		हाल ACPI_TYPE_LOCAL_REGION_FIELD:

			acpi_os_म_लिखो("Rgn [%4.4s]",
				       acpi_ut_get_node_name(obj_desc->
							     common_field.
							     region_obj->region.
							     node));
			अवरोध;

		हाल ACPI_TYPE_LOCAL_BANK_FIELD:

			acpi_os_म_लिखो("Rgn [%4.4s] Bnk [%4.4s]",
				       acpi_ut_get_node_name(obj_desc->
							     common_field.
							     region_obj->region.
							     node),
				       acpi_ut_get_node_name(obj_desc->
							     bank_field.
							     bank_obj->
							     common_field.
							     node));
			अवरोध;

		हाल ACPI_TYPE_LOCAL_INDEX_FIELD:

			acpi_os_म_लिखो("Idx [%4.4s] Dat [%4.4s]",
				       acpi_ut_get_node_name(obj_desc->
							     index_field.
							     index_obj->
							     common_field.node),
				       acpi_ut_get_node_name(obj_desc->
							     index_field.
							     data_obj->
							     common_field.
							     node));
			अवरोध;

		हाल ACPI_TYPE_LOCAL_ALIAS:
		हाल ACPI_TYPE_LOCAL_METHOD_ALIAS:

			acpi_os_म_लिखो("Target %4.4s (%p)\n",
				       acpi_ut_get_node_name(obj_desc),
				       obj_desc);
			अवरोध;

		शेष:

			acpi_os_म_लिखो("Object %p\n", obj_desc);
			अवरोध;
		पूर्ण

		/* Common field handling */

		चयन (type) अणु
		हाल ACPI_TYPE_BUFFER_FIELD:
		हाल ACPI_TYPE_LOCAL_REGION_FIELD:
		हाल ACPI_TYPE_LOCAL_BANK_FIELD:
		हाल ACPI_TYPE_LOCAL_INDEX_FIELD:

			acpi_os_म_लिखो(" Off %.3X Len %.2X Acc %.2X\n",
				       (obj_desc->common_field.
					base_byte_offset * 8)
				       +
				       obj_desc->common_field.
				       start_field_bit_offset,
				       obj_desc->common_field.bit_length,
				       obj_desc->common_field.
				       access_byte_width);
			अवरोध;

		शेष:

			अवरोध;
		पूर्ण
		अवरोध;

	हाल ACPI_DISPLAY_OBJECTS:

		acpi_os_म_लिखो("O:%p", obj_desc);
		अगर (!obj_desc) अणु

			/* No attached object, we are करोne */

			acpi_os_म_लिखो("\n");
			वापस (AE_OK);
		पूर्ण

		acpi_os_म_लिखो("(R%u)", obj_desc->common.reference_count);

		चयन (type) अणु
		हाल ACPI_TYPE_METHOD:

			/* Name is a Method and its AML offset/length are set */

			acpi_os_म_लिखो(" M:%p-%X\n", obj_desc->method.aml_start,
				       obj_desc->method.aml_length);
			अवरोध;

		हाल ACPI_TYPE_INTEGER:

			acpi_os_म_लिखो(" I:%8.8X8.8%X\n",
				       ACPI_FORMAT_UINT64(obj_desc->पूर्णांकeger.
							  value));
			अवरोध;

		हाल ACPI_TYPE_STRING:

			acpi_os_म_लिखो(" S:%p-%X\n", obj_desc->string.poपूर्णांकer,
				       obj_desc->string.length);
			अवरोध;

		हाल ACPI_TYPE_BUFFER:

			acpi_os_म_लिखो(" B:%p-%X\n", obj_desc->buffer.poपूर्णांकer,
				       obj_desc->buffer.length);
			अवरोध;

		शेष:

			acpi_os_म_लिखो("\n");
			अवरोध;
		पूर्ण
		अवरोध;

	शेष:
		acpi_os_म_लिखो("\n");
		अवरोध;
	पूर्ण

	/* If debug turned off, करोne */

	अगर (!(acpi_dbg_level & ACPI_LV_VALUES)) अणु
		वापस (AE_OK);
	पूर्ण

	/* If there is an attached object, display it */

	dbg_level = acpi_dbg_level;
	acpi_dbg_level = 0;
	obj_desc = acpi_ns_get_attached_object(this_node);
	acpi_dbg_level = dbg_level;

	/* Dump attached objects */

	जबतक (obj_desc) अणु
		obj_type = ACPI_TYPE_INVALID;
		acpi_os_म_लिखो("Attached Object %p: ", obj_desc);

		/* Decode the type of attached object and dump the contents */

		चयन (ACPI_GET_DESCRIPTOR_TYPE(obj_desc)) अणु
		हाल ACPI_DESC_TYPE_NAMED:

			acpi_os_म_लिखो("(Ptr to Node)\n");
			bytes_to_dump = माप(काष्ठा acpi_namespace_node);
			ACPI_DUMP_BUFFER(obj_desc, bytes_to_dump);
			अवरोध;

		हाल ACPI_DESC_TYPE_OPERAND:

			obj_type = obj_desc->common.type;

			अगर (obj_type > ACPI_TYPE_LOCAL_MAX) अणु
				acpi_os_म_लिखो
				    ("(Pointer to ACPI Object type %.2X [UNKNOWN])\n",
				     obj_type);

				bytes_to_dump = 32;
			पूर्ण अन्यथा अणु
				acpi_os_म_लिखो
				    ("(Pointer to ACPI Object type %.2X [%s])\n",
				     obj_type, acpi_ut_get_type_name(obj_type));

				bytes_to_dump =
				    माप(जोड़ acpi_opeअक्रम_object);
			पूर्ण

			ACPI_DUMP_BUFFER(obj_desc, bytes_to_dump);
			अवरोध;

		शेष:

			अवरोध;
		पूर्ण

		/* If value is NOT an पूर्णांकernal object, we are करोne */

		अगर (ACPI_GET_DESCRIPTOR_TYPE(obj_desc) !=
		    ACPI_DESC_TYPE_OPERAND) अणु
			जाओ cleanup;
		पूर्ण

		/* Valid object, get the poपूर्णांकer to next level, अगर any */

		चयन (obj_type) अणु
		हाल ACPI_TYPE_BUFFER:
		हाल ACPI_TYPE_STRING:
			/*
			 * NOTE: takes advantage of common fields between string/buffer
			 */
			bytes_to_dump = obj_desc->string.length;
			obj_desc = (व्योम *)obj_desc->string.poपूर्णांकer;

			acpi_os_म_लिखो("(Buffer/String pointer %p length %X)\n",
				       obj_desc, bytes_to_dump);
			ACPI_DUMP_BUFFER(obj_desc, bytes_to_dump);
			जाओ cleanup;

		हाल ACPI_TYPE_BUFFER_FIELD:

			obj_desc =
			    (जोड़ acpi_opeअक्रम_object *)obj_desc->buffer_field.
			    buffer_obj;
			अवरोध;

		हाल ACPI_TYPE_PACKAGE:

			obj_desc = (व्योम *)obj_desc->package.elements;
			अवरोध;

		हाल ACPI_TYPE_METHOD:

			obj_desc = (व्योम *)obj_desc->method.aml_start;
			अवरोध;

		हाल ACPI_TYPE_LOCAL_REGION_FIELD:

			obj_desc = (व्योम *)obj_desc->field.region_obj;
			अवरोध;

		हाल ACPI_TYPE_LOCAL_BANK_FIELD:

			obj_desc = (व्योम *)obj_desc->bank_field.region_obj;
			अवरोध;

		हाल ACPI_TYPE_LOCAL_INDEX_FIELD:

			obj_desc = (व्योम *)obj_desc->index_field.index_obj;
			अवरोध;

		शेष:

			जाओ cleanup;
		पूर्ण
	पूर्ण

cleanup:
	acpi_os_म_लिखो("\n");
	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_dump_objects
 *
 * PARAMETERS:  type                - Object type to be dumped
 *              display_type        - 0 or ACPI_DISPLAY_SUMMARY
 *              max_depth           - Maximum depth of dump. Use ACPI_UINT32_MAX
 *                                    क्रम an effectively unlimited depth.
 *              owner_id            - Dump only objects owned by this ID. Use
 *                                    ACPI_UINT32_MAX to match all owners.
 *              start_handle        - Where in namespace to start/end search
 *
 * RETURN:      None
 *
 * DESCRIPTION: Dump typed objects within the loaded namespace. Uses
 *              acpi_ns_walk_namespace in conjunction with acpi_ns_dump_one_object.
 *
 ******************************************************************************/

व्योम
acpi_ns_dump_objects(acpi_object_type type,
		     u8 display_type,
		     u32 max_depth,
		     acpi_owner_id owner_id, acpi_handle start_handle)
अणु
	काष्ठा acpi_walk_info info;
	acpi_status status;

	ACPI_FUNCTION_ENTRY();

	/*
	 * Just lock the entire namespace क्रम the duration of the dump.
	 * We करोn't want any changes to the namespace during this समय,
	 * especially the temporary nodes since we are going to display
	 * them also.
	 */
	status = acpi_ut_acquire_mutex(ACPI_MTX_NAMESPACE);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_os_म_लिखो("Could not acquire namespace mutex\n");
		वापस;
	पूर्ण

	info.count = 0;
	info.debug_level = ACPI_LV_TABLES;
	info.owner_id = owner_id;
	info.display_type = display_type;

	(व्योम)acpi_ns_walk_namespace(type, start_handle, max_depth,
				     ACPI_NS_WALK_NO_UNLOCK |
				     ACPI_NS_WALK_TEMP_NODES,
				     acpi_ns_dump_one_object, शून्य,
				     (व्योम *)&info, शून्य);

	acpi_os_म_लिखो("\nNamespace node count: %u\n\n", info.count);
	(व्योम)acpi_ut_release_mutex(ACPI_MTX_NAMESPACE);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_dump_one_object_path, acpi_ns_get_max_depth
 *
 * PARAMETERS:  obj_handle          - Node to be dumped
 *              level               - Nesting level of the handle
 *              context             - Passed पूर्णांकo walk_namespace
 *              वापस_value        - Not used
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Dump the full pathname to a namespace object. acp_ns_get_max_depth
 *              computes the maximum nesting depth in the namespace tree, in
 *              order to simplअगरy क्रमmatting in acpi_ns_dump_one_object_path.
 *              These procedures are user_functions called by acpi_ns_walk_namespace.
 *
 ******************************************************************************/

अटल acpi_status
acpi_ns_dump_one_object_path(acpi_handle obj_handle,
			     u32 level, व्योम *context, व्योम **वापस_value)
अणु
	u32 max_level = *((u32 *)context);
	अक्षर *pathname;
	काष्ठा acpi_namespace_node *node;
	पूर्णांक path_indent;

	अगर (!obj_handle) अणु
		वापस (AE_OK);
	पूर्ण

	node = acpi_ns_validate_handle(obj_handle);
	अगर (!node) अणु

		/* Ignore bad node during namespace walk */

		वापस (AE_OK);
	पूर्ण

	pathname = acpi_ns_get_normalized_pathname(node, TRUE);

	path_indent = 1;
	अगर (level <= max_level) अणु
		path_indent = max_level - level + 1;
	पूर्ण

	acpi_os_म_लिखो("%2d%*s%-12s%*s",
		       level, level, " ", acpi_ut_get_type_name(node->type),
		       path_indent, " ");

	acpi_os_म_लिखो("%s\n", &pathname[1]);
	ACPI_FREE(pathname);
	वापस (AE_OK);
पूर्ण

अटल acpi_status
acpi_ns_get_max_depth(acpi_handle obj_handle,
		      u32 level, व्योम *context, व्योम **वापस_value)
अणु
	u32 *max_level = (u32 *)context;

	अगर (level > *max_level) अणु
		*max_level = level;
	पूर्ण
	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_dump_object_paths
 *
 * PARAMETERS:  type                - Object type to be dumped
 *              display_type        - 0 or ACPI_DISPLAY_SUMMARY
 *              max_depth           - Maximum depth of dump. Use ACPI_UINT32_MAX
 *                                    क्रम an effectively unlimited depth.
 *              owner_id            - Dump only objects owned by this ID. Use
 *                                    ACPI_UINT32_MAX to match all owners.
 *              start_handle        - Where in namespace to start/end search
 *
 * RETURN:      None
 *
 * DESCRIPTION: Dump full object pathnames within the loaded namespace. Uses
 *              acpi_ns_walk_namespace in conjunction with acpi_ns_dump_one_object_path.
 *
 ******************************************************************************/

व्योम
acpi_ns_dump_object_paths(acpi_object_type type,
			  u8 display_type,
			  u32 max_depth,
			  acpi_owner_id owner_id, acpi_handle start_handle)
अणु
	acpi_status status;
	u32 max_level = 0;

	ACPI_FUNCTION_ENTRY();

	/*
	 * Just lock the entire namespace क्रम the duration of the dump.
	 * We करोn't want any changes to the namespace during this समय,
	 * especially the temporary nodes since we are going to display
	 * them also.
	 */
	status = acpi_ut_acquire_mutex(ACPI_MTX_NAMESPACE);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_os_म_लिखो("Could not acquire namespace mutex\n");
		वापस;
	पूर्ण

	/* Get the max depth of the namespace tree, क्रम क्रमmatting later */

	(व्योम)acpi_ns_walk_namespace(type, start_handle, max_depth,
				     ACPI_NS_WALK_NO_UNLOCK |
				     ACPI_NS_WALK_TEMP_NODES,
				     acpi_ns_get_max_depth, शून्य,
				     (व्योम *)&max_level, शून्य);

	/* Now dump the entire namespace */

	(व्योम)acpi_ns_walk_namespace(type, start_handle, max_depth,
				     ACPI_NS_WALK_NO_UNLOCK |
				     ACPI_NS_WALK_TEMP_NODES,
				     acpi_ns_dump_one_object_path, शून्य,
				     (व्योम *)&max_level, शून्य);

	(व्योम)acpi_ut_release_mutex(ACPI_MTX_NAMESPACE);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_dump_entry
 *
 * PARAMETERS:  handle              - Node to be dumped
 *              debug_level         - Output level
 *
 * RETURN:      None
 *
 * DESCRIPTION: Dump a single Node
 *
 ******************************************************************************/

व्योम acpi_ns_dump_entry(acpi_handle handle, u32 debug_level)
अणु
	काष्ठा acpi_walk_info info;

	ACPI_FUNCTION_ENTRY();

	info.debug_level = debug_level;
	info.owner_id = ACPI_OWNER_ID_MAX;
	info.display_type = ACPI_DISPLAY_SUMMARY;

	(व्योम)acpi_ns_dump_one_object(handle, 1, &info, शून्य);
पूर्ण

#अगर_घोषित ACPI_ASL_COMPILER
/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_dump_tables
 *
 * PARAMETERS:  search_base         - Root of subtree to be dumped, or
 *                                    NS_ALL to dump the entire namespace
 *              max_depth           - Maximum depth of dump. Use पूर्णांक_उच्च
 *                                    क्रम an effectively unlimited depth.
 *
 * RETURN:      None
 *
 * DESCRIPTION: Dump the name space, or a portion of it.
 *
 ******************************************************************************/

व्योम acpi_ns_dump_tables(acpi_handle search_base, u32 max_depth)
अणु
	acpi_handle search_handle = search_base;

	ACPI_FUNCTION_TRACE(ns_dump_tables);

	अगर (!acpi_gbl_root_node) अणु
		/*
		 * If the name space has not been initialized,
		 * there is nothing to dump.
		 */
		ACPI_DEBUG_PRINT((ACPI_DB_TABLES,
				  "namespace not initialized!\n"));
		वापस_VOID;
	पूर्ण

	अगर (ACPI_NS_ALL == search_base) अणु

		/* Entire namespace */

		search_handle = acpi_gbl_root_node;
		ACPI_DEBUG_PRINT((ACPI_DB_TABLES, "\\\n"));
	पूर्ण

	acpi_ns_dump_objects(ACPI_TYPE_ANY, ACPI_DISPLAY_OBJECTS, max_depth,
			     ACPI_OWNER_ID_MAX, search_handle);
	वापस_VOID;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर
