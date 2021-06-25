<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Advanced Linux Sound Architecture - ALSA - Driver
 *  Copyright (c) 1994-2003 by Jaroslav Kysela <perex@perex.cz>,
 *                             Abramo Bagnara <abramo@alsa-project.org>
 */
#अगर_अघोषित __SOUND_ASOUND_H
#घोषणा __SOUND_ASOUND_H

#समावेश <linux/ioctl.h>
#समावेश <linux/समय.स>
#समावेश <यंत्र/byteorder.h>

#अगर_घोषित  __LITTLE_ENDIAN
#घोषणा SNDRV_LITTLE_ENDIAN
#अन्यथा
#अगर_घोषित __BIG_ENDIAN
#घोषणा SNDRV_BIG_ENDIAN
#अन्यथा
#त्रुटि "Unsupported endian..."
#पूर्ण_अगर
#पूर्ण_अगर

#समावेश <uapi/sound/asound.h>
#पूर्ण_अगर /* __SOUND_ASOUND_H */
