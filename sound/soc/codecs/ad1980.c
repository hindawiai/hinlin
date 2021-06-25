<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ad1980.c  --  ALSA Soc AD1980 codec support
 *
 * Copyright:	Analog Devices Inc.
 * Author:	Roy Huang <roy.huang@analog.com>
 * 		Clअगरf Cai <clअगरf.cai@analog.com>
 */

/*
 * WARNING:
 *
 * Because Analog Devices Inc. disजारीd the ad1980 sound chip since
 * Sep. 2009, this ad1980 driver is not मुख्यtained, tested and supported
 * by ADI now.
 */

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/regmap.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/ac97_codec.h>
#समावेश <sound/initval.h>
#समावेश <sound/soc.h>

अटल स्थिर काष्ठा reg_शेष ad1980_reg_शेषs[] = अणु
	अणु 0x02, 0x8000 पूर्ण,
	अणु 0x04, 0x8000 पूर्ण,
	अणु 0x06, 0x8000 पूर्ण,
	अणु 0x0c, 0x8008 पूर्ण,
	अणु 0x0e, 0x8008 पूर्ण,
	अणु 0x10, 0x8808 पूर्ण,
	अणु 0x12, 0x8808 पूर्ण,
	अणु 0x16, 0x8808 पूर्ण,
	अणु 0x18, 0x8808 पूर्ण,
	अणु 0x1a, 0x0000 पूर्ण,
	अणु 0x1c, 0x8000 पूर्ण,
	अणु 0x20, 0x0000 पूर्ण,
	अणु 0x28, 0x03c7 पूर्ण,
	अणु 0x2c, 0xbb80 पूर्ण,
	अणु 0x2e, 0xbb80 पूर्ण,
	अणु 0x30, 0xbb80 पूर्ण,
	अणु 0x32, 0xbb80 पूर्ण,
	अणु 0x36, 0x8080 पूर्ण,
	अणु 0x38, 0x8080 पूर्ण,
	अणु 0x3a, 0x2000 पूर्ण,
	अणु 0x60, 0x0000 पूर्ण,
	अणु 0x62, 0x0000 पूर्ण,
	अणु 0x72, 0x0000 पूर्ण,
	अणु 0x74, 0x1001 पूर्ण,
	अणु 0x76, 0x0000 पूर्ण,
पूर्ण;

अटल bool ad1980_पढ़ोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल AC97_RESET ... AC97_MASTER_MONO:
	हाल AC97_PHONE ... AC97_CD:
	हाल AC97_AUX ... AC97_GENERAL_PURPOSE:
	हाल AC97_POWERDOWN ... AC97_PCM_LR_ADC_RATE:
	हाल AC97_SPDIF:
	हाल AC97_CODEC_CLASS_REV:
	हाल AC97_PCI_SVID:
	हाल AC97_AD_CODEC_CFG:
	हाल AC97_AD_JACK_SPDIF:
	हाल AC97_AD_SERIAL_CFG:
	हाल AC97_VENDOR_ID1:
	हाल AC97_VENDOR_ID2:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool ad1980_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल AC97_VENDOR_ID1:
	हाल AC97_VENDOR_ID2:
		वापस false;
	शेष:
		वापस ad1980_पढ़ोable_reg(dev, reg);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config ad1980_regmap_config = अणु
	.reg_bits = 16,
	.reg_stride = 2,
	.val_bits = 16,
	.max_रेजिस्टर = 0x7e,
	.cache_type = REGCACHE_RBTREE,

	.अस्थिर_reg = regmap_ac97_शेष_अस्थिर,
	.पढ़ोable_reg = ad1980_पढ़ोable_reg,
	.ग_लिखोable_reg = ad1980_ग_लिखोable_reg,

	.reg_शेषs = ad1980_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(ad1980_reg_शेषs),
पूर्ण;

अटल स्थिर अक्षर *ad1980_rec_sel[] = अणु"Mic", "CD", "NC", "AUX", "Line",
		"Stereo Mix", "Mono Mix", "Phone"पूर्ण;

अटल SOC_ENUM_DOUBLE_DECL(ad1980_cap_src,
			    AC97_REC_SEL, 8, 0, ad1980_rec_sel);

अटल स्थिर काष्ठा snd_kcontrol_new ad1980_snd_ac97_controls[] = अणु
SOC_DOUBLE("Master Playback Volume", AC97_MASTER, 8, 0, 31, 1),
SOC_SINGLE("Master Playback Switch", AC97_MASTER, 15, 1, 1),

SOC_DOUBLE("Headphone Playback Volume", AC97_HEADPHONE, 8, 0, 31, 1),
SOC_SINGLE("Headphone Playback Switch", AC97_HEADPHONE, 15, 1, 1),

SOC_DOUBLE("PCM Playback Volume", AC97_PCM, 8, 0, 31, 1),
SOC_SINGLE("PCM Playback Switch", AC97_PCM, 15, 1, 1),

SOC_DOUBLE("PCM Capture Volume", AC97_REC_GAIN, 8, 0, 31, 0),
SOC_SINGLE("PCM Capture Switch", AC97_REC_GAIN, 15, 1, 1),

SOC_SINGLE("Mono Playback Volume", AC97_MASTER_MONO, 0, 31, 1),
SOC_SINGLE("Mono Playback Switch", AC97_MASTER_MONO, 15, 1, 1),

SOC_SINGLE("Phone Capture Volume", AC97_PHONE, 0, 31, 1),
SOC_SINGLE("Phone Capture Switch", AC97_PHONE, 15, 1, 1),

SOC_SINGLE("Mic Volume", AC97_MIC, 0, 31, 1),
SOC_SINGLE("Mic Switch", AC97_MIC, 15, 1, 1),

SOC_SINGLE("Stereo Mic Switch", AC97_AD_MISC, 6, 1, 0),
SOC_DOUBLE("Line HP Swap Switch", AC97_AD_MISC, 10, 5, 1, 0),

SOC_DOUBLE("Surround Playback Volume", AC97_SURROUND_MASTER, 8, 0, 31, 1),
SOC_DOUBLE("Surround Playback Switch", AC97_SURROUND_MASTER, 15, 7, 1, 1),

SOC_DOUBLE("Center/LFE Playback Volume", AC97_CENTER_LFE_MASTER, 8, 0, 31, 1),
SOC_DOUBLE("Center/LFE Playback Switch", AC97_CENTER_LFE_MASTER, 15, 7, 1, 1),

SOC_ENUM("Capture Source", ad1980_cap_src),

