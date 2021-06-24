<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Analog Devices ADV7511 HDMI transmitter driver
 *
 * Copyright 2012 Analog Devices Inc.
 * Copyright (c) 2016, Linaro Limited
 */

#समावेश <sound/core.h>
#समावेश <sound/hdmi-codec.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>
#समावेश <linux/of_graph.h>

#समावेश "adv7511.h"

अटल व्योम adv7511_calc_cts_n(अचिन्हित पूर्णांक f_पंचांगds, अचिन्हित पूर्णांक fs,
			       अचिन्हित पूर्णांक *cts, अचिन्हित पूर्णांक *n)
अणु
	चयन (fs) अणु
	हाल 32000:
	हाल 48000:
	हाल 96000:
	हाल 192000:
		*n = fs * 128 / 1000;
		अवरोध;
	हाल 44100:
	हाल 88200:
	हाल 176400:
		*n = fs * 128 / 900;
		अवरोध;
	पूर्ण

	*cts = ((f_पंचांगds * *n) / (128 * fs)) * 1000;
पूर्ण

अटल पूर्णांक adv7511_update_cts_n(काष्ठा adv7511 *adv7511)
अणु
	अचिन्हित पूर्णांक cts = 0;
	अचिन्हित पूर्णांक n = 0;

	adv7511_calc_cts_n(adv7511->f_पंचांगds, adv7511->f_audio, &cts, &n);

	regmap_ग_लिखो(adv7511->regmap, ADV7511_REG_N0, (n >> 16) & 0xf);
	regmap_ग_लिखो(adv7511->regmap, ADV7511_REG_N1, (n >> 8) & 0xff);
	regmap_ग_लिखो(adv7511->regmap, ADV7511_REG_N2, n & 0xff);

	regmap_ग_लिखो(adv7511->regmap, ADV7511_REG_CTS_MANUAL0,
		     (cts >> 16) & 0xf);
	regmap_ग_लिखो(adv7511->regmap, ADV7511_REG_CTS_MANUAL1,
		     (cts >> 8) & 0xff);
	regmap_ग_लिखो(adv7511->regmap, ADV7511_REG_CTS_MANUAL2,
		     cts & 0xff);

	वापस 0;
पूर्ण

अटल पूर्णांक adv7511_hdmi_hw_params(काष्ठा device *dev, व्योम *data,
				  काष्ठा hdmi_codec_daअगरmt *fmt,
				  काष्ठा hdmi_codec_params *hparms)
अणु
	काष्ठा adv7511 *adv7511 = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक audio_source, i2s_क्रमmat = 0;
	अचिन्हित पूर्णांक invert_घड़ी;
	अचिन्हित पूर्णांक rate;
	अचिन्हित पूर्णांक len;

	चयन (hparms->sample_rate) अणु
	हाल 32000:
		rate = ADV7511_SAMPLE_FREQ_32000;
		अवरोध;
	हाल 44100:
		rate = ADV7511_SAMPLE_FREQ_44100;
		अवरोध;
	हाल 48000:
		rate = ADV7511_SAMPLE_FREQ_48000;
		अवरोध;
	हाल 88200:
		rate = ADV7511_SAMPLE_FREQ_88200;
		अवरोध;
	हाल 96000:
		rate = ADV7511_SAMPLE_FREQ_96000;
		अवरोध;
	हाल 176400:
		rate = ADV7511_SAMPLE_FREQ_176400;
		अवरोध;
	हाल 192000:
		rate = ADV7511_SAMPLE_FREQ_192000;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (hparms->sample_width) अणु
	हाल 16:
		len = ADV7511_I2S_SAMPLE_LEN_16;
		अवरोध;
	हाल 18:
		len = ADV7511_I2S_SAMPLE_LEN_18;
		अवरोध;
	हाल 20:
		len = ADV7511_I2S_SAMPLE_LEN_20;
		अवरोध;
	हाल 24:
		len = ADV7511_I2S_SAMPLE_LEN_24;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt->fmt) अणु
	हाल HDMI_I2S:
		audio_source = ADV7511_AUDIO_SOURCE_I2S;
		i2s_क्रमmat = ADV7511_I2S_FORMAT_I2S;
		अवरोध;
	हाल HDMI_RIGHT_J:
		audio_source = ADV7511_AUDIO_SOURCE_I2S;
		i2s_क्रमmat = ADV7511_I2S_FORMAT_RIGHT_J;
		अवरोध;
	हाल HDMI_LEFT_J:
		audio_source = ADV7511_AUDIO_SOURCE_I2S;
		i2s_क्रमmat = ADV7511_I2S_FORMAT_LEFT_J;
		अवरोध;
	हाल HDMI_SPDIF:
		audio_source = ADV7511_AUDIO_SOURCE_SPDIF;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	invert_घड़ी = fmt->bit_clk_inv;

	regmap_update_bits(adv7511->regmap, ADV7511_REG_AUDIO_SOURCE, 0x70,
			   audio_source << 4);
	regmap_update_bits(adv7511->regmap, ADV7511_REG_AUDIO_CONFIG, BIT(6),
			   invert_घड़ी << 6);
	regmap_update_bits(adv7511->regmap, ADV7511_REG_I2S_CONFIG, 0x03,
			   i2s_क्रमmat);

	adv7511->audio_source = audio_source;

	adv7511->f_audio = hparms->sample_rate;

	adv7511_update_cts_n(adv7511);

	regmap_update_bits(adv7511->regmap, ADV7511_REG_AUDIO_CFG3,
			   ADV7511_AUDIO_CFG3_LEN_MASK, len);
	regmap_update_bits(adv7511->regmap, ADV7511_REG_I2C_FREQ_ID_CFG,
			   ADV7511_I2C_FREQ_ID_CFG_RATE_MASK, rate << 4);
	regmap_ग_लिखो(adv7511->regmap, 0x73, 0x1);

	वापस 0;
पूर्ण

अटल पूर्णांक audio_startup(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा adv7511 *adv7511 = dev_get_drvdata(dev);

	regmap_update_bits(adv7511->regmap, ADV7511_REG_AUDIO_CONFIG,
				BIT(7), 0);

	/* hide Audio infoframe updates */
	regmap_update_bits(adv7511->regmap, ADV7511_REG_INFOFRAME_UPDATE,
				BIT(5), BIT(5));
	/* enable N/CTS, enable Audio sample packets */
	regmap_update_bits(adv7511->regmap, ADV7511_REG_PACKET_ENABLE1,
				BIT(5), BIT(5));
	/* enable N/CTS */
	regmap_update_bits(adv7511->regmap, ADV7511_REG_PACKET_ENABLE1,
				BIT(6), BIT(6));
	/* not copyrighted */
	regmap_update_bits(adv7511->regmap, ADV7511_REG_AUDIO_CFG1,
				BIT(5), BIT(5));
	/* enable audio infoframes */
	regmap_update_bits(adv7511->regmap, ADV7511_REG_PACKET_ENABLE1,
				BIT(3), BIT(3));
	/* AV mute disable */
	regmap_update_bits(adv7511->regmap, ADV7511_REG_GC(0),
				BIT(7) | BIT(6), BIT(7));
	/* use Audio infoframe updated info */
	regmap_update_bits(adv7511->regmap, ADV7511_REG_GC(1),
				BIT(5), 0);
	/* enable SPDIF receiver */
	अगर (adv7511->audio_source == ADV7511_AUDIO_SOURCE_SPDIF)
		regmap_update_bits(adv7511->regmap, ADV7511_REG_AUDIO_CONFIG,
				   BIT(7), BIT(7));

	वापस 0;
पूर्ण

अटल व्योम audio_shutकरोwn(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा adv7511 *adv7511 = dev_get_drvdata(dev);

	अगर (adv7511->audio_source == ADV7511_AUDIO_SOURCE_SPDIF)
		regmap_update_bits(adv7511->regmap, ADV7511_REG_AUDIO_CONFIG,
				   BIT(7), 0);
पूर्ण

अटल पूर्णांक adv7511_hdmi_i2s_get_dai_id(काष्ठा snd_soc_component *component,
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

अटल स्थिर काष्ठा hdmi_codec_ops adv7511_codec_ops = अणु
	.hw_params	= adv7511_hdmi_hw_params,
	.audio_shutकरोwn = audio_shutकरोwn,
	.audio_startup	= audio_startup,
	.get_dai_id	= adv7511_hdmi_i2s_get_dai_id,
पूर्ण;

अटल स्थिर काष्ठा hdmi_codec_pdata codec_data = अणु
	.ops = &adv7511_codec_ops,
	.max_i2s_channels = 2,
	.i2s = 1,
	.spdअगर = 1,
पूर्ण;

पूर्णांक adv7511_audio_init(काष्ठा device *dev, काष्ठा adv7511 *adv7511)
अणु
	adv7511->audio_pdev = platक्रमm_device_रेजिस्टर_data(dev,
					HDMI_CODEC_DRV_NAME,
					PLATFORM_DEVID_AUTO,
					&codec_data,
					माप(codec_data));
	वापस PTR_ERR_OR_ZERO(adv7511->audio_pdev);
पूर्ण

व्योम adv7511_audio_निकास(काष्ठा adv7511 *adv7511)
अणु
	अगर (adv7511->audio_pdev) अणु
		platक्रमm_device_unरेजिस्टर(adv7511->audio_pdev);
		adv7511->audio_pdev = शून्य;
	पूर्ण
पूर्ण
