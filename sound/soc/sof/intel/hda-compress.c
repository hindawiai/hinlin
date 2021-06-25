<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
//
// This file is provided under a dual BSD/GPLv2 license.  When using or
// redistributing this file, you may करो so under either license.
//
// Copyright(c) 2019-2020 Intel Corporation. All rights reserved.
//
// Author: Cezary Rojewski <cezary.rojewski@पूर्णांकel.com>
//

#समावेश <sound/hdaudio_ext.h>
#समावेश <sound/soc.h>
#समावेश "../sof-priv.h"
#समावेश "hda.h"

अटल अंतरभूत काष्ठा hdac_ext_stream *
hda_compr_get_stream(काष्ठा snd_compr_stream *cstream)
अणु
	वापस cstream->runसमय->निजी_data;
पूर्ण

पूर्णांक hda_probe_compr_assign(काष्ठा snd_sof_dev *sdev,
			   काष्ठा snd_compr_stream *cstream,
			   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा hdac_ext_stream *stream;

	stream = hda_dsp_stream_get(sdev, cstream->direction, 0);
	अगर (!stream)
		वापस -EBUSY;

	hdac_stream(stream)->curr_pos = 0;
	hdac_stream(stream)->cstream = cstream;
	cstream->runसमय->निजी_data = stream;

	वापस hdac_stream(stream)->stream_tag;
पूर्ण

पूर्णांक hda_probe_compr_मुक्त(काष्ठा snd_sof_dev *sdev,
			 काष्ठा snd_compr_stream *cstream,
			 काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा hdac_ext_stream *stream = hda_compr_get_stream(cstream);
	पूर्णांक ret;

	ret = hda_dsp_stream_put(sdev, cstream->direction,
				 hdac_stream(stream)->stream_tag);
	अगर (ret < 0) अणु
		dev_dbg(sdev->dev, "stream put failed: %d\n", ret);
		वापस ret;
	पूर्ण

	hdac_stream(stream)->cstream = शून्य;
	cstream->runसमय->निजी_data = शून्य;

	वापस 0;
पूर्ण

पूर्णांक hda_probe_compr_set_params(काष्ठा snd_sof_dev *sdev,
			       काष्ठा snd_compr_stream *cstream,
			       काष्ठा snd_compr_params *params,
			       काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा hdac_ext_stream *stream = hda_compr_get_stream(cstream);
	काष्ठा hdac_stream *hstream = hdac_stream(stream);
	काष्ठा snd_dma_buffer *dmab;
	u32 bits, rate;
	पूर्णांक bps, ret;

	dmab = cstream->runसमय->dma_buffer_p;
	/* compr params करो not store bit depth, शेष to S32_LE */
	bps = snd_pcm_क्रमmat_physical_width(SNDRV_PCM_FORMAT_S32_LE);
	अगर (bps < 0)
		वापस bps;
	bits = hda_dsp_get_bits(sdev, bps);
	rate = hda_dsp_get_mult_भाग(sdev, params->codec.sample_rate);

	hstream->क्रमmat_val = rate | bits | (params->codec.ch_out - 1);
	hstream->bufsize = cstream->runसमय->buffer_size;
	hstream->period_bytes = cstream->runसमय->fragment_size;
	hstream->no_period_wakeup = 0;

	ret = hda_dsp_stream_hw_params(sdev, stream, dmab, शून्य);
	अगर (ret < 0) अणु
		dev_err(sdev->dev, "error: hdac prepare failed: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक hda_probe_compr_trigger(काष्ठा snd_sof_dev *sdev,
			    काष्ठा snd_compr_stream *cstream, पूर्णांक cmd,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा hdac_ext_stream *stream = hda_compr_get_stream(cstream);

	वापस hda_dsp_stream_trigger(sdev, stream, cmd);
पूर्ण

पूर्णांक hda_probe_compr_poपूर्णांकer(काष्ठा snd_sof_dev *sdev,
			    काष्ठा snd_compr_stream *cstream,
			    काष्ठा snd_compr_tstamp *tstamp,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा hdac_ext_stream *stream = hda_compr_get_stream(cstream);
	काष्ठा snd_soc_pcm_stream *pstream;

	pstream = &dai->driver->capture;
	tstamp->copied_total = hdac_stream(stream)->curr_pos;
	tstamp->sampling_rate = snd_pcm_rate_bit_to_rate(pstream->rates);

	वापस 0;
पूर्ण
