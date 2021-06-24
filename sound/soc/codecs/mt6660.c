<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

// Copyright (c) 2019 MediaTek Inc.

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/delay.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>
#समावेश <sound/pcm_params.h>

#समावेश "mt6660.h"

काष्ठा reg_माप_प्रकारable अणु
	u32 addr;
	u8 size;
पूर्ण;

अटल स्थिर काष्ठा reg_माप_प्रकारable mt6660_reg_माप_प्रकारable[] = अणु
	अणु MT6660_REG_HPF1_COEF, 4 पूर्ण,
	अणु MT6660_REG_HPF2_COEF, 4 पूर्ण,
	अणु MT6660_REG_TDM_CFG3, 2 पूर्ण,
	अणु MT6660_REG_RESV17, 2 पूर्ण,
	अणु MT6660_REG_RESV23, 2 पूर्ण,
	अणु MT6660_REG_SIGMAX, 2 पूर्ण,
	अणु MT6660_REG_DEVID, 2 पूर्ण,
	अणु MT6660_REG_HCLIP_CTRL, 2 पूर्ण,
	अणु MT6660_REG_DA_GAIN, 2 पूर्ण,
पूर्ण;

अटल पूर्णांक mt6660_get_reg_size(uपूर्णांक32_t addr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(mt6660_reg_माप_प्रकारable); i++) अणु
		अगर (mt6660_reg_माप_प्रकारable[i].addr == addr)
			वापस mt6660_reg_माप_प्रकारable[i].size;
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक mt6660_reg_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	काष्ठा mt6660_chip *chip = context;
	पूर्णांक size = mt6660_get_reg_size(reg);
	u8 reg_data[4];
	पूर्णांक i, ret;

	क्रम (i = 0; i < size; i++)
		reg_data[size - i - 1] = (val >> (8 * i)) & 0xff;

	ret = i2c_smbus_ग_लिखो_i2c_block_data(chip->i2c, reg, size, reg_data);
	वापस ret;
पूर्ण

अटल पूर्णांक mt6660_reg_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक *val)
अणु
	काष्ठा mt6660_chip *chip = context;
	पूर्णांक size = mt6660_get_reg_size(reg);
	पूर्णांक i, ret;
	u8 data[4];
	u32 reg_data = 0;

	ret = i2c_smbus_पढ़ो_i2c_block_data(chip->i2c, reg, size, data);
	अगर (ret < 0)
		वापस ret;
	क्रम (i = 0; i < size; i++) अणु
		reg_data <<= 8;
		reg_data |= data[i];
	पूर्ण
	*val = reg_data;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा regmap_config mt6660_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 32,
	.reg_ग_लिखो = mt6660_reg_ग_लिखो,
	.reg_पढ़ो = mt6660_reg_पढ़ो,
पूर्ण;

अटल पूर्णांक mt6660_codec_dac_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	अगर (event == SND_SOC_DAPM_POST_PMU)
		usleep_range(1000, 1100);
	वापस 0;
पूर्ण

अटल पूर्णांक mt6660_codec_classd_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	पूर्णांक ret;

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		dev_dbg(component->dev,
			"%s: before classd turn on\n", __func__);
		/* config to adaptive mode */
		ret = snd_soc_component_update_bits(component,
			MT6660_REG_BST_CTRL, 0x03, 0x03);
		अगर (ret < 0) अणु
			dev_err(component->dev, "config mode adaptive fail\n");
			वापस ret;
		पूर्ण
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMU:
		/* voltage sensing enable */
		ret = snd_soc_component_update_bits(component,
			MT6660_REG_RESV7, 0x04, 0x04);
		अगर (ret < 0) अणु
			dev_err(component->dev,
				"enable voltage sensing fail\n");
			वापस ret;
		पूर्ण
		dev_dbg(component->dev, "Amp on\n");
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		dev_dbg(component->dev, "Amp off\n");
		/* voltage sensing disable */
		ret = snd_soc_component_update_bits(component,
			MT6660_REG_RESV7, 0x04, 0x00);
		अगर (ret < 0) अणु
			dev_err(component->dev,
				"disable voltage sensing fail\n");
			वापस ret;
		पूर्ण
		/* pop-noise improvement 1 */
		ret = snd_soc_component_update_bits(component,
			MT6660_REG_RESV10, 0x10, 0x10);
		अगर (ret < 0) अणु
			dev_err(component->dev,
				"pop-noise improvement 1 fail\n");
			वापस ret;
		पूर्ण
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		dev_dbg(component->dev,
			"%s: after classd turn off\n", __func__);
		/* pop-noise improvement 2 */
		ret = snd_soc_component_update_bits(component,
			MT6660_REG_RESV10, 0x10, 0x00);
		अगर (ret < 0) अणु
			dev_err(component->dev,
				"pop-noise improvement 2 fail\n");
			वापस ret;
		पूर्ण
		/* config to off mode */
		ret = snd_soc_component_update_bits(component,
			MT6660_REG_BST_CTRL, 0x03, 0x00);
		अगर (ret < 0) अणु
			dev_err(component->dev, "config mode off fail\n");
			वापस ret;
		पूर्ण
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget mt6660_component_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_DAC_E("DAC", शून्य, MT6660_REG_PLL_CFG1,
		0, 1, mt6660_codec_dac_event, SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_ADC("VI ADC", शून्य, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_PGA("PGA", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_OUT_DRV_E("ClassD", MT6660_REG_SYSTEM_CTRL, 2, 0,
			       शून्य, 0, mt6660_codec_classd_event,
			       SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			       SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_OUTPUT("OUTP"),
	SND_SOC_DAPM_OUTPUT("OUTN"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route mt6660_component_dapm_routes[] = अणु
	अणु "DAC", शून्य, "aif_playback" पूर्ण,
	अणु "PGA", शून्य, "DAC" पूर्ण,
	अणु "ClassD", शून्य, "PGA" पूर्ण,
	अणु "OUTP", शून्य, "ClassD" पूर्ण,
	अणु "OUTN", शून्य, "ClassD" पूर्ण,
	अणु "VI ADC", शून्य, "ClassD" पूर्ण,
	अणु "aif_capture", शून्य, "VI ADC" पूर्ण,
पूर्ण;

अटल पूर्णांक mt6660_component_get_volsw(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_kcontrol_component(kcontrol);
	काष्ठा mt6660_chip *chip = (काष्ठा mt6660_chip *)
		snd_soc_component_get_drvdata(component);

	ucontrol->value.पूर्णांकeger.value[0] = chip->chip_rev & 0x0f;
	वापस 0;
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(vol_ctl_tlv, -1155, 5, 0);

अटल स्थिर काष्ठा snd_kcontrol_new mt6660_component_snd_controls[] = अणु
	SOC_SINGLE_TLV("Digital Volume", MT6660_REG_VOL_CTRL, 0, 255,
			   1, vol_ctl_tlv),
	SOC_SINGLE("Hard Clip Switch", MT6660_REG_HCLIP_CTRL, 8, 1, 0),
	SOC_SINGLE("Clip Switch", MT6660_REG_SPS_CTRL, 0, 1, 0),
	SOC_SINGLE("Boost Mode", MT6660_REG_BST_CTRL, 0, 3, 0),
	SOC_SINGLE("DRE Switch", MT6660_REG_DRE_CTRL, 0, 1, 0),
	SOC_SINGLE("DC Protect Switch",	MT6660_REG_DC_PROTECT_CTRL, 3, 1, 0),
	SOC_SINGLE("Data Output Left Channel Selection",
		   MT6660_REG_DATAO_SEL, 3, 7, 0),
	SOC_SINGLE("Data Output Right Channel Selection",
		   MT6660_REG_DATAO_SEL, 0, 7, 0),
	SOC_SINGLE_EXT("T0 SEL", MT6660_REG_CALI_T0, 0, 7, 0,
		       snd_soc_get_volsw, शून्य),
	SOC_SINGLE_EXT("Chip Rev", MT6660_REG_DEVID, 8, 15, 0,
		       mt6660_component_get_volsw, शून्य),
पूर्ण;

अटल पूर्णांक _mt6660_chip_घातer_on(काष्ठा mt6660_chip *chip, पूर्णांक on_off)
अणु
	वापस regmap_ग_लिखो_bits(chip->regmap, MT6660_REG_SYSTEM_CTRL,
				 0x01, on_off ? 0x00 : 0x01);
पूर्ण

काष्ठा reg_table अणु
	uपूर्णांक32_t addr;
	uपूर्णांक32_t mask;
	uपूर्णांक32_t val;
पूर्ण;

अटल स्थिर काष्ठा reg_table mt6660_setting_table[] = अणु
	अणु 0x20, 0x80, 0x00 पूर्ण,
	अणु 0x30, 0x01, 0x00 पूर्ण,
	अणु 0x50, 0x1c, 0x04 पूर्ण,
	अणु 0xB1, 0x0c, 0x00 पूर्ण,
	अणु 0xD3, 0x03, 0x03 पूर्ण,
	अणु 0xE0, 0x01, 0x00 पूर्ण,
	अणु 0x98, 0x44, 0x04 पूर्ण,
	अणु 0xB9, 0xff, 0x82 पूर्ण,
	अणु 0xB7, 0x7777, 0x7273 पूर्ण,
	अणु 0xB6, 0x07, 0x03 पूर्ण,
	अणु 0x6B, 0xe0, 0x20 पूर्ण,
	अणु 0x07, 0xff, 0x70 पूर्ण,
	अणु 0xBB, 0xff, 0x20 पूर्ण,
	अणु 0x69, 0xff, 0x40 पूर्ण,
	अणु 0xBD, 0xffff, 0x17f8 पूर्ण,
	अणु 0x70, 0xff, 0x15 पूर्ण,
	अणु 0x7C, 0xff, 0x00 पूर्ण,
	अणु 0x46, 0xff, 0x1d पूर्ण,
	अणु 0x1A, 0xffffffff, 0x7fdb7ffe पूर्ण,
	अणु 0x1B, 0xffffffff, 0x7fdb7ffe पूर्ण,
	अणु 0x51, 0xff, 0x58 पूर्ण,
	अणु 0xA2, 0xff, 0xce पूर्ण,
	अणु 0x33, 0xffff, 0x7fff पूर्ण,
	अणु 0x4C, 0xffff, 0x0116 पूर्ण,
	अणु 0x16, 0x1800, 0x0800 पूर्ण,
	अणु 0x68, 0x1f, 0x07 पूर्ण,
पूर्ण;

अटल पूर्णांक mt6660_component_setting(काष्ठा snd_soc_component *component)
अणु
	काष्ठा mt6660_chip *chip = snd_soc_component_get_drvdata(component);
	पूर्णांक ret = 0;
	माप_प्रकार i = 0;

	ret = _mt6660_chip_घातer_on(chip, 1);
	अगर (ret < 0) अणु
		dev_err(component->dev, "%s chip power on failed\n", __func__);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(mt6660_setting_table); i++) अणु
		ret = snd_soc_component_update_bits(component,
				mt6660_setting_table[i].addr,
				mt6660_setting_table[i].mask,
				mt6660_setting_table[i].val);
		अगर (ret < 0) अणु
			dev_err(component->dev, "%s update 0x%02x failed\n",
				__func__, mt6660_setting_table[i].addr);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = _mt6660_chip_घातer_on(chip, 0);
	अगर (ret < 0) अणु
		dev_err(component->dev, "%s chip power off failed\n", __func__);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt6660_component_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा mt6660_chip *chip = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	dev_dbg(component->dev, "%s\n", __func__);
	snd_soc_component_init_regmap(component, chip->regmap);

	ret = mt6660_component_setting(component);
	अगर (ret < 0)
		dev_err(chip->dev, "mt6660 component setting failed\n");

	वापस ret;
पूर्ण

अटल व्योम mt6660_component_हटाओ(काष्ठा snd_soc_component *component)
अणु
	dev_dbg(component->dev, "%s\n", __func__);
	snd_soc_component_निकास_regmap(component);
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver mt6660_component_driver = अणु
	.probe = mt6660_component_probe,
	.हटाओ = mt6660_component_हटाओ,

	.controls = mt6660_component_snd_controls,
	.num_controls = ARRAY_SIZE(mt6660_component_snd_controls),
	.dapm_widमाला_लो = mt6660_component_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(mt6660_component_dapm_widमाला_लो),
	.dapm_routes = mt6660_component_dapm_routes,
	.num_dapm_routes = ARRAY_SIZE(mt6660_component_dapm_routes),

	.idle_bias_on = false, /* idle_bias_off = true */
पूर्ण;

अटल पूर्णांक mt6660_component_aअगर_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *hw_params, काष्ठा snd_soc_dai *dai)
अणु
	पूर्णांक word_len = params_physical_width(hw_params);
	पूर्णांक aud_bit = params_width(hw_params);
	u16 reg_data = 0;
	पूर्णांक ret;

	dev_dbg(dai->dev, "%s: ++\n", __func__);
	dev_dbg(dai->dev, "format: 0x%08x\n", params_क्रमmat(hw_params));
	dev_dbg(dai->dev, "rate: 0x%08x\n", params_rate(hw_params));
	dev_dbg(dai->dev, "word_len: %d, aud_bit: %d\n", word_len, aud_bit);
	अगर (word_len > 32 || word_len < 16) अणु
		dev_err(dai->dev, "not supported word length\n");
		वापस -ENOTSUPP;
	पूर्ण
	चयन (aud_bit) अणु
	हाल 16:
		reg_data = 3;
		अवरोध;
	हाल 18:
		reg_data = 2;
		अवरोध;
	हाल 20:
		reg_data = 1;
		अवरोध;
	हाल 24:
	हाल 32:
		reg_data = 0;
		अवरोध;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण
	ret = snd_soc_component_update_bits(dai->component,
		MT6660_REG_SERIAL_CFG1, 0xc0, (reg_data << 6));
	अगर (ret < 0) अणु
		dev_err(dai->dev, "config aud bit fail\n");
		वापस ret;
	पूर्ण
	ret = snd_soc_component_update_bits(dai->component,
		MT6660_REG_TDM_CFG3, 0x3f0, word_len << 4);
	अगर (ret < 0) अणु
		dev_err(dai->dev, "config word len fail\n");
		वापस ret;
	पूर्ण
	dev_dbg(dai->dev, "%s: --\n", __func__);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops mt6660_component_aअगर_ops = अणु
	.hw_params = mt6660_component_aअगर_hw_params,
पूर्ण;

#घोषणा STUB_RATES	SNDRV_PCM_RATE_8000_192000
#घोषणा STUB_FORMATS	(SNDRV_PCM_FMTBIT_S16_LE | \
			SNDRV_PCM_FMTBIT_U16_LE | \
			SNDRV_PCM_FMTBIT_S24_LE | \
			SNDRV_PCM_FMTBIT_U24_LE | \
			SNDRV_PCM_FMTBIT_S32_LE | \
			SNDRV_PCM_FMTBIT_U32_LE)

अटल काष्ठा snd_soc_dai_driver mt6660_codec_dai = अणु
	.name = "mt6660-aif",
	.playback = अणु
		.stream_name	= "aif_playback",
		.channels_min	= 1,
		.channels_max	= 2,
		.rates		= STUB_RATES,
		.क्रमmats	= STUB_FORMATS,
	पूर्ण,
	.capture = अणु
		.stream_name	= "aif_capture",
		.channels_min	= 1,
		.channels_max	= 2,
		.rates = STUB_RATES,
		.क्रमmats = STUB_FORMATS,
	पूर्ण,
	/* dai properties */
	.symmetric_rate = 1,
	.symmetric_channels = 1,
	.symmetric_sample_bits = 1,
	/* dai operations */
	.ops = &mt6660_component_aअगर_ops,
पूर्ण;

अटल पूर्णांक _mt6660_chip_id_check(काष्ठा mt6660_chip *chip)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;

	ret = regmap_पढ़ो(chip->regmap, MT6660_REG_DEVID, &val);
	अगर (ret < 0)
		वापस ret;
	val &= 0x0ff0;
	अगर (val != 0x00e0 && val != 0x01e0) अणु
		dev_err(chip->dev, "%s id(%x) not match\n", __func__, val);
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक _mt6660_chip_sw_reset(काष्ठा mt6660_chip *chip)
अणु
	पूर्णांक ret;

	/* turn on मुख्य pll first, then trigger reset */
	ret = regmap_ग_लिखो(chip->regmap, MT6660_REG_SYSTEM_CTRL, 0x00);
	अगर (ret < 0)
		वापस ret;
	ret = regmap_ग_लिखो(chip->regmap, MT6660_REG_SYSTEM_CTRL, 0x80);
	अगर (ret < 0)
		वापस ret;
	msleep(30);
	वापस 0;
पूर्ण

अटल पूर्णांक _mt6660_पढ़ो_chip_revision(काष्ठा mt6660_chip *chip)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;

	ret = regmap_पढ़ो(chip->regmap, MT6660_REG_DEVID, &val);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "get chip revision fail\n");
		वापस ret;
	पूर्ण
	chip->chip_rev = val&0xff;
	dev_info(chip->dev, "%s chip_rev = %x\n", __func__, chip->chip_rev);
	वापस 0;
पूर्ण

अटल पूर्णांक mt6660_i2c_probe(काष्ठा i2c_client *client,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा mt6660_chip *chip = शून्य;
	पूर्णांक ret;

	dev_dbg(&client->dev, "%s\n", __func__);
	chip = devm_kzalloc(&client->dev, माप(*chip), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;
	chip->i2c = client;
	chip->dev = &client->dev;
	mutex_init(&chip->io_lock);
	i2c_set_clientdata(client, chip);

	chip->regmap = devm_regmap_init(&client->dev,
		शून्य, chip, &mt6660_regmap_config);
	अगर (IS_ERR(chip->regmap)) अणु
		ret = PTR_ERR(chip->regmap);
		dev_err(&client->dev, "failed to initialise regmap: %d\n", ret);
		वापस ret;
	पूर्ण

	/* chip reset first */
	ret = _mt6660_chip_sw_reset(chip);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "chip reset fail\n");
		जाओ probe_fail;
	पूर्ण
	/* chip घातer on */
	ret = _mt6660_chip_घातer_on(chip, 1);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "chip power on 2 fail\n");
		जाओ probe_fail;
	पूर्ण
	/* chip devid check */
	ret = _mt6660_chip_id_check(chip);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "chip id check fail\n");
		जाओ probe_fail;
	पूर्ण
	/* chip revision get */
	ret = _mt6660_पढ़ो_chip_revision(chip);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "read chip revision fail\n");
		जाओ probe_fail;
	पूर्ण
	pm_runसमय_set_active(chip->dev);
	pm_runसमय_enable(chip->dev);

	ret = devm_snd_soc_रेजिस्टर_component(chip->dev,
					       &mt6660_component_driver,
					       &mt6660_codec_dai, 1);
	वापस ret;
