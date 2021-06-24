<शैली गुरु>
/*
 * ASoC codec driver क्रम spear platक्रमm
 *
 * sound/soc/codecs/sta529.c -- spear ALSA Soc codec driver
 *
 * Copyright (C) 2012 ST Microelectronics
 * Rajeev Kumar <rajeevkumar.linux@gmail.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/clk.h>
#समावेश <linux/init.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/pm.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#समावेश <sound/core.h>
#समावेश <sound/initval.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/tlv.h>

/* STA529 Register offsets */
#घोषणा	 STA529_FFXCFG0		0x00
#घोषणा	 STA529_FFXCFG1		0x01
#घोषणा	 STA529_MVOL		0x02
#घोषणा	 STA529_LVOL		0x03
#घोषणा	 STA529_RVOL		0x04
#घोषणा	 STA529_TTF0		0x05
#घोषणा	 STA529_TTF1		0x06
#घोषणा	 STA529_TTP0		0x07
#घोषणा	 STA529_TTP1		0x08
#घोषणा	 STA529_S2PCFG0		0x0A
#घोषणा	 STA529_S2PCFG1		0x0B
#घोषणा	 STA529_P2SCFG0		0x0C
#घोषणा	 STA529_P2SCFG1		0x0D
#घोषणा	 STA529_PLLCFG0		0x14
#घोषणा	 STA529_PLLCFG1		0x15
#घोषणा	 STA529_PLLCFG2		0x16
#घोषणा	 STA529_PLLCFG3		0x17
#घोषणा	 STA529_PLLPFE		0x18
#घोषणा	 STA529_PLLST		0x19
#घोषणा	 STA529_ADCCFG		0x1E /*mic_select*/
#घोषणा	 STA529_CKOCFG		0x1F
#घोषणा	 STA529_MISC		0x20
#घोषणा	 STA529_PADST0		0x21
#घोषणा	 STA529_PADST1		0x22
#घोषणा	 STA529_FFXST		0x23
#घोषणा	 STA529_PWMIN1		0x2D
#घोषणा	 STA529_PWMIN2		0x2E
#घोषणा	 STA529_POWST		0x32

#घोषणा STA529_MAX_REGISTER	0x32

#घोषणा STA529_RATES		(SNDRV_PCM_RATE_8000 | \
				SNDRV_PCM_RATE_11025 | \
				SNDRV_PCM_RATE_16000 | \
				SNDRV_PCM_RATE_22050 | \
				SNDRV_PCM_RATE_32000 | \
				SNDRV_PCM_RATE_44100 | \
				SNDRV_PCM_RATE_48000)

#घोषणा STA529_FORMAT		(SNDRV_PCM_FMTBIT_S16_LE | \
				SNDRV_PCM_FMTBIT_S24_LE | \
				SNDRV_PCM_FMTBIT_S32_LE)
#घोषणा	S2PC_VALUE		0x98
#घोषणा CLOCK_OUT		0x60
#घोषणा DATA_FORMAT_MSK		0x0E
#घोषणा LEFT_J_DATA_FORMAT	0x00
#घोषणा I2S_DATA_FORMAT		0x02
#घोषणा RIGHT_J_DATA_FORMAT	0x04
#घोषणा CODEC_MUTE_VAL		0x80

#घोषणा POWER_CNTLMSAK		0x40
#घोषणा POWER_STDBY		0x40
#घोषणा FFX_MASK		0x80
#घोषणा FFX_OFF			0x80
#घोषणा POWER_UP		0x00
#घोषणा FFX_CLK_ENB		0x01
#घोषणा FFX_CLK_DIS		0x00
#घोषणा FFX_CLK_MSK		0x01
#घोषणा PLAY_FREQ_RANGE_MSK	0x70
#घोषणा CAP_FREQ_RANGE_MSK	0x0C
#घोषणा PDATA_LEN_MSK		0xC0
#घोषणा BCLK_TO_FS_MSK		0x30
#घोषणा AUDIO_MUTE_MSK		0x80

अटल स्थिर काष्ठा reg_शेष sta529_reg_शेषs[] = अणु
	अणु 0,  0x35 पूर्ण,     /* R0   - FFX Configuration reg 0 */
	अणु 1,  0xc8 पूर्ण,     /* R1   - FFX Configuration reg 1 */
	अणु 2,  0x50 पूर्ण,     /* R2   - Master Volume */
	अणु 3,  0x00 पूर्ण,     /* R3   - Left Volume */
	अणु 4,  0x00 पूर्ण,     /* R4  -  Right Volume */
	अणु 10, 0xb2 पूर्ण,     /* R10  - S2P Config Reg 0 */
	अणु 11, 0x41 पूर्ण,     /* R11  - S2P Config Reg 1 */
	अणु 12, 0x92 पूर्ण,     /* R12  - P2S Config Reg 0 */
	अणु 13, 0x41 पूर्ण,     /* R13  - P2S Config Reg 1 */
	अणु 30, 0xd2 पूर्ण,     /* R30  - ADC Config Reg */
	अणु 31, 0x40 पूर्ण,     /* R31  - घड़ी Out Reg */
	अणु 32, 0x21 पूर्ण,     /* R32  - Misc Register */
पूर्ण;

काष्ठा sta529 अणु
	काष्ठा regmap *regmap;
पूर्ण;

अटल bool sta529_पढ़ोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु

	हाल STA529_FFXCFG0:
	हाल STA529_FFXCFG1:
	हाल STA529_MVOL:
	हाल STA529_LVOL:
	हाल STA529_RVOL:
	हाल STA529_S2PCFG0:
	हाल STA529_S2PCFG1:
	हाल STA529_P2SCFG0:
	हाल STA529_P2SCFG1:
	हाल STA529_ADCCFG:
	हाल STA529_CKOCFG:
	हाल STA529_MISC:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण


अटल स्थिर अक्षर *pwm_mode_text[] = अणु "Binary", "Headphone", "Ternary",
	"Phase-shift"पूर्ण;

अटल स्थिर DECLARE_TLV_DB_SCALE(out_gain_tlv, -9150, 50, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(master_vol_tlv, -12750, 50, 0);
अटल SOC_ENUM_SINGLE_DECL(pwm_src, STA529_FFXCFG1, 4, pwm_mode_text);

अटल स्थिर काष्ठा snd_kcontrol_new sta529_snd_controls[] = अणु
	SOC_DOUBLE_R_TLV("Digital Playback Volume", STA529_LVOL, STA529_RVOL, 0,
			127, 0, out_gain_tlv),
	SOC_SINGLE_TLV("Master Playback Volume", STA529_MVOL, 0, 127, 1,
			master_vol_tlv),
	SOC_ENUM("PWM Select", pwm_src),
पूर्ण;

अटल पूर्णांक sta529_set_bias_level(काष्ठा snd_soc_component *component, क्रमागत
		snd_soc_bias_level level)
अणु
	काष्ठा sta529 *sta529 = snd_soc_component_get_drvdata(component);

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
	हाल SND_SOC_BIAS_PREPARE:
		snd_soc_component_update_bits(component, STA529_FFXCFG0, POWER_CNTLMSAK,
				POWER_UP);
		snd_soc_component_update_bits(component, STA529_MISC,	FFX_CLK_MSK,
				FFX_CLK_ENB);
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF)
			regcache_sync(sta529->regmap);
		snd_soc_component_update_bits(component, STA529_FFXCFG0,
					POWER_CNTLMSAK, POWER_STDBY);
		/* Making FFX output to zero */
		snd_soc_component_update_bits(component, STA529_FFXCFG0, FFX_MASK,
				FFX_OFF);
		snd_soc_component_update_bits(component, STA529_MISC, FFX_CLK_MSK,
				FFX_CLK_DIS);
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		अवरोध;
	पूर्ण

	वापस 0;

पूर्ण

