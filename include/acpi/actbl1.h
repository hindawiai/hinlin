<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/******************************************************************************
 *
 * Name: actbl1.h - Additional ACPI table definitions
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#अगर_अघोषित __ACTBL1_H__
#घोषणा __ACTBL1_H__

/*******************************************************************************
 *
 * Additional ACPI Tables
 *
 * These tables are not consumed directly by the ACPICA subप्रणाली, but are
 * included here to support device drivers and the AML disassembler.
 *
 ******************************************************************************/

/*
 * Values क्रम description table header signatures क्रम tables defined in this
 * file. Useful because they make it more dअगरficult to inadvertently type in
 * the wrong signature.
 */
#घोषणा ACPI_SIG_ASF            "ASF!"	/* Alert Standard Format table */
#घोषणा ACPI_SIG_BERT           "BERT"	/* Boot Error Record Table */
#घोषणा ACPI_SIG_BGRT           "BGRT"	/* Boot Graphics Resource Table */
#घोषणा ACPI_SIG_BOOT           "BOOT"	/* Simple Boot Flag Table */
#घोषणा ACPI_SIG_CEDT           "CEDT"	/* CXL Early Discovery Table */
#घोषणा ACPI_SIG_CPEP           "CPEP"	/* Corrected Platक्रमm Error Polling table */
#घोषणा ACPI_SIG_CSRT           "CSRT"	/* Core System Resource Table */
#घोषणा ACPI_SIG_DBG2           "DBG2"	/* Debug Port table type 2 */
#घोषणा ACPI_SIG_DBGP           "DBGP"	/* Debug Port table */
#घोषणा ACPI_SIG_DMAR           "DMAR"	/* DMA Remapping table */
#घोषणा ACPI_SIG_DRTM           "DRTM"	/* Dynamic Root of Trust क्रम Measurement table */
#घोषणा ACPI_SIG_ECDT           "ECDT"	/* Embedded Controller Boot Resources Table */
#घोषणा ACPI_SIG_EINJ           "EINJ"	/* Error Injection table */
#घोषणा ACPI_SIG_ERST           "ERST"	/* Error Record Serialization Table */
#घोषणा ACPI_SIG_FPDT           "FPDT"	/* Firmware Perक्रमmance Data Table */
#घोषणा ACPI_SIG_GTDT           "GTDT"	/* Generic Timer Description Table */
#घोषणा ACPI_SIG_HEST           "HEST"	/* Hardware Error Source Table */
#घोषणा ACPI_SIG_HMAT           "HMAT"	/* Heterogeneous Memory Attributes Table */
#घोषणा ACPI_SIG_HPET           "HPET"	/* High Precision Event Timer table */
#घोषणा ACPI_SIG_IBFT           "IBFT"	/* iSCSI Boot Firmware Table */

#घोषणा ACPI_SIG_S3PT           "S3PT"	/* S3 Perक्रमmance (sub)Table */
#घोषणा ACPI_SIG_PCCS           "PCC"	/* PCC Shared Memory Region */

/* Reserved table signatures */

#घोषणा ACPI_SIG_MATR           "MATR"	/* Memory Address Translation Table */
#घोषणा ACPI_SIG_MSDM           "MSDM"	/* Microsoft Data Management Table */

/*
 * These tables have been seen in the field, but no definition has been found
 */
#अगर_घोषित ACPI_UNDEFINED_TABLES
#घोषणा ACPI_SIG_ATKG           "ATKG"
#घोषणा ACPI_SIG_GSCI           "GSCI"	/* GMCH SCI table */
#घोषणा ACPI_SIG_IEIT           "IEIT"
#पूर्ण_अगर

/*
 * All tables must be byte-packed to match the ACPI specअगरication, since
 * the tables are provided by the प्रणाली BIOS.
 */
#आशय pack(1)

/*
 * Note: C bitfields are not used क्रम this reason:
 *
 * "Bitfields are great and easy to पढ़ो, but unक्रमtunately the C language
 * करोes not specअगरy the layout of bitfields in memory, which means they are
 * essentially useless क्रम dealing with packed data in on-disk क्रमmats or
 * binary wire protocols." (Or ACPI tables and buffers.) "If you ask me,
 * this decision was a design error in C. Ritchie could have picked an order
 * and stuck with it." Norman Ramsey.
 * See http://stackoverflow.com/a/1053662/41661
 */

/*******************************************************************************
 *
 * Common subtable headers
 *
 ******************************************************************************/

/* Generic subtable header (used in MADT, SRAT, etc.) */

काष्ठा acpi_subtable_header अणु
	u8 type;
	u8 length;
पूर्ण;

/* Subtable header क्रम WHEA tables (EINJ, ERST, WDAT) */

काष्ठा acpi_whea_header अणु
	u8 action;
	u8 inकाष्ठाion;
	u8 flags;
	u8 reserved;
	काष्ठा acpi_generic_address रेजिस्टर_region;
	u64 value;		/* Value used with Read/Write रेजिस्टर */
	u64 mask;		/* Biपंचांगask required क्रम this रेजिस्टर inकाष्ठाion */
पूर्ण;

/*******************************************************************************
 *
 * ASF - Alert Standard Format table (Signature "ASF!")
 *       Revision 0x10
 *
 * Conक्रमms to the Alert Standard Format Specअगरication V2.0, 23 April 2003
 *
 ******************************************************************************/

काष्ठा acpi_table_asf अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
पूर्ण;

/* ASF subtable header */

काष्ठा acpi_asf_header अणु
	u8 type;
	u8 reserved;
	u16 length;
पूर्ण;

/* Values क्रम Type field above */

क्रमागत acpi_asf_type अणु
	ACPI_ASF_TYPE_INFO = 0,
	ACPI_ASF_TYPE_ALERT = 1,
	ACPI_ASF_TYPE_CONTROL = 2,
	ACPI_ASF_TYPE_BOOT = 3,
	ACPI_ASF_TYPE_ADDRESS = 4,
	ACPI_ASF_TYPE_RESERVED = 5
पूर्ण;

/*
 * ASF subtables
 */

/* 0: ASF Inक्रमmation */

काष्ठा acpi_asf_info अणु
	काष्ठा acpi_asf_header header;
	u8 min_reset_value;
	u8 min_poll_पूर्णांकerval;
	u16 प्रणाली_id;
	u32 mfg_id;
	u8 flags;
	u8 reserved2[3];
पूर्ण;

/* Masks क्रम Flags field above */

#घोषणा ACPI_ASF_SMBUS_PROTOCOLS    (1)

/* 1: ASF Alerts */

काष्ठा acpi_asf_alert अणु
	काष्ठा acpi_asf_header header;
	u8 निश्चित_mask;
	u8 deनिश्चित_mask;
	u8 alerts;
	u8 data_length;
पूर्ण;

काष्ठा acpi_asf_alert_data अणु
	u8 address;
	u8 command;
	u8 mask;
	u8 value;
	u8 sensor_type;
	u8 type;
	u8 offset;
	u8 source_type;
	u8 severity;
	u8 sensor_number;
	u8 entity;
	u8 instance;
पूर्ण;

/* 2: ASF Remote Control */

काष्ठा acpi_asf_remote अणु
	काष्ठा acpi_asf_header header;
	u8 controls;
	u8 data_length;
	u16 reserved2;
पूर्ण;

काष्ठा acpi_asf_control_data अणु
	u8 function;
	u8 address;
	u8 command;
	u8 value;
पूर्ण;

/* 3: ASF RMCP Boot Options */

काष्ठा acpi_asf_rmcp अणु
	काष्ठा acpi_asf_header header;
	u8 capabilities[7];
	u8 completion_code;
	u32 enterprise_id;
	u8 command;
	u16 parameter;
	u16 boot_options;
	u16 oem_parameters;
पूर्ण;

/* 4: ASF Address */

काष्ठा acpi_asf_address अणु
	काष्ठा acpi_asf_header header;
	u8 eprom_address;
	u8 devices;
पूर्ण;

/*******************************************************************************
 *
 * BERT - Boot Error Record Table (ACPI 4.0)
 *        Version 1
 *
 ******************************************************************************/

काष्ठा acpi_table_bert अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
	u32 region_length;	/* Length of the boot error region */
	u64 address;		/* Physical address of the error region */
पूर्ण;

/* Boot Error Region (not a subtable, poपूर्णांकed to by Address field above) */

काष्ठा acpi_bert_region अणु
	u32 block_status;	/* Type of error inक्रमmation */
	u32 raw_data_offset;	/* Offset to raw error data */
	u32 raw_data_length;	/* Length of raw error data */
	u32 data_length;	/* Length of generic error data */
	u32 error_severity;	/* Severity code */
पूर्ण;

/* Values क्रम block_status flags above */

#घोषणा ACPI_BERT_UNCORRECTABLE             (1)
#घोषणा ACPI_BERT_CORRECTABLE               (1<<1)
#घोषणा ACPI_BERT_MULTIPLE_UNCORRECTABLE    (1<<2)
#घोषणा ACPI_BERT_MULTIPLE_CORRECTABLE      (1<<3)
#घोषणा ACPI_BERT_ERROR_ENTRY_COUNT         (0xFF<<4)	/* 8 bits, error count */

/* Values क्रम error_severity above */

क्रमागत acpi_bert_error_severity अणु
	ACPI_BERT_ERROR_CORRECTABLE = 0,
	ACPI_BERT_ERROR_FATAL = 1,
	ACPI_BERT_ERROR_CORRECTED = 2,
	ACPI_BERT_ERROR_NONE = 3,
	ACPI_BERT_ERROR_RESERVED = 4	/* 4 and greater are reserved */
पूर्ण;

/*
 * Note: The generic error data that follows the error_severity field above
 * uses the काष्ठा acpi_hest_generic_data defined under the HEST table below
 */

/*******************************************************************************
 *
 * BGRT - Boot Graphics Resource Table (ACPI 5.0)
 *        Version 1
 *
 ******************************************************************************/

काष्ठा acpi_table_bgrt अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
	u16 version;
	u8 status;
	u8 image_type;
	u64 image_address;
	u32 image_offset_x;
	u32 image_offset_y;
पूर्ण;

/* Flags क्रम Status field above */

#घोषणा ACPI_BGRT_DISPLAYED                 (1)
#घोषणा ACPI_BGRT_ORIENTATION_OFFSET        (3 << 1)

/*******************************************************************************
 *
 * BOOT - Simple Boot Flag Table
 *        Version 1
 *
 * Conक्रमms to the "Simple Boot Flag Specification", Version 2.1
 *
 ******************************************************************************/

काष्ठा acpi_table_boot अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
	u8 cmos_index;		/* Index in CMOS RAM क्रम the boot रेजिस्टर */
	u8 reserved[3];
पूर्ण;

/*******************************************************************************
 *
 * CEDT - CXL Early Discovery Table
 *        Version 1
 *
 * Conक्रमms to the "CXL Early Discovery Table" (CXL 2.0)
 *
 ******************************************************************************/

काष्ठा acpi_table_cedt अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
पूर्ण;

/* CEDT subtable header (Perक्रमmance Record Structure) */

काष्ठा acpi_cedt_header अणु
	u8 type;
	u8 reserved;
	u16 length;
पूर्ण;

/* Values क्रम Type field above */

क्रमागत acpi_cedt_type अणु
	ACPI_CEDT_TYPE_CHBS = 0,
	ACPI_CEDT_TYPE_RESERVED = 1
पूर्ण;

/*
 * CEDT subtables
 */

/* 0: CXL Host Bridge Structure */

काष्ठा acpi_cedt_chbs अणु
	काष्ठा acpi_cedt_header header;
	u32 uid;
	u32 cxl_version;
	u32 reserved;
	u64 base;
	u64 length;
पूर्ण;

/*******************************************************************************
 *
 * CPEP - Corrected Platक्रमm Error Polling table (ACPI 4.0)
 *        Version 1
 *
 ******************************************************************************/

काष्ठा acpi_table_cpep अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
	u64 reserved;
पूर्ण;

/* Subtable */

काष्ठा acpi_cpep_polling अणु
	काष्ठा acpi_subtable_header header;
	u8 id;			/* Processor ID */
	u8 eid;			/* Processor EID */
	u32 पूर्णांकerval;		/* Polling पूर्णांकerval (msec) */
पूर्ण;

/*******************************************************************************
 *
 * CSRT - Core System Resource Table
 *        Version 0
 *
 * Conक्रमms to the "Core System Resource Table (CSRT)", November 14, 2011
 *
 ******************************************************************************/

काष्ठा acpi_table_csrt अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
पूर्ण;

/* Resource Group subtable */

काष्ठा acpi_csrt_group अणु
	u32 length;
	u32 venकरोr_id;
	u32 subvenकरोr_id;
	u16 device_id;
	u16 subdevice_id;
	u16 revision;
	u16 reserved;
	u32 shared_info_length;

	/* Shared data immediately follows (Length = shared_info_length) */
पूर्ण;

/* Shared Info subtable */

काष्ठा acpi_csrt_shared_info अणु
	u16 major_version;
	u16 minor_version;
	u32 mmio_base_low;
	u32 mmio_base_high;
	u32 gsi_पूर्णांकerrupt;
	u8 पूर्णांकerrupt_polarity;
	u8 पूर्णांकerrupt_mode;
	u8 num_channels;
	u8 dma_address_width;
	u16 base_request_line;
	u16 num_handshake_संकेतs;
	u32 max_block_size;

	/* Resource descriptors immediately follow (Length = Group length - shared_info_length) */
पूर्ण;

/* Resource Descriptor subtable */

काष्ठा acpi_csrt_descriptor अणु
	u32 length;
	u16 type;
	u16 subtype;
	u32 uid;

	/* Resource-specअगरic inक्रमmation immediately follows */
पूर्ण;

/* Resource Types */

#घोषणा ACPI_CSRT_TYPE_INTERRUPT    0x0001
#घोषणा ACPI_CSRT_TYPE_TIMER        0x0002
#घोषणा ACPI_CSRT_TYPE_DMA          0x0003

/* Resource Subtypes */

#घोषणा ACPI_CSRT_XRUPT_LINE        0x0000
#घोषणा ACPI_CSRT_XRUPT_CONTROLLER  0x0001
#घोषणा ACPI_CSRT_TIMER             0x0000
#घोषणा ACPI_CSRT_DMA_CHANNEL       0x0000
#घोषणा ACPI_CSRT_DMA_CONTROLLER    0x0001

/*******************************************************************************
 *
 * DBG2 - Debug Port Table 2
 *        Version 0 (Both मुख्य table and subtables)
 *
 * Conक्रमms to "Microsoft Debug Port Table 2 (DBG2)", December 10, 2015
 *
 ******************************************************************************/

काष्ठा acpi_table_dbg2 अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
	u32 info_offset;
	u32 info_count;
पूर्ण;

काष्ठा acpi_dbg2_header अणु
	u32 info_offset;
	u32 info_count;
पूर्ण;

/* Debug Device Inक्रमmation Subtable */

