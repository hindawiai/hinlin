<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * omap-hdmi-audio.c -- OMAP4+ DSS HDMI audio support library
 *
 * Copyright (C) 2014 Texas Instruments Incorporated - https://www.ti.com
 *
 * Author: Jyri Sarha <jsarha@ti.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/माला.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <sound/soc.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/dmaengine_pcm.h>
#समावेश <uapi/sound/asound.h>
#समावेश <sound/asoundef.h>
#समावेश <sound/omap-hdmi-audपन.स>

#समावेश "sdma-pcm.h"

#घोषणा DRV_NAME "omap-hdmi-audio"

काष्ठा hdmi_audio_data अणु
	काष्ठा snd_soc_card *card;

	स्थिर काष्ठा omap_hdmi_audio_ops *ops;
	काष्ठा device *dssdev;
	काष्ठा snd_dmaengine_dai_dma_data dma_data;
	काष्ठा omap_dss_audio dss_audio;
	काष्ठा snd_aes_iec958 iec;
	काष्ठा snd_cea_861_aud_अगर cea;

	काष्ठा mutex current_stream_lock;
	काष्ठा snd_pcm_substream *current_stream;
पूर्ण;

अटल
काष्ठा hdmi_audio_data *card_drvdata_substream(काष्ठा snd_pcm_substream *ss)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = ss->निजी_data;

	वापस snd_soc_card_get_drvdata(rtd->card);
पूर्ण

अटल व्योम hdmi_dai_पात(काष्ठा device *dev)
अणु
	काष्ठा hdmi_audio_data *ad = dev_get_drvdata(dev);

	mutex_lock(&ad->current_stream_lock);
	अगर (ad->current_stream && ad->current_stream->runसमय &&
	    snd_pcm_running(ad->current_stream)) अणु
		dev_err(dev, "HDMI display disabled, aborting playback\n");
		snd_pcm_stream_lock_irq(ad->current_stream);
		snd_pcm_stop(ad->current_stream, SNDRV_PCM_STATE_DISCONNECTED);
		snd_pcm_stream_unlock_irq(ad->current_stream);
	पूर्ण
	mutex_unlock(&ad->current_stream_lock);
पूर्ण

