<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/*******************************************************************************
 *
 * Module Name: dbstats - Generation and display of ACPI table statistics
 *
 ******************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acdebug.h"
#समावेश "acnamesp.h"

#घोषणा _COMPONENT          ACPI_CA_DEBUGGER
ACPI_MODULE_NAME("dbstats")

/* Local prototypes */
अटल व्योम acpi_db_count_namespace_objects(व्योम);

अटल व्योम acpi_db_क्रमागतerate_object(जोड़ acpi_opeअक्रम_object *obj_desc);

अटल acpi_status
acpi_db_classअगरy_one_object(acpi_handle obj_handle,
			    u32 nesting_level,
			    व्योम *context, व्योम **वापस_value);

#अगर defined ACPI_DBG_TRACK_ALLOCATIONS || defined ACPI_USE_LOCAL_CACHE
अटल व्योम acpi_db_list_info(काष्ठा acpi_memory_list *list);
#पूर्ण_अगर

/*
 * Statistics subcommands
 */
अटल काष्ठा acpi_db_argument_info acpi_db_stat_types[] = अणु
	अणु"ALLOCATIONS"पूर्ण,
	अणु"OBJECTS"पूर्ण,
	अणु"MEMORY"पूर्ण,
	अणु"MISC"पूर्ण,
	अणु"TABLES"पूर्ण,
	अणु"SIZES"पूर्ण,
	अणु"STACK"पूर्ण,
	अणुशून्यपूर्ण			/* Must be null terminated */
पूर्ण;

#घोषणा CMD_STAT_ALLOCATIONS     0
#घोषणा CMD_STAT_OBJECTS         1
#घोषणा CMD_STAT_MEMORY          2
#घोषणा CMD_STAT_MISC            3
#घोषणा CMD_STAT_TABLES          4
#घोषणा CMD_STAT_SIZES           5
#घोषणा CMD_STAT_STACK           6

#अगर defined ACPI_DBG_TRACK_ALLOCATIONS || defined ACPI_USE_LOCAL_CACHE
/*******************************************************************************
 *
 * FUNCTION:    acpi_db_list_info
 *
 * PARAMETERS:  list            - Memory list/cache to be displayed
 *
 * RETURN:      None
 *
 * DESCRIPTION: Display inक्रमmation about the input memory list or cache.
 *
 ******************************************************************************/

अटल व्योम acpi_db_list_info(काष्ठा acpi_memory_list *list)
अणु
#अगर_घोषित ACPI_DBG_TRACK_ALLOCATIONS
	u32 outstanding;
#पूर्ण_अगर

	acpi_os_म_लिखो("\n%s\n", list->list_name);

	/* max_depth > 0 indicates a cache object */

	अगर (list->max_depth > 0) अणु
		acpi_os_म_लिखो
		    ("    Cache: [Depth    MaxD Avail  Size]                "
		     "%8.2X %8.2X %8.2X %8.2X\n", list->current_depth,
		     list->max_depth, list->max_depth - list->current_depth,
		     (list->current_depth * list->object_size));
	पूर्ण
#अगर_घोषित ACPI_DBG_TRACK_ALLOCATIONS
	अगर (list->max_depth > 0) अणु
		acpi_os_म_लिखो
		    ("    Cache: [Requests Hits Misses ObjSize]             "
		     "%8.2X %8.2X %8.2X %8.2X\n", list->requests, list->hits,
		     list->requests - list->hits, list->object_size);
	पूर्ण

	outstanding = acpi_db_get_cache_info(list);

	अगर (list->object_size) अणु
		acpi_os_म_लिखो
		    ("    Mem:   [Alloc    Free Max    CurSize Outstanding] "
		     "%8.2X %8.2X %8.2X %8.2X %8.2X\n", list->total_allocated,
		     list->total_मुक्तd, list->max_occupied,
		     outstanding * list->object_size, outstanding);
	पूर्ण अन्यथा अणु
		acpi_os_म_लिखो
		    ("    Mem:   [Alloc Free Max CurSize Outstanding Total] "
		     "%8.2X %8.2X %8.2X %8.2X %8.2X %8.2X\n",
		     list->total_allocated, list->total_मुक्तd,
		     list->max_occupied, list->current_total_size, outstanding,
		     list->total_size);
	पूर्ण
