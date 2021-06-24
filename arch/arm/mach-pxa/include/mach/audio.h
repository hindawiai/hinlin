<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_ARCH_AUDIO_H__
#घोषणा __ASM_ARCH_AUDIO_H__

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/ac97_codec.h>

/*
 * @reset_gpio: AC97 reset gpio (normally gpio113 or gpio95)
 *              a -1 value means no gpio will be used क्रम reset
 * @codec_pdata: AC97 codec platक्रमm_data

 * reset_gpio should only be specअगरied क्रम pxa27x CPUs where a silicon
 * bug prevents correct operation of the reset line. If not specअगरied,
 * the शेष behaviour on these CPUs is to consider gpio 113 as the
 * AC97 reset line, which is the शेष on most boards.
 */
प्रकार काष्ठा अणु
	पूर्णांक (*startup)(काष्ठा snd_pcm_substream *, व्योम *);
	व्योम (*shutकरोwn)(काष्ठा snd_pcm_substream *, व्योम *);
	व्योम (*suspend)(व्योम *);
	व्योम (*resume)(व्योम *);
	व्योम *priv;
	पूर्णांक reset_gpio;
	व्योम *codec_pdata[AC97_BUS_MAX_DEVICES];
पूर्ण pxa2xx_audio_ops_t;

बाह्य व्योम pxa_set_ac97_info(pxa2xx_audio_ops_t *ops);

#पूर्ण_अगर
