<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/******************************************************************************
 *
 * Name: actbl2.h - ACPI Table Definitions (tables not in ACPI spec)
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#अगर_अघोषित __ACTBL2_H__
#घोषणा __ACTBL2_H__

/*******************************************************************************
 *
 * Additional ACPI Tables (2)
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
#घोषणा ACPI_SIG_IORT           "IORT"	/* IO Remapping Table */
#घोषणा ACPI_SIG_IVRS           "IVRS"	/* I/O Virtualization Reporting Structure */
#घोषणा ACPI_SIG_LPIT           "LPIT"	/* Low Power Idle Table */
#घोषणा ACPI_SIG_MADT           "APIC"	/* Multiple APIC Description Table */
#घोषणा ACPI_SIG_MCFG           "MCFG"	/* PCI Memory Mapped Configuration table */
#घोषणा ACPI_SIG_MCHI           "MCHI"	/* Management Controller Host Interface table */
#घोषणा ACPI_SIG_MPST           "MPST"	/* Memory Power State Table */
#घोषणा ACPI_SIG_MSCT           "MSCT"	/* Maximum System Characteristics Table */
#घोषणा ACPI_SIG_MSDM           "MSDM"	/* Microsoft Data Management Table */
#घोषणा ACPI_SIG_NFIT           "NFIT"	/* NVDIMM Firmware Interface Table */
#घोषणा ACPI_SIG_PCCT           "PCCT"	/* Platक्रमm Communications Channel Table */
#घोषणा ACPI_SIG_PDTT           "PDTT"	/* Platक्रमm Debug Trigger Table */
#घोषणा ACPI_SIG_PHAT           "PHAT"	/* Platक्रमm Health Assessment Table */
#घोषणा ACPI_SIG_PMTT           "PMTT"	/* Platक्रमm Memory Topology Table */
#घोषणा ACPI_SIG_PPTT           "PPTT"	/* Processor Properties Topology Table */
#घोषणा ACPI_SIG_RASF           "RASF"	/* RAS Feature table */
#घोषणा ACPI_SIG_SBST           "SBST"	/* Smart Battery Specअगरication Table */
#घोषणा ACPI_SIG_SDEI           "SDEI"	/* Software Delegated Exception Interface Table */
#घोषणा ACPI_SIG_SDEV           "SDEV"	/* Secure Devices table */
#घोषणा ACPI_SIG_NHLT           "NHLT"	/* Non-HDAudio Link Table */

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
 * IORT - IO Remapping Table
 *
 * Conक्रमms to "IO Remapping Table System Software on ARM Platforms",
 * Document number: ARM DEN 0049E.b, Feb 2021
 *
 ******************************************************************************/

काष्ठा acpi_table_iort अणु
	काष्ठा acpi_table_header header;
	u32 node_count;
	u32 node_offset;
	u32 reserved;
पूर्ण;

/*
 * IORT subtables
 */
काष्ठा acpi_iort_node अणु
	u8 type;
	u16 length;
	u8 revision;
	u32 identअगरier;
	u32 mapping_count;
	u32 mapping_offset;
	अक्षर node_data[1];
पूर्ण;

/* Values क्रम subtable Type above */

क्रमागत acpi_iort_node_type अणु
	ACPI_IORT_NODE_ITS_GROUP = 0x00,
	ACPI_IORT_NODE_NAMED_COMPONENT = 0x01,
	ACPI_IORT_NODE_PCI_ROOT_COMPLEX = 0x02,
	ACPI_IORT_NODE_SMMU = 0x03,
	ACPI_IORT_NODE_SMMU_V3 = 0x04,
	ACPI_IORT_NODE_PMCG = 0x05,
	ACPI_IORT_NODE_RMR = 0x06,
पूर्ण;

काष्ठा acpi_iort_id_mapping अणु
	u32 input_base;		/* Lowest value in input range */
	u32 id_count;		/* Number of IDs */
	u32 output_base;	/* Lowest value in output range */
	u32 output_reference;	/* A reference to the output node */
	u32 flags;
पूर्ण;

/* Masks क्रम Flags field above क्रम IORT subtable */

#घोषणा ACPI_IORT_ID_SINGLE_MAPPING (1)

काष्ठा acpi_iort_memory_access अणु
	u32 cache_coherency;
	u8 hपूर्णांकs;
	u16 reserved;
	u8 memory_flags;
पूर्ण;

/* Values क्रम cache_coherency field above */

#घोषणा ACPI_IORT_NODE_COHERENT         0x00000001	/* The device node is fully coherent */
#घोषणा ACPI_IORT_NODE_NOT_COHERENT     0x00000000	/* The device node is not coherent */

/* Masks क्रम Hपूर्णांकs field above */

#घोषणा ACPI_IORT_HT_TRANSIENT          (1)
#घोषणा ACPI_IORT_HT_WRITE              (1<<1)
#घोषणा ACPI_IORT_HT_READ               (1<<2)
#घोषणा ACPI_IORT_HT_OVERRIDE           (1<<3)

/* Masks क्रम memory_flags field above */

#घोषणा ACPI_IORT_MF_COHERENCY          (1)
#घोषणा ACPI_IORT_MF_ATTRIBUTES         (1<<1)

/*
 * IORT node specअगरic subtables
 */
काष्ठा acpi_iort_its_group अणु
	u32 its_count;
	u32 identअगरiers[1];	/* GIC ITS identअगरier array */
पूर्ण;

काष्ठा acpi_iort_named_component अणु
	u32 node_flags;
	u64 memory_properties;	/* Memory access properties */
	u8 memory_address_limit;	/* Memory address size limit */
	अक्षर device_name[1];	/* Path of namespace object */
पूर्ण;

/* Masks क्रम Flags field above */

#घोषणा ACPI_IORT_NC_STALL_SUPPORTED    (1)
#घोषणा ACPI_IORT_NC_PASID_BITS         (31<<1)

काष्ठा acpi_iort_root_complex अणु
	u64 memory_properties;	/* Memory access properties */
	u32 ats_attribute;
	u32 pci_segment_number;
	u8 memory_address_limit;	/* Memory address size limit */
	u8 reserved[3];		/* Reserved, must be zero */
पूर्ण;

/* Masks क्रम ats_attribute field above */

#घोषणा ACPI_IORT_ATS_SUPPORTED         (1)	/* The root complex ATS support */
#घोषणा ACPI_IORT_PRI_SUPPORTED         (1<<1)	/* The root complex PRI support */
#घोषणा ACPI_IORT_PASID_FWD_SUPPORTED   (1<<2)	/* The root complex PASID क्रमward support */

काष्ठा acpi_iort_smmu अणु
	u64 base_address;	/* SMMU base address */
	u64 span;		/* Length of memory range */
	u32 model;
	u32 flags;
	u32 global_पूर्णांकerrupt_offset;
	u32 context_पूर्णांकerrupt_count;
	u32 context_पूर्णांकerrupt_offset;
	u32 pmu_पूर्णांकerrupt_count;
	u32 pmu_पूर्णांकerrupt_offset;
	u64 पूर्णांकerrupts[1];	/* Interrupt array */
पूर्ण;

/* Values क्रम Model field above */

#घोषणा ACPI_IORT_SMMU_V1               0x00000000	/* Generic SMMUv1 */
#घोषणा ACPI_IORT_SMMU_V2               0x00000001	/* Generic SMMUv2 */
#घोषणा ACPI_IORT_SMMU_CORELINK_MMU400  0x00000002	/* ARM Corelink MMU-400 */
#घोषणा ACPI_IORT_SMMU_CORELINK_MMU500  0x00000003	/* ARM Corelink MMU-500 */
#घोषणा ACPI_IORT_SMMU_CORELINK_MMU401  0x00000004	/* ARM Corelink MMU-401 */
#घोषणा ACPI_IORT_SMMU_CAVIUM_THUNDERX  0x00000005	/* Cavium thunder_x SMMUv2 */

/* Masks क्रम Flags field above */

#घोषणा ACPI_IORT_SMMU_DVM_SUPPORTED    (1)
#घोषणा ACPI_IORT_SMMU_COHERENT_WALK    (1<<1)

/* Global पूर्णांकerrupt क्रमmat */

काष्ठा acpi_iort_smmu_gsi अणु
	u32 nsg_irpt;
	u32 nsg_irpt_flags;
	u32 nsg_cfg_irpt;
	u32 nsg_cfg_irpt_flags;
पूर्ण;

काष्ठा acpi_iort_smmu_v3 अणु
	u64 base_address;	/* SMMUv3 base address */
	u32 flags;
	u32 reserved;
	u64 vatos_address;
	u32 model;
	u32 event_gsiv;
	u32 pri_gsiv;
	u32 gerr_gsiv;
	u32 sync_gsiv;
	u32 pxm;
	u32 id_mapping_index;
पूर्ण;

/* Values क्रम Model field above */

