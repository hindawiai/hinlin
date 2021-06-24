<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// rt700.c -- rt700 ALSA SoC audio driver
//
// Copyright(c) 2019 Realtek Semiconductor Corp.
//
//

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pm.h>
#समावेश <linux/soundwire/sdw.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>
#समावेश <sound/hda_verbs.h>
#समावेश <sound/jack.h>

#समावेश "rt700.h"

अटल पूर्णांक rt700_index_ग_लिखो(काष्ठा regmap *regmap,
		अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक value)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक addr = (RT700_PRIV_INDEX_W_H << 8) | reg;

	ret = regmap_ग_लिखो(regmap, addr, value);
	अगर (ret < 0)
		pr_err("Failed to set private value: %06x <= %04x ret=%d\n",
			addr, value, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक rt700_index_पढ़ो(काष्ठा regmap *regmap,
		अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक *value)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक addr = (RT700_PRIV_INDEX_W_H << 8) | reg;

	*value = 0;
	ret = regmap_पढ़ो(regmap, addr, value);
	अगर (ret < 0)
		pr_err("Failed to get private value: %06x => %04x ret=%d\n",
			addr, *value, ret);

	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक rt700_button_detect(काष्ठा rt700_priv *rt700)
अणु
	अचिन्हित पूर्णांक btn_type = 0, val80, val81;
	पूर्णांक ret;

	ret = rt700_index_पढ़ो(rt700->regmap, RT700_IRQ_FLAG_TABLE1, &val80);
	अगर (ret < 0)
		जाओ पढ़ो_error;
	ret = rt700_index_पढ़ो(rt700->regmap, RT700_IRQ_FLAG_TABLE2, &val81);
	अगर (ret < 0)
		जाओ पढ़ो_error;

	val80 &= 0x0381;
	val81 &= 0xff00;

	चयन (val80) अणु
	हाल 0x0200:
	हाल 0x0100:
	हाल 0x0080:
		btn_type |= SND_JACK_BTN_0;
		अवरोध;
	हाल 0x0001:
		btn_type |= SND_JACK_BTN_3;
		अवरोध;
	पूर्ण
	चयन (val81) अणु
	हाल 0x8000:
	हाल 0x4000:
	हाल 0x2000:
		btn_type |= SND_JACK_BTN_1;
		अवरोध;
	हाल 0x1000:
	हाल 0x0800:
	हाल 0x0400:
		btn_type |= SND_JACK_BTN_2;
		अवरोध;
	हाल 0x0200:
	हाल 0x0100:
		btn_type |= SND_JACK_BTN_3;
		अवरोध;
	पूर्ण
पढ़ो_error:
	वापस btn_type;
पूर्ण

अटल पूर्णांक rt700_headset_detect(काष्ठा rt700_priv *rt700)
अणु
	अचिन्हित पूर्णांक buf, loop = 0;
	पूर्णांक ret;
	अचिन्हित पूर्णांक jack_status = 0, reg;

	ret = rt700_index_पढ़ो(rt700->regmap,
					RT700_COMBO_JACK_AUTO_CTL2, &buf);
	अगर (ret < 0)
		जाओ io_error;

	जबतक (loop < 500 &&
		(buf & RT700_COMBOJACK_AUTO_DET_STATUS) == 0) अणु
		loop++;

		usleep_range(9000, 10000);
		ret = rt700_index_पढ़ो(rt700->regmap,
					RT700_COMBO_JACK_AUTO_CTL2, &buf);
		अगर (ret < 0)
			जाओ io_error;

		reg = RT700_VERB_GET_PIN_SENSE | RT700_HP_OUT;
		ret = regmap_पढ़ो(rt700->regmap, reg, &jack_status);
		अगर ((jack_status & (1 << 31)) == 0)
			जाओ हटाओ_error;
	पूर्ण

	अगर (loop >= 500)
		जाओ to_error;

	अगर (buf & RT700_COMBOJACK_AUTO_DET_TRS)
		rt700->jack_type = SND_JACK_HEADPHONE;
	अन्यथा अगर ((buf & RT700_COMBOJACK_AUTO_DET_CTIA) ||
		(buf & RT700_COMBOJACK_AUTO_DET_OMTP))
		rt700->jack_type = SND_JACK_HEADSET;

	वापस 0;

to_error:
	ret = -ETIMEDOUT;
	pr_err_ratelimited("Time-out error in %s\n", __func__);
	वापस ret;
io_error:
	pr_err_ratelimited("IO error in %s, ret %d\n", __func__, ret);
	वापस ret;
हटाओ_error:
	pr_err_ratelimited("Jack removal in %s\n", __func__);
	वापस -ENODEV;
पूर्ण

अटल व्योम rt700_jack_detect_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rt700_priv *rt700 =
		container_of(work, काष्ठा rt700_priv, jack_detect_work.work);
	पूर्णांक btn_type = 0, ret;
	अचिन्हित पूर्णांक jack_status = 0, reg;

	अगर (!rt700->hs_jack)
		वापस;

	अगर (!rt700->component->card->instantiated)
		वापस;

	reg = RT700_VERB_GET_PIN_SENSE | RT700_HP_OUT;
	ret = regmap_पढ़ो(rt700->regmap, reg, &jack_status);
	अगर (ret < 0)
		जाओ io_error;

	/* pin attached */
	अगर (jack_status & (1 << 31)) अणु
		/* jack in */
		अगर (rt700->jack_type == 0) अणु
			ret = rt700_headset_detect(rt700);
			अगर (ret < 0)
				वापस;
			अगर (rt700->jack_type == SND_JACK_HEADSET)
				btn_type = rt700_button_detect(rt700);
		पूर्ण अन्यथा अगर (rt700->jack_type == SND_JACK_HEADSET) अणु
			/* jack is alपढ़ोy in, report button event */
			btn_type = rt700_button_detect(rt700);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* jack out */
		rt700->jack_type = 0;
	पूर्ण

	dev_dbg(&rt700->slave->dev,
		"in %s, jack_type=0x%x\n", __func__, rt700->jack_type);
	dev_dbg(&rt700->slave->dev,
		"in %s, btn_type=0x%x\n", __func__, btn_type);

	snd_soc_jack_report(rt700->hs_jack, rt700->jack_type | btn_type,
			SND_JACK_HEADSET |
			SND_JACK_BTN_0 | SND_JACK_BTN_1 |
			SND_JACK_BTN_2 | SND_JACK_BTN_3);

	अगर (btn_type) अणु
		/* button released */
		snd_soc_jack_report(rt700->hs_jack, rt700->jack_type,
			SND_JACK_HEADSET |
			SND_JACK_BTN_0 | SND_JACK_BTN_1 |
			SND_JACK_BTN_2 | SND_JACK_BTN_3);

		mod_delayed_work(प्रणाली_घातer_efficient_wq,
			&rt700->jack_btn_check_work, msecs_to_jअगरfies(200));
	पूर्ण

	वापस;

io_error:
	pr_err_ratelimited("IO error in %s, ret %d\n", __func__, ret);
पूर्ण

अटल व्योम rt700_btn_check_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rt700_priv *rt700 = container_of(work, काष्ठा rt700_priv,
		jack_btn_check_work.work);
	पूर्णांक btn_type = 0, ret;
	अचिन्हित पूर्णांक jack_status = 0, reg;

	reg = RT700_VERB_GET_PIN_SENSE | RT700_HP_OUT;
	ret = regmap_पढ़ो(rt700->regmap, reg, &jack_status);
	अगर (ret < 0)
		जाओ io_error;

	/* pin attached */
	अगर (jack_status & (1 << 31)) अणु
		अगर (rt700->jack_type == SND_JACK_HEADSET) अणु
			/* jack is alपढ़ोy in, report button event */
			btn_type = rt700_button_detect(rt700);
		पूर्ण
	पूर्ण अन्यथा अणु
		rt700->jack_type = 0;
	पूर्ण

	/* cbj comparator */
	ret = rt700_index_पढ़ो(rt700->regmap, RT700_COMBO_JACK_AUTO_CTL2, &reg);
	अगर (ret < 0)
		जाओ io_error;

	अगर ((reg & 0xf0) == 0xf0)
		btn_type = 0;

	dev_dbg(&rt700->slave->dev,
		"%s, btn_type=0x%x\n",	__func__, btn_type);
	snd_soc_jack_report(rt700->hs_jack, rt700->jack_type | btn_type,
			SND_JACK_HEADSET |
			SND_JACK_BTN_0 | SND_JACK_BTN_1 |
			SND_JACK_BTN_2 | SND_JACK_BTN_3);

	अगर (btn_type) अणु
		/* button released */
		snd_soc_jack_report(rt700->hs_jack, rt700->jack_type,
			SND_JACK_HEADSET |
			SND_JACK_BTN_0 | SND_JACK_BTN_1 |
			SND_JACK_BTN_2 | SND_JACK_BTN_3);

		mod_delayed_work(प्रणाली_घातer_efficient_wq,
			&rt700->jack_btn_check_work, msecs_to_jअगरfies(200));
	पूर्ण

	वापस;

io_error:
	pr_err_ratelimited("IO error in %s, ret %d\n", __func__, ret);
पूर्ण

अटल व्योम rt700_jack_init(काष्ठा rt700_priv *rt700)
अणु
	काष्ठा snd_soc_dapm_context *dapm =
		snd_soc_component_get_dapm(rt700->component);

	/* घातer on */
	अगर (dapm->bias_level <= SND_SOC_BIAS_STANDBY)
		regmap_ग_लिखो(rt700->regmap,
			RT700_SET_AUDIO_POWER_STATE, AC_PWRST_D0);

	अगर (rt700->hs_jack) अणु
		/* Enable Jack Detection */
		regmap_ग_लिखो(rt700->regmap,
			RT700_SET_MIC2_UNSOLICITED_ENABLE, 0x82);
		regmap_ग_लिखो(rt700->regmap,
			RT700_SET_HP_UNSOLICITED_ENABLE, 0x81);
		regmap_ग_लिखो(rt700->regmap,
			RT700_SET_INLINE_UNSOLICITED_ENABLE, 0x83);
		rt700_index_ग_लिखो(rt700->regmap, 0x10, 0x2420);
		rt700_index_ग_लिखो(rt700->regmap, 0x19, 0x2e11);

		dev_dbg(&rt700->slave->dev, "in %s enable\n", __func__);

		mod_delayed_work(प्रणाली_घातer_efficient_wq,
			&rt700->jack_detect_work, msecs_to_jअगरfies(250));
	पूर्ण अन्यथा अणु
		regmap_ग_लिखो(rt700->regmap,
			RT700_SET_MIC2_UNSOLICITED_ENABLE, 0x00);
		regmap_ग_लिखो(rt700->regmap,
			RT700_SET_HP_UNSOLICITED_ENABLE, 0x00);
		regmap_ग_लिखो(rt700->regmap,
			RT700_SET_INLINE_UNSOLICITED_ENABLE, 0x00);

		dev_dbg(&rt700->slave->dev, "in %s disable\n", __func__);
	पूर्ण

	/* घातer off */
	अगर (dapm->bias_level <= SND_SOC_BIAS_STANDBY)
		regmap_ग_लिखो(rt700->regmap,
			RT700_SET_AUDIO_POWER_STATE, AC_PWRST_D3);
पूर्ण

अटल पूर्णांक rt700_set_jack_detect(काष्ठा snd_soc_component *component,
	काष्ठा snd_soc_jack *hs_jack, व्योम *data)
अणु
	काष्ठा rt700_priv *rt700 = snd_soc_component_get_drvdata(component);

	rt700->hs_jack = hs_jack;

	अगर (!rt700->hw_init) अणु
		dev_dbg(&rt700->slave->dev,
			"%s hw_init not ready yet\n", __func__);
		वापस 0;
	पूर्ण

	rt700_jack_init(rt700);

	वापस 0;
पूर्ण

अटल व्योम rt700_get_gain(काष्ठा rt700_priv *rt700, अचिन्हित पूर्णांक addr_h,
				अचिन्हित पूर्णांक addr_l, अचिन्हित पूर्णांक val_h,
				अचिन्हित पूर्णांक *r_val, अचिन्हित पूर्णांक *l_val)
अणु
	/* R Channel */
	*r_val = (val_h << 8);
	regmap_पढ़ो(rt700->regmap, addr_l, r_val);

	/* L Channel */
	val_h |= 0x20;
	*l_val = (val_h << 8);
	regmap_पढ़ो(rt700->regmap, addr_h, l_val);
पूर्ण

/* For Verb-Set Amplअगरier Gain (Verb ID = 3h) */
अटल पूर्णांक rt700_set_amp_gain_put(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_soc_dapm_context *dapm =
		snd_soc_component_get_dapm(component);
	काष्ठा soc_mixer_control *mc =
		(काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	काष्ठा rt700_priv *rt700 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक addr_h, addr_l, val_h, val_ll, val_lr;
	अचिन्हित पूर्णांक पढ़ो_ll, पढ़ो_rl;
	पूर्णांक i;

	/* Can't use update bit function, so पढ़ो the original value first */
	addr_h = mc->reg;
	addr_l = mc->rreg;
	अगर (mc->shअगरt == RT700_सूची_OUT_SFT) /* output */
		val_h = 0x80;
	अन्यथा /* input */
		val_h = 0x0;

	rt700_get_gain(rt700, addr_h, addr_l, val_h, &पढ़ो_rl, &पढ़ो_ll);

	/* L Channel */
	अगर (mc->invert) अणु
		/* क्रम mute */
		val_ll = (mc->max - ucontrol->value.पूर्णांकeger.value[0]) << 7;
		/* keep gain */
		पढ़ो_ll = पढ़ो_ll & 0x7f;
		val_ll |= पढ़ो_ll;
	पूर्ण अन्यथा अणु
		/* क्रम gain */
		val_ll = ((ucontrol->value.पूर्णांकeger.value[0]) & 0x7f);
		अगर (val_ll > mc->max)
			val_ll = mc->max;
		/* keep mute status */
		पढ़ो_ll = पढ़ो_ll & 0x80;
		val_ll |= पढ़ो_ll;
	पूर्ण

	अगर (dapm->bias_level <= SND_SOC_BIAS_STANDBY)
		regmap_ग_लिखो(rt700->regmap,
				RT700_SET_AUDIO_POWER_STATE, AC_PWRST_D0);

	/* R Channel */
	अगर (mc->invert) अणु
		/* क्रम mute */
		val_lr = (mc->max - ucontrol->value.पूर्णांकeger.value[1]) << 7;
		/* keep gain */
		पढ़ो_rl = पढ़ो_rl & 0x7f;
		val_lr |= पढ़ो_rl;
	पूर्ण अन्यथा अणु
		/* क्रम gain */
		val_lr = ((ucontrol->value.पूर्णांकeger.value[1]) & 0x7f);
		अगर (val_lr > mc->max)
			val_lr = mc->max;
		/* keep mute status */
		पढ़ो_rl = पढ़ो_rl & 0x80;
		val_lr |= पढ़ो_rl;
	पूर्ण

	क्रम (i = 0; i < 3; i++) अणु /* retry 3 बार at most */
		अगर (val_ll == val_lr) अणु
			/* Set both L/R channels at the same समय */
			val_h = (1 << mc->shअगरt) | (3 << 4);
			regmap_ग_लिखो(rt700->regmap,
				addr_h, (val_h << 8 | val_ll));
			regmap_ग_लिखो(rt700->regmap,
				addr_l, (val_h << 8 | val_ll));
		पूर्ण अन्यथा अणु
			/* Lch*/
			val_h = (1 << mc->shअगरt) | (1 << 5);
			regmap_ग_लिखो(rt700->regmap,
				addr_h, (val_h << 8 | val_ll));

			/* Rch */
			val_h = (1 << mc->shअगरt) | (1 << 4);
			regmap_ग_लिखो(rt700->regmap,
				addr_l, (val_h << 8 | val_lr));
		पूर्ण
		/* check result */
		अगर (mc->shअगरt == RT700_सूची_OUT_SFT) /* output */
			val_h = 0x80;
		अन्यथा /* input */
			val_h = 0x0;

		rt700_get_gain(rt700, addr_h, addr_l, val_h,
					&पढ़ो_rl, &पढ़ो_ll);
		अगर (पढ़ो_rl == val_lr && पढ़ो_ll == val_ll)
			अवरोध;
	पूर्ण

	अगर (dapm->bias_level <= SND_SOC_BIAS_STANDBY)
		regmap_ग_लिखो(rt700->regmap,
				RT700_SET_AUDIO_POWER_STATE, AC_PWRST_D3);
	वापस 0;
पूर्ण

अटल पूर्णांक rt700_set_amp_gain_get(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा rt700_priv *rt700 = snd_soc_component_get_drvdata(component);
	काष्ठा soc_mixer_control *mc =
		(काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक addr_h, addr_l, val_h;
	अचिन्हित पूर्णांक पढ़ो_ll, पढ़ो_rl;

	addr_h = mc->reg;
	addr_l = mc->rreg;
	अगर (mc->shअगरt == RT700_सूची_OUT_SFT) /* output */
		val_h = 0x80;
	अन्यथा /* input */
		val_h = 0x0;

	rt700_get_gain(rt700, addr_h, addr_l, val_h, &पढ़ो_rl, &पढ़ो_ll);

	अगर (mc->invert) अणु
		/* क्रम mute status */
		पढ़ो_ll = !((पढ़ो_ll & 0x80) >> RT700_MUTE_SFT);
		पढ़ो_rl = !((पढ़ो_rl & 0x80) >> RT700_MUTE_SFT);
	पूर्ण अन्यथा अणु
		/* क्रम gain */
		पढ़ो_ll = पढ़ो_ll & 0x7f;
		पढ़ो_rl = पढ़ो_rl & 0x7f;
	पूर्ण
	ucontrol->value.पूर्णांकeger.value[0] = पढ़ो_ll;
	ucontrol->value.पूर्णांकeger.value[1] = पढ़ो_rl;

	वापस 0;
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(out_vol_tlv, -6525, 75, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(in_vol_tlv, -1725, 75, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(mic_vol_tlv, 0, 1000, 0);

अटल स्थिर काष्ठा snd_kcontrol_new rt700_snd_controls[] = अणु
	SOC_DOUBLE_R_EXT_TLV("DAC Front Playback Volume",
		RT700_SET_GAIN_DAC1_H, RT700_SET_GAIN_DAC1_L,
		RT700_सूची_OUT_SFT, 0x57, 0,
		rt700_set_amp_gain_get, rt700_set_amp_gain_put, out_vol_tlv),
	SOC_DOUBLE_R_EXT("ADC 08 Capture Switch",
		RT700_SET_GAIN_ADC2_H, RT700_SET_GAIN_ADC2_L,
		RT700_सूची_IN_SFT, 1, 1,
		rt700_set_amp_gain_get, rt700_set_amp_gain_put),
	SOC_DOUBLE_R_EXT("ADC 09 Capture Switch",
		RT700_SET_GAIN_ADC1_H,	RT700_SET_GAIN_ADC1_L,
		RT700_सूची_IN_SFT, 1, 1,
		rt700_set_amp_gain_get, rt700_set_amp_gain_put),
	SOC_DOUBLE_R_EXT_TLV("ADC 08 Capture Volume",
		RT700_SET_GAIN_ADC2_H,	RT700_SET_GAIN_ADC2_L,
		RT700_सूची_IN_SFT, 0x3f, 0,
		rt700_set_amp_gain_get, rt700_set_amp_gain_put, in_vol_tlv),
	SOC_DOUBLE_R_EXT_TLV("ADC 09 Capture Volume",
		RT700_SET_GAIN_ADC1_H, RT700_SET_GAIN_ADC1_L,
		RT700_सूची_IN_SFT, 0x3f, 0,
		rt700_set_amp_gain_get, rt700_set_amp_gain_put, in_vol_tlv),
	SOC_DOUBLE_R_EXT_TLV("AMIC Volume",
		RT700_SET_GAIN_AMIC_H,	RT700_SET_GAIN_AMIC_L,
		RT700_सूची_IN_SFT, 3, 0,
		rt700_set_amp_gain_get, rt700_set_amp_gain_put, mic_vol_tlv),
पूर्ण;

अटल पूर्णांक rt700_mux_get(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_kcontrol_component(kcontrol);
	काष्ठा rt700_priv *rt700 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक reg, val = 0, nid;
	पूर्णांक ret;

	अगर (म_माला(ucontrol->id.name, "HPO Mux"))
		nid = RT700_HP_OUT;
	अन्यथा अगर (म_माला(ucontrol->id.name, "ADC 22 Mux"))
		nid = RT700_MIXER_IN1;
	अन्यथा अगर (म_माला(ucontrol->id.name, "ADC 23 Mux"))
		nid = RT700_MIXER_IN2;
	अन्यथा
		वापस -EINVAL;

	/* vid = 0xf01 */
	reg = RT700_VERB_SET_CONNECT_SEL | nid;
	ret = regmap_पढ़ो(rt700->regmap, reg, &val);
	अगर (ret < 0)
		वापस ret;

	ucontrol->value.क्रमागतerated.item[0] = val;

	वापस 0;
पूर्ण

अटल पूर्णांक rt700_mux_put(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_kcontrol_component(kcontrol);
	काष्ठा snd_soc_dapm_context *dapm =
		snd_soc_dapm_kcontrol_dapm(kcontrol);
	काष्ठा rt700_priv *rt700 = snd_soc_component_get_drvdata(component);
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक *item = ucontrol->value.क्रमागतerated.item;
	अचिन्हित पूर्णांक val, val2 = 0, change, reg, nid;
	पूर्णांक ret;

	अगर (item[0] >= e->items)
		वापस -EINVAL;

	अगर (म_माला(ucontrol->id.name, "HPO Mux"))
		nid = RT700_HP_OUT;
	अन्यथा अगर (म_माला(ucontrol->id.name, "ADC 22 Mux"))
		nid = RT700_MIXER_IN1;
	अन्यथा अगर (म_माला(ucontrol->id.name, "ADC 23 Mux"))
		nid = RT700_MIXER_IN2;
	अन्यथा
		वापस -EINVAL;

	/* Verb ID = 0x701h */
	val = snd_soc_क्रमागत_item_to_val(e, item[0]) << e->shअगरt_l;

	reg = RT700_VERB_SET_CONNECT_SEL | nid;
	ret = regmap_पढ़ो(rt700->regmap, reg, &val2);
	अगर (ret < 0)
		वापस ret;

	अगर (val == val2)
		change = 0;
	अन्यथा
		change = 1;

	अगर (change) अणु
		reg = RT700_VERB_SET_CONNECT_SEL | nid;
		regmap_ग_लिखो(rt700->regmap, reg, val);
	पूर्ण

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
	rt700_adc22_क्रमागत, SND_SOC_NOPM, 0, adc_mux_text);

अटल SOC_ENUM_SINGLE_DECL(
	rt700_adc23_क्रमागत, SND_SOC_NOPM, 0, adc_mux_text);

अटल स्थिर काष्ठा snd_kcontrol_new rt700_adc22_mux =
	SOC_DAPM_ENUM_EXT("ADC 22 Mux", rt700_adc22_क्रमागत,
			rt700_mux_get, rt700_mux_put);

अटल स्थिर काष्ठा snd_kcontrol_new rt700_adc23_mux =
	SOC_DAPM_ENUM_EXT("ADC 23 Mux", rt700_adc23_क्रमागत,
			rt700_mux_get, rt700_mux_put);

अटल स्थिर अक्षर * स्थिर out_mux_text[] = अणु
	"Front",
	"Surround",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt700_hp_क्रमागत, SND_SOC_NOPM, 0, out_mux_text);

अटल स्थिर काष्ठा snd_kcontrol_new rt700_hp_mux =
	SOC_DAPM_ENUM_EXT("HP Mux", rt700_hp_क्रमागत,
			rt700_mux_get, rt700_mux_put);

अटल पूर्णांक rt700_dac_front_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	काष्ठा rt700_priv *rt700 = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		regmap_ग_लिखो(rt700->regmap,
			RT700_SET_STREAMID_DAC1, 0x10);
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		regmap_ग_लिखो(rt700->regmap,
			RT700_SET_STREAMID_DAC1, 0x00);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rt700_dac_surround_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	काष्ठा rt700_priv *rt700 = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		regmap_ग_लिखो(rt700->regmap,
			RT700_SET_STREAMID_DAC2, 0x10);
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		regmap_ग_लिखो(rt700->regmap,
			RT700_SET_STREAMID_DAC2, 0x00);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rt700_adc_09_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	काष्ठा rt700_priv *rt700 = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		regmap_ग_लिखो(rt700->regmap,
			RT700_SET_STREAMID_ADC1, 0x10);
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		regmap_ग_लिखो(rt700->regmap,
			RT700_SET_STREAMID_ADC1, 0x00);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rt700_adc_08_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	काष्ठा rt700_priv *rt700 = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		regmap_ग_लिखो(rt700->regmap,
			RT700_SET_STREAMID_ADC2, 0x10);
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		regmap_ग_लिखो(rt700->regmap,
			RT700_SET_STREAMID_ADC2, 0x00);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rt700_hpo_mux_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	काष्ठा rt700_priv *rt700 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक val_h = (1 << RT700_सूची_OUT_SFT) | (0x3 << 4);
	अचिन्हित पूर्णांक val_l;

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		val_l = 0x00;
		regmap_ग_लिखो(rt700->regmap,
			RT700_SET_GAIN_HP_H, (val_h << 8 | val_l));
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		val_l = (1 << RT700_MUTE_SFT);
		regmap_ग_लिखो(rt700->regmap,
			RT700_SET_GAIN_HP_H, (val_h << 8 | val_l));
		usleep_range(50000, 55000);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rt700_spk_pga_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	काष्ठा rt700_priv *rt700 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक val_h = (1 << RT700_सूची_OUT_SFT) | (0x3 << 4);
	अचिन्हित पूर्णांक val_l;

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		val_l = 0x00;
		regmap_ग_लिखो(rt700->regmap,
			RT700_SET_GAIN_SPK_H, (val_h << 8 | val_l));
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		val_l = (1 << RT700_MUTE_SFT);
		regmap_ग_लिखो(rt700->regmap,
			RT700_SET_GAIN_SPK_H, (val_h << 8 | val_l));
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget rt700_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_OUTPUT("HP"),
	SND_SOC_DAPM_OUTPUT("SPK"),
	SND_SOC_DAPM_INPUT("DMIC1"),
	SND_SOC_DAPM_INPUT("DMIC2"),
	SND_SOC_DAPM_INPUT("MIC2"),
	SND_SOC_DAPM_INPUT("LINE1"),
	SND_SOC_DAPM_INPUT("LINE2"),
	SND_SOC_DAPM_DAC_E("DAC Front", शून्य, SND_SOC_NOPM, 0, 0,
		rt700_dac_front_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),
	SND_SOC_DAPM_DAC_E("DAC Surround", शून्य, SND_SOC_NOPM, 0, 0,
		rt700_dac_surround_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),
	SND_SOC_DAPM_MUX_E("HPO Mux", SND_SOC_NOPM, 0, 0, &rt700_hp_mux,
		rt700_hpo_mux_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),
	SND_SOC_DAPM_PGA_E("SPK PGA", SND_SOC_NOPM, 0, 0, शून्य, 0,
		rt700_spk_pga_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),
	SND_SOC_DAPM_ADC_E("ADC 09", शून्य, SND_SOC_NOPM, 0, 0,
		rt700_adc_09_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),
	SND_SOC_DAPM_ADC_E("ADC 08", शून्य, SND_SOC_NOPM, 0, 0,
		rt700_adc_08_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),
	SND_SOC_DAPM_MUX("ADC 22 Mux", SND_SOC_NOPM, 0, 0,
		&rt700_adc22_mux),
	SND_SOC_DAPM_MUX("ADC 23 Mux", SND_SOC_NOPM, 0, 0,
		&rt700_adc23_mux),
	SND_SOC_DAPM_AIF_IN("DP1RX", "DP1 Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("DP3RX", "DP3 Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("DP2TX", "DP2 Capture", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("DP4TX", "DP4 Capture", 0, SND_SOC_NOPM, 0, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route rt700_audio_map[] = अणु
	अणु"DAC Front", शून्य, "DP1RX"पूर्ण,
	अणु"DAC Surround", शून्य, "DP3RX"पूर्ण,
	अणु"DP2TX", शून्य, "ADC 09"पूर्ण,
	अणु"DP4TX", शून्य, "ADC 08"पूर्ण,
	अणु"ADC 09", शून्य, "ADC 22 Mux"पूर्ण,
	अणु"ADC 08", शून्य, "ADC 23 Mux"पूर्ण,
	अणु"ADC 22 Mux", "DMIC", "DMIC1"पूर्ण,
	अणु"ADC 22 Mux", "LINE1", "LINE1"पूर्ण,
	अणु"ADC 22 Mux", "LINE2", "LINE2"पूर्ण,
	अणु"ADC 22 Mux", "MIC2", "MIC2"पूर्ण,
	अणु"ADC 23 Mux", "DMIC", "DMIC2"पूर्ण,
	अणु"ADC 23 Mux", "LINE1", "LINE1"पूर्ण,
	अणु"ADC 23 Mux", "LINE2", "LINE2"पूर्ण,
	अणु"ADC 23 Mux", "MIC2", "MIC2"पूर्ण,
	अणु"HPO Mux", "Front", "DAC Front"पूर्ण,
	अणु"HPO Mux", "Surround", "DAC Surround"पूर्ण,
	अणु"HP", शून्य, "HPO Mux"पूर्ण,
	अणु"SPK PGA", शून्य, "DAC Front"पूर्ण,
	अणु"SPK", शून्य, "SPK PGA"पूर्ण,
पूर्ण;

अटल पूर्णांक rt700_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा rt700_priv *rt700 = snd_soc_component_get_drvdata(component);

	rt700->component = component;

	वापस 0;
पूर्ण

अटल पूर्णांक rt700_set_bias_level(काष्ठा snd_soc_component *component,
				क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा snd_soc_dapm_context *dapm =
		snd_soc_component_get_dapm(component);
	काष्ठा rt700_priv *rt700 = snd_soc_component_get_drvdata(component);

	चयन (level) अणु
	हाल SND_SOC_BIAS_PREPARE:
		अगर (dapm->bias_level == SND_SOC_BIAS_STANDBY) अणु
			regmap_ग_लिखो(rt700->regmap,
				RT700_SET_AUDIO_POWER_STATE,
				AC_PWRST_D0);
		पूर्ण
		अवरोध;

	हाल SND_SOC_BIAS_STANDBY:
		regmap_ग_लिखो(rt700->regmap,
			RT700_SET_AUDIO_POWER_STATE,
			AC_PWRST_D3);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
	dapm->bias_level = level;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_codec_dev_rt700 = अणु
	.probe = rt700_probe,
	.set_bias_level = rt700_set_bias_level,
	.controls = rt700_snd_controls,
	.num_controls = ARRAY_SIZE(rt700_snd_controls),
	.dapm_widमाला_लो = rt700_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(rt700_dapm_widमाला_लो),
	.dapm_routes = rt700_audio_map,
	.num_dapm_routes = ARRAY_SIZE(rt700_audio_map),
	.set_jack = rt700_set_jack_detect,
पूर्ण;

अटल पूर्णांक rt700_set_sdw_stream(काष्ठा snd_soc_dai *dai, व्योम *sdw_stream,
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

अटल व्योम rt700_shutकरोwn(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा sdw_stream_data *stream;

	stream = snd_soc_dai_get_dma_data(dai, substream);
	snd_soc_dai_set_dma_data(dai, substream, शून्य);
	kमुक्त(stream);
पूर्ण

अटल पूर्णांक rt700_pcm_hw_params(काष्ठा snd_pcm_substream *substream,
					काष्ठा snd_pcm_hw_params *params,
					काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt700_priv *rt700 = snd_soc_component_get_drvdata(component);
	काष्ठा sdw_stream_config stream_config;
	काष्ठा sdw_port_config port_config;
	क्रमागत sdw_data_direction direction;
	काष्ठा sdw_stream_data *stream;
	पूर्णांक retval, port, num_channels;
	अचिन्हित पूर्णांक val = 0;

	dev_dbg(dai->dev, "%s %s", __func__, dai->name);
	stream = snd_soc_dai_get_dma_data(dai, substream);

	अगर (!stream)
		वापस -EINVAL;

	अगर (!rt700->slave)
		वापस -EINVAL;

	/* SoundWire specअगरic configuration */
	/* This code assumes port 1 क्रम playback and port 2 क्रम capture */
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		direction = SDW_DATA_सूची_RX;
		port = 1;
	पूर्ण अन्यथा अणु
		direction = SDW_DATA_सूची_TX;
		port = 2;
	पूर्ण

	चयन (dai->id) अणु
	हाल RT700_AIF1:
		अवरोध;
	हाल RT700_AIF2:
		port += 2;
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid DAI id %d\n", dai->id);
		वापस -EINVAL;
	पूर्ण

	stream_config.frame_rate = params_rate(params);
	stream_config.ch_count = params_channels(params);
	stream_config.bps = snd_pcm_क्रमmat_width(params_क्रमmat(params));
	stream_config.direction = direction;

	num_channels = params_channels(params);
	port_config.ch_mask = (1 << (num_channels)) - 1;
	port_config.num = port;

	retval = sdw_stream_add_slave(rt700->slave, &stream_config,
					&port_config, 1, stream->sdw_stream);
	अगर (retval) अणु
		dev_err(dai->dev, "Unable to configure port\n");
		वापस retval;
	पूर्ण

	अगर (params_channels(params) <= 16) अणु
		/* bit 3:0 Number of Channel */
		val |= (params_channels(params) - 1);
	पूर्ण अन्यथा अणु
		dev_err(component->dev, "Unsupported channels %d\n",
			params_channels(params));
		वापस -EINVAL;
	पूर्ण

	चयन (params_width(params)) अणु
	/* bit 6:4 Bits per Sample */
	हाल 8:
		अवरोध;
	हाल 16:
		val |= (0x1 << 4);
		अवरोध;
	हाल 20:
		val |= (0x2 << 4);
		अवरोध;
	हाल 24:
		val |= (0x3 << 4);
		अवरोध;
	हाल 32:
		val |= (0x4 << 4);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* 48Khz */
	regmap_ग_लिखो(rt700->regmap, RT700_DAC_FORMAT_H, val);
	regmap_ग_लिखो(rt700->regmap, RT700_ADC_FORMAT_H, val);

	वापस retval;
पूर्ण

अटल पूर्णांक rt700_pcm_hw_मुक्त(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt700_priv *rt700 = snd_soc_component_get_drvdata(component);
	काष्ठा sdw_stream_data *stream =
		snd_soc_dai_get_dma_data(dai, substream);

	अगर (!rt700->slave)
		वापस -EINVAL;

	sdw_stream_हटाओ_slave(rt700->slave, stream->sdw_stream);
	वापस 0;
पूर्ण

#घोषणा RT700_STEREO_RATES (SNDRV_PCM_RATE_44100 | SNDRV_PCM_RATE_48000)
#घोषणा RT700_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE | \
			SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S8)

अटल स्थिर काष्ठा snd_soc_dai_ops rt700_ops = अणु
	.hw_params	= rt700_pcm_hw_params,
	.hw_मुक्त	= rt700_pcm_hw_मुक्त,
	.set_sdw_stream	= rt700_set_sdw_stream,
	.shutकरोwn	= rt700_shutकरोwn,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver rt700_dai[] = अणु
	अणु
		.name = "rt700-aif1",
		.id = RT700_AIF1,
		.playback = अणु
			.stream_name = "DP1 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT700_STEREO_RATES,
			.क्रमmats = RT700_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "DP2 Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT700_STEREO_RATES,
			.क्रमmats = RT700_FORMATS,
		पूर्ण,
		.ops = &rt700_ops,
	पूर्ण,
	अणु
		.name = "rt700-aif2",
		.id = RT700_AIF2,
		.playback = अणु
			.stream_name = "DP3 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT700_STEREO_RATES,
			.क्रमmats = RT700_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "DP4 Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT700_STEREO_RATES,
			.क्रमmats = RT700_FORMATS,
		पूर्ण,
		.ops = &rt700_ops,
	पूर्ण,
पूर्ण;

/* Bus घड़ी frequency */
#घोषणा RT700_CLK_FREQ_9600000HZ 9600000
#घोषणा RT700_CLK_FREQ_12000000HZ 12000000
#घोषणा RT700_CLK_FREQ_6000000HZ 6000000
#घोषणा RT700_CLK_FREQ_4800000HZ 4800000
#घोषणा RT700_CLK_FREQ_2400000HZ 2400000
#घोषणा RT700_CLK_FREQ_12288000HZ 12288000

पूर्णांक rt700_घड़ी_config(काष्ठा device *dev)
अणु
	काष्ठा rt700_priv *rt700 = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक clk_freq, value;

	clk_freq = (rt700->params.curr_dr_freq >> 1);

	चयन (clk_freq) अणु
	हाल RT700_CLK_FREQ_12000000HZ:
		value = 0x0;
		अवरोध;
	हाल RT700_CLK_FREQ_6000000HZ:
		value = 0x1;
		अवरोध;
	हाल RT700_CLK_FREQ_9600000HZ:
		value = 0x2;
		अवरोध;
	हाल RT700_CLK_FREQ_4800000HZ:
		value = 0x3;
		अवरोध;
	हाल RT700_CLK_FREQ_2400000HZ:
		value = 0x4;
		अवरोध;
	हाल RT700_CLK_FREQ_12288000HZ:
		value = 0x5;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_ग_लिखो(rt700->regmap, 0xe0, value);
	regmap_ग_लिखो(rt700->regmap, 0xf0, value);

	dev_dbg(dev, "%s complete, clk_freq=%d\n", __func__, clk_freq);

	वापस 0;
पूर्ण

पूर्णांक rt700_init(काष्ठा device *dev, काष्ठा regmap *sdw_regmap,
			काष्ठा regmap *regmap, काष्ठा sdw_slave *slave)

अणु
	काष्ठा rt700_priv *rt700;
	पूर्णांक ret;

	rt700 = devm_kzalloc(dev, माप(*rt700), GFP_KERNEL);
	अगर (!rt700)
		वापस -ENOMEM;

	dev_set_drvdata(dev, rt700);
	rt700->slave = slave;
	rt700->sdw_regmap = sdw_regmap;
	rt700->regmap = regmap;

	/*
	 * Mark hw_init to false
	 * HW init will be perक्रमmed when device reports present
	 */
	rt700->hw_init = false;
	rt700->first_hw_init = false;

	ret =  devm_snd_soc_रेजिस्टर_component(dev,
				&soc_codec_dev_rt700,
				rt700_dai,
				ARRAY_SIZE(rt700_dai));

	dev_dbg(&slave->dev, "%s\n", __func__);

	वापस ret;
पूर्ण

पूर्णांक rt700_io_init(काष्ठा device *dev, काष्ठा sdw_slave *slave)
अणु
	काष्ठा rt700_priv *rt700 = dev_get_drvdata(dev);

	अगर (rt700->hw_init)
		वापस 0;

	अगर (rt700->first_hw_init) अणु
		regcache_cache_only(rt700->regmap, false);
		regcache_cache_bypass(rt700->regmap, true);
	पूर्ण

	/*
	 * PM runसमय is only enabled when a Slave reports as Attached
	 */
	अगर (!rt700->first_hw_init) अणु
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

	/* reset */
	regmap_ग_लिखो(rt700->regmap, 0xff01, 0x0000);
	regmap_ग_लिखो(rt700->regmap, 0x7520, 0x001a);
	regmap_ग_लिखो(rt700->regmap, 0x7420, 0xc003);

	/* घातer on */
	regmap_ग_लिखो(rt700->regmap, RT700_SET_AUDIO_POWER_STATE, AC_PWRST_D0);
	/* Set Pin Widget */
	regmap_ग_लिखो(rt700->regmap, RT700_SET_PIN_HP, 0x40);
	regmap_ग_लिखो(rt700->regmap, RT700_SET_PIN_SPK, 0x40);
	regmap_ग_लिखो(rt700->regmap, RT700_SET_EAPD_SPK, RT700_EAPD_HIGH);
	regmap_ग_लिखो(rt700->regmap, RT700_SET_PIN_DMIC1, 0x20);
	regmap_ग_लिखो(rt700->regmap, RT700_SET_PIN_DMIC2, 0x20);
	regmap_ग_लिखो(rt700->regmap, RT700_SET_PIN_MIC2, 0x20);

	/* Set Configuration Default */
	regmap_ग_लिखो(rt700->regmap, 0x4f12, 0x91);
	regmap_ग_लिखो(rt700->regmap, 0x4e12, 0xd6);
	regmap_ग_लिखो(rt700->regmap, 0x4d12, 0x11);
	regmap_ग_लिखो(rt700->regmap, 0x4c12, 0x20);
	regmap_ग_लिखो(rt700->regmap, 0x4f13, 0x91);
	regmap_ग_लिखो(rt700->regmap, 0x4e13, 0xd6);
	regmap_ग_लिखो(rt700->regmap, 0x4d13, 0x11);
	regmap_ग_लिखो(rt700->regmap, 0x4c13, 0x21);

	regmap_ग_लिखो(rt700->regmap, 0x4f19, 0x02);
	regmap_ग_लिखो(rt700->regmap, 0x4e19, 0xa1);
	regmap_ग_लिखो(rt700->regmap, 0x4d19, 0x90);
	regmap_ग_लिखो(rt700->regmap, 0x4c19, 0x80);

	/* Enable Line2 */
	regmap_ग_लिखो(rt700->regmap,  0x371b, 0x40);
	regmap_ग_लिखो(rt700->regmap,  0x731b, 0xb0);
	regmap_ग_लिखो(rt700->regmap,  0x839b, 0x00);

	/* Set index */
	rt700_index_ग_लिखो(rt700->regmap, 0x4a, 0x201b);
	rt700_index_ग_लिखो(rt700->regmap, 0x45, 0x5089);
	rt700_index_ग_लिखो(rt700->regmap, 0x6b, 0x5064);
	rt700_index_ग_लिखो(rt700->regmap, 0x48, 0xd249);

	/* Finish Initial Settings, set घातer to D3 */
	regmap_ग_लिखो(rt700->regmap, RT700_SET_AUDIO_POWER_STATE, AC_PWRST_D3);

	अगर (!rt700->first_hw_init) अणु
		INIT_DELAYED_WORK(&rt700->jack_detect_work,
			rt700_jack_detect_handler);
		INIT_DELAYED_WORK(&rt700->jack_btn_check_work,
			rt700_btn_check_handler);
	पूर्ण

	/*
	 * अगर set_jack callback occurred early than io_init,
	 * we set up the jack detection function now
	 */
	अगर (rt700->hs_jack)
		rt700_jack_init(rt700);

	अगर (rt700->first_hw_init) अणु
		regcache_cache_bypass(rt700->regmap, false);
		regcache_mark_dirty(rt700->regmap);
	पूर्ण अन्यथा
		rt700->first_hw_init = true;

	/* Mark Slave initialization complete */
	rt700->hw_init = true;

	pm_runसमय_mark_last_busy(&slave->dev);
	pm_runसमय_put_स्वतःsuspend(&slave->dev);

	dev_dbg(&slave->dev, "%s hw_init complete\n", __func__);

	वापस 0;
पूर्ण

MODULE_DESCRIPTION("ASoC RT700 driver SDW");
MODULE_AUTHOR("Shuming Fan <shumingf@realtek.com>");
MODULE_LICENSE("GPL v2");
