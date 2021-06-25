<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  sst_mfld_platक्रमm.c - Intel MID Platक्रमm driver
 *
 *  Copyright (C) 2010-2014 Intel Corp
 *  Author: Vinod Koul <vinod.koul@पूर्णांकel.com>
 *  Author: Harsha Priya <priya.harsha@पूर्णांकel.com>
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/compress_driver.h>
#समावेश <यंत्र/platक्रमm_sst_audपन.स>
#समावेश "sst-mfld-platform.h"
#समावेश "sst-atom-controls.h"

काष्ठा sst_device *sst;
अटल DEFINE_MUTEX(sst_lock);

पूर्णांक sst_रेजिस्टर_dsp(काष्ठा sst_device *dev)
अणु
	अगर (WARN_ON(!dev))
		वापस -EINVAL;
	अगर (!try_module_get(dev->dev->driver->owner))
		वापस -ENODEV;
	mutex_lock(&sst_lock);
	अगर (sst) अणु
		dev_err(dev->dev, "we already have a device %s\n", sst->name);
		module_put(dev->dev->driver->owner);
		mutex_unlock(&sst_lock);
		वापस -EEXIST;
	पूर्ण
	dev_dbg(dev->dev, "registering device %s\n", dev->name);
	sst = dev;
	mutex_unlock(&sst_lock);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(sst_रेजिस्टर_dsp);

पूर्णांक sst_unरेजिस्टर_dsp(काष्ठा sst_device *dev)
अणु
	अगर (WARN_ON(!dev))
		वापस -EINVAL;
	अगर (dev != sst)
		वापस -EINVAL;

	mutex_lock(&sst_lock);

	अगर (!sst) अणु
		mutex_unlock(&sst_lock);
		वापस -EIO;
	पूर्ण

	module_put(sst->dev->driver->owner);
	dev_dbg(dev->dev, "unreg %s\n", sst->name);
	sst = शून्य;
	mutex_unlock(&sst_lock);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(sst_unरेजिस्टर_dsp);

अटल स्थिर काष्ठा snd_pcm_hardware sst_platक्रमm_pcm_hw = अणु
	.info =	(SNDRV_PCM_INFO_INTERLEAVED |
			SNDRV_PCM_INFO_DOUBLE |
			SNDRV_PCM_INFO_PAUSE |
			SNDRV_PCM_INFO_RESUME |
			SNDRV_PCM_INFO_MMAP|
			SNDRV_PCM_INFO_MMAP_VALID |
			SNDRV_PCM_INFO_BLOCK_TRANSFER |
			SNDRV_PCM_INFO_SYNC_START),
	.buffer_bytes_max = SST_MAX_BUFFER,
	.period_bytes_min = SST_MIN_PERIOD_BYTES,
	.period_bytes_max = SST_MAX_PERIOD_BYTES,
	.periods_min = SST_MIN_PERIODS,
	.periods_max = SST_MAX_PERIODS,
	.fअगरo_size = SST_FIFO_SIZE,
पूर्ण;

अटल काष्ठा sst_dev_stream_map dpcm_strm_map[] = अणु
	अणु0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFFपूर्ण, /* Reserved, not in use */
	अणुMERR_DPCM_AUDIO, 0, SNDRV_PCM_STREAM_PLAYBACK, PIPE_MEDIA1_IN, SST_TASK_ID_MEDIA, 0पूर्ण,
	अणुMERR_DPCM_COMPR, 0, SNDRV_PCM_STREAM_PLAYBACK, PIPE_MEDIA0_IN, SST_TASK_ID_MEDIA, 0पूर्ण,
	अणुMERR_DPCM_AUDIO, 0, SNDRV_PCM_STREAM_CAPTURE, PIPE_PCM1_OUT, SST_TASK_ID_MEDIA, 0पूर्ण,
	अणुMERR_DPCM_DEEP_BUFFER, 0, SNDRV_PCM_STREAM_PLAYBACK, PIPE_MEDIA3_IN, SST_TASK_ID_MEDIA, 0पूर्ण,
पूर्ण;

अटल पूर्णांक sst_media_digital_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक stream)
अणु

	वापस sst_send_pipe_gains(dai, stream, mute);
पूर्ण

/* helper functions */
व्योम sst_set_stream_status(काष्ठा sst_runसमय_stream *stream,
					पूर्णांक state)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&stream->status_lock, flags);
	stream->stream_status = state;
	spin_unlock_irqrestore(&stream->status_lock, flags);
पूर्ण

अटल अंतरभूत पूर्णांक sst_get_stream_status(काष्ठा sst_runसमय_stream *stream)
अणु
	पूर्णांक state;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&stream->status_lock, flags);
	state = stream->stream_status;
	spin_unlock_irqrestore(&stream->status_lock, flags);
	वापस state;
पूर्ण

अटल व्योम sst_fill_alloc_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_sst_alloc_params_ext *alloc_param)
अणु
	अचिन्हित पूर्णांक channels;
	snd_pcm_uframes_t period_size;
	sमाप_प्रकार periodbytes;
	sमाप_प्रकार buffer_bytes = snd_pcm_lib_buffer_bytes(substream);
	u32 buffer_addr = virt_to_phys(substream->dma_buffer.area);

	channels = substream->runसमय->channels;
	period_size = substream->runसमय->period_size;
	periodbytes = samples_to_bytes(substream->runसमय, period_size);
	alloc_param->ring_buf_info[0].addr = buffer_addr;
	alloc_param->ring_buf_info[0].size = buffer_bytes;
	alloc_param->sg_count = 1;
	alloc_param->reserved = 0;
	alloc_param->frag_size = periodbytes * channels;

पूर्ण
अटल व्योम sst_fill_pcm_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_sst_stream_params *param)
अणु
	param->uc.pcm_params.num_chan = (u8) substream->runसमय->channels;
	param->uc.pcm_params.pcm_wd_sz = substream->runसमय->sample_bits;
	param->uc.pcm_params.sfreq = substream->runसमय->rate;

	/* PCM stream via ALSA पूर्णांकerface */
	param->uc.pcm_params.use_offload_path = 0;
	param->uc.pcm_params.reserved2 = 0;
	स_रखो(param->uc.pcm_params.channel_map, 0, माप(u8));

पूर्ण

अटल पूर्णांक sst_get_stream_mapping(पूर्णांक dev, पूर्णांक sdev, पूर्णांक dir,
	काष्ठा sst_dev_stream_map *map, पूर्णांक size)
अणु
	पूर्णांक i;

	अगर (map == शून्य)
		वापस -EINVAL;


	/* index 0 is not used in stream map */
	क्रम (i = 1; i < size; i++) अणु
		अगर ((map[i].dev_num == dev) && (map[i].direction == dir))
			वापस i;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक sst_fill_stream_params(व्योम *substream,
	स्थिर काष्ठा sst_data *ctx, काष्ठा snd_sst_params *str_params, bool is_compress)
अणु
	पूर्णांक map_size;
	पूर्णांक index;
	काष्ठा sst_dev_stream_map *map;
	काष्ठा snd_pcm_substream *pstream = शून्य;
	काष्ठा snd_compr_stream *cstream = शून्य;

	map = ctx->pdata->pdev_strm_map;
	map_size = ctx->pdata->strm_map_size;

	अगर (is_compress)
		cstream = (काष्ठा snd_compr_stream *)substream;
	अन्यथा
		pstream = (काष्ठा snd_pcm_substream *)substream;

	str_params->stream_type = SST_STREAM_TYPE_MUSIC;

	/* For pcm streams */
	अगर (pstream) अणु
		index = sst_get_stream_mapping(pstream->pcm->device,
					  pstream->number, pstream->stream,
					  map, map_size);
		अगर (index <= 0)
			वापस -EINVAL;

		str_params->stream_id = index;
		str_params->device_type = map[index].device_id;
		str_params->task = map[index].task_id;

		str_params->ops = (u8)pstream->stream;
	पूर्ण

	अगर (cstream) अणु
		index = sst_get_stream_mapping(cstream->device->device,
					       0, cstream->direction,
					       map, map_size);
		अगर (index <= 0)
			वापस -EINVAL;
		str_params->stream_id = index;
		str_params->device_type = map[index].device_id;
		str_params->task = map[index].task_id;

		str_params->ops = (u8)cstream->direction;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक sst_platक्रमm_alloc_stream(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा sst_runसमय_stream *stream =
			substream->runसमय->निजी_data;
	काष्ठा snd_sst_stream_params param = अणुअणुअणु0,पूर्ण,पूर्ण,पूर्ण;
	काष्ठा snd_sst_params str_params = अणु0पूर्ण;
	काष्ठा snd_sst_alloc_params_ext alloc_params = अणु0पूर्ण;
	पूर्णांक ret_val = 0;
	काष्ठा sst_data *ctx = snd_soc_dai_get_drvdata(dai);

	/* set codec params and inक्रमm SST driver the same */
	sst_fill_pcm_params(substream, &param);
	sst_fill_alloc_params(substream, &alloc_params);
	substream->runसमय->dma_area = substream->dma_buffer.area;
	str_params.sparams = param;
	str_params.aparams = alloc_params;
	str_params.codec = SST_CODEC_TYPE_PCM;

	/* fill the device type and stream id to pass to SST driver */
	ret_val = sst_fill_stream_params(substream, ctx, &str_params, false);
	अगर (ret_val < 0)
		वापस ret_val;

	stream->stream_info.str_id = str_params.stream_id;

	ret_val = stream->ops->खोलो(sst->dev, &str_params);
	अगर (ret_val <= 0)
		वापस ret_val;


	वापस ret_val;
पूर्ण

अटल व्योम sst_period_elapsed(व्योम *arg)
अणु
	काष्ठा snd_pcm_substream *substream = arg;
	काष्ठा sst_runसमय_stream *stream;
	पूर्णांक status;

	अगर (!substream || !substream->runसमय)
		वापस;
	stream = substream->runसमय->निजी_data;
	अगर (!stream)
		वापस;
	status = sst_get_stream_status(stream);
	अगर (status != SST_PLATFORM_RUNNING)
		वापस;
	snd_pcm_period_elapsed(substream);
पूर्ण

अटल पूर्णांक sst_platक्रमm_init_stream(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा sst_runसमय_stream *stream =
			substream->runसमय->निजी_data;
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	पूर्णांक ret_val;

	dev_dbg(rtd->dev, "setting buffer ptr param\n");
	sst_set_stream_status(stream, SST_PLATFORM_INIT);
	stream->stream_info.period_elapsed = sst_period_elapsed;
	stream->stream_info.arg = substream;
	stream->stream_info.buffer_ptr = 0;
	stream->stream_info.sfreq = substream->runसमय->rate;
	ret_val = stream->ops->stream_init(sst->dev, &stream->stream_info);
	अगर (ret_val)
		dev_err(rtd->dev, "control_set ret error %d\n", ret_val);
	वापस ret_val;

पूर्ण

अटल पूर्णांक घातer_up_sst(काष्ठा sst_runसमय_stream *stream)
अणु
	वापस stream->ops->घातer(sst->dev, true);
पूर्ण

अटल व्योम घातer_करोwn_sst(काष्ठा sst_runसमय_stream *stream)
अणु
	stream->ops->घातer(sst->dev, false);
पूर्ण

अटल पूर्णांक sst_media_खोलो(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_soc_dai *dai)
अणु
	पूर्णांक ret_val = 0;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा sst_runसमय_stream *stream;

	stream = kzalloc(माप(*stream), GFP_KERNEL);
	अगर (!stream)
		वापस -ENOMEM;
	spin_lock_init(&stream->status_lock);

	/* get the sst ops */
	mutex_lock(&sst_lock);
	अगर (!sst ||
	    !try_module_get(sst->dev->driver->owner)) अणु
		dev_err(dai->dev, "no device available to run\n");
		ret_val = -ENODEV;
		जाओ out_ops;
	पूर्ण
	stream->ops = sst->ops;
	mutex_unlock(&sst_lock);

	stream->stream_info.str_id = 0;

	stream->stream_info.arg = substream;
	/* allocate memory क्रम SST API set */
	runसमय->निजी_data = stream;

	ret_val = घातer_up_sst(stream);
	अगर (ret_val < 0)
		जाओ out_घातer_up;

	/*
	 * Make sure the period to be multiple of 1ms to align the
	 * design of firmware. Apply same rule to buffer size to make
	 * sure alsa could always find a value क्रम period size
	 * regardless the buffer size given by user space.
	 */
	snd_pcm_hw_स्थिरraपूर्णांक_step(substream->runसमय, 0,
			   SNDRV_PCM_HW_PARAM_PERIOD_SIZE, 48);
	snd_pcm_hw_स्थिरraपूर्णांक_step(substream->runसमय, 0,
			   SNDRV_PCM_HW_PARAM_BUFFER_SIZE, 48);

	/* Make sure, that the period size is always even */
	snd_pcm_hw_स्थिरraपूर्णांक_step(substream->runसमय, 0,
			   SNDRV_PCM_HW_PARAM_PERIODS, 2);

	वापस snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय,
			 SNDRV_PCM_HW_PARAM_PERIODS);
out_ops:
	mutex_unlock(&sst_lock);
out_घातer_up:
	kमुक्त(stream);
	वापस ret_val;
पूर्ण

अटल व्योम sst_media_बंद(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा sst_runसमय_stream *stream;
	पूर्णांक str_id;

	stream = substream->runसमय->निजी_data;
	घातer_करोwn_sst(stream);

	str_id = stream->stream_info.str_id;
	अगर (str_id)
		stream->ops->बंद(sst->dev, str_id);
	module_put(sst->dev->driver->owner);
	kमुक्त(stream);
पूर्ण

अटल पूर्णांक sst_media_prepare(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा sst_runसमय_stream *stream;
	पूर्णांक ret_val, str_id;

	stream = substream->runसमय->निजी_data;
	str_id = stream->stream_info.str_id;
	अगर (stream->stream_info.str_id) अणु
		ret_val = stream->ops->stream_drop(sst->dev, str_id);
		वापस ret_val;
	पूर्ण

	ret_val = sst_platक्रमm_alloc_stream(substream, dai);
	अगर (ret_val <= 0)
		वापस ret_val;
	snम_लिखो(substream->pcm->id, माप(substream->pcm->id),
			"%d", stream->stream_info.str_id);

	ret_val = sst_platक्रमm_init_stream(substream);
	अगर (ret_val)
		वापस ret_val;
	substream->runसमय->hw.info = SNDRV_PCM_INFO_BLOCK_TRANSFER;
	वापस 0;
पूर्ण

अटल पूर्णांक sst_enable_ssp(काष्ठा snd_pcm_substream *substream,
			काष्ठा snd_soc_dai *dai)
अणु
	पूर्णांक ret = 0;

	अगर (!snd_soc_dai_active(dai)) अणु
		ret = sst_handle_vb_समयr(dai, true);
		sst_fill_ssp_शेषs(dai);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक sst_be_hw_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params,
				काष्ठा snd_soc_dai *dai)
अणु
	पूर्णांक ret = 0;

	अगर (snd_soc_dai_active(dai) == 1)
		ret = send_ssp_cmd(dai, dai->name, 1);
	वापस ret;
पूर्ण

अटल पूर्णांक sst_set_क्रमmat(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	पूर्णांक ret = 0;

	अगर (!snd_soc_dai_active(dai))
		वापस 0;

	ret = sst_fill_ssp_config(dai, fmt);
	अगर (ret < 0)
		dev_err(dai->dev, "sst_set_format failed..\n");

	वापस ret;
पूर्ण

अटल पूर्णांक sst_platक्रमm_set_ssp_slot(काष्ठा snd_soc_dai *dai,
			अचिन्हित पूर्णांक tx_mask, अचिन्हित पूर्णांक rx_mask,
			पूर्णांक slots, पूर्णांक slot_width) अणु
	पूर्णांक ret = 0;

	अगर (!snd_soc_dai_active(dai))
		वापस ret;

	ret = sst_fill_ssp_slot(dai, tx_mask, rx_mask, slots, slot_width);
	अगर (ret < 0)
		dev_err(dai->dev, "sst_fill_ssp_slot failed..%d\n", ret);

	वापस ret;
पूर्ण

अटल व्योम sst_disable_ssp(काष्ठा snd_pcm_substream *substream,
			काष्ठा snd_soc_dai *dai)
अणु
	अगर (!snd_soc_dai_active(dai)) अणु
		send_ssp_cmd(dai, dai->name, 0);
		sst_handle_vb_समयr(dai, false);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops sst_media_dai_ops = अणु
	.startup = sst_media_खोलो,
	.shutकरोwn = sst_media_बंद,
	.prepare = sst_media_prepare,
	.mute_stream = sst_media_digital_mute,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops sst_compr_dai_ops = अणु
	.mute_stream = sst_media_digital_mute,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops sst_be_dai_ops = अणु
	.startup = sst_enable_ssp,
	.hw_params = sst_be_hw_params,
	.set_fmt = sst_set_क्रमmat,
	.set_tdm_slot = sst_platक्रमm_set_ssp_slot,
	.shutकरोwn = sst_disable_ssp,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver sst_platक्रमm_dai[] = अणु
अणु
	.name = "media-cpu-dai",
	.ops = &sst_media_dai_ops,
	.playback = अणु
		.stream_name = "Headset Playback",
		.channels_min = SST_STEREO,
		.channels_max = SST_STEREO,
		.rates = SNDRV_PCM_RATE_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
	.capture = अणु
		.stream_name = "Headset Capture",
		.channels_min = 1,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
पूर्ण,
अणु
	.name = "deepbuffer-cpu-dai",
	.ops = &sst_media_dai_ops,
	.playback = अणु
		.stream_name = "Deepbuffer Playback",
		.channels_min = SST_STEREO,
		.channels_max = SST_STEREO,
		.rates = SNDRV_PCM_RATE_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
पूर्ण,
अणु
	.name = "compress-cpu-dai",
	.compress_new = snd_soc_new_compress,
	.ops = &sst_compr_dai_ops,
	.playback = अणु
		.stream_name = "Compress Playback",
		.channels_min = 1,
	पूर्ण,
पूर्ण,
/* BE CPU  Dais */
अणु
	.name = "ssp0-port",
	.ops = &sst_be_dai_ops,
	.playback = अणु
		.stream_name = "ssp0 Tx",
		.channels_min = SST_STEREO,
		.channels_max = SST_STEREO,
		.rates = SNDRV_PCM_RATE_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
	.capture = अणु
		.stream_name = "ssp0 Rx",
		.channels_min = SST_STEREO,
		.channels_max = SST_STEREO,
		.rates = SNDRV_PCM_RATE_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
पूर्ण,
अणु
	.name = "ssp1-port",
	.ops = &sst_be_dai_ops,
	.playback = अणु
		.stream_name = "ssp1 Tx",
		.channels_min = SST_STEREO,
		.channels_max = SST_STEREO,
		.rates = SNDRV_PCM_RATE_8000|SNDRV_PCM_RATE_16000|SNDRV_PCM_RATE_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
	.capture = अणु
		.stream_name = "ssp1 Rx",
		.channels_min = SST_STEREO,
		.channels_max = SST_STEREO,
		.rates = SNDRV_PCM_RATE_8000|SNDRV_PCM_RATE_16000|SNDRV_PCM_RATE_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
पूर्ण,
अणु
	.name = "ssp2-port",
	.ops = &sst_be_dai_ops,
	.playback = अणु
		.stream_name = "ssp2 Tx",
		.channels_min = SST_STEREO,
		.channels_max = SST_STEREO,
		.rates = SNDRV_PCM_RATE_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
	.capture = अणु
		.stream_name = "ssp2 Rx",
		.channels_min = SST_STEREO,
		.channels_max = SST_STEREO,
		.rates = SNDRV_PCM_RATE_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
पूर्ण,
पूर्ण;

अटल पूर्णांक sst_soc_खोलो(काष्ठा snd_soc_component *component,
			काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय;

	अगर (substream->pcm->पूर्णांकernal)
		वापस 0;

	runसमय = substream->runसमय;
	runसमय->hw = sst_platक्रमm_pcm_hw;
	वापस 0;
पूर्ण

अटल पूर्णांक sst_soc_trigger(काष्ठा snd_soc_component *component,
			   काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	पूर्णांक ret_val = 0, str_id;
	काष्ठा sst_runसमय_stream *stream;
	पूर्णांक status;
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);

	dev_dbg(rtd->dev, "%s called\n", __func__);
	अगर (substream->pcm->पूर्णांकernal)
		वापस 0;
	stream = substream->runसमय->निजी_data;
	str_id = stream->stream_info.str_id;
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		dev_dbg(rtd->dev, "sst: Trigger Start\n");
		status = SST_PLATFORM_RUNNING;
		stream->stream_info.arg = substream;
		ret_val = stream->ops->stream_start(sst->dev, str_id);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		dev_dbg(rtd->dev, "sst: in stop\n");
		status = SST_PLATFORM_DROPPED;
		ret_val = stream->ops->stream_drop(sst->dev, str_id);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		dev_dbg(rtd->dev, "sst: in pause\n");
		status = SST_PLATFORM_PAUSED;
		ret_val = stream->ops->stream_छोड़ो(sst->dev, str_id);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		dev_dbg(rtd->dev, "sst: in pause release\n");
		status = SST_PLATFORM_RUNNING;
		ret_val = stream->ops->stream_छोड़ो_release(sst->dev, str_id);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (!ret_val)
		sst_set_stream_status(stream, status);

	वापस ret_val;
पूर्ण


अटल snd_pcm_uframes_t sst_soc_poपूर्णांकer(काष्ठा snd_soc_component *component,
					 काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा sst_runसमय_stream *stream;
	पूर्णांक ret_val, status;
	काष्ठा pcm_stream_info *str_info;
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);

	stream = substream->runसमय->निजी_data;
	status = sst_get_stream_status(stream);
	अगर (status == SST_PLATFORM_INIT)
		वापस 0;
	str_info = &stream->stream_info;
	ret_val = stream->ops->stream_पढ़ो_tstamp(sst->dev, str_info);
	अगर (ret_val) अणु
		dev_err(rtd->dev, "sst: error code = %d\n", ret_val);
		वापस ret_val;
	पूर्ण
	substream->runसमय->delay = str_info->pcm_delay;
	वापस str_info->buffer_ptr;
पूर्ण

अटल पूर्णांक sst_soc_pcm_new(काष्ठा snd_soc_component *component,
			   काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_dai *dai = asoc_rtd_to_cpu(rtd, 0);
	काष्ठा snd_pcm *pcm = rtd->pcm;

	अगर (dai->driver->playback.channels_min ||
			dai->driver->capture.channels_min) अणु
		snd_pcm_set_managed_buffer_all(pcm,
			SNDRV_DMA_TYPE_CONTINUOUS,
			snd_dma_continuous_data(GFP_DMA),
			SST_MIN_BUFFER, SST_MAX_BUFFER);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक sst_soc_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा sst_data *drv = dev_get_drvdata(component->dev);

	drv->soc_card = component->card;
	वापस sst_dsp_init_v2_dpcm(component);
पूर्ण

अटल व्योम sst_soc_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा sst_data *drv = dev_get_drvdata(component->dev);

	drv->soc_card = शून्य;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver sst_soc_platक्रमm_drv  = अणु
	.name		= DRV_NAME,
	.probe		= sst_soc_probe,
	.हटाओ		= sst_soc_हटाओ,
	.खोलो		= sst_soc_खोलो,
	.trigger	= sst_soc_trigger,
	.poपूर्णांकer	= sst_soc_poपूर्णांकer,
	.compress_ops	= &sst_platक्रमm_compress_ops,
	.pcm_स्थिरruct	= sst_soc_pcm_new,
पूर्ण;

अटल पूर्णांक sst_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sst_data *drv;
	पूर्णांक ret;
	काष्ठा sst_platक्रमm_data *pdata;

	drv = devm_kzalloc(&pdev->dev, माप(*drv), GFP_KERNEL);
	अगर (drv == शून्य) अणु
		वापस -ENOMEM;
	पूर्ण

	pdata = devm_kzalloc(&pdev->dev, माप(*pdata), GFP_KERNEL);
	अगर (pdata == शून्य) अणु
		वापस -ENOMEM;
	पूर्ण

	pdata->pdev_strm_map = dpcm_strm_map;
	pdata->strm_map_size = ARRAY_SIZE(dpcm_strm_map);
	drv->pdata = pdata;
	drv->pdev = pdev;
	mutex_init(&drv->lock);
	dev_set_drvdata(&pdev->dev, drv);

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev, &sst_soc_platक्रमm_drv,
				sst_platक्रमm_dai, ARRAY_SIZE(sst_platक्रमm_dai));
	अगर (ret)
		dev_err(&pdev->dev, "registering cpu dais failed\n");

	वापस ret;
पूर्ण

अटल पूर्णांक sst_platक्रमm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	dev_dbg(&pdev->dev, "sst_platform_remove success\n");
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP

अटल पूर्णांक sst_soc_prepare(काष्ठा device *dev)
अणु
	काष्ठा sst_data *drv = dev_get_drvdata(dev);
	काष्ठा snd_soc_pcm_runसमय *rtd;

	अगर (!drv->soc_card)
		वापस 0;

	/* suspend all pcms first */
	snd_soc_suspend(drv->soc_card->dev);
	snd_soc_घातeroff(drv->soc_card->dev);

	/* set the SSPs to idle */
	क्रम_each_card_rtds(drv->soc_card, rtd) अणु
		काष्ठा snd_soc_dai *dai = asoc_rtd_to_cpu(rtd, 0);

		अगर (snd_soc_dai_active(dai)) अणु
			send_ssp_cmd(dai, dai->name, 0);
			sst_handle_vb_समयr(dai, false);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sst_soc_complete(काष्ठा device *dev)
अणु
	काष्ठा sst_data *drv = dev_get_drvdata(dev);
	काष्ठा snd_soc_pcm_runसमय *rtd;

	अगर (!drv->soc_card)
		वापस;

	/* restart SSPs */
	क्रम_each_card_rtds(drv->soc_card, rtd) अणु
		काष्ठा snd_soc_dai *dai = asoc_rtd_to_cpu(rtd, 0);

		अगर (snd_soc_dai_active(dai)) अणु
			sst_handle_vb_समयr(dai, true);
			send_ssp_cmd(dai, dai->name, 1);
		पूर्ण
	पूर्ण
	snd_soc_resume(drv->soc_card->dev);
पूर्ण

#अन्यथा

#घोषणा sst_soc_prepare शून्य
#घोषणा sst_soc_complete शून्य

#पूर्ण_अगर


अटल स्थिर काष्ठा dev_pm_ops sst_platक्रमm_pm = अणु
	.prepare	= sst_soc_prepare,
	.complete	= sst_soc_complete,
पूर्ण;

अटल काष्ठा platक्रमm_driver sst_platक्रमm_driver = अणु
	.driver		= अणु
		.name		= "sst-mfld-platform",
		.pm             = &sst_platक्रमm_pm,
	पूर्ण,
	.probe		= sst_platक्रमm_probe,
	.हटाओ		= sst_platक्रमm_हटाओ,
पूर्ण;

module_platक्रमm_driver(sst_platक्रमm_driver);

MODULE_DESCRIPTION("ASoC Intel(R) MID Platform driver");
MODULE_AUTHOR("Vinod Koul <vinod.koul@intel.com>");
MODULE_AUTHOR("Harsha Priya <priya.harsha@intel.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:sst-atom-hifi2-platform");
MODULE_ALIAS("platform:sst-mfld-platform");
