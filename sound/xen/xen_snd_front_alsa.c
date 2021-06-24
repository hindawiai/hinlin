<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT

/*
 * Xen para-भव sound device
 *
 * Copyright (C) 2016-2018 EPAM Systems Inc.
 *
 * Author: Oleksandr Andrushchenko <oleksandr_andrushchenko@epam.com>
 */

#समावेश <linux/platक्रमm_device.h>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>

#समावेश <xen/xenbus.h>
#समावेश <xen/xen-front-pgdir-shbuf.h>

#समावेश "xen_snd_front.h"
#समावेश "xen_snd_front_alsa.h"
#समावेश "xen_snd_front_cfg.h"
#समावेश "xen_snd_front_evtchnl.h"

काष्ठा xen_snd_front_pcm_stream_info अणु
	काष्ठा xen_snd_front_info *front_info;
	काष्ठा xen_snd_front_evtchnl_pair *evt_pair;

	/* This is the shared buffer with its backing storage. */
	काष्ठा xen_front_pgdir_shbuf shbuf;
	u8 *buffer;
	माप_प्रकार buffer_sz;
	पूर्णांक num_pages;
	काष्ठा page **pages;

	पूर्णांक index;

	bool is_खोलो;
	काष्ठा snd_pcm_hardware pcm_hw;

	/* Number of processed frames as reported by the backend. */
	snd_pcm_uframes_t be_cur_frame;
	/* Current HW poपूर्णांकer to be reported via .period callback. */
	atomic_t hw_ptr;
	/* Modulo of the number of processed frames - क्रम period detection. */
	u32 out_frames;
पूर्ण;

काष्ठा xen_snd_front_pcm_instance_info अणु
	काष्ठा xen_snd_front_card_info *card_info;
	काष्ठा snd_pcm *pcm;
	काष्ठा snd_pcm_hardware pcm_hw;
	पूर्णांक num_pcm_streams_pb;
	काष्ठा xen_snd_front_pcm_stream_info *streams_pb;
	पूर्णांक num_pcm_streams_cap;
	काष्ठा xen_snd_front_pcm_stream_info *streams_cap;
पूर्ण;

काष्ठा xen_snd_front_card_info अणु
	काष्ठा xen_snd_front_info *front_info;
	काष्ठा snd_card *card;
	काष्ठा snd_pcm_hardware pcm_hw;
	पूर्णांक num_pcm_instances;
	काष्ठा xen_snd_front_pcm_instance_info *pcm_instances;
पूर्ण;

काष्ठा alsa_sndअगर_sample_क्रमmat अणु
	u8 sndअगर;
	snd_pcm_क्रमmat_t alsa;
पूर्ण;

काष्ठा alsa_sndअगर_hw_param अणु
	u8 sndअगर;
	snd_pcm_hw_param_t alsa;
पूर्ण;

