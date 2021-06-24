<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Apple Onboard Audio driver क्रम tas codec
 *
 * Copyright 2006 Johannes Berg <johannes@sipsolutions.net>
 *
 * Open questions:
 *  - How to distinguish between 3004 and versions?
 *
 * FIXMEs:
 *  - This codec driver करोesn't honour the 'connected'
 *    property of the aoa_codec काष्ठा, hence अगर
 *    it is used in machines where not everything is
 *    connected it will display wrong mixer elements.
 *  - Driver assumes that the microphone is always
 *    monaureal and connected to the right channel of
 *    the input. This should also be a codec-dependent
 *    flag, maybe the codec should have 3 dअगरferent
 *    bits क्रम the three dअगरferent possibilities how
 *    it can be hooked up...
 *    But as दीर्घ as I करोn't see any hardware hooked
 *    up that way...
 *  - As Apple notes in their code, the tas3004 seems
 *    to delay the right channel by one sample. You can
 *    see this when क्रम example recording stereo in
 *    audacity, or recording the tas output via cable
 *    on another machine (use a sinus generator or so).
 *    I tried programming the BiQuads but couldn't
 *    make the delay work, maybe someone can पढ़ो the
 *    datasheet and fix it. The relevant Apple comment
 *    is in AppleTAS3004Audio.cpp lines 1637 ff. Note
 *    that their comment describing how they program
 *    the filters sucks...
 *
 * Other things:
 *  - this should actually रेजिस्टर *two* aoa_codec
 *    काष्ठाs since it has two inमाला_दो. Then it must
 *    use the prepare callback to क्रमbid running the
 *    secondary output on a dअगरferent घड़ी.
 *    Also, whatever bus knows how to करो this must
 *    provide two soundbus_dev devices and the fabric
 *    must be able to link them correctly.
 *
 *    I करोn't even know अगर Apple ever uses the second
 *    port on the tas3004 though, I करोn't think their
 *    i2s controllers can even करो it. OTOH, they all
 *    derive the घड़ीs from common घड़ीs, so it
 *    might just be possible. The framework allows the
 *    codec to refine the transfer_info items in the
 *    usable callback, so we can simply हटाओ the
 *    rates the second instance is not using when it
 *    actually is in use.
 *    Maybe we'll need to make the sound busses have
 *    a 'clock group id' value so the codec can
 *    determine अगर the two outमाला_दो can be driven at
 *    the same समय. But that is likely overसमाप्त, up
 *    to the fabric to not link them up incorrectly,
 *    and up to the hardware designer to not wire
 *    them up in some weird unusable way.
 */
#समावेश <मानकघोष.स>
#समावेश <linux/i2c.h>
#समावेश <यंत्र/pmac_low_i2c.h>
#समावेश <यंत्र/prom.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>

