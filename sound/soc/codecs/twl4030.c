<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ALSA SoC TWL4030 codec driver
 *
 * Author:      Steve Sakoman, <steve@sakoman.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/i2c.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/mfd/twl.h>
#समावेश <linux/slab.h>
#समावेश <linux/gpपन.स>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>

/* Register descriptions are here */
#समावेश <linux/mfd/twl4030-audपन.स>

/* TWL4030 PMBR1 Register */
#घोषणा TWL4030_PMBR1_REG		0x0D
/* TWL4030 PMBR1 Register GPIO6 mux bits */
#घोषणा TWL4030_GPIO6_PWM0_MUTE(value)	((value & 0x03) << 2)

#घोषणा TWL4030_CACHEREGNUM	(TWL4030_REG_MISC_SET_2 + 1)

/* codec निजी data */
काष्ठा twl4030_priv अणु
	अचिन्हित पूर्णांक codec_घातered;

	/* reference counts of AIF/APLL users */
	अचिन्हित पूर्णांक apll_enabled;

	काष्ठा snd_pcm_substream *master_substream;
	काष्ठा snd_pcm_substream *slave_substream;

	अचिन्हित पूर्णांक configured;
	अचिन्हित पूर्णांक rate;
	अचिन्हित पूर्णांक sample_bits;
	अचिन्हित पूर्णांक channels;

	अचिन्हित पूर्णांक sysclk;

	/* Output (with associated amp) states */
	u8 hsl_enabled, hsr_enabled;
	u8 earpiece_enabled;
	u8 predrivel_enabled, predriver_enabled;
	u8 carkitl_enabled, carkitr_enabled;
	u8 ctl_cache[TWL4030_REG_PRECKR_CTL - TWL4030_REG_EAR_CTL + 1];

	काष्ठा twl4030_codec_data *pdata;
पूर्ण;

अटल व्योम tw4030_init_ctl_cache(काष्ठा twl4030_priv *twl4030)
अणु
	पूर्णांक i;
	u8 byte;

	क्रम (i = TWL4030_REG_EAR_CTL; i <= TWL4030_REG_PRECKR_CTL; i++) अणु
		twl_i2c_पढ़ो_u8(TWL4030_MODULE_AUDIO_VOICE, &byte, i);
		twl4030->ctl_cache[i - TWL4030_REG_EAR_CTL] = byte;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक twl4030_पढ़ो(काष्ठा snd_soc_component *component, अचिन्हित पूर्णांक reg)
अणु
	काष्ठा twl4030_priv *twl4030 = snd_soc_component_get_drvdata(component);
	u8 value = 0;

	अगर (reg >= TWL4030_CACHEREGNUM)
		वापस -EIO;

	चयन (reg) अणु
	हाल TWL4030_REG_EAR_CTL:
	हाल TWL4030_REG_PREDL_CTL:
	हाल TWL4030_REG_PREDR_CTL:
	हाल TWL4030_REG_PRECKL_CTL:
	हाल TWL4030_REG_PRECKR_CTL:
	हाल TWL4030_REG_HS_GAIN_SET:
		value = twl4030->ctl_cache[reg - TWL4030_REG_EAR_CTL];
		अवरोध;
	शेष:
		twl_i2c_पढ़ो_u8(TWL4030_MODULE_AUDIO_VOICE, &value, reg);
		अवरोध;
	पूर्ण

	वापस value;
पूर्ण

अटल bool twl4030_can_ग_लिखो_to_chip(काष्ठा twl4030_priv *twl4030,
				      अचिन्हित पूर्णांक reg)
अणु
	bool ग_लिखो_to_reg = false;

	/* Decide अगर the given रेजिस्टर can be written */
	चयन (reg) अणु
	हाल TWL4030_REG_EAR_CTL:
		अगर (twl4030->earpiece_enabled)
			ग_लिखो_to_reg = true;
		अवरोध;
	हाल TWL4030_REG_PREDL_CTL:
		अगर (twl4030->predrivel_enabled)
			ग_लिखो_to_reg = true;
		अवरोध;
	हाल TWL4030_REG_PREDR_CTL:
		अगर (twl4030->predriver_enabled)
			ग_लिखो_to_reg = true;
		अवरोध;
	हाल TWL4030_REG_PRECKL_CTL:
		अगर (twl4030->carkitl_enabled)
			ग_लिखो_to_reg = true;
		अवरोध;
	हाल TWL4030_REG_PRECKR_CTL:
		अगर (twl4030->carkitr_enabled)
			ग_लिखो_to_reg = true;
		अवरोध;
	हाल TWL4030_REG_HS_GAIN_SET:
		अगर (twl4030->hsl_enabled || twl4030->hsr_enabled)
			ग_लिखो_to_reg = true;
		अवरोध;
	शेष:
		/* All other रेजिस्टर can be written */
		ग_लिखो_to_reg = true;
		अवरोध;
	पूर्ण

	वापस ग_लिखो_to_reg;
पूर्ण

अटल पूर्णांक twl4030_ग_लिखो(काष्ठा snd_soc_component *component, अचिन्हित पूर्णांक reg,
			 अचिन्हित पूर्णांक value)
अणु
	काष्ठा twl4030_priv *twl4030 = snd_soc_component_get_drvdata(component);

	/* Update the ctl cache */
	चयन (reg) अणु
	हाल TWL4030_REG_EAR_CTL:
	हाल TWL4030_REG_PREDL_CTL:
	हाल TWL4030_REG_PREDR_CTL:
	हाल TWL4030_REG_PRECKL_CTL:
	हाल TWL4030_REG_PRECKR_CTL:
	हाल TWL4030_REG_HS_GAIN_SET:
		twl4030->ctl_cache[reg - TWL4030_REG_EAR_CTL] = value;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (twl4030_can_ग_लिखो_to_chip(twl4030, reg))
		वापस twl_i2c_ग_लिखो_u8(TWL4030_MODULE_AUDIO_VOICE, value, reg);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम twl4030_रुको_ms(पूर्णांक समय)
अणु
	अगर (समय < 60) अणु
		समय *= 1000;
		usleep_range(समय, समय + 500);
	पूर्ण अन्यथा अणु
		msleep(समय);
	पूर्ण
पूर्ण

अटल व्योम twl4030_codec_enable(काष्ठा snd_soc_component *component, पूर्णांक enable)
अणु
	काष्ठा twl4030_priv *twl4030 = snd_soc_component_get_drvdata(component);
	पूर्णांक mode;

	अगर (enable == twl4030->codec_घातered)
		वापस;

	अगर (enable)
		mode = twl4030_audio_enable_resource(TWL4030_AUDIO_RES_POWER);
	अन्यथा
		mode = twl4030_audio_disable_resource(TWL4030_AUDIO_RES_POWER);

	अगर (mode >= 0)
		twl4030->codec_घातered = enable;

	/* REVISIT: this delay is present in TI sample drivers */
	/* but there seems to be no TRM requirement क्रम it     */
	udelay(10);
पूर्ण

अटल व्योम twl4030_setup_pdata_of(काष्ठा twl4030_codec_data *pdata,
				   काष्ठा device_node *node)
अणु
	पूर्णांक value;

	of_property_पढ़ो_u32(node, "ti,digimic_delay",
			     &pdata->digimic_delay);
	of_property_पढ़ो_u32(node, "ti,ramp_delay_value",
			     &pdata->ramp_delay_value);
	of_property_पढ़ो_u32(node, "ti,offset_cncl_path",
			     &pdata->offset_cncl_path);
	अगर (!of_property_पढ़ो_u32(node, "ti,hs_extmute", &value))
		pdata->hs_exपंचांगute = value;

	pdata->hs_exपंचांगute_gpio = of_get_named_gpio(node,
						   "ti,hs_extmute_gpio", 0);
	अगर (gpio_is_valid(pdata->hs_exपंचांगute_gpio))
		pdata->hs_exपंचांगute = 1;
पूर्ण

अटल काष्ठा twl4030_codec_data *twl4030_get_pdata(काष्ठा snd_soc_component *component)
अणु
	काष्ठा twl4030_codec_data *pdata = dev_get_platdata(component->dev);
	काष्ठा device_node *twl4030_codec_node = शून्य;

	twl4030_codec_node = of_get_child_by_name(component->dev->parent->of_node,
						  "codec");

	अगर (!pdata && twl4030_codec_node) अणु
		pdata = devm_kzalloc(component->dev,
				     माप(काष्ठा twl4030_codec_data),
				     GFP_KERNEL);
		अगर (!pdata) अणु
			of_node_put(twl4030_codec_node);
			वापस शून्य;
		पूर्ण
		twl4030_setup_pdata_of(pdata, twl4030_codec_node);
		of_node_put(twl4030_codec_node);
	पूर्ण

	वापस pdata;
पूर्ण

अटल व्योम twl4030_init_chip(काष्ठा snd_soc_component *component)
अणु
	काष्ठा twl4030_codec_data *pdata;
	काष्ठा twl4030_priv *twl4030 = snd_soc_component_get_drvdata(component);
	u8 reg, byte;
	पूर्णांक i = 0;

	pdata = twl4030_get_pdata(component);

	अगर (pdata && pdata->hs_exपंचांगute) अणु
		अगर (gpio_is_valid(pdata->hs_exपंचांगute_gpio)) अणु
			पूर्णांक ret;

			अगर (!pdata->hs_exपंचांगute_gpio)
				dev_warn(component->dev,
					"Extmute GPIO is 0 is this correct?\n");

			ret = gpio_request_one(pdata->hs_exपंचांगute_gpio,
					       GPIOF_OUT_INIT_LOW,
					       "hs_extmute");
			अगर (ret) अणु
				dev_err(component->dev,
					"Failed to get hs_extmute GPIO\n");
				pdata->hs_exपंचांगute_gpio = -1;
			पूर्ण
		पूर्ण अन्यथा अणु
			u8 pin_mux;

			/* Set TWL4030 GPIO6 as EXTMUTE संकेत */
			twl_i2c_पढ़ो_u8(TWL4030_MODULE_INTBR, &pin_mux,
					TWL4030_PMBR1_REG);
			pin_mux &= ~TWL4030_GPIO6_PWM0_MUTE(0x03);
			pin_mux |= TWL4030_GPIO6_PWM0_MUTE(0x02);
			twl_i2c_ग_लिखो_u8(TWL4030_MODULE_INTBR, pin_mux,
					 TWL4030_PMBR1_REG);
		पूर्ण
	पूर्ण

	/* Initialize the local ctl रेजिस्टर cache */
	tw4030_init_ctl_cache(twl4030);

	/* anti-pop when changing analog gain */
	reg = twl4030_पढ़ो(component, TWL4030_REG_MISC_SET_1);
	twl4030_ग_लिखो(component, TWL4030_REG_MISC_SET_1,
		      reg | TWL4030_SMOOTH_ANAVOL_EN);

	twl4030_ग_लिखो(component, TWL4030_REG_OPTION,
		      TWL4030_ATXL1_EN | TWL4030_ATXR1_EN |
		      TWL4030_ARXL2_EN | TWL4030_ARXR2_EN);

	/* REG_ARXR2_APGA_CTL reset according to the TRM: 0dB, DA_EN */
	twl4030_ग_लिखो(component, TWL4030_REG_ARXR2_APGA_CTL, 0x32);

	/* Machine dependent setup */
	अगर (!pdata)
		वापस;

	twl4030->pdata = pdata;

	reg = twl4030_पढ़ो(component, TWL4030_REG_HS_POPN_SET);
	reg &= ~TWL4030_RAMP_DELAY;
	reg |= (pdata->ramp_delay_value << 2);
	twl4030_ग_लिखो(component, TWL4030_REG_HS_POPN_SET, reg);

	/* initiate offset cancellation */
	twl4030_codec_enable(component, 1);

	reg = twl4030_पढ़ो(component, TWL4030_REG_ANAMICL);
	reg &= ~TWL4030_OFFSET_CNCL_SEL;
	reg |= pdata->offset_cncl_path;
	twl4030_ग_लिखो(component, TWL4030_REG_ANAMICL,
		      reg | TWL4030_CNCL_OFFSET_START);

	/*
	 * Wait क्रम offset cancellation to complete.
	 * Since this takes a जबतक, करो not slam the i2c.
	 * Start polling the status after ~20ms.
	 */
	msleep(20);
	करो अणु
		usleep_range(1000, 2000);
		twl_set_regcache_bypass(TWL4030_MODULE_AUDIO_VOICE, true);
		twl_i2c_पढ़ो_u8(TWL4030_MODULE_AUDIO_VOICE, &byte,
				TWL4030_REG_ANAMICL);
		twl_set_regcache_bypass(TWL4030_MODULE_AUDIO_VOICE, false);
	पूर्ण जबतक ((i++ < 100) &&
		 ((byte & TWL4030_CNCL_OFFSET_START) ==
		  TWL4030_CNCL_OFFSET_START));

	twl4030_codec_enable(component, 0);
पूर्ण

अटल व्योम twl4030_apll_enable(काष्ठा snd_soc_component *component, पूर्णांक enable)
अणु
	काष्ठा twl4030_priv *twl4030 = snd_soc_component_get_drvdata(component);

	अगर (enable) अणु
		twl4030->apll_enabled++;
		अगर (twl4030->apll_enabled == 1)
			twl4030_audio_enable_resource(
							TWL4030_AUDIO_RES_APLL);
	पूर्ण अन्यथा अणु
		twl4030->apll_enabled--;
		अगर (!twl4030->apll_enabled)
			twl4030_audio_disable_resource(
							TWL4030_AUDIO_RES_APLL);
	पूर्ण
पूर्ण

/* Earpiece */
अटल स्थिर काष्ठा snd_kcontrol_new twl4030_dapm_earpiece_controls[] = अणु
	SOC_DAPM_SINGLE("Voice", TWL4030_REG_EAR_CTL, 0, 1, 0),
	SOC_DAPM_SINGLE("AudioL1", TWL4030_REG_EAR_CTL, 1, 1, 0),
	SOC_DAPM_SINGLE("AudioL2", TWL4030_REG_EAR_CTL, 2, 1, 0),
	SOC_DAPM_SINGLE("AudioR1", TWL4030_REG_EAR_CTL, 3, 1, 0),
पूर्ण;

/* PreDrive Left */
अटल स्थिर काष्ठा snd_kcontrol_new twl4030_dapm_predrivel_controls[] = अणु
	SOC_DAPM_SINGLE("Voice", TWL4030_REG_PREDL_CTL, 0, 1, 0),
	SOC_DAPM_SINGLE("AudioL1", TWL4030_REG_PREDL_CTL, 1, 1, 0),
	SOC_DAPM_SINGLE("AudioL2", TWL4030_REG_PREDL_CTL, 2, 1, 0),
	SOC_DAPM_SINGLE("AudioR2", TWL4030_REG_PREDL_CTL, 3, 1, 0),
पूर्ण;

/* PreDrive Right */
अटल स्थिर काष्ठा snd_kcontrol_new twl4030_dapm_predriver_controls[] = अणु
	SOC_DAPM_SINGLE("Voice", TWL4030_REG_PREDR_CTL, 0, 1, 0),
	SOC_DAPM_SINGLE("AudioR1", TWL4030_REG_PREDR_CTL, 1, 1, 0),
	SOC_DAPM_SINGLE("AudioR2", TWL4030_REG_PREDR_CTL, 2, 1, 0),
	SOC_DAPM_SINGLE("AudioL2", TWL4030_REG_PREDR_CTL, 3, 1, 0),
पूर्ण;

/* Headset Left */
अटल स्थिर काष्ठा snd_kcontrol_new twl4030_dapm_hsol_controls[] = अणु
	SOC_DAPM_SINGLE("Voice", TWL4030_REG_HS_SEL, 0, 1, 0),
	SOC_DAPM_SINGLE("AudioL1", TWL4030_REG_HS_SEL, 1, 1, 0),
	SOC_DAPM_SINGLE("AudioL2", TWL4030_REG_HS_SEL, 2, 1, 0),
पूर्ण;

/* Headset Right */
अटल स्थिर काष्ठा snd_kcontrol_new twl4030_dapm_hsor_controls[] = अणु
	SOC_DAPM_SINGLE("Voice", TWL4030_REG_HS_SEL, 3, 1, 0),
	SOC_DAPM_SINGLE("AudioR1", TWL4030_REG_HS_SEL, 4, 1, 0),
	SOC_DAPM_SINGLE("AudioR2", TWL4030_REG_HS_SEL, 5, 1, 0),
पूर्ण;

/* Carkit Left */
अटल स्थिर काष्ठा snd_kcontrol_new twl4030_dapm_carkitl_controls[] = अणु
	SOC_DAPM_SINGLE("Voice", TWL4030_REG_PRECKL_CTL, 0, 1, 0),
	SOC_DAPM_SINGLE("AudioL1", TWL4030_REG_PRECKL_CTL, 1, 1, 0),
	SOC_DAPM_SINGLE("AudioL2", TWL4030_REG_PRECKL_CTL, 2, 1, 0),
पूर्ण;

/* Carkit Right */
अटल स्थिर काष्ठा snd_kcontrol_new twl4030_dapm_carkitr_controls[] = अणु
	SOC_DAPM_SINGLE("Voice", TWL4030_REG_PRECKR_CTL, 0, 1, 0),
	SOC_DAPM_SINGLE("AudioR1", TWL4030_REG_PRECKR_CTL, 1, 1, 0),
	SOC_DAPM_SINGLE("AudioR2", TWL4030_REG_PRECKR_CTL, 2, 1, 0),
पूर्ण;

/* Handsमुक्त Left */
अटल स्थिर अक्षर *twl4030_handsमुक्तl_texts[] =
		अणु"Voice", "AudioL1", "AudioL2", "AudioR2"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(twl4030_handsमुक्तl_क्रमागत,
			    TWL4030_REG_HFL_CTL, 0,
			    twl4030_handsमुक्तl_texts);

अटल स्थिर काष्ठा snd_kcontrol_new twl4030_dapm_handsमुक्तl_control =
SOC_DAPM_ENUM("Route", twl4030_handsमुक्तl_क्रमागत);

/* Handsमुक्त Left भव mute */
अटल स्थिर काष्ठा snd_kcontrol_new twl4030_dapm_handsमुक्तlmute_control =
	SOC_DAPM_SINGLE_VIRT("Switch", 1);

/* Handsमुक्त Right */
अटल स्थिर अक्षर *twl4030_handsमुक्तr_texts[] =
		अणु"Voice", "AudioR1", "AudioR2", "AudioL2"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(twl4030_handsमुक्तr_क्रमागत,
			    TWL4030_REG_HFR_CTL, 0,
			    twl4030_handsमुक्तr_texts);

अटल स्थिर काष्ठा snd_kcontrol_new twl4030_dapm_handsमुक्तr_control =
SOC_DAPM_ENUM("Route", twl4030_handsमुक्तr_क्रमागत);

/* Handsमुक्त Right भव mute */
अटल स्थिर काष्ठा snd_kcontrol_new twl4030_dapm_handsमुक्तrmute_control =
	SOC_DAPM_SINGLE_VIRT("Switch", 1);

/* Vibra */
/* Vibra audio path selection */
अटल स्थिर अक्षर *twl4030_vibra_texts[] =
		अणु"AudioL1", "AudioR1", "AudioL2", "AudioR2"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(twl4030_vibra_क्रमागत,
			    TWL4030_REG_VIBRA_CTL, 2,
			    twl4030_vibra_texts);

अटल स्थिर काष्ठा snd_kcontrol_new twl4030_dapm_vibra_control =
SOC_DAPM_ENUM("Route", twl4030_vibra_क्रमागत);

/* Vibra path selection: local vibrator (PWM) or audio driven */
अटल स्थिर अक्षर *twl4030_vibrapath_texts[] =
		अणु"Local vibrator", "Audio"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(twl4030_vibrapath_क्रमागत,
			    TWL4030_REG_VIBRA_CTL, 4,
			    twl4030_vibrapath_texts);

अटल स्थिर काष्ठा snd_kcontrol_new twl4030_dapm_vibrapath_control =
SOC_DAPM_ENUM("Route", twl4030_vibrapath_क्रमागत);

/* Left analog microphone selection */
अटल स्थिर काष्ठा snd_kcontrol_new twl4030_dapm_analoglmic_controls[] = अणु
	SOC_DAPM_SINGLE("Main Mic Capture Switch",
			TWL4030_REG_ANAMICL, 0, 1, 0),
	SOC_DAPM_SINGLE("Headset Mic Capture Switch",
			TWL4030_REG_ANAMICL, 1, 1, 0),
	SOC_DAPM_SINGLE("AUXL Capture Switch",
			TWL4030_REG_ANAMICL, 2, 1, 0),
	SOC_DAPM_SINGLE("Carkit Mic Capture Switch",
			TWL4030_REG_ANAMICL, 3, 1, 0),
पूर्ण;

/* Right analog microphone selection */
अटल स्थिर काष्ठा snd_kcontrol_new twl4030_dapm_analogrmic_controls[] = अणु
	SOC_DAPM_SINGLE("Sub Mic Capture Switch", TWL4030_REG_ANAMICR, 0, 1, 0),
	SOC_DAPM_SINGLE("AUXR Capture Switch", TWL4030_REG_ANAMICR, 2, 1, 0),
पूर्ण;

/* TX1 L/R Analog/Digital microphone selection */
अटल स्थिर अक्षर *twl4030_micpathtx1_texts[] =
		अणु"Analog", "Digimic0"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(twl4030_micpathtx1_क्रमागत,
			    TWL4030_REG_ADCMICSEL, 0,
			    twl4030_micpathtx1_texts);

अटल स्थिर काष्ठा snd_kcontrol_new twl4030_dapm_micpathtx1_control =
SOC_DAPM_ENUM("Route", twl4030_micpathtx1_क्रमागत);

/* TX2 L/R Analog/Digital microphone selection */
अटल स्थिर अक्षर *twl4030_micpathtx2_texts[] =
		अणु"Analog", "Digimic1"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(twl4030_micpathtx2_क्रमागत,
			    TWL4030_REG_ADCMICSEL, 2,
			    twl4030_micpathtx2_texts);

अटल स्थिर काष्ठा snd_kcontrol_new twl4030_dapm_micpathtx2_control =
SOC_DAPM_ENUM("Route", twl4030_micpathtx2_क्रमागत);

/* Analog bypass क्रम AudioR1 */
अटल स्थिर काष्ठा snd_kcontrol_new twl4030_dapm_abypassr1_control =
	SOC_DAPM_SINGLE("Switch", TWL4030_REG_ARXR1_APGA_CTL, 2, 1, 0);

/* Analog bypass क्रम AudioL1 */
अटल स्थिर काष्ठा snd_kcontrol_new twl4030_dapm_abypassl1_control =
	SOC_DAPM_SINGLE("Switch", TWL4030_REG_ARXL1_APGA_CTL, 2, 1, 0);

/* Analog bypass क्रम AudioR2 */
अटल स्थिर काष्ठा snd_kcontrol_new twl4030_dapm_abypassr2_control =
	SOC_DAPM_SINGLE("Switch", TWL4030_REG_ARXR2_APGA_CTL, 2, 1, 0);

/* Analog bypass क्रम AudioL2 */
अटल स्थिर काष्ठा snd_kcontrol_new twl4030_dapm_abypassl2_control =
	SOC_DAPM_SINGLE("Switch", TWL4030_REG_ARXL2_APGA_CTL, 2, 1, 0);

/* Analog bypass क्रम Voice */
अटल स्थिर काष्ठा snd_kcontrol_new twl4030_dapm_abypassv_control =
	SOC_DAPM_SINGLE("Switch", TWL4030_REG_VDL_APGA_CTL, 2, 1, 0);

/* Digital bypass gain, mute instead of -30dB */
अटल स्थिर DECLARE_TLV_DB_RANGE(twl4030_dapm_dbypass_tlv,
	0, 1, TLV_DB_SCALE_ITEM(-3000, 600, 1),
	2, 3, TLV_DB_SCALE_ITEM(-2400, 0, 0),
	4, 7, TLV_DB_SCALE_ITEM(-1800, 600, 0)
);

/* Digital bypass left (TX1L -> RX2L) */
अटल स्थिर काष्ठा snd_kcontrol_new twl4030_dapm_dbypassl_control =
	SOC_DAPM_SINGLE_TLV("Volume",
			TWL4030_REG_ATX2ARXPGA, 3, 7, 0,
			twl4030_dapm_dbypass_tlv);

/* Digital bypass right (TX1R -> RX2R) */
अटल स्थिर काष्ठा snd_kcontrol_new twl4030_dapm_dbypassr_control =
	SOC_DAPM_SINGLE_TLV("Volume",
			TWL4030_REG_ATX2ARXPGA, 0, 7, 0,
			twl4030_dapm_dbypass_tlv);

/*
 * Voice Sidetone GAIN volume control:
 * from -51 to -10 dB in 1 dB steps (mute instead of -51 dB)
 */
अटल DECLARE_TLV_DB_SCALE(twl4030_dapm_dbypassv_tlv, -5100, 100, 1);

