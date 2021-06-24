<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
#घोषणा __NO_VERSION__
/*
 * Driver क्रम Digigram pcxhr compatible soundcards
 *
 * mixer callbacks
 *
 * Copyright (c) 2004 by Digigram <alsa@digigram.com>
 */

#समावेश <linux/समय.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/mutex.h>
#समावेश <sound/core.h>
#समावेश "pcxhr.h"
#समावेश "pcxhr_hwdep.h"
#समावेश "pcxhr_core.h"
#समावेश <sound/control.h>
#समावेश <sound/tlv.h>
#समावेश <sound/asoundef.h>
#समावेश "pcxhr_mixer.h"
#समावेश "pcxhr_mix22.h"

#घोषणा PCXHR_LINE_CAPTURE_LEVEL_MIN   0	/* -112.0 dB */
#घोषणा PCXHR_LINE_CAPTURE_LEVEL_MAX   255	/* +15.5 dB */
#घोषणा PCXHR_LINE_CAPTURE_ZERO_LEVEL  224	/* 0.0 dB ( 0 dBu -> 0 dBFS ) */

#घोषणा PCXHR_LINE_PLAYBACK_LEVEL_MIN  0	/* -104.0 dB */
#घोषणा PCXHR_LINE_PLAYBACK_LEVEL_MAX  128	/* +24.0 dB */
#घोषणा PCXHR_LINE_PLAYBACK_ZERO_LEVEL 104	/* 0.0 dB ( 0 dBFS -> 0 dBu ) */

अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_analog_capture, -11200, 50, 1550);
अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_analog_playback, -10400, 100, 2400);

अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_a_hr222_capture, -11150, 50, 1600);
अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_a_hr222_playback, -2550, 50, 2400);

अटल पूर्णांक pcxhr_update_analog_audio_level(काष्ठा snd_pcxhr *chip,
					   पूर्णांक is_capture, पूर्णांक channel)
अणु
	पूर्णांक err, vol;
	काष्ठा pcxhr_rmh rmh;

	pcxhr_init_rmh(&rmh, CMD_ACCESS_IO_WRITE);
	अगर (is_capture) अणु
		rmh.cmd[0] |= IO_NUM_REG_IN_ANA_LEVEL;
		rmh.cmd[2] = chip->analog_capture_volume[channel];
	पूर्ण अन्यथा अणु
		rmh.cmd[0] |= IO_NUM_REG_OUT_ANA_LEVEL;
		अगर (chip->analog_playback_active[channel])
			vol = chip->analog_playback_volume[channel];
		अन्यथा
			vol = PCXHR_LINE_PLAYBACK_LEVEL_MIN;
		/* playback analog levels are inversed */
		rmh.cmd[2] = PCXHR_LINE_PLAYBACK_LEVEL_MAX - vol;
	पूर्ण
	rmh.cmd[1]  = 1 << ((2 * chip->chip_idx) + channel);	/* audio mask */
	rmh.cmd_len = 3;
	err = pcxhr_send_msg(chip->mgr, &rmh);
	अगर (err < 0) अणु
		dev_dbg(chip->card->dev,
			"error update_analog_audio_level card(%d)"
			   " is_capture(%d) err(%x)\n",
			   chip->chip_idx, is_capture, err);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * analog level control
 */
अटल पूर्णांक pcxhr_analog_vol_info(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा snd_pcxhr *chip = snd_kcontrol_chip(kcontrol);

	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	अगर (kcontrol->निजी_value == 0) अणु	/* playback */
	    अगर (chip->mgr->is_hr_stereo) अणु
		uinfo->value.पूर्णांकeger.min =
			HR222_LINE_PLAYBACK_LEVEL_MIN;	/* -25 dB */
		uinfo->value.पूर्णांकeger.max =
			HR222_LINE_PLAYBACK_LEVEL_MAX;	/* +24 dB */
	    पूर्ण अन्यथा अणु
		uinfo->value.पूर्णांकeger.min =
			PCXHR_LINE_PLAYBACK_LEVEL_MIN;	/*-104 dB */
		uinfo->value.पूर्णांकeger.max =
			PCXHR_LINE_PLAYBACK_LEVEL_MAX;	/* +24 dB */
	    पूर्ण
	पूर्ण अन्यथा अणु				/* capture */
	    अगर (chip->mgr->is_hr_stereo) अणु
		uinfo->value.पूर्णांकeger.min =
			HR222_LINE_CAPTURE_LEVEL_MIN;	/*-112 dB */
		uinfo->value.पूर्णांकeger.max =
			HR222_LINE_CAPTURE_LEVEL_MAX;	/* +15.5 dB */
	    पूर्ण अन्यथा अणु
		uinfo->value.पूर्णांकeger.min =
			PCXHR_LINE_CAPTURE_LEVEL_MIN;	/*-112 dB */
		uinfo->value.पूर्णांकeger.max =
			PCXHR_LINE_CAPTURE_LEVEL_MAX;	/* +15.5 dB */
	    पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक pcxhr_analog_vol_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pcxhr *chip = snd_kcontrol_chip(kcontrol);
	mutex_lock(&chip->mgr->mixer_mutex);
	अगर (kcontrol->निजी_value == 0) अणु	/* playback */
	  ucontrol->value.पूर्णांकeger.value[0] = chip->analog_playback_volume[0];
	  ucontrol->value.पूर्णांकeger.value[1] = chip->analog_playback_volume[1];
	पूर्ण अन्यथा अणु				/* capture */
	  ucontrol->value.पूर्णांकeger.value[0] = chip->analog_capture_volume[0];
	  ucontrol->value.पूर्णांकeger.value[1] = chip->analog_capture_volume[1];
	पूर्ण
	mutex_unlock(&chip->mgr->mixer_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक pcxhr_analog_vol_put(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pcxhr *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक changed = 0;
	पूर्णांक is_capture, i;

	mutex_lock(&chip->mgr->mixer_mutex);
	is_capture = (kcontrol->निजी_value != 0);
	क्रम (i = 0; i < 2; i++) अणु
		पूर्णांक  new_volume = ucontrol->value.पूर्णांकeger.value[i];
		पूर्णांक *stored_volume = is_capture ?
			&chip->analog_capture_volume[i] :
			&chip->analog_playback_volume[i];
		अगर (is_capture) अणु
			अगर (chip->mgr->is_hr_stereo) अणु
				अगर (new_volume < HR222_LINE_CAPTURE_LEVEL_MIN ||
				    new_volume > HR222_LINE_CAPTURE_LEVEL_MAX)
					जारी;
			पूर्ण अन्यथा अणु
				अगर (new_volume < PCXHR_LINE_CAPTURE_LEVEL_MIN ||
				    new_volume > PCXHR_LINE_CAPTURE_LEVEL_MAX)
					जारी;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (chip->mgr->is_hr_stereo) अणु
				अगर (new_volume < HR222_LINE_PLAYBACK_LEVEL_MIN ||
				    new_volume > HR222_LINE_PLAYBACK_LEVEL_MAX)
					जारी;
			पूर्ण अन्यथा अणु
				अगर (new_volume < PCXHR_LINE_PLAYBACK_LEVEL_MIN ||
				    new_volume > PCXHR_LINE_PLAYBACK_LEVEL_MAX)
					जारी;
			पूर्ण
		पूर्ण
		अगर (*stored_volume != new_volume) अणु
			*stored_volume = new_volume;
			changed = 1;
			अगर (chip->mgr->is_hr_stereo)
				hr222_update_analog_audio_level(chip,
								is_capture, i);
			अन्यथा
				pcxhr_update_analog_audio_level(chip,
								is_capture, i);
		पूर्ण
	पूर्ण
	mutex_unlock(&chip->mgr->mixer_mutex);
	वापस changed;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new pcxhr_control_analog_level = अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_MIXER,
	.access =	(SNDRV_CTL_ELEM_ACCESS_READWRITE |
			 SNDRV_CTL_ELEM_ACCESS_TLV_READ),
	/* name will be filled later */
	.info =		pcxhr_analog_vol_info,
	.get =		pcxhr_analog_vol_get,
	.put =		pcxhr_analog_vol_put,
	/* tlv will be filled later */
पूर्ण;

/* shared */

#घोषणा pcxhr_sw_info		snd_ctl_boolean_stereo_info

अटल पूर्णांक pcxhr_audio_sw_get(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pcxhr *chip = snd_kcontrol_chip(kcontrol);

	mutex_lock(&chip->mgr->mixer_mutex);
	ucontrol->value.पूर्णांकeger.value[0] = chip->analog_playback_active[0];
	ucontrol->value.पूर्णांकeger.value[1] = chip->analog_playback_active[1];
	mutex_unlock(&chip->mgr->mixer_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक pcxhr_audio_sw_put(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pcxhr *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक i, changed = 0;
	mutex_lock(&chip->mgr->mixer_mutex);
	क्रम(i = 0; i < 2; i++) अणु
		अगर (chip->analog_playback_active[i] !=
		    ucontrol->value.पूर्णांकeger.value[i]) अणु
			chip->analog_playback_active[i] =
				!!ucontrol->value.पूर्णांकeger.value[i];
			changed = 1;
			/* update playback levels */
			अगर (chip->mgr->is_hr_stereo)
				hr222_update_analog_audio_level(chip, 0, i);
			अन्यथा
				pcxhr_update_analog_audio_level(chip, 0, i);
		पूर्ण
	पूर्ण
	mutex_unlock(&chip->mgr->mixer_mutex);
	वापस changed;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new pcxhr_control_output_चयन = अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_MIXER,
	.name =		"Master Playback Switch",
	.info =		pcxhr_sw_info,		/* shared */
	.get =		pcxhr_audio_sw_get,
	.put =		pcxhr_audio_sw_put
पूर्ण;


#घोषणा PCXHR_DIGITAL_LEVEL_MIN		0x000	/* -110 dB */
#घोषणा PCXHR_DIGITAL_LEVEL_MAX		0x1ff	/* +18 dB */
#घोषणा PCXHR_DIGITAL_ZERO_LEVEL	0x1b7	/*  0 dB */

अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_digital, -10975, 25, 1800);

#घोषणा MORE_THAN_ONE_STREAM_LEVEL	0x000001
#घोषणा VALID_STREAM_PAN_LEVEL_MASK	0x800000
#घोषणा VALID_STREAM_LEVEL_MASK		0x400000
#घोषणा VALID_STREAM_LEVEL_1_MASK	0x200000
#घोषणा VALID_STREAM_LEVEL_2_MASK	0x100000

अटल पूर्णांक pcxhr_update_playback_stream_level(काष्ठा snd_pcxhr* chip, पूर्णांक idx)
अणु
	पूर्णांक err;
	काष्ठा pcxhr_rmh rmh;
	काष्ठा pcxhr_pipe *pipe = &chip->playback_pipe;
	पूर्णांक left, right;

	अगर (chip->digital_playback_active[idx][0])
		left = chip->digital_playback_volume[idx][0];
	अन्यथा
		left = PCXHR_DIGITAL_LEVEL_MIN;
	अगर (chip->digital_playback_active[idx][1])
		right = chip->digital_playback_volume[idx][1];
	अन्यथा
		right = PCXHR_DIGITAL_LEVEL_MIN;

	pcxhr_init_rmh(&rmh, CMD_STREAM_OUT_LEVEL_ADJUST);
	/* add pipe and stream mask */
	pcxhr_set_pipe_cmd_params(&rmh, 0, pipe->first_audio, 0, 1<<idx);
	/* volume left->left / right->right panoramic level */
	rmh.cmd[0] |= MORE_THAN_ONE_STREAM_LEVEL;
	rmh.cmd[2]  = VALID_STREAM_PAN_LEVEL_MASK | VALID_STREAM_LEVEL_1_MASK;
	rmh.cmd[2] |= (left << 10);
	rmh.cmd[3]  = VALID_STREAM_PAN_LEVEL_MASK | VALID_STREAM_LEVEL_2_MASK;
	rmh.cmd[3] |= right;
	rmh.cmd_len = 4;

	err = pcxhr_send_msg(chip->mgr, &rmh);
	अगर (err < 0) अणु
		dev_dbg(chip->card->dev, "error update_playback_stream_level "
			   "card(%d) err(%x)\n", chip->chip_idx, err);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा AUDIO_IO_HAS_MUTE_LEVEL		0x400000
#घोषणा AUDIO_IO_HAS_MUTE_MONITOR_1	0x200000
#घोषणा VALID_AUDIO_IO_DIGITAL_LEVEL	0x000001
#घोषणा VALID_AUDIO_IO_MONITOR_LEVEL	0x000002
#घोषणा VALID_AUDIO_IO_MUTE_LEVEL	0x000004
#घोषणा VALID_AUDIO_IO_MUTE_MONITOR_1	0x000008

अटल पूर्णांक pcxhr_update_audio_pipe_level(काष्ठा snd_pcxhr *chip,
					 पूर्णांक capture, पूर्णांक channel)
अणु
	पूर्णांक err;
	काष्ठा pcxhr_rmh rmh;
	काष्ठा pcxhr_pipe *pipe;

	अगर (capture)
		pipe = &chip->capture_pipe[0];
	अन्यथा
		pipe = &chip->playback_pipe;

	pcxhr_init_rmh(&rmh, CMD_AUDIO_LEVEL_ADJUST);
	/* add channel mask */
	pcxhr_set_pipe_cmd_params(&rmh, capture, 0, 0,
				  1 << (channel + pipe->first_audio));
	/* TODO : अगर mask (3 << pipe->first_audio) is used, left and right
	 * channel will be programmed to the same params */
	अगर (capture) अणु
		rmh.cmd[0] |= VALID_AUDIO_IO_DIGITAL_LEVEL;
		/* VALID_AUDIO_IO_MUTE_LEVEL not yet handled
		 * (capture pipe level) */
		rmh.cmd[2] = chip->digital_capture_volume[channel];
	पूर्ण अन्यथा अणु
		rmh.cmd[0] |=	VALID_AUDIO_IO_MONITOR_LEVEL |
				VALID_AUDIO_IO_MUTE_MONITOR_1;
		/* VALID_AUDIO_IO_DIGITAL_LEVEL and VALID_AUDIO_IO_MUTE_LEVEL
		 * not yet handled (playback pipe level)
		 */
		rmh.cmd[2] = chip->monitoring_volume[channel] << 10;
		अगर (chip->monitoring_active[channel] == 0)
			rmh.cmd[2] |= AUDIO_IO_HAS_MUTE_MONITOR_1;
	पूर्ण
	rmh.cmd_len = 3;

	err = pcxhr_send_msg(chip->mgr, &rmh);
	अगर (err < 0) अणु
		dev_dbg(chip->card->dev,
			"error update_audio_level(%d) err=%x\n",
			   chip->chip_idx, err);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण


/* shared */
अटल पूर्णांक pcxhr_digital_vol_info(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = PCXHR_DIGITAL_LEVEL_MIN;   /* -109.5 dB */
	uinfo->value.पूर्णांकeger.max = PCXHR_DIGITAL_LEVEL_MAX;   /*   18.0 dB */
	वापस 0;
पूर्ण


अटल पूर्णांक pcxhr_pcm_vol_get(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pcxhr *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक idx = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id);	/* index */
	पूर्णांक *stored_volume;
	पूर्णांक is_capture = kcontrol->निजी_value;

	mutex_lock(&chip->mgr->mixer_mutex);
	अगर (is_capture)		/* digital capture */
		stored_volume = chip->digital_capture_volume;
	अन्यथा			/* digital playback */
		stored_volume = chip->digital_playback_volume[idx];
	ucontrol->value.पूर्णांकeger.value[0] = stored_volume[0];
	ucontrol->value.पूर्णांकeger.value[1] = stored_volume[1];
	mutex_unlock(&chip->mgr->mixer_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक pcxhr_pcm_vol_put(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pcxhr *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक idx = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id);	/* index */
	पूर्णांक changed = 0;
	पूर्णांक is_capture = kcontrol->निजी_value;
	पूर्णांक *stored_volume;
	पूर्णांक i;

	mutex_lock(&chip->mgr->mixer_mutex);
	अगर (is_capture)		/* digital capture */
		stored_volume = chip->digital_capture_volume;
	अन्यथा			/* digital playback */
		stored_volume = chip->digital_playback_volume[idx];
	क्रम (i = 0; i < 2; i++) अणु
		पूर्णांक vol = ucontrol->value.पूर्णांकeger.value[i];
		अगर (vol < PCXHR_DIGITAL_LEVEL_MIN ||
		    vol > PCXHR_DIGITAL_LEVEL_MAX)
			जारी;
		अगर (stored_volume[i] != vol) अणु
			stored_volume[i] = vol;
			changed = 1;
			अगर (is_capture)	/* update capture volume */
				pcxhr_update_audio_pipe_level(chip, 1, i);
		पूर्ण
	पूर्ण
	अगर (!is_capture && changed)	/* update playback volume */
		pcxhr_update_playback_stream_level(chip, idx);
	mutex_unlock(&chip->mgr->mixer_mutex);
	वापस changed;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_pcxhr_pcm_vol =
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_MIXER,
	.access =	(SNDRV_CTL_ELEM_ACCESS_READWRITE |
			 SNDRV_CTL_ELEM_ACCESS_TLV_READ),
	/* name will be filled later */
	/* count will be filled later */
	.info =		pcxhr_digital_vol_info,		/* shared */
	.get =		pcxhr_pcm_vol_get,
	.put =		pcxhr_pcm_vol_put,
	.tlv = अणु .p = db_scale_digital पूर्ण,
पूर्ण;


अटल पूर्णांक pcxhr_pcm_sw_get(काष्ठा snd_kcontrol *kcontrol,
			    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pcxhr *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक idx = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id); /* index */

	mutex_lock(&chip->mgr->mixer_mutex);
	ucontrol->value.पूर्णांकeger.value[0] = chip->digital_playback_active[idx][0];
	ucontrol->value.पूर्णांकeger.value[1] = chip->digital_playback_active[idx][1];
	mutex_unlock(&chip->mgr->mixer_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक pcxhr_pcm_sw_put(काष्ठा snd_kcontrol *kcontrol,
			    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pcxhr *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक changed = 0;
	पूर्णांक idx = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id); /* index */
	पूर्णांक i, j;

	mutex_lock(&chip->mgr->mixer_mutex);
	j = idx;
	क्रम (i = 0; i < 2; i++) अणु
		अगर (chip->digital_playback_active[j][i] !=
		    ucontrol->value.पूर्णांकeger.value[i]) अणु
			chip->digital_playback_active[j][i] =
				!!ucontrol->value.पूर्णांकeger.value[i];
			changed = 1;
		पूर्ण
	पूर्ण
	अगर (changed)
		pcxhr_update_playback_stream_level(chip, idx);
	mutex_unlock(&chip->mgr->mixer_mutex);
	वापस changed;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new pcxhr_control_pcm_चयन = अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_MIXER,
	.name =		"PCM Playback Switch",
	.count =	PCXHR_PLAYBACK_STREAMS,
	.info =		pcxhr_sw_info,		/* shared */
	.get =		pcxhr_pcm_sw_get,
	.put =		pcxhr_pcm_sw_put
पूर्ण;


/*
 * monitoring level control
 */

अटल पूर्णांक pcxhr_monitor_vol_get(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pcxhr *chip = snd_kcontrol_chip(kcontrol);
	mutex_lock(&chip->mgr->mixer_mutex);
	ucontrol->value.पूर्णांकeger.value[0] = chip->monitoring_volume[0];
	ucontrol->value.पूर्णांकeger.value[1] = chip->monitoring_volume[1];
	mutex_unlock(&chip->mgr->mixer_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक pcxhr_monitor_vol_put(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pcxhr *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक changed = 0;
	पूर्णांक i;

	mutex_lock(&chip->mgr->mixer_mutex);
	क्रम (i = 0; i < 2; i++) अणु
		अगर (chip->monitoring_volume[i] !=
		    ucontrol->value.पूर्णांकeger.value[i]) अणु
			chip->monitoring_volume[i] =
				ucontrol->value.पूर्णांकeger.value[i];
			अगर (chip->monitoring_active[i])
				/* update monitoring volume and mute */
				/* करो only when monitoring is unmuted */
				pcxhr_update_audio_pipe_level(chip, 0, i);
			changed = 1;
		पूर्ण
	पूर्ण
	mutex_unlock(&chip->mgr->mixer_mutex);
	वापस changed;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new pcxhr_control_monitor_vol = अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_MIXER,
	.access =	(SNDRV_CTL_ELEM_ACCESS_READWRITE |
			 SNDRV_CTL_ELEM_ACCESS_TLV_READ),
	.name =         "Monitoring Playback Volume",
	.info =		pcxhr_digital_vol_info,		/* shared */
	.get =		pcxhr_monitor_vol_get,
	.put =		pcxhr_monitor_vol_put,
	.tlv = अणु .p = db_scale_digital पूर्ण,
पूर्ण;

/*
 * monitoring चयन control
 */

अटल पूर्णांक pcxhr_monitor_sw_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pcxhr *chip = snd_kcontrol_chip(kcontrol);
	mutex_lock(&chip->mgr->mixer_mutex);
	ucontrol->value.पूर्णांकeger.value[0] = chip->monitoring_active[0];
	ucontrol->value.पूर्णांकeger.value[1] = chip->monitoring_active[1];
	mutex_unlock(&chip->mgr->mixer_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक pcxhr_monitor_sw_put(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pcxhr *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक changed = 0;
	पूर्णांक i;

	mutex_lock(&chip->mgr->mixer_mutex);
	क्रम (i = 0; i < 2; i++) अणु
		अगर (chip->monitoring_active[i] !=
		    ucontrol->value.पूर्णांकeger.value[i]) अणु
			chip->monitoring_active[i] =
				!!ucontrol->value.पूर्णांकeger.value[i];
			changed |= (1<<i); /* mask 0x01 and 0x02 */
		पूर्ण
	पूर्ण
	अगर (changed & 0x01)
		/* update left monitoring volume and mute */
		pcxhr_update_audio_pipe_level(chip, 0, 0);
	अगर (changed & 0x02)
		/* update right monitoring volume and mute */
		pcxhr_update_audio_pipe_level(chip, 0, 1);

	mutex_unlock(&chip->mgr->mixer_mutex);
	वापस (changed != 0);
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new pcxhr_control_monitor_sw = अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_MIXER,
	.name =         "Monitoring Playback Switch",
	.info =         pcxhr_sw_info,		/* shared */
	.get =          pcxhr_monitor_sw_get,
	.put =          pcxhr_monitor_sw_put
पूर्ण;



/*
 * audio source select
 */
#घोषणा PCXHR_SOURCE_AUDIO01_UER	0x000100
#घोषणा PCXHR_SOURCE_AUDIO01_SYNC	0x000200
#घोषणा PCXHR_SOURCE_AUDIO23_UER	0x000400
#घोषणा PCXHR_SOURCE_AUDIO45_UER	0x001000
#घोषणा PCXHR_SOURCE_AUDIO67_UER	0x040000

अटल पूर्णांक pcxhr_set_audio_source(काष्ठा snd_pcxhr* chip)
अणु
	काष्ठा pcxhr_rmh rmh;
	अचिन्हित पूर्णांक mask, reg;
	अचिन्हित पूर्णांक codec;
	पूर्णांक err, changed;

	चयन (chip->chip_idx) अणु
	हाल 0 : mask = PCXHR_SOURCE_AUDIO01_UER; codec = CS8420_01_CS; अवरोध;
	हाल 1 : mask = PCXHR_SOURCE_AUDIO23_UER; codec = CS8420_23_CS; अवरोध;
	हाल 2 : mask = PCXHR_SOURCE_AUDIO45_UER; codec = CS8420_45_CS; अवरोध;
	हाल 3 : mask = PCXHR_SOURCE_AUDIO67_UER; codec = CS8420_67_CS; अवरोध;
	शेष: वापस -EINVAL;
	पूर्ण
	अगर (chip->audio_capture_source != 0) अणु
		reg = mask;	/* audio source from digital plug */
	पूर्ण अन्यथा अणु
		reg = 0;	/* audio source from analog plug */
	पूर्ण
	/* set the input source */
	pcxhr_ग_लिखो_io_num_reg_cont(chip->mgr, mask, reg, &changed);
	/* resync them (otherwise channel inversion possible) */
	अगर (changed) अणु
		pcxhr_init_rmh(&rmh, CMD_RESYNC_AUDIO_INPUTS);
		rmh.cmd[0] |= (1 << chip->chip_idx);
		err = pcxhr_send_msg(chip->mgr, &rmh);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (chip->mgr->board_aes_in_192k) अणु
		पूर्णांक i;
		अचिन्हित पूर्णांक src_config = 0xC0;
		/* update all src configs with one call */
		क्रम (i = 0; (i < 4) && (i < chip->mgr->capture_chips); i++) अणु
			अगर (chip->mgr->chip[i]->audio_capture_source == 2)
				src_config |= (1 << (3 - i));
		पूर्ण
		/* set codec SRC on off */
		pcxhr_init_rmh(&rmh, CMD_ACCESS_IO_WRITE);
		rmh.cmd_len = 2;
		rmh.cmd[0] |= IO_NUM_REG_CONFIG_SRC;
		rmh.cmd[1] = src_config;
		err = pcxhr_send_msg(chip->mgr, &rmh);
	पूर्ण अन्यथा अणु
		पूर्णांक use_src = 0;
		अगर (chip->audio_capture_source == 2)
			use_src = 1;
		/* set codec SRC on off */
		pcxhr_init_rmh(&rmh, CMD_ACCESS_IO_WRITE);
		rmh.cmd_len = 3;
		rmh.cmd[0] |= IO_NUM_UER_CHIP_REG;
		rmh.cmd[1] = codec;
		rmh.cmd[2] = ((CS8420_DATA_FLOW_CTL & CHIP_SIG_AND_MAP_SPI) |
			      (use_src ? 0x41 : 0x54));
		err = pcxhr_send_msg(chip->mgr, &rmh);
		अगर (err)
			वापस err;
		rmh.cmd[2] = ((CS8420_CLOCK_SRC_CTL & CHIP_SIG_AND_MAP_SPI) |
			      (use_src ? 0x41 : 0x49));
		err = pcxhr_send_msg(chip->mgr, &rmh);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक pcxhr_audio_src_info(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर *texts[5] = अणु
		"Line", "Digital", "Digi+SRC", "Mic", "Line+Mic"
	पूर्ण;
	पूर्णांक i;
	काष्ठा snd_pcxhr *chip = snd_kcontrol_chip(kcontrol);

	i = 2;			/* no SRC, no Mic available */
	अगर (chip->mgr->board_has_aes1) अणु
		i = 3;		/* SRC available */
		अगर (chip->mgr->board_has_mic)
			i = 5;	/* Mic and MicroMix available */
	पूर्ण
	वापस snd_ctl_क्रमागत_info(uinfo, 1, i, texts);
पूर्ण

अटल पूर्णांक pcxhr_audio_src_get(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pcxhr *chip = snd_kcontrol_chip(kcontrol);
	ucontrol->value.क्रमागतerated.item[0] = chip->audio_capture_source;
	वापस 0;
पूर्ण

अटल पूर्णांक pcxhr_audio_src_put(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pcxhr *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक ret = 0;
	पूर्णांक i = 2;		/* no SRC, no Mic available */
	अगर (chip->mgr->board_has_aes1) अणु
		i = 3;		/* SRC available */
		अगर (chip->mgr->board_has_mic)
			i = 5;	/* Mic and MicroMix available */
	पूर्ण
	अगर (ucontrol->value.क्रमागतerated.item[0] >= i)
		वापस -EINVAL;
	mutex_lock(&chip->mgr->mixer_mutex);
	अगर (chip->audio_capture_source != ucontrol->value.क्रमागतerated.item[0]) अणु
		chip->audio_capture_source = ucontrol->value.क्रमागतerated.item[0];
		अगर (chip->mgr->is_hr_stereo)
			hr222_set_audio_source(chip);
		अन्यथा
			pcxhr_set_audio_source(chip);
		ret = 1;
	पूर्ण
	mutex_unlock(&chip->mgr->mixer_mutex);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new pcxhr_control_audio_src = अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_MIXER,
	.name =		"Capture Source",
	.info =		pcxhr_audio_src_info,
	.get =		pcxhr_audio_src_get,
	.put =		pcxhr_audio_src_put,
पूर्ण;


/*
 * घड़ी type selection
 * क्रमागत pcxhr_घड़ी_प्रकारype अणु
 *	PCXHR_CLOCK_TYPE_INTERNAL = 0,
 *	PCXHR_CLOCK_TYPE_WORD_CLOCK,
 *	PCXHR_CLOCK_TYPE_AES_SYNC,
 *	PCXHR_CLOCK_TYPE_AES_1,
 *	PCXHR_CLOCK_TYPE_AES_2,
 *	PCXHR_CLOCK_TYPE_AES_3,
 *	PCXHR_CLOCK_TYPE_AES_4,
 *	PCXHR_CLOCK_TYPE_MAX = PCXHR_CLOCK_TYPE_AES_4,
 *	HR22_CLOCK_TYPE_INTERNAL = PCXHR_CLOCK_TYPE_INTERNAL,
 *	HR22_CLOCK_TYPE_AES_SYNC,
 *	HR22_CLOCK_TYPE_AES_1,
 *	HR22_CLOCK_TYPE_MAX = HR22_CLOCK_TYPE_AES_1,
 * पूर्ण;
 */

अटल पूर्णांक pcxhr_घड़ी_प्रकारype_info(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर *textsPCXHR[7] = अणु
		"Internal", "WordClock", "AES Sync",
		"AES 1", "AES 2", "AES 3", "AES 4"
	पूर्ण;
	अटल स्थिर अक्षर *textsHR22[3] = अणु
		"Internal", "AES Sync", "AES 1"
	पूर्ण;
	स्थिर अक्षर **texts;
	काष्ठा pcxhr_mgr *mgr = snd_kcontrol_chip(kcontrol);
	पूर्णांक घड़ी_items = 2;	/* at least Internal and AES Sync घड़ी */
	अगर (mgr->board_has_aes1) अणु
		घड़ी_items += mgr->capture_chips;	/* add AES x */
		अगर (!mgr->is_hr_stereo)
			घड़ी_items += 1;		/* add word घड़ी */
	पूर्ण
	अगर (mgr->is_hr_stereo) अणु
		texts = textsHR22;
		snd_BUG_ON(घड़ी_items > (HR22_CLOCK_TYPE_MAX+1));
	पूर्ण अन्यथा अणु
		texts = textsPCXHR;
		snd_BUG_ON(घड़ी_items > (PCXHR_CLOCK_TYPE_MAX+1));
	पूर्ण
	वापस snd_ctl_क्रमागत_info(uinfo, 1, घड़ी_items, texts);
पूर्ण

अटल पूर्णांक pcxhr_घड़ी_प्रकारype_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा pcxhr_mgr *mgr = snd_kcontrol_chip(kcontrol);
	ucontrol->value.क्रमागतerated.item[0] = mgr->use_घड़ी_प्रकारype;
	वापस 0;
पूर्ण

अटल पूर्णांक pcxhr_घड़ी_प्रकारype_put(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा pcxhr_mgr *mgr = snd_kcontrol_chip(kcontrol);
	पूर्णांक rate, ret = 0;
	अचिन्हित पूर्णांक घड़ी_items = 2; /* at least Internal and AES Sync घड़ी */
	अगर (mgr->board_has_aes1) अणु
		घड़ी_items += mgr->capture_chips;	/* add AES x */
		अगर (!mgr->is_hr_stereo)
			घड़ी_items += 1;		/* add word घड़ी */
	पूर्ण
	अगर (ucontrol->value.क्रमागतerated.item[0] >= घड़ी_items)
		वापस -EINVAL;
	mutex_lock(&mgr->mixer_mutex);
	अगर (mgr->use_घड़ी_प्रकारype != ucontrol->value.क्रमागतerated.item[0]) अणु
		mutex_lock(&mgr->setup_mutex);
		mgr->use_घड़ी_प्रकारype = ucontrol->value.क्रमागतerated.item[0];
		rate = 0;
		अगर (mgr->use_घड़ी_प्रकारype != PCXHR_CLOCK_TYPE_INTERNAL) अणु
			pcxhr_get_बाह्यal_घड़ी(mgr, mgr->use_घड़ी_प्रकारype,
						 &rate);
		पूर्ण अन्यथा अणु
			rate = mgr->sample_rate;
			अगर (!rate)
				rate = 48000;
		पूर्ण
		अगर (rate) अणु
			pcxhr_set_घड़ी(mgr, rate);
			अगर (mgr->sample_rate)
				mgr->sample_rate = rate;
		पूर्ण
		mutex_unlock(&mgr->setup_mutex);
		ret = 1; /* वापस 1 even अगर the set was not करोne. ok ? */
	पूर्ण
	mutex_unlock(&mgr->mixer_mutex);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new pcxhr_control_घड़ी_प्रकारype = अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_MIXER,
	.name =		"Clock Mode",
	.info =		pcxhr_घड़ी_प्रकारype_info,
	.get =		pcxhr_घड़ी_प्रकारype_get,
	.put =		pcxhr_घड़ी_प्रकारype_put,
पूर्ण;

/*
 * घड़ी rate control
 * specअगरic control that scans the sample rates on the बाह्यal plugs
 */
अटल पूर्णांक pcxhr_घड़ी_rate_info(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा pcxhr_mgr *mgr = snd_kcontrol_chip(kcontrol);
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 3 + mgr->capture_chips;
	uinfo->value.पूर्णांकeger.min = 0;		/* घड़ी not present */
	uinfo->value.पूर्णांकeger.max = 192000;	/* max sample rate 192 kHz */
	वापस 0;
पूर्ण

अटल पूर्णांक pcxhr_घड़ी_rate_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा pcxhr_mgr *mgr = snd_kcontrol_chip(kcontrol);
	पूर्णांक i, err, rate;

	mutex_lock(&mgr->mixer_mutex);
	क्रम(i = 0; i < 3 + mgr->capture_chips; i++) अणु
		अगर (i == PCXHR_CLOCK_TYPE_INTERNAL)
			rate = mgr->sample_rate_real;
		अन्यथा अणु
			err = pcxhr_get_बाह्यal_घड़ी(mgr, i, &rate);
			अगर (err)
				अवरोध;
		पूर्ण
		ucontrol->value.पूर्णांकeger.value[i] = rate;
	पूर्ण
	mutex_unlock(&mgr->mixer_mutex);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new pcxhr_control_घड़ी_rate = अणु
	.access =	SNDRV_CTL_ELEM_ACCESS_READ,
	.अगरace =	SNDRV_CTL_ELEM_IFACE_CARD,
	.name =		"Clock Rates",
	.info =		pcxhr_घड़ी_rate_info,
	.get =		pcxhr_घड़ी_rate_get,
पूर्ण;

/*
 * IEC958 status bits
 */
अटल पूर्णांक pcxhr_iec958_info(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक pcxhr_iec958_capture_byte(काष्ठा snd_pcxhr *chip,
				     पूर्णांक aes_idx, अचिन्हित अक्षर *aes_bits)
अणु
	पूर्णांक i, err;
	अचिन्हित अक्षर temp;
	काष्ठा pcxhr_rmh rmh;

	pcxhr_init_rmh(&rmh, CMD_ACCESS_IO_READ);
	rmh.cmd[0] |= IO_NUM_UER_CHIP_REG;
	चयन (chip->chip_idx) अणु
	  /* instead of CS8420_01_CS use CS8416_01_CS क्रम AES SYNC plug */
	हाल 0:	rmh.cmd[1] = CS8420_01_CS; अवरोध;
	हाल 1:	rmh.cmd[1] = CS8420_23_CS; अवरोध;
	हाल 2:	rmh.cmd[1] = CS8420_45_CS; अवरोध;
	हाल 3:	rmh.cmd[1] = CS8420_67_CS; अवरोध;
	शेष: वापस -EINVAL;
	पूर्ण
	अगर (chip->mgr->board_aes_in_192k) अणु
		चयन (aes_idx) अणु
		हाल 0:	rmh.cmd[2] = CS8416_CSB0; अवरोध;
		हाल 1:	rmh.cmd[2] = CS8416_CSB1; अवरोध;
		हाल 2:	rmh.cmd[2] = CS8416_CSB2; अवरोध;
		हाल 3:	rmh.cmd[2] = CS8416_CSB3; अवरोध;
		हाल 4:	rmh.cmd[2] = CS8416_CSB4; अवरोध;
		शेष: वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (aes_idx) अणु
		  /* instead of CS8420_CSB0 use CS8416_CSBx क्रम AES SYNC plug */
		हाल 0:	rmh.cmd[2] = CS8420_CSB0; अवरोध;
		हाल 1:	rmh.cmd[2] = CS8420_CSB1; अवरोध;
		हाल 2:	rmh.cmd[2] = CS8420_CSB2; अवरोध;
		हाल 3:	rmh.cmd[2] = CS8420_CSB3; अवरोध;
		हाल 4:	rmh.cmd[2] = CS8420_CSB4; अवरोध;
		शेष: वापस -EINVAL;
		पूर्ण
	पूर्ण
	/* size and code the chip id क्रम the fpga */
	rmh.cmd[1] &= 0x0fffff;
	/* chip signature + map क्रम spi पढ़ो */
	rmh.cmd[2] &= CHIP_SIG_AND_MAP_SPI;
	rmh.cmd_len = 3;
	err = pcxhr_send_msg(chip->mgr, &rmh);
	अगर (err)
		वापस err;

	अगर (chip->mgr->board_aes_in_192k) अणु
		temp = (अचिन्हित अक्षर)rmh.stat[1];
	पूर्ण अन्यथा अणु
		temp = 0;
		/* reversed bit order (not with CS8416_01_CS) */
		क्रम (i = 0; i < 8; i++) अणु
			temp <<= 1;
			अगर (rmh.stat[1] & (1 << i))
				temp |= 1;
		पूर्ण
	पूर्ण
	dev_dbg(chip->card->dev, "read iec958 AES %d byte %d = 0x%x\n",
		    chip->chip_idx, aes_idx, temp);
	*aes_bits = temp;
	वापस 0;
पूर्ण

अटल पूर्णांक pcxhr_iec958_get(काष्ठा snd_kcontrol *kcontrol,
			    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pcxhr *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित अक्षर aes_bits;
	पूर्णांक i, err;

	mutex_lock(&chip->mgr->mixer_mutex);
	क्रम(i = 0; i < 5; i++) अणु
		अगर (kcontrol->निजी_value == 0)	/* playback */
			aes_bits = chip->aes_bits[i];
		अन्यथा अणु				/* capture */
			अगर (chip->mgr->is_hr_stereo)
				err = hr222_iec958_capture_byte(chip, i,
								&aes_bits);
			अन्यथा
				err = pcxhr_iec958_capture_byte(chip, i,
								&aes_bits);
			अगर (err)
				अवरोध;
		पूर्ण
		ucontrol->value.iec958.status[i] = aes_bits;
	पूर्ण
	mutex_unlock(&chip->mgr->mixer_mutex);
        वापस 0;
पूर्ण

अटल पूर्णांक pcxhr_iec958_mask_get(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < 5; i++)
		ucontrol->value.iec958.status[i] = 0xff;
        वापस 0;
पूर्ण

अटल पूर्णांक pcxhr_iec958_update_byte(काष्ठा snd_pcxhr *chip,
				    पूर्णांक aes_idx, अचिन्हित अक्षर aes_bits)
अणु
	पूर्णांक i, err, cmd;
	अचिन्हित अक्षर new_bits = aes_bits;
	अचिन्हित अक्षर old_bits = chip->aes_bits[aes_idx];
	काष्ठा pcxhr_rmh rmh;

	क्रम (i = 0; i < 8; i++) अणु
		अगर ((old_bits & 0x01) != (new_bits & 0x01)) अणु
			cmd = chip->chip_idx & 0x03;      /* chip index 0..3 */
			अगर (chip->chip_idx > 3)
				/* new bit used अगर chip_idx>3 (PCX1222HR) */
				cmd |= 1 << 22;
			cmd |= ((aes_idx << 3) + i) << 2; /* add bit offset */
			cmd |= (new_bits & 0x01) << 23;   /* add bit value */
			pcxhr_init_rmh(&rmh, CMD_ACCESS_IO_WRITE);
			rmh.cmd[0] |= IO_NUM_REG_CUER;
			rmh.cmd[1] = cmd;
			rmh.cmd_len = 2;
			dev_dbg(chip->card->dev,
				"write iec958 AES %d byte %d bit %d (cmd %x)\n",
				    chip->chip_idx, aes_idx, i, cmd);
			err = pcxhr_send_msg(chip->mgr, &rmh);
			अगर (err)
				वापस err;
		पूर्ण
		old_bits >>= 1;
		new_bits >>= 1;
	पूर्ण
	chip->aes_bits[aes_idx] = aes_bits;
	वापस 0;
पूर्ण

अटल पूर्णांक pcxhr_iec958_put(काष्ठा snd_kcontrol *kcontrol,
			    काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_pcxhr *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक i, changed = 0;

	/* playback */
	mutex_lock(&chip->mgr->mixer_mutex);
	क्रम (i = 0; i < 5; i++) अणु
		अगर (ucontrol->value.iec958.status[i] != chip->aes_bits[i]) अणु
			अगर (chip->mgr->is_hr_stereo)
				hr222_iec958_update_byte(chip, i,
					ucontrol->value.iec958.status[i]);
			अन्यथा
				pcxhr_iec958_update_byte(chip, i,
					ucontrol->value.iec958.status[i]);
			changed = 1;
		पूर्ण
	पूर्ण
	mutex_unlock(&chip->mgr->mixer_mutex);
	वापस changed;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new pcxhr_control_playback_iec958_mask = अणु
	.access =	SNDRV_CTL_ELEM_ACCESS_READ,
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		SNDRV_CTL_NAME_IEC958("",PLAYBACK,MASK),
	.info =		pcxhr_iec958_info,
	.get =		pcxhr_iec958_mask_get
पूर्ण;
अटल स्थिर काष्ठा snd_kcontrol_new pcxhr_control_playback_iec958 = अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =         SNDRV_CTL_NAME_IEC958("",PLAYBACK,DEFAULT),
	.info =         pcxhr_iec958_info,
	.get =          pcxhr_iec958_get,
	.put =          pcxhr_iec958_put,
	.निजी_value = 0 /* playback */
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new pcxhr_control_capture_iec958_mask = अणु
	.access =	SNDRV_CTL_ELEM_ACCESS_READ,
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		SNDRV_CTL_NAME_IEC958("",CAPTURE,MASK),
	.info =		pcxhr_iec958_info,
	.get =		pcxhr_iec958_mask_get
पूर्ण;
अटल स्थिर काष्ठा snd_kcontrol_new pcxhr_control_capture_iec958 = अणु
	.access =	SNDRV_CTL_ELEM_ACCESS_READ,
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =         SNDRV_CTL_NAME_IEC958("",CAPTURE,DEFAULT),
	.info =         pcxhr_iec958_info,
	.get =          pcxhr_iec958_get,
	.निजी_value = 1 /* capture */
पूर्ण;

अटल व्योम pcxhr_init_audio_levels(काष्ठा snd_pcxhr *chip)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 2; i++) अणु
		अगर (chip->nb_streams_play) अणु
			पूर्णांक j;
			/* at boot समय the digital volumes are unmuted 0dB */
			क्रम (j = 0; j < PCXHR_PLAYBACK_STREAMS; j++) अणु
				chip->digital_playback_active[j][i] = 1;
				chip->digital_playback_volume[j][i] =
					PCXHR_DIGITAL_ZERO_LEVEL;
			पूर्ण
			/* after boot, only two bits are set on the uer
			 * पूर्णांकerface
			 */
			chip->aes_bits[0] = (IEC958_AES0_PROFESSIONAL |
					     IEC958_AES0_PRO_FS_48000);
#अगर_घोषित CONFIG_SND_DEBUG
			/* analog volumes क्रम playback
			 * (is LEVEL_MIN after boot)
			 */
			chip->analog_playback_active[i] = 1;
			अगर (chip->mgr->is_hr_stereo)
				chip->analog_playback_volume[i] =
					HR222_LINE_PLAYBACK_ZERO_LEVEL;
			अन्यथा अणु
				chip->analog_playback_volume[i] =
					PCXHR_LINE_PLAYBACK_ZERO_LEVEL;
				pcxhr_update_analog_audio_level(chip, 0, i);
			पूर्ण
#पूर्ण_अगर
			/* stereo cards need to be initialised after boot */
			अगर (chip->mgr->is_hr_stereo)
				hr222_update_analog_audio_level(chip, 0, i);
		पूर्ण
		अगर (chip->nb_streams_capt) अणु
			/* at boot समय the digital volumes are unmuted 0dB */
			chip->digital_capture_volume[i] =
				PCXHR_DIGITAL_ZERO_LEVEL;
			chip->analog_capture_active = 1;
#अगर_घोषित CONFIG_SND_DEBUG
			/* analog volumes क्रम playback
			 * (is LEVEL_MIN after boot)
			 */
			अगर (chip->mgr->is_hr_stereo)
				chip->analog_capture_volume[i] =
					HR222_LINE_CAPTURE_ZERO_LEVEL;
			अन्यथा अणु
				chip->analog_capture_volume[i] =
					PCXHR_LINE_CAPTURE_ZERO_LEVEL;
				pcxhr_update_analog_audio_level(chip, 1, i);
			पूर्ण
#पूर्ण_अगर
			/* stereo cards need to be initialised after boot */
			अगर (chip->mgr->is_hr_stereo)
				hr222_update_analog_audio_level(chip, 1, i);
		पूर्ण
	पूर्ण

	वापस;
पूर्ण


पूर्णांक pcxhr_create_mixer(काष्ठा pcxhr_mgr *mgr)
अणु
	काष्ठा snd_pcxhr *chip;
	पूर्णांक err, i;

	mutex_init(&mgr->mixer_mutex); /* can be in another place */

	क्रम (i = 0; i < mgr->num_cards; i++) अणु
		काष्ठा snd_kcontrol_new temp;
		chip = mgr->chip[i];

		अगर (chip->nb_streams_play) अणु
			/* analog output level control */
			temp = pcxhr_control_analog_level;
			temp.name = "Master Playback Volume";
			temp.निजी_value = 0; /* playback */
			अगर (mgr->is_hr_stereo)
				temp.tlv.p = db_scale_a_hr222_playback;
			अन्यथा
				temp.tlv.p = db_scale_analog_playback;
			err = snd_ctl_add(chip->card,
					  snd_ctl_new1(&temp, chip));
			अगर (err < 0)
				वापस err;

			/* output mute controls */
			err = snd_ctl_add(chip->card,
				snd_ctl_new1(&pcxhr_control_output_चयन,
					     chip));
			अगर (err < 0)
				वापस err;

			temp = snd_pcxhr_pcm_vol;
			temp.name = "PCM Playback Volume";
			temp.count = PCXHR_PLAYBACK_STREAMS;
			temp.निजी_value = 0; /* playback */
			err = snd_ctl_add(chip->card,
					  snd_ctl_new1(&temp, chip));
			अगर (err < 0)
				वापस err;

			err = snd_ctl_add(chip->card,
				snd_ctl_new1(&pcxhr_control_pcm_चयन, chip));
			अगर (err < 0)
				वापस err;

			/* IEC958 controls */
			err = snd_ctl_add(chip->card,
				snd_ctl_new1(&pcxhr_control_playback_iec958_mask,
					     chip));
			अगर (err < 0)
				वापस err;

			err = snd_ctl_add(chip->card,
				snd_ctl_new1(&pcxhr_control_playback_iec958,
					     chip));
			अगर (err < 0)
				वापस err;
		पूर्ण
		अगर (chip->nb_streams_capt) अणु
			/* analog input level control */
			temp = pcxhr_control_analog_level;
			temp.name = "Line Capture Volume";
			temp.निजी_value = 1; /* capture */
			अगर (mgr->is_hr_stereo)
				temp.tlv.p = db_scale_a_hr222_capture;
			अन्यथा
				temp.tlv.p = db_scale_analog_capture;

			err = snd_ctl_add(chip->card,
					  snd_ctl_new1(&temp, chip));
			अगर (err < 0)
				वापस err;

			temp = snd_pcxhr_pcm_vol;
			temp.name = "PCM Capture Volume";
			temp.count = 1;
			temp.निजी_value = 1; /* capture */

			err = snd_ctl_add(chip->card,
					  snd_ctl_new1(&temp, chip));
			अगर (err < 0)
				वापस err;

			/* Audio source */
			err = snd_ctl_add(chip->card,
				snd_ctl_new1(&pcxhr_control_audio_src, chip));
			अगर (err < 0)
				वापस err;

			/* IEC958 controls */
			err = snd_ctl_add(chip->card,
				snd_ctl_new1(&pcxhr_control_capture_iec958_mask,
					     chip));
			अगर (err < 0)
				वापस err;

			err = snd_ctl_add(chip->card,
				snd_ctl_new1(&pcxhr_control_capture_iec958,
					     chip));
			अगर (err < 0)
				वापस err;

			अगर (mgr->is_hr_stereo) अणु
				err = hr222_add_mic_controls(chip);
				अगर (err < 0)
					वापस err;
			पूर्ण
		पूर्ण
		/* monitoring only अगर playback and capture device available */
		अगर (chip->nb_streams_capt > 0 && chip->nb_streams_play > 0) अणु
			/* monitoring */
			err = snd_ctl_add(chip->card,
				snd_ctl_new1(&pcxhr_control_monitor_vol, chip));
			अगर (err < 0)
				वापस err;

			err = snd_ctl_add(chip->card,
				snd_ctl_new1(&pcxhr_control_monitor_sw, chip));
			अगर (err < 0)
				वापस err;
		पूर्ण

		अगर (i == 0) अणु
			/* घड़ी mode only one control per pcxhr */
			err = snd_ctl_add(chip->card,
				snd_ctl_new1(&pcxhr_control_घड़ी_प्रकारype, mgr));
			अगर (err < 0)
				वापस err;
			/* non standard control used to scan
			 * the बाह्यal घड़ी presence/frequencies
			 */
			err = snd_ctl_add(chip->card,
				snd_ctl_new1(&pcxhr_control_घड़ी_rate, mgr));
			अगर (err < 0)
				वापस err;
		पूर्ण

		/* init values क्रम the mixer data */
		pcxhr_init_audio_levels(chip);
	पूर्ण

	वापस 0;
पूर्ण
