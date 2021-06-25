<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: hwvalid - I/O request validation
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"

#घोषणा _COMPONENT          ACPI_HARDWARE
ACPI_MODULE_NAME("hwvalid")

/* Local prototypes */
अटल acpi_status
acpi_hw_validate_io_request(acpi_io_address address, u32 bit_width);

/*
 * Protected I/O ports. Some ports are always illegal, and some are
 * conditionally illegal. This table must reमुख्य ordered by port address.
 *
 * The table is used to implement the Microsoft port access rules that
 * first appeared in Winकरोws XP. Some ports are always illegal, and some
 * ports are only illegal अगर the BIOS calls _OSI with a win_XP string or
 * later (meaning that the BIOS itelf is post-XP.)
 *
 * This provides ACPICA with the desired port protections and
 * Microsoft compatibility.
 *
 * Description of port entries:
 *  DMA:   DMA controller
 *  PIC0:  Programmable Interrupt Controller (8259A)
 *  PIT1:  System Timer 1
 *  PIT2:  System Timer 2 failsafe
 *  RTC:   Real-समय घड़ी
 *  CMOS:  Extended CMOS
 *  DMA1:  DMA 1 page रेजिस्टरs
 *  DMA1L: DMA 1 Ch 0 low page
 *  DMA2:  DMA 2 page रेजिस्टरs
 *  DMA2L: DMA 2 low page refresh
 *  ARBC:  Arbitration control
 *  SETUP: Reserved प्रणाली board setup
 *  POS:   POS channel select
 *  PIC1:  Cascaded PIC
 *  IDMA:  ISA DMA
 *  ELCR:  PIC edge/level रेजिस्टरs
 *  PCI:   PCI configuration space
 */
अटल स्थिर काष्ठा acpi_port_info acpi_रक्षित_ports[] = अणु
	अणु"DMA", 0x0000, 0x000F, ACPI_OSI_WIN_XPपूर्ण,
	अणु"PIC0", 0x0020, 0x0021, ACPI_ALWAYS_ILLEGALपूर्ण,
	अणु"PIT1", 0x0040, 0x0043, ACPI_OSI_WIN_XPपूर्ण,
	अणु"PIT2", 0x0048, 0x004B, ACPI_OSI_WIN_XPपूर्ण,
	अणु"RTC", 0x0070, 0x0071, ACPI_OSI_WIN_XPपूर्ण,
	अणु"CMOS", 0x0074, 0x0076, ACPI_OSI_WIN_XPपूर्ण,
	अणु"DMA1", 0x0081, 0x0083, ACPI_OSI_WIN_XPपूर्ण,
	अणु"DMA1L", 0x0087, 0x0087, ACPI_OSI_WIN_XPपूर्ण,
	अणु"DMA2", 0x0089, 0x008B, ACPI_OSI_WIN_XPपूर्ण,
	अणु"DMA2L", 0x008F, 0x008F, ACPI_OSI_WIN_XPपूर्ण,
	अणु"ARBC", 0x0090, 0x0091, ACPI_OSI_WIN_XPपूर्ण,
	अणु"SETUP", 0x0093, 0x0094, ACPI_OSI_WIN_XPपूर्ण,
	अणु"POS", 0x0096, 0x0097, ACPI_OSI_WIN_XPपूर्ण,
	अणु"PIC1", 0x00A0, 0x00A1, ACPI_ALWAYS_ILLEGALपूर्ण,
	अणु"IDMA", 0x00C0, 0x00DF, ACPI_OSI_WIN_XPपूर्ण,
	अणु"ELCR", 0x04D0, 0x04D1, ACPI_ALWAYS_ILLEGALपूर्ण,
	अणु"PCI", 0x0CF8, 0x0CFF, ACPI_OSI_WIN_XPपूर्ण
पूर्ण;

#घोषणा ACPI_PORT_INFO_ENTRIES      ACPI_ARRAY_LENGTH (acpi_रक्षित_ports)

/******************************************************************************
 *
 * FUNCTION:    acpi_hw_validate_io_request
 *
 * PARAMETERS:  Address             Address of I/O port/रेजिस्टर
 *              bit_width           Number of bits (8,16,32)
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Validates an I/O request (address/length). Certain ports are
 *              always illegal and some ports are only illegal depending on
 *              the requests the BIOS AML code makes to the predefined
 *              _OSI method.
 *
 ******************************************************************************/

अटल acpi_status
acpi_hw_validate_io_request(acpi_io_address address, u32 bit_width)
अणु
	u32 i;
	u32 byte_width;
	acpi_io_address last_address;
	स्थिर काष्ठा acpi_port_info *port_info;

	ACPI_FUNCTION_TRACE(hw_validate_io_request);

	/* Supported widths are 8/16/32 */

	अगर ((bit_width != 8) && (bit_width != 16) && (bit_width != 32)) अणु
		ACPI_ERROR((AE_INFO,
			    "Bad BitWidth parameter: %8.8X", bit_width));
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	port_info = acpi_रक्षित_ports;
	byte_width = ACPI_DIV_8(bit_width);
	last_address = address + byte_width - 1;

	ACPI_DEBUG_PRINT((ACPI_DB_IO,
			  "Address %8.8X%8.8X LastAddress %8.8X%8.8X Length %X",
			  ACPI_FORMAT_UINT64(address),
			  ACPI_FORMAT_UINT64(last_address), byte_width));

	/* Maximum 16-bit address in I/O space */

	अगर (last_address > ACPI_UINT16_MAX) अणु
		ACPI_ERROR((AE_INFO,
			    "Illegal I/O port address/length above 64K: %8.8X%8.8X/0x%X",
			    ACPI_FORMAT_UINT64(address), byte_width));
		वापस_ACPI_STATUS(AE_LIMIT);
	पूर्ण

	/* Exit अगर requested address is not within the रक्षित port table */

	अगर (address > acpi_रक्षित_ports[ACPI_PORT_INFO_ENTRIES - 1].end) अणु
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	/* Check request against the list of रक्षित I/O ports */

	क्रम (i = 0; i < ACPI_PORT_INFO_ENTRIES; i++, port_info++) अणु
		/*
		 * Check अगर the requested address range will ग_लिखो to a reserved
		 * port. There are four हालs to consider:
		 *
		 * 1) Address range is contained completely in the port address range
		 * 2) Address range overlaps port range at the port range start
		 * 3) Address range overlaps port range at the port range end
		 * 4) Address range completely encompasses the port range
		 */
		अगर ((address <= port_info->end)
		    && (last_address >= port_info->start)) अणु

			/* Port illegality may depend on the _OSI calls made by the BIOS */

			अगर (acpi_gbl_osi_data >= port_info->osi_dependency) अणु
				ACPI_DEBUG_PRINT((ACPI_DB_VALUES,
						  "Denied AML access to port 0x%8.8X%8.8X/%X (%s 0x%.4X-0x%.4X)\n",
						  ACPI_FORMAT_UINT64(address),
						  byte_width, port_info->name,
						  port_info->start,
						  port_info->end));

				वापस_ACPI_STATUS(AE_AML_ILLEGAL_ADDRESS);
			पूर्ण
		पूर्ण

		/* Finished अगर address range ends beक्रमe the end of this port */

		अगर (last_address <= port_info->end) अणु
			अवरोध;
		पूर्ण
	पूर्ण

	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_hw_पढ़ो_port
 *
 * PARAMETERS:  Address             Address of I/O port/रेजिस्टर to पढ़ो
 *              Value               Where value (data) is वापसed
 *              Width               Number of bits
 *
 * RETURN:      Status and value पढ़ो from port
 *
 * DESCRIPTION: Read data from an I/O port or रेजिस्टर. This is a front-end
 *              to acpi_os_पढ़ो_port that perक्रमms validation on both the port
 *              address and the length.
 *
 *****************************************************************************/

acpi_status acpi_hw_पढ़ो_port(acpi_io_address address, u32 *value, u32 width)
अणु
	acpi_status status;
	u32 one_byte;
	u32 i;

	/* Truncate address to 16 bits अगर requested */

	अगर (acpi_gbl_truncate_io_addresses) अणु
		address &= ACPI_UINT16_MAX;
	पूर्ण

	/* Validate the entire request and perक्रमm the I/O */

	status = acpi_hw_validate_io_request(address, width);
	अगर (ACPI_SUCCESS(status)) अणु
		status = acpi_os_पढ़ो_port(address, value, width);
		वापस (status);
	पूर्ण

	अगर (status != AE_AML_ILLEGAL_ADDRESS) अणु
		वापस (status);
	पूर्ण

	/*
	 * There has been a protection violation within the request. Fall
	 * back to byte granularity port I/O and ignore the failing bytes.
	 * This provides compatibility with other ACPI implementations.
	 */
	क्रम (i = 0, *value = 0; i < width; i += 8) अणु

		/* Validate and पढ़ो one byte */

		अगर (acpi_hw_validate_io_request(address, 8) == AE_OK) अणु
			status = acpi_os_पढ़ो_port(address, &one_byte, 8);
			अगर (ACPI_FAILURE(status)) अणु
				वापस (status);
			पूर्ण

			*value |= (one_byte << i);
		पूर्ण

		address++;
	पूर्ण

	वापस (AE_OK);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_hw_ग_लिखो_port
 *
 * PARAMETERS:  Address             Address of I/O port/रेजिस्टर to ग_लिखो
 *              Value               Value to ग_लिखो
 *              Width               Number of bits
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Write data to an I/O port or रेजिस्टर. This is a front-end
 *              to acpi_os_ग_लिखो_port that perक्रमms validation on both the port
 *              address and the length.
 *
 *****************************************************************************/

acpi_status acpi_hw_ग_लिखो_port(acpi_io_address address, u32 value, u32 width)
अणु
	acpi_status status;
	u32 i;

	/* Truncate address to 16 bits अगर requested */

	अगर (acpi_gbl_truncate_io_addresses) अणु
		address &= ACPI_UINT16_MAX;
	पूर्ण

	/* Validate the entire request and perक्रमm the I/O */

	status = acpi_hw_validate_io_request(address, width);
	अगर (ACPI_SUCCESS(status)) अणु
		status = acpi_os_ग_लिखो_port(address, value, width);
		वापस (status);
	पूर्ण

	अगर (status != AE_AML_ILLEGAL_ADDRESS) अणु
		वापस (status);
	पूर्ण

	/*
	 * There has been a protection violation within the request. Fall
	 * back to byte granularity port I/O and ignore the failing bytes.
	 * This provides compatibility with other ACPI implementations.
	 */
	क्रम (i = 0; i < width; i += 8) अणु

		/* Validate and ग_लिखो one byte */

		अगर (acpi_hw_validate_io_request(address, 8) == AE_OK) अणु
			status =
			    acpi_os_ग_लिखो_port(address, (value >> i) & 0xFF, 8);
			अगर (ACPI_FAILURE(status)) अणु
				वापस (status);
			पूर्ण
		पूर्ण

		address++;
	पूर्ण

	वापस (AE_OK);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_hw_validate_io_block
 *
 * PARAMETERS:  Address             Address of I/O port/रेजिस्टर blobk
 *              bit_width           Number of bits (8,16,32) in each रेजिस्टर
 *              count               Number of रेजिस्टरs in the block
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Validates a block of I/O ports/रेजिस्टरs.
 *
 ******************************************************************************/

acpi_status acpi_hw_validate_io_block(u64 address, u32 bit_width, u32 count)
अणु
	acpi_status status;

	जबतक (count--) अणु
		status = acpi_hw_validate_io_request((acpi_io_address)address,
						     bit_width);
		अगर (ACPI_FAILURE(status))
			वापस_ACPI_STATUS(status);

		address += ACPI_DIV_8(bit_width);
	पूर्ण

	वापस_ACPI_STATUS(AE_OK);
पूर्ण
