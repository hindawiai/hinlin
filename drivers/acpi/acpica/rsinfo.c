<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/*******************************************************************************
 *
 * Module Name: rsinfo - Dispatch and Info tables
 *
 ******************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acresrc.h"

#घोषणा _COMPONENT          ACPI_RESOURCES
ACPI_MODULE_NAME("rsinfo")

/*
 * Resource dispatch and inक्रमmation tables. Any new resource types (either
 * Large or Small) must be reflected in each of these tables, so they are here
 * in one place.
 *
 * The tables क्रम Large descriptors are indexed by bits 6:0 of the AML
 * descriptor type byte. The tables क्रम Small descriptors are indexed by
 * bits 6:3 of the descriptor byte. The tables क्रम पूर्णांकernal resource
 * descriptors are indexed by the acpi_resource_type field.
 */
/* Dispatch table क्रम resource-to-AML (Set Resource) conversion functions */
काष्ठा acpi_rsconvert_info *acpi_gbl_set_resource_dispatch[] = अणु
	acpi_rs_set_irq,	/* 0x00, ACPI_RESOURCE_TYPE_IRQ */
	acpi_rs_convert_dma,	/* 0x01, ACPI_RESOURCE_TYPE_DMA */
	acpi_rs_set_start_dpf,	/* 0x02, ACPI_RESOURCE_TYPE_START_DEPENDENT */
	acpi_rs_convert_end_dpf,	/* 0x03, ACPI_RESOURCE_TYPE_END_DEPENDENT */
	acpi_rs_convert_io,	/* 0x04, ACPI_RESOURCE_TYPE_IO */
	acpi_rs_convert_fixed_io,	/* 0x05, ACPI_RESOURCE_TYPE_FIXED_IO */
	acpi_rs_set_venकरोr,	/* 0x06, ACPI_RESOURCE_TYPE_VENDOR */
	acpi_rs_convert_end_tag,	/* 0x07, ACPI_RESOURCE_TYPE_END_TAG */
	acpi_rs_convert_memory24,	/* 0x08, ACPI_RESOURCE_TYPE_MEMORY24 */
	acpi_rs_convert_memory32,	/* 0x09, ACPI_RESOURCE_TYPE_MEMORY32 */
	acpi_rs_convert_fixed_memory32,	/* 0x0A, ACPI_RESOURCE_TYPE_FIXED_MEMORY32 */
	acpi_rs_convert_address16,	/* 0x0B, ACPI_RESOURCE_TYPE_ADDRESS16 */
	acpi_rs_convert_address32,	/* 0x0C, ACPI_RESOURCE_TYPE_ADDRESS32 */
	acpi_rs_convert_address64,	/* 0x0D, ACPI_RESOURCE_TYPE_ADDRESS64 */
	acpi_rs_convert_ext_address64,	/* 0x0E, ACPI_RESOURCE_TYPE_EXTENDED_ADDRESS64 */
	acpi_rs_convert_ext_irq,	/* 0x0F, ACPI_RESOURCE_TYPE_EXTENDED_IRQ */
	acpi_rs_convert_generic_reg,	/* 0x10, ACPI_RESOURCE_TYPE_GENERIC_REGISTER */
	acpi_rs_convert_gpio,	/* 0x11, ACPI_RESOURCE_TYPE_GPIO */
	acpi_rs_convert_fixed_dma,	/* 0x12, ACPI_RESOURCE_TYPE_FIXED_DMA */
	शून्य,			/* 0x13, ACPI_RESOURCE_TYPE_SERIAL_BUS - Use subtype table below */
	acpi_rs_convert_pin_function,	/* 0x14, ACPI_RESOURCE_TYPE_PIN_FUNCTION */
	acpi_rs_convert_pin_config,	/* 0x15, ACPI_RESOURCE_TYPE_PIN_CONFIG */
	acpi_rs_convert_pin_group,	/* 0x16, ACPI_RESOURCE_TYPE_PIN_GROUP */
	acpi_rs_convert_pin_group_function,	/* 0x17, ACPI_RESOURCE_TYPE_PIN_GROUP_FUNCTION */
	acpi_rs_convert_pin_group_config,	/* 0x18, ACPI_RESOURCE_TYPE_PIN_GROUP_CONFIG */
पूर्ण;

/* Dispatch tables क्रम AML-to-resource (Get Resource) conversion functions */

काष्ठा acpi_rsconvert_info *acpi_gbl_get_resource_dispatch[] = अणु
	/* Small descriptors */

	शून्य,			/* 0x00, Reserved */
	शून्य,			/* 0x01, Reserved */
	शून्य,			/* 0x02, Reserved */
	शून्य,			/* 0x03, Reserved */
	acpi_rs_get_irq,	/* 0x04, ACPI_RESOURCE_NAME_IRQ */
	acpi_rs_convert_dma,	/* 0x05, ACPI_RESOURCE_NAME_DMA */
	acpi_rs_get_start_dpf,	/* 0x06, ACPI_RESOURCE_NAME_START_DEPENDENT */
	acpi_rs_convert_end_dpf,	/* 0x07, ACPI_RESOURCE_NAME_END_DEPENDENT */
	acpi_rs_convert_io,	/* 0x08, ACPI_RESOURCE_NAME_IO */
	acpi_rs_convert_fixed_io,	/* 0x09, ACPI_RESOURCE_NAME_FIXED_IO */
	acpi_rs_convert_fixed_dma,	/* 0x0A, ACPI_RESOURCE_NAME_FIXED_DMA */
	शून्य,			/* 0x0B, Reserved */
	शून्य,			/* 0x0C, Reserved */
	शून्य,			/* 0x0D, Reserved */
	acpi_rs_get_venकरोr_small,	/* 0x0E, ACPI_RESOURCE_NAME_VENDOR_SMALL */
	acpi_rs_convert_end_tag,	/* 0x0F, ACPI_RESOURCE_NAME_END_TAG */

	/* Large descriptors */

	शून्य,			/* 0x00, Reserved */
	acpi_rs_convert_memory24,	/* 0x01, ACPI_RESOURCE_NAME_MEMORY24 */
	acpi_rs_convert_generic_reg,	/* 0x02, ACPI_RESOURCE_NAME_GENERIC_REGISTER */
	शून्य,			/* 0x03, Reserved */
	acpi_rs_get_venकरोr_large,	/* 0x04, ACPI_RESOURCE_NAME_VENDOR_LARGE */
	acpi_rs_convert_memory32,	/* 0x05, ACPI_RESOURCE_NAME_MEMORY32 */
	acpi_rs_convert_fixed_memory32,	/* 0x06, ACPI_RESOURCE_NAME_FIXED_MEMORY32 */
	acpi_rs_convert_address32,	/* 0x07, ACPI_RESOURCE_NAME_ADDRESS32 */
	acpi_rs_convert_address16,	/* 0x08, ACPI_RESOURCE_NAME_ADDRESS16 */
	acpi_rs_convert_ext_irq,	/* 0x09, ACPI_RESOURCE_NAME_EXTENDED_IRQ */
	acpi_rs_convert_address64,	/* 0x0A, ACPI_RESOURCE_NAME_ADDRESS64 */
	acpi_rs_convert_ext_address64,	/* 0x0B, ACPI_RESOURCE_NAME_EXTENDED_ADDRESS64 */
	acpi_rs_convert_gpio,	/* 0x0C, ACPI_RESOURCE_NAME_GPIO */
	acpi_rs_convert_pin_function,	/* 0x0D, ACPI_RESOURCE_NAME_PIN_FUNCTION */
	शून्य,			/* 0x0E, ACPI_RESOURCE_NAME_SERIAL_BUS - Use subtype table below */
	acpi_rs_convert_pin_config,	/* 0x0F, ACPI_RESOURCE_NAME_PIN_CONFIG */
	acpi_rs_convert_pin_group,	/* 0x10, ACPI_RESOURCE_NAME_PIN_GROUP */
	acpi_rs_convert_pin_group_function,	/* 0x11, ACPI_RESOURCE_NAME_PIN_GROUP_FUNCTION */
	acpi_rs_convert_pin_group_config,	/* 0x12, ACPI_RESOURCE_NAME_PIN_GROUP_CONFIG */
