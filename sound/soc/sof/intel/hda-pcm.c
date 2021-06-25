<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
//
// This file is provided under a dual BSD/GPLv2 license.  When using or
// redistributing this file, you may करो so under either license.
//
// Copyright(c) 2018 Intel Corporation. All rights reserved.
//
// Authors: Liam Girdwood <liam.r.girdwood@linux.पूर्णांकel.com>
//	    Ranjani Sridharan <ranjani.sridharan@linux.पूर्णांकel.com>
//	    Rander Wang <अक्रमer.wang@पूर्णांकel.com>
//          Keyon Jie <yang.jie@linux.पूर्णांकel.com>
//

/*
 * Hardware पूर्णांकerface क्रम generic Intel audio DSP HDA IP
 */

#समावेश <sound/hda_रेजिस्टर.h>
#समावेश <sound/pcm_params.h>
#समावेश "../sof-audio.h"
#समावेश "../ops.h"
#समावेश "hda.h"

#घोषणा SDnFMT_BASE(x)	((x) << 14)
#घोषणा SDnFMT_MULT(x)	(((x) - 1) << 11)
#घोषणा SDnFMT_DIV(x)	(((x) - 1) << 8)
#घोषणा SDnFMT_BITS(x)	((x) << 4)
#घोषणा SDnFMT_CHAN(x)	((x) << 0)

u32 hda_dsp_get_mult_भाग(काष्ठा snd_sof_dev *sdev, पूर्णांक rate)
अणु
	चयन (rate) अणु
	हाल 8000:
		वापस SDnFMT_DIV(6);
	हाल 9600:
		वापस SDnFMT_DIV(5);
	हाल 11025:
		वापस SDnFMT_BASE(1) | SDnFMT_DIV(4);
	हाल 16000:
		वापस SDnFMT_DIV(3);
	हाल 22050:
		वापस SDnFMT_BASE(1) | SDnFMT_DIV(2);
	हाल 32000:
		वापस SDnFMT_DIV(3) | SDnFMT_MULT(2);
	हाल 44100:
		वापस SDnFMT_BASE(1);
	हाल 48000:
		वापस 0;
	हाल 88200:
		वापस SDnFMT_BASE(1) | SDnFMT_MULT(2);
	हाल 96000:
		वापस SDnFMT_MULT(2);
	हाल 176400:
		वापस SDnFMT_BASE(1) | SDnFMT_MULT(4);
	हाल 192000:
		वापस SDnFMT_MULT(4);
	शेष:
		dev_warn(sdev->dev, "can't find div rate %d using 48kHz\n",
			 rate);
		वापस 0; /* use 48KHz अगर not found */
	पूर्ण
पूर्ण;

u32 hda_dsp_get_bits(काष्ठा snd_sof_dev *sdev, पूर्णांक sample_bits)
अणु
	चयन (sample_bits) अणु
	हाल 8:
		वापस SDnFMT_BITS(0);
	हाल 16:
		वापस SDnFMT_BITS(1);
	हाल 20:
		वापस SDnFMT_BITS(2);
	हाल 24:
		वापस SDnFMT_BITS(3);
	हाल 32:
		वापस SDnFMT_BITS(4);
	शेष:
		dev_warn(sdev->dev, "can't find %d bits using 16bit\n",
			 sample_bits);
		वापस SDnFMT_BITS(1); /* use 16bits क्रमmat अगर not found */
	पूर्ण
पूर्ण;

पूर्णांक hda_dsp_pcm_hw_params(काष्ठा snd_sof_dev *sdev,
			  काष्ठा snd_pcm_substream *substream,
			  काष्ठा snd_pcm_hw_params *params,
			  काष्ठा sof_ipc_stream_params *ipc_params)
अणु
	काष्ठा hdac_stream *hstream = substream->runसमय->निजी_data;
	काष्ठा hdac_ext_stream *stream = stream_to_hdac_ext_stream(hstream);
	काष्ठा sof_पूर्णांकel_hda_dev *hda = sdev->pdata->hw_pdata;
	काष्ठा snd_dma_buffer *dmab;
	काष्ठा sof_ipc_fw_version *v = &sdev->fw_पढ़ोy.version;
	पूर्णांक ret;
	u32 size, rate, bits;

	size = params_buffer_bytes(params);
	rate = hda_dsp_get_mult_भाग(sdev, params_rate(params));
	bits = hda_dsp_get_bits(sdev, params_width(params));

	hstream->substream = substream;

	dmab = substream->runसमय->dma_buffer_p;

	hstream->क्रमmat_val = rate | bits | (params_channels(params) - 1);
	hstream->bufsize = size;
	hstream->period_bytes = params_period_bytes(params);
	hstream->no_period_wakeup  =
			(params->info & SNDRV_PCM_INFO_NO_PERIOD_WAKEUP) &&
			(params->flags & SNDRV_PCM_HW_PARAMS_NO_PERIOD_WAKEUP);

	ret = hda_dsp_stream_hw_params(sdev, stream, dmab, params);
	अगर (ret < 0) अणु
		dev_err(sdev->dev, "error: hdac prepare failed: %d\n", ret);
		वापस ret;
	पूर्ण

	/* disable SPIB, to enable buffer wrap क्रम stream */
	hda_dsp_stream_spib_config(sdev, stream, HDA_DSP_SPIB_DISABLE, 0);

	/* update no_stream_position flag क्रम ipc params */
	अगर (hda && hda->no_ipc_position) अणु
		/* For older ABIs set host_period_bytes to zero to inक्रमm
		 * FW we करोn't want position updates. Newer versions use
		 * no_stream_position क्रम this purpose.
		 */
		अगर (v->abi_version < SOF_ABI_VER(3, 10, 0))
			ipc_params->host_period_bytes = 0;
		अन्यथा
			ipc_params->no_stream_position = 1;
	पूर्ण

	ipc_params->stream_tag = hstream->stream_tag;

	वापस 0;
पूर्ण

पूर्णांक hda_dsp_pcm_trigger(काष्ठा snd_sof_dev *sdev,
			काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा hdac_stream *hstream = substream->runसमय->निजी_data;
	काष्ठा hdac_ext_stream *stream = stream_to_hdac_ext_stream(hstream);

	वापस hda_dsp_stream_trigger(sdev, stream, cmd);
पूर्ण

snd_pcm_uframes_t hda_dsp_pcm_poपूर्णांकer(काष्ठा snd_sof_dev *sdev,
				      काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_component *scomp = sdev->component;
	काष्ठा hdac_stream *hstream = substream->runसमय->निजी_data;
	काष्ठा sof_पूर्णांकel_hda_dev *hda = sdev->pdata->hw_pdata;
	काष्ठा snd_sof_pcm *spcm;
	snd_pcm_uframes_t pos;

	spcm = snd_sof_find_spcm_dai(scomp, rtd);
	अगर (!spcm) अणु
		dev_warn_ratelimited(sdev->dev, "warn: can't find PCM with DAI ID %d\n",
				     rtd->dai_link->id);
		वापस 0;
	पूर्ण

	अगर (hda && !hda->no_ipc_position) अणु
		/* पढ़ो position from IPC position */
		pos = spcm->stream[substream->stream].posn.host_posn;
		जाओ found;
	पूर्ण

	/*
	 * DPIB/posbuf position mode:
	 * For Playback, Use DPIB रेजिस्टर from HDA space which
	 * reflects the actual data transferred.
	 * For Capture, Use the position buffer क्रम poपूर्णांकer, as DPIB
	 * is not accurate enough, its update may be completed
	 * earlier than the data written to DDR.
	 */
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		pos = snd_sof_dsp_पढ़ो(sdev, HDA_DSP_HDA_BAR,
				       AZX_REG_VS_SDXDPIB_XBASE +
				       (AZX_REG_VS_SDXDPIB_XINTERVAL *
					hstream->index));
	पूर्ण अन्यथा अणु
		/*
		 * For capture stream, we need more workaround to fix the
		 * position incorrect issue:
		 *
		 * 1. Wait at least 20us beक्रमe पढ़ोing position buffer after
		 * the पूर्णांकerrupt generated(IOC), to make sure position update
		 * happens on frame boundary i.e. 20.833uSec क्रम 48KHz.
		 * 2. Perक्रमm a dummy Read to DPIB रेजिस्टर to flush DMA
		 * position value.
		 * 3. Read the DMA Position from posbuf. Now the पढ़ोback
		 * value should be >= period boundary.
		 */
		usleep_range(20, 21);
		snd_sof_dsp_पढ़ो(sdev, HDA_DSP_HDA_BAR,
				 AZX_REG_VS_SDXDPIB_XBASE +
				 (AZX_REG_VS_SDXDPIB_XINTERVAL *
				  hstream->index));
		pos = snd_hdac_stream_get_pos_posbuf(hstream);
	पूर्ण

	अगर (pos >= hstream->bufsize)
		pos = 0;

found:
	pos = bytes_to_frames(substream->runसमय, pos);

	dev_vdbg(sdev->dev, "PCM: stream %d dir %d position %lu\n",
		 hstream->index, substream->stream, pos);
	वापस pos;
पूर्ण

पूर्णांक hda_dsp_pcm_खोलो(काष्ठा snd_sof_dev *sdev,
		     काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_component *scomp = sdev->component;
	काष्ठा hdac_ext_stream *dsp_stream;
	काष्ठा snd_sof_pcm *spcm;
	पूर्णांक direction = substream->stream;
	u32 flags = 0;

	spcm = snd_sof_find_spcm_dai(scomp, rtd);
	अगर (!spcm) अणु
		dev_err(sdev->dev, "error: can't find PCM with DAI ID %d\n", rtd->dai_link->id);
		वापस -EINVAL;
	पूर्ण

	/* All playback and D0i3 compatible streams are DMI L1 capable */
	अगर (direction == SNDRV_PCM_STREAM_PLAYBACK ||
	    spcm->stream[substream->stream].d0i3_compatible)
		flags |= SOF_HDA_STREAM_DMI_L1_COMPATIBLE;

	dsp_stream = hda_dsp_stream_get(sdev, direction, flags);
	अगर (!dsp_stream) अणु
		dev_err(sdev->dev, "error: no stream available\n");
		वापस -ENODEV;
	पूर्ण

	/* minimum as per HDA spec */
	snd_pcm_hw_स्थिरraपूर्णांक_step(substream->runसमय, 0, SNDRV_PCM_HW_PARAM_PERIOD_BYTES, 4);

	/* aव्योम circular buffer wrap in middle of period */
	snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(substream->runसमय,
				      SNDRV_PCM_HW_PARAM_PERIODS);

	/* binding pcm substream to hda stream */
	substream->runसमय->निजी_data = &dsp_stream->hstream;
	वापस 0;
पूर्ण

पूर्णांक hda_dsp_pcm_बंद(काष्ठा snd_sof_dev *sdev,
		      काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा hdac_stream *hstream = substream->runसमय->निजी_data;
	पूर्णांक direction = substream->stream;
	पूर्णांक ret;

	ret = hda_dsp_stream_put(sdev, direction, hstream->stream_tag);

	अगर (ret) अणु
		dev_dbg(sdev->dev, "stream %s not opened!\n", substream->name);
		वापस -ENODEV;
	पूर्ण

	/* unbinding pcm substream to hda stream */
	substream->runसमय->निजी_data = शून्य;
	वापस 0;
पूर्ण
