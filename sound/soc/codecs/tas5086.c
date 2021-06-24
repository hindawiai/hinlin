<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * TAS5086 ASoC codec driver
 *
 * Copyright (c) 2013 Daniel Mack <zonque@gmail.com>
 *
 * TODO:
 *  - implement DAPM and input muxing
 *  - implement modulation limit
 *  - implement non-शेष PWM start
 *
 * Note that this chip has a very unusual रेजिस्टर layout, specअगरically
 * because the रेजिस्टरs are of unequal size, and multi-byte रेजिस्टरs
 * require bulk ग_लिखोs to take effect. Regmap करोes not support that kind
 * of devices.
 *
 * Currently, the driver करोes not touch any of the रेजिस्टरs >= 0x20, so
 * it करोesn't matter because the entire map can be accessed as 8-bit
 * array. In हाल more features will be added in the future
 * that require access to higher रेजिस्टरs, the entire regmap H/W I/O
 * routines have to be खोलो-coded.
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_gpपन.स>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>
#समावेश <sound/tas5086.h>

#घोषणा TAS5086_PCM_FORMATS (SNDRV_PCM_FMTBIT_S16_LE  |		\
			     SNDRV_PCM_FMTBIT_S20_3LE |		\
			     SNDRV_PCM_FMTBIT_S24_3LE)

#घोषणा TAS5086_PCM_RATES   (SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_44100  | \
			     SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_88200  | \
			     SNDRV_PCM_RATE_96000 | SNDRV_PCM_RATE_176400 | \
			     SNDRV_PCM_RATE_192000)

/*
 * TAS5086 रेजिस्टरs
 */
#घोषणा TAS5086_CLOCK_CONTROL		0x00	/* Clock control रेजिस्टर  */
#घोषणा TAS5086_CLOCK_RATE(val)		(val << 5)
#घोषणा TAS5086_CLOCK_RATE_MASK		(0x7 << 5)
#घोषणा TAS5086_CLOCK_RATIO(val)	(val << 2)
#घोषणा TAS5086_CLOCK_RATIO_MASK	(0x7 << 2)
#घोषणा TAS5086_CLOCK_SCLK_RATIO_48	(1 << 1)
#घोषणा TAS5086_CLOCK_VALID		(1 << 0)

#घोषणा TAS5086_DEEMPH_MASK		0x03
#घोषणा TAS5086_SOFT_MUTE_ALL		0x3f

#घोषणा TAS5086_DEV_ID			0x01	/* Device ID रेजिस्टर */
#घोषणा TAS5086_ERROR_STATUS		0x02	/* Error status रेजिस्टर */
#घोषणा TAS5086_SYS_CONTROL_1		0x03	/* System control रेजिस्टर 1 */
#घोषणा TAS5086_SERIAL_DATA_IF		0x04	/* Serial data पूर्णांकerface रेजिस्टर  */
#घोषणा TAS5086_SYS_CONTROL_2		0x05	/* System control रेजिस्टर 2 */
#घोषणा TAS5086_SOFT_MUTE		0x06	/* Soft mute रेजिस्टर */
#घोषणा TAS5086_MASTER_VOL		0x07	/* Master volume  */
#घोषणा TAS5086_CHANNEL_VOL(X)		(0x08 + (X))	/* Channel 1-6 volume */
#घोषणा TAS5086_VOLUME_CONTROL		0x09	/* Volume control रेजिस्टर */
#घोषणा TAS5086_MOD_LIMIT		0x10	/* Modulation limit रेजिस्टर */
#घोषणा TAS5086_PWM_START		0x18	/* PWM start रेजिस्टर */
#घोषणा TAS5086_SURROUND		0x19	/* Surround रेजिस्टर */
#घोषणा TAS5086_SPLIT_CAP_CHARGE	0x1a	/* Split cap अक्षरge period रेजिस्टर */
#घोषणा TAS5086_OSC_TRIM		0x1b	/* Oscillator trim रेजिस्टर */
#घोषणा TAS5086_BKNDERR 		0x1c
#घोषणा TAS5086_INPUT_MUX		0x20
#घोषणा TAS5086_PWM_OUTPUT_MUX		0x25

#घोषणा TAS5086_MAX_REGISTER		TAS5086_PWM_OUTPUT_MUX

#घोषणा TAS5086_PWM_START_MIDZ_FOR_START_1	(1 << 7)
#घोषणा TAS5086_PWM_START_MIDZ_FOR_START_2	(1 << 6)
#घोषणा TAS5086_PWM_START_CHANNEL_MASK		(0x3f)

/*
 * Default TAS5086 घातer-up configuration
 */
अटल स्थिर काष्ठा reg_शेष tas5086_reg_शेषs[] = अणु
	अणु 0x00,	0x6c पूर्ण,
	अणु 0x01,	0x03 पूर्ण,
	अणु 0x02,	0x00 पूर्ण,
	अणु 0x03,	0xa0 पूर्ण,
	अणु 0x04,	0x05 पूर्ण,
	अणु 0x05,	0x60 पूर्ण,
	अणु 0x06,	0x00 पूर्ण,
	अणु 0x07,	0xff पूर्ण,
	अणु 0x08,	0x30 पूर्ण,
	अणु 0x09,	0x30 पूर्ण,
	अणु 0x0a,	0x30 पूर्ण,
	अणु 0x0b,	0x30 पूर्ण,
	अणु 0x0c,	0x30 पूर्ण,
	अणु 0x0d,	0x30 पूर्ण,
	अणु 0x0e,	0xb1 पूर्ण,
	अणु 0x0f,	0x00 पूर्ण,
	अणु 0x10,	0x02 पूर्ण,
	अणु 0x11,	0x00 पूर्ण,
	अणु 0x12,	0x00 पूर्ण,
	अणु 0x13,	0x00 पूर्ण,
	अणु 0x14,	0x00 पूर्ण,
	अणु 0x15,	0x00 पूर्ण,
	अणु 0x16,	0x00 पूर्ण,
	अणु 0x17,	0x00 पूर्ण,
	अणु 0x18,	0x3f पूर्ण,
	अणु 0x19,	0x00 पूर्ण,
	अणु 0x1a,	0x18 पूर्ण,
	अणु 0x1b,	0x82 पूर्ण,
	अणु 0x1c,	0x05 पूर्ण,
