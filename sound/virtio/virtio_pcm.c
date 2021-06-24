<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * virtio-snd: Virtio sound device
 * Copyright (C) 2021 OpenSynergy GmbH
 */
#समावेश <linux/moduleparam.h>
#समावेश <linux/virtio_config.h>

#समावेश "virtio_card.h"

अटल u32 pcm_buffer_ms = 160;
module_param(pcm_buffer_ms, uपूर्णांक, 0644);
MODULE_PARM_DESC(pcm_buffer_ms, "PCM substream buffer time in milliseconds");

अटल u32 pcm_periods_min = 2;
module_param(pcm_periods_min, uपूर्णांक, 0644);
MODULE_PARM_DESC(pcm_periods_min, "Minimum number of PCM periods");

अटल u32 pcm_periods_max = 16;
module_param(pcm_periods_max, uपूर्णांक, 0644);
MODULE_PARM_DESC(pcm_periods_max, "Maximum number of PCM periods");

अटल u32 pcm_period_ms_min = 10;
module_param(pcm_period_ms_min, uपूर्णांक, 0644);
MODULE_PARM_DESC(pcm_period_ms_min, "Minimum PCM period time in milliseconds");

अटल u32 pcm_period_ms_max = 80;
module_param(pcm_period_ms_max, uपूर्णांक, 0644);
MODULE_PARM_DESC(pcm_period_ms_max, "Maximum PCM period time in milliseconds");

/* Map क्रम converting VirtIO क्रमmat to ALSA क्रमmat. */
अटल स्थिर snd_pcm_क्रमmat_t g_v2a_क्रमmat_map[] = अणु
	[VIRTIO_SND_PCM_FMT_IMA_ADPCM] = SNDRV_PCM_FORMAT_IMA_ADPCM,
	[VIRTIO_SND_PCM_FMT_MU_LAW] = SNDRV_PCM_FORMAT_MU_LAW,
	[VIRTIO_SND_PCM_FMT_A_LAW] = SNDRV_PCM_FORMAT_A_LAW,
	[VIRTIO_SND_PCM_FMT_S8] = SNDRV_PCM_FORMAT_S8,
	[VIRTIO_SND_PCM_FMT_U8] = SNDRV_PCM_FORMAT_U8,
	[VIRTIO_SND_PCM_FMT_S16] = SNDRV_PCM_FORMAT_S16_LE,
	[VIRTIO_SND_PCM_FMT_U16] = SNDRV_PCM_FORMAT_U16_LE,
	[VIRTIO_SND_PCM_FMT_S18_3] = SNDRV_PCM_FORMAT_S18_3LE,
	[VIRTIO_SND_PCM_FMT_U18_3] = SNDRV_PCM_FORMAT_U18_3LE,
	[VIRTIO_SND_PCM_FMT_S20_3] = SNDRV_PCM_FORMAT_S20_3LE,
	[VIRTIO_SND_PCM_FMT_U20_3] = SNDRV_PCM_FORMAT_U20_3LE,
	[VIRTIO_SND_PCM_FMT_S24_3] = SNDRV_PCM_FORMAT_S24_3LE,
	[VIRTIO_SND_PCM_FMT_U24_3] = SNDRV_PCM_FORMAT_U24_3LE,
	[VIRTIO_SND_PCM_FMT_S20] = SNDRV_PCM_FORMAT_S20_LE,
	[VIRTIO_SND_PCM_FMT_U20] = SNDRV_PCM_FORMAT_U20_LE,
	[VIRTIO_SND_PCM_FMT_S24] = SNDRV_PCM_FORMAT_S24_LE,
	[VIRTIO_SND_PCM_FMT_U24] = SNDRV_PCM_FORMAT_U24_LE,
	[VIRTIO_SND_PCM_FMT_S32] = SNDRV_PCM_FORMAT_S32_LE,
	[VIRTIO_SND_PCM_FMT_U32] = SNDRV_PCM_FORMAT_U32_LE,
	[VIRTIO_SND_PCM_FMT_FLOAT] = SNDRV_PCM_FORMAT_FLOAT_LE,
	[VIRTIO_SND_PCM_FMT_FLOAT64] = SNDRV_PCM_FORMAT_FLOAT64_LE,
	[VIRTIO_SND_PCM_FMT_DSD_U8] = SNDRV_PCM_FORMAT_DSD_U8,
	[VIRTIO_SND_PCM_FMT_DSD_U16] = SNDRV_PCM_FORMAT_DSD_U16_LE,
	[VIRTIO_SND_PCM_FMT_DSD_U32] = SNDRV_PCM_FORMAT_DSD_U32_LE,
	[VIRTIO_SND_PCM_FMT_IEC958_SUBFRAME] =
		SNDRV_PCM_FORMAT_IEC958_SUBFRAME_LE
