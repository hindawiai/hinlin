<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ALSA SoC I2S Audio Layer क्रम Broadcom BCM2835 SoC
 *
 * Author:	Florian Meier <florian.meier@koalo.de>
 *		Copyright 2013
 *
 * Based on
 *	Raspberry Pi PCM I2S ALSA Driver
 *	Copyright (c) by Phil Poole 2013
 *
 *	ALSA SoC I2S (McBSP) Audio Layer क्रम TI DAVINCI processor
 *      Vladimir Barinov, <vbarinov@embeddedalley.com>
 *	Copyright (C) 2007 MontaVista Software, Inc., <source@mvista.com>
 *
 *	OMAP ALSA SoC DAI driver using McBSP port
 *	Copyright (C) 2008 Nokia Corporation
 *	Contact: Jarkko Nikula <jarkko.nikula@biपंचांगer.com>
 *		 Peter Ujfalusi <peter.ujfalusi@ti.com>
 *
 *	Freescale SSI ALSA SoC Digital Audio Interface (DAI) driver
 *	Author: Timur Tabi <timur@मुक्तscale.com>
 *	Copyright 2007-2010 Freescale Semiconductor, Inc.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/slab.h>

#समावेश <sound/core.h>
#समावेश <sound/dmaengine_pcm.h>
#समावेश <sound/initval.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>

/* I2S रेजिस्टरs */
#घोषणा BCM2835_I2S_CS_A_REG		0x00
#घोषणा BCM2835_I2S_FIFO_A_REG		0x04
#घोषणा BCM2835_I2S_MODE_A_REG		0x08
#घोषणा BCM2835_I2S_RXC_A_REG		0x0c
#घोषणा BCM2835_I2S_TXC_A_REG		0x10
#घोषणा BCM2835_I2S_DREQ_A_REG		0x14
#घोषणा BCM2835_I2S_INTEN_A_REG	0x18
#घोषणा BCM2835_I2S_INTSTC_A_REG	0x1c
#घोषणा BCM2835_I2S_GRAY_REG		0x20

/* I2S रेजिस्टर settings */
#घोषणा BCM2835_I2S_STBY		BIT(25)
#घोषणा BCM2835_I2S_SYNC		BIT(24)
#घोषणा BCM2835_I2S_RXSEX		BIT(23)
#घोषणा BCM2835_I2S_RXF		BIT(22)
#घोषणा BCM2835_I2S_TXE		BIT(21)
#घोषणा BCM2835_I2S_RXD		BIT(20)
#घोषणा BCM2835_I2S_TXD		BIT(19)
#घोषणा BCM2835_I2S_RXR		BIT(18)
#घोषणा BCM2835_I2S_TXW		BIT(17)
#घोषणा BCM2835_I2S_CS_RXERR		BIT(16)
#घोषणा BCM2835_I2S_CS_TXERR		BIT(15)
#घोषणा BCM2835_I2S_RXSYNC		BIT(14)
#घोषणा BCM2835_I2S_TXSYNC		BIT(13)
#घोषणा BCM2835_I2S_DMAEN		BIT(9)
#घोषणा BCM2835_I2S_RXTHR(v)		((v) << 7)
#घोषणा BCM2835_I2S_TXTHR(v)		((v) << 5)
#घोषणा BCM2835_I2S_RXCLR		BIT(4)
#घोषणा BCM2835_I2S_TXCLR		BIT(3)
#घोषणा BCM2835_I2S_TXON		BIT(2)
#घोषणा BCM2835_I2S_RXON		BIT(1)
#घोषणा BCM2835_I2S_EN			(1)

#घोषणा BCM2835_I2S_CLKDIS		BIT(28)
#घोषणा BCM2835_I2S_PDMN		BIT(27)
#घोषणा BCM2835_I2S_PDME		BIT(26)
#घोषणा BCM2835_I2S_FRXP		BIT(25)
#घोषणा BCM2835_I2S_FTXP		BIT(24)
#घोषणा BCM2835_I2S_CLKM		BIT(23)
#घोषणा BCM2835_I2S_CLKI		BIT(22)
#घोषणा BCM2835_I2S_FSM		BIT(21)
#घोषणा BCM2835_I2S_FSI		BIT(20)
#घोषणा BCM2835_I2S_FLEN(v)		((v) << 10)
#घोषणा BCM2835_I2S_FSLEN(v)		(v)

