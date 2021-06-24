<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 */
 
/*
 * Vortex PCM ALSA driver.
 *
 * Supports ADB and WT DMA. Unक्रमtunately, WT channels करो not run yet.
 * It reमुख्यs stuck,and DMA transfers करो not happen. 
 */
#समावेश <sound/asoundef.h>
#समावेश <linux/समय.स>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश "au88x0.h"

#घोषणा VORTEX_PCM_TYPE(x) (x->name[40])

/* hardware definition */
अटल स्थिर काष्ठा snd_pcm_hardware snd_vortex_playback_hw_adb = अणु
	.info =
	    (SNDRV_PCM_INFO_MMAP | /* SNDRV_PCM_INFO_RESUME | */
	     SNDRV_PCM_INFO_PAUSE | SNDRV_PCM_INFO_INTERLEAVED |
	     SNDRV_PCM_INFO_MMAP_VALID),
	.क्रमmats =
	    SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_U8 |
	    SNDRV_PCM_FMTBIT_MU_LAW | SNDRV_PCM_FMTBIT_A_LAW,
	.rates = SNDRV_PCM_RATE_CONTINUOUS,
	.rate_min = 5000,
	.rate_max = 48000,
	.channels_min = 1,
	.channels_max = 2,
	.buffer_bytes_max = 0x10000,
	.period_bytes_min = 0x20,
	.period_bytes_max = 0x1000,
	.periods_min = 2,
	.periods_max = 1024,
पूर्ण;

#अगर_अघोषित CHIP_AU8820
अटल स्थिर काष्ठा snd_pcm_hardware snd_vortex_playback_hw_a3d = अणु
	.info =
	    (SNDRV_PCM_INFO_MMAP | /* SNDRV_PCM_INFO_RESUME | */
	     SNDRV_PCM_INFO_PAUSE | SNDRV_PCM_INFO_INTERLEAVED |
	     SNDRV_PCM_INFO_MMAP_VALID),
	.क्रमmats =
	    SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_U8 |
	    SNDRV_PCM_FMTBIT_MU_LAW | SNDRV_PCM_FMTBIT_A_LAW,
	.rates = SNDRV_PCM_RATE_CONTINUOUS,
	.rate_min = 5000,
	.rate_max = 48000,
	.channels_min = 1,
	.channels_max = 1,
	.buffer_bytes_max = 0x10000,
	.period_bytes_min = 0x100,
	.period_bytes_max = 0x1000,
	.periods_min = 2,
	.periods_max = 64,
पूर्ण;
#पूर्ण_अगर
अटल स्थिर काष्ठा snd_pcm_hardware snd_vortex_playback_hw_spdअगर = अणु
	.info =
	    (SNDRV_PCM_INFO_MMAP | /* SNDRV_PCM_INFO_RESUME | */
	     SNDRV_PCM_INFO_PAUSE | SNDRV_PCM_INFO_INTERLEAVED |
	     SNDRV_PCM_INFO_MMAP_VALID),
	.क्रमmats =
	    SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_U8 |
	    SNDRV_PCM_FMTBIT_IEC958_SUBFRAME_LE | SNDRV_PCM_FMTBIT_MU_LAW |
	    SNDRV_PCM_FMTBIT_A_LAW,
	.rates =
	    SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_44100 | SNDRV_PCM_RATE_48000,
	.rate_min = 32000,
	.rate_max = 48000,
	.channels_min = 1,
	.channels_max = 2,
	.buffer_bytes_max = 0x10000,
	.period_bytes_min = 0x100,
	.period_bytes_max = 0x1000,
	.periods_min = 2,
	.periods_max = 64,
पूर्ण;

#अगर_अघोषित CHIP_AU8810
अटल स्थिर काष्ठा snd_pcm_hardware snd_vortex_playback_hw_wt = अणु
	.info = (SNDRV_PCM_INFO_MMAP |
		 SNDRV_PCM_INFO_INTERLEAVED |
		 SNDRV_PCM_INFO_BLOCK_TRANSFER | SNDRV_PCM_INFO_MMAP_VALID),
	.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	.rates = SNDRV_PCM_RATE_8000_48000 | SNDRV_PCM_RATE_CONTINUOUS,	// SNDRV_PCM_RATE_48000,
	.rate_min = 8000,
	.rate_max = 48000,
	.channels_min = 1,
	.channels_max = 2,
	.buffer_bytes_max = 0x10000,
	.period_bytes_min = 0x0400,
	.period_bytes_max = 0x1000,
	.periods_min = 2,
	.periods_max = 64,
