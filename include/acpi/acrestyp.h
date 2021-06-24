<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/******************************************************************************
 *
 * Name: acrestyp.h - Defines, types, and काष्ठाures क्रम resource descriptors
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#अगर_अघोषित __ACRESTYP_H__
#घोषणा __ACRESTYP_H__

/*
 * Definitions क्रम Resource Attributes
 */
प्रकार u16 acpi_rs_length;	/* Resource Length field is fixed at 16 bits */
प्रकार u32 acpi_rsdesc_size;	/* Max Resource Descriptor size is (Length+3) = (64K-1)+3 */

/*
 * Memory Attributes
 */
#घोषणा ACPI_READ_ONLY_MEMORY           (u8) 0x00
#घोषणा ACPI_READ_WRITE_MEMORY          (u8) 0x01

#घोषणा ACPI_NON_CACHEABLE_MEMORY       (u8) 0x00
#घोषणा ACPI_CACHABLE_MEMORY            (u8) 0x01
#घोषणा ACPI_WRITE_COMBINING_MEMORY     (u8) 0x02
#घोषणा ACPI_PREFETCHABLE_MEMORY        (u8) 0x03

/*! [Begin] no source code translation */
/*
 * IO Attributes
 * The ISA IO ranges are:     n000-n0FFh,  n400-n4FFh, n800-n8FFh, nC00-nCFFh.
 * The non-ISA IO ranges are: n100-n3FFh,  n500-n7FFh, n900-nBFFh, nCD0-nFFFh.
 */
/*! [End] no source code translation !*/

#घोषणा ACPI_NON_ISA_ONLY_RANGES        (u8) 0x01
#घोषणा ACPI_ISA_ONLY_RANGES            (u8) 0x02
#घोषणा ACPI_ENTIRE_RANGE               (ACPI_NON_ISA_ONLY_RANGES | ACPI_ISA_ONLY_RANGES)

/* Type of translation - 1=Sparse, 0=Dense */

#घोषणा ACPI_SPARSE_TRANSLATION         (u8) 0x01

/*
 * IO Port Descriptor Decode
 */
#घोषणा ACPI_DECODE_10                  (u8) 0x00	/* 10-bit IO address decode */
#घोषणा ACPI_DECODE_16                  (u8) 0x01	/* 16-bit IO address decode */

/*
 * Interrupt attributes - used in multiple descriptors
 */

/* Triggering */

#घोषणा ACPI_LEVEL_SENSITIVE            (u8) 0x00
#घोषणा ACPI_EDGE_SENSITIVE             (u8) 0x01

/* Polarity */

#घोषणा ACPI_ACTIVE_HIGH                (u8) 0x00
#घोषणा ACPI_ACTIVE_LOW                 (u8) 0x01
#घोषणा ACPI_ACTIVE_BOTH                (u8) 0x02

/* Sharing */

#घोषणा ACPI_EXCLUSIVE                  (u8) 0x00
#घोषणा ACPI_SHARED                     (u8) 0x01

/* Wake */

#घोषणा ACPI_NOT_WAKE_CAPABLE           (u8) 0x00
#घोषणा ACPI_WAKE_CAPABLE               (u8) 0x01

/*
 * DMA Attributes
 */
#घोषणा ACPI_COMPATIBILITY              (u8) 0x00
#घोषणा ACPI_TYPE_A                     (u8) 0x01
#घोषणा ACPI_TYPE_B                     (u8) 0x02
#घोषणा ACPI_TYPE_F                     (u8) 0x03

#घोषणा ACPI_NOT_BUS_MASTER             (u8) 0x00
#घोषणा ACPI_BUS_MASTER                 (u8) 0x01

#घोषणा ACPI_TRANSFER_8                 (u8) 0x00
#घोषणा ACPI_TRANSFER_8_16              (u8) 0x01
#घोषणा ACPI_TRANSFER_16                (u8) 0x02

/*
 * Start Dependent Functions Priority definitions
 */
#घोषणा ACPI_GOOD_CONFIGURATION         (u8) 0x00
#घोषणा ACPI_ACCEPTABLE_CONFIGURATION   (u8) 0x01
#घोषणा ACPI_SUB_OPTIMAL_CONFIGURATION  (u8) 0x02

/*
 * 16, 32 and 64-bit Address Descriptor resource types
 */
#घोषणा ACPI_MEMORY_RANGE               (u8) 0x00
#घोषणा ACPI_IO_RANGE                   (u8) 0x01
#घोषणा ACPI_BUS_NUMBER_RANGE           (u8) 0x02

#घोषणा ACPI_ADDRESS_NOT_FIXED          (u8) 0x00
#घोषणा ACPI_ADDRESS_FIXED              (u8) 0x01

#घोषणा ACPI_POS_DECODE                 (u8) 0x00
#घोषणा ACPI_SUB_DECODE                 (u8) 0x01

/* Producer/Consumer */

#घोषणा ACPI_PRODUCER                   (u8) 0x00
#घोषणा ACPI_CONSUMER                   (u8) 0x01

/*
 * If possible, pack the following काष्ठाures to byte alignment
 */
#अगर_अघोषित ACPI_MISALIGNMENT_NOT_SUPPORTED
#आशय pack(1)
#पूर्ण_अगर

/* UUID data काष्ठाures क्रम use in venकरोr-defined resource descriptors */

काष्ठा acpi_uuid अणु
	u8 data[ACPI_UUID_LENGTH];
पूर्ण;

काष्ठा acpi_venकरोr_uuid अणु
	u8 subtype;
	u8 data[ACPI_UUID_LENGTH];
पूर्ण;

/*
 * Structures used to describe device resources
 */
काष्ठा acpi_resource_irq अणु
	u8 descriptor_length;
	u8 triggering;
	u8 polarity;
	u8 shareable;
	u8 wake_capable;
	u8 पूर्णांकerrupt_count;
	u8 पूर्णांकerrupts[1];
पूर्ण;

काष्ठा acpi_resource_dma अणु
	u8 type;
	u8 bus_master;
	u8 transfer;
	u8 channel_count;
	u8 channels[1];
पूर्ण;

काष्ठा acpi_resource_start_dependent अणु
	u8 descriptor_length;
	u8 compatibility_priority;
	u8 perक्रमmance_robustness;
पूर्ण;

/*
 * The END_DEPENDENT_FUNCTIONS_RESOURCE काष्ठा is not
 * needed because it has no fields
 */

काष्ठा acpi_resource_io अणु
	u8 io_decode;
	u8 alignment;
	u8 address_length;
	u16 minimum;
	u16 maximum;
पूर्ण;

काष्ठा acpi_resource_fixed_io अणु
	u16 address;
	u8 address_length;
पूर्ण;

काष्ठा acpi_resource_fixed_dma अणु
	u16 request_lines;
	u16 channels;
	u8 width;
पूर्ण;

/* Values क्रम Width field above */

#घोषणा ACPI_DMA_WIDTH8                         0
#घोषणा ACPI_DMA_WIDTH16                        1
#घोषणा ACPI_DMA_WIDTH32                        2
#घोषणा ACPI_DMA_WIDTH64                        3
#घोषणा ACPI_DMA_WIDTH128                       4
#घोषणा ACPI_DMA_WIDTH256                       5

काष्ठा acpi_resource_venकरोr अणु
	u16 byte_length;
	u8 byte_data[1];
पूर्ण;

/* Venकरोr resource with UUID info (पूर्णांकroduced in ACPI 3.0) */

काष्ठा acpi_resource_venकरोr_typed अणु
	u16 byte_length;
	u8 uuid_subtype;
	u8 uuid[ACPI_UUID_LENGTH];
	u8 byte_data[1];
पूर्ण;

काष्ठा acpi_resource_end_tag अणु
	u8 checksum;
पूर्ण;

काष्ठा acpi_resource_memory24 अणु
	u8 ग_लिखो_protect;
	u16 minimum;
	u16 maximum;
	u16 alignment;
	u16 address_length;
पूर्ण;

