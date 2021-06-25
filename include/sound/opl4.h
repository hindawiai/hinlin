<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_OPL4_H
#घोषणा __SOUND_OPL4_H

/*
 * Global definitions क्रम the OPL4 driver
 * Copyright (c) 2003 by Clemens Ladisch <clemens@ladisch.de>
 */

#समावेश <sound/opl3.h>

काष्ठा snd_opl4;

बाह्य पूर्णांक snd_opl4_create(काष्ठा snd_card *card,
			   अचिन्हित दीर्घ fm_port, अचिन्हित दीर्घ pcm_port,
			   पूर्णांक seq_device,
			   काष्ठा snd_opl3 **opl3, काष्ठा snd_opl4 **opl4);

#पूर्ण_अगर /* __SOUND_OPL4_H */