अटल पूर्णांक sta529_hw_params(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_pcm_hw_params *params,
		काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	पूर्णांक pdata, play_freq_val, record_freq_val;
	पूर्णांक bclk_to_fs_ratio;

	चयन (params_width(params)) अणु
	हाल 16:
		pdata = 1;
		bclk_to_fs_ratio = 0;
		अवरोध;
	हाल 24:
		pdata = 2;
		bclk_to_fs_ratio = 1;
		अवरोध;
	हाल 32:
		pdata = 3;
		bclk_to_fs_ratio = 2;
		अवरोध;
	शेष:
		dev_err(component->dev, "Unsupported format\n");
		वापस -EINVAL;
	पूर्ण

	चयन (params_rate(params)) अणु
	हाल 8000:
	हाल 11025:
		play_freq_val = 0;
		record_freq_val = 2;
		अवरोध;
	हाल 16000:
	हाल 22050:
		play_freq_val = 1;
		record_freq_val = 0;
		अवरोध;

	हाल 32000:
	हाल 44100:
	हाल 48000:
		play_freq_val = 2;
		record_freq_val = 0;
		अवरोध;
	शेष:
		dev_err(component->dev, "Unsupported rate\n");
		वापस -EINVAL;
	पूर्ण

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		snd_soc_component_update_bits(component, STA529_S2PCFG1, PDATA_LEN_MSK,
				pdata << 6);
		snd_soc_component_update_bits(component, STA529_S2PCFG1, BCLK_TO_FS_MSK,
				bclk_to_fs_ratio << 4);
		snd_soc_component_update_bits(component, STA529_MISC, PLAY_FREQ_RANGE_MSK,
				play_freq_val << 4);
	पूर्ण अन्यथा अणु
		snd_soc_component_update_bits(component, STA529_P2SCFG1, PDATA_LEN_MSK,
				pdata << 6);
		snd_soc_component_update_bits(component, STA529_P2SCFG1, BCLK_TO_FS_MSK,
				bclk_to_fs_ratio << 4);
		snd_soc_component_update_bits(component, STA529_MISC, CAP_FREQ_RANGE_MSK,
				record_freq_val << 2);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sta529_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	u8 val = 0;

	अगर (mute)
		val |= CODEC_MUTE_VAL;

	snd_soc_component_update_bits(dai->component, STA529_FFXCFG0, AUDIO_MUTE_MSK, val);

	वापस 0;
पूर्ण

अटल पूर्णांक sta529_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai, u32 fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	u8 mode = 0;

	/* पूर्णांकerface क्रमmat */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_LEFT_J:
		mode = LEFT_J_DATA_FORMAT;
		अवरोध;
	हाल SND_SOC_DAIFMT_I2S:
		mode = I2S_DATA_FORMAT;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		mode = RIGHT_J_DATA_FORMAT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, STA529_S2PCFG0, DATA_FORMAT_MSK, mode);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops sta529_dai_ops = अणु
	.hw_params	=	sta529_hw_params,
	.set_fmt	=	sta529_set_dai_fmt,
	.mute_stream	=	sta529_mute,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver sta529_dai = अणु
	.name = "sta529-audio",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = STA529_RATES,
		.क्रमmats = STA529_FORMAT,
	पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 2,
		.channels_max = 2,
		.rates = STA529_RATES,
		.क्रमmats = STA529_FORMAT,
	पूर्ण,
	.ops	= &sta529_dai_ops,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver sta529_component_driver = अणु
	.set_bias_level		= sta529_set_bias_level,
	.controls		= sta529_snd_controls,
	.num_controls		= ARRAY_SIZE(sta529_snd_controls),
	.suspend_bias_off	= 1,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config sta529_regmap = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = STA529_MAX_REGISTER,
	.पढ़ोable_reg = sta529_पढ़ोable,

	.cache_type = REGCACHE_RBTREE,
	.reg_शेषs = sta529_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(sta529_reg_शेषs),
पूर्ण;

अटल पूर्णांक sta529_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा sta529 *sta529;
	पूर्णांक ret;

	sta529 = devm_kzalloc(&i2c->dev, माप(काष्ठा sta529), GFP_KERNEL);
	अगर (!sta529)
		वापस -ENOMEM;

	sta529->regmap = devm_regmap_init_i2c(i2c, &sta529_regmap);
	अगर (IS_ERR(sta529->regmap)) अणु
		ret = PTR_ERR(sta529->regmap);
		dev_err(&i2c->dev, "Failed to allocate regmap: %d\n", ret);
		वापस ret;
	पूर्ण

	i2c_set_clientdata(i2c, sta529);

	ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev,
			&sta529_component_driver, &sta529_dai, 1);
	अगर (ret != 0)
		dev_err(&i2c->dev, "Failed to register CODEC: %d\n", ret);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id sta529_i2c_id[] = अणु
	अणु "sta529", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, sta529_i2c_id);

अटल स्थिर काष्ठा of_device_id sta529_of_match[] = अणु
	अणु .compatible = "st,sta529", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sta529_of_match);

अटल काष्ठा i2c_driver sta529_i2c_driver = अणु
	.driver = अणु
		.name = "sta529",
		.of_match_table = sta529_of_match,
	पूर्ण,
	.probe		= sta529_i2c_probe,
	.id_table	= sta529_i2c_id,
पूर्ण;

module_i2c_driver(sta529_i2c_driver);

MODULE_DESCRIPTION("ASoC STA529 codec driver");
MODULE_AUTHOR("Rajeev Kumar <rajeevkumar.linux@gmail.com>");
MODULE_LICENSE("GPL");
