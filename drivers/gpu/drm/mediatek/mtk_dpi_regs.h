<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2014 MediaTek Inc.
 * Author: Jie Qiu <jie.qiu@mediatek.com>
 */
#अगर_अघोषित __MTK_DPI_REGS_H
#घोषणा __MTK_DPI_REGS_H

#घोषणा DPI_EN			0x00
#घोषणा EN				BIT(0)

#घोषणा DPI_RET			0x04
#घोषणा RST				BIT(0)

#घोषणा DPI_INTEN		0x08
#घोषणा INT_VSYNC_EN			BIT(0)
#घोषणा INT_VDE_EN			BIT(1)
#घोषणा INT_UNDERFLOW_EN		BIT(2)

#घोषणा DPI_INTSTA		0x0C
#घोषणा INT_VSYNC_STA			BIT(0)
#घोषणा INT_VDE_STA			BIT(1)
#घोषणा INT_UNDERFLOW_STA		BIT(2)

#घोषणा DPI_CON			0x10
#घोषणा BG_ENABLE			BIT(0)
#घोषणा IN_RB_SWAP			BIT(1)
#घोषणा INTL_EN				BIT(2)
#घोषणा TDFP_EN				BIT(3)
#घोषणा CLPF_EN				BIT(4)
#घोषणा YUV422_EN			BIT(5)
#घोषणा CSC_ENABLE			BIT(6)
#घोषणा R601_SEL			BIT(7)
#घोषणा EMBSYNC_EN			BIT(8)
#घोषणा VS_LODD_EN			BIT(16)
#घोषणा VS_LEVEN_EN			BIT(17)
#घोषणा VS_RODD_EN			BIT(18)
#घोषणा VS_REVEN			BIT(19)
#घोषणा FAKE_DE_LODD			BIT(20)
#घोषणा FAKE_DE_LEVEN			BIT(21)
#घोषणा FAKE_DE_RODD			BIT(22)
#घोषणा FAKE_DE_REVEN			BIT(23)

#घोषणा DPI_OUTPUT_SETTING	0x14
#घोषणा CH_SWAP				0
#घोषणा CH_SWAP_MASK			(0x7 << 0)
#घोषणा SWAP_RGB			0x00
#घोषणा SWAP_GBR			0x01
#घोषणा SWAP_BRG			0x02
#घोषणा SWAP_RBG			0x03
#घोषणा SWAP_GRB			0x04
#घोषणा SWAP_BGR			0x05
#घोषणा BIT_SWAP			BIT(3)
#घोषणा B_MASK				BIT(4)
#घोषणा G_MASK				BIT(5)
#घोषणा R_MASK				BIT(6)
#घोषणा DE_MASK				BIT(8)
#घोषणा HS_MASK				BIT(9)
#घोषणा VS_MASK				BIT(10)
#घोषणा DE_POL				BIT(12)
#घोषणा HSYNC_POL			BIT(13)
#घोषणा VSYNC_POL			BIT(14)
#घोषणा CK_POL				BIT(15)
#घोषणा OEN_OFF				BIT(16)
#घोषणा EDGE_SEL			BIT(17)
#घोषणा OUT_BIT				18
#घोषणा OUT_BIT_MASK			(0x3 << 18)
#घोषणा OUT_BIT_8			0x00
#घोषणा OUT_BIT_10			0x01
#घोषणा OUT_BIT_12			0x02
#घोषणा OUT_BIT_16			0x03
#घोषणा YC_MAP				20
#घोषणा YC_MAP_MASK			(0x7 << 20)
#घोषणा YC_MAP_RGB			0x00
#घोषणा YC_MAP_CYCY			0x04
#घोषणा YC_MAP_YCYC			0x05
#घोषणा YC_MAP_CY			0x06
#घोषणा YC_MAP_YC			0x07

#घोषणा DPI_SIZE		0x18
#घोषणा HSIZE				0
#घोषणा HSIZE_MASK			(0x1FFF << 0)
#घोषणा VSIZE				16
#घोषणा VSIZE_MASK			(0x1FFF << 16)

#घोषणा DPI_DDR_SETTING		0x1C
#घोषणा DDR_EN				BIT(0)
#घोषणा DDDR_SEL			BIT(1)
#घोषणा DDR_4PHASE			BIT(2)
#घोषणा DDR_WIDTH			(0x3 << 4)
#घोषणा DDR_PAD_MODE			(0x1 << 8)

#घोषणा DPI_TGEN_HWIDTH		0x20
#घोषणा HPW				0
#घोषणा HPW_MASK			(0xFFF << 0)

#घोषणा DPI_TGEN_HPORCH		0x24
#घोषणा HBP				0
#घोषणा HBP_MASK			(0xFFF << 0)
#घोषणा HFP				16
#घोषणा HFP_MASK			(0xFFF << 16)

#घोषणा DPI_TGEN_VWIDTH		0x28
#घोषणा DPI_TGEN_VPORCH		0x2C

#घोषणा VSYNC_WIDTH_SHIFT		0
#घोषणा VSYNC_WIDTH_MASK		(0xFFF << 0)
#घोषणा VSYNC_HALF_LINE_SHIFT		16
#घोषणा VSYNC_HALF_LINE_MASK		BIT(16)
#घोषणा VSYNC_BACK_PORCH_SHIFT		0
#घोषणा VSYNC_BACK_PORCH_MASK		(0xFFF << 0)
#घोषणा VSYNC_FRONT_PORCH_SHIFT		16
#घोषणा VSYNC_FRONT_PORCH_MASK		(0xFFF << 16)

#घोषणा DPI_BG_HCNTL		0x30
#घोषणा BG_RIGHT			(0x1FFF << 0)
#घोषणा BG_LEFT				(0x1FFF << 16)

#घोषणा DPI_BG_VCNTL		0x34
#घोषणा BG_BOT				(0x1FFF << 0)
#घोषणा BG_TOP				(0x1FFF << 16)

#घोषणा DPI_BG_COLOR		0x38
#घोषणा BG_B				(0xF << 0)
#घोषणा BG_G				(0xF << 8)
#घोषणा BG_R				(0xF << 16)

#घोषणा DPI_FIFO_CTL		0x3C
#घोषणा FIFO_VALID_SET			(0x1F << 0)
#घोषणा FIFO_RST_SEL			(0x1 << 8)

#घोषणा DPI_STATUS		0x40
#घोषणा VCOUNTER			(0x1FFF << 0)
#घोषणा DPI_BUSY			BIT(16)
#घोषणा OUTEN				BIT(17)
#घोषणा FIELD				BIT(20)
#घोषणा TDLR				BIT(21)

#घोषणा DPI_TMODE		0x44
#घोषणा DPI_OEN_ON			BIT(0)

#घोषणा DPI_CHECKSUM		0x48
#घोषणा DPI_CHECKSUM_MASK		(0xFFFFFF << 0)
#घोषणा DPI_CHECKSUM_READY		BIT(30)
#घोषणा DPI_CHECKSUM_EN			BIT(31)

#घोषणा DPI_DUMMY		0x50
#घोषणा DPI_DUMMY_MASK			(0xFFFFFFFF << 0)

#घोषणा DPI_TGEN_VWIDTH_LEVEN	0x68
#घोषणा DPI_TGEN_VPORCH_LEVEN	0x6C
#घोषणा DPI_TGEN_VWIDTH_RODD	0x70
#घोषणा DPI_TGEN_VPORCH_RODD	0x74
#घोषणा DPI_TGEN_VWIDTH_REVEN	0x78
#घोषणा DPI_TGEN_VPORCH_REVEN	0x7C

#घोषणा DPI_ESAV_VTIMING_LODD	0x80
#घोषणा ESAV_VOFST_LODD			(0xFFF << 0)
#घोषणा ESAV_VWID_LODD			(0xFFF << 16)

#घोषणा DPI_ESAV_VTIMING_LEVEN	0x84
#घोषणा ESAV_VOFST_LEVEN		(0xFFF << 0)
#घोषणा ESAV_VWID_LEVEN			(0xFFF << 16)

#घोषणा DPI_ESAV_VTIMING_RODD	0x88
#घोषणा ESAV_VOFST_RODD			(0xFFF << 0)
#घोषणा ESAV_VWID_RODD			(0xFFF << 16)

#घोषणा DPI_ESAV_VTIMING_REVEN	0x8C
#घोषणा ESAV_VOFST_REVEN		(0xFFF << 0)
#घोषणा ESAV_VWID_REVEN			(0xFFF << 16)

#घोषणा DPI_ESAV_FTIMING	0x90
#घोषणा ESAV_FOFST_ODD			(0xFFF << 0)
#घोषणा ESAV_FOFST_EVEN			(0xFFF << 16)

#घोषणा DPI_CLPF_SETTING	0x94
#घोषणा CLPF_TYPE			(0x3 << 0)
#घोषणा ROUND_EN			BIT(4)

#घोषणा DPI_Y_LIMIT		0x98
#घोषणा Y_LIMINT_BOT			0
#घोषणा Y_LIMINT_BOT_MASK		(0xFFF << 0)
#घोषणा Y_LIMINT_TOP			16
#घोषणा Y_LIMINT_TOP_MASK		(0xFFF << 16)

#घोषणा DPI_C_LIMIT		0x9C
#घोषणा C_LIMIT_BOT			0
#घोषणा C_LIMIT_BOT_MASK		(0xFFF << 0)
#घोषणा C_LIMIT_TOP			16
#घोषणा C_LIMIT_TOP_MASK		(0xFFF << 16)

#घोषणा DPI_YUV422_SETTING	0xA0
#घोषणा UV_SWAP				BIT(0)
#घोषणा CR_DELSEL			BIT(4)
#घोषणा CB_DELSEL			BIT(5)
#घोषणा Y_DELSEL			BIT(6)
#घोषणा DE_DELSEL			BIT(7)

#घोषणा DPI_EMBSYNC_SETTING	0xA4
#घोषणा EMBSYNC_R_CR_EN			BIT(0)
#घोषणा EMPSYNC_G_Y_EN			BIT(1)
#घोषणा EMPSYNC_B_CB_EN			BIT(2)
#घोषणा ESAV_F_INV			BIT(4)
#घोषणा ESAV_V_INV			BIT(5)
#घोषणा ESAV_H_INV			BIT(6)
#घोषणा ESAV_CODE_MAN			BIT(8)
#घोषणा VS_OUT_SEL			(0x7 << 12)

#घोषणा DPI_ESAV_CODE_SET0	0xA8
#घोषणा ESAV_CODE0			(0xFFF << 0)
#घोषणा ESAV_CODE1			(0xFFF << 16)

#घोषणा DPI_ESAV_CODE_SET1	0xAC
#घोषणा ESAV_CODE2			(0xFFF << 0)
#घोषणा ESAV_CODE3_MSB			BIT(16)

#घोषणा EDGE_SEL_EN			BIT(5)
#घोषणा H_FRE_2N			BIT(25)
#पूर्ण_अगर /* __MTK_DPI_REGS_H */
