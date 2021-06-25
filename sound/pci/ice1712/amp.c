<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   ALSA driver क्रम ICEnsemble VT1724 (Envy24HT)
 *
 *   Lowlevel functions क्रम Advanced Micro Peripherals Ltd AUDIO2000
 *
 *	Copyright (c) 2000 Jaroslav Kysela <perex@perex.cz>
 */      

#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <sound/core.h>

#समावेश "ice1712.h"
#समावेश "envy24ht.h"
#समावेश "amp.h"

अटल व्योम wm_put(काष्ठा snd_ice1712 *ice, पूर्णांक reg, अचिन्हित लघु val)
अणु
	अचिन्हित लघु cval;
	cval = (reg << 9) | val;
	snd_vt1724_ग_लिखो_i2c(ice, WM_DEV, cval >> 8, cval & 0xff);
पूर्ण

अटल पूर्णांक snd_vt1724_amp_init(काष्ठा snd_ice1712 *ice)
अणु
	अटल स्थिर अचिन्हित लघु wm_inits[] = अणु
		WM_ATTEN_L,	0x0000,	/* 0 db */
		WM_ATTEN_R,	0x0000,	/* 0 db */
		WM_DAC_CTRL,	0x0008,	/* 24bit I2S */
		WM_INT_CTRL,	0x0001, /* 24bit I2S */	
	पूर्ण;

	अचिन्हित पूर्णांक i;

	/* only use basic functionality क्रम now */

	/* VT1616 6ch codec connected to PSDOUT0 using packed mode */
	ice->num_total_dacs = 6;
	ice->num_total_adcs = 2;

	/* Chaपूर्णांकech AV-710 has another WM8728 codec connected to PSDOUT4
	   (shared with the SPDIF output). Mixer control क्रम this codec
	   is not yet supported. */
	अगर (ice->eeprom.subvenकरोr == VT1724_SUBDEVICE_AV710) अणु
		क्रम (i = 0; i < ARRAY_SIZE(wm_inits); i += 2)
			wm_put(ice, wm_inits[i], wm_inits[i+1]);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_vt1724_amp_add_controls(काष्ठा snd_ice1712 *ice)
अणु
	अगर (ice->ac97)
		/* we use pins 39 and 41 of the VT1616 क्रम left and right
		पढ़ो outमाला_दो */
		snd_ac97_ग_लिखो_cache(ice->ac97, 0x5a,
			snd_ac97_पढ़ो(ice->ac97, 0x5a) & ~0x8000);
	वापस 0;
पूर्ण


/* entry poपूर्णांक */
काष्ठा snd_ice1712_card_info snd_vt1724_amp_cards[] = अणु
	अणु
		.subvenकरोr = VT1724_SUBDEVICE_AV710,
		.name = "Chaintech AV-710",
		.model = "av710",
		.chip_init = snd_vt1724_amp_init,
		.build_controls = snd_vt1724_amp_add_controls,
	पूर्ण,
	अणु
		.subvenकरोr = VT1724_SUBDEVICE_AUDIO2000,
		.name = "AMP Ltd AUDIO2000",
		.model = "amp2000",
		.chip_init = snd_vt1724_amp_init,
		.build_controls = snd_vt1724_amp_add_controls,
	पूर्ण,
	अणु पूर्ण /* terminator */
पूर्ण;

