<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/******************************************************************************
 *
 * Name: actbl.h - Basic ACPI Table Definitions
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#अगर_अघोषित __ACTBL_H__
#घोषणा __ACTBL_H__

/*******************************************************************************
 *
 * Fundamental ACPI tables
 *
 * This file contains definitions क्रम the ACPI tables that are directly consumed
 * by ACPICA. All other tables are consumed by the OS-dependent ACPI-related
 * device drivers and other OS support code.
 *
 * The RSDP and FACS करो not use the common ACPI table header. All other ACPI
 * tables use the header.
 *
 ******************************************************************************/

/*
 * Values क्रम description table header signatures क्रम tables defined in this
 * file. Useful because they make it more dअगरficult to inadvertently type in
 * the wrong signature.
 */
#घोषणा ACPI_SIG_DSDT           "DSDT"	/* Dअगरferentiated System Description Table */
#घोषणा ACPI_SIG_FADT           "FACP"	/* Fixed ACPI Description Table */
#घोषणा ACPI_SIG_FACS           "FACS"	/* Firmware ACPI Control Structure */
#घोषणा ACPI_SIG_OSDT           "OSDT"	/* Override System Description Table */
#घोषणा ACPI_SIG_PSDT           "PSDT"	/* Persistent System Description Table */
#घोषणा ACPI_SIG_RSDP           "RSD PTR "	/* Root System Description Poपूर्णांकer */
#घोषणा ACPI_SIG_RSDT           "RSDT"	/* Root System Description Table */
#घोषणा ACPI_SIG_XSDT           "XSDT"	/* Extended  System Description Table */
#घोषणा ACPI_SIG_SSDT           "SSDT"	/* Secondary System Description Table */
#घोषणा ACPI_RSDP_NAME          "RSDP"	/* Short name क्रम RSDP, not signature */
#घोषणा ACPI_OEM_NAME           "OEM"	/* Short name क्रम OEM, not signature */

/*
 * All tables and काष्ठाures must be byte-packed to match the ACPI
 * specअगरication, since the tables are provided by the प्रणाली BIOS
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
 * Master ACPI Table Header. This common header is used by all ACPI tables
 * except the RSDP and FACS.
 *
 ******************************************************************************/

काष्ठा acpi_table_header अणु
	अक्षर signature[ACPI_NAMESEG_SIZE];	/* ASCII table signature */
	u32 length;		/* Length of table in bytes, including this header */
	u8 revision;		/* ACPI Specअगरication minor version number */
	u8 checksum;		/* To make sum of entire table == 0 */
	अक्षर oem_id[ACPI_OEM_ID_SIZE];	/* ASCII OEM identअगरication */
	अक्षर oem_table_id[ACPI_OEM_TABLE_ID_SIZE];	/* ASCII OEM table identअगरication */
	u32 oem_revision;	/* OEM revision number */
	अक्षर asl_compiler_id[ACPI_NAMESEG_SIZE];	/* ASCII ASL compiler venकरोr ID */
	u32 asl_compiler_revision;	/* ASL compiler version */
पूर्ण;

/*******************************************************************************
 *
 * GAS - Generic Address Structure (ACPI 2.0+)
 *
 * Note: Since this काष्ठाure is used in the ACPI tables, it is byte aligned.
 * If misaligned access is not supported by the hardware, accesses to the
 * 64-bit Address field must be perक्रमmed with care.
 *
 ******************************************************************************/

काष्ठा acpi_generic_address अणु
	u8 space_id;		/* Address space where काष्ठा or रेजिस्टर exists */
	u8 bit_width;		/* Size in bits of given रेजिस्टर */
	u8 bit_offset;		/* Bit offset within the रेजिस्टर */
	u8 access_width;	/* Minimum Access size (ACPI 3.0) */
	u64 address;		/* 64-bit address of काष्ठा or रेजिस्टर */
पूर्ण;

