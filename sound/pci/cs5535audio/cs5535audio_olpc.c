<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * OLPC XO-1 additional sound features
 *
 * Copyright तऊ 2006  Jaya Kumar <jayakumar.lkml@gmail.com>
 * Copyright तऊ 2007-2008  Andres Salomon <dilinger@debian.org>
 */
#समावेश <sound/core.h>
#समावेश <sound/info.h>
#समावेश <sound/control.h>
#समावेश <sound/ac97_codec.h>
#समावेश <linux/gpपन.स>

#समावेश <यंत्र/olpc.h>
#समावेश "cs5535audio.h"

#घोषणा DRV_NAME "cs5535audio-olpc"

/*
 * OLPC has an additional feature on top of the regular AD1888 codec features.
 * It has an Analog Input mode that is चयनed पूर्णांकo (after disabling the
 * High Pass Filter) via GPIO.  It is supported on B2 and later models.
 */
व्योम olpc_analog_input(काष्ठा snd_ac97 *ac97, पूर्णांक on)
अणु
	पूर्णांक err;

	अगर (!machine_is_olpc())
		वापस;

	/* update the High Pass Filter (via AC97_AD_TEST2) */
	err = snd_ac97_update_bits(ac97, AC97_AD_TEST2,
			1 << AC97_AD_HPFD_SHIFT, on << AC97_AD_HPFD_SHIFT);
	अगर (err < 0) अणु
		dev_err(ac97->bus->card->dev,
			"setting High Pass Filter - %d\n", err);
		वापस;
	पूर्ण

	/* set Analog Input through GPIO */
	gpio_set_value(OLPC_GPIO_MIC_AC, on);
पूर्ण

/*
 * OLPC XO-1's V_REFOUT is a mic bias enable.
 */
व्योम olpc_mic_bias(काष्ठा snd_ac97 *ac97, पूर्णांक on)
अणु
	पूर्णांक err;

	अगर (!machine_is_olpc())
		वापस;

	on = on ? 0 : 1;
	err = snd_ac97_update_bits(ac97, AC97_AD_MISC,
			1 << AC97_AD_VREFD_SHIFT, on << AC97_AD_VREFD_SHIFT);
	अगर (err < 0)
		dev_err(ac97->bus->card->dev, "setting MIC Bias - %d\n", err);
पूर्ण

अटल पूर्णांक olpc_dc_info(काष्ठा snd_kcontrol *kctl,
		काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_BOOLEAN;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक olpc_dc_get(काष्ठा snd_kcontrol *kctl, काष्ठा snd_ctl_elem_value *v)
अणु
	v->value.पूर्णांकeger.value[0] = gpio_get_value(OLPC_GPIO_MIC_AC);
	वापस 0;
पूर्ण

अटल पूर्णांक olpc_dc_put(काष्ठा snd_kcontrol *kctl, काष्ठा snd_ctl_elem_value *v)
अणु
	काष्ठा cs5535audio *cs5535au = snd_kcontrol_chip(kctl);

	olpc_analog_input(cs5535au->ac97, v->value.पूर्णांकeger.value[0]);
	वापस 1;
पूर्ण

अटल पूर्णांक olpc_mic_info(काष्ठा snd_kcontrol *kctl,
		काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_BOOLEAN;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक olpc_mic_get(काष्ठा snd_kcontrol *kctl, काष्ठा snd_ctl_elem_value *v)
अणु
	काष्ठा cs5535audio *cs5535au = snd_kcontrol_chip(kctl);
	काष्ठा snd_ac97 *ac97 = cs5535au->ac97;
	पूर्णांक i;

	i = (snd_ac97_पढ़ो(ac97, AC97_AD_MISC) >> AC97_AD_VREFD_SHIFT) & 0x1;
	v->value.पूर्णांकeger.value[0] = i ? 0 : 1;
	वापस 0;
पूर्ण

अटल पूर्णांक olpc_mic_put(काष्ठा snd_kcontrol *kctl, काष्ठा snd_ctl_elem_value *v)
अणु
	काष्ठा cs5535audio *cs5535au = snd_kcontrol_chip(kctl);

	olpc_mic_bias(cs5535au->ac97, v->value.पूर्णांकeger.value[0]);
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new olpc_cs5535audio_ctls[] = अणु
अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "DC Mode Enable",
	.info = olpc_dc_info,
	.get = olpc_dc_get,
	.put = olpc_dc_put,
	.निजी_value = 0,
पूर्ण,
अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "MIC Bias Enable",
	.info = olpc_mic_info,
	.get = olpc_mic_get,
	.put = olpc_mic_put,
	.निजी_value = 0,
पूर्ण,
पूर्ण;

व्योम olpc_prequirks(काष्ठा snd_card *card,
		    काष्ठा snd_ac97_ढाँचा *ac97)
अणु
	अगर (!machine_is_olpc())
		वापस;

	/* invert EAPD अगर on an OLPC B3 or higher */
	अगर (olpc_board_at_least(olpc_board_pre(0xb3)))
		ac97->scaps |= AC97_SCAP_INV_EAPD;
पूर्ण

पूर्णांक olpc_quirks(काष्ठा snd_card *card, काष्ठा snd_ac97 *ac97)
अणु
	काष्ठा snd_ctl_elem_id elem;
	पूर्णांक i, err;

	अगर (!machine_is_olpc())
		वापस 0;

	अगर (gpio_request(OLPC_GPIO_MIC_AC, DRV_NAME)) अणु
		dev_err(card->dev, "unable to allocate MIC GPIO\n");
		वापस -EIO;
	पूर्ण
	gpio_direction_output(OLPC_GPIO_MIC_AC, 0);

	/* drop the original AD1888 HPF control */
	स_रखो(&elem, 0, माप(elem));
	elem.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;
	strscpy(elem.name, "High Pass Filter Enable", माप(elem.name));
	snd_ctl_हटाओ_id(card, &elem);

	/* drop the original V_REFOUT control */
	स_रखो(&elem, 0, माप(elem));
	elem.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;
	strscpy(elem.name, "V_REFOUT Enable", माप(elem.name));
	snd_ctl_हटाओ_id(card, &elem);

	/* add the OLPC-specअगरic controls */
	क्रम (i = 0; i < ARRAY_SIZE(olpc_cs5535audio_ctls); i++) अणु
		err = snd_ctl_add(card, snd_ctl_new1(&olpc_cs5535audio_ctls[i],
				ac97->निजी_data));
		अगर (err < 0) अणु
			gpio_मुक्त(OLPC_GPIO_MIC_AC);
			वापस err;
		पूर्ण
	पूर्ण

	/* turn off the mic by शेष */
	olpc_mic_bias(ac97, 0);
	वापस 0;
पूर्ण

व्योम olpc_quirks_cleanup(व्योम)
अणु
	gpio_मुक्त(OLPC_GPIO_MIC_AC);
पूर्ण
