<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   ALSA driver क्रम ICEnsemble VT1724 (Envy24HT)
 *
 *   Lowlevel functions क्रम Audiotrak Prodigy 7.1 Hअगरi
 *   based on pontis.c
 *
 *      Copyright (c) 2007 Julian Scheel <julian@jusst.de>
 *      Copyright (c) 2007 allank
 *      Copyright (c) 2004 Takashi Iwai <tiwai@suse.de>
 */


#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>

#समावेश <sound/core.h>
#समावेश <sound/info.h>
#समावेश <sound/tlv.h>

#समावेश "ice1712.h"
#समावेश "envy24ht.h"
#समावेश "prodigy_hifi.h"

काष्ठा prodigy_hअगरi_spec अणु
	अचिन्हित लघु master[2];
	अचिन्हित लघु vol[8];
पूर्ण;

/* I2C addresses */
#घोषणा WM_DEV		0x34

/* WM8776 रेजिस्टरs */
#घोषणा WM_HP_ATTEN_L		0x00	/* headphone left attenuation */
#घोषणा WM_HP_ATTEN_R		0x01	/* headphone left attenuation */
#घोषणा WM_HP_MASTER		0x02	/* headphone master (both channels),
						override LLR */
#घोषणा WM_DAC_ATTEN_L		0x03	/* digital left attenuation */
#घोषणा WM_DAC_ATTEN_R		0x04
#घोषणा WM_DAC_MASTER		0x05
#घोषणा WM_PHASE_SWAP		0x06	/* DAC phase swap */
#घोषणा WM_DAC_CTRL1		0x07
#घोषणा WM_DAC_MUTE		0x08
#घोषणा WM_DAC_CTRL2		0x09
#घोषणा WM_DAC_INT		0x0a
#घोषणा WM_ADC_INT		0x0b
#घोषणा WM_MASTER_CTRL		0x0c
#घोषणा WM_POWERDOWN		0x0d
#घोषणा WM_ADC_ATTEN_L		0x0e
#घोषणा WM_ADC_ATTEN_R		0x0f
#घोषणा WM_ALC_CTRL1		0x10
#घोषणा WM_ALC_CTRL2		0x11
#घोषणा WM_ALC_CTRL3		0x12
#घोषणा WM_NOISE_GATE		0x13
#घोषणा WM_LIMITER		0x14
#घोषणा WM_ADC_MUX		0x15
#घोषणा WM_OUT_MUX		0x16
#घोषणा WM_RESET		0x17

/* Analog Recording Source :- Mic, LineIn, CD/Video, */

/* implement capture source select control क्रम WM8776 */

#घोषणा WM_AIN1 "AIN1"
#घोषणा WM_AIN2 "AIN2"
#घोषणा WM_AIN3 "AIN3"
#घोषणा WM_AIN4 "AIN4"
#घोषणा WM_AIN5 "AIN5"

/* GPIO pins of envy24ht connected to wm8766 */
#घोषणा WM8766_SPI_CLK	 (1<<17) /* CLK, Pin97 on ICE1724 */
#घोषणा WM8766_SPI_MD	  (1<<16) /* DATA VT1724 -> WM8766, Pin96 */
#घोषणा WM8766_SPI_ML	  (1<<18) /* Latch, Pin98 */

/* WM8766 रेजिस्टरs */
#घोषणा WM8766_DAC_CTRL	 0x02   /* DAC Control */
#घोषणा WM8766_INT_CTRL	 0x03   /* Interface Control */
#घोषणा WM8766_DAC_CTRL2	0x09
#घोषणा WM8766_DAC_CTRL3	0x0a
#घोषणा WM8766_RESET	    0x1f
#घोषणा WM8766_LDA1	     0x00
#घोषणा WM8766_LDA2	     0x04
#घोषणा WM8766_LDA3	     0x06
#घोषणा WM8766_RDA1	     0x01
#घोषणा WM8766_RDA2	     0x05
#घोषणा WM8766_RDA3	     0x07
#घोषणा WM8766_MUTE1	    0x0C
#घोषणा WM8766_MUTE2	    0x0F


/*
 * Prodigy HD2
 */
#घोषणा AK4396_ADDR    0x00
#घोषणा AK4396_CSN    (1 << 8)    /* CSN->GPIO8, pin 75 */
#घोषणा AK4396_CCLK   (1 << 9)    /* CCLK->GPIO9, pin 76 */
#घोषणा AK4396_CDTI   (1 << 10)   /* CDTI->GPIO10, pin 77 */

/* ak4396 रेजिस्टरs */
#घोषणा AK4396_CTRL1	    0x00
#घोषणा AK4396_CTRL2	    0x01
#घोषणा AK4396_CTRL3	    0x02
#घोषणा AK4396_LCH_ATT	  0x03
#घोषणा AK4396_RCH_ATT	  0x04


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
 * set the रेजिस्टर value of WM codec and remember it
 */
अटल व्योम wm_put_nocache(काष्ठा snd_ice1712 *ice, पूर्णांक reg, अचिन्हित लघु val)
अणु
	अचिन्हित लघु cval;
	cval = (reg << 9) | val;
	snd_vt1724_ग_लिखो_i2c(ice, WM_DEV, cval >> 8, cval & 0xff);
पूर्ण

अटल व्योम wm_put(काष्ठा snd_ice1712 *ice, पूर्णांक reg, अचिन्हित लघु val)
अणु
	wm_put_nocache(ice, reg, val);
	reg <<= 1;
	ice->akm[0].images[reg] = val >> 8;
	ice->akm[0].images[reg + 1] = val;
पूर्ण

/*
 * ग_लिखो data in the SPI mode
 */

अटल व्योम set_gpio_bit(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक bit, पूर्णांक val)
अणु
	अचिन्हित पूर्णांक पंचांगp = snd_ice1712_gpio_पढ़ो(ice);
	अगर (val)
		पंचांगp |= bit;
	अन्यथा
		पंचांगp &= ~bit;
	snd_ice1712_gpio_ग_लिखो(ice, पंचांगp);
