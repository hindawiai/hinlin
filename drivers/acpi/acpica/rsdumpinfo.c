<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/*******************************************************************************
 *
 * Module Name: rsdumpinfo - Tables used to display resource descriptors.
 *
 ******************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acresrc.h"

#घोषणा _COMPONENT          ACPI_RESOURCES
ACPI_MODULE_NAME("rsdumpinfo")

#अगर defined(ACPI_DEBUG_OUTPUT) || defined(ACPI_DISASSEMBLER) || defined(ACPI_DEBUGGER)
#घोषणा ACPI_RSD_OFFSET(f)          (u8) ACPI_OFFSET (जोड़ acpi_resource_data,f)
#घोषणा ACPI_PRT_OFFSET(f)          (u8) ACPI_OFFSET (काष्ठा acpi_pci_routing_table,f)
#घोषणा ACPI_RSD_TABLE_SIZE(name)   (माप(name) / माप (काष्ठा acpi_rsdump_info))
/*******************************************************************************
 *
 * Resource Descriptor info tables
 *
 * Note: The first table entry must be a Title or Literal and must contain
 * the table length (number of table entries)
 *
 ******************************************************************************/
काष्ठा acpi_rsdump_info acpi_rs_dump_irq[7] = अणु
	अणुACPI_RSD_TITLE, ACPI_RSD_TABLE_SIZE(acpi_rs_dump_irq), "IRQ", शून्यपूर्ण,
	अणुACPI_RSD_UINT8, ACPI_RSD_OFFSET(irq.descriptor_length),
	 "Descriptor Length", शून्यपूर्ण,
	अणुACPI_RSD_1BITFLAG, ACPI_RSD_OFFSET(irq.triggering), "Triggering",
	 acpi_gbl_he_decodeपूर्ण,
	अणुACPI_RSD_1BITFLAG, ACPI_RSD_OFFSET(irq.polarity), "Polarity",
	 acpi_gbl_ll_decodeपूर्ण,
	अणुACPI_RSD_2BITFLAG, ACPI_RSD_OFFSET(irq.shareable), "Sharing",
	 acpi_gbl_shr_decodeपूर्ण,
	अणुACPI_RSD_UINT8, ACPI_RSD_OFFSET(irq.पूर्णांकerrupt_count),
	 "Interrupt Count", शून्यपूर्ण,
	अणुACPI_RSD_SHORTLIST, ACPI_RSD_OFFSET(irq.पूर्णांकerrupts[0]),
	 "Interrupt List", शून्यपूर्ण
पूर्ण;

काष्ठा acpi_rsdump_info acpi_rs_dump_dma[6] = अणु
	अणुACPI_RSD_TITLE, ACPI_RSD_TABLE_SIZE(acpi_rs_dump_dma), "DMA", शून्यपूर्ण,
	अणुACPI_RSD_2BITFLAG, ACPI_RSD_OFFSET(dma.type), "Speed",
	 acpi_gbl_typ_decodeपूर्ण,
	अणुACPI_RSD_1BITFLAG, ACPI_RSD_OFFSET(dma.bus_master), "Mastering",
	 acpi_gbl_bm_decodeपूर्ण,
	अणुACPI_RSD_2BITFLAG, ACPI_RSD_OFFSET(dma.transfer), "Transfer Type",
	 acpi_gbl_siz_decodeपूर्ण,
	अणुACPI_RSD_UINT8, ACPI_RSD_OFFSET(dma.channel_count), "Channel Count",
	 शून्यपूर्ण,
	अणुACPI_RSD_SHORTLIST, ACPI_RSD_OFFSET(dma.channels[0]), "Channel List",
	 शून्यपूर्ण
पूर्ण;

काष्ठा acpi_rsdump_info acpi_rs_dump_start_dpf[4] = अणु
	अणुACPI_RSD_TITLE, ACPI_RSD_TABLE_SIZE(acpi_rs_dump_start_dpf),
	 "Start-Dependent-Functions", शून्यपूर्ण,
	अणुACPI_RSD_UINT8, ACPI_RSD_OFFSET(start_dpf.descriptor_length),
	 "Descriptor Length", शून्यपूर्ण,
	अणुACPI_RSD_2BITFLAG, ACPI_RSD_OFFSET(start_dpf.compatibility_priority),
	 "Compatibility Priority", acpi_gbl_config_decodeपूर्ण,
	अणुACPI_RSD_2BITFLAG, ACPI_RSD_OFFSET(start_dpf.perक्रमmance_robustness),
	 "Performance/Robustness", acpi_gbl_config_decodeपूर्ण
पूर्ण;

काष्ठा acpi_rsdump_info acpi_rs_dump_end_dpf[1] = अणु
	अणुACPI_RSD_TITLE, ACPI_RSD_TABLE_SIZE(acpi_rs_dump_end_dpf),
	 "End-Dependent-Functions", शून्यपूर्ण
पूर्ण;

काष्ठा acpi_rsdump_info acpi_rs_dump_io[6] = अणु
	अणुACPI_RSD_TITLE, ACPI_RSD_TABLE_SIZE(acpi_rs_dump_io), "I/O", शून्यपूर्ण,
	अणुACPI_RSD_1BITFLAG, ACPI_RSD_OFFSET(io.io_decode), "Address Decoding",
	 acpi_gbl_io_decodeपूर्ण,
	अणुACPI_RSD_UINT16, ACPI_RSD_OFFSET(io.minimum), "Address Minimum", शून्यपूर्ण,
	अणुACPI_RSD_UINT16, ACPI_RSD_OFFSET(io.maximum), "Address Maximum", शून्यपूर्ण,
	अणुACPI_RSD_UINT8, ACPI_RSD_OFFSET(io.alignment), "Alignment", शून्यपूर्ण,
	अणुACPI_RSD_UINT8, ACPI_RSD_OFFSET(io.address_length), "Address Length",
	 शून्यपूर्ण