#घोषणा ACPI_IORT_SMMU_V3_GENERIC           0x00000000	/* Generic SMMUv3 */
#घोषणा ACPI_IORT_SMMU_V3_HISILICON_HI161X  0x00000001	/* hi_silicon Hi161x SMMUv3 */
#घोषणा ACPI_IORT_SMMU_V3_CAVIUM_CN99XX     0x00000002	/* Cavium CN99xx SMMUv3 */

/* Masks क्रम Flags field above */

#घोषणा ACPI_IORT_SMMU_V3_COHACC_OVERRIDE   (1)
#घोषणा ACPI_IORT_SMMU_V3_HTTU_OVERRIDE     (3<<1)
#घोषणा ACPI_IORT_SMMU_V3_PXM_VALID         (1<<3)

काष्ठा acpi_iort_pmcg अणु
	u64 page0_base_address;
	u32 overflow_gsiv;
	u32 node_reference;
	u64 page1_base_address;
पूर्ण;

काष्ठा acpi_iort_rmr अणु
	u32 flags;
	u32 rmr_count;
	u32 rmr_offset;
पूर्ण;

काष्ठा acpi_iort_rmr_desc अणु
	u64 base_address;
	u64 length;
	u32 reserved;
पूर्ण;

/*******************************************************************************
 *
 * IVRS - I/O Virtualization Reporting Structure
 *        Version 1
 *
 * Conक्रमms to "AMD I/O Virtualization Technology (IOMMU) Specification",
 * Revision 1.26, February 2009.
 *
 ******************************************************************************/

काष्ठा acpi_table_ivrs अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
	u32 info;		/* Common भवization info */
	u64 reserved;
पूर्ण;

/* Values क्रम Info field above */

#घोषणा ACPI_IVRS_PHYSICAL_SIZE     0x00007F00	/* 7 bits, physical address size */
#घोषणा ACPI_IVRS_VIRTUAL_SIZE      0x003F8000	/* 7 bits, भव address size */
#घोषणा ACPI_IVRS_ATS_RESERVED      0x00400000	/* ATS address translation range reserved */

/* IVRS subtable header */

काष्ठा acpi_ivrs_header अणु
	u8 type;		/* Subtable type */
	u8 flags;
	u16 length;		/* Subtable length */
	u16 device_id;		/* ID of IOMMU */
पूर्ण;

/* Values क्रम subtable Type above */

क्रमागत acpi_ivrs_type अणु
	ACPI_IVRS_TYPE_HARDWARE1 = 0x10,
	ACPI_IVRS_TYPE_HARDWARE2 = 0x11,
	ACPI_IVRS_TYPE_HARDWARE3 = 0x40,
	ACPI_IVRS_TYPE_MEMORY1 = 0x20,
	ACPI_IVRS_TYPE_MEMORY2 = 0x21,
	ACPI_IVRS_TYPE_MEMORY3 = 0x22
पूर्ण;

/* Masks क्रम Flags field above क्रम IVHD subtable */

#घोषणा ACPI_IVHD_TT_ENABLE         (1)
#घोषणा ACPI_IVHD_PASS_PW           (1<<1)
#घोषणा ACPI_IVHD_RES_PASS_PW       (1<<2)
#घोषणा ACPI_IVHD_ISOC              (1<<3)
#घोषणा ACPI_IVHD_IOTLB             (1<<4)

/* Masks क्रम Flags field above क्रम IVMD subtable */

#घोषणा ACPI_IVMD_UNITY             (1)
#घोषणा ACPI_IVMD_READ              (1<<1)
#घोषणा ACPI_IVMD_WRITE             (1<<2)
#घोषणा ACPI_IVMD_EXCLUSION_RANGE   (1<<3)

/*
 * IVRS subtables, correspond to Type in काष्ठा acpi_ivrs_header
 */

/* 0x10: I/O Virtualization Hardware Definition Block (IVHD) */

काष्ठा acpi_ivrs_hardware_10 अणु
	काष्ठा acpi_ivrs_header header;
	u16 capability_offset;	/* Offset क्रम IOMMU control fields */
	u64 base_address;	/* IOMMU control रेजिस्टरs */
	u16 pci_segment_group;
	u16 info;		/* MSI number and unit ID */
	u32 feature_reporting;
पूर्ण;

/* 0x11: I/O Virtualization Hardware Definition Block (IVHD) */

काष्ठा acpi_ivrs_hardware_11 अणु
	काष्ठा acpi_ivrs_header header;
	u16 capability_offset;	/* Offset क्रम IOMMU control fields */
	u64 base_address;	/* IOMMU control रेजिस्टरs */
	u16 pci_segment_group;
	u16 info;		/* MSI number and unit ID */
	u32 attributes;
	u64 efr_रेजिस्टर_image;
	u64 reserved;
पूर्ण;

/* Masks क्रम Info field above */

#घोषणा ACPI_IVHD_MSI_NUMBER_MASK   0x001F	/* 5 bits, MSI message number */
#घोषणा ACPI_IVHD_UNIT_ID_MASK      0x1F00	/* 5 bits, unit_ID */

/*
 * Device Entries क्रम IVHD subtable, appear after काष्ठा acpi_ivrs_hardware काष्ठाure.
 * Upper two bits of the Type field are the (encoded) length of the काष्ठाure.
 * Currently, only 4 and 8 byte entries are defined. 16 and 32 byte entries
 * are reserved क्रम future use but not defined.
 */
काष्ठा acpi_ivrs_de_header अणु
	u8 type;
	u16 id;
	u8 data_setting;
पूर्ण;

/* Length of device entry is in the top two bits of Type field above */

#घोषणा ACPI_IVHD_ENTRY_LENGTH      0xC0

/* Values क्रम device entry Type field above */

क्रमागत acpi_ivrs_device_entry_type अणु
	/* 4-byte device entries, all use काष्ठा acpi_ivrs_device4 */

	ACPI_IVRS_TYPE_PAD4 = 0,
	ACPI_IVRS_TYPE_ALL = 1,
	ACPI_IVRS_TYPE_SELECT = 2,
	ACPI_IVRS_TYPE_START = 3,
	ACPI_IVRS_TYPE_END = 4,

	/* 8-byte device entries */

	ACPI_IVRS_TYPE_PAD8 = 64,
	ACPI_IVRS_TYPE_NOT_USED = 65,
	ACPI_IVRS_TYPE_ALIAS_SELECT = 66,	/* Uses काष्ठा acpi_ivrs_device8a */
	ACPI_IVRS_TYPE_ALIAS_START = 67,	/* Uses काष्ठा acpi_ivrs_device8a */
	ACPI_IVRS_TYPE_EXT_SELECT = 70,	/* Uses काष्ठा acpi_ivrs_device8b */
	ACPI_IVRS_TYPE_EXT_START = 71,	/* Uses काष्ठा acpi_ivrs_device8b */
	ACPI_IVRS_TYPE_SPECIAL = 72,	/* Uses काष्ठा acpi_ivrs_device8c */

	/* Variable-length device entries */

	ACPI_IVRS_TYPE_HID = 240	/* Uses ACPI_IVRS_DEVICE_HID */
पूर्ण;

/* Values क्रम Data field above */

#घोषणा ACPI_IVHD_INIT_PASS         (1)
#घोषणा ACPI_IVHD_EINT_PASS         (1<<1)
#घोषणा ACPI_IVHD_NMI_PASS          (1<<2)
#घोषणा ACPI_IVHD_SYSTEM_MGMT       (3<<4)
#घोषणा ACPI_IVHD_LINT0_PASS        (1<<6)
#घोषणा ACPI_IVHD_LINT1_PASS        (1<<7)

/* Types 0-4: 4-byte device entry */

काष्ठा acpi_ivrs_device4 अणु
	काष्ठा acpi_ivrs_de_header header;
पूर्ण;

/* Types 66-67: 8-byte device entry */

काष्ठा acpi_ivrs_device8a अणु
	काष्ठा acpi_ivrs_de_header header;
	u8 reserved1;
	u16 used_id;
	u8 reserved2;
पूर्ण;

/* Types 70-71: 8-byte device entry */

काष्ठा acpi_ivrs_device8b अणु
	काष्ठा acpi_ivrs_de_header header;
	u32 extended_data;
पूर्ण;

/* Values क्रम extended_data above */

#घोषणा ACPI_IVHD_ATS_DISABLED      (1<<31)

/* Type 72: 8-byte device entry */

काष्ठा acpi_ivrs_device8c अणु
	काष्ठा acpi_ivrs_de_header header;
	u8 handle;
	u16 used_id;
	u8 variety;
पूर्ण;

/* Values क्रम Variety field above */

#घोषणा ACPI_IVHD_IOAPIC            1
#घोषणा ACPI_IVHD_HPET              2

/* Type 240: variable-length device entry */

काष्ठा acpi_ivrs_device_hid अणु
	काष्ठा acpi_ivrs_de_header header;
	u64 acpi_hid;
	u64 acpi_cid;
	u8 uid_type;
	u8 uid_length;
पूर्ण;

/* 0x20, 0x21, 0x22: I/O Virtualization Memory Definition Block (IVMD) */

