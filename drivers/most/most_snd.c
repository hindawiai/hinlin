<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * sound.c - Sound component क्रम Mostcore
 *
 * Copyright (C) 2015 Microchip Technology Germany II GmbH & Co. KG
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <linux/sched.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/most.h>

#घोषणा DRIVER_NAME "sound"
#घोषणा STRING_SIZE	80

अटल काष्ठा most_component comp;

/**
 * काष्ठा channel - निजी काष्ठाure to keep channel specअगरic data
 * @substream: stores the substream काष्ठाure
 * @अगरace: पूर्णांकerface क्रम which the channel beदीर्घs to
 * @cfg: channel configuration
 * @card: रेजिस्टरed sound card
 * @list: list क्रम निजी use
 * @id: channel index
 * @period_pos: current period position (ring buffer)
 * @buffer_pos: current buffer position (ring buffer)
 * @is_stream_running: identअगरies whether a stream is running or not
 * @खोलोed: set when the stream is खोलोed
 * @playback_task: playback thपढ़ो
 * @playback_रुकोq: रुकोq used by playback thपढ़ो
 */
काष्ठा channel अणु
	काष्ठा snd_pcm_substream *substream;
	काष्ठा snd_pcm_hardware pcm_hardware;
	काष्ठा most_पूर्णांकerface *अगरace;
	काष्ठा most_channel_config *cfg;
	काष्ठा snd_card *card;
	काष्ठा list_head list;
	पूर्णांक id;
	अचिन्हित पूर्णांक period_pos;
	अचिन्हित पूर्णांक buffer_pos;
	bool is_stream_running;
	काष्ठा task_काष्ठा *playback_task;
	रुको_queue_head_t playback_रुकोq;
	व्योम (*copy_fn)(व्योम *alsa, व्योम *most, अचिन्हित पूर्णांक bytes);
पूर्ण;

काष्ठा sound_adapter अणु
	काष्ठा list_head dev_list;
	काष्ठा most_पूर्णांकerface *अगरace;
	काष्ठा snd_card *card;
	काष्ठा list_head list;
	bool रेजिस्टरed;
	पूर्णांक pcm_dev_idx;
पूर्ण;

अटल काष्ठा list_head adpt_list;

#घोषणा MOST_PCM_INFO (SNDRV_PCM_INFO_MMAP | \
		       SNDRV_PCM_INFO_MMAP_VALID | \
		       SNDRV_PCM_INFO_BATCH | \
		       SNDRV_PCM_INFO_INTERLEAVED | \
		       SNDRV_PCM_INFO_BLOCK_TRANSFER)

अटल व्योम swap_copy16(u16 *dest, स्थिर u16 *source, अचिन्हित पूर्णांक bytes)
अणु
	अचिन्हित पूर्णांक i = 0;

	जबतक (i < (bytes / 2)) अणु
		dest[i] = swab16(source[i]);
		i++;
	पूर्ण
पूर्ण

अटल व्योम swap_copy24(u8 *dest, स्थिर u8 *source, अचिन्हित पूर्णांक bytes)
अणु
	अचिन्हित पूर्णांक i = 0;

	अगर (bytes < 2)
		वापस;
	जबतक (i < bytes - 2) अणु
		dest[i] = source[i + 2];
		dest[i + 1] = source[i + 1];
		dest[i + 2] = source[i];
		i += 3;
	पूर्ण
पूर्ण

अटल व्योम swap_copy32(u32 *dest, स्थिर u32 *source, अचिन्हित पूर्णांक bytes)
अणु
	अचिन्हित पूर्णांक i = 0;

	जबतक (i < bytes / 4) अणु
		dest[i] = swab32(source[i]);
		i++;
	पूर्ण
पूर्ण

अटल व्योम alsa_to_most_स_नकल(व्योम *alsa, व्योम *most, अचिन्हित पूर्णांक bytes)
अणु
	स_नकल(most, alsa, bytes);
पूर्ण

अटल व्योम alsa_to_most_copy16(व्योम *alsa, व्योम *most, अचिन्हित पूर्णांक bytes)
अणु
	swap_copy16(most, alsa, bytes);
पूर्ण

अटल व्योम alsa_to_most_copy24(व्योम *alsa, व्योम *most, अचिन्हित पूर्णांक bytes)
अणु
	swap_copy24(most, alsa, bytes);
पूर्ण

अटल व्योम alsa_to_most_copy32(व्योम *alsa, व्योम *most, अचिन्हित पूर्णांक bytes)
अणु
	swap_copy32(most, alsa, bytes);
