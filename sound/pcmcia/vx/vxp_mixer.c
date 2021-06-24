<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम Digigram VXpocket soundcards
 *
 * VX-pocket mixer
 *
 * Copyright (c) 2002 by Takashi Iwai <tiwai@suse.de>
 */

#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/tlv.h>
#समावेश "vxpocket.h"

#घोषणा MIC_LEVEL_MIN	0
#घोषणा MIC_LEVEL_MAX	8

/*
 * mic level control (क्रम VXPocket)
 */
अटल पूर्णांक vx_mic_level_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = MIC_LEVEL_MAX;
	वापस 0;
पूर्ण

अटल पूर्णांक vx_mic_level_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा vx_core *_chip = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_vxpocket *chip = to_vxpocket(_chip);
	ucontrol->value.पूर्णांकeger.value[0] = chip->mic_level;
	वापस 0;
पूर्ण

अटल पूर्णांक vx_mic_level_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा vx_core *_chip = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_vxpocket *chip = to_vxpocket(_chip);
	अचिन्हित पूर्णांक val = ucontrol->value.पूर्णांकeger.value[0];

	अगर (val > MIC_LEVEL_MAX)
		वापस -EINVAL;
	mutex_lock(&_chip->mixer_mutex);
	अगर (chip->mic_level != ucontrol->value.पूर्णांकeger.value[0]) अणु
		vx_set_mic_level(_chip, ucontrol->value.पूर्णांकeger.value[0]);
		chip->mic_level = ucontrol->value.पूर्णांकeger.value[0];
		mutex_unlock(&_chip->mixer_mutex);
		वापस 1;
	पूर्ण
	mutex_unlock(&_chip->mixer_mutex);
	वापस 0;
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_mic, -21, 3, 0);

अटल स्थिर काष्ठा snd_kcontrol_new vx_control_mic_level = अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_MIXER,
	.access =	(SNDRV_CTL_ELEM_ACCESS_READWRITE |
			 SNDRV_CTL_ELEM_ACCESS_TLV_READ),
	.name =		"Mic Capture Volume",
	.info =		vx_mic_level_info,
	.get =		vx_mic_level_get,
	.put =		vx_mic_level_put,
	.tlv = अणु .p = db_scale_mic पूर्ण,
पूर्ण;

/*
 * mic boost level control (क्रम VXP440)
 */
#घोषणा vx_mic_boost_info		snd_ctl_boolean_mono_info

अटल पूर्णांक vx_mic_boost_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा vx_core *_chip = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_vxpocket *chip = to_vxpocket(_chip);
	ucontrol->value.पूर्णांकeger.value[0] = chip->mic_level;
	वापस 0;
पूर्ण

अटल पूर्णांक vx_mic_boost_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा vx_core *_chip = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_vxpocket *chip = to_vxpocket(_chip);
	पूर्णांक val = !!ucontrol->value.पूर्णांकeger.value[0];
	mutex_lock(&_chip->mixer_mutex);
	अगर (chip->mic_level != val) अणु
		vx_set_mic_boost(_chip, val);
		chip->mic_level = val;
		mutex_unlock(&_chip->mixer_mutex);
		वापस 1;
	पूर्ण
	mutex_unlock(&_chip->mixer_mutex);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new vx_control_mic_boost = अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_MIXER,
	.name =		"Mic Boost",
	.info =		vx_mic_boost_info,
	.get =		vx_mic_boost_get,
	.put =		vx_mic_boost_put,
पूर्ण;


पूर्णांक vxp_add_mic_controls(काष्ठा vx_core *_chip)
अणु
	काष्ठा snd_vxpocket *chip = to_vxpocket(_chip);
	पूर्णांक err;

	/* mute input levels */
	chip->mic_level = 0;
	चयन (_chip->type) अणु
	हाल VX_TYPE_VXPOCKET:
		vx_set_mic_level(_chip, 0);
		अवरोध;
	हाल VX_TYPE_VXP440:
		vx_set_mic_boost(_chip, 0);
		अवरोध;
	पूर्ण

	/* mic level */
	चयन (_chip->type) अणु
	हाल VX_TYPE_VXPOCKET:
		अगर ((err = snd_ctl_add(_chip->card, snd_ctl_new1(&vx_control_mic_level, chip))) < 0)
			वापस err;
		अवरोध;
	हाल VX_TYPE_VXP440:
		अगर ((err = snd_ctl_add(_chip->card, snd_ctl_new1(&vx_control_mic_boost, chip))) < 0)
			वापस err;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

