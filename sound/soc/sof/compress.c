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

#समावेश <sound/soc.h>
#समावेश "compress.h"
#समावेश "ops.h"
#समावेश "probe.h"

काष्ठा snd_compress_ops sof_probe_compressed_ops = अणु
	.copy		= sof_probe_compr_copy,
पूर्ण;
EXPORT_SYMBOL(sof_probe_compressed_ops);

पूर्णांक sof_probe_compr_खोलो(काष्ठा snd_compr_stream *cstream,
		काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_sof_dev *sdev =
				snd_soc_component_get_drvdata(dai->component);
	पूर्णांक ret;

	ret = snd_sof_probe_compr_assign(sdev, cstream, dai);
	अगर (ret < 0) अणु
		dev_err(dai->dev, "Failed to assign probe stream: %d\n", ret);
		वापस ret;
	पूर्ण

	sdev->extractor_stream_tag = ret;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(sof_probe_compr_खोलो);

पूर्णांक sof_probe_compr_मुक्त(काष्ठा snd_compr_stream *cstream,
		काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_sof_dev *sdev =
				snd_soc_component_get_drvdata(dai->component);
	काष्ठा sof_probe_poपूर्णांक_desc *desc;
	माप_प्रकार num_desc;
	पूर्णांक i, ret;

	/* disconnect all probe poपूर्णांकs */
	ret = sof_ipc_probe_poपूर्णांकs_info(sdev, &desc, &num_desc);
	अगर (ret < 0) अणु
		dev_err(dai->dev, "Failed to get probe points: %d\n", ret);
		जाओ निकास;
	पूर्ण

	क्रम (i = 0; i < num_desc; i++)
		sof_ipc_probe_poपूर्णांकs_हटाओ(sdev, &desc[i].buffer_id, 1);
	kमुक्त(desc);

निकास:
	ret = sof_ipc_probe_deinit(sdev);
	अगर (ret < 0)
		dev_err(dai->dev, "Failed to deinit probe: %d\n", ret);

	sdev->extractor_stream_tag = SOF_PROBE_INVALID_NODE_ID;
	snd_compr_मुक्त_pages(cstream);

	वापस snd_sof_probe_compr_मुक्त(sdev, cstream, dai);
पूर्ण
EXPORT_SYMBOL(sof_probe_compr_मुक्त);

पूर्णांक sof_probe_compr_set_params(काष्ठा snd_compr_stream *cstream,
		काष्ठा snd_compr_params *params, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_compr_runसमय *rtd = cstream->runसमय;
	काष्ठा snd_sof_dev *sdev =
				snd_soc_component_get_drvdata(dai->component);
	पूर्णांक ret;

	cstream->dma_buffer.dev.type = SNDRV_DMA_TYPE_DEV_SG;
	cstream->dma_buffer.dev.dev = sdev->dev;
	ret = snd_compr_दो_स्मृति_pages(cstream, rtd->buffer_size);
	अगर (ret < 0)
		वापस ret;

	ret = snd_sof_probe_compr_set_params(sdev, cstream, params, dai);
	अगर (ret < 0)
		वापस ret;

	ret = sof_ipc_probe_init(sdev, sdev->extractor_stream_tag,
				 rtd->dma_bytes);
	अगर (ret < 0) अणु
		dev_err(dai->dev, "Failed to init probe: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(sof_probe_compr_set_params);

पूर्णांक sof_probe_compr_trigger(काष्ठा snd_compr_stream *cstream, पूर्णांक cmd,
		काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_sof_dev *sdev =
				snd_soc_component_get_drvdata(dai->component);

	वापस snd_sof_probe_compr_trigger(sdev, cstream, cmd, dai);
पूर्ण
EXPORT_SYMBOL(sof_probe_compr_trigger);

पूर्णांक sof_probe_compr_poपूर्णांकer(काष्ठा snd_compr_stream *cstream,
		काष्ठा snd_compr_tstamp *tstamp, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_sof_dev *sdev =
				snd_soc_component_get_drvdata(dai->component);

	वापस snd_sof_probe_compr_poपूर्णांकer(sdev, cstream, tstamp, dai);
पूर्ण
EXPORT_SYMBOL(sof_probe_compr_poपूर्णांकer);

पूर्णांक sof_probe_compr_copy(काष्ठा snd_soc_component *component,
			 काष्ठा snd_compr_stream *cstream,
			 अक्षर __user *buf, माप_प्रकार count)
अणु
	काष्ठा snd_compr_runसमय *rtd = cstream->runसमय;
	अचिन्हित पूर्णांक offset, n;
	व्योम *ptr;
	पूर्णांक ret;

	अगर (count > rtd->buffer_size)
		count = rtd->buffer_size;

	भाग_u64_rem(rtd->total_bytes_transferred, rtd->buffer_size, &offset);
	ptr = rtd->dma_area + offset;
	n = rtd->buffer_size - offset;

	अगर (count < n) अणु
		ret = copy_to_user(buf, ptr, count);
	पूर्ण अन्यथा अणु
		ret = copy_to_user(buf, ptr, n);
		ret += copy_to_user(buf + n, rtd->dma_area, count - n);
	पूर्ण

	अगर (ret)
		वापस count - ret;
	वापस count;
पूर्ण
EXPORT_SYMBOL(sof_probe_compr_copy);
