<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2011 Marvell International Ltd. All rights reserved.
 */

#अगर_अघोषित __ASM_ARCH_REGS_USB_H
#घोषणा __ASM_ARCH_REGS_USB_H

#घोषणा PXA168_U2O_REGBASE	(0xd4208000)
#घोषणा PXA168_U2O_PHYBASE	(0xd4207000)

#घोषणा PXA168_U2H_REGBASE      (0xd4209000)
#घोषणा PXA168_U2H_PHYBASE      (0xd4206000)

#घोषणा MMP3_HSIC1_REGBASE	(0xf0001000)
#घोषणा MMP3_HSIC1_PHYBASE	(0xf0001800)

#घोषणा MMP3_HSIC2_REGBASE	(0xf0002000)
#घोषणा MMP3_HSIC2_PHYBASE	(0xf0002800)

#घोषणा MMP3_FSIC_REGBASE	(0xf0003000)
#घोषणा MMP3_FSIC_PHYBASE	(0xf0003800)


#घोषणा USB_REG_RANGE		(0x1ff)
#घोषणा USB_PHY_RANGE		(0xff)

/* रेजिस्टरs */
#घोषणा U2x_CAPREGS_OFFSET       0x100

/* phy regs */
#घोषणा UTMI_REVISION		0x0
#घोषणा UTMI_CTRL		0x4
#घोषणा UTMI_PLL		0x8
#घोषणा UTMI_TX			0xc
#घोषणा UTMI_RX			0x10
#घोषणा UTMI_IVREF		0x14
#घोषणा UTMI_T0			0x18
#घोषणा UTMI_T1			0x1c
#घोषणा UTMI_T2			0x20
#घोषणा UTMI_T3			0x24
#घोषणा UTMI_T4			0x28
#घोषणा UTMI_T5			0x2c
#घोषणा UTMI_RESERVE		0x30
#घोषणा UTMI_USB_INT		0x34
#घोषणा UTMI_DBG_CTL		0x38
#घोषणा UTMI_OTG_ADDON		0x3c

/* For UTMICTRL Register */
#घोषणा UTMI_CTRL_USB_CLK_EN                    (1 << 31)
/* pxa168 */
#घोषणा UTMI_CTRL_SUSPEND_SET1                  (1 << 30)
#घोषणा UTMI_CTRL_SUSPEND_SET2                  (1 << 29)
#घोषणा UTMI_CTRL_RXBUF_PDWN                    (1 << 24)
#घोषणा UTMI_CTRL_TXBUF_PDWN                    (1 << 11)

#घोषणा UTMI_CTRL_INPKT_DELAY_SHIFT             30
#घोषणा UTMI_CTRL_INPKT_DELAY_SOF_SHIFT		28
#घोषणा UTMI_CTRL_PU_REF_SHIFT			20
#घोषणा UTMI_CTRL_ARC_PULLDN_SHIFT              12
#घोषणा UTMI_CTRL_PLL_PWR_UP_SHIFT              1
#घोषणा UTMI_CTRL_PWR_UP_SHIFT                  0

/* For UTMI_PLL Register */
#घोषणा UTMI_PLL_PLLCALI12_SHIFT		29
#घोषणा UTMI_PLL_PLLCALI12_MASK			(0x3 << 29)

#घोषणा UTMI_PLL_PLLVDD18_SHIFT			27
#घोषणा UTMI_PLL_PLLVDD18_MASK			(0x3 << 27)

#घोषणा UTMI_PLL_PLLVDD12_SHIFT			25
#घोषणा UTMI_PLL_PLLVDD12_MASK			(0x3 << 25)

#घोषणा UTMI_PLL_CLK_BLK_EN_SHIFT               24
#घोषणा CLK_BLK_EN                              (0x1 << 24)
#घोषणा PLL_READY                               (0x1 << 23)
#घोषणा KVCO_EXT                                (0x1 << 22)
#घोषणा VCOCAL_START                            (0x1 << 21)

