<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
//
// Copyright(c) 2019 Intel Corporation. All rights reserved.

#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>
#समावेश <sound/hda_codec.h>
#समावेश <sound/hda_i915.h>
#समावेश "../../codecs/hdac_hda.h"

#समावेश "hda_dsp_common.h"

#अगर IS_ENABLED(CONFIG_SND_SOC_SOF_HDA_AUDIO_CODEC)

/*
 * Search card topology and वापस PCM device number
 * matching Nth HDMI device (zero-based index).
 */
अटल काष्ठा snd_pcm *hda_dsp_hdmi_pcm_handle(काष्ठा snd_soc_card *card,
					       पूर्णांक hdmi_idx)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd;
	काष्ठा snd_pcm *spcm;
	पूर्णांक i = 0;

	क्रम_each_card_rtds(card, rtd) अणु
		spcm = rtd->pcm ?
			rtd->pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].pcm : शून्य;
		अगर (spcm && म_माला(spcm->id, "HDMI")) अणु
			अगर (i == hdmi_idx)
				वापस rtd->pcm;
			++i;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * Search card topology and रेजिस्टर HDMI PCM related controls
 * to codec driver.
 */
पूर्णांक hda_dsp_hdmi_build_controls(काष्ठा snd_soc_card *card,
				काष्ठा snd_soc_component *comp)
अणु
	काष्ठा hdac_hda_priv *hda_pvt;
	काष्ठा hda_codec *hcodec;
	काष्ठा snd_pcm *spcm;
	काष्ठा hda_pcm *hpcm;
	पूर्णांक err = 0, i = 0;

	अगर (!comp)
		वापस -EINVAL;

	hda_pvt = snd_soc_component_get_drvdata(comp);
	hcodec = &hda_pvt->codec;

	list_क्रम_each_entry(hpcm, &hcodec->pcm_list_head, list) अणु
		spcm = hda_dsp_hdmi_pcm_handle(card, i);
		अगर (spcm) अणु
			hpcm->pcm = spcm;
			hpcm->device = spcm->device;
			dev_dbg(card->dev,
				"%s: mapping HDMI converter %d to PCM %d (%p)\n",
				__func__, i, hpcm->device, spcm);
		पूर्ण अन्यथा अणु
			hpcm->pcm = शून्य;
			hpcm->device = SNDRV_PCM_INVALID_DEVICE;
			dev_warn(card->dev,
				 "%s: no PCM in topology for HDMI converter %d\n\n",
				 __func__, i);
		पूर्ण
		i++;
	पूर्ण
	snd_hdac_display_घातer(hcodec->core.bus,
			       HDA_CODEC_IDX_CONTROLLER, true);
	err = snd_hda_codec_build_controls(hcodec);
	अगर (err < 0)
		dev_err(card->dev, "unable to create controls %d\n", err);
	snd_hdac_display_घातer(hcodec->core.bus,
			       HDA_CODEC_IDX_CONTROLLER, false);

	वापस err;
पूर्ण

#पूर्ण_अगर
