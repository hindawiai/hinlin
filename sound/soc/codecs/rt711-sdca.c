<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
//
// rt711-sdca.c -- rt711 SDCA ALSA SoC audio driver
//
// Copyright(c) 2021 Realtek Semiconductor Corp.
//
//

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/soundwire/sdw_रेजिस्टरs.h>
#समावेश <linux/slab.h>
#समावेश <linux/bitops.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>
#समावेश <sound/jack.h>

#समावेश "rt711-sdca.h"

अटल पूर्णांक rt711_sdca_index_ग_लिखो(काष्ठा rt711_sdca_priv *rt711,
		अचिन्हित पूर्णांक nid, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक value)
अणु
	पूर्णांक ret;
	काष्ठा regmap *regmap = rt711->mbq_regmap;
	अचिन्हित पूर्णांक addr = (nid << 20) | reg;

	ret = regmap_ग_लिखो(regmap, addr, value);
	अगर (ret < 0)
		dev_err(rt711->component->dev,
			"Failed to set private value: %06x <= %04x ret=%d\n",
			addr, value, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक rt711_sdca_index_पढ़ो(काष्ठा rt711_sdca_priv *rt711,
		अचिन्हित पूर्णांक nid, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक *value)
अणु
	पूर्णांक ret;
	काष्ठा regmap *regmap = rt711->mbq_regmap;
	अचिन्हित पूर्णांक addr = (nid << 20) | reg;

	ret = regmap_पढ़ो(regmap, addr, value);
	अगर (ret < 0)
		dev_err(rt711->component->dev,
			"Failed to get private value: %06x => %04x ret=%d\n",
			addr, *value, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक rt711_sdca_index_update_bits(काष्ठा rt711_sdca_priv *rt711,
	अचिन्हित पूर्णांक nid, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val)
अणु
	अचिन्हित पूर्णांक पंचांगp;
	पूर्णांक ret;

	ret = rt711_sdca_index_पढ़ो(rt711, nid, reg, &पंचांगp);
	अगर (ret < 0)
		वापस ret;

	set_mask_bits(&पंचांगp, mask, val);
	वापस rt711_sdca_index_ग_लिखो(rt711, nid, reg, पंचांगp);
पूर्ण

अटल व्योम rt711_sdca_reset(काष्ठा rt711_sdca_priv *rt711)
अणु
	rt711_sdca_index_update_bits(rt711, RT711_VENDOR_REG,
		RT711_PARA_VERB_CTL, RT711_HIDDEN_REG_SW_RESET,
		RT711_HIDDEN_REG_SW_RESET);
	rt711_sdca_index_update_bits(rt711, RT711_VENDOR_HDA_CTL,
		RT711_HDA_LEGACY_RESET_CTL, 0x1, 0x1);
पूर्ण

अटल पूर्णांक rt711_sdca_calibration(काष्ठा rt711_sdca_priv *rt711)
अणु
	अचिन्हित पूर्णांक val, loop_rc = 0, loop_dc = 0;
	काष्ठा device *dev;
	काष्ठा regmap *regmap = rt711->regmap;
	पूर्णांक chk_cnt = 100;
	पूर्णांक ret = 0;

	mutex_lock(&rt711->calibrate_mutex);
	dev = regmap_get_device(regmap);

	regmap_पढ़ो(rt711->regmap, RT711_RC_CAL_STATUS, &val);
	/* RC calibration */
	अगर (!(val & 0x40))
		rt711_sdca_index_update_bits(rt711, RT711_VENDOR_ANALOG_CTL,
			RT711_MISC_POWER_CTL0, 0x0010, 0x0010);

	क्रम (loop_rc = 0; loop_rc < chk_cnt && !(val & 0x40); loop_rc++) अणु
		usleep_range(10000, 11000);
		ret = regmap_पढ़ो(rt711->regmap, RT711_RC_CAL_STATUS, &val);
		अगर (ret < 0)
			जाओ _cali_fail_;
	पूर्ण
	अगर (loop_rc == chk_cnt)
		dev_err(dev, "%s, RC calibration time-out!\n", __func__);

	/* HP calibration by manual mode setting */
	rt711_sdca_index_update_bits(rt711, RT711_VENDOR_REG,
		RT711_FSM_CTL, 0x2000, 0x2000);

	/* Calibration manual mode */
	rt711_sdca_index_update_bits(rt711, RT711_VENDOR_REG,
		RT711_FSM_CTL, 0xf, RT711_CALI_CTL);

	/* reset HP calibration */
	rt711_sdca_index_update_bits(rt711, RT711_VENDOR_CALI,
		RT711_DAC_DC_CALI_CTL1, RT711_DAC_DC_FORCE_CALI_RST, 0x00);
	rt711_sdca_index_update_bits(rt711, RT711_VENDOR_CALI,
		RT711_DAC_DC_CALI_CTL1, RT711_DAC_DC_FORCE_CALI_RST,
		RT711_DAC_DC_FORCE_CALI_RST);

	/* cal_clk_en_reg */
	अगर (rt711->hw_ver == RT711_VER_VD0)
		rt711_sdca_index_update_bits(rt711, RT711_VENDOR_CALI,
			RT711_DAC_DC_CALI_CTL1, RT711_DAC_DC_CALI_CLK_EN,
			RT711_DAC_DC_CALI_CLK_EN);

	/* trigger */
	rt711_sdca_index_update_bits(rt711, RT711_VENDOR_CALI,
		RT711_DAC_DC_CALI_CTL1, RT711_DAC_DC_CALI_TRIGGER,
		RT711_DAC_DC_CALI_TRIGGER);

	/* रुको क्रम calibration process */
	rt711_sdca_index_पढ़ो(rt711, RT711_VENDOR_CALI,
		RT711_DAC_DC_CALI_CTL1, &val);

	क्रम (loop_dc = 0; loop_dc < chk_cnt &&
		(val & RT711_DAC_DC_CALI_TRIGGER); loop_dc++) अणु
		usleep_range(10000, 11000);
		ret = rt711_sdca_index_पढ़ो(rt711, RT711_VENDOR_CALI,
			RT711_DAC_DC_CALI_CTL1, &val);
		अगर (ret < 0)
			जाओ _cali_fail_;
	पूर्ण
	अगर (loop_dc == chk_cnt)
		dev_err(dev, "%s, calibration time-out!\n", __func__);

	अगर (loop_dc == chk_cnt || loop_rc == chk_cnt)
		ret = -ETIMEDOUT;

_cali_fail_:
	/* enable impedance sense */
	rt711_sdca_index_update_bits(rt711, RT711_VENDOR_REG,
		RT711_FSM_CTL, RT711_FSM_IMP_EN, RT711_FSM_IMP_EN);

	/* release HP-JD and trigger FSM */
	rt711_sdca_index_ग_लिखो(rt711, RT711_VENDOR_REG,
		RT711_DIGITAL_MISC_CTRL4, 0x201b);

	mutex_unlock(&rt711->calibrate_mutex);
	dev_dbg(dev, "%s calibration complete, ret=%d\n", __func__, ret);
	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक rt711_sdca_button_detect(काष्ठा rt711_sdca_priv *rt711)
अणु
	अचिन्हित पूर्णांक btn_type = 0, offset, idx, val, owner;
	पूर्णांक ret;
	अचिन्हित अक्षर buf[3];

	/* get current UMP message owner */
	ret = regmap_पढ़ो(rt711->regmap,
		SDW_SDCA_CTL(FUNC_NUM_HID, RT711_SDCA_ENT_HID01, RT711_SDCA_CTL_HIDTX_CURRENT_OWNER, 0),
		&owner);
	अगर (ret < 0)
		वापस 0;

	/* अगर owner is device then there is no button event from device */
	अगर (owner == 1)
		वापस 0;

	/* पढ़ो UMP message offset */
	ret = regmap_पढ़ो(rt711->regmap,
		SDW_SDCA_CTL(FUNC_NUM_HID, RT711_SDCA_ENT_HID01, RT711_SDCA_CTL_HIDTX_MESSAGE_OFFSET, 0),
		&offset);
	अगर (ret < 0)
		जाओ _end_btn_det_;

	क्रम (idx = 0; idx < माप(buf); idx++) अणु
		ret = regmap_पढ़ो(rt711->regmap,
			RT711_BUF_ADDR_HID1 + offset + idx, &val);
		अगर (ret < 0)
			जाओ _end_btn_det_;
		buf[idx] = val & 0xff;
	पूर्ण

	अगर (buf[0] == 0x11) अणु
		चयन (buf[1] & 0xf0) अणु
		हाल 0x10:
			btn_type |= SND_JACK_BTN_2;
			अवरोध;
		हाल 0x20:
			btn_type |= SND_JACK_BTN_3;
			अवरोध;
		हाल 0x40:
			btn_type |= SND_JACK_BTN_0;
			अवरोध;
		हाल 0x80:
			btn_type |= SND_JACK_BTN_1;
			अवरोध;
		पूर्ण
		चयन (buf[2]) अणु
		हाल 0x01:
		हाल 0x10:
			btn_type |= SND_JACK_BTN_2;
			अवरोध;
		हाल 0x02:
		हाल 0x20:
			btn_type |= SND_JACK_BTN_3;
			अवरोध;
		हाल 0x04:
		हाल 0x40:
			btn_type |= SND_JACK_BTN_0;
			अवरोध;
		हाल 0x08:
		हाल 0x80:
			btn_type |= SND_JACK_BTN_1;
			अवरोध;
		पूर्ण
	पूर्ण

_end_btn_det_:
	/* Host is owner, so set back to device */
	अगर (owner == 0)
		/* set owner to device */
		regmap_ग_लिखो(rt711->regmap,
			SDW_SDCA_CTL(FUNC_NUM_HID, RT711_SDCA_ENT_HID01,
				RT711_SDCA_CTL_HIDTX_SET_OWNER_TO_DEVICE, 0), 0x01);

	वापस btn_type;
पूर्ण

अटल पूर्णांक rt711_sdca_headset_detect(काष्ठा rt711_sdca_priv *rt711)
अणु
	अचिन्हित पूर्णांक det_mode;
	पूर्णांक ret;

	/* get detected_mode */
	ret = regmap_पढ़ो(rt711->regmap,
		SDW_SDCA_CTL(FUNC_NUM_JACK_CODEC, RT711_SDCA_ENT_GE49, RT711_SDCA_CTL_DETECTED_MODE, 0),
		&det_mode);
	अगर (ret < 0)
		जाओ io_error;

	चयन (det_mode) अणु
	हाल 0x00:
		rt711->jack_type = 0;
		अवरोध;
	हाल 0x03:
		rt711->jack_type = SND_JACK_HEADPHONE;
		अवरोध;
	हाल 0x05:
		rt711->jack_type = SND_JACK_HEADSET;
		अवरोध;
	पूर्ण

	/* ग_लिखो selected_mode */
	अगर (det_mode) अणु
		ret = regmap_ग_लिखो(rt711->regmap,
			SDW_SDCA_CTL(FUNC_NUM_JACK_CODEC, RT711_SDCA_ENT_GE49, RT711_SDCA_CTL_SELECTED_MODE, 0),
			det_mode);
		अगर (ret < 0)
			जाओ io_error;
	पूर्ण

	dev_dbg(&rt711->slave->dev,
		"%s, detected_mode=0x%x\n", __func__, det_mode);

	वापस 0;

io_error:
	pr_err_ratelimited("IO error in %s, ret %d\n", __func__, ret);
	वापस ret;
पूर्ण

अटल व्योम rt711_sdca_jack_detect_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rt711_sdca_priv *rt711 =
		container_of(work, काष्ठा rt711_sdca_priv, jack_detect_work.work);
	पूर्णांक btn_type = 0, ret;

	अगर (!rt711->hs_jack)
		वापस;

	अगर (!rt711->component->card->instantiated)
		वापस;

	/* SDW_SCP_SDCA_INT_SDCA_0 is used क्रम jack detection */
	अगर (rt711->scp_sdca_stat1 & SDW_SCP_SDCA_INT_SDCA_0) अणु
		ret = rt711_sdca_headset_detect(rt711);
		अगर (ret < 0)
			वापस;
	पूर्ण

	/* SDW_SCP_SDCA_INT_SDCA_8 is used क्रम button detection */
	अगर (rt711->scp_sdca_stat2 & SDW_SCP_SDCA_INT_SDCA_8)
		btn_type = rt711_sdca_button_detect(rt711);

	अगर (rt711->jack_type == 0)
		btn_type = 0;

	dev_dbg(&rt711->slave->dev,
		"in %s, jack_type=0x%x\n", __func__, rt711->jack_type);
	dev_dbg(&rt711->slave->dev,
		"in %s, btn_type=0x%x\n", __func__, btn_type);
	dev_dbg(&rt711->slave->dev,
		"in %s, scp_sdca_stat1=0x%x, scp_sdca_stat2=0x%x\n", __func__,
		rt711->scp_sdca_stat1, rt711->scp_sdca_stat2);

	snd_soc_jack_report(rt711->hs_jack, rt711->jack_type | btn_type,
			SND_JACK_HEADSET |
			SND_JACK_BTN_0 | SND_JACK_BTN_1 |
			SND_JACK_BTN_2 | SND_JACK_BTN_3);

	अगर (btn_type) अणु
		/* button released */
		snd_soc_jack_report(rt711->hs_jack, rt711->jack_type,
			SND_JACK_HEADSET |
			SND_JACK_BTN_0 | SND_JACK_BTN_1 |
			SND_JACK_BTN_2 | SND_JACK_BTN_3);

		mod_delayed_work(प्रणाली_घातer_efficient_wq,
			&rt711->jack_btn_check_work, msecs_to_jअगरfies(200));
	पूर्ण
पूर्ण

अटल व्योम rt711_sdca_btn_check_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rt711_sdca_priv *rt711 =
		container_of(work, काष्ठा rt711_sdca_priv, jack_btn_check_work.work);
	पूर्णांक btn_type = 0, ret, idx;
	अचिन्हित पूर्णांक det_mode, offset, val;
	अचिन्हित अक्षर buf[3];

	ret = regmap_पढ़ो(rt711->regmap,
		SDW_SDCA_CTL(FUNC_NUM_JACK_CODEC, RT711_SDCA_ENT_GE49, RT711_SDCA_CTL_DETECTED_MODE, 0),
		&det_mode);
	अगर (ret < 0)
		जाओ io_error;

	/* pin attached */
	अगर (det_mode) अणु
		/* पढ़ो UMP message offset */
		ret = regmap_पढ़ो(rt711->regmap,
			SDW_SDCA_CTL(FUNC_NUM_HID, RT711_SDCA_ENT_HID01, RT711_SDCA_CTL_HIDTX_MESSAGE_OFFSET, 0),
			&offset);
		अगर (ret < 0)
			जाओ io_error;

		क्रम (idx = 0; idx < माप(buf); idx++) अणु
			ret = regmap_पढ़ो(rt711->regmap,
				RT711_BUF_ADDR_HID1 + offset + idx, &val);
			अगर (ret < 0)
				जाओ io_error;
			buf[idx] = val & 0xff;
		पूर्ण

		अगर (buf[0] == 0x11) अणु
			चयन (buf[1] & 0xf0) अणु
			हाल 0x10:
				btn_type |= SND_JACK_BTN_2;
				अवरोध;
			हाल 0x20:
				btn_type |= SND_JACK_BTN_3;
				अवरोध;
			हाल 0x40:
				btn_type |= SND_JACK_BTN_0;
				अवरोध;
			हाल 0x80:
				btn_type |= SND_JACK_BTN_1;
				अवरोध;
			पूर्ण
			चयन (buf[2]) अणु
			हाल 0x01:
			हाल 0x10:
				btn_type |= SND_JACK_BTN_2;
				अवरोध;
			हाल 0x02:
			हाल 0x20:
				btn_type |= SND_JACK_BTN_3;
				अवरोध;
			हाल 0x04:
			हाल 0x40:
				btn_type |= SND_JACK_BTN_0;
				अवरोध;
			हाल 0x08:
			हाल 0x80:
				btn_type |= SND_JACK_BTN_1;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा
		rt711->jack_type = 0;

	dev_dbg(&rt711->slave->dev, "%s, btn_type=0x%x\n",	__func__, btn_type);
	snd_soc_jack_report(rt711->hs_jack, rt711->jack_type | btn_type,
			SND_JACK_HEADSET |
			SND_JACK_BTN_0 | SND_JACK_BTN_1 |
			SND_JACK_BTN_2 | SND_JACK_BTN_3);

	अगर (btn_type) अणु
		/* button released */
		snd_soc_jack_report(rt711->hs_jack, rt711->jack_type,
			SND_JACK_HEADSET |
			SND_JACK_BTN_0 | SND_JACK_BTN_1 |
			SND_JACK_BTN_2 | SND_JACK_BTN_3);

		mod_delayed_work(प्रणाली_घातer_efficient_wq,
			&rt711->jack_btn_check_work, msecs_to_jअगरfies(200));
	पूर्ण

	वापस;

io_error:
	pr_err_ratelimited("IO error in %s, ret %d\n", __func__, ret);
पूर्ण

अटल व्योम rt711_sdca_jack_init(काष्ठा rt711_sdca_priv *rt711)
अणु
	mutex_lock(&rt711->calibrate_mutex);

	अगर (rt711->hs_jack) अणु
		/* Enable HID1 event & set button RTC mode */
		rt711_sdca_index_update_bits(rt711, RT711_VENDOR_HDA_CTL,
			RT711_PUSH_BTN_INT_CTL6, 0x80f0, 0x8000);
		rt711_sdca_index_update_bits(rt711, RT711_VENDOR_HDA_CTL,
			RT711_PUSH_BTN_INT_CTL2, 0x11dd, 0x11dd);
		rt711_sdca_index_ग_लिखो(rt711, RT711_VENDOR_HDA_CTL,
			RT711_PUSH_BTN_INT_CTL7, 0xffff);
		rt711_sdca_index_update_bits(rt711, RT711_VENDOR_HDA_CTL,
			RT711_PUSH_BTN_INT_CTL9, 0xf000, 0x0000);

		/* GE_mode_change_event_en & Hid1_push_button_event_en */
		rt711_sdca_index_update_bits(rt711, RT711_VENDOR_HDA_CTL,
			RT711_GE_MODE_RELATED_CTL, 0x0c00, 0x0c00);

		चयन (rt711->jd_src) अणु
		हाल RT711_JD1:
			/* शेष settings was alपढ़ोy क्रम JD1 */
			अवरोध;
		हाल RT711_JD2:
			rt711_sdca_index_update_bits(rt711, RT711_VENDOR_REG,
				RT711_JD_CTL1, RT711_JD2_DIGITAL_MODE_SEL,
				RT711_JD2_DIGITAL_MODE_SEL);
			rt711_sdca_index_update_bits(rt711, RT711_VENDOR_REG,
				RT711_JD_CTL2, RT711_JD2_2PORT_200K_DECODE_HP | RT711_HP_JD_SEL_JD2,
				RT711_JD2_2PORT_200K_DECODE_HP | RT711_HP_JD_SEL_JD2);
			rt711_sdca_index_update_bits(rt711, RT711_VENDOR_REG,
				RT711_CC_DET1,
				RT711_HP_JD_FINAL_RESULT_CTL_JD12,
				RT711_HP_JD_FINAL_RESULT_CTL_JD12);
			अवरोध;
		शेष:
			dev_warn(rt711->component->dev, "Wrong JD source\n");
			अवरोध;
		पूर्ण

		/* set SCP_SDCA_IntMask1[0]=1 */
		sdw_ग_लिखो_no_pm(rt711->slave, SDW_SCP_SDCA_INTMASK1, SDW_SCP_SDCA_INTMASK_SDCA_0);
		/* set SCP_SDCA_IntMask2[0]=1 */
		sdw_ग_लिखो_no_pm(rt711->slave, SDW_SCP_SDCA_INTMASK2, SDW_SCP_SDCA_INTMASK_SDCA_8);
		dev_dbg(&rt711->slave->dev, "in %s enable\n", __func__);
	पूर्ण अन्यथा अणु
		/* disable HID 1/2 event */
		rt711_sdca_index_update_bits(rt711, RT711_VENDOR_HDA_CTL,
			RT711_GE_MODE_RELATED_CTL, 0x0c00, 0x0000);

		dev_dbg(&rt711->slave->dev, "in %s disable\n", __func__);
	पूर्ण

	mutex_unlock(&rt711->calibrate_mutex);
पूर्ण

अटल पूर्णांक rt711_sdca_set_jack_detect(काष्ठा snd_soc_component *component,
	काष्ठा snd_soc_jack *hs_jack, व्योम *data)
अणु
	काष्ठा rt711_sdca_priv *rt711 = snd_soc_component_get_drvdata(component);

	rt711->hs_jack = hs_jack;

	अगर (!rt711->hw_init) अणु
		dev_dbg(&rt711->slave->dev,
			"%s hw_init not ready yet\n", __func__);
		वापस 0;
	पूर्ण

	rt711_sdca_jack_init(rt711);
	वापस 0;
पूर्ण

/* For SDCA control DAC/ADC Gain */
अटल पूर्णांक rt711_sdca_set_gain_put(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा soc_mixer_control *mc =
		(काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	काष्ठा rt711_sdca_priv *rt711 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक पढ़ो_l, पढ़ो_r, gain_l_val, gain_r_val;
	अचिन्हित पूर्णांक i, adc_vol_flag = 0, changed = 0;
	अचिन्हित पूर्णांक lvalue, rvalue;

	अगर (म_माला(ucontrol->id.name, "FU1E Capture Volume") ||
		म_माला(ucontrol->id.name, "FU0F Capture Volume"))
		adc_vol_flag = 1;

	regmap_पढ़ो(rt711->mbq_regmap, mc->reg, &lvalue);
	regmap_पढ़ो(rt711->mbq_regmap, mc->rreg, &rvalue);

	/* control value to 2's complement value */
	/* L Channel */
	gain_l_val = ucontrol->value.पूर्णांकeger.value[0];
	अगर (gain_l_val > mc->max)
		gain_l_val = mc->max;
	पढ़ो_l = gain_l_val;

	अगर (mc->shअगरt == 8) /* boost gain */
		gain_l_val = (gain_l_val * 10) << mc->shअगरt;
	अन्यथा अणु /* ADC/DAC gain */
		अगर (adc_vol_flag && gain_l_val > mc->shअगरt)
			gain_l_val = (gain_l_val - mc->shअगरt) * 75;
		अन्यथा
			gain_l_val = (mc->shअगरt - gain_l_val) * 75;
		gain_l_val <<= 8;
		gain_l_val /= 100;
		अगर (!(adc_vol_flag && पढ़ो_l > mc->shअगरt)) अणु
			gain_l_val = ~gain_l_val;
			gain_l_val += 1;
		पूर्ण
		gain_l_val &= 0xffff;
	पूर्ण

	/* R Channel */
	gain_r_val = ucontrol->value.पूर्णांकeger.value[1];
	अगर (gain_r_val > mc->max)
		gain_r_val = mc->max;
	पढ़ो_r = gain_r_val;

	अगर (mc->shअगरt == 8) /* boost gain */
		gain_r_val = (gain_r_val * 10) << mc->shअगरt;
	अन्यथा अणु /* ADC/DAC gain */
		अगर (adc_vol_flag && gain_r_val > mc->shअगरt)
			gain_r_val = (gain_r_val - mc->shअगरt) * 75;
		अन्यथा
			gain_r_val = (mc->shअगरt - gain_r_val) * 75;
		gain_r_val <<= 8;
		gain_r_val /= 100;
		अगर (!(adc_vol_flag && पढ़ो_r > mc->shअगरt)) अणु
			gain_r_val = ~gain_r_val;
			gain_r_val += 1;
		पूर्ण
		gain_r_val &= 0xffff;
	पूर्ण

	अगर (lvalue != gain_l_val || rvalue != gain_r_val)
		changed = 1;
	अन्यथा
		वापस 0;

	क्रम (i = 0; i < 3; i++) अणु /* retry 3 बार at most */
		/* Lch*/
		regmap_ग_लिखो(rt711->mbq_regmap, mc->reg, gain_l_val);

		/* Rch */
		regmap_ग_लिखो(rt711->mbq_regmap, mc->rreg, gain_r_val);

		regmap_पढ़ो(rt711->mbq_regmap, mc->reg, &पढ़ो_l);
		regmap_पढ़ो(rt711->mbq_regmap, mc->rreg, &पढ़ो_r);
		अगर (पढ़ो_r == gain_r_val && पढ़ो_l == gain_l_val)
			अवरोध;
	पूर्ण

	वापस i == 3 ? -EIO : changed;
पूर्ण

अटल पूर्णांक rt711_sdca_set_gain_get(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा rt711_sdca_priv *rt711 = snd_soc_component_get_drvdata(component);
	काष्ठा soc_mixer_control *mc =
		(काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक पढ़ो_l, पढ़ो_r, ctl_l = 0, ctl_r = 0;
	अचिन्हित पूर्णांक adc_vol_flag = 0, neg_flag = 0;

	अगर (म_माला(ucontrol->id.name, "FU1E Capture Volume") ||
		म_माला(ucontrol->id.name, "FU0F Capture Volume"))
		adc_vol_flag = 1;

	regmap_पढ़ो(rt711->mbq_regmap, mc->reg, &पढ़ो_l);
	regmap_पढ़ो(rt711->mbq_regmap, mc->rreg, &पढ़ो_r);

	/* 2's complement value to control value */
	अगर (mc->shअगरt == 8) /* boost gain */
		ctl_l = (पढ़ो_l >> mc->shअगरt) / 10;
	अन्यथा अणु /* ADC/DAC gain */
		ctl_l = पढ़ो_l;
		अगर (पढ़ो_l & BIT(15)) अणु
			ctl_l = 0xffff & ~(पढ़ो_l - 1);
			neg_flag = 1;
		पूर्ण
		ctl_l *= 100;
		ctl_l >>= 8;
		अगर (adc_vol_flag) अणु
			अगर (neg_flag)
				ctl_l = mc->shअगरt - (ctl_l / 75);
			अन्यथा
				ctl_l = mc->shअगरt + (ctl_l / 75);
		पूर्ण अन्यथा
			ctl_l = mc->max - (ctl_l / 75);
	पूर्ण

	neg_flag = 0;
	अगर (पढ़ो_l != पढ़ो_r) अणु
		अगर (mc->shअगरt == 8) /* boost gain */
			ctl_r = (पढ़ो_r >> mc->shअगरt) / 10;
		अन्यथा अणु /* ADC/DAC gain */
			ctl_r = पढ़ो_r;
			अगर (पढ़ो_r & BIT(15)) अणु
				ctl_r = 0xffff & ~(पढ़ो_r - 1);
				neg_flag = 1;
			पूर्ण
			ctl_r *= 100;
			ctl_r >>= 8;
			अगर (adc_vol_flag) अणु
				अगर (neg_flag)
					ctl_r = mc->shअगरt - (ctl_r / 75);
				अन्यथा
					ctl_r = mc->shअगरt + (ctl_r / 75);
			पूर्ण अन्यथा
				ctl_r = mc->max - (ctl_r / 75);
		पूर्ण
	पूर्ण अन्यथा
		ctl_r = ctl_l;

	ucontrol->value.पूर्णांकeger.value[0] = ctl_l;
	ucontrol->value.पूर्णांकeger.value[1] = ctl_r;

	वापस 0;
पूर्ण

अटल पूर्णांक rt711_sdca_set_fu0f_capture_ctl(काष्ठा rt711_sdca_priv *rt711)
अणु
	पूर्णांक err;
	अचिन्हित पूर्णांक ch_l, ch_r;

	ch_l = (rt711->fu0f_dapm_mute || rt711->fu0f_mixer_l_mute) ? 0x01 : 0x00;
	ch_r = (rt711->fu0f_dapm_mute || rt711->fu0f_mixer_r_mute) ? 0x01 : 0x00;

	err = regmap_ग_लिखो(rt711->regmap,
			SDW_SDCA_CTL(FUNC_NUM_JACK_CODEC, RT711_SDCA_ENT_USER_FU0F,
			RT711_SDCA_CTL_FU_MUTE, CH_L), ch_l);
	अगर (err < 0)
		वापस err;

	err = regmap_ग_लिखो(rt711->regmap,
			SDW_SDCA_CTL(FUNC_NUM_JACK_CODEC, RT711_SDCA_ENT_USER_FU0F,
			RT711_SDCA_CTL_FU_MUTE, CH_R), ch_r);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक rt711_sdca_set_fu1e_capture_ctl(काष्ठा rt711_sdca_priv *rt711)
अणु
	पूर्णांक err;
	अचिन्हित पूर्णांक ch_l, ch_r;

	ch_l = (rt711->fu1e_dapm_mute || rt711->fu1e_mixer_l_mute) ? 0x01 : 0x00;
	ch_r = (rt711->fu1e_dapm_mute || rt711->fu1e_mixer_r_mute) ? 0x01 : 0x00;

	err = regmap_ग_लिखो(rt711->regmap,
			SDW_SDCA_CTL(FUNC_NUM_MIC_ARRAY, RT711_SDCA_ENT_USER_FU1E,
			RT711_SDCA_CTL_FU_MUTE, CH_L), ch_l);
	अगर (err < 0)
		वापस err;

	err = regmap_ग_लिखो(rt711->regmap,
			SDW_SDCA_CTL(FUNC_NUM_MIC_ARRAY, RT711_SDCA_ENT_USER_FU1E,
			RT711_SDCA_CTL_FU_MUTE, CH_R), ch_r);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक rt711_sdca_fu1e_capture_get(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा rt711_sdca_priv *rt711 = snd_soc_component_get_drvdata(component);

	ucontrol->value.पूर्णांकeger.value[0] = !rt711->fu1e_mixer_l_mute;
	ucontrol->value.पूर्णांकeger.value[1] = !rt711->fu1e_mixer_r_mute;
	वापस 0;
पूर्ण

अटल पूर्णांक rt711_sdca_fu1e_capture_put(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा rt711_sdca_priv *rt711 = snd_soc_component_get_drvdata(component);
	पूर्णांक err, changed = 0;

	अगर (rt711->fu1e_mixer_l_mute != !ucontrol->value.पूर्णांकeger.value[0] ||
		rt711->fu1e_mixer_r_mute != !ucontrol->value.पूर्णांकeger.value[1])
		changed = 1;

	rt711->fu1e_mixer_l_mute = !ucontrol->value.पूर्णांकeger.value[0];
	rt711->fu1e_mixer_r_mute = !ucontrol->value.पूर्णांकeger.value[1];
	err = rt711_sdca_set_fu1e_capture_ctl(rt711);
	अगर (err < 0)
		वापस err;

	वापस changed;
पूर्ण

अटल पूर्णांक rt711_sdca_fu0f_capture_get(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा rt711_sdca_priv *rt711 = snd_soc_component_get_drvdata(component);

	ucontrol->value.पूर्णांकeger.value[0] = !rt711->fu0f_mixer_l_mute;
	ucontrol->value.पूर्णांकeger.value[1] = !rt711->fu0f_mixer_r_mute;
	वापस 0;
पूर्ण

अटल पूर्णांक rt711_sdca_fu0f_capture_put(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा rt711_sdca_priv *rt711 = snd_soc_component_get_drvdata(component);
	पूर्णांक err, changed = 0;

	अगर (rt711->fu0f_mixer_l_mute != !ucontrol->value.पूर्णांकeger.value[0] ||
		rt711->fu0f_mixer_r_mute != !ucontrol->value.पूर्णांकeger.value[1])
		changed = 1;

	rt711->fu0f_mixer_l_mute = !ucontrol->value.पूर्णांकeger.value[0];
	rt711->fu0f_mixer_r_mute = !ucontrol->value.पूर्णांकeger.value[1];
	err = rt711_sdca_set_fu0f_capture_ctl(rt711);
	अगर (err < 0)
		वापस err;

	वापस changed;
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(out_vol_tlv, -6525, 75, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(in_vol_tlv, -1725, 75, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(mic_vol_tlv, 0, 1000, 0);

अटल स्थिर काष्ठा snd_kcontrol_new rt711_sdca_snd_controls[] = अणु
	SOC_DOUBLE_R_EXT_TLV("FU05 Playback Volume",
		SDW_SDCA_CTL(FUNC_NUM_JACK_CODEC, RT711_SDCA_ENT_USER_FU05, RT711_SDCA_CTL_FU_VOLUME, CH_L),
		SDW_SDCA_CTL(FUNC_NUM_JACK_CODEC, RT711_SDCA_ENT_USER_FU05, RT711_SDCA_CTL_FU_VOLUME, CH_R),
		0x57, 0x57, 0,
		rt711_sdca_set_gain_get, rt711_sdca_set_gain_put, out_vol_tlv),
	SOC_DOUBLE_EXT("FU1E Capture Switch", SND_SOC_NOPM, 0, 1, 1, 0,
		rt711_sdca_fu1e_capture_get, rt711_sdca_fu1e_capture_put),
	SOC_DOUBLE_EXT("FU0F Capture Switch", SND_SOC_NOPM, 0, 1, 1, 0,
		rt711_sdca_fu0f_capture_get, rt711_sdca_fu0f_capture_put),
	SOC_DOUBLE_R_EXT_TLV("FU1E Capture Volume",
		SDW_SDCA_CTL(FUNC_NUM_MIC_ARRAY, RT711_SDCA_ENT_USER_FU1E, RT711_SDCA_CTL_FU_VOLUME, CH_L),
		SDW_SDCA_CTL(FUNC_NUM_MIC_ARRAY, RT711_SDCA_ENT_USER_FU1E, RT711_SDCA_CTL_FU_VOLUME, CH_R),
		0x17, 0x3f, 0,
		rt711_sdca_set_gain_get, rt711_sdca_set_gain_put, in_vol_tlv),
	SOC_DOUBLE_R_EXT_TLV("FU0F Capture Volume",
		SDW_SDCA_CTL(FUNC_NUM_JACK_CODEC, RT711_SDCA_ENT_USER_FU0F, RT711_SDCA_CTL_FU_VOLUME, CH_L),
		SDW_SDCA_CTL(FUNC_NUM_JACK_CODEC, RT711_SDCA_ENT_USER_FU0F, RT711_SDCA_CTL_FU_VOLUME, CH_R),
		0x17, 0x3f, 0,
		rt711_sdca_set_gain_get, rt711_sdca_set_gain_put, in_vol_tlv),
	SOC_DOUBLE_R_EXT_TLV("FU44 Gain Volume",
		SDW_SDCA_CTL(FUNC_NUM_JACK_CODEC, RT711_SDCA_ENT_PLATFORM_FU44, RT711_SDCA_CTL_FU_CH_GAIN, CH_L),
		SDW_SDCA_CTL(FUNC_NUM_JACK_CODEC, RT711_SDCA_ENT_PLATFORM_FU44, RT711_SDCA_CTL_FU_CH_GAIN, CH_R),
		8, 3, 0,
		rt711_sdca_set_gain_get, rt711_sdca_set_gain_put, mic_vol_tlv),
	SOC_DOUBLE_R_EXT_TLV("FU15 Gain Volume",
		SDW_SDCA_CTL(FUNC_NUM_MIC_ARRAY, RT711_SDCA_ENT_PLATFORM_FU15, RT711_SDCA_CTL_FU_CH_GAIN, CH_L),
		SDW_SDCA_CTL(FUNC_NUM_MIC_ARRAY, RT711_SDCA_ENT_PLATFORM_FU15, RT711_SDCA_CTL_FU_CH_GAIN, CH_R),
		8, 3, 0,
		rt711_sdca_set_gain_get, rt711_sdca_set_gain_put, mic_vol_tlv),
पूर्ण;

अटल पूर्णांक rt711_sdca_mux_get(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_kcontrol_component(kcontrol);
	काष्ठा rt711_sdca_priv *rt711 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक val = 0, mask_sft;

	अगर (म_माला(ucontrol->id.name, "ADC 22 Mux"))
		mask_sft = 10;
	अन्यथा अगर (म_माला(ucontrol->id.name, "ADC 23 Mux"))
		mask_sft = 13;
	अन्यथा
		वापस -EINVAL;

	rt711_sdca_index_पढ़ो(rt711, RT711_VENDOR_HDA_CTL,
		RT711_HDA_LEGACY_MUX_CTL1, &val);

	ucontrol->value.क्रमागतerated.item[0] = (val >> mask_sft) & 0x7;

	वापस 0;
पूर्ण

अटल पूर्णांक rt711_sdca_mux_put(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_kcontrol_component(kcontrol);
	काष्ठा snd_soc_dapm_context *dapm =
		snd_soc_dapm_kcontrol_dapm(kcontrol);
	काष्ठा rt711_sdca_priv *rt711 = snd_soc_component_get_drvdata(component);
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक *item = ucontrol->value.क्रमागतerated.item;
	अचिन्हित पूर्णांक val, val2 = 0, change, mask_sft;

	अगर (item[0] >= e->items)
		वापस -EINVAL;

	अगर (म_माला(ucontrol->id.name, "ADC 22 Mux"))
		mask_sft = 10;
	अन्यथा अगर (म_माला(ucontrol->id.name, "ADC 23 Mux"))
		mask_sft = 13;
	अन्यथा
		वापस -EINVAL;

	val = snd_soc_क्रमागत_item_to_val(e, item[0]) << e->shअगरt_l;

	rt711_sdca_index_पढ़ो(rt711, RT711_VENDOR_HDA_CTL,
		RT711_HDA_LEGACY_MUX_CTL1, &val2);
	val2 = (val2 >> mask_sft) & 0x7;

	अगर (val == val2)
		change = 0;
	अन्यथा
		change = 1;

	अगर (change)
		rt711_sdca_index_update_bits(rt711, RT711_VENDOR_HDA_CTL,
			RT711_HDA_LEGACY_MUX_CTL1, 0x7 << mask_sft,
			val << mask_sft);

	snd_soc_dapm_mux_update_घातer(dapm, kcontrol,
		item[0], e, शून्य);

	वापस change;
पूर्ण

अटल स्थिर अक्षर * स्थिर adc_mux_text[] = अणु
	"MIC2",
	"LINE1",
	"LINE2",
	"DMIC",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt711_adc22_क्रमागत, SND_SOC_NOPM, 0, adc_mux_text);

अटल SOC_ENUM_SINGLE_DECL(
	rt711_adc23_क्रमागत, SND_SOC_NOPM, 0, adc_mux_text);

अटल स्थिर काष्ठा snd_kcontrol_new rt711_sdca_adc22_mux =
	SOC_DAPM_ENUM_EXT("ADC 22 Mux", rt711_adc22_क्रमागत,
			rt711_sdca_mux_get, rt711_sdca_mux_put);

अटल स्थिर काष्ठा snd_kcontrol_new rt711_sdca_adc23_mux =
	SOC_DAPM_ENUM_EXT("ADC 23 Mux", rt711_adc23_क्रमागत,
			rt711_sdca_mux_get, rt711_sdca_mux_put);

अटल पूर्णांक rt711_sdca_fu05_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	काष्ठा rt711_sdca_priv *rt711 = snd_soc_component_get_drvdata(component);
	अचिन्हित अक्षर unmute = 0x0, mute = 0x1;

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		regmap_ग_लिखो(rt711->regmap,
			SDW_SDCA_CTL(FUNC_NUM_JACK_CODEC, RT711_SDCA_ENT_USER_FU05,
				RT711_SDCA_CTL_FU_MUTE, CH_L),
				unmute);
		regmap_ग_लिखो(rt711->regmap,
			SDW_SDCA_CTL(FUNC_NUM_JACK_CODEC, RT711_SDCA_ENT_USER_FU05,
				RT711_SDCA_CTL_FU_MUTE, CH_R),
				unmute);
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		regmap_ग_लिखो(rt711->regmap,
			SDW_SDCA_CTL(FUNC_NUM_JACK_CODEC, RT711_SDCA_ENT_USER_FU05,
				RT711_SDCA_CTL_FU_MUTE, CH_L),
				mute);
		regmap_ग_लिखो(rt711->regmap,
			SDW_SDCA_CTL(FUNC_NUM_JACK_CODEC, RT711_SDCA_ENT_USER_FU05,
				RT711_SDCA_CTL_FU_MUTE, CH_R),
				mute);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rt711_sdca_fu0f_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	काष्ठा rt711_sdca_priv *rt711 = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		rt711->fu0f_dapm_mute = false;
		rt711_sdca_set_fu0f_capture_ctl(rt711);
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		rt711->fu0f_dapm_mute = true;
		rt711_sdca_set_fu0f_capture_ctl(rt711);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rt711_sdca_fu1e_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	काष्ठा rt711_sdca_priv *rt711 = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		rt711->fu1e_dapm_mute = false;
		rt711_sdca_set_fu1e_capture_ctl(rt711);
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		rt711->fu1e_dapm_mute = true;
		rt711_sdca_set_fu1e_capture_ctl(rt711);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rt711_sdca_pde28_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	काष्ठा rt711_sdca_priv *rt711 = snd_soc_component_get_drvdata(component);
	अचिन्हित अक्षर ps0 = 0x0, ps3 = 0x3;

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		regmap_ग_लिखो(rt711->regmap,
			SDW_SDCA_CTL(FUNC_NUM_JACK_CODEC, RT711_SDCA_ENT_PDE28,
				RT711_SDCA_CTL_REQ_POWER_STATE, 0),
				ps0);
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		regmap_ग_लिखो(rt711->regmap,
			SDW_SDCA_CTL(FUNC_NUM_JACK_CODEC, RT711_SDCA_ENT_PDE28,
				RT711_SDCA_CTL_REQ_POWER_STATE, 0),
				ps3);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rt711_sdca_pde29_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	काष्ठा rt711_sdca_priv *rt711 = snd_soc_component_get_drvdata(component);
	अचिन्हित अक्षर ps0 = 0x0, ps3 = 0x3;

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		regmap_ग_लिखो(rt711->regmap,
			SDW_SDCA_CTL(FUNC_NUM_JACK_CODEC, RT711_SDCA_ENT_PDE29,
				RT711_SDCA_CTL_REQ_POWER_STATE, 0),
				ps0);
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		regmap_ग_लिखो(rt711->regmap,
			SDW_SDCA_CTL(FUNC_NUM_JACK_CODEC, RT711_SDCA_ENT_PDE29,
				RT711_SDCA_CTL_REQ_POWER_STATE, 0),
				ps3);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rt711_sdca_pde2a_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	काष्ठा rt711_sdca_priv *rt711 = snd_soc_component_get_drvdata(component);
	अचिन्हित अक्षर ps0 = 0x0, ps3 = 0x3;

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		regmap_ग_लिखो(rt711->regmap,
			SDW_SDCA_CTL(FUNC_NUM_MIC_ARRAY, RT711_SDCA_ENT_PDE2A,
				RT711_SDCA_CTL_REQ_POWER_STATE, 0),
				ps0);
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		regmap_ग_लिखो(rt711->regmap,
			SDW_SDCA_CTL(FUNC_NUM_MIC_ARRAY, RT711_SDCA_ENT_PDE2A,
				RT711_SDCA_CTL_REQ_POWER_STATE, 0),
				ps3);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rt711_sdca_line1_घातer_event(काष्ठा snd_soc_dapm_widget *w,
			काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	काष्ठा rt711_sdca_priv *rt711 = snd_soc_component_get_drvdata(component);
	अटल अचिन्हित पूर्णांक sel_mode = 0xffff;

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		regmap_पढ़ो(rt711->regmap,
			SDW_SDCA_CTL(FUNC_NUM_JACK_CODEC, RT711_SDCA_ENT_GE49,
				RT711_SDCA_CTL_SELECTED_MODE, 0),
				&sel_mode);
		regmap_ग_लिखो(rt711->regmap,
			SDW_SDCA_CTL(FUNC_NUM_JACK_CODEC, RT711_SDCA_ENT_LINE1,
				RT711_SDCA_CTL_VENDOR_DEF, 0),
				0x1);
		regmap_ग_लिखो(rt711->regmap,
			SDW_SDCA_CTL(FUNC_NUM_JACK_CODEC, RT711_SDCA_ENT_GE49,
				RT711_SDCA_CTL_SELECTED_MODE, 0),
				0x7);
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		regmap_ग_लिखो(rt711->regmap,
			SDW_SDCA_CTL(FUNC_NUM_JACK_CODEC, RT711_SDCA_ENT_LINE1,
				RT711_SDCA_CTL_VENDOR_DEF, 0),
				0x0);
		अगर (sel_mode != 0xffff)
			regmap_ग_लिखो(rt711->regmap,
				SDW_SDCA_CTL(FUNC_NUM_JACK_CODEC, RT711_SDCA_ENT_GE49,
				RT711_SDCA_CTL_SELECTED_MODE, 0),
				sel_mode);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt711_sdca_line2_घातer_event(काष्ठा snd_soc_dapm_widget *w,
			काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	काष्ठा rt711_sdca_priv *rt711 = snd_soc_component_get_drvdata(component);
	अचिन्हित अक्षर ps0 = 0x0, ps3 = 0x3;

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		regmap_ग_लिखो(rt711->regmap,
			SDW_SDCA_CTL(FUNC_NUM_JACK_CODEC, RT711_SDCA_ENT_PDELINE2,
				RT711_SDCA_CTL_REQ_POWER_STATE, 0),
				ps0);
		regmap_ग_लिखो(rt711->regmap,
			SDW_SDCA_CTL(FUNC_NUM_JACK_CODEC, RT711_SDCA_ENT_LINE2,
				RT711_SDCA_CTL_VENDOR_DEF, 0),
				0x1);
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		regmap_ग_लिखो(rt711->regmap,
			SDW_SDCA_CTL(FUNC_NUM_JACK_CODEC, RT711_SDCA_ENT_LINE2,
				RT711_SDCA_CTL_VENDOR_DEF, 0),
				0x0);
		regmap_ग_लिखो(rt711->regmap,
			SDW_SDCA_CTL(FUNC_NUM_JACK_CODEC, RT711_SDCA_ENT_PDELINE2,
				RT711_SDCA_CTL_REQ_POWER_STATE, 0),
				ps3);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget rt711_sdca_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_OUTPUT("HP"),
	SND_SOC_DAPM_INPUT("MIC2"),
	SND_SOC_DAPM_INPUT("DMIC1"),
	SND_SOC_DAPM_INPUT("DMIC2"),
	SND_SOC_DAPM_INPUT("LINE1"),
	SND_SOC_DAPM_INPUT("LINE2"),

	SND_SOC_DAPM_PGA_E("LINE1 Power", SND_SOC_NOPM,
		0, 0, शून्य, 0, rt711_sdca_line1_घातer_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),
	SND_SOC_DAPM_PGA_E("LINE2 Power", SND_SOC_NOPM,
		0, 0, शून्य, 0, rt711_sdca_line2_घातer_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),

	SND_SOC_DAPM_SUPPLY("PDE 28", SND_SOC_NOPM, 0, 0,
		rt711_sdca_pde28_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),
	SND_SOC_DAPM_SUPPLY("PDE 29", SND_SOC_NOPM, 0, 0,
		rt711_sdca_pde29_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),
	SND_SOC_DAPM_SUPPLY("PDE 2A", SND_SOC_NOPM, 0, 0,
		rt711_sdca_pde2a_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),

	SND_SOC_DAPM_DAC_E("FU 05", शून्य, SND_SOC_NOPM, 0, 0,
		rt711_sdca_fu05_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),
	SND_SOC_DAPM_ADC_E("FU 0F", शून्य, SND_SOC_NOPM, 0, 0,
		rt711_sdca_fu0f_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),
	SND_SOC_DAPM_ADC_E("FU 1E", शून्य, SND_SOC_NOPM, 0, 0,
		rt711_sdca_fu1e_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),
	SND_SOC_DAPM_MUX("ADC 22 Mux", SND_SOC_NOPM, 0, 0,
		&rt711_sdca_adc22_mux),
	SND_SOC_DAPM_MUX("ADC 23 Mux", SND_SOC_NOPM, 0, 0,
		&rt711_sdca_adc23_mux),

	SND_SOC_DAPM_AIF_IN("DP3RX", "DP3 Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("DP2TX", "DP2 Capture", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("DP4TX", "DP4 Capture", 0, SND_SOC_NOPM, 0, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route rt711_sdca_audio_map[] = अणु
	अणु"FU 05", शून्य, "DP3RX"पूर्ण,
	अणु"DP2TX", शून्य, "FU 0F"पूर्ण,
	अणु"DP4TX", शून्य, "FU 1E"पूर्ण,

	अणु"LINE1 Power", शून्य, "LINE1"पूर्ण,
	अणु"LINE2 Power", शून्य, "LINE2"पूर्ण,
	अणु"HP", शून्य, "PDE 28"पूर्ण,
	अणु"FU 0F", शून्य, "PDE 29"पूर्ण,
	अणु"FU 1E", शून्य, "PDE 2A"पूर्ण,

	अणु"FU 0F", शून्य, "ADC 22 Mux"पूर्ण,
	अणु"FU 1E", शून्य, "ADC 23 Mux"पूर्ण,
	अणु"ADC 22 Mux", "DMIC", "DMIC1"पूर्ण,
	अणु"ADC 22 Mux", "LINE1", "LINE1 Power"पूर्ण,
	अणु"ADC 22 Mux", "LINE2", "LINE2 Power"पूर्ण,
	अणु"ADC 22 Mux", "MIC2", "MIC2"पूर्ण,
	अणु"ADC 23 Mux", "DMIC", "DMIC2"पूर्ण,
	अणु"ADC 23 Mux", "LINE1", "LINE1 Power"पूर्ण,
	अणु"ADC 23 Mux", "LINE2", "LINE2 Power"पूर्ण,
	अणु"ADC 23 Mux", "MIC2", "MIC2"पूर्ण,

	अणु"HP", शून्य, "FU 05"पूर्ण,
पूर्ण;

अटल पूर्णांक rt711_sdca_parse_dt(काष्ठा rt711_sdca_priv *rt711, काष्ठा device *dev)
अणु
	device_property_पढ़ो_u32(dev, "realtek,jd-src", &rt711->jd_src);

	वापस 0;
पूर्ण

अटल पूर्णांक rt711_sdca_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt711_sdca_priv *rt711 = snd_soc_component_get_drvdata(component);

	rt711_sdca_parse_dt(rt711, &rt711->slave->dev);
	rt711->component = component;

	वापस 0;
पूर्ण

अटल व्योम rt711_sdca_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt711_sdca_priv *rt711 = snd_soc_component_get_drvdata(component);

	regcache_cache_only(rt711->regmap, true);
	regcache_cache_only(rt711->mbq_regmap, true);
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_sdca_dev_rt711 = अणु
	.probe = rt711_sdca_probe,
	.controls = rt711_sdca_snd_controls,
	.num_controls = ARRAY_SIZE(rt711_sdca_snd_controls),
	.dapm_widमाला_लो = rt711_sdca_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(rt711_sdca_dapm_widमाला_लो),
	.dapm_routes = rt711_sdca_audio_map,
	.num_dapm_routes = ARRAY_SIZE(rt711_sdca_audio_map),
	.set_jack = rt711_sdca_set_jack_detect,
	.हटाओ = rt711_sdca_हटाओ,
पूर्ण;

अटल पूर्णांक rt711_sdca_set_sdw_stream(काष्ठा snd_soc_dai *dai, व्योम *sdw_stream,
				पूर्णांक direction)
अणु
	काष्ठा sdw_stream_data *stream;

	अगर (!sdw_stream)
		वापस 0;

	stream = kzalloc(माप(*stream), GFP_KERNEL);
	अगर (!stream)
		वापस -ENOMEM;

	stream->sdw_stream = sdw_stream;

	/* Use tx_mask or rx_mask to configure stream tag and set dma_data */
	अगर (direction == SNDRV_PCM_STREAM_PLAYBACK)
		dai->playback_dma_data = stream;
	अन्यथा
		dai->capture_dma_data = stream;

	वापस 0;
पूर्ण

अटल व्योम rt711_sdca_shutकरोwn(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा sdw_stream_data *stream;

	stream = snd_soc_dai_get_dma_data(dai, substream);
	snd_soc_dai_set_dma_data(dai, substream, शून्य);
	kमुक्त(stream);
पूर्ण

अटल पूर्णांक rt711_sdca_pcm_hw_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt711_sdca_priv *rt711 = snd_soc_component_get_drvdata(component);
	काष्ठा sdw_stream_config stream_config;
	काष्ठा sdw_port_config port_config;
	क्रमागत sdw_data_direction direction;
	काष्ठा sdw_stream_data *stream;
	पूर्णांक retval, port, num_channels;
	अचिन्हित पूर्णांक sampling_rate;

	dev_dbg(dai->dev, "%s %s", __func__, dai->name);
	stream = snd_soc_dai_get_dma_data(dai, substream);

	अगर (!stream)
		वापस -EINVAL;

	अगर (!rt711->slave)
		वापस -EINVAL;

	/* SoundWire specअगरic configuration */
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		direction = SDW_DATA_सूची_RX;
		port = 3;
	पूर्ण अन्यथा अणु
		direction = SDW_DATA_सूची_TX;
		अगर (dai->id == RT711_AIF1)
			port = 2;
		अन्यथा अगर (dai->id == RT711_AIF2)
			port = 4;
		अन्यथा
			वापस -EINVAL;
	पूर्ण

	stream_config.frame_rate = params_rate(params);
	stream_config.ch_count = params_channels(params);
	stream_config.bps = snd_pcm_क्रमmat_width(params_क्रमmat(params));
	stream_config.direction = direction;

	num_channels = params_channels(params);
	port_config.ch_mask = GENMASK(num_channels - 1, 0);
	port_config.num = port;

	retval = sdw_stream_add_slave(rt711->slave, &stream_config,
					&port_config, 1, stream->sdw_stream);
	अगर (retval) अणु
		dev_err(dai->dev, "Unable to configure port\n");
		वापस retval;
	पूर्ण

	अगर (params_channels(params) > 16) अणु
		dev_err(component->dev, "Unsupported channels %d\n",
			params_channels(params));
		वापस -EINVAL;
	पूर्ण

	/* sampling rate configuration */
	चयन (params_rate(params)) अणु
	हाल 44100:
		sampling_rate = RT711_SDCA_RATE_44100HZ;
		अवरोध;
	हाल 48000:
		sampling_rate = RT711_SDCA_RATE_48000HZ;
		अवरोध;
	हाल 96000:
		sampling_rate = RT711_SDCA_RATE_96000HZ;
		अवरोध;
	हाल 192000:
		sampling_rate = RT711_SDCA_RATE_192000HZ;
		अवरोध;
	शेष:
		dev_err(component->dev, "Rate %d is not supported\n",
			params_rate(params));
		वापस -EINVAL;
	पूर्ण

	/* set sampling frequency */
	regmap_ग_लिखो(rt711->regmap,
		SDW_SDCA_CTL(FUNC_NUM_JACK_CODEC, RT711_SDCA_ENT_CS01, RT711_SDCA_CTL_SAMPLE_FREQ_INDEX, 0),
		sampling_rate);
	regmap_ग_लिखो(rt711->regmap,
		SDW_SDCA_CTL(FUNC_NUM_JACK_CODEC, RT711_SDCA_ENT_CS11, RT711_SDCA_CTL_SAMPLE_FREQ_INDEX, 0),
		sampling_rate);
	regmap_ग_लिखो(rt711->regmap,
		SDW_SDCA_CTL(FUNC_NUM_MIC_ARRAY, RT711_SDCA_ENT_CS1F, RT711_SDCA_CTL_SAMPLE_FREQ_INDEX, 0),
		sampling_rate);

	वापस 0;
पूर्ण

अटल पूर्णांक rt711_sdca_pcm_hw_मुक्त(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt711_sdca_priv *rt711 = snd_soc_component_get_drvdata(component);
	काष्ठा sdw_stream_data *stream =
		snd_soc_dai_get_dma_data(dai, substream);

	अगर (!rt711->slave)
		वापस -EINVAL;

	sdw_stream_हटाओ_slave(rt711->slave, stream->sdw_stream);
	वापस 0;
पूर्ण

#घोषणा RT711_STEREO_RATES (SNDRV_PCM_RATE_44100 | SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_96000 | \
			SNDRV_PCM_RATE_192000)
#घोषणा RT711_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE | \
			SNDRV_PCM_FMTBIT_S24_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops rt711_sdca_ops = अणु
	.hw_params	= rt711_sdca_pcm_hw_params,
	.hw_मुक्त	= rt711_sdca_pcm_hw_मुक्त,
	.set_sdw_stream	= rt711_sdca_set_sdw_stream,
	.shutकरोwn	= rt711_sdca_shutकरोwn,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver rt711_sdca_dai[] = अणु
	अणु
		.name = "rt711-sdca-aif1",
		.id = RT711_AIF1,
		.playback = अणु
			.stream_name = "DP3 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT711_STEREO_RATES,
			.क्रमmats = RT711_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "DP2 Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT711_STEREO_RATES,
			.क्रमmats = RT711_FORMATS,
		पूर्ण,
		.ops = &rt711_sdca_ops,
	पूर्ण,
	अणु
		.name = "rt711-sdca-aif2",
		.id = RT711_AIF2,
		.capture = अणु
			.stream_name = "DP4 Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT711_STEREO_RATES,
			.क्रमmats = RT711_FORMATS,
		पूर्ण,
		.ops = &rt711_sdca_ops,
	पूर्ण
पूर्ण;

पूर्णांक rt711_sdca_init(काष्ठा device *dev, काष्ठा regmap *regmap,
			काष्ठा regmap *mbq_regmap, काष्ठा sdw_slave *slave)
अणु
	काष्ठा rt711_sdca_priv *rt711;
	पूर्णांक ret;

	rt711 = devm_kzalloc(dev, माप(*rt711), GFP_KERNEL);
	अगर (!rt711)
		वापस -ENOMEM;

	dev_set_drvdata(dev, rt711);
	rt711->slave = slave;
	rt711->regmap = regmap;
	rt711->mbq_regmap = mbq_regmap;

	/*
	 * Mark hw_init to false
	 * HW init will be perक्रमmed when device reports present
	 */
	rt711->hw_init = false;
	rt711->first_hw_init = false;
	rt711->fu0f_dapm_mute = true;
	rt711->fu1e_dapm_mute = true;
	rt711->fu0f_mixer_l_mute = rt711->fu0f_mixer_r_mute = true;
	rt711->fu1e_mixer_l_mute = rt711->fu1e_mixer_r_mute = true;

	/* JD source uses JD2 in शेष */
	rt711->jd_src = RT711_JD2;

	ret =  devm_snd_soc_रेजिस्टर_component(dev,
			&soc_sdca_dev_rt711,
			rt711_sdca_dai,
			ARRAY_SIZE(rt711_sdca_dai));

	dev_dbg(&slave->dev, "%s\n", __func__);

	वापस ret;
पूर्ण

अटल व्योम rt711_sdca_vd0_io_init(काष्ठा rt711_sdca_priv *rt711)
अणु
	rt711_sdca_index_ग_लिखो(rt711, RT711_VENDOR_REG,
		RT711_GPIO_TEST_MODE_CTL2, 0x0e00);
	rt711_sdca_index_ग_लिखो(rt711, RT711_VENDOR_HDA_CTL,
		RT711_HDA_LEGACY_GPIO_CTL, 0x0008);

	regmap_ग_लिखो(rt711->regmap, 0x2f5a, 0x01);

	rt711_sdca_index_ग_लिखो(rt711, RT711_VENDOR_REG,
		RT711_ADC27_VOL_SET, 0x8728);

	rt711_sdca_index_ग_लिखो(rt711, RT711_VENDOR_REG,
		RT711_COMBO_JACK_AUTO_CTL3, 0xa472);

	regmap_ग_लिखो(rt711->regmap, 0x2f50, 0x02);

	rt711_sdca_index_update_bits(rt711, RT711_VENDOR_ANALOG_CTL,
		RT711_MISC_POWER_CTL4, 0x6000, 0x6000);

	rt711_sdca_index_update_bits(rt711, RT711_VENDOR_REG,
		RT711_COMBO_JACK_AUTO_CTL3, 0x000c, 0x000c);

	rt711_sdca_index_ग_लिखो(rt711, RT711_VENDOR_HDA_CTL,
		RT711_HDA_LEGACY_CONFIG_CTL, 0x0000);

	rt711_sdca_index_ग_लिखो(rt711, RT711_VENDOR_VAD,
		RT711_VAD_SRAM_CTL1, 0x0050);
पूर्ण

अटल व्योम rt711_sdca_vd1_io_init(काष्ठा rt711_sdca_priv *rt711)
अणु
	rt711_sdca_index_update_bits(rt711, RT711_VENDOR_HDA_CTL,
		RT711_HDA_LEGACY_UNSOLICITED_CTL, 0x0300, 0x0000);

	rt711_sdca_index_ग_लिखो(rt711, RT711_VENDOR_REG,
		RT711_COMBO_JACK_AUTO_CTL3, 0xa43e);

	regmap_ग_लिखो(rt711->regmap, 0x2f5a, 0x05);

	rt711_sdca_index_ग_लिखो(rt711, RT711_VENDOR_REG,
		RT711_JD_CTRL6, 0x0500);

	rt711_sdca_index_ग_लिखो(rt711, RT711_VENDOR_REG,
		RT711_DMIC_CTL1, 0x6173);

	rt711_sdca_index_ग_लिखो(rt711, RT711_VENDOR_HDA_CTL,
		RT711_HDA_LEGACY_CONFIG_CTL, 0x0000);

	rt711_sdca_index_ग_लिखो(rt711, RT711_VENDOR_VAD,
		RT711_VAD_SRAM_CTL1, 0x0050);
पूर्ण

पूर्णांक rt711_sdca_io_init(काष्ठा device *dev, काष्ठा sdw_slave *slave)
अणु
	काष्ठा rt711_sdca_priv *rt711 = dev_get_drvdata(dev);
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक val;

	अगर (rt711->hw_init)
		वापस 0;

	अगर (rt711->first_hw_init) अणु
		regcache_cache_only(rt711->regmap, false);
		regcache_cache_bypass(rt711->regmap, true);
	पूर्ण अन्यथा अणु
		/*
		 * PM runसमय is only enabled when a Slave reports as Attached
		 */

		/* set स्वतःsuspend parameters */
		pm_runसमय_set_स्वतःsuspend_delay(&slave->dev, 3000);
		pm_runसमय_use_स्वतःsuspend(&slave->dev);

		/* update count of parent 'active' children */
		pm_runसमय_set_active(&slave->dev);

		/* make sure the device करोes not suspend immediately */
		pm_runसमय_mark_last_busy(&slave->dev);

		pm_runसमय_enable(&slave->dev);
	पूर्ण

	pm_runसमय_get_noresume(&slave->dev);

	rt711_sdca_reset(rt711);

	rt711_sdca_index_पढ़ो(rt711, RT711_VENDOR_REG, RT711_JD_PRODUCT_NUM, &val);
	rt711->hw_ver = val & 0xf;

	अगर (rt711->hw_ver == RT711_VER_VD0)
		rt711_sdca_vd0_io_init(rt711);
	अन्यथा
		rt711_sdca_vd1_io_init(rt711);

	/* DP4 mux select from 08_filter_Out_pri */
	rt711_sdca_index_update_bits(rt711, RT711_VENDOR_REG,
		RT711_FILTER_SRC_SEL, 0x1800, 0x0800);

	/* ge_exclusive_inbox_en disable */
	rt711_sdca_index_update_bits(rt711, RT711_VENDOR_HDA_CTL,
		RT711_PUSH_BTN_INT_CTL0, 0x20, 0x00);

	अगर (!rt711->first_hw_init) अणु
		INIT_DELAYED_WORK(&rt711->jack_detect_work,
			rt711_sdca_jack_detect_handler);
		INIT_DELAYED_WORK(&rt711->jack_btn_check_work,
			rt711_sdca_btn_check_handler);
		mutex_init(&rt711->calibrate_mutex);
	पूर्ण

	/* calibration */
	ret = rt711_sdca_calibration(rt711);
	अगर (ret < 0)
		dev_err(dev, "%s, calibration failed!\n", __func__);

	/* HP output enable */
	regmap_ग_लिखो(rt711->regmap,
		SDW_SDCA_CTL(FUNC_NUM_JACK_CODEC, RT711_SDCA_ENT_OT1, RT711_SDCA_CTL_VENDOR_DEF, 0), 0x4);

	/*
	 * अगर set_jack callback occurred early than io_init,
	 * we set up the jack detection function now
	 */
	अगर (rt711->hs_jack)
		rt711_sdca_jack_init(rt711);

	अगर (rt711->first_hw_init) अणु
		regcache_cache_bypass(rt711->regmap, false);
		regcache_mark_dirty(rt711->regmap);
	पूर्ण अन्यथा
		rt711->first_hw_init = true;

	/* Mark Slave initialization complete */
	rt711->hw_init = true;

	pm_runसमय_mark_last_busy(&slave->dev);
	pm_runसमय_put_स्वतःsuspend(&slave->dev);

	dev_dbg(&slave->dev, "%s hw_init complete\n", __func__);
	वापस 0;
पूर्ण

MODULE_DESCRIPTION("ASoC RT711 SDCA SDW driver");
MODULE_AUTHOR("Shuming Fan <shumingf@realtek.com>");
MODULE_LICENSE("GPL");
