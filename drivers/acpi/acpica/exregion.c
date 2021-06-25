<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: exregion - ACPI शेष op_region (address space) handlers
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acinterp.h"

#घोषणा _COMPONENT          ACPI_EXECUTER
ACPI_MODULE_NAME("exregion")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_प्रणाली_memory_space_handler
 *
 * PARAMETERS:  function            - Read or Write operation
 *              address             - Where in the space to पढ़ो or ग_लिखो
 *              bit_width           - Field width in bits (8, 16, or 32)
 *              value               - Poपूर्णांकer to in or out value
 *              handler_context     - Poपूर्णांकer to Handler's context
 *              region_context      - Poपूर्णांकer to context specअगरic to the
 *                                    accessed region
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Handler क्रम the System Memory address space (Op Region)
 *
 ******************************************************************************/
acpi_status
acpi_ex_प्रणाली_memory_space_handler(u32 function,
				    acpi_physical_address address,
				    u32 bit_width,
				    u64 *value,
				    व्योम *handler_context, व्योम *region_context)
अणु
	acpi_status status = AE_OK;
	व्योम *logical_addr_ptr = शून्य;
	काष्ठा acpi_mem_space_context *mem_info = region_context;
	काष्ठा acpi_mem_mapping *mm = mem_info->cur_mm;
	u32 length;
	acpi_size map_length;
	acpi_size page_boundary_map_length;
#अगर_घोषित ACPI_MISALIGNMENT_NOT_SUPPORTED
	u32 reमुख्यder;
#पूर्ण_अगर

	ACPI_FUNCTION_TRACE(ex_प्रणाली_memory_space_handler);

	/* Validate and translate the bit width */

	चयन (bit_width) अणु
	हाल 8:

		length = 1;
		अवरोध;

	हाल 16:

		length = 2;
		अवरोध;

	हाल 32:

		length = 4;
		अवरोध;

	हाल 64:

		length = 8;
		अवरोध;

	शेष:

		ACPI_ERROR((AE_INFO, "Invalid SystemMemory width %u",
			    bit_width));
		वापस_ACPI_STATUS(AE_AML_OPERAND_VALUE);
	पूर्ण

#अगर_घोषित ACPI_MISALIGNMENT_NOT_SUPPORTED
	/*
	 * Hardware करोes not support non-aligned data transfers, we must verअगरy
	 * the request.
	 */
	(व्योम)acpi_ut_लघु_भागide((u64) address, length, शून्य, &reमुख्यder);
	अगर (reमुख्यder != 0) अणु
		वापस_ACPI_STATUS(AE_AML_ALIGNMENT);
	पूर्ण
#पूर्ण_अगर

	/*
	 * Does the request fit पूर्णांकo the cached memory mapping?
	 * Is 1) Address below the current mapping? OR
	 *    2) Address beyond the current mapping?
	 */
	अगर (!mm || (address < mm->physical_address) ||
	    ((u64) address + length > (u64) mm->physical_address + mm->length)) अणु
		/*
		 * The request cannot be resolved by the current memory mapping.
		 *
		 * Look क्रम an existing saved mapping covering the address range
		 * at hand.  If found, save it as the current one and carry out
		 * the access.
		 */
		क्रम (mm = mem_info->first_mm; mm; mm = mm->next_mm) अणु
			अगर (mm == mem_info->cur_mm)
				जारी;

			अगर (address < mm->physical_address)
				जारी;

			अगर ((u64) address + length >
					(u64) mm->physical_address + mm->length)
				जारी;

			mem_info->cur_mm = mm;
			जाओ access;
		पूर्ण

		/* Create a new mappings list entry */
		mm = ACPI_ALLOCATE_ZEROED(माप(*mm));
		अगर (!mm) अणु
			ACPI_ERROR((AE_INFO,
				    "Unable to save memory mapping at 0x%8.8X%8.8X, size %u",
				    ACPI_FORMAT_UINT64(address), length));
			वापस_ACPI_STATUS(AE_NO_MEMORY);
		पूर्ण

		/*
		 * October 2009: Attempt to map from the requested address to the
		 * end of the region. However, we will never map more than one
		 * page, nor will we cross a page boundary.
		 */
		map_length = (acpi_size)
		    ((mem_info->address + mem_info->length) - address);

		/*
		 * If mapping the entire reमुख्यing portion of the region will cross
		 * a page boundary, just map up to the page boundary, करो not cross.
		 * On some प्रणालीs, crossing a page boundary जबतक mapping regions
		 * can cause warnings अगर the pages have dअगरferent attributes
		 * due to resource management.
		 *
		 * This has the added benefit of स्थिरraining a single mapping to
		 * one page, which is similar to the original code that used a 4k
		 * maximum winकरोw.
		 */
		page_boundary_map_length = (acpi_size)
		    (ACPI_ROUND_UP(address, ACPI_DEFAULT_PAGE_SIZE) - address);
		अगर (page_boundary_map_length == 0) अणु
			page_boundary_map_length = ACPI_DEFAULT_PAGE_SIZE;
		पूर्ण

		अगर (map_length > page_boundary_map_length) अणु
			map_length = page_boundary_map_length;
		पूर्ण

		/* Create a new mapping starting at the address given */

		logical_addr_ptr = acpi_os_map_memory(address, map_length);
		अगर (!logical_addr_ptr) अणु
			ACPI_ERROR((AE_INFO,
				    "Could not map memory at 0x%8.8X%8.8X, size %u",
				    ACPI_FORMAT_UINT64(address),
				    (u32)map_length));
			ACPI_FREE(mm);
			वापस_ACPI_STATUS(AE_NO_MEMORY);
		पूर्ण

		/* Save the physical address and mapping size */

		mm->logical_address = logical_addr_ptr;
		mm->physical_address = address;
		mm->length = map_length;

		/*
		 * Add the new entry to the mappigs list and save it as the
		 * current mapping.
		 */
		mm->next_mm = mem_info->first_mm;
		mem_info->first_mm = mm;

		mem_info->cur_mm = mm;
	पूर्ण

access:
	/*
	 * Generate a logical poपूर्णांकer corresponding to the address we want to
	 * access
	 */
	logical_addr_ptr = mm->logical_address +
		((u64) address - (u64) mm->physical_address);

	ACPI_DEBUG_PRINT((ACPI_DB_INFO,
			  "System-Memory (width %u) R/W %u Address=%8.8X%8.8X\n",
			  bit_width, function, ACPI_FORMAT_UINT64(address)));

	/*
	 * Perक्रमm the memory पढ़ो or ग_लिखो
	 *
	 * Note: For machines that करो not support non-aligned transfers, the target
	 * address was checked क्रम alignment above. We करो not attempt to अवरोध the
	 * transfer up पूर्णांकo smaller (byte-size) chunks because the AML specअगरically
	 * asked क्रम a transfer width that the hardware may require.
	 */
	चयन (function) अणु
	हाल ACPI_READ:

		*value = 0;
		चयन (bit_width) अणु
		हाल 8:

			*value = (u64)ACPI_GET8(logical_addr_ptr);
			अवरोध;

		हाल 16:

			*value = (u64)ACPI_GET16(logical_addr_ptr);
			अवरोध;

		हाल 32:

			*value = (u64)ACPI_GET32(logical_addr_ptr);
			अवरोध;

		हाल 64:

			*value = (u64)ACPI_GET64(logical_addr_ptr);
			अवरोध;

		शेष:

			/* bit_width was alपढ़ोy validated */

			अवरोध;
		पूर्ण
		अवरोध;

	हाल ACPI_WRITE:

		चयन (bit_width) अणु
		हाल 8:

			ACPI_SET8(logical_addr_ptr, *value);
			अवरोध;

		हाल 16:

			ACPI_SET16(logical_addr_ptr, *value);
			अवरोध;

		हाल 32:

			ACPI_SET32(logical_addr_ptr, *value);
			अवरोध;

		हाल 64:

			ACPI_SET64(logical_addr_ptr, *value);
			अवरोध;

		शेष:

			/* bit_width was alपढ़ोy validated */

			अवरोध;
		पूर्ण
		अवरोध;

	शेष:

		status = AE_BAD_PARAMETER;
		अवरोध;
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_प्रणाली_io_space_handler
 *
 * PARAMETERS:  function            - Read or Write operation
 *              address             - Where in the space to पढ़ो or ग_लिखो
 *              bit_width           - Field width in bits (8, 16, or 32)
 *              value               - Poपूर्णांकer to in or out value
 *              handler_context     - Poपूर्णांकer to Handler's context
 *              region_context      - Poपूर्णांकer to context specअगरic to the
 *                                    accessed region
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Handler क्रम the System IO address space (Op Region)
 *
 ******************************************************************************/

acpi_status
acpi_ex_प्रणाली_io_space_handler(u32 function,
				acpi_physical_address address,
				u32 bit_width,
				u64 *value,
				व्योम *handler_context, व्योम *region_context)
अणु
	acpi_status status = AE_OK;
	u32 value32;

	ACPI_FUNCTION_TRACE(ex_प्रणाली_io_space_handler);

	ACPI_DEBUG_PRINT((ACPI_DB_INFO,
			  "System-IO (width %u) R/W %u Address=%8.8X%8.8X\n",
			  bit_width, function, ACPI_FORMAT_UINT64(address)));

	/* Decode the function parameter */

	चयन (function) अणु
	हाल ACPI_READ:

		status = acpi_hw_पढ़ो_port((acpi_io_address)address,
					   &value32, bit_width);
		*value = value32;
		अवरोध;

	हाल ACPI_WRITE:

		status = acpi_hw_ग_लिखो_port((acpi_io_address)address,
					    (u32)*value, bit_width);
		अवरोध;

	शेष:

		status = AE_BAD_PARAMETER;
		अवरोध;
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण

#अगर_घोषित ACPI_PCI_CONFIGURED
/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_pci_config_space_handler
 *
 * PARAMETERS:  function            - Read or Write operation
 *              address             - Where in the space to पढ़ो or ग_लिखो
 *              bit_width           - Field width in bits (8, 16, or 32)
 *              value               - Poपूर्णांकer to in or out value
 *              handler_context     - Poपूर्णांकer to Handler's context
 *              region_context      - Poपूर्णांकer to context specअगरic to the
 *                                    accessed region
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Handler क्रम the PCI Config address space (Op Region)
 *
 ******************************************************************************/

acpi_status
acpi_ex_pci_config_space_handler(u32 function,
				 acpi_physical_address address,
				 u32 bit_width,
				 u64 *value,
				 व्योम *handler_context, व्योम *region_context)
अणु
	acpi_status status = AE_OK;
	काष्ठा acpi_pci_id *pci_id;
	u16 pci_रेजिस्टर;

	ACPI_FUNCTION_TRACE(ex_pci_config_space_handler);

	/*
	 *  The arguments to acpi_os(Read|Write)pci_configuration are:
	 *
	 *  pci_segment is the PCI bus segment range 0-31
	 *  pci_bus     is the PCI bus number range 0-255
	 *  pci_device  is the PCI device number range 0-31
	 *  pci_function is the PCI device function number
	 *  pci_रेजिस्टर is the Config space रेजिस्टर range 0-255 bytes
	 *
	 *  value - input value क्रम ग_लिखो, output address क्रम पढ़ो
	 *
	 */
	pci_id = (काष्ठा acpi_pci_id *)region_context;
	pci_रेजिस्टर = (u16) (u32) address;

	ACPI_DEBUG_PRINT((ACPI_DB_INFO,
			  "Pci-Config %u (%u) Seg(%04x) Bus(%04x) "
			  "Dev(%04x) Func(%04x) Reg(%04x)\n",
			  function, bit_width, pci_id->segment, pci_id->bus,
			  pci_id->device, pci_id->function, pci_रेजिस्टर));

	चयन (function) अणु
	हाल ACPI_READ:

		*value = 0;
		status =
		    acpi_os_पढ़ो_pci_configuration(pci_id, pci_रेजिस्टर, value,
						   bit_width);
		अवरोध;

	हाल ACPI_WRITE:

		status =
		    acpi_os_ग_लिखो_pci_configuration(pci_id, pci_रेजिस्टर,
						    *value, bit_width);
		अवरोध;

	शेष:

		status = AE_BAD_PARAMETER;
		अवरोध;
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण
#पूर्ण_अगर

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_cmos_space_handler
 *
 * PARAMETERS:  function            - Read or Write operation
 *              address             - Where in the space to पढ़ो or ग_लिखो
 *              bit_width           - Field width in bits (8, 16, or 32)
 *              value               - Poपूर्णांकer to in or out value
 *              handler_context     - Poपूर्णांकer to Handler's context
 *              region_context      - Poपूर्णांकer to context specअगरic to the
 *                                    accessed region
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Handler क्रम the CMOS address space (Op Region)
 *
 ******************************************************************************/

acpi_status
acpi_ex_cmos_space_handler(u32 function,
			   acpi_physical_address address,
			   u32 bit_width,
			   u64 *value,
			   व्योम *handler_context, व्योम *region_context)
अणु
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TRACE(ex_cmos_space_handler);

	वापस_ACPI_STATUS(status);
पूर्ण

#अगर_घोषित ACPI_PCI_CONFIGURED
/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_pci_bar_space_handler
 *
 * PARAMETERS:  function            - Read or Write operation
 *              address             - Where in the space to पढ़ो or ग_लिखो
 *              bit_width           - Field width in bits (8, 16, or 32)
 *              value               - Poपूर्णांकer to in or out value
 *              handler_context     - Poपूर्णांकer to Handler's context
 *              region_context      - Poपूर्णांकer to context specअगरic to the
 *                                    accessed region
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Handler क्रम the PCI bar_target address space (Op Region)
 *
 ******************************************************************************/

acpi_status
acpi_ex_pci_bar_space_handler(u32 function,
			      acpi_physical_address address,
			      u32 bit_width,
			      u64 *value,
			      व्योम *handler_context, व्योम *region_context)
अणु
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TRACE(ex_pci_bar_space_handler);

	वापस_ACPI_STATUS(status);
पूर्ण
#पूर्ण_अगर

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_data_table_space_handler
 *
 * PARAMETERS:  function            - Read or Write operation
 *              address             - Where in the space to पढ़ो or ग_लिखो
 *              bit_width           - Field width in bits (8, 16, or 32)
 *              value               - Poपूर्णांकer to in or out value
 *              handler_context     - Poपूर्णांकer to Handler's context
 *              region_context      - Poपूर्णांकer to context specअगरic to the
 *                                    accessed region
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Handler क्रम the Data Table address space (Op Region)
 *
 ******************************************************************************/

acpi_status
acpi_ex_data_table_space_handler(u32 function,
				 acpi_physical_address address,
				 u32 bit_width,
				 u64 *value,
				 व्योम *handler_context, व्योम *region_context)
अणु
	ACPI_FUNCTION_TRACE(ex_data_table_space_handler);

	/*
	 * Perक्रमm the memory पढ़ो or ग_लिखो. The bit_width was alपढ़ोy
	 * validated.
	 */
	चयन (function) अणु
	हाल ACPI_READ:

		स_नकल(ACPI_CAST_PTR(अक्षर, value),
		       ACPI_PHYSADDR_TO_PTR(address), ACPI_DIV_8(bit_width));
		अवरोध;

	हाल ACPI_WRITE:

		स_नकल(ACPI_PHYSADDR_TO_PTR(address),
		       ACPI_CAST_PTR(अक्षर, value), ACPI_DIV_8(bit_width));
		अवरोध;

	शेष:

		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	वापस_ACPI_STATUS(AE_OK);
पूर्ण