पूर्ण;

/* Map क्रम converting VirtIO frame rate to ALSA frame rate. */
काष्ठा virtsnd_v2a_rate अणु
	अचिन्हित पूर्णांक alsa_bit;
	अचिन्हित पूर्णांक rate;
पूर्ण;

अटल स्थिर काष्ठा virtsnd_v2a_rate g_v2a_rate_map[] = अणु
	[VIRTIO_SND_PCM_RATE_5512] = अणु SNDRV_PCM_RATE_5512, 5512 पूर्ण,
	[VIRTIO_SND_PCM_RATE_8000] = अणु SNDRV_PCM_RATE_8000, 8000 पूर्ण,
	[VIRTIO_SND_PCM_RATE_11025] = अणु SNDRV_PCM_RATE_11025, 11025 पूर्ण,
	[VIRTIO_SND_PCM_RATE_16000] = अणु SNDRV_PCM_RATE_16000, 16000 पूर्ण,
	[VIRTIO_SND_PCM_RATE_22050] = अणु SNDRV_PCM_RATE_22050, 22050 पूर्ण,
	[VIRTIO_SND_PCM_RATE_32000] = अणु SNDRV_PCM_RATE_32000, 32000 पूर्ण,
	[VIRTIO_SND_PCM_RATE_44100] = अणु SNDRV_PCM_RATE_44100, 44100 पूर्ण,
	[VIRTIO_SND_PCM_RATE_48000] = अणु SNDRV_PCM_RATE_48000, 48000 पूर्ण,
	[VIRTIO_SND_PCM_RATE_64000] = अणु SNDRV_PCM_RATE_64000, 64000 पूर्ण,
	[VIRTIO_SND_PCM_RATE_88200] = अणु SNDRV_PCM_RATE_88200, 88200 पूर्ण,
	[VIRTIO_SND_PCM_RATE_96000] = अणु SNDRV_PCM_RATE_96000, 96000 पूर्ण,
	[VIRTIO_SND_PCM_RATE_176400] = अणु SNDRV_PCM_RATE_176400, 176400 पूर्ण,
	[VIRTIO_SND_PCM_RATE_192000] = अणु SNDRV_PCM_RATE_192000, 192000 पूर्ण
पूर्ण;

/**
 * virtsnd_pcm_build_hw() - Parse substream config and build HW descriptor.
 * @vss: VirtIO substream.
 * @info: VirtIO substream inक्रमmation entry.
 *
 * Context: Any context.
 * Return: 0 on success, -EINVAL अगर configuration is invalid.
 */
अटल पूर्णांक virtsnd_pcm_build_hw(काष्ठा virtio_pcm_substream *vss,
				काष्ठा virtio_snd_pcm_info *info)
अणु
	काष्ठा virtio_device *vdev = vss->snd->vdev;
	अचिन्हित पूर्णांक i;
	u64 values;
	माप_प्रकार sample_max = 0;
	माप_प्रकार sample_min = 0;

	vss->features = le32_to_cpu(info->features);

	/*
	 * TODO: set SNDRV_PCM_INFO_अणुBATCH,BLOCK_TRANSFERपूर्ण अगर device supports
	 * only message-based transport.
	 */
	vss->hw.info =
		SNDRV_PCM_INFO_MMAP |
		SNDRV_PCM_INFO_MMAP_VALID |
		SNDRV_PCM_INFO_BATCH |
		SNDRV_PCM_INFO_BLOCK_TRANSFER |
		SNDRV_PCM_INFO_INTERLEAVED |
		SNDRV_PCM_INFO_PAUSE;

	अगर (!info->channels_min || info->channels_min > info->channels_max) अणु
		dev_err(&vdev->dev,
			"SID %u: invalid channel range [%u %u]\n",
			vss->sid, info->channels_min, info->channels_max);
		वापस -EINVAL;
	पूर्ण

	vss->hw.channels_min = info->channels_min;
	vss->hw.channels_max = info->channels_max;

	values = le64_to_cpu(info->क्रमmats);

	vss->hw.क्रमmats = 0;

	क्रम (i = 0; i < ARRAY_SIZE(g_v2a_क्रमmat_map); ++i)
		अगर (values & (1ULL << i)) अणु
			snd_pcm_क्रमmat_t alsa_fmt = g_v2a_क्रमmat_map[i];
			पूर्णांक bytes = snd_pcm_क्रमmat_physical_width(alsa_fmt) / 8;

			अगर (!sample_min || sample_min > bytes)
				sample_min = bytes;

			अगर (sample_max < bytes)
				sample_max = bytes;

			vss->hw.क्रमmats |= pcm_क्रमmat_to_bits(alsa_fmt);
		पूर्ण

	अगर (!vss->hw.क्रमmats) अणु
		dev_err(&vdev->dev,
			"SID %u: no supported PCM sample formats found\n",
			vss->sid);
		वापस -EINVAL;
	पूर्ण

	values = le64_to_cpu(info->rates);

	vss->hw.rates = 0;

	क्रम (i = 0; i < ARRAY_SIZE(g_v2a_rate_map); ++i)
		अगर (values & (1ULL << i)) अणु
			अगर (!vss->hw.rate_min ||
			    vss->hw.rate_min > g_v2a_rate_map[i].rate)
				vss->hw.rate_min = g_v2a_rate_map[i].rate;

			अगर (vss->hw.rate_max < g_v2a_rate_map[i].rate)
				vss->hw.rate_max = g_v2a_rate_map[i].rate;

			vss->hw.rates |= g_v2a_rate_map[i].alsa_bit;
		पूर्ण

	अगर (!vss->hw.rates) अणु
		dev_err(&vdev->dev,
			"SID %u: no supported PCM frame rates found\n",
			vss->sid);
		वापस -EINVAL;
	पूर्ण

	vss->hw.periods_min = pcm_periods_min;
	vss->hw.periods_max = pcm_periods_max;

	/*
	 * We must ensure that there is enough space in the buffer to store
	 * pcm_buffer_ms ms क्रम the combination (Cmax, Smax, Rmax), where:
	 *   Cmax = maximum supported number of channels,
	 *   Smax = maximum supported sample size in bytes,
	 *   Rmax = maximum supported frame rate.
	 */
	vss->hw.buffer_bytes_max =
		PAGE_ALIGN(sample_max * vss->hw.channels_max * pcm_buffer_ms *
			   (vss->hw.rate_max / MSEC_PER_SEC));

	/*
	 * We must ensure that the minimum period size is enough to store
	 * pcm_period_ms_min ms क्रम the combination (Cmin, Smin, Rmin), where:
	 *   Cmin = minimum supported number of channels,
	 *   Smin = minimum supported sample size in bytes,
	 *   Rmin = minimum supported frame rate.
	 */
	vss->hw.period_bytes_min =
		sample_min * vss->hw.channels_min * pcm_period_ms_min *
		(vss->hw.rate_min / MSEC_PER_SEC);

	/*
	 * We must ensure that the maximum period size is enough to store
	 * pcm_period_ms_max ms क्रम the combination (Cmax, Smax, Rmax).
	 */
	vss->hw.period_bytes_max =
		sample_max * vss->hw.channels_max * pcm_period_ms_max *
		(vss->hw.rate_max / MSEC_PER_SEC);

	वापस 0;
पूर्ण

/**
 * virtsnd_pcm_find() - Find the PCM device क्रम the specअगरied node ID.
 * @snd: VirtIO sound device.
 * @nid: Function node ID.
 *
 * Context: Any context.
 * Return: a poपूर्णांकer to the PCM device or ERR_PTR(-ENOENT).
 */
काष्ठा virtio_pcm *virtsnd_pcm_find(काष्ठा virtio_snd *snd, u32 nid)
अणु
	काष्ठा virtio_pcm *vpcm;

	list_क्रम_each_entry(vpcm, &snd->pcm_list, list)
		अगर (vpcm->nid == nid)
			वापस vpcm;

	वापस ERR_PTR(-ENOENT);
पूर्ण

/**
 * virtsnd_pcm_find_or_create() - Find or create the PCM device क्रम the
 *                                specअगरied node ID.
 * @snd: VirtIO sound device.
 * @nid: Function node ID.
 *
 * Context: Any context that permits to sleep.
 * Return: a poपूर्णांकer to the PCM device or ERR_PTR(-त्रुटि_सं).
 */
काष्ठा virtio_pcm *virtsnd_pcm_find_or_create(काष्ठा virtio_snd *snd, u32 nid)
अणु
	काष्ठा virtio_device *vdev = snd->vdev;
	काष्ठा virtio_pcm *vpcm;

	vpcm = virtsnd_pcm_find(snd, nid);
	अगर (!IS_ERR(vpcm))
		वापस vpcm;

	vpcm = devm_kzalloc(&vdev->dev, माप(*vpcm), GFP_KERNEL);
	अगर (!vpcm)
		वापस ERR_PTR(-ENOMEM);

	vpcm->nid = nid;
	list_add_tail(&vpcm->list, &snd->pcm_list);

	वापस vpcm;
पूर्ण

/**
 * virtsnd_pcm_validate() - Validate अगर the device can be started.
 * @vdev: VirtIO parent device.
 *
 * Context: Any context.
 * Return: 0 on success, -EINVAL on failure.
 */
पूर्णांक virtsnd_pcm_validate(काष्ठा virtio_device *vdev)
अणु
	अगर (pcm_periods_min < 2 || pcm_periods_min > pcm_periods_max) अणु
		dev_err(&vdev->dev,
			"invalid range [%u %u] of the number of PCM periods\n",
			pcm_periods_min, pcm_periods_max);
		वापस -EINVAL;
	पूर्ण

	अगर (!pcm_period_ms_min || pcm_period_ms_min > pcm_period_ms_max) अणु
		dev_err(&vdev->dev,
			"invalid range [%u %u] of the size of the PCM period\n",
			pcm_period_ms_min, pcm_period_ms_max);
		वापस -EINVAL;
	पूर्ण

	अगर (pcm_buffer_ms < pcm_periods_min * pcm_period_ms_min) अणु
		dev_err(&vdev->dev,
			"pcm_buffer_ms(=%u) value cannot be < %u ms\n",
			pcm_buffer_ms, pcm_periods_min * pcm_period_ms_min);
		वापस -EINVAL;
	पूर्ण

	अगर (pcm_period_ms_max > pcm_buffer_ms / 2) अणु
		dev_err(&vdev->dev,
			"pcm_period_ms_max(=%u) value cannot be > %u ms\n",
			pcm_period_ms_max, pcm_buffer_ms / 2);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * virtsnd_pcm_period_elapsed() - Kernel work function to handle the elapsed
 *                                period state.
 * @work: Elapsed period work.
 *
 * The मुख्य purpose of this function is to call snd_pcm_period_elapsed() in
 * a process context, not in an पूर्णांकerrupt context. This is necessary because PCM
 * devices operate in non-atomic mode.
 *
 * Context: Process context.
 */
