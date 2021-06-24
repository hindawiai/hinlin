<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright 2020 NXP
 */

#अगर_अघोषित _FSL_AUD2HTX_H
#घोषणा _FSL_AUD2HTX_H

#घोषणा FSL_AUD2HTX_FORMATS (SNDRV_PCM_FMTBIT_S24_LE | \
			     SNDRV_PCM_FMTBIT_S32_LE)

/* AUD2HTX Register Map */
#घोषणा AUD2HTX_CTRL          0x0   /* AUD2HTX Control Register */
#घोषणा AUD2HTX_CTRL_EXT      0x4   /* AUD2HTX Control Extended Register */
#घोषणा AUD2HTX_WR            0x8   /* AUD2HTX Write Register */
#घोषणा AUD2HTX_STATUS        0xC   /* AUD2HTX Status Register */
#घोषणा AUD2HTX_IRQ_NOMASK    0x10  /* AUD2HTX Nonmasked Interrupt Flags Register */
#घोषणा AUD2HTX_IRQ_MASKED    0x14  /* AUD2HTX Masked Interrupt Flags Register */
#घोषणा AUD2HTX_IRQ_MASK      0x18  /* AUD2HTX IRQ Masks Register */

/* AUD2HTX Control Register */
#घोषणा AUD2HTX_CTRL_EN          BIT(0)

/* AUD2HTX Control Extended Register */
#घोषणा AUD2HTX_CTRE_DE          BIT(0)
#घोषणा AUD2HTX_CTRE_DT_SHIFT    0x1
#घोषणा AUD2HTX_CTRE_DT_WIDTH    0x2
#घोषणा AUD2HTX_CTRE_DT_MASK     ((BIT(AUD2HTX_CTRE_DT_WIDTH) - 1) \
				 << AUD2HTX_CTRE_DT_SHIFT)
#घोषणा AUD2HTX_CTRE_WL_SHIFT    16
#घोषणा AUD2HTX_CTRE_WL_WIDTH    5
#घोषणा AUD2HTX_CTRE_WL_MASK     ((BIT(AUD2HTX_CTRE_WL_WIDTH) - 1) \
				 << AUD2HTX_CTRE_WL_SHIFT)
#घोषणा AUD2HTX_CTRE_WH_SHIFT    24
#घोषणा AUD2HTX_CTRE_WH_WIDTH    5
#घोषणा AUD2HTX_CTRE_WH_MASK     ((BIT(AUD2HTX_CTRE_WH_WIDTH) - 1) \
				 << AUD2HTX_CTRE_WH_SHIFT)

/* AUD2HTX IRQ Masks Register */
#घोषणा AUD2HTX_WM_HIGH_IRQ_MASK BIT(2)
#घोषणा AUD2HTX_WM_LOW_IRQ_MASK  BIT(1)
#घोषणा AUD2HTX_OVF_MASK         BIT(0)

#घोषणा AUD2HTX_FIFO_DEPTH       0x20
#घोषणा AUD2HTX_WTMK_LOW         0x10
#घोषणा AUD2HTX_WTMK_HIGH        0x10
#घोषणा AUD2HTX_MAXBURST         0x10

/**
 * fsl_aud2htx: AUD2HTX निजी data
 *
 * @pdev: platक्रमm device poपूर्णांकer
 * @regmap: regmap handler
 * @bus_clk: घड़ी source to access रेजिस्टर
 * @dma_params_rx: DMA parameters क्रम receive channel
 * @dma_params_tx: DMA parameters क्रम transmit channel
 */
काष्ठा fsl_aud2htx अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा regmap *regmap;
	काष्ठा clk *bus_clk;

	काष्ठा snd_dmaengine_dai_dma_data dma_params_rx;
	काष्ठा snd_dmaengine_dai_dma_data dma_params_tx;
पूर्ण;

#पूर्ण_अगर /* _FSL_AUD2HTX_H */
