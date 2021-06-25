<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *                   Uros Bizjak <uros@kss-loka.si>
 *
 *  Routines क्रम control of 8-bit SoundBlaster cards and clones
 *  Please note: I करोn't have access to old SB8 soundcards.
 *
 * --
 *
 * Thu Apr 29 20:36:17 BST 1999 George David Morrison <gdm@gedamo.demon.co.uk>
 *   DSP can't respond to commands whilst in "high speed" mode. Caused 
 *   glitching during playback. Fixed.
 *
 * Wed Jul 12 22:02:55 CEST 2000 Uros Bizjak <uros@kss-loka.si>
 *   Cleaned up and rewrote lowlevel routines.
 */

#समावेश <linux/पन.स>
#समावेश <यंत्र/dma.h>
#समावेश <linux/init.h>
#समावेश <linux/समय.स>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/sb.h>

MODULE_AUTHOR("Jaroslav Kysela <perex@perex.cz>, Uros Bizjak <uros@kss-loka.si>");
MODULE_DESCRIPTION("Routines for control of 8-bit SoundBlaster cards and clones");
MODULE_LICENSE("GPL");

#घोषणा SB8_CLOCK	1000000
#घोषणा SB8_DEN(v)	((SB8_CLOCK + (v) / 2) / (v))
#घोषणा SB8_RATE(v)	(SB8_CLOCK / SB8_DEN(v))

अटल स्थिर काष्ठा snd_ratnum घड़ी = अणु
	.num = SB8_CLOCK,
	.den_min = 1,
	.den_max = 256,
	.den_step = 1,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_ratnums hw_स्थिरraपूर्णांकs_घड़ी = अणु
	.nrats = 1,
	.rats = &घड़ी,
पूर्ण;

अटल स्थिर काष्ठा snd_ratnum stereo_घड़ीs[] = अणु
	अणु
		.num = SB8_CLOCK,
		.den_min = SB8_DEN(22050),
		.den_max = SB8_DEN(22050),
		.den_step = 1,
	पूर्ण,
	अणु
		.num = SB8_CLOCK,
		.den_min = SB8_DEN(11025),
		.den_max = SB8_DEN(11025),
		.den_step = 1,
	पूर्ण
पूर्ण;

