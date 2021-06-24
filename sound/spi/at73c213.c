<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम AT73C213 16-bit stereo DAC connected to Aपंचांगel SSC
 *
 * Copyright (C) 2006-2007 Aपंचांगel Norway
 */

/*#घोषणा DEBUG*/

#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>

#समावेश <sound/initval.h>
#समावेश <sound/control.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>

#समावेश <linux/aपंचांगel-ssc.h>

#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/at73c213.h>

#समावेश "at73c213.h"

#घोषणा BITRATE_MIN	 8000 /* Hardware limit? */
#घोषणा BITRATE_TARGET	CONFIG_SND_AT73C213_TARGET_BITRATE
#घोषणा BITRATE_MAX	50000 /* Hardware limit. */

/* Initial (hardware reset) AT73C213 रेजिस्टर values. */
अटल स्थिर u8 snd_at73c213_original_image[18] =
अणु
	0x00,	/* 00 - CTRL    */
	0x05,	/* 01 - LLIG    */
	0x05,	/* 02 - RLIG    */
	0x08,	/* 03 - LPMG    */
	0x08,	/* 04 - RPMG    */
	0x00,	/* 05 - LLOG    */
	0x00,	/* 06 - RLOG    */
	0x22,	/* 07 - OLC     */
	0x09,	/* 08 - MC      */
	0x00,	/* 09 - CSFC    */
	0x00,	/* 0A - MISC    */
	0x00,	/* 0B -         */
	0x00,	/* 0C - PRECH   */
	0x05,	/* 0D - AUXG    */
	0x00,	/* 0E -         */
	0x00,	/* 0F -         */
	0x00,	/* 10 - RST     */
	0x00,	/* 11 - PA_CTRL */
पूर्ण;

काष्ठा snd_at73c213 अणु
	काष्ठा snd_card			*card;
	काष्ठा snd_pcm			*pcm;
	काष्ठा snd_pcm_substream	*substream;
	काष्ठा at73c213_board_info	*board;
	पूर्णांक				irq;
	पूर्णांक				period;
	अचिन्हित दीर्घ			bitrate;
	काष्ठा ssc_device		*ssc;
	काष्ठा spi_device		*spi;
	u8				spi_wbuffer[2];
	u8				spi_rbuffer[2];
	/* Image of the SPI रेजिस्टरs in AT73C213. */
	u8				reg_image[18];
	/* Protect SSC रेजिस्टरs against concurrent access. */
	spinlock_t			lock;
	/* Protect mixer रेजिस्टरs against concurrent access. */
	काष्ठा mutex			mixer_lock;
पूर्ण;

#घोषणा get_chip(card) ((काष्ठा snd_at73c213 *)card->निजी_data)

अटल पूर्णांक
snd_at73c213_ग_लिखो_reg(काष्ठा snd_at73c213 *chip, u8 reg, u8 val)
अणु
	काष्ठा spi_message msg;
	काष्ठा spi_transfer msg_xfer = अणु
		.len		= 2,
		.cs_change	= 0,
	पूर्ण;
	पूर्णांक retval;

	spi_message_init(&msg);

	chip->spi_wbuffer[0] = reg;
	chip->spi_wbuffer[1] = val;

	msg_xfer.tx_buf = chip->spi_wbuffer;
	msg_xfer.rx_buf = chip->spi_rbuffer;
	spi_message_add_tail(&msg_xfer, &msg);

	retval = spi_sync(chip->spi, &msg);

	अगर (!retval)
		chip->reg_image[reg] = val;

	वापस retval;
पूर्ण

अटल काष्ठा snd_pcm_hardware snd_at73c213_playback_hw = अणु
	.info		= SNDRV_PCM_INFO_INTERLEAVED |
			  SNDRV_PCM_INFO_BLOCK_TRANSFER,
	.क्रमmats	= SNDRV_PCM_FMTBIT_S16_BE,
	.rates		= SNDRV_PCM_RATE_CONTINUOUS,
	.rate_min	= 8000,  /* Replaced by chip->bitrate later. */
	.rate_max	= 50000, /* Replaced by chip->bitrate later. */
	.channels_min	= 1,
	.channels_max	= 2,
	.buffer_bytes_max = 64 * 1024 - 1,
	.period_bytes_min = 512,
	.period_bytes_max = 64 * 1024 - 1,
	.periods_min	= 4,
	.periods_max	= 1024,
पूर्ण;

/*
 * Calculate and set bitrate and भागisions.
 */
