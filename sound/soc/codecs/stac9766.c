<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * stac9766.c  --  ALSA SoC STAC9766 codec support
 *
 * Copyright 2009 Jon Smirl, Digispeaker
 * Author: Jon Smirl <jonsmirl@gmail.com>
 *
 *  Features:-
 *
 *   o Support क्रम AC97 Codec, S/PDIF
 */

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/regmap.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/ac97_codec.h>
#समावेश <sound/initval.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>

#घोषणा STAC9766_VENDOR_ID 0x83847666
#घोषणा STAC9766_VENDOR_ID_MASK 0xffffffff

#घोषणा AC97_STAC_DA_CONTROL 0x6A
#घोषणा AC97_STAC_ANALOG_SPECIAL 0x6E
#घोषणा AC97_STAC_STEREO_MIC 0x78

अटल स्थिर काष्ठा reg_शेष stac9766_reg_शेषs[] = अणु
	अणु 0x02, 0x8000 पूर्ण,
	अणु 0x04, 0x8000 पूर्ण,
	अणु 0x06, 0x8000 पूर्ण,
	अणु 0x0a, 0x0000 पूर्ण,
	अणु 0x0c, 0x8008 पूर्ण,
	अणु 0x0e, 0x8008 पूर्ण,
	अणु 0x10, 0x8808 पूर्ण,
	अणु 0x12, 0x8808 पूर्ण,
	अणु 0x14, 0x8808 पूर्ण,
	अणु 0x16, 0x8808 पूर्ण,
	अणु 0x18, 0x8808 पूर्ण,
	अणु 0x1a, 0x0000 पूर्ण,
	अणु 0x1c, 0x8000 पूर्ण,
	अणु 0x20, 0x0000 पूर्ण,
	अणु 0x22, 0x0000 पूर्ण,
	अणु 0x28, 0x0a05 पूर्ण,
	अणु 0x2c, 0xbb80 पूर्ण,
	अणु 0x32, 0xbb80 पूर्ण,
	अणु 0x3a, 0x2000 पूर्ण,
	अणु 0x3e, 0x0100 पूर्ण,
	अणु 0x4c, 0x0300 पूर्ण,
	अणु 0x4e, 0xffff पूर्ण,
	अणु 0x50, 0x0000 पूर्ण,
	अणु 0x52, 0x0000 पूर्ण,
	अणु 0x54, 0x0000 पूर्ण,
	अणु 0x6a, 0x0000 पूर्ण,
	अणु 0x6e, 0x1000 पूर्ण,
	अणु 0x72, 0x0000 पूर्ण,
	अणु 0x78, 0x0000 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config stac9766_regmap_config = अणु
	.reg_bits = 16,
	.reg_stride = 2,
	.val_bits = 16,
	.max_रेजिस्टर = 0x78,
	.cache_type = REGCACHE_RBTREE,

	.अस्थिर_reg = regmap_ac97_शेष_अस्थिर,

	.reg_शेषs = stac9766_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(stac9766_reg_शेषs),
पूर्ण;

अटल स्थिर अक्षर *stac9766_record_mux[] = अणु"Mic", "CD", "Video", "AUX",
			"Line", "Stereo Mix", "Mono Mix", "Phone"पूर्ण;
अटल स्थिर अक्षर *stac9766_mono_mux[] = अणु"Mix", "Mic"पूर्ण;
अटल स्थिर अक्षर *stac9766_mic_mux[] = अणु"Mic1", "Mic2"पूर्ण;
अटल स्थिर अक्षर *stac9766_SPDIF_mux[] = अणु"PCM", "ADC Record"पूर्ण;
अटल स्थिर अक्षर *stac9766_popbypass_mux[] = अणु"Normal", "Bypass Mixer"पूर्ण;
अटल स्थिर अक्षर *stac9766_record_all_mux[] = अणु"All analog",
	"Analog plus DAC"पूर्ण;
अटल स्थिर अक्षर *stac9766_boost1[] = अणु"0dB", "10dB"पूर्ण;
अटल स्थिर अक्षर *stac9766_boost2[] = अणु"0dB", "20dB"पूर्ण;
अटल स्थिर अक्षर *stac9766_stereo_mic[] = अणु"Off", "On"पूर्ण;

अटल SOC_ENUM_DOUBLE_DECL(stac9766_record_क्रमागत,
			    AC97_REC_SEL, 8, 0, stac9766_record_mux);
अटल SOC_ENUM_SINGLE_DECL(stac9766_mono_क्रमागत,
			    AC97_GENERAL_PURPOSE, 9, stac9766_mono_mux);
अटल SOC_ENUM_SINGLE_DECL(stac9766_mic_क्रमागत,
			    AC97_GENERAL_PURPOSE, 8, stac9766_mic_mux);
अटल SOC_ENUM_SINGLE_DECL(stac9766_SPDIF_क्रमागत,
			    AC97_STAC_DA_CONTROL, 1, stac9766_SPDIF_mux);
अटल SOC_ENUM_SINGLE_DECL(stac9766_popbypass_क्रमागत,
			    AC97_GENERAL_PURPOSE, 15, stac9766_popbypass_mux);
अटल SOC_ENUM_SINGLE_DECL(stac9766_record_all_क्रमागत,
			    AC97_STAC_ANALOG_SPECIAL, 12,
			    stac9766_record_all_mux);
अटल SOC_ENUM_SINGLE_DECL(stac9766_boost1_क्रमागत,
			    AC97_MIC, 6, stac9766_boost1); /* 0/10dB */
अटल SOC_ENUM_SINGLE_DECL(stac9766_boost2_क्रमागत,
			    AC97_STAC_ANALOG_SPECIAL, 2, stac9766_boost2); /* 0/20dB */
अटल SOC_ENUM_SINGLE_DECL(stac9766_stereo_mic_क्रमागत,
			    AC97_STAC_STEREO_MIC, 2, stac9766_stereo_mic);

अटल स्थिर SNDRV_CTL_TLVD_DECLARE_DB_SCALE(master_tlv, -4650, 150, 0);
अटल स्थिर SNDRV_CTL_TLVD_DECLARE_DB_SCALE(record_tlv,     0, 150, 0);
अटल स्थिर SNDRV_CTL_TLVD_DECLARE_DB_SCALE(beep_tlv,   -4500, 300, 0);
अटल स्थिर SNDRV_CTL_TLVD_DECLARE_DB_SCALE(mix_tlv,    -3450, 150, 0);

अटल स्थिर काष्ठा snd_kcontrol_new stac9766_snd_ac97_controls[] = अणु
	SOC_DOUBLE_TLV("Speaker Volume", AC97_MASTER, 8, 0, 31, 1, master_tlv),
	SOC_SINGLE("Speaker Switch", AC97_MASTER, 15, 1, 1),
	SOC_DOUBLE_TLV("Headphone Volume", AC97_HEADPHONE, 8, 0, 31, 1,
		       master_tlv),
	SOC_SINGLE("Headphone Switch", AC97_HEADPHONE, 15, 1, 1),
	SOC_SINGLE_TLV("Mono Out Volume", AC97_MASTER_MONO, 0, 31, 1,
		       master_tlv),
	SOC_SINGLE("Mono Out Switch", AC97_MASTER_MONO, 15, 1, 1),

	SOC_DOUBLE_TLV("Record Volume", AC97_REC_GAIN, 8, 0, 15, 0, record_tlv),
	SOC_SINGLE("Record Switch", AC97_REC_GAIN, 15, 1, 1),


	SOC_SINGLE_TLV("Beep Volume", AC97_PC_BEEP, 1, 15, 1, beep_tlv),
	SOC_SINGLE("Beep Switch", AC97_PC_BEEP, 15, 1, 1),
	SOC_SINGLE("Beep Frequency", AC97_PC_BEEP, 5, 127, 1),
	SOC_SINGLE_TLV("Phone Volume", AC97_PHONE, 0, 31, 1, mix_tlv),
	SOC_SINGLE("Phone Switch", AC97_PHONE, 15, 1, 1),

	SOC_ENUM("Mic Boost1", stac9766_boost1_क्रमागत),
	SOC_ENUM("Mic Boost2", stac9766_boost2_क्रमागत),
	SOC_SINGLE_TLV("Mic Volume", AC97_MIC, 0, 31, 1, mix_tlv),
	SOC_SINGLE("Mic Switch", AC97_MIC, 15, 1, 1),
	SOC_ENUM("Stereo Mic", stac9766_stereo_mic_क्रमागत),

	SOC_DOUBLE_TLV("Line Volume", AC97_LINE, 8, 0, 31, 1, mix_tlv),
	SOC_SINGLE("Line Switch", AC97_LINE, 15, 1, 1),
	SOC_DOUBLE_TLV("CD Volume", AC97_CD, 8, 0, 31, 1, mix_tlv),
	SOC_SINGLE("CD Switch", AC97_CD, 15, 1, 1),
	SOC_DOUBLE_TLV("AUX Volume", AC97_AUX, 8, 0, 31, 1, mix_tlv),
	SOC_SINGLE("AUX Switch", AC97_AUX, 15, 1, 1),
	SOC_DOUBLE_TLV("Video Volume", AC97_VIDEO, 8, 0, 31, 1, mix_tlv),
	SOC_SINGLE("Video Switch", AC97_VIDEO, 15, 1, 1),

	SOC_DOUBLE_TLV("DAC Volume", AC97_PCM, 8, 0, 31, 1, mix_tlv),
	SOC_SINGLE("DAC Switch", AC97_PCM, 15, 1, 1),
	SOC_SINGLE("Loopback Test Switch", AC97_GENERAL_PURPOSE, 7, 1, 0),
	SOC_SINGLE("3D Volume", AC97_3D_CONTROL, 3, 2, 1),
	SOC_SINGLE("3D Switch", AC97_GENERAL_PURPOSE, 13, 1, 0),

	SOC_ENUM("SPDIF Mux", stac9766_SPDIF_क्रमागत),
	SOC_ENUM("Mic1/2 Mux", stac9766_mic_क्रमागत),
	SOC_ENUM("Record All Mux", stac9766_record_all_क्रमागत),
	SOC_ENUM("Record Mux", stac9766_record_क्रमागत),
	SOC_ENUM("Mono Mux", stac9766_mono_क्रमागत),
	SOC_ENUM("Pop Bypass Mux", stac9766_popbypass_क्रमागत),
पूर्ण;

अटल पूर्णांक ac97_analog_prepare(काष्ठा snd_pcm_substream *substream,
			       काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अचिन्हित लघु reg;

	/* enable variable rate audio, disable SPDIF output */
	snd_soc_component_update_bits(component, AC97_EXTENDED_STATUS, 0x5, 0x1);

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		reg = AC97_PCM_FRONT_DAC_RATE;
	अन्यथा
		reg = AC97_PCM_LR_ADC_RATE;

	वापस snd_soc_component_ग_लिखो(component, reg, runसमय->rate);
पूर्ण

अटल पूर्णांक ac97_digital_prepare(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अचिन्हित लघु reg;

	snd_soc_component_ग_लिखो(component, AC97_SPDIF, 0x2002);

	/* Enable VRA and SPDIF out */
	snd_soc_component_update_bits(component, AC97_EXTENDED_STATUS, 0x5, 0x5);

	reg = AC97_PCM_FRONT_DAC_RATE;

	वापस snd_soc_component_ग_लिखो(component, reg, runसमय->rate);
पूर्ण

अटल पूर्णांक stac9766_set_bias_level(काष्ठा snd_soc_component *component,
				   क्रमागत snd_soc_bias_level level)
अणु
	चयन (level) अणु
	हाल SND_SOC_BIAS_ON: /* full On */
	हाल SND_SOC_BIAS_PREPARE: /* partial On */
	हाल SND_SOC_BIAS_STANDBY: /* Off, with घातer */
		snd_soc_component_ग_लिखो(component, AC97_POWERDOWN, 0x0000);
		अवरोध;
	हाल SND_SOC_BIAS_OFF: /* Off, without घातer */
		/* disable everything including AC link */
		snd_soc_component_ग_लिखो(component, AC97_POWERDOWN, 0xffff);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक stac9766_component_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_ac97 *ac97 = snd_soc_component_get_drvdata(component);

	वापस snd_ac97_reset(ac97, true, STAC9766_VENDOR_ID,
		STAC9766_VENDOR_ID_MASK);
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops stac9766_dai_ops_analog = अणु
	.prepare = ac97_analog_prepare,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops stac9766_dai_ops_digital = अणु
	.prepare = ac97_digital_prepare,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver stac9766_dai[] = अणु
अणु
	.name = "stac9766-hifi-analog",

	/* stream cababilities */
	.playback = अणु
		.stream_name = "stac9766 analog",
		.channels_min = 1,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_48000,
		.क्रमmats = SND_SOC_STD_AC97_FMTS,
	पूर्ण,
	.capture = अणु
		.stream_name = "stac9766 analog",
		.channels_min = 1,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_48000,
		.क्रमmats = SND_SOC_STD_AC97_FMTS,
	पूर्ण,
	/* alsa ops */
	.ops = &stac9766_dai_ops_analog,
पूर्ण,
अणु
	.name = "stac9766-hifi-IEC958",

	/* stream cababilities */
	.playback = अणु
		.stream_name = "stac9766 IEC958",
		.channels_min = 1,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_32000 | \
			SNDRV_PCM_RATE_44100 | SNDRV_PCM_RATE_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_IEC958_SUBFRAME_BE,
	पूर्ण,
	/* alsa ops */
	.ops = &stac9766_dai_ops_digital,
पूर्ण
पूर्ण;

अटल पूर्णांक stac9766_component_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_ac97 *ac97;
	काष्ठा regmap *regmap;
	पूर्णांक ret;

	ac97 = snd_soc_new_ac97_component(component, STAC9766_VENDOR_ID,
			STAC9766_VENDOR_ID_MASK);
	अगर (IS_ERR(ac97))
		वापस PTR_ERR(ac97);

	regmap = regmap_init_ac97(ac97, &stac9766_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		ret = PTR_ERR(regmap);
		जाओ err_मुक्त_ac97;
	पूर्ण

	snd_soc_component_init_regmap(component, regmap);
	snd_soc_component_set_drvdata(component, ac97);

	वापस 0;
err_मुक्त_ac97:
	snd_soc_मुक्त_ac97_component(ac97);
	वापस ret;
पूर्ण

अटल व्योम stac9766_component_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_ac97 *ac97 = snd_soc_component_get_drvdata(component);

	snd_soc_component_निकास_regmap(component);
	snd_soc_मुक्त_ac97_component(ac97);
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_stac9766 = अणु
	.controls		= stac9766_snd_ac97_controls,
	.num_controls		= ARRAY_SIZE(stac9766_snd_ac97_controls),
	.set_bias_level		= stac9766_set_bias_level,
	.probe			= stac9766_component_probe,
	.हटाओ			= stac9766_component_हटाओ,
	.resume			= stac9766_component_resume,
	.suspend_bias_off	= 1,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,

पूर्ण;

अटल पूर्णांक stac9766_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev,
			&soc_component_dev_stac9766, stac9766_dai, ARRAY_SIZE(stac9766_dai));
पूर्ण

अटल काष्ठा platक्रमm_driver stac9766_codec_driver = अणु
	.driver = अणु
			.name = "stac9766-codec",
	पूर्ण,

	.probe = stac9766_probe,
पूर्ण;

module_platक्रमm_driver(stac9766_codec_driver);

MODULE_DESCRIPTION("ASoC stac9766 driver");
MODULE_AUTHOR("Jon Smirl <jonsmirl@gmail.com>");
MODULE_LICENSE("GPL");