काष्ठा acpi_dbg2_device अणु
	u8 revision;
	u16 length;
	u8 रेजिस्टर_count;	/* Number of base_address रेजिस्टरs */
	u16 namepath_length;
	u16 namepath_offset;
	u16 oem_data_length;
	u16 oem_data_offset;
	u16 port_type;
	u16 port_subtype;
	u16 reserved;
	u16 base_address_offset;
	u16 address_size_offset;
	/*
	 * Data that follows:
	 *    base_address (required) - Each in 12-byte Generic Address Structure क्रमmat.
	 *    address_size (required) - Array of u32 sizes corresponding to each base_address रेजिस्टर.
	 *    Namepath    (required) - Null terminated string. Single करोt अगर not supported.
	 *    oem_data    (optional) - Length is oem_data_length.
	 */
पूर्ण;

/* Types क्रम port_type field above */

#घोषणा ACPI_DBG2_SERIAL_PORT       0x8000
#घोषणा ACPI_DBG2_1394_PORT         0x8001
#घोषणा ACPI_DBG2_USB_PORT          0x8002
#घोषणा ACPI_DBG2_NET_PORT          0x8003

/* Subtypes क्रम port_subtype field above */

#घोषणा ACPI_DBG2_16550_COMPATIBLE  0x0000
#घोषणा ACPI_DBG2_16550_SUBSET      0x0001
#घोषणा ACPI_DBG2_ARM_PL011         0x0003
#घोषणा ACPI_DBG2_ARM_SBSA_32BIT    0x000D
#घोषणा ACPI_DBG2_ARM_SBSA_GENERIC  0x000E
#घोषणा ACPI_DBG2_ARM_DCC           0x000F
#घोषणा ACPI_DBG2_BCM2835           0x0010

#घोषणा ACPI_DBG2_1394_STANDARD     0x0000

#घोषणा ACPI_DBG2_USB_XHCI          0x0000
#घोषणा ACPI_DBG2_USB_EHCI          0x0001

/*******************************************************************************
 *
 * DBGP - Debug Port table
 *        Version 1
 *
 * Conक्रमms to the "Debug Port Specification", Version 1.00, 2/9/2000
 *
 ******************************************************************************/

काष्ठा acpi_table_dbgp अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
	u8 type;		/* 0=full 16550, 1=subset of 16550 */
	u8 reserved[3];
	काष्ठा acpi_generic_address debug_port;
पूर्ण;

/*******************************************************************************
 *
 * DMAR - DMA Remapping table
 *        Version 1
 *
 * Conक्रमms to "Intel Virtualization Technology for Directed I/O",
 * Version 2.3, October 2014
 *
 ******************************************************************************/

काष्ठा acpi_table_dmar अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
	u8 width;		/* Host Address Width */
	u8 flags;
	u8 reserved[10];
पूर्ण;

/* Masks क्रम Flags field above */

#घोषणा ACPI_DMAR_INTR_REMAP        (1)
#घोषणा ACPI_DMAR_X2APIC_OPT_OUT    (1<<1)
#घोषणा ACPI_DMAR_X2APIC_MODE       (1<<2)

/* DMAR subtable header */

काष्ठा acpi_dmar_header अणु
	u16 type;
	u16 length;
पूर्ण;

/* Values क्रम subtable type in काष्ठा acpi_dmar_header */

क्रमागत acpi_dmar_type अणु
	ACPI_DMAR_TYPE_HARDWARE_UNIT = 0,
	ACPI_DMAR_TYPE_RESERVED_MEMORY = 1,
	ACPI_DMAR_TYPE_ROOT_ATS = 2,
	ACPI_DMAR_TYPE_HARDWARE_AFFINITY = 3,
	ACPI_DMAR_TYPE_NAMESPACE = 4,
	ACPI_DMAR_TYPE_SATC = 5,
	ACPI_DMAR_TYPE_RESERVED = 6	/* 6 and greater are reserved */
पूर्ण;

/* DMAR Device Scope काष्ठाure */

काष्ठा acpi_dmar_device_scope अणु
	u8 entry_type;
	u8 length;
	u16 reserved;
	u8 क्रमागतeration_id;
	u8 bus;
पूर्ण;

/* Values क्रम entry_type in काष्ठा acpi_dmar_device_scope - device types */

क्रमागत acpi_dmar_scope_type अणु
	ACPI_DMAR_SCOPE_TYPE_NOT_USED = 0,
	ACPI_DMAR_SCOPE_TYPE_ENDPOINT = 1,
	ACPI_DMAR_SCOPE_TYPE_BRIDGE = 2,
	ACPI_DMAR_SCOPE_TYPE_IOAPIC = 3,
	ACPI_DMAR_SCOPE_TYPE_HPET = 4,
	ACPI_DMAR_SCOPE_TYPE_NAMESPACE = 5,
	ACPI_DMAR_SCOPE_TYPE_RESERVED = 6	/* 6 and greater are reserved */
पूर्ण;

काष्ठा acpi_dmar_pci_path अणु
	u8 device;
	u8 function;
पूर्ण;

/*
 * DMAR Subtables, correspond to Type in काष्ठा acpi_dmar_header
 */

/* 0: Hardware Unit Definition */

काष्ठा acpi_dmar_hardware_unit अणु
	काष्ठा acpi_dmar_header header;
	u8 flags;
	u8 reserved;
	u16 segment;
	u64 address;		/* Register Base Address */
पूर्ण;

/* Masks क्रम Flags field above */

#घोषणा ACPI_DMAR_INCLUDE_ALL       (1)

/* 1: Reserved Memory Definition */

काष्ठा acpi_dmar_reserved_memory अणु
	काष्ठा acpi_dmar_header header;
	u16 reserved;
	u16 segment;
	u64 base_address;	/* 4K aligned base address */
	u64 end_address;	/* 4K aligned limit address */
पूर्ण;

/* Masks क्रम Flags field above */

#घोषणा ACPI_DMAR_ALLOW_ALL         (1)

/* 2: Root Port ATS Capability Reporting Structure */

काष्ठा acpi_dmar_atsr अणु
	काष्ठा acpi_dmar_header header;
	u8 flags;
	u8 reserved;
	u16 segment;
पूर्ण;

/* Masks क्रम Flags field above */

#घोषणा ACPI_DMAR_ALL_PORTS         (1)

/* 3: Remapping Hardware Static Affinity Structure */

काष्ठा acpi_dmar_rhsa अणु
	काष्ठा acpi_dmar_header header;
	u32 reserved;
	u64 base_address;
	u32 proximity_करोमुख्य;
पूर्ण;

/* 4: ACPI Namespace Device Declaration Structure */

काष्ठा acpi_dmar_andd अणु
	काष्ठा acpi_dmar_header header;
	u8 reserved[3];
	u8 device_number;
	अक्षर device_name[1];
पूर्ण;

/* 5: SOC Integrated Address Translation Cache Reporting Structure */

काष्ठा acpi_dmar_satc अणु
	काष्ठा acpi_dmar_header header;
	u8 flags;
	u8 reserved;
	u16 segment;
पूर्ण;
/*******************************************************************************
 *
 * DRTM - Dynamic Root of Trust क्रम Measurement table
 * Conक्रमms to "TCG D-RTM Architecture" June 17 2013, Version 1.0.0
 * Table version 1
 *
 ******************************************************************************/

काष्ठा acpi_table_drपंचांग अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
	u64 entry_base_address;
	u64 entry_length;
	u32 entry_address32;
	u64 entry_address64;
	u64 निकास_address;
	u64 log_area_address;
	u32 log_area_length;
	u64 arch_dependent_address;
	u32 flags;
पूर्ण;

/* Flag Definitions क्रम above */

