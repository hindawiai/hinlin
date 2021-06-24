<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *  Routines क्रम control of ICS 2101 chip and "mixer" in GF1 chip
 */

#समावेश <linux/समय.स>
#समावेश <linux/रुको.h>
#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/gus.h>

/*
 *
 */

#घोषणा GF1_SINGLE(xname, xindex, shअगरt, invert) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xindex, \
  .info = snd_gf1_info_single, \
  .get = snd_gf1_get_single, .put = snd_gf1_put_single, \
  .निजी_value = shअगरt | (invert << 8) पूर्ण

#घोषणा snd_gf1_info_single	snd_ctl_boolean_mono_info

अटल पूर्णांक snd_gf1_get_single(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_gus_card *gus = snd_kcontrol_chip(kcontrol);
	पूर्णांक shअगरt = kcontrol->निजी_value & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 8) & 1;
	
	ucontrol->value.पूर्णांकeger.value[0] = (gus->mix_cntrl_reg >> shअगरt) & 1;
	अगर (invert)
		ucontrol->value.पूर्णांकeger.value[0] ^= 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_gf1_put_single(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_gus_card *gus = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	पूर्णांक shअगरt = kcontrol->निजी_value & 0xff;
	पूर्णांक invert = (kcontrol->निजी_value >> 8) & 1;
	पूर्णांक change;
	अचिन्हित अक्षर oval, nval;
	
	nval = ucontrol->value.पूर्णांकeger.value[0] & 1;
	अगर (invert)
		nval ^= 1;
	nval <<= shअगरt;
	spin_lock_irqsave(&gus->reg_lock, flags);
	oval = gus->mix_cntrl_reg;
	nval = (oval & ~(1 << shअगरt)) | nval;
	change = nval != oval;
	outb(gus->mix_cntrl_reg = nval, GUSP(gus, MIXCNTRLREG));
	outb(gus->gf1.active_voice = 0, GUSP(gus, GF1PAGE));
	spin_unlock_irqrestore(&gus->reg_lock, flags);
	वापस change;
पूर्ण

#घोषणा ICS_DOUBLE(xname, xindex, addr) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xindex, \
  .info = snd_ics_info_द्विगुन, \
  .get = snd_ics_get_द्विगुन, .put = snd_ics_put_द्विगुन, \
  .निजी_value = addr पूर्ण

अटल पूर्णांक snd_ics_info_द्विगुन(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 127;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ics_get_द्विगुन(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_gus_card *gus = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	पूर्णांक addr = kcontrol->निजी_value & 0xff;
	अचिन्हित अक्षर left, right;
	
	spin_lock_irqsave(&gus->reg_lock, flags);
	left = gus->gf1.ics_regs[addr][0];
	right = gus->gf1.ics_regs[addr][1];
	spin_unlock_irqrestore(&gus->reg_lock, flags);
	ucontrol->value.पूर्णांकeger.value[0] = left & 127;
	ucontrol->value.पूर्णांकeger.value[1] = right & 127;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ics_put_द्विगुन(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_gus_card *gus = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	पूर्णांक addr = kcontrol->निजी_value & 0xff;
	पूर्णांक change;
	अचिन्हित अक्षर val1, val2, oval1, oval2;
	
	val1 = ucontrol->value.पूर्णांकeger.value[0] & 127;
	val2 = ucontrol->value.पूर्णांकeger.value[1] & 127;
	spin_lock_irqsave(&gus->reg_lock, flags);
	oval1 = gus->gf1.ics_regs[addr][0];
	oval2 = gus->gf1.ics_regs[addr][1];
	change = val1 != oval1 || val2 != oval2;
	gus->gf1.ics_regs[addr][0] = val1;
	gus->gf1.ics_regs[addr][1] = val2;
	अगर (gus->ics_flag && gus->ics_flipped &&
	    (addr == SNDRV_ICS_GF1_DEV || addr == SNDRV_ICS_MASTER_DEV))
		swap(val1, val2);
	addr <<= 3;
	outb(addr | 0, GUSP(gus, MIXCNTRLPORT));
	outb(1, GUSP(gus, MIXDATAPORT));
	outb(addr | 2, GUSP(gus, MIXCNTRLPORT));
	outb((अचिन्हित अक्षर) val1, GUSP(gus, MIXDATAPORT));
	outb(addr | 1, GUSP(gus, MIXCNTRLPORT));
	outb(2, GUSP(gus, MIXDATAPORT));
	outb(addr | 3, GUSP(gus, MIXCNTRLPORT));
	outb((अचिन्हित अक्षर) val2, GUSP(gus, MIXDATAPORT));
	spin_unlock_irqrestore(&gus->reg_lock, flags);
	वापस change;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_gf1_controls[] = अणु
GF1_SINGLE("Master Playback Switch", 0, 1, 1),
GF1_SINGLE("Line Switch", 0, 0, 1),
GF1_SINGLE("Mic Switch", 0, 2, 0)
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_ics_controls[] = अणु
GF1_SINGLE("Master Playback Switch", 0, 1, 1),
ICS_DOUBLE("Master Playback Volume", 0, SNDRV_ICS_MASTER_DEV),
ICS_DOUBLE("Synth Playback Volume", 0, SNDRV_ICS_GF1_DEV),
GF1_SINGLE("Line Switch", 0, 0, 1),
ICS_DOUBLE("Line Playback Volume", 0, SNDRV_ICS_LINE_DEV),
GF1_SINGLE("Mic Switch", 0, 2, 0),
ICS_DOUBLE("Mic Playback Volume", 0, SNDRV_ICS_MIC_DEV),
ICS_DOUBLE("CD Playback Volume", 0, SNDRV_ICS_CD_DEV)
पूर्ण;

पूर्णांक snd_gf1_new_mixer(काष्ठा snd_gus_card * gus)
अणु
	काष्ठा snd_card *card;
	अचिन्हित पूर्णांक idx, max;
	पूर्णांक err;

	अगर (snd_BUG_ON(!gus))
		वापस -EINVAL;
	card = gus->card;
	अगर (snd_BUG_ON(!card))
		वापस -EINVAL;

	अगर (gus->ics_flag)
		snd_component_add(card, "ICS2101");
	अगर (card->mixername[0] == '\0') अणु
		म_नकल(card->mixername, gus->ics_flag ? "GF1,ICS2101" : "GF1");
	पूर्ण अन्यथा अणु
		अगर (gus->ics_flag)
			म_जोड़ो(card->mixername, ",ICS2101");
		म_जोड़ो(card->mixername, ",GF1");
	पूर्ण

	अगर (!gus->ics_flag) अणु
		max = gus->ess_flag ? 1 : ARRAY_SIZE(snd_gf1_controls);
		क्रम (idx = 0; idx < max; idx++) अणु
			अगर ((err = snd_ctl_add(card, snd_ctl_new1(&snd_gf1_controls[idx], gus))) < 0)
				वापस err;
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (idx = 0; idx < ARRAY_SIZE(snd_ics_controls); idx++) अणु
			अगर ((err = snd_ctl_add(card, snd_ctl_new1(&snd_ics_controls[idx], gus))) < 0)
				वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
