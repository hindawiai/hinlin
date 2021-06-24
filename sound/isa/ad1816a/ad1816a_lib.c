<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    ad1816a.c - lowlevel code क्रम Analog Devices AD1816A chip.
    Copyright (C) 1999-2000 by Massimo Piccioni <dafastidio@libero.it>

*/

#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/ioport.h>
#समावेश <linux/पन.स>
#समावेश <sound/core.h>
#समावेश <sound/tlv.h>
#समावेश <sound/ad1816a.h>

#समावेश <यंत्र/dma.h>

अटल अंतरभूत पूर्णांक snd_ad1816a_busy_रुको(काष्ठा snd_ad1816a *chip)
अणु
	पूर्णांक समयout;

	क्रम (समयout = 1000; समयout-- > 0; udelay(10))
		अगर (inb(AD1816A_REG(AD1816A_CHIP_STATUS)) & AD1816A_READY)
			वापस 0;

	snd_prपूर्णांकk(KERN_WARNING "chip busy.\n");
	वापस -EBUSY;
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर snd_ad1816a_in(काष्ठा snd_ad1816a *chip, अचिन्हित अक्षर reg)
अणु
	snd_ad1816a_busy_रुको(chip);
	वापस inb(AD1816A_REG(reg));
पूर्ण

अटल अंतरभूत व्योम snd_ad1816a_out(काष्ठा snd_ad1816a *chip, अचिन्हित अक्षर reg,
			    अचिन्हित अक्षर value)
अणु
	snd_ad1816a_busy_रुको(chip);
	outb(value, AD1816A_REG(reg));
पूर्ण

अटल अंतरभूत व्योम snd_ad1816a_out_mask(काष्ठा snd_ad1816a *chip, अचिन्हित अक्षर reg,
				 अचिन्हित अक्षर mask, अचिन्हित अक्षर value)
अणु
	snd_ad1816a_out(chip, reg,
		(value & mask) | (snd_ad1816a_in(chip, reg) & ~mask));
पूर्ण

अटल अचिन्हित लघु snd_ad1816a_पढ़ो(काष्ठा snd_ad1816a *chip, अचिन्हित अक्षर reg)
अणु
	snd_ad1816a_out(chip, AD1816A_INसूची_ADDR, reg & 0x3f);
	वापस snd_ad1816a_in(chip, AD1816A_INसूची_DATA_LOW) |
		(snd_ad1816a_in(chip, AD1816A_INसूची_DATA_HIGH) << 8);
पूर्ण

अटल व्योम snd_ad1816a_ग_लिखो(काष्ठा snd_ad1816a *chip, अचिन्हित अक्षर reg,
			      अचिन्हित लघु value)
अणु
	snd_ad1816a_out(chip, AD1816A_INसूची_ADDR, reg & 0x3f);
	snd_ad1816a_out(chip, AD1816A_INसूची_DATA_LOW, value & 0xff);
	snd_ad1816a_out(chip, AD1816A_INसूची_DATA_HIGH, (value >> 8) & 0xff);
पूर्ण

अटल व्योम snd_ad1816a_ग_लिखो_mask(काष्ठा snd_ad1816a *chip, अचिन्हित अक्षर reg,
				   अचिन्हित लघु mask, अचिन्हित लघु value)
अणु
	snd_ad1816a_ग_लिखो(chip, reg,
		(value & mask) | (snd_ad1816a_पढ़ो(chip, reg) & ~mask));
पूर्ण


अटल अचिन्हित अक्षर snd_ad1816a_get_क्रमmat(काष्ठा snd_ad1816a *chip,
					    snd_pcm_क्रमmat_t क्रमmat,
					    पूर्णांक channels)
अणु
	अचिन्हित अक्षर retval = AD1816A_FMT_LINEAR_8;

	चयन (क्रमmat) अणु
	हाल SNDRV_PCM_FORMAT_MU_LAW:
		retval = AD1816A_FMT_ULAW_8;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_A_LAW:
		retval = AD1816A_FMT_ALAW_8;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S16_LE:
		retval = AD1816A_FMT_LINEAR_16_LIT;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S16_BE:
		retval = AD1816A_FMT_LINEAR_16_BIG;
	पूर्ण
	वापस (channels > 1) ? (retval | AD1816A_FMT_STEREO) : retval;
पूर्ण

अटल पूर्णांक snd_ad1816a_खोलो(काष्ठा snd_ad1816a *chip, अचिन्हित पूर्णांक mode)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chip->lock, flags);

	अगर (chip->mode & mode) अणु
		spin_unlock_irqrestore(&chip->lock, flags);
		वापस -EAGAIN;
	पूर्ण

	चयन ((mode &= AD1816A_MODE_OPEN)) अणु
	हाल AD1816A_MODE_PLAYBACK:
		snd_ad1816a_out_mask(chip, AD1816A_INTERRUPT_STATUS,
			AD1816A_PLAYBACK_IRQ_PENDING, 0x00);
		snd_ad1816a_ग_लिखो_mask(chip, AD1816A_INTERRUPT_ENABLE,
			AD1816A_PLAYBACK_IRQ_ENABLE, 0xffff);
		अवरोध;
	हाल AD1816A_MODE_CAPTURE:
		snd_ad1816a_out_mask(chip, AD1816A_INTERRUPT_STATUS,
			AD1816A_CAPTURE_IRQ_PENDING, 0x00);
		snd_ad1816a_ग_लिखो_mask(chip, AD1816A_INTERRUPT_ENABLE,
			AD1816A_CAPTURE_IRQ_ENABLE, 0xffff);
		अवरोध;
	हाल AD1816A_MODE_TIMER:
		snd_ad1816a_out_mask(chip, AD1816A_INTERRUPT_STATUS,
			AD1816A_TIMER_IRQ_PENDING, 0x00);
		snd_ad1816a_ग_लिखो_mask(chip, AD1816A_INTERRUPT_ENABLE,
			AD1816A_TIMER_IRQ_ENABLE, 0xffff);
	पूर्ण
	chip->mode |= mode;

	spin_unlock_irqrestore(&chip->lock, flags);
	वापस 0;
