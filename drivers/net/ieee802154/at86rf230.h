<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * AT86RF230/RF231 driver
 *
 * Copyright (C) 2009-2012 Siemens AG
 *
 * Written by:
 * Dmitry Eremin-Solenikov <dbaryshkov@gmail.com>
 * Alexander Smirnov <alex.bluesman.smirnov@gmail.com>
 */

#अगर_अघोषित _AT86RF230_H
#घोषणा _AT86RF230_H

#घोषणा RG_TRX_STATUS	(0x01)
#घोषणा SR_TRX_STATUS		0x01, 0x1f, 0
#घोषणा SR_RESERVED_01_3	0x01, 0x20, 5
#घोषणा SR_CCA_STATUS		0x01, 0x40, 6
#घोषणा SR_CCA_DONE		0x01, 0x80, 7
#घोषणा RG_TRX_STATE	(0x02)
#घोषणा SR_TRX_CMD		0x02, 0x1f, 0
#घोषणा SR_TRAC_STATUS		0x02, 0xe0, 5
#घोषणा RG_TRX_CTRL_0	(0x03)
#घोषणा SR_CLKM_CTRL		0x03, 0x07, 0
#घोषणा SR_CLKM_SHA_SEL		0x03, 0x08, 3
#घोषणा SR_PAD_IO_CLKM		0x03, 0x30, 4
#घोषणा SR_PAD_IO		0x03, 0xc0, 6
#घोषणा RG_TRX_CTRL_1	(0x04)
#घोषणा SR_IRQ_POLARITY		0x04, 0x01, 0
#घोषणा SR_IRQ_MASK_MODE	0x04, 0x02, 1
#घोषणा SR_SPI_CMD_MODE		0x04, 0x0c, 2
#घोषणा SR_RX_BL_CTRL		0x04, 0x10, 4
#घोषणा SR_TX_AUTO_CRC_ON	0x04, 0x20, 5
#घोषणा SR_IRQ_2_EXT_EN		0x04, 0x40, 6
#घोषणा SR_PA_EXT_EN		0x04, 0x80, 7
#घोषणा RG_PHY_TX_PWR	(0x05)
#घोषणा SR_TX_PWR_23X		0x05, 0x0f, 0
#घोषणा SR_PA_LT_230		0x05, 0x30, 4
#घोषणा SR_PA_BUF_LT_230	0x05, 0xc0, 6
#घोषणा SR_TX_PWR_212		0x05, 0x1f, 0
#घोषणा SR_GC_PA_212		0x05, 0x60, 5
#घोषणा SR_PA_BOOST_LT_212	0x05, 0x80, 7
#घोषणा RG_PHY_RSSI	(0x06)
#घोषणा SR_RSSI			0x06, 0x1f, 0
#घोषणा SR_RND_VALUE		0x06, 0x60, 5
#घोषणा SR_RX_CRC_VALID		0x06, 0x80, 7
#घोषणा RG_PHY_ED_LEVEL	(0x07)
#घोषणा SR_ED_LEVEL		0x07, 0xff, 0
#घोषणा RG_PHY_CC_CCA	(0x08)
#घोषणा SR_CHANNEL		0x08, 0x1f, 0
#घोषणा SR_CCA_MODE		0x08, 0x60, 5
#घोषणा SR_CCA_REQUEST		0x08, 0x80, 7
#घोषणा RG_CCA_THRES	(0x09)
#घोषणा SR_CCA_ED_THRES		0x09, 0x0f, 0
#घोषणा SR_RESERVED_09_1	0x09, 0xf0, 4
#घोषणा RG_RX_CTRL	(0x0a)
#घोषणा SR_PDT_THRES		0x0a, 0x0f, 0
#घोषणा SR_RESERVED_0a_1	0x0a, 0xf0, 4
#घोषणा RG_SFD_VALUE	(0x0b)
#घोषणा SR_SFD_VALUE		0x0b, 0xff, 0
#घोषणा RG_TRX_CTRL_2	(0x0c)
#घोषणा SR_OQPSK_DATA_RATE	0x0c, 0x03, 0
#घोषणा SR_SUB_MODE		0x0c, 0x04, 2
#घोषणा SR_BPSK_QPSK		0x0c, 0x08, 3
#घोषणा SR_OQPSK_SUB1_RC_EN	0x0c, 0x10, 4
#घोषणा SR_RESERVED_0c_5	0x0c, 0x60, 5
#घोषणा SR_RX_SAFE_MODE		0x0c, 0x80, 7
#घोषणा RG_ANT_DIV	(0x0d)
#घोषणा SR_ANT_CTRL		0x0d, 0x03, 0
#घोषणा SR_ANT_EXT_SW_EN	0x0d, 0x04, 2
#घोषणा SR_ANT_DIV_EN		0x0d, 0x08, 3
#घोषणा SR_RESERVED_0d_2	0x0d, 0x70, 4
#घोषणा SR_ANT_SEL		0x0d, 0x80, 7
#घोषणा RG_IRQ_MASK	(0x0e)
#घोषणा SR_IRQ_MASK		0x0e, 0xff, 0
#घोषणा RG_IRQ_STATUS	(0x0f)
#घोषणा SR_IRQ_0_PLL_LOCK	0x0f, 0x01, 0
#घोषणा SR_IRQ_1_PLL_UNLOCK	0x0f, 0x02, 1
#घोषणा SR_IRQ_2_RX_START	0x0f, 0x04, 2
#घोषणा SR_IRQ_3_TRX_END	0x0f, 0x08, 3
#घोषणा SR_IRQ_4_CCA_ED_DONE	0x0f, 0x10, 4
#घोषणा SR_IRQ_5_AMI		0x0f, 0x20, 5
#घोषणा SR_IRQ_6_TRX_UR		0x0f, 0x40, 6
#घोषणा SR_IRQ_7_BAT_LOW	0x0f, 0x80, 7
#घोषणा RG_VREG_CTRL	(0x10)
#घोषणा SR_RESERVED_10_6	0x10, 0x03, 0
#घोषणा SR_DVDD_OK		0x10, 0x04, 2
#घोषणा SR_DVREG_EXT		0x10, 0x08, 3
#घोषणा SR_RESERVED_10_3	0x10, 0x30, 4
#घोषणा SR_AVDD_OK		0x10, 0x40, 6
#घोषणा SR_AVREG_EXT		0x10, 0x80, 7
#घोषणा RG_BATMON	(0x11)
#घोषणा SR_BATMON_VTH		0x11, 0x0f, 0
#घोषणा SR_BATMON_HR		0x11, 0x10, 4
#घोषणा SR_BATMON_OK		0x11, 0x20, 5
#घोषणा SR_RESERVED_11_1	0x11, 0xc0, 6
#घोषणा RG_XOSC_CTRL	(0x12)
#घोषणा SR_XTAL_TRIM		0x12, 0x0f, 0
#घोषणा SR_XTAL_MODE		0x12, 0xf0, 4
#घोषणा RG_RX_SYN	(0x15)
#घोषणा SR_RX_PDT_LEVEL		0x15, 0x0f, 0
#घोषणा SR_RESERVED_15_2	0x15, 0x70, 4
#घोषणा SR_RX_PDT_DIS		0x15, 0x80, 7
#घोषणा RG_XAH_CTRL_1	(0x17)
#घोषणा SR_RESERVED_17_8	0x17, 0x01, 0
#घोषणा SR_AACK_PROM_MODE	0x17, 0x02, 1
#घोषणा SR_AACK_ACK_TIME	0x17, 0x04, 2
#घोषणा SR_RESERVED_17_5	0x17, 0x08, 3
#घोषणा SR_AACK_UPLD_RES_FT	0x17, 0x10, 4
#घोषणा SR_AACK_FLTR_RES_FT	0x17, 0x20, 5
#घोषणा SR_CSMA_LBT_MODE	0x17, 0x40, 6
#घोषणा SR_RESERVED_17_1	0x17, 0x80, 7
#घोषणा RG_FTN_CTRL	(0x18)
#घोषणा SR_RESERVED_18_2	0x18, 0x7f, 0
#घोषणा SR_FTN_START		0x18, 0x80, 7
#घोषणा RG_PLL_CF	(0x1a)
#घोषणा SR_RESERVED_1a_2	0x1a, 0x7f, 0
#घोषणा SR_PLL_CF_START		0x1a, 0x80, 7
#घोषणा RG_PLL_DCU	(0x1b)
#घोषणा SR_RESERVED_1b_3	0x1b, 0x3f, 0
#घोषणा SR_RESERVED_1b_2	0x1b, 0x40, 6
#घोषणा SR_PLL_DCU_START	0x1b, 0x80, 7
#घोषणा RG_PART_NUM	(0x1c)
#घोषणा SR_PART_NUM		0x1c, 0xff, 0
#घोषणा RG_VERSION_NUM	(0x1d)
#घोषणा SR_VERSION_NUM		0x1d, 0xff, 0
#घोषणा RG_MAN_ID_0	(0x1e)
#घोषणा SR_MAN_ID_0		0x1e, 0xff, 0
#घोषणा RG_MAN_ID_1	(0x1f)
#घोषणा SR_MAN_ID_1		0x1f, 0xff, 0
#घोषणा RG_SHORT_ADDR_0	(0x20)
#घोषणा SR_SHORT_ADDR_0		0x20, 0xff, 0
#घोषणा RG_SHORT_ADDR_1	(0x21)
#घोषणा SR_SHORT_ADDR_1		0x21, 0xff, 0
#घोषणा RG_PAN_ID_0	(0x22)
#घोषणा SR_PAN_ID_0		0x22, 0xff, 0
#घोषणा RG_PAN_ID_1	(0x23)
#घोषणा SR_PAN_ID_1		0x23, 0xff, 0
#घोषणा RG_IEEE_ADDR_0	(0x24)
#घोषणा SR_IEEE_ADDR_0		0x24, 0xff, 0
#घोषणा RG_IEEE_ADDR_1	(0x25)
#घोषणा SR_IEEE_ADDR_1		0x25, 0xff, 0
#घोषणा RG_IEEE_ADDR_2	(0x26)
#घोषणा SR_IEEE_ADDR_2		0x26, 0xff, 0
#घोषणा RG_IEEE_ADDR_3	(0x27)
#घोषणा SR_IEEE_ADDR_3		0x27, 0xff, 0
#घोषणा RG_IEEE_ADDR_4	(0x28)
#घोषणा SR_IEEE_ADDR_4		0x28, 0xff, 0
#घोषणा RG_IEEE_ADDR_5	(0x29)
#घोषणा SR_IEEE_ADDR_5		0x29, 0xff, 0
#घोषणा RG_IEEE_ADDR_6	(0x2a)
#घोषणा SR_IEEE_ADDR_6		0x2a, 0xff, 0
#घोषणा RG_IEEE_ADDR_7	(0x2b)
#घोषणा SR_IEEE_ADDR_7		0x2b, 0xff, 0
#घोषणा RG_XAH_CTRL_0	(0x2c)
#घोषणा SR_SLOTTED_OPERATION	0x2c, 0x01, 0
#घोषणा SR_MAX_CSMA_RETRIES	0x2c, 0x0e, 1
#घोषणा SR_MAX_FRAME_RETRIES	0x2c, 0xf0, 4
#घोषणा RG_CSMA_SEED_0	(0x2d)
#घोषणा SR_CSMA_SEED_0		0x2d, 0xff, 0
#घोषणा RG_CSMA_SEED_1	(0x2e)
#घोषणा SR_CSMA_SEED_1		0x2e, 0x07, 0
#घोषणा SR_AACK_I_AM_COORD	0x2e, 0x08, 3
#घोषणा SR_AACK_DIS_ACK		0x2e, 0x10, 4
#घोषणा SR_AACK_SET_PD		0x2e, 0x20, 5
#घोषणा SR_AACK_FVN_MODE	0x2e, 0xc0, 6
#घोषणा RG_CSMA_BE	(0x2f)
#घोषणा SR_MIN_BE		0x2f, 0x0f, 0
#घोषणा SR_MAX_BE		0x2f, 0xf0, 4

