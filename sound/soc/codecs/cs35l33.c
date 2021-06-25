<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * cs35l33.c -- CS35L33 ALSA SoC audio driver
 *
 * Copyright 2016 Cirrus Logic, Inc.
 *
 * Author: Paul Handrigan <paul.handrigan@cirrus.com>
 */
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <sound/cs35l33.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>

#समावेश "cs35l33.h"

#घोषणा CS35L33_BOOT_DELAY	50

काष्ठा cs35l33_निजी अणु
	काष्ठा snd_soc_component *component;
	काष्ठा cs35l33_pdata pdata;
	काष्ठा regmap *regmap;
	काष्ठा gpio_desc *reset_gpio;
	bool amp_cal;
	पूर्णांक mclk_पूर्णांक;
	काष्ठा regulator_bulk_data core_supplies[2];
	पूर्णांक num_core_supplies;
	bool is_tdm_mode;
	bool enable_soft_ramp;
पूर्ण;

अटल स्थिर काष्ठा reg_शेष cs35l33_reg[] = अणु
	अणुCS35L33_PWRCTL1, 0x85पूर्ण,
	अणुCS35L33_PWRCTL2, 0xFEपूर्ण,
	अणुCS35L33_CLK_CTL, 0x0Cपूर्ण,
	अणुCS35L33_BST_PEAK_CTL, 0x90पूर्ण,
	अणुCS35L33_PROTECT_CTL, 0x55पूर्ण,
	अणुCS35L33_BST_CTL1, 0x00पूर्ण,
	अणुCS35L33_BST_CTL2, 0x01पूर्ण,
	अणुCS35L33_ADSP_CTL, 0x00पूर्ण,
	अणुCS35L33_ADC_CTL, 0xC8पूर्ण,
	अणुCS35L33_DAC_CTL, 0x14पूर्ण,
	अणुCS35L33_DIG_VOL_CTL, 0x00पूर्ण,
	अणुCS35L33_CLASSD_CTL, 0x04पूर्ण,
	अणुCS35L33_AMP_CTL, 0x90पूर्ण,
	अणुCS35L33_INT_MASK_1, 0xFFपूर्ण,
	अणुCS35L33_INT_MASK_2, 0xFFपूर्ण,
	अणुCS35L33_DIAG_LOCK, 0x00पूर्ण,
	अणुCS35L33_DIAG_CTRL_1, 0x40पूर्ण,
	अणुCS35L33_DIAG_CTRL_2, 0x00पूर्ण,
	अणुCS35L33_HG_MEMLDO_CTL, 0x62पूर्ण,
	अणुCS35L33_HG_REL_RATE, 0x03पूर्ण,
	अणुCS35L33_LDO_DEL, 0x12पूर्ण,
	अणुCS35L33_HG_HEAD, 0x0Aपूर्ण,
	अणुCS35L33_HG_EN, 0x05पूर्ण,
	अणुCS35L33_TX_VMON, 0x00पूर्ण,
	अणुCS35L33_TX_IMON, 0x03पूर्ण,
	अणुCS35L33_TX_VPMON, 0x02पूर्ण,
	अणुCS35L33_TX_VBSTMON, 0x05पूर्ण,
	अणुCS35L33_TX_FLAG, 0x06पूर्ण,
	अणुCS35L33_TX_EN1, 0x00पूर्ण,
	अणुCS35L33_TX_EN2, 0x00पूर्ण,
	अणुCS35L33_TX_EN3, 0x00पूर्ण,
	अणुCS35L33_TX_EN4, 0x00पूर्ण,
	अणुCS35L33_RX_AUD, 0x40पूर्ण,
	अणुCS35L33_RX_SPLY, 0x03पूर्ण,
	अणुCS35L33_RX_ALIVE, 0x04पूर्ण,
	अणुCS35L33_BST_CTL4, 0x63पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_sequence cs35l33_patch[] = अणु
	अणु 0x00,  0x99, 0 पूर्ण,
	अणु 0x59,  0x02, 0 पूर्ण,
	अणु 0x52,  0x30, 0 पूर्ण,
	अणु 0x39,  0x45, 0 पूर्ण,
	अणु 0x57,  0x30, 0 पूर्ण,
	अणु 0x2C,  0x68, 0 पूर्ण,
	अणु 0x00,  0x00, 0 पूर्ण,
पूर्ण;

अटल bool cs35l33_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल CS35L33_DEVID_AB:
	हाल CS35L33_DEVID_CD:
	हाल CS35L33_DEVID_E:
	हाल CS35L33_REV_ID:
	हाल CS35L33_INT_STATUS_1:
	हाल CS35L33_INT_STATUS_2:
	हाल CS35L33_HG_STATUS:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool cs35l33_ग_लिखोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	/* these are पढ़ो only रेजिस्टरs */
	हाल CS35L33_DEVID_AB:
	हाल CS35L33_DEVID_CD:
	हाल CS35L33_DEVID_E:
	हाल CS35L33_REV_ID:
	हाल CS35L33_INT_STATUS_1:
	हाल CS35L33_INT_STATUS_2:
	हाल CS35L33_HG_STATUS:
		वापस false;
	शेष:
		वापस true;
	पूर्ण
पूर्ण

अटल bool cs35l33_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल CS35L33_DEVID_AB:
	हाल CS35L33_DEVID_CD:
	हाल CS35L33_DEVID_E:
	हाल CS35L33_REV_ID:
	हाल CS35L33_PWRCTL1:
	हाल CS35L33_PWRCTL2:
	हाल CS35L33_CLK_CTL:
	हाल CS35L33_BST_PEAK_CTL:
	हाल CS35L33_PROTECT_CTL:
	हाल CS35L33_BST_CTL1:
	हाल CS35L33_BST_CTL2:
	हाल CS35L33_ADSP_CTL:
	हाल CS35L33_ADC_CTL:
	हाल CS35L33_DAC_CTL:
	हाल CS35L33_DIG_VOL_CTL:
	हाल CS35L33_CLASSD_CTL:
	हाल CS35L33_AMP_CTL:
	हाल CS35L33_INT_MASK_1:
	हाल CS35L33_INT_MASK_2:
	हाल CS35L33_INT_STATUS_1:
	हाल CS35L33_INT_STATUS_2:
	हाल CS35L33_DIAG_LOCK:
	हाल CS35L33_DIAG_CTRL_1:
	हाल CS35L33_DIAG_CTRL_2:
	हाल CS35L33_HG_MEMLDO_CTL:
	हाल CS35L33_HG_REL_RATE:
	हाल CS35L33_LDO_DEL:
	हाल CS35L33_HG_HEAD:
	हाल CS35L33_HG_EN:
	हाल CS35L33_TX_VMON:
	हाल CS35L33_TX_IMON:
	हाल CS35L33_TX_VPMON:
	हाल CS35L33_TX_VBSTMON:
	हाल CS35L33_TX_FLAG:
	हाल CS35L33_TX_EN1:
	हाल CS35L33_TX_EN2:
	हाल CS35L33_TX_EN3:
	हाल CS35L33_TX_EN4:
	हाल CS35L33_RX_AUD:
	हाल CS35L33_RX_SPLY:
	हाल CS35L33_RX_ALIVE:
	हाल CS35L33_BST_CTL4:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल DECLARE_TLV_DB_SCALE(classd_ctl_tlv, 900, 100, 0);
अटल DECLARE_TLV_DB_SCALE(dac_tlv, -10200, 50, 0);

अटल स्थिर काष्ठा snd_kcontrol_new cs35l33_snd_controls[] = अणु

	SOC_SINGLE_TLV("SPK Amp Volume", CS35L33_AMP_CTL,
		       4, 0x09, 0, classd_ctl_tlv),
	SOC_SINGLE_SX_TLV("DAC Volume", CS35L33_DIG_VOL_CTL,
			0, 0x34, 0xE4, dac_tlv),
पूर्ण;

अटल पूर्णांक cs35l33_spkrdrv_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा cs35l33_निजी *priv = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		अगर (!priv->amp_cal) अणु
			usleep_range(8000, 9000);
			priv->amp_cal = true;
			regmap_update_bits(priv->regmap, CS35L33_CLASSD_CTL,
				    CS35L33_AMP_CAL, 0);
			dev_dbg(component->dev, "Amp calibration done\n");
		पूर्ण
		dev_dbg(component->dev, "Amp turned on\n");
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		dev_dbg(component->dev, "Amp turned off\n");
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid event = 0x%x\n", event);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cs35l33_sdin_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा cs35l33_निजी *priv = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक val;

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		regmap_update_bits(priv->regmap, CS35L33_PWRCTL1,
				    CS35L33_PDN_BST, 0);
		val = priv->is_tdm_mode ? 0 : CS35L33_PDN_TDM;
		regmap_update_bits(priv->regmap, CS35L33_PWRCTL2,
				    CS35L33_PDN_TDM, val);
		dev_dbg(component->dev, "BST turned on\n");
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMU:
		dev_dbg(component->dev, "SDIN turned on\n");
		अगर (!priv->amp_cal) अणु
			regmap_update_bits(priv->regmap, CS35L33_CLASSD_CTL,
				    CS35L33_AMP_CAL, CS35L33_AMP_CAL);
			dev_dbg(component->dev, "Amp calibration started\n");
			usleep_range(10000, 11000);
		पूर्ण
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		regmap_update_bits(priv->regmap, CS35L33_PWRCTL2,
				    CS35L33_PDN_TDM, CS35L33_PDN_TDM);
		usleep_range(4000, 4100);
		regmap_update_bits(priv->regmap, CS35L33_PWRCTL1,
				    CS35L33_PDN_BST, CS35L33_PDN_BST);
		dev_dbg(component->dev, "BST and SDIN turned off\n");
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid event = 0x%x\n", event);

	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cs35l33_sकरोut_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा cs35l33_निजी *priv = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक mask = CS35L33_SDOUT_3ST_I2S | CS35L33_PDN_TDM;
	अचिन्हित पूर्णांक mask2 = CS35L33_SDOUT_3ST_TDM;
	अचिन्हित पूर्णांक val, val2;

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		अगर (priv->is_tdm_mode) अणु
			/* set sकरोut_3st_i2s and reset pdn_tdm */
			val = CS35L33_SDOUT_3ST_I2S;
			/* reset sकरोut_3st_tdm */
			val2 = 0;
		पूर्ण अन्यथा अणु
			/* reset sकरोut_3st_i2s and set pdn_tdm */
			val = CS35L33_PDN_TDM;
			/* set sकरोut_3st_tdm */
			val2 = CS35L33_SDOUT_3ST_TDM;
		पूर्ण
		dev_dbg(component->dev, "SDOUT turned on\n");
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		val = CS35L33_SDOUT_3ST_I2S | CS35L33_PDN_TDM;
		val2 = CS35L33_SDOUT_3ST_TDM;
		dev_dbg(component->dev, "SDOUT turned off\n");
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid event = 0x%x\n", event);
		वापस 0;
	पूर्ण

	regmap_update_bits(priv->regmap, CS35L33_PWRCTL2,
		mask, val);
	regmap_update_bits(priv->regmap, CS35L33_CLK_CTL,
		mask2, val2);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget cs35l33_dapm_widमाला_लो[] = अणु

	SND_SOC_DAPM_OUTPUT("SPK"),
	SND_SOC_DAPM_OUT_DRV_E("SPKDRV", CS35L33_PWRCTL1, 7, 1, शून्य, 0,
		cs35l33_spkrdrv_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_AIF_IN_E("SDIN", शून्य, 0, CS35L33_PWRCTL2,
		2, 1, cs35l33_sdin_event, SND_SOC_DAPM_PRE_PMU |
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_POST_PMD),

	SND_SOC_DAPM_INPUT("MON"),

	SND_SOC_DAPM_ADC("VMON", शून्य,
		CS35L33_PWRCTL2, CS35L33_PDN_VMON_SHIFT, 1),
	SND_SOC_DAPM_ADC("IMON", शून्य,
		CS35L33_PWRCTL2, CS35L33_PDN_IMON_SHIFT, 1),
	SND_SOC_DAPM_ADC("VPMON", शून्य,
		CS35L33_PWRCTL2, CS35L33_PDN_VPMON_SHIFT, 1),
	SND_SOC_DAPM_ADC("VBSTMON", शून्य,
		CS35L33_PWRCTL2, CS35L33_PDN_VBSTMON_SHIFT, 1),

	SND_SOC_DAPM_AIF_OUT_E("SDOUT", शून्य, 0, SND_SOC_NOPM, 0, 0,
		cs35l33_sकरोut_event, SND_SOC_DAPM_PRE_PMU |
		SND_SOC_DAPM_PRE_PMD),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route cs35l33_audio_map[] = अणु
	अणु"SDIN", शून्य, "CS35L33 Playback"पूर्ण,
	अणु"SPKDRV", शून्य, "SDIN"पूर्ण,
	अणु"SPK", शून्य, "SPKDRV"पूर्ण,

	अणु"VMON", शून्य, "MON"पूर्ण,
	अणु"IMON", शून्य, "MON"पूर्ण,

	अणु"SDOUT", शून्य, "VMON"पूर्ण,
	अणु"SDOUT", शून्य, "IMON"पूर्ण,
	अणु"CS35L33 Capture", शून्य, "SDOUT"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route cs35l33_vphg_स्वतः_route[] = अणु
	अणु"SPKDRV", शून्य, "VPMON"पूर्ण,
	अणु"VPMON", शून्य, "CS35L33 Playback"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route cs35l33_vp_vbst_mon_route[] = अणु
	अणु"SDOUT", शून्य, "VPMON"पूर्ण,
	अणु"VPMON", शून्य, "MON"पूर्ण,
	अणु"SDOUT", शून्य, "VBSTMON"पूर्ण,
	अणु"VBSTMON", शून्य, "MON"पूर्ण,
पूर्ण;

अटल पूर्णांक cs35l33_set_bias_level(काष्ठा snd_soc_component *component,
				  क्रमागत snd_soc_bias_level level)
अणु
	अचिन्हित पूर्णांक val;
	काष्ठा cs35l33_निजी *priv = snd_soc_component_get_drvdata(component);

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		अवरोध;
	हाल SND_SOC_BIAS_PREPARE:
		regmap_update_bits(priv->regmap, CS35L33_PWRCTL1,
				    CS35L33_PDN_ALL, 0);
		regmap_update_bits(priv->regmap, CS35L33_CLK_CTL,
				    CS35L33_MCLKDIS, 0);
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		regmap_update_bits(priv->regmap, CS35L33_PWRCTL1,
				    CS35L33_PDN_ALL, CS35L33_PDN_ALL);
		regmap_पढ़ो(priv->regmap, CS35L33_INT_STATUS_2, &val);
		usleep_range(1000, 1100);
		अगर (val & CS35L33_PDN_DONE)
			regmap_update_bits(priv->regmap, CS35L33_CLK_CTL,
					    CS35L33_MCLKDIS, CS35L33_MCLKDIS);
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा cs35l33_mclk_भाग अणु
	पूर्णांक mclk;
	पूर्णांक srate;
	u8 adsp_rate;
	u8 पूर्णांक_fs_ratio;
पूर्ण;

अटल स्थिर काष्ठा cs35l33_mclk_भाग cs35l33_mclk_coeffs[] = अणु
	/* MCLK, Sample Rate, adsp_rate, पूर्णांक_fs_ratio */
	अणु5644800, 11025, 0x4, CS35L33_INT_FS_RATEपूर्ण,
	अणु5644800, 22050, 0x8, CS35L33_INT_FS_RATEपूर्ण,
	अणु5644800, 44100, 0xC, CS35L33_INT_FS_RATEपूर्ण,

	अणु6000000,  8000, 0x1, 0पूर्ण,
	अणु6000000, 11025, 0x2, 0पूर्ण,
	अणु6000000, 11029, 0x3, 0पूर्ण,
	अणु6000000, 12000, 0x4, 0पूर्ण,
	अणु6000000, 16000, 0x5, 0पूर्ण,
	अणु6000000, 22050, 0x6, 0पूर्ण,
	अणु6000000, 22059, 0x7, 0पूर्ण,
	अणु6000000, 24000, 0x8, 0पूर्ण,
	अणु6000000, 32000, 0x9, 0पूर्ण,
	अणु6000000, 44100, 0xA, 0पूर्ण,
	अणु6000000, 44118, 0xB, 0पूर्ण,
	अणु6000000, 48000, 0xC, 0पूर्ण,

	अणु6144000,  8000, 0x1, CS35L33_INT_FS_RATEपूर्ण,
	अणु6144000, 12000, 0x4, CS35L33_INT_FS_RATEपूर्ण,
	अणु6144000, 16000, 0x5, CS35L33_INT_FS_RATEपूर्ण,
	अणु6144000, 24000, 0x8, CS35L33_INT_FS_RATEपूर्ण,
	अणु6144000, 32000, 0x9, CS35L33_INT_FS_RATEपूर्ण,
	अणु6144000, 48000, 0xC, CS35L33_INT_FS_RATEपूर्ण,
पूर्ण;

अटल पूर्णांक cs35l33_get_mclk_coeff(पूर्णांक mclk, पूर्णांक srate)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(cs35l33_mclk_coeffs); i++) अणु
		अगर (cs35l33_mclk_coeffs[i].mclk == mclk &&
			cs35l33_mclk_coeffs[i].srate == srate)
			वापस i;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक cs35l33_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा cs35l33_निजी *priv = snd_soc_component_get_drvdata(component);

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		regmap_update_bits(priv->regmap, CS35L33_ADSP_CTL,
			CS35L33_MS_MASK, CS35L33_MS_MASK);
		dev_dbg(component->dev, "Audio port in master mode\n");
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		regmap_update_bits(priv->regmap, CS35L33_ADSP_CTL,
			CS35L33_MS_MASK, 0);
		dev_dbg(component->dev, "Audio port in slave mode\n");
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_DSP_A:
		/*
		 * tdm mode in cs35l33 resembles dsp-a mode very
		 * बंदly, it is dsp-a with fsync shअगरted left by half bclk
		 */
		priv->is_tdm_mode = true;
		dev_dbg(component->dev, "Audio port in TDM mode\n");
		अवरोध;
	हाल SND_SOC_DAIFMT_I2S:
		priv->is_tdm_mode = false;
		dev_dbg(component->dev, "Audio port in I2S mode\n");
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cs35l33_pcm_hw_params(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *params,
				 काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा cs35l33_निजी *priv = snd_soc_component_get_drvdata(component);
	पूर्णांक sample_size = params_width(params);
	पूर्णांक coeff = cs35l33_get_mclk_coeff(priv->mclk_पूर्णांक, params_rate(params));

	अगर (coeff < 0)
		वापस coeff;

	regmap_update_bits(priv->regmap, CS35L33_CLK_CTL,
		CS35L33_ADSP_FS | CS35L33_INT_FS_RATE,
		cs35l33_mclk_coeffs[coeff].पूर्णांक_fs_ratio
		| cs35l33_mclk_coeffs[coeff].adsp_rate);

	अगर (priv->is_tdm_mode) अणु
		sample_size = (sample_size / 8) - 1;
		अगर (sample_size > 2)
			sample_size = 2;
		regmap_update_bits(priv->regmap, CS35L33_RX_AUD,
			CS35L33_AUDIN_RX_DEPTH,
			sample_size << CS35L33_AUDIN_RX_DEPTH_SHIFT);
	पूर्ण

	dev_dbg(component->dev, "sample rate=%d, bits per sample=%d\n",
		params_rate(params), params_width(params));

	वापस 0;
पूर्ण

अटल स्थिर अचिन्हित पूर्णांक cs35l33_src_rates[] = अणु
	8000, 11025, 11029, 12000, 16000, 22050,
	22059, 24000, 32000, 44100, 44118, 48000
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list cs35l33_स्थिरraपूर्णांकs = अणु
	.count  = ARRAY_SIZE(cs35l33_src_rates),
	.list   = cs35l33_src_rates,
पूर्ण;

अटल पूर्णांक cs35l33_pcm_startup(काष्ठा snd_pcm_substream *substream,
			       काष्ठा snd_soc_dai *dai)
अणु
	snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
					SNDRV_PCM_HW_PARAM_RATE,
					&cs35l33_स्थिरraपूर्णांकs);
	वापस 0;
