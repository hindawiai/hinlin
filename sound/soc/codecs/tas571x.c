<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * TAS571x amplअगरier audio driver
 *
 * Copyright (C) 2015 Google, Inc.
 * Copyright (c) 2013 Daniel Mack <zonque@gmail.com>
 *
 * TAS5721 support:
 * Copyright (C) 2016 Petr Kulhavy, Barix AG <petr@barix.com>
 *
 * TAS5707 support:
 * Copyright (C) 2018 Jerome Brunet, Baylibre SAS <jbrunet@baylibre.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/मानकघोष.स>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "tas571x.h"

#घोषणा TAS571X_MAX_SUPPLIES		6

काष्ठा tas571x_chip अणु
	स्थिर अक्षर			*स्थिर *supply_names;
	पूर्णांक				num_supply_names;
	स्थिर काष्ठा snd_kcontrol_new	*controls;
	पूर्णांक				num_controls;
	स्थिर काष्ठा regmap_config	*regmap_config;
	पूर्णांक				vol_reg_size;
पूर्ण;

काष्ठा tas571x_निजी अणु
	स्थिर काष्ठा tas571x_chip	*chip;
	काष्ठा regmap			*regmap;
	काष्ठा regulator_bulk_data	supplies[TAS571X_MAX_SUPPLIES];
	काष्ठा clk			*mclk;
	अचिन्हित पूर्णांक			क्रमmat;
	काष्ठा gpio_desc		*reset_gpio;
	काष्ठा gpio_desc		*pdn_gpio;
	काष्ठा snd_soc_component_driver	component_driver;
पूर्ण;

अटल पूर्णांक tas571x_रेजिस्टर_size(काष्ठा tas571x_निजी *priv, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल TAS571X_MVOL_REG:
	हाल TAS571X_CH1_VOL_REG:
	हाल TAS571X_CH2_VOL_REG:
		वापस priv->chip->vol_reg_size;
	हाल TAS571X_INPUT_MUX_REG:
	हाल TAS571X_CH4_SRC_SELECT_REG:
	हाल TAS571X_PWM_MUX_REG:
	हाल TAS5717_CH1_RIGHT_CH_MIX_REG:
	हाल TAS5717_CH1_LEFT_CH_MIX_REG:
	हाल TAS5717_CH2_LEFT_CH_MIX_REG:
	हाल TAS5717_CH2_RIGHT_CH_MIX_REG:
		वापस 4;
	शेष:
		वापस 1;
	पूर्ण
पूर्ण

अटल पूर्णांक tas571x_reg_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg,
			     अचिन्हित पूर्णांक value)
अणु
	काष्ठा i2c_client *client = context;
	काष्ठा tas571x_निजी *priv = i2c_get_clientdata(client);
	अचिन्हित पूर्णांक i, size;
	uपूर्णांक8_t buf[5];
	पूर्णांक ret;

	size = tas571x_रेजिस्टर_size(priv, reg);
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

अटल पूर्णांक tas571x_reg_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg,
			    अचिन्हित पूर्णांक *value)
अणु
	काष्ठा i2c_client *client = context;
	काष्ठा tas571x_निजी *priv = i2c_get_clientdata(client);
	uपूर्णांक8_t send_buf, recv_buf[4];
	काष्ठा i2c_msg msgs[2];
	अचिन्हित पूर्णांक size;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	size = tas571x_रेजिस्टर_size(priv, reg);
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

/*
 * रेजिस्टर ग_लिखो क्रम 8- and 20-byte रेजिस्टरs
 */
अटल पूर्णांक tas571x_reg_ग_लिखो_multiword(काष्ठा i2c_client *client,
		अचिन्हित पूर्णांक reg, स्थिर दीर्घ values[], माप_प्रकार len)
अणु
	माप_प्रकार i;
	uपूर्णांक8_t *buf, *p;
	पूर्णांक ret;
	माप_प्रकार send_size = 1 + len * माप(uपूर्णांक32_t);

	buf = kzalloc(send_size, GFP_KERNEL | GFP_DMA);
	अगर (!buf)
		वापस -ENOMEM;
	buf[0] = reg;

	क्रम (i = 0, p = buf + 1; i < len; i++, p += माप(uपूर्णांक32_t))
		put_unaligned_be32(values[i], p);

	ret = i2c_master_send(client, buf, send_size);

	kमुक्त(buf);

	अगर (ret == send_size)
		वापस 0;
	अन्यथा अगर (ret < 0)
		वापस ret;
	अन्यथा
		वापस -EIO;
पूर्ण

/*
 * रेजिस्टर पढ़ो क्रम 8- and 20-byte रेजिस्टरs
 */
अटल पूर्णांक tas571x_reg_पढ़ो_multiword(काष्ठा i2c_client *client,
		अचिन्हित पूर्णांक reg, दीर्घ values[], माप_प्रकार len)
अणु
	अचिन्हित पूर्णांक i;
	uपूर्णांक8_t send_buf;
	uपूर्णांक8_t *recv_buf, *p;
	काष्ठा i2c_msg msgs[2];
	अचिन्हित पूर्णांक recv_size = len * माप(uपूर्णांक32_t);
	पूर्णांक ret;

	recv_buf = kzalloc(recv_size, GFP_KERNEL | GFP_DMA);
	अगर (!recv_buf)
		वापस -ENOMEM;

	send_buf = reg;

	msgs[0].addr = client->addr;
	msgs[0].len = माप(send_buf);
	msgs[0].buf = &send_buf;
	msgs[0].flags = 0;

	msgs[1].addr = client->addr;
	msgs[1].len = recv_size;
	msgs[1].buf = recv_buf;
	msgs[1].flags = I2C_M_RD;

	ret = i2c_transfer(client->adapter, msgs, ARRAY_SIZE(msgs));
	अगर (ret < 0)
		जाओ err_ret;
	अन्यथा अगर (ret != ARRAY_SIZE(msgs)) अणु
		ret = -EIO;
		जाओ err_ret;
	पूर्ण

	क्रम (i = 0, p = recv_buf; i < len; i++, p += माप(uपूर्णांक32_t))
		values[i] = get_unaligned_be32(p);

err_ret:
	kमुक्त(recv_buf);
	वापस ret;
पूर्ण

/*
 * Integer array controls क्रम setting biquad, mixer, DRC coefficients.
 * According to the datasheet each coefficient is effectively 26bits,
 * i.e. stored as 32bits, where bits [31:26] are ignored.
 * TI's TAS57xx Graphical Development Environment tool however produces
 * coefficients with more than 26 bits. For this reason we allow values
 * in the full 32-bits reange.
 * The coefficients are ordered as given in the TAS571x data sheet:
 * b0, b1, b2, a1, a2
 */

अटल पूर्णांक tas571x_coefficient_info(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_info *uinfo)
अणु
	पूर्णांक numcoef = kcontrol->निजी_value >> 16;

	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = numcoef;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 0xffffffff;
	वापस 0;
पूर्ण

