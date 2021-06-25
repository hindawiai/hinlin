<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/******************************************************************************
 *
 * Name: acresrc.h - Resource Manager function prototypes
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#अगर_अघोषित __ACRESRC_H__
#घोषणा __ACRESRC_H__

/* Need the AML resource descriptor काष्ठाs */

#समावेश "amlresrc.h"

/*
 * If possible, pack the following काष्ठाures to byte alignment, since we
 * करोn't care about perक्रमmance क्रम debug output. Two हालs where we cannot
 * pack the काष्ठाures:
 *
 * 1) Hardware करोes not support misaligned memory transfers
 * 2) Compiler करोes not support poपूर्णांकers within packed काष्ठाures
 */
#अगर (!defined(ACPI_MISALIGNMENT_NOT_SUPPORTED) && !defined(ACPI_PACKED_POINTERS_NOT_SUPPORTED))
#आशय pack(1)
#पूर्ण_अगर

/*
 * Inभागidual entry क्रम the resource conversion tables
 */
प्रकार स्थिर काष्ठा acpi_rsconvert_info अणु
	u8 opcode;
	u8 resource_offset;
	u8 aml_offset;
	u8 value;

पूर्ण acpi_rsconvert_info;

/* Resource conversion opcodes */

प्रकार क्रमागत अणु
	ACPI_RSC_INITGET = 0,
	ACPI_RSC_INITSET,
	ACPI_RSC_FLAGINIT,
	ACPI_RSC_1BITFLAG,
	ACPI_RSC_2BITFLAG,
	ACPI_RSC_3BITFLAG,
	ACPI_RSC_6BITFLAG,
	ACPI_RSC_ADDRESS,
	ACPI_RSC_BITMASK,
	ACPI_RSC_BITMASK16,
	ACPI_RSC_COUNT,
	ACPI_RSC_COUNT16,
	ACPI_RSC_COUNT_GPIO_PIN,
	ACPI_RSC_COUNT_GPIO_RES,
	ACPI_RSC_COUNT_GPIO_VEN,
	ACPI_RSC_COUNT_SERIAL_RES,
	ACPI_RSC_COUNT_SERIAL_VEN,
	ACPI_RSC_DATA8,
	ACPI_RSC_EXIT_EQ,
	ACPI_RSC_EXIT_LE,
	ACPI_RSC_EXIT_NE,
	ACPI_RSC_LENGTH,
	ACPI_RSC_MOVE_GPIO_PIN,
	ACPI_RSC_MOVE_GPIO_RES,
	ACPI_RSC_MOVE_SERIAL_RES,
	ACPI_RSC_MOVE_SERIAL_VEN,
	ACPI_RSC_MOVE8,
	ACPI_RSC_MOVE16,
	ACPI_RSC_MOVE32,
	ACPI_RSC_MOVE64,
	ACPI_RSC_SET8,
	ACPI_RSC_SOURCE,
	ACPI_RSC_SOURCEX
पूर्ण ACPI_RSCONVERT_OPCODES;

/* Resource Conversion sub-opcodes */

#घोषणा ACPI_RSC_COMPARE_AML_LENGTH     0
#घोषणा ACPI_RSC_COMPARE_VALUE          1

#घोषणा ACPI_RSC_TABLE_SIZE(d)          (माप (d) / माप (काष्ठा acpi_rsconvert_info))

#घोषणा ACPI_RS_OFFSET(f)               (u8) ACPI_OFFSET (काष्ठा acpi_resource,f)
#घोषणा AML_OFFSET(f)                   (u8) ACPI_OFFSET (जोड़ aml_resource,f)

/*
 * Inभागidual entry क्रम the resource dump tables
 */
प्रकार स्थिर काष्ठा acpi_rsdump_info अणु
	u8 opcode;
	u8 offset;
	स्थिर अक्षर *name;
	स्थिर अक्षर **poपूर्णांकer;

पूर्ण acpi_rsdump_info;

/* Values क्रम the Opcode field above */

प्रकार क्रमागत अणु
	ACPI_RSD_TITLE = 0,
	ACPI_RSD_1BITFLAG,
	ACPI_RSD_2BITFLAG,
	ACPI_RSD_3BITFLAG,
	ACPI_RSD_6BITFLAG,
	ACPI_RSD_ADDRESS,
	ACPI_RSD_DWORDLIST,
	ACPI_RSD_LITERAL,
	ACPI_RSD_LONGLIST,
	ACPI_RSD_SHORTLIST,
	ACPI_RSD_SHORTLISTX,
	ACPI_RSD_SOURCE,
	ACPI_RSD_STRING,
	ACPI_RSD_UINT8,
	ACPI_RSD_UINT16,
	ACPI_RSD_UINT32,
	ACPI_RSD_UINT64,
	ACPI_RSD_WORDLIST,
	ACPI_RSD_LABEL,
	ACPI_RSD_SOURCE_LABEL,

पूर्ण ACPI_RSDUMP_OPCODES;

/* restore शेष alignment */

#आशय pack()

/* Resource tables indexed by पूर्णांकernal resource type */

बाह्य स्थिर u8 acpi_gbl_aml_resource_sizes[];
बाह्य स्थिर u8 acpi_gbl_aml_resource_serial_bus_sizes[];
बाह्य काष्ठा acpi_rsconvert_info *acpi_gbl_set_resource_dispatch[];

/* Resource tables indexed by raw AML resource descriptor type */

बाह्य स्थिर u8 acpi_gbl_resource_काष्ठा_sizes[];
बाह्य स्थिर u8 acpi_gbl_resource_काष्ठा_serial_bus_sizes[];
बाह्य काष्ठा acpi_rsconvert_info *acpi_gbl_get_resource_dispatch[];

बाह्य काष्ठा acpi_rsconvert_info
    *acpi_gbl_convert_resource_serial_bus_dispatch[];

काष्ठा acpi_venकरोr_walk_info अणु
	काष्ठा acpi_venकरोr_uuid *uuid;
	काष्ठा acpi_buffer *buffer;
	acpi_status status;
पूर्ण;

/*
 * rscreate
 */
acpi_status
acpi_rs_create_resource_list(जोड़ acpi_opeअक्रम_object *aml_buffer,
			     काष्ठा acpi_buffer *output_buffer);

acpi_status
acpi_rs_create_aml_resources(काष्ठा acpi_buffer *resource_list,
			     काष्ठा acpi_buffer *output_buffer);

acpi_status
acpi_rs_create_pci_routing_table(जोड़ acpi_opeअक्रम_object *package_object,
				 काष्ठा acpi_buffer *output_buffer);

/*
 * rsutils
 */

acpi_status
acpi_rs_get_prt_method_data(काष्ठा acpi_namespace_node *node,
			    काष्ठा acpi_buffer *ret_buffer);

acpi_status
acpi_rs_get_crs_method_data(काष्ठा acpi_namespace_node *node,
			    काष्ठा acpi_buffer *ret_buffer);

acpi_status
acpi_rs_get_prs_method_data(काष्ठा acpi_namespace_node *node,
			    काष्ठा acpi_buffer *ret_buffer);

acpi_status
acpi_rs_get_method_data(acpi_handle handle,
			स्थिर अक्षर *path, काष्ठा acpi_buffer *ret_buffer);

acpi_status
acpi_rs_set_srs_method_data(काष्ठा acpi_namespace_node *node,
			    काष्ठा acpi_buffer *ret_buffer);

acpi_status
acpi_rs_get_aei_method_data(काष्ठा acpi_namespace_node *node,
			    काष्ठा acpi_buffer *ret_buffer);

/*
 * rscalc
 */
acpi_status
acpi_rs_get_list_length(u8 *aml_buffer,
			u32 aml_buffer_length, acpi_size *size_needed);

acpi_status
acpi_rs_get_aml_length(काष्ठा acpi_resource *resource_list,
		       acpi_size resource_list_size, acpi_size *size_needed);

acpi_status
acpi_rs_get_pci_routing_table_length(जोड़ acpi_opeअक्रम_object *package_object,
				     acpi_size *buffer_size_needed);

acpi_status
acpi_rs_convert_aml_to_resources(u8 * aml,
				 u32 length,
				 u32 offset, u8 resource_index, व्योम **context);

acpi_status
acpi_rs_convert_resources_to_aml(काष्ठा acpi_resource *resource,
				 acpi_size aml_size_needed, u8 * output_buffer);

/*
 * rsaddr
 */
व्योम
acpi_rs_set_address_common(जोड़ aml_resource *aml,
			   काष्ठा acpi_resource *resource);

u8
acpi_rs_get_address_common(काष्ठा acpi_resource *resource,
			   जोड़ aml_resource *aml);

