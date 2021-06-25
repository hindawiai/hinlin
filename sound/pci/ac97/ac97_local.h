<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *  Universal पूर्णांकerface क्रम Audio Codec '97
 *
 *  For more details look to AC '97 component specअगरication revision 2.2
 *  by Intel Corporation (http://developer.पूर्णांकel.com).
 */

व्योम snd_ac97_get_name(काष्ठा snd_ac97 *ac97, अचिन्हित पूर्णांक id, अक्षर *name,
		       पूर्णांक modem);
पूर्णांक snd_ac97_update_bits_nolock(काष्ठा snd_ac97 *ac97, अचिन्हित लघु reg,
				अचिन्हित लघु mask, अचिन्हित लघु value);

/* ac97_proc.c */
#अगर_घोषित CONFIG_SND_PROC_FS
व्योम snd_ac97_bus_proc_init(काष्ठा snd_ac97_bus * ac97);
व्योम snd_ac97_bus_proc_करोne(काष्ठा snd_ac97_bus * ac97);
व्योम snd_ac97_proc_init(काष्ठा snd_ac97 * ac97);
व्योम snd_ac97_proc_करोne(काष्ठा snd_ac97 * ac97);
#अन्यथा
#घोषणा snd_ac97_bus_proc_init(ac97_bus_t) करो अणु पूर्ण जबतक (0)
#घोषणा snd_ac97_bus_proc_करोne(ac97_bus_t) करो अणु पूर्ण जबतक (0)
#घोषणा snd_ac97_proc_init(ac97_t) करो अणु पूर्ण जबतक (0)
#घोषणा snd_ac97_proc_करोne(ac97_t) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर
