<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *	ALSA driver क्रम ICEnsemble VT1724 (Envy24HT)
 *
 *	Lowlevel functions क्रम Ego Sys Waveterminal 192M
 *
 *		Copyright (c) 2006 Guedez Clement <klem.dev@gmail.com>
 *		Some functions are taken from the Prodigy192 driver
 *		source
 */



#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <sound/core.h>
#समावेश <sound/tlv.h>
#समावेश <linux/slab.h>

#समावेश "ice1712.h"
#समावेश "envy24ht.h"
#समावेश "wtm.h"
#समावेश "stac946x.h"

काष्ठा wपंचांग_spec अणु
	/* rate change needs atomic mute/unmute of all dacs*/
	काष्ठा mutex mute_mutex;
पूर्ण;


/*
 *	2*ADC 6*DAC no1 ringbuffer r/w on i2c bus
 */
अटल अंतरभूत व्योम stac9460_put(काष्ठा snd_ice1712 *ice, पूर्णांक reg,
						अचिन्हित अक्षर val)
अणु
	snd_vt1724_ग_लिखो_i2c(ice, STAC9460_I2C_ADDR, reg, val);
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर stac9460_get(काष्ठा snd_ice1712 *ice, पूर्णांक reg)
अणु
	वापस snd_vt1724_पढ़ो_i2c(ice, STAC9460_I2C_ADDR, reg);
पूर्ण

/*
 *	2*ADC 2*DAC no2 ringbuffer r/w on i2c bus
 */
अटल अंतरभूत व्योम stac9460_2_put(काष्ठा snd_ice1712 *ice, पूर्णांक reg,
						अचिन्हित अक्षर val)
अणु
	snd_vt1724_ग_लिखो_i2c(ice, STAC9460_2_I2C_ADDR, reg, val);
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर stac9460_2_get(काष्ठा snd_ice1712 *ice, पूर्णांक reg)
अणु
	वापस snd_vt1724_पढ़ो_i2c(ice, STAC9460_2_I2C_ADDR, reg);
पूर्ण


/*
 *	DAC mute control
 */
अटल व्योम stac9460_dac_mute_all(काष्ठा snd_ice1712 *ice, अचिन्हित अक्षर mute,
				अचिन्हित लघु पूर्णांक *change_mask)
अणु
	अचिन्हित अक्षर new, old;
	पूर्णांक id, idx, change;

	/*stac9460 1*/
	क्रम (id = 0; id < 7; id++) अणु
		अगर (*change_mask & (0x01 << id)) अणु
			अगर (id == 0)
				idx = STAC946X_MASTER_VOLUME;
			अन्यथा
				idx = STAC946X_LF_VOLUME - 1 + id;
			old = stac9460_get(ice, idx);
			new = (~mute << 7 & 0x80) | (old & ~0x80);
			change = (new != old);
			अगर (change) अणु
				stac9460_put(ice, idx, new);
				*change_mask = *change_mask | (0x01 << id);
			पूर्ण अन्यथा अणु
				*change_mask = *change_mask & ~(0x01 << id);
			पूर्ण
		पूर्ण
	पूर्ण

	/*stac9460 2*/
	क्रम (id = 0; id < 3; id++) अणु
		अगर (*change_mask & (0x01 << (id + 7))) अणु
			अगर (id == 0)
				idx = STAC946X_MASTER_VOLUME;
			अन्यथा
				idx = STAC946X_LF_VOLUME - 1 + id;
			old = stac9460_2_get(ice, idx);
			new = (~mute << 7 & 0x80) | (old & ~0x80);
			change = (new != old);
			अगर (change) अणु
				stac9460_2_put(ice, idx, new);
				*change_mask = *change_mask | (0x01 << id);
			पूर्ण अन्यथा अणु
				*change_mask = *change_mask & ~(0x01 << id);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण



#घोषणा stac9460_dac_mute_info		snd_ctl_boolean_mono_info

अटल पूर्णांक stac9460_dac_mute_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	काष्ठा wपंचांग_spec *spec = ice->spec;
	अचिन्हित अक्षर val;
	पूर्णांक idx, id;

	mutex_lock(&spec->mute_mutex);

	अगर (kcontrol->निजी_value) अणु
		idx = STAC946X_MASTER_VOLUME;
		id = 0;
	पूर्ण अन्यथा अणु
		id = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id);
		idx = id + STAC946X_LF_VOLUME;
	पूर्ण
	अगर (id < 6)
		val = stac9460_get(ice, idx);
	अन्यथा
		val = stac9460_2_get(ice, idx - 6);
	ucontrol->value.पूर्णांकeger.value[0] = (~val >> 7) & 0x1;

	mutex_unlock(&spec->mute_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक stac9460_dac_mute_put(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित अक्षर new, old;
	पूर्णांक id, idx;
	पूर्णांक change;

	अगर (kcontrol->निजी_value) अणु
		idx = STAC946X_MASTER_VOLUME;
		old = stac9460_get(ice, idx);
		new = (~ucontrol->value.पूर्णांकeger.value[0] << 7 & 0x80) |
							(old & ~0x80);
		change = (new != old);
		अगर (change) अणु
			stac9460_put(ice, idx, new);
			stac9460_2_put(ice, idx, new);
		पूर्ण
	पूर्ण अन्यथा अणु
		id = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id);
		idx = id + STAC946X_LF_VOLUME;
		अगर (id < 6)
			old = stac9460_get(ice, idx);
		अन्यथा
			old = stac9460_2_get(ice, idx - 6);
		new = (~ucontrol->value.पूर्णांकeger.value[0] << 7 & 0x80) |
							(old & ~0x80);
		change = (new != old);
		अगर (change) अणु
			अगर (id < 6)
				stac9460_put(ice, idx, new);
			अन्यथा
				stac9460_2_put(ice, idx - 6, new);
		पूर्ण
	पूर्ण
	वापस change;
पूर्ण

/*
 * 	DAC volume attenuation mixer control
 */
अटल पूर्णांक stac9460_dac_vol_info(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;			/* mute */
	uinfo->value.पूर्णांकeger.max = 0x7f;		/* 0dB */
	वापस 0;
पूर्ण

अटल पूर्णांक stac9460_dac_vol_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	पूर्णांक idx, id;
	अचिन्हित अक्षर vol;

	अगर (kcontrol->निजी_value) अणु
		idx = STAC946X_MASTER_VOLUME;
		id = 0;
	पूर्ण अन्यथा अणु
		id = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id);
		idx = id + STAC946X_LF_VOLUME;
	पूर्ण
	अगर (id < 6)
		vol = stac9460_get(ice, idx) & 0x7f;
	अन्यथा
		vol = stac9460_2_get(ice, idx - 6) & 0x7f;
	ucontrol->value.पूर्णांकeger.value[0] = 0x7f - vol;
	वापस 0;
पूर्ण

अटल पूर्णांक stac9460_dac_vol_put(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	पूर्णांक idx, id;
	अचिन्हित अक्षर पंचांगp, ovol, nvol;
	पूर्णांक change;

	अगर (kcontrol->निजी_value) अणु
		idx = STAC946X_MASTER_VOLUME;
		nvol = ucontrol->value.पूर्णांकeger.value[0] & 0x7f;
		पंचांगp = stac9460_get(ice, idx);
		ovol = 0x7f - (पंचांगp & 0x7f);
		change = (ovol != nvol);
		अगर (change) अणु
			stac9460_put(ice, idx, (0x7f - nvol) | (पंचांगp & 0x80));
			stac9460_2_put(ice, idx, (0x7f - nvol) | (पंचांगp & 0x80));
		पूर्ण
	पूर्ण अन्यथा अणु
		id = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id);
		idx = id + STAC946X_LF_VOLUME;
		nvol = ucontrol->value.पूर्णांकeger.value[0] & 0x7f;
		अगर (id < 6)
			पंचांगp = stac9460_get(ice, idx);
		अन्यथा
			पंचांगp = stac9460_2_get(ice, idx - 6);
		ovol = 0x7f - (पंचांगp & 0x7f);
		change = (ovol != nvol);
		अगर (change) अणु
			अगर (id < 6)
				stac9460_put(ice, idx, (0x7f - nvol) |
							(पंचांगp & 0x80));
			अन्यथा
				stac9460_2_put(ice, idx-6, (0x7f - nvol) |
							(पंचांगp & 0x80));
		पूर्ण
	पूर्ण
	वापस change;
पूर्ण

/*
 * ADC mute control
 */
#घोषणा stac9460_adc_mute_info		snd_ctl_boolean_stereo_info

अटल पूर्णांक stac9460_adc_mute_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित अक्षर val;
	पूर्णांक i, id;

	id = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id);
	अगर (id == 0) अणु
		क्रम (i = 0; i < 2; ++i) अणु
			val = stac9460_get(ice, STAC946X_MIC_L_VOLUME + i);
			ucontrol->value.पूर्णांकeger.value[i] = ~val>>7 & 0x1;
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < 2; ++i) अणु
			val = stac9460_2_get(ice, STAC946X_MIC_L_VOLUME + i);
			ucontrol->value.पूर्णांकeger.value[i] = ~val>>7 & 0x1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक stac9460_adc_mute_put(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित अक्षर new, old;
	पूर्णांक i, reg, id;
	पूर्णांक change;

	id = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id);
	अगर (id == 0) अणु
		क्रम (i = 0; i < 2; ++i) अणु
			reg = STAC946X_MIC_L_VOLUME + i;
			old = stac9460_get(ice, reg);
			new = (~ucontrol->value.पूर्णांकeger.value[i]<<7&0x80) |
								(old&~0x80);
			change = (new != old);
			अगर (change)
				stac9460_put(ice, reg, new);
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < 2; ++i) अणु
			reg = STAC946X_MIC_L_VOLUME + i;
			old = stac9460_2_get(ice, reg);
			new = (~ucontrol->value.पूर्णांकeger.value[i]<<7&0x80) |
								(old&~0x80);
			change = (new != old);
			अगर (change)
				stac9460_2_put(ice, reg, new);
		पूर्ण
	पूर्ण
	वापस change;
पूर्ण

/*
 *ADC gain mixer control
 */
अटल पूर्णांक stac9460_adc_vol_info(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;		/* 0dB */
	uinfo->value.पूर्णांकeger.max = 0x0f;	/* 22.5dB */
	वापस 0;
पूर्ण

अटल पूर्णांक stac9460_adc_vol_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	पूर्णांक i, reg, id;
	अचिन्हित अक्षर vol;

	id = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id);
	अगर (id == 0) अणु
		क्रम (i = 0; i < 2; ++i) अणु
			reg = STAC946X_MIC_L_VOLUME + i;
			vol = stac9460_get(ice, reg) & 0x0f;
			ucontrol->value.पूर्णांकeger.value[i] = 0x0f - vol;
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < 2; ++i) अणु
			reg = STAC946X_MIC_L_VOLUME + i;
			vol = stac9460_2_get(ice, reg) & 0x0f;
			ucontrol->value.पूर्णांकeger.value[i] = 0x0f - vol;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक stac9460_adc_vol_put(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	पूर्णांक i, reg, id;
	अचिन्हित अक्षर ovol, nvol;
	पूर्णांक change;

	id = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id);
	अगर (id == 0) अणु
		क्रम (i = 0; i < 2; ++i) अणु
			reg = STAC946X_MIC_L_VOLUME + i;
			nvol = ucontrol->value.पूर्णांकeger.value[i] & 0x0f;
			ovol = 0x0f - stac9460_get(ice, reg);
			change = ((ovol & 0x0f) != nvol);
			अगर (change)
				stac9460_put(ice, reg, (0x0f - nvol) |
							(ovol & ~0x0f));
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < 2; ++i) अणु
			reg = STAC946X_MIC_L_VOLUME + i;
			nvol = ucontrol->value.पूर्णांकeger.value[i] & 0x0f;
			ovol = 0x0f - stac9460_2_get(ice, reg);
			change = ((ovol & 0x0f) != nvol);
			अगर (change)
				stac9460_2_put(ice, reg, (0x0f - nvol) |
							(ovol & ~0x0f));
		पूर्ण
	पूर्ण
	वापस change;
पूर्ण

/*
 * MIC / LINE चयन fonction
 */
अटल पूर्णांक stac9460_mic_sw_info(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[2] = अणु "Line In", "Mic" पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 2, texts);
पूर्ण


