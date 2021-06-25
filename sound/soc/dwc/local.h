<शैली गुरु>
/*
 * Copyright (ST) 2012 Rajeev Kumar (rajeevkumar.linux@gmail.com)
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#अगर_अघोषित __DESIGNWARE_LOCAL_H
#घोषणा __DESIGNWARE_LOCAL_H

#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/types.h>
#समावेश <sound/dmaengine_pcm.h>
#समावेश <sound/pcm.h>
#समावेश <sound/designware_i2s.h>

/* common रेजिस्टर क्रम all channel */
#घोषणा IER		0x000
#घोषणा IRER		0x004
#घोषणा ITER		0x008
#घोषणा CER		0x00C
#घोषणा CCR		0x010
#घोषणा RXFFR		0x014
#घोषणा TXFFR		0x018

/* Interrupt status रेजिस्टर fields */
#घोषणा ISR_TXFO	BIT(5)
#घोषणा ISR_TXFE	BIT(4)
#घोषणा ISR_RXFO	BIT(1)
#घोषणा ISR_RXDA	BIT(0)

/* I2STxRxRegisters क्रम all channels */
#घोषणा LRBR_LTHR(x)	(0x40 * x + 0x020)
#घोषणा RRBR_RTHR(x)	(0x40 * x + 0x024)
#घोषणा RER(x)		(0x40 * x + 0x028)
#घोषणा TER(x)		(0x40 * x + 0x02C)
#घोषणा RCR(x)		(0x40 * x + 0x030)
#घोषणा TCR(x)		(0x40 * x + 0x034)
#घोषणा ISR(x)		(0x40 * x + 0x038)
#घोषणा IMR(x)		(0x40 * x + 0x03C)
#घोषणा ROR(x)		(0x40 * x + 0x040)
#घोषणा TOR(x)		(0x40 * x + 0x044)
#घोषणा RFCR(x)		(0x40 * x + 0x048)
#घोषणा TFCR(x)		(0x40 * x + 0x04C)
#घोषणा RFF(x)		(0x40 * x + 0x050)
#घोषणा TFF(x)		(0x40 * x + 0x054)

/* I2SCOMPRegisters */
#घोषणा I2S_COMP_PARAM_2	0x01F0
#घोषणा I2S_COMP_PARAM_1	0x01F4
#घोषणा I2S_COMP_VERSION	0x01F8
#घोषणा I2S_COMP_TYPE		0x01FC

/*
 * Component parameter रेजिस्टर fields - define the I2S block's
 * configuration.
 */
#घोषणा	COMP1_TX_WORDSIZE_3(r)	(((r) & GENMASK(27, 25)) >> 25)
#घोषणा	COMP1_TX_WORDSIZE_2(r)	(((r) & GENMASK(24, 22)) >> 22)
#घोषणा	COMP1_TX_WORDSIZE_1(r)	(((r) & GENMASK(21, 19)) >> 19)
#घोषणा	COMP1_TX_WORDSIZE_0(r)	(((r) & GENMASK(18, 16)) >> 16)
#घोषणा	COMP1_TX_CHANNELS(r)	(((r) & GENMASK(10, 9)) >> 9)
#घोषणा	COMP1_RX_CHANNELS(r)	(((r) & GENMASK(8, 7)) >> 7)
#घोषणा	COMP1_RX_ENABLED(r)	(((r) & BIT(6)) >> 6)
#घोषणा	COMP1_TX_ENABLED(r)	(((r) & BIT(5)) >> 5)
#घोषणा	COMP1_MODE_EN(r)	(((r) & BIT(4)) >> 4)
#घोषणा	COMP1_FIFO_DEPTH_GLOBAL(r)	(((r) & GENMASK(3, 2)) >> 2)
#घोषणा	COMP1_APB_DATA_WIDTH(r)	(((r) & GENMASK(1, 0)) >> 0)

#घोषणा	COMP2_RX_WORDSIZE_3(r)	(((r) & GENMASK(12, 10)) >> 10)
#घोषणा	COMP2_RX_WORDSIZE_2(r)	(((r) & GENMASK(9, 7)) >> 7)
#घोषणा	COMP2_RX_WORDSIZE_1(r)	(((r) & GENMASK(5, 3)) >> 3)
#घोषणा	COMP2_RX_WORDSIZE_0(r)	(((r) & GENMASK(2, 0)) >> 0)

/* Number of entries in WORDSIZE and DATA_WIDTH parameter रेजिस्टरs */
#घोषणा	COMP_MAX_WORDSIZE	(1 << 3)
#घोषणा	COMP_MAX_DATA_WIDTH	(1 << 2)

#घोषणा MAX_CHANNEL_NUM		8
#घोषणा MIN_CHANNEL_NUM		2

जोड़ dw_i2s_snd_dma_data अणु
	काष्ठा i2s_dma_data pd;
	काष्ठा snd_dmaengine_dai_dma_data dt;
पूर्ण;

काष्ठा dw_i2s_dev अणु
	व्योम __iomem *i2s_base;
	काष्ठा clk *clk;
	पूर्णांक active;
	अचिन्हित पूर्णांक capability;
	अचिन्हित पूर्णांक quirks;
	अचिन्हित पूर्णांक i2s_reg_comp1;
	अचिन्हित पूर्णांक i2s_reg_comp2;
	काष्ठा device *dev;
	u32 ccr;
	u32 xfer_resolution;
	u32 fअगरo_th;

	/* data related to DMA transfers b/w i2s and DMAC */
	जोड़ dw_i2s_snd_dma_data play_dma_data;
	जोड़ dw_i2s_snd_dma_data capture_dma_data;
	काष्ठा i2s_clk_config_data config;
	पूर्णांक (*i2s_clk_cfg)(काष्ठा i2s_clk_config_data *config);

	/* data related to PIO transfers */
	bool use_pio;
	काष्ठा snd_pcm_substream __rcu *tx_substream;
	काष्ठा snd_pcm_substream __rcu *rx_substream;
	अचिन्हित पूर्णांक (*tx_fn)(काष्ठा dw_i2s_dev *dev,
			काष्ठा snd_pcm_runसमय *runसमय, अचिन्हित पूर्णांक tx_ptr,
			bool *period_elapsed);
	अचिन्हित पूर्णांक (*rx_fn)(काष्ठा dw_i2s_dev *dev,
			काष्ठा snd_pcm_runसमय *runसमय, अचिन्हित पूर्णांक rx_ptr,
			bool *period_elapsed);
	अचिन्हित पूर्णांक tx_ptr;
	अचिन्हित पूर्णांक rx_ptr;
पूर्ण;

#अगर IS_ENABLED(CONFIG_SND_DESIGNWARE_PCM)
व्योम dw_pcm_push_tx(काष्ठा dw_i2s_dev *dev);
व्योम dw_pcm_pop_rx(काष्ठा dw_i2s_dev *dev);
पूर्णांक dw_pcm_रेजिस्टर(काष्ठा platक्रमm_device *pdev);
#अन्यथा
अटल अंतरभूत व्योम dw_pcm_push_tx(काष्ठा dw_i2s_dev *dev) अणु पूर्ण
अटल अंतरभूत व्योम dw_pcm_pop_rx(काष्ठा dw_i2s_dev *dev) अणु पूर्ण
अटल अंतरभूत पूर्णांक dw_pcm_रेजिस्टर(काष्ठा platक्रमm_device *pdev)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
