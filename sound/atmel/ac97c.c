<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम Aपंचांगel AC97C
 *
 * Copyright (C) 2005-2009 Aपंचांगel Corporation
 */
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/device.h>
#समावेश <linux/aपंचांगel_pdc.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mutex.h>
#समावेश <linux/types.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>

#समावेश <sound/core.h>
#समावेश <sound/initval.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/ac97_codec.h>
#समावेश <sound/meदो_स्मृति.h>

#समावेश "ac97c.h"

/* Serialize access to खोलोed variable */
अटल DEFINE_MUTEX(खोलोed_mutex);

काष्ठा aपंचांगel_ac97c अणु
	काष्ठा clk			*pclk;
	काष्ठा platक्रमm_device		*pdev;

	काष्ठा snd_pcm_substream	*playback_substream;
	काष्ठा snd_pcm_substream	*capture_substream;
	काष्ठा snd_card			*card;
	काष्ठा snd_pcm			*pcm;
	काष्ठा snd_ac97			*ac97;
	काष्ठा snd_ac97_bus		*ac97_bus;

	u64				cur_क्रमmat;
	अचिन्हित पूर्णांक			cur_rate;
	पूर्णांक				playback_period, capture_period;
	/* Serialize access to खोलोed variable */
	spinlock_t			lock;
	व्योम __iomem			*regs;
	पूर्णांक				irq;
	पूर्णांक				खोलोed;
	काष्ठा gpio_desc		*reset_pin;
पूर्ण;

#घोषणा get_chip(card) ((काष्ठा aपंचांगel_ac97c *)(card)->निजी_data)

#घोषणा ac97c_ग_लिखोl(chip, reg, val)			\
	__raw_ग_लिखोl((val), (chip)->regs + AC97C_##reg)
#घोषणा ac97c_पढ़ोl(chip, reg)				\
	__raw_पढ़ोl((chip)->regs + AC97C_##reg)

अटल स्थिर काष्ठा snd_pcm_hardware aपंचांगel_ac97c_hw = अणु
	.info			= (SNDRV_PCM_INFO_MMAP
				  | SNDRV_PCM_INFO_MMAP_VALID
				  | SNDRV_PCM_INFO_INTERLEAVED
				  | SNDRV_PCM_INFO_BLOCK_TRANSFER
				  | SNDRV_PCM_INFO_JOINT_DUPLEX
				  | SNDRV_PCM_INFO_RESUME
				  | SNDRV_PCM_INFO_PAUSE),
	.क्रमmats		= (SNDRV_PCM_FMTBIT_S16_BE
				  | SNDRV_PCM_FMTBIT_S16_LE),
	.rates			= (SNDRV_PCM_RATE_CONTINUOUS),
	.rate_min		= 4000,
	.rate_max		= 48000,
	.channels_min		= 1,
	.channels_max		= 2,
	.buffer_bytes_max	= 2 * 2 * 64 * 2048,
	.period_bytes_min	= 4096,
	.period_bytes_max	= 4096,
	.periods_min		= 6,
	.periods_max		= 64,
पूर्ण;

अटल पूर्णांक aपंचांगel_ac97c_playback_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा aपंचांगel_ac97c *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	mutex_lock(&खोलोed_mutex);
	chip->खोलोed++;
	runसमय->hw = aपंचांगel_ac97c_hw;
	अगर (chip->cur_rate) अणु
		runसमय->hw.rate_min = chip->cur_rate;
		runसमय->hw.rate_max = chip->cur_rate;
	पूर्ण
	अगर (chip->cur_क्रमmat)
		runसमय->hw.क्रमmats = pcm_क्रमmat_to_bits(chip->cur_क्रमmat);
	mutex_unlock(&खोलोed_mutex);
	chip->playback_substream = substream;
	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_ac97c_capture_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा aपंचांगel_ac97c *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	mutex_lock(&खोलोed_mutex);
	chip->खोलोed++;
	runसमय->hw = aपंचांगel_ac97c_hw;
	अगर (chip->cur_rate) अणु
		runसमय->hw.rate_min = chip->cur_rate;
		runसमय->hw.rate_max = chip->cur_rate;
	पूर्ण
	अगर (chip->cur_क्रमmat)
		runसमय->hw.क्रमmats = pcm_क्रमmat_to_bits(chip->cur_क्रमmat);
	mutex_unlock(&खोलोed_mutex);
	chip->capture_substream = substream;
	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_ac97c_playback_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा aपंचांगel_ac97c *chip = snd_pcm_substream_chip(substream);

	mutex_lock(&खोलोed_mutex);
	chip->खोलोed--;
	अगर (!chip->खोलोed) अणु
		chip->cur_rate = 0;
		chip->cur_क्रमmat = 0;
	पूर्ण
	mutex_unlock(&खोलोed_mutex);

	chip->playback_substream = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_ac97c_capture_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा aपंचांगel_ac97c *chip = snd_pcm_substream_chip(substream);

	mutex_lock(&खोलोed_mutex);
	chip->खोलोed--;
	अगर (!chip->खोलोed) अणु
		chip->cur_rate = 0;
		chip->cur_क्रमmat = 0;
	पूर्ण
	mutex_unlock(&खोलोed_mutex);

	chip->capture_substream = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_ac97c_playback_hw_params(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा aपंचांगel_ac97c *chip = snd_pcm_substream_chip(substream);

	/* Set restrictions to params. */
	mutex_lock(&खोलोed_mutex);
	chip->cur_rate = params_rate(hw_params);
	chip->cur_क्रमmat = params_क्रमmat(hw_params);
	mutex_unlock(&खोलोed_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_ac97c_capture_hw_params(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा aपंचांगel_ac97c *chip = snd_pcm_substream_chip(substream);

	/* Set restrictions to params. */
	mutex_lock(&खोलोed_mutex);
	chip->cur_rate = params_rate(hw_params);
	chip->cur_क्रमmat = params_क्रमmat(hw_params);
	mutex_unlock(&खोलोed_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_ac97c_playback_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा aपंचांगel_ac97c *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक block_size = frames_to_bytes(runसमय, runसमय->period_size);
	अचिन्हित दीर्घ word = ac97c_पढ़ोl(chip, OCA);
	पूर्णांक retval;

	chip->playback_period = 0;
	word &= ~(AC97C_CH_MASK(PCM_LEFT) | AC97C_CH_MASK(PCM_RIGHT));

	/* assign channels to AC97C channel A */
	चयन (runसमय->channels) अणु
	हाल 1:
		word |= AC97C_CH_ASSIGN(PCM_LEFT, A);
		अवरोध;
	हाल 2:
		word |= AC97C_CH_ASSIGN(PCM_LEFT, A)
			| AC97C_CH_ASSIGN(PCM_RIGHT, A);
		अवरोध;
	शेष:
		/* TODO: support more than two channels */
		वापस -EINVAL;
	पूर्ण
	ac97c_ग_लिखोl(chip, OCA, word);

	/* configure sample क्रमmat and size */
	word = ac97c_पढ़ोl(chip, CAMR);
	अगर (chip->खोलोed <= 1)
		word = AC97C_CMR_DMAEN | AC97C_CMR_SIZE_16;
	अन्यथा
		word |= AC97C_CMR_DMAEN | AC97C_CMR_SIZE_16;

	चयन (runसमय->क्रमmat) अणु
	हाल SNDRV_PCM_FORMAT_S16_LE:
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S16_BE:
		word &= ~(AC97C_CMR_CEM_LITTLE);
		अवरोध;
	शेष:
		word = ac97c_पढ़ोl(chip, OCA);
		word &= ~(AC97C_CH_MASK(PCM_LEFT) | AC97C_CH_MASK(PCM_RIGHT));
		ac97c_ग_लिखोl(chip, OCA, word);
		वापस -EINVAL;
	पूर्ण

	/* Enable underrun पूर्णांकerrupt on channel A */
	word |= AC97C_CSR_UNRUN;

	ac97c_ग_लिखोl(chip, CAMR, word);

	/* Enable channel A event पूर्णांकerrupt */
	word = ac97c_पढ़ोl(chip, IMR);
	word |= AC97C_SR_CAEVT;
	ac97c_ग_लिखोl(chip, IER, word);

	/* set variable rate अगर needed */
	अगर (runसमय->rate != 48000) अणु
		word = ac97c_पढ़ोl(chip, MR);
		word |= AC97C_MR_VRA;
		ac97c_ग_लिखोl(chip, MR, word);
	पूर्ण अन्यथा अणु
		word = ac97c_पढ़ोl(chip, MR);
		word &= ~(AC97C_MR_VRA);
		ac97c_ग_लिखोl(chip, MR, word);
	पूर्ण

	retval = snd_ac97_set_rate(chip->ac97, AC97_PCM_FRONT_DAC_RATE,
			runसमय->rate);
	अगर (retval)
		dev_dbg(&chip->pdev->dev, "could not set rate %d Hz\n",
				runसमय->rate);

	/* Initialize and start the PDC */
	ग_लिखोl(runसमय->dma_addr, chip->regs + ATMEL_PDC_TPR);
	ग_लिखोl(block_size / 2, chip->regs + ATMEL_PDC_TCR);
	ग_लिखोl(runसमय->dma_addr + block_size, chip->regs + ATMEL_PDC_TNPR);
	ग_लिखोl(block_size / 2, chip->regs + ATMEL_PDC_TNCR);

	वापस retval;
पूर्ण

अटल पूर्णांक aपंचांगel_ac97c_capture_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा aपंचांगel_ac97c *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक block_size = frames_to_bytes(runसमय, runसमय->period_size);
	अचिन्हित दीर्घ word = ac97c_पढ़ोl(chip, ICA);
	पूर्णांक retval;

	chip->capture_period = 0;
	word &= ~(AC97C_CH_MASK(PCM_LEFT) | AC97C_CH_MASK(PCM_RIGHT));

	/* assign channels to AC97C channel A */
	चयन (runसमय->channels) अणु
	हाल 1:
		word |= AC97C_CH_ASSIGN(PCM_LEFT, A);
		अवरोध;
	हाल 2:
		word |= AC97C_CH_ASSIGN(PCM_LEFT, A)
			| AC97C_CH_ASSIGN(PCM_RIGHT, A);
		अवरोध;
	शेष:
		/* TODO: support more than two channels */
		वापस -EINVAL;
	पूर्ण
	ac97c_ग_लिखोl(chip, ICA, word);

	/* configure sample क्रमmat and size */
	word = ac97c_पढ़ोl(chip, CAMR);
	अगर (chip->खोलोed <= 1)
		word = AC97C_CMR_DMAEN | AC97C_CMR_SIZE_16;
	अन्यथा
		word |= AC97C_CMR_DMAEN | AC97C_CMR_SIZE_16;

	चयन (runसमय->क्रमmat) अणु
	हाल SNDRV_PCM_FORMAT_S16_LE:
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S16_BE:
		word &= ~(AC97C_CMR_CEM_LITTLE);
		अवरोध;
	शेष:
		word = ac97c_पढ़ोl(chip, ICA);
		word &= ~(AC97C_CH_MASK(PCM_LEFT) | AC97C_CH_MASK(PCM_RIGHT));
		ac97c_ग_लिखोl(chip, ICA, word);
		वापस -EINVAL;
	पूर्ण

	/* Enable overrun पूर्णांकerrupt on channel A */
	word |= AC97C_CSR_OVRUN;

	ac97c_ग_लिखोl(chip, CAMR, word);

	/* Enable channel A event पूर्णांकerrupt */
	word = ac97c_पढ़ोl(chip, IMR);
	word |= AC97C_SR_CAEVT;
	ac97c_ग_लिखोl(chip, IER, word);

	/* set variable rate अगर needed */
	अगर (runसमय->rate != 48000) अणु
		word = ac97c_पढ़ोl(chip, MR);
		word |= AC97C_MR_VRA;
		ac97c_ग_लिखोl(chip, MR, word);
	पूर्ण अन्यथा अणु
		word = ac97c_पढ़ोl(chip, MR);
		word &= ~(AC97C_MR_VRA);
		ac97c_ग_लिखोl(chip, MR, word);
	पूर्ण

	retval = snd_ac97_set_rate(chip->ac97, AC97_PCM_LR_ADC_RATE,
			runसमय->rate);
	अगर (retval)
		dev_dbg(&chip->pdev->dev, "could not set rate %d Hz\n",
				runसमय->rate);

	/* Initialize and start the PDC */
	ग_लिखोl(runसमय->dma_addr, chip->regs + ATMEL_PDC_RPR);
	ग_लिखोl(block_size / 2, chip->regs + ATMEL_PDC_RCR);
	ग_लिखोl(runसमय->dma_addr + block_size, chip->regs + ATMEL_PDC_RNPR);
	ग_लिखोl(block_size / 2, chip->regs + ATMEL_PDC_RNCR);

	वापस retval;
पूर्ण

अटल पूर्णांक
aपंचांगel_ac97c_playback_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा aपंचांगel_ac97c *chip = snd_pcm_substream_chip(substream);
	अचिन्हित दीर्घ camr, ptcr = 0;

	camr = ac97c_पढ़ोl(chip, CAMR);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_START:
		ptcr = ATMEL_PDC_TXTEN;
		camr |= AC97C_CMR_CENA | AC97C_CSR_ENDTX;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_STOP:
		ptcr |= ATMEL_PDC_TXTDIS;
		अगर (chip->खोलोed <= 1)
			camr &= ~AC97C_CMR_CENA;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ac97c_ग_लिखोl(chip, CAMR, camr);
	ग_लिखोl(ptcr, chip->regs + ATMEL_PDC_PTCR);
	वापस 0;
पूर्ण

अटल पूर्णांक
aपंचांगel_ac97c_capture_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा aपंचांगel_ac97c *chip = snd_pcm_substream_chip(substream);
	अचिन्हित दीर्घ camr, ptcr = 0;

	camr = ac97c_पढ़ोl(chip, CAMR);
	ptcr = पढ़ोl(chip->regs + ATMEL_PDC_PTSR);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_START:
		ptcr = ATMEL_PDC_RXTEN;
		camr |= AC97C_CMR_CENA | AC97C_CSR_ENDRX;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_STOP:
		ptcr |= ATMEL_PDC_RXTDIS;
		अगर (chip->खोलोed <= 1)
			camr &= ~AC97C_CMR_CENA;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ac97c_ग_लिखोl(chip, CAMR, camr);
	ग_लिखोl(ptcr, chip->regs + ATMEL_PDC_PTCR);
	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t
aपंचांगel_ac97c_playback_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा aपंचांगel_ac97c	*chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय	*runसमय = substream->runसमय;
	snd_pcm_uframes_t	frames;
	अचिन्हित दीर्घ		bytes;

	bytes = पढ़ोl(chip->regs + ATMEL_PDC_TPR);
	bytes -= runसमय->dma_addr;

	frames = bytes_to_frames(runसमय, bytes);
	अगर (frames >= runसमय->buffer_size)
		frames -= runसमय->buffer_size;
	वापस frames;
पूर्ण

अटल snd_pcm_uframes_t
aपंचांगel_ac97c_capture_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा aपंचांगel_ac97c	*chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय	*runसमय = substream->runसमय;
	snd_pcm_uframes_t	frames;
	अचिन्हित दीर्घ		bytes;

	bytes = पढ़ोl(chip->regs + ATMEL_PDC_RPR);
	bytes -= runसमय->dma_addr;

	frames = bytes_to_frames(runसमय, bytes);
	अगर (frames >= runसमय->buffer_size)
		frames -= runसमय->buffer_size;
	वापस frames;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops aपंचांगel_ac97_playback_ops = अणु
	.खोलो		= aपंचांगel_ac97c_playback_खोलो,
	.बंद		= aपंचांगel_ac97c_playback_बंद,
	.hw_params	= aपंचांगel_ac97c_playback_hw_params,
	.prepare	= aपंचांगel_ac97c_playback_prepare,
	.trigger	= aपंचांगel_ac97c_playback_trigger,
	.poपूर्णांकer	= aपंचांगel_ac97c_playback_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops aपंचांगel_ac97_capture_ops = अणु
	.खोलो		= aपंचांगel_ac97c_capture_खोलो,
	.बंद		= aपंचांगel_ac97c_capture_बंद,
	.hw_params	= aपंचांगel_ac97c_capture_hw_params,
	.prepare	= aपंचांगel_ac97c_capture_prepare,
	.trigger	= aपंचांगel_ac97c_capture_trigger,
	.poपूर्णांकer	= aपंचांगel_ac97c_capture_poपूर्णांकer,
पूर्ण;

अटल irqवापस_t aपंचांगel_ac97c_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा aपंचांगel_ac97c	*chip  = (काष्ठा aपंचांगel_ac97c *)dev;
	irqवापस_t		retval = IRQ_NONE;
	u32			sr     = ac97c_पढ़ोl(chip, SR);
	u32			casr   = ac97c_पढ़ोl(chip, CASR);
	u32			cosr   = ac97c_पढ़ोl(chip, COSR);
	u32			camr   = ac97c_पढ़ोl(chip, CAMR);

	अगर (sr & AC97C_SR_CAEVT) अणु
		काष्ठा snd_pcm_runसमय *runसमय;
		पूर्णांक offset, next_period, block_size;
		dev_dbg(&chip->pdev->dev, "channel A event%s%s%s%s%s%s\n",
			(casr & AC97C_CSR_OVRUN)   ? " OVRUN"   : "",
			(casr & AC97C_CSR_RXRDY)   ? " RXRDY"   : "",
			(casr & AC97C_CSR_UNRUN)   ? " UNRUN"   : "",
			(casr & AC97C_CSR_TXEMPTY) ? " TXEMPTY" : "",
			(casr & AC97C_CSR_TXRDY)   ? " TXRDY"   : "",
			!casr                      ? " NONE"    : "");
		अगर ((casr & camr) & AC97C_CSR_ENDTX) अणु
			runसमय = chip->playback_substream->runसमय;
			block_size = frames_to_bytes(runसमय, runसमय->period_size);
			chip->playback_period++;

			अगर (chip->playback_period == runसमय->periods)
				chip->playback_period = 0;
			next_period = chip->playback_period + 1;
			अगर (next_period == runसमय->periods)
				next_period = 0;

			offset = block_size * next_period;

			ग_लिखोl(runसमय->dma_addr + offset, chip->regs + ATMEL_PDC_TNPR);
			ग_लिखोl(block_size / 2, chip->regs + ATMEL_PDC_TNCR);

			snd_pcm_period_elapsed(chip->playback_substream);
		पूर्ण
		अगर ((casr & camr) & AC97C_CSR_ENDRX) अणु
			runसमय = chip->capture_substream->runसमय;
			block_size = frames_to_bytes(runसमय, runसमय->period_size);
			chip->capture_period++;

			अगर (chip->capture_period == runसमय->periods)
				chip->capture_period = 0;
			next_period = chip->capture_period + 1;
			अगर (next_period == runसमय->periods)
				next_period = 0;

			offset = block_size * next_period;

			ग_लिखोl(runसमय->dma_addr + offset, chip->regs + ATMEL_PDC_RNPR);
			ग_लिखोl(block_size / 2, chip->regs + ATMEL_PDC_RNCR);
			snd_pcm_period_elapsed(chip->capture_substream);
		पूर्ण
		retval = IRQ_HANDLED;
	पूर्ण

	अगर (sr & AC97C_SR_COEVT) अणु
		dev_info(&chip->pdev->dev, "codec channel event%s%s%s%s%s\n",
			 (cosr & AC97C_CSR_OVRUN)   ? " OVRUN"   : "",
			 (cosr & AC97C_CSR_RXRDY)   ? " RXRDY"   : "",
			 (cosr & AC97C_CSR_TXEMPTY) ? " TXEMPTY" : "",
			 (cosr & AC97C_CSR_TXRDY)   ? " TXRDY"   : "",
			 !cosr                      ? " NONE"    : "");
		retval = IRQ_HANDLED;
	पूर्ण

	अगर (retval == IRQ_NONE) अणु
		dev_err(&chip->pdev->dev, "spurious interrupt sr 0x%08x "
				"casr 0x%08x cosr 0x%08x\n", sr, casr, cosr);
	पूर्ण

	वापस retval;
पूर्ण

अटल स्थिर काष्ठा ac97_pcm at91_ac97_pcm_defs[] = अणु
	/* Playback */
	अणु
		.exclusive = 1,
		.r = अणु अणु
			.slots = ((1 << AC97_SLOT_PCM_LEFT)
				  | (1 << AC97_SLOT_PCM_RIGHT)),
		पूर्ण पूर्ण,
	पूर्ण,
	/* PCM in */
	अणु
		.stream = 1,
		.exclusive = 1,
		.r = अणु अणु
			.slots = ((1 << AC97_SLOT_PCM_LEFT)
					| (1 << AC97_SLOT_PCM_RIGHT)),
		पूर्ण पूर्ण
	पूर्ण,
	/* Mic in */
	अणु
		.stream = 1,
		.exclusive = 1,
		.r = अणु अणु
			.slots = (1<<AC97_SLOT_MIC),
		पूर्ण पूर्ण
	पूर्ण,
पूर्ण;

अटल पूर्णांक aपंचांगel_ac97c_pcm_new(काष्ठा aपंचांगel_ac97c *chip)
अणु
	काष्ठा snd_pcm		*pcm;
	काष्ठा snd_pcm_hardware	hw = aपंचांगel_ac97c_hw;
	पूर्णांक			retval;

	retval = snd_ac97_pcm_assign(chip->ac97_bus,
				     ARRAY_SIZE(at91_ac97_pcm_defs),
				     at91_ac97_pcm_defs);
	अगर (retval)
		वापस retval;

	retval = snd_pcm_new(chip->card, chip->card->लघुname, 0, 1, 1, &pcm);
	अगर (retval)
		वापस retval;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &aपंचांगel_ac97_capture_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &aपंचांगel_ac97_playback_ops);

	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV,
			&chip->pdev->dev, hw.periods_min * hw.period_bytes_min,
			hw.buffer_bytes_max);

	pcm->निजी_data = chip;
	pcm->info_flags = 0;
	म_नकल(pcm->name, chip->card->लघुname);
	chip->pcm = pcm;

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_ac97c_mixer_new(काष्ठा aपंचांगel_ac97c *chip)
अणु
	काष्ठा snd_ac97_ढाँचा ढाँचा;
	स_रखो(&ढाँचा, 0, माप(ढाँचा));
	ढाँचा.निजी_data = chip;
	वापस snd_ac97_mixer(chip->ac97_bus, &ढाँचा, &chip->ac97);
पूर्ण

अटल व्योम aपंचांगel_ac97c_ग_लिखो(काष्ठा snd_ac97 *ac97, अचिन्हित लघु reg,
		अचिन्हित लघु val)
अणु
	काष्ठा aपंचांगel_ac97c *chip = get_chip(ac97);
	अचिन्हित दीर्घ word;
	पूर्णांक समयout = 40;

	word = (reg & 0x7f) << 16 | val;

	करो अणु
		अगर (ac97c_पढ़ोl(chip, COSR) & AC97C_CSR_TXRDY) अणु
			ac97c_ग_लिखोl(chip, COTHR, word);
			वापस;
		पूर्ण
		udelay(1);
	पूर्ण जबतक (--समयout);

	dev_dbg(&chip->pdev->dev, "codec write timeout\n");
पूर्ण

अटल अचिन्हित लघु aपंचांगel_ac97c_पढ़ो(काष्ठा snd_ac97 *ac97,
		अचिन्हित लघु reg)
अणु
	काष्ठा aपंचांगel_ac97c *chip = get_chip(ac97);
	अचिन्हित दीर्घ word;
	पूर्णांक समयout = 40;
	पूर्णांक ग_लिखो = 10;

	word = (0x80 | (reg & 0x7f)) << 16;

	अगर ((ac97c_पढ़ोl(chip, COSR) & AC97C_CSR_RXRDY) != 0)
		ac97c_पढ़ोl(chip, CORHR);

retry_ग_लिखो:
	समयout = 40;

	करो अणु
		अगर ((ac97c_पढ़ोl(chip, COSR) & AC97C_CSR_TXRDY) != 0) अणु
			ac97c_ग_लिखोl(chip, COTHR, word);
			जाओ पढ़ो_reg;
		पूर्ण
		udelay(10);
	पूर्ण जबतक (--समयout);

	अगर (!--ग_लिखो)
		जाओ समयd_out;
	जाओ retry_ग_लिखो;

पढ़ो_reg:
	करो अणु
		अगर ((ac97c_पढ़ोl(chip, COSR) & AC97C_CSR_RXRDY) != 0) अणु
			अचिन्हित लघु val = ac97c_पढ़ोl(chip, CORHR);
			वापस val;
		पूर्ण
		udelay(10);
	पूर्ण जबतक (--समयout);

	अगर (!--ग_लिखो)
		जाओ समयd_out;
	जाओ retry_ग_लिखो;

समयd_out:
	dev_dbg(&chip->pdev->dev, "codec read timeout\n");
	वापस 0xffff;
पूर्ण

अटल व्योम aपंचांगel_ac97c_reset(काष्ठा aपंचांगel_ac97c *chip)
अणु
	ac97c_ग_लिखोl(chip, MR,   0);
	ac97c_ग_लिखोl(chip, MR,   AC97C_MR_ENA);
	ac97c_ग_लिखोl(chip, CAMR, 0);
	ac97c_ग_लिखोl(chip, COMR, 0);

	अगर (!IS_ERR(chip->reset_pin)) अणु
		gpiod_set_value(chip->reset_pin, 0);
		/* AC97 v2.2 specअगरications says minimum 1 us. */
		udelay(2);
		gpiod_set_value(chip->reset_pin, 1);
	पूर्ण अन्यथा अणु
		ac97c_ग_लिखोl(chip, MR, AC97C_MR_WRST | AC97C_MR_ENA);
		udelay(2);
		ac97c_ग_लिखोl(chip, MR, AC97C_MR_ENA);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा of_device_id aपंचांगel_ac97c_dt_ids[] = अणु
	अणु .compatible = "atmel,at91sam9263-ac97c", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, aपंचांगel_ac97c_dt_ids);

अटल पूर्णांक aपंचांगel_ac97c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device			*dev = &pdev->dev;
	काष्ठा snd_card			*card;
	काष्ठा aपंचांगel_ac97c		*chip;
	काष्ठा resource			*regs;
	काष्ठा clk			*pclk;
	अटल स्थिर काष्ठा snd_ac97_bus_ops	ops = अणु
		.ग_लिखो	= aपंचांगel_ac97c_ग_लिखो,
		.पढ़ो	= aपंचांगel_ac97c_पढ़ो,
	पूर्ण;
	पूर्णांक				retval;
	पूर्णांक				irq;

	regs = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!regs) अणु
		dev_dbg(&pdev->dev, "no memory resource\n");
		वापस -ENXIO;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		dev_dbg(&pdev->dev, "could not get irq: %d\n", irq);
		वापस irq;
	पूर्ण

	pclk = clk_get(&pdev->dev, "ac97_clk");
	अगर (IS_ERR(pclk)) अणु
		dev_dbg(&pdev->dev, "no peripheral clock\n");
		वापस PTR_ERR(pclk);
	पूर्ण
	retval = clk_prepare_enable(pclk);
	अगर (retval)
		जाओ err_prepare_enable;

	retval = snd_card_new(&pdev->dev, SNDRV_DEFAULT_IDX1,
			      SNDRV_DEFAULT_STR1, THIS_MODULE,
			      माप(काष्ठा aपंचांगel_ac97c), &card);
	अगर (retval) अणु
		dev_dbg(&pdev->dev, "could not create sound card device\n");
		जाओ err_snd_card_new;
	पूर्ण

	chip = get_chip(card);

	retval = request_irq(irq, aपंचांगel_ac97c_पूर्णांकerrupt, 0, "AC97C", chip);
	अगर (retval) अणु
		dev_dbg(&pdev->dev, "unable to request irq %d\n", irq);
		जाओ err_request_irq;
	पूर्ण
	chip->irq = irq;

	spin_lock_init(&chip->lock);

	म_नकल(card->driver, "Atmel AC97C");
	म_नकल(card->लघुname, "Atmel AC97C");
	प्र_लिखो(card->दीर्घname, "Atmel AC97 controller");

	chip->card = card;
	chip->pclk = pclk;
	chip->pdev = pdev;
	chip->regs = ioremap(regs->start, resource_size(regs));

	अगर (!chip->regs) अणु
		dev_dbg(&pdev->dev, "could not remap register memory\n");
		retval = -ENOMEM;
		जाओ err_ioremap;
	पूर्ण

	chip->reset_pin = devm_gpiod_get_index(dev, "ac97", 2, GPIOD_OUT_HIGH);
	अगर (IS_ERR(chip->reset_pin))
		dev_dbg(dev, "reset pin not available\n");

	aपंचांगel_ac97c_reset(chip);

	/* Enable overrun पूर्णांकerrupt from codec channel */
	ac97c_ग_लिखोl(chip, COMR, AC97C_CSR_OVRUN);
	ac97c_ग_लिखोl(chip, IER, ac97c_पढ़ोl(chip, IMR) | AC97C_SR_COEVT);

	retval = snd_ac97_bus(card, 0, &ops, chip, &chip->ac97_bus);
	अगर (retval) अणु
		dev_dbg(&pdev->dev, "could not register on ac97 bus\n");
		जाओ err_ac97_bus;
	पूर्ण

	retval = aपंचांगel_ac97c_mixer_new(chip);
	अगर (retval) अणु
		dev_dbg(&pdev->dev, "could not register ac97 mixer\n");
		जाओ err_ac97_bus;
	पूर्ण

	retval = aपंचांगel_ac97c_pcm_new(chip);
	अगर (retval) अणु
		dev_dbg(&pdev->dev, "could not register ac97 pcm device\n");
		जाओ err_ac97_bus;
	पूर्ण

	retval = snd_card_रेजिस्टर(card);
	अगर (retval) अणु
		dev_dbg(&pdev->dev, "could not register sound card\n");
		जाओ err_ac97_bus;
	पूर्ण

	platक्रमm_set_drvdata(pdev, card);

	dev_info(&pdev->dev, "Atmel AC97 controller at 0x%p, irq = %d\n",
			chip->regs, irq);

	वापस 0;

err_ac97_bus:
	iounmap(chip->regs);
err_ioremap:
	मुक्त_irq(irq, chip);
err_request_irq:
	snd_card_मुक्त(card);
err_snd_card_new:
	clk_disable_unprepare(pclk);
err_prepare_enable:
	clk_put(pclk);
	वापस retval;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक aपंचांगel_ac97c_suspend(काष्ठा device *pdev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(pdev);
	काष्ठा aपंचांगel_ac97c *chip = card->निजी_data;

	clk_disable_unprepare(chip->pclk);
	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_ac97c_resume(काष्ठा device *pdev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(pdev);
	काष्ठा aपंचांगel_ac97c *chip = card->निजी_data;
	पूर्णांक ret = clk_prepare_enable(chip->pclk);

	वापस ret;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(aपंचांगel_ac97c_pm, aपंचांगel_ac97c_suspend, aपंचांगel_ac97c_resume);
#घोषणा ATMEL_AC97C_PM_OPS	&aपंचांगel_ac97c_pm
#अन्यथा
#घोषणा ATMEL_AC97C_PM_OPS	शून्य
#पूर्ण_अगर

अटल पूर्णांक aपंचांगel_ac97c_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_card *card = platक्रमm_get_drvdata(pdev);
	काष्ठा aपंचांगel_ac97c *chip = get_chip(card);

	ac97c_ग_लिखोl(chip, CAMR, 0);
	ac97c_ग_लिखोl(chip, COMR, 0);
	ac97c_ग_लिखोl(chip, MR,   0);

	clk_disable_unprepare(chip->pclk);
	clk_put(chip->pclk);
	iounmap(chip->regs);
	मुक्त_irq(chip->irq, chip);

	snd_card_मुक्त(card);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver aपंचांगel_ac97c_driver = अणु
	.probe		= aपंचांगel_ac97c_probe,
	.हटाओ		= aपंचांगel_ac97c_हटाओ,
	.driver		= अणु
		.name	= "atmel_ac97c",
		.pm	= ATMEL_AC97C_PM_OPS,
		.of_match_table = aपंचांगel_ac97c_dt_ids,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(aपंचांगel_ac97c_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Driver for Atmel AC97 controller");
MODULE_AUTHOR("Hans-Christian Egtvedt <egtvedt@samfundet.no>");