अटल पूर्णांक snd_sb8_hw_स्थिरraपूर्णांक_rate_channels(काष्ठा snd_pcm_hw_params *params,
					       काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा snd_पूर्णांकerval *c = hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_CHANNELS);
	अगर (c->min > 1) अणु
	  	अचिन्हित पूर्णांक num = 0, den = 0;
		पूर्णांक err = snd_पूर्णांकerval_ratnum(hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_RATE),
					  2, stereo_घड़ीs, &num, &den);
		अगर (err >= 0 && den) अणु
			params->rate_num = num;
			params->rate_den = den;
		पूर्ण
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_sb8_hw_स्थिरraपूर्णांक_channels_rate(काष्ठा snd_pcm_hw_params *params,
					       काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा snd_पूर्णांकerval *r = hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_RATE);
	अगर (r->min > SB8_RATE(22050) || r->max <= SB8_RATE(11025)) अणु
		काष्ठा snd_पूर्णांकerval t = अणु .min = 1, .max = 1 पूर्ण;
		वापस snd_पूर्णांकerval_refine(hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_CHANNELS), &t);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_sb8_playback_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_sb *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अचिन्हित पूर्णांक mixreg, rate, size, count;
	अचिन्हित अक्षर क्रमmat;
	अचिन्हित अक्षर stereo = runसमय->channels > 1;
	पूर्णांक dma;

	rate = runसमय->rate;
	चयन (chip->hardware) अणु
	हाल SB_HW_JAZZ16:
		अगर (runसमय->क्रमmat == SNDRV_PCM_FORMAT_S16_LE) अणु
			अगर (chip->mode & SB_MODE_CAPTURE_16)
				वापस -EBUSY;
			अन्यथा
				chip->mode |= SB_MODE_PLAYBACK_16;
		पूर्ण
		chip->playback_क्रमmat = SB_DSP_LO_OUTPUT_AUTO;
		अवरोध;
	हाल SB_HW_PRO:
		अगर (runसमय->channels > 1) अणु
			अगर (snd_BUG_ON(rate != SB8_RATE(11025) &&
				       rate != SB8_RATE(22050)))
				वापस -EINVAL;
			chip->playback_क्रमmat = SB_DSP_HI_OUTPUT_AUTO;
			अवरोध;
		पूर्ण
		fallthrough;
	हाल SB_HW_201:
		अगर (rate > 23000) अणु
			chip->playback_क्रमmat = SB_DSP_HI_OUTPUT_AUTO;
			अवरोध;
		पूर्ण
		fallthrough;
	हाल SB_HW_20:
		chip->playback_क्रमmat = SB_DSP_LO_OUTPUT_AUTO;
		अवरोध;
	हाल SB_HW_10:
		chip->playback_क्रमmat = SB_DSP_OUTPUT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	अगर (chip->mode & SB_MODE_PLAYBACK_16) अणु
		क्रमmat = stereo ? SB_DSP_STEREO_16BIT : SB_DSP_MONO_16BIT;
		dma = chip->dma16;
	पूर्ण अन्यथा अणु
		क्रमmat = stereo ? SB_DSP_STEREO_8BIT : SB_DSP_MONO_8BIT;
		chip->mode |= SB_MODE_PLAYBACK_8;
		dma = chip->dma8;
	पूर्ण
	size = chip->p_dma_size = snd_pcm_lib_buffer_bytes(substream);
	count = chip->p_period_size = snd_pcm_lib_period_bytes(substream);
	spin_lock_irqsave(&chip->reg_lock, flags);
	snd_sbdsp_command(chip, SB_DSP_SPEAKER_ON);
	अगर (chip->hardware == SB_HW_JAZZ16)
		snd_sbdsp_command(chip, क्रमmat);
	अन्यथा अगर (stereo) अणु
		/* set playback stereo mode */
		spin_lock(&chip->mixer_lock);
		mixreg = snd_sbmixer_पढ़ो(chip, SB_DSP_STEREO_SW);
		snd_sbmixer_ग_लिखो(chip, SB_DSP_STEREO_SW, mixreg | 0x02);
		spin_unlock(&chip->mixer_lock);

		/* Soundblaster hardware programming reference guide, 3-23 */
		snd_sbdsp_command(chip, SB_DSP_DMA8_EXIT);
		runसमय->dma_area[0] = 0x80;
		snd_dma_program(dma, runसमय->dma_addr, 1, DMA_MODE_WRITE);
		/* क्रमce पूर्णांकerrupt */
		snd_sbdsp_command(chip, SB_DSP_OUTPUT);
		snd_sbdsp_command(chip, 0);
		snd_sbdsp_command(chip, 0);
	पूर्ण
	snd_sbdsp_command(chip, SB_DSP_SAMPLE_RATE);
	अगर (stereo) अणु
		snd_sbdsp_command(chip, 256 - runसमय->rate_den / 2);
		spin_lock(&chip->mixer_lock);
		/* save output filter status and turn it off */
		mixreg = snd_sbmixer_पढ़ो(chip, SB_DSP_PLAYBACK_FILT);
		snd_sbmixer_ग_लिखो(chip, SB_DSP_PLAYBACK_FILT, mixreg | 0x20);
		spin_unlock(&chip->mixer_lock);
		/* just use क्रमce_mode16 क्रम temporary storate... */
		chip->क्रमce_mode16 = mixreg;
	पूर्ण अन्यथा अणु
		snd_sbdsp_command(chip, 256 - runसमय->rate_den);
	पूर्ण
	अगर (chip->playback_क्रमmat != SB_DSP_OUTPUT) अणु
		अगर (chip->mode & SB_MODE_PLAYBACK_16)
			count /= 2;
		count--;
		snd_sbdsp_command(chip, SB_DSP_BLOCK_SIZE);
		snd_sbdsp_command(chip, count & 0xff);
		snd_sbdsp_command(chip, count >> 8);
	पूर्ण
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	snd_dma_program(dma, runसमय->dma_addr,
			size, DMA_MODE_WRITE | DMA_AUTOINIT);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_sb8_playback_trigger(काष्ठा snd_pcm_substream *substream,
				    पूर्णांक cmd)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_sb *chip = snd_pcm_substream_chip(substream);
	अचिन्हित पूर्णांक count;

	spin_lock_irqsave(&chip->reg_lock, flags);
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		snd_sbdsp_command(chip, chip->playback_क्रमmat);
		अगर (chip->playback_क्रमmat == SB_DSP_OUTPUT) अणु
			count = chip->p_period_size - 1;
			snd_sbdsp_command(chip, count & 0xff);
			snd_sbdsp_command(chip, count >> 8);
		पूर्ण
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		अगर (chip->playback_क्रमmat == SB_DSP_HI_OUTPUT_AUTO) अणु
			काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
			snd_sbdsp_reset(chip);
			अगर (runसमय->channels > 1) अणु
				spin_lock(&chip->mixer_lock);
				/* restore output filter and set hardware to mono mode */ 
				snd_sbmixer_ग_लिखो(chip, SB_DSP_STEREO_SW, chip->क्रमce_mode16 & ~0x02);
				spin_unlock(&chip->mixer_lock);
			पूर्ण
		पूर्ण अन्यथा अणु
			snd_sbdsp_command(chip, SB_DSP_DMA8_OFF);
		पूर्ण
		snd_sbdsp_command(chip, SB_DSP_SPEAKER_OFF);
	पूर्ण
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_sb8_capture_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_sb *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अचिन्हित पूर्णांक mixreg, rate, size, count;
	अचिन्हित अक्षर क्रमmat;
	अचिन्हित अक्षर stereo = runसमय->channels > 1;
	पूर्णांक dma;

	rate = runसमय->rate;
	चयन (chip->hardware) अणु
	हाल SB_HW_JAZZ16:
		अगर (runसमय->क्रमmat == SNDRV_PCM_FORMAT_S16_LE) अणु
			अगर (chip->mode & SB_MODE_PLAYBACK_16)
				वापस -EBUSY;
			अन्यथा
				chip->mode |= SB_MODE_CAPTURE_16;
		पूर्ण
		chip->capture_क्रमmat = SB_DSP_LO_INPUT_AUTO;
		अवरोध;
	हाल SB_HW_PRO:
		अगर (runसमय->channels > 1) अणु
			अगर (snd_BUG_ON(rate != SB8_RATE(11025) &&
				       rate != SB8_RATE(22050)))
				वापस -EINVAL;
			chip->capture_क्रमmat = SB_DSP_HI_INPUT_AUTO;
			अवरोध;
		पूर्ण
		chip->capture_क्रमmat = (rate > 23000) ? SB_DSP_HI_INPUT_AUTO : SB_DSP_LO_INPUT_AUTO;
		अवरोध;
	हाल SB_HW_201:
		अगर (rate > 13000) अणु
			chip->capture_क्रमmat = SB_DSP_HI_INPUT_AUTO;
			अवरोध;
		पूर्ण
		fallthrough;
	हाल SB_HW_20:
		chip->capture_क्रमmat = SB_DSP_LO_INPUT_AUTO;
		अवरोध;
	हाल SB_HW_10:
		chip->capture_क्रमmat = SB_DSP_INPUT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	अगर (chip->mode & SB_MODE_CAPTURE_16) अणु
		क्रमmat = stereo ? SB_DSP_STEREO_16BIT : SB_DSP_MONO_16BIT;
		dma = chip->dma16;
	पूर्ण अन्यथा अणु
		क्रमmat = stereo ? SB_DSP_STEREO_8BIT : SB_DSP_MONO_8BIT;
		chip->mode |= SB_MODE_CAPTURE_8;
		dma = chip->dma8;
	पूर्ण
	size = chip->c_dma_size = snd_pcm_lib_buffer_bytes(substream);
	count = chip->c_period_size = snd_pcm_lib_period_bytes(substream);
	spin_lock_irqsave(&chip->reg_lock, flags);
	snd_sbdsp_command(chip, SB_DSP_SPEAKER_OFF);
	अगर (chip->hardware == SB_HW_JAZZ16)
		snd_sbdsp_command(chip, क्रमmat);
	अन्यथा अगर (stereo)
		snd_sbdsp_command(chip, SB_DSP_STEREO_8BIT);
	snd_sbdsp_command(chip, SB_DSP_SAMPLE_RATE);
	अगर (stereo) अणु
		snd_sbdsp_command(chip, 256 - runसमय->rate_den / 2);
		spin_lock(&chip->mixer_lock);
		/* save input filter status and turn it off */
		mixreg = snd_sbmixer_पढ़ो(chip, SB_DSP_CAPTURE_FILT);
		snd_sbmixer_ग_लिखो(chip, SB_DSP_CAPTURE_FILT, mixreg | 0x20);
		spin_unlock(&chip->mixer_lock);
		/* just use क्रमce_mode16 क्रम temporary storate... */
		chip->क्रमce_mode16 = mixreg;
	पूर्ण अन्यथा अणु
		snd_sbdsp_command(chip, 256 - runसमय->rate_den);
	पूर्ण
	अगर (chip->capture_क्रमmat != SB_DSP_INPUT) अणु
		अगर (chip->mode & SB_MODE_PLAYBACK_16)
			count /= 2;
		count--;
		snd_sbdsp_command(chip, SB_DSP_BLOCK_SIZE);
		snd_sbdsp_command(chip, count & 0xff);
		snd_sbdsp_command(chip, count >> 8);
	पूर्ण
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	snd_dma_program(dma, runसमय->dma_addr,
			size, DMA_MODE_READ | DMA_AUTOINIT);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_sb8_capture_trigger(काष्ठा snd_pcm_substream *substream,
				   पूर्णांक cmd)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_sb *chip = snd_pcm_substream_chip(substream);
	अचिन्हित पूर्णांक count;

	spin_lock_irqsave(&chip->reg_lock, flags);
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		snd_sbdsp_command(chip, chip->capture_क्रमmat);
		अगर (chip->capture_क्रमmat == SB_DSP_INPUT) अणु
			count = chip->c_period_size - 1;
			snd_sbdsp_command(chip, count & 0xff);
			snd_sbdsp_command(chip, count >> 8);
		पूर्ण
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		अगर (chip->capture_क्रमmat == SB_DSP_HI_INPUT_AUTO) अणु
			काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
			snd_sbdsp_reset(chip);
			अगर (runसमय->channels > 1) अणु
				/* restore input filter status */
				spin_lock(&chip->mixer_lock);
				snd_sbmixer_ग_लिखो(chip, SB_DSP_CAPTURE_FILT, chip->क्रमce_mode16);
				spin_unlock(&chip->mixer_lock);
				/* set hardware to mono mode */
				snd_sbdsp_command(chip, SB_DSP_MONO_8BIT);
			पूर्ण
		पूर्ण अन्यथा अणु
			snd_sbdsp_command(chip, SB_DSP_DMA8_OFF);
		पूर्ण
		snd_sbdsp_command(chip, SB_DSP_SPEAKER_OFF);
	पूर्ण
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	वापस 0;
पूर्ण

