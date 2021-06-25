<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * sata_mv.c - Marvell SATA support
 *
 * Copyright 2008-2009: Marvell Corporation, all rights reserved.
 * Copyright 2005: EMC Corporation, all rights reserved.
 * Copyright 2005 Red Hat, Inc.  All rights reserved.
 *
 * Originally written by Brett Russ.
 * Extensive overhaul and enhancement by Mark Lord <mlord@pobox.com>.
 *
 * Please ALWAYS copy linux-ide@vger.kernel.org on emails.
 */

/*
 * sata_mv TODO list:
 *
 * --> Develop a low-घातer-consumption strategy, and implement it.
 *
 * --> Add sysfs attributes क्रम per-chip / per-HC IRQ coalescing thresholds.
 *
 * --> [Experiment, Marvell value added] Is it possible to use target
 *       mode to cross-connect two Linux boxes with Marvell cards?  If so,
 *       creating LibATA target mode support would be very पूर्णांकeresting.
 *
 *       Target mode, क्रम those without करोcs, is the ability to directly
 *       connect two SATA ports.
 */

/*
 * 80x1-B2 errata PCI#11:
 *
 * Users of the 6041/6081 Rev.B2 chips (current is C0)
 * should be careful to insert those cards only onto PCI-X bus #0,
 * and only in device slots 0..7, not higher.  The chips may not
 * work correctly otherwise  (note: this is a pretty rare condition).
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/device.h>
#समावेश <linux/clk.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/ata_platक्रमm.h>
#समावेश <linux/mbus.h>
#समावेश <linux/bitops.h>
#समावेश <linux/gfp.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <linux/libata.h>

#घोषणा DRV_NAME	"sata_mv"
#घोषणा DRV_VERSION	"1.28"

/*
 * module options
 */

#अगर_घोषित CONFIG_PCI
अटल पूर्णांक msi;
module_param(msi, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(msi, "Enable use of PCI MSI (0=off, 1=on)");
#पूर्ण_अगर

अटल पूर्णांक irq_coalescing_io_count;
module_param(irq_coalescing_io_count, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(irq_coalescing_io_count,
		 "IRQ coalescing I/O count threshold (0..255)");

अटल पूर्णांक irq_coalescing_usecs;
module_param(irq_coalescing_usecs, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(irq_coalescing_usecs,
		 "IRQ coalescing time threshold in usecs");

क्रमागत अणु
	/* BAR's are क्रमागतerated in terms of pci_resource_start() terms */
	MV_PRIMARY_BAR		= 0,	/* offset 0x10: memory space */
	MV_IO_BAR		= 2,	/* offset 0x18: IO space */
	MV_MISC_BAR		= 3,	/* offset 0x1c: FLASH, NVRAM, SRAM */

	MV_MAJOR_REG_AREA_SZ	= 0x10000,	/* 64KB */
	MV_MINOR_REG_AREA_SZ	= 0x2000,	/* 8KB */

	/* For use with both IRQ coalescing methods ("all ports" or "per-HC" */
	COAL_CLOCKS_PER_USEC	= 150,		/* क्रम calculating COAL_TIMEs */
	MAX_COAL_TIME_THRESHOLD	= ((1 << 24) - 1), /* पूर्णांकernal घड़ीs count */
	MAX_COAL_IO_COUNT	= 255,		/* completed I/O count */

	MV_PCI_REG_BASE		= 0,

	/*
	 * Per-chip ("all ports") पूर्णांकerrupt coalescing feature.
	 * This is only क्रम GEN_II / GEN_IIE hardware.
	 *
	 * Coalescing defers the पूर्णांकerrupt until either the IO_THRESHOLD
	 * (count of completed I/Os) is met, or the TIME_THRESHOLD is met.
	 */
	COAL_REG_BASE		= 0x18000,
	IRQ_COAL_CAUSE		= (COAL_REG_BASE + 0x08),
	ALL_PORTS_COAL_IRQ	= (1 << 4),	/* all ports irq event */

	IRQ_COAL_IO_THRESHOLD   = (COAL_REG_BASE + 0xcc),
	IRQ_COAL_TIME_THRESHOLD = (COAL_REG_BASE + 0xd0),

	/*
	 * Registers क्रम the (unused here) transaction coalescing feature:
	 */
	TRAN_COAL_CAUSE_LO	= (COAL_REG_BASE + 0x88),
	TRAN_COAL_CAUSE_HI	= (COAL_REG_BASE + 0x8c),

	SATAHC0_REG_BASE	= 0x20000,
	FLASH_CTL		= 0x1046c,
	GPIO_PORT_CTL		= 0x104f0,
	RESET_CFG		= 0x180d8,

	MV_PCI_REG_SZ		= MV_MAJOR_REG_AREA_SZ,
	MV_SATAHC_REG_SZ	= MV_MAJOR_REG_AREA_SZ,
	MV_SATAHC_ARBTR_REG_SZ	= MV_MINOR_REG_AREA_SZ,		/* arbiter */
	MV_PORT_REG_SZ		= MV_MINOR_REG_AREA_SZ,

	MV_MAX_Q_DEPTH		= 32,
	MV_MAX_Q_DEPTH_MASK	= MV_MAX_Q_DEPTH - 1,

	/* CRQB needs alignment on a 1KB boundary. Size == 1KB
	 * CRPB needs alignment on a 256B boundary. Size == 256B
	 * ePRD (SG) entries need alignment on a 16B boundary. Size == 16B
	 */
	MV_CRQB_Q_SZ		= (32 * MV_MAX_Q_DEPTH),
	MV_CRPB_Q_SZ		= (8 * MV_MAX_Q_DEPTH),
	MV_MAX_SG_CT		= 256,
	MV_SG_TBL_SZ		= (16 * MV_MAX_SG_CT),

	/* Determine hc from 0-7 port: hc = port >> MV_PORT_HC_SHIFT */
	MV_PORT_HC_SHIFT	= 2,
	MV_PORTS_PER_HC		= (1 << MV_PORT_HC_SHIFT), /* 4 */
	/* Determine hc port from 0-7 port: hardport = port & MV_PORT_MASK */
	MV_PORT_MASK		= (MV_PORTS_PER_HC - 1),   /* 3 */

	/* Host Flags */
	MV_FLAG_DUAL_HC		= (1 << 30),  /* two SATA Host Controllers */

	MV_COMMON_FLAGS		= ATA_FLAG_SATA | ATA_FLAG_PIO_POLLING,

	MV_GEN_I_FLAGS		= MV_COMMON_FLAGS | ATA_FLAG_NO_ATAPI,

	MV_GEN_II_FLAGS		= MV_COMMON_FLAGS | ATA_FLAG_NCQ |
				  ATA_FLAG_PMP | ATA_FLAG_ACPI_SATA,

	MV_GEN_IIE_FLAGS	= MV_GEN_II_FLAGS | ATA_FLAG_AN,

	CRQB_FLAG_READ		= (1 << 0),
	CRQB_TAG_SHIFT		= 1,
	CRQB_IOID_SHIFT		= 6,	/* CRQB Gen-II/IIE IO Id shअगरt */
	CRQB_PMP_SHIFT		= 12,	/* CRQB Gen-II/IIE PMP shअगरt */
	CRQB_HOSTQ_SHIFT	= 17,	/* CRQB Gen-II/IIE HostQueTag shअगरt */
	CRQB_CMD_ADDR_SHIFT	= 8,
	CRQB_CMD_CS		= (0x2 << 11),
	CRQB_CMD_LAST		= (1 << 15),

	CRPB_FLAG_STATUS_SHIFT	= 8,
	CRPB_IOID_SHIFT_6	= 5,	/* CRPB Gen-II IO Id shअगरt */
	CRPB_IOID_SHIFT_7	= 7,	/* CRPB Gen-IIE IO Id shअगरt */

	EPRD_FLAG_END_OF_TBL	= (1 << 31),

	/* PCI पूर्णांकerface रेजिस्टरs */

	MV_PCI_COMMAND		= 0xc00,
	MV_PCI_COMMAND_MWRCOM	= (1 << 4),	/* PCI Master Write Combining */
	MV_PCI_COMMAND_MRDTRIG	= (1 << 7),	/* PCI Master Read Trigger */

	PCI_MAIN_CMD_STS	= 0xd30,
	STOP_PCI_MASTER		= (1 << 2),
	PCI_MASTER_EMPTY	= (1 << 3),
	GLOB_SFT_RST		= (1 << 4),

	MV_PCI_MODE		= 0xd00,
	MV_PCI_MODE_MASK	= 0x30,

	MV_PCI_EXP_ROM_BAR_CTL	= 0xd2c,
	MV_PCI_DISC_TIMER	= 0xd04,
	MV_PCI_MSI_TRIGGER	= 0xc38,
	MV_PCI_SERR_MASK	= 0xc28,
	MV_PCI_XBAR_TMOUT	= 0x1d04,
	MV_PCI_ERR_LOW_ADDRESS	= 0x1d40,
	MV_PCI_ERR_HIGH_ADDRESS	= 0x1d44,
	MV_PCI_ERR_ATTRIBUTE	= 0x1d48,
	MV_PCI_ERR_COMMAND	= 0x1d50,

	PCI_IRQ_CAUSE		= 0x1d58,
	PCI_IRQ_MASK		= 0x1d5c,
	PCI_UNMASK_ALL_IRQS	= 0x7fffff,	/* bits 22-0 */

	PCIE_IRQ_CAUSE		= 0x1900,
	PCIE_IRQ_MASK		= 0x1910,
	PCIE_UNMASK_ALL_IRQS	= 0x40a,	/* assorted bits */

	/* Host Controller Main Interrupt Cause/Mask रेजिस्टरs (1 per-chip) */
	PCI_HC_MAIN_IRQ_CAUSE	= 0x1d60,
	PCI_HC_MAIN_IRQ_MASK	= 0x1d64,
	SOC_HC_MAIN_IRQ_CAUSE	= 0x20020,
	SOC_HC_MAIN_IRQ_MASK	= 0x20024,
	ERR_IRQ			= (1 << 0),	/* shअगरt by (2 * port #) */
	DONE_IRQ		= (1 << 1),	/* shअगरt by (2 * port #) */
	HC0_IRQ_PEND		= 0x1ff,	/* bits 0-8 = HC0's ports */
	HC_SHIFT		= 9,		/* bits 9-17 = HC1's ports */
	DONE_IRQ_0_3		= 0x000000aa,	/* DONE_IRQ ports 0,1,2,3 */
	DONE_IRQ_4_7		= (DONE_IRQ_0_3 << HC_SHIFT),  /* 4,5,6,7 */
	PCI_ERR			= (1 << 18),
	TRAN_COAL_LO_DONE	= (1 << 19),	/* transaction coalescing */
	TRAN_COAL_HI_DONE	= (1 << 20),	/* transaction coalescing */
	PORTS_0_3_COAL_DONE	= (1 << 8),	/* HC0 IRQ coalescing */
	PORTS_4_7_COAL_DONE	= (1 << 17),	/* HC1 IRQ coalescing */
	ALL_PORTS_COAL_DONE	= (1 << 21),	/* GEN_II(E) IRQ coalescing */
	GPIO_INT		= (1 << 22),
	SELF_INT		= (1 << 23),
	TWSI_INT		= (1 << 24),
	HC_MAIN_RSVD		= (0x7f << 25),	/* bits 31-25 */
	HC_MAIN_RSVD_5		= (0x1fff << 19), /* bits 31-19 */
	HC_MAIN_RSVD_SOC	= (0x3fffffb << 6),     /* bits 31-9, 7-6 */

	/* SATAHC रेजिस्टरs */
	HC_CFG			= 0x00,

	HC_IRQ_CAUSE		= 0x14,
	DMA_IRQ			= (1 << 0),	/* shअगरt by port # */
	HC_COAL_IRQ		= (1 << 4),	/* IRQ coalescing */
	DEV_IRQ			= (1 << 8),	/* shअगरt by port # */

	/*
	 * Per-HC (Host-Controller) पूर्णांकerrupt coalescing feature.
	 * This is present on all chip generations.
	 *
	 * Coalescing defers the पूर्णांकerrupt until either the IO_THRESHOLD
	 * (count of completed I/Os) is met, or the TIME_THRESHOLD is met.
	 */
	HC_IRQ_COAL_IO_THRESHOLD	= 0x000c,
	HC_IRQ_COAL_TIME_THRESHOLD	= 0x0010,

	SOC_LED_CTRL		= 0x2c,
	SOC_LED_CTRL_BLINK	= (1 << 0),	/* Active LED blink */
	SOC_LED_CTRL_ACT_PRESENCE = (1 << 2),	/* Multiplex dev presence */
						/*  with dev activity LED */

	/* Shaकरोw block रेजिस्टरs */
	SHD_BLK			= 0x100,
	SHD_CTL_AST		= 0x20,		/* ofs from SHD_BLK */

	/* SATA रेजिस्टरs */
	SATA_STATUS		= 0x300,  /* ctrl, err regs follow status */
	SATA_ACTIVE		= 0x350,
	FIS_IRQ_CAUSE		= 0x364,
	FIS_IRQ_CAUSE_AN	= (1 << 9),	/* async notअगरication */

	LTMODE			= 0x30c,	/* requires पढ़ो-after-ग_लिखो */
	LTMODE_BIT8		= (1 << 8),	/* unknown, but necessary */

	PHY_MODE2		= 0x330,
	PHY_MODE3		= 0x310,

	PHY_MODE4		= 0x314,	/* requires पढ़ो-after-ग_लिखो */
	PHY_MODE4_CFG_MASK	= 0x00000003,	/* phy पूर्णांकernal config field */
	PHY_MODE4_CFG_VALUE	= 0x00000001,	/* phy पूर्णांकernal config field */
	PHY_MODE4_RSVD_ZEROS	= 0x5de3fffa,	/* Gen2e always ग_लिखो zeros */
	PHY_MODE4_RSVD_ONES	= 0x00000005,	/* Gen2e always ग_लिखो ones */

	SATA_IFCTL		= 0x344,
	SATA_TESTCTL		= 0x348,
	SATA_IFSTAT		= 0x34c,
	VENDOR_UNIQUE_FIS	= 0x35c,

	FISCFG			= 0x360,
	FISCFG_WAIT_DEV_ERR	= (1 << 8),	/* रुको क्रम host on DevErr */
	FISCFG_SINGLE_SYNC	= (1 << 16),	/* SYNC on DMA activation */

	PHY_MODE9_GEN2		= 0x398,
	PHY_MODE9_GEN1		= 0x39c,
	PHYCFG_OFS		= 0x3a0,	/* only in 65n devices */

	MV5_PHY_MODE		= 0x74,
	MV5_LTMODE		= 0x30,
	MV5_PHY_CTL		= 0x0C,
	SATA_IFCFG		= 0x050,
	LP_PHY_CTL		= 0x058,
	LP_PHY_CTL_PIN_PU_PLL   = (1 << 0),
	LP_PHY_CTL_PIN_PU_RX    = (1 << 1),
	LP_PHY_CTL_PIN_PU_TX    = (1 << 2),
	LP_PHY_CTL_GEN_TX_3G    = (1 << 5),
	LP_PHY_CTL_GEN_RX_3G    = (1 << 9),

	MV_M2_PREAMP_MASK	= 0x7e0,

	/* Port रेजिस्टरs */
	EDMA_CFG		= 0,
	EDMA_CFG_Q_DEPTH	= 0x1f,		/* max device queue depth */
	EDMA_CFG_NCQ		= (1 << 5),	/* क्रम R/W FPDMA queued */
	EDMA_CFG_NCQ_GO_ON_ERR	= (1 << 14),	/* जारी on error */
	EDMA_CFG_RD_BRST_EXT	= (1 << 11),	/* पढ़ो burst 512B */
	EDMA_CFG_WR_BUFF_LEN	= (1 << 13),	/* ग_लिखो buffer 512B */
	EDMA_CFG_EDMA_FBS	= (1 << 16),	/* EDMA FIS-Based Switching */
	EDMA_CFG_FBS		= (1 << 26),	/* FIS-Based Switching */

	EDMA_ERR_IRQ_CAUSE	= 0x8,
	EDMA_ERR_IRQ_MASK	= 0xc,
	EDMA_ERR_D_PAR		= (1 << 0),	/* UDMA data parity err */
	EDMA_ERR_PRD_PAR	= (1 << 1),	/* UDMA PRD parity err */
	EDMA_ERR_DEV		= (1 << 2),	/* device error */
	EDMA_ERR_DEV_DCON	= (1 << 3),	/* device disconnect */
	EDMA_ERR_DEV_CON	= (1 << 4),	/* device connected */
	EDMA_ERR_SERR		= (1 << 5),	/* SError bits [WBDST] उठाओd */
	EDMA_ERR_SELF_DIS	= (1 << 7),	/* Gen II/IIE self-disable */
	EDMA_ERR_SELF_DIS_5	= (1 << 8),	/* Gen I self-disable */
	EDMA_ERR_BIST_ASYNC	= (1 << 8),	/* BIST FIS or Async Notअगरy */
	EDMA_ERR_TRANS_IRQ_7	= (1 << 8),	/* Gen IIE transprt layer irq */
	EDMA_ERR_CRQB_PAR	= (1 << 9),	/* CRQB parity error */
	EDMA_ERR_CRPB_PAR	= (1 << 10),	/* CRPB parity error */
	EDMA_ERR_INTRL_PAR	= (1 << 11),	/* पूर्णांकernal parity error */
	EDMA_ERR_IORDY		= (1 << 12),	/* IORdy समयout */

	EDMA_ERR_LNK_CTRL_RX	= (0xf << 13),	/* link ctrl rx error */
	EDMA_ERR_LNK_CTRL_RX_0	= (1 << 13),	/* transient: CRC err */
	EDMA_ERR_LNK_CTRL_RX_1	= (1 << 14),	/* transient: FIFO err */
	EDMA_ERR_LNK_CTRL_RX_2	= (1 << 15),	/* fatal: caught SYNC */
	EDMA_ERR_LNK_CTRL_RX_3	= (1 << 16),	/* transient: FIS rx err */

	EDMA_ERR_LNK_DATA_RX	= (0xf << 17),	/* link data rx error */

	EDMA_ERR_LNK_CTRL_TX	= (0x1f << 21),	/* link ctrl tx error */
	EDMA_ERR_LNK_CTRL_TX_0	= (1 << 21),	/* transient: CRC err */
	EDMA_ERR_LNK_CTRL_TX_1	= (1 << 22),	/* transient: FIFO err */
	EDMA_ERR_LNK_CTRL_TX_2	= (1 << 23),	/* transient: caught SYNC */
	EDMA_ERR_LNK_CTRL_TX_3	= (1 << 24),	/* transient: caught DMAT */
	EDMA_ERR_LNK_CTRL_TX_4	= (1 << 25),	/* transient: FIS collision */

	EDMA_ERR_LNK_DATA_TX	= (0x1f << 26),	/* link data tx error */

	EDMA_ERR_TRANS_PROTO	= (1 << 31),	/* transport protocol error */
	EDMA_ERR_OVERRUN_5	= (1 << 5),
	EDMA_ERR_UNDERRUN_5	= (1 << 6),

	EDMA_ERR_IRQ_TRANSIENT  = EDMA_ERR_LNK_CTRL_RX_0 |
				  EDMA_ERR_LNK_CTRL_RX_1 |
				  EDMA_ERR_LNK_CTRL_RX_3 |
				  EDMA_ERR_LNK_CTRL_TX,

	EDMA_EH_FREEZE		= EDMA_ERR_D_PAR |
				  EDMA_ERR_PRD_PAR |
				  EDMA_ERR_DEV_DCON |
				  EDMA_ERR_DEV_CON |
				  EDMA_ERR_SERR |
				  EDMA_ERR_SELF_DIS |
				  EDMA_ERR_CRQB_PAR |
				  EDMA_ERR_CRPB_PAR |
				  EDMA_ERR_INTRL_PAR |
				  EDMA_ERR_IORDY |
				  EDMA_ERR_LNK_CTRL_RX_2 |
				  EDMA_ERR_LNK_DATA_RX |
				  EDMA_ERR_LNK_DATA_TX |
				  EDMA_ERR_TRANS_PROTO,

	EDMA_EH_FREEZE_5	= EDMA_ERR_D_PAR |
				  EDMA_ERR_PRD_PAR |
				  EDMA_ERR_DEV_DCON |
				  EDMA_ERR_DEV_CON |
				  EDMA_ERR_OVERRUN_5 |
				  EDMA_ERR_UNDERRUN_5 |
				  EDMA_ERR_SELF_DIS_5 |
				  EDMA_ERR_CRQB_PAR |
				  EDMA_ERR_CRPB_PAR |
				  EDMA_ERR_INTRL_PAR |
				  EDMA_ERR_IORDY,

	EDMA_REQ_Q_BASE_HI	= 0x10,
	EDMA_REQ_Q_IN_PTR	= 0x14,		/* also contains BASE_LO */

	EDMA_REQ_Q_OUT_PTR	= 0x18,
	EDMA_REQ_Q_PTR_SHIFT	= 5,

	EDMA_RSP_Q_BASE_HI	= 0x1c,
	EDMA_RSP_Q_IN_PTR	= 0x20,
	EDMA_RSP_Q_OUT_PTR	= 0x24,		/* also contains BASE_LO */
	EDMA_RSP_Q_PTR_SHIFT	= 3,

	EDMA_CMD		= 0x28,		/* EDMA command रेजिस्टर */
	EDMA_EN			= (1 << 0),	/* enable EDMA */
	EDMA_DS			= (1 << 1),	/* disable EDMA; self-negated */
	EDMA_RESET		= (1 << 2),	/* reset eng/trans/link/phy */

	EDMA_STATUS		= 0x30,		/* EDMA engine status */
	EDMA_STATUS_CACHE_EMPTY	= (1 << 6),	/* GenIIe command cache empty */
	EDMA_STATUS_IDLE	= (1 << 7),	/* GenIIe EDMA enabled/idle */

	EDMA_IORDY_TMOUT	= 0x34,
	EDMA_ARB_CFG		= 0x38,

	EDMA_HALTCOND		= 0x60,		/* GenIIe halt conditions */
	EDMA_UNKNOWN_RSVD	= 0x6C,		/* GenIIe unknown/reserved */

	BMDMA_CMD		= 0x224,	/* bmdma command रेजिस्टर */
	BMDMA_STATUS		= 0x228,	/* bmdma status रेजिस्टर */
	BMDMA_PRD_LOW		= 0x22c,	/* bmdma PRD addr 31:0 */
	BMDMA_PRD_HIGH		= 0x230,	/* bmdma PRD addr 63:32 */

	/* Host निजी flags (hp_flags) */
	MV_HP_FLAG_MSI		= (1 << 0),
	MV_HP_ERRATA_50XXB0	= (1 << 1),
	MV_HP_ERRATA_50XXB2	= (1 << 2),
	MV_HP_ERRATA_60X1B2	= (1 << 3),
	MV_HP_ERRATA_60X1C0	= (1 << 4),
	MV_HP_GEN_I		= (1 << 6),	/* Generation I: 50xx */
	MV_HP_GEN_II		= (1 << 7),	/* Generation II: 60xx */
	MV_HP_GEN_IIE		= (1 << 8),	/* Generation IIE: 6042/7042 */
	MV_HP_PCIE		= (1 << 9),	/* PCIe bus/regs: 7042 */
	MV_HP_CUT_THROUGH	= (1 << 10),	/* can use EDMA cut-through */
	MV_HP_FLAG_SOC		= (1 << 11),	/* SystemOnChip, no PCI */
	MV_HP_QUIRK_LED_BLINK_EN = (1 << 12),	/* is led blinking enabled? */
	MV_HP_FIX_LP_PHY_CTL	= (1 << 13),	/* fix speed in LP_PHY_CTL ? */

	/* Port निजी flags (pp_flags) */
	MV_PP_FLAG_EDMA_EN	= (1 << 0),	/* is EDMA engine enabled? */
	MV_PP_FLAG_NCQ_EN	= (1 << 1),	/* is EDMA set up क्रम NCQ? */
	MV_PP_FLAG_FBS_EN	= (1 << 2),	/* is EDMA set up क्रम FBS? */
	MV_PP_FLAG_DELAYED_EH	= (1 << 3),	/* delayed dev err handling */
	MV_PP_FLAG_FAKE_ATA_BUSY = (1 << 4),	/* ignore initial ATA_DRDY */
पूर्ण;

#घोषणा IS_GEN_I(hpriv) ((hpriv)->hp_flags & MV_HP_GEN_I)
#घोषणा IS_GEN_II(hpriv) ((hpriv)->hp_flags & MV_HP_GEN_II)
#घोषणा IS_GEN_IIE(hpriv) ((hpriv)->hp_flags & MV_HP_GEN_IIE)
#घोषणा IS_PCIE(hpriv) ((hpriv)->hp_flags & MV_HP_PCIE)
#घोषणा IS_SOC(hpriv) ((hpriv)->hp_flags & MV_HP_FLAG_SOC)

#घोषणा WINDOW_CTRL(i)		(0x20030 + ((i) << 4))
#घोषणा WINDOW_BASE(i)		(0x20034 + ((i) << 4))

क्रमागत अणु
	/* DMA boundary 0xffff is required by the s/g splitting
	 * we need on /length/ in mv_fill-sg().
	 */
	MV_DMA_BOUNDARY		= 0xffffU,

	/* mask of रेजिस्टर bits containing lower 32 bits
	 * of EDMA request queue DMA address
	 */
	EDMA_REQ_Q_BASE_LO_MASK	= 0xfffffc00U,

	/* ditto, क्रम response queue */
	EDMA_RSP_Q_BASE_LO_MASK	= 0xffffff00U,
पूर्ण;

क्रमागत chip_type अणु
	chip_504x,
	chip_508x,
	chip_5080,
	chip_604x,
	chip_608x,
	chip_6042,
	chip_7042,
	chip_soc,
पूर्ण;

/* Command ReQuest Block: 32B */
काष्ठा mv_crqb अणु
	__le32			sg_addr;
	__le32			sg_addr_hi;
	__le16			ctrl_flags;
	__le16			ata_cmd[11];
पूर्ण;

काष्ठा mv_crqb_iie अणु
	__le32			addr;
	__le32			addr_hi;
	__le32			flags;
	__le32			len;
	__le32			ata_cmd[4];
पूर्ण;

/* Command ResPonse Block: 8B */
काष्ठा mv_crpb अणु
	__le16			id;
	__le16			flags;
	__le32			पंचांगsपंचांगp;
पूर्ण;

/* EDMA Physical Region Descriptor (ePRD); A.K.A. SG */
काष्ठा mv_sg अणु
	__le32			addr;
	__le32			flags_size;
	__le32			addr_hi;
	__le32			reserved;
पूर्ण;

/*
 * We keep a local cache of a few frequently accessed port
 * रेजिस्टरs here, to aव्योम having to पढ़ो them (very slow)
 * when चयनing between EDMA and non-EDMA modes.
 */
काष्ठा mv_cached_regs अणु
	u32			fiscfg;
	u32			lपंचांगode;
	u32			haltcond;
	u32			unknown_rsvd;
पूर्ण;

काष्ठा mv_port_priv अणु
	काष्ठा mv_crqb		*crqb;
	dma_addr_t		crqb_dma;
	काष्ठा mv_crpb		*crpb;
	dma_addr_t		crpb_dma;
	काष्ठा mv_sg		*sg_tbl[MV_MAX_Q_DEPTH];
	dma_addr_t		sg_tbl_dma[MV_MAX_Q_DEPTH];

	अचिन्हित पूर्णांक		req_idx;
	अचिन्हित पूर्णांक		resp_idx;

	u32			pp_flags;
	काष्ठा mv_cached_regs	cached;
	अचिन्हित पूर्णांक		delayed_eh_pmp_map;
पूर्ण;

काष्ठा mv_port_संकेत अणु
	u32			amps;
	u32			pre;
पूर्ण;

काष्ठा mv_host_priv अणु
	u32			hp_flags;
	अचिन्हित पूर्णांक 		board_idx;
	u32			मुख्य_irq_mask;
	काष्ठा mv_port_संकेत	संकेत[8];
	स्थिर काष्ठा mv_hw_ops	*ops;
	पूर्णांक			n_ports;
	व्योम __iomem		*base;
	व्योम __iomem		*मुख्य_irq_cause_addr;
	व्योम __iomem		*मुख्य_irq_mask_addr;
	u32			irq_cause_offset;
	u32			irq_mask_offset;
	u32			unmask_all_irqs;

	/*
	 * Needed on some devices that require their घड़ीs to be enabled.
	 * These are optional: अगर the platक्रमm device करोes not have any
	 * घड़ीs, they won't be used.  Also, अगर the underlying hardware
	 * करोes not support the common घड़ी framework (CONFIG_HAVE_CLK=n),
	 * all the घड़ी operations become no-ops (see clk.h).
	 */
	काष्ठा clk		*clk;
	काष्ठा clk              **port_clks;
	/*
	 * Some devices have a SATA PHY which can be enabled/disabled
	 * in order to save घातer. These are optional: अगर the platक्रमm
	 * devices करोes not have any phy, they won't be used.
	 */
	काष्ठा phy		**port_phys;
	/*
	 * These consistent DMA memory pools give us guaranteed
	 * alignment क्रम hardware-accessed data काष्ठाures,
	 * and less memory waste in accomplishing the alignment.
	 */
	काष्ठा dma_pool		*crqb_pool;
	काष्ठा dma_pool		*crpb_pool;
	काष्ठा dma_pool		*sg_tbl_pool;
पूर्ण;

काष्ठा mv_hw_ops अणु
	व्योम (*phy_errata)(काष्ठा mv_host_priv *hpriv, व्योम __iomem *mmio,
			   अचिन्हित पूर्णांक port);
	व्योम (*enable_leds)(काष्ठा mv_host_priv *hpriv, व्योम __iomem *mmio);
	व्योम (*पढ़ो_preamp)(काष्ठा mv_host_priv *hpriv, पूर्णांक idx,
			   व्योम __iomem *mmio);
	पूर्णांक (*reset_hc)(काष्ठा mv_host_priv *hpriv, व्योम __iomem *mmio,
			अचिन्हित पूर्णांक n_hc);
	व्योम (*reset_flash)(काष्ठा mv_host_priv *hpriv, व्योम __iomem *mmio);
	व्योम (*reset_bus)(काष्ठा ata_host *host, व्योम __iomem *mmio);
पूर्ण;

अटल पूर्णांक mv_scr_पढ़ो(काष्ठा ata_link *link, अचिन्हित पूर्णांक sc_reg_in, u32 *val);
अटल पूर्णांक mv_scr_ग_लिखो(काष्ठा ata_link *link, अचिन्हित पूर्णांक sc_reg_in, u32 val);
अटल पूर्णांक mv5_scr_पढ़ो(काष्ठा ata_link *link, अचिन्हित पूर्णांक sc_reg_in, u32 *val);
अटल पूर्णांक mv5_scr_ग_लिखो(काष्ठा ata_link *link, अचिन्हित पूर्णांक sc_reg_in, u32 val);
अटल पूर्णांक mv_port_start(काष्ठा ata_port *ap);
अटल व्योम mv_port_stop(काष्ठा ata_port *ap);
अटल पूर्णांक mv_qc_defer(काष्ठा ata_queued_cmd *qc);
अटल क्रमागत ata_completion_errors mv_qc_prep(काष्ठा ata_queued_cmd *qc);
अटल क्रमागत ata_completion_errors mv_qc_prep_iie(काष्ठा ata_queued_cmd *qc);
अटल अचिन्हित पूर्णांक mv_qc_issue(काष्ठा ata_queued_cmd *qc);
अटल पूर्णांक mv_hardreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *class,
			अचिन्हित दीर्घ deadline);
अटल व्योम mv_eh_मुक्तze(काष्ठा ata_port *ap);
अटल व्योम mv_eh_thaw(काष्ठा ata_port *ap);
अटल व्योम mv6_dev_config(काष्ठा ata_device *dev);

अटल व्योम mv5_phy_errata(काष्ठा mv_host_priv *hpriv, व्योम __iomem *mmio,
			   अचिन्हित पूर्णांक port);
अटल व्योम mv5_enable_leds(काष्ठा mv_host_priv *hpriv, व्योम __iomem *mmio);
अटल व्योम mv5_पढ़ो_preamp(काष्ठा mv_host_priv *hpriv, पूर्णांक idx,
			   व्योम __iomem *mmio);
अटल पूर्णांक mv5_reset_hc(काष्ठा mv_host_priv *hpriv, व्योम __iomem *mmio,
			अचिन्हित पूर्णांक n_hc);
अटल व्योम mv5_reset_flash(काष्ठा mv_host_priv *hpriv, व्योम __iomem *mmio);
अटल व्योम mv5_reset_bus(काष्ठा ata_host *host, व्योम __iomem *mmio);

अटल व्योम mv6_phy_errata(काष्ठा mv_host_priv *hpriv, व्योम __iomem *mmio,
			   अचिन्हित पूर्णांक port);
अटल व्योम mv6_enable_leds(काष्ठा mv_host_priv *hpriv, व्योम __iomem *mmio);
अटल व्योम mv6_पढ़ो_preamp(काष्ठा mv_host_priv *hpriv, पूर्णांक idx,
			   व्योम __iomem *mmio);
अटल पूर्णांक mv6_reset_hc(काष्ठा mv_host_priv *hpriv, व्योम __iomem *mmio,
			अचिन्हित पूर्णांक n_hc);
अटल व्योम mv6_reset_flash(काष्ठा mv_host_priv *hpriv, व्योम __iomem *mmio);
अटल व्योम mv_soc_enable_leds(काष्ठा mv_host_priv *hpriv,
				      व्योम __iomem *mmio);
अटल व्योम mv_soc_पढ़ो_preamp(काष्ठा mv_host_priv *hpriv, पूर्णांक idx,
				      व्योम __iomem *mmio);
अटल पूर्णांक mv_soc_reset_hc(काष्ठा mv_host_priv *hpriv,
				  व्योम __iomem *mmio, अचिन्हित पूर्णांक n_hc);
अटल व्योम mv_soc_reset_flash(काष्ठा mv_host_priv *hpriv,
				      व्योम __iomem *mmio);
अटल व्योम mv_soc_reset_bus(काष्ठा ata_host *host, व्योम __iomem *mmio);
अटल व्योम mv_soc_65n_phy_errata(काष्ठा mv_host_priv *hpriv,
				  व्योम __iomem *mmio, अचिन्हित पूर्णांक port);
अटल व्योम mv_reset_pci_bus(काष्ठा ata_host *host, व्योम __iomem *mmio);
अटल व्योम mv_reset_channel(काष्ठा mv_host_priv *hpriv, व्योम __iomem *mmio,
			     अचिन्हित पूर्णांक port_no);
अटल पूर्णांक mv_stop_edma(काष्ठा ata_port *ap);
अटल पूर्णांक mv_stop_edma_engine(व्योम __iomem *port_mmio);
अटल व्योम mv_edma_cfg(काष्ठा ata_port *ap, पूर्णांक want_ncq, पूर्णांक want_edma);

अटल व्योम mv_pmp_select(काष्ठा ata_port *ap, पूर्णांक pmp);
अटल पूर्णांक mv_pmp_hardreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *class,
				अचिन्हित दीर्घ deadline);
अटल पूर्णांक  mv_softreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *class,
				अचिन्हित दीर्घ deadline);
अटल व्योम mv_pmp_error_handler(काष्ठा ata_port *ap);
अटल व्योम mv_process_crpb_entries(काष्ठा ata_port *ap,
					काष्ठा mv_port_priv *pp);

अटल व्योम mv_sff_irq_clear(काष्ठा ata_port *ap);
अटल पूर्णांक mv_check_atapi_dma(काष्ठा ata_queued_cmd *qc);
अटल व्योम mv_bmdma_setup(काष्ठा ata_queued_cmd *qc);
अटल व्योम mv_bmdma_start(काष्ठा ata_queued_cmd *qc);
अटल व्योम mv_bmdma_stop(काष्ठा ata_queued_cmd *qc);
अटल u8   mv_bmdma_status(काष्ठा ata_port *ap);
अटल u8 mv_sff_check_status(काष्ठा ata_port *ap);

/* .sg_tablesize is (MV_MAX_SG_CT / 2) in the काष्ठाures below
 * because we have to allow room क्रम worst हाल splitting of
 * PRDs क्रम 64K boundaries in mv_fill_sg().
 */
#अगर_घोषित CONFIG_PCI
अटल काष्ठा scsi_host_ढाँचा mv5_sht = अणु
	ATA_BASE_SHT(DRV_NAME),
	.sg_tablesize		= MV_MAX_SG_CT / 2,
	.dma_boundary		= MV_DMA_BOUNDARY,
पूर्ण;
#पूर्ण_अगर
अटल काष्ठा scsi_host_ढाँचा mv6_sht = अणु
	ATA_NCQ_SHT(DRV_NAME),
	.can_queue		= MV_MAX_Q_DEPTH - 1,
	.sg_tablesize		= MV_MAX_SG_CT / 2,
	.dma_boundary		= MV_DMA_BOUNDARY,
पूर्ण;

अटल काष्ठा ata_port_operations mv5_ops = अणु
	.inherits		= &ata_sff_port_ops,

	.lost_पूर्णांकerrupt		= ATA_OP_शून्य,

	.qc_defer		= mv_qc_defer,
	.qc_prep		= mv_qc_prep,
	.qc_issue		= mv_qc_issue,

	.मुक्तze			= mv_eh_मुक्तze,
	.thaw			= mv_eh_thaw,
	.hardreset		= mv_hardreset,

	.scr_पढ़ो		= mv5_scr_पढ़ो,
	.scr_ग_लिखो		= mv5_scr_ग_लिखो,

	.port_start		= mv_port_start,
	.port_stop		= mv_port_stop,
पूर्ण;

अटल काष्ठा ata_port_operations mv6_ops = अणु
	.inherits		= &ata_bmdma_port_ops,

	.lost_पूर्णांकerrupt		= ATA_OP_शून्य,

	.qc_defer		= mv_qc_defer,
	.qc_prep		= mv_qc_prep,
	.qc_issue		= mv_qc_issue,

	.dev_config             = mv6_dev_config,

	.मुक्तze			= mv_eh_मुक्तze,
	.thaw			= mv_eh_thaw,
	.hardreset		= mv_hardreset,
	.softreset		= mv_softreset,
	.pmp_hardreset		= mv_pmp_hardreset,
	.pmp_softreset		= mv_softreset,
	.error_handler		= mv_pmp_error_handler,

	.scr_पढ़ो		= mv_scr_पढ़ो,
	.scr_ग_लिखो		= mv_scr_ग_लिखो,

	.sff_check_status	= mv_sff_check_status,
	.sff_irq_clear		= mv_sff_irq_clear,
	.check_atapi_dma	= mv_check_atapi_dma,
	.bmdma_setup		= mv_bmdma_setup,
	.bmdma_start		= mv_bmdma_start,
	.bmdma_stop		= mv_bmdma_stop,
	.bmdma_status		= mv_bmdma_status,

	.port_start		= mv_port_start,
	.port_stop		= mv_port_stop,
पूर्ण;

अटल काष्ठा ata_port_operations mv_iie_ops = अणु
	.inherits		= &mv6_ops,
	.dev_config		= ATA_OP_शून्य,
	.qc_prep		= mv_qc_prep_iie,
पूर्ण;

अटल स्थिर काष्ठा ata_port_info mv_port_info[] = अणु
	अणु  /* chip_504x */
		.flags		= MV_GEN_I_FLAGS,
		.pio_mask	= ATA_PIO4,
		.udma_mask	= ATA_UDMA6,
		.port_ops	= &mv5_ops,
	पूर्ण,
	अणु  /* chip_508x */
		.flags		= MV_GEN_I_FLAGS | MV_FLAG_DUAL_HC,
		.pio_mask	= ATA_PIO4,
		.udma_mask	= ATA_UDMA6,
		.port_ops	= &mv5_ops,
	पूर्ण,
	अणु  /* chip_5080 */
		.flags		= MV_GEN_I_FLAGS | MV_FLAG_DUAL_HC,
		.pio_mask	= ATA_PIO4,
		.udma_mask	= ATA_UDMA6,
		.port_ops	= &mv5_ops,
	पूर्ण,
	अणु  /* chip_604x */
		.flags		= MV_GEN_II_FLAGS,
		.pio_mask	= ATA_PIO4,
		.udma_mask	= ATA_UDMA6,
		.port_ops	= &mv6_ops,
	पूर्ण,
	अणु  /* chip_608x */
		.flags		= MV_GEN_II_FLAGS | MV_FLAG_DUAL_HC,
		.pio_mask	= ATA_PIO4,
		.udma_mask	= ATA_UDMA6,
		.port_ops	= &mv6_ops,
	पूर्ण,
	अणु  /* chip_6042 */
		.flags		= MV_GEN_IIE_FLAGS,
		.pio_mask	= ATA_PIO4,
		.udma_mask	= ATA_UDMA6,
		.port_ops	= &mv_iie_ops,
	पूर्ण,
	अणु  /* chip_7042 */
		.flags		= MV_GEN_IIE_FLAGS,
		.pio_mask	= ATA_PIO4,
		.udma_mask	= ATA_UDMA6,
		.port_ops	= &mv_iie_ops,
	पूर्ण,
	अणु  /* chip_soc */
		.flags		= MV_GEN_IIE_FLAGS,
		.pio_mask	= ATA_PIO4,
		.udma_mask	= ATA_UDMA6,
		.port_ops	= &mv_iie_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id mv_pci_tbl[] = अणु
	अणु PCI_VDEVICE(MARVELL, 0x5040), chip_504x पूर्ण,
	अणु PCI_VDEVICE(MARVELL, 0x5041), chip_504x पूर्ण,
	अणु PCI_VDEVICE(MARVELL, 0x5080), chip_5080 पूर्ण,
	अणु PCI_VDEVICE(MARVELL, 0x5081), chip_508x पूर्ण,
	/* RocketRAID 1720/174x have dअगरferent identअगरiers */
	अणु PCI_VDEVICE(TTI, 0x1720), chip_6042 पूर्ण,
	अणु PCI_VDEVICE(TTI, 0x1740), chip_6042 पूर्ण,
	अणु PCI_VDEVICE(TTI, 0x1742), chip_6042 पूर्ण,

	अणु PCI_VDEVICE(MARVELL, 0x6040), chip_604x पूर्ण,
	अणु PCI_VDEVICE(MARVELL, 0x6041), chip_604x पूर्ण,
	अणु PCI_VDEVICE(MARVELL, 0x6042), chip_6042 पूर्ण,
	अणु PCI_VDEVICE(MARVELL, 0x6080), chip_608x पूर्ण,
	अणु PCI_VDEVICE(MARVELL, 0x6081), chip_608x पूर्ण,

	अणु PCI_VDEVICE(ADAPTEC2, 0x0241), chip_604x पूर्ण,

	/* Adaptec 1430SA */
	अणु PCI_VDEVICE(ADAPTEC2, 0x0243), chip_7042 पूर्ण,

	/* Marvell 7042 support */
	अणु PCI_VDEVICE(MARVELL, 0x7042), chip_7042 पूर्ण,

	/* Highpoपूर्णांक RocketRAID PCIe series */
	अणु PCI_VDEVICE(TTI, 0x2300), chip_7042 पूर्ण,
	अणु PCI_VDEVICE(TTI, 0x2310), chip_7042 पूर्ण,

	अणु पूर्ण			/* terminate list */
पूर्ण;

अटल स्थिर काष्ठा mv_hw_ops mv5xxx_ops = अणु
	.phy_errata		= mv5_phy_errata,
	.enable_leds		= mv5_enable_leds,
	.पढ़ो_preamp		= mv5_पढ़ो_preamp,
	.reset_hc		= mv5_reset_hc,
	.reset_flash		= mv5_reset_flash,
	.reset_bus		= mv5_reset_bus,
पूर्ण;

अटल स्थिर काष्ठा mv_hw_ops mv6xxx_ops = अणु
	.phy_errata		= mv6_phy_errata,
	.enable_leds		= mv6_enable_leds,
	.पढ़ो_preamp		= mv6_पढ़ो_preamp,
	.reset_hc		= mv6_reset_hc,
	.reset_flash		= mv6_reset_flash,
	.reset_bus		= mv_reset_pci_bus,
पूर्ण;

अटल स्थिर काष्ठा mv_hw_ops mv_soc_ops = अणु
	.phy_errata		= mv6_phy_errata,
	.enable_leds		= mv_soc_enable_leds,
	.पढ़ो_preamp		= mv_soc_पढ़ो_preamp,
	.reset_hc		= mv_soc_reset_hc,
	.reset_flash		= mv_soc_reset_flash,
	.reset_bus		= mv_soc_reset_bus,
पूर्ण;

अटल स्थिर काष्ठा mv_hw_ops mv_soc_65n_ops = अणु
	.phy_errata		= mv_soc_65n_phy_errata,
	.enable_leds		= mv_soc_enable_leds,
	.reset_hc		= mv_soc_reset_hc,
	.reset_flash		= mv_soc_reset_flash,
	.reset_bus		= mv_soc_reset_bus,
पूर्ण;

/*
 * Functions
 */

अटल अंतरभूत व्योम ग_लिखोlfl(अचिन्हित दीर्घ data, व्योम __iomem *addr)
अणु
	ग_लिखोl(data, addr);
	(व्योम) पढ़ोl(addr);	/* flush to aव्योम PCI posted ग_लिखो */
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक mv_hc_from_port(अचिन्हित पूर्णांक port)
अणु
	वापस port >> MV_PORT_HC_SHIFT;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक mv_hardport_from_port(अचिन्हित पूर्णांक port)
अणु
	वापस port & MV_PORT_MASK;
पूर्ण

/*
 * Consolidate some rather tricky bit shअगरt calculations.
 * This is hot-path stuff, so not a function.
 * Simple code, with two वापस values, so macro rather than अंतरभूत.
 *
 * port is the sole input, in range 0..7.
 * shअगरt is one output, क्रम use with मुख्य_irq_cause / मुख्य_irq_mask रेजिस्टरs.
 * hardport is the other output, in range 0..3.
 *
 * Note that port and hardport may be the same variable in some हालs.
 */
#घोषणा MV_PORT_TO_SHIFT_AND_HARDPORT(port, shअगरt, hardport)	\
अणु								\
	shअगरt    = mv_hc_from_port(port) * HC_SHIFT;		\
	hardport = mv_hardport_from_port(port);			\
	shअगरt   += hardport * 2;				\
पूर्ण

अटल अंतरभूत व्योम __iomem *mv_hc_base(व्योम __iomem *base, अचिन्हित पूर्णांक hc)
अणु
	वापस (base + SATAHC0_REG_BASE + (hc * MV_SATAHC_REG_SZ));
पूर्ण

अटल अंतरभूत व्योम __iomem *mv_hc_base_from_port(व्योम __iomem *base,
						 अचिन्हित पूर्णांक port)
अणु
	वापस mv_hc_base(base, mv_hc_from_port(port));
पूर्ण

अटल अंतरभूत व्योम __iomem *mv_port_base(व्योम __iomem *base, अचिन्हित पूर्णांक port)
अणु
	वापस  mv_hc_base_from_port(base, port) +
		MV_SATAHC_ARBTR_REG_SZ +
		(mv_hardport_from_port(port) * MV_PORT_REG_SZ);
पूर्ण

अटल व्योम __iomem *mv5_phy_base(व्योम __iomem *mmio, अचिन्हित पूर्णांक port)
अणु
	व्योम __iomem *hc_mmio = mv_hc_base_from_port(mmio, port);
	अचिन्हित दीर्घ ofs = (mv_hardport_from_port(port) + 1) * 0x100UL;

	वापस hc_mmio + ofs;
पूर्ण

अटल अंतरभूत व्योम __iomem *mv_host_base(काष्ठा ata_host *host)
अणु
	काष्ठा mv_host_priv *hpriv = host->निजी_data;
	वापस hpriv->base;
पूर्ण

अटल अंतरभूत व्योम __iomem *mv_ap_base(काष्ठा ata_port *ap)
अणु
	वापस mv_port_base(mv_host_base(ap->host), ap->port_no);
पूर्ण

अटल अंतरभूत पूर्णांक mv_get_hc_count(अचिन्हित दीर्घ port_flags)
अणु
	वापस ((port_flags & MV_FLAG_DUAL_HC) ? 2 : 1);
पूर्ण

/**
 *      mv_save_cached_regs - (re-)initialize cached port रेजिस्टरs
 *      @ap: the port whose रेजिस्टरs we are caching
 *
 *	Initialize the local cache of port रेजिस्टरs,
 *	so that पढ़ोing them over and over again can
 *	be aव्योमed on the hotter paths of this driver.
 *	This saves a few microseconds each समय we चयन
 *	to/from EDMA mode to perक्रमm (eg.) a drive cache flush.
 */
अटल व्योम mv_save_cached_regs(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *port_mmio = mv_ap_base(ap);
	काष्ठा mv_port_priv *pp = ap->निजी_data;

	pp->cached.fiscfg = पढ़ोl(port_mmio + FISCFG);
	pp->cached.lपंचांगode = पढ़ोl(port_mmio + LTMODE);
	pp->cached.haltcond = पढ़ोl(port_mmio + EDMA_HALTCOND);
	pp->cached.unknown_rsvd = पढ़ोl(port_mmio + EDMA_UNKNOWN_RSVD);
पूर्ण

/**
 *      mv_ग_लिखो_cached_reg - ग_लिखो to a cached port रेजिस्टर
 *      @addr: hardware address of the रेजिस्टर
 *      @old: poपूर्णांकer to cached value of the रेजिस्टर
 *      @new: new value क्रम the रेजिस्टर
 *
 *	Write a new value to a cached रेजिस्टर,
 *	but only अगर the value is dअगरferent from beक्रमe.
 */
अटल अंतरभूत व्योम mv_ग_लिखो_cached_reg(व्योम __iomem *addr, u32 *old, u32 new)
अणु
	अगर (new != *old) अणु
		अचिन्हित दीर्घ laddr;
		*old = new;
		/*
		 * Workaround क्रम 88SX60x1-B2 FEr SATA#13:
		 * Read-after-ग_लिखो is needed to prevent generating 64-bit
		 * ग_लिखो cycles on the PCI bus क्रम SATA पूर्णांकerface रेजिस्टरs
		 * at offsets ending in 0x4 or 0xc.
		 *
		 * Looks like a lot of fuss, but it aव्योमs an unnecessary
		 * +1 usec पढ़ो-after-ग_लिखो delay क्रम unaffected रेजिस्टरs.
		 */
		laddr = (अचिन्हित दीर्घ)addr & 0xffff;
		अगर (laddr >= 0x300 && laddr <= 0x33c) अणु
			laddr &= 0x000f;
			अगर (laddr == 0x4 || laddr == 0xc) अणु
				ग_लिखोlfl(new, addr); /* पढ़ो after ग_लिखो */
				वापस;
			पूर्ण
		पूर्ण
		ग_लिखोl(new, addr); /* unaffected by the errata */
	पूर्ण
पूर्ण

अटल व्योम mv_set_edma_ptrs(व्योम __iomem *port_mmio,
			     काष्ठा mv_host_priv *hpriv,
			     काष्ठा mv_port_priv *pp)
अणु
	u32 index;

	/*
	 * initialize request queue
	 */
	pp->req_idx &= MV_MAX_Q_DEPTH_MASK;	/* paranoia */
	index = pp->req_idx << EDMA_REQ_Q_PTR_SHIFT;

	WARN_ON(pp->crqb_dma & 0x3ff);
	ग_लिखोl((pp->crqb_dma >> 16) >> 16, port_mmio + EDMA_REQ_Q_BASE_HI);
	ग_लिखोlfl((pp->crqb_dma & EDMA_REQ_Q_BASE_LO_MASK) | index,
		 port_mmio + EDMA_REQ_Q_IN_PTR);
	ग_लिखोlfl(index, port_mmio + EDMA_REQ_Q_OUT_PTR);

	/*
	 * initialize response queue
	 */
	pp->resp_idx &= MV_MAX_Q_DEPTH_MASK;	/* paranoia */
	index = pp->resp_idx << EDMA_RSP_Q_PTR_SHIFT;

	WARN_ON(pp->crpb_dma & 0xff);
	ग_लिखोl((pp->crpb_dma >> 16) >> 16, port_mmio + EDMA_RSP_Q_BASE_HI);
	ग_लिखोlfl(index, port_mmio + EDMA_RSP_Q_IN_PTR);
	ग_लिखोlfl((pp->crpb_dma & EDMA_RSP_Q_BASE_LO_MASK) | index,
		 port_mmio + EDMA_RSP_Q_OUT_PTR);
पूर्ण

अटल व्योम mv_ग_लिखो_मुख्य_irq_mask(u32 mask, काष्ठा mv_host_priv *hpriv)
अणु
	/*
	 * When writing to the मुख्य_irq_mask in hardware,
	 * we must ensure exclusivity between the पूर्णांकerrupt coalescing bits
	 * and the corresponding inभागidual port DONE_IRQ bits.
	 *
	 * Note that this रेजिस्टर is really an "IRQ enable" रेजिस्टर,
	 * not an "IRQ mask" रेजिस्टर as Marvell's naming might suggest.
	 */
	अगर (mask & (ALL_PORTS_COAL_DONE | PORTS_0_3_COAL_DONE))
		mask &= ~DONE_IRQ_0_3;
	अगर (mask & (ALL_PORTS_COAL_DONE | PORTS_4_7_COAL_DONE))
		mask &= ~DONE_IRQ_4_7;
	ग_लिखोlfl(mask, hpriv->मुख्य_irq_mask_addr);
पूर्ण

अटल व्योम mv_set_मुख्य_irq_mask(काष्ठा ata_host *host,
				 u32 disable_bits, u32 enable_bits)
अणु
	काष्ठा mv_host_priv *hpriv = host->निजी_data;
	u32 old_mask, new_mask;

	old_mask = hpriv->मुख्य_irq_mask;
	new_mask = (old_mask & ~disable_bits) | enable_bits;
	अगर (new_mask != old_mask) अणु
		hpriv->मुख्य_irq_mask = new_mask;
		mv_ग_लिखो_मुख्य_irq_mask(new_mask, hpriv);
	पूर्ण
पूर्ण

अटल व्योम mv_enable_port_irqs(काष्ठा ata_port *ap,
				     अचिन्हित पूर्णांक port_bits)
अणु
	अचिन्हित पूर्णांक shअगरt, hardport, port = ap->port_no;
	u32 disable_bits, enable_bits;

	MV_PORT_TO_SHIFT_AND_HARDPORT(port, shअगरt, hardport);

	disable_bits = (DONE_IRQ | ERR_IRQ) << shअगरt;
	enable_bits  = port_bits << shअगरt;
	mv_set_मुख्य_irq_mask(ap->host, disable_bits, enable_bits);
पूर्ण

अटल व्योम mv_clear_and_enable_port_irqs(काष्ठा ata_port *ap,
					  व्योम __iomem *port_mmio,
					  अचिन्हित पूर्णांक port_irqs)
अणु
	काष्ठा mv_host_priv *hpriv = ap->host->निजी_data;
	पूर्णांक hardport = mv_hardport_from_port(ap->port_no);
	व्योम __iomem *hc_mmio = mv_hc_base_from_port(
				mv_host_base(ap->host), ap->port_no);
	u32 hc_irq_cause;

	/* clear EDMA event indicators, अगर any */
	ग_लिखोlfl(0, port_mmio + EDMA_ERR_IRQ_CAUSE);

	/* clear pending irq events */
	hc_irq_cause = ~((DEV_IRQ | DMA_IRQ) << hardport);
	ग_लिखोlfl(hc_irq_cause, hc_mmio + HC_IRQ_CAUSE);

	/* clear FIS IRQ Cause */
	अगर (IS_GEN_IIE(hpriv))
		ग_लिखोlfl(0, port_mmio + FIS_IRQ_CAUSE);

	mv_enable_port_irqs(ap, port_irqs);
पूर्ण

अटल व्योम mv_set_irq_coalescing(काष्ठा ata_host *host,
				  अचिन्हित पूर्णांक count, अचिन्हित पूर्णांक usecs)
अणु
	काष्ठा mv_host_priv *hpriv = host->निजी_data;
	व्योम __iomem *mmio = hpriv->base, *hc_mmio;
	u32 coal_enable = 0;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक clks, is_dual_hc = hpriv->n_ports > MV_PORTS_PER_HC;
	स्थिर u32 coal_disable = PORTS_0_3_COAL_DONE | PORTS_4_7_COAL_DONE |
							ALL_PORTS_COAL_DONE;

	/* Disable IRQ coalescing अगर either threshold is zero */
	अगर (!usecs || !count) अणु
		clks = count = 0;
	पूर्ण अन्यथा अणु
		/* Respect maximum limits of the hardware */
		clks = usecs * COAL_CLOCKS_PER_USEC;
		अगर (clks > MAX_COAL_TIME_THRESHOLD)
			clks = MAX_COAL_TIME_THRESHOLD;
		अगर (count > MAX_COAL_IO_COUNT)
			count = MAX_COAL_IO_COUNT;
	पूर्ण

	spin_lock_irqsave(&host->lock, flags);
	mv_set_मुख्य_irq_mask(host, coal_disable, 0);

	अगर (is_dual_hc && !IS_GEN_I(hpriv)) अणु
		/*
		 * GEN_II/GEN_IIE with dual host controllers:
		 * one set of global thresholds क्रम the entire chip.
		 */
		ग_लिखोl(clks,  mmio + IRQ_COAL_TIME_THRESHOLD);
		ग_लिखोl(count, mmio + IRQ_COAL_IO_THRESHOLD);
		/* clear leftover coal IRQ bit */
		ग_लिखोl(~ALL_PORTS_COAL_IRQ, mmio + IRQ_COAL_CAUSE);
		अगर (count)
			coal_enable = ALL_PORTS_COAL_DONE;
		clks = count = 0; /* क्रमce clearing of regular regs below */
	पूर्ण

	/*
	 * All chips: independent thresholds क्रम each HC on the chip.
	 */
	hc_mmio = mv_hc_base_from_port(mmio, 0);
	ग_लिखोl(clks,  hc_mmio + HC_IRQ_COAL_TIME_THRESHOLD);
	ग_लिखोl(count, hc_mmio + HC_IRQ_COAL_IO_THRESHOLD);
	ग_लिखोl(~HC_COAL_IRQ, hc_mmio + HC_IRQ_CAUSE);
	अगर (count)
		coal_enable |= PORTS_0_3_COAL_DONE;
	अगर (is_dual_hc) अणु
		hc_mmio = mv_hc_base_from_port(mmio, MV_PORTS_PER_HC);
		ग_लिखोl(clks,  hc_mmio + HC_IRQ_COAL_TIME_THRESHOLD);
		ग_लिखोl(count, hc_mmio + HC_IRQ_COAL_IO_THRESHOLD);
		ग_लिखोl(~HC_COAL_IRQ, hc_mmio + HC_IRQ_CAUSE);
		अगर (count)
			coal_enable |= PORTS_4_7_COAL_DONE;
	पूर्ण

	mv_set_मुख्य_irq_mask(host, 0, coal_enable);
	spin_unlock_irqrestore(&host->lock, flags);
पूर्ण

/*
 *      mv_start_edma - Enable eDMA engine
 *      @pp: port निजी data
 *
 *      Verअगरy the local cache of the eDMA state is accurate with a
 *      WARN_ON.
 *
 *      LOCKING:
 *      Inherited from caller.
 */
अटल व्योम mv_start_edma(काष्ठा ata_port *ap, व्योम __iomem *port_mmio,
			 काष्ठा mv_port_priv *pp, u8 protocol)
अणु
	पूर्णांक want_ncq = (protocol == ATA_PROT_NCQ);

	अगर (pp->pp_flags & MV_PP_FLAG_EDMA_EN) अणु
		पूर्णांक using_ncq = ((pp->pp_flags & MV_PP_FLAG_NCQ_EN) != 0);
		अगर (want_ncq != using_ncq)
			mv_stop_edma(ap);
	पूर्ण
	अगर (!(pp->pp_flags & MV_PP_FLAG_EDMA_EN)) अणु
		काष्ठा mv_host_priv *hpriv = ap->host->निजी_data;

		mv_edma_cfg(ap, want_ncq, 1);

		mv_set_edma_ptrs(port_mmio, hpriv, pp);
		mv_clear_and_enable_port_irqs(ap, port_mmio, DONE_IRQ|ERR_IRQ);

		ग_लिखोlfl(EDMA_EN, port_mmio + EDMA_CMD);
		pp->pp_flags |= MV_PP_FLAG_EDMA_EN;
	पूर्ण
पूर्ण

अटल व्योम mv_रुको_क्रम_edma_empty_idle(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *port_mmio = mv_ap_base(ap);
	स्थिर u32 empty_idle = (EDMA_STATUS_CACHE_EMPTY | EDMA_STATUS_IDLE);
	स्थिर पूर्णांक per_loop = 5, समयout = (15 * 1000 / per_loop);
	पूर्णांक i;

	/*
	 * Wait क्रम the EDMA engine to finish transactions in progress.
	 * No idea what a good "timeout" value might be, but measurements
	 * indicate that it often requires hundreds of microseconds
	 * with two drives in-use.  So we use the 15msec value above
	 * as a rough guess at what even more drives might require.
	 */
	क्रम (i = 0; i < समयout; ++i) अणु
		u32 edma_stat = पढ़ोl(port_mmio + EDMA_STATUS);
		अगर ((edma_stat & empty_idle) == empty_idle)
			अवरोध;
		udelay(per_loop);
	पूर्ण
	/* ata_port_info(ap, "%s: %u+ usecs\n", __func__, i); */
पूर्ण

/**
 *      mv_stop_edma_engine - Disable eDMA engine
 *      @port_mmio: io base address
 *
 *      LOCKING:
 *      Inherited from caller.
 */
अटल पूर्णांक mv_stop_edma_engine(व्योम __iomem *port_mmio)
अणु
	पूर्णांक i;

	/* Disable eDMA.  The disable bit स्वतः clears. */
	ग_लिखोlfl(EDMA_DS, port_mmio + EDMA_CMD);

	/* Wait क्रम the chip to confirm eDMA is off. */
	क्रम (i = 10000; i > 0; i--) अणु
		u32 reg = पढ़ोl(port_mmio + EDMA_CMD);
		अगर (!(reg & EDMA_EN))
			वापस 0;
		udelay(10);
	पूर्ण
	वापस -EIO;
पूर्ण

अटल पूर्णांक mv_stop_edma(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *port_mmio = mv_ap_base(ap);
	काष्ठा mv_port_priv *pp = ap->निजी_data;
	पूर्णांक err = 0;

	अगर (!(pp->pp_flags & MV_PP_FLAG_EDMA_EN))
		वापस 0;
	pp->pp_flags &= ~MV_PP_FLAG_EDMA_EN;
	mv_रुको_क्रम_edma_empty_idle(ap);
	अगर (mv_stop_edma_engine(port_mmio)) अणु
		ata_port_err(ap, "Unable to stop eDMA\n");
		err = -EIO;
	पूर्ण
	mv_edma_cfg(ap, 0, 0);
	वापस err;
पूर्ण

#अगर_घोषित ATA_DEBUG
अटल व्योम mv_dump_mem(व्योम __iomem *start, अचिन्हित bytes)
अणु
	पूर्णांक b, w;
	क्रम (b = 0; b < bytes; ) अणु
		DPRINTK("%p: ", start + b);
		क्रम (w = 0; b < bytes && w < 4; w++) अणु
			prपूर्णांकk("%08x ", पढ़ोl(start + b));
			b += माप(u32);
		पूर्ण
		prपूर्णांकk("\n");
	पूर्ण
पूर्ण
#पूर्ण_अगर
#अगर defined(ATA_DEBUG) || defined(CONFIG_PCI)
अटल व्योम mv_dump_pci_cfg(काष्ठा pci_dev *pdev, अचिन्हित bytes)
अणु
#अगर_घोषित ATA_DEBUG
	पूर्णांक b, w;
	u32 dw;
	क्रम (b = 0; b < bytes; ) अणु
		DPRINTK("%02x: ", b);
		क्रम (w = 0; b < bytes && w < 4; w++) अणु
			(व्योम) pci_पढ़ो_config_dword(pdev, b, &dw);
			prपूर्णांकk("%08x ", dw);
			b += माप(u32);
		पूर्ण
		prपूर्णांकk("\n");
	पूर्ण
#पूर्ण_अगर
पूर्ण
#पूर्ण_अगर
अटल व्योम mv_dump_all_regs(व्योम __iomem *mmio_base, पूर्णांक port,
			     काष्ठा pci_dev *pdev)
अणु
#अगर_घोषित ATA_DEBUG
	व्योम __iomem *hc_base = mv_hc_base(mmio_base,
					   port >> MV_PORT_HC_SHIFT);
	व्योम __iomem *port_base;
	पूर्णांक start_port, num_ports, p, start_hc, num_hcs, hc;

	अगर (0 > port) अणु
		start_hc = start_port = 0;
		num_ports = 8;		/* shld be benign क्रम 4 port devs */
		num_hcs = 2;
	पूर्ण अन्यथा अणु
		start_hc = port >> MV_PORT_HC_SHIFT;
		start_port = port;
		num_ports = num_hcs = 1;
	पूर्ण
	DPRINTK("All registers for port(s) %u-%u:\n", start_port,
		num_ports > 1 ? num_ports - 1 : start_port);

	अगर (शून्य != pdev) अणु
		DPRINTK("PCI config space regs:\n");
		mv_dump_pci_cfg(pdev, 0x68);
	पूर्ण
	DPRINTK("PCI regs:\n");
	mv_dump_mem(mmio_base+0xc00, 0x3c);
	mv_dump_mem(mmio_base+0xd00, 0x34);
	mv_dump_mem(mmio_base+0xf00, 0x4);
	mv_dump_mem(mmio_base+0x1d00, 0x6c);
	क्रम (hc = start_hc; hc < start_hc + num_hcs; hc++) अणु
		hc_base = mv_hc_base(mmio_base, hc);
		DPRINTK("HC regs (HC %i):\n", hc);
		mv_dump_mem(hc_base, 0x1c);
	पूर्ण
	क्रम (p = start_port; p < start_port + num_ports; p++) अणु
		port_base = mv_port_base(mmio_base, p);
		DPRINTK("EDMA regs (port %i):\n", p);
		mv_dump_mem(port_base, 0x54);
		DPRINTK("SATA regs (port %i):\n", p);
		mv_dump_mem(port_base+0x300, 0x60);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल अचिन्हित पूर्णांक mv_scr_offset(अचिन्हित पूर्णांक sc_reg_in)
अणु
	अचिन्हित पूर्णांक ofs;

	चयन (sc_reg_in) अणु
	हाल SCR_STATUS:
	हाल SCR_CONTROL:
	हाल SCR_ERROR:
		ofs = SATA_STATUS + (sc_reg_in * माप(u32));
		अवरोध;
	हाल SCR_ACTIVE:
		ofs = SATA_ACTIVE;   /* active is not with the others */
		अवरोध;
	शेष:
		ofs = 0xffffffffU;
		अवरोध;
	पूर्ण
	वापस ofs;
पूर्ण

अटल पूर्णांक mv_scr_पढ़ो(काष्ठा ata_link *link, अचिन्हित पूर्णांक sc_reg_in, u32 *val)
अणु
	अचिन्हित पूर्णांक ofs = mv_scr_offset(sc_reg_in);

	अगर (ofs != 0xffffffffU) अणु
		*val = पढ़ोl(mv_ap_base(link->ap) + ofs);
		वापस 0;
	पूर्ण अन्यथा
		वापस -EINVAL;
पूर्ण

अटल पूर्णांक mv_scr_ग_लिखो(काष्ठा ata_link *link, अचिन्हित पूर्णांक sc_reg_in, u32 val)
अणु
	अचिन्हित पूर्णांक ofs = mv_scr_offset(sc_reg_in);

	अगर (ofs != 0xffffffffU) अणु
		व्योम __iomem *addr = mv_ap_base(link->ap) + ofs;
		काष्ठा mv_host_priv *hpriv = link->ap->host->निजी_data;
		अगर (sc_reg_in == SCR_CONTROL) अणु
			/*
			 * Workaround क्रम 88SX60x1 FEr SATA#26:
			 *
			 * COMRESETs have to take care not to accidentally
			 * put the drive to sleep when writing SCR_CONTROL.
			 * Setting bits 12..15 prevents this problem.
			 *
			 * So अगर we see an outbound COMMRESET, set those bits.
			 * Ditto क्रम the followup ग_लिखो that clears the reset.
			 *
			 * The proprietary driver करोes this क्रम
			 * all chip versions, and so करो we.
			 */
			अगर ((val & 0xf) == 1 || (पढ़ोl(addr) & 0xf) == 1)
				val |= 0xf000;

			अगर (hpriv->hp_flags & MV_HP_FIX_LP_PHY_CTL) अणु
				व्योम __iomem *lp_phy_addr =
					mv_ap_base(link->ap) + LP_PHY_CTL;
				/*
				 * Set PHY speed according to SControl speed.
				 */
				u32 lp_phy_val =
					LP_PHY_CTL_PIN_PU_PLL |
					LP_PHY_CTL_PIN_PU_RX  |
					LP_PHY_CTL_PIN_PU_TX;

				अगर ((val & 0xf0) != 0x10)
					lp_phy_val |=
						LP_PHY_CTL_GEN_TX_3G |
						LP_PHY_CTL_GEN_RX_3G;

				ग_लिखोlfl(lp_phy_val, lp_phy_addr);
			पूर्ण
		पूर्ण
		ग_लिखोlfl(val, addr);
		वापस 0;
	पूर्ण अन्यथा
		वापस -EINVAL;
पूर्ण

अटल व्योम mv6_dev_config(काष्ठा ata_device *adev)
अणु
	/*
	 * Deal with Gen-II ("mv6") hardware quirks/restrictions:
	 *
	 * Gen-II करोes not support NCQ over a port multiplier
	 *  (no FIS-based चयनing).
	 */
	अगर (adev->flags & ATA_DFLAG_NCQ) अणु
		अगर (sata_pmp_attached(adev->link->ap)) अणु
			adev->flags &= ~ATA_DFLAG_NCQ;
			ata_dev_info(adev,
				"NCQ disabled for command-based switching\n");
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक mv_qc_defer(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_link *link = qc->dev->link;
	काष्ठा ata_port *ap = link->ap;
	काष्ठा mv_port_priv *pp = ap->निजी_data;

	/*
	 * Don't allow new commands if we're in a delayed EH state
	 * क्रम NCQ and/or FIS-based चयनing.
	 */
	अगर (pp->pp_flags & MV_PP_FLAG_DELAYED_EH)
		वापस ATA_DEFER_PORT;

	/* PIO commands need exclusive link: no other commands [DMA or PIO]
	 * can run concurrently.
	 * set excl_link when we want to send a PIO command in DMA mode
	 * or a non-NCQ command in NCQ mode.
	 * When we receive a command from that link, and there are no
	 * outstanding commands, mark a flag to clear excl_link and let
	 * the command go through.
	 */
	अगर (unlikely(ap->excl_link)) अणु
		अगर (link == ap->excl_link) अणु
			अगर (ap->nr_active_links)
				वापस ATA_DEFER_PORT;
			qc->flags |= ATA_QCFLAG_CLEAR_EXCL;
			वापस 0;
		पूर्ण अन्यथा
			वापस ATA_DEFER_PORT;
	पूर्ण

	/*
	 * If the port is completely idle, then allow the new qc.
	 */
	अगर (ap->nr_active_links == 0)
		वापस 0;

	/*
	 * The port is operating in host queuing mode (EDMA) with NCQ
	 * enabled, allow multiple NCQ commands.  EDMA also allows
	 * queueing multiple DMA commands but libata core currently
	 * करोesn't allow it.
	 */
	अगर ((pp->pp_flags & MV_PP_FLAG_EDMA_EN) &&
	    (pp->pp_flags & MV_PP_FLAG_NCQ_EN)) अणु
		अगर (ata_is_ncq(qc->tf.protocol))
			वापस 0;
		अन्यथा अणु
			ap->excl_link = link;
			वापस ATA_DEFER_PORT;
		पूर्ण
	पूर्ण

	वापस ATA_DEFER_PORT;
पूर्ण

अटल व्योम mv_config_fbs(काष्ठा ata_port *ap, पूर्णांक want_ncq, पूर्णांक want_fbs)
अणु
	काष्ठा mv_port_priv *pp = ap->निजी_data;
	व्योम __iomem *port_mmio;

	u32 fiscfg,   *old_fiscfg   = &pp->cached.fiscfg;
	u32 lपंचांगode,   *old_lपंचांगode   = &pp->cached.lपंचांगode;
	u32 haltcond, *old_haltcond = &pp->cached.haltcond;

	lपंचांगode   = *old_lपंचांगode & ~LTMODE_BIT8;
	haltcond = *old_haltcond | EDMA_ERR_DEV;

	अगर (want_fbs) अणु
		fiscfg = *old_fiscfg | FISCFG_SINGLE_SYNC;
		lपंचांगode = *old_lपंचांगode | LTMODE_BIT8;
		अगर (want_ncq)
			haltcond &= ~EDMA_ERR_DEV;
		अन्यथा
			fiscfg |=  FISCFG_WAIT_DEV_ERR;
	पूर्ण अन्यथा अणु
		fiscfg = *old_fiscfg & ~(FISCFG_SINGLE_SYNC | FISCFG_WAIT_DEV_ERR);
	पूर्ण

	port_mmio = mv_ap_base(ap);
	mv_ग_लिखो_cached_reg(port_mmio + FISCFG, old_fiscfg, fiscfg);
	mv_ग_लिखो_cached_reg(port_mmio + LTMODE, old_lपंचांगode, lपंचांगode);
	mv_ग_लिखो_cached_reg(port_mmio + EDMA_HALTCOND, old_haltcond, haltcond);
पूर्ण

अटल व्योम mv_60x1_errata_sata25(काष्ठा ata_port *ap, पूर्णांक want_ncq)
अणु
	काष्ठा mv_host_priv *hpriv = ap->host->निजी_data;
	u32 old, new;

	/* workaround क्रम 88SX60x1 FEr SATA#25 (part 1) */
	old = पढ़ोl(hpriv->base + GPIO_PORT_CTL);
	अगर (want_ncq)
		new = old | (1 << 22);
	अन्यथा
		new = old & ~(1 << 22);
	अगर (new != old)
		ग_लिखोl(new, hpriv->base + GPIO_PORT_CTL);
पूर्ण

/*
 *	mv_bmdma_enable - set a magic bit on GEN_IIE to allow bmdma
 *	@ap: Port being initialized
 *
 *	There are two DMA modes on these chips:  basic DMA, and EDMA.
 *
 *	Bit-0 of the "EDMA RESERVED" रेजिस्टर enables/disables use
 *	of basic DMA on the GEN_IIE versions of the chips.
 *
 *	This bit survives EDMA resets, and must be set क्रम basic DMA
 *	to function, and should be cleared when EDMA is active.
 */
अटल व्योम mv_bmdma_enable_iie(काष्ठा ata_port *ap, पूर्णांक enable_bmdma)
अणु
	काष्ठा mv_port_priv *pp = ap->निजी_data;
	u32 new, *old = &pp->cached.unknown_rsvd;

	अगर (enable_bmdma)
		new = *old | 1;
	अन्यथा
		new = *old & ~1;
	mv_ग_लिखो_cached_reg(mv_ap_base(ap) + EDMA_UNKNOWN_RSVD, old, new);
पूर्ण

/*
 * SOC chips have an issue whereby the HDD LEDs करोn't always blink
 * during I/O when NCQ is enabled. Enabling a special "LED blink" mode
 * of the SOC takes care of it, generating a steady blink rate when
 * any drive on the chip is active.
 *
 * Unक्रमtunately, the blink mode is a global hardware setting क्रम the SOC,
 * so we must use it whenever at least one port on the SOC has NCQ enabled.
 *
 * We turn "LED blink" off when NCQ is not in use anywhere, because the normal
 * LED operation works then, and provides better (more accurate) feedback.
 *
 * Note that this code assumes that an SOC never has more than one HC onboard.
 */
अटल व्योम mv_soc_led_blink_enable(काष्ठा ata_port *ap)
अणु
	काष्ठा ata_host *host = ap->host;
	काष्ठा mv_host_priv *hpriv = host->निजी_data;
	व्योम __iomem *hc_mmio;
	u32 led_ctrl;

	अगर (hpriv->hp_flags & MV_HP_QUIRK_LED_BLINK_EN)
		वापस;
	hpriv->hp_flags |= MV_HP_QUIRK_LED_BLINK_EN;
	hc_mmio = mv_hc_base_from_port(mv_host_base(host), ap->port_no);
	led_ctrl = पढ़ोl(hc_mmio + SOC_LED_CTRL);
	ग_लिखोl(led_ctrl | SOC_LED_CTRL_BLINK, hc_mmio + SOC_LED_CTRL);
पूर्ण

अटल व्योम mv_soc_led_blink_disable(काष्ठा ata_port *ap)
अणु
	काष्ठा ata_host *host = ap->host;
	काष्ठा mv_host_priv *hpriv = host->निजी_data;
	व्योम __iomem *hc_mmio;
	u32 led_ctrl;
	अचिन्हित पूर्णांक port;

	अगर (!(hpriv->hp_flags & MV_HP_QUIRK_LED_BLINK_EN))
		वापस;

	/* disable led-blink only अगर no ports are using NCQ */
	क्रम (port = 0; port < hpriv->n_ports; port++) अणु
		काष्ठा ata_port *this_ap = host->ports[port];
		काष्ठा mv_port_priv *pp = this_ap->निजी_data;

		अगर (pp->pp_flags & MV_PP_FLAG_NCQ_EN)
			वापस;
	पूर्ण

	hpriv->hp_flags &= ~MV_HP_QUIRK_LED_BLINK_EN;
	hc_mmio = mv_hc_base_from_port(mv_host_base(host), ap->port_no);
	led_ctrl = पढ़ोl(hc_mmio + SOC_LED_CTRL);
	ग_लिखोl(led_ctrl & ~SOC_LED_CTRL_BLINK, hc_mmio + SOC_LED_CTRL);
पूर्ण

अटल व्योम mv_edma_cfg(काष्ठा ata_port *ap, पूर्णांक want_ncq, पूर्णांक want_edma)
अणु
	u32 cfg;
	काष्ठा mv_port_priv *pp    = ap->निजी_data;
	काष्ठा mv_host_priv *hpriv = ap->host->निजी_data;
	व्योम __iomem *port_mmio    = mv_ap_base(ap);

	/* set up non-NCQ EDMA configuration */
	cfg = EDMA_CFG_Q_DEPTH;		/* always 0x1f क्रम *all* chips */
	pp->pp_flags &=
	  ~(MV_PP_FLAG_FBS_EN | MV_PP_FLAG_NCQ_EN | MV_PP_FLAG_FAKE_ATA_BUSY);

	अगर (IS_GEN_I(hpriv))
		cfg |= (1 << 8);	/* enab config burst size mask */

	अन्यथा अगर (IS_GEN_II(hpriv)) अणु
		cfg |= EDMA_CFG_RD_BRST_EXT | EDMA_CFG_WR_BUFF_LEN;
		mv_60x1_errata_sata25(ap, want_ncq);

	पूर्ण अन्यथा अगर (IS_GEN_IIE(hpriv)) अणु
		पूर्णांक want_fbs = sata_pmp_attached(ap);
		/*
		 * Possible future enhancement:
		 *
		 * The chip can use FBS with non-NCQ, अगर we allow it,
		 * But first we need to have the error handling in place
		 * क्रम this mode (datasheet section 7.3.15.4.2.3).
		 * So disallow non-NCQ FBS क्रम now.
		 */
		want_fbs &= want_ncq;

		mv_config_fbs(ap, want_ncq, want_fbs);

		अगर (want_fbs) अणु
			pp->pp_flags |= MV_PP_FLAG_FBS_EN;
			cfg |= EDMA_CFG_EDMA_FBS; /* FIS-based चयनing */
		पूर्ण

		cfg |= (1 << 23);	/* करो not mask PM field in rx'd FIS */
		अगर (want_edma) अणु
			cfg |= (1 << 22); /* enab 4-entry host queue cache */
			अगर (!IS_SOC(hpriv))
				cfg |= (1 << 18); /* enab early completion */
		पूर्ण
		अगर (hpriv->hp_flags & MV_HP_CUT_THROUGH)
			cfg |= (1 << 17); /* enab cut-thru (dis stor&क्रमwrd) */
		mv_bmdma_enable_iie(ap, !want_edma);

		अगर (IS_SOC(hpriv)) अणु
			अगर (want_ncq)
				mv_soc_led_blink_enable(ap);
			अन्यथा
				mv_soc_led_blink_disable(ap);
		पूर्ण
	पूर्ण

	अगर (want_ncq) अणु
		cfg |= EDMA_CFG_NCQ;
		pp->pp_flags |=  MV_PP_FLAG_NCQ_EN;
	पूर्ण

	ग_लिखोlfl(cfg, port_mmio + EDMA_CFG);
पूर्ण

अटल व्योम mv_port_मुक्त_dma_mem(काष्ठा ata_port *ap)
अणु
	काष्ठा mv_host_priv *hpriv = ap->host->निजी_data;
	काष्ठा mv_port_priv *pp = ap->निजी_data;
	पूर्णांक tag;

	अगर (pp->crqb) अणु
		dma_pool_मुक्त(hpriv->crqb_pool, pp->crqb, pp->crqb_dma);
		pp->crqb = शून्य;
	पूर्ण
	अगर (pp->crpb) अणु
		dma_pool_मुक्त(hpriv->crpb_pool, pp->crpb, pp->crpb_dma);
		pp->crpb = शून्य;
	पूर्ण
	/*
	 * For GEN_I, there's no NCQ, so we have only a single sg_tbl.
	 * For later hardware, we have one unique sg_tbl per NCQ tag.
	 */
	क्रम (tag = 0; tag < MV_MAX_Q_DEPTH; ++tag) अणु
		अगर (pp->sg_tbl[tag]) अणु
			अगर (tag == 0 || !IS_GEN_I(hpriv))
				dma_pool_मुक्त(hpriv->sg_tbl_pool,
					      pp->sg_tbl[tag],
					      pp->sg_tbl_dma[tag]);
			pp->sg_tbl[tag] = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

/**
 *      mv_port_start - Port specअगरic init/start routine.
 *      @ap: ATA channel to manipulate
 *
 *      Allocate and poपूर्णांक to DMA memory, init port निजी memory,
 *      zero indices.
 *
 *      LOCKING:
 *      Inherited from caller.
 */
अटल पूर्णांक mv_port_start(काष्ठा ata_port *ap)
अणु
	काष्ठा device *dev = ap->host->dev;
	काष्ठा mv_host_priv *hpriv = ap->host->निजी_data;
	काष्ठा mv_port_priv *pp;
	अचिन्हित दीर्घ flags;
	पूर्णांक tag;

	pp = devm_kzalloc(dev, माप(*pp), GFP_KERNEL);
	अगर (!pp)
		वापस -ENOMEM;
	ap->निजी_data = pp;

	pp->crqb = dma_pool_zalloc(hpriv->crqb_pool, GFP_KERNEL, &pp->crqb_dma);
	अगर (!pp->crqb)
		वापस -ENOMEM;

	pp->crpb = dma_pool_zalloc(hpriv->crpb_pool, GFP_KERNEL, &pp->crpb_dma);
	अगर (!pp->crpb)
		जाओ out_port_मुक्त_dma_mem;

	/* 6041/6081 Rev. "C0" (and newer) are okay with async notअगरy */
	अगर (hpriv->hp_flags & MV_HP_ERRATA_60X1C0)
		ap->flags |= ATA_FLAG_AN;
	/*
	 * For GEN_I, there's no NCQ, so we only allocate a single sg_tbl.
	 * For later hardware, we need one unique sg_tbl per NCQ tag.
	 */
	क्रम (tag = 0; tag < MV_MAX_Q_DEPTH; ++tag) अणु
		अगर (tag == 0 || !IS_GEN_I(hpriv)) अणु
			pp->sg_tbl[tag] = dma_pool_alloc(hpriv->sg_tbl_pool,
					      GFP_KERNEL, &pp->sg_tbl_dma[tag]);
			अगर (!pp->sg_tbl[tag])
				जाओ out_port_मुक्त_dma_mem;
		पूर्ण अन्यथा अणु
			pp->sg_tbl[tag]     = pp->sg_tbl[0];
			pp->sg_tbl_dma[tag] = pp->sg_tbl_dma[0];
		पूर्ण
	पूर्ण

	spin_lock_irqsave(ap->lock, flags);
	mv_save_cached_regs(ap);
	mv_edma_cfg(ap, 0, 0);
	spin_unlock_irqrestore(ap->lock, flags);

	वापस 0;

out_port_मुक्त_dma_mem:
	mv_port_मुक्त_dma_mem(ap);
	वापस -ENOMEM;
पूर्ण

/**
 *      mv_port_stop - Port specअगरic cleanup/stop routine.
 *      @ap: ATA channel to manipulate
 *
 *      Stop DMA, cleanup port memory.
 *
 *      LOCKING:
 *      This routine uses the host lock to protect the DMA stop.
 */
अटल व्योम mv_port_stop(काष्ठा ata_port *ap)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(ap->lock, flags);
	mv_stop_edma(ap);
	mv_enable_port_irqs(ap, 0);
	spin_unlock_irqrestore(ap->lock, flags);
	mv_port_मुक्त_dma_mem(ap);
पूर्ण

/**
 *      mv_fill_sg - Fill out the Marvell ePRD (scatter gather) entries
 *      @qc: queued command whose SG list to source from
 *
 *      Populate the SG list and mark the last entry.
 *
 *      LOCKING:
 *      Inherited from caller.
 */
अटल व्योम mv_fill_sg(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा mv_port_priv *pp = qc->ap->निजी_data;
	काष्ठा scatterlist *sg;
	काष्ठा mv_sg *mv_sg, *last_sg = शून्य;
	अचिन्हित पूर्णांक si;

	mv_sg = pp->sg_tbl[qc->hw_tag];
	क्रम_each_sg(qc->sg, sg, qc->n_elem, si) अणु
		dma_addr_t addr = sg_dma_address(sg);
		u32 sg_len = sg_dma_len(sg);

		जबतक (sg_len) अणु
			u32 offset = addr & 0xffff;
			u32 len = sg_len;

			अगर (offset + len > 0x10000)
				len = 0x10000 - offset;

			mv_sg->addr = cpu_to_le32(addr & 0xffffffff);
			mv_sg->addr_hi = cpu_to_le32((addr >> 16) >> 16);
			mv_sg->flags_size = cpu_to_le32(len & 0xffff);
			mv_sg->reserved = 0;

			sg_len -= len;
			addr += len;

			last_sg = mv_sg;
			mv_sg++;
		पूर्ण
	पूर्ण

	अगर (likely(last_sg))
		last_sg->flags_size |= cpu_to_le32(EPRD_FLAG_END_OF_TBL);
	mb(); /* ensure data काष्ठाure is visible to the chipset */
पूर्ण

अटल व्योम mv_crqb_pack_cmd(__le16 *cmdw, u8 data, u8 addr, अचिन्हित last)
अणु
	u16 पंचांगp = data | (addr << CRQB_CMD_ADDR_SHIFT) | CRQB_CMD_CS |
		(last ? CRQB_CMD_LAST : 0);
	*cmdw = cpu_to_le16(पंचांगp);
पूर्ण

/**
 *	mv_sff_irq_clear - Clear hardware पूर्णांकerrupt after DMA.
 *	@ap: Port associated with this ATA transaction.
 *
 *	We need this only क्रम ATAPI bmdma transactions,
 *	as otherwise we experience spurious पूर्णांकerrupts
 *	after libata-sff handles the bmdma पूर्णांकerrupts.
 */
अटल व्योम mv_sff_irq_clear(काष्ठा ata_port *ap)
अणु
	mv_clear_and_enable_port_irqs(ap, mv_ap_base(ap), ERR_IRQ);
पूर्ण

/**
 *	mv_check_atapi_dma - Filter ATAPI cmds which are unsuitable क्रम DMA.
 *	@qc: queued command to check क्रम chipset/DMA compatibility.
 *
 *	The bmdma engines cannot handle speculative data sizes
 *	(bytecount under/over flow).  So only allow DMA क्रम
 *	data transfer commands with known data sizes.
 *
 *	LOCKING:
 *	Inherited from caller.
 */
अटल पूर्णांक mv_check_atapi_dma(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा scsi_cmnd *scmd = qc->scsicmd;

	अगर (scmd) अणु
		चयन (scmd->cmnd[0]) अणु
		हाल READ_6:
		हाल READ_10:
		हाल READ_12:
		हाल WRITE_6:
		हाल WRITE_10:
		हाल WRITE_12:
		हाल GPCMD_READ_CD:
		हाल GPCMD_SEND_DVD_STRUCTURE:
		हाल GPCMD_SEND_CUE_SHEET:
			वापस 0; /* DMA is safe */
		पूर्ण
	पूर्ण
	वापस -EOPNOTSUPP; /* use PIO instead */
पूर्ण

/**
 *	mv_bmdma_setup - Set up BMDMA transaction
 *	@qc: queued command to prepare DMA क्रम.
 *
 *	LOCKING:
 *	Inherited from caller.
 */
अटल व्योम mv_bmdma_setup(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	व्योम __iomem *port_mmio = mv_ap_base(ap);
	काष्ठा mv_port_priv *pp = ap->निजी_data;

	mv_fill_sg(qc);

	/* clear all DMA cmd bits */
	ग_लिखोl(0, port_mmio + BMDMA_CMD);

	/* load PRD table addr. */
	ग_लिखोl((pp->sg_tbl_dma[qc->hw_tag] >> 16) >> 16,
		port_mmio + BMDMA_PRD_HIGH);
	ग_लिखोlfl(pp->sg_tbl_dma[qc->hw_tag],
		port_mmio + BMDMA_PRD_LOW);

	/* issue r/w command */
	ap->ops->sff_exec_command(ap, &qc->tf);
पूर्ण

/**
 *	mv_bmdma_start - Start a BMDMA transaction
 *	@qc: queued command to start DMA on.
 *
 *	LOCKING:
 *	Inherited from caller.
 */
अटल व्योम mv_bmdma_start(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	व्योम __iomem *port_mmio = mv_ap_base(ap);
	अचिन्हित पूर्णांक rw = (qc->tf.flags & ATA_TFLAG_WRITE);
	u32 cmd = (rw ? 0 : ATA_DMA_WR) | ATA_DMA_START;

	/* start host DMA transaction */
	ग_लिखोlfl(cmd, port_mmio + BMDMA_CMD);
पूर्ण

/**
 *	mv_bmdma_stop_ap - Stop BMDMA transfer
 *	@ap: port to stop
 *
 *	Clears the ATA_DMA_START flag in the bmdma control रेजिस्टर
 *
 *	LOCKING:
 *	Inherited from caller.
 */
अटल व्योम mv_bmdma_stop_ap(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *port_mmio = mv_ap_base(ap);
	u32 cmd;

	/* clear start/stop bit */
	cmd = पढ़ोl(port_mmio + BMDMA_CMD);
	अगर (cmd & ATA_DMA_START) अणु
		cmd &= ~ATA_DMA_START;
		ग_लिखोlfl(cmd, port_mmio + BMDMA_CMD);

		/* one-PIO-cycle guaranteed रुको, per spec, क्रम HDMA1:0 transition */
		ata_sff_dma_छोड़ो(ap);
	पूर्ण
पूर्ण

अटल व्योम mv_bmdma_stop(काष्ठा ata_queued_cmd *qc)
अणु
	mv_bmdma_stop_ap(qc->ap);
पूर्ण

/**
 *	mv_bmdma_status - Read BMDMA status
 *	@ap: port क्रम which to retrieve DMA status.
 *
 *	Read and वापस equivalent of the sff BMDMA status रेजिस्टर.
 *
 *	LOCKING:
 *	Inherited from caller.
 */
अटल u8 mv_bmdma_status(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *port_mmio = mv_ap_base(ap);
	u32 reg, status;

	/*
	 * Other bits are valid only अगर ATA_DMA_ACTIVE==0,
	 * and the ATA_DMA_INTR bit करोesn't exist.
	 */
	reg = पढ़ोl(port_mmio + BMDMA_STATUS);
	अगर (reg & ATA_DMA_ACTIVE)
		status = ATA_DMA_ACTIVE;
	अन्यथा अगर (reg & ATA_DMA_ERR)
		status = (reg & ATA_DMA_ERR) | ATA_DMA_INTR;
	अन्यथा अणु
		/*
		 * Just because DMA_ACTIVE is 0 (DMA completed),
		 * this करोes _not_ mean the device is "done".
		 * So we should not yet be संकेतling ATA_DMA_INTR
		 * in some हालs.  Eg. DSM/TRIM, and perhaps others.
		 */
		mv_bmdma_stop_ap(ap);
		अगर (ioपढ़ो8(ap->ioaddr.altstatus_addr) & ATA_BUSY)
			status = 0;
		अन्यथा
			status = ATA_DMA_INTR;
	पूर्ण
	वापस status;
पूर्ण

अटल व्योम mv_rw_multi_errata_sata24(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_taskfile *tf = &qc->tf;
	/*
	 * Workaround क्रम 88SX60x1 FEr SATA#24.
	 *
	 * Chip may corrupt WRITEs अगर multi_count >= 4kB.
	 * Note that READs are unaffected.
	 *
	 * It's not clear अगर this errata really means "4K bytes",
	 * or अगर it always happens क्रम multi_count > 7
	 * regardless of device sector_size.
	 *
	 * So, क्रम safety, any ग_लिखो with multi_count > 7
	 * माला_लो converted here पूर्णांकo a regular PIO ग_लिखो instead:
	 */
	अगर ((tf->flags & ATA_TFLAG_WRITE) && is_multi_taskfile(tf)) अणु
		अगर (qc->dev->multi_count > 7) अणु
			चयन (tf->command) अणु
			हाल ATA_CMD_WRITE_MULTI:
				tf->command = ATA_CMD_PIO_WRITE;
				अवरोध;
			हाल ATA_CMD_WRITE_MULTI_FUA_EXT:
				tf->flags &= ~ATA_TFLAG_FUA; /* ugh */
				fallthrough;
			हाल ATA_CMD_WRITE_MULTI_EXT:
				tf->command = ATA_CMD_PIO_WRITE_EXT;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/**
 *      mv_qc_prep - Host specअगरic command preparation.
 *      @qc: queued command to prepare
 *
 *      This routine simply redirects to the general purpose routine
 *      अगर command is not DMA.  Else, it handles prep of the CRQB
 *      (command request block), करोes some sanity checking, and calls
 *      the SG load routine.
 *
 *      LOCKING:
 *      Inherited from caller.
 */
अटल क्रमागत ata_completion_errors mv_qc_prep(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा mv_port_priv *pp = ap->निजी_data;
	__le16 *cw;
	काष्ठा ata_taskfile *tf = &qc->tf;
	u16 flags = 0;
	अचिन्हित in_index;

	चयन (tf->protocol) अणु
	हाल ATA_PROT_DMA:
		अगर (tf->command == ATA_CMD_DSM)
			वापस AC_ERR_OK;
		fallthrough;
	हाल ATA_PROT_NCQ:
		अवरोध;	/* जारी below */
	हाल ATA_PROT_PIO:
		mv_rw_multi_errata_sata24(qc);
		वापस AC_ERR_OK;
	शेष:
		वापस AC_ERR_OK;
	पूर्ण

	/* Fill in command request block
	 */
	अगर (!(tf->flags & ATA_TFLAG_WRITE))
		flags |= CRQB_FLAG_READ;
	WARN_ON(MV_MAX_Q_DEPTH <= qc->hw_tag);
	flags |= qc->hw_tag << CRQB_TAG_SHIFT;
	flags |= (qc->dev->link->pmp & 0xf) << CRQB_PMP_SHIFT;

	/* get current queue index from software */
	in_index = pp->req_idx;

	pp->crqb[in_index].sg_addr =
		cpu_to_le32(pp->sg_tbl_dma[qc->hw_tag] & 0xffffffff);
	pp->crqb[in_index].sg_addr_hi =
		cpu_to_le32((pp->sg_tbl_dma[qc->hw_tag] >> 16) >> 16);
	pp->crqb[in_index].ctrl_flags = cpu_to_le16(flags);

	cw = &pp->crqb[in_index].ata_cmd[0];

	/* Sadly, the CRQB cannot accommodate all रेजिस्टरs--there are
	 * only 11 bytes...so we must pick and choose required
	 * रेजिस्टरs based on the command.  So, we drop feature and
	 * hob_feature क्रम [RW] DMA commands, but they are needed क्रम
	 * NCQ.  NCQ will drop hob_nsect, which is not needed there
	 * (nsect is used only क्रम the tag; feat/hob_feat hold true nsect).
	 */
	चयन (tf->command) अणु
	हाल ATA_CMD_READ:
	हाल ATA_CMD_READ_EXT:
	हाल ATA_CMD_WRITE:
	हाल ATA_CMD_WRITE_EXT:
	हाल ATA_CMD_WRITE_FUA_EXT:
		mv_crqb_pack_cmd(cw++, tf->hob_nsect, ATA_REG_NSECT, 0);
		अवरोध;
	हाल ATA_CMD_FPDMA_READ:
	हाल ATA_CMD_FPDMA_WRITE:
		mv_crqb_pack_cmd(cw++, tf->hob_feature, ATA_REG_FEATURE, 0);
		mv_crqb_pack_cmd(cw++, tf->feature, ATA_REG_FEATURE, 0);
		अवरोध;
	शेष:
		/* The only other commands EDMA supports in non-queued and
		 * non-NCQ mode are: [RW] STREAM DMA and W DMA FUA EXT, none
		 * of which are defined/used by Linux.  If we get here, this
		 * driver needs work.
		 */
		ata_port_err(ap, "%s: unsupported command: %.2x\n", __func__,
				tf->command);
		वापस AC_ERR_INVALID;
	पूर्ण
	mv_crqb_pack_cmd(cw++, tf->nsect, ATA_REG_NSECT, 0);
	mv_crqb_pack_cmd(cw++, tf->hob_lbal, ATA_REG_LBAL, 0);
	mv_crqb_pack_cmd(cw++, tf->lbal, ATA_REG_LBAL, 0);
	mv_crqb_pack_cmd(cw++, tf->hob_lbam, ATA_REG_LBAM, 0);
	mv_crqb_pack_cmd(cw++, tf->lbam, ATA_REG_LBAM, 0);
	mv_crqb_pack_cmd(cw++, tf->hob_lbah, ATA_REG_LBAH, 0);
	mv_crqb_pack_cmd(cw++, tf->lbah, ATA_REG_LBAH, 0);
	mv_crqb_pack_cmd(cw++, tf->device, ATA_REG_DEVICE, 0);
	mv_crqb_pack_cmd(cw++, tf->command, ATA_REG_CMD, 1);	/* last */

	अगर (!(qc->flags & ATA_QCFLAG_DMAMAP))
		वापस AC_ERR_OK;
	mv_fill_sg(qc);

	वापस AC_ERR_OK;
पूर्ण

/**
 *      mv_qc_prep_iie - Host specअगरic command preparation.
 *      @qc: queued command to prepare
 *
 *      This routine simply redirects to the general purpose routine
 *      अगर command is not DMA.  Else, it handles prep of the CRQB
 *      (command request block), करोes some sanity checking, and calls
 *      the SG load routine.
 *
 *      LOCKING:
 *      Inherited from caller.
 */
अटल क्रमागत ata_completion_errors mv_qc_prep_iie(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा mv_port_priv *pp = ap->निजी_data;
	काष्ठा mv_crqb_iie *crqb;
	काष्ठा ata_taskfile *tf = &qc->tf;
	अचिन्हित in_index;
	u32 flags = 0;

	अगर ((tf->protocol != ATA_PROT_DMA) &&
	    (tf->protocol != ATA_PROT_NCQ))
		वापस AC_ERR_OK;
	अगर (tf->command == ATA_CMD_DSM)
		वापस AC_ERR_OK;  /* use bmdma क्रम this */

	/* Fill in Gen IIE command request block */
	अगर (!(tf->flags & ATA_TFLAG_WRITE))
		flags |= CRQB_FLAG_READ;

	WARN_ON(MV_MAX_Q_DEPTH <= qc->hw_tag);
	flags |= qc->hw_tag << CRQB_TAG_SHIFT;
	flags |= qc->hw_tag << CRQB_HOSTQ_SHIFT;
	flags |= (qc->dev->link->pmp & 0xf) << CRQB_PMP_SHIFT;

	/* get current queue index from software */
	in_index = pp->req_idx;

	crqb = (काष्ठा mv_crqb_iie *) &pp->crqb[in_index];
	crqb->addr = cpu_to_le32(pp->sg_tbl_dma[qc->hw_tag] & 0xffffffff);
	crqb->addr_hi = cpu_to_le32((pp->sg_tbl_dma[qc->hw_tag] >> 16) >> 16);
	crqb->flags = cpu_to_le32(flags);

	crqb->ata_cmd[0] = cpu_to_le32(
			(tf->command << 16) |
			(tf->feature << 24)
		);
	crqb->ata_cmd[1] = cpu_to_le32(
			(tf->lbal << 0) |
			(tf->lbam << 8) |
			(tf->lbah << 16) |
			(tf->device << 24)
		);
	crqb->ata_cmd[2] = cpu_to_le32(
			(tf->hob_lbal << 0) |
			(tf->hob_lbam << 8) |
			(tf->hob_lbah << 16) |
			(tf->hob_feature << 24)
		);
	crqb->ata_cmd[3] = cpu_to_le32(
			(tf->nsect << 0) |
			(tf->hob_nsect << 8)
		);

	अगर (!(qc->flags & ATA_QCFLAG_DMAMAP))
		वापस AC_ERR_OK;
	mv_fill_sg(qc);

	वापस AC_ERR_OK;
पूर्ण

/**
 *	mv_sff_check_status - fetch device status, अगर valid
 *	@ap: ATA port to fetch status from
 *
 *	When using command issue via mv_qc_issue_fis(),
 *	the initial ATA_BUSY state करोes not show up in the
 *	ATA status (shaकरोw) रेजिस्टर.  This can confuse libata!
 *
 *	So we have a hook here to fake ATA_BUSY क्रम that situation,
 *	until the first समय a BUSY, DRQ, or ERR bit is seen.
 *
 *	The rest of the समय, it simply वापसs the ATA status रेजिस्टर.
 */
अटल u8 mv_sff_check_status(काष्ठा ata_port *ap)
अणु
	u8 stat = ioपढ़ो8(ap->ioaddr.status_addr);
	काष्ठा mv_port_priv *pp = ap->निजी_data;

	अगर (pp->pp_flags & MV_PP_FLAG_FAKE_ATA_BUSY) अणु
		अगर (stat & (ATA_BUSY | ATA_DRQ | ATA_ERR))
			pp->pp_flags &= ~MV_PP_FLAG_FAKE_ATA_BUSY;
		अन्यथा
			stat = ATA_BUSY;
	पूर्ण
	वापस stat;
पूर्ण

/**
 *	mv_send_fis - Send a FIS, using the "Vendor-Unique FIS" रेजिस्टर
 *	@ap: ATA port to send a FIS
 *	@fis: fis to be sent
 *	@nwords: number of 32-bit words in the fis
 */
अटल अचिन्हित पूर्णांक mv_send_fis(काष्ठा ata_port *ap, u32 *fis, पूर्णांक nwords)
अणु
	व्योम __iomem *port_mmio = mv_ap_base(ap);
	u32 अगरctl, old_अगरctl, अगरstat;
	पूर्णांक i, समयout = 200, final_word = nwords - 1;

	/* Initiate FIS transmission mode */
	old_अगरctl = पढ़ोl(port_mmio + SATA_IFCTL);
	अगरctl = 0x100 | (old_अगरctl & 0xf);
	ग_लिखोlfl(अगरctl, port_mmio + SATA_IFCTL);

	/* Send all words of the FIS except क्रम the final word */
	क्रम (i = 0; i < final_word; ++i)
		ग_लिखोl(fis[i], port_mmio + VENDOR_UNIQUE_FIS);

	/* Flag end-of-transmission, and then send the final word */
	ग_लिखोlfl(अगरctl | 0x200, port_mmio + SATA_IFCTL);
	ग_लिखोlfl(fis[final_word], port_mmio + VENDOR_UNIQUE_FIS);

	/*
	 * Wait क्रम FIS transmission to complete.
	 * This typically takes just a single iteration.
	 */
	करो अणु
		अगरstat = पढ़ोl(port_mmio + SATA_IFSTAT);
	पूर्ण जबतक (!(अगरstat & 0x1000) && --समयout);

	/* Restore original port configuration */
	ग_लिखोlfl(old_अगरctl, port_mmio + SATA_IFCTL);

	/* See अगर it worked */
	अगर ((अगरstat & 0x3000) != 0x1000) अणु
		ata_port_warn(ap, "%s transmission error, ifstat=%08x\n",
			      __func__, अगरstat);
		वापस AC_ERR_OTHER;
	पूर्ण
	वापस 0;
पूर्ण

/**
 *	mv_qc_issue_fis - Issue a command directly as a FIS
 *	@qc: queued command to start
 *
 *	Note that the ATA shaकरोw रेजिस्टरs are not updated
 *	after command issue, so the device will appear "READY"
 *	अगर polled, even जबतक it is BUSY processing the command.
 *
 *	So we use a status hook to fake ATA_BUSY until the drive changes state.
 *
 *	Note: we करोn't get updated shaकरोw regs on *completion*
 *	of non-data commands. So aव्योम sending them via this function,
 *	as they will appear to have completed immediately.
 *
 *	GEN_IIE has special रेजिस्टरs that we could get the result tf from,
 *	but earlier chipsets करो not.  For now, we ignore those रेजिस्टरs.
 */
अटल अचिन्हित पूर्णांक mv_qc_issue_fis(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा mv_port_priv *pp = ap->निजी_data;
	काष्ठा ata_link *link = qc->dev->link;
	u32 fis[5];
	पूर्णांक err = 0;

	ata_tf_to_fis(&qc->tf, link->pmp, 1, (व्योम *)fis);
	err = mv_send_fis(ap, fis, ARRAY_SIZE(fis));
	अगर (err)
		वापस err;

	चयन (qc->tf.protocol) अणु
	हाल ATAPI_PROT_PIO:
		pp->pp_flags |= MV_PP_FLAG_FAKE_ATA_BUSY;
		fallthrough;
	हाल ATAPI_PROT_NODATA:
		ap->hsm_task_state = HSM_ST_FIRST;
		अवरोध;
	हाल ATA_PROT_PIO:
		pp->pp_flags |= MV_PP_FLAG_FAKE_ATA_BUSY;
		अगर (qc->tf.flags & ATA_TFLAG_WRITE)
			ap->hsm_task_state = HSM_ST_FIRST;
		अन्यथा
			ap->hsm_task_state = HSM_ST;
		अवरोध;
	शेष:
		ap->hsm_task_state = HSM_ST_LAST;
		अवरोध;
	पूर्ण

	अगर (qc->tf.flags & ATA_TFLAG_POLLING)
		ata_sff_queue_pio_task(link, 0);
	वापस 0;
पूर्ण

/**
 *      mv_qc_issue - Initiate a command to the host
 *      @qc: queued command to start
 *
 *      This routine simply redirects to the general purpose routine
 *      अगर command is not DMA.  Else, it sanity checks our local
 *      caches of the request producer/consumer indices then enables
 *      DMA and bumps the request producer index.
 *
 *      LOCKING:
 *      Inherited from caller.
 */
अटल अचिन्हित पूर्णांक mv_qc_issue(काष्ठा ata_queued_cmd *qc)
अणु
	अटल पूर्णांक limit_warnings = 10;
	काष्ठा ata_port *ap = qc->ap;
	व्योम __iomem *port_mmio = mv_ap_base(ap);
	काष्ठा mv_port_priv *pp = ap->निजी_data;
	u32 in_index;
	अचिन्हित पूर्णांक port_irqs;

	pp->pp_flags &= ~MV_PP_FLAG_FAKE_ATA_BUSY; /* paranoia */

	चयन (qc->tf.protocol) अणु
	हाल ATA_PROT_DMA:
		अगर (qc->tf.command == ATA_CMD_DSM) अणु
			अगर (!ap->ops->bmdma_setup)  /* no bmdma on GEN_I */
				वापस AC_ERR_OTHER;
			अवरोध;  /* use bmdma क्रम this */
		पूर्ण
		fallthrough;
	हाल ATA_PROT_NCQ:
		mv_start_edma(ap, port_mmio, pp, qc->tf.protocol);
		pp->req_idx = (pp->req_idx + 1) & MV_MAX_Q_DEPTH_MASK;
		in_index = pp->req_idx << EDMA_REQ_Q_PTR_SHIFT;

		/* Write the request in poपूर्णांकer to kick the EDMA to lअगरe */
		ग_लिखोlfl((pp->crqb_dma & EDMA_REQ_Q_BASE_LO_MASK) | in_index,
					port_mmio + EDMA_REQ_Q_IN_PTR);
		वापस 0;

	हाल ATA_PROT_PIO:
		/*
		 * Errata SATA#16, SATA#24: warn अगर multiple DRQs expected.
		 *
		 * Someday, we might implement special polling workarounds
		 * क्रम these, but it all seems rather unnecessary since we
		 * normally use only DMA क्रम commands which transfer more
		 * than a single block of data.
		 *
		 * Much of the समय, this could just work regardless.
		 * So क्रम now, just log the incident, and allow the attempt.
		 */
		अगर (limit_warnings > 0 && (qc->nbytes / qc->sect_size) > 1) अणु
			--limit_warnings;
			ata_link_warn(qc->dev->link, DRV_NAME
				      ": attempting PIO w/multiple DRQ: "
				      "this may fail due to h/w errata\n");
		पूर्ण
		fallthrough;
	हाल ATA_PROT_NODATA:
	हाल ATAPI_PROT_PIO:
	हाल ATAPI_PROT_NODATA:
		अगर (ap->flags & ATA_FLAG_PIO_POLLING)
			qc->tf.flags |= ATA_TFLAG_POLLING;
		अवरोध;
	पूर्ण

	अगर (qc->tf.flags & ATA_TFLAG_POLLING)
		port_irqs = ERR_IRQ;	/* mask device पूर्णांकerrupt when polling */
	अन्यथा
		port_irqs = ERR_IRQ | DONE_IRQ;	/* unmask all पूर्णांकerrupts */

	/*
	 * We're about to send a non-EDMA capable command to the
	 * port.  Turn off EDMA so there won't be problems accessing
	 * shaकरोw block, etc रेजिस्टरs.
	 */
	mv_stop_edma(ap);
	mv_clear_and_enable_port_irqs(ap, mv_ap_base(ap), port_irqs);
	mv_pmp_select(ap, qc->dev->link->pmp);

	अगर (qc->tf.command == ATA_CMD_READ_LOG_EXT) अणु
		काष्ठा mv_host_priv *hpriv = ap->host->निजी_data;
		/*
		 * Workaround क्रम 88SX60x1 FEr SATA#25 (part 2).
		 *
		 * After any NCQ error, the READ_LOG_EXT command
		 * from libata-eh *must* use mv_qc_issue_fis().
		 * Otherwise it might fail, due to chip errata.
		 *
		 * Rather than special-हाल it, we'll just *always*
		 * use this method here क्रम READ_LOG_EXT, making क्रम
		 * easier testing.
		 */
		अगर (IS_GEN_II(hpriv))
			वापस mv_qc_issue_fis(qc);
	पूर्ण
	वापस ata_bmdma_qc_issue(qc);
पूर्ण

अटल काष्ठा ata_queued_cmd *mv_get_active_qc(काष्ठा ata_port *ap)
अणु
	काष्ठा mv_port_priv *pp = ap->निजी_data;
	काष्ठा ata_queued_cmd *qc;

	अगर (pp->pp_flags & MV_PP_FLAG_NCQ_EN)
		वापस शून्य;
	qc = ata_qc_from_tag(ap, ap->link.active_tag);
	अगर (qc && !(qc->tf.flags & ATA_TFLAG_POLLING))
		वापस qc;
	वापस शून्य;
पूर्ण

अटल व्योम mv_pmp_error_handler(काष्ठा ata_port *ap)
अणु
	अचिन्हित पूर्णांक pmp, pmp_map;
	काष्ठा mv_port_priv *pp = ap->निजी_data;

	अगर (pp->pp_flags & MV_PP_FLAG_DELAYED_EH) अणु
		/*
		 * Perक्रमm NCQ error analysis on failed PMPs
		 * beक्रमe we मुक्तze the port entirely.
		 *
		 * The failed PMPs are marked earlier by mv_pmp_eh_prep().
		 */
		pmp_map = pp->delayed_eh_pmp_map;
		pp->pp_flags &= ~MV_PP_FLAG_DELAYED_EH;
		क्रम (pmp = 0; pmp_map != 0; pmp++) अणु
			अचिन्हित पूर्णांक this_pmp = (1 << pmp);
			अगर (pmp_map & this_pmp) अणु
				काष्ठा ata_link *link = &ap->pmp_link[pmp];
				pmp_map &= ~this_pmp;
				ata_eh_analyze_ncq_error(link);
			पूर्ण
		पूर्ण
		ata_port_मुक्तze(ap);
	पूर्ण
	sata_pmp_error_handler(ap);
पूर्ण

अटल अचिन्हित पूर्णांक mv_get_err_pmp_map(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *port_mmio = mv_ap_base(ap);

	वापस पढ़ोl(port_mmio + SATA_TESTCTL) >> 16;
पूर्ण

अटल व्योम mv_pmp_eh_prep(काष्ठा ata_port *ap, अचिन्हित पूर्णांक pmp_map)
अणु
	अचिन्हित पूर्णांक pmp;

	/*
	 * Initialize EH info क्रम PMPs which saw device errors
	 */
	क्रम (pmp = 0; pmp_map != 0; pmp++) अणु
		अचिन्हित पूर्णांक this_pmp = (1 << pmp);
		अगर (pmp_map & this_pmp) अणु
			काष्ठा ata_link *link = &ap->pmp_link[pmp];
			काष्ठा ata_eh_info *ehi = &link->eh_info;

			pmp_map &= ~this_pmp;
			ata_ehi_clear_desc(ehi);
			ata_ehi_push_desc(ehi, "dev err");
			ehi->err_mask |= AC_ERR_DEV;
			ehi->action |= ATA_EH_RESET;
			ata_link_पात(link);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक mv_req_q_empty(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *port_mmio = mv_ap_base(ap);
	u32 in_ptr, out_ptr;

	in_ptr  = (पढ़ोl(port_mmio + EDMA_REQ_Q_IN_PTR)
			>> EDMA_REQ_Q_PTR_SHIFT) & MV_MAX_Q_DEPTH_MASK;
	out_ptr = (पढ़ोl(port_mmio + EDMA_REQ_Q_OUT_PTR)
			>> EDMA_REQ_Q_PTR_SHIFT) & MV_MAX_Q_DEPTH_MASK;
	वापस (in_ptr == out_ptr);	/* 1 == queue_is_empty */
पूर्ण

अटल पूर्णांक mv_handle_fbs_ncq_dev_err(काष्ठा ata_port *ap)
अणु
	काष्ठा mv_port_priv *pp = ap->निजी_data;
	पूर्णांक failed_links;
	अचिन्हित पूर्णांक old_map, new_map;

	/*
	 * Device error during FBS+NCQ operation:
	 *
	 * Set a port flag to prevent further I/O being enqueued.
	 * Leave the EDMA running to drain outstanding commands from this port.
	 * Perक्रमm the post-mortem/EH only when all responses are complete.
	 * Follow recovery sequence from 6042/7042 datasheet (7.3.15.4.2.2).
	 */
	अगर (!(pp->pp_flags & MV_PP_FLAG_DELAYED_EH)) अणु
		pp->pp_flags |= MV_PP_FLAG_DELAYED_EH;
		pp->delayed_eh_pmp_map = 0;
	पूर्ण
	old_map = pp->delayed_eh_pmp_map;
	new_map = old_map | mv_get_err_pmp_map(ap);

	अगर (old_map != new_map) अणु
		pp->delayed_eh_pmp_map = new_map;
		mv_pmp_eh_prep(ap, new_map & ~old_map);
	पूर्ण
	failed_links = hweight16(new_map);

	ata_port_info(ap,
		      "%s: pmp_map=%04x qc_map=%04llx failed_links=%d nr_active_links=%d\n",
		      __func__, pp->delayed_eh_pmp_map,
		      ap->qc_active, failed_links,
		      ap->nr_active_links);

	अगर (ap->nr_active_links <= failed_links && mv_req_q_empty(ap)) अणु
		mv_process_crpb_entries(ap, pp);
		mv_stop_edma(ap);
		mv_eh_मुक्तze(ap);
		ata_port_info(ap, "%s: done\n", __func__);
		वापस 1;	/* handled */
	पूर्ण
	ata_port_info(ap, "%s: waiting\n", __func__);
	वापस 1;	/* handled */
पूर्ण

अटल पूर्णांक mv_handle_fbs_non_ncq_dev_err(काष्ठा ata_port *ap)
अणु
	/*
	 * Possible future enhancement:
	 *
	 * FBS+non-NCQ operation is not yet implemented.
	 * See related notes in mv_edma_cfg().
	 *
	 * Device error during FBS+non-NCQ operation:
	 *
	 * We need to snapshot the shaकरोw रेजिस्टरs क्रम each failed command.
	 * Follow recovery sequence from 6042/7042 datasheet (7.3.15.4.2.3).
	 */
	वापस 0;	/* not handled */
पूर्ण

अटल पूर्णांक mv_handle_dev_err(काष्ठा ata_port *ap, u32 edma_err_cause)
अणु
	काष्ठा mv_port_priv *pp = ap->निजी_data;

	अगर (!(pp->pp_flags & MV_PP_FLAG_EDMA_EN))
		वापस 0;	/* EDMA was not active: not handled */
	अगर (!(pp->pp_flags & MV_PP_FLAG_FBS_EN))
		वापस 0;	/* FBS was not active: not handled */

	अगर (!(edma_err_cause & EDMA_ERR_DEV))
		वापस 0;	/* non DEV error: not handled */
	edma_err_cause &= ~EDMA_ERR_IRQ_TRANSIENT;
	अगर (edma_err_cause & ~(EDMA_ERR_DEV | EDMA_ERR_SELF_DIS))
		वापस 0;	/* other problems: not handled */

	अगर (pp->pp_flags & MV_PP_FLAG_NCQ_EN) अणु
		/*
		 * EDMA should NOT have self-disabled क्रम this हाल.
		 * If it did, then something is wrong अन्यथाwhere,
		 * and we cannot handle it here.
		 */
		अगर (edma_err_cause & EDMA_ERR_SELF_DIS) अणु
			ata_port_warn(ap, "%s: err_cause=0x%x pp_flags=0x%x\n",
				      __func__, edma_err_cause, pp->pp_flags);
			वापस 0; /* not handled */
		पूर्ण
		वापस mv_handle_fbs_ncq_dev_err(ap);
	पूर्ण अन्यथा अणु
		/*
		 * EDMA should have self-disabled क्रम this हाल.
		 * If it did not, then something is wrong अन्यथाwhere,
		 * and we cannot handle it here.
		 */
		अगर (!(edma_err_cause & EDMA_ERR_SELF_DIS)) अणु
			ata_port_warn(ap, "%s: err_cause=0x%x pp_flags=0x%x\n",
				      __func__, edma_err_cause, pp->pp_flags);
			वापस 0; /* not handled */
		पूर्ण
		वापस mv_handle_fbs_non_ncq_dev_err(ap);
	पूर्ण
	वापस 0;	/* not handled */
पूर्ण

अटल व्योम mv_unexpected_पूर्णांकr(काष्ठा ata_port *ap, पूर्णांक edma_was_enabled)
अणु
	काष्ठा ata_eh_info *ehi = &ap->link.eh_info;
	अक्षर *when = "idle";

	ata_ehi_clear_desc(ehi);
	अगर (edma_was_enabled) अणु
		when = "EDMA enabled";
	पूर्ण अन्यथा अणु
		काष्ठा ata_queued_cmd *qc = ata_qc_from_tag(ap, ap->link.active_tag);
		अगर (qc && (qc->tf.flags & ATA_TFLAG_POLLING))
			when = "polling";
	पूर्ण
	ata_ehi_push_desc(ehi, "unexpected device interrupt while %s", when);
	ehi->err_mask |= AC_ERR_OTHER;
	ehi->action   |= ATA_EH_RESET;
	ata_port_मुक्तze(ap);
पूर्ण

/**
 *      mv_err_पूर्णांकr - Handle error पूर्णांकerrupts on the port
 *      @ap: ATA channel to manipulate
 *
 *      Most हालs require a full reset of the chip's state machine,
 *      which also perक्रमms a COMRESET.
 *      Also, अगर the port disabled DMA, update our cached copy to match.
 *
 *      LOCKING:
 *      Inherited from caller.
 */
अटल व्योम mv_err_पूर्णांकr(काष्ठा ata_port *ap)
अणु
	व्योम __iomem *port_mmio = mv_ap_base(ap);
	u32 edma_err_cause, eh_मुक्तze_mask, serr = 0;
	u32 fis_cause = 0;
	काष्ठा mv_port_priv *pp = ap->निजी_data;
	काष्ठा mv_host_priv *hpriv = ap->host->निजी_data;
	अचिन्हित पूर्णांक action = 0, err_mask = 0;
	काष्ठा ata_eh_info *ehi = &ap->link.eh_info;
	काष्ठा ata_queued_cmd *qc;
	पूर्णांक पात = 0;

	/*
	 * Read and clear the SError and err_cause bits.
	 * For GenIIe, अगर EDMA_ERR_TRANS_IRQ_7 is set, we also must पढ़ो/clear
	 * the FIS_IRQ_CAUSE रेजिस्टर beक्रमe clearing edma_err_cause.
	 */
	sata_scr_पढ़ो(&ap->link, SCR_ERROR, &serr);
	sata_scr_ग_लिखो_flush(&ap->link, SCR_ERROR, serr);

	edma_err_cause = पढ़ोl(port_mmio + EDMA_ERR_IRQ_CAUSE);
	अगर (IS_GEN_IIE(hpriv) && (edma_err_cause & EDMA_ERR_TRANS_IRQ_7)) अणु
		fis_cause = पढ़ोl(port_mmio + FIS_IRQ_CAUSE);
		ग_लिखोlfl(~fis_cause, port_mmio + FIS_IRQ_CAUSE);
	पूर्ण
	ग_लिखोlfl(~edma_err_cause, port_mmio + EDMA_ERR_IRQ_CAUSE);

	अगर (edma_err_cause & EDMA_ERR_DEV) अणु
		/*
		 * Device errors during FIS-based चयनing operation
		 * require special handling.
		 */
		अगर (mv_handle_dev_err(ap, edma_err_cause))
			वापस;
	पूर्ण

	qc = mv_get_active_qc(ap);
	ata_ehi_clear_desc(ehi);
	ata_ehi_push_desc(ehi, "edma_err_cause=%08x pp_flags=%08x",
			  edma_err_cause, pp->pp_flags);

	अगर (IS_GEN_IIE(hpriv) && (edma_err_cause & EDMA_ERR_TRANS_IRQ_7)) अणु
		ata_ehi_push_desc(ehi, "fis_cause=%08x", fis_cause);
		अगर (fis_cause & FIS_IRQ_CAUSE_AN) अणु
			u32 ec = edma_err_cause &
			       ~(EDMA_ERR_TRANS_IRQ_7 | EDMA_ERR_IRQ_TRANSIENT);
			sata_async_notअगरication(ap);
			अगर (!ec)
				वापस; /* Just an AN; no need क्रम the nukes */
			ata_ehi_push_desc(ehi, "SDB notify");
		पूर्ण
	पूर्ण
	/*
	 * All generations share these EDMA error cause bits:
	 */
	अगर (edma_err_cause & EDMA_ERR_DEV) अणु
		err_mask |= AC_ERR_DEV;
		action |= ATA_EH_RESET;
		ata_ehi_push_desc(ehi, "dev error");
	पूर्ण
	अगर (edma_err_cause & (EDMA_ERR_D_PAR | EDMA_ERR_PRD_PAR |
			EDMA_ERR_CRQB_PAR | EDMA_ERR_CRPB_PAR |
			EDMA_ERR_INTRL_PAR)) अणु
		err_mask |= AC_ERR_ATA_BUS;
		action |= ATA_EH_RESET;
		ata_ehi_push_desc(ehi, "parity error");
	पूर्ण
	अगर (edma_err_cause & (EDMA_ERR_DEV_DCON | EDMA_ERR_DEV_CON)) अणु
		ata_ehi_hotplugged(ehi);
		ata_ehi_push_desc(ehi, edma_err_cause & EDMA_ERR_DEV_DCON ?
			"dev disconnect" : "dev connect");
		action |= ATA_EH_RESET;
	पूर्ण

	/*
	 * Gen-I has a dअगरferent SELF_DIS bit,
	 * dअगरferent FREEZE bits, and no SERR bit:
	 */
	अगर (IS_GEN_I(hpriv)) अणु
		eh_मुक्तze_mask = EDMA_EH_FREEZE_5;
		अगर (edma_err_cause & EDMA_ERR_SELF_DIS_5) अणु
			pp->pp_flags &= ~MV_PP_FLAG_EDMA_EN;
			ata_ehi_push_desc(ehi, "EDMA self-disable");
		पूर्ण
	पूर्ण अन्यथा अणु
		eh_मुक्तze_mask = EDMA_EH_FREEZE;
		अगर (edma_err_cause & EDMA_ERR_SELF_DIS) अणु
			pp->pp_flags &= ~MV_PP_FLAG_EDMA_EN;
			ata_ehi_push_desc(ehi, "EDMA self-disable");
		पूर्ण
		अगर (edma_err_cause & EDMA_ERR_SERR) अणु
			ata_ehi_push_desc(ehi, "SError=%08x", serr);
			err_mask |= AC_ERR_ATA_BUS;
			action |= ATA_EH_RESET;
		पूर्ण
	पूर्ण

	अगर (!err_mask) अणु
		err_mask = AC_ERR_OTHER;
		action |= ATA_EH_RESET;
	पूर्ण

	ehi->serror |= serr;
	ehi->action |= action;

	अगर (qc)
		qc->err_mask |= err_mask;
	अन्यथा
		ehi->err_mask |= err_mask;

	अगर (err_mask == AC_ERR_DEV) अणु
		/*
		 * Cannot करो ata_port_मुक्तze() here,
		 * because it would समाप्त PIO access,
		 * which is needed क्रम further diagnosis.
		 */
		mv_eh_मुक्तze(ap);
		पात = 1;
	पूर्ण अन्यथा अगर (edma_err_cause & eh_मुक्तze_mask) अणु
		/*
		 * Note to self: ata_port_मुक्तze() calls ata_port_पात()
		 */
		ata_port_मुक्तze(ap);
	पूर्ण अन्यथा अणु
		पात = 1;
	पूर्ण

	अगर (पात) अणु
		अगर (qc)
			ata_link_पात(qc->dev->link);
		अन्यथा
			ata_port_पात(ap);
	पूर्ण
पूर्ण

अटल bool mv_process_crpb_response(काष्ठा ata_port *ap,
		काष्ठा mv_crpb *response, अचिन्हित पूर्णांक tag, पूर्णांक ncq_enabled)
अणु
	u8 ata_status;
	u16 edma_status = le16_to_cpu(response->flags);

	/*
	 * edma_status from a response queue entry:
	 *   LSB is from EDMA_ERR_IRQ_CAUSE (non-NCQ only).
	 *   MSB is saved ATA status from command completion.
	 */
	अगर (!ncq_enabled) अणु
		u8 err_cause = edma_status & 0xff & ~EDMA_ERR_DEV;
		अगर (err_cause) अणु
			/*
			 * Error will be seen/handled by
			 * mv_err_पूर्णांकr().  So करो nothing at all here.
			 */
			वापस false;
		पूर्ण
	पूर्ण
	ata_status = edma_status >> CRPB_FLAG_STATUS_SHIFT;
	अगर (!ac_err_mask(ata_status))
		वापस true;
	/* अन्यथा: leave it क्रम mv_err_पूर्णांकr() */
	वापस false;
पूर्ण

अटल व्योम mv_process_crpb_entries(काष्ठा ata_port *ap, काष्ठा mv_port_priv *pp)
अणु
	व्योम __iomem *port_mmio = mv_ap_base(ap);
	काष्ठा mv_host_priv *hpriv = ap->host->निजी_data;
	u32 in_index;
	bool work_करोne = false;
	u32 करोne_mask = 0;
	पूर्णांक ncq_enabled = (pp->pp_flags & MV_PP_FLAG_NCQ_EN);

	/* Get the hardware queue position index */
	in_index = (पढ़ोl(port_mmio + EDMA_RSP_Q_IN_PTR)
			>> EDMA_RSP_Q_PTR_SHIFT) & MV_MAX_Q_DEPTH_MASK;

	/* Process new responses from since the last समय we looked */
	जबतक (in_index != pp->resp_idx) अणु
		अचिन्हित पूर्णांक tag;
		काष्ठा mv_crpb *response = &pp->crpb[pp->resp_idx];

		pp->resp_idx = (pp->resp_idx + 1) & MV_MAX_Q_DEPTH_MASK;

		अगर (IS_GEN_I(hpriv)) अणु
			/* 50xx: no NCQ, only one command active at a समय */
			tag = ap->link.active_tag;
		पूर्ण अन्यथा अणु
			/* Gen II/IIE: get command tag from CRPB entry */
			tag = le16_to_cpu(response->id) & 0x1f;
		पूर्ण
		अगर (mv_process_crpb_response(ap, response, tag, ncq_enabled))
			करोne_mask |= 1 << tag;
		work_करोne = true;
	पूर्ण

	अगर (work_करोne) अणु
		ata_qc_complete_multiple(ap, ata_qc_get_active(ap) ^ करोne_mask);

		/* Update the software queue position index in hardware */
		ग_लिखोlfl((pp->crpb_dma & EDMA_RSP_Q_BASE_LO_MASK) |
			 (pp->resp_idx << EDMA_RSP_Q_PTR_SHIFT),
			 port_mmio + EDMA_RSP_Q_OUT_PTR);
	पूर्ण
पूर्ण

अटल व्योम mv_port_पूर्णांकr(काष्ठा ata_port *ap, u32 port_cause)
अणु
	काष्ठा mv_port_priv *pp;
	पूर्णांक edma_was_enabled;

	/*
	 * Grab a snapshot of the EDMA_EN flag setting,
	 * so that we have a consistent view क्रम this port,
	 * even अगर something we call of our routines changes it.
	 */
	pp = ap->निजी_data;
	edma_was_enabled = (pp->pp_flags & MV_PP_FLAG_EDMA_EN);
	/*
	 * Process completed CRPB response(s) beक्रमe other events.
	 */
	अगर (edma_was_enabled && (port_cause & DONE_IRQ)) अणु
		mv_process_crpb_entries(ap, pp);
		अगर (pp->pp_flags & MV_PP_FLAG_DELAYED_EH)
			mv_handle_fbs_ncq_dev_err(ap);
	पूर्ण
	/*
	 * Handle chip-reported errors, or जारी on to handle PIO.
	 */
	अगर (unlikely(port_cause & ERR_IRQ)) अणु
		mv_err_पूर्णांकr(ap);
	पूर्ण अन्यथा अगर (!edma_was_enabled) अणु
		काष्ठा ata_queued_cmd *qc = mv_get_active_qc(ap);
		अगर (qc)
			ata_bmdma_port_पूर्णांकr(ap, qc);
		अन्यथा
			mv_unexpected_पूर्णांकr(ap, edma_was_enabled);
	पूर्ण
पूर्ण

/**
 *      mv_host_पूर्णांकr - Handle all पूर्णांकerrupts on the given host controller
 *      @host: host specअगरic काष्ठाure
 *      @मुख्य_irq_cause: Main पूर्णांकerrupt cause रेजिस्टर क्रम the chip.
 *
 *      LOCKING:
 *      Inherited from caller.
 */
अटल पूर्णांक mv_host_पूर्णांकr(काष्ठा ata_host *host, u32 मुख्य_irq_cause)
अणु
	काष्ठा mv_host_priv *hpriv = host->निजी_data;
	व्योम __iomem *mmio = hpriv->base, *hc_mmio;
	अचिन्हित पूर्णांक handled = 0, port;

	/* If निश्चितed, clear the "all ports" IRQ coalescing bit */
	अगर (मुख्य_irq_cause & ALL_PORTS_COAL_DONE)
		ग_लिखोl(~ALL_PORTS_COAL_IRQ, mmio + IRQ_COAL_CAUSE);

	क्रम (port = 0; port < hpriv->n_ports; port++) अणु
		काष्ठा ata_port *ap = host->ports[port];
		अचिन्हित पूर्णांक p, shअगरt, hardport, port_cause;

		MV_PORT_TO_SHIFT_AND_HARDPORT(port, shअगरt, hardport);
		/*
		 * Each hc within the host has its own hc_irq_cause रेजिस्टर,
		 * where the पूर्णांकerrupting ports bits get ack'd.
		 */
		अगर (hardport == 0) अणु	/* first port on this hc ? */
			u32 hc_cause = (मुख्य_irq_cause >> shअगरt) & HC0_IRQ_PEND;
			u32 port_mask, ack_irqs;
			/*
			 * Skip this entire hc अगर nothing pending क्रम any ports
			 */
			अगर (!hc_cause) अणु
				port += MV_PORTS_PER_HC - 1;
				जारी;
			पूर्ण
			/*
			 * We करोn't need/want to पढ़ो the hc_irq_cause रेजिस्टर,
			 * because करोing so hurts perक्रमmance, and
			 * मुख्य_irq_cause alपढ़ोy gives us everything we need.
			 *
			 * But we करो have to *ग_लिखो* to the hc_irq_cause to ack
			 * the ports that we are handling this समय through.
			 *
			 * This requires that we create a biपंचांगap क्रम those
			 * ports which पूर्णांकerrupted us, and use that biपंचांगap
			 * to ack (only) those ports via hc_irq_cause.
			 */
			ack_irqs = 0;
			अगर (hc_cause & PORTS_0_3_COAL_DONE)
				ack_irqs = HC_COAL_IRQ;
			क्रम (p = 0; p < MV_PORTS_PER_HC; ++p) अणु
				अगर ((port + p) >= hpriv->n_ports)
					अवरोध;
				port_mask = (DONE_IRQ | ERR_IRQ) << (p * 2);
				अगर (hc_cause & port_mask)
					ack_irqs |= (DMA_IRQ | DEV_IRQ) << p;
			पूर्ण
			hc_mmio = mv_hc_base_from_port(mmio, port);
			ग_लिखोlfl(~ack_irqs, hc_mmio + HC_IRQ_CAUSE);
			handled = 1;
		पूर्ण
		/*
		 * Handle पूर्णांकerrupts संकेतled क्रम this port:
		 */
		port_cause = (मुख्य_irq_cause >> shअगरt) & (DONE_IRQ | ERR_IRQ);
		अगर (port_cause)
			mv_port_पूर्णांकr(ap, port_cause);
	पूर्ण
	वापस handled;
पूर्ण

अटल पूर्णांक mv_pci_error(काष्ठा ata_host *host, व्योम __iomem *mmio)
अणु
	काष्ठा mv_host_priv *hpriv = host->निजी_data;
	काष्ठा ata_port *ap;
	काष्ठा ata_queued_cmd *qc;
	काष्ठा ata_eh_info *ehi;
	अचिन्हित पूर्णांक i, err_mask, prपूर्णांकed = 0;
	u32 err_cause;

	err_cause = पढ़ोl(mmio + hpriv->irq_cause_offset);

	dev_err(host->dev, "PCI ERROR; PCI IRQ cause=0x%08x\n", err_cause);

	DPRINTK("All regs @ PCI error\n");
	mv_dump_all_regs(mmio, -1, to_pci_dev(host->dev));

	ग_लिखोlfl(0, mmio + hpriv->irq_cause_offset);

	क्रम (i = 0; i < host->n_ports; i++) अणु
		ap = host->ports[i];
		अगर (!ata_link_offline(&ap->link)) अणु
			ehi = &ap->link.eh_info;
			ata_ehi_clear_desc(ehi);
			अगर (!prपूर्णांकed++)
				ata_ehi_push_desc(ehi,
					"PCI err cause 0x%08x", err_cause);
			err_mask = AC_ERR_HOST_BUS;
			ehi->action = ATA_EH_RESET;
			qc = ata_qc_from_tag(ap, ap->link.active_tag);
			अगर (qc)
				qc->err_mask |= err_mask;
			अन्यथा
				ehi->err_mask |= err_mask;

			ata_port_मुक्तze(ap);
		पूर्ण
	पूर्ण
	वापस 1;	/* handled */
पूर्ण

/**
 *      mv_पूर्णांकerrupt - Main पूर्णांकerrupt event handler
 *      @irq: unused
 *      @dev_instance: निजी data; in this हाल the host काष्ठाure
 *
 *      Read the पढ़ो only रेजिस्टर to determine अगर any host
 *      controllers have pending पूर्णांकerrupts.  If so, call lower level
 *      routine to handle.  Also check क्रम PCI errors which are only
 *      reported here.
 *
 *      LOCKING:
 *      This routine holds the host lock जबतक processing pending
 *      पूर्णांकerrupts.
 */
अटल irqवापस_t mv_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा ata_host *host = dev_instance;
	काष्ठा mv_host_priv *hpriv = host->निजी_data;
	अचिन्हित पूर्णांक handled = 0;
	पूर्णांक using_msi = hpriv->hp_flags & MV_HP_FLAG_MSI;
	u32 मुख्य_irq_cause, pending_irqs;

	spin_lock(&host->lock);

	/* क्रम MSI:  block new पूर्णांकerrupts जबतक in here */
	अगर (using_msi)
		mv_ग_लिखो_मुख्य_irq_mask(0, hpriv);

	मुख्य_irq_cause = पढ़ोl(hpriv->मुख्य_irq_cause_addr);
	pending_irqs   = मुख्य_irq_cause & hpriv->मुख्य_irq_mask;
	/*
	 * Deal with हालs where we either have nothing pending, or have पढ़ो
	 * a bogus रेजिस्टर value which can indicate HW removal or PCI fault.
	 */
	अगर (pending_irqs && मुख्य_irq_cause != 0xffffffffU) अणु
		अगर (unlikely((pending_irqs & PCI_ERR) && !IS_SOC(hpriv)))
			handled = mv_pci_error(host, hpriv->base);
		अन्यथा
			handled = mv_host_पूर्णांकr(host, pending_irqs);
	पूर्ण

	/* क्रम MSI: unmask; पूर्णांकerrupt cause bits will retrigger now */
	अगर (using_msi)
		mv_ग_लिखो_मुख्य_irq_mask(hpriv->मुख्य_irq_mask, hpriv);

	spin_unlock(&host->lock);

	वापस IRQ_RETVAL(handled);
पूर्ण

अटल अचिन्हित पूर्णांक mv5_scr_offset(अचिन्हित पूर्णांक sc_reg_in)
अणु
	अचिन्हित पूर्णांक ofs;

	चयन (sc_reg_in) अणु
	हाल SCR_STATUS:
	हाल SCR_ERROR:
	हाल SCR_CONTROL:
		ofs = sc_reg_in * माप(u32);
		अवरोध;
	शेष:
		ofs = 0xffffffffU;
		अवरोध;
	पूर्ण
	वापस ofs;
पूर्ण

अटल पूर्णांक mv5_scr_पढ़ो(काष्ठा ata_link *link, अचिन्हित पूर्णांक sc_reg_in, u32 *val)
अणु
	काष्ठा mv_host_priv *hpriv = link->ap->host->निजी_data;
	व्योम __iomem *mmio = hpriv->base;
	व्योम __iomem *addr = mv5_phy_base(mmio, link->ap->port_no);
	अचिन्हित पूर्णांक ofs = mv5_scr_offset(sc_reg_in);

	अगर (ofs != 0xffffffffU) अणु
		*val = पढ़ोl(addr + ofs);
		वापस 0;
	पूर्ण अन्यथा
		वापस -EINVAL;
पूर्ण

अटल पूर्णांक mv5_scr_ग_लिखो(काष्ठा ata_link *link, अचिन्हित पूर्णांक sc_reg_in, u32 val)
अणु
	काष्ठा mv_host_priv *hpriv = link->ap->host->निजी_data;
	व्योम __iomem *mmio = hpriv->base;
	व्योम __iomem *addr = mv5_phy_base(mmio, link->ap->port_no);
	अचिन्हित पूर्णांक ofs = mv5_scr_offset(sc_reg_in);

	अगर (ofs != 0xffffffffU) अणु
		ग_लिखोlfl(val, addr + ofs);
		वापस 0;
	पूर्ण अन्यथा
		वापस -EINVAL;
पूर्ण

अटल व्योम mv5_reset_bus(काष्ठा ata_host *host, व्योम __iomem *mmio)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(host->dev);
	पूर्णांक early_5080;

	early_5080 = (pdev->device == 0x5080) && (pdev->revision == 0);

	अगर (!early_5080) अणु
		u32 पंचांगp = पढ़ोl(mmio + MV_PCI_EXP_ROM_BAR_CTL);
		पंचांगp |= (1 << 0);
		ग_लिखोl(पंचांगp, mmio + MV_PCI_EXP_ROM_BAR_CTL);
	पूर्ण

	mv_reset_pci_bus(host, mmio);
पूर्ण

अटल व्योम mv5_reset_flash(काष्ठा mv_host_priv *hpriv, व्योम __iomem *mmio)
अणु
	ग_लिखोl(0x0fcfffff, mmio + FLASH_CTL);
पूर्ण

अटल व्योम mv5_पढ़ो_preamp(काष्ठा mv_host_priv *hpriv, पूर्णांक idx,
			   व्योम __iomem *mmio)
अणु
	व्योम __iomem *phy_mmio = mv5_phy_base(mmio, idx);
	u32 पंचांगp;

	पंचांगp = पढ़ोl(phy_mmio + MV5_PHY_MODE);

	hpriv->संकेत[idx].pre = पंचांगp & 0x1800;	/* bits 12:11 */
	hpriv->संकेत[idx].amps = पंचांगp & 0xe0;	/* bits 7:5 */
पूर्ण

अटल व्योम mv5_enable_leds(काष्ठा mv_host_priv *hpriv, व्योम __iomem *mmio)
अणु
	u32 पंचांगp;

	ग_लिखोl(0, mmio + GPIO_PORT_CTL);

	/* FIXME: handle MV_HP_ERRATA_50XXB2 errata */

	पंचांगp = पढ़ोl(mmio + MV_PCI_EXP_ROM_BAR_CTL);
	पंचांगp |= ~(1 << 0);
	ग_लिखोl(पंचांगp, mmio + MV_PCI_EXP_ROM_BAR_CTL);
पूर्ण

अटल व्योम mv5_phy_errata(काष्ठा mv_host_priv *hpriv, व्योम __iomem *mmio,
			   अचिन्हित पूर्णांक port)
अणु
	व्योम __iomem *phy_mmio = mv5_phy_base(mmio, port);
	स्थिर u32 mask = (1<<12) | (1<<11) | (1<<7) | (1<<6) | (1<<5);
	u32 पंचांगp;
	पूर्णांक fix_apm_sq = (hpriv->hp_flags & MV_HP_ERRATA_50XXB0);

	अगर (fix_apm_sq) अणु
		पंचांगp = पढ़ोl(phy_mmio + MV5_LTMODE);
		पंचांगp |= (1 << 19);
		ग_लिखोl(पंचांगp, phy_mmio + MV5_LTMODE);

		पंचांगp = पढ़ोl(phy_mmio + MV5_PHY_CTL);
		पंचांगp &= ~0x3;
		पंचांगp |= 0x1;
		ग_लिखोl(पंचांगp, phy_mmio + MV5_PHY_CTL);
	पूर्ण

	पंचांगp = पढ़ोl(phy_mmio + MV5_PHY_MODE);
	पंचांगp &= ~mask;
	पंचांगp |= hpriv->संकेत[port].pre;
	पंचांगp |= hpriv->संकेत[port].amps;
	ग_लिखोl(पंचांगp, phy_mmio + MV5_PHY_MODE);
पूर्ण


#अघोषित ZERO
#घोषणा ZERO(reg) ग_लिखोl(0, port_mmio + (reg))
अटल व्योम mv5_reset_hc_port(काष्ठा mv_host_priv *hpriv, व्योम __iomem *mmio,
			     अचिन्हित पूर्णांक port)
अणु
	व्योम __iomem *port_mmio = mv_port_base(mmio, port);

	mv_reset_channel(hpriv, mmio, port);

	ZERO(0x028);	/* command */
	ग_लिखोl(0x11f, port_mmio + EDMA_CFG);
	ZERO(0x004);	/* समयr */
	ZERO(0x008);	/* irq err cause */
	ZERO(0x00c);	/* irq err mask */
	ZERO(0x010);	/* rq bah */
	ZERO(0x014);	/* rq inp */
	ZERO(0x018);	/* rq outp */
	ZERO(0x01c);	/* respq bah */
	ZERO(0x024);	/* respq outp */
	ZERO(0x020);	/* respq inp */
	ZERO(0x02c);	/* test control */
	ग_लिखोl(0xbc, port_mmio + EDMA_IORDY_TMOUT);
पूर्ण
#अघोषित ZERO

#घोषणा ZERO(reg) ग_लिखोl(0, hc_mmio + (reg))
अटल व्योम mv5_reset_one_hc(काष्ठा mv_host_priv *hpriv, व्योम __iomem *mmio,
			अचिन्हित पूर्णांक hc)
अणु
	व्योम __iomem *hc_mmio = mv_hc_base(mmio, hc);
	u32 पंचांगp;

	ZERO(0x00c);
	ZERO(0x010);
	ZERO(0x014);
	ZERO(0x018);

	पंचांगp = पढ़ोl(hc_mmio + 0x20);
	पंचांगp &= 0x1c1c1c1c;
	पंचांगp |= 0x03030303;
	ग_लिखोl(पंचांगp, hc_mmio + 0x20);
पूर्ण
#अघोषित ZERO

अटल पूर्णांक mv5_reset_hc(काष्ठा mv_host_priv *hpriv, व्योम __iomem *mmio,
			अचिन्हित पूर्णांक n_hc)
अणु
	अचिन्हित पूर्णांक hc, port;

	क्रम (hc = 0; hc < n_hc; hc++) अणु
		क्रम (port = 0; port < MV_PORTS_PER_HC; port++)
			mv5_reset_hc_port(hpriv, mmio,
					  (hc * MV_PORTS_PER_HC) + port);

		mv5_reset_one_hc(hpriv, mmio, hc);
	पूर्ण

	वापस 0;
पूर्ण

#अघोषित ZERO
#घोषणा ZERO(reg) ग_लिखोl(0, mmio + (reg))
अटल व्योम mv_reset_pci_bus(काष्ठा ata_host *host, व्योम __iomem *mmio)
अणु
	काष्ठा mv_host_priv *hpriv = host->निजी_data;
	u32 पंचांगp;

	पंचांगp = पढ़ोl(mmio + MV_PCI_MODE);
	पंचांगp &= 0xff00ffff;
	ग_लिखोl(पंचांगp, mmio + MV_PCI_MODE);

	ZERO(MV_PCI_DISC_TIMER);
	ZERO(MV_PCI_MSI_TRIGGER);
	ग_लिखोl(0x000100ff, mmio + MV_PCI_XBAR_TMOUT);
	ZERO(MV_PCI_SERR_MASK);
	ZERO(hpriv->irq_cause_offset);
	ZERO(hpriv->irq_mask_offset);
	ZERO(MV_PCI_ERR_LOW_ADDRESS);
	ZERO(MV_PCI_ERR_HIGH_ADDRESS);
	ZERO(MV_PCI_ERR_ATTRIBUTE);
	ZERO(MV_PCI_ERR_COMMAND);
पूर्ण
#अघोषित ZERO

अटल व्योम mv6_reset_flash(काष्ठा mv_host_priv *hpriv, व्योम __iomem *mmio)
अणु
	u32 पंचांगp;

	mv5_reset_flash(hpriv, mmio);

	पंचांगp = पढ़ोl(mmio + GPIO_PORT_CTL);
	पंचांगp &= 0x3;
	पंचांगp |= (1 << 5) | (1 << 6);
	ग_लिखोl(पंचांगp, mmio + GPIO_PORT_CTL);
पूर्ण

/*
 *      mv6_reset_hc - Perक्रमm the 6xxx global soft reset
 *      @mmio: base address of the HBA
 *
 *      This routine only applies to 6xxx parts.
 *
 *      LOCKING:
 *      Inherited from caller.
 */
अटल पूर्णांक mv6_reset_hc(काष्ठा mv_host_priv *hpriv, व्योम __iomem *mmio,
			अचिन्हित पूर्णांक n_hc)
अणु
	व्योम __iomem *reg = mmio + PCI_MAIN_CMD_STS;
	पूर्णांक i, rc = 0;
	u32 t;

	/* Following procedure defined in PCI "मुख्य command and status
	 * रेजिस्टर" table.
	 */
	t = पढ़ोl(reg);
	ग_लिखोl(t | STOP_PCI_MASTER, reg);

	क्रम (i = 0; i < 1000; i++) अणु
		udelay(1);
		t = पढ़ोl(reg);
		अगर (PCI_MASTER_EMPTY & t)
			अवरोध;
	पूर्ण
	अगर (!(PCI_MASTER_EMPTY & t)) अणु
		prपूर्णांकk(KERN_ERR DRV_NAME ": PCI master won't flush\n");
		rc = 1;
		जाओ करोne;
	पूर्ण

	/* set reset */
	i = 5;
	करो अणु
		ग_लिखोl(t | GLOB_SFT_RST, reg);
		t = पढ़ोl(reg);
		udelay(1);
	पूर्ण जबतक (!(GLOB_SFT_RST & t) && (i-- > 0));

	अगर (!(GLOB_SFT_RST & t)) अणु
		prपूर्णांकk(KERN_ERR DRV_NAME ": can't set global reset\n");
		rc = 1;
		जाओ करोne;
	पूर्ण

	/* clear reset and *reenable the PCI master* (not mentioned in spec) */
	i = 5;
	करो अणु
		ग_लिखोl(t & ~(GLOB_SFT_RST | STOP_PCI_MASTER), reg);
		t = पढ़ोl(reg);
		udelay(1);
	पूर्ण जबतक ((GLOB_SFT_RST & t) && (i-- > 0));

	अगर (GLOB_SFT_RST & t) अणु
		prपूर्णांकk(KERN_ERR DRV_NAME ": can't clear global reset\n");
		rc = 1;
	पूर्ण
करोne:
	वापस rc;
पूर्ण

अटल व्योम mv6_पढ़ो_preamp(काष्ठा mv_host_priv *hpriv, पूर्णांक idx,
			   व्योम __iomem *mmio)
अणु
	व्योम __iomem *port_mmio;
	u32 पंचांगp;

	पंचांगp = पढ़ोl(mmio + RESET_CFG);
	अगर ((पंचांगp & (1 << 0)) == 0) अणु
		hpriv->संकेत[idx].amps = 0x7 << 8;
		hpriv->संकेत[idx].pre = 0x1 << 5;
		वापस;
	पूर्ण

	port_mmio = mv_port_base(mmio, idx);
	पंचांगp = पढ़ोl(port_mmio + PHY_MODE2);

	hpriv->संकेत[idx].amps = पंचांगp & 0x700;	/* bits 10:8 */
	hpriv->संकेत[idx].pre = पंचांगp & 0xe0;	/* bits 7:5 */
पूर्ण

अटल व्योम mv6_enable_leds(काष्ठा mv_host_priv *hpriv, व्योम __iomem *mmio)
अणु
	ग_लिखोl(0x00000060, mmio + GPIO_PORT_CTL);
पूर्ण

अटल व्योम mv6_phy_errata(काष्ठा mv_host_priv *hpriv, व्योम __iomem *mmio,
			   अचिन्हित पूर्णांक port)
अणु
	व्योम __iomem *port_mmio = mv_port_base(mmio, port);

	u32 hp_flags = hpriv->hp_flags;
	पूर्णांक fix_phy_mode2 =
		hp_flags & (MV_HP_ERRATA_60X1B2 | MV_HP_ERRATA_60X1C0);
	पूर्णांक fix_phy_mode4 =
		hp_flags & (MV_HP_ERRATA_60X1B2 | MV_HP_ERRATA_60X1C0);
	u32 m2, m3;

	अगर (fix_phy_mode2) अणु
		m2 = पढ़ोl(port_mmio + PHY_MODE2);
		m2 &= ~(1 << 16);
		m2 |= (1 << 31);
		ग_लिखोl(m2, port_mmio + PHY_MODE2);

		udelay(200);

		m2 = पढ़ोl(port_mmio + PHY_MODE2);
		m2 &= ~((1 << 16) | (1 << 31));
		ग_लिखोl(m2, port_mmio + PHY_MODE2);

		udelay(200);
	पूर्ण

	/*
	 * Gen-II/IIe PHY_MODE3 errata RM#2:
	 * Achieves better receiver noise perक्रमmance than the h/w शेष:
	 */
	m3 = पढ़ोl(port_mmio + PHY_MODE3);
	m3 = (m3 & 0x1f) | (0x5555601 << 5);

	/* Guideline 88F5182 (GL# SATA-S11) */
	अगर (IS_SOC(hpriv))
		m3 &= ~0x1c;

	अगर (fix_phy_mode4) अणु
		u32 m4 = पढ़ोl(port_mmio + PHY_MODE4);
		/*
		 * Enक्रमce reserved-bit restrictions on GenIIe devices only.
		 * For earlier chipsets, क्रमce only the पूर्णांकernal config field
		 *  (workaround क्रम errata FEr SATA#10 part 1).
		 */
		अगर (IS_GEN_IIE(hpriv))
			m4 = (m4 & ~PHY_MODE4_RSVD_ZEROS) | PHY_MODE4_RSVD_ONES;
		अन्यथा
			m4 = (m4 & ~PHY_MODE4_CFG_MASK) | PHY_MODE4_CFG_VALUE;
		ग_लिखोl(m4, port_mmio + PHY_MODE4);
	पूर्ण
	/*
	 * Workaround क्रम 60x1-B2 errata SATA#13:
	 * Any ग_लिखो to PHY_MODE4 (above) may corrupt PHY_MODE3,
	 * so we must always reग_लिखो PHY_MODE3 after PHY_MODE4.
	 * Or ensure we use ग_लिखोlfl() when writing PHY_MODE4.
	 */
	ग_लिखोl(m3, port_mmio + PHY_MODE3);

	/* Revert values of pre-emphasis and संकेत amps to the saved ones */
	m2 = पढ़ोl(port_mmio + PHY_MODE2);

	m2 &= ~MV_M2_PREAMP_MASK;
	m2 |= hpriv->संकेत[port].amps;
	m2 |= hpriv->संकेत[port].pre;
	m2 &= ~(1 << 16);

	/* according to mvSata 3.6.1, some IIE values are fixed */
	अगर (IS_GEN_IIE(hpriv)) अणु
		m2 &= ~0xC30FF01F;
		m2 |= 0x0000900F;
	पूर्ण

	ग_लिखोl(m2, port_mmio + PHY_MODE2);
पूर्ण

/* TODO: use the generic LED पूर्णांकerface to configure the SATA Presence */
/* & Acitivy LEDs on the board */
अटल व्योम mv_soc_enable_leds(काष्ठा mv_host_priv *hpriv,
				      व्योम __iomem *mmio)
अणु
	वापस;
पूर्ण

अटल व्योम mv_soc_पढ़ो_preamp(काष्ठा mv_host_priv *hpriv, पूर्णांक idx,
			   व्योम __iomem *mmio)
अणु
	व्योम __iomem *port_mmio;
	u32 पंचांगp;

	port_mmio = mv_port_base(mmio, idx);
	पंचांगp = पढ़ोl(port_mmio + PHY_MODE2);

	hpriv->संकेत[idx].amps = पंचांगp & 0x700;	/* bits 10:8 */
	hpriv->संकेत[idx].pre = पंचांगp & 0xe0;	/* bits 7:5 */
पूर्ण

#अघोषित ZERO
#घोषणा ZERO(reg) ग_लिखोl(0, port_mmio + (reg))
अटल व्योम mv_soc_reset_hc_port(काष्ठा mv_host_priv *hpriv,
					व्योम __iomem *mmio, अचिन्हित पूर्णांक port)
अणु
	व्योम __iomem *port_mmio = mv_port_base(mmio, port);

	mv_reset_channel(hpriv, mmio, port);

	ZERO(0x028);		/* command */
	ग_लिखोl(0x101f, port_mmio + EDMA_CFG);
	ZERO(0x004);		/* समयr */
	ZERO(0x008);		/* irq err cause */
	ZERO(0x00c);		/* irq err mask */
	ZERO(0x010);		/* rq bah */
	ZERO(0x014);		/* rq inp */
	ZERO(0x018);		/* rq outp */
	ZERO(0x01c);		/* respq bah */
	ZERO(0x024);		/* respq outp */
	ZERO(0x020);		/* respq inp */
	ZERO(0x02c);		/* test control */
	ग_लिखोl(0x800, port_mmio + EDMA_IORDY_TMOUT);
पूर्ण

#अघोषित ZERO

#घोषणा ZERO(reg) ग_लिखोl(0, hc_mmio + (reg))
अटल व्योम mv_soc_reset_one_hc(काष्ठा mv_host_priv *hpriv,
				       व्योम __iomem *mmio)
अणु
	व्योम __iomem *hc_mmio = mv_hc_base(mmio, 0);

	ZERO(0x00c);
	ZERO(0x010);
	ZERO(0x014);

पूर्ण

#अघोषित ZERO

अटल पूर्णांक mv_soc_reset_hc(काष्ठा mv_host_priv *hpriv,
				  व्योम __iomem *mmio, अचिन्हित पूर्णांक n_hc)
अणु
	अचिन्हित पूर्णांक port;

	क्रम (port = 0; port < hpriv->n_ports; port++)
		mv_soc_reset_hc_port(hpriv, mmio, port);

	mv_soc_reset_one_hc(hpriv, mmio);

	वापस 0;
पूर्ण

अटल व्योम mv_soc_reset_flash(काष्ठा mv_host_priv *hpriv,
				      व्योम __iomem *mmio)
अणु
	वापस;
पूर्ण

अटल व्योम mv_soc_reset_bus(काष्ठा ata_host *host, व्योम __iomem *mmio)
अणु
	वापस;
पूर्ण

अटल व्योम mv_soc_65n_phy_errata(काष्ठा mv_host_priv *hpriv,
				  व्योम __iomem *mmio, अचिन्हित पूर्णांक port)
अणु
	व्योम __iomem *port_mmio = mv_port_base(mmio, port);
	u32	reg;

	reg = पढ़ोl(port_mmio + PHY_MODE3);
	reg &= ~(0x3 << 27);	/* SELMUPF (bits 28:27) to 1 */
	reg |= (0x1 << 27);
	reg &= ~(0x3 << 29);	/* SELMUPI (bits 30:29) to 1 */
	reg |= (0x1 << 29);
	ग_लिखोl(reg, port_mmio + PHY_MODE3);

	reg = पढ़ोl(port_mmio + PHY_MODE4);
	reg &= ~0x1;	/* SATU_OD8 (bit 0) to 0, reserved bit 16 must be set */
	reg |= (0x1 << 16);
	ग_लिखोl(reg, port_mmio + PHY_MODE4);

	reg = पढ़ोl(port_mmio + PHY_MODE9_GEN2);
	reg &= ~0xf;	/* TXAMP[3:0] (bits 3:0) to 8 */
	reg |= 0x8;
	reg &= ~(0x1 << 14);	/* TXAMP[4] (bit 14) to 0 */
	ग_लिखोl(reg, port_mmio + PHY_MODE9_GEN2);

	reg = पढ़ोl(port_mmio + PHY_MODE9_GEN1);
	reg &= ~0xf;	/* TXAMP[3:0] (bits 3:0) to 8 */
	reg |= 0x8;
	reg &= ~(0x1 << 14);	/* TXAMP[4] (bit 14) to 0 */
	ग_लिखोl(reg, port_mmio + PHY_MODE9_GEN1);
पूर्ण

/*
 *	soc_is_65 - check अगर the soc is 65 nano device
 *
 *	Detect the type of the SoC, this is करोne by पढ़ोing the PHYCFG_OFS
 *	रेजिस्टर, this रेजिस्टर should contain non-zero value and it exists only
 *	in the 65 nano devices, when पढ़ोing it from older devices we get 0.
 */
अटल bool soc_is_65n(काष्ठा mv_host_priv *hpriv)
अणु
	व्योम __iomem *port0_mmio = mv_port_base(hpriv->base, 0);

	अगर (पढ़ोl(port0_mmio + PHYCFG_OFS))
		वापस true;
	वापस false;
पूर्ण

अटल व्योम mv_setup_अगरcfg(व्योम __iomem *port_mmio, पूर्णांक want_gen2i)
अणु
	u32 अगरcfg = पढ़ोl(port_mmio + SATA_IFCFG);

	अगरcfg = (अगरcfg & 0xf7f) | 0x9b1000;	/* from chip spec */
	अगर (want_gen2i)
		अगरcfg |= (1 << 7);		/* enable gen2i speed */
	ग_लिखोlfl(अगरcfg, port_mmio + SATA_IFCFG);
पूर्ण

अटल व्योम mv_reset_channel(काष्ठा mv_host_priv *hpriv, व्योम __iomem *mmio,
			     अचिन्हित पूर्णांक port_no)
अणु
	व्योम __iomem *port_mmio = mv_port_base(mmio, port_no);

	/*
	 * The datasheet warns against setting EDMA_RESET when EDMA is active
	 * (but करोesn't say what the problem might be).  So we first try
	 * to disable the EDMA engine beक्रमe करोing the EDMA_RESET operation.
	 */
	mv_stop_edma_engine(port_mmio);
	ग_लिखोlfl(EDMA_RESET, port_mmio + EDMA_CMD);

	अगर (!IS_GEN_I(hpriv)) अणु
		/* Enable 3.0gb/s link speed: this survives EDMA_RESET */
		mv_setup_अगरcfg(port_mmio, 1);
	पूर्ण
	/*
	 * Strobing EDMA_RESET here causes a hard reset of the SATA transport,
	 * link, and physical layers.  It resets all SATA पूर्णांकerface रेजिस्टरs
	 * (except क्रम SATA_IFCFG), and issues a COMRESET to the dev.
	 */
	ग_लिखोlfl(EDMA_RESET, port_mmio + EDMA_CMD);
	udelay(25);	/* allow reset propagation */
	ग_लिखोlfl(0, port_mmio + EDMA_CMD);

	hpriv->ops->phy_errata(hpriv, mmio, port_no);

	अगर (IS_GEN_I(hpriv))
		usleep_range(500, 1000);
पूर्ण

अटल व्योम mv_pmp_select(काष्ठा ata_port *ap, पूर्णांक pmp)
अणु
	अगर (sata_pmp_supported(ap)) अणु
		व्योम __iomem *port_mmio = mv_ap_base(ap);
		u32 reg = पढ़ोl(port_mmio + SATA_IFCTL);
		पूर्णांक old = reg & 0xf;

		अगर (old != pmp) अणु
			reg = (reg & ~0xf) | pmp;
			ग_लिखोlfl(reg, port_mmio + SATA_IFCTL);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक mv_pmp_hardreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *class,
				अचिन्हित दीर्घ deadline)
अणु
	mv_pmp_select(link->ap, sata_srst_pmp(link));
	वापस sata_std_hardreset(link, class, deadline);
पूर्ण

अटल पूर्णांक mv_softreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *class,
				अचिन्हित दीर्घ deadline)
अणु
	mv_pmp_select(link->ap, sata_srst_pmp(link));
	वापस ata_sff_softreset(link, class, deadline);
पूर्ण

अटल पूर्णांक mv_hardreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *class,
			अचिन्हित दीर्घ deadline)
अणु
	काष्ठा ata_port *ap = link->ap;
	काष्ठा mv_host_priv *hpriv = ap->host->निजी_data;
	काष्ठा mv_port_priv *pp = ap->निजी_data;
	व्योम __iomem *mmio = hpriv->base;
	पूर्णांक rc, attempts = 0, extra = 0;
	u32 sstatus;
	bool online;

	mv_reset_channel(hpriv, mmio, ap->port_no);
	pp->pp_flags &= ~MV_PP_FLAG_EDMA_EN;
	pp->pp_flags &=
	  ~(MV_PP_FLAG_FBS_EN | MV_PP_FLAG_NCQ_EN | MV_PP_FLAG_FAKE_ATA_BUSY);

	/* Workaround क्रम errata FEr SATA#10 (part 2) */
	करो अणु
		स्थिर अचिन्हित दीर्घ *timing =
				sata_ehc_deb_timing(&link->eh_context);

		rc = sata_link_hardreset(link, timing, deadline + extra,
					 &online, शून्य);
		rc = online ? -EAGAIN : rc;
		अगर (rc)
			वापस rc;
		sata_scr_पढ़ो(link, SCR_STATUS, &sstatus);
		अगर (!IS_GEN_I(hpriv) && ++attempts >= 5 && sstatus == 0x121) अणु
			/* Force 1.5gb/s link speed and try again */
			mv_setup_अगरcfg(mv_ap_base(ap), 0);
			अगर (समय_after(jअगरfies + HZ, deadline))
				extra = HZ; /* only extend it once, max */
		पूर्ण
	पूर्ण जबतक (sstatus != 0x0 && sstatus != 0x113 && sstatus != 0x123);
	mv_save_cached_regs(ap);
	mv_edma_cfg(ap, 0, 0);

	वापस rc;
पूर्ण

अटल व्योम mv_eh_मुक्तze(काष्ठा ata_port *ap)
अणु
	mv_stop_edma(ap);
	mv_enable_port_irqs(ap, 0);
पूर्ण

अटल व्योम mv_eh_thaw(काष्ठा ata_port *ap)
अणु
	काष्ठा mv_host_priv *hpriv = ap->host->निजी_data;
	अचिन्हित पूर्णांक port = ap->port_no;
	अचिन्हित पूर्णांक hardport = mv_hardport_from_port(port);
	व्योम __iomem *hc_mmio = mv_hc_base_from_port(hpriv->base, port);
	व्योम __iomem *port_mmio = mv_ap_base(ap);
	u32 hc_irq_cause;

	/* clear EDMA errors on this port */
	ग_लिखोl(0, port_mmio + EDMA_ERR_IRQ_CAUSE);

	/* clear pending irq events */
	hc_irq_cause = ~((DEV_IRQ | DMA_IRQ) << hardport);
	ग_लिखोlfl(hc_irq_cause, hc_mmio + HC_IRQ_CAUSE);

	mv_enable_port_irqs(ap, ERR_IRQ);
पूर्ण

/**
 *      mv_port_init - Perक्रमm some early initialization on a single port.
 *      @port: libata data काष्ठाure storing shaकरोw रेजिस्टर addresses
 *      @port_mmio: base address of the port
 *
 *      Initialize shaकरोw रेजिस्टर mmio addresses, clear outstanding
 *      पूर्णांकerrupts on the port, and unmask पूर्णांकerrupts क्रम the future
 *      start of the port.
 *
 *      LOCKING:
 *      Inherited from caller.
 */
अटल व्योम mv_port_init(काष्ठा ata_ioports *port,  व्योम __iomem *port_mmio)
अणु
	व्योम __iomem *serr, *shd_base = port_mmio + SHD_BLK;

	/* PIO related setup
	 */
	port->data_addr = shd_base + (माप(u32) * ATA_REG_DATA);
	port->error_addr =
		port->feature_addr = shd_base + (माप(u32) * ATA_REG_ERR);
	port->nsect_addr = shd_base + (माप(u32) * ATA_REG_NSECT);
	port->lbal_addr = shd_base + (माप(u32) * ATA_REG_LBAL);
	port->lbam_addr = shd_base + (माप(u32) * ATA_REG_LBAM);
	port->lbah_addr = shd_base + (माप(u32) * ATA_REG_LBAH);
	port->device_addr = shd_base + (माप(u32) * ATA_REG_DEVICE);
	port->status_addr =
		port->command_addr = shd_base + (माप(u32) * ATA_REG_STATUS);
	/* special हाल: control/altstatus करोesn't have ATA_REG_ address */
	port->altstatus_addr = port->ctl_addr = shd_base + SHD_CTL_AST;

	/* Clear any currently outstanding port पूर्णांकerrupt conditions */
	serr = port_mmio + mv_scr_offset(SCR_ERROR);
	ग_लिखोlfl(पढ़ोl(serr), serr);
	ग_लिखोlfl(0, port_mmio + EDMA_ERR_IRQ_CAUSE);

	/* unmask all non-transient EDMA error पूर्णांकerrupts */
	ग_लिखोlfl(~EDMA_ERR_IRQ_TRANSIENT, port_mmio + EDMA_ERR_IRQ_MASK);

	VPRINTK("EDMA cfg=0x%08x EDMA IRQ err cause/mask=0x%08x/0x%08x\n",
		पढ़ोl(port_mmio + EDMA_CFG),
		पढ़ोl(port_mmio + EDMA_ERR_IRQ_CAUSE),
		पढ़ोl(port_mmio + EDMA_ERR_IRQ_MASK));
पूर्ण

अटल अचिन्हित पूर्णांक mv_in_pcix_mode(काष्ठा ata_host *host)
अणु
	काष्ठा mv_host_priv *hpriv = host->निजी_data;
	व्योम __iomem *mmio = hpriv->base;
	u32 reg;

	अगर (IS_SOC(hpriv) || !IS_PCIE(hpriv))
		वापस 0;	/* not PCI-X capable */
	reg = पढ़ोl(mmio + MV_PCI_MODE);
	अगर ((reg & MV_PCI_MODE_MASK) == 0)
		वापस 0;	/* conventional PCI mode */
	वापस 1;	/* chip is in PCI-X mode */
पूर्ण

अटल पूर्णांक mv_pci_cut_through_okay(काष्ठा ata_host *host)
अणु
	काष्ठा mv_host_priv *hpriv = host->निजी_data;
	व्योम __iomem *mmio = hpriv->base;
	u32 reg;

	अगर (!mv_in_pcix_mode(host)) अणु
		reg = पढ़ोl(mmio + MV_PCI_COMMAND);
		अगर (reg & MV_PCI_COMMAND_MRDTRIG)
			वापस 0; /* not okay */
	पूर्ण
	वापस 1; /* okay */
पूर्ण

अटल व्योम mv_60x1b2_errata_pci7(काष्ठा ata_host *host)
अणु
	काष्ठा mv_host_priv *hpriv = host->निजी_data;
	व्योम __iomem *mmio = hpriv->base;

	/* workaround क्रम 60x1-B2 errata PCI#7 */
	अगर (mv_in_pcix_mode(host)) अणु
		u32 reg = पढ़ोl(mmio + MV_PCI_COMMAND);
		ग_लिखोlfl(reg & ~MV_PCI_COMMAND_MWRCOM, mmio + MV_PCI_COMMAND);
	पूर्ण
पूर्ण

अटल पूर्णांक mv_chip_id(काष्ठा ata_host *host, अचिन्हित पूर्णांक board_idx)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(host->dev);
	काष्ठा mv_host_priv *hpriv = host->निजी_data;
	u32 hp_flags = hpriv->hp_flags;

	चयन (board_idx) अणु
	हाल chip_5080:
		hpriv->ops = &mv5xxx_ops;
		hp_flags |= MV_HP_GEN_I;

		चयन (pdev->revision) अणु
		हाल 0x1:
			hp_flags |= MV_HP_ERRATA_50XXB0;
			अवरोध;
		हाल 0x3:
			hp_flags |= MV_HP_ERRATA_50XXB2;
			अवरोध;
		शेष:
			dev_warn(&pdev->dev,
				 "Applying 50XXB2 workarounds to unknown rev\n");
			hp_flags |= MV_HP_ERRATA_50XXB2;
			अवरोध;
		पूर्ण
		अवरोध;

	हाल chip_504x:
	हाल chip_508x:
		hpriv->ops = &mv5xxx_ops;
		hp_flags |= MV_HP_GEN_I;

		चयन (pdev->revision) अणु
		हाल 0x0:
			hp_flags |= MV_HP_ERRATA_50XXB0;
			अवरोध;
		हाल 0x3:
			hp_flags |= MV_HP_ERRATA_50XXB2;
			अवरोध;
		शेष:
			dev_warn(&pdev->dev,
				 "Applying B2 workarounds to unknown rev\n");
			hp_flags |= MV_HP_ERRATA_50XXB2;
			अवरोध;
		पूर्ण
		अवरोध;

	हाल chip_604x:
	हाल chip_608x:
		hpriv->ops = &mv6xxx_ops;
		hp_flags |= MV_HP_GEN_II;

		चयन (pdev->revision) अणु
		हाल 0x7:
			mv_60x1b2_errata_pci7(host);
			hp_flags |= MV_HP_ERRATA_60X1B2;
			अवरोध;
		हाल 0x9:
			hp_flags |= MV_HP_ERRATA_60X1C0;
			अवरोध;
		शेष:
			dev_warn(&pdev->dev,
				 "Applying B2 workarounds to unknown rev\n");
			hp_flags |= MV_HP_ERRATA_60X1B2;
			अवरोध;
		पूर्ण
		अवरोध;

	हाल chip_7042:
		hp_flags |= MV_HP_PCIE | MV_HP_CUT_THROUGH;
		अगर (pdev->venकरोr == PCI_VENDOR_ID_TTI &&
		    (pdev->device == 0x2300 || pdev->device == 0x2310))
		अणु
			/*
			 * Highpoपूर्णांक RocketRAID PCIe 23xx series cards:
			 *
			 * Unconfigured drives are treated as "Legacy"
			 * by the BIOS, and it overग_लिखोs sector 8 with
			 * a "Lgcy" metadata block prior to Linux boot.
			 *
			 * Configured drives (RAID or JBOD) leave sector 8
			 * alone, but instead overग_लिखो a high numbered
			 * sector क्रम the RAID metadata.  This sector can
			 * be determined exactly, by truncating the physical
			 * drive capacity to a nice even GB value.
			 *
			 * RAID metadata is at: (dev->n_sectors & ~0xfffff)
			 *
			 * Warn the user, lest they think we're just buggy.
			 */
			prपूर्णांकk(KERN_WARNING DRV_NAME ": Highpoint RocketRAID"
				" BIOS CORRUPTS DATA on all attached drives,"
				" regardless of if/how they are configured."
				" BEWARE!\n");
			prपूर्णांकk(KERN_WARNING DRV_NAME ": For data safety, do not"
				" use sectors 8-9 on \"Legacy\" drives,"
				" and avoid the final two gigabytes on"
				" all RocketRAID BIOS initialized drives.\n");
		पूर्ण
		fallthrough;
	हाल chip_6042:
		hpriv->ops = &mv6xxx_ops;
		hp_flags |= MV_HP_GEN_IIE;
		अगर (board_idx == chip_6042 && mv_pci_cut_through_okay(host))
			hp_flags |= MV_HP_CUT_THROUGH;

		चयन (pdev->revision) अणु
		हाल 0x2: /* Rev.B0: the first/only खुला release */
			hp_flags |= MV_HP_ERRATA_60X1C0;
			अवरोध;
		शेष:
			dev_warn(&pdev->dev,
				 "Applying 60X1C0 workarounds to unknown rev\n");
			hp_flags |= MV_HP_ERRATA_60X1C0;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल chip_soc:
		अगर (soc_is_65n(hpriv))
			hpriv->ops = &mv_soc_65n_ops;
		अन्यथा
			hpriv->ops = &mv_soc_ops;
		hp_flags |= MV_HP_FLAG_SOC | MV_HP_GEN_IIE |
			MV_HP_ERRATA_60X1C0;
		अवरोध;

	शेष:
		dev_err(host->dev, "BUG: invalid board index %u\n", board_idx);
		वापस 1;
	पूर्ण

	hpriv->hp_flags = hp_flags;
	अगर (hp_flags & MV_HP_PCIE) अणु
		hpriv->irq_cause_offset	= PCIE_IRQ_CAUSE;
		hpriv->irq_mask_offset	= PCIE_IRQ_MASK;
		hpriv->unmask_all_irqs	= PCIE_UNMASK_ALL_IRQS;
	पूर्ण अन्यथा अणु
		hpriv->irq_cause_offset	= PCI_IRQ_CAUSE;
		hpriv->irq_mask_offset	= PCI_IRQ_MASK;
		hpriv->unmask_all_irqs	= PCI_UNMASK_ALL_IRQS;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *      mv_init_host - Perक्रमm some early initialization of the host.
 *	@host: ATA host to initialize
 *
 *      If possible, करो an early global reset of the host.  Then करो
 *      our port init and clear/unmask all/relevant host पूर्णांकerrupts.
 *
 *      LOCKING:
 *      Inherited from caller.
 */
अटल पूर्णांक mv_init_host(काष्ठा ata_host *host)
अणु
	पूर्णांक rc = 0, n_hc, port, hc;
	काष्ठा mv_host_priv *hpriv = host->निजी_data;
	व्योम __iomem *mmio = hpriv->base;

	rc = mv_chip_id(host, hpriv->board_idx);
	अगर (rc)
		जाओ करोne;

	अगर (IS_SOC(hpriv)) अणु
		hpriv->मुख्य_irq_cause_addr = mmio + SOC_HC_MAIN_IRQ_CAUSE;
		hpriv->मुख्य_irq_mask_addr  = mmio + SOC_HC_MAIN_IRQ_MASK;
	पूर्ण अन्यथा अणु
		hpriv->मुख्य_irq_cause_addr = mmio + PCI_HC_MAIN_IRQ_CAUSE;
		hpriv->मुख्य_irq_mask_addr  = mmio + PCI_HC_MAIN_IRQ_MASK;
	पूर्ण

	/* initialize shaकरोw irq mask with रेजिस्टर's value */
	hpriv->मुख्य_irq_mask = पढ़ोl(hpriv->मुख्य_irq_mask_addr);

	/* global पूर्णांकerrupt mask: 0 == mask everything */
	mv_set_मुख्य_irq_mask(host, ~0, 0);

	n_hc = mv_get_hc_count(host->ports[0]->flags);

	क्रम (port = 0; port < host->n_ports; port++)
		अगर (hpriv->ops->पढ़ो_preamp)
			hpriv->ops->पढ़ो_preamp(hpriv, port, mmio);

	rc = hpriv->ops->reset_hc(hpriv, mmio, n_hc);
	अगर (rc)
		जाओ करोne;

	hpriv->ops->reset_flash(hpriv, mmio);
	hpriv->ops->reset_bus(host, mmio);
	hpriv->ops->enable_leds(hpriv, mmio);

	क्रम (port = 0; port < host->n_ports; port++) अणु
		काष्ठा ata_port *ap = host->ports[port];
		व्योम __iomem *port_mmio = mv_port_base(mmio, port);

		mv_port_init(&ap->ioaddr, port_mmio);
	पूर्ण

	क्रम (hc = 0; hc < n_hc; hc++) अणु
		व्योम __iomem *hc_mmio = mv_hc_base(mmio, hc);

		VPRINTK("HC%i: HC config=0x%08x HC IRQ cause "
			"(before clear)=0x%08x\n", hc,
			पढ़ोl(hc_mmio + HC_CFG),
			पढ़ोl(hc_mmio + HC_IRQ_CAUSE));

		/* Clear any currently outstanding hc पूर्णांकerrupt conditions */
		ग_लिखोlfl(0, hc_mmio + HC_IRQ_CAUSE);
	पूर्ण

	अगर (!IS_SOC(hpriv)) अणु
		/* Clear any currently outstanding host पूर्णांकerrupt conditions */
		ग_लिखोlfl(0, mmio + hpriv->irq_cause_offset);

		/* and unmask पूर्णांकerrupt generation क्रम host regs */
		ग_लिखोlfl(hpriv->unmask_all_irqs, mmio + hpriv->irq_mask_offset);
	पूर्ण

	/*
	 * enable only global host पूर्णांकerrupts क्रम now.
	 * The per-port पूर्णांकerrupts get करोne later as ports are set up.
	 */
	mv_set_मुख्य_irq_mask(host, 0, PCI_ERR);
	mv_set_irq_coalescing(host, irq_coalescing_io_count,
				    irq_coalescing_usecs);
करोne:
	वापस rc;
पूर्ण

अटल पूर्णांक mv_create_dma_pools(काष्ठा mv_host_priv *hpriv, काष्ठा device *dev)
अणु
	hpriv->crqb_pool   = dmam_pool_create("crqb_q", dev, MV_CRQB_Q_SZ,
							     MV_CRQB_Q_SZ, 0);
	अगर (!hpriv->crqb_pool)
		वापस -ENOMEM;

	hpriv->crpb_pool   = dmam_pool_create("crpb_q", dev, MV_CRPB_Q_SZ,
							     MV_CRPB_Q_SZ, 0);
	अगर (!hpriv->crpb_pool)
		वापस -ENOMEM;

	hpriv->sg_tbl_pool = dmam_pool_create("sg_tbl", dev, MV_SG_TBL_SZ,
							     MV_SG_TBL_SZ, 0);
	अगर (!hpriv->sg_tbl_pool)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम mv_conf_mbus_winकरोws(काष्ठा mv_host_priv *hpriv,
				 स्थिर काष्ठा mbus_dram_target_info *dram)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 4; i++) अणु
		ग_लिखोl(0, hpriv->base + WINDOW_CTRL(i));
		ग_लिखोl(0, hpriv->base + WINDOW_BASE(i));
	पूर्ण

	क्रम (i = 0; i < dram->num_cs; i++) अणु
		स्थिर काष्ठा mbus_dram_winकरोw *cs = dram->cs + i;

		ग_लिखोl(((cs->size - 1) & 0xffff0000) |
			(cs->mbus_attr << 8) |
			(dram->mbus_dram_target_id << 4) | 1,
			hpriv->base + WINDOW_CTRL(i));
		ग_लिखोl(cs->base, hpriv->base + WINDOW_BASE(i));
	पूर्ण
पूर्ण

/**
 *      mv_platक्रमm_probe - handle a positive probe of an soc Marvell
 *      host
 *      @pdev: platक्रमm device found
 *
 *      LOCKING:
 *      Inherited from caller.
 */
अटल पूर्णांक mv_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा mv_sata_platक्रमm_data *mv_platक्रमm_data;
	स्थिर काष्ठा mbus_dram_target_info *dram;
	स्थिर काष्ठा ata_port_info *ppi[] =
	    अणु &mv_port_info[chip_soc], शून्य पूर्ण;
	काष्ठा ata_host *host;
	काष्ठा mv_host_priv *hpriv;
	काष्ठा resource *res;
	पूर्णांक n_ports = 0, irq = 0;
	पूर्णांक rc;
	पूर्णांक port;

	ata_prपूर्णांक_version_once(&pdev->dev, DRV_VERSION);

	/*
	 * Simple resource validation ..
	 */
	अगर (unlikely(pdev->num_resources != 2)) अणु
		dev_err(&pdev->dev, "invalid number of resources\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Get the रेजिस्टर base first
	 */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (res == शून्य)
		वापस -EINVAL;

	/* allocate host */
	अगर (pdev->dev.of_node) अणु
		rc = of_property_पढ़ो_u32(pdev->dev.of_node, "nr-ports",
					   &n_ports);
		अगर (rc) अणु
			dev_err(&pdev->dev,
				"error parsing nr-ports property: %d\n", rc);
			वापस rc;
		पूर्ण

		अगर (n_ports <= 0) अणु
			dev_err(&pdev->dev, "nr-ports must be positive: %d\n",
				n_ports);
			वापस -EINVAL;
		पूर्ण

		irq = irq_of_parse_and_map(pdev->dev.of_node, 0);
	पूर्ण अन्यथा अणु
		mv_platक्रमm_data = dev_get_platdata(&pdev->dev);
		n_ports = mv_platक्रमm_data->n_ports;
		irq = platक्रमm_get_irq(pdev, 0);
	पूर्ण
	अगर (irq < 0)
		वापस irq;
	अगर (!irq)
		वापस -EINVAL;

	host = ata_host_alloc_pinfo(&pdev->dev, ppi, n_ports);
	hpriv = devm_kzalloc(&pdev->dev, माप(*hpriv), GFP_KERNEL);

	अगर (!host || !hpriv)
		वापस -ENOMEM;
	hpriv->port_clks = devm_kसुस्मृति(&pdev->dev,
					n_ports, माप(काष्ठा clk *),
					GFP_KERNEL);
	अगर (!hpriv->port_clks)
		वापस -ENOMEM;
	hpriv->port_phys = devm_kसुस्मृति(&pdev->dev,
					n_ports, माप(काष्ठा phy *),
					GFP_KERNEL);
	अगर (!hpriv->port_phys)
		वापस -ENOMEM;
	host->निजी_data = hpriv;
	hpriv->board_idx = chip_soc;

	host->iomap = शून्य;
	hpriv->base = devm_ioremap(&pdev->dev, res->start,
				   resource_size(res));
	अगर (!hpriv->base)
		वापस -ENOMEM;

	hpriv->base -= SATAHC0_REG_BASE;

	hpriv->clk = clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(hpriv->clk))
		dev_notice(&pdev->dev, "cannot get optional clkdev\n");
	अन्यथा
		clk_prepare_enable(hpriv->clk);

	क्रम (port = 0; port < n_ports; port++) अणु
		अक्षर port_number[16];
		प्र_लिखो(port_number, "%d", port);
		hpriv->port_clks[port] = clk_get(&pdev->dev, port_number);
		अगर (!IS_ERR(hpriv->port_clks[port]))
			clk_prepare_enable(hpriv->port_clks[port]);

		प्र_लिखो(port_number, "port%d", port);
		hpriv->port_phys[port] = devm_phy_optional_get(&pdev->dev,
							       port_number);
		अगर (IS_ERR(hpriv->port_phys[port])) अणु
			rc = PTR_ERR(hpriv->port_phys[port]);
			hpriv->port_phys[port] = शून्य;
			अगर (rc != -EPROBE_DEFER)
				dev_warn(&pdev->dev, "error getting phy %d", rc);

			/* Cleanup only the initialized ports */
			hpriv->n_ports = port;
			जाओ err;
		पूर्ण अन्यथा
			phy_घातer_on(hpriv->port_phys[port]);
	पूर्ण

	/* All the ports have been initialized */
	hpriv->n_ports = n_ports;

	/*
	 * (Re-)program MBUS remapping winकरोws अगर we are asked to.
	 */
	dram = mv_mbus_dram_info();
	अगर (dram)
		mv_conf_mbus_winकरोws(hpriv, dram);

	rc = mv_create_dma_pools(hpriv, &pdev->dev);
	अगर (rc)
		जाओ err;

	/*
	 * To allow disk hotplug on Armada 370/XP SoCs, the PHY speed must be
	 * updated in the LP_PHY_CTL रेजिस्टर.
	 */
	अगर (pdev->dev.of_node &&
		of_device_is_compatible(pdev->dev.of_node,
					"marvell,armada-370-sata"))
		hpriv->hp_flags |= MV_HP_FIX_LP_PHY_CTL;

	/* initialize adapter */
	rc = mv_init_host(host);
	अगर (rc)
		जाओ err;

	dev_info(&pdev->dev, "slots %u ports %d\n",
		 (अचिन्हित)MV_MAX_Q_DEPTH, host->n_ports);

	rc = ata_host_activate(host, irq, mv_पूर्णांकerrupt, IRQF_SHARED, &mv6_sht);
	अगर (!rc)
		वापस 0;

err:
	अगर (!IS_ERR(hpriv->clk)) अणु
		clk_disable_unprepare(hpriv->clk);
		clk_put(hpriv->clk);
	पूर्ण
	क्रम (port = 0; port < hpriv->n_ports; port++) अणु
		अगर (!IS_ERR(hpriv->port_clks[port])) अणु
			clk_disable_unprepare(hpriv->port_clks[port]);
			clk_put(hpriv->port_clks[port]);
		पूर्ण
		phy_घातer_off(hpriv->port_phys[port]);
	पूर्ण

	वापस rc;
पूर्ण

/*
 *
 *      mv_platक्रमm_हटाओ    -       unplug a platक्रमm पूर्णांकerface
 *      @pdev: platक्रमm device
 *
 *      A platक्रमm bus SATA device has been unplugged. Perक्रमm the needed
 *      cleanup. Also called on module unload क्रम any active devices.
 */
अटल पूर्णांक mv_platक्रमm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ata_host *host = platक्रमm_get_drvdata(pdev);
	काष्ठा mv_host_priv *hpriv = host->निजी_data;
	पूर्णांक port;
	ata_host_detach(host);

	अगर (!IS_ERR(hpriv->clk)) अणु
		clk_disable_unprepare(hpriv->clk);
		clk_put(hpriv->clk);
	पूर्ण
	क्रम (port = 0; port < host->n_ports; port++) अणु
		अगर (!IS_ERR(hpriv->port_clks[port])) अणु
			clk_disable_unprepare(hpriv->port_clks[port]);
			clk_put(hpriv->port_clks[port]);
		पूर्ण
		phy_घातer_off(hpriv->port_phys[port]);
	पूर्ण
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक mv_platक्रमm_suspend(काष्ठा platक्रमm_device *pdev, pm_message_t state)
अणु
	काष्ठा ata_host *host = platक्रमm_get_drvdata(pdev);
	अगर (host)
		वापस ata_host_suspend(host, state);
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक mv_platक्रमm_resume(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ata_host *host = platक्रमm_get_drvdata(pdev);
	स्थिर काष्ठा mbus_dram_target_info *dram;
	पूर्णांक ret;

	अगर (host) अणु
		काष्ठा mv_host_priv *hpriv = host->निजी_data;

		/*
		 * (Re-)program MBUS remapping winकरोws अगर we are asked to.
		 */
		dram = mv_mbus_dram_info();
		अगर (dram)
			mv_conf_mbus_winकरोws(hpriv, dram);

		/* initialize adapter */
		ret = mv_init_host(host);
		अगर (ret) अणु
			prपूर्णांकk(KERN_ERR DRV_NAME ": Error during HW init\n");
			वापस ret;
		पूर्ण
		ata_host_resume(host);
	पूर्ण

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा mv_platक्रमm_suspend शून्य
#घोषणा mv_platक्रमm_resume शून्य
#पूर्ण_अगर

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id mv_sata_dt_ids[] = अणु
	अणु .compatible = "marvell,armada-370-sata", पूर्ण,
	अणु .compatible = "marvell,orion-sata", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mv_sata_dt_ids);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver mv_platक्रमm_driver = अणु
	.probe		= mv_platक्रमm_probe,
	.हटाओ		= mv_platक्रमm_हटाओ,
	.suspend	= mv_platक्रमm_suspend,
	.resume		= mv_platक्रमm_resume,
	.driver		= अणु
		.name = DRV_NAME,
		.of_match_table = of_match_ptr(mv_sata_dt_ids),
	पूर्ण,
पूर्ण;


#अगर_घोषित CONFIG_PCI
अटल पूर्णांक mv_pci_init_one(काष्ठा pci_dev *pdev,
			   स्थिर काष्ठा pci_device_id *ent);
#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक mv_pci_device_resume(काष्ठा pci_dev *pdev);
#पूर्ण_अगर


अटल काष्ठा pci_driver mv_pci_driver = अणु
	.name			= DRV_NAME,
	.id_table		= mv_pci_tbl,
	.probe			= mv_pci_init_one,
	.हटाओ			= ata_pci_हटाओ_one,
#अगर_घोषित CONFIG_PM_SLEEP
	.suspend		= ata_pci_device_suspend,
	.resume			= mv_pci_device_resume,
#पूर्ण_अगर

पूर्ण;

/**
 *      mv_prपूर्णांक_info - Dump key info to kernel log क्रम perusal.
 *      @host: ATA host to prपूर्णांक info about
 *
 *      FIXME: complete this.
 *
 *      LOCKING:
 *      Inherited from caller.
 */
अटल व्योम mv_prपूर्णांक_info(काष्ठा ata_host *host)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(host->dev);
	काष्ठा mv_host_priv *hpriv = host->निजी_data;
	u8 scc;
	स्थिर अक्षर *scc_s, *gen;

	/* Use this to determine the HW stepping of the chip so we know
	 * what errata to workaround
	 */
	pci_पढ़ो_config_byte(pdev, PCI_CLASS_DEVICE, &scc);
	अगर (scc == 0)
		scc_s = "SCSI";
	अन्यथा अगर (scc == 0x01)
		scc_s = "RAID";
	अन्यथा
		scc_s = "?";

	अगर (IS_GEN_I(hpriv))
		gen = "I";
	अन्यथा अगर (IS_GEN_II(hpriv))
		gen = "II";
	अन्यथा अगर (IS_GEN_IIE(hpriv))
		gen = "IIE";
	अन्यथा
		gen = "?";

	dev_info(&pdev->dev, "Gen-%s %u slots %u ports %s mode IRQ via %s\n",
		 gen, (अचिन्हित)MV_MAX_Q_DEPTH, host->n_ports,
		 scc_s, (MV_HP_FLAG_MSI & hpriv->hp_flags) ? "MSI" : "INTx");
पूर्ण

/**
 *      mv_pci_init_one - handle a positive probe of a PCI Marvell host
 *      @pdev: PCI device found
 *      @ent: PCI device ID entry क्रम the matched host
 *
 *      LOCKING:
 *      Inherited from caller.
 */
अटल पूर्णांक mv_pci_init_one(काष्ठा pci_dev *pdev,
			   स्थिर काष्ठा pci_device_id *ent)
अणु
	अचिन्हित पूर्णांक board_idx = (अचिन्हित पूर्णांक)ent->driver_data;
	स्थिर काष्ठा ata_port_info *ppi[] = अणु &mv_port_info[board_idx], शून्य पूर्ण;
	काष्ठा ata_host *host;
	काष्ठा mv_host_priv *hpriv;
	पूर्णांक n_ports, port, rc;

	ata_prपूर्णांक_version_once(&pdev->dev, DRV_VERSION);

	/* allocate host */
	n_ports = mv_get_hc_count(ppi[0]->flags) * MV_PORTS_PER_HC;

	host = ata_host_alloc_pinfo(&pdev->dev, ppi, n_ports);
	hpriv = devm_kzalloc(&pdev->dev, माप(*hpriv), GFP_KERNEL);
	अगर (!host || !hpriv)
		वापस -ENOMEM;
	host->निजी_data = hpriv;
	hpriv->n_ports = n_ports;
	hpriv->board_idx = board_idx;

	/* acquire resources */
	rc = pcim_enable_device(pdev);
	अगर (rc)
		वापस rc;

	rc = pcim_iomap_regions(pdev, 1 << MV_PRIMARY_BAR, DRV_NAME);
	अगर (rc == -EBUSY)
		pcim_pin_device(pdev);
	अगर (rc)
		वापस rc;
	host->iomap = pcim_iomap_table(pdev);
	hpriv->base = host->iomap[MV_PRIMARY_BAR];

	rc = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
	अगर (rc) अणु
		dev_err(&pdev->dev, "DMA enable failed\n");
		वापस rc;
	पूर्ण

	rc = mv_create_dma_pools(hpriv, &pdev->dev);
	अगर (rc)
		वापस rc;

	क्रम (port = 0; port < host->n_ports; port++) अणु
		काष्ठा ata_port *ap = host->ports[port];
		व्योम __iomem *port_mmio = mv_port_base(hpriv->base, port);
		अचिन्हित पूर्णांक offset = port_mmio - hpriv->base;

		ata_port_pbar_desc(ap, MV_PRIMARY_BAR, -1, "mmio");
		ata_port_pbar_desc(ap, MV_PRIMARY_BAR, offset, "port");
	पूर्ण

	/* initialize adapter */
	rc = mv_init_host(host);
	अगर (rc)
		वापस rc;

	/* Enable message-चयनed पूर्णांकerrupts, अगर requested */
	अगर (msi && pci_enable_msi(pdev) == 0)
		hpriv->hp_flags |= MV_HP_FLAG_MSI;

	mv_dump_pci_cfg(pdev, 0x68);
	mv_prपूर्णांक_info(host);

	pci_set_master(pdev);
	pci_try_set_mwi(pdev);
	वापस ata_host_activate(host, pdev->irq, mv_पूर्णांकerrupt, IRQF_SHARED,
				 IS_GEN_I(hpriv) ? &mv5_sht : &mv6_sht);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक mv_pci_device_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ata_host *host = pci_get_drvdata(pdev);
	पूर्णांक rc;

	rc = ata_pci_device_करो_resume(pdev);
	अगर (rc)
		वापस rc;

	/* initialize adapter */
	rc = mv_init_host(host);
	अगर (rc)
		वापस rc;

	ata_host_resume(host);

	वापस 0;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर

अटल पूर्णांक __init mv_init(व्योम)
अणु
	पूर्णांक rc = -ENODEV;
#अगर_घोषित CONFIG_PCI
	rc = pci_रेजिस्टर_driver(&mv_pci_driver);
	अगर (rc < 0)
		वापस rc;
#पूर्ण_अगर
	rc = platक्रमm_driver_रेजिस्टर(&mv_platक्रमm_driver);

#अगर_घोषित CONFIG_PCI
	अगर (rc < 0)
		pci_unरेजिस्टर_driver(&mv_pci_driver);
#पूर्ण_अगर
	वापस rc;
पूर्ण

अटल व्योम __निकास mv_निकास(व्योम)
अणु
#अगर_घोषित CONFIG_PCI
	pci_unरेजिस्टर_driver(&mv_pci_driver);
#पूर्ण_अगर
	platक्रमm_driver_unरेजिस्टर(&mv_platक्रमm_driver);
पूर्ण

MODULE_AUTHOR("Brett Russ");
MODULE_DESCRIPTION("SCSI low-level driver for Marvell SATA controllers");
MODULE_LICENSE("GPL v2");
MODULE_DEVICE_TABLE(pci, mv_pci_tbl);
MODULE_VERSION(DRV_VERSION);
MODULE_ALIAS("platform:" DRV_NAME);

module_init(mv_init);
module_निकास(mv_निकास);
