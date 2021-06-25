<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   ALSA driver क्रम ICEnsemble VT17xx
 *
 *   Lowlevel functions क्रम WM8766 codec
 *
 *	Copyright (c) 2012 Ondrej Zary <linux@rainbow-software.org>
 */

#समावेश <linux/delay.h>
#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/tlv.h>
#समावेश "wm8766.h"

/* low-level access */

अटल व्योम snd_wm8766_ग_लिखो(काष्ठा snd_wm8766 *wm, u16 addr, u16 data)
अणु
	अगर (addr < WM8766_REG_COUNT)
		wm->regs[addr] = data;
	wm->ops.ग_लिखो(wm, addr, data);
पूर्ण

/* mixer controls */

अटल स्थिर DECLARE_TLV_DB_SCALE(wm8766_tlv, -12750, 50, 1);

अटल स्थिर काष्ठा snd_wm8766_ctl snd_wm8766_शेष_ctl[WM8766_CTL_COUNT] = अणु
	[WM8766_CTL_CH1_VOL] = अणु
		.name = "Channel 1 Playback Volume",
		.type = SNDRV_CTL_ELEM_TYPE_INTEGER,
		.tlv = wm8766_tlv,
		.reg1 = WM8766_REG_DACL1,
		.reg2 = WM8766_REG_DACR1,
		.mask1 = WM8766_VOL_MASK,
		.mask2 = WM8766_VOL_MASK,
		.max = 0xff,
		.flags = WM8766_FLAG_STEREO | WM8766_FLAG_VOL_UPDATE,
	पूर्ण,
	[WM8766_CTL_CH2_VOL] = अणु
		.name = "Channel 2 Playback Volume",
		.type = SNDRV_CTL_ELEM_TYPE_INTEGER,
		.tlv = wm8766_tlv,
		.reg1 = WM8766_REG_DACL2,
		.reg2 = WM8766_REG_DACR2,
		.mask1 = WM8766_VOL_MASK,
		.mask2 = WM8766_VOL_MASK,
		.max = 0xff,
		.flags = WM8766_FLAG_STEREO | WM8766_FLAG_VOL_UPDATE,
	पूर्ण,
	[WM8766_CTL_CH3_VOL] = अणु
		.name = "Channel 3 Playback Volume",
		.type = SNDRV_CTL_ELEM_TYPE_INTEGER,
		.tlv = wm8766_tlv,
		.reg1 = WM8766_REG_DACL3,
		.reg2 = WM8766_REG_DACR3,
		.mask1 = WM8766_VOL_MASK,
		.mask2 = WM8766_VOL_MASK,
		.max = 0xff,
		.flags = WM8766_FLAG_STEREO | WM8766_FLAG_VOL_UPDATE,
	पूर्ण,
	[WM8766_CTL_CH1_SW] = अणु
		.name = "Channel 1 Playback Switch",
		.type = SNDRV_CTL_ELEM_TYPE_BOOLEAN,
		.reg1 = WM8766_REG_DACCTRL2,
		.mask1 = WM8766_DAC2_MUTE1,
		.flags = WM8766_FLAG_INVERT,
	पूर्ण,
	[WM8766_CTL_CH2_SW] = अणु
		.name = "Channel 2 Playback Switch",
		.type = SNDRV_CTL_ELEM_TYPE_BOOLEAN,
		.reg1 = WM8766_REG_DACCTRL2,
		.mask1 = WM8766_DAC2_MUTE2,
		.flags = WM8766_FLAG_INVERT,
	पूर्ण,
	[WM8766_CTL_CH3_SW] = अणु
		.name = "Channel 3 Playback Switch",
		.type = SNDRV_CTL_ELEM_TYPE_BOOLEAN,
		.reg1 = WM8766_REG_DACCTRL2,
		.mask1 = WM8766_DAC2_MUTE3,
		.flags = WM8766_FLAG_INVERT,
	पूर्ण,
	[WM8766_CTL_PHASE1_SW] = अणु
		.name = "Channel 1 Phase Invert Playback Switch",
		.type = SNDRV_CTL_ELEM_TYPE_BOOLEAN,
		.reg1 = WM8766_REG_IFCTRL,
		.mask1 = WM8766_PHASE_INVERT1,
	पूर्ण,
	[WM8766_CTL_PHASE2_SW] = अणु
		.name = "Channel 2 Phase Invert Playback Switch",
		.type = SNDRV_CTL_ELEM_TYPE_BOOLEAN,
		.reg1 = WM8766_REG_IFCTRL,
		.mask1 = WM8766_PHASE_INVERT2,
	पूर्ण,
	[WM8766_CTL_PHASE3_SW] = अणु
		.name = "Channel 3 Phase Invert Playback Switch",
		.type = SNDRV_CTL_ELEM_TYPE_BOOLEAN,
		.reg1 = WM8766_REG_IFCTRL,
		.mask1 = WM8766_PHASE_INVERT3,
	पूर्ण,
	[WM8766_CTL_DEEMPH1_SW] = अणु
		.name = "Channel 1 Deemphasis Playback Switch",
		.type = SNDRV_CTL_ELEM_TYPE_BOOLEAN,
		.reg1 = WM8766_REG_DACCTRL2,
		.mask1 = WM8766_DAC2_DEEMP1,
	पूर्ण,
	[WM8766_CTL_DEEMPH2_SW] = अणु
		.name = "Channel 2 Deemphasis Playback Switch",
		.type = SNDRV_CTL_ELEM_TYPE_BOOLEAN,
		.reg1 = WM8766_REG_DACCTRL2,
		.mask1 = WM8766_DAC2_DEEMP2,
	पूर्ण,
	[WM8766_CTL_DEEMPH3_SW] = अणु
		.name = "Channel 3 Deemphasis Playback Switch",
		.type = SNDRV_CTL_ELEM_TYPE_BOOLEAN,
		.reg1 = WM8766_REG_DACCTRL2,
		.mask1 = WM8766_DAC2_DEEMP3,
	पूर्ण,
	[WM8766_CTL_IZD_SW] = अणु
		.name = "Infinite Zero Detect Playback Switch",
		.type = SNDRV_CTL_ELEM_TYPE_BOOLEAN,
		.reg1 = WM8766_REG_DACCTRL1,
		.mask1 = WM8766_DAC_IZD,
	पूर्ण,
	[WM8766_CTL_ZC_SW] = अणु
		.name = "Zero Cross Detect Playback Switch",
		.type = SNDRV_CTL_ELEM_TYPE_BOOLEAN,
		.reg1 = WM8766_REG_DACCTRL2,
		.mask1 = WM8766_DAC2_ZCD,
		.flags = WM8766_FLAG_INVERT,
	पूर्ण,