अटल पूर्णांक stac9460_mic_sw_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित अक्षर val;
	पूर्णांक id;

	id = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id);
	अगर (id == 0)
		val = stac9460_get(ice, STAC946X_GENERAL_PURPOSE);
	अन्यथा
		val = stac9460_2_get(ice, STAC946X_GENERAL_PURPOSE);
	ucontrol->value.क्रमागतerated.item[0] = (val >> 7) & 0x1;
	वापस 0;
पूर्ण

अटल पूर्णांक stac9460_mic_sw_put(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	अचिन्हित अक्षर new, old;
	पूर्णांक change, id;

	id = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id);
	अगर (id == 0)
		old = stac9460_get(ice, STAC946X_GENERAL_PURPOSE);
	अन्यथा
		old = stac9460_2_get(ice, STAC946X_GENERAL_PURPOSE);
	new = (ucontrol->value.क्रमागतerated.item[0] << 7 & 0x80) | (old & ~0x80);
	change = (new != old);
	अगर (change) अणु
		अगर (id == 0)
			stac9460_put(ice, STAC946X_GENERAL_PURPOSE, new);
		अन्यथा
			stac9460_2_put(ice, STAC946X_GENERAL_PURPOSE, new);
	पूर्ण
	वापस change;
पूर्ण


/*
 * Handler क्रम setting correct codec rate - called when rate change is detected
 */
अटल व्योम stac9460_set_rate_val(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक rate)
अणु
	अचिन्हित अक्षर old, new;
	अचिन्हित लघु पूर्णांक changed;
	काष्ठा wपंचांग_spec *spec = ice->spec;

	अगर (rate == 0)  /* no hपूर्णांक - S/PDIF input is master, simply वापस */
		वापस;
	अन्यथा अगर (rate <= 48000)
		new = 0x08;     /* 256x, base rate mode */
	अन्यथा अगर (rate <= 96000)
		new = 0x11;     /* 256x, mid rate mode */
	अन्यथा
		new = 0x12;     /* 128x, high rate mode */

	old = stac9460_get(ice, STAC946X_MASTER_CLOCKING);
	अगर (old == new)
		वापस;
	/* change detected, setting master घड़ी, muting first */
	/* due to possible conflicts with mute controls - mutexing */
	mutex_lock(&spec->mute_mutex);
	/* we have to remember current mute status क्रम each DAC */
	changed = 0xFFFF;
	stac9460_dac_mute_all(ice, 0, &changed);
	/*prपूर्णांकk(KERN_DEBUG "Rate change: %d, new MC: 0x%02x\n", rate, new);*/
	stac9460_put(ice, STAC946X_MASTER_CLOCKING, new);
	stac9460_2_put(ice, STAC946X_MASTER_CLOCKING, new);
	udelay(10);
	/* unmuting - only originally unmuted dacs -
	* i.e. those changed when muting */
	stac9460_dac_mute_all(ice, 1, &changed);
	mutex_unlock(&spec->mute_mutex);
पूर्ण


/*Limits value in dB क्रम fader*/
अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_dac, -19125, 75, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_adc, 0, 150, 0);

/*
 * Control tअसल
 */
अटल स्थिर काष्ठा snd_kcontrol_new stac9640_controls[] = अणु
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.access = (SNDRV_CTL_ELEM_ACCESS_READWRITE |
			    SNDRV_CTL_ELEM_ACCESS_TLV_READ),
		.name = "Master Playback Switch",
		.info = stac9460_dac_mute_info,
		.get = stac9460_dac_mute_get,
		.put = stac9460_dac_mute_put,
		.निजी_value = 1,
		.tlv = अणु .p = db_scale_dac पूर्ण
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Master Playback Volume",
		.info = stac9460_dac_vol_info,
		.get = stac9460_dac_vol_get,
		.put = stac9460_dac_vol_put,
		.निजी_value = 1,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "MIC/Line Input Enum",
		.count = 2,
		.info = stac9460_mic_sw_info,
		.get = stac9460_mic_sw_get,
		.put = stac9460_mic_sw_put,

	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "DAC Switch",
		.count = 8,
		.info = stac9460_dac_mute_info,
		.get = stac9460_dac_mute_get,
		.put = stac9460_dac_mute_put,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.access = (SNDRV_CTL_ELEM_ACCESS_READWRITE |
			    SNDRV_CTL_ELEM_ACCESS_TLV_READ),

		.name = "DAC Volume",
		.count = 8,
		.info = stac9460_dac_vol_info,
		.get = stac9460_dac_vol_get,
		.put = stac9460_dac_vol_put,
		.tlv = अणु .p = db_scale_dac पूर्ण
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "ADC Switch",
		.count = 2,
		.info = stac9460_adc_mute_info,
		.get = stac9460_adc_mute_get,
		.put = stac9460_adc_mute_put,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.access = (SNDRV_CTL_ELEM_ACCESS_READWRITE |
			    SNDRV_CTL_ELEM_ACCESS_TLV_READ),

		.name = "ADC Volume",
		.count = 2,
		.info = stac9460_adc_vol_info,
		.get = stac9460_adc_vol_get,
		.put = stac9460_adc_vol_put,
		.tlv = अणु .p = db_scale_adc पूर्ण
	पूर्ण