#पूर्ण_अगर
पूर्ण
#पूर्ण_अगर

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_क्रमागतerate_object
 *
 * PARAMETERS:  obj_desc            - Object to be counted
 *
 * RETURN:      None
 *
 * DESCRIPTION: Add this object to the global counts, by object type.
 *              Limited recursion handles subobjects and packages, and this
 *              is probably acceptable within the AML debugger only.
 *
 ******************************************************************************/

अटल व्योम acpi_db_क्रमागतerate_object(जोड़ acpi_opeअक्रम_object *obj_desc)
अणु
	u32 i;

	अगर (!obj_desc) अणु
		वापस;
	पूर्ण

	/* Enumerate this object first */

	acpi_gbl_num_objects++;

	अगर (obj_desc->common.type > ACPI_TYPE_NS_NODE_MAX) अणु
		acpi_gbl_obj_type_count_misc++;
	पूर्ण अन्यथा अणु
		acpi_gbl_obj_type_count[obj_desc->common.type]++;
	पूर्ण

	/* Count the sub-objects */

	चयन (obj_desc->common.type) अणु
	हाल ACPI_TYPE_PACKAGE:

		क्रम (i = 0; i < obj_desc->package.count; i++) अणु
			acpi_db_क्रमागतerate_object(obj_desc->package.elements[i]);
		पूर्ण
		अवरोध;

	हाल ACPI_TYPE_DEVICE:

		acpi_db_क्रमागतerate_object(obj_desc->device.notअगरy_list[0]);
		acpi_db_क्रमागतerate_object(obj_desc->device.notअगरy_list[1]);
		acpi_db_क्रमागतerate_object(obj_desc->device.handler);
		अवरोध;

	हाल ACPI_TYPE_BUFFER_FIELD:

		अगर (acpi_ns_get_secondary_object(obj_desc)) अणु
			acpi_gbl_obj_type_count[ACPI_TYPE_BUFFER_FIELD]++;
		पूर्ण
		अवरोध;

	हाल ACPI_TYPE_REGION:

		acpi_gbl_obj_type_count[ACPI_TYPE_LOCAL_REGION_FIELD]++;
		acpi_db_क्रमागतerate_object(obj_desc->region.handler);
		अवरोध;

	हाल ACPI_TYPE_POWER:

		acpi_db_क्रमागतerate_object(obj_desc->घातer_resource.
					 notअगरy_list[0]);
		acpi_db_क्रमागतerate_object(obj_desc->घातer_resource.
					 notअगरy_list[1]);
		अवरोध;

	हाल ACPI_TYPE_PROCESSOR:

		acpi_db_क्रमागतerate_object(obj_desc->processor.notअगरy_list[0]);
		acpi_db_क्रमागतerate_object(obj_desc->processor.notअगरy_list[1]);
		acpi_db_क्रमागतerate_object(obj_desc->processor.handler);
		अवरोध;

	हाल ACPI_TYPE_THERMAL:

		acpi_db_क्रमागतerate_object(obj_desc->thermal_zone.notअगरy_list[0]);
		acpi_db_क्रमागतerate_object(obj_desc->thermal_zone.notअगरy_list[1]);
		acpi_db_क्रमागतerate_object(obj_desc->thermal_zone.handler);
		अवरोध;

	शेष:

		अवरोध;
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_classअगरy_one_object
 *
 * PARAMETERS:  Callback क्रम walk_namespace
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Enumerate both the object descriptor (including subobjects) and
 *              the parent namespace node.
 *
 ******************************************************************************/

अटल acpi_status
acpi_db_classअगरy_one_object(acpi_handle obj_handle,
			    u32 nesting_level,
			    व्योम *context, व्योम **वापस_value)
