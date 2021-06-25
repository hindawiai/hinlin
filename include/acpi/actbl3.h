<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/******************************************************************************
 *
 * Name: actbl3.h - ACPI Table Definitions
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#अगर_अघोषित __ACTBL3_H__
#घोषणा __ACTBL3_H__

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
#घोषणा ACPI_SIG_SLIC           "SLIC"	/* Software Licensing Description Table */
#घोषणा ACPI_SIG_SLIT           "SLIT"	/* System Locality Distance Inक्रमmation Table */
#घोषणा ACPI_SIG_SPCR           "SPCR"	/* Serial Port Console Redirection table */
#घोषणा ACPI_SIG_SPMI           "SPMI"	/* Server Platक्रमm Management Interface table */
#घोषणा ACPI_SIG_SRAT           "SRAT"	/* System Resource Affinity Table */
#घोषणा ACPI_SIG_STAO           "STAO"	/* Status Override table */
#घोषणा ACPI_SIG_TCPA           "TCPA"	/* Trusted Computing Platक्रमm Alliance table */
#घोषणा ACPI_SIG_TPM2           "TPM2"	/* Trusted Platक्रमm Module 2.0 H/W पूर्णांकerface table */
#घोषणा ACPI_SIG_UEFI           "UEFI"	/* Uefi Boot Optimization Table */
#घोषणा ACPI_SIG_VIOT           "VIOT"	/* Virtual I/O Translation Table */
#घोषणा ACPI_SIG_WAET           "WAET"	/* Winकरोws ACPI Emulated devices Table */
#घोषणा ACPI_SIG_WDAT           "WDAT"	/* Watchकरोg Action Table */
#घोषणा ACPI_SIG_WDDT           "WDDT"	/* Watchकरोg Timer Description Table */
#घोषणा ACPI_SIG_WDRT           "WDRT"	/* Watchकरोg Resource Table */
#घोषणा ACPI_SIG_WPBT           "WPBT"	/* Winकरोws Platक्रमm Binary Table */
#घोषणा ACPI_SIG_WSMT           "WSMT"	/* Winकरोws SMM Security Mitigations Table */
#घोषणा ACPI_SIG_XENV           "XENV"	/* Xen Environment table */
#घोषणा ACPI_SIG_XXXX           "XXXX"	/* Intermediate AML header क्रम ASL/ASL+ converter */

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
 * SLIC - Software Licensing Description Table
 *
 * Conक्रमms to "Microsoft Software Licensing Tables (SLIC and MSDM)",
 * November 29, 2011. Copyright 2011 Microsoft
 *
 ******************************************************************************/

/* Basic SLIC table is only the common ACPI header */

काष्ठा acpi_table_slic अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
पूर्ण;

/*******************************************************************************
 *
 * SLIT - System Locality Distance Inक्रमmation Table
 *        Version 1
 *
 ******************************************************************************/

काष्ठा acpi_table_slit अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
	u64 locality_count;
	u8 entry[1];		/* Real size = localities^2 */
पूर्ण;

/*******************************************************************************
 *
 * SPCR - Serial Port Console Redirection table
 *        Version 2
 *
 * Conक्रमms to "Serial Port Console Redirection Table",
 * Version 1.03, August 10, 2015
 *
 ******************************************************************************/

काष्ठा acpi_table_spcr अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
	u8 पूर्णांकerface_type;	/* 0=full 16550, 1=subset of 16550 */
	u8 reserved[3];
	काष्ठा acpi_generic_address serial_port;
	u8 पूर्णांकerrupt_type;
	u8 pc_पूर्णांकerrupt;
	u32 पूर्णांकerrupt;
	u8 baud_rate;
	u8 parity;
	u8 stop_bits;
	u8 flow_control;
	u8 terminal_type;
	u8 reserved1;
	u16 pci_device_id;
	u16 pci_venकरोr_id;
	u8 pci_bus;
	u8 pci_device;
	u8 pci_function;
	u32 pci_flags;
	u8 pci_segment;
	u32 reserved2;