पूर्ण;
#पूर्ण_अगर
#अगर_घोषित CHIP_AU8830
अटल स्थिर अचिन्हित पूर्णांक au8830_channels[3] = अणु
	1, 2, 4,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list hw_स्थिरraपूर्णांकs_au8830_channels = अणु
	.count = ARRAY_SIZE(au8830_channels),
	.list = au8830_channels,
	.mask = 0,
पूर्ण;
#पूर्ण_अगर

अटल व्योम vortex_notअगरy_pcm_vol_change(काष्ठा snd_card *card,
			काष्ठा snd_kcontrol *kctl, पूर्णांक activate)
अणु
	अगर (activate)
		kctl->vd[0].access &= ~SNDRV_CTL_ELEM_ACCESS_INACTIVE;
	अन्यथा
		kctl->vd[0].access |= SNDRV_CTL_ELEM_ACCESS_INACTIVE;
	snd_ctl_notअगरy(card, SNDRV_CTL_EVENT_MASK_VALUE |
				SNDRV_CTL_EVENT_MASK_INFO, &(kctl->id));
पूर्ण

/* खोलो callback */
अटल पूर्णांक snd_vortex_pcm_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	vortex_t *vortex = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक err;
	
	/* Force equal size periods */
	अगर ((err =
	     snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय,
					   SNDRV_PCM_HW_PARAM_PERIODS)) < 0)
		वापस err;
	/* Aव्योम PAGE_SIZE boundary to fall inside of a period. */
	अगर ((err =
	     snd_pcm_hw_स्थिरraपूर्णांक_घात2(runसमय, 0,
					SNDRV_PCM_HW_PARAM_PERIOD_BYTES)) < 0)
		वापस err;

	snd_pcm_hw_स्थिरraपूर्णांक_step(runसमय, 0,
					SNDRV_PCM_HW_PARAM_BUFFER_BYTES, 64);

	अगर (VORTEX_PCM_TYPE(substream->pcm) != VORTEX_PCM_WT) अणु
#अगर_अघोषित CHIP_AU8820
		अगर (VORTEX_PCM_TYPE(substream->pcm) == VORTEX_PCM_A3D) अणु
			runसमय->hw = snd_vortex_playback_hw_a3d;
		पूर्ण
#पूर्ण_अगर
		अगर (VORTEX_PCM_TYPE(substream->pcm) == VORTEX_PCM_SPDIF) अणु
			runसमय->hw = snd_vortex_playback_hw_spdअगर;
			चयन (vortex->spdअगर_sr) अणु
			हाल 32000:
				runसमय->hw.rates = SNDRV_PCM_RATE_32000;
				अवरोध;
			हाल 44100:
				runसमय->hw.rates = SNDRV_PCM_RATE_44100;
				अवरोध;
			हाल 48000:
				runसमय->hw.rates = SNDRV_PCM_RATE_48000;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (VORTEX_PCM_TYPE(substream->pcm) == VORTEX_PCM_ADB
		    || VORTEX_PCM_TYPE(substream->pcm) == VORTEX_PCM_I2S)
			runसमय->hw = snd_vortex_playback_hw_adb;
#अगर_घोषित CHIP_AU8830
		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK &&
			VORTEX_IS_QUAD(vortex) &&
			VORTEX_PCM_TYPE(substream->pcm) == VORTEX_PCM_ADB) अणु
			runसमय->hw.channels_max = 4;
			snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0,
				SNDRV_PCM_HW_PARAM_CHANNELS,
				&hw_स्थिरraपूर्णांकs_au8830_channels);
		पूर्ण
#पूर्ण_अगर
		substream->runसमय->निजी_data = शून्य;
	पूर्ण
#अगर_अघोषित CHIP_AU8810
	अन्यथा अणु
		runसमय->hw = snd_vortex_playback_hw_wt;
		substream->runसमय->निजी_data = शून्य;
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

/* बंद callback */
अटल पूर्णांक snd_vortex_pcm_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	//vortex_t *chip = snd_pcm_substream_chip(substream);
	stream_t *stream = (stream_t *) substream->runसमय->निजी_data;

	// the hardware-specअगरic codes will be here
	अगर (stream != शून्य) अणु
		stream->substream = शून्य;
		stream->nr_ch = 0;
	पूर्ण
	substream->runसमय->निजी_data = शून्य;
	वापस 0;
पूर्ण

/* hw_params callback */
अटल पूर्णांक
snd_vortex_pcm_hw_params(काष्ठा snd_pcm_substream *substream,
			 काष्ठा snd_pcm_hw_params *hw_params)
अणु
	vortex_t *chip = snd_pcm_substream_chip(substream);
	stream_t *stream = (stream_t *) (substream->runसमय->निजी_data);

	/*
	   pr_info( "Vortex: periods %d, period_bytes %d, channels = %d\n", params_periods(hw_params),
	   params_period_bytes(hw_params), params_channels(hw_params));
	 */
	spin_lock_irq(&chip->lock);
	// Make audio routes and config buffer DMA.
	अगर (VORTEX_PCM_TYPE(substream->pcm) != VORTEX_PCM_WT) अणु
		पूर्णांक dma, type = VORTEX_PCM_TYPE(substream->pcm);
		/* Dealloc any routes. */
		अगर (stream != शून्य)
			vortex_adb_allocroute(chip, stream->dma,
					      stream->nr_ch, stream->dir,
					      stream->type,
					      substream->number);
		/* Alloc routes. */
		dma =
		    vortex_adb_allocroute(chip, -1,
					  params_channels(hw_params),
					  substream->stream, type,
					  substream->number);
		अगर (dma < 0) अणु
			spin_unlock_irq(&chip->lock);
			वापस dma;
		पूर्ण
		stream = substream->runसमय->निजी_data = &chip->dma_adb[dma];
		stream->substream = substream;
		/* Setup Buffers. */
		vortex_adbdma_रखो_बफfers(chip, dma,
					 params_period_bytes(hw_params),
					 params_periods(hw_params));
		अगर (VORTEX_PCM_TYPE(substream->pcm) == VORTEX_PCM_ADB) अणु
			chip->pcm_vol[substream->number].active = 1;
			vortex_notअगरy_pcm_vol_change(chip->card,
				chip->pcm_vol[substream->number].kctl, 1);
		पूर्ण
	पूर्ण
#अगर_अघोषित CHIP_AU8810
	अन्यथा अणु
		/* अगर (stream != शून्य)
		   vortex_wt_allocroute(chip, substream->number, 0); */
		vortex_wt_allocroute(chip, substream->number,
				     params_channels(hw_params));
		stream = substream->runसमय->निजी_data =
		    &chip->dma_wt[substream->number];
		stream->dma = substream->number;
		stream->substream = substream;
		vortex_wtdma_रखो_बफfers(chip, substream->number,
					params_period_bytes(hw_params),
					params_periods(hw_params));
	पूर्ण
#पूर्ण_अगर
	spin_unlock_irq(&chip->lock);
	वापस 0;
पूर्ण

/* hw_मुक्त callback */
अटल पूर्णांक snd_vortex_pcm_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	vortex_t *chip = snd_pcm_substream_chip(substream);
	stream_t *stream = (stream_t *) (substream->runसमय->निजी_data);

	spin_lock_irq(&chip->lock);
	// Delete audio routes.
	अगर (VORTEX_PCM_TYPE(substream->pcm) != VORTEX_PCM_WT) अणु
		अगर (stream != शून्य) अणु
			अगर (VORTEX_PCM_TYPE(substream->pcm) == VORTEX_PCM_ADB) अणु
				chip->pcm_vol[substream->number].active = 0;
				vortex_notअगरy_pcm_vol_change(chip->card,
					chip->pcm_vol[substream->number].kctl,
					0);
			पूर्ण
			vortex_adb_allocroute(chip, stream->dma,
					      stream->nr_ch, stream->dir,
					      stream->type,
					      substream->number);
		पूर्ण
	पूर्ण
