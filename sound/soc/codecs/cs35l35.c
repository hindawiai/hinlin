<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * cs35l35.c -- CS35L35 ALSA SoC audio driver
 *
 * Copyright 2017 Cirrus Logic, Inc.
 *
 * Author: Brian Austin <brian.austin@cirrus.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/regmap.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <linux/gpपन.स>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>
#समावेश <sound/cs35l35.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/completion.h>

#समावेश "cs35l35.h"

/*
 * Some fields take zero as a valid value so use a high bit flag that won't
 * get written to the device to mark those.
 */
#घोषणा CS35L35_VALID_PDATA 0x80000000

अटल स्थिर काष्ठा reg_शेष cs35l35_reg[] = अणु
	अणुCS35L35_PWRCTL1,		0x01पूर्ण,
	अणुCS35L35_PWRCTL2,		0x11पूर्ण,
	अणुCS35L35_PWRCTL3,		0x00पूर्ण,
	अणुCS35L35_CLK_CTL1,		0x04पूर्ण,
	अणुCS35L35_CLK_CTL2,		0x12पूर्ण,
	अणुCS35L35_CLK_CTL3,		0xCFपूर्ण,
	अणुCS35L35_SP_FMT_CTL1,		0x20पूर्ण,
	अणुCS35L35_SP_FMT_CTL2,		0x00पूर्ण,
	अणुCS35L35_SP_FMT_CTL3,		0x02पूर्ण,
	अणुCS35L35_MAG_COMP_CTL,		0x00पूर्ण,
	अणुCS35L35_AMP_INP_DRV_CTL,	0x01पूर्ण,
	अणुCS35L35_AMP_DIG_VOL_CTL,	0x12पूर्ण,
	अणुCS35L35_AMP_DIG_VOL,		0x00पूर्ण,
	अणुCS35L35_ADV_DIG_VOL,		0x00पूर्ण,
	अणुCS35L35_PROTECT_CTL,		0x06पूर्ण,
	अणुCS35L35_AMP_GAIN_AUD_CTL,	0x13पूर्ण,
	अणुCS35L35_AMP_GAIN_PDM_CTL,	0x00पूर्ण,
	अणुCS35L35_AMP_GAIN_ADV_CTL,	0x00पूर्ण,
	अणुCS35L35_GPI_CTL,		0x00पूर्ण,
	अणुCS35L35_BST_CVTR_V_CTL,	0x00पूर्ण,
	अणुCS35L35_BST_PEAK_I,		0x07पूर्ण,
	अणुCS35L35_BST_RAMP_CTL,		0x85पूर्ण,
	अणुCS35L35_BST_CONV_COEF_1,	0x24पूर्ण,
	अणुCS35L35_BST_CONV_COEF_2,	0x24पूर्ण,
	अणुCS35L35_BST_CONV_SLOPE_COMP,	0x4Eपूर्ण,
	अणुCS35L35_BST_CONV_SW_FREQ,	0x04पूर्ण,
	अणुCS35L35_CLASS_H_CTL,		0x0Bपूर्ण,
	अणुCS35L35_CLASS_H_HEADRM_CTL,	0x0Bपूर्ण,
	अणुCS35L35_CLASS_H_RELEASE_RATE,	0x08पूर्ण,
	अणुCS35L35_CLASS_H_FET_DRIVE_CTL, 0x41पूर्ण,
	अणुCS35L35_CLASS_H_VP_CTL,	0xC5पूर्ण,
	अणुCS35L35_VPBR_CTL,		0x0Aपूर्ण,
	अणुCS35L35_VPBR_VOL_CTL,		0x90पूर्ण,
	अणुCS35L35_VPBR_TIMING_CTL,	0x6Aपूर्ण,
	अणुCS35L35_VPBR_MODE_VOL_CTL,	0x00पूर्ण,
	अणुCS35L35_SPKR_MON_CTL,		0xC0पूर्ण,
	अणुCS35L35_IMON_SCALE_CTL,	0x30पूर्ण,
	अणुCS35L35_AUDIN_RXLOC_CTL,	0x00पूर्ण,
	अणुCS35L35_ADVIN_RXLOC_CTL,	0x80पूर्ण,
	अणुCS35L35_VMON_TXLOC_CTL,	0x00पूर्ण,
	अणुCS35L35_IMON_TXLOC_CTL,	0x80पूर्ण,
	अणुCS35L35_VPMON_TXLOC_CTL,	0x04पूर्ण,
	अणुCS35L35_VBSTMON_TXLOC_CTL,	0x84पूर्ण,
	अणुCS35L35_VPBR_STATUS_TXLOC_CTL,	0x04पूर्ण,
	अणुCS35L35_ZERO_FILL_LOC_CTL,	0x00पूर्ण,
	अणुCS35L35_AUDIN_DEPTH_CTL,	0x0Fपूर्ण,
	अणुCS35L35_SPKMON_DEPTH_CTL,	0x0Fपूर्ण,
	अणुCS35L35_SUPMON_DEPTH_CTL,	0x0Fपूर्ण,
	अणुCS35L35_ZEROFILL_DEPTH_CTL,	0x00पूर्ण,
	अणुCS35L35_MULT_DEV_SYNCH1,	0x02पूर्ण,
	अणुCS35L35_MULT_DEV_SYNCH2,	0x80पूर्ण,
	अणुCS35L35_PROT_RELEASE_CTL,	0x00पूर्ण,
	अणुCS35L35_DIAG_MODE_REG_LOCK,	0x00पूर्ण,
	अणुCS35L35_DIAG_MODE_CTL_1,	0x40पूर्ण,
	अणुCS35L35_DIAG_MODE_CTL_2,	0x00पूर्ण,
	अणुCS35L35_INT_MASK_1,		0xFFपूर्ण,
	अणुCS35L35_INT_MASK_2,		0xFFपूर्ण,
	अणुCS35L35_INT_MASK_3,		0xFFपूर्ण,
	अणुCS35L35_INT_MASK_4,		0xFFपूर्ण,

पूर्ण;

अटल bool cs35l35_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल CS35L35_INT_STATUS_1:
	हाल CS35L35_INT_STATUS_2:
	हाल CS35L35_INT_STATUS_3:
	हाल CS35L35_INT_STATUS_4:
	हाल CS35L35_PLL_STATUS:
	हाल CS35L35_OTP_TRIM_STATUS:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool cs35l35_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल CS35L35_DEVID_AB ... CS35L35_PWRCTL3:
	हाल CS35L35_CLK_CTL1 ... CS35L35_SP_FMT_CTL3:
	हाल CS35L35_MAG_COMP_CTL ... CS35L35_AMP_GAIN_AUD_CTL:
	हाल CS35L35_AMP_GAIN_PDM_CTL ... CS35L35_BST_PEAK_I:
	हाल CS35L35_BST_RAMP_CTL ... CS35L35_BST_CONV_SW_FREQ:
	हाल CS35L35_CLASS_H_CTL ... CS35L35_CLASS_H_VP_CTL:
	हाल CS35L35_CLASS_H_STATUS:
	हाल CS35L35_VPBR_CTL ... CS35L35_VPBR_MODE_VOL_CTL:
	हाल CS35L35_VPBR_ATTEN_STATUS:
	हाल CS35L35_SPKR_MON_CTL:
	हाल CS35L35_IMON_SCALE_CTL ... CS35L35_ZEROFILL_DEPTH_CTL:
	हाल CS35L35_MULT_DEV_SYNCH1 ... CS35L35_PROT_RELEASE_CTL:
	हाल CS35L35_DIAG_MODE_REG_LOCK ... CS35L35_DIAG_MODE_CTL_2:
	हाल CS35L35_INT_MASK_1 ... CS35L35_PLL_STATUS:
	हाल CS35L35_OTP_TRIM_STATUS:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool cs35l35_precious_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल CS35L35_INT_STATUS_1:
	हाल CS35L35_INT_STATUS_2:
	हाल CS35L35_INT_STATUS_3:
	हाल CS35L35_INT_STATUS_4:
	हाल CS35L35_PLL_STATUS:
	हाल CS35L35_OTP_TRIM_STATUS:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल व्योम cs35l35_reset(काष्ठा cs35l35_निजी *cs35l35)
अणु
	gpiod_set_value_cansleep(cs35l35->reset_gpio, 0);
	usleep_range(2000, 2100);
	gpiod_set_value_cansleep(cs35l35->reset_gpio, 1);
	usleep_range(1000, 1100);
पूर्ण