पूर्ण;

/* Masks क्रम pci_flags field above */

#घोषणा ACPI_SPCR_DO_NOT_DISABLE    (1)

/* Values क्रम Interface Type: See the definition of the DBG2 table */

/*******************************************************************************
 *
 * SPMI - Server Platक्रमm Management Interface table
 *        Version 5
 *
 * Conक्रमms to "Intelligent Platक्रमm Management Interface Specअगरication
 * Second Generation v2.0", Document Revision 1.0, February 12, 2004 with
 * June 12, 2009 markup.
 *
 ******************************************************************************/

काष्ठा acpi_table_spmi अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
	u8 पूर्णांकerface_type;
	u8 reserved;		/* Must be 1 */
	u16 spec_revision;	/* Version of IPMI */
	u8 पूर्णांकerrupt_type;
	u8 gpe_number;		/* GPE asचिन्हित */
	u8 reserved1;
	u8 pci_device_flag;
	u32 पूर्णांकerrupt;
	काष्ठा acpi_generic_address ipmi_रेजिस्टर;
	u8 pci_segment;
	u8 pci_bus;
	u8 pci_device;
	u8 pci_function;
	u8 reserved2;
पूर्ण;

/* Values क्रम पूर्णांकerface_type above */

क्रमागत acpi_spmi_पूर्णांकerface_types अणु
	ACPI_SPMI_NOT_USED = 0,
	ACPI_SPMI_KEYBOARD = 1,
	ACPI_SPMI_SMI = 2,
	ACPI_SPMI_BLOCK_TRANSFER = 3,
	ACPI_SPMI_SMBUS = 4,
	ACPI_SPMI_RESERVED = 5	/* 5 and above are reserved */
पूर्ण;

/*******************************************************************************
 *
 * SRAT - System Resource Affinity Table
 *        Version 3
 *
 ******************************************************************************/

काष्ठा acpi_table_srat अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
	u32 table_revision;	/* Must be value '1' */
	u64 reserved;		/* Reserved, must be zero */
पूर्ण;

/* Values क्रम subtable type in काष्ठा acpi_subtable_header */

क्रमागत acpi_srat_type अणु
	ACPI_SRAT_TYPE_CPU_AFFINITY = 0,
	ACPI_SRAT_TYPE_MEMORY_AFFINITY = 1,
	ACPI_SRAT_TYPE_X2APIC_CPU_AFFINITY = 2,
	ACPI_SRAT_TYPE_GICC_AFFINITY = 3,
	ACPI_SRAT_TYPE_GIC_ITS_AFFINITY = 4,	/* ACPI 6.2 */
	ACPI_SRAT_TYPE_GENERIC_AFFINITY = 5,	/* ACPI 6.3 */
	ACPI_SRAT_TYPE_RESERVED = 6	/* 5 and greater are reserved */
पूर्ण;

/*
 * SRAT Subtables, correspond to Type in काष्ठा acpi_subtable_header
 */

/* 0: Processor Local APIC/SAPIC Affinity */

काष्ठा acpi_srat_cpu_affinity अणु
	काष्ठा acpi_subtable_header header;
	u8 proximity_करोमुख्य_lo;
	u8 apic_id;
	u32 flags;
	u8 local_sapic_eid;
	u8 proximity_करोमुख्य_hi[3];
	u32 घड़ी_करोमुख्य;
पूर्ण;

/* Flags */

#घोषणा ACPI_SRAT_CPU_USE_AFFINITY  (1)	/* 00: Use affinity काष्ठाure */

/* 1: Memory Affinity */

काष्ठा acpi_srat_mem_affinity अणु
	काष्ठा acpi_subtable_header header;
	u32 proximity_करोमुख्य;
	u16 reserved;		/* Reserved, must be zero */
	u64 base_address;
	u64 length;
	u32 reserved1;
	u32 flags;
	u64 reserved2;		/* Reserved, must be zero */