काष्ठा acpi_resource_memory32 अणु
	u8 ग_लिखो_protect;
	u32 minimum;
	u32 maximum;
	u32 alignment;
	u32 address_length;
पूर्ण;

काष्ठा acpi_resource_fixed_memory32 अणु
	u8 ग_लिखो_protect;
	u32 address;
	u32 address_length;
पूर्ण;

काष्ठा acpi_memory_attribute अणु
	u8 ग_लिखो_protect;
	u8 caching;
	u8 range_type;
	u8 translation;
पूर्ण;

काष्ठा acpi_io_attribute अणु
	u8 range_type;
	u8 translation;
	u8 translation_type;
	u8 reserved1;
पूर्ण;

जोड़ acpi_resource_attribute अणु
	काष्ठा acpi_memory_attribute mem;
	काष्ठा acpi_io_attribute io;

	/* Used क्रम the *word_space macros */

	u8 type_specअगरic;
पूर्ण;

काष्ठा acpi_resource_label अणु
	u16 string_length;
	अक्षर *string_ptr;
पूर्ण;

काष्ठा acpi_resource_source अणु
	u8 index;
	u16 string_length;
	अक्षर *string_ptr;
पूर्ण;

/* Fields common to all address descriptors, 16/32/64 bit */

#घोषणा ACPI_RESOURCE_ADDRESS_COMMON \
	u8                                      resource_type; \
	u8                                      producer_consumer; \
	u8                                      decode; \
	u8                                      min_address_fixed; \
	u8                                      max_address_fixed; \
	जोड़ acpi_resource_attribute           info;

काष्ठा acpi_address16_attribute अणु
	u16 granularity;
	u16 minimum;
	u16 maximum;
	u16 translation_offset;
	u16 address_length;
पूर्ण;

काष्ठा acpi_address32_attribute अणु
	u32 granularity;
	u32 minimum;
	u32 maximum;
	u32 translation_offset;
	u32 address_length;
पूर्ण;

काष्ठा acpi_address64_attribute अणु
	u64 granularity;
	u64 minimum;
	u64 maximum;
	u64 translation_offset;
	u64 address_length;
पूर्ण;

काष्ठा acpi_resource_address अणु
ACPI_RESOURCE_ADDRESS_COMMONपूर्ण;

काष्ठा acpi_resource_address16 अणु
	ACPI_RESOURCE_ADDRESS_COMMON काष्ठा acpi_address16_attribute address;
	काष्ठा acpi_resource_source resource_source;
पूर्ण;

काष्ठा acpi_resource_address32 अणु
	ACPI_RESOURCE_ADDRESS_COMMON काष्ठा acpi_address32_attribute address;
	काष्ठा acpi_resource_source resource_source;
पूर्ण;

काष्ठा acpi_resource_address64 अणु
	ACPI_RESOURCE_ADDRESS_COMMON काष्ठा acpi_address64_attribute address;
	काष्ठा acpi_resource_source resource_source;
पूर्ण;

काष्ठा acpi_resource_extended_address64 अणु
	ACPI_RESOURCE_ADDRESS_COMMON u8 revision_ID;
	काष्ठा acpi_address64_attribute address;
	u64 type_specअगरic;
पूर्ण;

काष्ठा acpi_resource_extended_irq अणु
	u8 producer_consumer;
	u8 triggering;
	u8 polarity;
	u8 shareable;
	u8 wake_capable;
	u8 पूर्णांकerrupt_count;
	काष्ठा acpi_resource_source resource_source;
	u32 पूर्णांकerrupts[1];
पूर्ण;

काष्ठा acpi_resource_generic_रेजिस्टर अणु
	u8 space_id;
	u8 bit_width;
	u8 bit_offset;
	u8 access_size;
	u64 address;
पूर्ण;

काष्ठा acpi_resource_gpio अणु
	u8 revision_id;
	u8 connection_type;
	u8 producer_consumer;	/* For values, see Producer/Consumer above */
	u8 pin_config;
	u8 shareable;		/* For values, see Interrupt Attributes above */
	u8 wake_capable;	/* For values, see Interrupt Attributes above */
	u8 io_restriction;
	u8 triggering;		/* For values, see Interrupt Attributes above */
	u8 polarity;		/* For values, see Interrupt Attributes above */
	u16 drive_strength;
	u16 debounce_समयout;
	u16 pin_table_length;
	u16 venकरोr_length;
	काष्ठा acpi_resource_source resource_source;
	u16 *pin_table;
	u8 *venकरोr_data;
पूर्ण;

/* Values क्रम GPIO connection_type field above */

#घोषणा ACPI_RESOURCE_GPIO_TYPE_INT             0
#घोषणा ACPI_RESOURCE_GPIO_TYPE_IO              1

/* Values क्रम pin_config field above */

#घोषणा ACPI_PIN_CONFIG_DEFAULT                 0
#घोषणा ACPI_PIN_CONFIG_PULLUP                  1
#घोषणा ACPI_PIN_CONFIG_PULLDOWN                2
#घोषणा ACPI_PIN_CONFIG_NOPULL                  3

/* Values क्रम io_restriction field above */

#घोषणा ACPI_IO_RESTRICT_NONE                   0
#घोषणा ACPI_IO_RESTRICT_INPUT                  1
#घोषणा ACPI_IO_RESTRICT_OUTPUT                 2
#घोषणा ACPI_IO_RESTRICT_NONE_PRESERVE          3

/* Common काष्ठाure क्रम I2C, SPI, UART, CSI2 serial descriptors */

#घोषणा ACPI_RESOURCE_SERIAL_COMMON \
	u8                                      revision_id; \
	u8                                      type; \
	u8                                      producer_consumer;   /* For values, see Producer/Consumer above */\
	u8                                      slave_mode; \
	u8                                      connection_sharing; \
	u8                                      type_revision_id; \
	u16                                     type_data_length; \
	u16                                     venकरोr_length; \
	काष्ठा acpi_resource_source             resource_source; \
	u8                                      *venकरोr_data;

काष्ठा acpi_resource_common_serialbus अणु
ACPI_RESOURCE_SERIAL_COMMONपूर्ण;

/* Values क्रम the Type field above */

#घोषणा ACPI_RESOURCE_SERIAL_TYPE_I2C           1
#घोषणा ACPI_RESOURCE_SERIAL_TYPE_SPI           2
#घोषणा ACPI_RESOURCE_SERIAL_TYPE_UART          3
#घोषणा ACPI_RESOURCE_SERIAL_TYPE_CSI2          4

/* Values क्रम slave_mode field above */

#घोषणा ACPI_CONTROLLER_INITIATED               0
#घोषणा ACPI_DEVICE_INITIATED                   1

काष्ठा acpi_resource_i2c_serialbus अणु
	ACPI_RESOURCE_SERIAL_COMMON u8 access_mode;
	u16 slave_address;
	u32 connection_speed;
पूर्ण;

/* Values क्रम access_mode field above */

#घोषणा ACPI_I2C_7BIT_MODE                      0
#घोषणा ACPI_I2C_10BIT_MODE                     1

काष्ठा acpi_resource_spi_serialbus अणु
	ACPI_RESOURCE_SERIAL_COMMON u8 wire_mode;
	u8 device_polarity;
	u8 data_bit_length;
	u8 घड़ी_phase;
	u8 घड़ी_polarity;
	u16 device_selection;
	u32 connection_speed;
पूर्ण;

/* Values क्रम wire_mode field above */

#घोषणा ACPI_SPI_4WIRE_MODE                     0
#घोषणा ACPI_SPI_3WIRE_MODE                     1

/* Values क्रम device_polarity field above */

#घोषणा ACPI_SPI_ACTIVE_LOW                     0
#घोषणा ACPI_SPI_ACTIVE_HIGH                    1

/* Values क्रम घड़ी_phase field above */

#घोषणा ACPI_SPI_FIRST_PHASE                    0
#घोषणा ACPI_SPI_SECOND_PHASE                   1

/* Values क्रम घड़ी_polarity field above */

