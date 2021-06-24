<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: oslinuxtbl - Linux OSL क्रम obtaining ACPI tables
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश "acpidump.h"

#घोषणा _COMPONENT          ACPI_OS_SERVICES
ACPI_MODULE_NAME("oslinuxtbl")

#अगर_अघोषित PATH_MAX
#घोषणा PATH_MAX 256
#पूर्ण_अगर
/* List of inक्रमmation about obtained ACPI tables */
प्रकार काष्ठा osl_table_info अणु
	काष्ठा osl_table_info *next;
	u32 instance;
	अक्षर signature[ACPI_NAMESEG_SIZE];

पूर्ण osl_table_info;

/* Local prototypes */

अटल acpi_status osl_table_initialize(व्योम);

अटल acpi_status
osl_table_name_from_file(अक्षर *filename, अक्षर *signature, u32 *instance);

अटल acpi_status osl_add_table_to_list(अक्षर *signature, u32 instance);

अटल acpi_status
osl_पढ़ो_table_from_file(अक्षर *filename,
			 acpi_size file_offset,
			 काष्ठा acpi_table_header **table);

अटल acpi_status
osl_map_table(acpi_size address,
	      अक्षर *signature, काष्ठा acpi_table_header **table);

अटल व्योम osl_unmap_table(काष्ठा acpi_table_header *table);

अटल acpi_physical_address
osl_find_rsdp_via_efi_by_keyword(खाता * file, स्थिर अक्षर *keyword);

अटल acpi_physical_address osl_find_rsdp_via_efi(व्योम);

अटल acpi_status osl_load_rsdp(व्योम);

अटल acpi_status osl_list_customized_tables(अक्षर *directory);

अटल acpi_status
osl_get_customized_table(अक्षर *pathname,
			 अक्षर *signature,
			 u32 instance,
			 काष्ठा acpi_table_header **table,
			 acpi_physical_address *address);

अटल acpi_status osl_list_bios_tables(व्योम);

अटल acpi_status
osl_get_bios_table(अक्षर *signature,
		   u32 instance,
		   काष्ठा acpi_table_header **table,
		   acpi_physical_address *address);

अटल acpi_status osl_get_last_status(acpi_status शेष_status);

/* File locations */

#घोषणा DYNAMIC_TABLE_सूची   "/sys/firmware/acpi/tables/dynamic"
#घोषणा STATIC_TABLE_सूची    "/sys/firmware/acpi/tables"
#घोषणा EFI_SYSTAB          "/sys/firmware/efi/systab"

/* Should we get dynamically loaded SSDTs from DYNAMIC_TABLE_सूची? */

u8 gbl_dump_dynamic_tables = TRUE;

/* Initialization flags */

u8 gbl_table_list_initialized = FALSE;

/* Local copies of मुख्य ACPI tables */

काष्ठा acpi_table_rsdp gbl_rsdp;
काष्ठा acpi_table_fadt *gbl_fadt = शून्य;
काष्ठा acpi_table_rsdt *gbl_rsdt = शून्य;
काष्ठा acpi_table_xsdt *gbl_xsdt = शून्य;

/* Table addresses */

acpi_physical_address gbl_fadt_address = 0;
acpi_physical_address gbl_rsdp_address = 0;

/* Revision of RSD PTR */

u8 gbl_revision = 0;

काष्ठा osl_table_info *gbl_table_list_head = शून्य;
u32 gbl_table_count = 0;

/******************************************************************************
 *
 * FUNCTION:    osl_get_last_status
 *
 * PARAMETERS:  शेष_status  - Default error status to वापस
 *
 * RETURN:      Status; Converted from त्रुटि_सं.
 *
 * DESCRIPTION: Get last त्रुटि_सं and convert it to acpi_status.
 *
 *****************************************************************************/

अटल acpi_status osl_get_last_status(acpi_status शेष_status)
अणु

	चयन (त्रुटि_सं) अणु
	हाल EACCES:
	हाल EPERM:

		वापस (AE_ACCESS);

	हाल ENOENT:

		वापस (AE_NOT_FOUND);

	हाल ENOMEM:

		वापस (AE_NO_MEMORY);

	शेष:

		वापस (शेष_status);
	पूर्ण
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_os_get_table_by_address
 *
 * PARAMETERS:  address         - Physical address of the ACPI table
 *              table           - Where a poपूर्णांकer to the table is वापसed
 *
 * RETURN:      Status; Table buffer is वापसed अगर AE_OK.
 *              AE_NOT_FOUND: A valid table was not found at the address
 *
 * DESCRIPTION: Get an ACPI table via a physical memory address.
 *
 *****************************************************************************/

acpi_status
acpi_os_get_table_by_address(acpi_physical_address address,
			     काष्ठा acpi_table_header **table)
अणु
	u32 table_length;
	काष्ठा acpi_table_header *mapped_table;
	काष्ठा acpi_table_header *local_table = शून्य;
	acpi_status status = AE_OK;

	/* Get मुख्य ACPI tables from memory on first invocation of this function */

	status = osl_table_initialize();
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	/* Map the table and validate it */

	status = osl_map_table(address, शून्य, &mapped_table);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	/* Copy table to local buffer and वापस it */

	table_length = ap_get_table_length(mapped_table);
	अगर (table_length == 0) अणु
		status = AE_BAD_HEADER;
		जाओ निकास;
	पूर्ण

	local_table = सुस्मृति(1, table_length);
	अगर (!local_table) अणु
		status = AE_NO_MEMORY;
		जाओ निकास;
	पूर्ण

	स_नकल(local_table, mapped_table, table_length);

निकास:
	osl_unmap_table(mapped_table);
	*table = local_table;
	वापस (status);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_os_get_table_by_name
 *
 * PARAMETERS:  signature       - ACPI Signature क्रम desired table. Must be
 *                                a null terminated 4-अक्षरacter string.
 *              instance        - Multiple table support क्रम SSDT/UEFI (0...n)
 *                                Must be 0 क्रम other tables.
 *              table           - Where a poपूर्णांकer to the table is वापसed
 *              address         - Where the table physical address is वापसed
 *
 * RETURN:      Status; Table buffer and physical address वापसed अगर AE_OK.
 *              AE_LIMIT: Instance is beyond valid limit
 *              AE_NOT_FOUND: A table with the signature was not found
 *
 * NOTE:        Assumes the input signature is upperहाल.
 *
 *****************************************************************************/

acpi_status
acpi_os_get_table_by_name(अक्षर *signature,
			  u32 instance,
			  काष्ठा acpi_table_header **table,
			  acpi_physical_address *address)
अणु
	acpi_status status;

	/* Get मुख्य ACPI tables from memory on first invocation of this function */

	status = osl_table_initialize();
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	/* Not a मुख्य ACPI table, attempt to extract it from the RSDT/XSDT */

	अगर (!gbl_dump_customized_tables) अणु

		/* Attempt to get the table from the memory */

		status =
		    osl_get_bios_table(signature, instance, table, address);
	पूर्ण अन्यथा अणु
		/* Attempt to get the table from the अटल directory */

		status = osl_get_customized_table(STATIC_TABLE_सूची, signature,
						  instance, table, address);
	पूर्ण

	अगर (ACPI_FAILURE(status) && status == AE_LIMIT) अणु
		अगर (gbl_dump_dynamic_tables) अणु

			/* Attempt to get a dynamic table */

			status =
			    osl_get_customized_table(DYNAMIC_TABLE_सूची,
						     signature, instance, table,
						     address);
		पूर्ण
	पूर्ण

	वापस (status);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    osl_add_table_to_list
 *
 * PARAMETERS:  signature       - Table signature
 *              instance        - Table instance
 *
 * RETURN:      Status; Successfully added अगर AE_OK.
 *              AE_NO_MEMORY: Memory allocation error
 *
 * DESCRIPTION: Insert a table काष्ठाure पूर्णांकo OSL table list.
 *
 *****************************************************************************/

अटल acpi_status osl_add_table_to_list(अक्षर *signature, u32 instance)
अणु
	काष्ठा osl_table_info *new_info;
	काष्ठा osl_table_info *next;
	u32 next_instance = 0;
	u8 found = FALSE;

	new_info = सुस्मृति(1, माप(काष्ठा osl_table_info));
	अगर (!new_info) अणु
		वापस (AE_NO_MEMORY);
	पूर्ण

	ACPI_COPY_NAMESEG(new_info->signature, signature);

	अगर (!gbl_table_list_head) अणु
		gbl_table_list_head = new_info;
	पूर्ण अन्यथा अणु
		next = gbl_table_list_head;
		जबतक (1) अणु
			अगर (ACPI_COMPARE_NAMESEG(next->signature, signature)) अणु
				अगर (next->instance == instance) अणु
					found = TRUE;
				पूर्ण
				अगर (next->instance >= next_instance) अणु
					next_instance = next->instance + 1;
				पूर्ण
			पूर्ण

			अगर (!next->next) अणु
				अवरोध;
			पूर्ण
			next = next->next;
		पूर्ण
		next->next = new_info;
	पूर्ण

	अगर (found) अणु
		अगर (instance) अणु
			ख_लिखो(मानक_त्रुटि,
				"%4.4s: Warning unmatched table instance %d, expected %d\n",
				signature, instance, next_instance);
		पूर्ण
		instance = next_instance;
	पूर्ण

	new_info->instance = instance;
	gbl_table_count++;

	वापस (AE_OK);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_os_get_table_by_index
 *
 * PARAMETERS:  index           - Which table to get
 *              table           - Where a poपूर्णांकer to the table is वापसed
 *              instance        - Where a poपूर्णांकer to the table instance no. is
 *                                वापसed
 *              address         - Where the table physical address is वापसed
 *
 * RETURN:      Status; Table buffer and physical address वापसed अगर AE_OK.
 *              AE_LIMIT: Index is beyond valid limit
 *
 * DESCRIPTION: Get an ACPI table via an index value (0 through n). Returns
 *              AE_LIMIT when an invalid index is reached. Index is not
 *              necessarily an index पूर्णांकo the RSDT/XSDT.
 *
 *****************************************************************************/

acpi_status
acpi_os_get_table_by_index(u32 index,
			   काष्ठा acpi_table_header **table,
			   u32 *instance, acpi_physical_address *address)
अणु
	काष्ठा osl_table_info *info;
	acpi_status status;
	u32 i;

	/* Get मुख्य ACPI tables from memory on first invocation of this function */

	status = osl_table_initialize();
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	/* Validate Index */

	अगर (index >= gbl_table_count) अणु
		वापस (AE_LIMIT);
	पूर्ण

	/* Poपूर्णांक to the table list entry specअगरied by the Index argument */

	info = gbl_table_list_head;
	क्रम (i = 0; i < index; i++) अणु
		info = info->next;
	पूर्ण

	/* Now we can just get the table via the signature */

	status = acpi_os_get_table_by_name(info->signature, info->instance,
					   table, address);

	अगर (ACPI_SUCCESS(status)) अणु
		*instance = info->instance;
	पूर्ण
	वापस (status);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    osl_find_rsdp_via_efi_by_keyword
 *
 * PARAMETERS:  keyword         - Character string indicating ACPI GUID version
 *                                in the EFI table
 *
 * RETURN:      RSDP address अगर found
 *
 * DESCRIPTION: Find RSDP address via EFI using keyword indicating the ACPI
 *              GUID version.
 *
 *****************************************************************************/

अटल acpi_physical_address
osl_find_rsdp_via_efi_by_keyword(खाता * file, स्थिर अक्षर *keyword)
अणु
	अक्षर buffer[80];
	अचिन्हित दीर्घ दीर्घ address = 0;
	अक्षर क्रमmat[32];

	snम_लिखो(क्रमmat, 32, "%s=%s", keyword, "%llx");
	ख_जाओ(file, 0, शुरू_से);
	जबतक (ख_माला_लो(buffer, 80, file)) अणु
		अगर (माला_पूछो(buffer, क्रमmat, &address) == 1) अणु
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ((acpi_physical_address)(address));
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    osl_find_rsdp_via_efi
 *
 * PARAMETERS:  None
 *
 * RETURN:      RSDP address अगर found
 *
 * DESCRIPTION: Find RSDP address via EFI.
 *
 *****************************************************************************/

अटल acpi_physical_address osl_find_rsdp_via_efi(व्योम)
अणु
	खाता *file;
	acpi_physical_address address = 0;

	file = ख_खोलो(EFI_SYSTAB, "r");
	अगर (file) अणु
		address = osl_find_rsdp_via_efi_by_keyword(file, "ACPI20");
		अगर (!address) अणु
			address =
			    osl_find_rsdp_via_efi_by_keyword(file, "ACPI");
		पूर्ण
		ख_बंद(file);
	पूर्ण

	वापस (address);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    osl_load_rsdp
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Scan and load RSDP.
 *
 *****************************************************************************/

अटल acpi_status osl_load_rsdp(व्योम)
अणु
	काष्ठा acpi_table_header *mapped_table;
	u8 *rsdp_address;
	acpi_physical_address rsdp_base;
	acpi_size rsdp_size;

	/* Get RSDP from memory */

	rsdp_size = माप(काष्ठा acpi_table_rsdp);
	अगर (gbl_rsdp_base) अणु
		rsdp_base = gbl_rsdp_base;
	पूर्ण अन्यथा अणु
		rsdp_base = osl_find_rsdp_via_efi();
	पूर्ण

	अगर (!rsdp_base) अणु
		rsdp_base = ACPI_HI_RSDP_WINDOW_BASE;
		rsdp_size = ACPI_HI_RSDP_WINDOW_SIZE;
	पूर्ण

	rsdp_address = acpi_os_map_memory(rsdp_base, rsdp_size);
	अगर (!rsdp_address) अणु
		वापस (osl_get_last_status(AE_BAD_ADDRESS));
	पूर्ण

	/* Search low memory क्रम the RSDP */

	mapped_table = ACPI_CAST_PTR(काष्ठा acpi_table_header,
				     acpi_tb_scan_memory_क्रम_rsdp(rsdp_address,
								  rsdp_size));
	अगर (!mapped_table) अणु
		acpi_os_unmap_memory(rsdp_address, rsdp_size);
		वापस (AE_NOT_FOUND);
	पूर्ण

	gbl_rsdp_address =
	    rsdp_base + (ACPI_CAST8(mapped_table) - rsdp_address);

	स_नकल(&gbl_rsdp, mapped_table, माप(काष्ठा acpi_table_rsdp));
	acpi_os_unmap_memory(rsdp_address, rsdp_size);

	वापस (AE_OK);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    osl_can_use_xsdt
 *
 * PARAMETERS:  None
 *
 * RETURN:      TRUE अगर XSDT is allowed to be used.
 *
 * DESCRIPTION: This function collects logic that can be used to determine अगर
 *              XSDT should be used instead of RSDT.
 *
 *****************************************************************************/

अटल u8 osl_can_use_xsdt(व्योम)
अणु
	अगर (gbl_revision && !acpi_gbl_करो_not_use_xsdt) अणु
		वापस (TRUE);
	पूर्ण अन्यथा अणु
		वापस (FALSE);
	पूर्ण
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    osl_table_initialize
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Initialize ACPI table data. Get and store मुख्य ACPI tables to
 *              local variables. Main ACPI tables include RSDT, FADT, RSDT,
 *              and/or XSDT.
 *
 *****************************************************************************/

अटल acpi_status osl_table_initialize(व्योम)
अणु
	acpi_status status;
	acpi_physical_address address;

	अगर (gbl_table_list_initialized) अणु
		वापस (AE_OK);
	पूर्ण

	अगर (!gbl_dump_customized_tables) अणु

		/* Get RSDP from memory */

		status = osl_load_rsdp();
		अगर (ACPI_FAILURE(status)) अणु
			वापस (status);
		पूर्ण

		/* Get XSDT from memory */

		अगर (gbl_rsdp.revision && !gbl_करो_not_dump_xsdt) अणु
			अगर (gbl_xsdt) अणु
				मुक्त(gbl_xsdt);
				gbl_xsdt = शून्य;
			पूर्ण

			gbl_revision = 2;
			status = osl_get_bios_table(ACPI_SIG_XSDT, 0,
						    ACPI_CAST_PTR(काष्ठा
								  acpi_table_header
								  *, &gbl_xsdt),
						    &address);
			अगर (ACPI_FAILURE(status)) अणु
				वापस (status);
			पूर्ण
		पूर्ण

		/* Get RSDT from memory */

		अगर (gbl_rsdp.rsdt_physical_address) अणु
			अगर (gbl_rsdt) अणु
				मुक्त(gbl_rsdt);
				gbl_rsdt = शून्य;
			पूर्ण

			status = osl_get_bios_table(ACPI_SIG_RSDT, 0,
						    ACPI_CAST_PTR(काष्ठा
								  acpi_table_header
								  *, &gbl_rsdt),
						    &address);
			अगर (ACPI_FAILURE(status)) अणु
				वापस (status);
			पूर्ण
		पूर्ण

		/* Get FADT from memory */

		अगर (gbl_fadt) अणु
			मुक्त(gbl_fadt);
			gbl_fadt = शून्य;
		पूर्ण

		status = osl_get_bios_table(ACPI_SIG_FADT, 0,
					    ACPI_CAST_PTR(काष्ठा
							  acpi_table_header *,
							  &gbl_fadt),
					    &gbl_fadt_address);
		अगर (ACPI_FAILURE(status)) अणु
			वापस (status);
		पूर्ण

		/* Add mandatory tables to global table list first */

		status = osl_add_table_to_list(ACPI_RSDP_NAME, 0);
		अगर (ACPI_FAILURE(status)) अणु
			वापस (status);
		पूर्ण

		status = osl_add_table_to_list(ACPI_SIG_RSDT, 0);
		अगर (ACPI_FAILURE(status)) अणु
			वापस (status);
		पूर्ण

		अगर (gbl_revision == 2) अणु
			status = osl_add_table_to_list(ACPI_SIG_XSDT, 0);
			अगर (ACPI_FAILURE(status)) अणु
				वापस (status);
			पूर्ण
		पूर्ण

		status = osl_add_table_to_list(ACPI_SIG_DSDT, 0);
		अगर (ACPI_FAILURE(status)) अणु
			वापस (status);
		पूर्ण

		status = osl_add_table_to_list(ACPI_SIG_FACS, 0);
		अगर (ACPI_FAILURE(status)) अणु
			वापस (status);
		पूर्ण

		/* Add all tables found in the memory */

		status = osl_list_bios_tables();
		अगर (ACPI_FAILURE(status)) अणु
			वापस (status);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Add all tables found in the अटल directory */

		status = osl_list_customized_tables(STATIC_TABLE_सूची);
		अगर (ACPI_FAILURE(status)) अणु
			वापस (status);
		पूर्ण
	पूर्ण

	अगर (gbl_dump_dynamic_tables) अणु

		/* Add all dynamically loaded tables in the dynamic directory */

		status = osl_list_customized_tables(DYNAMIC_TABLE_सूची);
		अगर (ACPI_FAILURE(status)) अणु
			वापस (status);
		पूर्ण
	पूर्ण

	gbl_table_list_initialized = TRUE;
	वापस (AE_OK);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    osl_list_bios_tables
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status; Table list is initialized अगर AE_OK.
 *
 * DESCRIPTION: Add ACPI tables to the table list from memory.
 *
 * NOTE:        This works on Linux as table customization करोes not modअगरy the
 *              addresses stored in RSDP/RSDT/XSDT/FADT.
 *
 *****************************************************************************/

अटल acpi_status osl_list_bios_tables(व्योम)
अणु
	काष्ठा acpi_table_header *mapped_table = शून्य;
	u8 *table_data;
	u8 number_of_tables;
	u8 item_size;
	acpi_physical_address table_address = 0;
	acpi_status status = AE_OK;
	u32 i;

	अगर (osl_can_use_xsdt()) अणु
		item_size = माप(u64);
		table_data =
		    ACPI_CAST8(gbl_xsdt) + माप(काष्ठा acpi_table_header);
		number_of_tables =
		    (u8)((gbl_xsdt->header.length -
			  माप(काष्ठा acpi_table_header))
			 / item_size);
	पूर्ण अन्यथा अणु		/* Use RSDT अगर XSDT is not available */

		item_size = माप(u32);
		table_data =
		    ACPI_CAST8(gbl_rsdt) + माप(काष्ठा acpi_table_header);
		number_of_tables =
		    (u8)((gbl_rsdt->header.length -
			  माप(काष्ठा acpi_table_header))
			 / item_size);
	पूर्ण

	/* Search RSDT/XSDT क्रम the requested table */

	क्रम (i = 0; i < number_of_tables; ++i, table_data += item_size) अणु
		अगर (osl_can_use_xsdt()) अणु
			table_address =
			    (acpi_physical_address)(*ACPI_CAST64(table_data));
		पूर्ण अन्यथा अणु
			table_address =
			    (acpi_physical_address)(*ACPI_CAST32(table_data));
		पूर्ण

		/* Skip शून्य entries in RSDT/XSDT */

		अगर (table_address == 0) अणु
			जारी;
		पूर्ण

		status = osl_map_table(table_address, शून्य, &mapped_table);
		अगर (ACPI_FAILURE(status)) अणु
			वापस (status);
		पूर्ण

		osl_add_table_to_list(mapped_table->signature, 0);
		osl_unmap_table(mapped_table);
	पूर्ण

	वापस (AE_OK);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    osl_get_bios_table
 *
 * PARAMETERS:  signature       - ACPI Signature क्रम common table. Must be
 *                                a null terminated 4-अक्षरacter string.
 *              instance        - Multiple table support क्रम SSDT/UEFI (0...n)
 *                                Must be 0 क्रम other tables.
 *              table           - Where a poपूर्णांकer to the table is वापसed
 *              address         - Where the table physical address is वापसed
 *
 * RETURN:      Status; Table buffer and physical address वापसed अगर AE_OK.
 *              AE_LIMIT: Instance is beyond valid limit
 *              AE_NOT_FOUND: A table with the signature was not found
 *
 * DESCRIPTION: Get a BIOS provided ACPI table
 *
 * NOTE:        Assumes the input signature is upperहाल.
 *
 *****************************************************************************/

अटल acpi_status
osl_get_bios_table(अक्षर *signature,
		   u32 instance,
		   काष्ठा acpi_table_header **table,
		   acpi_physical_address *address)
अणु
	काष्ठा acpi_table_header *local_table = शून्य;
	काष्ठा acpi_table_header *mapped_table = शून्य;
	u8 *table_data;
	u8 number_of_tables;
	u8 item_size;
	u32 current_instance = 0;
	acpi_physical_address table_address;
	acpi_physical_address first_table_address = 0;
	u32 table_length = 0;
	acpi_status status = AE_OK;
	u32 i;

	/* Handle special tables whose addresses are not in RSDT/XSDT */

	अगर (ACPI_COMPARE_NAMESEG(signature, ACPI_RSDP_NAME) ||
	    ACPI_COMPARE_NAMESEG(signature, ACPI_SIG_RSDT) ||
	    ACPI_COMPARE_NAMESEG(signature, ACPI_SIG_XSDT) ||
	    ACPI_COMPARE_NAMESEG(signature, ACPI_SIG_DSDT) ||
	    ACPI_COMPARE_NAMESEG(signature, ACPI_SIG_FACS)) अणु

find_next_instance:

		table_address = 0;

		/*
		 * Get the appropriate address, either 32-bit or 64-bit. Be very
		 * careful about the FADT length and validate table addresses.
		 * Note: The 64-bit addresses have priority.
		 */
		अगर (ACPI_COMPARE_NAMESEG(signature, ACPI_SIG_DSDT)) अणु
			अगर (current_instance < 2) अणु
				अगर ((gbl_fadt->header.length >=
				     MIN_FADT_FOR_XDSDT) && gbl_fadt->Xdsdt
				    && current_instance == 0) अणु
					table_address =
					    (acpi_physical_address)gbl_fadt->
					    Xdsdt;
				पूर्ण अन्यथा
				    अगर ((gbl_fadt->header.length >=
					 MIN_FADT_FOR_DSDT)
					&& gbl_fadt->dsdt !=
					first_table_address) अणु
					table_address =
					    (acpi_physical_address)gbl_fadt->
					    dsdt;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अगर (ACPI_COMPARE_NAMESEG(signature, ACPI_SIG_FACS)) अणु
			अगर (current_instance < 2) अणु
				अगर ((gbl_fadt->header.length >=
				     MIN_FADT_FOR_XFACS) && gbl_fadt->Xfacs
				    && current_instance == 0) अणु
					table_address =
					    (acpi_physical_address)gbl_fadt->
					    Xfacs;
				पूर्ण अन्यथा
				    अगर ((gbl_fadt->header.length >=
					 MIN_FADT_FOR_FACS)
					&& gbl_fadt->facs !=
					first_table_address) अणु
					table_address =
					    (acpi_physical_address)gbl_fadt->
					    facs;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अगर (ACPI_COMPARE_NAMESEG(signature, ACPI_SIG_XSDT)) अणु
			अगर (!gbl_revision) अणु
				वापस (AE_BAD_SIGNATURE);
			पूर्ण
			अगर (current_instance == 0) अणु
				table_address =
				    (acpi_physical_address)gbl_rsdp.
				    xsdt_physical_address;
			पूर्ण
		पूर्ण अन्यथा अगर (ACPI_COMPARE_NAMESEG(signature, ACPI_SIG_RSDT)) अणु
			अगर (current_instance == 0) अणु
				table_address =
				    (acpi_physical_address)gbl_rsdp.
				    rsdt_physical_address;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (current_instance == 0) अणु
				table_address =
				    (acpi_physical_address)gbl_rsdp_address;
				signature = ACPI_SIG_RSDP;
			पूर्ण
		पूर्ण

		अगर (table_address == 0) अणु
			जाओ निकास_find_table;
		पूर्ण

		/* Now we can get the requested special table */

		status = osl_map_table(table_address, signature, &mapped_table);
		अगर (ACPI_FAILURE(status)) अणु
			वापस (status);
		पूर्ण

		table_length = ap_get_table_length(mapped_table);
		अगर (first_table_address == 0) अणु
			first_table_address = table_address;
		पूर्ण

		/* Match table instance */

		अगर (current_instance != instance) अणु
			osl_unmap_table(mapped_table);
			mapped_table = शून्य;
			current_instance++;
			जाओ find_next_instance;
		पूर्ण
	पूर्ण अन्यथा अणु		/* Case क्रम a normal ACPI table */

		अगर (osl_can_use_xsdt()) अणु
			item_size = माप(u64);
			table_data =
			    ACPI_CAST8(gbl_xsdt) +
			    माप(काष्ठा acpi_table_header);
			number_of_tables =
			    (u8)((gbl_xsdt->header.length -
				  माप(काष्ठा acpi_table_header))
				 / item_size);
		पूर्ण अन्यथा अणु	/* Use RSDT अगर XSDT is not available */

			item_size = माप(u32);
			table_data =
			    ACPI_CAST8(gbl_rsdt) +
			    माप(काष्ठा acpi_table_header);
			number_of_tables =
			    (u8)((gbl_rsdt->header.length -
				  माप(काष्ठा acpi_table_header))
				 / item_size);
		पूर्ण

		/* Search RSDT/XSDT क्रम the requested table */

		क्रम (i = 0; i < number_of_tables; ++i, table_data += item_size) अणु
			अगर (osl_can_use_xsdt()) अणु
				table_address =
				    (acpi_physical_address)(*ACPI_CAST64
							    (table_data));
			पूर्ण अन्यथा अणु
				table_address =
				    (acpi_physical_address)(*ACPI_CAST32
							    (table_data));
			पूर्ण

			/* Skip शून्य entries in RSDT/XSDT */

			अगर (table_address == 0) अणु
				जारी;
			पूर्ण

			status =
			    osl_map_table(table_address, शून्य, &mapped_table);
			अगर (ACPI_FAILURE(status)) अणु
				वापस (status);
			पूर्ण
			table_length = mapped_table->length;

			/* Does this table match the requested signature? */

			अगर (!ACPI_COMPARE_NAMESEG
			    (mapped_table->signature, signature)) अणु
				osl_unmap_table(mapped_table);
				mapped_table = शून्य;
				जारी;
			पूर्ण

			/* Match table instance (क्रम SSDT/UEFI tables) */

			अगर (current_instance != instance) अणु
				osl_unmap_table(mapped_table);
				mapped_table = शून्य;
				current_instance++;
				जारी;
			पूर्ण

			अवरोध;
		पूर्ण
	पूर्ण

निकास_find_table:

	अगर (!mapped_table) अणु
		वापस (AE_LIMIT);
	पूर्ण

	अगर (table_length == 0) अणु
		status = AE_BAD_HEADER;
		जाओ निकास;
	पूर्ण

	/* Copy table to local buffer and वापस it */

	local_table = सुस्मृति(1, table_length);
	अगर (!local_table) अणु
		status = AE_NO_MEMORY;
		जाओ निकास;
	पूर्ण

	स_नकल(local_table, mapped_table, table_length);
	*address = table_address;
	*table = local_table;

निकास:
	osl_unmap_table(mapped_table);
	वापस (status);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    osl_list_customized_tables
 *
 * PARAMETERS:  directory           - Directory that contains the tables
 *
 * RETURN:      Status; Table list is initialized अगर AE_OK.
 *
 * DESCRIPTION: Add ACPI tables to the table list from a directory.
 *
 *****************************************************************************/

अटल acpi_status osl_list_customized_tables(अक्षर *directory)
अणु
	व्योम *table_dir;
	u32 instance;
	अक्षर temp_name[ACPI_NAMESEG_SIZE];
	अक्षर *filename;
	acpi_status status = AE_OK;

	/* Open the requested directory */

	table_dir = acpi_os_खोलो_directory(directory, "*", REQUEST_खाता_ONLY);
	अगर (!table_dir) अणु
		वापस (osl_get_last_status(AE_NOT_FOUND));
	पूर्ण

	/* Examine all entries in this directory */

	जबतक ((filename = acpi_os_get_next_filename(table_dir))) अणु

		/* Extract table name and instance number */

		status =
		    osl_table_name_from_file(filename, temp_name, &instance);

		/* Ignore meaningless files */

		अगर (ACPI_FAILURE(status)) अणु
			जारी;
		पूर्ण

		/* Add new info node to global table list */

		status = osl_add_table_to_list(temp_name, instance);
		अगर (ACPI_FAILURE(status)) अणु
			अवरोध;
		पूर्ण
	पूर्ण

	acpi_os_बंद_directory(table_dir);
	वापस (status);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    osl_map_table
 *
 * PARAMETERS:  address             - Address of the table in memory
 *              signature           - Optional ACPI Signature क्रम desired table.
 *                                    Null terminated 4-अक्षरacter string.
 *              table               - Where a poपूर्णांकer to the mapped table is
 *                                    वापसed
 *
 * RETURN:      Status; Mapped table is वापसed अगर AE_OK.
 *              AE_NOT_FOUND: A valid table was not found at the address
 *
 * DESCRIPTION: Map entire ACPI table पूर्णांकo caller's address space.
 *
 *****************************************************************************/

अटल acpi_status
osl_map_table(acpi_size address,
	      अक्षर *signature, काष्ठा acpi_table_header **table)
अणु
	काष्ठा acpi_table_header *mapped_table;
	u32 length;

	अगर (!address) अणु
		वापस (AE_BAD_ADDRESS);
	पूर्ण

	/*
	 * Map the header so we can get the table length.
	 * Use माप (काष्ठा acpi_table_header) as:
	 * 1. it is bigger than 24 to include RSDP->Length
	 * 2. it is smaller than माप (काष्ठा acpi_table_rsdp)
	 */
	mapped_table =
	    acpi_os_map_memory(address, माप(काष्ठा acpi_table_header));
	अगर (!mapped_table) अणु
		ख_लिखो(मानक_त्रुटि, "Could not map table header at 0x%8.8X%8.8X\n",
			ACPI_FORMAT_UINT64(address));
		वापस (osl_get_last_status(AE_BAD_ADDRESS));
	पूर्ण

	/* If specअगरied, signature must match */

	अगर (signature) अणु
		अगर (ACPI_VALIDATE_RSDP_SIG(signature)) अणु
			अगर (!ACPI_VALIDATE_RSDP_SIG(mapped_table->signature)) अणु
				acpi_os_unmap_memory(mapped_table,
						     माप(काष्ठा
							    acpi_table_header));
				वापस (AE_BAD_SIGNATURE);
			पूर्ण
		पूर्ण अन्यथा
		    अगर (!ACPI_COMPARE_NAMESEG
			(signature, mapped_table->signature)) अणु
			acpi_os_unmap_memory(mapped_table,
					     माप(काष्ठा acpi_table_header));
			वापस (AE_BAD_SIGNATURE);
		पूर्ण
	पूर्ण

	/* Map the entire table */

	length = ap_get_table_length(mapped_table);
	acpi_os_unmap_memory(mapped_table, माप(काष्ठा acpi_table_header));
	अगर (length == 0) अणु
		वापस (AE_BAD_HEADER);
	पूर्ण

	mapped_table = acpi_os_map_memory(address, length);
	अगर (!mapped_table) अणु
		ख_लिखो(मानक_त्रुटि,
			"Could not map table at 0x%8.8X%8.8X length %8.8X\n",
			ACPI_FORMAT_UINT64(address), length);
		वापस (osl_get_last_status(AE_INVALID_TABLE_LENGTH));
	पूर्ण

	(व्योम)ap_is_valid_checksum(mapped_table);

	*table = mapped_table;
	वापस (AE_OK);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    osl_unmap_table
 *
 * PARAMETERS:  table               - A poपूर्णांकer to the mapped table
 *
 * RETURN:      None
 *
 * DESCRIPTION: Unmap entire ACPI table.
 *
 *****************************************************************************/

अटल व्योम osl_unmap_table(काष्ठा acpi_table_header *table)
अणु
	अगर (table) अणु
		acpi_os_unmap_memory(table, ap_get_table_length(table));
	पूर्ण
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    osl_table_name_from_file
 *
 * PARAMETERS:  filename            - File that contains the desired table
 *              signature           - Poपूर्णांकer to 4-अक्षरacter buffer to store
 *                                    extracted table signature.
 *              instance            - Poपूर्णांकer to पूर्णांकeger to store extracted
 *                                    table instance number.
 *
 * RETURN:      Status; Table name is extracted अगर AE_OK.
 *
 * DESCRIPTION: Extract table signature and instance number from a table file
 *              name.
 *
 *****************************************************************************/

अटल acpi_status
osl_table_name_from_file(अक्षर *filename, अक्षर *signature, u32 *instance)
अणु

	/* Ignore meaningless files */

	अगर (म_माप(filename) < ACPI_NAMESEG_SIZE) अणु
		वापस (AE_BAD_SIGNATURE);
	पूर्ण

	/* Extract instance number */

	अगर (है_अंक((पूर्णांक)filename[ACPI_NAMESEG_SIZE])) अणु
		माला_पूछो(&filename[ACPI_NAMESEG_SIZE], "%u", instance);
	पूर्ण अन्यथा अगर (म_माप(filename) != ACPI_NAMESEG_SIZE) अणु
		वापस (AE_BAD_SIGNATURE);
	पूर्ण अन्यथा अणु
		*instance = 0;
	पूर्ण

	/* Extract signature */

	ACPI_COPY_NAMESEG(signature, filename);
	वापस (AE_OK);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    osl_पढ़ो_table_from_file
 *
 * PARAMETERS:  filename            - File that contains the desired table
 *              file_offset         - Offset of the table in file
 *              table               - Where a poपूर्णांकer to the table is वापसed
 *
 * RETURN:      Status; Table buffer is वापसed अगर AE_OK.
 *
 * DESCRIPTION: Read a ACPI table from a file.
 *
 *****************************************************************************/

अटल acpi_status
osl_पढ़ो_table_from_file(अक्षर *filename,
			 acpi_size file_offset,
			 काष्ठा acpi_table_header **table)
अणु
	खाता *table_file;
	काष्ठा acpi_table_header header;
	काष्ठा acpi_table_header *local_table = शून्य;
	u32 table_length;
	s32 count;
	acpi_status status = AE_OK;

	/* Open the file */

	table_file = ख_खोलो(filename, "rb");
	अगर (table_file == शून्य) अणु
		ख_लिखो(मानक_त्रुटि, "Could not open table file: %s\n", filename);
		वापस (osl_get_last_status(AE_NOT_FOUND));
	पूर्ण

	ख_जाओ(table_file, file_offset, शुरू_से);

	/* Read the Table header to get the table length */

	count = ख_पढ़ो(&header, 1, माप(काष्ठा acpi_table_header), table_file);
	अगर (count != माप(काष्ठा acpi_table_header)) अणु
		ख_लिखो(मानक_त्रुटि, "Could not read table header: %s\n", filename);
		status = AE_BAD_HEADER;
		जाओ निकास;
	पूर्ण

#अगर_घोषित ACPI_OBSOLETE_FUNCTIONS

	/* If signature is specअगरied, it must match the table */

	अगर (signature) अणु
		अगर (ACPI_VALIDATE_RSDP_SIG(signature)) अणु
			अगर (!ACPI_VALIDATE_RSDP_SIG(header.signature)) अणु
				ख_लिखो(मानक_त्रुटि,
					"Incorrect RSDP signature: found %8.8s\n",
					header.signature);
				status = AE_BAD_SIGNATURE;
				जाओ निकास;
			पूर्ण
		पूर्ण अन्यथा अगर (!ACPI_COMPARE_NAMESEG(signature, header.signature)) अणु
			ख_लिखो(मानक_त्रुटि,
				"Incorrect signature: Expecting %4.4s, found %4.4s\n",
				signature, header.signature);
			status = AE_BAD_SIGNATURE;
			जाओ निकास;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	table_length = ap_get_table_length(&header);
	अगर (table_length == 0) अणु
		status = AE_BAD_HEADER;
		जाओ निकास;
	पूर्ण

	/* Read the entire table पूर्णांकo a local buffer */

	local_table = सुस्मृति(1, table_length);
	अगर (!local_table) अणु
		ख_लिखो(मानक_त्रुटि,
			"%4.4s: Could not allocate buffer for table of length %X\n",
			header.signature, table_length);
		status = AE_NO_MEMORY;
		जाओ निकास;
	पूर्ण

	ख_जाओ(table_file, file_offset, शुरू_से);

	count = ख_पढ़ो(local_table, 1, table_length, table_file);
	अगर (count != table_length) अणु
		ख_लिखो(मानक_त्रुटि, "%4.4s: Could not read table content\n",
			header.signature);
		status = AE_INVALID_TABLE_LENGTH;
		जाओ निकास;
	पूर्ण

	/* Validate checksum */

	(व्योम)ap_is_valid_checksum(local_table);

निकास:
	ख_बंद(table_file);
	*table = local_table;
	वापस (status);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    osl_get_customized_table
 *
 * PARAMETERS:  pathname        - Directory to find Linux customized table
 *              signature       - ACPI Signature क्रम desired table. Must be
 *                                a null terminated 4-अक्षरacter string.
 *              instance        - Multiple table support क्रम SSDT/UEFI (0...n)
 *                                Must be 0 क्रम other tables.
 *              table           - Where a poपूर्णांकer to the table is वापसed
 *              address         - Where the table physical address is वापसed
 *
 * RETURN:      Status; Table buffer is वापसed अगर AE_OK.
 *              AE_LIMIT: Instance is beyond valid limit
 *              AE_NOT_FOUND: A table with the signature was not found
 *
 * DESCRIPTION: Get an OS customized table.
 *
 *****************************************************************************/

अटल acpi_status
osl_get_customized_table(अक्षर *pathname,
			 अक्षर *signature,
			 u32 instance,
			 काष्ठा acpi_table_header **table,
			 acpi_physical_address *address)
अणु
	व्योम *table_dir;
	u32 current_instance = 0;
	अक्षर temp_name[ACPI_NAMESEG_SIZE];
	अक्षर table_filename[PATH_MAX];
	अक्षर *filename;
	acpi_status status;

	/* Open the directory क्रम customized tables */

	table_dir = acpi_os_खोलो_directory(pathname, "*", REQUEST_खाता_ONLY);
	अगर (!table_dir) अणु
		वापस (osl_get_last_status(AE_NOT_FOUND));
	पूर्ण

	/* Attempt to find the table in the directory */

	जबतक ((filename = acpi_os_get_next_filename(table_dir))) अणु

		/* Ignore meaningless files */

		अगर (!ACPI_COMPARE_NAMESEG(filename, signature)) अणु
			जारी;
		पूर्ण

		/* Extract table name and instance number */

		status =
		    osl_table_name_from_file(filename, temp_name,
					     &current_instance);

		/* Ignore meaningless files */

		अगर (ACPI_FAILURE(status) || current_instance != instance) अणु
			जारी;
		पूर्ण

		/* Create the table pathname */

		अगर (instance != 0) अणु
			प्र_लिखो(table_filename, "%s/%4.4s%d", pathname,
				temp_name, instance);
		पूर्ण अन्यथा अणु
			प्र_लिखो(table_filename, "%s/%4.4s", pathname,
				temp_name);
		पूर्ण
		अवरोध;
	पूर्ण

	acpi_os_बंद_directory(table_dir);

	अगर (!filename) अणु
		वापस (AE_LIMIT);
	पूर्ण

	/* There is no physical address saved क्रम customized tables, use zero */

	*address = 0;
	status = osl_पढ़ो_table_from_file(table_filename, 0, table);

	वापस (status);
पूर्ण
