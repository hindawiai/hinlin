<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* include/linux/amba/pl080.h
 *
 * Copyright 2008 Openmoko, Inc.
 * Copyright 2008 Simtec Electronics
 *      http://armlinux.simtec.co.uk/
 *      Ben Dooks <ben@simtec.co.uk>
 *
 * ARM PrimeCell PL080 DMA controller
*/

/* Note, there are some Samsung updates to this controller block which
 * make it not entierly compatible with the PL080 specअगरication from
 * ARM. When in करोubt, check the Samsung करोcumentation first.
 *
 * The Samsung defines are PL080S, and add an extra control रेजिस्टर,
 * the ability to move more than 2^11 counts of data and some extra
 * Oneन_अंकD features.
*/

#अगर_अघोषित ASM_PL080_H
#घोषणा ASM_PL080_H

#घोषणा PL080_INT_STATUS			(0x00)
#घोषणा PL080_TC_STATUS				(0x04)
#घोषणा PL080_TC_CLEAR				(0x08)
#घोषणा PL080_ERR_STATUS			(0x0C)
#घोषणा PL080_ERR_CLEAR				(0x10)
#घोषणा PL080_RAW_TC_STATUS			(0x14)
#घोषणा PL080_RAW_ERR_STATUS			(0x18)
#घोषणा PL080_EN_CHAN				(0x1c)
#घोषणा PL080_SOFT_BREQ				(0x20)
#घोषणा PL080_SOFT_SREQ				(0x24)
#घोषणा PL080_SOFT_LBREQ			(0x28)
#घोषणा PL080_SOFT_LSREQ			(0x2C)

#घोषणा PL080_CONFIG				(0x30)
#घोषणा PL080_CONFIG_M2_BE			BIT(2)
#घोषणा PL080_CONFIG_M1_BE			BIT(1)
#घोषणा PL080_CONFIG_ENABLE			BIT(0)

#घोषणा PL080_SYNC				(0x34)

/* The Faraday Technology FTDMAC020 variant रेजिस्टरs */
#घोषणा FTDMAC020_CH_BUSY			(0x20)
/* Identical to PL080_CONFIG */
#घोषणा FTDMAC020_CSR				(0x24)
/* Identical to PL080_SYNC */
#घोषणा FTDMAC020_SYNC				(0x2C)
#घोषणा FTDMAC020_REVISION			(0x30)
#घोषणा FTDMAC020_FEATURE			(0x34)

/* Per channel configuration रेजिस्टरs */
#घोषणा PL080_Cx_BASE(x)			((0x100 + (x * 0x20)))
#घोषणा PL080_CH_SRC_ADDR			(0x00)
#घोषणा PL080_CH_DST_ADDR			(0x04)
#घोषणा PL080_CH_LLI				(0x08)
#घोषणा PL080_CH_CONTROL			(0x0C)
#घोषणा PL080_CH_CONFIG				(0x10)
#घोषणा PL080S_CH_CONTROL2			(0x10)
#घोषणा PL080S_CH_CONFIG			(0x14)
/* The Faraday FTDMAC020 derivative shuffles the रेजिस्टरs around */
#घोषणा FTDMAC020_CH_CSR			(0x00)
#घोषणा FTDMAC020_CH_CFG			(0x04)
#घोषणा FTDMAC020_CH_SRC_ADDR			(0x08)
#घोषणा FTDMAC020_CH_DST_ADDR			(0x0C)
#घोषणा FTDMAC020_CH_LLP			(0x10)
#घोषणा FTDMAC020_CH_SIZE			(0x14)

#घोषणा PL080_LLI_ADDR_MASK			GENMASK(31, 2)
#घोषणा PL080_LLI_ADDR_SHIFT			(2)
#घोषणा PL080_LLI_LM_AHB2			BIT(0)

#घोषणा PL080_CONTROL_TC_IRQ_EN			BIT(31)
#घोषणा PL080_CONTROL_PROT_MASK			GENMASK(30, 28)
#घोषणा PL080_CONTROL_PROT_SHIFT		(28)
#घोषणा PL080_CONTROL_PROT_CACHE		BIT(30)
#घोषणा PL080_CONTROL_PROT_BUFF			BIT(29)
#घोषणा PL080_CONTROL_PROT_SYS			BIT(28)
#घोषणा PL080_CONTROL_DST_INCR			BIT(27)
#घोषणा PL080_CONTROL_SRC_INCR			BIT(26)
#घोषणा PL080_CONTROL_DST_AHB2			BIT(25)
#घोषणा PL080_CONTROL_SRC_AHB2			BIT(24)
#घोषणा PL080_CONTROL_DWIDTH_MASK		GENMASK(23, 21)
#घोषणा PL080_CONTROL_DWIDTH_SHIFT		(21)
#घोषणा PL080_CONTROL_SWIDTH_MASK		GENMASK(20, 18)
#घोषणा PL080_CONTROL_SWIDTH_SHIFT		(18)
#घोषणा PL080_CONTROL_DB_SIZE_MASK		GENMASK(17, 15)
#घोषणा PL080_CONTROL_DB_SIZE_SHIFT		(15)
#घोषणा PL080_CONTROL_SB_SIZE_MASK		GENMASK(14, 12)
#घोषणा PL080_CONTROL_SB_SIZE_SHIFT		(12)
#घोषणा PL080_CONTROL_TRANSFER_SIZE_MASK	GENMASK(11, 0)
#घोषणा PL080S_CONTROL_TRANSFER_SIZE_MASK	GENMASK(24, 0)
#घोषणा PL080_CONTROL_TRANSFER_SIZE_SHIFT	(0)