पूर्ण

/*
 * SPI implementation क्रम WM8766 codec - only writing supported, no पढ़ोback
 */

अटल व्योम wm8766_spi_send_word(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक data)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < 16; i++) अणु
		set_gpio_bit(ice, WM8766_SPI_CLK, 0);
		udelay(1);
		set_gpio_bit(ice, WM8766_SPI_MD, data & 0x8000);
		udelay(1);
		set_gpio_bit(ice, WM8766_SPI_CLK, 1);
		udelay(1);
		data <<= 1;
	पूर्ण
पूर्ण

अटल व्योम wm8766_spi_ग_लिखो(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक reg,
			     अचिन्हित पूर्णांक data)
अणु
	अचिन्हित पूर्णांक block;

	snd_ice1712_gpio_set_dir(ice, WM8766_SPI_MD|
					WM8766_SPI_CLK|WM8766_SPI_ML);
	snd_ice1712_gpio_set_mask(ice, ~(WM8766_SPI_MD|
					WM8766_SPI_CLK|WM8766_SPI_ML));
	/* latch must be low when writing */
	set_gpio_bit(ice, WM8766_SPI_ML, 0);
	block = (reg << 9) | (data & 0x1ff);
	wm8766_spi_send_word(ice, block); /* REGISTER ADDRESS */
	/* release latch */
	set_gpio_bit(ice, WM8766_SPI_ML, 1);
	udelay(1);
	/* restore */
	snd_ice1712_gpio_set_mask(ice, ice->gpio.ग_लिखो_mask);
	snd_ice1712_gpio_set_dir(ice, ice->gpio.direction);
पूर्ण


/*
 * serial पूर्णांकerface क्रम ak4396 - only writing supported, no पढ़ोback
 */

अटल व्योम ak4396_send_word(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक data)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < 16; i++) अणु
		set_gpio_bit(ice, AK4396_CCLK, 0);
		udelay(1);
		set_gpio_bit(ice, AK4396_CDTI, data & 0x8000);
		udelay(1);
		set_gpio_bit(ice, AK4396_CCLK, 1);
		udelay(1);
		data <<= 1;
	पूर्ण
पूर्ण

अटल व्योम ak4396_ग_लिखो(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक reg,
			 अचिन्हित पूर्णांक data)
अणु
	अचिन्हित पूर्णांक block;

	snd_ice1712_gpio_set_dir(ice, AK4396_CSN|AK4396_CCLK|AK4396_CDTI);
	snd_ice1712_gpio_set_mask(ice, ~(AK4396_CSN|AK4396_CCLK|AK4396_CDTI));
	/* latch must be low when writing */
	set_gpio_bit(ice, AK4396_CSN, 0); 
	block =  ((AK4396_ADDR & 0x03) << 14) | (1 << 13) |
			((reg & 0x1f) << 8) | (data & 0xff);
	ak4396_send_word(ice, block); /* REGISTER ADDRESS */
	/* release latch */
	set_gpio_bit(ice, AK4396_CSN, 1);
	udelay(1);
	/* restore */
	snd_ice1712_gpio_set_mask(ice, ice->gpio.ग_लिखो_mask);
	snd_ice1712_gpio_set_dir(ice, ice->gpio.direction);
पूर्ण


/*
 * ak4396 mixers
 */



/*
 * DAC volume attenuation mixer control (-64dB to 0dB)
 */

अटल पूर्णांक ak4396_dac_vol_info(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;   /* mute */
	uinfo->value.पूर्णांकeger.max = 0xFF; /* linear */
	वापस 0;
पूर्ण

अटल पूर्णांक ak4396_dac_vol_get(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	काष्ठा prodigy_hअगरi_spec *spec = ice->spec;
	पूर्णांक i;
	
	क्रम (i = 0; i < 2; i++)
		ucontrol->value.पूर्णांकeger.value[i] = spec->vol[i];

	वापस 0;
पूर्ण

अटल पूर्णांक ak4396_dac_vol_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	काष्ठा prodigy_hअगरi_spec *spec = ice->spec;
	पूर्णांक i;
	पूर्णांक change = 0;
	
	mutex_lock(&ice->gpio_mutex);
	क्रम (i = 0; i < 2; i++) अणु
		अगर (ucontrol->value.पूर्णांकeger.value[i] != spec->vol[i]) अणु
			spec->vol[i] = ucontrol->value.पूर्णांकeger.value[i];
			ak4396_ग_लिखो(ice, AK4396_LCH_ATT + i,
				     spec->vol[i] & 0xff);
			change = 1;
		पूर्ण
	पूर्ण
	mutex_unlock(&ice->gpio_mutex);
	वापस change;
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_wm_dac, -12700, 100, 1);
अटल स्थिर DECLARE_TLV_DB_LINEAR(ak4396_db_scale, TLV_DB_GAIN_MUTE, 0);

अटल स्थिर काष्ठा snd_kcontrol_new prodigy_hd2_controls[] = अणु
    अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.access = (SNDRV_CTL_ELEM_ACCESS_READWRITE |
		SNDRV_CTL_ELEM_ACCESS_TLV_READ),
	.name = "Front Playback Volume",
	.info = ak4396_dac_vol_info,
	.get = ak4396_dac_vol_get,
	.put = ak4396_dac_vol_put,
	.tlv = अणु .p = ak4396_db_scale पूर्ण,
    पूर्ण,
पूर्ण;


/* --------------- */

#घोषणा WM_VOL_MAX	255
#घोषणा WM_VOL_MUTE	0x8000


#घोषणा DAC_0dB	0xff
#घोषणा DAC_RES	128
#घोषणा DAC_MIN	(DAC_0dB - DAC_RES)


अटल व्योम wm_set_vol(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक index,
		       अचिन्हित लघु vol, अचिन्हित लघु master)
अणु
	अचिन्हित अक्षर nvol;
	
	अगर ((master & WM_VOL_MUTE) || (vol & WM_VOL_MUTE))
		nvol = 0;
	अन्यथा अणु
		nvol = (((vol & ~WM_VOL_MUTE) * (master & ~WM_VOL_MUTE)) / 128)
				& WM_VOL_MAX;
		nvol = (nvol ? (nvol + DAC_MIN) : 0) & 0xff;
	पूर्ण
	
	wm_put(ice, index, nvol);
	wm_put_nocache(ice, index, 0x100 | nvol);
पूर्ण

अटल व्योम wm8766_set_vol(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक index,
			   अचिन्हित लघु vol, अचिन्हित लघु master)
अणु
	अचिन्हित अक्षर nvol;
	
	अगर ((master & WM_VOL_MUTE) || (vol & WM_VOL_MUTE))
		nvol = 0;
	अन्यथा अणु
		nvol = (((vol & ~WM_VOL_MUTE) * (master & ~WM_VOL_MUTE)) / 128)
				& WM_VOL_MAX;
		nvol = (nvol ? (nvol + DAC_MIN) : 0) & 0xff;
	पूर्ण

	wm8766_spi_ग_लिखो(ice, index, (0x0100 | nvol));
पूर्ण


/*
 * DAC volume attenuation mixer control (-64dB to 0dB)
 */

अटल पूर्णांक wm_dac_vol_info(काष्ठा snd_kcontrol *kcontrol,
			   काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;	/* mute */
	uinfo->value.पूर्णांकeger.max = DAC_RES;	/* 0dB, 0.5dB step */
	वापस 0;
पूर्ण

अटल पूर्णांक wm_dac_vol_get(काष्ठा snd_kcontrol *kcontrol,
			  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	काष्ठा prodigy_hअगरi_spec *spec = ice->spec;
	पूर्णांक i;

	क्रम (i = 0; i < 2; i++)
		ucontrol->value.पूर्णांकeger.value[i] =
			spec->vol[2 + i] & ~WM_VOL_MUTE;
	वापस 0;
पूर्ण

अटल पूर्णांक wm_dac_vol_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	काष्ठा prodigy_hअगरi_spec *spec = ice->spec;
	पूर्णांक i, idx, change = 0;

	mutex_lock(&ice->gpio_mutex);
	क्रम (i = 0; i < 2; i++) अणु
		अगर (ucontrol->value.पूर्णांकeger.value[i] != spec->vol[2 + i]) अणु
			idx = WM_DAC_ATTEN_L + i;
			spec->vol[2 + i] &= WM_VOL_MUTE;
			spec->vol[2 + i] |= ucontrol->value.पूर्णांकeger.value[i];
			wm_set_vol(ice, idx, spec->vol[2 + i], spec->master[i]);
			change = 1;
		पूर्ण
	पूर्ण
	mutex_unlock(&ice->gpio_mutex);
	वापस change;
पूर्ण


/*
 * WM8766 DAC volume attenuation mixer control
 */
अटल पूर्णांक wm8766_vol_info(काष्ठा snd_kcontrol *kcontrol,
			   काष्ठा snd_ctl_elem_info *uinfo)
अणु
	पूर्णांक voices = kcontrol->निजी_value >> 8;
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = voices;
	uinfo->value.पूर्णांकeger.min = 0;		/* mute */
	uinfo->value.पूर्णांकeger.max = DAC_RES;	/* 0dB */
	वापस 0;
पूर्ण

अटल पूर्णांक wm8766_vol_get(काष्ठा snd_kcontrol *kcontrol,
			  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	काष्ठा prodigy_hअगरi_spec *spec = ice->spec;
	पूर्णांक i, ofs, voices;

	voices = kcontrol->निजी_value >> 8;
	ofs = kcontrol->निजी_value & 0xff;
	क्रम (i = 0; i < voices; i++)
		ucontrol->value.पूर्णांकeger.value[i] = spec->vol[ofs + i];
	वापस 0;
पूर्ण

अटल पूर्णांक wm8766_vol_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	काष्ठा prodigy_hअगरi_spec *spec = ice->spec;
	पूर्णांक i, idx, ofs, voices;
	पूर्णांक change = 0;

	voices = kcontrol->निजी_value >> 8;
	ofs = kcontrol->निजी_value & 0xff;
	mutex_lock(&ice->gpio_mutex);
	क्रम (i = 0; i < voices; i++) अणु
		अगर (ucontrol->value.पूर्णांकeger.value[i] != spec->vol[ofs + i]) अणु
			idx = WM8766_LDA1 + ofs + i;
			spec->vol[ofs + i] &= WM_VOL_MUTE;
			spec->vol[ofs + i] |= ucontrol->value.पूर्णांकeger.value[i];
			wm8766_set_vol(ice, idx,
				       spec->vol[ofs + i], spec->master[i]);
			change = 1;
		पूर्ण
	पूर्ण
	mutex_unlock(&ice->gpio_mutex);
	वापस change;
पूर्ण

/*
 * Master volume attenuation mixer control / applied to WM8776+WM8766
 */
अटल पूर्णांक wm_master_vol_info(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = DAC_RES;
	वापस 0;
पूर्ण

अटल पूर्णांक wm_master_vol_get(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	काष्ठा prodigy_hअगरi_spec *spec = ice->spec;
	पूर्णांक i;
	क्रम (i = 0; i < 2; i++)
		ucontrol->value.पूर्णांकeger.value[i] = spec->master[i];
	वापस 0;
पूर्ण

अटल पूर्णांक wm_master_vol_put(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	काष्ठा prodigy_hअगरi_spec *spec = ice->spec;
	पूर्णांक ch, change = 0;

	mutex_lock(&ice->gpio_mutex);
	क्रम (ch = 0; ch < 2; ch++) अणु
		अगर (ucontrol->value.पूर्णांकeger.value[ch] != spec->master[ch]) अणु
			spec->master[ch] = ucontrol->value.पूर्णांकeger.value[ch];

			/* Apply to front DAC */
			wm_set_vol(ice, WM_DAC_ATTEN_L + ch,
				   spec->vol[2 + ch], spec->master[ch]);

			wm8766_set_vol(ice, WM8766_LDA1 + ch,
				       spec->vol[0 + ch], spec->master[ch]);

			wm8766_set_vol(ice, WM8766_LDA2 + ch,
				       spec->vol[4 + ch], spec->master[ch]);

			wm8766_set_vol(ice, WM8766_LDA3 + ch,
				       spec->vol[6 + ch], spec->master[ch]);
			change = 1;
		पूर्ण
	पूर्ण
	mutex_unlock(&ice->gpio_mutex);	
	वापस change;
पूर्ण


/* KONSTI */

अटल पूर्णांक wm_adc_mux_क्रमागत_info(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[32] = अणु
		"NULL", WM_AIN1, WM_AIN2, WM_AIN1 "+" WM_AIN2,
		WM_AIN3, WM_AIN1 "+" WM_AIN3, WM_AIN2 "+" WM_AIN3,
		WM_AIN1 "+" WM_AIN2 "+" WM_AIN3,
		WM_AIN4, WM_AIN1 "+" WM_AIN4, WM_AIN2 "+" WM_AIN4,
		WM_AIN1 "+" WM_AIN2 "+" WM_AIN4,
		WM_AIN3 "+" WM_AIN4, WM_AIN1 "+" WM_AIN3 "+" WM_AIN4,
		WM_AIN2 "+" WM_AIN3 "+" WM_AIN4,
		WM_AIN1 "+" WM_AIN2 "+" WM_AIN3 "+" WM_AIN4,
		WM_AIN5, WM_AIN1 "+" WM_AIN5, WM_AIN2 "+" WM_AIN5,
		WM_AIN1 "+" WM_AIN2 "+" WM_AIN5,
		WM_AIN3 "+" WM_AIN5, WM_AIN1 "+" WM_AIN3 "+" WM_AIN5,
		WM_AIN2 "+" WM_AIN3 "+" WM_AIN5,
		WM_AIN1 "+" WM_AIN2 "+" WM_AIN3 "+" WM_AIN5,
		WM_AIN4 "+" WM_AIN5, WM_AIN1 "+" WM_AIN4 "+" WM_AIN5,
		WM_AIN2 "+" WM_AIN4 "+" WM_AIN5,
		WM_AIN1 "+" WM_AIN2 "+" WM_AIN4 "+" WM_AIN5,
		WM_AIN3 "+" WM_AIN4 "+" WM_AIN5,
		WM_AIN1 "+" WM_AIN3 "+" WM_AIN4 "+" WM_AIN5,
		WM_AIN2 "+" WM_AIN3 "+" WM_AIN4 "+" WM_AIN5,
		WM_AIN1 "+" WM_AIN2 "+" WM_AIN3 "+" WM_AIN4 "+" WM_AIN5
	पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 32, texts);
पूर्ण

अटल पूर्णांक wm_adc_mux_क्रमागत_get(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);

	mutex_lock(&ice->gpio_mutex);
	ucontrol->value.क्रमागतerated.item[0] = wm_get(ice, WM_ADC_MUX) & 0x1f;
	mutex_unlock(&ice->gpio_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक wm_adc_mux_क्रमागत_put(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित लघु oval, nval;
	पूर्णांक change = 0;

	mutex_lock(&ice->gpio_mutex);
	oval = wm_get(ice, WM_ADC_MUX);
	nval = (oval & 0xe0) | ucontrol->value.क्रमागतerated.item[0];
	अगर (nval != oval) अणु
		wm_put(ice, WM_ADC_MUX, nval);
		change = 1;
	पूर्ण
	mutex_unlock(&ice->gpio_mutex);
	वापस change;
पूर्ण

/* KONSTI */

/*
 * ADC gain mixer control (-64dB to 0dB)
 */

#घोषणा ADC_0dB	0xcf
#घोषणा ADC_RES	128
#घोषणा ADC_MIN	(ADC_0dB - ADC_RES)

अटल पूर्णांक wm_adc_vol_info(काष्ठा snd_kcontrol *kcontrol,
			   काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;	/* mute (-64dB) */
	uinfo->value.पूर्णांकeger.max = ADC_RES;	/* 0dB, 0.5dB step */
	वापस 0;
पूर्ण

अटल पूर्णांक wm_adc_vol_get(काष्ठा snd_kcontrol *kcontrol,
			  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित लघु val;
	पूर्णांक i;

	mutex_lock(&ice->gpio_mutex);
	क्रम (i = 0; i < 2; i++) अणु
		val = wm_get(ice, WM_ADC_ATTEN_L + i) & 0xff;
		val = val > ADC_MIN ? (val - ADC_MIN) : 0;
		ucontrol->value.पूर्णांकeger.value[i] = val;
	पूर्ण
	mutex_unlock(&ice->gpio_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक wm_adc_vol_put(काष्ठा snd_kcontrol *kcontrol,
			  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित लघु ovol, nvol;
	पूर्णांक i, idx, change = 0;

	mutex_lock(&ice->gpio_mutex);
	क्रम (i = 0; i < 2; i++) अणु
		nvol = ucontrol->value.पूर्णांकeger.value[i];
		nvol = nvol ? (nvol + ADC_MIN) : 0;
		idx  = WM_ADC_ATTEN_L + i;
		ovol = wm_get(ice, idx) & 0xff;
		अगर (ovol != nvol) अणु
			wm_put(ice, idx, nvol);
			change = 1;
		पूर्ण
	पूर्ण
	mutex_unlock(&ice->gpio_mutex);
	वापस change;
पूर्ण

/*
 * ADC input mux mixer control
 */
#घोषणा wm_adc_mux_info		snd_ctl_boolean_mono_info

अटल पूर्णांक wm_adc_mux_get(काष्ठा snd_kcontrol *kcontrol,
			  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	पूर्णांक bit = kcontrol->निजी_value;

	mutex_lock(&ice->gpio_mutex);
	ucontrol->value.पूर्णांकeger.value[0] =
		(wm_get(ice, WM_ADC_MUX) & (1 << bit)) ? 1 : 0;
	mutex_unlock(&ice->gpio_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक wm_adc_mux_put(काष्ठा snd_kcontrol *kcontrol,
			  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	पूर्णांक bit = kcontrol->निजी_value;
	अचिन्हित लघु oval, nval;
	पूर्णांक change;

	mutex_lock(&ice->gpio_mutex);
	nval = oval = wm_get(ice, WM_ADC_MUX);
	अगर (ucontrol->value.पूर्णांकeger.value[0])
		nval |= (1 << bit);
	अन्यथा
		nval &= ~(1 << bit);
	change = nval != oval;
	अगर (change) अणु
		wm_put(ice, WM_ADC_MUX, nval);
	पूर्ण
	mutex_unlock(&ice->gpio_mutex);
	वापस 0;
पूर्ण

/*
 * Analog bypass (In -> Out)
 */
#घोषणा wm_bypass_info		snd_ctl_boolean_mono_info

अटल पूर्णांक wm_bypass_get(काष्ठा snd_kcontrol *kcontrol,
			 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);

	mutex_lock(&ice->gpio_mutex);
	ucontrol->value.पूर्णांकeger.value[0] =
		(wm_get(ice, WM_OUT_MUX) & 0x04) ? 1 : 0;
	mutex_unlock(&ice->gpio_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक wm_bypass_put(काष्ठा snd_kcontrol *kcontrol,
			 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित लघु val, oval;
	पूर्णांक change = 0;

	mutex_lock(&ice->gpio_mutex);
	val = oval = wm_get(ice, WM_OUT_MUX);
	अगर (ucontrol->value.पूर्णांकeger.value[0])
		val |= 0x04;
	अन्यथा
		val &= ~0x04;
	अगर (val != oval) अणु
		wm_put(ice, WM_OUT_MUX, val);
		change = 1;
	पूर्ण
	mutex_unlock(&ice->gpio_mutex);
	वापस change;
पूर्ण

/*
 * Left/Right swap
 */
#घोषणा wm_chswap_info		snd_ctl_boolean_mono_info

अटल पूर्णांक wm_chswap_get(काष्ठा snd_kcontrol *kcontrol,
			 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);

	mutex_lock(&ice->gpio_mutex);
	ucontrol->value.पूर्णांकeger.value[0] =
			(wm_get(ice, WM_DAC_CTRL1) & 0xf0) != 0x90;
	mutex_unlock(&ice->gpio_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक wm_chswap_put(काष्ठा snd_kcontrol *kcontrol,
			 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित लघु val, oval;
	पूर्णांक change = 0;

	mutex_lock(&ice->gpio_mutex);
	oval = wm_get(ice, WM_DAC_CTRL1);
	val = oval & 0x0f;
	अगर (ucontrol->value.पूर्णांकeger.value[0])
		val |= 0x60;
	अन्यथा
		val |= 0x90;
	अगर (val != oval) अणु
		wm_put(ice, WM_DAC_CTRL1, val);
		wm_put_nocache(ice, WM_DAC_CTRL1, val);
		change = 1;
	पूर्ण
	mutex_unlock(&ice->gpio_mutex);
	वापस change;
पूर्ण


/*
 * mixers
 */

अटल स्थिर काष्ठा snd_kcontrol_new prodigy_hअगरi_controls[] = अणु
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
		.access = (SNDRV_CTL_ELEM_ACCESS_READWRITE |
			   SNDRV_CTL_ELEM_ACCESS_TLV_READ),
		.name = "Front Playback Volume",
		.info = wm_dac_vol_info,
		.get = wm_dac_vol_get,
		.put = wm_dac_vol_put,
		.tlv = अणु .p = db_scale_wm_dac पूर्ण,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.access = (SNDRV_CTL_ELEM_ACCESS_READWRITE |
			   SNDRV_CTL_ELEM_ACCESS_TLV_READ),
		.name = "Rear Playback Volume",
		.info = wm8766_vol_info,
		.get = wm8766_vol_get,
		.put = wm8766_vol_put,
		.निजी_value = (2 << 8) | 0,
		.tlv = अणु .p = db_scale_wm_dac पूर्ण,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.access = (SNDRV_CTL_ELEM_ACCESS_READWRITE |
			   SNDRV_CTL_ELEM_ACCESS_TLV_READ),
		.name = "Center Playback Volume",
		.info = wm8766_vol_info,
		.get = wm8766_vol_get,
		.put = wm8766_vol_put,
		.निजी_value = (1 << 8) | 4,
		.tlv = अणु .p = db_scale_wm_dac पूर्ण
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.access = (SNDRV_CTL_ELEM_ACCESS_READWRITE |
			   SNDRV_CTL_ELEM_ACCESS_TLV_READ),
		.name = "LFE Playback Volume",
		.info = wm8766_vol_info,
		.get = wm8766_vol_get,
		.put = wm8766_vol_put,
		.निजी_value = (1 << 8) | 5,
		.tlv = अणु .p = db_scale_wm_dac पूर्ण
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.access = (SNDRV_CTL_ELEM_ACCESS_READWRITE |
			   SNDRV_CTL_ELEM_ACCESS_TLV_READ),
		.name = "Side Playback Volume",
		.info = wm8766_vol_info,
		.get = wm8766_vol_get,
		.put = wm8766_vol_put,
		.निजी_value = (2 << 8) | 6,
		.tlv = अणु .p = db_scale_wm_dac पूर्ण,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.access = (SNDRV_CTL_ELEM_ACCESS_READWRITE |
			   SNDRV_CTL_ELEM_ACCESS_TLV_READ),
		.name = "Capture Volume",
		.info = wm_adc_vol_info,
		.get = wm_adc_vol_get,
		.put = wm_adc_vol_put,
		.tlv = अणु .p = db_scale_wm_dac पूर्ण,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "CD Capture Switch",
		.info = wm_adc_mux_info,
		.get = wm_adc_mux_get,
		.put = wm_adc_mux_put,
		.निजी_value = 0,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Line Capture Switch",
		.info = wm_adc_mux_info,
		.get = wm_adc_mux_get,
		.put = wm_adc_mux_put,
		.निजी_value = 1,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Analog Bypass Switch",
		.info = wm_bypass_info,
		.get = wm_bypass_get,
		.put = wm_bypass_put,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Swap Output Channels",
		.info = wm_chswap_info,
		.get = wm_chswap_get,
		.put = wm_chswap_put,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Analog Capture Source",
		.info = wm_adc_mux_क्रमागत_info,
		.get = wm_adc_mux_क्रमागत_get,
		.put = wm_adc_mux_क्रमागत_put,
	पूर्ण,
पूर्ण;

/*
 * WM codec रेजिस्टरs
 */
अटल व्योम wm_proc_regs_ग_लिखो(काष्ठा snd_info_entry *entry,
			       काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_ice1712 *ice = entry->निजी_data;
	अक्षर line[64];
	अचिन्हित पूर्णांक reg, val;
	mutex_lock(&ice->gpio_mutex);
	जबतक (!snd_info_get_line(buffer, line, माप(line))) अणु
		अगर (माला_पूछो(line, "%x %x", &reg, &val) != 2)
			जारी;
		अगर (reg <= 0x17 && val <= 0xffff)
			wm_put(ice, reg, val);
	पूर्ण
	mutex_unlock(&ice->gpio_mutex);
पूर्ण

अटल व्योम wm_proc_regs_पढ़ो(काष्ठा snd_info_entry *entry,
			      काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_ice1712 *ice = entry->निजी_data;
	पूर्णांक reg, val;

	mutex_lock(&ice->gpio_mutex);
	क्रम (reg = 0; reg <= 0x17; reg++) अणु
		val = wm_get(ice, reg);
		snd_iम_लिखो(buffer, "%02x = %04x\n", reg, val);
	पूर्ण
	mutex_unlock(&ice->gpio_mutex);
पूर्ण

अटल व्योम wm_proc_init(काष्ठा snd_ice1712 *ice)
अणु
	snd_card_rw_proc_new(ice->card, "wm_codec", ice, wm_proc_regs_पढ़ो,
			     wm_proc_regs_ग_लिखो);
पूर्ण

अटल पूर्णांक prodigy_hअगरi_add_controls(काष्ठा snd_ice1712 *ice)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 0; i < ARRAY_SIZE(prodigy_hअगरi_controls); i++) अणु
		err = snd_ctl_add(ice->card,
				  snd_ctl_new1(&prodigy_hअगरi_controls[i], ice));
		अगर (err < 0)
			वापस err;
	पूर्ण

	wm_proc_init(ice);

	वापस 0;
पूर्ण

अटल पूर्णांक prodigy_hd2_add_controls(काष्ठा snd_ice1712 *ice)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 0; i < ARRAY_SIZE(prodigy_hd2_controls); i++) अणु
		err = snd_ctl_add(ice->card,
				  snd_ctl_new1(&prodigy_hd2_controls[i], ice));
		अगर (err < 0)
			वापस err;
	पूर्ण

	wm_proc_init(ice);

	वापस 0;
पूर्ण

अटल व्योम wm8766_init(काष्ठा snd_ice1712 *ice)
अणु
	अटल स्थिर अचिन्हित लघु wm8766_inits[] = अणु
		WM8766_RESET,	   0x0000,
		WM8766_DAC_CTRL,	0x0120,
		WM8766_INT_CTRL,	0x0022, /* I2S Normal Mode, 24 bit */
		WM8766_DAC_CTRL2,       0x0001,
		WM8766_DAC_CTRL3,       0x0080,
		WM8766_LDA1,	    0x0100,
		WM8766_LDA2,	    0x0100,
		WM8766_LDA3,	    0x0100,
		WM8766_RDA1,	    0x0100,
		WM8766_RDA2,	    0x0100,
		WM8766_RDA3,	    0x0100,
		WM8766_MUTE1,	   0x0000,
		WM8766_MUTE2,	   0x0000,
	पूर्ण;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(wm8766_inits); i += 2)
		wm8766_spi_ग_लिखो(ice, wm8766_inits[i], wm8766_inits[i + 1]);
पूर्ण

अटल व्योम wm8776_init(काष्ठा snd_ice1712 *ice)
अणु
	अटल स्थिर अचिन्हित लघु wm8776_inits[] = अणु
		/* These come first to reduce init pop noise */
		WM_ADC_MUX,	0x0003,	/* ADC mute */
		/* 0x00c0 replaced by 0x0003 */
		
		WM_DAC_MUTE,	0x0001,	/* DAC sofपंचांगute */
		WM_DAC_CTRL1,	0x0000,	/* DAC mute */

		WM_POWERDOWN,	0x0008,	/* All घातer-up except HP */
		WM_RESET,	0x0000,	/* reset */
	पूर्ण;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(wm8776_inits); i += 2)
		wm_put(ice, wm8776_inits[i], wm8776_inits[i + 1]);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक prodigy_hअगरi_resume(काष्ठा snd_ice1712 *ice)
अणु
	अटल स्थिर अचिन्हित लघु wm8776_reinit_रेजिस्टरs[] = अणु
		WM_MASTER_CTRL,
		WM_DAC_INT,
		WM_ADC_INT,
		WM_OUT_MUX,
		WM_HP_ATTEN_L,
		WM_HP_ATTEN_R,
		WM_PHASE_SWAP,
		WM_DAC_CTRL2,
		WM_ADC_ATTEN_L,
		WM_ADC_ATTEN_R,
		WM_ALC_CTRL1,
		WM_ALC_CTRL2,
		WM_ALC_CTRL3,
		WM_NOISE_GATE,
		WM_ADC_MUX,
		/* no DAC attenuation here */
	पूर्ण;
	काष्ठा prodigy_hअगरi_spec *spec = ice->spec;
	पूर्णांक i, ch;

	mutex_lock(&ice->gpio_mutex);

	/* reinitialize WM8776 and re-apply old रेजिस्टर values */
	wm8776_init(ice);
	schedule_समयout_unपूर्णांकerruptible(1);
	क्रम (i = 0; i < ARRAY_SIZE(wm8776_reinit_रेजिस्टरs); i++)
		wm_put(ice, wm8776_reinit_रेजिस्टरs[i],
		       wm_get(ice, wm8776_reinit_रेजिस्टरs[i]));

	/* reinitialize WM8766 and re-apply volumes क्रम all DACs */
	wm8766_init(ice);
	क्रम (ch = 0; ch < 2; ch++) अणु
		wm_set_vol(ice, WM_DAC_ATTEN_L + ch,
			   spec->vol[2 + ch], spec->master[ch]);

		wm8766_set_vol(ice, WM8766_LDA1 + ch,
			       spec->vol[0 + ch], spec->master[ch]);

		wm8766_set_vol(ice, WM8766_LDA2 + ch,
			       spec->vol[4 + ch], spec->master[ch]);

		wm8766_set_vol(ice, WM8766_LDA3 + ch,
			       spec->vol[6 + ch], spec->master[ch]);
	पूर्ण

	/* unmute WM8776 DAC */
	wm_put(ice, WM_DAC_MUTE, 0x00);
	wm_put(ice, WM_DAC_CTRL1, 0x90);

	mutex_unlock(&ice->gpio_mutex);
	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * initialize the chip
 */
अटल पूर्णांक prodigy_hअगरi_init(काष्ठा snd_ice1712 *ice)
अणु
	अटल स्थिर अचिन्हित लघु wm8776_शेषs[] = अणु
		WM_MASTER_CTRL,  0x0022, /* 256fs, slave mode */
		WM_DAC_INT,	0x0022,	/* I2S, normal polarity, 24bit */
		WM_ADC_INT,	0x0022,	/* I2S, normal polarity, 24bit */
		WM_DAC_CTRL1,	0x0090,	/* DAC L/R */
		WM_OUT_MUX,	0x0001,	/* OUT DAC */
		WM_HP_ATTEN_L,	0x0179,	/* HP 0dB */
		WM_HP_ATTEN_R,	0x0179,	/* HP 0dB */
		WM_DAC_ATTEN_L,	0x0000,	/* DAC 0dB */
		WM_DAC_ATTEN_L,	0x0100,	/* DAC 0dB */
		WM_DAC_ATTEN_R,	0x0000,	/* DAC 0dB */
		WM_DAC_ATTEN_R,	0x0100,	/* DAC 0dB */
		WM_PHASE_SWAP,	0x0000,	/* phase normal */
#अगर 0
		WM_DAC_MASTER,	0x0100,	/* DAC master muted */
#पूर्ण_अगर
		WM_DAC_CTRL2,	0x0000,	/* no deemphasis, no ZFLG */
		WM_ADC_ATTEN_L,	0x0000,	/* ADC muted */
		WM_ADC_ATTEN_R,	0x0000,	/* ADC muted */
#अगर 1
		WM_ALC_CTRL1,	0x007b,	/* */
		WM_ALC_CTRL2,	0x0000,	/* */
		WM_ALC_CTRL3,	0x0000,	/* */
		WM_NOISE_GATE,	0x0000,	/* */
#पूर्ण_अगर
		WM_DAC_MUTE,	0x0000,	/* DAC unmute */
		WM_ADC_MUX,	0x0003,	/* ADC unmute, both CD/Line On */
	पूर्ण;
	काष्ठा prodigy_hअगरi_spec *spec;
	अचिन्हित पूर्णांक i;

	ice->vt1720 = 0;
	ice->vt1724 = 1;

	ice->num_total_dacs = 8;
	ice->num_total_adcs = 1;

	/* HACK - use this as the SPDIF source.
	* करोn't call snd_ice1712_gpio_get/put(), otherwise it's overwritten
	*/
	ice->gpio.saved[0] = 0;
	/* to remember the रेजिस्टर values */

	ice->akm = kzalloc(माप(काष्ठा snd_akm4xxx), GFP_KERNEL);
	अगर (! ice->akm)
		वापस -ENOMEM;
	ice->akm_codecs = 1;

	spec = kzalloc(माप(*spec), GFP_KERNEL);
	अगर (!spec)
		वापस -ENOMEM;
	ice->spec = spec;

	/* initialize WM8776 codec */
	wm8776_init(ice);
	schedule_समयout_unपूर्णांकerruptible(1);
	क्रम (i = 0; i < ARRAY_SIZE(wm8776_शेषs); i += 2)
		wm_put(ice, wm8776_शेषs[i], wm8776_शेषs[i + 1]);

	wm8766_init(ice);

#अगर_घोषित CONFIG_PM_SLEEP
	ice->pm_resume = &prodigy_hअगरi_resume;
	ice->pm_suspend_enabled = 1;
#पूर्ण_अगर

	वापस 0;
पूर्ण


/*
 * initialize the chip
 */
अटल व्योम ak4396_init(काष्ठा snd_ice1712 *ice)
अणु
	अटल स्थिर अचिन्हित लघु ak4396_inits[] = अणु
		AK4396_CTRL1,	   0x87,   /* I2S Normal Mode, 24 bit */
		AK4396_CTRL2,	   0x02,
		AK4396_CTRL3,	   0x00, 
		AK4396_LCH_ATT,	 0x00,
		AK4396_RCH_ATT,	 0x00,
	पूर्ण;

	अचिन्हित पूर्णांक i;

	/* initialize ak4396 codec */
	/* reset codec */
	ak4396_ग_लिखो(ice, AK4396_CTRL1, 0x86);
	msleep(100);
	ak4396_ग_लिखो(ice, AK4396_CTRL1, 0x87);

	क्रम (i = 0; i < ARRAY_SIZE(ak4396_inits); i += 2)
		ak4396_ग_लिखो(ice, ak4396_inits[i], ak4396_inits[i+1]);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक prodigy_hd2_resume(काष्ठा snd_ice1712 *ice)
अणु
	/* initialize ak4396 codec and restore previous mixer volumes */
	काष्ठा prodigy_hअगरi_spec *spec = ice->spec;
	पूर्णांक i;
	mutex_lock(&ice->gpio_mutex);
	ak4396_init(ice);
	क्रम (i = 0; i < 2; i++)
		ak4396_ग_लिखो(ice, AK4396_LCH_ATT + i, spec->vol[i] & 0xff);
	mutex_unlock(&ice->gpio_mutex);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक prodigy_hd2_init(काष्ठा snd_ice1712 *ice)
अणु
	काष्ठा prodigy_hअगरi_spec *spec;

	ice->vt1720 = 0;
	ice->vt1724 = 1;

	ice->num_total_dacs = 1;
	ice->num_total_adcs = 1;

	/* HACK - use this as the SPDIF source.
	* करोn't call snd_ice1712_gpio_get/put(), otherwise it's overwritten
	*/
	ice->gpio.saved[0] = 0;
	/* to remember the रेजिस्टर values */

	ice->akm = kzalloc(माप(काष्ठा snd_akm4xxx), GFP_KERNEL);
	अगर (! ice->akm)
		वापस -ENOMEM;
	ice->akm_codecs = 1;

	spec = kzalloc(माप(*spec), GFP_KERNEL);
	अगर (!spec)
		वापस -ENOMEM;
	ice->spec = spec;

#अगर_घोषित CONFIG_PM_SLEEP
	ice->pm_resume = &prodigy_hd2_resume;
	ice->pm_suspend_enabled = 1;
#पूर्ण_अगर

	ak4396_init(ice);

	वापस 0;
पूर्ण


अटल स्थिर अचिन्हित अक्षर prodigy71hअगरi_eeprom[] = अणु
	0x4b,   /* SYSCONF: घड़ी 512, spdअगर-in/ADC, 4DACs */
	0x80,   /* ACLINK: I2S */
	0xfc,   /* I2S: vol, 96k, 24bit, 192k */
	0xc3,   /* SPDIF: out-en, out-पूर्णांक, spdअगर-in */
	0xff,   /* GPIO_सूची */
	0xff,   /* GPIO_सूची1 */
	0x5f,   /* GPIO_सूची2 */
	0x00,   /* GPIO_MASK */
	0x00,   /* GPIO_MASK1 */
	0x00,   /* GPIO_MASK2 */
	0x00,   /* GPIO_STATE */
	0x00,   /* GPIO_STATE1 */
	0x00,   /* GPIO_STATE2 */
पूर्ण;

अटल स्थिर अचिन्हित अक्षर prodigyhd2_eeprom[] = अणु
	0x4b,   /* SYSCONF: घड़ी 512, spdअगर-in/ADC, 4DACs */
	0x80,   /* ACLINK: I2S */
	0xfc,   /* I2S: vol, 96k, 24bit, 192k */
	0xc3,   /* SPDIF: out-en, out-पूर्णांक, spdअगर-in */
	0xff,   /* GPIO_सूची */
	0xff,   /* GPIO_सूची1 */
	0x5f,   /* GPIO_सूची2 */
	0x00,   /* GPIO_MASK */
	0x00,   /* GPIO_MASK1 */
	0x00,   /* GPIO_MASK2 */
	0x00,   /* GPIO_STATE */
	0x00,   /* GPIO_STATE1 */
	0x00,   /* GPIO_STATE2 */
पूर्ण;

अटल स्थिर अचिन्हित अक्षर क्रमtissimo4_eeprom[] = अणु
	0x43,   /* SYSCONF: घड़ी 512, ADC, 4DACs */	
	0x80,   /* ACLINK: I2S */
	0xfc,   /* I2S: vol, 96k, 24bit, 192k */
	0xc1,   /* SPDIF: out-en, out-पूर्णांक */
	0xff,   /* GPIO_सूची */
	0xff,   /* GPIO_सूची1 */
	0x5f,   /* GPIO_सूची2 */
	0x00,   /* GPIO_MASK */
	0x00,   /* GPIO_MASK1 */
	0x00,   /* GPIO_MASK2 */
	0x00,   /* GPIO_STATE */
	0x00,   /* GPIO_STATE1 */
	0x00,   /* GPIO_STATE2 */
पूर्ण;

/* entry poपूर्णांक */
काष्ठा snd_ice1712_card_info snd_vt1724_prodigy_hअगरi_cards[] = अणु
	अणु
		.subvenकरोr = VT1724_SUBDEVICE_PRODIGY_HIFI,
		.name = "Audiotrak Prodigy 7.1 HiFi",
		.model = "prodigy71hifi",
		.chip_init = prodigy_hअगरi_init,
		.build_controls = prodigy_hअगरi_add_controls,
		.eeprom_size = माप(prodigy71hअगरi_eeprom),
		.eeprom_data = prodigy71hअगरi_eeprom,
		.driver = "Prodigy71HIFI",
	पूर्ण,
	अणु
	.subvenकरोr = VT1724_SUBDEVICE_PRODIGY_HD2,
	.name = "Audiotrak Prodigy HD2",
	.model = "prodigyhd2",
	.chip_init = prodigy_hd2_init,
	.build_controls = prodigy_hd2_add_controls,
	.eeprom_size = माप(prodigyhd2_eeprom),
	.eeprom_data = prodigyhd2_eeprom,
	.driver = "Prodigy71HD2",
	पूर्ण,
	अणु
		.subvenकरोr = VT1724_SUBDEVICE_FORTISSIMO4,
		.name = "Hercules Fortissimo IV",
		.model = "fortissimo4",
		.chip_init = prodigy_hअगरi_init,
		.build_controls = prodigy_hअगरi_add_controls,
		.eeprom_size = माप(क्रमtissimo4_eeprom),
		.eeprom_data = क्रमtissimo4_eeprom,
		.driver = "Fortissimo4",
	पूर्ण,
	अणु पूर्ण /* terminator */
पूर्ण;

