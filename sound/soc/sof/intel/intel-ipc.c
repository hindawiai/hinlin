<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
//
// This file is provided under a dual BSD/GPLv2 license.  When using or
// redistributing this file, you may करो so under either license.
//
// Copyright(c) 2019 Intel Corporation. All rights reserved.
//
// Authors: Guennadi Liakhovetski <guennadi.liakhovetski@linux.पूर्णांकel.com>

/* Intel-specअगरic SOF IPC code */

#समावेश <linux/device.h>
#समावेश <linux/export.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>

#समावेश <sound/pcm.h>
#समावेश <sound/sof/stream.h>

#समावेश "../ops.h"
#समावेश "../sof-priv.h"

काष्ठा पूर्णांकel_stream अणु
	माप_प्रकार posn_offset;
पूर्ण;

/* Mailbox-based Intel IPC implementation */
व्योम पूर्णांकel_ipc_msg_data(काष्ठा snd_sof_dev *sdev,
			काष्ठा snd_pcm_substream *substream,
			व्योम *p, माप_प्रकार sz)
अणु
	अगर (!substream || !sdev->stream_box.size) अणु
		sof_mailbox_पढ़ो(sdev, sdev->dsp_box.offset, p, sz);
	पूर्ण अन्यथा अणु
		काष्ठा पूर्णांकel_stream *stream = substream->runसमय->निजी_data;

		/* The stream might alपढ़ोy be बंदd */
		अगर (stream)
			sof_mailbox_पढ़ो(sdev, stream->posn_offset, p, sz);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_NS(पूर्णांकel_ipc_msg_data, SND_SOC_SOF_INTEL_HIFI_EP_IPC);

पूर्णांक पूर्णांकel_ipc_pcm_params(काष्ठा snd_sof_dev *sdev,
			 काष्ठा snd_pcm_substream *substream,
			 स्थिर काष्ठा sof_ipc_pcm_params_reply *reply)
अणु
	काष्ठा पूर्णांकel_stream *stream = substream->runसमय->निजी_data;
	माप_प्रकार posn_offset = reply->posn_offset;

	/* check अगर offset is overflow or it is not aligned */
	अगर (posn_offset > sdev->stream_box.size ||
	    posn_offset % माप(काष्ठा sof_ipc_stream_posn) != 0)
		वापस -EINVAL;

	stream->posn_offset = sdev->stream_box.offset + posn_offset;

	dev_dbg(sdev->dev, "pcm: stream dir %d, posn mailbox offset is %zu",
		substream->stream, stream->posn_offset);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_NS(पूर्णांकel_ipc_pcm_params, SND_SOC_SOF_INTEL_HIFI_EP_IPC);

पूर्णांक पूर्णांकel_pcm_खोलो(काष्ठा snd_sof_dev *sdev,
		   काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा पूर्णांकel_stream *stream = kदो_स्मृति(माप(*stream), GFP_KERNEL);

	अगर (!stream)
		वापस -ENOMEM;

	/* binding pcm substream to hda stream */
	substream->runसमय->निजी_data = stream;

	/* align to DMA minimum transfer size */
	snd_pcm_hw_स्थिरraपूर्णांक_step(substream->runसमय, 0, SNDRV_PCM_HW_PARAM_PERIOD_BYTES, 4);

	/* aव्योम circular buffer wrap in middle of period */
	snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(substream->runसमय,
				      SNDRV_PCM_HW_PARAM_PERIODS);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_NS(पूर्णांकel_pcm_खोलो, SND_SOC_SOF_INTEL_HIFI_EP_IPC);

पूर्णांक पूर्णांकel_pcm_बंद(काष्ठा snd_sof_dev *sdev,
		    काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा पूर्णांकel_stream *stream = substream->runसमय->निजी_data;

	substream->runसमय->निजी_data = शून्य;
	kमुक्त(stream);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_NS(पूर्णांकel_pcm_बंद, SND_SOC_SOF_INTEL_HIFI_EP_IPC);

MODULE_LICENSE("Dual BSD/GPL");