#घोषणा BCM2835_I2S_CHWEX		BIT(15)
#घोषणा BCM2835_I2S_CHEN		BIT(14)
#घोषणा BCM2835_I2S_CHPOS(v)		((v) << 4)
#घोषणा BCM2835_I2S_CHWID(v)		(v)
#घोषणा BCM2835_I2S_CH1(v)		((v) << 16)
#घोषणा BCM2835_I2S_CH2(v)		(v)
#घोषणा BCM2835_I2S_CH1_POS(v)		BCM2835_I2S_CH1(BCM2835_I2S_CHPOS(v))
#घोषणा BCM2835_I2S_CH2_POS(v)		BCM2835_I2S_CH2(BCM2835_I2S_CHPOS(v))

#घोषणा BCM2835_I2S_TX_PANIC(v)	((v) << 24)
#घोषणा BCM2835_I2S_RX_PANIC(v)	((v) << 16)
#घोषणा BCM2835_I2S_TX(v)		((v) << 8)
#घोषणा BCM2835_I2S_RX(v)		(v)

#घोषणा BCM2835_I2S_INT_RXERR		BIT(3)
#घोषणा BCM2835_I2S_INT_TXERR		BIT(2)
#घोषणा BCM2835_I2S_INT_RXR		BIT(1)
#घोषणा BCM2835_I2S_INT_TXW		BIT(0)

/* Frame length रेजिस्टर is 10 bit, maximum length 1024 */
#घोषणा BCM2835_I2S_MAX_FRAME_LENGTH	1024

/* General device काष्ठा */
काष्ठा bcm2835_i2s_dev अणु
	काष्ठा device				*dev;
	काष्ठा snd_dmaengine_dai_dma_data	dma_data[2];
	अचिन्हित पूर्णांक				fmt;
	अचिन्हित पूर्णांक				tdm_slots;
	अचिन्हित पूर्णांक				rx_mask;
	अचिन्हित पूर्णांक				tx_mask;
	अचिन्हित पूर्णांक				slot_width;
	अचिन्हित पूर्णांक				frame_length;

	काष्ठा regmap				*i2s_regmap;
	काष्ठा clk				*clk;
	bool					clk_prepared;
	पूर्णांक					clk_rate;
पूर्ण;

अटल व्योम bcm2835_i2s_start_घड़ी(काष्ठा bcm2835_i2s_dev *dev)
अणु
	अचिन्हित पूर्णांक master = dev->fmt & SND_SOC_DAIFMT_MASTER_MASK;

	अगर (dev->clk_prepared)
		वापस;

	चयन (master) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
	हाल SND_SOC_DAIFMT_CBS_CFM:
		clk_prepare_enable(dev->clk);
		dev->clk_prepared = true;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम bcm2835_i2s_stop_घड़ी(काष्ठा bcm2835_i2s_dev *dev)
अणु
	अगर (dev->clk_prepared)
		clk_disable_unprepare(dev->clk);
	dev->clk_prepared = false;
पूर्ण

अटल व्योम bcm2835_i2s_clear_fअगरos(काष्ठा bcm2835_i2s_dev *dev,
				    bool tx, bool rx)
