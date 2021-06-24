<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2017, Maxim Integrated

#समावेश <linux/acpi.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/cdev.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_gpपन.स>
#समावेश <sound/tlv.h>
#समावेश "max98373.h"

अटल पूर्णांक max98373_dac_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा max98373_priv *max98373 = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		regmap_update_bits(max98373->regmap,
			MAX98373_R20FF_GLOBAL_SHDN,
			MAX98373_GLOBAL_EN_MASK, 1);
		usleep_range(30000, 31000);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		regmap_update_bits(max98373->regmap,
			MAX98373_R20FF_GLOBAL_SHDN,
			MAX98373_GLOBAL_EN_MASK, 0);
		usleep_range(30000, 31000);
		max98373->tdm_mode = false;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर अक्षर * स्थिर max98373_चयन_text[] = अणु
	"Left", "Right", "LeftRight"पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत dai_sel_क्रमागत =
	SOC_ENUM_SINGLE(MAX98373_R2029_PCM_TO_SPK_MONO_MIX_1,
		MAX98373_PCM_TO_SPK_MONOMIX_CFG_SHIFT,
		3, max98373_चयन_text);

अटल स्थिर काष्ठा snd_kcontrol_new max98373_dai_controls =
	SOC_DAPM_ENUM("DAI Sel", dai_sel_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new max98373_vi_control =
	SOC_DAPM_SINGLE("Switch", MAX98373_R202C_PCM_TX_EN, 0, 1, 0);

अटल स्थिर काष्ठा snd_kcontrol_new max98373_spkfb_control =
	SOC_DAPM_SINGLE("Switch", MAX98373_R2043_AMP_EN, 1, 1, 0);

अटल स्थिर काष्ठा snd_soc_dapm_widget max98373_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_DAC_E("Amp Enable", "HiFi Playback",
	MAX98373_R202B_PCM_RX_EN, 0, 0, max98373_dac_event,
	SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),
SND_SOC_DAPM_MUX("DAI Sel Mux", SND_SOC_NOPM, 0, 0,
	&max98373_dai_controls),
SND_SOC_DAPM_OUTPUT("BE_OUT"),
SND_SOC_DAPM_AIF_OUT("Voltage Sense", "HiFi Capture", 0,
	MAX98373_R2047_IV_SENSE_ADC_EN, 0, 0),
SND_SOC_DAPM_AIF_OUT("Current Sense", "HiFi Capture", 0,
	MAX98373_R2047_IV_SENSE_ADC_EN, 1, 0),
SND_SOC_DAPM_AIF_OUT("Speaker FB Sense", "HiFi Capture", 0,
	SND_SOC_NOPM, 0, 0),
SND_SOC_DAPM_SWITCH("VI Sense", SND_SOC_NOPM, 0, 0,
	&max98373_vi_control),
SND_SOC_DAPM_SWITCH("SpkFB Sense", SND_SOC_NOPM, 0, 0,
	&max98373_spkfb_control),
SND_SOC_DAPM_SIGGEN("VMON"),
SND_SOC_DAPM_SIGGEN("IMON"),
SND_SOC_DAPM_SIGGEN("FBMON"),
पूर्ण;

अटल DECLARE_TLV_DB_SCALE(max98373_digital_tlv, -6350, 50, 1);
अटल स्थिर DECLARE_TLV_DB_RANGE(max98373_spk_tlv,
	0, 8, TLV_DB_SCALE_ITEM(0, 50, 0),
	9, 10, TLV_DB_SCALE_ITEM(500, 100, 0),
);
अटल स्थिर DECLARE_TLV_DB_RANGE(max98373_spkgain_max_tlv,
	0, 9, TLV_DB_SCALE_ITEM(800, 100, 0),
);
अटल स्थिर DECLARE_TLV_DB_RANGE(max98373_dht_step_माप_प्रकारlv,
	0, 1, TLV_DB_SCALE_ITEM(25, 25, 0),
	2, 4, TLV_DB_SCALE_ITEM(100, 100, 0),
);
अटल स्थिर DECLARE_TLV_DB_RANGE(max98373_dht_spkgain_min_tlv,
	0, 9, TLV_DB_SCALE_ITEM(800, 100, 0),
);
अटल स्थिर DECLARE_TLV_DB_RANGE(max98373_dht_rotation_poपूर्णांक_tlv,
	0, 1, TLV_DB_SCALE_ITEM(-3000, 500, 0),
	2, 4, TLV_DB_SCALE_ITEM(-2200, 200, 0),
	5, 6, TLV_DB_SCALE_ITEM(-1500, 300, 0),
	7, 9, TLV_DB_SCALE_ITEM(-1000, 200, 0),
	10, 13, TLV_DB_SCALE_ITEM(-500, 100, 0),
	14, 15, TLV_DB_SCALE_ITEM(-100, 50, 0),
);
अटल स्थिर DECLARE_TLV_DB_RANGE(max98373_limiter_thresh_tlv,
	0, 15, TLV_DB_SCALE_ITEM(-1500, 100, 0),
);

अटल स्थिर DECLARE_TLV_DB_RANGE(max98373_bde_gain_tlv,
	0, 60, TLV_DB_SCALE_ITEM(-1500, 25, 0),
);

अटल स्थिर अक्षर * स्थिर max98373_output_voltage_lvl_text[] = अणु
	"5.43V", "6.09V", "6.83V", "7.67V", "8.60V",
	"9.65V", "10.83V", "12.15V", "13.63V", "15.29V"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(max98373_out_volt_क्रमागत,
			    MAX98373_R203E_AMP_PATH_GAIN, 0,
			    max98373_output_voltage_lvl_text);

अटल स्थिर अक्षर * स्थिर max98373_dht_attack_rate_text[] = अणु
	"17.5us", "35us", "70us", "140us",
	"280us", "560us", "1120us", "2240us"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(max98373_dht_attack_rate_क्रमागत,
			    MAX98373_R20D2_DHT_ATTACK_CFG, 0,
			    max98373_dht_attack_rate_text);

अटल स्थिर अक्षर * स्थिर max98373_dht_release_rate_text[] = अणु
	"45ms", "225ms", "450ms", "1150ms",
	"2250ms", "3100ms", "4500ms", "6750ms"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(max98373_dht_release_rate_क्रमागत,
			    MAX98373_R20D3_DHT_RELEASE_CFG, 0,
			    max98373_dht_release_rate_text);

अटल स्थिर अक्षर * स्थिर max98373_limiter_attack_rate_text[] = अणु
	"10us", "20us", "40us", "80us",
	"160us", "320us", "640us", "1.28ms",
	"2.56ms", "5.12ms", "10.24ms", "20.48ms",
	"40.96ms", "81.92ms", "16.384ms", "32.768ms"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(max98373_limiter_attack_rate_क्रमागत,
			    MAX98373_R20E1_LIMITER_ATK_REL_RATES, 4,
			    max98373_limiter_attack_rate_text);

अटल स्थिर अक्षर * स्थिर max98373_limiter_release_rate_text[] = अणु
	"40us", "80us", "160us", "320us",
	"640us", "1.28ms", "2.56ms", "5.120ms",
	"10.24ms", "20.48ms", "40.96ms", "81.92ms",
	"163.84ms", "327.68ms", "655.36ms", "1310.72ms"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(max98373_limiter_release_rate_क्रमागत,
			    MAX98373_R20E1_LIMITER_ATK_REL_RATES, 0,
			    max98373_limiter_release_rate_text);

अटल स्थिर अक्षर * स्थिर max98373_ADC_samplerate_text[] = अणु
	"333kHz", "192kHz", "64kHz", "48kHz"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(max98373_adc_samplerate_क्रमागत,
			    MAX98373_R2051_MEAS_ADC_SAMPLING_RATE, 0,
			    max98373_ADC_samplerate_text);

अटल पूर्णांक max98373_feedback_get(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा soc_mixer_control *mc =
		(काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	काष्ठा max98373_priv *max98373 = snd_soc_component_get_drvdata(component);
	पूर्णांक i;

	अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
		/*
		 * Register values will be cached beक्रमe suspend. The cached value
		 * will be a valid value and userspace will happy with that.
		 */
		क्रम (i = 0; i < max98373->cache_num; i++) अणु
			अगर (mc->reg == max98373->cache[i].reg) अणु
				ucontrol->value.पूर्णांकeger.value[0] = max98373->cache[i].val;
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस snd_soc_get_volsw(kcontrol, ucontrol);
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new max98373_snd_controls[] = अणु
SOC_SINGLE("Digital Vol Sel Switch", MAX98373_R203F_AMP_DSP_CFG,
	MAX98373_AMP_VOL_SEL_SHIFT, 1, 0),
SOC_SINGLE("Volume Location Switch", MAX98373_R203F_AMP_DSP_CFG,
	MAX98373_AMP_VOL_SEL_SHIFT, 1, 0),
SOC_SINGLE("Ramp Up Switch", MAX98373_R203F_AMP_DSP_CFG,
	MAX98373_AMP_DSP_CFG_RMP_UP_SHIFT, 1, 0),
SOC_SINGLE("Ramp Down Switch", MAX98373_R203F_AMP_DSP_CFG,
	MAX98373_AMP_DSP_CFG_RMP_DN_SHIFT, 1, 0),
/* Speaker Amplअगरier Overcurrent Automatic Restart Enable */
SOC_SINGLE("OVC Autorestart Switch", MAX98373_R20FE_DEVICE_AUTO_RESTART_CFG,
	MAX98373_OVC_AUTORESTART_SHIFT, 1, 0),
/* Thermal Shutकरोwn Automatic Restart Enable */
SOC_SINGLE("THERM Autorestart Switch", MAX98373_R20FE_DEVICE_AUTO_RESTART_CFG,
	MAX98373_THERM_AUTORESTART_SHIFT, 1, 0),
/* Clock Monitor Automatic Restart Enable */
SOC_SINGLE("CMON Autorestart Switch", MAX98373_R20FE_DEVICE_AUTO_RESTART_CFG,
	MAX98373_CMON_AUTORESTART_SHIFT, 1, 0),
SOC_SINGLE("CLK Monitor Switch", MAX98373_R20FE_DEVICE_AUTO_RESTART_CFG,
	MAX98373_CLOCK_MON_SHIFT, 1, 0),
SOC_SINGLE("Dither Switch", MAX98373_R203F_AMP_DSP_CFG,
	MAX98373_AMP_DSP_CFG_DITH_SHIFT, 1, 0),
SOC_SINGLE("DC Blocker Switch", MAX98373_R203F_AMP_DSP_CFG,
	MAX98373_AMP_DSP_CFG_DCBLK_SHIFT, 1, 0),
SOC_SINGLE_TLV("Digital Volume", MAX98373_R203D_AMP_DIG_VOL_CTRL,
	0, 0x7F, 1, max98373_digital_tlv),
SOC_SINGLE_TLV("Speaker Volume", MAX98373_R203E_AMP_PATH_GAIN,
	MAX98373_SPK_DIGI_GAIN_SHIFT, 10, 0, max98373_spk_tlv),
SOC_SINGLE_TLV("FS Max Volume", MAX98373_R203E_AMP_PATH_GAIN,
	MAX98373_FS_GAIN_MAX_SHIFT, 9, 0, max98373_spkgain_max_tlv),
SOC_ENUM("Output Voltage", max98373_out_volt_क्रमागत),
/* Dynamic Headroom Tracking */
SOC_SINGLE("DHT Switch", MAX98373_R20D4_DHT_EN,
	MAX98373_DHT_EN_SHIFT, 1, 0),
SOC_SINGLE_TLV("DHT Min Volume", MAX98373_R20D1_DHT_CFG,
	MAX98373_DHT_SPK_GAIN_MIN_SHIFT, 9, 0, max98373_dht_spkgain_min_tlv),
SOC_SINGLE_TLV("DHT Rot Pnt Volume", MAX98373_R20D1_DHT_CFG,
	MAX98373_DHT_ROT_PNT_SHIFT, 15, 1, max98373_dht_rotation_poपूर्णांक_tlv),
SOC_SINGLE_TLV("DHT Attack Step Volume", MAX98373_R20D2_DHT_ATTACK_CFG,
	MAX98373_DHT_ATTACK_STEP_SHIFT, 4, 0, max98373_dht_step_माप_प्रकारlv),
SOC_SINGLE_TLV("DHT Release Step Volume", MAX98373_R20D3_DHT_RELEASE_CFG,
	MAX98373_DHT_RELEASE_STEP_SHIFT, 4, 0, max98373_dht_step_माप_प्रकारlv),
SOC_ENUM("DHT Attack Rate", max98373_dht_attack_rate_क्रमागत),
SOC_ENUM("DHT Release Rate", max98373_dht_release_rate_क्रमागत),
/* ADC configuration */
SOC_SINGLE("ADC PVDD CH Switch", MAX98373_R2056_MEAS_ADC_PVDD_CH_EN, 0, 1, 0),
SOC_SINGLE("ADC PVDD FLT Switch", MAX98373_R2052_MEAS_ADC_PVDD_FLT_CFG,
	MAX98373_FLT_EN_SHIFT, 1, 0),
SOC_SINGLE("ADC TEMP FLT Switch", MAX98373_R2053_MEAS_ADC_THERM_FLT_CFG,
	MAX98373_FLT_EN_SHIFT, 1, 0),
SOC_SINGLE_EXT("ADC PVDD", MAX98373_R2054_MEAS_ADC_PVDD_CH_READBACK, 0, 0xFF, 0,
	max98373_feedback_get, शून्य),
SOC_SINGLE_EXT("ADC TEMP", MAX98373_R2055_MEAS_ADC_THERM_CH_READBACK, 0, 0xFF, 0,
	max98373_feedback_get, शून्य),
SOC_SINGLE("ADC PVDD FLT Coeff", MAX98373_R2052_MEAS_ADC_PVDD_FLT_CFG,
	0, 0x3, 0),
SOC_SINGLE("ADC TEMP FLT Coeff", MAX98373_R2053_MEAS_ADC_THERM_FLT_CFG,
	0, 0x3, 0),
SOC_ENUM("ADC SampleRate", max98373_adc_samplerate_क्रमागत),
/* Brownout Detection Engine */
SOC_SINGLE("BDE Switch", MAX98373_R20B5_BDE_EN, MAX98373_BDE_EN_SHIFT, 1, 0),
SOC_SINGLE("BDE LVL4 Mute Switch", MAX98373_R20B2_BDE_L4_CFG_2,
	MAX98373_LVL4_MUTE_EN_SHIFT, 1, 0),
SOC_SINGLE("BDE LVL4 Hold Switch", MAX98373_R20B2_BDE_L4_CFG_2,
	MAX98373_LVL4_HOLD_EN_SHIFT, 1, 0),
SOC_SINGLE("BDE LVL1 Thresh", MAX98373_R2097_BDE_L1_THRESH, 0, 0xFF, 0),
SOC_SINGLE("BDE LVL2 Thresh", MAX98373_R2098_BDE_L2_THRESH, 0, 0xFF, 0),
SOC_SINGLE("BDE LVL3 Thresh", MAX98373_R2099_BDE_L3_THRESH, 0, 0xFF, 0),
SOC_SINGLE("BDE LVL4 Thresh", MAX98373_R209A_BDE_L4_THRESH, 0, 0xFF, 0),
SOC_SINGLE_EXT("BDE Active Level", MAX98373_R20B6_BDE_CUR_STATE_READBACK, 0, 8, 0,
	max98373_feedback_get, शून्य),
SOC_SINGLE("BDE Clip Mode Switch", MAX98373_R2092_BDE_CLIPPER_MODE, 0, 1, 0),
SOC_SINGLE("BDE Thresh Hysteresis", MAX98373_R209B_BDE_THRESH_HYST, 0, 0xFF, 0),
SOC_SINGLE("BDE Hold Time", MAX98373_R2090_BDE_LVL_HOLD, 0, 0xFF, 0),
SOC_SINGLE("BDE Attack Rate", MAX98373_R2091_BDE_GAIN_ATK_REL_RATE, 4, 0xF, 0),
SOC_SINGLE("BDE Release Rate", MAX98373_R2091_BDE_GAIN_ATK_REL_RATE, 0, 0xF, 0),
SOC_SINGLE_TLV("BDE LVL1 Clip Thresh Volume", MAX98373_R20A9_BDE_L1_CFG_2,
	0, 0x3C, 1, max98373_bde_gain_tlv),
SOC_SINGLE_TLV("BDE LVL2 Clip Thresh Volume", MAX98373_R20AC_BDE_L2_CFG_2,
	0, 0x3C, 1, max98373_bde_gain_tlv),
SOC_SINGLE_TLV("BDE LVL3 Clip Thresh Volume", MAX98373_R20AF_BDE_L3_CFG_2,
	0, 0x3C, 1, max98373_bde_gain_tlv),
SOC_SINGLE_TLV("BDE LVL4 Clip Thresh Volume", MAX98373_R20B2_BDE_L4_CFG_2,
	0, 0x3C, 1, max98373_bde_gain_tlv),
SOC_SINGLE_TLV("BDE LVL1 Clip Reduction Volume", MAX98373_R20AA_BDE_L1_CFG_3,
	0, 0x3C, 1, max98373_bde_gain_tlv),
SOC_SINGLE_TLV("BDE LVL2 Clip Reduction Volume", MAX98373_R20AD_BDE_L2_CFG_3,
	0, 0x3C, 1, max98373_bde_gain_tlv),
SOC_SINGLE_TLV("BDE LVL3 Clip Reduction Volume", MAX98373_R20B0_BDE_L3_CFG_3,
	0, 0x3C, 1, max98373_bde_gain_tlv),
SOC_SINGLE_TLV("BDE LVL4 Clip Reduction Volume", MAX98373_R20B3_BDE_L4_CFG_3,
	0, 0x3C, 1, max98373_bde_gain_tlv),
SOC_SINGLE_TLV("BDE LVL1 Limiter Thresh Volume", MAX98373_R20A8_BDE_L1_CFG_1,
	0, 0xF, 1, max98373_limiter_thresh_tlv),
SOC_SINGLE_TLV("BDE LVL2 Limiter Thresh Volume", MAX98373_R20AB_BDE_L2_CFG_1,
	0, 0xF, 1, max98373_limiter_thresh_tlv),
SOC_SINGLE_TLV("BDE LVL3 Limiter Thresh Volume", MAX98373_R20AE_BDE_L3_CFG_1,
	0, 0xF, 1, max98373_limiter_thresh_tlv),
SOC_SINGLE_TLV("BDE LVL4 Limiter Thresh Volume", MAX98373_R20B1_BDE_L4_CFG_1,
	0, 0xF, 1, max98373_limiter_thresh_tlv),
/* Limiter */
SOC_SINGLE("Limiter Switch", MAX98373_R20E2_LIMITER_EN,
	MAX98373_LIMITER_EN_SHIFT, 1, 0),
SOC_SINGLE("Limiter Src Switch", MAX98373_R20E0_LIMITER_THRESH_CFG,
	MAX98373_LIMITER_THRESH_SRC_SHIFT, 1, 0),
SOC_SINGLE_TLV("Limiter Thresh Volume", MAX98373_R20E0_LIMITER_THRESH_CFG,
	MAX98373_LIMITER_THRESH_SHIFT, 15, 0, max98373_limiter_thresh_tlv),
SOC_ENUM("Limiter Attack Rate", max98373_limiter_attack_rate_क्रमागत),
SOC_ENUM("Limiter Release Rate", max98373_limiter_release_rate_क्रमागत),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route max98373_audio_map[] = अणु
	/* Plabyack */
	अणु"DAI Sel Mux", "Left", "Amp Enable"पूर्ण,
	अणु"DAI Sel Mux", "Right", "Amp Enable"पूर्ण,
	अणु"DAI Sel Mux", "LeftRight", "Amp Enable"पूर्ण,
	अणु"BE_OUT", शून्य, "DAI Sel Mux"पूर्ण,
	/* Capture */
	अणु "VI Sense", "Switch", "VMON" पूर्ण,
	अणु "VI Sense", "Switch", "IMON" पूर्ण,
	अणु "SpkFB Sense", "Switch", "FBMON" पूर्ण,
	अणु "Voltage Sense", शून्य, "VI Sense" पूर्ण,
	अणु "Current Sense", शून्य, "VI Sense" पूर्ण,
	अणु "Speaker FB Sense", शून्य, "SpkFB Sense" पूर्ण,
पूर्ण;

व्योम max98373_reset(काष्ठा max98373_priv *max98373, काष्ठा device *dev)
अणु
	पूर्णांक ret, reg, count;

	/* Software Reset */
	ret = regmap_update_bits(max98373->regmap,
		MAX98373_R2000_SW_RESET,
		MAX98373_SOFT_RESET,
		MAX98373_SOFT_RESET);
	अगर (ret)
		dev_err(dev, "Reset command failed. (ret:%d)\n", ret);

	count = 0;
	जबतक (count < 3) अणु
		usleep_range(10000, 11000);
		/* Software Reset Verअगरication */
		ret = regmap_पढ़ो(max98373->regmap,
			MAX98373_R21FF_REV_ID, &reg);
		अगर (!ret) अणु
			dev_info(dev, "Reset completed (retry:%d)\n", count);
			वापस;
		पूर्ण
		count++;
	पूर्ण
	dev_err(dev, "Reset failed. (ret:%d)\n", ret);
पूर्ण
EXPORT_SYMBOL_GPL(max98373_reset);

अटल पूर्णांक max98373_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा max98373_priv *max98373 = snd_soc_component_get_drvdata(component);

	/* Software Reset */
	max98373_reset(max98373, component->dev);

	/* IV शेष slot configuration */
	regmap_ग_लिखो(max98373->regmap,
		MAX98373_R2020_PCM_TX_HIZ_EN_1,
		0xFF);
	regmap_ग_लिखो(max98373->regmap,
		MAX98373_R2021_PCM_TX_HIZ_EN_2,
		0xFF);
	/* L/R mix configuration */
	regmap_ग_लिखो(max98373->regmap,
		MAX98373_R2029_PCM_TO_SPK_MONO_MIX_1,
		0x80);
	regmap_ग_लिखो(max98373->regmap,
		MAX98373_R202A_PCM_TO_SPK_MONO_MIX_2,
		0x1);
	/* Enable DC blocker */
	regmap_ग_लिखो(max98373->regmap,
		MAX98373_R203F_AMP_DSP_CFG,
		0x3);
	/* Enable IMON VMON DC blocker */
	regmap_ग_लिखो(max98373->regmap,
		MAX98373_R2046_IV_SENSE_ADC_DSP_CFG,
		0x7);
	/* voltage, current slot configuration */
	regmap_ग_लिखो(max98373->regmap,
		MAX98373_R2022_PCM_TX_SRC_1,
		(max98373->i_slot << MAX98373_PCM_TX_CH_SRC_A_I_SHIFT |
		max98373->v_slot) & 0xFF);
	अगर (max98373->v_slot < 8)
		regmap_update_bits(max98373->regmap,
			MAX98373_R2020_PCM_TX_HIZ_EN_1,
			1 << max98373->v_slot, 0);
	अन्यथा
		regmap_update_bits(max98373->regmap,
			MAX98373_R2021_PCM_TX_HIZ_EN_2,
			1 << (max98373->v_slot - 8), 0);

	अगर (max98373->i_slot < 8)
		regmap_update_bits(max98373->regmap,
			MAX98373_R2020_PCM_TX_HIZ_EN_1,
			1 << max98373->i_slot, 0);
	अन्यथा
		regmap_update_bits(max98373->regmap,
			MAX98373_R2021_PCM_TX_HIZ_EN_2,
			1 << (max98373->i_slot - 8), 0);

	/* enable स्वतः restart function by शेष */
	regmap_ग_लिखो(max98373->regmap,
		MAX98373_R20FE_DEVICE_AUTO_RESTART_CFG,
		0xF);

	/* speaker feedback slot configuration */
	regmap_ग_लिखो(max98373->regmap,
		MAX98373_R2023_PCM_TX_SRC_2,
		max98373->spkfb_slot & 0xFF);

	/* Set पूर्णांकerleave mode */
	अगर (max98373->पूर्णांकerleave_mode)
		regmap_update_bits(max98373->regmap,
			MAX98373_R2024_PCM_DATA_FMT_CFG,
			MAX98373_PCM_TX_CH_INTERLEAVE_MASK,
			MAX98373_PCM_TX_CH_INTERLEAVE_MASK);

	/* Speaker enable */
	regmap_update_bits(max98373->regmap,
		MAX98373_R2043_AMP_EN,
		MAX98373_SPK_EN_MASK, 1);

	वापस 0;
पूर्ण

स्थिर काष्ठा snd_soc_component_driver soc_codec_dev_max98373 = अणु
	.probe			= max98373_probe,
	.controls		= max98373_snd_controls,
	.num_controls		= ARRAY_SIZE(max98373_snd_controls),
	.dapm_widमाला_लो		= max98373_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(max98373_dapm_widमाला_लो),
	.dapm_routes		= max98373_audio_map,
	.num_dapm_routes	= ARRAY_SIZE(max98373_audio_map),
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;
EXPORT_SYMBOL_GPL(soc_codec_dev_max98373);

स्थिर काष्ठा snd_soc_component_driver soc_codec_dev_max98373_sdw = अणु
	.probe			= शून्य,
	.controls		= max98373_snd_controls,
	.num_controls		= ARRAY_SIZE(max98373_snd_controls),
	.dapm_widमाला_लो		= max98373_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(max98373_dapm_widमाला_लो),
	.dapm_routes		= max98373_audio_map,
	.num_dapm_routes	= ARRAY_SIZE(max98373_audio_map),
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;
EXPORT_SYMBOL_GPL(soc_codec_dev_max98373_sdw);

व्योम max98373_slot_config(काष्ठा device *dev,
			  काष्ठा max98373_priv *max98373)
अणु
	पूर्णांक value;

	अगर (!device_property_पढ़ो_u32(dev, "maxim,vmon-slot-no", &value))
		max98373->v_slot = value & 0xF;
	अन्यथा
		max98373->v_slot = 0;

	अगर (!device_property_पढ़ो_u32(dev, "maxim,imon-slot-no", &value))
		max98373->i_slot = value & 0xF;
	अन्यथा
		max98373->i_slot = 1;
	अगर (dev->of_node) अणु
		max98373->reset_gpio = of_get_named_gpio(dev->of_node,
						"maxim,reset-gpio", 0);
		अगर (!gpio_is_valid(max98373->reset_gpio)) अणु
			dev_err(dev, "Looking up %s property in node %s failed %d\n",
				"maxim,reset-gpio", dev->of_node->full_name,
				max98373->reset_gpio);
		पूर्ण अन्यथा अणु
			dev_dbg(dev, "maxim,reset-gpio=%d",
				max98373->reset_gpio);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* this makes reset_gpio as invalid */
		max98373->reset_gpio = -1;
	पूर्ण

	अगर (!device_property_पढ़ो_u32(dev, "maxim,spkfb-slot-no", &value))
		max98373->spkfb_slot = value & 0xF;
	अन्यथा
		max98373->spkfb_slot = 2;
पूर्ण
EXPORT_SYMBOL_GPL(max98373_slot_config);

MODULE_DESCRIPTION("ALSA SoC MAX98373 driver");
MODULE_AUTHOR("Ryan Lee <ryans.lee@maximintegrated.com>");
MODULE_LICENSE("GPL");