पूर्ण;

काष्ठा acpi_rsdump_info acpi_rs_dump_fixed_io[3] = अणु
	अणुACPI_RSD_TITLE, ACPI_RSD_TABLE_SIZE(acpi_rs_dump_fixed_io),
	 "Fixed I/O", शून्यपूर्ण,
	अणुACPI_RSD_UINT16, ACPI_RSD_OFFSET(fixed_io.address), "Address", शून्यपूर्ण,
	अणुACPI_RSD_UINT8, ACPI_RSD_OFFSET(fixed_io.address_length),
	 "Address Length", शून्यपूर्ण
पूर्ण;

काष्ठा acpi_rsdump_info acpi_rs_dump_venकरोr[3] = अणु
	अणुACPI_RSD_TITLE, ACPI_RSD_TABLE_SIZE(acpi_rs_dump_venकरोr),
	 "Vendor Specific", शून्यपूर्ण,
	अणुACPI_RSD_UINT16, ACPI_RSD_OFFSET(venकरोr.byte_length), "Length", शून्यपूर्ण,
	अणुACPI_RSD_LONGLIST, ACPI_RSD_OFFSET(venकरोr.byte_data[0]), "Vendor Data",
	 शून्यपूर्ण
पूर्ण;

काष्ठा acpi_rsdump_info acpi_rs_dump_end_tag[1] = अणु
	अणुACPI_RSD_TITLE, ACPI_RSD_TABLE_SIZE(acpi_rs_dump_end_tag), "EndTag",
	 शून्यपूर्ण
पूर्ण;

काष्ठा acpi_rsdump_info acpi_rs_dump_memory24[6] = अणु
	अणुACPI_RSD_TITLE, ACPI_RSD_TABLE_SIZE(acpi_rs_dump_memory24),
	 "24-Bit Memory Range", शून्यपूर्ण,
	अणुACPI_RSD_1BITFLAG, ACPI_RSD_OFFSET(memory24.ग_लिखो_protect),
	 "Write Protect", acpi_gbl_rw_decodeपूर्ण,
	अणुACPI_RSD_UINT16, ACPI_RSD_OFFSET(memory24.minimum), "Address Minimum",
	 शून्यपूर्ण,
	अणुACPI_RSD_UINT16, ACPI_RSD_OFFSET(memory24.maximum), "Address Maximum",
	 शून्यपूर्ण,
	अणुACPI_RSD_UINT16, ACPI_RSD_OFFSET(memory24.alignment), "Alignment",
	 शून्यपूर्ण,
	अणुACPI_RSD_UINT16, ACPI_RSD_OFFSET(memory24.address_length),
	 "Address Length", शून्यपूर्ण
पूर्ण;

काष्ठा acpi_rsdump_info acpi_rs_dump_memory32[6] = अणु
	अणुACPI_RSD_TITLE, ACPI_RSD_TABLE_SIZE(acpi_rs_dump_memory32),
	 "32-Bit Memory Range", शून्यपूर्ण,
	अणुACPI_RSD_1BITFLAG, ACPI_RSD_OFFSET(memory32.ग_लिखो_protect),
	 "Write Protect", acpi_gbl_rw_decodeपूर्ण,
	अणुACPI_RSD_UINT32, ACPI_RSD_OFFSET(memory32.minimum), "Address Minimum",
	 शून्यपूर्ण,
	अणुACPI_RSD_UINT32, ACPI_RSD_OFFSET(memory32.maximum), "Address Maximum",
	 शून्यपूर्ण,
	अणुACPI_RSD_UINT32, ACPI_RSD_OFFSET(memory32.alignment), "Alignment",
	 शून्यपूर्ण,
	अणुACPI_RSD_UINT32, ACPI_RSD_OFFSET(memory32.address_length),
	 "Address Length", शून्यपूर्ण
पूर्ण;

काष्ठा acpi_rsdump_info acpi_rs_dump_fixed_memory32[4] = अणु
	अणुACPI_RSD_TITLE, ACPI_RSD_TABLE_SIZE(acpi_rs_dump_fixed_memory32),
	 "32-Bit Fixed Memory Range", शून्यपूर्ण,
	अणुACPI_RSD_1BITFLAG, ACPI_RSD_OFFSET(fixed_memory32.ग_लिखो_protect),
	 "Write Protect", acpi_gbl_rw_decodeपूर्ण,
	अणुACPI_RSD_UINT32, ACPI_RSD_OFFSET(fixed_memory32.address), "Address",
	 शून्यपूर्ण,
	अणुACPI_RSD_UINT32, ACPI_RSD_OFFSET(fixed_memory32.address_length),
	 "Address Length", शून्यपूर्ण
पूर्ण;

काष्ठा acpi_rsdump_info acpi_rs_dump_address16[8] = अणु
	अणुACPI_RSD_TITLE, ACPI_RSD_TABLE_SIZE(acpi_rs_dump_address16),
	 "16-Bit WORD Address Space", शून्यपूर्ण,
	अणुACPI_RSD_ADDRESS, 0, शून्य, शून्यपूर्ण,
	अणुACPI_RSD_UINT16, ACPI_RSD_OFFSET(address16.address.granularity),
	 "Granularity", शून्यपूर्ण,
	अणुACPI_RSD_UINT16, ACPI_RSD_OFFSET(address16.address.minimum),
	 "Address Minimum", शून्यपूर्ण,
	अणुACPI_RSD_UINT16, ACPI_RSD_OFFSET(address16.address.maximum),
	 "Address Maximum", शून्यपूर्ण,
	अणुACPI_RSD_UINT16, ACPI_RSD_OFFSET(address16.address.translation_offset),
	 "Translation Offset", शून्यपूर्ण,
	अणुACPI_RSD_UINT16, ACPI_RSD_OFFSET(address16.address.address_length),
	 "Address Length", शून्यपूर्ण,
	अणुACPI_RSD_SOURCE, ACPI_RSD_OFFSET(address16.resource_source), शून्य, शून्यपूर्ण
पूर्ण;

काष्ठा acpi_rsdump_info acpi_rs_dump_address32[8] = अणु
	अणुACPI_RSD_TITLE, ACPI_RSD_TABLE_SIZE(acpi_rs_dump_address32),
	 "32-Bit DWORD Address Space", शून्यपूर्ण,
	अणुACPI_RSD_ADDRESS, 0, शून्य, शून्यपूर्ण,
	अणुACPI_RSD_UINT32, ACPI_RSD_OFFSET(address32.address.granularity),
	 "Granularity", शून्यपूर्ण,
	अणुACPI_RSD_UINT32, ACPI_RSD_OFFSET(address32.address.minimum),
	 "Address Minimum", शून्यपूर्ण,
	अणुACPI_RSD_UINT32, ACPI_RSD_OFFSET(address32.address.maximum),
	 "Address Maximum", शून्यपूर्ण,
	अणुACPI_RSD_UINT32, ACPI_RSD_OFFSET(address32.address.translation_offset),
	 "Translation Offset", शून्यपूर्ण,
	अणुACPI_RSD_UINT32, ACPI_RSD_OFFSET(address32.address.address_length),
	 "Address Length", शून्यपूर्ण,
	अणुACPI_RSD_SOURCE, ACPI_RSD_OFFSET(address32.resource_source), शून्य, शून्यपूर्ण
पूर्ण;

काष्ठा acpi_rsdump_info acpi_rs_dump_address64[8] = अणु
	अणुACPI_RSD_TITLE, ACPI_RSD_TABLE_SIZE(acpi_rs_dump_address64),
	 "64-Bit QWORD Address Space", शून्यपूर्ण,
	अणुACPI_RSD_ADDRESS, 0, शून्य, शून्यपूर्ण,
	अणुACPI_RSD_UINT64, ACPI_RSD_OFFSET(address64.address.granularity),
	 "Granularity", शून्यपूर्ण,
	अणुACPI_RSD_UINT64, ACPI_RSD_OFFSET(address64.address.minimum),
	 "Address Minimum", शून्यपूर्ण,
	अणुACPI_RSD_UINT64, ACPI_RSD_OFFSET(address64.address.maximum),
	 "Address Maximum", शून्यपूर्ण,
	अणुACPI_RSD_UINT64, ACPI_RSD_OFFSET(address64.address.translation_offset),
	 "Translation Offset", शून्यपूर्ण,
	अणुACPI_RSD_UINT64, ACPI_RSD_OFFSET(address64.address.address_length),
	 "Address Length", शून्यपूर्ण,
	अणुACPI_RSD_SOURCE, ACPI_RSD_OFFSET(address64.resource_source), शून्य, शून्यपूर्ण
पूर्ण;

काष्ठा acpi_rsdump_info acpi_rs_dump_ext_address64[8] = अणु
	अणुACPI_RSD_TITLE, ACPI_RSD_TABLE_SIZE(acpi_rs_dump_ext_address64),
	 "64-Bit Extended Address Space", शून्यपूर्ण,
	अणुACPI_RSD_ADDRESS, 0, शून्य, शून्यपूर्ण,
	अणुACPI_RSD_UINT64, ACPI_RSD_OFFSET(ext_address64.address.granularity),
	 "Granularity", शून्यपूर्ण,
	अणुACPI_RSD_UINT64, ACPI_RSD_OFFSET(ext_address64.address.minimum),
	 "Address Minimum", शून्यपूर्ण,
	अणुACPI_RSD_UINT64, ACPI_RSD_OFFSET(ext_address64.address.maximum),
	 "Address Maximum", शून्यपूर्ण,
	अणुACPI_RSD_UINT64,
	 ACPI_RSD_OFFSET(ext_address64.address.translation_offset),
	 "Translation Offset", शून्यपूर्ण,
	अणुACPI_RSD_UINT64, ACPI_RSD_OFFSET(ext_address64.address.address_length),
	 "Address Length", शून्यपूर्ण,
	अणुACPI_RSD_UINT64, ACPI_RSD_OFFSET(ext_address64.type_specअगरic),
	 "Type-Specific Attribute", शून्यपूर्ण
पूर्ण;

काष्ठा acpi_rsdump_info acpi_rs_dump_ext_irq[8] = अणु
	अणुACPI_RSD_TITLE, ACPI_RSD_TABLE_SIZE(acpi_rs_dump_ext_irq),
	 "Extended IRQ", शून्यपूर्ण,
	अणुACPI_RSD_1BITFLAG, ACPI_RSD_OFFSET(extended_irq.producer_consumer),
	 "Type", acpi_gbl_consume_decodeपूर्ण,
	अणुACPI_RSD_1BITFLAG, ACPI_RSD_OFFSET(extended_irq.triggering),
	 "Triggering", acpi_gbl_he_decodeपूर्ण,
	अणुACPI_RSD_1BITFLAG, ACPI_RSD_OFFSET(extended_irq.polarity), "Polarity",
	 acpi_gbl_ll_decodeपूर्ण,
	अणुACPI_RSD_2BITFLAG, ACPI_RSD_OFFSET(extended_irq.shareable), "Sharing",
	 acpi_gbl_shr_decodeपूर्ण,
	अणुACPI_RSD_SOURCE, ACPI_RSD_OFFSET(extended_irq.resource_source), शून्य,
	 शून्यपूर्ण,
	अणुACPI_RSD_UINT8, ACPI_RSD_OFFSET(extended_irq.पूर्णांकerrupt_count),
	 "Interrupt Count", शून्यपूर्ण,
	अणुACPI_RSD_DWORDLIST, ACPI_RSD_OFFSET(extended_irq.पूर्णांकerrupts[0]),
	 "Interrupt List", शून्यपूर्ण
