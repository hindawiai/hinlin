<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  sst_drv_पूर्णांकerface.c - Intel SST Driver क्रम audio engine
 *
 *  Copyright (C) 2008-14 Intel Corp
 *  Authors:	Vinod Koul <vinod.koul@पूर्णांकel.com>
 *		Harsha Priya <priya.harsha@पूर्णांकel.com>
 *		Dharageswari R <dharageswari.r@पूर्णांकel.com)
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <linux/fs.h>
#समावेश <linux/firmware.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pm_qos.h>
#समावेश <linux/math64.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>
#समावेश <sound/compress_driver.h>
#समावेश <यंत्र/platक्रमm_sst_audपन.स>
#समावेश "../sst-mfld-platform.h"
#समावेश "sst.h"

#घोषणा NUM_CODEC 2
#घोषणा MIN_FRAGMENT 2
#घोषणा MAX_FRAGMENT 4
#घोषणा MIN_FRAGMENT_SIZE (50 * 1024)
#घोषणा MAX_FRAGMENT_SIZE (1024 * 1024)
#घोषणा SST_GET_BYTES_PER_SAMPLE(pcm_wd_sz)  (((pcm_wd_sz + 15) >> 4) << 1)
#अगर_घोषित CONFIG_PM
#घोषणा GET_USAGE_COUNT(dev) (atomic_पढ़ो(&dev->घातer.usage_count))
#अन्यथा
#घोषणा GET_USAGE_COUNT(dev) 1
#पूर्ण_अगर

पूर्णांक मुक्त_stream_context(काष्ठा पूर्णांकel_sst_drv *ctx, अचिन्हित पूर्णांक str_id)
अणु
	काष्ठा stream_info *stream;
	पूर्णांक ret = 0;

	stream = get_stream_info(ctx, str_id);
	अगर (stream) अणु
		/* str_id is valid, so stream is alloacted */
		ret = sst_मुक्त_stream(ctx, str_id);
		अगर (ret)
			sst_clean_stream(&ctx->streams[str_id]);
		वापस ret;
	पूर्ण अन्यथा अणु
		dev_err(ctx->dev, "we tried to free stream context %d which was freed!!!\n", str_id);
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक sst_get_stream_allocated(काष्ठा पूर्णांकel_sst_drv *ctx,
	काष्ठा snd_sst_params *str_param,
	काष्ठा snd_sst_lib_करोwnload **lib_dnld)
अणु
	पूर्णांक retval;

	retval = ctx->ops->alloc_stream(ctx, str_param);
	अगर (retval > 0)
		dev_dbg(ctx->dev, "Stream allocated %d\n", retval);
	वापस retval;

पूर्ण

/*
 * sst_get_sfreq - this function वापसs the frequency of the stream
 *
 * @str_param : stream params
 */
पूर्णांक sst_get_sfreq(काष्ठा snd_sst_params *str_param)
अणु
	चयन (str_param->codec) अणु
	हाल SST_CODEC_TYPE_PCM:
		वापस str_param->sparams.uc.pcm_params.sfreq;
	हाल SST_CODEC_TYPE_AAC:
		वापस str_param->sparams.uc.aac_params.बाह्यalsr;
	हाल SST_CODEC_TYPE_MP3:
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/*
 * sst_get_num_channel - get number of channels क्रम the stream
 *
 * @str_param : stream params
 */
पूर्णांक sst_get_num_channel(काष्ठा snd_sst_params *str_param)
अणु
	चयन (str_param->codec) अणु
	हाल SST_CODEC_TYPE_PCM:
		वापस str_param->sparams.uc.pcm_params.num_chan;
	हाल SST_CODEC_TYPE_MP3:
		वापस str_param->sparams.uc.mp3_params.num_chan;
	हाल SST_CODEC_TYPE_AAC:
		वापस str_param->sparams.uc.aac_params.num_chan;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/*
 * sst_get_stream - this function prepares क्रम stream allocation
 *
 * @str_param : stream param
 */
पूर्णांक sst_get_stream(काष्ठा पूर्णांकel_sst_drv *ctx,
			काष्ठा snd_sst_params *str_param)
