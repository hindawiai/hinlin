<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * oxfw-spkr.c - a part of driver क्रम OXFW970/971 based devices
 *
 * Copyright (c) Clemens Ladisch <clemens@ladisch.de>
 */

#समावेश "oxfw.h"

काष्ठा fw_spkr अणु
	bool mute;
	s16 volume[6];
	s16 volume_min;
	s16 volume_max;

	अचिन्हित पूर्णांक mixer_channels;
	u8 mute_fb_id;
	u8 volume_fb_id;
पूर्ण;

क्रमागत control_action अणु CTL_READ, CTL_WRITE पूर्ण;
क्रमागत control_attribute अणु
	CTL_MIN		= 0x02,
	CTL_MAX		= 0x03,
	CTL_CURRENT	= 0x10,
पूर्ण;

अटल पूर्णांक avc_audio_feature_mute(काष्ठा fw_unit *unit, u8 fb_id, bool *value,
				  क्रमागत control_action action)
अणु
	u8 *buf;
	u8 response_ok;
	पूर्णांक err;

	buf = kदो_स्मृति(11, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	अगर (action == CTL_READ) अणु
		buf[0] = 0x01;		/* AV/C, STATUS */
		response_ok = 0x0c;	/*       STABLE */
	पूर्ण अन्यथा अणु
		buf[0] = 0x00;		/* AV/C, CONTROL */
		response_ok = 0x09;	/*       ACCEPTED */
	पूर्ण
	buf[1] = 0x08;			/* audio unit 0 */
	buf[2] = 0xb8;			/* FUNCTION BLOCK */
	buf[3] = 0x81;			/* function block type: feature */
	buf[4] = fb_id;			/* function block ID */
	buf[5] = 0x10;			/* control attribute: current */
	buf[6] = 0x02;			/* selector length */
	buf[7] = 0x00;			/* audio channel number */
	buf[8] = 0x01;			/* control selector: mute */
	buf[9] = 0x01;			/* control data length */
	अगर (action == CTL_READ)
		buf[10] = 0xff;
	अन्यथा
		buf[10] = *value ? 0x70 : 0x60;

	err = fcp_avc_transaction(unit, buf, 11, buf, 11, 0x3fe);
	अगर (err < 0)
		जाओ error;
	अगर (err < 11) अणु
		dev_err(&unit->device, "short FCP response\n");
		err = -EIO;
		जाओ error;
	पूर्ण
	अगर (buf[0] != response_ok) अणु
		dev_err(&unit->device, "mute command failed\n");
		err = -EIO;
		जाओ error;
	पूर्ण
	अगर (action == CTL_READ)
		*value = buf[10] == 0x70;

	err = 0;

error:
	kमुक्त(buf);

	वापस err;
पूर्ण

अटल पूर्णांक avc_audio_feature_volume(काष्ठा fw_unit *unit, u8 fb_id, s16 *value,
				    अचिन्हित पूर्णांक channel,
				    क्रमागत control_attribute attribute,
				    क्रमागत control_action action)
अणु
	u8 *buf;
	u8 response_ok;
	पूर्णांक err;

	buf = kदो_स्मृति(12, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	अगर (action == CTL_READ) अणु
		buf[0] = 0x01;		/* AV/C, STATUS */
		response_ok = 0x0c;	/*       STABLE */
	पूर्ण अन्यथा अणु
		buf[0] = 0x00;		/* AV/C, CONTROL */
		response_ok = 0x09;	/*       ACCEPTED */
	पूर्ण
	buf[1] = 0x08;			/* audio unit 0 */
	buf[2] = 0xb8;			/* FUNCTION BLOCK */
	buf[3] = 0x81;			/* function block type: feature */
	buf[4] = fb_id;			/* function block ID */
	buf[5] = attribute;		/* control attribute */
	buf[6] = 0x02;			/* selector length */
	buf[7] = channel;		/* audio channel number */
	buf[8] = 0x02;			/* control selector: volume */
	buf[9] = 0x02;			/* control data length */
	अगर (action == CTL_READ) अणु
		buf[10] = 0xff;
		buf[11] = 0xff;
	पूर्ण अन्यथा अणु
		buf[10] = *value >> 8;
		buf[11] = *value;
	पूर्ण

	err = fcp_avc_transaction(unit, buf, 12, buf, 12, 0x3fe);
	अगर (err < 0)
		जाओ error;
	अगर (err < 12) अणु
		dev_err(&unit->device, "short FCP response\n");
		err = -EIO;
		जाओ error;
	पूर्ण
	अगर (buf[0] != response_ok) अणु
		dev_err(&unit->device, "volume command failed\n");
		err = -EIO;
		जाओ error;
	पूर्ण
	अगर (action == CTL_READ)
		*value = (buf[10] << 8) | buf[11];

	err = 0;

error:
	kमुक्त(buf);

	वापस err;
पूर्ण

अटल पूर्णांक spkr_mute_get(काष्ठा snd_kcontrol *control,
			 काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा snd_oxfw *oxfw = control->निजी_data;
	काष्ठा fw_spkr *spkr = oxfw->spec;

	value->value.पूर्णांकeger.value[0] = !spkr->mute;

	वापस 0;
पूर्ण

अटल पूर्णांक spkr_mute_put(काष्ठा snd_kcontrol *control,
			 काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा snd_oxfw *oxfw = control->निजी_data;
	काष्ठा fw_spkr *spkr = oxfw->spec;
	bool mute;
	पूर्णांक err;

	mute = !value->value.पूर्णांकeger.value[0];

	अगर (mute == spkr->mute)
		वापस 0;

	err = avc_audio_feature_mute(oxfw->unit, spkr->mute_fb_id, &mute,
				     CTL_WRITE);
	अगर (err < 0)
		वापस err;
	spkr->mute = mute;

	वापस 1;
पूर्ण

अटल पूर्णांक spkr_volume_info(काष्ठा snd_kcontrol *control,
			    काष्ठा snd_ctl_elem_info *info)
अणु
	काष्ठा snd_oxfw *oxfw = control->निजी_data;
	काष्ठा fw_spkr *spkr = oxfw->spec;

	info->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	info->count = spkr->mixer_channels;
	info->value.पूर्णांकeger.min = spkr->volume_min;
	info->value.पूर्णांकeger.max = spkr->volume_max;

	वापस 0;
पूर्ण

अटल स्थिर u8 channel_map[6] = अणु 0, 1, 4, 5, 2, 3 पूर्ण;

अटल पूर्णांक spkr_volume_get(काष्ठा snd_kcontrol *control,
			   काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा snd_oxfw *oxfw = control->निजी_data;
	काष्ठा fw_spkr *spkr = oxfw->spec;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < spkr->mixer_channels; ++i)
		value->value.पूर्णांकeger.value[channel_map[i]] = spkr->volume[i];

	वापस 0;
पूर्ण

अटल पूर्णांक spkr_volume_put(काष्ठा snd_kcontrol *control,
			   काष्ठा snd_ctl_elem_value *value)
अणु
	काष्ठा snd_oxfw *oxfw = control->निजी_data;
	काष्ठा fw_spkr *spkr = oxfw->spec;
	अचिन्हित पूर्णांक i, changed_channels;
	bool equal_values = true;
	s16 volume;
	पूर्णांक err;

	क्रम (i = 0; i < spkr->mixer_channels; ++i) अणु
		अगर (value->value.पूर्णांकeger.value[i] < spkr->volume_min ||
		    value->value.पूर्णांकeger.value[i] > spkr->volume_max)
			वापस -EINVAL;
		अगर (value->value.पूर्णांकeger.value[i] !=
		    value->value.पूर्णांकeger.value[0])
			equal_values = false;
	पूर्ण

	changed_channels = 0;
	क्रम (i = 0; i < spkr->mixer_channels; ++i)
		अगर (value->value.पूर्णांकeger.value[channel_map[i]] !=
							spkr->volume[i])
			changed_channels |= 1 << (i + 1);

	अगर (equal_values && changed_channels != 0)
		changed_channels = 1 << 0;

	क्रम (i = 0; i <= spkr->mixer_channels; ++i) अणु
		volume = value->value.पूर्णांकeger.value[channel_map[i ? i - 1 : 0]];
		अगर (changed_channels & (1 << i)) अणु
			err = avc_audio_feature_volume(oxfw->unit,
						  spkr->volume_fb_id, &volume,
						  i, CTL_CURRENT, CTL_WRITE);
			अगर (err < 0)
				वापस err;
		पूर्ण
		अगर (i > 0)
			spkr->volume[i - 1] = volume;
	पूर्ण

	वापस changed_channels != 0;
पूर्ण

पूर्णांक snd_oxfw_add_spkr(काष्ठा snd_oxfw *oxfw, bool is_lacie)
अणु
	अटल स्थिर काष्ठा snd_kcontrol_new controls[] = अणु
		अणु
			.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
			.name = "PCM Playback Switch",
			.info = snd_ctl_boolean_mono_info,
			.get = spkr_mute_get,
			.put = spkr_mute_put,
		पूर्ण,
		अणु
			.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
			.name = "PCM Playback Volume",
			.info = spkr_volume_info,
			.get = spkr_volume_get,
			.put = spkr_volume_put,
		पूर्ण,
	पूर्ण;
	काष्ठा fw_spkr *spkr;
	अचिन्हित पूर्णांक i, first_ch;
	पूर्णांक err;

	spkr = devm_kzalloc(&oxfw->card->card_dev, माप(काष्ठा fw_spkr),
			    GFP_KERNEL);
	अगर (!spkr)
		वापस -ENOMEM;
	oxfw->spec = spkr;

	अगर (is_lacie) अणु
		spkr->mixer_channels = 1;
		spkr->mute_fb_id = 0x01;
		spkr->volume_fb_id = 0x01;
	पूर्ण अन्यथा अणु
		spkr->mixer_channels = 6;
		spkr->mute_fb_id = 0x01;
		spkr->volume_fb_id = 0x02;
	पूर्ण

	err = avc_audio_feature_volume(oxfw->unit, spkr->volume_fb_id,
				       &spkr->volume_min, 0, CTL_MIN, CTL_READ);
	अगर (err < 0)
		वापस err;
	err = avc_audio_feature_volume(oxfw->unit, spkr->volume_fb_id,
				       &spkr->volume_max, 0, CTL_MAX, CTL_READ);
	अगर (err < 0)
		वापस err;

	err = avc_audio_feature_mute(oxfw->unit, spkr->mute_fb_id, &spkr->mute,
				     CTL_READ);
	अगर (err < 0)
		वापस err;

	first_ch = spkr->mixer_channels == 1 ? 0 : 1;
	क्रम (i = 0; i < spkr->mixer_channels; ++i) अणु
		err = avc_audio_feature_volume(oxfw->unit, spkr->volume_fb_id,
					       &spkr->volume[i], first_ch + i,
					       CTL_CURRENT, CTL_READ);
		अगर (err < 0)
			वापस err;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(controls); ++i) अणु
		err = snd_ctl_add(oxfw->card,
				  snd_ctl_new1(&controls[i], oxfw));
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण
