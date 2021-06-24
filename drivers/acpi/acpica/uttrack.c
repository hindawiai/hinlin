<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: uttrack - Memory allocation tracking routines (debug only)
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

/*
 * These procedures are used क्रम tracking memory leaks in the subप्रणाली, and
 * they get compiled out when the ACPI_DBG_TRACK_ALLOCATIONS is not set.
 *
 * Each memory allocation is tracked via a करोubly linked list. Each
 * element contains the caller's component, module name, function name, and
 * line number. acpi_ut_allocate and acpi_ut_allocate_zeroed call
 * acpi_ut_track_allocation to add an element to the list; deletion
 * occurs in the body of acpi_ut_मुक्त.
 */

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"

#अगर_घोषित ACPI_DBG_TRACK_ALLOCATIONS

#घोषणा _COMPONENT          ACPI_UTILITIES
ACPI_MODULE_NAME("uttrack")

/* Local prototypes */
अटल काष्ठा acpi_debug_mem_block *acpi_ut_find_allocation(काष्ठा
							    acpi_debug_mem_block
							    *allocation);

अटल acpi_status
acpi_ut_track_allocation(काष्ठा acpi_debug_mem_block *address,
			 acpi_size size,
			 u8 alloc_type,
			 u32 component, स्थिर अक्षर *module, u32 line);

अटल acpi_status
acpi_ut_हटाओ_allocation(काष्ठा acpi_debug_mem_block *address,
			  u32 component, स्थिर अक्षर *module, u32 line);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_create_list
 *
 * PARAMETERS:  cache_name      - Ascii name क्रम the cache
 *              object_size     - Size of each cached object
 *              वापस_cache    - Where the new cache object is वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Create a local memory list क्रम tracking purposed
 *
 ******************************************************************************/

acpi_status
acpi_ut_create_list(स्थिर अक्षर *list_name,
		    u16 object_size, काष्ठा acpi_memory_list **वापस_cache)
अणु
	काष्ठा acpi_memory_list *cache;

	cache = acpi_os_allocate_zeroed(माप(काष्ठा acpi_memory_list));
	अगर (!cache) अणु
		वापस (AE_NO_MEMORY);
	पूर्ण

	cache->list_name = list_name;
	cache->object_size = object_size;

	*वापस_cache = cache;
	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_allocate_and_track
 *
 * PARAMETERS:  size                - Size of the allocation
 *              component           - Component type of caller
 *              module              - Source file name of caller
 *              line                - Line number of caller
 *
 * RETURN:      Address of the allocated memory on success, शून्य on failure.
 *
 * DESCRIPTION: The subप्रणाली's equivalent of दो_स्मृति.
 *
 ******************************************************************************/

व्योम *acpi_ut_allocate_and_track(acpi_size size,
				 u32 component, स्थिर अक्षर *module, u32 line)
अणु
	काष्ठा acpi_debug_mem_block *allocation;
	acpi_status status;

	/* Check क्रम an inadvertent size of zero bytes */

	अगर (!size) अणु
		ACPI_WARNING((module, line,
			      "Attempt to allocate zero bytes, allocating 1 byte"));
		size = 1;
	पूर्ण

	allocation =
	    acpi_os_allocate(size + माप(काष्ठा acpi_debug_mem_header));
	अगर (!allocation) अणु

		/* Report allocation error */

		ACPI_WARNING((module, line,
			      "Could not allocate size %u", (u32)size));

		वापस (शून्य);
	पूर्ण

	status =
	    acpi_ut_track_allocation(allocation, size, ACPI_MEM_MALLOC,
				     component, module, line);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_os_मुक्त(allocation);
		वापस (शून्य);
	पूर्ण

	acpi_gbl_global_list->total_allocated++;
	acpi_gbl_global_list->total_size += (u32)size;
	acpi_gbl_global_list->current_total_size += (u32)size;

	अगर (acpi_gbl_global_list->current_total_size >
	    acpi_gbl_global_list->max_occupied) अणु
		acpi_gbl_global_list->max_occupied =
		    acpi_gbl_global_list->current_total_size;
	पूर्ण

	वापस ((व्योम *)&allocation->user_space);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_allocate_zeroed_and_track
 *
 * PARAMETERS:  size                - Size of the allocation
 *              component           - Component type of caller
 *              module              - Source file name of caller
 *              line                - Line number of caller
 *
 * RETURN:      Address of the allocated memory on success, शून्य on failure.
 *
 * DESCRIPTION: Subप्रणाली equivalent of सुस्मृति.
 *
 ******************************************************************************/

