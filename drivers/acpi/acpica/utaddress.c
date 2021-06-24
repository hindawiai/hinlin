<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: utaddress - op_region address range check
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acnamesp.h"

#घोषणा _COMPONENT          ACPI_UTILITIES
ACPI_MODULE_NAME("utaddress")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_add_address_range
 *
 * PARAMETERS:  space_id            - Address space ID
 *              address             - op_region start address
 *              length              - op_region length
 *              region_node         - op_region namespace node
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Add the Operation Region address range to the global list.
 *              The only supported Space IDs are Memory and I/O. Called when
 *              the op_region address/length opeअक्रमs are fully evaluated.
 *
 * MUTEX:       Locks the namespace
 *
 * NOTE: Because this पूर्णांकerface is only called when an op_region argument
 * list is evaluated, there cannot be any duplicate region_nodes.
 * Duplicate Address/Length values are allowed, however, so that multiple
 * address conflicts can be detected.
 *
 ******************************************************************************/
acpi_status
acpi_ut_add_address_range(acpi_adr_space_type space_id,
			  acpi_physical_address address,
			  u32 length, काष्ठा acpi_namespace_node *region_node)
अणु
	काष्ठा acpi_address_range *range_info;

	ACPI_FUNCTION_TRACE(ut_add_address_range);

	अगर ((space_id != ACPI_ADR_SPACE_SYSTEM_MEMORY) &&
	    (space_id != ACPI_ADR_SPACE_SYSTEM_IO)) अणु
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	/* Allocate/init a new info block, add it to the appropriate list */

	range_info = ACPI_ALLOCATE(माप(काष्ठा acpi_address_range));
	अगर (!range_info) अणु
		वापस_ACPI_STATUS(AE_NO_MEMORY);
	पूर्ण

	range_info->start_address = address;
	range_info->end_address = (address + length - 1);
	range_info->region_node = region_node;

	range_info->next = acpi_gbl_address_range_list[space_id];
	acpi_gbl_address_range_list[space_id] = range_info;

	ACPI_DEBUG_PRINT((ACPI_DB_NAMES,
			  "\nAdded [%4.4s] address range: 0x%8.8X%8.8X-0x%8.8X%8.8X\n",
			  acpi_ut_get_node_name(range_info->region_node),
			  ACPI_FORMAT_UINT64(address),
			  ACPI_FORMAT_UINT64(range_info->end_address)));

	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_हटाओ_address_range
 *
 * PARAMETERS:  space_id            - Address space ID
 *              region_node         - op_region namespace node
 *
 * RETURN:      None
 *
 * DESCRIPTION: Remove the Operation Region from the global list. The only
 *              supported Space IDs are Memory and I/O. Called when an
 *              op_region is deleted.
 *
 * MUTEX:       Assumes the namespace is locked
 *
 ******************************************************************************/

व्योम
acpi_ut_हटाओ_address_range(acpi_adr_space_type space_id,
			     काष्ठा acpi_namespace_node *region_node)
अणु
	काष्ठा acpi_address_range *range_info;
	काष्ठा acpi_address_range *prev;

	ACPI_FUNCTION_TRACE(ut_हटाओ_address_range);

	अगर ((space_id != ACPI_ADR_SPACE_SYSTEM_MEMORY) &&
	    (space_id != ACPI_ADR_SPACE_SYSTEM_IO)) अणु
		वापस_VOID;
	पूर्ण

	/* Get the appropriate list head and check the list */

	range_info = prev = acpi_gbl_address_range_list[space_id];
	जबतक (range_info) अणु
		अगर (range_info->region_node == region_node) अणु
			अगर (range_info == prev) अणु	/* Found at list head */
				acpi_gbl_address_range_list[space_id] =
				    range_info->next;
			पूर्ण अन्यथा अणु
				prev->next = range_info->next;
			पूर्ण

			ACPI_DEBUG_PRINT((ACPI_DB_NAMES,
					  "\nRemoved [%4.4s] address range: 0x%8.8X%8.8X-0x%8.8X%8.8X\n",
					  acpi_ut_get_node_name(range_info->
								region_node),
					  ACPI_FORMAT_UINT64(range_info->
							     start_address),
					  ACPI_FORMAT_UINT64(range_info->
							     end_address)));

			ACPI_FREE(range_info);
			वापस_VOID;
		पूर्ण

		prev = range_info;
		range_info = range_info->next;
	पूर्ण

	वापस_VOID;
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_check_address_range
 *
 * PARAMETERS:  space_id            - Address space ID
 *              address             - Start address
 *              length              - Length of address range
 *              warn                - TRUE अगर warning on overlap desired
 *
 * RETURN:      Count of the number of conflicts detected. Zero is always
 *              वापसed क्रम Space IDs other than Memory or I/O.
 *
 * DESCRIPTION: Check अगर the input address range overlaps any of the
 *              ASL operation region address ranges. The only supported
 *              Space IDs are Memory and I/O.
 *
 * MUTEX:       Assumes the namespace is locked.
 *
 ******************************************************************************/

u32
acpi_ut_check_address_range(acpi_adr_space_type space_id,
			    acpi_physical_address address, u32 length, u8 warn)
अणु
	काष्ठा acpi_address_range *range_info;
	acpi_physical_address end_address;
	अक्षर *pathname;
	u32 overlap_count = 0;

	ACPI_FUNCTION_TRACE(ut_check_address_range);

	अगर ((space_id != ACPI_ADR_SPACE_SYSTEM_MEMORY) &&
	    (space_id != ACPI_ADR_SPACE_SYSTEM_IO)) अणु
		वापस_UINT32(0);
	पूर्ण

	range_info = acpi_gbl_address_range_list[space_id];
	end_address = address + length - 1;

	/* Check entire list क्रम all possible conflicts */

	जबतक (range_info) अणु
		/*
		 * Check अगर the requested address/length overlaps this
		 * address range. There are four हालs to consider:
		 *
		 * 1) Input address/length is contained completely in the
		 *    address range
		 * 2) Input address/length overlaps range at the range start
		 * 3) Input address/length overlaps range at the range end
		 * 4) Input address/length completely encompasses the range
		 */
		अगर ((address <= range_info->end_address) &&
		    (end_address >= range_info->start_address)) अणु

			/* Found an address range overlap */

			overlap_count++;
			अगर (warn) अणु	/* Optional warning message */
				pathname =
				    acpi_ns_get_normalized_pathname(range_info->
								    region_node,
								    TRUE);

				ACPI_WARNING((AE_INFO,
					      "%s range 0x%8.8X%8.8X-0x%8.8X%8.8X conflicts with OpRegion 0x%8.8X%8.8X-0x%8.8X%8.8X (%s)",
					      acpi_ut_get_region_name(space_id),
					      ACPI_FORMAT_UINT64(address),
					      ACPI_FORMAT_UINT64(end_address),
					      ACPI_FORMAT_UINT64(range_info->
								 start_address),
					      ACPI_FORMAT_UINT64(range_info->
								 end_address),
					      pathname));
				ACPI_FREE(pathname);
			पूर्ण
		पूर्ण

		range_info = range_info->next;
	पूर्ण

	वापस_UINT32(overlap_count);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_delete_address_lists
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: Delete all global address range lists (called during
 *              subप्रणाली shutकरोwn).
 *
 ******************************************************************************/

व्योम acpi_ut_delete_address_lists(व्योम)
अणु
	काष्ठा acpi_address_range *next;
	काष्ठा acpi_address_range *range_info;
	पूर्णांक i;

	/* Delete all elements in all address range lists */

	क्रम (i = 0; i < ACPI_ADDRESS_RANGE_MAX; i++) अणु
		next = acpi_gbl_address_range_list[i];

		जबतक (next) अणु
			range_info = next;
			next = range_info->next;
			ACPI_FREE(range_info);
		पूर्ण

		acpi_gbl_address_range_list[i] = शून्य;
	पूर्ण
पूर्ण