#घोषणा CMD_REG		0x80
#घोषणा CMD_REG_MASK	0x3f
#घोषणा CMD_WRITE	0x40
#घोषणा CMD_FB		0x20

#घोषणा IRQ_BAT_LOW	BIT(7)
#घोषणा IRQ_TRX_UR	BIT(6)
#घोषणा IRQ_AMI		BIT(5)
#घोषणा IRQ_CCA_ED	BIT(4)
#घोषणा IRQ_TRX_END	BIT(3)
#घोषणा IRQ_RX_START	BIT(2)
#घोषणा IRQ_PLL_UNL	BIT(1)
#घोषणा IRQ_PLL_LOCK	BIT(0)

#घोषणा IRQ_ACTIVE_HIGH	0
#घोषणा IRQ_ACTIVE_LOW	1

#घोषणा STATE_P_ON		0x00	/* BUSY */
#घोषणा STATE_BUSY_RX		0x01
#घोषणा STATE_BUSY_TX		0x02
#घोषणा STATE_FORCE_TRX_OFF	0x03
#घोषणा STATE_FORCE_TX_ON	0x04	/* IDLE */
/* 0x05 */				/* INVALID_PARAMETER */
#घोषणा STATE_RX_ON		0x06
/* 0x07 */				/* SUCCESS */
#घोषणा STATE_TRX_OFF		0x08
#घोषणा STATE_TX_ON		0x09
/* 0x0a - 0x0e */			/* 0x0a - UNSUPPORTED_ATTRIBUTE */
#घोषणा STATE_SLEEP		0x0F
#घोषणा STATE_PREP_DEEP_SLEEP	0x10
#घोषणा STATE_BUSY_RX_AACK	0x11
#घोषणा STATE_BUSY_TX_ARET	0x12
#घोषणा STATE_RX_AACK_ON	0x16
#घोषणा STATE_TX_ARET_ON	0x19
#घोषणा STATE_RX_ON_NOCLK	0x1C
#घोषणा STATE_RX_AACK_ON_NOCLK	0x1D
#घोषणा STATE_BUSY_RX_AACK_NOCLK 0x1E
#घोषणा STATE_TRANSITION_IN_PROGRESS 0x1F

#घोषणा TRX_STATE_MASK		(0x1F)
#घोषणा TRAC_MASK(x)		((x & 0xe0) >> 5)

#घोषणा TRAC_SUCCESS			0
#घोषणा TRAC_SUCCESS_DATA_PENDING	1
#घोषणा TRAC_SUCCESS_WAIT_FOR_ACK	2
#घोषणा TRAC_CHANNEL_ACCESS_FAILURE	3
#घोषणा TRAC_NO_ACK			5
#घोषणा TRAC_INVALID			7

#पूर्ण_अगर /* !_AT86RF230_H */
