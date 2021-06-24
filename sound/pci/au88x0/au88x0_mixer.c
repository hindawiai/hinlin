<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Vortex Mixer support.
 *
 * There is much more than just the AC97 mixer...
 *
 */

#समावेश <linux/समय.स>
#समावेश <linux/init.h>
#समावेश <sound/core.h>
#समावेश "au88x0.h"

अटल पूर्णांक हटाओ_ctl(काष्ठा snd_card *card, स्थिर अक्षर *name)
अणु
	काष्ठा snd_ctl_elem_id id;
	स_रखो(&id, 0, माप(id));
	म_नकल(id.name, name);
	id.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER;
	वापस snd_ctl_हटाओ_id(card, &id);
पूर्ण

अटल पूर्णांक snd_vortex_mixer(vortex_t *vortex)
अणु
	काष्ठा snd_ac97_bus *pbus;
	काष्ठा snd_ac97_ढाँचा ac97;
	पूर्णांक err;
	अटल स्थिर काष्ठा snd_ac97_bus_ops ops = अणु
		.ग_लिखो = vortex_codec_ग_लिखो,
		.पढ़ो = vortex_codec_पढ़ो,
	पूर्ण;

	अगर ((err = snd_ac97_bus(vortex->card, 0, &ops, शून्य, &pbus)) < 0)
		वापस err;
	स_रखो(&ac97, 0, माप(ac97));
	// Initialize AC97 codec stuff.
	ac97.निजी_data = vortex;
	ac97.scaps = AC97_SCAP_NO_SPDIF;
	err = snd_ac97_mixer(pbus, &ac97, &vortex->codec);
	vortex->isquad = ((vortex->codec == शून्य) ?  0 : (vortex->codec->ext_id&0x80));
	हटाओ_ctl(vortex->card, "Master Mono Playback Volume");
	हटाओ_ctl(vortex->card, "Master Mono Playback Switch");
	वापस err;
पूर्ण
