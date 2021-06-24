<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *  Routines क्रम control of 16-bit SoundBlaster cards and clones
 *  Note: This is very ugly hardware which uses one 8-bit DMA channel and
 *        second 16-bit DMA channel. Unक्रमtunately 8-bit DMA channel can't
 *        transfer 16-bit samples and 16-bit DMA channels can't transfer
 *        8-bit samples. This make full duplex more complicated than
 *        can be... People, करोn't buy these soundcards क्रम full 16-bit
 *        duplex!!!
 *  Note: 16-bit wide is asचिन्हित to first direction which made request.
 *        With full duplex - playback is preferred with असलtract layer.
 *
 *  Note: Some chip revisions have hardware bug. Changing capture
 *        channel from full-duplex 8bit DMA to 16bit DMA will block
 *        16bit DMA transfers from DSP chip (capture) until 8bit transfer
 *        to DSP chip (playback) starts. This bug can be aव्योमed with
 *        "16bit DMA Allocation" setting set to Playback or Capture.
 */

#समावेश <linux/पन.स>
#समावेश <यंत्र/dma.h>
#समावेश <linux/init.h>
#समावेश <linux/समय.स>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/sb.h>
#समावेश <sound/sb16_csp.h>
#समावेश <sound/mpu401.h>
#समावेश <sound/control.h>
#समावेश <sound/info.h>

MODULE_AUTHOR("Jaroslav Kysela <perex@perex.cz>");
MODULE_DESCRIPTION("Routines for control of 16-bit SoundBlaster cards and clones");
MODULE_LICENSE("GPL");

#घोषणा runसमय_क्रमmat_bits(runसमय) \
	((अचिन्हित पूर्णांक)pcm_क्रमmat_to_bits((runसमय)->क्रमmat))

#अगर_घोषित CONFIG_SND_SB16_CSP
अटल व्योम snd_sb16_csp_playback_prepare(काष्ठा snd_sb *chip, काष्ठा snd_pcm_runसमय *runसमय)
अणु
	अगर (chip->hardware == SB_HW_16CSP) अणु
		काष्ठा snd_sb_csp *csp = chip->csp;

		अगर (csp->running & SNDRV_SB_CSP_ST_LOADED) अणु
			/* manually loaded codec */
			अगर ((csp->mode & SNDRV_SB_CSP_MODE_DSP_WRITE) &&
			    (runसमय_क्रमmat_bits(runसमय) == csp->acc_क्रमmat)) अणु
				/* Supported runसमय PCM क्रमmat क्रम playback */
				अगर (csp->ops.csp_use(csp) == 0) अणु
					/* If CSP was successfully acquired */
					जाओ __start_CSP;
				पूर्ण
			पूर्ण अन्यथा अगर ((csp->mode & SNDRV_SB_CSP_MODE_QSOUND) && (csp->q_enabled)) अणु
				/* QSound decoder is loaded and enabled */
				अगर (runसमय_क्रमmat_bits(runसमय) & (SNDRV_PCM_FMTBIT_S8 | SNDRV_PCM_FMTBIT_U8 |
							      SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_U16_LE)) अणु
					/* Only क्रम simple PCM क्रमmats */
					अगर (csp->ops.csp_use(csp) == 0) अणु
						/* If CSP was successfully acquired */
						जाओ __start_CSP;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अगर (csp->ops.csp_use(csp) == 0) अणु
			/* Acquire CSP and try to स्वतःload hardware codec */
			अगर (csp->ops.csp_स्वतःload(csp, runसमय->क्रमmat, SNDRV_SB_CSP_MODE_DSP_WRITE)) अणु
				/* Unsupported क्रमmat, release CSP */
				csp->ops.csp_unuse(csp);
			पूर्ण अन्यथा अणु
		      __start_CSP:
				/* Try to start CSP */
				अगर (csp->ops.csp_start(csp, (chip->mode & SB_MODE_PLAYBACK_16) ?
						       SNDRV_SB_CSP_SAMPLE_16BIT : SNDRV_SB_CSP_SAMPLE_8BIT,
						       (runसमय->channels > 1) ?
						       SNDRV_SB_CSP_STEREO : SNDRV_SB_CSP_MONO)) अणु
					/* Failed, release CSP */
					csp->ops.csp_unuse(csp);
				पूर्ण अन्यथा अणु
					/* Success, CSP acquired and running */
					chip->खोलो = SNDRV_SB_CSP_MODE_DSP_WRITE;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम snd_sb16_csp_capture_prepare(काष्ठा snd_sb *chip, काष्ठा snd_pcm_runसमय *runसमय)
