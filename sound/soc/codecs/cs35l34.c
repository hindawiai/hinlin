<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * cs35l34.c -- CS35l34 ALSA SoC audio driver
 *
 * Copyright 2016 Cirrus Logic, Inc.
 *
 * Author: Paul Handrigan <Paul.Handrigan@cirrus.com>
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
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/of_device.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/of_irq.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>
#समावेश <sound/cs35l34.h>

#समावेश "cs35l34.h"

#घोषणा PDN_DONE_ATTEMPTS 10
#घोषणा CS35L34_START_DELAY 50

काष्ठा  cs35l34_निजी अणु
	काष्ठा snd_soc_component *component;
	काष्ठा cs35l34_platक्रमm_data pdata;
	काष्ठा regmap *regmap;
	काष्ठा regulator_bulk_data core_supplies[2];
	पूर्णांक num_core_supplies;
	पूर्णांक mclk_पूर्णांक;
	bool tdm_mode;
	काष्ठा gpio_desc *reset_gpio;	/* Active-low reset GPIO */
पूर्ण;

अटल स्थिर काष्ठा reg_शेष cs35l34_reg[] = अणु
	अणुCS35L34_PWRCTL1, 0x01पूर्ण,
	अणुCS35L34_PWRCTL2, 0x19पूर्ण,
	अणुCS35L34_PWRCTL3, 0x01पूर्ण,
	अणुCS35L34_ADSP_CLK_CTL, 0x08पूर्ण,
	अणुCS35L34_MCLK_CTL, 0x11पूर्ण,
	अणुCS35L34_AMP_INP_DRV_CTL, 0x01पूर्ण,
	अणुCS35L34_AMP_DIG_VOL_CTL, 0x12पूर्ण,
	अणुCS35L34_AMP_DIG_VOL, 0x00पूर्ण,
	अणुCS35L34_AMP_ANLG_GAIN_CTL, 0x0Fपूर्ण,
	अणुCS35L34_PROTECT_CTL, 0x06पूर्ण,
	अणुCS35L34_AMP_KEEP_ALIVE_CTL, 0x04पूर्ण,
	अणुCS35L34_BST_CVTR_V_CTL, 0x00पूर्ण,
	अणुCS35L34_BST_PEAK_I, 0x10पूर्ण,
	अणुCS35L34_BST_RAMP_CTL, 0x87पूर्ण,
	अणुCS35L34_BST_CONV_COEF_1, 0x24पूर्ण,
	अणुCS35L34_BST_CONV_COEF_2, 0x24पूर्ण,
	अणुCS35L34_BST_CONV_SLOPE_COMP, 0x4Eपूर्ण,
	अणुCS35L34_BST_CONV_SW_FREQ, 0x08पूर्ण,
	अणुCS35L34_CLASS_H_CTL, 0x0Dपूर्ण,
	अणुCS35L34_CLASS_H_HEADRM_CTL, 0x0Dपूर्ण,
	अणुCS35L34_CLASS_H_RELEASE_RATE, 0x08पूर्ण,
	अणुCS35L34_CLASS_H_FET_DRIVE_CTL, 0x41पूर्ण,
	अणुCS35L34_CLASS_H_STATUS, 0x05पूर्ण,
	अणुCS35L34_VPBR_CTL, 0x0Aपूर्ण,
	अणुCS35L34_VPBR_VOL_CTL, 0x90पूर्ण,
	अणुCS35L34_VPBR_TIMING_CTL, 0x6Aपूर्ण,
	अणुCS35L34_PRED_MAX_ATTEN_SPK_LOAD, 0x95पूर्ण,
	अणुCS35L34_PRED_BROWNOUT_THRESH, 0x1Cपूर्ण,
	अणुCS35L34_PRED_BROWNOUT_VOL_CTL, 0x00पूर्ण,
	अणुCS35L34_PRED_BROWNOUT_RATE_CTL, 0x10पूर्ण,
	अणुCS35L34_PRED_WAIT_CTL, 0x10पूर्ण,
	अणुCS35L34_PRED_ZVP_INIT_IMP_CTL, 0x08पूर्ण,
	अणुCS35L34_PRED_MAN_SAFE_VPI_CTL, 0x80पूर्ण,
	अणुCS35L34_VPBR_ATTEN_STATUS, 0x00पूर्ण,
	अणुCS35L34_PRED_BRWNOUT_ATT_STATUS, 0x00पूर्ण,
	अणुCS35L34_SPKR_MON_CTL, 0xC6पूर्ण,
	अणुCS35L34_ADSP_I2S_CTL, 0x00पूर्ण,
	अणुCS35L34_ADSP_TDM_CTL, 0x00पूर्ण,
	अणुCS35L34_TDM_TX_CTL_1_VMON, 0x00पूर्ण,
	अणुCS35L34_TDM_TX_CTL_2_IMON, 0x04पूर्ण,
	अणुCS35L34_TDM_TX_CTL_3_VPMON, 0x03पूर्ण,
	अणुCS35L34_TDM_TX_CTL_4_VBSTMON, 0x07पूर्ण,
	अणुCS35L34_TDM_TX_CTL_5_FLAG1, 0x08पूर्ण,
	अणुCS35L34_TDM_TX_CTL_6_FLAG2, 0x09पूर्ण,
	अणुCS35L34_TDM_TX_SLOT_EN_1, 0x00पूर्ण,
	अणुCS35L34_TDM_TX_SLOT_EN_2, 0x00पूर्ण,
	अणुCS35L34_TDM_TX_SLOT_EN_3, 0x00पूर्ण,
	अणुCS35L34_TDM_TX_SLOT_EN_4, 0x00पूर्ण,
	अणुCS35L34_TDM_RX_CTL_1_AUDIN, 0x40पूर्ण,
	अणुCS35L34_TDM_RX_CTL_3_ALIVE, 0x04पूर्ण,
	अणुCS35L34_MULT_DEV_SYNCH1, 0x00पूर्ण,
	अणुCS35L34_MULT_DEV_SYNCH2, 0x80पूर्ण,
	अणुCS35L34_PROT_RELEASE_CTL, 0x00पूर्ण,
	अणुCS35L34_DIAG_MODE_REG_LOCK, 0x00पूर्ण,
	अणुCS35L34_DIAG_MODE_CTL_1, 0x00पूर्ण,
	अणुCS35L34_DIAG_MODE_CTL_2, 0x00पूर्ण,
	अणुCS35L34_INT_MASK_1, 0xFFपूर्ण,
	अणुCS35L34_INT_MASK_2, 0xFFपूर्ण,
	अणुCS35L34_INT_MASK_3, 0xFFपूर्ण,
	अणुCS35L34_INT_MASK_4, 0xFFपूर्ण,
	अणुCS35L34_INT_STATUS_1, 0x30पूर्ण,
	अणुCS35L34_INT_STATUS_2, 0x05पूर्ण,
	अणुCS35L34_INT_STATUS_3, 0x00पूर्ण,
	अणुCS35L34_INT_STATUS_4, 0x00पूर्ण,
	अणुCS35L34_OTP_TRIM_STATUS, 0x00पूर्ण,
पूर्ण;

अटल bool cs35l34_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल CS35L34_DEVID_AB:
	हाल CS35L34_DEVID_CD:
	हाल CS35L34_DEVID_E:
	हाल CS35L34_FAB_ID:
	हाल CS35L34_REV_ID:
	हाल CS35L34_INT_STATUS_1:
	हाल CS35L34_INT_STATUS_2:
	हाल CS35L34_INT_STATUS_3:
	हाल CS35L34_INT_STATUS_4:
	हाल CS35L34_CLASS_H_STATUS:
	हाल CS35L34_VPBR_ATTEN_STATUS:
	हाल CS35L34_OTP_TRIM_STATUS:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool cs35l34_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल	CS35L34_DEVID_AB:
	हाल	CS35L34_DEVID_CD:
	हाल	CS35L34_DEVID_E:
	हाल	CS35L34_FAB_ID:
	हाल	CS35L34_REV_ID:
	हाल	CS35L34_PWRCTL1:
	हाल	CS35L34_PWRCTL2:
	हाल	CS35L34_PWRCTL3:
	हाल	CS35L34_ADSP_CLK_CTL:
	हाल	CS35L34_MCLK_CTL:
	हाल	CS35L34_AMP_INP_DRV_CTL:
	हाल	CS35L34_AMP_DIG_VOL_CTL:
	हाल	CS35L34_AMP_DIG_VOL:
	हाल	CS35L34_AMP_ANLG_GAIN_CTL:
	हाल	CS35L34_PROTECT_CTL:
	हाल	CS35L34_AMP_KEEP_ALIVE_CTL:
	हाल	CS35L34_BST_CVTR_V_CTL:
	हाल	CS35L34_BST_PEAK_I:
	हाल	CS35L34_BST_RAMP_CTL:
	हाल	CS35L34_BST_CONV_COEF_1:
	हाल	CS35L34_BST_CONV_COEF_2:
	हाल	CS35L34_BST_CONV_SLOPE_COMP:
	हाल	CS35L34_BST_CONV_SW_FREQ:
	हाल	CS35L34_CLASS_H_CTL:
	हाल	CS35L34_CLASS_H_HEADRM_CTL:
	हाल	CS35L34_CLASS_H_RELEASE_RATE:
	हाल	CS35L34_CLASS_H_FET_DRIVE_CTL:
	हाल	CS35L34_CLASS_H_STATUS:
	हाल	CS35L34_VPBR_CTL:
	हाल	CS35L34_VPBR_VOL_CTL:
	हाल	CS35L34_VPBR_TIMING_CTL:
	हाल	CS35L34_PRED_MAX_ATTEN_SPK_LOAD:
	हाल	CS35L34_PRED_BROWNOUT_THRESH:
	हाल	CS35L34_PRED_BROWNOUT_VOL_CTL:
	हाल	CS35L34_PRED_BROWNOUT_RATE_CTL:
	हाल	CS35L34_PRED_WAIT_CTL:
	हाल	CS35L34_PRED_ZVP_INIT_IMP_CTL:
	हाल	CS35L34_PRED_MAN_SAFE_VPI_CTL:
	हाल	CS35L34_VPBR_ATTEN_STATUS:
	हाल	CS35L34_PRED_BRWNOUT_ATT_STATUS:
	हाल	CS35L34_SPKR_MON_CTL:
	हाल	CS35L34_ADSP_I2S_CTL:
	हाल	CS35L34_ADSP_TDM_CTL:
	हाल	CS35L34_TDM_TX_CTL_1_VMON:
	हाल	CS35L34_TDM_TX_CTL_2_IMON:
	हाल	CS35L34_TDM_TX_CTL_3_VPMON:
	हाल	CS35L34_TDM_TX_CTL_4_VBSTMON:
	हाल	CS35L34_TDM_TX_CTL_5_FLAG1:
	हाल	CS35L34_TDM_TX_CTL_6_FLAG2:
	हाल	CS35L34_TDM_TX_SLOT_EN_1:
	हाल	CS35L34_TDM_TX_SLOT_EN_2:
	हाल	CS35L34_TDM_TX_SLOT_EN_3:
	हाल	CS35L34_TDM_TX_SLOT_EN_4:
	हाल	CS35L34_TDM_RX_CTL_1_AUDIN:
	हाल	CS35L34_TDM_RX_CTL_3_ALIVE:
	हाल	CS35L34_MULT_DEV_SYNCH1:
	हाल	CS35L34_MULT_DEV_SYNCH2:
	हाल	CS35L34_PROT_RELEASE_CTL:
	हाल	CS35L34_DIAG_MODE_REG_LOCK:
	हाल	CS35L34_DIAG_MODE_CTL_1:
	हाल	CS35L34_DIAG_MODE_CTL_2:
	हाल	CS35L34_INT_MASK_1:
	हाल	CS35L34_INT_MASK_2:
	हाल	CS35L34_INT_MASK_3:
	हाल	CS35L34_INT_MASK_4:
	हाल	CS35L34_INT_STATUS_1:
	हाल	CS35L34_INT_STATUS_2:
	हाल	CS35L34_INT_STATUS_3:
	हाल	CS35L34_INT_STATUS_4:
	हाल	CS35L34_OTP_TRIM_STATUS:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool cs35l34_precious_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल CS35L34_INT_STATUS_1:
	हाल CS35L34_INT_STATUS_2:
	हाल CS35L34_INT_STATUS_3:
	हाल CS35L34_INT_STATUS_4:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक cs35l34_sdin_event(काष्ठा snd_soc_dapm_widget *w,
		काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा cs35l34_निजी *priv = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		अगर (priv->tdm_mode)
			regmap_update_bits(priv->regmap, CS35L34_PWRCTL3,
						CS35L34_PDN_TDM, 0x00);

		ret = regmap_update_bits(priv->regmap, CS35L34_PWRCTL1,
						CS35L34_PDN_ALL, 0);
		अगर (ret < 0) अणु
			dev_err(component->dev, "Cannot set Power bits %d\n", ret);
			वापस ret;
		पूर्ण
		usleep_range(5000, 5100);
	अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		अगर (priv->tdm_mode) अणु
			regmap_update_bits(priv->regmap, CS35L34_PWRCTL3,
					CS35L34_PDN_TDM, CS35L34_PDN_TDM);
		पूर्ण
		ret = regmap_update_bits(priv->regmap, CS35L34_PWRCTL1,
					CS35L34_PDN_ALL, CS35L34_PDN_ALL);
	अवरोध;
	शेष:
		pr_err("Invalid event = 0x%x\n", event);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cs35l34_set_tdm_slot(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक tx_mask,
				अचिन्हित पूर्णांक rx_mask, पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा cs35l34_निजी *priv = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक reg, bit_pos;
	पूर्णांक slot, slot_num;

	अगर (slot_width != 8)
		वापस -EINVAL;

	priv->tdm_mode = true;
	/* scan rx_mask क्रम aud slot */
	slot = ffs(rx_mask) - 1;
	अगर (slot >= 0)
		snd_soc_component_update_bits(component, CS35L34_TDM_RX_CTL_1_AUDIN,
					CS35L34_X_LOC, slot);

	/* scan tx_mask: vmon(2 slots); imon (2 slots); vpmon (1 slot)
	 * vbsपंचांगon (1 slot)
	 */
	slot = ffs(tx_mask) - 1;
	slot_num = 0;

	/* disable vpmon/vbsपंचांगon: enable later अगर set in tx_mask */
	snd_soc_component_update_bits(component, CS35L34_TDM_TX_CTL_3_VPMON,
				CS35L34_X_STATE | CS35L34_X_LOC,
				CS35L34_X_STATE | CS35L34_X_LOC);
	snd_soc_component_update_bits(component, CS35L34_TDM_TX_CTL_4_VBSTMON,
				CS35L34_X_STATE | CS35L34_X_LOC,
				CS35L34_X_STATE | CS35L34_X_LOC);

	/* disconnect अणुvp,vbstपूर्ण_mon routes: eanble later अगर set in tx_mask*/
	जबतक (slot >= 0) अणु
		/* configure VMON_TX_LOC */
		अगर (slot_num == 0)
			snd_soc_component_update_bits(component, CS35L34_TDM_TX_CTL_1_VMON,
					CS35L34_X_STATE | CS35L34_X_LOC, slot);

		/* configure IMON_TX_LOC */
		अगर (slot_num == 4) अणु
			snd_soc_component_update_bits(component, CS35L34_TDM_TX_CTL_2_IMON,
					CS35L34_X_STATE | CS35L34_X_LOC, slot);
		पूर्ण
		/* configure VPMON_TX_LOC */
		अगर (slot_num == 3) अणु
			snd_soc_component_update_bits(component, CS35L34_TDM_TX_CTL_3_VPMON,
					CS35L34_X_STATE | CS35L34_X_LOC, slot);
		पूर्ण
		/* configure VBSTMON_TX_LOC */
		अगर (slot_num == 7) अणु
			snd_soc_component_update_bits(component,
				CS35L34_TDM_TX_CTL_4_VBSTMON,
				CS35L34_X_STATE | CS35L34_X_LOC, slot);
		पूर्ण

		/* Enable the relevant tx slot */
		reg = CS35L34_TDM_TX_SLOT_EN_4 - (slot/8);
		bit_pos = slot - ((slot / 8) * (8));
		snd_soc_component_update_bits(component, reg,
			1 << bit_pos, 1 << bit_pos);

		tx_mask &= ~(1 << slot);
		slot = ffs(tx_mask) - 1;
		slot_num++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cs35l34_मुख्य_amp_event(काष्ठा snd_soc_dapm_widget *w,
		काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा cs35l34_निजी *priv = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		regmap_update_bits(priv->regmap, CS35L34_BST_CVTR_V_CTL,
				CS35L34_BST_CVTL_MASK, priv->pdata.boost_vtge);
		usleep_range(5000, 5100);
		regmap_update_bits(priv->regmap, CS35L34_PROTECT_CTL,
						CS35L34_MUTE, 0);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		regmap_update_bits(priv->regmap, CS35L34_BST_CVTR_V_CTL,
			CS35L34_BST_CVTL_MASK, 0);
		regmap_update_bits(priv->regmap, CS35L34_PROTECT_CTL,
			CS35L34_MUTE, CS35L34_MUTE);
		usleep_range(5000, 5100);
		अवरोध;
	शेष:
		pr_err("Invalid event = 0x%x\n", event);
	पूर्ण
	वापस 0;
पूर्ण

अटल DECLARE_TLV_DB_SCALE(dig_vol_tlv, -10200, 50, 0);

अटल DECLARE_TLV_DB_SCALE(amp_gain_tlv, 300, 100, 0);


अटल स्थिर काष्ठा snd_kcontrol_new cs35l34_snd_controls[] = अणु
	SOC_SINGLE_SX_TLV("Digital Volume", CS35L34_AMP_DIG_VOL,
		      0, 0x34, 0xE4, dig_vol_tlv),
	SOC_SINGLE_TLV("Amp Gain Volume", CS35L34_AMP_ANLG_GAIN_CTL,
		      0, 0xF, 0, amp_gain_tlv),
पूर्ण;


अटल पूर्णांक cs35l34_mclk_event(काष्ठा snd_soc_dapm_widget *w,
		काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा cs35l34_निजी *priv = snd_soc_component_get_drvdata(component);
	पूर्णांक ret, i;
	अचिन्हित पूर्णांक reg;

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMD:
		ret = regmap_पढ़ो(priv->regmap, CS35L34_AMP_DIG_VOL_CTL,
			&reg);
		अगर (ret != 0) अणु
			pr_err("%s regmap read failure %d\n", __func__, ret);
			वापस ret;
		पूर्ण
		अगर (reg & CS35L34_AMP_DIGSFT)
			msleep(40);
		अन्यथा
			usleep_range(2000, 2100);

		क्रम (i = 0; i < PDN_DONE_ATTEMPTS; i++) अणु
			ret = regmap_पढ़ो(priv->regmap, CS35L34_INT_STATUS_2,
				&reg);
			अगर (ret != 0) अणु
				pr_err("%s regmap read failure %d\n",
					__func__, ret);
				वापस ret;
			पूर्ण
			अगर (reg & CS35L34_PDN_DONE)
				अवरोध;

			usleep_range(5000, 5100);
		पूर्ण
		अगर (i == PDN_DONE_ATTEMPTS)
			pr_err("%s Device did not power down properly\n",
				__func__);
		अवरोध;
	शेष:
		pr_err("Invalid event = 0x%x\n", event);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget cs35l34_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_AIF_IN_E("SDIN", शून्य, 0, CS35L34_PWRCTL3,
					1, 1, cs35l34_sdin_event,
					SND_SOC_DAPM_PRE_PMU |
					SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_AIF_OUT("SDOUT", शून्य, 0, CS35L34_PWRCTL3, 2, 1),

	SND_SOC_DAPM_SUPPLY("EXTCLK", CS35L34_PWRCTL3, 7, 1,
		cs35l34_mclk_event, SND_SOC_DAPM_PRE_PMD),

	SND_SOC_DAPM_OUTPUT("SPK"),

	SND_SOC_DAPM_INPUT("VP"),
	SND_SOC_DAPM_INPUT("VPST"),
	SND_SOC_DAPM_INPUT("ISENSE"),
	SND_SOC_DAPM_INPUT("VSENSE"),

	SND_SOC_DAPM_ADC("VMON ADC", शून्य, CS35L34_PWRCTL2, 7, 1),
	SND_SOC_DAPM_ADC("IMON ADC", शून्य, CS35L34_PWRCTL2, 6, 1),
	SND_SOC_DAPM_ADC("VPMON ADC", शून्य, CS35L34_PWRCTL3, 3, 1),
	SND_SOC_DAPM_ADC("VBSTMON ADC", शून्य, CS35L34_PWRCTL3, 4, 1),
	SND_SOC_DAPM_ADC("CLASS H", शून्य, CS35L34_PWRCTL2, 5, 1),
	SND_SOC_DAPM_ADC("BOOST", शून्य, CS35L34_PWRCTL2, 2, 1),

	SND_SOC_DAPM_OUT_DRV_E("Main AMP", CS35L34_PWRCTL2, 0, 1, शून्य, 0,
		cs35l34_मुख्य_amp_event, SND_SOC_DAPM_POST_PMU |
			SND_SOC_DAPM_POST_PMD),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route cs35l34_audio_map[] = अणु
	अणु"SDIN", शून्य, "AMP Playback"पूर्ण,
	अणु"BOOST", शून्य, "SDIN"पूर्ण,
	अणु"CLASS H", शून्य, "BOOST"पूर्ण,
	अणु"Main AMP", शून्य, "CLASS H"पूर्ण,
	अणु"SPK", शून्य, "Main AMP"पूर्ण,

	अणु"VPMON ADC", शून्य, "CLASS H"पूर्ण,
	अणु"VBSTMON ADC", शून्य, "CLASS H"पूर्ण,
	अणु"SPK", शून्य, "VPMON ADC"पूर्ण,
	अणु"SPK", शून्य, "VBSTMON ADC"पूर्ण,

	अणु"IMON ADC", शून्य, "ISENSE"पूर्ण,
	अणु"VMON ADC", शून्य, "VSENSE"पूर्ण,
	अणु"SDOUT", शून्य, "IMON ADC"पूर्ण,
	अणु"SDOUT", शून्य, "VMON ADC"पूर्ण,
	अणु"AMP Capture", शून्य, "SDOUT"पूर्ण,

	अणु"SDIN", शून्य, "EXTCLK"पूर्ण,
	अणु"SDOUT", शून्य, "EXTCLK"पूर्ण,
पूर्ण;

काष्ठा cs35l34_mclk_भाग अणु
	पूर्णांक mclk;
	पूर्णांक srate;
	u8 adsp_rate;
पूर्ण;

अटल काष्ठा cs35l34_mclk_भाग cs35l34_mclk_coeffs[] = अणु

	/* MCLK, Sample Rate, adsp_rate */

	अणु5644800, 11025, 0x1पूर्ण,
	अणु5644800, 22050, 0x4पूर्ण,
	अणु5644800, 44100, 0x7पूर्ण,

	अणु6000000,  8000, 0x0पूर्ण,
	अणु6000000, 11025, 0x1पूर्ण,
	अणु6000000, 12000, 0x2पूर्ण,
	अणु6000000, 16000, 0x3पूर्ण,
	अणु6000000, 22050, 0x4पूर्ण,
	अणु6000000, 24000, 0x5पूर्ण,
	अणु6000000, 32000, 0x6पूर्ण,
	अणु6000000, 44100, 0x7पूर्ण,
	अणु6000000, 48000, 0x8पूर्ण,

	अणु6144000,  8000, 0x0पूर्ण,
	अणु6144000, 11025, 0x1पूर्ण,
	अणु6144000, 12000, 0x2पूर्ण,
	अणु6144000, 16000, 0x3पूर्ण,
	अणु6144000, 22050, 0x4पूर्ण,
	अणु6144000, 24000, 0x5पूर्ण,
	अणु6144000, 32000, 0x6पूर्ण,
	अणु6144000, 44100, 0x7पूर्ण,
	अणु6144000, 48000, 0x8पूर्ण,
पूर्ण;

अटल पूर्णांक cs35l34_get_mclk_coeff(पूर्णांक mclk, पूर्णांक srate)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(cs35l34_mclk_coeffs); i++) अणु
		अगर (cs35l34_mclk_coeffs[i].mclk == mclk &&
			cs35l34_mclk_coeffs[i].srate == srate)
			वापस i;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक cs35l34_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा cs35l34_निजी *priv = snd_soc_component_get_drvdata(component);

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		regmap_update_bits(priv->regmap, CS35L34_ADSP_CLK_CTL,
				    0x80, 0x80);
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		regmap_update_bits(priv->regmap, CS35L34_ADSP_CLK_CTL,
				    0x80, 0x00);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cs35l34_pcm_hw_params(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *params,
				 काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा cs35l34_निजी *priv = snd_soc_component_get_drvdata(component);
	पूर्णांक srate = params_rate(params);
	पूर्णांक ret;

	पूर्णांक coeff = cs35l34_get_mclk_coeff(priv->mclk_पूर्णांक, srate);

	अगर (coeff < 0) अणु
		dev_err(component->dev, "ERROR: Invalid mclk %d and/or srate %d\n",
			priv->mclk_पूर्णांक, srate);
		वापस coeff;
	पूर्ण

	ret = regmap_update_bits(priv->regmap, CS35L34_ADSP_CLK_CTL,
		CS35L34_ADSP_RATE, cs35l34_mclk_coeffs[coeff].adsp_rate);
	अगर (ret != 0)
		dev_err(component->dev, "Failed to set clock state %d\n", ret);

	वापस ret;
पूर्ण

अटल स्थिर अचिन्हित पूर्णांक cs35l34_src_rates[] = अणु
	8000, 11025, 12000, 16000, 22050, 24000, 32000, 44100, 48000
पूर्ण;


अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list cs35l34_स्थिरraपूर्णांकs = अणु
	.count  = ARRAY_SIZE(cs35l34_src_rates),
	.list   = cs35l34_src_rates,
पूर्ण;

अटल पूर्णांक cs35l34_pcm_startup(काष्ठा snd_pcm_substream *substream,
			       काष्ठा snd_soc_dai *dai)
अणु

	snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
				SNDRV_PCM_HW_PARAM_RATE, &cs35l34_स्थिरraपूर्णांकs);
	वापस 0;
पूर्ण


अटल पूर्णांक cs35l34_set_tristate(काष्ठा snd_soc_dai *dai, पूर्णांक tristate)
अणु

	काष्ठा snd_soc_component *component = dai->component;

	अगर (tristate)
		snd_soc_component_update_bits(component, CS35L34_PWRCTL3,
					CS35L34_PDN_SDOUT, CS35L34_PDN_SDOUT);
	अन्यथा
		snd_soc_component_update_bits(component, CS35L34_PWRCTL3,
					CS35L34_PDN_SDOUT, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक cs35l34_dai_set_sysclk(काष्ठा snd_soc_dai *dai,
				पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा cs35l34_निजी *cs35l34 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक value;

	चयन (freq) अणु
	हाल CS35L34_MCLK_5644:
		value = CS35L34_MCLK_RATE_5P6448;
		cs35l34->mclk_पूर्णांक = freq;
	अवरोध;
	हाल CS35L34_MCLK_6:
		value = CS35L34_MCLK_RATE_6P0000;
		cs35l34->mclk_पूर्णांक = freq;
	अवरोध;
	हाल CS35L34_MCLK_6144:
		value = CS35L34_MCLK_RATE_6P1440;
		cs35l34->mclk_पूर्णांक = freq;
	अवरोध;
	हाल CS35L34_MCLK_11289:
		value = CS35L34_MCLK_DIV | CS35L34_MCLK_RATE_5P6448;
		cs35l34->mclk_पूर्णांक = freq / 2;
	अवरोध;
	हाल CS35L34_MCLK_12:
		value = CS35L34_MCLK_DIV | CS35L34_MCLK_RATE_6P0000;
		cs35l34->mclk_पूर्णांक = freq / 2;
	अवरोध;
	हाल CS35L34_MCLK_12288:
		value = CS35L34_MCLK_DIV | CS35L34_MCLK_RATE_6P1440;
		cs35l34->mclk_पूर्णांक = freq / 2;
	अवरोध;
	शेष:
		dev_err(component->dev, "ERROR: Invalid Frequency %d\n", freq);
		cs35l34->mclk_पूर्णांक = 0;
		वापस -EINVAL;
	पूर्ण
	regmap_update_bits(cs35l34->regmap, CS35L34_MCLK_CTL,
			CS35L34_MCLK_DIV | CS35L34_MCLK_RATE_MASK, value);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops cs35l34_ops = अणु
	.startup = cs35l34_pcm_startup,
	.set_tristate = cs35l34_set_tristate,
	.set_fmt = cs35l34_set_dai_fmt,
	.hw_params = cs35l34_pcm_hw_params,
	.set_sysclk = cs35l34_dai_set_sysclk,
	.set_tdm_slot = cs35l34_set_tdm_slot,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver cs35l34_dai = अणु
		.name = "cs35l34",
		.id = 0,
		.playback = अणु
			.stream_name = "AMP Playback",
			.channels_min = 1,
			.channels_max = 8,
			.rates = CS35L34_RATES,
			.क्रमmats = CS35L34_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "AMP Capture",
			.channels_min = 1,
			.channels_max = 8,
			.rates = CS35L34_RATES,
			.क्रमmats = CS35L34_FORMATS,
		पूर्ण,
		.ops = &cs35l34_ops,
		.symmetric_rate = 1,
पूर्ण;

अटल पूर्णांक cs35l34_boost_inductor(काष्ठा cs35l34_निजी *cs35l34,
	अचिन्हित पूर्णांक inductor)
अणु
	काष्ठा snd_soc_component *component = cs35l34->component;

	चयन (inductor) अणु
	हाल 1000: /* 1 uH */
		regmap_ग_लिखो(cs35l34->regmap, CS35L34_BST_CONV_COEF_1, 0x24);
		regmap_ग_लिखो(cs35l34->regmap, CS35L34_BST_CONV_COEF_2, 0x24);
		regmap_ग_लिखो(cs35l34->regmap, CS35L34_BST_CONV_SLOPE_COMP,
			0x4E);
		regmap_ग_लिखो(cs35l34->regmap, CS35L34_BST_CONV_SW_FREQ, 0);
		अवरोध;
	हाल 1200: /* 1.2 uH */
		regmap_ग_लिखो(cs35l34->regmap, CS35L34_BST_CONV_COEF_1, 0x20);
		regmap_ग_लिखो(cs35l34->regmap, CS35L34_BST_CONV_COEF_2, 0x20);
		regmap_ग_लिखो(cs35l34->regmap, CS35L34_BST_CONV_SLOPE_COMP,
			0x47);
		regmap_ग_लिखो(cs35l34->regmap, CS35L34_BST_CONV_SW_FREQ, 1);
		अवरोध;
	हाल 1500: /* 1.5uH */
		regmap_ग_लिखो(cs35l34->regmap, CS35L34_BST_CONV_COEF_1, 0x20);
		regmap_ग_लिखो(cs35l34->regmap, CS35L34_BST_CONV_COEF_2, 0x20);
		regmap_ग_लिखो(cs35l34->regmap, CS35L34_BST_CONV_SLOPE_COMP,
			0x3C);
		regmap_ग_लिखो(cs35l34->regmap, CS35L34_BST_CONV_SW_FREQ, 2);
		अवरोध;
	हाल 2200: /* 2.2uH */
		regmap_ग_लिखो(cs35l34->regmap, CS35L34_BST_CONV_COEF_1, 0x19);
		regmap_ग_लिखो(cs35l34->regmap, CS35L34_BST_CONV_COEF_2, 0x25);
		regmap_ग_लिखो(cs35l34->regmap, CS35L34_BST_CONV_SLOPE_COMP,
			0x23);
		regmap_ग_लिखो(cs35l34->regmap, CS35L34_BST_CONV_SW_FREQ, 3);
		अवरोध;
	शेष:
		dev_err(component->dev, "%s Invalid Inductor Value %d uH\n",
			__func__, inductor);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cs35l34_probe(काष्ठा snd_soc_component *component)
अणु
	पूर्णांक ret = 0;
	काष्ठा cs35l34_निजी *cs35l34 = snd_soc_component_get_drvdata(component);

	pm_runसमय_get_sync(component->dev);

	/* Set over temperature warning attenuation to 6 dB */
	regmap_update_bits(cs35l34->regmap, CS35L34_PROTECT_CTL,
		 CS35L34_OTW_ATTN_MASK, 0x8);

	/* Set Power control रेजिस्टरs 2 and 3 to have everything
	 * घातered करोwn at initialization
	 */
	regmap_ग_लिखो(cs35l34->regmap, CS35L34_PWRCTL2, 0xFD);
	regmap_ग_लिखो(cs35l34->regmap, CS35L34_PWRCTL3, 0x1F);

	/* Set mute bit at startup */
	regmap_update_bits(cs35l34->regmap, CS35L34_PROTECT_CTL,
				CS35L34_MUTE, CS35L34_MUTE);

	/* Set Platक्रमm Data */
	अगर (cs35l34->pdata.boost_peak)
		regmap_update_bits(cs35l34->regmap, CS35L34_BST_PEAK_I,
				CS35L34_BST_PEAK_MASK,
				cs35l34->pdata.boost_peak);

	अगर (cs35l34->pdata.gain_zc_disable)
		regmap_update_bits(cs35l34->regmap, CS35L34_PROTECT_CTL,
			CS35L34_GAIN_ZC_MASK, 0);
	अन्यथा
		regmap_update_bits(cs35l34->regmap, CS35L34_PROTECT_CTL,
			CS35L34_GAIN_ZC_MASK, CS35L34_GAIN_ZC_MASK);

	अगर (cs35l34->pdata.aअगर_half_drv)
		regmap_update_bits(cs35l34->regmap, CS35L34_ADSP_CLK_CTL,
			CS35L34_ADSP_DRIVE, 0);

	अगर (cs35l34->pdata.digsft_disable)
		regmap_update_bits(cs35l34->regmap, CS35L34_AMP_DIG_VOL_CTL,
			CS35L34_AMP_DIGSFT, 0);

	अगर (cs35l34->pdata.amp_inv)
		regmap_update_bits(cs35l34->regmap, CS35L34_AMP_DIG_VOL_CTL,
			CS35L34_INV, CS35L34_INV);

	अगर (cs35l34->pdata.boost_ind)
		ret = cs35l34_boost_inductor(cs35l34, cs35l34->pdata.boost_ind);

	अगर (cs35l34->pdata.i2s_sdinloc)
		regmap_update_bits(cs35l34->regmap, CS35L34_ADSP_I2S_CTL,
			CS35L34_I2S_LOC_MASK,
			cs35l34->pdata.i2s_sdinloc << CS35L34_I2S_LOC_SHIFT);

	अगर (cs35l34->pdata.tdm_rising_edge)
		regmap_update_bits(cs35l34->regmap, CS35L34_ADSP_TDM_CTL,
			1, 1);

	pm_runसमय_put_sync(component->dev);

	वापस ret;
पूर्ण


अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_cs35l34 = अणु
	.probe			= cs35l34_probe,
	.dapm_widमाला_लो		= cs35l34_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(cs35l34_dapm_widमाला_लो),
	.dapm_routes		= cs35l34_audio_map,
	.num_dapm_routes	= ARRAY_SIZE(cs35l34_audio_map),
	.controls		= cs35l34_snd_controls,
	.num_controls		= ARRAY_SIZE(cs35l34_snd_controls),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल काष्ठा regmap_config cs35l34_regmap = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = CS35L34_MAX_REGISTER,
	.reg_शेषs = cs35l34_reg,
	.num_reg_शेषs = ARRAY_SIZE(cs35l34_reg),
	.अस्थिर_reg = cs35l34_अस्थिर_रेजिस्टर,
	.पढ़ोable_reg = cs35l34_पढ़ोable_रेजिस्टर,
	.precious_reg = cs35l34_precious_रेजिस्टर,
	.cache_type = REGCACHE_RBTREE,

	.use_single_पढ़ो = true,
	.use_single_ग_लिखो = true,
पूर्ण;

अटल पूर्णांक cs35l34_handle_of_data(काष्ठा i2c_client *i2c_client,
				काष्ठा cs35l34_platक्रमm_data *pdata)
अणु
	काष्ठा device_node *np = i2c_client->dev.of_node;
	अचिन्हित पूर्णांक val;

	अगर (of_property_पढ़ो_u32(np, "cirrus,boost-vtge-millivolt",
		&val) >= 0) अणु
		/* Boost Voltage has a maximum of 8V */
		अगर (val > 8000 || (val < 3300 && val > 0)) अणु
			dev_err(&i2c_client->dev,
				"Invalid Boost Voltage %d mV\n", val);
			वापस -EINVAL;
		पूर्ण
		अगर (val == 0)
			pdata->boost_vtge = 0; /* Use VP */
		अन्यथा
			pdata->boost_vtge = ((val - 3300)/100) + 1;
	पूर्ण अन्यथा अणु
		dev_warn(&i2c_client->dev,
			"Boost Voltage not specified. Using VP\n");
	पूर्ण

	अगर (of_property_पढ़ो_u32(np, "cirrus,boost-ind-nanohenry", &val) >= 0) अणु
		pdata->boost_ind = val;
	पूर्ण अन्यथा अणु
		dev_err(&i2c_client->dev, "Inductor not specified.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (of_property_पढ़ो_u32(np, "cirrus,boost-peak-milliamp", &val) >= 0) अणु
		अगर (val > 3840 || val < 1200) अणु
			dev_err(&i2c_client->dev,
				"Invalid Boost Peak Current %d mA\n", val);
			वापस -EINVAL;
		पूर्ण
		pdata->boost_peak = ((val - 1200)/80) + 1;
	पूर्ण

	pdata->aअगर_half_drv = of_property_पढ़ो_bool(np,
		"cirrus,aif-half-drv");
	pdata->digsft_disable = of_property_पढ़ो_bool(np,
		"cirrus,digsft-disable");

	pdata->gain_zc_disable = of_property_पढ़ो_bool(np,
		"cirrus,gain-zc-disable");
	pdata->amp_inv = of_property_पढ़ो_bool(np, "cirrus,amp-inv");

	अगर (of_property_पढ़ो_u32(np, "cirrus,i2s-sdinloc", &val) >= 0)
		pdata->i2s_sdinloc = val;
	अगर (of_property_पढ़ो_u32(np, "cirrus,tdm-rising-edge", &val) >= 0)
		pdata->tdm_rising_edge = val;

	वापस 0;
पूर्ण

अटल irqवापस_t cs35l34_irq_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा cs35l34_निजी *cs35l34 = data;
	काष्ठा snd_soc_component *component = cs35l34->component;
	अचिन्हित पूर्णांक sticky1, sticky2, sticky3, sticky4;
	अचिन्हित पूर्णांक mask1, mask2, mask3, mask4, current1;


	/* ack the irq by पढ़ोing all status रेजिस्टरs */
	regmap_पढ़ो(cs35l34->regmap, CS35L34_INT_STATUS_4, &sticky4);
	regmap_पढ़ो(cs35l34->regmap, CS35L34_INT_STATUS_3, &sticky3);
	regmap_पढ़ो(cs35l34->regmap, CS35L34_INT_STATUS_2, &sticky2);
	regmap_पढ़ो(cs35l34->regmap, CS35L34_INT_STATUS_1, &sticky1);

	regmap_पढ़ो(cs35l34->regmap, CS35L34_INT_MASK_4, &mask4);
	regmap_पढ़ो(cs35l34->regmap, CS35L34_INT_MASK_3, &mask3);
	regmap_पढ़ो(cs35l34->regmap, CS35L34_INT_MASK_2, &mask2);
	regmap_पढ़ो(cs35l34->regmap, CS35L34_INT_MASK_1, &mask1);

	अगर (!(sticky1 & ~mask1) && !(sticky2 & ~mask2) && !(sticky3 & ~mask3)
		&& !(sticky4 & ~mask4))
		वापस IRQ_NONE;

	regmap_पढ़ो(cs35l34->regmap, CS35L34_INT_STATUS_1, &current1);

	अगर (sticky1 & CS35L34_CAL_ERR) अणु
		dev_err(component->dev, "Cal error\n");

		/* error is no दीर्घer निश्चितed; safe to reset */
		अगर (!(current1 & CS35L34_CAL_ERR)) अणु
			dev_dbg(component->dev, "Cal error release\n");
			regmap_update_bits(cs35l34->regmap,
					CS35L34_PROT_RELEASE_CTL,
					CS35L34_CAL_ERR_RLS, 0);
			regmap_update_bits(cs35l34->regmap,
					CS35L34_PROT_RELEASE_CTL,
					CS35L34_CAL_ERR_RLS,
					CS35L34_CAL_ERR_RLS);
			regmap_update_bits(cs35l34->regmap,
					CS35L34_PROT_RELEASE_CTL,
					CS35L34_CAL_ERR_RLS, 0);
			/* note: amp will re-calibrate on next resume */
		पूर्ण
	पूर्ण

	अगर (sticky1 & CS35L34_ALIVE_ERR)
		dev_err(component->dev, "Alive error\n");

	अगर (sticky1 & CS35L34_AMP_SHORT) अणु
		dev_crit(component->dev, "Amp short error\n");

		/* error is no दीर्घer निश्चितed; safe to reset */
		अगर (!(current1 & CS35L34_AMP_SHORT)) अणु
			dev_dbg(component->dev,
				"Amp short error release\n");
			regmap_update_bits(cs35l34->regmap,
					CS35L34_PROT_RELEASE_CTL,
					CS35L34_SHORT_RLS, 0);
			regmap_update_bits(cs35l34->regmap,
					CS35L34_PROT_RELEASE_CTL,
					CS35L34_SHORT_RLS,
					CS35L34_SHORT_RLS);
			regmap_update_bits(cs35l34->regmap,
					CS35L34_PROT_RELEASE_CTL,
					CS35L34_SHORT_RLS, 0);
		पूर्ण
	पूर्ण

	अगर (sticky1 & CS35L34_OTW) अणु
		dev_crit(component->dev, "Over temperature warning\n");

		/* error is no दीर्घer निश्चितed; safe to reset */
		अगर (!(current1 & CS35L34_OTW)) अणु
			dev_dbg(component->dev,
				"Over temperature warning release\n");
			regmap_update_bits(cs35l34->regmap,
					CS35L34_PROT_RELEASE_CTL,
					CS35L34_OTW_RLS, 0);
			regmap_update_bits(cs35l34->regmap,
					CS35L34_PROT_RELEASE_CTL,
					CS35L34_OTW_RLS,
					CS35L34_OTW_RLS);
			regmap_update_bits(cs35l34->regmap,
					CS35L34_PROT_RELEASE_CTL,
					CS35L34_OTW_RLS, 0);
		पूर्ण
	पूर्ण

	अगर (sticky1 & CS35L34_OTE) अणु
		dev_crit(component->dev, "Over temperature error\n");

		/* error is no दीर्घer निश्चितed; safe to reset */
		अगर (!(current1 & CS35L34_OTE)) अणु
			dev_dbg(component->dev,
				"Over temperature error release\n");
			regmap_update_bits(cs35l34->regmap,
					CS35L34_PROT_RELEASE_CTL,
					CS35L34_OTE_RLS, 0);
			regmap_update_bits(cs35l34->regmap,
					CS35L34_PROT_RELEASE_CTL,
					CS35L34_OTE_RLS,
					CS35L34_OTE_RLS);
			regmap_update_bits(cs35l34->regmap,
					CS35L34_PROT_RELEASE_CTL,
					CS35L34_OTE_RLS, 0);
		पूर्ण
	पूर्ण

	अगर (sticky3 & CS35L34_BST_HIGH) अणु
		dev_crit(component->dev, "VBST too high error; powering off!\n");
		regmap_update_bits(cs35l34->regmap, CS35L34_PWRCTL2,
				CS35L34_PDN_AMP, CS35L34_PDN_AMP);
		regmap_update_bits(cs35l34->regmap, CS35L34_PWRCTL1,
				CS35L34_PDN_ALL, CS35L34_PDN_ALL);
	पूर्ण

	अगर (sticky3 & CS35L34_LBST_SHORT) अणु
		dev_crit(component->dev, "LBST short error; powering off!\n");
		regmap_update_bits(cs35l34->regmap, CS35L34_PWRCTL2,
				CS35L34_PDN_AMP, CS35L34_PDN_AMP);
		regmap_update_bits(cs35l34->regmap, CS35L34_PWRCTL1,
				CS35L34_PDN_ALL, CS35L34_PDN_ALL);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर अक्षर * स्थिर cs35l34_core_supplies[] = अणु
	"VA",
	"VP",
पूर्ण;

अटल पूर्णांक cs35l34_i2c_probe(काष्ठा i2c_client *i2c_client,
			      स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा cs35l34_निजी *cs35l34;
	काष्ठा cs35l34_platक्रमm_data *pdata =
		dev_get_platdata(&i2c_client->dev);
	पूर्णांक i;
	पूर्णांक ret;
	अचिन्हित पूर्णांक devid = 0;
	अचिन्हित पूर्णांक reg;

	cs35l34 = devm_kzalloc(&i2c_client->dev, माप(*cs35l34), GFP_KERNEL);
	अगर (!cs35l34)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c_client, cs35l34);
	cs35l34->regmap = devm_regmap_init_i2c(i2c_client, &cs35l34_regmap);
	अगर (IS_ERR(cs35l34->regmap)) अणु
		ret = PTR_ERR(cs35l34->regmap);
		dev_err(&i2c_client->dev, "regmap_init() failed: %d\n", ret);
		वापस ret;
	पूर्ण

	cs35l34->num_core_supplies = ARRAY_SIZE(cs35l34_core_supplies);
	क्रम (i = 0; i < ARRAY_SIZE(cs35l34_core_supplies); i++)
		cs35l34->core_supplies[i].supply = cs35l34_core_supplies[i];

	ret = devm_regulator_bulk_get(&i2c_client->dev,
		cs35l34->num_core_supplies,
		cs35l34->core_supplies);
	अगर (ret != 0) अणु
		dev_err(&i2c_client->dev,
			"Failed to request core supplies %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regulator_bulk_enable(cs35l34->num_core_supplies,
					cs35l34->core_supplies);
	अगर (ret != 0) अणु
		dev_err(&i2c_client->dev,
			"Failed to enable core supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (pdata) अणु
		cs35l34->pdata = *pdata;
	पूर्ण अन्यथा अणु
		pdata = devm_kzalloc(&i2c_client->dev, माप(*pdata),
				     GFP_KERNEL);
		अगर (!pdata)
			वापस -ENOMEM;

		अगर (i2c_client->dev.of_node) अणु
			ret = cs35l34_handle_of_data(i2c_client, pdata);
			अगर (ret != 0)
				वापस ret;

		पूर्ण
		cs35l34->pdata = *pdata;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(&i2c_client->dev, i2c_client->irq, शून्य,
			cs35l34_irq_thपढ़ो, IRQF_ONESHOT | IRQF_TRIGGER_LOW,
			"cs35l34", cs35l34);
	अगर (ret != 0)
		dev_err(&i2c_client->dev, "Failed to request IRQ: %d\n", ret);

	cs35l34->reset_gpio = devm_gpiod_get_optional(&i2c_client->dev,
				"reset-gpios", GPIOD_OUT_LOW);
	अगर (IS_ERR(cs35l34->reset_gpio))
		वापस PTR_ERR(cs35l34->reset_gpio);

	gpiod_set_value_cansleep(cs35l34->reset_gpio, 1);

	msleep(CS35L34_START_DELAY);

	ret = regmap_पढ़ो(cs35l34->regmap, CS35L34_DEVID_AB, &reg);

	devid = (reg & 0xFF) << 12;
	ret = regmap_पढ़ो(cs35l34->regmap, CS35L34_DEVID_CD, &reg);
	devid |= (reg & 0xFF) << 4;
	ret = regmap_पढ़ो(cs35l34->regmap, CS35L34_DEVID_E, &reg);
	devid |= (reg & 0xF0) >> 4;

	अगर (devid != CS35L34_CHIP_ID) अणु
		dev_err(&i2c_client->dev,
			"CS35l34 Device ID (%X). Expected ID %X\n",
			devid, CS35L34_CHIP_ID);
		ret = -ENODEV;
		जाओ err_regulator;
	पूर्ण

	ret = regmap_पढ़ो(cs35l34->regmap, CS35L34_REV_ID, &reg);
	अगर (ret < 0) अणु
		dev_err(&i2c_client->dev, "Get Revision ID failed\n");
		जाओ err_regulator;
	पूर्ण

	dev_info(&i2c_client->dev,
		 "Cirrus Logic CS35l34 (%x), Revision: %02X\n", devid,
		reg & 0xFF);

	/* Unmask critical पूर्णांकerrupts */
	regmap_update_bits(cs35l34->regmap, CS35L34_INT_MASK_1,
				CS35L34_M_CAL_ERR | CS35L34_M_ALIVE_ERR |
				CS35L34_M_AMP_SHORT | CS35L34_M_OTW |
				CS35L34_M_OTE, 0);
	regmap_update_bits(cs35l34->regmap, CS35L34_INT_MASK_3,
				CS35L34_M_BST_HIGH | CS35L34_M_LBST_SHORT, 0);

	pm_runसमय_set_स्वतःsuspend_delay(&i2c_client->dev, 100);
	pm_runसमय_use_स्वतःsuspend(&i2c_client->dev);
	pm_runसमय_set_active(&i2c_client->dev);
	pm_runसमय_enable(&i2c_client->dev);

	ret = devm_snd_soc_रेजिस्टर_component(&i2c_client->dev,
			&soc_component_dev_cs35l34, &cs35l34_dai, 1);
	अगर (ret < 0) अणु
		dev_err(&i2c_client->dev,
			"%s: Register component failed\n", __func__);
		जाओ err_regulator;
	पूर्ण

	वापस 0;

err_regulator:
	regulator_bulk_disable(cs35l34->num_core_supplies,
		cs35l34->core_supplies);

	वापस ret;
पूर्ण

अटल पूर्णांक cs35l34_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा cs35l34_निजी *cs35l34 = i2c_get_clientdata(client);

	gpiod_set_value_cansleep(cs35l34->reset_gpio, 0);

	pm_runसमय_disable(&client->dev);
	regulator_bulk_disable(cs35l34->num_core_supplies,
		cs35l34->core_supplies);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused cs35l34_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा cs35l34_निजी *cs35l34 = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = regulator_bulk_enable(cs35l34->num_core_supplies,
		cs35l34->core_supplies);

	अगर (ret != 0) अणु
		dev_err(dev, "Failed to enable core supplies: %d\n",
			ret);
		वापस ret;
	पूर्ण

	regcache_cache_only(cs35l34->regmap, false);

	gpiod_set_value_cansleep(cs35l34->reset_gpio, 1);
	msleep(CS35L34_START_DELAY);

	ret = regcache_sync(cs35l34->regmap);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to restore register cache\n");
		जाओ err;
	पूर्ण
	वापस 0;
err:
	regcache_cache_only(cs35l34->regmap, true);
	regulator_bulk_disable(cs35l34->num_core_supplies,
		cs35l34->core_supplies);

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused cs35l34_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा cs35l34_निजी *cs35l34 = dev_get_drvdata(dev);

	regcache_cache_only(cs35l34->regmap, true);
	regcache_mark_dirty(cs35l34->regmap);

	gpiod_set_value_cansleep(cs35l34->reset_gpio, 0);

	regulator_bulk_disable(cs35l34->num_core_supplies,
			cs35l34->core_supplies);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops cs35l34_pm_ops = अणु
	SET_RUNTIME_PM_OPS(cs35l34_runसमय_suspend,
			   cs35l34_runसमय_resume,
			   शून्य)
पूर्ण;

अटल स्थिर काष्ठा of_device_id cs35l34_of_match[] = अणु
	अणु.compatible = "cirrus,cs35l34"पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, cs35l34_of_match);

अटल स्थिर काष्ठा i2c_device_id cs35l34_id[] = अणु
	अणु"cs35l34", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, cs35l34_id);

अटल काष्ठा i2c_driver cs35l34_i2c_driver = अणु
	.driver = अणु
		.name = "cs35l34",
		.pm = &cs35l34_pm_ops,
		.of_match_table = cs35l34_of_match,

		पूर्ण,
	.id_table = cs35l34_id,
	.probe = cs35l34_i2c_probe,
	.हटाओ = cs35l34_i2c_हटाओ,

पूर्ण;

अटल पूर्णांक __init cs35l34_modinit(व्योम)
अणु
	पूर्णांक ret;

	ret = i2c_add_driver(&cs35l34_i2c_driver);
	अगर (ret != 0) अणु
		pr_err("Failed to register CS35l34 I2C driver: %d\n", ret);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण
module_init(cs35l34_modinit);

अटल व्योम __निकास cs35l34_निकास(व्योम)
अणु
	i2c_del_driver(&cs35l34_i2c_driver);
पूर्ण
module_निकास(cs35l34_निकास);

MODULE_DESCRIPTION("ASoC CS35l34 driver");
MODULE_AUTHOR("Paul Handrigan, Cirrus Logic Inc, <Paul.Handrigan@cirrus.com>");
MODULE_LICENSE("GPL");