अटल स्थिर काष्ठा alsa_sndअगर_sample_क्रमmat ALSA_SNDIF_FORMATS[] = अणु
	अणु
		.sndअगर = XENSND_PCM_FORMAT_U8,
		.alsa = SNDRV_PCM_FORMAT_U8
	पूर्ण,
	अणु
		.sndअगर = XENSND_PCM_FORMAT_S8,
		.alsa = SNDRV_PCM_FORMAT_S8
	पूर्ण,
	अणु
		.sndअगर = XENSND_PCM_FORMAT_U16_LE,
		.alsa = SNDRV_PCM_FORMAT_U16_LE
	पूर्ण,
	अणु
		.sndअगर = XENSND_PCM_FORMAT_U16_BE,
		.alsa = SNDRV_PCM_FORMAT_U16_BE
	पूर्ण,
	अणु
		.sndअगर = XENSND_PCM_FORMAT_S16_LE,
		.alsa = SNDRV_PCM_FORMAT_S16_LE
	पूर्ण,
	अणु
		.sndअगर = XENSND_PCM_FORMAT_S16_BE,
		.alsa = SNDRV_PCM_FORMAT_S16_BE
	पूर्ण,
	अणु
		.sndअगर = XENSND_PCM_FORMAT_U24_LE,
		.alsa = SNDRV_PCM_FORMAT_U24_LE
	पूर्ण,
	अणु
		.sndअगर = XENSND_PCM_FORMAT_U24_BE,
		.alsa = SNDRV_PCM_FORMAT_U24_BE
	पूर्ण,
	अणु
		.sndअगर = XENSND_PCM_FORMAT_S24_LE,
		.alsa = SNDRV_PCM_FORMAT_S24_LE
	पूर्ण,
	अणु
		.sndअगर = XENSND_PCM_FORMAT_S24_BE,
		.alsa = SNDRV_PCM_FORMAT_S24_BE
	पूर्ण,
	अणु
		.sndअगर = XENSND_PCM_FORMAT_U32_LE,
		.alsa = SNDRV_PCM_FORMAT_U32_LE
	पूर्ण,
	अणु
		.sndअगर = XENSND_PCM_FORMAT_U32_BE,
		.alsa = SNDRV_PCM_FORMAT_U32_BE
	पूर्ण,
	अणु
		.sndअगर = XENSND_PCM_FORMAT_S32_LE,
		.alsa = SNDRV_PCM_FORMAT_S32_LE
	पूर्ण,
	अणु
		.sndअगर = XENSND_PCM_FORMAT_S32_BE,
		.alsa = SNDRV_PCM_FORMAT_S32_BE
	पूर्ण,
	अणु
		.sndअगर = XENSND_PCM_FORMAT_A_LAW,
		.alsa = SNDRV_PCM_FORMAT_A_LAW
	पूर्ण,
	अणु
		.sndअगर = XENSND_PCM_FORMAT_MU_LAW,
		.alsa = SNDRV_PCM_FORMAT_MU_LAW
	पूर्ण,
	अणु
		.sndअगर = XENSND_PCM_FORMAT_F32_LE,
		.alsa = SNDRV_PCM_FORMAT_FLOAT_LE
	पूर्ण,
	अणु
		.sndअगर = XENSND_PCM_FORMAT_F32_BE,
		.alsa = SNDRV_PCM_FORMAT_FLOAT_BE
	पूर्ण,
	अणु
		.sndअगर = XENSND_PCM_FORMAT_F64_LE,
		.alsa = SNDRV_PCM_FORMAT_FLOAT64_LE
	पूर्ण,
	अणु
		.sndअगर = XENSND_PCM_FORMAT_F64_BE,
		.alsa = SNDRV_PCM_FORMAT_FLOAT64_BE
	पूर्ण,
	अणु
		.sndअगर = XENSND_PCM_FORMAT_IEC958_SUBFRAME_LE,
		.alsa = SNDRV_PCM_FORMAT_IEC958_SUBFRAME_LE
	पूर्ण,
	अणु
		.sndअगर = XENSND_PCM_FORMAT_IEC958_SUBFRAME_BE,
		.alsa = SNDRV_PCM_FORMAT_IEC958_SUBFRAME_BE
	पूर्ण,
	अणु
		.sndअगर = XENSND_PCM_FORMAT_IMA_ADPCM,
		.alsa = SNDRV_PCM_FORMAT_IMA_ADPCM
	पूर्ण,
	अणु
		.sndअगर = XENSND_PCM_FORMAT_MPEG,
		.alsa = SNDRV_PCM_FORMAT_MPEG
	पूर्ण,
	अणु
		.sndअगर = XENSND_PCM_FORMAT_GSM,
		.alsa = SNDRV_PCM_FORMAT_GSM
	पूर्ण,
पूर्ण;

अटल पूर्णांक to_sndअगर_क्रमmat(snd_pcm_क्रमmat_t क्रमmat)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ALSA_SNDIF_FORMATS); i++)
		अगर (ALSA_SNDIF_FORMATS[i].alsa == क्रमmat)
			वापस ALSA_SNDIF_FORMATS[i].sndअगर;

	वापस -EINVAL;
पूर्ण

अटल u64 to_sndअगर_क्रमmats_mask(u64 alsa_क्रमmats)
अणु
	u64 mask;
	पूर्णांक i;

	mask = 0;
	क्रम (i = 0; i < ARRAY_SIZE(ALSA_SNDIF_FORMATS); i++)
		अगर (pcm_क्रमmat_to_bits(ALSA_SNDIF_FORMATS[i].alsa) & alsa_क्रमmats)
			mask |= BIT_ULL(ALSA_SNDIF_FORMATS[i].sndअगर);

	वापस mask;
पूर्ण

अटल u64 to_alsa_क्रमmats_mask(u64 sndअगर_क्रमmats)
अणु
	u64 mask;
	पूर्णांक i;

	mask = 0;
	क्रम (i = 0; i < ARRAY_SIZE(ALSA_SNDIF_FORMATS); i++)
		अगर (BIT_ULL(ALSA_SNDIF_FORMATS[i].sndअगर) & sndअगर_क्रमmats)
			mask |= pcm_क्रमmat_to_bits(ALSA_SNDIF_FORMATS[i].alsa);

	वापस mask;
पूर्ण

अटल व्योम stream_clear(काष्ठा xen_snd_front_pcm_stream_info *stream)
अणु
	stream->is_खोलो = false;
	stream->be_cur_frame = 0;
	stream->out_frames = 0;
	atomic_set(&stream->hw_ptr, 0);
	xen_snd_front_evtchnl_pair_clear(stream->evt_pair);
	स_रखो(&stream->shbuf, 0, माप(stream->shbuf));
	stream->buffer = शून्य;
	stream->buffer_sz = 0;
	stream->pages = शून्य;
	stream->num_pages = 0;
पूर्ण

अटल व्योम stream_मुक्त(काष्ठा xen_snd_front_pcm_stream_info *stream)
अणु
	xen_front_pgdir_shbuf_unmap(&stream->shbuf);
	xen_front_pgdir_shbuf_मुक्त(&stream->shbuf);
	अगर (stream->buffer)
		मुक्त_pages_exact(stream->buffer, stream->buffer_sz);
	kमुक्त(stream->pages);
	stream_clear(stream);
पूर्ण

अटल काष्ठा xen_snd_front_pcm_stream_info *
stream_get(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा xen_snd_front_pcm_instance_info *pcm_instance =
			snd_pcm_substream_chip(substream);
	काष्ठा xen_snd_front_pcm_stream_info *stream;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		stream = &pcm_instance->streams_pb[substream->number];
	अन्यथा
		stream = &pcm_instance->streams_cap[substream->number];

	वापस stream;
पूर्ण

अटल पूर्णांक alsa_hw_rule(काष्ठा snd_pcm_hw_params *params,
			काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा xen_snd_front_pcm_stream_info *stream = rule->निजी;
	काष्ठा device *dev = &stream->front_info->xb_dev->dev;
	काष्ठा snd_mask *क्रमmats =
			hw_param_mask(params, SNDRV_PCM_HW_PARAM_FORMAT);
	काष्ठा snd_पूर्णांकerval *rates =
			hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_RATE);
	काष्ठा snd_पूर्णांकerval *channels =
			hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_CHANNELS);
	काष्ठा snd_पूर्णांकerval *period =
			hw_param_पूर्णांकerval(params,
					  SNDRV_PCM_HW_PARAM_PERIOD_SIZE);
	काष्ठा snd_पूर्णांकerval *buffer =
			hw_param_पूर्णांकerval(params,
					  SNDRV_PCM_HW_PARAM_BUFFER_SIZE);
	काष्ठा xensnd_query_hw_param req;
	काष्ठा xensnd_query_hw_param resp;
	काष्ठा snd_पूर्णांकerval पूर्णांकerval;
	काष्ठा snd_mask mask;
	u64 sndअगर_क्रमmats;
	पूर्णांक changed, ret;

	/* Collect all the values we need क्रम the query. */

	req.क्रमmats = to_sndअगर_क्रमmats_mask((u64)क्रमmats->bits[0] |
					    (u64)(क्रमmats->bits[1]) << 32);

	req.rates.min = rates->min;
	req.rates.max = rates->max;

	req.channels.min = channels->min;
	req.channels.max = channels->max;

	req.buffer.min = buffer->min;
	req.buffer.max = buffer->max;

	req.period.min = period->min;
	req.period.max = period->max;

	ret = xen_snd_front_stream_query_hw_param(&stream->evt_pair->req,
						  &req, &resp);
	अगर (ret < 0) अणु
		/* Check अगर this is due to backend communication error. */
		अगर (ret == -EIO || ret == -ETIMEDOUT)
			dev_err(dev, "Failed to query ALSA HW parameters\n");
		वापस ret;
	पूर्ण

	/* Refine HW parameters after the query. */
	changed  = 0;

	sndअगर_क्रमmats = to_alsa_क्रमmats_mask(resp.क्रमmats);
	snd_mask_none(&mask);
	mask.bits[0] = (u32)sndअगर_क्रमmats;
	mask.bits[1] = (u32)(sndअगर_क्रमmats >> 32);
	ret = snd_mask_refine(क्रमmats, &mask);
	अगर (ret < 0)
		वापस ret;
	changed |= ret;

	पूर्णांकerval.खोलोmin = 0;
	पूर्णांकerval.खोलोmax = 0;
	पूर्णांकerval.पूर्णांकeger = 1;

	पूर्णांकerval.min = resp.rates.min;
	पूर्णांकerval.max = resp.rates.max;
	ret = snd_पूर्णांकerval_refine(rates, &पूर्णांकerval);
	अगर (ret < 0)
		वापस ret;
	changed |= ret;

	पूर्णांकerval.min = resp.channels.min;
	पूर्णांकerval.max = resp.channels.max;
	ret = snd_पूर्णांकerval_refine(channels, &पूर्णांकerval);
	अगर (ret < 0)
		वापस ret;
	changed |= ret;

	पूर्णांकerval.min = resp.buffer.min;
	पूर्णांकerval.max = resp.buffer.max;
	ret = snd_पूर्णांकerval_refine(buffer, &पूर्णांकerval);
	अगर (ret < 0)
		वापस ret;
	changed |= ret;

	पूर्णांकerval.min = resp.period.min;
	पूर्णांकerval.max = resp.period.max;
	ret = snd_पूर्णांकerval_refine(period, &पूर्णांकerval);
	अगर (ret < 0)
		वापस ret;
	changed |= ret;

	वापस changed;
पूर्ण

अटल पूर्णांक alsa_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा xen_snd_front_pcm_instance_info *pcm_instance =
			snd_pcm_substream_chip(substream);
	काष्ठा xen_snd_front_pcm_stream_info *stream = stream_get(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा xen_snd_front_info *front_info =
			pcm_instance->card_info->front_info;
	काष्ठा device *dev = &front_info->xb_dev->dev;
	पूर्णांक ret;

	/*
	 * Return our HW properties: override शेषs with those configured
	 * via XenStore.
	 */
	runसमय->hw = stream->pcm_hw;
	runसमय->hw.info &= ~(SNDRV_PCM_INFO_MMAP |
			      SNDRV_PCM_INFO_MMAP_VALID |
			      SNDRV_PCM_INFO_DOUBLE |
			      SNDRV_PCM_INFO_BATCH |
			      SNDRV_PCM_INFO_NONINTERLEAVED |
			      SNDRV_PCM_INFO_RESUME |
			      SNDRV_PCM_INFO_PAUSE);
	runसमय->hw.info |= SNDRV_PCM_INFO_INTERLEAVED;

	stream->evt_pair = &front_info->evt_pairs[stream->index];

	stream->front_info = front_info;

	stream->evt_pair->evt.u.evt.substream = substream;

	stream_clear(stream);

	xen_snd_front_evtchnl_pair_set_connected(stream->evt_pair, true);

	ret = snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_FORMAT,
				  alsa_hw_rule, stream,
				  SNDRV_PCM_HW_PARAM_FORMAT, -1);
	अगर (ret) अणु
		dev_err(dev, "Failed to add HW rule for SNDRV_PCM_HW_PARAM_FORMAT\n");
		वापस ret;
	पूर्ण

	ret = snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
				  alsa_hw_rule, stream,
				  SNDRV_PCM_HW_PARAM_RATE, -1);
	अगर (ret) अणु
		dev_err(dev, "Failed to add HW rule for SNDRV_PCM_HW_PARAM_RATE\n");
		वापस ret;
	पूर्ण

	ret = snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
				  alsa_hw_rule, stream,
				  SNDRV_PCM_HW_PARAM_CHANNELS, -1);
	अगर (ret) अणु
		dev_err(dev, "Failed to add HW rule for SNDRV_PCM_HW_PARAM_CHANNELS\n");
		वापस ret;
	पूर्ण

	ret = snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_PERIOD_SIZE,
				  alsa_hw_rule, stream,
				  SNDRV_PCM_HW_PARAM_PERIOD_SIZE, -1);
	अगर (ret) अणु
		dev_err(dev, "Failed to add HW rule for SNDRV_PCM_HW_PARAM_PERIOD_SIZE\n");
		वापस ret;
	पूर्ण

	ret = snd_pcm_hw_rule_add(runसमय, 0, SNDRV_PCM_HW_PARAM_BUFFER_SIZE,
				  alsa_hw_rule, stream,
				  SNDRV_PCM_HW_PARAM_BUFFER_SIZE, -1);
	अगर (ret) अणु
		dev_err(dev, "Failed to add HW rule for SNDRV_PCM_HW_PARAM_BUFFER_SIZE\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक alsa_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा xen_snd_front_pcm_stream_info *stream = stream_get(substream);

	xen_snd_front_evtchnl_pair_set_connected(stream->evt_pair, false);
	वापस 0;
पूर्ण

अटल पूर्णांक shbuf_setup_backstore(काष्ठा xen_snd_front_pcm_stream_info *stream,
				 माप_प्रकार buffer_sz)
अणु
	पूर्णांक i;

	stream->buffer = alloc_pages_exact(buffer_sz, GFP_KERNEL);
	अगर (!stream->buffer)
		वापस -ENOMEM;

	stream->buffer_sz = buffer_sz;
	stream->num_pages = DIV_ROUND_UP(stream->buffer_sz, PAGE_SIZE);
	stream->pages = kसुस्मृति(stream->num_pages, माप(काष्ठा page *),
				GFP_KERNEL);
	अगर (!stream->pages)
		वापस -ENOMEM;

	क्रम (i = 0; i < stream->num_pages; i++)
		stream->pages[i] = virt_to_page(stream->buffer + i * PAGE_SIZE);

	वापस 0;
पूर्ण

अटल पूर्णांक alsa_hw_params(काष्ठा snd_pcm_substream *substream,
			  काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा xen_snd_front_pcm_stream_info *stream = stream_get(substream);
	काष्ठा xen_snd_front_info *front_info = stream->front_info;
	काष्ठा xen_front_pgdir_shbuf_cfg buf_cfg;
	पूर्णांक ret;

	/*
	 * This callback may be called multiple बार,
	 * so मुक्त the previously allocated shared buffer अगर any.
	 */
	stream_मुक्त(stream);
	ret = shbuf_setup_backstore(stream, params_buffer_bytes(params));
	अगर (ret < 0)
		जाओ fail;

	स_रखो(&buf_cfg, 0, माप(buf_cfg));
	buf_cfg.xb_dev = front_info->xb_dev;
	buf_cfg.pgdir = &stream->shbuf;
	buf_cfg.num_pages = stream->num_pages;
	buf_cfg.pages = stream->pages;

	ret = xen_front_pgdir_shbuf_alloc(&buf_cfg);
	अगर (ret < 0)
		जाओ fail;

	ret = xen_front_pgdir_shbuf_map(&stream->shbuf);
	अगर (ret < 0)
		जाओ fail;

	वापस 0;

fail:
	stream_मुक्त(stream);
	dev_err(&front_info->xb_dev->dev,
		"Failed to allocate buffers for stream with index %d\n",
		stream->index);
	वापस ret;
पूर्ण

अटल पूर्णांक alsa_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा xen_snd_front_pcm_stream_info *stream = stream_get(substream);
	पूर्णांक ret;

	ret = xen_snd_front_stream_बंद(&stream->evt_pair->req);
	stream_मुक्त(stream);
	वापस ret;
पूर्ण

अटल पूर्णांक alsa_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा xen_snd_front_pcm_stream_info *stream = stream_get(substream);

	अगर (!stream->is_खोलो) अणु
		काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
		u8 sndअगर_क्रमmat;
		पूर्णांक ret;

		ret = to_sndअगर_क्रमmat(runसमय->क्रमmat);
		अगर (ret < 0) अणु
			dev_err(&stream->front_info->xb_dev->dev,
				"Unsupported sample format: %d\n",
				runसमय->क्रमmat);
			वापस ret;
		पूर्ण
		sndअगर_क्रमmat = ret;

		ret = xen_snd_front_stream_prepare(&stream->evt_pair->req,
						   &stream->shbuf,
						   sndअगर_क्रमmat,
						   runसमय->channels,
						   runसमय->rate,
						   snd_pcm_lib_buffer_bytes(substream),
						   snd_pcm_lib_period_bytes(substream));
		अगर (ret < 0)
			वापस ret;

		stream->is_खोलो = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक alsa_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा xen_snd_front_pcm_stream_info *stream = stream_get(substream);
	पूर्णांक type;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		type = XENSND_OP_TRIGGER_START;
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_RESUME:
		type = XENSND_OP_TRIGGER_RESUME;
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_STOP:
		type = XENSND_OP_TRIGGER_STOP;
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		type = XENSND_OP_TRIGGER_PAUSE;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस xen_snd_front_stream_trigger(&stream->evt_pair->req, type);
पूर्ण

व्योम xen_snd_front_alsa_handle_cur_pos(काष्ठा xen_snd_front_evtchnl *evtchnl,
				       u64 pos_bytes)
अणु
	काष्ठा snd_pcm_substream *substream = evtchnl->u.evt.substream;
	काष्ठा xen_snd_front_pcm_stream_info *stream = stream_get(substream);
	snd_pcm_uframes_t delta, new_hw_ptr, cur_frame;

	cur_frame = bytes_to_frames(substream->runसमय, pos_bytes);

	delta = cur_frame - stream->be_cur_frame;
	stream->be_cur_frame = cur_frame;

	new_hw_ptr = (snd_pcm_uframes_t)atomic_पढ़ो(&stream->hw_ptr);
	new_hw_ptr = (new_hw_ptr + delta) % substream->runसमय->buffer_size;
	atomic_set(&stream->hw_ptr, (पूर्णांक)new_hw_ptr);

	stream->out_frames += delta;
	अगर (stream->out_frames > substream->runसमय->period_size) अणु
		stream->out_frames %= substream->runसमय->period_size;
		snd_pcm_period_elapsed(substream);
	पूर्ण
पूर्ण

अटल snd_pcm_uframes_t alsa_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा xen_snd_front_pcm_stream_info *stream = stream_get(substream);

	वापस (snd_pcm_uframes_t)atomic_पढ़ो(&stream->hw_ptr);
पूर्ण

अटल पूर्णांक alsa_pb_copy_user(काष्ठा snd_pcm_substream *substream,
			     पूर्णांक channel, अचिन्हित दीर्घ pos, व्योम __user *src,
			     अचिन्हित दीर्घ count)
अणु
	काष्ठा xen_snd_front_pcm_stream_info *stream = stream_get(substream);

	अगर (unlikely(pos + count > stream->buffer_sz))
		वापस -EINVAL;

	अगर (copy_from_user(stream->buffer + pos, src, count))
		वापस -EFAULT;

	वापस xen_snd_front_stream_ग_लिखो(&stream->evt_pair->req, pos, count);
पूर्ण

अटल पूर्णांक alsa_pb_copy_kernel(काष्ठा snd_pcm_substream *substream,
			       पूर्णांक channel, अचिन्हित दीर्घ pos, व्योम *src,
			       अचिन्हित दीर्घ count)
अणु
	काष्ठा xen_snd_front_pcm_stream_info *stream = stream_get(substream);

	अगर (unlikely(pos + count > stream->buffer_sz))
		वापस -EINVAL;

	स_नकल(stream->buffer + pos, src, count);

	वापस xen_snd_front_stream_ग_लिखो(&stream->evt_pair->req, pos, count);
पूर्ण

अटल पूर्णांक alsa_cap_copy_user(काष्ठा snd_pcm_substream *substream,
			      पूर्णांक channel, अचिन्हित दीर्घ pos, व्योम __user *dst,
			      अचिन्हित दीर्घ count)
अणु
	काष्ठा xen_snd_front_pcm_stream_info *stream = stream_get(substream);
	पूर्णांक ret;

	अगर (unlikely(pos + count > stream->buffer_sz))
		वापस -EINVAL;

	ret = xen_snd_front_stream_पढ़ो(&stream->evt_pair->req, pos, count);
	अगर (ret < 0)
		वापस ret;

	वापस copy_to_user(dst, stream->buffer + pos, count) ?
		-EFAULT : 0;
पूर्ण

अटल पूर्णांक alsa_cap_copy_kernel(काष्ठा snd_pcm_substream *substream,
				पूर्णांक channel, अचिन्हित दीर्घ pos, व्योम *dst,
				अचिन्हित दीर्घ count)
अणु
	काष्ठा xen_snd_front_pcm_stream_info *stream = stream_get(substream);
	पूर्णांक ret;

	अगर (unlikely(pos + count > stream->buffer_sz))
		वापस -EINVAL;

	ret = xen_snd_front_stream_पढ़ो(&stream->evt_pair->req, pos, count);
	अगर (ret < 0)
		वापस ret;

	स_नकल(dst, stream->buffer + pos, count);

	वापस 0;
पूर्ण

अटल पूर्णांक alsa_pb_fill_silence(काष्ठा snd_pcm_substream *substream,
				पूर्णांक channel, अचिन्हित दीर्घ pos,
				अचिन्हित दीर्घ count)
अणु
	काष्ठा xen_snd_front_pcm_stream_info *stream = stream_get(substream);

	अगर (unlikely(pos + count > stream->buffer_sz))
		वापस -EINVAL;

	स_रखो(stream->buffer + pos, 0, count);

	वापस xen_snd_front_stream_ग_लिखो(&stream->evt_pair->req, pos, count);
पूर्ण

/*
 * FIXME: The mmaped data transfer is asynchronous and there is no
 * ack संकेत from user-space when it is करोne. This is the
 * reason it is not implemented in the PV driver as we करो need
 * to know when the buffer can be transferred to the backend.
 */

अटल स्थिर काष्ठा snd_pcm_ops snd_drv_alsa_playback_ops = अणु
	.खोलो		= alsa_खोलो,
	.बंद		= alsa_बंद,
	.hw_params	= alsa_hw_params,
	.hw_मुक्त	= alsa_hw_मुक्त,
	.prepare	= alsa_prepare,
	.trigger	= alsa_trigger,
	.poपूर्णांकer	= alsa_poपूर्णांकer,
	.copy_user	= alsa_pb_copy_user,
	.copy_kernel	= alsa_pb_copy_kernel,
	.fill_silence	= alsa_pb_fill_silence,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_drv_alsa_capture_ops = अणु
	.खोलो		= alsa_खोलो,
	.बंद		= alsa_बंद,
	.hw_params	= alsa_hw_params,
	.hw_मुक्त	= alsa_hw_मुक्त,
	.prepare	= alsa_prepare,
	.trigger	= alsa_trigger,
	.poपूर्णांकer	= alsa_poपूर्णांकer,
	.copy_user	= alsa_cap_copy_user,
	.copy_kernel	= alsa_cap_copy_kernel,
पूर्ण;

अटल पूर्णांक new_pcm_instance(काष्ठा xen_snd_front_card_info *card_info,
			    काष्ठा xen_front_cfg_pcm_instance *instance_cfg,
			    काष्ठा xen_snd_front_pcm_instance_info *pcm_instance_info)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक ret, i;

	dev_dbg(&card_info->front_info->xb_dev->dev,
		"New PCM device \"%s\" with id %d playback %d capture %d",
		instance_cfg->name,
		instance_cfg->device_id,
		instance_cfg->num_streams_pb,
		instance_cfg->num_streams_cap);

	pcm_instance_info->card_info = card_info;

	pcm_instance_info->pcm_hw = instance_cfg->pcm_hw;

	अगर (instance_cfg->num_streams_pb) अणु
		pcm_instance_info->streams_pb =
				devm_kसुस्मृति(&card_info->card->card_dev,
					     instance_cfg->num_streams_pb,
					     माप(काष्ठा xen_snd_front_pcm_stream_info),
					     GFP_KERNEL);
		अगर (!pcm_instance_info->streams_pb)
			वापस -ENOMEM;
	पूर्ण

	अगर (instance_cfg->num_streams_cap) अणु
		pcm_instance_info->streams_cap =
				devm_kसुस्मृति(&card_info->card->card_dev,
					     instance_cfg->num_streams_cap,
					     माप(काष्ठा xen_snd_front_pcm_stream_info),
					     GFP_KERNEL);
		अगर (!pcm_instance_info->streams_cap)
			वापस -ENOMEM;
	पूर्ण

	pcm_instance_info->num_pcm_streams_pb =
			instance_cfg->num_streams_pb;
	pcm_instance_info->num_pcm_streams_cap =
			instance_cfg->num_streams_cap;

	क्रम (i = 0; i < pcm_instance_info->num_pcm_streams_pb; i++) अणु
		pcm_instance_info->streams_pb[i].pcm_hw =
			instance_cfg->streams_pb[i].pcm_hw;
		pcm_instance_info->streams_pb[i].index =
			instance_cfg->streams_pb[i].index;
	पूर्ण

	क्रम (i = 0; i < pcm_instance_info->num_pcm_streams_cap; i++) अणु
		pcm_instance_info->streams_cap[i].pcm_hw =
			instance_cfg->streams_cap[i].pcm_hw;
		pcm_instance_info->streams_cap[i].index =
			instance_cfg->streams_cap[i].index;
	पूर्ण

	ret = snd_pcm_new(card_info->card, instance_cfg->name,
			  instance_cfg->device_id,
			  instance_cfg->num_streams_pb,
			  instance_cfg->num_streams_cap,
			  &pcm);
	अगर (ret < 0)
		वापस ret;

	pcm->निजी_data = pcm_instance_info;
	pcm->info_flags = 0;
	/* we want to handle all PCM operations in non-atomic context */
	pcm->nonatomic = true;
	म_नकलन(pcm->name, "Virtual card PCM", माप(pcm->name));

	अगर (instance_cfg->num_streams_pb)
		snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK,
				&snd_drv_alsa_playback_ops);

	अगर (instance_cfg->num_streams_cap)
		snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE,
				&snd_drv_alsa_capture_ops);

	pcm_instance_info->pcm = pcm;
	वापस 0;