अणु
	पूर्णांक retval;
	काष्ठा stream_info *str_info;

	/* stream is not allocated, we are allocating */
	retval = ctx->ops->alloc_stream(ctx, str_param);
	अगर (retval <= 0) अणु
		वापस -EIO;
	पूर्ण
	/* store sampling freq */
	str_info = &ctx->streams[retval];
	str_info->sfreq = sst_get_sfreq(str_param);

	वापस retval;
पूर्ण

अटल पूर्णांक sst_घातer_control(काष्ठा device *dev, bool state)
अणु
	काष्ठा पूर्णांकel_sst_drv *ctx = dev_get_drvdata(dev);
	पूर्णांक ret = 0;
	पूर्णांक usage_count = 0;

	अगर (state) अणु
		ret = pm_runसमय_get_sync(dev);
		usage_count = GET_USAGE_COUNT(dev);
		dev_dbg(ctx->dev, "Enable: pm usage count: %d\n", usage_count);
		अगर (ret < 0) अणु
			pm_runसमय_put_sync(dev);
			dev_err(ctx->dev, "Runtime get failed with err: %d\n", ret);
			वापस ret;
		पूर्ण
		अगर ((ctx->sst_state == SST_RESET) && (usage_count == 1)) अणु
			ret = sst_load_fw(ctx);
			अगर (ret) अणु
				dev_err(dev, "FW download fail %d\n", ret);
				sst_set_fw_state_locked(ctx, SST_RESET);
				ret = sst_pm_runसमय_put(ctx);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		usage_count = GET_USAGE_COUNT(dev);
		dev_dbg(ctx->dev, "Disable: pm usage count: %d\n", usage_count);
		वापस sst_pm_runसमय_put(ctx);
	पूर्ण
	वापस ret;
पूर्ण

/*
 * sst_खोलो_pcm_stream - Open PCM पूर्णांकerface
 *
 * @str_param: parameters of pcm stream
 *
 * This function is called by MID sound card driver to खोलो
 * a new pcm पूर्णांकerface
 */
अटल पूर्णांक sst_खोलो_pcm_stream(काष्ठा device *dev,
		काष्ठा snd_sst_params *str_param)
अणु
	पूर्णांक retval;
	काष्ठा पूर्णांकel_sst_drv *ctx = dev_get_drvdata(dev);

	अगर (!str_param)
		वापस -EINVAL;

	retval = sst_get_stream(ctx, str_param);
	अगर (retval > 0)
		ctx->stream_cnt++;
	अन्यथा
		dev_err(ctx->dev, "sst_get_stream returned err %d\n", retval);

	वापस retval;
पूर्ण

अटल पूर्णांक sst_cdev_खोलो(काष्ठा device *dev,
		काष्ठा snd_sst_params *str_params, काष्ठा sst_compress_cb *cb)
अणु
	पूर्णांक str_id, retval;
	काष्ठा stream_info *stream;
	काष्ठा पूर्णांकel_sst_drv *ctx = dev_get_drvdata(dev);

	retval = pm_runसमय_get_sync(ctx->dev);
	अगर (retval < 0) अणु
		pm_runसमय_put_sync(ctx->dev);
		वापस retval;
	पूर्ण

	str_id = sst_get_stream(ctx, str_params);
	अगर (str_id > 0) अणु
		dev_dbg(dev, "stream allocated in sst_cdev_open %d\n", str_id);
		stream = &ctx->streams[str_id];
		stream->compr_cb = cb->compr_cb;
		stream->compr_cb_param = cb->param;
		stream->drain_notअगरy = cb->drain_notअगरy;
		stream->drain_cb_param = cb->drain_cb_param;
	पूर्ण अन्यथा अणु
		dev_err(dev, "stream encountered error during alloc %d\n", str_id);
		str_id = -EINVAL;
		sst_pm_runसमय_put(ctx);
	पूर्ण
	वापस str_id;
पूर्ण