probe_fail:
	_mt6660_chip_घातer_on(chip, 0);
	mutex_destroy(&chip->io_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक mt6660_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा mt6660_chip *chip = i2c_get_clientdata(client);

	pm_runसमय_disable(chip->dev);
	pm_runसमय_set_suspended(chip->dev);
	mutex_destroy(&chip->io_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused mt6660_i2c_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा mt6660_chip *chip = dev_get_drvdata(dev);

	dev_dbg(dev, "enter low power mode\n");
	वापस regmap_update_bits(chip->regmap,
		MT6660_REG_SYSTEM_CTRL, 0x01, 0x01);
पूर्ण

अटल पूर्णांक __maybe_unused mt6660_i2c_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा mt6660_chip *chip = dev_get_drvdata(dev);

	dev_dbg(dev, "exit low power mode\n");
	वापस regmap_update_bits(chip->regmap,
		MT6660_REG_SYSTEM_CTRL, 0x01, 0x00);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops mt6660_dev_pm_ops = अणु
	SET_RUNTIME_PM_OPS(mt6660_i2c_runसमय_suspend,
			   mt6660_i2c_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा of_device_id __maybe_unused mt6660_of_id[] = अणु
	अणु .compatible = "mediatek,mt6660",पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mt6660_of_id);

अटल स्थिर काष्ठा i2c_device_id mt6660_i2c_id[] = अणु
	अणु"mt6660", 0 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, mt6660_i2c_id);

अटल काष्ठा i2c_driver mt6660_i2c_driver = अणु
	.driver = अणु
		.name = "mt6660",
		.of_match_table = of_match_ptr(mt6660_of_id),
		.pm = &mt6660_dev_pm_ops,
	पूर्ण,
	.probe = mt6660_i2c_probe,
	.हटाओ = mt6660_i2c_हटाओ,
	.id_table = mt6660_i2c_id,
पूर्ण;
module_i2c_driver(mt6660_i2c_driver);

MODULE_AUTHOR("Jeff Chang <jeff_chang@richtek.com>");
MODULE_DESCRIPTION("MT6660 SPKAMP Driver");
MODULE_LICENSE("GPL");
MODULE_VERSION("1.0.8_G");
