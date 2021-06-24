<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// tfa9879.c  --  driver क्रम NXP Semiconductors TFA9879
//
// Copyright (C) 2014 Axentia Technologies AB
// Author: Peter Rosin <peda@axentia.se>

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>
#समावेश <sound/pcm_params.h>

#समावेश "tfa9879.h"

काष्ठा tfa9879_priv अणु
	काष्ठा regmap *regmap;
	पूर्णांक lsb_justअगरied;
पूर्ण;

अटल पूर्णांक tfa9879_hw_params(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *params,
			     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा tfa9879_priv *tfa9879 = snd_soc_component_get_drvdata(component);
	पूर्णांक fs;
	पूर्णांक i2s_set = 0;

	चयन (params_rate(params)) अणु
	हाल 8000:
		fs = TFA9879_I2S_FS_8000;
		अवरोध;
	हाल 11025:
		fs = TFA9879_I2S_FS_11025;
		अवरोध;
	हाल 12000:
		fs = TFA9879_I2S_FS_12000;
		अवरोध;
	हाल 16000:
		fs = TFA9879_I2S_FS_16000;
		अवरोध;
	हाल 22050:
		fs = TFA9879_I2S_FS_22050;
		अवरोध;
	हाल 24000:
		fs = TFA9879_I2S_FS_24000;
		अवरोध;
	हाल 32000:
		fs = TFA9879_I2S_FS_32000;
		अवरोध;
	हाल 44100:
		fs = TFA9879_I2S_FS_44100;
		अवरोध;
	हाल 48000:
		fs = TFA9879_I2S_FS_48000;
		अवरोध;
	हाल 64000:
		fs = TFA9879_I2S_FS_64000;
		अवरोध;
	हाल 88200:
		fs = TFA9879_I2S_FS_88200;
		अवरोध;
	हाल 96000:
		fs = TFA9879_I2S_FS_96000;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (params_width(params)) अणु
	हाल 16:
		i2s_set = TFA9879_I2S_SET_LSB_J_16;
		अवरोध;
	हाल 24:
		i2s_set = TFA9879_I2S_SET_LSB_J_24;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (tfa9879->lsb_justअगरied)
		snd_soc_component_update_bits(component,
					      TFA9879_SERIAL_INTERFACE_1,
					      TFA9879_I2S_SET_MASK,
					      i2s_set << TFA9879_I2S_SET_SHIFT);

	snd_soc_component_update_bits(component, TFA9879_SERIAL_INTERFACE_1,
				      TFA9879_I2S_FS_MASK,
				      fs << TFA9879_I2S_FS_SHIFT);
	वापस 0;
पूर्ण

अटल पूर्णांक tfa9879_mute_stream(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = dai->component;

	snd_soc_component_update_bits(component, TFA9879_MISC_CONTROL,
				      TFA9879_S_MUTE_MASK,
				      !!mute << TFA9879_S_MUTE_SHIFT);

	वापस 0;
पूर्ण

अटल पूर्णांक tfa9879_set_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा tfa9879_priv *tfa9879 = snd_soc_component_get_drvdata(component);
	पूर्णांक i2s_set;
	पूर्णांक sck_pol;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		sck_pol = TFA9879_SCK_POL_NORMAL;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		sck_pol = TFA9879_SCK_POL_INVERSE;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		tfa9879->lsb_justअगरied = 0;
		i2s_set = TFA9879_I2S_SET_I2S_24;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		tfa9879->lsb_justअगरied = 0;
		i2s_set = TFA9879_I2S_SET_MSB_J_24;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		tfa9879->lsb_justअगरied = 1;
		i2s_set = TFA9879_I2S_SET_LSB_J_24;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, TFA9879_SERIAL_INTERFACE_1,
				      TFA9879_SCK_POL_MASK,
				      sck_pol << TFA9879_SCK_POL_SHIFT);
	snd_soc_component_update_bits(component, TFA9879_SERIAL_INTERFACE_1,
				      TFA9879_I2S_SET_MASK,
				      i2s_set << TFA9879_I2S_SET_SHIFT);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा reg_शेष tfa9879_regs[] = अणु
	अणु TFA9879_DEVICE_CONTROL,	0x0000 पूर्ण, /* 0x00 */
	अणु TFA9879_SERIAL_INTERFACE_1,	0x0a18 पूर्ण, /* 0x01 */
	अणु TFA9879_PCM_IOM2_FORMAT_1,	0x0007 पूर्ण, /* 0x02 */
	अणु TFA9879_SERIAL_INTERFACE_2,	0x0a18 पूर्ण, /* 0x03 */
	अणु TFA9879_PCM_IOM2_FORMAT_2,	0x0007 पूर्ण, /* 0x04 */
	अणु TFA9879_EQUALIZER_A1,		0x59dd पूर्ण, /* 0x05 */
	अणु TFA9879_EQUALIZER_A2,		0xc63e पूर्ण, /* 0x06 */
	अणु TFA9879_EQUALIZER_B1,		0x651a पूर्ण, /* 0x07 */
	अणु TFA9879_EQUALIZER_B2,		0xe53e पूर्ण, /* 0x08 */
	अणु TFA9879_EQUALIZER_C1,		0x4616 पूर्ण, /* 0x09 */
	अणु TFA9879_EQUALIZER_C2,		0xd33e पूर्ण, /* 0x0a */
	अणु TFA9879_EQUALIZER_D1,		0x4df3 पूर्ण, /* 0x0b */
	अणु TFA9879_EQUALIZER_D2,		0xea3e पूर्ण, /* 0x0c */
	अणु TFA9879_EQUALIZER_E1,		0x5ee0 पूर्ण, /* 0x0d */
	अणु TFA9879_EQUALIZER_E2,		0xf93e पूर्ण, /* 0x0e */
	अणु TFA9879_BYPASS_CONTROL,	0x0093 पूर्ण, /* 0x0f */
	अणु TFA9879_DYNAMIC_RANGE_COMPR,	0x92ba पूर्ण, /* 0x10 */
	अणु TFA9879_BASS_TREBLE,		0x12a5 पूर्ण, /* 0x11 */
	अणु TFA9879_HIGH_PASS_FILTER,	0x0004 पूर्ण, /* 0x12 */
	अणु TFA9879_VOLUME_CONTROL,	0x10bd पूर्ण, /* 0x13 */
	अणु TFA9879_MISC_CONTROL,		0x0000 पूर्ण, /* 0x14 */
पूर्ण;

अटल bool tfa9879_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस reg == TFA9879_MISC_STATUS;
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(volume_tlv, -7050, 50, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(tb_gain_tlv, -1800, 200, 0);
अटल स्थिर अक्षर * स्थिर tb_freq_text[] = अणु
	"Low", "Mid", "High"
पूर्ण;
अटल स्थिर काष्ठा soc_क्रमागत treble_freq_क्रमागत =
	SOC_ENUM_SINGLE(TFA9879_BASS_TREBLE, TFA9879_F_TRBLE_SHIFT,
			ARRAY_SIZE(tb_freq_text), tb_freq_text);
अटल स्थिर काष्ठा soc_क्रमागत bass_freq_क्रमागत =
	SOC_ENUM_SINGLE(TFA9879_BASS_TREBLE, TFA9879_F_BASS_SHIFT,
			ARRAY_SIZE(tb_freq_text), tb_freq_text);

अटल स्थिर काष्ठा snd_kcontrol_new tfa9879_controls[] = अणु
	SOC_SINGLE_TLV("PCM Playback Volume", TFA9879_VOLUME_CONTROL,
		       TFA9879_VOL_SHIFT, 0xbd, 1, volume_tlv),
	SOC_SINGLE_TLV("Treble Volume", TFA9879_BASS_TREBLE,
		       TFA9879_G_TRBLE_SHIFT, 18, 0, tb_gain_tlv),
	SOC_SINGLE_TLV("Bass Volume", TFA9879_BASS_TREBLE,
		       TFA9879_G_BASS_SHIFT, 18, 0, tb_gain_tlv),
	SOC_ENUM("Treble Corner Freq", treble_freq_क्रमागत),
	SOC_ENUM("Bass Corner Freq", bass_freq_क्रमागत),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget tfa9879_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_AIF_IN("AIFINL", "Playback", 0, SND_SOC_NOPM, 0, 0),
SND_SOC_DAPM_AIF_IN("AIFINR", "Playback", 1, SND_SOC_NOPM, 0, 0),
SND_SOC_DAPM_DAC("DAC", शून्य, TFA9879_DEVICE_CONTROL, TFA9879_OPMODE_SHIFT, 0),
SND_SOC_DAPM_OUTPUT("LINEOUT"),
SND_SOC_DAPM_SUPPLY("POWER", TFA9879_DEVICE_CONTROL, TFA9879_POWERUP_SHIFT, 0,
		    शून्य, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route tfa9879_dapm_routes[] = अणु
	अणु "DAC", शून्य, "AIFINL" पूर्ण,
	अणु "DAC", शून्य, "AIFINR" पूर्ण,

	अणु "LINEOUT", शून्य, "DAC" पूर्ण,

	अणु "DAC", शून्य, "POWER" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver tfa9879_component = अणु
	.controls		= tfa9879_controls,
	.num_controls		= ARRAY_SIZE(tfa9879_controls),
	.dapm_widमाला_लो		= tfa9879_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(tfa9879_dapm_widमाला_लो),
	.dapm_routes		= tfa9879_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(tfa9879_dapm_routes),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config tfa9879_regmap = अणु
	.reg_bits = 8,
	.val_bits = 16,

	.अस्थिर_reg = tfa9879_अस्थिर_reg,
	.max_रेजिस्टर = TFA9879_MISC_STATUS,
	.reg_शेषs = tfa9879_regs,
	.num_reg_शेषs = ARRAY_SIZE(tfa9879_regs),
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops tfa9879_dai_ops = अणु
	.hw_params = tfa9879_hw_params,
	.mute_stream = tfa9879_mute_stream,
	.set_fmt = tfa9879_set_fmt,
	.no_capture_mute = 1,
पूर्ण;

#घोषणा TFA9879_RATES SNDRV_PCM_RATE_8000_96000

#घोषणा TFA9879_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | \
			 SNDRV_PCM_FMTBIT_S24_LE)

अटल काष्ठा snd_soc_dai_driver tfa9879_dai = अणु
	.name = "tfa9879-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = TFA9879_RATES,
		.क्रमmats = TFA9879_FORMATS, पूर्ण,
	.ops = &tfa9879_dai_ops,
पूर्ण;

अटल पूर्णांक tfa9879_i2c_probe(काष्ठा i2c_client *i2c)
अणु
	काष्ठा tfa9879_priv *tfa9879;
	पूर्णांक i;

	tfa9879 = devm_kzalloc(&i2c->dev, माप(*tfa9879), GFP_KERNEL);
	अगर (!tfa9879)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, tfa9879);

	tfa9879->regmap = devm_regmap_init_i2c(i2c, &tfa9879_regmap);
	अगर (IS_ERR(tfa9879->regmap))
		वापस PTR_ERR(tfa9879->regmap);

	/* Ensure the device is in reset state */
	क्रम (i = 0; i < ARRAY_SIZE(tfa9879_regs); i++)
		regmap_ग_लिखो(tfa9879->regmap,
			     tfa9879_regs[i].reg, tfa9879_regs[i].def);

	वापस devm_snd_soc_रेजिस्टर_component(&i2c->dev, &tfa9879_component,
					       &tfa9879_dai, 1);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id tfa9879_i2c_id[] = अणु
	अणु "tfa9879", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tfa9879_i2c_id);

अटल स्थिर काष्ठा of_device_id tfa9879_of_match[] = अणु
	अणु .compatible = "nxp,tfa9879", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tfa9879_of_match);

अटल काष्ठा i2c_driver tfa9879_i2c_driver = अणु
	.driver = अणु
		.name = "tfa9879",
		.of_match_table = tfa9879_of_match,
	पूर्ण,
	.probe_new = tfa9879_i2c_probe,
	.id_table = tfa9879_i2c_id,
पूर्ण;

module_i2c_driver(tfa9879_i2c_driver);

MODULE_DESCRIPTION("ASoC NXP Semiconductors TFA9879 driver");
MODULE_AUTHOR("Peter Rosin <peda@axentia.se>");
MODULE_LICENSE("GPL");
