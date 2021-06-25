<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * 2007+ Copyright (c) Evgeniy Polyakov <johnpol@2ka.mipt.ru>
 * All rights reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/mm.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/crypto.h>
#समावेश <linux/hw_अक्रमom.h>
#समावेश <linux/kसमय.स>

#समावेश <crypto/algapi.h>
#समावेश <crypto/पूर्णांकernal/des.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>

अटल अक्षर hअगरn_pll_ref[माप("extNNN")] = "ext";
module_param_string(hअगरn_pll_ref, hअगरn_pll_ref, माप(hअगरn_pll_ref), 0444);
MODULE_PARM_DESC(hअगरn_pll_ref,
		 "PLL reference clock (pci[freq] or ext[freq], default ext)");

अटल atomic_t hअगरn_dev_number;

#घोषणा ACRYPTO_OP_DECRYPT	0
#घोषणा ACRYPTO_OP_ENCRYPT	1
#घोषणा ACRYPTO_OP_HMAC		2
#घोषणा ACRYPTO_OP_RNG		3

#घोषणा ACRYPTO_MODE_ECB		0
#घोषणा ACRYPTO_MODE_CBC		1
#घोषणा ACRYPTO_MODE_CFB		2
#घोषणा ACRYPTO_MODE_OFB		3

#घोषणा ACRYPTO_TYPE_AES_128	0
#घोषणा ACRYPTO_TYPE_AES_192	1
#घोषणा ACRYPTO_TYPE_AES_256	2
#घोषणा ACRYPTO_TYPE_3DES	3
#घोषणा ACRYPTO_TYPE_DES	4

#घोषणा PCI_VENDOR_ID_HIFN		0x13A3
#घोषणा PCI_DEVICE_ID_HIFN_7955		0x0020
#घोषणा	PCI_DEVICE_ID_HIFN_7956		0x001d

/* I/O region sizes */

#घोषणा HIFN_BAR0_SIZE			0x1000
#घोषणा HIFN_BAR1_SIZE			0x2000
#घोषणा HIFN_BAR2_SIZE			0x8000

/* DMA registres */

#घोषणा HIFN_DMA_CRA			0x0C	/* DMA Command Ring Address */
#घोषणा HIFN_DMA_SDRA			0x1C	/* DMA Source Data Ring Address */
#घोषणा HIFN_DMA_RRA			0x2C	/* DMA Result Ring Address */
#घोषणा HIFN_DMA_DDRA			0x3C	/* DMA Destination Data Ring Address */
#घोषणा HIFN_DMA_STCTL			0x40	/* DMA Status and Control */
#घोषणा HIFN_DMA_INTREN			0x44	/* DMA Interrupt Enable */
#घोषणा HIFN_DMA_CFG1			0x48	/* DMA Configuration #1 */
#घोषणा HIFN_DMA_CFG2			0x6C	/* DMA Configuration #2 */
#घोषणा HIFN_CHIP_ID			0x98	/* Chip ID */

/*
 * Processing Unit Registers (offset from BASEREG0)
 */
#घोषणा	HIFN_0_PUDATA		0x00	/* Processing Unit Data */
#घोषणा	HIFN_0_PUCTRL		0x04	/* Processing Unit Control */
#घोषणा	HIFN_0_PUISR		0x08	/* Processing Unit Interrupt Status */
#घोषणा	HIFN_0_PUCNFG		0x0c	/* Processing Unit Configuration */
#घोषणा	HIFN_0_PUIER		0x10	/* Processing Unit Interrupt Enable */
#घोषणा	HIFN_0_PUSTAT		0x14	/* Processing Unit Status/Chip ID */
#घोषणा	HIFN_0_FIFOSTAT		0x18	/* FIFO Status */
#घोषणा	HIFN_0_FIFOCNFG		0x1c	/* FIFO Configuration */
#घोषणा	HIFN_0_SPACESIZE	0x20	/* Register space size */

/* Processing Unit Control Register (HIFN_0_PUCTRL) */
#घोषणा	HIFN_PUCTRL_CLRSRCFIFO	0x0010	/* clear source fअगरo */
#घोषणा	HIFN_PUCTRL_STOP	0x0008	/* stop pu */
#घोषणा	HIFN_PUCTRL_LOCKRAM	0x0004	/* lock ram */
#घोषणा	HIFN_PUCTRL_DMAENA	0x0002	/* enable dma */
#घोषणा	HIFN_PUCTRL_RESET	0x0001	/* Reset processing unit */

/* Processing Unit Interrupt Status Register (HIFN_0_PUISR) */
#घोषणा	HIFN_PUISR_CMDINVAL	0x8000	/* Invalid command पूर्णांकerrupt */
#घोषणा	HIFN_PUISR_DATAERR	0x4000	/* Data error पूर्णांकerrupt */
#घोषणा	HIFN_PUISR_SRCFIFO	0x2000	/* Source FIFO पढ़ोy पूर्णांकerrupt */
#घोषणा	HIFN_PUISR_DSTFIFO	0x1000	/* Destination FIFO पढ़ोy पूर्णांकerrupt */
#घोषणा	HIFN_PUISR_DSTOVER	0x0200	/* Destination overrun पूर्णांकerrupt */
#घोषणा	HIFN_PUISR_SRCCMD	0x0080	/* Source command पूर्णांकerrupt */
#घोषणा	HIFN_PUISR_SRCCTX	0x0040	/* Source context पूर्णांकerrupt */
#घोषणा	HIFN_PUISR_SRCDATA	0x0020	/* Source data पूर्णांकerrupt */
#घोषणा	HIFN_PUISR_DSTDATA	0x0010	/* Destination data पूर्णांकerrupt */
#घोषणा	HIFN_PUISR_DSTRESULT	0x0004	/* Destination result पूर्णांकerrupt */

/* Processing Unit Configuration Register (HIFN_0_PUCNFG) */
#घोषणा	HIFN_PUCNFG_DRAMMASK	0xe000	/* DRAM size mask */
#घोषणा	HIFN_PUCNFG_DSZ_256K	0x0000	/* 256k dram */
#घोषणा	HIFN_PUCNFG_DSZ_512K	0x2000	/* 512k dram */
#घोषणा	HIFN_PUCNFG_DSZ_1M	0x4000	/* 1m dram */
#घोषणा	HIFN_PUCNFG_DSZ_2M	0x6000	/* 2m dram */
#घोषणा	HIFN_PUCNFG_DSZ_4M	0x8000	/* 4m dram */
#घोषणा	HIFN_PUCNFG_DSZ_8M	0xa000	/* 8m dram */
#घोषणा	HIFN_PUNCFG_DSZ_16M	0xc000	/* 16m dram */
#घोषणा	HIFN_PUCNFG_DSZ_32M	0xe000	/* 32m dram */
#घोषणा	HIFN_PUCNFG_DRAMREFRESH	0x1800	/* DRAM refresh rate mask */
#घोषणा	HIFN_PUCNFG_DRFR_512	0x0000	/* 512 भागisor of ECLK */
#घोषणा	HIFN_PUCNFG_DRFR_256	0x0800	/* 256 भागisor of ECLK */
#घोषणा	HIFN_PUCNFG_DRFR_128	0x1000	/* 128 भागisor of ECLK */
#घोषणा	HIFN_PUCNFG_TCALLPHASES	0x0200	/* your guess is as good as mine... */
#घोषणा	HIFN_PUCNFG_TCDRVTOTEM	0x0100	/* your guess is as good as mine... */
#घोषणा	HIFN_PUCNFG_BIGENDIAN	0x0080	/* DMA big endian mode */
#घोषणा	HIFN_PUCNFG_BUS32	0x0040	/* Bus width 32bits */
#घोषणा	HIFN_PUCNFG_BUS16	0x0000	/* Bus width 16 bits */
#घोषणा	HIFN_PUCNFG_CHIPID	0x0020	/* Allow chipid from PUSTAT */
#घोषणा	HIFN_PUCNFG_DRAM	0x0010	/* Context RAM is DRAM */
#घोषणा	HIFN_PUCNFG_SRAM	0x0000	/* Context RAM is SRAM */
#घोषणा	HIFN_PUCNFG_COMPSING	0x0004	/* Enable single compression context */
#घोषणा	HIFN_PUCNFG_ENCCNFG	0x0002	/* Encryption configuration */

/* Processing Unit Interrupt Enable Register (HIFN_0_PUIER) */
#घोषणा	HIFN_PUIER_CMDINVAL	0x8000	/* Invalid command पूर्णांकerrupt */
#घोषणा	HIFN_PUIER_DATAERR	0x4000	/* Data error पूर्णांकerrupt */
#घोषणा	HIFN_PUIER_SRCFIFO	0x2000	/* Source FIFO पढ़ोy पूर्णांकerrupt */
#घोषणा	HIFN_PUIER_DSTFIFO	0x1000	/* Destination FIFO पढ़ोy पूर्णांकerrupt */
#घोषणा	HIFN_PUIER_DSTOVER	0x0200	/* Destination overrun पूर्णांकerrupt */
#घोषणा	HIFN_PUIER_SRCCMD	0x0080	/* Source command पूर्णांकerrupt */
#घोषणा	HIFN_PUIER_SRCCTX	0x0040	/* Source context पूर्णांकerrupt */
#घोषणा	HIFN_PUIER_SRCDATA	0x0020	/* Source data पूर्णांकerrupt */
#घोषणा	HIFN_PUIER_DSTDATA	0x0010	/* Destination data पूर्णांकerrupt */
#घोषणा	HIFN_PUIER_DSTRESULT	0x0004	/* Destination result पूर्णांकerrupt */

/* Processing Unit Status Register/Chip ID (HIFN_0_PUSTAT) */
#घोषणा	HIFN_PUSTAT_CMDINVAL	0x8000	/* Invalid command पूर्णांकerrupt */
#घोषणा	HIFN_PUSTAT_DATAERR	0x4000	/* Data error पूर्णांकerrupt */
#घोषणा	HIFN_PUSTAT_SRCFIFO	0x2000	/* Source FIFO पढ़ोy पूर्णांकerrupt */
#घोषणा	HIFN_PUSTAT_DSTFIFO	0x1000	/* Destination FIFO पढ़ोy पूर्णांकerrupt */
#घोषणा	HIFN_PUSTAT_DSTOVER	0x0200	/* Destination overrun पूर्णांकerrupt */
#घोषणा	HIFN_PUSTAT_SRCCMD	0x0080	/* Source command पूर्णांकerrupt */
#घोषणा	HIFN_PUSTAT_SRCCTX	0x0040	/* Source context पूर्णांकerrupt */
#घोषणा	HIFN_PUSTAT_SRCDATA	0x0020	/* Source data पूर्णांकerrupt */
#घोषणा	HIFN_PUSTAT_DSTDATA	0x0010	/* Destination data पूर्णांकerrupt */
#घोषणा	HIFN_PUSTAT_DSTRESULT	0x0004	/* Destination result पूर्णांकerrupt */
#घोषणा	HIFN_PUSTAT_CHIPREV	0x00ff	/* Chip revision mask */
#घोषणा	HIFN_PUSTAT_CHIPENA	0xff00	/* Chip enabled mask */
#घोषणा	HIFN_PUSTAT_ENA_2	0x1100	/* Level 2 enabled */
#घोषणा	HIFN_PUSTAT_ENA_1	0x1000	/* Level 1 enabled */
#घोषणा	HIFN_PUSTAT_ENA_0	0x3000	/* Level 0 enabled */
#घोषणा	HIFN_PUSTAT_REV_2	0x0020	/* 7751 PT6/2 */
#घोषणा	HIFN_PUSTAT_REV_3	0x0030	/* 7751 PT6/3 */

/* FIFO Status Register (HIFN_0_FIFOSTAT) */
#घोषणा	HIFN_FIFOSTAT_SRC	0x7f00	/* Source FIFO available */
#घोषणा	HIFN_FIFOSTAT_DST	0x007f	/* Destination FIFO available */

/* FIFO Configuration Register (HIFN_0_FIFOCNFG) */
#घोषणा	HIFN_FIFOCNFG_THRESHOLD	0x0400	/* must be written as 1 */

/*
 * DMA Interface Registers (offset from BASEREG1)
 */
#घोषणा	HIFN_1_DMA_CRAR		0x0c	/* DMA Command Ring Address */
#घोषणा	HIFN_1_DMA_SRAR		0x1c	/* DMA Source Ring Address */
#घोषणा	HIFN_1_DMA_RRAR		0x2c	/* DMA Result Ring Address */
#घोषणा	HIFN_1_DMA_DRAR		0x3c	/* DMA Destination Ring Address */
#घोषणा	HIFN_1_DMA_CSR		0x40	/* DMA Status and Control */
#घोषणा	HIFN_1_DMA_IER		0x44	/* DMA Interrupt Enable */
#घोषणा	HIFN_1_DMA_CNFG		0x48	/* DMA Configuration */
#घोषणा	HIFN_1_PLL		0x4c	/* 795x: PLL config */
#घोषणा	HIFN_1_7811_RNGENA	0x60	/* 7811: rng enable */
#घोषणा	HIFN_1_7811_RNGCFG	0x64	/* 7811: rng config */
#घोषणा	HIFN_1_7811_RNGDAT	0x68	/* 7811: rng data */
#घोषणा	HIFN_1_7811_RNGSTS	0x6c	/* 7811: rng status */
#घोषणा	HIFN_1_7811_MIPSRST	0x94	/* 7811: MIPS reset */
#घोषणा	HIFN_1_REVID		0x98	/* Revision ID */
#घोषणा	HIFN_1_UNLOCK_SECRET1	0xf4
#घोषणा	HIFN_1_UNLOCK_SECRET2	0xfc
#घोषणा	HIFN_1_PUB_RESET	0x204	/* Public/RNG Reset */
#घोषणा	HIFN_1_PUB_BASE		0x300	/* Public Base Address */
#घोषणा	HIFN_1_PUB_OPLEN	0x304	/* Public Opeअक्रम Length */
#घोषणा	HIFN_1_PUB_OP		0x308	/* Public Opeअक्रम */
#घोषणा	HIFN_1_PUB_STATUS	0x30c	/* Public Status */
#घोषणा	HIFN_1_PUB_IEN		0x310	/* Public Interrupt enable */
#घोषणा	HIFN_1_RNG_CONFIG	0x314	/* RNG config */
#घोषणा	HIFN_1_RNG_DATA		0x318	/* RNG data */
#घोषणा	HIFN_1_PUB_MEM		0x400	/* start of Public key memory */
#घोषणा	HIFN_1_PUB_MEMEND	0xbff	/* end of Public key memory */

