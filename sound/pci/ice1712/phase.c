<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   ALSA driver क्रम ICEnsemble ICE1724 (Envy24)
 *
 *   Lowlevel functions क्रम Terratec PHASE 22
 *
 *	Copyright (c) 2005 Misha Zhilin <misha@epiphan.com>
 */

/* PHASE 22 overview:
 *   Audio controller: VIA Envy24HT-S (slightly trimmed करोwn Envy24HT, 4in/4out)
 *   Analog chip: AK4524 (partially via Philip's 74HCT125)
 *   Digital receiver: CS8414-CS (supported in this release)
 *		PHASE 22 revision 2.0 and Terrasoniq/Musonik TS22PCI have CS8416
 *		(support status unknown, please test and report)
 *
 *   Envy connects to AK4524
 *	- CS directly from GPIO 10
 *	- CCLK via 74HCT125's gate #4 from GPIO 4
 *	- CDTI via 74HCT125's gate #2 from GPIO 5
 *		CDTI may be completely blocked by 74HCT125's gate #1
 *		controlled by GPIO 3
 */

/* PHASE 28 overview:
 *   Audio controller: VIA Envy24HT (full untrimmed version, 4in/8out)
 *   Analog chip: WM8770 (8 channel 192k DAC, 2 channel 96k ADC)
 *   Digital receiver: CS8414-CS (supported in this release)
 */

#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>

#समावेश <sound/core.h>

#समावेश "ice1712.h"
#समावेश "envy24ht.h"
#समावेश "phase.h"
#समावेश <sound/tlv.h>

/* AC97 रेजिस्टर cache क्रम Phase28 */
काष्ठा phase28_spec अणु
	अचिन्हित लघु master[2];
	अचिन्हित लघु vol[8];
पूर्ण;

/* WM8770 रेजिस्टरs */
#घोषणा WM_DAC_ATTEN		0x00	/* DAC1-8 analog attenuation */
#घोषणा WM_DAC_MASTER_ATTEN	0x08	/* DAC master analog attenuation */
#घोषणा WM_DAC_DIG_ATTEN	0x09	/* DAC1-8 digital attenuation */
#घोषणा WM_DAC_DIG_MASTER_ATTEN	0x11	/* DAC master digital attenuation */
#घोषणा WM_PHASE_SWAP		0x12	/* DAC phase */
#घोषणा WM_DAC_CTRL1		0x13	/* DAC control bits */
#घोषणा WM_MUTE			0x14	/* mute controls */
#घोषणा WM_DAC_CTRL2		0x15	/* de-emphasis and zefo-flag */
#घोषणा WM_INT_CTRL		0x16	/* पूर्णांकerface control */
#घोषणा WM_MASTER		0x17	/* master घड़ी and mode */
#घोषणा WM_POWERDOWN		0x18	/* घातer-करोwn controls */
#घोषणा WM_ADC_GAIN		0x19	/* ADC gain L(19)/R(1a) */
#घोषणा WM_ADC_MUX		0x1b	/* input MUX */
#घोषणा WM_OUT_MUX1		0x1c	/* output MUX */
#घोषणा WM_OUT_MUX2		0x1e	/* output MUX */
#घोषणा WM_RESET		0x1f	/* software reset */


/*
 * Logarithmic volume values क्रम WM8770
 * Computed as 20 * Log10(255 / x)
 */
अटल स्थिर अचिन्हित अक्षर wm_vol[256] = अणु
	127, 48, 42, 39, 36, 34, 33, 31, 30, 29, 28, 27, 27, 26, 25, 25, 24,
	24, 23, 23, 22, 22, 21, 21, 21, 20, 20, 20, 19, 19, 19, 18, 18, 18, 18,
	17, 17, 17, 17, 16, 16, 16, 16, 15, 15, 15, 15, 15, 15, 14, 14, 14, 14,
	14, 13, 13, 13, 13, 13, 13, 13, 12, 12, 12, 12, 12, 12, 12, 11, 11, 11,
	11, 11, 11, 11, 11, 11, 10, 10, 10, 10, 10, 10, 10, 10, 10, 9, 9, 9, 9,
	9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 7, 7, 7, 7, 7,
	7, 7, 7, 7, 7, 7, 7, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 5, 5,
	5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
	4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
पूर्ण;

#घोषणा WM_VOL_MAX	(माप(wm_vol) - 1)
#घोषणा WM_VOL_MUTE	0x8000

अटल स्थिर काष्ठा snd_akm4xxx akm_phase22 = अणु
	.type = SND_AK4524,
	.num_dacs = 2,
	.num_adcs = 2,
पूर्ण;

अटल स्थिर काष्ठा snd_ak4xxx_निजी akm_phase22_priv = अणु
	.caddr =	2,
	.cअगर =		1,
	.data_mask =	1 << 4,
	.clk_mask =	1 << 5,
	.cs_mask =	1 << 10,
	.cs_addr =	1 << 10,
	.cs_none =	0,
	.add_flags = 	1 << 3,
	.mask_flags =	0,
पूर्ण;

अटल पूर्णांक phase22_init(काष्ठा snd_ice1712 *ice)
अणु
	काष्ठा snd_akm4xxx *ak;
	पूर्णांक err;

	/* Configure DAC/ADC description क्रम generic part of ice1724 */
	चयन (ice->eeprom.subvenकरोr) अणु
	हाल VT1724_SUBDEVICE_PHASE22:
	हाल VT1724_SUBDEVICE_TS22:
		ice->num_total_dacs = 2;
		ice->num_total_adcs = 2;
		ice->vt1720 = 1; /* Envy24HT-S have 16 bit wide GPIO */
		अवरोध;
	शेष:
		snd_BUG();
		वापस -EINVAL;
	पूर्ण

	/* Initialize analog chips */
	ice->akm = kzalloc(माप(काष्ठा snd_akm4xxx), GFP_KERNEL);
	ak = ice->akm;
	अगर (!ak)
		वापस -ENOMEM;
	ice->akm_codecs = 1;
	चयन (ice->eeprom.subvenकरोr) अणु
	हाल VT1724_SUBDEVICE_PHASE22:
	हाल VT1724_SUBDEVICE_TS22:
		err = snd_ice1712_akm4xxx_init(ak, &akm_phase22,
						&akm_phase22_priv, ice);
		अगर (err < 0)
			वापस err;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक phase22_add_controls(काष्ठा snd_ice1712 *ice)
अणु
	पूर्णांक err = 0;

	चयन (ice->eeprom.subvenकरोr) अणु
	हाल VT1724_SUBDEVICE_PHASE22:
	हाल VT1724_SUBDEVICE_TS22:
		err = snd_ice1712_akm4xxx_build_controls(ice);
		अगर (err < 0)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर अचिन्हित अक्षर phase22_eeprom[] = अणु
	[ICE_EEP2_SYSCONF]     = 0x28,  /* घड़ी 512, mpu 401,
					spdअगर-in/1xADC, 1xDACs */
	[ICE_EEP2_ACLINK]      = 0x80,	/* I2S */
	[ICE_EEP2_I2S]         = 0xf0,	/* vol, 96k, 24bit */
	[ICE_EEP2_SPDIF]       = 0xc3,	/* out-en, out-पूर्णांक, spdअगर-in */
	[ICE_EEP2_GPIO_सूची]    = 0xff,
	[ICE_EEP2_GPIO_सूची1]   = 0xff,
	[ICE_EEP2_GPIO_सूची2]   = 0xff,
	[ICE_EEP2_GPIO_MASK]   = 0x00,
	[ICE_EEP2_GPIO_MASK1]  = 0x00,
	[ICE_EEP2_GPIO_MASK2]  = 0x00,
	[ICE_EEP2_GPIO_STATE]  = 0x00,
	[ICE_EEP2_GPIO_STATE1] = 0x00,
	[ICE_EEP2_GPIO_STATE2] = 0x00,
पूर्ण;

अटल स्थिर अचिन्हित अक्षर phase28_eeprom[] = अणु
	[ICE_EEP2_SYSCONF]     = 0x2b,  /* घड़ी 512, mpu401,
					spdअगर-in/1xADC, 4xDACs */
	[ICE_EEP2_ACLINK]      = 0x80,	/* I2S */
	[ICE_EEP2_I2S]         = 0xfc,	/* vol, 96k, 24bit, 192k */
	[ICE_EEP2_SPDIF]       = 0xc3,	/* out-en, out-पूर्णांक, spdअगर-in */
	[ICE_EEP2_GPIO_सूची]    = 0xff,
	[ICE_EEP2_GPIO_सूची1]   = 0xff,
	[ICE_EEP2_GPIO_सूची2]   = 0x5f,
	[ICE_EEP2_GPIO_MASK]   = 0x00,
	[ICE_EEP2_GPIO_MASK1]  = 0x00,
	[ICE_EEP2_GPIO_MASK2]  = 0x00,
	[ICE_EEP2_GPIO_STATE]  = 0x00,
	[ICE_EEP2_GPIO_STATE1] = 0x00,
	[ICE_EEP2_GPIO_STATE2] = 0x00,
पूर्ण;

/*
 * ग_लिखो data in the SPI mode
 */
अटल व्योम phase28_spi_ग_लिखो(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक cs,
				अचिन्हित पूर्णांक data, पूर्णांक bits)
अणु
	अचिन्हित पूर्णांक पंचांगp;
	पूर्णांक i;

	पंचांगp = snd_ice1712_gpio_पढ़ो(ice);

	snd_ice1712_gpio_set_mask(ice, ~(PHASE28_WM_RW|PHASE28_SPI_MOSI|
					PHASE28_SPI_CLK|PHASE28_WM_CS));
	पंचांगp |= PHASE28_WM_RW;
	पंचांगp &= ~cs;
	snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
	udelay(1);

	क्रम (i = bits - 1; i >= 0; i--) अणु
		पंचांगp &= ~PHASE28_SPI_CLK;
		snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
		udelay(1);
		अगर (data & (1 << i))
			पंचांगp |= PHASE28_SPI_MOSI;
		अन्यथा
			पंचांगp &= ~PHASE28_SPI_MOSI;
		snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
		udelay(1);
		पंचांगp |= PHASE28_SPI_CLK;
		snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
		udelay(1);
	पूर्ण

	पंचांगp &= ~PHASE28_SPI_CLK;
	पंचांगp |= cs;
	snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
	udelay(1);
	पंचांगp |= PHASE28_SPI_CLK;
	snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
	udelay(1);
पूर्ण

/*
 * get the current रेजिस्टर value of WM codec
 */
अटल अचिन्हित लघु wm_get(काष्ठा snd_ice1712 *ice, पूर्णांक reg)
अणु
	reg <<= 1;
	वापस ((अचिन्हित लघु)ice->akm[0].images[reg] << 8) |
		ice->akm[0].images[reg + 1];
पूर्ण

/*
 * set the रेजिस्टर value of WM codec
 */
अटल व्योम wm_put_nocache(काष्ठा snd_ice1712 *ice, पूर्णांक reg, अचिन्हित लघु val)
अणु
	phase28_spi_ग_लिखो(ice, PHASE28_WM_CS, (reg << 9) | (val & 0x1ff), 16);
पूर्ण

/*
 * set the रेजिस्टर value of WM codec and remember it
 */
अटल व्योम wm_put(काष्ठा snd_ice1712 *ice, पूर्णांक reg, अचिन्हित लघु val)
अणु
	wm_put_nocache(ice, reg, val);
	reg <<= 1;
	ice->akm[0].images[reg] = val >> 8;
	ice->akm[0].images[reg + 1] = val;
पूर्ण

अटल व्योम wm_set_vol(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक index,
			अचिन्हित लघु vol, अचिन्हित लघु master)
अणु
	अचिन्हित अक्षर nvol;

	अगर ((master & WM_VOL_MUTE) || (vol & WM_VOL_MUTE))
		nvol = 0;
	अन्यथा
		nvol = 127 - wm_vol[(((vol & ~WM_VOL_MUTE) *
			(master & ~WM_VOL_MUTE)) / 127) & WM_VOL_MAX];

	wm_put(ice, index, nvol);
	wm_put_nocache(ice, index, 0x180 | nvol);
पूर्ण

/*
 * DAC mute control
 */
#घोषणा wm_pcm_mute_info	snd_ctl_boolean_mono_info