अटल पूर्णांक cs35l35_रुको_क्रम_pdn(काष्ठा cs35l35_निजी *cs35l35)
अणु
	पूर्णांक ret;

	अगर (cs35l35->pdata.ext_bst) अणु
		usleep_range(5000, 5500);
		वापस 0;
	पूर्ण

	reinit_completion(&cs35l35->pdn_करोne);

	ret = रुको_क्रम_completion_समयout(&cs35l35->pdn_करोne,
					  msecs_to_jअगरfies(100));
	अगर (ret == 0) अणु
		dev_err(cs35l35->dev, "PDN_DONE did not complete\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cs35l35_sdin_event(काष्ठा snd_soc_dapm_widget *w,
		काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा cs35l35_निजी *cs35l35 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret = 0;

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		regmap_update_bits(cs35l35->regmap, CS35L35_CLK_CTL1,
					CS35L35_MCLK_DIS_MASK,
					0 << CS35L35_MCLK_DIS_SHIFT);
		regmap_update_bits(cs35l35->regmap, CS35L35_PWRCTL1,
					CS35L35_DISCHG_FILT_MASK,
					0 << CS35L35_DISCHG_FILT_SHIFT);
		regmap_update_bits(cs35l35->regmap, CS35L35_PWRCTL1,
					CS35L35_PDN_ALL_MASK, 0);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		regmap_update_bits(cs35l35->regmap, CS35L35_PWRCTL1,
					CS35L35_DISCHG_FILT_MASK,
					1 << CS35L35_DISCHG_FILT_SHIFT);
		regmap_update_bits(cs35l35->regmap, CS35L35_PWRCTL1,
					  CS35L35_PDN_ALL_MASK, 1);

		/* Alपढ़ोy muted, so disable volume ramp क्रम faster shutकरोwn */
		regmap_update_bits(cs35l35->regmap, CS35L35_AMP_DIG_VOL_CTL,
				   CS35L35_AMP_DIGSFT_MASK, 0);

		ret = cs35l35_रुको_क्रम_pdn(cs35l35);

		regmap_update_bits(cs35l35->regmap, CS35L35_CLK_CTL1,
					CS35L35_MCLK_DIS_MASK,
					1 << CS35L35_MCLK_DIS_SHIFT);

		regmap_update_bits(cs35l35->regmap, CS35L35_AMP_DIG_VOL_CTL,
				   CS35L35_AMP_DIGSFT_MASK,
				   1 << CS35L35_AMP_DIGSFT_SHIFT);
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid event = 0x%x\n", event);
		ret = -EINVAL;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक cs35l35_मुख्य_amp_event(काष्ठा snd_soc_dapm_widget *w,
		काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा cs35l35_निजी *cs35l35 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक reg[4];
	पूर्णांक i;

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		अगर (cs35l35->pdata.bst_pdn_fet_on)
			regmap_update_bits(cs35l35->regmap, CS35L35_PWRCTL2,
				CS35L35_PDN_BST_MASK,
				0 << CS35L35_PDN_BST_FETON_SHIFT);
		अन्यथा
			regmap_update_bits(cs35l35->regmap, CS35L35_PWRCTL2,
				CS35L35_PDN_BST_MASK,
				0 << CS35L35_PDN_BST_FETOFF_SHIFT);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMU:
		usleep_range(5000, 5100);
		/* If in PDM mode we must use VP क्रम Voltage control */
		अगर (cs35l35->pdm_mode)
			regmap_update_bits(cs35l35->regmap,
					CS35L35_BST_CVTR_V_CTL,
					CS35L35_BST_CTL_MASK,
					0 << CS35L35_BST_CTL_SHIFT);

		regmap_update_bits(cs35l35->regmap, CS35L35_PROTECT_CTL,
			CS35L35_AMP_MUTE_MASK, 0);

		क्रम (i = 0; i < 2; i++)
			regmap_bulk_पढ़ो(cs35l35->regmap, CS35L35_INT_STATUS_1,
					&reg, ARRAY_SIZE(reg));

		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		regmap_update_bits(cs35l35->regmap, CS35L35_PROTECT_CTL,
				CS35L35_AMP_MUTE_MASK,
				1 << CS35L35_AMP_MUTE_SHIFT);
		अगर (cs35l35->pdata.bst_pdn_fet_on)
			regmap_update_bits(cs35l35->regmap, CS35L35_PWRCTL2,
				CS35L35_PDN_BST_MASK,
				1 << CS35L35_PDN_BST_FETON_SHIFT);
		अन्यथा
			regmap_update_bits(cs35l35->regmap, CS35L35_PWRCTL2,
				CS35L35_PDN_BST_MASK,
				1 << CS35L35_PDN_BST_FETOFF_SHIFT);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		usleep_range(5000, 5100);
		/*
		 * If PDM mode we should चयन back to pdata value
		 * क्रम Voltage control when we go करोwn
		 */
		अगर (cs35l35->pdm_mode)
			regmap_update_bits(cs35l35->regmap,
					CS35L35_BST_CVTR_V_CTL,
					CS35L35_BST_CTL_MASK,
					cs35l35->pdata.bst_vctl
					<< CS35L35_BST_CTL_SHIFT);

		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid event = 0x%x\n", event);
	पूर्ण
	वापस 0;
पूर्ण

अटल DECLARE_TLV_DB_SCALE(amp_gain_tlv, 0, 1, 1);
अटल DECLARE_TLV_DB_SCALE(dig_vol_tlv, -10200, 50, 0);

अटल स्थिर काष्ठा snd_kcontrol_new cs35l35_aud_controls[] = अणु
	SOC_SINGLE_SX_TLV("Digital Audio Volume", CS35L35_AMP_DIG_VOL,
		      0, 0x34, 0xE4, dig_vol_tlv),
	SOC_SINGLE_TLV("Analog Audio Volume", CS35L35_AMP_GAIN_AUD_CTL, 0, 19, 0,
			amp_gain_tlv),
	SOC_SINGLE_TLV("PDM Volume", CS35L35_AMP_GAIN_PDM_CTL, 0, 19, 0,
			amp_gain_tlv),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new cs35l35_adv_controls[] = अणु
	SOC_SINGLE_SX_TLV("Digital Advisory Volume", CS35L35_ADV_DIG_VOL,
		      0, 0x34, 0xE4, dig_vol_tlv),
	SOC_SINGLE_TLV("Analog Advisory Volume", CS35L35_AMP_GAIN_ADV_CTL, 0, 19, 0,
			amp_gain_tlv),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget cs35l35_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_AIF_IN_E("SDIN", शून्य, 0, CS35L35_PWRCTL3, 1, 1,
				cs35l35_sdin_event, SND_SOC_DAPM_PRE_PMU |
				SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_AIF_OUT("SDOUT", शून्य, 0, CS35L35_PWRCTL3, 2, 1),

	SND_SOC_DAPM_OUTPUT("SPK"),

	SND_SOC_DAPM_INPUT("VP"),
	SND_SOC_DAPM_INPUT("VBST"),
	SND_SOC_DAPM_INPUT("ISENSE"),
	SND_SOC_DAPM_INPUT("VSENSE"),

	SND_SOC_DAPM_ADC("VMON ADC", शून्य, CS35L35_PWRCTL2, 7, 1),
	SND_SOC_DAPM_ADC("IMON ADC", शून्य, CS35L35_PWRCTL2, 6, 1),
	SND_SOC_DAPM_ADC("VPMON ADC", शून्य, CS35L35_PWRCTL3, 3, 1),
	SND_SOC_DAPM_ADC("VBSTMON ADC", शून्य, CS35L35_PWRCTL3, 4, 1),
	SND_SOC_DAPM_ADC("CLASS H", शून्य, CS35L35_PWRCTL2, 5, 1),

	SND_SOC_DAPM_OUT_DRV_E("Main AMP", CS35L35_PWRCTL2, 0, 1, शून्य, 0,
		cs35l35_मुख्य_amp_event, SND_SOC_DAPM_PRE_PMU |
				SND_SOC_DAPM_POST_PMD | SND_SOC_DAPM_POST_PMU |
				SND_SOC_DAPM_PRE_PMD),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route cs35l35_audio_map[] = अणु
	अणु"VPMON ADC", शून्य, "VP"पूर्ण,
	अणु"VBSTMON ADC", शून्य, "VBST"पूर्ण,
	अणु"IMON ADC", शून्य, "ISENSE"पूर्ण,
	अणु"VMON ADC", शून्य, "VSENSE"पूर्ण,
	अणु"SDOUT", शून्य, "IMON ADC"पूर्ण,
	अणु"SDOUT", शून्य, "VMON ADC"पूर्ण,
	अणु"SDOUT", शून्य, "VBSTMON ADC"पूर्ण,
	अणु"SDOUT", शून्य, "VPMON ADC"पूर्ण,
	अणु"AMP Capture", शून्य, "SDOUT"पूर्ण,

	अणु"SDIN", शून्य, "AMP Playback"पूर्ण,
	अणु"CLASS H", शून्य, "SDIN"पूर्ण,
	अणु"Main AMP", शून्य, "CLASS H"पूर्ण,
	अणु"SPK", शून्य, "Main AMP"पूर्ण,
पूर्ण;

अटल पूर्णांक cs35l35_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा cs35l35_निजी *cs35l35 = snd_soc_component_get_drvdata(component);

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		regmap_update_bits(cs35l35->regmap, CS35L35_CLK_CTL1,
				    CS35L35_MS_MASK, 1 << CS35L35_MS_SHIFT);
		cs35l35->slave_mode = false;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		regmap_update_bits(cs35l35->regmap, CS35L35_CLK_CTL1,
				    CS35L35_MS_MASK, 0 << CS35L35_MS_SHIFT);
		cs35l35->slave_mode = true;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		cs35l35->i2s_mode = true;
		cs35l35->pdm_mode = false;
		अवरोध;
	हाल SND_SOC_DAIFMT_PDM:
		cs35l35->pdm_mode = true;
		cs35l35->i2s_mode = false;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा cs35l35_sysclk_config अणु
	पूर्णांक sysclk;
	पूर्णांक srate;
	u8 clk_cfg;
पूर्ण;

अटल काष्ठा cs35l35_sysclk_config cs35l35_clk_ctl[] = अणु

	/* SYSCLK, Sample Rate, Serial Port Cfg */
	अणु5644800, 44100, 0x00पूर्ण,
	अणु5644800, 88200, 0x40पूर्ण,
	अणु6144000, 48000, 0x10पूर्ण,
	अणु6144000, 96000, 0x50पूर्ण,
	अणु11289600, 44100, 0x01पूर्ण,
	अणु11289600, 88200, 0x41पूर्ण,
	अणु11289600, 176400, 0x81पूर्ण,
	अणु12000000, 44100, 0x03पूर्ण,
	अणु12000000, 48000, 0x13पूर्ण,
	अणु12000000, 88200, 0x43पूर्ण,
	अणु12000000, 96000, 0x53पूर्ण,
	अणु12000000, 176400, 0x83पूर्ण,
	अणु12000000, 192000, 0x93पूर्ण,
	अणु12288000, 48000, 0x11पूर्ण,
	अणु12288000, 96000, 0x51पूर्ण,
	अणु12288000, 192000, 0x91पूर्ण,
	अणु13000000, 44100, 0x07पूर्ण,
	अणु13000000, 48000, 0x17पूर्ण,
	अणु13000000, 88200, 0x47पूर्ण,
	अणु13000000, 96000, 0x57पूर्ण,
	अणु13000000, 176400, 0x87पूर्ण,
	अणु13000000, 192000, 0x97पूर्ण,
	अणु22579200, 44100, 0x02पूर्ण,
	अणु22579200, 88200, 0x42पूर्ण,
	अणु22579200, 176400, 0x82पूर्ण,
	अणु24000000, 44100, 0x0Bपूर्ण,
	अणु24000000, 48000, 0x1Bपूर्ण,
	अणु24000000, 88200, 0x4Bपूर्ण,
	अणु24000000, 96000, 0x5Bपूर्ण,
	अणु24000000, 176400, 0x8Bपूर्ण,
	अणु24000000, 192000, 0x9Bपूर्ण,
	अणु24576000, 48000, 0x12पूर्ण,
	अणु24576000, 96000, 0x52पूर्ण,
	अणु24576000, 192000, 0x92पूर्ण,
	अणु26000000, 44100, 0x0Fपूर्ण,
	अणु26000000, 48000, 0x1Fपूर्ण,
	अणु26000000, 88200, 0x4Fपूर्ण,
	अणु26000000, 96000, 0x5Fपूर्ण,
	अणु26000000, 176400, 0x8Fपूर्ण,
	अणु26000000, 192000, 0x9Fपूर्ण,
पूर्ण;

अटल पूर्णांक cs35l35_get_clk_config(पूर्णांक sysclk, पूर्णांक srate)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(cs35l35_clk_ctl); i++) अणु
		अगर (cs35l35_clk_ctl[i].sysclk == sysclk &&
			cs35l35_clk_ctl[i].srate == srate)
			वापस cs35l35_clk_ctl[i].clk_cfg;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक cs35l35_hw_params(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *params,
				 काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा cs35l35_निजी *cs35l35 = snd_soc_component_get_drvdata(component);
	काष्ठा classh_cfg *classh = &cs35l35->pdata.classh_algo;
	पूर्णांक srate = params_rate(params);
	पूर्णांक ret = 0;
	u8 sp_sclks;
	पूर्णांक audin_क्रमmat;
	पूर्णांक errata_chk;

	पूर्णांक clk_ctl = cs35l35_get_clk_config(cs35l35->sysclk, srate);

	अगर (clk_ctl < 0) अणु
		dev_err(component->dev, "Invalid CLK:Rate %d:%d\n",
			cs35l35->sysclk, srate);
		वापस -EINVAL;
	पूर्ण

	ret = regmap_update_bits(cs35l35->regmap, CS35L35_CLK_CTL2,
			  CS35L35_CLK_CTL2_MASK, clk_ctl);
	अगर (ret != 0) अणु
		dev_err(component->dev, "Failed to set port config %d\n", ret);
		वापस ret;
	पूर्ण

	/*
	 * Rev A0 Errata
	 * When configured क्रम the weak-drive detection path (CH_WKFET_DIS = 0)
	 * the Class H algorithm करोes not enable weak-drive operation क्रम
	 * nonzero values of CH_WKFET_DELAY अगर SP_RATE = 01 or 10
	 */
	errata_chk = clk_ctl & CS35L35_SP_RATE_MASK;

	अगर (classh->classh_wk_fet_disable == 0x00 &&
		(errata_chk == 0x01 || errata_chk == 0x03)) अणु
		ret = regmap_update_bits(cs35l35->regmap,
					CS35L35_CLASS_H_FET_DRIVE_CTL,
					CS35L35_CH_WKFET_DEL_MASK,
					0 << CS35L35_CH_WKFET_DEL_SHIFT);
		अगर (ret != 0) अणु
			dev_err(component->dev, "Failed to set fet config %d\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण

	/*
	 * You can pull more Monitor data from the SDOUT pin than going to SDIN
	 * Just make sure your SCLK is fast enough to fill the frame
	 */
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		चयन (params_width(params)) अणु
		हाल 8:
			audin_क्रमmat = CS35L35_SDIN_DEPTH_8;
			अवरोध;
		हाल 16:
			audin_क्रमmat = CS35L35_SDIN_DEPTH_16;
			अवरोध;
		हाल 24:
			audin_क्रमmat = CS35L35_SDIN_DEPTH_24;
			अवरोध;
		शेष:
			dev_err(component->dev, "Unsupported Width %d\n",
				params_width(params));
			वापस -EINVAL;
		पूर्ण
		regmap_update_bits(cs35l35->regmap,
				CS35L35_AUDIN_DEPTH_CTL,
				CS35L35_AUDIN_DEPTH_MASK,
				audin_क्रमmat <<
				CS35L35_AUDIN_DEPTH_SHIFT);
		अगर (cs35l35->pdata.stereo) अणु
			regmap_update_bits(cs35l35->regmap,
					CS35L35_AUDIN_DEPTH_CTL,
					CS35L35_ADVIN_DEPTH_MASK,
					audin_क्रमmat <<
					CS35L35_ADVIN_DEPTH_SHIFT);
		पूर्ण
	पूर्ण

	अगर (cs35l35->i2s_mode) अणु
		/* We have to take the SCLK to derive num sclks
		 * to configure the CLOCK_CTL3 रेजिस्टर correctly
		 */
		अगर ((cs35l35->sclk / srate) % 4) अणु
			dev_err(component->dev, "Unsupported sclk/fs ratio %d:%d\n",
					cs35l35->sclk, srate);
			वापस -EINVAL;
		पूर्ण
		sp_sclks = ((cs35l35->sclk / srate) / 4) - 1;

		/* Only certain ratios are supported in I2S Slave Mode */
		अगर (cs35l35->slave_mode) अणु
			चयन (sp_sclks) अणु
			हाल CS35L35_SP_SCLKS_32FS:
			हाल CS35L35_SP_SCLKS_48FS:
			हाल CS35L35_SP_SCLKS_64FS:
				अवरोध;
			शेष:
				dev_err(component->dev, "ratio not supported\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Only certain ratios supported in I2S MASTER Mode */
			चयन (sp_sclks) अणु
			हाल CS35L35_SP_SCLKS_32FS:
			हाल CS35L35_SP_SCLKS_64FS:
				अवरोध;
			शेष:
				dev_err(component->dev, "ratio not supported\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण
		ret = regmap_update_bits(cs35l35->regmap,
					CS35L35_CLK_CTL3,
					CS35L35_SP_SCLKS_MASK, sp_sclks <<
					CS35L35_SP_SCLKS_SHIFT);
		अगर (ret != 0) अणु
			dev_err(component->dev, "Failed to set fsclk %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर अचिन्हित पूर्णांक cs35l35_src_rates[] = अणु
	44100, 48000, 88200, 96000, 176400, 192000
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list cs35l35_स्थिरraपूर्णांकs = अणु
	.count  = ARRAY_SIZE(cs35l35_src_rates),
	.list   = cs35l35_src_rates,
पूर्ण;

अटल पूर्णांक cs35l35_pcm_startup(काष्ठा snd_pcm_substream *substream,
			       काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा cs35l35_निजी *cs35l35 = snd_soc_component_get_drvdata(component);

	अगर (!substream->runसमय)
		वापस 0;

	snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
				SNDRV_PCM_HW_PARAM_RATE, &cs35l35_स्थिरraपूर्णांकs);

	regmap_update_bits(cs35l35->regmap, CS35L35_AMP_INP_DRV_CTL,
					CS35L35_PDM_MODE_MASK,
					0 << CS35L35_PDM_MODE_SHIFT);

	वापस 0;
पूर्ण

अटल स्थिर अचिन्हित पूर्णांक cs35l35_pdm_rates[] = अणु
	44100, 48000, 88200, 96000
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list cs35l35_pdm_स्थिरraपूर्णांकs = अणु
	.count  = ARRAY_SIZE(cs35l35_pdm_rates),
	.list   = cs35l35_pdm_rates,
पूर्ण;

अटल पूर्णांक cs35l35_pdm_startup(काष्ठा snd_pcm_substream *substream,
			       काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा cs35l35_निजी *cs35l35 = snd_soc_component_get_drvdata(component);

	अगर (!substream->runसमय)
		वापस 0;

	snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
				SNDRV_PCM_HW_PARAM_RATE,
				&cs35l35_pdm_स्थिरraपूर्णांकs);

	regmap_update_bits(cs35l35->regmap, CS35L35_AMP_INP_DRV_CTL,
					CS35L35_PDM_MODE_MASK,
					1 << CS35L35_PDM_MODE_SHIFT);

	वापस 0;
पूर्ण

अटल पूर्णांक cs35l35_dai_set_sysclk(काष्ठा snd_soc_dai *dai,
				पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा cs35l35_निजी *cs35l35 = snd_soc_component_get_drvdata(component);

	/* Need the SCLK Frequency regardless of sysclk source क्रम I2S */
	cs35l35->sclk = freq;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops cs35l35_ops = अणु
	.startup = cs35l35_pcm_startup,
	.set_fmt = cs35l35_set_dai_fmt,
	.hw_params = cs35l35_hw_params,
	.set_sysclk = cs35l35_dai_set_sysclk,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops cs35l35_pdm_ops = अणु
	.startup = cs35l35_pdm_startup,
	.set_fmt = cs35l35_set_dai_fmt,
	.hw_params = cs35l35_hw_params,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver cs35l35_dai[] = अणु
	अणु
		.name = "cs35l35-pcm",
		.id = 0,
		.playback = अणु
			.stream_name = "AMP Playback",
			.channels_min = 1,
			.channels_max = 8,
			.rates = SNDRV_PCM_RATE_KNOT,
			.क्रमmats = CS35L35_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "AMP Capture",
			.channels_min = 1,
			.channels_max = 8,
			.rates = SNDRV_PCM_RATE_KNOT,
			.क्रमmats = CS35L35_FORMATS,
		पूर्ण,
		.ops = &cs35l35_ops,
		.symmetric_rate = 1,
	पूर्ण,
	अणु
		.name = "cs35l35-pdm",
		.id = 1,
		.playback = अणु
			.stream_name = "PDM Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_KNOT,
			.क्रमmats = CS35L35_FORMATS,
		पूर्ण,
		.ops = &cs35l35_pdm_ops,
	पूर्ण,
पूर्ण;

अटल पूर्णांक cs35l35_component_set_sysclk(काष्ठा snd_soc_component *component,
				पूर्णांक clk_id, पूर्णांक source, अचिन्हित पूर्णांक freq,
				पूर्णांक dir)
अणु
	काष्ठा cs35l35_निजी *cs35l35 = snd_soc_component_get_drvdata(component);
	पूर्णांक clksrc;
	पूर्णांक ret = 0;

	चयन (clk_id) अणु
	हाल 0:
		clksrc = CS35L35_CLK_SOURCE_MCLK;
		अवरोध;
	हाल 1:
		clksrc = CS35L35_CLK_SOURCE_SCLK;
		अवरोध;
	हाल 2:
		clksrc = CS35L35_CLK_SOURCE_PDM;
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid CLK Source\n");
		वापस -EINVAL;
	पूर्ण

	चयन (freq) अणु
	हाल 5644800:
	हाल 6144000:
	हाल 11289600:
	हाल 12000000:
	हाल 12288000:
	हाल 13000000:
	हाल 22579200:
	हाल 24000000:
	हाल 24576000:
	हाल 26000000:
		cs35l35->sysclk = freq;
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid CLK Frequency Input : %d\n", freq);
		वापस -EINVAL;
	पूर्ण

	ret = regmap_update_bits(cs35l35->regmap, CS35L35_CLK_CTL1,
				CS35L35_CLK_SOURCE_MASK,
				clksrc << CS35L35_CLK_SOURCE_SHIFT);
	अगर (ret != 0) अणु
		dev_err(component->dev, "Failed to set sysclk %d\n", ret);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक cs35l35_boost_inductor(काष्ठा cs35l35_निजी *cs35l35,
				  पूर्णांक inductor)
अणु
	काष्ठा regmap *regmap = cs35l35->regmap;
	अचिन्हित पूर्णांक bst_ipk = 0;

	/*
	 * Digital Boost Converter Configuration क्रम feedback,
	 * ramping, चयनing frequency, and estimation block seeding.
	 */

	regmap_update_bits(regmap, CS35L35_BST_CONV_SW_FREQ,
			   CS35L35_BST_CONV_SWFREQ_MASK, 0x00);

	regmap_पढ़ो(regmap, CS35L35_BST_PEAK_I, &bst_ipk);
	bst_ipk &= CS35L35_BST_IPK_MASK;

	चयन (inductor) अणु
	हाल 1000: /* 1 uH */
		regmap_ग_लिखो(regmap, CS35L35_BST_CONV_COEF_1, 0x24);
		regmap_ग_लिखो(regmap, CS35L35_BST_CONV_COEF_2, 0x24);
		regmap_update_bits(regmap, CS35L35_BST_CONV_SW_FREQ,
				   CS35L35_BST_CONV_LBST_MASK, 0x00);

		अगर (bst_ipk < 0x04)
			regmap_ग_लिखो(regmap, CS35L35_BST_CONV_SLOPE_COMP, 0x1B);
		अन्यथा
			regmap_ग_लिखो(regmap, CS35L35_BST_CONV_SLOPE_COMP, 0x4E);
		अवरोध;
	हाल 1200: /* 1.2 uH */
		regmap_ग_लिखो(regmap, CS35L35_BST_CONV_COEF_1, 0x20);
		regmap_ग_लिखो(regmap, CS35L35_BST_CONV_COEF_2, 0x20);
		regmap_update_bits(regmap, CS35L35_BST_CONV_SW_FREQ,
				   CS35L35_BST_CONV_LBST_MASK, 0x01);

		अगर (bst_ipk < 0x04)
			regmap_ग_लिखो(regmap, CS35L35_BST_CONV_SLOPE_COMP, 0x1B);
		अन्यथा
			regmap_ग_लिखो(regmap, CS35L35_BST_CONV_SLOPE_COMP, 0x47);
		अवरोध;
	हाल 1500: /* 1.5uH */
		regmap_ग_लिखो(regmap, CS35L35_BST_CONV_COEF_1, 0x20);
		regmap_ग_लिखो(regmap, CS35L35_BST_CONV_COEF_2, 0x20);
		regmap_update_bits(regmap, CS35L35_BST_CONV_SW_FREQ,
				   CS35L35_BST_CONV_LBST_MASK, 0x02);

		अगर (bst_ipk < 0x04)
			regmap_ग_लिखो(regmap, CS35L35_BST_CONV_SLOPE_COMP, 0x1B);
		अन्यथा
			regmap_ग_लिखो(regmap, CS35L35_BST_CONV_SLOPE_COMP, 0x3C);
		अवरोध;
	हाल 2200: /* 2.2uH */
		regmap_ग_लिखो(regmap, CS35L35_BST_CONV_COEF_1, 0x19);
		regmap_ग_लिखो(regmap, CS35L35_BST_CONV_COEF_2, 0x25);
		regmap_update_bits(regmap, CS35L35_BST_CONV_SW_FREQ,
				   CS35L35_BST_CONV_LBST_MASK, 0x03);

		अगर (bst_ipk < 0x04)
			regmap_ग_लिखो(regmap, CS35L35_BST_CONV_SLOPE_COMP, 0x1B);
		अन्यथा
			regmap_ग_लिखो(regmap, CS35L35_BST_CONV_SLOPE_COMP, 0x23);
		अवरोध;
	शेष:
		dev_err(cs35l35->dev, "Invalid Inductor Value %d uH\n",
			inductor);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cs35l35_component_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा cs35l35_निजी *cs35l35 = snd_soc_component_get_drvdata(component);
	काष्ठा classh_cfg *classh = &cs35l35->pdata.classh_algo;
	काष्ठा monitor_cfg *monitor_config = &cs35l35->pdata.mon_cfg;
	पूर्णांक ret;

	/* Set Platक्रमm Data */
	अगर (cs35l35->pdata.bst_vctl)
		regmap_update_bits(cs35l35->regmap, CS35L35_BST_CVTR_V_CTL,
				CS35L35_BST_CTL_MASK,
				cs35l35->pdata.bst_vctl);

	अगर (cs35l35->pdata.bst_ipk)
		regmap_update_bits(cs35l35->regmap, CS35L35_BST_PEAK_I,
				CS35L35_BST_IPK_MASK,
				cs35l35->pdata.bst_ipk <<
				CS35L35_BST_IPK_SHIFT);

	ret = cs35l35_boost_inductor(cs35l35, cs35l35->pdata.boost_ind);
	अगर (ret)
		वापस ret;

	अगर (cs35l35->pdata.gain_zc)
		regmap_update_bits(cs35l35->regmap, CS35L35_PROTECT_CTL,
				CS35L35_AMP_GAIN_ZC_MASK,
				cs35l35->pdata.gain_zc <<
				CS35L35_AMP_GAIN_ZC_SHIFT);

	अगर (cs35l35->pdata.aud_channel)
		regmap_update_bits(cs35l35->regmap,
				CS35L35_AUDIN_RXLOC_CTL,
				CS35L35_AUD_IN_LR_MASK,
				cs35l35->pdata.aud_channel <<
				CS35L35_AUD_IN_LR_SHIFT);

	अगर (cs35l35->pdata.stereo) अणु
		regmap_update_bits(cs35l35->regmap,
				CS35L35_ADVIN_RXLOC_CTL,
				CS35L35_ADV_IN_LR_MASK,
				cs35l35->pdata.adv_channel <<
				CS35L35_ADV_IN_LR_SHIFT);
		अगर (cs35l35->pdata.shared_bst)
			regmap_update_bits(cs35l35->regmap, CS35L35_CLASS_H_CTL,
					CS35L35_CH_STEREO_MASK,
					1 << CS35L35_CH_STEREO_SHIFT);
		ret = snd_soc_add_component_controls(component, cs35l35_adv_controls,
					ARRAY_SIZE(cs35l35_adv_controls));
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (cs35l35->pdata.sp_drv_str)
		regmap_update_bits(cs35l35->regmap, CS35L35_CLK_CTL1,
				CS35L35_SP_DRV_MASK,
				cs35l35->pdata.sp_drv_str <<
				CS35L35_SP_DRV_SHIFT);
	अगर (cs35l35->pdata.sp_drv_unused)
		regmap_update_bits(cs35l35->regmap, CS35L35_SP_FMT_CTL3,
				   CS35L35_SP_I2S_DRV_MASK,
				   cs35l35->pdata.sp_drv_unused <<
				   CS35L35_SP_I2S_DRV_SHIFT);

	अगर (classh->classh_algo_enable) अणु
		अगर (classh->classh_bst_override)
			regmap_update_bits(cs35l35->regmap,
					CS35L35_CLASS_H_CTL,
					CS35L35_CH_BST_OVR_MASK,
					classh->classh_bst_override <<
					CS35L35_CH_BST_OVR_SHIFT);
		अगर (classh->classh_bst_max_limit)
			regmap_update_bits(cs35l35->regmap,
					CS35L35_CLASS_H_CTL,
					CS35L35_CH_BST_LIM_MASK,
					classh->classh_bst_max_limit <<
					CS35L35_CH_BST_LIM_SHIFT);
		अगर (classh->classh_mem_depth)
			regmap_update_bits(cs35l35->regmap,
					CS35L35_CLASS_H_CTL,
					CS35L35_CH_MEM_DEPTH_MASK,
					classh->classh_mem_depth <<
					CS35L35_CH_MEM_DEPTH_SHIFT);
		अगर (classh->classh_headroom)
			regmap_update_bits(cs35l35->regmap,
					CS35L35_CLASS_H_HEADRM_CTL,
					CS35L35_CH_HDRM_CTL_MASK,
					classh->classh_headroom <<
					CS35L35_CH_HDRM_CTL_SHIFT);
		अगर (classh->classh_release_rate)
			regmap_update_bits(cs35l35->regmap,
					CS35L35_CLASS_H_RELEASE_RATE,
					CS35L35_CH_REL_RATE_MASK,
					classh->classh_release_rate <<
					CS35L35_CH_REL_RATE_SHIFT);
		अगर (classh->classh_wk_fet_disable)
			regmap_update_bits(cs35l35->regmap,
					CS35L35_CLASS_H_FET_DRIVE_CTL,
					CS35L35_CH_WKFET_DIS_MASK,
					classh->classh_wk_fet_disable <<
					CS35L35_CH_WKFET_DIS_SHIFT);
		अगर (classh->classh_wk_fet_delay)
			regmap_update_bits(cs35l35->regmap,
					CS35L35_CLASS_H_FET_DRIVE_CTL,
					CS35L35_CH_WKFET_DEL_MASK,
					classh->classh_wk_fet_delay <<
					CS35L35_CH_WKFET_DEL_SHIFT);
		अगर (classh->classh_wk_fet_thld)
			regmap_update_bits(cs35l35->regmap,
					CS35L35_CLASS_H_FET_DRIVE_CTL,
					CS35L35_CH_WKFET_THLD_MASK,
					classh->classh_wk_fet_thld <<
					CS35L35_CH_WKFET_THLD_SHIFT);
		अगर (classh->classh_vpch_स्वतः)
			regmap_update_bits(cs35l35->regmap,
					CS35L35_CLASS_H_VP_CTL,
					CS35L35_CH_VP_AUTO_MASK,
					classh->classh_vpch_स्वतः <<
					CS35L35_CH_VP_AUTO_SHIFT);
		अगर (classh->classh_vpch_rate)
			regmap_update_bits(cs35l35->regmap,
					CS35L35_CLASS_H_VP_CTL,
					CS35L35_CH_VP_RATE_MASK,
					classh->classh_vpch_rate <<
					CS35L35_CH_VP_RATE_SHIFT);
		अगर (classh->classh_vpch_man)
			regmap_update_bits(cs35l35->regmap,
					CS35L35_CLASS_H_VP_CTL,
					CS35L35_CH_VP_MAN_MASK,
					classh->classh_vpch_man <<
					CS35L35_CH_VP_MAN_SHIFT);
	पूर्ण

	अगर (monitor_config->is_present) अणु
		अगर (monitor_config->vmon_specs) अणु
			regmap_update_bits(cs35l35->regmap,
					CS35L35_SPKMON_DEPTH_CTL,
					CS35L35_VMON_DEPTH_MASK,
					monitor_config->vmon_dpth <<
					CS35L35_VMON_DEPTH_SHIFT);
			regmap_update_bits(cs35l35->regmap,
					CS35L35_VMON_TXLOC_CTL,
					CS35L35_MON_TXLOC_MASK,
					monitor_config->vmon_loc <<
					CS35L35_MON_TXLOC_SHIFT);
			regmap_update_bits(cs35l35->regmap,
					CS35L35_VMON_TXLOC_CTL,
					CS35L35_MON_FRM_MASK,
					monitor_config->vmon_frm <<
					CS35L35_MON_FRM_SHIFT);
		पूर्ण
		अगर (monitor_config->imon_specs) अणु
			regmap_update_bits(cs35l35->regmap,
					CS35L35_SPKMON_DEPTH_CTL,
					CS35L35_IMON_DEPTH_MASK,
					monitor_config->imon_dpth <<
					CS35L35_IMON_DEPTH_SHIFT);
			regmap_update_bits(cs35l35->regmap,
					CS35L35_IMON_TXLOC_CTL,
					CS35L35_MON_TXLOC_MASK,
					monitor_config->imon_loc <<
					CS35L35_MON_TXLOC_SHIFT);
			regmap_update_bits(cs35l35->regmap,
					CS35L35_IMON_TXLOC_CTL,
					CS35L35_MON_FRM_MASK,
					monitor_config->imon_frm <<
					CS35L35_MON_FRM_SHIFT);
			regmap_update_bits(cs35l35->regmap,
					CS35L35_IMON_SCALE_CTL,
					CS35L35_IMON_SCALE_MASK,
					monitor_config->imon_scale <<
					CS35L35_IMON_SCALE_SHIFT);
		पूर्ण
		अगर (monitor_config->vpmon_specs) अणु
			regmap_update_bits(cs35l35->regmap,
					CS35L35_SUPMON_DEPTH_CTL,
					CS35L35_VPMON_DEPTH_MASK,
					monitor_config->vpmon_dpth <<
					CS35L35_VPMON_DEPTH_SHIFT);
			regmap_update_bits(cs35l35->regmap,
					CS35L35_VPMON_TXLOC_CTL,
					CS35L35_MON_TXLOC_MASK,
					monitor_config->vpmon_loc <<
					CS35L35_MON_TXLOC_SHIFT);
			regmap_update_bits(cs35l35->regmap,
					CS35L35_VPMON_TXLOC_CTL,
					CS35L35_MON_FRM_MASK,
					monitor_config->vpmon_frm <<
					CS35L35_MON_FRM_SHIFT);
		पूर्ण
		अगर (monitor_config->vbsपंचांगon_specs) अणु
			regmap_update_bits(cs35l35->regmap,
					CS35L35_SUPMON_DEPTH_CTL,
					CS35L35_VBSTMON_DEPTH_MASK,
					monitor_config->vpmon_dpth <<
					CS35L35_VBSTMON_DEPTH_SHIFT);
			regmap_update_bits(cs35l35->regmap,
					CS35L35_VBSTMON_TXLOC_CTL,
					CS35L35_MON_TXLOC_MASK,
					monitor_config->vbsपंचांगon_loc <<
					CS35L35_MON_TXLOC_SHIFT);
			regmap_update_bits(cs35l35->regmap,
					CS35L35_VBSTMON_TXLOC_CTL,
					CS35L35_MON_FRM_MASK,
					monitor_config->vbsपंचांगon_frm <<
					CS35L35_MON_FRM_SHIFT);
		पूर्ण
		अगर (monitor_config->vpbrstat_specs) अणु
			regmap_update_bits(cs35l35->regmap,
					CS35L35_SUPMON_DEPTH_CTL,
					CS35L35_VPBRSTAT_DEPTH_MASK,
					monitor_config->vpbrstat_dpth <<
					CS35L35_VPBRSTAT_DEPTH_SHIFT);
			regmap_update_bits(cs35l35->regmap,
					CS35L35_VPBR_STATUS_TXLOC_CTL,
					CS35L35_MON_TXLOC_MASK,
					monitor_config->vpbrstat_loc <<
					CS35L35_MON_TXLOC_SHIFT);
			regmap_update_bits(cs35l35->regmap,
					CS35L35_VPBR_STATUS_TXLOC_CTL,
					CS35L35_MON_FRM_MASK,
					monitor_config->vpbrstat_frm <<
					CS35L35_MON_FRM_SHIFT);
		पूर्ण
		अगर (monitor_config->zerofill_specs) अणु
			regmap_update_bits(cs35l35->regmap,
					CS35L35_SUPMON_DEPTH_CTL,
					CS35L35_ZEROFILL_DEPTH_MASK,
					monitor_config->zerofill_dpth <<
					CS35L35_ZEROFILL_DEPTH_SHIFT);
			regmap_update_bits(cs35l35->regmap,
					CS35L35_ZERO_FILL_LOC_CTL,
					CS35L35_MON_TXLOC_MASK,
					monitor_config->zerofill_loc <<
					CS35L35_MON_TXLOC_SHIFT);
			regmap_update_bits(cs35l35->regmap,
					CS35L35_ZERO_FILL_LOC_CTL,
					CS35L35_MON_FRM_MASK,
					monitor_config->zerofill_frm <<
					CS35L35_MON_FRM_SHIFT);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_cs35l35 = अणु
	.probe			= cs35l35_component_probe,
	.set_sysclk		= cs35l35_component_set_sysclk,
	.dapm_widमाला_लो		= cs35l35_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(cs35l35_dapm_widमाला_लो),
	.dapm_routes		= cs35l35_audio_map,
	.num_dapm_routes	= ARRAY_SIZE(cs35l35_audio_map),
	.controls		= cs35l35_aud_controls,
	.num_controls		= ARRAY_SIZE(cs35l35_aud_controls),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल काष्ठा regmap_config cs35l35_regmap = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = CS35L35_MAX_REGISTER,
	.reg_शेषs = cs35l35_reg,
	.num_reg_शेषs = ARRAY_SIZE(cs35l35_reg),
	.अस्थिर_reg = cs35l35_अस्थिर_रेजिस्टर,
	.पढ़ोable_reg = cs35l35_पढ़ोable_रेजिस्टर,
	.precious_reg = cs35l35_precious_रेजिस्टर,
	.cache_type = REGCACHE_RBTREE,
	.use_single_पढ़ो = true,
	.use_single_ग_लिखो = true,
पूर्ण;

अटल irqवापस_t cs35l35_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा cs35l35_निजी *cs35l35 = data;
	अचिन्हित पूर्णांक sticky1, sticky2, sticky3, sticky4;
	अचिन्हित पूर्णांक mask1, mask2, mask3, mask4, current1;

	/* ack the irq by पढ़ोing all status रेजिस्टरs */
	regmap_पढ़ो(cs35l35->regmap, CS35L35_INT_STATUS_4, &sticky4);
	regmap_पढ़ो(cs35l35->regmap, CS35L35_INT_STATUS_3, &sticky3);
	regmap_पढ़ो(cs35l35->regmap, CS35L35_INT_STATUS_2, &sticky2);
	regmap_पढ़ो(cs35l35->regmap, CS35L35_INT_STATUS_1, &sticky1);

	regmap_पढ़ो(cs35l35->regmap, CS35L35_INT_MASK_4, &mask4);
	regmap_पढ़ो(cs35l35->regmap, CS35L35_INT_MASK_3, &mask3);
	regmap_पढ़ो(cs35l35->regmap, CS35L35_INT_MASK_2, &mask2);
	regmap_पढ़ो(cs35l35->regmap, CS35L35_INT_MASK_1, &mask1);

	/* Check to see अगर unmasked bits are active */
	अगर (!(sticky1 & ~mask1) && !(sticky2 & ~mask2) && !(sticky3 & ~mask3)
			&& !(sticky4 & ~mask4))
		वापस IRQ_NONE;

	अगर (sticky2 & CS35L35_PDN_DONE)
		complete(&cs35l35->pdn_करोne);

	/* पढ़ो the current values */
	regmap_पढ़ो(cs35l35->regmap, CS35L35_INT_STATUS_1, &current1);

	/* handle the पूर्णांकerrupts */
	अगर (sticky1 & CS35L35_CAL_ERR) अणु
		dev_crit(cs35l35->dev, "Calibration Error\n");

		/* error is no दीर्घer निश्चितed; safe to reset */
		अगर (!(current1 & CS35L35_CAL_ERR)) अणु
			pr_debug("%s : Cal error release\n", __func__);
			regmap_update_bits(cs35l35->regmap,
					CS35L35_PROT_RELEASE_CTL,
					CS35L35_CAL_ERR_RLS, 0);
			regmap_update_bits(cs35l35->regmap,
					CS35L35_PROT_RELEASE_CTL,
					CS35L35_CAL_ERR_RLS,
					CS35L35_CAL_ERR_RLS);
			regmap_update_bits(cs35l35->regmap,
					CS35L35_PROT_RELEASE_CTL,
					CS35L35_CAL_ERR_RLS, 0);
		पूर्ण
	पूर्ण

	अगर (sticky1 & CS35L35_AMP_SHORT) अणु
		dev_crit(cs35l35->dev, "AMP Short Error\n");
		/* error is no दीर्घer निश्चितed; safe to reset */
		अगर (!(current1 & CS35L35_AMP_SHORT)) अणु
			dev_dbg(cs35l35->dev, "Amp short error release\n");
			regmap_update_bits(cs35l35->regmap,
					CS35L35_PROT_RELEASE_CTL,
					CS35L35_SHORT_RLS, 0);
			regmap_update_bits(cs35l35->regmap,
					CS35L35_PROT_RELEASE_CTL,
					CS35L35_SHORT_RLS,
					CS35L35_SHORT_RLS);
			regmap_update_bits(cs35l35->regmap,
					CS35L35_PROT_RELEASE_CTL,
					CS35L35_SHORT_RLS, 0);
		पूर्ण
	पूर्ण

	अगर (sticky1 & CS35L35_OTW) अणु
		dev_warn(cs35l35->dev, "Over temperature warning\n");

		/* error is no दीर्घer निश्चितed; safe to reset */
		अगर (!(current1 & CS35L35_OTW)) अणु
			dev_dbg(cs35l35->dev, "Over temperature warn release\n");
			regmap_update_bits(cs35l35->regmap,
					CS35L35_PROT_RELEASE_CTL,
					CS35L35_OTW_RLS, 0);
			regmap_update_bits(cs35l35->regmap,
					CS35L35_PROT_RELEASE_CTL,
					CS35L35_OTW_RLS,
					CS35L35_OTW_RLS);
			regmap_update_bits(cs35l35->regmap,
					CS35L35_PROT_RELEASE_CTL,
					CS35L35_OTW_RLS, 0);
		पूर्ण
	पूर्ण

	अगर (sticky1 & CS35L35_OTE) अणु
		dev_crit(cs35l35->dev, "Over temperature error\n");
		/* error is no दीर्घer निश्चितed; safe to reset */
		अगर (!(current1 & CS35L35_OTE)) अणु
			dev_dbg(cs35l35->dev, "Over temperature error release\n");
			regmap_update_bits(cs35l35->regmap,
					CS35L35_PROT_RELEASE_CTL,
					CS35L35_OTE_RLS, 0);
			regmap_update_bits(cs35l35->regmap,
					CS35L35_PROT_RELEASE_CTL,
					CS35L35_OTE_RLS,
					CS35L35_OTE_RLS);
			regmap_update_bits(cs35l35->regmap,
					CS35L35_PROT_RELEASE_CTL,
					CS35L35_OTE_RLS, 0);
		पूर्ण
	पूर्ण

	अगर (sticky3 & CS35L35_BST_HIGH) अणु
		dev_crit(cs35l35->dev, "VBST error: powering off!\n");
		regmap_update_bits(cs35l35->regmap, CS35L35_PWRCTL2,
			CS35L35_PDN_AMP, CS35L35_PDN_AMP);
		regmap_update_bits(cs35l35->regmap, CS35L35_PWRCTL1,
			CS35L35_PDN_ALL, CS35L35_PDN_ALL);
	पूर्ण

	अगर (sticky3 & CS35L35_LBST_SHORT) अणु
		dev_crit(cs35l35->dev, "LBST error: powering off!\n");
		regmap_update_bits(cs35l35->regmap, CS35L35_PWRCTL2,
			CS35L35_PDN_AMP, CS35L35_PDN_AMP);
		regmap_update_bits(cs35l35->regmap, CS35L35_PWRCTL1,
			CS35L35_PDN_ALL, CS35L35_PDN_ALL);
	पूर्ण

	अगर (sticky2 & CS35L35_VPBR_ERR)
		dev_dbg(cs35l35->dev, "Error: Reactive Brownout\n");

	अगर (sticky4 & CS35L35_VMON_OVFL)
		dev_dbg(cs35l35->dev, "Error: VMON overflow\n");

	अगर (sticky4 & CS35L35_IMON_OVFL)
		dev_dbg(cs35l35->dev, "Error: IMON overflow\n");

	वापस IRQ_HANDLED;
पूर्ण


अटल पूर्णांक cs35l35_handle_of_data(काष्ठा i2c_client *i2c_client,
				काष्ठा cs35l35_platक्रमm_data *pdata)
अणु
	काष्ठा device_node *np = i2c_client->dev.of_node;
	काष्ठा device_node *classh, *संकेत_क्रमmat;
	काष्ठा classh_cfg *classh_config = &pdata->classh_algo;
	काष्ठा monitor_cfg *monitor_config = &pdata->mon_cfg;
	अचिन्हित पूर्णांक val32 = 0;
	u8 monitor_array[4];
	स्थिर पूर्णांक imon_array_size = ARRAY_SIZE(monitor_array);
	स्थिर पूर्णांक mon_array_size = imon_array_size - 1;
	पूर्णांक ret = 0;

	अगर (!np)
		वापस 0;

	pdata->bst_pdn_fet_on = of_property_पढ़ो_bool(np,
					"cirrus,boost-pdn-fet-on");

	ret = of_property_पढ़ो_u32(np, "cirrus,boost-ctl-millivolt", &val32);
	अगर (ret >= 0) अणु
		अगर (val32 < 2600 || val32 > 9000) अणु
			dev_err(&i2c_client->dev,
				"Invalid Boost Voltage %d mV\n", val32);
			वापस -EINVAL;
		पूर्ण
		pdata->bst_vctl = ((val32 - 2600) / 100) + 1;
	पूर्ण

	ret = of_property_पढ़ो_u32(np, "cirrus,boost-peak-milliamp", &val32);
	अगर (ret >= 0) अणु
		अगर (val32 < 1680 || val32 > 4480) अणु
			dev_err(&i2c_client->dev,
				"Invalid Boost Peak Current %u mA\n", val32);
			वापस -EINVAL;
		पूर्ण

		pdata->bst_ipk = ((val32 - 1680) / 110) | CS35L35_VALID_PDATA;
	पूर्ण

	ret = of_property_पढ़ो_u32(np, "cirrus,boost-ind-nanohenry", &val32);
	अगर (ret >= 0) अणु
		pdata->boost_ind = val32;
	पूर्ण अन्यथा अणु
		dev_err(&i2c_client->dev, "Inductor not specified.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (of_property_पढ़ो_u32(np, "cirrus,sp-drv-strength", &val32) >= 0)
		pdata->sp_drv_str = val32;
	अगर (of_property_पढ़ो_u32(np, "cirrus,sp-drv-unused", &val32) >= 0)
		pdata->sp_drv_unused = val32 | CS35L35_VALID_PDATA;

	pdata->stereo = of_property_पढ़ो_bool(np, "cirrus,stereo-config");

	अगर (pdata->stereo) अणु
		ret = of_property_पढ़ो_u32(np, "cirrus,audio-channel", &val32);
		अगर (ret >= 0)
			pdata->aud_channel = val32;

		ret = of_property_पढ़ो_u32(np, "cirrus,advisory-channel",
					   &val32);
		अगर (ret >= 0)
			pdata->adv_channel = val32;

		pdata->shared_bst = of_property_पढ़ो_bool(np,
						"cirrus,shared-boost");
	पूर्ण

	pdata->ext_bst = of_property_पढ़ो_bool(np, "cirrus,external-boost");

	pdata->gain_zc = of_property_पढ़ो_bool(np, "cirrus,amp-gain-zc");

	classh = of_get_child_by_name(np, "cirrus,classh-internal-algo");
	classh_config->classh_algo_enable = classh ? true : false;

	अगर (classh_config->classh_algo_enable) अणु
		classh_config->classh_bst_override =
			of_property_पढ़ो_bool(np, "cirrus,classh-bst-overide");

		ret = of_property_पढ़ो_u32(classh,
					   "cirrus,classh-bst-max-limit",
					   &val32);
		अगर (ret >= 0) अणु
			val32 |= CS35L35_VALID_PDATA;
			classh_config->classh_bst_max_limit = val32;
		पूर्ण

		ret = of_property_पढ़ो_u32(classh,
					   "cirrus,classh-bst-max-limit",
					   &val32);
		अगर (ret >= 0) अणु
			val32 |= CS35L35_VALID_PDATA;
			classh_config->classh_bst_max_limit = val32;
		पूर्ण

		ret = of_property_पढ़ो_u32(classh, "cirrus,classh-mem-depth",
					   &val32);
		अगर (ret >= 0) अणु
			val32 |= CS35L35_VALID_PDATA;
			classh_config->classh_mem_depth = val32;
		पूर्ण

		ret = of_property_पढ़ो_u32(classh, "cirrus,classh-release-rate",
					   &val32);
		अगर (ret >= 0)
			classh_config->classh_release_rate = val32;

		ret = of_property_पढ़ो_u32(classh, "cirrus,classh-headroom",
					   &val32);
		अगर (ret >= 0) अणु
			val32 |= CS35L35_VALID_PDATA;
			classh_config->classh_headroom = val32;
		पूर्ण

		ret = of_property_पढ़ो_u32(classh,
					   "cirrus,classh-wk-fet-disable",
					   &val32);
		अगर (ret >= 0)
			classh_config->classh_wk_fet_disable = val32;

		ret = of_property_पढ़ो_u32(classh, "cirrus,classh-wk-fet-delay",
					   &val32);
		अगर (ret >= 0) अणु
			val32 |= CS35L35_VALID_PDATA;
			classh_config->classh_wk_fet_delay = val32;
		पूर्ण

		ret = of_property_पढ़ो_u32(classh, "cirrus,classh-wk-fet-thld",
					   &val32);
		अगर (ret >= 0)
			classh_config->classh_wk_fet_thld = val32;

		ret = of_property_पढ़ो_u32(classh, "cirrus,classh-vpch-auto",
					   &val32);
		अगर (ret >= 0) अणु
			val32 |= CS35L35_VALID_PDATA;
			classh_config->classh_vpch_स्वतः = val32;
		पूर्ण

		ret = of_property_पढ़ो_u32(classh, "cirrus,classh-vpch-rate",
					   &val32);
		अगर (ret >= 0) अणु
			val32 |= CS35L35_VALID_PDATA;
			classh_config->classh_vpch_rate = val32;
		पूर्ण

		ret = of_property_पढ़ो_u32(classh, "cirrus,classh-vpch-man",
					   &val32);
		अगर (ret >= 0)
			classh_config->classh_vpch_man = val32;
	पूर्ण
	of_node_put(classh);

	/* frame depth location */
	संकेत_क्रमmat = of_get_child_by_name(np, "cirrus,monitor-signal-format");
	monitor_config->is_present = संकेत_क्रमmat ? true : false;
	अगर (monitor_config->is_present) अणु
		ret = of_property_पढ़ो_u8_array(संकेत_क्रमmat, "cirrus,imon",
						monitor_array, imon_array_size);
		अगर (!ret) अणु
			monitor_config->imon_specs = true;
			monitor_config->imon_dpth = monitor_array[0];
			monitor_config->imon_loc = monitor_array[1];
			monitor_config->imon_frm = monitor_array[2];
			monitor_config->imon_scale = monitor_array[3];
		पूर्ण
		ret = of_property_पढ़ो_u8_array(संकेत_क्रमmat, "cirrus,vmon",
						monitor_array, mon_array_size);
		अगर (!ret) अणु
			monitor_config->vmon_specs = true;
			monitor_config->vmon_dpth = monitor_array[0];
			monitor_config->vmon_loc = monitor_array[1];
			monitor_config->vmon_frm = monitor_array[2];
		पूर्ण
		ret = of_property_पढ़ो_u8_array(संकेत_क्रमmat, "cirrus,vpmon",
						monitor_array, mon_array_size);
		अगर (!ret) अणु
			monitor_config->vpmon_specs = true;
			monitor_config->vpmon_dpth = monitor_array[0];
			monitor_config->vpmon_loc = monitor_array[1];
			monitor_config->vpmon_frm = monitor_array[2];
		पूर्ण
		ret = of_property_पढ़ो_u8_array(संकेत_क्रमmat, "cirrus,vbstmon",
						monitor_array, mon_array_size);
		अगर (!ret) अणु
			monitor_config->vbsपंचांगon_specs = true;
			monitor_config->vbsपंचांगon_dpth = monitor_array[0];
			monitor_config->vbsपंचांगon_loc = monitor_array[1];
			monitor_config->vbsपंचांगon_frm = monitor_array[2];
		पूर्ण
		ret = of_property_पढ़ो_u8_array(संकेत_क्रमmat, "cirrus,vpbrstat",
						monitor_array, mon_array_size);
		अगर (!ret) अणु
			monitor_config->vpbrstat_specs = true;
			monitor_config->vpbrstat_dpth = monitor_array[0];
			monitor_config->vpbrstat_loc = monitor_array[1];
			monitor_config->vpbrstat_frm = monitor_array[2];
		पूर्ण
		ret = of_property_पढ़ो_u8_array(संकेत_क्रमmat, "cirrus,zerofill",
						monitor_array, mon_array_size);
		अगर (!ret) अणु
			monitor_config->zerofill_specs = true;
			monitor_config->zerofill_dpth = monitor_array[0];
			monitor_config->zerofill_loc = monitor_array[1];
			monitor_config->zerofill_frm = monitor_array[2];
		पूर्ण
	पूर्ण
	of_node_put(संकेत_क्रमmat);

	वापस 0;
पूर्ण

/* Errata Rev A0 */
अटल स्थिर काष्ठा reg_sequence cs35l35_errata_patch[] = अणु

	अणु 0x7F, 0x99 पूर्ण,
	अणु 0x00, 0x99 पूर्ण,
	अणु 0x52, 0x22 पूर्ण,
	अणु 0x04, 0x14 पूर्ण,
	अणु 0x6D, 0x44 पूर्ण,
	अणु 0x24, 0x10 पूर्ण,
	अणु 0x58, 0xC4 पूर्ण,
	अणु 0x00, 0x98 पूर्ण,
	अणु 0x18, 0x08 पूर्ण,
	अणु 0x00, 0x00 पूर्ण,
	अणु 0x7F, 0x00 पूर्ण,
पूर्ण;

अटल पूर्णांक cs35l35_i2c_probe(काष्ठा i2c_client *i2c_client,
			      स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा cs35l35_निजी *cs35l35;
	काष्ठा device *dev = &i2c_client->dev;
	काष्ठा cs35l35_platक्रमm_data *pdata = dev_get_platdata(dev);
	पूर्णांक i;
	पूर्णांक ret;
	अचिन्हित पूर्णांक devid = 0;
	अचिन्हित पूर्णांक reg;

	cs35l35 = devm_kzalloc(dev, माप(काष्ठा cs35l35_निजी), GFP_KERNEL);
	अगर (!cs35l35)
		वापस -ENOMEM;

	cs35l35->dev = dev;

	i2c_set_clientdata(i2c_client, cs35l35);
	cs35l35->regmap = devm_regmap_init_i2c(i2c_client, &cs35l35_regmap);
	अगर (IS_ERR(cs35l35->regmap)) अणु
		ret = PTR_ERR(cs35l35->regmap);
		dev_err(dev, "regmap_init() failed: %d\n", ret);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(cs35l35_supplies); i++)
		cs35l35->supplies[i].supply = cs35l35_supplies[i];

	cs35l35->num_supplies = ARRAY_SIZE(cs35l35_supplies);

	ret = devm_regulator_bulk_get(dev, cs35l35->num_supplies,
				      cs35l35->supplies);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to request core supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (pdata) अणु
		cs35l35->pdata = *pdata;
	पूर्ण अन्यथा अणु
		pdata = devm_kzalloc(dev, माप(काष्ठा cs35l35_platक्रमm_data),
				     GFP_KERNEL);
		अगर (!pdata)
			वापस -ENOMEM;
		अगर (i2c_client->dev.of_node) अणु
			ret = cs35l35_handle_of_data(i2c_client, pdata);
			अगर (ret != 0)
				वापस ret;

		पूर्ण
		cs35l35->pdata = *pdata;
	पूर्ण

	ret = regulator_bulk_enable(cs35l35->num_supplies,
					cs35l35->supplies);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to enable core supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	/* वापसing शून्य can be valid अगर in stereo mode */
	cs35l35->reset_gpio = devm_gpiod_get_optional(dev, "reset",
						      GPIOD_OUT_LOW);
	अगर (IS_ERR(cs35l35->reset_gpio)) अणु
		ret = PTR_ERR(cs35l35->reset_gpio);
		cs35l35->reset_gpio = शून्य;
		अगर (ret == -EBUSY) अणु
			dev_info(dev,
				 "Reset line busy, assuming shared reset\n");
		पूर्ण अन्यथा अणु
			dev_err(dev, "Failed to get reset GPIO: %d\n", ret);
			जाओ err;
		पूर्ण
	पूर्ण

	cs35l35_reset(cs35l35);

	init_completion(&cs35l35->pdn_करोne);

	ret = devm_request_thपढ़ोed_irq(dev, i2c_client->irq, शून्य, cs35l35_irq,
					IRQF_ONESHOT | IRQF_TRIGGER_LOW |
					IRQF_SHARED, "cs35l35", cs35l35);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to request IRQ: %d\n", ret);
		जाओ err;
	पूर्ण
	/* initialize codec */
	ret = regmap_पढ़ो(cs35l35->regmap, CS35L35_DEVID_AB, &reg);

	devid = (reg & 0xFF) << 12;
	ret = regmap_पढ़ो(cs35l35->regmap, CS35L35_DEVID_CD, &reg);
	devid |= (reg & 0xFF) << 4;
	ret = regmap_पढ़ो(cs35l35->regmap, CS35L35_DEVID_E, &reg);
	devid |= (reg & 0xF0) >> 4;

	अगर (devid != CS35L35_CHIP_ID) अणु
		dev_err(dev, "CS35L35 Device ID (%X). Expected ID %X\n",
			devid, CS35L35_CHIP_ID);
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	ret = regmap_पढ़ो(cs35l35->regmap, CS35L35_REV_ID, &reg);
	अगर (ret < 0) अणु
		dev_err(dev, "Get Revision ID failed: %d\n", ret);
		जाओ err;
	पूर्ण

	ret = regmap_रेजिस्टर_patch(cs35l35->regmap, cs35l35_errata_patch,
				    ARRAY_SIZE(cs35l35_errata_patch));
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to apply errata patch: %d\n", ret);
		जाओ err;
	पूर्ण

	dev_info(dev, "Cirrus Logic CS35L35 (%x), Revision: %02X\n",
		 devid, reg & 0xFF);

	/* Set the INT Masks क्रम critical errors */
	regmap_ग_लिखो(cs35l35->regmap, CS35L35_INT_MASK_1,
				CS35L35_INT1_CRIT_MASK);
	regmap_ग_लिखो(cs35l35->regmap, CS35L35_INT_MASK_2,
				CS35L35_INT2_CRIT_MASK);
	regmap_ग_लिखो(cs35l35->regmap, CS35L35_INT_MASK_3,
				CS35L35_INT3_CRIT_MASK);
	regmap_ग_लिखो(cs35l35->regmap, CS35L35_INT_MASK_4,
				CS35L35_INT4_CRIT_MASK);

	regmap_update_bits(cs35l35->regmap, CS35L35_PWRCTL2,
			CS35L35_PWR2_PDN_MASK,
			CS35L35_PWR2_PDN_MASK);

	अगर (cs35l35->pdata.bst_pdn_fet_on)
		regmap_update_bits(cs35l35->regmap, CS35L35_PWRCTL2,
					CS35L35_PDN_BST_MASK,
					1 << CS35L35_PDN_BST_FETON_SHIFT);
	अन्यथा
		regmap_update_bits(cs35l35->regmap, CS35L35_PWRCTL2,
					CS35L35_PDN_BST_MASK,
					1 << CS35L35_PDN_BST_FETOFF_SHIFT);

	regmap_update_bits(cs35l35->regmap, CS35L35_PWRCTL3,
			CS35L35_PWR3_PDN_MASK,
			CS35L35_PWR3_PDN_MASK);

	regmap_update_bits(cs35l35->regmap, CS35L35_PROTECT_CTL,
		CS35L35_AMP_MUTE_MASK, 1 << CS35L35_AMP_MUTE_SHIFT);

	ret = devm_snd_soc_रेजिस्टर_component(dev, &soc_component_dev_cs35l35,
					cs35l35_dai, ARRAY_SIZE(cs35l35_dai));
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to register component: %d\n", ret);
		जाओ err;
	पूर्ण

	वापस 0;

err:
	regulator_bulk_disable(cs35l35->num_supplies,
			       cs35l35->supplies);
	gpiod_set_value_cansleep(cs35l35->reset_gpio, 0);

	वापस ret;
पूर्ण

अटल पूर्णांक cs35l35_i2c_हटाओ(काष्ठा i2c_client *i2c_client)
अणु
	काष्ठा cs35l35_निजी *cs35l35 = i2c_get_clientdata(i2c_client);

	regulator_bulk_disable(cs35l35->num_supplies, cs35l35->supplies);
	gpiod_set_value_cansleep(cs35l35->reset_gpio, 0);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id cs35l35_of_match[] = अणु
	अणु.compatible = "cirrus,cs35l35"पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, cs35l35_of_match);

अटल स्थिर काष्ठा i2c_device_id cs35l35_id[] = अणु
	अणु"cs35l35", 0पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, cs35l35_id);

अटल काष्ठा i2c_driver cs35l35_i2c_driver = अणु
	.driver = अणु
		.name = "cs35l35",
		.of_match_table = cs35l35_of_match,
	पूर्ण,
	.id_table = cs35l35_id,
	.probe = cs35l35_i2c_probe,
	.हटाओ = cs35l35_i2c_हटाओ,
पूर्ण;

module_i2c_driver(cs35l35_i2c_driver);

MODULE_DESCRIPTION("ASoC CS35L35 driver");
MODULE_AUTHOR("Brian Austin, Cirrus Logic Inc, <brian.austin@cirrus.com>");
MODULE_LICENSE("GPL");