irqवापस_t snd_sb8dsp_पूर्णांकerrupt(काष्ठा snd_sb *chip)
अणु
	काष्ठा snd_pcm_substream *substream;

	snd_sb_ack_8bit(chip);
	चयन (chip->mode) अणु
	हाल SB_MODE_PLAYBACK_16:	/* ok.. playback is active */
		अगर (chip->hardware != SB_HW_JAZZ16)
			अवरोध;
		fallthrough;
	हाल SB_MODE_PLAYBACK_8:
		substream = chip->playback_substream;
		अगर (chip->playback_क्रमmat == SB_DSP_OUTPUT)
		    	snd_sb8_playback_trigger(substream, SNDRV_PCM_TRIGGER_START);
		snd_pcm_period_elapsed(substream);
		अवरोध;
	हाल SB_MODE_CAPTURE_16:
		अगर (chip->hardware != SB_HW_JAZZ16)
			अवरोध;
		fallthrough;
	हाल SB_MODE_CAPTURE_8:
		substream = chip->capture_substream;
		अगर (chip->capture_क्रमmat == SB_DSP_INPUT)
		    	snd_sb8_capture_trigger(substream, SNDRV_PCM_TRIGGER_START);
		snd_pcm_period_elapsed(substream);
		अवरोध;
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल snd_pcm_uframes_t snd_sb8_playback_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_sb *chip = snd_pcm_substream_chip(substream);
	माप_प्रकार ptr;
	पूर्णांक dma;

	अगर (chip->mode & SB_MODE_PLAYBACK_8)
		dma = chip->dma8;
	अन्यथा अगर (chip->mode & SB_MODE_PLAYBACK_16)
		dma = chip->dma16;
	अन्यथा
		वापस 0;
	ptr = snd_dma_poपूर्णांकer(dma, chip->p_dma_size);
	वापस bytes_to_frames(substream->runसमय, ptr);