अटल व्योम virtsnd_pcm_period_elapsed(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा virtio_pcm_substream *vss =
		container_of(work, काष्ठा virtio_pcm_substream, elapsed_period);

	snd_pcm_period_elapsed(vss->substream);
पूर्ण

/**
 * virtsnd_pcm_parse_cfg() - Parse the stream configuration.
 * @snd: VirtIO sound device.
 *
 * This function is called during initial device initialization.
 *
 * Context: Any context that permits to sleep.
 * Return: 0 on success, -त्रुटि_सं on failure.
 */
पूर्णांक virtsnd_pcm_parse_cfg(काष्ठा virtio_snd *snd)
अणु
	काष्ठा virtio_device *vdev = snd->vdev;
	काष्ठा virtio_snd_pcm_info *info;
	u32 i;
	पूर्णांक rc;

	virtio_cपढ़ो_le(vdev, काष्ठा virtio_snd_config, streams,
			&snd->nsubstreams);
	अगर (!snd->nsubstreams)
		वापस 0;

	snd->substreams = devm_kसुस्मृति(&vdev->dev, snd->nsubstreams,
				       माप(*snd->substreams), GFP_KERNEL);
	अगर (!snd->substreams)
		वापस -ENOMEM;

	info = kसुस्मृति(snd->nsubstreams, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	rc = virtsnd_ctl_query_info(snd, VIRTIO_SND_R_PCM_INFO, 0,
				    snd->nsubstreams, माप(*info), info);
	अगर (rc)
		जाओ on_निकास;

	क्रम (i = 0; i < snd->nsubstreams; ++i) अणु
		काष्ठा virtio_pcm_substream *vss = &snd->substreams[i];
		काष्ठा virtio_pcm *vpcm;

		vss->snd = snd;
		vss->sid = i;
		INIT_WORK(&vss->elapsed_period, virtsnd_pcm_period_elapsed);
		init_रुकोqueue_head(&vss->msg_empty);
		spin_lock_init(&vss->lock);

		rc = virtsnd_pcm_build_hw(vss, &info[i]);
		अगर (rc)
			जाओ on_निकास;

		vss->nid = le32_to_cpu(info[i].hdr.hda_fn_nid);

		vpcm = virtsnd_pcm_find_or_create(snd, vss->nid);
		अगर (IS_ERR(vpcm)) अणु
			rc = PTR_ERR(vpcm);
			जाओ on_निकास;
		पूर्ण

		चयन (info[i].direction) अणु
		हाल VIRTIO_SND_D_OUTPUT:
			vss->direction = SNDRV_PCM_STREAM_PLAYBACK;
			अवरोध;
		हाल VIRTIO_SND_D_INPUT:
			vss->direction = SNDRV_PCM_STREAM_CAPTURE;
			अवरोध;
		शेष:
			dev_err(&vdev->dev, "SID %u: unknown direction (%u)\n",
				vss->sid, info[i].direction);
			rc = -EINVAL;
			जाओ on_निकास;
		पूर्ण

		vpcm->streams[vss->direction].nsubstreams++;
	पूर्ण

on_निकास:
	kमुक्त(info);

	वापस rc;
पूर्ण

/**
 * virtsnd_pcm_build_devs() - Build ALSA PCM devices.
 * @snd: VirtIO sound device.
 *
 * Context: Any context that permits to sleep.
 * Return: 0 on success, -त्रुटि_सं on failure.
 */
पूर्णांक virtsnd_pcm_build_devs(काष्ठा virtio_snd *snd)
अणु
	काष्ठा virtio_device *vdev = snd->vdev;
	काष्ठा virtio_pcm *vpcm;
	u32 i;
	पूर्णांक rc;

	list_क्रम_each_entry(vpcm, &snd->pcm_list, list) अणु
		अचिन्हित पूर्णांक npbs =
			vpcm->streams[SNDRV_PCM_STREAM_PLAYBACK].nsubstreams;
		अचिन्हित पूर्णांक ncps =
			vpcm->streams[SNDRV_PCM_STREAM_CAPTURE].nsubstreams;

		अगर (!npbs && !ncps)
			जारी;

		rc = snd_pcm_new(snd->card, VIRTIO_SND_CARD_DRIVER, vpcm->nid,
				 npbs, ncps, &vpcm->pcm);
		अगर (rc) अणु
			dev_err(&vdev->dev, "snd_pcm_new[%u] failed: %d\n",
				vpcm->nid, rc);
			वापस rc;
		पूर्ण

		vpcm->pcm->info_flags = 0;
		vpcm->pcm->dev_class = SNDRV_PCM_CLASS_GENERIC;
		vpcm->pcm->dev_subclass = SNDRV_PCM_SUBCLASS_GENERIC_MIX;
		snम_लिखो(vpcm->pcm->name, माप(vpcm->pcm->name),
			 VIRTIO_SND_PCM_NAME " %u", vpcm->pcm->device);
		vpcm->pcm->निजी_data = vpcm;
		vpcm->pcm->nonatomic = true;

		क्रम (i = 0; i < ARRAY_SIZE(vpcm->streams); ++i) अणु
			काष्ठा virtio_pcm_stream *stream = &vpcm->streams[i];

			अगर (!stream->nsubstreams)
				जारी;

			stream->substreams =
				devm_kसुस्मृति(&vdev->dev, stream->nsubstreams,
					     माप(*stream->substreams),
					     GFP_KERNEL);
			अगर (!stream->substreams)
				वापस -ENOMEM;

			stream->nsubstreams = 0;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < snd->nsubstreams; ++i) अणु
		काष्ठा virtio_pcm_stream *vs;
		काष्ठा virtio_pcm_substream *vss = &snd->substreams[i];

		vpcm = virtsnd_pcm_find(snd, vss->nid);
		अगर (IS_ERR(vpcm))
			वापस PTR_ERR(vpcm);

		vs = &vpcm->streams[vss->direction];
		vs->substreams[vs->nsubstreams++] = vss;
	पूर्ण

	list_क्रम_each_entry(vpcm, &snd->pcm_list, list) अणु
		क्रम (i = 0; i < ARRAY_SIZE(vpcm->streams); ++i) अणु
			काष्ठा virtio_pcm_stream *vs = &vpcm->streams[i];
			काष्ठा snd_pcm_str *ks = &vpcm->pcm->streams[i];
			काष्ठा snd_pcm_substream *kss;

			अगर (!vs->nsubstreams)
				जारी;

			क्रम (kss = ks->substream; kss; kss = kss->next)
				vs->substreams[kss->number]->substream = kss;

			snd_pcm_set_ops(vpcm->pcm, i, &virtsnd_pcm_ops);
		पूर्ण

		snd_pcm_set_managed_buffer_all(vpcm->pcm,
					       SNDRV_DMA_TYPE_VMALLOC, शून्य,
					       0, 0);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * virtsnd_pcm_event() - Handle the PCM device event notअगरication.
 * @snd: VirtIO sound device.
 * @event: VirtIO sound event.
 *
 * Context: Interrupt context.
 */
व्योम virtsnd_pcm_event(काष्ठा virtio_snd *snd, काष्ठा virtio_snd_event *event)
अणु
	काष्ठा virtio_pcm_substream *vss;
	u32 sid = le32_to_cpu(event->data);

	अगर (sid >= snd->nsubstreams)
		वापस;

	vss = &snd->substreams[sid];

	चयन (le32_to_cpu(event->hdr.code)) अणु
	हाल VIRTIO_SND_EVT_PCM_PERIOD_ELAPSED:
		/* TODO: deal with shmem elapsed period */
		अवरोध;
	हाल VIRTIO_SND_EVT_PCM_XRUN:
		spin_lock(&vss->lock);
		अगर (vss->xfer_enabled)
			vss->xfer_xrun = true;
		spin_unlock(&vss->lock);
		अवरोध;
	पूर्ण
पूर्ण