पूर्ण;

काष्ठा acpi_rsdump_info acpi_rs_dump_generic_reg[6] = अणु
	अणुACPI_RSD_TITLE, ACPI_RSD_TABLE_SIZE(acpi_rs_dump_generic_reg),
	 "Generic Register", शून्यपूर्ण,
	अणुACPI_RSD_UINT8, ACPI_RSD_OFFSET(generic_reg.space_id), "Space ID",
	 शून्यपूर्ण,
	अणुACPI_RSD_UINT8, ACPI_RSD_OFFSET(generic_reg.bit_width), "Bit Width",
	 शून्यपूर्ण,
	अणुACPI_RSD_UINT8, ACPI_RSD_OFFSET(generic_reg.bit_offset), "Bit Offset",
	 शून्यपूर्ण,
	अणुACPI_RSD_UINT8, ACPI_RSD_OFFSET(generic_reg.access_size),
	 "Access Size", शून्यपूर्ण,
	अणुACPI_RSD_UINT64, ACPI_RSD_OFFSET(generic_reg.address), "Address", शून्यपूर्ण
पूर्ण;

काष्ठा acpi_rsdump_info acpi_rs_dump_gpio[16] = अणु
	अणुACPI_RSD_TITLE, ACPI_RSD_TABLE_SIZE(acpi_rs_dump_gpio), "GPIO", शून्यपूर्ण,
	अणुACPI_RSD_UINT8, ACPI_RSD_OFFSET(gpio.revision_id), "RevisionId", शून्यपूर्ण,
	अणुACPI_RSD_UINT8, ACPI_RSD_OFFSET(gpio.connection_type),
	 "ConnectionType", acpi_gbl_ct_decodeपूर्ण,
	अणुACPI_RSD_1BITFLAG, ACPI_RSD_OFFSET(gpio.producer_consumer),
	 "ProducerConsumer", acpi_gbl_consume_decodeपूर्ण,
	अणुACPI_RSD_UINT8, ACPI_RSD_OFFSET(gpio.pin_config), "PinConfig",
	 acpi_gbl_ppc_decodeपूर्ण,
	अणुACPI_RSD_2BITFLAG, ACPI_RSD_OFFSET(gpio.shareable), "Sharing",
	 acpi_gbl_shr_decodeपूर्ण,
	अणुACPI_RSD_2BITFLAG, ACPI_RSD_OFFSET(gpio.io_restriction),
	 "IoRestriction", acpi_gbl_ior_decodeपूर्ण,
	अणुACPI_RSD_1BITFLAG, ACPI_RSD_OFFSET(gpio.triggering), "Triggering",
	 acpi_gbl_he_decodeपूर्ण,
	अणुACPI_RSD_2BITFLAG, ACPI_RSD_OFFSET(gpio.polarity), "Polarity",
	 acpi_gbl_ll_decodeपूर्ण,
	अणुACPI_RSD_UINT16, ACPI_RSD_OFFSET(gpio.drive_strength), "DriveStrength",
	 शून्यपूर्ण,
	अणुACPI_RSD_UINT16, ACPI_RSD_OFFSET(gpio.debounce_समयout),
	 "DebounceTimeout", शून्यपूर्ण,
	अणुACPI_RSD_SOURCE, ACPI_RSD_OFFSET(gpio.resource_source),
	 "ResourceSource", शून्यपूर्ण,
	अणुACPI_RSD_UINT16, ACPI_RSD_OFFSET(gpio.pin_table_length),
	 "PinTableLength", शून्यपूर्ण,
	अणुACPI_RSD_WORDLIST, ACPI_RSD_OFFSET(gpio.pin_table), "PinTable", शून्यपूर्ण,
	अणुACPI_RSD_UINT16, ACPI_RSD_OFFSET(gpio.venकरोr_length), "VendorLength",
	 शून्यपूर्ण,
	अणुACPI_RSD_SHORTLISTX, ACPI_RSD_OFFSET(gpio.venकरोr_data), "VendorData",
	 शून्यपूर्ण,
पूर्ण;

काष्ठा acpi_rsdump_info acpi_rs_dump_pin_function[10] = अणु
	अणुACPI_RSD_TITLE, ACPI_RSD_TABLE_SIZE(acpi_rs_dump_pin_function),
	 "PinFunction", शून्यपूर्ण,
	अणुACPI_RSD_UINT8, ACPI_RSD_OFFSET(pin_function.revision_id),
	 "RevisionId", शून्यपूर्ण,
	अणुACPI_RSD_UINT8, ACPI_RSD_OFFSET(pin_function.pin_config), "PinConfig",
	 acpi_gbl_ppc_decodeपूर्ण,
	अणुACPI_RSD_1BITFLAG, ACPI_RSD_OFFSET(pin_function.shareable), "Sharing",
	 acpi_gbl_shr_decodeपूर्ण,
	अणुACPI_RSD_UINT16, ACPI_RSD_OFFSET(pin_function.function_number),
	 "FunctionNumber", शून्यपूर्ण,
	अणुACPI_RSD_SOURCE, ACPI_RSD_OFFSET(pin_function.resource_source),
	 "ResourceSource", शून्यपूर्ण,
	अणुACPI_RSD_UINT16, ACPI_RSD_OFFSET(pin_function.pin_table_length),
	 "PinTableLength", शून्यपूर्ण,
	अणुACPI_RSD_WORDLIST, ACPI_RSD_OFFSET(pin_function.pin_table), "PinTable",
	 शून्यपूर्ण,
	अणुACPI_RSD_UINT16, ACPI_RSD_OFFSET(pin_function.venकरोr_length),
	 "VendorLength", शून्यपूर्ण,
	अणुACPI_RSD_SHORTLISTX, ACPI_RSD_OFFSET(pin_function.venकरोr_data),
	 "VendorData", शून्यपूर्ण,
पूर्ण;

काष्ठा acpi_rsdump_info acpi_rs_dump_pin_config[11] = अणु
	अणुACPI_RSD_TITLE, ACPI_RSD_TABLE_SIZE(acpi_rs_dump_pin_config),
	 "PinConfig", शून्यपूर्ण,
	अणुACPI_RSD_UINT8, ACPI_RSD_OFFSET(pin_config.revision_id), "RevisionId",
	 शून्यपूर्ण,
	अणुACPI_RSD_1BITFLAG, ACPI_RSD_OFFSET(pin_config.producer_consumer),
	 "ProducerConsumer", acpi_gbl_consume_decodeपूर्ण,
	अणुACPI_RSD_1BITFLAG, ACPI_RSD_OFFSET(pin_config.shareable), "Sharing",
	 acpi_gbl_shr_decodeपूर्ण,
	अणुACPI_RSD_UINT8, ACPI_RSD_OFFSET(pin_config.pin_config_type),
	 "PinConfigType", शून्यपूर्ण,
	अणुACPI_RSD_UINT32, ACPI_RSD_OFFSET(pin_config.pin_config_value),
	 "PinConfigValue", शून्यपूर्ण,
	अणुACPI_RSD_SOURCE, ACPI_RSD_OFFSET(pin_config.resource_source),
	 "ResourceSource", शून्यपूर्ण,
	अणुACPI_RSD_UINT16, ACPI_RSD_OFFSET(pin_config.pin_table_length),
	 "PinTableLength", शून्यपूर्ण,
	अणुACPI_RSD_WORDLIST, ACPI_RSD_OFFSET(pin_config.pin_table), "PinTable",
	 शून्यपूर्ण,
	अणुACPI_RSD_UINT16, ACPI_RSD_OFFSET(pin_config.venकरोr_length),
	 "VendorLength", शून्यपूर्ण,
	अणुACPI_RSD_SHORTLISTX, ACPI_RSD_OFFSET(pin_config.venकरोr_data),
	 "VendorData", शून्यपूर्ण,
पूर्ण;

काष्ठा acpi_rsdump_info acpi_rs_dump_pin_group[8] = अणु
	अणुACPI_RSD_TITLE, ACPI_RSD_TABLE_SIZE(acpi_rs_dump_pin_group),
	 "PinGroup", शून्यपूर्ण,
	अणुACPI_RSD_UINT8, ACPI_RSD_OFFSET(pin_group.revision_id), "RevisionId",
	 शून्यपूर्ण,
	अणुACPI_RSD_1BITFLAG, ACPI_RSD_OFFSET(pin_group.producer_consumer),
	 "ProducerConsumer", acpi_gbl_consume_decodeपूर्ण,
	अणुACPI_RSD_UINT16, ACPI_RSD_OFFSET(pin_group.pin_table_length),
	 "PinTableLength", शून्यपूर्ण,
	अणुACPI_RSD_WORDLIST, ACPI_RSD_OFFSET(pin_group.pin_table), "PinTable",
	 शून्यपूर्ण,
	अणुACPI_RSD_LABEL, ACPI_RSD_OFFSET(pin_group.resource_label),
	 "ResourceLabel", शून्यपूर्ण,
	अणुACPI_RSD_UINT16, ACPI_RSD_OFFSET(pin_group.venकरोr_length),
	 "VendorLength", शून्यपूर्ण,
	अणुACPI_RSD_SHORTLISTX, ACPI_RSD_OFFSET(pin_group.venकरोr_data),
	 "VendorData", शून्यपूर्ण,
पूर्ण;

काष्ठा acpi_rsdump_info acpi_rs_dump_pin_group_function[9] = अणु
	अणुACPI_RSD_TITLE, ACPI_RSD_TABLE_SIZE(acpi_rs_dump_pin_group_function),
	 "PinGroupFunction", शून्यपूर्ण,
	अणुACPI_RSD_UINT8, ACPI_RSD_OFFSET(pin_group_function.revision_id),
	 "RevisionId", शून्यपूर्ण,
	अणुACPI_RSD_1BITFLAG,
	 ACPI_RSD_OFFSET(pin_group_function.producer_consumer),
	 "ProducerConsumer", acpi_gbl_consume_decodeपूर्ण,
	अणुACPI_RSD_1BITFLAG, ACPI_RSD_OFFSET(pin_group_function.shareable),
	 "Sharing", acpi_gbl_shr_decodeपूर्ण,
	अणुACPI_RSD_UINT16, ACPI_RSD_OFFSET(pin_group_function.function_number),
	 "FunctionNumber", शून्यपूर्ण,
	अणुACPI_RSD_SOURCE_LABEL,
	 ACPI_RSD_OFFSET(pin_group_function.resource_source_label),
	 "ResourceSourceLabel", शून्यपूर्ण,
	अणुACPI_RSD_SOURCE, ACPI_RSD_OFFSET(pin_group_function.resource_source),
	 "ResourceSource", शून्यपूर्ण,
	अणुACPI_RSD_UINT16, ACPI_RSD_OFFSET(pin_group_function.venकरोr_length),
	 "VendorLength", शून्यपूर्ण,
	अणुACPI_RSD_SHORTLISTX, ACPI_RSD_OFFSET(pin_group_function.venकरोr_data),
	 "VendorData", शून्यपूर्ण,
पूर्ण;

काष्ठा acpi_rsdump_info acpi_rs_dump_pin_group_config[10] = अणु
	अणुACPI_RSD_TITLE, ACPI_RSD_TABLE_SIZE(acpi_rs_dump_pin_group_config),
	 "PinGroupConfig", शून्यपूर्ण,
	अणुACPI_RSD_UINT8, ACPI_RSD_OFFSET(pin_group_config.revision_id),
	 "RevisionId", शून्यपूर्ण,
	अणुACPI_RSD_1BITFLAG, ACPI_RSD_OFFSET(pin_group_config.producer_consumer),
	 "ProducerConsumer", acpi_gbl_consume_decodeपूर्ण,
	अणुACPI_RSD_1BITFLAG, ACPI_RSD_OFFSET(pin_group_config.shareable),
	 "Sharing", acpi_gbl_shr_decodeपूर्ण,
	अणुACPI_RSD_UINT8, ACPI_RSD_OFFSET(pin_group_config.pin_config_type),
	 "PinConfigType", शून्यपूर्ण,
	अणुACPI_RSD_UINT32, ACPI_RSD_OFFSET(pin_group_config.pin_config_value),
	 "PinConfigValue", शून्यपूर्ण,
	अणुACPI_RSD_SOURCE_LABEL,
	 ACPI_RSD_OFFSET(pin_group_config.resource_source_label),
	 "ResourceSourceLabel", शून्यपूर्ण,
	अणुACPI_RSD_SOURCE, ACPI_RSD_OFFSET(pin_group_config.resource_source),
	 "ResourceSource", शून्यपूर्ण,
	अणुACPI_RSD_UINT16, ACPI_RSD_OFFSET(pin_group_config.venकरोr_length),
	 "VendorLength", शून्यपूर्ण,
	अणुACPI_RSD_SHORTLISTX, ACPI_RSD_OFFSET(pin_group_config.venकरोr_data),
	 "VendorData", शून्यपूर्ण,
पूर्ण;

काष्ठा acpi_rsdump_info acpi_rs_dump_fixed_dma[4] = अणु
	अणुACPI_RSD_TITLE, ACPI_RSD_TABLE_SIZE(acpi_rs_dump_fixed_dma),
	 "FixedDma", शून्यपूर्ण,
	अणुACPI_RSD_UINT16, ACPI_RSD_OFFSET(fixed_dma.request_lines),
	 "RequestLines", शून्यपूर्ण,
	अणुACPI_RSD_UINT16, ACPI_RSD_OFFSET(fixed_dma.channels), "Channels",
	 शून्यपूर्ण,
	अणुACPI_RSD_UINT8, ACPI_RSD_OFFSET(fixed_dma.width), "TransferWidth",
	 acpi_gbl_dts_decodeपूर्ण,
पूर्ण;

#घोषणा ACPI_RS_DUMP_COMMON_SERIAL_BUS \
	अणुACPI_RSD_UINT8,    ACPI_RSD_OFFSET (common_serial_bus.revision_id),    "RevisionId",               शून्यपूर्ण, \
	अणुACPI_RSD_UINT8,    ACPI_RSD_OFFSET (common_serial_bus.type),           "Type",                     acpi_gbl_sbt_decodeपूर्ण, \
	अणुACPI_RSD_1BITFLAG, ACPI_RSD_OFFSET (common_serial_bus.producer_consumer), "ProducerConsumer",      acpi_gbl_consume_decodeपूर्ण, \
	अणुACPI_RSD_1BITFLAG, ACPI_RSD_OFFSET (common_serial_bus.slave_mode),     "SlaveMode",                acpi_gbl_sm_decodeपूर्ण, \
	अणुACPI_RSD_1BITFLAG, ACPI_RSD_OFFSET (common_serial_bus.connection_sharing),"ConnectionSharing",     acpi_gbl_shr_decodeपूर्ण, \
	अणुACPI_RSD_UINT8,    ACPI_RSD_OFFSET (common_serial_bus.type_revision_id), "TypeRevisionId",         शून्यपूर्ण, \
	अणुACPI_RSD_UINT16,   ACPI_RSD_OFFSET (common_serial_bus.type_data_length), "TypeDataLength",         शून्यपूर्ण, \
	अणुACPI_RSD_SOURCE,   ACPI_RSD_OFFSET (common_serial_bus.resource_source), "ResourceSource",          शून्यपूर्ण, \
	अणुACPI_RSD_UINT16,   ACPI_RSD_OFFSET (common_serial_bus.venकरोr_length),  "VendorLength",             शून्यपूर्ण, \
	अणुACPI_RSD_SHORTLISTX,ACPI_RSD_OFFSET (common_serial_bus.venकरोr_data),   "VendorData",               शून्यपूर्ण,

काष्ठा acpi_rsdump_info acpi_rs_dump_common_serial_bus[11] = अणु
	अणुACPI_RSD_TITLE, ACPI_RSD_TABLE_SIZE(acpi_rs_dump_common_serial_bus),
	 "Common Serial Bus", शून्यपूर्ण,
	ACPI_RS_DUMP_COMMON_SERIAL_BUS
