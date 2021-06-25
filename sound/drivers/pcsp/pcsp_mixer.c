<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PC-Speaker driver क्रम Linux
 *
 * Mixer implementation.
 * Copyright (C) 2001-2008  Stas Sergeev
 */

#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश "pcsp.h"


अटल पूर्णांक pcsp_enable_info(काष्ठा snd_kcontrol *kcontrol,
			    काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_BOOLEAN;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक pcsp_enable_get(काष्ठा snd_kcontrol *kcontrol,
			   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pcsp *chip = snd_kcontrol_chip(kcontrol);
	ucontrol->value.पूर्णांकeger.value[0] = chip->enable;
	वापस 0;
पूर्ण

अटल पूर्णांक pcsp_enable_put(काष्ठा snd_kcontrol *kcontrol,
			   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pcsp *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक changed = 0;
	पूर्णांक enab = ucontrol->value.पूर्णांकeger.value[0];
	अगर (enab != chip->enable) अणु
		chip->enable = enab;
		changed = 1;
	पूर्ण
	वापस changed;
पूर्ण

अटल पूर्णांक pcsp_treble_info(काष्ठा snd_kcontrol *kcontrol,
			    काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा snd_pcsp *chip = snd_kcontrol_chip(kcontrol);
	uinfo->type = SNDRV_CTL_ELEM_TYPE_ENUMERATED;
	uinfo->count = 1;
	uinfo->value.क्रमागतerated.items = chip->max_treble + 1;
	अगर (uinfo->value.क्रमागतerated.item > chip->max_treble)
		uinfo->value.क्रमागतerated.item = chip->max_treble;
	प्र_लिखो(uinfo->value.क्रमागतerated.name, "%lu",
		(अचिन्हित दीर्घ)PCSP_CALC_RATE(uinfo->value.क्रमागतerated.item));
	वापस 0;
पूर्ण

अटल पूर्णांक pcsp_treble_get(काष्ठा snd_kcontrol *kcontrol,
			   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pcsp *chip = snd_kcontrol_chip(kcontrol);
	ucontrol->value.क्रमागतerated.item[0] = chip->treble;
	वापस 0;
पूर्ण

अटल पूर्णांक pcsp_treble_put(काष्ठा snd_kcontrol *kcontrol,
			   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pcsp *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक changed = 0;
	पूर्णांक treble = ucontrol->value.क्रमागतerated.item[0];
	अगर (treble != chip->treble) अणु
		chip->treble = treble;
#अगर PCSP_DEBUG
		prपूर्णांकk(KERN_INFO "PCSP: rate set to %li\n", PCSP_RATE());
#पूर्ण_अगर
		changed = 1;
	पूर्ण
	वापस changed;
पूर्ण

अटल पूर्णांक pcsp_pcspkr_info(काष्ठा snd_kcontrol *kcontrol,
			    काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_BOOLEAN;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक pcsp_pcspkr_get(काष्ठा snd_kcontrol *kcontrol,
			   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pcsp *chip = snd_kcontrol_chip(kcontrol);
	ucontrol->value.पूर्णांकeger.value[0] = chip->pcspkr;
	वापस 0;
पूर्ण

अटल पूर्णांक pcsp_pcspkr_put(काष्ठा snd_kcontrol *kcontrol,
			   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pcsp *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक changed = 0;
	पूर्णांक spkr = ucontrol->value.पूर्णांकeger.value[0];
	अगर (spkr != chip->pcspkr) अणु
		chip->pcspkr = spkr;
		changed = 1;
	पूर्ण
	वापस changed;
पूर्ण

#घोषणा PCSP_MIXER_CONTROL(ctl_type, ctl_name) \
अणु \
	.अगरace =	SNDRV_CTL_ELEM_IFACE_MIXER, \
	.name =		ctl_name, \
	.info =		pcsp_##ctl_type##_info, \
	.get =		pcsp_##ctl_type##_get, \
	.put =		pcsp_##ctl_type##_put, \
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_pcsp_controls_pcm[] = अणु
	PCSP_MIXER_CONTROL(enable, "Master Playback Switch"),
	PCSP_MIXER_CONTROL(treble, "BaseFRQ Playback Volume"),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_pcsp_controls_spkr[] = अणु
	PCSP_MIXER_CONTROL(pcspkr, "Beep Playback Switch"),
पूर्ण;

अटल पूर्णांक snd_pcsp_ctls_add(काष्ठा snd_pcsp *chip,
			     स्थिर काष्ठा snd_kcontrol_new *ctls, पूर्णांक num)
अणु
	पूर्णांक i, err;
	काष्ठा snd_card *card = chip->card;
	क्रम (i = 0; i < num; i++) अणु
		err = snd_ctl_add(card, snd_ctl_new1(ctls + i, chip));
		अगर (err < 0)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक snd_pcsp_new_mixer(काष्ठा snd_pcsp *chip, पूर्णांक nopcm)
अणु
	पूर्णांक err;
	काष्ठा snd_card *card = chip->card;

	अगर (!nopcm) अणु
		err = snd_pcsp_ctls_add(chip, snd_pcsp_controls_pcm,
			ARRAY_SIZE(snd_pcsp_controls_pcm));
		अगर (err < 0)
			वापस err;
	पूर्ण
	err = snd_pcsp_ctls_add(chip, snd_pcsp_controls_spkr,
		ARRAY_SIZE(snd_pcsp_controls_spkr));
	अगर (err < 0)
		वापस err;

	म_नकल(card->mixername, "PC-Speaker");

	वापस 0;
पूर्ण