काष्ठा acpi_ivrs_memory अणु
	काष्ठा acpi_ivrs_header header;
	u16 aux_data;
	u64 reserved;
	u64 start_address;
	u64 memory_length;
पूर्ण;

/*******************************************************************************
 *
 * LPIT - Low Power Idle Table
 *
 * Conक्रमms to "ACPI Low Power Idle Table (LPIT)" July 2014.
 *
 ******************************************************************************/

काष्ठा acpi_table_lpit अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
पूर्ण;

/* LPIT subtable header */

काष्ठा acpi_lpit_header अणु
	u32 type;		/* Subtable type */
	u32 length;		/* Subtable length */
	u16 unique_id;
	u16 reserved;
	u32 flags;
पूर्ण;

/* Values क्रम subtable Type above */

क्रमागत acpi_lpit_type अणु
	ACPI_LPIT_TYPE_NATIVE_CSTATE = 0x00,
	ACPI_LPIT_TYPE_RESERVED = 0x01	/* 1 and above are reserved */
पूर्ण;

/* Masks क्रम Flags field above  */

#घोषणा ACPI_LPIT_STATE_DISABLED    (1)
#घोषणा ACPI_LPIT_NO_COUNTER        (1<<1)

/*
 * LPIT subtables, correspond to Type in काष्ठा acpi_lpit_header
 */

/* 0x00: Native C-state inकाष्ठाion based LPI काष्ठाure */

काष्ठा acpi_lpit_native अणु
	काष्ठा acpi_lpit_header header;
	काष्ठा acpi_generic_address entry_trigger;
	u32 residency;
	u32 latency;
	काष्ठा acpi_generic_address residency_counter;
	u64 counter_frequency;
पूर्ण;

/*******************************************************************************
 *
 * MADT - Multiple APIC Description Table
 *        Version 3
 *
 ******************************************************************************/

काष्ठा acpi_table_madt अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
	u32 address;		/* Physical address of local APIC */
	u32 flags;
पूर्ण;

/* Masks क्रम Flags field above */

#घोषणा ACPI_MADT_PCAT_COMPAT       (1)	/* 00: System also has dual 8259s */

/* Values क्रम PCATCompat flag */

#घोषणा ACPI_MADT_DUAL_PIC          1
#घोषणा ACPI_MADT_MULTIPLE_APIC     0

/* Values क्रम MADT subtable type in काष्ठा acpi_subtable_header */

क्रमागत acpi_madt_type अणु
	ACPI_MADT_TYPE_LOCAL_APIC = 0,
	ACPI_MADT_TYPE_IO_APIC = 1,
	ACPI_MADT_TYPE_INTERRUPT_OVERRIDE = 2,
	ACPI_MADT_TYPE_NMI_SOURCE = 3,
	ACPI_MADT_TYPE_LOCAL_APIC_NMI = 4,
	ACPI_MADT_TYPE_LOCAL_APIC_OVERRIDE = 5,
	ACPI_MADT_TYPE_IO_SAPIC = 6,
	ACPI_MADT_TYPE_LOCAL_SAPIC = 7,
	ACPI_MADT_TYPE_INTERRUPT_SOURCE = 8,
	ACPI_MADT_TYPE_LOCAL_X2APIC = 9,
	ACPI_MADT_TYPE_LOCAL_X2APIC_NMI = 10,
	ACPI_MADT_TYPE_GENERIC_INTERRUPT = 11,
	ACPI_MADT_TYPE_GENERIC_DISTRIBUTOR = 12,
	ACPI_MADT_TYPE_GENERIC_MSI_FRAME = 13,
	ACPI_MADT_TYPE_GENERIC_REDISTRIBUTOR = 14,
	ACPI_MADT_TYPE_GENERIC_TRANSLATOR = 15,
	ACPI_MADT_TYPE_MULTIPROC_WAKEUP = 16,
	ACPI_MADT_TYPE_RESERVED = 17	/* 17 and greater are reserved */
पूर्ण;

/*
 * MADT Subtables, correspond to Type in काष्ठा acpi_subtable_header
 */

/* 0: Processor Local APIC */

काष्ठा acpi_madt_local_apic अणु
	काष्ठा acpi_subtable_header header;
	u8 processor_id;	/* ACPI processor id */
	u8 id;			/* Processor's local APIC id */
	u32 lapic_flags;
पूर्ण;

/* 1: IO APIC */

काष्ठा acpi_madt_io_apic अणु
	काष्ठा acpi_subtable_header header;
	u8 id;			/* I/O APIC ID */
	u8 reserved;		/* reserved - must be zero */
	u32 address;		/* APIC physical address */
	u32 global_irq_base;	/* Global प्रणाली पूर्णांकerrupt where INTI lines start */
पूर्ण;

/* 2: Interrupt Override */

काष्ठा acpi_madt_पूर्णांकerrupt_override अणु
	काष्ठा acpi_subtable_header header;
	u8 bus;			/* 0 - ISA */
	u8 source_irq;		/* Interrupt source (IRQ) */
	u32 global_irq;		/* Global प्रणाली पूर्णांकerrupt */
	u16 पूर्णांकi_flags;
पूर्ण;

/* 3: NMI Source */

काष्ठा acpi_madt_nmi_source अणु
	काष्ठा acpi_subtable_header header;
	u16 पूर्णांकi_flags;
	u32 global_irq;		/* Global प्रणाली पूर्णांकerrupt */
पूर्ण;

/* 4: Local APIC NMI */

काष्ठा acpi_madt_local_apic_nmi अणु
	काष्ठा acpi_subtable_header header;
	u8 processor_id;	/* ACPI processor id */
	u16 पूर्णांकi_flags;
	u8 lपूर्णांक;		/* LINTn to which NMI is connected */
पूर्ण;

/* 5: Address Override */

काष्ठा acpi_madt_local_apic_override अणु
	काष्ठा acpi_subtable_header header;
	u16 reserved;		/* Reserved, must be zero */
	u64 address;		/* APIC physical address */
पूर्ण;

/* 6: I/O Sapic */

काष्ठा acpi_madt_io_sapic अणु
	काष्ठा acpi_subtable_header header;
	u8 id;			/* I/O SAPIC ID */
	u8 reserved;		/* Reserved, must be zero */
	u32 global_irq_base;	/* Global पूर्णांकerrupt क्रम SAPIC start */
	u64 address;		/* SAPIC physical address */
पूर्ण;

/* 7: Local Sapic */

काष्ठा acpi_madt_local_sapic अणु
	काष्ठा acpi_subtable_header header;
	u8 processor_id;	/* ACPI processor id */
	u8 id;			/* SAPIC ID */
	u8 eid;			/* SAPIC EID */
	u8 reserved[3];		/* Reserved, must be zero */
	u32 lapic_flags;
	u32 uid;		/* Numeric UID - ACPI 3.0 */
	अक्षर uid_string[1];	/* String UID  - ACPI 3.0 */
पूर्ण;

/* 8: Platक्रमm Interrupt Source */

काष्ठा acpi_madt_पूर्णांकerrupt_source अणु
	काष्ठा acpi_subtable_header header;
	u16 पूर्णांकi_flags;
	u8 type;		/* 1=PMI, 2=INIT, 3=corrected */
	u8 id;			/* Processor ID */
	u8 eid;			/* Processor EID */
	u8 io_sapic_vector;	/* Vector value क्रम PMI पूर्णांकerrupts */
	u32 global_irq;		/* Global प्रणाली पूर्णांकerrupt */
	u32 flags;		/* Interrupt Source Flags */
पूर्ण;

/* Masks क्रम Flags field above */

#घोषणा ACPI_MADT_CPEI_OVERRIDE     (1)

/* 9: Processor Local X2APIC (ACPI 4.0) */

काष्ठा acpi_madt_local_x2apic अणु
	काष्ठा acpi_subtable_header header;
	u16 reserved;		/* reserved - must be zero */
	u32 local_apic_id;	/* Processor x2APIC ID  */
	u32 lapic_flags;
	u32 uid;		/* ACPI processor UID */
पूर्ण;

/* 10: Local X2APIC NMI (ACPI 4.0) */

काष्ठा acpi_madt_local_x2apic_nmi अणु
	काष्ठा acpi_subtable_header header;
	u16 पूर्णांकi_flags;
	u32 uid;		/* ACPI processor UID */
	u8 lपूर्णांक;		/* LINTn to which NMI is connected */
	u8 reserved[3];		/* reserved - must be zero */
पूर्ण;

/* 11: Generic पूर्णांकerrupt - GICC (ACPI 5.0 + ACPI 6.0 + ACPI 6.3 changes) */

