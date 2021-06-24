<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2011 Freescale Semiconductor, Inc. All Rights Reserved.
 */


#अगर_अघोषित _MXS_SAIF_H
#घोषणा _MXS_SAIF_H

#घोषणा SAIF_CTRL	0x0
#घोषणा SAIF_STAT	0x10
#घोषणा SAIF_DATA	0x20
#घोषणा SAIF_VERSION	0X30

/* SAIF_CTRL */
#घोषणा BM_SAIF_CTRL_SFTRST		0x80000000
#घोषणा BM_SAIF_CTRL_CLKGATE		0x40000000
#घोषणा BP_SAIF_CTRL_BITCLK_MULT_RATE	27
#घोषणा BM_SAIF_CTRL_BITCLK_MULT_RATE	0x38000000
#घोषणा BF_SAIF_CTRL_BITCLK_MULT_RATE(v) \
		(((v) << 27) & BM_SAIF_CTRL_BITCLK_MULT_RATE)
#घोषणा BM_SAIF_CTRL_BITCLK_BASE_RATE	0x04000000
#घोषणा BM_SAIF_CTRL_FIFO_ERROR_IRQ_EN	0x02000000
#घोषणा BM_SAIF_CTRL_FIFO_SERVICE_IRQ_EN	0x01000000
#घोषणा BP_SAIF_CTRL_RSRVD2		21
#घोषणा BM_SAIF_CTRL_RSRVD2		0x00E00000

#घोषणा BP_SAIF_CTRL_DMAWAIT_COUNT	16
#घोषणा BM_SAIF_CTRL_DMAWAIT_COUNT	0x001F0000
#घोषणा BF_SAIF_CTRL_DMAWAIT_COUNT(v) \
		(((v) << 16) & BM_SAIF_CTRL_DMAWAIT_COUNT)
#घोषणा BP_SAIF_CTRL_CHANNEL_NUM_SELECT 14
#घोषणा BM_SAIF_CTRL_CHANNEL_NUM_SELECT 0x0000C000
#घोषणा BF_SAIF_CTRL_CHANNEL_NUM_SELECT(v) \
		(((v) << 14) & BM_SAIF_CTRL_CHANNEL_NUM_SELECT)
#घोषणा BM_SAIF_CTRL_LRCLK_PULSE	0x00002000
#घोषणा BM_SAIF_CTRL_BIT_ORDER		0x00001000
#घोषणा BM_SAIF_CTRL_DELAY		0x00000800
#घोषणा BM_SAIF_CTRL_JUSTIFY		0x00000400
#घोषणा BM_SAIF_CTRL_LRCLK_POLARITY	0x00000200
#घोषणा BM_SAIF_CTRL_BITCLK_EDGE	0x00000100
#घोषणा BP_SAIF_CTRL_WORD_LENGTH	4
#घोषणा BM_SAIF_CTRL_WORD_LENGTH	0x000000F0
#घोषणा BF_SAIF_CTRL_WORD_LENGTH(v) \
		(((v) << 4) & BM_SAIF_CTRL_WORD_LENGTH)
#घोषणा BM_SAIF_CTRL_BITCLK_48XFS_ENABLE	0x00000008
#घोषणा BM_SAIF_CTRL_SLAVE_MODE		0x00000004
#घोषणा BM_SAIF_CTRL_READ_MODE		0x00000002
#घोषणा BM_SAIF_CTRL_RUN		0x00000001

/* SAIF_STAT */
#घोषणा BM_SAIF_STAT_PRESENT		0x80000000
#घोषणा BP_SAIF_STAT_RSRVD2		17
#घोषणा BM_SAIF_STAT_RSRVD2		0x7FFE0000
#घोषणा BF_SAIF_STAT_RSRVD2(v) \
		(((v) << 17) & BM_SAIF_STAT_RSRVD2)
#घोषणा BM_SAIF_STAT_DMA_PREQ		0x00010000
#घोषणा BP_SAIF_STAT_RSRVD1		7
#घोषणा BM_SAIF_STAT_RSRVD1		0x0000FF80
#घोषणा BF_SAIF_STAT_RSRVD1(v) \
		(((v) << 7) & BM_SAIF_STAT_RSRVD1)

#घोषणा BM_SAIF_STAT_FIFO_UNDERFLOW_IRQ 0x00000040
#घोषणा BM_SAIF_STAT_FIFO_OVERFLOW_IRQ	0x00000020
#घोषणा BM_SAIF_STAT_FIFO_SERVICE_IRQ	0x00000010
#घोषणा BP_SAIF_STAT_RSRVD0		1
#घोषणा BM_SAIF_STAT_RSRVD0		0x0000000E
#घोषणा BF_SAIF_STAT_RSRVD0(v) \
		(((v) << 1) & BM_SAIF_STAT_RSRVD0)
#घोषणा BM_SAIF_STAT_BUSY		0x00000001

/* SAFI_DATA */
#घोषणा BP_SAIF_DATA_PCM_RIGHT		16
#घोषणा BM_SAIF_DATA_PCM_RIGHT		0xFFFF0000
#घोषणा BF_SAIF_DATA_PCM_RIGHT(v) \
		(((v) << 16) & BM_SAIF_DATA_PCM_RIGHT)
#घोषणा BP_SAIF_DATA_PCM_LEFT		0
#घोषणा BM_SAIF_DATA_PCM_LEFT		0x0000FFFF
#घोषणा BF_SAIF_DATA_PCM_LEFT(v)	\
		(((v) << 0) & BM_SAIF_DATA_PCM_LEFT)

/* SAIF_VERSION */
#घोषणा BP_SAIF_VERSION_MAJOR		24
#घोषणा BM_SAIF_VERSION_MAJOR		0xFF000000
#घोषणा BF_SAIF_VERSION_MAJOR(v) \
		(((v) << 24) & BM_SAIF_VERSION_MAJOR)
#घोषणा BP_SAIF_VERSION_MINOR		16
#घोषणा BM_SAIF_VERSION_MINOR		0x00FF0000
#घोषणा BF_SAIF_VERSION_MINOR(v) \
		(((v) << 16) & BM_SAIF_VERSION_MINOR)
#घोषणा BP_SAIF_VERSION_STEP		0
#घोषणा BM_SAIF_VERSION_STEP		0x0000FFFF
#घोषणा BF_SAIF_VERSION_STEP(v) \
		(((v) << 0) & BM_SAIF_VERSION_STEP)

#घोषणा MXS_SAIF_MCLK		0

#समावेश "mxs-pcm.h"

काष्ठा mxs_saअगर अणु
	काष्ठा device *dev;
	काष्ठा clk *clk;
	अचिन्हित पूर्णांक mclk;
	अचिन्हित पूर्णांक mclk_in_use;
	व्योम __iomem *base;
	अचिन्हित पूर्णांक id;
	अचिन्हित पूर्णांक master_id;
	अचिन्हित पूर्णांक cur_rate;
	अचिन्हित पूर्णांक ongoing;

	u32 fअगरo_underrun;
	u32 fअगरo_overrun;

	क्रमागत अणु
		MXS_SAIF_STATE_STOPPED,
		MXS_SAIF_STATE_RUNNING,
	पूर्ण state;
पूर्ण;

बाह्य पूर्णांक mxs_saअगर_put_mclk(अचिन्हित पूर्णांक saअगर_id);
बाह्य पूर्णांक mxs_saअगर_get_mclk(अचिन्हित पूर्णांक saअगर_id, अचिन्हित पूर्णांक mclk,
					अचिन्हित पूर्णांक rate);
#पूर्ण_अगर
