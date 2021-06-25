<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2004-2009 Freescale Semiconductor, Inc. All Rights Reserved.
 */

#अगर_अघोषित __ASM_ARCH_MXC_DMA_H__
#घोषणा __ASM_ARCH_MXC_DMA_H__

#समावेश <linux/scatterlist.h>
#समावेश <linux/device.h>
#समावेश <linux/dmaengine.h>

/*
 * This क्रमागतerates peripheral types. Used क्रम SDMA.
 */
क्रमागत sdma_peripheral_type अणु
	IMX_DMATYPE_SSI,	/* MCU करोमुख्य SSI */
	IMX_DMATYPE_SSI_SP,	/* Shared SSI */
	IMX_DMATYPE_MMC,	/* MMC */
	IMX_DMATYPE_SDHC,	/* SDHC */
	IMX_DMATYPE_UART,	/* MCU करोमुख्य UART */
	IMX_DMATYPE_UART_SP,	/* Shared UART */
	IMX_DMATYPE_FIRI,	/* FIRI */
	IMX_DMATYPE_CSPI,	/* MCU करोमुख्य CSPI */
	IMX_DMATYPE_CSPI_SP,	/* Shared CSPI */
	IMX_DMATYPE_SIM,	/* SIM */
	IMX_DMATYPE_ATA,	/* ATA */
	IMX_DMATYPE_CCM,	/* CCM */
	IMX_DMATYPE_EXT,	/* External peripheral */
	IMX_DMATYPE_MSHC,	/* Memory Stick Host Controller */
	IMX_DMATYPE_MSHC_SP,	/* Shared Memory Stick Host Controller */
	IMX_DMATYPE_DSP,	/* DSP */
	IMX_DMATYPE_MEMORY,	/* Memory */
	IMX_DMATYPE_FIFO_MEMORY,/* FIFO type Memory */
	IMX_DMATYPE_SPDIF,	/* SPDIF */
	IMX_DMATYPE_IPU_MEMORY,	/* IPU Memory */
	IMX_DMATYPE_ASRC,	/* ASRC */
	IMX_DMATYPE_ESAI,	/* ESAI */
	IMX_DMATYPE_SSI_DUAL,	/* SSI Dual FIFO */
	IMX_DMATYPE_ASRC_SP,	/* Shared ASRC */
	IMX_DMATYPE_SAI,	/* SAI */
पूर्ण;

क्रमागत imx_dma_prio अणु
	DMA_PRIO_HIGH = 0,
	DMA_PRIO_MEDIUM = 1,
	DMA_PRIO_LOW = 2
पूर्ण;

काष्ठा imx_dma_data अणु
	पूर्णांक dma_request; /* DMA request line */
	पूर्णांक dma_request2; /* secondary DMA request line */
	क्रमागत sdma_peripheral_type peripheral_type;
	पूर्णांक priority;
पूर्ण;

अटल अंतरभूत पूर्णांक imx_dma_is_ipu(काष्ठा dma_chan *chan)
अणु
	वापस !म_भेद(dev_name(chan->device->dev), "ipu-core");
पूर्ण

अटल अंतरभूत पूर्णांक imx_dma_is_general_purpose(काष्ठा dma_chan *chan)
अणु
	वापस !म_भेद(chan->device->dev->driver->name, "imx-sdma") ||
		!म_भेद(chan->device->dev->driver->name, "imx-dma");
पूर्ण

#पूर्ण_अगर
