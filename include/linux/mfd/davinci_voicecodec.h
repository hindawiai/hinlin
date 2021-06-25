<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * DaVinci Voice Codec Core Interface क्रम TI platक्रमms
 *
 * Copyright (C) 2010 Texas Instruments, Inc
 *
 * Author: Miguel Aguilar <miguel.aguilar@ridgerun.com>
 */

#अगर_अघोषित __LINUX_MFD_DAVINCI_VOICECODEC_H_
#घोषणा __LINUX_MFD_DAVINCI_VOICECODEC_H_

#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/platक्रमm_data/edma.h>

काष्ठा regmap;

/*
 * Register values.
 */
#घोषणा DAVINCI_VC_PID			0x00
#घोषणा DAVINCI_VC_CTRL			0x04
#घोषणा DAVINCI_VC_INTEN		0x08
#घोषणा DAVINCI_VC_INTSTATUS		0x0c
#घोषणा DAVINCI_VC_INTCLR		0x10
#घोषणा DAVINCI_VC_EMUL_CTRL		0x14
#घोषणा DAVINCI_VC_RFIFO		0x20
#घोषणा DAVINCI_VC_WFIFO		0x24
#घोषणा DAVINCI_VC_FIFOSTAT		0x28
#घोषणा DAVINCI_VC_TST_CTRL		0x2C
#घोषणा DAVINCI_VC_REG05		0x94
#घोषणा DAVINCI_VC_REG09		0xA4
#घोषणा DAVINCI_VC_REG12		0xB0

/* DAVINCI_VC_CTRL bit fields */
#घोषणा DAVINCI_VC_CTRL_MASK		0x5500
#घोषणा DAVINCI_VC_CTRL_RSTADC		BIT(0)
#घोषणा DAVINCI_VC_CTRL_RSTDAC		BIT(1)
#घोषणा DAVINCI_VC_CTRL_RD_BITS_8	BIT(4)
#घोषणा DAVINCI_VC_CTRL_RD_UNSIGNED	BIT(5)
#घोषणा DAVINCI_VC_CTRL_WD_BITS_8	BIT(6)
#घोषणा DAVINCI_VC_CTRL_WD_UNSIGNED	BIT(7)
#घोषणा DAVINCI_VC_CTRL_RFIFOEN		BIT(8)
#घोषणा DAVINCI_VC_CTRL_RFIFOCL		BIT(9)
#घोषणा DAVINCI_VC_CTRL_RFIFOMD_WORD_1	BIT(10)
#घोषणा DAVINCI_VC_CTRL_WFIFOEN		BIT(12)
#घोषणा DAVINCI_VC_CTRL_WFIFOCL		BIT(13)
#घोषणा DAVINCI_VC_CTRL_WFIFOMD_WORD_1	BIT(14)

/* DAVINCI_VC_INT bit fields */
#घोषणा DAVINCI_VC_INT_MASK		0x3F
#घोषणा DAVINCI_VC_INT_RDRDY_MASK	BIT(0)
#घोषणा DAVINCI_VC_INT_RERROVF_MASK	BIT(1)
#घोषणा DAVINCI_VC_INT_RERRUDR_MASK	BIT(2)
#घोषणा DAVINCI_VC_INT_WDREQ_MASK	BIT(3)
#घोषणा DAVINCI_VC_INT_WERROVF_MASKBIT	BIT(4)
#घोषणा DAVINCI_VC_INT_WERRUDR_MASK	BIT(5)

/* DAVINCI_VC_REG05 bit fields */
#घोषणा DAVINCI_VC_REG05_PGA_GAIN	0x07

/* DAVINCI_VC_REG09 bit fields */
#घोषणा DAVINCI_VC_REG09_MUTE		0x40
#घोषणा DAVINCI_VC_REG09_DIG_ATTEN	0x3F

/* DAVINCI_VC_REG12 bit fields */
#घोषणा DAVINCI_VC_REG12_POWER_ALL_ON	0xFD
#घोषणा DAVINCI_VC_REG12_POWER_ALL_OFF	0x00

#घोषणा DAVINCI_VC_CELLS		2

क्रमागत davinci_vc_cells अणु
	DAVINCI_VC_VCIF_CELL,
	DAVINCI_VC_CQ93VC_CELL,
पूर्ण;

काष्ठा davinci_vcअगर अणु
	काष्ठा platक्रमm_device	*pdev;
	u32 dma_tx_channel;
	u32 dma_rx_channel;
	dma_addr_t dma_tx_addr;
	dma_addr_t dma_rx_addr;
पूर्ण;

काष्ठा davinci_vc अणु
	/* Device data */
	काष्ठा device *dev;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा clk *clk;

	/* Memory resources */
	व्योम __iomem *base;
	काष्ठा regmap *regmap;

	/* MFD cells */
	काष्ठा mfd_cell cells[DAVINCI_VC_CELLS];

	/* Client devices */
	काष्ठा davinci_vcअगर davinci_vcअगर;
पूर्ण;

#पूर्ण_अगर
