<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
//
// rt715-sdca.c -- rt715 ALSA SoC audio driver
//
// Copyright(c) 2020 Realtek Semiconductor Corp.
//
//
//

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pm.h>
#समावेश <linux/soundwire/sdw.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>
#समावेश <linux/soundwire/sdw_रेजिस्टरs.h>

#समावेश "rt715-sdca.h"

अटल पूर्णांक rt715_sdca_index_ग_लिखो(काष्ठा rt715_sdca_priv *rt715,
		अचिन्हित पूर्णांक nid, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक value)
अणु
	काष्ठा regmap *regmap = rt715->mbq_regmap;
	अचिन्हित पूर्णांक addr;
	पूर्णांक ret;

	addr = (nid << 20) | reg;

	ret = regmap_ग_लिखो(regmap, addr, value);
	अगर (ret < 0)
		dev_err(&rt715->slave->dev,
				"Failed to set private value: %08x <= %04x %d\n", ret, addr,
				value);

	वापस ret;
पूर्ण

अटल पूर्णांक rt715_sdca_index_पढ़ो(काष्ठा rt715_sdca_priv *rt715,
		अचिन्हित पूर्णांक nid, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक *value)
अणु
	काष्ठा regmap *regmap = rt715->mbq_regmap;
	अचिन्हित पूर्णांक addr;
	पूर्णांक ret;

	addr = (nid << 20) | reg;

	ret = regmap_पढ़ो(regmap, addr, value);
	अगर (ret < 0)
		dev_err(&rt715->slave->dev,
				"Failed to get private value: %06x => %04x ret=%d\n",
				addr, *value, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक rt715_sdca_index_update_bits(काष्ठा rt715_sdca_priv *rt715,
	अचिन्हित पूर्णांक nid, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक val)
अणु
	अचिन्हित पूर्णांक पंचांगp;
	पूर्णांक ret;

	ret = rt715_sdca_index_पढ़ो(rt715, nid, reg, &पंचांगp);
	अगर (ret < 0)
		वापस ret;

	set_mask_bits(&पंचांगp, mask, val);

	वापस rt715_sdca_index_ग_लिखो(rt715, nid, reg, पंचांगp);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक rt715_sdca_vol_gain(अचिन्हित पूर्णांक u_ctrl_val,
		अचिन्हित पूर्णांक vol_max, अचिन्हित पूर्णांक vol_gain_sft)
अणु
	अचिन्हित पूर्णांक val;

	अगर (u_ctrl_val > vol_max)
		u_ctrl_val = vol_max;
	val = u_ctrl_val;
	u_ctrl_val =
		((असल(u_ctrl_val - vol_gain_sft) * RT715_SDCA_DB_STEP) << 8) / 1000;
	अगर (val <= vol_gain_sft) अणु
		u_ctrl_val = ~u_ctrl_val;
		u_ctrl_val += 1;
	पूर्ण
	u_ctrl_val &= 0xffff;

	वापस u_ctrl_val;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक rt715_sdca_boost_gain(अचिन्हित पूर्णांक u_ctrl_val,
		अचिन्हित पूर्णांक b_max, अचिन्हित पूर्णांक b_gain_sft)
अणु
	अगर (u_ctrl_val > b_max)
		u_ctrl_val = b_max;

	वापस (u_ctrl_val * 10) << b_gain_sft;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक rt715_sdca_get_gain(अचिन्हित पूर्णांक reg_val,
		अचिन्हित पूर्णांक gain_sft)
अणु
	अचिन्हित पूर्णांक neg_flag = 0;

	अगर (reg_val & BIT(15)) अणु
		reg_val = ~(reg_val - 1) & 0xffff;
		neg_flag = 1;
	पूर्ण
	reg_val *= 1000;
	reg_val >>= 8;
	अगर (neg_flag)
		reg_val = gain_sft - reg_val / RT715_SDCA_DB_STEP;
	अन्यथा
		reg_val = gain_sft + reg_val / RT715_SDCA_DB_STEP;

	वापस reg_val;
पूर्ण

/* SDCA Volume/Boost control */
अटल पूर्णांक rt715_sdca_set_amp_gain_put(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा soc_mixer_control *mc =
		(काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	काष्ठा rt715_sdca_priv *rt715 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक gain_val, i, k_changed = 0;
	पूर्णांक ret;

	क्रम (i = 0; i < 2; i++) अणु
		अगर (ucontrol->value.पूर्णांकeger.value[i] != rt715->kctl_2ch_orig[i]) अणु
			k_changed = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < 2; i++) अणु
		rt715->kctl_2ch_orig[i] = ucontrol->value.पूर्णांकeger.value[i];
		gain_val =
			rt715_sdca_vol_gain(ucontrol->value.पूर्णांकeger.value[i], mc->max,
				mc->shअगरt);
		ret = regmap_ग_लिखो(rt715->mbq_regmap, mc->reg + i, gain_val);
		अगर (ret != 0) अणु
			dev_err(component->dev, "Failed to write 0x%x=0x%x\n",
				mc->reg + i, gain_val);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस k_changed;
पूर्ण

अटल पूर्णांक rt715_sdca_set_amp_gain_4ch_put(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा rt715_sdca_priv *rt715 = snd_soc_component_get_drvdata(component);
	काष्ठा rt715_sdca_kcontrol_निजी *p =
		(काष्ठा rt715_sdca_kcontrol_निजी *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक reg_base = p->reg_base, k_changed = 0;
	स्थिर अचिन्हित पूर्णांक gain_sft = 0x2f;
	अचिन्हित पूर्णांक gain_val, i;
	पूर्णांक ret;

	क्रम (i = 0; i < 4; i++) अणु
		अगर (ucontrol->value.पूर्णांकeger.value[i] != rt715->kctl_4ch_orig[i]) अणु
			k_changed = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < 4; i++) अणु
		rt715->kctl_4ch_orig[i] = ucontrol->value.पूर्णांकeger.value[i];
		gain_val =
			rt715_sdca_vol_gain(ucontrol->value.पूर्णांकeger.value[i], p->max,
				gain_sft);
		ret = regmap_ग_लिखो(rt715->mbq_regmap, reg_base + i,
				gain_val);
		अगर (ret != 0) अणु
			dev_err(component->dev, "Failed to write 0x%x=0x%x\n",
				reg_base + i, gain_val);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस k_changed;
पूर्ण

अटल पूर्णांक rt715_sdca_set_amp_gain_8ch_put(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा rt715_sdca_priv *rt715 = snd_soc_component_get_drvdata(component);
	काष्ठा rt715_sdca_kcontrol_निजी *p =
		(काष्ठा rt715_sdca_kcontrol_निजी *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक reg_base = p->reg_base, i, k_changed = 0;
	स्थिर अचिन्हित पूर्णांक gain_sft = 8;
	अचिन्हित पूर्णांक gain_val, reg;
	पूर्णांक ret;

	क्रम (i = 0; i < 8; i++) अणु
		अगर (ucontrol->value.पूर्णांकeger.value[i] != rt715->kctl_8ch_orig[i]) अणु
			k_changed = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < 8; i++) अणु
		rt715->kctl_8ch_orig[i] = ucontrol->value.पूर्णांकeger.value[i];
		gain_val =
			rt715_sdca_boost_gain(ucontrol->value.पूर्णांकeger.value[i], p->max,
				gain_sft);
		reg = i < 7 ? reg_base + i : (reg_base - 1) | BIT(15);
		ret = regmap_ग_लिखो(rt715->mbq_regmap, reg, gain_val);
		अगर (ret != 0) अणु
			dev_err(component->dev, "Failed to write 0x%x=0x%x\n",
				reg, gain_val);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस k_changed;
पूर्ण

अटल पूर्णांक rt715_sdca_set_amp_gain_get(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा soc_mixer_control *mc =
		(काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	काष्ठा rt715_sdca_priv *rt715 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक val, i;
	पूर्णांक ret;

	क्रम (i = 0; i < 2; i++) अणु
		ret = regmap_पढ़ो(rt715->mbq_regmap, mc->reg + i, &val);
		अगर (ret < 0) अणु
			dev_err(component->dev, "Failed to read 0x%x, ret=%d\n",
				mc->reg + i, ret);
			वापस ret;
		पूर्ण
		ucontrol->value.पूर्णांकeger.value[i] = rt715_sdca_get_gain(val, mc->shअगरt);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt715_sdca_set_amp_gain_4ch_get(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा rt715_sdca_priv *rt715 = snd_soc_component_get_drvdata(component);
	काष्ठा rt715_sdca_kcontrol_निजी *p =
		(काष्ठा rt715_sdca_kcontrol_निजी *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक reg_base = p->reg_base, i;
	स्थिर अचिन्हित पूर्णांक gain_sft = 0x2f;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	क्रम (i = 0; i < 4; i++) अणु
		ret = regmap_पढ़ो(rt715->mbq_regmap, reg_base + i, &val);
		अगर (ret < 0) अणु
			dev_err(component->dev, "Failed to read 0x%x, ret=%d\n",
				reg_base + i, ret);
			वापस ret;
		पूर्ण
		ucontrol->value.पूर्णांकeger.value[i] = rt715_sdca_get_gain(val, gain_sft);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt715_sdca_set_amp_gain_8ch_get(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा rt715_sdca_priv *rt715 = snd_soc_component_get_drvdata(component);
	काष्ठा rt715_sdca_kcontrol_निजी *p =
		(काष्ठा rt715_sdca_kcontrol_निजी *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक reg_base = p->reg_base;
	स्थिर अचिन्हित पूर्णांक gain_sft = 8;
	अचिन्हित पूर्णांक val_l, val_r;
	अचिन्हित पूर्णांक i, reg;
	पूर्णांक ret;

	क्रम (i = 0; i < 8; i += 2) अणु
		ret = regmap_पढ़ो(rt715->mbq_regmap, reg_base + i, &val_l);
		अगर (ret < 0) अणु
			dev_err(component->dev, "Failed to read 0x%x, ret=%d\n",
					reg_base + i, ret);
			वापस ret;
		पूर्ण
		ucontrol->value.पूर्णांकeger.value[i] = (val_l >> gain_sft) / 10;

		reg = (i == 6) ? (reg_base - 1) | BIT(15) : reg_base + 1 + i;
		ret = regmap_पढ़ो(rt715->mbq_regmap, reg, &val_r);
		अगर (ret < 0) अणु
			dev_err(component->dev, "Failed to read 0x%x, ret=%d\n",
					reg, ret);
			वापस ret;
		पूर्ण
		ucontrol->value.पूर्णांकeger.value[i + 1] = (val_r >> gain_sft) / 10;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(in_vol_tlv, -17625, 375, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(mic_vol_tlv, 0, 1000, 0);

अटल पूर्णांक rt715_sdca_get_volsw(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा rt715_sdca_kcontrol_निजी *p =
		(काष्ठा rt715_sdca_kcontrol_निजी *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक reg_base = p->reg_base;
	अचिन्हित पूर्णांक invert = p->invert, i;
	पूर्णांक val;

	क्रम (i = 0; i < p->count; i += 2) अणु
		val = snd_soc_component_पढ़ो(component, reg_base + i);
		अगर (val < 0)
			वापस -EINVAL;
		ucontrol->value.पूर्णांकeger.value[i] = invert ? p->max - val : val;

		val = snd_soc_component_पढ़ो(component, reg_base + 1 + i);
		अगर (val < 0)
			वापस -EINVAL;
		ucontrol->value.पूर्णांकeger.value[i + 1] =
			invert ? p->max - val : val;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rt715_sdca_put_volsw(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा rt715_sdca_priv *rt715 = snd_soc_component_get_drvdata(component);
	काष्ठा rt715_sdca_kcontrol_निजी *p =
		(काष्ठा rt715_sdca_kcontrol_निजी *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक val[4] = अणु0पूर्ण, val_mask, i, k_changed = 0;
	अचिन्हित पूर्णांक reg = p->reg_base;
	अचिन्हित पूर्णांक shअगरt = p->shअगरt;
	अचिन्हित पूर्णांक max = p->max;
	अचिन्हित पूर्णांक mask = (1 << fls(max)) - 1;
	अचिन्हित पूर्णांक invert = p->invert;
	पूर्णांक err;

	क्रम (i = 0; i < 4; i++) अणु
		अगर (ucontrol->value.पूर्णांकeger.value[i] != rt715->kctl_चयन_orig[i]) अणु
			k_changed = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < 2; i++) अणु
		rt715->kctl_चयन_orig[i * 2] = ucontrol->value.पूर्णांकeger.value[i * 2];
		val[i * 2] = ucontrol->value.पूर्णांकeger.value[i * 2] & mask;
		अगर (invert)
			val[i * 2] = max - val[i * 2];
		val_mask = mask << shअगरt;
		val[i * 2] <<= shअगरt;

		rt715->kctl_चयन_orig[i * 2 + 1] =
			ucontrol->value.पूर्णांकeger.value[i * 2 + 1];
		val[i * 2 + 1] =
			ucontrol->value.पूर्णांकeger.value[i * 2 + 1] & mask;
		अगर (invert)
			val[i * 2 + 1] = max - val[i * 2 + 1];

		val[i * 2 + 1] <<=  shअगरt;

		err = snd_soc_component_update_bits(component, reg + i * 2, val_mask,
				val[i * 2]);
		अगर (err < 0)
			वापस err;

		err = snd_soc_component_update_bits(component, reg + 1 + i * 2,
			val_mask, val[i * 2 + 1]);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस k_changed;
पूर्ण

अटल पूर्णांक rt715_sdca_fu_info(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा rt715_sdca_kcontrol_निजी *p =
		(काष्ठा rt715_sdca_kcontrol_निजी *)kcontrol->निजी_value;

	अगर (p->max == 1)
		uinfo->type = SNDRV_CTL_ELEM_TYPE_BOOLEAN;
	अन्यथा
		uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = p->count;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = p->max;
	वापस 0;
पूर्ण

#घोषणा RT715_SDCA_PR_VALUE(xreg_base, xcount, xmax, xshअगरt, xinvert) \
	((अचिन्हित दीर्घ)&(काष्ठा rt715_sdca_kcontrol_निजी) \
		अणु.reg_base = xreg_base, .count = xcount, .max = xmax, \
		.shअगरt = xshअगरt, .invert = xinvertपूर्ण)

#घोषणा RT715_SDCA_FU_CTRL(xname, reg_base, xshअगरt, xmax, xinvert, xcount) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = (xname), \
	.info = rt715_sdca_fu_info, \
	.get = rt715_sdca_get_volsw, \
	.put = rt715_sdca_put_volsw, \
	.निजी_value = RT715_SDCA_PR_VALUE(reg_base, xcount, xmax, \
					xshअगरt, xinvert)पूर्ण

#घोषणा SOC_DOUBLE_R_EXT(xname, reg_left, reg_right, xshअगरt, xmax, xinvert,\
	 xhandler_get, xhandler_put) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = (xname), \
	.info = snd_soc_info_volsw, \
	.get = xhandler_get, .put = xhandler_put, \
	.निजी_value = SOC_DOUBLE_R_VALUE(reg_left, reg_right, xshअगरt, \
					    xmax, xinvert) पूर्ण

#घोषणा RT715_SDCA_EXT_TLV(xname, reg_base, xhandler_get,\
	 xhandler_put, tlv_array, xcount, xmax) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = (xname), \
	.access = SNDRV_CTL_ELEM_ACCESS_TLV_READ | \
		 SNDRV_CTL_ELEM_ACCESS_READWRITE, \
	.tlv.p = (tlv_array), \
	.info = rt715_sdca_fu_info, \
	.get = xhandler_get, .put = xhandler_put, \
	.निजी_value = RT715_SDCA_PR_VALUE(reg_base, xcount, xmax, 0, 0) पूर्ण

#घोषणा RT715_SDCA_BOOST_EXT_TLV(xname, reg_base, xhandler_get,\
	 xhandler_put, tlv_array, xcount, xmax) \
अणु	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = (xname), \
	.access = SNDRV_CTL_ELEM_ACCESS_TLV_READ | \
		 SNDRV_CTL_ELEM_ACCESS_READWRITE, \
	.tlv.p = (tlv_array), \
	.info = rt715_sdca_fu_info, \
	.get = xhandler_get, .put = xhandler_put, \
	.निजी_value = RT715_SDCA_PR_VALUE(reg_base, xcount, xmax, 0, 0) पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new rt715_sdca_snd_controls[] = अणु
	/* Capture चयन */
	SOC_DOUBLE_R("FU0A Capture Switch",
		SDW_SDCA_CTL(FUN_MIC_ARRAY, RT715_SDCA_FU_ADC7_27_VOL,
			RT715_SDCA_FU_MUTE_CTRL, CH_01),
		SDW_SDCA_CTL(FUN_MIC_ARRAY, RT715_SDCA_FU_ADC7_27_VOL,
			RT715_SDCA_FU_MUTE_CTRL, CH_02),
			0, 1, 1),
	RT715_SDCA_FU_CTRL("FU02 Capture Switch",
		SDW_SDCA_CTL(FUN_MIC_ARRAY, RT715_SDCA_FU_ADC8_9_VOL,
			RT715_SDCA_FU_MUTE_CTRL, CH_01),
			0, 1, 1, 4),
	RT715_SDCA_FU_CTRL("FU06 Capture Switch",
		SDW_SDCA_CTL(FUN_MIC_ARRAY, RT715_SDCA_FU_ADC10_11_VOL,
			RT715_SDCA_FU_MUTE_CTRL, CH_01),
			0, 1, 1, 4),
	/* Volume Control */
	SOC_DOUBLE_R_EXT_TLV("FU0A Capture Volume",
		SDW_SDCA_CTL(FUN_MIC_ARRAY, RT715_SDCA_FU_ADC7_27_VOL,
			RT715_SDCA_FU_VOL_CTRL, CH_01),
		SDW_SDCA_CTL(FUN_MIC_ARRAY, RT715_SDCA_FU_ADC7_27_VOL,
			RT715_SDCA_FU_VOL_CTRL, CH_02),
			0x2f, 0x7f, 0,
		rt715_sdca_set_amp_gain_get, rt715_sdca_set_amp_gain_put,
		in_vol_tlv),
	RT715_SDCA_EXT_TLV("FU02 Capture Volume",
		SDW_SDCA_CTL(FUN_MIC_ARRAY, RT715_SDCA_FU_ADC8_9_VOL,
			RT715_SDCA_FU_VOL_CTRL, CH_01),
		rt715_sdca_set_amp_gain_4ch_get,
		rt715_sdca_set_amp_gain_4ch_put,
		in_vol_tlv, 4, 0x7f),
	RT715_SDCA_EXT_TLV("FU06 Capture Volume",
		SDW_SDCA_CTL(FUN_MIC_ARRAY, RT715_SDCA_FU_ADC10_11_VOL,
			RT715_SDCA_FU_VOL_CTRL, CH_01),
		rt715_sdca_set_amp_gain_4ch_get,
		rt715_sdca_set_amp_gain_4ch_put,
		in_vol_tlv, 4, 0x7f),
	/* MIC Boost Control */
	RT715_SDCA_BOOST_EXT_TLV("FU0E Boost",
		SDW_SDCA_CTL(FUN_MIC_ARRAY, RT715_SDCA_FU_DMIC_GAIN_EN,
			RT715_SDCA_FU_DMIC_GAIN_CTRL, CH_01),
			rt715_sdca_set_amp_gain_8ch_get,
			rt715_sdca_set_amp_gain_8ch_put,
			mic_vol_tlv, 8, 3),
	RT715_SDCA_BOOST_EXT_TLV("FU0C Boost",
		SDW_SDCA_CTL(FUN_MIC_ARRAY, RT715_SDCA_FU_AMIC_GAIN_EN,
			RT715_SDCA_FU_DMIC_GAIN_CTRL, CH_01),
			rt715_sdca_set_amp_gain_8ch_get,
			rt715_sdca_set_amp_gain_8ch_put,
			mic_vol_tlv, 8, 3),
पूर्ण;

अटल पूर्णांक rt715_sdca_mux_get(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_kcontrol_component(kcontrol);
	काष्ठा rt715_sdca_priv *rt715 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक val, mask_sft;

	अगर (म_माला(ucontrol->id.name, "ADC 22 Mux"))
		mask_sft = 12;
	अन्यथा अगर (म_माला(ucontrol->id.name, "ADC 23 Mux"))
		mask_sft = 8;
	अन्यथा अगर (म_माला(ucontrol->id.name, "ADC 24 Mux"))
		mask_sft = 4;
	अन्यथा अगर (म_माला(ucontrol->id.name, "ADC 25 Mux"))
		mask_sft = 0;
	अन्यथा
		वापस -EINVAL;

	rt715_sdca_index_पढ़ो(rt715, RT715_VENDOR_HDA_CTL,
		RT715_HDA_LEGACY_MUX_CTL1, &val);
	val = (val >> mask_sft) & 0xf;

	/*
	 * The first two indices of ADC Mux 24/25 are routed to the same
	 * hardware source. ie, ADC Mux 24 0/1 will both connect to MIC2.
	 * To have a unique set of inमाला_दो, we skip the index1 of the muxes.
	 */
	अगर ((म_माला(ucontrol->id.name, "ADC 24 Mux") ||
		म_माला(ucontrol->id.name, "ADC 25 Mux")) && val > 0)
		val -= 1;
	ucontrol->value.क्रमागतerated.item[0] = val;

	वापस 0;
पूर्ण

अटल पूर्णांक rt715_sdca_mux_put(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_kcontrol_component(kcontrol);
	काष्ठा snd_soc_dapm_context *dapm =
				snd_soc_dapm_kcontrol_dapm(kcontrol);
	काष्ठा rt715_sdca_priv *rt715 = snd_soc_component_get_drvdata(component);
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक *item = ucontrol->value.क्रमागतerated.item;
	अचिन्हित पूर्णांक val, val2 = 0, change, mask_sft;

	अगर (item[0] >= e->items)
		वापस -EINVAL;

	अगर (म_माला(ucontrol->id.name, "ADC 22 Mux"))
		mask_sft = 12;
	अन्यथा अगर (म_माला(ucontrol->id.name, "ADC 23 Mux"))
		mask_sft = 8;
	अन्यथा अगर (म_माला(ucontrol->id.name, "ADC 24 Mux"))
		mask_sft = 4;
	अन्यथा अगर (म_माला(ucontrol->id.name, "ADC 25 Mux"))
		mask_sft = 0;
	अन्यथा
		वापस -EINVAL;

	/* Verb ID = 0x701h, nid = e->reg */
	val = snd_soc_क्रमागत_item_to_val(e, item[0]) << e->shअगरt_l;

	rt715_sdca_index_पढ़ो(rt715, RT715_VENDOR_HDA_CTL,
		RT715_HDA_LEGACY_MUX_CTL1, &val2);
	val2 = (val2 >> mask_sft) & 0xf;

	change = val != val2;

	अगर (change)
		rt715_sdca_index_update_bits(rt715, RT715_VENDOR_HDA_CTL,
			RT715_HDA_LEGACY_MUX_CTL1, 0xf << mask_sft, val << mask_sft);

	snd_soc_dapm_mux_update_घातer(dapm, kcontrol, item[0], e, शून्य);

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
अटल पूर्णांक rt715_adc_24_25_values[] = अणु
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

अटल SOC_ENUM_SINGLE_DECL(rt715_adc22_क्रमागत, SND_SOC_NOPM, 0,
	adc_22_23_mux_text);

अटल SOC_ENUM_SINGLE_DECL(rt715_adc23_क्रमागत, SND_SOC_NOPM, 0,
	adc_22_23_mux_text);

अटल SOC_VALUE_ENUM_SINGLE_DECL(rt715_adc24_क्रमागत,
	SND_SOC_NOPM, 0, 0xf,
	adc_24_mux_text, rt715_adc_24_25_values);
अटल SOC_VALUE_ENUM_SINGLE_DECL(rt715_adc25_क्रमागत,
	SND_SOC_NOPM, 0, 0xf,
	adc_25_mux_text, rt715_adc_24_25_values);

अटल स्थिर काष्ठा snd_kcontrol_new rt715_adc22_mux =
	SOC_DAPM_ENUM_EXT("ADC 22 Mux", rt715_adc22_क्रमागत,
			rt715_sdca_mux_get, rt715_sdca_mux_put);

अटल स्थिर काष्ठा snd_kcontrol_new rt715_adc23_mux =
	SOC_DAPM_ENUM_EXT("ADC 23 Mux", rt715_adc23_क्रमागत,
			rt715_sdca_mux_get, rt715_sdca_mux_put);

अटल स्थिर काष्ठा snd_kcontrol_new rt715_adc24_mux =
	SOC_DAPM_ENUM_EXT("ADC 24 Mux", rt715_adc24_क्रमागत,
			rt715_sdca_mux_get, rt715_sdca_mux_put);

अटल स्थिर काष्ठा snd_kcontrol_new rt715_adc25_mux =
	SOC_DAPM_ENUM_EXT("ADC 25 Mux", rt715_adc25_क्रमागत,
			rt715_sdca_mux_get, rt715_sdca_mux_put);

अटल पूर्णांक rt715_sdca_pde23_24_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	काष्ठा rt715_sdca_priv *rt715 = snd_soc_component_get_drvdata(component);

	चयन (event) अणु
	हाल SND_SOC_DAPM_POST_PMU:
		regmap_ग_लिखो(rt715->regmap,
			SDW_SDCA_CTL(FUN_MIC_ARRAY, RT715_SDCA_CREQ_POW_EN,
				RT715_SDCA_REQ_POW_CTRL,
				CH_00), 0x00);
		अवरोध;
	हाल SND_SOC_DAPM_PRE_PMD:
		regmap_ग_लिखो(rt715->regmap,
			SDW_SDCA_CTL(FUN_MIC_ARRAY, RT715_SDCA_CREQ_POW_EN,
				RT715_SDCA_REQ_POW_CTRL,
				CH_00), 0x03);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget rt715_sdca_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_INPUT("DMIC1"),
	SND_SOC_DAPM_INPUT("DMIC2"),
	SND_SOC_DAPM_INPUT("DMIC3"),
	SND_SOC_DAPM_INPUT("DMIC4"),
	SND_SOC_DAPM_INPUT("MIC1"),
	SND_SOC_DAPM_INPUT("MIC2"),
	SND_SOC_DAPM_INPUT("LINE1"),
	SND_SOC_DAPM_INPUT("LINE2"),

	SND_SOC_DAPM_SUPPLY("PDE23_24", SND_SOC_NOPM, 0, 0,
		rt715_sdca_pde23_24_event,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),

	SND_SOC_DAPM_ADC("ADC 07", शून्य, SND_SOC_NOPM, 4, 0),
	SND_SOC_DAPM_ADC("ADC 08", शून्य, SND_SOC_NOPM, 4, 0),
	SND_SOC_DAPM_ADC("ADC 09", शून्य, SND_SOC_NOPM, 4, 0),
	SND_SOC_DAPM_ADC("ADC 27", शून्य, SND_SOC_NOPM, 4, 0),
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

अटल स्थिर काष्ठा snd_soc_dapm_route rt715_sdca_audio_map[] = अणु
	अणु"DP6TX", शून्य, "ADC 09"पूर्ण,
	अणु"DP6TX", शून्य, "ADC 08"पूर्ण,
	अणु"DP4TX", शून्य, "ADC 07"पूर्ण,
	अणु"DP4TX", शून्य, "ADC 27"पूर्ण,
	अणु"DP4TX", शून्य, "ADC 09"पूर्ण,
	अणु"DP4TX", शून्य, "ADC 08"पूर्ण,

	अणु"LINE1", शून्य, "PDE23_24"पूर्ण,
	अणु"LINE2", शून्य, "PDE23_24"पूर्ण,
	अणु"MIC1", शून्य, "PDE23_24"पूर्ण,
	अणु"MIC2", शून्य, "PDE23_24"पूर्ण,
	अणु"DMIC1", शून्य, "PDE23_24"पूर्ण,
	अणु"DMIC2", शून्य, "PDE23_24"पूर्ण,
	अणु"DMIC3", शून्य, "PDE23_24"पूर्ण,
	अणु"DMIC4", शून्य, "PDE23_24"पूर्ण,

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

अटल स्थिर काष्ठा snd_soc_component_driver soc_codec_dev_rt715_sdca = अणु
	.controls = rt715_sdca_snd_controls,
	.num_controls = ARRAY_SIZE(rt715_sdca_snd_controls),
	.dapm_widमाला_लो = rt715_sdca_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(rt715_sdca_dapm_widमाला_लो),
	.dapm_routes = rt715_sdca_audio_map,
	.num_dapm_routes = ARRAY_SIZE(rt715_sdca_audio_map),
पूर्ण;

अटल पूर्णांक rt715_sdca_set_sdw_stream(काष्ठा snd_soc_dai *dai, व्योम *sdw_stream,
				पूर्णांक direction)
अणु
	काष्ठा rt715_sdw_stream_data *stream;

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

अटल व्योम rt715_sdca_shutकरोwn(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_soc_dai *dai)

अणु
	काष्ठा rt715_sdw_stream_data *stream;

	stream = snd_soc_dai_get_dma_data(dai, substream);
	अगर (!stream)
		वापस;

	snd_soc_dai_set_dma_data(dai, substream, शून्य);
	kमुक्त(stream);
पूर्ण

अटल पूर्णांक rt715_sdca_pcm_hw_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt715_sdca_priv *rt715 = snd_soc_component_get_drvdata(component);
	काष्ठा sdw_stream_config stream_config;
	काष्ठा sdw_port_config port_config;
	क्रमागत sdw_data_direction direction;
	काष्ठा rt715_sdw_stream_data *stream;
	पूर्णांक retval, port, num_channels;
	अचिन्हित पूर्णांक val;

	stream = snd_soc_dai_get_dma_data(dai, substream);

	अगर (!stream)
		वापस -EINVAL;

	अगर (!rt715->slave)
		वापस -EINVAL;

	चयन (dai->id) अणु
	हाल RT715_AIF1:
		direction = SDW_DATA_सूची_TX;
		port = 6;
		rt715_sdca_index_ग_लिखो(rt715, RT715_VENDOR_REG, RT715_SDW_INPUT_SEL,
			0xa500);
		अवरोध;
	हाल RT715_AIF2:
		direction = SDW_DATA_सूची_TX;
		port = 4;
		rt715_sdca_index_ग_लिखो(rt715, RT715_VENDOR_REG, RT715_SDW_INPUT_SEL,
			0xaf00);
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
	port_config.ch_mask = GENMASK(num_channels - 1, 0);
	port_config.num = port;

	retval = sdw_stream_add_slave(rt715->slave, &stream_config,
					&port_config, 1, stream->sdw_stream);
	अगर (retval) अणु
		dev_err(component->dev, "Unable to configure port, retval:%d\n",
			retval);
		वापस retval;
	पूर्ण

	चयन (params_rate(params)) अणु
	हाल 8000:
		val = 0x1;
		अवरोध;
	हाल 11025:
		val = 0x2;
		अवरोध;
	हाल 12000:
		val = 0x3;
		अवरोध;
	हाल 16000:
		val = 0x4;
		अवरोध;
	हाल 22050:
		val = 0x5;
		अवरोध;
	हाल 24000:
		val = 0x6;
		अवरोध;
	हाल 32000:
		val = 0x7;
		अवरोध;
	हाल 44100:
		val = 0x8;
		अवरोध;
	हाल 48000:
		val = 0x9;
		अवरोध;
	हाल 88200:
		val = 0xa;
		अवरोध;
	हाल 96000:
		val = 0xb;
		अवरोध;
	हाल 176400:
		val = 0xc;
		अवरोध;
	हाल 192000:
		val = 0xd;
		अवरोध;
	हाल 384000:
		val = 0xe;
		अवरोध;
	हाल 768000:
		val = 0xf;
		अवरोध;
	शेष:
		dev_err(component->dev, "Unsupported sample rate %d\n",
			params_rate(params));
		वापस -EINVAL;
	पूर्ण

	regmap_ग_लिखो(rt715->regmap,
		SDW_SDCA_CTL(FUN_MIC_ARRAY, RT715_SDCA_CS_FREQ_IND_EN,
			RT715_SDCA_FREQ_IND_CTRL, CH_00), val);

	वापस 0;
पूर्ण

अटल पूर्णांक rt715_sdca_pcm_hw_मुक्त(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा rt715_sdca_priv *rt715 = snd_soc_component_get_drvdata(component);
	काष्ठा rt715_sdw_stream_data *stream =
		snd_soc_dai_get_dma_data(dai, substream);

	अगर (!rt715->slave)
		वापस -EINVAL;

	sdw_stream_हटाओ_slave(rt715->slave, stream->sdw_stream);
	वापस 0;
पूर्ण

#घोषणा RT715_STEREO_RATES (SNDRV_PCM_RATE_44100 | SNDRV_PCM_RATE_48000)
#घोषणा RT715_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE | \
			SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S8)

अटल स्थिर काष्ठा snd_soc_dai_ops rt715_sdca_ops = अणु
	.hw_params	= rt715_sdca_pcm_hw_params,
	.hw_मुक्त	= rt715_sdca_pcm_hw_मुक्त,
	.set_sdw_stream	= rt715_sdca_set_sdw_stream,
	.shutकरोwn	= rt715_sdca_shutकरोwn,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver rt715_sdca_dai[] = अणु
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
		.ops = &rt715_sdca_ops,
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
		.ops = &rt715_sdca_ops,
	पूर्ण,
पूर्ण;

/* Bus घड़ी frequency */
#घोषणा RT715_CLK_FREQ_9600000HZ 9600000
#घोषणा RT715_CLK_FREQ_12000000HZ 12000000
#घोषणा RT715_CLK_FREQ_6000000HZ 6000000
#घोषणा RT715_CLK_FREQ_4800000HZ 4800000
#घोषणा RT715_CLK_FREQ_2400000HZ 2400000
#घोषणा RT715_CLK_FREQ_12288000HZ 12288000

पूर्णांक rt715_sdca_init(काष्ठा device *dev, काष्ठा regmap *mbq_regmap,
	काष्ठा regmap *regmap, काष्ठा sdw_slave *slave)
अणु
	काष्ठा rt715_sdca_priv *rt715;
	पूर्णांक ret;

	rt715 = devm_kzalloc(dev, माप(*rt715), GFP_KERNEL);
	अगर (!rt715)
		वापस -ENOMEM;

	dev_set_drvdata(dev, rt715);
	rt715->slave = slave;
	rt715->regmap = regmap;
	rt715->mbq_regmap = mbq_regmap;
	rt715->hw_sdw_ver = slave->id.sdw_version;
	/*
	 * Mark hw_init to false
	 * HW init will be perक्रमmed when device reports present
	 */
	rt715->hw_init = false;
	rt715->first_init = false;

	ret = devm_snd_soc_रेजिस्टर_component(dev,
			&soc_codec_dev_rt715_sdca,
			rt715_sdca_dai,
			ARRAY_SIZE(rt715_sdca_dai));

	वापस ret;
पूर्ण

पूर्णांक rt715_sdca_io_init(काष्ठा device *dev, काष्ठा sdw_slave *slave)
अणु
	काष्ठा rt715_sdca_priv *rt715 = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक hw_ver;

	अगर (rt715->hw_init)
		वापस 0;

	/*
	 * PM runसमय is only enabled when a Slave reports as Attached
	 */
	अगर (!rt715->first_init) अणु
		/* set स्वतःsuspend parameters */
		pm_runसमय_set_स्वतःsuspend_delay(&slave->dev, 3000);
		pm_runसमय_use_स्वतःsuspend(&slave->dev);

		/* update count of parent 'active' children */
		pm_runसमय_set_active(&slave->dev);

		/* make sure the device करोes not suspend immediately */
		pm_runसमय_mark_last_busy(&slave->dev);

		pm_runसमय_enable(&slave->dev);

		rt715->first_init = true;
	पूर्ण

	pm_runसमय_get_noresume(&slave->dev);

	rt715_sdca_index_पढ़ो(rt715, RT715_VENDOR_REG,
		RT715_PRODUCT_NUM, &hw_ver);
	hw_ver = hw_ver & 0x000f;

	/* set घड़ी selector = बाह्यal */
	regmap_ग_लिखो(rt715->regmap,
		SDW_SDCA_CTL(FUN_MIC_ARRAY, RT715_SDCA_CX_CLK_SEL_EN,
			RT715_SDCA_CX_CLK_SEL_CTRL, CH_00), 0x1);
	/* set GPIO_4/5/6 to be 3rd/4th DMIC usage */
	अगर (hw_ver == 0x0)
		rt715_sdca_index_update_bits(rt715, RT715_VENDOR_REG,
			RT715_AD_FUNC_EN, 0x54, 0x54);
	अन्यथा अगर (hw_ver == 0x1) अणु
		rt715_sdca_index_update_bits(rt715, RT715_VENDOR_REG,
			RT715_AD_FUNC_EN, 0x55, 0x55);
		rt715_sdca_index_update_bits(rt715, RT715_VENDOR_REG,
			RT715_REV_1, 0x40, 0x40);
	पूर्ण
	/* trigger mode = VAD enable */
	regmap_ग_लिखो(rt715->regmap,
		SDW_SDCA_CTL(FUN_MIC_ARRAY, RT715_SDCA_SMPU_TRIG_ST_EN,
			RT715_SDCA_SMPU_TRIG_EN_CTRL, CH_00), 0x2);
	/* SMPU-1 पूर्णांकerrupt enable mask */
	regmap_update_bits(rt715->regmap, RT715_INT_MASK, 0x1, 0x1);

	/* Mark Slave initialization complete */
	rt715->hw_init = true;

	pm_runसमय_mark_last_busy(&slave->dev);
	pm_runसमय_put_स्वतःsuspend(&slave->dev);

	वापस 0;
पूर्ण

MODULE_DESCRIPTION("ASoC rt715 driver SDW SDCA");
MODULE_AUTHOR("Jack Yu <jack.yu@realtek.com>");
MODULE_LICENSE("GPL v2");
