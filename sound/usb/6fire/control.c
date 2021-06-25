<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Linux driver क्रम TerraTec DMX 6Fire USB
 *
 * Mixer control
 *
 * Author:	Torsten Schenk <torsten.schenk@zoho.com>
 * Created:	Jan 01, 2011
 * Copyright:	(C) Torsten Schenk
 *
 * Thanks to:
 * - Holger Ruckdeschel: he found out how to control inभागidual channel
 *   volumes and पूर्णांकroduced mute चयन
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <sound/control.h>
#समावेश <sound/tlv.h>

#समावेश "control.h"
#समावेश "comm.h"
#समावेश "chip.h"

अटल स्थिर अक्षर * स्थिर opt_coax_texts[2] = अणु "Optical", "Coax" पूर्ण;
अटल स्थिर अक्षर * स्थिर line_phono_texts[2] = अणु "Line", "Phono" पूर्ण;

/*
 * data that needs to be sent to device. sets up card पूर्णांकernal stuff.
 * values dumped from winकरोws driver and filtered by trial'n'error.
 */
अटल स्थिर काष्ठा अणु
	u8 type;
	u8 reg;
	u8 value;
पूर्ण
init_data[] = अणु
	अणु 0x22, 0x00, 0x00 पूर्ण, अणु 0x20, 0x00, 0x08 पूर्ण, अणु 0x22, 0x01, 0x01 पूर्ण,
	अणु 0x20, 0x01, 0x08 पूर्ण, अणु 0x22, 0x02, 0x00 पूर्ण, अणु 0x20, 0x02, 0x08 पूर्ण,
	अणु 0x22, 0x03, 0x00 पूर्ण, अणु 0x20, 0x03, 0x08 पूर्ण, अणु 0x22, 0x04, 0x00 पूर्ण,
	अणु 0x20, 0x04, 0x08 पूर्ण, अणु 0x22, 0x05, 0x01 पूर्ण, अणु 0x20, 0x05, 0x08 पूर्ण,
	अणु 0x22, 0x04, 0x01 पूर्ण, अणु 0x12, 0x04, 0x00 पूर्ण, अणु 0x12, 0x05, 0x00 पूर्ण,
	अणु 0x12, 0x0d, 0x38 पूर्ण, अणु 0x12, 0x21, 0x82 पूर्ण, अणु 0x12, 0x22, 0x80 पूर्ण,
	अणु 0x12, 0x23, 0x00 पूर्ण, अणु 0x12, 0x06, 0x02 पूर्ण, अणु 0x12, 0x03, 0x00 पूर्ण,
	अणु 0x12, 0x02, 0x00 पूर्ण, अणु 0x22, 0x03, 0x01 पूर्ण,
	अणु 0 पूर्ण /* TERMINATING ENTRY */
पूर्ण;

अटल स्थिर पूर्णांक rates_altsetting[] = अणु 1, 1, 2, 2, 3, 3 पूर्ण;
/* values to ग_लिखो to soundcard रेजिस्टर क्रम all samplerates */
अटल स्थिर u16 rates_6fire_vl[] = अणु0x00, 0x01, 0x00, 0x01, 0x00, 0x01पूर्ण;
अटल स्थिर u16 rates_6fire_vh[] = अणु0x11, 0x11, 0x10, 0x10, 0x00, 0x00पूर्ण;

अटल DECLARE_TLV_DB_MINMAX(tlv_output, -9000, 0);
अटल DECLARE_TLV_DB_MINMAX(tlv_input, -1500, 1500);

क्रमागत अणु
	DIGITAL_THRU_ONLY_SAMPLERATE = 3
पूर्ण;

अटल व्योम usb6fire_control_output_vol_update(काष्ठा control_runसमय *rt)
अणु
	काष्ठा comm_runसमय *comm_rt = rt->chip->comm;
	पूर्णांक i;

	अगर (comm_rt)
		क्रम (i = 0; i < 6; i++)
			अगर (!(rt->ovol_updated & (1 << i))) अणु
				comm_rt->ग_लिखो8(comm_rt, 0x12, 0x0f + i,
					180 - rt->output_vol[i]);
				rt->ovol_updated |= 1 << i;
			पूर्ण
पूर्ण

अटल व्योम usb6fire_control_output_mute_update(काष्ठा control_runसमय *rt)
अणु
	काष्ठा comm_runसमय *comm_rt = rt->chip->comm;

	अगर (comm_rt)
		comm_rt->ग_लिखो8(comm_rt, 0x12, 0x0e, ~rt->output_mute);
पूर्ण

अटल व्योम usb6fire_control_input_vol_update(काष्ठा control_runसमय *rt)
अणु
	काष्ठा comm_runसमय *comm_rt = rt->chip->comm;
	पूर्णांक i;

	अगर (comm_rt)
		क्रम (i = 0; i < 2; i++)
			अगर (!(rt->ivol_updated & (1 << i))) अणु
				comm_rt->ग_लिखो8(comm_rt, 0x12, 0x1c + i,
					rt->input_vol[i] & 0x3f);
				rt->ivol_updated |= 1 << i;
			पूर्ण
पूर्ण

अटल व्योम usb6fire_control_line_phono_update(काष्ठा control_runसमय *rt)
अणु
	काष्ठा comm_runसमय *comm_rt = rt->chip->comm;
	अगर (comm_rt) अणु
		comm_rt->ग_लिखो8(comm_rt, 0x22, 0x02, rt->line_phono_चयन);
		comm_rt->ग_लिखो8(comm_rt, 0x21, 0x02, rt->line_phono_चयन);
	पूर्ण
पूर्ण

अटल व्योम usb6fire_control_opt_coax_update(काष्ठा control_runसमय *rt)
अणु
	काष्ठा comm_runसमय *comm_rt = rt->chip->comm;
	अगर (comm_rt) अणु
		comm_rt->ग_लिखो8(comm_rt, 0x22, 0x00, rt->opt_coax_चयन);
		comm_rt->ग_लिखो8(comm_rt, 0x21, 0x00, rt->opt_coax_चयन);
	पूर्ण
पूर्ण

अटल पूर्णांक usb6fire_control_set_rate(काष्ठा control_runसमय *rt, पूर्णांक rate)
अणु
	पूर्णांक ret;
	काष्ठा usb_device *device = rt->chip->dev;
	काष्ठा comm_runसमय *comm_rt = rt->chip->comm;

	अगर (rate < 0 || rate >= CONTROL_N_RATES)
		वापस -EINVAL;

	ret = usb_set_पूर्णांकerface(device, 1, rates_altsetting[rate]);
	अगर (ret < 0)
		वापस ret;

	/* set soundcard घड़ी */
	ret = comm_rt->ग_लिखो16(comm_rt, 0x02, 0x01, rates_6fire_vl[rate],
			rates_6fire_vh[rate]);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक usb6fire_control_set_channels(
	काष्ठा control_runसमय *rt, पूर्णांक n_analog_out,
	पूर्णांक n_analog_in, bool spdअगर_out, bool spdअगर_in)
अणु
	पूर्णांक ret;
	काष्ठा comm_runसमय *comm_rt = rt->chip->comm;

	/* enable analog inमाला_दो and outमाला_दो
	 * (one bit per stereo-channel) */
	ret = comm_rt->ग_लिखो16(comm_rt, 0x02, 0x02,
			(1 << (n_analog_out / 2)) - 1,
			(1 << (n_analog_in / 2)) - 1);
	अगर (ret < 0)
		वापस ret;

	/* disable digital inमाला_दो and outमाला_दो */
	/* TODO: use spdअगर_x to enable/disable digital channels */
	ret = comm_rt->ग_लिखो16(comm_rt, 0x02, 0x03, 0x00, 0x00);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक usb6fire_control_streaming_update(काष्ठा control_runसमय *rt)
अणु
	काष्ठा comm_runसमय *comm_rt = rt->chip->comm;

	अगर (comm_rt) अणु
		अगर (!rt->usb_streaming && rt->digital_thru_चयन)
			usb6fire_control_set_rate(rt,
				DIGITAL_THRU_ONLY_SAMPLERATE);
		वापस comm_rt->ग_लिखो16(comm_rt, 0x02, 0x00, 0x00,
			(rt->usb_streaming ? 0x01 : 0x00) |
			(rt->digital_thru_चयन ? 0x08 : 0x00));
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक usb6fire_control_output_vol_info(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 180;
	वापस 0;
पूर्ण

अटल पूर्णांक usb6fire_control_output_vol_put(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा control_runसमय *rt = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक ch = kcontrol->निजी_value;
	पूर्णांक changed = 0;

	अगर (ch > 4) अणु
		dev_err(&rt->chip->dev->dev,
			"Invalid channel in volume control.");
		वापस -EINVAL;
	पूर्ण

	अगर (rt->output_vol[ch] != ucontrol->value.पूर्णांकeger.value[0]) अणु
		rt->output_vol[ch] = ucontrol->value.पूर्णांकeger.value[0];
		rt->ovol_updated &= ~(1 << ch);
		changed = 1;
	पूर्ण
	अगर (rt->output_vol[ch + 1] != ucontrol->value.पूर्णांकeger.value[1]) अणु
		rt->output_vol[ch + 1] = ucontrol->value.पूर्णांकeger.value[1];
		rt->ovol_updated &= ~(2 << ch);
		changed = 1;
	पूर्ण

	अगर (changed)
		usb6fire_control_output_vol_update(rt);

	वापस changed;
पूर्ण

अटल पूर्णांक usb6fire_control_output_vol_get(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा control_runसमय *rt = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक ch = kcontrol->निजी_value;

	अगर (ch > 4) अणु
		dev_err(&rt->chip->dev->dev,
			"Invalid channel in volume control.");
		वापस -EINVAL;
	पूर्ण

	ucontrol->value.पूर्णांकeger.value[0] = rt->output_vol[ch];
	ucontrol->value.पूर्णांकeger.value[1] = rt->output_vol[ch + 1];
	वापस 0;
पूर्ण

अटल पूर्णांक usb6fire_control_output_mute_put(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा control_runसमय *rt = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक ch = kcontrol->निजी_value;
	u8 old = rt->output_mute;
	u8 value = 0;

	अगर (ch > 4) अणु
		dev_err(&rt->chip->dev->dev,
			"Invalid channel in volume control.");
		वापस -EINVAL;
	पूर्ण

	rt->output_mute &= ~(3 << ch);
	अगर (ucontrol->value.पूर्णांकeger.value[0])
		value |= 1;
	अगर (ucontrol->value.पूर्णांकeger.value[1])
		value |= 2;
	rt->output_mute |= value << ch;

	अगर (rt->output_mute != old)
		usb6fire_control_output_mute_update(rt);

	वापस rt->output_mute != old;
पूर्ण

अटल पूर्णांक usb6fire_control_output_mute_get(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा control_runसमय *rt = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक ch = kcontrol->निजी_value;
	u8 value = rt->output_mute >> ch;

	अगर (ch > 4) अणु
		dev_err(&rt->chip->dev->dev,
			"Invalid channel in volume control.");
		वापस -EINVAL;
	पूर्ण

	ucontrol->value.पूर्णांकeger.value[0] = 1 & value;
	value >>= 1;
	ucontrol->value.पूर्णांकeger.value[1] = 1 & value;

	वापस 0;
पूर्ण

अटल पूर्णांक usb6fire_control_input_vol_info(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 30;
	वापस 0;
पूर्ण

अटल पूर्णांक usb6fire_control_input_vol_put(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा control_runसमय *rt = snd_kcontrol_chip(kcontrol);
	पूर्णांक changed = 0;

	अगर (rt->input_vol[0] != ucontrol->value.पूर्णांकeger.value[0]) अणु
		rt->input_vol[0] = ucontrol->value.पूर्णांकeger.value[0] - 15;
		rt->ivol_updated &= ~(1 << 0);
		changed = 1;
	पूर्ण
	अगर (rt->input_vol[1] != ucontrol->value.पूर्णांकeger.value[1]) अणु
		rt->input_vol[1] = ucontrol->value.पूर्णांकeger.value[1] - 15;
		rt->ivol_updated &= ~(1 << 1);
		changed = 1;
	पूर्ण

	अगर (changed)
		usb6fire_control_input_vol_update(rt);

	वापस changed;
पूर्ण

अटल पूर्णांक usb6fire_control_input_vol_get(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा control_runसमय *rt = snd_kcontrol_chip(kcontrol);

	ucontrol->value.पूर्णांकeger.value[0] = rt->input_vol[0] + 15;
	ucontrol->value.पूर्णांकeger.value[1] = rt->input_vol[1] + 15;

	वापस 0;
पूर्ण

अटल पूर्णांक usb6fire_control_line_phono_info(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_info *uinfo)
अणु
	वापस snd_ctl_क्रमागत_info(uinfo, 1, 2, line_phono_texts);
पूर्ण

अटल पूर्णांक usb6fire_control_line_phono_put(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा control_runसमय *rt = snd_kcontrol_chip(kcontrol);
	पूर्णांक changed = 0;
	अगर (rt->line_phono_चयन != ucontrol->value.पूर्णांकeger.value[0]) अणु
		rt->line_phono_चयन = ucontrol->value.पूर्णांकeger.value[0];
		usb6fire_control_line_phono_update(rt);
		changed = 1;
	पूर्ण
	वापस changed;
पूर्ण

अटल पूर्णांक usb6fire_control_line_phono_get(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा control_runसमय *rt = snd_kcontrol_chip(kcontrol);
	ucontrol->value.पूर्णांकeger.value[0] = rt->line_phono_चयन;
	वापस 0;
पूर्ण

अटल पूर्णांक usb6fire_control_opt_coax_info(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_info *uinfo)
अणु
	वापस snd_ctl_क्रमागत_info(uinfo, 1, 2, opt_coax_texts);
पूर्ण

अटल पूर्णांक usb6fire_control_opt_coax_put(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा control_runसमय *rt = snd_kcontrol_chip(kcontrol);
	पूर्णांक changed = 0;

	अगर (rt->opt_coax_चयन != ucontrol->value.क्रमागतerated.item[0]) अणु
		rt->opt_coax_चयन = ucontrol->value.क्रमागतerated.item[0];
		usb6fire_control_opt_coax_update(rt);
		changed = 1;
	पूर्ण
	वापस changed;
पूर्ण

अटल पूर्णांक usb6fire_control_opt_coax_get(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा control_runसमय *rt = snd_kcontrol_chip(kcontrol);
	ucontrol->value.क्रमागतerated.item[0] = rt->opt_coax_चयन;
	वापस 0;
पूर्ण

अटल पूर्णांक usb6fire_control_digital_thru_put(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा control_runसमय *rt = snd_kcontrol_chip(kcontrol);
	पूर्णांक changed = 0;

	अगर (rt->digital_thru_चयन != ucontrol->value.पूर्णांकeger.value[0]) अणु
		rt->digital_thru_चयन = ucontrol->value.पूर्णांकeger.value[0];
		usb6fire_control_streaming_update(rt);
		changed = 1;
	पूर्ण
	वापस changed;
पूर्ण

अटल पूर्णांक usb6fire_control_digital_thru_get(काष्ठा snd_kcontrol *kcontrol,
		काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा control_runसमय *rt = snd_kcontrol_chip(kcontrol);
	ucontrol->value.पूर्णांकeger.value[0] = rt->digital_thru_चयन;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new vol_elements[] = अणु
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Analog Playback Volume",
		.index = 0,
		.निजी_value = 0,
		.access = SNDRV_CTL_ELEM_ACCESS_READWRITE |
			SNDRV_CTL_ELEM_ACCESS_TLV_READ,
		.info = usb6fire_control_output_vol_info,
		.get = usb6fire_control_output_vol_get,
		.put = usb6fire_control_output_vol_put,
		.tlv = अणु .p = tlv_output पूर्ण
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Analog Playback Volume",
		.index = 1,
		.निजी_value = 2,
		.access = SNDRV_CTL_ELEM_ACCESS_READWRITE |
			SNDRV_CTL_ELEM_ACCESS_TLV_READ,
		.info = usb6fire_control_output_vol_info,
		.get = usb6fire_control_output_vol_get,
		.put = usb6fire_control_output_vol_put,
		.tlv = अणु .p = tlv_output पूर्ण
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Analog Playback Volume",
		.index = 2,
		.निजी_value = 4,
		.access = SNDRV_CTL_ELEM_ACCESS_READWRITE |
			SNDRV_CTL_ELEM_ACCESS_TLV_READ,
		.info = usb6fire_control_output_vol_info,
		.get = usb6fire_control_output_vol_get,
		.put = usb6fire_control_output_vol_put,
		.tlv = अणु .p = tlv_output पूर्ण
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mute_elements[] = अणु
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Analog Playback Switch",
		.index = 0,
		.निजी_value = 0,
		.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
		.info = snd_ctl_boolean_stereo_info,
		.get = usb6fire_control_output_mute_get,
		.put = usb6fire_control_output_mute_put,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Analog Playback Switch",
		.index = 1,
		.निजी_value = 2,
		.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
		.info = snd_ctl_boolean_stereo_info,
		.get = usb6fire_control_output_mute_get,
		.put = usb6fire_control_output_mute_put,
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Analog Playback Switch",
		.index = 2,
		.निजी_value = 4,
		.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
		.info = snd_ctl_boolean_stereo_info,
		.get = usb6fire_control_output_mute_get,
		.put = usb6fire_control_output_mute_put,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new elements[] = अणु
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Line/Phono Capture Route",
		.index = 0,
		.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
		.info = usb6fire_control_line_phono_info,
		.get = usb6fire_control_line_phono_get,
		.put = usb6fire_control_line_phono_put
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Opt/Coax Capture Route",
		.index = 0,
		.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
		.info = usb6fire_control_opt_coax_info,
		.get = usb6fire_control_opt_coax_get,
		.put = usb6fire_control_opt_coax_put
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Digital Thru Playback Route",
		.index = 0,
		.access = SNDRV_CTL_ELEM_ACCESS_READWRITE,
		.info = snd_ctl_boolean_mono_info,
		.get = usb6fire_control_digital_thru_get,
		.put = usb6fire_control_digital_thru_put
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name = "Analog Capture Volume",
		.index = 0,
		.access = SNDRV_CTL_ELEM_ACCESS_READWRITE |
			SNDRV_CTL_ELEM_ACCESS_TLV_READ,
		.info = usb6fire_control_input_vol_info,
		.get = usb6fire_control_input_vol_get,
		.put = usb6fire_control_input_vol_put,
		.tlv = अणु .p = tlv_input पूर्ण
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक usb6fire_control_add_भव(
	काष्ठा control_runसमय *rt,
	काष्ठा snd_card *card,
	अक्षर *name,
	स्थिर काष्ठा snd_kcontrol_new *elems)
अणु
	पूर्णांक ret;
	पूर्णांक i;
	काष्ठा snd_kcontrol *vmaster =
		snd_ctl_make_भव_master(name, tlv_output);
	काष्ठा snd_kcontrol *control;

	अगर (!vmaster)
		वापस -ENOMEM;
	ret = snd_ctl_add(card, vmaster);
	अगर (ret < 0)
		वापस ret;

	i = 0;
	जबतक (elems[i].name) अणु
		control = snd_ctl_new1(&elems[i], rt);
		अगर (!control)
			वापस -ENOMEM;
		ret = snd_ctl_add(card, control);
		अगर (ret < 0)
			वापस ret;
		ret = snd_ctl_add_follower(vmaster, control);
		अगर (ret < 0)
			वापस ret;
		i++;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक usb6fire_control_init(काष्ठा sfire_chip *chip)
अणु
	पूर्णांक i;
	पूर्णांक ret;
	काष्ठा control_runसमय *rt = kzalloc(माप(काष्ठा control_runसमय),
			GFP_KERNEL);
	काष्ठा comm_runसमय *comm_rt = chip->comm;

	अगर (!rt)
		वापस -ENOMEM;

	rt->chip = chip;
	rt->update_streaming = usb6fire_control_streaming_update;
	rt->set_rate = usb6fire_control_set_rate;
	rt->set_channels = usb6fire_control_set_channels;

	i = 0;
	जबतक (init_data[i].type) अणु
		comm_rt->ग_लिखो8(comm_rt, init_data[i].type, init_data[i].reg,
				init_data[i].value);
		i++;
	पूर्ण

	usb6fire_control_opt_coax_update(rt);
	usb6fire_control_line_phono_update(rt);
	usb6fire_control_output_vol_update(rt);
	usb6fire_control_output_mute_update(rt);
	usb6fire_control_input_vol_update(rt);
	usb6fire_control_streaming_update(rt);

	ret = usb6fire_control_add_भव(rt, chip->card,
		"Master Playback Volume", vol_elements);
	अगर (ret) अणु
		dev_err(&chip->dev->dev, "cannot add control.\n");
		kमुक्त(rt);
		वापस ret;
	पूर्ण
	ret = usb6fire_control_add_भव(rt, chip->card,
		"Master Playback Switch", mute_elements);
	अगर (ret) अणु
		dev_err(&chip->dev->dev, "cannot add control.\n");
		kमुक्त(rt);
		वापस ret;
	पूर्ण

	i = 0;
	जबतक (elements[i].name) अणु
		ret = snd_ctl_add(chip->card, snd_ctl_new1(&elements[i], rt));
		अगर (ret < 0) अणु
			kमुक्त(rt);
			dev_err(&chip->dev->dev, "cannot add control.\n");
			वापस ret;
		पूर्ण
		i++;
	पूर्ण

	chip->control = rt;
	वापस 0;
पूर्ण

व्योम usb6fire_control_पात(काष्ठा sfire_chip *chip)
अणुपूर्ण

व्योम usb6fire_control_destroy(काष्ठा sfire_chip *chip)
अणु
	kमुक्त(chip->control);
	chip->control = शून्य;
पूर्ण
