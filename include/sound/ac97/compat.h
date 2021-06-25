<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 *  Copyright (C) 2016 Robert Jarzmik <robert.jarzmik@मुक्त.fr>
 *
 * This file is क्रम backward compatibility with snd_ac97 काष्ठाure and its
 * multiple usages, such as the snd_ac97_bus and snd_ac97_build_ops.
 */

#अगर_अघोषित AC97_COMPAT_H
#घोषणा AC97_COMPAT_H

#समावेश <sound/ac97_codec.h>

काष्ठा snd_ac97 *snd_ac97_compat_alloc(काष्ठा ac97_codec_device *adev);
व्योम snd_ac97_compat_release(काष्ठा snd_ac97 *ac97);

#पूर्ण_अगर