पूर्ण

पूर्णांक xen_snd_front_alsa_init(काष्ठा xen_snd_front_info *front_info)
अणु
	काष्ठा device *dev = &front_info->xb_dev->dev;
	काष्ठा xen_front_cfg_card *cfg = &front_info->cfg;
	काष्ठा xen_snd_front_card_info *card_info;
	काष्ठा snd_card *card;
	पूर्णांक ret, i;

	dev_dbg(dev, "Creating virtual sound card\n");

	ret = snd_card_new(dev, 0, XENSND_DRIVER_NAME, THIS_MODULE,
			   माप(काष्ठा xen_snd_front_card_info), &card);
	अगर (ret < 0)
		वापस ret;

	card_info = card->निजी_data;
	card_info->front_info = front_info;
	front_info->card_info = card_info;
	card_info->card = card;
	card_info->pcm_instances =
			devm_kसुस्मृति(dev, cfg->num_pcm_instances,
				     माप(काष्ठा xen_snd_front_pcm_instance_info),
				     GFP_KERNEL);
	अगर (!card_info->pcm_instances) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	card_info->num_pcm_instances = cfg->num_pcm_instances;
	card_info->pcm_hw = cfg->pcm_hw;

	क्रम (i = 0; i < cfg->num_pcm_instances; i++) अणु
		ret = new_pcm_instance(card_info, &cfg->pcm_instances[i],
				       &card_info->pcm_instances[i]);
		अगर (ret < 0)
			जाओ fail;
	पूर्ण

	म_नकलन(card->driver, XENSND_DRIVER_NAME, माप(card->driver));
	म_नकलन(card->लघुname, cfg->name_लघु, माप(card->लघुname));
	म_नकलन(card->दीर्घname, cfg->name_दीर्घ, माप(card->दीर्घname));

	ret = snd_card_रेजिस्टर(card);
	अगर (ret < 0)
		जाओ fail;

	वापस 0;

fail:
	snd_card_मुक्त(card);
	वापस ret;
पूर्ण

व्योम xen_snd_front_alsa_fini(काष्ठा xen_snd_front_info *front_info)
अणु
	काष्ठा xen_snd_front_card_info *card_info;
	काष्ठा snd_card *card;

	card_info = front_info->card_info;
	अगर (!card_info)
		वापस;

	card = card_info->card;
	अगर (!card)
		वापस;

	dev_dbg(&front_info->xb_dev->dev, "Removing virtual sound card %d\n",
		card->number);
	snd_card_मुक्त(card);

	/* Card_info will be मुक्तd when destroying front_info->xb_dev->dev. */
	card_info->card = शून्य;
पूर्ण
