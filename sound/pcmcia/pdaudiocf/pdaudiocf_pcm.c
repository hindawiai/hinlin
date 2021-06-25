<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम Sound Core PDAudioCF soundcards
 *
 * PCM part
 *
 * Copyright (c) 2003 by Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <linux/delay.h>
#समावेश <sound/core.h>
#समावेश <sound/asoundef.h>
#समावेश "pdaudiocf.h"


/*
 * clear the SRAM contents
 */
अटल पूर्णांक pdacf_pcm_clear_sram(काष्ठा snd_pdacf *chip)
अणु
	पूर्णांक max_loop = 64 * 1024;

	जबतक (inw(chip->port + PDAUDIOCF_REG_RDP) != inw(chip->port + PDAUDIOCF_REG_WDP)) अणु
		अगर (max_loop-- < 0)
			वापस -EIO;
		inw(chip->port + PDAUDIOCF_REG_MD);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * pdacf_pcm_trigger - trigger callback क्रम capture
 */
अटल पूर्णांक pdacf_pcm_trigger(काष्ठा snd_pcm_substream *subs, पूर्णांक cmd)
अणु
	काष्ठा snd_pdacf *chip = snd_pcm_substream_chip(subs);
	काष्ठा snd_pcm_runसमय *runसमय = subs->runसमय;
	पूर्णांक inc, ret = 0, rate;
	अचिन्हित लघु mask, val, पंचांगp;

	अगर (chip->chip_status & PDAUDIOCF_STAT_IS_STALE)
		वापस -EBUSY;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		chip->pcm_hwptr = 0;
		chip->pcm_tकरोne = 0;
		fallthrough;
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		mask = 0;
		val = PDAUDIOCF_RECORD;
		inc = 1;
		rate = snd_ak4117_check_rate_and_errors(chip->ak4117, AK4117_CHECK_NO_STAT|AK4117_CHECK_NO_RATE);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		mask = PDAUDIOCF_RECORD;
		val = 0;
		inc = -1;
		rate = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	mutex_lock(&chip->reg_lock);
	chip->pcm_running += inc;
	पंचांगp = pdacf_reg_पढ़ो(chip, PDAUDIOCF_REG_SCR);
	अगर (chip->pcm_running) अणु
		अगर ((chip->ak4117->rcs0 & AK4117_UNLCK) || runसमय->rate != rate) अणु
			chip->pcm_running -= inc;
			ret = -EIO;
			जाओ __end;
		पूर्ण
	पूर्ण
	पंचांगp &= ~mask;
	पंचांगp |= val;
	pdacf_reg_ग_लिखो(chip, PDAUDIOCF_REG_SCR, पंचांगp);
      __end:
	mutex_unlock(&chip->reg_lock);
	snd_ak4117_check_rate_and_errors(chip->ak4117, AK4117_CHECK_NO_RATE);
	वापस ret;
पूर्ण

/*
 * pdacf_pcm_prepare - prepare callback क्रम playback and capture
 */
अटल पूर्णांक pdacf_pcm_prepare(काष्ठा snd_pcm_substream *subs)
अणु
	काष्ठा snd_pdacf *chip = snd_pcm_substream_chip(subs);
	काष्ठा snd_pcm_runसमय *runसमय = subs->runसमय;
	u16 val, nval, aval;

	अगर (chip->chip_status & PDAUDIOCF_STAT_IS_STALE)
		वापस -EBUSY;

	chip->pcm_channels = runसमय->channels;

	chip->pcm_little = snd_pcm_क्रमmat_little_endian(runसमय->क्रमmat) > 0;
#अगर_घोषित SNDRV_LITTLE_ENDIAN
	chip->pcm_swab = snd_pcm_क्रमmat_big_endian(runसमय->क्रमmat) > 0;
#अन्यथा
	chip->pcm_swab = chip->pcm_little;
#पूर्ण_अगर

	अगर (snd_pcm_क्रमmat_अचिन्हित(runसमय->क्रमmat))
		chip->pcm_xor = 0x80008000;

	अगर (pdacf_pcm_clear_sram(chip) < 0)
		वापस -EIO;
	
	val = nval = pdacf_reg_पढ़ो(chip, PDAUDIOCF_REG_SCR);
	nval &= ~(PDAUDIOCF_DATAFMT0|PDAUDIOCF_DATAFMT1);
	चयन (runसमय->क्रमmat) अणु
	हाल SNDRV_PCM_FORMAT_S16_LE:
	हाल SNDRV_PCM_FORMAT_S16_BE:
		अवरोध;
	शेष: /* 24-bit */
		nval |= PDAUDIOCF_DATAFMT0 | PDAUDIOCF_DATAFMT1;
		अवरोध;
	पूर्ण
	aval = 0;
	chip->pcm_sample = 4;
	चयन (runसमय->क्रमmat) अणु
	हाल SNDRV_PCM_FORMAT_S16_LE:
	हाल SNDRV_PCM_FORMAT_S16_BE:
		aval = AK4117_DIF_16R;
		chip->pcm_frame = 2;
		chip->pcm_sample = 2;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S24_3LE:
	हाल SNDRV_PCM_FORMAT_S24_3BE:
		chip->pcm_sample = 3;
		fallthrough;
	शेष: /* 24-bit */
		aval = AK4117_DIF_24R;
		chip->pcm_frame = 3;
		chip->pcm_xor &= 0xffff0000;
		अवरोध;
	पूर्ण

	अगर (val != nval) अणु
		snd_ak4117_reg_ग_लिखो(chip->ak4117, AK4117_REG_IO, AK4117_DIF2|AK4117_DIF1|AK4117_DIF0, aval);
		pdacf_reg_ग_लिखो(chip, PDAUDIOCF_REG_SCR, nval);
	पूर्ण

	val = pdacf_reg_पढ़ो(chip,  PDAUDIOCF_REG_IER);
	val &= ~(PDAUDIOCF_IRQLVLEN1);
	val |= PDAUDIOCF_IRQLVLEN0;
	pdacf_reg_ग_लिखो(chip, PDAUDIOCF_REG_IER, val);

	chip->pcm_size = runसमय->buffer_size;
	chip->pcm_period = runसमय->period_size;
	chip->pcm_area = runसमय->dma_area;

	वापस 0;