अटल पूर्णांक snd_at73c213_set_bitrate(काष्ठा snd_at73c213 *chip)
अणु
	अचिन्हित दीर्घ ssc_rate = clk_get_rate(chip->ssc->clk);
	अचिन्हित दीर्घ dac_rate_new, ssc_भाग;
	पूर्णांक status;
	अचिन्हित दीर्घ ssc_भाग_max, ssc_भाग_min;
	पूर्णांक max_tries;

	/*
	 * We connect two घड़ीs here, picking भागisors so the I2S घड़ीs
	 * out data at the same rate the DAC घड़ीs it in ... and as बंद
	 * as practical to the desired target rate.
	 *
	 * The DAC master घड़ी (MCLK) is programmable, and is either 256
	 * or (not here) 384 बार the I2S output घड़ी (BCLK).
	 */

	/* SSC घड़ी / (bitrate * stereo * 16-bit). */
	ssc_भाग = ssc_rate / (BITRATE_TARGET * 2 * 16);
	ssc_भाग_min = ssc_rate / (BITRATE_MAX * 2 * 16);
	ssc_भाग_max = ssc_rate / (BITRATE_MIN * 2 * 16);
	max_tries = (ssc_भाग_max - ssc_भाग_min) / 2;

	अगर (max_tries < 1)
		max_tries = 1;

	/* ssc_भाग must be even. */
	ssc_भाग = (ssc_भाग + 1) & ~1UL;

	अगर ((ssc_rate / (ssc_भाग * 2 * 16)) < BITRATE_MIN) अणु
		ssc_भाग -= 2;
		अगर ((ssc_rate / (ssc_भाग * 2 * 16)) > BITRATE_MAX)
			वापस -ENXIO;
	पूर्ण

	/* Search क्रम a possible bitrate. */
	करो अणु
		/* SSC घड़ी / (ssc भागider * 16-bit * stereo). */
		अगर ((ssc_rate / (ssc_भाग * 2 * 16)) < BITRATE_MIN)
			वापस -ENXIO;

		/* 256 / (2 * 16) = 8 */
		dac_rate_new = 8 * (ssc_rate / ssc_भाग);

		status = clk_round_rate(chip->board->dac_clk, dac_rate_new);
		अगर (status <= 0)
			वापस status;

		/* Ignore dअगरference smaller than 256 Hz. */
		अगर ((status/256) == (dac_rate_new/256))
			जाओ set_rate;

		ssc_भाग += 2;
	पूर्ण जबतक (--max_tries);

	/* Not able to find a valid bitrate. */
	वापस -ENXIO;

set_rate:
	status = clk_set_rate(chip->board->dac_clk, status);
	अगर (status < 0)
		वापस status;

	/* Set भागider in SSC device. */
	ssc_ग_लिखोl(chip->ssc->regs, CMR, ssc_भाग/2);

	/* SSC घड़ी / (ssc भागider * 16-bit * stereo). */
	chip->bitrate = ssc_rate / (ssc_भाग * 16 * 2);

	dev_info(&chip->spi->dev,
			"at73c213: supported bitrate is %lu (%lu divider)\n",
			chip->bitrate, ssc_भाग);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_at73c213_pcm_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_at73c213 *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक err;

	/* ensure buffer_size is a multiple of period_size */
	err = snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय,
					SNDRV_PCM_HW_PARAM_PERIODS);
	अगर (err < 0)
		वापस err;
	snd_at73c213_playback_hw.rate_min = chip->bitrate;
	snd_at73c213_playback_hw.rate_max = chip->bitrate;
	runसमय->hw = snd_at73c213_playback_hw;
	chip->substream = substream;

	clk_enable(chip->ssc->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_at73c213_pcm_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_at73c213 *chip = snd_pcm_substream_chip(substream);
	chip->substream = शून्य;
	clk_disable(chip->ssc->clk);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_at73c213_pcm_hw_params(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा snd_at73c213 *chip = snd_pcm_substream_chip(substream);
	पूर्णांक channels = params_channels(hw_params);
	पूर्णांक val;

	val = ssc_पढ़ोl(chip->ssc->regs, TFMR);
	val = SSC_BFINS(TFMR_DATNB, channels - 1, val);
	ssc_ग_लिखोl(chip->ssc->regs, TFMR, val);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_at73c213_pcm_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_at73c213 *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक block_size;

	block_size = frames_to_bytes(runसमय, runसमय->period_size);

	chip->period = 0;

	ssc_ग_लिखोl(chip->ssc->regs, PDC_TPR,
			(दीर्घ)runसमय->dma_addr);
	ssc_ग_लिखोl(chip->ssc->regs, PDC_TCR,
			runसमय->period_size * runसमय->channels);
	ssc_ग_लिखोl(chip->ssc->regs, PDC_TNPR,
			(दीर्घ)runसमय->dma_addr + block_size);
	ssc_ग_लिखोl(chip->ssc->regs, PDC_TNCR,
			runसमय->period_size * runसमय->channels);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_at73c213_pcm_trigger(काष्ठा snd_pcm_substream *substream,
				   पूर्णांक cmd)
अणु
	काष्ठा snd_at73c213 *chip = snd_pcm_substream_chip(substream);
	पूर्णांक retval = 0;

	spin_lock(&chip->lock);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		ssc_ग_लिखोl(chip->ssc->regs, IER, SSC_BIT(IER_ENDTX));
		ssc_ग_लिखोl(chip->ssc->regs, PDC_PTCR, SSC_BIT(PDC_PTCR_TXTEN));
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		ssc_ग_लिखोl(chip->ssc->regs, PDC_PTCR, SSC_BIT(PDC_PTCR_TXTDIS));
		ssc_ग_लिखोl(chip->ssc->regs, IDR, SSC_BIT(IDR_ENDTX));
		अवरोध;
	शेष:
		dev_dbg(&chip->spi->dev, "spurious command %x\n", cmd);
		retval = -EINVAL;
		अवरोध;
	पूर्ण

	spin_unlock(&chip->lock);

	वापस retval;
पूर्ण

अटल snd_pcm_uframes_t
snd_at73c213_pcm_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_at73c213 *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	snd_pcm_uframes_t pos;
	अचिन्हित दीर्घ bytes;

	bytes = ssc_पढ़ोl(chip->ssc->regs, PDC_TPR)
		- (अचिन्हित दीर्घ)runसमय->dma_addr;

	pos = bytes_to_frames(runसमय, bytes);
	अगर (pos >= runसमय->buffer_size)
		pos -= runसमय->buffer_size;

	वापस pos;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops at73c213_playback_ops = अणु
	.खोलो		= snd_at73c213_pcm_खोलो,
	.बंद		= snd_at73c213_pcm_बंद,
	.hw_params	= snd_at73c213_pcm_hw_params,
	.prepare	= snd_at73c213_pcm_prepare,
	.trigger	= snd_at73c213_pcm_trigger,
	.poपूर्णांकer	= snd_at73c213_pcm_poपूर्णांकer,
पूर्ण;

अटल पूर्णांक snd_at73c213_pcm_new(काष्ठा snd_at73c213 *chip, पूर्णांक device)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक retval;

	retval = snd_pcm_new(chip->card, chip->card->लघुname,
			device, 1, 0, &pcm);
	अगर (retval < 0)
		जाओ out;

	pcm->निजी_data = chip;
	pcm->info_flags = SNDRV_PCM_INFO_BLOCK_TRANSFER;
	म_नकल(pcm->name, "at73c213");
	chip->pcm = pcm;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &at73c213_playback_ops);

	snd_pcm_set_managed_buffer_all(chip->pcm,
			SNDRV_DMA_TYPE_DEV, &chip->ssc->pdev->dev,
			64 * 1024, 64 * 1024);
out:
	वापस retval;
पूर्ण

अटल irqवापस_t snd_at73c213_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा snd_at73c213 *chip = dev_id;
	काष्ठा snd_pcm_runसमय *runसमय = chip->substream->runसमय;
	u32 status;
	पूर्णांक offset;
	पूर्णांक block_size;
	पूर्णांक next_period;
	पूर्णांक retval = IRQ_NONE;

	spin_lock(&chip->lock);

	block_size = frames_to_bytes(runसमय, runसमय->period_size);
	status = ssc_पढ़ोl(chip->ssc->regs, IMR);

	अगर (status & SSC_BIT(IMR_ENDTX)) अणु
		chip->period++;
		अगर (chip->period == runसमय->periods)
			chip->period = 0;
		next_period = chip->period + 1;
		अगर (next_period == runसमय->periods)
			next_period = 0;

		offset = block_size * next_period;

		ssc_ग_लिखोl(chip->ssc->regs, PDC_TNPR,
				(दीर्घ)runसमय->dma_addr + offset);
		ssc_ग_लिखोl(chip->ssc->regs, PDC_TNCR,
				runसमय->period_size * runसमय->channels);
		retval = IRQ_HANDLED;
	पूर्ण

	ssc_पढ़ोl(chip->ssc->regs, IMR);
	spin_unlock(&chip->lock);

	अगर (status & SSC_BIT(IMR_ENDTX))
		snd_pcm_period_elapsed(chip->substream);

	वापस retval;
पूर्ण

/*
 * Mixer functions.
 */
अटल पूर्णांक snd_at73c213_mono_get(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_at73c213 *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक reg = kcontrol->निजी_value & 0xff;
	पूर्णांक shअगरt = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक mask = (kcontrol->निजी_value >> 16) & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 24) & 0xff;

	mutex_lock(&chip->mixer_lock);

	ucontrol->value.पूर्णांकeger.value[0] =
		(chip->reg_image[reg] >> shअगरt) & mask;

	अगर (invert)
		ucontrol->value.पूर्णांकeger.value[0] =
			mask - ucontrol->value.पूर्णांकeger.value[0];

	mutex_unlock(&chip->mixer_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_at73c213_mono_put(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_at73c213 *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक reg = kcontrol->निजी_value & 0xff;
	पूर्णांक shअगरt = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक mask = (kcontrol->निजी_value >> 16) & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 24) & 0xff;
	पूर्णांक change, retval;
	अचिन्हित लघु val;

	val = (ucontrol->value.पूर्णांकeger.value[0] & mask);
	अगर (invert)
		val = mask - val;
	val <<= shअगरt;

	mutex_lock(&chip->mixer_lock);

	val = (chip->reg_image[reg] & ~(mask << shअगरt)) | val;
	change = val != chip->reg_image[reg];
	retval = snd_at73c213_ग_लिखो_reg(chip, reg, val);

	mutex_unlock(&chip->mixer_lock);

	अगर (retval)
		वापस retval;

	वापस change;
पूर्ण

अटल पूर्णांक snd_at73c213_stereo_info(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_info *uinfo)
अणु
	पूर्णांक mask = (kcontrol->निजी_value >> 24) & 0xff;

	अगर (mask == 1)
		uinfo->type = SNDRV_CTL_ELEM_TYPE_BOOLEAN;
	अन्यथा
		uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;

	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = mask;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_at73c213_stereo_get(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_at73c213 *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक left_reg = kcontrol->निजी_value & 0xff;
	पूर्णांक right_reg = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक shअगरt_left = (kcontrol->निजी_value >> 16) & 0x07;
	पूर्णांक shअगरt_right = (kcontrol->निजी_value >> 19) & 0x07;
	पूर्णांक mask = (kcontrol->निजी_value >> 24) & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 22) & 1;

	mutex_lock(&chip->mixer_lock);

	ucontrol->value.पूर्णांकeger.value[0] =
		(chip->reg_image[left_reg] >> shअगरt_left) & mask;
	ucontrol->value.पूर्णांकeger.value[1] =
		(chip->reg_image[right_reg] >> shअगरt_right) & mask;

	अगर (invert) अणु
		ucontrol->value.पूर्णांकeger.value[0] =
			mask - ucontrol->value.पूर्णांकeger.value[0];
		ucontrol->value.पूर्णांकeger.value[1] =
			mask - ucontrol->value.पूर्णांकeger.value[1];
	पूर्ण

	mutex_unlock(&chip->mixer_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_at73c213_stereo_put(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_at73c213 *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक left_reg = kcontrol->निजी_value & 0xff;
	पूर्णांक right_reg = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक shअगरt_left = (kcontrol->निजी_value >> 16) & 0x07;
	पूर्णांक shअगरt_right = (kcontrol->निजी_value >> 19) & 0x07;
	पूर्णांक mask = (kcontrol->निजी_value >> 24) & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 22) & 1;
	पूर्णांक change, retval;
	अचिन्हित लघु val1, val2;

	val1 = ucontrol->value.पूर्णांकeger.value[0] & mask;
	val2 = ucontrol->value.पूर्णांकeger.value[1] & mask;
	अगर (invert) अणु
		val1 = mask - val1;
		val2 = mask - val2;
	पूर्ण
	val1 <<= shअगरt_left;
	val2 <<= shअगरt_right;

	mutex_lock(&chip->mixer_lock);

	val1 = (chip->reg_image[left_reg] & ~(mask << shअगरt_left)) | val1;
	val2 = (chip->reg_image[right_reg] & ~(mask << shअगरt_right)) | val2;
	change = val1 != chip->reg_image[left_reg]
		|| val2 != chip->reg_image[right_reg];
	retval = snd_at73c213_ग_लिखो_reg(chip, left_reg, val1);
	अगर (retval) अणु
		mutex_unlock(&chip->mixer_lock);
		जाओ out;
	पूर्ण
	retval = snd_at73c213_ग_लिखो_reg(chip, right_reg, val2);
	अगर (retval) अणु
		mutex_unlock(&chip->mixer_lock);
		जाओ out;
	पूर्ण

	mutex_unlock(&chip->mixer_lock);

	वापस change;

out:
	वापस retval;
पूर्ण

#घोषणा snd_at73c213_mono_चयन_info	snd_ctl_boolean_mono_info

अटल पूर्णांक snd_at73c213_mono_चयन_get(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_at73c213 *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक reg = kcontrol->निजी_value & 0xff;
	पूर्णांक shअगरt = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 24) & 0xff;

	mutex_lock(&chip->mixer_lock);

	ucontrol->value.पूर्णांकeger.value[0] =
		(chip->reg_image[reg] >> shअगरt) & 0x01;

	अगर (invert)
		ucontrol->value.पूर्णांकeger.value[0] =
			0x01 - ucontrol->value.पूर्णांकeger.value[0];

	mutex_unlock(&chip->mixer_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_at73c213_mono_चयन_put(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_at73c213 *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक reg = kcontrol->निजी_value & 0xff;
	पूर्णांक shअगरt = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक mask = (kcontrol->निजी_value >> 16) & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 24) & 0xff;
	पूर्णांक change, retval;
	अचिन्हित लघु val;

	अगर (ucontrol->value.पूर्णांकeger.value[0])
		val = mask;
	अन्यथा
		val = 0;

	अगर (invert)
		val = mask - val;
	val <<= shअगरt;

	mutex_lock(&chip->mixer_lock);

	val |= (chip->reg_image[reg] & ~(mask << shअगरt));
	change = val != chip->reg_image[reg];

	retval = snd_at73c213_ग_लिखो_reg(chip, reg, val);

	mutex_unlock(&chip->mixer_lock);

	अगर (retval)
		वापस retval;

	वापस change;
पूर्ण

अटल पूर्णांक snd_at73c213_pa_volume_info(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = ((kcontrol->निजी_value >> 16) & 0xff) - 1;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_at73c213_line_capture_volume_info(
		काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	/* When inverted will give values 0x10001 => 0. */
	uinfo->value.पूर्णांकeger.min = 14;
	uinfo->value.पूर्णांकeger.max = 31;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_at73c213_aux_capture_volume_info(
		काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	/* When inverted will give values 0x10001 => 0. */
	uinfo->value.पूर्णांकeger.min = 14;
	uinfo->value.पूर्णांकeger.max = 31;

	वापस 0;
पूर्ण

#घोषणा AT73C213_MONO_SWITCH(xname, xindex, reg, shअगरt, mask, invert)	\
अणु									\
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,				\
	.name = xname,							\
	.index = xindex,						\
	.info = snd_at73c213_mono_चयन_info,				\
	.get = snd_at73c213_mono_चयन_get,				\
	.put = snd_at73c213_mono_चयन_put,				\
	.निजी_value = (reg | (shअगरt << 8) | (mask << 16) | (invert << 24)) \
पूर्ण

#घोषणा AT73C213_STEREO(xname, xindex, left_reg, right_reg, shअगरt_left, shअगरt_right, mask, invert) \
अणु									\
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,				\
	.name = xname,							\
	.index = xindex,						\
	.info = snd_at73c213_stereo_info,				\
	.get = snd_at73c213_stereo_get,					\
	.put = snd_at73c213_stereo_put,					\
	.निजी_value = (left_reg | (right_reg << 8)			\
			| (shअगरt_left << 16) | (shअगरt_right << 19)	\
			| (mask << 24) | (invert << 22))		\
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_at73c213_controls[] = अणु
AT73C213_STEREO("Master Playback Volume", 0, DAC_LMPG, DAC_RMPG, 0, 0, 0x1f, 1),
AT73C213_STEREO("Master Playback Switch", 0, DAC_LMPG, DAC_RMPG, 5, 5, 1, 1),
AT73C213_STEREO("PCM Playback Volume", 0, DAC_LLOG, DAC_RLOG, 0, 0, 0x1f, 1),
AT73C213_STEREO("PCM Playback Switch", 0, DAC_LLOG, DAC_RLOG, 5, 5, 1, 1),
AT73C213_MONO_SWITCH("Mono PA Playback Switch", 0, DAC_CTRL, DAC_CTRL_ONPADRV,
		     0x01, 0),
अणु
	.अगरace	= SNDRV_CTL_ELEM_IFACE_MIXER,
	.name	= "PA Playback Volume",
	.index	= 0,
	.info	= snd_at73c213_pa_volume_info,
	.get	= snd_at73c213_mono_get,
	.put	= snd_at73c213_mono_put,
	.निजी_value	= PA_CTRL | (PA_CTRL_APAGAIN << 8) | \
		(0x0f << 16) | (1 << 24),
पूर्ण,
AT73C213_MONO_SWITCH("PA High Gain Playback Switch", 0, PA_CTRL, PA_CTRL_APALP,
		     0x01, 1),
AT73C213_MONO_SWITCH("PA Playback Switch", 0, PA_CTRL, PA_CTRL_APAON, 0x01, 0),
अणु
	.अगरace	= SNDRV_CTL_ELEM_IFACE_MIXER,
	.name	= "Aux Capture Volume",
	.index	= 0,
	.info	= snd_at73c213_aux_capture_volume_info,
	.get	= snd_at73c213_mono_get,
	.put	= snd_at73c213_mono_put,
	.निजी_value	= DAC_AUXG | (0 << 8) | (0x1f << 16) | (1 << 24),
पूर्ण,
AT73C213_MONO_SWITCH("Aux Capture Switch", 0, DAC_CTRL, DAC_CTRL_ONAUXIN,
		     0x01, 0),
अणु
	.अगरace	= SNDRV_CTL_ELEM_IFACE_MIXER,
	.name	= "Line Capture Volume",
	.index	= 0,
	.info	= snd_at73c213_line_capture_volume_info,
	.get	= snd_at73c213_stereo_get,
	.put	= snd_at73c213_stereo_put,
	.निजी_value	= DAC_LLIG | (DAC_RLIG << 8) | (0 << 16) | (0 << 19)
		| (0x1f << 24) | (1 << 22),
पूर्ण,
AT73C213_MONO_SWITCH("Line Capture Switch", 0, DAC_CTRL, 0, 0x03, 0),
पूर्ण;

अटल पूर्णांक snd_at73c213_mixer(काष्ठा snd_at73c213 *chip)
अणु
	काष्ठा snd_card *card;
	पूर्णांक errval, idx;

	अगर (chip == शून्य || chip->pcm == शून्य)
		वापस -EINVAL;

	card = chip->card;

	म_नकल(card->mixername, chip->pcm->name);

	क्रम (idx = 0; idx < ARRAY_SIZE(snd_at73c213_controls); idx++) अणु
		errval = snd_ctl_add(card,
				snd_ctl_new1(&snd_at73c213_controls[idx],
					chip));
		अगर (errval < 0)
			जाओ cleanup;
	पूर्ण

	वापस 0;

cleanup:
	क्रम (idx = 1; idx < ARRAY_SIZE(snd_at73c213_controls) + 1; idx++) अणु
		काष्ठा snd_kcontrol *kctl;
		kctl = snd_ctl_find_numid(card, idx);
		अगर (kctl)
			snd_ctl_हटाओ(card, kctl);
	पूर्ण
	वापस errval;
पूर्ण

/*
 * Device functions
 */
अटल पूर्णांक snd_at73c213_ssc_init(काष्ठा snd_at73c213 *chip)
अणु
	/*
	 * Continuous घड़ी output.
	 * Starts on falling TF.
	 * Delay 1 cycle (1 bit).
	 * Periode is 16 bit (16 - 1).
	 */
	ssc_ग_लिखोl(chip->ssc->regs, TCMR,
			SSC_BF(TCMR_CKO, 1)
			| SSC_BF(TCMR_START, 4)
			| SSC_BF(TCMR_STTDLY, 1)
			| SSC_BF(TCMR_PERIOD, 16 - 1));
	/*
	 * Data length is 16 bit (16 - 1).
	 * Transmit MSB first.
	 * Transmit 2 words each transfer.
	 * Frame sync length is 16 bit (16 - 1).
	 * Frame starts on negative pulse.
	 */
	ssc_ग_लिखोl(chip->ssc->regs, TFMR,
			SSC_BF(TFMR_DATLEN, 16 - 1)
			| SSC_BIT(TFMR_MSBF)
			| SSC_BF(TFMR_DATNB, 1)
			| SSC_BF(TFMR_FSLEN, 16 - 1)
			| SSC_BF(TFMR_FSOS, 1));

	वापस 0;
पूर्ण

अटल पूर्णांक snd_at73c213_chip_init(काष्ठा snd_at73c213 *chip)
अणु
	पूर्णांक retval;
	अचिन्हित अक्षर dac_ctrl = 0;

	retval = snd_at73c213_set_bitrate(chip);
	अगर (retval)
		जाओ out;

	/* Enable DAC master घड़ी. */
	clk_enable(chip->board->dac_clk);

	/* Initialize at73c213 on SPI bus. */
	retval = snd_at73c213_ग_लिखो_reg(chip, DAC_RST, 0x04);
	अगर (retval)
		जाओ out_clk;
	msleep(1);
	retval = snd_at73c213_ग_लिखो_reg(chip, DAC_RST, 0x03);
	अगर (retval)
		जाओ out_clk;

	/* Preअक्षरge everything. */
	retval = snd_at73c213_ग_लिखो_reg(chip, DAC_PRECH, 0xff);
	अगर (retval)
		जाओ out_clk;
	retval = snd_at73c213_ग_लिखो_reg(chip, PA_CTRL, (1<<PA_CTRL_APAPRECH));
	अगर (retval)
		जाओ out_clk;
	retval = snd_at73c213_ग_लिखो_reg(chip, DAC_CTRL,
			(1<<DAC_CTRL_ONLNOL) | (1<<DAC_CTRL_ONLNOR));
	अगर (retval)
		जाओ out_clk;

	msleep(50);

	/* Stop preअक्षरging PA. */
	retval = snd_at73c213_ग_लिखो_reg(chip, PA_CTRL,
			(1<<PA_CTRL_APALP) | 0x0f);
	अगर (retval)
		जाओ out_clk;

	msleep(450);

	/* Stop preअक्षरging DAC, turn on master घातer. */
	retval = snd_at73c213_ग_लिखो_reg(chip, DAC_PRECH, (1<<DAC_PRECH_ONMSTR));
	अगर (retval)
		जाओ out_clk;

	msleep(1);

	/* Turn on DAC. */
	dac_ctrl = (1<<DAC_CTRL_ONDACL) | (1<<DAC_CTRL_ONDACR)
		| (1<<DAC_CTRL_ONLNOL) | (1<<DAC_CTRL_ONLNOR);

	retval = snd_at73c213_ग_लिखो_reg(chip, DAC_CTRL, dac_ctrl);
	अगर (retval)
		जाओ out_clk;

	/* Mute sound. */
	retval = snd_at73c213_ग_लिखो_reg(chip, DAC_LMPG, 0x3f);
	अगर (retval)
		जाओ out_clk;
	retval = snd_at73c213_ग_लिखो_reg(chip, DAC_RMPG, 0x3f);
	अगर (retval)
		जाओ out_clk;
	retval = snd_at73c213_ग_लिखो_reg(chip, DAC_LLOG, 0x3f);
	अगर (retval)
		जाओ out_clk;
	retval = snd_at73c213_ग_लिखो_reg(chip, DAC_RLOG, 0x3f);
	अगर (retval)
		जाओ out_clk;
	retval = snd_at73c213_ग_लिखो_reg(chip, DAC_LLIG, 0x11);
	अगर (retval)
		जाओ out_clk;
	retval = snd_at73c213_ग_लिखो_reg(chip, DAC_RLIG, 0x11);
	अगर (retval)
		जाओ out_clk;
	retval = snd_at73c213_ग_लिखो_reg(chip, DAC_AUXG, 0x11);
	अगर (retval)
		जाओ out_clk;

	/* Enable I2S device, i.e. घड़ी output. */
	ssc_ग_लिखोl(chip->ssc->regs, CR, SSC_BIT(CR_TXEN));

	जाओ out;

out_clk:
	clk_disable(chip->board->dac_clk);
out:
	वापस retval;
पूर्ण

अटल पूर्णांक snd_at73c213_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा snd_at73c213 *chip = device->device_data;

	ssc_ग_लिखोl(chip->ssc->regs, CR, SSC_BIT(CR_TXDIS));
	अगर (chip->irq >= 0) अणु
		मुक्त_irq(chip->irq, chip);
		chip->irq = -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_at73c213_dev_init(काष्ठा snd_card *card,
				 काष्ठा spi_device *spi)
अणु
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त	= snd_at73c213_dev_मुक्त,
	पूर्ण;
	काष्ठा snd_at73c213 *chip = get_chip(card);
	पूर्णांक irq, retval;

	irq = chip->ssc->irq;
	अगर (irq < 0)
		वापस irq;

	spin_lock_init(&chip->lock);
	mutex_init(&chip->mixer_lock);
	chip->card = card;
	chip->irq = -1;

	clk_enable(chip->ssc->clk);

	retval = request_irq(irq, snd_at73c213_पूर्णांकerrupt, 0, "at73c213", chip);
	अगर (retval) अणु
		dev_dbg(&chip->spi->dev, "unable to request irq %d\n", irq);
		जाओ out;
	पूर्ण
	chip->irq = irq;

	स_नकल(&chip->reg_image, &snd_at73c213_original_image,
			माप(snd_at73c213_original_image));

	retval = snd_at73c213_ssc_init(chip);
	अगर (retval)
		जाओ out_irq;

	retval = snd_at73c213_chip_init(chip);
	अगर (retval)
		जाओ out_irq;

	retval = snd_at73c213_pcm_new(chip, 0);
	अगर (retval)
		जाओ out_irq;

	retval = snd_device_new(card, SNDRV_DEV_LOWLEVEL, chip, &ops);
	अगर (retval)
		जाओ out_irq;

	retval = snd_at73c213_mixer(chip);
	अगर (retval)
		जाओ out_snd_dev;

	जाओ out;

out_snd_dev:
	snd_device_मुक्त(card, chip);
out_irq:
	मुक्त_irq(chip->irq, chip);
	chip->irq = -1;
out:
	clk_disable(chip->ssc->clk);

	वापस retval;
पूर्ण

अटल पूर्णांक snd_at73c213_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा snd_card			*card;
	काष्ठा snd_at73c213		*chip;
	काष्ठा at73c213_board_info	*board;
	पूर्णांक				retval;
	अक्षर				id[16];

	board = spi->dev.platक्रमm_data;
	अगर (!board) अणु
		dev_dbg(&spi->dev, "no platform_data\n");
		वापस -ENXIO;
	पूर्ण

	अगर (!board->dac_clk) अणु
		dev_dbg(&spi->dev, "no DAC clk\n");
		वापस -ENXIO;
	पूर्ण

	अगर (IS_ERR(board->dac_clk)) अणु
		dev_dbg(&spi->dev, "no DAC clk\n");
		वापस PTR_ERR(board->dac_clk);
	पूर्ण

	/* Allocate "card" using some unused identअगरiers. */
	snम_लिखो(id, माप id, "at73c213_%d", board->ssc_id);
	retval = snd_card_new(&spi->dev, -1, id, THIS_MODULE,
			      माप(काष्ठा snd_at73c213), &card);
	अगर (retval < 0)
		जाओ out;

	chip = card->निजी_data;
	chip->spi = spi;
	chip->board = board;

	chip->ssc = ssc_request(board->ssc_id);
	अगर (IS_ERR(chip->ssc)) अणु
		dev_dbg(&spi->dev, "could not get ssc%d device\n",
				board->ssc_id);
		retval = PTR_ERR(chip->ssc);
		जाओ out_card;
	पूर्ण

	retval = snd_at73c213_dev_init(card, spi);
	अगर (retval)
		जाओ out_ssc;

	म_नकल(card->driver, "at73c213");
	म_नकल(card->लघुname, board->लघुname);
	प्र_लिखो(card->दीर्घname, "%s on irq %d", card->लघुname, chip->irq);

	retval = snd_card_रेजिस्टर(card);
	अगर (retval)
		जाओ out_ssc;

	dev_set_drvdata(&spi->dev, card);

	जाओ out;

out_ssc:
	ssc_मुक्त(chip->ssc);
out_card:
	snd_card_मुक्त(card);
out:
	वापस retval;
पूर्ण

अटल पूर्णांक snd_at73c213_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(&spi->dev);
	काष्ठा snd_at73c213 *chip = card->निजी_data;
	पूर्णांक retval;

	/* Stop playback. */
	clk_enable(chip->ssc->clk);
	ssc_ग_लिखोl(chip->ssc->regs, CR, SSC_BIT(CR_TXDIS));
	clk_disable(chip->ssc->clk);

	/* Mute sound. */
	retval = snd_at73c213_ग_लिखो_reg(chip, DAC_LMPG, 0x3f);
	अगर (retval)
		जाओ out;
	retval = snd_at73c213_ग_लिखो_reg(chip, DAC_RMPG, 0x3f);
	अगर (retval)
		जाओ out;
	retval = snd_at73c213_ग_लिखो_reg(chip, DAC_LLOG, 0x3f);
	अगर (retval)
		जाओ out;
	retval = snd_at73c213_ग_लिखो_reg(chip, DAC_RLOG, 0x3f);
	अगर (retval)
		जाओ out;
	retval = snd_at73c213_ग_लिखो_reg(chip, DAC_LLIG, 0x11);
	अगर (retval)
		जाओ out;
	retval = snd_at73c213_ग_लिखो_reg(chip, DAC_RLIG, 0x11);
	अगर (retval)
		जाओ out;
	retval = snd_at73c213_ग_लिखो_reg(chip, DAC_AUXG, 0x11);
	अगर (retval)
		जाओ out;

	/* Turn off PA. */
	retval = snd_at73c213_ग_लिखो_reg(chip, PA_CTRL,
					chip->reg_image[PA_CTRL] | 0x0f);
	अगर (retval)
		जाओ out;
	msleep(10);
	retval = snd_at73c213_ग_लिखो_reg(chip, PA_CTRL,
					(1 << PA_CTRL_APALP) | 0x0f);
	अगर (retval)
		जाओ out;

	/* Turn off बाह्यal DAC. */
	retval = snd_at73c213_ग_लिखो_reg(chip, DAC_CTRL, 0x0c);
	अगर (retval)
		जाओ out;
	msleep(2);
	retval = snd_at73c213_ग_लिखो_reg(chip, DAC_CTRL, 0x00);
	अगर (retval)
		जाओ out;

	/* Turn off master घातer. */
	retval = snd_at73c213_ग_लिखो_reg(chip, DAC_PRECH, 0x00);
	अगर (retval)
		जाओ out;

out:
	/* Stop DAC master घड़ी. */
	clk_disable(chip->board->dac_clk);

	ssc_मुक्त(chip->ssc);
	snd_card_मुक्त(card);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP

अटल पूर्णांक snd_at73c213_suspend(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा snd_at73c213 *chip = card->निजी_data;

	ssc_ग_लिखोl(chip->ssc->regs, CR, SSC_BIT(CR_TXDIS));
	clk_disable(chip->ssc->clk);
	clk_disable(chip->board->dac_clk);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_at73c213_resume(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा snd_at73c213 *chip = card->निजी_data;

	clk_enable(chip->board->dac_clk);
	clk_enable(chip->ssc->clk);
	ssc_ग_लिखोl(chip->ssc->regs, CR, SSC_BIT(CR_TXEN));

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(at73c213_pm_ops, snd_at73c213_suspend,
		snd_at73c213_resume);
#घोषणा AT73C213_PM_OPS (&at73c213_pm_ops)

#अन्यथा
#घोषणा AT73C213_PM_OPS शून्य
#पूर्ण_अगर

अटल काष्ठा spi_driver at73c213_driver = अणु
	.driver		= अणु
		.name	= "at73c213",
		.pm	= AT73C213_PM_OPS,
	पूर्ण,
	.probe		= snd_at73c213_probe,
	.हटाओ		= snd_at73c213_हटाओ,
पूर्ण;

module_spi_driver(at73c213_driver);

MODULE_AUTHOR("Hans-Christian Egtvedt <egtvedt@samfundet.no>");
MODULE_DESCRIPTION("Sound driver for AT73C213 with Atmel SSC");
MODULE_LICENSE("GPL");
