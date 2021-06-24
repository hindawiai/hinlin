<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Helper functions क्रम jack-detection kcontrols
 *
 * Copyright (c) 2011 Takashi Iwai <tiwai@suse.de>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <sound/core.h>
#समावेश <sound/control.h>

#घोषणा jack_detect_kctl_info	snd_ctl_boolean_mono_info

अटल पूर्णांक jack_detect_kctl_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.पूर्णांकeger.value[0] = kcontrol->निजी_value;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new jack_detect_kctl = अणु
	/* name is filled later */
	.अगरace = SNDRV_CTL_ELEM_IFACE_CARD,
	.access = SNDRV_CTL_ELEM_ACCESS_READ,
	.info = jack_detect_kctl_info,
	.get = jack_detect_kctl_get,
पूर्ण;

अटल पूर्णांक get_available_index(काष्ठा snd_card *card, स्थिर अक्षर *name)
अणु
	काष्ठा snd_ctl_elem_id sid;

	स_रखो(&sid, 0, माप(sid));

	sid.index = 0;
	sid.अगरace = SNDRV_CTL_ELEM_IFACE_CARD;
	strscpy(sid.name, name, माप(sid.name));

	जबतक (snd_ctl_find_id(card, &sid)) अणु
		sid.index++;
		/* reset numid; otherwise snd_ctl_find_id() hits this again */
		sid.numid = 0;
	पूर्ण

	वापस sid.index;
पूर्ण

अटल व्योम jack_kctl_name_gen(अक्षर *name, स्थिर अक्षर *src_name, पूर्णांक size)
अणु
	माप_प्रकार count = म_माप(src_name);
	bool need_cat = true;

	/* हटाओ redundant " Jack" from src_name */
	अगर (count >= 5)
		need_cat = म_भेदन(&src_name[count - 5], " Jack", 5) ? true : false;

	snम_लिखो(name, size, need_cat ? "%s Jack" : "%s", src_name);

पूर्ण

काष्ठा snd_kcontrol *
snd_kctl_jack_new(स्थिर अक्षर *name, काष्ठा snd_card *card)
अणु
	काष्ठा snd_kcontrol *kctl;

	kctl = snd_ctl_new1(&jack_detect_kctl, शून्य);
	अगर (!kctl)
		वापस शून्य;

	jack_kctl_name_gen(kctl->id.name, name, माप(kctl->id.name));
	kctl->id.index = get_available_index(card, kctl->id.name);
	kctl->निजी_value = 0;
	वापस kctl;
पूर्ण

व्योम snd_kctl_jack_report(काष्ठा snd_card *card,
			  काष्ठा snd_kcontrol *kctl, bool status)
अणु
	अगर (kctl->निजी_value == status)
		वापस;
	kctl->निजी_value = status;
	snd_ctl_notअगरy(card, SNDRV_CTL_EVENT_MASK_VALUE, &kctl->id);
पूर्ण
