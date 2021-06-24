<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 *	PCI standard defines
 *	Copyright 1994, Drew Eckhardt
 *	Copyright 1997--1999 Martin Mares <mj@ucw.cz>
 *
 *	For more inक्रमmation, please consult the following manuals (look at
 *	http://www.pcisig.com/ क्रम how to get them):
 *
 *	PCI BIOS Specअगरication
 *	PCI Local Bus Specअगरication
 *	PCI to PCI Bridge Specअगरication
 *	PCI System Design Guide
 *
 *	For HyperTransport inक्रमmation, please consult the following manuals
 *	from http://www.hypertransport.org :
 *
 *	The HyperTransport I/O Link Specअगरication
 */

#अगर_अघोषित LINUX_PCI_REGS_H
#घोषणा LINUX_PCI_REGS_H

/*
 * Conventional PCI and PCI-X Mode 1 devices have 256 bytes of
 * configuration space.  PCI-X Mode 2 and PCIe devices have 4096 bytes of
 * configuration space.
 */
#घोषणा PCI_CFG_SPACE_SIZE	256
#घोषणा PCI_CFG_SPACE_EXP_SIZE	4096

/*
 * Under PCI, each device has 256 bytes of configuration address space,
 * of which the first 64 bytes are standardized as follows:
 */
#घोषणा PCI_STD_HEADER_SIZखातापूर्ण	64
#घोषणा PCI_STD_NUM_BARS	6	/* Number of standard BARs */
#घोषणा PCI_VENDOR_ID		0x00	/* 16 bits */
#घोषणा PCI_DEVICE_ID		0x02	/* 16 bits */
#घोषणा PCI_COMMAND		0x04	/* 16 bits */
#घोषणा  PCI_COMMAND_IO		0x1	/* Enable response in I/O space */
#घोषणा  PCI_COMMAND_MEMORY	0x2	/* Enable response in Memory space */
#घोषणा  PCI_COMMAND_MASTER	0x4	/* Enable bus mastering */
#घोषणा  PCI_COMMAND_SPECIAL	0x8	/* Enable response to special cycles */
#घोषणा  PCI_COMMAND_INVALIDATE	0x10	/* Use memory ग_लिखो and invalidate */
#घोषणा  PCI_COMMAND_VGA_PALETTE 0x20	/* Enable palette snooping */
#घोषणा  PCI_COMMAND_PARITY	0x40	/* Enable parity checking */
#घोषणा  PCI_COMMAND_WAIT	0x80	/* Enable address/data stepping */
#घोषणा  PCI_COMMAND_SERR	0x100	/* Enable SERR */
#घोषणा  PCI_COMMAND_FAST_BACK	0x200	/* Enable back-to-back ग_लिखोs */
#घोषणा  PCI_COMMAND_INTX_DISABLE 0x400 /* INTx Emulation Disable */

#घोषणा PCI_STATUS		0x06	/* 16 bits */
#घोषणा  PCI_STATUS_IMM_READY	0x01	/* Immediate Readiness */
#घोषणा  PCI_STATUS_INTERRUPT	0x08	/* Interrupt status */
#घोषणा  PCI_STATUS_CAP_LIST	0x10	/* Support Capability List */
#घोषणा  PCI_STATUS_66MHZ	0x20	/* Support 66 MHz PCI 2.1 bus */
#घोषणा  PCI_STATUS_UDF		0x40	/* Support User Definable Features [obsolete] */
#घोषणा  PCI_STATUS_FAST_BACK	0x80	/* Accept fast-back to back */
#घोषणा  PCI_STATUS_PARITY	0x100	/* Detected parity error */
#घोषणा  PCI_STATUS_DEVSEL_MASK	0x600	/* DEVSEL timing */
#घोषणा  PCI_STATUS_DEVSEL_FAST		0x000
#घोषणा  PCI_STATUS_DEVSEL_MEDIUM	0x200
#घोषणा  PCI_STATUS_DEVSEL_SLOW		0x400
#घोषणा  PCI_STATUS_SIG_TARGET_ABORT	0x800 /* Set on target पात */
#घोषणा  PCI_STATUS_REC_TARGET_ABORT	0x1000 /* Master ack of " */
#घोषणा  PCI_STATUS_REC_MASTER_ABORT	0x2000 /* Set on master पात */
#घोषणा  PCI_STATUS_SIG_SYSTEM_ERROR	0x4000 /* Set when we drive SERR */
#घोषणा  PCI_STATUS_DETECTED_PARITY	0x8000 /* Set on parity error */

#घोषणा PCI_CLASS_REVISION	0x08	/* High 24 bits are class, low 8 revision */
#घोषणा PCI_REVISION_ID		0x08	/* Revision ID */
#घोषणा PCI_CLASS_PROG		0x09	/* Reg. Level Programming Interface */
#घोषणा PCI_CLASS_DEVICE	0x0a	/* Device class */

#घोषणा PCI_CACHE_LINE_SIZE	0x0c	/* 8 bits */
#घोषणा PCI_LATENCY_TIMER	0x0d	/* 8 bits */
#घोषणा PCI_HEADER_TYPE		0x0e	/* 8 bits */
#घोषणा  PCI_HEADER_TYPE_MASK		0x7f
#घोषणा  PCI_HEADER_TYPE_NORMAL		0
#घोषणा  PCI_HEADER_TYPE_BRIDGE		1
#घोषणा  PCI_HEADER_TYPE_CARDBUS	2

#घोषणा PCI_BIST		0x0f	/* 8 bits */
#घोषणा  PCI_BIST_CODE_MASK	0x0f	/* Return result */
#घोषणा  PCI_BIST_START		0x40	/* 1 to start BIST, 2 secs or less */
#घोषणा  PCI_BIST_CAPABLE	0x80	/* 1 अगर BIST capable */

/*
 * Base addresses specअगरy locations in memory or I/O space.
 * Decoded size can be determined by writing a value of
 * 0xffffffff to the रेजिस्टर, and पढ़ोing it back.  Only
 * 1 bits are decoded.
 */
#घोषणा PCI_BASE_ADDRESS_0	0x10	/* 32 bits */
#घोषणा PCI_BASE_ADDRESS_1	0x14	/* 32 bits [htype 0,1 only] */
#घोषणा PCI_BASE_ADDRESS_2	0x18	/* 32 bits [htype 0 only] */
#घोषणा PCI_BASE_ADDRESS_3	0x1c	/* 32 bits */
#घोषणा PCI_BASE_ADDRESS_4	0x20	/* 32 bits */
#घोषणा PCI_BASE_ADDRESS_5	0x24	/* 32 bits */
#घोषणा  PCI_BASE_ADDRESS_SPACE		0x01	/* 0 = memory, 1 = I/O */
#घोषणा  PCI_BASE_ADDRESS_SPACE_IO	0x01
#घोषणा  PCI_BASE_ADDRESS_SPACE_MEMORY	0x00
#घोषणा  PCI_BASE_ADDRESS_MEM_TYPE_MASK	0x06
#घोषणा  PCI_BASE_ADDRESS_MEM_TYPE_32	0x00	/* 32 bit address */
#घोषणा  PCI_BASE_ADDRESS_MEM_TYPE_1M	0x02	/* Below 1M [obsolete] */
#घोषणा  PCI_BASE_ADDRESS_MEM_TYPE_64	0x04	/* 64 bit address */
#घोषणा  PCI_BASE_ADDRESS_MEM_PREFETCH	0x08	/* prefetchable? */
#घोषणा  PCI_BASE_ADDRESS_MEM_MASK	(~0x0fUL)
#घोषणा  PCI_BASE_ADDRESS_IO_MASK	(~0x03UL)
/* bit 1 is reserved अगर address_space = 1 */

/* Header type 0 (normal devices) */
#घोषणा PCI_CARDBUS_CIS		0x28
#घोषणा PCI_SUBSYSTEM_VENDOR_ID	0x2c
#घोषणा PCI_SUBSYSTEM_ID	0x2e
#घोषणा PCI_ROM_ADDRESS		0x30	/* Bits 31..11 are address, 10..1 reserved */
#घोषणा  PCI_ROM_ADDRESS_ENABLE	0x01
#घोषणा PCI_ROM_ADDRESS_MASK	(~0x7ffU)

#घोषणा PCI_CAPABILITY_LIST	0x34	/* Offset of first capability list entry */

/* 0x35-0x3b are reserved */
#घोषणा PCI_INTERRUPT_LINE	0x3c	/* 8 bits */
#घोषणा PCI_INTERRUPT_PIN	0x3d	/* 8 bits */
#घोषणा PCI_MIN_GNT		0x3e	/* 8 bits */
#घोषणा PCI_MAX_LAT		0x3f	/* 8 bits */

/* Header type 1 (PCI-to-PCI bridges) */
#घोषणा PCI_PRIMARY_BUS		0x18	/* Primary bus number */
#घोषणा PCI_SECONDARY_BUS	0x19	/* Secondary bus number */
#घोषणा PCI_SUBORDINATE_BUS	0x1a	/* Highest bus number behind the bridge */
#घोषणा PCI_SEC_LATENCY_TIMER	0x1b	/* Latency समयr क्रम secondary पूर्णांकerface */
#घोषणा PCI_IO_BASE		0x1c	/* I/O range behind the bridge */
#घोषणा PCI_IO_LIMIT		0x1d
#घोषणा  PCI_IO_RANGE_TYPE_MASK	0x0fUL	/* I/O bridging type */
#घोषणा  PCI_IO_RANGE_TYPE_16	0x00
#घोषणा  PCI_IO_RANGE_TYPE_32	0x01
#घोषणा  PCI_IO_RANGE_MASK	(~0x0fUL) /* Standard 4K I/O winकरोws */
#घोषणा  PCI_IO_1K_RANGE_MASK	(~0x03UL) /* Intel 1K I/O winकरोws */
#घोषणा PCI_SEC_STATUS		0x1e	/* Secondary status रेजिस्टर, only bit 14 used */
#घोषणा PCI_MEMORY_BASE		0x20	/* Memory range behind */
#घोषणा PCI_MEMORY_LIMIT	0x22
#घोषणा  PCI_MEMORY_RANGE_TYPE_MASK 0x0fUL
#घोषणा  PCI_MEMORY_RANGE_MASK	(~0x0fUL)
#घोषणा PCI_PREF_MEMORY_BASE	0x24	/* Prefetchable memory range behind */
#घोषणा PCI_PREF_MEMORY_LIMIT	0x26
#घोषणा  PCI_PREF_RANGE_TYPE_MASK 0x0fUL
#घोषणा  PCI_PREF_RANGE_TYPE_32	0x00
#घोषणा  PCI_PREF_RANGE_TYPE_64	0x01
#घोषणा  PCI_PREF_RANGE_MASK	(~0x0fUL)
#घोषणा PCI_PREF_BASE_UPPER32	0x28	/* Upper half of prefetchable memory range */
#घोषणा PCI_PREF_LIMIT_UPPER32	0x2c
#घोषणा PCI_IO_BASE_UPPER16	0x30	/* Upper half of I/O addresses */
#घोषणा PCI_IO_LIMIT_UPPER16	0x32
/* 0x34 same as क्रम htype 0 */
/* 0x35-0x3b is reserved */
#घोषणा PCI_ROM_ADDRESS1	0x38	/* Same as PCI_ROM_ADDRESS, but क्रम htype 1 */
/* 0x3c-0x3d are same as क्रम htype 0 */
#घोषणा PCI_BRIDGE_CONTROL	0x3e
#घोषणा  PCI_BRIDGE_CTL_PARITY	0x01	/* Enable parity detection on secondary पूर्णांकerface */
#घोषणा  PCI_BRIDGE_CTL_SERR	0x02	/* The same क्रम SERR क्रमwarding */
#घोषणा  PCI_BRIDGE_CTL_ISA	0x04	/* Enable ISA mode */
#घोषणा  PCI_BRIDGE_CTL_VGA	0x08	/* Forward VGA addresses */
#घोषणा  PCI_BRIDGE_CTL_MASTER_ABORT	0x20  /* Report master पातs */
#घोषणा  PCI_BRIDGE_CTL_BUS_RESET	0x40	/* Secondary bus reset */
#घोषणा  PCI_BRIDGE_CTL_FAST_BACK	0x80	/* Fast Back2Back enabled on secondary पूर्णांकerface */

/* Header type 2 (CardBus bridges) */
#घोषणा PCI_CB_CAPABILITY_LIST	0x14
/* 0x15 reserved */
#घोषणा PCI_CB_SEC_STATUS	0x16	/* Secondary status */
#घोषणा PCI_CB_PRIMARY_BUS	0x18	/* PCI bus number */
#घोषणा PCI_CB_CARD_BUS		0x19	/* CardBus bus number */
#घोषणा PCI_CB_SUBORDINATE_BUS	0x1a	/* Subordinate bus number */
#घोषणा PCI_CB_LATENCY_TIMER	0x1b	/* CardBus latency समयr */
#घोषणा PCI_CB_MEMORY_BASE_0	0x1c
#घोषणा PCI_CB_MEMORY_LIMIT_0	0x20
#घोषणा PCI_CB_MEMORY_BASE_1	0x24
#घोषणा PCI_CB_MEMORY_LIMIT_1	0x28
#घोषणा PCI_CB_IO_BASE_0	0x2c
#घोषणा PCI_CB_IO_BASE_0_HI	0x2e
#घोषणा PCI_CB_IO_LIMIT_0	0x30
#घोषणा PCI_CB_IO_LIMIT_0_HI	0x32
#घोषणा PCI_CB_IO_BASE_1	0x34
#घोषणा PCI_CB_IO_BASE_1_HI	0x36
#घोषणा PCI_CB_IO_LIMIT_1	0x38
#घोषणा PCI_CB_IO_LIMIT_1_HI	0x3a
#घोषणा  PCI_CB_IO_RANGE_MASK	(~0x03UL)
/* 0x3c-0x3d are same as क्रम htype 0 */
#घोषणा PCI_CB_BRIDGE_CONTROL	0x3e
#घोषणा  PCI_CB_BRIDGE_CTL_PARITY	0x01	/* Similar to standard bridge control रेजिस्टर */
#घोषणा  PCI_CB_BRIDGE_CTL_SERR		0x02
#घोषणा  PCI_CB_BRIDGE_CTL_ISA		0x04
#घोषणा  PCI_CB_BRIDGE_CTL_VGA		0x08
#घोषणा  PCI_CB_BRIDGE_CTL_MASTER_ABORT	0x20
#घोषणा  PCI_CB_BRIDGE_CTL_CB_RESET	0x40	/* CardBus reset */
#घोषणा  PCI_CB_BRIDGE_CTL_16BIT_INT	0x80	/* Enable पूर्णांकerrupt क्रम 16-bit cards */
#घोषणा  PCI_CB_BRIDGE_CTL_PREFETCH_MEM0 0x100	/* Prefetch enable क्रम both memory regions */
#घोषणा  PCI_CB_BRIDGE_CTL_PREFETCH_MEM1 0x200
#घोषणा  PCI_CB_BRIDGE_CTL_POST_WRITES	0x400
#घोषणा PCI_CB_SUBSYSTEM_VENDOR_ID	0x40
#घोषणा PCI_CB_SUBSYSTEM_ID		0x42
#घोषणा PCI_CB_LEGACY_MODE_BASE		0x44	/* 16-bit PC Card legacy mode base address (ExCa) */
/* 0x48-0x7f reserved */

/* Capability lists */

#घोषणा PCI_CAP_LIST_ID		0	/* Capability ID */
#घोषणा  PCI_CAP_ID_PM		0x01	/* Power Management */
#घोषणा  PCI_CAP_ID_AGP		0x02	/* Accelerated Graphics Port */
#घोषणा  PCI_CAP_ID_VPD		0x03	/* Vital Product Data */
#घोषणा  PCI_CAP_ID_SLOTID	0x04	/* Slot Identअगरication */
#घोषणा  PCI_CAP_ID_MSI		0x05	/* Message Signalled Interrupts */
#घोषणा  PCI_CAP_ID_CHSWP	0x06	/* CompactPCI HotSwap */
#घोषणा  PCI_CAP_ID_PCIX	0x07	/* PCI-X */
#घोषणा  PCI_CAP_ID_HT		0x08	/* HyperTransport */
#घोषणा  PCI_CAP_ID_VNDR	0x09	/* Venकरोr-Specअगरic */
#घोषणा  PCI_CAP_ID_DBG		0x0A	/* Debug port */
#घोषणा  PCI_CAP_ID_CCRC	0x0B	/* CompactPCI Central Resource Control */
#घोषणा  PCI_CAP_ID_SHPC	0x0C	/* PCI Standard Hot-Plug Controller */
#घोषणा  PCI_CAP_ID_SSVID	0x0D	/* Bridge subप्रणाली venकरोr/device ID */
#घोषणा  PCI_CAP_ID_AGP3	0x0E	/* AGP Target PCI-PCI bridge */
#घोषणा  PCI_CAP_ID_SECDEV	0x0F	/* Secure Device */
#घोषणा  PCI_CAP_ID_EXP		0x10	/* PCI Express */
#घोषणा  PCI_CAP_ID_MSIX	0x11	/* MSI-X */
#घोषणा  PCI_CAP_ID_SATA	0x12	/* SATA Data/Index Conf. */
#घोषणा  PCI_CAP_ID_AF		0x13	/* PCI Advanced Features */
#घोषणा  PCI_CAP_ID_EA		0x14	/* PCI Enhanced Allocation */
#घोषणा  PCI_CAP_ID_MAX		PCI_CAP_ID_EA
#घोषणा PCI_CAP_LIST_NEXT	1	/* Next capability in the list */
#घोषणा PCI_CAP_FLAGS		2	/* Capability defined flags (16 bits) */
#घोषणा PCI_CAP_SIZखातापूर्ण		4

/* Power Management Registers */

#घोषणा PCI_PM_PMC		2	/* PM Capabilities Register */
#घोषणा  PCI_PM_CAP_VER_MASK	0x0007	/* Version */
#घोषणा  PCI_PM_CAP_PME_CLOCK	0x0008	/* PME घड़ी required */
#घोषणा  PCI_PM_CAP_RESERVED    0x0010  /* Reserved field */
#घोषणा  PCI_PM_CAP_DSI		0x0020	/* Device specअगरic initialization */
#घोषणा  PCI_PM_CAP_AUX_POWER	0x01C0	/* Auxiliary घातer support mask */
#घोषणा  PCI_PM_CAP_D1		0x0200	/* D1 घातer state support */
#घोषणा  PCI_PM_CAP_D2		0x0400	/* D2 घातer state support */
#घोषणा  PCI_PM_CAP_PME		0x0800	/* PME pin supported */
#घोषणा  PCI_PM_CAP_PME_MASK	0xF800	/* PME Mask of all supported states */
#घोषणा  PCI_PM_CAP_PME_D0	0x0800	/* PME# from D0 */
#घोषणा  PCI_PM_CAP_PME_D1	0x1000	/* PME# from D1 */
#घोषणा  PCI_PM_CAP_PME_D2	0x2000	/* PME# from D2 */
#घोषणा  PCI_PM_CAP_PME_D3hot	0x4000	/* PME# from D3 (hot) */
#घोषणा  PCI_PM_CAP_PME_D3cold	0x8000	/* PME# from D3 (cold) */
#घोषणा  PCI_PM_CAP_PME_SHIFT	11	/* Start of the PME Mask in PMC */
#घोषणा PCI_PM_CTRL		4	/* PM control and status रेजिस्टर */
#घोषणा  PCI_PM_CTRL_STATE_MASK	0x0003	/* Current घातer state (D0 to D3) */
#घोषणा  PCI_PM_CTRL_NO_SOFT_RESET	0x0008	/* No reset क्रम D3hot->D0 */
#घोषणा  PCI_PM_CTRL_PME_ENABLE	0x0100	/* PME pin enable */
#घोषणा  PCI_PM_CTRL_DATA_SEL_MASK	0x1e00	/* Data select (??) */
#घोषणा  PCI_PM_CTRL_DATA_SCALE_MASK	0x6000	/* Data scale (??) */
#घोषणा  PCI_PM_CTRL_PME_STATUS	0x8000	/* PME pin status */
#घोषणा PCI_PM_PPB_EXTENSIONS	6	/* PPB support extensions (??) */
#घोषणा  PCI_PM_PPB_B2_B3	0x40	/* Stop घड़ी when in D3hot (??) */
#घोषणा  PCI_PM_BPCC_ENABLE	0x80	/* Bus घातer/घड़ी control enable (??) */
#घोषणा PCI_PM_DATA_REGISTER	7	/* (??) */
#घोषणा PCI_PM_SIZखातापूर्ण		8

/* AGP रेजिस्टरs */

#घोषणा PCI_AGP_VERSION		2	/* BCD version number */
#घोषणा PCI_AGP_RFU		3	/* Rest of capability flags */
#घोषणा PCI_AGP_STATUS		4	/* Status रेजिस्टर */
#घोषणा  PCI_AGP_STATUS_RQ_MASK	0xff000000	/* Maximum number of requests - 1 */
#घोषणा  PCI_AGP_STATUS_SBA	0x0200	/* Sideband addressing supported */
#घोषणा  PCI_AGP_STATUS_64BIT	0x0020	/* 64-bit addressing supported */
#घोषणा  PCI_AGP_STATUS_FW	0x0010	/* FW transfers supported */
#घोषणा  PCI_AGP_STATUS_RATE4	0x0004	/* 4x transfer rate supported */
#घोषणा  PCI_AGP_STATUS_RATE2	0x0002	/* 2x transfer rate supported */
#घोषणा  PCI_AGP_STATUS_RATE1	0x0001	/* 1x transfer rate supported */
#घोषणा PCI_AGP_COMMAND		8	/* Control रेजिस्टर */
#घोषणा  PCI_AGP_COMMAND_RQ_MASK 0xff000000  /* Master: Maximum number of requests */
#घोषणा  PCI_AGP_COMMAND_SBA	0x0200	/* Sideband addressing enabled */
#घोषणा  PCI_AGP_COMMAND_AGP	0x0100	/* Allow processing of AGP transactions */
#घोषणा  PCI_AGP_COMMAND_64BIT	0x0020	/* Allow processing of 64-bit addresses */
#घोषणा  PCI_AGP_COMMAND_FW	0x0010	/* Force FW transfers */
#घोषणा  PCI_AGP_COMMAND_RATE4	0x0004	/* Use 4x rate */
#घोषणा  PCI_AGP_COMMAND_RATE2	0x0002	/* Use 2x rate */
#घोषणा  PCI_AGP_COMMAND_RATE1	0x0001	/* Use 1x rate */
#घोषणा PCI_AGP_SIZखातापूर्ण		12

/* Vital Product Data */

#घोषणा PCI_VPD_ADDR		2	/* Address to access (15 bits!) */
#घोषणा  PCI_VPD_ADDR_MASK	0x7fff	/* Address mask */
#घोषणा  PCI_VPD_ADDR_F		0x8000	/* Write 0, 1 indicates completion */
#घोषणा PCI_VPD_DATA		4	/* 32-bits of data वापसed here */
#घोषणा PCI_CAP_VPD_SIZखातापूर्ण	8

/* Slot Identअगरication */

#घोषणा PCI_SID_ESR		2	/* Expansion Slot Register */
#घोषणा  PCI_SID_ESR_NSLOTS	0x1f	/* Number of expansion slots available */
#घोषणा  PCI_SID_ESR_FIC	0x20	/* First In Chassis Flag */
#घोषणा PCI_SID_CHASSIS_NR	3	/* Chassis Number */

/* Message Signalled Interrupt रेजिस्टरs */

#घोषणा PCI_MSI_FLAGS		2	/* Message Control */
#घोषणा  PCI_MSI_FLAGS_ENABLE	0x0001	/* MSI feature enabled */
#घोषणा  PCI_MSI_FLAGS_QMASK	0x000e	/* Maximum queue size available */
#घोषणा  PCI_MSI_FLAGS_QSIZE	0x0070	/* Message queue size configured */
#घोषणा  PCI_MSI_FLAGS_64BIT	0x0080	/* 64-bit addresses allowed */
#घोषणा  PCI_MSI_FLAGS_MASKBIT	0x0100	/* Per-vector masking capable */
#घोषणा PCI_MSI_RFU		3	/* Rest of capability flags */
#घोषणा PCI_MSI_ADDRESS_LO	4	/* Lower 32 bits */
#घोषणा PCI_MSI_ADDRESS_HI	8	/* Upper 32 bits (अगर PCI_MSI_FLAGS_64BIT set) */
#घोषणा PCI_MSI_DATA_32		8	/* 16 bits of data क्रम 32-bit devices */
#घोषणा PCI_MSI_MASK_32		12	/* Mask bits रेजिस्टर क्रम 32-bit devices */
#घोषणा PCI_MSI_PENDING_32	16	/* Pending पूर्णांकrs क्रम 32-bit devices */
#घोषणा PCI_MSI_DATA_64		12	/* 16 bits of data क्रम 64-bit devices */
#घोषणा PCI_MSI_MASK_64		16	/* Mask bits रेजिस्टर क्रम 64-bit devices */
#घोषणा PCI_MSI_PENDING_64	20	/* Pending पूर्णांकrs क्रम 64-bit devices */

/* MSI-X रेजिस्टरs (in MSI-X capability) */
#घोषणा PCI_MSIX_FLAGS		2	/* Message Control */
#घोषणा  PCI_MSIX_FLAGS_QSIZE	0x07FF	/* Table size */
#घोषणा  PCI_MSIX_FLAGS_MASKALL	0x4000	/* Mask all vectors क्रम this function */
#घोषणा  PCI_MSIX_FLAGS_ENABLE	0x8000	/* MSI-X enable */
#घोषणा PCI_MSIX_TABLE		4	/* Table offset */
#घोषणा  PCI_MSIX_TABLE_BIR	0x00000007 /* BAR index */
#घोषणा  PCI_MSIX_TABLE_OFFSET	0xfffffff8 /* Offset पूर्णांकo specअगरied BAR */
#घोषणा PCI_MSIX_PBA		8	/* Pending Bit Array offset */
#घोषणा  PCI_MSIX_PBA_BIR	0x00000007 /* BAR index */
#घोषणा  PCI_MSIX_PBA_OFFSET	0xfffffff8 /* Offset पूर्णांकo specअगरied BAR */
#घोषणा PCI_MSIX_FLAGS_BIRMASK	PCI_MSIX_PBA_BIR /* deprecated */
#घोषणा PCI_CAP_MSIX_SIZखातापूर्ण	12	/* size of MSIX रेजिस्टरs */

/* MSI-X Table entry क्रमmat (in memory mapped by a BAR) */
#घोषणा PCI_MSIX_ENTRY_SIZE		16
#घोषणा PCI_MSIX_ENTRY_LOWER_ADDR	0  /* Message Address */
#घोषणा PCI_MSIX_ENTRY_UPPER_ADDR	4  /* Message Upper Address */
#घोषणा PCI_MSIX_ENTRY_DATA		8  /* Message Data */
#घोषणा PCI_MSIX_ENTRY_VECTOR_CTRL	12 /* Vector Control */
#घोषणा  PCI_MSIX_ENTRY_CTRL_MASKBIT	0x00000001

/* CompactPCI Hotswap Register */

#घोषणा PCI_CHSWP_CSR		2	/* Control and Status Register */
#घोषणा  PCI_CHSWP_DHA		0x01	/* Device Hiding Arm */
#घोषणा  PCI_CHSWP_EIM		0x02	/* ENUM# Signal Mask */
#घोषणा  PCI_CHSWP_PIE		0x04	/* Pending Insert or Extract */
#घोषणा  PCI_CHSWP_LOO		0x08	/* LED On / Off */
#घोषणा  PCI_CHSWP_PI		0x30	/* Programming Interface */
#घोषणा  PCI_CHSWP_EXT		0x40	/* ENUM# status - extraction */
#घोषणा  PCI_CHSWP_INS		0x80	/* ENUM# status - insertion */

/* PCI Advanced Feature रेजिस्टरs */

#घोषणा PCI_AF_LENGTH		2
#घोषणा PCI_AF_CAP		3
#घोषणा  PCI_AF_CAP_TP		0x01
#घोषणा  PCI_AF_CAP_FLR		0x02
#घोषणा PCI_AF_CTRL		4
#घोषणा  PCI_AF_CTRL_FLR	0x01
#घोषणा PCI_AF_STATUS		5
#घोषणा  PCI_AF_STATUS_TP	0x01
#घोषणा PCI_CAP_AF_SIZखातापूर्ण	6	/* size of AF रेजिस्टरs */

/* PCI Enhanced Allocation रेजिस्टरs */

#घोषणा PCI_EA_NUM_ENT		2	/* Number of Capability Entries */
#घोषणा  PCI_EA_NUM_ENT_MASK	0x3f	/* Num Entries Mask */
#घोषणा PCI_EA_FIRST_ENT	4	/* First EA Entry in List */
#घोषणा PCI_EA_FIRST_ENT_BRIDGE	8	/* First EA Entry क्रम Bridges */
#घोषणा  PCI_EA_ES		0x00000007 /* Entry Size */
#घोषणा  PCI_EA_BEI		0x000000f0 /* BAR Equivalent Indicator */

/* EA fixed Secondary and Subordinate bus numbers क्रम Bridge */
#घोषणा PCI_EA_SEC_BUS_MASK	0xff
#घोषणा PCI_EA_SUB_BUS_MASK	0xff00
#घोषणा PCI_EA_SUB_BUS_SHIFT	8

/* 0-5 map to BARs 0-5 respectively */
#घोषणा   PCI_EA_BEI_BAR0		0
#घोषणा   PCI_EA_BEI_BAR5		5
#घोषणा   PCI_EA_BEI_BRIDGE		6	/* Resource behind bridge */
#घोषणा   PCI_EA_BEI_ENI		7	/* Equivalent Not Indicated */
#घोषणा   PCI_EA_BEI_ROM		8	/* Expansion ROM */
/* 9-14 map to VF BARs 0-5 respectively */
#घोषणा   PCI_EA_BEI_VF_BAR0		9
#घोषणा   PCI_EA_BEI_VF_BAR5		14
#घोषणा   PCI_EA_BEI_RESERVED		15	/* Reserved - Treat like ENI */
#घोषणा  PCI_EA_PP		0x0000ff00	/* Primary Properties */
#घोषणा  PCI_EA_SP		0x00ff0000	/* Secondary Properties */
#घोषणा   PCI_EA_P_MEM			0x00	/* Non-Prefetch Memory */
#घोषणा   PCI_EA_P_MEM_PREFETCH		0x01	/* Prefetchable Memory */
#घोषणा   PCI_EA_P_IO			0x02	/* I/O Space */
#घोषणा   PCI_EA_P_VF_MEM_PREFETCH	0x03	/* VF Prefetchable Memory */
#घोषणा   PCI_EA_P_VF_MEM		0x04	/* VF Non-Prefetch Memory */
#घोषणा   PCI_EA_P_BRIDGE_MEM		0x05	/* Bridge Non-Prefetch Memory */
#घोषणा   PCI_EA_P_BRIDGE_MEM_PREFETCH	0x06	/* Bridge Prefetchable Memory */
#घोषणा   PCI_EA_P_BRIDGE_IO		0x07	/* Bridge I/O Space */
/* 0x08-0xfc reserved */
#घोषणा   PCI_EA_P_MEM_RESERVED		0xfd	/* Reserved Memory */
#घोषणा   PCI_EA_P_IO_RESERVED		0xfe	/* Reserved I/O Space */
#घोषणा   PCI_EA_P_UNAVAILABLE		0xff	/* Entry Unavailable */
#घोषणा  PCI_EA_WRITABLE	0x40000000	/* Writable: 1 = RW, 0 = HwInit */
#घोषणा  PCI_EA_ENABLE		0x80000000	/* Enable क्रम this entry */
#घोषणा PCI_EA_BASE		4		/* Base Address Offset */
#घोषणा PCI_EA_MAX_OFFSET	8		/* MaxOffset (resource length) */
/* bit 0 is reserved */
#घोषणा  PCI_EA_IS_64		0x00000002	/* 64-bit field flag */
#घोषणा  PCI_EA_FIELD_MASK	0xfffffffc	/* For Base & Max Offset */

/* PCI-X रेजिस्टरs (Type 0 (non-bridge) devices) */

#घोषणा PCI_X_CMD		2	/* Modes & Features */
#घोषणा  PCI_X_CMD_DPERR_E	0x0001	/* Data Parity Error Recovery Enable */
#घोषणा  PCI_X_CMD_ERO		0x0002	/* Enable Relaxed Ordering */
#घोषणा  PCI_X_CMD_READ_512	0x0000	/* 512 byte maximum पढ़ो byte count */
#घोषणा  PCI_X_CMD_READ_1K	0x0004	/* 1Kbyte maximum पढ़ो byte count */
#घोषणा  PCI_X_CMD_READ_2K	0x0008	/* 2Kbyte maximum पढ़ो byte count */
#घोषणा  PCI_X_CMD_READ_4K	0x000c	/* 4Kbyte maximum पढ़ो byte count */
#घोषणा  PCI_X_CMD_MAX_READ	0x000c	/* Max Memory Read Byte Count */
				/* Max # of outstanding split transactions */
#घोषणा  PCI_X_CMD_SPLIT_1	0x0000	/* Max 1 */
#घोषणा  PCI_X_CMD_SPLIT_2	0x0010	/* Max 2 */
#घोषणा  PCI_X_CMD_SPLIT_3	0x0020	/* Max 3 */
#घोषणा  PCI_X_CMD_SPLIT_4	0x0030	/* Max 4 */
#घोषणा  PCI_X_CMD_SPLIT_8	0x0040	/* Max 8 */
#घोषणा  PCI_X_CMD_SPLIT_12	0x0050	/* Max 12 */
#घोषणा  PCI_X_CMD_SPLIT_16	0x0060	/* Max 16 */
#घोषणा  PCI_X_CMD_SPLIT_32	0x0070	/* Max 32 */
#घोषणा  PCI_X_CMD_MAX_SPLIT	0x0070	/* Max Outstanding Split Transactions */
#घोषणा  PCI_X_CMD_VERSION(x)	(((x) >> 12) & 3) /* Version */
#घोषणा PCI_X_STATUS		4	/* PCI-X capabilities */
#घोषणा  PCI_X_STATUS_DEVFN	0x000000ff	/* A copy of devfn */
#घोषणा  PCI_X_STATUS_BUS	0x0000ff00	/* A copy of bus nr */
#घोषणा  PCI_X_STATUS_64BIT	0x00010000	/* 64-bit device */
#घोषणा  PCI_X_STATUS_133MHZ	0x00020000	/* 133 MHz capable */
#घोषणा  PCI_X_STATUS_SPL_DISC	0x00040000	/* Split Completion Discarded */
#घोषणा  PCI_X_STATUS_UNX_SPL	0x00080000	/* Unexpected Split Completion */
#घोषणा  PCI_X_STATUS_COMPLEX	0x00100000	/* Device Complनिकासy */
#घोषणा  PCI_X_STATUS_MAX_READ	0x00600000	/* Deचिन्हित Max Memory Read Count */
#घोषणा  PCI_X_STATUS_MAX_SPLIT	0x03800000	/* Deचिन्हित Max Outstanding Split Transactions */
#घोषणा  PCI_X_STATUS_MAX_CUM	0x1c000000	/* Deचिन्हित Max Cumulative Read Size */
#घोषणा  PCI_X_STATUS_SPL_ERR	0x20000000	/* Rcvd Split Completion Error Msg */
#घोषणा  PCI_X_STATUS_266MHZ	0x40000000	/* 266 MHz capable */
#घोषणा  PCI_X_STATUS_533MHZ	0x80000000	/* 533 MHz capable */
#घोषणा PCI_X_ECC_CSR		8	/* ECC control and status */
#घोषणा PCI_CAP_PCIX_SIZखातापूर्ण_V0	8	/* size of रेजिस्टरs क्रम Version 0 */
#घोषणा PCI_CAP_PCIX_SIZखातापूर्ण_V1	24	/* size क्रम Version 1 */
#घोषणा PCI_CAP_PCIX_SIZखातापूर्ण_V2	PCI_CAP_PCIX_SIZखातापूर्ण_V1	/* Same क्रम v2 */

/* PCI-X रेजिस्टरs (Type 1 (bridge) devices) */

#घोषणा PCI_X_BRIDGE_SSTATUS	2	/* Secondary Status */
#घोषणा  PCI_X_SSTATUS_64BIT	0x0001	/* Secondary AD पूर्णांकerface is 64 bits */
#घोषणा  PCI_X_SSTATUS_133MHZ	0x0002	/* 133 MHz capable */
#घोषणा  PCI_X_SSTATUS_FREQ	0x03c0	/* Secondary Bus Mode and Frequency */
#घोषणा  PCI_X_SSTATUS_VERS	0x3000	/* PCI-X Capability Version */
#घोषणा  PCI_X_SSTATUS_V1	0x1000	/* Mode 2, not Mode 1 */
#घोषणा  PCI_X_SSTATUS_V2	0x2000	/* Mode 1 or Modes 1 and 2 */
#घोषणा  PCI_X_SSTATUS_266MHZ	0x4000	/* 266 MHz capable */
#घोषणा  PCI_X_SSTATUS_533MHZ	0x8000	/* 533 MHz capable */
#घोषणा PCI_X_BRIDGE_STATUS	4	/* Bridge Status */

/* PCI Bridge Subप्रणाली ID रेजिस्टरs */

#घोषणा PCI_SSVID_VENDOR_ID     4	/* PCI Bridge subप्रणाली venकरोr ID */
#घोषणा PCI_SSVID_DEVICE_ID     6	/* PCI Bridge subप्रणाली device ID */

/* PCI Express capability रेजिस्टरs */

#घोषणा PCI_EXP_FLAGS		2	/* Capabilities रेजिस्टर */
#घोषणा  PCI_EXP_FLAGS_VERS	0x000f	/* Capability version */
#घोषणा  PCI_EXP_FLAGS_TYPE	0x00f0	/* Device/Port type */
#घोषणा   PCI_EXP_TYPE_ENDPOINT	   0x0	/* Express Endpoपूर्णांक */
#घोषणा   PCI_EXP_TYPE_LEG_END	   0x1	/* Legacy Endpoपूर्णांक */
#घोषणा   PCI_EXP_TYPE_ROOT_PORT   0x4	/* Root Port */
#घोषणा   PCI_EXP_TYPE_UPSTREAM	   0x5	/* Upstream Port */
#घोषणा   PCI_EXP_TYPE_DOWNSTREAM  0x6	/* Downstream Port */
#घोषणा   PCI_EXP_TYPE_PCI_BRIDGE  0x7	/* PCIe to PCI/PCI-X Bridge */
#घोषणा   PCI_EXP_TYPE_PCIE_BRIDGE 0x8	/* PCI/PCI-X to PCIe Bridge */
#घोषणा   PCI_EXP_TYPE_RC_END	   0x9	/* Root Complex Integrated Endpoपूर्णांक */
#घोषणा   PCI_EXP_TYPE_RC_EC	   0xa	/* Root Complex Event Collector */
#घोषणा  PCI_EXP_FLAGS_SLOT	0x0100	/* Slot implemented */
#घोषणा  PCI_EXP_FLAGS_IRQ	0x3e00	/* Interrupt message number */
#घोषणा PCI_EXP_DEVCAP		4	/* Device capabilities */
#घोषणा  PCI_EXP_DEVCAP_PAYLOAD	0x00000007 /* Max_Payload_Size */
#घोषणा  PCI_EXP_DEVCAP_PHANTOM	0x00000018 /* Phantom functions */
#घोषणा  PCI_EXP_DEVCAP_EXT_TAG	0x00000020 /* Extended tags */
#घोषणा  PCI_EXP_DEVCAP_L0S	0x000001c0 /* L0s Acceptable Latency */
#घोषणा  PCI_EXP_DEVCAP_L1	0x00000e00 /* L1 Acceptable Latency */
#घोषणा  PCI_EXP_DEVCAP_ATN_BUT	0x00001000 /* Attention Button Present */
#घोषणा  PCI_EXP_DEVCAP_ATN_IND	0x00002000 /* Attention Indicator Present */
#घोषणा  PCI_EXP_DEVCAP_PWR_IND	0x00004000 /* Power Indicator Present */
#घोषणा  PCI_EXP_DEVCAP_RBER	0x00008000 /* Role-Based Error Reporting */
#घोषणा  PCI_EXP_DEVCAP_PWR_VAL	0x03fc0000 /* Slot Power Limit Value */
#घोषणा  PCI_EXP_DEVCAP_PWR_SCL	0x0c000000 /* Slot Power Limit Scale */
#घोषणा  PCI_EXP_DEVCAP_FLR     0x10000000 /* Function Level Reset */
#घोषणा PCI_EXP_DEVCTL		8	/* Device Control */
#घोषणा  PCI_EXP_DEVCTL_CERE	0x0001	/* Correctable Error Reporting En. */
#घोषणा  PCI_EXP_DEVCTL_NFERE	0x0002	/* Non-Fatal Error Reporting Enable */
#घोषणा  PCI_EXP_DEVCTL_FERE	0x0004	/* Fatal Error Reporting Enable */
#घोषणा  PCI_EXP_DEVCTL_URRE	0x0008	/* Unsupported Request Reporting En. */
#घोषणा  PCI_EXP_DEVCTL_RELAX_EN 0x0010 /* Enable relaxed ordering */
#घोषणा  PCI_EXP_DEVCTL_PAYLOAD	0x00e0	/* Max_Payload_Size */
#घोषणा  PCI_EXP_DEVCTL_EXT_TAG	0x0100	/* Extended Tag Field Enable */
#घोषणा  PCI_EXP_DEVCTL_PHANTOM	0x0200	/* Phantom Functions Enable */
#घोषणा  PCI_EXP_DEVCTL_AUX_PME	0x0400	/* Auxiliary Power PM Enable */
#घोषणा  PCI_EXP_DEVCTL_NOSNOOP_EN 0x0800  /* Enable No Snoop */
#घोषणा  PCI_EXP_DEVCTL_READRQ	0x7000	/* Max_Read_Request_Size */
#घोषणा  PCI_EXP_DEVCTL_READRQ_128B  0x0000 /* 128 Bytes */
#घोषणा  PCI_EXP_DEVCTL_READRQ_256B  0x1000 /* 256 Bytes */
#घोषणा  PCI_EXP_DEVCTL_READRQ_512B  0x2000 /* 512 Bytes */
#घोषणा  PCI_EXP_DEVCTL_READRQ_1024B 0x3000 /* 1024 Bytes */
#घोषणा  PCI_EXP_DEVCTL_READRQ_2048B 0x4000 /* 2048 Bytes */
#घोषणा  PCI_EXP_DEVCTL_READRQ_4096B 0x5000 /* 4096 Bytes */
#घोषणा  PCI_EXP_DEVCTL_BCR_FLR 0x8000  /* Bridge Configuration Retry / FLR */
#घोषणा PCI_EXP_DEVSTA		10	/* Device Status */
#घोषणा  PCI_EXP_DEVSTA_CED	0x0001	/* Correctable Error Detected */
#घोषणा  PCI_EXP_DEVSTA_NFED	0x0002	/* Non-Fatal Error Detected */
#घोषणा  PCI_EXP_DEVSTA_FED	0x0004	/* Fatal Error Detected */
#घोषणा  PCI_EXP_DEVSTA_URD	0x0008	/* Unsupported Request Detected */
#घोषणा  PCI_EXP_DEVSTA_AUXPD	0x0010	/* AUX Power Detected */
#घोषणा  PCI_EXP_DEVSTA_TRPND	0x0020	/* Transactions Pending */
#घोषणा PCI_CAP_EXP_RC_ENDPOINT_SIZखातापूर्ण_V1	12	/* v1 endpoपूर्णांकs without link end here */
#घोषणा PCI_EXP_LNKCAP		12	/* Link Capabilities */
#घोषणा  PCI_EXP_LNKCAP_SLS	0x0000000f /* Supported Link Speeds */
#घोषणा  PCI_EXP_LNKCAP_SLS_2_5GB 0x00000001 /* LNKCAP2 SLS Vector bit 0 */
#घोषणा  PCI_EXP_LNKCAP_SLS_5_0GB 0x00000002 /* LNKCAP2 SLS Vector bit 1 */
#घोषणा  PCI_EXP_LNKCAP_SLS_8_0GB 0x00000003 /* LNKCAP2 SLS Vector bit 2 */
#घोषणा  PCI_EXP_LNKCAP_SLS_16_0GB 0x00000004 /* LNKCAP2 SLS Vector bit 3 */
#घोषणा  PCI_EXP_LNKCAP_SLS_32_0GB 0x00000005 /* LNKCAP2 SLS Vector bit 4 */
#घोषणा  PCI_EXP_LNKCAP_SLS_64_0GB 0x00000006 /* LNKCAP2 SLS Vector bit 5 */
#घोषणा  PCI_EXP_LNKCAP_MLW	0x000003f0 /* Maximum Link Width */
#घोषणा  PCI_EXP_LNKCAP_ASPMS	0x00000c00 /* ASPM Support */
#घोषणा  PCI_EXP_LNKCAP_ASPM_L0S 0x00000400 /* ASPM L0s Support */
#घोषणा  PCI_EXP_LNKCAP_ASPM_L1  0x00000800 /* ASPM L1 Support */
#घोषणा  PCI_EXP_LNKCAP_L0SEL	0x00007000 /* L0s Exit Latency */
#घोषणा  PCI_EXP_LNKCAP_L1EL	0x00038000 /* L1 Exit Latency */
#घोषणा  PCI_EXP_LNKCAP_CLKPM	0x00040000 /* Clock Power Management */
#घोषणा  PCI_EXP_LNKCAP_SDERC	0x00080000 /* Surprise Down Error Reporting Capable */
#घोषणा  PCI_EXP_LNKCAP_DLLLARC	0x00100000 /* Data Link Layer Link Active Reporting Capable */
#घोषणा  PCI_EXP_LNKCAP_LBNC	0x00200000 /* Link Bandwidth Notअगरication Capability */
#घोषणा  PCI_EXP_LNKCAP_PN	0xff000000 /* Port Number */
#घोषणा PCI_EXP_LNKCTL		16	/* Link Control */
#घोषणा  PCI_EXP_LNKCTL_ASPMC	0x0003	/* ASPM Control */
#घोषणा  PCI_EXP_LNKCTL_ASPM_L0S 0x0001	/* L0s Enable */
#घोषणा  PCI_EXP_LNKCTL_ASPM_L1  0x0002	/* L1 Enable */
#घोषणा  PCI_EXP_LNKCTL_RCB	0x0008	/* Read Completion Boundary */
#घोषणा  PCI_EXP_LNKCTL_LD	0x0010	/* Link Disable */
#घोषणा  PCI_EXP_LNKCTL_RL	0x0020	/* Retrain Link */
#घोषणा  PCI_EXP_LNKCTL_CCC	0x0040	/* Common Clock Configuration */
#घोषणा  PCI_EXP_LNKCTL_ES	0x0080	/* Extended Synch */
#घोषणा  PCI_EXP_LNKCTL_CLKREQ_EN 0x0100 /* Enable clkreq */
#घोषणा  PCI_EXP_LNKCTL_HAWD	0x0200	/* Hardware Autonomous Width Disable */
#घोषणा  PCI_EXP_LNKCTL_LBMIE	0x0400	/* Link Bandwidth Management Interrupt Enable */
#घोषणा  PCI_EXP_LNKCTL_LABIE	0x0800	/* Link Autonomous Bandwidth Interrupt Enable */
#घोषणा PCI_EXP_LNKSTA		18	/* Link Status */
#घोषणा  PCI_EXP_LNKSTA_CLS	0x000f	/* Current Link Speed */
#घोषणा  PCI_EXP_LNKSTA_CLS_2_5GB 0x0001 /* Current Link Speed 2.5GT/s */
#घोषणा  PCI_EXP_LNKSTA_CLS_5_0GB 0x0002 /* Current Link Speed 5.0GT/s */
#घोषणा  PCI_EXP_LNKSTA_CLS_8_0GB 0x0003 /* Current Link Speed 8.0GT/s */
#घोषणा  PCI_EXP_LNKSTA_CLS_16_0GB 0x0004 /* Current Link Speed 16.0GT/s */
#घोषणा  PCI_EXP_LNKSTA_CLS_32_0GB 0x0005 /* Current Link Speed 32.0GT/s */
#घोषणा  PCI_EXP_LNKSTA_CLS_64_0GB 0x0006 /* Current Link Speed 64.0GT/s */
#घोषणा  PCI_EXP_LNKSTA_NLW	0x03f0	/* Negotiated Link Width */
#घोषणा  PCI_EXP_LNKSTA_NLW_X1	0x0010	/* Current Link Width x1 */
#घोषणा  PCI_EXP_LNKSTA_NLW_X2	0x0020	/* Current Link Width x2 */
#घोषणा  PCI_EXP_LNKSTA_NLW_X4	0x0040	/* Current Link Width x4 */
#घोषणा  PCI_EXP_LNKSTA_NLW_X8	0x0080	/* Current Link Width x8 */
#घोषणा  PCI_EXP_LNKSTA_NLW_SHIFT 4	/* start of NLW mask in link status */
#घोषणा  PCI_EXP_LNKSTA_LT	0x0800	/* Link Training */
#घोषणा  PCI_EXP_LNKSTA_SLC	0x1000	/* Slot Clock Configuration */
#घोषणा  PCI_EXP_LNKSTA_DLLLA	0x2000	/* Data Link Layer Link Active */
#घोषणा  PCI_EXP_LNKSTA_LBMS	0x4000	/* Link Bandwidth Management Status */
#घोषणा  PCI_EXP_LNKSTA_LABS	0x8000	/* Link Autonomous Bandwidth Status */
#घोषणा PCI_CAP_EXP_ENDPOINT_SIZखातापूर्ण_V1	20	/* v1 endpoपूर्णांकs with link end here */
#घोषणा PCI_EXP_SLTCAP		20	/* Slot Capabilities */
#घोषणा  PCI_EXP_SLTCAP_ABP	0x00000001 /* Attention Button Present */
#घोषणा  PCI_EXP_SLTCAP_PCP	0x00000002 /* Power Controller Present */
#घोषणा  PCI_EXP_SLTCAP_MRLSP	0x00000004 /* MRL Sensor Present */
#घोषणा  PCI_EXP_SLTCAP_AIP	0x00000008 /* Attention Indicator Present */
#घोषणा  PCI_EXP_SLTCAP_PIP	0x00000010 /* Power Indicator Present */
#घोषणा  PCI_EXP_SLTCAP_HPS	0x00000020 /* Hot-Plug Surprise */
#घोषणा  PCI_EXP_SLTCAP_HPC	0x00000040 /* Hot-Plug Capable */
#घोषणा  PCI_EXP_SLTCAP_SPLV	0x00007f80 /* Slot Power Limit Value */
#घोषणा  PCI_EXP_SLTCAP_SPLS	0x00018000 /* Slot Power Limit Scale */
#घोषणा  PCI_EXP_SLTCAP_EIP	0x00020000 /* Electromechanical Interlock Present */
#घोषणा  PCI_EXP_SLTCAP_NCCS	0x00040000 /* No Command Completed Support */
#घोषणा  PCI_EXP_SLTCAP_PSN	0xfff80000 /* Physical Slot Number */
#घोषणा PCI_EXP_SLTCTL		24	/* Slot Control */
#घोषणा  PCI_EXP_SLTCTL_ABPE	0x0001	/* Attention Button Pressed Enable */
#घोषणा  PCI_EXP_SLTCTL_PFDE	0x0002	/* Power Fault Detected Enable */
#घोषणा  PCI_EXP_SLTCTL_MRLSCE	0x0004	/* MRL Sensor Changed Enable */
#घोषणा  PCI_EXP_SLTCTL_PDCE	0x0008	/* Presence Detect Changed Enable */
#घोषणा  PCI_EXP_SLTCTL_CCIE	0x0010	/* Command Completed Interrupt Enable */
#घोषणा  PCI_EXP_SLTCTL_HPIE	0x0020	/* Hot-Plug Interrupt Enable */
#घोषणा  PCI_EXP_SLTCTL_AIC	0x00c0	/* Attention Indicator Control */
#घोषणा  PCI_EXP_SLTCTL_ATTN_IND_SHIFT 6      /* Attention Indicator shअगरt */
#घोषणा  PCI_EXP_SLTCTL_ATTN_IND_ON    0x0040 /* Attention Indicator on */
#घोषणा  PCI_EXP_SLTCTL_ATTN_IND_BLINK 0x0080 /* Attention Indicator blinking */
#घोषणा  PCI_EXP_SLTCTL_ATTN_IND_OFF   0x00c0 /* Attention Indicator off */
#घोषणा  PCI_EXP_SLTCTL_PIC	0x0300	/* Power Indicator Control */
#घोषणा  PCI_EXP_SLTCTL_PWR_IND_ON     0x0100 /* Power Indicator on */
#घोषणा  PCI_EXP_SLTCTL_PWR_IND_BLINK  0x0200 /* Power Indicator blinking */
#घोषणा  PCI_EXP_SLTCTL_PWR_IND_OFF    0x0300 /* Power Indicator off */
#घोषणा  PCI_EXP_SLTCTL_PCC	0x0400	/* Power Controller Control */
#घोषणा  PCI_EXP_SLTCTL_PWR_ON         0x0000 /* Power On */
#घोषणा  PCI_EXP_SLTCTL_PWR_OFF        0x0400 /* Power Off */
#घोषणा  PCI_EXP_SLTCTL_EIC	0x0800	/* Electromechanical Interlock Control */
#घोषणा  PCI_EXP_SLTCTL_DLLSCE	0x1000	/* Data Link Layer State Changed Enable */
#घोषणा  PCI_EXP_SLTCTL_IBPD_DISABLE	0x4000 /* In-band PD disable */
#घोषणा PCI_EXP_SLTSTA		26	/* Slot Status */
#घोषणा  PCI_EXP_SLTSTA_ABP	0x0001	/* Attention Button Pressed */
#घोषणा  PCI_EXP_SLTSTA_PFD	0x0002	/* Power Fault Detected */
#घोषणा  PCI_EXP_SLTSTA_MRLSC	0x0004	/* MRL Sensor Changed */
#घोषणा  PCI_EXP_SLTSTA_PDC	0x0008	/* Presence Detect Changed */
#घोषणा  PCI_EXP_SLTSTA_CC	0x0010	/* Command Completed */
#घोषणा  PCI_EXP_SLTSTA_MRLSS	0x0020	/* MRL Sensor State */
#घोषणा  PCI_EXP_SLTSTA_PDS	0x0040	/* Presence Detect State */
#घोषणा  PCI_EXP_SLTSTA_EIS	0x0080	/* Electromechanical Interlock Status */
#घोषणा  PCI_EXP_SLTSTA_DLLSC	0x0100	/* Data Link Layer State Changed */
#घोषणा PCI_EXP_RTCTL		28	/* Root Control */
#घोषणा  PCI_EXP_RTCTL_SECEE	0x0001	/* System Error on Correctable Error */
#घोषणा  PCI_EXP_RTCTL_SENFEE	0x0002	/* System Error on Non-Fatal Error */
#घोषणा  PCI_EXP_RTCTL_SEFEE	0x0004	/* System Error on Fatal Error */
#घोषणा  PCI_EXP_RTCTL_PMEIE	0x0008	/* PME Interrupt Enable */
#घोषणा  PCI_EXP_RTCTL_CRSSVE	0x0010	/* CRS Software Visibility Enable */
#घोषणा PCI_EXP_RTCAP		30	/* Root Capabilities */
#घोषणा  PCI_EXP_RTCAP_CRSVIS	0x0001	/* CRS Software Visibility capability */
#घोषणा PCI_EXP_RTSTA		32	/* Root Status */
#घोषणा  PCI_EXP_RTSTA_PME	0x00010000 /* PME status */
#घोषणा  PCI_EXP_RTSTA_PENDING	0x00020000 /* PME pending */
/*
 * The Device Capabilities 2, Device Status 2, Device Control 2,
 * Link Capabilities 2, Link Status 2, Link Control 2,
 * Slot Capabilities 2, Slot Status 2, and Slot Control 2 रेजिस्टरs
 * are only present on devices with PCIe Capability version 2.
 * Use pcie_capability_पढ़ो_word() and similar पूर्णांकerfaces to use them
 * safely.
 */
#घोषणा PCI_EXP_DEVCAP2		36	/* Device Capabilities 2 */
#घोषणा  PCI_EXP_DEVCAP2_COMP_TMOUT_DIS	0x00000010 /* Completion Timeout Disable supported */
#घोषणा  PCI_EXP_DEVCAP2_ARI		0x00000020 /* Alternative Routing-ID */
#घोषणा  PCI_EXP_DEVCAP2_ATOMIC_ROUTE	0x00000040 /* Atomic Op routing */
#घोषणा  PCI_EXP_DEVCAP2_ATOMIC_COMP32	0x00000080 /* 32b AtomicOp completion */
#घोषणा  PCI_EXP_DEVCAP2_ATOMIC_COMP64	0x00000100 /* 64b AtomicOp completion */
#घोषणा  PCI_EXP_DEVCAP2_ATOMIC_COMP128	0x00000200 /* 128b AtomicOp completion */
#घोषणा  PCI_EXP_DEVCAP2_LTR		0x00000800 /* Latency tolerance reporting */
#घोषणा  PCI_EXP_DEVCAP2_OBFF_MASK	0x000c0000 /* OBFF support mechanism */
#घोषणा  PCI_EXP_DEVCAP2_OBFF_MSG	0x00040000 /* New message संकेतing */
#घोषणा  PCI_EXP_DEVCAP2_OBFF_WAKE	0x00080000 /* Re-use WAKE# क्रम OBFF */
#घोषणा  PCI_EXP_DEVCAP2_EE_PREFIX	0x00200000 /* End-End TLP Prefix */
#घोषणा PCI_EXP_DEVCTL2		40	/* Device Control 2 */
#घोषणा  PCI_EXP_DEVCTL2_COMP_TIMEOUT	0x000f	/* Completion Timeout Value */
#घोषणा  PCI_EXP_DEVCTL2_COMP_TMOUT_DIS	0x0010	/* Completion Timeout Disable */
#घोषणा  PCI_EXP_DEVCTL2_ARI		0x0020	/* Alternative Routing-ID */
#घोषणा  PCI_EXP_DEVCTL2_ATOMIC_REQ	0x0040	/* Set Atomic requests */
#घोषणा  PCI_EXP_DEVCTL2_ATOMIC_EGRESS_BLOCK 0x0080 /* Block atomic egress */
#घोषणा  PCI_EXP_DEVCTL2_IDO_REQ_EN	0x0100	/* Allow IDO क्रम requests */
#घोषणा  PCI_EXP_DEVCTL2_IDO_CMP_EN	0x0200	/* Allow IDO क्रम completions */
#घोषणा  PCI_EXP_DEVCTL2_LTR_EN		0x0400	/* Enable LTR mechanism */
#घोषणा  PCI_EXP_DEVCTL2_OBFF_MSGA_EN	0x2000	/* Enable OBFF Message type A */
#घोषणा  PCI_EXP_DEVCTL2_OBFF_MSGB_EN	0x4000	/* Enable OBFF Message type B */
#घोषणा  PCI_EXP_DEVCTL2_OBFF_WAKE_EN	0x6000	/* OBFF using WAKE# संकेतing */
#घोषणा PCI_EXP_DEVSTA2		42	/* Device Status 2 */
#घोषणा PCI_CAP_EXP_RC_ENDPOINT_SIZखातापूर्ण_V2	44	/* v2 endpoपूर्णांकs without link end here */
#घोषणा PCI_EXP_LNKCAP2		44	/* Link Capabilities 2 */
#घोषणा  PCI_EXP_LNKCAP2_SLS_2_5GB	0x00000002 /* Supported Speed 2.5GT/s */
#घोषणा  PCI_EXP_LNKCAP2_SLS_5_0GB	0x00000004 /* Supported Speed 5GT/s */
#घोषणा  PCI_EXP_LNKCAP2_SLS_8_0GB	0x00000008 /* Supported Speed 8GT/s */
#घोषणा  PCI_EXP_LNKCAP2_SLS_16_0GB	0x00000010 /* Supported Speed 16GT/s */
#घोषणा  PCI_EXP_LNKCAP2_SLS_32_0GB	0x00000020 /* Supported Speed 32GT/s */
#घोषणा  PCI_EXP_LNKCAP2_SLS_64_0GB	0x00000040 /* Supported Speed 64GT/s */
#घोषणा  PCI_EXP_LNKCAP2_CROSSLINK	0x00000100 /* Crosslink supported */
#घोषणा PCI_EXP_LNKCTL2		48	/* Link Control 2 */
#घोषणा  PCI_EXP_LNKCTL2_TLS		0x000f
#घोषणा  PCI_EXP_LNKCTL2_TLS_2_5GT	0x0001 /* Supported Speed 2.5GT/s */
#घोषणा  PCI_EXP_LNKCTL2_TLS_5_0GT	0x0002 /* Supported Speed 5GT/s */
#घोषणा  PCI_EXP_LNKCTL2_TLS_8_0GT	0x0003 /* Supported Speed 8GT/s */
#घोषणा  PCI_EXP_LNKCTL2_TLS_16_0GT	0x0004 /* Supported Speed 16GT/s */
#घोषणा  PCI_EXP_LNKCTL2_TLS_32_0GT	0x0005 /* Supported Speed 32GT/s */
#घोषणा  PCI_EXP_LNKCTL2_TLS_64_0GT	0x0006 /* Supported Speed 64GT/s */
#घोषणा  PCI_EXP_LNKCTL2_ENTER_COMP	0x0010 /* Enter Compliance */
#घोषणा  PCI_EXP_LNKCTL2_TX_MARGIN	0x0380 /* Transmit Margin */
#घोषणा  PCI_EXP_LNKCTL2_HASD		0x0020 /* HW Autonomous Speed Disable */
#घोषणा PCI_EXP_LNKSTA2		50	/* Link Status 2 */
#घोषणा PCI_CAP_EXP_ENDPOINT_SIZखातापूर्ण_V2	52	/* v2 endpoपूर्णांकs with link end here */
#घोषणा PCI_EXP_SLTCAP2		52	/* Slot Capabilities 2 */
#घोषणा  PCI_EXP_SLTCAP2_IBPD	0x00000001 /* In-band PD Disable Supported */
#घोषणा PCI_EXP_SLTCTL2		56	/* Slot Control 2 */
#घोषणा PCI_EXP_SLTSTA2		58	/* Slot Status 2 */

/* Extended Capabilities (PCI-X 2.0 and Express) */
#घोषणा PCI_EXT_CAP_ID(header)		(header & 0x0000ffff)
#घोषणा PCI_EXT_CAP_VER(header)		((header >> 16) & 0xf)
#घोषणा PCI_EXT_CAP_NEXT(header)	((header >> 20) & 0xffc)

#घोषणा PCI_EXT_CAP_ID_ERR	0x01	/* Advanced Error Reporting */
#घोषणा PCI_EXT_CAP_ID_VC	0x02	/* Virtual Channel Capability */
#घोषणा PCI_EXT_CAP_ID_DSN	0x03	/* Device Serial Number */
#घोषणा PCI_EXT_CAP_ID_PWR	0x04	/* Power Budgeting */
#घोषणा PCI_EXT_CAP_ID_RCLD	0x05	/* Root Complex Link Declaration */
#घोषणा PCI_EXT_CAP_ID_RCILC	0x06	/* Root Complex Internal Link Control */
#घोषणा PCI_EXT_CAP_ID_RCEC	0x07	/* Root Complex Event Collector */
#घोषणा PCI_EXT_CAP_ID_MFVC	0x08	/* Multi-Function VC Capability */
#घोषणा PCI_EXT_CAP_ID_VC9	0x09	/* same as _VC */
#घोषणा PCI_EXT_CAP_ID_RCRB	0x0A	/* Root Complex RB? */
#घोषणा PCI_EXT_CAP_ID_VNDR	0x0B	/* Venकरोr-Specअगरic */
#घोषणा PCI_EXT_CAP_ID_CAC	0x0C	/* Config Access - obsolete */
#घोषणा PCI_EXT_CAP_ID_ACS	0x0D	/* Access Control Services */
#घोषणा PCI_EXT_CAP_ID_ARI	0x0E	/* Alternate Routing ID */
#घोषणा PCI_EXT_CAP_ID_ATS	0x0F	/* Address Translation Services */
#घोषणा PCI_EXT_CAP_ID_SRIOV	0x10	/* Single Root I/O Virtualization */
#घोषणा PCI_EXT_CAP_ID_MRIOV	0x11	/* Multi Root I/O Virtualization */
#घोषणा PCI_EXT_CAP_ID_MCAST	0x12	/* Multicast */
#घोषणा PCI_EXT_CAP_ID_PRI	0x13	/* Page Request Interface */
#घोषणा PCI_EXT_CAP_ID_AMD_XXX	0x14	/* Reserved क्रम AMD */
#घोषणा PCI_EXT_CAP_ID_REBAR	0x15	/* Resizable BAR */
#घोषणा PCI_EXT_CAP_ID_DPA	0x16	/* Dynamic Power Allocation */
#घोषणा PCI_EXT_CAP_ID_TPH	0x17	/* TPH Requester */
#घोषणा PCI_EXT_CAP_ID_LTR	0x18	/* Latency Tolerance Reporting */
#घोषणा PCI_EXT_CAP_ID_SECPCI	0x19	/* Secondary PCIe Capability */
#घोषणा PCI_EXT_CAP_ID_PMUX	0x1A	/* Protocol Multiplexing */
#घोषणा PCI_EXT_CAP_ID_PASID	0x1B	/* Process Address Space ID */
#घोषणा PCI_EXT_CAP_ID_DPC	0x1D	/* Downstream Port Containment */
#घोषणा PCI_EXT_CAP_ID_L1SS	0x1E	/* L1 PM Substates */
#घोषणा PCI_EXT_CAP_ID_PTM	0x1F	/* Precision Time Measurement */
#घोषणा PCI_EXT_CAP_ID_DVSEC	0x23	/* Designated Venकरोr-Specअगरic */
#घोषणा PCI_EXT_CAP_ID_DLF	0x25	/* Data Link Feature */
#घोषणा PCI_EXT_CAP_ID_PL_16GT	0x26	/* Physical Layer 16.0 GT/s */
#घोषणा PCI_EXT_CAP_ID_MAX	PCI_EXT_CAP_ID_PL_16GT

#घोषणा PCI_EXT_CAP_DSN_SIZखातापूर्ण	12
#घोषणा PCI_EXT_CAP_MCAST_ENDPOINT_SIZखातापूर्ण 40

/* Advanced Error Reporting */
#घोषणा PCI_ERR_UNCOR_STATUS	4	/* Uncorrectable Error Status */
#घोषणा  PCI_ERR_UNC_UND	0x00000001	/* Undefined */
#घोषणा  PCI_ERR_UNC_DLP	0x00000010	/* Data Link Protocol */
#घोषणा  PCI_ERR_UNC_SURPDN	0x00000020	/* Surprise Down */
#घोषणा  PCI_ERR_UNC_POISON_TLP	0x00001000	/* Poisoned TLP */
#घोषणा  PCI_ERR_UNC_FCP	0x00002000	/* Flow Control Protocol */
#घोषणा  PCI_ERR_UNC_COMP_TIME	0x00004000	/* Completion Timeout */
#घोषणा  PCI_ERR_UNC_COMP_ABORT	0x00008000	/* Completer Abort */
#घोषणा  PCI_ERR_UNC_UNX_COMP	0x00010000	/* Unexpected Completion */
#घोषणा  PCI_ERR_UNC_RX_OVER	0x00020000	/* Receiver Overflow */
#घोषणा  PCI_ERR_UNC_MALF_TLP	0x00040000	/* Malक्रमmed TLP */
#घोषणा  PCI_ERR_UNC_ECRC	0x00080000	/* ECRC Error Status */
#घोषणा  PCI_ERR_UNC_UNSUP	0x00100000	/* Unsupported Request */
#घोषणा  PCI_ERR_UNC_ACSV	0x00200000	/* ACS Violation */
#घोषणा  PCI_ERR_UNC_INTN	0x00400000	/* पूर्णांकernal error */
#घोषणा  PCI_ERR_UNC_MCBTLP	0x00800000	/* MC blocked TLP */
#घोषणा  PCI_ERR_UNC_ATOMEG	0x01000000	/* Atomic egress blocked */
#घोषणा  PCI_ERR_UNC_TLPPRE	0x02000000	/* TLP prefix blocked */
#घोषणा PCI_ERR_UNCOR_MASK	8	/* Uncorrectable Error Mask */
	/* Same bits as above */
#घोषणा PCI_ERR_UNCOR_SEVER	12	/* Uncorrectable Error Severity */
	/* Same bits as above */
#घोषणा PCI_ERR_COR_STATUS	16	/* Correctable Error Status */
#घोषणा  PCI_ERR_COR_RCVR	0x00000001	/* Receiver Error Status */
#घोषणा  PCI_ERR_COR_BAD_TLP	0x00000040	/* Bad TLP Status */
#घोषणा  PCI_ERR_COR_BAD_DLLP	0x00000080	/* Bad DLLP Status */
#घोषणा  PCI_ERR_COR_REP_ROLL	0x00000100	/* REPLAY_NUM Rollover */
#घोषणा  PCI_ERR_COR_REP_TIMER	0x00001000	/* Replay Timer Timeout */
#घोषणा  PCI_ERR_COR_ADV_NFAT	0x00002000	/* Advisory Non-Fatal */
#घोषणा  PCI_ERR_COR_INTERNAL	0x00004000	/* Corrected Internal */
#घोषणा  PCI_ERR_COR_LOG_OVER	0x00008000	/* Header Log Overflow */
#घोषणा PCI_ERR_COR_MASK	20	/* Correctable Error Mask */
	/* Same bits as above */
#घोषणा PCI_ERR_CAP		24	/* Advanced Error Capabilities */
#घोषणा  PCI_ERR_CAP_FEP(x)	((x) & 31)	/* First Error Poपूर्णांकer */
#घोषणा  PCI_ERR_CAP_ECRC_GENC	0x00000020	/* ECRC Generation Capable */
#घोषणा  PCI_ERR_CAP_ECRC_GENE	0x00000040	/* ECRC Generation Enable */
#घोषणा  PCI_ERR_CAP_ECRC_CHKC	0x00000080	/* ECRC Check Capable */
#घोषणा  PCI_ERR_CAP_ECRC_CHKE	0x00000100	/* ECRC Check Enable */
#घोषणा PCI_ERR_HEADER_LOG	28	/* Header Log Register (16 bytes) */
#घोषणा PCI_ERR_ROOT_COMMAND	44	/* Root Error Command */
#घोषणा  PCI_ERR_ROOT_CMD_COR_EN	0x00000001 /* Correctable Err Reporting Enable */
#घोषणा  PCI_ERR_ROOT_CMD_NONFATAL_EN	0x00000002 /* Non-Fatal Err Reporting Enable */
#घोषणा  PCI_ERR_ROOT_CMD_FATAL_EN	0x00000004 /* Fatal Err Reporting Enable */
#घोषणा PCI_ERR_ROOT_STATUS	48
#घोषणा  PCI_ERR_ROOT_COR_RCV		0x00000001 /* ERR_COR Received */
#घोषणा  PCI_ERR_ROOT_MULTI_COR_RCV	0x00000002 /* Multiple ERR_COR */
#घोषणा  PCI_ERR_ROOT_UNCOR_RCV		0x00000004 /* ERR_FATAL/NONFATAL */
#घोषणा  PCI_ERR_ROOT_MULTI_UNCOR_RCV	0x00000008 /* Multiple FATAL/NONFATAL */
#घोषणा  PCI_ERR_ROOT_FIRST_FATAL	0x00000010 /* First UNC is Fatal */
#घोषणा  PCI_ERR_ROOT_NONFATAL_RCV	0x00000020 /* Non-Fatal Received */
#घोषणा  PCI_ERR_ROOT_FATAL_RCV		0x00000040 /* Fatal Received */
#घोषणा  PCI_ERR_ROOT_AER_IRQ		0xf8000000 /* Advanced Error Interrupt Message Number */
#घोषणा PCI_ERR_ROOT_ERR_SRC	52	/* Error Source Identअगरication */

/* Virtual Channel */
#घोषणा PCI_VC_PORT_CAP1	4
#घोषणा  PCI_VC_CAP1_EVCC	0x00000007	/* extended VC count */
#घोषणा  PCI_VC_CAP1_LPEVCC	0x00000070	/* low prio extended VC count */
#घोषणा  PCI_VC_CAP1_ARB_SIZE	0x00000c00
#घोषणा PCI_VC_PORT_CAP2	8
#घोषणा  PCI_VC_CAP2_32_PHASE		0x00000002
#घोषणा  PCI_VC_CAP2_64_PHASE		0x00000004
#घोषणा  PCI_VC_CAP2_128_PHASE		0x00000008
#घोषणा  PCI_VC_CAP2_ARB_OFF		0xff000000
#घोषणा PCI_VC_PORT_CTRL	12
#घोषणा  PCI_VC_PORT_CTRL_LOAD_TABLE	0x00000001
#घोषणा PCI_VC_PORT_STATUS	14
#घोषणा  PCI_VC_PORT_STATUS_TABLE	0x00000001
#घोषणा PCI_VC_RES_CAP		16
#घोषणा  PCI_VC_RES_CAP_32_PHASE	0x00000002
#घोषणा  PCI_VC_RES_CAP_64_PHASE	0x00000004
#घोषणा  PCI_VC_RES_CAP_128_PHASE	0x00000008
#घोषणा  PCI_VC_RES_CAP_128_PHASE_TB	0x00000010
#घोषणा  PCI_VC_RES_CAP_256_PHASE	0x00000020
#घोषणा  PCI_VC_RES_CAP_ARB_OFF		0xff000000
#घोषणा PCI_VC_RES_CTRL		20
#घोषणा  PCI_VC_RES_CTRL_LOAD_TABLE	0x00010000
#घोषणा  PCI_VC_RES_CTRL_ARB_SELECT	0x000e0000
#घोषणा  PCI_VC_RES_CTRL_ID		0x07000000
#घोषणा  PCI_VC_RES_CTRL_ENABLE		0x80000000
#घोषणा PCI_VC_RES_STATUS	26
#घोषणा  PCI_VC_RES_STATUS_TABLE	0x00000001
#घोषणा  PCI_VC_RES_STATUS_NEGO		0x00000002
#घोषणा PCI_CAP_VC_BASE_SIZखातापूर्ण		0x10
#घोषणा PCI_CAP_VC_PER_VC_SIZखातापूर्ण	0x0C

/* Power Budgeting */
#घोषणा PCI_PWR_DSR		4	/* Data Select Register */
#घोषणा PCI_PWR_DATA		8	/* Data Register */
#घोषणा  PCI_PWR_DATA_BASE(x)	((x) & 0xff)	    /* Base Power */
#घोषणा  PCI_PWR_DATA_SCALE(x)	(((x) >> 8) & 3)    /* Data Scale */
#घोषणा  PCI_PWR_DATA_PM_SUB(x)	(((x) >> 10) & 7)   /* PM Sub State */
#घोषणा  PCI_PWR_DATA_PM_STATE(x) (((x) >> 13) & 3) /* PM State */
#घोषणा  PCI_PWR_DATA_TYPE(x)	(((x) >> 15) & 7)   /* Type */
#घोषणा  PCI_PWR_DATA_RAIL(x)	(((x) >> 18) & 7)   /* Power Rail */
#घोषणा PCI_PWR_CAP		12	/* Capability */
#घोषणा  PCI_PWR_CAP_BUDGET(x)	((x) & 1)	/* Included in प्रणाली budget */
#घोषणा PCI_EXT_CAP_PWR_SIZखातापूर्ण	16

/* Root Complex Event Collector Endpoपूर्णांक Association  */
#घोषणा PCI_RCEC_RCIEP_BITMAP	4	/* Associated Biपंचांगap क्रम RCiEPs */
#घोषणा PCI_RCEC_BUSN		8	/* RCEC Associated Bus Numbers */
#घोषणा  PCI_RCEC_BUSN_REG_VER	0x02	/* Least version with BUSN present */
#घोषणा  PCI_RCEC_BUSN_NEXT(x)	(((x) >> 8) & 0xff)
#घोषणा  PCI_RCEC_BUSN_LAST(x)	(((x) >> 16) & 0xff)

/* Venकरोr-Specअगरic (VSEC, PCI_EXT_CAP_ID_VNDR) */
#घोषणा PCI_VNDR_HEADER		4	/* Venकरोr-Specअगरic Header */
#घोषणा  PCI_VNDR_HEADER_ID(x)	((x) & 0xffff)
#घोषणा  PCI_VNDR_HEADER_REV(x)	(((x) >> 16) & 0xf)
#घोषणा  PCI_VNDR_HEADER_LEN(x)	(((x) >> 20) & 0xfff)

/*
 * HyperTransport sub capability types
 *
 * Unक्रमtunately there are both 3 bit and 5 bit capability types defined
 * in the HT spec, catering क्रम that is a little messy. You probably करोn't
 * want to use these directly, just use pci_find_ht_capability() and it
 * will करो the right thing क्रम you.
 */
#घोषणा HT_3BIT_CAP_MASK	0xE0
#घोषणा HT_CAPTYPE_SLAVE	0x00	/* Slave/Primary link configuration */
#घोषणा HT_CAPTYPE_HOST		0x20	/* Host/Secondary link configuration */

#घोषणा HT_5BIT_CAP_MASK	0xF8
#घोषणा HT_CAPTYPE_IRQ		0x80	/* IRQ Configuration */
#घोषणा HT_CAPTYPE_REMAPPING_40	0xA0	/* 40 bit address remapping */
#घोषणा HT_CAPTYPE_REMAPPING_64 0xA2	/* 64 bit address remapping */
#घोषणा HT_CAPTYPE_UNITID_CLUMP	0x90	/* Unit ID clumping */
#घोषणा HT_CAPTYPE_EXTCONF	0x98	/* Extended Configuration Space Access */
#घोषणा HT_CAPTYPE_MSI_MAPPING	0xA8	/* MSI Mapping Capability */
#घोषणा  HT_MSI_FLAGS		0x02		/* Offset to flags */
#घोषणा  HT_MSI_FLAGS_ENABLE	0x1		/* Mapping enable */
#घोषणा  HT_MSI_FLAGS_FIXED	0x2		/* Fixed mapping only */
#घोषणा  HT_MSI_FIXED_ADDR	0x00000000FEE00000ULL	/* Fixed addr */
#घोषणा  HT_MSI_ADDR_LO		0x04		/* Offset to low addr bits */
#घोषणा  HT_MSI_ADDR_LO_MASK	0xFFF00000	/* Low address bit mask */
#घोषणा  HT_MSI_ADDR_HI		0x08		/* Offset to high addr bits */
#घोषणा HT_CAPTYPE_सूचीECT_ROUTE	0xB0	/* Direct routing configuration */
#घोषणा HT_CAPTYPE_VCSET	0xB8	/* Virtual Channel configuration */
#घोषणा HT_CAPTYPE_ERROR_RETRY	0xC0	/* Retry on error configuration */
#घोषणा HT_CAPTYPE_GEN3		0xD0	/* Generation 3 HyperTransport configuration */
#घोषणा HT_CAPTYPE_PM		0xE0	/* HyperTransport घातer management configuration */
#घोषणा HT_CAP_SIZखातापूर्ण_LONG	28	/* slave & primary */
#घोषणा HT_CAP_SIZखातापूर्ण_SHORT	24	/* host & secondary */

/* Alternative Routing-ID Interpretation */
#घोषणा PCI_ARI_CAP		0x04	/* ARI Capability Register */
#घोषणा  PCI_ARI_CAP_MFVC	0x0001	/* MFVC Function Groups Capability */
#घोषणा  PCI_ARI_CAP_ACS	0x0002	/* ACS Function Groups Capability */
#घोषणा  PCI_ARI_CAP_NFN(x)	(((x) >> 8) & 0xff) /* Next Function Number */
#घोषणा PCI_ARI_CTRL		0x06	/* ARI Control Register */
#घोषणा  PCI_ARI_CTRL_MFVC	0x0001	/* MFVC Function Groups Enable */
#घोषणा  PCI_ARI_CTRL_ACS	0x0002	/* ACS Function Groups Enable */
#घोषणा  PCI_ARI_CTRL_FG(x)	(((x) >> 4) & 7) /* Function Group */
#घोषणा PCI_EXT_CAP_ARI_SIZखातापूर्ण	8

/* Address Translation Service */
#घोषणा PCI_ATS_CAP		0x04	/* ATS Capability Register */
#घोषणा  PCI_ATS_CAP_QDEP(x)	((x) & 0x1f)	/* Invalidate Queue Depth */
#घोषणा  PCI_ATS_MAX_QDEP	32	/* Max Invalidate Queue Depth */
#घोषणा  PCI_ATS_CAP_PAGE_ALIGNED	0x0020 /* Page Aligned Request */
#घोषणा PCI_ATS_CTRL		0x06	/* ATS Control Register */
#घोषणा  PCI_ATS_CTRL_ENABLE	0x8000	/* ATS Enable */
#घोषणा  PCI_ATS_CTRL_STU(x)	((x) & 0x1f)	/* Smallest Translation Unit */
#घोषणा  PCI_ATS_MIN_STU	12	/* shअगरt of minimum STU block */
#घोषणा PCI_EXT_CAP_ATS_SIZखातापूर्ण	8

/* Page Request Interface */
#घोषणा PCI_PRI_CTRL		0x04	/* PRI control रेजिस्टर */
#घोषणा  PCI_PRI_CTRL_ENABLE	0x0001	/* Enable */
#घोषणा  PCI_PRI_CTRL_RESET	0x0002	/* Reset */
#घोषणा PCI_PRI_STATUS		0x06	/* PRI status रेजिस्टर */
#घोषणा  PCI_PRI_STATUS_RF	0x0001	/* Response Failure */
#घोषणा  PCI_PRI_STATUS_UPRGI	0x0002	/* Unexpected PRG index */
#घोषणा  PCI_PRI_STATUS_STOPPED	0x0100	/* PRI Stopped */
#घोषणा  PCI_PRI_STATUS_PASID	0x8000	/* PRG Response PASID Required */
#घोषणा PCI_PRI_MAX_REQ		0x08	/* PRI max reqs supported */
#घोषणा PCI_PRI_ALLOC_REQ	0x0c	/* PRI max reqs allowed */
#घोषणा PCI_EXT_CAP_PRI_SIZखातापूर्ण	16

/* Process Address Space ID */
#घोषणा PCI_PASID_CAP		0x04    /* PASID feature रेजिस्टर */
#घोषणा  PCI_PASID_CAP_EXEC	0x02	/* Exec permissions Supported */
#घोषणा  PCI_PASID_CAP_PRIV	0x04	/* Privilege Mode Supported */
#घोषणा PCI_PASID_CTRL		0x06    /* PASID control रेजिस्टर */
#घोषणा  PCI_PASID_CTRL_ENABLE	0x01	/* Enable bit */
#घोषणा  PCI_PASID_CTRL_EXEC	0x02	/* Exec permissions Enable */
#घोषणा  PCI_PASID_CTRL_PRIV	0x04	/* Privilege Mode Enable */
#घोषणा PCI_EXT_CAP_PASID_SIZखातापूर्ण	8

/* Single Root I/O Virtualization */
#घोषणा PCI_SRIOV_CAP		0x04	/* SR-IOV Capabilities */
#घोषणा  PCI_SRIOV_CAP_VFM	0x00000001  /* VF Migration Capable */
#घोषणा  PCI_SRIOV_CAP_INTR(x)	((x) >> 21) /* Interrupt Message Number */
#घोषणा PCI_SRIOV_CTRL		0x08	/* SR-IOV Control */
#घोषणा  PCI_SRIOV_CTRL_VFE	0x0001	/* VF Enable */
#घोषणा  PCI_SRIOV_CTRL_VFM	0x0002	/* VF Migration Enable */
#घोषणा  PCI_SRIOV_CTRL_INTR	0x0004	/* VF Migration Interrupt Enable */
#घोषणा  PCI_SRIOV_CTRL_MSE	0x0008	/* VF Memory Space Enable */
#घोषणा  PCI_SRIOV_CTRL_ARI	0x0010	/* ARI Capable Hierarchy */
#घोषणा PCI_SRIOV_STATUS	0x0a	/* SR-IOV Status */
#घोषणा  PCI_SRIOV_STATUS_VFM	0x0001	/* VF Migration Status */
#घोषणा PCI_SRIOV_INITIAL_VF	0x0c	/* Initial VFs */
#घोषणा PCI_SRIOV_TOTAL_VF	0x0e	/* Total VFs */
#घोषणा PCI_SRIOV_NUM_VF	0x10	/* Number of VFs */
#घोषणा PCI_SRIOV_FUNC_LINK	0x12	/* Function Dependency Link */
#घोषणा PCI_SRIOV_VF_OFFSET	0x14	/* First VF Offset */
#घोषणा PCI_SRIOV_VF_STRIDE	0x16	/* Following VF Stride */
#घोषणा PCI_SRIOV_VF_DID	0x1a	/* VF Device ID */
#घोषणा PCI_SRIOV_SUP_PGSIZE	0x1c	/* Supported Page Sizes */
#घोषणा PCI_SRIOV_SYS_PGSIZE	0x20	/* System Page Size */
#घोषणा PCI_SRIOV_BAR		0x24	/* VF BAR0 */
#घोषणा  PCI_SRIOV_NUM_BARS	6	/* Number of VF BARs */
#घोषणा PCI_SRIOV_VFM		0x3c	/* VF Migration State Array Offset*/
#घोषणा  PCI_SRIOV_VFM_BIR(x)	((x) & 7)	/* State BIR */
#घोषणा  PCI_SRIOV_VFM_OFFSET(x) ((x) & ~7)	/* State Offset */
#घोषणा  PCI_SRIOV_VFM_UA	0x0	/* Inactive.Unavailable */
#घोषणा  PCI_SRIOV_VFM_MI	0x1	/* Dormant.MigrateIn */
#घोषणा  PCI_SRIOV_VFM_MO	0x2	/* Active.MigrateOut */
#घोषणा  PCI_SRIOV_VFM_AV	0x3	/* Active.Available */
#घोषणा PCI_EXT_CAP_SRIOV_SIZखातापूर्ण 64

#घोषणा PCI_LTR_MAX_SNOOP_LAT	0x4
#घोषणा PCI_LTR_MAX_NOSNOOP_LAT	0x6
#घोषणा  PCI_LTR_VALUE_MASK	0x000003ff
#घोषणा  PCI_LTR_SCALE_MASK	0x00001c00
#घोषणा  PCI_LTR_SCALE_SHIFT	10
#घोषणा PCI_EXT_CAP_LTR_SIZखातापूर्ण	8

/* Access Control Service */
#घोषणा PCI_ACS_CAP		0x04	/* ACS Capability Register */
#घोषणा  PCI_ACS_SV		0x0001	/* Source Validation */
#घोषणा  PCI_ACS_TB		0x0002	/* Translation Blocking */
#घोषणा  PCI_ACS_RR		0x0004	/* P2P Request Redirect */
#घोषणा  PCI_ACS_CR		0x0008	/* P2P Completion Redirect */
#घोषणा  PCI_ACS_UF		0x0010	/* Upstream Forwarding */
#घोषणा  PCI_ACS_EC		0x0020	/* P2P Egress Control */
#घोषणा  PCI_ACS_DT		0x0040	/* Direct Translated P2P */
#घोषणा PCI_ACS_EGRESS_BITS	0x05	/* ACS Egress Control Vector Size */
#घोषणा PCI_ACS_CTRL		0x06	/* ACS Control Register */
#घोषणा PCI_ACS_EGRESS_CTL_V	0x08	/* ACS Egress Control Vector */

#घोषणा PCI_VSEC_HDR		4	/* extended cap - venकरोr-specअगरic */
#घोषणा  PCI_VSEC_HDR_LEN_SHIFT	20	/* shअगरt क्रम length field */

/* SATA capability */
#घोषणा PCI_SATA_REGS		4	/* SATA REGs specअगरier */
#घोषणा  PCI_SATA_REGS_MASK	0xF	/* location - BAR#/अंतरभूत */
#घोषणा  PCI_SATA_REGS_INLINE	0xF	/* REGS in config space */
#घोषणा PCI_SATA_SIZखातापूर्ण_SHORT	8
#घोषणा PCI_SATA_SIZखातापूर्ण_LONG	16

/* Resizable BARs */
#घोषणा PCI_REBAR_CAP		4	/* capability रेजिस्टर */
#घोषणा  PCI_REBAR_CAP_SIZES		0x00FFFFF0  /* supported BAR sizes */
#घोषणा PCI_REBAR_CTRL		8	/* control रेजिस्टर */
#घोषणा  PCI_REBAR_CTRL_BAR_IDX		0x00000007  /* BAR index */
#घोषणा  PCI_REBAR_CTRL_NBAR_MASK	0x000000E0  /* # of resizable BARs */
#घोषणा  PCI_REBAR_CTRL_NBAR_SHIFT	5	    /* shअगरt क्रम # of BARs */
#घोषणा  PCI_REBAR_CTRL_BAR_SIZE	0x00001F00  /* BAR size */
#घोषणा  PCI_REBAR_CTRL_BAR_SHIFT	8	    /* shअगरt क्रम BAR size */

/* Dynamic Power Allocation */
#घोषणा PCI_DPA_CAP		4	/* capability रेजिस्टर */
#घोषणा  PCI_DPA_CAP_SUBSTATE_MASK	0x1F	/* # substates - 1 */
#घोषणा PCI_DPA_BASE_SIZखातापूर्ण	16	/* size with 0 substates */

/* TPH Requester */
#घोषणा PCI_TPH_CAP		4	/* capability रेजिस्टर */
#घोषणा  PCI_TPH_CAP_LOC_MASK	0x600	/* location mask */
#घोषणा   PCI_TPH_LOC_NONE	0x000	/* no location */
#घोषणा   PCI_TPH_LOC_CAP	0x200	/* in capability */
#घोषणा   PCI_TPH_LOC_MSIX	0x400	/* in MSI-X */
#घोषणा PCI_TPH_CAP_ST_MASK	0x07FF0000	/* st table mask */
#घोषणा PCI_TPH_CAP_ST_SHIFT	16	/* st table shअगरt */
#घोषणा PCI_TPH_BASE_SIZखातापूर्ण	12	/* size with no st table */

/* Downstream Port Containment */
#घोषणा PCI_EXP_DPC_CAP			4	/* DPC Capability */
#घोषणा PCI_EXP_DPC_IRQ			0x001F	/* Interrupt Message Number */
#घोषणा  PCI_EXP_DPC_CAP_RP_EXT		0x0020	/* Root Port Extensions */
#घोषणा  PCI_EXP_DPC_CAP_POISONED_TLP	0x0040	/* Poisoned TLP Egress Blocking Supported */
#घोषणा  PCI_EXP_DPC_CAP_SW_TRIGGER	0x0080	/* Software Triggering Supported */
#घोषणा  PCI_EXP_DPC_RP_PIO_LOG_SIZE	0x0F00	/* RP PIO Log Size */
#घोषणा  PCI_EXP_DPC_CAP_DL_ACTIVE	0x1000	/* ERR_COR संकेत on DL_Active supported */

#घोषणा PCI_EXP_DPC_CTL			6	/* DPC control */
#घोषणा  PCI_EXP_DPC_CTL_EN_FATAL	0x0001	/* Enable trigger on ERR_FATAL message */
#घोषणा  PCI_EXP_DPC_CTL_EN_NONFATAL	0x0002	/* Enable trigger on ERR_NONFATAL message */
#घोषणा  PCI_EXP_DPC_CTL_INT_EN		0x0008	/* DPC Interrupt Enable */

#घोषणा PCI_EXP_DPC_STATUS		8	/* DPC Status */
#घोषणा  PCI_EXP_DPC_STATUS_TRIGGER	    0x0001 /* Trigger Status */
#घोषणा  PCI_EXP_DPC_STATUS_TRIGGER_RSN	    0x0006 /* Trigger Reason */
#घोषणा  PCI_EXP_DPC_STATUS_INTERRUPT	    0x0008 /* Interrupt Status */
#घोषणा  PCI_EXP_DPC_RP_BUSY		    0x0010 /* Root Port Busy */
#घोषणा  PCI_EXP_DPC_STATUS_TRIGGER_RSN_EXT 0x0060 /* Trig Reason Extension */

#घोषणा PCI_EXP_DPC_SOURCE_ID		10	/* DPC Source Identअगरier */

#घोषणा PCI_EXP_DPC_RP_PIO_STATUS	 0x0C	/* RP PIO Status */
#घोषणा PCI_EXP_DPC_RP_PIO_MASK		 0x10	/* RP PIO Mask */
#घोषणा PCI_EXP_DPC_RP_PIO_SEVERITY	 0x14	/* RP PIO Severity */
#घोषणा PCI_EXP_DPC_RP_PIO_SYSERROR	 0x18	/* RP PIO SysError */
#घोषणा PCI_EXP_DPC_RP_PIO_EXCEPTION	 0x1C	/* RP PIO Exception */
#घोषणा PCI_EXP_DPC_RP_PIO_HEADER_LOG	 0x20	/* RP PIO Header Log */
#घोषणा PCI_EXP_DPC_RP_PIO_IMPSPEC_LOG	 0x30	/* RP PIO ImpSpec Log */
#घोषणा PCI_EXP_DPC_RP_PIO_TLPPREFIX_LOG 0x34	/* RP PIO TLP Prefix Log */

/* Precision Time Measurement */
#घोषणा PCI_PTM_CAP			0x04	    /* PTM Capability */
#घोषणा  PCI_PTM_CAP_REQ		0x00000001  /* Requester capable */
#घोषणा  PCI_PTM_CAP_ROOT		0x00000004  /* Root capable */
#घोषणा  PCI_PTM_GRANULARITY_MASK	0x0000FF00  /* Clock granularity */
#घोषणा PCI_PTM_CTRL			0x08	    /* PTM Control */
#घोषणा  PCI_PTM_CTRL_ENABLE		0x00000001  /* PTM enable */
#घोषणा  PCI_PTM_CTRL_ROOT		0x00000002  /* Root select */

/* ASPM L1 PM Substates */
#घोषणा PCI_L1SS_CAP		0x04	/* Capabilities Register */
#घोषणा  PCI_L1SS_CAP_PCIPM_L1_2	0x00000001  /* PCI-PM L1.2 Supported */
#घोषणा  PCI_L1SS_CAP_PCIPM_L1_1	0x00000002  /* PCI-PM L1.1 Supported */
#घोषणा  PCI_L1SS_CAP_ASPM_L1_2		0x00000004  /* ASPM L1.2 Supported */
#घोषणा  PCI_L1SS_CAP_ASPM_L1_1		0x00000008  /* ASPM L1.1 Supported */
#घोषणा  PCI_L1SS_CAP_L1_PM_SS		0x00000010  /* L1 PM Substates Supported */
#घोषणा  PCI_L1SS_CAP_CM_RESTORE_TIME	0x0000ff00  /* Port Common_Mode_Restore_Time */
#घोषणा  PCI_L1SS_CAP_P_PWR_ON_SCALE	0x00030000  /* Port T_POWER_ON scale */
#घोषणा  PCI_L1SS_CAP_P_PWR_ON_VALUE	0x00f80000  /* Port T_POWER_ON value */
#घोषणा PCI_L1SS_CTL1		0x08	/* Control 1 Register */
#घोषणा  PCI_L1SS_CTL1_PCIPM_L1_2	0x00000001  /* PCI-PM L1.2 Enable */
#घोषणा  PCI_L1SS_CTL1_PCIPM_L1_1	0x00000002  /* PCI-PM L1.1 Enable */
#घोषणा  PCI_L1SS_CTL1_ASPM_L1_2	0x00000004  /* ASPM L1.2 Enable */
#घोषणा  PCI_L1SS_CTL1_ASPM_L1_1	0x00000008  /* ASPM L1.1 Enable */
#घोषणा  PCI_L1SS_CTL1_L1_2_MASK	0x00000005
#घोषणा  PCI_L1SS_CTL1_L1SS_MASK	0x0000000f
#घोषणा  PCI_L1SS_CTL1_CM_RESTORE_TIME	0x0000ff00  /* Common_Mode_Restore_Time */
#घोषणा  PCI_L1SS_CTL1_LTR_L12_TH_VALUE	0x03ff0000  /* LTR_L1.2_THRESHOLD_Value */
#घोषणा  PCI_L1SS_CTL1_LTR_L12_TH_SCALE	0xe0000000  /* LTR_L1.2_THRESHOLD_Scale */
#घोषणा PCI_L1SS_CTL2		0x0c	/* Control 2 Register */

/* Designated Venकरोr-Specअगरic (DVSEC, PCI_EXT_CAP_ID_DVSEC) */
#घोषणा PCI_DVSEC_HEADER1		0x4 /* Designated Venकरोr-Specअगरic Header1 */
#घोषणा PCI_DVSEC_HEADER2		0x8 /* Designated Venकरोr-Specअगरic Header2 */

/* Data Link Feature */
#घोषणा PCI_DLF_CAP		0x04	/* Capabilities Register */
#घोषणा  PCI_DLF_EXCHANGE_ENABLE	0x80000000  /* Data Link Feature Exchange Enable */

/* Physical Layer 16.0 GT/s */
#घोषणा PCI_PL_16GT_LE_CTRL	0x20	/* Lane Equalization Control Register */
#घोषणा  PCI_PL_16GT_LE_CTRL_DSP_TX_PRESET_MASK		0x0000000F
#घोषणा  PCI_PL_16GT_LE_CTRL_USP_TX_PRESET_MASK		0x000000F0
#घोषणा  PCI_PL_16GT_LE_CTRL_USP_TX_PRESET_SHIFT	4

#पूर्ण_अगर /* LINUX_PCI_REGS_H */