पूर्ण

अटल व्योम snd_ad1816a_बंद(काष्ठा snd_ad1816a *chip, अचिन्हित पूर्णांक mode)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chip->lock, flags);

	चयन ((mode &= AD1816A_MODE_OPEN)) अणु
	हाल AD1816A_MODE_PLAYBACK:
		snd_ad1816a_out_mask(chip, AD1816A_INTERRUPT_STATUS,
			AD1816A_PLAYBACK_IRQ_PENDING, 0x00);
		snd_ad1816a_ग_लिखो_mask(chip, AD1816A_INTERRUPT_ENABLE,
			AD1816A_PLAYBACK_IRQ_ENABLE, 0x0000);
		अवरोध;
	हाल AD1816A_MODE_CAPTURE:
		snd_ad1816a_out_mask(chip, AD1816A_INTERRUPT_STATUS,
			AD1816A_CAPTURE_IRQ_PENDING, 0x00);
		snd_ad1816a_ग_लिखो_mask(chip, AD1816A_INTERRUPT_ENABLE,
			AD1816A_CAPTURE_IRQ_ENABLE, 0x0000);
		अवरोध;
	हाल AD1816A_MODE_TIMER:
		snd_ad1816a_out_mask(chip, AD1816A_INTERRUPT_STATUS,
			AD1816A_TIMER_IRQ_PENDING, 0x00);
		snd_ad1816a_ग_लिखो_mask(chip, AD1816A_INTERRUPT_ENABLE,
			AD1816A_TIMER_IRQ_ENABLE, 0x0000);
	पूर्ण
	अगर (!((chip->mode &= ~mode) & AD1816A_MODE_OPEN))
		chip->mode = 0;

	spin_unlock_irqrestore(&chip->lock, flags);
पूर्ण


अटल पूर्णांक snd_ad1816a_trigger(काष्ठा snd_ad1816a *chip, अचिन्हित अक्षर what,
			       पूर्णांक channel, पूर्णांक cmd, पूर्णांक iscapture)
अणु
	पूर्णांक error = 0;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_STOP:
		spin_lock(&chip->lock);
		cmd = (cmd == SNDRV_PCM_TRIGGER_START) ? 0xff: 0x00;
		/* अगर (what & AD1816A_PLAYBACK_ENABLE) */
		/* That is not valid, because playback and capture enable
		 * are the same bit pattern, just to dअगरferent addresses
		 */
		अगर (! iscapture)
			snd_ad1816a_out_mask(chip, AD1816A_PLAYBACK_CONFIG,
				AD1816A_PLAYBACK_ENABLE, cmd);
		अन्यथा
			snd_ad1816a_out_mask(chip, AD1816A_CAPTURE_CONFIG,
				AD1816A_CAPTURE_ENABLE, cmd);
		spin_unlock(&chip->lock);
		अवरोध;
	शेष:
		snd_prपूर्णांकk(KERN_WARNING "invalid trigger mode 0x%x.\n", what);
		error = -EINVAL;
	पूर्ण

	वापस error;
पूर्ण

अटल पूर्णांक snd_ad1816a_playback_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा snd_ad1816a *chip = snd_pcm_substream_chip(substream);
	वापस snd_ad1816a_trigger(chip, AD1816A_PLAYBACK_ENABLE,
				   SNDRV_PCM_STREAM_PLAYBACK, cmd, 0);
पूर्ण

अटल पूर्णांक snd_ad1816a_capture_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा snd_ad1816a *chip = snd_pcm_substream_chip(substream);
	वापस snd_ad1816a_trigger(chip, AD1816A_CAPTURE_ENABLE,
				   SNDRV_PCM_STREAM_CAPTURE, cmd, 1);
पूर्ण

