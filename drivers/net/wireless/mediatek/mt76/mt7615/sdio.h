<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/* Copyright (C) 2020 MediaTek Inc.
 *
 * Author: Sean Wang <sean.wang@mediatek.com>
 */

#अगर_अघोषित __MT76S_H
#घोषणा __MT76S_H

#घोषणा MT_PSE_PAGE_SZ			128

#घोषणा MCR_WCIR			0x0000
#घोषणा MCR_WHLPCR			0x0004
#घोषणा WHLPCR_FW_OWN_REQ_CLR		BIT(9)
#घोषणा WHLPCR_FW_OWN_REQ_SET		BIT(8)
#घोषणा WHLPCR_IS_DRIVER_OWN		BIT(8)
#घोषणा WHLPCR_INT_EN_CLR		BIT(1)
#घोषणा WHLPCR_INT_EN_SET		BIT(0)

#घोषणा MCR_WSDIOCSR			0x0008
#घोषणा MCR_WHCR			0x000C
#घोषणा W_INT_CLR_CTRL			BIT(1)
#घोषणा RECV_MAILBOX_RD_CLR_EN		BIT(2)
#घोषणा MAX_HIF_RX_LEN_NUM		GENMASK(13, 8)
#घोषणा RX_ENHANCE_MODE			BIT(16)

#घोषणा MCR_WHISR			0x0010
#घोषणा MCR_WHIER			0x0014
#घोषणा WHIER_D2H_SW_INT		GENMASK(31, 8)
#घोषणा WHIER_FW_OWN_BACK_INT_EN	BIT(7)
#घोषणा WHIER_ABNORMAL_INT_EN		BIT(6)
#घोषणा WHIER_RX1_DONE_INT_EN		BIT(2)
#घोषणा WHIER_RX0_DONE_INT_EN		BIT(1)
#घोषणा WHIER_TX_DONE_INT_EN		BIT(0)
#घोषणा WHIER_DEFAULT			(WHIER_RX0_DONE_INT_EN	| \
					 WHIER_RX1_DONE_INT_EN	| \
					 WHIER_TX_DONE_INT_EN	| \
					 WHIER_ABNORMAL_INT_EN	| \
					 WHIER_D2H_SW_INT)

#घोषणा MCR_WASR			0x0020
#घोषणा MCR_WSICR			0x0024
#घोषणा MCR_WTSR0			0x0028
#घोषणा TQ0_CNT				GENMASK(7, 0)
#घोषणा TQ1_CNT				GENMASK(15, 8)
#घोषणा TQ2_CNT				GENMASK(23, 16)
#घोषणा TQ3_CNT				GENMASK(31, 24)

#घोषणा MCR_WTSR1			0x002c
#घोषणा TQ4_CNT				GENMASK(7, 0)
#घोषणा TQ5_CNT				GENMASK(15, 8)
#घोषणा TQ6_CNT				GENMASK(23, 16)
#घोषणा TQ7_CNT				GENMASK(31, 24)

#घोषणा MCR_WTDR1			0x0034
#घोषणा MCR_WRDR0			0x0050
#घोषणा MCR_WRDR1			0x0054
#घोषणा MCR_WRDR(p)			(0x0050 + 4 * (p))
#घोषणा MCR_H2DSM0R			0x0070
#घोषणा H2D_SW_INT_READ			BIT(16)
#घोषणा H2D_SW_INT_WRITE		BIT(17)

#घोषणा MCR_H2DSM1R			0x0074
#घोषणा MCR_D2HRM0R			0x0078
#घोषणा MCR_D2HRM1R			0x007c
#घोषणा MCR_D2HRM2R			0x0080
#घोषणा MCR_WRPLR			0x0090
#घोषणा RX0_PACKET_LENGTH		GENMASK(15, 0)
#घोषणा RX1_PACKET_LENGTH		GENMASK(31, 16)

#घोषणा MCR_WTMDR			0x00b0
#घोषणा MCR_WTMCR			0x00b4
#घोषणा MCR_WTMDPCR0			0x00b8
#घोषणा MCR_WTMDPCR1			0x00bc
#घोषणा MCR_WPLRCR			0x00d4
#घोषणा MCR_WSR				0x00D8
#घोषणा MCR_CLKIOCR			0x0100
#घोषणा MCR_CMDIOCR			0x0104
#घोषणा MCR_DAT0IOCR			0x0108
#घोषणा MCR_DAT1IOCR			0x010C
#घोषणा MCR_DAT2IOCR			0x0110
#घोषणा MCR_DAT3IOCR			0x0114
#घोषणा MCR_CLKDLYCR			0x0118
#घोषणा MCR_CMDDLYCR			0x011C
#घोषणा MCR_ODATDLYCR			0x0120
#घोषणा MCR_IDATDLYCR1			0x0124
#घोषणा MCR_IDATDLYCR2			0x0128
#घोषणा MCR_ILCHCR			0x012C
#घोषणा MCR_WTQCR0			0x0130
#घोषणा MCR_WTQCR1			0x0134
#घोषणा MCR_WTQCR2			0x0138
#घोषणा MCR_WTQCR3			0x013C
#घोषणा MCR_WTQCR4			0x0140
#घोषणा MCR_WTQCR5			0x0144
#घोषणा MCR_WTQCR6			0x0148
#घोषणा MCR_WTQCR7			0x014C
#घोषणा MCR_WTQCR(x)                   (0x130 + 4 * (x))
#घोषणा TXQ_CNT_L			GENMASK(15, 0)
#घोषणा TXQ_CNT_H			GENMASK(31, 16)

#घोषणा MCR_SWPCDBGR			0x0154

काष्ठा mt76s_पूर्णांकr अणु
	u32 isr;
	काष्ठा अणु
		u32 wtqcr[8];
	पूर्ण tx;
	काष्ठा अणु
		u16 num[2];
		u16 len[2][16];
	पूर्ण rx;
	u32 rec_mb[2];
पूर्ण __packed;

#पूर्ण_अगर