अटल पूर्णांक sst_cdev_बंद(काष्ठा device *dev, अचिन्हित पूर्णांक str_id)
अणु
	पूर्णांक retval;
	काष्ठा stream_info *stream;
	काष्ठा पूर्णांकel_sst_drv *ctx = dev_get_drvdata(dev);

	stream = get_stream_info(ctx, str_id);
	अगर (!stream) अणु
		dev_err(dev, "stream info is NULL for str %d!!!\n", str_id);
		वापस -EINVAL;
	पूर्ण

	retval = sst_मुक्त_stream(ctx, str_id);
	stream->compr_cb_param = शून्य;
	stream->compr_cb = शून्य;

	अगर (retval)
		dev_err(dev, "free stream returned err %d\n", retval);

	dev_dbg(dev, "End\n");
	वापस retval;
पूर्ण

अटल पूर्णांक sst_cdev_ack(काष्ठा device *dev, अचिन्हित पूर्णांक str_id,
		अचिन्हित दीर्घ bytes)
अणु
	काष्ठा stream_info *stream;
	काष्ठा snd_sst_tstamp fw_tstamp = अणु0,पूर्ण;
	पूर्णांक offset;
	व्योम __iomem *addr;
	काष्ठा पूर्णांकel_sst_drv *ctx = dev_get_drvdata(dev);

	stream = get_stream_info(ctx, str_id);
	अगर (!stream)
		वापस -EINVAL;

	/* update bytes sent */
	stream->cumm_bytes += bytes;
	dev_dbg(dev, "bytes copied %d inc by %ld\n", stream->cumm_bytes, bytes);

	addr =  ((व्योम __iomem *)(ctx->mailbox + ctx->tstamp)) +
		(str_id * माप(fw_tstamp));

	स_नकल_fromio(&fw_tstamp, addr, माप(fw_tstamp));

	fw_tstamp.bytes_copied = stream->cumm_bytes;
	dev_dbg(dev, "bytes sent to fw %llu inc by %ld\n",
			fw_tstamp.bytes_copied, bytes);

	offset =  दुरत्व(काष्ठा snd_sst_tstamp, bytes_copied);
	sst_shim_ग_लिखो(addr, offset, fw_tstamp.bytes_copied);
	वापस 0;
पूर्ण

अटल पूर्णांक sst_cdev_set_metadata(काष्ठा device *dev,
		अचिन्हित पूर्णांक str_id, काष्ठा snd_compr_metadata *metadata)
अणु
	पूर्णांक retval = 0;
	काष्ठा stream_info *str_info;
	काष्ठा पूर्णांकel_sst_drv *ctx = dev_get_drvdata(dev);

	dev_dbg(dev, "set metadata for stream %d\n", str_id);

	str_info = get_stream_info(ctx, str_id);
	अगर (!str_info)
		वापस -EINVAL;

	dev_dbg(dev, "pipe id = %d\n", str_info->pipe_id);
	retval = sst_prepare_and_post_msg(ctx, str_info->task_id, IPC_CMD,
			IPC_IA_SET_STREAM_PARAMS_MRFLD, str_info->pipe_id,
			माप(*metadata), metadata, शून्य,
			true, true, true, false);

	वापस retval;
पूर्ण

अटल पूर्णांक sst_cdev_stream_छोड़ो(काष्ठा device *dev, अचिन्हित पूर्णांक str_id)
अणु
	काष्ठा पूर्णांकel_sst_drv *ctx = dev_get_drvdata(dev);

	वापस sst_छोड़ो_stream(ctx, str_id);
पूर्ण

अटल पूर्णांक sst_cdev_stream_छोड़ो_release(काष्ठा device *dev,
		अचिन्हित पूर्णांक str_id)
अणु
	काष्ठा पूर्णांकel_sst_drv *ctx = dev_get_drvdata(dev);

	वापस sst_resume_stream(ctx, str_id);
पूर्ण

अटल पूर्णांक sst_cdev_stream_start(काष्ठा device *dev, अचिन्हित पूर्णांक str_id)
अणु
	काष्ठा stream_info *str_info;
	काष्ठा पूर्णांकel_sst_drv *ctx = dev_get_drvdata(dev);

	str_info = get_stream_info(ctx, str_id);
	अगर (!str_info)
		वापस -EINVAL;
	str_info->prev = str_info->status;
	str_info->status = STREAM_RUNNING;
	वापस sst_start_stream(ctx, str_id);
पूर्ण

