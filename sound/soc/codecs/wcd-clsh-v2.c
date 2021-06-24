<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2015-2016, The Linux Foundation. All rights reserved.
// Copyright (c) 2017-2018, Linaro Limited

#समावेश <linux/slab.h>
#समावेश <sound/soc.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश "wcd9335.h"
#समावेश "wcd-clsh-v2.h"

काष्ठा wcd_clsh_ctrl अणु
	पूर्णांक state;
	पूर्णांक mode;
	पूर्णांक flyback_users;
	पूर्णांक buck_users;
	पूर्णांक clsh_users;
	पूर्णांक codec_version;
	काष्ठा snd_soc_component *comp;
पूर्ण;

/* Class-H रेजिस्टरs क्रम codecs from and above WCD9335 */
#घोषणा WCD9XXX_A_CDC_RX0_RX_PATH_CFG0			WCD9335_REG(0xB, 0x42)
#घोषणा WCD9XXX_A_CDC_RX_PATH_CLSH_EN_MASK		BIT(6)
#घोषणा WCD9XXX_A_CDC_RX_PATH_CLSH_ENABLE		BIT(6)
#घोषणा WCD9XXX_A_CDC_RX_PATH_CLSH_DISABLE		0
#घोषणा WCD9XXX_A_CDC_RX1_RX_PATH_CFG0			WCD9335_REG(0xB, 0x56)
#घोषणा WCD9XXX_A_CDC_RX2_RX_PATH_CFG0			WCD9335_REG(0xB, 0x6A)
#घोषणा WCD9XXX_A_CDC_CLSH_K1_MSB			WCD9335_REG(0xC, 0x08)
#घोषणा WCD9XXX_A_CDC_CLSH_K1_MSB_COEF_MASK		GENMASK(3, 0)
#घोषणा WCD9XXX_A_CDC_CLSH_K1_LSB			WCD9335_REG(0xC, 0x09)
#घोषणा WCD9XXX_A_CDC_CLSH_K1_LSB_COEF_MASK		GENMASK(7, 0)
#घोषणा WCD9XXX_A_ANA_RX_SUPPLIES			WCD9335_REG(0x6, 0x08)
#घोषणा WCD9XXX_A_ANA_RX_REGULATOR_MODE_MASK		BIT(1)
#घोषणा WCD9XXX_A_ANA_RX_REGULATOR_MODE_CLS_H		0
#घोषणा WCD9XXX_A_ANA_RX_REGULATOR_MODE_CLS_AB		BIT(1)
#घोषणा WCD9XXX_A_ANA_RX_VNEG_PWR_LVL_MASK		BIT(2)
#घोषणा WCD9XXX_A_ANA_RX_VNEG_PWR_LVL_UHQA		BIT(2)
#घोषणा WCD9XXX_A_ANA_RX_VNEG_PWR_LVL_DEFAULT		0
#घोषणा WCD9XXX_A_ANA_RX_VPOS_PWR_LVL_MASK		BIT(3)
#घोषणा WCD9XXX_A_ANA_RX_VPOS_PWR_LVL_UHQA		BIT(3)
#घोषणा WCD9XXX_A_ANA_RX_VPOS_PWR_LVL_DEFAULT		0
#घोषणा WCD9XXX_A_ANA_RX_VNEG_EN_MASK			BIT(6)
#घोषणा WCD9XXX_A_ANA_RX_VNEG_EN_SHIFT			6
#घोषणा WCD9XXX_A_ANA_RX_VNEG_ENABLE			BIT(6)
#घोषणा WCD9XXX_A_ANA_RX_VNEG_DISABLE			0
#घोषणा WCD9XXX_A_ANA_RX_VPOS_EN_MASK			BIT(7)
#घोषणा WCD9XXX_A_ANA_RX_VPOS_EN_SHIFT			7
#घोषणा WCD9XXX_A_ANA_RX_VPOS_ENABLE			BIT(7)
#घोषणा WCD9XXX_A_ANA_RX_VPOS_DISABLE			0
#घोषणा WCD9XXX_A_ANA_HPH				WCD9335_REG(0x6, 0x09)
#घोषणा WCD9XXX_A_ANA_HPH_PWR_LEVEL_MASK		GENMASK(3, 2)
#घोषणा WCD9XXX_A_ANA_HPH_PWR_LEVEL_UHQA		0x08
#घोषणा WCD9XXX_A_ANA_HPH_PWR_LEVEL_LP			0x04
#घोषणा WCD9XXX_A_ANA_HPH_PWR_LEVEL_NORMAL		0x0
#घोषणा WCD9XXX_A_CDC_CLSH_CRC				WCD9335_REG(0xC, 0x01)
#घोषणा WCD9XXX_A_CDC_CLSH_CRC_CLK_EN_MASK		BIT(0)
#घोषणा WCD9XXX_A_CDC_CLSH_CRC_CLK_ENABLE		BIT(0)
#घोषणा WCD9XXX_A_CDC_CLSH_CRC_CLK_DISABLE		0
#घोषणा WCD9XXX_FLYBACK_EN				WCD9335_REG(0x6, 0xA4)
#घोषणा WCD9XXX_FLYBACK_EN_DELAY_SEL_MASK		GENMASK(6, 5)
#घोषणा WCD9XXX_FLYBACK_EN_DELAY_26P25_US		0x40
#घोषणा WCD9XXX_FLYBACK_EN_RESET_BY_EXT_MASK		BIT(4)
#घोषणा WCD9XXX_FLYBACK_EN_PWDN_WITHOUT_DELAY		BIT(4)
#घोषणा WCD9XXX_FLYBACK_EN_PWDN_WITH_DELAY			0
#घोषणा WCD9XXX_RX_BIAS_FLYB_BUFF			WCD9335_REG(0x6, 0xC7)
#घोषणा WCD9XXX_RX_BIAS_FLYB_VNEG_5_UA_MASK		GENMASK(7, 4)
#घोषणा WCD9XXX_RX_BIAS_FLYB_VPOS_5_UA_MASK		GENMASK(3, 0)
#घोषणा WCD9XXX_HPH_L_EN				WCD9335_REG(0x6, 0xD3)
#घोषणा WCD9XXX_HPH_CONST_SEL_L_MASK			GENMASK(7, 3)
#घोषणा WCD9XXX_HPH_CONST_SEL_BYPASS			0
#घोषणा WCD9XXX_HPH_CONST_SEL_LP_PATH			0x40
#घोषणा WCD9XXX_HPH_CONST_SEL_HQ_PATH			0x80
#घोषणा WCD9XXX_HPH_R_EN				WCD9335_REG(0x6, 0xD6)
#घोषणा WCD9XXX_HPH_REFBUFF_UHQA_CTL			WCD9335_REG(0x6, 0xDD)
#घोषणा WCD9XXX_HPH_REFBUFF_UHQA_GAIN_MASK		GENMASK(2, 0)
#घोषणा WCD9XXX_CLASSH_CTRL_VCL_2                       WCD9335_REG(0x6, 0x9B)
#घोषणा WCD9XXX_CLASSH_CTRL_VCL_2_VREF_FILT_1_MASK	GENMASK(5, 4)
#घोषणा WCD9XXX_CLASSH_CTRL_VCL_VREF_FILT_R_50KOHM	0x20
#घोषणा WCD9XXX_CLASSH_CTRL_VCL_VREF_FILT_R_0KOHM	0x0
#घोषणा WCD9XXX_CDC_RX1_RX_PATH_CTL			WCD9335_REG(0xB, 0x55)
#घोषणा WCD9XXX_CDC_RX2_RX_PATH_CTL			WCD9335_REG(0xB, 0x69)
#घोषणा WCD9XXX_CDC_CLK_RST_CTRL_MCLK_CONTROL		WCD9335_REG(0xD, 0x41)
#घोषणा WCD9XXX_CDC_CLK_RST_CTRL_MCLK_EN_MASK		BIT(0)
#घोषणा WCD9XXX_CDC_CLK_RST_CTRL_MCLK_11P3_EN_MASK	BIT(1)
#घोषणा WCD9XXX_CLASSH_CTRL_CCL_1                       WCD9335_REG(0x6, 0x9C)
#घोषणा WCD9XXX_CLASSH_CTRL_CCL_1_DELTA_IPEAK_MASK	GENMASK(7, 4)
#घोषणा WCD9XXX_CLASSH_CTRL_CCL_1_DELTA_IPEAK_50MA	0x50
#घोषणा WCD9XXX_CLASSH_CTRL_CCL_1_DELTA_IPEAK_30MA	0x30