पूर्ण

अटल व्योम most_to_alsa_स_नकल(व्योम *alsa, व्योम *most, अचिन्हित पूर्णांक bytes)
अणु
	स_नकल(alsa, most, bytes);
पूर्ण

अटल व्योम most_to_alsa_copy16(व्योम *alsa, व्योम *most, अचिन्हित पूर्णांक bytes)
अणु
	swap_copy16(alsa, most, bytes);
पूर्ण

अटल व्योम most_to_alsa_copy24(व्योम *alsa, व्योम *most, अचिन्हित पूर्णांक bytes)
अणु
	swap_copy24(alsa, most, bytes);
पूर्ण

अटल व्योम most_to_alsa_copy32(व्योम *alsa, व्योम *most, अचिन्हित पूर्णांक bytes)
अणु
	swap_copy32(alsa, most, bytes);
पूर्ण

/**
 * get_channel - get poपूर्णांकer to channel
 * @अगरace: पूर्णांकerface काष्ठाure
 * @channel_id: channel ID
 *
 * This traverses the channel list and वापसs the channel matching the
 * ID and पूर्णांकerface.
 *
 * Returns poपूर्णांकer to channel on success or शून्य otherwise.
 */
अटल काष्ठा channel *get_channel(काष्ठा most_पूर्णांकerface *अगरace,
				   पूर्णांक channel_id)
अणु
	काष्ठा sound_adapter *adpt = अगरace->priv;
	काष्ठा channel *channel;

	list_क्रम_each_entry(channel, &adpt->dev_list, list) अणु
		अगर ((channel->अगरace == अगरace) && (channel->id == channel_id))
			वापस channel;
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * copy_data - implements data copying function
 * @channel: channel
 * @mbo: MBO from core
 *
 * Copy data from/to ring buffer to/from MBO and update the buffer position
 */
अटल bool copy_data(काष्ठा channel *channel, काष्ठा mbo *mbo)
अणु
	काष्ठा snd_pcm_runसमय *स्थिर runसमय = channel->substream->runसमय;
	अचिन्हित पूर्णांक स्थिर frame_bytes = channel->cfg->subbuffer_size;
	अचिन्हित पूर्णांक स्थिर buffer_size = runसमय->buffer_size;
	अचिन्हित पूर्णांक frames;
	अचिन्हित पूर्णांक fr0;

	अगर (channel->cfg->direction & MOST_CH_RX)
		frames = mbo->processed_length / frame_bytes;
	अन्यथा
		frames = mbo->buffer_length / frame_bytes;
	fr0 = min(buffer_size - channel->buffer_pos, frames);

	channel->copy_fn(runसमय->dma_area + channel->buffer_pos * frame_bytes,
			 mbo->virt_address,
			 fr0 * frame_bytes);

	अगर (frames > fr0) अणु
		/* wrap around at end of ring buffer */
		channel->copy_fn(runसमय->dma_area,
				 mbo->virt_address + fr0 * frame_bytes,
				 (frames - fr0) * frame_bytes);
	पूर्ण

	channel->buffer_pos += frames;
	अगर (channel->buffer_pos >= buffer_size)
		channel->buffer_pos -= buffer_size;
	channel->period_pos += frames;
	अगर (channel->period_pos >= runसमय->period_size) अणु
		channel->period_pos -= runसमय->period_size;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/**
 * playback_thपढ़ो - function implements the playback thपढ़ो
 * @data: निजी data
 *
 * Thपढ़ो which करोes the playback functionality in a loop. It रुकोs क्रम a मुक्त
 * MBO from mostcore क्रम a particular channel and copy the data from ring buffer
 * to MBO. Submit the MBO back to mostcore, after copying the data.
 *
 * Returns 0 on success or error code otherwise.
 */
अटल पूर्णांक playback_thपढ़ो(व्योम *data)
अणु
	काष्ठा channel *स्थिर channel = data;

	जबतक (!kthपढ़ो_should_stop()) अणु
		काष्ठा mbo *mbo = शून्य;
		bool period_elapsed = false;

		रुको_event_पूर्णांकerruptible(
			channel->playback_रुकोq,
			kthपढ़ो_should_stop() ||
			(channel->is_stream_running &&
			 (mbo = most_get_mbo(channel->अगरace, channel->id,
					     &comp))));
		अगर (!mbo)
			जारी;

		अगर (channel->is_stream_running)
			period_elapsed = copy_data(channel, mbo);
		अन्यथा
			स_रखो(mbo->virt_address, 0, mbo->buffer_length);

		most_submit_mbo(mbo);
		अगर (period_elapsed)
			snd_pcm_period_elapsed(channel->substream);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * pcm_खोलो - implements खोलो callback function क्रम PCM middle layer
 * @substream: poपूर्णांकer to ALSA PCM substream
 *
 * This is called when a PCM substream is खोलोed. At least, the function should
 * initialize the runसमय->hw record.
 *
 * Returns 0 on success or error code otherwise.
 */