अटल पूर्णांक sst_cdev_stream_drop(काष्ठा device *dev, अचिन्हित पूर्णांक str_id)
अणु
	काष्ठा पूर्णांकel_sst_drv *ctx = dev_get_drvdata(dev);

	वापस sst_drop_stream(ctx, str_id);
पूर्ण

अटल पूर्णांक sst_cdev_stream_drain(काष्ठा device *dev, अचिन्हित पूर्णांक str_id)
अणु
	काष्ठा पूर्णांकel_sst_drv *ctx = dev_get_drvdata(dev);

	वापस sst_drain_stream(ctx, str_id, false);
पूर्ण

अटल पूर्णांक sst_cdev_stream_partial_drain(काष्ठा device *dev,
		अचिन्हित पूर्णांक str_id)
अणु
	काष्ठा पूर्णांकel_sst_drv *ctx = dev_get_drvdata(dev);

	वापस sst_drain_stream(ctx, str_id, true);
पूर्ण

अटल पूर्णांक sst_cdev_tstamp(काष्ठा device *dev, अचिन्हित पूर्णांक str_id,
		काष्ठा snd_compr_tstamp *tstamp)
अणु
	काष्ठा snd_sst_tstamp fw_tstamp = अणु0,पूर्ण;
	काष्ठा stream_info *stream;
	काष्ठा पूर्णांकel_sst_drv *ctx = dev_get_drvdata(dev);
	व्योम __iomem *addr;

	addr = (व्योम __iomem *)(ctx->mailbox + ctx->tstamp) +
		(str_id * माप(fw_tstamp));

	स_नकल_fromio(&fw_tstamp, addr, माप(fw_tstamp));

	stream = get_stream_info(ctx, str_id);
	अगर (!stream)
		वापस -EINVAL;
	dev_dbg(dev, "rb_counter %llu in bytes\n", fw_tstamp.ring_buffer_counter);

	tstamp->copied_total = fw_tstamp.ring_buffer_counter;
	tstamp->pcm_frames = fw_tstamp.frames_decoded;
	tstamp->pcm_io_frames = भाग_u64(fw_tstamp.hardware_counter,
			(u64)stream->num_ch * SST_GET_BYTES_PER_SAMPLE(24));
	tstamp->sampling_rate = fw_tstamp.sampling_frequency;

	dev_dbg(dev, "PCM  = %u\n", tstamp->pcm_io_frames);
	dev_dbg(dev, "Ptr Query on strid = %d  copied_total %d, decodec %d\n",
		str_id, tstamp->copied_total, tstamp->pcm_frames);
	dev_dbg(dev, "rendered %d\n", tstamp->pcm_io_frames);

	वापस 0;
पूर्ण

अटल पूर्णांक sst_cdev_caps(काष्ठा snd_compr_caps *caps)
अणु
	caps->num_codecs = NUM_CODEC;
	caps->min_fragment_size = MIN_FRAGMENT_SIZE;  /* 50KB */
	caps->max_fragment_size = MAX_FRAGMENT_SIZE;  /* 1024KB */
	caps->min_fragments = MIN_FRAGMENT;
	caps->max_fragments = MAX_FRAGMENT;
	caps->codecs[0] = SND_AUDIOCODEC_MP3;
	caps->codecs[1] = SND_AUDIOCODEC_AAC;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_compr_codec_caps caps_mp3 = अणु
	.num_descriptors = 1,
	.descriptor[0].max_ch = 2,
	.descriptor[0].sample_rates[0] = 48000,
	.descriptor[0].sample_rates[1] = 44100,
	.descriptor[0].sample_rates[2] = 32000,
	.descriptor[0].sample_rates[3] = 16000,
	.descriptor[0].sample_rates[4] = 8000,
	.descriptor[0].num_sample_rates = 5,
	.descriptor[0].bit_rate[0] = 320,
	.descriptor[0].bit_rate[1] = 192,
	.descriptor[0].num_bitrates = 2,
	.descriptor[0].profiles = 0,
	.descriptor[0].modes = SND_AUDIOCHANMODE_MP3_STEREO,
	.descriptor[0].क्रमmats = 0,
पूर्ण;

