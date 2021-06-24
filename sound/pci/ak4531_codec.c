<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *  Universal routines क्रम AK4531 codec
 */

#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>
#समावेश <linux/module.h>

#समावेश <sound/core.h>
#समावेश <sound/ak4531_codec.h>
#समावेश <sound/tlv.h>

/*
MODULE_AUTHOR("Jaroslav Kysela <perex@perex.cz>");
MODULE_DESCRIPTION("Universal routines for AK4531 codec");
MODULE_LICENSE("GPL");
*/

अटल व्योम snd_ak4531_proc_init(काष्ठा snd_card *card, काष्ठा snd_ak4531 *ak4531);

/*
 *
 */
 
#अगर 0

अटल व्योम snd_ak4531_dump(काष्ठा snd_ak4531 *ak4531)
अणु
	पूर्णांक idx;
	
	क्रम (idx = 0; idx < 0x19; idx++)
		prपूर्णांकk(KERN_DEBUG "ak4531 0x%x: 0x%x\n",
		       idx, ak4531->regs[idx]);
पूर्ण

#पूर्ण_अगर

/*
 *
 */

#घोषणा AK4531_SINGLE(xname, xindex, reg, shअगरt, mask, invert) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xindex, \
  .info = snd_ak4531_info_single, \
  .get = snd_ak4531_get_single, .put = snd_ak4531_put_single, \
  .निजी_value = reg | (shअगरt << 16) | (mask << 24) | (invert << 22) पूर्ण
#घोषणा AK4531_SINGLE_TLV(xname, xindex, reg, shअगरt, mask, invert, xtlv)    \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
  .access = SNDRV_CTL_ELEM_ACCESS_READWRITE | SNDRV_CTL_ELEM_ACCESS_TLV_READ, \
  .name = xname, .index = xindex, \
  .info = snd_ak4531_info_single, \
  .get = snd_ak4531_get_single, .put = snd_ak4531_put_single, \
  .निजी_value = reg | (shअगरt << 16) | (mask << 24) | (invert << 22), \
  .tlv = अणु .p = (xtlv) पूर्ण पूर्ण

अटल पूर्णांक snd_ak4531_info_single(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	पूर्णांक mask = (kcontrol->निजी_value >> 24) & 0xff;

	uinfo->type = mask == 1 ? SNDRV_CTL_ELEM_TYPE_BOOLEAN : SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = mask;
	वापस 0;
पूर्ण
 
अटल पूर्णांक snd_ak4531_get_single(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ak4531 *ak4531 = snd_kcontrol_chip(kcontrol);
	पूर्णांक reg = kcontrol->निजी_value & 0xff;
	पूर्णांक shअगरt = (kcontrol->निजी_value >> 16) & 0x07;
	पूर्णांक mask = (kcontrol->निजी_value >> 24) & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 22) & 1;
	पूर्णांक val;

	mutex_lock(&ak4531->reg_mutex);
	val = (ak4531->regs[reg] >> shअगरt) & mask;
	mutex_unlock(&ak4531->reg_mutex);
	अगर (invert) अणु
		val = mask - val;
	पूर्ण
	ucontrol->value.पूर्णांकeger.value[0] = val;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ak4531_put_single(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ak4531 *ak4531 = snd_kcontrol_chip(kcontrol);
	पूर्णांक reg = kcontrol->निजी_value & 0xff;
	पूर्णांक shअगरt = (kcontrol->निजी_value >> 16) & 0x07;
	पूर्णांक mask = (kcontrol->निजी_value >> 24) & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 22) & 1;
	पूर्णांक change;
	पूर्णांक val;

	val = ucontrol->value.पूर्णांकeger.value[0] & mask;
	अगर (invert) अणु
		val = mask - val;
	पूर्ण
	val <<= shअगरt;
	mutex_lock(&ak4531->reg_mutex);
	val = (ak4531->regs[reg] & ~(mask << shअगरt)) | val;
	change = val != ak4531->regs[reg];
	ak4531->ग_लिखो(ak4531, reg, ak4531->regs[reg] = val);
	mutex_unlock(&ak4531->reg_mutex);
	वापस change;
पूर्ण

#घोषणा AK4531_DOUBLE(xname, xindex, left_reg, right_reg, left_shअगरt, right_shअगरt, mask, invert) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xindex, \
  .info = snd_ak4531_info_द्विगुन, \
  .get = snd_ak4531_get_द्विगुन, .put = snd_ak4531_put_द्विगुन, \
  .निजी_value = left_reg | (right_reg << 8) | (left_shअगरt << 16) | (right_shअगरt << 19) | (mask << 24) | (invert << 22) पूर्ण
#घोषणा AK4531_DOUBLE_TLV(xname, xindex, left_reg, right_reg, left_shअगरt, right_shअगरt, mask, invert, xtlv) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
  .access = SNDRV_CTL_ELEM_ACCESS_READWRITE | SNDRV_CTL_ELEM_ACCESS_TLV_READ, \
  .name = xname, .index = xindex, \
  .info = snd_ak4531_info_द्विगुन, \
  .get = snd_ak4531_get_द्विगुन, .put = snd_ak4531_put_द्विगुन, \
  .निजी_value = left_reg | (right_reg << 8) | (left_shअगरt << 16) | (right_shअगरt << 19) | (mask << 24) | (invert << 22), \
  .tlv = अणु .p = (xtlv) पूर्ण पूर्ण

अटल पूर्णांक snd_ak4531_info_द्विगुन(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	पूर्णांक mask = (kcontrol->निजी_value >> 24) & 0xff;

	uinfo->type = mask == 1 ? SNDRV_CTL_ELEM_TYPE_BOOLEAN : SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = mask;
	वापस 0;
पूर्ण
 
अटल पूर्णांक snd_ak4531_get_द्विगुन(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ak4531 *ak4531 = snd_kcontrol_chip(kcontrol);
	पूर्णांक left_reg = kcontrol->निजी_value & 0xff;
	पूर्णांक right_reg = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक left_shअगरt = (kcontrol->निजी_value >> 16) & 0x07;
	पूर्णांक right_shअगरt = (kcontrol->निजी_value >> 19) & 0x07;
	पूर्णांक mask = (kcontrol->निजी_value >> 24) & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 22) & 1;
	पूर्णांक left, right;

	mutex_lock(&ak4531->reg_mutex);
	left = (ak4531->regs[left_reg] >> left_shअगरt) & mask;
	right = (ak4531->regs[right_reg] >> right_shअगरt) & mask;
	mutex_unlock(&ak4531->reg_mutex);
	अगर (invert) अणु
		left = mask - left;
		right = mask - right;
	पूर्ण
	ucontrol->value.पूर्णांकeger.value[0] = left;
	ucontrol->value.पूर्णांकeger.value[1] = right;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ak4531_put_द्विगुन(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ak4531 *ak4531 = snd_kcontrol_chip(kcontrol);
	पूर्णांक left_reg = kcontrol->निजी_value & 0xff;
	पूर्णांक right_reg = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक left_shअगरt = (kcontrol->निजी_value >> 16) & 0x07;
	पूर्णांक right_shअगरt = (kcontrol->निजी_value >> 19) & 0x07;
	पूर्णांक mask = (kcontrol->निजी_value >> 24) & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 22) & 1;
	पूर्णांक change;
	पूर्णांक left, right;

	left = ucontrol->value.पूर्णांकeger.value[0] & mask;
	right = ucontrol->value.पूर्णांकeger.value[1] & mask;
	अगर (invert) अणु
		left = mask - left;
		right = mask - right;
	पूर्ण
	left <<= left_shअगरt;
	right <<= right_shअगरt;
	mutex_lock(&ak4531->reg_mutex);
	अगर (left_reg == right_reg) अणु
		left = (ak4531->regs[left_reg] & ~((mask << left_shअगरt) | (mask << right_shअगरt))) | left | right;
		change = left != ak4531->regs[left_reg];
		ak4531->ग_लिखो(ak4531, left_reg, ak4531->regs[left_reg] = left);
	पूर्ण अन्यथा अणु
		left = (ak4531->regs[left_reg] & ~(mask << left_shअगरt)) | left;
		right = (ak4531->regs[right_reg] & ~(mask << right_shअगरt)) | right;
		change = left != ak4531->regs[left_reg] || right != ak4531->regs[right_reg];
		ak4531->ग_लिखो(ak4531, left_reg, ak4531->regs[left_reg] = left);
		ak4531->ग_लिखो(ak4531, right_reg, ak4531->regs[right_reg] = right);
	पूर्ण
	mutex_unlock(&ak4531->reg_mutex);
	वापस change;
पूर्ण

#घोषणा AK4531_INPUT_SW(xname, xindex, reg1, reg2, left_shअगरt, right_shअगरt) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xindex, \
  .info = snd_ak4531_info_input_sw, \
  .get = snd_ak4531_get_input_sw, .put = snd_ak4531_put_input_sw, \
  .निजी_value = reg1 | (reg2 << 8) | (left_shअगरt << 16) | (right_shअगरt << 24) पूर्ण

अटल पूर्णांक snd_ak4531_info_input_sw(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_BOOLEAN;
	uinfo->count = 4;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 1;
	वापस 0;
पूर्ण
 
अटल पूर्णांक snd_ak4531_get_input_sw(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ak4531 *ak4531 = snd_kcontrol_chip(kcontrol);
	पूर्णांक reg1 = kcontrol->निजी_value & 0xff;
	पूर्णांक reg2 = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक left_shअगरt = (kcontrol->निजी_value >> 16) & 0x0f;
	पूर्णांक right_shअगरt = (kcontrol->निजी_value >> 24) & 0x0f;

	mutex_lock(&ak4531->reg_mutex);
	ucontrol->value.पूर्णांकeger.value[0] = (ak4531->regs[reg1] >> left_shअगरt) & 1;
	ucontrol->value.पूर्णांकeger.value[1] = (ak4531->regs[reg2] >> left_shअगरt) & 1;
	ucontrol->value.पूर्णांकeger.value[2] = (ak4531->regs[reg1] >> right_shअगरt) & 1;
	ucontrol->value.पूर्णांकeger.value[3] = (ak4531->regs[reg2] >> right_shअगरt) & 1;
	mutex_unlock(&ak4531->reg_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ak4531_put_input_sw(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ak4531 *ak4531 = snd_kcontrol_chip(kcontrol);
	पूर्णांक reg1 = kcontrol->निजी_value & 0xff;
	पूर्णांक reg2 = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक left_shअगरt = (kcontrol->निजी_value >> 16) & 0x0f;
	पूर्णांक right_shअगरt = (kcontrol->निजी_value >> 24) & 0x0f;
	पूर्णांक change;
	पूर्णांक val1, val2;

	mutex_lock(&ak4531->reg_mutex);
	val1 = ak4531->regs[reg1] & ~((1 << left_shअगरt) | (1 << right_shअगरt));
	val2 = ak4531->regs[reg2] & ~((1 << left_shअगरt) | (1 << right_shअगरt));
	val1 |= (ucontrol->value.पूर्णांकeger.value[0] & 1) << left_shअगरt;
	val2 |= (ucontrol->value.पूर्णांकeger.value[1] & 1) << left_shअगरt;
	val1 |= (ucontrol->value.पूर्णांकeger.value[2] & 1) << right_shअगरt;
	val2 |= (ucontrol->value.पूर्णांकeger.value[3] & 1) << right_shअगरt;
	change = val1 != ak4531->regs[reg1] || val2 != ak4531->regs[reg2];
	ak4531->ग_लिखो(ak4531, reg1, ak4531->regs[reg1] = val1);
	ak4531->ग_लिखो(ak4531, reg2, ak4531->regs[reg2] = val2);
	mutex_unlock(&ak4531->reg_mutex);
	वापस change;
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_master, -6200, 200, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_mono, -2800, 400, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_input, -5000, 200, 0);

अटल स्थिर काष्ठा snd_kcontrol_new snd_ak4531_controls[] = अणु

AK4531_DOUBLE_TLV("Master Playback Switch", 0,
		  AK4531_LMASTER, AK4531_RMASTER, 7, 7, 1, 1,
		  db_scale_master),
AK4531_DOUBLE("Master Playback Volume", 0, AK4531_LMASTER, AK4531_RMASTER, 0, 0, 0x1f, 1),

AK4531_SINGLE_TLV("Master Mono Playback Switch", 0, AK4531_MONO_OUT, 7, 1, 1,
		  db_scale_mono),
AK4531_SINGLE("Master Mono Playback Volume", 0, AK4531_MONO_OUT, 0, 0x07, 1),

AK4531_DOUBLE("PCM Switch", 0, AK4531_LVOICE, AK4531_RVOICE, 7, 7, 1, 1),
AK4531_DOUBLE_TLV("PCM Volume", 0, AK4531_LVOICE, AK4531_RVOICE, 0, 0, 0x1f, 1,
		  db_scale_input),
AK4531_DOUBLE("PCM Playback Switch", 0, AK4531_OUT_SW2, AK4531_OUT_SW2, 3, 2, 1, 0),
AK4531_DOUBLE("PCM Capture Switch", 0, AK4531_LIN_SW2, AK4531_RIN_SW2, 2, 2, 1, 0),

AK4531_DOUBLE("PCM Switch", 1, AK4531_LFM, AK4531_RFM, 7, 7, 1, 1),
AK4531_DOUBLE_TLV("PCM Volume", 1, AK4531_LFM, AK4531_RFM, 0, 0, 0x1f, 1,
		  db_scale_input),
AK4531_DOUBLE("PCM Playback Switch", 1, AK4531_OUT_SW1, AK4531_OUT_SW1, 6, 5, 1, 0),
AK4531_INPUT_SW("PCM Capture Route", 1, AK4531_LIN_SW1, AK4531_RIN_SW1, 6, 5),

AK4531_DOUBLE("CD Switch", 0, AK4531_LCD, AK4531_RCD, 7, 7, 1, 1),
AK4531_DOUBLE_TLV("CD Volume", 0, AK4531_LCD, AK4531_RCD, 0, 0, 0x1f, 1,
		  db_scale_input),
AK4531_DOUBLE("CD Playback Switch", 0, AK4531_OUT_SW1, AK4531_OUT_SW1, 2, 1, 1, 0),
AK4531_INPUT_SW("CD Capture Route", 0, AK4531_LIN_SW1, AK4531_RIN_SW1, 2, 1),

AK4531_DOUBLE("Line Switch", 0, AK4531_LLINE, AK4531_RLINE, 7, 7, 1, 1),
AK4531_DOUBLE_TLV("Line Volume", 0, AK4531_LLINE, AK4531_RLINE, 0, 0, 0x1f, 1,
		  db_scale_input),
AK4531_DOUBLE("Line Playback Switch", 0, AK4531_OUT_SW1, AK4531_OUT_SW1, 4, 3, 1, 0),
AK4531_INPUT_SW("Line Capture Route", 0, AK4531_LIN_SW1, AK4531_RIN_SW1, 4, 3),

AK4531_DOUBLE("Aux Switch", 0, AK4531_LAUXA, AK4531_RAUXA, 7, 7, 1, 1),
AK4531_DOUBLE_TLV("Aux Volume", 0, AK4531_LAUXA, AK4531_RAUXA, 0, 0, 0x1f, 1,
		  db_scale_input),
AK4531_DOUBLE("Aux Playback Switch", 0, AK4531_OUT_SW2, AK4531_OUT_SW2, 5, 4, 1, 0),
AK4531_INPUT_SW("Aux Capture Route", 0, AK4531_LIN_SW2, AK4531_RIN_SW2, 4, 3),

AK4531_SINGLE("Mono Switch", 0, AK4531_MONO1, 7, 1, 1),
AK4531_SINGLE_TLV("Mono Volume", 0, AK4531_MONO1, 0, 0x1f, 1, db_scale_input),
AK4531_SINGLE("Mono Playback Switch", 0, AK4531_OUT_SW2, 0, 1, 0),
AK4531_DOUBLE("Mono Capture Switch", 0, AK4531_LIN_SW2, AK4531_RIN_SW2, 0, 0, 1, 0),

AK4531_SINGLE("Mono Switch", 1, AK4531_MONO2, 7, 1, 1),
AK4531_SINGLE_TLV("Mono Volume", 1, AK4531_MONO2, 0, 0x1f, 1, db_scale_input),
AK4531_SINGLE("Mono Playback Switch", 1, AK4531_OUT_SW2, 1, 1, 0),
AK4531_DOUBLE("Mono Capture Switch", 1, AK4531_LIN_SW2, AK4531_RIN_SW2, 1, 1, 1, 0),

AK4531_SINGLE_TLV("Mic Volume", 0, AK4531_MIC, 0, 0x1f, 1, db_scale_input),
AK4531_SINGLE("Mic Switch", 0, AK4531_MIC, 7, 1, 1),
AK4531_SINGLE("Mic Playback Switch", 0, AK4531_OUT_SW1, 0, 1, 0),
AK4531_DOUBLE("Mic Capture Switch", 0, AK4531_LIN_SW1, AK4531_RIN_SW1, 0, 0, 1, 0),

AK4531_DOUBLE("Mic Bypass Capture Switch", 0, AK4531_LIN_SW2, AK4531_RIN_SW2, 7, 7, 1, 0),
AK4531_DOUBLE("Mono1 Bypass Capture Switch", 0, AK4531_LIN_SW2, AK4531_RIN_SW2, 6, 6, 1, 0),
AK4531_DOUBLE("Mono2 Bypass Capture Switch", 0, AK4531_LIN_SW2, AK4531_RIN_SW2, 5, 5, 1, 0),

AK4531_SINGLE("AD Input Select", 0, AK4531_AD_IN, 0, 1, 0),
AK4531_SINGLE("Mic Boost (+30dB)", 0, AK4531_MIC_GAIN, 0, 1, 0)
पूर्ण;

अटल पूर्णांक snd_ak4531_मुक्त(काष्ठा snd_ak4531 *ak4531)
अणु
	अगर (ak4531) अणु
		अगर (ak4531->निजी_मुक्त)
			ak4531->निजी_मुक्त(ak4531);
		kमुक्त(ak4531);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ak4531_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा snd_ak4531 *ak4531 = device->device_data;
	वापस snd_ak4531_मुक्त(ak4531);
पूर्ण

अटल स्थिर u8 snd_ak4531_initial_map[0x19 + 1] = अणु
	0x9f,		/* 00: Master Volume Lch */
	0x9f,		/* 01: Master Volume Rch */
	0x9f,		/* 02: Voice Volume Lch */
	0x9f,		/* 03: Voice Volume Rch */
	0x9f,		/* 04: FM Volume Lch */
	0x9f,		/* 05: FM Volume Rch */
	0x9f,		/* 06: CD Audio Volume Lch */
	0x9f,		/* 07: CD Audio Volume Rch */
	0x9f,		/* 08: Line Volume Lch */
	0x9f,		/* 09: Line Volume Rch */
	0x9f,		/* 0a: Aux Volume Lch */
	0x9f,		/* 0b: Aux Volume Rch */
	0x9f,		/* 0c: Mono1 Volume */
	0x9f,		/* 0d: Mono2 Volume */
	0x9f,		/* 0e: Mic Volume */
	0x87,		/* 0f: Mono-out Volume */
	0x00,		/* 10: Output Mixer SW1 */
	0x00,		/* 11: Output Mixer SW2 */
	0x00,		/* 12: Lch Input Mixer SW1 */
	0x00,		/* 13: Rch Input Mixer SW1 */
	0x00,		/* 14: Lch Input Mixer SW2 */
	0x00,		/* 15: Rch Input Mixer SW2 */
	0x00,		/* 16: Reset & Power Down */
	0x00,		/* 17: Clock Select */
	0x00,		/* 18: AD Input Select */
	0x01		/* 19: Mic Amp Setup */
पूर्ण;

पूर्णांक snd_ak4531_mixer(काष्ठा snd_card *card,
		     काष्ठा snd_ak4531 *_ak4531,
		     काष्ठा snd_ak4531 **rak4531)
अणु
	अचिन्हित पूर्णांक idx;
	पूर्णांक err;
	काष्ठा snd_ak4531 *ak4531;
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त =	snd_ak4531_dev_मुक्त,
	पूर्ण;

	अगर (snd_BUG_ON(!card || !_ak4531))
		वापस -EINVAL;
	अगर (rak4531)
		*rak4531 = शून्य;
	ak4531 = kzalloc(माप(*ak4531), GFP_KERNEL);
	अगर (ak4531 == शून्य)
		वापस -ENOMEM;
	*ak4531 = *_ak4531;
	mutex_init(&ak4531->reg_mutex);
	अगर ((err = snd_component_add(card, "AK4531")) < 0) अणु
		snd_ak4531_मुक्त(ak4531);
		वापस err;
	पूर्ण
	म_नकल(card->mixername, "Asahi Kasei AK4531");
	ak4531->ग_लिखो(ak4531, AK4531_RESET, 0x03);	/* no RST, PD */
	udelay(100);
	ak4531->ग_लिखो(ak4531, AK4531_CLOCK, 0x00);	/* CODEC ADC and CODEC DAC use अणुLR,Bपूर्णCLK2 and run off LRCLK2 PLL */
	क्रम (idx = 0; idx <= 0x19; idx++) अणु
		अगर (idx == AK4531_RESET || idx == AK4531_CLOCK)
			जारी;
		ak4531->ग_लिखो(ak4531, idx, ak4531->regs[idx] = snd_ak4531_initial_map[idx]);	/* recording source is mixer */
	पूर्ण
	क्रम (idx = 0; idx < ARRAY_SIZE(snd_ak4531_controls); idx++) अणु
		अगर ((err = snd_ctl_add(card, snd_ctl_new1(&snd_ak4531_controls[idx], ak4531))) < 0) अणु
			snd_ak4531_मुक्त(ak4531);
			वापस err;
		पूर्ण
	पूर्ण
	snd_ak4531_proc_init(card, ak4531);
	अगर ((err = snd_device_new(card, SNDRV_DEV_CODEC, ak4531, &ops)) < 0) अणु
		snd_ak4531_मुक्त(ak4531);
		वापस err;
	पूर्ण

#अगर 0
	snd_ak4531_dump(ak4531);
#पूर्ण_अगर
	अगर (rak4531)
		*rak4531 = ak4531;
	वापस 0;
पूर्ण

/*
 * घातer management
 */
#अगर_घोषित CONFIG_PM
व्योम snd_ak4531_suspend(काष्ठा snd_ak4531 *ak4531)
अणु
	/* mute */
	ak4531->ग_लिखो(ak4531, AK4531_LMASTER, 0x9f);
	ak4531->ग_लिखो(ak4531, AK4531_RMASTER, 0x9f);
	/* घातerकरोwn */
	ak4531->ग_लिखो(ak4531, AK4531_RESET, 0x01);
पूर्ण

व्योम snd_ak4531_resume(काष्ठा snd_ak4531 *ak4531)
अणु
	पूर्णांक idx;

	/* initialize */
	ak4531->ग_लिखो(ak4531, AK4531_RESET, 0x03);
	udelay(100);
	ak4531->ग_लिखो(ak4531, AK4531_CLOCK, 0x00);
	/* restore mixer रेजिस्टरs */
	क्रम (idx = 0; idx <= 0x19; idx++) अणु
		अगर (idx == AK4531_RESET || idx == AK4531_CLOCK)
			जारी;
		ak4531->ग_लिखो(ak4531, idx, ak4531->regs[idx]);
	पूर्ण
पूर्ण
#पूर्ण_अगर

/*
 * /proc पूर्णांकerface
 */

अटल व्योम snd_ak4531_proc_पढ़ो(काष्ठा snd_info_entry *entry, 
				 काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_ak4531 *ak4531 = entry->निजी_data;

	snd_iम_लिखो(buffer, "Asahi Kasei AK4531\n\n");
	snd_iम_लिखो(buffer, "Recording source   : %s\n"
		    "MIC gain           : %s\n",
		    ak4531->regs[AK4531_AD_IN] & 1 ? "external" : "mixer",
		    ak4531->regs[AK4531_MIC_GAIN] & 1 ? "+30dB" : "+0dB");
पूर्ण

अटल व्योम
snd_ak4531_proc_init(काष्ठा snd_card *card, काष्ठा snd_ak4531 *ak4531)
अणु
	snd_card_ro_proc_new(card, "ak4531", ak4531, snd_ak4531_proc_पढ़ो);
पूर्ण