अणु
	अगर (chip->hardware == SB_HW_16CSP) अणु
		काष्ठा snd_sb_csp *csp = chip->csp;

		अगर (csp->running & SNDRV_SB_CSP_ST_LOADED) अणु
			/* manually loaded codec */
			अगर ((csp->mode & SNDRV_SB_CSP_MODE_DSP_READ) &&
			    (runसमय_क्रमmat_bits(runसमय) == csp->acc_क्रमmat)) अणु
				/* Supported runसमय PCM क्रमmat क्रम capture */
				अगर (csp->ops.csp_use(csp) == 0) अणु
					/* If CSP was successfully acquired */
					जाओ __start_CSP;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अगर (csp->ops.csp_use(csp) == 0) अणु
			/* Acquire CSP and try to स्वतःload hardware codec */
			अगर (csp->ops.csp_स्वतःload(csp, runसमय->क्रमmat, SNDRV_SB_CSP_MODE_DSP_READ)) अणु
				/* Unsupported क्रमmat, release CSP */
				csp->ops.csp_unuse(csp);
			पूर्ण अन्यथा अणु
		      __start_CSP:
				/* Try to start CSP */
				अगर (csp->ops.csp_start(csp, (chip->mode & SB_MODE_CAPTURE_16) ?
						       SNDRV_SB_CSP_SAMPLE_16BIT : SNDRV_SB_CSP_SAMPLE_8BIT,
						       (runसमय->channels > 1) ?
						       SNDRV_SB_CSP_STEREO : SNDRV_SB_CSP_MONO)) अणु
					/* Failed, release CSP */
					csp->ops.csp_unuse(csp);
				पूर्ण अन्यथा अणु
					/* Success, CSP acquired and running */
					chip->खोलो = SNDRV_SB_CSP_MODE_DSP_READ;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम snd_sb16_csp_update(काष्ठा snd_sb *chip)
अणु
	अगर (chip->hardware == SB_HW_16CSP) अणु
		काष्ठा snd_sb_csp *csp = chip->csp;

		अगर (csp->qpos_changed) अणु
			spin_lock(&chip->reg_lock);
			csp->ops.csp_qsound_transfer (csp);
			spin_unlock(&chip->reg_lock);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम snd_sb16_csp_playback_खोलो(काष्ठा snd_sb *chip, काष्ठा snd_pcm_runसमय *runसमय)
अणु
	/* CSP decoders (QSound excluded) support only 16bit transfers */
	अगर (chip->hardware == SB_HW_16CSP) अणु
		काष्ठा snd_sb_csp *csp = chip->csp;

		अगर (csp->running & SNDRV_SB_CSP_ST_LOADED) अणु
			/* manually loaded codec */
			अगर (csp->mode & SNDRV_SB_CSP_MODE_DSP_WRITE) अणु
				runसमय->hw.क्रमmats |= csp->acc_क्रमmat;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* स्वतःloaded codecs */
			runसमय->hw.क्रमmats |= SNDRV_PCM_FMTBIT_MU_LAW | SNDRV_PCM_FMTBIT_A_LAW |
					       SNDRV_PCM_FMTBIT_IMA_ADPCM;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम snd_sb16_csp_playback_बंद(काष्ठा snd_sb *chip)
अणु
	अगर ((chip->hardware == SB_HW_16CSP) && (chip->खोलो == SNDRV_SB_CSP_MODE_DSP_WRITE)) अणु
		काष्ठा snd_sb_csp *csp = chip->csp;

		अगर (csp->ops.csp_stop(csp) == 0) अणु
			csp->ops.csp_unuse(csp);
			chip->खोलो = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम snd_sb16_csp_capture_खोलो(काष्ठा snd_sb *chip, काष्ठा snd_pcm_runसमय *runसमय)
अणु
	/* CSP coders support only 16bit transfers */
	अगर (chip->hardware == SB_HW_16CSP) अणु
		काष्ठा snd_sb_csp *csp = chip->csp;

		अगर (csp->running & SNDRV_SB_CSP_ST_LOADED) अणु
			/* manually loaded codec */
			अगर (csp->mode & SNDRV_SB_CSP_MODE_DSP_READ) अणु
				runसमय->hw.क्रमmats |= csp->acc_क्रमmat;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* स्वतःloaded codecs */
			runसमय->hw.क्रमmats |= SNDRV_PCM_FMTBIT_MU_LAW | SNDRV_PCM_FMTBIT_A_LAW |
					       SNDRV_PCM_FMTBIT_IMA_ADPCM;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम snd_sb16_csp_capture_बंद(काष्ठा snd_sb *chip)
अणु
	अगर ((chip->hardware == SB_HW_16CSP) && (chip->खोलो == SNDRV_SB_CSP_MODE_DSP_READ)) अणु
		काष्ठा snd_sb_csp *csp = chip->csp;

		अगर (csp->ops.csp_stop(csp) == 0) अणु
			csp->ops.csp_unuse(csp);
			chip->खोलो = 0;
		पूर्ण
	पूर्ण
पूर्ण
#अन्यथा
#घोषणा snd_sb16_csp_playback_prepare(chip, runसमय)	/*nop*/
#घोषणा snd_sb16_csp_capture_prepare(chip, runसमय)	/*nop*/
#घोषणा snd_sb16_csp_update(chip)			/*nop*/
#घोषणा snd_sb16_csp_playback_खोलो(chip, runसमय)	/*nop*/
#घोषणा snd_sb16_csp_playback_बंद(chip)		/*nop*/
#घोषणा snd_sb16_csp_capture_खोलो(chip, runसमय)	/*nop*/
#घोषणा snd_sb16_csp_capture_बंद(chip)      	 	/*nop*/
#पूर्ण_अगर


अटल व्योम snd_sb16_setup_rate(काष्ठा snd_sb *chip,
				अचिन्हित लघु rate,
				पूर्णांक channel)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chip->reg_lock, flags);
	अगर (chip->mode & (channel == SNDRV_PCM_STREAM_PLAYBACK ? SB_MODE_PLAYBACK_16 : SB_MODE_CAPTURE_16))
		snd_sb_ack_16bit(chip);
	अन्यथा
		snd_sb_ack_8bit(chip);
	अगर (!(chip->mode & SB_RATE_LOCK)) अणु
		chip->locked_rate = rate;
		snd_sbdsp_command(chip, SB_DSP_SAMPLE_RATE_IN);
		snd_sbdsp_command(chip, rate >> 8);
		snd_sbdsp_command(chip, rate & 0xff);
		snd_sbdsp_command(chip, SB_DSP_SAMPLE_RATE_OUT);
		snd_sbdsp_command(chip, rate >> 8);
		snd_sbdsp_command(chip, rate & 0xff);
	पूर्ण
	spin_unlock_irqrestore(&chip->reg_lock, flags);
पूर्ण

अटल पूर्णांक snd_sb16_playback_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_sb *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अचिन्हित अक्षर क्रमmat;
	अचिन्हित पूर्णांक size, count, dma;

	snd_sb16_csp_playback_prepare(chip, runसमय);
	अगर (snd_pcm_क्रमmat_अचिन्हित(runसमय->क्रमmat) > 0) अणु
		क्रमmat = runसमय->channels > 1 ? SB_DSP4_MODE_UNS_STEREO : SB_DSP4_MODE_UNS_MONO;
	पूर्ण अन्यथा अणु
		क्रमmat = runसमय->channels > 1 ? SB_DSP4_MODE_SIGN_STEREO : SB_DSP4_MODE_SIGN_MONO;
	पूर्ण

	snd_sb16_setup_rate(chip, runसमय->rate, SNDRV_PCM_STREAM_PLAYBACK);
	size = chip->p_dma_size = snd_pcm_lib_buffer_bytes(substream);
	dma = (chip->mode & SB_MODE_PLAYBACK_8) ? chip->dma8 : chip->dma16;
	snd_dma_program(dma, runसमय->dma_addr, size, DMA_MODE_WRITE | DMA_AUTOINIT);

	count = snd_pcm_lib_period_bytes(substream);
	spin_lock_irqsave(&chip->reg_lock, flags);
	अगर (chip->mode & SB_MODE_PLAYBACK_16) अणु
		count >>= 1;
		count--;
		snd_sbdsp_command(chip, SB_DSP4_OUT16_AI);
		snd_sbdsp_command(chip, क्रमmat);
		snd_sbdsp_command(chip, count & 0xff);
		snd_sbdsp_command(chip, count >> 8);
		snd_sbdsp_command(chip, SB_DSP_DMA16_OFF);
	पूर्ण अन्यथा अणु
		count--;
		snd_sbdsp_command(chip, SB_DSP4_OUT8_AI);
		snd_sbdsp_command(chip, क्रमmat);
		snd_sbdsp_command(chip, count & 0xff);
		snd_sbdsp_command(chip, count >> 8);
		snd_sbdsp_command(chip, SB_DSP_DMA8_OFF);
	पूर्ण
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_sb16_playback_trigger(काष्ठा snd_pcm_substream *substream,
				     पूर्णांक cmd)