#अगर_अघोषित CHIP_AU8810
	अन्यथा अणु
		अगर (stream != शून्य)
			vortex_wt_allocroute(chip, stream->dma, 0);
	पूर्ण
#पूर्ण_अगर
	substream->runसमय->निजी_data = शून्य;
	spin_unlock_irq(&chip->lock);

	वापस 0;
पूर्ण

/* prepare callback */
अटल पूर्णांक snd_vortex_pcm_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	vortex_t *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	stream_t *stream = (stream_t *) substream->runसमय->निजी_data;
	पूर्णांक dma = stream->dma, fmt, dir;

	// set up the hardware with the current configuration.
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		dir = 1;
	अन्यथा
		dir = 0;
	fmt = vortex_alsafmt_aspfmt(runसमय->क्रमmat, chip);
	spin_lock_irq(&chip->lock);
	अगर (VORTEX_PCM_TYPE(substream->pcm) != VORTEX_PCM_WT) अणु
		vortex_adbdma_seपंचांगode(chip, dma, 1, dir, fmt,
				runसमय->channels == 1 ? 0 : 1, 0);
		vortex_adbdma_setstartbuffer(chip, dma, 0);
		अगर (VORTEX_PCM_TYPE(substream->pcm) != VORTEX_PCM_SPDIF)
			vortex_adb_setsrc(chip, dma, runसमय->rate, dir);
	पूर्ण
#अगर_अघोषित CHIP_AU8810
	अन्यथा अणु
		vortex_wtdma_seपंचांगode(chip, dma, 1, fmt, 0, 0);
		// FIXME: Set rate (i guess using vortex_wt_ग_लिखोreg() somehow).
		vortex_wtdma_setstartbuffer(chip, dma, 0);
	पूर्ण
#पूर्ण_अगर
	spin_unlock_irq(&chip->lock);
	वापस 0;
पूर्ण

/* trigger callback */
अटल पूर्णांक snd_vortex_pcm_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	vortex_t *chip = snd_pcm_substream_chip(substream);
	stream_t *stream = (stream_t *) substream->runसमय->निजी_data;
	पूर्णांक dma = stream->dma;

	spin_lock(&chip->lock);
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		// करो something to start the PCM engine
		//prपूर्णांकk(KERN_INFO "vortex: start %d\n", dma);
		stream->fअगरo_enabled = 1;
		अगर (VORTEX_PCM_TYPE(substream->pcm) != VORTEX_PCM_WT) अणु
			vortex_adbdma_resetup(chip, dma);
			vortex_adbdma_startfअगरo(chip, dma);
		पूर्ण
#अगर_अघोषित CHIP_AU8810
		अन्यथा अणु
			dev_info(chip->card->dev, "wt start %d\n", dma);
			vortex_wtdma_startfअगरo(chip, dma);
		पूर्ण
#पूर्ण_अगर
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		// करो something to stop the PCM engine
		//prपूर्णांकk(KERN_INFO "vortex: stop %d\n", dma);
		stream->fअगरo_enabled = 0;
		अगर (VORTEX_PCM_TYPE(substream->pcm) != VORTEX_PCM_WT)
			vortex_adbdma_stopfअगरo(chip, dma);
#अगर_अघोषित CHIP_AU8810
		अन्यथा अणु
			dev_info(chip->card->dev, "wt stop %d\n", dma);
			vortex_wtdma_stopfअगरo(chip, dma);
		पूर्ण
#पूर्ण_अगर
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		//prपूर्णांकk(KERN_INFO "vortex: pause %d\n", dma);
		अगर (VORTEX_PCM_TYPE(substream->pcm) != VORTEX_PCM_WT)
			vortex_adbdma_छोड़ोfअगरo(chip, dma);
#अगर_अघोषित CHIP_AU8810
		अन्यथा
			vortex_wtdma_छोड़ोfअगरo(chip, dma);
#पूर्ण_अगर
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		//prपूर्णांकk(KERN_INFO "vortex: resume %d\n", dma);
		अगर (VORTEX_PCM_TYPE(substream->pcm) != VORTEX_PCM_WT)
			vortex_adbdma_resumefअगरo(chip, dma);
#अगर_अघोषित CHIP_AU8810
		अन्यथा
			vortex_wtdma_resumefअगरo(chip, dma);
#पूर्ण_अगर
		अवरोध;
	शेष:
		spin_unlock(&chip->lock);
		वापस -EINVAL;
	पूर्ण
	spin_unlock(&chip->lock);
	वापस 0;
पूर्ण

/* poपूर्णांकer callback */
अटल snd_pcm_uframes_t snd_vortex_pcm_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	vortex_t *chip = snd_pcm_substream_chip(substream);
	stream_t *stream = (stream_t *) substream->runसमय->निजी_data;
	पूर्णांक dma = stream->dma;
	snd_pcm_uframes_t current_ptr = 0;

	spin_lock(&chip->lock);
	अगर (VORTEX_PCM_TYPE(substream->pcm) != VORTEX_PCM_WT)
		current_ptr = vortex_adbdma_getlinearpos(chip, dma);
#अगर_अघोषित CHIP_AU8810
	अन्यथा
		current_ptr = vortex_wtdma_getlinearpos(chip, dma);
#पूर्ण_अगर
	//prपूर्णांकk(KERN_INFO "vortex: pointer = 0x%x\n", current_ptr);
	spin_unlock(&chip->lock);
	current_ptr = bytes_to_frames(substream->runसमय, current_ptr);
	अगर (current_ptr >= substream->runसमय->buffer_size)
		current_ptr = 0;
	वापस current_ptr;
पूर्ण

/* चालकs */
अटल स्थिर काष्ठा snd_pcm_ops snd_vortex_playback_ops = अणु
	.खोलो = snd_vortex_pcm_खोलो,
	.बंद = snd_vortex_pcm_बंद,
	.hw_params = snd_vortex_pcm_hw_params,
	.hw_मुक्त = snd_vortex_pcm_hw_मुक्त,
	.prepare = snd_vortex_pcm_prepare,
	.trigger = snd_vortex_pcm_trigger,
	.poपूर्णांकer = snd_vortex_pcm_poपूर्णांकer,
पूर्ण;

/*
*  definitions of capture are omitted here...
*/

अटल स्थिर अक्षर * स्थिर vortex_pcm_prettyname[VORTEX_PCM_LAST] = अणु
	CARD_NAME " ADB",
	CARD_NAME " SPDIF",
	CARD_NAME " A3D",
	CARD_NAME " WT",
	CARD_NAME " I2S",
पूर्ण;
अटल स्थिर अक्षर * स्थिर vortex_pcm_name[VORTEX_PCM_LAST] = अणु
	"adb",
	"spdif",
	"a3d",
	"wt",
	"i2s",
पूर्ण;

/* SPDIF kcontrol */

अटल पूर्णांक snd_vortex_spdअगर_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_vortex_spdअगर_mask_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.iec958.status[0] = 0xff;
	ucontrol->value.iec958.status[1] = 0xff;
	ucontrol->value.iec958.status[2] = 0xff;
	ucontrol->value.iec958.status[3] = IEC958_AES3_CON_FS;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_vortex_spdअगर_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	vortex_t *vortex = snd_kcontrol_chip(kcontrol);
	ucontrol->value.iec958.status[0] = 0x00;
	ucontrol->value.iec958.status[1] = IEC958_AES1_CON_ORIGINAL|IEC958_AES1_CON_DIGDIGCONV_ID;
	ucontrol->value.iec958.status[2] = 0x00;
	चयन (vortex->spdअगर_sr) अणु
	हाल 32000: ucontrol->value.iec958.status[3] = IEC958_AES3_CON_FS_32000; अवरोध;
	हाल 44100: ucontrol->value.iec958.status[3] = IEC958_AES3_CON_FS_44100; अवरोध;
	हाल 48000: ucontrol->value.iec958.status[3] = IEC958_AES3_CON_FS_48000; अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_vortex_spdअगर_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	vortex_t *vortex = snd_kcontrol_chip(kcontrol);
	पूर्णांक spdअगर_sr = 48000;
	चयन (ucontrol->value.iec958.status[3] & IEC958_AES3_CON_FS) अणु
	हाल IEC958_AES3_CON_FS_32000: spdअगर_sr = 32000; अवरोध;
	हाल IEC958_AES3_CON_FS_44100: spdअगर_sr = 44100; अवरोध;
	हाल IEC958_AES3_CON_FS_48000: spdअगर_sr = 48000; अवरोध;
	पूर्ण
	अगर (spdअगर_sr == vortex->spdअगर_sr)
		वापस 0;
	vortex->spdअगर_sr = spdअगर_sr;
	vortex_spdअगर_init(vortex, vortex->spdअगर_sr, 1);
	वापस 1;
पूर्ण

/* spdअगर controls */
अटल स्थिर काष्ठा snd_kcontrol_new snd_vortex_mixer_spdअगर[] = अणु
	अणु
		.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
		.name =		SNDRV_CTL_NAME_IEC958("",PLAYBACK,DEFAULT),
		.info =		snd_vortex_spdअगर_info,
		.get =		snd_vortex_spdअगर_get,
		.put =		snd_vortex_spdअगर_put,
	पूर्ण,
	अणु
		.access =	SNDRV_CTL_ELEM_ACCESS_READ,
		.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
		.name =		SNDRV_CTL_NAME_IEC958("",PLAYBACK,CON_MASK),
		.info =		snd_vortex_spdअगर_info,
		.get =		snd_vortex_spdअगर_mask_get
	पूर्ण,
पूर्ण;

/* subdevice PCM Volume control */

अटल पूर्णांक snd_vortex_pcm_vol_info(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_info *uinfo)
अणु
	vortex_t *vortex = snd_kcontrol_chip(kcontrol);
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = (VORTEX_IS_QUAD(vortex) ? 4 : 2);
	uinfo->value.पूर्णांकeger.min = -128;
	uinfo->value.पूर्णांकeger.max = 32;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_vortex_pcm_vol_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	पूर्णांक i;
	vortex_t *vortex = snd_kcontrol_chip(kcontrol);
	पूर्णांक subdev = kcontrol->id.subdevice;
	काष्ठा pcm_vol *p = &vortex->pcm_vol[subdev];
	पूर्णांक max_chn = (VORTEX_IS_QUAD(vortex) ? 4 : 2);
	क्रम (i = 0; i < max_chn; i++)
		ucontrol->value.पूर्णांकeger.value[i] = p->vol[i];
	वापस 0;
पूर्ण