पूर्ण;

अटल पूर्णांक tas5086_रेजिस्टर_size(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल TAS5086_CLOCK_CONTROL ... TAS5086_BKNDERR:
		वापस 1;
	हाल TAS5086_INPUT_MUX:
	हाल TAS5086_PWM_OUTPUT_MUX:
		वापस 4;
	पूर्ण

	dev_err(dev, "Unsupported register address: %d\n", reg);
	वापस 0;
पूर्ण

अटल bool tas5086_accessible_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल 0x0f:
	हाल 0x11 ... 0x17:
	हाल 0x1d ... 0x1f:
		वापस false;
	शेष:
		वापस true;
	पूर्ण
पूर्ण

अटल bool tas5086_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल TAS5086_DEV_ID:
	हाल TAS5086_ERROR_STATUS:
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool tas5086_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस tas5086_accessible_reg(dev, reg) && (reg != TAS5086_DEV_ID);
पूर्ण

अटल पूर्णांक tas5086_reg_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg,
			      अचिन्हित पूर्णांक value)
अणु
	काष्ठा i2c_client *client = context;
	अचिन्हित पूर्णांक i, size;
	uपूर्णांक8_t buf[5];
	पूर्णांक ret;

	size = tas5086_रेजिस्टर_size(&client->dev, reg);
	अगर (size == 0)
		वापस -EINVAL;

	buf[0] = reg;

	क्रम (i = size; i >= 1; --i) अणु
		buf[i] = value;
		value >>= 8;
	पूर्ण

	ret = i2c_master_send(client, buf, size + 1);
	अगर (ret == size + 1)
		वापस 0;
	अन्यथा अगर (ret < 0)
		वापस ret;
	अन्यथा
		वापस -EIO;
पूर्ण

अटल पूर्णांक tas5086_reg_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg,
			     अचिन्हित पूर्णांक *value)
अणु
	काष्ठा i2c_client *client = context;
	uपूर्णांक8_t send_buf, recv_buf[4];
	काष्ठा i2c_msg msgs[2];
	अचिन्हित पूर्णांक size;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	size = tas5086_रेजिस्टर_size(&client->dev, reg);
	अगर (size == 0)
		वापस -EINVAL;

	send_buf = reg;

	msgs[0].addr = client->addr;
	msgs[0].len = माप(send_buf);
	msgs[0].buf = &send_buf;
	msgs[0].flags = 0;

	msgs[1].addr = client->addr;
	msgs[1].len = size;
	msgs[1].buf = recv_buf;
	msgs[1].flags = I2C_M_RD;

	ret = i2c_transfer(client->adapter, msgs, ARRAY_SIZE(msgs));
	अगर (ret < 0)
		वापस ret;
	अन्यथा अगर (ret != ARRAY_SIZE(msgs))
		वापस -EIO;

	*value = 0;

	क्रम (i = 0; i < size; i++) अणु
		*value <<= 8;
		*value |= recv_buf[i];
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर अक्षर * स्थिर supply_names[] = अणु
	"dvdd", "avdd"
पूर्ण;

काष्ठा tas5086_निजी अणु
	काष्ठा regmap	*regmap;
	अचिन्हित पूर्णांक	mclk, sclk;
	अचिन्हित पूर्णांक	क्रमmat;
	bool		deemph;
	अचिन्हित पूर्णांक	अक्षरge_period;
	अचिन्हित पूर्णांक	pwm_start_mid_z;
	/* Current sample rate क्रम de-emphasis control */
	पूर्णांक		rate;
	/* GPIO driving Reset pin, अगर any */
	पूर्णांक		gpio_nreset;
	काष्ठा		regulator_bulk_data supplies[ARRAY_SIZE(supply_names)];
पूर्ण;

अटल पूर्णांक tas5086_deemph[] = अणु 0, 32000, 44100, 48000 पूर्ण;

अटल पूर्णांक tas5086_set_deemph(काष्ठा snd_soc_component *component)
अणु
	काष्ठा tas5086_निजी *priv = snd_soc_component_get_drvdata(component);
	पूर्णांक i, val = 0;

	अगर (priv->deemph) अणु
		क्रम (i = 0; i < ARRAY_SIZE(tas5086_deemph); i++) अणु
			अगर (tas5086_deemph[i] == priv->rate) अणु
				val = i;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस regmap_update_bits(priv->regmap, TAS5086_SYS_CONTROL_1,
				  TAS5086_DEEMPH_MASK, val);
पूर्ण