अटल पूर्णांक pcm_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा channel *channel = substream->निजी_data;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा most_channel_config *cfg = channel->cfg;
	पूर्णांक ret;

	channel->substream = substream;

	अगर (cfg->direction == MOST_CH_TX) अणु
		channel->playback_task = kthपढ़ो_run(playback_thपढ़ो, channel,
						     "most_audio_playback");
		अगर (IS_ERR(channel->playback_task)) अणु
			pr_err("Couldn't start thread\n");
			वापस PTR_ERR(channel->playback_task);
		पूर्ण
	पूर्ण

	ret = most_start_channel(channel->अगरace, channel->id, &comp);
	अगर (ret) अणु
		pr_err("most_start_channel() failed!\n");
		अगर (cfg->direction == MOST_CH_TX)
			kthपढ़ो_stop(channel->playback_task);
		वापस ret;
	पूर्ण

	runसमय->hw = channel->pcm_hardware;
	वापस 0;
पूर्ण

/**
 * pcm_बंद - implements बंद callback function क्रम PCM middle layer
 * @substream: sub-stream poपूर्णांकer
 *
 * Obviously, this is called when a PCM substream is बंदd. Any निजी
 * instance क्रम a PCM substream allocated in the खोलो callback will be
 * released here.
 *
 * Returns 0 on success or error code otherwise.
 */
अटल पूर्णांक pcm_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा channel *channel = substream->निजी_data;

	अगर (channel->cfg->direction == MOST_CH_TX)
		kthपढ़ो_stop(channel->playback_task);
	most_stop_channel(channel->अगरace, channel->id, &comp);
	वापस 0;
पूर्ण

/**
 * pcm_prepare - implements prepare callback function क्रम PCM middle layer
 * @substream: substream poपूर्णांकer
 *
 * This callback is called when the PCM is "prepared". Format rate, sample rate,
 * etc., can be set here. This callback can be called many बार at each setup.
 *
 * Returns 0 on success or error code otherwise.
 */
अटल पूर्णांक pcm_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा channel *channel = substream->निजी_data;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा most_channel_config *cfg = channel->cfg;
	पूर्णांक width = snd_pcm_क्रमmat_physical_width(runसमय->क्रमmat);

	channel->copy_fn = शून्य;

	अगर (cfg->direction == MOST_CH_TX) अणु
		अगर (snd_pcm_क्रमmat_big_endian(runसमय->क्रमmat) || width == 8)
			channel->copy_fn = alsa_to_most_स_नकल;
		अन्यथा अगर (width == 16)
			channel->copy_fn = alsa_to_most_copy16;
		अन्यथा अगर (width == 24)
			channel->copy_fn = alsa_to_most_copy24;
		अन्यथा अगर (width == 32)
			channel->copy_fn = alsa_to_most_copy32;
	पूर्ण अन्यथा अणु
		अगर (snd_pcm_क्रमmat_big_endian(runसमय->क्रमmat) || width == 8)
			channel->copy_fn = most_to_alsa_स_नकल;
		अन्यथा अगर (width == 16)
			channel->copy_fn = most_to_alsa_copy16;
		अन्यथा अगर (width == 24)
			channel->copy_fn = most_to_alsa_copy24;
		अन्यथा अगर (width == 32)
			channel->copy_fn = most_to_alsa_copy32;
	पूर्ण

	अगर (!channel->copy_fn)
		वापस -EINVAL;
	channel->period_pos = 0;
	channel->buffer_pos = 0;
	वापस 0;
पूर्ण

/**
 * pcm_trigger - implements trigger callback function क्रम PCM middle layer
 * @substream: substream poपूर्णांकer
 * @cmd: action to perक्रमm
 *
 * This is called when the PCM is started, stopped or छोड़ोd. The action will be
 * specअगरied in the second argument, SNDRV_PCM_TRIGGER_XXX
 *
 * Returns 0 on success or error code otherwise.
 */
अटल पूर्णांक pcm_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा channel *channel = substream->निजी_data;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		channel->is_stream_running = true;
		wake_up_पूर्णांकerruptible(&channel->playback_रुकोq);
		वापस 0;

	हाल SNDRV_PCM_TRIGGER_STOP:
		channel->is_stream_running = false;
		वापस 0;

	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * pcm_poपूर्णांकer - implements poपूर्णांकer callback function क्रम PCM middle layer
 * @substream: substream poपूर्णांकer
 *
 * This callback is called when the PCM middle layer inquires the current
 * hardware position on the buffer. The position must be वापसed in frames,
 * ranging from 0 to buffer_size-1.
 */
अटल snd_pcm_uframes_t pcm_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा channel *channel = substream->निजी_data;

	वापस channel->buffer_pos;
पूर्ण

/**
 * Initialization of काष्ठा snd_pcm_ops
 */
अटल स्थिर काष्ठा snd_pcm_ops pcm_ops = अणु
	.खोलो       = pcm_खोलो,
	.बंद      = pcm_बंद,
	.prepare    = pcm_prepare,
	.trigger    = pcm_trigger,
	.poपूर्णांकer    = pcm_poपूर्णांकer,
पूर्ण;

अटल पूर्णांक split_arg_list(अक्षर *buf, u16 *ch_num, अक्षर **sample_res)
अणु
	अक्षर *num;
	पूर्णांक ret;

	num = strsep(&buf, "x");
	अगर (!num)
		जाओ err;
	ret = kstrtou16(num, 0, ch_num);
	अगर (ret)
		जाओ err;
	*sample_res = strsep(&buf, ".\n");
	अगर (!*sample_res)
		जाओ err;
	वापस 0;

err:
	pr_err("Bad PCM format\n");
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा sample_resolution_info अणु
	स्थिर अक्षर *sample_res;
	पूर्णांक bytes;
	u64 क्रमmats;
पूर्ण sinfo[] = अणु
	अणु "8", 1, SNDRV_PCM_FMTBIT_S8 पूर्ण,
	अणु "16", 2, SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S16_BE पूर्ण,
	अणु "24", 3, SNDRV_PCM_FMTBIT_S24_3LE | SNDRV_PCM_FMTBIT_S24_3BE पूर्ण,
	अणु "32", 4, SNDRV_PCM_FMTBIT_S32_LE | SNDRV_PCM_FMTBIT_S32_BE पूर्ण,
पूर्ण;

अटल पूर्णांक audio_set_hw_params(काष्ठा snd_pcm_hardware *pcm_hw,
			       u16 ch_num, अक्षर *sample_res,
			       काष्ठा most_channel_config *cfg)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(sinfo); i++) अणु
		अगर (!म_भेद(sample_res, sinfo[i].sample_res))
			जाओ found;
	पूर्ण
	pr_err("Unsupported PCM format\n");
	वापस -EINVAL;

found:
	अगर (!ch_num) अणु
		pr_err("Bad number of channels\n");
		वापस -EINVAL;
	पूर्ण

	अगर (cfg->subbuffer_size != ch_num * sinfo[i].bytes) अणु
		pr_err("Audio resolution doesn't fit subbuffer size\n");
		वापस -EINVAL;
	पूर्ण

	pcm_hw->info = MOST_PCM_INFO;
	pcm_hw->rates = SNDRV_PCM_RATE_48000;
	pcm_hw->rate_min = 48000;
	pcm_hw->rate_max = 48000;
	pcm_hw->buffer_bytes_max = cfg->num_buffers * cfg->buffer_size;
	pcm_hw->period_bytes_min = cfg->buffer_size;
	pcm_hw->period_bytes_max = cfg->buffer_size;
	pcm_hw->periods_min = 1;
	pcm_hw->periods_max = cfg->num_buffers;
	pcm_hw->channels_min = ch_num;
	pcm_hw->channels_max = ch_num;
	pcm_hw->क्रमmats = sinfo[i].क्रमmats;
	वापस 0;
पूर्ण

अटल व्योम release_adapter(काष्ठा sound_adapter *adpt)
अणु
	काष्ठा channel *channel, *पंचांगp;

	list_क्रम_each_entry_safe(channel, पंचांगp, &adpt->dev_list, list) अणु
		list_del(&channel->list);
		kमुक्त(channel);
	पूर्ण
	अगर (adpt->card)
		snd_card_मुक्त(adpt->card);
	list_del(&adpt->list);
	kमुक्त(adpt);
पूर्ण

/**
 * audio_probe_channel - probe function of the driver module
 * @अगरace: poपूर्णांकer to पूर्णांकerface instance
 * @channel_id: channel index/ID
 * @cfg: poपूर्णांकer to actual channel configuration
 * @arg_list: string that provides the name of the device to be created in /dev
 *	      plus the desired audio resolution
 *
 * Creates sound card, pcm device, sets pcm ops and रेजिस्टरs sound card.
 *
 * Returns 0 on success or error code otherwise.
 */
अटल पूर्णांक audio_probe_channel(काष्ठा most_पूर्णांकerface *अगरace, पूर्णांक channel_id,
			       काष्ठा most_channel_config *cfg,
			       अक्षर *device_name, अक्षर *arg_list)
अणु
	काष्ठा channel *channel;
	काष्ठा sound_adapter *adpt;
	काष्ठा snd_pcm *pcm;
	पूर्णांक playback_count = 0;
	पूर्णांक capture_count = 0;
	पूर्णांक ret;
	पूर्णांक direction;
	u16 ch_num;
	अक्षर *sample_res;
	अक्षर arg_list_cpy[STRING_SIZE];

	अगर (cfg->data_type != MOST_CH_SYNC) अणु
		pr_err("Incompatible channel type\n");
		वापस -EINVAL;
	पूर्ण
	strscpy(arg_list_cpy, arg_list, STRING_SIZE);
	ret = split_arg_list(arg_list_cpy, &ch_num, &sample_res);
	अगर (ret < 0)
		वापस ret;

	list_क्रम_each_entry(adpt, &adpt_list, list) अणु
		अगर (adpt->अगरace != अगरace)
			जारी;
		अगर (adpt->रेजिस्टरed)
			वापस -ENOSPC;
		adpt->pcm_dev_idx++;
		जाओ skip_adpt_alloc;
	पूर्ण
	adpt = kzalloc(माप(*adpt), GFP_KERNEL);
	अगर (!adpt)
		वापस -ENOMEM;

	adpt->अगरace = अगरace;
	INIT_LIST_HEAD(&adpt->dev_list);
	अगरace->priv = adpt;
	list_add_tail(&adpt->list, &adpt_list);
	ret = snd_card_new(अगरace->driver_dev, -1, "INIC", THIS_MODULE,
			   माप(*channel), &adpt->card);
	अगर (ret < 0)
		जाओ err_मुक्त_adpt;
	snम_लिखो(adpt->card->driver, माप(adpt->card->driver),
		 "%s", DRIVER_NAME);
	snम_लिखो(adpt->card->लघुname, माप(adpt->card->लघुname),
		 "Microchip INIC");
	snम_लिखो(adpt->card->दीर्घname, माप(adpt->card->दीर्घname),
		 "%s at %s", adpt->card->लघुname, अगरace->description);
skip_adpt_alloc:
	अगर (get_channel(अगरace, channel_id)) अणु
		pr_err("channel (%s:%d) is already linked\n",
		       अगरace->description, channel_id);
		वापस -EEXIST;
	पूर्ण

	अगर (cfg->direction == MOST_CH_TX) अणु
		playback_count = 1;
		direction = SNDRV_PCM_STREAM_PLAYBACK;
	पूर्ण अन्यथा अणु
		capture_count = 1;
		direction = SNDRV_PCM_STREAM_CAPTURE;
	पूर्ण
	channel = kzalloc(माप(*channel), GFP_KERNEL);
	अगर (!channel) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_adpt;
	पूर्ण
	channel->card = adpt->card;
	channel->cfg = cfg;
	channel->अगरace = अगरace;
	channel->id = channel_id;
	init_रुकोqueue_head(&channel->playback_रुकोq);
	list_add_tail(&channel->list, &adpt->dev_list);

	ret = audio_set_hw_params(&channel->pcm_hardware, ch_num, sample_res,
				  cfg);
	अगर (ret)
		जाओ err_मुक्त_adpt;

	ret = snd_pcm_new(adpt->card, device_name, adpt->pcm_dev_idx,
			  playback_count, capture_count, &pcm);

	अगर (ret < 0)
		जाओ err_मुक्त_adpt;

	pcm->निजी_data = channel;
	strscpy(pcm->name, device_name, माप(pcm->name));
	snd_pcm_set_ops(pcm, direction, &pcm_ops);
	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_VMALLOC, शून्य, 0, 0);
	वापस 0;

err_मुक्त_adpt:
	release_adapter(adpt);
	वापस ret;
पूर्ण