काष्ठा acpi_madt_generic_पूर्णांकerrupt अणु
	काष्ठा acpi_subtable_header header;
	u16 reserved;		/* reserved - must be zero */
	u32 cpu_पूर्णांकerface_number;
	u32 uid;
	u32 flags;
	u32 parking_version;
	u32 perक्रमmance_पूर्णांकerrupt;
	u64 parked_address;
	u64 base_address;
	u64 gicv_base_address;
	u64 gich_base_address;
	u32 vgic_पूर्णांकerrupt;
	u64 gicr_base_address;
	u64 arm_mpidr;
	u8 efficiency_class;
	u8 reserved2[1];
	u16 spe_पूर्णांकerrupt;	/* ACPI 6.3 */
पूर्ण;

/* Masks क्रम Flags field above */

/* ACPI_MADT_ENABLED                    (1)      Processor is usable अगर set */
#घोषणा ACPI_MADT_PERFORMANCE_IRQ_MODE  (1<<1)	/* 01: Perक्रमmance Interrupt Mode */
#घोषणा ACPI_MADT_VGIC_IRQ_MODE         (1<<2)	/* 02: VGIC Maपूर्णांकenance Interrupt mode */

/* 12: Generic Distributor (ACPI 5.0 + ACPI 6.0 changes) */

काष्ठा acpi_madt_generic_distributor अणु
	काष्ठा acpi_subtable_header header;
	u16 reserved;		/* reserved - must be zero */
	u32 gic_id;
	u64 base_address;
	u32 global_irq_base;
	u8 version;
	u8 reserved2[3];	/* reserved - must be zero */
पूर्ण;

/* Values क्रम Version field above */

क्रमागत acpi_madt_gic_version अणु
	ACPI_MADT_GIC_VERSION_NONE = 0,
	ACPI_MADT_GIC_VERSION_V1 = 1,
	ACPI_MADT_GIC_VERSION_V2 = 2,
	ACPI_MADT_GIC_VERSION_V3 = 3,
	ACPI_MADT_GIC_VERSION_V4 = 4,
	ACPI_MADT_GIC_VERSION_RESERVED = 5	/* 5 and greater are reserved */
पूर्ण;

/* 13: Generic MSI Frame (ACPI 5.1) */

काष्ठा acpi_madt_generic_msi_frame अणु
	काष्ठा acpi_subtable_header header;
	u16 reserved;		/* reserved - must be zero */
	u32 msi_frame_id;
	u64 base_address;
	u32 flags;
	u16 spi_count;
	u16 spi_base;
पूर्ण;

/* Masks क्रम Flags field above */

#घोषणा ACPI_MADT_OVERRIDE_SPI_VALUES   (1)

/* 14: Generic Redistributor (ACPI 5.1) */

काष्ठा acpi_madt_generic_redistributor अणु
	काष्ठा acpi_subtable_header header;
	u16 reserved;		/* reserved - must be zero */
	u64 base_address;
	u32 length;
पूर्ण;

/* 15: Generic Translator (ACPI 6.0) */

काष्ठा acpi_madt_generic_translator अणु
	काष्ठा acpi_subtable_header header;
	u16 reserved;		/* reserved - must be zero */
	u32 translation_id;
	u64 base_address;
	u32 reserved2;
पूर्ण;

/* 16: Multiprocessor wakeup (ACPI 6.4) */

काष्ठा acpi_madt_multiproc_wakeup अणु
	काष्ठा acpi_subtable_header header;
	u16 mailbox_version;
	u32 reserved;		/* reserved - must be zero */
	u64 base_address;
पूर्ण;

/*
 * Common flags fields क्रम MADT subtables
 */

/* MADT Local APIC flags */

#घोषणा ACPI_MADT_ENABLED           (1)	/* 00: Processor is usable अगर set */

/* MADT MPS INTI flags (पूर्णांकi_flags) */

#घोषणा ACPI_MADT_POLARITY_MASK     (3)	/* 00-01: Polarity of APIC I/O input संकेतs */
#घोषणा ACPI_MADT_TRIGGER_MASK      (3<<2)	/* 02-03: Trigger mode of APIC input संकेतs */

/* Values क्रम MPS INTI flags */

#घोषणा ACPI_MADT_POLARITY_CONFORMS       0
#घोषणा ACPI_MADT_POLARITY_ACTIVE_HIGH    1
#घोषणा ACPI_MADT_POLARITY_RESERVED       2
#घोषणा ACPI_MADT_POLARITY_ACTIVE_LOW     3

#घोषणा ACPI_MADT_TRIGGER_CONFORMS        (0)
#घोषणा ACPI_MADT_TRIGGER_EDGE            (1<<2)
#घोषणा ACPI_MADT_TRIGGER_RESERVED        (2<<2)
#घोषणा ACPI_MADT_TRIGGER_LEVEL           (3<<2)

/*******************************************************************************
 *
 * MCFG - PCI Memory Mapped Configuration table and subtable
 *        Version 1
 *
 * Conक्रमms to "PCI Firmware Specification", Revision 3.0, June 20, 2005
 *
 ******************************************************************************/

काष्ठा acpi_table_mcfg अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
	u8 reserved[8];
पूर्ण;

/* Subtable */

काष्ठा acpi_mcfg_allocation अणु
	u64 address;		/* Base address, processor-relative */
	u16 pci_segment;	/* PCI segment group number */
	u8 start_bus_number;	/* Starting PCI Bus number */
	u8 end_bus_number;	/* Final PCI Bus number */
	u32 reserved;
पूर्ण;

/*******************************************************************************
 *
 * MCHI - Management Controller Host Interface Table
 *        Version 1
 *
 * Conक्रमms to "Management Component Transport Protocol (MCTP) Host
 * Interface Specअगरication", Revision 1.0.0a, October 13, 2009
 *
 ******************************************************************************/

काष्ठा acpi_table_mchi अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
	u8 पूर्णांकerface_type;
	u8 protocol;
	u64 protocol_data;
	u8 पूर्णांकerrupt_type;
	u8 gpe;
	u8 pci_device_flag;
	u32 global_पूर्णांकerrupt;
	काष्ठा acpi_generic_address control_रेजिस्टर;
	u8 pci_segment;
	u8 pci_bus;
	u8 pci_device;
	u8 pci_function;
पूर्ण;

/*******************************************************************************
 *
 * MPST - Memory Power State Table (ACPI 5.0)
 *        Version 1
 *
 ******************************************************************************/

#घोषणा ACPI_MPST_CHANNEL_INFO \
	u8                              channel_id; \
	u8                              reserved1[3]; \
	u16                             घातer_node_count; \
	u16                             reserved2;

/* Main table */

काष्ठा acpi_table_mpst अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
	 ACPI_MPST_CHANNEL_INFO	/* Platक्रमm Communication Channel */
पूर्ण;

/* Memory Platक्रमm Communication Channel Info */

काष्ठा acpi_mpst_channel अणु
	ACPI_MPST_CHANNEL_INFO	/* Platक्रमm Communication Channel */
पूर्ण;

/* Memory Power Node Structure */

काष्ठा acpi_mpst_घातer_node अणु
	u8 flags;
	u8 reserved1;
	u16 node_id;
	u32 length;
	u64 range_address;
	u64 range_length;
	u32 num_घातer_states;
	u32 num_physical_components;
पूर्ण;

/* Values क्रम Flags field above */

#घोषणा ACPI_MPST_ENABLED               1
#घोषणा ACPI_MPST_POWER_MANAGED         2
#घोषणा ACPI_MPST_HOT_PLUG_CAPABLE      4

/* Memory Power State Structure (follows POWER_NODE above) */

काष्ठा acpi_mpst_घातer_state अणु
	u8 घातer_state;
	u8 info_index;
पूर्ण;

/* Physical Component ID Structure (follows POWER_STATE above) */

काष्ठा acpi_mpst_component अणु
	u16 component_id;
पूर्ण;

/* Memory Power State Characteristics Structure (follows all POWER_NODEs) */

काष्ठा acpi_mpst_data_hdr अणु
	u16 अक्षरacteristics_count;
	u16 reserved;
पूर्ण;

काष्ठा acpi_mpst_घातer_data अणु
	u8 काष्ठाure_id;
	u8 flags;
	u16 reserved1;
	u32 average_घातer;
	u32 घातer_saving;
	u64 निकास_latency;
	u64 reserved2;
पूर्ण;

/* Values क्रम Flags field above */

#घोषणा ACPI_MPST_PRESERVE              1
#घोषणा ACPI_MPST_AUTOENTRY             2
#घोषणा ACPI_MPST_AUTOEXIT              4

/* Shared Memory Region (not part of an ACPI table) */

काष्ठा acpi_mpst_shared अणु
	u32 signature;
	u16 pcc_command;
	u16 pcc_status;
	u32 command_रेजिस्टर;
	u32 status_रेजिस्टर;
	u32 घातer_state_id;
	u32 घातer_node_id;
	u64 energy_consumed;
	u64 average_घातer;
पूर्ण;

/*******************************************************************************
 *
 * MSCT - Maximum System Characteristics Table (ACPI 4.0)
 *        Version 1
 *
 ******************************************************************************/