#घोषणा PL080_BSIZE_1				(0x0)
#घोषणा PL080_BSIZE_4				(0x1)
#घोषणा PL080_BSIZE_8				(0x2)
#घोषणा PL080_BSIZE_16				(0x3)
#घोषणा PL080_BSIZE_32				(0x4)
#घोषणा PL080_BSIZE_64				(0x5)
#घोषणा PL080_BSIZE_128				(0x6)
#घोषणा PL080_BSIZE_256				(0x7)

#घोषणा PL080_WIDTH_8BIT			(0x0)
#घोषणा PL080_WIDTH_16BIT			(0x1)
#घोषणा PL080_WIDTH_32BIT			(0x2)

#घोषणा PL080N_CONFIG_ITPROT			BIT(20)
#घोषणा PL080N_CONFIG_SECPROT			BIT(19)
#घोषणा PL080_CONFIG_HALT			BIT(18)
#घोषणा PL080_CONFIG_ACTIVE			BIT(17)  /* RO */
#घोषणा PL080_CONFIG_LOCK			BIT(16)
#घोषणा PL080_CONFIG_TC_IRQ_MASK		BIT(15)
#घोषणा PL080_CONFIG_ERR_IRQ_MASK		BIT(14)
#घोषणा PL080_CONFIG_FLOW_CONTROL_MASK		GENMASK(13, 11)
#घोषणा PL080_CONFIG_FLOW_CONTROL_SHIFT		(11)
#घोषणा PL080_CONFIG_DST_SEL_MASK		GENMASK(9, 6)
#घोषणा PL080_CONFIG_DST_SEL_SHIFT		(6)
#घोषणा PL080_CONFIG_SRC_SEL_MASK		GENMASK(4, 1)
#घोषणा PL080_CONFIG_SRC_SEL_SHIFT		(1)
#घोषणा PL080_CONFIG_ENABLE			BIT(0)

#घोषणा PL080_FLOW_MEM2MEM			(0x0)
#घोषणा PL080_FLOW_MEM2PER			(0x1)
#घोषणा PL080_FLOW_PER2MEM			(0x2)
#घोषणा PL080_FLOW_SRC2DST			(0x3)
#घोषणा PL080_FLOW_SRC2DST_DST			(0x4)
#घोषणा PL080_FLOW_MEM2PER_PER			(0x5)
#घोषणा PL080_FLOW_PER2MEM_PER			(0x6)
#घोषणा PL080_FLOW_SRC2DST_SRC			(0x7)

#घोषणा FTDMAC020_CH_CSR_TC_MSK			BIT(31)
/* Later versions have a threshold in bits 24..26,  */
#घोषणा FTDMAC020_CH_CSR_FIFOTH_MSK		GENMASK(26, 24)
#घोषणा FTDMAC020_CH_CSR_FIFOTH_SHIFT		(24)
#घोषणा FTDMAC020_CH_CSR_CHPR1_MSK		GENMASK(23, 22)
#घोषणा FTDMAC020_CH_CSR_PROT3			BIT(21)
#घोषणा FTDMAC020_CH_CSR_PROT2			BIT(20)
#घोषणा FTDMAC020_CH_CSR_PROT1			BIT(19)
#घोषणा FTDMAC020_CH_CSR_SRC_SIZE_MSK		GENMASK(18, 16)
#घोषणा FTDMAC020_CH_CSR_SRC_SIZE_SHIFT		(16)
#घोषणा FTDMAC020_CH_CSR_ABT			BIT(15)
#घोषणा FTDMAC020_CH_CSR_SRC_WIDTH_MSK		GENMASK(13, 11)
#घोषणा FTDMAC020_CH_CSR_SRC_WIDTH_SHIFT	(11)
#घोषणा FTDMAC020_CH_CSR_DST_WIDTH_MSK		GENMASK(10, 8)
#घोषणा FTDMAC020_CH_CSR_DST_WIDTH_SHIFT	(8)
#घोषणा FTDMAC020_CH_CSR_MODE			BIT(7)
/* 00 = increase, 01 = decrease, 10 = fix */
#घोषणा FTDMAC020_CH_CSR_SRCAD_CTL_MSK		GENMASK(6, 5)
#घोषणा FTDMAC020_CH_CSR_SRCAD_CTL_SHIFT	(5)
#घोषणा FTDMAC020_CH_CSR_DSTAD_CTL_MSK		GENMASK(4, 3)
#घोषणा FTDMAC020_CH_CSR_DSTAD_CTL_SHIFT	(3)
#घोषणा FTDMAC020_CH_CSR_SRC_SEL		BIT(2)
#घोषणा FTDMAC020_CH_CSR_DST_SEL		BIT(1)
#घोषणा FTDMAC020_CH_CSR_EN			BIT(0)