#घोषणा CLSH_REQ_ENABLE		true
#घोषणा CLSH_REQ_DISABLE	false
#घोषणा WCD_USLEEP_RANGE	50

क्रमागत अणु
	DAC_GAIN_0DB = 0,
	DAC_GAIN_0P2DB,
	DAC_GAIN_0P4DB,
	DAC_GAIN_0P6DB,
	DAC_GAIN_0P8DB,
	DAC_GAIN_M0P2DB,
	DAC_GAIN_M0P4DB,
	DAC_GAIN_M0P6DB,
पूर्ण;

अटल अंतरभूत व्योम wcd_enable_clsh_block(काष्ठा wcd_clsh_ctrl *ctrl,
					 bool enable)
अणु
	काष्ठा snd_soc_component *comp = ctrl->comp;

	अगर ((enable && ++ctrl->clsh_users == 1) ||
	    (!enable && --ctrl->clsh_users == 0))
		snd_soc_component_update_bits(comp, WCD9XXX_A_CDC_CLSH_CRC,
				      WCD9XXX_A_CDC_CLSH_CRC_CLK_EN_MASK,
				      enable);
	अगर (ctrl->clsh_users < 0)
		ctrl->clsh_users = 0;
पूर्ण

अटल अंतरभूत bool wcd_clsh_enable_status(काष्ठा snd_soc_component *comp)
अणु
	वापस snd_soc_component_पढ़ो(comp, WCD9XXX_A_CDC_CLSH_CRC) &
					WCD9XXX_A_CDC_CLSH_CRC_CLK_EN_MASK;