/* Digital bypass voice: sidetone (VUL -> VDL)*/
अटल स्थिर काष्ठा snd_kcontrol_new twl4030_dapm_dbypassv_control =
	SOC_DAPM_SINGLE_TLV("Volume",
			TWL4030_REG_VSTPGA, 0, 0x29, 0,
			twl4030_dapm_dbypassv_tlv);

/*
 * Output PGA builder:
 * Handle the muting and unmuting of the given output (turning off the
 * amplअगरier associated with the output pin)
 * On mute bypass the reg_cache and ग_लिखो 0 to the रेजिस्टर
 * On unmute: restore the रेजिस्टर content from the reg_cache
 * Outमाला_दो handled in this way:  Earpiece, PreDrivL/R, CarkitL/R
 */
#घोषणा TWL4030_OUTPUT_PGA(pin_name, reg, mask)				\
अटल पूर्णांक pin_name##pga_event(काष्ठा snd_soc_dapm_widget *w,		\
			       काष्ठा snd_kcontrol *kcontrol, पूर्णांक event) \
अणु									\
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);	\
	काष्ठा twl4030_priv *twl4030 = snd_soc_component_get_drvdata(component); \
									\
	चयन (event) अणु						\
	हाल SND_SOC_DAPM_POST_PMU:					\
		twl4030->pin_name##_enabled = 1;			\
		twl4030_ग_लिखो(component, reg, twl4030_पढ़ो(component, reg));	\
		अवरोध;							\
	हाल SND_SOC_DAPM_POST_PMD:					\
		twl4030->pin_name##_enabled = 0;			\
		twl_i2c_ग_लिखो_u8(TWL4030_MODULE_AUDIO_VOICE, 0, reg);	\
		अवरोध;							\
	पूर्ण								\
	वापस 0;							\
पूर्ण

TWL4030_OUTPUT_PGA(earpiece, TWL4030_REG_EAR_CTL, TWL4030_EAR_GAIN);
TWL4030_OUTPUT_PGA(predrivel, TWL4030_REG_PREDL_CTL, TWL4030_PREDL_GAIN);
TWL4030_OUTPUT_PGA(predriver, TWL4030_REG_PREDR_CTL, TWL4030_PREDR_GAIN);
TWL4030_OUTPUT_PGA(carkitl, TWL4030_REG_PRECKL_CTL, TWL4030_PRECKL_GAIN);
TWL4030_OUTPUT_PGA(carkitr, TWL4030_REG_PRECKR_CTL, TWL4030_PRECKR_GAIN);

अटल व्योम handsमुक्त_ramp(काष्ठा snd_soc_component *component, पूर्णांक reg, पूर्णांक ramp)
अणु
	अचिन्हित अक्षर hs_ctl;

	hs_ctl = twl4030_पढ़ो(component, reg);

	अगर (ramp) अणु
		/* HF ramp-up */
		hs_ctl |= TWL4030_HF_CTL_REF_EN;
		twl4030_ग_लिखो(component, reg, hs_ctl);
		udelay(10);
		hs_ctl |= TWL4030_HF_CTL_RAMP_EN;
		twl4030_ग_लिखो(component, reg, hs_ctl);
		udelay(40);
		hs_ctl |= TWL4030_HF_CTL_LOOP_EN;
		hs_ctl |= TWL4030_HF_CTL_HB_EN;
		twl4030_ग_लिखो(component, reg, hs_ctl);
	पूर्ण अन्यथा अणु
		/* HF ramp-करोwn */
		hs_ctl &= ~TWL4030_HF_CTL_LOOP_EN;
		hs_ctl &= ~TWL4030_HF_CTL_HB_EN;
		twl4030_ग_लिखो(component, reg, hs_ctl);
		hs_ctl &= ~TWL4030_HF_CTL_RAMP_EN;
		twl4030_ग_लिखो(component, reg, hs_ctl);
		udelay(40);
		hs_ctl &= ~TWL4030_HF_CTL_REF_EN;
		twl4030_ग_लिखो(component, reg, hs_ctl);
	पूर्ण
पूर्ण