/* DMA Status and Control Register (HIFN_1_DMA_CSR) */
#घोषणा	HIFN_DMACSR_D_CTRLMASK	0xc0000000	/* Destinition Ring Control */
#घोषणा	HIFN_DMACSR_D_CTRL_NOP	0x00000000	/* Dest. Control: no-op */
#घोषणा	HIFN_DMACSR_D_CTRL_DIS	0x40000000	/* Dest. Control: disable */
#घोषणा	HIFN_DMACSR_D_CTRL_ENA	0x80000000	/* Dest. Control: enable */
#घोषणा	HIFN_DMACSR_D_ABORT	0x20000000	/* Destinition Ring PCIAbort */
#घोषणा	HIFN_DMACSR_D_DONE	0x10000000	/* Destinition Ring Done */
#घोषणा	HIFN_DMACSR_D_LAST	0x08000000	/* Destinition Ring Last */
#घोषणा	HIFN_DMACSR_D_WAIT	0x04000000	/* Destinition Ring Waiting */
#घोषणा	HIFN_DMACSR_D_OVER	0x02000000	/* Destinition Ring Overflow */
#घोषणा	HIFN_DMACSR_R_CTRL	0x00c00000	/* Result Ring Control */
#घोषणा	HIFN_DMACSR_R_CTRL_NOP	0x00000000	/* Result Control: no-op */
#घोषणा	HIFN_DMACSR_R_CTRL_DIS	0x00400000	/* Result Control: disable */
#घोषणा	HIFN_DMACSR_R_CTRL_ENA	0x00800000	/* Result Control: enable */
#घोषणा	HIFN_DMACSR_R_ABORT	0x00200000	/* Result Ring PCI Abort */
#घोषणा	HIFN_DMACSR_R_DONE	0x00100000	/* Result Ring Done */
#घोषणा	HIFN_DMACSR_R_LAST	0x00080000	/* Result Ring Last */
#घोषणा	HIFN_DMACSR_R_WAIT	0x00040000	/* Result Ring Waiting */
#घोषणा	HIFN_DMACSR_R_OVER	0x00020000	/* Result Ring Overflow */
#घोषणा	HIFN_DMACSR_S_CTRL	0x0000c000	/* Source Ring Control */
#घोषणा	HIFN_DMACSR_S_CTRL_NOP	0x00000000	/* Source Control: no-op */
#घोषणा	HIFN_DMACSR_S_CTRL_DIS	0x00004000	/* Source Control: disable */
#घोषणा	HIFN_DMACSR_S_CTRL_ENA	0x00008000	/* Source Control: enable */
#घोषणा	HIFN_DMACSR_S_ABORT	0x00002000	/* Source Ring PCI Abort */
#घोषणा	HIFN_DMACSR_S_DONE	0x00001000	/* Source Ring Done */
#घोषणा	HIFN_DMACSR_S_LAST	0x00000800	/* Source Ring Last */
#घोषणा	HIFN_DMACSR_S_WAIT	0x00000400	/* Source Ring Waiting */
#घोषणा	HIFN_DMACSR_ILLW	0x00000200	/* Illegal ग_लिखो (7811 only) */
#घोषणा	HIFN_DMACSR_ILLR	0x00000100	/* Illegal पढ़ो (7811 only) */
#घोषणा	HIFN_DMACSR_C_CTRL	0x000000c0	/* Command Ring Control */
#घोषणा	HIFN_DMACSR_C_CTRL_NOP	0x00000000	/* Command Control: no-op */
#घोषणा	HIFN_DMACSR_C_CTRL_DIS	0x00000040	/* Command Control: disable */
#घोषणा	HIFN_DMACSR_C_CTRL_ENA	0x00000080	/* Command Control: enable */
#घोषणा	HIFN_DMACSR_C_ABORT	0x00000020	/* Command Ring PCI Abort */
#घोषणा	HIFN_DMACSR_C_DONE	0x00000010	/* Command Ring Done */
#घोषणा	HIFN_DMACSR_C_LAST	0x00000008	/* Command Ring Last */
#घोषणा	HIFN_DMACSR_C_WAIT	0x00000004	/* Command Ring Waiting */
#घोषणा	HIFN_DMACSR_PUBDONE	0x00000002	/* Public op करोne (7951 only) */
#घोषणा	HIFN_DMACSR_ENGINE	0x00000001	/* Command Ring Engine IRQ */

/* DMA Interrupt Enable Register (HIFN_1_DMA_IER) */
#घोषणा	HIFN_DMAIER_D_ABORT	0x20000000	/* Destination Ring PCIAbort */
#घोषणा	HIFN_DMAIER_D_DONE	0x10000000	/* Destination Ring Done */
#घोषणा	HIFN_DMAIER_D_LAST	0x08000000	/* Destination Ring Last */
#घोषणा	HIFN_DMAIER_D_WAIT	0x04000000	/* Destination Ring Waiting */
#घोषणा	HIFN_DMAIER_D_OVER	0x02000000	/* Destination Ring Overflow */
#घोषणा	HIFN_DMAIER_R_ABORT	0x00200000	/* Result Ring PCI Abort */
#घोषणा	HIFN_DMAIER_R_DONE	0x00100000	/* Result Ring Done */
#घोषणा	HIFN_DMAIER_R_LAST	0x00080000	/* Result Ring Last */
#घोषणा	HIFN_DMAIER_R_WAIT	0x00040000	/* Result Ring Waiting */
#घोषणा	HIFN_DMAIER_R_OVER	0x00020000	/* Result Ring Overflow */
#घोषणा	HIFN_DMAIER_S_ABORT	0x00002000	/* Source Ring PCI Abort */
#घोषणा	HIFN_DMAIER_S_DONE	0x00001000	/* Source Ring Done */
#घोषणा	HIFN_DMAIER_S_LAST	0x00000800	/* Source Ring Last */
#घोषणा	HIFN_DMAIER_S_WAIT	0x00000400	/* Source Ring Waiting */
#घोषणा	HIFN_DMAIER_ILLW	0x00000200	/* Illegal ग_लिखो (7811 only) */
#घोषणा	HIFN_DMAIER_ILLR	0x00000100	/* Illegal पढ़ो (7811 only) */
#घोषणा	HIFN_DMAIER_C_ABORT	0x00000020	/* Command Ring PCI Abort */
#घोषणा	HIFN_DMAIER_C_DONE	0x00000010	/* Command Ring Done */
#घोषणा	HIFN_DMAIER_C_LAST	0x00000008	/* Command Ring Last */
#घोषणा	HIFN_DMAIER_C_WAIT	0x00000004	/* Command Ring Waiting */
#घोषणा	HIFN_DMAIER_PUBDONE	0x00000002	/* खुला op करोne (7951 only) */
#घोषणा	HIFN_DMAIER_ENGINE	0x00000001	/* Engine IRQ */

/* DMA Configuration Register (HIFN_1_DMA_CNFG) */
#घोषणा	HIFN_DMACNFG_BIGENDIAN	0x10000000	/* big endian mode */
#घोषणा	HIFN_DMACNFG_POLLFREQ	0x00ff0000	/* Poll frequency mask */
#घोषणा	HIFN_DMACNFG_UNLOCK	0x00000800
#घोषणा	HIFN_DMACNFG_POLLINVAL	0x00000700	/* Invalid Poll Scalar */
#घोषणा	HIFN_DMACNFG_LAST	0x00000010	/* Host control LAST bit */
#घोषणा	HIFN_DMACNFG_MODE	0x00000004	/* DMA mode */
#घोषणा	HIFN_DMACNFG_DMARESET	0x00000002	/* DMA Reset # */
#घोषणा	HIFN_DMACNFG_MSTRESET	0x00000001	/* Master Reset # */

/* PLL configuration रेजिस्टर */
#घोषणा HIFN_PLL_REF_CLK_HBI	0x00000000	/* HBI reference घड़ी */
#घोषणा HIFN_PLL_REF_CLK_PLL	0x00000001	/* PLL reference घड़ी */
#घोषणा HIFN_PLL_BP		0x00000002	/* Reference घड़ी bypass */
#घोषणा HIFN_PLL_PK_CLK_HBI	0x00000000	/* PK engine HBI घड़ी */
#घोषणा HIFN_PLL_PK_CLK_PLL	0x00000008	/* PK engine PLL घड़ी */
#घोषणा HIFN_PLL_PE_CLK_HBI	0x00000000	/* PE engine HBI घड़ी */
#घोषणा HIFN_PLL_PE_CLK_PLL	0x00000010	/* PE engine PLL घड़ी */
#घोषणा HIFN_PLL_RESERVED_1	0x00000400	/* Reserved bit, must be 1 */
#घोषणा HIFN_PLL_ND_SHIFT	11		/* Clock multiplier shअगरt */
#घोषणा HIFN_PLL_ND_MULT_2	0x00000000	/* PLL घड़ी multiplier 2 */
#घोषणा HIFN_PLL_ND_MULT_4	0x00000800	/* PLL घड़ी multiplier 4 */
#घोषणा HIFN_PLL_ND_MULT_6	0x00001000	/* PLL घड़ी multiplier 6 */
#घोषणा HIFN_PLL_ND_MULT_8	0x00001800	/* PLL घड़ी multiplier 8 */
#घोषणा HIFN_PLL_ND_MULT_10	0x00002000	/* PLL घड़ी multiplier 10 */
#घोषणा HIFN_PLL_ND_MULT_12	0x00002800	/* PLL घड़ी multiplier 12 */
#घोषणा HIFN_PLL_IS_1_8		0x00000000	/* अक्षरge pump (mult. 1-8) */
#घोषणा HIFN_PLL_IS_9_12	0x00010000	/* अक्षरge pump (mult. 9-12) */

#घोषणा HIFN_PLL_FCK_MAX	266		/* Maximum PLL frequency */

/* Public key reset रेजिस्टर (HIFN_1_PUB_RESET) */
#घोषणा	HIFN_PUBRST_RESET	0x00000001	/* reset खुला/rng unit */

/* Public base address रेजिस्टर (HIFN_1_PUB_BASE) */
#घोषणा	HIFN_PUBBASE_ADDR	0x00003fff	/* base address */

/* Public opeअक्रम length रेजिस्टर (HIFN_1_PUB_OPLEN) */
#घोषणा	HIFN_PUBOPLEN_MOD_M	0x0000007f	/* modulus length mask */
#घोषणा	HIFN_PUBOPLEN_MOD_S	0		/* modulus length shअगरt */
#घोषणा	HIFN_PUBOPLEN_EXP_M	0x0003ff80	/* exponent length mask */
#घोषणा	HIFN_PUBOPLEN_EXP_S	7		/* exponent length shअगरt */
#घोषणा	HIFN_PUBOPLEN_RED_M	0x003c0000	/* reducend length mask */
#घोषणा	HIFN_PUBOPLEN_RED_S	18		/* reducend length shअगरt */

/* Public operation रेजिस्टर (HIFN_1_PUB_OP) */
#घोषणा	HIFN_PUBOP_AOFFSET_M	0x0000007f	/* A offset mask */
#घोषणा	HIFN_PUBOP_AOFFSET_S	0		/* A offset shअगरt */
#घोषणा	HIFN_PUBOP_BOFFSET_M	0x00000f80	/* B offset mask */
#घोषणा	HIFN_PUBOP_BOFFSET_S	7		/* B offset shअगरt */
#घोषणा	HIFN_PUBOP_MOFFSET_M	0x0003f000	/* M offset mask */
#घोषणा	HIFN_PUBOP_MOFFSET_S	12		/* M offset shअगरt */
#घोषणा	HIFN_PUBOP_OP_MASK	0x003c0000	/* Opcode: */
#घोषणा	HIFN_PUBOP_OP_NOP	0x00000000	/*  NOP */
#घोषणा	HIFN_PUBOP_OP_ADD	0x00040000	/*  ADD */
#घोषणा	HIFN_PUBOP_OP_ADDC	0x00080000	/*  ADD w/carry */
#घोषणा	HIFN_PUBOP_OP_SUB	0x000c0000	/*  SUB */
#घोषणा	HIFN_PUBOP_OP_SUBC	0x00100000	/*  SUB w/carry */
#घोषणा	HIFN_PUBOP_OP_MODADD	0x00140000	/*  Modular ADD */
#घोषणा	HIFN_PUBOP_OP_MODSUB	0x00180000	/*  Modular SUB */
#घोषणा	HIFN_PUBOP_OP_INCA	0x001c0000	/*  INC A */
#घोषणा	HIFN_PUBOP_OP_DECA	0x00200000	/*  DEC A */
#घोषणा	HIFN_PUBOP_OP_MULT	0x00240000	/*  MULT */
#घोषणा	HIFN_PUBOP_OP_MODMULT	0x00280000	/*  Modular MULT */
#घोषणा	HIFN_PUBOP_OP_MODRED	0x002c0000	/*  Modular RED */
#घोषणा	HIFN_PUBOP_OP_MODEXP	0x00300000	/*  Modular EXP */

/* Public status रेजिस्टर (HIFN_1_PUB_STATUS) */
#घोषणा	HIFN_PUBSTS_DONE	0x00000001	/* operation करोne */
#घोषणा	HIFN_PUBSTS_CARRY	0x00000002	/* carry */

/* Public पूर्णांकerrupt enable रेजिस्टर (HIFN_1_PUB_IEN) */
#घोषणा	HIFN_PUBIEN_DONE	0x00000001	/* operation करोne पूर्णांकerrupt */

/* Ranकरोm number generator config रेजिस्टर (HIFN_1_RNG_CONFIG) */
#घोषणा	HIFN_RNGCFG_ENA		0x00000001	/* enable rng */

#घोषणा HIFN_NAMESIZE			32
#घोषणा HIFN_MAX_RESULT_ORDER		5

#घोषणा	HIFN_D_CMD_RSIZE		(24 * 1)
#घोषणा	HIFN_D_SRC_RSIZE		(80 * 1)
#घोषणा	HIFN_D_DST_RSIZE		(80 * 1)
#घोषणा	HIFN_D_RES_RSIZE		(24 * 1)

#घोषणा HIFN_D_DST_DALIGN		4

#घोषणा HIFN_QUEUE_LENGTH		(HIFN_D_CMD_RSIZE - 1)

#घोषणा AES_MIN_KEY_SIZE		16
#घोषणा AES_MAX_KEY_SIZE		32

#घोषणा HIFN_DES_KEY_LENGTH		8
#घोषणा HIFN_3DES_KEY_LENGTH		24
#घोषणा HIFN_MAX_CRYPT_KEY_LENGTH	AES_MAX_KEY_SIZE
#घोषणा HIFN_IV_LENGTH			8
#घोषणा HIFN_AES_IV_LENGTH		16
#घोषणा	HIFN_MAX_IV_LENGTH		HIFN_AES_IV_LENGTH

#घोषणा HIFN_MAC_KEY_LENGTH		64
#घोषणा HIFN_MD5_LENGTH			16
#घोषणा HIFN_SHA1_LENGTH		20
#घोषणा HIFN_MAC_TRUNC_LENGTH		12

#घोषणा	HIFN_MAX_COMMAND		(8 + 8 + 8 + 64 + 260)
#घोषणा	HIFN_MAX_RESULT			(8 + 4 + 4 + 20 + 4)
#घोषणा HIFN_USED_RESULT		12

काष्ठा hअगरn_desc अणु
	अस्थिर __le32		l;
	अस्थिर __le32		p;
पूर्ण;

काष्ठा hअगरn_dma अणु
	काष्ठा hअगरn_desc	cmdr[HIFN_D_CMD_RSIZE + 1];
	काष्ठा hअगरn_desc	srcr[HIFN_D_SRC_RSIZE + 1];
	काष्ठा hअगरn_desc	dstr[HIFN_D_DST_RSIZE + 1];
	काष्ठा hअगरn_desc	resr[HIFN_D_RES_RSIZE + 1];

	u8			command_bufs[HIFN_D_CMD_RSIZE][HIFN_MAX_COMMAND];
	u8			result_bufs[HIFN_D_CMD_RSIZE][HIFN_MAX_RESULT];

	/*
	 *  Our current positions क्रम insertion and removal from the descriptor
	 *  rings.
	 */
	अस्थिर पूर्णांक		cmdi, srci, dsti, resi;
	अस्थिर पूर्णांक		cmdu, srcu, dstu, resu;
	पूर्णांक			cmdk, srck, dstk, resk;
पूर्ण;

#घोषणा HIFN_FLAG_CMD_BUSY	(1 << 0)
#घोषणा HIFN_FLAG_SRC_BUSY	(1 << 1)
#घोषणा HIFN_FLAG_DST_BUSY	(1 << 2)
#घोषणा HIFN_FLAG_RES_BUSY	(1 << 3)
#घोषणा HIFN_FLAG_OLD_KEY	(1 << 4)

#घोषणा HIFN_DEFAULT_ACTIVE_NUM	5

काष्ठा hअगरn_device अणु
	अक्षर			name[HIFN_NAMESIZE];

	पूर्णांक			irq;

	काष्ठा pci_dev		*pdev;
	व्योम __iomem		*bar[3];

	व्योम			*desc_virt;
	dma_addr_t		desc_dma;

	u32			dmareg;

	व्योम			*sa[HIFN_D_RES_RSIZE];

	spinlock_t		lock;

	u32			flags;
	पूर्णांक			active, started;
	काष्ठा delayed_work	work;
	अचिन्हित दीर्घ		reset;
	अचिन्हित दीर्घ		success;
	अचिन्हित दीर्घ		prev_success;

	u8			snum;

	काष्ठा tasklet_काष्ठा	tasklet;

	काष्ठा crypto_queue	queue;
	काष्ठा list_head	alg_list;

	अचिन्हित पूर्णांक		pk_clk_freq;

#अगर_घोषित CONFIG_CRYPTO_DEV_HIFN_795X_RNG
	अचिन्हित पूर्णांक		rng_रुको_समय;
	kसमय_प्रकार			rngसमय;
	काष्ठा hwrng		rng;
#पूर्ण_अगर
पूर्ण;

#घोषणा	HIFN_D_LENGTH			0x0000ffff
#घोषणा	HIFN_D_NOINVALID		0x01000000
#घोषणा	HIFN_D_MASKDONEIRQ		0x02000000
#घोषणा	HIFN_D_DESTOVER			0x04000000
#घोषणा	HIFN_D_OVER			0x08000000
#घोषणा	HIFN_D_LAST			0x20000000
#घोषणा	HIFN_D_JUMP			0x40000000
#घोषणा	HIFN_D_VALID			0x80000000

काष्ठा hअगरn_base_command अणु
	अस्थिर __le16		masks;
	अस्थिर __le16		session_num;
	अस्थिर __le16		total_source_count;
	अस्थिर __le16		total_dest_count;
पूर्ण;

#घोषणा	HIFN_BASE_CMD_COMP		0x0100	/* enable compression engine */
#घोषणा	HIFN_BASE_CMD_PAD		0x0200	/* enable padding engine */
#घोषणा	HIFN_BASE_CMD_MAC		0x0400	/* enable MAC engine */
#घोषणा	HIFN_BASE_CMD_CRYPT		0x0800	/* enable crypt engine */
#घोषणा	HIFN_BASE_CMD_DECODE		0x2000
#घोषणा	HIFN_BASE_CMD_SRCLEN_M		0xc000
#घोषणा	HIFN_BASE_CMD_SRCLEN_S		14
#घोषणा	HIFN_BASE_CMD_DSTLEN_M		0x3000
#घोषणा	HIFN_BASE_CMD_DSTLEN_S		12
#घोषणा	HIFN_BASE_CMD_LENMASK_HI	0x30000
#घोषणा	HIFN_BASE_CMD_LENMASK_LO	0x0ffff

/*
 * Structure to help build up the command data काष्ठाure.
 */
काष्ठा hअगरn_crypt_command अणु
	अस्थिर __le16		masks;
	अस्थिर __le16		header_skip;
	अस्थिर __le16		source_count;
	अस्थिर __le16		reserved;
पूर्ण;

#घोषणा	HIFN_CRYPT_CMD_ALG_MASK		0x0003		/* algorithm: */
#घोषणा	HIFN_CRYPT_CMD_ALG_DES		0x0000		/*   DES */
#घोषणा	HIFN_CRYPT_CMD_ALG_3DES		0x0001		/*   3DES */
#घोषणा	HIFN_CRYPT_CMD_ALG_RC4		0x0002		/*   RC4 */
#घोषणा	HIFN_CRYPT_CMD_ALG_AES		0x0003		/*   AES */
#घोषणा	HIFN_CRYPT_CMD_MODE_MASK	0x0018		/* Encrypt mode: */
#घोषणा	HIFN_CRYPT_CMD_MODE_ECB		0x0000		/*   ECB */
#घोषणा	HIFN_CRYPT_CMD_MODE_CBC		0x0008		/*   CBC */
#घोषणा	HIFN_CRYPT_CMD_MODE_CFB		0x0010		/*   CFB */
#घोषणा	HIFN_CRYPT_CMD_MODE_OFB		0x0018		/*   OFB */
#घोषणा	HIFN_CRYPT_CMD_CLR_CTX		0x0040		/* clear context */
#घोषणा	HIFN_CRYPT_CMD_KSZ_MASK		0x0600		/* AES key size: */
#घोषणा	HIFN_CRYPT_CMD_KSZ_128		0x0000		/*  128 bit */
#घोषणा	HIFN_CRYPT_CMD_KSZ_192		0x0200		/*  192 bit */
#घोषणा	HIFN_CRYPT_CMD_KSZ_256		0x0400		/*  256 bit */
#घोषणा	HIFN_CRYPT_CMD_NEW_KEY		0x0800		/* expect new key */
#घोषणा	HIFN_CRYPT_CMD_NEW_IV		0x1000		/* expect new iv */
#घोषणा	HIFN_CRYPT_CMD_SRCLEN_M		0xc000
#घोषणा	HIFN_CRYPT_CMD_SRCLEN_S		14

/*
 * Structure to help build up the command data काष्ठाure.
 */
काष्ठा hअगरn_mac_command अणु
	अस्थिर __le16	masks;
	अस्थिर __le16	header_skip;
	अस्थिर __le16	source_count;
	अस्थिर __le16	reserved;
पूर्ण;

#घोषणा	HIFN_MAC_CMD_ALG_MASK		0x0001
#घोषणा	HIFN_MAC_CMD_ALG_SHA1		0x0000
#घोषणा	HIFN_MAC_CMD_ALG_MD5		0x0001
#घोषणा	HIFN_MAC_CMD_MODE_MASK		0x000c
#घोषणा	HIFN_MAC_CMD_MODE_HMAC		0x0000
#घोषणा	HIFN_MAC_CMD_MODE_SSL_MAC	0x0004
#घोषणा	HIFN_MAC_CMD_MODE_HASH		0x0008
#घोषणा	HIFN_MAC_CMD_MODE_FULL		0x0004
#घोषणा	HIFN_MAC_CMD_TRUNC		0x0010
#घोषणा	HIFN_MAC_CMD_RESULT		0x0020
#घोषणा	HIFN_MAC_CMD_APPEND		0x0040
#घोषणा	HIFN_MAC_CMD_SRCLEN_M		0xc000
#घोषणा	HIFN_MAC_CMD_SRCLEN_S		14

/*
 * MAC POS IPsec initiates authentication after encryption on encodes
 * and beक्रमe decryption on decodes.
 */
#घोषणा	HIFN_MAC_CMD_POS_IPSEC		0x0200
#घोषणा	HIFN_MAC_CMD_NEW_KEY		0x0800

काष्ठा hअगरn_comp_command अणु
	अस्थिर __le16		masks;
	अस्थिर __le16		header_skip;
	अस्थिर __le16		source_count;
	अस्थिर __le16		reserved;
पूर्ण;

#घोषणा	HIFN_COMP_CMD_SRCLEN_M		0xc000
#घोषणा	HIFN_COMP_CMD_SRCLEN_S		14
#घोषणा	HIFN_COMP_CMD_ONE		0x0100	/* must be one */
#घोषणा	HIFN_COMP_CMD_CLEARHIST		0x0010	/* clear history */
#घोषणा	HIFN_COMP_CMD_UPDATEHIST	0x0008	/* update history */
#घोषणा	HIFN_COMP_CMD_LZS_STRIP0	0x0004	/* LZS: strip zero */
#घोषणा	HIFN_COMP_CMD_MPPC_RESTART	0x0004	/* MPPC: restart */
#घोषणा	HIFN_COMP_CMD_ALG_MASK		0x0001	/* compression mode: */
#घोषणा	HIFN_COMP_CMD_ALG_MPPC		0x0001	/*   MPPC */
#घोषणा	HIFN_COMP_CMD_ALG_LZS		0x0000	/*   LZS */

काष्ठा hअगरn_base_result अणु
	अस्थिर __le16		flags;
	अस्थिर __le16		session;
	अस्थिर __le16		src_cnt;		/* 15:0 of source count */
	अस्थिर __le16		dst_cnt;		/* 15:0 of dest count */
पूर्ण;

#घोषणा	HIFN_BASE_RES_DSTOVERRUN	0x0200	/* destination overrun */
#घोषणा	HIFN_BASE_RES_SRCLEN_M		0xc000	/* 17:16 of source count */
#घोषणा	HIFN_BASE_RES_SRCLEN_S		14
#घोषणा	HIFN_BASE_RES_DSTLEN_M		0x3000	/* 17:16 of dest count */
#घोषणा	HIFN_BASE_RES_DSTLEN_S		12

काष्ठा hअगरn_comp_result अणु
	अस्थिर __le16		flags;
	अस्थिर __le16		crc;
पूर्ण;

#घोषणा	HIFN_COMP_RES_LCB_M		0xff00	/* दीर्घitudinal check byte */
#घोषणा	HIFN_COMP_RES_LCB_S		8
#घोषणा	HIFN_COMP_RES_RESTART		0x0004	/* MPPC: restart */
#घोषणा	HIFN_COMP_RES_ENDMARKER		0x0002	/* LZS: end marker seen */
#घोषणा	HIFN_COMP_RES_SRC_NOTZERO	0x0001	/* source expired */

काष्ठा hअगरn_mac_result अणु
	अस्थिर __le16		flags;
	अस्थिर __le16		reserved;
	/* followed by 0, 6, 8, or 10 u16's of the MAC, then crypt */
पूर्ण;

#घोषणा	HIFN_MAC_RES_MISCOMPARE		0x0002	/* compare failed */
#घोषणा	HIFN_MAC_RES_SRC_NOTZERO	0x0001	/* source expired */

काष्ठा hअगरn_crypt_result अणु
	अस्थिर __le16		flags;
	अस्थिर __le16		reserved;
पूर्ण;

#घोषणा	HIFN_CRYPT_RES_SRC_NOTZERO	0x0001	/* source expired */

#अगर_अघोषित HIFN_POLL_FREQUENCY
#घोषणा	HIFN_POLL_FREQUENCY	0x1
#पूर्ण_अगर

#अगर_अघोषित HIFN_POLL_SCALAR
#घोषणा	HIFN_POLL_SCALAR	0x0
#पूर्ण_अगर

#घोषणा	HIFN_MAX_SEGLEN		0xffff		/* maximum dma segment len */
#घोषणा	HIFN_MAX_DMALEN		0x3ffff		/* maximum dma length */

काष्ठा hअगरn_crypto_alg अणु
	काष्ठा list_head	entry;
	काष्ठा skcipher_alg	alg;
	काष्ठा hअगरn_device	*dev;
पूर्ण;

#घोषणा ASYNC_SCATTERLIST_CACHE	16

#घोषणा ASYNC_FLAGS_MISALIGNED	(1 << 0)

काष्ठा hअगरn_cipher_walk अणु
	काष्ठा scatterlist	cache[ASYNC_SCATTERLIST_CACHE];
	u32			flags;
	पूर्णांक			num;
पूर्ण;

काष्ठा hअगरn_context अणु
	u8			key[HIFN_MAX_CRYPT_KEY_LENGTH];
	काष्ठा hअगरn_device	*dev;
	अचिन्हित पूर्णांक		keysize;
पूर्ण;

काष्ठा hअगरn_request_context अणु
	u8			*iv;
	अचिन्हित पूर्णांक		ivsize;
	u8			op, type, mode, unused;
	काष्ठा hअगरn_cipher_walk	walk;
पूर्ण;

#घोषणा crypto_alg_to_hअगरn(a)	container_of(a, काष्ठा hअगरn_crypto_alg, alg)

अटल अंतरभूत u32 hअगरn_पढ़ो_0(काष्ठा hअगरn_device *dev, u32 reg)
अणु
	वापस पढ़ोl(dev->bar[0] + reg);
पूर्ण

अटल अंतरभूत u32 hअगरn_पढ़ो_1(काष्ठा hअगरn_device *dev, u32 reg)
अणु
	वापस पढ़ोl(dev->bar[1] + reg);
पूर्ण

अटल अंतरभूत व्योम hअगरn_ग_लिखो_0(काष्ठा hअगरn_device *dev, u32 reg, u32 val)
अणु
	ग_लिखोl((__क्रमce u32)cpu_to_le32(val), dev->bar[0] + reg);
पूर्ण

अटल अंतरभूत व्योम hअगरn_ग_लिखो_1(काष्ठा hअगरn_device *dev, u32 reg, u32 val)
अणु
	ग_लिखोl((__क्रमce u32)cpu_to_le32(val), dev->bar[1] + reg);
पूर्ण

अटल व्योम hअगरn_रुको_puc(काष्ठा hअगरn_device *dev)
अणु
	पूर्णांक i;
	u32 ret;

	क्रम (i = 10000; i > 0; --i) अणु
		ret = hअगरn_पढ़ो_0(dev, HIFN_0_PUCTRL);
		अगर (!(ret & HIFN_PUCTRL_RESET))
			अवरोध;

		udelay(1);
	पूर्ण

	अगर (!i)
		dev_err(&dev->pdev->dev, "Failed to reset PUC unit.\n");
पूर्ण

अटल व्योम hअगरn_reset_puc(काष्ठा hअगरn_device *dev)
अणु
	hअगरn_ग_लिखो_0(dev, HIFN_0_PUCTRL, HIFN_PUCTRL_DMAENA);
	hअगरn_रुको_puc(dev);
पूर्ण

अटल व्योम hअगरn_stop_device(काष्ठा hअगरn_device *dev)
अणु
	hअगरn_ग_लिखो_1(dev, HIFN_1_DMA_CSR,
		HIFN_DMACSR_D_CTRL_DIS | HIFN_DMACSR_R_CTRL_DIS |
		HIFN_DMACSR_S_CTRL_DIS | HIFN_DMACSR_C_CTRL_DIS);
	hअगरn_ग_लिखो_0(dev, HIFN_0_PUIER, 0);
	hअगरn_ग_लिखो_1(dev, HIFN_1_DMA_IER, 0);
पूर्ण

अटल व्योम hअगरn_reset_dma(काष्ठा hअगरn_device *dev, पूर्णांक full)
अणु
	hअगरn_stop_device(dev);

	/*
	 * Setting poll frequency and others to 0.
	 */
	hअगरn_ग_लिखो_1(dev, HIFN_1_DMA_CNFG, HIFN_DMACNFG_MSTRESET |
			HIFN_DMACNFG_DMARESET | HIFN_DMACNFG_MODE);
	mdelay(1);

	/*
	 * Reset DMA.
	 */
	अगर (full) अणु
		hअगरn_ग_लिखो_1(dev, HIFN_1_DMA_CNFG, HIFN_DMACNFG_MODE);
		mdelay(1);
	पूर्ण अन्यथा अणु
		hअगरn_ग_लिखो_1(dev, HIFN_1_DMA_CNFG, HIFN_DMACNFG_MODE |
				HIFN_DMACNFG_MSTRESET);
		hअगरn_reset_puc(dev);
	पूर्ण

	hअगरn_ग_लिखो_1(dev, HIFN_1_DMA_CNFG, HIFN_DMACNFG_MSTRESET |
			HIFN_DMACNFG_DMARESET | HIFN_DMACNFG_MODE);

	hअगरn_reset_puc(dev);
पूर्ण

अटल u32 hअगरn_next_signature(u32 a, u_पूर्णांक cnt)
अणु
	पूर्णांक i;
	u32 v;

	क्रम (i = 0; i < cnt; i++) अणु
		/* get the parity */
		v = a & 0x80080125;
		v ^= v >> 16;
		v ^= v >> 8;
		v ^= v >> 4;
		v ^= v >> 2;
		v ^= v >> 1;

		a = (v & 1) ^ (a << 1);
	पूर्ण

	वापस a;
पूर्ण

अटल काष्ठा pci2id अणु
	u_लघु		pci_venकरोr;
	u_लघु		pci_prod;
	अक्षर		card_id[13];
पूर्ण pci2id[] = अणु
	अणु
		PCI_VENDOR_ID_HIFN,
		PCI_DEVICE_ID_HIFN_7955,
		अणु 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		  0x00, 0x00, 0x00, 0x00, 0x00 पूर्ण
	पूर्ण,
	अणु
		PCI_VENDOR_ID_HIFN,
		PCI_DEVICE_ID_HIFN_7956,
		अणु 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		  0x00, 0x00, 0x00, 0x00, 0x00 पूर्ण
	पूर्ण
पूर्ण;

#अगर_घोषित CONFIG_CRYPTO_DEV_HIFN_795X_RNG
अटल पूर्णांक hअगरn_rng_data_present(काष्ठा hwrng *rng, पूर्णांक रुको)
अणु
	काष्ठा hअगरn_device *dev = (काष्ठा hअगरn_device *)rng->priv;
	s64 nsec;

	nsec = kसमय_प्रकारo_ns(kसमय_sub(kसमय_get(), dev->rngसमय));
	nsec -= dev->rng_रुको_समय;
	अगर (nsec <= 0)
		वापस 1;
	अगर (!रुको)
		वापस 0;
	ndelay(nsec);
	वापस 1;
पूर्ण

अटल पूर्णांक hअगरn_rng_data_पढ़ो(काष्ठा hwrng *rng, u32 *data)
अणु
	काष्ठा hअगरn_device *dev = (काष्ठा hअगरn_device *)rng->priv;

	*data = hअगरn_पढ़ो_1(dev, HIFN_1_RNG_DATA);
	dev->rngसमय = kसमय_get();
	वापस 4;
पूर्ण

अटल पूर्णांक hअगरn_रेजिस्टर_rng(काष्ठा hअगरn_device *dev)
अणु
	/*
	 * We must रुको at least 256 Pk_clk cycles between two पढ़ोs of the rng.
	 */
	dev->rng_रुको_समय	= DIV_ROUND_UP_ULL(NSEC_PER_SEC,
						   dev->pk_clk_freq) * 256;

	dev->rng.name		= dev->name;
	dev->rng.data_present	= hअगरn_rng_data_present;
	dev->rng.data_पढ़ो	= hअगरn_rng_data_पढ़ो;
	dev->rng.priv		= (अचिन्हित दीर्घ)dev;

	वापस hwrng_रेजिस्टर(&dev->rng);
पूर्ण

अटल व्योम hअगरn_unरेजिस्टर_rng(काष्ठा hअगरn_device *dev)
अणु
	hwrng_unरेजिस्टर(&dev->rng);
पूर्ण
#अन्यथा
#घोषणा hअगरn_रेजिस्टर_rng(dev)		0
#घोषणा hअगरn_unरेजिस्टर_rng(dev)
#पूर्ण_अगर

अटल पूर्णांक hअगरn_init_pubrng(काष्ठा hअगरn_device *dev)
अणु
	पूर्णांक i;

	hअगरn_ग_लिखो_1(dev, HIFN_1_PUB_RESET, hअगरn_पढ़ो_1(dev, HIFN_1_PUB_RESET) |
			HIFN_PUBRST_RESET);

	क्रम (i = 100; i > 0; --i) अणु
		mdelay(1);

		अगर ((hअगरn_पढ़ो_1(dev, HIFN_1_PUB_RESET) & HIFN_PUBRST_RESET) == 0)
			अवरोध;
	पूर्ण

	अगर (!i) अणु
		dev_err(&dev->pdev->dev, "Failed to initialise public key engine.\n");
	पूर्ण अन्यथा अणु
		hअगरn_ग_लिखो_1(dev, HIFN_1_PUB_IEN, HIFN_PUBIEN_DONE);
		dev->dmareg |= HIFN_DMAIER_PUBDONE;
		hअगरn_ग_लिखो_1(dev, HIFN_1_DMA_IER, dev->dmareg);

		dev_dbg(&dev->pdev->dev, "Public key engine has been successfully initialised.\n");
	पूर्ण

	/* Enable RNG engine. */

	hअगरn_ग_लिखो_1(dev, HIFN_1_RNG_CONFIG,
			hअगरn_पढ़ो_1(dev, HIFN_1_RNG_CONFIG) | HIFN_RNGCFG_ENA);
	dev_dbg(&dev->pdev->dev, "RNG engine has been successfully initialised.\n");

#अगर_घोषित CONFIG_CRYPTO_DEV_HIFN_795X_RNG
	/* First value must be discarded */
	hअगरn_पढ़ो_1(dev, HIFN_1_RNG_DATA);
	dev->rngसमय = kसमय_get();
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक hअगरn_enable_crypto(काष्ठा hअगरn_device *dev)
अणु
	u32 dmacfg, addr;
	अक्षर *offtbl = शून्य;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(pci2id); i++) अणु
		अगर (pci2id[i].pci_venकरोr == dev->pdev->venकरोr &&
				pci2id[i].pci_prod == dev->pdev->device) अणु
			offtbl = pci2id[i].card_id;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!offtbl) अणु
		dev_err(&dev->pdev->dev, "Unknown card!\n");
		वापस -ENODEV;
	पूर्ण

	dmacfg = hअगरn_पढ़ो_1(dev, HIFN_1_DMA_CNFG);

	hअगरn_ग_लिखो_1(dev, HIFN_1_DMA_CNFG,
			HIFN_DMACNFG_UNLOCK | HIFN_DMACNFG_MSTRESET |
			HIFN_DMACNFG_DMARESET | HIFN_DMACNFG_MODE);
	mdelay(1);
	addr = hअगरn_पढ़ो_1(dev, HIFN_1_UNLOCK_SECRET1);
	mdelay(1);
	hअगरn_ग_लिखो_1(dev, HIFN_1_UNLOCK_SECRET2, 0);
	mdelay(1);

	क्रम (i = 0; i < 12; ++i) अणु
		addr = hअगरn_next_signature(addr, offtbl[i] + 0x101);
		hअगरn_ग_लिखो_1(dev, HIFN_1_UNLOCK_SECRET2, addr);

		mdelay(1);
	पूर्ण
	hअगरn_ग_लिखो_1(dev, HIFN_1_DMA_CNFG, dmacfg);

	dev_dbg(&dev->pdev->dev, "%s %s.\n", dev->name, pci_name(dev->pdev));

	वापस 0;
पूर्ण

अटल व्योम hअगरn_init_dma(काष्ठा hअगरn_device *dev)
अणु
	काष्ठा hअगरn_dma *dma = (काष्ठा hअगरn_dma *)dev->desc_virt;
	u32 dptr = dev->desc_dma;
	पूर्णांक i;

	क्रम (i = 0; i < HIFN_D_CMD_RSIZE; ++i)
		dma->cmdr[i].p = __cpu_to_le32(dptr +
				दुरत्व(काष्ठा hअगरn_dma, command_bufs[i][0]));
	क्रम (i = 0; i < HIFN_D_RES_RSIZE; ++i)
		dma->resr[i].p = __cpu_to_le32(dptr +
				दुरत्व(काष्ठा hअगरn_dma, result_bufs[i][0]));

	/* Setup LAST descriptors. */
	dma->cmdr[HIFN_D_CMD_RSIZE].p = __cpu_to_le32(dptr +
			दुरत्व(काष्ठा hअगरn_dma, cmdr[0]));
	dma->srcr[HIFN_D_SRC_RSIZE].p = __cpu_to_le32(dptr +
			दुरत्व(काष्ठा hअगरn_dma, srcr[0]));
	dma->dstr[HIFN_D_DST_RSIZE].p = __cpu_to_le32(dptr +
			दुरत्व(काष्ठा hअगरn_dma, dstr[0]));
	dma->resr[HIFN_D_RES_RSIZE].p = __cpu_to_le32(dptr +
			दुरत्व(काष्ठा hअगरn_dma, resr[0]));

	dma->cmdu = dma->srcu = dma->dstu = dma->resu = 0;
	dma->cmdi = dma->srci = dma->dsti = dma->resi = 0;
	dma->cmdk = dma->srck = dma->dstk = dma->resk = 0;
पूर्ण

/*
 * Initialize the PLL. We need to know the frequency of the reference घड़ी
 * to calculate the optimal multiplier. For PCI we assume 66MHz, since that
 * allows us to operate without the risk of overघड़ीing the chip. If it
 * actually uses 33MHz, the chip will operate at half the speed, this can be
 * overridden by specअगरying the frequency as module parameter (pci33).
 *
 * Unक्रमtunately the PCI घड़ी is not very suitable since the HIFN needs a
 * stable घड़ी and the PCI घड़ी frequency may vary, so the शेष is the
 * बाह्यal घड़ी. There is no way to find out its frequency, we शेष to
 * 66MHz since according to Mike Ham of HiFn, almost every board in existence
 * has an बाह्यal crystal populated at 66MHz.
 */
अटल व्योम hअगरn_init_pll(काष्ठा hअगरn_device *dev)
अणु
	अचिन्हित पूर्णांक freq, m;
	u32 pllcfg;

	pllcfg = HIFN_1_PLL | HIFN_PLL_RESERVED_1;

	अगर (म_भेदन(hअगरn_pll_ref, "ext", 3) == 0)
		pllcfg |= HIFN_PLL_REF_CLK_PLL;
	अन्यथा
		pllcfg |= HIFN_PLL_REF_CLK_HBI;

	अगर (hअगरn_pll_ref[3] != '\0')
		freq = simple_म_से_अदीर्घ(hअगरn_pll_ref + 3, शून्य, 10);
	अन्यथा अणु
		freq = 66;
		dev_info(&dev->pdev->dev, "assuming %uMHz clock speed, override with hifn_pll_ref=%.3s<frequency>\n",
			 freq, hअगरn_pll_ref);
	पूर्ण

	m = HIFN_PLL_FCK_MAX / freq;

	pllcfg |= (m / 2 - 1) << HIFN_PLL_ND_SHIFT;
	अगर (m <= 8)
		pllcfg |= HIFN_PLL_IS_1_8;
	अन्यथा
		pllcfg |= HIFN_PLL_IS_9_12;

	/* Select घड़ी source and enable घड़ी bypass */
	hअगरn_ग_लिखो_1(dev, HIFN_1_PLL, pllcfg |
		     HIFN_PLL_PK_CLK_HBI | HIFN_PLL_PE_CLK_HBI | HIFN_PLL_BP);

	/* Let the chip lock to the input घड़ी */
	mdelay(10);

	/* Disable घड़ी bypass */
	hअगरn_ग_लिखो_1(dev, HIFN_1_PLL, pllcfg |
		     HIFN_PLL_PK_CLK_HBI | HIFN_PLL_PE_CLK_HBI);

	/* Switch the engines to the PLL */
	hअगरn_ग_लिखो_1(dev, HIFN_1_PLL, pllcfg |
		     HIFN_PLL_PK_CLK_PLL | HIFN_PLL_PE_CLK_PLL);

	/*
	 * The Fpk_clk runs at half the total speed. Its frequency is needed to
	 * calculate the minimum समय between two पढ़ोs of the rng. Since 33MHz
	 * is actually 33.333... we overestimate the frequency here, resulting
	 * in slightly larger पूर्णांकervals.
	 */
	dev->pk_clk_freq = 1000000 * (freq + 1) * m / 2;
पूर्ण

अटल व्योम hअगरn_init_रेजिस्टरs(काष्ठा hअगरn_device *dev)
अणु
	u32 dptr = dev->desc_dma;

	/* Initialization magic... */
	hअगरn_ग_लिखो_0(dev, HIFN_0_PUCTRL, HIFN_PUCTRL_DMAENA);
	hअगरn_ग_लिखो_0(dev, HIFN_0_FIFOCNFG, HIFN_FIFOCNFG_THRESHOLD);
	hअगरn_ग_लिखो_0(dev, HIFN_0_PUIER, HIFN_PUIER_DSTOVER);

	/* ग_लिखो all 4 ring address रेजिस्टरs */
	hअगरn_ग_लिखो_1(dev, HIFN_1_DMA_CRAR, dptr +
				दुरत्व(काष्ठा hअगरn_dma, cmdr[0]));
	hअगरn_ग_लिखो_1(dev, HIFN_1_DMA_SRAR, dptr +
				दुरत्व(काष्ठा hअगरn_dma, srcr[0]));
	hअगरn_ग_लिखो_1(dev, HIFN_1_DMA_DRAR, dptr +
				दुरत्व(काष्ठा hअगरn_dma, dstr[0]));
	hअगरn_ग_लिखो_1(dev, HIFN_1_DMA_RRAR, dptr +
				दुरत्व(काष्ठा hअगरn_dma, resr[0]));

	mdelay(2);
#अगर 0
	hअगरn_ग_लिखो_1(dev, HIFN_1_DMA_CSR,
	    HIFN_DMACSR_D_CTRL_DIS | HIFN_DMACSR_R_CTRL_DIS |
	    HIFN_DMACSR_S_CTRL_DIS | HIFN_DMACSR_C_CTRL_DIS |
	    HIFN_DMACSR_D_ABORT | HIFN_DMACSR_D_DONE | HIFN_DMACSR_D_LAST |
	    HIFN_DMACSR_D_WAIT | HIFN_DMACSR_D_OVER |
	    HIFN_DMACSR_R_ABORT | HIFN_DMACSR_R_DONE | HIFN_DMACSR_R_LAST |
	    HIFN_DMACSR_R_WAIT | HIFN_DMACSR_R_OVER |
	    HIFN_DMACSR_S_ABORT | HIFN_DMACSR_S_DONE | HIFN_DMACSR_S_LAST |
	    HIFN_DMACSR_S_WAIT |
	    HIFN_DMACSR_C_ABORT | HIFN_DMACSR_C_DONE | HIFN_DMACSR_C_LAST |
	    HIFN_DMACSR_C_WAIT |
	    HIFN_DMACSR_ENGINE |
	    HIFN_DMACSR_PUBDONE);
#अन्यथा
	hअगरn_ग_लिखो_1(dev, HIFN_1_DMA_CSR,
	    HIFN_DMACSR_C_CTRL_ENA | HIFN_DMACSR_S_CTRL_ENA |
	    HIFN_DMACSR_D_CTRL_ENA | HIFN_DMACSR_R_CTRL_ENA |
	    HIFN_DMACSR_D_ABORT | HIFN_DMACSR_D_DONE | HIFN_DMACSR_D_LAST |
	    HIFN_DMACSR_D_WAIT | HIFN_DMACSR_D_OVER |
	    HIFN_DMACSR_R_ABORT | HIFN_DMACSR_R_DONE | HIFN_DMACSR_R_LAST |
	    HIFN_DMACSR_R_WAIT | HIFN_DMACSR_R_OVER |
	    HIFN_DMACSR_S_ABORT | HIFN_DMACSR_S_DONE | HIFN_DMACSR_S_LAST |
	    HIFN_DMACSR_S_WAIT |
	    HIFN_DMACSR_C_ABORT | HIFN_DMACSR_C_DONE | HIFN_DMACSR_C_LAST |
	    HIFN_DMACSR_C_WAIT |
	    HIFN_DMACSR_ENGINE |
	    HIFN_DMACSR_PUBDONE);
#पूर्ण_अगर
	hअगरn_पढ़ो_1(dev, HIFN_1_DMA_CSR);

	dev->dmareg |= HIFN_DMAIER_R_DONE | HIFN_DMAIER_C_ABORT |
	    HIFN_DMAIER_D_OVER | HIFN_DMAIER_R_OVER |
	    HIFN_DMAIER_S_ABORT | HIFN_DMAIER_D_ABORT | HIFN_DMAIER_R_ABORT |
	    HIFN_DMAIER_ENGINE;
	dev->dmareg &= ~HIFN_DMAIER_C_WAIT;

	hअगरn_ग_लिखो_1(dev, HIFN_1_DMA_IER, dev->dmareg);
	hअगरn_पढ़ो_1(dev, HIFN_1_DMA_IER);
#अगर 0
	hअगरn_ग_लिखो_0(dev, HIFN_0_PUCNFG, HIFN_PUCNFG_ENCCNFG |
		    HIFN_PUCNFG_DRFR_128 | HIFN_PUCNFG_TCALLPHASES |
		    HIFN_PUCNFG_TCDRVTOTEM | HIFN_PUCNFG_BUS32 |
		    HIFN_PUCNFG_DRAM);
#अन्यथा
	hअगरn_ग_लिखो_0(dev, HIFN_0_PUCNFG, 0x10342);
#पूर्ण_अगर
	hअगरn_init_pll(dev);

	hअगरn_ग_लिखो_0(dev, HIFN_0_PUISR, HIFN_PUISR_DSTOVER);
	hअगरn_ग_लिखो_1(dev, HIFN_1_DMA_CNFG, HIFN_DMACNFG_MSTRESET |
	    HIFN_DMACNFG_DMARESET | HIFN_DMACNFG_MODE | HIFN_DMACNFG_LAST |
	    ((HIFN_POLL_FREQUENCY << 16 ) & HIFN_DMACNFG_POLLFREQ) |
	    ((HIFN_POLL_SCALAR << 8) & HIFN_DMACNFG_POLLINVAL));
पूर्ण

अटल पूर्णांक hअगरn_setup_base_command(काष्ठा hअगरn_device *dev, u8 *buf,
		अचिन्हित dlen, अचिन्हित slen, u16 mask, u8 snum)
अणु
	काष्ठा hअगरn_base_command *base_cmd;
	u8 *buf_pos = buf;

	base_cmd = (काष्ठा hअगरn_base_command *)buf_pos;
	base_cmd->masks = __cpu_to_le16(mask);
	base_cmd->total_source_count =
		__cpu_to_le16(slen & HIFN_BASE_CMD_LENMASK_LO);
	base_cmd->total_dest_count =
		__cpu_to_le16(dlen & HIFN_BASE_CMD_LENMASK_LO);

	dlen >>= 16;
	slen >>= 16;
	base_cmd->session_num = __cpu_to_le16(snum |
	    ((slen << HIFN_BASE_CMD_SRCLEN_S) & HIFN_BASE_CMD_SRCLEN_M) |
	    ((dlen << HIFN_BASE_CMD_DSTLEN_S) & HIFN_BASE_CMD_DSTLEN_M));

	वापस माप(काष्ठा hअगरn_base_command);
पूर्ण

अटल पूर्णांक hअगरn_setup_crypto_command(काष्ठा hअगरn_device *dev,
		u8 *buf, अचिन्हित dlen, अचिन्हित slen,
		u8 *key, पूर्णांक keylen, u8 *iv, पूर्णांक ivsize, u16 mode)
अणु
	काष्ठा hअगरn_dma *dma = (काष्ठा hअगरn_dma *)dev->desc_virt;
	काष्ठा hअगरn_crypt_command *cry_cmd;
	u8 *buf_pos = buf;
	u16 cmd_len;

	cry_cmd = (काष्ठा hअगरn_crypt_command *)buf_pos;

	cry_cmd->source_count = __cpu_to_le16(dlen & 0xffff);
	dlen >>= 16;
	cry_cmd->masks = __cpu_to_le16(mode |
			((dlen << HIFN_CRYPT_CMD_SRCLEN_S) &
			 HIFN_CRYPT_CMD_SRCLEN_M));
	cry_cmd->header_skip = 0;
	cry_cmd->reserved = 0;

	buf_pos += माप(काष्ठा hअगरn_crypt_command);

	dma->cmdu++;
	अगर (dma->cmdu > 1) अणु
		dev->dmareg |= HIFN_DMAIER_C_WAIT;
		hअगरn_ग_लिखो_1(dev, HIFN_1_DMA_IER, dev->dmareg);
	पूर्ण

	अगर (keylen) अणु
		स_नकल(buf_pos, key, keylen);
		buf_pos += keylen;
	पूर्ण
	अगर (ivsize) अणु
		स_नकल(buf_pos, iv, ivsize);
		buf_pos += ivsize;
	पूर्ण

	cmd_len = buf_pos - buf;

	वापस cmd_len;
पूर्ण

अटल पूर्णांक hअगरn_setup_cmd_desc(काष्ठा hअगरn_device *dev,
		काष्ठा hअगरn_context *ctx, काष्ठा hअगरn_request_context *rctx,
		व्योम *priv, अचिन्हित पूर्णांक nbytes)
अणु
	काष्ठा hअगरn_dma *dma = (काष्ठा hअगरn_dma *)dev->desc_virt;
	पूर्णांक cmd_len, sa_idx;
	u8 *buf, *buf_pos;
	u16 mask;

	sa_idx = dma->cmdi;
	buf_pos = buf = dma->command_bufs[dma->cmdi];

	mask = 0;
	चयन (rctx->op) अणु
	हाल ACRYPTO_OP_DECRYPT:
		mask = HIFN_BASE_CMD_CRYPT | HIFN_BASE_CMD_DECODE;
		अवरोध;
	हाल ACRYPTO_OP_ENCRYPT:
		mask = HIFN_BASE_CMD_CRYPT;
		अवरोध;
	हाल ACRYPTO_OP_HMAC:
		mask = HIFN_BASE_CMD_MAC;
		अवरोध;
	शेष:
		जाओ err_out;
	पूर्ण

	buf_pos += hअगरn_setup_base_command(dev, buf_pos, nbytes,
			nbytes, mask, dev->snum);

	अगर (rctx->op == ACRYPTO_OP_ENCRYPT || rctx->op == ACRYPTO_OP_DECRYPT) अणु
		u16 md = 0;

		अगर (ctx->keysize)
			md |= HIFN_CRYPT_CMD_NEW_KEY;
		अगर (rctx->iv && rctx->mode != ACRYPTO_MODE_ECB)
			md |= HIFN_CRYPT_CMD_NEW_IV;

		चयन (rctx->mode) अणु
		हाल ACRYPTO_MODE_ECB:
			md |= HIFN_CRYPT_CMD_MODE_ECB;
			अवरोध;
		हाल ACRYPTO_MODE_CBC:
			md |= HIFN_CRYPT_CMD_MODE_CBC;
			अवरोध;
		हाल ACRYPTO_MODE_CFB:
			md |= HIFN_CRYPT_CMD_MODE_CFB;
			अवरोध;
		हाल ACRYPTO_MODE_OFB:
			md |= HIFN_CRYPT_CMD_MODE_OFB;
			अवरोध;
		शेष:
			जाओ err_out;
		पूर्ण

		चयन (rctx->type) अणु
		हाल ACRYPTO_TYPE_AES_128:
			अगर (ctx->keysize != 16)
				जाओ err_out;
			md |= HIFN_CRYPT_CMD_KSZ_128 |
				HIFN_CRYPT_CMD_ALG_AES;
			अवरोध;
		हाल ACRYPTO_TYPE_AES_192:
			अगर (ctx->keysize != 24)
				जाओ err_out;
			md |= HIFN_CRYPT_CMD_KSZ_192 |
				HIFN_CRYPT_CMD_ALG_AES;
			अवरोध;
		हाल ACRYPTO_TYPE_AES_256:
			अगर (ctx->keysize != 32)
				जाओ err_out;
			md |= HIFN_CRYPT_CMD_KSZ_256 |
				HIFN_CRYPT_CMD_ALG_AES;
			अवरोध;
		हाल ACRYPTO_TYPE_3DES:
			अगर (ctx->keysize != 24)
				जाओ err_out;
			md |= HIFN_CRYPT_CMD_ALG_3DES;
			अवरोध;
		हाल ACRYPTO_TYPE_DES:
			अगर (ctx->keysize != 8)
				जाओ err_out;
			md |= HIFN_CRYPT_CMD_ALG_DES;
			अवरोध;
		शेष:
			जाओ err_out;
		पूर्ण

		buf_pos += hअगरn_setup_crypto_command(dev, buf_pos,
				nbytes, nbytes, ctx->key, ctx->keysize,
				rctx->iv, rctx->ivsize, md);
	पूर्ण

	dev->sa[sa_idx] = priv;
	dev->started++;

	cmd_len = buf_pos - buf;
	dma->cmdr[dma->cmdi].l = __cpu_to_le32(cmd_len | HIFN_D_VALID |
			HIFN_D_LAST | HIFN_D_MASKDONEIRQ);

	अगर (++dma->cmdi == HIFN_D_CMD_RSIZE) अणु
		dma->cmdr[dma->cmdi].l = __cpu_to_le32(
			HIFN_D_VALID | HIFN_D_LAST |
			HIFN_D_MASKDONEIRQ | HIFN_D_JUMP);
		dma->cmdi = 0;
	पूर्ण अन्यथा अणु
		dma->cmdr[dma->cmdi - 1].l |= __cpu_to_le32(HIFN_D_VALID);
	पूर्ण

	अगर (!(dev->flags & HIFN_FLAG_CMD_BUSY)) अणु
		hअगरn_ग_लिखो_1(dev, HIFN_1_DMA_CSR, HIFN_DMACSR_C_CTRL_ENA);
		dev->flags |= HIFN_FLAG_CMD_BUSY;
	पूर्ण
	वापस 0;

err_out:
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक hअगरn_setup_src_desc(काष्ठा hअगरn_device *dev, काष्ठा page *page,
		अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक size, पूर्णांक last)
अणु
	काष्ठा hअगरn_dma *dma = (काष्ठा hअगरn_dma *)dev->desc_virt;
	पूर्णांक idx;
	dma_addr_t addr;

	addr = dma_map_page(&dev->pdev->dev, page, offset, size,
			    DMA_TO_DEVICE);

	idx = dma->srci;

	dma->srcr[idx].p = __cpu_to_le32(addr);
	dma->srcr[idx].l = __cpu_to_le32(size | HIFN_D_VALID |
			HIFN_D_MASKDONEIRQ | (last ? HIFN_D_LAST : 0));

	अगर (++idx == HIFN_D_SRC_RSIZE) अणु
		dma->srcr[idx].l = __cpu_to_le32(HIFN_D_VALID |
				HIFN_D_JUMP | HIFN_D_MASKDONEIRQ |
				(last ? HIFN_D_LAST : 0));
		idx = 0;
	पूर्ण

	dma->srci = idx;
	dma->srcu++;

	अगर (!(dev->flags & HIFN_FLAG_SRC_BUSY)) अणु
		hअगरn_ग_लिखो_1(dev, HIFN_1_DMA_CSR, HIFN_DMACSR_S_CTRL_ENA);
		dev->flags |= HIFN_FLAG_SRC_BUSY;
	पूर्ण

	वापस size;
पूर्ण

अटल व्योम hअगरn_setup_res_desc(काष्ठा hअगरn_device *dev)
अणु
	काष्ठा hअगरn_dma *dma = (काष्ठा hअगरn_dma *)dev->desc_virt;

	dma->resr[dma->resi].l = __cpu_to_le32(HIFN_USED_RESULT |
			HIFN_D_VALID | HIFN_D_LAST);
	/*
	 * dma->resr[dma->resi].l = __cpu_to_le32(HIFN_MAX_RESULT | HIFN_D_VALID |
	 *					HIFN_D_LAST);
	 */

	अगर (++dma->resi == HIFN_D_RES_RSIZE) अणु
		dma->resr[HIFN_D_RES_RSIZE].l = __cpu_to_le32(HIFN_D_VALID |
				HIFN_D_JUMP | HIFN_D_MASKDONEIRQ | HIFN_D_LAST);
		dma->resi = 0;
	पूर्ण

	dma->resu++;

	अगर (!(dev->flags & HIFN_FLAG_RES_BUSY)) अणु
		hअगरn_ग_लिखो_1(dev, HIFN_1_DMA_CSR, HIFN_DMACSR_R_CTRL_ENA);
		dev->flags |= HIFN_FLAG_RES_BUSY;
	पूर्ण
पूर्ण

अटल व्योम hअगरn_setup_dst_desc(काष्ठा hअगरn_device *dev, काष्ठा page *page,
		अचिन्हित offset, अचिन्हित size, पूर्णांक last)
अणु
	काष्ठा hअगरn_dma *dma = (काष्ठा hअगरn_dma *)dev->desc_virt;
	पूर्णांक idx;
	dma_addr_t addr;

	addr = dma_map_page(&dev->pdev->dev, page, offset, size,
			    DMA_FROM_DEVICE);

	idx = dma->dsti;
	dma->dstr[idx].p = __cpu_to_le32(addr);
	dma->dstr[idx].l = __cpu_to_le32(size |	HIFN_D_VALID |
			HIFN_D_MASKDONEIRQ | (last ? HIFN_D_LAST : 0));

	अगर (++idx == HIFN_D_DST_RSIZE) अणु
		dma->dstr[idx].l = __cpu_to_le32(HIFN_D_VALID |
				HIFN_D_JUMP | HIFN_D_MASKDONEIRQ |
				(last ? HIFN_D_LAST : 0));
		idx = 0;
	पूर्ण
	dma->dsti = idx;
	dma->dstu++;

	अगर (!(dev->flags & HIFN_FLAG_DST_BUSY)) अणु
		hअगरn_ग_लिखो_1(dev, HIFN_1_DMA_CSR, HIFN_DMACSR_D_CTRL_ENA);
		dev->flags |= HIFN_FLAG_DST_BUSY;
	पूर्ण
पूर्ण

अटल पूर्णांक hअगरn_setup_dma(काष्ठा hअगरn_device *dev,
		काष्ठा hअगरn_context *ctx, काष्ठा hअगरn_request_context *rctx,
		काष्ठा scatterlist *src, काष्ठा scatterlist *dst,
		अचिन्हित पूर्णांक nbytes, व्योम *priv)
अणु
	काष्ठा scatterlist *t;
	काष्ठा page *spage, *dpage;
	अचिन्हित पूर्णांक soff, करोff;
	अचिन्हित पूर्णांक n, len;

	n = nbytes;
	जबतक (n) अणु
		spage = sg_page(src);
		soff = src->offset;
		len = min(src->length, n);

		hअगरn_setup_src_desc(dev, spage, soff, len, n - len == 0);

		src++;
		n -= len;
	पूर्ण

	t = &rctx->walk.cache[0];
	n = nbytes;
	जबतक (n) अणु
		अगर (t->length && rctx->walk.flags & ASYNC_FLAGS_MISALIGNED) अणु
			BUG_ON(!sg_page(t));
			dpage = sg_page(t);
			करोff = 0;
			len = t->length;
		पूर्ण अन्यथा अणु
			BUG_ON(!sg_page(dst));
			dpage = sg_page(dst);
			करोff = dst->offset;
			len = dst->length;
		पूर्ण
		len = min(len, n);

		hअगरn_setup_dst_desc(dev, dpage, करोff, len, n - len == 0);

		dst++;
		t++;
		n -= len;
	पूर्ण

	hअगरn_setup_cmd_desc(dev, ctx, rctx, priv, nbytes);
	hअगरn_setup_res_desc(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक hअगरn_cipher_walk_init(काष्ठा hअगरn_cipher_walk *w,
		पूर्णांक num, gfp_t gfp_flags)
अणु
	पूर्णांक i;

	num = min(ASYNC_SCATTERLIST_CACHE, num);
	sg_init_table(w->cache, num);

	w->num = 0;
	क्रम (i = 0; i < num; ++i) अणु
		काष्ठा page *page = alloc_page(gfp_flags);
		काष्ठा scatterlist *s;

		अगर (!page)
			अवरोध;

		s = &w->cache[i];

		sg_set_page(s, page, PAGE_SIZE, 0);
		w->num++;
	पूर्ण

	वापस i;
पूर्ण

अटल व्योम hअगरn_cipher_walk_निकास(काष्ठा hअगरn_cipher_walk *w)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < w->num; ++i) अणु
		काष्ठा scatterlist *s = &w->cache[i];

		__मुक्त_page(sg_page(s));

		s->length = 0;
	पूर्ण

	w->num = 0;
पूर्ण

अटल पूर्णांक skcipher_add(अचिन्हित पूर्णांक *drestp, काष्ठा scatterlist *dst,
		अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक *nbytesp)
अणु
	अचिन्हित पूर्णांक copy, drest = *drestp, nbytes = *nbytesp;
	पूर्णांक idx = 0;

	अगर (drest < size || size > nbytes)
		वापस -EINVAL;

	जबतक (size) अणु
		copy = min3(drest, size, dst->length);

		size -= copy;
		drest -= copy;
		nbytes -= copy;

		pr_debug("%s: copy: %u, size: %u, drest: %u, nbytes: %u.\n",
			 __func__, copy, size, drest, nbytes);

		dst++;
		idx++;
	पूर्ण

	*nbytesp = nbytes;
	*drestp = drest;

	वापस idx;
पूर्ण

अटल पूर्णांक hअगरn_cipher_walk(काष्ठा skcipher_request *req,
		काष्ठा hअगरn_cipher_walk *w)
अणु
	काष्ठा scatterlist *dst, *t;
	अचिन्हित पूर्णांक nbytes = req->cryptlen, offset, copy, dअगरf;
	पूर्णांक idx, tidx, err;

	tidx = idx = 0;
	offset = 0;
	जबतक (nbytes) अणु
		अगर (idx >= w->num && (w->flags & ASYNC_FLAGS_MISALIGNED))
			वापस -EINVAL;

		dst = &req->dst[idx];

		pr_debug("\n%s: dlen: %u, doff: %u, offset: %u, nbytes: %u.\n",
			 __func__, dst->length, dst->offset, offset, nbytes);

		अगर (!IS_ALIGNED(dst->offset, HIFN_D_DST_DALIGN) ||
		    !IS_ALIGNED(dst->length, HIFN_D_DST_DALIGN) ||
		    offset) अणु
			अचिन्हित slen = min(dst->length - offset, nbytes);
			अचिन्हित dlen = PAGE_SIZE;

			t = &w->cache[idx];

			err = skcipher_add(&dlen, dst, slen, &nbytes);
			अगर (err < 0)
				वापस err;

			idx += err;

			copy = slen & ~(HIFN_D_DST_DALIGN - 1);
			dअगरf = slen & (HIFN_D_DST_DALIGN - 1);

			अगर (dlen < nbytes) अणु
				/*
				 * Destination page करोes not have enough space
				 * to put there additional blocksized chunk,
				 * so we mark that page as containing only
				 * blocksize aligned chunks:
				 *	t->length = (slen & ~(HIFN_D_DST_DALIGN - 1));
				 * and increase number of bytes to be processed
				 * in next chunk:
				 *	nbytes += dअगरf;
				 */
				nbytes += dअगरf;

				/*
				 * Temporary of course...
				 * Kick author अगर you will catch this one.
				 */
				pr_err("%s: dlen: %u, nbytes: %u, slen: %u, offset: %u.\n",
				       __func__, dlen, nbytes, slen, offset);
				pr_err("%s: please contact author to fix this "
				       "issue, generally you should not catch "
				       "this path under any condition but who "
				       "knows how did you use crypto code.\n"
				       "Thank you.\n",	__func__);
				BUG();
			पूर्ण अन्यथा अणु
				copy += dअगरf + nbytes;

				dst = &req->dst[idx];

				err = skcipher_add(&dlen, dst, nbytes, &nbytes);
				अगर (err < 0)
					वापस err;

				idx += err;
			पूर्ण

			t->length = copy;
			t->offset = offset;
		पूर्ण अन्यथा अणु
			nbytes -= min(dst->length, nbytes);
			idx++;
		पूर्ण

		tidx++;
	पूर्ण

	वापस tidx;
पूर्ण

अटल पूर्णांक hअगरn_setup_session(काष्ठा skcipher_request *req)
अणु
	काष्ठा hअगरn_context *ctx = crypto_tfm_ctx(req->base.tfm);
	काष्ठा hअगरn_request_context *rctx = skcipher_request_ctx(req);
	काष्ठा hअगरn_device *dev = ctx->dev;
	अचिन्हित दीर्घ dlen, flags;
	अचिन्हित पूर्णांक nbytes = req->cryptlen, idx = 0;
	पूर्णांक err = -EINVAL, sg_num;
	काष्ठा scatterlist *dst;

	अगर (rctx->iv && !rctx->ivsize && rctx->mode != ACRYPTO_MODE_ECB)
		जाओ err_out_निकास;

	rctx->walk.flags = 0;

	जबतक (nbytes) अणु
		dst = &req->dst[idx];
		dlen = min(dst->length, nbytes);

		अगर (!IS_ALIGNED(dst->offset, HIFN_D_DST_DALIGN) ||
		    !IS_ALIGNED(dlen, HIFN_D_DST_DALIGN))
			rctx->walk.flags |= ASYNC_FLAGS_MISALIGNED;

		nbytes -= dlen;
		idx++;
	पूर्ण

	अगर (rctx->walk.flags & ASYNC_FLAGS_MISALIGNED) अणु
		err = hअगरn_cipher_walk_init(&rctx->walk, idx, GFP_ATOMIC);
		अगर (err < 0)
			वापस err;
	पूर्ण

	sg_num = hअगरn_cipher_walk(req, &rctx->walk);
	अगर (sg_num < 0) अणु
		err = sg_num;
		जाओ err_out_निकास;
	पूर्ण

	spin_lock_irqsave(&dev->lock, flags);
	अगर (dev->started + sg_num > HIFN_QUEUE_LENGTH) अणु
		err = -EAGAIN;
		जाओ err_out;
	पूर्ण

	err = hअगरn_setup_dma(dev, ctx, rctx, req->src, req->dst, req->cryptlen, req);
	अगर (err)
		जाओ err_out;

	dev->snum++;

	dev->active = HIFN_DEFAULT_ACTIVE_NUM;
	spin_unlock_irqrestore(&dev->lock, flags);

	वापस 0;

err_out:
	spin_unlock_irqrestore(&dev->lock, flags);
err_out_निकास:
	अगर (err) अणु
		dev_info(&dev->pdev->dev, "iv: %p [%d], key: %p [%d], mode: %u, op: %u, "
			 "type: %u, err: %d.\n",
			 rctx->iv, rctx->ivsize,
			 ctx->key, ctx->keysize,
			 rctx->mode, rctx->op, rctx->type, err);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक hअगरn_start_device(काष्ठा hअगरn_device *dev)
अणु
	पूर्णांक err;

	dev->started = dev->active = 0;
	hअगरn_reset_dma(dev, 1);

	err = hअगरn_enable_crypto(dev);
	अगर (err)
		वापस err;

	hअगरn_reset_puc(dev);

	hअगरn_init_dma(dev);

	hअगरn_init_रेजिस्टरs(dev);

	hअगरn_init_pubrng(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक skcipher_get(व्योम *saddr, अचिन्हित पूर्णांक *srestp, अचिन्हित पूर्णांक offset,
		काष्ठा scatterlist *dst, अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक *nbytesp)
अणु
	अचिन्हित पूर्णांक srest = *srestp, nbytes = *nbytesp, copy;
	व्योम *daddr;
	पूर्णांक idx = 0;

	अगर (srest < size || size > nbytes)
		वापस -EINVAL;

	जबतक (size) अणु
		copy = min3(srest, dst->length, size);

		daddr = kmap_atomic(sg_page(dst));
		स_नकल(daddr + dst->offset + offset, saddr, copy);
		kunmap_atomic(daddr);

		nbytes -= copy;
		size -= copy;
		srest -= copy;
		saddr += copy;
		offset = 0;

		pr_debug("%s: copy: %u, size: %u, srest: %u, nbytes: %u.\n",
			 __func__, copy, size, srest, nbytes);

		dst++;
		idx++;
	पूर्ण

	*nbytesp = nbytes;
	*srestp = srest;

	वापस idx;
पूर्ण

अटल अंतरभूत व्योम hअगरn_complete_sa(काष्ठा hअगरn_device *dev, पूर्णांक i)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->lock, flags);
	dev->sa[i] = शून्य;
	dev->started--;
	अगर (dev->started < 0)
		dev_info(&dev->pdev->dev, "%s: started: %d.\n", __func__,
			 dev->started);
	spin_unlock_irqrestore(&dev->lock, flags);
	BUG_ON(dev->started < 0);
पूर्ण

अटल व्योम hअगरn_process_पढ़ोy(काष्ठा skcipher_request *req, पूर्णांक error)
अणु
	काष्ठा hअगरn_request_context *rctx = skcipher_request_ctx(req);

	अगर (rctx->walk.flags & ASYNC_FLAGS_MISALIGNED) अणु
		अचिन्हित पूर्णांक nbytes = req->cryptlen;
		पूर्णांक idx = 0, err;
		काष्ठा scatterlist *dst, *t;
		व्योम *saddr;

		जबतक (nbytes) अणु
			t = &rctx->walk.cache[idx];
			dst = &req->dst[idx];

			pr_debug("\n%s: sg_page(t): %p, t->length: %u, "
				"sg_page(dst): %p, dst->length: %u, "
				"nbytes: %u.\n",
				__func__, sg_page(t), t->length,
				sg_page(dst), dst->length, nbytes);

			अगर (!t->length) अणु
				nbytes -= min(dst->length, nbytes);
				idx++;
				जारी;
			पूर्ण

			saddr = kmap_atomic(sg_page(t));

			err = skcipher_get(saddr, &t->length, t->offset,
					dst, nbytes, &nbytes);
			अगर (err < 0) अणु
				kunmap_atomic(saddr);
				अवरोध;
			पूर्ण

			idx += err;
			kunmap_atomic(saddr);
		पूर्ण

		hअगरn_cipher_walk_निकास(&rctx->walk);
	पूर्ण

	req->base.complete(&req->base, error);
पूर्ण

अटल व्योम hअगरn_clear_rings(काष्ठा hअगरn_device *dev, पूर्णांक error)
अणु
	काष्ठा hअगरn_dma *dma = (काष्ठा hअगरn_dma *)dev->desc_virt;
	पूर्णांक i, u;

	dev_dbg(&dev->pdev->dev, "ring cleanup 1: i: %d.%d.%d.%d, u: %d.%d.%d.%d, "
			"k: %d.%d.%d.%d.\n",
			dma->cmdi, dma->srci, dma->dsti, dma->resi,
			dma->cmdu, dma->srcu, dma->dstu, dma->resu,
			dma->cmdk, dma->srck, dma->dstk, dma->resk);

	i = dma->resk; u = dma->resu;
	जबतक (u != 0) अणु
		अगर (dma->resr[i].l & __cpu_to_le32(HIFN_D_VALID))
			अवरोध;

		अगर (dev->sa[i]) अणु
			dev->success++;
			dev->reset = 0;
			hअगरn_process_पढ़ोy(dev->sa[i], error);
			hअगरn_complete_sa(dev, i);
		पूर्ण

		अगर (++i == HIFN_D_RES_RSIZE)
			i = 0;
		u--;
	पूर्ण
	dma->resk = i; dma->resu = u;

	i = dma->srck; u = dma->srcu;
	जबतक (u != 0) अणु
		अगर (dma->srcr[i].l & __cpu_to_le32(HIFN_D_VALID))
			अवरोध;
		अगर (++i == HIFN_D_SRC_RSIZE)
			i = 0;
		u--;
	पूर्ण
	dma->srck = i; dma->srcu = u;

	i = dma->cmdk; u = dma->cmdu;
	जबतक (u != 0) अणु
		अगर (dma->cmdr[i].l & __cpu_to_le32(HIFN_D_VALID))
			अवरोध;
		अगर (++i == HIFN_D_CMD_RSIZE)
			i = 0;
		u--;
	पूर्ण
	dma->cmdk = i; dma->cmdu = u;

	i = dma->dstk; u = dma->dstu;
	जबतक (u != 0) अणु
		अगर (dma->dstr[i].l & __cpu_to_le32(HIFN_D_VALID))
			अवरोध;
		अगर (++i == HIFN_D_DST_RSIZE)
			i = 0;
		u--;
	पूर्ण
	dma->dstk = i; dma->dstu = u;

	dev_dbg(&dev->pdev->dev, "ring cleanup 2: i: %d.%d.%d.%d, u: %d.%d.%d.%d, "
			"k: %d.%d.%d.%d.\n",
			dma->cmdi, dma->srci, dma->dsti, dma->resi,
			dma->cmdu, dma->srcu, dma->dstu, dma->resu,
			dma->cmdk, dma->srck, dma->dstk, dma->resk);
पूर्ण

अटल व्योम hअगरn_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dw = to_delayed_work(work);
	काष्ठा hअगरn_device *dev = container_of(dw, काष्ठा hअगरn_device, work);
	अचिन्हित दीर्घ flags;
	पूर्णांक reset = 0;
	u32 r = 0;

	spin_lock_irqsave(&dev->lock, flags);
	अगर (dev->active == 0) अणु
		काष्ठा hअगरn_dma *dma = (काष्ठा hअगरn_dma *)dev->desc_virt;

		अगर (dma->cmdu == 0 && (dev->flags & HIFN_FLAG_CMD_BUSY)) अणु
			dev->flags &= ~HIFN_FLAG_CMD_BUSY;
			r |= HIFN_DMACSR_C_CTRL_DIS;
		पूर्ण
		अगर (dma->srcu == 0 && (dev->flags & HIFN_FLAG_SRC_BUSY)) अणु
			dev->flags &= ~HIFN_FLAG_SRC_BUSY;
			r |= HIFN_DMACSR_S_CTRL_DIS;
		पूर्ण
		अगर (dma->dstu == 0 && (dev->flags & HIFN_FLAG_DST_BUSY)) अणु
			dev->flags &= ~HIFN_FLAG_DST_BUSY;
			r |= HIFN_DMACSR_D_CTRL_DIS;
		पूर्ण
		अगर (dma->resu == 0 && (dev->flags & HIFN_FLAG_RES_BUSY)) अणु
			dev->flags &= ~HIFN_FLAG_RES_BUSY;
			r |= HIFN_DMACSR_R_CTRL_DIS;
		पूर्ण
		अगर (r)
			hअगरn_ग_लिखो_1(dev, HIFN_1_DMA_CSR, r);
	पूर्ण अन्यथा
		dev->active--;

	अगर ((dev->prev_success == dev->success) && dev->started)
		reset = 1;
	dev->prev_success = dev->success;
	spin_unlock_irqrestore(&dev->lock, flags);

	अगर (reset) अणु
		अगर (++dev->reset >= 5) अणु
			पूर्णांक i;
			काष्ठा hअगरn_dma *dma = (काष्ठा hअगरn_dma *)dev->desc_virt;

			dev_info(&dev->pdev->dev,
				 "r: %08x, active: %d, started: %d, "
				 "success: %lu: qlen: %u/%u, reset: %d.\n",
				 r, dev->active, dev->started,
				 dev->success, dev->queue.qlen, dev->queue.max_qlen,
				 reset);

			dev_info(&dev->pdev->dev, "%s: res: ", __func__);
			क्रम (i = 0; i < HIFN_D_RES_RSIZE; ++i) अणु
				pr_info("%x.%p ", dma->resr[i].l, dev->sa[i]);
				अगर (dev->sa[i]) अणु
					hअगरn_process_पढ़ोy(dev->sa[i], -ENODEV);
					hअगरn_complete_sa(dev, i);
				पूर्ण
			पूर्ण
			pr_info("\n");

			hअगरn_reset_dma(dev, 1);
			hअगरn_stop_device(dev);
			hअगरn_start_device(dev);
			dev->reset = 0;
		पूर्ण

		tasklet_schedule(&dev->tasklet);
	पूर्ण

	schedule_delayed_work(&dev->work, HZ);
पूर्ण

अटल irqवापस_t hअगरn_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा hअगरn_device *dev = (काष्ठा hअगरn_device *)data;
	काष्ठा hअगरn_dma *dma = (काष्ठा hअगरn_dma *)dev->desc_virt;
	u32 dmacsr, restart;

	dmacsr = hअगरn_पढ़ो_1(dev, HIFN_1_DMA_CSR);

	dev_dbg(&dev->pdev->dev, "1 dmacsr: %08x, dmareg: %08x, res: %08x [%d], "
			"i: %d.%d.%d.%d, u: %d.%d.%d.%d.\n",
		dmacsr, dev->dmareg, dmacsr & dev->dmareg, dma->cmdi,
		dma->cmdi, dma->srci, dma->dsti, dma->resi,
		dma->cmdu, dma->srcu, dma->dstu, dma->resu);

	अगर ((dmacsr & dev->dmareg) == 0)
		वापस IRQ_NONE;

	hअगरn_ग_लिखो_1(dev, HIFN_1_DMA_CSR, dmacsr & dev->dmareg);

	अगर (dmacsr & HIFN_DMACSR_ENGINE)
		hअगरn_ग_लिखो_0(dev, HIFN_0_PUISR, hअगरn_पढ़ो_0(dev, HIFN_0_PUISR));
	अगर (dmacsr & HIFN_DMACSR_PUBDONE)
		hअगरn_ग_लिखो_1(dev, HIFN_1_PUB_STATUS,
			hअगरn_पढ़ो_1(dev, HIFN_1_PUB_STATUS) | HIFN_PUBSTS_DONE);

	restart = dmacsr & (HIFN_DMACSR_R_OVER | HIFN_DMACSR_D_OVER);
	अगर (restart) अणु
		u32 puisr = hअगरn_पढ़ो_0(dev, HIFN_0_PUISR);

		dev_warn(&dev->pdev->dev, "overflow: r: %d, d: %d, puisr: %08x, d: %u.\n",
			 !!(dmacsr & HIFN_DMACSR_R_OVER),
			 !!(dmacsr & HIFN_DMACSR_D_OVER),
			puisr, !!(puisr & HIFN_PUISR_DSTOVER));
		अगर (!!(puisr & HIFN_PUISR_DSTOVER))
			hअगरn_ग_लिखो_0(dev, HIFN_0_PUISR, HIFN_PUISR_DSTOVER);
		hअगरn_ग_लिखो_1(dev, HIFN_1_DMA_CSR, dmacsr & (HIFN_DMACSR_R_OVER |
					HIFN_DMACSR_D_OVER));
	पूर्ण

	restart = dmacsr & (HIFN_DMACSR_C_ABORT | HIFN_DMACSR_S_ABORT |
			HIFN_DMACSR_D_ABORT | HIFN_DMACSR_R_ABORT);
	अगर (restart) अणु
		dev_warn(&dev->pdev->dev, "abort: c: %d, s: %d, d: %d, r: %d.\n",
			 !!(dmacsr & HIFN_DMACSR_C_ABORT),
			 !!(dmacsr & HIFN_DMACSR_S_ABORT),
			 !!(dmacsr & HIFN_DMACSR_D_ABORT),
			 !!(dmacsr & HIFN_DMACSR_R_ABORT));
		hअगरn_reset_dma(dev, 1);
		hअगरn_init_dma(dev);
		hअगरn_init_रेजिस्टरs(dev);
	पूर्ण

	अगर ((dmacsr & HIFN_DMACSR_C_WAIT) && (dma->cmdu == 0)) अणु
		dev_dbg(&dev->pdev->dev, "wait on command.\n");
		dev->dmareg &= ~(HIFN_DMAIER_C_WAIT);
		hअगरn_ग_लिखो_1(dev, HIFN_1_DMA_IER, dev->dmareg);
	पूर्ण

	tasklet_schedule(&dev->tasklet);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम hअगरn_flush(काष्ठा hअगरn_device *dev)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा crypto_async_request *async_req;
	काष्ठा skcipher_request *req;
	काष्ठा hअगरn_dma *dma = (काष्ठा hअगरn_dma *)dev->desc_virt;
	पूर्णांक i;

	क्रम (i = 0; i < HIFN_D_RES_RSIZE; ++i) अणु
		काष्ठा hअगरn_desc *d = &dma->resr[i];

		अगर (dev->sa[i]) अणु
			hअगरn_process_पढ़ोy(dev->sa[i],
				(d->l & __cpu_to_le32(HIFN_D_VALID)) ? -ENODEV : 0);
			hअगरn_complete_sa(dev, i);
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&dev->lock, flags);
	जबतक ((async_req = crypto_dequeue_request(&dev->queue))) अणु
		req = skcipher_request_cast(async_req);
		spin_unlock_irqrestore(&dev->lock, flags);

		hअगरn_process_पढ़ोy(req, -ENODEV);

		spin_lock_irqsave(&dev->lock, flags);
	पूर्ण
	spin_unlock_irqrestore(&dev->lock, flags);
पूर्ण

अटल पूर्णांक hअगरn_setkey(काष्ठा crypto_skcipher *cipher, स्थिर u8 *key,
		अचिन्हित पूर्णांक len)
अणु
	काष्ठा hअगरn_context *ctx = crypto_skcipher_ctx(cipher);
	काष्ठा hअगरn_device *dev = ctx->dev;
	पूर्णांक err;

	err = verअगरy_skcipher_des_key(cipher, key);
	अगर (err)
		वापस err;

	dev->flags &= ~HIFN_FLAG_OLD_KEY;

	स_नकल(ctx->key, key, len);
	ctx->keysize = len;

	वापस 0;
पूर्ण

अटल पूर्णांक hअगरn_des3_setkey(काष्ठा crypto_skcipher *cipher, स्थिर u8 *key,
			    अचिन्हित पूर्णांक len)
अणु
	काष्ठा hअगरn_context *ctx = crypto_skcipher_ctx(cipher);
	काष्ठा hअगरn_device *dev = ctx->dev;
	पूर्णांक err;

	err = verअगरy_skcipher_des3_key(cipher, key);
	अगर (err)
		वापस err;

	dev->flags &= ~HIFN_FLAG_OLD_KEY;

	स_नकल(ctx->key, key, len);
	ctx->keysize = len;

	वापस 0;
पूर्ण

अटल पूर्णांक hअगरn_handle_req(काष्ठा skcipher_request *req)
अणु
	काष्ठा hअगरn_context *ctx = crypto_tfm_ctx(req->base.tfm);
	काष्ठा hअगरn_device *dev = ctx->dev;
	पूर्णांक err = -EAGAIN;

	अगर (dev->started + DIV_ROUND_UP(req->cryptlen, PAGE_SIZE) <= HIFN_QUEUE_LENGTH)
		err = hअगरn_setup_session(req);

	अगर (err == -EAGAIN) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&dev->lock, flags);
		err = crypto_enqueue_request(&dev->queue, &req->base);
		spin_unlock_irqrestore(&dev->lock, flags);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक hअगरn_setup_crypto_req(काष्ठा skcipher_request *req, u8 op,
		u8 type, u8 mode)
अणु
	काष्ठा hअगरn_context *ctx = crypto_tfm_ctx(req->base.tfm);
	काष्ठा hअगरn_request_context *rctx = skcipher_request_ctx(req);
	अचिन्हित ivsize;

	ivsize = crypto_skcipher_ivsize(crypto_skcipher_reqtfm(req));

	अगर (req->iv && mode != ACRYPTO_MODE_ECB) अणु
		अगर (type == ACRYPTO_TYPE_AES_128)
			ivsize = HIFN_AES_IV_LENGTH;
		अन्यथा अगर (type == ACRYPTO_TYPE_DES)
			ivsize = HIFN_DES_KEY_LENGTH;
		अन्यथा अगर (type == ACRYPTO_TYPE_3DES)
			ivsize = HIFN_3DES_KEY_LENGTH;
	पूर्ण

	अगर (ctx->keysize != 16 && type == ACRYPTO_TYPE_AES_128) अणु
		अगर (ctx->keysize == 24)
			type = ACRYPTO_TYPE_AES_192;
		अन्यथा अगर (ctx->keysize == 32)
			type = ACRYPTO_TYPE_AES_256;
	पूर्ण

	rctx->op = op;
	rctx->mode = mode;
	rctx->type = type;
	rctx->iv = req->iv;
	rctx->ivsize = ivsize;

	/*
	 * HEAVY TODO: needs to kick Herbert XU to ग_लिखो करोcumentation.
	 * HEAVY TODO: needs to kick Herbert XU to ग_लिखो करोcumentation.
	 * HEAVY TODO: needs to kick Herbert XU to ग_लिखो करोcumentation.
	 */

	वापस hअगरn_handle_req(req);
पूर्ण

अटल पूर्णांक hअगरn_process_queue(काष्ठा hअगरn_device *dev)
अणु
	काष्ठा crypto_async_request *async_req, *backlog;
	काष्ठा skcipher_request *req;
	अचिन्हित दीर्घ flags;
	पूर्णांक err = 0;

	जबतक (dev->started < HIFN_QUEUE_LENGTH) अणु
		spin_lock_irqsave(&dev->lock, flags);
		backlog = crypto_get_backlog(&dev->queue);
		async_req = crypto_dequeue_request(&dev->queue);
		spin_unlock_irqrestore(&dev->lock, flags);

		अगर (!async_req)
			अवरोध;

		अगर (backlog)
			backlog->complete(backlog, -EINPROGRESS);

		req = skcipher_request_cast(async_req);

		err = hअगरn_handle_req(req);
		अगर (err)
			अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक hअगरn_setup_crypto(काष्ठा skcipher_request *req, u8 op,
		u8 type, u8 mode)
अणु
	पूर्णांक err;
	काष्ठा hअगरn_context *ctx = crypto_tfm_ctx(req->base.tfm);
	काष्ठा hअगरn_device *dev = ctx->dev;

	err = hअगरn_setup_crypto_req(req, op, type, mode);
	अगर (err)
		वापस err;

	अगर (dev->started < HIFN_QUEUE_LENGTH &&	dev->queue.qlen)
		hअगरn_process_queue(dev);

	वापस -EINPROGRESS;
पूर्ण

/*
 * AES ecryption functions.
 */
अटल अंतरभूत पूर्णांक hअगरn_encrypt_aes_ecb(काष्ठा skcipher_request *req)
अणु
	वापस hअगरn_setup_crypto(req, ACRYPTO_OP_ENCRYPT,
			ACRYPTO_TYPE_AES_128, ACRYPTO_MODE_ECB);
पूर्ण
अटल अंतरभूत पूर्णांक hअगरn_encrypt_aes_cbc(काष्ठा skcipher_request *req)
अणु
	वापस hअगरn_setup_crypto(req, ACRYPTO_OP_ENCRYPT,
			ACRYPTO_TYPE_AES_128, ACRYPTO_MODE_CBC);
पूर्ण
अटल अंतरभूत पूर्णांक hअगरn_encrypt_aes_cfb(काष्ठा skcipher_request *req)
अणु
	वापस hअगरn_setup_crypto(req, ACRYPTO_OP_ENCRYPT,
			ACRYPTO_TYPE_AES_128, ACRYPTO_MODE_CFB);
पूर्ण
अटल अंतरभूत पूर्णांक hअगरn_encrypt_aes_ofb(काष्ठा skcipher_request *req)
अणु
	वापस hअगरn_setup_crypto(req, ACRYPTO_OP_ENCRYPT,
			ACRYPTO_TYPE_AES_128, ACRYPTO_MODE_OFB);
पूर्ण

/*
 * AES decryption functions.
 */
अटल अंतरभूत पूर्णांक hअगरn_decrypt_aes_ecb(काष्ठा skcipher_request *req)
अणु
	वापस hअगरn_setup_crypto(req, ACRYPTO_OP_DECRYPT,
			ACRYPTO_TYPE_AES_128, ACRYPTO_MODE_ECB);
पूर्ण
अटल अंतरभूत पूर्णांक hअगरn_decrypt_aes_cbc(काष्ठा skcipher_request *req)
अणु
	वापस hअगरn_setup_crypto(req, ACRYPTO_OP_DECRYPT,
			ACRYPTO_TYPE_AES_128, ACRYPTO_MODE_CBC);
पूर्ण
अटल अंतरभूत पूर्णांक hअगरn_decrypt_aes_cfb(काष्ठा skcipher_request *req)
अणु
	वापस hअगरn_setup_crypto(req, ACRYPTO_OP_DECRYPT,
			ACRYPTO_TYPE_AES_128, ACRYPTO_MODE_CFB);
पूर्ण
अटल अंतरभूत पूर्णांक hअगरn_decrypt_aes_ofb(काष्ठा skcipher_request *req)
अणु
	वापस hअगरn_setup_crypto(req, ACRYPTO_OP_DECRYPT,
			ACRYPTO_TYPE_AES_128, ACRYPTO_MODE_OFB);
पूर्ण

/*
 * DES ecryption functions.
 */
अटल अंतरभूत पूर्णांक hअगरn_encrypt_des_ecb(काष्ठा skcipher_request *req)
अणु
	वापस hअगरn_setup_crypto(req, ACRYPTO_OP_ENCRYPT,
			ACRYPTO_TYPE_DES, ACRYPTO_MODE_ECB);
पूर्ण
अटल अंतरभूत पूर्णांक hअगरn_encrypt_des_cbc(काष्ठा skcipher_request *req)
अणु
	वापस hअगरn_setup_crypto(req, ACRYPTO_OP_ENCRYPT,
			ACRYPTO_TYPE_DES, ACRYPTO_MODE_CBC);
पूर्ण
अटल अंतरभूत पूर्णांक hअगरn_encrypt_des_cfb(काष्ठा skcipher_request *req)
अणु
	वापस hअगरn_setup_crypto(req, ACRYPTO_OP_ENCRYPT,
			ACRYPTO_TYPE_DES, ACRYPTO_MODE_CFB);
पूर्ण
अटल अंतरभूत पूर्णांक hअगरn_encrypt_des_ofb(काष्ठा skcipher_request *req)
अणु
	वापस hअगरn_setup_crypto(req, ACRYPTO_OP_ENCRYPT,
			ACRYPTO_TYPE_DES, ACRYPTO_MODE_OFB);
पूर्ण

/*
 * DES decryption functions.
 */
अटल अंतरभूत पूर्णांक hअगरn_decrypt_des_ecb(काष्ठा skcipher_request *req)
अणु
	वापस hअगरn_setup_crypto(req, ACRYPTO_OP_DECRYPT,
			ACRYPTO_TYPE_DES, ACRYPTO_MODE_ECB);
पूर्ण
अटल अंतरभूत पूर्णांक hअगरn_decrypt_des_cbc(काष्ठा skcipher_request *req)
अणु
	वापस hअगरn_setup_crypto(req, ACRYPTO_OP_DECRYPT,
			ACRYPTO_TYPE_DES, ACRYPTO_MODE_CBC);
पूर्ण
अटल अंतरभूत पूर्णांक hअगरn_decrypt_des_cfb(काष्ठा skcipher_request *req)
अणु
	वापस hअगरn_setup_crypto(req, ACRYPTO_OP_DECRYPT,
			ACRYPTO_TYPE_DES, ACRYPTO_MODE_CFB);
पूर्ण
अटल अंतरभूत पूर्णांक hअगरn_decrypt_des_ofb(काष्ठा skcipher_request *req)
अणु
	वापस hअगरn_setup_crypto(req, ACRYPTO_OP_DECRYPT,
			ACRYPTO_TYPE_DES, ACRYPTO_MODE_OFB);
पूर्ण

/*
 * 3DES ecryption functions.
 */
अटल अंतरभूत पूर्णांक hअगरn_encrypt_3des_ecb(काष्ठा skcipher_request *req)
अणु
	वापस hअगरn_setup_crypto(req, ACRYPTO_OP_ENCRYPT,
			ACRYPTO_TYPE_3DES, ACRYPTO_MODE_ECB);
पूर्ण
अटल अंतरभूत पूर्णांक hअगरn_encrypt_3des_cbc(काष्ठा skcipher_request *req)
अणु
	वापस hअगरn_setup_crypto(req, ACRYPTO_OP_ENCRYPT,
			ACRYPTO_TYPE_3DES, ACRYPTO_MODE_CBC);
पूर्ण
अटल अंतरभूत पूर्णांक hअगरn_encrypt_3des_cfb(काष्ठा skcipher_request *req)
अणु
	वापस hअगरn_setup_crypto(req, ACRYPTO_OP_ENCRYPT,
			ACRYPTO_TYPE_3DES, ACRYPTO_MODE_CFB);
पूर्ण
अटल अंतरभूत पूर्णांक hअगरn_encrypt_3des_ofb(काष्ठा skcipher_request *req)
अणु
	वापस hअगरn_setup_crypto(req, ACRYPTO_OP_ENCRYPT,
			ACRYPTO_TYPE_3DES, ACRYPTO_MODE_OFB);
पूर्ण

/* 3DES decryption functions. */
अटल अंतरभूत पूर्णांक hअगरn_decrypt_3des_ecb(काष्ठा skcipher_request *req)
अणु
	वापस hअगरn_setup_crypto(req, ACRYPTO_OP_DECRYPT,
			ACRYPTO_TYPE_3DES, ACRYPTO_MODE_ECB);
पूर्ण
अटल अंतरभूत पूर्णांक hअगरn_decrypt_3des_cbc(काष्ठा skcipher_request *req)
अणु
	वापस hअगरn_setup_crypto(req, ACRYPTO_OP_DECRYPT,
			ACRYPTO_TYPE_3DES, ACRYPTO_MODE_CBC);
पूर्ण
अटल अंतरभूत पूर्णांक hअगरn_decrypt_3des_cfb(काष्ठा skcipher_request *req)
अणु
	वापस hअगरn_setup_crypto(req, ACRYPTO_OP_DECRYPT,
			ACRYPTO_TYPE_3DES, ACRYPTO_MODE_CFB);
पूर्ण
अटल अंतरभूत पूर्णांक hअगरn_decrypt_3des_ofb(काष्ठा skcipher_request *req)
अणु
	वापस hअगरn_setup_crypto(req, ACRYPTO_OP_DECRYPT,
			ACRYPTO_TYPE_3DES, ACRYPTO_MODE_OFB);
पूर्ण

काष्ठा hअगरn_alg_ढाँचा अणु
	अक्षर name[CRYPTO_MAX_ALG_NAME];
	अक्षर drv_name[CRYPTO_MAX_ALG_NAME];
	अचिन्हित पूर्णांक bsize;
	काष्ठा skcipher_alg skcipher;
पूर्ण;

अटल स्थिर काष्ठा hअगरn_alg_ढाँचा hअगरn_alg_ढाँचाs[] = अणु
	/*
	 * 3DES ECB, CBC, CFB and OFB modes.
	 */
	अणु
		.name = "cfb(des3_ede)", .drv_name = "cfb-3des", .bsize = 8,
		.skcipher = अणु
			.min_keysize	=	HIFN_3DES_KEY_LENGTH,
			.max_keysize	=	HIFN_3DES_KEY_LENGTH,
			.setkey		=	hअगरn_des3_setkey,
			.encrypt	=	hअगरn_encrypt_3des_cfb,
			.decrypt	=	hअगरn_decrypt_3des_cfb,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "ofb(des3_ede)", .drv_name = "ofb-3des", .bsize = 8,
		.skcipher = अणु
			.min_keysize	=	HIFN_3DES_KEY_LENGTH,
			.max_keysize	=	HIFN_3DES_KEY_LENGTH,
			.setkey		=	hअगरn_des3_setkey,
			.encrypt	=	hअगरn_encrypt_3des_ofb,
			.decrypt	=	hअगरn_decrypt_3des_ofb,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "cbc(des3_ede)", .drv_name = "cbc-3des", .bsize = 8,
		.skcipher = अणु
			.ivsize		=	HIFN_IV_LENGTH,
			.min_keysize	=	HIFN_3DES_KEY_LENGTH,
			.max_keysize	=	HIFN_3DES_KEY_LENGTH,
			.setkey		=	hअगरn_des3_setkey,
			.encrypt	=	hअगरn_encrypt_3des_cbc,
			.decrypt	=	hअगरn_decrypt_3des_cbc,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "ecb(des3_ede)", .drv_name = "ecb-3des", .bsize = 8,
		.skcipher = अणु
			.min_keysize	=	HIFN_3DES_KEY_LENGTH,
			.max_keysize	=	HIFN_3DES_KEY_LENGTH,
			.setkey		=	hअगरn_des3_setkey,
			.encrypt	=	hअगरn_encrypt_3des_ecb,
			.decrypt	=	hअगरn_decrypt_3des_ecb,
		पूर्ण,
	पूर्ण,

	/*
	 * DES ECB, CBC, CFB and OFB modes.
	 */
	अणु
		.name = "cfb(des)", .drv_name = "cfb-des", .bsize = 8,
		.skcipher = अणु
			.min_keysize	=	HIFN_DES_KEY_LENGTH,
			.max_keysize	=	HIFN_DES_KEY_LENGTH,
			.setkey		=	hअगरn_setkey,
			.encrypt	=	hअगरn_encrypt_des_cfb,
			.decrypt	=	hअगरn_decrypt_des_cfb,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "ofb(des)", .drv_name = "ofb-des", .bsize = 8,
		.skcipher = अणु
			.min_keysize	=	HIFN_DES_KEY_LENGTH,
			.max_keysize	=	HIFN_DES_KEY_LENGTH,
			.setkey		=	hअगरn_setkey,
			.encrypt	=	hअगरn_encrypt_des_ofb,
			.decrypt	=	hअगरn_decrypt_des_ofb,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "cbc(des)", .drv_name = "cbc-des", .bsize = 8,
		.skcipher = अणु
			.ivsize		=	HIFN_IV_LENGTH,
			.min_keysize	=	HIFN_DES_KEY_LENGTH,
			.max_keysize	=	HIFN_DES_KEY_LENGTH,
			.setkey		=	hअगरn_setkey,
			.encrypt	=	hअगरn_encrypt_des_cbc,
			.decrypt	=	hअगरn_decrypt_des_cbc,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "ecb(des)", .drv_name = "ecb-des", .bsize = 8,
		.skcipher = अणु
			.min_keysize	=	HIFN_DES_KEY_LENGTH,
			.max_keysize	=	HIFN_DES_KEY_LENGTH,
			.setkey		=	hअगरn_setkey,
			.encrypt	=	hअगरn_encrypt_des_ecb,
			.decrypt	=	hअगरn_decrypt_des_ecb,
		पूर्ण,
	पूर्ण,

	/*
	 * AES ECB, CBC, CFB and OFB modes.
	 */
	अणु
		.name = "ecb(aes)", .drv_name = "ecb-aes", .bsize = 16,
		.skcipher = अणु
			.min_keysize	=	AES_MIN_KEY_SIZE,
			.max_keysize	=	AES_MAX_KEY_SIZE,
			.setkey		=	hअगरn_setkey,
			.encrypt	=	hअगरn_encrypt_aes_ecb,
			.decrypt	=	hअगरn_decrypt_aes_ecb,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "cbc(aes)", .drv_name = "cbc-aes", .bsize = 16,
		.skcipher = अणु
			.ivsize		=	HIFN_AES_IV_LENGTH,
			.min_keysize	=	AES_MIN_KEY_SIZE,
			.max_keysize	=	AES_MAX_KEY_SIZE,
			.setkey		=	hअगरn_setkey,
			.encrypt	=	hअगरn_encrypt_aes_cbc,
			.decrypt	=	hअगरn_decrypt_aes_cbc,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "cfb(aes)", .drv_name = "cfb-aes", .bsize = 16,
		.skcipher = अणु
			.min_keysize	=	AES_MIN_KEY_SIZE,
			.max_keysize	=	AES_MAX_KEY_SIZE,
			.setkey		=	hअगरn_setkey,
			.encrypt	=	hअगरn_encrypt_aes_cfb,
			.decrypt	=	hअगरn_decrypt_aes_cfb,
		पूर्ण,
	पूर्ण,
	अणु
		.name = "ofb(aes)", .drv_name = "ofb-aes", .bsize = 16,
		.skcipher = अणु
			.min_keysize	=	AES_MIN_KEY_SIZE,
			.max_keysize	=	AES_MAX_KEY_SIZE,
			.setkey		=	hअगरn_setkey,
			.encrypt	=	hअगरn_encrypt_aes_ofb,
			.decrypt	=	hअगरn_decrypt_aes_ofb,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक hअगरn_init_tfm(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा skcipher_alg *alg = crypto_skcipher_alg(tfm);
	काष्ठा hअगरn_crypto_alg *ha = crypto_alg_to_hअगरn(alg);
	काष्ठा hअगरn_context *ctx = crypto_skcipher_ctx(tfm);

	ctx->dev = ha->dev;
	crypto_skcipher_set_reqsize(tfm, माप(काष्ठा hअगरn_request_context));

	वापस 0;
पूर्ण

अटल पूर्णांक hअगरn_alg_alloc(काष्ठा hअगरn_device *dev, स्थिर काष्ठा hअगरn_alg_ढाँचा *t)
अणु
	काष्ठा hअगरn_crypto_alg *alg;
	पूर्णांक err;

	alg = kzalloc(माप(*alg), GFP_KERNEL);
	अगर (!alg)
		वापस -ENOMEM;

	alg->alg = t->skcipher;
	alg->alg.init = hअगरn_init_tfm;

	snम_लिखो(alg->alg.base.cra_name, CRYPTO_MAX_ALG_NAME, "%s", t->name);
	snम_लिखो(alg->alg.base.cra_driver_name, CRYPTO_MAX_ALG_NAME, "%s-%s",
		 t->drv_name, dev->name);

	alg->alg.base.cra_priority = 300;
	alg->alg.base.cra_flags = CRYPTO_ALG_KERN_DRIVER_ONLY | CRYPTO_ALG_ASYNC;
	alg->alg.base.cra_blocksize = t->bsize;
	alg->alg.base.cra_ctxsize = माप(काष्ठा hअगरn_context);
	alg->alg.base.cra_alignmask = 0;
	alg->alg.base.cra_module = THIS_MODULE;

	alg->dev = dev;

	list_add_tail(&alg->entry, &dev->alg_list);

	err = crypto_रेजिस्टर_skcipher(&alg->alg);
	अगर (err) अणु
		list_del(&alg->entry);
		kमुक्त(alg);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम hअगरn_unरेजिस्टर_alg(काष्ठा hअगरn_device *dev)
अणु
	काष्ठा hअगरn_crypto_alg *a, *n;

	list_क्रम_each_entry_safe(a, n, &dev->alg_list, entry) अणु
		list_del(&a->entry);
		crypto_unरेजिस्टर_skcipher(&a->alg);
		kमुक्त(a);
	पूर्ण
पूर्ण

अटल पूर्णांक hअगरn_रेजिस्टर_alg(काष्ठा hअगरn_device *dev)
अणु
	पूर्णांक i, err;

	क्रम (i = 0; i < ARRAY_SIZE(hअगरn_alg_ढाँचाs); ++i) अणु
		err = hअगरn_alg_alloc(dev, &hअगरn_alg_ढाँचाs[i]);
		अगर (err)
			जाओ err_out_निकास;
	पूर्ण

	वापस 0;

err_out_निकास:
	hअगरn_unरेजिस्टर_alg(dev);
	वापस err;
पूर्ण

अटल व्योम hअगरn_tasklet_callback(अचिन्हित दीर्घ data)
अणु
	काष्ठा hअगरn_device *dev = (काष्ठा hअगरn_device *)data;

	/*
	 * This is ok to call this without lock being held,
	 * althogh it modअगरies some parameters used in parallel,
	 * (like dev->success), but they are used in process
	 * context or update is atomic (like setting dev->sa[i] to शून्य).
	 */
	hअगरn_clear_rings(dev, 0);

	अगर (dev->started < HIFN_QUEUE_LENGTH &&	dev->queue.qlen)
		hअगरn_process_queue(dev);
पूर्ण

अटल पूर्णांक hअगरn_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	पूर्णांक err, i;
	काष्ठा hअगरn_device *dev;
	अक्षर name[8];

	err = pci_enable_device(pdev);
	अगर (err)
		वापस err;
	pci_set_master(pdev);

	err = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));
	अगर (err)
		जाओ err_out_disable_pci_device;

	snम_लिखो(name, माप(name), "hifn%d",
			atomic_inc_वापस(&hअगरn_dev_number) - 1);

	err = pci_request_regions(pdev, name);
	अगर (err)
		जाओ err_out_disable_pci_device;

	अगर (pci_resource_len(pdev, 0) < HIFN_BAR0_SIZE ||
	    pci_resource_len(pdev, 1) < HIFN_BAR1_SIZE ||
	    pci_resource_len(pdev, 2) < HIFN_BAR2_SIZE) अणु
		dev_err(&pdev->dev, "Broken hardware - I/O regions are too small.\n");
		err = -ENODEV;
		जाओ err_out_मुक्त_regions;
	पूर्ण

	dev = kzalloc(माप(काष्ठा hअगरn_device) + माप(काष्ठा crypto_alg),
			GFP_KERNEL);
	अगर (!dev) अणु
		err = -ENOMEM;
		जाओ err_out_मुक्त_regions;
	पूर्ण

	INIT_LIST_HEAD(&dev->alg_list);

	snम_लिखो(dev->name, माप(dev->name), "%s", name);
	spin_lock_init(&dev->lock);

	क्रम (i = 0; i < 3; ++i) अणु
		अचिन्हित दीर्घ addr, size;

		addr = pci_resource_start(pdev, i);
		size = pci_resource_len(pdev, i);

		dev->bar[i] = ioremap(addr, size);
		अगर (!dev->bar[i]) अणु
			err = -ENOMEM;
			जाओ err_out_unmap_bars;
		पूर्ण
	पूर्ण

	dev->desc_virt = dma_alloc_coherent(&pdev->dev,
					    माप(काष्ठा hअगरn_dma),
					    &dev->desc_dma, GFP_KERNEL);
	अगर (!dev->desc_virt) अणु
		dev_err(&pdev->dev, "Failed to allocate descriptor rings.\n");
		err = -ENOMEM;
		जाओ err_out_unmap_bars;
	पूर्ण

	dev->pdev = pdev;
	dev->irq = pdev->irq;

	क्रम (i = 0; i < HIFN_D_RES_RSIZE; ++i)
		dev->sa[i] = शून्य;

	pci_set_drvdata(pdev, dev);

	tasklet_init(&dev->tasklet, hअगरn_tasklet_callback, (अचिन्हित दीर्घ)dev);

	crypto_init_queue(&dev->queue, 1);

	err = request_irq(dev->irq, hअगरn_पूर्णांकerrupt, IRQF_SHARED, dev->name, dev);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to request IRQ%d: err: %d.\n",
			dev->irq, err);
		dev->irq = 0;
		जाओ err_out_मुक्त_desc;
	पूर्ण

	err = hअगरn_start_device(dev);
	अगर (err)
		जाओ err_out_मुक्त_irq;

	err = hअगरn_रेजिस्टर_rng(dev);
	अगर (err)
		जाओ err_out_stop_device;

	err = hअगरn_रेजिस्टर_alg(dev);
	अगर (err)
		जाओ err_out_unरेजिस्टर_rng;

	INIT_DELAYED_WORK(&dev->work, hअगरn_work);
	schedule_delayed_work(&dev->work, HZ);

	dev_dbg(&pdev->dev, "HIFN crypto accelerator card at %s has been "
		"successfully registered as %s.\n",
		pci_name(pdev), dev->name);

	वापस 0;

err_out_unरेजिस्टर_rng:
	hअगरn_unरेजिस्टर_rng(dev);
err_out_stop_device:
	hअगरn_reset_dma(dev, 1);
	hअगरn_stop_device(dev);
err_out_मुक्त_irq:
	मुक्त_irq(dev->irq, dev);
	tasklet_समाप्त(&dev->tasklet);
err_out_मुक्त_desc:
	dma_मुक्त_coherent(&pdev->dev, माप(काष्ठा hअगरn_dma), dev->desc_virt,
			  dev->desc_dma);

err_out_unmap_bars:
	क्रम (i = 0; i < 3; ++i)
		अगर (dev->bar[i])
			iounmap(dev->bar[i]);
	kमुक्त(dev);

err_out_मुक्त_regions:
	pci_release_regions(pdev);

err_out_disable_pci_device:
	pci_disable_device(pdev);

	वापस err;
पूर्ण

अटल व्योम hअगरn_हटाओ(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक i;
	काष्ठा hअगरn_device *dev;

	dev = pci_get_drvdata(pdev);

	अगर (dev) अणु
		cancel_delayed_work_sync(&dev->work);

		hअगरn_unरेजिस्टर_rng(dev);
		hअगरn_unरेजिस्टर_alg(dev);
		hअगरn_reset_dma(dev, 1);
		hअगरn_stop_device(dev);

		मुक्त_irq(dev->irq, dev);
		tasklet_समाप्त(&dev->tasklet);

		hअगरn_flush(dev);

		dma_मुक्त_coherent(&pdev->dev, माप(काष्ठा hअगरn_dma),
				  dev->desc_virt, dev->desc_dma);
		क्रम (i = 0; i < 3; ++i)
			अगर (dev->bar[i])
				iounmap(dev->bar[i]);

		kमुक्त(dev);
	पूर्ण

	pci_release_regions(pdev);
	pci_disable_device(pdev);
पूर्ण

अटल काष्ठा pci_device_id hअगरn_pci_tbl[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_HIFN, PCI_DEVICE_ID_HIFN_7955) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_HIFN, PCI_DEVICE_ID_HIFN_7956) पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, hअगरn_pci_tbl);

अटल काष्ठा pci_driver hअगरn_pci_driver = अणु
	.name     = "hifn795x",
	.id_table = hअगरn_pci_tbl,
	.probe    = hअगरn_probe,
	.हटाओ   = hअगरn_हटाओ,
पूर्ण;

अटल पूर्णांक __init hअगरn_init(व्योम)
अणु
	अचिन्हित पूर्णांक freq;
	पूर्णांक err;

	अगर (म_भेदन(hअगरn_pll_ref, "ext", 3) &&
	    म_भेदन(hअगरn_pll_ref, "pci", 3)) अणु
		pr_err("hifn795x: invalid hifn_pll_ref clock, must be pci or ext");
		वापस -EINVAL;
	पूर्ण

	/*
	 * For the 7955/7956 the reference घड़ी frequency must be in the
	 * range of 20MHz-100MHz. For the 7954 the upper bound is 66.67MHz,
	 * but this chip is currently not supported.
	 */
	अगर (hअगरn_pll_ref[3] != '\0') अणु
		freq = simple_म_से_अदीर्घ(hअगरn_pll_ref + 3, शून्य, 10);
		अगर (freq < 20 || freq > 100) अणु
			pr_err("hifn795x: invalid hifn_pll_ref frequency, must"
			       "be in the range of 20-100");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	err = pci_रेजिस्टर_driver(&hअगरn_pci_driver);
	अगर (err < 0) अणु
		pr_err("Failed to register PCI driver for %s device.\n",
		       hअगरn_pci_driver.name);
		वापस -ENODEV;
	पूर्ण

	pr_info("Driver for HIFN 795x crypto accelerator chip "
		"has been successfully registered.\n");

	वापस 0;
पूर्ण

अटल व्योम __निकास hअगरn_fini(व्योम)
अणु
	pci_unरेजिस्टर_driver(&hअगरn_pci_driver);

	pr_info("Driver for HIFN 795x crypto accelerator chip "
		"has been successfully unregistered.\n");
पूर्ण

module_init(hअगरn_init);
module_निकास(hअगरn_fini);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Evgeniy Polyakov <johnpol@2ka.mipt.ru>");
MODULE_DESCRIPTION("Driver for HIFN 795x crypto accelerator chip.");