पूर्ण


/*
 * capture hw inक्रमmation
 */

अटल स्थिर काष्ठा snd_pcm_hardware pdacf_pcm_capture_hw = अणु
	.info =			(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_PAUSE | SNDRV_PCM_INFO_RESUME |
				 SNDRV_PCM_INFO_MMAP_VALID |
				 SNDRV_PCM_INFO_BATCH),
	.क्रमmats =		SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S16_BE |
				SNDRV_PCM_FMTBIT_S24_3LE | SNDRV_PCM_FMTBIT_S24_3BE |
				SNDRV_PCM_FMTBIT_S32_LE | SNDRV_PCM_FMTBIT_S32_BE,
	.rates =		SNDRV_PCM_RATE_32000 |
				SNDRV_PCM_RATE_44100 |
				SNDRV_PCM_RATE_48000 |
				SNDRV_PCM_RATE_88200 |
				SNDRV_PCM_RATE_96000 |
				SNDRV_PCM_RATE_176400 |
				SNDRV_PCM_RATE_192000,
	.rate_min =		32000,
	.rate_max =		192000,
	.channels_min =		1,
	.channels_max =		2,
	.buffer_bytes_max =	(512*1024),
	.period_bytes_min =	8*1024,
	.period_bytes_max =	(64*1024),
	.periods_min =		2,
	.periods_max =		128,
	.fअगरo_size =		0,
पूर्ण;


/*
 * pdacf_pcm_capture_खोलो - खोलो callback क्रम capture
 */
अटल पूर्णांक pdacf_pcm_capture_खोलो(काष्ठा snd_pcm_substream *subs)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = subs->runसमय;
	काष्ठा snd_pdacf *chip = snd_pcm_substream_chip(subs);

	अगर (chip->chip_status & PDAUDIOCF_STAT_IS_STALE)
		वापस -EBUSY;

	runसमय->hw = pdacf_pcm_capture_hw;
	runसमय->निजी_data = chip;
	chip->pcm_substream = subs;

	वापस 0;
पूर्ण

/*
 * pdacf_pcm_capture_बंद - बंद callback क्रम capture
 */
अटल पूर्णांक pdacf_pcm_capture_बंद(काष्ठा snd_pcm_substream *subs)
अणु
	काष्ठा snd_pdacf *chip = snd_pcm_substream_chip(subs);

	अगर (!chip)
		वापस -EINVAL;
	pdacf_reinit(chip, 0);
	chip->pcm_substream = शून्य;
	वापस 0;
पूर्ण


/*
 * pdacf_pcm_capture_poपूर्णांकer - poपूर्णांकer callback क्रम capture
 */
अटल snd_pcm_uframes_t pdacf_pcm_capture_poपूर्णांकer(काष्ठा snd_pcm_substream *subs)
अणु
	काष्ठा snd_pdacf *chip = snd_pcm_substream_chip(subs);
	वापस chip->pcm_hwptr;
पूर्ण

/*
 * चालकs क्रम PCM capture
 */
अटल स्थिर काष्ठा snd_pcm_ops pdacf_pcm_capture_ops = अणु
	.खोलो =		pdacf_pcm_capture_खोलो,
	.बंद =	pdacf_pcm_capture_बंद,
	.prepare =	pdacf_pcm_prepare,
	.trigger =	pdacf_pcm_trigger,
	.poपूर्णांकer =	pdacf_pcm_capture_poपूर्णांकer,
पूर्ण;


/*
 * snd_pdacf_pcm_new - create and initialize a pcm
 */
पूर्णांक snd_pdacf_pcm_new(काष्ठा snd_pdacf *chip)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;

	err = snd_pcm_new(chip->card, "PDAudioCF", 0, 0, 1, &pcm);
	अगर (err < 0)
		वापस err;
		
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &pdacf_pcm_capture_ops);
	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_VMALLOC,
				       snd_dma_continuous_data(GFP_KERNEL | GFP_DMA32),
				       0, 0);

	pcm->निजी_data = chip;
	pcm->info_flags = 0;
	pcm->nonatomic = true;
	म_नकल(pcm->name, chip->card->लघुname);
	chip->pcm = pcm;
	
	err = snd_ak4117_build(chip->ak4117, pcm->streams[SNDRV_PCM_STREAM_CAPTURE].substream);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण
