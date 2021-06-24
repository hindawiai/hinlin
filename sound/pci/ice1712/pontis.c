<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   ALSA driver क्रम ICEnsemble VT1724 (Envy24HT)
 *
 *   Lowlevel functions क्रम Pontis MS300
 *
 *	Copyright (c) 2004 Takashi Iwai <tiwai@suse.de>
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
#समावेश "pontis.h"

/* I2C addresses */
#घोषणा WM_DEV		0x34
#घोषणा CS_DEV		0x20

/* WM8776 रेजिस्टरs */
#घोषणा WM_HP_ATTEN_L		0x00	/* headphone left attenuation */
#घोषणा WM_HP_ATTEN_R		0x01	/* headphone left attenuation */
#घोषणा WM_HP_MASTER		0x02	/* headphone master (both channels) */
					/* override LLR */
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

/*
 * GPIO
 */
#घोषणा PONTIS_CS_CS		(1<<4)	/* CS */
#घोषणा PONTIS_CS_CLK		(1<<5)	/* CLK */
#घोषणा PONTIS_CS_RDATA		(1<<6)	/* CS8416 -> VT1720 */
#घोषणा PONTIS_CS_WDATA		(1<<7)	/* VT1720 -> CS8416 */


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
 * DAC volume attenuation mixer control (-64dB to 0dB)
 */

#घोषणा DAC_0dB	0xff
#घोषणा DAC_RES	128
#घोषणा DAC_MIN	(DAC_0dB - DAC_RES)

अटल पूर्णांक wm_dac_vol_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;	/* mute */
	uinfo->value.पूर्णांकeger.max = DAC_RES;	/* 0dB, 0.5dB step */
	वापस 0;
पूर्ण

अटल पूर्णांक wm_dac_vol_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित लघु val;
	पूर्णांक i;

	mutex_lock(&ice->gpio_mutex);
	क्रम (i = 0; i < 2; i++) अणु
		val = wm_get(ice, WM_DAC_ATTEN_L + i) & 0xff;
		val = val > DAC_MIN ? (val - DAC_MIN) : 0;
		ucontrol->value.पूर्णांकeger.value[i] = val;
	पूर्ण
	mutex_unlock(&ice->gpio_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक wm_dac_vol_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित लघु oval, nval;
	पूर्णांक i, idx, change = 0;

	mutex_lock(&ice->gpio_mutex);
	क्रम (i = 0; i < 2; i++) अणु
		nval = ucontrol->value.पूर्णांकeger.value[i];
		nval = (nval ? (nval + DAC_MIN) : 0) & 0xff;
		idx = WM_DAC_ATTEN_L + i;
		oval = wm_get(ice, idx) & 0xff;
		अगर (oval != nval) अणु
			wm_put(ice, idx, nval);
			wm_put_nocache(ice, idx, nval | 0x100);
			change = 1;
		पूर्ण
	पूर्ण
	mutex_unlock(&ice->gpio_mutex);
	वापस change;
पूर्ण

/*
 * ADC gain mixer control (-64dB to 0dB)
 */

#घोषणा ADC_0dB	0xcf
#घोषणा ADC_RES	128
#घोषणा ADC_MIN	(ADC_0dB - ADC_RES)

अटल पूर्णांक wm_adc_vol_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;	/* mute (-64dB) */
	uinfo->value.पूर्णांकeger.max = ADC_RES;	/* 0dB, 0.5dB step */
	वापस 0;
पूर्ण

अटल पूर्णांक wm_adc_vol_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
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

अटल पूर्णांक wm_adc_vol_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
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

अटल पूर्णांक wm_adc_mux_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	पूर्णांक bit = kcontrol->निजी_value;

	mutex_lock(&ice->gpio_mutex);
	ucontrol->value.पूर्णांकeger.value[0] = (wm_get(ice, WM_ADC_MUX) & (1 << bit)) ? 1 : 0;
	mutex_unlock(&ice->gpio_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक wm_adc_mux_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
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
	वापस change;
पूर्ण

/*
 * Analog bypass (In -> Out)
 */
#घोषणा wm_bypass_info		snd_ctl_boolean_mono_info

अटल पूर्णांक wm_bypass_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);

	mutex_lock(&ice->gpio_mutex);
	ucontrol->value.पूर्णांकeger.value[0] = (wm_get(ice, WM_OUT_MUX) & 0x04) ? 1 : 0;
	mutex_unlock(&ice->gpio_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक wm_bypass_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
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

अटल पूर्णांक wm_chswap_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);

	mutex_lock(&ice->gpio_mutex);
	ucontrol->value.पूर्णांकeger.value[0] = (wm_get(ice, WM_DAC_CTRL1) & 0xf0) != 0x90;
	mutex_unlock(&ice->gpio_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक wm_chswap_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
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

अटल व्योम spi_send_byte(काष्ठा snd_ice1712 *ice, अचिन्हित अक्षर data)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < 8; i++) अणु
		set_gpio_bit(ice, PONTIS_CS_CLK, 0);
		udelay(1);
		set_gpio_bit(ice, PONTIS_CS_WDATA, data & 0x80);
		udelay(1);
		set_gpio_bit(ice, PONTIS_CS_CLK, 1);
		udelay(1);
		data <<= 1;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक spi_पढ़ो_byte(काष्ठा snd_ice1712 *ice)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक val = 0;

	क्रम (i = 0; i < 8; i++) अणु
		val <<= 1;
		set_gpio_bit(ice, PONTIS_CS_CLK, 0);
		udelay(1);
		अगर (snd_ice1712_gpio_पढ़ो(ice) & PONTIS_CS_RDATA)
			val |= 1;
		udelay(1);
		set_gpio_bit(ice, PONTIS_CS_CLK, 1);
		udelay(1);
	पूर्ण
	वापस val;
पूर्ण


अटल व्योम spi_ग_लिखो(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक dev, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक data)
अणु
	snd_ice1712_gpio_set_dir(ice, PONTIS_CS_CS|PONTIS_CS_WDATA|PONTIS_CS_CLK);
	snd_ice1712_gpio_set_mask(ice, ~(PONTIS_CS_CS|PONTIS_CS_WDATA|PONTIS_CS_CLK));
	set_gpio_bit(ice, PONTIS_CS_CS, 0);
	spi_send_byte(ice, dev & ~1); /* WRITE */
	spi_send_byte(ice, reg); /* MAP */
	spi_send_byte(ice, data); /* DATA */
	/* trigger */
	set_gpio_bit(ice, PONTIS_CS_CS, 1);
	udelay(1);
	/* restore */
	snd_ice1712_gpio_set_mask(ice, ice->gpio.ग_लिखो_mask);
	snd_ice1712_gpio_set_dir(ice, ice->gpio.direction);
पूर्ण

अटल अचिन्हित पूर्णांक spi_पढ़ो(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक dev, अचिन्हित पूर्णांक reg)
अणु
	अचिन्हित पूर्णांक val;
	snd_ice1712_gpio_set_dir(ice, PONTIS_CS_CS|PONTIS_CS_WDATA|PONTIS_CS_CLK);
	snd_ice1712_gpio_set_mask(ice, ~(PONTIS_CS_CS|PONTIS_CS_WDATA|PONTIS_CS_CLK));
	set_gpio_bit(ice, PONTIS_CS_CS, 0);
	spi_send_byte(ice, dev & ~1); /* WRITE */
	spi_send_byte(ice, reg); /* MAP */
	/* trigger */
	set_gpio_bit(ice, PONTIS_CS_CS, 1);
	udelay(1);
	set_gpio_bit(ice, PONTIS_CS_CS, 0);
	spi_send_byte(ice, dev | 1); /* READ */
	val = spi_पढ़ो_byte(ice);
	/* trigger */
	set_gpio_bit(ice, PONTIS_CS_CS, 1);
	udelay(1);
	/* restore */
	snd_ice1712_gpio_set_mask(ice, ice->gpio.ग_लिखो_mask);
	snd_ice1712_gpio_set_dir(ice, ice->gpio.direction);
	वापस val;
पूर्ण


/*
 * SPDIF input source
 */
अटल पूर्णांक cs_source_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[] = अणु
		"Coax",		/* RXP0 */
		"Optical",	/* RXP1 */
		"CD",		/* RXP2 */
	पूर्ण;
	वापस snd_ctl_क्रमागत_info(uinfo, 1, 3, texts);
पूर्ण

अटल पूर्णांक cs_source_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);

	mutex_lock(&ice->gpio_mutex);
	ucontrol->value.क्रमागतerated.item[0] = ice->gpio.saved[0];
	mutex_unlock(&ice->gpio_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक cs_source_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित अक्षर val;
	पूर्णांक change = 0;

	mutex_lock(&ice->gpio_mutex);
	अगर (ucontrol->value.क्रमागतerated.item[0] != ice->gpio.saved[0]) अणु
		ice->gpio.saved[0] = ucontrol->value.क्रमागतerated.item[0] & 3;
		val = 0x80 | (ice->gpio.saved[0] << 3);
		spi_ग_लिखो(ice, CS_DEV, 0x04, val);
		change = 1;
	पूर्ण
	mutex_unlock(&ice->gpio_mutex);
	वापस change;
पूर्ण


/*
 * GPIO controls
 */
अटल पूर्णांक pontis_gpio_mask_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 0xffff; /* 16bit */
	वापस 0;
पूर्ण

अटल पूर्णांक pontis_gpio_mask_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	mutex_lock(&ice->gpio_mutex);
	/* 4-7 reserved */
	ucontrol->value.पूर्णांकeger.value[0] = (~ice->gpio.ग_लिखो_mask & 0xffff) | 0x00f0;
	mutex_unlock(&ice->gpio_mutex);
	वापस 0;
पूर्ण
	
अटल पूर्णांक pontis_gpio_mask_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक val;
	पूर्णांक changed;
	mutex_lock(&ice->gpio_mutex);
	/* 4-7 reserved */
	val = (~ucontrol->value.पूर्णांकeger.value[0] & 0xffff) | 0x00f0;
	changed = val != ice->gpio.ग_लिखो_mask;
	ice->gpio.ग_लिखो_mask = val;
	mutex_unlock(&ice->gpio_mutex);
	वापस changed;
पूर्ण

अटल पूर्णांक pontis_gpio_dir_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	mutex_lock(&ice->gpio_mutex);
	/* 4-7 reserved */
	ucontrol->value.पूर्णांकeger.value[0] = ice->gpio.direction & 0xff0f;
	mutex_unlock(&ice->gpio_mutex);
	वापस 0;
पूर्ण
	
अटल पूर्णांक pontis_gpio_dir_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक val;
	पूर्णांक changed;
	mutex_lock(&ice->gpio_mutex);
	/* 4-7 reserved */
	val = ucontrol->value.पूर्णांकeger.value[0] & 0xff0f;
	changed = (val != ice->gpio.direction);
	ice->gpio.direction = val;
	mutex_unlock(&ice->gpio_mutex);
	वापस changed;
पूर्ण

अटल पूर्णांक pontis_gpio_data_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	mutex_lock(&ice->gpio_mutex);
	snd_ice1712_gpio_set_dir(ice, ice->gpio.direction);
	snd_ice1712_gpio_set_mask(ice, ice->gpio.ग_लिखो_mask);
	ucontrol->value.पूर्णांकeger.value[0] = snd_ice1712_gpio_पढ़ो(ice) & 0xffff;
	mutex_unlock(&ice->gpio_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक pontis_gpio_data_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक val, nval;
	पूर्णांक changed = 0;
	mutex_lock(&ice->gpio_mutex);
	snd_ice1712_gpio_set_dir(ice, ice->gpio.direction);
	snd_ice1712_gpio_set_mask(ice, ice->gpio.ग_लिखो_mask);
	val = snd_ice1712_gpio_पढ़ो(ice) & 0xffff;
	nval = ucontrol->value.पूर्णांकeger.value[0] & 0xffff;
	अगर (val != nval) अणु
		snd_ice1712_gpio_ग_लिखो(ice, nval);
		changed = 1;
	पूर्ण
	mutex_unlock(&ice->gpio_mutex);
	वापस changed;
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_volume, -6400, 50, 1);

/*
 * mixers
 */

अटल स्थिर काष्ठा snd_kcontrol_new pontis_controls[] = अणु
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.access = (SNDRV_CTL_ELEM_ACCESS_READWRITE |
			   SNDRV_CTL_ELEM_ACCESS_TLV_READ),
		.name = "PCM Playback Volume",
		.info = wm_dac_vol_info,
		.get = wm_dac_vol_get,
		.put = wm_dac_vol_put,
		.tlv = अणु .p = db_scale_volume पूर्ण,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.access = (SNDRV_CTL_ELEM_ACCESS_READWRITE |
			   SNDRV_CTL_ELEM_ACCESS_TLV_READ),
		.name = "Capture Volume",
		.info = wm_adc_vol_info,
		.get = wm_adc_vol_get,
		.put = wm_adc_vol_put,
		.tlv = अणु .p = db_scale_volume पूर्ण,
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
		.name = "IEC958 Input Source",
		.info = cs_source_info,
		.get = cs_source_get,
		.put = cs_source_put,
	पूर्ण,
	/* FIXME: which पूर्णांकerface? */
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_CARD,
		.name = "GPIO Mask",
		.info = pontis_gpio_mask_info,
		.get = pontis_gpio_mask_get,
		.put = pontis_gpio_mask_put,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_CARD,
		.name = "GPIO Direction",
		.info = pontis_gpio_mask_info,
		.get = pontis_gpio_dir_get,
		.put = pontis_gpio_dir_put,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_CARD,
		.name = "GPIO Data",
		.info = pontis_gpio_mask_info,
		.get = pontis_gpio_data_get,
		.put = pontis_gpio_data_put,
	पूर्ण,
पूर्ण;


/*
 * WM codec रेजिस्टरs
 */
अटल व्योम wm_proc_regs_ग_लिखो(काष्ठा snd_info_entry *entry, काष्ठा snd_info_buffer *buffer)
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

अटल व्योम wm_proc_regs_पढ़ो(काष्ठा snd_info_entry *entry, काष्ठा snd_info_buffer *buffer)
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

अटल व्योम cs_proc_regs_पढ़ो(काष्ठा snd_info_entry *entry, काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_ice1712 *ice = entry->निजी_data;
	पूर्णांक reg, val;

	mutex_lock(&ice->gpio_mutex);
	क्रम (reg = 0; reg <= 0x26; reg++) अणु
		val = spi_पढ़ो(ice, CS_DEV, reg);
		snd_iम_लिखो(buffer, "%02x = %02x\n", reg, val);
	पूर्ण
	val = spi_पढ़ो(ice, CS_DEV, 0x7f);
	snd_iम_लिखो(buffer, "%02x = %02x\n", 0x7f, val);
	mutex_unlock(&ice->gpio_mutex);
पूर्ण

अटल व्योम cs_proc_init(काष्ठा snd_ice1712 *ice)
अणु
	snd_card_ro_proc_new(ice->card, "cs_codec", ice, cs_proc_regs_पढ़ो);
पूर्ण


अटल पूर्णांक pontis_add_controls(काष्ठा snd_ice1712 *ice)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 0; i < ARRAY_SIZE(pontis_controls); i++) अणु
		err = snd_ctl_add(ice->card, snd_ctl_new1(&pontis_controls[i], ice));
		अगर (err < 0)
			वापस err;
	पूर्ण

	wm_proc_init(ice);
	cs_proc_init(ice);

	वापस 0;
पूर्ण


/*
 * initialize the chip
 */
अटल पूर्णांक pontis_init(काष्ठा snd_ice1712 *ice)
अणु
	अटल स्थिर अचिन्हित लघु wm_inits[] = अणु
		/* These come first to reduce init pop noise */
		WM_ADC_MUX,	0x00c0,	/* ADC mute */
		WM_DAC_MUTE,	0x0001,	/* DAC sofपंचांगute */
		WM_DAC_CTRL1,	0x0000,	/* DAC mute */

		WM_POWERDOWN,	0x0008,	/* All घातer-up except HP */
		WM_RESET,	0x0000,	/* reset */
	पूर्ण;
	अटल स्थिर अचिन्हित लघु wm_inits2[] = अणु
		WM_MASTER_CTRL,	0x0022,	/* 256fs, slave mode */
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
		/* WM_DAC_MASTER,	0x0100, */	/* DAC master muted */
		WM_PHASE_SWAP,	0x0000,	/* phase normal */
		WM_DAC_CTRL2,	0x0000,	/* no deemphasis, no ZFLG */
		WM_ADC_ATTEN_L,	0x0000,	/* ADC muted */
		WM_ADC_ATTEN_R,	0x0000,	/* ADC muted */
#अगर 0
		WM_ALC_CTRL1,	0x007b,	/* */
		WM_ALC_CTRL2,	0x0000,	/* */
		WM_ALC_CTRL3,	0x0000,	/* */
		WM_NOISE_GATE,	0x0000,	/* */
#पूर्ण_अगर
		WM_DAC_MUTE,	0x0000,	/* DAC unmute */
		WM_ADC_MUX,	0x0003,	/* ADC unmute, both CD/Line On */
	पूर्ण;
	अटल स्थिर अचिन्हित अक्षर cs_inits[] = अणु
		0x04,	0x80,	/* RUN, RXP0 */
		0x05,	0x05,	/* slave, 24bit */
		0x01,	0x00,
		0x02,	0x00,
		0x03,	0x00,
	पूर्ण;
	अचिन्हित पूर्णांक i;

	ice->vt1720 = 1;
	ice->num_total_dacs = 2;
	ice->num_total_adcs = 2;

	/* to remember the रेजिस्टर values */
	ice->akm = kzalloc(माप(काष्ठा snd_akm4xxx), GFP_KERNEL);
	अगर (! ice->akm)
		वापस -ENOMEM;
	ice->akm_codecs = 1;

	/* HACK - use this as the SPDIF source.
	 * करोn't call snd_ice1712_gpio_get/put(), otherwise it's overwritten
	 */
	ice->gpio.saved[0] = 0;

	/* initialize WM8776 codec */
	क्रम (i = 0; i < ARRAY_SIZE(wm_inits); i += 2)
		wm_put(ice, wm_inits[i], wm_inits[i+1]);
	schedule_समयout_unपूर्णांकerruptible(1);
	क्रम (i = 0; i < ARRAY_SIZE(wm_inits2); i += 2)
		wm_put(ice, wm_inits2[i], wm_inits2[i+1]);

	/* initialize CS8416 codec */
	/* निश्चित PRST#; MT05 bit 7 */
	outb(inb(ICEMT1724(ice, AC97_CMD)) | 0x80, ICEMT1724(ice, AC97_CMD));
	mdelay(5);
	/* deनिश्चित PRST# */
	outb(inb(ICEMT1724(ice, AC97_CMD)) & ~0x80, ICEMT1724(ice, AC97_CMD));

	क्रम (i = 0; i < ARRAY_SIZE(cs_inits); i += 2)
		spi_ग_लिखो(ice, CS_DEV, cs_inits[i], cs_inits[i+1]);

	वापस 0;
पूर्ण


/*
 * Pontis boards करोn't provide the EEPROM data at all.
 * hence the driver needs to sets up it properly.
 */

अटल स्थिर अचिन्हित अक्षर pontis_eeprom[] = अणु
	[ICE_EEP2_SYSCONF]     = 0x08,	/* घड़ी 256, mpu401, spdअगर-in/ADC, 1DAC */
	[ICE_EEP2_ACLINK]      = 0x80,	/* I2S */
	[ICE_EEP2_I2S]         = 0xf8,	/* vol, 96k, 24bit, 192k */
	[ICE_EEP2_SPDIF]       = 0xc3,	/* out-en, out-पूर्णांक, spdअगर-in */
	[ICE_EEP2_GPIO_सूची]    = 0x07,
	[ICE_EEP2_GPIO_सूची1]   = 0x00,
	[ICE_EEP2_GPIO_सूची2]   = 0x00,	/* ignored */
	[ICE_EEP2_GPIO_MASK]   = 0x0f,	/* 4-7 reserved क्रम CS8416 */
	[ICE_EEP2_GPIO_MASK1]  = 0xff,
	[ICE_EEP2_GPIO_MASK2]  = 0x00,	/* ignored */
	[ICE_EEP2_GPIO_STATE]  = 0x06,	/* 0-low, 1-high, 2-high */
	[ICE_EEP2_GPIO_STATE1] = 0x00,
	[ICE_EEP2_GPIO_STATE2] = 0x00,	/* ignored */
पूर्ण;

/* entry poपूर्णांक */
काष्ठा snd_ice1712_card_info snd_vt1720_pontis_cards[] = अणु
	अणु
		.subvenकरोr = VT1720_SUBDEVICE_PONTIS_MS300,
		.name = "Pontis MS300",
		.model = "ms300",
		.chip_init = pontis_init,
		.build_controls = pontis_add_controls,
		.eeprom_size = माप(pontis_eeprom),
		.eeprom_data = pontis_eeprom,
	पूर्ण,
	अणु पूर्ण /* terminator */
पूर्ण;