अटल पूर्णांक wm_pcm_mute_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);

	mutex_lock(&ice->gpio_mutex);
	ucontrol->value.पूर्णांकeger.value[0] = (wm_get(ice, WM_MUTE) & 0x10) ?
						0 : 1;
	mutex_unlock(&ice->gpio_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक wm_pcm_mute_put(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित लघु nval, oval;
	पूर्णांक change;

	snd_ice1712_save_gpio_status(ice);
	oval = wm_get(ice, WM_MUTE);
	nval = (oval & ~0x10) | (ucontrol->value.पूर्णांकeger.value[0] ? 0 : 0x10);
	change = (nval != oval);
	अगर (change)
		wm_put(ice, WM_MUTE, nval);
	snd_ice1712_restore_gpio_status(ice);

	वापस change;
पूर्ण

/*
 * Master volume attenuation mixer control
 */
अटल पूर्णांक wm_master_vol_info(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = WM_VOL_MAX;
	वापस 0;
पूर्ण

अटल पूर्णांक wm_master_vol_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	काष्ठा phase28_spec *spec = ice->spec;
	पूर्णांक i;
	क्रम (i = 0; i < 2; i++)
		ucontrol->value.पूर्णांकeger.value[i] = spec->master[i] &
							~WM_VOL_MUTE;
	वापस 0;
पूर्ण

अटल पूर्णांक wm_master_vol_put(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	काष्ठा phase28_spec *spec = ice->spec;
	पूर्णांक ch, change = 0;

	snd_ice1712_save_gpio_status(ice);
	क्रम (ch = 0; ch < 2; ch++) अणु
		अचिन्हित पूर्णांक vol = ucontrol->value.पूर्णांकeger.value[ch];
		अगर (vol > WM_VOL_MAX)
			जारी;
		vol |= spec->master[ch] & WM_VOL_MUTE;
		अगर (vol != spec->master[ch]) अणु
			पूर्णांक dac;
			spec->master[ch] = vol;
			क्रम (dac = 0; dac < ice->num_total_dacs; dac += 2)
				wm_set_vol(ice, WM_DAC_ATTEN + dac + ch,
					   spec->vol[dac + ch],
					   spec->master[ch]);
			change = 1;
		पूर्ण
	पूर्ण
	snd_ice1712_restore_gpio_status(ice);
	वापस change;
पूर्ण

अटल पूर्णांक phase28_init(काष्ठा snd_ice1712 *ice)
अणु
	अटल स्थिर अचिन्हित लघु wm_inits_phase28[] = अणु
		/* These come first to reduce init pop noise */
		0x1b, 0x044,	/* ADC Mux (AC'97 source) */
		0x1c, 0x00B,	/* Out Mux1 (VOUT1 = DAC+AUX, VOUT2 = DAC) */
		0x1d, 0x009,	/* Out Mux2 (VOUT2 = DAC, VOUT3 = DAC) */

		0x18, 0x000,	/* All घातer-up */

		0x16, 0x122,	/* I2S, normal polarity, 24bit */
		0x17, 0x022,	/* 256fs, slave mode */
		0x00, 0,	/* DAC1 analog mute */
		0x01, 0,	/* DAC2 analog mute */
		0x02, 0,	/* DAC3 analog mute */
		0x03, 0,	/* DAC4 analog mute */
		0x04, 0,	/* DAC5 analog mute */
		0x05, 0,	/* DAC6 analog mute */
		0x06, 0,	/* DAC7 analog mute */
		0x07, 0,	/* DAC8 analog mute */
		0x08, 0x100,	/* master analog mute */
		0x09, 0xff,	/* DAC1 digital full */
		0x0a, 0xff,	/* DAC2 digital full */
		0x0b, 0xff,	/* DAC3 digital full */
		0x0c, 0xff,	/* DAC4 digital full */
		0x0d, 0xff,	/* DAC5 digital full */
		0x0e, 0xff,	/* DAC6 digital full */
		0x0f, 0xff,	/* DAC7 digital full */
		0x10, 0xff,	/* DAC8 digital full */
		0x11, 0x1ff,	/* master digital full */
		0x12, 0x000,	/* phase normal */
		0x13, 0x090,	/* unmute DAC L/R */
		0x14, 0x000,	/* all unmute */
		0x15, 0x000,	/* no deemphasis, no ZFLG */
		0x19, 0x000,	/* -12dB ADC/L */
		0x1a, 0x000,	/* -12dB ADC/R */
		(अचिन्हित लघु)-1
	पूर्ण;

	अचिन्हित पूर्णांक पंचांगp;
	काष्ठा snd_akm4xxx *ak;
	काष्ठा phase28_spec *spec;
	स्थिर अचिन्हित लघु *p;
	पूर्णांक i;

	ice->num_total_dacs = 8;
	ice->num_total_adcs = 2;

	spec = kzalloc(माप(*spec), GFP_KERNEL);
	अगर (!spec)
		वापस -ENOMEM;
	ice->spec = spec;

	/* Initialize analog chips */
	ice->akm = kzalloc(माप(काष्ठा snd_akm4xxx), GFP_KERNEL);
	ak = ice->akm;
	अगर (!ak)
		वापस -ENOMEM;
	ice->akm_codecs = 1;

	snd_ice1712_gpio_set_dir(ice, 0x5fffff); /* fix this क्रम समय being */

	/* reset the wm codec as the SPI mode */
	snd_ice1712_save_gpio_status(ice);
	snd_ice1712_gpio_set_mask(ice, ~(PHASE28_WM_RESET|PHASE28_WM_CS|
					PHASE28_HP_SEL));

	पंचांगp = snd_ice1712_gpio_पढ़ो(ice);
	पंचांगp &= ~PHASE28_WM_RESET;
	snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
	udelay(1);
	पंचांगp |= PHASE28_WM_CS;
	snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
	udelay(1);
	पंचांगp |= PHASE28_WM_RESET;
	snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
	udelay(1);

	p = wm_inits_phase28;
	क्रम (; *p != (अचिन्हित लघु)-1; p += 2)
		wm_put(ice, p[0], p[1]);

	snd_ice1712_restore_gpio_status(ice);

	spec->master[0] = WM_VOL_MUTE;
	spec->master[1] = WM_VOL_MUTE;
	क्रम (i = 0; i < ice->num_total_dacs; i++) अणु
		spec->vol[i] = WM_VOL_MUTE;
		wm_set_vol(ice, i, spec->vol[i], spec->master[i % 2]);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * DAC volume attenuation mixer control
 */
अटल पूर्णांक wm_vol_info(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_info *uinfo)
अणु
	पूर्णांक voices = kcontrol->निजी_value >> 8;
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = voices;
	uinfo->value.पूर्णांकeger.min = 0;		/* mute (-101dB) */
	uinfo->value.पूर्णांकeger.max = 0x7F;	/* 0dB */
	वापस 0;
पूर्ण

अटल पूर्णांक wm_vol_get(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	काष्ठा phase28_spec *spec = ice->spec;
	पूर्णांक i, ofs, voices;

	voices = kcontrol->निजी_value >> 8;
	ofs = kcontrol->निजी_value & 0xff;
	क्रम (i = 0; i < voices; i++)
		ucontrol->value.पूर्णांकeger.value[i] =
			spec->vol[ofs+i] & ~WM_VOL_MUTE;
	वापस 0;
पूर्ण

अटल पूर्णांक wm_vol_put(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	काष्ठा phase28_spec *spec = ice->spec;
	पूर्णांक i, idx, ofs, voices;
	पूर्णांक change = 0;

	voices = kcontrol->निजी_value >> 8;
	ofs = kcontrol->निजी_value & 0xff;
	snd_ice1712_save_gpio_status(ice);
	क्रम (i = 0; i < voices; i++) अणु
		अचिन्हित पूर्णांक vol;
		vol = ucontrol->value.पूर्णांकeger.value[i];
		अगर (vol > 0x7f)
			जारी;
		vol |= spec->vol[ofs+i] & WM_VOL_MUTE;
		अगर (vol != spec->vol[ofs+i]) अणु
			spec->vol[ofs+i] = vol;
			idx  = WM_DAC_ATTEN + ofs + i;
			wm_set_vol(ice, idx, spec->vol[ofs+i],
				   spec->master[i]);
			change = 1;
		पूर्ण
	पूर्ण
	snd_ice1712_restore_gpio_status(ice);
	वापस change;
पूर्ण

/*
 * WM8770 mute control
 */
अटल पूर्णांक wm_mute_info(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_info *uinfo) अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_BOOLEAN;
	uinfo->count = kcontrol->निजी_value >> 8;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक wm_mute_get(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	काष्ठा phase28_spec *spec = ice->spec;
	पूर्णांक voices, ofs, i;

	voices = kcontrol->निजी_value >> 8;
	ofs = kcontrol->निजी_value & 0xFF;

	क्रम (i = 0; i < voices; i++)
		ucontrol->value.पूर्णांकeger.value[i] =
			(spec->vol[ofs+i] & WM_VOL_MUTE) ? 0 : 1;
	वापस 0;
पूर्ण

अटल पूर्णांक wm_mute_put(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	काष्ठा phase28_spec *spec = ice->spec;
	पूर्णांक change = 0, voices, ofs, i;

	voices = kcontrol->निजी_value >> 8;
	ofs = kcontrol->निजी_value & 0xFF;

	snd_ice1712_save_gpio_status(ice);
	क्रम (i = 0; i < voices; i++) अणु
		पूर्णांक val = (spec->vol[ofs + i] & WM_VOL_MUTE) ? 0 : 1;
		अगर (ucontrol->value.पूर्णांकeger.value[i] != val) अणु
			spec->vol[ofs + i] &= ~WM_VOL_MUTE;
			spec->vol[ofs + i] |=
				ucontrol->value.पूर्णांकeger.value[i] ? 0 :
				WM_VOL_MUTE;
			wm_set_vol(ice, ofs + i, spec->vol[ofs + i],
					spec->master[i]);
			change = 1;
		पूर्ण
	पूर्ण
	snd_ice1712_restore_gpio_status(ice);

	वापस change;
पूर्ण

/*
 * WM8770 master mute control
 */
#घोषणा wm_master_mute_info		snd_ctl_boolean_stereo_info

अटल पूर्णांक wm_master_mute_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	काष्ठा phase28_spec *spec = ice->spec;

	ucontrol->value.पूर्णांकeger.value[0] =
		(spec->master[0] & WM_VOL_MUTE) ? 0 : 1;
	ucontrol->value.पूर्णांकeger.value[1] =
		(spec->master[1] & WM_VOL_MUTE) ? 0 : 1;
	वापस 0;
पूर्ण

अटल पूर्णांक wm_master_mute_put(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	काष्ठा phase28_spec *spec = ice->spec;
	पूर्णांक change = 0, i;

	snd_ice1712_save_gpio_status(ice);
	क्रम (i = 0; i < 2; i++) अणु
		पूर्णांक val = (spec->master[i] & WM_VOL_MUTE) ? 0 : 1;
		अगर (ucontrol->value.पूर्णांकeger.value[i] != val) अणु
			पूर्णांक dac;
			spec->master[i] &= ~WM_VOL_MUTE;
			spec->master[i] |=
				ucontrol->value.पूर्णांकeger.value[i] ? 0 :
				WM_VOL_MUTE;
			क्रम (dac = 0; dac < ice->num_total_dacs; dac += 2)
				wm_set_vol(ice, WM_DAC_ATTEN + dac + i,
						spec->vol[dac + i],
						spec->master[i]);
			change = 1;
		पूर्ण
	पूर्ण
	snd_ice1712_restore_gpio_status(ice);

	वापस change;
पूर्ण

/* digital master volume */
#घोषणा PCM_0dB 0xff
#घोषणा PCM_RES 128	/* -64dB */
#घोषणा PCM_MIN (PCM_0dB - PCM_RES)
अटल पूर्णांक wm_pcm_vol_info(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;		/* mute (-64dB) */
	uinfo->value.पूर्णांकeger.max = PCM_RES;	/* 0dB */
	वापस 0;
पूर्ण

अटल पूर्णांक wm_pcm_vol_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित लघु val;

	mutex_lock(&ice->gpio_mutex);
	val = wm_get(ice, WM_DAC_DIG_MASTER_ATTEN) & 0xff;
	val = val > PCM_MIN ? (val - PCM_MIN) : 0;
	ucontrol->value.पूर्णांकeger.value[0] = val;
	mutex_unlock(&ice->gpio_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक wm_pcm_vol_put(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित लघु ovol, nvol;
	पूर्णांक change = 0;

	nvol = ucontrol->value.पूर्णांकeger.value[0];
	अगर (nvol > PCM_RES)
		वापस -EINVAL;
	snd_ice1712_save_gpio_status(ice);
	nvol = (nvol ? (nvol + PCM_MIN) : 0) & 0xff;
	ovol = wm_get(ice, WM_DAC_DIG_MASTER_ATTEN) & 0xff;
	अगर (ovol != nvol) अणु
		wm_put(ice, WM_DAC_DIG_MASTER_ATTEN, nvol); /* prelatch */
		/* update */
		wm_put_nocache(ice, WM_DAC_DIG_MASTER_ATTEN, nvol | 0x100);
		change = 1;
	पूर्ण
	snd_ice1712_restore_gpio_status(ice);
	वापस change;
पूर्ण

/*
 * Deemphasis
 */
#घोषणा phase28_deemp_info	snd_ctl_boolean_mono_info

अटल पूर्णांक phase28_deemp_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	ucontrol->value.पूर्णांकeger.value[0] = (wm_get(ice, WM_DAC_CTRL2) & 0xf) ==
						0xf;
	वापस 0;
पूर्ण

अटल पूर्णांक phase28_deemp_put(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	पूर्णांक temp, temp2;
	temp = wm_get(ice, WM_DAC_CTRL2);
	temp2 = temp;
	अगर (ucontrol->value.पूर्णांकeger.value[0])
		temp |= 0xf;
	अन्यथा
		temp &= ~0xf;
	अगर (temp != temp2) अणु
		wm_put(ice, WM_DAC_CTRL2, temp);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * ADC Oversampling
 */
अटल पूर्णांक phase28_oversampling_info(काष्ठा snd_kcontrol *k,
					काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[2] = अणु "128x", "64x"	पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 2, texts);
पूर्ण

अटल पूर्णांक phase28_oversampling_get(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	ucontrol->value.क्रमागतerated.item[0] = (wm_get(ice, WM_MASTER) & 0x8) ==
						0x8;
	वापस 0;
पूर्ण

अटल पूर्णांक phase28_oversampling_put(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	पूर्णांक temp, temp2;
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);

	temp = wm_get(ice, WM_MASTER);
	temp2 = temp;

	अगर (ucontrol->value.क्रमागतerated.item[0])
		temp |= 0x8;
	अन्यथा
		temp &= ~0x8;

	अगर (temp != temp2) अणु
		wm_put(ice, WM_MASTER, temp);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_wm_dac, -12700, 100, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_wm_pcm, -6400, 50, 1);

अटल स्थिर काष्ठा snd_kcontrol_new phase28_dac_controls[] = अणु
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Master Playback Switch",
		.info = wm_master_mute_info,
		.get = wm_master_mute_get,
		.put = wm_master_mute_put
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.access = (SNDRV_CTL_ELEM_ACCESS_READWRITE |
			   SNDRV_CTL_ELEM_ACCESS_TLV_READ),
		.name = "Master Playback Volume",
		.info = wm_master_vol_info,
		.get = wm_master_vol_get,
		.put = wm_master_vol_put,
		.tlv = अणु .p = db_scale_wm_dac पूर्ण
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Front Playback Switch",
		.info = wm_mute_info,
		.get = wm_mute_get,
		.put = wm_mute_put,
		.निजी_value = (2 << 8) | 0
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.access = (SNDRV_CTL_ELEM_ACCESS_READWRITE |
			   SNDRV_CTL_ELEM_ACCESS_TLV_READ),
		.name = "Front Playback Volume",
		.info = wm_vol_info,
		.get = wm_vol_get,
		.put = wm_vol_put,
		.निजी_value = (2 << 8) | 0,
		.tlv = अणु .p = db_scale_wm_dac पूर्ण
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Rear Playback Switch",
		.info = wm_mute_info,
		.get = wm_mute_get,
		.put = wm_mute_put,
		.निजी_value = (2 << 8) | 2
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.access = (SNDRV_CTL_ELEM_ACCESS_READWRITE |
			   SNDRV_CTL_ELEM_ACCESS_TLV_READ),
		.name = "Rear Playback Volume",
		.info = wm_vol_info,
		.get = wm_vol_get,
		.put = wm_vol_put,
		.निजी_value = (2 << 8) | 2,
		.tlv = अणु .p = db_scale_wm_dac पूर्ण
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Center Playback Switch",
		.info = wm_mute_info,
		.get = wm_mute_get,
		.put = wm_mute_put,
		.निजी_value = (1 << 8) | 4
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.access = (SNDRV_CTL_ELEM_ACCESS_READWRITE |
			   SNDRV_CTL_ELEM_ACCESS_TLV_READ),
		.name = "Center Playback Volume",
		.info = wm_vol_info,
		.get = wm_vol_get,
		.put = wm_vol_put,
		.निजी_value = (1 << 8) | 4,
		.tlv = अणु .p = db_scale_wm_dac पूर्ण
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "LFE Playback Switch",
		.info = wm_mute_info,
		.get = wm_mute_get,
		.put = wm_mute_put,
		.निजी_value = (1 << 8) | 5
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.access = (SNDRV_CTL_ELEM_ACCESS_READWRITE |
			   SNDRV_CTL_ELEM_ACCESS_TLV_READ),
		.name = "LFE Playback Volume",
		.info = wm_vol_info,
		.get = wm_vol_get,
		.put = wm_vol_put,
		.निजी_value = (1 << 8) | 5,
		.tlv = अणु .p = db_scale_wm_dac पूर्ण
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Side Playback Switch",
		.info = wm_mute_info,
		.get = wm_mute_get,
		.put = wm_mute_put,
		.निजी_value = (2 << 8) | 6
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.access = (SNDRV_CTL_ELEM_ACCESS_READWRITE |
			   SNDRV_CTL_ELEM_ACCESS_TLV_READ),
		.name = "Side Playback Volume",
		.info = wm_vol_info,
		.get = wm_vol_get,
		.put = wm_vol_put,
		.निजी_value = (2 << 8) | 6,
		.tlv = अणु .p = db_scale_wm_dac पूर्ण
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new wm_controls[] = अणु
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "PCM Playback Switch",
		.info = wm_pcm_mute_info,
		.get = wm_pcm_mute_get,
		.put = wm_pcm_mute_put
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.access = (SNDRV_CTL_ELEM_ACCESS_READWRITE |
			   SNDRV_CTL_ELEM_ACCESS_TLV_READ),
		.name = "PCM Playback Volume",
		.info = wm_pcm_vol_info,
		.get = wm_pcm_vol_get,
		.put = wm_pcm_vol_put,
		.tlv = अणु .p = db_scale_wm_pcm पूर्ण
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "DAC Deemphasis Switch",
		.info = phase28_deemp_info,
		.get = phase28_deemp_get,
		.put = phase28_deemp_put
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "ADC Oversampling",
		.info = phase28_oversampling_info,
		.get = phase28_oversampling_get,
		.put = phase28_oversampling_put
	पूर्ण
पूर्ण;

अटल पूर्णांक phase28_add_controls(काष्ठा snd_ice1712 *ice)
अणु
	अचिन्हित पूर्णांक i, counts;
	पूर्णांक err;

	counts = ARRAY_SIZE(phase28_dac_controls);
	क्रम (i = 0; i < counts; i++) अणु
		err = snd_ctl_add(ice->card,
					snd_ctl_new1(&phase28_dac_controls[i],
							ice));
		अगर (err < 0)
			वापस err;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(wm_controls); i++) अणु
		err = snd_ctl_add(ice->card,
					snd_ctl_new1(&wm_controls[i], ice));
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा snd_ice1712_card_info snd_vt1724_phase_cards[] = अणु
	अणु
		.subvenकरोr = VT1724_SUBDEVICE_PHASE22,
		.name = "Terratec PHASE 22",
		.model = "phase22",
		.chip_init = phase22_init,
		.build_controls = phase22_add_controls,
		.eeprom_size = माप(phase22_eeprom),
		.eeprom_data = phase22_eeprom,
	पूर्ण,
	अणु
		.subvenकरोr = VT1724_SUBDEVICE_PHASE28,
		.name = "Terratec PHASE 28",
		.model = "phase28",
		.chip_init = phase28_init,
		.build_controls = phase28_add_controls,
		.eeprom_size = माप(phase28_eeprom),
		.eeprom_data = phase28_eeprom,
	पूर्ण,
	अणु
		.subvenकरोr = VT1724_SUBDEVICE_TS22,
		.name = "Terrasoniq TS22 PCI",
		.model = "TS22",
		.chip_init = phase22_init,
		.build_controls = phase22_add_controls,
		.eeprom_size = माप(phase22_eeprom),
		.eeprom_data = phase22_eeprom,
	पूर्ण,
	अणु पूर्ण /* terminator */
पूर्ण;