#घोषणा ACPI_SPI_START_LOW                      0
#घोषणा ACPI_SPI_START_HIGH                     1

काष्ठा acpi_resource_uart_serialbus अणु
	ACPI_RESOURCE_SERIAL_COMMON u8 endian;
	u8 data_bits;
	u8 stop_bits;
	u8 flow_control;
	u8 parity;
	u8 lines_enabled;
	u16 rx_fअगरo_size;
	u16 tx_fअगरo_size;
	u32 शेष_baud_rate;
पूर्ण;

/* Values क्रम Endian field above */

#घोषणा ACPI_UART_LITTLE_ENDIAN                 0
#घोषणा ACPI_UART_BIG_ENDIAN                    1

/* Values क्रम data_bits field above */

#घोषणा ACPI_UART_5_DATA_BITS                   0
#घोषणा ACPI_UART_6_DATA_BITS                   1
#घोषणा ACPI_UART_7_DATA_BITS                   2
#घोषणा ACPI_UART_8_DATA_BITS                   3
#घोषणा ACPI_UART_9_DATA_BITS                   4

/* Values क्रम stop_bits field above */

#घोषणा ACPI_UART_NO_STOP_BITS                  0
#घोषणा ACPI_UART_1_STOP_BIT                    1
#घोषणा ACPI_UART_1P5_STOP_BITS                 2
#घोषणा ACPI_UART_2_STOP_BITS                   3

/* Values क्रम flow_control field above */

#घोषणा ACPI_UART_FLOW_CONTROL_NONE             0
#घोषणा ACPI_UART_FLOW_CONTROL_HW               1
#घोषणा ACPI_UART_FLOW_CONTROL_XON_XOFF         2

/* Values क्रम Parity field above */

#घोषणा ACPI_UART_PARITY_NONE                   0
#घोषणा ACPI_UART_PARITY_EVEN                   1
#घोषणा ACPI_UART_PARITY_ODD                    2
#घोषणा ACPI_UART_PARITY_MARK                   3
#घोषणा ACPI_UART_PARITY_SPACE                  4

/* Values क्रम lines_enabled bitfield above */

#घोषणा ACPI_UART_CARRIER_DETECT                (1<<2)
#घोषणा ACPI_UART_RING_INDICATOR                (1<<3)
#घोषणा ACPI_UART_DATA_SET_READY                (1<<4)
#घोषणा ACPI_UART_DATA_TERMINAL_READY           (1<<5)
#घोषणा ACPI_UART_CLEAR_TO_SEND                 (1<<6)
#घोषणा ACPI_UART_REQUEST_TO_SEND               (1<<7)

काष्ठा acpi_resource_csi2_serialbus अणु
	ACPI_RESOURCE_SERIAL_COMMON u8 local_port_instance;
	u8 phy_type;
पूर्ण;

काष्ठा acpi_resource_pin_function अणु
	u8 revision_id;
	u8 pin_config;
	u8 shareable;		/* For values, see Interrupt Attributes above */
	u16 function_number;
	u16 pin_table_length;
	u16 venकरोr_length;
	काष्ठा acpi_resource_source resource_source;
	u16 *pin_table;
	u8 *venकरोr_data;
पूर्ण;

काष्ठा acpi_resource_pin_config अणु
	u8 revision_id;
	u8 producer_consumer;	/* For values, see Producer/Consumer above */
	u8 shareable;		/* For values, see Interrupt Attributes above */
	u8 pin_config_type;
	u32 pin_config_value;
	u16 pin_table_length;
	u16 venकरोr_length;
	काष्ठा acpi_resource_source resource_source;
	u16 *pin_table;
	u8 *venकरोr_data;
पूर्ण;

/* Values क्रम pin_config_type field above */

