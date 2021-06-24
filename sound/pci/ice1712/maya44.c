<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   ALSA driver क्रम ICEnsemble VT1724 (Envy24HT)
 *
 *   Lowlevel functions क्रम ESI Maya44 cards
 *
 *	Copyright (c) 2009 Takashi Iwai <tiwai@suse.de>
 *	Based on the patches by Rainer Zimmermann <mail@lightshed.de>
 */

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/pcm.h>
#समावेश <sound/tlv.h>

#समावेश "ice1712.h"
#समावेश "envy24ht.h"
#समावेश "maya44.h"

/* WM8776 रेजिस्टर indexes */
#घोषणा WM8776_REG_HEADPHONE_L		0x00
#घोषणा WM8776_REG_HEADPHONE_R		0x01
#घोषणा WM8776_REG_HEADPHONE_MASTER	0x02
#घोषणा WM8776_REG_DAC_ATTEN_L		0x03
#घोषणा WM8776_REG_DAC_ATTEN_R		0x04
#घोषणा WM8776_REG_DAC_ATTEN_MASTER	0x05
#घोषणा WM8776_REG_DAC_PHASE		0x06
#घोषणा WM8776_REG_DAC_CONTROL		0x07
#घोषणा WM8776_REG_DAC_MUTE		0x08
#घोषणा WM8776_REG_DAC_DEEMPH		0x09
#घोषणा WM8776_REG_DAC_IF_CONTROL	0x0a
#घोषणा WM8776_REG_ADC_IF_CONTROL	0x0b
#घोषणा WM8776_REG_MASTER_MODE_CONTROL	0x0c
#घोषणा WM8776_REG_POWERDOWN		0x0d
#घोषणा WM8776_REG_ADC_ATTEN_L		0x0e
#घोषणा WM8776_REG_ADC_ATTEN_R		0x0f
#घोषणा WM8776_REG_ADC_ALC1		0x10
#घोषणा WM8776_REG_ADC_ALC2		0x11
#घोषणा WM8776_REG_ADC_ALC3		0x12
#घोषणा WM8776_REG_ADC_NOISE_GATE	0x13
#घोषणा WM8776_REG_ADC_LIMITER		0x14
#घोषणा WM8776_REG_ADC_MUX		0x15
#घोषणा WM8776_REG_OUTPUT_MUX		0x16
#घोषणा WM8776_REG_RESET		0x17

#घोषणा WM8776_NUM_REGS			0x18

/* घड़ी ratio identअगरiers क्रम snd_wm8776_set_rate() */
#घोषणा WM8776_CLOCK_RATIO_128FS	0
#घोषणा WM8776_CLOCK_RATIO_192FS	1
#घोषणा WM8776_CLOCK_RATIO_256FS	2
#घोषणा WM8776_CLOCK_RATIO_384FS	3
#घोषणा WM8776_CLOCK_RATIO_512FS	4
#घोषणा WM8776_CLOCK_RATIO_768FS	5

क्रमागत अणु WM_VOL_HP, WM_VOL_DAC, WM_VOL_ADC, WM_NUM_VOLS पूर्ण;
क्रमागत अणु WM_SW_DAC, WM_SW_BYPASS, WM_NUM_SWITCHES पूर्ण;

काष्ठा snd_wm8776 अणु
	अचिन्हित अक्षर addr;
	अचिन्हित लघु regs[WM8776_NUM_REGS];
	अचिन्हित अक्षर volumes[WM_NUM_VOLS][2];
	अचिन्हित पूर्णांक चयन_bits;
पूर्ण;

काष्ठा snd_maya44 अणु
	काष्ठा snd_ice1712 *ice;
	काष्ठा snd_wm8776 wm[2];
	काष्ठा mutex mutex;
पूर्ण;


/* ग_लिखो the given रेजिस्टर and save the data to the cache */
अटल व्योम wm8776_ग_लिखो(काष्ठा snd_ice1712 *ice, काष्ठा snd_wm8776 *wm,
			 अचिन्हित अक्षर reg, अचिन्हित लघु val)
अणु
	/*
	 * WM8776 रेजिस्टरs are up to 9 bits wide, bit 8 is placed in the LSB
	 * of the address field
	 */
	snd_vt1724_ग_लिखो_i2c(ice, wm->addr,
			     (reg << 1) | ((val >> 8) & 1),
			     val & 0xff);
	wm->regs[reg] = val;
पूर्ण

/*
 * update the given रेजिस्टर with and/or mask and save the data to the cache
 */
अटल पूर्णांक wm8776_ग_लिखो_bits(काष्ठा snd_ice1712 *ice, काष्ठा snd_wm8776 *wm,
			     अचिन्हित अक्षर reg,
			     अचिन्हित लघु mask, अचिन्हित लघु val)
अणु
	val |= wm->regs[reg] & ~mask;
	अगर (val != wm->regs[reg]) अणु
		wm8776_ग_लिखो(ice, wm, reg, val);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण


/*
 * WM8776 volume controls
 */

काष्ठा maya_vol_info अणु
	अचिन्हित पूर्णांक maxval;		/* volume range: 0..maxval */
	अचिन्हित अक्षर regs[2];		/* left and right रेजिस्टरs */
	अचिन्हित लघु mask;		/* value mask */
	अचिन्हित लघु offset;		/* zero-value offset */
	अचिन्हित लघु mute;		/* mute bit */
	अचिन्हित लघु update;		/* update bits */
	अचिन्हित अक्षर mux_bits[2];	/* extra bits क्रम ADC mute */
पूर्ण;

अटल स्थिर काष्ठा maya_vol_info vol_info[WM_NUM_VOLS] = अणु
	[WM_VOL_HP] = अणु
		.maxval = 80,
		.regs = अणु WM8776_REG_HEADPHONE_L, WM8776_REG_HEADPHONE_R पूर्ण,
		.mask = 0x7f,
		.offset = 0x30,
		.mute = 0x00,
		.update = 0x180,	/* update and zero-cross enable */
	पूर्ण,
	[WM_VOL_DAC] = अणु
		.maxval = 255,
		.regs = अणु WM8776_REG_DAC_ATTEN_L, WM8776_REG_DAC_ATTEN_R पूर्ण,
		.mask = 0xff,
		.offset = 0x01,
		.mute = 0x00,
		.update = 0x100,	/* zero-cross enable */
	पूर्ण,
	[WM_VOL_ADC] = अणु
		.maxval = 91,
		.regs = अणु WM8776_REG_ADC_ATTEN_L, WM8776_REG_ADC_ATTEN_R पूर्ण,
		.mask = 0xff,
		.offset = 0xa5,
		.mute = 0xa5,
		.update = 0x100,	/* update */
		.mux_bits = अणु 0x80, 0x40 पूर्ण, /* ADCMUX bits */
	पूर्ण,
पूर्ण;

/*
 * dB tables
 */
/* headphone output: mute, -73..+6db (1db step) */
अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_hp, -7400, 100, 1);
/* DAC output: mute, -127..0db (0.5db step) */
अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_dac, -12750, 50, 1);
/* ADC gain: mute, -21..+24db (0.5db step) */
अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_adc, -2100, 50, 1);

अटल पूर्णांक maya_vol_info(काष्ठा snd_kcontrol *kcontrol,
			 काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अचिन्हित पूर्णांक idx = kcontrol->निजी_value;
	स्थिर काष्ठा maya_vol_info *vol = &vol_info[idx];

	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = vol->maxval;
	वापस 0;
पूर्ण

अटल पूर्णांक maya_vol_get(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_maya44 *chip = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_wm8776 *wm =
		&chip->wm[snd_ctl_get_ioff(kcontrol, &ucontrol->id)];
	अचिन्हित पूर्णांक idx = kcontrol->निजी_value;

	mutex_lock(&chip->mutex);
	ucontrol->value.पूर्णांकeger.value[0] = wm->volumes[idx][0];
	ucontrol->value.पूर्णांकeger.value[1] = wm->volumes[idx][1];
	mutex_unlock(&chip->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक maya_vol_put(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_maya44 *chip = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_wm8776 *wm =
		&chip->wm[snd_ctl_get_ioff(kcontrol, &ucontrol->id)];
	अचिन्हित पूर्णांक idx = kcontrol->निजी_value;
	स्थिर काष्ठा maya_vol_info *vol = &vol_info[idx];
	अचिन्हित पूर्णांक val, data;
	पूर्णांक ch, changed = 0;

	mutex_lock(&chip->mutex);
	क्रम (ch = 0; ch < 2; ch++) अणु
		val = ucontrol->value.पूर्णांकeger.value[ch];
		अगर (val > vol->maxval)
			val = vol->maxval;
		अगर (val == wm->volumes[idx][ch])
			जारी;
		अगर (!val)
			data = vol->mute;
		अन्यथा
			data = (val - 1) + vol->offset;
		data |= vol->update;
		changed |= wm8776_ग_लिखो_bits(chip->ice, wm, vol->regs[ch],
					     vol->mask | vol->update, data);
		अगर (vol->mux_bits[ch])
			wm8776_ग_लिखो_bits(chip->ice, wm, WM8776_REG_ADC_MUX,
					  vol->mux_bits[ch],
					  val ? 0 : vol->mux_bits[ch]);
		wm->volumes[idx][ch] = val;
	पूर्ण
	mutex_unlock(&chip->mutex);
	वापस changed;
पूर्ण

/*
 * WM8776 चयन controls
 */

#घोषणा COMPOSE_SW_VAL(idx, reg, mask)	((idx) | ((reg) << 8) | ((mask) << 16))
#घोषणा GET_SW_VAL_IDX(val)	((val) & 0xff)
#घोषणा GET_SW_VAL_REG(val)	(((val) >> 8) & 0xff)
#घोषणा GET_SW_VAL_MASK(val)	(((val) >> 16) & 0xff)

#घोषणा maya_sw_info	snd_ctl_boolean_mono_info

अटल पूर्णांक maya_sw_get(काष्ठा snd_kcontrol *kcontrol,
		       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_maya44 *chip = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_wm8776 *wm =
		&chip->wm[snd_ctl_get_ioff(kcontrol, &ucontrol->id)];
	अचिन्हित पूर्णांक idx = GET_SW_VAL_IDX(kcontrol->निजी_value);

	ucontrol->value.पूर्णांकeger.value[0] = (wm->चयन_bits >> idx) & 1;
	वापस 0;
पूर्ण

अटल पूर्णांक maya_sw_put(काष्ठा snd_kcontrol *kcontrol,
		       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_maya44 *chip = snd_kcontrol_chip(kcontrol);
	काष्ठा snd_wm8776 *wm =
		&chip->wm[snd_ctl_get_ioff(kcontrol, &ucontrol->id)];
	अचिन्हित पूर्णांक idx = GET_SW_VAL_IDX(kcontrol->निजी_value);
	अचिन्हित पूर्णांक mask, val;
	पूर्णांक changed;

	mutex_lock(&chip->mutex);
	mask = 1 << idx;
	wm->चयन_bits &= ~mask;
	val = ucontrol->value.पूर्णांकeger.value[0];
	अगर (val)
		wm->चयन_bits |= mask;
	mask = GET_SW_VAL_MASK(kcontrol->निजी_value);
	changed = wm8776_ग_लिखो_bits(chip->ice, wm,
				    GET_SW_VAL_REG(kcontrol->निजी_value),
				    mask, val ? mask : 0);
	mutex_unlock(&chip->mutex);
	वापस changed;
पूर्ण

/*
 * GPIO pins (known ones क्रम maya44)
 */
#घोषणा GPIO_PHANTOM_OFF	2
#घोषणा GPIO_MIC_RELAY		4
#घोषणा GPIO_SPDIF_IN_INV	5
#घोषणा GPIO_MUST_BE_0		7

/*
 * GPIO चयन controls
 */

#घोषणा COMPOSE_GPIO_VAL(shअगरt, inv)	((shअगरt) | ((inv) << 8))
#घोषणा GET_GPIO_VAL_SHIFT(val)		((val) & 0xff)
#घोषणा GET_GPIO_VAL_INV(val)		(((val) >> 8) & 1)

अटल पूर्णांक maya_set_gpio_bits(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक mask,
			      अचिन्हित पूर्णांक bits)
अणु
	अचिन्हित पूर्णांक data;
	data = snd_ice1712_gpio_पढ़ो(ice);
	अगर ((data & mask) == bits)
		वापस 0;
	snd_ice1712_gpio_ग_लिखो(ice, (data & ~mask) | bits);
	वापस 1;
पूर्ण

#घोषणा maya_gpio_sw_info	snd_ctl_boolean_mono_info

अटल पूर्णांक maya_gpio_sw_get(काष्ठा snd_kcontrol *kcontrol,
			    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_maya44 *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक shअगरt = GET_GPIO_VAL_SHIFT(kcontrol->निजी_value);
	अचिन्हित पूर्णांक val;

	val = (snd_ice1712_gpio_पढ़ो(chip->ice) >> shअगरt) & 1;
	अगर (GET_GPIO_VAL_INV(kcontrol->निजी_value))
		val = !val;
	ucontrol->value.पूर्णांकeger.value[0] = val;
	वापस 0;
पूर्ण

अटल पूर्णांक maya_gpio_sw_put(काष्ठा snd_kcontrol *kcontrol,
			    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_maya44 *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक shअगरt = GET_GPIO_VAL_SHIFT(kcontrol->निजी_value);
	अचिन्हित पूर्णांक val, mask;
	पूर्णांक changed;

	mutex_lock(&chip->mutex);
	mask = 1 << shअगरt;
	val = ucontrol->value.पूर्णांकeger.value[0];
	अगर (GET_GPIO_VAL_INV(kcontrol->निजी_value))
		val = !val;
	val = val ? mask : 0;
	changed = maya_set_gpio_bits(chip->ice, mask, val);
	mutex_unlock(&chip->mutex);
	वापस changed;
पूर्ण

/*
 * capture source selection
 */

/* known working input slots (0-4) */
#घोषणा MAYA_LINE_IN	1	/* in-2 */
#घोषणा MAYA_MIC_IN	3	/* in-4 */

अटल व्योम wm8776_select_input(काष्ठा snd_maya44 *chip, पूर्णांक idx, पूर्णांक line)
अणु
	wm8776_ग_लिखो_bits(chip->ice, &chip->wm[idx], WM8776_REG_ADC_MUX,
			  0x1f, 1 << line);
पूर्ण

अटल पूर्णांक maya_rec_src_info(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[] = अणु "Line", "Mic" पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, ARRAY_SIZE(texts), texts);
पूर्ण

अटल पूर्णांक maya_rec_src_get(काष्ठा snd_kcontrol *kcontrol,
			    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_maya44 *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक sel;

	अगर (snd_ice1712_gpio_पढ़ो(chip->ice) & (1 << GPIO_MIC_RELAY))
		sel = 1;
	अन्यथा
		sel = 0;
	ucontrol->value.क्रमागतerated.item[0] = sel;
	वापस 0;
पूर्ण

अटल पूर्णांक maya_rec_src_put(काष्ठा snd_kcontrol *kcontrol,
			    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_maya44 *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक sel = ucontrol->value.क्रमागतerated.item[0];
	पूर्णांक changed;

	mutex_lock(&chip->mutex);
	changed = maya_set_gpio_bits(chip->ice, 1 << GPIO_MIC_RELAY,
				     sel ? (1 << GPIO_MIC_RELAY) : 0);
	wm8776_select_input(chip, 0, sel ? MAYA_MIC_IN : MAYA_LINE_IN);
	mutex_unlock(&chip->mutex);
	वापस changed;
पूर्ण

/*
 * Maya44 routing चयन settings have dअगरferent meanings than the standard
 * ice1724 चयनes as defined in snd_vt1724_pro_route_info (ice1724.c).
 */
अटल पूर्णांक maya_pb_route_info(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[] = अणु
		"PCM Out", /* 0 */
		"Input 1", "Input 2", "Input 3", "Input 4"
	पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, ARRAY_SIZE(texts), texts);
पूर्ण

अटल पूर्णांक maya_pb_route_shअगरt(पूर्णांक idx)
अणु
	अटल स्थिर अचिन्हित अक्षर shअगरt[10] =
		अणु 8, 20, 0, 3, 11, 23, 14, 26, 17, 29 पूर्ण;
	वापस shअगरt[idx % 10];
पूर्ण

अटल पूर्णांक maya_pb_route_get(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_maya44 *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक idx = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id);
	ucontrol->value.क्रमागतerated.item[0] =
		snd_ice1724_get_route_val(chip->ice, maya_pb_route_shअगरt(idx));
	वापस 0;
पूर्ण

अटल पूर्णांक maya_pb_route_put(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_maya44 *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक idx = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id);
	वापस snd_ice1724_put_route_val(chip->ice,
					 ucontrol->value.क्रमागतerated.item[0],
					 maya_pb_route_shअगरt(idx));
पूर्ण


/*
 * controls to be added
 */

अटल स्थिर काष्ठा snd_kcontrol_new maya_controls[] = अणु
	अणु
		.name = "Crossmix Playback Volume",
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.access = SNDRV_CTL_ELEM_ACCESS_READWRITE |
			SNDRV_CTL_ELEM_ACCESS_TLV_READ,
		.info = maya_vol_info,
		.get = maya_vol_get,
		.put = maya_vol_put,
		.tlv = अणु .p = db_scale_hp पूर्ण,
		.निजी_value = WM_VOL_HP,
		.count = 2,
	पूर्ण,
	अणु
		.name = "PCM Playback Volume",
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.access = SNDRV_CTL_ELEM_ACCESS_READWRITE |
			SNDRV_CTL_ELEM_ACCESS_TLV_READ,
		.info = maya_vol_info,
		.get = maya_vol_get,
		.put = maya_vol_put,
		.tlv = अणु .p = db_scale_dac पूर्ण,
		.निजी_value = WM_VOL_DAC,
		.count = 2,
	पूर्ण,
	अणु
		.name = "Line Capture Volume",
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.access = SNDRV_CTL_ELEM_ACCESS_READWRITE |
			SNDRV_CTL_ELEM_ACCESS_TLV_READ,
		.info = maya_vol_info,
		.get = maya_vol_get,
		.put = maya_vol_put,
		.tlv = अणु .p = db_scale_adc पूर्ण,
		.निजी_value = WM_VOL_ADC,
		.count = 2,
	पूर्ण,
	अणु
		.name = "PCM Playback Switch",
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.info = maya_sw_info,
		.get = maya_sw_get,
		.put = maya_sw_put,
		.निजी_value = COMPOSE_SW_VAL(WM_SW_DAC,
						WM8776_REG_OUTPUT_MUX, 0x01),
		.count = 2,
	पूर्ण,
	अणु
		.name = "Bypass Playback Switch",
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.info = maya_sw_info,
		.get = maya_sw_get,
		.put = maya_sw_put,
		.निजी_value = COMPOSE_SW_VAL(WM_SW_BYPASS,
						WM8776_REG_OUTPUT_MUX, 0x04),
		.count = 2,
	पूर्ण,
	अणु
		.name = "Capture Source",
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.info = maya_rec_src_info,
		.get = maya_rec_src_get,
		.put = maya_rec_src_put,
	पूर्ण,
	अणु
		.name = "Mic Phantom Power Switch",
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.info = maya_gpio_sw_info,
		.get = maya_gpio_sw_get,
		.put = maya_gpio_sw_put,
		.निजी_value = COMPOSE_GPIO_VAL(GPIO_PHANTOM_OFF, 1),
	पूर्ण,
	अणु
		.name = "SPDIF Capture Switch",
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.info = maya_gpio_sw_info,
		.get = maya_gpio_sw_get,
		.put = maya_gpio_sw_put,
		.निजी_value = COMPOSE_GPIO_VAL(GPIO_SPDIF_IN_INV, 1),
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "H/W Playback Route",
		.info = maya_pb_route_info,
		.get = maya_pb_route_get,
		.put = maya_pb_route_put,
		.count = 4,  /* FIXME: करो controls 5-9 have any meaning? */
	पूर्ण,
पूर्ण;

अटल पूर्णांक maya44_add_controls(काष्ठा snd_ice1712 *ice)
अणु
	पूर्णांक err, i;

	क्रम (i = 0; i < ARRAY_SIZE(maya_controls); i++) अणु
		err = snd_ctl_add(ice->card, snd_ctl_new1(&maya_controls[i],
							  ice->spec));
		अगर (err < 0)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण


/*
 * initialize a wm8776 chip
 */
अटल व्योम wm8776_init(काष्ठा snd_ice1712 *ice,
			काष्ठा snd_wm8776 *wm, अचिन्हित पूर्णांक addr)
अणु
	अटल स्थिर अचिन्हित लघु inits_wm8776[] = अणु
		0x02, 0x100, /* R2: headphone L+R muted + update */
		0x05, 0x100, /* R5: DAC output L+R muted + update */
		0x06, 0x000, /* R6: DAC output phase normal */
		0x07, 0x091, /* R7: DAC enable zero cross detection,
				normal output */
		0x08, 0x000, /* R8: DAC soft mute off */
		0x09, 0x000, /* R9: no deemph, DAC zero detect disabled */
		0x0a, 0x022, /* R10: DAC I2C mode, std polarities, 24bit */
		0x0b, 0x022, /* R11: ADC I2C mode, std polarities, 24bit,
				highpass filter enabled */
		0x0c, 0x042, /* R12: ADC+DAC slave, ADC+DAC 44,1kHz */
		0x0d, 0x000, /* R13: all घातer up */
		0x0e, 0x100, /* R14: ADC left muted,
				enable zero cross detection */
		0x0f, 0x100, /* R15: ADC right muted,
				enable zero cross detection */
			     /* R16: ALC...*/
		0x11, 0x000, /* R17: disable ALC */
			     /* R18: ALC...*/
			     /* R19: noise gate...*/
		0x15, 0x000, /* R21: ADC input mux init, mute all inमाला_दो */
		0x16, 0x001, /* R22: output mux, select DAC */
		0xff, 0xff
	पूर्ण;

	स्थिर अचिन्हित लघु *ptr;
	अचिन्हित अक्षर reg;
	अचिन्हित लघु data;

	wm->addr = addr;
	/* enable DAC output; mute bypass, aux & all inमाला_दो */
	wm->चयन_bits = (1 << WM_SW_DAC);

	ptr = inits_wm8776;
	जबतक (*ptr != 0xff) अणु
		reg = *ptr++;
		data = *ptr++;
		wm8776_ग_लिखो(ice, wm, reg, data);
	पूर्ण
पूर्ण


/*
 * change the rate on the WM8776 codecs.
 * this assumes that the VT17xx's rate is changed by the calling function.
 * NOTE: even though the WM8776's are running in slave mode and rate
 * selection is स्वतःmatic, we need to call snd_wm8776_set_rate() here
 * to make sure some flags are set correctly.
 */
अटल व्योम set_rate(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक rate)
अणु
	काष्ठा snd_maya44 *chip = ice->spec;
	अचिन्हित पूर्णांक ratio, adc_ratio, val;
	पूर्णांक i;

	चयन (rate) अणु
	हाल 192000:
		ratio = WM8776_CLOCK_RATIO_128FS;
		अवरोध;
	हाल 176400:
		ratio = WM8776_CLOCK_RATIO_128FS;
		अवरोध;
	हाल 96000:
		ratio = WM8776_CLOCK_RATIO_256FS;
		अवरोध;
	हाल 88200:
		ratio = WM8776_CLOCK_RATIO_384FS;
		अवरोध;
	हाल 48000:
		ratio = WM8776_CLOCK_RATIO_512FS;
		अवरोध;
	हाल 44100:
		ratio = WM8776_CLOCK_RATIO_512FS;
		अवरोध;
	हाल 32000:
		ratio = WM8776_CLOCK_RATIO_768FS;
		अवरोध;
	हाल 0:
		/* no hपूर्णांक - S/PDIF input is master, simply वापस */
		वापस;
	शेष:
		snd_BUG();
		वापस;
	पूर्ण

	/*
	 * this currently sets the same rate क्रम ADC and DAC, but limits
	 * ADC rate to 256X (96kHz). For 256X mode (96kHz), this sets ADC
	 * oversampling to 64x, as recommended by WM8776 datasheet.
	 * Setting the rate is not really necessary in slave mode.
	 */
	adc_ratio = ratio;
	अगर (adc_ratio < WM8776_CLOCK_RATIO_256FS)
		adc_ratio = WM8776_CLOCK_RATIO_256FS;

	val = adc_ratio;
	अगर (adc_ratio == WM8776_CLOCK_RATIO_256FS)
		val |= 8;
	val |= ratio << 4;

	mutex_lock(&chip->mutex);
	क्रम (i = 0; i < 2; i++)
		wm8776_ग_लिखो_bits(ice, &chip->wm[i],
				  WM8776_REG_MASTER_MODE_CONTROL,
				  0x180, val);
	mutex_unlock(&chip->mutex);
पूर्ण

/*
 * supported sample rates (to override the शेष one)
 */

अटल स्थिर अचिन्हित पूर्णांक rates[] = अणु
	32000, 44100, 48000, 64000, 88200, 96000, 176400, 192000
पूर्ण;

/* playback rates: 32..192 kHz */
अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list dac_rates = अणु
	.count = ARRAY_SIZE(rates),
	.list = rates,
	.mask = 0
पूर्ण;


/*
 * chip addresses on I2C bus
 */
अटल स्थिर अचिन्हित अक्षर wm8776_addr[2] = अणु
	0x34, 0x36, /* codec 0 & 1 */
पूर्ण;

/*
 * initialize the chip
 */
अटल पूर्णांक maya44_init(काष्ठा snd_ice1712 *ice)
अणु
	पूर्णांक i;
	काष्ठा snd_maya44 *chip;

	chip = kzalloc(माप(*chip), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;
	mutex_init(&chip->mutex);
	chip->ice = ice;
	ice->spec = chip;

	/* initialise codecs */
	ice->num_total_dacs = 4;
	ice->num_total_adcs = 4;
	ice->akm_codecs = 0;

	क्रम (i = 0; i < 2; i++) अणु
		wm8776_init(ice, &chip->wm[i], wm8776_addr[i]);
		wm8776_select_input(chip, i, MAYA_LINE_IN);
	पूर्ण

	/* set card specअगरic rates */
	ice->hw_rates = &dac_rates;

	/* रेजिस्टर change rate notअगरier */
	ice->gpio.set_pro_rate = set_rate;

	/* RDMA1 (2nd input channel) is used क्रम ADC by शेष */
	ice->क्रमce_rdma1 = 1;

	/* have an own routing control */
	ice->own_routing = 1;

	वापस 0;
पूर्ण


/*
 * Maya44 boards करोn't provide the EEPROM data except क्रम the venकरोr IDs.
 * hence the driver needs to sets up it properly.
 */

अटल स्थिर अचिन्हित अक्षर maya44_eeprom[] = अणु
	[ICE_EEP2_SYSCONF]     = 0x45,
		/* घड़ी xin1=49.152MHz, mpu401, 2 stereo ADCs+DACs */
	[ICE_EEP2_ACLINK]      = 0x80,
		/* I2S */
	[ICE_EEP2_I2S]         = 0xf8,
		/* vol, 96k, 24bit, 192k */
	[ICE_EEP2_SPDIF]       = 0xc3,
		/* enable spdअगर out, spdअगर out supp, spdअगर-in, ext spdअगर out */
	[ICE_EEP2_GPIO_सूची]    = 0xff,
	[ICE_EEP2_GPIO_सूची1]   = 0xff,
	[ICE_EEP2_GPIO_सूची2]   = 0xff,
	[ICE_EEP2_GPIO_MASK]   = 0/*0x9f*/,
	[ICE_EEP2_GPIO_MASK1]  = 0/*0xff*/,
	[ICE_EEP2_GPIO_MASK2]  = 0/*0x7f*/,
	[ICE_EEP2_GPIO_STATE]  = (1 << GPIO_PHANTOM_OFF) |
			(1 << GPIO_SPDIF_IN_INV),
	[ICE_EEP2_GPIO_STATE1] = 0x00,
	[ICE_EEP2_GPIO_STATE2] = 0x00,
पूर्ण;

/* entry poपूर्णांक */
काष्ठा snd_ice1712_card_info snd_vt1724_maya44_cards[] = अणु
	अणु
		.subvenकरोr = VT1724_SUBDEVICE_MAYA44,
		.name = "ESI Maya44",
		.model = "maya44",
		.chip_init = maya44_init,
		.build_controls = maya44_add_controls,
		.eeprom_size = माप(maya44_eeprom),
		.eeprom_data = maya44_eeprom,
	पूर्ण,
	अणु पूर्ण /* terminator */
पूर्ण;
