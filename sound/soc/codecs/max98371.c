<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * max98371.c -- ALSA SoC Stereo MAX98371 driver
 *
 * Copyright 2015-16 Maxim Integrated Products
 */

#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>
#समावेश "max98371.h"

अटल स्थिर अक्षर *स्थिर monomix_text[] = अणु
	"Left", "Right", "LeftRightDiv2",
पूर्ण;

अटल स्थिर अक्षर *स्थिर hpf_cutoff_txt[] = अणु
	"Disable", "DC Block", "50Hz",
	"100Hz", "200Hz", "400Hz", "800Hz",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(max98371_monomix, MAX98371_MONOMIX_CFG, 0,
		monomix_text);

अटल SOC_ENUM_SINGLE_DECL(max98371_hpf_cutoff, MAX98371_HPF, 0,
		hpf_cutoff_txt);

अटल स्थिर DECLARE_TLV_DB_RANGE(max98371_dht_min_gain,
	0, 1, TLV_DB_SCALE_ITEM(537, 66, 0),
	2, 3, TLV_DB_SCALE_ITEM(677, 82, 0),
	4, 5, TLV_DB_SCALE_ITEM(852, 104, 0),
	6, 7, TLV_DB_SCALE_ITEM(1072, 131, 0),
	8, 9, TLV_DB_SCALE_ITEM(1350, 165, 0),
	10, 11, TLV_DB_SCALE_ITEM(1699, 101, 0),
);

अटल स्थिर DECLARE_TLV_DB_RANGE(max98371_dht_max_gain,
	0, 1, TLV_DB_SCALE_ITEM(537, 66, 0),
	2, 3, TLV_DB_SCALE_ITEM(677, 82, 0),
	4, 5, TLV_DB_SCALE_ITEM(852, 104, 0),
	6, 7, TLV_DB_SCALE_ITEM(1072, 131, 0),
	8, 9, TLV_DB_SCALE_ITEM(1350, 165, 0),
	10, 11, TLV_DB_SCALE_ITEM(1699, 208, 0),
);

अटल स्थिर DECLARE_TLV_DB_RANGE(max98371_dht_rot_gain,
	0, 1, TLV_DB_SCALE_ITEM(-50, -50, 0),
	2, 6, TLV_DB_SCALE_ITEM(-100, -100, 0),
	7, 8, TLV_DB_SCALE_ITEM(-800, -200, 0),
	9, 11, TLV_DB_SCALE_ITEM(-1200, -300, 0),
	12, 13, TLV_DB_SCALE_ITEM(-2000, -200, 0),
	14, 15, TLV_DB_SCALE_ITEM(-2500, -500, 0),
);

अटल स्थिर काष्ठा reg_शेष max98371_reg[] = अणु
	अणु 0x01, 0x00 पूर्ण,
	अणु 0x02, 0x00 पूर्ण,
	अणु 0x03, 0x00 पूर्ण,
	अणु 0x04, 0x00 पूर्ण,
	अणु 0x05, 0x00 पूर्ण,
	अणु 0x06, 0x00 पूर्ण,
	अणु 0x07, 0x00 पूर्ण,
	अणु 0x08, 0x00 पूर्ण,
	अणु 0x09, 0x00 पूर्ण,
	अणु 0x0A, 0x00 पूर्ण,
	अणु 0x10, 0x06 पूर्ण,
	अणु 0x11, 0x08 पूर्ण,
	अणु 0x14, 0x80 पूर्ण,
	अणु 0x15, 0x00 पूर्ण,
	अणु 0x16, 0x00 पूर्ण,
	अणु 0x18, 0x00 पूर्ण,
	अणु 0x19, 0x00 पूर्ण,
	अणु 0x1C, 0x00 पूर्ण,
	अणु 0x1D, 0x00 पूर्ण,
	अणु 0x1E, 0x00 पूर्ण,
	अणु 0x1F, 0x00 पूर्ण,
	अणु 0x20, 0x00 पूर्ण,
	अणु 0x21, 0x00 पूर्ण,
	अणु 0x22, 0x00 पूर्ण,
	अणु 0x23, 0x00 पूर्ण,
	अणु 0x24, 0x00 पूर्ण,
	अणु 0x25, 0x00 पूर्ण,
	अणु 0x26, 0x00 पूर्ण,
	अणु 0x27, 0x00 पूर्ण,
	अणु 0x28, 0x00 पूर्ण,
	अणु 0x29, 0x00 पूर्ण,
	अणु 0x2A, 0x00 पूर्ण,
	अणु 0x2B, 0x00 पूर्ण,
	अणु 0x2C, 0x00 पूर्ण,
	अणु 0x2D, 0x00 पूर्ण,
	अणु 0x2E, 0x0B पूर्ण,
	अणु 0x31, 0x00 पूर्ण,
	अणु 0x32, 0x18 पूर्ण,
	अणु 0x33, 0x00 पूर्ण,
	अणु 0x34, 0x00 पूर्ण,
	अणु 0x36, 0x00 पूर्ण,
	अणु 0x37, 0x00 पूर्ण,
	अणु 0x38, 0x00 पूर्ण,
	अणु 0x39, 0x00 पूर्ण,
	अणु 0x3A, 0x00 पूर्ण,
	अणु 0x3B, 0x00 पूर्ण,
	अणु 0x3C, 0x00 पूर्ण,
	अणु 0x3D, 0x00 पूर्ण,
	अणु 0x3E, 0x00 पूर्ण,
	अणु 0x3F, 0x00 पूर्ण,
	अणु 0x40, 0x00 पूर्ण,
	अणु 0x41, 0x00 पूर्ण,
	अणु 0x42, 0x00 पूर्ण,
	अणु 0x43, 0x00 पूर्ण,
	अणु 0x4A, 0x00 पूर्ण,
	अणु 0x4B, 0x00 पूर्ण,
	अणु 0x4C, 0x00 पूर्ण,
	अणु 0x4D, 0x00 पूर्ण,
	अणु 0x4E, 0x00 पूर्ण,
	अणु 0x50, 0x00 पूर्ण,
	अणु 0x51, 0x00 पूर्ण,
	अणु 0x55, 0x00 पूर्ण,
	अणु 0x58, 0x00 पूर्ण,
	अणु 0x59, 0x00 पूर्ण,
	अणु 0x5C, 0x00 पूर्ण,
	अणु 0xFF, 0x43 पूर्ण,
पूर्ण;

अटल bool max98371_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल MAX98371_IRQ_CLEAR1:
	हाल MAX98371_IRQ_CLEAR2:
	हाल MAX98371_IRQ_CLEAR3:
	हाल MAX98371_VERSION:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool max98371_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल MAX98371_SOFT_RESET:
		वापस false;
	शेष:
		वापस true;
	पूर्ण
पूर्ण;

अटल स्थिर DECLARE_TLV_DB_RANGE(max98371_gain_tlv,
	0, 7, TLV_DB_SCALE_ITEM(0, 50, 0),
	8, 10, TLV_DB_SCALE_ITEM(400, 100, 0)
);

अटल स्थिर DECLARE_TLV_DB_SCALE(digital_tlv, -6300, 50, 1);

अटल स्थिर काष्ठा snd_kcontrol_new max98371_snd_controls[] = अणु
	SOC_SINGLE_TLV("Speaker Volume", MAX98371_GAIN,
			MAX98371_GAIN_SHIFT, (1<<MAX98371_GAIN_WIDTH)-1, 0,
			max98371_gain_tlv),
	SOC_SINGLE_TLV("Digital Volume", MAX98371_DIGITAL_GAIN, 0,
			(1<<MAX98371_DIGITAL_GAIN_WIDTH)-1, 1, digital_tlv),
	SOC_SINGLE_TLV("Speaker DHT Max Volume", MAX98371_GAIN,
			0, (1<<MAX98371_DHT_MAX_WIDTH)-1, 0,
			max98371_dht_max_gain),
	SOC_SINGLE_TLV("Speaker DHT Min Volume", MAX98371_DHT_GAIN,
			0, (1<<MAX98371_DHT_GAIN_WIDTH)-1, 0,
			max98371_dht_min_gain),
	SOC_SINGLE_TLV("Speaker DHT Rotation Volume", MAX98371_DHT_GAIN,
			0, (1<<MAX98371_DHT_ROT_WIDTH)-1, 0,
			max98371_dht_rot_gain),
	SOC_SINGLE("DHT Attack Step", MAX98371_DHT, MAX98371_DHT_STEP, 3, 0),
	SOC_SINGLE("DHT Attack Rate", MAX98371_DHT, 0, 7, 0),
	SOC_ENUM("Monomix Select", max98371_monomix),
	SOC_ENUM("HPF Cutoff", max98371_hpf_cutoff),
पूर्ण;

अटल पूर्णांक max98371_dai_set_fmt(काष्ठा snd_soc_dai *codec_dai,
		अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा max98371_priv *max98371 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक val = 0;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अवरोध;
	शेष:
		dev_err(component->dev, "DAI clock mode unsupported");
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		val |= 0;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		val |= MAX98371_DAI_RIGHT;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		val |= MAX98371_DAI_LEFT;
		अवरोध;
	शेष:
		dev_err(component->dev, "DAI wrong mode unsupported");
		वापस -EINVAL;
	पूर्ण
	regmap_update_bits(max98371->regmap, MAX98371_FMT,
			MAX98371_FMT_MODE_MASK, val);
	वापस 0;
पूर्ण

अटल पूर्णांक max98371_dai_hw_params(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_pcm_hw_params *params,
		काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा max98371_priv *max98371 = snd_soc_component_get_drvdata(component);
	पूर्णांक blr_clk_ratio, ch_size, channels = params_channels(params);
	पूर्णांक rate = params_rate(params);

	चयन (params_क्रमmat(params)) अणु
	हाल SNDRV_PCM_FORMAT_S8:
		regmap_update_bits(max98371->regmap, MAX98371_FMT,
				MAX98371_FMT_MASK, MAX98371_DAI_CHANSZ_16);
		ch_size = 8;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S16_LE:
		regmap_update_bits(max98371->regmap, MAX98371_FMT,
				MAX98371_FMT_MASK, MAX98371_DAI_CHANSZ_16);
		ch_size = 16;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S24_LE:
		regmap_update_bits(max98371->regmap, MAX98371_FMT,
				MAX98371_FMT_MASK, MAX98371_DAI_CHANSZ_32);
		ch_size = 24;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S32_LE:
		regmap_update_bits(max98371->regmap, MAX98371_FMT,
				MAX98371_FMT_MASK, MAX98371_DAI_CHANSZ_32);
		ch_size = 32;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* BCLK/LRCLK ratio calculation */
	blr_clk_ratio = channels * ch_size;
	चयन (blr_clk_ratio) अणु
	हाल 32:
		regmap_update_bits(max98371->regmap,
			MAX98371_DAI_CLK,
			MAX98371_DAI_BSEL_MASK, MAX98371_DAI_BSEL_32);
		अवरोध;
	हाल 48:
		regmap_update_bits(max98371->regmap,
			MAX98371_DAI_CLK,
			MAX98371_DAI_BSEL_MASK, MAX98371_DAI_BSEL_48);
		अवरोध;
	हाल 64:
		regmap_update_bits(max98371->regmap,
			MAX98371_DAI_CLK,
			MAX98371_DAI_BSEL_MASK, MAX98371_DAI_BSEL_64);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (rate) अणु
	हाल 32000:
		regmap_update_bits(max98371->regmap,
			MAX98371_SPK_SR,
			MAX98371_SPK_SR_MASK, MAX98371_SPK_SR_32);
		अवरोध;
	हाल 44100:
		regmap_update_bits(max98371->regmap,
			MAX98371_SPK_SR,
			MAX98371_SPK_SR_MASK, MAX98371_SPK_SR_44);
		अवरोध;
	हाल 48000:
		regmap_update_bits(max98371->regmap,
			MAX98371_SPK_SR,
			MAX98371_SPK_SR_MASK, MAX98371_SPK_SR_48);
		अवरोध;
	हाल 88200:
		regmap_update_bits(max98371->regmap,
			MAX98371_SPK_SR,
			MAX98371_SPK_SR_MASK, MAX98371_SPK_SR_88);
		अवरोध;
	हाल 96000:
		regmap_update_bits(max98371->regmap,
			MAX98371_SPK_SR,
			MAX98371_SPK_SR_MASK, MAX98371_SPK_SR_96);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* enabling both the RX channels*/
	regmap_update_bits(max98371->regmap, MAX98371_MONOMIX_SRC,
			MAX98371_MONOMIX_SRC_MASK, MONOMIX_RX_0_1);
	regmap_update_bits(max98371->regmap, MAX98371_DAI_CHANNEL,
			MAX98371_CHANNEL_MASK, MAX98371_CHANNEL_MASK);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget max98371_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_DAC("DAC", शून्य, MAX98371_SPK_ENABLE, 0, 0),
	SND_SOC_DAPM_SUPPLY("Global Enable", MAX98371_GLOBAL_ENABLE,
		0, 0, शून्य, 0),
	SND_SOC_DAPM_OUTPUT("SPK_OUT"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route max98371_audio_map[] = अणु
	अणु"DAC", शून्य, "HiFi Playback"पूर्ण,
	अणु"SPK_OUT", शून्य, "DAC"पूर्ण,
	अणु"SPK_OUT", शून्य, "Global Enable"पूर्ण,
पूर्ण;

#घोषणा MAX98371_RATES SNDRV_PCM_RATE_8000_48000
#घोषणा MAX98371_FORMATS (SNDRV_PCM_FMTBIT_S8 | SNDRV_PCM_FMTBIT_S16_BE | \
		SNDRV_PCM_FMTBIT_S24_BE | SNDRV_PCM_FMTBIT_S32_BE)

अटल स्थिर काष्ठा snd_soc_dai_ops max98371_dai_ops = अणु
	.set_fmt = max98371_dai_set_fmt,
	.hw_params = max98371_dai_hw_params,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver max98371_dai[] = अणु
	अणु
		.name = "max98371-aif1",
		.playback = अणु
			.stream_name = "HiFi Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_8000_48000,
			.क्रमmats = MAX98371_FORMATS,
		पूर्ण,
		.ops = &max98371_dai_ops,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver max98371_component = अणु
	.controls		= max98371_snd_controls,
	.num_controls		= ARRAY_SIZE(max98371_snd_controls),
	.dapm_routes		= max98371_audio_map,
	.num_dapm_routes	= ARRAY_SIZE(max98371_audio_map),
	.dapm_widमाला_लो		= max98371_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(max98371_dapm_widमाला_लो),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config max98371_regmap = अणु
	.reg_bits         = 8,
	.val_bits         = 8,
	.max_रेजिस्टर     = MAX98371_VERSION,
	.reg_शेषs     = max98371_reg,
	.num_reg_शेषs = ARRAY_SIZE(max98371_reg),
	.अस्थिर_reg     = max98371_अस्थिर_रेजिस्टर,
	.पढ़ोable_reg     = max98371_पढ़ोable_रेजिस्टर,
	.cache_type       = REGCACHE_RBTREE,
पूर्ण;

अटल पूर्णांक max98371_i2c_probe(काष्ठा i2c_client *i2c,
		स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा max98371_priv *max98371;
	पूर्णांक ret, reg;

	max98371 = devm_kzalloc(&i2c->dev,
			माप(*max98371), GFP_KERNEL);
	अगर (!max98371)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, max98371);
	max98371->regmap = devm_regmap_init_i2c(i2c, &max98371_regmap);
	अगर (IS_ERR(max98371->regmap)) अणु
		ret = PTR_ERR(max98371->regmap);
		dev_err(&i2c->dev,
				"Failed to allocate regmap: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regmap_पढ़ो(max98371->regmap, MAX98371_VERSION, &reg);
	अगर (ret < 0) अणु
		dev_info(&i2c->dev, "device error %d\n", ret);
		वापस ret;
	पूर्ण
	dev_info(&i2c->dev, "device version %x\n", reg);

	ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev, &max98371_component,
			max98371_dai, ARRAY_SIZE(max98371_dai));
	अगर (ret < 0) अणु
		dev_err(&i2c->dev, "Failed to register component: %d\n", ret);
		वापस ret;
	पूर्ण
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id max98371_i2c_id[] = अणु
	अणु "max98371", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, max98371_i2c_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id max98371_of_match[] = अणु
	अणु .compatible = "maxim,max98371", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, max98371_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver max98371_i2c_driver = अणु
	.driver = अणु
		.name = "max98371",
		.of_match_table = of_match_ptr(max98371_of_match),
	पूर्ण,
	.probe  = max98371_i2c_probe,
	.id_table = max98371_i2c_id,
पूर्ण;

module_i2c_driver(max98371_i2c_driver);

MODULE_AUTHOR("anish kumar <yesanishhere@gmail.com>");
MODULE_DESCRIPTION("ALSA SoC MAX98371 driver");
MODULE_LICENSE("GPL");