#घोषणा ACPI_PIN_CONFIG_DEFAULT                 0
#घोषणा ACPI_PIN_CONFIG_BIAS_PULL_UP            1
#घोषणा ACPI_PIN_CONFIG_BIAS_PULL_DOWN          2
#घोषणा ACPI_PIN_CONFIG_BIAS_DEFAULT            3
#घोषणा ACPI_PIN_CONFIG_BIAS_DISABLE            4
#घोषणा ACPI_PIN_CONFIG_BIAS_HIGH_IMPEDANCE     5
#घोषणा ACPI_PIN_CONFIG_BIAS_BUS_HOLD           6
#घोषणा ACPI_PIN_CONFIG_DRIVE_OPEN_DRAIN        7
#घोषणा ACPI_PIN_CONFIG_DRIVE_OPEN_SOURCE       8
#घोषणा ACPI_PIN_CONFIG_DRIVE_PUSH_PULL         9
#घोषणा ACPI_PIN_CONFIG_DRIVE_STRENGTH          10
#घोषणा ACPI_PIN_CONFIG_SLEW_RATE               11
#घोषणा ACPI_PIN_CONFIG_INPUT_DEBOUNCE          12
#घोषणा ACPI_PIN_CONFIG_INPUT_SCHMITT_TRIGGER   13

काष्ठा acpi_resource_pin_group अणु
	u8 revision_id;
	u8 producer_consumer;	/* For values, see Producer/Consumer above */
	u16 pin_table_length;
	u16 venकरोr_length;
	u16 *pin_table;
	काष्ठा acpi_resource_label resource_label;
	u8 *venकरोr_data;
पूर्ण;

काष्ठा acpi_resource_pin_group_function अणु
	u8 revision_id;
	u8 producer_consumer;	/* For values, see Producer/Consumer above */
	u8 shareable;		/* For values, see Interrupt Attributes above */
	u16 function_number;
	u16 venकरोr_length;
	काष्ठा acpi_resource_source resource_source;
	काष्ठा acpi_resource_label resource_source_label;
	u8 *venकरोr_data;
पूर्ण;

काष्ठा acpi_resource_pin_group_config अणु
	u8 revision_id;
	u8 producer_consumer;	/* For values, see Producer/Consumer above */
	u8 shareable;		/* For values, see Interrupt Attributes above */
	u8 pin_config_type;	/* For values, see pin_config_type above */
	u32 pin_config_value;
	u16 venकरोr_length;
	काष्ठा acpi_resource_source resource_source;
	काष्ठा acpi_resource_label resource_source_label;
	u8 *venकरोr_data;
पूर्ण;

/* ACPI_RESOURCE_TYPEs */

#घोषणा ACPI_RESOURCE_TYPE_IRQ                  0
#घोषणा ACPI_RESOURCE_TYPE_DMA                  1
#घोषणा ACPI_RESOURCE_TYPE_START_DEPENDENT      2
#घोषणा ACPI_RESOURCE_TYPE_END_DEPENDENT        3
#घोषणा ACPI_RESOURCE_TYPE_IO                   4
#घोषणा ACPI_RESOURCE_TYPE_FIXED_IO             5
#घोषणा ACPI_RESOURCE_TYPE_VENDOR               6
#घोषणा ACPI_RESOURCE_TYPE_END_TAG              7
#घोषणा ACPI_RESOURCE_TYPE_MEMORY24             8
#घोषणा ACPI_RESOURCE_TYPE_MEMORY32             9
#घोषणा ACPI_RESOURCE_TYPE_FIXED_MEMORY32       10
#घोषणा ACPI_RESOURCE_TYPE_ADDRESS16            11
#घोषणा ACPI_RESOURCE_TYPE_ADDRESS32            12
#घोषणा ACPI_RESOURCE_TYPE_ADDRESS64            13
#घोषणा ACPI_RESOURCE_TYPE_EXTENDED_ADDRESS64   14	/* ACPI 3.0 */
#घोषणा ACPI_RESOURCE_TYPE_EXTENDED_IRQ         15
#घोषणा ACPI_RESOURCE_TYPE_GENERIC_REGISTER     16
#घोषणा ACPI_RESOURCE_TYPE_GPIO                 17	/* ACPI 5.0 */
#घोषणा ACPI_RESOURCE_TYPE_FIXED_DMA            18	/* ACPI 5.0 */
#घोषणा ACPI_RESOURCE_TYPE_SERIAL_BUS           19	/* ACPI 5.0 */
#घोषणा ACPI_RESOURCE_TYPE_PIN_FUNCTION         20	/* ACPI 6.2 */
#घोषणा ACPI_RESOURCE_TYPE_PIN_CONFIG           21	/* ACPI 6.2 */
#घोषणा ACPI_RESOURCE_TYPE_PIN_GROUP            22	/* ACPI 6.2 */
#घोषणा ACPI_RESOURCE_TYPE_PIN_GROUP_FUNCTION   23	/* ACPI 6.2 */
#घोषणा ACPI_RESOURCE_TYPE_PIN_GROUP_CONFIG     24	/* ACPI 6.2 */
#घोषणा ACPI_RESOURCE_TYPE_MAX                  24