पूर्ण

अटल अंतरभूत व्योम wcd_clsh_set_buck_mode(काष्ठा snd_soc_component *comp,
					  पूर्णांक mode)
अणु
	/* set to HIFI */
	अगर (mode == CLS_H_HIFI)
		snd_soc_component_update_bits(comp, WCD9XXX_A_ANA_RX_SUPPLIES,
					WCD9XXX_A_ANA_RX_VPOS_PWR_LVL_MASK,
					WCD9XXX_A_ANA_RX_VPOS_PWR_LVL_UHQA);
	अन्यथा
		snd_soc_component_update_bits(comp, WCD9XXX_A_ANA_RX_SUPPLIES,
					WCD9XXX_A_ANA_RX_VPOS_PWR_LVL_MASK,
					WCD9XXX_A_ANA_RX_VPOS_PWR_LVL_DEFAULT);
पूर्ण

अटल अंतरभूत व्योम wcd_clsh_set_flyback_mode(काष्ठा snd_soc_component *comp,
					     पूर्णांक mode)
अणु
	/* set to HIFI */
	अगर (mode == CLS_H_HIFI)
		snd_soc_component_update_bits(comp, WCD9XXX_A_ANA_RX_SUPPLIES,
					WCD9XXX_A_ANA_RX_VNEG_PWR_LVL_MASK,
					WCD9XXX_A_ANA_RX_VNEG_PWR_LVL_UHQA);
	अन्यथा
		snd_soc_component_update_bits(comp, WCD9XXX_A_ANA_RX_SUPPLIES,
					WCD9XXX_A_ANA_RX_VNEG_PWR_LVL_MASK,
					WCD9XXX_A_ANA_RX_VNEG_PWR_LVL_DEFAULT);
पूर्ण

अटल व्योम wcd_clsh_buck_ctrl(काष्ठा wcd_clsh_ctrl *ctrl,
			       पूर्णांक mode,
			       bool enable)
अणु
	काष्ठा snd_soc_component *comp = ctrl->comp;

	/* enable/disable buck */
	अगर ((enable && (++ctrl->buck_users == 1)) ||
	   (!enable && (--ctrl->buck_users == 0)))
		snd_soc_component_update_bits(comp, WCD9XXX_A_ANA_RX_SUPPLIES,
				WCD9XXX_A_ANA_RX_VPOS_EN_MASK,
				enable << WCD9XXX_A_ANA_RX_VPOS_EN_SHIFT);
	/*
	 * 500us sleep is required after buck enable/disable
	 * as per HW requirement
	 */
	usleep_range(500, 500 + WCD_USLEEP_RANGE);
पूर्ण

अटल व्योम wcd_clsh_flyback_ctrl(काष्ठा wcd_clsh_ctrl *ctrl,
				  पूर्णांक mode,
				  bool enable)
अणु
	काष्ठा snd_soc_component *comp = ctrl->comp;

	/* enable/disable flyback */
	अगर ((enable && (++ctrl->flyback_users == 1)) ||
	   (!enable && (--ctrl->flyback_users == 0))) अणु
		snd_soc_component_update_bits(comp, WCD9XXX_A_ANA_RX_SUPPLIES,
				WCD9XXX_A_ANA_RX_VNEG_EN_MASK,
				enable << WCD9XXX_A_ANA_RX_VNEG_EN_SHIFT);
		/* 100usec delay is needed as per HW requirement */
		usleep_range(100, 110);
	पूर्ण
	/*
	 * 500us sleep is required after flyback enable/disable
	 * as per HW requirement
	 */
	usleep_range(500, 500 + WCD_USLEEP_RANGE);
पूर्ण

अटल व्योम wcd_clsh_set_gain_path(काष्ठा wcd_clsh_ctrl *ctrl, पूर्णांक mode)
अणु
	काष्ठा snd_soc_component *comp = ctrl->comp;
	पूर्णांक val = 0;

	चयन (mode) अणु
	हाल CLS_H_NORMAL:
	हाल CLS_AB:
		val = WCD9XXX_HPH_CONST_SEL_BYPASS;
		अवरोध;
	हाल CLS_H_HIFI:
		val = WCD9XXX_HPH_CONST_SEL_HQ_PATH;
		अवरोध;
	हाल CLS_H_LP:
		val = WCD9XXX_HPH_CONST_SEL_LP_PATH;
		अवरोध;
	पूर्ण

	snd_soc_component_update_bits(comp, WCD9XXX_HPH_L_EN,
					WCD9XXX_HPH_CONST_SEL_L_MASK,
					val);

	snd_soc_component_update_bits(comp, WCD9XXX_HPH_R_EN,
					WCD9XXX_HPH_CONST_SEL_L_MASK,
					val);
पूर्ण

अटल व्योम wcd_clsh_set_hph_mode(काष्ठा snd_soc_component *comp,
				  पूर्णांक mode)
अणु
	पूर्णांक val = 0, gain = 0, res_val;
	पूर्णांक ipeak = WCD9XXX_CLASSH_CTRL_CCL_1_DELTA_IPEAK_50MA;

	res_val = WCD9XXX_CLASSH_CTRL_VCL_VREF_FILT_R_0KOHM;
	चयन (mode) अणु
	हाल CLS_H_NORMAL:
		res_val = WCD9XXX_CLASSH_CTRL_VCL_VREF_FILT_R_50KOHM;
		val = WCD9XXX_A_ANA_HPH_PWR_LEVEL_NORMAL;
		gain = DAC_GAIN_0DB;
		ipeak = WCD9XXX_CLASSH_CTRL_CCL_1_DELTA_IPEAK_50MA;
		अवरोध;
	हाल CLS_AB:
		val = WCD9XXX_A_ANA_HPH_PWR_LEVEL_NORMAL;
		gain = DAC_GAIN_0DB;
		ipeak = WCD9XXX_CLASSH_CTRL_CCL_1_DELTA_IPEAK_50MA;
		अवरोध;
	हाल CLS_H_HIFI:
		val = WCD9XXX_A_ANA_HPH_PWR_LEVEL_UHQA;
		gain = DAC_GAIN_M0P2DB;
		ipeak = WCD9XXX_CLASSH_CTRL_CCL_1_DELTA_IPEAK_50MA;
		अवरोध;
	हाल CLS_H_LP:
		val = WCD9XXX_A_ANA_HPH_PWR_LEVEL_LP;
		ipeak = WCD9XXX_CLASSH_CTRL_CCL_1_DELTA_IPEAK_30MA;
		अवरोध;
	पूर्ण

	snd_soc_component_update_bits(comp, WCD9XXX_A_ANA_HPH,
					WCD9XXX_A_ANA_HPH_PWR_LEVEL_MASK, val);
	snd_soc_component_update_bits(comp, WCD9XXX_CLASSH_CTRL_VCL_2,
				WCD9XXX_CLASSH_CTRL_VCL_2_VREF_FILT_1_MASK,
				res_val);
	अगर (mode != CLS_H_LP)
		snd_soc_component_update_bits(comp,
					WCD9XXX_HPH_REFBUFF_UHQA_CTL,
					WCD9XXX_HPH_REFBUFF_UHQA_GAIN_MASK,
					gain);
	snd_soc_component_update_bits(comp, WCD9XXX_CLASSH_CTRL_CCL_1,
				WCD9XXX_CLASSH_CTRL_CCL_1_DELTA_IPEAK_MASK,
				ipeak);
पूर्ण

अटल व्योम wcd_clsh_set_flyback_current(काष्ठा snd_soc_component *comp,
					 पूर्णांक mode)
अणु

	snd_soc_component_update_bits(comp, WCD9XXX_RX_BIAS_FLYB_BUFF,
				WCD9XXX_RX_BIAS_FLYB_VPOS_5_UA_MASK, 0x0A);
	snd_soc_component_update_bits(comp, WCD9XXX_RX_BIAS_FLYB_BUFF,
				WCD9XXX_RX_BIAS_FLYB_VNEG_5_UA_MASK, 0x0A);
	/* Sleep needed to aव्योम click and pop as per HW requirement */
	usleep_range(100, 110);
पूर्ण

अटल व्योम wcd_clsh_set_buck_regulator_mode(काष्ठा snd_soc_component *comp,
					     पूर्णांक mode)
अणु
	अगर (mode == CLS_AB)
		snd_soc_component_update_bits(comp, WCD9XXX_A_ANA_RX_SUPPLIES,
					WCD9XXX_A_ANA_RX_REGULATOR_MODE_MASK,
					WCD9XXX_A_ANA_RX_REGULATOR_MODE_CLS_AB);
	अन्यथा
		snd_soc_component_update_bits(comp, WCD9XXX_A_ANA_RX_SUPPLIES,
					WCD9XXX_A_ANA_RX_REGULATOR_MODE_MASK,
					WCD9XXX_A_ANA_RX_REGULATOR_MODE_CLS_H);
पूर्ण

अटल व्योम wcd_clsh_state_lo(काष्ठा wcd_clsh_ctrl *ctrl, पूर्णांक req_state,
			      bool is_enable, पूर्णांक mode)
अणु
	काष्ठा snd_soc_component *comp = ctrl->comp;

	अगर (mode != CLS_AB) अणु
		dev_err(comp->dev, "%s: LO cannot be in this mode: %d\n",
			__func__, mode);
		वापस;
	पूर्ण

	अगर (is_enable) अणु
		wcd_clsh_set_buck_regulator_mode(comp, mode);
		wcd_clsh_set_buck_mode(comp, mode);
		wcd_clsh_set_flyback_mode(comp, mode);
		wcd_clsh_flyback_ctrl(ctrl, mode, true);
		wcd_clsh_set_flyback_current(comp, mode);
		wcd_clsh_buck_ctrl(ctrl, mode, true);
	पूर्ण अन्यथा अणु
		wcd_clsh_buck_ctrl(ctrl, mode, false);
		wcd_clsh_flyback_ctrl(ctrl, mode, false);
		wcd_clsh_set_flyback_mode(comp, CLS_H_NORMAL);
		wcd_clsh_set_buck_mode(comp, CLS_H_NORMAL);
		wcd_clsh_set_buck_regulator_mode(comp, CLS_H_NORMAL);
	पूर्ण
पूर्ण

अटल व्योम wcd_clsh_state_hph_r(काष्ठा wcd_clsh_ctrl *ctrl, पूर्णांक req_state,
				 bool is_enable, पूर्णांक mode)
अणु
	काष्ठा snd_soc_component *comp = ctrl->comp;

	अगर (mode == CLS_H_NORMAL) अणु
		dev_err(comp->dev, "%s: Normal mode not applicable for hph_r\n",
			__func__);
		वापस;
	पूर्ण

	अगर (is_enable) अणु
		अगर (mode != CLS_AB) अणु
			wcd_enable_clsh_block(ctrl, true);
			/*
			 * These K1 values depend on the Headphone Impedance
			 * For now it is assumed to be 16 ohm
			 */
			snd_soc_component_update_bits(comp,
					WCD9XXX_A_CDC_CLSH_K1_MSB,
					WCD9XXX_A_CDC_CLSH_K1_MSB_COEF_MASK,
					0x00);
			snd_soc_component_update_bits(comp,
					WCD9XXX_A_CDC_CLSH_K1_LSB,
					WCD9XXX_A_CDC_CLSH_K1_LSB_COEF_MASK,
					0xC0);
			snd_soc_component_update_bits(comp,
					    WCD9XXX_A_CDC_RX2_RX_PATH_CFG0,
					    WCD9XXX_A_CDC_RX_PATH_CLSH_EN_MASK,
					    WCD9XXX_A_CDC_RX_PATH_CLSH_ENABLE);
		पूर्ण
		wcd_clsh_set_buck_regulator_mode(comp, mode);
		wcd_clsh_set_flyback_mode(comp, mode);
		wcd_clsh_flyback_ctrl(ctrl, mode, true);
		wcd_clsh_set_flyback_current(comp, mode);
		wcd_clsh_set_buck_mode(comp, mode);
		wcd_clsh_buck_ctrl(ctrl, mode, true);
		wcd_clsh_set_hph_mode(comp, mode);
		wcd_clsh_set_gain_path(ctrl, mode);
	पूर्ण अन्यथा अणु
		wcd_clsh_set_hph_mode(comp, CLS_H_NORMAL);

		अगर (mode != CLS_AB) अणु
			snd_soc_component_update_bits(comp,
					    WCD9XXX_A_CDC_RX2_RX_PATH_CFG0,
					    WCD9XXX_A_CDC_RX_PATH_CLSH_EN_MASK,
					    WCD9XXX_A_CDC_RX_PATH_CLSH_DISABLE);
			wcd_enable_clsh_block(ctrl, false);
		पूर्ण
		/* buck and flyback set to शेष mode and disable */
		wcd_clsh_buck_ctrl(ctrl, CLS_H_NORMAL, false);
		wcd_clsh_flyback_ctrl(ctrl, CLS_H_NORMAL, false);
		wcd_clsh_set_flyback_mode(comp, CLS_H_NORMAL);
		wcd_clsh_set_buck_mode(comp, CLS_H_NORMAL);
		wcd_clsh_set_buck_regulator_mode(comp, CLS_H_NORMAL);
	पूर्ण
पूर्ण

अटल व्योम wcd_clsh_state_hph_l(काष्ठा wcd_clsh_ctrl *ctrl, पूर्णांक req_state,
				 bool is_enable, पूर्णांक mode)
अणु
	काष्ठा snd_soc_component *comp = ctrl->comp;

	अगर (mode == CLS_H_NORMAL) अणु
		dev_err(comp->dev, "%s: Normal mode not applicable for hph_l\n",
			__func__);
		वापस;
	पूर्ण

	अगर (is_enable) अणु
		अगर (mode != CLS_AB) अणु
			wcd_enable_clsh_block(ctrl, true);
			/*
			 * These K1 values depend on the Headphone Impedance
			 * For now it is assumed to be 16 ohm
			 */
			snd_soc_component_update_bits(comp,
					WCD9XXX_A_CDC_CLSH_K1_MSB,
					WCD9XXX_A_CDC_CLSH_K1_MSB_COEF_MASK,
					0x00);
			snd_soc_component_update_bits(comp,
					WCD9XXX_A_CDC_CLSH_K1_LSB,
					WCD9XXX_A_CDC_CLSH_K1_LSB_COEF_MASK,
					0xC0);
			snd_soc_component_update_bits(comp,
					    WCD9XXX_A_CDC_RX1_RX_PATH_CFG0,
					    WCD9XXX_A_CDC_RX_PATH_CLSH_EN_MASK,
					    WCD9XXX_A_CDC_RX_PATH_CLSH_ENABLE);
		पूर्ण
		wcd_clsh_set_buck_regulator_mode(comp, mode);
		wcd_clsh_set_flyback_mode(comp, mode);
		wcd_clsh_flyback_ctrl(ctrl, mode, true);
		wcd_clsh_set_flyback_current(comp, mode);
		wcd_clsh_set_buck_mode(comp, mode);
		wcd_clsh_buck_ctrl(ctrl, mode, true);
		wcd_clsh_set_hph_mode(comp, mode);
		wcd_clsh_set_gain_path(ctrl, mode);
	पूर्ण अन्यथा अणु
		wcd_clsh_set_hph_mode(comp, CLS_H_NORMAL);

		अगर (mode != CLS_AB) अणु
			snd_soc_component_update_bits(comp,
					    WCD9XXX_A_CDC_RX1_RX_PATH_CFG0,
					    WCD9XXX_A_CDC_RX_PATH_CLSH_EN_MASK,
					    WCD9XXX_A_CDC_RX_PATH_CLSH_DISABLE);
			wcd_enable_clsh_block(ctrl, false);
		पूर्ण
		/* set buck and flyback to Default Mode */
		wcd_clsh_buck_ctrl(ctrl, CLS_H_NORMAL, false);
		wcd_clsh_flyback_ctrl(ctrl, CLS_H_NORMAL, false);
		wcd_clsh_set_flyback_mode(comp, CLS_H_NORMAL);
		wcd_clsh_set_buck_mode(comp, CLS_H_NORMAL);
		wcd_clsh_set_buck_regulator_mode(comp, CLS_H_NORMAL);
	पूर्ण
पूर्ण

अटल व्योम wcd_clsh_state_ear(काष्ठा wcd_clsh_ctrl *ctrl, पूर्णांक req_state,
			       bool is_enable, पूर्णांक mode)
अणु
	काष्ठा snd_soc_component *comp = ctrl->comp;

	अगर (mode != CLS_H_NORMAL) अणु
		dev_err(comp->dev, "%s: mode: %d cannot be used for EAR\n",
			__func__, mode);
		वापस;
	पूर्ण

	अगर (is_enable) अणु
		wcd_enable_clsh_block(ctrl, true);
		snd_soc_component_update_bits(comp,
					WCD9XXX_A_CDC_RX0_RX_PATH_CFG0,
					WCD9XXX_A_CDC_RX_PATH_CLSH_EN_MASK,
					WCD9XXX_A_CDC_RX_PATH_CLSH_ENABLE);
		wcd_clsh_set_buck_mode(comp, mode);
		wcd_clsh_set_flyback_mode(comp, mode);
		wcd_clsh_flyback_ctrl(ctrl, mode, true);
		wcd_clsh_set_flyback_current(comp, mode);
		wcd_clsh_buck_ctrl(ctrl, mode, true);
	पूर्ण अन्यथा अणु
		snd_soc_component_update_bits(comp,
					WCD9XXX_A_CDC_RX0_RX_PATH_CFG0,
					WCD9XXX_A_CDC_RX_PATH_CLSH_EN_MASK,
					WCD9XXX_A_CDC_RX_PATH_CLSH_DISABLE);
		wcd_enable_clsh_block(ctrl, false);
		wcd_clsh_buck_ctrl(ctrl, mode, false);
		wcd_clsh_flyback_ctrl(ctrl, mode, false);
		wcd_clsh_set_flyback_mode(comp, CLS_H_NORMAL);
		wcd_clsh_set_buck_mode(comp, CLS_H_NORMAL);
	पूर्ण
पूर्ण

अटल पूर्णांक _wcd_clsh_ctrl_set_state(काष्ठा wcd_clsh_ctrl *ctrl, पूर्णांक req_state,
				    bool is_enable, पूर्णांक mode)
अणु
	चयन (req_state) अणु
	हाल WCD_CLSH_STATE_EAR:
		wcd_clsh_state_ear(ctrl, req_state, is_enable, mode);
		अवरोध;
	हाल WCD_CLSH_STATE_HPHL:
		wcd_clsh_state_hph_l(ctrl, req_state, is_enable, mode);
		अवरोध;
	हाल WCD_CLSH_STATE_HPHR:
		wcd_clsh_state_hph_r(ctrl, req_state, is_enable, mode);
		अवरोध;
	हाल WCD_CLSH_STATE_LO:
		wcd_clsh_state_lo(ctrl, req_state, is_enable, mode);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Function: wcd_clsh_is_state_valid
 * Params: state
 * Description:
 * Provides inक्रमmation on valid states of Class H configuration
 */
अटल bool wcd_clsh_is_state_valid(पूर्णांक state)
अणु
	चयन (state) अणु
	हाल WCD_CLSH_STATE_IDLE:
	हाल WCD_CLSH_STATE_EAR:
	हाल WCD_CLSH_STATE_HPHL:
	हाल WCD_CLSH_STATE_HPHR:
	हाल WCD_CLSH_STATE_LO:
		वापस true;
	शेष:
		वापस false;
	पूर्ण;
पूर्ण

/*
 * Function: wcd_clsh_fsm
 * Params: ctrl, req_state, req_type, clsh_event
 * Description:
 * This function handles PRE DAC and POST DAC conditions of dअगरferent devices
 * and updates class H configuration of dअगरferent combination of devices
 * based on validity of their states. ctrl will contain current
 * class h state inक्रमmation
 */
पूर्णांक wcd_clsh_ctrl_set_state(काष्ठा wcd_clsh_ctrl *ctrl,
			    क्रमागत wcd_clsh_event clsh_event,
			    पूर्णांक nstate,
			    क्रमागत wcd_clsh_mode mode)
अणु
	काष्ठा snd_soc_component *comp = ctrl->comp;

	अगर (nstate == ctrl->state)
		वापस 0;

	अगर (!wcd_clsh_is_state_valid(nstate)) अणु
		dev_err(comp->dev, "Class-H not a valid new state:\n");
		वापस -EINVAL;
	पूर्ण

	चयन (clsh_event) अणु
	हाल WCD_CLSH_EVENT_PRE_DAC:
		_wcd_clsh_ctrl_set_state(ctrl, nstate, CLSH_REQ_ENABLE, mode);
		अवरोध;
	हाल WCD_CLSH_EVENT_POST_PA:
		_wcd_clsh_ctrl_set_state(ctrl, nstate, CLSH_REQ_DISABLE, mode);
		अवरोध;
	पूर्ण

	ctrl->state = nstate;
	ctrl->mode = mode;

	वापस 0;
पूर्ण

पूर्णांक wcd_clsh_ctrl_get_state(काष्ठा wcd_clsh_ctrl *ctrl)
अणु
	वापस ctrl->state;
पूर्ण

काष्ठा wcd_clsh_ctrl *wcd_clsh_ctrl_alloc(काष्ठा snd_soc_component *comp,
					  पूर्णांक version)
अणु
	काष्ठा wcd_clsh_ctrl *ctrl;

	ctrl = kzalloc(माप(*ctrl), GFP_KERNEL);
	अगर (!ctrl)
		वापस ERR_PTR(-ENOMEM);

	ctrl->state = WCD_CLSH_STATE_IDLE;
	ctrl->comp = comp;

	वापस ctrl;
पूर्ण

व्योम wcd_clsh_ctrl_मुक्त(काष्ठा wcd_clsh_ctrl *ctrl)
अणु
	kमुक्त(ctrl);
पूर्ण
