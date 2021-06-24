<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright 2019 NXP
 *
 */

#अगर_अघोषित _FSL_ASRC_COMMON_H
#घोषणा _FSL_ASRC_COMMON_H

/* directions */
#घोषणा IN	0
#घोषणा OUT	1

क्रमागत asrc_pair_index अणु
	ASRC_INVALID_PAIR = -1,
	ASRC_PAIR_A = 0,
	ASRC_PAIR_B = 1,
	ASRC_PAIR_C = 2,
	ASRC_PAIR_D = 3,
पूर्ण;

#घोषणा PAIR_CTX_NUM  0x4

/**
 * fsl_asrc_pair: ASRC Pair common data
 *
 * @asrc: poपूर्णांकer to its parent module
 * @error: error record
 * @index: pair index (ASRC_PAIR_A, ASRC_PAIR_B, ASRC_PAIR_C)
 * @channels: occupied channel number
 * @desc: input and output dma descriptors
 * @dma_chan: inputer and output DMA channels
 * @dma_data: निजी dma data
 * @pos: hardware poपूर्णांकer position
 * @req_dma_chan: flag to release dev_to_dev chan
 * @निजी: pair निजी area
 */
काष्ठा fsl_asrc_pair अणु
	काष्ठा fsl_asrc *asrc;
	अचिन्हित पूर्णांक error;

	क्रमागत asrc_pair_index index;
	अचिन्हित पूर्णांक channels;

	काष्ठा dma_async_tx_descriptor *desc[2];
	काष्ठा dma_chan *dma_chan[2];
	काष्ठा imx_dma_data dma_data;
	अचिन्हित पूर्णांक pos;
	bool req_dma_chan;

	व्योम *निजी;
पूर्ण;

/**
 * fsl_asrc: ASRC common data
 *
 * @dma_params_rx: DMA parameters क्रम receive channel
 * @dma_params_tx: DMA parameters क्रम transmit channel
 * @pdev: platक्रमm device poपूर्णांकer
 * @regmap: regmap handler
 * @paddr: physical address to the base address of रेजिस्टरs
 * @mem_clk: घड़ी source to access रेजिस्टर
 * @ipg_clk: घड़ी source to drive peripheral
 * @spba_clk: SPBA घड़ी (optional, depending on SoC design)
 * @lock: spin lock क्रम resource protection
 * @pair: pair poपूर्णांकers
 * @channel_avail: non-occupied channel numbers
 * @asrc_rate: शेष sample rate क्रम ASoC Back-Ends
 * @asrc_क्रमmat: शेष sample क्रमmat क्रम ASoC Back-Ends
 * @use_edma: edma is used
 * @get_dma_channel: function poपूर्णांकer
 * @request_pair: function poपूर्णांकer
 * @release_pair: function poपूर्णांकer
 * @get_fअगरo_addr: function poपूर्णांकer
 * @pair_priv_size: size of pair निजी काष्ठा.
 * @निजी: निजी data काष्ठाure
 */
काष्ठा fsl_asrc अणु
	काष्ठा snd_dmaengine_dai_dma_data dma_params_rx;
	काष्ठा snd_dmaengine_dai_dma_data dma_params_tx;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा regmap *regmap;
	अचिन्हित दीर्घ paddr;
	काष्ठा clk *mem_clk;
	काष्ठा clk *ipg_clk;
	काष्ठा clk *spba_clk;
	spinlock_t lock;      /* spin lock क्रम resource protection */

	काष्ठा fsl_asrc_pair *pair[PAIR_CTX_NUM];
	अचिन्हित पूर्णांक channel_avail;

	पूर्णांक asrc_rate;
	snd_pcm_क्रमmat_t asrc_क्रमmat;
	bool use_edma;

	काष्ठा dma_chan *(*get_dma_channel)(काष्ठा fsl_asrc_pair *pair, bool dir);
	पूर्णांक (*request_pair)(पूर्णांक channels, काष्ठा fsl_asrc_pair *pair);
	व्योम (*release_pair)(काष्ठा fsl_asrc_pair *pair);
	पूर्णांक (*get_fअगरo_addr)(u8 dir, क्रमागत asrc_pair_index index);
	माप_प्रकार pair_priv_size;

	व्योम *निजी;
पूर्ण;

#घोषणा DRV_NAME "fsl-asrc-dai"
बाह्य काष्ठा snd_soc_component_driver fsl_asrc_component;

#पूर्ण_अगर /* _FSL_ASRC_COMMON_H */
