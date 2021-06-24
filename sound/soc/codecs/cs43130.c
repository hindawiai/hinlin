<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * cs43130.c  --  CS43130 ALSA Soc Audio driver
 *
 * Copyright 2017 Cirrus Logic, Inc.
 *
 * Authors: Li Xu <li.xu@cirrus.com>
 */
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/i2c.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/of_irq.h>
#समावेश <linux/completion.h>
#समावेश <linux/mutex.h>
#समावेश <linux/workqueue.h>
#समावेश <sound/jack.h>

#समावेश "cs43130.h"

अटल स्थिर काष्ठा reg_शेष cs43130_reg_शेषs[] = अणु
	अणुCS43130_SYS_CLK_CTL_1, 0x06पूर्ण,
	अणुCS43130_SP_SRATE, 0x01पूर्ण,
	अणुCS43130_SP_BITSIZE, 0x05पूर्ण,
	अणुCS43130_PAD_INT_CFG, 0x03पूर्ण,
	अणुCS43130_PWDN_CTL, 0xFEपूर्ण,
	अणुCS43130_CRYSTAL_SET, 0x04पूर्ण,
	अणुCS43130_PLL_SET_1, 0x00पूर्ण,
	अणुCS43130_PLL_SET_2, 0x00पूर्ण,
	अणुCS43130_PLL_SET_3, 0x00पूर्ण,
	अणुCS43130_PLL_SET_4, 0x00पूर्ण,
	अणुCS43130_PLL_SET_5, 0x40पूर्ण,
	अणुCS43130_PLL_SET_6, 0x10पूर्ण,
	अणुCS43130_PLL_SET_7, 0x80पूर्ण,
	अणुCS43130_PLL_SET_8, 0x03पूर्ण,
	अणुCS43130_PLL_SET_9, 0x02पूर्ण,
	अणुCS43130_PLL_SET_10, 0x02पूर्ण,
	अणुCS43130_CLKOUT_CTL, 0x00पूर्ण,
	अणुCS43130_ASP_NUM_1, 0x01पूर्ण,
	अणुCS43130_ASP_NUM_2, 0x00पूर्ण,
	अणुCS43130_ASP_DEN_1, 0x08पूर्ण,
	अणुCS43130_ASP_DEN_2, 0x00पूर्ण,
	अणुCS43130_ASP_LRCK_HI_TIME_1, 0x1Fपूर्ण,
	अणुCS43130_ASP_LRCK_HI_TIME_2, 0x00पूर्ण,
	अणुCS43130_ASP_LRCK_PERIOD_1, 0x3Fपूर्ण,
	अणुCS43130_ASP_LRCK_PERIOD_2, 0x00पूर्ण,
	अणुCS43130_ASP_CLOCK_CONF, 0x0Cपूर्ण,
	अणुCS43130_ASP_FRAME_CONF, 0x0Aपूर्ण,
	अणुCS43130_XSP_NUM_1, 0x01पूर्ण,
	अणुCS43130_XSP_NUM_2, 0x00पूर्ण,
	अणुCS43130_XSP_DEN_1, 0x02पूर्ण,
	अणुCS43130_XSP_DEN_2, 0x00पूर्ण,
	अणुCS43130_XSP_LRCK_HI_TIME_1, 0x1Fपूर्ण,
	अणुCS43130_XSP_LRCK_HI_TIME_2, 0x00पूर्ण,
	अणुCS43130_XSP_LRCK_PERIOD_1, 0x3Fपूर्ण,
	अणुCS43130_XSP_LRCK_PERIOD_2, 0x00पूर्ण,
	अणुCS43130_XSP_CLOCK_CONF, 0x0Cपूर्ण,
	अणुCS43130_XSP_FRAME_CONF, 0x0Aपूर्ण,
	अणुCS43130_ASP_CH_1_LOC, 0x00पूर्ण,
	अणुCS43130_ASP_CH_2_LOC, 0x00पूर्ण,
	अणुCS43130_ASP_CH_1_SZ_EN, 0x06पूर्ण,
	अणुCS43130_ASP_CH_2_SZ_EN, 0x0Eपूर्ण,
	अणुCS43130_XSP_CH_1_LOC, 0x00पूर्ण,
	अणुCS43130_XSP_CH_2_LOC, 0x00पूर्ण,
	अणुCS43130_XSP_CH_1_SZ_EN, 0x06पूर्ण,
	अणुCS43130_XSP_CH_2_SZ_EN, 0x0Eपूर्ण,
	अणुCS43130_DSD_VOL_B, 0x78पूर्ण,
	अणुCS43130_DSD_VOL_A, 0x78पूर्ण,
	अणुCS43130_DSD_PATH_CTL_1, 0xA8पूर्ण,
	अणुCS43130_DSD_INT_CFG, 0x00पूर्ण,
	अणुCS43130_DSD_PATH_CTL_2, 0x02पूर्ण,
	अणुCS43130_DSD_PCM_MIX_CTL, 0x00पूर्ण,
	अणुCS43130_DSD_PATH_CTL_3, 0x40पूर्ण,
	अणुCS43130_HP_OUT_CTL_1, 0x30पूर्ण,
	अणुCS43130_PCM_FILT_OPT, 0x02पूर्ण,
	अणुCS43130_PCM_VOL_B, 0x78पूर्ण,
	अणुCS43130_PCM_VOL_A, 0x78पूर्ण,
	अणुCS43130_PCM_PATH_CTL_1, 0xA8पूर्ण,
	अणुCS43130_PCM_PATH_CTL_2, 0x00पूर्ण,
	अणुCS43130_CLASS_H_CTL, 0x1Eपूर्ण,
	अणुCS43130_HP_DETECT, 0x04पूर्ण,
	अणुCS43130_HP_LOAD_1, 0x00पूर्ण,
	अणुCS43130_HP_MEAS_LOAD_1, 0x00पूर्ण,
	अणुCS43130_HP_MEAS_LOAD_2, 0x00पूर्ण,
	अणुCS43130_INT_MASK_1, 0xFFपूर्ण,
	अणुCS43130_INT_MASK_2, 0xFFपूर्ण,
	अणुCS43130_INT_MASK_3, 0xFFपूर्ण,
	अणुCS43130_INT_MASK_4, 0xFFपूर्ण,
	अणुCS43130_INT_MASK_5, 0xFFपूर्ण,
पूर्ण;

अटल bool cs43130_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल CS43130_INT_STATUS_1 ... CS43130_INT_STATUS_5:
	हाल CS43130_HP_DC_STAT_1 ... CS43130_HP_DC_STAT_2:
	हाल CS43130_HP_AC_STAT_1 ... CS43130_HP_AC_STAT_2:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool cs43130_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल CS43130_DEVID_AB ... CS43130_SYS_CLK_CTL_1:
	हाल CS43130_SP_SRATE ... CS43130_PAD_INT_CFG:
	हाल CS43130_PWDN_CTL:
	हाल CS43130_CRYSTAL_SET:
	हाल CS43130_PLL_SET_1 ... CS43130_PLL_SET_5:
	हाल CS43130_PLL_SET_6:
	हाल CS43130_PLL_SET_7:
	हाल CS43130_PLL_SET_8:
	हाल CS43130_PLL_SET_9:
	हाल CS43130_PLL_SET_10:
	हाल CS43130_CLKOUT_CTL:
	हाल CS43130_ASP_NUM_1 ... CS43130_ASP_FRAME_CONF:
	हाल CS43130_XSP_NUM_1 ... CS43130_XSP_FRAME_CONF:
	हाल CS43130_ASP_CH_1_LOC:
	हाल CS43130_ASP_CH_2_LOC:
	हाल CS43130_ASP_CH_1_SZ_EN:
	हाल CS43130_ASP_CH_2_SZ_EN:
	हाल CS43130_XSP_CH_1_LOC:
	हाल CS43130_XSP_CH_2_LOC:
	हाल CS43130_XSP_CH_1_SZ_EN:
	हाल CS43130_XSP_CH_2_SZ_EN:
	हाल CS43130_DSD_VOL_B ... CS43130_DSD_PATH_CTL_3:
	हाल CS43130_HP_OUT_CTL_1:
	हाल CS43130_PCM_FILT_OPT ... CS43130_PCM_PATH_CTL_2:
	हाल CS43130_CLASS_H_CTL:
	हाल CS43130_HP_DETECT:
	हाल CS43130_HP_STATUS:
	हाल CS43130_HP_LOAD_1:
	हाल CS43130_HP_MEAS_LOAD_1:
	हाल CS43130_HP_MEAS_LOAD_2:
	हाल CS43130_HP_DC_STAT_1:
	हाल CS43130_HP_DC_STAT_2:
	हाल CS43130_HP_AC_STAT_1:
	हाल CS43130_HP_AC_STAT_2:
	हाल CS43130_HP_LOAD_STAT:
	हाल CS43130_INT_STATUS_1 ... CS43130_INT_STATUS_5:
	हाल CS43130_INT_MASK_1 ... CS43130_INT_MASK_5:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool cs43130_precious_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल CS43130_INT_STATUS_1 ... CS43130_INT_STATUS_5:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

काष्ठा cs43130_pll_params अणु
	अचिन्हित पूर्णांक pll_in;
	u8 sclk_preभाग;
	u8 pll_भाग_पूर्णांक;
	u32 pll_भाग_frac;
	u8 pll_mode;
	u8 pll_भागout;
	अचिन्हित पूर्णांक pll_out;
	u8 pll_cal_ratio;
पूर्ण;