पूर्ण

अटल पूर्णांक cs35l33_set_tristate(काष्ठा snd_soc_dai *dai, पूर्णांक tristate)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा cs35l33_निजी *priv = snd_soc_component_get_drvdata(component);

	अगर (tristate) अणु
		regmap_update_bits(priv->regmap, CS35L33_PWRCTL2,
			CS35L33_SDOUT_3ST_I2S, CS35L33_SDOUT_3ST_I2S);
		regmap_update_bits(priv->regmap, CS35L33_CLK_CTL,
			CS35L33_SDOUT_3ST_TDM, CS35L33_SDOUT_3ST_TDM);
	पूर्ण अन्यथा अणु
		regmap_update_bits(priv->regmap, CS35L33_PWRCTL2,
			CS35L33_SDOUT_3ST_I2S, 0);
		regmap_update_bits(priv->regmap, CS35L33_CLK_CTL,
			CS35L33_SDOUT_3ST_TDM, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cs35l33_set_tdm_slot(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक tx_mask,
				अचिन्हित पूर्णांक rx_mask, पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	काष्ठा cs35l33_निजी *priv = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक reg, bit_pos, i;
	पूर्णांक slot, slot_num;

	अगर (slot_width != 8)
		वापस -EINVAL;

	/* scan rx_mask क्रम aud slot */
	slot = ffs(rx_mask) - 1;
	अगर (slot >= 0) अणु
		regmap_update_bits(priv->regmap, CS35L33_RX_AUD,
			CS35L33_X_LOC, slot);
		dev_dbg(component->dev, "Audio starts from slots %d", slot);
	पूर्ण

	/*
	 * scan tx_mask: vmon(2 slots); imon (2 slots);
	 * vpmon (1 slot) vbsपंचांगon (1 slot)
	 */
	slot = ffs(tx_mask) - 1;
	slot_num = 0;

	क्रम (i = 0; i < 2 ; i++) अणु
		/* disable vpmon/vbsपंचांगon: enable later अगर set in tx_mask */
		regmap_update_bits(priv->regmap, CS35L33_TX_VPMON + i,
			CS35L33_X_STATE | CS35L33_X_LOC, CS35L33_X_STATE
			| CS35L33_X_LOC);
	पूर्ण

	/* disconnect अणुvp,vbstपूर्ण_mon routes: eanble later अगर set in tx_mask*/
	snd_soc_dapm_del_routes(dapm, cs35l33_vp_vbst_mon_route,
		ARRAY_SIZE(cs35l33_vp_vbst_mon_route));

	जबतक (slot >= 0) अणु
		/* configure VMON_TX_LOC */
		अगर (slot_num == 0) अणु
			regmap_update_bits(priv->regmap, CS35L33_TX_VMON,
				CS35L33_X_STATE | CS35L33_X_LOC, slot);
			dev_dbg(component->dev, "VMON enabled in slots %d-%d",
				slot, slot + 1);
		पूर्ण

		/* configure IMON_TX_LOC */
		अगर (slot_num == 3) अणु
			regmap_update_bits(priv->regmap, CS35L33_TX_IMON,
				CS35L33_X_STATE | CS35L33_X_LOC, slot);
			dev_dbg(component->dev, "IMON enabled in slots %d-%d",
				slot, slot + 1);
		पूर्ण

		/* configure VPMON_TX_LOC */
		अगर (slot_num == 4) अणु
			regmap_update_bits(priv->regmap, CS35L33_TX_VPMON,
				CS35L33_X_STATE | CS35L33_X_LOC, slot);
			snd_soc_dapm_add_routes(dapm,
				&cs35l33_vp_vbst_mon_route[0], 2);
			dev_dbg(component->dev, "VPMON enabled in slots %d", slot);
		पूर्ण

		/* configure VBSTMON_TX_LOC */
		अगर (slot_num == 5) अणु
			regmap_update_bits(priv->regmap, CS35L33_TX_VBSTMON,
				CS35L33_X_STATE | CS35L33_X_LOC, slot);
			snd_soc_dapm_add_routes(dapm,
				&cs35l33_vp_vbst_mon_route[2], 2);
			dev_dbg(component->dev,
				"VBSTMON enabled in slots %d", slot);
		पूर्ण

		/* Enable the relevant tx slot */
		reg = CS35L33_TX_EN4 - (slot/8);
		bit_pos = slot - ((slot / 8) * (8));
		regmap_update_bits(priv->regmap, reg,
			1 << bit_pos, 1 << bit_pos);

		tx_mask &= ~(1 << slot);
		slot = ffs(tx_mask) - 1;
		slot_num++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cs35l33_component_set_sysclk(काष्ठा snd_soc_component *component,
		पूर्णांक clk_id, पूर्णांक source, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा cs35l33_निजी *cs35l33 = snd_soc_component_get_drvdata(component);

	चयन (freq) अणु
	हाल CS35L33_MCLK_5644:
	हाल CS35L33_MCLK_6:
	हाल CS35L33_MCLK_6144:
		regmap_update_bits(cs35l33->regmap, CS35L33_CLK_CTL,
			CS35L33_MCLKDIV2, 0);
		cs35l33->mclk_पूर्णांक = freq;
		अवरोध;
	हाल CS35L33_MCLK_11289:
	हाल CS35L33_MCLK_12:
	हाल CS35L33_MCLK_12288:
		regmap_update_bits(cs35l33->regmap, CS35L33_CLK_CTL,
			CS35L33_MCLKDIV2, CS35L33_MCLKDIV2);
		cs35l33->mclk_पूर्णांक = freq/2;
		अवरोध;
	शेष:
		cs35l33->mclk_पूर्णांक = 0;
		वापस -EINVAL;
	पूर्ण

	dev_dbg(component->dev, "external mclk freq=%d, internal mclk freq=%d\n",
		freq, cs35l33->mclk_पूर्णांक);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops cs35l33_ops = अणु
	.startup = cs35l33_pcm_startup,
	.set_tristate = cs35l33_set_tristate,
	.set_fmt = cs35l33_set_dai_fmt,
	.hw_params = cs35l33_pcm_hw_params,
	.set_tdm_slot = cs35l33_set_tdm_slot,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver cs35l33_dai = अणु
		.name = "cs35l33-dai",
		.id = 0,
		.playback = अणु
			.stream_name = "CS35L33 Playback",
			.channels_min = 1,
			.channels_max = 1,
			.rates = CS35L33_RATES,
			.क्रमmats = CS35L33_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "CS35L33 Capture",
			.channels_min = 2,
			.channels_max = 2,
			.rates = CS35L33_RATES,
			.क्रमmats = CS35L33_FORMATS,
		पूर्ण,
		.ops = &cs35l33_ops,
		.symmetric_rate = 1,
पूर्ण;

अटल पूर्णांक cs35l33_set_hg_data(काष्ठा snd_soc_component *component,
			       काष्ठा cs35l33_pdata *pdata)
अणु
	काष्ठा cs35l33_hg *hg_config = &pdata->hg_config;
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	काष्ठा cs35l33_निजी *priv = snd_soc_component_get_drvdata(component);

	अगर (hg_config->enable_hg_algo) अणु
		regmap_update_bits(priv->regmap, CS35L33_HG_MEMLDO_CTL,
			CS35L33_MEM_DEPTH_MASK,
			hg_config->mem_depth << CS35L33_MEM_DEPTH_SHIFT);
		regmap_ग_लिखो(priv->regmap, CS35L33_HG_REL_RATE,
			hg_config->release_rate);
		regmap_update_bits(priv->regmap, CS35L33_HG_HEAD,
			CS35L33_HD_RM_MASK,
			hg_config->hd_rm << CS35L33_HD_RM_SHIFT);
		regmap_update_bits(priv->regmap, CS35L33_HG_MEMLDO_CTL,
			CS35L33_LDO_THLD_MASK,
			hg_config->lकरो_thld << CS35L33_LDO_THLD_SHIFT);
		regmap_update_bits(priv->regmap, CS35L33_HG_MEMLDO_CTL,
			CS35L33_LDO_DISABLE_MASK,
			hg_config->lकरो_path_disable <<
				CS35L33_LDO_DISABLE_SHIFT);
		regmap_update_bits(priv->regmap, CS35L33_LDO_DEL,
			CS35L33_LDO_ENTRY_DELAY_MASK,
			hg_config->lकरो_entry_delay <<
				CS35L33_LDO_ENTRY_DELAY_SHIFT);
		अगर (hg_config->vp_hg_स्वतः) अणु
			regmap_update_bits(priv->regmap, CS35L33_HG_EN,
				CS35L33_VP_HG_AUTO_MASK,
				CS35L33_VP_HG_AUTO_MASK);
			snd_soc_dapm_add_routes(dapm, cs35l33_vphg_स्वतः_route,
				ARRAY_SIZE(cs35l33_vphg_स्वतः_route));
		पूर्ण
		regmap_update_bits(priv->regmap, CS35L33_HG_EN,
			CS35L33_VP_HG_MASK,
			hg_config->vp_hg << CS35L33_VP_HG_SHIFT);
		regmap_update_bits(priv->regmap, CS35L33_LDO_DEL,
			CS35L33_VP_HG_RATE_MASK,
			hg_config->vp_hg_rate << CS35L33_VP_HG_RATE_SHIFT);
		regmap_update_bits(priv->regmap, CS35L33_LDO_DEL,
			CS35L33_VP_HG_VA_MASK,
			hg_config->vp_hg_va << CS35L33_VP_HG_VA_SHIFT);
		regmap_update_bits(priv->regmap, CS35L33_HG_EN,
			CS35L33_CLASS_HG_EN_MASK, CS35L33_CLASS_HG_EN_MASK);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cs35l33_set_bst_ipk(काष्ठा snd_soc_component *component, अचिन्हित पूर्णांक bst)
अणु
	काष्ठा cs35l33_निजी *cs35l33 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret = 0, steps = 0;

	/* Boost current in uA */
	अगर (bst > 3600000 || bst < 1850000) अणु
		dev_err(component->dev, "Invalid boost current %d\n", bst);
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	अगर (bst % 15625) अणु
		dev_err(component->dev, "Current not a multiple of 15625uA (%d)\n",
			bst);
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	जबतक (bst > 1850000) अणु
		bst -= 15625;
		steps++;
	पूर्ण

	regmap_ग_लिखो(cs35l33->regmap, CS35L33_BST_PEAK_CTL,
		steps+0x70);

err:
	वापस ret;
पूर्ण

अटल पूर्णांक cs35l33_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा cs35l33_निजी *cs35l33 = snd_soc_component_get_drvdata(component);

	cs35l33->component = component;
	pm_runसमय_get_sync(component->dev);

	regmap_update_bits(cs35l33->regmap, CS35L33_PROTECT_CTL,
		CS35L33_ALIVE_WD_DIS, 0x8);
	regmap_update_bits(cs35l33->regmap, CS35L33_BST_CTL2,
				CS35L33_ALIVE_WD_DIS2,
				CS35L33_ALIVE_WD_DIS2);

	/* Set Platक्रमm Data */
	regmap_update_bits(cs35l33->regmap, CS35L33_BST_CTL1,
		CS35L33_BST_CTL_MASK, cs35l33->pdata.boost_ctl);
	regmap_update_bits(cs35l33->regmap, CS35L33_CLASSD_CTL,
		CS35L33_AMP_DRV_SEL_MASK,
		cs35l33->pdata.amp_drv_sel << CS35L33_AMP_DRV_SEL_SHIFT);

	अगर (cs35l33->pdata.boost_ipk)
		cs35l33_set_bst_ipk(component, cs35l33->pdata.boost_ipk);

	अगर (cs35l33->enable_soft_ramp) अणु
		snd_soc_component_update_bits(component, CS35L33_DAC_CTL,
			CS35L33_DIGSFT, CS35L33_DIGSFT);
		snd_soc_component_update_bits(component, CS35L33_DAC_CTL,
			CS35L33_DSR_RATE, cs35l33->pdata.ramp_rate);
	पूर्ण अन्यथा अणु
		snd_soc_component_update_bits(component, CS35L33_DAC_CTL,
			CS35L33_DIGSFT, 0);
	पूर्ण

	/* update IMON scaling rate अगर dअगरferent from शेष of 0x8 */
	अगर (cs35l33->pdata.imon_adc_scale != 0x8)
		snd_soc_component_update_bits(component, CS35L33_ADC_CTL,
			CS35L33_IMON_SCALE, cs35l33->pdata.imon_adc_scale);

	cs35l33_set_hg_data(component, &(cs35l33->pdata));

	/*
	 * unmask important पूर्णांकerrupts that causes the chip to enter
	 * speaker safe mode and hence deserves user attention
	 */
	regmap_update_bits(cs35l33->regmap, CS35L33_INT_MASK_1,
		CS35L33_M_OTE | CS35L33_M_OTW | CS35L33_M_AMP_SHORT |
		CS35L33_M_CAL_ERR, 0);

	pm_runसमय_put_sync(component->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_cs35l33 = अणु
	.probe			= cs35l33_probe,
	.set_bias_level		= cs35l33_set_bias_level,
	.set_sysclk		= cs35l33_component_set_sysclk,
	.controls		= cs35l33_snd_controls,
	.num_controls		= ARRAY_SIZE(cs35l33_snd_controls),
	.dapm_widमाला_लो		= cs35l33_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(cs35l33_dapm_widमाला_लो),
	.dapm_routes		= cs35l33_audio_map,
	.num_dapm_routes	= ARRAY_SIZE(cs35l33_audio_map),
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config cs35l33_regmap = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = CS35L33_MAX_REGISTER,
	.reg_शेषs = cs35l33_reg,
	.num_reg_शेषs = ARRAY_SIZE(cs35l33_reg),
	.अस्थिर_reg = cs35l33_अस्थिर_रेजिस्टर,
	.पढ़ोable_reg = cs35l33_पढ़ोable_रेजिस्टर,
	.ग_लिखोable_reg = cs35l33_ग_लिखोable_रेजिस्टर,
	.cache_type = REGCACHE_RBTREE,
	.use_single_पढ़ो = true,
	.use_single_ग_लिखो = true,
पूर्ण;

अटल पूर्णांक __maybe_unused cs35l33_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा cs35l33_निजी *cs35l33 = dev_get_drvdata(dev);
	पूर्णांक ret;

	dev_dbg(dev, "%s\n", __func__);

	gpiod_set_value_cansleep(cs35l33->reset_gpio, 0);

	ret = regulator_bulk_enable(cs35l33->num_core_supplies,
		cs35l33->core_supplies);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to enable core supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	regcache_cache_only(cs35l33->regmap, false);

	gpiod_set_value_cansleep(cs35l33->reset_gpio, 1);

	msleep(CS35L33_BOOT_DELAY);

	ret = regcache_sync(cs35l33->regmap);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to restore register cache\n");
		जाओ err;
	पूर्ण

	वापस 0;

err:
	regcache_cache_only(cs35l33->regmap, true);
	regulator_bulk_disable(cs35l33->num_core_supplies,
		cs35l33->core_supplies);

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused cs35l33_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा cs35l33_निजी *cs35l33 = dev_get_drvdata(dev);

	dev_dbg(dev, "%s\n", __func__);

	/* reकरो the calibration in next घातer up */
	cs35l33->amp_cal = false;

	regcache_cache_only(cs35l33->regmap, true);
	regcache_mark_dirty(cs35l33->regmap);
	regulator_bulk_disable(cs35l33->num_core_supplies,
		cs35l33->core_supplies);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops cs35l33_pm_ops = अणु
	SET_RUNTIME_PM_OPS(cs35l33_runसमय_suspend,
			   cs35l33_runसमय_resume,
			   शून्य)
पूर्ण;

अटल पूर्णांक cs35l33_get_hg_data(स्थिर काष्ठा device_node *np,
			       काष्ठा cs35l33_pdata *pdata)
अणु
	काष्ठा device_node *hg;
	काष्ठा cs35l33_hg *hg_config = &pdata->hg_config;
	u32 val32;

	hg = of_get_child_by_name(np, "cirrus,hg-algo");
	hg_config->enable_hg_algo = hg ? true : false;

	अगर (hg_config->enable_hg_algo) अणु
		अगर (of_property_पढ़ो_u32(hg, "cirrus,mem-depth", &val32) >= 0)
			hg_config->mem_depth = val32;
		अगर (of_property_पढ़ो_u32(hg, "cirrus,release-rate",
				&val32) >= 0)
			hg_config->release_rate = val32;
		अगर (of_property_पढ़ो_u32(hg, "cirrus,ldo-thld", &val32) >= 0)
			hg_config->lकरो_thld = val32;
		अगर (of_property_पढ़ो_u32(hg, "cirrus,ldo-path-disable",
				&val32) >= 0)
			hg_config->lकरो_path_disable = val32;
		अगर (of_property_पढ़ो_u32(hg, "cirrus,ldo-entry-delay",
				&val32) >= 0)
			hg_config->lकरो_entry_delay = val32;

		hg_config->vp_hg_स्वतः = of_property_पढ़ो_bool(hg,
			"cirrus,vp-hg-auto");

		अगर (of_property_पढ़ो_u32(hg, "cirrus,vp-hg", &val32) >= 0)
			hg_config->vp_hg = val32;
		अगर (of_property_पढ़ो_u32(hg, "cirrus,vp-hg-rate", &val32) >= 0)
			hg_config->vp_hg_rate = val32;
		अगर (of_property_पढ़ो_u32(hg, "cirrus,vp-hg-va", &val32) >= 0)
			hg_config->vp_hg_va = val32;
	पूर्ण

	of_node_put(hg);

	वापस 0;
पूर्ण

अटल irqवापस_t cs35l33_irq_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा cs35l33_निजी *cs35l33 = data;
	काष्ठा snd_soc_component *component = cs35l33->component;
	अचिन्हित पूर्णांक sticky_val1, sticky_val2, current_val, mask1, mask2;

	regmap_पढ़ो(cs35l33->regmap, CS35L33_INT_STATUS_2,
		&sticky_val2);
	regmap_पढ़ो(cs35l33->regmap, CS35L33_INT_STATUS_1,
		&sticky_val1);
	regmap_पढ़ो(cs35l33->regmap, CS35L33_INT_MASK_2, &mask2);
	regmap_पढ़ो(cs35l33->regmap, CS35L33_INT_MASK_1, &mask1);

	/* Check to see अगर the unmasked bits are active,
	 *  अगर not then निकास.
	 */
	अगर (!(sticky_val1 & ~mask1) && !(sticky_val2 & ~mask2))
		वापस IRQ_NONE;

	regmap_पढ़ो(cs35l33->regmap, CS35L33_INT_STATUS_1,
		&current_val);

	/* handle the पूर्णांकerrupts */

	अगर (sticky_val1 & CS35L33_AMP_SHORT) अणु
		dev_crit(component->dev, "Amp short error\n");
		अगर (!(current_val & CS35L33_AMP_SHORT)) अणु
			dev_dbg(component->dev,
				"Amp short error release\n");
			regmap_update_bits(cs35l33->regmap,
				CS35L33_AMP_CTL,
				CS35L33_AMP_SHORT_RLS, 0);
			regmap_update_bits(cs35l33->regmap,
				CS35L33_AMP_CTL,
				CS35L33_AMP_SHORT_RLS,
				CS35L33_AMP_SHORT_RLS);
			regmap_update_bits(cs35l33->regmap,
				CS35L33_AMP_CTL, CS35L33_AMP_SHORT_RLS,
				0);
		पूर्ण
	पूर्ण

	अगर (sticky_val1 & CS35L33_CAL_ERR) अणु
		dev_err(component->dev, "Cal error\n");

		/* reकरो the calibration in next घातer up */
		cs35l33->amp_cal = false;

		अगर (!(current_val & CS35L33_CAL_ERR)) अणु
			dev_dbg(component->dev, "Cal error release\n");
			regmap_update_bits(cs35l33->regmap,
				CS35L33_AMP_CTL, CS35L33_CAL_ERR_RLS,
				0);
			regmap_update_bits(cs35l33->regmap,
				CS35L33_AMP_CTL, CS35L33_CAL_ERR_RLS,
				CS35L33_CAL_ERR_RLS);
			regmap_update_bits(cs35l33->regmap,
				CS35L33_AMP_CTL, CS35L33_CAL_ERR_RLS,
				0);
		पूर्ण
	पूर्ण

	अगर (sticky_val1 & CS35L33_OTE) अणु
		dev_crit(component->dev, "Over temperature error\n");
		अगर (!(current_val & CS35L33_OTE)) अणु
			dev_dbg(component->dev,
				"Over temperature error release\n");
			regmap_update_bits(cs35l33->regmap,
				CS35L33_AMP_CTL, CS35L33_OTE_RLS, 0);
			regmap_update_bits(cs35l33->regmap,
				CS35L33_AMP_CTL, CS35L33_OTE_RLS,
				CS35L33_OTE_RLS);
			regmap_update_bits(cs35l33->regmap,
				CS35L33_AMP_CTL, CS35L33_OTE_RLS, 0);
		पूर्ण
	पूर्ण

	अगर (sticky_val1 & CS35L33_OTW) अणु
		dev_err(component->dev, "Over temperature warning\n");
		अगर (!(current_val & CS35L33_OTW)) अणु
			dev_dbg(component->dev,
				"Over temperature warning release\n");
			regmap_update_bits(cs35l33->regmap,
				CS35L33_AMP_CTL, CS35L33_OTW_RLS, 0);
			regmap_update_bits(cs35l33->regmap,
				CS35L33_AMP_CTL, CS35L33_OTW_RLS,
				CS35L33_OTW_RLS);
			regmap_update_bits(cs35l33->regmap,
				CS35L33_AMP_CTL, CS35L33_OTW_RLS, 0);
		पूर्ण
	पूर्ण
	अगर (CS35L33_ALIVE_ERR & sticky_val1)
		dev_err(component->dev, "ERROR: ADSPCLK Interrupt\n");

	अगर (CS35L33_MCLK_ERR & sticky_val1)
		dev_err(component->dev, "ERROR: MCLK Interrupt\n");

	अगर (CS35L33_VMON_OVFL & sticky_val2)
		dev_err(component->dev,
			"ERROR: VMON Overflow Interrupt\n");

	अगर (CS35L33_IMON_OVFL & sticky_val2)
		dev_err(component->dev,
			"ERROR: IMON Overflow Interrupt\n");

	अगर (CS35L33_VPMON_OVFL & sticky_val2)
		dev_err(component->dev,
			"ERROR: VPMON Overflow Interrupt\n");

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर अक्षर * स्थिर cs35l33_core_supplies[] = अणु
	"VA",
	"VP",
पूर्ण;

अटल पूर्णांक cs35l33_of_get_pdata(काष्ठा device *dev,
				काष्ठा cs35l33_निजी *cs35l33)
अणु
	काष्ठा device_node *np = dev->of_node;
	काष्ठा cs35l33_pdata *pdata = &cs35l33->pdata;
	u32 val32;

	अगर (!np)
		वापस 0;

	अगर (of_property_पढ़ो_u32(np, "cirrus,boost-ctl", &val32) >= 0) अणु
		pdata->boost_ctl = val32;
		pdata->amp_drv_sel = 1;
	पूर्ण

	अगर (of_property_पढ़ो_u32(np, "cirrus,ramp-rate", &val32) >= 0) अणु
		pdata->ramp_rate = val32;
		cs35l33->enable_soft_ramp = true;
	पूर्ण

	अगर (of_property_पढ़ो_u32(np, "cirrus,boost-ipk", &val32) >= 0)
		pdata->boost_ipk = val32;

	अगर (of_property_पढ़ो_u32(np, "cirrus,imon-adc-scale", &val32) >= 0) अणु
		अगर ((val32 == 0x0) || (val32 == 0x7) || (val32 == 0x6))
			pdata->imon_adc_scale = val32;
		अन्यथा
			/* use शेष value */
			pdata->imon_adc_scale = 0x8;
	पूर्ण अन्यथा अणु
		/* use शेष value */
		pdata->imon_adc_scale = 0x8;
	पूर्ण

	cs35l33_get_hg_data(np, pdata);

	वापस 0;
पूर्ण

अटल पूर्णांक cs35l33_i2c_probe(काष्ठा i2c_client *i2c_client,
				       स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा cs35l33_निजी *cs35l33;
	काष्ठा cs35l33_pdata *pdata = dev_get_platdata(&i2c_client->dev);
	पूर्णांक ret, devid, i;
	अचिन्हित पूर्णांक reg;

	cs35l33 = devm_kzalloc(&i2c_client->dev, माप(काष्ठा cs35l33_निजी),
			       GFP_KERNEL);
	अगर (!cs35l33)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c_client, cs35l33);
	cs35l33->regmap = devm_regmap_init_i2c(i2c_client, &cs35l33_regmap);
	अगर (IS_ERR(cs35l33->regmap)) अणु
		ret = PTR_ERR(cs35l33->regmap);
		dev_err(&i2c_client->dev, "regmap_init() failed: %d\n", ret);
		वापस ret;
	पूर्ण

	regcache_cache_only(cs35l33->regmap, true);

	क्रम (i = 0; i < ARRAY_SIZE(cs35l33_core_supplies); i++)
		cs35l33->core_supplies[i].supply
			= cs35l33_core_supplies[i];
	cs35l33->num_core_supplies = ARRAY_SIZE(cs35l33_core_supplies);

	ret = devm_regulator_bulk_get(&i2c_client->dev,
			cs35l33->num_core_supplies,
			cs35l33->core_supplies);
	अगर (ret != 0) अणु
		dev_err(&i2c_client->dev,
			"Failed to request core supplies: %d\n",
			ret);
		वापस ret;
	पूर्ण

	अगर (pdata) अणु
		cs35l33->pdata = *pdata;
	पूर्ण अन्यथा अणु
		cs35l33_of_get_pdata(&i2c_client->dev, cs35l33);
		pdata = &cs35l33->pdata;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(&i2c_client->dev, i2c_client->irq, शून्य,
			cs35l33_irq_thपढ़ो, IRQF_ONESHOT | IRQF_TRIGGER_LOW,
			"cs35l33", cs35l33);
	अगर (ret != 0)
		dev_warn(&i2c_client->dev, "Failed to request IRQ: %d\n", ret);

	/* We could issue !RST or skip it based on AMP topology */
	cs35l33->reset_gpio = devm_gpiod_get_optional(&i2c_client->dev,
			"reset-gpios", GPIOD_OUT_HIGH);
	अगर (IS_ERR(cs35l33->reset_gpio)) अणु
		dev_err(&i2c_client->dev, "%s ERROR: Can't get reset GPIO\n",
			__func__);
		वापस PTR_ERR(cs35l33->reset_gpio);
	पूर्ण

	ret = regulator_bulk_enable(cs35l33->num_core_supplies,
					cs35l33->core_supplies);
	अगर (ret != 0) अणु
		dev_err(&i2c_client->dev,
			"Failed to enable core supplies: %d\n",
			ret);
		वापस ret;
	पूर्ण

	gpiod_set_value_cansleep(cs35l33->reset_gpio, 1);

	msleep(CS35L33_BOOT_DELAY);
	regcache_cache_only(cs35l33->regmap, false);

	/* initialize codec */
	ret = regmap_पढ़ो(cs35l33->regmap, CS35L33_DEVID_AB, &reg);
	devid = (reg & 0xFF) << 12;
	ret = regmap_पढ़ो(cs35l33->regmap, CS35L33_DEVID_CD, &reg);
	devid |= (reg & 0xFF) << 4;
	ret = regmap_पढ़ो(cs35l33->regmap, CS35L33_DEVID_E, &reg);
	devid |= (reg & 0xF0) >> 4;

	अगर (devid != CS35L33_CHIP_ID) अणु
		dev_err(&i2c_client->dev,
			"CS35L33 Device ID (%X). Expected ID %X\n",
			devid, CS35L33_CHIP_ID);
		ret = -EINVAL;
		जाओ err_enable;
	पूर्ण

	ret = regmap_पढ़ो(cs35l33->regmap, CS35L33_REV_ID, &reg);
	अगर (ret < 0) अणु
		dev_err(&i2c_client->dev, "Get Revision ID failed\n");
		जाओ err_enable;
	पूर्ण

	dev_info(&i2c_client->dev,
		 "Cirrus Logic CS35L33, Revision: %02X\n", reg & 0xFF);

	ret = regmap_रेजिस्टर_patch(cs35l33->regmap,
			cs35l33_patch, ARRAY_SIZE(cs35l33_patch));
	अगर (ret < 0) अणु
		dev_err(&i2c_client->dev,
			"Error in applying regmap patch: %d\n", ret);
		जाओ err_enable;
	पूर्ण

	/* disable mclk and tdm */
	regmap_update_bits(cs35l33->regmap, CS35L33_CLK_CTL,
		CS35L33_MCLKDIS | CS35L33_SDOUT_3ST_TDM,
		CS35L33_MCLKDIS | CS35L33_SDOUT_3ST_TDM);

	pm_runसमय_set_स्वतःsuspend_delay(&i2c_client->dev, 100);
	pm_runसमय_use_स्वतःsuspend(&i2c_client->dev);
	pm_runसमय_set_active(&i2c_client->dev);
	pm_runसमय_enable(&i2c_client->dev);

	ret = devm_snd_soc_रेजिस्टर_component(&i2c_client->dev,
			&soc_component_dev_cs35l33, &cs35l33_dai, 1);
	अगर (ret < 0) अणु
		dev_err(&i2c_client->dev, "%s: Register component failed\n",
			__func__);
		जाओ err_enable;
	पूर्ण

	वापस 0;

err_enable:
	regulator_bulk_disable(cs35l33->num_core_supplies,
			       cs35l33->core_supplies);

	वापस ret;
पूर्ण

अटल पूर्णांक cs35l33_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा cs35l33_निजी *cs35l33 = i2c_get_clientdata(client);

	gpiod_set_value_cansleep(cs35l33->reset_gpio, 0);

	pm_runसमय_disable(&client->dev);
	regulator_bulk_disable(cs35l33->num_core_supplies,
		cs35l33->core_supplies);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id cs35l33_of_match[] = अणु
	अणु .compatible = "cirrus,cs35l33", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, cs35l33_of_match);

अटल स्थिर काष्ठा i2c_device_id cs35l33_id[] = अणु
	अणु"cs35l33", 0पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, cs35l33_id);

अटल काष्ठा i2c_driver cs35l33_i2c_driver = अणु
	.driver = अणु
		.name = "cs35l33",
		.pm = &cs35l33_pm_ops,
		.of_match_table = cs35l33_of_match,

		पूर्ण,
	.id_table = cs35l33_id,
	.probe = cs35l33_i2c_probe,
	.हटाओ = cs35l33_i2c_हटाओ,

पूर्ण;
module_i2c_driver(cs35l33_i2c_driver);

MODULE_DESCRIPTION("ASoC CS35L33 driver");
MODULE_AUTHOR("Paul Handrigan, Cirrus Logic Inc, <paul.handrigan@cirrus.com>");
MODULE_LICENSE("GPL");
