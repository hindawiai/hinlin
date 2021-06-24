<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: tbxfroot - Find the root ACPI table (RSDT)
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "actables.h"

#घोषणा _COMPONENT          ACPI_TABLES
ACPI_MODULE_NAME("tbxfroot")

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_get_rsdp_length
 *
 * PARAMETERS:  rsdp                - Poपूर्णांकer to RSDP
 *
 * RETURN:      Table length
 *
 * DESCRIPTION: Get the length of the RSDP
 *
 ******************************************************************************/
u32 acpi_tb_get_rsdp_length(काष्ठा acpi_table_rsdp *rsdp)
अणु

	अगर (!ACPI_VALIDATE_RSDP_SIG(rsdp->signature)) अणु

		/* BAD Signature */

		वापस (0);
	पूर्ण

	/* "Length" field is available अगर table version >= 2 */

	अगर (rsdp->revision >= 2) अणु
		वापस (rsdp->length);
	पूर्ण अन्यथा अणु
		वापस (ACPI_RSDP_CHECKSUM_LENGTH);
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_validate_rsdp
 *
 * PARAMETERS:  rsdp                - Poपूर्णांकer to unvalidated RSDP
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Validate the RSDP (ptr)
 *
 ******************************************************************************/

acpi_status acpi_tb_validate_rsdp(काष्ठा acpi_table_rsdp *rsdp)
अणु

	/*
	 * The signature and checksum must both be correct
	 *
	 * Note: Someबार there exists more than one RSDP in memory; the valid
	 * RSDP has a valid checksum, all others have an invalid checksum.
	 */
	अगर (!ACPI_VALIDATE_RSDP_SIG(rsdp->signature)) अणु

		/* Nope, BAD Signature */

		वापस (AE_BAD_SIGNATURE);
	पूर्ण

	/* Check the standard checksum */

	अगर (acpi_tb_checksum((u8 *) rsdp, ACPI_RSDP_CHECKSUM_LENGTH) != 0) अणु
		वापस (AE_BAD_CHECKSUM);
	पूर्ण

	/* Check extended checksum अगर table version >= 2 */

	अगर ((rsdp->revision >= 2) &&
	    (acpi_tb_checksum((u8 *) rsdp, ACPI_RSDP_XCHECKSUM_LENGTH) != 0)) अणु
		वापस (AE_BAD_CHECKSUM);
	पूर्ण

	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_find_root_poपूर्णांकer
 *
 * PARAMETERS:  table_address           - Where the table poपूर्णांकer is वापसed
 *
 * RETURN:      Status, RSDP physical address
 *
 * DESCRIPTION: Search lower 1Mbyte of memory क्रम the root प्रणाली descriptor
 *              poपूर्णांकer काष्ठाure. If it is found, set *RSDP to poपूर्णांक to it.
 *
 * NOTE1:       The RSDP must be either in the first 1K of the Extended
 *              BIOS Data Area or between E0000 and FFFFF (From ACPI Spec.)
 *              Only a 32-bit physical address is necessary.
 *
 * NOTE2:       This function is always available, regardless of the
 *              initialization state of the rest of ACPI.
 *
 ******************************************************************************/

acpi_status ACPI_INIT_FUNCTION
acpi_find_root_poपूर्णांकer(acpi_physical_address *table_address)
अणु
	u8 *table_ptr;
	u8 *mem_rover;
	u32 physical_address;

	ACPI_FUNCTION_TRACE(acpi_find_root_poपूर्णांकer);

	/* 1a) Get the location of the Extended BIOS Data Area (EBDA) */

	table_ptr = acpi_os_map_memory((acpi_physical_address)
				       ACPI_EBDA_PTR_LOCATION,
				       ACPI_EBDA_PTR_LENGTH);
	अगर (!table_ptr) अणु
		ACPI_ERROR((AE_INFO,
			    "Could not map memory at 0x%8.8X for length %u",
			    ACPI_EBDA_PTR_LOCATION, ACPI_EBDA_PTR_LENGTH));

		वापस_ACPI_STATUS(AE_NO_MEMORY);
	पूर्ण

	ACPI_MOVE_16_TO_32(&physical_address, table_ptr);

	/* Convert segment part to physical address */

	physical_address <<= 4;
	acpi_os_unmap_memory(table_ptr, ACPI_EBDA_PTR_LENGTH);

	/* EBDA present? */

	अगर (physical_address > 0x400) अणु
		/*
		 * 1b) Search EBDA paragraphs (EBDA is required to be a
		 *     minimum of 1K length)
		 */
		table_ptr = acpi_os_map_memory((acpi_physical_address)
					       physical_address,
					       ACPI_EBDA_WINDOW_SIZE);
		अगर (!table_ptr) अणु
			ACPI_ERROR((AE_INFO,
				    "Could not map memory at 0x%8.8X for length %u",
				    physical_address, ACPI_EBDA_WINDOW_SIZE));

			वापस_ACPI_STATUS(AE_NO_MEMORY);
		पूर्ण

		mem_rover =
		    acpi_tb_scan_memory_क्रम_rsdp(table_ptr,
						 ACPI_EBDA_WINDOW_SIZE);
		acpi_os_unmap_memory(table_ptr, ACPI_EBDA_WINDOW_SIZE);

		अगर (mem_rover) अणु

			/* Return the physical address */

			physical_address +=
			    (u32) ACPI_PTR_DIFF(mem_rover, table_ptr);

			*table_address =
			    (acpi_physical_address)physical_address;
			वापस_ACPI_STATUS(AE_OK);
		पूर्ण
	पूर्ण

	/*
	 * 2) Search upper memory: 16-byte boundaries in E0000h-FFFFFh
	 */
	table_ptr = acpi_os_map_memory((acpi_physical_address)
				       ACPI_HI_RSDP_WINDOW_BASE,
				       ACPI_HI_RSDP_WINDOW_SIZE);

	अगर (!table_ptr) अणु
		ACPI_ERROR((AE_INFO,
			    "Could not map memory at 0x%8.8X for length %u",
			    ACPI_HI_RSDP_WINDOW_BASE,
			    ACPI_HI_RSDP_WINDOW_SIZE));

		वापस_ACPI_STATUS(AE_NO_MEMORY);
	पूर्ण

	mem_rover =
	    acpi_tb_scan_memory_क्रम_rsdp(table_ptr, ACPI_HI_RSDP_WINDOW_SIZE);
	acpi_os_unmap_memory(table_ptr, ACPI_HI_RSDP_WINDOW_SIZE);

	अगर (mem_rover) अणु

		/* Return the physical address */

		physical_address = (u32)
		    (ACPI_HI_RSDP_WINDOW_BASE +
		     ACPI_PTR_DIFF(mem_rover, table_ptr));

		*table_address = (acpi_physical_address)physical_address;
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	/* A valid RSDP was not found */

	ACPI_BIOS_ERROR((AE_INFO, "A valid RSDP was not found"));
	वापस_ACPI_STATUS(AE_NOT_FOUND);
पूर्ण

ACPI_EXPORT_SYMBOL_INIT(acpi_find_root_poपूर्णांकer)

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_scan_memory_क्रम_rsdp
 *
 * PARAMETERS:  start_address       - Starting poपूर्णांकer क्रम search
 *              length              - Maximum length to search
 *
 * RETURN:      Poपूर्णांकer to the RSDP अगर found, otherwise शून्य.
 *
 * DESCRIPTION: Search a block of memory क्रम the RSDP signature
 *
 ******************************************************************************/
u8 *acpi_tb_scan_memory_क्रम_rsdp(u8 *start_address, u32 length)
अणु
	acpi_status status;
	u8 *mem_rover;
	u8 *end_address;

	ACPI_FUNCTION_TRACE(tb_scan_memory_क्रम_rsdp);

	end_address = start_address + length;

	/* Search from given start address क्रम the requested length */

	क्रम (mem_rover = start_address; mem_rover < end_address;
	     mem_rover += ACPI_RSDP_SCAN_STEP) अणु

		/* The RSDP signature and checksum must both be correct */

		status =
		    acpi_tb_validate_rsdp(ACPI_CAST_PTR
					  (काष्ठा acpi_table_rsdp, mem_rover));
		अगर (ACPI_SUCCESS(status)) अणु

			/* Sig and checksum valid, we have found a real RSDP */

			ACPI_DEBUG_PRINT((ACPI_DB_INFO,
					  "RSDP located at physical address %p\n",
					  mem_rover));
			वापस_PTR(mem_rover);
		पूर्ण

		/* No sig match or bad checksum, keep searching */
	पूर्ण

	/* Searched entire block, no RSDP was found */

	ACPI_DEBUG_PRINT((ACPI_DB_INFO,
			  "Searched entire block from %p, valid RSDP was not found\n",
			  start_address));
	वापस_PTR(शून्य);
पूर्ण
