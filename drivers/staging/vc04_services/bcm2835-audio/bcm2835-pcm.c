<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright 2011 Broadcom Corporation.  All rights reserved. */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>

#समावेश <sound/asoundef.h>

#समावेश "bcm2835.h"

/* hardware definition */
अटल स्थिर काष्ठा snd_pcm_hardware snd_bcm2835_playback_hw = अणु
	.info = (SNDRV_PCM_INFO_INTERLEAVED | SNDRV_PCM_INFO_BLOCK_TRANSFER |
		 SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_MMAP_VALID |
		 SNDRV_PCM_INFO_SYNC_APPLPTR | SNDRV_PCM_INFO_BATCH),
	.क्रमmats = SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S16_LE,
	.rates = SNDRV_PCM_RATE_CONTINUOUS | SNDRV_PCM_RATE_8000_192000,
	.rate_min = 8000,
	.rate_max = 192000,
	.channels_min = 1,
	.channels_max = 8,
	.buffer_bytes_max = 512 * 1024,
	.period_bytes_min = 1 * 1024,
	.period_bytes_max = 512 * 1024,
	.periods_min = 1,
	.periods_max = 128,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware snd_bcm2835_playback_spdअगर_hw = अणु
	.info = (SNDRV_PCM_INFO_INTERLEAVED | SNDRV_PCM_INFO_BLOCK_TRANSFER |
		 SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_MMAP_VALID |
		 SNDRV_PCM_INFO_SYNC_APPLPTR | SNDRV_PCM_INFO_BATCH),
	.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	.rates = SNDRV_PCM_RATE_CONTINUOUS | SNDRV_PCM_RATE_44100 |
	SNDRV_PCM_RATE_48000,
	.rate_min = 44100,
	.rate_max = 48000,
	.channels_min = 2,
	.channels_max = 2,
	.buffer_bytes_max = 128 * 1024,
	.period_bytes_min = 1 * 1024,
	.period_bytes_max = 128 * 1024,
	.periods_min = 1,
	.periods_max = 128,
पूर्ण;

अटल व्योम snd_bcm2835_playback_मुक्त(काष्ठा snd_pcm_runसमय *runसमय)
अणु
	kमुक्त(runसमय->निजी_data);
पूर्ण

व्योम bcm2835_playback_fअगरo(काष्ठा bcm2835_alsa_stream *alsa_stream,
			   अचिन्हित पूर्णांक bytes)
अणु
	काष्ठा snd_pcm_substream *substream = alsa_stream->substream;
	अचिन्हित पूर्णांक pos;

	अगर (!alsa_stream->period_size)
		वापस;

	अगर (bytes >= alsa_stream->buffer_size) अणु
		snd_pcm_stream_lock(substream);
		snd_pcm_stop(substream,
			     alsa_stream->draining ?
			     SNDRV_PCM_STATE_SETUP :
			     SNDRV_PCM_STATE_XRUN);
		snd_pcm_stream_unlock(substream);
		वापस;
	पूर्ण

	pos = atomic_पढ़ो(&alsa_stream->pos);
	pos += bytes;
	pos %= alsa_stream->buffer_size;
	atomic_set(&alsa_stream->pos, pos);

	alsa_stream->period_offset += bytes;
	alsa_stream->पूर्णांकerpolate_start = kसमय_get();
	अगर (alsa_stream->period_offset >= alsa_stream->period_size) अणु
		alsa_stream->period_offset %= alsa_stream->period_size;
		snd_pcm_period_elapsed(substream);
	पूर्ण
पूर्ण

/* खोलो callback */
अटल पूर्णांक snd_bcm2835_playback_खोलो_generic(
	काष्ठा snd_pcm_substream *substream, पूर्णांक spdअगर)
अणु
	काष्ठा bcm2835_chip *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा bcm2835_alsa_stream *alsa_stream;
	पूर्णांक idx;
	पूर्णांक err;

	mutex_lock(&chip->audio_mutex);
	idx = substream->number;

	अगर (spdअगर && chip->खोलोed) अणु
		err = -EBUSY;
		जाओ out;
	पूर्ण अन्यथा अगर (!spdअगर && (chip->खोलोed & (1 << idx))) अणु
		err = -EBUSY;
		जाओ out;
	पूर्ण
	अगर (idx >= MAX_SUBSTREAMS) अणु
		dev_err(chip->dev,
			"substream(%d) device doesn't exist max(%d) substreams allowed\n",
			idx, MAX_SUBSTREAMS);
		err = -ENODEV;
		जाओ out;
	पूर्ण

	alsa_stream = kzalloc(माप(*alsa_stream), GFP_KERNEL);
	अगर (!alsa_stream) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	/* Initialise alsa_stream */
	alsa_stream->chip = chip;
	alsa_stream->substream = substream;
	alsa_stream->idx = idx;

	err = bcm2835_audio_खोलो(alsa_stream);
	अगर (err) अणु
		kमुक्त(alsa_stream);
		जाओ out;
	पूर्ण
	runसमय->निजी_data = alsa_stream;
	runसमय->निजी_मुक्त = snd_bcm2835_playback_मुक्त;
	अगर (spdअगर) अणु
		runसमय->hw = snd_bcm2835_playback_spdअगर_hw;
	पूर्ण अन्यथा अणु
		/* clear spdअगर status, as we are not in spdअगर mode */
		chip->spdअगर_status = 0;
		runसमय->hw = snd_bcm2835_playback_hw;
	पूर्ण
	/* minimum 16 bytes alignment (क्रम vchiq bulk transfers) */
	snd_pcm_hw_स्थिरraपूर्णांक_step(runसमय,
				   0,
				   SNDRV_PCM_HW_PARAM_PERIOD_BYTES,
				   16);

	/* position update is in 10ms order */
	snd_pcm_hw_स्थिरraपूर्णांक_minmax(runसमय,
				     SNDRV_PCM_HW_PARAM_PERIOD_TIME,
				     10 * 1000, अच_पूर्णांक_उच्च);

	chip->alsa_stream[idx] = alsa_stream;

	chip->खोलोed |= (1 << idx);

out:
	mutex_unlock(&chip->audio_mutex);

	वापस err;
पूर्ण

अटल पूर्णांक snd_bcm2835_playback_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	वापस snd_bcm2835_playback_खोलो_generic(substream, 0);
पूर्ण

अटल पूर्णांक snd_bcm2835_playback_spdअगर_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	वापस snd_bcm2835_playback_खोलो_generic(substream, 1);
पूर्ण

अटल पूर्णांक snd_bcm2835_playback_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा bcm2835_alsa_stream *alsa_stream;
	काष्ठा snd_pcm_runसमय *runसमय;
	काष्ठा bcm2835_chip *chip;

	chip = snd_pcm_substream_chip(substream);
	mutex_lock(&chip->audio_mutex);
	runसमय = substream->runसमय;
	alsa_stream = runसमय->निजी_data;

	alsa_stream->period_size = 0;
	alsa_stream->buffer_size = 0;

	bcm2835_audio_बंद(alsa_stream);
	alsa_stream->chip->alsa_stream[alsa_stream->idx] = शून्य;
	/*
	 * Do not मुक्त up alsa_stream here, it will be मुक्तd up by
	 * runसमय->निजी_मुक्त callback we रेजिस्टरed in *_खोलो above
	 */

	chip->खोलोed &= ~(1 << substream->number);

	mutex_unlock(&chip->audio_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_bcm2835_pcm_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा bcm2835_chip *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा bcm2835_alsa_stream *alsa_stream = runसमय->निजी_data;
	पूर्णांक channels;
	पूर्णांक err;

	/* notअगरy the vchiq that it should enter spdअगर passthrough mode by
	 * setting channels=0 (see
	 * https://github.com/raspberrypi/linux/issues/528)
	 */
	अगर (chip->spdअगर_status & IEC958_AES0_NONAUDIO)
		channels = 0;
	अन्यथा
		channels = runसमय->channels;

	err = bcm2835_audio_set_params(alsa_stream, channels,
				       runसमय->rate,
				       snd_pcm_क्रमmat_width(runसमय->क्रमmat));
	अगर (err < 0)
		वापस err;

	स_रखो(&alsa_stream->pcm_indirect, 0, माप(alsa_stream->pcm_indirect));

	alsa_stream->pcm_indirect.hw_buffer_size =
		alsa_stream->pcm_indirect.sw_buffer_size =
		snd_pcm_lib_buffer_bytes(substream);

	alsa_stream->buffer_size = snd_pcm_lib_buffer_bytes(substream);
	alsa_stream->period_size = snd_pcm_lib_period_bytes(substream);
	atomic_set(&alsa_stream->pos, 0);
	alsa_stream->period_offset = 0;
	alsa_stream->draining = false;
	alsa_stream->पूर्णांकerpolate_start = kसमय_get();

	वापस 0;
पूर्ण

अटल व्योम snd_bcm2835_pcm_transfer(काष्ठा snd_pcm_substream *substream,
				     काष्ठा snd_pcm_indirect *rec, माप_प्रकार bytes)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा bcm2835_alsa_stream *alsa_stream = runसमय->निजी_data;
	व्योम *src = (व्योम *) (substream->runसमय->dma_area + rec->sw_data);

	bcm2835_audio_ग_लिखो(alsa_stream, bytes, src);
पूर्ण

अटल पूर्णांक snd_bcm2835_pcm_ack(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा bcm2835_alsa_stream *alsa_stream = runसमय->निजी_data;
	काष्ठा snd_pcm_indirect *pcm_indirect = &alsa_stream->pcm_indirect;

	वापस snd_pcm_indirect_playback_transfer(substream, pcm_indirect,
						  snd_bcm2835_pcm_transfer);
पूर्ण

/* trigger callback */
अटल पूर्णांक snd_bcm2835_pcm_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा bcm2835_alsa_stream *alsa_stream = runसमय->निजी_data;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		वापस bcm2835_audio_start(alsa_stream);
	हाल SNDRV_PCM_TRIGGER_DRAIN:
		alsa_stream->draining = true;
		वापस bcm2835_audio_drain(alsa_stream);
	हाल SNDRV_PCM_TRIGGER_STOP:
		वापस bcm2835_audio_stop(alsa_stream);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/* poपूर्णांकer callback */
अटल snd_pcm_uframes_t
snd_bcm2835_pcm_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा bcm2835_alsa_stream *alsa_stream = runसमय->निजी_data;
	kसमय_प्रकार now = kसमय_get();

	/* Give userspace better delay reporting by पूर्णांकerpolating between GPU
	 * notअगरications, assuming audio speed is बंद enough to the घड़ी
	 * used क्रम kसमय
	 */

	अगर ((kसमय_प्रकारo_ns(alsa_stream->पूर्णांकerpolate_start)) &&
	    (kसमय_compare(alsa_stream->पूर्णांकerpolate_start, now) < 0)) अणु
		u64 पूर्णांकerval =
			(kसमय_प्रकारo_ns(kसमय_sub(now,
				alsa_stream->पूर्णांकerpolate_start)));
		u64 frames_output_in_पूर्णांकerval =
			भाग_u64((पूर्णांकerval * runसमय->rate), 1000000000);
		snd_pcm_sframes_t frames_output_in_पूर्णांकerval_sized =
			-frames_output_in_पूर्णांकerval;
		runसमय->delay = frames_output_in_पूर्णांकerval_sized;
	पूर्ण

	वापस snd_pcm_indirect_playback_poपूर्णांकer(substream,
		&alsa_stream->pcm_indirect,
		atomic_पढ़ो(&alsa_stream->pos));
पूर्ण

/* चालकs */
अटल स्थिर काष्ठा snd_pcm_ops snd_bcm2835_playback_ops = अणु
	.खोलो = snd_bcm2835_playback_खोलो,
	.बंद = snd_bcm2835_playback_बंद,
	.prepare = snd_bcm2835_pcm_prepare,
	.trigger = snd_bcm2835_pcm_trigger,
	.poपूर्णांकer = snd_bcm2835_pcm_poपूर्णांकer,
	.ack = snd_bcm2835_pcm_ack,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_bcm2835_playback_spdअगर_ops = अणु
	.खोलो = snd_bcm2835_playback_spdअगर_खोलो,
	.बंद = snd_bcm2835_playback_बंद,
	.prepare = snd_bcm2835_pcm_prepare,
	.trigger = snd_bcm2835_pcm_trigger,
	.poपूर्णांकer = snd_bcm2835_pcm_poपूर्णांकer,
	.ack = snd_bcm2835_pcm_ack,
पूर्ण;

/* create a pcm device */
पूर्णांक snd_bcm2835_new_pcm(काष्ठा bcm2835_chip *chip, स्थिर अक्षर *name,
			पूर्णांक idx, क्रमागत snd_bcm2835_route route,
			u32 numchannels, bool spdअगर)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;

	err = snd_pcm_new(chip->card, name, idx, numchannels, 0, &pcm);
	अगर (err)
		वापस err;

	pcm->निजी_data = chip;
	pcm->nonatomic = true;
	strscpy(pcm->name, name, माप(pcm->name));
	अगर (!spdअगर) अणु
		chip->dest = route;
		chip->volume = 0;
		chip->mute = CTRL_VOL_UNMUTE;
	पूर्ण

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK,
			spdअगर ? &snd_bcm2835_playback_spdअगर_ops :
			&snd_bcm2835_playback_ops);

	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV,
				       chip->card->dev, 128 * 1024, 128 * 1024);

	अगर (spdअगर)
		chip->pcm_spdअगर = pcm;
	अन्यथा
		chip->pcm = pcm;
	वापस 0;
पूर्ण