#घोषणा ACPI_DRTM_ACCESS_ALLOWED            (1)
#घोषणा ACPI_DRTM_ENABLE_GAP_CODE           (1<<1)
#घोषणा ACPI_DRTM_INCOMPLETE_MEASUREMENTS   (1<<2)
#घोषणा ACPI_DRTM_AUTHORITY_ORDER           (1<<3)

/* 1) Validated Tables List (64-bit addresses) */

काष्ठा acpi_drपंचांग_vtable_list अणु
	u32 validated_table_count;
	u64 validated_tables[1];
पूर्ण;

/* 2) Resources List (of Resource Descriptors) */

/* Resource Descriptor */

काष्ठा acpi_drपंचांग_resource अणु
	u8 size[7];
	u8 type;
	u64 address;
पूर्ण;

काष्ठा acpi_drपंचांग_resource_list अणु
	u32 resource_count;
	काष्ठा acpi_drपंचांग_resource resources[1];
पूर्ण;

/* 3) Platक्रमm-specअगरic Identअगरiers List */

काष्ठा acpi_drपंचांग_dps_id अणु
	u32 dps_id_length;
	u8 dps_id[16];
पूर्ण;

/*******************************************************************************
 *
 * ECDT - Embedded Controller Boot Resources Table
 *        Version 1
 *
 ******************************************************************************/

काष्ठा acpi_table_ecdt अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
	काष्ठा acpi_generic_address control;	/* Address of EC command/status रेजिस्टर */
	काष्ठा acpi_generic_address data;	/* Address of EC data रेजिस्टर */
	u32 uid;		/* Unique ID - must be same as the EC _UID method */
	u8 gpe;			/* The GPE क्रम the EC */
	u8 id[1];		/* Full namepath of the EC in the ACPI namespace */
पूर्ण;

/*******************************************************************************
 *
 * EINJ - Error Injection Table (ACPI 4.0)
 *        Version 1
 *
 ******************************************************************************/

काष्ठा acpi_table_einj अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
	u32 header_length;
	u8 flags;
	u8 reserved[3];
	u32 entries;
पूर्ण;

/* EINJ Injection Inकाष्ठाion Entries (actions) */

काष्ठा acpi_einj_entry अणु
	काष्ठा acpi_whea_header whea_header;	/* Common header क्रम WHEA tables */
पूर्ण;

/* Masks क्रम Flags field above */

#घोषणा ACPI_EINJ_PRESERVE          (1)

/* Values क्रम Action field above */

क्रमागत acpi_einj_actions अणु
	ACPI_EINJ_BEGIN_OPERATION = 0,
	ACPI_EINJ_GET_TRIGGER_TABLE = 1,
	ACPI_EINJ_SET_ERROR_TYPE = 2,
	ACPI_EINJ_GET_ERROR_TYPE = 3,
	ACPI_EINJ_END_OPERATION = 4,
	ACPI_EINJ_EXECUTE_OPERATION = 5,
	ACPI_EINJ_CHECK_BUSY_STATUS = 6,
	ACPI_EINJ_GET_COMMAND_STATUS = 7,
	ACPI_EINJ_SET_ERROR_TYPE_WITH_ADDRESS = 8,
	ACPI_EINJ_GET_EXECUTE_TIMINGS = 9,
	ACPI_EINJ_ACTION_RESERVED = 10,	/* 10 and greater are reserved */
	ACPI_EINJ_TRIGGER_ERROR = 0xFF	/* Except क्रम this value */
पूर्ण;

/* Values क्रम Inकाष्ठाion field above */

क्रमागत acpi_einj_inकाष्ठाions अणु
	ACPI_EINJ_READ_REGISTER = 0,
	ACPI_EINJ_READ_REGISTER_VALUE = 1,
	ACPI_EINJ_WRITE_REGISTER = 2,
	ACPI_EINJ_WRITE_REGISTER_VALUE = 3,
	ACPI_EINJ_NOOP = 4,
	ACPI_EINJ_FLUSH_CACHELINE = 5,
	ACPI_EINJ_INSTRUCTION_RESERVED = 6	/* 6 and greater are reserved */
पूर्ण;

काष्ठा acpi_einj_error_type_with_addr अणु
	u32 error_type;
	u32 venकरोr_काष्ठा_offset;
	u32 flags;
	u32 apic_id;
	u64 address;
	u64 range;
	u32 pcie_id;
पूर्ण;

काष्ठा acpi_einj_venकरोr अणु
	u32 length;
	u32 pcie_id;
	u16 venकरोr_id;
	u16 device_id;
	u8 revision_id;
	u8 reserved[3];
पूर्ण;

/* EINJ Trigger Error Action Table */

काष्ठा acpi_einj_trigger अणु
	u32 header_size;
	u32 revision;
	u32 table_size;
	u32 entry_count;
पूर्ण;

/* Command status वापस values */

क्रमागत acpi_einj_command_status अणु
	ACPI_EINJ_SUCCESS = 0,
	ACPI_EINJ_FAILURE = 1,
	ACPI_EINJ_INVALID_ACCESS = 2,
	ACPI_EINJ_STATUS_RESERVED = 3	/* 3 and greater are reserved */
पूर्ण;

/* Error types वापसed from ACPI_EINJ_GET_ERROR_TYPE (bitfield) */

#घोषणा ACPI_EINJ_PROCESSOR_CORRECTABLE     (1)
#घोषणा ACPI_EINJ_PROCESSOR_UNCORRECTABLE   (1<<1)
#घोषणा ACPI_EINJ_PROCESSOR_FATAL           (1<<2)
#घोषणा ACPI_EINJ_MEMORY_CORRECTABLE        (1<<3)
#घोषणा ACPI_EINJ_MEMORY_UNCORRECTABLE      (1<<4)
#घोषणा ACPI_EINJ_MEMORY_FATAL              (1<<5)
#घोषणा ACPI_EINJ_PCIX_CORRECTABLE          (1<<6)
#घोषणा ACPI_EINJ_PCIX_UNCORRECTABLE        (1<<7)
#घोषणा ACPI_EINJ_PCIX_FATAL                (1<<8)
#घोषणा ACPI_EINJ_PLATFORM_CORRECTABLE      (1<<9)
#घोषणा ACPI_EINJ_PLATFORM_UNCORRECTABLE    (1<<10)
#घोषणा ACPI_EINJ_PLATFORM_FATAL            (1<<11)
#घोषणा ACPI_EINJ_VENDOR_DEFINED            (1<<31)

/*******************************************************************************
 *
 * ERST - Error Record Serialization Table (ACPI 4.0)
 *        Version 1
 *
 ******************************************************************************/

काष्ठा acpi_table_erst अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
	u32 header_length;
	u32 reserved;
	u32 entries;
पूर्ण;

/* ERST Serialization Entries (actions) */

काष्ठा acpi_erst_entry अणु
	काष्ठा acpi_whea_header whea_header;	/* Common header क्रम WHEA tables */
पूर्ण;

/* Masks क्रम Flags field above */

#घोषणा ACPI_ERST_PRESERVE          (1)

/* Values क्रम Action field above */

क्रमागत acpi_erst_actions अणु
	ACPI_ERST_BEGIN_WRITE = 0,
	ACPI_ERST_BEGIN_READ = 1,
	ACPI_ERST_BEGIN_CLEAR = 2,
	ACPI_ERST_END = 3,
	ACPI_ERST_SET_RECORD_OFFSET = 4,
	ACPI_ERST_EXECUTE_OPERATION = 5,
	ACPI_ERST_CHECK_BUSY_STATUS = 6,
	ACPI_ERST_GET_COMMAND_STATUS = 7,
	ACPI_ERST_GET_RECORD_ID = 8,
	ACPI_ERST_SET_RECORD_ID = 9,
	ACPI_ERST_GET_RECORD_COUNT = 10,
	ACPI_ERST_BEGIN_DUMMY_WRIITE = 11,
	ACPI_ERST_NOT_USED = 12,
	ACPI_ERST_GET_ERROR_RANGE = 13,
	ACPI_ERST_GET_ERROR_LENGTH = 14,
	ACPI_ERST_GET_ERROR_ATTRIBUTES = 15,
	ACPI_ERST_EXECUTE_TIMINGS = 16,
	ACPI_ERST_ACTION_RESERVED = 17	/* 17 and greater are reserved */
पूर्ण;

/* Values क्रम Inकाष्ठाion field above */

क्रमागत acpi_erst_inकाष्ठाions अणु
	ACPI_ERST_READ_REGISTER = 0,
	ACPI_ERST_READ_REGISTER_VALUE = 1,
	ACPI_ERST_WRITE_REGISTER = 2,
	ACPI_ERST_WRITE_REGISTER_VALUE = 3,
	ACPI_ERST_NOOP = 4,
	ACPI_ERST_LOAD_VAR1 = 5,
	ACPI_ERST_LOAD_VAR2 = 6,
	ACPI_ERST_STORE_VAR1 = 7,
	ACPI_ERST_ADD = 8,
	ACPI_ERST_SUBTRACT = 9,
	ACPI_ERST_ADD_VALUE = 10,
	ACPI_ERST_SUBTRACT_VALUE = 11,
	ACPI_ERST_STALL = 12,
	ACPI_ERST_STALL_WHILE_TRUE = 13,
	ACPI_ERST_SKIP_NEXT_IF_TRUE = 14,
	ACPI_ERST_GOTO = 15,
	ACPI_ERST_SET_SRC_ADDRESS_BASE = 16,
	ACPI_ERST_SET_DST_ADDRESS_BASE = 17,
	ACPI_ERST_MOVE_DATA = 18,
	ACPI_ERST_INSTRUCTION_RESERVED = 19	/* 19 and greater are reserved */
पूर्ण;

/* Command status वापस values */

क्रमागत acpi_erst_command_status अणु
	ACPI_ERST_SUCCESS = 0,
	ACPI_ERST_NO_SPACE = 1,
	ACPI_ERST_NOT_AVAILABLE = 2,
	ACPI_ERST_FAILURE = 3,
	ACPI_ERST_RECORD_EMPTY = 4,
	ACPI_ERST_NOT_FOUND = 5,
	ACPI_ERST_STATUS_RESERVED = 6	/* 6 and greater are reserved */
पूर्ण;

/* Error Record Serialization Inक्रमmation */

काष्ठा acpi_erst_info अणु
	u16 signature;		/* Should be "ER" */
	u8 data[48];
पूर्ण;

/*******************************************************************************
 *
 * FPDT - Firmware Perक्रमmance Data Table (ACPI 5.0)
 *        Version 1
 *
 ******************************************************************************/

काष्ठा acpi_table_fpdt अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
पूर्ण;

/* FPDT subtable header (Perक्रमmance Record Structure) */

काष्ठा acpi_fpdt_header अणु
	u16 type;
	u8 length;
	u8 revision;
पूर्ण;

/* Values क्रम Type field above */

क्रमागत acpi_fpdt_type अणु
	ACPI_FPDT_TYPE_BOOT = 0,
	ACPI_FPDT_TYPE_S3PERF = 1
पूर्ण;

/*
 * FPDT subtables
 */

/* 0: Firmware Basic Boot Perक्रमmance Record */

काष्ठा acpi_fpdt_boot_poपूर्णांकer अणु
	काष्ठा acpi_fpdt_header header;
	u8 reserved[4];
	u64 address;
पूर्ण;

/* 1: S3 Perक्रमmance Table Poपूर्णांकer Record */

काष्ठा acpi_fpdt_s3pt_poपूर्णांकer अणु
	काष्ठा acpi_fpdt_header header;
	u8 reserved[4];
	u64 address;
पूर्ण;

/*
 * S3PT - S3 Perक्रमmance Table. This table is poपूर्णांकed to by the
 * S3 Poपूर्णांकer Record above.
 */
काष्ठा acpi_table_s3pt अणु
	u8 signature[4];	/* "S3PT" */
	u32 length;
पूर्ण;

/*
 * S3PT Subtables (Not part of the actual FPDT)
 */

/* Values क्रम Type field in S3PT header */

क्रमागत acpi_s3pt_type अणु
	ACPI_S3PT_TYPE_RESUME = 0,
	ACPI_S3PT_TYPE_SUSPEND = 1,
	ACPI_FPDT_BOOT_PERFORMANCE = 2
पूर्ण;

काष्ठा acpi_s3pt_resume अणु
	काष्ठा acpi_fpdt_header header;
	u32 resume_count;
	u64 full_resume;
	u64 average_resume;
पूर्ण;

काष्ठा acpi_s3pt_suspend अणु
	काष्ठा acpi_fpdt_header header;
	u64 suspend_start;
	u64 suspend_end;
पूर्ण;

/*
 * FPDT Boot Perक्रमmance Record (Not part of the actual FPDT)
 */
काष्ठा acpi_fpdt_boot अणु
	काष्ठा acpi_fpdt_header header;
	u8 reserved[4];
	u64 reset_end;
	u64 load_start;
	u64 startup_start;
	u64 निकास_services_entry;
	u64 निकास_services_निकास;
पूर्ण;

/*******************************************************************************
 *
 * GTDT - Generic Timer Description Table (ACPI 5.1)
 *        Version 2
 *
 ******************************************************************************/

काष्ठा acpi_table_gtdt अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
	u64 counter_block_addresss;
	u32 reserved;
	u32 secure_el1_पूर्णांकerrupt;
	u32 secure_el1_flags;
	u32 non_secure_el1_पूर्णांकerrupt;
	u32 non_secure_el1_flags;
	u32 भव_समयr_पूर्णांकerrupt;
	u32 भव_समयr_flags;
	u32 non_secure_el2_पूर्णांकerrupt;
	u32 non_secure_el2_flags;
	u64 counter_पढ़ो_block_address;
	u32 platक्रमm_समयr_count;
	u32 platक्रमm_समयr_offset;
पूर्ण;

/* Flag Definitions: Timer Block Physical Timers and Virtual समयrs */

#घोषणा ACPI_GTDT_INTERRUPT_MODE        (1)
#घोषणा ACPI_GTDT_INTERRUPT_POLARITY    (1<<1)
#घोषणा ACPI_GTDT_ALWAYS_ON             (1<<2)

काष्ठा acpi_gtdt_el2 अणु
	u32 भव_el2_समयr_gsiv;
	u32 भव_el2_समयr_flags;
पूर्ण;

/* Common GTDT subtable header */

काष्ठा acpi_gtdt_header अणु
	u8 type;
	u16 length;
पूर्ण;

/* Values क्रम GTDT subtable type above */

क्रमागत acpi_gtdt_type अणु
	ACPI_GTDT_TYPE_TIMER_BLOCK = 0,
	ACPI_GTDT_TYPE_WATCHDOG = 1,
	ACPI_GTDT_TYPE_RESERVED = 2	/* 2 and greater are reserved */
पूर्ण;

/* GTDT Subtables, correspond to Type in काष्ठा acpi_gtdt_header */

/* 0: Generic Timer Block */

काष्ठा acpi_gtdt_समयr_block अणु
	काष्ठा acpi_gtdt_header header;
	u8 reserved;
	u64 block_address;
	u32 समयr_count;
	u32 समयr_offset;
पूर्ण;

/* Timer Sub-Structure, one per समयr */

काष्ठा acpi_gtdt_समयr_entry अणु
	u8 frame_number;
	u8 reserved[3];
	u64 base_address;
	u64 el0_base_address;
	u32 समयr_पूर्णांकerrupt;
	u32 समयr_flags;
	u32 भव_समयr_पूर्णांकerrupt;
	u32 भव_समयr_flags;
	u32 common_flags;
पूर्ण;

/* Flag Definitions: समयr_flags and भव_समयr_flags above */

#घोषणा ACPI_GTDT_GT_IRQ_MODE               (1)
#घोषणा ACPI_GTDT_GT_IRQ_POLARITY           (1<<1)

/* Flag Definitions: common_flags above */

#घोषणा ACPI_GTDT_GT_IS_SECURE_TIMER        (1)
#घोषणा ACPI_GTDT_GT_ALWAYS_ON              (1<<1)

/* 1: SBSA Generic Watchकरोg Structure */

काष्ठा acpi_gtdt_watchकरोg अणु
	काष्ठा acpi_gtdt_header header;
	u8 reserved;
	u64 refresh_frame_address;
	u64 control_frame_address;
	u32 समयr_पूर्णांकerrupt;
	u32 समयr_flags;
पूर्ण;

/* Flag Definitions: समयr_flags above */

#घोषणा ACPI_GTDT_WATCHDOG_IRQ_MODE         (1)
#घोषणा ACPI_GTDT_WATCHDOG_IRQ_POLARITY     (1<<1)
#घोषणा ACPI_GTDT_WATCHDOG_SECURE           (1<<2)

/*******************************************************************************
 *
 * HEST - Hardware Error Source Table (ACPI 4.0)
 *        Version 1
 *
 ******************************************************************************/

काष्ठा acpi_table_hest अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
	u32 error_source_count;
पूर्ण;

/* HEST subtable header */

काष्ठा acpi_hest_header अणु
	u16 type;
	u16 source_id;
पूर्ण;

/* Values क्रम Type field above क्रम subtables */

क्रमागत acpi_hest_types अणु
	ACPI_HEST_TYPE_IA32_CHECK = 0,
	ACPI_HEST_TYPE_IA32_CORRECTED_CHECK = 1,
	ACPI_HEST_TYPE_IA32_NMI = 2,
	ACPI_HEST_TYPE_NOT_USED3 = 3,
	ACPI_HEST_TYPE_NOT_USED4 = 4,
	ACPI_HEST_TYPE_NOT_USED5 = 5,
	ACPI_HEST_TYPE_AER_ROOT_PORT = 6,
	ACPI_HEST_TYPE_AER_ENDPOINT = 7,
	ACPI_HEST_TYPE_AER_BRIDGE = 8,
	ACPI_HEST_TYPE_GENERIC_ERROR = 9,
	ACPI_HEST_TYPE_GENERIC_ERROR_V2 = 10,
	ACPI_HEST_TYPE_IA32_DEFERRED_CHECK = 11,
	ACPI_HEST_TYPE_RESERVED = 12	/* 12 and greater are reserved */
पूर्ण;

/*
 * HEST subकाष्ठाures contained in subtables
 */

/*
 * IA32 Error Bank(s) - Follows the काष्ठा acpi_hest_ia_machine_check and
 * काष्ठा acpi_hest_ia_corrected काष्ठाures.
 */
काष्ठा acpi_hest_ia_error_bank अणु
	u8 bank_number;
	u8 clear_status_on_init;
	u8 status_क्रमmat;
	u8 reserved;
	u32 control_रेजिस्टर;
	u64 control_data;
	u32 status_रेजिस्टर;
	u32 address_रेजिस्टर;
	u32 misc_रेजिस्टर;
पूर्ण;

/* Common HEST sub-काष्ठाure क्रम PCI/AER काष्ठाures below (6,7,8) */

काष्ठा acpi_hest_aer_common अणु
	u16 reserved1;
	u8 flags;
	u8 enabled;
	u32 records_to_pपुनः_स्मृतिate;
	u32 max_sections_per_record;
	u32 bus;		/* Bus and Segment numbers */
	u16 device;
	u16 function;
	u16 device_control;
	u16 reserved2;
	u32 uncorrectable_mask;
	u32 uncorrectable_severity;
	u32 correctable_mask;
	u32 advanced_capabilities;
पूर्ण;

/* Masks क्रम HEST Flags fields */

#घोषणा ACPI_HEST_FIRMWARE_FIRST        (1)
#घोषणा ACPI_HEST_GLOBAL                (1<<1)
#घोषणा ACPI_HEST_GHES_ASSIST           (1<<2)

/*
 * Macros to access the bus/segment numbers in Bus field above:
 *  Bus number is encoded in bits 7:0
 *  Segment number is encoded in bits 23:8
 */
#घोषणा ACPI_HEST_BUS(bus)              ((bus) & 0xFF)
#घोषणा ACPI_HEST_SEGMENT(bus)          (((bus) >> 8) & 0xFFFF)

/* Hardware Error Notअगरication */

काष्ठा acpi_hest_notअगरy अणु
	u8 type;
	u8 length;
	u16 config_ग_लिखो_enable;
	u32 poll_पूर्णांकerval;
	u32 vector;
	u32 polling_threshold_value;
	u32 polling_threshold_winकरोw;
	u32 error_threshold_value;
	u32 error_threshold_winकरोw;
पूर्ण;

/* Values क्रम Notअगरy Type field above */

क्रमागत acpi_hest_notअगरy_types अणु
	ACPI_HEST_NOTIFY_POLLED = 0,
	ACPI_HEST_NOTIFY_EXTERNAL = 1,
	ACPI_HEST_NOTIFY_LOCAL = 2,
	ACPI_HEST_NOTIFY_SCI = 3,
	ACPI_HEST_NOTIFY_NMI = 4,
	ACPI_HEST_NOTIFY_CMCI = 5,	/* ACPI 5.0 */
	ACPI_HEST_NOTIFY_MCE = 6,	/* ACPI 5.0 */
	ACPI_HEST_NOTIFY_GPIO = 7,	/* ACPI 6.0 */
	ACPI_HEST_NOTIFY_SEA = 8,	/* ACPI 6.1 */
	ACPI_HEST_NOTIFY_SEI = 9,	/* ACPI 6.1 */
	ACPI_HEST_NOTIFY_GSIV = 10,	/* ACPI 6.1 */
	ACPI_HEST_NOTIFY_SOFTWARE_DELEGATED = 11,	/* ACPI 6.2 */
	ACPI_HEST_NOTIFY_RESERVED = 12	/* 12 and greater are reserved */
पूर्ण;

/* Values क्रम config_ग_लिखो_enable bitfield above */

#घोषणा ACPI_HEST_TYPE                  (1)
#घोषणा ACPI_HEST_POLL_INTERVAL         (1<<1)
#घोषणा ACPI_HEST_POLL_THRESHOLD_VALUE  (1<<2)
#घोषणा ACPI_HEST_POLL_THRESHOLD_WINDOW (1<<3)
#घोषणा ACPI_HEST_ERR_THRESHOLD_VALUE   (1<<4)
#घोषणा ACPI_HEST_ERR_THRESHOLD_WINDOW  (1<<5)

/*
 * HEST subtables
 */

/* 0: IA32 Machine Check Exception */

काष्ठा acpi_hest_ia_machine_check अणु
	काष्ठा acpi_hest_header header;
	u16 reserved1;
	u8 flags;		/* See flags ACPI_HEST_GLOBAL, etc. above */
	u8 enabled;
	u32 records_to_pपुनः_स्मृतिate;
	u32 max_sections_per_record;
	u64 global_capability_data;
	u64 global_control_data;
	u8 num_hardware_banks;
	u8 reserved3[7];
पूर्ण;

/* 1: IA32 Corrected Machine Check */

काष्ठा acpi_hest_ia_corrected अणु
	काष्ठा acpi_hest_header header;
	u16 reserved1;
	u8 flags;		/* See flags ACPI_HEST_GLOBAL, etc. above */
	u8 enabled;
	u32 records_to_pपुनः_स्मृतिate;
	u32 max_sections_per_record;
	काष्ठा acpi_hest_notअगरy notअगरy;
	u8 num_hardware_banks;
	u8 reserved2[3];
पूर्ण;

/* 2: IA32 Non-Maskable Interrupt */

काष्ठा acpi_hest_ia_nmi अणु
	काष्ठा acpi_hest_header header;
	u32 reserved;
	u32 records_to_pपुनः_स्मृतिate;
	u32 max_sections_per_record;
	u32 max_raw_data_length;
पूर्ण;

/* 3,4,5: Not used */

/* 6: PCI Express Root Port AER */

काष्ठा acpi_hest_aer_root अणु
	काष्ठा acpi_hest_header header;
	काष्ठा acpi_hest_aer_common aer;
	u32 root_error_command;
पूर्ण;

/* 7: PCI Express AER (AER Endpoपूर्णांक) */

काष्ठा acpi_hest_aer अणु
	काष्ठा acpi_hest_header header;
	काष्ठा acpi_hest_aer_common aer;
पूर्ण;

/* 8: PCI Express/PCI-X Bridge AER */

काष्ठा acpi_hest_aer_bridge अणु
	काष्ठा acpi_hest_header header;
	काष्ठा acpi_hest_aer_common aer;
	u32 uncorrectable_mask2;
	u32 uncorrectable_severity2;
	u32 advanced_capabilities2;
पूर्ण;

/* 9: Generic Hardware Error Source */

काष्ठा acpi_hest_generic अणु
	काष्ठा acpi_hest_header header;
	u16 related_source_id;
	u8 reserved;
	u8 enabled;
	u32 records_to_pपुनः_स्मृतिate;
	u32 max_sections_per_record;
	u32 max_raw_data_length;
	काष्ठा acpi_generic_address error_status_address;
	काष्ठा acpi_hest_notअगरy notअगरy;
	u32 error_block_length;
पूर्ण;

/* 10: Generic Hardware Error Source, version 2 */

काष्ठा acpi_hest_generic_v2 अणु
	काष्ठा acpi_hest_header header;
	u16 related_source_id;
	u8 reserved;
	u8 enabled;
	u32 records_to_pपुनः_स्मृतिate;
	u32 max_sections_per_record;
	u32 max_raw_data_length;
	काष्ठा acpi_generic_address error_status_address;
	काष्ठा acpi_hest_notअगरy notअगरy;
	u32 error_block_length;
	काष्ठा acpi_generic_address पढ़ो_ack_रेजिस्टर;
	u64 पढ़ो_ack_preserve;
	u64 पढ़ो_ack_ग_लिखो;
पूर्ण;

/* Generic Error Status block */

काष्ठा acpi_hest_generic_status अणु
	u32 block_status;
	u32 raw_data_offset;
	u32 raw_data_length;
	u32 data_length;
	u32 error_severity;
पूर्ण;

/* Values क्रम block_status flags above */

#घोषणा ACPI_HEST_UNCORRECTABLE             (1)
#घोषणा ACPI_HEST_CORRECTABLE               (1<<1)
#घोषणा ACPI_HEST_MULTIPLE_UNCORRECTABLE    (1<<2)
#घोषणा ACPI_HEST_MULTIPLE_CORRECTABLE      (1<<3)
#घोषणा ACPI_HEST_ERROR_ENTRY_COUNT         (0xFF<<4)	/* 8 bits, error count */

/* Generic Error Data entry */

काष्ठा acpi_hest_generic_data अणु
	u8 section_type[16];
	u32 error_severity;
	u16 revision;
	u8 validation_bits;
	u8 flags;
	u32 error_data_length;
	u8 fru_id[16];
	u8 fru_text[20];
पूर्ण;

/* Extension क्रम revision 0x0300 */

काष्ठा acpi_hest_generic_data_v300 अणु
	u8 section_type[16];
	u32 error_severity;
	u16 revision;
	u8 validation_bits;
	u8 flags;
	u32 error_data_length;
	u8 fru_id[16];
	u8 fru_text[20];
	u64 समय_stamp;
पूर्ण;

/* Values क्रम error_severity above */

#घोषणा ACPI_HEST_GEN_ERROR_RECOVERABLE     0
#घोषणा ACPI_HEST_GEN_ERROR_FATAL           1
#घोषणा ACPI_HEST_GEN_ERROR_CORRECTED       2
#घोषणा ACPI_HEST_GEN_ERROR_NONE            3

/* Flags क्रम validation_bits above */

#घोषणा ACPI_HEST_GEN_VALID_FRU_ID          (1)
#घोषणा ACPI_HEST_GEN_VALID_FRU_STRING      (1<<1)
#घोषणा ACPI_HEST_GEN_VALID_TIMESTAMP       (1<<2)

/* 11: IA32 Deferred Machine Check Exception (ACPI 6.2) */

काष्ठा acpi_hest_ia_deferred_check अणु
	काष्ठा acpi_hest_header header;
	u16 reserved1;
	u8 flags;		/* See flags ACPI_HEST_GLOBAL, etc. above */
	u8 enabled;
	u32 records_to_pपुनः_स्मृतिate;
	u32 max_sections_per_record;
	काष्ठा acpi_hest_notअगरy notअगरy;
	u8 num_hardware_banks;
	u8 reserved2[3];
पूर्ण;

/*******************************************************************************
 *
 * HMAT - Heterogeneous Memory Attributes Table (ACPI 6.2)
 *        Version 1
 *
 ******************************************************************************/

काष्ठा acpi_table_hmat अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
	u32 reserved;
पूर्ण;

/* Values क्रम HMAT काष्ठाure types */

क्रमागत acpi_hmat_type अणु
	ACPI_HMAT_TYPE_PROXIMITY = 0,	/* Memory proximity करोमुख्य attributes */
	ACPI_HMAT_TYPE_LOCALITY = 1,	/* System locality latency and bandwidth inक्रमmation */
	ACPI_HMAT_TYPE_CACHE = 2,	/* Memory side cache inक्रमmation */
	ACPI_HMAT_TYPE_RESERVED = 3	/* 3 and greater are reserved */
पूर्ण;

काष्ठा acpi_hmat_काष्ठाure अणु
	u16 type;
	u16 reserved;
	u32 length;
पूर्ण;

/*
 * HMAT Structures, correspond to Type in काष्ठा acpi_hmat_काष्ठाure
 */

/* 0: Memory proximity करोमुख्य attributes */

काष्ठा acpi_hmat_proximity_करोमुख्य अणु
	काष्ठा acpi_hmat_काष्ठाure header;
	u16 flags;
	u16 reserved1;
	u32 processor_PD;	/* Processor proximity करोमुख्य */
	u32 memory_PD;		/* Memory proximity करोमुख्य */
	u32 reserved2;
	u64 reserved3;
	u64 reserved4;
पूर्ण;

/* Masks क्रम Flags field above */

#घोषणा ACPI_HMAT_PROCESSOR_PD_VALID    (1)	/* 1: processor_PD field is valid */
#घोषणा ACPI_HMAT_MEMORY_PD_VALID       (1<<1)	/* 1: memory_PD field is valid */
#घोषणा ACPI_HMAT_RESERVATION_HINT      (1<<2)	/* 1: Reservation hपूर्णांक */

/* 1: System locality latency and bandwidth inक्रमmation */

काष्ठा acpi_hmat_locality अणु
	काष्ठा acpi_hmat_काष्ठाure header;
	u8 flags;
	u8 data_type;
	u8 min_transfer_size;
	u8 reserved1;
	u32 number_of_initiator_Pds;
	u32 number_of_target_Pds;
	u32 reserved2;
	u64 entry_base_unit;
पूर्ण;

/* Masks क्रम Flags field above */

#घोषणा ACPI_HMAT_MEMORY_HIERARCHY  (0x0F)     /* Bits 0-3 */

/* Values क्रम Memory Hierarchy flags */

#घोषणा ACPI_HMAT_MEMORY            0
#घोषणा ACPI_HMAT_LAST_LEVEL_CACHE  1
#घोषणा ACPI_HMAT_1ST_LEVEL_CACHE   2
#घोषणा ACPI_HMAT_2ND_LEVEL_CACHE   3
#घोषणा ACPI_HMAT_3RD_LEVEL_CACHE   4
#घोषणा ACPI_HMAT_MINIMUM_XFER_SIZE 0x10       /* Bit 4: ACPI 6.4 */
#घोषणा ACPI_HMAT_NON_SEQUENTIAL_XFERS 0x20    /* Bit 5: ACPI 6.4 */


/* Values क्रम data_type field above */

#घोषणा ACPI_HMAT_ACCESS_LATENCY    0
#घोषणा ACPI_HMAT_READ_LATENCY      1
#घोषणा ACPI_HMAT_WRITE_LATENCY     2
#घोषणा ACPI_HMAT_ACCESS_BANDWIDTH  3
#घोषणा ACPI_HMAT_READ_BANDWIDTH    4
#घोषणा ACPI_HMAT_WRITE_BANDWIDTH   5

/* 2: Memory side cache inक्रमmation */

काष्ठा acpi_hmat_cache अणु
	काष्ठा acpi_hmat_काष्ठाure header;
	u32 memory_PD;
	u32 reserved1;
	u64 cache_size;
	u32 cache_attributes;
	u16 reserved2;
	u16 number_of_SMBIOShandles;
पूर्ण;

/* Masks क्रम cache_attributes field above */

#घोषणा ACPI_HMAT_TOTAL_CACHE_LEVEL     (0x0000000F)
#घोषणा ACPI_HMAT_CACHE_LEVEL           (0x000000F0)
#घोषणा ACPI_HMAT_CACHE_ASSOCIATIVITY   (0x00000F00)
#घोषणा ACPI_HMAT_WRITE_POLICY          (0x0000F000)
#घोषणा ACPI_HMAT_CACHE_LINE_SIZE       (0xFFFF0000)

/* Values क्रम cache associativity flag */

#घोषणा ACPI_HMAT_CA_NONE                     (0)
#घोषणा ACPI_HMAT_CA_सूचीECT_MAPPED            (1)
#घोषणा ACPI_HMAT_CA_COMPLEX_CACHE_INDEXING   (2)

/* Values क्रम ग_लिखो policy flag */

#घोषणा ACPI_HMAT_CP_NONE   (0)
#घोषणा ACPI_HMAT_CP_WB     (1)
#घोषणा ACPI_HMAT_CP_WT     (2)

/*******************************************************************************
 *
 * HPET - High Precision Event Timer table
 *        Version 1
 *
 * Conक्रमms to "IA-PC HPET (High Precision Event Timers) Specification",
 * Version 1.0a, October 2004
 *
 ******************************************************************************/

काष्ठा acpi_table_hpet अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
	u32 id;			/* Hardware ID of event समयr block */
	काष्ठा acpi_generic_address address;	/* Address of event समयr block */
	u8 sequence;		/* HPET sequence number */
	u16 minimum_tick;	/* Main counter min tick, periodic mode */
	u8 flags;
पूर्ण;

/* Masks क्रम Flags field above */

#घोषणा ACPI_HPET_PAGE_PROTECT_MASK (3)

/* Values क्रम Page Protect flags */

क्रमागत acpi_hpet_page_protect अणु
	ACPI_HPET_NO_PAGE_PROTECT = 0,
	ACPI_HPET_PAGE_PROTECT4 = 1,
	ACPI_HPET_PAGE_PROTECT64 = 2
पूर्ण;

/*******************************************************************************
 *
 * IBFT - Boot Firmware Table
 *        Version 1
 *
 * Conक्रमms to "iSCSI Boot Firmware Table (iBFT) as Defined in ACPI 3.0b
 * Specअगरication", Version 1.01, March 1, 2007
 *
 * Note: It appears that this table is not पूर्णांकended to appear in the RSDT/XSDT.
 * Thereक्रमe, it is not currently supported by the disassembler.
 *
 ******************************************************************************/

काष्ठा acpi_table_ibft अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
	u8 reserved[12];
पूर्ण;

/* IBFT common subtable header */

काष्ठा acpi_ibft_header अणु
	u8 type;
	u8 version;
	u16 length;
	u8 index;
	u8 flags;
पूर्ण;

/* Values क्रम Type field above */

क्रमागत acpi_ibft_type अणु
	ACPI_IBFT_TYPE_NOT_USED = 0,
	ACPI_IBFT_TYPE_CONTROL = 1,
	ACPI_IBFT_TYPE_INITIATOR = 2,
	ACPI_IBFT_TYPE_NIC = 3,
	ACPI_IBFT_TYPE_TARGET = 4,
	ACPI_IBFT_TYPE_EXTENSIONS = 5,
	ACPI_IBFT_TYPE_RESERVED = 6	/* 6 and greater are reserved */
पूर्ण;

/* IBFT subtables */

काष्ठा acpi_ibft_control अणु
	काष्ठा acpi_ibft_header header;
	u16 extensions;
	u16 initiator_offset;
	u16 nic0_offset;
	u16 target0_offset;
	u16 nic1_offset;
	u16 target1_offset;
पूर्ण;

काष्ठा acpi_ibft_initiator अणु
	काष्ठा acpi_ibft_header header;
	u8 sns_server[16];
	u8 slp_server[16];
	u8 primary_server[16];
	u8 secondary_server[16];
	u16 name_length;
	u16 name_offset;
पूर्ण;

काष्ठा acpi_ibft_nic अणु
	काष्ठा acpi_ibft_header header;
	u8 ip_address[16];
	u8 subnet_mask_prefix;
	u8 origin;
	u8 gateway[16];
	u8 primary_dns[16];
	u8 secondary_dns[16];
	u8 dhcp[16];
	u16 vlan;
	u8 mac_address[6];
	u16 pci_address;
	u16 name_length;
	u16 name_offset;
पूर्ण;

काष्ठा acpi_ibft_target अणु
	काष्ठा acpi_ibft_header header;
	u8 target_ip_address[16];
	u16 target_ip_socket;
	u8 target_boot_lun[8];
	u8 chap_type;
	u8 nic_association;
	u16 target_name_length;
	u16 target_name_offset;
	u16 chap_name_length;
	u16 chap_name_offset;
	u16 chap_secret_length;
	u16 chap_secret_offset;
	u16 reverse_chap_name_length;
	u16 reverse_chap_name_offset;
	u16 reverse_chap_secret_length;
	u16 reverse_chap_secret_offset;
पूर्ण;

/* Reset to शेष packing */

#आशय pack()

#पूर्ण_अगर				/* __ACTBL1_H__ */