अटल पूर्णांक snd_ad1816a_playback_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ad1816a *chip = snd_pcm_substream_chip(substream);
	अचिन्हित दीर्घ flags;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अचिन्हित पूर्णांक size, rate;

	spin_lock_irqsave(&chip->lock, flags);

	chip->p_dma_size = size = snd_pcm_lib_buffer_bytes(substream);
	snd_ad1816a_out_mask(chip, AD1816A_PLAYBACK_CONFIG,
		AD1816A_PLAYBACK_ENABLE | AD1816A_PLAYBACK_PIO, 0x00);

	snd_dma_program(chip->dma1, runसमय->dma_addr, size,
			DMA_MODE_WRITE | DMA_AUTOINIT);

	rate = runसमय->rate;
	अगर (chip->घड़ी_freq)
		rate = (rate * 33000) / chip->घड़ी_freq;
	snd_ad1816a_ग_लिखो(chip, AD1816A_PLAYBACK_SAMPLE_RATE, rate);
	snd_ad1816a_out_mask(chip, AD1816A_PLAYBACK_CONFIG,
		AD1816A_FMT_ALL | AD1816A_FMT_STEREO,
		snd_ad1816a_get_क्रमmat(chip, runसमय->क्रमmat,
			runसमय->channels));

	snd_ad1816a_ग_लिखो(chip, AD1816A_PLAYBACK_BASE_COUNT,
		snd_pcm_lib_period_bytes(substream) / 4 - 1);

	spin_unlock_irqrestore(&chip->lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ad1816a_capture_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ad1816a *chip = snd_pcm_substream_chip(substream);
	अचिन्हित दीर्घ flags;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अचिन्हित पूर्णांक size, rate;

	spin_lock_irqsave(&chip->lock, flags);

	chip->c_dma_size = size = snd_pcm_lib_buffer_bytes(substream);
	snd_ad1816a_out_mask(chip, AD1816A_CAPTURE_CONFIG,
		AD1816A_CAPTURE_ENABLE | AD1816A_CAPTURE_PIO, 0x00);

	snd_dma_program(chip->dma2, runसमय->dma_addr, size,
			DMA_MODE_READ | DMA_AUTOINIT);

	rate = runसमय->rate;
	अगर (chip->घड़ी_freq)
		rate = (rate * 33000) / chip->घड़ी_freq;
	snd_ad1816a_ग_लिखो(chip, AD1816A_CAPTURE_SAMPLE_RATE, rate);
	snd_ad1816a_out_mask(chip, AD1816A_CAPTURE_CONFIG,
		AD1816A_FMT_ALL | AD1816A_FMT_STEREO,
		snd_ad1816a_get_क्रमmat(chip, runसमय->क्रमmat,
			runसमय->channels));

	snd_ad1816a_ग_लिखो(chip, AD1816A_CAPTURE_BASE_COUNT,
		snd_pcm_lib_period_bytes(substream) / 4 - 1);

	spin_unlock_irqrestore(&chip->lock, flags);
	वापस 0;
पूर्ण


अटल snd_pcm_uframes_t snd_ad1816a_playback_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ad1816a *chip = snd_pcm_substream_chip(substream);
	माप_प्रकार ptr;
	अगर (!(chip->mode & AD1816A_MODE_PLAYBACK))
		वापस 0;
	ptr = snd_dma_poपूर्णांकer(chip->dma1, chip->p_dma_size);
	वापस bytes_to_frames(substream->runसमय, ptr);
पूर्ण

अटल snd_pcm_uframes_t snd_ad1816a_capture_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ad1816a *chip = snd_pcm_substream_chip(substream);
	माप_प्रकार ptr;
	अगर (!(chip->mode & AD1816A_MODE_CAPTURE))
		वापस 0;
	ptr = snd_dma_poपूर्णांकer(chip->dma2, chip->c_dma_size);
	वापस bytes_to_frames(substream->runसमय, ptr);
पूर्ण


अटल irqवापस_t snd_ad1816a_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा snd_ad1816a *chip = dev_id;
	अचिन्हित अक्षर status;

	spin_lock(&chip->lock);
	status = snd_ad1816a_in(chip, AD1816A_INTERRUPT_STATUS);
	spin_unlock(&chip->lock);

	अगर ((status & AD1816A_PLAYBACK_IRQ_PENDING) && chip->playback_substream)
		snd_pcm_period_elapsed(chip->playback_substream);

	अगर ((status & AD1816A_CAPTURE_IRQ_PENDING) && chip->capture_substream)
		snd_pcm_period_elapsed(chip->capture_substream);

	अगर ((status & AD1816A_TIMER_IRQ_PENDING) && chip->समयr)
		snd_समयr_पूर्णांकerrupt(chip->समयr, chip->समयr->sticks);

	spin_lock(&chip->lock);
	snd_ad1816a_out(chip, AD1816A_INTERRUPT_STATUS, 0x00);
	spin_unlock(&chip->lock);
	वापस IRQ_HANDLED;
पूर्ण


अटल स्थिर काष्ठा snd_pcm_hardware snd_ad1816a_playback = अणु
	.info =			(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_MMAP_VALID),
	.क्रमmats =		(SNDRV_PCM_FMTBIT_MU_LAW | SNDRV_PCM_FMTBIT_A_LAW |
				 SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S16_LE |
				 SNDRV_PCM_FMTBIT_S16_BE),
	.rates =		SNDRV_PCM_RATE_CONTINUOUS | SNDRV_PCM_RATE_8000_48000,
	.rate_min =		4000,
	.rate_max =		55200,
	.channels_min =		1,
	.channels_max =		2,
	.buffer_bytes_max =	(128*1024),
	.period_bytes_min =	64,
	.period_bytes_max =	(128*1024),
	.periods_min =		1,
	.periods_max =		1024,
	.fअगरo_size =		0,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware snd_ad1816a_capture = अणु
	.info =			(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_MMAP_VALID),
	.क्रमmats =		(SNDRV_PCM_FMTBIT_MU_LAW | SNDRV_PCM_FMTBIT_A_LAW |
				 SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S16_LE |
				 SNDRV_PCM_FMTBIT_S16_BE),
	.rates =		SNDRV_PCM_RATE_CONTINUOUS | SNDRV_PCM_RATE_8000_48000,
	.rate_min =		4000,
	.rate_max =		55200,
	.channels_min =		1,
	.channels_max =		2,
	.buffer_bytes_max =	(128*1024),
	.period_bytes_min =	64,
	.period_bytes_max =	(128*1024),
	.periods_min =		1,
	.periods_max =		1024,
	.fअगरo_size =		0,
पूर्ण;

अटल पूर्णांक snd_ad1816a_समयr_बंद(काष्ठा snd_समयr *समयr)
अणु
	काष्ठा snd_ad1816a *chip = snd_समयr_chip(समयr);
	snd_ad1816a_बंद(chip, AD1816A_MODE_TIMER);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ad1816a_समयr_खोलो(काष्ठा snd_समयr *समयr)
अणु
	काष्ठा snd_ad1816a *chip = snd_समयr_chip(समयr);
	snd_ad1816a_खोलो(chip, AD1816A_MODE_TIMER);
	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ snd_ad1816a_समयr_resolution(काष्ठा snd_समयr *समयr)
अणु
	अगर (snd_BUG_ON(!समयr))
		वापस 0;

	वापस 10000;
पूर्ण

अटल पूर्णांक snd_ad1816a_समयr_start(काष्ठा snd_समयr *समयr)
अणु
	अचिन्हित लघु bits;
	अचिन्हित दीर्घ flags;
	काष्ठा snd_ad1816a *chip = snd_समयr_chip(समयr);
	spin_lock_irqsave(&chip->lock, flags);
	bits = snd_ad1816a_पढ़ो(chip, AD1816A_INTERRUPT_ENABLE);

	अगर (!(bits & AD1816A_TIMER_ENABLE)) अणु
		snd_ad1816a_ग_लिखो(chip, AD1816A_TIMER_BASE_COUNT,
			समयr->sticks & 0xffff);

		snd_ad1816a_ग_लिखो_mask(chip, AD1816A_INTERRUPT_ENABLE,
			AD1816A_TIMER_ENABLE, 0xffff);
	पूर्ण
	spin_unlock_irqrestore(&chip->lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ad1816a_समयr_stop(काष्ठा snd_समयr *समयr)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_ad1816a *chip = snd_समयr_chip(समयr);
	spin_lock_irqsave(&chip->lock, flags);

	snd_ad1816a_ग_लिखो_mask(chip, AD1816A_INTERRUPT_ENABLE,
		AD1816A_TIMER_ENABLE, 0x0000);

	spin_unlock_irqrestore(&chip->lock, flags);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_समयr_hardware snd_ad1816a_समयr_table = अणु
	.flags =	SNDRV_TIMER_HW_AUTO,
	.resolution =	10000,
	.ticks =	65535,
	.खोलो =		snd_ad1816a_समयr_खोलो,
	.बंद =	snd_ad1816a_समयr_बंद,
	.c_resolution =	snd_ad1816a_समयr_resolution,
	.start =	snd_ad1816a_समयr_start,
	.stop =		snd_ad1816a_समयr_stop,
पूर्ण;

अटल पूर्णांक snd_ad1816a_playback_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ad1816a *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक error;

	अगर ((error = snd_ad1816a_खोलो(chip, AD1816A_MODE_PLAYBACK)) < 0)
		वापस error;
	runसमय->hw = snd_ad1816a_playback;
	snd_pcm_limit_isa_dma_size(chip->dma1, &runसमय->hw.buffer_bytes_max);
	snd_pcm_limit_isa_dma_size(chip->dma1, &runसमय->hw.period_bytes_max);
	chip->playback_substream = substream;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ad1816a_capture_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ad1816a *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक error;

	अगर ((error = snd_ad1816a_खोलो(chip, AD1816A_MODE_CAPTURE)) < 0)
		वापस error;
	runसमय->hw = snd_ad1816a_capture;
	snd_pcm_limit_isa_dma_size(chip->dma2, &runसमय->hw.buffer_bytes_max);
	snd_pcm_limit_isa_dma_size(chip->dma2, &runसमय->hw.period_bytes_max);
	chip->capture_substream = substream;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ad1816a_playback_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ad1816a *chip = snd_pcm_substream_chip(substream);

	chip->playback_substream = शून्य;
	snd_ad1816a_बंद(chip, AD1816A_MODE_PLAYBACK);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ad1816a_capture_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ad1816a *chip = snd_pcm_substream_chip(substream);

	chip->capture_substream = शून्य;
	snd_ad1816a_बंद(chip, AD1816A_MODE_CAPTURE);
	वापस 0;
पूर्ण


अटल व्योम snd_ad1816a_init(काष्ठा snd_ad1816a *chip)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chip->lock, flags);

	snd_ad1816a_out(chip, AD1816A_INTERRUPT_STATUS, 0x00);
	snd_ad1816a_out_mask(chip, AD1816A_PLAYBACK_CONFIG,
		AD1816A_PLAYBACK_ENABLE | AD1816A_PLAYBACK_PIO, 0x00);
	snd_ad1816a_out_mask(chip, AD1816A_CAPTURE_CONFIG,
		AD1816A_CAPTURE_ENABLE | AD1816A_CAPTURE_PIO, 0x00);
	snd_ad1816a_ग_लिखो(chip, AD1816A_INTERRUPT_ENABLE, 0x0000);
	snd_ad1816a_ग_लिखो_mask(chip, AD1816A_CHIP_CONFIG,
		AD1816A_CAPTURE_NOT_EQUAL | AD1816A_WSS_ENABLE, 0xffff);
	snd_ad1816a_ग_लिखो(chip, AD1816A_DSP_CONFIG, 0x0000);
	snd_ad1816a_ग_लिखो(chip, AD1816A_POWERDOWN_CTRL, 0x0000);

	spin_unlock_irqrestore(&chip->lock, flags);
पूर्ण

#अगर_घोषित CONFIG_PM
व्योम snd_ad1816a_suspend(काष्ठा snd_ad1816a *chip)
अणु
	पूर्णांक reg;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chip->lock, flags);
	क्रम (reg = 0; reg < 48; reg++)
		chip->image[reg] = snd_ad1816a_पढ़ो(chip, reg);
	spin_unlock_irqrestore(&chip->lock, flags);
पूर्ण

व्योम snd_ad1816a_resume(काष्ठा snd_ad1816a *chip)
अणु
	पूर्णांक reg;
	अचिन्हित दीर्घ flags;

	snd_ad1816a_init(chip);
	spin_lock_irqsave(&chip->lock, flags);
	क्रम (reg = 0; reg < 48; reg++)
		snd_ad1816a_ग_लिखो(chip, reg, chip->image[reg]);
	spin_unlock_irqrestore(&chip->lock, flags);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक snd_ad1816a_probe(काष्ठा snd_ad1816a *chip)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chip->lock, flags);

	चयन (chip->version = snd_ad1816a_पढ़ो(chip, AD1816A_VERSION_ID)) अणु
	हाल 0:
		chip->hardware = AD1816A_HW_AD1815;
		अवरोध;
	हाल 1:
		chip->hardware = AD1816A_HW_AD18MAX10;
		अवरोध;
	हाल 3:
		chip->hardware = AD1816A_HW_AD1816A;
		अवरोध;
	शेष:
		chip->hardware = AD1816A_HW_AUTO;
	पूर्ण

	spin_unlock_irqrestore(&chip->lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ad1816a_मुक्त(काष्ठा snd_ad1816a *chip)
अणु
	release_and_मुक्त_resource(chip->res_port);
	अगर (chip->irq >= 0)
		मुक्त_irq(chip->irq, (व्योम *) chip);
	अगर (chip->dma1 >= 0) अणु
		snd_dma_disable(chip->dma1);
		मुक्त_dma(chip->dma1);
	पूर्ण
	अगर (chip->dma2 >= 0) अणु
		snd_dma_disable(chip->dma2);
		मुक्त_dma(chip->dma2);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ad1816a_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा snd_ad1816a *chip = device->device_data;
	वापस snd_ad1816a_मुक्त(chip);
पूर्ण

अटल स्थिर अक्षर *snd_ad1816a_chip_id(काष्ठा snd_ad1816a *chip)
अणु
	चयन (chip->hardware) अणु
	हाल AD1816A_HW_AD1816A: वापस "AD1816A";
	हाल AD1816A_HW_AD1815:	वापस "AD1815";
	हाल AD1816A_HW_AD18MAX10: वापस "AD18max10";
	शेष:
		snd_prपूर्णांकk(KERN_WARNING "Unknown chip version %d:%d.\n",
			chip->version, chip->hardware);
		वापस "AD1816A - unknown";
	पूर्ण
पूर्ण

पूर्णांक snd_ad1816a_create(काष्ठा snd_card *card,
		       अचिन्हित दीर्घ port, पूर्णांक irq, पूर्णांक dma1, पूर्णांक dma2,
		       काष्ठा snd_ad1816a *chip)
अणु
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त =	snd_ad1816a_dev_मुक्त,
	पूर्ण;
	पूर्णांक error;

	chip->irq = -1;
	chip->dma1 = -1;
	chip->dma2 = -1;

	अगर ((chip->res_port = request_region(port, 16, "AD1816A")) == शून्य) अणु
		snd_prपूर्णांकk(KERN_ERR "ad1816a: can't grab port 0x%lx\n", port);
		snd_ad1816a_मुक्त(chip);
		वापस -EBUSY;
	पूर्ण
	अगर (request_irq(irq, snd_ad1816a_पूर्णांकerrupt, 0, "AD1816A", (व्योम *) chip)) अणु
		snd_prपूर्णांकk(KERN_ERR "ad1816a: can't grab IRQ %d\n", irq);
		snd_ad1816a_मुक्त(chip);
		वापस -EBUSY;
	पूर्ण
	chip->irq = irq;
	card->sync_irq = chip->irq;
	अगर (request_dma(dma1, "AD1816A - 1")) अणु
		snd_prपूर्णांकk(KERN_ERR "ad1816a: can't grab DMA1 %d\n", dma1);
		snd_ad1816a_मुक्त(chip);
		वापस -EBUSY;
	पूर्ण
	chip->dma1 = dma1;
	अगर (request_dma(dma2, "AD1816A - 2")) अणु
		snd_prपूर्णांकk(KERN_ERR "ad1816a: can't grab DMA2 %d\n", dma2);
		snd_ad1816a_मुक्त(chip);
		वापस -EBUSY;
	पूर्ण
	chip->dma2 = dma2;

	chip->card = card;
	chip->port = port;
	spin_lock_init(&chip->lock);

	अगर ((error = snd_ad1816a_probe(chip))) अणु
		snd_ad1816a_मुक्त(chip);
		वापस error;
	पूर्ण

	snd_ad1816a_init(chip);

	/* Register device */
	अगर ((error = snd_device_new(card, SNDRV_DEV_LOWLEVEL, chip, &ops)) < 0) अणु
		snd_ad1816a_मुक्त(chip);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops snd_ad1816a_playback_ops = अणु
	.खोलो =		snd_ad1816a_playback_खोलो,
	.बंद =	snd_ad1816a_playback_बंद,
	.prepare =	snd_ad1816a_playback_prepare,
	.trigger =	snd_ad1816a_playback_trigger,
	.poपूर्णांकer =	snd_ad1816a_playback_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_ad1816a_capture_ops = अणु
	.खोलो =		snd_ad1816a_capture_खोलो,
	.बंद =	snd_ad1816a_capture_बंद,
	.prepare =	snd_ad1816a_capture_prepare,
	.trigger =	snd_ad1816a_capture_trigger,
	.poपूर्णांकer =	snd_ad1816a_capture_poपूर्णांकer,
पूर्ण;

पूर्णांक snd_ad1816a_pcm(काष्ठा snd_ad1816a *chip, पूर्णांक device)
अणु
	पूर्णांक error;
	काष्ठा snd_pcm *pcm;

	अगर ((error = snd_pcm_new(chip->card, "AD1816A", device, 1, 1, &pcm)))
		वापस error;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_ad1816a_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_ad1816a_capture_ops);

	pcm->निजी_data = chip;
	pcm->info_flags = (chip->dma1 == chip->dma2 ) ? SNDRV_PCM_INFO_JOINT_DUPLEX : 0;

	म_नकल(pcm->name, snd_ad1816a_chip_id(chip));
	snd_ad1816a_init(chip);

	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV, chip->card->dev,
				       64*1024, chip->dma1 > 3 || chip->dma2 > 3 ? 128*1024 : 64*1024);

	chip->pcm = pcm;
	वापस 0;
