<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * OPL4 mixer functions
 * Copyright (c) 2003 by Clemens Ladisch <clemens@ladisch.de>
 */

#समावेश "opl4_local.h"
#समावेश <sound/control.h>

अटल पूर्णांक snd_opl4_ctl_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 7;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_opl4_ctl_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_opl4 *opl4 = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	u8 reg = kcontrol->निजी_value;
	u8 value;

	spin_lock_irqsave(&opl4->reg_lock, flags);
	value = snd_opl4_पढ़ो(opl4, reg);
	spin_unlock_irqrestore(&opl4->reg_lock, flags);
	ucontrol->value.पूर्णांकeger.value[0] = 7 - (value & 7);
	ucontrol->value.पूर्णांकeger.value[1] = 7 - ((value >> 3) & 7);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_opl4_ctl_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_opl4 *opl4 = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	u8 reg = kcontrol->निजी_value;
	u8 value, old_value;

	value = (7 - (ucontrol->value.पूर्णांकeger.value[0] & 7)) |
		((7 - (ucontrol->value.पूर्णांकeger.value[1] & 7)) << 3);
	spin_lock_irqsave(&opl4->reg_lock, flags);
	old_value = snd_opl4_पढ़ो(opl4, reg);
	snd_opl4_ग_लिखो(opl4, reg, value);
	spin_unlock_irqrestore(&opl4->reg_lock, flags);
	वापस value != old_value;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_opl4_controls[] = अणु
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "FM Playback Volume",
		.info = snd_opl4_ctl_info,
		.get = snd_opl4_ctl_get,
		.put = snd_opl4_ctl_put,
		.निजी_value = OPL4_REG_MIX_CONTROL_FM
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Wavetable Playback Volume",
		.info = snd_opl4_ctl_info,
		.get = snd_opl4_ctl_get,
		.put = snd_opl4_ctl_put,
		.निजी_value = OPL4_REG_MIX_CONTROL_PCM
	पूर्ण
पूर्ण;

पूर्णांक snd_opl4_create_mixer(काष्ठा snd_opl4 *opl4)
अणु
	काष्ठा snd_card *card = opl4->card;
	पूर्णांक i, err;

	म_जोड़ो(card->mixername, ",OPL4");

	क्रम (i = 0; i < 2; ++i) अणु
		err = snd_ctl_add(card, snd_ctl_new1(&snd_opl4_controls[i], opl4));
		अगर (err < 0)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण
