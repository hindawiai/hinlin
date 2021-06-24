<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  sst_mfld_platक्रमm.c - Intel MID Platक्रमm driver
 *
 *  Copyright (C) 2010-2014 Intel Corp
 *  Author: Vinod Koul <vinod.koul@पूर्णांकel.com>
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
#समावेश "sst-mfld-platform.h"

/* compress stream operations */
अटल व्योम sst_compr_fragment_elapsed(व्योम *arg)
अणु
	काष्ठा snd_compr_stream *cstream = (काष्ठा snd_compr_stream *)arg;

	pr_debug("fragment elapsed by driver\n");
	अगर (cstream)
		snd_compr_fragment_elapsed(cstream);
पूर्ण

अटल व्योम sst_drain_notअगरy(व्योम *arg)
अणु
	काष्ठा snd_compr_stream *cstream = (काष्ठा snd_compr_stream *)arg;

	pr_debug("drain notify by driver\n");
	अगर (cstream)
		snd_compr_drain_notअगरy(cstream);
पूर्ण

अटल पूर्णांक sst_platक्रमm_compr_खोलो(काष्ठा snd_soc_component *component,
				   काष्ठा snd_compr_stream *cstream)
अणु
	पूर्णांक ret_val;
	काष्ठा snd_compr_runसमय *runसमय = cstream->runसमय;
	काष्ठा sst_runसमय_stream *stream;

	stream = kzalloc(माप(*stream), GFP_KERNEL);
	अगर (!stream)
		वापस -ENOMEM;

	spin_lock_init(&stream->status_lock);

	/* get the sst ops */
	अगर (!sst || !try_module_get(sst->dev->driver->owner)) अणु
		pr_err("no device available to run\n");
		ret_val = -ENODEV;
		जाओ out_ops;
	पूर्ण
	stream->compr_ops = sst->compr_ops;
	stream->id = 0;

	/* Turn on LPE */
	sst->compr_ops->घातer(sst->dev, true);

	sst_set_stream_status(stream, SST_PLATFORM_INIT);
	runसमय->निजी_data = stream;
	वापस 0;
out_ops:
	kमुक्त(stream);
	वापस ret_val;
पूर्ण

अटल पूर्णांक sst_platक्रमm_compr_मुक्त(काष्ठा snd_soc_component *component,
				   काष्ठा snd_compr_stream *cstream)
अणु
	काष्ठा sst_runसमय_stream *stream;
	पूर्णांक ret_val = 0, str_id;

	stream = cstream->runसमय->निजी_data;
	/* Turn off LPE */
	sst->compr_ops->घातer(sst->dev, false);

	/*need to check*/
	str_id = stream->id;
	अगर (str_id)
		ret_val = stream->compr_ops->बंद(sst->dev, str_id);
	module_put(sst->dev->driver->owner);
	kमुक्त(stream);
	pr_debug("%s: %d\n", __func__, ret_val);
	वापस 0;
पूर्ण

अटल पूर्णांक sst_platक्रमm_compr_set_params(काष्ठा snd_soc_component *component,
					 काष्ठा snd_compr_stream *cstream,
					 काष्ठा snd_compr_params *params)
अणु
	काष्ठा sst_runसमय_stream *stream;
	पूर्णांक retval;
	काष्ठा snd_sst_params str_params;
	काष्ठा sst_compress_cb cb;
	काष्ठा sst_data *ctx = snd_soc_component_get_drvdata(component);

	stream = cstream->runसमय->निजी_data;
	/* स्थिरruct fw काष्ठाure क्रम this*/
	स_रखो(&str_params, 0, माप(str_params));

	/* fill the device type and stream id to pass to SST driver */
	retval = sst_fill_stream_params(cstream, ctx, &str_params, true);
	pr_debug("compr_set_params: fill stream params ret_val = 0x%x\n", retval);
	अगर (retval < 0)
		वापस retval;

	चयन (params->codec.id) अणु
	हाल SND_AUDIOCODEC_MP3: अणु
		str_params.codec = SST_CODEC_TYPE_MP3;
		str_params.sparams.uc.mp3_params.num_chan = params->codec.ch_in;
		str_params.sparams.uc.mp3_params.pcm_wd_sz = 16;
		अवरोध;
	पूर्ण

	हाल SND_AUDIOCODEC_AAC: अणु
		str_params.codec = SST_CODEC_TYPE_AAC;
		str_params.sparams.uc.aac_params.num_chan = params->codec.ch_in;
		str_params.sparams.uc.aac_params.pcm_wd_sz = 16;
		अगर (params->codec.क्रमmat == SND_AUDIOSTREAMFORMAT_MP4ADTS)
			str_params.sparams.uc.aac_params.bs_क्रमmat =
							AAC_BIT_STREAM_ADTS;
		अन्यथा अगर (params->codec.क्रमmat == SND_AUDIOSTREAMFORMAT_RAW)
			str_params.sparams.uc.aac_params.bs_क्रमmat =
							AAC_BIT_STREAM_RAW;
		अन्यथा अणु
			pr_err("Undefined format%d\n", params->codec.क्रमmat);
			वापस -EINVAL;
		पूर्ण
		str_params.sparams.uc.aac_params.बाह्यalsr =
						params->codec.sample_rate;
		अवरोध;
	पूर्ण

	शेष:
		pr_err("codec not supported, id =%d\n", params->codec.id);
		वापस -EINVAL;
	पूर्ण

	str_params.aparams.ring_buf_info[0].addr  =
					virt_to_phys(cstream->runसमय->buffer);
	str_params.aparams.ring_buf_info[0].size =
					cstream->runसमय->buffer_size;
	str_params.aparams.sg_count = 1;
	str_params.aparams.frag_size = cstream->runसमय->fragment_size;

	cb.param = cstream;
	cb.compr_cb = sst_compr_fragment_elapsed;
	cb.drain_cb_param = cstream;
	cb.drain_notअगरy = sst_drain_notअगरy;

	retval = stream->compr_ops->खोलो(sst->dev, &str_params, &cb);
	अगर (retval < 0) अणु
		pr_err("stream allocation failed %d\n", retval);
		वापस retval;
	पूर्ण

	stream->id = retval;
	वापस 0;
पूर्ण

अटल पूर्णांक sst_platक्रमm_compr_trigger(काष्ठा snd_soc_component *component,
				      काष्ठा snd_compr_stream *cstream, पूर्णांक cmd)
अणु
	काष्ठा sst_runसमय_stream *stream = cstream->runसमय->निजी_data;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		अगर (stream->compr_ops->stream_start)
			वापस stream->compr_ops->stream_start(sst->dev, stream->id);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		अगर (stream->compr_ops->stream_drop)
			वापस stream->compr_ops->stream_drop(sst->dev, stream->id);
		अवरोध;
	हाल SND_COMPR_TRIGGER_DRAIN:
		अगर (stream->compr_ops->stream_drain)
			वापस stream->compr_ops->stream_drain(sst->dev, stream->id);
		अवरोध;
	हाल SND_COMPR_TRIGGER_PARTIAL_DRAIN:
		अगर (stream->compr_ops->stream_partial_drain)
			वापस stream->compr_ops->stream_partial_drain(sst->dev, stream->id);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		अगर (stream->compr_ops->stream_छोड़ो)
			वापस stream->compr_ops->stream_छोड़ो(sst->dev, stream->id);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		अगर (stream->compr_ops->stream_छोड़ो_release)
			वापस stream->compr_ops->stream_छोड़ो_release(sst->dev, stream->id);
		अवरोध;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक sst_platक्रमm_compr_poपूर्णांकer(काष्ठा snd_soc_component *component,
				      काष्ठा snd_compr_stream *cstream,
				      काष्ठा snd_compr_tstamp *tstamp)
अणु
	काष्ठा sst_runसमय_stream *stream;

	stream  = cstream->runसमय->निजी_data;
	stream->compr_ops->tstamp(sst->dev, stream->id, tstamp);
	tstamp->byte_offset = tstamp->copied_total %
				 (u32)cstream->runसमय->buffer_size;
	pr_debug("calc bytes offset/copied bytes as %d\n", tstamp->byte_offset);
	वापस 0;
पूर्ण

अटल पूर्णांक sst_platक्रमm_compr_ack(काष्ठा snd_soc_component *component,
				  काष्ठा snd_compr_stream *cstream,
				  माप_प्रकार bytes)
अणु
	काष्ठा sst_runसमय_stream *stream;

	stream  = cstream->runसमय->निजी_data;
	stream->compr_ops->ack(sst->dev, stream->id, (अचिन्हित दीर्घ)bytes);
	stream->bytes_written += bytes;

	वापस 0;
पूर्ण

अटल पूर्णांक sst_platक्रमm_compr_get_caps(काष्ठा snd_soc_component *component,
				       काष्ठा snd_compr_stream *cstream,
				       काष्ठा snd_compr_caps *caps)
अणु
	काष्ठा sst_runसमय_stream *stream =
		cstream->runसमय->निजी_data;

	वापस stream->compr_ops->get_caps(caps);
पूर्ण

अटल पूर्णांक sst_platक्रमm_compr_get_codec_caps(काष्ठा snd_soc_component *component,
					     काष्ठा snd_compr_stream *cstream,
					     काष्ठा snd_compr_codec_caps *codec)
अणु
	काष्ठा sst_runसमय_stream *stream =
		cstream->runसमय->निजी_data;

	वापस stream->compr_ops->get_codec_caps(codec);
पूर्ण

अटल पूर्णांक sst_platक्रमm_compr_set_metadata(काष्ठा snd_soc_component *component,
					   काष्ठा snd_compr_stream *cstream,
					   काष्ठा snd_compr_metadata *metadata)
अणु
	काष्ठा sst_runसमय_stream *stream  =
		 cstream->runसमय->निजी_data;

	वापस stream->compr_ops->set_metadata(sst->dev, stream->id, metadata);
पूर्ण

स्थिर काष्ठा snd_compress_ops sst_platक्रमm_compress_ops = अणु

	.खोलो = sst_platक्रमm_compr_खोलो,
	.मुक्त = sst_platक्रमm_compr_मुक्त,
	.set_params = sst_platक्रमm_compr_set_params,
	.set_metadata = sst_platक्रमm_compr_set_metadata,
	.trigger = sst_platक्रमm_compr_trigger,
	.poपूर्णांकer = sst_platक्रमm_compr_poपूर्णांकer,
	.ack = sst_platक्रमm_compr_ack,
	.get_caps = sst_platक्रमm_compr_get_caps,
	.get_codec_caps = sst_platक्रमm_compr_get_codec_caps,
पूर्ण;