#घोषणा UTMI_PLL_KVCO_SHIFT			15
#घोषणा UTMI_PLL_KVCO_MASK                      (0x7 << 15)

#घोषणा UTMI_PLL_ICP_SHIFT			12
#घोषणा UTMI_PLL_ICP_MASK                       (0x7 << 12)

#घोषणा UTMI_PLL_FBDIV_SHIFT                    4
#घोषणा UTMI_PLL_FBDIV_MASK                     (0xFF << 4)

#घोषणा UTMI_PLL_REFDIV_SHIFT                   0
#घोषणा UTMI_PLL_REFDIV_MASK                    (0xF << 0)

/* For UTMI_TX Register */
#घोषणा UTMI_TX_REG_EXT_FS_RCAL_SHIFT		27
#घोषणा UTMI_TX_REG_EXT_FS_RCAL_MASK		(0xf << 27)

#घोषणा UTMI_TX_REG_EXT_FS_RCAL_EN_SHIFT	26
#घोषणा UTMI_TX_REG_EXT_FS_RCAL_EN_MASK		(0x1 << 26)

#घोषणा UTMI_TX_TXVDD12_SHIFT                   22
#घोषणा UTMI_TX_TXVDD12_MASK                    (0x3 << 22)

#घोषणा UTMI_TX_CK60_PHSEL_SHIFT                17
#घोषणा UTMI_TX_CK60_PHSEL_MASK                 (0xf << 17)

#घोषणा UTMI_TX_IMPCAL_VTH_SHIFT                14
#घोषणा UTMI_TX_IMPCAL_VTH_MASK                 (0x7 << 14)

#घोषणा REG_RCAL_START                          (0x1 << 12)

#घोषणा UTMI_TX_LOW_VDD_EN_SHIFT                11

#घोषणा UTMI_TX_AMP_SHIFT			0
#घोषणा UTMI_TX_AMP_MASK			(0x7 << 0)

/* For UTMI_RX Register */
#घोषणा UTMI_REG_SQ_LENGTH_SHIFT                15
#घोषणा UTMI_REG_SQ_LENGTH_MASK                 (0x3 << 15)

#घोषणा UTMI_RX_SQ_THRESH_SHIFT                 4
#घोषणा UTMI_RX_SQ_THRESH_MASK                  (0xf << 4)

#घोषणा UTMI_OTG_ADDON_OTG_ON			(1 << 0)

/* fsic रेजिस्टरs */
#घोषणा FSIC_MISC			0x4
#घोषणा FSIC_INT			0x28
#घोषणा FSIC_CTRL			0x30

/* HSIC रेजिस्टरs */
#घोषणा HSIC_PAD_CTRL			0x4

#घोषणा HSIC_CTRL			0x8
#घोषणा HSIC_CTRL_HSIC_ENABLE		(1<<7)
#घोषणा HSIC_CTRL_PLL_BYPASS		(1<<4)

#घोषणा TEST_GRP_0			0xc
#घोषणा TEST_GRP_1			0x10

#घोषणा HSIC_INT			0x14
#घोषणा HSIC_INT_READY_INT_EN		(1<<10)
#घोषणा HSIC_INT_CONNECT_INT_EN		(1<<9)
#घोषणा HSIC_INT_CORE_INT_EN		(1<<8)
#घोषणा HSIC_INT_HS_READY		(1<<2)
#घोषणा HSIC_INT_CONNECT		(1<<1)
#घोषणा HSIC_INT_CORE			(1<<0)

#घोषणा HSIC_CONFIG			0x18
#घोषणा USBHSIC_CTRL			0x20

#घोषणा HSIC_USB_CTRL			0x28
#घोषणा HSIC_USB_CTRL_CLKEN		1
#घोषणा	HSIC_USB_CLK_PHY		0x0
#घोषणा HSIC_USB_CLK_PMU		0x1

#पूर्ण_अगर /* __ASM_ARCH_PXA_U2O_H */