/*******************************************************************************
 *
 * RSDP - Root System Description Poपूर्णांकer (Signature is "RSD PTR ")
 *        Version 2
 *
 ******************************************************************************/

काष्ठा acpi_table_rsdp अणु
	अक्षर signature[8];	/* ACPI signature, contains "RSD PTR " */
	u8 checksum;		/* ACPI 1.0 checksum */
	अक्षर oem_id[ACPI_OEM_ID_SIZE];	/* OEM identअगरication */
	u8 revision;		/* Must be (0) क्रम ACPI 1.0 or (2) क्रम ACPI 2.0+ */
	u32 rsdt_physical_address;	/* 32-bit physical address of the RSDT */
	u32 length;		/* Table length in bytes, including header (ACPI 2.0+) */
	u64 xsdt_physical_address;	/* 64-bit physical address of the XSDT (ACPI 2.0+) */
	u8 extended_checksum;	/* Checksum of entire table (ACPI 2.0+) */
	u8 reserved[3];		/* Reserved, must be zero */
पूर्ण;

/* Standalone काष्ठा क्रम the ACPI 1.0 RSDP */

काष्ठा acpi_rsdp_common अणु
	अक्षर signature[8];
	u8 checksum;
	अक्षर oem_id[ACPI_OEM_ID_SIZE];
	u8 revision;
	u32 rsdt_physical_address;
पूर्ण;

/* Standalone काष्ठा क्रम the extended part of the RSDP (ACPI 2.0+) */

काष्ठा acpi_rsdp_extension अणु
	u32 length;
	u64 xsdt_physical_address;
	u8 extended_checksum;
	u8 reserved[3];
पूर्ण;

/*******************************************************************************
 *
 * RSDT/XSDT - Root System Description Tables
 *             Version 1 (both)
 *
 ******************************************************************************/

काष्ठा acpi_table_rsdt अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
	u32 table_offset_entry[1];	/* Array of poपूर्णांकers to ACPI tables */
पूर्ण;

काष्ठा acpi_table_xsdt अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
	u64 table_offset_entry[1];	/* Array of poपूर्णांकers to ACPI tables */
पूर्ण;

#घोषणा ACPI_RSDT_ENTRY_SIZE        (माप (u32))
#घोषणा ACPI_XSDT_ENTRY_SIZE        (माप (u64))

/*******************************************************************************
 *
 * FACS - Firmware ACPI Control Structure (FACS)
 *
 ******************************************************************************/

काष्ठा acpi_table_facs अणु
	अक्षर signature[4];	/* ASCII table signature */
	u32 length;		/* Length of काष्ठाure, in bytes */
	u32 hardware_signature;	/* Hardware configuration signature */
	u32 firmware_waking_vector;	/* 32-bit physical address of the Firmware Waking Vector */
	u32 global_lock;	/* Global Lock क्रम shared hardware resources */
	u32 flags;
	u64 xfirmware_waking_vector;	/* 64-bit version of the Firmware Waking Vector (ACPI 2.0+) */
	u8 version;		/* Version of this table (ACPI 2.0+) */
	u8 reserved[3];		/* Reserved, must be zero */
	u32 ospm_flags;		/* Flags to be set by OSPM (ACPI 4.0) */
	u8 reserved1[24];	/* Reserved, must be zero */
पूर्ण;

/* Masks क्रम global_lock flag field above */

#घोषणा ACPI_GLOCK_PENDING          (1)	/* 00: Pending global lock ownership */
#घोषणा ACPI_GLOCK_OWNED            (1<<1)	/* 01: Global lock is owned */

/* Masks क्रम Flags field above  */

#घोषणा ACPI_FACS_S4_BIOS_PRESENT   (1)	/* 00: S4BIOS support is present */
#घोषणा ACPI_FACS_64BIT_WAKE        (1<<1)	/* 01: 64-bit wake vector supported (ACPI 4.0) */

/* Masks क्रम ospm_flags field above */

#घोषणा ACPI_FACS_64BIT_ENVIRONMENT (1)	/* 00: 64-bit wake environment is required (ACPI 4.0) */

