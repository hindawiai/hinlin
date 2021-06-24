<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  Intel KeemBay Platक्रमm driver
 *
 *  Copyright (C) 2020 Intel Corporation.
 *
 */

#अगर_अघोषित KMB_PLATFORM_H_
#घोषणा KMB_PLATFORM_H_

#समावेश <linux/bits.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/types.h>
#समावेश <sound/dmaengine_pcm.h>

/* Register values with reference to KMB databook v1.1 */
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

/* I2S Tx Rx Registers क्रम all channels */
#घोषणा LRBR_LTHR(x)	(0x40 * (x) + 0x020)
#घोषणा RRBR_RTHR(x)	(0x40 * (x) + 0x024)
#घोषणा RER(x)		(0x40 * (x) + 0x028)
#घोषणा TER(x)		(0x40 * (x) + 0x02C)
#घोषणा RCR(x)		(0x40 * (x) + 0x030)
#घोषणा TCR(x)		(0x40 * (x) + 0x034)
#घोषणा ISR(x)		(0x40 * (x) + 0x038)
#घोषणा IMR(x)		(0x40 * (x) + 0x03C)
#घोषणा ROR(x)		(0x40 * (x) + 0x040)
#घोषणा TOR(x)		(0x40 * (x) + 0x044)
#घोषणा RFCR(x)		(0x40 * (x) + 0x048)
#घोषणा TFCR(x)		(0x40 * (x) + 0x04C)
#घोषणा RFF(x)		(0x40 * (x) + 0x050)
#घोषणा TFF(x)		(0x40 * (x) + 0x054)

/* I2S COMP Registers */
#घोषणा I2S_COMP_PARAM_2	0x01F0
#घोषणा I2S_COMP_PARAM_1	0x01F4
#घोषणा I2S_COMP_VERSION	0x01F8
#घोषणा I2S_COMP_TYPE		0x01FC

/* PSS_GEN_CTRL_I2S_GEN_CFG_0 Registers */
#घोषणा I2S_GEN_CFG_0		0x000
#घोषणा PSS_CPR_RST_EN		0x010
#घोषणा PSS_CPR_RST_SET		0x014
#घोषणा PSS_CPR_CLK_CLR		0x000
#घोषणा PSS_CPR_AUX_RST_EN	0x070

#घोषणा CLOCK_PROVIDER_MODE	BIT(13)

/* Interrupt Flag */
#घोषणा TX_INT_FLAG		GENMASK(5, 4)
#घोषणा RX_INT_FLAG		GENMASK(1, 0)
/*
 * Component parameter रेजिस्टर fields - define the I2S block's
 * configuration.
 */
#घोषणा	COMP1_TX_WORDSIZE_3(r)		FIELD_GET(GENMASK(27, 25), (r))
#घोषणा	COMP1_TX_WORDSIZE_2(r)		FIELD_GET(GENMASK(24, 22), (r))
#घोषणा	COMP1_TX_WORDSIZE_1(r)		FIELD_GET(GENMASK(21, 19), (r))
#घोषणा	COMP1_TX_WORDSIZE_0(r)		FIELD_GET(GENMASK(18, 16), (r))
#घोषणा	COMP1_RX_ENABLED(r)		FIELD_GET(BIT(6), (r))
#घोषणा	COMP1_TX_ENABLED(r)		FIELD_GET(BIT(5), (r))
#घोषणा	COMP1_MODE_EN(r)		FIELD_GET(BIT(4), (r))
#घोषणा	COMP1_APB_DATA_WIDTH(r)		FIELD_GET(GENMASK(1, 0), (r))
#घोषणा	COMP2_RX_WORDSIZE_3(r)		FIELD_GET(GENMASK(12, 10), (r))
#घोषणा	COMP2_RX_WORDSIZE_2(r)		FIELD_GET(GENMASK(9, 7), (r))
#घोषणा	COMP2_RX_WORDSIZE_1(r)		FIELD_GET(GENMASK(5, 3), (r))
#घोषणा	COMP2_RX_WORDSIZE_0(r)		FIELD_GET(GENMASK(2, 0), (r))

/* Add 1 to the below रेजिस्टरs to indicate the actual size */
#घोषणा	COMP1_TX_CHANNELS(r)	(FIELD_GET(GENMASK(10, 9), (r)) + 1)
#घोषणा	COMP1_RX_CHANNELS(r)	(FIELD_GET(GENMASK(8, 7), (r)) + 1)
#घोषणा	COMP1_FIFO_DEPTH(r)	(FIELD_GET(GENMASK(3, 2), (r)) + 1)

/* Number of entries in WORDSIZE and DATA_WIDTH parameter रेजिस्टरs */
#घोषणा	COMP_MAX_WORDSIZE	8	/* 3 bits रेजिस्टर width */

#घोषणा MAX_CHANNEL_NUM		8
#घोषणा MIN_CHANNEL_NUM		2
#घोषणा MAX_ISR			4

#घोषणा TWO_CHANNEL_SUPPORT	2	/* up to 2.0 */
#घोषणा FOUR_CHANNEL_SUPPORT	4	/* up to 3.1 */
#घोषणा SIX_CHANNEL_SUPPORT	6	/* up to 5.1 */
#घोषणा EIGHT_CHANNEL_SUPPORT	8	/* up to 7.1 */

#घोषणा DWC_I2S_PLAY	BIT(0)
#घोषणा DWC_I2S_RECORD	BIT(1)
#घोषणा DW_I2S_CONSUMER	BIT(2)
#घोषणा DW_I2S_PROVIDER	BIT(3)

#घोषणा I2S_RXDMA	0x01C0
#घोषणा I2S_RRXDMA	0x01C4
#घोषणा I2S_TXDMA	0x01C8
#घोषणा I2S_RTXDMA	0x01CC
#घोषणा I2S_DMACR	0x0200
#घोषणा I2S_DMAEN_RXBLOCK	(1 << 16)
#घोषणा I2S_DMAEN_TXBLOCK	(1 << 17)

/*
 * काष्ठा i2s_clk_config_data - represent i2s clk configuration data
 * @chan_nr: number of channel
 * @data_width: number of bits per sample (8/16/24/32 bit)
 * @sample_rate: sampling frequency (8Khz, 16Khz, 48Khz)
 */
काष्ठा i2s_clk_config_data अणु
	पूर्णांक chan_nr;
	u32 data_width;
	u32 sample_rate;
पूर्ण;

काष्ठा kmb_i2s_info अणु
	व्योम __iomem *i2s_base;
	व्योम __iomem *pss_base;
	काष्ठा clk *clk_i2s;
	काष्ठा clk *clk_apb;
	पूर्णांक active;
	अचिन्हित पूर्णांक capability;
	अचिन्हित पूर्णांक i2s_reg_comp1;
	अचिन्हित पूर्णांक i2s_reg_comp2;
	काष्ठा device *dev;
	u32 ccr;
	u32 xfer_resolution;
	u32 fअगरo_th;
	bool घड़ी_provider;
	/* data related to DMA transfers b/w i2s and DMAC */
	काष्ठा snd_dmaengine_dai_dma_data play_dma_data;
	काष्ठा snd_dmaengine_dai_dma_data capture_dma_data;

	काष्ठा i2s_clk_config_data config;
	पूर्णांक (*i2s_clk_cfg)(काष्ठा i2s_clk_config_data *config);

	/* data related to PIO transfers */
	bool use_pio;
	काष्ठा snd_pcm_substream *tx_substream;
	काष्ठा snd_pcm_substream *rx_substream;
	अचिन्हित पूर्णांक tx_ptr;
	अचिन्हित पूर्णांक rx_ptr;
	bool iec958_fmt;
पूर्ण;

#पूर्ण_अगर /* KMB_PLATFORM_H_ */