अटल स्थिर काष्ठा cs43130_pll_params pll_ratio_table[] = अणु
	अणु9600000, 0x02, 0x49, 0x800000, 0x00, 0x08, 22579200, 151पूर्ण,
	अणु9600000, 0x02, 0x50, 0x000000, 0x00, 0x08, 24576000, 164पूर्ण,

	अणु11289600, 0x02, 0X40, 0, 0x01, 0x08, 22579200, 128पूर्ण,
	अणु11289600, 0x02, 0x44, 0x06F700, 0x0, 0x08, 24576000, 139पूर्ण,

	अणु12000000, 0x02, 0x49, 0x800000, 0x00, 0x0A, 22579200, 120पूर्ण,
	अणु12000000, 0x02, 0x40, 0x000000, 0x00, 0x08, 24576000, 131पूर्ण,

	अणु12288000, 0x02, 0x49, 0x800000, 0x01, 0x0A, 22579200, 118पूर्ण,
	अणु12288000, 0x02, 0x40, 0x000000, 0x01, 0x08, 24576000, 128पूर्ण,

	अणु13000000, 0x02, 0x45, 0x797680, 0x01, 0x0A, 22579200, 111पूर्ण,
	अणु13000000, 0x02, 0x3C, 0x7EA940, 0x01, 0x08, 24576000, 121पूर्ण,

	अणु19200000, 0x03, 0x49, 0x800000, 0x00, 0x08, 22579200, 151पूर्ण,
	अणु19200000, 0x03, 0x50, 0x000000, 0x00, 0x08, 24576000, 164पूर्ण,

	अणु22579200, 0, 0, 0, 0, 0, 22579200, 0पूर्ण,
	अणु22579200, 0x03, 0x44, 0x06F700, 0x00, 0x08, 24576000, 139पूर्ण,

	अणु24000000, 0x03, 0x49, 0x800000, 0x00, 0x0A, 22579200, 120पूर्ण,
	अणु24000000, 0x03, 0x40, 0x000000, 0x00, 0x08, 24576000, 131पूर्ण,

	अणु24576000, 0x03, 0x49, 0x800000, 0x01, 0x0A, 22579200, 118पूर्ण,
	अणु24576000, 0, 0, 0, 0, 0, 24576000, 0पूर्ण,

	अणु26000000, 0x03, 0x45, 0x797680, 0x01, 0x0A, 22579200, 111पूर्ण,
	अणु26000000, 0x03, 0x3C, 0x7EA940, 0x01, 0x08, 24576000, 121पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cs43130_pll_params *cs43130_get_pll_table(
		अचिन्हित पूर्णांक freq_in, अचिन्हित पूर्णांक freq_out)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(pll_ratio_table); i++) अणु
		अगर (pll_ratio_table[i].pll_in == freq_in &&
		    pll_ratio_table[i].pll_out == freq_out)
			वापस &pll_ratio_table[i];
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक cs43130_pll_config(काष्ठा snd_soc_component *component)
अणु
	काष्ठा cs43130_निजी *cs43130 = snd_soc_component_get_drvdata(component);
	स्थिर काष्ठा cs43130_pll_params *pll_entry;

	dev_dbg(component->dev, "cs43130->mclk = %u, cs43130->mclk_int = %u\n",
		cs43130->mclk, cs43130->mclk_पूर्णांक);

	pll_entry = cs43130_get_pll_table(cs43130->mclk, cs43130->mclk_पूर्णांक);
	अगर (!pll_entry)
		वापस -EINVAL;

	अगर (pll_entry->pll_cal_ratio == 0) अणु
		regmap_update_bits(cs43130->regmap, CS43130_PLL_SET_1,
				   CS43130_PLL_START_MASK, 0);

		cs43130->pll_bypass = true;
		वापस 0;
	पूर्ण

	cs43130->pll_bypass = false;

	regmap_update_bits(cs43130->regmap, CS43130_PLL_SET_2,
			   CS43130_PLL_DIV_DATA_MASK,
			   pll_entry->pll_भाग_frac >>
			   CS43130_PLL_DIV_FRAC_0_DATA_SHIFT);
	regmap_update_bits(cs43130->regmap, CS43130_PLL_SET_3,
			   CS43130_PLL_DIV_DATA_MASK,
			   pll_entry->pll_भाग_frac >>
			   CS43130_PLL_DIV_FRAC_1_DATA_SHIFT);
	regmap_update_bits(cs43130->regmap, CS43130_PLL_SET_4,
			   CS43130_PLL_DIV_DATA_MASK,
			   pll_entry->pll_भाग_frac >>
			   CS43130_PLL_DIV_FRAC_2_DATA_SHIFT);
	regmap_ग_लिखो(cs43130->regmap, CS43130_PLL_SET_5,
		     pll_entry->pll_भाग_पूर्णांक);
	regmap_ग_लिखो(cs43130->regmap, CS43130_PLL_SET_6, pll_entry->pll_भागout);
	regmap_ग_लिखो(cs43130->regmap, CS43130_PLL_SET_7,
		     pll_entry->pll_cal_ratio);
	regmap_update_bits(cs43130->regmap, CS43130_PLL_SET_8,
			   CS43130_PLL_MODE_MASK,
			   pll_entry->pll_mode << CS43130_PLL_MODE_SHIFT);
	regmap_ग_लिखो(cs43130->regmap, CS43130_PLL_SET_9,
		     pll_entry->sclk_preभाग);
	regmap_update_bits(cs43130->regmap, CS43130_PLL_SET_1,
			   CS43130_PLL_START_MASK, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक cs43130_set_pll(काष्ठा snd_soc_component *component, पूर्णांक pll_id, पूर्णांक source,
			   अचिन्हित पूर्णांक freq_in, अचिन्हित पूर्णांक freq_out)
अणु
	पूर्णांक ret = 0;
	काष्ठा cs43130_निजी *cs43130 = snd_soc_component_get_drvdata(component);

	चयन (freq_in) अणु
	हाल 9600000:
	हाल 11289600:
	हाल 12000000:
	हाल 12288000:
	हाल 13000000:
	हाल 19200000:
	हाल 22579200:
	हाल 24000000:
	हाल 24576000:
	हाल 26000000:
		cs43130->mclk = freq_in;
		अवरोध;
	शेष:
		dev_err(component->dev,
			"unsupported pll input reference clock:%d\n", freq_in);
		वापस -EINVAL;
	पूर्ण

	चयन (freq_out) अणु
	हाल 22579200:
		cs43130->mclk_पूर्णांक = freq_out;
		अवरोध;
	हाल 24576000:
		cs43130->mclk_पूर्णांक = freq_out;
		अवरोध;
	शेष:
		dev_err(component->dev,
			"unsupported pll output ref clock: %u\n", freq_out);
		वापस -EINVAL;
	पूर्ण

	ret = cs43130_pll_config(component);
	dev_dbg(component->dev, "cs43130->pll_bypass = %d", cs43130->pll_bypass);
	वापस ret;
पूर्ण

अटल पूर्णांक cs43130_change_clksrc(काष्ठा snd_soc_component *component,
				 क्रमागत cs43130_mclk_src_sel src)
अणु
	पूर्णांक ret;
	काष्ठा cs43130_निजी *cs43130 = snd_soc_component_get_drvdata(component);
	पूर्णांक mclk_पूर्णांक_decoded;

	अगर (src == cs43130->mclk_पूर्णांक_src) अणु
		/* clk source has not changed */
		वापस 0;
	पूर्ण

	चयन (cs43130->mclk_पूर्णांक) अणु
	हाल CS43130_MCLK_22M:
		mclk_पूर्णांक_decoded = CS43130_MCLK_22P5;
		अवरोध;
	हाल CS43130_MCLK_24M:
		mclk_पूर्णांक_decoded = CS43130_MCLK_24P5;
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid MCLK INT freq: %u\n", cs43130->mclk_पूर्णांक);
		वापस -EINVAL;
	पूर्ण

	चयन (src) अणु
	हाल CS43130_MCLK_SRC_EXT:
		cs43130->pll_bypass = true;
		cs43130->mclk_पूर्णांक_src = CS43130_MCLK_SRC_EXT;
		अगर (cs43130->xtal_ibias == CS43130_XTAL_UNUSED) अणु
			regmap_update_bits(cs43130->regmap, CS43130_PWDN_CTL,
					   CS43130_PDN_XTAL_MASK,
					   1 << CS43130_PDN_XTAL_SHIFT);
		पूर्ण अन्यथा अणु
			reinit_completion(&cs43130->xtal_rdy);
			regmap_update_bits(cs43130->regmap, CS43130_INT_MASK_1,
					   CS43130_XTAL_RDY_INT_MASK, 0);
			regmap_update_bits(cs43130->regmap, CS43130_PWDN_CTL,
					   CS43130_PDN_XTAL_MASK, 0);
			ret = रुको_क्रम_completion_समयout(&cs43130->xtal_rdy,
							  msecs_to_jअगरfies(100));
			regmap_update_bits(cs43130->regmap, CS43130_INT_MASK_1,
					   CS43130_XTAL_RDY_INT_MASK,
					   1 << CS43130_XTAL_RDY_INT_SHIFT);
			अगर (ret == 0) अणु
				dev_err(component->dev, "Timeout waiting for XTAL_READY interrupt\n");
				वापस -ETIMEDOUT;
			पूर्ण
		पूर्ण

		regmap_update_bits(cs43130->regmap, CS43130_SYS_CLK_CTL_1,
				   CS43130_MCLK_SRC_SEL_MASK,
				   src << CS43130_MCLK_SRC_SEL_SHIFT);
		regmap_update_bits(cs43130->regmap, CS43130_SYS_CLK_CTL_1,
				   CS43130_MCLK_INT_MASK,
				   mclk_पूर्णांक_decoded << CS43130_MCLK_INT_SHIFT);
		usleep_range(150, 200);

		regmap_update_bits(cs43130->regmap, CS43130_PWDN_CTL,
				   CS43130_PDN_PLL_MASK,
				   1 << CS43130_PDN_PLL_SHIFT);
		अवरोध;
	हाल CS43130_MCLK_SRC_PLL:
		cs43130->pll_bypass = false;
		cs43130->mclk_पूर्णांक_src = CS43130_MCLK_SRC_PLL;
		अगर (cs43130->xtal_ibias == CS43130_XTAL_UNUSED) अणु
			regmap_update_bits(cs43130->regmap, CS43130_PWDN_CTL,
					   CS43130_PDN_XTAL_MASK,
					   1 << CS43130_PDN_XTAL_SHIFT);
		पूर्ण अन्यथा अणु
			reinit_completion(&cs43130->xtal_rdy);
			regmap_update_bits(cs43130->regmap, CS43130_INT_MASK_1,
					   CS43130_XTAL_RDY_INT_MASK, 0);
			regmap_update_bits(cs43130->regmap, CS43130_PWDN_CTL,
					   CS43130_PDN_XTAL_MASK, 0);
			ret = रुको_क्रम_completion_समयout(&cs43130->xtal_rdy,
							  msecs_to_jअगरfies(100));
			regmap_update_bits(cs43130->regmap, CS43130_INT_MASK_1,
					   CS43130_XTAL_RDY_INT_MASK,
					   1 << CS43130_XTAL_RDY_INT_SHIFT);
			अगर (ret == 0) अणु
				dev_err(component->dev, "Timeout waiting for XTAL_READY interrupt\n");
				वापस -ETIMEDOUT;
			पूर्ण
		पूर्ण

		reinit_completion(&cs43130->pll_rdy);
		regmap_update_bits(cs43130->regmap, CS43130_INT_MASK_1,
				   CS43130_PLL_RDY_INT_MASK, 0);
		regmap_update_bits(cs43130->regmap, CS43130_PWDN_CTL,
				   CS43130_PDN_PLL_MASK, 0);
		ret = रुको_क्रम_completion_समयout(&cs43130->pll_rdy,
						  msecs_to_jअगरfies(100));
		regmap_update_bits(cs43130->regmap, CS43130_INT_MASK_1,
				   CS43130_PLL_RDY_INT_MASK,
				   1 << CS43130_PLL_RDY_INT_SHIFT);
		अगर (ret == 0) अणु
			dev_err(component->dev, "Timeout waiting for PLL_READY interrupt\n");
			वापस -ETIMEDOUT;
		पूर्ण

		regmap_update_bits(cs43130->regmap, CS43130_SYS_CLK_CTL_1,
				   CS43130_MCLK_SRC_SEL_MASK,
				   src << CS43130_MCLK_SRC_SEL_SHIFT);
		regmap_update_bits(cs43130->regmap, CS43130_SYS_CLK_CTL_1,
				   CS43130_MCLK_INT_MASK,
				   mclk_पूर्णांक_decoded << CS43130_MCLK_INT_SHIFT);
		usleep_range(150, 200);
		अवरोध;
	हाल CS43130_MCLK_SRC_RCO:
		cs43130->mclk_पूर्णांक_src = CS43130_MCLK_SRC_RCO;

		regmap_update_bits(cs43130->regmap, CS43130_SYS_CLK_CTL_1,
				   CS43130_MCLK_SRC_SEL_MASK,
				   src << CS43130_MCLK_SRC_SEL_SHIFT);
		regmap_update_bits(cs43130->regmap, CS43130_SYS_CLK_CTL_1,
				   CS43130_MCLK_INT_MASK,
				   CS43130_MCLK_22P5 << CS43130_MCLK_INT_SHIFT);
		usleep_range(150, 200);

		regmap_update_bits(cs43130->regmap, CS43130_PWDN_CTL,
				   CS43130_PDN_XTAL_MASK,
				   1 << CS43130_PDN_XTAL_SHIFT);
		regmap_update_bits(cs43130->regmap, CS43130_PWDN_CTL,
				   CS43130_PDN_PLL_MASK,
				   1 << CS43130_PDN_PLL_SHIFT);
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid MCLK source value\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा cs43130_bitwidth_map cs43130_bitwidth_table[] = अणु
	अणु8,	CS43130_SP_BIT_SIZE_8,	CS43130_CH_BIT_SIZE_8पूर्ण,
	अणु16,	CS43130_SP_BIT_SIZE_16, CS43130_CH_BIT_SIZE_16पूर्ण,
	अणु24,	CS43130_SP_BIT_SIZE_24, CS43130_CH_BIT_SIZE_24पूर्ण,
	अणु32,	CS43130_SP_BIT_SIZE_32, CS43130_CH_BIT_SIZE_32पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cs43130_bitwidth_map *cs43130_get_bitwidth_table(
				अचिन्हित पूर्णांक bitwidth)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(cs43130_bitwidth_table); i++) अणु
		अगर (cs43130_bitwidth_table[i].bitwidth == bitwidth)
			वापस &cs43130_bitwidth_table[i];
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक cs43130_set_bitwidth(पूर्णांक dai_id, अचिन्हित पूर्णांक bitwidth_dai,
			  काष्ठा regmap *regmap)
अणु
	स्थिर काष्ठा cs43130_bitwidth_map *bw_map;

	bw_map = cs43130_get_bitwidth_table(bitwidth_dai);
	अगर (!bw_map)
		वापस -EINVAL;

	चयन (dai_id) अणु
	हाल CS43130_ASP_PCM_DAI:
	हाल CS43130_ASP_DOP_DAI:
		regmap_update_bits(regmap, CS43130_ASP_CH_1_SZ_EN,
				   CS43130_CH_BITSIZE_MASK, bw_map->ch_bit);
		regmap_update_bits(regmap, CS43130_ASP_CH_2_SZ_EN,
				   CS43130_CH_BITSIZE_MASK, bw_map->ch_bit);
		regmap_update_bits(regmap, CS43130_SP_BITSIZE,
				   CS43130_ASP_BITSIZE_MASK, bw_map->sp_bit);
		अवरोध;
	हाल CS43130_XSP_DOP_DAI:
		regmap_update_bits(regmap, CS43130_XSP_CH_1_SZ_EN,
				   CS43130_CH_BITSIZE_MASK, bw_map->ch_bit);
		regmap_update_bits(regmap, CS43130_XSP_CH_2_SZ_EN,
				   CS43130_CH_BITSIZE_MASK, bw_map->ch_bit);
		regmap_update_bits(regmap, CS43130_SP_BITSIZE,
				   CS43130_XSP_BITSIZE_MASK, bw_map->sp_bit <<
				   CS43130_XSP_BITSIZE_SHIFT);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा cs43130_rate_map cs43130_rate_table[] = अणु
	अणु32000,		CS43130_ASP_SPRATE_32Kपूर्ण,
	अणु44100,		CS43130_ASP_SPRATE_44_1Kपूर्ण,
	अणु48000,		CS43130_ASP_SPRATE_48Kपूर्ण,
	अणु88200,		CS43130_ASP_SPRATE_88_2Kपूर्ण,
	अणु96000,		CS43130_ASP_SPRATE_96Kपूर्ण,
	अणु176400,	CS43130_ASP_SPRATE_176_4Kपूर्ण,
	अणु192000,	CS43130_ASP_SPRATE_192Kपूर्ण,
	अणु352800,	CS43130_ASP_SPRATE_352_8Kपूर्ण,
	अणु384000,	CS43130_ASP_SPRATE_384Kपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cs43130_rate_map *cs43130_get_rate_table(पूर्णांक fs)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(cs43130_rate_table); i++) अणु
		अगर (cs43130_rate_table[i].fs == fs)
			वापस &cs43130_rate_table[i];
	पूर्ण

	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा cs43130_clk_gen *cs43130_get_clk_gen(पूर्णांक mclk_पूर्णांक, पूर्णांक fs,
		स्थिर काष्ठा cs43130_clk_gen *clk_gen_table, पूर्णांक len_clk_gen_table)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < len_clk_gen_table; i++) अणु
		अगर (clk_gen_table[i].mclk_पूर्णांक == mclk_पूर्णांक &&
		    clk_gen_table[i].fs == fs)
			वापस &clk_gen_table[i];
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक cs43130_set_sp_fmt(पूर्णांक dai_id, अचिन्हित पूर्णांक bitwidth_sclk,
			      काष्ठा snd_pcm_hw_params *params,
			      काष्ठा cs43130_निजी *cs43130)