/*******************************************************************************
 *
 * FADT - Fixed ACPI Description Table (Signature "FACP")
 *        Version 6
 *
 ******************************************************************************/

/* Fields common to all versions of the FADT */

काष्ठा acpi_table_fadt अणु
	काष्ठा acpi_table_header header;	/* Common ACPI table header */
	u32 facs;		/* 32-bit physical address of FACS */
	u32 dsdt;		/* 32-bit physical address of DSDT */
	u8 model;		/* System Interrupt Model (ACPI 1.0) - not used in ACPI 2.0+ */
	u8 preferred_profile;	/* Conveys preferred घातer management profile to OSPM. */
	u16 sci_पूर्णांकerrupt;	/* System vector of SCI पूर्णांकerrupt */
	u32 smi_command;	/* 32-bit Port address of SMI command port */
	u8 acpi_enable;		/* Value to ग_लिखो to SMI_CMD to enable ACPI */
	u8 acpi_disable;	/* Value to ग_लिखो to SMI_CMD to disable ACPI */
	u8 s4_bios_request;	/* Value to ग_लिखो to SMI_CMD to enter S4BIOS state */
	u8 pstate_control;	/* Processor perक्रमmance state control */
	u32 pm1a_event_block;	/* 32-bit port address of Power Mgt 1a Event Reg Blk */
	u32 pm1b_event_block;	/* 32-bit port address of Power Mgt 1b Event Reg Blk */
	u32 pm1a_control_block;	/* 32-bit port address of Power Mgt 1a Control Reg Blk */
	u32 pm1b_control_block;	/* 32-bit port address of Power Mgt 1b Control Reg Blk */
	u32 pm2_control_block;	/* 32-bit port address of Power Mgt 2 Control Reg Blk */
	u32 pm_समयr_block;	/* 32-bit port address of Power Mgt Timer Ctrl Reg Blk */
	u32 gpe0_block;		/* 32-bit port address of General Purpose Event 0 Reg Blk */
	u32 gpe1_block;		/* 32-bit port address of General Purpose Event 1 Reg Blk */
	u8 pm1_event_length;	/* Byte Length of ports at pm1x_event_block */
	u8 pm1_control_length;	/* Byte Length of ports at pm1x_control_block */
	u8 pm2_control_length;	/* Byte Length of ports at pm2_control_block */
	u8 pm_समयr_length;	/* Byte Length of ports at pm_समयr_block */
	u8 gpe0_block_length;	/* Byte Length of ports at gpe0_block */
	u8 gpe1_block_length;	/* Byte Length of ports at gpe1_block */
	u8 gpe1_base;		/* Offset in GPE number space where GPE1 events start */
	u8 cst_control;		/* Support क्रम the _CST object and C-States change notअगरication */
	u16 c2_latency;		/* Worst हाल HW latency to enter/निकास C2 state */
	u16 c3_latency;		/* Worst हाल HW latency to enter/निकास C3 state */
	u16 flush_size;		/* Processor memory cache line width, in bytes */
	u16 flush_stride;	/* Number of flush strides that need to be पढ़ो */
	u8 duty_offset;		/* Processor duty cycle index in processor P_CNT reg */
	u8 duty_width;		/* Processor duty cycle value bit width in P_CNT रेजिस्टर */
	u8 day_alarm;		/* Index to day-of-month alarm in RTC CMOS RAM */
	u8 month_alarm;		/* Index to month-of-year alarm in RTC CMOS RAM */
	u8 century;		/* Index to century in RTC CMOS RAM */
	u16 boot_flags;		/* IA-PC Boot Architecture Flags (see below क्रम inभागidual flags) */
	u8 reserved;		/* Reserved, must be zero */
	u32 flags;		/* Miscellaneous flag bits (see below क्रम inभागidual flags) */
	काष्ठा acpi_generic_address reset_रेजिस्टर;	/* 64-bit address of the Reset रेजिस्टर */
	u8 reset_value;		/* Value to ग_लिखो to the reset_रेजिस्टर port to reset the प्रणाली */
	u16 arm_boot_flags;	/* ARM-Specअगरic Boot Flags (see below क्रम inभागidual flags) (ACPI 5.1) */
	u8 minor_revision;	/* FADT Minor Revision (ACPI 5.1) */
	u64 Xfacs;		/* 64-bit physical address of FACS */
	u64 Xdsdt;		/* 64-bit physical address of DSDT */
	काष्ठा acpi_generic_address xpm1a_event_block;	/* 64-bit Extended Power Mgt 1a Event Reg Blk address */
	काष्ठा acpi_generic_address xpm1b_event_block;	/* 64-bit Extended Power Mgt 1b Event Reg Blk address */
	काष्ठा acpi_generic_address xpm1a_control_block;	/* 64-bit Extended Power Mgt 1a Control Reg Blk address */
	काष्ठा acpi_generic_address xpm1b_control_block;	/* 64-bit Extended Power Mgt 1b Control Reg Blk address */
	काष्ठा acpi_generic_address xpm2_control_block;	/* 64-bit Extended Power Mgt 2 Control Reg Blk address */
	काष्ठा acpi_generic_address xpm_समयr_block;	/* 64-bit Extended Power Mgt Timer Ctrl Reg Blk address */
	काष्ठा acpi_generic_address xgpe0_block;	/* 64-bit Extended General Purpose Event 0 Reg Blk address */
	काष्ठा acpi_generic_address xgpe1_block;	/* 64-bit Extended General Purpose Event 1 Reg Blk address */
	काष्ठा acpi_generic_address sleep_control;	/* 64-bit Sleep Control रेजिस्टर (ACPI 5.0) */
	काष्ठा acpi_generic_address sleep_status;	/* 64-bit Sleep Status रेजिस्टर (ACPI 5.0) */
	u64 hypervisor_id;	/* Hypervisor Venकरोr ID (ACPI 6.0) */
पूर्ण;

/* Masks क्रम FADT IA-PC Boot Architecture Flags (boot_flags) [Vx]=Introduced in this FADT revision */

#घोषणा ACPI_FADT_LEGACY_DEVICES    (1)  	/* 00: [V2] System has LPC or ISA bus devices */
#घोषणा ACPI_FADT_8042              (1<<1)	/* 01: [V3] System has an 8042 controller on port 60/64 */
#घोषणा ACPI_FADT_NO_VGA            (1<<2)	/* 02: [V4] It is not safe to probe क्रम VGA hardware */
#घोषणा ACPI_FADT_NO_MSI            (1<<3)	/* 03: [V4] Message Signaled Interrupts (MSI) must not be enabled */
#घोषणा ACPI_FADT_NO_ASPM           (1<<4)	/* 04: [V4] PCIe ASPM control must not be enabled */
#घोषणा ACPI_FADT_NO_CMOS_RTC       (1<<5)	/* 05: [V5] No CMOS real-समय घड़ी present */

#घोषणा FADT2_REVISION_ID               3

/* Masks क्रम FADT ARM Boot Architecture Flags (arm_boot_flags) ACPI 5.1 */

#घोषणा ACPI_FADT_PSCI_COMPLIANT    (1)	/* 00: [V5+] PSCI 0.2+ is implemented */
#घोषणा ACPI_FADT_PSCI_USE_HVC      (1<<1)	/* 01: [V5+] HVC must be used instead of SMC as the PSCI conduit */

/* Masks क्रम FADT flags */

#घोषणा ACPI_FADT_WBINVD            (1)	/* 00: [V1] The WBINVD inकाष्ठाion works properly */
#घोषणा ACPI_FADT_WBINVD_FLUSH      (1<<1)	/* 01: [V1] WBINVD flushes but करोes not invalidate caches */
#घोषणा ACPI_FADT_C1_SUPPORTED      (1<<2)	/* 02: [V1] All processors support C1 state */
#घोषणा ACPI_FADT_C2_MP_SUPPORTED   (1<<3)	/* 03: [V1] C2 state works on MP प्रणाली */
#घोषणा ACPI_FADT_POWER_BUTTON      (1<<4)	/* 04: [V1] Power button is handled as a control method device */
#घोषणा ACPI_FADT_SLEEP_BUTTON      (1<<5)	/* 05: [V1] Sleep button is handled as a control method device */
#घोषणा ACPI_FADT_FIXED_RTC         (1<<6)	/* 06: [V1] RTC wakeup status is not in fixed रेजिस्टर space */
#घोषणा ACPI_FADT_S4_RTC_WAKE       (1<<7)	/* 07: [V1] RTC alarm can wake प्रणाली from S4 */
#घोषणा ACPI_FADT_32BIT_TIMER       (1<<8)	/* 08: [V1] ACPI समयr width is 32-bit (0=24-bit) */
#घोषणा ACPI_FADT_DOCKING_SUPPORTED (1<<9)	/* 09: [V1] Docking supported */
#घोषणा ACPI_FADT_RESET_REGISTER    (1<<10)	/* 10: [V2] System reset via the FADT RESET_REG supported */
#घोषणा ACPI_FADT_SEALED_CASE       (1<<11)	/* 11: [V3] No पूर्णांकernal expansion capabilities and हाल is sealed */
#घोषणा ACPI_FADT_HEADLESS          (1<<12)	/* 12: [V3] No local video capabilities or local input devices */
#घोषणा ACPI_FADT_SLEEP_TYPE        (1<<13)	/* 13: [V3] Must execute native inकाष्ठाion after writing  SLP_TYPx रेजिस्टर */
#घोषणा ACPI_FADT_PCI_EXPRESS_WAKE  (1<<14)	/* 14: [V4] System supports PCIEXP_WAKE (STS/EN) bits (ACPI 3.0) */
#घोषणा ACPI_FADT_PLATFORM_CLOCK    (1<<15)	/* 15: [V4] OSPM should use platक्रमm-provided समयr (ACPI 3.0) */
#घोषणा ACPI_FADT_S4_RTC_VALID      (1<<16)	/* 16: [V4] Contents of RTC_STS valid after S4 wake (ACPI 3.0) */
#घोषणा ACPI_FADT_REMOTE_POWER_ON   (1<<17)	/* 17: [V4] System is compatible with remote घातer on (ACPI 3.0) */
#घोषणा ACPI_FADT_APIC_CLUSTER      (1<<18)	/* 18: [V4] All local APICs must use cluster model (ACPI 3.0) */
#घोषणा ACPI_FADT_APIC_PHYSICAL     (1<<19)	/* 19: [V4] All local xAPICs must use physical dest mode (ACPI 3.0) */
#घोषणा ACPI_FADT_HW_REDUCED        (1<<20)	/* 20: [V5] ACPI hardware is not implemented (ACPI 5.0) */
#घोषणा ACPI_FADT_LOW_POWER_S0      (1<<21)	/* 21: [V5] S0 घातer savings are equal or better than S3 (ACPI 5.0) */

/* Values क्रम preferred_profile (Preferred Power Management Profiles) */

क्रमागत acpi_preferred_pm_profiles अणु
	PM_UNSPECIFIED = 0,
	PM_DESKTOP = 1,
	PM_MOBILE = 2,
	PM_WORKSTATION = 3,
	PM_ENTERPRISE_SERVER = 4,
	PM_SOHO_SERVER = 5,
	PM_APPLIANCE_PC = 6,
	PM_PERFORMANCE_SERVER = 7,
	PM_TABLET = 8
पूर्ण;

/* Values क्रम sleep_status and sleep_control रेजिस्टरs (V5+ FADT) */

#घोषणा ACPI_X_WAKE_STATUS          0x80
#घोषणा ACPI_X_SLEEP_TYPE_MASK      0x1C
#घोषणा ACPI_X_SLEEP_TYPE_POSITION  0x02
#घोषणा ACPI_X_SLEEP_ENABLE         0x20

/* Reset to शेष packing */

#आशय pack()

/*
 * Internal table-related काष्ठाures
 */
जोड़ acpi_name_जोड़ अणु
	u32 पूर्णांकeger;
	अक्षर ascii[4];
पूर्ण;

/* Internal ACPI Table Descriptor. One per ACPI table. */

काष्ठा acpi_table_desc अणु
	acpi_physical_address address;
	काष्ठा acpi_table_header *poपूर्णांकer;
	u32 length;		/* Length fixed at 32 bits (fixed in table header) */
	जोड़ acpi_name_जोड़ signature;
	acpi_owner_id owner_id;
	u8 flags;
	u16 validation_count;
पूर्ण;

/*
 * Maximum value of the validation_count field in काष्ठा acpi_table_desc.
 * When reached, validation_count cannot be changed any more and the table will
 * be permanently regarded as validated.
 *
 * This is to prevent situations in which unbalanced table get/put operations
 * may cause premature table unmapping in the OS to happen.
 *
 * The maximum validation count can be defined to any value, but should be
 * greater than the maximum number of OS early stage mapping slots to aव्योम
 * leaking early stage table mappings to the late stage.
 */
#घोषणा ACPI_MAX_TABLE_VALIDATIONS          ACPI_UINT16_MAX

/* Masks क्रम Flags field above */

#घोषणा ACPI_TABLE_ORIGIN_EXTERNAL_VIRTUAL  (0)	/* Virtual address, बाह्यal मुख्यtained */
#घोषणा ACPI_TABLE_ORIGIN_INTERNAL_PHYSICAL (1)	/* Physical address, पूर्णांकernally mapped */
#घोषणा ACPI_TABLE_ORIGIN_INTERNAL_VIRTUAL  (2)	/* Virtual address, पूर्णांकernallly allocated */
#घोषणा ACPI_TABLE_ORIGIN_MASK              (3)
#घोषणा ACPI_TABLE_IS_VERIFIED              (4)
#घोषणा ACPI_TABLE_IS_LOADED                (8)

/*
 * Get the reमुख्यing ACPI tables
 */
#समावेश <acpi/actbl1.h>
#समावेश <acpi/actbl2.h>
#समावेश <acpi/actbl3.h>

/* Macros used to generate offsets to specअगरic table fields */

#घोषणा ACPI_FADT_OFFSET(f)             (u16) ACPI_OFFSET (काष्ठा acpi_table_fadt, f)

/*
 * Sizes of the various flavors of FADT. We need to look बंदly
 * at the FADT length because the version number essentially tells
 * us nothing because of many BIOS bugs where the version करोes not
 * match the expected length. In other words, the length of the
 * FADT is the bottom line as to what the version really is.
 *
 * For reference, the values below are as follows:
 *     FADT V1 size: 0x074
 *     FADT V2 size: 0x084
 *     FADT V3 size: 0x0F4
 *     FADT V4 size: 0x0F4
 *     FADT V5 size: 0x10C
 *     FADT V6 size: 0x114
 */
#घोषणा ACPI_FADT_V1_SIZE       (u32) (ACPI_FADT_OFFSET (flags) + 4)
#घोषणा ACPI_FADT_V2_SIZE       (u32) (ACPI_FADT_OFFSET (minor_revision) + 1)
#घोषणा ACPI_FADT_V3_SIZE       (u32) (ACPI_FADT_OFFSET (sleep_control))
#घोषणा ACPI_FADT_V5_SIZE       (u32) (ACPI_FADT_OFFSET (hypervisor_id))
#घोषणा ACPI_FADT_V6_SIZE       (u32) (माप (काष्ठा acpi_table_fadt))

#घोषणा ACPI_FADT_CONFORMANCE   "ACPI 6.1 (FADT version 6)"

#पूर्ण_अगर				/* __ACTBL_H__ */