अटल पूर्णांक tas5086_get_deemph(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा tas5086_निजी *priv = snd_soc_component_get_drvdata(component);

	ucontrol->value.पूर्णांकeger.value[0] = priv->deemph;

	वापस 0;
पूर्ण

अटल पूर्णांक tas5086_put_deemph(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा tas5086_निजी *priv = snd_soc_component_get_drvdata(component);

	priv->deemph = ucontrol->value.पूर्णांकeger.value[0];

	वापस tas5086_set_deemph(component);
पूर्ण


अटल पूर्णांक tas5086_set_dai_sysclk(काष्ठा snd_soc_dai *codec_dai,
				  पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा tas5086_निजी *priv = snd_soc_component_get_drvdata(component);

	चयन (clk_id) अणु
	हाल TAS5086_CLK_IDX_MCLK:
		priv->mclk = freq;
		अवरोध;
	हाल TAS5086_CLK_IDX_SCLK:
		priv->sclk = freq;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tas5086_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai,
			       अचिन्हित पूर्णांक क्रमmat)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा tas5086_निजी *priv = snd_soc_component_get_drvdata(component);

	/* The TAS5086 can only be slave to all घड़ीs */
	अगर ((क्रमmat & SND_SOC_DAIFMT_MASTER_MASK) != SND_SOC_DAIFMT_CBS_CFS) अणु
		dev_err(component->dev, "Invalid clocking mode\n");
		वापस -EINVAL;
	पूर्ण

	/* we need to refer to the data क्रमmat from hw_params() */
	priv->क्रमmat = क्रमmat;

	वापस 0;
पूर्ण

अटल स्थिर पूर्णांक tas5086_sample_rates[] = अणु
	32000, 38000, 44100, 48000, 88200, 96000, 176400, 192000
पूर्ण;

अटल स्थिर पूर्णांक tas5086_ratios[] = अणु
	64, 128, 192, 256, 384, 512
पूर्ण;

अटल पूर्णांक index_in_array(स्थिर पूर्णांक *array, पूर्णांक len, पूर्णांक needle)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < len; i++)
		अगर (array[i] == needle)
			वापस i;

	वापस -ENOENT;
पूर्ण

अटल पूर्णांक tas5086_hw_params(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *params,
			     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा tas5086_निजी *priv = snd_soc_component_get_drvdata(component);
	पूर्णांक val;
	पूर्णांक ret;

	priv->rate = params_rate(params);

	/* Look up the sample rate and refer to the offset in the list */
	val = index_in_array(tas5086_sample_rates,
			     ARRAY_SIZE(tas5086_sample_rates), priv->rate);

	अगर (val < 0) अणु
		dev_err(component->dev, "Invalid sample rate\n");
		वापस -EINVAL;
	पूर्ण

	ret = regmap_update_bits(priv->regmap, TAS5086_CLOCK_CONTROL,
				 TAS5086_CLOCK_RATE_MASK,
				 TAS5086_CLOCK_RATE(val));
	अगर (ret < 0)
		वापस ret;

	/* MCLK / Fs ratio */
	val = index_in_array(tas5086_ratios, ARRAY_SIZE(tas5086_ratios),
			     priv->mclk / priv->rate);
	अगर (val < 0) अणु
		dev_err(component->dev, "Invalid MCLK / Fs ratio\n");
		वापस -EINVAL;
	पूर्ण

	ret = regmap_update_bits(priv->regmap, TAS5086_CLOCK_CONTROL,
				 TAS5086_CLOCK_RATIO_MASK,
				 TAS5086_CLOCK_RATIO(val));
	अगर (ret < 0)
		वापस ret;


	ret = regmap_update_bits(priv->regmap, TAS5086_CLOCK_CONTROL,
				 TAS5086_CLOCK_SCLK_RATIO_48,
				 (priv->sclk == 48 * priv->rate) ? 
					TAS5086_CLOCK_SCLK_RATIO_48 : 0);
	अगर (ret < 0)
		वापस ret;

	/*
	 * The chip has a very unituitive रेजिस्टर mapping and muxes inक्रमmation
	 * about data क्रमmat and sample depth पूर्णांकo the same रेजिस्टर, but not on
	 * a logical bit-boundary. Hence, we have to refer to the क्रमmat passed
	 * in the set_dai_fmt() callback and set up everything from here.
	 *
	 * First, determine the 'base' value, using the क्रमmat ...
	 */
	चयन (priv->क्रमmat & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_RIGHT_J:
		val = 0x00;
		अवरोध;
	हाल SND_SOC_DAIFMT_I2S:
		val = 0x03;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		val = 0x06;
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid DAI format\n");
		वापस -EINVAL;
	पूर्ण

	/* ... then add the offset क्रम the sample bit depth. */
	चयन (params_width(params)) अणु
        हाल 16:
		val += 0;
                अवरोध;
	हाल 20:
		val += 1;
		अवरोध;
	हाल 24:
		val += 2;
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid bit width\n");
		वापस -EINVAL;
	पूर्ण

	ret = regmap_ग_लिखो(priv->regmap, TAS5086_SERIAL_DATA_IF, val);
	अगर (ret < 0)
		वापस ret;

	/* घड़ी is considered valid now */
	ret = regmap_update_bits(priv->regmap, TAS5086_CLOCK_CONTROL,
				 TAS5086_CLOCK_VALID, TAS5086_CLOCK_VALID);
	अगर (ret < 0)
		वापस ret;

	वापस tas5086_set_deemph(component);
पूर्ण

अटल पूर्णांक tas5086_mute_stream(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक stream)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा tas5086_निजी *priv = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक val = 0;

	अगर (mute)
		val = TAS5086_SOFT_MUTE_ALL;

	वापस regmap_ग_लिखो(priv->regmap, TAS5086_SOFT_MUTE, val);
पूर्ण

अटल व्योम tas5086_reset(काष्ठा tas5086_निजी *priv)
अणु
	अगर (gpio_is_valid(priv->gpio_nreset)) अणु
		/* Reset codec - minimum निश्चितion समय is 400ns */
		gpio_direction_output(priv->gpio_nreset, 0);
		udelay(1);
		gpio_set_value(priv->gpio_nreset, 1);

		/* Codec needs ~15ms to wake up */
		msleep(15);
	पूर्ण
पूर्ण

/* अक्षरge period values in microseconds */
अटल स्थिर पूर्णांक tas5086_अक्षरge_period[] = अणु
	  13000,  16900,   23400,   31200,   41600,   54600,   72800,   96200,
	 130000, 156000,  234000,  312000,  416000,  546000,  728000,  962000,
	1300000, 169000, 2340000, 3120000, 4160000, 5460000, 7280000, 9620000,
पूर्ण;

अटल पूर्णांक tas5086_init(काष्ठा device *dev, काष्ठा tas5086_निजी *priv)
अणु
	पूर्णांक ret, i;

	/*
	 * If any of the channels is configured to start in Mid-Z mode,
	 * configure 'part 1' of the PWM starts to use Mid-Z, and tell
	 * all configured mid-z channels to start under 'part 1'.
	 */
	अगर (priv->pwm_start_mid_z)
		regmap_ग_लिखो(priv->regmap, TAS5086_PWM_START,
			     TAS5086_PWM_START_MIDZ_FOR_START_1 |
				priv->pwm_start_mid_z);

	/* lookup and set split-capacitor अक्षरge period */
	अगर (priv->अक्षरge_period == 0) अणु
		regmap_ग_लिखो(priv->regmap, TAS5086_SPLIT_CAP_CHARGE, 0);
	पूर्ण अन्यथा अणु
		i = index_in_array(tas5086_अक्षरge_period,
				   ARRAY_SIZE(tas5086_अक्षरge_period),
				   priv->अक्षरge_period);
		अगर (i >= 0)
			regmap_ग_लिखो(priv->regmap, TAS5086_SPLIT_CAP_CHARGE,
				     i + 0x08);
		अन्यथा
			dev_warn(dev,
				 "Invalid split-cap charge period of %d ns.\n",
				 priv->अक्षरge_period);
	पूर्ण

	/* enable factory trim */
	ret = regmap_ग_लिखो(priv->regmap, TAS5086_OSC_TRIM, 0x00);
	अगर (ret < 0)
		वापस ret;

	/* start all channels */
	ret = regmap_ग_लिखो(priv->regmap, TAS5086_SYS_CONTROL_2, 0x20);
	अगर (ret < 0)
		वापस ret;

	/* mute all channels क्रम now */
	ret = regmap_ग_लिखो(priv->regmap, TAS5086_SOFT_MUTE,
			   TAS5086_SOFT_MUTE_ALL);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

/* TAS5086 controls */
अटल स्थिर DECLARE_TLV_DB_SCALE(tas5086_dac_tlv, -10350, 50, 1);

अटल स्थिर काष्ठा snd_kcontrol_new tas5086_controls[] = अणु
	SOC_SINGLE_TLV("Master Playback Volume", TAS5086_MASTER_VOL,
		       0, 0xff, 1, tas5086_dac_tlv),
	SOC_DOUBLE_R_TLV("Channel 1/2 Playback Volume",
			 TAS5086_CHANNEL_VOL(0), TAS5086_CHANNEL_VOL(1),
			 0, 0xff, 1, tas5086_dac_tlv),
	SOC_DOUBLE_R_TLV("Channel 3/4 Playback Volume",
			 TAS5086_CHANNEL_VOL(2), TAS5086_CHANNEL_VOL(3),
			 0, 0xff, 1, tas5086_dac_tlv),
	SOC_DOUBLE_R_TLV("Channel 5/6 Playback Volume",
			 TAS5086_CHANNEL_VOL(4), TAS5086_CHANNEL_VOL(5),
			 0, 0xff, 1, tas5086_dac_tlv),
	SOC_SINGLE_BOOL_EXT("De-emphasis Switch", 0,
			    tas5086_get_deemph, tas5086_put_deemph),
पूर्ण;

/* Input mux controls */
अटल स्थिर अक्षर *tas5086_dapm_sdin_texts[] =
अणु
	"SDIN1-L", "SDIN1-R", "SDIN2-L", "SDIN2-R",
	"SDIN3-L", "SDIN3-R", "Ground (0)", "nc"
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत tas5086_dapm_input_mux_क्रमागत[] = अणु
	SOC_ENUM_SINGLE(TAS5086_INPUT_MUX, 20, 8, tas5086_dapm_sdin_texts),
	SOC_ENUM_SINGLE(TAS5086_INPUT_MUX, 16, 8, tas5086_dapm_sdin_texts),
	SOC_ENUM_SINGLE(TAS5086_INPUT_MUX, 12, 8, tas5086_dapm_sdin_texts),
	SOC_ENUM_SINGLE(TAS5086_INPUT_MUX, 8,  8, tas5086_dapm_sdin_texts),
	SOC_ENUM_SINGLE(TAS5086_INPUT_MUX, 4,  8, tas5086_dapm_sdin_texts),
	SOC_ENUM_SINGLE(TAS5086_INPUT_MUX, 0,  8, tas5086_dapm_sdin_texts),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new tas5086_dapm_input_mux_controls[] = अणु
	SOC_DAPM_ENUM("Channel 1 input", tas5086_dapm_input_mux_क्रमागत[0]),
	SOC_DAPM_ENUM("Channel 2 input", tas5086_dapm_input_mux_क्रमागत[1]),
	SOC_DAPM_ENUM("Channel 3 input", tas5086_dapm_input_mux_क्रमागत[2]),
	SOC_DAPM_ENUM("Channel 4 input", tas5086_dapm_input_mux_क्रमागत[3]),
	SOC_DAPM_ENUM("Channel 5 input", tas5086_dapm_input_mux_क्रमागत[4]),
	SOC_DAPM_ENUM("Channel 6 input", tas5086_dapm_input_mux_क्रमागत[5]),
पूर्ण;

/* Output mux controls */
अटल स्थिर अक्षर *tas5086_dapm_channel_texts[] =
	अणु "Channel 1 Mux", "Channel 2 Mux", "Channel 3 Mux",
	  "Channel 4 Mux", "Channel 5 Mux", "Channel 6 Mux" पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत tas5086_dapm_output_mux_क्रमागत[] = अणु
	SOC_ENUM_SINGLE(TAS5086_PWM_OUTPUT_MUX, 20, 6, tas5086_dapm_channel_texts),
	SOC_ENUM_SINGLE(TAS5086_PWM_OUTPUT_MUX, 16, 6, tas5086_dapm_channel_texts),
	SOC_ENUM_SINGLE(TAS5086_PWM_OUTPUT_MUX, 12, 6, tas5086_dapm_channel_texts),
	SOC_ENUM_SINGLE(TAS5086_PWM_OUTPUT_MUX, 8,  6, tas5086_dapm_channel_texts),
	SOC_ENUM_SINGLE(TAS5086_PWM_OUTPUT_MUX, 4,  6, tas5086_dapm_channel_texts),
	SOC_ENUM_SINGLE(TAS5086_PWM_OUTPUT_MUX, 0,  6, tas5086_dapm_channel_texts),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new tas5086_dapm_output_mux_controls[] = अणु
	SOC_DAPM_ENUM("PWM1 Output", tas5086_dapm_output_mux_क्रमागत[0]),
	SOC_DAPM_ENUM("PWM2 Output", tas5086_dapm_output_mux_क्रमागत[1]),
	SOC_DAPM_ENUM("PWM3 Output", tas5086_dapm_output_mux_क्रमागत[2]),
	SOC_DAPM_ENUM("PWM4 Output", tas5086_dapm_output_mux_क्रमागत[3]),
	SOC_DAPM_ENUM("PWM5 Output", tas5086_dapm_output_mux_क्रमागत[4]),
	SOC_DAPM_ENUM("PWM6 Output", tas5086_dapm_output_mux_क्रमागत[5]),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget tas5086_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_INPUT("SDIN1-L"),
	SND_SOC_DAPM_INPUT("SDIN1-R"),
	SND_SOC_DAPM_INPUT("SDIN2-L"),
	SND_SOC_DAPM_INPUT("SDIN2-R"),
	SND_SOC_DAPM_INPUT("SDIN3-L"),
	SND_SOC_DAPM_INPUT("SDIN3-R"),
	SND_SOC_DAPM_INPUT("SDIN4-L"),
	SND_SOC_DAPM_INPUT("SDIN4-R"),

	SND_SOC_DAPM_OUTPUT("PWM1"),
	SND_SOC_DAPM_OUTPUT("PWM2"),
	SND_SOC_DAPM_OUTPUT("PWM3"),
	SND_SOC_DAPM_OUTPUT("PWM4"),
	SND_SOC_DAPM_OUTPUT("PWM5"),
	SND_SOC_DAPM_OUTPUT("PWM6"),

	SND_SOC_DAPM_MUX("Channel 1 Mux", SND_SOC_NOPM, 0, 0,
			 &tas5086_dapm_input_mux_controls[0]),
	SND_SOC_DAPM_MUX("Channel 2 Mux", SND_SOC_NOPM, 0, 0,
			 &tas5086_dapm_input_mux_controls[1]),
	SND_SOC_DAPM_MUX("Channel 3 Mux", SND_SOC_NOPM, 0, 0,
			 &tas5086_dapm_input_mux_controls[2]),
	SND_SOC_DAPM_MUX("Channel 4 Mux", SND_SOC_NOPM, 0, 0,
			 &tas5086_dapm_input_mux_controls[3]),
	SND_SOC_DAPM_MUX("Channel 5 Mux", SND_SOC_NOPM, 0, 0,
			 &tas5086_dapm_input_mux_controls[4]),
	SND_SOC_DAPM_MUX("Channel 6 Mux", SND_SOC_NOPM, 0, 0,
			 &tas5086_dapm_input_mux_controls[5]),

	SND_SOC_DAPM_MUX("PWM1 Mux", SND_SOC_NOPM, 0, 0,
			 &tas5086_dapm_output_mux_controls[0]),
	SND_SOC_DAPM_MUX("PWM2 Mux", SND_SOC_NOPM, 0, 0,
			 &tas5086_dapm_output_mux_controls[1]),
	SND_SOC_DAPM_MUX("PWM3 Mux", SND_SOC_NOPM, 0, 0,
			 &tas5086_dapm_output_mux_controls[2]),
	SND_SOC_DAPM_MUX("PWM4 Mux", SND_SOC_NOPM, 0, 0,
			 &tas5086_dapm_output_mux_controls[3]),
	SND_SOC_DAPM_MUX("PWM5 Mux", SND_SOC_NOPM, 0, 0,
			 &tas5086_dapm_output_mux_controls[4]),
	SND_SOC_DAPM_MUX("PWM6 Mux", SND_SOC_NOPM, 0, 0,
			 &tas5086_dapm_output_mux_controls[5]),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route tas5086_dapm_routes[] = अणु
	/* SDIN inमाला_दो -> channel muxes */
	अणु "Channel 1 Mux", "SDIN1-L", "SDIN1-L" पूर्ण,
	अणु "Channel 1 Mux", "SDIN1-R", "SDIN1-R" पूर्ण,
	अणु "Channel 1 Mux", "SDIN2-L", "SDIN2-L" पूर्ण,
	अणु "Channel 1 Mux", "SDIN2-R", "SDIN2-R" पूर्ण,
	अणु "Channel 1 Mux", "SDIN3-L", "SDIN3-L" पूर्ण,
	अणु "Channel 1 Mux", "SDIN3-R", "SDIN3-R" पूर्ण,

	अणु "Channel 2 Mux", "SDIN1-L", "SDIN1-L" पूर्ण,
	अणु "Channel 2 Mux", "SDIN1-R", "SDIN1-R" पूर्ण,
	अणु "Channel 2 Mux", "SDIN2-L", "SDIN2-L" पूर्ण,
	अणु "Channel 2 Mux", "SDIN2-R", "SDIN2-R" पूर्ण,
	अणु "Channel 2 Mux", "SDIN3-L", "SDIN3-L" पूर्ण,
	अणु "Channel 2 Mux", "SDIN3-R", "SDIN3-R" पूर्ण,

	अणु "Channel 2 Mux", "SDIN1-L", "SDIN1-L" पूर्ण,
	अणु "Channel 2 Mux", "SDIN1-R", "SDIN1-R" पूर्ण,
	अणु "Channel 2 Mux", "SDIN2-L", "SDIN2-L" पूर्ण,
	अणु "Channel 2 Mux", "SDIN2-R", "SDIN2-R" पूर्ण,
	अणु "Channel 2 Mux", "SDIN3-L", "SDIN3-L" पूर्ण,
	अणु "Channel 2 Mux", "SDIN3-R", "SDIN3-R" पूर्ण,

	अणु "Channel 3 Mux", "SDIN1-L", "SDIN1-L" पूर्ण,
	अणु "Channel 3 Mux", "SDIN1-R", "SDIN1-R" पूर्ण,
	अणु "Channel 3 Mux", "SDIN2-L", "SDIN2-L" पूर्ण,
	अणु "Channel 3 Mux", "SDIN2-R", "SDIN2-R" पूर्ण,
	अणु "Channel 3 Mux", "SDIN3-L", "SDIN3-L" पूर्ण,
	अणु "Channel 3 Mux", "SDIN3-R", "SDIN3-R" पूर्ण,

	अणु "Channel 4 Mux", "SDIN1-L", "SDIN1-L" पूर्ण,
	अणु "Channel 4 Mux", "SDIN1-R", "SDIN1-R" पूर्ण,
	अणु "Channel 4 Mux", "SDIN2-L", "SDIN2-L" पूर्ण,
	अणु "Channel 4 Mux", "SDIN2-R", "SDIN2-R" पूर्ण,
	अणु "Channel 4 Mux", "SDIN3-L", "SDIN3-L" पूर्ण,
	अणु "Channel 4 Mux", "SDIN3-R", "SDIN3-R" पूर्ण,

	अणु "Channel 5 Mux", "SDIN1-L", "SDIN1-L" पूर्ण,
	अणु "Channel 5 Mux", "SDIN1-R", "SDIN1-R" पूर्ण,
	अणु "Channel 5 Mux", "SDIN2-L", "SDIN2-L" पूर्ण,
	अणु "Channel 5 Mux", "SDIN2-R", "SDIN2-R" पूर्ण,
	अणु "Channel 5 Mux", "SDIN3-L", "SDIN3-L" पूर्ण,
	अणु "Channel 5 Mux", "SDIN3-R", "SDIN3-R" पूर्ण,

	अणु "Channel 6 Mux", "SDIN1-L", "SDIN1-L" पूर्ण,
	अणु "Channel 6 Mux", "SDIN1-R", "SDIN1-R" पूर्ण,
	अणु "Channel 6 Mux", "SDIN2-L", "SDIN2-L" पूर्ण,
	अणु "Channel 6 Mux", "SDIN2-R", "SDIN2-R" पूर्ण,
	अणु "Channel 6 Mux", "SDIN3-L", "SDIN3-L" पूर्ण,
	अणु "Channel 6 Mux", "SDIN3-R", "SDIN3-R" पूर्ण,

	/* Channel muxes -> PWM muxes */
	अणु "PWM1 Mux", "Channel 1 Mux", "Channel 1 Mux" पूर्ण,
	अणु "PWM2 Mux", "Channel 1 Mux", "Channel 1 Mux" पूर्ण,
	अणु "PWM3 Mux", "Channel 1 Mux", "Channel 1 Mux" पूर्ण,
	अणु "PWM4 Mux", "Channel 1 Mux", "Channel 1 Mux" पूर्ण,
	अणु "PWM5 Mux", "Channel 1 Mux", "Channel 1 Mux" पूर्ण,
	अणु "PWM6 Mux", "Channel 1 Mux", "Channel 1 Mux" पूर्ण,

	अणु "PWM1 Mux", "Channel 2 Mux", "Channel 2 Mux" पूर्ण,
	अणु "PWM2 Mux", "Channel 2 Mux", "Channel 2 Mux" पूर्ण,
	अणु "PWM3 Mux", "Channel 2 Mux", "Channel 2 Mux" पूर्ण,
	अणु "PWM4 Mux", "Channel 2 Mux", "Channel 2 Mux" पूर्ण,
	अणु "PWM5 Mux", "Channel 2 Mux", "Channel 2 Mux" पूर्ण,
	अणु "PWM6 Mux", "Channel 2 Mux", "Channel 2 Mux" पूर्ण,

	अणु "PWM1 Mux", "Channel 3 Mux", "Channel 3 Mux" पूर्ण,
	अणु "PWM2 Mux", "Channel 3 Mux", "Channel 3 Mux" पूर्ण,
	अणु "PWM3 Mux", "Channel 3 Mux", "Channel 3 Mux" पूर्ण,
	अणु "PWM4 Mux", "Channel 3 Mux", "Channel 3 Mux" पूर्ण,
	अणु "PWM5 Mux", "Channel 3 Mux", "Channel 3 Mux" पूर्ण,
	अणु "PWM6 Mux", "Channel 3 Mux", "Channel 3 Mux" पूर्ण,

	अणु "PWM1 Mux", "Channel 4 Mux", "Channel 4 Mux" पूर्ण,
	अणु "PWM2 Mux", "Channel 4 Mux", "Channel 4 Mux" पूर्ण,
	अणु "PWM3 Mux", "Channel 4 Mux", "Channel 4 Mux" पूर्ण,
	अणु "PWM4 Mux", "Channel 4 Mux", "Channel 4 Mux" पूर्ण,
	अणु "PWM5 Mux", "Channel 4 Mux", "Channel 4 Mux" पूर्ण,
	अणु "PWM6 Mux", "Channel 4 Mux", "Channel 4 Mux" पूर्ण,

	अणु "PWM1 Mux", "Channel 5 Mux", "Channel 5 Mux" पूर्ण,
	अणु "PWM2 Mux", "Channel 5 Mux", "Channel 5 Mux" पूर्ण,
	अणु "PWM3 Mux", "Channel 5 Mux", "Channel 5 Mux" पूर्ण,
	अणु "PWM4 Mux", "Channel 5 Mux", "Channel 5 Mux" पूर्ण,
	अणु "PWM5 Mux", "Channel 5 Mux", "Channel 5 Mux" पूर्ण,
	अणु "PWM6 Mux", "Channel 5 Mux", "Channel 5 Mux" पूर्ण,

	अणु "PWM1 Mux", "Channel 6 Mux", "Channel 6 Mux" पूर्ण,
	अणु "PWM2 Mux", "Channel 6 Mux", "Channel 6 Mux" पूर्ण,
	अणु "PWM3 Mux", "Channel 6 Mux", "Channel 6 Mux" पूर्ण,
	अणु "PWM4 Mux", "Channel 6 Mux", "Channel 6 Mux" पूर्ण,
	अणु "PWM5 Mux", "Channel 6 Mux", "Channel 6 Mux" पूर्ण,
	अणु "PWM6 Mux", "Channel 6 Mux", "Channel 6 Mux" पूर्ण,

	/* The PWM muxes are directly connected to the PWM outमाला_दो */
	अणु "PWM1", शून्य, "PWM1 Mux" पूर्ण,
	अणु "PWM2", शून्य, "PWM2 Mux" पूर्ण,
	अणु "PWM3", शून्य, "PWM3 Mux" पूर्ण,
	अणु "PWM4", शून्य, "PWM4 Mux" पूर्ण,
	अणु "PWM5", शून्य, "PWM5 Mux" पूर्ण,
	अणु "PWM6", शून्य, "PWM6 Mux" पूर्ण,

पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops tas5086_dai_ops = अणु
	.hw_params	= tas5086_hw_params,
	.set_sysclk	= tas5086_set_dai_sysclk,
	.set_fmt	= tas5086_set_dai_fmt,
	.mute_stream	= tas5086_mute_stream,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver tas5086_dai = अणु
	.name = "tas5086-hifi",
	.playback = अणु
		.stream_name	= "Playback",
		.channels_min	= 2,
		.channels_max	= 6,
		.rates		= TAS5086_PCM_RATES,
		.क्रमmats	= TAS5086_PCM_FORMATS,
	पूर्ण,
	.ops = &tas5086_dai_ops,
पूर्ण;

#अगर_घोषित CONFIG_PM
अटल पूर्णांक tas5086_soc_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा tas5086_निजी *priv = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	/* Shut करोwn all channels */
	ret = regmap_ग_लिखो(priv->regmap, TAS5086_SYS_CONTROL_2, 0x60);
	अगर (ret < 0)
		वापस ret;

	regulator_bulk_disable(ARRAY_SIZE(priv->supplies), priv->supplies);

	वापस 0;
पूर्ण

अटल पूर्णांक tas5086_soc_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा tas5086_निजी *priv = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	ret = regulator_bulk_enable(ARRAY_SIZE(priv->supplies), priv->supplies);
	अगर (ret < 0)
		वापस ret;

	tas5086_reset(priv);
	regcache_mark_dirty(priv->regmap);

	ret = tas5086_init(component->dev, priv);
	अगर (ret < 0)
		वापस ret;

	ret = regcache_sync(priv->regmap);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा tas5086_soc_suspend	शून्य
#घोषणा tas5086_soc_resume	शून्य
#पूर्ण_अगर /* CONFIG_PM */

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id tas5086_dt_ids[] = अणु
	अणु .compatible = "ti,tas5086", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tas5086_dt_ids);
#पूर्ण_अगर

अटल पूर्णांक tas5086_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा tas5086_निजी *priv = snd_soc_component_get_drvdata(component);
	पूर्णांक i, ret;

	ret = regulator_bulk_enable(ARRAY_SIZE(priv->supplies), priv->supplies);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to enable regulators: %d\n", ret);
		वापस ret;
	पूर्ण

	priv->pwm_start_mid_z = 0;
	priv->अक्षरge_period = 1300000; /* hardware शेष is 1300 ms */

	अगर (of_match_device(of_match_ptr(tas5086_dt_ids), component->dev)) अणु
		काष्ठा device_node *of_node = component->dev->of_node;

		of_property_पढ़ो_u32(of_node, "ti,charge-period",
				     &priv->अक्षरge_period);

		क्रम (i = 0; i < 6; i++) अणु
			अक्षर name[25];

			snम_लिखो(name, माप(name),
				 "ti,mid-z-channel-%d", i + 1);

			अगर (of_get_property(of_node, name, शून्य) != शून्य)
				priv->pwm_start_mid_z |= 1 << i;
		पूर्ण
	पूर्ण

	tas5086_reset(priv);
	ret = tas5086_init(component->dev, priv);
	अगर (ret < 0)
		जाओ निकास_disable_regulators;

	/* set master volume to 0 dB */
	ret = regmap_ग_लिखो(priv->regmap, TAS5086_MASTER_VOL, 0x30);
	अगर (ret < 0)
		जाओ निकास_disable_regulators;

	वापस 0;

निकास_disable_regulators:
	regulator_bulk_disable(ARRAY_SIZE(priv->supplies), priv->supplies);

	वापस ret;
पूर्ण

अटल व्योम tas5086_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा tas5086_निजी *priv = snd_soc_component_get_drvdata(component);

	अगर (gpio_is_valid(priv->gpio_nreset))
		/* Set codec to the reset state */
		gpio_set_value(priv->gpio_nreset, 0);

	regulator_bulk_disable(ARRAY_SIZE(priv->supplies), priv->supplies);
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_tas5086 = अणु
	.probe			= tas5086_probe,
	.हटाओ			= tas5086_हटाओ,
	.suspend		= tas5086_soc_suspend,
	.resume			= tas5086_soc_resume,
	.controls		= tas5086_controls,
	.num_controls		= ARRAY_SIZE(tas5086_controls),
	.dapm_widमाला_लो		= tas5086_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(tas5086_dapm_widमाला_लो),
	.dapm_routes		= tas5086_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(tas5086_dapm_routes),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id tas5086_i2c_id[] = अणु
	अणु "tas5086", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tas5086_i2c_id);

अटल स्थिर काष्ठा regmap_config tas5086_regmap = अणु
	.reg_bits		= 8,
	.val_bits		= 32,
	.max_रेजिस्टर		= TAS5086_MAX_REGISTER,
	.reg_शेषs		= tas5086_reg_शेषs,
	.num_reg_शेषs	= ARRAY_SIZE(tas5086_reg_शेषs),
	.cache_type		= REGCACHE_RBTREE,
	.अस्थिर_reg		= tas5086_अस्थिर_reg,
	.ग_लिखोable_reg		= tas5086_ग_लिखोable_reg,
	.पढ़ोable_reg		= tas5086_accessible_reg,
	.reg_पढ़ो		= tas5086_reg_पढ़ो,
	.reg_ग_लिखो		= tas5086_reg_ग_लिखो,
पूर्ण;

अटल पूर्णांक tas5086_i2c_probe(काष्ठा i2c_client *i2c,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा tas5086_निजी *priv;
	काष्ठा device *dev = &i2c->dev;
	पूर्णांक gpio_nreset = -EINVAL;
	पूर्णांक i, ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	क्रम (i = 0; i < ARRAY_SIZE(supply_names); i++)
		priv->supplies[i].supply = supply_names[i];

	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(priv->supplies),
				      priv->supplies);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to get regulators: %d\n", ret);
		वापस ret;
	पूर्ण

	priv->regmap = devm_regmap_init(dev, शून्य, i2c, &tas5086_regmap);
	अगर (IS_ERR(priv->regmap)) अणु
		ret = PTR_ERR(priv->regmap);
		dev_err(&i2c->dev, "Failed to create regmap: %d\n", ret);
		वापस ret;
	पूर्ण

	i2c_set_clientdata(i2c, priv);

	अगर (of_match_device(of_match_ptr(tas5086_dt_ids), dev)) अणु
		काष्ठा device_node *of_node = dev->of_node;
		gpio_nreset = of_get_named_gpio(of_node, "reset-gpio", 0);
	पूर्ण

	अगर (gpio_is_valid(gpio_nreset))
		अगर (devm_gpio_request(dev, gpio_nreset, "TAS5086 Reset"))
			gpio_nreset = -EINVAL;

	priv->gpio_nreset = gpio_nreset;

	ret = regulator_bulk_enable(ARRAY_SIZE(priv->supplies), priv->supplies);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to enable regulators: %d\n", ret);
		वापस ret;
	पूर्ण

	tas5086_reset(priv);

	/* The TAS5086 always वापसs 0x03 in its TAS5086_DEV_ID रेजिस्टर */
	ret = regmap_पढ़ो(priv->regmap, TAS5086_DEV_ID, &i);
	अगर (ret == 0 && i != 0x3) अणु
		dev_err(dev,
			"Failed to identify TAS5086 codec (got %02x)\n", i);
		ret = -ENODEV;
	पूर्ण

	/*
	 * The chip has been identअगरied, so we can turn off the घातer
	 * again until the dai link is set up.
	 */
	regulator_bulk_disable(ARRAY_SIZE(priv->supplies), priv->supplies);

	अगर (ret == 0)
		ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev,
					     &soc_component_dev_tas5086,
					     &tas5086_dai, 1);

	वापस ret;
पूर्ण

अटल पूर्णांक tas5086_i2c_हटाओ(काष्ठा i2c_client *i2c)
अणु
	वापस 0;
पूर्ण

अटल काष्ठा i2c_driver tas5086_i2c_driver = अणु
	.driver = अणु
		.name	= "tas5086",
		.of_match_table = of_match_ptr(tas5086_dt_ids),
	पूर्ण,
	.id_table	= tas5086_i2c_id,
	.probe		= tas5086_i2c_probe,
	.हटाओ		= tas5086_i2c_हटाओ,
पूर्ण;

module_i2c_driver(tas5086_i2c_driver);

MODULE_AUTHOR("Daniel Mack <zonque@gmail.com>");
MODULE_DESCRIPTION("Texas Instruments TAS5086 ALSA SoC Codec Driver");
MODULE_LICENSE("GPL");
