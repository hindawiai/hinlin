<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
//
// Copyright(c) 2020 Intel Corporation. All rights reserved.
//
// Author: Cezary Rojewski <cezary.rojewski@पूर्णांकel.com>
//

#समावेश <linux/pm_runसमय.स>
#समावेश <sound/soc.h>
#समावेश <sound/pcm_params.h>
#समावेश <uapi/sound/tlv.h>
#समावेश "core.h"
#समावेश "messages.h"

काष्ठा catpt_stream_ढाँचा अणु
	क्रमागत catpt_path_id path_id;
	क्रमागत catpt_stream_type type;
	u32 persistent_size;
	u8 num_entries;
	काष्ठा catpt_module_entry entries[];
पूर्ण;

अटल काष्ठा catpt_stream_ढाँचा प्रणाली_pb = अणु
	.path_id = CATPT_PATH_SSP0_OUT,
	.type = CATPT_STRM_TYPE_SYSTEM,
	.num_entries = 1,
	.entries = अणुअणु CATPT_MODID_PCM_SYSTEM, 0 पूर्णपूर्ण,
पूर्ण;

अटल काष्ठा catpt_stream_ढाँचा प्रणाली_cp = अणु
	.path_id = CATPT_PATH_SSP0_IN,
	.type = CATPT_STRM_TYPE_CAPTURE,
	.num_entries = 1,
	.entries = अणुअणु CATPT_MODID_PCM_CAPTURE, 0 पूर्णपूर्ण,
पूर्ण;

अटल काष्ठा catpt_stream_ढाँचा offload_pb = अणु
	.path_id = CATPT_PATH_SSP0_OUT,
	.type = CATPT_STRM_TYPE_RENDER,
	.num_entries = 1,
	.entries = अणुअणु CATPT_MODID_PCM, 0 पूर्णपूर्ण,
पूर्ण;

अटल काष्ठा catpt_stream_ढाँचा loopback_cp = अणु
	.path_id = CATPT_PATH_SSP0_OUT,
	.type = CATPT_STRM_TYPE_LOOPBACK,
	.num_entries = 1,
	.entries = अणुअणु CATPT_MODID_PCM_REFERENCE, 0 पूर्णपूर्ण,
पूर्ण;

अटल काष्ठा catpt_stream_ढाँचा bluetooth_pb = अणु
	.path_id = CATPT_PATH_SSP1_OUT,
	.type = CATPT_STRM_TYPE_BLUETOOTH_RENDER,
	.num_entries = 1,
	.entries = अणुअणु CATPT_MODID_BLUETOOTH_RENDER, 0 पूर्णपूर्ण,
पूर्ण;

अटल काष्ठा catpt_stream_ढाँचा bluetooth_cp = अणु
	.path_id = CATPT_PATH_SSP1_IN,
	.type = CATPT_STRM_TYPE_BLUETOOTH_CAPTURE,
	.num_entries = 1,
	.entries = अणुअणु CATPT_MODID_BLUETOOTH_CAPTURE, 0 पूर्णपूर्ण,
पूर्ण;

अटल काष्ठा catpt_stream_ढाँचा *catpt_topology[] = अणु
	[CATPT_STRM_TYPE_RENDER]		= &offload_pb,
	[CATPT_STRM_TYPE_SYSTEM]		= &प्रणाली_pb,
	[CATPT_STRM_TYPE_CAPTURE]		= &प्रणाली_cp,
	[CATPT_STRM_TYPE_LOOPBACK]		= &loopback_cp,
	[CATPT_STRM_TYPE_BLUETOOTH_RENDER]	= &bluetooth_pb,
	[CATPT_STRM_TYPE_BLUETOOTH_CAPTURE]	= &bluetooth_cp,
पूर्ण;

अटल काष्ठा catpt_stream_ढाँचा *
catpt_get_stream_ढाँचा(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rपंचांग = substream->निजी_data;
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rपंचांग, 0);
	क्रमागत catpt_stream_type type;

	type = cpu_dai->driver->id;

	/* account क्रम capture in bidirectional dais */
	चयन (type) अणु
	हाल CATPT_STRM_TYPE_SYSTEM:
		अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
			type = CATPT_STRM_TYPE_CAPTURE;
		अवरोध;
	हाल CATPT_STRM_TYPE_BLUETOOTH_RENDER:
		अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
			type = CATPT_STRM_TYPE_BLUETOOTH_CAPTURE;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस catpt_topology[type];
पूर्ण

काष्ठा catpt_stream_runसमय *
catpt_stream_find(काष्ठा catpt_dev *cdev, u8 stream_hw_id)
अणु
	काष्ठा catpt_stream_runसमय *pos, *result = शून्य;

	spin_lock(&cdev->list_lock);
	list_क्रम_each_entry(pos, &cdev->stream_list, node) अणु
		अगर (pos->info.stream_hw_id == stream_hw_id) अणु
			result = pos;
			अवरोध;
		पूर्ण
	पूर्ण

	spin_unlock(&cdev->list_lock);
	वापस result;
पूर्ण

अटल u32 catpt_stream_पढ़ो_position(काष्ठा catpt_dev *cdev,
				      काष्ठा catpt_stream_runसमय *stream)
अणु
	u32 pos;

	स_नकल_fromio(&pos, cdev->lpe_ba + stream->info.पढ़ो_pos_regaddr,
		      माप(pos));
	वापस pos;
पूर्ण

अटल u32 catpt_stream_volume(काष्ठा catpt_dev *cdev,
			       काष्ठा catpt_stream_runसमय *stream, u32 channel)
अणु
	u32 volume, offset;

	अगर (channel >= CATPT_CHANNELS_MAX)
		channel = 0;

	offset = stream->info.volume_regaddr[channel];
	स_नकल_fromio(&volume, cdev->lpe_ba + offset, माप(volume));
	वापस volume;
पूर्ण

अटल u32 catpt_mixer_volume(काष्ठा catpt_dev *cdev,
			      काष्ठा catpt_mixer_stream_info *info, u32 channel)
अणु
	u32 volume, offset;

	अगर (channel >= CATPT_CHANNELS_MAX)
		channel = 0;

	offset = info->volume_regaddr[channel];
	स_नकल_fromio(&volume, cdev->lpe_ba + offset, माप(volume));
	वापस volume;
पूर्ण

अटल व्योम catpt_arrange_page_table(काष्ठा snd_pcm_substream *substream,
				     काष्ठा snd_dma_buffer *pgtbl)
अणु
	काष्ठा snd_pcm_runसमय *rपंचांग = substream->runसमय;
	काष्ठा snd_dma_buffer *databuf = snd_pcm_get_dma_buf(substream);
	पूर्णांक i, pages;

	pages = snd_sgbuf_aligned_pages(rपंचांग->dma_bytes);

	क्रम (i = 0; i < pages; i++) अणु
		u32 pfn, offset;
		u32 *page_table;

		pfn = PFN_DOWN(snd_sgbuf_get_addr(databuf, i * PAGE_SIZE));
		/* incrementing by 2 on even and 3 on odd */
		offset = ((i << 2) + i) >> 1;
		page_table = (u32 *)(pgtbl->area + offset);

		अगर (i & 1)
			*page_table |= (pfn << 4);
		अन्यथा
			*page_table |= pfn;
	पूर्ण
पूर्ण

अटल u32 catpt_get_channel_map(क्रमागत catpt_channel_config config)
अणु
	चयन (config) अणु
	हाल CATPT_CHANNEL_CONFIG_MONO:
		वापस GENMASK(31, 4) | CATPT_CHANNEL_CENTER;

	हाल CATPT_CHANNEL_CONFIG_STEREO:
		वापस GENMASK(31, 8) | CATPT_CHANNEL_LEFT
				      | (CATPT_CHANNEL_RIGHT << 4);

	हाल CATPT_CHANNEL_CONFIG_2_POINT_1:
		वापस GENMASK(31, 12) | CATPT_CHANNEL_LEFT
				       | (CATPT_CHANNEL_RIGHT << 4)
				       | (CATPT_CHANNEL_LFE << 8);

	हाल CATPT_CHANNEL_CONFIG_3_POINT_0:
		वापस GENMASK(31, 12) | CATPT_CHANNEL_LEFT
				       | (CATPT_CHANNEL_CENTER << 4)
				       | (CATPT_CHANNEL_RIGHT << 8);

	हाल CATPT_CHANNEL_CONFIG_3_POINT_1:
		वापस GENMASK(31, 16) | CATPT_CHANNEL_LEFT
				       | (CATPT_CHANNEL_CENTER << 4)
				       | (CATPT_CHANNEL_RIGHT << 8)
				       | (CATPT_CHANNEL_LFE << 12);

	हाल CATPT_CHANNEL_CONFIG_QUATRO:
		वापस GENMASK(31, 16) | CATPT_CHANNEL_LEFT
				       | (CATPT_CHANNEL_RIGHT << 4)
				       | (CATPT_CHANNEL_LEFT_SURROUND << 8)
				       | (CATPT_CHANNEL_RIGHT_SURROUND << 12);

	हाल CATPT_CHANNEL_CONFIG_4_POINT_0:
		वापस GENMASK(31, 16) | CATPT_CHANNEL_LEFT
				       | (CATPT_CHANNEL_CENTER << 4)
				       | (CATPT_CHANNEL_RIGHT << 8)
				       | (CATPT_CHANNEL_CENTER_SURROUND << 12);

	हाल CATPT_CHANNEL_CONFIG_5_POINT_0:
		वापस GENMASK(31, 20) | CATPT_CHANNEL_LEFT
				       | (CATPT_CHANNEL_CENTER << 4)
				       | (CATPT_CHANNEL_RIGHT << 8)
				       | (CATPT_CHANNEL_LEFT_SURROUND << 12)
				       | (CATPT_CHANNEL_RIGHT_SURROUND << 16);

	हाल CATPT_CHANNEL_CONFIG_5_POINT_1:
		वापस GENMASK(31, 24) | CATPT_CHANNEL_CENTER
				       | (CATPT_CHANNEL_LEFT << 4)
				       | (CATPT_CHANNEL_RIGHT << 8)
				       | (CATPT_CHANNEL_LEFT_SURROUND << 12)
				       | (CATPT_CHANNEL_RIGHT_SURROUND << 16)
				       | (CATPT_CHANNEL_LFE << 20);

	हाल CATPT_CHANNEL_CONFIG_DUAL_MONO:
		वापस GENMASK(31, 8) | CATPT_CHANNEL_LEFT
				      | (CATPT_CHANNEL_LEFT << 4);

	शेष:
		वापस U32_MAX;
	पूर्ण
पूर्ण

अटल क्रमागत catpt_channel_config catpt_get_channel_config(u32 num_channels)
अणु
	चयन (num_channels) अणु
	हाल 6:
		वापस CATPT_CHANNEL_CONFIG_5_POINT_1;
	हाल 5:
		वापस CATPT_CHANNEL_CONFIG_5_POINT_0;
	हाल 4:
		वापस CATPT_CHANNEL_CONFIG_QUATRO;
	हाल 3:
		वापस CATPT_CHANNEL_CONFIG_2_POINT_1;
	हाल 1:
		वापस CATPT_CHANNEL_CONFIG_MONO;
	हाल 2:
	शेष:
		वापस CATPT_CHANNEL_CONFIG_STEREO;
	पूर्ण
पूर्ण

अटल पूर्णांक catpt_dai_startup(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा catpt_dev *cdev = dev_get_drvdata(dai->dev);
	काष्ठा catpt_stream_ढाँचा *ढाँचा;
	काष्ठा catpt_stream_runसमय *stream;
	काष्ठा resource *res;
	पूर्णांक ret;

	ढाँचा = catpt_get_stream_ढाँचा(substream);

	stream = kzalloc(माप(*stream), GFP_KERNEL);
	अगर (!stream)
		वापस -ENOMEM;

	ret = snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV, cdev->dev, PAGE_SIZE,
				  &stream->pgtbl);
	अगर (ret)
		जाओ err_pgtbl;

	res = catpt_request_region(&cdev->dram, ढाँचा->persistent_size);
	अगर (!res) अणु
		ret = -EBUSY;
		जाओ err_request;
	पूर्ण

	catpt_dsp_update_srampge(cdev, &cdev->dram, cdev->spec->dram_mask);

	stream->ढाँचा = ढाँचा;
	stream->persistent = res;
	stream->substream = substream;
	INIT_LIST_HEAD(&stream->node);
	snd_soc_dai_set_dma_data(dai, substream, stream);

	spin_lock(&cdev->list_lock);
	list_add_tail(&stream->node, &cdev->stream_list);
	spin_unlock(&cdev->list_lock);

	वापस 0;

err_request:
	snd_dma_मुक्त_pages(&stream->pgtbl);
err_pgtbl:
	kमुक्त(stream);
	वापस ret;
पूर्ण

अटल व्योम catpt_dai_shutकरोwn(काष्ठा snd_pcm_substream *substream,
			       काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा catpt_dev *cdev = dev_get_drvdata(dai->dev);
	काष्ठा catpt_stream_runसमय *stream;

	stream = snd_soc_dai_get_dma_data(dai, substream);

	spin_lock(&cdev->list_lock);
	list_del(&stream->node);
	spin_unlock(&cdev->list_lock);

	release_resource(stream->persistent);
	kमुक्त(stream->persistent);
	catpt_dsp_update_srampge(cdev, &cdev->dram, cdev->spec->dram_mask);

	snd_dma_मुक्त_pages(&stream->pgtbl);
	kमुक्त(stream);
	snd_soc_dai_set_dma_data(dai, substream, शून्य);
पूर्ण

अटल पूर्णांक catpt_set_dspvol(काष्ठा catpt_dev *cdev, u8 stream_id, दीर्घ *ctlvol);

अटल पूर्णांक catpt_dai_apply_usettings(काष्ठा snd_soc_dai *dai,
				     काष्ठा catpt_stream_runसमय *stream)
अणु
	काष्ठा catpt_dev *cdev = dev_get_drvdata(dai->dev);
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा snd_kcontrol *pos;
	स्थिर अक्षर *name;
	पूर्णांक ret;
	u32 id = stream->info.stream_hw_id;

	/* only selected streams have inभागidual controls */
	चयन (id) अणु
	हाल CATPT_PIN_ID_OFFLOAD1:
		name = "Media0 Playback Volume";
		अवरोध;
	हाल CATPT_PIN_ID_OFFLOAD2:
		name = "Media1 Playback Volume";
		अवरोध;
	हाल CATPT_PIN_ID_CAPTURE1:
		name = "Mic Capture Volume";
		अवरोध;
	हाल CATPT_PIN_ID_REFERENCE:
		name = "Loopback Mute";
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	list_क्रम_each_entry(pos, &component->card->snd_card->controls, list) अणु
		अगर (pos->निजी_data == component &&
		    !म_भेदन(name, pos->id.name, माप(pos->id.name)))
			अवरोध;
	पूर्ण
	अगर (list_entry_is_head(pos, &component->card->snd_card->controls, list))
		वापस -ENOENT;

	अगर (stream->ढाँचा->type != CATPT_STRM_TYPE_LOOPBACK)
		वापस catpt_set_dspvol(cdev, id, (दीर्घ *)pos->निजी_value);
	ret = catpt_ipc_mute_loopback(cdev, id, *(bool *)pos->निजी_value);
	अगर (ret)
		वापस CATPT_IPC_ERROR(ret);
	वापस 0;
पूर्ण

अटल पूर्णांक catpt_dai_hw_params(काष्ठा snd_pcm_substream *substream,
			       काष्ठा snd_pcm_hw_params *params,
			       काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा catpt_dev *cdev = dev_get_drvdata(dai->dev);
	काष्ठा catpt_stream_runसमय *stream;
	काष्ठा catpt_audio_क्रमmat afmt;
	काष्ठा catpt_ring_info rinfo;
	काष्ठा snd_pcm_runसमय *rपंचांग = substream->runसमय;
	काष्ठा snd_dma_buffer *dmab;
	पूर्णांक ret;

	stream = snd_soc_dai_get_dma_data(dai, substream);
	अगर (stream->allocated)
		वापस 0;

	स_रखो(&afmt, 0, माप(afmt));
	afmt.sample_rate = params_rate(params);
	afmt.bit_depth = params_physical_width(params);
	afmt.valid_bit_depth = params_width(params);
	afmt.num_channels = params_channels(params);
	afmt.channel_config = catpt_get_channel_config(afmt.num_channels);
	afmt.channel_map = catpt_get_channel_map(afmt.channel_config);
	afmt.पूर्णांकerleaving = CATPT_INTERLEAVING_PER_CHANNEL;

	dmab = snd_pcm_get_dma_buf(substream);
	catpt_arrange_page_table(substream, &stream->pgtbl);

	स_रखो(&rinfo, 0, माप(rinfo));
	rinfo.page_table_addr = stream->pgtbl.addr;
	rinfo.num_pages = DIV_ROUND_UP(rपंचांग->dma_bytes, PAGE_SIZE);
	rinfo.size = rपंचांग->dma_bytes;
	rinfo.offset = 0;
	rinfo.ring_first_page_pfn = PFN_DOWN(snd_sgbuf_get_addr(dmab, 0));

	ret = catpt_ipc_alloc_stream(cdev, stream->ढाँचा->path_id,
				     stream->ढाँचा->type,
				     &afmt, &rinfo,
				     stream->ढाँचा->num_entries,
				     stream->ढाँचा->entries,
				     stream->persistent,
				     cdev->scratch,
				     &stream->info);
	अगर (ret)
		वापस CATPT_IPC_ERROR(ret);

	ret = catpt_dai_apply_usettings(dai, stream);
	अगर (ret)
		वापस ret;

	stream->allocated = true;
	वापस 0;
पूर्ण

अटल पूर्णांक catpt_dai_hw_मुक्त(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा catpt_dev *cdev = dev_get_drvdata(dai->dev);
	काष्ठा catpt_stream_runसमय *stream;

	stream = snd_soc_dai_get_dma_data(dai, substream);
	अगर (!stream->allocated)
		वापस 0;

	catpt_ipc_reset_stream(cdev, stream->info.stream_hw_id);
	catpt_ipc_मुक्त_stream(cdev, stream->info.stream_hw_id);

	stream->allocated = false;
	वापस 0;
पूर्ण

अटल पूर्णांक catpt_dai_prepare(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा catpt_dev *cdev = dev_get_drvdata(dai->dev);
	काष्ठा catpt_stream_runसमय *stream;
	पूर्णांक ret;

	stream = snd_soc_dai_get_dma_data(dai, substream);
	अगर (stream->prepared)
		वापस 0;

	ret = catpt_ipc_reset_stream(cdev, stream->info.stream_hw_id);
	अगर (ret)
		वापस CATPT_IPC_ERROR(ret);

	ret = catpt_ipc_छोड़ो_stream(cdev, stream->info.stream_hw_id);
	अगर (ret)
		वापस CATPT_IPC_ERROR(ret);

	stream->prepared = true;
	वापस 0;
पूर्ण

अटल पूर्णांक catpt_dai_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
			     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा catpt_dev *cdev = dev_get_drvdata(dai->dev);
	काष्ठा catpt_stream_runसमय *stream;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	snd_pcm_uframes_t pos;
	पूर्णांक ret;

	stream = snd_soc_dai_get_dma_data(dai, substream);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		/* only offload is set_ग_लिखो_pos driven */
		अगर (stream->ढाँचा->type != CATPT_STRM_TYPE_RENDER)
			जाओ resume_stream;

		pos = frames_to_bytes(runसमय, runसमय->start_threshold);
		/*
		 * Dsp operates on buffer halves, thus max 2x set_ग_लिखो_pos
		 * (entire buffer filled) prior to stream start.
		 */
		ret = catpt_ipc_set_ग_लिखो_pos(cdev, stream->info.stream_hw_id,
					      pos, false, false);
		अगर (ret)
			वापस CATPT_IPC_ERROR(ret);
		fallthrough;
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
	resume_stream:
		catpt_dsp_update_lpघड़ी(cdev);
		ret = catpt_ipc_resume_stream(cdev, stream->info.stream_hw_id);
		अगर (ret)
			वापस CATPT_IPC_ERROR(ret);
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_STOP:
		stream->prepared = false;
		fallthrough;
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		ret = catpt_ipc_छोड़ो_stream(cdev, stream->info.stream_hw_id);
		catpt_dsp_update_lpघड़ी(cdev);
		अगर (ret)
			वापस CATPT_IPC_ERROR(ret);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

व्योम catpt_stream_update_position(काष्ठा catpt_dev *cdev,
				  काष्ठा catpt_stream_runसमय *stream,
				  काष्ठा catpt_notअगरy_position *pos)
अणु
	काष्ठा snd_pcm_substream *substream = stream->substream;
	काष्ठा snd_pcm_runसमय *r = substream->runसमय;
	snd_pcm_uframes_t dsppos, newpos;
	पूर्णांक ret;

	dsppos = bytes_to_frames(r, pos->stream_position);

	अगर (!stream->prepared)
		जाओ निकास;
	/* only offload is set_ग_लिखो_pos driven */
	अगर (stream->ढाँचा->type != CATPT_STRM_TYPE_RENDER)
		जाओ निकास;

	अगर (dsppos >= r->buffer_size / 2)
		newpos = r->buffer_size / 2;
	अन्यथा
		newpos = 0;
	/*
	 * Dsp operates on buffer halves, thus on every notअगरy position
	 * (buffer half consumed) update wp to allow stream progression.
	 */
	ret = catpt_ipc_set_ग_लिखो_pos(cdev, stream->info.stream_hw_id,
				      frames_to_bytes(r, newpos),
				      false, false);
	अगर (ret) अणु
		dev_err(cdev->dev, "update position for stream %d failed: %d\n",
			stream->info.stream_hw_id, ret);
		वापस;
	पूर्ण
निकास:
	snd_pcm_period_elapsed(substream);
पूर्ण

/* 200 ms क्रम 2 32-bit channels at 48kHz (native क्रमmat) */
#घोषणा CATPT_BUFFER_MAX_SIZE	76800
#घोषणा CATPT_PCM_PERIODS_MAX	4
#घोषणा CATPT_PCM_PERIODS_MIN	2

अटल स्थिर काष्ठा snd_pcm_hardware catpt_pcm_hardware = अणु
	.info			= SNDRV_PCM_INFO_MMAP |
				  SNDRV_PCM_INFO_MMAP_VALID |
				  SNDRV_PCM_INFO_INTERLEAVED |
				  SNDRV_PCM_INFO_PAUSE |
				  SNDRV_PCM_INFO_RESUME |
				  SNDRV_PCM_INFO_NO_PERIOD_WAKEUP,
	.क्रमmats		= SNDRV_PCM_FMTBIT_S16_LE |
				  SNDRV_PCM_FMTBIT_S24_LE |
				  SNDRV_PCM_FMTBIT_S32_LE,
	.period_bytes_min	= PAGE_SIZE,
	.period_bytes_max	= CATPT_BUFFER_MAX_SIZE / CATPT_PCM_PERIODS_MIN,
	.periods_min		= CATPT_PCM_PERIODS_MIN,
	.periods_max		= CATPT_PCM_PERIODS_MAX,
	.buffer_bytes_max	= CATPT_BUFFER_MAX_SIZE,
पूर्ण;

अटल पूर्णांक catpt_component_pcm_स्थिरruct(काष्ठा snd_soc_component *component,
					 काष्ठा snd_soc_pcm_runसमय *rपंचांग)
अणु
	काष्ठा catpt_dev *cdev = dev_get_drvdata(component->dev);

	snd_pcm_set_managed_buffer_all(rपंचांग->pcm, SNDRV_DMA_TYPE_DEV_SG,
				       cdev->dev,
				       catpt_pcm_hardware.buffer_bytes_max,
				       catpt_pcm_hardware.buffer_bytes_max);

	वापस 0;
पूर्ण

अटल पूर्णांक catpt_component_खोलो(काष्ठा snd_soc_component *component,
				काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rपंचांग = substream->निजी_data;

	अगर (rपंचांग->dai_link->no_pcm)
		वापस 0;
	snd_soc_set_runसमय_hwparams(substream, &catpt_pcm_hardware);
	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t
catpt_component_poपूर्णांकer(काष्ठा snd_soc_component *component,
			काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा catpt_dev *cdev = dev_get_drvdata(component->dev);
	काष्ठा catpt_stream_runसमय *stream;
	काष्ठा snd_soc_pcm_runसमय *rपंचांग = substream->निजी_data;
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rपंचांग, 0);
	u32 pos;

	अगर (rपंचांग->dai_link->no_pcm)
		वापस 0;

	stream = snd_soc_dai_get_dma_data(cpu_dai, substream);
	pos = catpt_stream_पढ़ो_position(cdev, stream);

	वापस bytes_to_frames(substream->runसमय, pos);
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops catpt_fe_dai_ops = अणु
	.startup = catpt_dai_startup,
	.shutकरोwn = catpt_dai_shutकरोwn,
	.hw_params = catpt_dai_hw_params,
	.hw_मुक्त = catpt_dai_hw_मुक्त,
	.prepare = catpt_dai_prepare,
	.trigger = catpt_dai_trigger,
पूर्ण;

अटल पूर्णांक catpt_dai_pcm_new(काष्ठा snd_soc_pcm_runसमय *rपंचांग,
			     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rपंचांग, 0);
	काष्ठा catpt_dev *cdev = dev_get_drvdata(dai->dev);
	काष्ठा catpt_ssp_device_क्रमmat devfmt;
	पूर्णांक ret;

	devfmt.अगरace = dai->driver->id;
	devfmt.channels = codec_dai->driver->capture.channels_max;

	चयन (devfmt.अगरace) अणु
	हाल CATPT_SSP_IFACE_0:
		devfmt.mclk = CATPT_MCLK_FREQ_24_MHZ;

		चयन (devfmt.channels) अणु
		हाल 4:
			devfmt.mode = CATPT_SSP_MODE_TDM_PROVIDER;
			devfmt.घड़ी_भागider = 4;
			अवरोध;
		हाल 2:
		शेष:
			devfmt.mode = CATPT_SSP_MODE_I2S_PROVIDER;
			devfmt.घड़ी_भागider = 9;
			अवरोध;
		पूर्ण
		अवरोध;

	हाल CATPT_SSP_IFACE_1:
		devfmt.mclk = CATPT_MCLK_OFF;
		devfmt.mode = CATPT_SSP_MODE_I2S_CONSUMER;
		devfmt.घड़ी_भागider = 0;
		अवरोध;
	पूर्ण

	/* see अगर this is a new configuration */
	अगर (!स_भेद(&cdev->devfmt[devfmt.अगरace], &devfmt, माप(devfmt)))
		वापस 0;

	pm_runसमय_get_sync(cdev->dev);

	ret = catpt_ipc_set_device_क्रमmat(cdev, &devfmt);

	pm_runसमय_mark_last_busy(cdev->dev);
	pm_runसमय_put_स्वतःsuspend(cdev->dev);

	अगर (ret)
		वापस CATPT_IPC_ERROR(ret);

	/* store device क्रमmat set क्रम given SSP */
	स_नकल(&cdev->devfmt[devfmt.अगरace], &devfmt, माप(devfmt));
	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_dai_driver dai_drivers[] = अणु
/* FE DAIs */
अणु
	.name  = "System Pin",
	.id = CATPT_STRM_TYPE_SYSTEM,
	.ops = &catpt_fe_dai_ops,
	.playback = अणु
		.stream_name = "System Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S24_LE,
	पूर्ण,
	.capture = अणु
		.stream_name = "Analog Capture",
		.channels_min = 2,
		.channels_max = 4,
		.rates = SNDRV_PCM_RATE_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S24_LE,
	पूर्ण,
पूर्ण,
अणु
	.name  = "Offload0 Pin",
	.id = CATPT_STRM_TYPE_RENDER,
	.ops = &catpt_fe_dai_ops,
	.playback = अणु
		.stream_name = "Offload0 Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_192000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S24_LE,
	पूर्ण,
पूर्ण,
अणु
	.name  = "Offload1 Pin",
	.id = CATPT_STRM_TYPE_RENDER,
	.ops = &catpt_fe_dai_ops,
	.playback = अणु
		.stream_name = "Offload1 Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_192000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S24_LE,
	पूर्ण,
पूर्ण,
अणु
	.name  = "Loopback Pin",
	.id = CATPT_STRM_TYPE_LOOPBACK,
	.ops = &catpt_fe_dai_ops,
	.capture = अणु
		.stream_name = "Loopback Capture",
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S24_LE,
	पूर्ण,
पूर्ण,
अणु
	.name  = "Bluetooth Pin",
	.id = CATPT_STRM_TYPE_BLUETOOTH_RENDER,
	.ops = &catpt_fe_dai_ops,
	.playback = अणु
		.stream_name = "Bluetooth Playback",
		.channels_min = 1,
		.channels_max = 1,
		.rates = SNDRV_PCM_RATE_8000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
	.capture = अणु
		.stream_name = "Bluetooth Capture",
		.channels_min = 1,
		.channels_max = 1,
		.rates = SNDRV_PCM_RATE_8000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
पूर्ण,
/* BE DAIs */
अणु
	.name = "ssp0-port",
	.id = CATPT_SSP_IFACE_0,
	.pcm_new = catpt_dai_pcm_new,
	.playback = अणु
		.channels_min = 1,
		.channels_max = 8,
	पूर्ण,
	.capture = अणु
		.channels_min = 1,
		.channels_max = 8,
	पूर्ण,
पूर्ण,
अणु
	.name = "ssp1-port",
	.id = CATPT_SSP_IFACE_1,
	.pcm_new = catpt_dai_pcm_new,
	.playback = अणु
		.channels_min = 1,
		.channels_max = 8,
	पूर्ण,
	.capture = अणु
		.channels_min = 1,
		.channels_max = 8,
	पूर्ण,
पूर्ण,
पूर्ण;

#घोषणा DSP_VOLUME_MAX		S32_MAX /* 0db */
#घोषणा DSP_VOLUME_STEP_MAX	30

अटल u32 ctlvol_to_dspvol(u32 value)
अणु
	अगर (value > DSP_VOLUME_STEP_MAX)
		value = 0;
	वापस DSP_VOLUME_MAX >> (DSP_VOLUME_STEP_MAX - value);
पूर्ण

अटल u32 dspvol_to_ctlvol(u32 volume)
अणु
	अगर (volume > DSP_VOLUME_MAX)
		वापस DSP_VOLUME_STEP_MAX;
	वापस volume ? __fls(volume) : 0;
पूर्ण

अटल पूर्णांक catpt_set_dspvol(काष्ठा catpt_dev *cdev, u8 stream_id, दीर्घ *ctlvol)
अणु
	u32 dspvol;
	पूर्णांक ret, i;

	क्रम (i = 1; i < CATPT_CHANNELS_MAX; i++)
		अगर (ctlvol[i] != ctlvol[0])
			अवरोध;

	अगर (i == CATPT_CHANNELS_MAX) अणु
		dspvol = ctlvol_to_dspvol(ctlvol[0]);

		ret = catpt_ipc_set_volume(cdev, stream_id,
					   CATPT_ALL_CHANNELS_MASK, dspvol,
					   0, CATPT_AUDIO_CURVE_NONE);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < CATPT_CHANNELS_MAX; i++) अणु
			dspvol = ctlvol_to_dspvol(ctlvol[i]);

			ret = catpt_ipc_set_volume(cdev, stream_id,
						   i, dspvol,
						   0, CATPT_AUDIO_CURVE_NONE);
			अगर (ret)
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (ret)
		वापस CATPT_IPC_ERROR(ret);
	वापस 0;
पूर्ण

अटल पूर्णांक catpt_volume_info(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = CATPT_CHANNELS_MAX;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = DSP_VOLUME_STEP_MAX;
	वापस 0;
पूर्ण

अटल पूर्णांक catpt_mixer_volume_get(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_kcontrol_component(kcontrol);
	काष्ठा catpt_dev *cdev = dev_get_drvdata(component->dev);
	u32 dspvol;
	पूर्णांक i;

	pm_runसमय_get_sync(cdev->dev);

	क्रम (i = 0; i < CATPT_CHANNELS_MAX; i++) अणु
		dspvol = catpt_mixer_volume(cdev, &cdev->mixer, i);
		ucontrol->value.पूर्णांकeger.value[i] = dspvol_to_ctlvol(dspvol);
	पूर्ण

	pm_runसमय_mark_last_busy(cdev->dev);
	pm_runसमय_put_स्वतःsuspend(cdev->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक catpt_mixer_volume_put(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_kcontrol_component(kcontrol);
	काष्ठा catpt_dev *cdev = dev_get_drvdata(component->dev);
	पूर्णांक ret;

	pm_runसमय_get_sync(cdev->dev);

	ret = catpt_set_dspvol(cdev, cdev->mixer.mixer_hw_id,
			       ucontrol->value.पूर्णांकeger.value);

	pm_runसमय_mark_last_busy(cdev->dev);
	pm_runसमय_put_स्वतःsuspend(cdev->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक catpt_stream_volume_get(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol,
				   क्रमागत catpt_pin_id pin_id)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_kcontrol_component(kcontrol);
	काष्ठा catpt_dev *cdev = dev_get_drvdata(component->dev);
	काष्ठा catpt_stream_runसमय *stream;
	दीर्घ *ctlvol = (दीर्घ *)kcontrol->निजी_value;
	u32 dspvol;
	पूर्णांक i;

	stream = catpt_stream_find(cdev, pin_id);
	अगर (!stream) अणु
		क्रम (i = 0; i < CATPT_CHANNELS_MAX; i++)
			ucontrol->value.पूर्णांकeger.value[i] = ctlvol[i];
		वापस 0;
	पूर्ण

	pm_runसमय_get_sync(cdev->dev);

	क्रम (i = 0; i < CATPT_CHANNELS_MAX; i++) अणु
		dspvol = catpt_stream_volume(cdev, stream, i);
		ucontrol->value.पूर्णांकeger.value[i] = dspvol_to_ctlvol(dspvol);
	पूर्ण

	pm_runसमय_mark_last_busy(cdev->dev);
	pm_runसमय_put_स्वतःsuspend(cdev->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक catpt_stream_volume_put(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol,
				   क्रमागत catpt_pin_id pin_id)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_kcontrol_component(kcontrol);
	काष्ठा catpt_dev *cdev = dev_get_drvdata(component->dev);
	काष्ठा catpt_stream_runसमय *stream;
	दीर्घ *ctlvol = (दीर्घ *)kcontrol->निजी_value;
	पूर्णांक ret, i;

	stream = catpt_stream_find(cdev, pin_id);
	अगर (!stream) अणु
		क्रम (i = 0; i < CATPT_CHANNELS_MAX; i++)
			ctlvol[i] = ucontrol->value.पूर्णांकeger.value[i];
		वापस 0;
	पूर्ण

	pm_runसमय_get_sync(cdev->dev);

	ret = catpt_set_dspvol(cdev, stream->info.stream_hw_id,
			       ucontrol->value.पूर्णांकeger.value);

	pm_runसमय_mark_last_busy(cdev->dev);
	pm_runसमय_put_स्वतःsuspend(cdev->dev);

	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < CATPT_CHANNELS_MAX; i++)
		ctlvol[i] = ucontrol->value.पूर्णांकeger.value[i];
	वापस 0;
पूर्ण

अटल पूर्णांक catpt_offload1_volume_get(काष्ठा snd_kcontrol *kctl,
				     काष्ठा snd_ctl_elem_value *uctl)
अणु
	वापस catpt_stream_volume_get(kctl, uctl, CATPT_PIN_ID_OFFLOAD1);
पूर्ण

अटल पूर्णांक catpt_offload1_volume_put(काष्ठा snd_kcontrol *kctl,
				     काष्ठा snd_ctl_elem_value *uctl)
अणु
	वापस catpt_stream_volume_put(kctl, uctl, CATPT_PIN_ID_OFFLOAD1);
पूर्ण

अटल पूर्णांक catpt_offload2_volume_get(काष्ठा snd_kcontrol *kctl,
				     काष्ठा snd_ctl_elem_value *uctl)
अणु
	वापस catpt_stream_volume_get(kctl, uctl, CATPT_PIN_ID_OFFLOAD2);
पूर्ण

अटल पूर्णांक catpt_offload2_volume_put(काष्ठा snd_kcontrol *kctl,
				     काष्ठा snd_ctl_elem_value *uctl)
अणु
	वापस catpt_stream_volume_put(kctl, uctl, CATPT_PIN_ID_OFFLOAD2);
पूर्ण

अटल पूर्णांक catpt_capture_volume_get(काष्ठा snd_kcontrol *kctl,
				    काष्ठा snd_ctl_elem_value *uctl)
अणु
	वापस catpt_stream_volume_get(kctl, uctl, CATPT_PIN_ID_CAPTURE1);
पूर्ण

अटल पूर्णांक catpt_capture_volume_put(काष्ठा snd_kcontrol *kctl,
				    काष्ठा snd_ctl_elem_value *uctl)
अणु
	वापस catpt_stream_volume_put(kctl, uctl, CATPT_PIN_ID_CAPTURE1);
पूर्ण

अटल पूर्णांक catpt_loopback_चयन_get(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.पूर्णांकeger.value[0] = *(bool *)kcontrol->निजी_value;
	वापस 0;
पूर्ण

अटल पूर्णांक catpt_loopback_चयन_put(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_kcontrol_component(kcontrol);
	काष्ठा catpt_dev *cdev = dev_get_drvdata(component->dev);
	काष्ठा catpt_stream_runसमय *stream;
	bool mute;
	पूर्णांक ret;

	mute = (bool)ucontrol->value.पूर्णांकeger.value[0];
	stream = catpt_stream_find(cdev, CATPT_PIN_ID_REFERENCE);
	अगर (!stream) अणु
		*(bool *)kcontrol->निजी_value = mute;
		वापस 0;
	पूर्ण

	pm_runसमय_get_sync(cdev->dev);

	ret = catpt_ipc_mute_loopback(cdev, stream->info.stream_hw_id, mute);

	pm_runसमय_mark_last_busy(cdev->dev);
	pm_runसमय_put_स्वतःsuspend(cdev->dev);

	अगर (ret)
		वापस CATPT_IPC_ERROR(ret);

	*(bool *)kcontrol->निजी_value = mute;
	वापस 0;
पूर्ण

अटल पूर्णांक catpt_waves_चयन_get(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक catpt_waves_चयन_put(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक catpt_waves_param_get(काष्ठा snd_kcontrol *kcontrol,
				 अचिन्हित पूर्णांक __user *bytes,
				 अचिन्हित पूर्णांक size)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक catpt_waves_param_put(काष्ठा snd_kcontrol *kcontrol,
				 स्थिर अचिन्हित पूर्णांक __user *bytes,
				 अचिन्हित पूर्णांक size)
अणु
	वापस 0;
पूर्ण

अटल स्थिर SNDRV_CTL_TLVD_DECLARE_DB_SCALE(catpt_volume_tlv, -9000, 300, 1);

#घोषणा CATPT_VOLUME_CTL(kname, sname) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
	.name = (kname), \
	.access = SNDRV_CTL_ELEM_ACCESS_TLV_READ | \
		  SNDRV_CTL_ELEM_ACCESS_READWRITE, \
	.info = catpt_volume_info, \
	.get = catpt_##sname##_volume_get, \
	.put = catpt_##sname##_volume_put, \
	.tlv.p = catpt_volume_tlv, \
	.निजी_value = (अचिन्हित दीर्घ) \
		&(दीर्घ[CATPT_CHANNELS_MAX]) अणु0पूर्ण पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new component_kcontrols[] = अणु
/* Master volume (mixer stream) */
CATPT_VOLUME_CTL("Master Playback Volume", mixer),
/* Inभागidual volume controls क्रम offload and capture */
CATPT_VOLUME_CTL("Media0 Playback Volume", offload1),
CATPT_VOLUME_CTL("Media1 Playback Volume", offload2),
CATPT_VOLUME_CTL("Mic Capture Volume", capture),
SOC_SINGLE_BOOL_EXT("Loopback Mute", (अचिन्हित दीर्घ)&(bool[1]) अणु0पूर्ण,
		    catpt_loopback_चयन_get, catpt_loopback_चयन_put),
/* Enable or disable WAVES module */
SOC_SINGLE_BOOL_EXT("Waves Switch", 0,
		    catpt_waves_चयन_get, catpt_waves_चयन_put),
/* WAVES module parameter control */
SND_SOC_BYTES_TLV("Waves Set Param", 128,
		  catpt_waves_param_get, catpt_waves_param_put),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget component_widमाला_लो[] = अणु
	SND_SOC_DAPM_AIF_IN("SSP0 CODEC IN", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("SSP0 CODEC OUT", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("SSP1 BT IN", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("SSP1 BT OUT", शून्य, 0, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_MIXER("Playback VMixer", SND_SOC_NOPM, 0, 0, शून्य, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route component_routes[] = अणु
	अणु"Playback VMixer", शून्य, "System Playback"पूर्ण,
	अणु"Playback VMixer", शून्य, "Offload0 Playback"पूर्ण,
	अणु"Playback VMixer", शून्य, "Offload1 Playback"पूर्ण,

	अणु"SSP0 CODEC OUT", शून्य, "Playback VMixer"पूर्ण,

	अणु"Analog Capture", शून्य, "SSP0 CODEC IN"पूर्ण,
	अणु"Loopback Capture", शून्य, "SSP0 CODEC IN"पूर्ण,

	अणु"SSP1 BT OUT", शून्य, "Bluetooth Playback"पूर्ण,
	अणु"Bluetooth Capture", शून्य, "SSP1 BT IN"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver catpt_comp_driver = अणु
	.name = "catpt-platform",

	.pcm_स्थिरruct = catpt_component_pcm_स्थिरruct,
	.खोलो = catpt_component_खोलो,
	.poपूर्णांकer = catpt_component_poपूर्णांकer,

	.controls = component_kcontrols,
	.num_controls = ARRAY_SIZE(component_kcontrols),
	.dapm_widमाला_लो = component_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(component_widमाला_लो),
	.dapm_routes = component_routes,
	.num_dapm_routes = ARRAY_SIZE(component_routes),
पूर्ण;

पूर्णांक catpt_arm_stream_ढाँचाs(काष्ठा catpt_dev *cdev)
अणु
	काष्ठा resource *res;
	u32 scratch_size = 0;
	पूर्णांक i, j;

	क्रम (i = 0; i < ARRAY_SIZE(catpt_topology); i++) अणु
		काष्ठा catpt_stream_ढाँचा *ढाँचा;
		काष्ठा catpt_module_entry *entry;
		काष्ठा catpt_module_type *type;

		ढाँचा = catpt_topology[i];
		ढाँचा->persistent_size = 0;

		क्रम (j = 0; j < ढाँचा->num_entries; j++) अणु
			entry = &ढाँचा->entries[j];
			type = &cdev->modules[entry->module_id];

			अगर (!type->loaded)
				वापस -ENOENT;

			entry->entry_poपूर्णांक = type->entry_poपूर्णांक;
			ढाँचा->persistent_size += type->persistent_size;
			अगर (type->scratch_size > scratch_size)
				scratch_size = type->scratch_size;
		पूर्ण
	पूर्ण

	अगर (scratch_size) अणु
		/* allocate single scratch area क्रम all modules */
		res = catpt_request_region(&cdev->dram, scratch_size);
		अगर (!res)
			वापस -EBUSY;
		cdev->scratch = res;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक catpt_रेजिस्टर_plat_component(काष्ठा catpt_dev *cdev)
अणु
	काष्ठा snd_soc_component *component;
	पूर्णांक ret;

	component = devm_kzalloc(cdev->dev, माप(*component), GFP_KERNEL);
	अगर (!component)
		वापस -ENOMEM;

	ret = snd_soc_component_initialize(component, &catpt_comp_driver,
					   cdev->dev);
	अगर (ret)
		वापस ret;

	component->name = catpt_comp_driver.name;
	वापस snd_soc_add_component(component, dai_drivers,
				     ARRAY_SIZE(dai_drivers));
पूर्ण
