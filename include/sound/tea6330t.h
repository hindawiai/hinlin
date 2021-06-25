<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_TEA6330T_H
#घोषणा __SOUND_TEA6330T_H

/*
 *  Routines क्रम control of TEA6330T circuit.
 *  Sound fader control circuit क्रम car radios.
 */

#समावेश <sound/i2c.h>		/* generic i2c support */

पूर्णांक snd_tea6330t_detect(काष्ठा snd_i2c_bus *bus, पूर्णांक equalizer);
पूर्णांक snd_tea6330t_update_mixer(काष्ठा snd_card *card, काष्ठा snd_i2c_bus *bus,
			      पूर्णांक equalizer, पूर्णांक fader);

#पूर्ण_अगर /* __SOUND_TEA6330T_H */