पूर्ण

अटल snd_pcm_uframes_t snd_sb8_capture_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_sb *chip = snd_pcm_substream_chip(substream);
	माप_प्रकार ptr;
	पूर्णांक dma;

	अगर (chip->mode & SB_MODE_CAPTURE_8)
		dma = chip->dma8;
	अन्यथा अगर (chip->mode & SB_MODE_CAPTURE_16)
		dma = chip->dma16;
	अन्यथा
		वापस 0;
	ptr = snd_dma_poपूर्णांकer(dma, chip->c_dma_size);
	वापस bytes_to_frames(substream->runसमय, ptr);
पूर्ण

/*

 */

अटल स्थिर काष्ठा snd_pcm_hardware snd_sb8_playback =
अणु
	.info =			(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_MMAP_VALID),
	.क्रमmats =		 SNDRV_PCM_FMTBIT_U8,
	.rates =		(SNDRV_PCM_RATE_CONTINUOUS | SNDRV_PCM_RATE_8000 |
				 SNDRV_PCM_RATE_11025 | SNDRV_PCM_RATE_22050),
	.rate_min =		4000,
	.rate_max =		23000,
	.channels_min =		1,
	.channels_max =		1,
	.buffer_bytes_max =	65536,
	.period_bytes_min =	64,
	.period_bytes_max =	65536,
	.periods_min =		1,
	.periods_max =		1024,
	.fअगरo_size =		0,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware snd_sb8_capture =