काष्ठा acpi_table_msct अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
	u32 proximity_offset;	/* Location of proximity info काष्ठा(s) */
	u32 max_proximity_करोमुख्यs;	/* Max number of proximity करोमुख्यs */
	u32 max_घड़ी_करोमुख्यs;	/* Max number of घड़ी करोमुख्यs */
	u64 max_address;	/* Max physical address in प्रणाली */
पूर्ण;

/* subtable - Maximum Proximity Doमुख्य Inक्रमmation. Version 1 */

काष्ठा acpi_msct_proximity अणु
	u8 revision;
	u8 length;
	u32 range_start;	/* Start of करोमुख्य range */
	u32 range_end;		/* End of करोमुख्य range */
	u32 processor_capacity;
	u64 memory_capacity;	/* In bytes */
पूर्ण;

/*******************************************************************************
 *
 * MSDM - Microsoft Data Management table
 *
 * Conक्रमms to "Microsoft Software Licensing Tables (SLIC and MSDM)",
 * November 29, 2011. Copyright 2011 Microsoft
 *
 ******************************************************************************/

/* Basic MSDM table is only the common ACPI header */

काष्ठा acpi_table_msdm अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
पूर्ण;

/*******************************************************************************
 *
 * NFIT - NVDIMM Interface Table (ACPI 6.0+)
 *        Version 1
 *
 ******************************************************************************/

काष्ठा acpi_table_nfit अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
	u32 reserved;		/* Reserved, must be zero */
पूर्ण;

/* Subtable header क्रम NFIT */

काष्ठा acpi_nfit_header अणु
	u16 type;
	u16 length;
पूर्ण;

/* Values क्रम subtable type in काष्ठा acpi_nfit_header */

क्रमागत acpi_nfit_type अणु
	ACPI_NFIT_TYPE_SYSTEM_ADDRESS = 0,
	ACPI_NFIT_TYPE_MEMORY_MAP = 1,
	ACPI_NFIT_TYPE_INTERLEAVE = 2,
	ACPI_NFIT_TYPE_SMBIOS = 3,
	ACPI_NFIT_TYPE_CONTROL_REGION = 4,
	ACPI_NFIT_TYPE_DATA_REGION = 5,
	ACPI_NFIT_TYPE_FLUSH_ADDRESS = 6,
	ACPI_NFIT_TYPE_CAPABILITIES = 7,
	ACPI_NFIT_TYPE_RESERVED = 8	/* 8 and greater are reserved */
पूर्ण;

/*
 * NFIT Subtables
 */

/* 0: System Physical Address Range Structure */

काष्ठा acpi_nfit_प्रणाली_address अणु
	काष्ठा acpi_nfit_header header;
	u16 range_index;
	u16 flags;
	u32 reserved;		/* Reserved, must be zero */
	u32 proximity_करोमुख्य;
	u8 range_guid[16];
	u64 address;
	u64 length;
	u64 memory_mapping;
	u64 location_cookie;	/* ACPI 6.4 */
पूर्ण;

/* Flags */

#घोषणा ACPI_NFIT_ADD_ONLINE_ONLY       (1)	/* 00: Add/Online Operation Only */
#घोषणा ACPI_NFIT_PROXIMITY_VALID       (1<<1)	/* 01: Proximity Doमुख्य Valid */
#घोषणा ACPI_NFIT_LOCATION_COOKIE_VALID (1<<2)	/* 02: SPA location cookie valid (ACPI 6.4) */

/* Range Type GUIDs appear in the include/acuuid.h file */

/* 1: Memory Device to System Address Range Map Structure */

काष्ठा acpi_nfit_memory_map अणु
	काष्ठा acpi_nfit_header header;
	u32 device_handle;
	u16 physical_id;
	u16 region_id;
	u16 range_index;
	u16 region_index;
	u64 region_size;
	u64 region_offset;
	u64 address;
	u16 पूर्णांकerleave_index;
	u16 पूर्णांकerleave_ways;
	u16 flags;
	u16 reserved;		/* Reserved, must be zero */
पूर्ण;

/* Flags */

#घोषणा ACPI_NFIT_MEM_SAVE_FAILED       (1)	/* 00: Last SAVE to Memory Device failed */
#घोषणा ACPI_NFIT_MEM_RESTORE_FAILED    (1<<1)	/* 01: Last RESTORE from Memory Device failed */
#घोषणा ACPI_NFIT_MEM_FLUSH_FAILED      (1<<2)	/* 02: Platक्रमm flush failed */
#घोषणा ACPI_NFIT_MEM_NOT_ARMED         (1<<3)	/* 03: Memory Device is not armed */
#घोषणा ACPI_NFIT_MEM_HEALTH_OBSERVED   (1<<4)	/* 04: Memory Device observed SMART/health events */
#घोषणा ACPI_NFIT_MEM_HEALTH_ENABLED    (1<<5)	/* 05: SMART/health events enabled */
#घोषणा ACPI_NFIT_MEM_MAP_FAILED        (1<<6)	/* 06: Mapping to SPA failed */

/* 2: Interleave Structure */

काष्ठा acpi_nfit_पूर्णांकerleave अणु
	काष्ठा acpi_nfit_header header;
	u16 पूर्णांकerleave_index;
	u16 reserved;		/* Reserved, must be zero */
	u32 line_count;
	u32 line_size;
	u32 line_offset[1];	/* Variable length */
पूर्ण;

/* 3: SMBIOS Management Inक्रमmation Structure */

काष्ठा acpi_nfit_smbios अणु
	काष्ठा acpi_nfit_header header;
	u32 reserved;		/* Reserved, must be zero */
	u8 data[1];		/* Variable length */
पूर्ण;

/* 4: NVDIMM Control Region Structure */

काष्ठा acpi_nfit_control_region अणु
	काष्ठा acpi_nfit_header header;
	u16 region_index;
	u16 venकरोr_id;
	u16 device_id;
	u16 revision_id;
	u16 subप्रणाली_venकरोr_id;
	u16 subप्रणाली_device_id;
	u16 subप्रणाली_revision_id;
	u8 valid_fields;
	u8 manufacturing_location;
	u16 manufacturing_date;
	u8 reserved[2];		/* Reserved, must be zero */
	u32 serial_number;
	u16 code;
	u16 winकरोws;
	u64 winकरोw_size;
	u64 command_offset;
	u64 command_size;
	u64 status_offset;
	u64 status_size;
	u16 flags;
	u8 reserved1[6];	/* Reserved, must be zero */
पूर्ण;

/* Flags */

#घोषणा ACPI_NFIT_CONTROL_BUFFERED          (1)	/* Block Data Winकरोws implementation is buffered */

/* valid_fields bits */

#घोषणा ACPI_NFIT_CONTROL_MFG_INFO_VALID    (1)	/* Manufacturing fields are valid */

/* 5: NVDIMM Block Data Winकरोw Region Structure */

काष्ठा acpi_nfit_data_region अणु
	काष्ठा acpi_nfit_header header;
	u16 region_index;
	u16 winकरोws;
	u64 offset;
	u64 size;
	u64 capacity;
	u64 start_address;
पूर्ण;

/* 6: Flush Hपूर्णांक Address Structure */

काष्ठा acpi_nfit_flush_address अणु
	काष्ठा acpi_nfit_header header;
	u32 device_handle;
	u16 hपूर्णांक_count;
	u8 reserved[6];		/* Reserved, must be zero */
	u64 hपूर्णांक_address[1];	/* Variable length */
पूर्ण;

/* 7: Platक्रमm Capabilities Structure */

काष्ठा acpi_nfit_capabilities अणु
	काष्ठा acpi_nfit_header header;
	u8 highest_capability;
	u8 reserved[3];		/* Reserved, must be zero */
	u32 capabilities;
	u32 reserved2;
पूर्ण;

/* Capabilities Flags */

#घोषणा ACPI_NFIT_CAPABILITY_CACHE_FLUSH       (1)	/* 00: Cache Flush to NVDIMM capable */
#घोषणा ACPI_NFIT_CAPABILITY_MEM_FLUSH         (1<<1)	/* 01: Memory Flush to NVDIMM capable */
#घोषणा ACPI_NFIT_CAPABILITY_MEM_MIRRORING     (1<<2)	/* 02: Memory Mirroring capable */

/*
 * NFIT/DVDIMM device handle support - used as the _ADR क्रम each NVDIMM
 */
काष्ठा nfit_device_handle अणु
	u32 handle;
पूर्ण;

/* Device handle स्थिरruction and extraction macros */

#घोषणा ACPI_NFIT_DIMM_NUMBER_MASK              0x0000000F
#घोषणा ACPI_NFIT_CHANNEL_NUMBER_MASK           0x000000F0
#घोषणा ACPI_NFIT_MEMORY_ID_MASK                0x00000F00
#घोषणा ACPI_NFIT_SOCKET_ID_MASK                0x0000F000
#घोषणा ACPI_NFIT_NODE_ID_MASK                  0x0FFF0000

