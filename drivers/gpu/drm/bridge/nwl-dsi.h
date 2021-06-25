<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * NWL MIPI DSI host driver
 *
 * Copyright (C) 2017 NXP
 * Copyright (C) 2019 Purism SPC
 */
#अगर_अघोषित __NWL_DSI_H__
#घोषणा __NWL_DSI_H__

/* DSI HOST रेजिस्टरs */
#घोषणा NWL_DSI_CFG_NUM_LANES			0x0
#घोषणा NWL_DSI_CFG_NONCONTINUOUS_CLK		0x4
#घोषणा NWL_DSI_CFG_T_PRE			0x8
#घोषणा NWL_DSI_CFG_T_POST			0xc
#घोषणा NWL_DSI_CFG_TX_GAP			0x10
#घोषणा NWL_DSI_CFG_AUTOINSERT_EOTP		0x14
#घोषणा NWL_DSI_CFG_EXTRA_CMDS_AFTER_EOTP	0x18
#घोषणा NWL_DSI_CFG_HTX_TO_COUNT		0x1c
#घोषणा NWL_DSI_CFG_LRX_H_TO_COUNT		0x20
#घोषणा NWL_DSI_CFG_BTA_H_TO_COUNT		0x24
#घोषणा NWL_DSI_CFG_TWAKEUP			0x28
#घोषणा NWL_DSI_CFG_STATUS_OUT			0x2c
#घोषणा NWL_DSI_RX_ERROR_STATUS			0x30

/* DSI DPI रेजिस्टरs */
#घोषणा NWL_DSI_PIXEL_PAYLOAD_SIZE		0x200
#घोषणा NWL_DSI_PIXEL_FIFO_SEND_LEVEL		0x204
#घोषणा NWL_DSI_INTERFACE_COLOR_CODING		0x208
#घोषणा NWL_DSI_PIXEL_FORMAT			0x20c
#घोषणा NWL_DSI_VSYNC_POLARITY			0x210
#घोषणा NWL_DSI_VSYNC_POLARITY_ACTIVE_LOW	0
#घोषणा NWL_DSI_VSYNC_POLARITY_ACTIVE_HIGH	BIT(1)

#घोषणा NWL_DSI_HSYNC_POLARITY			0x214
#घोषणा NWL_DSI_HSYNC_POLARITY_ACTIVE_LOW	0
#घोषणा NWL_DSI_HSYNC_POLARITY_ACTIVE_HIGH	BIT(1)

#घोषणा NWL_DSI_VIDEO_MODE			0x218
#घोषणा NWL_DSI_HFP				0x21c
#घोषणा NWL_DSI_HBP				0x220
#घोषणा NWL_DSI_HSA				0x224
#घोषणा NWL_DSI_ENABLE_MULT_PKTS		0x228
#घोषणा NWL_DSI_VBP				0x22c
#घोषणा NWL_DSI_VFP				0x230
#घोषणा NWL_DSI_BLLP_MODE			0x234
#घोषणा NWL_DSI_USE_शून्य_PKT_BLLP		0x238
#घोषणा NWL_DSI_VACTIVE				0x23c
#घोषणा NWL_DSI_VC				0x240

/* DSI APB PKT control */
#घोषणा NWL_DSI_TX_PAYLOAD			0x280
#घोषणा NWL_DSI_PKT_CONTROL			0x284
#घोषणा NWL_DSI_SEND_PACKET			0x288
#घोषणा NWL_DSI_PKT_STATUS			0x28c
#घोषणा NWL_DSI_PKT_FIFO_WR_LEVEL		0x290
#घोषणा NWL_DSI_PKT_FIFO_RD_LEVEL		0x294
#घोषणा NWL_DSI_RX_PAYLOAD			0x298
#घोषणा NWL_DSI_RX_PKT_HEADER			0x29c

/* DSI IRQ handling */
#घोषणा NWL_DSI_IRQ_STATUS			0x2a0
#घोषणा NWL_DSI_SM_NOT_IDLE			BIT(0)
#घोषणा NWL_DSI_TX_PKT_DONE			BIT(1)
#घोषणा NWL_DSI_DPHY_सूचीECTION			BIT(2)
#घोषणा NWL_DSI_TX_FIFO_OVFLW			BIT(3)
#घोषणा NWL_DSI_TX_FIFO_UDFLW			BIT(4)
#घोषणा NWL_DSI_RX_FIFO_OVFLW			BIT(5)
#घोषणा NWL_DSI_RX_FIFO_UDFLW			BIT(6)
#घोषणा NWL_DSI_RX_PKT_HDR_RCVD			BIT(7)
#घोषणा NWL_DSI_RX_PKT_PAYLOAD_DATA_RCVD	BIT(8)
#घोषणा NWL_DSI_BTA_TIMEOUT			BIT(29)
#घोषणा NWL_DSI_LP_RX_TIMEOUT			BIT(30)
#घोषणा NWL_DSI_HS_TX_TIMEOUT			BIT(31)