पूर्ण;



/*INIT*/
अटल पूर्णांक wपंचांग_add_controls(काष्ठा snd_ice1712 *ice)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 0; i < ARRAY_SIZE(stac9640_controls); i++) अणु
		err = snd_ctl_add(ice->card,
				snd_ctl_new1(&stac9640_controls[i], ice));
		अगर (err < 0)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक wपंचांग_init(काष्ठा snd_ice1712 *ice)
अणु
	अटल स्थिर अचिन्हित लघु stac_inits_wपंचांग[] = अणु
		STAC946X_RESET, 0,
		STAC946X_MASTER_CLOCKING, 0x11,
		(अचिन्हित लघु)-1
	पूर्ण;
	स्थिर अचिन्हित लघु *p;
	काष्ठा wपंचांग_spec *spec;

	/*WTM 192M*/
	ice->num_total_dacs = 8;
	ice->num_total_adcs = 4;
	ice->क्रमce_rdma1 = 1;

	/*init mutex क्रम dac mute conflict*/
	spec = kzalloc(माप(*spec), GFP_KERNEL);
	अगर (!spec)
		वापस -ENOMEM;
	ice->spec = spec;
	mutex_init(&spec->mute_mutex);


	/*initialize codec*/
	p = stac_inits_wपंचांग;
	क्रम (; *p != (अचिन्हित लघु)-1; p += 2) अणु
		stac9460_put(ice, p[0], p[1]);
		stac9460_2_put(ice, p[0], p[1]);
	पूर्ण
	ice->gpio.set_pro_rate = stac9460_set_rate_val;
	वापस 0;
पूर्ण


अटल स्थिर अचिन्हित अक्षर wपंचांग_eeprom[] = अणु
	[ICE_EEP2_SYSCONF]      = 0x67, /*SYSCONF: घड़ी 192KHz, mpu401,
							4ADC, 8DAC */
	[ICE_EEP2_ACLINK]       = 0x80, /* ACLINK : I2S */
	[ICE_EEP2_I2S]          = 0xf8, /* I2S: vol; 96k, 24bit, 192k */
	[ICE_EEP2_SPDIF]        = 0xc1, /*SPDIF: out-en, spidf ext out*/
	[ICE_EEP2_GPIO_सूची]     = 0x9f,
	[ICE_EEP2_GPIO_सूची1]    = 0xff,
	[ICE_EEP2_GPIO_सूची2]    = 0x7f,
	[ICE_EEP2_GPIO_MASK]    = 0x9f,
	[ICE_EEP2_GPIO_MASK1]   = 0xff,
	[ICE_EEP2_GPIO_MASK2]   = 0x7f,
	[ICE_EEP2_GPIO_STATE]   = 0x16,
	[ICE_EEP2_GPIO_STATE1]  = 0x80,
	[ICE_EEP2_GPIO_STATE2]  = 0x00,
पूर्ण;


/*entry poपूर्णांक*/
काष्ठा snd_ice1712_card_info snd_vt1724_wपंचांग_cards[] = अणु
	अणु
		.subvenकरोr = VT1724_SUBDEVICE_WTM,
		.name = "ESI Waveterminal 192M",
		.model = "WT192M",
		.chip_init = wपंचांग_init,
		.build_controls = wपंचांग_add_controls,
		.eeprom_size = माप(wपंचांग_eeprom),
		.eeprom_data = wपंचांग_eeprom,
	पूर्ण,
	अणुपूर्ण /*terminator*/
पूर्ण;