अणु
	u16 frm_size;
	u16 hi_size;
	u8 frm_delay;
	u8 frm_phase;
	u8 frm_data;
	u8 sclk_edge;
	u8 lrck_edge;
	u8 clk_data;
	u8 loc_ch1;
	u8 loc_ch2;
	u8 dai_mode_val;
	स्थिर काष्ठा cs43130_clk_gen *clk_gen;

	चयन (cs43130->dais[dai_id].dai_क्रमmat) अणु
	हाल SND_SOC_DAIFMT_I2S:
		hi_size = bitwidth_sclk;
		frm_delay = 2;
		frm_phase = 0;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		hi_size = bitwidth_sclk;
		frm_delay = 2;
		frm_phase = 1;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		hi_size = 1;
		frm_delay = 2;
		frm_phase = 1;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		hi_size = 1;
		frm_delay = 0;
		frm_phase = 1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (cs43130->dais[dai_id].dai_mode) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		dai_mode_val = 0;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFM:
		dai_mode_val = 1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	frm_size = bitwidth_sclk * params_channels(params);
	sclk_edge = 1;
	lrck_edge = 0;
	loc_ch1 = 0;
	loc_ch2 = bitwidth_sclk * (params_channels(params) - 1);

	frm_data = frm_delay & CS43130_SP_FSD_MASK;
	frm_data |= (frm_phase << CS43130_SP_STP_SHIFT) & CS43130_SP_STP_MASK;

	clk_data = lrck_edge & CS43130_SP_LCPOL_IN_MASK;
	clk_data |= (lrck_edge << CS43130_SP_LCPOL_OUT_SHIFT) &
		    CS43130_SP_LCPOL_OUT_MASK;
	clk_data |= (sclk_edge << CS43130_SP_SCPOL_IN_SHIFT) &
		    CS43130_SP_SCPOL_IN_MASK;
	clk_data |= (sclk_edge << CS43130_SP_SCPOL_OUT_SHIFT) &
		    CS43130_SP_SCPOL_OUT_MASK;
	clk_data |= (dai_mode_val << CS43130_SP_MODE_SHIFT) &
		    CS43130_SP_MODE_MASK;

	चयन (dai_id) अणु
	हाल CS43130_ASP_PCM_DAI:
	हाल CS43130_ASP_DOP_DAI:
		regmap_update_bits(cs43130->regmap, CS43130_ASP_LRCK_PERIOD_1,
			CS43130_SP_LCPR_DATA_MASK, (frm_size - 1) >>
			CS43130_SP_LCPR_LSB_DATA_SHIFT);
		regmap_update_bits(cs43130->regmap, CS43130_ASP_LRCK_PERIOD_2,
			CS43130_SP_LCPR_DATA_MASK, (frm_size - 1) >>
			CS43130_SP_LCPR_MSB_DATA_SHIFT);
		regmap_update_bits(cs43130->regmap, CS43130_ASP_LRCK_HI_TIME_1,
			CS43130_SP_LCHI_DATA_MASK, (hi_size - 1) >>
			CS43130_SP_LCHI_LSB_DATA_SHIFT);
		regmap_update_bits(cs43130->regmap, CS43130_ASP_LRCK_HI_TIME_2,
			CS43130_SP_LCHI_DATA_MASK, (hi_size - 1) >>
			CS43130_SP_LCHI_MSB_DATA_SHIFT);
		regmap_ग_लिखो(cs43130->regmap, CS43130_ASP_FRAME_CONF, frm_data);
		regmap_ग_लिखो(cs43130->regmap, CS43130_ASP_CH_1_LOC, loc_ch1);
		regmap_ग_लिखो(cs43130->regmap, CS43130_ASP_CH_2_LOC, loc_ch2);
		regmap_update_bits(cs43130->regmap, CS43130_ASP_CH_1_SZ_EN,
			CS43130_CH_EN_MASK, 1 << CS43130_CH_EN_SHIFT);
		regmap_update_bits(cs43130->regmap, CS43130_ASP_CH_2_SZ_EN,
			CS43130_CH_EN_MASK, 1 << CS43130_CH_EN_SHIFT);
		regmap_ग_लिखो(cs43130->regmap, CS43130_ASP_CLOCK_CONF, clk_data);
		अवरोध;
	हाल CS43130_XSP_DOP_DAI:
		regmap_update_bits(cs43130->regmap, CS43130_XSP_LRCK_PERIOD_1,
			CS43130_SP_LCPR_DATA_MASK, (frm_size - 1) >>
			CS43130_SP_LCPR_LSB_DATA_SHIFT);
		regmap_update_bits(cs43130->regmap, CS43130_XSP_LRCK_PERIOD_2,
			CS43130_SP_LCPR_DATA_MASK, (frm_size - 1) >>
			CS43130_SP_LCPR_MSB_DATA_SHIFT);
		regmap_update_bits(cs43130->regmap, CS43130_XSP_LRCK_HI_TIME_1,
			CS43130_SP_LCHI_DATA_MASK, (hi_size - 1) >>
			CS43130_SP_LCHI_LSB_DATA_SHIFT);
		regmap_update_bits(cs43130->regmap, CS43130_XSP_LRCK_HI_TIME_2,
			CS43130_SP_LCHI_DATA_MASK, (hi_size - 1) >>
			CS43130_SP_LCHI_MSB_DATA_SHIFT);
		regmap_ग_लिखो(cs43130->regmap, CS43130_XSP_FRAME_CONF, frm_data);
		regmap_ग_लिखो(cs43130->regmap, CS43130_XSP_CH_1_LOC, loc_ch1);
		regmap_ग_लिखो(cs43130->regmap, CS43130_XSP_CH_2_LOC, loc_ch2);
		regmap_update_bits(cs43130->regmap, CS43130_XSP_CH_1_SZ_EN,
			CS43130_CH_EN_MASK, 1 << CS43130_CH_EN_SHIFT);
		regmap_update_bits(cs43130->regmap, CS43130_XSP_CH_2_SZ_EN,
			CS43130_CH_EN_MASK, 1 << CS43130_CH_EN_SHIFT);
		regmap_ग_लिखो(cs43130->regmap, CS43130_XSP_CLOCK_CONF, clk_data);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (frm_size) अणु
	हाल 16:
		clk_gen = cs43130_get_clk_gen(cs43130->mclk_पूर्णांक,
					      params_rate(params),
					      cs43130_16_clk_gen,
					      ARRAY_SIZE(cs43130_16_clk_gen));
		अवरोध;
	हाल 32:
		clk_gen = cs43130_get_clk_gen(cs43130->mclk_पूर्णांक,
					      params_rate(params),
					      cs43130_32_clk_gen,
					      ARRAY_SIZE(cs43130_32_clk_gen));
		अवरोध;
	हाल 48:
		clk_gen = cs43130_get_clk_gen(cs43130->mclk_पूर्णांक,
					      params_rate(params),
					      cs43130_48_clk_gen,
					      ARRAY_SIZE(cs43130_48_clk_gen));
		अवरोध;
	हाल 64:
		clk_gen = cs43130_get_clk_gen(cs43130->mclk_पूर्णांक,
					      params_rate(params),
					      cs43130_64_clk_gen,
					      ARRAY_SIZE(cs43130_64_clk_gen));
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (!clk_gen)
		वापस -EINVAL;

	चयन (dai_id) अणु
	हाल CS43130_ASP_PCM_DAI:
	हाल CS43130_ASP_DOP_DAI:
		regmap_ग_लिखो(cs43130->regmap, CS43130_ASP_DEN_1,
			     (clk_gen->den & CS43130_SP_M_LSB_DATA_MASK) >>
			     CS43130_SP_M_LSB_DATA_SHIFT);
		regmap_ग_लिखो(cs43130->regmap, CS43130_ASP_DEN_2,
			     (clk_gen->den & CS43130_SP_M_MSB_DATA_MASK) >>
			     CS43130_SP_M_MSB_DATA_SHIFT);
		regmap_ग_लिखो(cs43130->regmap, CS43130_ASP_NUM_1,
			     (clk_gen->num & CS43130_SP_N_LSB_DATA_MASK) >>
			     CS43130_SP_N_LSB_DATA_SHIFT);
		regmap_ग_लिखो(cs43130->regmap, CS43130_ASP_NUM_2,
			     (clk_gen->num & CS43130_SP_N_MSB_DATA_MASK) >>
			     CS43130_SP_N_MSB_DATA_SHIFT);
		अवरोध;
	हाल CS43130_XSP_DOP_DAI:
		regmap_ग_लिखो(cs43130->regmap, CS43130_XSP_DEN_1,
			     (clk_gen->den & CS43130_SP_M_LSB_DATA_MASK) >>
			     CS43130_SP_M_LSB_DATA_SHIFT);
		regmap_ग_लिखो(cs43130->regmap, CS43130_XSP_DEN_2,
			     (clk_gen->den & CS43130_SP_M_MSB_DATA_MASK) >>
			     CS43130_SP_M_MSB_DATA_SHIFT);
		regmap_ग_लिखो(cs43130->regmap, CS43130_XSP_NUM_1,
			     (clk_gen->num & CS43130_SP_N_LSB_DATA_MASK) >>
			     CS43130_SP_N_LSB_DATA_SHIFT);
		regmap_ग_लिखो(cs43130->regmap, CS43130_XSP_NUM_2,
			     (clk_gen->num & CS43130_SP_N_MSB_DATA_MASK) >>
			     CS43130_SP_N_MSB_DATA_SHIFT);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cs43130_pcm_dsd_mix(bool en, काष्ठा regmap *regmap)
अणु
	अगर (en) अणु
		regmap_update_bits(regmap, CS43130_DSD_PCM_MIX_CTL,
				   CS43130_MIX_PCM_PREP_MASK,
				   1 << CS43130_MIX_PCM_PREP_SHIFT);
		usleep_range(6000, 6050);
		regmap_update_bits(regmap, CS43130_DSD_PCM_MIX_CTL,
				   CS43130_MIX_PCM_DSD_MASK,
				   1 << CS43130_MIX_PCM_DSD_SHIFT);
	पूर्ण अन्यथा अणु
		regmap_update_bits(regmap, CS43130_DSD_PCM_MIX_CTL,
				   CS43130_MIX_PCM_DSD_MASK,
				   0 << CS43130_MIX_PCM_DSD_SHIFT);
		usleep_range(1600, 1650);
		regmap_update_bits(regmap, CS43130_DSD_PCM_MIX_CTL,
				   CS43130_MIX_PCM_PREP_MASK,
				   0 << CS43130_MIX_PCM_PREP_SHIFT);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cs43130_dsd_hw_params(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *params,
				 काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा cs43130_निजी *cs43130 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक required_clk;
	u8 dsd_speed;

	mutex_lock(&cs43130->clk_mutex);
	अगर (!cs43130->clk_req) अणु
		/* no DAI is currently using clk */
		अगर (!(CS43130_MCLK_22M % params_rate(params)))
			required_clk = CS43130_MCLK_22M;
		अन्यथा
			required_clk = CS43130_MCLK_24M;

		cs43130_set_pll(component, 0, 0, cs43130->mclk, required_clk);
		अगर (cs43130->pll_bypass)
			cs43130_change_clksrc(component, CS43130_MCLK_SRC_EXT);
		अन्यथा
			cs43130_change_clksrc(component, CS43130_MCLK_SRC_PLL);
	पूर्ण

	cs43130->clk_req++;
	अगर (cs43130->clk_req == 2)
		cs43130_pcm_dsd_mix(true, cs43130->regmap);
	mutex_unlock(&cs43130->clk_mutex);

	चयन (params_rate(params)) अणु
	हाल 176400:
		dsd_speed = 0;
		अवरोध;
	हाल 352800:
		dsd_speed = 1;
		अवरोध;
	शेष:
		dev_err(component->dev, "Rate(%u) not supported\n",
			params_rate(params));
		वापस -EINVAL;
	पूर्ण

	अगर (cs43130->dais[dai->id].dai_mode == SND_SOC_DAIFMT_CBM_CFM)
		regmap_update_bits(cs43130->regmap, CS43130_DSD_INT_CFG,
				   CS43130_DSD_MASTER, CS43130_DSD_MASTER);
	अन्यथा
		regmap_update_bits(cs43130->regmap, CS43130_DSD_INT_CFG,
				   CS43130_DSD_MASTER, 0);

	regmap_update_bits(cs43130->regmap, CS43130_DSD_PATH_CTL_2,
			   CS43130_DSD_SPEED_MASK,
			   dsd_speed << CS43130_DSD_SPEED_SHIFT);
	regmap_update_bits(cs43130->regmap, CS43130_DSD_PATH_CTL_2,
			   CS43130_DSD_SRC_MASK, CS43130_DSD_SRC_DSD <<
			   CS43130_DSD_SRC_SHIFT);

	वापस 0;
पूर्ण

अटल पूर्णांक cs43130_hw_params(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *params,
				 काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा cs43130_निजी *cs43130 = snd_soc_component_get_drvdata(component);
	स्थिर काष्ठा cs43130_rate_map *rate_map;
	अचिन्हित पूर्णांक sclk = cs43130->dais[dai->id].sclk;
	अचिन्हित पूर्णांक bitwidth_sclk;
	अचिन्हित पूर्णांक bitwidth_dai = (अचिन्हित पूर्णांक)(params_width(params));
	अचिन्हित पूर्णांक required_clk;
	u8 dsd_speed;

	mutex_lock(&cs43130->clk_mutex);
	अगर (!cs43130->clk_req) अणु
		/* no DAI is currently using clk */
		अगर (!(CS43130_MCLK_22M % params_rate(params)))
			required_clk = CS43130_MCLK_22M;
		अन्यथा
			required_clk = CS43130_MCLK_24M;

		cs43130_set_pll(component, 0, 0, cs43130->mclk, required_clk);
		अगर (cs43130->pll_bypass)
			cs43130_change_clksrc(component, CS43130_MCLK_SRC_EXT);
		अन्यथा
			cs43130_change_clksrc(component, CS43130_MCLK_SRC_PLL);
	पूर्ण

	cs43130->clk_req++;
	अगर (cs43130->clk_req == 2)
		cs43130_pcm_dsd_mix(true, cs43130->regmap);
	mutex_unlock(&cs43130->clk_mutex);

	चयन (dai->id) अणु
	हाल CS43130_ASP_DOP_DAI:
	हाल CS43130_XSP_DOP_DAI:
		/* DoP bitwidth is always 24-bit */
		bitwidth_dai = 24;
		sclk = params_rate(params) * bitwidth_dai *
		       params_channels(params);

		चयन (params_rate(params)) अणु
		हाल 176400:
			dsd_speed = 0;
			अवरोध;
		हाल 352800:
			dsd_speed = 1;
			अवरोध;
		शेष:
			dev_err(component->dev, "Rate(%u) not supported\n",
				params_rate(params));
			वापस -EINVAL;
		पूर्ण

		regmap_update_bits(cs43130->regmap, CS43130_DSD_PATH_CTL_2,
				   CS43130_DSD_SPEED_MASK,
				   dsd_speed << CS43130_DSD_SPEED_SHIFT);
		अवरोध;
	हाल CS43130_ASP_PCM_DAI:
		rate_map = cs43130_get_rate_table(params_rate(params));
		अगर (!rate_map)
			वापस -EINVAL;

		regmap_ग_लिखो(cs43130->regmap, CS43130_SP_SRATE, rate_map->val);
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid DAI (%d)\n", dai->id);
		वापस -EINVAL;
	पूर्ण

	चयन (dai->id) अणु
	हाल CS43130_ASP_DOP_DAI:
		regmap_update_bits(cs43130->regmap, CS43130_DSD_PATH_CTL_2,
				   CS43130_DSD_SRC_MASK, CS43130_DSD_SRC_ASP <<
				   CS43130_DSD_SRC_SHIFT);
		अवरोध;
	हाल CS43130_XSP_DOP_DAI:
		regmap_update_bits(cs43130->regmap, CS43130_DSD_PATH_CTL_2,
				   CS43130_DSD_SRC_MASK, CS43130_DSD_SRC_XSP <<
				   CS43130_DSD_SRC_SHIFT);
		अवरोध;
	पूर्ण

	अगर (!sclk && cs43130->dais[dai->id].dai_mode == SND_SOC_DAIFMT_CBM_CFM)
		/* Calculate SCLK in master mode अगर unasचिन्हित */
		sclk = params_rate(params) * bitwidth_dai *
		       params_channels(params);

	अगर (!sclk) अणु
		/* at this poपूर्णांक, SCLK must be set */
		dev_err(component->dev, "SCLK freq is not set\n");
		वापस -EINVAL;
	पूर्ण

	bitwidth_sclk = (sclk / params_rate(params)) / params_channels(params);
	अगर (bitwidth_sclk < bitwidth_dai) अणु
		dev_err(component->dev, "Format not supported: SCLK freq is too low\n");
		वापस -EINVAL;
	पूर्ण

	dev_dbg(component->dev,
		"sclk = %u, fs = %d, bitwidth_dai = %u\n",
		sclk, params_rate(params), bitwidth_dai);

	dev_dbg(component->dev,
		"bitwidth_sclk = %u, num_ch = %u\n",
		bitwidth_sclk, params_channels(params));

	cs43130_set_bitwidth(dai->id, bitwidth_dai, cs43130->regmap);
	cs43130_set_sp_fmt(dai->id, bitwidth_sclk, params, cs43130);

	वापस 0;
पूर्ण

अटल पूर्णांक cs43130_hw_मुक्त(काष्ठा snd_pcm_substream *substream,
			   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा cs43130_निजी *cs43130 = snd_soc_component_get_drvdata(component);

	mutex_lock(&cs43130->clk_mutex);
	cs43130->clk_req--;
	अगर (!cs43130->clk_req) अणु
		/* no DAI is currently using clk */
		cs43130_change_clksrc(component, CS43130_MCLK_SRC_RCO);
		cs43130_pcm_dsd_mix(false, cs43130->regmap);
	पूर्ण
	mutex_unlock(&cs43130->clk_mutex);

	वापस 0;
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(pcm_vol_tlv, -12750, 50, 1);

अटल स्थिर अक्षर * स्थिर pcm_ch_text[] = अणु
	"Left-Right Ch",
	"Left-Left Ch",
	"Right-Left Ch",
	"Right-Right Ch",
पूर्ण;

अटल स्थिर काष्ठा reg_sequence pcm_ch_en_seq[] = अणु
	अणुCS43130_DXD1, 0x99पूर्ण,
	अणु0x180005, 0x8Cपूर्ण,
	अणु0x180007, 0xABपूर्ण,
	अणु0x180015, 0x31पूर्ण,
	अणु0x180017, 0xB2पूर्ण,
	अणु0x180025, 0x30पूर्ण,
	अणु0x180027, 0x84पूर्ण,
	अणु0x180035, 0x9Cपूर्ण,
	अणु0x180037, 0xAEपूर्ण,
	अणु0x18000D, 0x24पूर्ण,
	अणु0x18000F, 0xA3पूर्ण,
	अणु0x18001D, 0x05पूर्ण,
	अणु0x18001F, 0xD4पूर्ण,
	अणु0x18002D, 0x0Bपूर्ण,
	अणु0x18002F, 0xC7पूर्ण,
	अणु0x18003D, 0x71पूर्ण,
	अणु0x18003F, 0xE7पूर्ण,
	अणुCS43130_DXD1, 0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_sequence pcm_ch_dis_seq[] = अणु
	अणुCS43130_DXD1, 0x99पूर्ण,
	अणु0x180005, 0x24पूर्ण,
	अणु0x180007, 0xA3पूर्ण,
	अणु0x180015, 0x05पूर्ण,
	अणु0x180017, 0xD4पूर्ण,
	अणु0x180025, 0x0Bपूर्ण,
	अणु0x180027, 0xC7पूर्ण,
	अणु0x180035, 0x71पूर्ण,
	अणु0x180037, 0xE7पूर्ण,
	अणु0x18000D, 0x8Cपूर्ण,
	अणु0x18000F, 0xABपूर्ण,
	अणु0x18001D, 0x31पूर्ण,
	अणु0x18001F, 0xB2पूर्ण,
	अणु0x18002D, 0x30पूर्ण,
	अणु0x18002F, 0x84पूर्ण,
	अणु0x18003D, 0x9Cपूर्ण,
	अणु0x18003F, 0xAEपूर्ण,
	अणुCS43130_DXD1, 0पूर्ण,
पूर्ण;

अटल पूर्णांक cs43130_pcm_ch_get(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	वापस snd_soc_get_क्रमागत_द्विगुन(kcontrol, ucontrol);
पूर्ण

अटल पूर्णांक cs43130_pcm_ch_put(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक *item = ucontrol->value.क्रमागतerated.item;
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा cs43130_निजी *cs43130 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक val;

	अगर (item[0] >= e->items)
		वापस -EINVAL;
	val = snd_soc_क्रमागत_item_to_val(e, item[0]) << e->shअगरt_l;

	चयन (cs43130->dev_id) अणु
	हाल CS43131_CHIP_ID:
	हाल CS43198_CHIP_ID:
		अगर (val >= 2)
			regmap_multi_reg_ग_लिखो(cs43130->regmap, pcm_ch_en_seq,
					       ARRAY_SIZE(pcm_ch_en_seq));
		अन्यथा
			regmap_multi_reg_ग_लिखो(cs43130->regmap, pcm_ch_dis_seq,
					       ARRAY_SIZE(pcm_ch_dis_seq));
		अवरोध;
	पूर्ण

	वापस snd_soc_put_क्रमागत_द्विगुन(kcontrol, ucontrol);
पूर्ण

अटल SOC_ENUM_SINGLE_DECL(pcm_ch_क्रमागत, CS43130_PCM_PATH_CTL_2, 0,
			    pcm_ch_text);

अटल स्थिर अक्षर * स्थिर pcm_spd_texts[] = अणु
	"Fast",
	"Slow",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(pcm_spd_क्रमागत, CS43130_PCM_FILT_OPT, 7,
			    pcm_spd_texts);

अटल स्थिर अक्षर * स्थिर dsd_texts[] = अणु
	"Off",
	"BCKA Mode",
	"BCKD Mode",
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक dsd_values[] = अणु
	CS43130_DSD_SRC_DSD,
	CS43130_DSD_SRC_ASP,
	CS43130_DSD_SRC_XSP,
पूर्ण;

अटल SOC_VALUE_ENUM_SINGLE_DECL(dsd_क्रमागत, CS43130_DSD_INT_CFG, 0, 0x03,
				  dsd_texts, dsd_values);

अटल स्थिर काष्ठा snd_kcontrol_new cs43130_snd_controls[] = अणु
	SOC_DOUBLE_R_TLV("Master Playback Volume",
			 CS43130_PCM_VOL_A, CS43130_PCM_VOL_B, 0, 0xFF, 1,
			 pcm_vol_tlv),
	SOC_DOUBLE_R_TLV("Master DSD Playback Volume",
			 CS43130_DSD_VOL_A, CS43130_DSD_VOL_B, 0, 0xFF, 1,
			 pcm_vol_tlv),
	SOC_ENUM_EXT("PCM Ch Select", pcm_ch_क्रमागत, cs43130_pcm_ch_get,
		     cs43130_pcm_ch_put),
	SOC_ENUM("PCM Filter Speed", pcm_spd_क्रमागत),
	SOC_SINGLE("PCM Phase Compensation", CS43130_PCM_FILT_OPT, 6, 1, 0),
	SOC_SINGLE("PCM Nonoversample Emulate", CS43130_PCM_FILT_OPT, 5, 1, 0),
	SOC_SINGLE("PCM High-pass Filter", CS43130_PCM_FILT_OPT, 1, 1, 0),
	SOC_SINGLE("PCM De-emphasis Filter", CS43130_PCM_FILT_OPT, 0, 1, 0),
	SOC_ENUM("DSD Phase Modulation", dsd_क्रमागत),
पूर्ण;

अटल स्थिर काष्ठा reg_sequence pcm_seq[] = अणु
	अणुCS43130_DXD1, 0x99पूर्ण,
	अणुCS43130_DXD7, 0x01पूर्ण,
	अणुCS43130_DXD8, 0पूर्ण,
	अणुCS43130_DXD9, 0x01पूर्ण,
	अणुCS43130_DXD3, 0x12पूर्ण,
	अणुCS43130_DXD4, 0पूर्ण,
	अणुCS43130_DXD10, 0x28पूर्ण,
	अणुCS43130_DXD11, 0x28पूर्ण,
	अणुCS43130_DXD1, 0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_sequence dsd_seq[] = अणु
	अणुCS43130_DXD1, 0x99पूर्ण,
	अणुCS43130_DXD7, 0x01पूर्ण,
	अणुCS43130_DXD8, 0पूर्ण,
	अणुCS43130_DXD9, 0x01पूर्ण,
	अणुCS43130_DXD3, 0x12पूर्ण,
	अणुCS43130_DXD4, 0पूर्ण,
	अणुCS43130_DXD10, 0x1Eपूर्ण,
	अणुCS43130_DXD11, 0x20पूर्ण,
	अणुCS43130_DXD1, 0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_sequence pop_मुक्त_seq[] = अणु
	अणुCS43130_DXD1, 0x99पूर्ण,
	अणुCS43130_DXD12, 0x0Aपूर्ण,
	अणुCS43130_DXD1, 0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_sequence pop_मुक्त_seq2[] = अणु
	अणुCS43130_DXD1, 0x99पूर्ण,
	अणुCS43130_DXD13, 0x20पूर्ण,
	अणुCS43130_DXD1, 0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_sequence mute_seq[] = अणु
	अणुCS43130_DXD1, 0x99पूर्ण,
	अणुCS43130_DXD3, 0x12पूर्ण,
	अणुCS43130_DXD5, 0x02पूर्ण,
	अणुCS43130_DXD4, 0x12पूर्ण,
	अणुCS43130_DXD1, 0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_sequence unmute_seq[] = अणु
	अणुCS43130_DXD1, 0x99पूर्ण,
	अणुCS43130_DXD3, 0x10पूर्ण,
	अणुCS43130_DXD5, 0पूर्ण,
	अणुCS43130_DXD4, 0x16पूर्ण,
	अणुCS43130_DXD1, 0पूर्ण,
पूर्ण;

अटल पूर्णांक cs43130_dsd_event(काष्ठा snd_soc_dapm_widget *w,
			      काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा cs43130_निजी *cs43130 = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		चयन (cs43130->dev_id) अणु
		हाल CS43130_CHIP_ID:
		हाल CS4399_CHIP_ID:
			regmap_multi_reg_ग_लिखो(cs43130->regmap, dsd_seq,
					       ARRAY_SIZE(dsd_seq));
			अवरोध;
		पूर्ण
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMU:
		regmap_update_bits(cs43130->regmap, CS43130_DSD_PATH_CTL_1,
				   CS43130_MUTE_MASK, 0);
		चयन (cs43130->dev_id) अणु
		हाल CS43130_CHIP_ID:
		हाल CS4399_CHIP_ID:
			regmap_multi_reg_ग_लिखो(cs43130->regmap, unmute_seq,
					       ARRAY_SIZE(unmute_seq));
			अवरोध;
		पूर्ण
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		चयन (cs43130->dev_id) अणु
		हाल CS43130_CHIP_ID:
		हाल CS4399_CHIP_ID:
			regmap_multi_reg_ग_लिखो(cs43130->regmap, mute_seq,
					       ARRAY_SIZE(mute_seq));
			regmap_update_bits(cs43130->regmap,
					   CS43130_DSD_PATH_CTL_1,
					   CS43130_MUTE_MASK, CS43130_MUTE_EN);
			/*
			 * DSD Power Down Sequence
			 * According to Design, 130ms is preferred.
			 */
			msleep(130);
			अवरोध;
		हाल CS43131_CHIP_ID:
		हाल CS43198_CHIP_ID:
			regmap_update_bits(cs43130->regmap,
					   CS43130_DSD_PATH_CTL_1,
					   CS43130_MUTE_MASK, CS43130_MUTE_EN);
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid event = 0x%x\n", event);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cs43130_pcm_event(काष्ठा snd_soc_dapm_widget *w,
			      काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा cs43130_निजी *cs43130 = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		चयन (cs43130->dev_id) अणु
		हाल CS43130_CHIP_ID:
		हाल CS4399_CHIP_ID:
			regmap_multi_reg_ग_लिखो(cs43130->regmap, pcm_seq,
					       ARRAY_SIZE(pcm_seq));
			अवरोध;
		पूर्ण
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMU:
		regmap_update_bits(cs43130->regmap, CS43130_PCM_PATH_CTL_1,
				   CS43130_MUTE_MASK, 0);
		चयन (cs43130->dev_id) अणु
		हाल CS43130_CHIP_ID:
		हाल CS4399_CHIP_ID:
			regmap_multi_reg_ग_लिखो(cs43130->regmap, unmute_seq,
					       ARRAY_SIZE(unmute_seq));
			अवरोध;
		पूर्ण
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		चयन (cs43130->dev_id) अणु
		हाल CS43130_CHIP_ID:
		हाल CS4399_CHIP_ID:
			regmap_multi_reg_ग_लिखो(cs43130->regmap, mute_seq,
					       ARRAY_SIZE(mute_seq));
			regmap_update_bits(cs43130->regmap,
					   CS43130_PCM_PATH_CTL_1,
					   CS43130_MUTE_MASK, CS43130_MUTE_EN);
			/*
			 * PCM Power Down Sequence
			 * According to Design, 130ms is preferred.
			 */
			msleep(130);
			अवरोध;
		हाल CS43131_CHIP_ID:
		हाल CS43198_CHIP_ID:
			regmap_update_bits(cs43130->regmap,
					   CS43130_PCM_PATH_CTL_1,
					   CS43130_MUTE_MASK, CS43130_MUTE_EN);
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid event = 0x%x\n", event);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा reg_sequence dac_postpmu_seq[] = अणु
	अणुCS43130_DXD9, 0x0Cपूर्ण,
	अणुCS43130_DXD3, 0x10पूर्ण,
	अणुCS43130_DXD4, 0x20पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_sequence dac_postpmd_seq[] = अणु
	अणुCS43130_DXD1, 0x99पूर्ण,
	अणुCS43130_DXD6, 0x01पूर्ण,
	अणुCS43130_DXD1, 0पूर्ण,
पूर्ण;

अटल पूर्णांक cs43130_dac_event(काष्ठा snd_soc_dapm_widget *w,
			     काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा cs43130_निजी *cs43130 = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		चयन (cs43130->dev_id) अणु
		हाल CS43130_CHIP_ID:
		हाल CS4399_CHIP_ID:
			regmap_multi_reg_ग_लिखो(cs43130->regmap, pop_मुक्त_seq,
					       ARRAY_SIZE(pop_मुक्त_seq));
			अवरोध;
		हाल CS43131_CHIP_ID:
		हाल CS43198_CHIP_ID:
			regmap_multi_reg_ग_लिखो(cs43130->regmap, pop_मुक्त_seq2,
					       ARRAY_SIZE(pop_मुक्त_seq2));
			अवरोध;
		पूर्ण
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMU:
		usleep_range(10000, 10050);

		regmap_ग_लिखो(cs43130->regmap, CS43130_DXD1, 0x99);

		चयन (cs43130->dev_id) अणु
		हाल CS43130_CHIP_ID:
		हाल CS4399_CHIP_ID:
			regmap_multi_reg_ग_लिखो(cs43130->regmap, dac_postpmu_seq,
					       ARRAY_SIZE(dac_postpmu_seq));
			/*
			 * Per datasheet, Sec. PCM Power-Up Sequence.
			 * According to Design, CS43130_DXD12 must be 0 to meet
			 * THDN and Dynamic Range spec.
			 */
			msleep(1000);
			regmap_ग_लिखो(cs43130->regmap, CS43130_DXD12, 0);
			अवरोध;
		हाल CS43131_CHIP_ID:
		हाल CS43198_CHIP_ID:
			usleep_range(12000, 12010);
			regmap_ग_लिखो(cs43130->regmap, CS43130_DXD13, 0);
			अवरोध;
		पूर्ण

		regmap_ग_लिखो(cs43130->regmap, CS43130_DXD1, 0);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		चयन (cs43130->dev_id) अणु
		हाल CS43130_CHIP_ID:
		हाल CS4399_CHIP_ID:
			regmap_multi_reg_ग_लिखो(cs43130->regmap, dac_postpmd_seq,
					       ARRAY_SIZE(dac_postpmd_seq));
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid DAC event = 0x%x\n", event);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा reg_sequence hpin_prepmd_seq[] = अणु
	अणुCS43130_DXD1, 0x99पूर्ण,
	अणुCS43130_DXD15, 0x64पूर्ण,
	अणुCS43130_DXD14, 0पूर्ण,
	अणुCS43130_DXD2, 0पूर्ण,
	अणुCS43130_DXD1, 0पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_sequence hpin_postpmu_seq[] = अणु
	अणुCS43130_DXD1, 0x99पूर्ण,
	अणुCS43130_DXD2, 1पूर्ण,
	अणुCS43130_DXD14, 0xDCपूर्ण,
	अणुCS43130_DXD15, 0xE4पूर्ण,
	अणुCS43130_DXD1, 0पूर्ण,
पूर्ण;

अटल पूर्णांक cs43130_hpin_event(काष्ठा snd_soc_dapm_widget *w,
			      काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा cs43130_निजी *cs43130 = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMD:
		regmap_multi_reg_ग_लिखो(cs43130->regmap, hpin_prepmd_seq,
				       ARRAY_SIZE(hpin_prepmd_seq));
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMU:
		regmap_multi_reg_ग_लिखो(cs43130->regmap, hpin_postpmu_seq,
				       ARRAY_SIZE(hpin_postpmu_seq));
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid HPIN event = 0x%x\n", event);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget digital_hp_widमाला_लो[] = अणु
	SND_SOC_DAPM_OUTPUT("HPOUTA"),
	SND_SOC_DAPM_OUTPUT("HPOUTB"),

	SND_SOC_DAPM_AIF_IN_E("ASPIN PCM", शून्य, 0, CS43130_PWDN_CTL,
			      CS43130_PDN_ASP_SHIFT, 1, cs43130_pcm_event,
			      (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			       SND_SOC_DAPM_PRE_PMD)),

	SND_SOC_DAPM_AIF_IN_E("ASPIN DoP", शून्य, 0, CS43130_PWDN_CTL,
			      CS43130_PDN_ASP_SHIFT, 1, cs43130_dsd_event,
			      (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			       SND_SOC_DAPM_PRE_PMD)),

	SND_SOC_DAPM_AIF_IN_E("XSPIN DoP", शून्य, 0, CS43130_PWDN_CTL,
			      CS43130_PDN_XSP_SHIFT, 1, cs43130_dsd_event,
			      (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			       SND_SOC_DAPM_PRE_PMD)),

	SND_SOC_DAPM_AIF_IN_E("XSPIN DSD", शून्य, 0, CS43130_PWDN_CTL,
			      CS43130_PDN_DSDIF_SHIFT, 1, cs43130_dsd_event,
			      (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			       SND_SOC_DAPM_PRE_PMD)),

	SND_SOC_DAPM_DAC("DSD", शून्य, CS43130_DSD_PATH_CTL_2,
			 CS43130_DSD_EN_SHIFT, 0),

	SND_SOC_DAPM_DAC_E("HiFi DAC", शून्य, CS43130_PWDN_CTL,
			   CS43130_PDN_HP_SHIFT, 1, cs43130_dac_event,
			   (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
			    SND_SOC_DAPM_POST_PMD)),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget analog_hp_widमाला_लो[] = अणु
	SND_SOC_DAPM_DAC_E("Analog Playback", शून्य, CS43130_HP_OUT_CTL_1,
			   CS43130_HP_IN_EN_SHIFT, 0, cs43130_hpin_event,
			   (SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD)),
पूर्ण;

अटल काष्ठा snd_soc_dapm_widget all_hp_widमाला_लो[
			ARRAY_SIZE(digital_hp_widमाला_लो) +
			ARRAY_SIZE(analog_hp_widमाला_लो)];

अटल स्थिर काष्ठा snd_soc_dapm_route digital_hp_routes[] = अणु
	अणु"ASPIN PCM", शून्य, "ASP PCM Playback"पूर्ण,
	अणु"ASPIN DoP", शून्य, "ASP DoP Playback"पूर्ण,
	अणु"XSPIN DoP", शून्य, "XSP DoP Playback"पूर्ण,
	अणु"XSPIN DSD", शून्य, "XSP DSD Playback"पूर्ण,
	अणु"DSD", शून्य, "ASPIN DoP"पूर्ण,
	अणु"DSD", शून्य, "XSPIN DoP"पूर्ण,
	अणु"DSD", शून्य, "XSPIN DSD"पूर्ण,
	अणु"HiFi DAC", शून्य, "ASPIN PCM"पूर्ण,
	अणु"HiFi DAC", शून्य, "DSD"पूर्ण,
	अणु"HPOUTA", शून्य, "HiFi DAC"पूर्ण,
	अणु"HPOUTB", शून्य, "HiFi DAC"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route analog_hp_routes[] = अणु
	अणु"HPOUTA", शून्य, "Analog Playback"पूर्ण,
	अणु"HPOUTB", शून्य, "Analog Playback"पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_dapm_route all_hp_routes[
			ARRAY_SIZE(digital_hp_routes) +
			ARRAY_SIZE(analog_hp_routes)];

अटल स्थिर अचिन्हित पूर्णांक cs43130_asp_src_rates[] = अणु
	32000, 44100, 48000, 88200, 96000, 176400, 192000, 352800, 384000
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list cs43130_asp_स्थिरraपूर्णांकs = अणु
	.count	= ARRAY_SIZE(cs43130_asp_src_rates),
	.list	= cs43130_asp_src_rates,
पूर्ण;

अटल पूर्णांक cs43130_pcm_startup(काष्ठा snd_pcm_substream *substream,
			       काष्ठा snd_soc_dai *dai)
अणु
	वापस snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
					  SNDRV_PCM_HW_PARAM_RATE,
					  &cs43130_asp_स्थिरraपूर्णांकs);
पूर्ण

अटल स्थिर अचिन्हित पूर्णांक cs43130_करोp_src_rates[] = अणु
	176400, 352800,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list cs43130_करोp_स्थिरraपूर्णांकs = अणु
	.count	= ARRAY_SIZE(cs43130_करोp_src_rates),
	.list	= cs43130_करोp_src_rates,
पूर्ण;

अटल पूर्णांक cs43130_करोp_startup(काष्ठा snd_pcm_substream *substream,
			       काष्ठा snd_soc_dai *dai)
अणु
	वापस snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
					  SNDRV_PCM_HW_PARAM_RATE,
					  &cs43130_करोp_स्थिरraपूर्णांकs);
पूर्ण

अटल पूर्णांक cs43130_pcm_set_fmt(काष्ठा snd_soc_dai *codec_dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा cs43130_निजी *cs43130 = snd_soc_component_get_drvdata(component);

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		cs43130->dais[codec_dai->id].dai_mode = SND_SOC_DAIFMT_CBS_CFS;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFM:
		cs43130->dais[codec_dai->id].dai_mode = SND_SOC_DAIFMT_CBM_CFM;
		अवरोध;
	शेष:
		dev_err(component->dev, "unsupported mode\n");
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		cs43130->dais[codec_dai->id].dai_क्रमmat = SND_SOC_DAIFMT_I2S;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		cs43130->dais[codec_dai->id].dai_क्रमmat = SND_SOC_DAIFMT_LEFT_J;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		cs43130->dais[codec_dai->id].dai_क्रमmat = SND_SOC_DAIFMT_DSP_A;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		cs43130->dais[codec_dai->id].dai_क्रमmat = SND_SOC_DAIFMT_DSP_B;
		अवरोध;
	शेष:
		dev_err(component->dev,
			"unsupported audio format\n");
		वापस -EINVAL;
	पूर्ण

	dev_dbg(component->dev, "dai_id = %d,  dai_mode = %u, dai_format = %u\n",
		codec_dai->id,
		cs43130->dais[codec_dai->id].dai_mode,
		cs43130->dais[codec_dai->id].dai_क्रमmat);

	वापस 0;
पूर्ण

अटल पूर्णांक cs43130_dsd_set_fmt(काष्ठा snd_soc_dai *codec_dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा cs43130_निजी *cs43130 = snd_soc_component_get_drvdata(component);

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		cs43130->dais[codec_dai->id].dai_mode = SND_SOC_DAIFMT_CBS_CFS;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFM:
		cs43130->dais[codec_dai->id].dai_mode = SND_SOC_DAIFMT_CBM_CFM;
		अवरोध;
	शेष:
		dev_err(component->dev, "Unsupported DAI format.\n");
		वापस -EINVAL;
	पूर्ण

	dev_dbg(component->dev, "dai_mode = 0x%x\n",
		cs43130->dais[codec_dai->id].dai_mode);

	वापस 0;
पूर्ण

अटल पूर्णांक cs43130_set_sysclk(काष्ठा snd_soc_dai *codec_dai,
				  पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा cs43130_निजी *cs43130 = snd_soc_component_get_drvdata(component);

	cs43130->dais[codec_dai->id].sclk = freq;
	dev_dbg(component->dev, "dai_id = %d,  sclk = %u\n", codec_dai->id,
		cs43130->dais[codec_dai->id].sclk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops cs43130_pcm_ops = अणु
	.startup	= cs43130_pcm_startup,
	.hw_params	= cs43130_hw_params,
	.hw_मुक्त	= cs43130_hw_मुक्त,
	.set_sysclk	= cs43130_set_sysclk,
	.set_fmt	= cs43130_pcm_set_fmt,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops cs43130_करोp_ops = अणु
	.startup	= cs43130_करोp_startup,
	.hw_params	= cs43130_hw_params,
	.hw_मुक्त	= cs43130_hw_मुक्त,
	.set_sysclk	= cs43130_set_sysclk,
	.set_fmt	= cs43130_pcm_set_fmt,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops cs43130_dsd_ops = अणु
	.startup        = cs43130_करोp_startup,
	.hw_params	= cs43130_dsd_hw_params,
	.hw_मुक्त	= cs43130_hw_मुक्त,
	.set_fmt	= cs43130_dsd_set_fmt,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver cs43130_dai[] = अणु
	अणु
		.name = "cs43130-asp-pcm",
		.id = CS43130_ASP_PCM_DAI,
		.playback = अणु
			.stream_name = "ASP PCM Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_KNOT,
			.क्रमmats = CS43130_PCM_FORMATS,
		पूर्ण,
		.ops = &cs43130_pcm_ops,
		.symmetric_rate = 1,
	पूर्ण,
	अणु
		.name = "cs43130-asp-dop",
		.id = CS43130_ASP_DOP_DAI,
		.playback = अणु
			.stream_name = "ASP DoP Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_KNOT,
			.क्रमmats = CS43130_DOP_FORMATS,
		पूर्ण,
		.ops = &cs43130_करोp_ops,
		.symmetric_rate = 1,
	पूर्ण,
	अणु
		.name = "cs43130-xsp-dop",
		.id = CS43130_XSP_DOP_DAI,
		.playback = अणु
			.stream_name = "XSP DoP Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_KNOT,
			.क्रमmats = CS43130_DOP_FORMATS,
		पूर्ण,
		.ops = &cs43130_करोp_ops,
		.symmetric_rate = 1,
	पूर्ण,
	अणु
		.name = "cs43130-xsp-dsd",
		.id = CS43130_XSP_DSD_DAI,
		.playback = अणु
			.stream_name = "XSP DSD Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_KNOT,
			.क्रमmats = CS43130_DOP_FORMATS,
		पूर्ण,
		.ops = &cs43130_dsd_ops,
	पूर्ण,

पूर्ण;

अटल पूर्णांक cs43130_component_set_sysclk(काष्ठा snd_soc_component *component,
				    पूर्णांक clk_id, पूर्णांक source, अचिन्हित पूर्णांक freq,
				    पूर्णांक dir)
अणु
	काष्ठा cs43130_निजी *cs43130 = snd_soc_component_get_drvdata(component);

	dev_dbg(component->dev, "clk_id = %d, source = %d, freq = %d, dir = %d\n",
		clk_id, source, freq, dir);

	चयन (freq) अणु
	हाल CS43130_MCLK_22M:
	हाल CS43130_MCLK_24M:
		cs43130->mclk = freq;
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid MCLK INT freq: %u\n", freq);
		वापस -EINVAL;
	पूर्ण

	अगर (source == CS43130_MCLK_SRC_EXT) अणु
		cs43130->pll_bypass = true;
	पूर्ण अन्यथा अणु
		dev_err(component->dev, "Invalid MCLK source\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत u16 cs43130_get_ac_reg_val(u16 ac_freq)
अणु
	/* AC freq is counted in 5.94Hz step. */
	वापस ac_freq / 6;
पूर्ण

अटल पूर्णांक cs43130_show_dc(काष्ठा device *dev, अक्षर *buf, u8 ch)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा cs43130_निजी *cs43130 = i2c_get_clientdata(client);

	अगर (!cs43130->hpload_करोne)
		वापस scnम_लिखो(buf, PAGE_SIZE, "NO_HPLOAD\n");
	अन्यथा
		वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n",
				 cs43130->hpload_dc[ch]);
पूर्ण

अटल sमाप_प्रकार cs43130_show_dc_l(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस cs43130_show_dc(dev, buf, HP_LEFT);
पूर्ण

अटल sमाप_प्रकार cs43130_show_dc_r(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस cs43130_show_dc(dev, buf, HP_RIGHT);
पूर्ण

अटल u16 स्थिर cs43130_ac_freq[CS43130_AC_FREQ] = अणु
	24,
	43,
	93,
	200,
	431,
	928,
	2000,
	4309,
	9283,
	20000,
पूर्ण;

अटल पूर्णांक cs43130_show_ac(काष्ठा device *dev, अक्षर *buf, u8 ch)
अणु
	पूर्णांक i, j = 0, पंचांगp;
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा cs43130_निजी *cs43130 = i2c_get_clientdata(client);

	अगर (cs43130->hpload_करोne && cs43130->ac_meas) अणु
		क्रम (i = 0; i < ARRAY_SIZE(cs43130_ac_freq); i++) अणु
			पंचांगp = scnम_लिखो(buf + j, PAGE_SIZE - j, "%u\n",
					cs43130->hpload_ac[i][ch]);
			अगर (!पंचांगp)
				अवरोध;

			j += पंचांगp;
		पूर्ण

		वापस j;
	पूर्ण अन्यथा अणु
		वापस scnम_लिखो(buf, PAGE_SIZE, "NO_HPLOAD\n");
	पूर्ण
पूर्ण

अटल sमाप_प्रकार cs43130_show_ac_l(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस cs43130_show_ac(dev, buf, HP_LEFT);
पूर्ण

अटल sमाप_प्रकार cs43130_show_ac_r(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस cs43130_show_ac(dev, buf, HP_RIGHT);
पूर्ण

अटल DEVICE_ATTR(hpload_dc_l, 0444, cs43130_show_dc_l, शून्य);
अटल DEVICE_ATTR(hpload_dc_r, 0444, cs43130_show_dc_r, शून्य);
अटल DEVICE_ATTR(hpload_ac_l, 0444, cs43130_show_ac_l, शून्य);
अटल DEVICE_ATTR(hpload_ac_r, 0444, cs43130_show_ac_r, शून्य);

अटल काष्ठा attribute *hpload_attrs[] = अणु
	&dev_attr_hpload_dc_l.attr,
	&dev_attr_hpload_dc_r.attr,
	&dev_attr_hpload_ac_l.attr,
	&dev_attr_hpload_ac_r.attr,
पूर्ण;
ATTRIBUTE_GROUPS(hpload);

अटल काष्ठा reg_sequence hp_en_cal_seq[] = अणु
	अणुCS43130_INT_MASK_4, CS43130_INT_MASK_ALLपूर्ण,
	अणुCS43130_HP_MEAS_LOAD_1, 0पूर्ण,
	अणुCS43130_HP_MEAS_LOAD_2, 0पूर्ण,
	अणुCS43130_INT_MASK_4, 0पूर्ण,
	अणुCS43130_DXD1, 0x99पूर्ण,
	अणुCS43130_DXD16, 0xBBपूर्ण,
	अणुCS43130_DXD12, 0x01पूर्ण,
	अणुCS43130_DXD19, 0xCBपूर्ण,
	अणुCS43130_DXD17, 0x95पूर्ण,
	अणुCS43130_DXD18, 0x0Bपूर्ण,
	अणुCS43130_DXD1, 0पूर्ण,
	अणुCS43130_HP_LOAD_1, 0x80पूर्ण,
पूर्ण;

अटल काष्ठा reg_sequence hp_en_cal_seq2[] = अणु
	अणुCS43130_INT_MASK_4, CS43130_INT_MASK_ALLपूर्ण,
	अणुCS43130_HP_MEAS_LOAD_1, 0पूर्ण,
	अणुCS43130_HP_MEAS_LOAD_2, 0पूर्ण,
	अणुCS43130_INT_MASK_4, 0पूर्ण,
	अणुCS43130_HP_LOAD_1, 0x80पूर्ण,
पूर्ण;

अटल काष्ठा reg_sequence hp_dis_cal_seq[] = अणु
	अणुCS43130_HP_LOAD_1, 0x80पूर्ण,
	अणुCS43130_DXD1, 0x99पूर्ण,
	अणुCS43130_DXD12, 0पूर्ण,
	अणुCS43130_DXD1, 0पूर्ण,
	अणुCS43130_HP_LOAD_1, 0पूर्ण,
पूर्ण;

अटल काष्ठा reg_sequence hp_dis_cal_seq2[] = अणु
	अणुCS43130_HP_LOAD_1, 0x80पूर्ण,
	अणुCS43130_HP_LOAD_1, 0पूर्ण,
पूर्ण;

अटल काष्ठा reg_sequence hp_dc_ch_l_seq[] = अणु
	अणुCS43130_DXD1, 0x99पूर्ण,
	अणुCS43130_DXD19, 0x0Aपूर्ण,
	अणुCS43130_DXD17, 0x93पूर्ण,
	अणुCS43130_DXD18, 0x0Aपूर्ण,
	अणुCS43130_DXD1, 0पूर्ण,
	अणुCS43130_HP_LOAD_1, 0x80पूर्ण,
	अणुCS43130_HP_LOAD_1, 0x81पूर्ण,
पूर्ण;

अटल काष्ठा reg_sequence hp_dc_ch_l_seq2[] = अणु
	अणुCS43130_HP_LOAD_1, 0x80पूर्ण,
	अणुCS43130_HP_LOAD_1, 0x81पूर्ण,
पूर्ण;

अटल काष्ठा reg_sequence hp_dc_ch_r_seq[] = अणु
	अणुCS43130_DXD1, 0x99पूर्ण,
	अणुCS43130_DXD19, 0x8Aपूर्ण,
	अणुCS43130_DXD17, 0x15पूर्ण,
	अणुCS43130_DXD18, 0x06पूर्ण,
	अणुCS43130_DXD1, 0पूर्ण,
	अणुCS43130_HP_LOAD_1, 0x90पूर्ण,
	अणुCS43130_HP_LOAD_1, 0x91पूर्ण,
पूर्ण;

अटल काष्ठा reg_sequence hp_dc_ch_r_seq2[] = अणु
	अणुCS43130_HP_LOAD_1, 0x90पूर्ण,
	अणुCS43130_HP_LOAD_1, 0x91पूर्ण,
पूर्ण;

अटल काष्ठा reg_sequence hp_ac_ch_l_seq[] = अणु
	अणुCS43130_DXD1, 0x99पूर्ण,
	अणुCS43130_DXD19, 0x0Aपूर्ण,
	अणुCS43130_DXD17, 0x93पूर्ण,
	अणुCS43130_DXD18, 0x0Aपूर्ण,
	अणुCS43130_DXD1, 0पूर्ण,
	अणुCS43130_HP_LOAD_1, 0x80पूर्ण,
	अणुCS43130_HP_LOAD_1, 0x82पूर्ण,
पूर्ण;

अटल काष्ठा reg_sequence hp_ac_ch_l_seq2[] = अणु
	अणुCS43130_HP_LOAD_1, 0x80पूर्ण,
	अणुCS43130_HP_LOAD_1, 0x82पूर्ण,
पूर्ण;

अटल काष्ठा reg_sequence hp_ac_ch_r_seq[] = अणु
	अणुCS43130_DXD1, 0x99पूर्ण,
	अणुCS43130_DXD19, 0x8Aपूर्ण,
	अणुCS43130_DXD17, 0x15पूर्ण,
	अणुCS43130_DXD18, 0x06पूर्ण,
	अणुCS43130_DXD1, 0पूर्ण,
	अणुCS43130_HP_LOAD_1, 0x90पूर्ण,
	अणुCS43130_HP_LOAD_1, 0x92पूर्ण,
पूर्ण;

अटल काष्ठा reg_sequence hp_ac_ch_r_seq2[] = अणु
	अणुCS43130_HP_LOAD_1, 0x90पूर्ण,
	अणुCS43130_HP_LOAD_1, 0x92पूर्ण,
पूर्ण;

अटल काष्ठा reg_sequence hp_cln_seq[] = अणु
	अणुCS43130_INT_MASK_4, CS43130_INT_MASK_ALLपूर्ण,
	अणुCS43130_HP_MEAS_LOAD_1, 0पूर्ण,
	अणुCS43130_HP_MEAS_LOAD_2, 0पूर्ण,
पूर्ण;

काष्ठा reg_sequences अणु
	काष्ठा reg_sequence	*seq;
	पूर्णांक			size;
	अचिन्हित पूर्णांक		msk;
पूर्ण;

अटल काष्ठा reg_sequences hpload_seq1[] = अणु
	अणु
		.seq	= hp_en_cal_seq,
		.size	= ARRAY_SIZE(hp_en_cal_seq),
		.msk	= CS43130_HPLOAD_ON_INT,
	पूर्ण,
	अणु
		.seq	= hp_dc_ch_l_seq,
		.size	= ARRAY_SIZE(hp_dc_ch_l_seq),
		.msk	= CS43130_HPLOAD_DC_INT,
	पूर्ण,
	अणु
		.seq	= hp_ac_ch_l_seq,
		.size	= ARRAY_SIZE(hp_ac_ch_l_seq),
		.msk	= CS43130_HPLOAD_AC_INT,
	पूर्ण,
	अणु
		.seq	= hp_dis_cal_seq,
		.size	= ARRAY_SIZE(hp_dis_cal_seq),
		.msk	= CS43130_HPLOAD_OFF_INT,
	पूर्ण,
	अणु
		.seq	= hp_en_cal_seq,
		.size	= ARRAY_SIZE(hp_en_cal_seq),
		.msk	= CS43130_HPLOAD_ON_INT,
	पूर्ण,
	अणु
		.seq	= hp_dc_ch_r_seq,
		.size	= ARRAY_SIZE(hp_dc_ch_r_seq),
		.msk	= CS43130_HPLOAD_DC_INT,
	पूर्ण,
	अणु
		.seq	= hp_ac_ch_r_seq,
		.size	= ARRAY_SIZE(hp_ac_ch_r_seq),
		.msk	= CS43130_HPLOAD_AC_INT,
	पूर्ण,
पूर्ण;

अटल काष्ठा reg_sequences hpload_seq2[] = अणु
	अणु
		.seq	= hp_en_cal_seq2,
		.size	= ARRAY_SIZE(hp_en_cal_seq2),
		.msk	= CS43130_HPLOAD_ON_INT,
	पूर्ण,
	अणु
		.seq	= hp_dc_ch_l_seq2,
		.size	= ARRAY_SIZE(hp_dc_ch_l_seq2),
		.msk	= CS43130_HPLOAD_DC_INT,
	पूर्ण,
	अणु
		.seq	= hp_ac_ch_l_seq2,
		.size	= ARRAY_SIZE(hp_ac_ch_l_seq2),
		.msk	= CS43130_HPLOAD_AC_INT,
	पूर्ण,
	अणु
		.seq	= hp_dis_cal_seq2,
		.size	= ARRAY_SIZE(hp_dis_cal_seq2),
		.msk	= CS43130_HPLOAD_OFF_INT,
	पूर्ण,
	अणु
		.seq	= hp_en_cal_seq2,
		.size	= ARRAY_SIZE(hp_en_cal_seq2),
		.msk	= CS43130_HPLOAD_ON_INT,
	पूर्ण,
	अणु
		.seq	= hp_dc_ch_r_seq2,
		.size	= ARRAY_SIZE(hp_dc_ch_r_seq2),
		.msk	= CS43130_HPLOAD_DC_INT,
	पूर्ण,
	अणु
		.seq	= hp_ac_ch_r_seq2,
		.size	= ARRAY_SIZE(hp_ac_ch_r_seq2),
		.msk	= CS43130_HPLOAD_AC_INT,
	पूर्ण,
पूर्ण;

अटल पूर्णांक cs43130_update_hpload(अचिन्हित पूर्णांक msk, पूर्णांक ac_idx,
				 काष्ठा cs43130_निजी *cs43130)
अणु
	bool left_ch = true;
	अचिन्हित पूर्णांक reg;
	u32 addr;
	u16 impedance;
	काष्ठा snd_soc_component *component = cs43130->component;

	चयन (msk) अणु
	हाल CS43130_HPLOAD_DC_INT:
	हाल CS43130_HPLOAD_AC_INT:
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	regmap_पढ़ो(cs43130->regmap, CS43130_HP_LOAD_1, &reg);
	अगर (reg & CS43130_HPLOAD_CHN_SEL)
		left_ch = false;

	अगर (msk == CS43130_HPLOAD_DC_INT)
		addr = CS43130_HP_DC_STAT_1;
	अन्यथा
		addr = CS43130_HP_AC_STAT_1;

	regmap_पढ़ो(cs43130->regmap, addr, &reg);
	impedance = reg >> 3;
	regmap_पढ़ो(cs43130->regmap, addr + 1, &reg);
	impedance |= reg << 5;

	अगर (msk == CS43130_HPLOAD_DC_INT) अणु
		अगर (left_ch)
			cs43130->hpload_dc[HP_LEFT] = impedance;
		अन्यथा
			cs43130->hpload_dc[HP_RIGHT] = impedance;

		dev_dbg(component->dev, "HP DC impedance (Ch %u): %u\n", !left_ch,
			impedance);
	पूर्ण अन्यथा अणु
		अगर (left_ch)
			cs43130->hpload_ac[ac_idx][HP_LEFT] = impedance;
		अन्यथा
			cs43130->hpload_ac[ac_idx][HP_RIGHT] = impedance;

		dev_dbg(component->dev, "HP AC (%u Hz) impedance (Ch %u): %u\n",
			cs43130->ac_freq[ac_idx], !left_ch, impedance);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cs43130_hpload_proc(काष्ठा cs43130_निजी *cs43130,
			       काष्ठा reg_sequence *seq, पूर्णांक seq_size,
			       अचिन्हित पूर्णांक rslt_msk, पूर्णांक ac_idx)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक msk;
	u16 ac_reg_val;
	काष्ठा snd_soc_component *component = cs43130->component;

	reinit_completion(&cs43130->hpload_evt);

	अगर (rslt_msk == CS43130_HPLOAD_AC_INT) अणु
		ac_reg_val = cs43130_get_ac_reg_val(cs43130->ac_freq[ac_idx]);
		regmap_update_bits(cs43130->regmap, CS43130_HP_LOAD_1,
				   CS43130_HPLOAD_AC_START, 0);
		regmap_update_bits(cs43130->regmap, CS43130_HP_MEAS_LOAD_1,
				   CS43130_HP_MEAS_LOAD_MASK,
				   ac_reg_val >> CS43130_HP_MEAS_LOAD_1_SHIFT);
		regmap_update_bits(cs43130->regmap, CS43130_HP_MEAS_LOAD_2,
				   CS43130_HP_MEAS_LOAD_MASK,
				   ac_reg_val >> CS43130_HP_MEAS_LOAD_2_SHIFT);
	पूर्ण

	regmap_multi_reg_ग_लिखो(cs43130->regmap, seq,
			       seq_size);

	ret = रुको_क्रम_completion_समयout(&cs43130->hpload_evt,
					  msecs_to_jअगरfies(1000));
	regmap_पढ़ो(cs43130->regmap, CS43130_INT_MASK_4, &msk);
	अगर (!ret) अणु
		dev_err(component->dev, "Timeout waiting for HPLOAD interrupt\n");
		वापस -1;
	पूर्ण

	dev_dbg(component->dev, "HP load stat: %x, INT_MASK_4: %x\n",
		cs43130->hpload_stat, msk);
	अगर ((cs43130->hpload_stat & (CS43130_HPLOAD_NO_DC_INT |
				     CS43130_HPLOAD_UNPLUG_INT |
				     CS43130_HPLOAD_OOR_INT)) ||
	    !(cs43130->hpload_stat & rslt_msk)) अणु
		dev_dbg(component->dev, "HP load measure failed\n");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा reg_sequence hv_seq[][2] = अणु
	अणु
		अणुCS43130_CLASS_H_CTL, 0x1Cपूर्ण,
		अणुCS43130_HP_OUT_CTL_1, 0x10पूर्ण,
	पूर्ण,
	अणु
		अणुCS43130_CLASS_H_CTL, 0x1Eपूर्ण,
		अणुCS43130_HP_OUT_CTL_1, 0x20पूर्ण,
	पूर्ण,
	अणु
		अणुCS43130_CLASS_H_CTL, 0x1Eपूर्ण,
		अणुCS43130_HP_OUT_CTL_1, 0x30पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक cs43130_set_hv(काष्ठा regmap *regmap, u16 hpload_dc,
			  स्थिर u16 *dc_threshold)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < CS43130_DC_THRESHOLD; i++) अणु
		अगर (hpload_dc <= dc_threshold[i])
			अवरोध;
	पूर्ण

	regmap_multi_reg_ग_लिखो(regmap, hv_seq[i], ARRAY_SIZE(hv_seq[i]));

	वापस 0;
पूर्ण

अटल व्योम cs43130_imp_meas(काष्ठा work_काष्ठा *wk)
अणु
	अचिन्हित पूर्णांक reg, seq_size;
	पूर्णांक i, ret, ac_idx;
	काष्ठा cs43130_निजी *cs43130;
	काष्ठा snd_soc_component *component;
	काष्ठा reg_sequences *hpload_seq;

	cs43130 = container_of(wk, काष्ठा cs43130_निजी, work);
	component = cs43130->component;

	अगर (!cs43130->mclk)
		वापस;

	cs43130->hpload_करोne = false;

	mutex_lock(&cs43130->clk_mutex);
	अगर (!cs43130->clk_req) अणु
		/* clk not in use */
		cs43130_set_pll(component, 0, 0, cs43130->mclk, CS43130_MCLK_22M);
		अगर (cs43130->pll_bypass)
			cs43130_change_clksrc(component, CS43130_MCLK_SRC_EXT);
		अन्यथा
			cs43130_change_clksrc(component, CS43130_MCLK_SRC_PLL);
	पूर्ण

	cs43130->clk_req++;
	mutex_unlock(&cs43130->clk_mutex);

	regmap_पढ़ो(cs43130->regmap, CS43130_INT_STATUS_4, &reg);

	चयन (cs43130->dev_id) अणु
	हाल CS43130_CHIP_ID:
		hpload_seq = hpload_seq1;
		seq_size = ARRAY_SIZE(hpload_seq1);
		अवरोध;
	हाल CS43131_CHIP_ID:
		hpload_seq = hpload_seq2;
		seq_size = ARRAY_SIZE(hpload_seq2);
		अवरोध;
	शेष:
		WARN(1, "Invalid dev_id for meas: %d", cs43130->dev_id);
		वापस;
	पूर्ण

	i = 0;
	ac_idx = 0;
	जबतक (i < seq_size) अणु
		ret = cs43130_hpload_proc(cs43130, hpload_seq[i].seq,
					  hpload_seq[i].size,
					  hpload_seq[i].msk, ac_idx);
		अगर (ret < 0)
			जाओ निकास;

		cs43130_update_hpload(hpload_seq[i].msk, ac_idx, cs43130);

		अगर (cs43130->ac_meas &&
		    hpload_seq[i].msk == CS43130_HPLOAD_AC_INT &&
		    ac_idx < CS43130_AC_FREQ - 1) अणु
			ac_idx++;
		पूर्ण अन्यथा अणु
			ac_idx = 0;
			i++;
		पूर्ण
	पूर्ण
	cs43130->hpload_करोne = true;

	अगर (cs43130->hpload_dc[HP_LEFT] >= CS43130_LINEOUT_LOAD)
		snd_soc_jack_report(&cs43130->jack, CS43130_JACK_LINEOUT,
				    CS43130_JACK_MASK);
	अन्यथा
		snd_soc_jack_report(&cs43130->jack, CS43130_JACK_HEADPHONE,
				    CS43130_JACK_MASK);

	dev_dbg(component->dev, "Set HP output control. DC threshold\n");
	क्रम (i = 0; i < CS43130_DC_THRESHOLD; i++)
		dev_dbg(component->dev, "DC threshold[%d]: %u.\n", i,
			cs43130->dc_threshold[i]);

	cs43130_set_hv(cs43130->regmap, cs43130->hpload_dc[HP_LEFT],
		       cs43130->dc_threshold);

निकास:
	चयन (cs43130->dev_id) अणु
	हाल CS43130_CHIP_ID:
		cs43130_hpload_proc(cs43130, hp_dis_cal_seq,
				    ARRAY_SIZE(hp_dis_cal_seq),
				    CS43130_HPLOAD_OFF_INT, ac_idx);
		अवरोध;
	हाल CS43131_CHIP_ID:
		cs43130_hpload_proc(cs43130, hp_dis_cal_seq2,
				    ARRAY_SIZE(hp_dis_cal_seq2),
				    CS43130_HPLOAD_OFF_INT, ac_idx);
		अवरोध;
	पूर्ण

	regmap_multi_reg_ग_लिखो(cs43130->regmap, hp_cln_seq,
			       ARRAY_SIZE(hp_cln_seq));

	mutex_lock(&cs43130->clk_mutex);
	cs43130->clk_req--;
	/* clk not in use */
	अगर (!cs43130->clk_req)
		cs43130_change_clksrc(component, CS43130_MCLK_SRC_RCO);
	mutex_unlock(&cs43130->clk_mutex);
पूर्ण

अटल irqवापस_t cs43130_irq_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा cs43130_निजी *cs43130 = (काष्ठा cs43130_निजी *)data;
	काष्ठा snd_soc_component *component = cs43130->component;
	अचिन्हित पूर्णांक stickies[CS43130_NUM_INT];
	अचिन्हित पूर्णांक irq_occurrence = 0;
	अचिन्हित पूर्णांक masks[CS43130_NUM_INT];
	पूर्णांक i, j;

	क्रम (i = 0; i < ARRAY_SIZE(stickies); i++) अणु
		regmap_पढ़ो(cs43130->regmap, CS43130_INT_STATUS_1 + i,
			    &stickies[i]);
		regmap_पढ़ो(cs43130->regmap, CS43130_INT_MASK_1 + i,
			    &masks[i]);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(stickies); i++) अणु
		stickies[i] = stickies[i] & (~masks[i]);
		क्रम (j = 0; j < 8; j++)
			irq_occurrence += (stickies[i] >> j) & 1;
	पूर्ण
	dev_dbg(component->dev, "number of interrupts occurred (%u)\n",
		irq_occurrence);

	अगर (!irq_occurrence)
		वापस IRQ_NONE;

	अगर (stickies[0] & CS43130_XTAL_RDY_INT) अणु
		complete(&cs43130->xtal_rdy);
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (stickies[0] & CS43130_PLL_RDY_INT) अणु
		complete(&cs43130->pll_rdy);
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (stickies[3] & CS43130_HPLOAD_NO_DC_INT) अणु
		cs43130->hpload_stat = stickies[3];
		dev_err(component->dev,
			"DC load has not completed before AC load (%x)\n",
			cs43130->hpload_stat);
		complete(&cs43130->hpload_evt);
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (stickies[3] & CS43130_HPLOAD_UNPLUG_INT) अणु
		cs43130->hpload_stat = stickies[3];
		dev_err(component->dev, "HP unplugged during measurement (%x)\n",
			cs43130->hpload_stat);
		complete(&cs43130->hpload_evt);
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (stickies[3] & CS43130_HPLOAD_OOR_INT) अणु
		cs43130->hpload_stat = stickies[3];
		dev_err(component->dev, "HP load out of range (%x)\n",
			cs43130->hpload_stat);
		complete(&cs43130->hpload_evt);
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (stickies[3] & CS43130_HPLOAD_AC_INT) अणु
		cs43130->hpload_stat = stickies[3];
		dev_dbg(component->dev, "HP AC load measurement done (%x)\n",
			cs43130->hpload_stat);
		complete(&cs43130->hpload_evt);
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (stickies[3] & CS43130_HPLOAD_DC_INT) अणु
		cs43130->hpload_stat = stickies[3];
		dev_dbg(component->dev, "HP DC load measurement done (%x)\n",
			cs43130->hpload_stat);
		complete(&cs43130->hpload_evt);
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (stickies[3] & CS43130_HPLOAD_ON_INT) अणु
		cs43130->hpload_stat = stickies[3];
		dev_dbg(component->dev, "HP load state machine on done (%x)\n",
			cs43130->hpload_stat);
		complete(&cs43130->hpload_evt);
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (stickies[3] & CS43130_HPLOAD_OFF_INT) अणु
		cs43130->hpload_stat = stickies[3];
		dev_dbg(component->dev, "HP load state machine off done (%x)\n",
			cs43130->hpload_stat);
		complete(&cs43130->hpload_evt);
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (stickies[0] & CS43130_XTAL_ERR_INT) अणु
		dev_err(component->dev, "Crystal err: clock is not running\n");
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (stickies[0] & CS43130_HP_UNPLUG_INT) अणु
		dev_dbg(component->dev, "HP unplugged\n");
		cs43130->hpload_करोne = false;
		snd_soc_jack_report(&cs43130->jack, 0, CS43130_JACK_MASK);
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (stickies[0] & CS43130_HP_PLUG_INT) अणु
		अगर (cs43130->dc_meas && !cs43130->hpload_करोne &&
		    !work_busy(&cs43130->work)) अणु
			dev_dbg(component->dev, "HP load queue work\n");
			queue_work(cs43130->wq, &cs43130->work);
		पूर्ण

		snd_soc_jack_report(&cs43130->jack, SND_JACK_MECHANICAL,
				    CS43130_JACK_MASK);
		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

अटल पूर्णांक cs43130_probe(काष्ठा snd_soc_component *component)
अणु
	पूर्णांक ret;
	काष्ठा cs43130_निजी *cs43130 = snd_soc_component_get_drvdata(component);
	काष्ठा snd_soc_card *card = component->card;
	अचिन्हित पूर्णांक reg;

	cs43130->component = component;

	अगर (cs43130->xtal_ibias != CS43130_XTAL_UNUSED) अणु
		regmap_update_bits(cs43130->regmap, CS43130_CRYSTAL_SET,
				   CS43130_XTAL_IBIAS_MASK,
				   cs43130->xtal_ibias);
		regmap_update_bits(cs43130->regmap, CS43130_INT_MASK_1,
				   CS43130_XTAL_ERR_INT, 0);
	पूर्ण

	ret = snd_soc_card_jack_new(card, "Headphone", CS43130_JACK_MASK,
				    &cs43130->jack, शून्य, 0);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Cannot create jack\n");
		वापस ret;
	पूर्ण

	cs43130->hpload_करोne = false;
	अगर (cs43130->dc_meas) अणु
		ret = sysfs_create_groups(&component->dev->kobj, hpload_groups);
		अगर (ret)
			वापस ret;

		cs43130->wq = create_singlethपढ़ो_workqueue("cs43130_hp");
		अगर (!cs43130->wq) अणु
			sysfs_हटाओ_groups(&component->dev->kobj, hpload_groups);
			वापस -ENOMEM;
		पूर्ण
		INIT_WORK(&cs43130->work, cs43130_imp_meas);
	पूर्ण

	regmap_पढ़ो(cs43130->regmap, CS43130_INT_STATUS_1, &reg);
	regmap_पढ़ो(cs43130->regmap, CS43130_HP_STATUS, &reg);
	regmap_update_bits(cs43130->regmap, CS43130_INT_MASK_1,
			   CS43130_HP_PLUG_INT | CS43130_HP_UNPLUG_INT, 0);
	regmap_update_bits(cs43130->regmap, CS43130_HP_DETECT,
			   CS43130_HP_DETECT_CTRL_MASK, 0);
	regmap_update_bits(cs43130->regmap, CS43130_HP_DETECT,
			   CS43130_HP_DETECT_CTRL_MASK,
			   CS43130_HP_DETECT_CTRL_MASK);

	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_component_driver soc_component_dev_cs43130 = अणु
	.probe			= cs43130_probe,
	.controls		= cs43130_snd_controls,
	.num_controls		= ARRAY_SIZE(cs43130_snd_controls),
	.set_sysclk		= cs43130_component_set_sysclk,
	.set_pll		= cs43130_set_pll,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config cs43130_regmap = अणु
	.reg_bits		= 24,
	.pad_bits		= 8,
	.val_bits		= 8,

	.max_रेजिस्टर		= CS43130_LASTREG,
	.reg_शेषs		= cs43130_reg_शेषs,
	.num_reg_शेषs	= ARRAY_SIZE(cs43130_reg_शेषs),
	.पढ़ोable_reg		= cs43130_पढ़ोable_रेजिस्टर,
	.precious_reg		= cs43130_precious_रेजिस्टर,
	.अस्थिर_reg		= cs43130_अस्थिर_रेजिस्टर,
	.cache_type		= REGCACHE_RBTREE,
	/* needed क्रम regcache_sync */
	.use_single_पढ़ो	= true,
	.use_single_ग_लिखो	= true,
पूर्ण;

अटल u16 स्थिर cs43130_dc_threshold[CS43130_DC_THRESHOLD] = अणु
	50,
	120,
पूर्ण;

अटल पूर्णांक cs43130_handle_device_data(काष्ठा i2c_client *i2c_client,
				      काष्ठा cs43130_निजी *cs43130)
अणु
	काष्ठा device_node *np = i2c_client->dev.of_node;
	अचिन्हित पूर्णांक val;
	पूर्णांक i;

	अगर (of_property_पढ़ो_u32(np, "cirrus,xtal-ibias", &val) < 0) अणु
		/* Crystal is unused. System घड़ी is used क्रम बाह्यal MCLK */
		cs43130->xtal_ibias = CS43130_XTAL_UNUSED;
		वापस 0;
	पूर्ण

	चयन (val) अणु
	हाल 1:
		cs43130->xtal_ibias = CS43130_XTAL_IBIAS_7_5UA;
		अवरोध;
	हाल 2:
		cs43130->xtal_ibias = CS43130_XTAL_IBIAS_12_5UA;
		अवरोध;
	हाल 3:
		cs43130->xtal_ibias = CS43130_XTAL_IBIAS_15UA;
		अवरोध;
	शेष:
		dev_err(&i2c_client->dev,
			"Invalid cirrus,xtal-ibias value: %d\n", val);
		वापस -EINVAL;
	पूर्ण

	cs43130->dc_meas = of_property_पढ़ो_bool(np, "cirrus,dc-measure");
	cs43130->ac_meas = of_property_पढ़ो_bool(np, "cirrus,ac-measure");

	अगर (of_property_पढ़ो_u16_array(np, "cirrus,ac-freq", cs43130->ac_freq,
					CS43130_AC_FREQ) < 0) अणु
		क्रम (i = 0; i < CS43130_AC_FREQ; i++)
			cs43130->ac_freq[i] = cs43130_ac_freq[i];
	पूर्ण

	अगर (of_property_पढ़ो_u16_array(np, "cirrus,dc-threshold",
				       cs43130->dc_threshold,
				       CS43130_DC_THRESHOLD) < 0) अणु
		क्रम (i = 0; i < CS43130_DC_THRESHOLD; i++)
			cs43130->dc_threshold[i] = cs43130_dc_threshold[i];
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cs43130_i2c_probe(काष्ठा i2c_client *client,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा cs43130_निजी *cs43130;
	पूर्णांक ret;
	अचिन्हित पूर्णांक devid = 0;
	अचिन्हित पूर्णांक reg;
	पूर्णांक i;

	cs43130 = devm_kzalloc(&client->dev, माप(*cs43130), GFP_KERNEL);
	अगर (!cs43130)
		वापस -ENOMEM;

	i2c_set_clientdata(client, cs43130);

	cs43130->regmap = devm_regmap_init_i2c(client, &cs43130_regmap);
	अगर (IS_ERR(cs43130->regmap)) अणु
		ret = PTR_ERR(cs43130->regmap);
		वापस ret;
	पूर्ण

	अगर (client->dev.of_node) अणु
		ret = cs43130_handle_device_data(client, cs43130);
		अगर (ret != 0)
			वापस ret;
	पूर्ण
	क्रम (i = 0; i < ARRAY_SIZE(cs43130->supplies); i++)
		cs43130->supplies[i].supply = cs43130_supply_names[i];

	ret = devm_regulator_bulk_get(&client->dev,
				      ARRAY_SIZE(cs43130->supplies),
				      cs43130->supplies);
	अगर (ret != 0) अणु
		dev_err(&client->dev, "Failed to request supplies: %d\n", ret);
		वापस ret;
	पूर्ण
	ret = regulator_bulk_enable(ARRAY_SIZE(cs43130->supplies),
				    cs43130->supplies);
	अगर (ret != 0) अणु
		dev_err(&client->dev, "Failed to enable supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	cs43130->reset_gpio = devm_gpiod_get_optional(&client->dev,
						      "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(cs43130->reset_gpio))
		वापस PTR_ERR(cs43130->reset_gpio);

	gpiod_set_value_cansleep(cs43130->reset_gpio, 1);

	usleep_range(2000, 2050);

	ret = regmap_पढ़ो(cs43130->regmap, CS43130_DEVID_AB, &reg);

	devid = (reg & 0xFF) << 12;
	ret = regmap_पढ़ो(cs43130->regmap, CS43130_DEVID_CD, &reg);
	devid |= (reg & 0xFF) << 4;
	ret = regmap_पढ़ो(cs43130->regmap, CS43130_DEVID_E, &reg);
	devid |= (reg & 0xF0) >> 4;

	चयन (devid) अणु
	हाल CS43130_CHIP_ID:
	हाल CS4399_CHIP_ID:
	हाल CS43131_CHIP_ID:
	हाल CS43198_CHIP_ID:
		अवरोध;
	शेष:
		dev_err(&client->dev,
			"CS43130 Device ID %X. Expected ID %X, %X, %X or %X\n",
			devid, CS43130_CHIP_ID, CS4399_CHIP_ID,
			CS43131_CHIP_ID, CS43198_CHIP_ID);
		ret = -ENODEV;
		जाओ err;
	पूर्ण

	cs43130->dev_id = devid;
	ret = regmap_पढ़ो(cs43130->regmap, CS43130_REV_ID, &reg);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "Get Revision ID failed\n");
		जाओ err;
	पूर्ण

	dev_info(&client->dev,
		 "Cirrus Logic CS43130 (%x), Revision: %02X\n", devid,
		 reg & 0xFF);

	mutex_init(&cs43130->clk_mutex);

	init_completion(&cs43130->xtal_rdy);
	init_completion(&cs43130->pll_rdy);
	init_completion(&cs43130->hpload_evt);

	ret = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
					शून्य, cs43130_irq_thपढ़ो,
					IRQF_ONESHOT | IRQF_TRIGGER_LOW,
					"cs43130", cs43130);
	अगर (ret != 0) अणु
		dev_err(&client->dev, "Failed to request IRQ: %d\n", ret);
		वापस ret;
	पूर्ण

	cs43130->mclk_पूर्णांक_src = CS43130_MCLK_SRC_RCO;

	pm_runसमय_set_स्वतःsuspend_delay(&client->dev, 100);
	pm_runसमय_use_स्वतःsuspend(&client->dev);
	pm_runसमय_set_active(&client->dev);
	pm_runसमय_enable(&client->dev);

	चयन (cs43130->dev_id) अणु
	हाल CS43130_CHIP_ID:
	हाल CS43131_CHIP_ID:
		स_नकल(all_hp_widमाला_लो, digital_hp_widमाला_लो,
		       माप(digital_hp_widमाला_लो));
		स_नकल(all_hp_widमाला_लो + ARRAY_SIZE(digital_hp_widमाला_लो),
		       analog_hp_widमाला_लो, माप(analog_hp_widमाला_लो));
		स_नकल(all_hp_routes, digital_hp_routes,
		       माप(digital_hp_routes));
		स_नकल(all_hp_routes + ARRAY_SIZE(digital_hp_routes),
		       analog_hp_routes, माप(analog_hp_routes));

		soc_component_dev_cs43130.dapm_widमाला_लो =
			all_hp_widमाला_लो;
		soc_component_dev_cs43130.num_dapm_widमाला_लो =
			ARRAY_SIZE(all_hp_widमाला_लो);
		soc_component_dev_cs43130.dapm_routes =
			all_hp_routes;
		soc_component_dev_cs43130.num_dapm_routes =
			ARRAY_SIZE(all_hp_routes);
		अवरोध;
	हाल CS43198_CHIP_ID:
	हाल CS4399_CHIP_ID:
		soc_component_dev_cs43130.dapm_widमाला_लो =
			digital_hp_widमाला_लो;
		soc_component_dev_cs43130.num_dapm_widमाला_लो =
			ARRAY_SIZE(digital_hp_widमाला_लो);
		soc_component_dev_cs43130.dapm_routes =
			digital_hp_routes;
		soc_component_dev_cs43130.num_dapm_routes =
			ARRAY_SIZE(digital_hp_routes);
		अवरोध;
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_component(&client->dev,
				     &soc_component_dev_cs43130,
				     cs43130_dai, ARRAY_SIZE(cs43130_dai));
	अगर (ret < 0) अणु
		dev_err(&client->dev,
			"snd_soc_register_component failed with ret = %d\n", ret);
		जाओ err;
	पूर्ण

	regmap_update_bits(cs43130->regmap, CS43130_PAD_INT_CFG,
			   CS43130_ASP_3ST_MASK, 0);
	regmap_update_bits(cs43130->regmap, CS43130_PAD_INT_CFG,
			   CS43130_XSP_3ST_MASK, 0);

	वापस 0;
err:
	वापस ret;
पूर्ण

अटल पूर्णांक cs43130_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा cs43130_निजी *cs43130 = i2c_get_clientdata(client);

	अगर (cs43130->xtal_ibias != CS43130_XTAL_UNUSED)
		regmap_update_bits(cs43130->regmap, CS43130_INT_MASK_1,
				   CS43130_XTAL_ERR_INT,
				   1 << CS43130_XTAL_ERR_INT_SHIFT);

	regmap_update_bits(cs43130->regmap, CS43130_INT_MASK_1,
			   CS43130_HP_PLUG_INT | CS43130_HP_UNPLUG_INT,
			   CS43130_HP_PLUG_INT | CS43130_HP_UNPLUG_INT);

	अगर (cs43130->dc_meas) अणु
		cancel_work_sync(&cs43130->work);
		flush_workqueue(cs43130->wq);

		device_हटाओ_file(&client->dev, &dev_attr_hpload_dc_l);
		device_हटाओ_file(&client->dev, &dev_attr_hpload_dc_r);
		device_हटाओ_file(&client->dev, &dev_attr_hpload_ac_l);
		device_हटाओ_file(&client->dev, &dev_attr_hpload_ac_r);
	पूर्ण

	gpiod_set_value_cansleep(cs43130->reset_gpio, 0);

	pm_runसमय_disable(&client->dev);
	regulator_bulk_disable(CS43130_NUM_SUPPLIES, cs43130->supplies);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused cs43130_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा cs43130_निजी *cs43130 = dev_get_drvdata(dev);

	अगर (cs43130->xtal_ibias != CS43130_XTAL_UNUSED)
		regmap_update_bits(cs43130->regmap, CS43130_INT_MASK_1,
				   CS43130_XTAL_ERR_INT,
				   1 << CS43130_XTAL_ERR_INT_SHIFT);

	regcache_cache_only(cs43130->regmap, true);
	regcache_mark_dirty(cs43130->regmap);

	gpiod_set_value_cansleep(cs43130->reset_gpio, 0);

	regulator_bulk_disable(CS43130_NUM_SUPPLIES, cs43130->supplies);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused cs43130_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा cs43130_निजी *cs43130 = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = regulator_bulk_enable(CS43130_NUM_SUPPLIES, cs43130->supplies);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to enable supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	regcache_cache_only(cs43130->regmap, false);

	gpiod_set_value_cansleep(cs43130->reset_gpio, 1);

	usleep_range(2000, 2050);

	ret = regcache_sync(cs43130->regmap);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to restore register cache\n");
		जाओ err;
	पूर्ण

	अगर (cs43130->xtal_ibias != CS43130_XTAL_UNUSED)
		regmap_update_bits(cs43130->regmap, CS43130_INT_MASK_1,
				   CS43130_XTAL_ERR_INT, 0);

	वापस 0;
err:
	regcache_cache_only(cs43130->regmap, true);
	regulator_bulk_disable(CS43130_NUM_SUPPLIES, cs43130->supplies);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops cs43130_runसमय_pm = अणु
	SET_RUNTIME_PM_OPS(cs43130_runसमय_suspend, cs43130_runसमय_resume,
			   शून्य)
पूर्ण;

अटल स्थिर काष्ठा of_device_id cs43130_of_match[] = अणु
	अणु.compatible = "cirrus,cs43130",पूर्ण,
	अणु.compatible = "cirrus,cs4399",पूर्ण,
	अणु.compatible = "cirrus,cs43131",पूर्ण,
	अणु.compatible = "cirrus,cs43198",पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, cs43130_of_match);

अटल स्थिर काष्ठा i2c_device_id cs43130_i2c_id[] = अणु
	अणु"cs43130", 0पूर्ण,
	अणु"cs4399", 0पूर्ण,
	अणु"cs43131", 0पूर्ण,
	अणु"cs43198", 0पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, cs43130_i2c_id);

अटल काष्ठा i2c_driver cs43130_i2c_driver = अणु
	.driver = अणु
		.name		= "cs43130",
		.of_match_table	= cs43130_of_match,
		.pm             = &cs43130_runसमय_pm,
	पूर्ण,
	.id_table	= cs43130_i2c_id,
	.probe		= cs43130_i2c_probe,
	.हटाओ		= cs43130_i2c_हटाओ,
पूर्ण;

module_i2c_driver(cs43130_i2c_driver);

MODULE_AUTHOR("Li Xu <li.xu@cirrus.com>");
MODULE_DESCRIPTION("Cirrus Logic CS43130 ALSA SoC Codec Driver");
MODULE_LICENSE("GPL");