व्योम *acpi_ut_allocate_zeroed_and_track(acpi_size size,
					u32 component,
					स्थिर अक्षर *module, u32 line)
अणु
	काष्ठा acpi_debug_mem_block *allocation;
	acpi_status status;

	/* Check क्रम an inadvertent size of zero bytes */

	अगर (!size) अणु
		ACPI_WARNING((module, line,
			      "Attempt to allocate zero bytes, allocating 1 byte"));
		size = 1;
	पूर्ण

	allocation =
	    acpi_os_allocate_zeroed(size +
				    माप(काष्ठा acpi_debug_mem_header));
	अगर (!allocation) अणु

		/* Report allocation error */

		ACPI_ERROR((module, line,
			    "Could not allocate size %u", (u32)size));
		वापस (शून्य);
	पूर्ण

	status = acpi_ut_track_allocation(allocation, size,
					  ACPI_MEM_CALLOC, component, module,
					  line);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_os_मुक्त(allocation);
		वापस (शून्य);
	पूर्ण

	acpi_gbl_global_list->total_allocated++;
	acpi_gbl_global_list->total_size += (u32)size;
	acpi_gbl_global_list->current_total_size += (u32)size;

	अगर (acpi_gbl_global_list->current_total_size >
	    acpi_gbl_global_list->max_occupied) अणु
		acpi_gbl_global_list->max_occupied =
		    acpi_gbl_global_list->current_total_size;
	पूर्ण

	वापस ((व्योम *)&allocation->user_space);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_मुक्त_and_track
 *
 * PARAMETERS:  allocation          - Address of the memory to deallocate
 *              component           - Component type of caller
 *              module              - Source file name of caller
 *              line                - Line number of caller
 *
 * RETURN:      None
 *
 * DESCRIPTION: Frees the memory at Allocation
 *
 ******************************************************************************/

व्योम
acpi_ut_मुक्त_and_track(व्योम *allocation,
		       u32 component, स्थिर अक्षर *module, u32 line)
अणु
	काष्ठा acpi_debug_mem_block *debug_block;
	acpi_status status;

	ACPI_FUNCTION_TRACE_PTR(ut_मुक्त, allocation);

	अगर (शून्य == allocation) अणु
		ACPI_ERROR((module, line, "Attempt to delete a NULL address"));

		वापस_VOID;
	पूर्ण

	debug_block = ACPI_CAST_PTR(काष्ठा acpi_debug_mem_block,
				    (((अक्षर *)allocation) -
				     माप(काष्ठा acpi_debug_mem_header)));

	acpi_gbl_global_list->total_मुक्तd++;
	acpi_gbl_global_list->current_total_size -= debug_block->size;

	status =
	    acpi_ut_हटाओ_allocation(debug_block, component, module, line);
	अगर (ACPI_FAILURE(status)) अणु
		ACPI_EXCEPTION((AE_INFO, status, "Could not free memory"));
	पूर्ण

	acpi_os_मुक्त(debug_block);
	ACPI_DEBUG_PRINT((ACPI_DB_ALLOCATIONS, "%p freed (block %p)\n",
			  allocation, debug_block));
	वापस_VOID;
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_find_allocation
 *
 * PARAMETERS:  allocation              - Address of allocated memory
 *
 * RETURN:      Three हालs:
 *              1) List is empty, शून्य is वापसed.
 *              2) Element was found. Returns Allocation parameter.
 *              3) Element was not found. Returns position where it should be
 *                  inserted पूर्णांकo the list.
 *
 * DESCRIPTION: Searches क्रम an element in the global allocation tracking list.
 *              If the element is not found, वापसs the location within the
 *              list where the element should be inserted.
 *
 *              Note: The list is ordered by larger-to-smaller addresses.
 *
 *              This global list is used to detect memory leaks in ACPICA as
 *              well as other issues such as an attempt to release the same
 *              पूर्णांकernal object more than once. Although expensive as far
 *              as cpu समय, this list is much more helpful क्रम finding these
 *              types of issues than using memory leak detectors outside of
 *              the ACPICA code.
 *
 ******************************************************************************/