अटल पूर्णांक snd_vortex_pcm_vol_put(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	पूर्णांक i;
	पूर्णांक changed = 0;
	पूर्णांक mixin;
	अचिन्हित अक्षर vol;
	vortex_t *vortex = snd_kcontrol_chip(kcontrol);
	पूर्णांक subdev = kcontrol->id.subdevice;
	काष्ठा pcm_vol *p = &vortex->pcm_vol[subdev];
	पूर्णांक max_chn = (VORTEX_IS_QUAD(vortex) ? 4 : 2);
	क्रम (i = 0; i < max_chn; i++) अणु
		अगर (p->vol[i] != ucontrol->value.पूर्णांकeger.value[i]) अणु
			p->vol[i] = ucontrol->value.पूर्णांकeger.value[i];
			अगर (p->active) अणु
				चयन (vortex->dma_adb[p->dma].nr_ch) अणु
				हाल 1:
					mixin = p->mixin[0];
					अवरोध;
				हाल 2:
				शेष:
					mixin = p->mixin[(i < 2) ? i : (i - 2)];
					अवरोध;
				हाल 4:
					mixin = p->mixin[i];
					अवरोध;
				पूर्ण
				vol = p->vol[i];
				vortex_mix_setinputvolumebyte(vortex,
					vortex->mixplayb[i], mixin, vol);
			पूर्ण
			changed = 1;
		पूर्ण
	पूर्ण
	वापस changed;
पूर्ण

अटल स्थिर DECLARE_TLV_DB_MINMAX(vortex_pcm_vol_db_scale, -9600, 2400);

अटल स्थिर काष्ठा snd_kcontrol_new snd_vortex_pcm_vol = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
	.name = "PCM Playback Volume",
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE |
		SNDRV_CTL_ELEM_ACCESS_TLV_READ |
		SNDRV_CTL_ELEM_ACCESS_INACTIVE,
	.info = snd_vortex_pcm_vol_info,
	.get = snd_vortex_pcm_vol_get,
	.put = snd_vortex_pcm_vol_put,
	.tlv = अणु .p = vortex_pcm_vol_db_scale पूर्ण,
पूर्ण;

/* create a pcm device */
अटल पूर्णांक snd_vortex_new_pcm(vortex_t *chip, पूर्णांक idx, पूर्णांक nr)
अणु
	काष्ठा snd_pcm *pcm;
	काष्ठा snd_kcontrol *kctl;
	पूर्णांक i;
	पूर्णांक err, nr_capt;

	अगर (!chip || idx < 0 || idx >= VORTEX_PCM_LAST)
		वापस -ENODEV;

	/* idx indicates which kind of PCM device. ADB, SPDIF, I2S and A3D share the 
	 * same dma engine. WT uses it own separate dma engine which can't capture. */
	अगर (idx == VORTEX_PCM_ADB)
		nr_capt = nr;
	अन्यथा
		nr_capt = 0;
	err = snd_pcm_new(chip->card, vortex_pcm_prettyname[idx], idx, nr,
			  nr_capt, &pcm);
	अगर (err < 0)
		वापस err;
	snम_लिखो(pcm->name, माप(pcm->name),
		"%s %s", CARD_NAME_SHORT, vortex_pcm_name[idx]);
	chip->pcm[idx] = pcm;
	// This is an evil hack, but it saves a lot of duplicated code.
	VORTEX_PCM_TYPE(pcm) = idx;
	pcm->निजी_data = chip;
	/* set चालकs */
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK,
			&snd_vortex_playback_ops);
	अगर (idx == VORTEX_PCM_ADB)
		snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE,
				&snd_vortex_playback_ops);
	
	/* pre-allocation of Scatter-Gather buffers */
	
	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV_SG,
				       &chip->pci_dev->dev, 0x10000, 0x10000);

	चयन (VORTEX_PCM_TYPE(pcm)) अणु
	हाल VORTEX_PCM_ADB:
		err = snd_pcm_add_chmap_ctls(pcm, SNDRV_PCM_STREAM_PLAYBACK,
					     snd_pcm_std_chmaps,
					     VORTEX_IS_QUAD(chip) ? 4 : 2,
					     0, शून्य);
		अगर (err < 0)
			वापस err;
		err = snd_pcm_add_chmap_ctls(pcm, SNDRV_PCM_STREAM_CAPTURE,
					     snd_pcm_std_chmaps, 2, 0, शून्य);
		अगर (err < 0)
			वापस err;
		अवरोध;
#अगर_घोषित CHIP_AU8830
	हाल VORTEX_PCM_A3D:
		err = snd_pcm_add_chmap_ctls(pcm, SNDRV_PCM_STREAM_PLAYBACK,
					     snd_pcm_std_chmaps, 1, 0, शून्य);
		अगर (err < 0)
			वापस err;
		अवरोध;
#पूर्ण_अगर
	पूर्ण

	अगर (VORTEX_PCM_TYPE(pcm) == VORTEX_PCM_SPDIF) अणु
		क्रम (i = 0; i < ARRAY_SIZE(snd_vortex_mixer_spdअगर); i++) अणु
			kctl = snd_ctl_new1(&snd_vortex_mixer_spdअगर[i], chip);
			अगर (!kctl)
				वापस -ENOMEM;
			अगर ((err = snd_ctl_add(chip->card, kctl)) < 0)
				वापस err;
		पूर्ण
	पूर्ण
	अगर (VORTEX_PCM_TYPE(pcm) == VORTEX_PCM_ADB) अणु
		क्रम (i = 0; i < NR_PCM; i++) अणु
			chip->pcm_vol[i].active = 0;
			chip->pcm_vol[i].dma = -1;
			kctl = snd_ctl_new1(&snd_vortex_pcm_vol, chip);
			अगर (!kctl)
				वापस -ENOMEM;
			chip->pcm_vol[i].kctl = kctl;
			kctl->id.device = 0;
			kctl->id.subdevice = i;
			err = snd_ctl_add(chip->card, kctl);
			अगर (err < 0)
				वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
