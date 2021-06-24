<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright 2011 Broadcom Corporation.  All rights reserved. */

#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/tlv.h>
#समावेश <sound/asoundef.h>

#समावेश "bcm2835.h"

/* volume maximum and minimum in terms of 0.01dB */
#घोषणा CTRL_VOL_MAX 400
#घोषणा CTRL_VOL_MIN -10239 /* originally -10240 */

अटल पूर्णांक bcm2835_audio_set_chip_ctls(काष्ठा bcm2835_chip *chip)
अणु
	पूर्णांक i, err = 0;

	/* change ctls क्रम all substreams */
	क्रम (i = 0; i < MAX_SUBSTREAMS; i++) अणु
		अगर (chip->alsa_stream[i]) अणु
			err = bcm2835_audio_set_ctls(chip->alsa_stream[i]);
			अगर (err < 0)
				अवरोध;
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक snd_bcm2835_ctl_info(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अगर (kcontrol->निजी_value == PCM_PLAYBACK_VOLUME) अणु
		uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
		uinfo->count = 1;
		uinfo->value.पूर्णांकeger.min = CTRL_VOL_MIN;
		uinfo->value.पूर्णांकeger.max = CTRL_VOL_MAX; /* 2303 */
	पूर्ण अन्यथा अगर (kcontrol->निजी_value == PCM_PLAYBACK_MUTE) अणु
		uinfo->type = SNDRV_CTL_ELEM_TYPE_BOOLEAN;
		uinfo->count = 1;
		uinfo->value.पूर्णांकeger.min = 0;
		uinfo->value.पूर्णांकeger.max = 1;
	पूर्ण अन्यथा अगर (kcontrol->निजी_value == PCM_PLAYBACK_DEVICE) अणु
		uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
		uinfo->count = 1;
		uinfo->value.पूर्णांकeger.min = 0;
		uinfo->value.पूर्णांकeger.max = AUDIO_DEST_MAX - 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_bcm2835_ctl_get(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा bcm2835_chip *chip = snd_kcontrol_chip(kcontrol);

	mutex_lock(&chip->audio_mutex);

	अगर (kcontrol->निजी_value == PCM_PLAYBACK_VOLUME)
		ucontrol->value.पूर्णांकeger.value[0] = chip->volume;
	अन्यथा अगर (kcontrol->निजी_value == PCM_PLAYBACK_MUTE)
		ucontrol->value.पूर्णांकeger.value[0] = chip->mute;
	अन्यथा अगर (kcontrol->निजी_value == PCM_PLAYBACK_DEVICE)
		ucontrol->value.पूर्णांकeger.value[0] = chip->dest;

	mutex_unlock(&chip->audio_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_bcm2835_ctl_put(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा bcm2835_chip *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक val, *valp;
	पूर्णांक changed = 0;

	अगर (kcontrol->निजी_value == PCM_PLAYBACK_VOLUME)
		valp = &chip->volume;
	अन्यथा अगर (kcontrol->निजी_value == PCM_PLAYBACK_MUTE)
		valp = &chip->mute;
	अन्यथा अगर (kcontrol->निजी_value == PCM_PLAYBACK_DEVICE)
		valp = &chip->dest;
	अन्यथा
		वापस -EINVAL;

	val = ucontrol->value.पूर्णांकeger.value[0];
	mutex_lock(&chip->audio_mutex);
	अगर (val != *valp) अणु
		*valp = val;
		changed = 1;
		अगर (bcm2835_audio_set_chip_ctls(chip))
			dev_err(chip->card->dev, "Failed to set ALSA controls..\n");
	पूर्ण
	mutex_unlock(&chip->audio_mutex);
	वापस changed;
पूर्ण

अटल DECLARE_TLV_DB_SCALE(snd_bcm2835_db_scale, CTRL_VOL_MIN, 1, 1);

अटल स्थिर काष्ठा snd_kcontrol_new snd_bcm2835_ctl[] = अणु
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "PCM Playback Volume",
		.access = SNDRV_CTL_ELEM_ACCESS_READWRITE | SNDRV_CTL_ELEM_ACCESS_TLV_READ,
		.निजी_value = PCM_PLAYBACK_VOLUME,
		.info = snd_bcm2835_ctl_info,
		.get = snd_bcm2835_ctl_get,
		.put = snd_bcm2835_ctl_put,
		.tlv = अणु.p = snd_bcm2835_db_scaleपूर्ण
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "PCM Playback Switch",
		.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
		.निजी_value = PCM_PLAYBACK_MUTE,
		.info = snd_bcm2835_ctl_info,
		.get = snd_bcm2835_ctl_get,
		.put = snd_bcm2835_ctl_put,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "PCM Playback Route",
		.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
		.निजी_value = PCM_PLAYBACK_DEVICE,
		.info = snd_bcm2835_ctl_info,
		.get = snd_bcm2835_ctl_get,
		.put = snd_bcm2835_ctl_put,
	पूर्ण,
पूर्ण;

अटल पूर्णांक snd_bcm2835_spdअगर_शेष_info(काष्ठा snd_kcontrol *kcontrol,
					  काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_bcm2835_spdअगर_शेष_get(काष्ठा snd_kcontrol *kcontrol,
					 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा bcm2835_chip *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक i;

	mutex_lock(&chip->audio_mutex);

	क्रम (i = 0; i < 4; i++)
		ucontrol->value.iec958.status[i] =
			(chip->spdअगर_status >> (i * 8)) & 0xff;

	mutex_unlock(&chip->audio_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_bcm2835_spdअगर_शेष_put(काष्ठा snd_kcontrol *kcontrol,
					 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा bcm2835_chip *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक val = 0;
	पूर्णांक i, change;

	mutex_lock(&chip->audio_mutex);

	क्रम (i = 0; i < 4; i++)
		val |= (अचिन्हित पूर्णांक)ucontrol->value.iec958.status[i] << (i * 8);

	change = val != chip->spdअगर_status;
	chip->spdअगर_status = val;

	mutex_unlock(&chip->audio_mutex);
	वापस change;
पूर्ण

अटल पूर्णांक snd_bcm2835_spdअगर_mask_info(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_bcm2835_spdअगर_mask_get(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	/*
	 * bcm2835 supports only consumer mode and sets all other क्रमmat flags
	 * स्वतःmatically. So the only thing left is संकेतling non-audio content
	 */
	ucontrol->value.iec958.status[0] = IEC958_AES0_NONAUDIO;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_bcm2835_spdअगर[] = अणु
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
		.name = SNDRV_CTL_NAME_IEC958("", PLAYBACK, DEFAULT),
		.info = snd_bcm2835_spdअगर_शेष_info,
		.get = snd_bcm2835_spdअगर_शेष_get,
		.put = snd_bcm2835_spdअगर_शेष_put
	पूर्ण,
	अणु
		.access = SNDRV_CTL_ELEM_ACCESS_READ,
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
		.name = SNDRV_CTL_NAME_IEC958("", PLAYBACK, CON_MASK),
		.info = snd_bcm2835_spdअगर_mask_info,
		.get = snd_bcm2835_spdअगर_mask_get,
	पूर्ण,
पूर्ण;

अटल पूर्णांक create_ctls(काष्ठा bcm2835_chip *chip, माप_प्रकार size,
		       स्थिर काष्ठा snd_kcontrol_new *kctls)
अणु
	पूर्णांक i, err;

	क्रम (i = 0; i < size; i++) अणु
		err = snd_ctl_add(chip->card, snd_ctl_new1(&kctls[i], chip));
		अगर (err < 0)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक snd_bcm2835_new_ctl(काष्ठा bcm2835_chip *chip)
अणु
	पूर्णांक err;

	strscpy(chip->card->mixername, "Broadcom Mixer", माप(chip->card->mixername));
	err = create_ctls(chip, ARRAY_SIZE(snd_bcm2835_ctl), snd_bcm2835_ctl);
	अगर (err < 0)
		वापस err;
	वापस create_ctls(chip, ARRAY_SIZE(snd_bcm2835_spdअगर),
			   snd_bcm2835_spdअगर);
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_bcm2835_headphones_ctl[] = अणु
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Headphone Playback Volume",
		.index = 0,
		.access = SNDRV_CTL_ELEM_ACCESS_READWRITE |
			  SNDRV_CTL_ELEM_ACCESS_TLV_READ,
		.निजी_value = PCM_PLAYBACK_VOLUME,
		.info = snd_bcm2835_ctl_info,
		.get = snd_bcm2835_ctl_get,
		.put = snd_bcm2835_ctl_put,
		.count = 1,
		.tlv = अणु.p = snd_bcm2835_db_scaleपूर्ण
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Headphone Playback Switch",
		.index = 0,
		.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
		.निजी_value = PCM_PLAYBACK_MUTE,
		.info = snd_bcm2835_ctl_info,
		.get = snd_bcm2835_ctl_get,
		.put = snd_bcm2835_ctl_put,
		.count = 1,
	पूर्ण
पूर्ण;

पूर्णांक snd_bcm2835_new_headphones_ctl(काष्ठा bcm2835_chip *chip)
अणु
	strscpy(chip->card->mixername, "Broadcom Mixer", माप(chip->card->mixername));
	वापस create_ctls(chip, ARRAY_SIZE(snd_bcm2835_headphones_ctl),
			   snd_bcm2835_headphones_ctl);
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_bcm2835_hdmi[] = अणु
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "HDMI Playback Volume",
		.index = 0,
		.access = SNDRV_CTL_ELEM_ACCESS_READWRITE |
			  SNDRV_CTL_ELEM_ACCESS_TLV_READ,
		.निजी_value = PCM_PLAYBACK_VOLUME,
		.info = snd_bcm2835_ctl_info,
		.get = snd_bcm2835_ctl_get,
		.put = snd_bcm2835_ctl_put,
		.count = 1,
		.tlv = अणु.p = snd_bcm2835_db_scaleपूर्ण
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "HDMI Playback Switch",
		.index = 0,
		.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
		.निजी_value = PCM_PLAYBACK_MUTE,
		.info = snd_bcm2835_ctl_info,
		.get = snd_bcm2835_ctl_get,
		.put = snd_bcm2835_ctl_put,
		.count = 1,
	पूर्ण
पूर्ण;

पूर्णांक snd_bcm2835_new_hdmi_ctl(काष्ठा bcm2835_chip *chip)
अणु
	strscpy(chip->card->mixername, "Broadcom Mixer", माप(chip->card->mixername));
	वापस create_ctls(chip, ARRAY_SIZE(snd_bcm2835_hdmi),
			   snd_bcm2835_hdmi);
पूर्ण

