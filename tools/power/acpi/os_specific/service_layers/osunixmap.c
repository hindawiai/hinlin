<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: osunixmap - Unix OSL क्रम file mappings
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश "acpidump.h"
#समावेश <unistd.h>
#समावेश <sys/mman.h>
#अगर_घोषित _मुक्त_BSD
#समावेश <sys/param.h>
#पूर्ण_अगर

#घोषणा _COMPONENT          ACPI_OS_SERVICES
ACPI_MODULE_NAME("osunixmap")

#अगर_अघोषित O_BINARY
#घोषणा O_BINARY 0
#पूर्ण_अगर
#अगर defined(_dragon_fly) || defined(_मुक्त_BSD) || defined(_QNX)
#घोषणा MMAP_FLAGS          MAP_SHARED
#अन्यथा
#घोषणा MMAP_FLAGS          MAP_PRIVATE
#पूर्ण_अगर
#घोषणा SYSTEM_MEMORY       "/dev/mem"
/*******************************************************************************
 *
 * FUNCTION:    acpi_os_get_page_size
 *
 * PARAMETERS:  None
 *
 * RETURN:      Page size of the platक्रमm.
 *
 * DESCRIPTION: Obtain page size of the platक्रमm.
 *
 ******************************************************************************/
अटल acpi_size acpi_os_get_page_size(व्योम)
अणु

#अगर_घोषित PAGE_SIZE
	वापस PAGE_SIZE;
#अन्यथा
	वापस sysconf(_SC_PAGESIZE);
#पूर्ण_अगर
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_os_map_memory
 *
 * PARAMETERS:  where               - Physical address of memory to be mapped
 *              length              - How much memory to map
 *
 * RETURN:      Poपूर्णांकer to mapped memory. Null on error.
 *
 * DESCRIPTION: Map physical memory पूर्णांकo local address space.
 *
 *****************************************************************************/

व्योम *acpi_os_map_memory(acpi_physical_address where, acpi_size length)
अणु
	u8 *mapped_memory;
	acpi_physical_address offset;
	acpi_size page_size;
	पूर्णांक fd;

	fd = खोलो(SYSTEM_MEMORY, O_RDONLY | O_BINARY);
	अगर (fd < 0) अणु
		ख_लिखो(मानक_त्रुटि, "Cannot open %s\n", SYSTEM_MEMORY);
		वापस (शून्य);
	पूर्ण

	/* Align the offset to use mmap */

	page_size = acpi_os_get_page_size();
	offset = where % page_size;

	/* Map the table header to get the length of the full table */

	mapped_memory = mmap(शून्य, (length + offset), PROT_READ, MMAP_FLAGS,
			     fd, (where - offset));
	अगर (mapped_memory == MAP_FAILED) अणु
		ख_लिखो(मानक_त्रुटि, "Cannot map %s\n", SYSTEM_MEMORY);
		बंद(fd);
		वापस (शून्य);
	पूर्ण

	बंद(fd);
	वापस (ACPI_CAST8(mapped_memory + offset));
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_os_unmap_memory
 *
 * PARAMETERS:  where               - Logical address of memory to be unmapped
 *              length              - How much memory to unmap
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Delete a previously created mapping. Where and Length must
 *              correspond to a previous mapping exactly.
 *
 *****************************************************************************/

व्योम acpi_os_unmap_memory(व्योम *where, acpi_size length)
अणु
	acpi_physical_address offset;
	acpi_size page_size;

	page_size = acpi_os_get_page_size();
	offset = ACPI_TO_INTEGER(where) % page_size;
	munmap((u8 *)where - offset, (length + offset));
पूर्ण