अटल पूर्णांक audio_create_sound_card(व्योम)
अणु
	पूर्णांक ret;
	काष्ठा sound_adapter *adpt;

	list_क्रम_each_entry(adpt, &adpt_list, list) अणु
		अगर (!adpt->रेजिस्टरed)
			जाओ adpt_alloc;
	पूर्ण
	वापस -ENODEV;
adpt_alloc:
	ret = snd_card_रेजिस्टर(adpt->card);
	अगर (ret < 0) अणु
		release_adapter(adpt);
		वापस ret;
	पूर्ण
	adpt->रेजिस्टरed = true;
	वापस 0;
पूर्ण

/**
 * audio_disconnect_channel - function to disconnect a channel
 * @अगरace: poपूर्णांकer to पूर्णांकerface instance
 * @channel_id: channel index
 *
 * This मुक्तs allocated memory and हटाओs the sound card from ALSA
 *
 * Returns 0 on success or error code otherwise.
 */
अटल पूर्णांक audio_disconnect_channel(काष्ठा most_पूर्णांकerface *अगरace,
				    पूर्णांक channel_id)
अणु
	काष्ठा channel *channel;
	काष्ठा sound_adapter *adpt = अगरace->priv;

	channel = get_channel(अगरace, channel_id);
	अगर (!channel)
		वापस -EINVAL;

	list_del(&channel->list);

	kमुक्त(channel);
	अगर (list_empty(&adpt->dev_list))
		release_adapter(adpt);
	वापस 0;
पूर्ण

/**
 * audio_rx_completion - completion handler क्रम rx channels
 * @mbo: poपूर्णांकer to buffer object that has completed
 *
 * This searches क्रम the channel this MBO beदीर्घs to and copy the data from MBO
 * to ring buffer
 *
 * Returns 0 on success or error code otherwise.
 */
अटल पूर्णांक audio_rx_completion(काष्ठा mbo *mbo)
अणु
	काष्ठा channel *channel = get_channel(mbo->अगरp, mbo->hdm_channel_id);
	bool period_elapsed = false;

	अगर (!channel)
		वापस -EINVAL;
	अगर (channel->is_stream_running)
		period_elapsed = copy_data(channel, mbo);
	most_put_mbo(mbo);
	अगर (period_elapsed)
		snd_pcm_period_elapsed(channel->substream);
	वापस 0;
पूर्ण

/**
 * audio_tx_completion - completion handler क्रम tx channels
 * @अगरace: poपूर्णांकer to पूर्णांकerface instance
 * @channel_id: channel index/ID
 *
 * This searches the channel that beदीर्घs to this combination of पूर्णांकerface
 * poपूर्णांकer and channel ID and wakes a process sitting in the रुको queue of
 * this channel.
 *
 * Returns 0 on success or error code otherwise.
 */
अटल पूर्णांक audio_tx_completion(काष्ठा most_पूर्णांकerface *अगरace, पूर्णांक channel_id)
अणु
	काष्ठा channel *channel = get_channel(अगरace, channel_id);

	अगर (!channel)
		वापस -EINVAL;

	wake_up_पूर्णांकerruptible(&channel->playback_रुकोq);
	वापस 0;
पूर्ण

/**
 * Initialization of the काष्ठा most_component
 */
अटल काष्ठा most_component comp = अणु
	.mod = THIS_MODULE,
	.name = DRIVER_NAME,
	.probe_channel = audio_probe_channel,
	.disconnect_channel = audio_disconnect_channel,
	.rx_completion = audio_rx_completion,
	.tx_completion = audio_tx_completion,
	.cfg_complete = audio_create_sound_card,
पूर्ण;

अटल पूर्णांक __init audio_init(व्योम)
अणु
	पूर्णांक ret;

	INIT_LIST_HEAD(&adpt_list);

	ret = most_रेजिस्टर_component(&comp);
	अगर (ret) अणु
		pr_err("Failed to register %s\n", comp.name);
		वापस ret;
	पूर्ण
	ret = most_रेजिस्टर_configfs_subsys(&comp);
	अगर (ret) अणु
		pr_err("Failed to register %s configfs subsys\n", comp.name);
		most_deरेजिस्टर_component(&comp);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम __निकास audio_निकास(व्योम)
अणु
	most_deरेजिस्टर_configfs_subsys(&comp);
	most_deरेजिस्टर_component(&comp);
पूर्ण

module_init(audio_init);
module_निकास(audio_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Christian Gromm <christian.gromm@microchip.com>");
MODULE_DESCRIPTION("Sound Component Module for Mostcore");