अणु
	काष्ठा snd_sb *chip = snd_pcm_substream_chip(substream);
	पूर्णांक result = 0;

	spin_lock(&chip->reg_lock);
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		chip->mode |= SB_RATE_LOCK_PLAYBACK;
		snd_sbdsp_command(chip, chip->mode & SB_MODE_PLAYBACK_16 ? SB_DSP_DMA16_ON : SB_DSP_DMA8_ON);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		snd_sbdsp_command(chip, chip->mode & SB_MODE_PLAYBACK_16 ? SB_DSP_DMA16_OFF : SB_DSP_DMA8_OFF);
		/* next two lines are needed क्रम some types of DSP4 (SB AWE 32 - 4.13) */
		अगर (chip->mode & SB_RATE_LOCK_CAPTURE)
			snd_sbdsp_command(chip, chip->mode & SB_MODE_CAPTURE_16 ? SB_DSP_DMA16_ON : SB_DSP_DMA8_ON);
		chip->mode &= ~SB_RATE_LOCK_PLAYBACK;
		अवरोध;
	शेष:
		result = -EINVAL;
	पूर्ण
	spin_unlock(&chip->reg_lock);
	वापस result;
पूर्ण

अटल पूर्णांक snd_sb16_capture_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_sb *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अचिन्हित अक्षर क्रमmat;
	अचिन्हित पूर्णांक size, count, dma;

	snd_sb16_csp_capture_prepare(chip, runसमय);
	अगर (snd_pcm_क्रमmat_अचिन्हित(runसमय->क्रमmat) > 0) अणु
		क्रमmat = runसमय->channels > 1 ? SB_DSP4_MODE_UNS_STEREO : SB_DSP4_MODE_UNS_MONO;
	पूर्ण अन्यथा अणु
		क्रमmat = runसमय->channels > 1 ? SB_DSP4_MODE_SIGN_STEREO : SB_DSP4_MODE_SIGN_MONO;
	पूर्ण
	snd_sb16_setup_rate(chip, runसमय->rate, SNDRV_PCM_STREAM_CAPTURE);
	size = chip->c_dma_size = snd_pcm_lib_buffer_bytes(substream);
	dma = (chip->mode & SB_MODE_CAPTURE_8) ? chip->dma8 : chip->dma16;
	snd_dma_program(dma, runसमय->dma_addr, size, DMA_MODE_READ | DMA_AUTOINIT);

	count = snd_pcm_lib_period_bytes(substream);
	spin_lock_irqsave(&chip->reg_lock, flags);
	अगर (chip->mode & SB_MODE_CAPTURE_16) अणु
		count >>= 1;
		count--;
		snd_sbdsp_command(chip, SB_DSP4_IN16_AI);
		snd_sbdsp_command(chip, क्रमmat);
		snd_sbdsp_command(chip, count & 0xff);
		snd_sbdsp_command(chip, count >> 8);
		snd_sbdsp_command(chip, SB_DSP_DMA16_OFF);
	पूर्ण अन्यथा अणु
		count--;
		snd_sbdsp_command(chip, SB_DSP4_IN8_AI);
		snd_sbdsp_command(chip, क्रमmat);
		snd_sbdsp_command(chip, count & 0xff);
		snd_sbdsp_command(chip, count >> 8);
		snd_sbdsp_command(chip, SB_DSP_DMA8_OFF);
	पूर्ण
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_sb16_capture_trigger(काष्ठा snd_pcm_substream *substream,
				    पूर्णांक cmd)
अणु
	काष्ठा snd_sb *chip = snd_pcm_substream_chip(substream);
	पूर्णांक result = 0;

	spin_lock(&chip->reg_lock);
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		chip->mode |= SB_RATE_LOCK_CAPTURE;
		snd_sbdsp_command(chip, chip->mode & SB_MODE_CAPTURE_16 ? SB_DSP_DMA16_ON : SB_DSP_DMA8_ON);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		snd_sbdsp_command(chip, chip->mode & SB_MODE_CAPTURE_16 ? SB_DSP_DMA16_OFF : SB_DSP_DMA8_OFF);
		/* next two lines are needed क्रम some types of DSP4 (SB AWE 32 - 4.13) */
		अगर (chip->mode & SB_RATE_LOCK_PLAYBACK)
			snd_sbdsp_command(chip, chip->mode & SB_MODE_PLAYBACK_16 ? SB_DSP_DMA16_ON : SB_DSP_DMA8_ON);
		chip->mode &= ~SB_RATE_LOCK_CAPTURE;
		अवरोध;
	शेष:
		result = -EINVAL;
	पूर्ण
	spin_unlock(&chip->reg_lock);
	वापस result;
पूर्ण

irqवापस_t snd_sb16dsp_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा snd_sb *chip = dev_id;
	अचिन्हित अक्षर status;
	पूर्णांक ok;

	spin_lock(&chip->mixer_lock);
	status = snd_sbmixer_पढ़ो(chip, SB_DSP4_IRQSTATUS);
	spin_unlock(&chip->mixer_lock);
	अगर ((status & SB_IRQTYPE_MPUIN) && chip->rmidi_callback)
		chip->rmidi_callback(irq, chip->rmidi->निजी_data);
	अगर (status & SB_IRQTYPE_8BIT) अणु
		ok = 0;
		अगर (chip->mode & SB_MODE_PLAYBACK_8) अणु
			snd_pcm_period_elapsed(chip->playback_substream);
			snd_sb16_csp_update(chip);
			ok++;
		पूर्ण
		अगर (chip->mode & SB_MODE_CAPTURE_8) अणु
			snd_pcm_period_elapsed(chip->capture_substream);
			ok++;
		पूर्ण
		spin_lock(&chip->reg_lock);
		अगर (!ok)
			snd_sbdsp_command(chip, SB_DSP_DMA8_OFF);
		snd_sb_ack_8bit(chip);
		spin_unlock(&chip->reg_lock);
	पूर्ण
	अगर (status & SB_IRQTYPE_16BIT) अणु
		ok = 0;
		अगर (chip->mode & SB_MODE_PLAYBACK_16) अणु
			snd_pcm_period_elapsed(chip->playback_substream);
			snd_sb16_csp_update(chip);
			ok++;
		पूर्ण
		अगर (chip->mode & SB_MODE_CAPTURE_16) अणु
			snd_pcm_period_elapsed(chip->capture_substream);
			ok++;
		पूर्ण
		spin_lock(&chip->reg_lock);
		अगर (!ok)
			snd_sbdsp_command(chip, SB_DSP_DMA16_OFF);
		snd_sb_ack_16bit(chip);
		spin_unlock(&chip->reg_lock);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

/*

 */

अटल snd_pcm_uframes_t snd_sb16_playback_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_sb *chip = snd_pcm_substream_chip(substream);
	अचिन्हित पूर्णांक dma;
	माप_प्रकार ptr;

	dma = (chip->mode & SB_MODE_PLAYBACK_8) ? chip->dma8 : chip->dma16;
	ptr = snd_dma_poपूर्णांकer(dma, chip->p_dma_size);
	वापस bytes_to_frames(substream->runसमय, ptr);
पूर्ण

अटल snd_pcm_uframes_t snd_sb16_capture_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_sb *chip = snd_pcm_substream_chip(substream);
	अचिन्हित पूर्णांक dma;
	माप_प्रकार ptr;

	dma = (chip->mode & SB_MODE_CAPTURE_8) ? chip->dma8 : chip->dma16;
	ptr = snd_dma_poपूर्णांकer(dma, chip->c_dma_size);
	वापस bytes_to_frames(substream->runसमय, ptr);
पूर्ण

/*

 */

अटल स्थिर काष्ठा snd_pcm_hardware snd_sb16_playback =
अणु
	.info =			(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_MMAP_VALID),
	.क्रमmats =		0,
	.rates =		SNDRV_PCM_RATE_CONTINUOUS | SNDRV_PCM_RATE_8000_44100,
	.rate_min =		4000,
	.rate_max =		44100,
	.channels_min =		1,
	.channels_max =		2,
	.buffer_bytes_max =	(128*1024),
	.period_bytes_min =	64,
	.period_bytes_max =	(128*1024),
	.periods_min =		1,
	.periods_max =		1024,
	.fअगरo_size =		0,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware snd_sb16_capture =
अणु
	.info =			(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_MMAP_VALID),
	.क्रमmats =		0,
	.rates =		SNDRV_PCM_RATE_CONTINUOUS | SNDRV_PCM_RATE_8000_44100,
	.rate_min =		4000,
	.rate_max =		44100,
	.channels_min =		1,
	.channels_max =		2,
	.buffer_bytes_max =	(128*1024),
	.period_bytes_min =	64,
	.period_bytes_max =	(128*1024),
	.periods_min =		1,
	.periods_max =		1024,
	.fअगरo_size =		0,
पूर्ण;

/*
 *  खोलो/बंद
 */