अणु
	पूर्णांक समयout = 1000;
	uपूर्णांक32_t syncval;
	uपूर्णांक32_t csreg;
	uपूर्णांक32_t i2s_active_state;
	bool clk_was_prepared;
	uपूर्णांक32_t off;
	uपूर्णांक32_t clr;

	off =  tx ? BCM2835_I2S_TXON : 0;
	off |= rx ? BCM2835_I2S_RXON : 0;

	clr =  tx ? BCM2835_I2S_TXCLR : 0;
	clr |= rx ? BCM2835_I2S_RXCLR : 0;

	/* Backup the current state */
	regmap_पढ़ो(dev->i2s_regmap, BCM2835_I2S_CS_A_REG, &csreg);
	i2s_active_state = csreg & (BCM2835_I2S_RXON | BCM2835_I2S_TXON);

	/* Start घड़ी अगर not running */
	clk_was_prepared = dev->clk_prepared;
	अगर (!clk_was_prepared)
		bcm2835_i2s_start_घड़ी(dev);

	/* Stop I2S module */
	regmap_update_bits(dev->i2s_regmap, BCM2835_I2S_CS_A_REG, off, 0);

	/*
	 * Clear the FIFOs
	 * Requires at least 2 PCM घड़ी cycles to take effect
	 */
	regmap_update_bits(dev->i2s_regmap, BCM2835_I2S_CS_A_REG, clr, clr);

	/* Wait क्रम 2 PCM घड़ी cycles */

	/*
	 * Toggle the SYNC flag. After 2 PCM घड़ी cycles it can be पढ़ो back
	 * FIXME: This करोes not seem to work क्रम slave mode!
	 */
	regmap_पढ़ो(dev->i2s_regmap, BCM2835_I2S_CS_A_REG, &syncval);
	syncval &= BCM2835_I2S_SYNC;

	regmap_update_bits(dev->i2s_regmap, BCM2835_I2S_CS_A_REG,
			BCM2835_I2S_SYNC, ~syncval);

	/* Wait क्रम the SYNC flag changing it's state */
	जबतक (--समयout) अणु
		regmap_पढ़ो(dev->i2s_regmap, BCM2835_I2S_CS_A_REG, &csreg);
		अगर ((csreg & BCM2835_I2S_SYNC) != syncval)
			अवरोध;
	पूर्ण

	अगर (!समयout)
		dev_err(dev->dev, "I2S SYNC error!\n");

	/* Stop घड़ी अगर it was not running beक्रमe */
	अगर (!clk_was_prepared)
		bcm2835_i2s_stop_घड़ी(dev);

	/* Restore I2S state */
	regmap_update_bits(dev->i2s_regmap, BCM2835_I2S_CS_A_REG,
			BCM2835_I2S_RXON | BCM2835_I2S_TXON, i2s_active_state);
पूर्ण

अटल पूर्णांक bcm2835_i2s_set_dai_fmt(काष्ठा snd_soc_dai *dai,
				      अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा bcm2835_i2s_dev *dev = snd_soc_dai_get_drvdata(dai);
	dev->fmt = fmt;
	वापस 0;
पूर्ण

अटल पूर्णांक bcm2835_i2s_set_dai_bclk_ratio(काष्ठा snd_soc_dai *dai,
				      अचिन्हित पूर्णांक ratio)
अणु
	काष्ठा bcm2835_i2s_dev *dev = snd_soc_dai_get_drvdata(dai);

	अगर (!ratio) अणु
		dev->tdm_slots = 0;
		वापस 0;
	पूर्ण

	अगर (ratio > BCM2835_I2S_MAX_FRAME_LENGTH)
		वापस -EINVAL;

	dev->tdm_slots = 2;
	dev->rx_mask = 0x03;
	dev->tx_mask = 0x03;
	dev->slot_width = ratio / 2;
	dev->frame_length = ratio;

	वापस 0;
पूर्ण

अटल पूर्णांक bcm2835_i2s_set_dai_tdm_slot(काष्ठा snd_soc_dai *dai,
	अचिन्हित पूर्णांक tx_mask, अचिन्हित पूर्णांक rx_mask,
	पूर्णांक slots, पूर्णांक width)
अणु
	काष्ठा bcm2835_i2s_dev *dev = snd_soc_dai_get_drvdata(dai);

	अगर (slots) अणु
		अगर (slots < 0 || width < 0)
			वापस -EINVAL;

		/* Limit masks to available slots */
		rx_mask &= GENMASK(slots - 1, 0);
		tx_mask &= GENMASK(slots - 1, 0);

		/*
		 * The driver is limited to 2-channel setups.
		 * Check that exactly 2 bits are set in the masks.
		 */
		अगर (hweight_दीर्घ((अचिन्हित दीर्घ) rx_mask) != 2
		    || hweight_दीर्घ((अचिन्हित दीर्घ) tx_mask) != 2)
			वापस -EINVAL;

		अगर (slots * width > BCM2835_I2S_MAX_FRAME_LENGTH)
			वापस -EINVAL;
	पूर्ण

	dev->tdm_slots = slots;

	dev->rx_mask = rx_mask;
	dev->tx_mask = tx_mask;
	dev->slot_width = width;
	dev->frame_length = slots * width;

	वापस 0;
पूर्ण

/*
 * Convert logical slot number पूर्णांकo physical slot number.
 *
 * If odd_offset is 0 sequential number is identical to logical number.
 * This is used क्रम DSP modes with slot numbering 0 1 2 3 ...
 *
 * Otherwise odd_offset defines the physical offset क्रम odd numbered
 * slots. This is used क्रम I2S and left/right justअगरied modes to
 * translate from logical slot numbers 0 1 2 3 ... पूर्णांकo physical slot
 * numbers 0 2 ... 3 4 ...
 */
अटल पूर्णांक bcm2835_i2s_convert_slot(अचिन्हित पूर्णांक slot, अचिन्हित पूर्णांक odd_offset)
अणु
	अगर (!odd_offset)
		वापस slot;

	अगर (slot & 1)
		वापस (slot >> 1) + odd_offset;

	वापस slot >> 1;
पूर्ण

/*
 * Calculate channel position from mask and slot width.
 *
 * Mask must contain exactly 2 set bits.
 * Lowest set bit is channel 1 position, highest set bit channel 2.
 * The स्थिरant offset is added to both channel positions.
 *
 * If odd_offset is > 0 slot positions are translated to
 * I2S-style TDM slot numbering ( 0 2 ... 3 4 ...) with odd
 * logical slot numbers starting at physical slot odd_offset.
 */
अटल व्योम bcm2835_i2s_calc_channel_pos(
	अचिन्हित पूर्णांक *ch1_pos, अचिन्हित पूर्णांक *ch2_pos,
	अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक width,
	अचिन्हित पूर्णांक bit_offset, अचिन्हित पूर्णांक odd_offset)
अणु
	*ch1_pos = bcm2835_i2s_convert_slot((ffs(mask) - 1), odd_offset)
			* width + bit_offset;
	*ch2_pos = bcm2835_i2s_convert_slot((fls(mask) - 1), odd_offset)
			* width + bit_offset;
पूर्ण

अटल पूर्णांक bcm2835_i2s_hw_params(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *params,
				 काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा bcm2835_i2s_dev *dev = snd_soc_dai_get_drvdata(dai);
	अचिन्हित पूर्णांक data_length, data_delay, framesync_length;
	अचिन्हित पूर्णांक slots, slot_width, odd_slot_offset;
	पूर्णांक frame_length, bclk_rate;
	अचिन्हित पूर्णांक rx_mask, tx_mask;
	अचिन्हित पूर्णांक rx_ch1_pos, rx_ch2_pos, tx_ch1_pos, tx_ch2_pos;
	अचिन्हित पूर्णांक mode, क्रमmat;
	bool bit_घड़ी_master = false;
	bool frame_sync_master = false;
	bool frame_start_falling_edge = false;
	uपूर्णांक32_t csreg;
	पूर्णांक ret = 0;

	/*
	 * If a stream is alपढ़ोy enabled,
	 * the रेजिस्टरs are alपढ़ोy set properly.
	 */
	regmap_पढ़ो(dev->i2s_regmap, BCM2835_I2S_CS_A_REG, &csreg);

	अगर (csreg & (BCM2835_I2S_TXON | BCM2835_I2S_RXON))
		वापस 0;

	data_length = params_width(params);
	data_delay = 0;
	odd_slot_offset = 0;
	mode = 0;

	अगर (dev->tdm_slots) अणु
		slots = dev->tdm_slots;
		slot_width = dev->slot_width;
		frame_length = dev->frame_length;
		rx_mask = dev->rx_mask;
		tx_mask = dev->tx_mask;
		bclk_rate = dev->frame_length * params_rate(params);
	पूर्ण अन्यथा अणु
		slots = 2;
		slot_width = params_width(params);
		rx_mask = 0x03;
		tx_mask = 0x03;

		frame_length = snd_soc_params_to_frame_size(params);
		अगर (frame_length < 0)
			वापस frame_length;

		bclk_rate = snd_soc_params_to_bclk(params);
		अगर (bclk_rate < 0)
			वापस bclk_rate;
	पूर्ण

	/* Check अगर data fits पूर्णांकo slots */
	अगर (data_length > slot_width)
		वापस -EINVAL;

	/* Check अगर CPU is bit घड़ी master */
	चयन (dev->fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
	हाल SND_SOC_DAIFMT_CBS_CFM:
		bit_घड़ी_master = true;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFS:
	हाल SND_SOC_DAIFMT_CBM_CFM:
		bit_घड़ी_master = false;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Check अगर CPU is frame sync master */
	चयन (dev->fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
	हाल SND_SOC_DAIFMT_CBM_CFS:
		frame_sync_master = true;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFM:
	हाल SND_SOC_DAIFMT_CBM_CFM:
		frame_sync_master = false;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Clock should only be set up here अगर CPU is घड़ी master */
	अगर (bit_घड़ी_master &&
	    (!dev->clk_prepared || dev->clk_rate != bclk_rate)) अणु
		अगर (dev->clk_prepared)
			bcm2835_i2s_stop_घड़ी(dev);

		अगर (dev->clk_rate != bclk_rate) अणु
			ret = clk_set_rate(dev->clk, bclk_rate);
			अगर (ret)
				वापस ret;
			dev->clk_rate = bclk_rate;
		पूर्ण

		bcm2835_i2s_start_घड़ी(dev);
	पूर्ण

	/* Setup the frame क्रमmat */
	क्रमmat = BCM2835_I2S_CHEN;

	अगर (data_length >= 24)
		क्रमmat |= BCM2835_I2S_CHWEX;

	क्रमmat |= BCM2835_I2S_CHWID((data_length-8)&0xf);

	/* CH2 क्रमmat is the same as क्रम CH1 */
	क्रमmat = BCM2835_I2S_CH1(क्रमmat) | BCM2835_I2S_CH2(क्रमmat);

	चयन (dev->fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		/* I2S mode needs an even number of slots */
		अगर (slots & 1)
			वापस -EINVAL;

		/*
		 * Use I2S-style logical slot numbering: even slots
		 * are in first half of frame, odd slots in second half.
		 */
		odd_slot_offset = slots >> 1;

		/* MSB starts one cycle after frame start */
		data_delay = 1;

		/* Setup frame sync संकेत क्रम 50% duty cycle */
		framesync_length = frame_length / 2;
		frame_start_falling_edge = true;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		अगर (slots & 1)
			वापस -EINVAL;

		odd_slot_offset = slots >> 1;
		data_delay = 0;
		framesync_length = frame_length / 2;
		frame_start_falling_edge = false;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		अगर (slots & 1)
			वापस -EINVAL;

		/* Odd frame lengths aren't supported */
		अगर (frame_length & 1)
			वापस -EINVAL;

		odd_slot_offset = slots >> 1;
		data_delay = slot_width - data_length;
		framesync_length = frame_length / 2;
		frame_start_falling_edge = false;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		data_delay = 1;
		framesync_length = 1;
		frame_start_falling_edge = false;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		data_delay = 0;
		framesync_length = 1;
		frame_start_falling_edge = false;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	bcm2835_i2s_calc_channel_pos(&rx_ch1_pos, &rx_ch2_pos,
		rx_mask, slot_width, data_delay, odd_slot_offset);
	bcm2835_i2s_calc_channel_pos(&tx_ch1_pos, &tx_ch2_pos,
		tx_mask, slot_width, data_delay, odd_slot_offset);

	/*
	 * Transmitting data immediately after frame start, eg
	 * in left-justअगरied or DSP mode A, only works stable
	 * अगर bcm2835 is the frame घड़ी master.
	 */
	अगर ((!rx_ch1_pos || !tx_ch1_pos) && !frame_sync_master)
		dev_warn(dev->dev,
			"Unstable slave config detected, L/R may be swapped");

	/*
	 * Set क्रमmat क्रम both streams.
	 * We cannot set another frame length
	 * (and thereक्रमe word length) anyway,
	 * so the क्रमmat will be the same.
	 */
	regmap_ग_लिखो(dev->i2s_regmap, BCM2835_I2S_RXC_A_REG, 
		  क्रमmat
		| BCM2835_I2S_CH1_POS(rx_ch1_pos)
		| BCM2835_I2S_CH2_POS(rx_ch2_pos));
	regmap_ग_लिखो(dev->i2s_regmap, BCM2835_I2S_TXC_A_REG, 
		  क्रमmat
		| BCM2835_I2S_CH1_POS(tx_ch1_pos)
		| BCM2835_I2S_CH2_POS(tx_ch2_pos));

	/* Setup the I2S mode */

	अगर (data_length <= 16) अणु
		/*
		 * Use frame packed mode (2 channels per 32 bit word)
		 * We cannot set another frame length in the second stream
		 * (and thereक्रमe word length) anyway,
		 * so the क्रमmat will be the same.
		 */
		mode |= BCM2835_I2S_FTXP | BCM2835_I2S_FRXP;
	पूर्ण

	mode |= BCM2835_I2S_FLEN(frame_length - 1);
	mode |= BCM2835_I2S_FSLEN(framesync_length);

	/* CLKM selects bcm2835 घड़ी slave mode */
	अगर (!bit_घड़ी_master)
		mode |= BCM2835_I2S_CLKM;

	/* FSM selects bcm2835 frame sync slave mode */
	अगर (!frame_sync_master)
		mode |= BCM2835_I2S_FSM;

	/* CLKI selects normal घड़ीing mode, sampling on rising edge */
        चयन (dev->fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
	हाल SND_SOC_DAIFMT_NB_IF:
		mode |= BCM2835_I2S_CLKI;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
	हाल SND_SOC_DAIFMT_IB_IF:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* FSI selects frame start on falling edge */
	चयन (dev->fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
	हाल SND_SOC_DAIFMT_IB_NF:
		अगर (frame_start_falling_edge)
			mode |= BCM2835_I2S_FSI;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
	हाल SND_SOC_DAIFMT_IB_IF:
		अगर (!frame_start_falling_edge)
			mode |= BCM2835_I2S_FSI;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_ग_लिखो(dev->i2s_regmap, BCM2835_I2S_MODE_A_REG, mode);

	/* Setup the DMA parameters */
	regmap_update_bits(dev->i2s_regmap, BCM2835_I2S_CS_A_REG,
			BCM2835_I2S_RXTHR(1)
			| BCM2835_I2S_TXTHR(1)
			| BCM2835_I2S_DMAEN, 0xffffffff);

	regmap_update_bits(dev->i2s_regmap, BCM2835_I2S_DREQ_A_REG,
			  BCM2835_I2S_TX_PANIC(0x10)
			| BCM2835_I2S_RX_PANIC(0x30)
			| BCM2835_I2S_TX(0x30)
			| BCM2835_I2S_RX(0x20), 0xffffffff);

	/* Clear FIFOs */
	bcm2835_i2s_clear_fअगरos(dev, true, true);

	dev_dbg(dev->dev,
		"slots: %d width: %d rx mask: 0x%02x tx_mask: 0x%02x\n",
		slots, slot_width, rx_mask, tx_mask);

	dev_dbg(dev->dev, "frame len: %d sync len: %d data len: %d\n",
		frame_length, framesync_length, data_length);

	dev_dbg(dev->dev, "rx pos: %d,%d tx pos: %d,%d\n",
		rx_ch1_pos, rx_ch2_pos, tx_ch1_pos, tx_ch2_pos);

	dev_dbg(dev->dev, "sampling rate: %d bclk rate: %d\n",
		params_rate(params), bclk_rate);

	dev_dbg(dev->dev, "CLKM: %d CLKI: %d FSM: %d FSI: %d frame start: %s edge\n",
		!!(mode & BCM2835_I2S_CLKM),
		!!(mode & BCM2835_I2S_CLKI),
		!!(mode & BCM2835_I2S_FSM),
		!!(mode & BCM2835_I2S_FSI),
		(mode & BCM2835_I2S_FSI) ? "falling" : "rising");

	वापस ret;
पूर्ण

अटल पूर्णांक bcm2835_i2s_prepare(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा bcm2835_i2s_dev *dev = snd_soc_dai_get_drvdata(dai);
	uपूर्णांक32_t cs_reg;

	/*
	 * Clear both FIFOs अगर the one that should be started
	 * is not empty at the moment. This should only happen
	 * after overrun. Otherwise, hw_params would have cleared
	 * the FIFO.
	 */
	regmap_पढ़ो(dev->i2s_regmap, BCM2835_I2S_CS_A_REG, &cs_reg);

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK
			&& !(cs_reg & BCM2835_I2S_TXE))
		bcm2835_i2s_clear_fअगरos(dev, true, false);
	अन्यथा अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE
			&& (cs_reg & BCM2835_I2S_RXD))
		bcm2835_i2s_clear_fअगरos(dev, false, true);

	वापस 0;
पूर्ण

अटल व्योम bcm2835_i2s_stop(काष्ठा bcm2835_i2s_dev *dev,
		काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_soc_dai *dai)
अणु
	uपूर्णांक32_t mask;

	अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
		mask = BCM2835_I2S_RXON;
	अन्यथा
		mask = BCM2835_I2S_TXON;

	regmap_update_bits(dev->i2s_regmap,
			BCM2835_I2S_CS_A_REG, mask, 0);

	/* Stop also the घड़ी when not SND_SOC_DAIFMT_CONT */
	अगर (!snd_soc_dai_active(dai) && !(dev->fmt & SND_SOC_DAIFMT_CONT))
		bcm2835_i2s_stop_घड़ी(dev);
पूर्ण

अटल पूर्णांक bcm2835_i2s_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
			       काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा bcm2835_i2s_dev *dev = snd_soc_dai_get_drvdata(dai);
	uपूर्णांक32_t mask;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		bcm2835_i2s_start_घड़ी(dev);

		अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
			mask = BCM2835_I2S_RXON;
		अन्यथा
			mask = BCM2835_I2S_TXON;

		regmap_update_bits(dev->i2s_regmap,
				BCM2835_I2S_CS_A_REG, mask, mask);
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		bcm2835_i2s_stop(dev, substream, dai);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bcm2835_i2s_startup(काष्ठा snd_pcm_substream *substream,
			       काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा bcm2835_i2s_dev *dev = snd_soc_dai_get_drvdata(dai);

	अगर (snd_soc_dai_active(dai))
		वापस 0;

	/* Should this still be running stop it */
	bcm2835_i2s_stop_घड़ी(dev);

	/* Enable PCM block */
	regmap_update_bits(dev->i2s_regmap, BCM2835_I2S_CS_A_REG,
			BCM2835_I2S_EN, BCM2835_I2S_EN);

	/*
	 * Disable STBY.
	 * Requires at least 4 PCM घड़ी cycles to take effect.
	 */
	regmap_update_bits(dev->i2s_regmap, BCM2835_I2S_CS_A_REG,
			BCM2835_I2S_STBY, BCM2835_I2S_STBY);

	वापस 0;
पूर्ण

अटल व्योम bcm2835_i2s_shutकरोwn(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा bcm2835_i2s_dev *dev = snd_soc_dai_get_drvdata(dai);

	bcm2835_i2s_stop(dev, substream, dai);

	/* If both streams are stopped, disable module and घड़ी */
	अगर (snd_soc_dai_active(dai))
		वापस;

	/* Disable the module */
	regmap_update_bits(dev->i2s_regmap, BCM2835_I2S_CS_A_REG,
			BCM2835_I2S_EN, 0);

	/*
	 * Stopping घड़ी is necessary, because stop करोes
	 * not stop the घड़ी when SND_SOC_DAIFMT_CONT
	 */
	bcm2835_i2s_stop_घड़ी(dev);
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops bcm2835_i2s_dai_ops = अणु
	.startup	= bcm2835_i2s_startup,
	.shutकरोwn	= bcm2835_i2s_shutकरोwn,
	.prepare	= bcm2835_i2s_prepare,
	.trigger	= bcm2835_i2s_trigger,
	.hw_params	= bcm2835_i2s_hw_params,
	.set_fmt	= bcm2835_i2s_set_dai_fmt,
	.set_bclk_ratio	= bcm2835_i2s_set_dai_bclk_ratio,
	.set_tdm_slot	= bcm2835_i2s_set_dai_tdm_slot,
पूर्ण;

अटल पूर्णांक bcm2835_i2s_dai_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा bcm2835_i2s_dev *dev = snd_soc_dai_get_drvdata(dai);

	snd_soc_dai_init_dma_data(dai,
			&dev->dma_data[SNDRV_PCM_STREAM_PLAYBACK],
			&dev->dma_data[SNDRV_PCM_STREAM_CAPTURE]);

	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_dai_driver bcm2835_i2s_dai = अणु
	.name	= "bcm2835-i2s",
	.probe	= bcm2835_i2s_dai_probe,
	.playback = अणु
		.channels_min = 2,
		.channels_max = 2,
		.rates =	SNDRV_PCM_RATE_CONTINUOUS,
		.rate_min =	8000,
		.rate_max =	384000,
		.क्रमmats =	SNDRV_PCM_FMTBIT_S16_LE
				| SNDRV_PCM_FMTBIT_S24_LE
				| SNDRV_PCM_FMTBIT_S32_LE
		पूर्ण,
	.capture = अणु
		.channels_min = 2,
		.channels_max = 2,
		.rates =	SNDRV_PCM_RATE_CONTINUOUS,
		.rate_min =	8000,
		.rate_max =	384000,
		.क्रमmats =	SNDRV_PCM_FMTBIT_S16_LE
				| SNDRV_PCM_FMTBIT_S24_LE
				| SNDRV_PCM_FMTBIT_S32_LE
		पूर्ण,
	.ops = &bcm2835_i2s_dai_ops,
	.symmetric_rate = 1,
	.symmetric_sample_bits = 1,
पूर्ण;

अटल bool bcm2835_i2s_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल BCM2835_I2S_CS_A_REG:
	हाल BCM2835_I2S_FIFO_A_REG:
	हाल BCM2835_I2S_INTSTC_A_REG:
	हाल BCM2835_I2S_GRAY_REG:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool bcm2835_i2s_precious_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल BCM2835_I2S_FIFO_A_REG:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config bcm2835_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.max_रेजिस्टर = BCM2835_I2S_GRAY_REG,
	.precious_reg = bcm2835_i2s_precious_reg,
	.अस्थिर_reg = bcm2835_i2s_अस्थिर_reg,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver bcm2835_i2s_component = अणु
	.name		= "bcm2835-i2s-comp",
पूर्ण;

अटल पूर्णांक bcm2835_i2s_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bcm2835_i2s_dev *dev;
	पूर्णांक ret;
	व्योम __iomem *base;
	स्थिर __be32 *addr;
	dma_addr_t dma_base;

	dev = devm_kzalloc(&pdev->dev, माप(*dev),
			   GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

	/* get the घड़ी */
	dev->clk_prepared = false;
	dev->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(dev->clk)) अणु
		ret = PTR_ERR(dev->clk);
		अगर (ret == -EPROBE_DEFER)
			dev_dbg(&pdev->dev, "could not get clk: %d\n", ret);
		अन्यथा
			dev_err(&pdev->dev, "could not get clk: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Request ioarea */
	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	dev->i2s_regmap = devm_regmap_init_mmio(&pdev->dev, base,
				&bcm2835_regmap_config);
	अगर (IS_ERR(dev->i2s_regmap))
		वापस PTR_ERR(dev->i2s_regmap);

	/* Set the DMA address - we have to parse DT ourselves */
	addr = of_get_address(pdev->dev.of_node, 0, शून्य, शून्य);
	अगर (!addr) अणु
		dev_err(&pdev->dev, "could not get DMA-register address\n");
		वापस -EINVAL;
	पूर्ण
	dma_base = be32_to_cpup(addr);

	dev->dma_data[SNDRV_PCM_STREAM_PLAYBACK].addr =
		dma_base + BCM2835_I2S_FIFO_A_REG;

	dev->dma_data[SNDRV_PCM_STREAM_CAPTURE].addr =
		dma_base + BCM2835_I2S_FIFO_A_REG;

	/* Set the bus width */
	dev->dma_data[SNDRV_PCM_STREAM_PLAYBACK].addr_width =
		DMA_SLAVE_BUSWIDTH_4_BYTES;
	dev->dma_data[SNDRV_PCM_STREAM_CAPTURE].addr_width =
		DMA_SLAVE_BUSWIDTH_4_BYTES;

	/* Set burst */
	dev->dma_data[SNDRV_PCM_STREAM_PLAYBACK].maxburst = 2;
	dev->dma_data[SNDRV_PCM_STREAM_CAPTURE].maxburst = 2;

	/*
	 * Set the PACK flag to enable S16_LE support (2 S16_LE values
	 * packed पूर्णांकo 32-bit transfers).
	 */
	dev->dma_data[SNDRV_PCM_STREAM_PLAYBACK].flags =
		SND_DMAENGINE_PCM_DAI_FLAG_PACK;
	dev->dma_data[SNDRV_PCM_STREAM_CAPTURE].flags =
		SND_DMAENGINE_PCM_DAI_FLAG_PACK;

	/* Store the pdev */
	dev->dev = &pdev->dev;
	dev_set_drvdata(&pdev->dev, dev);

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev,
			&bcm2835_i2s_component, &bcm2835_i2s_dai, 1);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Could not register DAI: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = devm_snd_dmaengine_pcm_रेजिस्टर(&pdev->dev, शून्य, 0);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Could not register PCM: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id bcm2835_i2s_of_match[] = अणु
	अणु .compatible = "brcm,bcm2835-i2s", पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, bcm2835_i2s_of_match);

अटल काष्ठा platक्रमm_driver bcm2835_i2s_driver = अणु
	.probe		= bcm2835_i2s_probe,
	.driver		= अणु
		.name	= "bcm2835-i2s",
		.of_match_table = bcm2835_i2s_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(bcm2835_i2s_driver);

MODULE_ALIAS("platform:bcm2835-i2s");
MODULE_DESCRIPTION("BCM2835 I2S interface");
MODULE_AUTHOR("Florian Meier <florian.meier@koalo.de>");
MODULE_LICENSE("GPL v2");
