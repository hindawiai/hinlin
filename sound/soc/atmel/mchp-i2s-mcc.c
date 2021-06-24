<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Driver क्रम Microchip I2S Multi-channel controller
//
// Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries
//
// Author: Codrin Ciubotariu <codrin.ciubotariu@microchip.com>

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>

#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/lcm.h>
#समावेश <linux/of_device.h>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/initval.h>
#समावेश <sound/soc.h>
#समावेश <sound/dmaengine_pcm.h>

/*
 * ---- I2S Controller Register map ----
 */
#घोषणा MCHP_I2SMCC_CR		0x0000	/* Control Register */
#घोषणा MCHP_I2SMCC_MRA		0x0004	/* Mode Register A */
#घोषणा MCHP_I2SMCC_MRB		0x0008	/* Mode Register B */
#घोषणा MCHP_I2SMCC_SR		0x000C	/* Status Register */
#घोषणा MCHP_I2SMCC_IERA	0x0010	/* Interrupt Enable Register A */
#घोषणा MCHP_I2SMCC_IDRA	0x0014	/* Interrupt Disable Register A */
#घोषणा MCHP_I2SMCC_IMRA	0x0018	/* Interrupt Mask Register A */
#घोषणा MCHP_I2SMCC_ISRA	0X001C	/* Interrupt Status Register A */

#घोषणा MCHP_I2SMCC_IERB	0x0020	/* Interrupt Enable Register B */
#घोषणा MCHP_I2SMCC_IDRB	0x0024	/* Interrupt Disable Register B */
#घोषणा MCHP_I2SMCC_IMRB	0x0028	/* Interrupt Mask Register B */
#घोषणा MCHP_I2SMCC_ISRB	0X002C	/* Interrupt Status Register B */

#घोषणा MCHP_I2SMCC_RHR		0x0030	/* Receiver Holding Register */
#घोषणा MCHP_I2SMCC_THR		0x0034	/* Transmitter Holding Register */

#घोषणा MCHP_I2SMCC_RHL0R	0x0040	/* Receiver Holding Left 0 Register */
#घोषणा MCHP_I2SMCC_RHR0R	0x0044	/* Receiver Holding Right 0 Register */

#घोषणा MCHP_I2SMCC_RHL1R	0x0048	/* Receiver Holding Left 1 Register */
#घोषणा MCHP_I2SMCC_RHR1R	0x004C	/* Receiver Holding Right 1 Register */

#घोषणा MCHP_I2SMCC_RHL2R	0x0050	/* Receiver Holding Left 2 Register */
#घोषणा MCHP_I2SMCC_RHR2R	0x0054	/* Receiver Holding Right 2 Register */

#घोषणा MCHP_I2SMCC_RHL3R	0x0058	/* Receiver Holding Left 3 Register */
#घोषणा MCHP_I2SMCC_RHR3R	0x005C	/* Receiver Holding Right 3 Register */

#घोषणा MCHP_I2SMCC_THL0R	0x0060	/* Transmitter Holding Left 0 Register */
#घोषणा MCHP_I2SMCC_THR0R	0x0064	/* Transmitter Holding Right 0 Register */

#घोषणा MCHP_I2SMCC_THL1R	0x0068	/* Transmitter Holding Left 1 Register */
#घोषणा MCHP_I2SMCC_THR1R	0x006C	/* Transmitter Holding Right 1 Register */

#घोषणा MCHP_I2SMCC_THL2R	0x0070	/* Transmitter Holding Left 2 Register */
#घोषणा MCHP_I2SMCC_THR2R	0x0074	/* Transmitter Holding Right 2 Register */

#घोषणा MCHP_I2SMCC_THL3R	0x0078	/* Transmitter Holding Left 3 Register */
#घोषणा MCHP_I2SMCC_THR3R	0x007C	/* Transmitter Holding Right 3 Register */

#घोषणा MCHP_I2SMCC_VERSION	0x00FC	/* Version Register */

/*
 * ---- Control Register (Write-only) ----
 */
#घोषणा MCHP_I2SMCC_CR_RXEN		BIT(0)	/* Receiver Enable */
#घोषणा MCHP_I2SMCC_CR_RXDIS		BIT(1)	/* Receiver Disable */
#घोषणा MCHP_I2SMCC_CR_CKEN		BIT(2)	/* Clock Enable */
#घोषणा MCHP_I2SMCC_CR_CKDIS		BIT(3)	/* Clock Disable */
#घोषणा MCHP_I2SMCC_CR_TXEN		BIT(4)	/* Transmitter Enable */
#घोषणा MCHP_I2SMCC_CR_TXDIS		BIT(5)	/* Transmitter Disable */
#घोषणा MCHP_I2SMCC_CR_SWRST		BIT(7)	/* Software Reset */

/*
 * ---- Mode Register A (Read/Write) ----
 */
#घोषणा MCHP_I2SMCC_MRA_MODE_MASK		GENMASK(0, 0)
#घोषणा MCHP_I2SMCC_MRA_MODE_SLAVE		(0 << 0)
#घोषणा MCHP_I2SMCC_MRA_MODE_MASTER		(1 << 0)

#घोषणा MCHP_I2SMCC_MRA_DATALENGTH_MASK			GENMASK(3, 1)
#घोषणा MCHP_I2SMCC_MRA_DATALENGTH_32_BITS		(0 << 1)
#घोषणा MCHP_I2SMCC_MRA_DATALENGTH_24_BITS		(1 << 1)
#घोषणा MCHP_I2SMCC_MRA_DATALENGTH_20_BITS		(2 << 1)
#घोषणा MCHP_I2SMCC_MRA_DATALENGTH_18_BITS		(3 << 1)
#घोषणा MCHP_I2SMCC_MRA_DATALENGTH_16_BITS		(4 << 1)
#घोषणा MCHP_I2SMCC_MRA_DATALENGTH_16_BITS_COMPACT	(5 << 1)
#घोषणा MCHP_I2SMCC_MRA_DATALENGTH_8_BITS		(6 << 1)
#घोषणा MCHP_I2SMCC_MRA_DATALENGTH_8_BITS_COMPACT	(7 << 1)

#घोषणा MCHP_I2SMCC_MRA_WIRECFG_MASK		GENMASK(5, 4)
#घोषणा MCHP_I2SMCC_MRA_WIRECFG_TDM(pin)	(((pin) << 4) & \
						 MCHP_I2SMCC_MRA_WIRECFG_MASK)
#घोषणा MCHP_I2SMCC_MRA_WIRECFG_I2S_1_TDM_0	(0 << 4)
#घोषणा MCHP_I2SMCC_MRA_WIRECFG_I2S_2_TDM_1	(1 << 4)
#घोषणा MCHP_I2SMCC_MRA_WIRECFG_I2S_4_TDM_2	(2 << 4)
#घोषणा MCHP_I2SMCC_MRA_WIRECFG_TDM_3		(3 << 4)

#घोषणा MCHP_I2SMCC_MRA_FORMAT_MASK		GENMASK(7, 6)
#घोषणा MCHP_I2SMCC_MRA_FORMAT_I2S		(0 << 6)
#घोषणा MCHP_I2SMCC_MRA_FORMAT_LJ		(1 << 6) /* Left Justअगरied */
#घोषणा MCHP_I2SMCC_MRA_FORMAT_TDM		(2 << 6)
#घोषणा MCHP_I2SMCC_MRA_FORMAT_TDMLJ		(3 << 6)

/* Transmitter uses one DMA channel ... */
/* Left audio samples duplicated to right audio channel */
#घोषणा MCHP_I2SMCC_MRA_RXMONO			BIT(8)

/* I2SDO output of I2SC is पूर्णांकernally connected to I2SDI input */
#घोषणा MCHP_I2SMCC_MRA_RXLOOP			BIT(9)

/* Receiver uses one DMA channel ... */
/* Left audio samples duplicated to right audio channel */
#घोषणा MCHP_I2SMCC_MRA_TXMONO			BIT(10)

/* x sample transmitted when underrun */
#घोषणा MCHP_I2SMCC_MRA_TXSAME_ZERO		(0 << 11) /* Zero sample */
#घोषणा MCHP_I2SMCC_MRA_TXSAME_PREVIOUS		(1 << 11) /* Previous sample */

/* select between peripheral घड़ी and generated घड़ी */
#घोषणा MCHP_I2SMCC_MRA_SRCCLK_PCLK		(0 << 12)
#घोषणा MCHP_I2SMCC_MRA_SRCCLK_GCLK		(1 << 12)

/* Number of TDM Channels - 1 */
#घोषणा MCHP_I2SMCC_MRA_NBCHAN_MASK		GENMASK(15, 13)
#घोषणा MCHP_I2SMCC_MRA_NBCHAN(ch) \
	((((ch) - 1) << 13) & MCHP_I2SMCC_MRA_NBCHAN_MASK)

/* Selected Clock to I2SMCC Master Clock ratio */
#घोषणा MCHP_I2SMCC_MRA_IMCKDIV_MASK		GENMASK(21, 16)
#घोषणा MCHP_I2SMCC_MRA_IMCKDIV(भाग) \
	(((भाग) << 16) & MCHP_I2SMCC_MRA_IMCKDIV_MASK)

/* TDM Frame Synchronization */
#घोषणा MCHP_I2SMCC_MRA_TDMFS_MASK		GENMASK(23, 22)
#घोषणा MCHP_I2SMCC_MRA_TDMFS_SLOT		(0 << 22)
#घोषणा MCHP_I2SMCC_MRA_TDMFS_HALF		(1 << 22)
#घोषणा MCHP_I2SMCC_MRA_TDMFS_BIT		(2 << 22)

/* Selected Clock to I2SMC Serial Clock ratio */
#घोषणा MCHP_I2SMCC_MRA_ISCKDIV_MASK		GENMASK(29, 24)
#घोषणा MCHP_I2SMCC_MRA_ISCKDIV(भाग) \
	(((भाग) << 24) & MCHP_I2SMCC_MRA_ISCKDIV_MASK)

/* Master Clock mode */
#घोषणा MCHP_I2SMCC_MRA_IMCKMODE_MASK		GENMASK(30, 30)
/* 0: No master घड़ी generated*/
#घोषणा MCHP_I2SMCC_MRA_IMCKMODE_NONE		(0 << 30)
/* 1: master घड़ी generated (पूर्णांकernally generated घड़ी drives I2SMCK pin) */
#घोषणा MCHP_I2SMCC_MRA_IMCKMODE_GEN		(1 << 30)

/* Slot Width */
/* 0: slot is 32 bits wide क्रम DATALENGTH = 18/20/24 bits. */
/* 1: slot is 24 bits wide क्रम DATALENGTH = 18/20/24 bits. */
#घोषणा MCHP_I2SMCC_MRA_IWS			BIT(31)

/*
 * ---- Mode Register B (Read/Write) ----
 */
/* all enabled I2S left channels are filled first, then I2S right channels */
#घोषणा MCHP_I2SMCC_MRB_CRAMODE_LEFT_FIRST	(0 << 0)
/*
 * an enabled I2S left channel is filled, then the corresponding right
 * channel, until all channels are filled
 */
#घोषणा MCHP_I2SMCC_MRB_CRAMODE_REGULAR		(1 << 0)

#घोषणा MCHP_I2SMCC_MRB_FIFOEN			BIT(4)

#घोषणा MCHP_I2SMCC_MRB_DMACHUNK_MASK		GENMASK(9, 8)
#घोषणा MCHP_I2SMCC_MRB_DMACHUNK(no_words) \
	(((fls(no_words) - 1) << 8) & MCHP_I2SMCC_MRB_DMACHUNK_MASK)

#घोषणा MCHP_I2SMCC_MRB_CLKSEL_MASK		GENMASK(16, 16)
#घोषणा MCHP_I2SMCC_MRB_CLKSEL_EXT		(0 << 16)
#घोषणा MCHP_I2SMCC_MRB_CLKSEL_INT		(1 << 16)

/*
 * ---- Status Registers (Read-only) ----
 */
#घोषणा MCHP_I2SMCC_SR_RXEN		BIT(0)	/* Receiver Enabled */
#घोषणा MCHP_I2SMCC_SR_TXEN		BIT(4)	/* Transmitter Enabled */

/*
 * ---- Interrupt Enable/Disable/Mask/Status Registers A ----
 */
#घोषणा MCHP_I2SMCC_INT_TXRDY_MASK(ch)		GENMASK((ch) - 1, 0)
#घोषणा MCHP_I2SMCC_INT_TXRDYCH(ch)		BIT(ch)
#घोषणा MCHP_I2SMCC_INT_TXUNF_MASK(ch)		GENMASK((ch) + 7, 8)
#घोषणा MCHP_I2SMCC_INT_TXUNFCH(ch)		BIT((ch) + 8)
#घोषणा MCHP_I2SMCC_INT_RXRDY_MASK(ch)		GENMASK((ch) + 15, 16)
#घोषणा MCHP_I2SMCC_INT_RXRDYCH(ch)		BIT((ch) + 16)
#घोषणा MCHP_I2SMCC_INT_RXOVF_MASK(ch)		GENMASK((ch) + 23, 24)
#घोषणा MCHP_I2SMCC_INT_RXOVFCH(ch)		BIT((ch) + 24)

/*
 * ---- Interrupt Enable/Disable/Mask/Status Registers B ----
 */
#घोषणा MCHP_I2SMCC_INT_WERR			BIT(0)
#घोषणा MCHP_I2SMCC_INT_TXFFRDY			BIT(8)
#घोषणा MCHP_I2SMCC_INT_TXFFEMP			BIT(9)
#घोषणा MCHP_I2SMCC_INT_RXFFRDY			BIT(12)
#घोषणा MCHP_I2SMCC_INT_RXFFFUL			BIT(13)

/*
 * ---- Version Register (Read-only) ----
 */
#घोषणा MCHP_I2SMCC_VERSION_MASK		GENMASK(11, 0)

#घोषणा MCHP_I2SMCC_MAX_CHANNELS		8
#घोषणा MCHP_I2MCC_TDM_SLOT_WIDTH		32

अटल स्थिर काष्ठा regmap_config mchp_i2s_mcc_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.max_रेजिस्टर = MCHP_I2SMCC_VERSION,
पूर्ण;

काष्ठा mchp_i2s_mcc_soc_data अणु
	अचिन्हित पूर्णांक	data_pin_pair_num;
	bool		has_fअगरo;
पूर्ण;

काष्ठा mchp_i2s_mcc_dev अणु
	काष्ठा रुको_queue_head			wq_txrdy;
	काष्ठा रुको_queue_head			wq_rxrdy;
	काष्ठा device				*dev;
	काष्ठा regmap				*regmap;
	काष्ठा clk				*pclk;
	काष्ठा clk				*gclk;
	स्थिर काष्ठा mchp_i2s_mcc_soc_data	*soc;
	काष्ठा snd_dmaengine_dai_dma_data	playback;
	काष्ठा snd_dmaengine_dai_dma_data	capture;
	अचिन्हित पूर्णांक				fmt;
	अचिन्हित पूर्णांक				sysclk;
	अचिन्हित पूर्णांक				frame_length;
	पूर्णांक					tdm_slots;
	पूर्णांक					channels;
	u8					tdm_data_pair;
	अचिन्हित पूर्णांक				gclk_use:1;
	अचिन्हित पूर्णांक				gclk_running:1;
	अचिन्हित पूर्णांक				tx_rdy:1;
	अचिन्हित पूर्णांक				rx_rdy:1;
पूर्ण;

अटल irqवापस_t mchp_i2s_mcc_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mchp_i2s_mcc_dev *dev = dev_id;
	u32 sra, imra, srb, imrb, pendinga, pendingb, idra = 0, idrb = 0;
	irqवापस_t ret = IRQ_NONE;

	regmap_पढ़ो(dev->regmap, MCHP_I2SMCC_IMRA, &imra);
	regmap_पढ़ो(dev->regmap, MCHP_I2SMCC_ISRA, &sra);
	pendinga = imra & sra;

	regmap_पढ़ो(dev->regmap, MCHP_I2SMCC_IMRB, &imrb);
	regmap_पढ़ो(dev->regmap, MCHP_I2SMCC_ISRB, &srb);
	pendingb = imrb & srb;

	अगर (!pendinga && !pendingb)
		वापस IRQ_NONE;

	/*
	 * Tx/Rx पढ़ोy पूर्णांकerrupts are enabled when stopping only, to assure
	 * availability and to disable घड़ीs अगर necessary
	 */
	अगर (dev->soc->has_fअगरo) अणु
		idrb |= pendingb & (MCHP_I2SMCC_INT_TXFFRDY |
				    MCHP_I2SMCC_INT_RXFFRDY);
	पूर्ण अन्यथा अणु
		idra |= pendinga & (MCHP_I2SMCC_INT_TXRDY_MASK(dev->channels) |
				    MCHP_I2SMCC_INT_RXRDY_MASK(dev->channels));
	पूर्ण
	अगर (idra || idrb)
		ret = IRQ_HANDLED;

	अगर ((!dev->soc->has_fअगरo &&
	     (imra & MCHP_I2SMCC_INT_TXRDY_MASK(dev->channels)) &&
	     (imra & MCHP_I2SMCC_INT_TXRDY_MASK(dev->channels)) ==
	     (idra & MCHP_I2SMCC_INT_TXRDY_MASK(dev->channels))) ||
	    (dev->soc->has_fअगरo && imrb & MCHP_I2SMCC_INT_TXFFRDY)) अणु
		dev->tx_rdy = 1;
		wake_up_पूर्णांकerruptible(&dev->wq_txrdy);
	पूर्ण
	अगर ((!dev->soc->has_fअगरo &&
	     (imra & MCHP_I2SMCC_INT_RXRDY_MASK(dev->channels)) &&
	     (imra & MCHP_I2SMCC_INT_RXRDY_MASK(dev->channels)) ==
	     (idra & MCHP_I2SMCC_INT_RXRDY_MASK(dev->channels))) ||
	    (dev->soc->has_fअगरo && imrb & MCHP_I2SMCC_INT_RXFFRDY)) अणु
		dev->rx_rdy = 1;
		wake_up_पूर्णांकerruptible(&dev->wq_rxrdy);
	पूर्ण
	अगर (dev->soc->has_fअगरo)
		regmap_ग_लिखो(dev->regmap, MCHP_I2SMCC_IDRB, idrb);
	अन्यथा
		regmap_ग_लिखो(dev->regmap, MCHP_I2SMCC_IDRA, idra);

	वापस ret;
पूर्ण

अटल पूर्णांक mchp_i2s_mcc_set_sysclk(काष्ठा snd_soc_dai *dai,
				   पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा mchp_i2s_mcc_dev *dev = snd_soc_dai_get_drvdata(dai);

	dev_dbg(dev->dev, "%s() clk_id=%d freq=%u dir=%d\n",
		__func__, clk_id, freq, dir);

	/* We करो not need SYSCLK */
	अगर (dir == SND_SOC_CLOCK_IN)
		वापस 0;

	dev->sysclk = freq;

	वापस 0;
पूर्ण

अटल पूर्णांक mchp_i2s_mcc_set_bclk_ratio(काष्ठा snd_soc_dai *dai,
				       अचिन्हित पूर्णांक ratio)
अणु
	काष्ठा mchp_i2s_mcc_dev *dev = snd_soc_dai_get_drvdata(dai);

	dev_dbg(dev->dev, "%s() ratio=%u\n", __func__, ratio);

	dev->frame_length = ratio;

	वापस 0;
पूर्ण

अटल पूर्णांक mchp_i2s_mcc_set_dai_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा mchp_i2s_mcc_dev *dev = snd_soc_dai_get_drvdata(dai);

	dev_dbg(dev->dev, "%s() fmt=%#x\n", __func__, fmt);

	/* We करोn't support any kind of घड़ी inversion */
	अगर ((fmt & SND_SOC_DAIFMT_INV_MASK) != SND_SOC_DAIFMT_NB_NF)
		वापस -EINVAL;

	/* We can't generate only FSYNC */
	अगर ((fmt & SND_SOC_DAIFMT_MASTER_MASK) == SND_SOC_DAIFMT_CBM_CFS)
		वापस -EINVAL;

	/* We can only reconfigure the IP when it's stopped */
	अगर (fmt & SND_SOC_DAIFMT_CONT)
		वापस -EINVAL;

	dev->fmt = fmt;

	वापस 0;
पूर्ण

अटल पूर्णांक mchp_i2s_mcc_set_dai_tdm_slot(काष्ठा snd_soc_dai *dai,
					 अचिन्हित पूर्णांक tx_mask,
					 अचिन्हित पूर्णांक rx_mask,
					 पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा mchp_i2s_mcc_dev *dev = snd_soc_dai_get_drvdata(dai);

	dev_dbg(dev->dev,
		"%s() tx_mask=0x%08x rx_mask=0x%08x slots=%d width=%d\n",
		__func__, tx_mask, rx_mask, slots, slot_width);

	अगर (slots < 0 || slots > MCHP_I2SMCC_MAX_CHANNELS ||
	    slot_width != MCHP_I2MCC_TDM_SLOT_WIDTH)
		वापस -EINVAL;

	अगर (slots) अणु
		/* We करो not support daisy chain */
		अगर (rx_mask != GENMASK(slots - 1, 0) ||
		    rx_mask != tx_mask)
			वापस -EINVAL;
	पूर्ण

	dev->tdm_slots = slots;
	dev->frame_length = slots * MCHP_I2MCC_TDM_SLOT_WIDTH;

	वापस 0;
पूर्ण

अटल पूर्णांक mchp_i2s_mcc_clk_get_rate_dअगरf(काष्ठा clk *clk,
					  अचिन्हित दीर्घ rate,
					  काष्ठा clk **best_clk,
					  अचिन्हित दीर्घ *best_rate,
					  अचिन्हित दीर्घ *best_dअगरf_rate)
अणु
	दीर्घ round_rate;
	अचिन्हित पूर्णांक dअगरf_rate;

	round_rate = clk_round_rate(clk, rate);
	अगर (round_rate < 0)
		वापस (पूर्णांक)round_rate;

	dअगरf_rate = असल(rate - round_rate);
	अगर (dअगरf_rate < *best_dअगरf_rate) अणु
		*best_clk = clk;
		*best_dअगरf_rate = dअगरf_rate;
		*best_rate = rate;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mchp_i2s_mcc_config_भागs(काष्ठा mchp_i2s_mcc_dev *dev,
				    अचिन्हित पूर्णांक bclk, अचिन्हित पूर्णांक *mra,
				    अचिन्हित दीर्घ *best_rate)
अणु
	अचिन्हित दीर्घ clk_rate;
	अचिन्हित दीर्घ lcm_rate;
	अचिन्हित दीर्घ best_dअगरf_rate = ~0;
	अचिन्हित पूर्णांक sysclk;
	काष्ठा clk *best_clk = शून्य;
	पूर्णांक ret;

	/* For code simplअगरication */
	अगर (!dev->sysclk)
		sysclk = bclk;
	अन्यथा
		sysclk = dev->sysclk;

	/*
	 * MCLK is Selected CLK / (2 * IMCKDIV),
	 * BCLK is Selected CLK / (2 * ISCKDIV);
	 * अगर IMCKDIV or ISCKDIV are 0, MCLK or BCLK = Selected CLK
	 */
	lcm_rate = lcm(sysclk, bclk);
	अगर ((lcm_rate / sysclk % 2 == 1 && lcm_rate / sysclk > 2) ||
	    (lcm_rate / bclk % 2 == 1 && lcm_rate / bclk > 2))
		lcm_rate *= 2;

	क्रम (clk_rate = lcm_rate;
	     (clk_rate == sysclk || clk_rate / (sysclk * 2) <= GENMASK(5, 0)) &&
	     (clk_rate == bclk || clk_rate / (bclk * 2) <= GENMASK(5, 0));
	     clk_rate += lcm_rate) अणु
		ret = mchp_i2s_mcc_clk_get_rate_dअगरf(dev->gclk, clk_rate,
						     &best_clk, best_rate,
						     &best_dअगरf_rate);
		अगर (ret) अणु
			dev_err(dev->dev, "gclk error for rate %lu: %d",
				clk_rate, ret);
		पूर्ण अन्यथा अणु
			अगर (!best_dअगरf_rate) अणु
				dev_dbg(dev->dev, "found perfect rate on gclk: %lu\n",
					clk_rate);
				अवरोध;
			पूर्ण
		पूर्ण

		ret = mchp_i2s_mcc_clk_get_rate_dअगरf(dev->pclk, clk_rate,
						     &best_clk, best_rate,
						     &best_dअगरf_rate);
		अगर (ret) अणु
			dev_err(dev->dev, "pclk error for rate %lu: %d",
				clk_rate, ret);
		पूर्ण अन्यथा अणु
			अगर (!best_dअगरf_rate) अणु
				dev_dbg(dev->dev, "found perfect rate on pclk: %lu\n",
					clk_rate);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/* check अगर घड़ीs वापसed only errors */
	अगर (!best_clk) अणु
		dev_err(dev->dev, "unable to change rate to clocks\n");
		वापस -EINVAL;
	पूर्ण

	dev_dbg(dev->dev, "source CLK is %s with rate %lu, diff %lu\n",
		best_clk == dev->pclk ? "pclk" : "gclk",
		*best_rate, best_dअगरf_rate);

	/* Configure भागisors */
	अगर (dev->sysclk)
		*mra |= MCHP_I2SMCC_MRA_IMCKDIV(*best_rate / (2 * sysclk));
	*mra |= MCHP_I2SMCC_MRA_ISCKDIV(*best_rate / (2 * bclk));

	अगर (best_clk == dev->gclk)
		*mra |= MCHP_I2SMCC_MRA_SRCCLK_GCLK;
	अन्यथा
		*mra |= MCHP_I2SMCC_MRA_SRCCLK_PCLK;

	वापस 0;
पूर्ण

अटल पूर्णांक mchp_i2s_mcc_is_running(काष्ठा mchp_i2s_mcc_dev *dev)
अणु
	u32 sr;

	regmap_पढ़ो(dev->regmap, MCHP_I2SMCC_SR, &sr);
	वापस !!(sr & (MCHP_I2SMCC_SR_TXEN | MCHP_I2SMCC_SR_RXEN));
पूर्ण

अटल पूर्णांक mchp_i2s_mcc_hw_params(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_pcm_hw_params *params,
				  काष्ठा snd_soc_dai *dai)
अणु
	अचिन्हित दीर्घ rate = 0;
	काष्ठा mchp_i2s_mcc_dev *dev = snd_soc_dai_get_drvdata(dai);
	u32 mra = 0;
	u32 mrb = 0;
	अचिन्हित पूर्णांक channels = params_channels(params);
	अचिन्हित पूर्णांक frame_length = dev->frame_length;
	अचिन्हित पूर्णांक bclk_rate;
	पूर्णांक set_भागs = 0;
	पूर्णांक ret;
	bool is_playback = (substream->stream == SNDRV_PCM_STREAM_PLAYBACK);

	dev_dbg(dev->dev, "%s() rate=%u format=%#x width=%u channels=%u\n",
		__func__, params_rate(params), params_क्रमmat(params),
		params_width(params), params_channels(params));

	चयन (dev->fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		अगर (dev->tdm_slots) अणु
			dev_err(dev->dev, "I2S with TDM is not supported\n");
			वापस -EINVAL;
		पूर्ण
		mra |= MCHP_I2SMCC_MRA_FORMAT_I2S;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		अगर (dev->tdm_slots) अणु
			dev_err(dev->dev, "Left-Justified with TDM is not supported\n");
			वापस -EINVAL;
		पूर्ण
		mra |= MCHP_I2SMCC_MRA_FORMAT_LJ;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		mra |= MCHP_I2SMCC_MRA_FORMAT_TDM;
		अवरोध;
	शेष:
		dev_err(dev->dev, "unsupported bus format\n");
		वापस -EINVAL;
	पूर्ण

	चयन (dev->fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		/* cpu is BCLK and LRC master */
		mra |= MCHP_I2SMCC_MRA_MODE_MASTER;
		अगर (dev->sysclk)
			mra |= MCHP_I2SMCC_MRA_IMCKMODE_GEN;
		set_भागs = 1;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFM:
		/* cpu is BCLK master */
		mrb |= MCHP_I2SMCC_MRB_CLKSEL_INT;
		set_भागs = 1;
		fallthrough;
	हाल SND_SOC_DAIFMT_CBM_CFM:
		/* cpu is slave */
		mra |= MCHP_I2SMCC_MRA_MODE_SLAVE;
		अगर (dev->sysclk)
			dev_warn(dev->dev, "Unable to generate MCLK in Slave mode\n");
		अवरोध;
	शेष:
		dev_err(dev->dev, "unsupported master/slave mode\n");
		वापस -EINVAL;
	पूर्ण

	अगर (dev->fmt & (SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_LEFT_J)) अणु
		/* क्रम I2S and LEFT_J one pin is needed क्रम every 2 channels */
		अगर (channels > dev->soc->data_pin_pair_num * 2) अणु
			dev_err(dev->dev,
				"unsupported number of audio channels: %d\n",
				channels);
			वापस -EINVAL;
		पूर्ण

		/* enable क्रम पूर्णांकerleaved क्रमmat */
		mrb |= MCHP_I2SMCC_MRB_CRAMODE_REGULAR;

		चयन (channels) अणु
		हाल 1:
			अगर (is_playback)
				mra |= MCHP_I2SMCC_MRA_TXMONO;
			अन्यथा
				mra |= MCHP_I2SMCC_MRA_RXMONO;
			अवरोध;
		हाल 2:
			अवरोध;
		हाल 4:
			mra |= MCHP_I2SMCC_MRA_WIRECFG_I2S_2_TDM_1;
			अवरोध;
		हाल 8:
			mra |= MCHP_I2SMCC_MRA_WIRECFG_I2S_4_TDM_2;
			अवरोध;
		शेष:
			dev_err(dev->dev, "unsupported number of audio channels\n");
			वापस -EINVAL;
		पूर्ण

		अगर (!frame_length)
			frame_length = 2 * params_physical_width(params);
	पूर्ण अन्यथा अगर (dev->fmt & SND_SOC_DAIFMT_DSP_A) अणु
		mra |= MCHP_I2SMCC_MRA_WIRECFG_TDM(dev->tdm_data_pair);

		अगर (dev->tdm_slots) अणु
			अगर (channels % 2 && channels * 2 <= dev->tdm_slots) अणु
				/*
				 * Duplicate data क्रम even-numbered channels
				 * to odd-numbered channels
				 */
				अगर (is_playback)
					mra |= MCHP_I2SMCC_MRA_TXMONO;
				अन्यथा
					mra |= MCHP_I2SMCC_MRA_RXMONO;
			पूर्ण
			channels = dev->tdm_slots;
		पूर्ण

		mra |= MCHP_I2SMCC_MRA_NBCHAN(channels);
		अगर (!frame_length)
			frame_length = channels * MCHP_I2MCC_TDM_SLOT_WIDTH;
	पूर्ण

	/*
	 * We must have the same burst size configured
	 * in the DMA transfer and in out IP
	 */
	mrb |= MCHP_I2SMCC_MRB_DMACHUNK(channels);
	अगर (is_playback)
		dev->playback.maxburst = 1 << (fls(channels) - 1);
	अन्यथा
		dev->capture.maxburst = 1 << (fls(channels) - 1);

	चयन (params_क्रमmat(params)) अणु
	हाल SNDRV_PCM_FORMAT_S8:
		mra |= MCHP_I2SMCC_MRA_DATALENGTH_8_BITS;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S16_LE:
		mra |= MCHP_I2SMCC_MRA_DATALENGTH_16_BITS;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S18_3LE:
		mra |= MCHP_I2SMCC_MRA_DATALENGTH_18_BITS |
		       MCHP_I2SMCC_MRA_IWS;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S20_3LE:
		mra |= MCHP_I2SMCC_MRA_DATALENGTH_20_BITS |
		       MCHP_I2SMCC_MRA_IWS;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S24_3LE:
		mra |= MCHP_I2SMCC_MRA_DATALENGTH_24_BITS |
		       MCHP_I2SMCC_MRA_IWS;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S24_LE:
		mra |= MCHP_I2SMCC_MRA_DATALENGTH_24_BITS;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S32_LE:
		mra |= MCHP_I2SMCC_MRA_DATALENGTH_32_BITS;
		अवरोध;
	शेष:
		dev_err(dev->dev, "unsupported size/endianness for audio samples\n");
		वापस -EINVAL;
	पूर्ण

	अगर (set_भागs) अणु
		bclk_rate = frame_length * params_rate(params);
		ret = mchp_i2s_mcc_config_भागs(dev, bclk_rate, &mra,
					       &rate);
		अगर (ret) अणु
			dev_err(dev->dev,
				"unable to configure the divisors: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	/* enable FIFO अगर available */
	अगर (dev->soc->has_fअगरo)
		mrb |= MCHP_I2SMCC_MRB_FIFOEN;

	/*
	 * If we are alपढ़ोy running, the wanted setup must be
	 * the same with the one that's currently ongoing
	 */
	अगर (mchp_i2s_mcc_is_running(dev)) अणु
		u32 mra_cur;
		u32 mrb_cur;

		regmap_पढ़ो(dev->regmap, MCHP_I2SMCC_MRA, &mra_cur);
		regmap_पढ़ो(dev->regmap, MCHP_I2SMCC_MRB, &mrb_cur);
		अगर (mra != mra_cur || mrb != mrb_cur)
			वापस -EINVAL;

		वापस 0;
	पूर्ण

	अगर (mra & MCHP_I2SMCC_MRA_SRCCLK_GCLK && !dev->gclk_use) अणु
		/* set the rate */
		ret = clk_set_rate(dev->gclk, rate);
		अगर (ret) अणु
			dev_err(dev->dev,
				"unable to set rate %lu to GCLK: %d\n",
				rate, ret);
			वापस ret;
		पूर्ण

		ret = clk_prepare(dev->gclk);
		अगर (ret < 0) अणु
			dev_err(dev->dev, "unable to prepare GCLK: %d\n", ret);
			वापस ret;
		पूर्ण
		dev->gclk_use = 1;
	पूर्ण

	/* Save the number of channels to know what पूर्णांकerrupts to enable */
	dev->channels = channels;

	ret = regmap_ग_लिखो(dev->regmap, MCHP_I2SMCC_MRA, mra);
	अगर (ret < 0) अणु
		अगर (dev->gclk_use) अणु
			clk_unprepare(dev->gclk);
			dev->gclk_use = 0;
		पूर्ण
		वापस ret;
	पूर्ण
	वापस regmap_ग_लिखो(dev->regmap, MCHP_I2SMCC_MRB, mrb);
पूर्ण

अटल पूर्णांक mchp_i2s_mcc_hw_मुक्त(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा mchp_i2s_mcc_dev *dev = snd_soc_dai_get_drvdata(dai);
	bool is_playback = (substream->stream == SNDRV_PCM_STREAM_PLAYBACK);
	दीर्घ err;

	अगर (is_playback) अणु
		err = रुको_event_पूर्णांकerruptible_समयout(dev->wq_txrdy,
						       dev->tx_rdy,
						       msecs_to_jअगरfies(500));
		अगर (err == 0) अणु
			dev_warn_once(dev->dev,
				      "Timeout waiting for Tx ready\n");
			अगर (dev->soc->has_fअगरo)
				regmap_ग_लिखो(dev->regmap, MCHP_I2SMCC_IDRB,
					     MCHP_I2SMCC_INT_TXFFRDY);
			अन्यथा
				regmap_ग_लिखो(dev->regmap, MCHP_I2SMCC_IDRA,
					     MCHP_I2SMCC_INT_TXRDY_MASK(dev->channels));

			dev->tx_rdy = 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		err = रुको_event_पूर्णांकerruptible_समयout(dev->wq_rxrdy,
						       dev->rx_rdy,
						       msecs_to_jअगरfies(500));
		अगर (err == 0) अणु
			dev_warn_once(dev->dev,
				      "Timeout waiting for Rx ready\n");
			अगर (dev->soc->has_fअगरo)
				regmap_ग_लिखो(dev->regmap, MCHP_I2SMCC_IDRB,
					     MCHP_I2SMCC_INT_RXFFRDY);
			अन्यथा
				regmap_ग_लिखो(dev->regmap, MCHP_I2SMCC_IDRA,
					     MCHP_I2SMCC_INT_RXRDY_MASK(dev->channels));
			dev->rx_rdy = 1;
		पूर्ण
	पूर्ण

	अगर (!mchp_i2s_mcc_is_running(dev)) अणु
		regmap_ग_लिखो(dev->regmap, MCHP_I2SMCC_CR, MCHP_I2SMCC_CR_CKDIS);

		अगर (dev->gclk_running) अणु
			clk_disable(dev->gclk);
			dev->gclk_running = 0;
		पूर्ण
		अगर (dev->gclk_use) अणु
			clk_unprepare(dev->gclk);
			dev->gclk_use = 0;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mchp_i2s_mcc_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा mchp_i2s_mcc_dev *dev = snd_soc_dai_get_drvdata(dai);
	bool is_playback = (substream->stream == SNDRV_PCM_STREAM_PLAYBACK);
	u32 cr = 0;
	u32 iera = 0, ierb = 0;
	u32 sr;
	पूर्णांक err;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		अगर (is_playback)
			cr = MCHP_I2SMCC_CR_TXEN | MCHP_I2SMCC_CR_CKEN;
		अन्यथा
			cr = MCHP_I2SMCC_CR_RXEN | MCHP_I2SMCC_CR_CKEN;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		regmap_पढ़ो(dev->regmap, MCHP_I2SMCC_SR, &sr);
		अगर (is_playback && (sr & MCHP_I2SMCC_SR_TXEN)) अणु
			cr = MCHP_I2SMCC_CR_TXDIS;
			dev->tx_rdy = 0;
			/*
			 * Enable Tx Ready पूर्णांकerrupts on all channels
			 * to assure all data is sent
			 */
			अगर (dev->soc->has_fअगरo)
				ierb = MCHP_I2SMCC_INT_TXFFRDY;
			अन्यथा
				iera = MCHP_I2SMCC_INT_TXRDY_MASK(dev->channels);
		पूर्ण अन्यथा अगर (!is_playback && (sr & MCHP_I2SMCC_SR_RXEN)) अणु
			cr = MCHP_I2SMCC_CR_RXDIS;
			dev->rx_rdy = 0;
			/*
			 * Enable Rx Ready पूर्णांकerrupts on all channels
			 * to assure all data is received
			 */
			अगर (dev->soc->has_fअगरo)
				ierb = MCHP_I2SMCC_INT_RXFFRDY;
			अन्यथा
				iera = MCHP_I2SMCC_INT_RXRDY_MASK(dev->channels);
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर ((cr & MCHP_I2SMCC_CR_CKEN) && dev->gclk_use &&
	    !dev->gclk_running) अणु
		err = clk_enable(dev->gclk);
		अगर (err) अणु
			dev_err_once(dev->dev, "failed to enable GCLK: %d\n",
				     err);
		पूर्ण अन्यथा अणु
			dev->gclk_running = 1;
		पूर्ण
	पूर्ण

	अगर (dev->soc->has_fअगरo)
		regmap_ग_लिखो(dev->regmap, MCHP_I2SMCC_IERB, ierb);
	अन्यथा
		regmap_ग_लिखो(dev->regmap, MCHP_I2SMCC_IERA, iera);
	regmap_ग_लिखो(dev->regmap, MCHP_I2SMCC_CR, cr);

	वापस 0;
पूर्ण

अटल पूर्णांक mchp_i2s_mcc_startup(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा mchp_i2s_mcc_dev *dev = snd_soc_dai_get_drvdata(dai);

	/* Software reset the IP अगर it's not running */
	अगर (!mchp_i2s_mcc_is_running(dev)) अणु
		वापस regmap_ग_लिखो(dev->regmap, MCHP_I2SMCC_CR,
				    MCHP_I2SMCC_CR_SWRST);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops mchp_i2s_mcc_dai_ops = अणु
	.set_sysclk	= mchp_i2s_mcc_set_sysclk,
	.set_bclk_ratio = mchp_i2s_mcc_set_bclk_ratio,
	.startup	= mchp_i2s_mcc_startup,
	.trigger	= mchp_i2s_mcc_trigger,
	.hw_params	= mchp_i2s_mcc_hw_params,
	.hw_मुक्त	= mchp_i2s_mcc_hw_मुक्त,
	.set_fmt	= mchp_i2s_mcc_set_dai_fmt,
	.set_tdm_slot	= mchp_i2s_mcc_set_dai_tdm_slot,
पूर्ण;

अटल पूर्णांक mchp_i2s_mcc_dai_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा mchp_i2s_mcc_dev *dev = snd_soc_dai_get_drvdata(dai);

	init_रुकोqueue_head(&dev->wq_txrdy);
	init_रुकोqueue_head(&dev->wq_rxrdy);
	dev->tx_rdy = 1;
	dev->rx_rdy = 1;

	snd_soc_dai_init_dma_data(dai, &dev->playback, &dev->capture);

	वापस 0;
पूर्ण

#घोषणा MCHP_I2SMCC_RATES              SNDRV_PCM_RATE_8000_192000

#घोषणा MCHP_I2SMCC_FORMATS	(SNDRV_PCM_FMTBIT_S8 |          \
				 SNDRV_PCM_FMTBIT_S16_LE |      \
				 SNDRV_PCM_FMTBIT_S18_3LE |     \
				 SNDRV_PCM_FMTBIT_S20_3LE |     \
				 SNDRV_PCM_FMTBIT_S24_3LE |     \
				 SNDRV_PCM_FMTBIT_S24_LE |      \
				 SNDRV_PCM_FMTBIT_S32_LE)

अटल काष्ठा snd_soc_dai_driver mchp_i2s_mcc_dai = अणु
	.probe	= mchp_i2s_mcc_dai_probe,
	.playback = अणु
		.stream_name = "I2SMCC-Playback",
		.channels_min = 1,
		.channels_max = 8,
		.rates = MCHP_I2SMCC_RATES,
		.क्रमmats = MCHP_I2SMCC_FORMATS,
	पूर्ण,
	.capture = अणु
		.stream_name = "I2SMCC-Capture",
		.channels_min = 1,
		.channels_max = 8,
		.rates = MCHP_I2SMCC_RATES,
		.क्रमmats = MCHP_I2SMCC_FORMATS,
	पूर्ण,
	.ops = &mchp_i2s_mcc_dai_ops,
	.symmetric_rate = 1,
	.symmetric_sample_bits = 1,
	.symmetric_channels = 1,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver mchp_i2s_mcc_component = अणु
	.name	= "mchp-i2s-mcc",
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल काष्ठा mchp_i2s_mcc_soc_data mchp_i2s_mcc_sam9x60 = अणु
	.data_pin_pair_num = 1,
पूर्ण;

अटल काष्ठा mchp_i2s_mcc_soc_data mchp_i2s_mcc_sama7g5 = अणु
	.data_pin_pair_num = 4,
	.has_fअगरo = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mchp_i2s_mcc_dt_ids[] = अणु
	अणु
		.compatible = "microchip,sam9x60-i2smcc",
		.data = &mchp_i2s_mcc_sam9x60,
	पूर्ण,
	अणु
		.compatible = "microchip,sama7g5-i2smcc",
		.data = &mchp_i2s_mcc_sama7g5,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mchp_i2s_mcc_dt_ids);
#पूर्ण_अगर

अटल पूर्णांक mchp_i2s_mcc_soc_data_parse(काष्ठा platक्रमm_device *pdev,
				       काष्ठा mchp_i2s_mcc_dev *dev)
अणु
	पूर्णांक err;

	अगर (!dev->soc) अणु
		dev_err(&pdev->dev, "failed to get soc data\n");
		वापस -ENODEV;
	पूर्ण

	अगर (dev->soc->data_pin_pair_num == 1)
		वापस 0;

	err = of_property_पढ़ो_u8(pdev->dev.of_node, "microchip,tdm-data-pair",
				  &dev->tdm_data_pair);
	अगर (err < 0 && err != -EINVAL) अणु
		dev_err(&pdev->dev,
			"bad property data for 'microchip,tdm-data-pair': %d",
			err);
		वापस err;
	पूर्ण
	अगर (err == -EINVAL) अणु
		dev_info(&pdev->dev,
			 "'microchip,tdm-data-pair' not found; assuming DIN/DOUT 0 for TDM\n");
		dev->tdm_data_pair = 0;
	पूर्ण अन्यथा अणु
		अगर (dev->tdm_data_pair > dev->soc->data_pin_pair_num - 1) अणु
			dev_err(&pdev->dev,
				"invalid value for 'microchip,tdm-data-pair': %d\n",
				dev->tdm_data_pair);
			वापस -EINVAL;
		पूर्ण
		dev_dbg(&pdev->dev, "TMD format on DIN/DOUT %d pins\n",
			dev->tdm_data_pair);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mchp_i2s_mcc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mchp_i2s_mcc_dev *dev;
	काष्ठा resource *mem;
	काष्ठा regmap *regmap;
	व्योम __iomem *base;
	u32 version;
	पूर्णांक irq;
	पूर्णांक err;

	dev = devm_kzalloc(&pdev->dev, माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(&pdev->dev, mem);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	regmap = devm_regmap_init_mmio(&pdev->dev, base,
				       &mchp_i2s_mcc_regmap_config);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	err = devm_request_irq(&pdev->dev, irq, mchp_i2s_mcc_पूर्णांकerrupt, 0,
			       dev_name(&pdev->dev), dev);
	अगर (err)
		वापस err;

	dev->pclk = devm_clk_get(&pdev->dev, "pclk");
	अगर (IS_ERR(dev->pclk)) अणु
		err = PTR_ERR(dev->pclk);
		dev_err(&pdev->dev,
			"failed to get the peripheral clock: %d\n", err);
		वापस err;
	पूर्ण

	/* Get the optional generated घड़ी */
	dev->gclk = devm_clk_get(&pdev->dev, "gclk");
	अगर (IS_ERR(dev->gclk)) अणु
		अगर (PTR_ERR(dev->gclk) == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;
		dev_warn(&pdev->dev,
			 "generated clock not found: %d\n", err);
		dev->gclk = शून्य;
	पूर्ण

	dev->soc = of_device_get_match_data(&pdev->dev);
	err = mchp_i2s_mcc_soc_data_parse(pdev, dev);
	अगर (err < 0)
		वापस err;

	dev->dev = &pdev->dev;
	dev->regmap = regmap;
	platक्रमm_set_drvdata(pdev, dev);

	err = clk_prepare_enable(dev->pclk);
	अगर (err) अणु
		dev_err(&pdev->dev,
			"failed to enable the peripheral clock: %d\n", err);
		वापस err;
	पूर्ण

	err = devm_snd_soc_रेजिस्टर_component(&pdev->dev,
					      &mchp_i2s_mcc_component,
					      &mchp_i2s_mcc_dai, 1);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to register DAI: %d\n", err);
		clk_disable_unprepare(dev->pclk);
		वापस err;
	पूर्ण

	dev->playback.addr	= (dma_addr_t)mem->start + MCHP_I2SMCC_THR;
	dev->capture.addr	= (dma_addr_t)mem->start + MCHP_I2SMCC_RHR;

	err = devm_snd_dmaengine_pcm_रेजिस्टर(&pdev->dev, शून्य, 0);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to register PCM: %d\n", err);
		clk_disable_unprepare(dev->pclk);
		वापस err;
	पूर्ण

	/* Get IP version. */
	regmap_पढ़ो(dev->regmap, MCHP_I2SMCC_VERSION, &version);
	dev_info(&pdev->dev, "hw version: %#lx\n",
		 version & MCHP_I2SMCC_VERSION_MASK);

	वापस 0;
पूर्ण

अटल पूर्णांक mchp_i2s_mcc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mchp_i2s_mcc_dev *dev = platक्रमm_get_drvdata(pdev);

	clk_disable_unprepare(dev->pclk);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver mchp_i2s_mcc_driver = अणु
	.driver		= अणु
		.name	= "mchp_i2s_mcc",
		.of_match_table	= of_match_ptr(mchp_i2s_mcc_dt_ids),
	पूर्ण,
	.probe		= mchp_i2s_mcc_probe,
	.हटाओ		= mchp_i2s_mcc_हटाओ,
पूर्ण;
module_platक्रमm_driver(mchp_i2s_mcc_driver);

MODULE_DESCRIPTION("Microchip I2S Multi-Channel Controller driver");
MODULE_AUTHOR("Codrin Ciubotariu <codrin.ciubotariu@microchip.com>");
MODULE_LICENSE("GPL v2");