अटल पूर्णांक handsमुक्तlpga_event(काष्ठा snd_soc_dapm_widget *w,
			       काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		handsमुक्त_ramp(component, TWL4030_REG_HFL_CTL, 1);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		handsमुक्त_ramp(component, TWL4030_REG_HFL_CTL, 0);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक handsमुक्तrpga_event(काष्ठा snd_soc_dapm_widget *w,
			       काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		handsमुक्त_ramp(component, TWL4030_REG_HFR_CTL, 1);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		handsमुक्त_ramp(component, TWL4030_REG_HFR_CTL, 0);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक vibramux_event(काष्ठा snd_soc_dapm_widget *w,
			  काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	twl4030_ग_लिखो(component, TWL4030_REG_VIBRA_SET, 0xff);
	वापस 0;
पूर्ण

अटल पूर्णांक apll_event(काष्ठा snd_soc_dapm_widget *w,
		      काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		twl4030_apll_enable(component, 1);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		twl4030_apll_enable(component, 0);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक aअगर_event(काष्ठा snd_soc_dapm_widget *w,
		     काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	u8 audio_अगर;

	audio_अगर = twl4030_पढ़ो(component, TWL4030_REG_AUDIO_IF);
	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		/* Enable AIF */
		/* enable the PLL beक्रमe we use it to घड़ी the DAI */
		twl4030_apll_enable(component, 1);

		twl4030_ग_लिखो(component, TWL4030_REG_AUDIO_IF,
			      audio_अगर | TWL4030_AIF_EN);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		/* disable the DAI beक्रमe we stop it's source PLL */
		twl4030_ग_लिखो(component, TWL4030_REG_AUDIO_IF,
			      audio_अगर &  ~TWL4030_AIF_EN);
		twl4030_apll_enable(component, 0);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम headset_ramp(काष्ठा snd_soc_component *component, पूर्णांक ramp)
अणु
	अचिन्हित अक्षर hs_gain, hs_pop;
	काष्ठा twl4030_priv *twl4030 = snd_soc_component_get_drvdata(component);
	काष्ठा twl4030_codec_data *pdata = twl4030->pdata;
	/* Base values क्रम ramp delay calculation: 2^19 - 2^26 */
	अचिन्हित पूर्णांक ramp_base[] = अणु524288, 1048576, 2097152, 4194304,
				    8388608, 16777216, 33554432, 67108864पूर्ण;
	अचिन्हित पूर्णांक delay;

	hs_gain = twl4030_पढ़ो(component, TWL4030_REG_HS_GAIN_SET);
	hs_pop = twl4030_पढ़ो(component, TWL4030_REG_HS_POPN_SET);
	delay = (ramp_base[(hs_pop & TWL4030_RAMP_DELAY) >> 2] /
		twl4030->sysclk) + 1;

	/* Enable बाह्यal mute control, this dramatically reduces
	 * the pop-noise */
	अगर (pdata && pdata->hs_exपंचांगute) अणु
		अगर (gpio_is_valid(pdata->hs_exपंचांगute_gpio)) अणु
			gpio_set_value(pdata->hs_exपंचांगute_gpio, 1);
		पूर्ण अन्यथा अणु
			hs_pop |= TWL4030_EXTMUTE;
			twl4030_ग_लिखो(component, TWL4030_REG_HS_POPN_SET, hs_pop);
		पूर्ण
	पूर्ण

	अगर (ramp) अणु
		/* Headset ramp-up according to the TRM */
		hs_pop |= TWL4030_VMID_EN;
		twl4030_ग_लिखो(component, TWL4030_REG_HS_POPN_SET, hs_pop);
		/* Actually ग_लिखो to the रेजिस्टर */
		twl_i2c_ग_लिखो_u8(TWL4030_MODULE_AUDIO_VOICE, hs_gain,
				 TWL4030_REG_HS_GAIN_SET);
		hs_pop |= TWL4030_RAMP_EN;
		twl4030_ग_लिखो(component, TWL4030_REG_HS_POPN_SET, hs_pop);
		/* Wait ramp delay समय + 1, so the VMID can settle */
		twl4030_रुको_ms(delay);
	पूर्ण अन्यथा अणु
		/* Headset ramp-करोwn _not_ according to
		 * the TRM, but in a way that it is working */
		hs_pop &= ~TWL4030_RAMP_EN;
		twl4030_ग_लिखो(component, TWL4030_REG_HS_POPN_SET, hs_pop);
		/* Wait ramp delay समय + 1, so the VMID can settle */
		twl4030_रुको_ms(delay);
		/* Bypass the reg_cache to mute the headset */
		twl_i2c_ग_लिखो_u8(TWL4030_MODULE_AUDIO_VOICE, hs_gain & (~0x0f),
				 TWL4030_REG_HS_GAIN_SET);

		hs_pop &= ~TWL4030_VMID_EN;
		twl4030_ग_लिखो(component, TWL4030_REG_HS_POPN_SET, hs_pop);
	पूर्ण

	/* Disable बाह्यal mute */
	अगर (pdata && pdata->hs_exपंचांगute) अणु
		अगर (gpio_is_valid(pdata->hs_exपंचांगute_gpio)) अणु
			gpio_set_value(pdata->hs_exपंचांगute_gpio, 0);
		पूर्ण अन्यथा अणु
			hs_pop &= ~TWL4030_EXTMUTE;
			twl4030_ग_लिखो(component, TWL4030_REG_HS_POPN_SET, hs_pop);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक headsetlpga_event(काष्ठा snd_soc_dapm_widget *w,
			     काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा twl4030_priv *twl4030 = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		/* Do the ramp-up only once */
		अगर (!twl4030->hsr_enabled)
			headset_ramp(component, 1);

		twl4030->hsl_enabled = 1;
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		/* Do the ramp-करोwn only अगर both headsetL/R is disabled */
		अगर (!twl4030->hsr_enabled)
			headset_ramp(component, 0);

		twl4030->hsl_enabled = 0;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक headsetrpga_event(काष्ठा snd_soc_dapm_widget *w,
			     काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा twl4030_priv *twl4030 = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		/* Do the ramp-up only once */
		अगर (!twl4030->hsl_enabled)
			headset_ramp(component, 1);

		twl4030->hsr_enabled = 1;
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		/* Do the ramp-करोwn only अगर both headsetL/R is disabled */
		अगर (!twl4030->hsl_enabled)
			headset_ramp(component, 0);

		twl4030->hsr_enabled = 0;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक digimic_event(काष्ठा snd_soc_dapm_widget *w,
			 काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा twl4030_priv *twl4030 = snd_soc_component_get_drvdata(component);
	काष्ठा twl4030_codec_data *pdata = twl4030->pdata;

	अगर (pdata && pdata->digimic_delay)
		twl4030_रुको_ms(pdata->digimic_delay);
	वापस 0;
पूर्ण

/*
 * Some of the gain controls in TWL (mostly those which are associated with
 * the outमाला_दो) are implemented in an पूर्णांकeresting way:
 * 0x0 : Power करोwn (mute)
 * 0x1 : 6dB
 * 0x2 : 0 dB
 * 0x3 : -6 dB
 * Inverting not going to help with these.
 * Custom volsw and volsw_2r get/put functions to handle these gain bits.
 */
अटल पूर्णांक snd_soc_get_volsw_twl4030(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा soc_mixer_control *mc =
		(काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	अचिन्हित पूर्णांक reg = mc->reg;
	अचिन्हित पूर्णांक shअगरt = mc->shअगरt;
	अचिन्हित पूर्णांक rshअगरt = mc->rshअगरt;
	पूर्णांक max = mc->max;
	पूर्णांक mask = (1 << fls(max)) - 1;

	ucontrol->value.पूर्णांकeger.value[0] =
		(twl4030_पढ़ो(component, reg) >> shअगरt) & mask;
	अगर (ucontrol->value.पूर्णांकeger.value[0])
		ucontrol->value.पूर्णांकeger.value[0] =
			max + 1 - ucontrol->value.पूर्णांकeger.value[0];

	अगर (shअगरt != rshअगरt) अणु
		ucontrol->value.पूर्णांकeger.value[1] =
			(twl4030_पढ़ो(component, reg) >> rshअगरt) & mask;
		अगर (ucontrol->value.पूर्णांकeger.value[1])
			ucontrol->value.पूर्णांकeger.value[1] =
				max + 1 - ucontrol->value.पूर्णांकeger.value[1];
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_soc_put_volsw_twl4030(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा soc_mixer_control *mc =
		(काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	अचिन्हित पूर्णांक reg = mc->reg;
	अचिन्हित पूर्णांक shअगरt = mc->shअगरt;
	अचिन्हित पूर्णांक rshअगरt = mc->rshअगरt;
	पूर्णांक max = mc->max;
	पूर्णांक mask = (1 << fls(max)) - 1;
	अचिन्हित लघु val, val2, val_mask;

	val = (ucontrol->value.पूर्णांकeger.value[0] & mask);

	val_mask = mask << shअगरt;
	अगर (val)
		val = max + 1 - val;
	val = val << shअगरt;
	अगर (shअगरt != rshअगरt) अणु
		val2 = (ucontrol->value.पूर्णांकeger.value[1] & mask);
		val_mask |= mask << rshअगरt;
		अगर (val2)
			val2 = max + 1 - val2;
		val |= val2 << rshअगरt;
	पूर्ण
	वापस snd_soc_component_update_bits(component, reg, val_mask, val);
पूर्ण

अटल पूर्णांक snd_soc_get_volsw_r2_twl4030(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा soc_mixer_control *mc =
		(काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	अचिन्हित पूर्णांक reg = mc->reg;
	अचिन्हित पूर्णांक reg2 = mc->rreg;
	अचिन्हित पूर्णांक shअगरt = mc->shअगरt;
	पूर्णांक max = mc->max;
	पूर्णांक mask = (1<<fls(max))-1;

	ucontrol->value.पूर्णांकeger.value[0] =
		(twl4030_पढ़ो(component, reg) >> shअगरt) & mask;
	ucontrol->value.पूर्णांकeger.value[1] =
		(twl4030_पढ़ो(component, reg2) >> shअगरt) & mask;

	अगर (ucontrol->value.पूर्णांकeger.value[0])
		ucontrol->value.पूर्णांकeger.value[0] =
			max + 1 - ucontrol->value.पूर्णांकeger.value[0];
	अगर (ucontrol->value.पूर्णांकeger.value[1])
		ucontrol->value.पूर्णांकeger.value[1] =
			max + 1 - ucontrol->value.पूर्णांकeger.value[1];

	वापस 0;
पूर्ण

अटल पूर्णांक snd_soc_put_volsw_r2_twl4030(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा soc_mixer_control *mc =
		(काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	अचिन्हित पूर्णांक reg = mc->reg;
	अचिन्हित पूर्णांक reg2 = mc->rreg;
	अचिन्हित पूर्णांक shअगरt = mc->shअगरt;
	पूर्णांक max = mc->max;
	पूर्णांक mask = (1 << fls(max)) - 1;
	पूर्णांक err;
	अचिन्हित लघु val, val2, val_mask;

	val_mask = mask << shअगरt;
	val = (ucontrol->value.पूर्णांकeger.value[0] & mask);
	val2 = (ucontrol->value.पूर्णांकeger.value[1] & mask);

	अगर (val)
		val = max + 1 - val;
	अगर (val2)
		val2 = max + 1 - val2;

	val = val << shअगरt;
	val2 = val2 << shअगरt;

	err = snd_soc_component_update_bits(component, reg, val_mask, val);
	अगर (err < 0)
		वापस err;

	err = snd_soc_component_update_bits(component, reg2, val_mask, val2);
	वापस err;
पूर्ण

/* Codec operation modes */
अटल स्थिर अक्षर *twl4030_op_modes_texts[] = अणु
	"Option 2 (voice/audio)", "Option 1 (audio)"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(twl4030_op_modes_क्रमागत,
			    TWL4030_REG_CODEC_MODE, 0,
			    twl4030_op_modes_texts);

अटल पूर्णांक snd_soc_put_twl4030_opmode_क्रमागत_द्विगुन(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा twl4030_priv *twl4030 = snd_soc_component_get_drvdata(component);

	अगर (twl4030->configured) अणु
		dev_err(component->dev,
			"operation mode cannot be changed on-the-fly\n");
		वापस -EBUSY;
	पूर्ण

	वापस snd_soc_put_क्रमागत_द्विगुन(kcontrol, ucontrol);
पूर्ण

/*
 * FGAIN volume control:
 * from -62 to 0 dB in 1 dB steps (mute instead of -63 dB)
 */
अटल DECLARE_TLV_DB_SCALE(digital_fine_tlv, -6300, 100, 1);

/*
 * CGAIN volume control:
 * 0 dB to 12 dB in 6 dB steps
 * value 2 and 3 means 12 dB
 */
अटल DECLARE_TLV_DB_SCALE(digital_coarse_tlv, 0, 600, 0);

/*
 * Voice Downlink GAIN volume control:
 * from -37 to 12 dB in 1 dB steps (mute instead of -37 dB)
 */
अटल DECLARE_TLV_DB_SCALE(digital_voice_करोwnlink_tlv, -3700, 100, 1);

/*
 * Analog playback gain
 * -24 dB to 12 dB in 2 dB steps
 */
अटल DECLARE_TLV_DB_SCALE(analog_tlv, -2400, 200, 0);

/*
 * Gain controls tied to outमाला_दो
 * -6 dB to 6 dB in 6 dB steps (mute instead of -12)
 */
अटल DECLARE_TLV_DB_SCALE(output_tvl, -1200, 600, 1);

/*
 * Gain control क्रम earpiece amplअगरier
 * 0 dB to 12 dB in 6 dB steps (mute instead of -6)
 */
अटल DECLARE_TLV_DB_SCALE(output_ear_tvl, -600, 600, 1);

/*
 * Capture gain after the ADCs
 * from 0 dB to 31 dB in 1 dB steps
 */
अटल DECLARE_TLV_DB_SCALE(digital_capture_tlv, 0, 100, 0);

/*
 * Gain control क्रम input amplअगरiers
 * 0 dB to 30 dB in 6 dB steps
 */
अटल DECLARE_TLV_DB_SCALE(input_gain_tlv, 0, 600, 0);

/* AVADC घड़ी priority */
अटल स्थिर अक्षर *twl4030_avadc_clk_priority_texts[] = अणु
	"Voice high priority", "HiFi high priority"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(twl4030_avadc_clk_priority_क्रमागत,
			    TWL4030_REG_AVADC_CTL, 2,
			    twl4030_avadc_clk_priority_texts);

अटल स्थिर अक्षर *twl4030_rampdelay_texts[] = अणु
	"27/20/14 ms", "55/40/27 ms", "109/81/55 ms", "218/161/109 ms",
	"437/323/218 ms", "874/645/437 ms", "1748/1291/874 ms",
	"3495/2581/1748 ms"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(twl4030_rampdelay_क्रमागत,
			    TWL4030_REG_HS_POPN_SET, 2,
			    twl4030_rampdelay_texts);

/* Vibra H-bridge direction mode */
अटल स्थिर अक्षर *twl4030_vibradirmode_texts[] = अणु
	"Vibra H-bridge direction", "Audio data MSB",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(twl4030_vibradirmode_क्रमागत,
			    TWL4030_REG_VIBRA_CTL, 5,
			    twl4030_vibradirmode_texts);

/* Vibra H-bridge direction */
अटल स्थिर अक्षर *twl4030_vibradir_texts[] = अणु
	"Positive polarity", "Negative polarity",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(twl4030_vibradir_क्रमागत,
			    TWL4030_REG_VIBRA_CTL, 1,
			    twl4030_vibradir_texts);

/* Digimic Left and right swapping */
अटल स्थिर अक्षर *twl4030_digimicswap_texts[] = अणु
	"Not swapped", "Swapped",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(twl4030_digimicswap_क्रमागत,
			    TWL4030_REG_MISC_SET_1, 0,
			    twl4030_digimicswap_texts);

अटल स्थिर काष्ठा snd_kcontrol_new twl4030_snd_controls[] = अणु
	/* Codec operation mode control */
	SOC_ENUM_EXT("Codec Operation Mode", twl4030_op_modes_क्रमागत,
		snd_soc_get_क्रमागत_द्विगुन,
		snd_soc_put_twl4030_opmode_क्रमागत_द्विगुन),

	/* Common playback gain controls */
	SOC_DOUBLE_R_TLV("DAC1 Digital Fine Playback Volume",
		TWL4030_REG_ARXL1PGA, TWL4030_REG_ARXR1PGA,
		0, 0x3f, 0, digital_fine_tlv),
	SOC_DOUBLE_R_TLV("DAC2 Digital Fine Playback Volume",
		TWL4030_REG_ARXL2PGA, TWL4030_REG_ARXR2PGA,
		0, 0x3f, 0, digital_fine_tlv),

	SOC_DOUBLE_R_TLV("DAC1 Digital Coarse Playback Volume",
		TWL4030_REG_ARXL1PGA, TWL4030_REG_ARXR1PGA,
		6, 0x2, 0, digital_coarse_tlv),
	SOC_DOUBLE_R_TLV("DAC2 Digital Coarse Playback Volume",
		TWL4030_REG_ARXL2PGA, TWL4030_REG_ARXR2PGA,
		6, 0x2, 0, digital_coarse_tlv),

	SOC_DOUBLE_R_TLV("DAC1 Analog Playback Volume",
		TWL4030_REG_ARXL1_APGA_CTL, TWL4030_REG_ARXR1_APGA_CTL,
		3, 0x12, 1, analog_tlv),
	SOC_DOUBLE_R_TLV("DAC2 Analog Playback Volume",
		TWL4030_REG_ARXL2_APGA_CTL, TWL4030_REG_ARXR2_APGA_CTL,
		3, 0x12, 1, analog_tlv),
	SOC_DOUBLE_R("DAC1 Analog Playback Switch",
		TWL4030_REG_ARXL1_APGA_CTL, TWL4030_REG_ARXR1_APGA_CTL,
		1, 1, 0),
	SOC_DOUBLE_R("DAC2 Analog Playback Switch",
		TWL4030_REG_ARXL2_APGA_CTL, TWL4030_REG_ARXR2_APGA_CTL,
		1, 1, 0),

	/* Common voice करोwnlink gain controls */
	SOC_SINGLE_TLV("DAC Voice Digital Downlink Volume",
		TWL4030_REG_VRXPGA, 0, 0x31, 0, digital_voice_करोwnlink_tlv),

	SOC_SINGLE_TLV("DAC Voice Analog Downlink Volume",
		TWL4030_REG_VDL_APGA_CTL, 3, 0x12, 1, analog_tlv),

	SOC_SINGLE("DAC Voice Analog Downlink Switch",
		TWL4030_REG_VDL_APGA_CTL, 1, 1, 0),

	/* Separate output gain controls */
	SOC_DOUBLE_R_EXT_TLV("PreDriv Playback Volume",
		TWL4030_REG_PREDL_CTL, TWL4030_REG_PREDR_CTL,
		4, 3, 0, snd_soc_get_volsw_r2_twl4030,
		snd_soc_put_volsw_r2_twl4030, output_tvl),

	SOC_DOUBLE_EXT_TLV("Headset Playback Volume",
		TWL4030_REG_HS_GAIN_SET, 0, 2, 3, 0, snd_soc_get_volsw_twl4030,
		snd_soc_put_volsw_twl4030, output_tvl),

	SOC_DOUBLE_R_EXT_TLV("Carkit Playback Volume",
		TWL4030_REG_PRECKL_CTL, TWL4030_REG_PRECKR_CTL,
		4, 3, 0, snd_soc_get_volsw_r2_twl4030,
		snd_soc_put_volsw_r2_twl4030, output_tvl),

	SOC_SINGLE_EXT_TLV("Earpiece Playback Volume",
		TWL4030_REG_EAR_CTL, 4, 3, 0, snd_soc_get_volsw_twl4030,
		snd_soc_put_volsw_twl4030, output_ear_tvl),

	/* Common capture gain controls */
	SOC_DOUBLE_R_TLV("TX1 Digital Capture Volume",
		TWL4030_REG_ATXL1PGA, TWL4030_REG_ATXR1PGA,
		0, 0x1f, 0, digital_capture_tlv),
	SOC_DOUBLE_R_TLV("TX2 Digital Capture Volume",
		TWL4030_REG_AVTXL2PGA, TWL4030_REG_AVTXR2PGA,
		0, 0x1f, 0, digital_capture_tlv),

	SOC_DOUBLE_TLV("Analog Capture Volume", TWL4030_REG_ANAMIC_GAIN,
		0, 3, 5, 0, input_gain_tlv),

	SOC_ENUM("AVADC Clock Priority", twl4030_avadc_clk_priority_क्रमागत),

	SOC_ENUM("HS ramp delay", twl4030_rampdelay_क्रमागत),

	SOC_ENUM("Vibra H-bridge mode", twl4030_vibradirmode_क्रमागत),
	SOC_ENUM("Vibra H-bridge direction", twl4030_vibradir_क्रमागत),

	SOC_ENUM("Digimic LR Swap", twl4030_digimicswap_क्रमागत),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget twl4030_dapm_widमाला_लो[] = अणु
	/* Left channel inमाला_दो */
	SND_SOC_DAPM_INPUT("MAINMIC"),
	SND_SOC_DAPM_INPUT("HSMIC"),
	SND_SOC_DAPM_INPUT("AUXL"),
	SND_SOC_DAPM_INPUT("CARKITMIC"),
	/* Right channel inमाला_दो */
	SND_SOC_DAPM_INPUT("SUBMIC"),
	SND_SOC_DAPM_INPUT("AUXR"),
	/* Digital microphones (Stereo) */
	SND_SOC_DAPM_INPUT("DIGIMIC0"),
	SND_SOC_DAPM_INPUT("DIGIMIC1"),

	/* Outमाला_दो */
	SND_SOC_DAPM_OUTPUT("EARPIECE"),
	SND_SOC_DAPM_OUTPUT("PREDRIVEL"),
	SND_SOC_DAPM_OUTPUT("PREDRIVER"),
	SND_SOC_DAPM_OUTPUT("HSOL"),
	SND_SOC_DAPM_OUTPUT("HSOR"),
	SND_SOC_DAPM_OUTPUT("CARKITL"),
	SND_SOC_DAPM_OUTPUT("CARKITR"),
	SND_SOC_DAPM_OUTPUT("HFL"),
	SND_SOC_DAPM_OUTPUT("HFR"),
	SND_SOC_DAPM_OUTPUT("VIBRA"),

	/* AIF and APLL घड़ीs क्रम running DAIs (including loopback) */
	SND_SOC_DAPM_OUTPUT("Virtual HiFi OUT"),
	SND_SOC_DAPM_INPUT("Virtual HiFi IN"),
	SND_SOC_DAPM_OUTPUT("Virtual Voice OUT"),

	/* DACs */
	SND_SOC_DAPM_DAC("DAC Right1", शून्य, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC("DAC Left1", शून्य, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC("DAC Right2", शून्य, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC("DAC Left2", शून्य, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC("DAC Voice", शून्य, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_AIF_IN("VAIFIN", "Voice Playback", 0,
			    TWL4030_REG_VOICE_IF, 6, 0),

	/* Analog bypasses */
	SND_SOC_DAPM_SWITCH("Right1 Analog Loopback", SND_SOC_NOPM, 0, 0,
			&twl4030_dapm_abypassr1_control),
	SND_SOC_DAPM_SWITCH("Left1 Analog Loopback", SND_SOC_NOPM, 0, 0,
			&twl4030_dapm_abypassl1_control),
	SND_SOC_DAPM_SWITCH("Right2 Analog Loopback", SND_SOC_NOPM, 0, 0,
			&twl4030_dapm_abypassr2_control),
	SND_SOC_DAPM_SWITCH("Left2 Analog Loopback", SND_SOC_NOPM, 0, 0,
			&twl4030_dapm_abypassl2_control),
	SND_SOC_DAPM_SWITCH("Voice Analog Loopback", SND_SOC_NOPM, 0, 0,
			&twl4030_dapm_abypassv_control),

	/* Master analog loopback चयन */
	SND_SOC_DAPM_SUPPLY("FM Loop Enable", TWL4030_REG_MISC_SET_1, 5, 0,
			    शून्य, 0),

	/* Digital bypasses */
	SND_SOC_DAPM_SWITCH("Left Digital Loopback", SND_SOC_NOPM, 0, 0,
			&twl4030_dapm_dbypassl_control),
	SND_SOC_DAPM_SWITCH("Right Digital Loopback", SND_SOC_NOPM, 0, 0,
			&twl4030_dapm_dbypassr_control),
	SND_SOC_DAPM_SWITCH("Voice Digital Loopback", SND_SOC_NOPM, 0, 0,
			&twl4030_dapm_dbypassv_control),

	/* Digital mixers, घातer control क्रम the physical DACs */
	SND_SOC_DAPM_MIXER("Digital R1 Playback Mixer",
			TWL4030_REG_AVDAC_CTL, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("Digital L1 Playback Mixer",
			TWL4030_REG_AVDAC_CTL, 1, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("Digital R2 Playback Mixer",
			TWL4030_REG_AVDAC_CTL, 2, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("Digital L2 Playback Mixer",
			TWL4030_REG_AVDAC_CTL, 3, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("Digital Voice Playback Mixer",
			TWL4030_REG_AVDAC_CTL, 4, 0, शून्य, 0),

	/* Analog mixers, घातer control क्रम the physical PGAs */
	SND_SOC_DAPM_MIXER("Analog R1 Playback Mixer",
			TWL4030_REG_ARXR1_APGA_CTL, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("Analog L1 Playback Mixer",
			TWL4030_REG_ARXL1_APGA_CTL, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("Analog R2 Playback Mixer",
			TWL4030_REG_ARXR2_APGA_CTL, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("Analog L2 Playback Mixer",
			TWL4030_REG_ARXL2_APGA_CTL, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("Analog Voice Playback Mixer",
			TWL4030_REG_VDL_APGA_CTL, 0, 0, शून्य, 0),

	SND_SOC_DAPM_SUPPLY("APLL Enable", SND_SOC_NOPM, 0, 0, apll_event,
			    SND_SOC_DAPM_PRE_PMU|SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_SUPPLY("AIF Enable", SND_SOC_NOPM, 0, 0, aअगर_event,
			    SND_SOC_DAPM_PRE_PMU|SND_SOC_DAPM_POST_PMD),

	/* Output MIXER controls */
	/* Earpiece */
	SND_SOC_DAPM_MIXER("Earpiece Mixer", SND_SOC_NOPM, 0, 0,
			&twl4030_dapm_earpiece_controls[0],
			ARRAY_SIZE(twl4030_dapm_earpiece_controls)),
	SND_SOC_DAPM_PGA_E("Earpiece PGA", SND_SOC_NOPM,
			0, 0, शून्य, 0, earpiecepga_event,
			SND_SOC_DAPM_POST_PMU|SND_SOC_DAPM_POST_PMD),
	/* PreDrivL/R */
	SND_SOC_DAPM_MIXER("PredriveL Mixer", SND_SOC_NOPM, 0, 0,
			&twl4030_dapm_predrivel_controls[0],
			ARRAY_SIZE(twl4030_dapm_predrivel_controls)),
	SND_SOC_DAPM_PGA_E("PredriveL PGA", SND_SOC_NOPM,
			0, 0, शून्य, 0, predrivelpga_event,
			SND_SOC_DAPM_POST_PMU|SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_MIXER("PredriveR Mixer", SND_SOC_NOPM, 0, 0,
			&twl4030_dapm_predriver_controls[0],
			ARRAY_SIZE(twl4030_dapm_predriver_controls)),
	SND_SOC_DAPM_PGA_E("PredriveR PGA", SND_SOC_NOPM,
			0, 0, शून्य, 0, predriverpga_event,
			SND_SOC_DAPM_POST_PMU|SND_SOC_DAPM_POST_PMD),
	/* HeadsetL/R */
	SND_SOC_DAPM_MIXER("HeadsetL Mixer", SND_SOC_NOPM, 0, 0,
			&twl4030_dapm_hsol_controls[0],
			ARRAY_SIZE(twl4030_dapm_hsol_controls)),
	SND_SOC_DAPM_PGA_E("HeadsetL PGA", SND_SOC_NOPM,
			0, 0, शून्य, 0, headsetlpga_event,
			SND_SOC_DAPM_POST_PMU|SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_MIXER("HeadsetR Mixer", SND_SOC_NOPM, 0, 0,
			&twl4030_dapm_hsor_controls[0],
			ARRAY_SIZE(twl4030_dapm_hsor_controls)),
	SND_SOC_DAPM_PGA_E("HeadsetR PGA", SND_SOC_NOPM,
			0, 0, शून्य, 0, headsetrpga_event,
			SND_SOC_DAPM_POST_PMU|SND_SOC_DAPM_POST_PMD),
	/* CarkitL/R */
	SND_SOC_DAPM_MIXER("CarkitL Mixer", SND_SOC_NOPM, 0, 0,
			&twl4030_dapm_carkitl_controls[0],
			ARRAY_SIZE(twl4030_dapm_carkitl_controls)),
	SND_SOC_DAPM_PGA_E("CarkitL PGA", SND_SOC_NOPM,
			0, 0, शून्य, 0, carkitlpga_event,
			SND_SOC_DAPM_POST_PMU|SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_MIXER("CarkitR Mixer", SND_SOC_NOPM, 0, 0,
			&twl4030_dapm_carkitr_controls[0],
			ARRAY_SIZE(twl4030_dapm_carkitr_controls)),
	SND_SOC_DAPM_PGA_E("CarkitR PGA", SND_SOC_NOPM,
			0, 0, शून्य, 0, carkitrpga_event,
			SND_SOC_DAPM_POST_PMU|SND_SOC_DAPM_POST_PMD),

	/* Output MUX controls */
	/* Handsमुक्तL/R */
	SND_SOC_DAPM_MUX("HandsfreeL Mux", SND_SOC_NOPM, 0, 0,
		&twl4030_dapm_handsमुक्तl_control),
	SND_SOC_DAPM_SWITCH("HandsfreeL", SND_SOC_NOPM, 0, 0,
			&twl4030_dapm_handsमुक्तlmute_control),
	SND_SOC_DAPM_PGA_E("HandsfreeL PGA", SND_SOC_NOPM,
			0, 0, शून्य, 0, handsमुक्तlpga_event,
			SND_SOC_DAPM_POST_PMU|SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_MUX("HandsfreeR Mux", SND_SOC_NOPM, 5, 0,
		&twl4030_dapm_handsमुक्तr_control),
	SND_SOC_DAPM_SWITCH("HandsfreeR", SND_SOC_NOPM, 0, 0,
			&twl4030_dapm_handsमुक्तrmute_control),
	SND_SOC_DAPM_PGA_E("HandsfreeR PGA", SND_SOC_NOPM,
			0, 0, शून्य, 0, handsमुक्तrpga_event,
			SND_SOC_DAPM_POST_PMU|SND_SOC_DAPM_POST_PMD),
	/* Vibra */
	SND_SOC_DAPM_MUX_E("Vibra Mux", TWL4030_REG_VIBRA_CTL, 0, 0,
			   &twl4030_dapm_vibra_control, vibramux_event,
			   SND_SOC_DAPM_PRE_PMU),
	SND_SOC_DAPM_MUX("Vibra Route", SND_SOC_NOPM, 0, 0,
		&twl4030_dapm_vibrapath_control),

	/* Introducing four भव ADC, since TWL4030 have four channel क्रम
	   capture */
	SND_SOC_DAPM_ADC("ADC Virtual Left1", शून्य, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_ADC("ADC Virtual Right1", शून्य, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_ADC("ADC Virtual Left2", शून्य, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_ADC("ADC Virtual Right2", शून्य, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_AIF_OUT("VAIFOUT", "Voice Capture", 0,
			     TWL4030_REG_VOICE_IF, 5, 0),

	/* Analog/Digital mic path selection.
	   TX1 Left/Right: either analog Left/Right or Digimic0
	   TX2 Left/Right: either analog Left/Right or Digimic1 */
	SND_SOC_DAPM_MUX("TX1 Capture Route", SND_SOC_NOPM, 0, 0,
		&twl4030_dapm_micpathtx1_control),
	SND_SOC_DAPM_MUX("TX2 Capture Route", SND_SOC_NOPM, 0, 0,
		&twl4030_dapm_micpathtx2_control),

	/* Analog input mixers क्रम the capture amplअगरiers */
	SND_SOC_DAPM_MIXER("Analog Left",
		TWL4030_REG_ANAMICL, 4, 0,
		&twl4030_dapm_analoglmic_controls[0],
		ARRAY_SIZE(twl4030_dapm_analoglmic_controls)),
	SND_SOC_DAPM_MIXER("Analog Right",
		TWL4030_REG_ANAMICR, 4, 0,
		&twl4030_dapm_analogrmic_controls[0],
		ARRAY_SIZE(twl4030_dapm_analogrmic_controls)),

	SND_SOC_DAPM_PGA("ADC Physical Left",
		TWL4030_REG_AVADC_CTL, 3, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("ADC Physical Right",
		TWL4030_REG_AVADC_CTL, 1, 0, शून्य, 0),

	SND_SOC_DAPM_PGA_E("Digimic0 Enable",
		TWL4030_REG_ADCMICSEL, 1, 0, शून्य, 0,
		digimic_event, SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_PGA_E("Digimic1 Enable",
		TWL4030_REG_ADCMICSEL, 3, 0, शून्य, 0,
		digimic_event, SND_SOC_DAPM_POST_PMU),

	SND_SOC_DAPM_SUPPLY("micbias1 select", TWL4030_REG_MICBIAS_CTL, 5, 0,
			    शून्य, 0),
	SND_SOC_DAPM_SUPPLY("micbias2 select", TWL4030_REG_MICBIAS_CTL, 6, 0,
			    शून्य, 0),

	/* Microphone bias */
	SND_SOC_DAPM_SUPPLY("Mic Bias 1",
			    TWL4030_REG_MICBIAS_CTL, 0, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("Mic Bias 2",
			    TWL4030_REG_MICBIAS_CTL, 1, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("Headset Mic Bias",
			    TWL4030_REG_MICBIAS_CTL, 2, 0, शून्य, 0),

	SND_SOC_DAPM_SUPPLY("VIF Enable", TWL4030_REG_VOICE_IF, 0, 0, शून्य, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route पूर्णांकercon[] = अणु
	/* Stream -> DAC mapping */
	अणु"DAC Right1", शून्य, "HiFi Playback"पूर्ण,
	अणु"DAC Left1", शून्य, "HiFi Playback"पूर्ण,
	अणु"DAC Right2", शून्य, "HiFi Playback"पूर्ण,
	अणु"DAC Left2", शून्य, "HiFi Playback"पूर्ण,
	अणु"DAC Voice", शून्य, "VAIFIN"पूर्ण,

	/* ADC -> Stream mapping */
	अणु"HiFi Capture", शून्य, "ADC Virtual Left1"पूर्ण,
	अणु"HiFi Capture", शून्य, "ADC Virtual Right1"पूर्ण,
	अणु"HiFi Capture", शून्य, "ADC Virtual Left2"पूर्ण,
	अणु"HiFi Capture", शून्य, "ADC Virtual Right2"पूर्ण,
	अणु"VAIFOUT", शून्य, "ADC Virtual Left2"पूर्ण,
	अणु"VAIFOUT", शून्य, "ADC Virtual Right2"पूर्ण,
	अणु"VAIFOUT", शून्य, "VIF Enable"पूर्ण,

	अणु"Digital L1 Playback Mixer", शून्य, "DAC Left1"पूर्ण,
	अणु"Digital R1 Playback Mixer", शून्य, "DAC Right1"पूर्ण,
	अणु"Digital L2 Playback Mixer", शून्य, "DAC Left2"पूर्ण,
	अणु"Digital R2 Playback Mixer", शून्य, "DAC Right2"पूर्ण,
	अणु"Digital Voice Playback Mixer", शून्य, "DAC Voice"पूर्ण,

	/* Supply क्रम the digital part (APLL) */
	अणु"Digital Voice Playback Mixer", शून्य, "APLL Enable"पूर्ण,

	अणु"DAC Left1", शून्य, "AIF Enable"पूर्ण,
	अणु"DAC Right1", शून्य, "AIF Enable"पूर्ण,
	अणु"DAC Left2", शून्य, "AIF Enable"पूर्ण,
	अणु"DAC Right1", शून्य, "AIF Enable"पूर्ण,
	अणु"DAC Voice", शून्य, "VIF Enable"पूर्ण,

	अणु"Digital R2 Playback Mixer", शून्य, "AIF Enable"पूर्ण,
	अणु"Digital L2 Playback Mixer", शून्य, "AIF Enable"पूर्ण,

	अणु"Analog L1 Playback Mixer", शून्य, "Digital L1 Playback Mixer"पूर्ण,
	अणु"Analog R1 Playback Mixer", शून्य, "Digital R1 Playback Mixer"पूर्ण,
	अणु"Analog L2 Playback Mixer", शून्य, "Digital L2 Playback Mixer"पूर्ण,
	अणु"Analog R2 Playback Mixer", शून्य, "Digital R2 Playback Mixer"पूर्ण,
	अणु"Analog Voice Playback Mixer", शून्य, "Digital Voice Playback Mixer"पूर्ण,

	/* Internal playback routings */
	/* Earpiece */
	अणु"Earpiece Mixer", "Voice", "Analog Voice Playback Mixer"पूर्ण,
	अणु"Earpiece Mixer", "AudioL1", "Analog L1 Playback Mixer"पूर्ण,
	अणु"Earpiece Mixer", "AudioL2", "Analog L2 Playback Mixer"पूर्ण,
	अणु"Earpiece Mixer", "AudioR1", "Analog R1 Playback Mixer"पूर्ण,
	अणु"Earpiece PGA", शून्य, "Earpiece Mixer"पूर्ण,
	/* PreDrivL */
	अणु"PredriveL Mixer", "Voice", "Analog Voice Playback Mixer"पूर्ण,
	अणु"PredriveL Mixer", "AudioL1", "Analog L1 Playback Mixer"पूर्ण,
	अणु"PredriveL Mixer", "AudioL2", "Analog L2 Playback Mixer"पूर्ण,
	अणु"PredriveL Mixer", "AudioR2", "Analog R2 Playback Mixer"पूर्ण,
	अणु"PredriveL PGA", शून्य, "PredriveL Mixer"पूर्ण,
	/* PreDrivR */
	अणु"PredriveR Mixer", "Voice", "Analog Voice Playback Mixer"पूर्ण,
	अणु"PredriveR Mixer", "AudioR1", "Analog R1 Playback Mixer"पूर्ण,
	अणु"PredriveR Mixer", "AudioR2", "Analog R2 Playback Mixer"पूर्ण,
	अणु"PredriveR Mixer", "AudioL2", "Analog L2 Playback Mixer"पूर्ण,
	अणु"PredriveR PGA", शून्य, "PredriveR Mixer"पूर्ण,
	/* HeadsetL */
	अणु"HeadsetL Mixer", "Voice", "Analog Voice Playback Mixer"पूर्ण,
	अणु"HeadsetL Mixer", "AudioL1", "Analog L1 Playback Mixer"पूर्ण,
	अणु"HeadsetL Mixer", "AudioL2", "Analog L2 Playback Mixer"पूर्ण,
	अणु"HeadsetL PGA", शून्य, "HeadsetL Mixer"पूर्ण,
	/* HeadsetR */
	अणु"HeadsetR Mixer", "Voice", "Analog Voice Playback Mixer"पूर्ण,
	अणु"HeadsetR Mixer", "AudioR1", "Analog R1 Playback Mixer"पूर्ण,
	अणु"HeadsetR Mixer", "AudioR2", "Analog R2 Playback Mixer"पूर्ण,
	अणु"HeadsetR PGA", शून्य, "HeadsetR Mixer"पूर्ण,
	/* CarkitL */
	अणु"CarkitL Mixer", "Voice", "Analog Voice Playback Mixer"पूर्ण,
	अणु"CarkitL Mixer", "AudioL1", "Analog L1 Playback Mixer"पूर्ण,
	अणु"CarkitL Mixer", "AudioL2", "Analog L2 Playback Mixer"पूर्ण,
	अणु"CarkitL PGA", शून्य, "CarkitL Mixer"पूर्ण,
	/* CarkitR */
	अणु"CarkitR Mixer", "Voice", "Analog Voice Playback Mixer"पूर्ण,
	अणु"CarkitR Mixer", "AudioR1", "Analog R1 Playback Mixer"पूर्ण,
	अणु"CarkitR Mixer", "AudioR2", "Analog R2 Playback Mixer"पूर्ण,
	अणु"CarkitR PGA", शून्य, "CarkitR Mixer"पूर्ण,
	/* Handsमुक्तL */
	अणु"HandsfreeL Mux", "Voice", "Analog Voice Playback Mixer"पूर्ण,
	अणु"HandsfreeL Mux", "AudioL1", "Analog L1 Playback Mixer"पूर्ण,
	अणु"HandsfreeL Mux", "AudioL2", "Analog L2 Playback Mixer"पूर्ण,
	अणु"HandsfreeL Mux", "AudioR2", "Analog R2 Playback Mixer"पूर्ण,
	अणु"HandsfreeL", "Switch", "HandsfreeL Mux"पूर्ण,
	अणु"HandsfreeL PGA", शून्य, "HandsfreeL"पूर्ण,
	/* Handsमुक्तR */
	अणु"HandsfreeR Mux", "Voice", "Analog Voice Playback Mixer"पूर्ण,
	अणु"HandsfreeR Mux", "AudioR1", "Analog R1 Playback Mixer"पूर्ण,
	अणु"HandsfreeR Mux", "AudioR2", "Analog R2 Playback Mixer"पूर्ण,
	अणु"HandsfreeR Mux", "AudioL2", "Analog L2 Playback Mixer"पूर्ण,
	अणु"HandsfreeR", "Switch", "HandsfreeR Mux"पूर्ण,
	अणु"HandsfreeR PGA", शून्य, "HandsfreeR"पूर्ण,
	/* Vibra */
	अणु"Vibra Mux", "AudioL1", "DAC Left1"पूर्ण,
	अणु"Vibra Mux", "AudioR1", "DAC Right1"पूर्ण,
	अणु"Vibra Mux", "AudioL2", "DAC Left2"पूर्ण,
	अणु"Vibra Mux", "AudioR2", "DAC Right2"पूर्ण,

	/* outमाला_दो */
	/* Must be always connected (क्रम AIF and APLL) */
	अणु"Virtual HiFi OUT", शून्य, "DAC Left1"पूर्ण,
	अणु"Virtual HiFi OUT", शून्य, "DAC Right1"पूर्ण,
	अणु"Virtual HiFi OUT", शून्य, "DAC Left2"पूर्ण,
	अणु"Virtual HiFi OUT", शून्य, "DAC Right2"पूर्ण,
	/* Must be always connected (क्रम APLL) */
	अणु"Virtual Voice OUT", शून्य, "Digital Voice Playback Mixer"पूर्ण,
	/* Physical outमाला_दो */
	अणु"EARPIECE", शून्य, "Earpiece PGA"पूर्ण,
	अणु"PREDRIVEL", शून्य, "PredriveL PGA"पूर्ण,
	अणु"PREDRIVER", शून्य, "PredriveR PGA"पूर्ण,
	अणु"HSOL", शून्य, "HeadsetL PGA"पूर्ण,
	अणु"HSOR", शून्य, "HeadsetR PGA"पूर्ण,
	अणु"CARKITL", शून्य, "CarkitL PGA"पूर्ण,
	अणु"CARKITR", शून्य, "CarkitR PGA"पूर्ण,
	अणु"HFL", शून्य, "HandsfreeL PGA"पूर्ण,
	अणु"HFR", शून्य, "HandsfreeR PGA"पूर्ण,
	अणु"Vibra Route", "Audio", "Vibra Mux"पूर्ण,
	अणु"VIBRA", शून्य, "Vibra Route"पूर्ण,

	/* Capture path */
	/* Must be always connected (क्रम AIF and APLL) */
	अणु"ADC Virtual Left1", शून्य, "Virtual HiFi IN"पूर्ण,
	अणु"ADC Virtual Right1", शून्य, "Virtual HiFi IN"पूर्ण,
	अणु"ADC Virtual Left2", शून्य, "Virtual HiFi IN"पूर्ण,
	अणु"ADC Virtual Right2", शून्य, "Virtual HiFi IN"पूर्ण,
	/* Physical inमाला_दो */
	अणु"Analog Left", "Main Mic Capture Switch", "MAINMIC"पूर्ण,
	अणु"Analog Left", "Headset Mic Capture Switch", "HSMIC"पूर्ण,
	अणु"Analog Left", "AUXL Capture Switch", "AUXL"पूर्ण,
	अणु"Analog Left", "Carkit Mic Capture Switch", "CARKITMIC"पूर्ण,

	अणु"Analog Right", "Sub Mic Capture Switch", "SUBMIC"पूर्ण,
	अणु"Analog Right", "AUXR Capture Switch", "AUXR"पूर्ण,

	अणु"ADC Physical Left", शून्य, "Analog Left"पूर्ण,
	अणु"ADC Physical Right", शून्य, "Analog Right"पूर्ण,

	अणु"Digimic0 Enable", शून्य, "DIGIMIC0"पूर्ण,
	अणु"Digimic1 Enable", शून्य, "DIGIMIC1"पूर्ण,

	अणु"DIGIMIC0", शून्य, "micbias1 select"पूर्ण,
	अणु"DIGIMIC1", शून्य, "micbias2 select"पूर्ण,

	/* TX1 Left capture path */
	अणु"TX1 Capture Route", "Analog", "ADC Physical Left"पूर्ण,
	अणु"TX1 Capture Route", "Digimic0", "Digimic0 Enable"पूर्ण,
	/* TX1 Right capture path */
	अणु"TX1 Capture Route", "Analog", "ADC Physical Right"पूर्ण,
	अणु"TX1 Capture Route", "Digimic0", "Digimic0 Enable"पूर्ण,
	/* TX2 Left capture path */
	अणु"TX2 Capture Route", "Analog", "ADC Physical Left"पूर्ण,
	अणु"TX2 Capture Route", "Digimic1", "Digimic1 Enable"पूर्ण,
	/* TX2 Right capture path */
	अणु"TX2 Capture Route", "Analog", "ADC Physical Right"पूर्ण,
	अणु"TX2 Capture Route", "Digimic1", "Digimic1 Enable"पूर्ण,

	अणु"ADC Virtual Left1", शून्य, "TX1 Capture Route"पूर्ण,
	अणु"ADC Virtual Right1", शून्य, "TX1 Capture Route"पूर्ण,
	अणु"ADC Virtual Left2", शून्य, "TX2 Capture Route"पूर्ण,
	अणु"ADC Virtual Right2", शून्य, "TX2 Capture Route"पूर्ण,

	अणु"ADC Virtual Left1", शून्य, "AIF Enable"पूर्ण,
	अणु"ADC Virtual Right1", शून्य, "AIF Enable"पूर्ण,
	अणु"ADC Virtual Left2", शून्य, "AIF Enable"पूर्ण,
	अणु"ADC Virtual Right2", शून्य, "AIF Enable"पूर्ण,

	/* Analog bypass routes */
	अणु"Right1 Analog Loopback", "Switch", "Analog Right"पूर्ण,
	अणु"Left1 Analog Loopback", "Switch", "Analog Left"पूर्ण,
	अणु"Right2 Analog Loopback", "Switch", "Analog Right"पूर्ण,
	अणु"Left2 Analog Loopback", "Switch", "Analog Left"पूर्ण,
	अणु"Voice Analog Loopback", "Switch", "Analog Left"पूर्ण,

	/* Supply क्रम the Analog loopbacks */
	अणु"Right1 Analog Loopback", शून्य, "FM Loop Enable"पूर्ण,
	अणु"Left1 Analog Loopback", शून्य, "FM Loop Enable"पूर्ण,
	अणु"Right2 Analog Loopback", शून्य, "FM Loop Enable"पूर्ण,
	अणु"Left2 Analog Loopback", शून्य, "FM Loop Enable"पूर्ण,
	अणु"Voice Analog Loopback", शून्य, "FM Loop Enable"पूर्ण,

	अणु"Analog R1 Playback Mixer", शून्य, "Right1 Analog Loopback"पूर्ण,
	अणु"Analog L1 Playback Mixer", शून्य, "Left1 Analog Loopback"पूर्ण,
	अणु"Analog R2 Playback Mixer", शून्य, "Right2 Analog Loopback"पूर्ण,
	अणु"Analog L2 Playback Mixer", शून्य, "Left2 Analog Loopback"पूर्ण,
	अणु"Analog Voice Playback Mixer", शून्य, "Voice Analog Loopback"पूर्ण,

	/* Digital bypass routes */
	अणु"Right Digital Loopback", "Volume", "TX1 Capture Route"पूर्ण,
	अणु"Left Digital Loopback", "Volume", "TX1 Capture Route"पूर्ण,
	अणु"Voice Digital Loopback", "Volume", "TX2 Capture Route"पूर्ण,

	अणु"Digital R2 Playback Mixer", शून्य, "Right Digital Loopback"पूर्ण,
	अणु"Digital L2 Playback Mixer", शून्य, "Left Digital Loopback"पूर्ण,
	अणु"Digital Voice Playback Mixer", शून्य, "Voice Digital Loopback"पूर्ण,

पूर्ण;

अटल पूर्णांक twl4030_set_bias_level(काष्ठा snd_soc_component *component,
				  क्रमागत snd_soc_bias_level level)
अणु
	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		अवरोध;
	हाल SND_SOC_BIAS_PREPARE:
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF)
			twl4030_codec_enable(component, 1);
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		twl4030_codec_enable(component, 0);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम twl4030_स्थिरraपूर्णांकs(काष्ठा twl4030_priv *twl4030,
				काष्ठा snd_pcm_substream *mst_substream)
अणु
	काष्ठा snd_pcm_substream *slv_substream;

	/* Pick the stream, which need to be स्थिरrained */
	अगर (mst_substream == twl4030->master_substream)
		slv_substream = twl4030->slave_substream;
	अन्यथा अगर (mst_substream == twl4030->slave_substream)
		slv_substream = twl4030->master_substream;
	अन्यथा /* This should not happen.. */
		वापस;

	/* Set the स्थिरraपूर्णांकs according to the alपढ़ोy configured stream */
	snd_pcm_hw_स्थिरraपूर्णांक_single(slv_substream->runसमय,
				SNDRV_PCM_HW_PARAM_RATE,
				twl4030->rate);

	snd_pcm_hw_स्थिरraपूर्णांक_single(slv_substream->runसमय,
				SNDRV_PCM_HW_PARAM_SAMPLE_BITS,
				twl4030->sample_bits);

	snd_pcm_hw_स्थिरraपूर्णांक_single(slv_substream->runसमय,
				SNDRV_PCM_HW_PARAM_CHANNELS,
				twl4030->channels);
पूर्ण

/* In हाल of 4 channel mode, the RX1 L/R क्रम playback and the TX2 L/R क्रम
 * capture has to be enabled/disabled. */
अटल व्योम twl4030_tdm_enable(काष्ठा snd_soc_component *component, पूर्णांक direction,
			       पूर्णांक enable)
अणु
	u8 reg, mask;

	reg = twl4030_पढ़ो(component, TWL4030_REG_OPTION);

	अगर (direction == SNDRV_PCM_STREAM_PLAYBACK)
		mask = TWL4030_ARXL1_VRX_EN | TWL4030_ARXR1_EN;
	अन्यथा
		mask = TWL4030_ATXL2_VTXL_EN | TWL4030_ATXR2_VTXR_EN;

	अगर (enable)
		reg |= mask;
	अन्यथा
		reg &= ~mask;

	twl4030_ग_लिखो(component, TWL4030_REG_OPTION, reg);
पूर्ण

अटल पूर्णांक twl4030_startup(काष्ठा snd_pcm_substream *substream,
			   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा twl4030_priv *twl4030 = snd_soc_component_get_drvdata(component);

	अगर (twl4030->master_substream) अणु
		twl4030->slave_substream = substream;
		/* The DAI has one configuration क्रम playback and capture, so
		 * अगर the DAI has been alपढ़ोy configured then स्थिरrain this
		 * substream to match it. */
		अगर (twl4030->configured)
			twl4030_स्थिरraपूर्णांकs(twl4030, twl4030->master_substream);
	पूर्ण अन्यथा अणु
		अगर (!(twl4030_पढ़ो(component, TWL4030_REG_CODEC_MODE) &
			TWL4030_OPTION_1)) अणु
			/* In option2 4 channel is not supported, set the
			 * स्थिरraपूर्णांक क्रम the first stream क्रम channels, the
			 * second stream will 'inherit' this cosntraपूर्णांक */
			snd_pcm_hw_स्थिरraपूर्णांक_single(substream->runसमय,
						     SNDRV_PCM_HW_PARAM_CHANNELS,
						     2);
		पूर्ण
		twl4030->master_substream = substream;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम twl4030_shutकरोwn(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा twl4030_priv *twl4030 = snd_soc_component_get_drvdata(component);

	अगर (twl4030->master_substream == substream)
		twl4030->master_substream = twl4030->slave_substream;

	twl4030->slave_substream = शून्य;

	/* If all streams are बंदd, or the reमुख्यing stream has not yet
	 * been configured than set the DAI as not configured. */
	अगर (!twl4030->master_substream)
		twl4030->configured = 0;
	 अन्यथा अगर (!twl4030->master_substream->runसमय->channels)
		twl4030->configured = 0;

	 /* If the closing substream had 4 channel, करो the necessary cleanup */
	अगर (substream->runसमय->channels == 4)
		twl4030_tdm_enable(component, substream->stream, 0);
पूर्ण

अटल पूर्णांक twl4030_hw_params(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *params,
			     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा twl4030_priv *twl4030 = snd_soc_component_get_drvdata(component);
	u8 mode, old_mode, क्रमmat, old_क्रमmat;

	 /* If the substream has 4 channel, करो the necessary setup */
	अगर (params_channels(params) == 4) अणु
		क्रमmat = twl4030_पढ़ो(component, TWL4030_REG_AUDIO_IF);
		mode = twl4030_पढ़ो(component, TWL4030_REG_CODEC_MODE);

		/* Safety check: are we in the correct operating mode and
		 * the पूर्णांकerface is in TDM mode? */
		अगर ((mode & TWL4030_OPTION_1) &&
		    ((क्रमmat & TWL4030_AIF_FORMAT) == TWL4030_AIF_FORMAT_TDM))
			twl4030_tdm_enable(component, substream->stream, 1);
		अन्यथा
			वापस -EINVAL;
	पूर्ण

	अगर (twl4030->configured)
		/* Ignoring hw_params क्रम alपढ़ोy configured DAI */
		वापस 0;

	/* bit rate */
	old_mode = twl4030_पढ़ो(component,
				TWL4030_REG_CODEC_MODE) & ~TWL4030_CODECPDZ;
	mode = old_mode & ~TWL4030_APLL_RATE;

	चयन (params_rate(params)) अणु
	हाल 8000:
		mode |= TWL4030_APLL_RATE_8000;
		अवरोध;
	हाल 11025:
		mode |= TWL4030_APLL_RATE_11025;
		अवरोध;
	हाल 12000:
		mode |= TWL4030_APLL_RATE_12000;
		अवरोध;
	हाल 16000:
		mode |= TWL4030_APLL_RATE_16000;
		अवरोध;
	हाल 22050:
		mode |= TWL4030_APLL_RATE_22050;
		अवरोध;
	हाल 24000:
		mode |= TWL4030_APLL_RATE_24000;
		अवरोध;
	हाल 32000:
		mode |= TWL4030_APLL_RATE_32000;
		अवरोध;
	हाल 44100:
		mode |= TWL4030_APLL_RATE_44100;
		अवरोध;
	हाल 48000:
		mode |= TWL4030_APLL_RATE_48000;
		अवरोध;
	हाल 96000:
		mode |= TWL4030_APLL_RATE_96000;
		अवरोध;
	शेष:
		dev_err(component->dev, "%s: unknown rate %d\n", __func__,
			params_rate(params));
		वापस -EINVAL;
	पूर्ण

	/* sample size */
	old_क्रमmat = twl4030_पढ़ो(component, TWL4030_REG_AUDIO_IF);
	क्रमmat = old_क्रमmat;
	क्रमmat &= ~TWL4030_DATA_WIDTH;
	चयन (params_width(params)) अणु
	हाल 16:
		क्रमmat |= TWL4030_DATA_WIDTH_16S_16W;
		अवरोध;
	हाल 32:
		क्रमmat |= TWL4030_DATA_WIDTH_32S_24W;
		अवरोध;
	शेष:
		dev_err(component->dev, "%s: unsupported bits/sample %d\n",
			__func__, params_width(params));
		वापस -EINVAL;
	पूर्ण

	अगर (क्रमmat != old_क्रमmat || mode != old_mode) अणु
		अगर (twl4030->codec_घातered) अणु
			/*
			 * If the codec is घातered, than we need to toggle the
			 * codec घातer.
			 */
			twl4030_codec_enable(component, 0);
			twl4030_ग_लिखो(component, TWL4030_REG_CODEC_MODE, mode);
			twl4030_ग_लिखो(component, TWL4030_REG_AUDIO_IF, क्रमmat);
			twl4030_codec_enable(component, 1);
		पूर्ण अन्यथा अणु
			twl4030_ग_लिखो(component, TWL4030_REG_CODEC_MODE, mode);
			twl4030_ग_लिखो(component, TWL4030_REG_AUDIO_IF, क्रमmat);
		पूर्ण
	पूर्ण

	/* Store the important parameters क्रम the DAI configuration and set
	 * the DAI as configured */
	twl4030->configured = 1;
	twl4030->rate = params_rate(params);
	twl4030->sample_bits = hw_param_पूर्णांकerval(params,
					SNDRV_PCM_HW_PARAM_SAMPLE_BITS)->min;
	twl4030->channels = params_channels(params);

	/* If both playback and capture streams are खोलो, and one of them
	 * is setting the hw parameters right now (since we are here), set
	 * स्थिरraपूर्णांकs to the other stream to match the current one. */
	अगर (twl4030->slave_substream)
		twl4030_स्थिरraपूर्णांकs(twl4030, substream);

	वापस 0;
पूर्ण

अटल पूर्णांक twl4030_set_dai_sysclk(काष्ठा snd_soc_dai *codec_dai, पूर्णांक clk_id,
				  अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा twl4030_priv *twl4030 = snd_soc_component_get_drvdata(component);

	चयन (freq) अणु
	हाल 19200000:
	हाल 26000000:
	हाल 38400000:
		अवरोध;
	शेष:
		dev_err(component->dev, "Unsupported HFCLKIN: %u\n", freq);
		वापस -EINVAL;
	पूर्ण

	अगर ((freq / 1000) != twl4030->sysclk) अणु
		dev_err(component->dev,
			"Mismatch in HFCLKIN: %u (configured: %u)\n",
			freq, twl4030->sysclk * 1000);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक twl4030_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा twl4030_priv *twl4030 = snd_soc_component_get_drvdata(component);
	u8 old_क्रमmat, क्रमmat;

	/* get क्रमmat */
	old_क्रमmat = twl4030_पढ़ो(component, TWL4030_REG_AUDIO_IF);
	क्रमmat = old_क्रमmat;

	/* set master/slave audio पूर्णांकerface */
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		क्रमmat &= ~(TWL4030_AIF_SLAVE_EN);
		क्रमmat &= ~(TWL4030_CLK256FS_EN);
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		क्रमmat |= TWL4030_AIF_SLAVE_EN;
		क्रमmat |= TWL4030_CLK256FS_EN;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* पूर्णांकerface क्रमmat */
	क्रमmat &= ~TWL4030_AIF_FORMAT;
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		क्रमmat |= TWL4030_AIF_FORMAT_CODEC;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		क्रमmat |= TWL4030_AIF_FORMAT_TDM;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (क्रमmat != old_क्रमmat) अणु
		अगर (twl4030->codec_घातered) अणु
			/*
			 * If the codec is घातered, than we need to toggle the
			 * codec घातer.
			 */
			twl4030_codec_enable(component, 0);
			twl4030_ग_लिखो(component, TWL4030_REG_AUDIO_IF, क्रमmat);
			twl4030_codec_enable(component, 1);
		पूर्ण अन्यथा अणु
			twl4030_ग_लिखो(component, TWL4030_REG_AUDIO_IF, क्रमmat);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक twl4030_set_tristate(काष्ठा snd_soc_dai *dai, पूर्णांक tristate)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	u8 reg = twl4030_पढ़ो(component, TWL4030_REG_AUDIO_IF);

	अगर (tristate)
		reg |= TWL4030_AIF_TRI_EN;
	अन्यथा
		reg &= ~TWL4030_AIF_TRI_EN;

	वापस twl4030_ग_लिखो(component, TWL4030_REG_AUDIO_IF, reg);
पूर्ण

/* In हाल of voice mode, the RX1 L(VRX) क्रम करोwnlink and the TX2 L/R
 * (VTXL, VTXR) क्रम uplink has to be enabled/disabled. */
अटल व्योम twl4030_voice_enable(काष्ठा snd_soc_component *component, पूर्णांक direction,
				 पूर्णांक enable)
अणु
	u8 reg, mask;

	reg = twl4030_पढ़ो(component, TWL4030_REG_OPTION);

	अगर (direction == SNDRV_PCM_STREAM_PLAYBACK)
		mask = TWL4030_ARXL1_VRX_EN;
	अन्यथा
		mask = TWL4030_ATXL2_VTXL_EN | TWL4030_ATXR2_VTXR_EN;

	अगर (enable)
		reg |= mask;
	अन्यथा
		reg &= ~mask;

	twl4030_ग_लिखो(component, TWL4030_REG_OPTION, reg);
पूर्ण

अटल पूर्णांक twl4030_voice_startup(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा twl4030_priv *twl4030 = snd_soc_component_get_drvdata(component);
	u8 mode;

	/* If the प्रणाली master घड़ी is not 26MHz, the voice PCM पूर्णांकerface is
	 * not available.
	 */
	अगर (twl4030->sysclk != 26000) अणु
		dev_err(component->dev,
			"%s: HFCLKIN is %u KHz, voice interface needs 26MHz\n",
			__func__, twl4030->sysclk);
		वापस -EINVAL;
	पूर्ण

	/* If the codec mode is not option2, the voice PCM पूर्णांकerface is not
	 * available.
	 */
	mode = twl4030_पढ़ो(component, TWL4030_REG_CODEC_MODE)
		& TWL4030_OPT_MODE;

	अगर (mode != TWL4030_OPTION_2) अणु
		dev_err(component->dev, "%s: the codec mode is not option2\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम twl4030_voice_shutकरोwn(काष्ठा snd_pcm_substream *substream,
				   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;

	/* Enable voice digital filters */
	twl4030_voice_enable(component, substream->stream, 0);
पूर्ण

अटल पूर्णांक twl4030_voice_hw_params(काष्ठा snd_pcm_substream *substream,
				   काष्ठा snd_pcm_hw_params *params,
				   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा twl4030_priv *twl4030 = snd_soc_component_get_drvdata(component);
	u8 old_mode, mode;

	/* Enable voice digital filters */
	twl4030_voice_enable(component, substream->stream, 1);

	/* bit rate */
	old_mode = twl4030_पढ़ो(component,
				TWL4030_REG_CODEC_MODE) & ~TWL4030_CODECPDZ;
	mode = old_mode;

	चयन (params_rate(params)) अणु
	हाल 8000:
		mode &= ~(TWL4030_SEL_16K);
		अवरोध;
	हाल 16000:
		mode |= TWL4030_SEL_16K;
		अवरोध;
	शेष:
		dev_err(component->dev, "%s: unknown rate %d\n", __func__,
			params_rate(params));
		वापस -EINVAL;
	पूर्ण

	अगर (mode != old_mode) अणु
		अगर (twl4030->codec_घातered) अणु
			/*
			 * If the codec is घातered, than we need to toggle the
			 * codec घातer.
			 */
			twl4030_codec_enable(component, 0);
			twl4030_ग_लिखो(component, TWL4030_REG_CODEC_MODE, mode);
			twl4030_codec_enable(component, 1);
		पूर्ण अन्यथा अणु
			twl4030_ग_लिखो(component, TWL4030_REG_CODEC_MODE, mode);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक twl4030_voice_set_dai_sysclk(काष्ठा snd_soc_dai *codec_dai,
					पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा twl4030_priv *twl4030 = snd_soc_component_get_drvdata(component);

	अगर (freq != 26000000) अणु
		dev_err(component->dev,
			"%s: HFCLKIN is %u KHz, voice interface needs 26MHz\n",
			__func__, freq / 1000);
		वापस -EINVAL;
	पूर्ण
	अगर ((freq / 1000) != twl4030->sysclk) अणु
		dev_err(component->dev,
			"Mismatch in HFCLKIN: %u (configured: %u)\n",
			freq, twl4030->sysclk * 1000);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक twl4030_voice_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai,
				     अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा twl4030_priv *twl4030 = snd_soc_component_get_drvdata(component);
	u8 old_क्रमmat, क्रमmat;

	/* get क्रमmat */
	old_क्रमmat = twl4030_पढ़ो(component, TWL4030_REG_VOICE_IF);
	क्रमmat = old_क्रमmat;

	/* set master/slave audio पूर्णांकerface */
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		क्रमmat &= ~(TWL4030_VIF_SLAVE_EN);
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		क्रमmat |= TWL4030_VIF_SLAVE_EN;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* घड़ी inversion */
	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_IB_NF:
		क्रमmat &= ~(TWL4030_VIF_FORMAT);
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		क्रमmat |= TWL4030_VIF_FORMAT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (क्रमmat != old_क्रमmat) अणु
		अगर (twl4030->codec_घातered) अणु
			/*
			 * If the codec is घातered, than we need to toggle the
			 * codec घातer.
			 */
			twl4030_codec_enable(component, 0);
			twl4030_ग_लिखो(component, TWL4030_REG_VOICE_IF, क्रमmat);
			twl4030_codec_enable(component, 1);
		पूर्ण अन्यथा अणु
			twl4030_ग_लिखो(component, TWL4030_REG_VOICE_IF, क्रमmat);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक twl4030_voice_set_tristate(काष्ठा snd_soc_dai *dai, पूर्णांक tristate)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	u8 reg = twl4030_पढ़ो(component, TWL4030_REG_VOICE_IF);

	अगर (tristate)
		reg |= TWL4030_VIF_TRI_EN;
	अन्यथा
		reg &= ~TWL4030_VIF_TRI_EN;

	वापस twl4030_ग_लिखो(component, TWL4030_REG_VOICE_IF, reg);
पूर्ण

#घोषणा TWL4030_RATES	 (SNDRV_PCM_RATE_8000_48000)
#घोषणा TWL4030_FORMATS	 (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S32_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops twl4030_dai_hअगरi_ops = अणु
	.startup	= twl4030_startup,
	.shutकरोwn	= twl4030_shutकरोwn,
	.hw_params	= twl4030_hw_params,
	.set_sysclk	= twl4030_set_dai_sysclk,
	.set_fmt	= twl4030_set_dai_fmt,
	.set_tristate	= twl4030_set_tristate,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops twl4030_dai_voice_ops = अणु
	.startup	= twl4030_voice_startup,
	.shutकरोwn	= twl4030_voice_shutकरोwn,
	.hw_params	= twl4030_voice_hw_params,
	.set_sysclk	= twl4030_voice_set_dai_sysclk,
	.set_fmt	= twl4030_voice_set_dai_fmt,
	.set_tristate	= twl4030_voice_set_tristate,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver twl4030_dai[] = अणु
अणु
	.name = "twl4030-hifi",
	.playback = अणु
		.stream_name = "HiFi Playback",
		.channels_min = 2,
		.channels_max = 4,
		.rates = TWL4030_RATES | SNDRV_PCM_RATE_96000,
		.क्रमmats = TWL4030_FORMATS,
		.sig_bits = 24,पूर्ण,
	.capture = अणु
		.stream_name = "HiFi Capture",
		.channels_min = 2,
		.channels_max = 4,
		.rates = TWL4030_RATES,
		.क्रमmats = TWL4030_FORMATS,
		.sig_bits = 24,पूर्ण,
	.ops = &twl4030_dai_hअगरi_ops,
पूर्ण,
अणु
	.name = "twl4030-voice",
	.playback = अणु
		.stream_name = "Voice Playback",
		.channels_min = 1,
		.channels_max = 1,
		.rates = SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_16000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,पूर्ण,
	.capture = अणु
		.stream_name = "Voice Capture",
		.channels_min = 1,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_16000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,पूर्ण,
	.ops = &twl4030_dai_voice_ops,
पूर्ण,
पूर्ण;

अटल पूर्णांक twl4030_soc_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा twl4030_priv *twl4030;

	twl4030 = devm_kzalloc(component->dev, माप(काष्ठा twl4030_priv),
			       GFP_KERNEL);
	अगर (!twl4030)
		वापस -ENOMEM;
	snd_soc_component_set_drvdata(component, twl4030);
	/* Set the शेषs, and घातer up the codec */
	twl4030->sysclk = twl4030_audio_get_mclk() / 1000;

	twl4030_init_chip(component);

	वापस 0;
पूर्ण

अटल व्योम twl4030_soc_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा twl4030_priv *twl4030 = snd_soc_component_get_drvdata(component);
	काष्ठा twl4030_codec_data *pdata = twl4030->pdata;

	अगर (pdata && pdata->hs_exपंचांगute && gpio_is_valid(pdata->hs_exपंचांगute_gpio))
		gpio_मुक्त(pdata->hs_exपंचांगute_gpio);
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_twl4030 = अणु
	.probe			= twl4030_soc_probe,
	.हटाओ			= twl4030_soc_हटाओ,
	.पढ़ो			= twl4030_पढ़ो,
	.ग_लिखो			= twl4030_ग_लिखो,
	.set_bias_level		= twl4030_set_bias_level,
	.controls		= twl4030_snd_controls,
	.num_controls		= ARRAY_SIZE(twl4030_snd_controls),
	.dapm_widमाला_लो		= twl4030_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(twl4030_dapm_widमाला_लो),
	.dapm_routes		= पूर्णांकercon,
	.num_dapm_routes	= ARRAY_SIZE(पूर्णांकercon),
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल पूर्णांक twl4030_codec_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev,
				      &soc_component_dev_twl4030,
				      twl4030_dai, ARRAY_SIZE(twl4030_dai));
पूर्ण

MODULE_ALIAS("platform:twl4030-codec");

अटल काष्ठा platक्रमm_driver twl4030_codec_driver = अणु
	.probe		= twl4030_codec_probe,
	.driver		= अणु
		.name	= "twl4030-codec",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(twl4030_codec_driver);

MODULE_DESCRIPTION("ASoC TWL4030 codec driver");
MODULE_AUTHOR("Steve Sakoman");
MODULE_LICENSE("GPL");
