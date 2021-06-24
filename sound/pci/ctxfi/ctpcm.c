<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2008, Creative Technology Ltd. All Rights Reserved.
 *
 * @File	ctpcm.c
 *
 * @Brief
 * This file contains the definition of the pcm device functions.
 *
 * @Author	Liu Chun
 * @Date 	Apr 2 2008
 */

#समावेश "ctpcm.h"
#समावेश "cttimer.h"
#समावेश <linux/slab.h>
#समावेश <sound/pcm.h>

/* Hardware descriptions क्रम playback */
अटल स्थिर काष्ठा snd_pcm_hardware ct_pcm_playback_hw = अणु
	.info			= (SNDRV_PCM_INFO_MMAP |
				   SNDRV_PCM_INFO_INTERLEAVED |
				   SNDRV_PCM_INFO_BLOCK_TRANSFER |
				   SNDRV_PCM_INFO_MMAP_VALID |
				   SNDRV_PCM_INFO_PAUSE),
	.क्रमmats		= (SNDRV_PCM_FMTBIT_U8 |
				   SNDRV_PCM_FMTBIT_S16_LE |
				   SNDRV_PCM_FMTBIT_S24_3LE |
				   SNDRV_PCM_FMTBIT_S32_LE |
				   SNDRV_PCM_FMTBIT_FLOAT_LE),
	.rates			= (SNDRV_PCM_RATE_CONTINUOUS |
				   SNDRV_PCM_RATE_8000_192000),
	.rate_min		= 8000,
	.rate_max		= 192000,
	.channels_min		= 1,
	.channels_max		= 2,
	.buffer_bytes_max	= (128*1024),
	.period_bytes_min	= (64),
	.period_bytes_max	= (128*1024),
	.periods_min		= 2,
	.periods_max		= 1024,
	.fअगरo_size		= 0,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware ct_spdअगर_passthru_playback_hw = अणु
	.info			= (SNDRV_PCM_INFO_MMAP |
				   SNDRV_PCM_INFO_INTERLEAVED |
				   SNDRV_PCM_INFO_BLOCK_TRANSFER |
				   SNDRV_PCM_INFO_MMAP_VALID |
				   SNDRV_PCM_INFO_PAUSE),
	.क्रमmats		= SNDRV_PCM_FMTBIT_S16_LE,
	.rates			= (SNDRV_PCM_RATE_48000 |
				   SNDRV_PCM_RATE_44100 |
				   SNDRV_PCM_RATE_32000),
	.rate_min		= 32000,
	.rate_max		= 48000,
	.channels_min		= 2,
	.channels_max		= 2,
	.buffer_bytes_max	= (128*1024),
	.period_bytes_min	= (64),
	.period_bytes_max	= (128*1024),
	.periods_min		= 2,
	.periods_max		= 1024,
	.fअगरo_size		= 0,
पूर्ण;

/* Hardware descriptions क्रम capture */
अटल स्थिर काष्ठा snd_pcm_hardware ct_pcm_capture_hw = अणु
	.info			= (SNDRV_PCM_INFO_MMAP |
				   SNDRV_PCM_INFO_INTERLEAVED |
				   SNDRV_PCM_INFO_BLOCK_TRANSFER |
				   SNDRV_PCM_INFO_PAUSE |
				   SNDRV_PCM_INFO_MMAP_VALID),
	.क्रमmats		= (SNDRV_PCM_FMTBIT_U8 |
				   SNDRV_PCM_FMTBIT_S16_LE |
				   SNDRV_PCM_FMTBIT_S24_3LE |
				   SNDRV_PCM_FMTBIT_S32_LE |
				   SNDRV_PCM_FMTBIT_FLOAT_LE),
	.rates			= (SNDRV_PCM_RATE_CONTINUOUS |
				   SNDRV_PCM_RATE_8000_96000),
	.rate_min		= 8000,
	.rate_max		= 96000,
	.channels_min		= 1,
	.channels_max		= 2,
	.buffer_bytes_max	= (128*1024),
	.period_bytes_min	= (384),
	.period_bytes_max	= (64*1024),
	.periods_min		= 2,
	.periods_max		= 1024,
	.fअगरo_size		= 0,
पूर्ण;

अटल व्योम ct_atc_pcm_पूर्णांकerrupt(काष्ठा ct_atc_pcm *atc_pcm)
अणु
	काष्ठा ct_atc_pcm *apcm = atc_pcm;

	अगर (!apcm->substream)
		वापस;

	snd_pcm_period_elapsed(apcm->substream);
पूर्ण

अटल व्योम ct_atc_pcm_मुक्त_substream(काष्ठा snd_pcm_runसमय *runसमय)
अणु
	काष्ठा ct_atc_pcm *apcm = runसमय->निजी_data;
	काष्ठा ct_atc *atc = snd_pcm_substream_chip(apcm->substream);

	atc->pcm_release_resources(atc, apcm);
	ct_समयr_instance_मुक्त(apcm->समयr);
	kमुक्त(apcm);
	runसमय->निजी_data = शून्य;
पूर्ण

/* pcm playback operations */
अटल पूर्णांक ct_pcm_playback_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा ct_atc *atc = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा ct_atc_pcm *apcm;
	पूर्णांक err;

	apcm = kzalloc(माप(*apcm), GFP_KERNEL);
	अगर (!apcm)
		वापस -ENOMEM;

	apcm->substream = substream;
	apcm->पूर्णांकerrupt = ct_atc_pcm_पूर्णांकerrupt;
	अगर (IEC958 == substream->pcm->device) अणु
		runसमय->hw = ct_spdअगर_passthru_playback_hw;
		atc->spdअगर_out_passthru(atc, 1);
	पूर्ण अन्यथा अणु
		runसमय->hw = ct_pcm_playback_hw;
		अगर (FRONT == substream->pcm->device)
			runसमय->hw.channels_max = 8;
	पूर्ण

	err = snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय,
					    SNDRV_PCM_HW_PARAM_PERIODS);
	अगर (err < 0)
		जाओ मुक्त_pcm;

	err = snd_pcm_hw_स्थिरraपूर्णांक_minmax(runसमय,
					   SNDRV_PCM_HW_PARAM_BUFFER_BYTES,
					   1024, अच_पूर्णांक_उच्च);
	अगर (err < 0)
		जाओ मुक्त_pcm;

	apcm->समयr = ct_समयr_instance_new(atc->समयr, apcm);
	अगर (!apcm->समयr) अणु
		err = -ENOMEM;
		जाओ मुक्त_pcm;
	पूर्ण
	runसमय->निजी_data = apcm;
	runसमय->निजी_मुक्त = ct_atc_pcm_मुक्त_substream;

	वापस 0;

मुक्त_pcm:
	kमुक्त(apcm);
	वापस err;
पूर्ण

अटल पूर्णांक ct_pcm_playback_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा ct_atc *atc = snd_pcm_substream_chip(substream);

	/* TODO: Notअगरy mixer inactive. */
	अगर (IEC958 == substream->pcm->device)
		atc->spdअगर_out_passthru(atc, 0);

	/* The ct_atc_pcm object will be मुक्तd by runसमय->निजी_मुक्त */

	वापस 0;
पूर्ण

अटल पूर्णांक ct_pcm_hw_params(काष्ठा snd_pcm_substream *substream,
				     काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा ct_atc *atc = snd_pcm_substream_chip(substream);
	काष्ठा ct_atc_pcm *apcm = substream->runसमय->निजी_data;

	/* clear previous resources */
	atc->pcm_release_resources(atc, apcm);
	वापस 0;
पूर्ण

अटल पूर्णांक ct_pcm_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा ct_atc *atc = snd_pcm_substream_chip(substream);
	काष्ठा ct_atc_pcm *apcm = substream->runसमय->निजी_data;

	/* clear previous resources */
	atc->pcm_release_resources(atc, apcm);
	वापस 0;
पूर्ण


अटल पूर्णांक ct_pcm_playback_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	पूर्णांक err;
	काष्ठा ct_atc *atc = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा ct_atc_pcm *apcm = runसमय->निजी_data;

	अगर (IEC958 == substream->pcm->device)
		err = atc->spdअगर_passthru_playback_prepare(atc, apcm);
	अन्यथा
		err = atc->pcm_playback_prepare(atc, apcm);

	अगर (err < 0) अणु
		dev_err(atc->card->dev,
			"Preparing pcm playback failed!!!\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
ct_pcm_playback_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा ct_atc *atc = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा ct_atc_pcm *apcm = runसमय->निजी_data;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		atc->pcm_playback_start(atc, apcm);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		atc->pcm_playback_stop(atc, apcm);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t
ct_pcm_playback_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	अचिन्हित दीर्घ position;
	काष्ठा ct_atc *atc = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा ct_atc_pcm *apcm = runसमय->निजी_data;

	/* Read out playback position */
	position = atc->pcm_playback_position(atc, apcm);
	position = bytes_to_frames(runसमय, position);
	अगर (position >= runसमय->buffer_size)
		position = 0;
	वापस position;
पूर्ण

/* pcm capture operations */
अटल पूर्णांक ct_pcm_capture_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा ct_atc *atc = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा ct_atc_pcm *apcm;
	पूर्णांक err;

	apcm = kzalloc(माप(*apcm), GFP_KERNEL);
	अगर (!apcm)
		वापस -ENOMEM;

	apcm->started = 0;
	apcm->substream = substream;
	apcm->पूर्णांकerrupt = ct_atc_pcm_पूर्णांकerrupt;
	runसमय->hw = ct_pcm_capture_hw;
	runसमय->hw.rate_max = atc->rsr * atc->msr;

	err = snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय,
					    SNDRV_PCM_HW_PARAM_PERIODS);
	अगर (err < 0)
		जाओ मुक्त_pcm;

	err = snd_pcm_hw_स्थिरraपूर्णांक_minmax(runसमय,
					   SNDRV_PCM_HW_PARAM_BUFFER_BYTES,
					   1024, अच_पूर्णांक_उच्च);
	अगर (err < 0)
		जाओ मुक्त_pcm;

	apcm->समयr = ct_समयr_instance_new(atc->समयr, apcm);
	अगर (!apcm->समयr) अणु
		err = -ENOMEM;
		जाओ मुक्त_pcm;
	पूर्ण
	runसमय->निजी_data = apcm;
	runसमय->निजी_मुक्त = ct_atc_pcm_मुक्त_substream;

	वापस 0;

मुक्त_pcm:
	kमुक्त(apcm);
	वापस err;
पूर्ण

अटल पूर्णांक ct_pcm_capture_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	/* The ct_atc_pcm object will be मुक्तd by runसमय->निजी_मुक्त */
	/* TODO: Notअगरy mixer inactive. */
	वापस 0;
पूर्ण

अटल पूर्णांक ct_pcm_capture_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	पूर्णांक err;
	काष्ठा ct_atc *atc = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा ct_atc_pcm *apcm = runसमय->निजी_data;

	err = atc->pcm_capture_prepare(atc, apcm);
	अगर (err < 0) अणु
		dev_err(atc->card->dev,
			"Preparing pcm capture failed!!!\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
ct_pcm_capture_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा ct_atc *atc = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा ct_atc_pcm *apcm = runसमय->निजी_data;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		atc->pcm_capture_start(atc, apcm);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		atc->pcm_capture_stop(atc, apcm);
		अवरोध;
	शेष:
		atc->pcm_capture_stop(atc, apcm);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t
ct_pcm_capture_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	अचिन्हित दीर्घ position;
	काष्ठा ct_atc *atc = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा ct_atc_pcm *apcm = runसमय->निजी_data;

	/* Read out playback position */
	position = atc->pcm_capture_position(atc, apcm);
	position = bytes_to_frames(runसमय, position);
	अगर (position >= runसमय->buffer_size)
		position = 0;
	वापस position;
पूर्ण

/* PCM चालकs क्रम playback */
अटल स्थिर काष्ठा snd_pcm_ops ct_pcm_playback_ops = अणु
	.खोलो	 	= ct_pcm_playback_खोलो,
	.बंद		= ct_pcm_playback_बंद,
	.hw_params	= ct_pcm_hw_params,
	.hw_मुक्त	= ct_pcm_hw_मुक्त,
	.prepare	= ct_pcm_playback_prepare,
	.trigger	= ct_pcm_playback_trigger,
	.poपूर्णांकer	= ct_pcm_playback_poपूर्णांकer,
पूर्ण;

/* PCM चालकs क्रम capture */
अटल स्थिर काष्ठा snd_pcm_ops ct_pcm_capture_ops = अणु
	.खोलो	 	= ct_pcm_capture_खोलो,
	.बंद		= ct_pcm_capture_बंद,
	.hw_params	= ct_pcm_hw_params,
	.hw_मुक्त	= ct_pcm_hw_मुक्त,
	.prepare	= ct_pcm_capture_prepare,
	.trigger	= ct_pcm_capture_trigger,
	.poपूर्णांकer	= ct_pcm_capture_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_chmap_elem surround_map[] = अणु
	अणु .channels = 1,
	  .map = अणु SNDRV_CHMAP_MONO पूर्ण पूर्ण,
	अणु .channels = 2,
	  .map = अणु SNDRV_CHMAP_RL, SNDRV_CHMAP_RR पूर्ण पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_chmap_elem clfe_map[] = अणु
	अणु .channels = 1,
	  .map = अणु SNDRV_CHMAP_MONO पूर्ण पूर्ण,
	अणु .channels = 2,
	  .map = अणु SNDRV_CHMAP_FC, SNDRV_CHMAP_LFE पूर्ण पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_chmap_elem side_map[] = अणु
	अणु .channels = 1,
	  .map = अणु SNDRV_CHMAP_MONO पूर्ण पूर्ण,
	अणु .channels = 2,
	  .map = अणु SNDRV_CHMAP_SL, SNDRV_CHMAP_SR पूर्ण पूर्ण,
	अणु पूर्ण
पूर्ण;

/* Create ALSA pcm device */
पूर्णांक ct_alsa_pcm_create(काष्ठा ct_atc *atc,
		       क्रमागत CTALSADEVS device,
		       स्थिर अक्षर *device_name)
अणु
	काष्ठा snd_pcm *pcm;
	स्थिर काष्ठा snd_pcm_chmap_elem *map;
	पूर्णांक chs;
	पूर्णांक err;
	पूर्णांक playback_count, capture_count;

	playback_count = (IEC958 == device) ? 1 : 256;
	capture_count = (FRONT == device) ? 1 : 0;
	err = snd_pcm_new(atc->card, "ctxfi", device,
			  playback_count, capture_count, &pcm);
	अगर (err < 0) अणु
		dev_err(atc->card->dev, "snd_pcm_new failed!! Err=%d\n",
			err);
		वापस err;
	पूर्ण

	pcm->निजी_data = atc;
	pcm->info_flags = 0;
	pcm->dev_subclass = SNDRV_PCM_SUBCLASS_GENERIC_MIX;
	strscpy(pcm->name, device_name, माप(pcm->name));

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &ct_pcm_playback_ops);

	अगर (FRONT == device)
		snd_pcm_set_ops(pcm,
				SNDRV_PCM_STREAM_CAPTURE, &ct_pcm_capture_ops);

	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV_SG,
				       &atc->pci->dev, 128*1024, 128*1024);

	chs = 2;
	चयन (device) अणु
	हाल FRONT:
		chs = 8;
		map = snd_pcm_std_chmaps;
		अवरोध;
	हाल SURROUND:
		map = surround_map;
		अवरोध;
	हाल CLFE:
		map = clfe_map;
		अवरोध;
	हाल SIDE:
		map = side_map;
		अवरोध;
	शेष:
		map = snd_pcm_std_chmaps;
		अवरोध;
	पूर्ण
	err = snd_pcm_add_chmap_ctls(pcm, SNDRV_PCM_STREAM_PLAYBACK, map, chs,
				     0, शून्य);
	अगर (err < 0)
		वापस err;

#अगर_घोषित CONFIG_PM_SLEEP
	atc->pcms[device] = pcm;
#पूर्ण_अगर

	वापस 0;
पूर्ण