SOC_SINGLE("Mic Boost Switch", AC97_MIC, 6, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget ad1980_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_INPUT("MIC1"),
SND_SOC_DAPM_INPUT("MIC2"),
SND_SOC_DAPM_INPUT("CD_L"),
SND_SOC_DAPM_INPUT("CD_R"),
SND_SOC_DAPM_INPUT("AUX_L"),
SND_SOC_DAPM_INPUT("AUX_R"),
SND_SOC_DAPM_INPUT("LINE_IN_L"),
SND_SOC_DAPM_INPUT("LINE_IN_R"),

SND_SOC_DAPM_OUTPUT("LFE_OUT"),
SND_SOC_DAPM_OUTPUT("CENTER_OUT"),
SND_SOC_DAPM_OUTPUT("LINE_OUT_L"),
SND_SOC_DAPM_OUTPUT("LINE_OUT_R"),
SND_SOC_DAPM_OUTPUT("MONO_OUT"),
SND_SOC_DAPM_OUTPUT("HP_OUT_L"),
SND_SOC_DAPM_OUTPUT("HP_OUT_R"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route ad1980_dapm_routes[] = अणु
	अणु "Capture", शून्य, "MIC1" पूर्ण,
	अणु "Capture", शून्य, "MIC2" पूर्ण,
	अणु "Capture", शून्य, "CD_L" पूर्ण,
	अणु "Capture", शून्य, "CD_R" पूर्ण,
	अणु "Capture", शून्य, "AUX_L" पूर्ण,
	अणु "Capture", शून्य, "AUX_R" पूर्ण,
	अणु "Capture", शून्य, "LINE_IN_L" पूर्ण,
	अणु "Capture", शून्य, "LINE_IN_R" पूर्ण,

	अणु "LFE_OUT", शून्य, "Playback" पूर्ण,
	अणु "CENTER_OUT", शून्य, "Playback" पूर्ण,
	अणु "LINE_OUT_L", शून्य, "Playback" पूर्ण,
	अणु "LINE_OUT_R", शून्य, "Playback" पूर्ण,
	अणु "MONO_OUT", शून्य, "Playback" पूर्ण,
	अणु "HP_OUT_L", शून्य, "Playback" पूर्ण,
	अणु "HP_OUT_R", शून्य, "Playback" पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver ad1980_dai = अणु
	.name = "ad1980-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 2,
		.channels_max = 6,
		.rates = SNDRV_PCM_RATE_48000,
		.क्रमmats = SND_SOC_STD_AC97_FMTS, पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_48000,
		.क्रमmats = SND_SOC_STD_AC97_FMTS, पूर्ण,
पूर्ण;

#घोषणा AD1980_VENDOR_ID 0x41445300
#घोषणा AD1980_VENDOR_MASK 0xffffff00

अटल पूर्णांक ad1980_reset(काष्ठा snd_soc_component *component, पूर्णांक try_warm)
अणु
	काष्ठा snd_ac97 *ac97 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक retry_cnt = 0;
	पूर्णांक ret;

	करो अणु
		ret = snd_ac97_reset(ac97, true, AD1980_VENDOR_ID,
			AD1980_VENDOR_MASK);
		अगर (ret >= 0)
			वापस 0;

		/*
		 * Set bit 16slot in रेजिस्टर 74h, then every slot will has only
		 * 16 bits. This command is sent out in 20bit mode, in which
		 * हाल the first nibble of data is eaten by the addr. (Tag is
		 * always 16 bit)
		 */
		snd_soc_component_ग_लिखो(component, AC97_AD_SERIAL_CFG, 0x9900);

	पूर्ण जबतक (retry_cnt++ < 10);

	dev_err(component->dev, "Failed to reset: AC97 link error\n");

	वापस -EIO;
पूर्ण

अटल पूर्णांक ad1980_soc_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_ac97 *ac97;
	काष्ठा regmap *regmap;
	पूर्णांक ret;
	u16 venकरोr_id2;
	u16 ext_status;

	ac97 = snd_soc_new_ac97_component(component, 0, 0);
	अगर (IS_ERR(ac97)) अणु
		ret = PTR_ERR(ac97);
		dev_err(component->dev, "Failed to register AC97 component: %d\n", ret);
		वापस ret;
	पूर्ण

	regmap = regmap_init_ac97(ac97, &ad1980_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		ret = PTR_ERR(regmap);
		जाओ err_मुक्त_ac97;
	पूर्ण

	snd_soc_component_init_regmap(component, regmap);
	snd_soc_component_set_drvdata(component, ac97);

	ret = ad1980_reset(component, 0);
	अगर (ret < 0)
		जाओ reset_err;

	venकरोr_id2 = snd_soc_component_पढ़ो(component, AC97_VENDOR_ID2);
	अगर (venकरोr_id2 == 0x5374) अणु
		dev_warn(component->dev,
			"Found AD1981 - only 2/2 IN/OUT Channels supported\n");
	पूर्ण

	/* unmute captures and playbacks volume */
	snd_soc_component_ग_लिखो(component, AC97_MASTER, 0x0000);
	snd_soc_component_ग_लिखो(component, AC97_PCM, 0x0000);
	snd_soc_component_ग_लिखो(component, AC97_REC_GAIN, 0x0000);
	snd_soc_component_ग_लिखो(component, AC97_CENTER_LFE_MASTER, 0x0000);
	snd_soc_component_ग_लिखो(component, AC97_SURROUND_MASTER, 0x0000);

	/*घातer on LFE/CENTER/Surround DACs*/
	ext_status = snd_soc_component_पढ़ो(component, AC97_EXTENDED_STATUS);
	snd_soc_component_ग_लिखो(component, AC97_EXTENDED_STATUS, ext_status&~0x3800);

	वापस 0;

reset_err:
	snd_soc_component_निकास_regmap(component);
err_मुक्त_ac97:
	snd_soc_मुक्त_ac97_component(ac97);
	वापस ret;
पूर्ण

अटल व्योम ad1980_soc_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_ac97 *ac97 = snd_soc_component_get_drvdata(component);

	snd_soc_component_निकास_regmap(component);
	snd_soc_मुक्त_ac97_component(ac97);
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_ad1980 = अणु
	.probe			= ad1980_soc_probe,
	.हटाओ			= ad1980_soc_हटाओ,
	.controls		= ad1980_snd_ac97_controls,
	.num_controls		= ARRAY_SIZE(ad1980_snd_ac97_controls),
	.dapm_widमाला_लो		= ad1980_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(ad1980_dapm_widमाला_लो),
	.dapm_routes		= ad1980_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(ad1980_dapm_routes),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल पूर्णांक ad1980_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev,
			&soc_component_dev_ad1980, &ad1980_dai, 1);
पूर्ण

अटल काष्ठा platक्रमm_driver ad1980_codec_driver = अणु
	.driver = अणु
			.name = "ad1980",
	पूर्ण,

	.probe = ad1980_probe,
पूर्ण;

module_platक्रमm_driver(ad1980_codec_driver);

MODULE_DESCRIPTION("ASoC ad1980 driver (Obsolete)");
MODULE_AUTHOR("Roy Huang, Cliff Cai");
MODULE_LICENSE("GPL");