पूर्ण

पूर्णांक snd_ad1816a_समयr(काष्ठा snd_ad1816a *chip, पूर्णांक device)
अणु
	काष्ठा snd_समयr *समयr;
	काष्ठा snd_समयr_id tid;
	पूर्णांक error;

	tid.dev_class = SNDRV_TIMER_CLASS_CARD;
	tid.dev_sclass = SNDRV_TIMER_SCLASS_NONE;
	tid.card = chip->card->number;
	tid.device = device;
	tid.subdevice = 0;
	अगर ((error = snd_समयr_new(chip->card, "AD1816A", &tid, &समयr)) < 0)
		वापस error;
	म_नकल(समयr->name, snd_ad1816a_chip_id(chip));
	समयr->निजी_data = chip;
	chip->समयr = समयr;
	समयr->hw = snd_ad1816a_समयr_table;
	वापस 0;
पूर्ण

/*
 *
 */

अटल पूर्णांक snd_ad1816a_info_mux(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[8] = अणु
		"Line", "Mix", "CD", "Synth", "Video",
		"Mic", "Phone",
	पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 2, 7, texts);
पूर्ण

अटल पूर्णांक snd_ad1816a_get_mux(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ad1816a *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	अचिन्हित लघु val;
	
	spin_lock_irqsave(&chip->lock, flags);
	val = snd_ad1816a_पढ़ो(chip, AD1816A_ADC_SOURCE_SEL);
	spin_unlock_irqrestore(&chip->lock, flags);
	ucontrol->value.क्रमागतerated.item[0] = (val >> 12) & 7;
	ucontrol->value.क्रमागतerated.item[1] = (val >> 4) & 7;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ad1816a_put_mux(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ad1816a *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	अचिन्हित लघु val;
	पूर्णांक change;
	
	अगर (ucontrol->value.क्रमागतerated.item[0] > 6 ||
	    ucontrol->value.क्रमागतerated.item[1] > 6)
		वापस -EINVAL;
	val = (ucontrol->value.क्रमागतerated.item[0] << 12) |
	      (ucontrol->value.क्रमागतerated.item[1] << 4);
	spin_lock_irqsave(&chip->lock, flags);
	change = snd_ad1816a_पढ़ो(chip, AD1816A_ADC_SOURCE_SEL) != val;
	snd_ad1816a_ग_लिखो(chip, AD1816A_ADC_SOURCE_SEL, val);
	spin_unlock_irqrestore(&chip->lock, flags);
	वापस change;
पूर्ण

#घोषणा AD1816A_SINGLE_TLV(xname, reg, shअगरt, mask, invert, xtlv)	\
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
  .access = SNDRV_CTL_ELEM_ACCESS_READWRITE | SNDRV_CTL_ELEM_ACCESS_TLV_READ, \
  .name = xname, .info = snd_ad1816a_info_single, \
  .get = snd_ad1816a_get_single, .put = snd_ad1816a_put_single, \
  .निजी_value = reg | (shअगरt << 8) | (mask << 16) | (invert << 24), \
  .tlv = अणु .p = (xtlv) पूर्ण पूर्ण
#घोषणा AD1816A_SINGLE(xname, reg, shअगरt, mask, invert) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .info = snd_ad1816a_info_single, \
  .get = snd_ad1816a_get_single, .put = snd_ad1816a_put_single, \
  .निजी_value = reg | (shअगरt << 8) | (mask << 16) | (invert << 24) पूर्ण

अटल पूर्णांक snd_ad1816a_info_single(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	पूर्णांक mask = (kcontrol->निजी_value >> 16) & 0xff;

	uinfo->type = mask == 1 ? SNDRV_CTL_ELEM_TYPE_BOOLEAN : SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = mask;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ad1816a_get_single(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ad1816a *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	पूर्णांक reg = kcontrol->निजी_value & 0xff;
	पूर्णांक shअगरt = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक mask = (kcontrol->निजी_value >> 16) & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 24) & 0xff;
	
	spin_lock_irqsave(&chip->lock, flags);
	ucontrol->value.पूर्णांकeger.value[0] = (snd_ad1816a_पढ़ो(chip, reg) >> shअगरt) & mask;
	spin_unlock_irqrestore(&chip->lock, flags);
	अगर (invert)
		ucontrol->value.पूर्णांकeger.value[0] = mask - ucontrol->value.पूर्णांकeger.value[0];
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ad1816a_put_single(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ad1816a *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	पूर्णांक reg = kcontrol->निजी_value & 0xff;
	पूर्णांक shअगरt = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक mask = (kcontrol->निजी_value >> 16) & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 24) & 0xff;
	पूर्णांक change;
	अचिन्हित लघु old_val, val;
	
	val = (ucontrol->value.पूर्णांकeger.value[0] & mask);
	अगर (invert)
		val = mask - val;
	val <<= shअगरt;
	spin_lock_irqsave(&chip->lock, flags);
	old_val = snd_ad1816a_पढ़ो(chip, reg);
	val = (old_val & ~(mask << shअगरt)) | val;
	change = val != old_val;
	snd_ad1816a_ग_लिखो(chip, reg, val);
	spin_unlock_irqrestore(&chip->lock, flags);
	वापस change;
पूर्ण

#घोषणा AD1816A_DOUBLE_TLV(xname, reg, shअगरt_left, shअगरt_right, mask, invert, xtlv) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
  .access = SNDRV_CTL_ELEM_ACCESS_READWRITE | SNDRV_CTL_ELEM_ACCESS_TLV_READ, \
  .name = xname, .info = snd_ad1816a_info_द्विगुन,		\
  .get = snd_ad1816a_get_द्विगुन, .put = snd_ad1816a_put_द्विगुन, \
  .निजी_value = reg | (shअगरt_left << 8) | (shअगरt_right << 12) | (mask << 16) | (invert << 24), \
  .tlv = अणु .p = (xtlv) पूर्ण पूर्ण

#घोषणा AD1816A_DOUBLE(xname, reg, shअगरt_left, shअगरt_right, mask, invert) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .info = snd_ad1816a_info_द्विगुन, \
  .get = snd_ad1816a_get_द्विगुन, .put = snd_ad1816a_put_द्विगुन, \
  .निजी_value = reg | (shअगरt_left << 8) | (shअगरt_right << 12) | (mask << 16) | (invert << 24) पूर्ण

अटल पूर्णांक snd_ad1816a_info_द्विगुन(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	पूर्णांक mask = (kcontrol->निजी_value >> 16) & 0xff;

	uinfo->type = mask == 1 ? SNDRV_CTL_ELEM_TYPE_BOOLEAN : SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = mask;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ad1816a_get_द्विगुन(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ad1816a *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	पूर्णांक reg = kcontrol->निजी_value & 0xff;
	पूर्णांक shअगरt_left = (kcontrol->निजी_value >> 8) & 0x0f;
	पूर्णांक shअगरt_right = (kcontrol->निजी_value >> 12) & 0x0f;
	पूर्णांक mask = (kcontrol->निजी_value >> 16) & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 24) & 0xff;
	अचिन्हित लघु val;
	
	spin_lock_irqsave(&chip->lock, flags);
	val = snd_ad1816a_पढ़ो(chip, reg);
	ucontrol->value.पूर्णांकeger.value[0] = (val >> shअगरt_left) & mask;
	ucontrol->value.पूर्णांकeger.value[1] = (val >> shअगरt_right) & mask;
	spin_unlock_irqrestore(&chip->lock, flags);
	अगर (invert) अणु
		ucontrol->value.पूर्णांकeger.value[0] = mask - ucontrol->value.पूर्णांकeger.value[0];
		ucontrol->value.पूर्णांकeger.value[1] = mask - ucontrol->value.पूर्णांकeger.value[1];
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ad1816a_put_द्विगुन(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ad1816a *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	पूर्णांक reg = kcontrol->निजी_value & 0xff;
	पूर्णांक shअगरt_left = (kcontrol->निजी_value >> 8) & 0x0f;
	पूर्णांक shअगरt_right = (kcontrol->निजी_value >> 12) & 0x0f;
	पूर्णांक mask = (kcontrol->निजी_value >> 16) & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 24) & 0xff;
	पूर्णांक change;
	अचिन्हित लघु old_val, val1, val2;
	
	val1 = ucontrol->value.पूर्णांकeger.value[0] & mask;
	val2 = ucontrol->value.पूर्णांकeger.value[1] & mask;
	अगर (invert) अणु
		val1 = mask - val1;
		val2 = mask - val2;
	पूर्ण
	val1 <<= shअगरt_left;
	val2 <<= shअगरt_right;
	spin_lock_irqsave(&chip->lock, flags);
	old_val = snd_ad1816a_पढ़ो(chip, reg);
	val1 = (old_val & ~((mask << shअगरt_left) | (mask << shअगरt_right))) | val1 | val2;
	change = val1 != old_val;
	snd_ad1816a_ग_लिखो(chip, reg, val1);
	spin_unlock_irqrestore(&chip->lock, flags);
	वापस change;
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_4bit, -4500, 300, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_5bit, -4650, 150, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_6bit, -9450, 150, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_5bit_12db_max, -3450, 150, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_rec_gain, 0, 150, 0);

अटल स्थिर काष्ठा snd_kcontrol_new snd_ad1816a_controls[] = अणु
AD1816A_DOUBLE("Master Playback Switch", AD1816A_MASTER_ATT, 15, 7, 1, 1),
AD1816A_DOUBLE_TLV("Master Playback Volume", AD1816A_MASTER_ATT, 8, 0, 31, 1,
		   db_scale_5bit),
AD1816A_DOUBLE("PCM Playback Switch", AD1816A_VOICE_ATT, 15, 7, 1, 1),
AD1816A_DOUBLE_TLV("PCM Playback Volume", AD1816A_VOICE_ATT, 8, 0, 63, 1,
		   db_scale_6bit),
AD1816A_DOUBLE("Line Playback Switch", AD1816A_LINE_GAIN_ATT, 15, 7, 1, 1),
AD1816A_DOUBLE_TLV("Line Playback Volume", AD1816A_LINE_GAIN_ATT, 8, 0, 31, 1,
		   db_scale_5bit_12db_max),
AD1816A_DOUBLE("CD Playback Switch", AD1816A_CD_GAIN_ATT, 15, 7, 1, 1),
AD1816A_DOUBLE_TLV("CD Playback Volume", AD1816A_CD_GAIN_ATT, 8, 0, 31, 1,
		   db_scale_5bit_12db_max),
AD1816A_DOUBLE("Synth Playback Switch", AD1816A_SYNTH_GAIN_ATT, 15, 7, 1, 1),
AD1816A_DOUBLE_TLV("Synth Playback Volume", AD1816A_SYNTH_GAIN_ATT, 8, 0, 31, 1,
		   db_scale_5bit_12db_max),
AD1816A_DOUBLE("FM Playback Switch", AD1816A_FM_ATT, 15, 7, 1, 1),
AD1816A_DOUBLE_TLV("FM Playback Volume", AD1816A_FM_ATT, 8, 0, 63, 1,
		   db_scale_6bit),
AD1816A_SINGLE("Mic Playback Switch", AD1816A_MIC_GAIN_ATT, 15, 1, 1),
AD1816A_SINGLE_TLV("Mic Playback Volume", AD1816A_MIC_GAIN_ATT, 8, 31, 1,
		   db_scale_5bit_12db_max),
AD1816A_SINGLE("Mic Boost", AD1816A_MIC_GAIN_ATT, 14, 1, 0),
AD1816A_DOUBLE("Video Playback Switch", AD1816A_VID_GAIN_ATT, 15, 7, 1, 1),
AD1816A_DOUBLE_TLV("Video Playback Volume", AD1816A_VID_GAIN_ATT, 8, 0, 31, 1,
		   db_scale_5bit_12db_max),
AD1816A_SINGLE("Phone Capture Switch", AD1816A_PHONE_IN_GAIN_ATT, 15, 1, 1),
AD1816A_SINGLE_TLV("Phone Capture Volume", AD1816A_PHONE_IN_GAIN_ATT, 0, 15, 1,
		   db_scale_4bit),
AD1816A_SINGLE("Phone Playback Switch", AD1816A_PHONE_OUT_ATT, 7, 1, 1),
AD1816A_SINGLE_TLV("Phone Playback Volume", AD1816A_PHONE_OUT_ATT, 0, 31, 1,
		   db_scale_5bit),
अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Capture Source",
	.info = snd_ad1816a_info_mux,
	.get = snd_ad1816a_get_mux,
	.put = snd_ad1816a_put_mux,
पूर्ण,
AD1816A_DOUBLE("Capture Switch", AD1816A_ADC_PGA, 15, 7, 1, 1),
AD1816A_DOUBLE_TLV("Capture Volume", AD1816A_ADC_PGA, 8, 0, 15, 0,
		   db_scale_rec_gain),
AD1816A_SINGLE("3D Control - Switch", AD1816A_3D_PHAT_CTRL, 15, 1, 1),
AD1816A_SINGLE("3D Control - Level", AD1816A_3D_PHAT_CTRL, 0, 15, 0),
पूर्ण;
                                        
पूर्णांक snd_ad1816a_mixer(काष्ठा snd_ad1816a *chip)
अणु
	काष्ठा snd_card *card;
	अचिन्हित पूर्णांक idx;
	पूर्णांक err;

	अगर (snd_BUG_ON(!chip || !chip->card))
		वापस -EINVAL;

	card = chip->card;

	म_नकल(card->mixername, snd_ad1816a_chip_id(chip));

	क्रम (idx = 0; idx < ARRAY_SIZE(snd_ad1816a_controls); idx++) अणु
		अगर ((err = snd_ctl_add(card, snd_ctl_new1(&snd_ad1816a_controls[idx], chip))) < 0)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण
