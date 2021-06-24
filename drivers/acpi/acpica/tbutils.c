<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: tbutils - ACPI Table utilities
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "actables.h"

#घोषणा _COMPONENT          ACPI_TABLES
ACPI_MODULE_NAME("tbutils")

/* Local prototypes */
अटल acpi_physical_address
acpi_tb_get_root_table_entry(u8 *table_entry, u32 table_entry_size);

#अगर (!ACPI_REDUCED_HARDWARE)
/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_initialize_facs
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Create a permanent mapping क्रम the FADT and save it in a global
 *              क्रम accessing the Global Lock and Firmware Waking Vector
 *
 ******************************************************************************/

acpi_status acpi_tb_initialize_facs(व्योम)
अणु
	काष्ठा acpi_table_facs *facs;

	/* If Hardware Reduced flag is set, there is no FACS */

	अगर (acpi_gbl_reduced_hardware) अणु
		acpi_gbl_FACS = शून्य;
		वापस (AE_OK);
	पूर्ण अन्यथा अगर (acpi_gbl_FADT.Xfacs &&
		   (!acpi_gbl_FADT.facs
		    || !acpi_gbl_use32_bit_facs_addresses)) अणु
		(व्योम)acpi_get_table_by_index(acpi_gbl_xfacs_index,
					      ACPI_CAST_INसूचीECT_PTR(काष्ठा
								     acpi_table_header,
								     &facs));
		acpi_gbl_FACS = facs;
	पूर्ण अन्यथा अगर (acpi_gbl_FADT.facs) अणु
		(व्योम)acpi_get_table_by_index(acpi_gbl_facs_index,
					      ACPI_CAST_INसूचीECT_PTR(काष्ठा
								     acpi_table_header,
								     &facs));
		acpi_gbl_FACS = facs;
	पूर्ण

	/* If there is no FACS, just जारी. There was alपढ़ोy an error msg */

	वापस (AE_OK);
पूर्ण
#पूर्ण_अगर				/* !ACPI_REDUCED_HARDWARE */

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_check_dsdt_header
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: Quick compare to check validity of the DSDT. This will detect
 *              अगर the DSDT has been replaced from outside the OS and/or अगर
 *              the DSDT header has been corrupted.
 *
 ******************************************************************************/

व्योम acpi_tb_check_dsdt_header(व्योम)
अणु

	/* Compare original length and checksum to current values */

	अगर (acpi_gbl_original_dsdt_header.length != acpi_gbl_DSDT->length ||
	    acpi_gbl_original_dsdt_header.checksum != acpi_gbl_DSDT->checksum) अणु
		ACPI_BIOS_ERROR((AE_INFO,
				 "The DSDT has been corrupted or replaced - "
				 "old, new headers below"));

		acpi_tb_prपूर्णांक_table_header(0, &acpi_gbl_original_dsdt_header);
		acpi_tb_prपूर्णांक_table_header(0, acpi_gbl_DSDT);

		ACPI_ERROR((AE_INFO,
			    "Please send DMI info to linux-acpi@vger.kernel.org\n"
			    "If system does not work as expected, please boot with acpi=copy_dsdt"));

		/* Disable further error messages */

		acpi_gbl_original_dsdt_header.length = acpi_gbl_DSDT->length;
		acpi_gbl_original_dsdt_header.checksum =
		    acpi_gbl_DSDT->checksum;
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_copy_dsdt
 *
 * PARAMETERS:  table_index         - Index of installed table to copy
 *
 * RETURN:      The copied DSDT
 *
 * DESCRIPTION: Implements a subप्रणाली option to copy the DSDT to local memory.
 *              Some very bad BIOSs are known to either corrupt the DSDT or
 *              install a new, bad DSDT. This copy works around the problem.
 *
 ******************************************************************************/

काष्ठा acpi_table_header *acpi_tb_copy_dsdt(u32 table_index)
अणु
	काष्ठा acpi_table_header *new_table;
	काष्ठा acpi_table_desc *table_desc;

	table_desc = &acpi_gbl_root_table_list.tables[table_index];

	new_table = ACPI_ALLOCATE(table_desc->length);
	अगर (!new_table) अणु
		ACPI_ERROR((AE_INFO, "Could not copy DSDT of length 0x%X",
			    table_desc->length));
		वापस (शून्य);
	पूर्ण

	स_नकल(new_table, table_desc->poपूर्णांकer, table_desc->length);
	acpi_tb_uninstall_table(table_desc);

	acpi_tb_init_table_descriptor(&acpi_gbl_root_table_list.
				      tables[acpi_gbl_dsdt_index],
				      ACPI_PTR_TO_PHYSADDR(new_table),
				      ACPI_TABLE_ORIGIN_INTERNAL_VIRTUAL,
				      new_table);

	ACPI_INFO(("Forced DSDT copy: length 0x%05X copied locally, original unmapped", new_table->length));

	वापस (new_table);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_get_root_table_entry
 *
 * PARAMETERS:  table_entry         - Poपूर्णांकer to the RSDT/XSDT table entry
 *              table_entry_size    - माप 32 or 64 (RSDT or XSDT)
 *
 * RETURN:      Physical address extracted from the root table
 *
 * DESCRIPTION: Get one root table entry. Handles 32-bit and 64-bit हालs on
 *              both 32-bit and 64-bit platक्रमms
 *
 * NOTE:        acpi_physical_address is 32-bit on 32-bit platक्रमms, 64-bit on
 *              64-bit platक्रमms.
 *
 ******************************************************************************/

अटल acpi_physical_address
acpi_tb_get_root_table_entry(u8 *table_entry, u32 table_entry_size)
अणु
	u64 address64;

	/*
	 * Get the table physical address (32-bit क्रम RSDT, 64-bit क्रम XSDT):
	 * Note: Addresses are 32-bit aligned (not 64) in both RSDT and XSDT
	 */
	अगर (table_entry_size == ACPI_RSDT_ENTRY_SIZE) अणु
		/*
		 * 32-bit platक्रमm, RSDT: Return 32-bit table entry
		 * 64-bit platक्रमm, RSDT: Expand 32-bit to 64-bit and वापस
		 */
		वापस ((acpi_physical_address)
			(*ACPI_CAST_PTR(u32, table_entry)));
	पूर्ण अन्यथा अणु
		/*
		 * 32-bit platक्रमm, XSDT: Truncate 64-bit to 32-bit and वापस
		 * 64-bit platक्रमm, XSDT: Move (unaligned) 64-bit to local,
		 *  वापस 64-bit
		 */
		ACPI_MOVE_64_TO_64(&address64, table_entry);

#अगर ACPI_MACHINE_WIDTH == 32
		अगर (address64 > ACPI_UINT32_MAX) अणु

			/* Will truncate 64-bit address to 32 bits, issue warning */

			ACPI_BIOS_WARNING((AE_INFO,
					   "64-bit Physical Address in XSDT is too large (0x%8.8X%8.8X),"
					   " truncating",
					   ACPI_FORMAT_UINT64(address64)));
		पूर्ण
#पूर्ण_अगर
		वापस ((acpi_physical_address)(address64));
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_parse_root_table
 *
 * PARAMETERS:  rsdp_address        - Poपूर्णांकer to the RSDP
 *
 * RETURN:      Status
 *
 * DESCRIPTION: This function is called to parse the Root System Description
 *              Table (RSDT or XSDT)
 *
 * NOTE:        Tables are mapped (not copied) क्रम efficiency. The FACS must
 *              be mapped and cannot be copied because it contains the actual
 *              memory location of the ACPI Global Lock.
 *
 ******************************************************************************/

acpi_status ACPI_INIT_FUNCTION
acpi_tb_parse_root_table(acpi_physical_address rsdp_address)
अणु
	काष्ठा acpi_table_rsdp *rsdp;
	u32 table_entry_size;
	u32 i;
	u32 table_count;
	काष्ठा acpi_table_header *table;
	acpi_physical_address address;
	u32 length;
	u8 *table_entry;
	acpi_status status;
	u32 table_index;

	ACPI_FUNCTION_TRACE(tb_parse_root_table);

	/* Map the entire RSDP and extract the address of the RSDT or XSDT */

	rsdp = acpi_os_map_memory(rsdp_address, माप(काष्ठा acpi_table_rsdp));
	अगर (!rsdp) अणु
		वापस_ACPI_STATUS(AE_NO_MEMORY);
	पूर्ण

	acpi_tb_prपूर्णांक_table_header(rsdp_address,
				   ACPI_CAST_PTR(काष्ठा acpi_table_header,
						 rsdp));

	/* Use XSDT अगर present and not overridden. Otherwise, use RSDT */

	अगर ((rsdp->revision > 1) &&
	    rsdp->xsdt_physical_address && !acpi_gbl_करो_not_use_xsdt) अणु
		/*
		 * RSDP contains an XSDT (64-bit physical addresses). We must use
		 * the XSDT अगर the revision is > 1 and the XSDT poपूर्णांकer is present,
		 * as per the ACPI specअगरication.
		 */
		address = (acpi_physical_address)rsdp->xsdt_physical_address;
		table_entry_size = ACPI_XSDT_ENTRY_SIZE;
	पूर्ण अन्यथा अणु
		/* Root table is an RSDT (32-bit physical addresses) */

		address = (acpi_physical_address)rsdp->rsdt_physical_address;
		table_entry_size = ACPI_RSDT_ENTRY_SIZE;
	पूर्ण

	/*
	 * It is not possible to map more than one entry in some environments,
	 * so unmap the RSDP here beक्रमe mapping other tables
	 */
	acpi_os_unmap_memory(rsdp, माप(काष्ठा acpi_table_rsdp));

	/* Map the RSDT/XSDT table header to get the full table length */

	table = acpi_os_map_memory(address, माप(काष्ठा acpi_table_header));
	अगर (!table) अणु
		वापस_ACPI_STATUS(AE_NO_MEMORY);
	पूर्ण

	acpi_tb_prपूर्णांक_table_header(address, table);

	/*
	 * Validate length of the table, and map entire table.
	 * Minimum length table must contain at least one entry.
	 */
	length = table->length;
	acpi_os_unmap_memory(table, माप(काष्ठा acpi_table_header));

	अगर (length < (माप(काष्ठा acpi_table_header) + table_entry_size)) अणु
		ACPI_BIOS_ERROR((AE_INFO,
				 "Invalid table length 0x%X in RSDT/XSDT",
				 length));
		वापस_ACPI_STATUS(AE_INVALID_TABLE_LENGTH);
	पूर्ण

	table = acpi_os_map_memory(address, length);
	अगर (!table) अणु
		वापस_ACPI_STATUS(AE_NO_MEMORY);
	पूर्ण

	/* Validate the root table checksum */

	status = acpi_tb_verअगरy_checksum(table, length);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_os_unmap_memory(table, length);
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Get the number of entries and poपूर्णांकer to first entry */

	table_count = (u32)((table->length - माप(काष्ठा acpi_table_header)) /
			    table_entry_size);
	table_entry = ACPI_ADD_PTR(u8, table, माप(काष्ठा acpi_table_header));

	/* Initialize the root table array from the RSDT/XSDT */

	क्रम (i = 0; i < table_count; i++) अणु

		/* Get the table physical address (32-bit क्रम RSDT, 64-bit क्रम XSDT) */

		address =
		    acpi_tb_get_root_table_entry(table_entry, table_entry_size);

		/* Skip शून्य entries in RSDT/XSDT */

		अगर (!address) अणु
			जाओ next_table;
		पूर्ण

		status = acpi_tb_install_standard_table(address,
							ACPI_TABLE_ORIGIN_INTERNAL_PHYSICAL,
							FALSE, TRUE,
							&table_index);

		अगर (ACPI_SUCCESS(status) &&
		    ACPI_COMPARE_NAMESEG(&acpi_gbl_root_table_list.
					 tables[table_index].signature,
					 ACPI_SIG_FADT)) अणु
			acpi_gbl_fadt_index = table_index;
			acpi_tb_parse_fadt();
		पूर्ण

next_table:

		table_entry += table_entry_size;
	पूर्ण

	acpi_os_unmap_memory(table, length);
	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_get_table
 *
 * PARAMETERS:  table_desc          - Table descriptor
 *              out_table           - Where the poपूर्णांकer to the table is वापसed
 *
 * RETURN:      Status and poपूर्णांकer to the requested table
 *
 * DESCRIPTION: Increase a reference to a table descriptor and वापस the
 *              validated table poपूर्णांकer.
 *              If the table descriptor is an entry of the root table list,
 *              this API must be invoked with ACPI_MTX_TABLES acquired.
 *
 ******************************************************************************/

acpi_status
acpi_tb_get_table(काष्ठा acpi_table_desc *table_desc,
		  काष्ठा acpi_table_header **out_table)
अणु
	acpi_status status;

	ACPI_FUNCTION_TRACE(acpi_tb_get_table);

	अगर (table_desc->validation_count == 0) अणु

		/* Table need to be "VALIDATED" */

		status = acpi_tb_validate_table(table_desc);
		अगर (ACPI_FAILURE(status)) अणु
			वापस_ACPI_STATUS(status);
		पूर्ण
	पूर्ण

	अगर (table_desc->validation_count < ACPI_MAX_TABLE_VALIDATIONS) अणु
		table_desc->validation_count++;

		/*
		 * Detect validation_count overflows to ensure that the warning
		 * message will only be prपूर्णांकed once.
		 */
		अगर (table_desc->validation_count >= ACPI_MAX_TABLE_VALIDATIONS) अणु
			ACPI_WARNING((AE_INFO,
				      "Table %p, Validation count overflows\n",
				      table_desc));
		पूर्ण
	पूर्ण

	*out_table = table_desc->poपूर्णांकer;
	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_put_table
 *
 * PARAMETERS:  table_desc          - Table descriptor
 *
 * RETURN:      None
 *
 * DESCRIPTION: Decrease a reference to a table descriptor and release the
 *              validated table poपूर्णांकer अगर no references.
 *              If the table descriptor is an entry of the root table list,
 *              this API must be invoked with ACPI_MTX_TABLES acquired.
 *
 ******************************************************************************/

व्योम acpi_tb_put_table(काष्ठा acpi_table_desc *table_desc)
अणु

	ACPI_FUNCTION_TRACE(acpi_tb_put_table);

	अगर (table_desc->validation_count < ACPI_MAX_TABLE_VALIDATIONS) अणु
		table_desc->validation_count--;

		/*
		 * Detect validation_count underflows to ensure that the warning
		 * message will only be prपूर्णांकed once.
		 */
		अगर (table_desc->validation_count >= ACPI_MAX_TABLE_VALIDATIONS) अणु
			ACPI_WARNING((AE_INFO,
				      "Table %p, Validation count underflows\n",
				      table_desc));
			वापस_VOID;
		पूर्ण
	पूर्ण

	अगर (table_desc->validation_count == 0) अणु

		/* Table need to be "INVALIDATED" */

		acpi_tb_invalidate_table(table_desc);
	पूर्ण

	वापस_VOID;
पूर्ण
