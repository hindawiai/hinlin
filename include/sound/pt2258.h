<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *   ALSA Driver क्रम the PT2258 volume controller.
 *
 *	Copyright (c) 2006  Jochen Voss <voss@seehuhn.de>
 */      

#अगर_अघोषित __SOUND_PT2258_H
#घोषणा __SOUND_PT2258_H

काष्ठा snd_pt2258 अणु
	काष्ठा snd_card *card;
	काष्ठा snd_i2c_bus *i2c_bus;
	काष्ठा snd_i2c_device *i2c_dev;

	अचिन्हित अक्षर volume[6];
	पूर्णांक mute;
पूर्ण;

बाह्य पूर्णांक snd_pt2258_reset(काष्ठा snd_pt2258 *pt);
बाह्य पूर्णांक snd_pt2258_build_controls(काष्ठा snd_pt2258 *pt);

#पूर्ण_अगर /* __SOUND_PT2258_H */
