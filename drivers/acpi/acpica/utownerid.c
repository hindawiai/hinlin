<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/*******************************************************************************
 *
 * Module Name: utownerid - Support क्रम Table/Method Owner IDs
 *
 ******************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acnamesp.h"

#घोषणा _COMPONENT          ACPI_UTILITIES
ACPI_MODULE_NAME("utownerid")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_allocate_owner_id
 *
 * PARAMETERS:  owner_id        - Where the new owner ID is वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Allocate a table or method owner ID. The owner ID is used to
 *              track objects created by the table or method, to be deleted
 *              when the method निकासs or the table is unloaded.
 *
 ******************************************************************************/
acpi_status acpi_ut_allocate_owner_id(acpi_owner_id *owner_id)
अणु
	u32 i;
	u32 j;
	u32 k;
	acpi_status status;

	ACPI_FUNCTION_TRACE(ut_allocate_owner_id);

	/* Guard against multiple allocations of ID to the same location */

	अगर (*owner_id) अणु
		ACPI_ERROR((AE_INFO,
			    "Owner ID [0x%3.3X] already exists", *owner_id));
		वापस_ACPI_STATUS(AE_ALREADY_EXISTS);
	पूर्ण

	/* Mutex क्रम the global ID mask */

	status = acpi_ut_acquire_mutex(ACPI_MTX_CACHES);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/*
	 * Find a मुक्त owner ID, cycle through all possible IDs on repeated
	 * allocations. (ACPI_NUM_OWNERID_MASKS + 1) because first index
	 * may have to be scanned twice.
	 */
	क्रम (i = 0, j = acpi_gbl_last_owner_id_index;
	     i < (ACPI_NUM_OWNERID_MASKS + 1); i++, j++) अणु
		अगर (j >= ACPI_NUM_OWNERID_MASKS) अणु
			j = 0;	/* Wraparound to start of mask array */
		पूर्ण

		क्रम (k = acpi_gbl_next_owner_id_offset; k < 32; k++) अणु
			अगर (acpi_gbl_owner_id_mask[j] == ACPI_UINT32_MAX) अणु

				/* There are no मुक्त IDs in this mask */

				अवरोध;
			पूर्ण

			/*
			 * Note: the u32 cast ensures that 1 is stored as a अचिन्हित
			 * पूर्णांकeger. Omitting the cast may result in 1 being stored as an
			 * पूर्णांक. Some compilers or runसमय error detection may flag this as
			 * an error.
			 */
			अगर (!(acpi_gbl_owner_id_mask[j] & ((u32)1 << k))) अणु
				/*
				 * Found a मुक्त ID. The actual ID is the bit index plus one,
				 * making zero an invalid Owner ID. Save this as the last ID
				 * allocated and update the global ID mask.
				 */
				acpi_gbl_owner_id_mask[j] |= ((u32)1 << k);

				acpi_gbl_last_owner_id_index = (u8)j;
				acpi_gbl_next_owner_id_offset = (u8)(k + 1);

				/*
				 * Conकाष्ठा encoded ID from the index and bit position
				 *
				 * Note: Last [j].k (bit 4095) is never used and is marked
				 * permanently allocated (prevents +1 overflow)
				 */
				*owner_id =
				    (acpi_owner_id)((k + 1) + ACPI_MUL_32(j));

				ACPI_DEBUG_PRINT((ACPI_DB_VALUES,
						  "Allocated OwnerId: 0x%3.3X\n",
						  (अचिन्हित पूर्णांक)*owner_id));
				जाओ निकास;
			पूर्ण
		पूर्ण

		acpi_gbl_next_owner_id_offset = 0;
	पूर्ण

	/*
	 * All owner_ids have been allocated. This typically should
	 * not happen since the IDs are reused after deallocation. The IDs are
	 * allocated upon table load (one per table) and method execution, and
	 * they are released when a table is unloaded or a method completes
	 * execution.
	 *
	 * If this error happens, there may be very deep nesting of invoked
	 * control methods, or there may be a bug where the IDs are not released.
	 */
	status = AE_OWNER_ID_LIMIT;
	ACPI_ERROR((AE_INFO,
		    "Could not allocate new OwnerId (4095 max), AE_OWNER_ID_LIMIT"));

निकास:
	(व्योम)acpi_ut_release_mutex(ACPI_MTX_CACHES);
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_release_owner_id
 *
 * PARAMETERS:  owner_id_ptr        - Poपूर्णांकer to a previously allocated owner_ID
 *
 * RETURN:      None. No error is वापसed because we are either निकासing a
 *              control method or unloading a table. Either way, we would
 *              ignore any error anyway.
 *
 * DESCRIPTION: Release a table or method owner ID. Valid IDs are 1 - 255
 *
 ******************************************************************************/

व्योम acpi_ut_release_owner_id(acpi_owner_id *owner_id_ptr)
अणु
	acpi_owner_id owner_id = *owner_id_ptr;
	acpi_status status;
	u32 index;
	u32 bit;

	ACPI_FUNCTION_TRACE_U32(ut_release_owner_id, owner_id);

	/* Always clear the input owner_id (zero is an invalid ID) */

	*owner_id_ptr = 0;

	/* Zero is not a valid owner_ID */

	अगर (owner_id == 0) अणु
		ACPI_ERROR((AE_INFO, "Invalid OwnerId: 0x%3.3X", owner_id));
		वापस_VOID;
	पूर्ण

	/* Mutex क्रम the global ID mask */

	status = acpi_ut_acquire_mutex(ACPI_MTX_CACHES);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_VOID;
	पूर्ण

	/* Normalize the ID to zero */

	owner_id--;

	/* Decode ID to index/offset pair */

	index = ACPI_DIV_32(owner_id);
	bit = (u32)1 << ACPI_MOD_32(owner_id);

	/* Free the owner ID only अगर it is valid */

	अगर (acpi_gbl_owner_id_mask[index] & bit) अणु
		acpi_gbl_owner_id_mask[index] ^= bit;
	पूर्ण अन्यथा अणु
		ACPI_ERROR((AE_INFO,
			    "Attempted release of non-allocated OwnerId: 0x%3.3X",
			    owner_id + 1));
	पूर्ण

	(व्योम)acpi_ut_release_mutex(ACPI_MTX_CACHES);
	वापस_VOID;
पूर्ण