अणु
	.info =			(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_MMAP_VALID),
	.क्रमmats =		SNDRV_PCM_FMTBIT_U8,
	.rates =		(SNDRV_PCM_RATE_CONTINUOUS | SNDRV_PCM_RATE_8000 |
				 SNDRV_PCM_RATE_11025),
	.rate_min =		4000,
	.rate_max =		13000,
	.channels_min =		1,
	.channels_max =		1,
	.buffer_bytes_max =	65536,
	.period_bytes_min =	64,
	.period_bytes_max =	65536,
	.periods_min =		1,
	.periods_max =		1024,
	.fअगरo_size =		0,
पूर्ण;

/*
 *
 */
 
अटल पूर्णांक snd_sb8_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_sb *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chip->खोलो_lock, flags);
	अगर (chip->खोलो) अणु
		spin_unlock_irqrestore(&chip->खोलो_lock, flags);
		वापस -EAGAIN;
	पूर्ण
	chip->खोलो |= SB_OPEN_PCM;
	spin_unlock_irqrestore(&chip->खोलो_lock, flags);
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		chip->playback_substream = substream;
		runसमय->hw = snd_sb8_playback;
	पूर्ण अन्यथा अणु
		chip->capture_substream = substream;
		runसमय->hw = snd_sb8_capture;
	पूर्ण
	चयन (chip->hardware) अणु
	हाल SB_HW_JAZZ16:
		अगर (chip->dma16 == 5 || chip->dma16 == 7)
			runसमय->hw.क्रमmats |= SNDRV_PCM_FMTBIT_S16_LE;
		runसमय->hw.rates |= SNDRV_PCM_RATE_8000_48000;
		runसमय->hw.rate_min = 4000;
		runसमय->hw.rate_max = 50000;
		runसमय->hw.channels_max = 2;
		अवरोध;
	हाल SB_HW_PRO:
		runसमय->hw.rate_max = 44100;
		runसमय->hw.channels_max = 2;
		snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
				    snd_sb8_hw_स्थिरraपूर्णांक_rate_channels, शून्य,
				    SNDRV_PCM_HW_PARAM_CHANNELS,
				    SNDRV_PCM_HW_PARAM_RATE, -1);
		snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
				     snd_sb8_hw_स्थिरraपूर्णांक_channels_rate, शून्य,
				     SNDRV_PCM_HW_PARAM_RATE, -1);
		अवरोध;
	हाल SB_HW_201:
		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
			runसमय->hw.rate_max = 44100;
		पूर्ण अन्यथा अणु
			runसमय->hw.rate_max = 15000;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	snd_pcm_hw_स्थिरraपूर्णांक_ratnums(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
				      &hw_स्थिरraपूर्णांकs_घड़ी);
	अगर (chip->dma8 > 3 || chip->dma16 >= 0) अणु
		snd_pcm_hw_स्थिरraपूर्णांक_step(runसमय, 0,
					   SNDRV_PCM_HW_PARAM_BUFFER_BYTES, 2);
		snd_pcm_hw_स्थिरraपूर्णांक_step(runसमय, 0,
					   SNDRV_PCM_HW_PARAM_PERIOD_BYTES, 2);
		runसमय->hw.buffer_bytes_max = 128 * 1024 * 1024;
		runसमय->hw.period_bytes_max = 128 * 1024 * 1024;
	पूर्ण
	वापस 0;	