#घोषणा ACPI_NFIT_DIMM_NUMBER_OFFSET            0
#घोषणा ACPI_NFIT_CHANNEL_NUMBER_OFFSET         4
#घोषणा ACPI_NFIT_MEMORY_ID_OFFSET              8
#घोषणा ACPI_NFIT_SOCKET_ID_OFFSET              12
#घोषणा ACPI_NFIT_NODE_ID_OFFSET                16

/* Macro to स्थिरruct a NFIT/NVDIMM device handle */

#घोषणा ACPI_NFIT_BUILD_DEVICE_HANDLE(dimm, channel, memory, socket, node) \
	((dimm)                                         | \
	((channel) << ACPI_NFIT_CHANNEL_NUMBER_OFFSET)  | \
	((memory)  << ACPI_NFIT_MEMORY_ID_OFFSET)       | \
	((socket)  << ACPI_NFIT_SOCKET_ID_OFFSET)       | \
	((node)    << ACPI_NFIT_NODE_ID_OFFSET))

/* Macros to extract inभागidual fields from a NFIT/NVDIMM device handle */

#घोषणा ACPI_NFIT_GET_DIMM_NUMBER(handle) \
	((handle) & ACPI_NFIT_DIMM_NUMBER_MASK)

#घोषणा ACPI_NFIT_GET_CHANNEL_NUMBER(handle) \
	(((handle) & ACPI_NFIT_CHANNEL_NUMBER_MASK) >> ACPI_NFIT_CHANNEL_NUMBER_OFFSET)

#घोषणा ACPI_NFIT_GET_MEMORY_ID(handle) \
	(((handle) & ACPI_NFIT_MEMORY_ID_MASK)      >> ACPI_NFIT_MEMORY_ID_OFFSET)

#घोषणा ACPI_NFIT_GET_SOCKET_ID(handle) \
	(((handle) & ACPI_NFIT_SOCKET_ID_MASK)      >> ACPI_NFIT_SOCKET_ID_OFFSET)

#घोषणा ACPI_NFIT_GET_NODE_ID(handle) \
	(((handle) & ACPI_NFIT_NODE_ID_MASK)        >> ACPI_NFIT_NODE_ID_OFFSET)

/*******************************************************************************
 *
 * PCCT - Platक्रमm Communications Channel Table (ACPI 5.0)
 *        Version 2 (ACPI 6.2)
 *
 ******************************************************************************/

काष्ठा acpi_table_pcct अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
	u32 flags;
	u64 reserved;
पूर्ण;

/* Values क्रम Flags field above */

#घोषणा ACPI_PCCT_DOORBELL              1

/* Values क्रम subtable type in काष्ठा acpi_subtable_header */

क्रमागत acpi_pcct_type अणु
	ACPI_PCCT_TYPE_GENERIC_SUBSPACE = 0,
	ACPI_PCCT_TYPE_HW_REDUCED_SUBSPACE = 1,
	ACPI_PCCT_TYPE_HW_REDUCED_SUBSPACE_TYPE2 = 2,	/* ACPI 6.1 */
	ACPI_PCCT_TYPE_EXT_PCC_MASTER_SUBSPACE = 3,	/* ACPI 6.2 */
	ACPI_PCCT_TYPE_EXT_PCC_SLAVE_SUBSPACE = 4,	/* ACPI 6.2 */
	ACPI_PCCT_TYPE_HW_REG_COMM_SUBSPACE = 5,	/* ACPI 6.4 */
	ACPI_PCCT_TYPE_RESERVED = 6	/* 6 and greater are reserved */
पूर्ण;

/*
 * PCCT Subtables, correspond to Type in काष्ठा acpi_subtable_header
 */

/* 0: Generic Communications Subspace */

काष्ठा acpi_pcct_subspace अणु
	काष्ठा acpi_subtable_header header;
	u8 reserved[6];
	u64 base_address;
	u64 length;
	काष्ठा acpi_generic_address करोorbell_रेजिस्टर;
	u64 preserve_mask;
	u64 ग_लिखो_mask;
	u32 latency;
	u32 max_access_rate;
	u16 min_turnaround_समय;
पूर्ण;

/* 1: HW-reduced Communications Subspace (ACPI 5.1) */

काष्ठा acpi_pcct_hw_reduced अणु
	काष्ठा acpi_subtable_header header;
	u32 platक्रमm_पूर्णांकerrupt;
	u8 flags;
	u8 reserved;
	u64 base_address;
	u64 length;
	काष्ठा acpi_generic_address करोorbell_रेजिस्टर;
	u64 preserve_mask;
	u64 ग_लिखो_mask;
	u32 latency;
	u32 max_access_rate;
	u16 min_turnaround_समय;
पूर्ण;

/* 2: HW-reduced Communications Subspace Type 2 (ACPI 6.1) */

काष्ठा acpi_pcct_hw_reduced_type2 अणु
	काष्ठा acpi_subtable_header header;
	u32 platक्रमm_पूर्णांकerrupt;
	u8 flags;
	u8 reserved;
	u64 base_address;
	u64 length;
	काष्ठा acpi_generic_address करोorbell_रेजिस्टर;
	u64 preserve_mask;
	u64 ग_लिखो_mask;
	u32 latency;
	u32 max_access_rate;
	u16 min_turnaround_समय;
	काष्ठा acpi_generic_address platक्रमm_ack_रेजिस्टर;
	u64 ack_preserve_mask;
	u64 ack_ग_लिखो_mask;
पूर्ण;

/* 3: Extended PCC Master Subspace Type 3 (ACPI 6.2) */

काष्ठा acpi_pcct_ext_pcc_master अणु
	काष्ठा acpi_subtable_header header;
	u32 platक्रमm_पूर्णांकerrupt;
	u8 flags;
	u8 reserved1;
	u64 base_address;
	u32 length;
	काष्ठा acpi_generic_address करोorbell_रेजिस्टर;
	u64 preserve_mask;
	u64 ग_लिखो_mask;
	u32 latency;
	u32 max_access_rate;
	u32 min_turnaround_समय;
	काष्ठा acpi_generic_address platक्रमm_ack_रेजिस्टर;
	u64 ack_preserve_mask;
	u64 ack_set_mask;
	u64 reserved2;
	काष्ठा acpi_generic_address cmd_complete_रेजिस्टर;
	u64 cmd_complete_mask;
	काष्ठा acpi_generic_address cmd_update_रेजिस्टर;
	u64 cmd_update_preserve_mask;
	u64 cmd_update_set_mask;
	काष्ठा acpi_generic_address error_status_रेजिस्टर;
	u64 error_status_mask;
पूर्ण;

/* 4: Extended PCC Slave Subspace Type 4 (ACPI 6.2) */

काष्ठा acpi_pcct_ext_pcc_slave अणु
	काष्ठा acpi_subtable_header header;
	u32 platक्रमm_पूर्णांकerrupt;
	u8 flags;
	u8 reserved1;
	u64 base_address;
	u32 length;
	काष्ठा acpi_generic_address करोorbell_रेजिस्टर;
	u64 preserve_mask;
	u64 ग_लिखो_mask;
	u32 latency;
	u32 max_access_rate;
	u32 min_turnaround_समय;
	काष्ठा acpi_generic_address platक्रमm_ack_रेजिस्टर;
	u64 ack_preserve_mask;
	u64 ack_set_mask;
	u64 reserved2;
	काष्ठा acpi_generic_address cmd_complete_रेजिस्टर;
	u64 cmd_complete_mask;
	काष्ठा acpi_generic_address cmd_update_रेजिस्टर;
	u64 cmd_update_preserve_mask;
	u64 cmd_update_set_mask;
	काष्ठा acpi_generic_address error_status_रेजिस्टर;
	u64 error_status_mask;
पूर्ण;

/* 5: HW Registers based Communications Subspace */

काष्ठा acpi_pcct_hw_reg अणु
	काष्ठा acpi_subtable_header header;
	u16 version;
	u64 base_address;
	u64 length;
	काष्ठा acpi_generic_address करोorbell_रेजिस्टर;
	u64 करोorbell_preserve;
	u64 करोorbell_ग_लिखो;
	काष्ठा acpi_generic_address cmd_complete_रेजिस्टर;
	u64 cmd_complete_mask;
	काष्ठा acpi_generic_address error_status_रेजिस्टर;
	u64 error_status_mask;
	u32 nominal_latency;
	u32 min_turnaround_समय;
पूर्ण;

/* Values क्रम करोorbell flags above */

#घोषणा ACPI_PCCT_INTERRUPT_POLARITY    (1)
#घोषणा ACPI_PCCT_INTERRUPT_MODE        (1<<1)

/*
 * PCC memory काष्ठाures (not part of the ACPI table)
 */

/* Shared Memory Region */

काष्ठा acpi_pcct_shared_memory अणु
	u32 signature;
	u16 command;
	u16 status;
पूर्ण;

/* Extended PCC Subspace Shared Memory Region (ACPI 6.2) */

काष्ठा acpi_pcct_ext_pcc_shared_memory अणु
	u32 signature;
	u32 flags;
	u32 length;
	u32 command;
पूर्ण;

/*******************************************************************************
 *
 * PDTT - Platक्रमm Debug Trigger Table (ACPI 6.2)
 *        Version 0
 *
 ******************************************************************************/

काष्ठा acpi_table_pdtt अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
	u8 trigger_count;
	u8 reserved[3];
	u32 array_offset;
पूर्ण;

/*
 * PDTT Communication Channel Identअगरier Structure.
 * The number of these काष्ठाures is defined by trigger_count above,
 * starting at array_offset.
 */
काष्ठा acpi_pdtt_channel अणु
	u8 subchannel_id;
	u8 flags;
पूर्ण;

/* Flags क्रम above */

#घोषणा ACPI_PDTT_RUNTIME_TRIGGER           (1)
#घोषणा ACPI_PDTT_WAIT_COMPLETION           (1<<1)
#घोषणा ACPI_PDTT_TRIGGER_ORDER             (1<<2)

/*******************************************************************************
 *
 * PHAT - Platक्रमm Health Assessment Table (ACPI 6.4)
 *        Version 1
 *
 ******************************************************************************/

काष्ठा acpi_table_phat अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
पूर्ण;

/* Common header क्रम PHAT subtables that follow मुख्य table */

काष्ठा acpi_phat_header अणु
	u16 type;
	u16 length;
	u8 revision;
पूर्ण;

/* Values क्रम Type field above */

#घोषणा ACPI_PHAT_TYPE_FW_VERSION_DATA  0
#घोषणा ACPI_PHAT_TYPE_FW_HEALTH_DATA   1
#घोषणा ACPI_PHAT_TYPE_RESERVED         2	/* 0x02-0xFFFF are reserved */

/*
 * PHAT subtables, correspond to Type in काष्ठा acpi_phat_header
 */

/* 0: Firmware Version Data Record */

काष्ठा acpi_phat_version_data अणु
	काष्ठा acpi_phat_header header;
	u8 reserved[3];
	u32 element_count;
पूर्ण;

काष्ठा acpi_phat_version_element अणु
	u8 guid[16];
	u64 version_value;
	u32 producer_id;
पूर्ण;

/* 1: Firmware Health Data Record */

काष्ठा acpi_phat_health_data अणु
	काष्ठा acpi_phat_header header;
	u8 reserved[2];
	u8 health;
	u8 device_guid[16];
	u32 device_specअगरic_offset;	/* Zero अगर no Device-specअगरic data */
पूर्ण;

/* Values क्रम Health field above */

#घोषणा ACPI_PHAT_ERRORS_FOUND          0
#घोषणा ACPI_PHAT_NO_ERRORS             1
#घोषणा ACPI_PHAT_UNKNOWN_ERRORS        2
#घोषणा ACPI_PHAT_ADVISORY              3

/*******************************************************************************
 *
 * PMTT - Platक्रमm Memory Topology Table (ACPI 5.0)
 *        Version 1
 *
 ******************************************************************************/

काष्ठा acpi_table_pmtt अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
	u32 memory_device_count;
	/*
	 * Immediately followed by:
	 * MEMORY_DEVICE memory_device_काष्ठा[memory_device_count];
	 */
पूर्ण;

/* Common header क्रम PMTT subtables that follow मुख्य table */

काष्ठा acpi_pmtt_header अणु
	u8 type;
	u8 reserved1;
	u16 length;
	u16 flags;
	u16 reserved2;
	u32 memory_device_count;	/* Zero means no memory device काष्ठाs follow */
	/*
	 * Immediately followed by:
	 * u8 type_specअगरic_data[]
	 * MEMORY_DEVICE memory_device_काष्ठा[memory_device_count];
	 */
पूर्ण;

/* Values क्रम Type field above */

#घोषणा ACPI_PMTT_TYPE_SOCKET           0
#घोषणा ACPI_PMTT_TYPE_CONTROLLER       1
#घोषणा ACPI_PMTT_TYPE_DIMM             2
#घोषणा ACPI_PMTT_TYPE_RESERVED         3	/* 0x03-0xFE are reserved */
#घोषणा ACPI_PMTT_TYPE_VENDOR           0xFF

/* Values क्रम Flags field above */

#घोषणा ACPI_PMTT_TOP_LEVEL             0x0001
#घोषणा ACPI_PMTT_PHYSICAL              0x0002
#घोषणा ACPI_PMTT_MEMORY_TYPE           0x000C

/*
 * PMTT subtables, correspond to Type in काष्ठा acpi_pmtt_header
 */

/* 0: Socket Structure */

काष्ठा acpi_pmtt_socket अणु
	काष्ठा acpi_pmtt_header header;
	u16 socket_id;
	u16 reserved;
पूर्ण;
	/*
	 * Immediately followed by:
	 * MEMORY_DEVICE memory_device_काष्ठा[memory_device_count];
	 */

/* 1: Memory Controller subtable */

काष्ठा acpi_pmtt_controller अणु
	काष्ठा acpi_pmtt_header header;
	u16 controller_id;
	u16 reserved;
पूर्ण;
	/*
	 * Immediately followed by:
	 * MEMORY_DEVICE memory_device_काष्ठा[memory_device_count];
	 */

/* 2: Physical Component Identअगरier (DIMM) */

काष्ठा acpi_pmtt_physical_component अणु
	काष्ठा acpi_pmtt_header header;
	u32 bios_handle;
पूर्ण;

/* 0xFF: Venकरोr Specअगरic Data */

काष्ठा acpi_pmtt_venकरोr_specअगरic अणु
	काष्ठा acpi_pmtt_header header;
	u8 type_uuid[16];
	u8 specअगरic[];
	/*
	 * Immediately followed by:
	 * u8 venकरोr_specअगरic_data[];
	 * MEMORY_DEVICE memory_device_काष्ठा[memory_device_count];
	 */
पूर्ण;

/*******************************************************************************
 *
 * PPTT - Processor Properties Topology Table (ACPI 6.2)
 *        Version 1
 *
 ******************************************************************************/

काष्ठा acpi_table_pptt अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
पूर्ण;

/* Values क्रम Type field above */

क्रमागत acpi_pptt_type अणु
	ACPI_PPTT_TYPE_PROCESSOR = 0,
	ACPI_PPTT_TYPE_CACHE = 1,
	ACPI_PPTT_TYPE_ID = 2,
	ACPI_PPTT_TYPE_RESERVED = 3
पूर्ण;

/* 0: Processor Hierarchy Node Structure */

काष्ठा acpi_pptt_processor अणु
	काष्ठा acpi_subtable_header header;
	u16 reserved;
	u32 flags;
	u32 parent;
	u32 acpi_processor_id;
	u32 number_of_priv_resources;
पूर्ण;

/* Flags */

#घोषणा ACPI_PPTT_PHYSICAL_PACKAGE          (1)
#घोषणा ACPI_PPTT_ACPI_PROCESSOR_ID_VALID   (1<<1)
#घोषणा ACPI_PPTT_ACPI_PROCESSOR_IS_THREAD  (1<<2)	/* ACPI 6.3 */
#घोषणा ACPI_PPTT_ACPI_LEAF_NODE            (1<<3)	/* ACPI 6.3 */
#घोषणा ACPI_PPTT_ACPI_IDENTICAL            (1<<4)	/* ACPI 6.3 */

/* 1: Cache Type Structure */

काष्ठा acpi_pptt_cache अणु
	काष्ठा acpi_subtable_header header;
	u16 reserved;
	u32 flags;
	u32 next_level_of_cache;
	u32 size;
	u32 number_of_sets;
	u8 associativity;
	u8 attributes;
	u16 line_size;
पूर्ण;

/* 1: Cache Type Structure क्रम PPTT version 3 */

काष्ठा acpi_pptt_cache_v1 अणु
	u32 cache_id;
पूर्ण;

/* Flags */

#घोषणा ACPI_PPTT_SIZE_PROPERTY_VALID       (1)	/* Physical property valid */
#घोषणा ACPI_PPTT_NUMBER_OF_SETS_VALID      (1<<1)	/* Number of sets valid */
#घोषणा ACPI_PPTT_ASSOCIATIVITY_VALID       (1<<2)	/* Associativity valid */
#घोषणा ACPI_PPTT_ALLOCATION_TYPE_VALID     (1<<3)	/* Allocation type valid */
#घोषणा ACPI_PPTT_CACHE_TYPE_VALID          (1<<4)	/* Cache type valid */
#घोषणा ACPI_PPTT_WRITE_POLICY_VALID        (1<<5)	/* Write policy valid */
#घोषणा ACPI_PPTT_LINE_SIZE_VALID           (1<<6)	/* Line size valid */
#घोषणा ACPI_PPTT_CACHE_ID_VALID            (1<<7)	/* Cache ID valid */

/* Masks क्रम Attributes */

#घोषणा ACPI_PPTT_MASK_ALLOCATION_TYPE      (0x03)	/* Allocation type */
#घोषणा ACPI_PPTT_MASK_CACHE_TYPE           (0x0C)	/* Cache type */
#घोषणा ACPI_PPTT_MASK_WRITE_POLICY         (0x10)	/* Write policy */

/* Attributes describing cache */
#घोषणा ACPI_PPTT_CACHE_READ_ALLOCATE       (0x0)	/* Cache line is allocated on पढ़ो */
#घोषणा ACPI_PPTT_CACHE_WRITE_ALLOCATE      (0x01)	/* Cache line is allocated on ग_लिखो */
#घोषणा ACPI_PPTT_CACHE_RW_ALLOCATE         (0x02)	/* Cache line is allocated on पढ़ो and ग_लिखो */
#घोषणा ACPI_PPTT_CACHE_RW_ALLOCATE_ALT     (0x03)	/* Alternate representation of above */

#घोषणा ACPI_PPTT_CACHE_TYPE_DATA           (0x0)	/* Data cache */
#घोषणा ACPI_PPTT_CACHE_TYPE_INSTR          (1<<2)	/* Inकाष्ठाion cache */
#घोषणा ACPI_PPTT_CACHE_TYPE_UNIFIED        (2<<2)	/* Unअगरied I & D cache */
#घोषणा ACPI_PPTT_CACHE_TYPE_UNIFIED_ALT    (3<<2)	/* Alternate representation of above */

#घोषणा ACPI_PPTT_CACHE_POLICY_WB           (0x0)	/* Cache is ग_लिखो back */
#घोषणा ACPI_PPTT_CACHE_POLICY_WT           (1<<4)	/* Cache is ग_लिखो through */

/* 2: ID Structure */

काष्ठा acpi_pptt_id अणु
	काष्ठा acpi_subtable_header header;
	u16 reserved;
	u32 venकरोr_id;
	u64 level1_id;
	u64 level2_id;
	u16 major_rev;
	u16 minor_rev;
	u16 spin_rev;
पूर्ण;

/*******************************************************************************
 *
 * RASF - RAS Feature Table (ACPI 5.0)
 *        Version 1
 *
 ******************************************************************************/

काष्ठा acpi_table_rasf अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
	u8 channel_id[12];
पूर्ण;

/* RASF Platक्रमm Communication Channel Shared Memory Region */

काष्ठा acpi_rasf_shared_memory अणु
	u32 signature;
	u16 command;
	u16 status;
	u16 version;
	u8 capabilities[16];
	u8 set_capabilities[16];
	u16 num_parameter_blocks;
	u32 set_capabilities_status;
पूर्ण;

/* RASF Parameter Block Structure Header */

काष्ठा acpi_rasf_parameter_block अणु
	u16 type;
	u16 version;
	u16 length;
पूर्ण;

/* RASF Parameter Block Structure क्रम PATROL_SCRUB */

काष्ठा acpi_rasf_patrol_scrub_parameter अणु
	काष्ठा acpi_rasf_parameter_block header;
	u16 patrol_scrub_command;
	u64 requested_address_range[2];
	u64 actual_address_range[2];
	u16 flags;
	u8 requested_speed;
पूर्ण;

/* Masks क्रम Flags and Speed fields above */

#घोषणा ACPI_RASF_SCRUBBER_RUNNING      1
#घोषणा ACPI_RASF_SPEED                 (7<<1)
#घोषणा ACPI_RASF_SPEED_SLOW            (0<<1)
#घोषणा ACPI_RASF_SPEED_MEDIUM          (4<<1)
#घोषणा ACPI_RASF_SPEED_FAST            (7<<1)

/* Channel Commands */

क्रमागत acpi_rasf_commands अणु
	ACPI_RASF_EXECUTE_RASF_COMMAND = 1
पूर्ण;

/* Platक्रमm RAS Capabilities */

क्रमागत acpi_rasf_capabiliities अणु
	ACPI_HW_PATROL_SCRUB_SUPPORTED = 0,
	ACPI_SW_PATROL_SCRUB_EXPOSED = 1
पूर्ण;

/* Patrol Scrub Commands */

क्रमागत acpi_rasf_patrol_scrub_commands अणु
	ACPI_RASF_GET_PATROL_PARAMETERS = 1,
	ACPI_RASF_START_PATROL_SCRUBBER = 2,
	ACPI_RASF_STOP_PATROL_SCRUBBER = 3
पूर्ण;

/* Channel Command flags */

#घोषणा ACPI_RASF_GENERATE_SCI          (1<<15)

/* Status values */

क्रमागत acpi_rasf_status अणु
	ACPI_RASF_SUCCESS = 0,
	ACPI_RASF_NOT_VALID = 1,
	ACPI_RASF_NOT_SUPPORTED = 2,
	ACPI_RASF_BUSY = 3,
	ACPI_RASF_FAILED = 4,
	ACPI_RASF_ABORTED = 5,
	ACPI_RASF_INVALID_DATA = 6
पूर्ण;

/* Status flags */

#घोषणा ACPI_RASF_COMMAND_COMPLETE      (1)
#घोषणा ACPI_RASF_SCI_DOORBELL          (1<<1)
#घोषणा ACPI_RASF_ERROR                 (1<<2)
#घोषणा ACPI_RASF_STATUS                (0x1F<<3)

/*******************************************************************************
 *
 * SBST - Smart Battery Specअगरication Table
 *        Version 1
 *
 ******************************************************************************/

काष्ठा acpi_table_sbst अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
	u32 warning_level;
	u32 low_level;
	u32 critical_level;
पूर्ण;

/*******************************************************************************
 *
 * SDEI - Software Delegated Exception Interface Descriptor Table
 *
 * Conक्रमms to "Software Delegated Exception Interface (SDEI)" ARM DEN0054A,
 * May 8th, 2017. Copyright 2017 ARM Ltd.
 *
 ******************************************************************************/

काष्ठा acpi_table_sdei अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
पूर्ण;

/*******************************************************************************
 *
 * SDEV - Secure Devices Table (ACPI 6.2)
 *        Version 1
 *
 ******************************************************************************/

काष्ठा acpi_table_sdev अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
पूर्ण;

काष्ठा acpi_sdev_header अणु
	u8 type;
	u8 flags;
	u16 length;
पूर्ण;

/* Values क्रम subtable type above */

क्रमागत acpi_sdev_type अणु
	ACPI_SDEV_TYPE_NAMESPACE_DEVICE = 0,
	ACPI_SDEV_TYPE_PCIE_ENDPOINT_DEVICE = 1,
	ACPI_SDEV_TYPE_RESERVED = 2	/* 2 and greater are reserved */
पूर्ण;

/* Values क्रम flags above */

#घोषणा ACPI_SDEV_HANDOFF_TO_UNSECURE_OS    (1)
#घोषणा ACPI_SDEV_SECURE_COMPONENTS_PRESENT (1<<1)

/*
 * SDEV subtables
 */

/* 0: Namespace Device Based Secure Device Structure */

काष्ठा acpi_sdev_namespace अणु
	काष्ठा acpi_sdev_header header;
	u16 device_id_offset;
	u16 device_id_length;
	u16 venकरोr_data_offset;
	u16 venकरोr_data_length;
पूर्ण;

काष्ठा acpi_sdev_secure_component अणु
	u16 secure_component_offset;
	u16 secure_component_length;
पूर्ण;

/*
 * SDEV sub-subtables ("Components") क्रम above
 */
काष्ठा acpi_sdev_component अणु
	काष्ठा acpi_sdev_header header;
पूर्ण;

/* Values क्रम sub-subtable type above */

क्रमागत acpi_sac_type अणु
	ACPI_SDEV_TYPE_ID_COMPONENT = 0,
	ACPI_SDEV_TYPE_MEM_COMPONENT = 1
पूर्ण;

काष्ठा acpi_sdev_id_component अणु
	काष्ठा acpi_sdev_header header;
	u16 hardware_id_offset;
	u16 hardware_id_length;
	u16 subप्रणाली_id_offset;
	u16 subप्रणाली_id_length;
	u16 hardware_revision;
	u8 hardware_rev_present;
	u8 class_code_present;
	u8 pci_base_class;
	u8 pci_sub_class;
	u8 pci_programming_xface;
पूर्ण;

काष्ठा acpi_sdev_mem_component अणु
	काष्ठा acpi_sdev_header header;
	u32 reserved;
	u64 memory_base_address;
	u64 memory_length;
पूर्ण;

/* 1: PCIe Endpoपूर्णांक Device Based Device Structure */

काष्ठा acpi_sdev_pcie अणु
	काष्ठा acpi_sdev_header header;
	u16 segment;
	u16 start_bus;
	u16 path_offset;
	u16 path_length;
	u16 venकरोr_data_offset;
	u16 venकरोr_data_length;
पूर्ण;

/* 1a: PCIe Endpoपूर्णांक path entry */

काष्ठा acpi_sdev_pcie_path अणु
	u8 device;
	u8 function;
पूर्ण;

/* Reset to शेष packing */

#आशय pack()

#पूर्ण_अगर				/* __ACTBL2_H__ */