पूर्ण;

/* Subtype table क्रम serial_bus -- I2C, SPI, UART, and CSI2 */

काष्ठा acpi_rsconvert_info *acpi_gbl_convert_resource_serial_bus_dispatch[] = अणु
	शून्य,
	acpi_rs_convert_i2c_serial_bus,
	acpi_rs_convert_spi_serial_bus,
	acpi_rs_convert_uart_serial_bus,
	acpi_rs_convert_csi2_serial_bus
पूर्ण;

#अगर defined(ACPI_DEBUG_OUTPUT) || defined(ACPI_DISASSEMBLER) || defined(ACPI_DEBUGGER)

/* Dispatch table क्रम resource dump functions */

काष्ठा acpi_rsdump_info *acpi_gbl_dump_resource_dispatch[] = अणु
	acpi_rs_dump_irq,	/* ACPI_RESOURCE_TYPE_IRQ */
	acpi_rs_dump_dma,	/* ACPI_RESOURCE_TYPE_DMA */
	acpi_rs_dump_start_dpf,	/* ACPI_RESOURCE_TYPE_START_DEPENDENT */
	acpi_rs_dump_end_dpf,	/* ACPI_RESOURCE_TYPE_END_DEPENDENT */
	acpi_rs_dump_io,	/* ACPI_RESOURCE_TYPE_IO */
	acpi_rs_dump_fixed_io,	/* ACPI_RESOURCE_TYPE_FIXED_IO */
	acpi_rs_dump_venकरोr,	/* ACPI_RESOURCE_TYPE_VENDOR */
	acpi_rs_dump_end_tag,	/* ACPI_RESOURCE_TYPE_END_TAG */
	acpi_rs_dump_memory24,	/* ACPI_RESOURCE_TYPE_MEMORY24 */
	acpi_rs_dump_memory32,	/* ACPI_RESOURCE_TYPE_MEMORY32 */
	acpi_rs_dump_fixed_memory32,	/* ACPI_RESOURCE_TYPE_FIXED_MEMORY32 */
	acpi_rs_dump_address16,	/* ACPI_RESOURCE_TYPE_ADDRESS16 */
	acpi_rs_dump_address32,	/* ACPI_RESOURCE_TYPE_ADDRESS32 */
	acpi_rs_dump_address64,	/* ACPI_RESOURCE_TYPE_ADDRESS64 */
	acpi_rs_dump_ext_address64,	/* ACPI_RESOURCE_TYPE_EXTENDED_ADDRESS64 */
	acpi_rs_dump_ext_irq,	/* ACPI_RESOURCE_TYPE_EXTENDED_IRQ */
	acpi_rs_dump_generic_reg,	/* ACPI_RESOURCE_TYPE_GENERIC_REGISTER */
	acpi_rs_dump_gpio,	/* ACPI_RESOURCE_TYPE_GPIO */
	acpi_rs_dump_fixed_dma,	/* ACPI_RESOURCE_TYPE_FIXED_DMA */
	शून्य,			/* ACPI_RESOURCE_TYPE_SERIAL_BUS */
	acpi_rs_dump_pin_function,	/* ACPI_RESOURCE_TYPE_PIN_FUNCTION */
	acpi_rs_dump_pin_config,	/* ACPI_RESOURCE_TYPE_PIN_CONFIG */
	acpi_rs_dump_pin_group,	/* ACPI_RESOURCE_TYPE_PIN_GROUP */
	acpi_rs_dump_pin_group_function,	/* ACPI_RESOURCE_TYPE_PIN_GROUP_FUNCTION */
	acpi_rs_dump_pin_group_config,	/* ACPI_RESOURCE_TYPE_PIN_GROUP_CONFIG */
पूर्ण;

काष्ठा acpi_rsdump_info *acpi_gbl_dump_serial_bus_dispatch[] = अणु
	शून्य,
	acpi_rs_dump_i2c_serial_bus,	/* AML_RESOURCE_I2C_BUS_TYPE */
	acpi_rs_dump_spi_serial_bus,	/* AML_RESOURCE_SPI_BUS_TYPE */
	acpi_rs_dump_uart_serial_bus,	/* AML_RESOURCE_UART_BUS_TYPE */
	acpi_rs_dump_csi2_serial_bus,	/* AML_RESOURCE_CSI2_BUS_TYPE */
पूर्ण;
#पूर्ण_अगर

/*
 * Base sizes क्रम बाह्यal AML resource descriptors, indexed by पूर्णांकernal type.
 * Includes size of the descriptor header (1 byte क्रम small descriptors,
 * 3 bytes क्रम large descriptors)
 */
स्थिर u8 acpi_gbl_aml_resource_sizes[] = अणु
	माप(काष्ठा aml_resource_irq),	/* ACPI_RESOURCE_TYPE_IRQ (optional Byte 3 always created) */
	माप(काष्ठा aml_resource_dma),	/* ACPI_RESOURCE_TYPE_DMA */
	माप(काष्ठा aml_resource_start_dependent),	/* ACPI_RESOURCE_TYPE_START_DEPENDENT (optional Byte 1 always created) */
	माप(काष्ठा aml_resource_end_dependent),	/* ACPI_RESOURCE_TYPE_END_DEPENDENT */
	माप(काष्ठा aml_resource_io),	/* ACPI_RESOURCE_TYPE_IO */
	माप(काष्ठा aml_resource_fixed_io),	/* ACPI_RESOURCE_TYPE_FIXED_IO */
	माप(काष्ठा aml_resource_venकरोr_small),	/* ACPI_RESOURCE_TYPE_VENDOR */
	माप(काष्ठा aml_resource_end_tag),	/* ACPI_RESOURCE_TYPE_END_TAG */
	माप(काष्ठा aml_resource_memory24),	/* ACPI_RESOURCE_TYPE_MEMORY24 */
	माप(काष्ठा aml_resource_memory32),	/* ACPI_RESOURCE_TYPE_MEMORY32 */
	माप(काष्ठा aml_resource_fixed_memory32),	/* ACPI_RESOURCE_TYPE_FIXED_MEMORY32 */
	माप(काष्ठा aml_resource_address16),	/* ACPI_RESOURCE_TYPE_ADDRESS16 */
	माप(काष्ठा aml_resource_address32),	/* ACPI_RESOURCE_TYPE_ADDRESS32 */
	माप(काष्ठा aml_resource_address64),	/* ACPI_RESOURCE_TYPE_ADDRESS64 */
	माप(काष्ठा aml_resource_extended_address64),	/*ACPI_RESOURCE_TYPE_EXTENDED_ADDRESS64 */
	माप(काष्ठा aml_resource_extended_irq),	/* ACPI_RESOURCE_TYPE_EXTENDED_IRQ */
	माप(काष्ठा aml_resource_generic_रेजिस्टर),	/* ACPI_RESOURCE_TYPE_GENERIC_REGISTER */
	माप(काष्ठा aml_resource_gpio),	/* ACPI_RESOURCE_TYPE_GPIO */
	माप(काष्ठा aml_resource_fixed_dma),	/* ACPI_RESOURCE_TYPE_FIXED_DMA */
	माप(काष्ठा aml_resource_common_serialbus),	/* ACPI_RESOURCE_TYPE_SERIAL_BUS */
	माप(काष्ठा aml_resource_pin_function),	/* ACPI_RESOURCE_TYPE_PIN_FUNCTION */
	माप(काष्ठा aml_resource_pin_config),	/* ACPI_RESOURCE_TYPE_PIN_CONFIG */
	माप(काष्ठा aml_resource_pin_group),	/* ACPI_RESOURCE_TYPE_PIN_GROUP */
	माप(काष्ठा aml_resource_pin_group_function),	/* ACPI_RESOURCE_TYPE_PIN_GROUP_FUNCTION */
	माप(काष्ठा aml_resource_pin_group_config),	/* ACPI_RESOURCE_TYPE_PIN_GROUP_CONFIG */
पूर्ण;

स्थिर u8 acpi_gbl_resource_काष्ठा_sizes[] = अणु
	/* Small descriptors */

	0,
	0,
	0,
	0,
	ACPI_RS_SIZE(काष्ठा acpi_resource_irq),
	ACPI_RS_SIZE(काष्ठा acpi_resource_dma),
	ACPI_RS_SIZE(काष्ठा acpi_resource_start_dependent),
	ACPI_RS_SIZE_MIN,
	ACPI_RS_SIZE(काष्ठा acpi_resource_io),
	ACPI_RS_SIZE(काष्ठा acpi_resource_fixed_io),
	ACPI_RS_SIZE(काष्ठा acpi_resource_fixed_dma),
	0,
	0,
	0,
	ACPI_RS_SIZE(काष्ठा acpi_resource_venकरोr),
	ACPI_RS_SIZE_MIN,

	/* Large descriptors */

	0,
	ACPI_RS_SIZE(काष्ठा acpi_resource_memory24),
	ACPI_RS_SIZE(काष्ठा acpi_resource_generic_रेजिस्टर),
	0,
	ACPI_RS_SIZE(काष्ठा acpi_resource_venकरोr),
	ACPI_RS_SIZE(काष्ठा acpi_resource_memory32),
	ACPI_RS_SIZE(काष्ठा acpi_resource_fixed_memory32),
	ACPI_RS_SIZE(काष्ठा acpi_resource_address32),
	ACPI_RS_SIZE(काष्ठा acpi_resource_address16),
	ACPI_RS_SIZE(काष्ठा acpi_resource_extended_irq),
	ACPI_RS_SIZE(काष्ठा acpi_resource_address64),
	ACPI_RS_SIZE(काष्ठा acpi_resource_extended_address64),
	ACPI_RS_SIZE(काष्ठा acpi_resource_gpio),
	ACPI_RS_SIZE(काष्ठा acpi_resource_pin_function),
	ACPI_RS_SIZE(काष्ठा acpi_resource_common_serialbus),
	ACPI_RS_SIZE(काष्ठा acpi_resource_pin_config),
	ACPI_RS_SIZE(काष्ठा acpi_resource_pin_group),
	ACPI_RS_SIZE(काष्ठा acpi_resource_pin_group_function),
	ACPI_RS_SIZE(काष्ठा acpi_resource_pin_group_config),
पूर्ण;

स्थिर u8 acpi_gbl_aml_resource_serial_bus_sizes[] = अणु
	0,
	माप(काष्ठा aml_resource_i2c_serialbus),
	माप(काष्ठा aml_resource_spi_serialbus),
	माप(काष्ठा aml_resource_uart_serialbus),
	माप(काष्ठा aml_resource_csi2_serialbus),
पूर्ण;

स्थिर u8 acpi_gbl_resource_काष्ठा_serial_bus_sizes[] = अणु
	0,
	ACPI_RS_SIZE(काष्ठा acpi_resource_i2c_serialbus),
	ACPI_RS_SIZE(काष्ठा acpi_resource_spi_serialbus),
	ACPI_RS_SIZE(काष्ठा acpi_resource_uart_serialbus),
	ACPI_RS_SIZE(काष्ठा acpi_resource_csi2_serialbus),
पूर्ण;