अटल पूर्णांक hdmi_dai_startup(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा hdmi_audio_data *ad = card_drvdata_substream(substream);
	पूर्णांक ret;
	/*
	 * Make sure that the period bytes are multiple of the DMA packet size.
	 * Largest packet size we use is 32 32-bit words = 128 bytes
	 */
	ret = snd_pcm_hw_स्थिरraपूर्णांक_step(substream->runसमय, 0,
					 SNDRV_PCM_HW_PARAM_PERIOD_BYTES, 128);
	अगर (ret < 0) अणु
		dev_err(dai->dev, "Could not apply period constraint: %d\n",
			ret);
		वापस ret;
	पूर्ण
	ret = snd_pcm_hw_स्थिरraपूर्णांक_step(substream->runसमय, 0,
					 SNDRV_PCM_HW_PARAM_BUFFER_BYTES, 128);
	अगर (ret < 0) अणु
		dev_err(dai->dev, "Could not apply buffer constraint: %d\n",
			ret);
		वापस ret;
	पूर्ण

	snd_soc_dai_set_dma_data(dai, substream, &ad->dma_data);

	mutex_lock(&ad->current_stream_lock);
	ad->current_stream = substream;
	mutex_unlock(&ad->current_stream_lock);

	ret = ad->ops->audio_startup(ad->dssdev, hdmi_dai_पात);

	अगर (ret) अणु
		mutex_lock(&ad->current_stream_lock);
		ad->current_stream = शून्य;
		mutex_unlock(&ad->current_stream_lock);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक hdmi_dai_hw_params(काष्ठा snd_pcm_substream *substream,
			      काष्ठा snd_pcm_hw_params *params,
			      काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा hdmi_audio_data *ad = card_drvdata_substream(substream);
	काष्ठा snd_aes_iec958 *iec = &ad->iec;
	काष्ठा snd_cea_861_aud_अगर *cea = &ad->cea;

	WARN_ON(ad->current_stream != substream);

	चयन (params_क्रमmat(params)) अणु
	हाल SNDRV_PCM_FORMAT_S16_LE:
		ad->dma_data.maxburst = 16;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S24_LE:
		ad->dma_data.maxburst = 32;
		अवरोध;
	शेष:
		dev_err(dai->dev, "format not supported!\n");
		वापस -EINVAL;
	पूर्ण

	ad->dss_audio.iec = iec;
	ad->dss_audio.cea = cea;
	/*
	 * fill the IEC-60958 channel status word
	 */
	/* initialize the word bytes */
	स_रखो(iec->status, 0, माप(iec->status));

	/* specअगरy IEC-60958-3 (commercial use) */
	iec->status[0] &= ~IEC958_AES0_PROFESSIONAL;

	/* specअगरy that the audio is LPCM*/
	iec->status[0] &= ~IEC958_AES0_NONAUDIO;

	iec->status[0] |= IEC958_AES0_CON_NOT_COPYRIGHT;

	iec->status[0] |= IEC958_AES0_CON_EMPHASIS_NONE;

	iec->status[1] = IEC958_AES1_CON_GENERAL;

	iec->status[2] |= IEC958_AES2_CON_SOURCE_UNSPEC;

	iec->status[2] |= IEC958_AES2_CON_CHANNEL_UNSPEC;

	चयन (params_rate(params)) अणु
	हाल 32000:
		iec->status[3] |= IEC958_AES3_CON_FS_32000;
		अवरोध;
	हाल 44100:
		iec->status[3] |= IEC958_AES3_CON_FS_44100;
		अवरोध;
	हाल 48000:
		iec->status[3] |= IEC958_AES3_CON_FS_48000;
		अवरोध;
	हाल 88200:
		iec->status[3] |= IEC958_AES3_CON_FS_88200;
		अवरोध;
	हाल 96000:
		iec->status[3] |= IEC958_AES3_CON_FS_96000;
		अवरोध;
	हाल 176400:
		iec->status[3] |= IEC958_AES3_CON_FS_176400;
		अवरोध;
	हाल 192000:
		iec->status[3] |= IEC958_AES3_CON_FS_192000;
		अवरोध;
	शेष:
		dev_err(dai->dev, "rate not supported!\n");
		वापस -EINVAL;
	पूर्ण

	/* specअगरy the घड़ी accuracy */
	iec->status[3] |= IEC958_AES3_CON_CLOCK_1000PPM;

	/*
	 * specअगरy the word length. The same word length value can mean
	 * two dअगरferent lengths. Hence, we need to specअगरy the maximum
	 * word length as well.
	 */
	चयन (params_क्रमmat(params)) अणु
	हाल SNDRV_PCM_FORMAT_S16_LE:
		iec->status[4] |= IEC958_AES4_CON_WORDLEN_20_16;
		iec->status[4] &= ~IEC958_AES4_CON_MAX_WORDLEN_24;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S24_LE:
		iec->status[4] |= IEC958_AES4_CON_WORDLEN_24_20;
		iec->status[4] |= IEC958_AES4_CON_MAX_WORDLEN_24;
		अवरोध;
	शेष:
		dev_err(dai->dev, "format not supported!\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Fill the CEA-861 audio infoframe (see spec क्रम details)
	 */

	cea->db1_ct_cc = (params_channels(params) - 1)
		& CEA861_AUDIO_INFOFRAME_DB1CC;
	cea->db1_ct_cc |= CEA861_AUDIO_INFOFRAME_DB1CT_FROM_STREAM;

	cea->db2_sf_ss = CEA861_AUDIO_INFOFRAME_DB2SF_FROM_STREAM;
	cea->db2_sf_ss |= CEA861_AUDIO_INFOFRAME_DB2SS_FROM_STREAM;

	cea->db3 = 0; /* not used, all zeros */

	अगर (params_channels(params) == 2)
		cea->db4_ca = 0x0;
	अन्यथा अगर (params_channels(params) == 6)
		cea->db4_ca = 0xb;
	अन्यथा
		cea->db4_ca = 0x13;

	अगर (cea->db4_ca == 0x00)
		cea->db5_dminh_lsv = CEA861_AUDIO_INFOFRAME_DB5_DM_INH_PERMITTED;
	अन्यथा
		cea->db5_dminh_lsv = CEA861_AUDIO_INFOFRAME_DB5_DM_INH_PROHIBITED;

	/* the expression is trivial but makes clear what we are करोing */
	cea->db5_dminh_lsv |= (0 & CEA861_AUDIO_INFOFRAME_DB5_LSV);

	वापस ad->ops->audio_config(ad->dssdev, &ad->dss_audio);
पूर्ण

अटल पूर्णांक hdmi_dai_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा hdmi_audio_data *ad = card_drvdata_substream(substream);
	पूर्णांक err = 0;

	WARN_ON(ad->current_stream != substream);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		err = ad->ops->audio_start(ad->dssdev);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		ad->ops->audio_stop(ad->dssdev);
		अवरोध;
	शेष:
		err = -EINVAL;
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम hdmi_dai_shutकरोwn(काष्ठा snd_pcm_substream *substream,
			      काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा hdmi_audio_data *ad = card_drvdata_substream(substream);

	WARN_ON(ad->current_stream != substream);

	ad->ops->audio_shutकरोwn(ad->dssdev);

	mutex_lock(&ad->current_stream_lock);
	ad->current_stream = शून्य;
	mutex_unlock(&ad->current_stream_lock);
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops hdmi_dai_ops = अणु
	.startup	= hdmi_dai_startup,
	.hw_params	= hdmi_dai_hw_params,
	.trigger	= hdmi_dai_trigger,
	.shutकरोwn	= hdmi_dai_shutकरोwn,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver omap_hdmi_component = अणु
	.name = "omapdss_hdmi",
पूर्ण;

अटल काष्ठा snd_soc_dai_driver omap5_hdmi_dai = अणु
	.name = "omap5-hdmi-dai",
	.playback = अणु
		.channels_min = 2,
		.channels_max = 8,
		.rates = (SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_44100 |
			  SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_88200 |
			  SNDRV_PCM_RATE_96000 | SNDRV_PCM_RATE_176400 |
			  SNDRV_PCM_RATE_192000),
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
	.ops = &hdmi_dai_ops,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver omap4_hdmi_dai = अणु
	.name = "omap4-hdmi-dai",
	.playback = अणु
		.channels_min = 2,
		.channels_max = 8,
		.rates = (SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_44100 |
			  SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_88200 |
			  SNDRV_PCM_RATE_96000 | SNDRV_PCM_RATE_176400 |
			  SNDRV_PCM_RATE_192000),
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S24_LE,
	पूर्ण,
	.ops = &hdmi_dai_ops,
पूर्ण;

अटल पूर्णांक omap_hdmi_audio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap_hdmi_audio_pdata *ha = pdev->dev.platक्रमm_data;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा hdmi_audio_data *ad;
	काष्ठा snd_soc_dai_driver *dai_drv;
	काष्ठा snd_soc_card *card;
	काष्ठा snd_soc_dai_link_component *compnent;
	पूर्णांक ret;

	अगर (!ha) अणु
		dev_err(dev, "No platform data\n");
		वापस -EINVAL;
	पूर्ण

	ad = devm_kzalloc(dev, माप(*ad), GFP_KERNEL);
	अगर (!ad)
		वापस -ENOMEM;
	ad->dssdev = ha->dev;
	ad->ops = ha->ops;
	ad->dma_data.addr = ha->audio_dma_addr;
	ad->dma_data.filter_data = "audio_tx";
	ad->dma_data.addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	mutex_init(&ad->current_stream_lock);

	चयन (ha->version) अणु
	हाल 4:
		dai_drv = &omap4_hdmi_dai;
		अवरोध;
	हाल 5:
		dai_drv = &omap5_hdmi_dai;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	ret = devm_snd_soc_रेजिस्टर_component(ad->dssdev, &omap_hdmi_component,
					 dai_drv, 1);
	अगर (ret)
		वापस ret;

	ret = sdma_pcm_platक्रमm_रेजिस्टर(ad->dssdev, "audio_tx", शून्य);
	अगर (ret)
		वापस ret;

	card = devm_kzalloc(dev, माप(*card), GFP_KERNEL);
	अगर (!card)
		वापस -ENOMEM;

	card->name = devm_kaप्र_लिखो(dev, GFP_KERNEL,
				    "HDMI %s", dev_name(ad->dssdev));
	अगर (!card->name)
		वापस -ENOMEM;

	card->owner = THIS_MODULE;
	card->dai_link =
		devm_kzalloc(dev, माप(*(card->dai_link)), GFP_KERNEL);
	अगर (!card->dai_link)
		वापस -ENOMEM;

	compnent = devm_kzalloc(dev, 3 * माप(*compnent), GFP_KERNEL);
	अगर (!compnent)
		वापस -ENOMEM;
	card->dai_link->cpus		= &compnent[0];
	card->dai_link->num_cpus	= 1;
	card->dai_link->codecs		= &compnent[1];
	card->dai_link->num_codecs	= 1;
	card->dai_link->platक्रमms	= &compnent[2];
	card->dai_link->num_platक्रमms	= 1;

	card->dai_link->name = card->name;
	card->dai_link->stream_name = card->name;
	card->dai_link->cpus->dai_name = dev_name(ad->dssdev);
	card->dai_link->platक्रमms->name = dev_name(ad->dssdev);
	card->dai_link->codecs->name = "snd-soc-dummy";
	card->dai_link->codecs->dai_name = "snd-soc-dummy-dai";
	card->num_links = 1;
	card->dev = dev;

	ret = snd_soc_रेजिस्टर_card(card);
	अगर (ret) अणु
		dev_err(dev, "snd_soc_register_card failed (%d)\n", ret);
		वापस ret;
	पूर्ण

	ad->card = card;
	snd_soc_card_set_drvdata(card, ad);

	dev_set_drvdata(dev, ad);

	वापस 0;
पूर्ण

अटल पूर्णांक omap_hdmi_audio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hdmi_audio_data *ad = platक्रमm_get_drvdata(pdev);

	snd_soc_unरेजिस्टर_card(ad->card);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver hdmi_audio_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
	पूर्ण,
	.probe = omap_hdmi_audio_probe,
	.हटाओ = omap_hdmi_audio_हटाओ,
पूर्ण;

module_platक्रमm_driver(hdmi_audio_driver);

MODULE_AUTHOR("Jyri Sarha <jsarha@ti.com>");
MODULE_DESCRIPTION("OMAP HDMI Audio Driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRV_NAME);