/* Master जोड़ क्रम resource descriptors */

जोड़ acpi_resource_data अणु
	काष्ठा acpi_resource_irq irq;
	काष्ठा acpi_resource_dma dma;
	काष्ठा acpi_resource_start_dependent start_dpf;
	काष्ठा acpi_resource_io io;
	काष्ठा acpi_resource_fixed_io fixed_io;
	काष्ठा acpi_resource_fixed_dma fixed_dma;
	काष्ठा acpi_resource_venकरोr venकरोr;
	काष्ठा acpi_resource_venकरोr_typed venकरोr_typed;
	काष्ठा acpi_resource_end_tag end_tag;
	काष्ठा acpi_resource_memory24 memory24;
	काष्ठा acpi_resource_memory32 memory32;
	काष्ठा acpi_resource_fixed_memory32 fixed_memory32;
	काष्ठा acpi_resource_address16 address16;
	काष्ठा acpi_resource_address32 address32;
	काष्ठा acpi_resource_address64 address64;
	काष्ठा acpi_resource_extended_address64 ext_address64;
	काष्ठा acpi_resource_extended_irq extended_irq;
	काष्ठा acpi_resource_generic_रेजिस्टर generic_reg;
	काष्ठा acpi_resource_gpio gpio;
	काष्ठा acpi_resource_i2c_serialbus i2c_serial_bus;
	काष्ठा acpi_resource_spi_serialbus spi_serial_bus;
	काष्ठा acpi_resource_uart_serialbus uart_serial_bus;
	काष्ठा acpi_resource_csi2_serialbus csi2_serial_bus;
	काष्ठा acpi_resource_common_serialbus common_serial_bus;
	काष्ठा acpi_resource_pin_function pin_function;
	काष्ठा acpi_resource_pin_config pin_config;
	काष्ठा acpi_resource_pin_group pin_group;
	काष्ठा acpi_resource_pin_group_function pin_group_function;
	काष्ठा acpi_resource_pin_group_config pin_group_config;

	/* Common fields */

	काष्ठा acpi_resource_address address;	/* Common 16/32/64 address fields */
पूर्ण;

/* Common resource header */

काष्ठा acpi_resource अणु
	u32 type;
	u32 length;
	जोड़ acpi_resource_data data;
पूर्ण;

/* restore शेष alignment */

#आशय pack()

#घोषणा ACPI_RS_SIZE_NO_DATA                8	/* Id + Length fields */
#घोषणा ACPI_RS_SIZE_MIN                    (u32) ACPI_ROUND_UP_TO_NATIVE_WORD (12)
#घोषणा ACPI_RS_SIZE(type)                  (u32) (ACPI_RS_SIZE_NO_DATA + माप (type))

/* Macro क्रम walking resource ढाँचाs with multiple descriptors */

#घोषणा ACPI_NEXT_RESOURCE(res) \
	ACPI_ADD_PTR (काष्ठा acpi_resource, (res), (res)->length)

काष्ठा acpi_pci_routing_table अणु
	u32 length;
	u32 pin;
	u64 address;		/* here क्रम 64-bit alignment */
	u32 source_index;
	अक्षर source[4];		/* pad to 64 bits so माप() works in all हालs */
पूर्ण;

#पूर्ण_अगर				/* __ACRESTYP_H__ */
