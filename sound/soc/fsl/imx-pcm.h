<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright 2009 Sascha Hauer <s.hauer@pengutronix.de>
 *
 * This code is based on code copyrighted by Freescale,
 * Liam Girdwood, Javier Martin and probably others.
 */

#अगर_अघोषित _IMX_PCM_H
#घोषणा _IMX_PCM_H

#समावेश <linux/platक्रमm_data/dma-imx.h>

/*
 * Do not change this as the FIQ handler depends on this size
 */
#घोषणा IMX_SSI_DMABUF_SIZE	(64 * 1024)

#घोषणा IMX_DEFAULT_DMABUF_SIZE	(64 * 1024)
#घोषणा IMX_SAI_DMABUF_SIZE	(64 * 1024)
#घोषणा IMX_SPDIF_DMABUF_SIZE	(64 * 1024)
#घोषणा IMX_ESAI_DMABUF_SIZE	(256 * 1024)

अटल अंतरभूत व्योम
imx_pcm_dma_params_init_data(काष्ठा imx_dma_data *dma_data,
	पूर्णांक dma, क्रमागत sdma_peripheral_type peripheral_type)
अणु
	dma_data->dma_request = dma;
	dma_data->priority = DMA_PRIO_HIGH;
	dma_data->peripheral_type = peripheral_type;
पूर्ण

काष्ठा imx_pcm_fiq_params अणु
	पूर्णांक irq;
	व्योम __iomem *base;

	/* Poपूर्णांकer to original ssi driver to setup tx rx sizes */
	काष्ठा snd_dmaengine_dai_dma_data *dma_params_rx;
	काष्ठा snd_dmaengine_dai_dma_data *dma_params_tx;
पूर्ण;

#अगर IS_ENABLED(CONFIG_SND_SOC_IMX_PCM_DMA)
पूर्णांक imx_pcm_dma_init(काष्ठा platक्रमm_device *pdev, माप_प्रकार size);
#अन्यथा
अटल अंतरभूत पूर्णांक imx_pcm_dma_init(काष्ठा platक्रमm_device *pdev, माप_प्रकार size)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_SND_SOC_IMX_PCM_FIQ)
पूर्णांक imx_pcm_fiq_init(काष्ठा platक्रमm_device *pdev,
		काष्ठा imx_pcm_fiq_params *params);
व्योम imx_pcm_fiq_निकास(काष्ठा platक्रमm_device *pdev);
#अन्यथा
अटल अंतरभूत पूर्णांक imx_pcm_fiq_init(काष्ठा platक्रमm_device *pdev,
		काष्ठा imx_pcm_fiq_params *params)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत व्योम imx_pcm_fiq_निकास(काष्ठा platक्रमm_device *pdev)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _IMX_PCM_H */