#घोषणा NWL_DSI_IRQ_STATUS2			0x2a4
#घोषणा NWL_DSI_SINGLE_BIT_ECC_ERR		BIT(0)
#घोषणा NWL_DSI_MULTI_BIT_ECC_ERR		BIT(1)
#घोषणा NWL_DSI_CRC_ERR				BIT(2)

#घोषणा NWL_DSI_IRQ_MASK			0x2a8
#घोषणा NWL_DSI_SM_NOT_IDLE_MASK		BIT(0)
#घोषणा NWL_DSI_TX_PKT_DONE_MASK		BIT(1)
#घोषणा NWL_DSI_DPHY_सूचीECTION_MASK		BIT(2)
#घोषणा NWL_DSI_TX_FIFO_OVFLW_MASK		BIT(3)
#घोषणा NWL_DSI_TX_FIFO_UDFLW_MASK		BIT(4)
#घोषणा NWL_DSI_RX_FIFO_OVFLW_MASK		BIT(5)
#घोषणा NWL_DSI_RX_FIFO_UDFLW_MASK		BIT(6)
#घोषणा NWL_DSI_RX_PKT_HDR_RCVD_MASK		BIT(7)
#घोषणा NWL_DSI_RX_PKT_PAYLOAD_DATA_RCVD_MASK	BIT(8)
#घोषणा NWL_DSI_BTA_TIMEOUT_MASK		BIT(29)
#घोषणा NWL_DSI_LP_RX_TIMEOUT_MASK		BIT(30)
#घोषणा NWL_DSI_HS_TX_TIMEOUT_MASK		BIT(31)

#घोषणा NWL_DSI_IRQ_MASK2			0x2ac
#घोषणा NWL_DSI_SINGLE_BIT_ECC_ERR_MASK		BIT(0)
#घोषणा NWL_DSI_MULTI_BIT_ECC_ERR_MASK		BIT(1)
#घोषणा NWL_DSI_CRC_ERR_MASK			BIT(2)

/*
 * PKT_CONTROL क्रमmat:
 * [15: 0] - word count
 * [17:16] - भव channel
 * [23:18] - data type
 * [24]	   - LP or HS select (0 - LP, 1 - HS)
 * [25]	   - perक्रमm BTA after packet is sent
 * [26]	   - perक्रमm BTA only, no packet tx
 */
#घोषणा NWL_DSI_WC(x)		FIELD_PREP(GENMASK(15, 0), (x))
#घोषणा NWL_DSI_TX_VC(x)	FIELD_PREP(GENMASK(17, 16), (x))
#घोषणा NWL_DSI_TX_DT(x)	FIELD_PREP(GENMASK(23, 18), (x))
#घोषणा NWL_DSI_HS_SEL(x)	FIELD_PREP(GENMASK(24, 24), (x))
#घोषणा NWL_DSI_BTA_TX(x)	FIELD_PREP(GENMASK(25, 25), (x))
#घोषणा NWL_DSI_BTA_NO_TX(x)	FIELD_PREP(GENMASK(26, 26), (x))

/*
 * RX_PKT_HEADER क्रमmat:
 * [15: 0] - word count
 * [21:16] - data type
 * [23:22] - भव channel
 */
#घोषणा NWL_DSI_RX_DT(x)	FIELD_GET(GENMASK(21, 16), (x))
#घोषणा NWL_DSI_RX_VC(x)	FIELD_GET(GENMASK(23, 22), (x))

/* DSI Video mode */
#घोषणा NWL_DSI_VM_BURST_MODE_WITH_SYNC_PULSES		0
#घोषणा NWL_DSI_VM_NON_BURST_MODE_WITH_SYNC_EVENTS	BIT(0)
#घोषणा NWL_DSI_VM_BURST_MODE				BIT(1)

/* * DPI color coding */
#घोषणा NWL_DSI_DPI_16_BIT_565_PACKED	0
#घोषणा NWL_DSI_DPI_16_BIT_565_ALIGNED	1
#घोषणा NWL_DSI_DPI_16_BIT_565_SHIFTED	2
#घोषणा NWL_DSI_DPI_18_BIT_PACKED	3
#घोषणा NWL_DSI_DPI_18_BIT_ALIGNED	4
#घोषणा NWL_DSI_DPI_24_BIT		5

/* * DPI Pixel क्रमmat */
#घोषणा NWL_DSI_PIXEL_FORMAT_16  0
#घोषणा NWL_DSI_PIXEL_FORMAT_18  BIT(0)
#घोषणा NWL_DSI_PIXEL_FORMAT_18L BIT(1)
#घोषणा NWL_DSI_PIXEL_FORMAT_24  (BIT(0) | BIT(1))

#पूर्ण_अगर /* __NWL_DSI_H__ */