अटल पूर्णांक snd_sb16_playback_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_sb *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	spin_lock_irqsave(&chip->खोलो_lock, flags);
	अगर (chip->mode & SB_MODE_PLAYBACK) अणु
		spin_unlock_irqrestore(&chip->खोलो_lock, flags);
		वापस -EAGAIN;
	पूर्ण
	runसमय->hw = snd_sb16_playback;

	/* skip अगर 16 bit DMA was reserved क्रम capture */
	अगर (chip->क्रमce_mode16 & SB_MODE_CAPTURE_16)
		जाओ __skip_16bit;

	अगर (chip->dma16 >= 0 && !(chip->mode & SB_MODE_CAPTURE_16)) अणु
		chip->mode |= SB_MODE_PLAYBACK_16;
		runसमय->hw.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_U16_LE;
		/* Vibra16X hack */
		अगर (chip->dma16 <= 3) अणु
			runसमय->hw.buffer_bytes_max =
			runसमय->hw.period_bytes_max = 64 * 1024;
		पूर्ण अन्यथा अणु
			snd_sb16_csp_playback_खोलो(chip, runसमय);
		पूर्ण
		जाओ __खोलो_ok;
	पूर्ण

      __skip_16bit:
	अगर (chip->dma8 >= 0 && !(chip->mode & SB_MODE_CAPTURE_8)) अणु
		chip->mode |= SB_MODE_PLAYBACK_8;
		/* DSP v 4.xx can transfer 16bit data through 8bit DMA channel, SBHWPG 2-7 */
		अगर (chip->dma16 < 0) अणु
			runसमय->hw.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_U16_LE;
			chip->mode |= SB_MODE_PLAYBACK_16;
		पूर्ण अन्यथा अणु
			runसमय->hw.क्रमmats = SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S8;
		पूर्ण
		runसमय->hw.buffer_bytes_max =
		runसमय->hw.period_bytes_max = 64 * 1024;
		जाओ __खोलो_ok;
	पूर्ण
	spin_unlock_irqrestore(&chip->खोलो_lock, flags);
	वापस -EAGAIN;

      __खोलो_ok:
	अगर (chip->hardware == SB_HW_ALS100)
		runसमय->hw.rate_max = 48000;
	अगर (chip->hardware == SB_HW_CS5530) अणु
		runसमय->hw.buffer_bytes_max = 32 * 1024;
		runसमय->hw.periods_min = 2;
		runसमय->hw.rate_min = 44100;
	पूर्ण
	अगर (chip->mode & SB_RATE_LOCK)
		runसमय->hw.rate_min = runसमय->hw.rate_max = chip->locked_rate;
	chip->playback_substream = substream;
	spin_unlock_irqrestore(&chip->खोलो_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_sb16_playback_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_sb *chip = snd_pcm_substream_chip(substream);

	snd_sb16_csp_playback_बंद(chip);
	spin_lock_irqsave(&chip->खोलो_lock, flags);
	chip->playback_substream = शून्य;
	chip->mode &= ~SB_MODE_PLAYBACK;
	spin_unlock_irqrestore(&chip->खोलो_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_sb16_capture_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_sb *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	spin_lock_irqsave(&chip->खोलो_lock, flags);
	अगर (chip->mode & SB_MODE_CAPTURE) अणु
		spin_unlock_irqrestore(&chip->खोलो_lock, flags);
		वापस -EAGAIN;
	पूर्ण
	runसमय->hw = snd_sb16_capture;

	/* skip अगर 16 bit DMA was reserved क्रम playback */
	अगर (chip->क्रमce_mode16 & SB_MODE_PLAYBACK_16)
		जाओ __skip_16bit;

	अगर (chip->dma16 >= 0 && !(chip->mode & SB_MODE_PLAYBACK_16)) अणु
		chip->mode |= SB_MODE_CAPTURE_16;
		runसमय->hw.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_U16_LE;
		/* Vibra16X hack */
		अगर (chip->dma16 <= 3) अणु
			runसमय->hw.buffer_bytes_max =
			runसमय->hw.period_bytes_max = 64 * 1024;
		पूर्ण अन्यथा अणु
			snd_sb16_csp_capture_खोलो(chip, runसमय);
		पूर्ण
		जाओ __खोलो_ok;
	पूर्ण

      __skip_16bit:
	अगर (chip->dma8 >= 0 && !(chip->mode & SB_MODE_PLAYBACK_8)) अणु
		chip->mode |= SB_MODE_CAPTURE_8;
		/* DSP v 4.xx can transfer 16bit data through 8bit DMA channel, SBHWPG 2-7 */
		अगर (chip->dma16 < 0) अणु
			runसमय->hw.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_U16_LE;
			chip->mode |= SB_MODE_CAPTURE_16;
		पूर्ण अन्यथा अणु
			runसमय->hw.क्रमmats = SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S8;
		पूर्ण
		runसमय->hw.buffer_bytes_max =
		runसमय->hw.period_bytes_max = 64 * 1024;
		जाओ __खोलो_ok;
	पूर्ण
	spin_unlock_irqrestore(&chip->खोलो_lock, flags);
	वापस -EAGAIN;

      __खोलो_ok:
	अगर (chip->hardware == SB_HW_ALS100)
		runसमय->hw.rate_max = 48000;
	अगर (chip->hardware == SB_HW_CS5530) अणु
		runसमय->hw.buffer_bytes_max = 32 * 1024;
		runसमय->hw.periods_min = 2;
		runसमय->hw.rate_min = 44100;
	पूर्ण
	अगर (chip->mode & SB_RATE_LOCK)
		runसमय->hw.rate_min = runसमय->hw.rate_max = chip->locked_rate;
	chip->capture_substream = substream;
	spin_unlock_irqrestore(&chip->खोलो_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_sb16_capture_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_sb *chip = snd_pcm_substream_chip(substream);

	snd_sb16_csp_capture_बंद(chip);
	spin_lock_irqsave(&chip->खोलो_lock, flags);
	chip->capture_substream = शून्य;
	chip->mode &= ~SB_MODE_CAPTURE;
	spin_unlock_irqrestore(&chip->खोलो_lock, flags);
	वापस 0;
पूर्ण

/*
 *  DMA control पूर्णांकerface
 */

अटल पूर्णांक snd_sb16_set_dma_mode(काष्ठा snd_sb *chip, पूर्णांक what)
अणु
	अगर (chip->dma8 < 0 || chip->dma16 < 0) अणु
		अगर (snd_BUG_ON(what))
			वापस -EINVAL;
		वापस 0;
	पूर्ण
	अगर (what == 0) अणु
		chip->क्रमce_mode16 = 0;
	पूर्ण अन्यथा अगर (what == 1) अणु
		chip->क्रमce_mode16 = SB_MODE_PLAYBACK_16;
	पूर्ण अन्यथा अगर (what == 2) अणु
		chip->क्रमce_mode16 = SB_MODE_CAPTURE_16;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_sb16_get_dma_mode(काष्ठा snd_sb *chip)
अणु
	अगर (chip->dma8 < 0 || chip->dma16 < 0)
		वापस 0;
	चयन (chip->क्रमce_mode16) अणु
	हाल SB_MODE_PLAYBACK_16:
		वापस 1;
	हाल SB_MODE_CAPTURE_16:
		वापस 2;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक snd_sb16_dma_control_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[3] = अणु
		"Auto", "Playback", "Capture"
	पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 3, texts);
पूर्ण

अटल पूर्णांक snd_sb16_dma_control_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_sb *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	
	spin_lock_irqsave(&chip->reg_lock, flags);
	ucontrol->value.क्रमागतerated.item[0] = snd_sb16_get_dma_mode(chip);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_sb16_dma_control_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_sb *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर nval, oval;
	पूर्णांक change;
	
	अगर ((nval = ucontrol->value.क्रमागतerated.item[0]) > 2)
		वापस -EINVAL;
	spin_lock_irqsave(&chip->reg_lock, flags);
	oval = snd_sb16_get_dma_mode(chip);
	change = nval != oval;
	snd_sb16_set_dma_mode(chip, nval);
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	वापस change;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_sb16_dma_control = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_CARD,
	.name = "16-bit DMA Allocation",
	.info = snd_sb16_dma_control_info,
	.get = snd_sb16_dma_control_get,
	.put = snd_sb16_dma_control_put
पूर्ण;

/*
 *  Initialization part
 */
 
पूर्णांक snd_sb16dsp_configure(काष्ठा snd_sb * chip)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर irqreg = 0, dmareg = 0, mpureg;
	अचिन्हित अक्षर realirq, realdma, realmpureg;
	/* note: mpu रेजिस्टर should be present only on SB16 Vibra soundcards */

	// prपूर्णांकk(KERN_DEBUG "codec->irq=%i, codec->dma8=%i, codec->dma16=%i\n", chip->irq, chip->dma8, chip->dma16);
	spin_lock_irqsave(&chip->mixer_lock, flags);
	mpureg = snd_sbmixer_पढ़ो(chip, SB_DSP4_MPUSETUP) & ~0x06;
	spin_unlock_irqrestore(&chip->mixer_lock, flags);
	चयन (chip->irq) अणु
	हाल 2:
	हाल 9:
		irqreg |= SB_IRQSETUP_IRQ9;
		अवरोध;
	हाल 5:
		irqreg |= SB_IRQSETUP_IRQ5;
		अवरोध;
	हाल 7:
		irqreg |= SB_IRQSETUP_IRQ7;
		अवरोध;
	हाल 10:
		irqreg |= SB_IRQSETUP_IRQ10;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	अगर (chip->dma8 >= 0) अणु
		चयन (chip->dma8) अणु
		हाल 0:
			dmareg |= SB_DMASETUP_DMA0;
			अवरोध;
		हाल 1:
			dmareg |= SB_DMASETUP_DMA1;
			अवरोध;
		हाल 3:
			dmareg |= SB_DMASETUP_DMA3;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	अगर (chip->dma16 >= 0 && chip->dma16 != chip->dma8) अणु
		चयन (chip->dma16) अणु
		हाल 5:
			dmareg |= SB_DMASETUP_DMA5;
			अवरोध;
		हाल 6:
			dmareg |= SB_DMASETUP_DMA6;
			अवरोध;
		हाल 7:
			dmareg |= SB_DMASETUP_DMA7;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	चयन (chip->mpu_port) अणु
	हाल 0x300:
		mpureg |= 0x04;
		अवरोध;
	हाल 0x330:
		mpureg |= 0x00;
		अवरोध;
	शेष:
		mpureg |= 0x02;	/* disable MPU */
	पूर्ण
	spin_lock_irqsave(&chip->mixer_lock, flags);

	snd_sbmixer_ग_लिखो(chip, SB_DSP4_IRQSETUP, irqreg);
	realirq = snd_sbmixer_पढ़ो(chip, SB_DSP4_IRQSETUP);

	snd_sbmixer_ग_लिखो(chip, SB_DSP4_DMASETUP, dmareg);
	realdma = snd_sbmixer_पढ़ो(chip, SB_DSP4_DMASETUP);

	snd_sbmixer_ग_लिखो(chip, SB_DSP4_MPUSETUP, mpureg);
	realmpureg = snd_sbmixer_पढ़ो(chip, SB_DSP4_MPUSETUP);

	spin_unlock_irqrestore(&chip->mixer_lock, flags);
	अगर ((~realirq) & irqreg || (~realdma) & dmareg) अणु
		snd_prपूर्णांकk(KERN_ERR "SB16 [0x%lx]: unable to set DMA & IRQ (PnP device?)\n", chip->port);
		snd_prपूर्णांकk(KERN_ERR "SB16 [0x%lx]: wanted: irqreg=0x%x, dmareg=0x%x, mpureg = 0x%x\n", chip->port, realirq, realdma, realmpureg);
		snd_prपूर्णांकk(KERN_ERR "SB16 [0x%lx]:    got: irqreg=0x%x, dmareg=0x%x, mpureg = 0x%x\n", chip->port, irqreg, dmareg, mpureg);
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops snd_sb16_playback_ops = अणु
	.खोलो =		snd_sb16_playback_खोलो,
	.बंद =	snd_sb16_playback_बंद,
	.prepare =	snd_sb16_playback_prepare,
	.trigger =	snd_sb16_playback_trigger,
	.poपूर्णांकer =	snd_sb16_playback_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_sb16_capture_ops = अणु
	.खोलो =		snd_sb16_capture_खोलो,
	.बंद =	snd_sb16_capture_बंद,
	.prepare =	snd_sb16_capture_prepare,
	.trigger =	snd_sb16_capture_trigger,
	.poपूर्णांकer =	snd_sb16_capture_poपूर्णांकer,
पूर्ण;

पूर्णांक snd_sb16dsp_pcm(काष्ठा snd_sb *chip, पूर्णांक device)
अणु
	काष्ठा snd_card *card = chip->card;
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;

	अगर ((err = snd_pcm_new(card, "SB16 DSP", device, 1, 1, &pcm)) < 0)
		वापस err;
	प्र_लिखो(pcm->name, "DSP v%i.%i", chip->version >> 8, chip->version & 0xff);
	pcm->info_flags = SNDRV_PCM_INFO_JOINT_DUPLEX;
	pcm->निजी_data = chip;
	chip->pcm = pcm;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_sb16_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_sb16_capture_ops);

	अगर (chip->dma16 >= 0 && chip->dma8 != chip->dma16)
		snd_ctl_add(card, snd_ctl_new1(&snd_sb16_dma_control, chip));
	अन्यथा
		pcm->info_flags = SNDRV_PCM_INFO_HALF_DUPLEX;

	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV,
				       card->dev, 64*1024, 128*1024);
	वापस 0;
पूर्ण

स्थिर काष्ठा snd_pcm_ops *snd_sb16dsp_get_pcm_ops(पूर्णांक direction)
अणु
	वापस direction == SNDRV_PCM_STREAM_PLAYBACK ?
		&snd_sb16_playback_ops : &snd_sb16_capture_ops;
पूर्ण

EXPORT_SYMBOL(snd_sb16dsp_pcm);
EXPORT_SYMBOL(snd_sb16dsp_get_pcm_ops);
EXPORT_SYMBOL(snd_sb16dsp_configure);
EXPORT_SYMBOL(snd_sb16dsp_पूर्णांकerrupt);