पूर्ण;

काष्ठा acpi_rsdump_info acpi_rs_dump_csi2_serial_bus[11] = अणु
	अणु ACPI_RSD_TITLE, ACPI_RSD_TABLE_SIZE(acpi_rs_dump_csi2_serial_bus),
	 "Camera Serial Bus", शून्य पूर्ण,
	अणु ACPI_RSD_UINT8, ACPI_RSD_OFFSET(csi2_serial_bus.revision_id),
	 "RevisionId", शून्य पूर्ण,
	अणु ACPI_RSD_UINT8, ACPI_RSD_OFFSET(csi2_serial_bus.type), "Type",
	 acpi_gbl_sbt_decode पूर्ण,
	अणु ACPI_RSD_1BITFLAG, ACPI_RSD_OFFSET(csi2_serial_bus.producer_consumer),
	 "ProducerConsumer", acpi_gbl_consume_decode पूर्ण,
	अणु ACPI_RSD_1BITFLAG, ACPI_RSD_OFFSET(csi2_serial_bus.slave_mode),
	 "SlaveMode", acpi_gbl_sm_decode पूर्ण,
	अणु ACPI_RSD_2BITFLAG, ACPI_RSD_OFFSET(csi2_serial_bus.phy_type),
	 "PhyType", acpi_gbl_phy_decode पूर्ण,
	अणु ACPI_RSD_6BITFLAG,
	 ACPI_RSD_OFFSET(csi2_serial_bus.local_port_instance),
	 "LocalPortInstance", शून्य पूर्ण,
	अणु ACPI_RSD_UINT8, ACPI_RSD_OFFSET(csi2_serial_bus.type_revision_id),
	 "TypeRevisionId", शून्य पूर्ण,
	अणु ACPI_RSD_UINT16, ACPI_RSD_OFFSET(csi2_serial_bus.venकरोr_length),
	 "VendorLength", शून्य पूर्ण,
	अणु ACPI_RSD_SHORTLISTX, ACPI_RSD_OFFSET(csi2_serial_bus.venकरोr_data),
	 "VendorData", शून्य पूर्ण,
	अणु ACPI_RSD_SOURCE, ACPI_RSD_OFFSET(csi2_serial_bus.resource_source),
	 "ResourceSource", शून्य पूर्ण,
पूर्ण;

काष्ठा acpi_rsdump_info acpi_rs_dump_i2c_serial_bus[14] = अणु
	अणुACPI_RSD_TITLE, ACPI_RSD_TABLE_SIZE(acpi_rs_dump_i2c_serial_bus),
	 "I2C Serial Bus", शून्यपूर्ण,
	ACPI_RS_DUMP_COMMON_SERIAL_BUS अणुACPI_RSD_1BITFLAG,
					ACPI_RSD_OFFSET(i2c_serial_bus.
							access_mode),
					"AccessMode", acpi_gbl_am_decodeपूर्ण,
	अणुACPI_RSD_UINT32, ACPI_RSD_OFFSET(i2c_serial_bus.connection_speed),
	 "ConnectionSpeed", शून्यपूर्ण,
	अणुACPI_RSD_UINT16, ACPI_RSD_OFFSET(i2c_serial_bus.slave_address),
	 "SlaveAddress", शून्यपूर्ण,
पूर्ण;

काष्ठा acpi_rsdump_info acpi_rs_dump_spi_serial_bus[18] = अणु
	अणुACPI_RSD_TITLE, ACPI_RSD_TABLE_SIZE(acpi_rs_dump_spi_serial_bus),
	 "Spi Serial Bus", शून्यपूर्ण,
	ACPI_RS_DUMP_COMMON_SERIAL_BUS अणुACPI_RSD_1BITFLAG,
					ACPI_RSD_OFFSET(spi_serial_bus.
							wire_mode), "WireMode",
					acpi_gbl_wm_decodeपूर्ण,
	अणुACPI_RSD_1BITFLAG, ACPI_RSD_OFFSET(spi_serial_bus.device_polarity),
	 "DevicePolarity", acpi_gbl_dp_decodeपूर्ण,
	अणुACPI_RSD_UINT8, ACPI_RSD_OFFSET(spi_serial_bus.data_bit_length),
	 "DataBitLength", शून्यपूर्ण,
	अणुACPI_RSD_UINT8, ACPI_RSD_OFFSET(spi_serial_bus.घड़ी_phase),
	 "ClockPhase", acpi_gbl_cph_decodeपूर्ण,
	अणुACPI_RSD_UINT8, ACPI_RSD_OFFSET(spi_serial_bus.घड़ी_polarity),
	 "ClockPolarity", acpi_gbl_cpo_decodeपूर्ण,
	अणुACPI_RSD_UINT16, ACPI_RSD_OFFSET(spi_serial_bus.device_selection),
	 "DeviceSelection", शून्यपूर्ण,
	अणुACPI_RSD_UINT32, ACPI_RSD_OFFSET(spi_serial_bus.connection_speed),
	 "ConnectionSpeed", शून्यपूर्ण,
पूर्ण;

काष्ठा acpi_rsdump_info acpi_rs_dump_uart_serial_bus[20] = अणु
	अणुACPI_RSD_TITLE, ACPI_RSD_TABLE_SIZE(acpi_rs_dump_uart_serial_bus),
	 "Uart Serial Bus", शून्यपूर्ण,
	ACPI_RS_DUMP_COMMON_SERIAL_BUS अणुACPI_RSD_2BITFLAG,
					ACPI_RSD_OFFSET(uart_serial_bus.
							flow_control),
					"FlowControl", acpi_gbl_fc_decodeपूर्ण,
	अणुACPI_RSD_2BITFLAG, ACPI_RSD_OFFSET(uart_serial_bus.stop_bits),
	 "StopBits", acpi_gbl_sb_decodeपूर्ण,
	अणुACPI_RSD_3BITFLAG, ACPI_RSD_OFFSET(uart_serial_bus.data_bits),
	 "DataBits", acpi_gbl_bpb_decodeपूर्ण,
	अणुACPI_RSD_1BITFLAG, ACPI_RSD_OFFSET(uart_serial_bus.endian), "Endian",
	 acpi_gbl_ed_decodeपूर्ण,
	अणुACPI_RSD_UINT8, ACPI_RSD_OFFSET(uart_serial_bus.parity), "Parity",
	 acpi_gbl_pt_decodeपूर्ण,
	अणुACPI_RSD_UINT8, ACPI_RSD_OFFSET(uart_serial_bus.lines_enabled),
	 "LinesEnabled", शून्यपूर्ण,
	अणुACPI_RSD_UINT16, ACPI_RSD_OFFSET(uart_serial_bus.rx_fअगरo_size),
	 "RxFifoSize", शून्यपूर्ण,
	अणुACPI_RSD_UINT16, ACPI_RSD_OFFSET(uart_serial_bus.tx_fअगरo_size),
	 "TxFifoSize", शून्यपूर्ण,
	अणुACPI_RSD_UINT32, ACPI_RSD_OFFSET(uart_serial_bus.शेष_baud_rate),
	 "ConnectionSpeed", शून्यपूर्ण,
पूर्ण;

/*
 * Tables used क्रम common address descriptor flag fields
 */
काष्ठा acpi_rsdump_info acpi_rs_dump_general_flags[5] = अणु
	अणुACPI_RSD_TITLE, ACPI_RSD_TABLE_SIZE(acpi_rs_dump_general_flags), शून्य,
	 शून्यपूर्ण,
	अणुACPI_RSD_1BITFLAG, ACPI_RSD_OFFSET(address.producer_consumer),
	 "Consumer/Producer", acpi_gbl_consume_decodeपूर्ण,
	अणुACPI_RSD_1BITFLAG, ACPI_RSD_OFFSET(address.decode), "Address Decode",
	 acpi_gbl_dec_decodeपूर्ण,
	अणुACPI_RSD_1BITFLAG, ACPI_RSD_OFFSET(address.min_address_fixed),
	 "Min Relocatability", acpi_gbl_min_decodeपूर्ण,
	अणुACPI_RSD_1BITFLAG, ACPI_RSD_OFFSET(address.max_address_fixed),
	 "Max Relocatability", acpi_gbl_max_decodeपूर्ण
पूर्ण;

काष्ठा acpi_rsdump_info acpi_rs_dump_memory_flags[5] = अणु
	अणुACPI_RSD_LITERAL, ACPI_RSD_TABLE_SIZE(acpi_rs_dump_memory_flags),
	 "Resource Type", (व्योम *)"Memory Range"पूर्ण,
	अणुACPI_RSD_1BITFLAG, ACPI_RSD_OFFSET(address.info.mem.ग_लिखो_protect),
	 "Write Protect", acpi_gbl_rw_decodeपूर्ण,
	अणुACPI_RSD_2BITFLAG, ACPI_RSD_OFFSET(address.info.mem.caching),
	 "Caching", acpi_gbl_mem_decodeपूर्ण,
	अणुACPI_RSD_2BITFLAG, ACPI_RSD_OFFSET(address.info.mem.range_type),
	 "Range Type", acpi_gbl_mtp_decodeपूर्ण,
	अणुACPI_RSD_1BITFLAG, ACPI_RSD_OFFSET(address.info.mem.translation),
	 "Translation", acpi_gbl_ttp_decodeपूर्ण
पूर्ण;

काष्ठा acpi_rsdump_info acpi_rs_dump_io_flags[4] = अणु
	अणुACPI_RSD_LITERAL, ACPI_RSD_TABLE_SIZE(acpi_rs_dump_io_flags),
	 "Resource Type", (व्योम *)"I/O Range"पूर्ण,
	अणुACPI_RSD_2BITFLAG, ACPI_RSD_OFFSET(address.info.io.range_type),
	 "Range Type", acpi_gbl_rng_decodeपूर्ण,
	अणुACPI_RSD_1BITFLAG, ACPI_RSD_OFFSET(address.info.io.translation),
	 "Translation", acpi_gbl_ttp_decodeपूर्ण,
	अणुACPI_RSD_1BITFLAG, ACPI_RSD_OFFSET(address.info.io.translation_type),
	 "Translation Type", acpi_gbl_trs_decodeपूर्ण
पूर्ण;

/*
 * Table used to dump _PRT contents
 */
काष्ठा acpi_rsdump_info acpi_rs_dump_prt[5] = अणु
	अणुACPI_RSD_TITLE, ACPI_RSD_TABLE_SIZE(acpi_rs_dump_prt), शून्य, शून्यपूर्ण,
	अणुACPI_RSD_UINT64, ACPI_PRT_OFFSET(address), "Address", शून्यपूर्ण,
	अणुACPI_RSD_UINT32, ACPI_PRT_OFFSET(pin), "Pin", शून्यपूर्ण,
	अणुACPI_RSD_STRING, ACPI_PRT_OFFSET(source[0]), "Source", शून्यपूर्ण,
	अणुACPI_RSD_UINT32, ACPI_PRT_OFFSET(source_index), "Source Index", शून्यपूर्ण
पूर्ण;

#पूर्ण_अगर
