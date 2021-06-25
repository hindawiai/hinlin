<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * rt715.c -- rt715 ALSA SoC audio driver
 *
 * Copyright(c) 2019 Realtek Semiconductor Corp.
 *
 * ALC715 ASoC Codec Driver based Intel Dummy SdW codec driver
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pm.h>
#समावेश <linux/soundwire/sdw.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/of.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/of_device.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>
#समावेश <sound/hda_verbs.h>

#समावेश "rt715.h"

अटल पूर्णांक rt715_index_ग_लिखो(काष्ठा regmap *regmap, अचिन्हित पूर्णांक reg,
		अचिन्हित पूर्णांक value)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक addr = ((RT715_PRIV_INDEX_W_H) << 8) | reg;

	ret = regmap_ग_लिखो(regmap, addr, value);
	अगर (ret < 0) अणु
		pr_err("Failed to set private value: %08x <= %04x %d\n", ret,
			addr, value);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम rt715_get_gain(काष्ठा rt715_priv *rt715, अचिन्हित पूर्णांक addr_h,
				अचिन्हित पूर्णांक addr_l, अचिन्हित पूर्णांक val_h,
				अचिन्हित पूर्णांक *r_val, अचिन्हित पूर्णांक *l_val)
अणु
	पूर्णांक ret;
	/* R Channel */
	*r_val = val_h << 8;
	ret = regmap_पढ़ो(rt715->regmap, addr_l, r_val);
	अगर (ret < 0)
		pr_err("Failed to get R channel gain.\n");

	/* L Channel */
	val_h |= 0x20;
	*l_val = val_h << 8;
	ret = regmap_पढ़ो(rt715->regmap, addr_h, l_val);
	अगर (ret < 0)
		pr_err("Failed to get L channel gain.\n");
पूर्ण

/* For Verb-Set Amplअगरier Gain (Verb ID = 3h) */
अटल पूर्णांक rt715_set_amp_gain_put(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_soc_dapm_context *dapm =
		snd_soc_component_get_dapm(component);
	काष्ठा soc_mixer_control *mc =
		(काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	काष्ठा rt715_priv *rt715 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक addr_h, addr_l, val_h, val_ll, val_lr;
	अचिन्हित पूर्णांक पढ़ो_ll, पढ़ो_rl, i;
	अचिन्हित पूर्णांक k_vol_changed = 0;

	क्रम (i = 0; i < 2; i++) अणु
		अगर (ucontrol->value.पूर्णांकeger.value[i] != rt715->kctl_2ch_vol_ori[i]) अणु
			k_vol_changed = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	/* Can't use update bit function, so पढ़ो the original value first */
	addr_h = mc->reg;
	addr_l = mc->rreg;

	अगर (mc->shअगरt == RT715_सूची_OUT_SFT) /* output */
		val_h = 0x80;
	अन्यथा /* input */
		val_h = 0x0;

	rt715_get_gain(rt715, addr_h, addr_l, val_h, &पढ़ो_rl, &पढ़ो_ll);

	अगर (dapm->bias_level <= SND_SOC_BIAS_STANDBY)
		regmap_ग_लिखो(rt715->regmap,
				RT715_SET_AUDIO_POWER_STATE, AC_PWRST_D0);

	/* L Channel */
	rt715->kctl_2ch_vol_ori[0] = ucontrol->value.पूर्णांकeger.value[0];
	/* क्रम gain */
	val_ll = ((ucontrol->value.पूर्णांकeger.value[0]) & 0x7f);
	अगर (val_ll > mc->max)
		val_ll = mc->max;
	/* keep mute status */
	val_ll |= पढ़ो_ll & 0x80;

	/* R Channel */
	rt715->kctl_2ch_vol_ori[1] = ucontrol->value.पूर्णांकeger.value[1];
	/* क्रम gain */
	val_lr = ((ucontrol->value.पूर्णांकeger.value[1]) & 0x7f);
	अगर (val_lr > mc->max)
		val_lr = mc->max;
	/* keep mute status */
	val_lr |= पढ़ो_rl & 0x80;

	क्रम (i = 0; i < 3; i++) अणु /* retry 3 बार at most */

		अगर (val_ll == val_lr) अणु
			/* Set both L/R channels at the same समय */
			val_h = (1 << mc->shअगरt) | (3 << 4);
			regmap_ग_लिखो(rt715->regmap, addr_h,
				(val_h << 8) | val_ll);
			regmap_ग_लिखो(rt715->regmap, addr_l,
				(val_h << 8) | val_ll);
		पूर्ण अन्यथा अणु
			/* Lch*/
			val_h = (1 << mc->shअगरt) | (1 << 5);
			regmap_ग_लिखो(rt715->regmap, addr_h,
				(val_h << 8) | val_ll);
			/* Rch */
			val_h = (1 << mc->shअगरt) | (1 << 4);
			regmap_ग_लिखो(rt715->regmap, addr_l,
				(val_h << 8) | val_lr);
		पूर्ण
		/* check result */
		अगर (mc->shअगरt == RT715_सूची_OUT_SFT) /* output */
			val_h = 0x80;
		अन्यथा /* input */
			val_h = 0x0;

		rt715_get_gain(rt715, addr_h, addr_l, val_h,
				&पढ़ो_rl, &पढ़ो_ll);
		अगर (पढ़ो_rl == val_lr && पढ़ो_ll == val_ll)
			अवरोध;
	पूर्ण

	/* D0:घातer on state, D3: घातer saving mode */
	अगर (dapm->bias_level <= SND_SOC_BIAS_STANDBY)
		regmap_ग_लिखो(rt715->regmap,
				RT715_SET_AUDIO_POWER_STATE, AC_PWRST_D3);
	वापस k_vol_changed;
पूर्ण

अटल पूर्णांक rt715_set_amp_gain_get(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा rt715_priv *rt715 = snd_soc_component_get_drvdata(component);
	काष्ठा soc_mixer_control *mc =
		(काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक addr_h, addr_l, val_h;
	अचिन्हित पूर्णांक पढ़ो_ll, पढ़ो_rl;

	addr_h = mc->reg;
	addr_l = mc->rreg;
	अगर (mc->shअगरt == RT715_सूची_OUT_SFT) /* output */
		val_h = 0x80;
	अन्यथा /* input */
		val_h = 0x0;

	rt715_get_gain(rt715, addr_h, addr_l, val_h, &पढ़ो_rl, &पढ़ो_ll);

	अगर (mc->invert) अणु
		/* क्रम mute status */
		पढ़ो_ll = !(पढ़ो_ll & 0x80);
		पढ़ो_rl = !(पढ़ो_rl & 0x80);
	पूर्ण अन्यथा अणु
		/* क्रम gain */
		पढ़ो_ll = पढ़ो_ll & 0x7f;
		पढ़ो_rl = पढ़ो_rl & 0x7f;
	पूर्ण
	ucontrol->value.पूर्णांकeger.value[0] = पढ़ो_ll;
	ucontrol->value.पूर्णांकeger.value[1] = पढ़ो_rl;

	वापस 0;
पूर्ण

अटल पूर्णांक rt715_set_मुख्य_चयन_put(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_soc_dapm_context *dapm =
		snd_soc_component_get_dapm(component);
	काष्ठा rt715_priv *rt715 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक capture_reg_H[] = अणुRT715_SET_GAIN_MIC_ADC_H,
		RT715_SET_GAIN_LINE_ADC_H, RT715_SET_GAIN_MIX_ADC_H,
		RT715_SET_GAIN_MIX_ADC2_Hपूर्ण;
	अचिन्हित पूर्णांक capture_reg_L[] = अणुRT715_SET_GAIN_MIC_ADC_L,
		RT715_SET_GAIN_LINE_ADC_L, RT715_SET_GAIN_MIX_ADC_L,
		RT715_SET_GAIN_MIX_ADC2_Lपूर्ण;
	अचिन्हित पूर्णांक addr_h, addr_l, val_h = 0x0, val_ll, val_lr;
	अचिन्हित पूर्णांक k_shअगरt = RT715_सूची_IN_SFT, k_changed = 0;
	अचिन्हित पूर्णांक पढ़ो_ll, पढ़ो_rl, i, j, loop_cnt = 4;

	क्रम (i = 0; i < 8; i++) अणु
		अगर (ucontrol->value.पूर्णांकeger.value[i] != rt715->kctl_8ch_चयन_ori[i])
			k_changed = 1;
	पूर्ण

	क्रम (j = 0; j < loop_cnt; j++) अणु
		/* Can't use update bit function, so पढ़ो the original value first */
		addr_h = capture_reg_H[j];
		addr_l = capture_reg_L[j];
		rt715_get_gain(rt715, addr_h, addr_l, val_h, &पढ़ो_rl, &पढ़ो_ll);

		अगर (dapm->bias_level <= SND_SOC_BIAS_STANDBY)
			regmap_ग_लिखो(rt715->regmap,
					RT715_SET_AUDIO_POWER_STATE, AC_PWRST_D0);

		/* L Channel */
		/* क्रम mute */
		rt715->kctl_8ch_चयन_ori[j * 2] =
			ucontrol->value.पूर्णांकeger.value[j * 2];
		val_ll = (!ucontrol->value.पूर्णांकeger.value[j * 2]) << 7;
		/* keep gain */
		val_ll |= पढ़ो_ll & 0x7f;

		/* R Channel */
		/* क्रम mute */
		rt715->kctl_8ch_चयन_ori[j * 2 + 1] =
			ucontrol->value.पूर्णांकeger.value[j * 2 + 1];
		val_lr = (!ucontrol->value.पूर्णांकeger.value[j * 2 + 1]) << 7;
		/* keep gain */
		val_lr |= पढ़ो_rl & 0x7f;

		क्रम (i = 0; i < 3; i++) अणु /* retry 3 बार at most */

			अगर (val_ll == val_lr) अणु
				/* Set both L/R channels at the same समय */
				val_h = (1 << k_shअगरt) | (3 << 4);
				regmap_ग_लिखो(rt715->regmap, addr_h,
					(val_h << 8) | val_ll);
				regmap_ग_लिखो(rt715->regmap, addr_l,
					(val_h << 8) | val_ll);
			पूर्ण अन्यथा अणु
				/* Lch*/
				val_h = (1 << k_shअगरt) | (1 << 5);
				regmap_ग_लिखो(rt715->regmap, addr_h,
					(val_h << 8) | val_ll);
				/* Rch */
				val_h = (1 << k_shअगरt) | (1 << 4);
				regmap_ग_लिखो(rt715->regmap, addr_l,
					(val_h << 8) | val_lr);
			पूर्ण
			val_h = 0x0;
			rt715_get_gain(rt715, addr_h, addr_l, val_h,
					&पढ़ो_rl, &पढ़ो_ll);
			अगर (पढ़ो_rl == val_lr && पढ़ो_ll == val_ll)
				अवरोध;
		पूर्ण
	पूर्ण

	/* D0:घातer on state, D3: घातer saving mode */
	अगर (dapm->bias_level <= SND_SOC_BIAS_STANDBY)
		regmap_ग_लिखो(rt715->regmap,
				RT715_SET_AUDIO_POWER_STATE, AC_PWRST_D3);
	वापस k_changed;
पूर्ण

अटल पूर्णांक rt715_set_मुख्य_चयन_get(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा rt715_priv *rt715 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक capture_reg_H[] = अणुRT715_SET_GAIN_MIC_ADC_H,
		RT715_SET_GAIN_LINE_ADC_H, RT715_SET_GAIN_MIX_ADC_H,
		RT715_SET_GAIN_MIX_ADC2_Hपूर्ण;
	अचिन्हित पूर्णांक capture_reg_L[] = अणुRT715_SET_GAIN_MIC_ADC_L,
		RT715_SET_GAIN_LINE_ADC_L, RT715_SET_GAIN_MIX_ADC_L,
		RT715_SET_GAIN_MIX_ADC2_Lपूर्ण;
	अचिन्हित पूर्णांक addr_h, addr_l, val_h = 0x0, i, loop_cnt = 4;
	अचिन्हित पूर्णांक पढ़ो_ll, पढ़ो_rl;

	क्रम (i = 0; i < loop_cnt; i++) अणु
		addr_h = capture_reg_H[i];
		addr_l = capture_reg_L[i];
		rt715_get_gain(rt715, addr_h, addr_l, val_h, &पढ़ो_rl, &पढ़ो_ll);

		ucontrol->value.पूर्णांकeger.value[i * 2] = !(पढ़ो_ll & 0x80);
		ucontrol->value.पूर्णांकeger.value[i * 2 + 1] = !(पढ़ो_rl & 0x80);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt715_set_मुख्य_vol_put(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_soc_dapm_context *dapm =
		snd_soc_component_get_dapm(component);
	काष्ठा rt715_priv *rt715 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक capture_reg_H[] = अणुRT715_SET_GAIN_MIC_ADC_H,
		RT715_SET_GAIN_LINE_ADC_H, RT715_SET_GAIN_MIX_ADC_H,
		RT715_SET_GAIN_MIX_ADC2_Hपूर्ण;
	अचिन्हित पूर्णांक capture_reg_L[] = अणुRT715_SET_GAIN_MIC_ADC_L,
		RT715_SET_GAIN_LINE_ADC_L, RT715_SET_GAIN_MIX_ADC_L,
		RT715_SET_GAIN_MIX_ADC2_Lपूर्ण;
	अचिन्हित पूर्णांक addr_h, addr_l, val_h = 0x0, val_ll, val_lr;
	अचिन्हित पूर्णांक पढ़ो_ll, पढ़ो_rl, i, j, loop_cnt = 4, k_changed = 0;
	अचिन्हित पूर्णांक k_shअगरt = RT715_सूची_IN_SFT, k_max = 0x3f;

	क्रम (i = 0; i < 8; i++) अणु
		अगर (ucontrol->value.पूर्णांकeger.value[i] != rt715->kctl_8ch_vol_ori[i])
			k_changed = 1;
	पूर्ण

	क्रम (j = 0; j < loop_cnt; j++) अणु
		addr_h = capture_reg_H[j];
		addr_l = capture_reg_L[j];
		rt715_get_gain(rt715, addr_h, addr_l, val_h, &पढ़ो_rl, &पढ़ो_ll);

		अगर (dapm->bias_level <= SND_SOC_BIAS_STANDBY)
			regmap_ग_लिखो(rt715->regmap,
					RT715_SET_AUDIO_POWER_STATE, AC_PWRST_D0);

		/* L Channel */
		/* क्रम gain */
		rt715->kctl_8ch_vol_ori[j * 2] = ucontrol->value.पूर्णांकeger.value[j * 2];
		val_ll = ((ucontrol->value.पूर्णांकeger.value[j * 2]) & 0x7f);
		अगर (val_ll > k_max)
			val_ll = k_max;
		/* keep mute status */
		val_ll |= पढ़ो_ll & 0x80;

		/* R Channel */
		/* क्रम gain */
		rt715->kctl_8ch_vol_ori[j * 2 + 1] =
			ucontrol->value.पूर्णांकeger.value[j * 2 + 1];
		val_lr = ((ucontrol->value.पूर्णांकeger.value[j * 2 + 1]) & 0x7f);
		अगर (val_lr > k_max)
			val_lr = k_max;
		/* keep mute status */
		val_lr |= पढ़ो_rl & 0x80;

		क्रम (i = 0; i < 3; i++) अणु /* retry 3 बार at most */
			अगर (val_ll == val_lr) अणु
				/* Set both L/R channels at the same समय */
				val_h = (1 << k_shअगरt) | (3 << 4);
				regmap_ग_लिखो(rt715->regmap, addr_h,
					(val_h << 8) | val_ll);
				regmap_ग_लिखो(rt715->regmap, addr_l,
					(val_h << 8) | val_ll);
			पूर्ण अन्यथा अणु
				/* Lch*/
				val_h = (1 << k_shअगरt) | (1 << 5);
				regmap_ग_लिखो(rt715->regmap, addr_h,
					(val_h << 8) | val_ll);
				/* Rch */
				val_h = (1 << k_shअगरt) | (1 << 4);
				regmap_ग_लिखो(rt715->regmap, addr_l,
					(val_h << 8) | val_lr);
			पूर्ण
			val_h = 0x0;
			rt715_get_gain(rt715, addr_h, addr_l, val_h,
					&पढ़ो_rl, &पढ़ो_ll);
			अगर (पढ़ो_rl == val_lr && पढ़ो_ll == val_ll)
				अवरोध;
		पूर्ण
	पूर्ण

	/* D0:घातer on state, D3: घातer saving mode */
	अगर (dapm->bias_level <= SND_SOC_BIAS_STANDBY)
		regmap_ग_लिखो(rt715->regmap,
				RT715_SET_AUDIO_POWER_STATE, AC_PWRST_D3);
	वापस k_changed;
पूर्ण

अटल पूर्णांक rt715_set_मुख्य_vol_get(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा rt715_priv *rt715 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक capture_reg_H[] = अणुRT715_SET_GAIN_MIC_ADC_H,
		RT715_SET_GAIN_LINE_ADC_H, RT715_SET_GAIN_MIX_ADC_H,
		RT715_SET_GAIN_MIX_ADC2_Hपूर्ण;
	अचिन्हित पूर्णांक capture_reg_L[] = अणुRT715_SET_GAIN_MIC_ADC_L,
		RT715_SET_GAIN_LINE_ADC_L, RT715_SET_GAIN_MIX_ADC_L,
		RT715_SET_GAIN_MIX_ADC2_Lपूर्ण;
	अचिन्हित पूर्णांक addr_h, addr_l, val_h = 0x0, i, loop_cnt = 4;
	अचिन्हित पूर्णांक पढ़ो_ll, पढ़ो_rl;

	क्रम (i = 0; i < loop_cnt; i++) अणु
		addr_h = capture_reg_H[i];
		addr_l = capture_reg_L[i];
		rt715_get_gain(rt715, addr_h, addr_l, val_h, &पढ़ो_rl, &पढ़ो_ll);

		ucontrol->value.पूर्णांकeger.value[i * 2] = पढ़ो_ll & 0x7f;
		ucontrol->value.पूर्णांकeger.value[i * 2 + 1] = पढ़ो_rl & 0x7f;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(in_vol_tlv, -1725, 75, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(mic_vol_tlv, 0, 1000, 0);

अटल पूर्णांक rt715_चयन_info(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_BOOLEAN;
	uinfo->count = 8;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक rt715_vol_info(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 8;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 0x3f;
	वापस 0;
पूर्ण

#घोषणा SOC_DOUBLE_R_EXT(xname, reg_left, reg_right, xshअगरt, xmax, xinvert,\
	 xhandler_get, xhandler_put) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = (xname), \
	.info = snd_soc_info_volsw, \
	.get = xhandler_get, .put = xhandler_put, \
	.निजी_value = SOC_DOUBLE_R_VALUE(reg_left, reg_right, xshअगरt, \
					    xmax, xinvert) पूर्ण

#घोषणा RT715_MAIN_SWITCH_EXT(xname, xhandler_get, xhandler_put) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = (xname), \
	.info = rt715_चयन_info, \
	.get = xhandler_get, .put = xhandler_put, \
पूर्ण

#घोषणा RT715_MAIN_VOL_EXT_TLV(xname, xhandler_get, xhandler_put, tlv_array) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = (xname), \
	.access = SNDRV_CTL_ELEM_ACCESS_TLV_READ | \
		 SNDRV_CTL_ELEM_ACCESS_READWRITE, \
	.tlv.p = (tlv_array), \
	.info = rt715_vol_info, \
	.get = xhandler_get, .put = xhandler_put, \
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new rt715_snd_controls[] = अणु
	/* Capture चयन */
	RT715_MAIN_SWITCH_EXT("Capture Switch",
			rt715_set_मुख्य_चयन_get, rt715_set_मुख्य_चयन_put),
	/* Volume Control */
	RT715_MAIN_VOL_EXT_TLV("Capture Volume",
			rt715_set_मुख्य_vol_get, rt715_set_मुख्य_vol_put, in_vol_tlv),
	/* MIC Boost Control */
	SOC_DOUBLE_R_EXT_TLV("DMIC1 Boost", RT715_SET_GAIN_DMIC1_H,
			RT715_SET_GAIN_DMIC1_L, RT715_सूची_IN_SFT, 3, 0,
			rt715_set_amp_gain_get, rt715_set_amp_gain_put,
			mic_vol_tlv),
	SOC_DOUBLE_R_EXT_TLV("DMIC2 Boost", RT715_SET_GAIN_DMIC2_H,
			RT715_SET_GAIN_DMIC2_L, RT715_सूची_IN_SFT, 3, 0,
			rt715_set_amp_gain_get, rt715_set_amp_gain_put,
			mic_vol_tlv),
	SOC_DOUBLE_R_EXT_TLV("DMIC3 Boost", RT715_SET_GAIN_DMIC3_H,
			RT715_SET_GAIN_DMIC3_L, RT715_सूची_IN_SFT, 3, 0,
			rt715_set_amp_gain_get, rt715_set_amp_gain_put,
			mic_vol_tlv),
	SOC_DOUBLE_R_EXT_TLV("DMIC4 Boost", RT715_SET_GAIN_DMIC4_H,
			RT715_SET_GAIN_DMIC4_L, RT715_सूची_IN_SFT, 3, 0,
			rt715_set_amp_gain_get, rt715_set_amp_gain_put,
			mic_vol_tlv),
	SOC_DOUBLE_R_EXT_TLV("MIC1 Boost", RT715_SET_GAIN_MIC1_H,
			RT715_SET_GAIN_MIC1_L, RT715_सूची_IN_SFT, 3, 0,
			rt715_set_amp_gain_get, rt715_set_amp_gain_put,
			mic_vol_tlv),
	SOC_DOUBLE_R_EXT_TLV("MIC2 Boost", RT715_SET_GAIN_MIC2_H,
			RT715_SET_GAIN_MIC2_L, RT715_सूची_IN_SFT, 3, 0,
			rt715_set_amp_gain_get, rt715_set_amp_gain_put,
			mic_vol_tlv),
	SOC_DOUBLE_R_EXT_TLV("LINE1 Boost", RT715_SET_GAIN_LINE1_H,
			RT715_SET_GAIN_LINE1_L, RT715_सूची_IN_SFT, 3, 0,
			rt715_set_amp_gain_get, rt715_set_amp_gain_put,
			mic_vol_tlv),
	SOC_DOUBLE_R_EXT_TLV("LINE2 Boost", RT715_SET_GAIN_LINE2_H,
			RT715_SET_GAIN_LINE2_L, RT715_सूची_IN_SFT, 3, 0,
			rt715_set_amp_gain_get, rt715_set_amp_gain_put,
			mic_vol_tlv),
पूर्ण;

अटल पूर्णांक rt715_mux_get(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_kcontrol_component(kcontrol);
	काष्ठा rt715_priv *rt715 = snd_soc_component_get_drvdata(component);
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक reg, val;
	पूर्णांक ret;

	/* nid = e->reg, vid = 0xf01 */
	reg = RT715_VERB_SET_CONNECT_SEL | e->reg;
	ret = regmap_पढ़ो(rt715->regmap, reg, &val);
	अगर (ret < 0) अणु
		dev_err(component->dev, "%s: sdw read failed: %d\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	/*
	 * The first two indices of ADC Mux 24/25 are routed to the same
	 * hardware source. ie, ADC Mux 24 0/1 will both connect to MIC2.
	 * To have a unique set of inमाला_दो, we skip the index1 of the muxes.
	 */
	अगर ((e->reg == RT715_MUX_IN3 || e->reg == RT715_MUX_IN4) && (val > 0))
		val -= 1;
	ucontrol->value.क्रमागतerated.item[0] = val;

	वापस 0;
पूर्ण

अटल पूर्णांक rt715_mux_put(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_kcontrol_component(kcontrol);
	काष्ठा snd_soc_dapm_context *dapm =
				snd_soc_dapm_kcontrol_dapm(kcontrol);
	काष्ठा rt715_priv *rt715 = snd_soc_component_get_drvdata(component);
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक *item = ucontrol->value.क्रमागतerated.item;
	अचिन्हित पूर्णांक val, val2 = 0, change, reg;
	पूर्णांक ret;

	अगर (item[0] >= e->items)
		वापस -EINVAL;

	/* Verb ID = 0x701h, nid = e->reg */
	val = snd_soc_क्रमागत_item_to_val(e, item[0]) << e->shअगरt_l;

	reg = RT715_VERB_SET_CONNECT_SEL | e->reg;
	ret = regmap_पढ़ो(rt715->regmap, reg, &val2);
	अगर (ret < 0) अणु
		dev_err(component->dev, "%s: sdw read failed: %d\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	अगर (val == val2)
		change = 0;
	अन्यथा
		change = 1;

	अगर (change) अणु
		reg = RT715_VERB_SET_CONNECT_SEL | e->reg;
		regmap_ग_लिखो(rt715->regmap, reg, val);
	पूर्ण

	snd_soc_dapm_mux_update_घातer(dapm, kcontrol,
						item[0], e, शून्य);

	वापस change;
पूर्ण

अटल स्थिर अक्षर * स्थिर adc_22_23_mux_text[] = अणु
	"MIC1",
	"MIC2",
	"LINE1",
	"LINE2",
	"DMIC1",
	"DMIC2",
	"DMIC3",
	"DMIC4",
पूर्ण;

/*
 * Due to mux design क्रम nid 24 (MUX_IN3)/25 (MUX_IN4), connection index 0 and
 * 1 will be connected to the same dmic source, thereक्रमe we skip index 1 to
 * aव्योम misunderstanding on usage of dapm routing.
 */
अटल स्थिर अचिन्हित पूर्णांक rt715_adc_24_25_values[] = अणु
	0,
	2,
	3,
	4,
	5,
पूर्ण;

अटल स्थिर अक्षर * स्थिर adc_24_mux_text[] = अणु
	"MIC2",
	"DMIC1",
	"DMIC2",
	"DMIC3",
	"DMIC4",
पूर्ण;

अटल स्थिर अक्षर * स्थिर adc_25_mux_text[] = अणु
	"MIC1",
	"DMIC1",
	"DMIC2",
	"DMIC3",
	"DMIC4",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(
	rt715_adc22_क्रमागत, RT715_MUX_IN1, 0, adc_22_23_mux_text);

अटल SOC_ENUM_SINGLE_DECL(
	rt715_adc23_क्रमागत, RT715_MUX_IN2, 0, adc_22_23_mux_text);

अटल SOC_VALUE_ENUM_SINGLE_DECL(rt715_adc24_क्रमागत,
	RT715_MUX_IN3, 0, 0xf,
	adc_24_mux_text, rt715_adc_24_25_values);

अटल SOC_VALUE_ENUM_SINGLE_DECL(rt715_adc25_क्रमागत,
	RT715_MUX_IN4, 0, 0xf,
	adc_25_mux_text, rt715_adc_24_25_values);

अटल स्थिर काष्ठा snd_kcontrol_new rt715_adc22_mux =
	SOC_DAPM_ENUM_EXT("ADC 22 Mux", rt715_adc22_क्रमागत,
			rt715_mux_get, rt715_mux_put);

अटल स्थिर काष्ठा snd_kcontrol_new rt715_adc23_mux =
	SOC_DAPM_ENUM_EXT("ADC 23 Mux", rt715_adc23_क्रमागत,
			rt715_mux_get, rt715_mux_put);

अटल स्थिर काष्ठा snd_kcontrol_new rt715_adc24_mux =
	SOC_DAPM_ENUM_EXT("ADC 24 Mux", rt715_adc24_क्रमागत,
			rt715_mux_get, rt715_mux_put);

अटल स्थिर काष्ठा snd_kcontrol_new rt715_adc25_mux =
	SOC_DAPM_ENUM_EXT("ADC 25 Mux", rt715_adc25_क्रमागत,
			rt715_mux_get, rt715_mux_put);

अटल स्थिर काष्ठा snd_soc_dapm_widget rt715_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_INPUT("DMIC1"),
	SND_SOC_DAPM_INPUT("DMIC2"),
	SND_SOC_DAPM_INPUT("DMIC3"),
	SND_SOC_DAPM_INPUT("DMIC4"),
	SND_SOC_DAPM_INPUT("MIC1"),
	SND_SOC_DAPM_INPUT("MIC2"),
	SND_SOC_DAPM_INPUT("LINE1"),
	SND_SOC_DAPM_INPUT("LINE2"),
	SND_SOC_DAPM_ADC("ADC 07", शून्य, RT715_SET_STREAMID_MIC_ADC, 4, 0),
	SND_SOC_DAPM_ADC("ADC 08", शून्य, RT715_SET_STREAMID_LINE_ADC, 4, 0),
	SND_SOC_DAPM_ADC("ADC 09", शून्य, RT715_SET_STREAMID_MIX_ADC, 4, 0),
	SND_SOC_DAPM_ADC("ADC 27", शून्य, RT715_SET_STREAMID_MIX_ADC2, 4, 0),
	SND_SOC_DAPM_MUX("ADC 22 Mux", SND_SOC_NOPM, 0, 0,
		&rt715_adc22_mux),
	SND_SOC_DAPM_MUX("ADC 23 Mux", SND_SOC_NOPM, 0, 0,
		&rt715_adc23_mux),
	SND_SOC_DAPM_MUX("ADC 24 Mux", SND_SOC_NOPM, 0, 0,
		&rt715_adc24_mux),
	SND_SOC_DAPM_MUX("ADC 25 Mux", SND_SOC_NOPM, 0, 0,
		&rt715_adc25_mux),
	SND_SOC_DAPM_AIF_OUT("DP4TX", "DP4 Capture", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("DP6TX", "DP6 Capture", 0, SND_SOC_NOPM, 0, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route rt715_audio_map[] = अणु
	अणु"DP6TX", शून्य, "ADC 09"पूर्ण,
	अणु"DP6TX", शून्य, "ADC 08"पूर्ण,
	अणु"DP4TX", शून्य, "ADC 07"पूर्ण,
	अणु"DP4TX", शून्य, "ADC 27"पूर्ण,
	अणु"ADC 09", शून्य, "ADC 22 Mux"पूर्ण,
	अणु"ADC 08", शून्य, "ADC 23 Mux"पूर्ण,
	अणु"ADC 07", शून्य, "ADC 24 Mux"पूर्ण,
	अणु"ADC 27", शून्य, "ADC 25 Mux"पूर्ण,
	अणु"ADC 22 Mux", "MIC1", "MIC1"पूर्ण,
	अणु"ADC 22 Mux", "MIC2", "MIC2"पूर्ण,
	अणु"ADC 22 Mux", "LINE1", "LINE1"पूर्ण,
	अणु"ADC 22 Mux", "LINE2", "LINE2"पूर्ण,
	अणु"ADC 22 Mux", "DMIC1", "DMIC1"पूर्ण,
	अणु"ADC 22 Mux", "DMIC2", "DMIC2"पूर्ण,
	अणु"ADC 22 Mux", "DMIC3", "DMIC3"पूर्ण,
	अणु"ADC 22 Mux", "DMIC4", "DMIC4"पूर्ण,
	अणु"ADC 23 Mux", "MIC1", "MIC1"पूर्ण,
	अणु"ADC 23 Mux", "MIC2", "MIC2"पूर्ण,
	अणु"ADC 23 Mux", "LINE1", "LINE1"पूर्ण,
	अणु"ADC 23 Mux", "LINE2", "LINE2"पूर्ण,
	अणु"ADC 23 Mux", "DMIC1", "DMIC1"पूर्ण,
	अणु"ADC 23 Mux", "DMIC2", "DMIC2"पूर्ण,
	अणु"ADC 23 Mux", "DMIC3", "DMIC3"पूर्ण,
	अणु"ADC 23 Mux", "DMIC4", "DMIC4"पूर्ण,
	अणु"ADC 24 Mux", "MIC2", "MIC2"पूर्ण,
	अणु"ADC 24 Mux", "DMIC1", "DMIC1"पूर्ण,
	अणु"ADC 24 Mux", "DMIC2", "DMIC2"पूर्ण,
	अणु"ADC 24 Mux", "DMIC3", "DMIC3"पूर्ण,
	अणु"ADC 24 Mux", "DMIC4", "DMIC4"पूर्ण,
	अणु"ADC 25 Mux", "MIC1", "MIC1"पूर्ण,
	अणु"ADC 25 Mux", "DMIC1", "DMIC1"पूर्ण,
	अणु"ADC 25 Mux", "DMIC2", "DMIC2"पूर्ण,
	अणु"ADC 25 Mux", "DMIC3", "DMIC3"पूर्ण,
	अणु"ADC 25 Mux", "DMIC4", "DMIC4"पूर्ण,
पूर्ण;

अटल पूर्णांक rt715_set_bias_level(काष्ठा snd_soc_component *component,
				क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा snd_soc_dapm_context *dapm =
		snd_soc_component_get_dapm(component);
	काष्ठा rt715_priv *rt715 = snd_soc_component_get_drvdata(component);

	चयन (level) अणु
	हाल SND_SOC_BIAS_PREPARE:
		अगर (dapm->bias_level == SND_SOC_BIAS_STANDBY) अणु
			regmap_ग_लिखो(rt715->regmap,
						RT715_SET_AUDIO_POWER_STATE,
						AC_PWRST_D0);
			msleep(RT715_POWER_UP_DELAY_MS);
		पूर्ण
		अवरोध;

	हाल SND_SOC_BIAS_STANDBY:
		regmap_ग_लिखो(rt715->regmap,
					RT715_SET_AUDIO_POWER_STATE,
					AC_PWRST_D3);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
	dapm->bias_level = level;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_codec_dev_rt715 = अणु
	.set_bias_level = rt715_set_bias_level,
	.controls = rt715_snd_controls,
	.num_controls = ARRAY_SIZE(rt715_snd_controls),
	.dapm_widमाला_लो = rt715_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(rt715_dapm_widमाला_लो),
	.dapm_routes = rt715_audio_map,
	.num_dapm_routes = ARRAY_SIZE(rt715_audio_map),
पूर्ण;

अटल पूर्णांक rt715_set_sdw_stream(काष्ठा snd_soc_dai *dai, व्योम *sdw_stream,
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

अटल व्योम rt715_shutकरोwn(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_soc_dai *dai)

अणु
	काष्ठा sdw_stream_data *stream;

	stream = snd_soc_dai_get_dma_data(dai, substream);
	snd_soc_dai_set_dma_data(dai, substream, शून्य);
	kमुक्त(stream);
पूर्ण

अटल पूर्णांक rt715_pcm_hw_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt715_priv *rt715 = snd_soc_component_get_drvdata(component);
	काष्ठा sdw_stream_config stream_config;
	काष्ठा sdw_port_config port_config;
	क्रमागत sdw_data_direction direction;
	काष्ठा sdw_stream_data *stream;
	पूर्णांक retval, port, num_channels;
	अचिन्हित पूर्णांक val = 0;

	stream = snd_soc_dai_get_dma_data(dai, substream);

	अगर (!stream)
		वापस -EINVAL;

	अगर (!rt715->slave)
		वापस -EINVAL;

	चयन (dai->id) अणु
	हाल RT715_AIF1:
		direction = SDW_DATA_सूची_TX;
		port = 6;
		rt715_index_ग_लिखो(rt715->regmap, RT715_SDW_INPUT_SEL, 0xa500);
		अवरोध;
	हाल RT715_AIF2:
		direction = SDW_DATA_सूची_TX;
		port = 4;
		rt715_index_ग_लिखो(rt715->regmap, RT715_SDW_INPUT_SEL, 0xa000);
		अवरोध;
	शेष:
		dev_err(component->dev, "Invalid DAI id %d\n", dai->id);
		वापस -EINVAL;
	पूर्ण

	stream_config.frame_rate =  params_rate(params);
	stream_config.ch_count = params_channels(params);
	stream_config.bps = snd_pcm_क्रमmat_width(params_क्रमmat(params));
	stream_config.direction = direction;

	num_channels = params_channels(params);
	port_config.ch_mask = (1 << (num_channels)) - 1;
	port_config.num = port;

	retval = sdw_stream_add_slave(rt715->slave, &stream_config,
					&port_config, 1, stream->sdw_stream);
	अगर (retval) अणु
		dev_err(dai->dev, "Unable to configure port\n");
		वापस retval;
	पूर्ण

	चयन (params_rate(params)) अणु
	/* bit 14 0:48K 1:44.1K */
	/* bit 15 Stream Type 0:PCM 1:Non-PCM, should always be PCM */
	हाल 44100:
		val |= 0x40 << 8;
		अवरोध;
	हाल 48000:
		val |= 0x0 << 8;
		अवरोध;
	शेष:
		dev_err(component->dev, "Unsupported sample rate %d\n",
			params_rate(params));
		वापस -EINVAL;
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

	regmap_ग_लिखो(rt715->regmap, RT715_MIC_ADC_FORMAT_H, val);
	regmap_ग_लिखो(rt715->regmap, RT715_MIC_LINE_FORMAT_H, val);
	regmap_ग_लिखो(rt715->regmap, RT715_MIX_ADC_FORMAT_H, val);
	regmap_ग_लिखो(rt715->regmap, RT715_MIX_ADC2_FORMAT_H, val);

	वापस retval;
पूर्ण

अटल पूर्णांक rt715_pcm_hw_मुक्त(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt715_priv *rt715 = snd_soc_component_get_drvdata(component);
	काष्ठा sdw_stream_data *stream =
		snd_soc_dai_get_dma_data(dai, substream);

	अगर (!rt715->slave)
		वापस -EINVAL;

	sdw_stream_हटाओ_slave(rt715->slave, stream->sdw_stream);
	वापस 0;
पूर्ण

#घोषणा RT715_STEREO_RATES (SNDRV_PCM_RATE_44100 | SNDRV_PCM_RATE_48000)
#घोषणा RT715_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE | \
			SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S8)

अटल स्थिर काष्ठा snd_soc_dai_ops rt715_ops = अणु
	.hw_params	= rt715_pcm_hw_params,
	.hw_मुक्त	= rt715_pcm_hw_मुक्त,
	.set_sdw_stream	= rt715_set_sdw_stream,
	.shutकरोwn	= rt715_shutकरोwn,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver rt715_dai[] = अणु
	अणु
		.name = "rt715-aif1",
		.id = RT715_AIF1,
		.capture = अणु
			.stream_name = "DP6 Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT715_STEREO_RATES,
			.क्रमmats = RT715_FORMATS,
		पूर्ण,
		.ops = &rt715_ops,
	पूर्ण,
	अणु
		.name = "rt715-aif2",
		.id = RT715_AIF2,
		.capture = अणु
			.stream_name = "DP4 Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = RT715_STEREO_RATES,
			.क्रमmats = RT715_FORMATS,
		पूर्ण,
		.ops = &rt715_ops,
	पूर्ण,
पूर्ण;

/* Bus घड़ी frequency */
#घोषणा RT715_CLK_FREQ_9600000HZ 9600000
#घोषणा RT715_CLK_FREQ_12000000HZ 12000000
#घोषणा RT715_CLK_FREQ_6000000HZ 6000000
#घोषणा RT715_CLK_FREQ_4800000HZ 4800000
#घोषणा RT715_CLK_FREQ_2400000HZ 2400000
#घोषणा RT715_CLK_FREQ_12288000HZ 12288000

पूर्णांक rt715_घड़ी_config(काष्ठा device *dev)
अणु
	काष्ठा rt715_priv *rt715 = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक clk_freq, value;

	clk_freq = (rt715->params.curr_dr_freq >> 1);

	चयन (clk_freq) अणु
	हाल RT715_CLK_FREQ_12000000HZ:
		value = 0x0;
		अवरोध;
	हाल RT715_CLK_FREQ_6000000HZ:
		value = 0x1;
		अवरोध;
	हाल RT715_CLK_FREQ_9600000HZ:
		value = 0x2;
		अवरोध;
	हाल RT715_CLK_FREQ_4800000HZ:
		value = 0x3;
		अवरोध;
	हाल RT715_CLK_FREQ_2400000HZ:
		value = 0x4;
		अवरोध;
	हाल RT715_CLK_FREQ_12288000HZ:
		value = 0x5;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_ग_लिखो(rt715->regmap, 0xe0, value);
	regmap_ग_लिखो(rt715->regmap, 0xf0, value);

	वापस 0;
पूर्ण

पूर्णांक rt715_init(काष्ठा device *dev, काष्ठा regmap *sdw_regmap,
	काष्ठा regmap *regmap, काष्ठा sdw_slave *slave)
अणु
	काष्ठा rt715_priv *rt715;
	पूर्णांक ret;

	rt715 = devm_kzalloc(dev, माप(*rt715), GFP_KERNEL);
	अगर (!rt715)
		वापस -ENOMEM;

	dev_set_drvdata(dev, rt715);
	rt715->slave = slave;
	rt715->regmap = regmap;
	rt715->sdw_regmap = sdw_regmap;

	/*
	 * Mark hw_init to false
	 * HW init will be perक्रमmed when device reports present
	 */
	rt715->hw_init = false;
	rt715->first_hw_init = false;

	ret = devm_snd_soc_रेजिस्टर_component(dev,
						&soc_codec_dev_rt715,
						rt715_dai,
						ARRAY_SIZE(rt715_dai));

	वापस ret;
पूर्ण

पूर्णांक rt715_io_init(काष्ठा device *dev, काष्ठा sdw_slave *slave)
अणु
	काष्ठा rt715_priv *rt715 = dev_get_drvdata(dev);

	अगर (rt715->hw_init)
		वापस 0;

	/*
	 * PM runसमय is only enabled when a Slave reports as Attached
	 */
	अगर (!rt715->first_hw_init) अणु
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

	/* Mute nid=08h/09h */
	regmap_ग_लिखो(rt715->regmap, RT715_SET_GAIN_LINE_ADC_H, 0xb080);
	regmap_ग_लिखो(rt715->regmap, RT715_SET_GAIN_MIX_ADC_H, 0xb080);
	/* Mute nid=07h/27h */
	regmap_ग_लिखो(rt715->regmap, RT715_SET_GAIN_MIC_ADC_H, 0xb080);
	regmap_ग_लिखो(rt715->regmap, RT715_SET_GAIN_MIX_ADC2_H, 0xb080);

	/* Set Pin Widget */
	regmap_ग_लिखो(rt715->regmap, RT715_SET_PIN_DMIC1, 0x20);
	regmap_ग_लिखो(rt715->regmap, RT715_SET_PIN_DMIC2, 0x20);
	regmap_ग_लिखो(rt715->regmap, RT715_SET_PIN_DMIC3, 0x20);
	regmap_ग_लिखो(rt715->regmap, RT715_SET_PIN_DMIC4, 0x20);
	/* Set Converter Stream */
	regmap_ग_लिखो(rt715->regmap, RT715_SET_STREAMID_LINE_ADC, 0x10);
	regmap_ग_लिखो(rt715->regmap, RT715_SET_STREAMID_MIX_ADC, 0x10);
	regmap_ग_लिखो(rt715->regmap, RT715_SET_STREAMID_MIC_ADC, 0x10);
	regmap_ग_लिखो(rt715->regmap, RT715_SET_STREAMID_MIX_ADC2, 0x10);
	/* Set Configuration Default */
	regmap_ग_लिखो(rt715->regmap, RT715_SET_DMIC1_CONFIG_DEFAULT1, 0xd0);
	regmap_ग_लिखो(rt715->regmap, RT715_SET_DMIC1_CONFIG_DEFAULT2, 0x11);
	regmap_ग_लिखो(rt715->regmap, RT715_SET_DMIC1_CONFIG_DEFAULT3, 0xa1);
	regmap_ग_लिखो(rt715->regmap, RT715_SET_DMIC1_CONFIG_DEFAULT4, 0x81);
	regmap_ग_लिखो(rt715->regmap, RT715_SET_DMIC2_CONFIG_DEFAULT1, 0xd1);
	regmap_ग_लिखो(rt715->regmap, RT715_SET_DMIC2_CONFIG_DEFAULT2, 0x11);
	regmap_ग_लिखो(rt715->regmap, RT715_SET_DMIC2_CONFIG_DEFAULT3, 0xa1);
	regmap_ग_लिखो(rt715->regmap, RT715_SET_DMIC2_CONFIG_DEFAULT4, 0x81);
	regmap_ग_लिखो(rt715->regmap, RT715_SET_DMIC3_CONFIG_DEFAULT1, 0xd0);
	regmap_ग_लिखो(rt715->regmap, RT715_SET_DMIC3_CONFIG_DEFAULT2, 0x11);
	regmap_ग_लिखो(rt715->regmap, RT715_SET_DMIC3_CONFIG_DEFAULT3, 0xa1);
	regmap_ग_लिखो(rt715->regmap, RT715_SET_DMIC3_CONFIG_DEFAULT4, 0x81);
	regmap_ग_लिखो(rt715->regmap, RT715_SET_DMIC4_CONFIG_DEFAULT1, 0xd1);
	regmap_ग_लिखो(rt715->regmap, RT715_SET_DMIC4_CONFIG_DEFAULT2, 0x11);
	regmap_ग_लिखो(rt715->regmap, RT715_SET_DMIC4_CONFIG_DEFAULT3, 0xa1);
	regmap_ग_लिखो(rt715->regmap, RT715_SET_DMIC4_CONFIG_DEFAULT4, 0x81);

	/* Finish Initial Settings, set घातer to D3 */
	regmap_ग_लिखो(rt715->regmap, RT715_SET_AUDIO_POWER_STATE, AC_PWRST_D3);

	अगर (rt715->first_hw_init)
		regcache_mark_dirty(rt715->regmap);
	अन्यथा
		rt715->first_hw_init = true;

	/* Mark Slave initialization complete */
	rt715->hw_init = true;

	pm_runसमय_mark_last_busy(&slave->dev);
	pm_runसमय_put_स्वतःsuspend(&slave->dev);

	वापस 0;
पूर्ण

MODULE_DESCRIPTION("ASoC rt715 driver");
MODULE_DESCRIPTION("ASoC rt715 driver SDW");
MODULE_AUTHOR("Jack Yu <jack.yu@realtek.com>");
MODULE_LICENSE("GPL v2");
