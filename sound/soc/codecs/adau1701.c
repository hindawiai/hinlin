<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम ADAU1701 SigmaDSP processor
 *
 * Copyright 2011 Analog Devices Inc.
 * Author: Lars-Peter Clausen <lars@metafoo.de>
 *	based on an inital version by Clअगरf Cai <clअगरf.cai@analog.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/i2c.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/of_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/regmap.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>

#समावेश <यंत्र/unaligned.h>

#समावेश "sigmadsp.h"
#समावेश "adau1701.h"

#घोषणा ADAU1701_SAFELOAD_DATA(i) (0x0810 + (i))
#घोषणा ADAU1701_SAFELOAD_ADDR(i) (0x0815 + (i))

#घोषणा ADAU1701_DSPCTRL	0x081c
#घोषणा ADAU1701_SEROCTL	0x081e
#घोषणा ADAU1701_SERICTL	0x081f

#घोषणा ADAU1701_AUXNPOW	0x0822
#घोषणा ADAU1701_PINCONF_0	0x0820
#घोषणा ADAU1701_PINCONF_1	0x0821
#घोषणा ADAU1701_AUXNPOW	0x0822

#घोषणा ADAU1701_OSCIPOW	0x0826
#घोषणा ADAU1701_DACSET		0x0827

#घोषणा ADAU1701_MAX_REGISTER	0x0828

#घोषणा ADAU1701_DSPCTRL_CR		(1 << 2)
#घोषणा ADAU1701_DSPCTRL_DAM		(1 << 3)
#घोषणा ADAU1701_DSPCTRL_ADM		(1 << 4)
#घोषणा ADAU1701_DSPCTRL_IST		(1 << 5)
#घोषणा ADAU1701_DSPCTRL_SR_48		0x00
#घोषणा ADAU1701_DSPCTRL_SR_96		0x01
#घोषणा ADAU1701_DSPCTRL_SR_192		0x02
#घोषणा ADAU1701_DSPCTRL_SR_MASK	0x03

#घोषणा ADAU1701_SEROCTL_INV_LRCLK	0x2000
#घोषणा ADAU1701_SEROCTL_INV_BCLK	0x1000
#घोषणा ADAU1701_SEROCTL_MASTER		0x0800

#घोषणा ADAU1701_SEROCTL_OBF16		0x0000
#घोषणा ADAU1701_SEROCTL_OBF8		0x0200
#घोषणा ADAU1701_SEROCTL_OBF4		0x0400
#घोषणा ADAU1701_SEROCTL_OBF2		0x0600
#घोषणा ADAU1701_SEROCTL_OBF_MASK	0x0600

#घोषणा ADAU1701_SEROCTL_OLF1024	0x0000
#घोषणा ADAU1701_SEROCTL_OLF512		0x0080
#घोषणा ADAU1701_SEROCTL_OLF256		0x0100
#घोषणा ADAU1701_SEROCTL_OLF_MASK	0x0180

#घोषणा ADAU1701_SEROCTL_MSB_DEALY1	0x0000
#घोषणा ADAU1701_SEROCTL_MSB_DEALY0	0x0004
#घोषणा ADAU1701_SEROCTL_MSB_DEALY8	0x0008
#घोषणा ADAU1701_SEROCTL_MSB_DEALY12	0x000c
#घोषणा ADAU1701_SEROCTL_MSB_DEALY16	0x0010
#घोषणा ADAU1701_SEROCTL_MSB_DEALY_MASK	0x001c

#घोषणा ADAU1701_SEROCTL_WORD_LEN_24	0x0000
#घोषणा ADAU1701_SEROCTL_WORD_LEN_20	0x0001
#घोषणा ADAU1701_SEROCTL_WORD_LEN_16	0x0002
#घोषणा ADAU1701_SEROCTL_WORD_LEN_MASK	0x0003

#घोषणा ADAU1701_AUXNPOW_VBPD		0x40
#घोषणा ADAU1701_AUXNPOW_VRPD		0x20

#घोषणा ADAU1701_SERICTL_I2S		0
#घोषणा ADAU1701_SERICTL_LEFTJ		1
#घोषणा ADAU1701_SERICTL_TDM		2
#घोषणा ADAU1701_SERICTL_RIGHTJ_24	3
#घोषणा ADAU1701_SERICTL_RIGHTJ_20	4
#घोषणा ADAU1701_SERICTL_RIGHTJ_18	5
#घोषणा ADAU1701_SERICTL_RIGHTJ_16	6
#घोषणा ADAU1701_SERICTL_MODE_MASK	7
#घोषणा ADAU1701_SERICTL_INV_BCLK	BIT(3)
#घोषणा ADAU1701_SERICTL_INV_LRCLK	BIT(4)

#घोषणा ADAU1701_OSCIPOW_OPD		0x04
#घोषणा ADAU1701_DACSET_DACINIT		1

#घोषणा ADAU1707_CLKDIV_UNSET		(-1U)

#घोषणा ADAU1701_FIRMWARE "adau1701.bin"

अटल स्थिर अक्षर * स्थिर supply_names[] = अणु
	"dvdd", "avdd"
पूर्ण;

काष्ठा adau1701 अणु
	पूर्णांक gpio_nreset;
	पूर्णांक gpio_pll_mode[2];
	अचिन्हित पूर्णांक dai_fmt;
	अचिन्हित पूर्णांक pll_clkभाग;
	अचिन्हित पूर्णांक sysclk;
	काष्ठा regmap *regmap;
	काष्ठा i2c_client *client;
	u8 pin_config[12];

	काष्ठा sigmadsp *sigmadsp;
	काष्ठा regulator_bulk_data supplies[ARRAY_SIZE(supply_names)];
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new adau1701_controls[] = अणु
	SOC_SINGLE("Master Capture Switch", ADAU1701_DSPCTRL, 4, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget adau1701_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_DAC("DAC0", "Playback", ADAU1701_AUXNPOW, 3, 1),
	SND_SOC_DAPM_DAC("DAC1", "Playback", ADAU1701_AUXNPOW, 2, 1),
	SND_SOC_DAPM_DAC("DAC2", "Playback", ADAU1701_AUXNPOW, 1, 1),
	SND_SOC_DAPM_DAC("DAC3", "Playback", ADAU1701_AUXNPOW, 0, 1),
	SND_SOC_DAPM_ADC("ADC", "Capture", ADAU1701_AUXNPOW, 7, 1),

	SND_SOC_DAPM_OUTPUT("OUT0"),
	SND_SOC_DAPM_OUTPUT("OUT1"),
	SND_SOC_DAPM_OUTPUT("OUT2"),
	SND_SOC_DAPM_OUTPUT("OUT3"),
	SND_SOC_DAPM_INPUT("IN0"),
	SND_SOC_DAPM_INPUT("IN1"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route adau1701_dapm_routes[] = अणु
	अणु "OUT0", शून्य, "DAC0" पूर्ण,
	अणु "OUT1", शून्य, "DAC1" पूर्ण,
	अणु "OUT2", शून्य, "DAC2" पूर्ण,
	अणु "OUT3", शून्य, "DAC3" पूर्ण,

	अणु "ADC", शून्य, "IN0" पूर्ण,
	अणु "ADC", शून्य, "IN1" पूर्ण,
पूर्ण;

अटल अचिन्हित पूर्णांक adau1701_रेजिस्टर_size(काष्ठा device *dev,
		अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल ADAU1701_PINCONF_0:
	हाल ADAU1701_PINCONF_1:
		वापस 3;
	हाल ADAU1701_DSPCTRL:
	हाल ADAU1701_SEROCTL:
	हाल ADAU1701_AUXNPOW:
	हाल ADAU1701_OSCIPOW:
	हाल ADAU1701_DACSET:
		वापस 2;
	हाल ADAU1701_SERICTL:
		वापस 1;
	पूर्ण

	dev_err(dev, "Unsupported register address: %d\n", reg);
	वापस 0;
पूर्ण

अटल bool adau1701_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल ADAU1701_DACSET:
	हाल ADAU1701_DSPCTRL:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक adau1701_reg_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg,
			      अचिन्हित पूर्णांक value)
अणु
	काष्ठा i2c_client *client = context;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक size;
	uपूर्णांक8_t buf[5];
	पूर्णांक ret;

	size = adau1701_रेजिस्टर_size(&client->dev, reg);
	अगर (size == 0)
		वापस -EINVAL;

	buf[0] = reg >> 8;
	buf[1] = reg & 0xff;

	क्रम (i = size + 1; i >= 2; --i) अणु
		buf[i] = value;
		value >>= 8;
	पूर्ण

	ret = i2c_master_send(client, buf, size + 2);
	अगर (ret == size + 2)
		वापस 0;
	अन्यथा अगर (ret < 0)
		वापस ret;
	अन्यथा
		वापस -EIO;
पूर्ण

अटल पूर्णांक adau1701_reg_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg,
			     अचिन्हित पूर्णांक *value)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक size;
	uपूर्णांक8_t send_buf[2], recv_buf[3];
	काष्ठा i2c_client *client = context;
	काष्ठा i2c_msg msgs[2];

	size = adau1701_रेजिस्टर_size(&client->dev, reg);
	अगर (size == 0)
		वापस -EINVAL;

	send_buf[0] = reg >> 8;
	send_buf[1] = reg & 0xff;

	msgs[0].addr = client->addr;
	msgs[0].len = माप(send_buf);
	msgs[0].buf = send_buf;
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

अटल पूर्णांक adau1701_safeload(काष्ठा sigmadsp *sigmadsp, अचिन्हित पूर्णांक addr,
	स्थिर uपूर्णांक8_t bytes[], माप_प्रकार len)
अणु
	काष्ठा i2c_client *client = to_i2c_client(sigmadsp->dev);
	काष्ठा adau1701 *adau1701 = i2c_get_clientdata(client);
	अचिन्हित पूर्णांक val;
	अचिन्हित पूर्णांक i;
	uपूर्णांक8_t buf[10];
	पूर्णांक ret;

	ret = regmap_पढ़ो(adau1701->regmap, ADAU1701_DSPCTRL, &val);
	अगर (ret)
		वापस ret;

	अगर (val & ADAU1701_DSPCTRL_IST)
		msleep(50);

	क्रम (i = 0; i < len / 4; i++) अणु
		put_unaligned_le16(ADAU1701_SAFELOAD_DATA(i), buf);
		buf[2] = 0x00;
		स_नकल(buf + 3, bytes + i * 4, 4);
		ret = i2c_master_send(client, buf, 7);
		अगर (ret < 0)
			वापस ret;
		अन्यथा अगर (ret != 7)
			वापस -EIO;

		put_unaligned_le16(ADAU1701_SAFELOAD_ADDR(i), buf);
		put_unaligned_le16(addr + i, buf + 2);
		ret = i2c_master_send(client, buf, 4);
		अगर (ret < 0)
			वापस ret;
		अन्यथा अगर (ret != 4)
			वापस -EIO;
	पूर्ण

	वापस regmap_update_bits(adau1701->regmap, ADAU1701_DSPCTRL,
		ADAU1701_DSPCTRL_IST, ADAU1701_DSPCTRL_IST);
पूर्ण

अटल स्थिर काष्ठा sigmadsp_ops adau1701_sigmadsp_ops = अणु
	.safeload = adau1701_safeload,
पूर्ण;

अटल पूर्णांक adau1701_reset(काष्ठा snd_soc_component *component, अचिन्हित पूर्णांक clkभाग,
	अचिन्हित पूर्णांक rate)
अणु
	काष्ठा adau1701 *adau1701 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	sigmadsp_reset(adau1701->sigmadsp);

	अगर (clkभाग != ADAU1707_CLKDIV_UNSET &&
	    gpio_is_valid(adau1701->gpio_pll_mode[0]) &&
	    gpio_is_valid(adau1701->gpio_pll_mode[1])) अणु
		चयन (clkभाग) अणु
		हाल 64:
			gpio_set_value_cansleep(adau1701->gpio_pll_mode[0], 0);
			gpio_set_value_cansleep(adau1701->gpio_pll_mode[1], 0);
			अवरोध;
		हाल 256:
			gpio_set_value_cansleep(adau1701->gpio_pll_mode[0], 0);
			gpio_set_value_cansleep(adau1701->gpio_pll_mode[1], 1);
			अवरोध;
		हाल 384:
			gpio_set_value_cansleep(adau1701->gpio_pll_mode[0], 1);
			gpio_set_value_cansleep(adau1701->gpio_pll_mode[1], 0);
			अवरोध;
		हाल 0:	/* fallback */
		हाल 512:
			gpio_set_value_cansleep(adau1701->gpio_pll_mode[0], 1);
			gpio_set_value_cansleep(adau1701->gpio_pll_mode[1], 1);
			अवरोध;
		पूर्ण
	पूर्ण

	adau1701->pll_clkभाग = clkभाग;

	अगर (gpio_is_valid(adau1701->gpio_nreset)) अणु
		gpio_set_value_cansleep(adau1701->gpio_nreset, 0);
		/* minimum reset समय is 20ns */
		udelay(1);
		gpio_set_value_cansleep(adau1701->gpio_nreset, 1);
		/* घातer-up समय may be as दीर्घ as 85ms */
		mdelay(85);
	पूर्ण

	/*
	 * Postpone the firmware करोwnload to a poपूर्णांक in समय when we
	 * know the correct PLL setup
	 */
	अगर (clkभाग != ADAU1707_CLKDIV_UNSET) अणु
		ret = sigmadsp_setup(adau1701->sigmadsp, rate);
		अगर (ret) अणु
			dev_warn(component->dev, "Failed to load firmware\n");
			वापस ret;
		पूर्ण
	पूर्ण

	regmap_ग_लिखो(adau1701->regmap, ADAU1701_DACSET, ADAU1701_DACSET_DACINIT);
	regmap_ग_लिखो(adau1701->regmap, ADAU1701_DSPCTRL, ADAU1701_DSPCTRL_CR);

	regcache_mark_dirty(adau1701->regmap);
	regcache_sync(adau1701->regmap);

	वापस 0;
पूर्ण

अटल पूर्णांक adau1701_set_capture_pcm_क्रमmat(काष्ठा snd_soc_component *component,
					   काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा adau1701 *adau1701 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक mask = ADAU1701_SEROCTL_WORD_LEN_MASK;
	अचिन्हित पूर्णांक val;

	चयन (params_width(params)) अणु
	हाल 16:
		val = ADAU1701_SEROCTL_WORD_LEN_16;
		अवरोध;
	हाल 20:
		val = ADAU1701_SEROCTL_WORD_LEN_20;
		अवरोध;
	हाल 24:
		val = ADAU1701_SEROCTL_WORD_LEN_24;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (adau1701->dai_fmt == SND_SOC_DAIFMT_RIGHT_J) अणु
		चयन (params_width(params)) अणु
		हाल 16:
			val |= ADAU1701_SEROCTL_MSB_DEALY16;
			अवरोध;
		हाल 20:
			val |= ADAU1701_SEROCTL_MSB_DEALY12;
			अवरोध;
		हाल 24:
			val |= ADAU1701_SEROCTL_MSB_DEALY8;
			अवरोध;
		पूर्ण
		mask |= ADAU1701_SEROCTL_MSB_DEALY_MASK;
	पूर्ण

	regmap_update_bits(adau1701->regmap, ADAU1701_SEROCTL, mask, val);

	वापस 0;
पूर्ण

अटल पूर्णांक adau1701_set_playback_pcm_क्रमmat(काष्ठा snd_soc_component *component,
					    काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा adau1701 *adau1701 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक val;

	अगर (adau1701->dai_fmt != SND_SOC_DAIFMT_RIGHT_J)
		वापस 0;

	चयन (params_width(params)) अणु
	हाल 16:
		val = ADAU1701_SERICTL_RIGHTJ_16;
		अवरोध;
	हाल 20:
		val = ADAU1701_SERICTL_RIGHTJ_20;
		अवरोध;
	हाल 24:
		val = ADAU1701_SERICTL_RIGHTJ_24;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(adau1701->regmap, ADAU1701_SERICTL,
		ADAU1701_SERICTL_MODE_MASK, val);

	वापस 0;
पूर्ण

अटल पूर्णांक adau1701_hw_params(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_pcm_hw_params *params, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा adau1701 *adau1701 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक clkभाग = adau1701->sysclk / params_rate(params);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	/*
	 * If the mclk/lrclk ratio changes, the chip needs updated PLL
	 * mode GPIO settings, and a full reset cycle, including a new
	 * firmware upload.
	 */
	अगर (clkभाग != adau1701->pll_clkभाग) अणु
		ret = adau1701_reset(component, clkभाग, params_rate(params));
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	चयन (params_rate(params)) अणु
	हाल 192000:
		val = ADAU1701_DSPCTRL_SR_192;
		अवरोध;
	हाल 96000:
		val = ADAU1701_DSPCTRL_SR_96;
		अवरोध;
	हाल 48000:
		val = ADAU1701_DSPCTRL_SR_48;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(adau1701->regmap, ADAU1701_DSPCTRL,
		ADAU1701_DSPCTRL_SR_MASK, val);

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		वापस adau1701_set_playback_pcm_क्रमmat(component, params);
	अन्यथा
		वापस adau1701_set_capture_pcm_क्रमmat(component, params);
पूर्ण

अटल पूर्णांक adau1701_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai,
		अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा adau1701 *adau1701 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक serictl = 0x00, seroctl = 0x00;
	bool invert_lrclk;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		/* master, 64-bits per sample, 1 frame per sample */
		seroctl |= ADAU1701_SEROCTL_MASTER | ADAU1701_SEROCTL_OBF16
				| ADAU1701_SEROCTL_OLF1024;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* घड़ी inversion */
	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		invert_lrclk = false;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		invert_lrclk = true;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		invert_lrclk = false;
		serictl |= ADAU1701_SERICTL_INV_BCLK;
		seroctl |= ADAU1701_SEROCTL_INV_BCLK;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		invert_lrclk = true;
		serictl |= ADAU1701_SERICTL_INV_BCLK;
		seroctl |= ADAU1701_SEROCTL_INV_BCLK;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		serictl |= ADAU1701_SERICTL_LEFTJ;
		seroctl |= ADAU1701_SEROCTL_MSB_DEALY0;
		invert_lrclk = !invert_lrclk;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		serictl |= ADAU1701_SERICTL_RIGHTJ_24;
		seroctl |= ADAU1701_SEROCTL_MSB_DEALY8;
		invert_lrclk = !invert_lrclk;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (invert_lrclk) अणु
		seroctl |= ADAU1701_SEROCTL_INV_LRCLK;
		serictl |= ADAU1701_SERICTL_INV_LRCLK;
	पूर्ण

	adau1701->dai_fmt = fmt & SND_SOC_DAIFMT_FORMAT_MASK;

	regmap_ग_लिखो(adau1701->regmap, ADAU1701_SERICTL, serictl);
	regmap_update_bits(adau1701->regmap, ADAU1701_SEROCTL,
		~ADAU1701_SEROCTL_WORD_LEN_MASK, seroctl);

	वापस 0;
पूर्ण

अटल पूर्णांक adau1701_set_bias_level(काष्ठा snd_soc_component *component,
		क्रमागत snd_soc_bias_level level)
अणु
	अचिन्हित पूर्णांक mask = ADAU1701_AUXNPOW_VBPD | ADAU1701_AUXNPOW_VRPD;
	काष्ठा adau1701 *adau1701 = snd_soc_component_get_drvdata(component);

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		अवरोध;
	हाल SND_SOC_BIAS_PREPARE:
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		/* Enable VREF and VREF buffer */
		regmap_update_bits(adau1701->regmap,
				   ADAU1701_AUXNPOW, mask, 0x00);
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		/* Disable VREF and VREF buffer */
		regmap_update_bits(adau1701->regmap,
				   ADAU1701_AUXNPOW, mask, mask);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adau1701_mute_stream(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	अचिन्हित पूर्णांक mask = ADAU1701_DSPCTRL_DAM;
	काष्ठा adau1701 *adau1701 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक val;

	अगर (mute)
		val = 0;
	अन्यथा
		val = mask;

	regmap_update_bits(adau1701->regmap, ADAU1701_DSPCTRL, mask, val);

	वापस 0;
पूर्ण

अटल पूर्णांक adau1701_set_sysclk(काष्ठा snd_soc_component *component, पूर्णांक clk_id,
	पूर्णांक source, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	अचिन्हित पूर्णांक val;
	काष्ठा adau1701 *adau1701 = snd_soc_component_get_drvdata(component);

	चयन (clk_id) अणु
	हाल ADAU1701_CLK_SRC_OSC:
		val = 0x0;
		अवरोध;
	हाल ADAU1701_CLK_SRC_MCLK:
		val = ADAU1701_OSCIPOW_OPD;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(adau1701->regmap, ADAU1701_OSCIPOW,
			   ADAU1701_OSCIPOW_OPD, val);
	adau1701->sysclk = freq;

	वापस 0;
पूर्ण

अटल पूर्णांक adau1701_startup(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा adau1701 *adau1701 = snd_soc_component_get_drvdata(dai->component);

	वापस sigmadsp_restrict_params(adau1701->sigmadsp, substream);
पूर्ण

#घोषणा ADAU1701_RATES (SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_96000 | \
	SNDRV_PCM_RATE_192000)

#घोषणा ADAU1701_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE |\
	SNDRV_PCM_FMTBIT_S24_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops adau1701_dai_ops = अणु
	.set_fmt	= adau1701_set_dai_fmt,
	.hw_params	= adau1701_hw_params,
	.mute_stream	= adau1701_mute_stream,
	.startup	= adau1701_startup,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver adau1701_dai = अणु
	.name = "adau1701",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 2,
		.channels_max = 8,
		.rates = ADAU1701_RATES,
		.क्रमmats = ADAU1701_FORMATS,
	पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 2,
		.channels_max = 8,
		.rates = ADAU1701_RATES,
		.क्रमmats = ADAU1701_FORMATS,
	पूर्ण,
	.ops = &adau1701_dai_ops,
	.symmetric_rate = 1,
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id adau1701_dt_ids[] = अणु
	अणु .compatible = "adi,adau1701", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, adau1701_dt_ids);
#पूर्ण_अगर

अटल पूर्णांक adau1701_probe(काष्ठा snd_soc_component *component)
अणु
	पूर्णांक i, ret;
	अचिन्हित पूर्णांक val;
	काष्ठा adau1701 *adau1701 = snd_soc_component_get_drvdata(component);

	ret = sigmadsp_attach(adau1701->sigmadsp, component);
	अगर (ret)
		वापस ret;

	ret = regulator_bulk_enable(ARRAY_SIZE(adau1701->supplies),
				    adau1701->supplies);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to enable regulators: %d\n", ret);
		वापस ret;
	पूर्ण

	/*
	 * Let the pll_clkभाग variable शेष to something that won't happen
	 * at runसमय. That way, we can postpone the firmware करोwnload from
	 * adau1701_reset() to a poपूर्णांक in समय when we know the correct PLL
	 * mode parameters.
	 */
	adau1701->pll_clkभाग = ADAU1707_CLKDIV_UNSET;

	/* initalize with pre-configured pll mode settings */
	ret = adau1701_reset(component, adau1701->pll_clkभाग, 0);
	अगर (ret < 0)
		जाओ निकास_regulators_disable;

	/* set up pin config */
	val = 0;
	क्रम (i = 0; i < 6; i++)
		val |= adau1701->pin_config[i] << (i * 4);

	regmap_ग_लिखो(adau1701->regmap, ADAU1701_PINCONF_0, val);

	val = 0;
	क्रम (i = 0; i < 6; i++)
		val |= adau1701->pin_config[i + 6] << (i * 4);

	regmap_ग_लिखो(adau1701->regmap, ADAU1701_PINCONF_1, val);

	वापस 0;

निकास_regulators_disable:

	regulator_bulk_disable(ARRAY_SIZE(adau1701->supplies), adau1701->supplies);
	वापस ret;
पूर्ण

अटल व्योम adau1701_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा adau1701 *adau1701 = snd_soc_component_get_drvdata(component);

	अगर (gpio_is_valid(adau1701->gpio_nreset))
		gpio_set_value_cansleep(adau1701->gpio_nreset, 0);

	regulator_bulk_disable(ARRAY_SIZE(adau1701->supplies), adau1701->supplies);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक adau1701_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा adau1701 *adau1701 = snd_soc_component_get_drvdata(component);

	regulator_bulk_disable(ARRAY_SIZE(adau1701->supplies),
			       adau1701->supplies);

	वापस 0;
पूर्ण

अटल पूर्णांक adau1701_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा adau1701 *adau1701 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

        ret = regulator_bulk_enable(ARRAY_SIZE(adau1701->supplies),
				    adau1701->supplies);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to enable regulators: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस adau1701_reset(component, adau1701->pll_clkभाग, 0);
पूर्ण
#अन्यथा
#घोषणा adau1701_resume 	शून्य
#घोषणा adau1701_suspend 	शून्य
#पूर्ण_अगर /* CONFIG_PM */

अटल स्थिर काष्ठा snd_soc_component_driver adau1701_component_drv = अणु
	.probe			= adau1701_probe,
	.हटाओ			= adau1701_हटाओ,
	.resume			= adau1701_resume,
	.suspend		= adau1701_suspend,
	.set_bias_level		= adau1701_set_bias_level,
	.controls		= adau1701_controls,
	.num_controls		= ARRAY_SIZE(adau1701_controls),
	.dapm_widमाला_लो		= adau1701_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(adau1701_dapm_widमाला_लो),
	.dapm_routes		= adau1701_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(adau1701_dapm_routes),
	.set_sysclk		= adau1701_set_sysclk,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config adau1701_regmap = अणु
	.reg_bits		= 16,
	.val_bits		= 32,
	.max_रेजिस्टर		= ADAU1701_MAX_REGISTER,
	.cache_type		= REGCACHE_RBTREE,
	.अस्थिर_reg		= adau1701_अस्थिर_reg,
	.reg_ग_लिखो		= adau1701_reg_ग_लिखो,
	.reg_पढ़ो		= adau1701_reg_पढ़ो,
पूर्ण;

अटल पूर्णांक adau1701_i2c_probe(काष्ठा i2c_client *client,
			      स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा adau1701 *adau1701;
	काष्ठा device *dev = &client->dev;
	पूर्णांक gpio_nreset = -EINVAL;
	पूर्णांक gpio_pll_mode[2] = अणु -EINVAL, -EINVAL पूर्ण;
	पूर्णांक ret, i;

	adau1701 = devm_kzalloc(dev, माप(*adau1701), GFP_KERNEL);
	अगर (!adau1701)
		वापस -ENOMEM;

	क्रम (i = 0; i < ARRAY_SIZE(supply_names); i++)
		adau1701->supplies[i].supply = supply_names[i];

	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(adau1701->supplies),
			adau1701->supplies);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to get regulators: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regulator_bulk_enable(ARRAY_SIZE(adau1701->supplies),
			adau1701->supplies);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to enable regulators: %d\n", ret);
		वापस ret;
	पूर्ण

	adau1701->client = client;
	adau1701->regmap = devm_regmap_init(dev, शून्य, client,
					    &adau1701_regmap);
	अगर (IS_ERR(adau1701->regmap)) अणु
		ret = PTR_ERR(adau1701->regmap);
		जाओ निकास_regulators_disable;
	पूर्ण


	अगर (dev->of_node) अणु
		gpio_nreset = of_get_named_gpio(dev->of_node, "reset-gpio", 0);
		अगर (gpio_nreset < 0 && gpio_nreset != -ENOENT) अणु
			ret = gpio_nreset;
			जाओ निकास_regulators_disable;
		पूर्ण

		gpio_pll_mode[0] = of_get_named_gpio(dev->of_node,
						   "adi,pll-mode-gpios", 0);
		अगर (gpio_pll_mode[0] < 0 && gpio_pll_mode[0] != -ENOENT) अणु
			ret = gpio_pll_mode[0];
			जाओ निकास_regulators_disable;
		पूर्ण

		gpio_pll_mode[1] = of_get_named_gpio(dev->of_node,
						   "adi,pll-mode-gpios", 1);
		अगर (gpio_pll_mode[1] < 0 && gpio_pll_mode[1] != -ENOENT) अणु
			ret = gpio_pll_mode[1];
			जाओ निकास_regulators_disable;
		पूर्ण

		of_property_पढ़ो_u32(dev->of_node, "adi,pll-clkdiv",
				     &adau1701->pll_clkभाग);

		of_property_पढ़ो_u8_array(dev->of_node, "adi,pin-config",
					  adau1701->pin_config,
					  ARRAY_SIZE(adau1701->pin_config));
	पूर्ण

	अगर (gpio_is_valid(gpio_nreset)) अणु
		ret = devm_gpio_request_one(dev, gpio_nreset, GPIOF_OUT_INIT_LOW,
					    "ADAU1701 Reset");
		अगर (ret < 0)
			जाओ निकास_regulators_disable;
	पूर्ण

	अगर (gpio_is_valid(gpio_pll_mode[0]) &&
	    gpio_is_valid(gpio_pll_mode[1])) अणु
		ret = devm_gpio_request_one(dev, gpio_pll_mode[0],
					    GPIOF_OUT_INIT_LOW,
					    "ADAU1701 PLL mode 0");
		अगर (ret < 0)
			जाओ निकास_regulators_disable;

		ret = devm_gpio_request_one(dev, gpio_pll_mode[1],
					    GPIOF_OUT_INIT_LOW,
					    "ADAU1701 PLL mode 1");
		अगर (ret < 0)
			जाओ निकास_regulators_disable;
	पूर्ण

	adau1701->gpio_nreset = gpio_nreset;
	adau1701->gpio_pll_mode[0] = gpio_pll_mode[0];
	adau1701->gpio_pll_mode[1] = gpio_pll_mode[1];

	i2c_set_clientdata(client, adau1701);

	adau1701->sigmadsp = devm_sigmadsp_init_i2c(client,
		&adau1701_sigmadsp_ops, ADAU1701_FIRMWARE);
	अगर (IS_ERR(adau1701->sigmadsp)) अणु
		ret = PTR_ERR(adau1701->sigmadsp);
		जाओ निकास_regulators_disable;
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_component(&client->dev,
			&adau1701_component_drv,
			&adau1701_dai, 1);

निकास_regulators_disable:

	regulator_bulk_disable(ARRAY_SIZE(adau1701->supplies), adau1701->supplies);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id adau1701_i2c_id[] = अणु
	अणु "adau1401", 0 पूर्ण,
	अणु "adau1401a", 0 पूर्ण,
	अणु "adau1701", 0 पूर्ण,
	अणु "adau1702", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, adau1701_i2c_id);

अटल काष्ठा i2c_driver adau1701_i2c_driver = अणु
	.driver = अणु
		.name	= "adau1701",
		.of_match_table	= of_match_ptr(adau1701_dt_ids),
	पूर्ण,
	.probe		= adau1701_i2c_probe,
	.id_table	= adau1701_i2c_id,
पूर्ण;

module_i2c_driver(adau1701_i2c_driver);

MODULE_DESCRIPTION("ASoC ADAU1701 SigmaDSP driver");
MODULE_AUTHOR("Cliff Cai <cliff.cai@analog.com>");
MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_LICENSE("GPL");
