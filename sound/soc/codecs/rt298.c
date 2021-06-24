<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * rt298.c  --  RT298 ALSA SoC audio codec driver
 *
 * Copyright 2015 Realtek Semiconductor Corp.
 * Author: Bard Liao <bardliao@realtek.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/i2c.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/dmi.h>
#समावेश <linux/acpi.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>
#समावेश <sound/jack.h>
#समावेश <linux/workqueue.h>
#समावेश <sound/rt298.h>

#समावेश "rl6347a.h"
#समावेश "rt298.h"

#घोषणा RT298_VENDOR_ID 0x10ec0298

काष्ठा rt298_priv अणु
	काष्ठा reg_शेष *index_cache;
	पूर्णांक index_cache_size;
	काष्ठा regmap *regmap;
	काष्ठा snd_soc_component *component;
	काष्ठा rt298_platक्रमm_data pdata;
	काष्ठा i2c_client *i2c;
	काष्ठा snd_soc_jack *jack;
	काष्ठा delayed_work jack_detect_work;
	पूर्णांक sys_clk;
	पूर्णांक clk_id;
	पूर्णांक is_hp_in;
पूर्ण;

अटल स्थिर काष्ठा reg_शेष rt298_index_def[] = अणु
	अणु 0x01, 0xa5a8 पूर्ण,
	अणु 0x02, 0x8e95 पूर्ण,
	अणु 0x03, 0x0002 पूर्ण,
	अणु 0x04, 0xaf67 पूर्ण,
	अणु 0x08, 0x200f पूर्ण,
	अणु 0x09, 0xd010 पूर्ण,
	अणु 0x0a, 0x0100 पूर्ण,
	अणु 0x0b, 0x0000 पूर्ण,
	अणु 0x0d, 0x2800 पूर्ण,
	अणु 0x0f, 0x0022 पूर्ण,
	अणु 0x19, 0x0217 पूर्ण,
	अणु 0x20, 0x0020 पूर्ण,
	अणु 0x33, 0x0208 पूर्ण,
	अणु 0x46, 0x0300 पूर्ण,
	अणु 0x49, 0x4004 पूर्ण,
	अणु 0x4f, 0x50c9 पूर्ण,
	अणु 0x50, 0x3000 पूर्ण,
	अणु 0x63, 0x1b02 पूर्ण,
	अणु 0x67, 0x1111 पूर्ण,
	अणु 0x68, 0x1016 पूर्ण,
	अणु 0x69, 0x273f पूर्ण,
पूर्ण;
#घोषणा INDEX_CACHE_SIZE ARRAY_SIZE(rt298_index_def)

अटल स्थिर काष्ठा reg_शेष rt298_reg[] = अणु
	अणु 0x00170500, 0x00000400 पूर्ण,
	अणु 0x00220000, 0x00000031 पूर्ण,
	अणु 0x00239000, 0x0000007f पूर्ण,
	अणु 0x0023a000, 0x0000007f पूर्ण,
	अणु 0x00270500, 0x00000400 पूर्ण,
	अणु 0x00370500, 0x00000400 पूर्ण,
	अणु 0x00870500, 0x00000400 पूर्ण,
	अणु 0x00920000, 0x00000031 पूर्ण,
	अणु 0x00935000, 0x000000c3 पूर्ण,
	अणु 0x00936000, 0x000000c3 पूर्ण,
	अणु 0x00970500, 0x00000400 पूर्ण,
	अणु 0x00b37000, 0x00000097 पूर्ण,
	अणु 0x00b37200, 0x00000097 पूर्ण,
	अणु 0x00b37300, 0x00000097 पूर्ण,
	अणु 0x00c37000, 0x00000000 पूर्ण,
	अणु 0x00c37100, 0x00000080 पूर्ण,
	अणु 0x01270500, 0x00000400 पूर्ण,
	अणु 0x01370500, 0x00000400 पूर्ण,
	अणु 0x01371f00, 0x411111f0 पूर्ण,
	अणु 0x01439000, 0x00000080 पूर्ण,
	अणु 0x0143a000, 0x00000080 पूर्ण,
	अणु 0x01470700, 0x00000000 पूर्ण,
	अणु 0x01470500, 0x00000400 पूर्ण,
	अणु 0x01470c00, 0x00000000 पूर्ण,
	अणु 0x01470100, 0x00000000 पूर्ण,
	अणु 0x01837000, 0x00000000 पूर्ण,
	अणु 0x01870500, 0x00000400 पूर्ण,
	अणु 0x02050000, 0x00000000 पूर्ण,
	अणु 0x02139000, 0x00000080 पूर्ण,
	अणु 0x0213a000, 0x00000080 पूर्ण,
	अणु 0x02170100, 0x00000000 पूर्ण,
	अणु 0x02170500, 0x00000400 पूर्ण,
	अणु 0x02170700, 0x00000000 पूर्ण,
	अणु 0x02270100, 0x00000000 पूर्ण,
	अणु 0x02370100, 0x00000000 पूर्ण,
	अणु 0x01870700, 0x00000020 पूर्ण,
	अणु 0x00830000, 0x000000c3 पूर्ण,
	अणु 0x00930000, 0x000000c3 पूर्ण,
	अणु 0x01270700, 0x00000000 पूर्ण,
पूर्ण;

अटल bool rt298_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल 0 ... 0xff:
	हाल RT298_GET_PARAM(AC_NODE_ROOT, AC_PAR_VENDOR_ID):
	हाल RT298_GET_HP_SENSE:
	हाल RT298_GET_MIC1_SENSE:
	हाल RT298_PROC_COEF:
	हाल VERB_CMD(AC_VERB_GET_EAPD_BTLENABLE, RT298_MIC1, 0):
	हाल VERB_CMD(AC_VERB_GET_EAPD_BTLENABLE, RT298_SPK_OUT, 0):
	हाल VERB_CMD(AC_VERB_GET_EAPD_BTLENABLE, RT298_HP_OUT, 0):
		वापस true;
	शेष:
		वापस false;
	पूर्ण


पूर्ण

