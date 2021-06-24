<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// soc-ops.c  --  Generic ASoC operations
//
// Copyright 2005 Wolfson Microelectronics PLC.
// Copyright 2005 Openedhand Ltd.
// Copyright (C) 2010 Slimlogic Ltd.
// Copyright (C) 2010 Texas Instruments Inc.
//
// Author: Liam Girdwood <lrg@slimlogic.co.uk>
//         with code, comments and ideas from :-
//         Riअक्षरd Purdie <riअक्षरd@खोलोedhand.com>

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/bitops.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/jack.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dpcm.h>
#समावेश <sound/initval.h>

/**
 * snd_soc_info_क्रमागत_द्विगुन - क्रमागतerated द्विगुन mixer info callback
 * @kcontrol: mixer control
 * @uinfo: control element inक्रमmation
 *
 * Callback to provide inक्रमmation about a द्विगुन क्रमागतerated
 * mixer control.
 *
 * Returns 0 क्रम success.
 */
पूर्णांक snd_soc_info_क्रमागत_द्विगुन(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;

	वापस snd_ctl_क्रमागत_info(uinfo, e->shअगरt_l == e->shअगरt_r ? 1 : 2,
				 e->items, e->texts);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_info_क्रमागत_द्विगुन);

/**
 * snd_soc_get_क्रमागत_द्विगुन - क्रमागतerated द्विगुन mixer get callback
 * @kcontrol: mixer control
 * @ucontrol: control element inक्रमmation
 *
 * Callback to get the value of a द्विगुन क्रमागतerated mixer.
 *
 * Returns 0 क्रम success.
 */
पूर्णांक snd_soc_get_क्रमागत_द्विगुन(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक val, item;
	अचिन्हित पूर्णांक reg_val;

	reg_val = snd_soc_component_पढ़ो(component, e->reg);
	val = (reg_val >> e->shअगरt_l) & e->mask;
	item = snd_soc_क्रमागत_val_to_item(e, val);
	ucontrol->value.क्रमागतerated.item[0] = item;
	अगर (e->shअगरt_l != e->shअगरt_r) अणु
		val = (reg_val >> e->shअगरt_r) & e->mask;
		item = snd_soc_क्रमागत_val_to_item(e, val);
		ucontrol->value.क्रमागतerated.item[1] = item;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_get_क्रमागत_द्विगुन);

/**
 * snd_soc_put_क्रमागत_द्विगुन - क्रमागतerated द्विगुन mixer put callback
 * @kcontrol: mixer control
 * @ucontrol: control element inक्रमmation
 *
 * Callback to set the value of a द्विगुन क्रमागतerated mixer.
 *
 * Returns 0 क्रम success.
 */
पूर्णांक snd_soc_put_क्रमागत_द्विगुन(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक *item = ucontrol->value.क्रमागतerated.item;
	अचिन्हित पूर्णांक val;
	अचिन्हित पूर्णांक mask;

	अगर (item[0] >= e->items)
		वापस -EINVAL;
	val = snd_soc_क्रमागत_item_to_val(e, item[0]) << e->shअगरt_l;
	mask = e->mask << e->shअगरt_l;
	अगर (e->shअगरt_l != e->shअगरt_r) अणु
		अगर (item[1] >= e->items)
			वापस -EINVAL;
		val |= snd_soc_क्रमागत_item_to_val(e, item[1]) << e->shअगरt_r;
		mask |= e->mask << e->shअगरt_r;
	पूर्ण

	वापस snd_soc_component_update_bits(component, e->reg, mask, val);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_put_क्रमागत_द्विगुन);

/**
 * snd_soc_पढ़ो_चिन्हित - Read a codec रेजिस्टर and पूर्णांकerpret as चिन्हित value
 * @component: component
 * @reg: Register to पढ़ो
 * @mask: Mask to use after shअगरting the रेजिस्टर value
 * @shअगरt: Right shअगरt of रेजिस्टर value
 * @sign_bit: Bit that describes अगर a number is negative or not.
 * @चिन्हित_val: Poपूर्णांकer to where the पढ़ो value should be stored
 *
 * This functions पढ़ोs a codec रेजिस्टर. The रेजिस्टर value is shअगरted right
 * by 'shift' bits and masked with the given 'mask'. Afterwards it translates
 * the given रेजिस्टरvalue पूर्णांकo a चिन्हित पूर्णांकeger अगर sign_bit is non-zero.
 *
 * Returns 0 on sucess, otherwise an error value
 */
अटल पूर्णांक snd_soc_पढ़ो_चिन्हित(काष्ठा snd_soc_component *component,
	अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक shअगरt,
	अचिन्हित पूर्णांक sign_bit, पूर्णांक *चिन्हित_val)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;

	val = snd_soc_component_पढ़ो(component, reg);
	val = (val >> shअगरt) & mask;

	अगर (!sign_bit) अणु
		*चिन्हित_val = val;
		वापस 0;
	पूर्ण

	/* non-negative number */
	अगर (!(val & BIT(sign_bit))) अणु
		*चिन्हित_val = val;
		वापस 0;
	पूर्ण

	ret = val;

	/*
	 * The रेजिस्टर most probably करोes not contain a full-sized पूर्णांक.
	 * Instead we have an arbitrary number of bits in a चिन्हित
	 * representation which has to be translated पूर्णांकo a full-sized पूर्णांक.
	 * This is करोne by filling up all bits above the sign-bit.
	 */
	ret |= ~((पूर्णांक)(BIT(sign_bit) - 1));

	*चिन्हित_val = ret;

	वापस 0;
पूर्ण

/**
 * snd_soc_info_volsw - single mixer info callback
 * @kcontrol: mixer control
 * @uinfo: control element inक्रमmation
 *
 * Callback to provide inक्रमmation about a single mixer control, or a द्विगुन
 * mixer control that spans 2 रेजिस्टरs.
 *
 * Returns 0 क्रम success.
 */
पूर्णांक snd_soc_info_volsw(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा soc_mixer_control *mc =
		(काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	पूर्णांक platक्रमm_max;

	अगर (!mc->platक्रमm_max)
		mc->platक्रमm_max = mc->max;
	platक्रमm_max = mc->platक्रमm_max;

	अगर (platक्रमm_max == 1 && !म_माला(kcontrol->id.name, " Volume"))
		uinfo->type = SNDRV_CTL_ELEM_TYPE_BOOLEAN;
	अन्यथा
		uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;

	uinfo->count = snd_soc_volsw_is_stereo(mc) ? 2 : 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = platक्रमm_max - mc->min;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_info_volsw);

/**
 * snd_soc_info_volsw_sx - Mixer info callback क्रम SX TLV controls
 * @kcontrol: mixer control
 * @uinfo: control element inक्रमmation
 *
 * Callback to provide inक्रमmation about a single mixer control, or a द्विगुन
 * mixer control that spans 2 रेजिस्टरs of the SX TLV type. SX TLV controls
 * have a range that represents both positive and negative values either side
 * of zero but without a sign bit.
 *
 * Returns 0 क्रम success.
 */
पूर्णांक snd_soc_info_volsw_sx(काष्ठा snd_kcontrol *kcontrol,
			  काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा soc_mixer_control *mc =
		(काष्ठा soc_mixer_control *)kcontrol->निजी_value;

	snd_soc_info_volsw(kcontrol, uinfo);
	/* Max represents the number of levels in an SX control not the
	 * maximum value, so add the minimum value back on
	 */
	uinfo->value.पूर्णांकeger.max += mc->min;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_info_volsw_sx);

/**
 * snd_soc_get_volsw - single mixer get callback
 * @kcontrol: mixer control
 * @ucontrol: control element inक्रमmation
 *
 * Callback to get the value of a single mixer control, or a द्विगुन mixer
 * control that spans 2 रेजिस्टरs.
 *
 * Returns 0 क्रम success.
 */
पूर्णांक snd_soc_get_volsw(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा soc_mixer_control *mc =
		(काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक reg = mc->reg;
	अचिन्हित पूर्णांक reg2 = mc->rreg;
	अचिन्हित पूर्णांक shअगरt = mc->shअगरt;
	अचिन्हित पूर्णांक rshअगरt = mc->rshअगरt;
	पूर्णांक max = mc->max;
	पूर्णांक min = mc->min;
	पूर्णांक sign_bit = mc->sign_bit;
	अचिन्हित पूर्णांक mask = (1 << fls(max)) - 1;
	अचिन्हित पूर्णांक invert = mc->invert;
	पूर्णांक val;
	पूर्णांक ret;

	अगर (sign_bit)
		mask = BIT(sign_bit + 1) - 1;

	ret = snd_soc_पढ़ो_चिन्हित(component, reg, mask, shअगरt, sign_bit, &val);
	अगर (ret)
		वापस ret;

	ucontrol->value.पूर्णांकeger.value[0] = val - min;
	अगर (invert)
		ucontrol->value.पूर्णांकeger.value[0] =
			max - ucontrol->value.पूर्णांकeger.value[0];

	अगर (snd_soc_volsw_is_stereo(mc)) अणु
		अगर (reg == reg2)
			ret = snd_soc_पढ़ो_चिन्हित(component, reg, mask, rshअगरt,
				sign_bit, &val);
		अन्यथा
			ret = snd_soc_पढ़ो_चिन्हित(component, reg2, mask, shअगरt,
				sign_bit, &val);
		अगर (ret)
			वापस ret;

		ucontrol->value.पूर्णांकeger.value[1] = val - min;
		अगर (invert)
			ucontrol->value.पूर्णांकeger.value[1] =
				max - ucontrol->value.पूर्णांकeger.value[1];
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_get_volsw);

/**
 * snd_soc_put_volsw - single mixer put callback
 * @kcontrol: mixer control
 * @ucontrol: control element inक्रमmation
 *
 * Callback to set the value of a single mixer control, or a द्विगुन mixer
 * control that spans 2 रेजिस्टरs.
 *
 * Returns 0 क्रम success.
 */
पूर्णांक snd_soc_put_volsw(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा soc_mixer_control *mc =
		(काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक reg = mc->reg;
	अचिन्हित पूर्णांक reg2 = mc->rreg;
	अचिन्हित पूर्णांक shअगरt = mc->shअगरt;
	अचिन्हित पूर्णांक rshअगरt = mc->rshअगरt;
	पूर्णांक max = mc->max;
	पूर्णांक min = mc->min;
	अचिन्हित पूर्णांक sign_bit = mc->sign_bit;
	अचिन्हित पूर्णांक mask = (1 << fls(max)) - 1;
	अचिन्हित पूर्णांक invert = mc->invert;
	पूर्णांक err;
	bool type_2r = false;
	अचिन्हित पूर्णांक val2 = 0;
	अचिन्हित पूर्णांक val, val_mask;

	अगर (sign_bit)
		mask = BIT(sign_bit + 1) - 1;

	val = ((ucontrol->value.पूर्णांकeger.value[0] + min) & mask);
	अगर (invert)
		val = max - val;
	val_mask = mask << shअगरt;
	val = val << shअगरt;
	अगर (snd_soc_volsw_is_stereo(mc)) अणु
		val2 = ((ucontrol->value.पूर्णांकeger.value[1] + min) & mask);
		अगर (invert)
			val2 = max - val2;
		अगर (reg == reg2) अणु
			val_mask |= mask << rshअगरt;
			val |= val2 << rshअगरt;
		पूर्ण अन्यथा अणु
			val2 = val2 << shअगरt;
			type_2r = true;
		पूर्ण
	पूर्ण
	err = snd_soc_component_update_bits(component, reg, val_mask, val);
	अगर (err < 0)
		वापस err;

	अगर (type_2r)
		err = snd_soc_component_update_bits(component, reg2, val_mask,
			val2);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_put_volsw);

/**
 * snd_soc_get_volsw_sx - single mixer get callback
 * @kcontrol: mixer control
 * @ucontrol: control element inक्रमmation
 *
 * Callback to get the value of a single mixer control, or a द्विगुन mixer
 * control that spans 2 रेजिस्टरs.
 *
 * Returns 0 क्रम success.
 */
पूर्णांक snd_soc_get_volsw_sx(काष्ठा snd_kcontrol *kcontrol,
		      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा soc_mixer_control *mc =
	    (काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक reg = mc->reg;
	अचिन्हित पूर्णांक reg2 = mc->rreg;
	अचिन्हित पूर्णांक shअगरt = mc->shअगरt;
	अचिन्हित पूर्णांक rshअगरt = mc->rshअगरt;
	पूर्णांक max = mc->max;
	पूर्णांक min = mc->min;
	अचिन्हित पूर्णांक mask = (1U << (fls(min + max) - 1)) - 1;
	अचिन्हित पूर्णांक val;

	val = snd_soc_component_पढ़ो(component, reg);
	ucontrol->value.पूर्णांकeger.value[0] = ((val >> shअगरt) - min) & mask;

	अगर (snd_soc_volsw_is_stereo(mc)) अणु
		val = snd_soc_component_पढ़ो(component, reg2);
		val = ((val >> rshअगरt) - min) & mask;
		ucontrol->value.पूर्णांकeger.value[1] = val;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_get_volsw_sx);

/**
 * snd_soc_put_volsw_sx - द्विगुन mixer set callback
 * @kcontrol: mixer control
 * @ucontrol: control element inक्रमmation
 *
 * Callback to set the value of a द्विगुन mixer control that spans 2 रेजिस्टरs.
 *
 * Returns 0 क्रम success.
 */
पूर्णांक snd_soc_put_volsw_sx(काष्ठा snd_kcontrol *kcontrol,
			 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा soc_mixer_control *mc =
	    (काष्ठा soc_mixer_control *)kcontrol->निजी_value;

	अचिन्हित पूर्णांक reg = mc->reg;
	अचिन्हित पूर्णांक reg2 = mc->rreg;
	अचिन्हित पूर्णांक shअगरt = mc->shअगरt;
	अचिन्हित पूर्णांक rshअगरt = mc->rshअगरt;
	पूर्णांक max = mc->max;
	पूर्णांक min = mc->min;
	अचिन्हित पूर्णांक mask = (1U << (fls(min + max) - 1)) - 1;
	पूर्णांक err = 0;
	अचिन्हित पूर्णांक val, val_mask, val2;

	val_mask = mask << shअगरt;
	val = (ucontrol->value.पूर्णांकeger.value[0] + min) & mask;
	val = val << shअगरt;

	err = snd_soc_component_update_bits(component, reg, val_mask, val);
	अगर (err < 0)
		वापस err;

	अगर (snd_soc_volsw_is_stereo(mc)) अणु
		val_mask = mask << rshअगरt;
		val2 = (ucontrol->value.पूर्णांकeger.value[1] + min) & mask;
		val2 = val2 << rshअगरt;

		err = snd_soc_component_update_bits(component, reg2, val_mask,
			val2);
	पूर्ण
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_put_volsw_sx);

/**
 * snd_soc_info_volsw_range - single mixer info callback with range.
 * @kcontrol: mixer control
 * @uinfo: control element inक्रमmation
 *
 * Callback to provide inक्रमmation, within a range, about a single
 * mixer control.
 *
 * वापसs 0 क्रम success.
 */
पूर्णांक snd_soc_info_volsw_range(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा soc_mixer_control *mc =
		(काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	पूर्णांक platक्रमm_max;
	पूर्णांक min = mc->min;

	अगर (!mc->platक्रमm_max)
		mc->platक्रमm_max = mc->max;
	platक्रमm_max = mc->platक्रमm_max;

	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = snd_soc_volsw_is_stereo(mc) ? 2 : 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = platक्रमm_max - min;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_info_volsw_range);

/**
 * snd_soc_put_volsw_range - single mixer put value callback with range.
 * @kcontrol: mixer control
 * @ucontrol: control element inक्रमmation
 *
 * Callback to set the value, within a range, क्रम a single mixer control.
 *
 * Returns 0 क्रम success.
 */
पूर्णांक snd_soc_put_volsw_range(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा soc_mixer_control *mc =
		(काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक reg = mc->reg;
	अचिन्हित पूर्णांक rreg = mc->rreg;
	अचिन्हित पूर्णांक shअगरt = mc->shअगरt;
	पूर्णांक min = mc->min;
	पूर्णांक max = mc->max;
	अचिन्हित पूर्णांक mask = (1 << fls(max)) - 1;
	अचिन्हित पूर्णांक invert = mc->invert;
	अचिन्हित पूर्णांक val, val_mask;
	पूर्णांक ret;

	अगर (invert)
		val = (max - ucontrol->value.पूर्णांकeger.value[0]) & mask;
	अन्यथा
		val = ((ucontrol->value.पूर्णांकeger.value[0] + min) & mask);
	val_mask = mask << shअगरt;
	val = val << shअगरt;

	ret = snd_soc_component_update_bits(component, reg, val_mask, val);
	अगर (ret < 0)
		वापस ret;

	अगर (snd_soc_volsw_is_stereo(mc)) अणु
		अगर (invert)
			val = (max - ucontrol->value.पूर्णांकeger.value[1]) & mask;
		अन्यथा
			val = ((ucontrol->value.पूर्णांकeger.value[1] + min) & mask);
		val_mask = mask << shअगरt;
		val = val << shअगरt;

		ret = snd_soc_component_update_bits(component, rreg, val_mask,
			val);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_put_volsw_range);

/**
 * snd_soc_get_volsw_range - single mixer get callback with range
 * @kcontrol: mixer control
 * @ucontrol: control element inक्रमmation
 *
 * Callback to get the value, within a range, of a single mixer control.
 *
 * Returns 0 क्रम success.
 */
पूर्णांक snd_soc_get_volsw_range(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा soc_mixer_control *mc =
		(काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक reg = mc->reg;
	अचिन्हित पूर्णांक rreg = mc->rreg;
	अचिन्हित पूर्णांक shअगरt = mc->shअगरt;
	पूर्णांक min = mc->min;
	पूर्णांक max = mc->max;
	अचिन्हित पूर्णांक mask = (1 << fls(max)) - 1;
	अचिन्हित पूर्णांक invert = mc->invert;
	अचिन्हित पूर्णांक val;

	val = snd_soc_component_पढ़ो(component, reg);
	ucontrol->value.पूर्णांकeger.value[0] = (val >> shअगरt) & mask;
	अगर (invert)
		ucontrol->value.पूर्णांकeger.value[0] =
			max - ucontrol->value.पूर्णांकeger.value[0];
	अन्यथा
		ucontrol->value.पूर्णांकeger.value[0] =
			ucontrol->value.पूर्णांकeger.value[0] - min;

	अगर (snd_soc_volsw_is_stereo(mc)) अणु
		val = snd_soc_component_पढ़ो(component, rreg);
		ucontrol->value.पूर्णांकeger.value[1] = (val >> shअगरt) & mask;
		अगर (invert)
			ucontrol->value.पूर्णांकeger.value[1] =
				max - ucontrol->value.पूर्णांकeger.value[1];
		अन्यथा
			ucontrol->value.पूर्णांकeger.value[1] =
				ucontrol->value.पूर्णांकeger.value[1] - min;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_get_volsw_range);

/**
 * snd_soc_limit_volume - Set new limit to an existing volume control.
 *
 * @card: where to look क्रम the control
 * @name: Name of the control
 * @max: new maximum limit
 *
 * Return 0 क्रम success, अन्यथा error.
 */
पूर्णांक snd_soc_limit_volume(काष्ठा snd_soc_card *card,
	स्थिर अक्षर *name, पूर्णांक max)
अणु
	काष्ठा snd_kcontrol *kctl;
	काष्ठा soc_mixer_control *mc;
	पूर्णांक ret = -EINVAL;

	/* Sanity check क्रम name and max */
	अगर (unlikely(!name || max <= 0))
		वापस -EINVAL;

	kctl = snd_soc_card_get_kcontrol(card, name);
	अगर (kctl) अणु
		mc = (काष्ठा soc_mixer_control *)kctl->निजी_value;
		अगर (max <= mc->max) अणु
			mc->platक्रमm_max = max;
			ret = 0;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_limit_volume);

पूर्णांक snd_soc_bytes_info(काष्ठा snd_kcontrol *kcontrol,
		       काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा soc_bytes *params = (व्योम *)kcontrol->निजी_value;

	uinfo->type = SNDRV_CTL_ELEM_TYPE_BYTES;
	uinfo->count = params->num_regs * component->val_bytes;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_bytes_info);

पूर्णांक snd_soc_bytes_get(काष्ठा snd_kcontrol *kcontrol,
		      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा soc_bytes *params = (व्योम *)kcontrol->निजी_value;
	पूर्णांक ret;

	अगर (component->regmap)
		ret = regmap_raw_पढ़ो(component->regmap, params->base,
				      ucontrol->value.bytes.data,
				      params->num_regs * component->val_bytes);
	अन्यथा
		ret = -EINVAL;

	/* Hide any masked bytes to ensure consistent data reporting */
	अगर (ret == 0 && params->mask) अणु
		चयन (component->val_bytes) अणु
		हाल 1:
			ucontrol->value.bytes.data[0] &= ~params->mask;
			अवरोध;
		हाल 2:
			((u16 *)(&ucontrol->value.bytes.data))[0]
				&= cpu_to_be16(~params->mask);
			अवरोध;
		हाल 4:
			((u32 *)(&ucontrol->value.bytes.data))[0]
				&= cpu_to_be32(~params->mask);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_bytes_get);

पूर्णांक snd_soc_bytes_put(काष्ठा snd_kcontrol *kcontrol,
		      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा soc_bytes *params = (व्योम *)kcontrol->निजी_value;
	पूर्णांक ret, len;
	अचिन्हित पूर्णांक val, mask;
	व्योम *data;

	अगर (!component->regmap || !params->num_regs)
		वापस -EINVAL;

	len = params->num_regs * component->val_bytes;

	data = kmemdup(ucontrol->value.bytes.data, len, GFP_KERNEL | GFP_DMA);
	अगर (!data)
		वापस -ENOMEM;

	/*
	 * If we've got a mask then we need to preserve the रेजिस्टर
	 * bits.  We shouldn't modअगरy the incoming data so take a
	 * copy.
	 */
	अगर (params->mask) अणु
		ret = regmap_पढ़ो(component->regmap, params->base, &val);
		अगर (ret != 0)
			जाओ out;

		val &= params->mask;

		चयन (component->val_bytes) अणु
		हाल 1:
			((u8 *)data)[0] &= ~params->mask;
			((u8 *)data)[0] |= val;
			अवरोध;
		हाल 2:
			mask = ~params->mask;
			ret = regmap_parse_val(component->regmap,
							&mask, &mask);
			अगर (ret != 0)
				जाओ out;

			((u16 *)data)[0] &= mask;

			ret = regmap_parse_val(component->regmap,
							&val, &val);
			अगर (ret != 0)
				जाओ out;

			((u16 *)data)[0] |= val;
			अवरोध;
		हाल 4:
			mask = ~params->mask;
			ret = regmap_parse_val(component->regmap,
							&mask, &mask);
			अगर (ret != 0)
				जाओ out;

			((u32 *)data)[0] &= mask;

			ret = regmap_parse_val(component->regmap,
							&val, &val);
			अगर (ret != 0)
				जाओ out;

			((u32 *)data)[0] |= val;
			अवरोध;
		शेष:
			ret = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

	ret = regmap_raw_ग_लिखो(component->regmap, params->base,
			       data, len);

out:
	kमुक्त(data);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_bytes_put);

पूर्णांक snd_soc_bytes_info_ext(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_info *ucontrol)
अणु
	काष्ठा soc_bytes_ext *params = (व्योम *)kcontrol->निजी_value;

	ucontrol->type = SNDRV_CTL_ELEM_TYPE_BYTES;
	ucontrol->count = params->max;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_bytes_info_ext);

पूर्णांक snd_soc_bytes_tlv_callback(काष्ठा snd_kcontrol *kcontrol, पूर्णांक op_flag,
				अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक __user *tlv)
अणु
	काष्ठा soc_bytes_ext *params = (व्योम *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक count = size < params->max ? size : params->max;
	पूर्णांक ret = -ENXIO;

	चयन (op_flag) अणु
	हाल SNDRV_CTL_TLV_OP_READ:
		अगर (params->get)
			ret = params->get(kcontrol, tlv, count);
		अवरोध;
	हाल SNDRV_CTL_TLV_OP_WRITE:
		अगर (params->put)
			ret = params->put(kcontrol, tlv, count);
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_bytes_tlv_callback);

/**
 * snd_soc_info_xr_sx - चिन्हित multi रेजिस्टर info callback
 * @kcontrol: mreg control
 * @uinfo: control element inक्रमmation
 *
 * Callback to provide inक्रमmation of a control that can
 * span multiple codec रेजिस्टरs which together
 * क्रमms a single चिन्हित value in a MSB/LSB manner.
 *
 * Returns 0 क्रम success.
 */
पूर्णांक snd_soc_info_xr_sx(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा soc_mreg_control *mc =
		(काष्ठा soc_mreg_control *)kcontrol->निजी_value;
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = mc->min;
	uinfo->value.पूर्णांकeger.max = mc->max;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_info_xr_sx);

/**
 * snd_soc_get_xr_sx - चिन्हित multi रेजिस्टर get callback
 * @kcontrol: mreg control
 * @ucontrol: control element inक्रमmation
 *
 * Callback to get the value of a control that can span
 * multiple codec रेजिस्टरs which together क्रमms a single
 * चिन्हित value in a MSB/LSB manner. The control supports
 * specअगरying total no of bits used to allow क्रम bitfields
 * across the multiple codec रेजिस्टरs.
 *
 * Returns 0 क्रम success.
 */
पूर्णांक snd_soc_get_xr_sx(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा soc_mreg_control *mc =
		(काष्ठा soc_mreg_control *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक regbase = mc->regbase;
	अचिन्हित पूर्णांक regcount = mc->regcount;
	अचिन्हित पूर्णांक regwshअगरt = component->val_bytes * BITS_PER_BYTE;
	अचिन्हित पूर्णांक regwmask = (1UL<<regwshअगरt)-1;
	अचिन्हित पूर्णांक invert = mc->invert;
	अचिन्हित दीर्घ mask = (1UL<<mc->nbits)-1;
	दीर्घ min = mc->min;
	दीर्घ max = mc->max;
	दीर्घ val = 0;
	अचिन्हित पूर्णांक regval;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < regcount; i++) अणु
		regval = snd_soc_component_पढ़ो(component, regbase+i);
		val |= (regval & regwmask) << (regwshअगरt*(regcount-i-1));
	पूर्ण
	val &= mask;
	अगर (min < 0 && val > max)
		val |= ~mask;
	अगर (invert)
		val = max - val;
	ucontrol->value.पूर्णांकeger.value[0] = val;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_get_xr_sx);

/**
 * snd_soc_put_xr_sx - चिन्हित multi रेजिस्टर get callback
 * @kcontrol: mreg control
 * @ucontrol: control element inक्रमmation
 *
 * Callback to set the value of a control that can span
 * multiple codec रेजिस्टरs which together क्रमms a single
 * चिन्हित value in a MSB/LSB manner. The control supports
 * specअगरying total no of bits used to allow क्रम bitfields
 * across the multiple codec रेजिस्टरs.
 *
 * Returns 0 क्रम success.
 */
पूर्णांक snd_soc_put_xr_sx(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा soc_mreg_control *mc =
		(काष्ठा soc_mreg_control *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक regbase = mc->regbase;
	अचिन्हित पूर्णांक regcount = mc->regcount;
	अचिन्हित पूर्णांक regwshअगरt = component->val_bytes * BITS_PER_BYTE;
	अचिन्हित पूर्णांक regwmask = (1UL<<regwshअगरt)-1;
	अचिन्हित पूर्णांक invert = mc->invert;
	अचिन्हित दीर्घ mask = (1UL<<mc->nbits)-1;
	दीर्घ max = mc->max;
	दीर्घ val = ucontrol->value.पूर्णांकeger.value[0];
	अचिन्हित पूर्णांक i, regval, regmask;
	पूर्णांक err;

	अगर (invert)
		val = max - val;
	val &= mask;
	क्रम (i = 0; i < regcount; i++) अणु
		regval = (val >> (regwshअगरt*(regcount-i-1))) & regwmask;
		regmask = (mask >> (regwshअगरt*(regcount-i-1))) & regwmask;
		err = snd_soc_component_update_bits(component, regbase+i,
				regmask, regval);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_put_xr_sx);

/**
 * snd_soc_get_strobe - strobe get callback
 * @kcontrol: mixer control
 * @ucontrol: control element inक्रमmation
 *
 * Callback get the value of a strobe mixer control.
 *
 * Returns 0 क्रम success.
 */
पूर्णांक snd_soc_get_strobe(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा soc_mixer_control *mc =
		(काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक reg = mc->reg;
	अचिन्हित पूर्णांक shअगरt = mc->shअगरt;
	अचिन्हित पूर्णांक mask = 1 << shअगरt;
	अचिन्हित पूर्णांक invert = mc->invert != 0;
	अचिन्हित पूर्णांक val;

	val = snd_soc_component_पढ़ो(component, reg);
	val &= mask;

	अगर (shअगरt != 0 && val != 0)
		val = val >> shअगरt;
	ucontrol->value.क्रमागतerated.item[0] = val ^ invert;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_get_strobe);

/**
 * snd_soc_put_strobe - strobe put callback
 * @kcontrol: mixer control
 * @ucontrol: control element inक्रमmation
 *
 * Callback strobe a रेजिस्टर bit to high then low (or the inverse)
 * in one pass of a single mixer क्रमागत control.
 *
 * Returns 1 क्रम success.
 */
पूर्णांक snd_soc_put_strobe(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_kcontrol_chip(kcontrol);
	काष्ठा soc_mixer_control *mc =
		(काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक reg = mc->reg;
	अचिन्हित पूर्णांक shअगरt = mc->shअगरt;
	अचिन्हित पूर्णांक mask = 1 << shअगरt;
	अचिन्हित पूर्णांक invert = mc->invert != 0;
	अचिन्हित पूर्णांक strobe = ucontrol->value.क्रमागतerated.item[0] != 0;
	अचिन्हित पूर्णांक val1 = (strobe ^ invert) ? mask : 0;
	अचिन्हित पूर्णांक val2 = (strobe ^ invert) ? 0 : mask;
	पूर्णांक err;

	err = snd_soc_component_update_bits(component, reg, mask, val1);
	अगर (err < 0)
		वापस err;

	वापस snd_soc_component_update_bits(component, reg, mask, val2);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_put_strobe);