पूर्ण;

/* Flags */

#घोषणा ACPI_SRAT_MEM_ENABLED       (1)	/* 00: Use affinity काष्ठाure */
#घोषणा ACPI_SRAT_MEM_HOT_PLUGGABLE (1<<1)	/* 01: Memory region is hot pluggable */
#घोषणा ACPI_SRAT_MEM_NON_VOLATILE  (1<<2)	/* 02: Memory region is non-अस्थिर */

/* 2: Processor Local X2_APIC Affinity (ACPI 4.0) */

काष्ठा acpi_srat_x2apic_cpu_affinity अणु
	काष्ठा acpi_subtable_header header;
	u16 reserved;		/* Reserved, must be zero */
	u32 proximity_करोमुख्य;
	u32 apic_id;
	u32 flags;
	u32 घड़ी_करोमुख्य;
	u32 reserved2;
पूर्ण;

/* Flags क्रम काष्ठा acpi_srat_cpu_affinity and काष्ठा acpi_srat_x2apic_cpu_affinity */

#घोषणा ACPI_SRAT_CPU_ENABLED       (1)	/* 00: Use affinity काष्ठाure */

/* 3: GICC Affinity (ACPI 5.1) */

काष्ठा acpi_srat_gicc_affinity अणु
	काष्ठा acpi_subtable_header header;
	u32 proximity_करोमुख्य;
	u32 acpi_processor_uid;
	u32 flags;
	u32 घड़ी_करोमुख्य;
पूर्ण;

/* Flags क्रम काष्ठा acpi_srat_gicc_affinity */

#घोषणा ACPI_SRAT_GICC_ENABLED     (1)	/* 00: Use affinity काष्ठाure */

/* 4: GCC ITS Affinity (ACPI 6.2) */

काष्ठा acpi_srat_gic_its_affinity अणु
	काष्ठा acpi_subtable_header header;
	u32 proximity_करोमुख्य;
	u16 reserved;
	u32 its_id;
पूर्ण;

/* 5: Generic Initiator Affinity Structure (ACPI 6.3) */

काष्ठा acpi_srat_generic_affinity अणु
	काष्ठा acpi_subtable_header header;
	u8 reserved;
	u8 device_handle_type;
	u32 proximity_करोमुख्य;
	u8 device_handle[16];
	u32 flags;
	u32 reserved1;
पूर्ण;

/* Flags क्रम काष्ठा acpi_srat_generic_affinity */

#घोषणा ACPI_SRAT_GENERIC_AFFINITY_ENABLED     (1)	/* 00: Use affinity काष्ठाure */
#घोषणा ACPI_SRAT_ARCHITECTURAL_TRANSACTIONS   (1<<1)	/* ACPI 6.4 */

/*******************************************************************************
 *
 * STAO - Status Override Table (_STA override) - ACPI 6.0
 *        Version 1
 *
 * Conक्रमms to "ACPI Specification for Status Override Table"
 * 6 January 2015
 *
 ******************************************************************************/

काष्ठा acpi_table_stao अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
	u8 ignore_uart;
पूर्ण;

/*******************************************************************************
 *
 * TCPA - Trusted Computing Platक्रमm Alliance table
 *        Version 2
 *
 * TCG Hardware Interface Table क्रम TPM 1.2 Clients and Servers
 *
 * Conक्रमms to "TCG ACPI Specification, Family 1.2 and 2.0",
 * Version 1.2, Revision 8
 * February 27, 2017
 *
 * NOTE: There are two versions of the table with the same signature --
 * the client version and the server version. The common platक्रमm_class
 * field is used to dअगरferentiate the two types of tables.
 *
 ******************************************************************************/

काष्ठा acpi_table_tcpa_hdr अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
	u16 platक्रमm_class;
पूर्ण;

/*
 * Values क्रम platक्रमm_class above.
 * This is how the client and server subtables are dअगरferentiated
 */
#घोषणा ACPI_TCPA_CLIENT_TABLE          0
#घोषणा ACPI_TCPA_SERVER_TABLE          1

काष्ठा acpi_table_tcpa_client अणु
	u32 minimum_log_length;	/* Minimum length क्रम the event log area */
	u64 log_address;	/* Address of the event log area */
पूर्ण;

काष्ठा acpi_table_tcpa_server अणु
	u16 reserved;
	u64 minimum_log_length;	/* Minimum length क्रम the event log area */
	u64 log_address;	/* Address of the event log area */
	u16 spec_revision;
	u8 device_flags;
	u8 पूर्णांकerrupt_flags;
	u8 gpe_number;
	u8 reserved2[3];
	u32 global_पूर्णांकerrupt;
	काष्ठा acpi_generic_address address;
	u32 reserved3;
	काष्ठा acpi_generic_address config_address;
	u8 group;
	u8 bus;			/* PCI Bus/Segment/Function numbers */
	u8 device;
	u8 function;
पूर्ण;

/* Values क्रम device_flags above */

#घोषणा ACPI_TCPA_PCI_DEVICE            (1)
#घोषणा ACPI_TCPA_BUS_PNP               (1<<1)
#घोषणा ACPI_TCPA_ADDRESS_VALID         (1<<2)

/* Values क्रम पूर्णांकerrupt_flags above */

#घोषणा ACPI_TCPA_INTERRUPT_MODE        (1)
#घोषणा ACPI_TCPA_INTERRUPT_POLARITY    (1<<1)
#घोषणा ACPI_TCPA_SCI_VIA_GPE           (1<<2)
#घोषणा ACPI_TCPA_GLOBAL_INTERRUPT      (1<<3)

/*******************************************************************************
 *
 * TPM2 - Trusted Platक्रमm Module (TPM) 2.0 Hardware Interface Table
 *        Version 4
 *
 * TCG Hardware Interface Table क्रम TPM 2.0 Clients and Servers
 *
 * Conक्रमms to "TCG ACPI Specification, Family 1.2 and 2.0",
 * Version 1.2, Revision 8
 * February 27, 2017
 *
 ******************************************************************************/

/* Revision 3 */

काष्ठा acpi_table_tpm23 अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
	u32 reserved;
	u64 control_address;
	u32 start_method;
पूर्ण;

/* Value क्रम start_method above */

#घोषणा ACPI_TPM23_ACPI_START_METHOD                 2

/*
 * Optional trailer क्रम revision 3. If start method is 2, there is a 4 byte
 * reserved area of all zeros.
 */
काष्ठा acpi_पंचांगp23_trailer अणु
	u32 reserved;
पूर्ण;

/* Revision 4 */

काष्ठा acpi_table_tpm2 अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
	u16 platक्रमm_class;
	u16 reserved;
	u64 control_address;
	u32 start_method;

	/* Platक्रमm-specअगरic data follows */
पूर्ण;

/* Optional trailer क्रम revision 4 holding platक्रमm-specअगरic data */
काष्ठा acpi_tpm2_phy अणु
	u8  start_method_specअगरic[12];
	u32 log_area_minimum_length;
	u64 log_area_start_address;
पूर्ण;

/* Values क्रम start_method above */

#घोषणा ACPI_TPM2_NOT_ALLOWED                       0
#घोषणा ACPI_TPM2_RESERVED1                         1
#घोषणा ACPI_TPM2_START_METHOD                      2
#घोषणा ACPI_TPM2_RESERVED3                         3
#घोषणा ACPI_TPM2_RESERVED4                         4
#घोषणा ACPI_TPM2_RESERVED5                         5
#घोषणा ACPI_TPM2_MEMORY_MAPPED                     6
#घोषणा ACPI_TPM2_COMMAND_BUFFER                    7
#घोषणा ACPI_TPM2_COMMAND_BUFFER_WITH_START_METHOD  8
#घोषणा ACPI_TPM2_RESERVED9                         9
#घोषणा ACPI_TPM2_RESERVED10                        10
#घोषणा ACPI_TPM2_COMMAND_BUFFER_WITH_ARM_SMC       11	/* V1.2 Rev 8 */
#घोषणा ACPI_TPM2_RESERVED                          12

/* Optional trailer appears after any start_method subtables */

काष्ठा acpi_tpm2_trailer अणु
	u8 method_parameters[12];
	u32 minimum_log_length;	/* Minimum length क्रम the event log area */
	u64 log_address;	/* Address of the event log area */
पूर्ण;

/*
 * Subtables (start_method-specअगरic)
 */

/* 11: Start Method क्रम ARM SMC (V1.2 Rev 8) */

काष्ठा acpi_tpm2_arm_smc अणु
	u32 global_पूर्णांकerrupt;
	u8 पूर्णांकerrupt_flags;
	u8 operation_flags;
	u16 reserved;
	u32 function_id;
पूर्ण;

/* Values क्रम पूर्णांकerrupt_flags above */

#घोषणा ACPI_TPM2_INTERRUPT_SUPPORT     (1)

/* Values क्रम operation_flags above */

#घोषणा ACPI_TPM2_IDLE_SUPPORT          (1)

/*******************************************************************************
 *
 * UEFI - UEFI Boot optimization Table
 *        Version 1
 *
 * Conक्रमms to "Unified Extensible Firmware Interface Specification",
 * Version 2.3, May 8, 2009
 *
 ******************************************************************************/

काष्ठा acpi_table_uefi अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
	u8 identअगरier[16];	/* UUID identअगरier */
	u16 data_offset;	/* Offset of reमुख्यing data in table */
पूर्ण;

/*******************************************************************************
 *
 * VIOT - Virtual I/O Translation Table
 *        Version 1
 *
 ******************************************************************************/

काष्ठा acpi_table_viot अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
	u16 node_count;
	u16 node_offset;
	u8 reserved[8];
पूर्ण;

/* VIOT subtable header */

काष्ठा acpi_viot_header अणु
	u8 type;
	u8 reserved;
	u16 length;
पूर्ण;

/* Values क्रम Type field above */

क्रमागत acpi_viot_node_type अणु
	ACPI_VIOT_NODE_PCI_RANGE = 0x01,
	ACPI_VIOT_NODE_MMIO = 0x02,
	ACPI_VIOT_NODE_VIRTIO_IOMMU_PCI = 0x03,
	ACPI_VIOT_NODE_VIRTIO_IOMMU_MMIO = 0x04,
	ACPI_VIOT_RESERVED = 0x05
पूर्ण;

/* VIOT subtables */

काष्ठा acpi_viot_pci_range अणु
	काष्ठा acpi_viot_header header;
	u32 endpoपूर्णांक_start;
	u16 segment_start;
	u16 segment_end;
	u16 bdf_start;
	u16 bdf_end;
	u16 output_node;
	u8 reserved[6];
पूर्ण;

काष्ठा acpi_viot_mmio अणु
	काष्ठा acpi_viot_header header;
	u32 endpoपूर्णांक;
	u64 base_address;
	u16 output_node;
	u8 reserved[6];
पूर्ण;

काष्ठा acpi_viot_virtio_iommu_pci अणु
	काष्ठा acpi_viot_header header;
	u16 segment;
	u16 bdf;
	u8 reserved[8];
पूर्ण;

काष्ठा acpi_viot_virtio_iommu_mmio अणु
	काष्ठा acpi_viot_header header;
	u8 reserved[4];
	u64 base_address;
पूर्ण;

/*******************************************************************************
 *
 * WAET - Winकरोws ACPI Emulated devices Table
 *        Version 1
 *
 * Conक्रमms to "Windows ACPI Emulated Devices Table", version 1.0, April 6, 2009
 *
 ******************************************************************************/

काष्ठा acpi_table_waet अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
	u32 flags;
पूर्ण;

/* Masks क्रम Flags field above */

#घोषणा ACPI_WAET_RTC_NO_ACK        (1)	/* RTC requires no पूर्णांक acknowledge */
#घोषणा ACPI_WAET_TIMER_ONE_READ    (1<<1)	/* PM समयr requires only one पढ़ो */

/*******************************************************************************
 *
 * WDAT - Watchकरोg Action Table
 *        Version 1
 *
 * Conक्रमms to "Hardware Watchdog Timers Design Specification",
 * Copyright 2006 Microsoft Corporation.
 *
 ******************************************************************************/

काष्ठा acpi_table_wdat अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
	u32 header_length;	/* Watchकरोg Header Length */
	u16 pci_segment;	/* PCI Segment number */
	u8 pci_bus;		/* PCI Bus number */
	u8 pci_device;		/* PCI Device number */
	u8 pci_function;	/* PCI Function number */
	u8 reserved[3];
	u32 समयr_period;	/* Period of one समयr count (msec) */
	u32 max_count;		/* Maximum counter value supported */
	u32 min_count;		/* Minimum counter value */
	u8 flags;
	u8 reserved2[3];
	u32 entries;		/* Number of watchकरोg entries that follow */
पूर्ण;

/* Masks क्रम Flags field above */

#घोषणा ACPI_WDAT_ENABLED           (1)
#घोषणा ACPI_WDAT_STOPPED           0x80

/* WDAT Inकाष्ठाion Entries (actions) */

काष्ठा acpi_wdat_entry अणु
	u8 action;
	u8 inकाष्ठाion;
	u16 reserved;
	काष्ठा acpi_generic_address रेजिस्टर_region;
	u32 value;		/* Value used with Read/Write रेजिस्टर */
	u32 mask;		/* Biपंचांगask required क्रम this रेजिस्टर inकाष्ठाion */
पूर्ण;

/* Values क्रम Action field above */

क्रमागत acpi_wdat_actions अणु
	ACPI_WDAT_RESET = 1,
	ACPI_WDAT_GET_CURRENT_COUNTDOWN = 4,
	ACPI_WDAT_GET_COUNTDOWN = 5,
	ACPI_WDAT_SET_COUNTDOWN = 6,
	ACPI_WDAT_GET_RUNNING_STATE = 8,
	ACPI_WDAT_SET_RUNNING_STATE = 9,
	ACPI_WDAT_GET_STOPPED_STATE = 10,
	ACPI_WDAT_SET_STOPPED_STATE = 11,
	ACPI_WDAT_GET_REBOOT = 16,
	ACPI_WDAT_SET_REBOOT = 17,
	ACPI_WDAT_GET_SHUTDOWN = 18,
	ACPI_WDAT_SET_SHUTDOWN = 19,
	ACPI_WDAT_GET_STATUS = 32,
	ACPI_WDAT_SET_STATUS = 33,
	ACPI_WDAT_ACTION_RESERVED = 34	/* 34 and greater are reserved */
पूर्ण;

/* Values क्रम Inकाष्ठाion field above */

क्रमागत acpi_wdat_inकाष्ठाions अणु
	ACPI_WDAT_READ_VALUE = 0,
	ACPI_WDAT_READ_COUNTDOWN = 1,
	ACPI_WDAT_WRITE_VALUE = 2,
	ACPI_WDAT_WRITE_COUNTDOWN = 3,
	ACPI_WDAT_INSTRUCTION_RESERVED = 4,	/* 4 and greater are reserved */
	ACPI_WDAT_PRESERVE_REGISTER = 0x80	/* Except क्रम this value */
पूर्ण;

/*******************************************************************************
 *
 * WDDT - Watchकरोg Descriptor Table
 *        Version 1
 *
 * Conक्रमms to "Using the Intel ICH Family Watchdog Timer (WDT)",
 * Version 001, September 2002
 *
 ******************************************************************************/

काष्ठा acpi_table_wddt अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
	u16 spec_version;
	u16 table_version;
	u16 pci_venकरोr_id;
	काष्ठा acpi_generic_address address;
	u16 max_count;		/* Maximum counter value supported */
	u16 min_count;		/* Minimum counter value supported */
	u16 period;
	u16 status;
	u16 capability;
पूर्ण;

/* Flags क्रम Status field above */

#घोषणा ACPI_WDDT_AVAILABLE     (1)
#घोषणा ACPI_WDDT_ACTIVE        (1<<1)
#घोषणा ACPI_WDDT_TCO_OS_OWNED  (1<<2)
#घोषणा ACPI_WDDT_USER_RESET    (1<<11)
#घोषणा ACPI_WDDT_WDT_RESET     (1<<12)
#घोषणा ACPI_WDDT_POWER_FAIL    (1<<13)
#घोषणा ACPI_WDDT_UNKNOWN_RESET (1<<14)

/* Flags क्रम Capability field above */

#घोषणा ACPI_WDDT_AUTO_RESET    (1)
#घोषणा ACPI_WDDT_ALERT_SUPPORT (1<<1)

/*******************************************************************************
 *
 * WDRT - Watchकरोg Resource Table
 *        Version 1
 *
 * Conक्रमms to "Watchdog Timer Hardware Requirements for Windows Server 2003",
 * Version 1.01, August 28, 2006
 *
 ******************************************************************************/

काष्ठा acpi_table_wdrt अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
	काष्ठा acpi_generic_address control_रेजिस्टर;
	काष्ठा acpi_generic_address count_रेजिस्टर;
	u16 pci_device_id;
	u16 pci_venकरोr_id;
	u8 pci_bus;		/* PCI Bus number */
	u8 pci_device;		/* PCI Device number */
	u8 pci_function;	/* PCI Function number */
	u8 pci_segment;		/* PCI Segment number */
	u16 max_count;		/* Maximum counter value supported */
	u8 units;
पूर्ण;

/*******************************************************************************
 *
 * WPBT - Winकरोws Platक्रमm Environment Table (ACPI 6.0)
 *        Version 1
 *
 * Conक्रमms to "Windows Platform Binary Table (WPBT)" 29 November 2011
 *
 ******************************************************************************/

काष्ठा acpi_table_wpbt अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
	u32 hanकरोff_size;
	u64 hanकरोff_address;
	u8 layout;
	u8 type;
	u16 arguments_length;
पूर्ण;

/*******************************************************************************
 *
 * WSMT - Winकरोws SMM Security Mitigations Table
 *        Version 1
 *
 * Conक्रमms to "Windows SMM Security Mitigations Table",
 * Version 1.0, April 18, 2016
 *
 ******************************************************************************/

काष्ठा acpi_table_wsmt अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
	u32 protection_flags;
पूर्ण;

/* Flags क्रम protection_flags field above */

#घोषणा ACPI_WSMT_FIXED_COMM_BUFFERS                (1)
#घोषणा ACPI_WSMT_COMM_BUFFER_NESTED_PTR_PROTECTION (2)
#घोषणा ACPI_WSMT_SYSTEM_RESOURCE_PROTECTION        (4)

/*******************************************************************************
 *
 * XENV - Xen Environment Table (ACPI 6.0)
 *        Version 1
 *
 * Conक्रमms to "ACPI Specification for Xen Environment Table" 4 January 2015
 *
 ******************************************************************************/

काष्ठा acpi_table_xenv अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
	u64 grant_table_address;
	u64 grant_table_size;
	u32 event_पूर्णांकerrupt;
	u8 event_flags;
पूर्ण;

/* Reset to शेष packing */

#आशय pack()

#पूर्ण_अगर				/* __ACTBL3_H__ */
