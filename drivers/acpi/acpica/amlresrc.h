<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/******************************************************************************
 *
 * Module Name: amlresrc.h - AML resource descriptors
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

/* acpisrc:काष्ठा_defs -- क्रम acpisrc conversion */

#अगर_अघोषित __AMLRESRC_H
#घोषणा __AMLRESRC_H

/*
 * Resource descriptor tags, as defined in the ACPI specअगरication.
 * Used to symbolically reference fields within a descriptor.
 */
#घोषणा ACPI_RESTAG_ADDRESS                     "_ADR"
#घोषणा ACPI_RESTAG_ALIGNMENT                   "_ALN"
#घोषणा ACPI_RESTAG_ADDRESSSPACE                "_ASI"
#घोषणा ACPI_RESTAG_ACCESSSIZE                  "_ASZ"
#घोषणा ACPI_RESTAG_TYPESPECIFICATTRIBUTES      "_ATT"
#घोषणा ACPI_RESTAG_BASEADDRESS                 "_BAS"
#घोषणा ACPI_RESTAG_BUSMASTER                   "_BM_"	/* Master(1), Slave(0) */
#घोषणा ACPI_RESTAG_DEBOUNCETIME                "_DBT"
#घोषणा ACPI_RESTAG_DECODE                      "_DEC"
#घोषणा ACPI_RESTAG_DEVICEPOLARITY              "_DPL"
#घोषणा ACPI_RESTAG_DMA                         "_DMA"
#घोषणा ACPI_RESTAG_DMATYPE                     "_TYP"	/* Compatible(0), A(1), B(2), F(3) */
#घोषणा ACPI_RESTAG_DRIVESTRENGTH               "_DRS"
#घोषणा ACPI_RESTAG_ENDIANNESS                  "_END"
#घोषणा ACPI_RESTAG_FLOWCONTROL                 "_FLC"
#घोषणा ACPI_RESTAG_FUNCTION                    "_FUN"
#घोषणा ACPI_RESTAG_GRANULARITY                 "_GRA"
#घोषणा ACPI_RESTAG_INTERRUPT                   "_INT"
#घोषणा ACPI_RESTAG_INTERRUPTLEVEL              "_LL_"	/* active_lo(1), active_hi(0) */
#घोषणा ACPI_RESTAG_INTERRUPTSHARE              "_SHR"	/* Shareable(1), no_share(0) */
#घोषणा ACPI_RESTAG_INTERRUPTTYPE               "_HE_"	/* Edge(1), Level(0) */
#घोषणा ACPI_RESTAG_IORESTRICTION               "_IOR"
#घोषणा ACPI_RESTAG_LENGTH                      "_LEN"
#घोषणा ACPI_RESTAG_LINE                        "_LIN"
#घोषणा ACPI_RESTAG_LOCALPORT                   "_PRT"
#घोषणा ACPI_RESTAG_MEMATTRIBUTES               "_MTP"	/* Memory(0), Reserved(1), ACPI(2), NVS(3) */
#घोषणा ACPI_RESTAG_MEMTYPE                     "_MEM"	/* non_cache(0), Cacheable(1) Cache+combine(2), Cache+prefetch(3) */
#घोषणा ACPI_RESTAG_MAXADDR                     "_MAX"
#घोषणा ACPI_RESTAG_MINADDR                     "_MIN"
#घोषणा ACPI_RESTAG_MAXTYPE                     "_MAF"
#घोषणा ACPI_RESTAG_MINTYPE                     "_MIF"
#घोषणा ACPI_RESTAG_MODE                        "_MOD"
#घोषणा ACPI_RESTAG_PARITY                      "_PAR"
#घोषणा ACPI_RESTAG_PHASE                       "_PHA"
#घोषणा ACPI_RESTAG_PHYTYPE                     "_PHY"
#घोषणा ACPI_RESTAG_PIN                         "_PIN"
#घोषणा ACPI_RESTAG_PINCONFIG                   "_PPI"
#घोषणा ACPI_RESTAG_PINCONFIG_TYPE              "_TYP"
#घोषणा ACPI_RESTAG_PINCONFIG_VALUE             "_VAL"
#घोषणा ACPI_RESTAG_POLARITY                    "_POL"
#घोषणा ACPI_RESTAG_REGISTERBITOFFSET           "_RBO"
#घोषणा ACPI_RESTAG_REGISTERBITWIDTH            "_RBW"
#घोषणा ACPI_RESTAG_RANGETYPE                   "_RNG"
#घोषणा ACPI_RESTAG_READWRITETYPE               "_RW_"	/* पढ़ो_only(0), Writeable (1) */
#घोषणा ACPI_RESTAG_LENGTH_RX                   "_RXL"
#घोषणा ACPI_RESTAG_LENGTH_TX                   "_TXL"
#घोषणा ACPI_RESTAG_SLAVEMODE                   "_SLV"
#घोषणा ACPI_RESTAG_SPEED                       "_SPE"
#घोषणा ACPI_RESTAG_STOPBITS                    "_STB"
#घोषणा ACPI_RESTAG_TRANSLATION                 "_TRA"
#घोषणा ACPI_RESTAG_TRANSTYPE                   "_TRS"	/* Sparse(1), Dense(0) */
#घोषणा ACPI_RESTAG_TYPE                        "_TTP"	/* Translation(1), Static (0) */
#घोषणा ACPI_RESTAG_XFERTYPE                    "_SIZ"	/* 8(0), 8And16(1), 16(2) */
#घोषणा ACPI_RESTAG_VENDORDATA                  "_VEN"

/* Default sizes क्रम "small" resource descriptors */

#घोषणा ASL_RDESC_IRQ_SIZE                      0x02
#घोषणा ASL_RDESC_DMA_SIZE                      0x02
#घोषणा ASL_RDESC_ST_DEPEND_SIZE                0x00
#घोषणा ASL_RDESC_END_DEPEND_SIZE               0x00
#घोषणा ASL_RDESC_IO_SIZE                       0x07
#घोषणा ASL_RDESC_FIXED_IO_SIZE                 0x03
#घोषणा ASL_RDESC_FIXED_DMA_SIZE                0x05
#घोषणा ASL_RDESC_END_TAG_SIZE                  0x01

काष्ठा asl_resource_node अणु
	u32 buffer_length;
	व्योम *buffer;
	काष्ठा asl_resource_node *next;
पूर्ण;

काष्ठा asl_resource_info अणु
	जोड़ acpi_parse_object *descriptor_type_op;	/* Resource descriptor parse node */
	जोड़ acpi_parse_object *mapping_op;	/* Used क्रम mapfile support */
	u32 current_byte_offset;	/* Offset in resource ढाँचा */
पूर्ण;

/* Macros used to generate AML resource length fields */

#घोषणा ACPI_AML_SIZE_LARGE(r)      (माप (r) - माप (काष्ठा aml_resource_large_header))
#घोषणा ACPI_AML_SIZE_SMALL(r)      (माप (r) - माप (काष्ठा aml_resource_small_header))

/*
 * Resource descriptors defined in the ACPI specअगरication.
 *
 * Packing/alignment must be BYTE because these descriptors
 * are used to overlay the raw AML byte stream.
 */
#आशय pack(1)

/*
 * SMALL descriptors
 */
#घोषणा AML_RESOURCE_SMALL_HEADER_COMMON \
	u8                              descriptor_type;

काष्ठा aml_resource_small_header अणु
AML_RESOURCE_SMALL_HEADER_COMMONपूर्ण;

काष्ठा aml_resource_irq अणु
	AML_RESOURCE_SMALL_HEADER_COMMON u16 irq_mask;
	u8 flags;
पूर्ण;

काष्ठा aml_resource_irq_noflags अणु
	AML_RESOURCE_SMALL_HEADER_COMMON u16 irq_mask;
पूर्ण;

काष्ठा aml_resource_dma अणु
	AML_RESOURCE_SMALL_HEADER_COMMON u8 dma_channel_mask;
	u8 flags;
पूर्ण;

काष्ठा aml_resource_start_dependent अणु
	AML_RESOURCE_SMALL_HEADER_COMMON u8 flags;
पूर्ण;

काष्ठा aml_resource_start_dependent_noprio अणु
AML_RESOURCE_SMALL_HEADER_COMMONपूर्ण;

काष्ठा aml_resource_end_dependent अणु
AML_RESOURCE_SMALL_HEADER_COMMONपूर्ण;

काष्ठा aml_resource_io अणु
	AML_RESOURCE_SMALL_HEADER_COMMON u8 flags;
	u16 minimum;
	u16 maximum;
	u8 alignment;
	u8 address_length;
पूर्ण;

काष्ठा aml_resource_fixed_io अणु
	AML_RESOURCE_SMALL_HEADER_COMMON u16 address;
	u8 address_length;
पूर्ण;

काष्ठा aml_resource_venकरोr_small अणु
AML_RESOURCE_SMALL_HEADER_COMMONपूर्ण;

काष्ठा aml_resource_end_tag अणु
	AML_RESOURCE_SMALL_HEADER_COMMON u8 checksum;
पूर्ण;

काष्ठा aml_resource_fixed_dma अणु
	AML_RESOURCE_SMALL_HEADER_COMMON u16 request_lines;
	u16 channels;
	u8 width;
पूर्ण;

/*
 * LARGE descriptors
 */
#घोषणा AML_RESOURCE_LARGE_HEADER_COMMON \
	u8                              descriptor_type;\
	u16                             resource_length;

काष्ठा aml_resource_large_header अणु
AML_RESOURCE_LARGE_HEADER_COMMONपूर्ण;

/* General Flags क्रम address space resource descriptors */

#घोषणा ACPI_RESOURCE_FLAG_DEC      2
#घोषणा ACPI_RESOURCE_FLAG_MIF      4
#घोषणा ACPI_RESOURCE_FLAG_MAF      8

काष्ठा aml_resource_memory24 अणु
	AML_RESOURCE_LARGE_HEADER_COMMON u8 flags;
	u16 minimum;
	u16 maximum;
	u16 alignment;
	u16 address_length;
पूर्ण;

काष्ठा aml_resource_venकरोr_large अणु
AML_RESOURCE_LARGE_HEADER_COMMONपूर्ण;

काष्ठा aml_resource_memory32 अणु
	AML_RESOURCE_LARGE_HEADER_COMMON u8 flags;
	u32 minimum;
	u32 maximum;
	u32 alignment;
	u32 address_length;
पूर्ण;

काष्ठा aml_resource_fixed_memory32 अणु
	AML_RESOURCE_LARGE_HEADER_COMMON u8 flags;
	u32 address;
	u32 address_length;
पूर्ण;

#घोषणा AML_RESOURCE_ADDRESS_COMMON \
	u8                              resource_type; \
	u8                              flags; \
	u8                              specअगरic_flags;

काष्ठा aml_resource_address अणु
AML_RESOURCE_LARGE_HEADER_COMMON AML_RESOURCE_ADDRESS_COMMONपूर्ण;

काष्ठा aml_resource_extended_address64 अणु
	AML_RESOURCE_LARGE_HEADER_COMMON
	    AML_RESOURCE_ADDRESS_COMMON u8 revision_ID;
	u8 reserved;
	u64 granularity;
	u64 minimum;
	u64 maximum;
	u64 translation_offset;
	u64 address_length;
	u64 type_specअगरic;
पूर्ण;

#घोषणा AML_RESOURCE_EXTENDED_ADDRESS_REVISION          1	/* ACPI 3.0 */

काष्ठा aml_resource_address64 अणु
	AML_RESOURCE_LARGE_HEADER_COMMON
	    AML_RESOURCE_ADDRESS_COMMON u64 granularity;
	u64 minimum;
	u64 maximum;
	u64 translation_offset;
	u64 address_length;
पूर्ण;

काष्ठा aml_resource_address32 अणु
	AML_RESOURCE_LARGE_HEADER_COMMON
	    AML_RESOURCE_ADDRESS_COMMON u32 granularity;
	u32 minimum;
	u32 maximum;
	u32 translation_offset;
	u32 address_length;
पूर्ण;

काष्ठा aml_resource_address16 अणु
	AML_RESOURCE_LARGE_HEADER_COMMON
	    AML_RESOURCE_ADDRESS_COMMON u16 granularity;
	u16 minimum;
	u16 maximum;
	u16 translation_offset;
	u16 address_length;
पूर्ण;

काष्ठा aml_resource_extended_irq अणु
	AML_RESOURCE_LARGE_HEADER_COMMON u8 flags;
	u8 पूर्णांकerrupt_count;
	u32 पूर्णांकerrupts[1];
	/* res_source_index, res_source optional fields follow */
पूर्ण;

काष्ठा aml_resource_generic_रेजिस्टर अणु
	AML_RESOURCE_LARGE_HEADER_COMMON u8 address_space_id;
	u8 bit_width;
	u8 bit_offset;
	u8 access_size;		/* ACPI 3.0, was previously Reserved */
	u64 address;
पूर्ण;

/* Common descriptor क्रम gpio_पूर्णांक and gpio_io (ACPI 5.0) */

काष्ठा aml_resource_gpio अणु
	AML_RESOURCE_LARGE_HEADER_COMMON u8 revision_id;
	u8 connection_type;
	u16 flags;
	u16 पूर्णांक_flags;
	u8 pin_config;
	u16 drive_strength;
	u16 debounce_समयout;
	u16 pin_table_offset;
	u8 res_source_index;
	u16 res_source_offset;
	u16 venकरोr_offset;
	u16 venकरोr_length;
	/*
	 * Optional fields follow immediately:
	 * 1) PIN list (Words)
	 * 2) Resource Source String
	 * 3) Venकरोr Data bytes
	 */
पूर्ण;

#घोषणा AML_RESOURCE_GPIO_REVISION              1	/* ACPI 5.0 */

/* Values क्रम connection_type above */

#घोषणा AML_RESOURCE_GPIO_TYPE_INT              0
#घोषणा AML_RESOURCE_GPIO_TYPE_IO               1
#घोषणा AML_RESOURCE_MAX_GPIOTYPE               1

/* Common preamble क्रम all serial descriptors (ACPI 5.0) */

#घोषणा AML_RESOURCE_SERIAL_COMMON \
	u8                              revision_id; \
	u8                              res_source_index; \
	u8                              type; \
	u8                              flags; \
	u16                             type_specअगरic_flags; \
	u8                              type_revision_id; \
	u16                             type_data_length; \

/* Values क्रम the type field above */

#घोषणा AML_RESOURCE_I2C_SERIALBUSTYPE          1
#घोषणा AML_RESOURCE_SPI_SERIALBUSTYPE          2
#घोषणा AML_RESOURCE_UART_SERIALBUSTYPE         3
#घोषणा AML_RESOURCE_CSI2_SERIALBUSTYPE         4
#घोषणा AML_RESOURCE_MAX_SERIALBUSTYPE          4
#घोषणा AML_RESOURCE_VENDOR_SERIALBUSTYPE       192	/* Venकरोr defined is 0xC0-0xFF (NOT SUPPORTED) */

काष्ठा aml_resource_common_serialbus अणु
AML_RESOURCE_LARGE_HEADER_COMMON AML_RESOURCE_SERIAL_COMMONपूर्ण;

काष्ठा aml_resource_csi2_serialbus अणु
	AML_RESOURCE_LARGE_HEADER_COMMON AML_RESOURCE_SERIAL_COMMON
	    /*
	     * Optional fields follow immediately:
	     * 1) Venकरोr Data bytes
	     * 2) Resource Source String
	     */
पूर्ण;

#घोषणा AML_RESOURCE_CSI2_REVISION              1	/* ACPI 6.4 */
#घोषणा AML_RESOURCE_CSI2_TYPE_REVISION         1	/* ACPI 6.4 */
#घोषणा AML_RESOURCE_CSI2_MIN_DATA_LEN          0	/* ACPI 6.4 */

काष्ठा aml_resource_i2c_serialbus अणु
	AML_RESOURCE_LARGE_HEADER_COMMON
	    AML_RESOURCE_SERIAL_COMMON u32 connection_speed;
	u16 slave_address;
	/*
	 * Optional fields follow immediately:
	 * 1) Venकरोr Data bytes
	 * 2) Resource Source String
	 */
पूर्ण;

#घोषणा AML_RESOURCE_I2C_REVISION               1	/* ACPI 5.0 */
#घोषणा AML_RESOURCE_I2C_TYPE_REVISION          1	/* ACPI 5.0 */
#घोषणा AML_RESOURCE_I2C_MIN_DATA_LEN           6

काष्ठा aml_resource_spi_serialbus अणु
	AML_RESOURCE_LARGE_HEADER_COMMON
	    AML_RESOURCE_SERIAL_COMMON u32 connection_speed;
	u8 data_bit_length;
	u8 घड़ी_phase;
	u8 घड़ी_polarity;
	u16 device_selection;
	/*
	 * Optional fields follow immediately:
	 * 1) Venकरोr Data bytes
	 * 2) Resource Source String
	 */
पूर्ण;

#घोषणा AML_RESOURCE_SPI_REVISION               1	/* ACPI 5.0 */
#घोषणा AML_RESOURCE_SPI_TYPE_REVISION          1	/* ACPI 5.0 */
#घोषणा AML_RESOURCE_SPI_MIN_DATA_LEN           9

काष्ठा aml_resource_uart_serialbus अणु
	AML_RESOURCE_LARGE_HEADER_COMMON
	    AML_RESOURCE_SERIAL_COMMON u32 शेष_baud_rate;
	u16 rx_fअगरo_size;
	u16 tx_fअगरo_size;
	u8 parity;
	u8 lines_enabled;
	/*
	 * Optional fields follow immediately:
	 * 1) Venकरोr Data bytes
	 * 2) Resource Source String
	 */
पूर्ण;

#घोषणा AML_RESOURCE_UART_REVISION              1	/* ACPI 5.0 */
#घोषणा AML_RESOURCE_UART_TYPE_REVISION         1	/* ACPI 5.0 */
#घोषणा AML_RESOURCE_UART_MIN_DATA_LEN          10

काष्ठा aml_resource_pin_function अणु
	AML_RESOURCE_LARGE_HEADER_COMMON u8 revision_id;
	u16 flags;
	u8 pin_config;
	u16 function_number;
	u16 pin_table_offset;
	u8 res_source_index;
	u16 res_source_offset;
	u16 venकरोr_offset;
	u16 venकरोr_length;
	/*
	 * Optional fields follow immediately:
	 * 1) PIN list (Words)
	 * 2) Resource Source String
	 * 3) Venकरोr Data bytes
	 */
पूर्ण;

#घोषणा AML_RESOURCE_PIN_FUNCTION_REVISION      1	/* ACPI 6.2 */

काष्ठा aml_resource_pin_config अणु
	AML_RESOURCE_LARGE_HEADER_COMMON u8 revision_id;
	u16 flags;
	u8 pin_config_type;
	u32 pin_config_value;
	u16 pin_table_offset;
	u8 res_source_index;
	u16 res_source_offset;
	u16 venकरोr_offset;
	u16 venकरोr_length;
	/*
	 * Optional fields follow immediately:
	 * 1) PIN list (Words)
	 * 2) Resource Source String
	 * 3) Venकरोr Data bytes
	 */
पूर्ण;

#घोषणा AML_RESOURCE_PIN_CONFIG_REVISION      1	/* ACPI 6.2 */

काष्ठा aml_resource_pin_group अणु
	AML_RESOURCE_LARGE_HEADER_COMMON u8 revision_id;
	u16 flags;
	u16 pin_table_offset;
	u16 label_offset;
	u16 venकरोr_offset;
	u16 venकरोr_length;
	/*
	 * Optional fields follow immediately:
	 * 1) PIN list (Words)
	 * 2) Resource Label String
	 * 3) Venकरोr Data bytes
	 */
पूर्ण;

#घोषणा AML_RESOURCE_PIN_GROUP_REVISION      1	/* ACPI 6.2 */

काष्ठा aml_resource_pin_group_function अणु
	AML_RESOURCE_LARGE_HEADER_COMMON u8 revision_id;
	u16 flags;
	u16 function_number;
	u8 res_source_index;
	u16 res_source_offset;
	u16 res_source_label_offset;
	u16 venकरोr_offset;
	u16 venकरोr_length;
	/*
	 * Optional fields follow immediately:
	 * 1) Resource Source String
	 * 2) Resource Source Label String
	 * 3) Venकरोr Data bytes
	 */
पूर्ण;

#घोषणा AML_RESOURCE_PIN_GROUP_FUNCTION_REVISION    1	/* ACPI 6.2 */

काष्ठा aml_resource_pin_group_config अणु
	AML_RESOURCE_LARGE_HEADER_COMMON u8 revision_id;
	u16 flags;
	u8 pin_config_type;
	u32 pin_config_value;
	u8 res_source_index;
	u16 res_source_offset;
	u16 res_source_label_offset;
	u16 venकरोr_offset;
	u16 venकरोr_length;
	/*
	 * Optional fields follow immediately:
	 * 1) Resource Source String
	 * 2) Resource Source Label String
	 * 3) Venकरोr Data bytes
	 */
पूर्ण;

#घोषणा AML_RESOURCE_PIN_GROUP_CONFIG_REVISION    1	/* ACPI 6.2 */

/* restore शेष alignment */

#आशय pack()

/* Union of all resource descriptors, so we can allocate the worst हाल */

जोड़ aml_resource अणु
	/* Descriptor headers */

	u8 descriptor_type;
	काष्ठा aml_resource_small_header small_header;
	काष्ठा aml_resource_large_header large_header;

	/* Small resource descriptors */

	काष्ठा aml_resource_irq irq;
	काष्ठा aml_resource_dma dma;
	काष्ठा aml_resource_start_dependent start_dpf;
	काष्ठा aml_resource_end_dependent end_dpf;
	काष्ठा aml_resource_io io;
	काष्ठा aml_resource_fixed_io fixed_io;
	काष्ठा aml_resource_fixed_dma fixed_dma;
	काष्ठा aml_resource_venकरोr_small venकरोr_small;
	काष्ठा aml_resource_end_tag end_tag;

	/* Large resource descriptors */

	काष्ठा aml_resource_memory24 memory24;
	काष्ठा aml_resource_generic_रेजिस्टर generic_reg;
	काष्ठा aml_resource_venकरोr_large venकरोr_large;
	काष्ठा aml_resource_memory32 memory32;
	काष्ठा aml_resource_fixed_memory32 fixed_memory32;
	काष्ठा aml_resource_address16 address16;
	काष्ठा aml_resource_address32 address32;
	काष्ठा aml_resource_address64 address64;
	काष्ठा aml_resource_extended_address64 ext_address64;
	काष्ठा aml_resource_extended_irq extended_irq;
	काष्ठा aml_resource_gpio gpio;
	काष्ठा aml_resource_i2c_serialbus i2c_serial_bus;
	काष्ठा aml_resource_spi_serialbus spi_serial_bus;
	काष्ठा aml_resource_uart_serialbus uart_serial_bus;
	काष्ठा aml_resource_csi2_serialbus csi2_serial_bus;
	काष्ठा aml_resource_common_serialbus common_serial_bus;
	काष्ठा aml_resource_pin_function pin_function;
	काष्ठा aml_resource_pin_config pin_config;
	काष्ठा aml_resource_pin_group pin_group;
	काष्ठा aml_resource_pin_group_function pin_group_function;
	काष्ठा aml_resource_pin_group_config pin_group_config;

	/* Utility overlays */

	काष्ठा aml_resource_address address;
	u32 dword_item;
	u16 word_item;
	u8 byte_item;
पूर्ण;

/* Interfaces used by both the disassembler and compiler */

व्योम
mp_save_gpio_info(जोड़ acpi_parse_object *op,
		  जोड़ aml_resource *resource,
		  u32 pin_count, u16 *pin_list, अक्षर *device_name);

व्योम
mp_save_serial_info(जोड़ acpi_parse_object *op,
		    जोड़ aml_resource *resource, अक्षर *device_name);

अक्षर *mp_get_hid_from_parse_tree(काष्ठा acpi_namespace_node *hid_node);

अक्षर *mp_get_hid_via_namestring(अक्षर *device_name);

अक्षर *mp_get_connection_info(जोड़ acpi_parse_object *op,
			     u32 pin_index,
			     काष्ठा acpi_namespace_node **target_node,
			     अक्षर **target_name);

अक्षर *mp_get_parent_device_hid(जोड़ acpi_parse_object *op,
			       काष्ठा acpi_namespace_node **target_node,
			       अक्षर **parent_device_name);

अक्षर *mp_get_ddn_value(अक्षर *device_name);

अक्षर *mp_get_hid_value(काष्ठा acpi_namespace_node *device_node);

#पूर्ण_अगर
