<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * dw-hdmi-i2s-audio.c
 *
 * Copyright (c) 2017 Renesas Solutions Corp.
 * Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>
 */

#समावेश <linux/dma-mapping.h>
#समावेश <linux/module.h>

#समावेश <drm/bridge/dw_hdmi.h>
#समावेश <drm/drm_crtc.h>

#समावेश <sound/hdmi-codec.h>

#समावेश "dw-hdmi.h"
#समावेश "dw-hdmi-audio.h"

#घोषणा DRIVER_NAME "dw-hdmi-i2s-audio"

अटल अंतरभूत व्योम hdmi_ग_लिखो(काष्ठा dw_hdmi_i2s_audio_data *audio,
			      u8 val, पूर्णांक offset)
अणु
	काष्ठा dw_hdmi *hdmi = audio->hdmi;

	audio->ग_लिखो(hdmi, val, offset);
पूर्ण

अटल अंतरभूत u8 hdmi_पढ़ो(काष्ठा dw_hdmi_i2s_audio_data *audio, पूर्णांक offset)
अणु
	काष्ठा dw_hdmi *hdmi = audio->hdmi;

	वापस audio->पढ़ो(hdmi, offset);
पूर्ण

अटल पूर्णांक dw_hdmi_i2s_hw_params(काष्ठा device *dev, व्योम *data,
				 काष्ठा hdmi_codec_daअगरmt *fmt,
				 काष्ठा hdmi_codec_params *hparms)
अणु
	काष्ठा dw_hdmi_i2s_audio_data *audio = data;
	काष्ठा dw_hdmi *hdmi = audio->hdmi;
	u8 conf0 = 0;
	u8 conf1 = 0;
	u8 inअ_दोlkfs = 0;

	/* it cares I2S only */
	अगर (fmt->bit_clk_master | fmt->frame_clk_master) अणु
		dev_err(dev, "unsupported clock settings\n");
		वापस -EINVAL;
	पूर्ण

	/* Reset the FIFOs beक्रमe applying new params */
	hdmi_ग_लिखो(audio, HDMI_AUD_CONF0_SW_RESET, HDMI_AUD_CONF0);
	hdmi_ग_लिखो(audio, (u8)~HDMI_MC_SWRSTZ_I2SSWRST_REQ, HDMI_MC_SWRSTZ);

	inअ_दोlkfs	= HDMI_AUD_INPUTCLKFS_64FS;
	conf0		= (HDMI_AUD_CONF0_I2S_SELECT | HDMI_AUD_CONF0_I2S_EN0);

	/* Enable the required i2s lanes */
	चयन (hparms->channels) अणु
	हाल 7 ... 8:
		conf0 |= HDMI_AUD_CONF0_I2S_EN3;
		fallthrough;
	हाल 5 ... 6:
		conf0 |= HDMI_AUD_CONF0_I2S_EN2;
		fallthrough;
	हाल 3 ... 4:
		conf0 |= HDMI_AUD_CONF0_I2S_EN1;
		/* Fall-thru */
	पूर्ण

	चयन (hparms->sample_width) अणु
	हाल 16:
		conf1 = HDMI_AUD_CONF1_WIDTH_16;
		अवरोध;
	हाल 24:
	हाल 32:
		conf1 = HDMI_AUD_CONF1_WIDTH_24;
		अवरोध;
	पूर्ण

	चयन (fmt->fmt) अणु
	हाल HDMI_I2S:
		conf1 |= HDMI_AUD_CONF1_MODE_I2S;
		अवरोध;
	हाल HDMI_RIGHT_J:
		conf1 |= HDMI_AUD_CONF1_MODE_RIGHT_J;
		अवरोध;
	हाल HDMI_LEFT_J:
		conf1 |= HDMI_AUD_CONF1_MODE_LEFT_J;
		अवरोध;
	हाल HDMI_DSP_A:
		conf1 |= HDMI_AUD_CONF1_MODE_BURST_1;
		अवरोध;
	हाल HDMI_DSP_B:
		conf1 |= HDMI_AUD_CONF1_MODE_BURST_2;
		अवरोध;
	शेष:
		dev_err(dev, "unsupported format\n");
		वापस -EINVAL;
	पूर्ण

	dw_hdmi_set_sample_rate(hdmi, hparms->sample_rate);
	dw_hdmi_set_channel_status(hdmi, hparms->iec.status);
	dw_hdmi_set_channel_count(hdmi, hparms->channels);
	dw_hdmi_set_channel_allocation(hdmi, hparms->cea.channel_allocation);

	hdmi_ग_लिखो(audio, inअ_दोlkfs, HDMI_AUD_INPUTCLKFS);
	hdmi_ग_लिखो(audio, conf0, HDMI_AUD_CONF0);
	hdmi_ग_लिखो(audio, conf1, HDMI_AUD_CONF1);

	वापस 0;
पूर्ण

अटल पूर्णांक dw_hdmi_i2s_audio_startup(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा dw_hdmi_i2s_audio_data *audio = data;
	काष्ठा dw_hdmi *hdmi = audio->hdmi;

	dw_hdmi_audio_enable(hdmi);

	वापस 0;
पूर्ण

अटल व्योम dw_hdmi_i2s_audio_shutकरोwn(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा dw_hdmi_i2s_audio_data *audio = data;
	काष्ठा dw_hdmi *hdmi = audio->hdmi;

	dw_hdmi_audio_disable(hdmi);
पूर्ण

अटल पूर्णांक dw_hdmi_i2s_get_eld(काष्ठा device *dev, व्योम *data, uपूर्णांक8_t *buf,
			       माप_प्रकार len)
अणु
	काष्ठा dw_hdmi_i2s_audio_data *audio = data;

	स_नकल(buf, audio->eld, min_t(माप_प्रकार, MAX_ELD_BYTES, len));
	वापस 0;
पूर्ण

अटल पूर्णांक dw_hdmi_i2s_get_dai_id(काष्ठा snd_soc_component *component,
				  काष्ठा device_node *endpoपूर्णांक)
अणु
	काष्ठा of_endpoपूर्णांक of_ep;
	पूर्णांक ret;

	ret = of_graph_parse_endpoपूर्णांक(endpoपूर्णांक, &of_ep);
	अगर (ret < 0)
		वापस ret;

	/*
	 * HDMI sound should be located as reg = <2>
	 * Then, it is sound port 0
	 */
	अगर (of_ep.port == 2)
		वापस 0;

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक dw_hdmi_i2s_hook_plugged_cb(काष्ठा device *dev, व्योम *data,
				       hdmi_codec_plugged_cb fn,
				       काष्ठा device *codec_dev)
अणु
	काष्ठा dw_hdmi_i2s_audio_data *audio = data;
	काष्ठा dw_hdmi *hdmi = audio->hdmi;

	वापस dw_hdmi_set_plugged_cb(hdmi, fn, codec_dev);
पूर्ण

अटल स्थिर काष्ठा hdmi_codec_ops dw_hdmi_i2s_ops = अणु
	.hw_params	= dw_hdmi_i2s_hw_params,
	.audio_startup  = dw_hdmi_i2s_audio_startup,
	.audio_shutकरोwn	= dw_hdmi_i2s_audio_shutकरोwn,
	.get_eld	= dw_hdmi_i2s_get_eld,
	.get_dai_id	= dw_hdmi_i2s_get_dai_id,
	.hook_plugged_cb = dw_hdmi_i2s_hook_plugged_cb,
पूर्ण;

अटल पूर्णांक snd_dw_hdmi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dw_hdmi_i2s_audio_data *audio = pdev->dev.platक्रमm_data;
	काष्ठा platक्रमm_device_info pdevinfo;
	काष्ठा hdmi_codec_pdata pdata;
	काष्ठा platक्रमm_device *platक्रमm;

	pdata.ops		= &dw_hdmi_i2s_ops;
	pdata.i2s		= 1;
	pdata.max_i2s_channels	= 8;
	pdata.data		= audio;

	स_रखो(&pdevinfo, 0, माप(pdevinfo));
	pdevinfo.parent		= pdev->dev.parent;
	pdevinfo.id		= PLATFORM_DEVID_AUTO;
	pdevinfo.name		= HDMI_CODEC_DRV_NAME;
	pdevinfo.data		= &pdata;
	pdevinfo.size_data	= माप(pdata);
	pdevinfo.dma_mask	= DMA_BIT_MASK(32);

	platक्रमm = platक्रमm_device_रेजिस्टर_full(&pdevinfo);
	अगर (IS_ERR(platक्रमm))
		वापस PTR_ERR(platक्रमm);

	dev_set_drvdata(&pdev->dev, platक्रमm);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_dw_hdmi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा platक्रमm_device *platक्रमm = dev_get_drvdata(&pdev->dev);

	platक्रमm_device_unरेजिस्टर(platक्रमm);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver snd_dw_hdmi_driver = अणु
	.probe	= snd_dw_hdmi_probe,
	.हटाओ	= snd_dw_hdmi_हटाओ,
	.driver	= अणु
		.name = DRIVER_NAME,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(snd_dw_hdmi_driver);

MODULE_AUTHOR("Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>");
MODULE_DESCRIPTION("Synopsis Designware HDMI I2S ALSA SoC interface");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:" DRIVER_NAME);
