<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2016 Linaro Ltd.
 * Copyright 2016 ZTE Corporation.
 */

#अगर_अघोषित __ZX_HDMI_REGS_H__
#घोषणा __ZX_HDMI_REGS_H__

#घोषणा FUNC_SEL			0x000b
#घोषणा FUNC_HDMI_EN			BIT(0)
#घोषणा CLKPWD				0x000d
#घोषणा CLKPWD_PDIDCK			BIT(2)
#घोषणा P2T_CTRL			0x0066
#घोषणा P2T_DC_PKT_EN			BIT(7)
#घोषणा L1_INTR_STAT			0x007e
#घोषणा L1_INTR_STAT_INTR1		BIT(0)
#घोषणा INTR1_STAT			0x008f
#घोषणा INTR1_MASK			0x0095
#घोषणा INTR1_MONITOR_DETECT		(BIT(5) | BIT(6))
#घोषणा ZX_DDC_ADDR			0x00ed
#घोषणा ZX_DDC_SEGM			0x00ee
#घोषणा ZX_DDC_OFFSET			0x00ef
#घोषणा ZX_DDC_DIN_CNT1			0x00f0
#घोषणा ZX_DDC_DIN_CNT2			0x00f1
#घोषणा ZX_DDC_CMD			0x00f3
#घोषणा DDC_CMD_MASK			0xf
#घोषणा DDC_CMD_CLEAR_FIFO		0x9
#घोषणा DDC_CMD_SEQUENTIAL_READ		0x2
#घोषणा ZX_DDC_DATA			0x00f4
#घोषणा ZX_DDC_DOUT_CNT			0x00f5
#घोषणा DDC_DOUT_CNT_MASK		0x1f
#घोषणा TEST_TXCTRL			0x00f7
#घोषणा TEST_TXCTRL_HDMI_MODE		BIT(1)
#घोषणा HDMICTL4			0x0235
#घोषणा TPI_HPD_RSEN			0x063b
#घोषणा TPI_HPD_CONNECTION		(BIT(1) | BIT(2))
#घोषणा TPI_INFO_FSEL			0x06bf
#घोषणा FSEL_AVI			0
#घोषणा FSEL_GBD			1
#घोषणा FSEL_AUDIO			2
#घोषणा FSEL_SPD			3
#घोषणा FSEL_MPEG			4
#घोषणा FSEL_VSIF			5
#घोषणा TPI_INFO_B0			0x06c0
#घोषणा TPI_INFO_EN			0x06df
#घोषणा TPI_INFO_TRANS_EN		BIT(7)
#घोषणा TPI_INFO_TRANS_RPT		BIT(6)
#घोषणा TPI_DDC_MASTER_EN		0x06f8
#घोषणा HW_DDC_MASTER			BIT(7)
#घोषणा N_SVAL1				0xa03
#घोषणा N_SVAL2				0xa04
#घोषणा N_SVAL3				0xa05
#घोषणा AUD_EN				0xa13
#घोषणा AUD_IN_EN			BIT(0)
#घोषणा AUD_MODE			0xa14
#घोषणा SPDIF_EN			BIT(1)
#घोषणा TPI_AUD_CONFIG			0xa62
#घोषणा SPDIF_SAMPLE_SIZE_SHIFT		6
#घोषणा SPDIF_SAMPLE_SIZE_MASK		(0x3 << SPDIF_SAMPLE_SIZE_SHIFT)
#घोषणा SPDIF_SAMPLE_SIZE_16BIT		(0x1 << SPDIF_SAMPLE_SIZE_SHIFT)
#घोषणा SPDIF_SAMPLE_SIZE_20BIT		(0x2 << SPDIF_SAMPLE_SIZE_SHIFT)
#घोषणा SPDIF_SAMPLE_SIZE_24BIT		(0x3 << SPDIF_SAMPLE_SIZE_SHIFT)
#घोषणा TPI_AUD_MUTE			BIT(4)

#पूर्ण_अगर /* __ZX_HDMI_REGS_H__ */