/* FIFO threshold setting */
#घोषणा FTDMAC020_CH_CSR_FIFOTH_1		(0x0)
#घोषणा FTDMAC020_CH_CSR_FIFOTH_2		(0x1)
#घोषणा FTDMAC020_CH_CSR_FIFOTH_4		(0x2)
#घोषणा FTDMAC020_CH_CSR_FIFOTH_8		(0x3)
#घोषणा FTDMAC020_CH_CSR_FIFOTH_16		(0x4)
/* The FTDMAC020 supports 64bit wide transfers */
#घोषणा FTDMAC020_WIDTH_64BIT			(0x3)
/* Address can be increased, decreased or fixed */
#घोषणा FTDMAC020_CH_CSR_SRCAD_CTL_INC		(0x0)
#घोषणा FTDMAC020_CH_CSR_SRCAD_CTL_DEC		(0x1)
#घोषणा FTDMAC020_CH_CSR_SRCAD_CTL_FIXED	(0x2)

#घोषणा FTDMAC020_CH_CFG_LLP_CNT_MASK		GENMASK(19, 16)
#घोषणा FTDMAC020_CH_CFG_LLP_CNT_SHIFT		(16)
#घोषणा FTDMAC020_CH_CFG_BUSY			BIT(8)
#घोषणा FTDMAC020_CH_CFG_INT_ABT_MASK		BIT(2)
#घोषणा FTDMAC020_CH_CFG_INT_ERR_MASK		BIT(1)
#घोषणा FTDMAC020_CH_CFG_INT_TC_MASK		BIT(0)

/* Inside the LLIs, the applicable CSR fields are mapped dअगरferently */
#घोषणा FTDMAC020_LLI_TC_MSK			BIT(28)
#घोषणा FTDMAC020_LLI_SRC_WIDTH_MSK		GENMASK(27, 25)
#घोषणा FTDMAC020_LLI_SRC_WIDTH_SHIFT		(25)
#घोषणा FTDMAC020_LLI_DST_WIDTH_MSK		GENMASK(24, 22)
#घोषणा FTDMAC020_LLI_DST_WIDTH_SHIFT		(22)
#घोषणा FTDMAC020_LLI_SRCAD_CTL_MSK		GENMASK(21, 20)
#घोषणा FTDMAC020_LLI_SRCAD_CTL_SHIFT		(20)
#घोषणा FTDMAC020_LLI_DSTAD_CTL_MSK		GENMASK(19, 18)
#घोषणा FTDMAC020_LLI_DSTAD_CTL_SHIFT		(18)
#घोषणा FTDMAC020_LLI_SRC_SEL			BIT(17)
#घोषणा FTDMAC020_LLI_DST_SEL			BIT(16)
#घोषणा FTDMAC020_LLI_TRANSFER_SIZE_MASK	GENMASK(11, 0)
#घोषणा FTDMAC020_LLI_TRANSFER_SIZE_SHIFT	(0)

#घोषणा FTDMAC020_CFG_LLP_CNT_MASK		GENMASK(19, 16)
#घोषणा FTDMAC020_CFG_LLP_CNT_SHIFT		(16)
#घोषणा FTDMAC020_CFG_BUSY			BIT(8)
#घोषणा FTDMAC020_CFG_INT_ABT_MSK		BIT(2)
#घोषणा FTDMAC020_CFG_INT_ERR_MSK		BIT(1)
#घोषणा FTDMAC020_CFG_INT_TC_MSK		BIT(0)

/* DMA linked list chain काष्ठाure */

काष्ठा pl080_lli अणु
	u32	src_addr;
	u32	dst_addr;
	u32	next_lli;
	u32	control0;
पूर्ण;

काष्ठा pl080s_lli अणु
	u32	src_addr;
	u32	dst_addr;
	u32	next_lli;
	u32	control0;
	u32	control1;
पूर्ण;

#पूर्ण_अगर /* ASM_PL080_H */