पूर्ण

अटल पूर्णांक snd_sb8_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_sb *chip = snd_pcm_substream_chip(substream);

	chip->playback_substream = शून्य;
	chip->capture_substream = शून्य;
	spin_lock_irqsave(&chip->खोलो_lock, flags);
	chip->खोलो &= ~SB_OPEN_PCM;
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		chip->mode &= ~SB_MODE_PLAYBACK;
	अन्यथा
		chip->mode &= ~SB_MODE_CAPTURE;
	spin_unlock_irqrestore(&chip->खोलो_lock, flags);
	वापस 0;
पूर्ण

/*
 *  Initialization part
 */
 
अटल स्थिर काष्ठा snd_pcm_ops snd_sb8_playback_ops = अणु
	.खोलो =			snd_sb8_खोलो,
	.बंद =		snd_sb8_बंद,
	.prepare =		snd_sb8_playback_prepare,
	.trigger =		snd_sb8_playback_trigger,
	.poपूर्णांकer =		snd_sb8_playback_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_sb8_capture_ops = अणु
	.खोलो =			snd_sb8_खोलो,
	.बंद =		snd_sb8_बंद,
	.prepare =		snd_sb8_capture_prepare,
	.trigger =		snd_sb8_capture_trigger,
	.poपूर्णांकer =		snd_sb8_capture_poपूर्णांकer,
पूर्ण;

पूर्णांक snd_sb8dsp_pcm(काष्ठा snd_sb *chip, पूर्णांक device)
अणु
	काष्ठा snd_card *card = chip->card;
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;
	माप_प्रकार max_pपुनः_स्मृति = 64 * 1024;

	अगर ((err = snd_pcm_new(card, "SB8 DSP", device, 1, 1, &pcm)) < 0)
		वापस err;
	प्र_लिखो(pcm->name, "DSP v%i.%i", chip->version >> 8, chip->version & 0xff);
	pcm->info_flags = SNDRV_PCM_INFO_HALF_DUPLEX;
	pcm->निजी_data = chip;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_sb8_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_sb8_capture_ops);

	अगर (chip->dma8 > 3 || chip->dma16 >= 0)
		max_pपुनः_स्मृति = 128 * 1024;
	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV,
				       card->dev, 64*1024, max_pपुनः_स्मृति);

	वापस 0;
पूर्ण

EXPORT_SYMBOL(snd_sb8dsp_pcm);
EXPORT_SYMBOL(snd_sb8dsp_पूर्णांकerrupt);
  /* sb8_midi.c */
EXPORT_SYMBOL(snd_sb8dsp_midi_पूर्णांकerrupt);
EXPORT_SYMBOL(snd_sb8dsp_midi);