पूर्ण;

/* exported functions */

व्योम snd_wm8766_init(काष्ठा snd_wm8766 *wm)
अणु
	पूर्णांक i;
	अटल स्थिर u16 शेष_values[] = अणु
		0x000, 0x100,
		0x120, 0x000,
		0x000, 0x100, 0x000, 0x100, 0x000,
		0x000, 0x080,
	पूर्ण;

	स_नकल(wm->ctl, snd_wm8766_शेष_ctl, माप(wm->ctl));

	snd_wm8766_ग_लिखो(wm, WM8766_REG_RESET, 0x00); /* reset */
	udelay(10);
	/* load शेषs */
	क्रम (i = 0; i < ARRAY_SIZE(शेष_values); i++)
		snd_wm8766_ग_लिखो(wm, i, शेष_values[i]);
पूर्ण

व्योम snd_wm8766_resume(काष्ठा snd_wm8766 *wm)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < WM8766_REG_COUNT; i++)
		snd_wm8766_ग_लिखो(wm, i, wm->regs[i]);
पूर्ण

व्योम snd_wm8766_set_अगर(काष्ठा snd_wm8766 *wm, u16 dac)
अणु
	u16 val = wm->regs[WM8766_REG_IFCTRL] & ~WM8766_IF_MASK;

	dac &= WM8766_IF_MASK;
	snd_wm8766_ग_लिखो(wm, WM8766_REG_IFCTRL, val | dac);
पूर्ण

व्योम snd_wm8766_volume_restore(काष्ठा snd_wm8766 *wm)
अणु
	u16 val = wm->regs[WM8766_REG_DACR1];
	/* restore volume after MCLK stopped */
	snd_wm8766_ग_लिखो(wm, WM8766_REG_DACR1, val | WM8766_VOL_UPDATE);
पूर्ण

/* mixer callbacks */

अटल पूर्णांक snd_wm8766_volume_info(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा snd_wm8766 *wm = snd_kcontrol_chip(kcontrol);
	पूर्णांक n = kcontrol->निजी_value;

	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = (wm->ctl[n].flags & WM8766_FLAG_STEREO) ? 2 : 1;
	uinfo->value.पूर्णांकeger.min = wm->ctl[n].min;
	uinfo->value.पूर्णांकeger.max = wm->ctl[n].max;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_wm8766_क्रमागत_info(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा snd_wm8766 *wm = snd_kcontrol_chip(kcontrol);
	पूर्णांक n = kcontrol->निजी_value;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, wm->ctl[n].max,
						wm->ctl[n].क्रमागत_names);
पूर्ण

अटल पूर्णांक snd_wm8766_ctl_get(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_wm8766 *wm = snd_kcontrol_chip(kcontrol);
	पूर्णांक n = kcontrol->निजी_value;
	u16 val1, val2;

	अगर (wm->ctl[n].get)
		wm->ctl[n].get(wm, &val1, &val2);
	अन्यथा अणु
		val1 = wm->regs[wm->ctl[n].reg1] & wm->ctl[n].mask1;
		val1 >>= __ffs(wm->ctl[n].mask1);
		अगर (wm->ctl[n].flags & WM8766_FLAG_STEREO) अणु
			val2 = wm->regs[wm->ctl[n].reg2] & wm->ctl[n].mask2;
			val2 >>= __ffs(wm->ctl[n].mask2);
			अगर (wm->ctl[n].flags & WM8766_FLAG_VOL_UPDATE)
				val2 &= ~WM8766_VOL_UPDATE;
		पूर्ण
	पूर्ण
	अगर (wm->ctl[n].flags & WM8766_FLAG_INVERT) अणु
		val1 = wm->ctl[n].max - (val1 - wm->ctl[n].min);
		अगर (wm->ctl[n].flags & WM8766_FLAG_STEREO)
			val2 = wm->ctl[n].max - (val2 - wm->ctl[n].min);
	पूर्ण
	ucontrol->value.पूर्णांकeger.value[0] = val1;
	अगर (wm->ctl[n].flags & WM8766_FLAG_STEREO)
		ucontrol->value.पूर्णांकeger.value[1] = val2;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_wm8766_ctl_put(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_wm8766 *wm = snd_kcontrol_chip(kcontrol);
	पूर्णांक n = kcontrol->निजी_value;
	u16 val, regval1, regval2;

	/* this also works क्रम क्रमागत because value is a जोड़ */
	regval1 = ucontrol->value.पूर्णांकeger.value[0];
	regval2 = ucontrol->value.पूर्णांकeger.value[1];
	अगर (wm->ctl[n].flags & WM8766_FLAG_INVERT) अणु
		regval1 = wm->ctl[n].max - (regval1 - wm->ctl[n].min);
		regval2 = wm->ctl[n].max - (regval2 - wm->ctl[n].min);
	पूर्ण
	अगर (wm->ctl[n].set)
		wm->ctl[n].set(wm, regval1, regval2);
	अन्यथा अणु
		val = wm->regs[wm->ctl[n].reg1] & ~wm->ctl[n].mask1;
		val |= regval1 << __ffs(wm->ctl[n].mask1);
		/* both stereo controls in one रेजिस्टर */
		अगर (wm->ctl[n].flags & WM8766_FLAG_STEREO &&
				wm->ctl[n].reg1 == wm->ctl[n].reg2) अणु
			val &= ~wm->ctl[n].mask2;
			val |= regval2 << __ffs(wm->ctl[n].mask2);
		पूर्ण
		snd_wm8766_ग_लिखो(wm, wm->ctl[n].reg1, val);
		/* stereo controls in dअगरferent रेजिस्टरs */
		अगर (wm->ctl[n].flags & WM8766_FLAG_STEREO &&
				wm->ctl[n].reg1 != wm->ctl[n].reg2) अणु
			val = wm->regs[wm->ctl[n].reg2] & ~wm->ctl[n].mask2;
			val |= regval2 << __ffs(wm->ctl[n].mask2);
			अगर (wm->ctl[n].flags & WM8766_FLAG_VOL_UPDATE)
				val |= WM8766_VOL_UPDATE;
			snd_wm8766_ग_लिखो(wm, wm->ctl[n].reg2, val);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_wm8766_add_control(काष्ठा snd_wm8766 *wm, पूर्णांक num)
अणु
	काष्ठा snd_kcontrol_new cont;
	काष्ठा snd_kcontrol *ctl;

	स_रखो(&cont, 0, माप(cont));
	cont.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;
	cont.निजी_value = num;
	cont.name = wm->ctl[num].name;
	cont.access = SNDRV_CTL_ELEM_ACCESS_READWRITE;
	अगर (wm->ctl[num].flags & WM8766_FLAG_LIM ||
	    wm->ctl[num].flags & WM8766_FLAG_ALC)
		cont.access |= SNDRV_CTL_ELEM_ACCESS_INACTIVE;
	cont.tlv.p = शून्य;
	cont.get = snd_wm8766_ctl_get;
	cont.put = snd_wm8766_ctl_put;

	चयन (wm->ctl[num].type) अणु
	हाल SNDRV_CTL_ELEM_TYPE_INTEGER:
		cont.info = snd_wm8766_volume_info;
		cont.access |= SNDRV_CTL_ELEM_ACCESS_TLV_READ;
		cont.tlv.p = wm->ctl[num].tlv;
		अवरोध;
	हाल SNDRV_CTL_ELEM_TYPE_BOOLEAN:
		wm->ctl[num].max = 1;
		अगर (wm->ctl[num].flags & WM8766_FLAG_STEREO)
			cont.info = snd_ctl_boolean_stereo_info;
		अन्यथा
			cont.info = snd_ctl_boolean_mono_info;
		अवरोध;
	हाल SNDRV_CTL_ELEM_TYPE_ENUMERATED:
		cont.info = snd_wm8766_क्रमागत_info;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	ctl = snd_ctl_new1(&cont, wm);
	अगर (!ctl)
		वापस -ENOMEM;
	wm->ctl[num].kctl = ctl;

	वापस snd_ctl_add(wm->card, ctl);
पूर्ण

पूर्णांक snd_wm8766_build_controls(काष्ठा snd_wm8766 *wm)
अणु
	पूर्णांक err, i;

	क्रम (i = 0; i < WM8766_CTL_COUNT; i++)
		अगर (wm->ctl[i].name) अणु
			err = snd_wm8766_add_control(wm, i);
			अगर (err < 0)
				वापस err;
		पूर्ण

	वापस 0;
पूर्ण