MODULE_AUTHOR("Johannes Berg <johannes@sipsolutions.net>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("tas codec driver for snd-aoa");

#समावेश "tas.h"
#समावेश "tas-gain-table.h"
#समावेश "tas-basstreble.h"
#समावेश "../aoa.h"
#समावेश "../soundbus/soundbus.h"

#घोषणा PFX "snd-aoa-codec-tas: "


काष्ठा tas अणु
	काष्ठा aoa_codec	codec;
	काष्ठा i2c_client	*i2c;
	u32			mute_l:1, mute_r:1 ,
				controls_created:1 ,
				drc_enabled:1,
				hw_enabled:1;
	u8			cached_volume_l, cached_volume_r;
	u8			mixer_l[3], mixer_r[3];
	u8			bass, treble;
	u8			acr;
	पूर्णांक			drc_range;
	/* protects hardware access against concurrency from
	 * userspace when hitting controls and during
	 * codec init/suspend/resume */
	काष्ठा mutex		mtx;
पूर्ण;

अटल पूर्णांक tas_reset_init(काष्ठा tas *tas);

अटल काष्ठा tas *codec_to_tas(काष्ठा aoa_codec *codec)
अणु
	वापस container_of(codec, काष्ठा tas, codec);
पूर्ण

अटल अंतरभूत पूर्णांक tas_ग_लिखो_reg(काष्ठा tas *tas, u8 reg, u8 len, u8 *data)
अणु
	अगर (len == 1)
		वापस i2c_smbus_ग_लिखो_byte_data(tas->i2c, reg, *data);
	अन्यथा
		वापस i2c_smbus_ग_लिखो_i2c_block_data(tas->i2c, reg, len, data);
पूर्ण

अटल व्योम tas3004_set_drc(काष्ठा tas *tas)
अणु
	अचिन्हित अक्षर val[6];

	अगर (tas->drc_enabled)
		val[0] = 0x50; /* 3:1 above threshold */
	अन्यथा
		val[0] = 0x51; /* disabled */
	val[1] = 0x02; /* 1:1 below threshold */
	अगर (tas->drc_range > 0xef)
		val[2] = 0xef;
	अन्यथा अगर (tas->drc_range < 0)
		val[2] = 0x00;
	अन्यथा
		val[2] = tas->drc_range;
	val[3] = 0xb0;
	val[4] = 0x60;
	val[5] = 0xa0;

	tas_ग_लिखो_reg(tas, TAS_REG_DRC, 6, val);
पूर्ण

अटल व्योम tas_set_treble(काष्ठा tas *tas)
अणु
	u8 पंचांगp;

	पंचांगp = tas3004_treble(tas->treble);
	tas_ग_लिखो_reg(tas, TAS_REG_TREBLE, 1, &पंचांगp);
पूर्ण

अटल व्योम tas_set_bass(काष्ठा tas *tas)
अणु
	u8 पंचांगp;

	पंचांगp = tas3004_bass(tas->bass);
	tas_ग_लिखो_reg(tas, TAS_REG_BASS, 1, &पंचांगp);
पूर्ण

अटल व्योम tas_set_volume(काष्ठा tas *tas)
अणु
	u8 block[6];
	पूर्णांक पंचांगp;
	u8 left, right;

	left = tas->cached_volume_l;
	right = tas->cached_volume_r;

	अगर (left > 177) left = 177;
	अगर (right > 177) right = 177;

	अगर (tas->mute_l) left = 0;
	अगर (tas->mute_r) right = 0;

	/* analysing the volume and mixer tables shows
	 * that they are similar enough when we shअगरt
	 * the mixer table करोwn by 4 bits. The error
	 * is miniscule, in just one item the error
	 * is 1, at a value of 0x07f17b (mixer table
	 * value is 0x07f17a) */
	पंचांगp = tas_gaपूर्णांकable[left];
	block[0] = पंचांगp>>20;
	block[1] = पंचांगp>>12;
	block[2] = पंचांगp>>4;
	पंचांगp = tas_gaपूर्णांकable[right];
	block[3] = पंचांगp>>20;
	block[4] = पंचांगp>>12;
	block[5] = पंचांगp>>4;
	tas_ग_लिखो_reg(tas, TAS_REG_VOL, 6, block);
पूर्ण

अटल व्योम tas_set_mixer(काष्ठा tas *tas)
अणु
	u8 block[9];
	पूर्णांक पंचांगp, i;
	u8 val;

	क्रम (i=0;i<3;i++) अणु
		val = tas->mixer_l[i];
		अगर (val > 177) val = 177;
		पंचांगp = tas_gaपूर्णांकable[val];
		block[3*i+0] = पंचांगp>>16;
		block[3*i+1] = पंचांगp>>8;
		block[3*i+2] = पंचांगp;
	पूर्ण
	tas_ग_लिखो_reg(tas, TAS_REG_LMIX, 9, block);

	क्रम (i=0;i<3;i++) अणु
		val = tas->mixer_r[i];
		अगर (val > 177) val = 177;
		पंचांगp = tas_gaपूर्णांकable[val];
		block[3*i+0] = पंचांगp>>16;
		block[3*i+1] = पंचांगp>>8;
		block[3*i+2] = पंचांगp;
	पूर्ण
	tas_ग_लिखो_reg(tas, TAS_REG_RMIX, 9, block);
पूर्ण

/* alsa stuff */

अटल पूर्णांक tas_dev_रेजिस्टर(काष्ठा snd_device *dev)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_device_ops ops = अणु
	.dev_रेजिस्टर = tas_dev_रेजिस्टर,
पूर्ण;

अटल पूर्णांक tas_snd_vol_info(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 177;
	वापस 0;
पूर्ण

अटल पूर्णांक tas_snd_vol_get(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा tas *tas = snd_kcontrol_chip(kcontrol);

	mutex_lock(&tas->mtx);
	ucontrol->value.पूर्णांकeger.value[0] = tas->cached_volume_l;
	ucontrol->value.पूर्णांकeger.value[1] = tas->cached_volume_r;
	mutex_unlock(&tas->mtx);
	वापस 0;
पूर्ण

अटल पूर्णांक tas_snd_vol_put(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा tas *tas = snd_kcontrol_chip(kcontrol);

	अगर (ucontrol->value.पूर्णांकeger.value[0] < 0 ||
	    ucontrol->value.पूर्णांकeger.value[0] > 177)
		वापस -EINVAL;
	अगर (ucontrol->value.पूर्णांकeger.value[1] < 0 ||
	    ucontrol->value.पूर्णांकeger.value[1] > 177)
		वापस -EINVAL;

	mutex_lock(&tas->mtx);
	अगर (tas->cached_volume_l == ucontrol->value.पूर्णांकeger.value[0]
	 && tas->cached_volume_r == ucontrol->value.पूर्णांकeger.value[1]) अणु
		mutex_unlock(&tas->mtx);
		वापस 0;
	पूर्ण

	tas->cached_volume_l = ucontrol->value.पूर्णांकeger.value[0];
	tas->cached_volume_r = ucontrol->value.पूर्णांकeger.value[1];
	अगर (tas->hw_enabled)
		tas_set_volume(tas);
	mutex_unlock(&tas->mtx);
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new volume_control = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Master Playback Volume",
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.info = tas_snd_vol_info,
	.get = tas_snd_vol_get,
	.put = tas_snd_vol_put,
पूर्ण;

#घोषणा tas_snd_mute_info	snd_ctl_boolean_stereo_info

अटल पूर्णांक tas_snd_mute_get(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा tas *tas = snd_kcontrol_chip(kcontrol);

	mutex_lock(&tas->mtx);
	ucontrol->value.पूर्णांकeger.value[0] = !tas->mute_l;
	ucontrol->value.पूर्णांकeger.value[1] = !tas->mute_r;
	mutex_unlock(&tas->mtx);
	वापस 0;
पूर्ण

अटल पूर्णांक tas_snd_mute_put(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा tas *tas = snd_kcontrol_chip(kcontrol);

	mutex_lock(&tas->mtx);
	अगर (tas->mute_l == !ucontrol->value.पूर्णांकeger.value[0]
	 && tas->mute_r == !ucontrol->value.पूर्णांकeger.value[1]) अणु
		mutex_unlock(&tas->mtx);
		वापस 0;
	पूर्ण

	tas->mute_l = !ucontrol->value.पूर्णांकeger.value[0];
	tas->mute_r = !ucontrol->value.पूर्णांकeger.value[1];
	अगर (tas->hw_enabled)
		tas_set_volume(tas);
	mutex_unlock(&tas->mtx);
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new mute_control = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Master Playback Switch",
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.info = tas_snd_mute_info,
	.get = tas_snd_mute_get,
	.put = tas_snd_mute_put,
पूर्ण;

अटल पूर्णांक tas_snd_mixer_info(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 177;
	वापस 0;
पूर्ण

अटल पूर्णांक tas_snd_mixer_get(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा tas *tas = snd_kcontrol_chip(kcontrol);
	पूर्णांक idx = kcontrol->निजी_value;

	mutex_lock(&tas->mtx);
	ucontrol->value.पूर्णांकeger.value[0] = tas->mixer_l[idx];
	ucontrol->value.पूर्णांकeger.value[1] = tas->mixer_r[idx];
	mutex_unlock(&tas->mtx);

	वापस 0;
पूर्ण

अटल पूर्णांक tas_snd_mixer_put(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा tas *tas = snd_kcontrol_chip(kcontrol);
	पूर्णांक idx = kcontrol->निजी_value;

	mutex_lock(&tas->mtx);
	अगर (tas->mixer_l[idx] == ucontrol->value.पूर्णांकeger.value[0]
	 && tas->mixer_r[idx] == ucontrol->value.पूर्णांकeger.value[1]) अणु
		mutex_unlock(&tas->mtx);
		वापस 0;
	पूर्ण

	tas->mixer_l[idx] = ucontrol->value.पूर्णांकeger.value[0];
	tas->mixer_r[idx] = ucontrol->value.पूर्णांकeger.value[1];

	अगर (tas->hw_enabled)
		tas_set_mixer(tas);
	mutex_unlock(&tas->mtx);
	वापस 1;
पूर्ण

#घोषणा MIXER_CONTROL(n,descr,idx)			\
अटल स्थिर काष्ठा snd_kcontrol_new n##_control = अणु	\
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,		\
	.name = descr " Playback Volume",		\
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,	\
	.info = tas_snd_mixer_info,			\
	.get = tas_snd_mixer_get,			\
	.put = tas_snd_mixer_put,			\
	.निजी_value = idx,				\
पूर्ण

MIXER_CONTROL(pcm1, "PCM", 0);
MIXER_CONTROL(monitor, "Monitor", 2);

अटल पूर्णांक tas_snd_drc_range_info(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = TAS3004_DRC_MAX;
	वापस 0;
पूर्ण

अटल पूर्णांक tas_snd_drc_range_get(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा tas *tas = snd_kcontrol_chip(kcontrol);

	mutex_lock(&tas->mtx);
	ucontrol->value.पूर्णांकeger.value[0] = tas->drc_range;
	mutex_unlock(&tas->mtx);
	वापस 0;
पूर्ण

अटल पूर्णांक tas_snd_drc_range_put(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा tas *tas = snd_kcontrol_chip(kcontrol);

	अगर (ucontrol->value.पूर्णांकeger.value[0] < 0 ||
	    ucontrol->value.पूर्णांकeger.value[0] > TAS3004_DRC_MAX)
		वापस -EINVAL;

	mutex_lock(&tas->mtx);
	अगर (tas->drc_range == ucontrol->value.पूर्णांकeger.value[0]) अणु
		mutex_unlock(&tas->mtx);
		वापस 0;
	पूर्ण

	tas->drc_range = ucontrol->value.पूर्णांकeger.value[0];
	अगर (tas->hw_enabled)
		tas3004_set_drc(tas);
	mutex_unlock(&tas->mtx);
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new drc_range_control = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "DRC Range",
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.info = tas_snd_drc_range_info,
	.get = tas_snd_drc_range_get,
	.put = tas_snd_drc_range_put,
पूर्ण;

#घोषणा tas_snd_drc_चयन_info		snd_ctl_boolean_mono_info

अटल पूर्णांक tas_snd_drc_चयन_get(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा tas *tas = snd_kcontrol_chip(kcontrol);

	mutex_lock(&tas->mtx);
	ucontrol->value.पूर्णांकeger.value[0] = tas->drc_enabled;
	mutex_unlock(&tas->mtx);
	वापस 0;
पूर्ण

अटल पूर्णांक tas_snd_drc_चयन_put(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा tas *tas = snd_kcontrol_chip(kcontrol);

	mutex_lock(&tas->mtx);
	अगर (tas->drc_enabled == ucontrol->value.पूर्णांकeger.value[0]) अणु
		mutex_unlock(&tas->mtx);
		वापस 0;
	पूर्ण

	tas->drc_enabled = !!ucontrol->value.पूर्णांकeger.value[0];
	अगर (tas->hw_enabled)
		tas3004_set_drc(tas);
	mutex_unlock(&tas->mtx);
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new drc_चयन_control = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "DRC Range Switch",
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.info = tas_snd_drc_चयन_info,
	.get = tas_snd_drc_चयन_get,
	.put = tas_snd_drc_चयन_put,
पूर्ण;

अटल पूर्णांक tas_snd_capture_source_info(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[] = अणु "Line-In", "Microphone" पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 2, texts);
पूर्ण

अटल पूर्णांक tas_snd_capture_source_get(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा tas *tas = snd_kcontrol_chip(kcontrol);

	mutex_lock(&tas->mtx);
	ucontrol->value.क्रमागतerated.item[0] = !!(tas->acr & TAS_ACR_INPUT_B);
	mutex_unlock(&tas->mtx);
	वापस 0;
पूर्ण

अटल पूर्णांक tas_snd_capture_source_put(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा tas *tas = snd_kcontrol_chip(kcontrol);
	पूर्णांक oldacr;

	अगर (ucontrol->value.क्रमागतerated.item[0] > 1)
		वापस -EINVAL;
	mutex_lock(&tas->mtx);
	oldacr = tas->acr;

	/*
	 * Despite what the data sheet says in one place, the
	 * TAS_ACR_B_MONAUREAL bit क्रमces mono output even when
	 * input A (line in) is selected.
	 */
	tas->acr &= ~(TAS_ACR_INPUT_B | TAS_ACR_B_MONAUREAL);
	अगर (ucontrol->value.क्रमागतerated.item[0])
		tas->acr |= TAS_ACR_INPUT_B | TAS_ACR_B_MONAUREAL |
		      TAS_ACR_B_MON_SEL_RIGHT;
	अगर (oldacr == tas->acr) अणु
		mutex_unlock(&tas->mtx);
		वापस 0;
	पूर्ण
	अगर (tas->hw_enabled)
		tas_ग_लिखो_reg(tas, TAS_REG_ACR, 1, &tas->acr);
	mutex_unlock(&tas->mtx);
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
	.info = tas_snd_capture_source_info,
	.get = tas_snd_capture_source_get,
	.put = tas_snd_capture_source_put,
पूर्ण;

अटल पूर्णांक tas_snd_treble_info(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = TAS3004_TREBLE_MIN;
	uinfo->value.पूर्णांकeger.max = TAS3004_TREBLE_MAX;
	वापस 0;
पूर्ण

अटल पूर्णांक tas_snd_treble_get(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा tas *tas = snd_kcontrol_chip(kcontrol);

	mutex_lock(&tas->mtx);
	ucontrol->value.पूर्णांकeger.value[0] = tas->treble;
	mutex_unlock(&tas->mtx);
	वापस 0;
पूर्ण

अटल पूर्णांक tas_snd_treble_put(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा tas *tas = snd_kcontrol_chip(kcontrol);

	अगर (ucontrol->value.पूर्णांकeger.value[0] < TAS3004_TREBLE_MIN ||
	    ucontrol->value.पूर्णांकeger.value[0] > TAS3004_TREBLE_MAX)
		वापस -EINVAL;
	mutex_lock(&tas->mtx);
	अगर (tas->treble == ucontrol->value.पूर्णांकeger.value[0]) अणु
		mutex_unlock(&tas->mtx);
		वापस 0;
	पूर्ण

	tas->treble = ucontrol->value.पूर्णांकeger.value[0];
	अगर (tas->hw_enabled)
		tas_set_treble(tas);
	mutex_unlock(&tas->mtx);
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new treble_control = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Treble",
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.info = tas_snd_treble_info,
	.get = tas_snd_treble_get,
	.put = tas_snd_treble_put,
पूर्ण;

अटल पूर्णांक tas_snd_bass_info(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = TAS3004_BASS_MIN;
	uinfo->value.पूर्णांकeger.max = TAS3004_BASS_MAX;
	वापस 0;
पूर्ण

अटल पूर्णांक tas_snd_bass_get(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा tas *tas = snd_kcontrol_chip(kcontrol);

	mutex_lock(&tas->mtx);
	ucontrol->value.पूर्णांकeger.value[0] = tas->bass;
	mutex_unlock(&tas->mtx);
	वापस 0;
पूर्ण

अटल पूर्णांक tas_snd_bass_put(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा tas *tas = snd_kcontrol_chip(kcontrol);

	अगर (ucontrol->value.पूर्णांकeger.value[0] < TAS3004_BASS_MIN ||
	    ucontrol->value.पूर्णांकeger.value[0] > TAS3004_BASS_MAX)
		वापस -EINVAL;
	mutex_lock(&tas->mtx);
	अगर (tas->bass == ucontrol->value.पूर्णांकeger.value[0]) अणु
		mutex_unlock(&tas->mtx);
		वापस 0;
	पूर्ण

	tas->bass = ucontrol->value.पूर्णांकeger.value[0];
	अगर (tas->hw_enabled)
		tas_set_bass(tas);
	mutex_unlock(&tas->mtx);
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new bass_control = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Bass",
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.info = tas_snd_bass_info,
	.get = tas_snd_bass_get,
	.put = tas_snd_bass_put,
पूर्ण;

अटल काष्ठा transfer_info tas_transfers[] = अणु
	अणु
		/* input */
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_BE | SNDRV_PCM_FMTBIT_S24_BE,
		.rates = SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_44100 | SNDRV_PCM_RATE_48000,
		.transfer_in = 1,
	पूर्ण,
	अणु
		/* output */
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_BE | SNDRV_PCM_FMTBIT_S24_BE,
		.rates = SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_44100 | SNDRV_PCM_RATE_48000,
		.transfer_in = 0,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक tas_usable(काष्ठा codec_info_item *cii,
		      काष्ठा transfer_info *ti,
		      काष्ठा transfer_info *out)
अणु
	वापस 1;
पूर्ण

अटल पूर्णांक tas_reset_init(काष्ठा tas *tas)
अणु
	u8 पंचांगp;

	tas->codec.gpio->methods->all_amps_off(tas->codec.gpio);
	msleep(5);
	tas->codec.gpio->methods->set_hw_reset(tas->codec.gpio, 0);
	msleep(5);
	tas->codec.gpio->methods->set_hw_reset(tas->codec.gpio, 1);
	msleep(20);
	tas->codec.gpio->methods->set_hw_reset(tas->codec.gpio, 0);
	msleep(10);
	tas->codec.gpio->methods->all_amps_restore(tas->codec.gpio);

	पंचांगp = TAS_MCS_SCLK64 | TAS_MCS_SPORT_MODE_I2S | TAS_MCS_SPORT_WL_24BIT;
	अगर (tas_ग_लिखो_reg(tas, TAS_REG_MCS, 1, &पंचांगp))
		जाओ outerr;

	tas->acr |= TAS_ACR_ANALOG_PDOWN;
	अगर (tas_ग_लिखो_reg(tas, TAS_REG_ACR, 1, &tas->acr))
		जाओ outerr;

	पंचांगp = 0;
	अगर (tas_ग_लिखो_reg(tas, TAS_REG_MCS2, 1, &पंचांगp))
		जाओ outerr;

	tas3004_set_drc(tas);

	/* Set treble & bass to 0dB */
	tas->treble = TAS3004_TREBLE_ZERO;
	tas->bass = TAS3004_BASS_ZERO;
	tas_set_treble(tas);
	tas_set_bass(tas);

	tas->acr &= ~TAS_ACR_ANALOG_PDOWN;
	अगर (tas_ग_लिखो_reg(tas, TAS_REG_ACR, 1, &tas->acr))
		जाओ outerr;

	वापस 0;
 outerr:
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक tas_चयन_घड़ी(काष्ठा codec_info_item *cii, क्रमागत घड़ी_चयन घड़ी)
अणु
	काष्ठा tas *tas = cii->codec_data;

	चयन(घड़ी) अणु
	हाल CLOCK_SWITCH_PREPARE_SLAVE:
		/* Clocks are going away, mute mute mute */
		tas->codec.gpio->methods->all_amps_off(tas->codec.gpio);
		tas->hw_enabled = 0;
		अवरोध;
	हाल CLOCK_SWITCH_SLAVE:
		/* Clocks are back, re-init the codec */
		mutex_lock(&tas->mtx);
		tas_reset_init(tas);
		tas_set_volume(tas);
		tas_set_mixer(tas);
		tas->hw_enabled = 1;
		tas->codec.gpio->methods->all_amps_restore(tas->codec.gpio);
		mutex_unlock(&tas->mtx);
		अवरोध;
	शेष:
		/* करोesn't happen as of now */
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
/* we are controlled via i2c and assume that is always up
 * If that wasn't the case, we'd have to suspend once
 * our i2c device is suspended, and then take note of that! */
अटल पूर्णांक tas_suspend(काष्ठा tas *tas)
अणु
	mutex_lock(&tas->mtx);
	tas->hw_enabled = 0;
	tas->acr |= TAS_ACR_ANALOG_PDOWN;
	tas_ग_लिखो_reg(tas, TAS_REG_ACR, 1, &tas->acr);
	mutex_unlock(&tas->mtx);
	वापस 0;
पूर्ण

अटल पूर्णांक tas_resume(काष्ठा tas *tas)
अणु
	/* reset codec */
	mutex_lock(&tas->mtx);
	tas_reset_init(tas);
	tas_set_volume(tas);
	tas_set_mixer(tas);
	tas->hw_enabled = 1;
	mutex_unlock(&tas->mtx);
	वापस 0;
पूर्ण

अटल पूर्णांक _tas_suspend(काष्ठा codec_info_item *cii, pm_message_t state)
अणु
	वापस tas_suspend(cii->codec_data);
पूर्ण

अटल पूर्णांक _tas_resume(काष्ठा codec_info_item *cii)
अणु
	वापस tas_resume(cii->codec_data);
पूर्ण
#अन्यथा /* CONFIG_PM */
#घोषणा _tas_suspend	शून्य
#घोषणा _tas_resume	शून्य
#पूर्ण_अगर /* CONFIG_PM */

अटल काष्ठा codec_info tas_codec_info = अणु
	.transfers = tas_transfers,
	/* in theory, we can drive it at 512 too...
	 * but so far the framework करोesn't allow
	 * क्रम that and I करोn't see much poपूर्णांक in it. */
	.sysघड़ी_factor = 256,
	/* same here, could be 32 क्रम just one 16 bit क्रमmat */
	.bus_factor = 64,
	.owner = THIS_MODULE,
	.usable = tas_usable,
	.चयन_घड़ी = tas_चयन_घड़ी,
	.suspend = _tas_suspend,
	.resume = _tas_resume,
पूर्ण;

अटल पूर्णांक tas_init_codec(काष्ठा aoa_codec *codec)
अणु
	काष्ठा tas *tas = codec_to_tas(codec);
	पूर्णांक err;

	अगर (!tas->codec.gpio || !tas->codec.gpio->methods) अणु
		prपूर्णांकk(KERN_ERR PFX "gpios not assigned!!\n");
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&tas->mtx);
	अगर (tas_reset_init(tas)) अणु
		prपूर्णांकk(KERN_ERR PFX "tas failed to initialise\n");
		mutex_unlock(&tas->mtx);
		वापस -ENXIO;
	पूर्ण
	tas->hw_enabled = 1;
	mutex_unlock(&tas->mtx);

	अगर (tas->codec.soundbus_dev->attach_codec(tas->codec.soundbus_dev,
						   aoa_get_card(),
						   &tas_codec_info, tas)) अणु
		prपूर्णांकk(KERN_ERR PFX "error attaching tas to soundbus\n");
		वापस -ENODEV;
	पूर्ण

	अगर (aoa_snd_device_new(SNDRV_DEV_CODEC, tas, &ops)) अणु
		prपूर्णांकk(KERN_ERR PFX "failed to create tas snd device!\n");
		वापस -ENODEV;
	पूर्ण
	err = aoa_snd_ctl_add(snd_ctl_new1(&volume_control, tas));
	अगर (err)
		जाओ error;

	err = aoa_snd_ctl_add(snd_ctl_new1(&mute_control, tas));
	अगर (err)
		जाओ error;

	err = aoa_snd_ctl_add(snd_ctl_new1(&pcm1_control, tas));
	अगर (err)
		जाओ error;

	err = aoa_snd_ctl_add(snd_ctl_new1(&monitor_control, tas));
	अगर (err)
		जाओ error;

	err = aoa_snd_ctl_add(snd_ctl_new1(&capture_source_control, tas));
	अगर (err)
		जाओ error;

	err = aoa_snd_ctl_add(snd_ctl_new1(&drc_range_control, tas));
	अगर (err)
		जाओ error;

	err = aoa_snd_ctl_add(snd_ctl_new1(&drc_चयन_control, tas));
	अगर (err)
		जाओ error;

	err = aoa_snd_ctl_add(snd_ctl_new1(&treble_control, tas));
	अगर (err)
		जाओ error;

	err = aoa_snd_ctl_add(snd_ctl_new1(&bass_control, tas));
	अगर (err)
		जाओ error;

	वापस 0;
 error:
	tas->codec.soundbus_dev->detach_codec(tas->codec.soundbus_dev, tas);
	snd_device_मुक्त(aoa_get_card(), tas);
	वापस err;
पूर्ण

अटल व्योम tas_निकास_codec(काष्ठा aoa_codec *codec)
अणु
	काष्ठा tas *tas = codec_to_tas(codec);

	अगर (!tas->codec.soundbus_dev)
		वापस;
	tas->codec.soundbus_dev->detach_codec(tas->codec.soundbus_dev, tas);
पूर्ण


अटल पूर्णांक tas_i2c_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device_node *node = client->dev.of_node;
	काष्ठा tas *tas;

	tas = kzalloc(माप(काष्ठा tas), GFP_KERNEL);

	अगर (!tas)
		वापस -ENOMEM;

	mutex_init(&tas->mtx);
	tas->i2c = client;
	i2c_set_clientdata(client, tas);

	/* seems that half is a saner शेष */
	tas->drc_range = TAS3004_DRC_MAX / 2;

	strscpy(tas->codec.name, "tas", MAX_CODEC_NAME_LEN);
	tas->codec.owner = THIS_MODULE;
	tas->codec.init = tas_init_codec;
	tas->codec.निकास = tas_निकास_codec;
	tas->codec.node = of_node_get(node);

	अगर (aoa_codec_रेजिस्टर(&tas->codec)) अणु
		जाओ fail;
	पूर्ण
	prपूर्णांकk(KERN_DEBUG
	       "snd-aoa-codec-tas: tas found, addr 0x%02x on %pOF\n",
	       (अचिन्हित पूर्णांक)client->addr, node);
	वापस 0;
 fail:
	mutex_destroy(&tas->mtx);
	kमुक्त(tas);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक tas_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा tas *tas = i2c_get_clientdata(client);
	u8 पंचांगp = TAS_ACR_ANALOG_PDOWN;

	aoa_codec_unरेजिस्टर(&tas->codec);
	of_node_put(tas->codec.node);

	/* घातer करोwn codec chip */
	tas_ग_लिखो_reg(tas, TAS_REG_ACR, 1, &पंचांगp);

	mutex_destroy(&tas->mtx);
	kमुक्त(tas);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id tas_i2c_id[] = अणु
	अणु "MAC,tas3004", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c,tas_i2c_id);

अटल काष्ठा i2c_driver tas_driver = अणु
	.driver = अणु
		.name = "aoa_codec_tas",
	पूर्ण,
	.probe = tas_i2c_probe,
	.हटाओ = tas_i2c_हटाओ,
	.id_table = tas_i2c_id,
पूर्ण;

module_i2c_driver(tas_driver);
