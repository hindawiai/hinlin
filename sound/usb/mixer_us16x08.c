<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   Tascam US-16x08 ALSA driver
 *
 *   Copyright (c) 2016 by Detlef Urban (onkel@paraair.de)
 */

#समावेश <linux/slab.h>
#समावेश <linux/usb.h>
#समावेश <linux/usb/audio-v2.h>

#समावेश <sound/core.h>
#समावेश <sound/control.h>

#समावेश "usbaudio.h"
#समावेश "mixer.h"
#समावेश "helper.h"

#समावेश "mixer_us16x08.h"

/* USB control message ढाँचाs */
अटल स्थिर अक्षर route_msg[] = अणु
	0x61,
	0x02,
	0x03, /* input from master (0x02) or input from computer bus (0x03) */
	0x62,
	0x02,
	0x01, /* input index (0x01/0x02 eq. left/right) or bus (0x01-0x08) */
	0x41,
	0x01,
	0x61,
	0x02,
	0x01,
	0x62,
	0x02,
	0x01, /* output index (0x01-0x08) */
	0x42,
	0x01,
	0x43,
	0x01,
	0x00,
	0x00
पूर्ण;

अटल स्थिर अक्षर mix_init_msg1[] = अणु
	0x71, 0x01, 0x00, 0x00
पूर्ण;

अटल स्थिर अक्षर mix_init_msg2[] = अणु
	0x62, 0x02, 0x00, 0x61, 0x02, 0x04, 0xb1, 0x01, 0x00, 0x00
पूर्ण;

अटल स्थिर अक्षर mix_msg_in[] = अणु
	/* शेष message head, equal to all mixers */
	0x61, 0x02, 0x04, 0x62, 0x02, 0x01,
	0x81, /* 0x06: Controller ID */
	0x02, /* 0x07:  */
	0x00, /* 0x08: Value of common mixer */
	0x00,
	0x00
पूर्ण;

अटल स्थिर अक्षर mix_msg_out[] = अणु
	/* शेष message head, equal to all mixers */
	0x61, 0x02, 0x02, 0x62, 0x02, 0x01,
	0x81, /* 0x06: Controller ID */
	0x02, /*                    0x07:  */
	0x00, /*                    0x08: Value of common mixer */
	0x00,
	0x00
पूर्ण;

अटल स्थिर अक्षर bypass_msg_out[] = अणु
	0x45,
	0x02,
	0x01, /* on/off flag */
	0x00,
	0x00
पूर्ण;

अटल स्थिर अक्षर bus_msg_out[] = अणु
	0x44,
	0x02,
	0x01, /* on/off flag */
	0x00,
	0x00
पूर्ण;

अटल स्थिर अक्षर comp_msg[] = अणु
	/* शेष message head, equal to all mixers */
	0x61, 0x02, 0x04, 0x62, 0x02, 0x01,
	0x91,
	0x02,
	0xf0, /* 0x08: Threshold db (8) (e0 ... 00) (+-0dB -- -32dB) x-32 */
	0x92,
	0x02,
	0x0a, /* 0x0b: Ratio (0a,0b,0d,0f,11,14,19,1e,23,28,32,3c,50,a0,ff)  */
	0x93,
	0x02,
	0x02, /* 0x0e: Attack (0x02 ... 0xc0) (2ms ... 200ms) */
	0x94,
	0x02,
	0x01, /* 0x11: Release (0x01 ... 0x64) (10ms ... 1000ms) x*10  */
	0x95,
	0x02,
	0x03, /* 0x14: gain (0 ... 20) (0dB .. 20dB) */
	0x96,
	0x02,
	0x01,
	0x97,
	0x02,
	0x01, /* 0x1a: मुख्य Comp चयन (0 ... 1) (off ... on)) */
	0x00,
	0x00
पूर्ण;

अटल स्थिर अक्षर eqs_msq[] = अणु
	/* शेष message head, equal to all mixers */
	0x61, 0x02, 0x04, 0x62, 0x02, 0x01,
	0x51, /*                0x06: Controller ID  */
	0x02,
	0x04, /* 0x08: EQ set num (0x01..0x04) (LOW, LOWMID, HIGHMID, HIGH)) */
	0x52,
	0x02,
	0x0c, /* 0x0b: value dB (0 ... 12) (-12db .. +12db)  x-6 */
	0x53,
	0x02,
	0x0f, /* 0x0e: value freq (32-47) (1.7kHz..18kHz) */
	0x54,
	0x02,
	0x02, /* 0x11: band width (0-6) (Q16-Q0.25)  2^x/4 (EQ xxMID only) */
	0x55,
	0x02,
	0x01, /* 0x14: मुख्य EQ चयन (0 ... 1) (off ... on)) */
	0x00,
	0x00
पूर्ण;

/* compressor ratio map */
अटल स्थिर अक्षर ratio_map[] = अणु
	0x0a, 0x0b, 0x0d, 0x0f, 0x11, 0x14, 0x19, 0x1e,
	0x23, 0x28, 0x32, 0x3c, 0x50, 0xa0, 0xff
पूर्ण;

/* route क्रमागतeration names */
अटल स्थिर अक्षर *स्थिर route_names[] = अणु
	"Master Left", "Master Right", "Output 1", "Output 2", "Output 3",
	"Output 4", "Output 5", "Output 6", "Output 7", "Output 8",
पूर्ण;

अटल पूर्णांक snd_us16x08_recv_urb(काष्ठा snd_usb_audio *chip,
	अचिन्हित अक्षर *buf, पूर्णांक size)
अणु

	mutex_lock(&chip->mutex);
	snd_usb_ctl_msg(chip->dev,
		usb_rcvctrlpipe(chip->dev, 0),
		SND_US16X08_URB_METER_REQUEST,
		SND_US16X08_URB_METER_REQUESTTYPE, 0, 0, buf, size);
	mutex_unlock(&chip->mutex);
	वापस 0;
पूर्ण

/* wrapper function to send prepared URB buffer to usb device. Return an error
 * code अगर something went wrong
 */
अटल पूर्णांक snd_us16x08_send_urb(काष्ठा snd_usb_audio *chip, अक्षर *buf, पूर्णांक size)
अणु
	वापस snd_usb_ctl_msg(chip->dev, usb_sndctrlpipe(chip->dev, 0),
			SND_US16X08_URB_REQUEST, SND_US16X08_URB_REQUESTTYPE,
			0, 0, buf, size);
पूर्ण

अटल पूर्णांक snd_us16x08_route_info(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_info *uinfo)
अणु
	वापस snd_ctl_क्रमागत_info(uinfo, 1, 10, route_names);
पूर्ण

अटल पूर्णांक snd_us16x08_route_get(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा usb_mixer_elem_info *elem = kcontrol->निजी_data;
	पूर्णांक index = ucontrol->id.index;

	/* route has no bias */
	ucontrol->value.क्रमागतerated.item[0] = elem->cache_val[index];

	वापस 0;
पूर्ण

अटल पूर्णांक snd_us16x08_route_put(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा usb_mixer_elem_info *elem = kcontrol->निजी_data;
	काष्ठा snd_usb_audio *chip = elem->head.mixer->chip;
	पूर्णांक index = ucontrol->id.index;
	अक्षर buf[माप(route_msg)];
	पूर्णांक val, val_org, err;

	/*  get the new value (no bias क्रम routes) */
	val = ucontrol->value.क्रमागतerated.item[0];

	/* sanity check */
	अगर (val < 0 || val > 9)
		वापस -EINVAL;

	/* prepare the message buffer from ढाँचा */
	स_नकल(buf, route_msg, माप(route_msg));

	अगर (val < 2) अणु
		/* input comes from a master channel */
		val_org = val;
		buf[2] = 0x02;
	पूर्ण अन्यथा अणु
		/* input comes from a computer channel */
		buf[2] = 0x03;
		val_org = val - 2;
	पूर्ण

	/* place new route selection in URB message */
	buf[5] = (अचिन्हित अक्षर) (val_org & 0x0f) + 1;
	/* place route selector in URB message */
	buf[13] = index + 1;

	err = snd_us16x08_send_urb(chip, buf, माप(route_msg));

	अगर (err > 0) अणु
		elem->cached |= 1 << index;
		elem->cache_val[index] = val;
	पूर्ण अन्यथा अणु
		usb_audio_dbg(chip, "Failed to set routing, err:%d\n", err);
	पूर्ण

	वापस err > 0 ? 1 : 0;
पूर्ण

अटल पूर्णांक snd_us16x08_master_info(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->count = 1;
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->value.पूर्णांकeger.max = SND_US16X08_KCMAX(kcontrol);
	uinfo->value.पूर्णांकeger.min = SND_US16X08_KCMIN(kcontrol);
	uinfo->value.पूर्णांकeger.step = SND_US16X08_KCSTEP(kcontrol);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_us16x08_master_get(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा usb_mixer_elem_info *elem = kcontrol->निजी_data;
	पूर्णांक index = ucontrol->id.index;

	ucontrol->value.पूर्णांकeger.value[0] = elem->cache_val[index];

	वापस 0;
पूर्ण

अटल पूर्णांक snd_us16x08_master_put(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा usb_mixer_elem_info *elem = kcontrol->निजी_data;
	काष्ठा snd_usb_audio *chip = elem->head.mixer->chip;
	अक्षर buf[माप(mix_msg_out)];
	पूर्णांक val, err;
	पूर्णांक index = ucontrol->id.index;

	/* new control value incl. bias*/
	val = ucontrol->value.पूर्णांकeger.value[0];

	/* sanity check */
	अगर (val < SND_US16X08_KCMIN(kcontrol)
		|| val > SND_US16X08_KCMAX(kcontrol))
		वापस -EINVAL;

	/* prepare the message buffer from ढाँचा */
	स_नकल(buf, mix_msg_out, माप(mix_msg_out));

	buf[8] = val - SND_US16X08_KCBIAS(kcontrol);
	buf[6] = elem->head.id;

	/* place channel selector in URB message */
	buf[5] = index + 1;
	err = snd_us16x08_send_urb(chip, buf, माप(mix_msg_out));

	अगर (err > 0) अणु
		elem->cached |= 1 << index;
		elem->cache_val[index] = val;
	पूर्ण अन्यथा अणु
		usb_audio_dbg(chip, "Failed to set master, err:%d\n", err);
	पूर्ण

	वापस err > 0 ? 1 : 0;
पूर्ण

अटल पूर्णांक snd_us16x08_bus_put(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा usb_mixer_elem_info *elem = kcontrol->निजी_data;
	काष्ठा snd_usb_audio *chip = elem->head.mixer->chip;
	अक्षर buf[माप(mix_msg_out)];
	पूर्णांक val, err = 0;

	val = ucontrol->value.पूर्णांकeger.value[0];

	/* prepare the message buffer from ढाँचा */
	चयन (elem->head.id) अणु
	हाल SND_US16X08_ID_BYPASS:
		स_नकल(buf, bypass_msg_out, माप(bypass_msg_out));
		buf[2] = val;
		err = snd_us16x08_send_urb(chip, buf, माप(bypass_msg_out));
		अवरोध;
	हाल SND_US16X08_ID_BUSS_OUT:
		स_नकल(buf, bus_msg_out, माप(bus_msg_out));
		buf[2] = val;
		err = snd_us16x08_send_urb(chip, buf, माप(bus_msg_out));
		अवरोध;
	हाल SND_US16X08_ID_MUTE:
		स_नकल(buf, mix_msg_out, माप(mix_msg_out));
		buf[8] = val;
		buf[6] = elem->head.id;
		buf[5] = 1;
		err = snd_us16x08_send_urb(chip, buf, माप(mix_msg_out));
		अवरोध;
	पूर्ण

	अगर (err > 0) अणु
		elem->cached |= 1;
		elem->cache_val[0] = val;
	पूर्ण अन्यथा अणु
		usb_audio_dbg(chip, "Failed to set bus parameter, err:%d\n", err);
	पूर्ण

	वापस err > 0 ? 1 : 0;
पूर्ण

अटल पूर्णांक snd_us16x08_bus_get(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा usb_mixer_elem_info *elem = kcontrol->निजी_data;

	चयन (elem->head.id) अणु
	हाल SND_US16X08_ID_BUSS_OUT:
		ucontrol->value.पूर्णांकeger.value[0] = elem->cache_val[0];
		अवरोध;
	हाल SND_US16X08_ID_BYPASS:
		ucontrol->value.पूर्णांकeger.value[0] = elem->cache_val[0];
		अवरोध;
	हाल SND_US16X08_ID_MUTE:
		ucontrol->value.पूर्णांकeger.value[0] = elem->cache_val[0];
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/* माला_लो a current mixer value from common store */
अटल पूर्णांक snd_us16x08_channel_get(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा usb_mixer_elem_info *elem = kcontrol->निजी_data;
	पूर्णांक index = ucontrol->id.index;

	ucontrol->value.पूर्णांकeger.value[0] = elem->cache_val[index];

	वापस 0;
पूर्ण

अटल पूर्णांक snd_us16x08_channel_put(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा usb_mixer_elem_info *elem = kcontrol->निजी_data;
	काष्ठा snd_usb_audio *chip = elem->head.mixer->chip;
	अक्षर buf[माप(mix_msg_in)];
	पूर्णांक val, err;
	पूर्णांक index = ucontrol->id.index;

	val = ucontrol->value.पूर्णांकeger.value[0];

	/* sanity check */
	अगर (val < SND_US16X08_KCMIN(kcontrol)
		|| val > SND_US16X08_KCMAX(kcontrol))
		वापस -EINVAL;

	/* prepare URB message from ढाँचा */
	स_नकल(buf, mix_msg_in, माप(mix_msg_in));

	/* add the bias to the new value */
	buf[8] = val - SND_US16X08_KCBIAS(kcontrol);
	buf[6] = elem->head.id;
	buf[5] = index + 1;

	err = snd_us16x08_send_urb(chip, buf, माप(mix_msg_in));

	अगर (err > 0) अणु
		elem->cached |= 1 << index;
		elem->cache_val[index] = val;
	पूर्ण अन्यथा अणु
		usb_audio_dbg(chip, "Failed to set channel, err:%d\n", err);
	पूर्ण

	वापस err > 0 ? 1 : 0;
पूर्ण

अटल पूर्णांक snd_us16x08_mix_info(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->count = 1;
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->value.पूर्णांकeger.max = SND_US16X08_KCMAX(kcontrol);
	uinfo->value.पूर्णांकeger.min = SND_US16X08_KCMIN(kcontrol);
	uinfo->value.पूर्णांकeger.step = SND_US16X08_KCSTEP(kcontrol);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_us16x08_comp_get(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा usb_mixer_elem_info *elem = kcontrol->निजी_data;
	काष्ठा snd_us16x08_comp_store *store = elem->निजी_data;
	पूर्णांक index = ucontrol->id.index;
	पूर्णांक val_idx = COMP_STORE_IDX(elem->head.id);

	ucontrol->value.पूर्णांकeger.value[0] = store->val[val_idx][index];

	वापस 0;
पूर्ण

अटल पूर्णांक snd_us16x08_comp_put(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा usb_mixer_elem_info *elem = kcontrol->निजी_data;
	काष्ठा snd_usb_audio *chip = elem->head.mixer->chip;
	काष्ठा snd_us16x08_comp_store *store = elem->निजी_data;
	पूर्णांक index = ucontrol->id.index;
	अक्षर buf[माप(comp_msg)];
	पूर्णांक val_idx, val;
	पूर्णांक err;

	val = ucontrol->value.पूर्णांकeger.value[0];

	/* sanity check */
	अगर (val < SND_US16X08_KCMIN(kcontrol)
		|| val > SND_US16X08_KCMAX(kcontrol))
		वापस -EINVAL;

	/* new control value incl. bias*/
	val_idx = elem->head.id - SND_US16X08_ID_COMP_BASE;

	store->val[val_idx][index] = ucontrol->value.पूर्णांकeger.value[0];

	/* prepare compressor URB message from ढाँचा  */
	स_नकल(buf, comp_msg, माप(comp_msg));

	/* place comp values in message buffer watch bias! */
	buf[8] = store->val[
		COMP_STORE_IDX(SND_US16X08_ID_COMP_THRESHOLD)][index]
		- SND_US16X08_COMP_THRESHOLD_BIAS;
	buf[11] = ratio_map[store->val[
		COMP_STORE_IDX(SND_US16X08_ID_COMP_RATIO)][index]];
	buf[14] = store->val[COMP_STORE_IDX(SND_US16X08_ID_COMP_ATTACK)][index]
		+ SND_US16X08_COMP_ATTACK_BIAS;
	buf[17] = store->val[COMP_STORE_IDX(SND_US16X08_ID_COMP_RELEASE)][index]
		+ SND_US16X08_COMP_RELEASE_BIAS;
	buf[20] = store->val[COMP_STORE_IDX(SND_US16X08_ID_COMP_GAIN)][index];
	buf[26] = store->val[COMP_STORE_IDX(SND_US16X08_ID_COMP_SWITCH)][index];

	/* place channel selector in message buffer */
	buf[5] = index + 1;

	err = snd_us16x08_send_urb(chip, buf, माप(comp_msg));

	अगर (err > 0) अणु
		elem->cached |= 1 << index;
		elem->cache_val[index] = val;
	पूर्ण अन्यथा अणु
		usb_audio_dbg(chip, "Failed to set compressor, err:%d\n", err);
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक snd_us16x08_eqचयन_get(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	पूर्णांक val;
	काष्ठा usb_mixer_elem_info *elem = kcontrol->निजी_data;
	काष्ठा snd_us16x08_eq_store *store = elem->निजी_data;
	पूर्णांक index = ucontrol->id.index;

	/* get low चयन from cache is enough, cause all bands are together */
	val = store->val[EQ_STORE_BAND_IDX(elem->head.id)]
		[EQ_STORE_PARAM_IDX(elem->head.id)][index];
	ucontrol->value.पूर्णांकeger.value[0] = val;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_us16x08_eqचयन_put(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा usb_mixer_elem_info *elem = kcontrol->निजी_data;
	काष्ठा snd_usb_audio *chip = elem->head.mixer->chip;
	काष्ठा snd_us16x08_eq_store *store = elem->निजी_data;
	पूर्णांक index = ucontrol->id.index;
	अक्षर buf[माप(eqs_msq)];
	पूर्णांक val, err = 0;
	पूर्णांक b_idx;

	/* new control value incl. bias*/
	val = ucontrol->value.पूर्णांकeger.value[0] + SND_US16X08_KCBIAS(kcontrol);

	/* prepare URB message from EQ ढाँचा */
	स_नकल(buf, eqs_msq, माप(eqs_msq));

	/* place channel index in URB message */
	buf[5] = index + 1;
	क्रम (b_idx = 0; b_idx < SND_US16X08_ID_EQ_BAND_COUNT; b_idx++) अणु
		/* all four EQ bands have to be enabled/disabled in once */
		buf[20] = val;
		buf[17] = store->val[b_idx][2][index];
		buf[14] = store->val[b_idx][1][index];
		buf[11] = store->val[b_idx][0][index];
		buf[8] = b_idx + 1;
		err = snd_us16x08_send_urb(chip, buf, माप(eqs_msq));
		अगर (err < 0)
			अवरोध;
		store->val[b_idx][3][index] = val;
		msleep(15);
	पूर्ण

	अगर (err > 0) अणु
		elem->cached |= 1 << index;
		elem->cache_val[index] = val;
	पूर्ण अन्यथा अणु
		usb_audio_dbg(chip, "Failed to set eq switch, err:%d\n", err);
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक snd_us16x08_eq_get(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	पूर्णांक val;
	काष्ठा usb_mixer_elem_info *elem = kcontrol->निजी_data;
	काष्ठा snd_us16x08_eq_store *store = elem->निजी_data;
	पूर्णांक index = ucontrol->id.index;
	पूर्णांक b_idx = EQ_STORE_BAND_IDX(elem->head.id) - 1;
	पूर्णांक p_idx = EQ_STORE_PARAM_IDX(elem->head.id);

	val = store->val[b_idx][p_idx][index];

	ucontrol->value.पूर्णांकeger.value[0] = val;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_us16x08_eq_put(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा usb_mixer_elem_info *elem = kcontrol->निजी_data;
	काष्ठा snd_usb_audio *chip = elem->head.mixer->chip;
	काष्ठा snd_us16x08_eq_store *store = elem->निजी_data;
	पूर्णांक index = ucontrol->id.index;
	अक्षर buf[माप(eqs_msq)];
	पूर्णांक val, err;
	पूर्णांक b_idx = EQ_STORE_BAND_IDX(elem->head.id) - 1;
	पूर्णांक p_idx = EQ_STORE_PARAM_IDX(elem->head.id);

	val = ucontrol->value.पूर्णांकeger.value[0];

	/* sanity check */
	अगर (val < SND_US16X08_KCMIN(kcontrol)
		|| val > SND_US16X08_KCMAX(kcontrol))
		वापस -EINVAL;

	/* copy URB buffer from EQ ढाँचा */
	स_नकल(buf, eqs_msq, माप(eqs_msq));

	store->val[b_idx][p_idx][index] = val;
	buf[20] = store->val[b_idx][3][index];
	buf[17] = store->val[b_idx][2][index];
	buf[14] = store->val[b_idx][1][index];
	buf[11] = store->val[b_idx][0][index];

	/* place channel index in URB buffer */
	buf[5] = index + 1;

	/* place EQ band in URB buffer */
	buf[8] = b_idx + 1;

	err = snd_us16x08_send_urb(chip, buf, माप(eqs_msq));

	अगर (err > 0) अणु
		/* store new value in EQ band cache */
		elem->cached |= 1 << index;
		elem->cache_val[index] = val;
	पूर्ण अन्यथा अणु
		usb_audio_dbg(chip, "Failed to set eq param, err:%d\n", err);
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक snd_us16x08_meter_info(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->count = 34;
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->value.पूर्णांकeger.max = 0x7FFF;
	uinfo->value.पूर्णांकeger.min = 0;

	वापस 0;
पूर्ण

/* calculate compressor index क्रम reduction level request */
अटल पूर्णांक snd_get_meter_comp_index(काष्ठा snd_us16x08_meter_store *store)
अणु
	पूर्णांक ret;

	/* any channel active */
	अगर (store->comp_active_index) अणु
		/* check क्रम stereo link */
		अगर (store->comp_active_index & 0x20) अणु
			/* reset comp_index to left channel*/
			अगर (store->comp_index -
				store->comp_active_index > 1)
				store->comp_index =
				store->comp_active_index;

			ret = store->comp_index++ & 0x1F;
		पूर्ण अन्यथा अणु
			/* no stereo link */
			ret = store->comp_active_index;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* skip channels with no compressor active */
		जबतक (!store->comp_store->val[
			COMP_STORE_IDX(SND_US16X08_ID_COMP_SWITCH)]
			[store->comp_index - 1]
			&& store->comp_index <= SND_US16X08_MAX_CHANNELS) अणु
			store->comp_index++;
		पूर्ण
		ret = store->comp_index++;
		अगर (store->comp_index > SND_US16X08_MAX_CHANNELS)
			store->comp_index = 1;
	पूर्ण
	वापस ret;
पूर्ण

/* retrieve the meter level values from URB message */
अटल व्योम get_meter_levels_from_urb(पूर्णांक s,
	काष्ठा snd_us16x08_meter_store *store,
	u8 *meter_urb)
अणु
	पूर्णांक val = MUC2(meter_urb, s) + (MUC3(meter_urb, s) << 8);

	अगर (MUA0(meter_urb, s) == 0x61 && MUA1(meter_urb, s) == 0x02 &&
		MUA2(meter_urb, s) == 0x04 && MUB0(meter_urb, s) == 0x62) अणु
		अगर (MUC0(meter_urb, s) == 0x72)
			store->meter_level[MUB2(meter_urb, s) - 1] = val;
		अगर (MUC0(meter_urb, s) == 0xb2)
			store->comp_level[MUB2(meter_urb, s) - 1] = val;
	पूर्ण
	अगर (MUA0(meter_urb, s) == 0x61 && MUA1(meter_urb, s) == 0x02 &&
		MUA2(meter_urb, s) == 0x02 && MUB0(meter_urb, s) == 0x62)
		store->master_level[MUB2(meter_urb, s) - 1] = val;
पूर्ण

/* Function to retrieve current meter values from the device.
 *
 * The device needs to be polled क्रम meter values with an initial
 * requests. It will वापस with a sequence of dअगरferent meter value
 * packages. The first request (हाल 0:) initiate this meter response sequence.
 * After the third response, an additional request can be placed,
 * to retrieve compressor reduction level value क्रम given channel. This round
 * trip channel selector will skip all inactive compressors.
 * A mixer can पूर्णांकerrupt this round-trip by selecting one ore two (stereo-link)
 * specअगरic channels.
 */
अटल पूर्णांक snd_us16x08_meter_get(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	पूर्णांक i, set;
	काष्ठा usb_mixer_elem_info *elem = kcontrol->निजी_data;
	काष्ठा snd_usb_audio *chip = elem->head.mixer->chip;
	काष्ठा snd_us16x08_meter_store *store = elem->निजी_data;
	u8 meter_urb[64];

	चयन (kcontrol->निजी_value) अणु
	हाल 0: अणु
		अक्षर पंचांगp[माप(mix_init_msg1)];

		स_नकल(पंचांगp, mix_init_msg1, माप(mix_init_msg1));
		snd_us16x08_send_urb(chip, पंचांगp, 4);
		snd_us16x08_recv_urb(chip, meter_urb,
			माप(meter_urb));
		kcontrol->निजी_value++;
		अवरोध;
	पूर्ण
	हाल 1:
		snd_us16x08_recv_urb(chip, meter_urb,
			माप(meter_urb));
		kcontrol->निजी_value++;
		अवरोध;
	हाल 2:
		snd_us16x08_recv_urb(chip, meter_urb,
			माप(meter_urb));
		kcontrol->निजी_value++;
		अवरोध;
	हाल 3: अणु
		अक्षर पंचांगp[माप(mix_init_msg2)];

		स_नकल(पंचांगp, mix_init_msg2, माप(mix_init_msg2));
		पंचांगp[2] = snd_get_meter_comp_index(store);
		snd_us16x08_send_urb(chip, पंचांगp, 10);
		snd_us16x08_recv_urb(chip, meter_urb,
			माप(meter_urb));
		kcontrol->निजी_value = 0;
		अवरोध;
	पूर्ण
	पूर्ण

	क्रम (set = 0; set < 6; set++)
		get_meter_levels_from_urb(set, store, meter_urb);

	क्रम (i = 0; i < SND_US16X08_MAX_CHANNELS; i++) अणु
		ucontrol->value.पूर्णांकeger.value[i] =
			store ? store->meter_level[i] : 0;
	पूर्ण

	ucontrol->value.पूर्णांकeger.value[i++] = store ? store->master_level[0] : 0;
	ucontrol->value.पूर्णांकeger.value[i++] = store ? store->master_level[1] : 0;

	क्रम (i = 2; i < SND_US16X08_MAX_CHANNELS + 2; i++)
		ucontrol->value.पूर्णांकeger.value[i + SND_US16X08_MAX_CHANNELS] =
		store ? store->comp_level[i - 2] : 0;

	वापस 1;
पूर्ण

अटल पूर्णांक snd_us16x08_meter_put(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा usb_mixer_elem_info *elem = kcontrol->निजी_data;
	काष्ठा snd_us16x08_meter_store *store = elem->निजी_data;
	पूर्णांक val;

	val = ucontrol->value.पूर्णांकeger.value[0];

	/* sanity check */
	अगर (val < 0 || val >= SND_US16X08_MAX_CHANNELS)
		वापस -EINVAL;

	store->comp_active_index = val;
	store->comp_index = val;

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_us16x08_ch_boolean_ctl = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.count = 16,
	.info = snd_us16x08_चयन_info,
	.get = snd_us16x08_channel_get,
	.put = snd_us16x08_channel_put,
	.निजी_value = SND_US16X08_KCSET(SND_US16X08_NO_BIAS, 1, 0, 1)
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_us16x08_ch_पूर्णांक_ctl = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.count = 16,
	.info = snd_us16x08_mix_info,
	.get = snd_us16x08_channel_get,
	.put = snd_us16x08_channel_put,
	.निजी_value = SND_US16X08_KCSET(SND_US16X08_FADER_BIAS, 1, 0, 133)
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_us16x08_pan_पूर्णांक_ctl = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.count = 16,
	.info = snd_us16x08_mix_info,
	.get = snd_us16x08_channel_get,
	.put = snd_us16x08_channel_put,
	.निजी_value = SND_US16X08_KCSET(SND_US16X08_FADER_BIAS, 1, 0, 255)
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_us16x08_master_ctl = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.count = 1,
	.info = snd_us16x08_master_info,
	.get = snd_us16x08_master_get,
	.put = snd_us16x08_master_put,
	.निजी_value = SND_US16X08_KCSET(SND_US16X08_FADER_BIAS, 1, 0, 133)
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_us16x08_route_ctl = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.count = 8,
	.info = snd_us16x08_route_info,
	.get = snd_us16x08_route_get,
	.put = snd_us16x08_route_put,
	.निजी_value = SND_US16X08_KCSET(SND_US16X08_NO_BIAS, 1, 0, 9)
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_us16x08_bus_ctl = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.count = 1,
	.info = snd_us16x08_चयन_info,
	.get = snd_us16x08_bus_get,
	.put = snd_us16x08_bus_put,
	.निजी_value = SND_US16X08_KCSET(SND_US16X08_NO_BIAS, 1, 0, 1)
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_us16x08_compचयन_ctl = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.count = 16,
	.info = snd_us16x08_चयन_info,
	.get = snd_us16x08_comp_get,
	.put = snd_us16x08_comp_put,
	.निजी_value = SND_US16X08_KCSET(SND_US16X08_NO_BIAS, 1, 0, 1)
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_us16x08_comp_threshold_ctl = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.count = 16,
	.info = snd_us16x08_mix_info,
	.get = snd_us16x08_comp_get,
	.put = snd_us16x08_comp_put,
	.निजी_value = SND_US16X08_KCSET(SND_US16X08_COMP_THRESHOLD_BIAS, 1,
	0, 0x20)
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_us16x08_comp_ratio_ctl = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.count = 16,
	.info = snd_us16x08_mix_info,
	.get = snd_us16x08_comp_get,
	.put = snd_us16x08_comp_put,
	.निजी_value = SND_US16X08_KCSET(SND_US16X08_NO_BIAS, 1, 0,
	माप(ratio_map) - 1), /*max*/
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_us16x08_comp_gain_ctl = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.count = 16,
	.info = snd_us16x08_mix_info,
	.get = snd_us16x08_comp_get,
	.put = snd_us16x08_comp_put,
	.निजी_value = SND_US16X08_KCSET(SND_US16X08_NO_BIAS, 1, 0, 0x14)
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_us16x08_comp_attack_ctl = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.count = 16,
	.info = snd_us16x08_mix_info,
	.get = snd_us16x08_comp_get,
	.put = snd_us16x08_comp_put,
	.निजी_value =
	SND_US16X08_KCSET(SND_US16X08_COMP_ATTACK_BIAS, 1, 0, 0xc6),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_us16x08_comp_release_ctl = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.count = 16,
	.info = snd_us16x08_mix_info,
	.get = snd_us16x08_comp_get,
	.put = snd_us16x08_comp_put,
	.निजी_value =
	SND_US16X08_KCSET(SND_US16X08_COMP_RELEASE_BIAS, 1, 0, 0x63),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_us16x08_eq_gain_ctl = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.count = 16,
	.info = snd_us16x08_mix_info,
	.get = snd_us16x08_eq_get,
	.put = snd_us16x08_eq_put,
	.निजी_value = SND_US16X08_KCSET(SND_US16X08_NO_BIAS, 1, 0, 24),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_us16x08_eq_low_freq_ctl = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.count = 16,
	.info = snd_us16x08_mix_info,
	.get = snd_us16x08_eq_get,
	.put = snd_us16x08_eq_put,
	.निजी_value = SND_US16X08_KCSET(SND_US16X08_NO_BIAS, 1, 0, 0x1F),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_us16x08_eq_mid_freq_ctl = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.count = 16,
	.info = snd_us16x08_mix_info,
	.get = snd_us16x08_eq_get,
	.put = snd_us16x08_eq_put,
	.निजी_value = SND_US16X08_KCSET(SND_US16X08_NO_BIAS, 1, 0, 0x3F)
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_us16x08_eq_mid_width_ctl = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.count = 16,
	.info = snd_us16x08_mix_info,
	.get = snd_us16x08_eq_get,
	.put = snd_us16x08_eq_put,
	.निजी_value = SND_US16X08_KCSET(SND_US16X08_NO_BIAS, 1, 0, 0x06)
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_us16x08_eq_high_freq_ctl = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.count = 16,
	.info = snd_us16x08_mix_info,
	.get = snd_us16x08_eq_get,
	.put = snd_us16x08_eq_put,
	.निजी_value =
	SND_US16X08_KCSET(SND_US16X08_EQ_HIGHFREQ_BIAS, 1, 0, 0x1F)
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_us16x08_eq_चयन_ctl = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.count = 16,
	.info = snd_us16x08_चयन_info,
	.get = snd_us16x08_eqचयन_get,
	.put = snd_us16x08_eqचयन_put,
	.निजी_value = SND_US16X08_KCSET(SND_US16X08_NO_BIAS, 1, 0, 1)
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_us16x08_meter_ctl = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
	.count = 1,
	.info = snd_us16x08_meter_info,
	.get = snd_us16x08_meter_get,
	.put = snd_us16x08_meter_put
पूर्ण;

/* control store preparation */

/* setup compressor store and assign शेष value */
अटल काष्ठा snd_us16x08_comp_store *snd_us16x08_create_comp_store(व्योम)
अणु
	पूर्णांक i;
	काष्ठा snd_us16x08_comp_store *पंचांगp;

	पंचांगp = kदो_स्मृति(माप(*पंचांगp), GFP_KERNEL);
	अगर (!पंचांगp)
		वापस शून्य;

	क्रम (i = 0; i < SND_US16X08_MAX_CHANNELS; i++) अणु
		पंचांगp->val[COMP_STORE_IDX(SND_US16X08_ID_COMP_THRESHOLD)][i]
			= 0x20;
		पंचांगp->val[COMP_STORE_IDX(SND_US16X08_ID_COMP_RATIO)][i] = 0x00;
		पंचांगp->val[COMP_STORE_IDX(SND_US16X08_ID_COMP_GAIN)][i] = 0x00;
		पंचांगp->val[COMP_STORE_IDX(SND_US16X08_ID_COMP_SWITCH)][i] = 0x00;
		पंचांगp->val[COMP_STORE_IDX(SND_US16X08_ID_COMP_ATTACK)][i] = 0x00;
		पंचांगp->val[COMP_STORE_IDX(SND_US16X08_ID_COMP_RELEASE)][i] = 0x00;
	पूर्ण
	वापस पंचांगp;
पूर्ण

/* setup EQ store and assign शेष values */
अटल काष्ठा snd_us16x08_eq_store *snd_us16x08_create_eq_store(व्योम)
अणु
	पूर्णांक i, b_idx;
	काष्ठा snd_us16x08_eq_store *पंचांगp;

	पंचांगp = kदो_स्मृति(माप(*पंचांगp), GFP_KERNEL);
	अगर (!पंचांगp)
		वापस शून्य;

	क्रम (i = 0; i < SND_US16X08_MAX_CHANNELS; i++) अणु
		क्रम (b_idx = 0; b_idx < SND_US16X08_ID_EQ_BAND_COUNT; b_idx++) अणु
			पंचांगp->val[b_idx][0][i] = 0x0c;
			पंचांगp->val[b_idx][3][i] = 0x00;
			चयन (b_idx) अणु
			हाल 0: /* EQ Low */
				पंचांगp->val[b_idx][1][i] = 0x05;
				पंचांगp->val[b_idx][2][i] = 0xff;
				अवरोध;
			हाल 1: /* EQ Mid low */
				पंचांगp->val[b_idx][1][i] = 0x0e;
				पंचांगp->val[b_idx][2][i] = 0x02;
				अवरोध;
			हाल 2: /* EQ Mid High */
				पंचांगp->val[b_idx][1][i] = 0x1b;
				पंचांगp->val[b_idx][2][i] = 0x02;
				अवरोध;
			हाल 3: /* EQ High */
				पंचांगp->val[b_idx][1][i] = 0x2f
					- SND_US16X08_EQ_HIGHFREQ_BIAS;
				पंचांगp->val[b_idx][2][i] = 0xff;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस पंचांगp;
पूर्ण

अटल काष्ठा snd_us16x08_meter_store *snd_us16x08_create_meter_store(व्योम)
अणु
	काष्ठा snd_us16x08_meter_store *पंचांगp;

	पंचांगp = kzalloc(माप(*पंचांगp), GFP_KERNEL);
	अगर (!पंचांगp)
		वापस शून्य;
	पंचांगp->comp_index = 1;
	पंचांगp->comp_active_index = 0;
	वापस पंचांगp;
पूर्ण

/* release elem->निजी_मुक्त as well; called only once क्रम each *_store */
अटल व्योम elem_निजी_मुक्त(काष्ठा snd_kcontrol *kctl)
अणु
	काष्ठा usb_mixer_elem_info *elem = kctl->निजी_data;

	अगर (elem)
		kमुक्त(elem->निजी_data);
	kमुक्त(elem);
	kctl->निजी_data = शून्य;
पूर्ण

अटल पूर्णांक add_new_ctl(काष्ठा usb_mixer_पूर्णांकerface *mixer,
	स्थिर काष्ठा snd_kcontrol_new *ncontrol,
	पूर्णांक index, पूर्णांक val_type, पूर्णांक channels,
	स्थिर अक्षर *name, व्योम *opt,
	bool करो_निजी_मुक्त,
	काष्ठा usb_mixer_elem_info **elem_ret)
अणु
	काष्ठा snd_kcontrol *kctl;
	काष्ठा usb_mixer_elem_info *elem;
	पूर्णांक err;

	usb_audio_dbg(mixer->chip, "us16x08 add mixer %s\n", name);

	elem = kzalloc(माप(*elem), GFP_KERNEL);
	अगर (!elem)
		वापस -ENOMEM;

	elem->head.mixer = mixer;
	elem->head.resume = शून्य;
	elem->control = 0;
	elem->idx_off = 0;
	elem->head.id = index;
	elem->val_type = val_type;
	elem->channels = channels;
	elem->निजी_data = opt;

	kctl = snd_ctl_new1(ncontrol, elem);
	अगर (!kctl) अणु
		kमुक्त(elem);
		वापस -ENOMEM;
	पूर्ण

	अगर (करो_निजी_मुक्त)
		kctl->निजी_मुक्त = elem_निजी_मुक्त;
	अन्यथा
		kctl->निजी_मुक्त = snd_usb_mixer_elem_मुक्त;

	strscpy(kctl->id.name, name, माप(kctl->id.name));

	err = snd_usb_mixer_add_control(&elem->head, kctl);
	अगर (err < 0)
		वापस err;

	अगर (elem_ret)
		*elem_ret = elem;

	वापस 0;
पूर्ण

/* table of EQ controls */
अटल स्थिर काष्ठा snd_us16x08_control_params eq_controls[] = अणु
	अणु /* EQ चयन */
		.kcontrol_new = &snd_us16x08_eq_चयन_ctl,
		.control_id = SND_US16X08_ID_EQENABLE,
		.type = USB_MIXER_BOOLEAN,
		.num_channels = 16,
		.name = "EQ Switch",
	पूर्ण,
	अणु /* EQ low gain */
		.kcontrol_new = &snd_us16x08_eq_gain_ctl,
		.control_id = SND_US16X08_ID_EQLOWLEVEL,
		.type = USB_MIXER_U8,
		.num_channels = 16,
		.name = "EQ Low Volume",
	पूर्ण,
	अणु /* EQ low freq */
		.kcontrol_new = &snd_us16x08_eq_low_freq_ctl,
		.control_id = SND_US16X08_ID_EQLOWFREQ,
		.type = USB_MIXER_U8,
		.num_channels = 16,
		.name = "EQ Low Frequency",
	पूर्ण,
	अणु /* EQ mid low gain */
		.kcontrol_new = &snd_us16x08_eq_gain_ctl,
		.control_id = SND_US16X08_ID_EQLOWMIDLEVEL,
		.type = USB_MIXER_U8,
		.num_channels = 16,
		.name = "EQ MidLow Volume",
	पूर्ण,
	अणु /* EQ mid low freq */
		.kcontrol_new = &snd_us16x08_eq_mid_freq_ctl,
		.control_id = SND_US16X08_ID_EQLOWMIDFREQ,
		.type = USB_MIXER_U8,
		.num_channels = 16,
		.name = "EQ MidLow Frequency",
	पूर्ण,
	अणु /* EQ mid low Q */
		.kcontrol_new = &snd_us16x08_eq_mid_width_ctl,
		.control_id = SND_US16X08_ID_EQLOWMIDWIDTH,
		.type = USB_MIXER_U8,
		.num_channels = 16,
		.name = "EQ MidLow Q",
	पूर्ण,
	अणु /* EQ mid high gain */
		.kcontrol_new = &snd_us16x08_eq_gain_ctl,
		.control_id = SND_US16X08_ID_EQHIGHMIDLEVEL,
		.type = USB_MIXER_U8,
		.num_channels = 16,
		.name = "EQ MidHigh Volume",
	पूर्ण,
	अणु /* EQ mid high freq */
		.kcontrol_new = &snd_us16x08_eq_mid_freq_ctl,
		.control_id = SND_US16X08_ID_EQHIGHMIDFREQ,
		.type = USB_MIXER_U8,
		.num_channels = 16,
		.name = "EQ MidHigh Frequency",
	पूर्ण,
	अणु /* EQ mid high Q */
		.kcontrol_new = &snd_us16x08_eq_mid_width_ctl,
		.control_id = SND_US16X08_ID_EQHIGHMIDWIDTH,
		.type = USB_MIXER_U8,
		.num_channels = 16,
		.name = "EQ MidHigh Q",
	पूर्ण,
	अणु /* EQ high gain */
		.kcontrol_new = &snd_us16x08_eq_gain_ctl,
		.control_id = SND_US16X08_ID_EQHIGHLEVEL,
		.type = USB_MIXER_U8,
		.num_channels = 16,
		.name = "EQ High Volume",
	पूर्ण,
	अणु /* EQ low freq */
		.kcontrol_new = &snd_us16x08_eq_high_freq_ctl,
		.control_id = SND_US16X08_ID_EQHIGHFREQ,
		.type = USB_MIXER_U8,
		.num_channels = 16,
		.name = "EQ High Frequency",
	पूर्ण,
पूर्ण;

/* table of compressor controls */
अटल स्थिर काष्ठा snd_us16x08_control_params comp_controls[] = अणु
	अणु /* Comp enable */
		.kcontrol_new = &snd_us16x08_compचयन_ctl,
		.control_id = SND_US16X08_ID_COMP_SWITCH,
		.type = USB_MIXER_BOOLEAN,
		.num_channels = 16,
		.name = "Compressor Switch",
	पूर्ण,
	अणु /* Comp threshold */
		.kcontrol_new = &snd_us16x08_comp_threshold_ctl,
		.control_id = SND_US16X08_ID_COMP_THRESHOLD,
		.type = USB_MIXER_U8,
		.num_channels = 16,
		.name = "Compressor Threshold Volume",
	पूर्ण,
	अणु /* Comp ratio */
		.kcontrol_new = &snd_us16x08_comp_ratio_ctl,
		.control_id = SND_US16X08_ID_COMP_RATIO,
		.type = USB_MIXER_U8,
		.num_channels = 16,
		.name = "Compressor Ratio",
	पूर्ण,
	अणु /* Comp attack */
		.kcontrol_new = &snd_us16x08_comp_attack_ctl,
		.control_id = SND_US16X08_ID_COMP_ATTACK,
		.type = USB_MIXER_U8,
		.num_channels = 16,
		.name = "Compressor Attack",
	पूर्ण,
	अणु /* Comp release */
		.kcontrol_new = &snd_us16x08_comp_release_ctl,
		.control_id = SND_US16X08_ID_COMP_RELEASE,
		.type = USB_MIXER_U8,
		.num_channels = 16,
		.name = "Compressor Release",
	पूर्ण,
	अणु /* Comp gain */
		.kcontrol_new = &snd_us16x08_comp_gain_ctl,
		.control_id = SND_US16X08_ID_COMP_GAIN,
		.type = USB_MIXER_U8,
		.num_channels = 16,
		.name = "Compressor Volume",
	पूर्ण,
पूर्ण;

/* table of channel controls */
अटल स्थिर काष्ठा snd_us16x08_control_params channel_controls[] = अणु
	अणु /* Phase */
		.kcontrol_new = &snd_us16x08_ch_boolean_ctl,
		.control_id = SND_US16X08_ID_PHASE,
		.type = USB_MIXER_BOOLEAN,
		.num_channels = 16,
		.name = "Phase Switch",
		.शेष_val = 0
	पूर्ण,
	अणु /* Fader */
		.kcontrol_new = &snd_us16x08_ch_पूर्णांक_ctl,
		.control_id = SND_US16X08_ID_FADER,
		.type = USB_MIXER_U8,
		.num_channels = 16,
		.name = "Line Volume",
		.शेष_val = 127
	पूर्ण,
	अणु /* Mute */
		.kcontrol_new = &snd_us16x08_ch_boolean_ctl,
		.control_id = SND_US16X08_ID_MUTE,
		.type = USB_MIXER_BOOLEAN,
		.num_channels = 16,
		.name = "Mute Switch",
		.शेष_val = 0
	पूर्ण,
	अणु /* Pan */
		.kcontrol_new = &snd_us16x08_pan_पूर्णांक_ctl,
		.control_id = SND_US16X08_ID_PAN,
		.type = USB_MIXER_U16,
		.num_channels = 16,
		.name = "Pan Left-Right Volume",
		.शेष_val = 127
	पूर्ण,
पूर्ण;

/* table of master controls */
अटल स्थिर काष्ठा snd_us16x08_control_params master_controls[] = अणु
	अणु /* Master */
		.kcontrol_new = &snd_us16x08_master_ctl,
		.control_id = SND_US16X08_ID_FADER,
		.type = USB_MIXER_U8,
		.num_channels = 16,
		.name = "Master Volume",
		.शेष_val = 127
	पूर्ण,
	अणु /* Bypass */
		.kcontrol_new = &snd_us16x08_bus_ctl,
		.control_id = SND_US16X08_ID_BYPASS,
		.type = USB_MIXER_BOOLEAN,
		.num_channels = 16,
		.name = "DSP Bypass Switch",
		.शेष_val = 0
	पूर्ण,
	अणु /* Buss out */
		.kcontrol_new = &snd_us16x08_bus_ctl,
		.control_id = SND_US16X08_ID_BUSS_OUT,
		.type = USB_MIXER_BOOLEAN,
		.num_channels = 16,
		.name = "Buss Out Switch",
		.शेष_val = 0
	पूर्ण,
	अणु /* Master mute */
		.kcontrol_new = &snd_us16x08_bus_ctl,
		.control_id = SND_US16X08_ID_MUTE,
		.type = USB_MIXER_BOOLEAN,
		.num_channels = 16,
		.name = "Master Mute Switch",
		.शेष_val = 0
	पूर्ण,

पूर्ण;

पूर्णांक snd_us16x08_controls_create(काष्ठा usb_mixer_पूर्णांकerface *mixer)
अणु
	पूर्णांक i, j;
	पूर्णांक err;
	काष्ठा usb_mixer_elem_info *elem;
	काष्ठा snd_us16x08_comp_store *comp_store;
	काष्ठा snd_us16x08_meter_store *meter_store;
	काष्ठा snd_us16x08_eq_store *eq_store;

	/* just check क्रम non-MIDI पूर्णांकerface */
	अगर (mixer->hostअगर->desc.bInterfaceNumber == 3) अणु

		/* add routing control */
		err = add_new_ctl(mixer, &snd_us16x08_route_ctl,
			SND_US16X08_ID_ROUTE, USB_MIXER_U8, 8, "Line Out Route",
			शून्य, false, &elem);
		अगर (err < 0) अणु
			usb_audio_dbg(mixer->chip,
				"Failed to create route control, err:%d\n",
				err);
			वापस err;
		पूर्ण
		क्रम (i = 0; i < 8; i++)
			elem->cache_val[i] = i < 2 ? i : i + 2;
		elem->cached = 0xff;

		/* create compressor mixer elements */
		comp_store = snd_us16x08_create_comp_store();
		अगर (!comp_store)
			वापस -ENOMEM;

		/* add master controls */
		क्रम (i = 0; i < ARRAY_SIZE(master_controls); i++) अणु

			err = add_new_ctl(mixer,
				master_controls[i].kcontrol_new,
				master_controls[i].control_id,
				master_controls[i].type,
				master_controls[i].num_channels,
				master_controls[i].name,
				comp_store,
				i == 0, /* release comp_store only once */
				&elem);
			अगर (err < 0)
				वापस err;
			elem->cache_val[0] = master_controls[i].शेष_val;
			elem->cached = 1;
		पूर्ण

		/* add channel controls */
		क्रम (i = 0; i < ARRAY_SIZE(channel_controls); i++) अणु

			err = add_new_ctl(mixer,
				channel_controls[i].kcontrol_new,
				channel_controls[i].control_id,
				channel_controls[i].type,
				channel_controls[i].num_channels,
				channel_controls[i].name,
				comp_store,
				false, &elem);
			अगर (err < 0)
				वापस err;
			क्रम (j = 0; j < SND_US16X08_MAX_CHANNELS; j++) अणु
				elem->cache_val[j] =
					channel_controls[i].शेष_val;
			पूर्ण
			elem->cached = 0xffff;
		पूर्ण

		/* create eq store */
		eq_store = snd_us16x08_create_eq_store();
		अगर (!eq_store)
			वापस -ENOMEM;

		/* add EQ controls */
		क्रम (i = 0; i < ARRAY_SIZE(eq_controls); i++) अणु

			err = add_new_ctl(mixer,
				eq_controls[i].kcontrol_new,
				eq_controls[i].control_id,
				eq_controls[i].type,
				eq_controls[i].num_channels,
				eq_controls[i].name,
				eq_store,
				i == 0, /* release eq_store only once */
				शून्य);
			अगर (err < 0)
				वापस err;
		पूर्ण

		/* add compressor controls */
		क्रम (i = 0; i < ARRAY_SIZE(comp_controls); i++) अणु

			err = add_new_ctl(mixer,
				comp_controls[i].kcontrol_new,
				comp_controls[i].control_id,
				comp_controls[i].type,
				comp_controls[i].num_channels,
				comp_controls[i].name,
				comp_store,
				false, शून्य);
			अगर (err < 0)
				वापस err;
		पूर्ण

		/* create meters store */
		meter_store = snd_us16x08_create_meter_store();
		अगर (!meter_store)
			वापस -ENOMEM;

		/* meter function 'get' must access to compressor store
		 * so place a reference here
		 */
		meter_store->comp_store = comp_store;
		err = add_new_ctl(mixer, &snd_us16x08_meter_ctl,
			SND_US16X08_ID_METER, USB_MIXER_U16, 0, "Level Meter",
			meter_store, true, शून्य);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