अणु
	काष्ठा acpi_namespace_node *node;
	जोड़ acpi_opeअक्रम_object *obj_desc;
	u32 type;

	acpi_gbl_num_nodes++;

	node = (काष्ठा acpi_namespace_node *)obj_handle;
	obj_desc = acpi_ns_get_attached_object(node);

	acpi_db_क्रमागतerate_object(obj_desc);

	type = node->type;
	अगर (type > ACPI_TYPE_NS_NODE_MAX) अणु
		acpi_gbl_node_type_count_misc++;
	पूर्ण अन्यथा अणु
		acpi_gbl_node_type_count[type]++;
	पूर्ण

	वापस (AE_OK);

#अगर_घोषित ACPI_FUTURE_IMPLEMENTATION

	/* TBD: These need to be counted during the initial parsing phase */

	अगर (acpi_ps_is_named_op(op->opcode)) अणु
		num_nodes++;
	पूर्ण

	अगर (is_method) अणु
		num_method_elements++;
	पूर्ण

	num_grammar_elements++;
	op = acpi_ps_get_depth_next(root, op);

	size_of_parse_tree = (num_grammar_elements - num_method_elements) *
	    (u32)माप(जोड़ acpi_parse_object);
	size_of_method_trees =
	    num_method_elements * (u32)माप(जोड़ acpi_parse_object);
	size_of_node_entries =
	    num_nodes * (u32)माप(काष्ठा acpi_namespace_node);
	size_of_acpi_objects =
	    num_nodes * (u32)माप(जोड़ acpi_opeअक्रम_object);
#पूर्ण_अगर
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_count_namespace_objects
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: Count and classअगरy the entire namespace, including all
 *              namespace nodes and attached objects.
 *
 ******************************************************************************/

अटल व्योम acpi_db_count_namespace_objects(व्योम)
अणु
	u32 i;

	acpi_gbl_num_nodes = 0;
	acpi_gbl_num_objects = 0;

	acpi_gbl_obj_type_count_misc = 0;
	क्रम (i = 0; i < (ACPI_TYPE_NS_NODE_MAX - 1); i++) अणु
		acpi_gbl_obj_type_count[i] = 0;
		acpi_gbl_node_type_count[i] = 0;
	पूर्ण

	(व्योम)acpi_ns_walk_namespace(ACPI_TYPE_ANY, ACPI_ROOT_OBJECT,
				     ACPI_UINT32_MAX, FALSE,
				     acpi_db_classअगरy_one_object, शून्य, शून्य,
				     शून्य);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_display_statistics
 *
 * PARAMETERS:  type_arg        - Subcommand
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Display various statistics
 *
 ******************************************************************************/

acpi_status acpi_db_display_statistics(अक्षर *type_arg)
अणु
	u32 i;
	u32 temp;

	acpi_ut_strupr(type_arg);
	temp = acpi_db_match_argument(type_arg, acpi_db_stat_types);
	अगर (temp == ACPI_TYPE_NOT_FOUND) अणु
		acpi_os_म_लिखो("Invalid or unsupported argument\n");
		वापस (AE_OK);
	पूर्ण

	चयन (temp) अणु
	हाल CMD_STAT_ALLOCATIONS:

#अगर_घोषित ACPI_DBG_TRACK_ALLOCATIONS
		acpi_ut_dump_allocation_info();
#पूर्ण_अगर
		अवरोध;

	हाल CMD_STAT_TABLES:

		acpi_os_म_लिखो("ACPI Table Information (not implemented):\n\n");
		अवरोध;

	हाल CMD_STAT_OBJECTS:

		acpi_db_count_namespace_objects();

		acpi_os_म_लिखो
		    ("\nObjects defined in the current namespace:\n\n");

		acpi_os_म_लिखो("%16.16s %10.10s %10.10s\n",
			       "ACPI_TYPE", "NODES", "OBJECTS");

		क्रम (i = 0; i < ACPI_TYPE_NS_NODE_MAX; i++) अणु
			acpi_os_म_लिखो("%16.16s %10u %10u\n",
				       acpi_ut_get_type_name(i),
				       acpi_gbl_node_type_count[i],
				       acpi_gbl_obj_type_count[i]);
		पूर्ण

		acpi_os_म_लिखो("%16.16s %10u %10u\n", "Misc/Unknown",
			       acpi_gbl_node_type_count_misc,
			       acpi_gbl_obj_type_count_misc);

		acpi_os_म_लिखो("%16.16s %10u %10u\n", "TOTALS:",
			       acpi_gbl_num_nodes, acpi_gbl_num_objects);
		अवरोध;

	हाल CMD_STAT_MEMORY:

#अगर_घोषित ACPI_DBG_TRACK_ALLOCATIONS
		acpi_os_म_लिखो
		    ("\n----Object Statistics (all in hex)---------\n");

		acpi_db_list_info(acpi_gbl_global_list);
		acpi_db_list_info(acpi_gbl_ns_node_list);
#पूर्ण_अगर

#अगर_घोषित ACPI_USE_LOCAL_CACHE
		acpi_os_म_लिखो
		    ("\n----Cache Statistics (all in hex)---------\n");
		acpi_db_list_info(acpi_gbl_opeअक्रम_cache);
		acpi_db_list_info(acpi_gbl_ps_node_cache);
		acpi_db_list_info(acpi_gbl_ps_node_ext_cache);
		acpi_db_list_info(acpi_gbl_state_cache);
#पूर्ण_अगर

		अवरोध;

	हाल CMD_STAT_MISC:

		acpi_os_म_लिखो("\nMiscellaneous Statistics:\n\n");
		acpi_os_म_लिखो("%-28s:     %7u\n", "Calls to AcpiPsFind",
			       acpi_gbl_ps_find_count);
		acpi_os_म_लिखो("%-28s:     %7u\n", "Calls to AcpiNsLookup",
			       acpi_gbl_ns_lookup_count);

		acpi_os_म_लिखो("\nMutex usage:\n\n");
		क्रम (i = 0; i < ACPI_NUM_MUTEX; i++) अणु
			acpi_os_म_लिखो("%-28s:     %7u\n",
				       acpi_ut_get_mutex_name(i),
				       acpi_gbl_mutex_info[i].use_count);
		पूर्ण
		अवरोध;

	हाल CMD_STAT_SIZES:

		acpi_os_म_लिखो("\nInternal object sizes:\n\n");

		acpi_os_म_लिखो("Common         %3d\n",
			       (u32)माप(काष्ठा acpi_object_common));
		acpi_os_म_लिखो("Number         %3d\n",
			       (u32)माप(काष्ठा acpi_object_पूर्णांकeger));
		acpi_os_म_लिखो("String         %3d\n",
			       (u32)माप(काष्ठा acpi_object_string));
		acpi_os_म_लिखो("Buffer         %3d\n",
			       (u32)माप(काष्ठा acpi_object_buffer));
		acpi_os_म_लिखो("Package        %3d\n",
			       (u32)माप(काष्ठा acpi_object_package));
		acpi_os_म_लिखो("BufferField    %3d\n",
			       (u32)माप(काष्ठा acpi_object_buffer_field));
		acpi_os_म_लिखो("Device         %3d\n",
			       (u32)माप(काष्ठा acpi_object_device));
		acpi_os_म_लिखो("Event          %3d\n",
			       (u32)माप(काष्ठा acpi_object_event));
		acpi_os_म_लिखो("Method         %3d\n",
			       (u32)माप(काष्ठा acpi_object_method));
		acpi_os_म_लिखो("Mutex          %3d\n",
			       (u32)माप(काष्ठा acpi_object_mutex));
		acpi_os_म_लिखो("Region         %3d\n",
			       (u32)माप(काष्ठा acpi_object_region));
		acpi_os_म_लिखो("PowerResource  %3d\n",
			       (u32)माप(काष्ठा acpi_object_घातer_resource));
		acpi_os_म_लिखो("Processor      %3d\n",
			       (u32)माप(काष्ठा acpi_object_processor));
		acpi_os_म_लिखो("ThermalZone    %3d\n",
			       (u32)माप(काष्ठा acpi_object_thermal_zone));
		acpi_os_म_लिखो("RegionField    %3d\n",
			       (u32)माप(काष्ठा acpi_object_region_field));
		acpi_os_म_लिखो("BankField      %3d\n",
			       (u32)माप(काष्ठा acpi_object_bank_field));
		acpi_os_म_लिखो("IndexField     %3d\n",
			       (u32)माप(काष्ठा acpi_object_index_field));
		acpi_os_म_लिखो("Reference      %3d\n",
			       (u32)माप(काष्ठा acpi_object_reference));
		acpi_os_म_लिखो("Notify         %3d\n",
			       (u32)माप(काष्ठा acpi_object_notअगरy_handler));
		acpi_os_म_लिखो("AddressSpace   %3d\n",
			       (u32)माप(काष्ठा acpi_object_addr_handler));
		acpi_os_म_लिखो("Extra          %3d\n",
			       (u32)माप(काष्ठा acpi_object_extra));
		acpi_os_म_लिखो("Data           %3d\n",
			       (u32)माप(काष्ठा acpi_object_data));

		acpi_os_म_लिखो("\n");

		acpi_os_म_लिखो("ParseObject    %3d\n",
			       (u32)माप(काष्ठा acpi_parse_obj_common));
		acpi_os_म_लिखो("ParseObjectNamed %3d\n",
			       (u32)माप(काष्ठा acpi_parse_obj_named));
		acpi_os_म_लिखो("ParseObjectAsl %3d\n",
			       (u32)माप(काष्ठा acpi_parse_obj_asl));
		acpi_os_म_लिखो("OperandObject  %3d\n",
			       (u32)माप(जोड़ acpi_opeअक्रम_object));
		acpi_os_म_लिखो("NamespaceNode  %3d\n",
			       (u32)माप(काष्ठा acpi_namespace_node));
		acpi_os_म_लिखो("AcpiObject     %3d\n",
			       (u32)माप(जोड़ acpi_object));

		acpi_os_म_लिखो("\n");

		acpi_os_म_लिखो("Generic State  %3d\n",
			       (u32)माप(जोड़ acpi_generic_state));
		acpi_os_म_लिखो("Common State   %3d\n",
			       (u32)माप(काष्ठा acpi_common_state));
		acpi_os_म_लिखो("Control State  %3d\n",
			       (u32)माप(काष्ठा acpi_control_state));
		acpi_os_म_लिखो("Update State   %3d\n",
			       (u32)माप(काष्ठा acpi_update_state));
		acpi_os_म_लिखो("Scope State    %3d\n",
			       (u32)माप(काष्ठा acpi_scope_state));
		acpi_os_म_लिखो("Parse Scope    %3d\n",
			       (u32)माप(काष्ठा acpi_pscope_state));
		acpi_os_म_लिखो("Package State  %3d\n",
			       (u32)माप(काष्ठा acpi_pkg_state));
		acpi_os_म_लिखो("Thread State   %3d\n",
			       (u32)माप(काष्ठा acpi_thपढ़ो_state));
		acpi_os_म_लिखो("Result Values  %3d\n",
			       (u32)माप(काष्ठा acpi_result_values));
		acpi_os_म_लिखो("Notify Info    %3d\n",
			       (u32)माप(काष्ठा acpi_notअगरy_info));
		अवरोध;

	हाल CMD_STAT_STACK:
#अगर defined(ACPI_DEBUG_OUTPUT)

		temp =
		    (u32)ACPI_PTR_DIFF(acpi_gbl_entry_stack_poपूर्णांकer,
				       acpi_gbl_lowest_stack_poपूर्णांकer);

		acpi_os_म_लिखो("\nSubsystem Stack Usage:\n\n");
		acpi_os_म_लिखो("Entry Stack Pointer        %p\n",
			       acpi_gbl_entry_stack_poपूर्णांकer);
		acpi_os_म_लिखो("Lowest Stack Pointer       %p\n",
			       acpi_gbl_lowest_stack_poपूर्णांकer);
		acpi_os_म_लिखो("Stack Use                  %X (%u)\n", temp,
			       temp);
		acpi_os_म_लिखो("Deepest Procedure Nesting  %u\n",
			       acpi_gbl_deepest_nesting);
#पूर्ण_अगर
		अवरोध;

	शेष:

		अवरोध;
	पूर्ण

	acpi_os_म_लिखो("\n");
	वापस (AE_OK);
पूर्ण
