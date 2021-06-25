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

#समावेश <sound/hdaudio_ext.h>
#समावेश "../ops.h"
#समावेश "hda.h"

अटल पूर्णांक hda_dsp_trace_prepare(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा sof_पूर्णांकel_hda_dev *hda = sdev->pdata->hw_pdata;
	काष्ठा hdac_ext_stream *stream = hda->dtrace_stream;
	काष्ठा hdac_stream *hstream = &stream->hstream;
	काष्ठा snd_dma_buffer *dmab = &sdev->dmatb;
	पूर्णांक ret;

	hstream->period_bytes = 0;/* initialize period_bytes */
	hstream->bufsize = sdev->dmatb.bytes;

	ret = hda_dsp_stream_hw_params(sdev, stream, dmab, शून्य);
	अगर (ret < 0)
		dev_err(sdev->dev, "error: hdac prepare failed: %d\n", ret);

	वापस ret;
पूर्ण

पूर्णांक hda_dsp_trace_init(काष्ठा snd_sof_dev *sdev, u32 *stream_tag)
अणु
	काष्ठा sof_पूर्णांकel_hda_dev *hda = sdev->pdata->hw_pdata;
	पूर्णांक ret;

	hda->dtrace_stream = hda_dsp_stream_get(sdev, SNDRV_PCM_STREAM_CAPTURE,
						SOF_HDA_STREAM_DMI_L1_COMPATIBLE);

	अगर (!hda->dtrace_stream) अणु
		dev_err(sdev->dev,
			"error: no available capture stream for DMA trace\n");
		वापस -ENODEV;
	पूर्ण

	*stream_tag = hda->dtrace_stream->hstream.stream_tag;

	/*
	 * initialize capture stream, set BDL address and वापस corresponding
	 * stream tag which will be sent to the firmware by IPC message.
	 */
	ret = hda_dsp_trace_prepare(sdev);
	अगर (ret < 0) अणु
		dev_err(sdev->dev, "error: hdac trace init failed: %d\n", ret);
		hda_dsp_stream_put(sdev, SNDRV_PCM_STREAM_CAPTURE, *stream_tag);
		hda->dtrace_stream = शून्य;
		*stream_tag = 0;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक hda_dsp_trace_release(काष्ठा snd_sof_dev *sdev)
अणु
	काष्ठा sof_पूर्णांकel_hda_dev *hda = sdev->pdata->hw_pdata;
	काष्ठा hdac_stream *hstream;

	अगर (hda->dtrace_stream) अणु
		hstream = &hda->dtrace_stream->hstream;
		hda_dsp_stream_put(sdev,
				   SNDRV_PCM_STREAM_CAPTURE,
				   hstream->stream_tag);
		hda->dtrace_stream = शून्य;
		वापस 0;
	पूर्ण

	dev_dbg(sdev->dev, "DMA trace stream is not opened!\n");
	वापस -ENODEV;
पूर्ण

पूर्णांक hda_dsp_trace_trigger(काष्ठा snd_sof_dev *sdev, पूर्णांक cmd)
अणु
	काष्ठा sof_पूर्णांकel_hda_dev *hda = sdev->pdata->hw_pdata;

	वापस hda_dsp_stream_trigger(sdev, hda->dtrace_stream, cmd);
पूर्ण