अटल स्थिर काष्ठा snd_compr_codec_caps caps_aac = अणु
	.num_descriptors = 2,
	.descriptor[1].max_ch = 2,
	.descriptor[0].sample_rates[0] = 48000,
	.descriptor[0].sample_rates[1] = 44100,
	.descriptor[0].sample_rates[2] = 32000,
	.descriptor[0].sample_rates[3] = 16000,
	.descriptor[0].sample_rates[4] = 8000,
	.descriptor[0].num_sample_rates = 5,
	.descriptor[1].bit_rate[0] = 320,
	.descriptor[1].bit_rate[1] = 192,
	.descriptor[1].num_bitrates = 2,
	.descriptor[1].profiles = 0,
	.descriptor[1].modes = 0,
	.descriptor[1].क्रमmats =
			(SND_AUDIOSTREAMFORMAT_MP4ADTS |
				SND_AUDIOSTREAMFORMAT_RAW),
पूर्ण;

अटल पूर्णांक sst_cdev_codec_caps(काष्ठा snd_compr_codec_caps *codec)
अणु
	अगर (codec->codec == SND_AUDIOCODEC_MP3)
		*codec = caps_mp3;
	अन्यथा अगर (codec->codec == SND_AUDIOCODEC_AAC)
		*codec = caps_aac;
	अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण

व्योम sst_cdev_fragment_elapsed(काष्ठा पूर्णांकel_sst_drv *ctx, पूर्णांक str_id)
अणु
	काष्ठा stream_info *stream;

	dev_dbg(ctx->dev, "fragment elapsed from firmware for str_id %d\n",
			str_id);
	stream = &ctx->streams[str_id];
	अगर (stream->compr_cb)
		stream->compr_cb(stream->compr_cb_param);
पूर्ण

/*
 * sst_बंद_pcm_stream - Close PCM पूर्णांकerface
 *
 * @str_id: stream id to be बंदd
 *
 * This function is called by MID sound card driver to बंद
 * an existing pcm पूर्णांकerface
 */
अटल पूर्णांक sst_बंद_pcm_stream(काष्ठा device *dev, अचिन्हित पूर्णांक str_id)
अणु
	काष्ठा stream_info *stream;
	पूर्णांक retval = 0;
	काष्ठा पूर्णांकel_sst_drv *ctx = dev_get_drvdata(dev);

	stream = get_stream_info(ctx, str_id);
	अगर (!stream) अणु
		dev_err(ctx->dev, "stream info is NULL for str %d!!!\n", str_id);
		वापस -EINVAL;
	पूर्ण

	retval = मुक्त_stream_context(ctx, str_id);
	stream->pcm_substream = शून्य;
	stream->status = STREAM_UN_INIT;
	stream->period_elapsed = शून्य;
	ctx->stream_cnt--;

	अगर (retval)
		dev_err(ctx->dev, "free stream returned err %d\n", retval);

	dev_dbg(ctx->dev, "Exit\n");
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक sst_calc_tstamp(काष्ठा पूर्णांकel_sst_drv *ctx,
		काष्ठा pcm_stream_info *info,
		काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_sst_tstamp *fw_tstamp)
अणु
	माप_प्रकार delay_bytes, delay_frames;
	माप_प्रकार buffer_sz;
	u32 poपूर्णांकer_bytes, poपूर्णांकer_samples;

	dev_dbg(ctx->dev, "mrfld ring_buffer_counter %llu in bytes\n",
			fw_tstamp->ring_buffer_counter);
	dev_dbg(ctx->dev, "mrfld hardware_counter %llu in bytes\n",
			 fw_tstamp->hardware_counter);
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		delay_bytes = (माप_प्रकार) (fw_tstamp->ring_buffer_counter -
					fw_tstamp->hardware_counter);
	अन्यथा
		delay_bytes = (माप_प्रकार) (fw_tstamp->hardware_counter -
					fw_tstamp->ring_buffer_counter);
	delay_frames = bytes_to_frames(substream->runसमय, delay_bytes);
	buffer_sz = snd_pcm_lib_buffer_bytes(substream);
	भाग_u64_rem(fw_tstamp->ring_buffer_counter, buffer_sz, &poपूर्णांकer_bytes);
	poपूर्णांकer_samples = bytes_to_samples(substream->runसमय, poपूर्णांकer_bytes);

	dev_dbg(ctx->dev, "pcm delay %zu in bytes\n", delay_bytes);

	info->buffer_ptr = poपूर्णांकer_samples / substream->runसमय->channels;

	info->pcm_delay = delay_frames;
	dev_dbg(ctx->dev, "buffer ptr %llu pcm_delay rep: %llu\n",
			info->buffer_ptr, info->pcm_delay);
	वापस 0;
पूर्ण

अटल पूर्णांक sst_पढ़ो_बारtamp(काष्ठा device *dev, काष्ठा pcm_stream_info *info)
अणु
	काष्ठा stream_info *stream;
	काष्ठा snd_pcm_substream *substream;
	काष्ठा snd_sst_tstamp fw_tstamp;
	अचिन्हित पूर्णांक str_id;
	काष्ठा पूर्णांकel_sst_drv *ctx = dev_get_drvdata(dev);
	व्योम __iomem *addr;

	str_id = info->str_id;
	stream = get_stream_info(ctx, str_id);
	अगर (!stream)
		वापस -EINVAL;

	अगर (!stream->pcm_substream)
		वापस -EINVAL;
	substream = stream->pcm_substream;

	addr = (व्योम __iomem *)(ctx->mailbox + ctx->tstamp) +
		(str_id * माप(fw_tstamp));

	स_नकल_fromio(&fw_tstamp, addr, माप(fw_tstamp));

	वापस sst_calc_tstamp(ctx, info, substream, &fw_tstamp);
पूर्ण

अटल पूर्णांक sst_stream_start(काष्ठा device *dev, पूर्णांक str_id)
अणु
	काष्ठा stream_info *str_info;
	काष्ठा पूर्णांकel_sst_drv *ctx = dev_get_drvdata(dev);

	अगर (ctx->sst_state != SST_FW_RUNNING)
		वापस 0;
	str_info = get_stream_info(ctx, str_id);
	अगर (!str_info)
		वापस -EINVAL;
	str_info->prev = str_info->status;
	str_info->status = STREAM_RUNNING;
	sst_start_stream(ctx, str_id);

	वापस 0;
पूर्ण

अटल पूर्णांक sst_stream_drop(काष्ठा device *dev, पूर्णांक str_id)
अणु
	काष्ठा stream_info *str_info;
	काष्ठा पूर्णांकel_sst_drv *ctx = dev_get_drvdata(dev);

	अगर (ctx->sst_state != SST_FW_RUNNING)
		वापस 0;

	str_info = get_stream_info(ctx, str_id);
	अगर (!str_info)
		वापस -EINVAL;
	str_info->prev = STREAM_UN_INIT;
	str_info->status = STREAM_INIT;
	वापस sst_drop_stream(ctx, str_id);
पूर्ण

अटल पूर्णांक sst_stream_छोड़ो(काष्ठा device *dev, पूर्णांक str_id)
अणु
	काष्ठा stream_info *str_info;
	काष्ठा पूर्णांकel_sst_drv *ctx = dev_get_drvdata(dev);

	अगर (ctx->sst_state != SST_FW_RUNNING)
		वापस 0;

	str_info = get_stream_info(ctx, str_id);
	अगर (!str_info)
		वापस -EINVAL;

	वापस sst_छोड़ो_stream(ctx, str_id);
पूर्ण

अटल पूर्णांक sst_stream_resume(काष्ठा device *dev, पूर्णांक str_id)
अणु
	काष्ठा stream_info *str_info;
	काष्ठा पूर्णांकel_sst_drv *ctx = dev_get_drvdata(dev);

	अगर (ctx->sst_state != SST_FW_RUNNING)
		वापस 0;

	str_info = get_stream_info(ctx, str_id);
	अगर (!str_info)
		वापस -EINVAL;
	वापस sst_resume_stream(ctx, str_id);
पूर्ण

अटल पूर्णांक sst_stream_init(काष्ठा device *dev, काष्ठा pcm_stream_info *str_info)
अणु
	पूर्णांक str_id = 0;
	काष्ठा stream_info *stream;
	काष्ठा पूर्णांकel_sst_drv *ctx = dev_get_drvdata(dev);

	str_id = str_info->str_id;

	अगर (ctx->sst_state != SST_FW_RUNNING)
		वापस 0;

	stream = get_stream_info(ctx, str_id);
	अगर (!stream)
		वापस -EINVAL;

	dev_dbg(ctx->dev, "setting the period ptrs\n");
	stream->pcm_substream = str_info->arg;
	stream->period_elapsed = str_info->period_elapsed;
	stream->sfreq = str_info->sfreq;
	stream->prev = stream->status;
	stream->status = STREAM_INIT;
	dev_dbg(ctx->dev,
		"pcm_substream %p, period_elapsed %p, sfreq %d, status %d\n",
		stream->pcm_substream, stream->period_elapsed,
		stream->sfreq, stream->status);

	वापस 0;
पूर्ण

/*
 * sst_set_byte_stream - Set generic params
 *
 * @cmd: control cmd to be set
 * @arg: command argument
 *
 * This function is called by MID sound card driver to configure
 * SST runसमय params.
 */
अटल पूर्णांक sst_send_byte_stream(काष्ठा device *dev,
		काष्ठा snd_sst_bytes_v2 *bytes)
अणु
	पूर्णांक ret_val = 0;
	काष्ठा पूर्णांकel_sst_drv *ctx = dev_get_drvdata(dev);

	अगर (शून्य == bytes)
		वापस -EINVAL;
	ret_val = pm_runसमय_get_sync(ctx->dev);
	अगर (ret_val < 0) अणु
		pm_runसमय_put_sync(ctx->dev);
		वापस ret_val;
	पूर्ण

	ret_val = sst_send_byte_stream_mrfld(ctx, bytes);
	sst_pm_runसमय_put(ctx);

	वापस ret_val;
पूर्ण

अटल काष्ठा sst_ops pcm_ops = अणु
	.खोलो = sst_खोलो_pcm_stream,
	.stream_init = sst_stream_init,
	.stream_start = sst_stream_start,
	.stream_drop = sst_stream_drop,
	.stream_छोड़ो = sst_stream_छोड़ो,
	.stream_छोड़ो_release = sst_stream_resume,
	.stream_पढ़ो_tstamp = sst_पढ़ो_बारtamp,
	.send_byte_stream = sst_send_byte_stream,
	.बंद = sst_बंद_pcm_stream,
	.घातer = sst_घातer_control,
पूर्ण;

अटल काष्ठा compress_sst_ops compr_ops = अणु
	.खोलो = sst_cdev_खोलो,
	.बंद = sst_cdev_बंद,
	.stream_छोड़ो = sst_cdev_stream_छोड़ो,
	.stream_छोड़ो_release = sst_cdev_stream_छोड़ो_release,
	.stream_start = sst_cdev_stream_start,
	.stream_drop = sst_cdev_stream_drop,
	.stream_drain = sst_cdev_stream_drain,
	.stream_partial_drain = sst_cdev_stream_partial_drain,
	.tstamp = sst_cdev_tstamp,
	.ack = sst_cdev_ack,
	.get_caps = sst_cdev_caps,
	.get_codec_caps = sst_cdev_codec_caps,
	.set_metadata = sst_cdev_set_metadata,
	.घातer = sst_घातer_control,
पूर्ण;

अटल काष्ठा sst_device sst_dsp_device = अणु
	.name = "Intel(R) SST LPE",
	.dev = शून्य,
	.ops = &pcm_ops,
	.compr_ops = &compr_ops,
पूर्ण;

/*
 * sst_रेजिस्टर - function to रेजिस्टर DSP
 *
 * This functions रेजिस्टरs DSP with the platक्रमm driver
 */
पूर्णांक sst_रेजिस्टर(काष्ठा device *dev)
अणु
	पूर्णांक ret_val;

	sst_dsp_device.dev = dev;
	ret_val = sst_रेजिस्टर_dsp(&sst_dsp_device);
	अगर (ret_val)
		dev_err(dev, "Unable to register DSP with platform driver\n");

	वापस ret_val;
पूर्ण

पूर्णांक sst_unरेजिस्टर(काष्ठा device *dev)
अणु
	वापस sst_unरेजिस्टर_dsp(&sst_dsp_device);
पूर्ण