अटल bool rt298_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल 0 ... 0xff:
	हाल RT298_GET_PARAM(AC_NODE_ROOT, AC_PAR_VENDOR_ID):
	हाल RT298_GET_HP_SENSE:
	हाल RT298_GET_MIC1_SENSE:
	हाल RT298_SET_AUDIO_POWER:
	हाल RT298_SET_HPO_POWER:
	हाल RT298_SET_SPK_POWER:
	हाल RT298_SET_DMIC1_POWER:
	हाल RT298_SPK_MUX:
	हाल RT298_HPO_MUX:
	हाल RT298_ADC0_MUX:
	हाल RT298_ADC1_MUX:
	हाल RT298_SET_MIC1:
	हाल RT298_SET_PIN_HPO:
	हाल RT298_SET_PIN_SPK:
	हाल RT298_SET_PIN_DMIC1:
	हाल RT298_SPK_EAPD:
	हाल RT298_SET_AMP_GAIN_HPO:
	हाल RT298_SET_DMIC2_DEFAULT:
	हाल RT298_DACL_GAIN:
	हाल RT298_DACR_GAIN:
	हाल RT298_ADCL_GAIN:
	हाल RT298_ADCR_GAIN:
	हाल RT298_MIC_GAIN:
	हाल RT298_SPOL_GAIN:
	हाल RT298_SPOR_GAIN:
	हाल RT298_HPOL_GAIN:
	हाल RT298_HPOR_GAIN:
	हाल RT298_F_DAC_SWITCH:
	हाल RT298_F_RECMIX_SWITCH:
	हाल RT298_REC_MIC_SWITCH:
	हाल RT298_REC_I2S_SWITCH:
	हाल RT298_REC_LINE_SWITCH:
	हाल RT298_REC_BEEP_SWITCH:
	हाल RT298_DAC_FORMAT:
	हाल RT298_ADC_FORMAT:
	हाल RT298_COEF_INDEX:
	हाल RT298_PROC_COEF:
	हाल RT298_SET_AMP_GAIN_ADC_IN1:
	हाल RT298_SET_AMP_GAIN_ADC_IN2:
	हाल RT298_SET_POWER(RT298_DAC_OUT1):
	हाल RT298_SET_POWER(RT298_DAC_OUT2):
	हाल RT298_SET_POWER(RT298_ADC_IN1):
	हाल RT298_SET_POWER(RT298_ADC_IN2):
	हाल RT298_SET_POWER(RT298_DMIC2):
	हाल RT298_SET_POWER(RT298_MIC1):
	हाल VERB_CMD(AC_VERB_GET_EAPD_BTLENABLE, RT298_MIC1, 0):
	हाल VERB_CMD(AC_VERB_GET_EAPD_BTLENABLE, RT298_SPK_OUT, 0):
	हाल VERB_CMD(AC_VERB_GET_EAPD_BTLENABLE, RT298_HP_OUT, 0):
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PM
अटल व्योम rt298_index_sync(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt298_priv *rt298 = snd_soc_component_get_drvdata(component);
	पूर्णांक i;

	क्रम (i = 0; i < INDEX_CACHE_SIZE; i++) अणु
		snd_soc_component_ग_लिखो(component, rt298->index_cache[i].reg,
				  rt298->index_cache[i].def);
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक rt298_support_घातer_controls[] = अणु
	RT298_DAC_OUT1,
	RT298_DAC_OUT2,
	RT298_ADC_IN1,
	RT298_ADC_IN2,
	RT298_MIC1,
	RT298_DMIC1,
	RT298_DMIC2,
	RT298_SPK_OUT,
	RT298_HP_OUT,
पूर्ण;
#घोषणा RT298_POWER_REG_LEN ARRAY_SIZE(rt298_support_घातer_controls)

अटल पूर्णांक rt298_jack_detect(काष्ठा rt298_priv *rt298, bool *hp, bool *mic)
अणु
	काष्ठा snd_soc_dapm_context *dapm;
	अचिन्हित पूर्णांक val, buf;

	*hp = false;
	*mic = false;

	अगर (!rt298->component)
		वापस -EINVAL;

	dapm = snd_soc_component_get_dapm(rt298->component);

	अगर (rt298->pdata.cbj_en) अणु
		regmap_पढ़ो(rt298->regmap, RT298_GET_HP_SENSE, &buf);
		*hp = buf & 0x80000000;
		अगर (*hp == rt298->is_hp_in)
			वापस -1;
		rt298->is_hp_in = *hp;
		अगर (*hp) अणु
			/* घातer on HV,VERF */
			regmap_update_bits(rt298->regmap,
				RT298_DC_GAIN, 0x200, 0x200);

			snd_soc_dapm_क्रमce_enable_pin(dapm, "HV");
			snd_soc_dapm_क्रमce_enable_pin(dapm, "VREF");
			/* घातer LDO1 */
			snd_soc_dapm_क्रमce_enable_pin(dapm, "LDO1");
			snd_soc_dapm_sync(dapm);

			regmap_update_bits(rt298->regmap,
				RT298_POWER_CTRL1, 0x1001, 0);
			regmap_update_bits(rt298->regmap,
				RT298_POWER_CTRL2, 0x4, 0x4);

			regmap_ग_लिखो(rt298->regmap, RT298_SET_MIC1, 0x24);
			msleep(50);

			regmap_update_bits(rt298->regmap,
				RT298_CBJ_CTRL1, 0xfcc0, 0xd400);
			msleep(300);
			regmap_पढ़ो(rt298->regmap, RT298_CBJ_CTRL2, &val);

			अगर (0x0070 == (val & 0x0070)) अणु
				*mic = true;
			पूर्ण अन्यथा अणु
				regmap_update_bits(rt298->regmap,
					RT298_CBJ_CTRL1, 0xfcc0, 0xe400);
				msleep(300);
				regmap_पढ़ो(rt298->regmap,
					RT298_CBJ_CTRL2, &val);
				अगर (0x0070 == (val & 0x0070)) अणु
					*mic = true;
				पूर्ण अन्यथा अणु
					*mic = false;
					regmap_update_bits(rt298->regmap,
						RT298_CBJ_CTRL1,
						0xfcc0, 0xc400);
				पूर्ण
			पूर्ण

			regmap_update_bits(rt298->regmap,
				RT298_DC_GAIN, 0x200, 0x0);

		पूर्ण अन्यथा अणु
			*mic = false;
			regmap_ग_लिखो(rt298->regmap, RT298_SET_MIC1, 0x20);
			regmap_update_bits(rt298->regmap,
				RT298_CBJ_CTRL1, 0x0400, 0x0000);
		पूर्ण
	पूर्ण अन्यथा अणु
		regmap_पढ़ो(rt298->regmap, RT298_GET_HP_SENSE, &buf);
		*hp = buf & 0x80000000;
		regmap_पढ़ो(rt298->regmap, RT298_GET_MIC1_SENSE, &buf);
		*mic = buf & 0x80000000;
	पूर्ण
	अगर (!*mic) अणु
		snd_soc_dapm_disable_pin(dapm, "HV");
		snd_soc_dapm_disable_pin(dapm, "VREF");
	पूर्ण
	अगर (!*hp)
		snd_soc_dapm_disable_pin(dapm, "LDO1");
	snd_soc_dapm_sync(dapm);

	pr_debug("*hp = %d *mic = %d\n", *hp, *mic);

	वापस 0;
पूर्ण

अटल व्योम rt298_jack_detect_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rt298_priv *rt298 =
		container_of(work, काष्ठा rt298_priv, jack_detect_work.work);
	पूर्णांक status = 0;
	bool hp = false;
	bool mic = false;

	अगर (rt298_jack_detect(rt298, &hp, &mic) < 0)
		वापस;

	अगर (hp)
		status |= SND_JACK_HEADPHONE;

	अगर (mic)
		status |= SND_JACK_MICROPHONE;

	snd_soc_jack_report(rt298->jack, status,
		SND_JACK_MICROPHONE | SND_JACK_HEADPHONE);
पूर्ण

पूर्णांक rt298_mic_detect(काष्ठा snd_soc_component *component, काष्ठा snd_soc_jack *jack)
अणु
	काष्ठा rt298_priv *rt298 = snd_soc_component_get_drvdata(component);
	काष्ठा snd_soc_dapm_context *dapm;
	bool hp = false;
	bool mic = false;
	पूर्णांक status = 0;

	/* If jack in शून्य, disable HS jack */
	अगर (!jack) अणु
		regmap_update_bits(rt298->regmap, RT298_IRQ_CTRL, 0x2, 0x0);
		dapm = snd_soc_component_get_dapm(component);
		snd_soc_dapm_disable_pin(dapm, "LDO1");
		snd_soc_dapm_sync(dapm);
		वापस 0;
	पूर्ण

	rt298->jack = jack;
	regmap_update_bits(rt298->regmap, RT298_IRQ_CTRL, 0x2, 0x2);

	rt298_jack_detect(rt298, &hp, &mic);
	अगर (hp)
		status |= SND_JACK_HEADPHONE;

	अगर (mic)
		status |= SND_JACK_MICROPHONE;

	snd_soc_jack_report(rt298->jack, status,
		SND_JACK_MICROPHONE | SND_JACK_HEADPHONE);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(rt298_mic_detect);

अटल पूर्णांक is_mclk_mode(काष्ठा snd_soc_dapm_widget *source,
			 काष्ठा snd_soc_dapm_widget *sink)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(source->dapm);
	काष्ठा rt298_priv *rt298 = snd_soc_component_get_drvdata(component);

	अगर (rt298->clk_id == RT298_SCLK_S_MCLK)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(out_vol_tlv, -6350, 50, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(mic_vol_tlv, 0, 1000, 0);

अटल स्थिर काष्ठा snd_kcontrol_new rt298_snd_controls[] = अणु
	SOC_DOUBLE_R_TLV("DAC0 Playback Volume", RT298_DACL_GAIN,
			    RT298_DACR_GAIN, 0, 0x7f, 0, out_vol_tlv),
	SOC_DOUBLE_R_TLV("ADC0 Capture Volume", RT298_ADCL_GAIN,
			    RT298_ADCR_GAIN, 0, 0x7f, 0, out_vol_tlv),
	SOC_SINGLE_TLV("AMIC Volume", RT298_MIC_GAIN,
			    0, 0x3, 0, mic_vol_tlv),
	SOC_DOUBLE_R("Speaker Playback Switch", RT298_SPOL_GAIN,
			    RT298_SPOR_GAIN, RT298_MUTE_SFT, 1, 1),
पूर्ण;

/* Digital Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new rt298_front_mix[] = अणु
	SOC_DAPM_SINGLE("DAC Switch",  RT298_F_DAC_SWITCH,
			RT298_MUTE_SFT, 1, 1),
	SOC_DAPM_SINGLE("RECMIX Switch", RT298_F_RECMIX_SWITCH,
			RT298_MUTE_SFT, 1, 1),
पूर्ण;

/* Analog Input Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new rt298_rec_mix[] = अणु
	SOC_DAPM_SINGLE("Mic1 Switch", RT298_REC_MIC_SWITCH,
			RT298_MUTE_SFT, 1, 1),
	SOC_DAPM_SINGLE("I2S Switch", RT298_REC_I2S_SWITCH,
			RT298_MUTE_SFT, 1, 1),
	SOC_DAPM_SINGLE("Line1 Switch", RT298_REC_LINE_SWITCH,
			RT298_MUTE_SFT, 1, 1),
	SOC_DAPM_SINGLE("Beep Switch", RT298_REC_BEEP_SWITCH,
			RT298_MUTE_SFT, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new spo_enable_control =
	SOC_DAPM_SINGLE("Switch", RT298_SET_PIN_SPK,
			RT298_SET_PIN_SFT, 1, 0);

अटल स्थिर काष्ठा snd_kcontrol_new hpol_enable_control =
	SOC_DAPM_SINGLE_AUTODISABLE("Switch", RT298_HPOL_GAIN,
			RT298_MUTE_SFT, 1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new hpor_enable_control =
	SOC_DAPM_SINGLE_AUTODISABLE("Switch", RT298_HPOR_GAIN,
			RT298_MUTE_SFT, 1, 1);

/* ADC0 source */
अटल स्थिर अक्षर * स्थिर rt298_adc_src[] = अणु
	"Mic", "RECMIX", "Dmic"
पूर्ण;

अटल स्थिर पूर्णांक rt298_adc_values[] = अणु
	0, 4, 5,
पूर्ण;

अटल SOC_VALUE_ENUM_SINGLE_DECL(
	rt298_adc0_क्रमागत, RT298_ADC0_MUX, RT298_ADC_SEL_SFT,
	RT298_ADC_SEL_MASK, rt298_adc_src, rt298_adc_values);

अटल स्थिर काष्ठा snd_kcontrol_new rt298_adc0_mux =
	SOC_DAPM_ENUM("ADC 0 source", rt298_adc0_क्रमागत);

अटल SOC_VALUE_ENUM_SINGLE_DECL(
	rt298_adc1_क्रमागत, RT298_ADC1_MUX, RT298_ADC_SEL_SFT,
	RT298_ADC_SEL_MASK, rt298_adc_src, rt298_adc_values);

अटल स्थिर काष्ठा snd_kcontrol_new rt298_adc1_mux =
	SOC_DAPM_ENUM("ADC 1 source", rt298_adc1_क्रमागत);

अटल स्थिर अक्षर * स्थिर rt298_dac_src[] = अणु
	"Front", "Surround"
पूर्ण;
/* HP-OUT source */
अटल SOC_ENUM_SINGLE_DECL(rt298_hpo_क्रमागत, RT298_HPO_MUX,
				0, rt298_dac_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt298_hpo_mux =
SOC_DAPM_ENUM("HPO source", rt298_hpo_क्रमागत);

/* SPK-OUT source */
अटल SOC_ENUM_SINGLE_DECL(rt298_spo_क्रमागत, RT298_SPK_MUX,
				0, rt298_dac_src);

अटल स्थिर काष्ठा snd_kcontrol_new rt298_spo_mux =
SOC_DAPM_ENUM("SPO source", rt298_spo_क्रमागत);

अटल पूर्णांक rt298_spk_event(काष्ठा snd_soc_dapm_widget *w,
			    काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		snd_soc_component_ग_लिखो(component,
			RT298_SPK_EAPD, RT298_SET_EAPD_HIGH);
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		snd_soc_component_ग_लिखो(component,
			RT298_SPK_EAPD, RT298_SET_EAPD_LOW);
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt298_set_dmic1_event(काष्ठा snd_soc_dapm_widget *w,
				  काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		snd_soc_component_ग_लिखो(component, RT298_SET_PIN_DMIC1, 0x20);
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		snd_soc_component_ग_लिखो(component, RT298_SET_PIN_DMIC1, 0);
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt298_adc_event(काष्ठा snd_soc_dapm_widget *w,
			     काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	अचिन्हित पूर्णांक nid;

	nid = (w->reg >> 20) & 0xff;

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		snd_soc_component_update_bits(component,
			VERB_CMD(AC_VERB_SET_AMP_GAIN_MUTE, nid, 0),
			0x7080, 0x7000);
		 /* If MCLK करोesn't exist, reset AD filter */
		अगर (!(snd_soc_component_पढ़ो(component, RT298_VAD_CTRL) & 0x200)) अणु
			pr_info("NO MCLK\n");
			चयन (nid) अणु
			हाल RT298_ADC_IN1:
				snd_soc_component_update_bits(component,
					RT298_D_FILTER_CTRL, 0x2, 0x2);
				mdelay(10);
				snd_soc_component_update_bits(component,
					RT298_D_FILTER_CTRL, 0x2, 0x0);
				अवरोध;
			हाल RT298_ADC_IN2:
				snd_soc_component_update_bits(component,
					RT298_D_FILTER_CTRL, 0x4, 0x4);
				mdelay(10);
				snd_soc_component_update_bits(component,
					RT298_D_FILTER_CTRL, 0x4, 0x0);
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		snd_soc_component_update_bits(component,
			VERB_CMD(AC_VERB_SET_AMP_GAIN_MUTE, nid, 0),
			0x7080, 0x7080);
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt298_mic1_event(काष्ठा snd_soc_dapm_widget *w,
			     काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		snd_soc_component_update_bits(component,
			RT298_A_BIAS_CTRL3, 0xc000, 0x8000);
		snd_soc_component_update_bits(component,
			RT298_A_BIAS_CTRL2, 0xc000, 0x8000);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		snd_soc_component_update_bits(component,
			RT298_A_BIAS_CTRL3, 0xc000, 0x0000);
		snd_soc_component_update_bits(component,
			RT298_A_BIAS_CTRL2, 0xc000, 0x0000);
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget rt298_dapm_widमाला_लो[] = अणु

	SND_SOC_DAPM_SUPPLY_S("HV", 1, RT298_POWER_CTRL1,
		12, 1, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("VREF", RT298_POWER_CTRL1,
		0, 1, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("BG_MBIAS", 1, RT298_POWER_CTRL2,
		1, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("LDO1", 1, RT298_POWER_CTRL2,
		2, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("LDO2", 1, RT298_POWER_CTRL2,
		3, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("VREF1", 1, RT298_POWER_CTRL2,
		4, 1, शून्य, 0),
	SND_SOC_DAPM_SUPPLY_S("LV", 2, RT298_POWER_CTRL1,
		13, 1, शून्य, 0),


	SND_SOC_DAPM_SUPPLY("MCLK MODE", RT298_PLL_CTRL1,
		5, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("MIC1 Input Buffer", SND_SOC_NOPM,
		0, 0, rt298_mic1_event, SND_SOC_DAPM_PRE_PMU |
		SND_SOC_DAPM_POST_PMD),

	/* Input Lines */
	SND_SOC_DAPM_INPUT("DMIC1 Pin"),
	SND_SOC_DAPM_INPUT("DMIC2 Pin"),
	SND_SOC_DAPM_INPUT("MIC1"),
	SND_SOC_DAPM_INPUT("LINE1"),
	SND_SOC_DAPM_INPUT("Beep"),

	/* DMIC */
	SND_SOC_DAPM_PGA_E("DMIC1", RT298_SET_POWER(RT298_DMIC1), 0, 1,
		शून्य, 0, rt298_set_dmic1_event,
		SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_PGA("DMIC2", RT298_SET_POWER(RT298_DMIC2), 0, 1,
		शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DMIC Receiver", SND_SOC_NOPM,
		0, 0, शून्य, 0),

	/* REC Mixer */
	SND_SOC_DAPM_MIXER("RECMIX", SND_SOC_NOPM, 0, 0,
		rt298_rec_mix, ARRAY_SIZE(rt298_rec_mix)),

	/* ADCs */
	SND_SOC_DAPM_ADC("ADC 0", शून्य, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_ADC("ADC 1", शून्य, SND_SOC_NOPM, 0, 0),

	/* ADC Mux */
	SND_SOC_DAPM_MUX_E("ADC 0 Mux", RT298_SET_POWER(RT298_ADC_IN1), 0, 1,
		&rt298_adc0_mux, rt298_adc_event, SND_SOC_DAPM_PRE_PMD |
		SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_MUX_E("ADC 1 Mux", RT298_SET_POWER(RT298_ADC_IN2), 0, 1,
		&rt298_adc1_mux, rt298_adc_event, SND_SOC_DAPM_PRE_PMD |
		SND_SOC_DAPM_POST_PMU),

	/* Audio Interface */
	SND_SOC_DAPM_AIF_IN("AIF1RX", "AIF1 Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF1TX", "AIF1 Capture", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("AIF2RX", "AIF2 Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF2TX", "AIF2 Capture", 0, SND_SOC_NOPM, 0, 0),

	/* Output Side */
	/* DACs */
	SND_SOC_DAPM_DAC("DAC 0", शून्य, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC("DAC 1", शून्य, SND_SOC_NOPM, 0, 0),

	/* Output Mux */
	SND_SOC_DAPM_MUX("SPK Mux", SND_SOC_NOPM, 0, 0, &rt298_spo_mux),
	SND_SOC_DAPM_MUX("HPO Mux", SND_SOC_NOPM, 0, 0, &rt298_hpo_mux),

	SND_SOC_DAPM_SUPPLY("HP Power", RT298_SET_PIN_HPO,
		RT298_SET_PIN_SFT, 0, शून्य, 0),

	/* Output Mixer */
	SND_SOC_DAPM_MIXER("Front", RT298_SET_POWER(RT298_DAC_OUT1), 0, 1,
			rt298_front_mix, ARRAY_SIZE(rt298_front_mix)),
	SND_SOC_DAPM_PGA("Surround", RT298_SET_POWER(RT298_DAC_OUT2), 0, 1,
			शून्य, 0),

	/* Output Pga */
	SND_SOC_DAPM_SWITCH_E("SPO", SND_SOC_NOPM, 0, 0,
		&spo_enable_control, rt298_spk_event,
		SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_SWITCH("HPO L", SND_SOC_NOPM, 0, 0,
		&hpol_enable_control),
	SND_SOC_DAPM_SWITCH("HPO R", SND_SOC_NOPM, 0, 0,
		&hpor_enable_control),

	/* Output Lines */
	SND_SOC_DAPM_OUTPUT("SPOL"),
	SND_SOC_DAPM_OUTPUT("SPOR"),
	SND_SOC_DAPM_OUTPUT("HPO Pin"),
	SND_SOC_DAPM_OUTPUT("SPDIF"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route rt298_dapm_routes[] = अणु

	अणु"ADC 0", शून्य, "MCLK MODE", is_mclk_modeपूर्ण,
	अणु"ADC 1", शून्य, "MCLK MODE", is_mclk_modeपूर्ण,
	अणु"Front", शून्य, "MCLK MODE", is_mclk_modeपूर्ण,
	अणु"Surround", शून्य, "MCLK MODE", is_mclk_modeपूर्ण,

	अणु"HP Power", शून्य, "LDO1"पूर्ण,
	अणु"HP Power", शून्य, "LDO2"पूर्ण,
	अणु"HP Power", शून्य, "LV"पूर्ण,
	अणु"HP Power", शून्य, "VREF1"पूर्ण,
	अणु"HP Power", शून्य, "BG_MBIAS"पूर्ण,

	अणु"MIC1", शून्य, "LDO1"पूर्ण,
	अणु"MIC1", शून्य, "LDO2"पूर्ण,
	अणु"MIC1", शून्य, "HV"पूर्ण,
	अणु"MIC1", शून्य, "LV"पूर्ण,
	अणु"MIC1", शून्य, "VREF"पूर्ण,
	अणु"MIC1", शून्य, "VREF1"पूर्ण,
	अणु"MIC1", शून्य, "BG_MBIAS"पूर्ण,
	अणु"MIC1", शून्य, "MIC1 Input Buffer"पूर्ण,

	अणु"SPO", शून्य, "LDO1"पूर्ण,
	अणु"SPO", शून्य, "LDO2"पूर्ण,
	अणु"SPO", शून्य, "HV"पूर्ण,
	अणु"SPO", शून्य, "LV"पूर्ण,
	अणु"SPO", शून्य, "VREF"पूर्ण,
	अणु"SPO", शून्य, "VREF1"पूर्ण,
	अणु"SPO", शून्य, "BG_MBIAS"पूर्ण,

	अणु"DMIC1", शून्य, "DMIC1 Pin"पूर्ण,
	अणु"DMIC2", शून्य, "DMIC2 Pin"पूर्ण,
	अणु"DMIC1", शून्य, "DMIC Receiver"पूर्ण,
	अणु"DMIC2", शून्य, "DMIC Receiver"पूर्ण,

	अणु"RECMIX", "Beep Switch", "Beep"पूर्ण,
	अणु"RECMIX", "Line1 Switch", "LINE1"पूर्ण,
	अणु"RECMIX", "Mic1 Switch", "MIC1"पूर्ण,

	अणु"ADC 0 Mux", "Dmic", "DMIC1"पूर्ण,
	अणु"ADC 0 Mux", "RECMIX", "RECMIX"पूर्ण,
	अणु"ADC 0 Mux", "Mic", "MIC1"पूर्ण,
	अणु"ADC 1 Mux", "Dmic", "DMIC2"पूर्ण,
	अणु"ADC 1 Mux", "RECMIX", "RECMIX"पूर्ण,
	अणु"ADC 1 Mux", "Mic", "MIC1"पूर्ण,

	अणु"ADC 0", शून्य, "ADC 0 Mux"पूर्ण,
	अणु"ADC 1", शून्य, "ADC 1 Mux"पूर्ण,

	अणु"AIF1TX", शून्य, "ADC 0"पूर्ण,
	अणु"AIF2TX", शून्य, "ADC 1"पूर्ण,

	अणु"DAC 0", शून्य, "AIF1RX"पूर्ण,
	अणु"DAC 1", शून्य, "AIF2RX"पूर्ण,

	अणु"Front", "DAC Switch", "DAC 0"पूर्ण,
	अणु"Front", "RECMIX Switch", "RECMIX"पूर्ण,

	अणु"Surround", शून्य, "DAC 1"पूर्ण,

	अणु"SPK Mux", "Front", "Front"पूर्ण,
	अणु"SPK Mux", "Surround", "Surround"पूर्ण,

	अणु"HPO Mux", "Front", "Front"पूर्ण,
	अणु"HPO Mux", "Surround", "Surround"पूर्ण,

	अणु"SPO", "Switch", "SPK Mux"पूर्ण,
	अणु"HPO L", "Switch", "HPO Mux"पूर्ण,
	अणु"HPO R", "Switch", "HPO Mux"पूर्ण,
	अणु"HPO L", शून्य, "HP Power"पूर्ण,
	अणु"HPO R", शून्य, "HP Power"पूर्ण,

	अणु"SPOL", शून्य, "SPO"पूर्ण,
	अणु"SPOR", शून्य, "SPO"पूर्ण,
	अणु"HPO Pin", शून्य, "HPO L"पूर्ण,
	अणु"HPO Pin", शून्य, "HPO R"पूर्ण,
पूर्ण;

अटल पूर्णांक rt298_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt298_priv *rt298 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक val = 0;
	पूर्णांक d_len_code;

	चयन (params_rate(params)) अणु
	/* bit 14 0:48K 1:44.1K */
	हाल 44100:
	हाल 48000:
		अवरोध;
	शेष:
		dev_err(component->dev, "Unsupported sample rate %d\n",
					params_rate(params));
		वापस -EINVAL;
	पूर्ण
	चयन (rt298->sys_clk) अणु
	हाल 12288000:
	हाल 24576000:
		अगर (params_rate(params) != 48000) अणु
			dev_err(component->dev, "Sys_clk is not matched (%d %d)\n",
					params_rate(params), rt298->sys_clk);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल 11289600:
	हाल 22579200:
		अगर (params_rate(params) != 44100) अणु
			dev_err(component->dev, "Sys_clk is not matched (%d %d)\n",
					params_rate(params), rt298->sys_clk);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	पूर्ण

	अगर (params_channels(params) <= 16) अणु
		/* bit 3:0 Number of Channel */
		val |= (params_channels(params) - 1);
	पूर्ण अन्यथा अणु
		dev_err(component->dev, "Unsupported channels %d\n",
					params_channels(params));
		वापस -EINVAL;
	पूर्ण

	d_len_code = 0;
	चयन (params_width(params)) अणु
	/* bit 6:4 Bits per Sample */
	हाल 16:
		d_len_code = 0;
		val |= (0x1 << 4);
		अवरोध;
	हाल 32:
		d_len_code = 2;
		val |= (0x4 << 4);
		अवरोध;
	हाल 20:
		d_len_code = 1;
		val |= (0x2 << 4);
		अवरोध;
	हाल 24:
		d_len_code = 2;
		val |= (0x3 << 4);
		अवरोध;
	हाल 8:
		d_len_code = 3;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component,
		RT298_I2S_CTRL1, 0x0018, d_len_code << 3);
	dev_dbg(component->dev, "format val = 0x%x\n", val);

	snd_soc_component_update_bits(component, RT298_DAC_FORMAT, 0x407f, val);
	snd_soc_component_update_bits(component, RT298_ADC_FORMAT, 0x407f, val);

	वापस 0;
पूर्ण

अटल पूर्णांक rt298_set_dai_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = dai->component;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		snd_soc_component_update_bits(component,
			RT298_I2S_CTRL1, 0x800, 0x800);
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		snd_soc_component_update_bits(component,
			RT298_I2S_CTRL1, 0x800, 0x0);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		snd_soc_component_update_bits(component,
			RT298_I2S_CTRL1, 0x300, 0x0);
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		snd_soc_component_update_bits(component,
			RT298_I2S_CTRL1, 0x300, 0x1 << 8);
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		snd_soc_component_update_bits(component,
			RT298_I2S_CTRL1, 0x300, 0x2 << 8);
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		snd_soc_component_update_bits(component,
			RT298_I2S_CTRL1, 0x300, 0x3 << 8);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	/* bit 15 Stream Type 0:PCM 1:Non-PCM */
	snd_soc_component_update_bits(component, RT298_DAC_FORMAT, 0x8000, 0);
	snd_soc_component_update_bits(component, RT298_ADC_FORMAT, 0x8000, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक rt298_set_dai_sysclk(काष्ठा snd_soc_dai *dai,
				पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt298_priv *rt298 = snd_soc_component_get_drvdata(component);

	dev_dbg(component->dev, "%s freq=%d\n", __func__, freq);

	अगर (RT298_SCLK_S_MCLK == clk_id) अणु
		snd_soc_component_update_bits(component,
			RT298_I2S_CTRL2, 0x0100, 0x0);
		snd_soc_component_update_bits(component,
			RT298_PLL_CTRL1, 0x20, 0x20);
	पूर्ण अन्यथा अणु
		snd_soc_component_update_bits(component,
			RT298_I2S_CTRL2, 0x0100, 0x0100);
		snd_soc_component_update_bits(component,
			RT298_PLL_CTRL1, 0x20, 0x0);
	पूर्ण

	चयन (freq) अणु
	हाल 19200000:
		अगर (RT298_SCLK_S_MCLK == clk_id) अणु
			dev_err(component->dev, "Should not use MCLK\n");
			वापस -EINVAL;
		पूर्ण
		snd_soc_component_update_bits(component,
			RT298_I2S_CTRL2, 0x40, 0x40);
		अवरोध;
	हाल 24000000:
		अगर (RT298_SCLK_S_MCLK == clk_id) अणु
			dev_err(component->dev, "Should not use MCLK\n");
			वापस -EINVAL;
		पूर्ण
		snd_soc_component_update_bits(component,
			RT298_I2S_CTRL2, 0x40, 0x0);
		अवरोध;
	हाल 12288000:
	हाल 11289600:
		snd_soc_component_update_bits(component,
			RT298_I2S_CTRL2, 0x8, 0x0);
		snd_soc_component_update_bits(component,
			RT298_CLK_DIV, 0xfc1e, 0x0004);
		अवरोध;
	हाल 24576000:
	हाल 22579200:
		snd_soc_component_update_bits(component,
			RT298_I2S_CTRL2, 0x8, 0x8);
		snd_soc_component_update_bits(component,
			RT298_CLK_DIV, 0xfc1e, 0x5406);
		अवरोध;
	शेष:
		dev_err(component->dev, "Unsupported system clock\n");
		वापस -EINVAL;
	पूर्ण

	rt298->sys_clk = freq;
	rt298->clk_id = clk_id;

	वापस 0;
पूर्ण

अटल पूर्णांक rt298_set_bclk_ratio(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक ratio)
अणु
	काष्ठा snd_soc_component *component = dai->component;

	dev_dbg(component->dev, "%s ratio=%d\n", __func__, ratio);
	अगर (50 == ratio)
		snd_soc_component_update_bits(component,
			RT298_I2S_CTRL1, 0x1000, 0x1000);
	अन्यथा
		snd_soc_component_update_bits(component,
			RT298_I2S_CTRL1, 0x1000, 0x0);


	वापस 0;
पूर्ण

अटल पूर्णांक rt298_set_bias_level(काष्ठा snd_soc_component *component,
				 क्रमागत snd_soc_bias_level level)
अणु
	चयन (level) अणु
	हाल SND_SOC_BIAS_PREPARE:
		अगर (SND_SOC_BIAS_STANDBY ==
			snd_soc_component_get_bias_level(component)) अणु
			snd_soc_component_ग_लिखो(component,
				RT298_SET_AUDIO_POWER, AC_PWRST_D0);
			snd_soc_component_update_bits(component, 0x0d, 0x200, 0x200);
			snd_soc_component_update_bits(component, 0x52, 0x80, 0x0);
			mdelay(20);
			snd_soc_component_update_bits(component, 0x0d, 0x200, 0x0);
			snd_soc_component_update_bits(component, 0x52, 0x80, 0x80);
		पूर्ण
		अवरोध;

	हाल SND_SOC_BIAS_STANDBY:
		snd_soc_component_ग_लिखो(component,
			RT298_SET_AUDIO_POWER, AC_PWRST_D3);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t rt298_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा rt298_priv *rt298 = data;
	bool hp = false;
	bool mic = false;
	पूर्णांक ret, status = 0;

	ret = rt298_jack_detect(rt298, &hp, &mic);

	/* Clear IRQ */
	regmap_update_bits(rt298->regmap, RT298_IRQ_CTRL, 0x1, 0x1);

	अगर (ret == 0) अणु
		अगर (hp)
			status |= SND_JACK_HEADPHONE;

		अगर (mic)
			status |= SND_JACK_MICROPHONE;

		snd_soc_jack_report(rt298->jack, status,
			SND_JACK_MICROPHONE | SND_JACK_HEADPHONE);

		pm_wakeup_event(&rt298->i2c->dev, 300);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक rt298_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt298_priv *rt298 = snd_soc_component_get_drvdata(component);

	rt298->component = component;

	अगर (rt298->i2c->irq) अणु
		regmap_update_bits(rt298->regmap,
					RT298_IRQ_CTRL, 0x2, 0x2);

		INIT_DELAYED_WORK(&rt298->jack_detect_work,
					rt298_jack_detect_work);
		schedule_delayed_work(&rt298->jack_detect_work,
					msecs_to_jअगरfies(1250));
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rt298_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt298_priv *rt298 = snd_soc_component_get_drvdata(component);

	cancel_delayed_work_sync(&rt298->jack_detect_work);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक rt298_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt298_priv *rt298 = snd_soc_component_get_drvdata(component);

	rt298->is_hp_in = -1;
	regcache_cache_only(rt298->regmap, true);
	regcache_mark_dirty(rt298->regmap);

	वापस 0;
पूर्ण

अटल पूर्णांक rt298_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt298_priv *rt298 = snd_soc_component_get_drvdata(component);

	regcache_cache_only(rt298->regmap, false);
	rt298_index_sync(component);
	regcache_sync(rt298->regmap);

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा rt298_suspend शून्य
#घोषणा rt298_resume शून्य
#पूर्ण_अगर

#घोषणा RT298_STEREO_RATES (SNDRV_PCM_RATE_44100 | SNDRV_PCM_RATE_48000)
#घोषणा RT298_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE | \
			SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S8)

अटल स्थिर काष्ठा snd_soc_dai_ops rt298_aअगर_dai_ops = अणु
	.hw_params = rt298_hw_params,
	.set_fmt = rt298_set_dai_fmt,
	.set_sysclk = rt298_set_dai_sysclk,
	.set_bclk_ratio = rt298_set_bclk_ratio,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver rt298_dai[] = अणु
	अणु
		.name = "rt298-aif1",
		.id = RT298_AIF1,
		.playback = अणु
			.stream_name = "AIF1 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT298_STEREO_RATES,
			.क्रमmats = RT298_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "AIF1 Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT298_STEREO_RATES,
			.क्रमmats = RT298_FORMATS,
		पूर्ण,
		.ops = &rt298_aअगर_dai_ops,
		.symmetric_rate = 1,
	पूर्ण,
	अणु
		.name = "rt298-aif2",
		.id = RT298_AIF2,
		.playback = अणु
			.stream_name = "AIF2 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT298_STEREO_RATES,
			.क्रमmats = RT298_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "AIF2 Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT298_STEREO_RATES,
			.क्रमmats = RT298_FORMATS,
		पूर्ण,
		.ops = &rt298_aअगर_dai_ops,
		.symmetric_rate = 1,
	पूर्ण,

पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_rt298 = अणु
	.probe			= rt298_probe,
	.हटाओ			= rt298_हटाओ,
	.suspend		= rt298_suspend,
	.resume			= rt298_resume,
	.set_bias_level		= rt298_set_bias_level,
	.controls		= rt298_snd_controls,
	.num_controls		= ARRAY_SIZE(rt298_snd_controls),
	.dapm_widमाला_लो		= rt298_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(rt298_dapm_widमाला_लो),
	.dapm_routes		= rt298_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(rt298_dapm_routes),
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config rt298_regmap = अणु
	.reg_bits = 32,
	.val_bits = 32,
	.max_रेजिस्टर = 0x02370100,
	.अस्थिर_reg = rt298_अस्थिर_रेजिस्टर,
	.पढ़ोable_reg = rt298_पढ़ोable_रेजिस्टर,
	.reg_ग_लिखो = rl6347a_hw_ग_लिखो,
	.reg_पढ़ो = rl6347a_hw_पढ़ो,
	.cache_type = REGCACHE_RBTREE,
	.reg_शेषs = rt298_reg,
	.num_reg_शेषs = ARRAY_SIZE(rt298_reg),
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id rt298_i2c_id[] = अणु
	अणु"rt298", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, rt298_i2c_id);

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id rt298_acpi_match[] = अणु
	अणु "INT343A", 0 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, rt298_acpi_match);
#पूर्ण_अगर

अटल स्थिर काष्ठा dmi_प्रणाली_id क्रमce_combo_jack_table[] = अणु
	अणु
		.ident = "Intel Broxton P",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Intel Corp"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Broxton P")
		पूर्ण
	पूर्ण,
	अणु
		.ident = "Intel Gemini Lake",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Intel Corp"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Geminilake")
		पूर्ण
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक rt298_i2c_probe(काष्ठा i2c_client *i2c,
			   स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा rt298_platक्रमm_data *pdata = dev_get_platdata(&i2c->dev);
	काष्ठा rt298_priv *rt298;
	काष्ठा device *dev = &i2c->dev;
	स्थिर काष्ठा acpi_device_id *acpiid;
	पूर्णांक i, ret;

	rt298 = devm_kzalloc(&i2c->dev,	माप(*rt298),
				GFP_KERNEL);
	अगर (शून्य == rt298)
		वापस -ENOMEM;

	rt298->regmap = devm_regmap_init(&i2c->dev, शून्य, i2c, &rt298_regmap);
	अगर (IS_ERR(rt298->regmap)) अणु
		ret = PTR_ERR(rt298->regmap);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	regmap_पढ़ो(rt298->regmap,
		RT298_GET_PARAM(AC_NODE_ROOT, AC_PAR_VENDOR_ID), &ret);
	अगर (ret != RT298_VENDOR_ID) अणु
		dev_err(&i2c->dev,
			"Device with ID register %#x is not rt298\n", ret);
		वापस -ENODEV;
	पूर्ण

	rt298->index_cache = devm_kmemdup(&i2c->dev, rt298_index_def,
					  माप(rt298_index_def), GFP_KERNEL);
	अगर (!rt298->index_cache)
		वापस -ENOMEM;

	rt298->index_cache_size = INDEX_CACHE_SIZE;
	rt298->i2c = i2c;
	i2c_set_clientdata(i2c, rt298);

	/* restore codec शेष */
	क्रम (i = 0; i < INDEX_CACHE_SIZE; i++)
		regmap_ग_लिखो(rt298->regmap, rt298->index_cache[i].reg,
				rt298->index_cache[i].def);
	क्रम (i = 0; i < ARRAY_SIZE(rt298_reg); i++)
		regmap_ग_लिखो(rt298->regmap, rt298_reg[i].reg,
				rt298_reg[i].def);

	अगर (pdata)
		rt298->pdata = *pdata;

	/* enable jack combo mode on supported devices */
	acpiid = acpi_match_device(dev->driver->acpi_match_table, dev);
	अगर (acpiid && acpiid->driver_data) अणु
		rt298->pdata = *(काष्ठा rt298_platक्रमm_data *)
				acpiid->driver_data;
	पूर्ण

	अगर (dmi_check_प्रणाली(क्रमce_combo_jack_table)) अणु
		rt298->pdata.cbj_en = true;
		rt298->pdata.gpio2_en = false;
	पूर्ण

	/* VREF Charging */
	regmap_update_bits(rt298->regmap, 0x04, 0x80, 0x80);
	regmap_update_bits(rt298->regmap, 0x1b, 0x860, 0x860);
	/* Vref2 */
	regmap_update_bits(rt298->regmap, 0x08, 0x20, 0x20);

	regmap_ग_लिखो(rt298->regmap, RT298_SET_AUDIO_POWER, AC_PWRST_D3);

	क्रम (i = 0; i < RT298_POWER_REG_LEN; i++)
		regmap_ग_लिखो(rt298->regmap,
			RT298_SET_POWER(rt298_support_घातer_controls[i]),
			AC_PWRST_D1);

	अगर (!rt298->pdata.cbj_en) अणु
		regmap_ग_लिखो(rt298->regmap, RT298_CBJ_CTRL2, 0x0000);
		regmap_ग_लिखो(rt298->regmap, RT298_MIC1_DET_CTRL, 0x0816);
		regmap_update_bits(rt298->regmap,
					RT298_CBJ_CTRL1, 0xf000, 0xb000);
	पूर्ण अन्यथा अणु
		regmap_update_bits(rt298->regmap,
					RT298_CBJ_CTRL1, 0xf000, 0x5000);
	पूर्ण

	mdelay(10);

	अगर (!rt298->pdata.gpio2_en)
		regmap_ग_लिखो(rt298->regmap, RT298_SET_DMIC2_DEFAULT, 0x40);
	अन्यथा
		regmap_ग_लिखो(rt298->regmap, RT298_SET_DMIC2_DEFAULT, 0);

	mdelay(10);

	regmap_ग_लिखो(rt298->regmap, RT298_MISC_CTRL1, 0x0000);
	regmap_update_bits(rt298->regmap,
				RT298_WIND_FILTER_CTRL, 0x0082, 0x0082);

	regmap_ग_लिखो(rt298->regmap, RT298_UNSOLICITED_INLINE_CMD, 0x81);
	regmap_ग_लिखो(rt298->regmap, RT298_UNSOLICITED_HP_OUT, 0x82);
	regmap_ग_लिखो(rt298->regmap, RT298_UNSOLICITED_MIC1, 0x84);
	regmap_update_bits(rt298->regmap, RT298_IRQ_FLAG_CTRL, 0x2, 0x2);

	rt298->is_hp_in = -1;

	अगर (rt298->i2c->irq) अणु
		ret = request_thपढ़ोed_irq(rt298->i2c->irq, शून्य, rt298_irq,
			IRQF_TRIGGER_HIGH | IRQF_ONESHOT, "rt298", rt298);
		अगर (ret != 0) अणु
			dev_err(&i2c->dev,
				"Failed to reguest IRQ: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev,
				     &soc_component_dev_rt298,
				     rt298_dai, ARRAY_SIZE(rt298_dai));

	वापस ret;
पूर्ण

अटल पूर्णांक rt298_i2c_हटाओ(काष्ठा i2c_client *i2c)
अणु
	काष्ठा rt298_priv *rt298 = i2c_get_clientdata(i2c);

	अगर (i2c->irq)
		मुक्त_irq(i2c->irq, rt298);

	वापस 0;
पूर्ण


अटल काष्ठा i2c_driver rt298_i2c_driver = अणु
	.driver = अणु
		   .name = "rt298",
		   .acpi_match_table = ACPI_PTR(rt298_acpi_match),
		   पूर्ण,
	.probe = rt298_i2c_probe,
	.हटाओ = rt298_i2c_हटाओ,
	.id_table = rt298_i2c_id,
पूर्ण;

module_i2c_driver(rt298_i2c_driver);

MODULE_DESCRIPTION("ASoC RT298 driver");
MODULE_AUTHOR("Bard Liao <bardliao@realtek.com>");
MODULE_LICENSE("GPL");
