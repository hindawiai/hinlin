<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * rt5670-dsp.h  --  RT5670 ALSA SoC DSP driver
 *
 * Copyright 2014 Realtek Microelectronics
 * Author: Bard Liao <bardliao@realtek.com>
 */

#अगर_अघोषित __RT5670_DSP_H__
#घोषणा __RT5670_DSP_H__

#घोषणा RT5670_DSP_CTRL1		0xe0
#घोषणा RT5670_DSP_CTRL2		0xe1
#घोषणा RT5670_DSP_CTRL3		0xe2
#घोषणा RT5670_DSP_CTRL4		0xe3
#घोषणा RT5670_DSP_CTRL5		0xe4

/* DSP Control 1 (0xe0) */
#घोषणा RT5670_DSP_CMD_MASK		(0xff << 8)
#घोषणा RT5670_DSP_CMD_PE		(0x0d << 8)	/* Patch Entry */
#घोषणा RT5670_DSP_CMD_MW		(0x3b << 8)	/* Memory Write */
#घोषणा RT5670_DSP_CMD_MR		(0x37 << 8)	/* Memory Read */
#घोषणा RT5670_DSP_CMD_RR		(0x60 << 8)	/* Register Read */
#घोषणा RT5670_DSP_CMD_RW		(0x68 << 8)	/* Register Write */
#घोषणा RT5670_DSP_REG_DATHI		(0x26 << 8)	/* High Data Addr */
#घोषणा RT5670_DSP_REG_DATLO		(0x25 << 8)	/* Low Data Addr */
#घोषणा RT5670_DSP_CLK_MASK		(0x3 << 6)
#घोषणा RT5670_DSP_CLK_SFT		6
#घोषणा RT5670_DSP_CLK_768K		(0x0 << 6)
#घोषणा RT5670_DSP_CLK_384K		(0x1 << 6)
#घोषणा RT5670_DSP_CLK_192K		(0x2 << 6)
#घोषणा RT5670_DSP_CLK_96K		(0x3 << 6)
#घोषणा RT5670_DSP_BUSY_MASK		(0x1 << 5)
#घोषणा RT5670_DSP_RW_MASK		(0x1 << 4)
#घोषणा RT5670_DSP_DL_MASK		(0x3 << 2)
#घोषणा RT5670_DSP_DL_0			(0x0 << 2)
#घोषणा RT5670_DSP_DL_1			(0x1 << 2)
#घोषणा RT5670_DSP_DL_2			(0x2 << 2)
#घोषणा RT5670_DSP_DL_3			(0x3 << 2)
#घोषणा RT5670_DSP_I2C_AL_16		(0x1 << 1)
#घोषणा RT5670_DSP_CMD_EN		(0x1)

काष्ठा rt5670_dsp_param अणु
	u16 cmd_fmt;
	u16 addr;
	u16 data;
	u8 cmd;
पूर्ण;

#पूर्ण_अगर /* __RT5670_DSP_H__ */