अटल काष्ठा acpi_debug_mem_block *acpi_ut_find_allocation(काष्ठा
							    acpi_debug_mem_block
							    *allocation)
अणु
	काष्ठा acpi_debug_mem_block *element;

	element = acpi_gbl_global_list->list_head;
	अगर (!element) अणु
		वापस (शून्य);
	पूर्ण

	/*
	 * Search क्रम the address.
	 *
	 * Note: List is ordered by larger-to-smaller addresses, on the
	 * assumption that a new allocation usually has a larger address
	 * than previous allocations.
	 */
	जबतक (element > allocation) अणु

		/* Check क्रम end-of-list */

		अगर (!element->next) अणु
			वापस (element);
		पूर्ण

		element = element->next;
	पूर्ण

	अगर (element == allocation) अणु
		वापस (element);
	पूर्ण

	वापस (element->previous);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_track_allocation
 *
 * PARAMETERS:  allocation          - Address of allocated memory
 *              size                - Size of the allocation
 *              alloc_type          - MEM_MALLOC or MEM_CALLOC
 *              component           - Component type of caller
 *              module              - Source file name of caller
 *              line                - Line number of caller
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Inserts an element पूर्णांकo the global allocation tracking list.
 *
 ******************************************************************************/

अटल acpi_status
acpi_ut_track_allocation(काष्ठा acpi_debug_mem_block *allocation,
			 acpi_size size,
			 u8 alloc_type,
			 u32 component, स्थिर अक्षर *module, u32 line)
अणु
	काष्ठा acpi_memory_list *mem_list;
	काष्ठा acpi_debug_mem_block *element;
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TRACE_PTR(ut_track_allocation, allocation);

	अगर (acpi_gbl_disable_mem_tracking) अणु
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	mem_list = acpi_gbl_global_list;
	status = acpi_ut_acquire_mutex(ACPI_MTX_MEMORY);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/*
	 * Search the global list क्रम this address to make sure it is not
	 * alपढ़ोy present. This will catch several kinds of problems.
	 */
	element = acpi_ut_find_allocation(allocation);
	अगर (element == allocation) अणु
		ACPI_ERROR((AE_INFO,
			    "UtTrackAllocation: Allocation (%p) already present in global list!",
			    allocation));
		जाओ unlock_and_निकास;
	पूर्ण

	/* Fill in the instance data */

	allocation->size = (u32)size;
	allocation->alloc_type = alloc_type;
	allocation->component = component;
	allocation->line = line;

	acpi_ut_safe_म_नकलन(allocation->module, (अक्षर *)module,
			     ACPI_MAX_MODULE_NAME);

	अगर (!element) अणु

		/* Insert at list head */

		अगर (mem_list->list_head) अणु
			((काष्ठा acpi_debug_mem_block *)(mem_list->list_head))->
			    previous = allocation;
		पूर्ण

		allocation->next = mem_list->list_head;
		allocation->previous = शून्य;

		mem_list->list_head = allocation;
	पूर्ण अन्यथा अणु
		/* Insert after element */

		allocation->next = element->next;
		allocation->previous = element;

		अगर (element->next) अणु
			(element->next)->previous = allocation;
		पूर्ण

		element->next = allocation;
	पूर्ण

unlock_and_निकास:
	status = acpi_ut_release_mutex(ACPI_MTX_MEMORY);
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_हटाओ_allocation
 *
 * PARAMETERS:  allocation          - Address of allocated memory
 *              component           - Component type of caller
 *              module              - Source file name of caller
 *              line                - Line number of caller
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Deletes an element from the global allocation tracking list.
 *
 ******************************************************************************/

अटल acpi_status
acpi_ut_हटाओ_allocation(काष्ठा acpi_debug_mem_block *allocation,
			  u32 component, स्थिर अक्षर *module, u32 line)
अणु
	काष्ठा acpi_memory_list *mem_list;
	acpi_status status;

	ACPI_FUNCTION_NAME(ut_हटाओ_allocation);

	अगर (acpi_gbl_disable_mem_tracking) अणु
		वापस (AE_OK);
	पूर्ण

	mem_list = acpi_gbl_global_list;
	अगर (शून्य == mem_list->list_head) अणु

		/* No allocations! */

		ACPI_ERROR((module, line,
			    "Empty allocation list, nothing to free!"));

		वापस (AE_OK);
	पूर्ण

	status = acpi_ut_acquire_mutex(ACPI_MTX_MEMORY);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	/* Unlink */

	अगर (allocation->previous) अणु
		(allocation->previous)->next = allocation->next;
	पूर्ण अन्यथा अणु
		mem_list->list_head = allocation->next;
	पूर्ण

	अगर (allocation->next) अणु
		(allocation->next)->previous = allocation->previous;
	पूर्ण

	ACPI_DEBUG_PRINT((ACPI_DB_ALLOCATIONS, "Freeing %p, size 0%X\n",
			  &allocation->user_space, allocation->size));

	/* Mark the segment as deleted */

	स_रखो(&allocation->user_space, 0xEA, allocation->size);

	status = acpi_ut_release_mutex(ACPI_MTX_MEMORY);
	वापस (status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_dump_allocation_info
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: Prपूर्णांक some info about the outstanding allocations.
 *
 ******************************************************************************/

व्योम acpi_ut_dump_allocation_info(व्योम)
अणु
/*
	काष्ठा acpi_memory_list         *mem_list;
*/

	ACPI_FUNCTION_TRACE(ut_dump_allocation_info);

/*
	ACPI_DEBUG_PRINT (TRACE_ALLOCATIONS | TRACE_TABLES,
		("%30s: %4d (%3d Kb)\n", "Current allocations",
		mem_list->current_count,
		ROUND_UP_TO_1K (mem_list->current_size)));

	ACPI_DEBUG_PRINT (TRACE_ALLOCATIONS | TRACE_TABLES,
		("%30s: %4d (%3d Kb)\n", "Max concurrent allocations",
		mem_list->max_concurrent_count,
		ROUND_UP_TO_1K (mem_list->max_concurrent_size)));

	ACPI_DEBUG_PRINT (TRACE_ALLOCATIONS | TRACE_TABLES,
		("%30s: %4d (%3d Kb)\n", "Total (all) internal objects",
		running_object_count,
		ROUND_UP_TO_1K (running_object_size)));

	ACPI_DEBUG_PRINT (TRACE_ALLOCATIONS | TRACE_TABLES,
		("%30s: %4d (%3d Kb)\n", "Total (all) allocations",
		running_alloc_count,
		ROUND_UP_TO_1K (running_alloc_size)));

	ACPI_DEBUG_PRINT (TRACE_ALLOCATIONS | TRACE_TABLES,
		("%30s: %4d (%3d Kb)\n", "Current Nodes",
		acpi_gbl_current_node_count,
		ROUND_UP_TO_1K (acpi_gbl_current_node_size)));

	ACPI_DEBUG_PRINT (TRACE_ALLOCATIONS | TRACE_TABLES,
		("%30s: %4d (%3d Kb)\n", "Max Nodes",
		acpi_gbl_max_concurrent_node_count,
		ROUND_UP_TO_1K ((acpi_gbl_max_concurrent_node_count *
			माप (काष्ठा acpi_namespace_node)))));
*/
	वापस_VOID;
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_dump_allocations
 *
 * PARAMETERS:  component           - Component(s) to dump info क्रम.
 *              module              - Module to dump info क्रम. शून्य means all.
 *
 * RETURN:      None
 *
 * DESCRIPTION: Prपूर्णांक a list of all outstanding allocations.
 *
 ******************************************************************************/

व्योम acpi_ut_dump_allocations(u32 component, स्थिर अक्षर *module)
अणु
	काष्ठा acpi_debug_mem_block *element;
	जोड़ acpi_descriptor *descriptor;
	u32 num_outstanding = 0;
	u8 descriptor_type;

	ACPI_FUNCTION_TRACE(ut_dump_allocations);

	अगर (acpi_gbl_disable_mem_tracking) अणु
		वापस_VOID;
	पूर्ण

	/*
	 * Walk the allocation list.
	 */
	अगर (ACPI_FAILURE(acpi_ut_acquire_mutex(ACPI_MTX_MEMORY))) अणु
		वापस_VOID;
	पूर्ण

	अगर (!acpi_gbl_global_list) अणु
		जाओ निकास;
	पूर्ण

	element = acpi_gbl_global_list->list_head;
	जबतक (element) अणु
		अगर ((element->component & component) &&
		    ((module == शून्य)
		     || (0 == म_भेद(module, element->module)))) अणु
			descriptor =
			    ACPI_CAST_PTR(जोड़ acpi_descriptor,
					  &element->user_space);

			अगर (element->size <
			    माप(काष्ठा acpi_common_descriptor)) अणु
				acpi_os_म_लिखो("%p Length 0x%04X %9.9s-%4.4u "
					       "[Not a Descriptor - too small]\n",
					       descriptor, element->size,
					       element->module, element->line);
			पूर्ण अन्यथा अणु
				/* Ignore allocated objects that are in a cache */

				अगर (ACPI_GET_DESCRIPTOR_TYPE(descriptor) !=
				    ACPI_DESC_TYPE_CACHED) अणु
					acpi_os_म_लिखो
					    ("%p Length 0x%04X %9.9s-%4.4u [%s] ",
					     descriptor, element->size,
					     element->module, element->line,
					     acpi_ut_get_descriptor_name
					     (descriptor));

					/* Optional object hex dump */

					अगर (acpi_gbl_verbose_leak_dump) अणु
						acpi_os_म_लिखो("\n");
						acpi_ut_dump_buffer((u8 *)
								    descriptor,
								    element->
								    size,
								    DB_BYTE_DISPLAY,
								    0);
					पूर्ण

					/* Validate the descriptor type using Type field and length */

					descriptor_type = 0;	/* Not a valid descriptor type */

					चयन (ACPI_GET_DESCRIPTOR_TYPE
						(descriptor)) अणु
					हाल ACPI_DESC_TYPE_OPERAND:

						अगर (element->size ==
						    माप(जोड़
							   acpi_opeअक्रम_object))
						अणु
							descriptor_type =
							    ACPI_DESC_TYPE_OPERAND;
						पूर्ण
						अवरोध;

					हाल ACPI_DESC_TYPE_PARSER:

						अगर (element->size ==
						    माप(जोड़
							   acpi_parse_object)) अणु
							descriptor_type =
							    ACPI_DESC_TYPE_PARSER;
						पूर्ण
						अवरोध;

					हाल ACPI_DESC_TYPE_NAMED:

						अगर (element->size ==
						    माप(काष्ठा
							   acpi_namespace_node))
						अणु
							descriptor_type =
							    ACPI_DESC_TYPE_NAMED;
						पूर्ण
						अवरोध;

					शेष:

						अवरोध;
					पूर्ण

					/* Display additional info क्रम the major descriptor types */

					चयन (descriptor_type) अणु
					हाल ACPI_DESC_TYPE_OPERAND:

						acpi_os_म_लिखो
						    ("%12.12s RefCount 0x%04X\n",
						     acpi_ut_get_type_name
						     (descriptor->object.common.
						      type),
						     descriptor->object.common.
						     reference_count);
						अवरोध;

					हाल ACPI_DESC_TYPE_PARSER:

						acpi_os_म_लिखो
						    ("AmlOpcode 0x%04X\n",
						     descriptor->op.asl.
						     aml_opcode);
						अवरोध;

					हाल ACPI_DESC_TYPE_NAMED:

						acpi_os_म_लिखो("%4.4s\n",
							       acpi_ut_get_node_name
							       (&descriptor->
								node));
						अवरोध;

					शेष:

						acpi_os_म_लिखो("\n");
						अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण

			num_outstanding++;
		पूर्ण

		element = element->next;
	पूर्ण

निकास:
	(व्योम)acpi_ut_release_mutex(ACPI_MTX_MEMORY);

	/* Prपूर्णांक summary */

	अगर (!num_outstanding) अणु
		ACPI_INFO(("No outstanding allocations"));
	पूर्ण अन्यथा अणु
		ACPI_ERROR((AE_INFO, "%u (0x%X) Outstanding cache allocations",
			    num_outstanding, num_outstanding));
	पूर्ण

	वापस_VOID;
पूर्ण

#पूर्ण_अगर				/* ACPI_DBG_TRACK_ALLOCATIONS */