अटल पूर्णांक tas571x_coefficient_get(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा i2c_client *i2c = to_i2c_client(component->dev);
	पूर्णांक numcoef = kcontrol->निजी_value >> 16;
	पूर्णांक index = kcontrol->निजी_value & 0xffff;

	वापस tas571x_reg_पढ़ो_multiword(i2c, index,
		ucontrol->value.पूर्णांकeger.value, numcoef);
पूर्ण

अटल पूर्णांक tas571x_coefficient_put(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा i2c_client *i2c = to_i2c_client(component->dev);
	पूर्णांक numcoef = kcontrol->निजी_value >> 16;
	पूर्णांक index = kcontrol->निजी_value & 0xffff;

	वापस tas571x_reg_ग_लिखो_multiword(i2c, index,
		ucontrol->value.पूर्णांकeger.value, numcoef);
पूर्ण

अटल पूर्णांक tas571x_set_dai_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक क्रमmat)
अणु
	काष्ठा tas571x_निजी *priv = snd_soc_component_get_drvdata(dai->component);

	priv->क्रमmat = क्रमmat;

	वापस 0;
पूर्ण

अटल पूर्णांक tas571x_hw_params(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *params,
			     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा tas571x_निजी *priv = snd_soc_component_get_drvdata(dai->component);
	u32 val;

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
		वापस -EINVAL;
	पूर्ण

	अगर (params_width(params) >= 24)
		val += 2;
	अन्यथा अगर (params_width(params) >= 20)
		val += 1;

	वापस regmap_update_bits(priv->regmap, TAS571X_SDI_REG,
				  TAS571X_SDI_FMT_MASK, val);
पूर्ण

अटल पूर्णांक tas571x_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	u8 sysctl2;
	पूर्णांक ret;

	sysctl2 = mute ? TAS571X_SYS_CTRL_2_SDN_MASK : 0;

	ret = snd_soc_component_update_bits(component,
			    TAS571X_SYS_CTRL_2_REG,
		     TAS571X_SYS_CTRL_2_SDN_MASK,
		     sysctl2);
	usleep_range(1000, 2000);

	वापस ret;
पूर्ण

अटल पूर्णांक tas571x_set_bias_level(काष्ठा snd_soc_component *component,
				  क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा tas571x_निजी *priv = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		अवरोध;
	हाल SND_SOC_BIAS_PREPARE:
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
			अगर (!IS_ERR(priv->mclk)) अणु
				ret = clk_prepare_enable(priv->mclk);
				अगर (ret) अणु
					dev_err(component->dev,
						"Failed to enable master clock: %d\n",
						ret);
					वापस ret;
				पूर्ण
			पूर्ण
		पूर्ण
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		अगर (!IS_ERR(priv->mclk))
			clk_disable_unprepare(priv->mclk);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops tas571x_dai_ops = अणु
	.set_fmt	= tas571x_set_dai_fmt,
	.hw_params	= tas571x_hw_params,
	.mute_stream	= tas571x_mute,
	.no_capture_mute = 1,
पूर्ण;


#घोषणा BIQUAD_COEFS(xname, reg) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, \
	.info = tas571x_coefficient_info, \
	.get = tas571x_coefficient_get,\
	.put = tas571x_coefficient_put, \
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE, \
	.निजी_value = reg | (5 << 16) पूर्ण

अटल स्थिर अक्षर *स्थिर tas5711_supply_names[] = अणु
	"AVDD",
	"DVDD",
	"PVDD_A",
	"PVDD_B",
	"PVDD_C",
	"PVDD_D",
पूर्ण;

अटल स्थिर DECLARE_TLV_DB_SCALE(tas5711_volume_tlv, -10350, 50, 1);

अटल स्थिर काष्ठा snd_kcontrol_new tas5711_controls[] = अणु
	SOC_SINGLE_TLV("Master Volume",
		       TAS571X_MVOL_REG,
		       0, 0xff, 1, tas5711_volume_tlv),
	SOC_DOUBLE_R_TLV("Speaker Volume",
			 TAS571X_CH1_VOL_REG,
			 TAS571X_CH2_VOL_REG,
			 0, 0xff, 1, tas5711_volume_tlv),
	SOC_DOUBLE("Speaker Switch",
		   TAS571X_SOFT_MUTE_REG,
		   TAS571X_SOFT_MUTE_CH1_SHIFT, TAS571X_SOFT_MUTE_CH2_SHIFT,
		   1, 1),
पूर्ण;

अटल स्थिर काष्ठा regmap_range tas571x_पढ़ोonly_regs_range[] = अणु
	regmap_reg_range(TAS571X_CLK_CTRL_REG,  TAS571X_DEV_ID_REG),
पूर्ण;

अटल स्थिर काष्ठा regmap_range tas571x_अस्थिर_regs_range[] = अणु
	regmap_reg_range(TAS571X_CLK_CTRL_REG,  TAS571X_ERR_STATUS_REG),
	regmap_reg_range(TAS571X_OSC_TRIM_REG,  TAS571X_OSC_TRIM_REG),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table tas571x_ग_लिखो_regs = अणु
	.no_ranges =	tas571x_पढ़ोonly_regs_range,
	.n_no_ranges =	ARRAY_SIZE(tas571x_पढ़ोonly_regs_range),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table tas571x_अस्थिर_regs = अणु
	.yes_ranges =	tas571x_अस्थिर_regs_range,
	.n_yes_ranges =	ARRAY_SIZE(tas571x_अस्थिर_regs_range),

पूर्ण;

अटल स्थिर काष्ठा reg_शेष tas5711_reg_शेषs[] = अणु
	अणु 0x04, 0x05 पूर्ण,
	अणु 0x05, 0x40 पूर्ण,
	अणु 0x06, 0x00 पूर्ण,
	अणु 0x07, 0xff पूर्ण,
	अणु 0x08, 0x30 पूर्ण,
	अणु 0x09, 0x30 पूर्ण,
	अणु 0x1b, 0x82 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config tas5711_regmap_config = अणु
	.reg_bits			= 8,
	.val_bits			= 32,
	.max_रेजिस्टर			= 0xff,
	.reg_पढ़ो			= tas571x_reg_पढ़ो,
	.reg_ग_लिखो			= tas571x_reg_ग_लिखो,
	.reg_शेषs			= tas5711_reg_शेषs,
	.num_reg_शेषs		= ARRAY_SIZE(tas5711_reg_शेषs),
	.cache_type			= REGCACHE_RBTREE,
	.wr_table			= &tas571x_ग_लिखो_regs,
	.अस्थिर_table			= &tas571x_अस्थिर_regs,
पूर्ण;

अटल स्थिर काष्ठा tas571x_chip tas5711_chip = अणु
	.supply_names			= tas5711_supply_names,
	.num_supply_names		= ARRAY_SIZE(tas5711_supply_names),
	.controls			= tas5711_controls,
	.num_controls			= ARRAY_SIZE(tas5711_controls),
	.regmap_config			= &tas5711_regmap_config,
	.vol_reg_size			= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_range tas5707_अस्थिर_regs_range[] = अणु
	regmap_reg_range(TAS571X_CLK_CTRL_REG,  TAS571X_ERR_STATUS_REG),
	regmap_reg_range(TAS571X_OSC_TRIM_REG,  TAS571X_OSC_TRIM_REG),
	regmap_reg_range(TAS5707_CH1_BQ0_REG, TAS5707_CH2_BQ6_REG),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table tas5707_अस्थिर_regs = अणु
	.yes_ranges =	tas5707_अस्थिर_regs_range,
	.n_yes_ranges =	ARRAY_SIZE(tas5707_अस्थिर_regs_range),

पूर्ण;

अटल स्थिर DECLARE_TLV_DB_SCALE(tas5707_volume_tlv, -7900, 50, 1);

अटल स्थिर अक्षर * स्थिर tas5707_volume_slew_step_txt[] = अणु
	"256", "512", "1024", "2048",
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक tas5707_volume_slew_step_values[] = अणु
	3, 0, 1, 2,
पूर्ण;

अटल SOC_VALUE_ENUM_SINGLE_DECL(tas5707_volume_slew_step_क्रमागत,
				  TAS571X_VOL_CFG_REG, 0, 0x3,
				  tas5707_volume_slew_step_txt,
				  tas5707_volume_slew_step_values);

अटल स्थिर काष्ठा snd_kcontrol_new tas5707_controls[] = अणु
	SOC_SINGLE_TLV("Master Volume",
		       TAS571X_MVOL_REG,
		       0, 0xff, 1, tas5707_volume_tlv),
	SOC_DOUBLE_R_TLV("Speaker Volume",
			 TAS571X_CH1_VOL_REG,
			 TAS571X_CH2_VOL_REG,
			 0, 0xff, 1, tas5707_volume_tlv),
	SOC_DOUBLE("Speaker Switch",
		   TAS571X_SOFT_MUTE_REG,
		   TAS571X_SOFT_MUTE_CH1_SHIFT, TAS571X_SOFT_MUTE_CH2_SHIFT,
		   1, 1),

	SOC_ENUM("Slew Rate Steps", tas5707_volume_slew_step_क्रमागत),

	BIQUAD_COEFS("CH1 - Biquad 0", TAS5707_CH1_BQ0_REG),
	BIQUAD_COEFS("CH1 - Biquad 1", TAS5707_CH1_BQ1_REG),
	BIQUAD_COEFS("CH1 - Biquad 2", TAS5707_CH1_BQ2_REG),
	BIQUAD_COEFS("CH1 - Biquad 3", TAS5707_CH1_BQ3_REG),
	BIQUAD_COEFS("CH1 - Biquad 4", TAS5707_CH1_BQ4_REG),
	BIQUAD_COEFS("CH1 - Biquad 5", TAS5707_CH1_BQ5_REG),
	BIQUAD_COEFS("CH1 - Biquad 6", TAS5707_CH1_BQ6_REG),

	BIQUAD_COEFS("CH2 - Biquad 0", TAS5707_CH2_BQ0_REG),
	BIQUAD_COEFS("CH2 - Biquad 1", TAS5707_CH2_BQ1_REG),
	BIQUAD_COEFS("CH2 - Biquad 2", TAS5707_CH2_BQ2_REG),
	BIQUAD_COEFS("CH2 - Biquad 3", TAS5707_CH2_BQ3_REG),
	BIQUAD_COEFS("CH2 - Biquad 4", TAS5707_CH2_BQ4_REG),
	BIQUAD_COEFS("CH2 - Biquad 5", TAS5707_CH2_BQ5_REG),
	BIQUAD_COEFS("CH2 - Biquad 6", TAS5707_CH2_BQ6_REG),
पूर्ण;

अटल स्थिर काष्ठा reg_शेष tas5707_reg_शेषs[] = अणु
	अणुTAS571X_CLK_CTRL_REG,		0x6cपूर्ण,
	अणुTAS571X_DEV_ID_REG,		0x70पूर्ण,
	अणुTAS571X_ERR_STATUS_REG,	0x00पूर्ण,
	अणुTAS571X_SYS_CTRL_1_REG,	0xa0पूर्ण,
	अणुTAS571X_SDI_REG,		0x05पूर्ण,
	अणुTAS571X_SYS_CTRL_2_REG,	0x40पूर्ण,
	अणुTAS571X_SOFT_MUTE_REG,		0x00पूर्ण,
	अणुTAS571X_MVOL_REG,		0xffपूर्ण,
	अणुTAS571X_CH1_VOL_REG,		0x30पूर्ण,
	अणुTAS571X_CH2_VOL_REG,		0x30पूर्ण,
	अणुTAS571X_VOL_CFG_REG,		0x91पूर्ण,
	अणुTAS571X_MODULATION_LIMIT_REG,	0x02पूर्ण,
	अणुTAS571X_IC_DELAY_CH1_REG,	0xacपूर्ण,
	अणुTAS571X_IC_DELAY_CH2_REG,	0x54पूर्ण,
	अणुTAS571X_IC_DELAY_CH3_REG,	0xacपूर्ण,
	अणुTAS571X_IC_DELAY_CH4_REG,	0x54पूर्ण,
	अणुTAS571X_START_STOP_PERIOD_REG,	0x0fपूर्ण,
	अणुTAS571X_OSC_TRIM_REG,		0x82पूर्ण,
	अणुTAS571X_BKND_ERR_REG,		0x02पूर्ण,
	अणुTAS571X_INPUT_MUX_REG,		0x17772पूर्ण,
	अणुTAS571X_PWM_MUX_REG,		0x1021345पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config tas5707_regmap_config = अणु
	.reg_bits			= 8,
	.val_bits			= 32,
	.max_रेजिस्टर			= 0xff,
	.reg_पढ़ो			= tas571x_reg_पढ़ो,
	.reg_ग_लिखो			= tas571x_reg_ग_लिखो,
	.reg_शेषs			= tas5707_reg_शेषs,
	.num_reg_शेषs		= ARRAY_SIZE(tas5707_reg_शेषs),
	.cache_type			= REGCACHE_RBTREE,
	.wr_table			= &tas571x_ग_लिखो_regs,
	.अस्थिर_table			= &tas5707_अस्थिर_regs,
पूर्ण;

अटल स्थिर काष्ठा tas571x_chip tas5707_chip = अणु
	.supply_names			= tas5711_supply_names,
	.num_supply_names		= ARRAY_SIZE(tas5711_supply_names),
	.controls			= tas5707_controls,
	.num_controls			= ARRAY_SIZE(tas5707_controls),
	.regmap_config			= &tas5707_regmap_config,
	.vol_reg_size			= 1,
पूर्ण;

अटल स्थिर अक्षर *स्थिर tas5717_supply_names[] = अणु
	"AVDD",
	"DVDD",
	"HPVDD",
	"PVDD_AB",
	"PVDD_CD",
पूर्ण;

अटल स्थिर DECLARE_TLV_DB_SCALE(tas5717_volume_tlv, -10375, 25, 0);

अटल स्थिर काष्ठा snd_kcontrol_new tas5717_controls[] = अणु
	/* MVOL LSB is ignored - see comments in tas571x_i2c_probe() */
	SOC_SINGLE_TLV("Master Volume",
		       TAS571X_MVOL_REG, 1, 0x1ff, 1,
		       tas5717_volume_tlv),
	SOC_DOUBLE_R_TLV("Speaker Volume",
			 TAS571X_CH1_VOL_REG, TAS571X_CH2_VOL_REG,
			 1, 0x1ff, 1, tas5717_volume_tlv),
	SOC_DOUBLE("Speaker Switch",
		   TAS571X_SOFT_MUTE_REG,
		   TAS571X_SOFT_MUTE_CH1_SHIFT, TAS571X_SOFT_MUTE_CH2_SHIFT,
		   1, 1),

	SOC_DOUBLE_R_RANGE("CH1 Mixer Volume",
			   TAS5717_CH1_LEFT_CH_MIX_REG,
			   TAS5717_CH1_RIGHT_CH_MIX_REG,
			   16, 0, 0x80, 0),

	SOC_DOUBLE_R_RANGE("CH2 Mixer Volume",
			   TAS5717_CH2_LEFT_CH_MIX_REG,
			   TAS5717_CH2_RIGHT_CH_MIX_REG,
			   16, 0, 0x80, 0),

	/*
	 * The biquads are named according to the रेजिस्टर names.
	 * Please note that TI's TAS57xx Graphical Development Environment
	 * tool names them dअगरferent.
	 */
	BIQUAD_COEFS("CH1 - Biquad 0", TAS5717_CH1_BQ0_REG),
	BIQUAD_COEFS("CH1 - Biquad 1", TAS5717_CH1_BQ1_REG),
	BIQUAD_COEFS("CH1 - Biquad 2", TAS5717_CH1_BQ2_REG),
	BIQUAD_COEFS("CH1 - Biquad 3", TAS5717_CH1_BQ3_REG),
	BIQUAD_COEFS("CH1 - Biquad 4", TAS5717_CH1_BQ4_REG),
	BIQUAD_COEFS("CH1 - Biquad 5", TAS5717_CH1_BQ5_REG),
	BIQUAD_COEFS("CH1 - Biquad 6", TAS5717_CH1_BQ6_REG),
	BIQUAD_COEFS("CH1 - Biquad 7", TAS5717_CH1_BQ7_REG),
	BIQUAD_COEFS("CH1 - Biquad 8", TAS5717_CH1_BQ8_REG),
	BIQUAD_COEFS("CH1 - Biquad 9", TAS5717_CH1_BQ9_REG),
	BIQUAD_COEFS("CH1 - Biquad 10", TAS5717_CH1_BQ10_REG),
	BIQUAD_COEFS("CH1 - Biquad 11", TAS5717_CH1_BQ11_REG),

	BIQUAD_COEFS("CH2 - Biquad 0", TAS5717_CH2_BQ0_REG),
	BIQUAD_COEFS("CH2 - Biquad 1", TAS5717_CH2_BQ1_REG),
	BIQUAD_COEFS("CH2 - Biquad 2", TAS5717_CH2_BQ2_REG),
	BIQUAD_COEFS("CH2 - Biquad 3", TAS5717_CH2_BQ3_REG),
	BIQUAD_COEFS("CH2 - Biquad 4", TAS5717_CH2_BQ4_REG),
	BIQUAD_COEFS("CH2 - Biquad 5", TAS5717_CH2_BQ5_REG),
	BIQUAD_COEFS("CH2 - Biquad 6", TAS5717_CH2_BQ6_REG),
	BIQUAD_COEFS("CH2 - Biquad 7", TAS5717_CH2_BQ7_REG),
	BIQUAD_COEFS("CH2 - Biquad 8", TAS5717_CH2_BQ8_REG),
	BIQUAD_COEFS("CH2 - Biquad 9", TAS5717_CH2_BQ9_REG),
	BIQUAD_COEFS("CH2 - Biquad 10", TAS5717_CH2_BQ10_REG),
	BIQUAD_COEFS("CH2 - Biquad 11", TAS5717_CH2_BQ11_REG),

	BIQUAD_COEFS("CH3 - Biquad 0", TAS5717_CH3_BQ0_REG),
	BIQUAD_COEFS("CH3 - Biquad 1", TAS5717_CH3_BQ1_REG),

	BIQUAD_COEFS("CH4 - Biquad 0", TAS5717_CH4_BQ0_REG),
	BIQUAD_COEFS("CH4 - Biquad 1", TAS5717_CH4_BQ1_REG),
पूर्ण;

अटल स्थिर काष्ठा reg_शेष tas5717_reg_शेषs[] = अणु
	अणु 0x04, 0x05 पूर्ण,
	अणु 0x05, 0x40 पूर्ण,
	अणु 0x06, 0x00 पूर्ण,
	अणु 0x07, 0x03ff पूर्ण,
	अणु 0x08, 0x00c0 पूर्ण,
	अणु 0x09, 0x00c0 पूर्ण,
	अणु 0x1b, 0x82 पूर्ण,
	अणु TAS5717_CH1_RIGHT_CH_MIX_REG, 0x0 पूर्ण,
	अणु TAS5717_CH1_LEFT_CH_MIX_REG, 0x800000पूर्ण,
	अणु TAS5717_CH2_LEFT_CH_MIX_REG, 0x0 पूर्ण,
	अणु TAS5717_CH2_RIGHT_CH_MIX_REG, 0x800000पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config tas5717_regmap_config = अणु
	.reg_bits			= 8,
	.val_bits			= 32,
	.max_रेजिस्टर			= 0xff,
	.reg_पढ़ो			= tas571x_reg_पढ़ो,
	.reg_ग_लिखो			= tas571x_reg_ग_लिखो,
	.reg_शेषs			= tas5717_reg_शेषs,
	.num_reg_शेषs		= ARRAY_SIZE(tas5717_reg_शेषs),
	.cache_type			= REGCACHE_RBTREE,
	.wr_table			= &tas571x_ग_लिखो_regs,
	.अस्थिर_table			= &tas571x_अस्थिर_regs,
पूर्ण;

/* This entry is reused क्रम tas5719 as the software पूर्णांकerface is identical. */
अटल स्थिर काष्ठा tas571x_chip tas5717_chip = अणु
	.supply_names			= tas5717_supply_names,
	.num_supply_names		= ARRAY_SIZE(tas5717_supply_names),
	.controls			= tas5717_controls,
	.num_controls			= ARRAY_SIZE(tas5717_controls),
	.regmap_config			= &tas5717_regmap_config,
	.vol_reg_size			= 2,
पूर्ण;

अटल स्थिर अक्षर *स्थिर tas5721_supply_names[] = अणु
	"AVDD",
	"DVDD",
	"DRVDD",
	"PVDD",
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new tas5721_controls[] = अणु
	SOC_SINGLE_TLV("Master Volume",
		       TAS571X_MVOL_REG,
		       0, 0xff, 1, tas5711_volume_tlv),
	SOC_DOUBLE_R_TLV("Speaker Volume",
			 TAS571X_CH1_VOL_REG,
			 TAS571X_CH2_VOL_REG,
			 0, 0xff, 1, tas5711_volume_tlv),
	SOC_DOUBLE("Speaker Switch",
		   TAS571X_SOFT_MUTE_REG,
		   TAS571X_SOFT_MUTE_CH1_SHIFT, TAS571X_SOFT_MUTE_CH2_SHIFT,
		   1, 1),
पूर्ण;

अटल स्थिर काष्ठा reg_शेष tas5721_reg_शेषs[] = अणु
	अणुTAS571X_CLK_CTRL_REG,		0x6cपूर्ण,
	अणुTAS571X_DEV_ID_REG,		0x00पूर्ण,
	अणुTAS571X_ERR_STATUS_REG,	0x00पूर्ण,
	अणुTAS571X_SYS_CTRL_1_REG,	0xa0पूर्ण,
	अणुTAS571X_SDI_REG,		0x05पूर्ण,
	अणुTAS571X_SYS_CTRL_2_REG,	0x40पूर्ण,
	अणुTAS571X_SOFT_MUTE_REG,		0x00पूर्ण,
	अणुTAS571X_MVOL_REG,		0xffपूर्ण,
	अणुTAS571X_CH1_VOL_REG,		0x30पूर्ण,
	अणुTAS571X_CH2_VOL_REG,		0x30पूर्ण,
	अणुTAS571X_CH3_VOL_REG,		0x30पूर्ण,
	अणुTAS571X_VOL_CFG_REG,		0x91पूर्ण,
	अणुTAS571X_MODULATION_LIMIT_REG,	0x02पूर्ण,
	अणुTAS571X_IC_DELAY_CH1_REG,	0xacपूर्ण,
	अणुTAS571X_IC_DELAY_CH2_REG,	0x54पूर्ण,
	अणुTAS571X_IC_DELAY_CH3_REG,	0xacपूर्ण,
	अणुTAS571X_IC_DELAY_CH4_REG,	0x54पूर्ण,
	अणुTAS571X_PWM_CH_SDN_GROUP_REG,	0x30पूर्ण,
	अणुTAS571X_START_STOP_PERIOD_REG,	0x0fपूर्ण,
	अणुTAS571X_OSC_TRIM_REG,		0x82पूर्ण,
	अणुTAS571X_BKND_ERR_REG,		0x02पूर्ण,
	अणुTAS571X_INPUT_MUX_REG,		0x17772पूर्ण,
	अणुTAS571X_CH4_SRC_SELECT_REG,	0x4303पूर्ण,
	अणुTAS571X_PWM_MUX_REG,		0x1021345पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config tas5721_regmap_config = अणु
	.reg_bits			= 8,
	.val_bits			= 32,
	.max_रेजिस्टर			= 0xff,
	.reg_पढ़ो			= tas571x_reg_पढ़ो,
	.reg_ग_लिखो			= tas571x_reg_ग_लिखो,
	.reg_शेषs			= tas5721_reg_शेषs,
	.num_reg_शेषs		= ARRAY_SIZE(tas5721_reg_शेषs),
	.cache_type			= REGCACHE_RBTREE,
	.wr_table			= &tas571x_ग_लिखो_regs,
	.अस्थिर_table			= &tas571x_अस्थिर_regs,
पूर्ण;


अटल स्थिर काष्ठा tas571x_chip tas5721_chip = अणु
	.supply_names			= tas5721_supply_names,
	.num_supply_names		= ARRAY_SIZE(tas5721_supply_names),
	.controls			= tas5721_controls,
	.num_controls			= ARRAY_SIZE(tas5721_controls),
	.regmap_config			= &tas5721_regmap_config,
	.vol_reg_size			= 1,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget tas571x_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_DAC("DACL", शून्य, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC("DACR", शून्य, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_OUTPUT("OUT_A"),
	SND_SOC_DAPM_OUTPUT("OUT_B"),
	SND_SOC_DAPM_OUTPUT("OUT_C"),
	SND_SOC_DAPM_OUTPUT("OUT_D"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route tas571x_dapm_routes[] = अणु
	अणु "DACL",  शून्य, "Playback" पूर्ण,
	अणु "DACR",  शून्य, "Playback" पूर्ण,

	अणु "OUT_A", शून्य, "DACL" पूर्ण,
	अणु "OUT_B", शून्य, "DACL" पूर्ण,
	अणु "OUT_C", शून्य, "DACR" पूर्ण,
	अणु "OUT_D", शून्य, "DACR" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver tas571x_component = अणु
	.set_bias_level		= tas571x_set_bias_level,
	.dapm_widमाला_लो		= tas571x_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(tas571x_dapm_widमाला_लो),
	.dapm_routes		= tas571x_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(tas571x_dapm_routes),
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver tas571x_dai = अणु
	.name = "tas571x-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S32_LE |
			   SNDRV_PCM_FMTBIT_S24_LE |
			   SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
	.ops = &tas571x_dai_ops,
पूर्ण;

अटल स्थिर काष्ठा of_device_id tas571x_of_match[] __maybe_unused;

अटल पूर्णांक tas571x_i2c_probe(काष्ठा i2c_client *client,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा tas571x_निजी *priv;
	काष्ठा device *dev = &client->dev;
	स्थिर काष्ठा of_device_id *of_id;
	पूर्णांक i, ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;
	i2c_set_clientdata(client, priv);

	of_id = of_match_device(tas571x_of_match, dev);
	अगर (of_id)
		priv->chip = of_id->data;
	अन्यथा
		priv->chip = (व्योम *) id->driver_data;

	priv->mclk = devm_clk_get(dev, "mclk");
	अगर (IS_ERR(priv->mclk) && PTR_ERR(priv->mclk) != -ENOENT) अणु
		dev_err(dev, "Failed to request mclk: %ld\n",
			PTR_ERR(priv->mclk));
		वापस PTR_ERR(priv->mclk);
	पूर्ण

	अगर (WARN_ON(priv->chip->num_supply_names > TAS571X_MAX_SUPPLIES))
		वापस -EINVAL;
	क्रम (i = 0; i < priv->chip->num_supply_names; i++)
		priv->supplies[i].supply = priv->chip->supply_names[i];

	ret = devm_regulator_bulk_get(dev, priv->chip->num_supply_names,
				      priv->supplies);
	अगर (ret) अणु
		dev_err(dev, "Failed to get supplies: %d\n", ret);
		वापस ret;
	पूर्ण
	ret = regulator_bulk_enable(priv->chip->num_supply_names,
				    priv->supplies);
	अगर (ret) अणु
		dev_err(dev, "Failed to enable supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	priv->regmap = devm_regmap_init(dev, शून्य, client,
					priv->chip->regmap_config);
	अगर (IS_ERR(priv->regmap)) अणु
		ret = PTR_ERR(priv->regmap);
		जाओ disable_regs;
	पूर्ण

	priv->pdn_gpio = devm_gpiod_get_optional(dev, "pdn", GPIOD_OUT_LOW);
	अगर (IS_ERR(priv->pdn_gpio)) अणु
		dev_err(dev, "error requesting pdn_gpio: %ld\n",
			PTR_ERR(priv->pdn_gpio));
		वापस PTR_ERR(priv->pdn_gpio);
	पूर्ण

	priv->reset_gpio = devm_gpiod_get_optional(dev, "reset",
						   GPIOD_OUT_HIGH);
	अगर (IS_ERR(priv->reset_gpio)) अणु
		dev_err(dev, "error requesting reset_gpio: %ld\n",
			PTR_ERR(priv->reset_gpio));
		वापस PTR_ERR(priv->reset_gpio);
	पूर्ण अन्यथा अगर (priv->reset_gpio) अणु
		/* pulse the active low reset line क्रम ~100us */
		usleep_range(100, 200);
		gpiod_set_value(priv->reset_gpio, 0);
		usleep_range(13500, 20000);
	पूर्ण

	ret = regmap_ग_लिखो(priv->regmap, TAS571X_OSC_TRIM_REG, 0);
	अगर (ret)
		जाओ disable_regs;

	usleep_range(50000, 60000);

	स_नकल(&priv->component_driver, &tas571x_component, माप(priv->component_driver));
	priv->component_driver.controls = priv->chip->controls;
	priv->component_driver.num_controls = priv->chip->num_controls;

	अगर (priv->chip->vol_reg_size == 2) अणु
		/*
		 * The master volume शेषs to 0x3ff (mute), but we ignore
		 * (zero) the LSB because the hardware step size is 0.125 dB
		 * and TLV_DB_SCALE_ITEM has a resolution of 0.01 dB.
		 */
		ret = regmap_update_bits(priv->regmap, TAS571X_MVOL_REG, 1, 0);
		अगर (ret)
			जाओ disable_regs;
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_component(&client->dev,
				      &priv->component_driver,
				      &tas571x_dai, 1);
	अगर (ret)
		जाओ disable_regs;

	वापस ret;

disable_regs:
	regulator_bulk_disable(priv->chip->num_supply_names, priv->supplies);
	वापस ret;
पूर्ण

अटल पूर्णांक tas571x_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा tas571x_निजी *priv = i2c_get_clientdata(client);

	regulator_bulk_disable(priv->chip->num_supply_names, priv->supplies);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id tas571x_of_match[] __maybe_unused = अणु
	अणु .compatible = "ti,tas5707", .data = &tas5707_chip, पूर्ण,
	अणु .compatible = "ti,tas5711", .data = &tas5711_chip, पूर्ण,
	अणु .compatible = "ti,tas5717", .data = &tas5717_chip, पूर्ण,
	अणु .compatible = "ti,tas5719", .data = &tas5717_chip, पूर्ण,
	अणु .compatible = "ti,tas5721", .data = &tas5721_chip, पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tas571x_of_match);

अटल स्थिर काष्ठा i2c_device_id tas571x_i2c_id[] = अणु
	अणु "tas5707", (kernel_uदीर्घ_t) &tas5707_chip पूर्ण,
	अणु "tas5711", (kernel_uदीर्घ_t) &tas5711_chip पूर्ण,
	अणु "tas5717", (kernel_uदीर्घ_t) &tas5717_chip पूर्ण,
	अणु "tas5719", (kernel_uदीर्घ_t) &tas5717_chip पूर्ण,
	अणु "tas5721", (kernel_uदीर्घ_t) &tas5721_chip पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tas571x_i2c_id);

अटल काष्ठा i2c_driver tas571x_i2c_driver = अणु
	.driver = अणु
		.name = "tas571x",
		.of_match_table = of_match_ptr(tas571x_of_match),
	पूर्ण,
	.probe = tas571x_i2c_probe,
	.हटाओ = tas571x_i2c_हटाओ,
	.id_table = tas571x_i2c_id,
पूर्ण;
module_i2c_driver(tas571x_i2c_driver);

MODULE_DESCRIPTION("ASoC TAS571x driver");
MODULE_AUTHOR("Kevin Cernekee <cernekee@chromium.org>");
MODULE_LICENSE("GPL");
