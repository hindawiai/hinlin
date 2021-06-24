<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * virtio-snd: Virtio sound device
 * Copyright (C) 2021 OpenSynergy GmbH
 */
#समावेश <linux/virtio_config.h>

#समावेश "virtio_card.h"

/* VirtIO->ALSA channel position map */
अटल स्थिर u8 g_v2a_position_map[] = अणु
	[VIRTIO_SND_CHMAP_NONE] = SNDRV_CHMAP_UNKNOWN,
	[VIRTIO_SND_CHMAP_NA] = SNDRV_CHMAP_NA,
	[VIRTIO_SND_CHMAP_MONO] = SNDRV_CHMAP_MONO,
	[VIRTIO_SND_CHMAP_FL] = SNDRV_CHMAP_FL,
	[VIRTIO_SND_CHMAP_FR] = SNDRV_CHMAP_FR,
	[VIRTIO_SND_CHMAP_RL] = SNDRV_CHMAP_RL,
	[VIRTIO_SND_CHMAP_RR] = SNDRV_CHMAP_RR,
	[VIRTIO_SND_CHMAP_FC] = SNDRV_CHMAP_FC,
	[VIRTIO_SND_CHMAP_LFE] = SNDRV_CHMAP_LFE,
	[VIRTIO_SND_CHMAP_SL] = SNDRV_CHMAP_SL,
	[VIRTIO_SND_CHMAP_SR] = SNDRV_CHMAP_SR,
	[VIRTIO_SND_CHMAP_RC] = SNDRV_CHMAP_RC,
	[VIRTIO_SND_CHMAP_FLC] = SNDRV_CHMAP_FLC,
	[VIRTIO_SND_CHMAP_FRC] = SNDRV_CHMAP_FRC,
	[VIRTIO_SND_CHMAP_RLC] = SNDRV_CHMAP_RLC,
	[VIRTIO_SND_CHMAP_RRC] = SNDRV_CHMAP_RRC,
	[VIRTIO_SND_CHMAP_FLW] = SNDRV_CHMAP_FLW,
	[VIRTIO_SND_CHMAP_FRW] = SNDRV_CHMAP_FRW,
	[VIRTIO_SND_CHMAP_FLH] = SNDRV_CHMAP_FLH,
	[VIRTIO_SND_CHMAP_FCH] = SNDRV_CHMAP_FCH,
	[VIRTIO_SND_CHMAP_FRH] = SNDRV_CHMAP_FRH,
	[VIRTIO_SND_CHMAP_TC] = SNDRV_CHMAP_TC,
	[VIRTIO_SND_CHMAP_TFL] = SNDRV_CHMAP_TFL,
	[VIRTIO_SND_CHMAP_TFR] = SNDRV_CHMAP_TFR,
	[VIRTIO_SND_CHMAP_TFC] = SNDRV_CHMAP_TFC,
	[VIRTIO_SND_CHMAP_TRL] = SNDRV_CHMAP_TRL,
	[VIRTIO_SND_CHMAP_TRR] = SNDRV_CHMAP_TRR,
	[VIRTIO_SND_CHMAP_TRC] = SNDRV_CHMAP_TRC,
	[VIRTIO_SND_CHMAP_TFLC] = SNDRV_CHMAP_TFLC,
	[VIRTIO_SND_CHMAP_TFRC] = SNDRV_CHMAP_TFRC,
	[VIRTIO_SND_CHMAP_TSL] = SNDRV_CHMAP_TSL,
	[VIRTIO_SND_CHMAP_TSR] = SNDRV_CHMAP_TSR,
	[VIRTIO_SND_CHMAP_LLFE] = SNDRV_CHMAP_LLFE,
	[VIRTIO_SND_CHMAP_RLFE] = SNDRV_CHMAP_RLFE,
	[VIRTIO_SND_CHMAP_BC] = SNDRV_CHMAP_BC,
	[VIRTIO_SND_CHMAP_BLC] = SNDRV_CHMAP_BLC,
	[VIRTIO_SND_CHMAP_BRC] = SNDRV_CHMAP_BRC
पूर्ण;

/**
 * virtsnd_chmap_parse_cfg() - Parse the channel map configuration.
 * @snd: VirtIO sound device.
 *
 * This function is called during initial device initialization.
 *
 * Context: Any context that permits to sleep.
 * Return: 0 on success, -त्रुटि_सं on failure.
 */
पूर्णांक virtsnd_chmap_parse_cfg(काष्ठा virtio_snd *snd)
अणु
	काष्ठा virtio_device *vdev = snd->vdev;
	u32 i;
	पूर्णांक rc;

	virtio_cपढ़ो_le(vdev, काष्ठा virtio_snd_config, chmaps, &snd->nchmaps);
	अगर (!snd->nchmaps)
		वापस 0;

	snd->chmaps = devm_kसुस्मृति(&vdev->dev, snd->nchmaps,
				   माप(*snd->chmaps), GFP_KERNEL);
	अगर (!snd->chmaps)
		वापस -ENOMEM;

	rc = virtsnd_ctl_query_info(snd, VIRTIO_SND_R_CHMAP_INFO, 0,
				    snd->nchmaps, माप(*snd->chmaps),
				    snd->chmaps);
	अगर (rc)
		वापस rc;

	/* Count the number of channel maps per each PCM device/stream. */
	क्रम (i = 0; i < snd->nchmaps; ++i) अणु
		काष्ठा virtio_snd_chmap_info *info = &snd->chmaps[i];
		u32 nid = le32_to_cpu(info->hdr.hda_fn_nid);
		काष्ठा virtio_pcm *vpcm;
		काष्ठा virtio_pcm_stream *vs;

		vpcm = virtsnd_pcm_find_or_create(snd, nid);
		अगर (IS_ERR(vpcm))
			वापस PTR_ERR(vpcm);

		चयन (info->direction) अणु
		हाल VIRTIO_SND_D_OUTPUT:
			vs = &vpcm->streams[SNDRV_PCM_STREAM_PLAYBACK];
			अवरोध;
		हाल VIRTIO_SND_D_INPUT:
			vs = &vpcm->streams[SNDRV_PCM_STREAM_CAPTURE];
			अवरोध;
		शेष:
			dev_err(&vdev->dev,
				"chmap #%u: unknown direction (%u)\n", i,
				info->direction);
			वापस -EINVAL;
		पूर्ण

		vs->nchmaps++;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * virtsnd_chmap_add_ctls() - Create an ALSA control क्रम channel maps.
 * @pcm: ALSA PCM device.
 * @direction: PCM stream direction (SNDRV_PCM_STREAM_XXX).
 * @vs: VirtIO PCM stream.
 *
 * Context: Any context.
 * Return: 0 on success, -त्रुटि_सं on failure.
 */
अटल पूर्णांक virtsnd_chmap_add_ctls(काष्ठा snd_pcm *pcm, पूर्णांक direction,
				  काष्ठा virtio_pcm_stream *vs)
अणु
	u32 i;
	पूर्णांक max_channels = 0;

	क्रम (i = 0; i < vs->nchmaps; i++)
		अगर (max_channels < vs->chmaps[i].channels)
			max_channels = vs->chmaps[i].channels;

	वापस snd_pcm_add_chmap_ctls(pcm, direction, vs->chmaps, max_channels,
				      0, शून्य);
पूर्ण

/**
 * virtsnd_chmap_build_devs() - Build ALSA controls क्रम channel maps.
 * @snd: VirtIO sound device.
 *
 * Context: Any context.
 * Return: 0 on success, -त्रुटि_सं on failure.
 */
पूर्णांक virtsnd_chmap_build_devs(काष्ठा virtio_snd *snd)
अणु
	काष्ठा virtio_device *vdev = snd->vdev;
	काष्ठा virtio_pcm *vpcm;
	काष्ठा virtio_pcm_stream *vs;
	u32 i;
	पूर्णांक rc;

	/* Allocate channel map elements per each PCM device/stream. */
	list_क्रम_each_entry(vpcm, &snd->pcm_list, list) अणु
		क्रम (i = 0; i < ARRAY_SIZE(vpcm->streams); ++i) अणु
			vs = &vpcm->streams[i];

			अगर (!vs->nchmaps)
				जारी;

			vs->chmaps = devm_kसुस्मृति(&vdev->dev, vs->nchmaps + 1,
						  माप(*vs->chmaps),
						  GFP_KERNEL);
			अगर (!vs->chmaps)
				वापस -ENOMEM;

			vs->nchmaps = 0;
		पूर्ण
	पूर्ण

	/* Initialize channel maps per each PCM device/stream. */
	क्रम (i = 0; i < snd->nchmaps; ++i) अणु
		काष्ठा virtio_snd_chmap_info *info = &snd->chmaps[i];
		अचिन्हित पूर्णांक channels = info->channels;
		अचिन्हित पूर्णांक ch;
		काष्ठा snd_pcm_chmap_elem *chmap;

		vpcm = virtsnd_pcm_find(snd, le32_to_cpu(info->hdr.hda_fn_nid));
		अगर (IS_ERR(vpcm))
			वापस PTR_ERR(vpcm);

		अगर (info->direction == VIRTIO_SND_D_OUTPUT)
			vs = &vpcm->streams[SNDRV_PCM_STREAM_PLAYBACK];
		अन्यथा
			vs = &vpcm->streams[SNDRV_PCM_STREAM_CAPTURE];

		chmap = &vs->chmaps[vs->nchmaps++];

		अगर (channels > ARRAY_SIZE(chmap->map))
			channels = ARRAY_SIZE(chmap->map);

		chmap->channels = channels;

		क्रम (ch = 0; ch < channels; ++ch) अणु
			u8 position = info->positions[ch];

			अगर (position >= ARRAY_SIZE(g_v2a_position_map))
				वापस -EINVAL;

			chmap->map[ch] = g_v2a_position_map[position];
		पूर्ण
	पूर्ण

	/* Create an ALSA control per each PCM device/stream. */
	list_क्रम_each_entry(vpcm, &snd->pcm_list, list) अणु
		अगर (!vpcm->pcm)
			जारी;

		क्रम (i = 0; i < ARRAY_SIZE(vpcm->streams); ++i) अणु
			vs = &vpcm->streams[i];

			अगर (!vs->nchmaps)
				जारी;

			rc = virtsnd_chmap_add_ctls(vpcm->pcm, i, vs);
			अगर (rc)
				वापस rc;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