/*
 * rsmisc
 */
acpi_status
acpi_rs_convert_aml_to_resource(काष्ठा acpi_resource *resource,
				जोड़ aml_resource *aml,
				काष्ठा acpi_rsconvert_info *info);

acpi_status
acpi_rs_convert_resource_to_aml(काष्ठा acpi_resource *resource,
				जोड़ aml_resource *aml,
				काष्ठा acpi_rsconvert_info *info);

/*
 * rsutils
 */
व्योम
acpi_rs_move_data(व्योम *destination,
		  व्योम *source, u16 item_count, u8 move_type);

u8 acpi_rs_decode_biपंचांगask(u16 mask, u8 * list);

u16 acpi_rs_encode_biपंचांगask(u8 * list, u8 count);

acpi_rs_length
acpi_rs_get_resource_source(acpi_rs_length resource_length,
			    acpi_rs_length minimum_length,
			    काष्ठा acpi_resource_source *resource_source,
			    जोड़ aml_resource *aml, अक्षर *string_ptr);

acpi_rsdesc_size
acpi_rs_set_resource_source(जोड़ aml_resource *aml,
			    acpi_rs_length minimum_length,
			    काष्ठा acpi_resource_source *resource_source);

व्योम
acpi_rs_set_resource_header(u8 descriptor_type,
			    acpi_rsdesc_size total_length,
			    जोड़ aml_resource *aml);

व्योम
acpi_rs_set_resource_length(acpi_rsdesc_size total_length,
			    जोड़ aml_resource *aml);

/*
 * rsdump - Debugger support
 */
#अगर_घोषित ACPI_DEBUGGER
व्योम acpi_rs_dump_resource_list(काष्ठा acpi_resource *resource);

व्योम acpi_rs_dump_irq_list(u8 *route_table);
#पूर्ण_अगर

/*
 * Resource conversion tables
 */
बाह्य काष्ठा acpi_rsconvert_info acpi_rs_convert_dma[];
बाह्य काष्ठा acpi_rsconvert_info acpi_rs_convert_end_dpf[];
बाह्य काष्ठा acpi_rsconvert_info acpi_rs_convert_io[];
बाह्य काष्ठा acpi_rsconvert_info acpi_rs_convert_fixed_io[];
बाह्य काष्ठा acpi_rsconvert_info acpi_rs_convert_end_tag[];
बाह्य काष्ठा acpi_rsconvert_info acpi_rs_convert_memory24[];
बाह्य काष्ठा acpi_rsconvert_info acpi_rs_convert_generic_reg[];
बाह्य काष्ठा acpi_rsconvert_info acpi_rs_convert_memory32[];
बाह्य काष्ठा acpi_rsconvert_info acpi_rs_convert_fixed_memory32[];
बाह्य काष्ठा acpi_rsconvert_info acpi_rs_convert_address32[];
बाह्य काष्ठा acpi_rsconvert_info acpi_rs_convert_address16[];
बाह्य काष्ठा acpi_rsconvert_info acpi_rs_convert_ext_irq[];
बाह्य काष्ठा acpi_rsconvert_info acpi_rs_convert_address64[];
बाह्य काष्ठा acpi_rsconvert_info acpi_rs_convert_ext_address64[];
बाह्य काष्ठा acpi_rsconvert_info acpi_rs_convert_gpio[];
बाह्य काष्ठा acpi_rsconvert_info acpi_rs_convert_fixed_dma[];
बाह्य काष्ठा acpi_rsconvert_info acpi_rs_convert_csi2_serial_bus[];
बाह्य काष्ठा acpi_rsconvert_info acpi_rs_convert_i2c_serial_bus[];
बाह्य काष्ठा acpi_rsconvert_info acpi_rs_convert_spi_serial_bus[];
बाह्य काष्ठा acpi_rsconvert_info acpi_rs_convert_uart_serial_bus[];
बाह्य काष्ठा acpi_rsconvert_info acpi_rs_convert_pin_function[];
बाह्य काष्ठा acpi_rsconvert_info acpi_rs_convert_pin_config[];
बाह्य काष्ठा acpi_rsconvert_info acpi_rs_convert_pin_group[];
बाह्य काष्ठा acpi_rsconvert_info acpi_rs_convert_pin_group_function[];
बाह्य काष्ठा acpi_rsconvert_info acpi_rs_convert_pin_group_config[];

/* These resources require separate get/set tables */

बाह्य काष्ठा acpi_rsconvert_info acpi_rs_get_irq[];
बाह्य काष्ठा acpi_rsconvert_info acpi_rs_get_start_dpf[];
बाह्य काष्ठा acpi_rsconvert_info acpi_rs_get_venकरोr_small[];
बाह्य काष्ठा acpi_rsconvert_info acpi_rs_get_venकरोr_large[];

बाह्य काष्ठा acpi_rsconvert_info acpi_rs_set_irq[];
बाह्य काष्ठा acpi_rsconvert_info acpi_rs_set_start_dpf[];
बाह्य काष्ठा acpi_rsconvert_info acpi_rs_set_venकरोr[];

#अगर defined(ACPI_DEBUG_OUTPUT) || defined(ACPI_DEBUGGER)
/*
 * rsinfo
 */
बाह्य काष्ठा acpi_rsdump_info *acpi_gbl_dump_resource_dispatch[];
बाह्य काष्ठा acpi_rsdump_info *acpi_gbl_dump_serial_bus_dispatch[];

/*
 * rsdumpinfo
 */
बाह्य काष्ठा acpi_rsdump_info acpi_rs_dump_irq[];
बाह्य काष्ठा acpi_rsdump_info acpi_rs_dump_prt[];
बाह्य काष्ठा acpi_rsdump_info acpi_rs_dump_dma[];
बाह्य काष्ठा acpi_rsdump_info acpi_rs_dump_start_dpf[];
बाह्य काष्ठा acpi_rsdump_info acpi_rs_dump_end_dpf[];
बाह्य काष्ठा acpi_rsdump_info acpi_rs_dump_io[];
बाह्य काष्ठा acpi_rsdump_info acpi_rs_dump_io_flags[];
बाह्य काष्ठा acpi_rsdump_info acpi_rs_dump_fixed_io[];
बाह्य काष्ठा acpi_rsdump_info acpi_rs_dump_venकरोr[];
बाह्य काष्ठा acpi_rsdump_info acpi_rs_dump_end_tag[];
बाह्य काष्ठा acpi_rsdump_info acpi_rs_dump_memory24[];
बाह्य काष्ठा acpi_rsdump_info acpi_rs_dump_memory32[];
बाह्य काष्ठा acpi_rsdump_info acpi_rs_dump_memory_flags[];
बाह्य काष्ठा acpi_rsdump_info acpi_rs_dump_fixed_memory32[];
बाह्य काष्ठा acpi_rsdump_info acpi_rs_dump_address16[];
बाह्य काष्ठा acpi_rsdump_info acpi_rs_dump_address32[];
बाह्य काष्ठा acpi_rsdump_info acpi_rs_dump_address64[];
बाह्य काष्ठा acpi_rsdump_info acpi_rs_dump_ext_address64[];
बाह्य काष्ठा acpi_rsdump_info acpi_rs_dump_ext_irq[];
बाह्य काष्ठा acpi_rsdump_info acpi_rs_dump_generic_reg[];
बाह्य काष्ठा acpi_rsdump_info acpi_rs_dump_gpio[];
बाह्य काष्ठा acpi_rsdump_info acpi_rs_dump_pin_function[];
बाह्य काष्ठा acpi_rsdump_info acpi_rs_dump_fixed_dma[];
बाह्य काष्ठा acpi_rsdump_info acpi_rs_dump_common_serial_bus[];
बाह्य काष्ठा acpi_rsdump_info acpi_rs_dump_csi2_serial_bus[];
बाह्य काष्ठा acpi_rsdump_info acpi_rs_dump_i2c_serial_bus[];
बाह्य काष्ठा acpi_rsdump_info acpi_rs_dump_spi_serial_bus[];
बाह्य काष्ठा acpi_rsdump_info acpi_rs_dump_uart_serial_bus[];
बाह्य काष्ठा acpi_rsdump_info acpi_rs_dump_general_flags[];
बाह्य काष्ठा acpi_rsdump_info acpi_rs_dump_pin_config[];
बाह्य काष्ठा acpi_rsdump_info acpi_rs_dump_pin_group[];
बाह्य काष्ठा acpi_rsdump_info acpi_rs_dump_pin_group_function[];
बाह्य काष्ठा acpi_rsdump_info acpi_rs_dump_pin_group_config[];
#पूर्ण_अगर

#पूर्ण_अगर				/* __ACRESRC_H__ */
