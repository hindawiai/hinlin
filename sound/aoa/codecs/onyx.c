<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Apple Onboard Audio driver क्रम Onyx codec
 *
 * Copyright 2006 Johannes Berg <johannes@sipsolutions.net>
 *
 * This is a driver क्रम the pcm3052 codec chip (codenamed Onyx)
 * that is present in newer Apple hardware (with digital output).
 *
 * The Onyx codec has the following connections (listed by the bit
 * to be used in aoa_codec.connected):
 *  0: analog output
 *  1: digital output
 *  2: line input
 *  3: microphone input
 * Note that even though I know of no machine that has क्रम example
 * the digital output connected but not the analog, I have handled
 * all the dअगरferent हालs in the code so that this driver may serve
 * as a good example of what to करो.
 *
 * NOTE: This driver assumes that there's at most one chip to be
 * 	 used with one alsa card, in क्रमm of creating all kinds
 *	 of mixer elements without regard क्रम their existence.
 *	 But snd-aoa assumes that there's at most one card, so
 *	 this means you can only have one onyx on a प्रणाली. This
 *	 should probably be fixed by changing the assumption of
 *	 having just a single card on a प्रणाली, and making the
 *	 'card' poपूर्णांकer accessible to anyone who needs it instead
 *	 of hiding it in the aoa_snd_* functions...
 */
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
MODULE_AUTHOR("Johannes Berg <johannes@sipsolutions.net>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("pcm3052 (onyx) codec driver for snd-aoa");

#समावेश "onyx.h"
#समावेश "../aoa.h"
#समावेश "../soundbus/soundbus.h"


#घोषणा PFX "snd-aoa-codec-onyx: "

काष्ठा onyx अणु
	/* cache रेजिस्टरs 65 to 80, they are ग_लिखो-only! */
	u8			cache[16];
	काष्ठा i2c_client	*i2c;
	काष्ठा aoa_codec	codec;
	u32			initialised:1,
				spdअगर_locked:1,
				analog_locked:1,
				original_mute:2;
	पूर्णांक			खोलो_count;
	काष्ठा codec_info	*codec_info;

	/* mutex serializes concurrent access to the device
	 * and this काष्ठाure.
	 */
	काष्ठा mutex mutex;
पूर्ण;
#घोषणा codec_to_onyx(c) container_of(c, काष्ठा onyx, codec)

/* both वापस 0 अगर all ok, अन्यथा on error */
अटल पूर्णांक onyx_पढ़ो_रेजिस्टर(काष्ठा onyx *onyx, u8 reg, u8 *value)
अणु
	s32 v;

	अगर (reg != ONYX_REG_CONTROL) अणु
		*value = onyx->cache[reg-FIRSTREGISTER];
		वापस 0;
	पूर्ण
	v = i2c_smbus_पढ़ो_byte_data(onyx->i2c, reg);
	अगर (v < 0) अणु
		*value = 0;
		वापस -1;
	पूर्ण
	*value = (u8)v;
	onyx->cache[ONYX_REG_CONTROL-FIRSTREGISTER] = *value;
	वापस 0;
पूर्ण

अटल पूर्णांक onyx_ग_लिखो_रेजिस्टर(काष्ठा onyx *onyx, u8 reg, u8 value)
अणु
	पूर्णांक result;

	result = i2c_smbus_ग_लिखो_byte_data(onyx->i2c, reg, value);
	अगर (!result)
		onyx->cache[reg-FIRSTREGISTER] = value;
	वापस result;
पूर्ण

/* alsa stuff */

अटल पूर्णांक onyx_dev_रेजिस्टर(काष्ठा snd_device *dev)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_device_ops ops = अणु
	.dev_रेजिस्टर = onyx_dev_रेजिस्टर,
पूर्ण;

/* this is necessary because most alsa mixer programs
 * can't properly handle the negative range */
#घोषणा VOLUME_RANGE_SHIFT	128

अटल पूर्णांक onyx_snd_vol_info(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = -128 + VOLUME_RANGE_SHIFT;
	uinfo->value.पूर्णांकeger.max = -1 + VOLUME_RANGE_SHIFT;
	वापस 0;
पूर्ण

अटल पूर्णांक onyx_snd_vol_get(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा onyx *onyx = snd_kcontrol_chip(kcontrol);
	s8 l, r;

	mutex_lock(&onyx->mutex);
	onyx_पढ़ो_रेजिस्टर(onyx, ONYX_REG_DAC_ATTEN_LEFT, &l);
	onyx_पढ़ो_रेजिस्टर(onyx, ONYX_REG_DAC_ATTEN_RIGHT, &r);
	mutex_unlock(&onyx->mutex);

	ucontrol->value.पूर्णांकeger.value[0] = l + VOLUME_RANGE_SHIFT;
	ucontrol->value.पूर्णांकeger.value[1] = r + VOLUME_RANGE_SHIFT;

	वापस 0;
पूर्ण

अटल पूर्णांक onyx_snd_vol_put(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा onyx *onyx = snd_kcontrol_chip(kcontrol);
	s8 l, r;

	अगर (ucontrol->value.पूर्णांकeger.value[0] < -128 + VOLUME_RANGE_SHIFT ||
	    ucontrol->value.पूर्णांकeger.value[0] > -1 + VOLUME_RANGE_SHIFT)
		वापस -EINVAL;
	अगर (ucontrol->value.पूर्णांकeger.value[1] < -128 + VOLUME_RANGE_SHIFT ||
	    ucontrol->value.पूर्णांकeger.value[1] > -1 + VOLUME_RANGE_SHIFT)
		वापस -EINVAL;

	mutex_lock(&onyx->mutex);
	onyx_पढ़ो_रेजिस्टर(onyx, ONYX_REG_DAC_ATTEN_LEFT, &l);
	onyx_पढ़ो_रेजिस्टर(onyx, ONYX_REG_DAC_ATTEN_RIGHT, &r);

	अगर (l + VOLUME_RANGE_SHIFT == ucontrol->value.पूर्णांकeger.value[0] &&
	    r + VOLUME_RANGE_SHIFT == ucontrol->value.पूर्णांकeger.value[1]) अणु
		mutex_unlock(&onyx->mutex);
		वापस 0;
	पूर्ण

	onyx_ग_लिखो_रेजिस्टर(onyx, ONYX_REG_DAC_ATTEN_LEFT,
			    ucontrol->value.पूर्णांकeger.value[0]
			     - VOLUME_RANGE_SHIFT);
	onyx_ग_लिखो_रेजिस्टर(onyx, ONYX_REG_DAC_ATTEN_RIGHT,
			    ucontrol->value.पूर्णांकeger.value[1]
			     - VOLUME_RANGE_SHIFT);
	mutex_unlock(&onyx->mutex);

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new volume_control = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Master Playback Volume",
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.info = onyx_snd_vol_info,
	.get = onyx_snd_vol_get,
	.put = onyx_snd_vol_put,
पूर्ण;

/* like above, this is necessary because a lot
 * of alsa mixer programs करोn't handle ranges
 * that करोn't start at 0 properly.
 * even alsamixer is one of them... */
#घोषणा INPUTGAIN_RANGE_SHIFT	(-3)

अटल पूर्णांक onyx_snd_inputgain_info(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 3 + INPUTGAIN_RANGE_SHIFT;
	uinfo->value.पूर्णांकeger.max = 28 + INPUTGAIN_RANGE_SHIFT;
	वापस 0;
पूर्ण

अटल पूर्णांक onyx_snd_inputgain_get(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा onyx *onyx = snd_kcontrol_chip(kcontrol);
	u8 ig;

	mutex_lock(&onyx->mutex);
	onyx_पढ़ो_रेजिस्टर(onyx, ONYX_REG_ADC_CONTROL, &ig);
	mutex_unlock(&onyx->mutex);

	ucontrol->value.पूर्णांकeger.value[0] =
		(ig & ONYX_ADC_PGA_GAIN_MASK) + INPUTGAIN_RANGE_SHIFT;

	वापस 0;
पूर्ण

अटल पूर्णांक onyx_snd_inputgain_put(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा onyx *onyx = snd_kcontrol_chip(kcontrol);
	u8 v, n;

	अगर (ucontrol->value.पूर्णांकeger.value[0] < 3 + INPUTGAIN_RANGE_SHIFT ||
	    ucontrol->value.पूर्णांकeger.value[0] > 28 + INPUTGAIN_RANGE_SHIFT)
		वापस -EINVAL;
	mutex_lock(&onyx->mutex);
	onyx_पढ़ो_रेजिस्टर(onyx, ONYX_REG_ADC_CONTROL, &v);
	n = v;
	n &= ~ONYX_ADC_PGA_GAIN_MASK;
	n |= (ucontrol->value.पूर्णांकeger.value[0] - INPUTGAIN_RANGE_SHIFT)
		& ONYX_ADC_PGA_GAIN_MASK;
	onyx_ग_लिखो_रेजिस्टर(onyx, ONYX_REG_ADC_CONTROL, n);
	mutex_unlock(&onyx->mutex);

	वापस n != v;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new inputgain_control = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Master Capture Volume",
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.info = onyx_snd_inputgain_info,
	.get = onyx_snd_inputgain_get,
	.put = onyx_snd_inputgain_put,
पूर्ण;

अटल पूर्णांक onyx_snd_capture_source_info(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[] = अणु "Line-In", "Microphone" पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 2, texts);
पूर्ण

अटल पूर्णांक onyx_snd_capture_source_get(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा onyx *onyx = snd_kcontrol_chip(kcontrol);
	s8 v;

	mutex_lock(&onyx->mutex);
	onyx_पढ़ो_रेजिस्टर(onyx, ONYX_REG_ADC_CONTROL, &v);
	mutex_unlock(&onyx->mutex);

	ucontrol->value.क्रमागतerated.item[0] = !!(v&ONYX_ADC_INPUT_MIC);

	वापस 0;
पूर्ण

अटल व्योम onyx_set_capture_source(काष्ठा onyx *onyx, पूर्णांक mic)
अणु
	s8 v;

	mutex_lock(&onyx->mutex);
	onyx_पढ़ो_रेजिस्टर(onyx, ONYX_REG_ADC_CONTROL, &v);
	v &= ~ONYX_ADC_INPUT_MIC;
	अगर (mic)
		v |= ONYX_ADC_INPUT_MIC;
	onyx_ग_लिखो_रेजिस्टर(onyx, ONYX_REG_ADC_CONTROL, v);
	mutex_unlock(&onyx->mutex);
पूर्ण

अटल पूर्णांक onyx_snd_capture_source_put(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	अगर (ucontrol->value.क्रमागतerated.item[0] > 1)
		वापस -EINVAL;
	onyx_set_capture_source(snd_kcontrol_chip(kcontrol),
				ucontrol->value.क्रमागतerated.item[0]);
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new capture_source_control = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	/* If we name this 'Input Source', it properly shows up in
	 * alsamixer as a selection, * but it's shown under the
	 * 'Playback' category.
	 * If I name it 'Capture Source', it shows up in strange
	 * ways (two bools of which one can be selected at a
	 * समय) but at least it's shown in the 'Capture'
	 * category.
	 * I was told that this was due to backward compatibility,
	 * but I करोn't understand then why the mangling is *not*
	 * करोne when I name it "Input Source".....
	 */
	.name = "Capture Source",
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.info = onyx_snd_capture_source_info,
	.get = onyx_snd_capture_source_get,
	.put = onyx_snd_capture_source_put,
पूर्ण;

#घोषणा onyx_snd_mute_info	snd_ctl_boolean_stereo_info

अटल पूर्णांक onyx_snd_mute_get(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा onyx *onyx = snd_kcontrol_chip(kcontrol);
	u8 c;

	mutex_lock(&onyx->mutex);
	onyx_पढ़ो_रेजिस्टर(onyx, ONYX_REG_DAC_CONTROL, &c);
	mutex_unlock(&onyx->mutex);

	ucontrol->value.पूर्णांकeger.value[0] = !(c & ONYX_MUTE_LEFT);
	ucontrol->value.पूर्णांकeger.value[1] = !(c & ONYX_MUTE_RIGHT);

	वापस 0;
पूर्ण

अटल पूर्णांक onyx_snd_mute_put(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा onyx *onyx = snd_kcontrol_chip(kcontrol);
	u8 v = 0, c = 0;
	पूर्णांक err = -EBUSY;

	mutex_lock(&onyx->mutex);
	अगर (onyx->analog_locked)
		जाओ out_unlock;

	onyx_पढ़ो_रेजिस्टर(onyx, ONYX_REG_DAC_CONTROL, &v);
	c = v;
	c &= ~(ONYX_MUTE_RIGHT | ONYX_MUTE_LEFT);
	अगर (!ucontrol->value.पूर्णांकeger.value[0])
		c |= ONYX_MUTE_LEFT;
	अगर (!ucontrol->value.पूर्णांकeger.value[1])
		c |= ONYX_MUTE_RIGHT;
	err = onyx_ग_लिखो_रेजिस्टर(onyx, ONYX_REG_DAC_CONTROL, c);

 out_unlock:
	mutex_unlock(&onyx->mutex);

	वापस !err ? (v != c) : err;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new mute_control = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Master Playback Switch",
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.info = onyx_snd_mute_info,
	.get = onyx_snd_mute_get,
	.put = onyx_snd_mute_put,
पूर्ण;


#घोषणा onyx_snd_single_bit_info	snd_ctl_boolean_mono_info

#घोषणा FLAG_POLARITY_INVERT	1
#घोषणा FLAG_SPDIFLOCK		2

अटल पूर्णांक onyx_snd_single_bit_get(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा onyx *onyx = snd_kcontrol_chip(kcontrol);
	u8 c;
	दीर्घ पूर्णांक pv = kcontrol->निजी_value;
	u8 polarity = (pv >> 16) & FLAG_POLARITY_INVERT;
	u8 address = (pv >> 8) & 0xff;
	u8 mask = pv & 0xff;

	mutex_lock(&onyx->mutex);
	onyx_पढ़ो_रेजिस्टर(onyx, address, &c);
	mutex_unlock(&onyx->mutex);

	ucontrol->value.पूर्णांकeger.value[0] = !!(c & mask) ^ polarity;

	वापस 0;
पूर्ण

अटल पूर्णांक onyx_snd_single_bit_put(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा onyx *onyx = snd_kcontrol_chip(kcontrol);
	u8 v = 0, c = 0;
	पूर्णांक err;
	दीर्घ पूर्णांक pv = kcontrol->निजी_value;
	u8 polarity = (pv >> 16) & FLAG_POLARITY_INVERT;
	u8 spdअगरlock = (pv >> 16) & FLAG_SPDIFLOCK;
	u8 address = (pv >> 8) & 0xff;
	u8 mask = pv & 0xff;

	mutex_lock(&onyx->mutex);
	अगर (spdअगरlock && onyx->spdअगर_locked) अणु
		/* even अगर alsamixer करोesn't care.. */
		err = -EBUSY;
		जाओ out_unlock;
	पूर्ण
	onyx_पढ़ो_रेजिस्टर(onyx, address, &v);
	c = v;
	c &= ~(mask);
	अगर (!!ucontrol->value.पूर्णांकeger.value[0] ^ polarity)
		c |= mask;
	err = onyx_ग_लिखो_रेजिस्टर(onyx, address, c);

 out_unlock:
	mutex_unlock(&onyx->mutex);

	वापस !err ? (v != c) : err;
पूर्ण

#घोषणा SINGLE_BIT(n, type, description, address, mask, flags)	 	\
अटल स्थिर काष्ठा snd_kcontrol_new n##_control = अणु			\
	.अगरace = SNDRV_CTL_ELEM_IFACE_##type,				\
	.name = description,						\
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,			\
	.info = onyx_snd_single_bit_info,				\
	.get = onyx_snd_single_bit_get,					\
	.put = onyx_snd_single_bit_put,					\
	.निजी_value = (flags << 16) | (address << 8) | mask		\
पूर्ण

SINGLE_BIT(spdअगर,
	   MIXER,
	   SNDRV_CTL_NAME_IEC958("", PLAYBACK, SWITCH),
	   ONYX_REG_DIG_INFO4,
	   ONYX_SPDIF_ENABLE,
	   FLAG_SPDIFLOCK);
SINGLE_BIT(ovr1,
	   MIXER,
	   "Oversampling Rate",
	   ONYX_REG_DAC_CONTROL,
	   ONYX_OVR1,
	   0);
SINGLE_BIT(flt0,
	   MIXER,
	   "Fast Digital Filter Rolloff",
	   ONYX_REG_DAC_FILTER,
	   ONYX_ROLLOFF_FAST,
	   FLAG_POLARITY_INVERT);
SINGLE_BIT(hpf,
	   MIXER,
	   "Highpass Filter",
	   ONYX_REG_ADC_HPF_BYPASS,
	   ONYX_HPF_DISABLE,
	   FLAG_POLARITY_INVERT);
SINGLE_BIT(dm12,
	   MIXER,
	   "Digital De-Emphasis",
	   ONYX_REG_DAC_DEEMPH,
	   ONYX_DIGDEEMPH_CTRL,
	   0);

अटल पूर्णांक onyx_spdअगर_info(काष्ठा snd_kcontrol *kcontrol,
			   काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक onyx_spdअगर_mask_get(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	/* datasheet page 30, all others are 0 */
	ucontrol->value.iec958.status[0] = 0x3e;
	ucontrol->value.iec958.status[1] = 0xff;

	ucontrol->value.iec958.status[3] = 0x3f;
	ucontrol->value.iec958.status[4] = 0x0f;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new onyx_spdअगर_mask = अणु
	.access =	SNDRV_CTL_ELEM_ACCESS_READ,
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		SNDRV_CTL_NAME_IEC958("",PLAYBACK,CON_MASK),
	.info =		onyx_spdअगर_info,
	.get =		onyx_spdअगर_mask_get,
पूर्ण;

अटल पूर्णांक onyx_spdअगर_get(काष्ठा snd_kcontrol *kcontrol,
			  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा onyx *onyx = snd_kcontrol_chip(kcontrol);
	u8 v;

	mutex_lock(&onyx->mutex);
	onyx_पढ़ो_रेजिस्टर(onyx, ONYX_REG_DIG_INFO1, &v);
	ucontrol->value.iec958.status[0] = v & 0x3e;

	onyx_पढ़ो_रेजिस्टर(onyx, ONYX_REG_DIG_INFO2, &v);
	ucontrol->value.iec958.status[1] = v;

	onyx_पढ़ो_रेजिस्टर(onyx, ONYX_REG_DIG_INFO3, &v);
	ucontrol->value.iec958.status[3] = v & 0x3f;

	onyx_पढ़ो_रेजिस्टर(onyx, ONYX_REG_DIG_INFO4, &v);
	ucontrol->value.iec958.status[4] = v & 0x0f;
	mutex_unlock(&onyx->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक onyx_spdअगर_put(काष्ठा snd_kcontrol *kcontrol,
			  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा onyx *onyx = snd_kcontrol_chip(kcontrol);
	u8 v;

	mutex_lock(&onyx->mutex);
	onyx_पढ़ो_रेजिस्टर(onyx, ONYX_REG_DIG_INFO1, &v);
	v = (v & ~0x3e) | (ucontrol->value.iec958.status[0] & 0x3e);
	onyx_ग_लिखो_रेजिस्टर(onyx, ONYX_REG_DIG_INFO1, v);

	v = ucontrol->value.iec958.status[1];
	onyx_ग_लिखो_रेजिस्टर(onyx, ONYX_REG_DIG_INFO2, v);

	onyx_पढ़ो_रेजिस्टर(onyx, ONYX_REG_DIG_INFO3, &v);
	v = (v & ~0x3f) | (ucontrol->value.iec958.status[3] & 0x3f);
	onyx_ग_लिखो_रेजिस्टर(onyx, ONYX_REG_DIG_INFO3, v);

	onyx_पढ़ो_रेजिस्टर(onyx, ONYX_REG_DIG_INFO4, &v);
	v = (v & ~0x0f) | (ucontrol->value.iec958.status[4] & 0x0f);
	onyx_ग_लिखो_रेजिस्टर(onyx, ONYX_REG_DIG_INFO4, v);
	mutex_unlock(&onyx->mutex);

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new onyx_spdअगर_ctrl = अणु
	.access =	SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		SNDRV_CTL_NAME_IEC958("",PLAYBACK,DEFAULT),
	.info =		onyx_spdअगर_info,
	.get =		onyx_spdअगर_get,
	.put =		onyx_spdअगर_put,
पूर्ण;

/* our रेजिस्टरs */

अटल स्थिर u8 रेजिस्टर_map[] = अणु
	ONYX_REG_DAC_ATTEN_LEFT,
	ONYX_REG_DAC_ATTEN_RIGHT,
	ONYX_REG_CONTROL,
	ONYX_REG_DAC_CONTROL,
	ONYX_REG_DAC_DEEMPH,
	ONYX_REG_DAC_FILTER,
	ONYX_REG_DAC_OUTPHASE,
	ONYX_REG_ADC_CONTROL,
	ONYX_REG_ADC_HPF_BYPASS,
	ONYX_REG_DIG_INFO1,
	ONYX_REG_DIG_INFO2,
	ONYX_REG_DIG_INFO3,
	ONYX_REG_DIG_INFO4
पूर्ण;

अटल स्थिर u8 initial_values[ARRAY_SIZE(रेजिस्टर_map)] = अणु
	0x80, 0x80, /* muted */
	ONYX_MRST | ONYX_SRST, /* but handled specially! */
	ONYX_MUTE_LEFT | ONYX_MUTE_RIGHT,
	0, /* no deemphasis */
	ONYX_DAC_FILTER_ALWAYS,
	ONYX_OUTPHASE_INVERTED,
	(-1 /*dB*/ + 8) & 0xF, /* line in selected, -1 dB gain*/
	ONYX_ADC_HPF_ALWAYS,
	(1<<2),	/* pcm audio */
	2,	/* category: pcm coder */
	0,	/* sampling frequency 44.1 kHz, घड़ी accuracy level II */
	1	/* 24 bit depth */
पूर्ण;

/* reset रेजिस्टरs of chip, either to initial or to previous values */
अटल पूर्णांक onyx_रेजिस्टर_init(काष्ठा onyx *onyx)
अणु
	पूर्णांक i;
	u8 val;
	u8 regs[माप(initial_values)];

	अगर (!onyx->initialised) अणु
		स_नकल(regs, initial_values, माप(initial_values));
		अगर (onyx_पढ़ो_रेजिस्टर(onyx, ONYX_REG_CONTROL, &val))
			वापस -1;
		val &= ~ONYX_SILICONVERSION;
		val |= initial_values[3];
		regs[3] = val;
	पूर्ण अन्यथा अणु
		क्रम (i=0; i<माप(रेजिस्टर_map); i++)
			regs[i] = onyx->cache[रेजिस्टर_map[i]-FIRSTREGISTER];
	पूर्ण

	क्रम (i=0; i<माप(रेजिस्टर_map); i++) अणु
		अगर (onyx_ग_लिखो_रेजिस्टर(onyx, रेजिस्टर_map[i], regs[i]))
			वापस -1;
	पूर्ण
	onyx->initialised = 1;
	वापस 0;
पूर्ण

अटल काष्ठा transfer_info onyx_transfers[] = अणु
	/* this is first so we can skip it अगर no input is present...
	 * No hardware exists with that, but it's here as an example
	 * of what to करो :) */
	अणु
		/* analog input */
		.क्रमmats = SNDRV_PCM_FMTBIT_S8 |
			   SNDRV_PCM_FMTBIT_S16_BE |
			   SNDRV_PCM_FMTBIT_S24_BE,
		.rates = SNDRV_PCM_RATE_8000_96000,
		.transfer_in = 1,
		.must_be_घड़ी_source = 0,
		.tag = 0,
	पूर्ण,
	अणु
		/* अगर analog and digital are currently off, anything should go,
		 * so this entry describes everything we can करो... */
		.क्रमmats = SNDRV_PCM_FMTBIT_S8 |
			   SNDRV_PCM_FMTBIT_S16_BE |
			   SNDRV_PCM_FMTBIT_S24_BE
#अगर_घोषित SNDRV_PCM_FMTBIT_COMPRESSED_16BE
			   | SNDRV_PCM_FMTBIT_COMPRESSED_16BE
#पूर्ण_अगर
		,
		.rates = SNDRV_PCM_RATE_8000_96000,
		.tag = 0,
	पूर्ण,
	अणु
		/* analog output */
		.क्रमmats = SNDRV_PCM_FMTBIT_S8 |
			   SNDRV_PCM_FMTBIT_S16_BE |
			   SNDRV_PCM_FMTBIT_S24_BE,
		.rates = SNDRV_PCM_RATE_8000_96000,
		.transfer_in = 0,
		.must_be_घड़ी_source = 0,
		.tag = 1,
	पूर्ण,
	अणु
		/* digital pcm output, also possible क्रम analog out */
		.क्रमmats = SNDRV_PCM_FMTBIT_S8 |
			   SNDRV_PCM_FMTBIT_S16_BE |
			   SNDRV_PCM_FMTBIT_S24_BE,
		.rates = SNDRV_PCM_RATE_32000 |
			 SNDRV_PCM_RATE_44100 |
			 SNDRV_PCM_RATE_48000,
		.transfer_in = 0,
		.must_be_घड़ी_source = 0,
		.tag = 2,
	पूर्ण,
#अगर_घोषित SNDRV_PCM_FMTBIT_COMPRESSED_16BE
	/* Once alsa माला_लो supports क्रम this kind of thing we can add it... */
	अणु
		/* digital compressed output */
		.क्रमmats =  SNDRV_PCM_FMTBIT_COMPRESSED_16BE,
		.rates = SNDRV_PCM_RATE_32000 |
			 SNDRV_PCM_RATE_44100 |
			 SNDRV_PCM_RATE_48000,
		.tag = 2,
	पूर्ण,
#पूर्ण_अगर
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक onyx_usable(काष्ठा codec_info_item *cii,
		       काष्ठा transfer_info *ti,
		       काष्ठा transfer_info *out)
अणु
	u8 v;
	काष्ठा onyx *onyx = cii->codec_data;
	पूर्णांक spdअगर_enabled, analog_enabled;

	mutex_lock(&onyx->mutex);
	onyx_पढ़ो_रेजिस्टर(onyx, ONYX_REG_DIG_INFO4, &v);
	spdअगर_enabled = !!(v & ONYX_SPDIF_ENABLE);
	onyx_पढ़ो_रेजिस्टर(onyx, ONYX_REG_DAC_CONTROL, &v);
	analog_enabled =
		(v & (ONYX_MUTE_RIGHT|ONYX_MUTE_LEFT))
		 != (ONYX_MUTE_RIGHT|ONYX_MUTE_LEFT);
	mutex_unlock(&onyx->mutex);

	चयन (ti->tag) अणु
	हाल 0: वापस 1;
	हाल 1:	वापस analog_enabled;
	हाल 2: वापस spdअगर_enabled;
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक onyx_prepare(काष्ठा codec_info_item *cii,
			काष्ठा bus_info *bi,
			काष्ठा snd_pcm_substream *substream)
अणु
	u8 v;
	काष्ठा onyx *onyx = cii->codec_data;
	पूर्णांक err = -EBUSY;

	mutex_lock(&onyx->mutex);

#अगर_घोषित SNDRV_PCM_FMTBIT_COMPRESSED_16BE
	अगर (substream->runसमय->क्रमmat == SNDRV_PCM_FMTBIT_COMPRESSED_16BE) अणु
		/* mute and lock analog output */
		onyx_पढ़ो_रेजिस्टर(onyx, ONYX_REG_DAC_CONTROL, &v);
		अगर (onyx_ग_लिखो_रेजिस्टर(onyx,
					ONYX_REG_DAC_CONTROL,
					v | ONYX_MUTE_RIGHT | ONYX_MUTE_LEFT))
			जाओ out_unlock;
		onyx->analog_locked = 1;
		err = 0;
		जाओ out_unlock;
	पूर्ण
#पूर्ण_अगर
	चयन (substream->runसमय->rate) अणु
	हाल 32000:
	हाल 44100:
	हाल 48000:
		/* these rates are ok क्रम all outमाला_दो */
		/* FIXME: program spdअगर channel control bits here so that
		 *	  userspace करोesn't have to अगर it only plays pcm! */
		err = 0;
		जाओ out_unlock;
	शेष:
		/* got some rate that the digital output can't करो,
		 * so disable and lock it */
		onyx_पढ़ो_रेजिस्टर(cii->codec_data, ONYX_REG_DIG_INFO4, &v);
		अगर (onyx_ग_लिखो_रेजिस्टर(onyx,
					ONYX_REG_DIG_INFO4,
					v & ~ONYX_SPDIF_ENABLE))
			जाओ out_unlock;
		onyx->spdअगर_locked = 1;
		err = 0;
		जाओ out_unlock;
	पूर्ण

 out_unlock:
	mutex_unlock(&onyx->mutex);

	वापस err;
पूर्ण

अटल पूर्णांक onyx_खोलो(काष्ठा codec_info_item *cii,
		     काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा onyx *onyx = cii->codec_data;

	mutex_lock(&onyx->mutex);
	onyx->खोलो_count++;
	mutex_unlock(&onyx->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक onyx_बंद(काष्ठा codec_info_item *cii,
		      काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा onyx *onyx = cii->codec_data;

	mutex_lock(&onyx->mutex);
	onyx->खोलो_count--;
	अगर (!onyx->खोलो_count)
		onyx->spdअगर_locked = onyx->analog_locked = 0;
	mutex_unlock(&onyx->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक onyx_चयन_घड़ी(काष्ठा codec_info_item *cii,
			     क्रमागत घड़ी_चयन what)
अणु
	काष्ठा onyx *onyx = cii->codec_data;

	mutex_lock(&onyx->mutex);
	/* this *MUST* be more elaborate later... */
	चयन (what) अणु
	हाल CLOCK_SWITCH_PREPARE_SLAVE:
		onyx->codec.gpio->methods->all_amps_off(onyx->codec.gpio);
		अवरोध;
	हाल CLOCK_SWITCH_SLAVE:
		onyx->codec.gpio->methods->all_amps_restore(onyx->codec.gpio);
		अवरोध;
	शेष: /* silence warning */
		अवरोध;
	पूर्ण
	mutex_unlock(&onyx->mutex);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM

अटल पूर्णांक onyx_suspend(काष्ठा codec_info_item *cii, pm_message_t state)
अणु
	काष्ठा onyx *onyx = cii->codec_data;
	u8 v;
	पूर्णांक err = -ENXIO;

	mutex_lock(&onyx->mutex);
	अगर (onyx_पढ़ो_रेजिस्टर(onyx, ONYX_REG_CONTROL, &v))
		जाओ out_unlock;
	onyx_ग_लिखो_रेजिस्टर(onyx, ONYX_REG_CONTROL, v | ONYX_ADPSV | ONYX_DAPSV);
	/* Apple करोes a sleep here but the datasheet says to करो it on resume */
	err = 0;
 out_unlock:
	mutex_unlock(&onyx->mutex);

	वापस err;
पूर्ण

अटल पूर्णांक onyx_resume(काष्ठा codec_info_item *cii)
अणु
	काष्ठा onyx *onyx = cii->codec_data;
	u8 v;
	पूर्णांक err = -ENXIO;

	mutex_lock(&onyx->mutex);

	/* reset codec */
	onyx->codec.gpio->methods->set_hw_reset(onyx->codec.gpio, 0);
	msleep(1);
	onyx->codec.gpio->methods->set_hw_reset(onyx->codec.gpio, 1);
	msleep(1);
	onyx->codec.gpio->methods->set_hw_reset(onyx->codec.gpio, 0);
	msleep(1);

	/* take codec out of suspend (अगर it still is after reset) */
	अगर (onyx_पढ़ो_रेजिस्टर(onyx, ONYX_REG_CONTROL, &v))
		जाओ out_unlock;
	onyx_ग_लिखो_रेजिस्टर(onyx, ONYX_REG_CONTROL, v & ~(ONYX_ADPSV | ONYX_DAPSV));
	/* FIXME: should भागide by sample rate, but 8k is the lowest we go */
	msleep(2205000/8000);
	/* reset all values */
	onyx_रेजिस्टर_init(onyx);
	err = 0;
 out_unlock:
	mutex_unlock(&onyx->mutex);

	वापस err;
पूर्ण

#पूर्ण_अगर /* CONFIG_PM */

अटल काष्ठा codec_info onyx_codec_info = अणु
	.transfers = onyx_transfers,
	.sysघड़ी_factor = 256,
	.bus_factor = 64,
	.owner = THIS_MODULE,
	.usable = onyx_usable,
	.prepare = onyx_prepare,
	.खोलो = onyx_खोलो,
	.बंद = onyx_बंद,
	.चयन_घड़ी = onyx_चयन_घड़ी,
#अगर_घोषित CONFIG_PM
	.suspend = onyx_suspend,
	.resume = onyx_resume,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक onyx_init_codec(काष्ठा aoa_codec *codec)
अणु
	काष्ठा onyx *onyx = codec_to_onyx(codec);
	काष्ठा snd_kcontrol *ctl;
	काष्ठा codec_info *ci = &onyx_codec_info;
	u8 v;
	पूर्णांक err;

	अगर (!onyx->codec.gpio || !onyx->codec.gpio->methods) अणु
		prपूर्णांकk(KERN_ERR PFX "gpios not assigned!!\n");
		वापस -EINVAL;
	पूर्ण

	onyx->codec.gpio->methods->set_hw_reset(onyx->codec.gpio, 0);
	msleep(1);
	onyx->codec.gpio->methods->set_hw_reset(onyx->codec.gpio, 1);
	msleep(1);
	onyx->codec.gpio->methods->set_hw_reset(onyx->codec.gpio, 0);
	msleep(1);

	अगर (onyx_रेजिस्टर_init(onyx)) अणु
		prपूर्णांकk(KERN_ERR PFX "failed to initialise onyx registers\n");
		वापस -ENODEV;
	पूर्ण

	अगर (aoa_snd_device_new(SNDRV_DEV_CODEC, onyx, &ops)) अणु
		prपूर्णांकk(KERN_ERR PFX "failed to create onyx snd device!\n");
		वापस -ENODEV;
	पूर्ण

	/* nothing connected? what a joke! */
	अगर ((onyx->codec.connected & 0xF) == 0)
		वापस -ENOTCONN;

	/* अगर no inमाला_दो are present... */
	अगर ((onyx->codec.connected & 0xC) == 0) अणु
		अगर (!onyx->codec_info)
			onyx->codec_info = kदो_स्मृति(माप(काष्ठा codec_info), GFP_KERNEL);
		अगर (!onyx->codec_info)
			वापस -ENOMEM;
		ci = onyx->codec_info;
		*ci = onyx_codec_info;
		ci->transfers++;
	पूर्ण

	/* अगर no outमाला_दो are present... */
	अगर ((onyx->codec.connected & 3) == 0) अणु
		अगर (!onyx->codec_info)
			onyx->codec_info = kदो_स्मृति(माप(काष्ठा codec_info), GFP_KERNEL);
		अगर (!onyx->codec_info)
			वापस -ENOMEM;
		ci = onyx->codec_info;
		/* this is fine as there have to be inमाला_दो
		 * अगर we end up in this part of the code */
		*ci = onyx_codec_info;
		ci->transfers[1].क्रमmats = 0;
	पूर्ण

	अगर (onyx->codec.soundbus_dev->attach_codec(onyx->codec.soundbus_dev,
						   aoa_get_card(),
						   ci, onyx)) अणु
		prपूर्णांकk(KERN_ERR PFX "error creating onyx pcm\n");
		वापस -ENODEV;
	पूर्ण
#घोषणा ADDCTL(n)							\
	करो अणु								\
		ctl = snd_ctl_new1(&n, onyx);				\
		अगर (ctl) अणु						\
			ctl->id.device =				\
				onyx->codec.soundbus_dev->pcm->device;	\
			err = aoa_snd_ctl_add(ctl);			\
			अगर (err)					\
				जाओ error;				\
		पूर्ण							\
	पूर्ण जबतक (0)

	अगर (onyx->codec.soundbus_dev->pcm) अणु
		/* give the user appropriate controls
		 * depending on what inमाला_दो are connected */
		अगर ((onyx->codec.connected & 0xC) == 0xC)
			ADDCTL(capture_source_control);
		अन्यथा अगर (onyx->codec.connected & 4)
			onyx_set_capture_source(onyx, 0);
		अन्यथा
			onyx_set_capture_source(onyx, 1);
		अगर (onyx->codec.connected & 0xC)
			ADDCTL(inputgain_control);

		/* depending on what output is connected,
		 * give the user appropriate controls */
		अगर (onyx->codec.connected & 1) अणु
			ADDCTL(volume_control);
			ADDCTL(mute_control);
			ADDCTL(ovr1_control);
			ADDCTL(flt0_control);
			ADDCTL(hpf_control);
			ADDCTL(dm12_control);
			/* spdअगर control शेषs to off */
		पूर्ण
		अगर (onyx->codec.connected & 2) अणु
			ADDCTL(onyx_spdअगर_mask);
			ADDCTL(onyx_spdअगर_ctrl);
		पूर्ण
		अगर ((onyx->codec.connected & 3) == 3)
			ADDCTL(spdअगर_control);
		/* अगर only S/PDIF is connected, enable it unconditionally */
		अगर ((onyx->codec.connected & 3) == 2) अणु
			onyx_पढ़ो_रेजिस्टर(onyx, ONYX_REG_DIG_INFO4, &v);
			v |= ONYX_SPDIF_ENABLE;
			onyx_ग_लिखो_रेजिस्टर(onyx, ONYX_REG_DIG_INFO4, v);
		पूर्ण
	पूर्ण
#अघोषित ADDCTL
	prपूर्णांकk(KERN_INFO PFX "attached to onyx codec via i2c\n");

	वापस 0;
 error:
	onyx->codec.soundbus_dev->detach_codec(onyx->codec.soundbus_dev, onyx);
	snd_device_मुक्त(aoa_get_card(), onyx);
	वापस err;
पूर्ण

अटल व्योम onyx_निकास_codec(काष्ठा aoa_codec *codec)
अणु
	काष्ठा onyx *onyx = codec_to_onyx(codec);

	अगर (!onyx->codec.soundbus_dev) अणु
		prपूर्णांकk(KERN_ERR PFX "onyx_exit_codec called without soundbus_dev!\n");
		वापस;
	पूर्ण
	onyx->codec.soundbus_dev->detach_codec(onyx->codec.soundbus_dev, onyx);
पूर्ण

अटल पूर्णांक onyx_i2c_probe(काष्ठा i2c_client *client,
			  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device_node *node = client->dev.of_node;
	काष्ठा onyx *onyx;
	u8 dummy;

	onyx = kzalloc(माप(काष्ठा onyx), GFP_KERNEL);

	अगर (!onyx)
		वापस -ENOMEM;

	mutex_init(&onyx->mutex);
	onyx->i2c = client;
	i2c_set_clientdata(client, onyx);

	/* we try to पढ़ो from रेजिस्टर ONYX_REG_CONTROL
	 * to check अगर the codec is present */
	अगर (onyx_पढ़ो_रेजिस्टर(onyx, ONYX_REG_CONTROL, &dummy) != 0) अणु
		prपूर्णांकk(KERN_ERR PFX "failed to read control register\n");
		जाओ fail;
	पूर्ण

	strscpy(onyx->codec.name, "onyx", MAX_CODEC_NAME_LEN);
	onyx->codec.owner = THIS_MODULE;
	onyx->codec.init = onyx_init_codec;
	onyx->codec.निकास = onyx_निकास_codec;
	onyx->codec.node = of_node_get(node);

	अगर (aoa_codec_रेजिस्टर(&onyx->codec)) अणु
		जाओ fail;
	पूर्ण
	prपूर्णांकk(KERN_DEBUG PFX "created and attached onyx instance\n");
	वापस 0;
 fail:
	kमुक्त(onyx);
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक onyx_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा onyx *onyx = i2c_get_clientdata(client);

	aoa_codec_unरेजिस्टर(&onyx->codec);
	of_node_put(onyx->codec.node);
	kमुक्त(onyx->codec_info);
	kमुक्त(onyx);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id onyx_i2c_id[] = अणु
	अणु "MAC,pcm3052", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c,onyx_i2c_id);

अटल काष्ठा i2c_driver onyx_driver = अणु
	.driver = अणु
		.name = "aoa_codec_onyx",
	पूर्ण,
	.probe = onyx_i2c_probe,
	.हटाओ = onyx_i2c_हटाओ,
	.id_table = onyx_i2c_id,
पूर्ण;

module_i2c_driver(onyx_driver);
