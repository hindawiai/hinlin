<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_AK4531_CODEC_H
#घोषणा __SOUND_AK4531_CODEC_H

/*
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *  Universal पूर्णांकerface क्रम Audio Codec '97
 *
 *  For more details look to AC '97 component specअगरication revision 2.1
 *  by Intel Corporation (http://developer.पूर्णांकel.com).
 */

#समावेश <sound/info.h>
#समावेश <sound/control.h>

/*
 *  ASAHI KASEI - AK4531 codec
 *  - not really AC'97 codec, but it uses very similar interface as AC'97
 */

/*
 *  AK4531 codec रेजिस्टरs
 */

#घोषणा AK4531_LMASTER  0x00	/* master volume left */
#घोषणा AK4531_RMASTER  0x01	/* master volume right */
#घोषणा AK4531_LVOICE   0x02	/* channel volume left */
#घोषणा AK4531_RVOICE   0x03	/* channel volume right */
#घोषणा AK4531_LFM      0x04	/* FM volume left */
#घोषणा AK4531_RFM      0x05	/* FM volume right */
#घोषणा AK4531_LCD      0x06	/* CD volume left */
#घोषणा AK4531_RCD      0x07	/* CD volume right */
#घोषणा AK4531_LLINE    0x08	/* LINE volume left */
#घोषणा AK4531_RLINE    0x09	/* LINE volume right */
#घोषणा AK4531_LAUXA    0x0a	/* AUXA volume left */
#घोषणा AK4531_RAUXA    0x0b	/* AUXA volume right */
#घोषणा AK4531_MONO1    0x0c	/* MONO1 volume left */
#घोषणा AK4531_MONO2    0x0d	/* MONO1 volume right */
#घोषणा AK4531_MIC      0x0e	/* MIC volume */
#घोषणा AK4531_MONO_OUT 0x0f	/* Mono-out volume */
#घोषणा AK4531_OUT_SW1  0x10	/* Output mixer चयन 1 */
#घोषणा AK4531_OUT_SW2  0x11	/* Output mixer चयन 2 */
#घोषणा AK4531_LIN_SW1  0x12	/* Input left mixer चयन 1 */
#घोषणा AK4531_RIN_SW1  0x13	/* Input right mixer चयन 1 */
#घोषणा AK4531_LIN_SW2  0x14	/* Input left mixer चयन 2 */
#घोषणा AK4531_RIN_SW2  0x15	/* Input right mixer चयन 2 */
#घोषणा AK4531_RESET    0x16	/* Reset & घातer करोwn */
#घोषणा AK4531_CLOCK    0x17	/* Clock select */
#घोषणा AK4531_AD_IN    0x18	/* AD input select */
#घोषणा AK4531_MIC_GAIN 0x19	/* MIC amplअगरied gain */

काष्ठा snd_ak4531 अणु
	व्योम (*ग_लिखो) (काष्ठा snd_ak4531 *ak4531, अचिन्हित लघु reg,
		       अचिन्हित लघु val);
	व्योम *निजी_data;
	व्योम (*निजी_मुक्त) (काष्ठा snd_ak4531 *ak4531);
	/* --- */
	अचिन्हित अक्षर regs[0x20];
	काष्ठा mutex reg_mutex;
पूर्ण;

पूर्णांक snd_ak4531_mixer(काष्ठा snd_card *card, काष्ठा snd_ak4531 *_ak4531,
		     काष्ठा snd_ak4531 **rak4531);

#अगर_घोषित CONFIG_PM
व्योम snd_ak4531_suspend(काष्ठा snd_ak4531 *ak4531);
व्योम snd_ak4531_resume(काष्ठा snd_ak4531 *ak4531);
#पूर्ण_अगर

#पूर्ण_अगर /* __SOUND_AK4531_CODEC_H */
