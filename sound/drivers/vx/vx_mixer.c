<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम Digigram VX soundcards
 *
 * Common mixer part
 *
 * Copyright (c) 2002 by Takashi Iwai <tiwai@suse.de>
 */

#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/tlv.h>
#समावेश <sound/vx_core.h>
#समावेश "vx_cmd.h"


/*
 * ग_लिखो a codec data (24bit)
 */
अटल व्योम vx_ग_लिखो_codec_reg(काष्ठा vx_core *chip, पूर्णांक codec, अचिन्हित पूर्णांक data)
अणु
	अगर (snd_BUG_ON(!chip->ops->ग_लिखो_codec))
		वापस;

	अगर (chip->chip_status & VX_STAT_IS_STALE)
		वापस;

	mutex_lock(&chip->lock);
	chip->ops->ग_लिखो_codec(chip, codec, data);
	mutex_unlock(&chip->lock);
पूर्ण

/*
 * Data type used to access the Codec
 */
जोड़ vx_codec_data अणु
	u32 l;
#अगर_घोषित SNDRV_BIG_ENDIAN
	काष्ठा w अणु
		u16 h;
		u16 l;
	पूर्ण w;
	काष्ठा b अणु
		u8 hh;
		u8 mh;
		u8 ml;
		u8 ll;
	पूर्ण b;
#अन्यथा /* LITTLE_ENDIAN */
	काष्ठा w अणु
		u16 l;
		u16 h;
	पूर्ण w;
	काष्ठा b अणु
		u8 ll;
		u8 ml;
		u8 mh;
		u8 hh;
	पूर्ण b;
#पूर्ण_अगर
पूर्ण;

#घोषणा SET_CDC_DATA_SEL(di,s)          ((di).b.mh = (u8) (s))
#घोषणा SET_CDC_DATA_REG(di,r)          ((di).b.ml = (u8) (r))
#घोषणा SET_CDC_DATA_VAL(di,d)          ((di).b.ll = (u8) (d))
#घोषणा SET_CDC_DATA_INIT(di)           ((di).l = 0L, SET_CDC_DATA_SEL(di,XX_CODEC_SELECTOR))

/*
 * set up codec रेजिस्टर and ग_लिखो the value
 * @codec: the codec id, 0 or 1
 * @reg: रेजिस्टर index
 * @val: data value
 */
अटल व्योम vx_set_codec_reg(काष्ठा vx_core *chip, पूर्णांक codec, पूर्णांक reg, पूर्णांक val)
अणु
	जोड़ vx_codec_data data;
	/* DAC control रेजिस्टर */
	SET_CDC_DATA_INIT(data);
	SET_CDC_DATA_REG(data, reg);
	SET_CDC_DATA_VAL(data, val);
	vx_ग_लिखो_codec_reg(chip, codec, data.l);
पूर्ण


/*
 * vx_set_analog_output_level - set the output attenuation level
 * @codec: the output codec, 0 or 1.  (1 क्रम VXP440 only)
 * @left: left output level, 0 = mute
 * @right: right output level
 */
अटल व्योम vx_set_analog_output_level(काष्ठा vx_core *chip, पूर्णांक codec, पूर्णांक left, पूर्णांक right)
अणु
	left  = chip->hw->output_level_max - left;
	right = chip->hw->output_level_max - right;

	अगर (chip->ops->akm_ग_लिखो) अणु
		chip->ops->akm_ग_लिखो(chip, XX_CODEC_LEVEL_LEFT_REGISTER, left);
		chip->ops->akm_ग_लिखो(chip, XX_CODEC_LEVEL_RIGHT_REGISTER, right);
	पूर्ण अन्यथा अणु
		/* convert to attenuation level: 0 = 0dB (max), 0xe3 = -113.5 dB (min) */
		vx_set_codec_reg(chip, codec, XX_CODEC_LEVEL_LEFT_REGISTER, left);
		vx_set_codec_reg(chip, codec, XX_CODEC_LEVEL_RIGHT_REGISTER, right);
	पूर्ण
पूर्ण


/*
 * vx_toggle_dac_mute -  mute/unmute DAC
 * @mute: 0 = unmute, 1 = mute
 */

#घोषणा DAC_ATTEN_MIN	0x08
#घोषणा DAC_ATTEN_MAX	0x38

व्योम vx_toggle_dac_mute(काष्ठा vx_core *chip, पूर्णांक mute)
अणु
	अचिन्हित पूर्णांक i;
	क्रम (i = 0; i < chip->hw->num_codecs; i++) अणु
		अगर (chip->ops->akm_ग_लिखो)
			chip->ops->akm_ग_लिखो(chip, XX_CODEC_DAC_CONTROL_REGISTER, mute); /* XXX */
		अन्यथा
			vx_set_codec_reg(chip, i, XX_CODEC_DAC_CONTROL_REGISTER,
					 mute ? DAC_ATTEN_MAX : DAC_ATTEN_MIN);
	पूर्ण
पूर्ण

/*
 * vx_reset_codec - reset and initialize the codecs
 */
व्योम vx_reset_codec(काष्ठा vx_core *chip, पूर्णांक cold_reset)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक port = chip->type >= VX_TYPE_VXPOCKET ? 0x75 : 0x65;

	chip->ops->reset_codec(chip);

	/* AKM codecs should be initialized in reset_codec callback */
	अगर (! chip->ops->akm_ग_लिखो) अणु
		/* initialize old codecs */
		क्रम (i = 0; i < chip->hw->num_codecs; i++) अणु
			/* DAC control रेजिस्टर (change level when zero crossing + mute) */
			vx_set_codec_reg(chip, i, XX_CODEC_DAC_CONTROL_REGISTER, DAC_ATTEN_MAX);
			/* ADC control रेजिस्टर */
			vx_set_codec_reg(chip, i, XX_CODEC_ADC_CONTROL_REGISTER, 0x00);
			/* Port mode रेजिस्टर */
			vx_set_codec_reg(chip, i, XX_CODEC_PORT_MODE_REGISTER, port);
			/* Clock control रेजिस्टर */
			vx_set_codec_reg(chip, i, XX_CODEC_CLOCK_CONTROL_REGISTER, 0x00);
		पूर्ण
	पूर्ण

	/* mute analog output */
	क्रम (i = 0; i < chip->hw->num_codecs; i++) अणु
		chip->output_level[i][0] = 0;
		chip->output_level[i][1] = 0;
		vx_set_analog_output_level(chip, i, 0, 0);
	पूर्ण
पूर्ण

/*
 * change the audio input source
 * @src: the target source (VX_AUDIO_SRC_XXX)
 */
अटल व्योम vx_change_audio_source(काष्ठा vx_core *chip, पूर्णांक src)
अणु
	अगर (chip->chip_status & VX_STAT_IS_STALE)
		वापस;

	mutex_lock(&chip->lock);
	chip->ops->change_audio_source(chip, src);
	mutex_unlock(&chip->lock);
पूर्ण


/*
 * change the audio source अगर necessary and possible
 * वापसs 1 अगर the source is actually changed.
 */
पूर्णांक vx_sync_audio_source(काष्ठा vx_core *chip)
अणु
	अगर (chip->audio_source_target == chip->audio_source ||
	    chip->pcm_running)
		वापस 0;
	vx_change_audio_source(chip, chip->audio_source_target);
	chip->audio_source = chip->audio_source_target;
	वापस 1;
पूर्ण


/*
 * audio level, mute, monitoring
 */
काष्ठा vx_audio_level अणु
	अचिन्हित पूर्णांक has_level: 1;
	अचिन्हित पूर्णांक has_monitor_level: 1;
	अचिन्हित पूर्णांक has_mute: 1;
	अचिन्हित पूर्णांक has_monitor_mute: 1;
	अचिन्हित पूर्णांक mute;
	अचिन्हित पूर्णांक monitor_mute;
	लघु level;
	लघु monitor_level;
पूर्ण;

अटल पूर्णांक vx_adjust_audio_level(काष्ठा vx_core *chip, पूर्णांक audio, पूर्णांक capture,
				 काष्ठा vx_audio_level *info)
अणु
	काष्ठा vx_rmh rmh;

	अगर (chip->chip_status & VX_STAT_IS_STALE)
		वापस -EBUSY;

        vx_init_rmh(&rmh, CMD_AUDIO_LEVEL_ADJUST);
	अगर (capture)
		rmh.Cmd[0] |= COMMAND_RECORD_MASK;
	/* Add Audio IO mask */
	rmh.Cmd[1] = 1 << audio;
	rmh.Cmd[2] = 0;
	अगर (info->has_level) अणु
		rmh.Cmd[0] |=  VALID_AUDIO_IO_DIGITAL_LEVEL;
		rmh.Cmd[2] |= info->level;
        पूर्ण
	अगर (info->has_monitor_level) अणु
		rmh.Cmd[0] |=  VALID_AUDIO_IO_MONITORING_LEVEL;
		rmh.Cmd[2] |= ((अचिन्हित पूर्णांक)info->monitor_level << 10);
        पूर्ण
	अगर (info->has_mute) अणु 
		rmh.Cmd[0] |= VALID_AUDIO_IO_MUTE_LEVEL;
		अगर (info->mute)
			rmh.Cmd[2] |= AUDIO_IO_HAS_MUTE_LEVEL;
	पूर्ण
	अगर (info->has_monitor_mute) अणु
		/* validate flag क्रम M2 at least to unmute it */ 
		rmh.Cmd[0] |=  VALID_AUDIO_IO_MUTE_MONITORING_1 | VALID_AUDIO_IO_MUTE_MONITORING_2;
		अगर (info->monitor_mute)
			rmh.Cmd[2] |= AUDIO_IO_HAS_MUTE_MONITORING_1;
	पूर्ण

	वापस vx_send_msg(chip, &rmh);
पूर्ण

    
#अगर 0 // not used
अटल पूर्णांक vx_पढ़ो_audio_level(काष्ठा vx_core *chip, पूर्णांक audio, पूर्णांक capture,
			       काष्ठा vx_audio_level *info)
अणु
	पूर्णांक err;
	काष्ठा vx_rmh rmh;

	स_रखो(info, 0, माप(*info));
        vx_init_rmh(&rmh, CMD_GET_AUDIO_LEVELS);
	अगर (capture)
		rmh.Cmd[0] |= COMMAND_RECORD_MASK;
	/* Add Audio IO mask */
	rmh.Cmd[1] = 1 << audio;
	err = vx_send_msg(chip, &rmh);
	अगर (err < 0)
		वापस err;
	info.level = rmh.Stat[0] & MASK_DSP_WORD_LEVEL;
	info.monitor_level = (rmh.Stat[0] >> 10) & MASK_DSP_WORD_LEVEL;
	info.mute = (rmh.Stat[i] & AUDIO_IO_HAS_MUTE_LEVEL) ? 1 : 0;
	info.monitor_mute = (rmh.Stat[i] & AUDIO_IO_HAS_MUTE_MONITORING_1) ? 1 : 0;
	वापस 0;
पूर्ण
#पूर्ण_अगर // not used

/*
 * set the monitoring level and mute state of the given audio
 * no more अटल, because must be called from vx_pcm to demute monitoring
 */
पूर्णांक vx_set_monitor_level(काष्ठा vx_core *chip, पूर्णांक audio, पूर्णांक level, पूर्णांक active)
अणु
	काष्ठा vx_audio_level info;

	स_रखो(&info, 0, माप(info));
	info.has_monitor_level = 1;
	info.monitor_level = level;
	info.has_monitor_mute = 1;
	info.monitor_mute = !active;
	chip->audio_monitor[audio] = level;
	chip->audio_monitor_active[audio] = active;
	वापस vx_adjust_audio_level(chip, audio, 0, &info); /* playback only */
पूर्ण


/*
 * set the mute status of the given audio
 */
अटल पूर्णांक vx_set_audio_चयन(काष्ठा vx_core *chip, पूर्णांक audio, पूर्णांक active)
अणु
	काष्ठा vx_audio_level info;

	स_रखो(&info, 0, माप(info));
	info.has_mute = 1;
	info.mute = !active;
	chip->audio_active[audio] = active;
	वापस vx_adjust_audio_level(chip, audio, 0, &info); /* playback only */
पूर्ण

/*
 * set the mute status of the given audio
 */
अटल पूर्णांक vx_set_audio_gain(काष्ठा vx_core *chip, पूर्णांक audio, पूर्णांक capture, पूर्णांक level)
अणु
	काष्ठा vx_audio_level info;

	स_रखो(&info, 0, माप(info));
	info.has_level = 1;
	info.level = level;
	chip->audio_gain[capture][audio] = level;
	वापस vx_adjust_audio_level(chip, audio, capture, &info);
पूर्ण

/*
 * reset all audio levels
 */
अटल व्योम vx_reset_audio_levels(काष्ठा vx_core *chip)
अणु
	अचिन्हित पूर्णांक i, c;
	काष्ठा vx_audio_level info;

	स_रखो(chip->audio_gain, 0, माप(chip->audio_gain));
	स_रखो(chip->audio_active, 0, माप(chip->audio_active));
	स_रखो(chip->audio_monitor, 0, माप(chip->audio_monitor));
	स_रखो(chip->audio_monitor_active, 0, माप(chip->audio_monitor_active));

	क्रम (c = 0; c < 2; c++) अणु
		क्रम (i = 0; i < chip->hw->num_ins * 2; i++) अणु
			स_रखो(&info, 0, माप(info));
			अगर (c == 0) अणु
				info.has_monitor_level = 1;
				info.has_mute = 1;
				info.has_monitor_mute = 1;
			पूर्ण
			info.has_level = 1;
			info.level = CVAL_0DB; /* शेष: 0dB */
			vx_adjust_audio_level(chip, i, c, &info);
			chip->audio_gain[c][i] = CVAL_0DB;
			chip->audio_monitor[i] = CVAL_0DB;
		पूर्ण
	पूर्ण
पूर्ण


/*
 * VU, peak meter record
 */

#घोषणा VU_METER_CHANNELS	2

काष्ठा vx_vu_meter अणु
	पूर्णांक saturated;
	पूर्णांक vu_level;
	पूर्णांक peak_level;
पूर्ण;

/*
 * get the VU and peak meter values
 * @audio: the audio index
 * @capture: 0 = playback, 1 = capture operation
 * @info: the array of vx_vu_meter records (size = 2).
 */
अटल पूर्णांक vx_get_audio_vu_meter(काष्ठा vx_core *chip, पूर्णांक audio, पूर्णांक capture, काष्ठा vx_vu_meter *info)
अणु
	काष्ठा vx_rmh rmh;
	पूर्णांक i, err;

	अगर (chip->chip_status & VX_STAT_IS_STALE)
		वापस -EBUSY;

	vx_init_rmh(&rmh, CMD_AUDIO_VU_PIC_METER);
	rmh.LgStat += 2 * VU_METER_CHANNELS;
	अगर (capture)
		rmh.Cmd[0] |= COMMAND_RECORD_MASK;
    
        /* Add Audio IO mask */
	rmh.Cmd[1] = 0;
	क्रम (i = 0; i < VU_METER_CHANNELS; i++)
		rmh.Cmd[1] |= 1 << (audio + i);
	err = vx_send_msg(chip, &rmh);
	अगर (err < 0)
		वापस err;
	/* Read response */
	क्रम (i = 0; i < 2 * VU_METER_CHANNELS; i +=2) अणु
		info->saturated = (rmh.Stat[0] & (1 << (audio + i))) ? 1 : 0;
		info->vu_level = rmh.Stat[i + 1];
		info->peak_level = rmh.Stat[i + 2];
		info++;
	पूर्ण
	वापस 0;
पूर्ण
   

/*
 * control API entries
 */

/*
 * output level control
 */
अटल पूर्णांक vx_output_level_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा vx_core *chip = snd_kcontrol_chip(kcontrol);
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = chip->hw->output_level_max;
	वापस 0;
पूर्ण

अटल पूर्णांक vx_output_level_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा vx_core *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक codec = kcontrol->id.index;
	mutex_lock(&chip->mixer_mutex);
	ucontrol->value.पूर्णांकeger.value[0] = chip->output_level[codec][0];
	ucontrol->value.पूर्णांकeger.value[1] = chip->output_level[codec][1];
	mutex_unlock(&chip->mixer_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक vx_output_level_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा vx_core *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक codec = kcontrol->id.index;
	अचिन्हित पूर्णांक val[2], vmax;

	vmax = chip->hw->output_level_max;
	val[0] = ucontrol->value.पूर्णांकeger.value[0];
	val[1] = ucontrol->value.पूर्णांकeger.value[1];
	अगर (val[0] > vmax || val[1] > vmax)
		वापस -EINVAL;
	mutex_lock(&chip->mixer_mutex);
	अगर (val[0] != chip->output_level[codec][0] ||
	    val[1] != chip->output_level[codec][1]) अणु
		vx_set_analog_output_level(chip, codec, val[0], val[1]);
		chip->output_level[codec][0] = val[0];
		chip->output_level[codec][1] = val[1];
		mutex_unlock(&chip->mixer_mutex);
		वापस 1;
	पूर्ण
	mutex_unlock(&chip->mixer_mutex);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new vx_control_output_level = अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_MIXER,
	.access =	(SNDRV_CTL_ELEM_ACCESS_READWRITE |
			 SNDRV_CTL_ELEM_ACCESS_TLV_READ),
	.name =		"Master Playback Volume",
	.info =		vx_output_level_info,
	.get =		vx_output_level_get,
	.put =		vx_output_level_put,
	/* tlv will be filled later */
पूर्ण;

/*
 * audio source select
 */
अटल पूर्णांक vx_audio_src_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts_mic[3] = अणु
		"Digital", "Line", "Mic"
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर texts_vx2[2] = अणु
		"Digital", "Analog"
	पूर्ण;
	काष्ठा vx_core *chip = snd_kcontrol_chip(kcontrol);

	अगर (chip->type >= VX_TYPE_VXPOCKET)
		वापस snd_ctl_क्रमागत_info(uinfo, 1, 3, texts_mic);
	अन्यथा
		वापस snd_ctl_क्रमागत_info(uinfo, 1, 2, texts_vx2);
पूर्ण

अटल पूर्णांक vx_audio_src_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा vx_core *chip = snd_kcontrol_chip(kcontrol);
	ucontrol->value.क्रमागतerated.item[0] = chip->audio_source_target;
	वापस 0;
पूर्ण

अटल पूर्णांक vx_audio_src_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा vx_core *chip = snd_kcontrol_chip(kcontrol);

	अगर (chip->type >= VX_TYPE_VXPOCKET) अणु
		अगर (ucontrol->value.क्रमागतerated.item[0] > 2)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		अगर (ucontrol->value.क्रमागतerated.item[0] > 1)
			वापस -EINVAL;
	पूर्ण
	mutex_lock(&chip->mixer_mutex);
	अगर (chip->audio_source_target != ucontrol->value.क्रमागतerated.item[0]) अणु
		chip->audio_source_target = ucontrol->value.क्रमागतerated.item[0];
		vx_sync_audio_source(chip);
		mutex_unlock(&chip->mixer_mutex);
		वापस 1;
	पूर्ण
	mutex_unlock(&chip->mixer_mutex);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new vx_control_audio_src = अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_MIXER,
	.name =		"Capture Source",
	.info =		vx_audio_src_info,
	.get =		vx_audio_src_get,
	.put =		vx_audio_src_put,
पूर्ण;

/*
 * घड़ी mode selection
 */
अटल पूर्णांक vx_घड़ी_mode_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[3] = अणु
		"Auto", "Internal", "External"
	पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 3, texts);
पूर्ण

अटल पूर्णांक vx_घड़ी_mode_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा vx_core *chip = snd_kcontrol_chip(kcontrol);
	ucontrol->value.क्रमागतerated.item[0] = chip->घड़ी_mode;
	वापस 0;
पूर्ण

अटल पूर्णांक vx_घड़ी_mode_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा vx_core *chip = snd_kcontrol_chip(kcontrol);

	अगर (ucontrol->value.क्रमागतerated.item[0] > 2)
		वापस -EINVAL;
	mutex_lock(&chip->mixer_mutex);
	अगर (chip->घड़ी_mode != ucontrol->value.क्रमागतerated.item[0]) अणु
		chip->घड़ी_mode = ucontrol->value.क्रमागतerated.item[0];
		vx_set_घड़ी(chip, chip->freq);
		mutex_unlock(&chip->mixer_mutex);
		वापस 1;
	पूर्ण
	mutex_unlock(&chip->mixer_mutex);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new vx_control_घड़ी_mode = अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_MIXER,
	.name =		"Clock Mode",
	.info =		vx_घड़ी_mode_info,
	.get =		vx_घड़ी_mode_get,
	.put =		vx_घड़ी_mode_put,
पूर्ण;

/*
 * Audio Gain
 */
अटल पूर्णांक vx_audio_gain_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = CVAL_MAX;
	वापस 0;
पूर्ण

अटल पूर्णांक vx_audio_gain_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा vx_core *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक audio = kcontrol->निजी_value & 0xff;
	पूर्णांक capture = (kcontrol->निजी_value >> 8) & 1;

	mutex_lock(&chip->mixer_mutex);
	ucontrol->value.पूर्णांकeger.value[0] = chip->audio_gain[capture][audio];
	ucontrol->value.पूर्णांकeger.value[1] = chip->audio_gain[capture][audio+1];
	mutex_unlock(&chip->mixer_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक vx_audio_gain_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा vx_core *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक audio = kcontrol->निजी_value & 0xff;
	पूर्णांक capture = (kcontrol->निजी_value >> 8) & 1;
	अचिन्हित पूर्णांक val[2];

	val[0] = ucontrol->value.पूर्णांकeger.value[0];
	val[1] = ucontrol->value.पूर्णांकeger.value[1];
	अगर (val[0] > CVAL_MAX || val[1] > CVAL_MAX)
		वापस -EINVAL;
	mutex_lock(&chip->mixer_mutex);
	अगर (val[0] != chip->audio_gain[capture][audio] ||
	    val[1] != chip->audio_gain[capture][audio+1]) अणु
		vx_set_audio_gain(chip, audio, capture, val[0]);
		vx_set_audio_gain(chip, audio+1, capture, val[1]);
		mutex_unlock(&chip->mixer_mutex);
		वापस 1;
	पूर्ण
	mutex_unlock(&chip->mixer_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक vx_audio_monitor_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा vx_core *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक audio = kcontrol->निजी_value & 0xff;

	mutex_lock(&chip->mixer_mutex);
	ucontrol->value.पूर्णांकeger.value[0] = chip->audio_monitor[audio];
	ucontrol->value.पूर्णांकeger.value[1] = chip->audio_monitor[audio+1];
	mutex_unlock(&chip->mixer_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक vx_audio_monitor_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा vx_core *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक audio = kcontrol->निजी_value & 0xff;
	अचिन्हित पूर्णांक val[2];

	val[0] = ucontrol->value.पूर्णांकeger.value[0];
	val[1] = ucontrol->value.पूर्णांकeger.value[1];
	अगर (val[0] > CVAL_MAX || val[1] > CVAL_MAX)
		वापस -EINVAL;

	mutex_lock(&chip->mixer_mutex);
	अगर (val[0] != chip->audio_monitor[audio] ||
	    val[1] != chip->audio_monitor[audio+1]) अणु
		vx_set_monitor_level(chip, audio, val[0],
				     chip->audio_monitor_active[audio]);
		vx_set_monitor_level(chip, audio+1, val[1],
				     chip->audio_monitor_active[audio+1]);
		mutex_unlock(&chip->mixer_mutex);
		वापस 1;
	पूर्ण
	mutex_unlock(&chip->mixer_mutex);
	वापस 0;
पूर्ण

#घोषणा vx_audio_sw_info	snd_ctl_boolean_stereo_info

अटल पूर्णांक vx_audio_sw_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा vx_core *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक audio = kcontrol->निजी_value & 0xff;

	mutex_lock(&chip->mixer_mutex);
	ucontrol->value.पूर्णांकeger.value[0] = chip->audio_active[audio];
	ucontrol->value.पूर्णांकeger.value[1] = chip->audio_active[audio+1];
	mutex_unlock(&chip->mixer_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक vx_audio_sw_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा vx_core *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक audio = kcontrol->निजी_value & 0xff;

	mutex_lock(&chip->mixer_mutex);
	अगर (ucontrol->value.पूर्णांकeger.value[0] != chip->audio_active[audio] ||
	    ucontrol->value.पूर्णांकeger.value[1] != chip->audio_active[audio+1]) अणु
		vx_set_audio_चयन(chip, audio,
				    !!ucontrol->value.पूर्णांकeger.value[0]);
		vx_set_audio_चयन(chip, audio+1,
				    !!ucontrol->value.पूर्णांकeger.value[1]);
		mutex_unlock(&chip->mixer_mutex);
		वापस 1;
	पूर्ण
	mutex_unlock(&chip->mixer_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक vx_monitor_sw_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा vx_core *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक audio = kcontrol->निजी_value & 0xff;

	mutex_lock(&chip->mixer_mutex);
	ucontrol->value.पूर्णांकeger.value[0] = chip->audio_monitor_active[audio];
	ucontrol->value.पूर्णांकeger.value[1] = chip->audio_monitor_active[audio+1];
	mutex_unlock(&chip->mixer_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक vx_monitor_sw_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा vx_core *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक audio = kcontrol->निजी_value & 0xff;

	mutex_lock(&chip->mixer_mutex);
	अगर (ucontrol->value.पूर्णांकeger.value[0] != chip->audio_monitor_active[audio] ||
	    ucontrol->value.पूर्णांकeger.value[1] != chip->audio_monitor_active[audio+1]) अणु
		vx_set_monitor_level(chip, audio, chip->audio_monitor[audio],
				     !!ucontrol->value.पूर्णांकeger.value[0]);
		vx_set_monitor_level(chip, audio+1, chip->audio_monitor[audio+1],
				     !!ucontrol->value.पूर्णांकeger.value[1]);
		mutex_unlock(&chip->mixer_mutex);
		वापस 1;
	पूर्ण
	mutex_unlock(&chip->mixer_mutex);
	वापस 0;
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_audio_gain, -10975, 25, 0);

अटल स्थिर काष्ठा snd_kcontrol_new vx_control_audio_gain = अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_MIXER,
	.access =	(SNDRV_CTL_ELEM_ACCESS_READWRITE |
			 SNDRV_CTL_ELEM_ACCESS_TLV_READ),
	/* name will be filled later */
	.info =         vx_audio_gain_info,
	.get =          vx_audio_gain_get,
	.put =          vx_audio_gain_put,
	.tlv = अणु .p = db_scale_audio_gain पूर्ण,
पूर्ण;
अटल स्थिर काष्ठा snd_kcontrol_new vx_control_output_चयन = अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_MIXER,
	.name =         "PCM Playback Switch",
	.info =         vx_audio_sw_info,
	.get =          vx_audio_sw_get,
	.put =          vx_audio_sw_put
पूर्ण;
अटल स्थिर काष्ठा snd_kcontrol_new vx_control_monitor_gain = अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_MIXER,
	.name =         "Monitoring Volume",
	.access =	(SNDRV_CTL_ELEM_ACCESS_READWRITE |
			 SNDRV_CTL_ELEM_ACCESS_TLV_READ),
	.info =         vx_audio_gain_info,	/* shared */
	.get =          vx_audio_monitor_get,
	.put =          vx_audio_monitor_put,
	.tlv = अणु .p = db_scale_audio_gain पूर्ण,
पूर्ण;
अटल स्थिर काष्ठा snd_kcontrol_new vx_control_monitor_चयन = अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_MIXER,
	.name =         "Monitoring Switch",
	.info =         vx_audio_sw_info,	/* shared */
	.get =          vx_monitor_sw_get,
	.put =          vx_monitor_sw_put
पूर्ण;


/*
 * IEC958 status bits
 */
अटल पूर्णांक vx_iec958_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक vx_iec958_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा vx_core *chip = snd_kcontrol_chip(kcontrol);

	mutex_lock(&chip->mixer_mutex);
	ucontrol->value.iec958.status[0] = (chip->uer_bits >> 0) & 0xff;
	ucontrol->value.iec958.status[1] = (chip->uer_bits >> 8) & 0xff;
	ucontrol->value.iec958.status[2] = (chip->uer_bits >> 16) & 0xff;
	ucontrol->value.iec958.status[3] = (chip->uer_bits >> 24) & 0xff;
	mutex_unlock(&chip->mixer_mutex);
        वापस 0;
पूर्ण

अटल पूर्णांक vx_iec958_mask_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.iec958.status[0] = 0xff;
	ucontrol->value.iec958.status[1] = 0xff;
	ucontrol->value.iec958.status[2] = 0xff;
	ucontrol->value.iec958.status[3] = 0xff;
        वापस 0;
पूर्ण

अटल पूर्णांक vx_iec958_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा vx_core *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक val;

	val = (ucontrol->value.iec958.status[0] << 0) |
	      (ucontrol->value.iec958.status[1] << 8) |
	      (ucontrol->value.iec958.status[2] << 16) |
	      (ucontrol->value.iec958.status[3] << 24);
	mutex_lock(&chip->mixer_mutex);
	अगर (chip->uer_bits != val) अणु
		chip->uer_bits = val;
		vx_set_iec958_status(chip, val);
		mutex_unlock(&chip->mixer_mutex);
		वापस 1;
	पूर्ण
	mutex_unlock(&chip->mixer_mutex);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new vx_control_iec958_mask = अणु
	.access =	SNDRV_CTL_ELEM_ACCESS_READ,
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		SNDRV_CTL_NAME_IEC958("",PLAYBACK,MASK),
	.info =		vx_iec958_info,	/* shared */
	.get =		vx_iec958_mask_get,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new vx_control_iec958 = अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =         SNDRV_CTL_NAME_IEC958("",PLAYBACK,DEFAULT),
	.info =         vx_iec958_info,
	.get =          vx_iec958_get,
	.put =          vx_iec958_put
पूर्ण;


/*
 * VU meter
 */

#घोषणा METER_MAX	0xff
#घोषणा METER_SHIFT	16

अटल पूर्णांक vx_vu_meter_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = METER_MAX;
	वापस 0;
पूर्ण

अटल पूर्णांक vx_vu_meter_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा vx_core *chip = snd_kcontrol_chip(kcontrol);
	काष्ठा vx_vu_meter meter[2];
	पूर्णांक audio = kcontrol->निजी_value & 0xff;
	पूर्णांक capture = (kcontrol->निजी_value >> 8) & 1;

	vx_get_audio_vu_meter(chip, audio, capture, meter);
	ucontrol->value.पूर्णांकeger.value[0] = meter[0].vu_level >> METER_SHIFT;
	ucontrol->value.पूर्णांकeger.value[1] = meter[1].vu_level >> METER_SHIFT;
	वापस 0;
पूर्ण

अटल पूर्णांक vx_peak_meter_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा vx_core *chip = snd_kcontrol_chip(kcontrol);
	काष्ठा vx_vu_meter meter[2];
	पूर्णांक audio = kcontrol->निजी_value & 0xff;
	पूर्णांक capture = (kcontrol->निजी_value >> 8) & 1;

	vx_get_audio_vu_meter(chip, audio, capture, meter);
	ucontrol->value.पूर्णांकeger.value[0] = meter[0].peak_level >> METER_SHIFT;
	ucontrol->value.पूर्णांकeger.value[1] = meter[1].peak_level >> METER_SHIFT;
	वापस 0;
पूर्ण

#घोषणा vx_saturation_info	snd_ctl_boolean_stereo_info

अटल पूर्णांक vx_saturation_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा vx_core *chip = snd_kcontrol_chip(kcontrol);
	काष्ठा vx_vu_meter meter[2];
	पूर्णांक audio = kcontrol->निजी_value & 0xff;

	vx_get_audio_vu_meter(chip, audio, 1, meter); /* capture only */
	ucontrol->value.पूर्णांकeger.value[0] = meter[0].saturated;
	ucontrol->value.पूर्णांकeger.value[1] = meter[1].saturated;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new vx_control_vu_meter = अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_MIXER,
	.access =	SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_VOLATILE,
	/* name will be filled later */
	.info =		vx_vu_meter_info,
	.get =		vx_vu_meter_get,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new vx_control_peak_meter = अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_MIXER,
	.access =	SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_VOLATILE,
	/* name will be filled later */
	.info =		vx_vu_meter_info,	/* shared */
	.get =		vx_peak_meter_get,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new vx_control_saturation = अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_MIXER,
	.name =		"Input Saturation",
	.access =	SNDRV_CTL_ELEM_ACCESS_READ | SNDRV_CTL_ELEM_ACCESS_VOLATILE,
	.info =		vx_saturation_info,
	.get =		vx_saturation_get,
पूर्ण;



/*
 *
 */

पूर्णांक snd_vx_mixer_new(काष्ठा vx_core *chip)
अणु
	अचिन्हित पूर्णांक i, c;
	पूर्णांक err;
	काष्ठा snd_kcontrol_new temp;
	काष्ठा snd_card *card = chip->card;
	अक्षर name[32];

	म_नकल(card->mixername, card->driver);

	/* output level controls */
	क्रम (i = 0; i < chip->hw->num_outs; i++) अणु
		temp = vx_control_output_level;
		temp.index = i;
		temp.tlv.p = chip->hw->output_level_db_scale;
		अगर ((err = snd_ctl_add(card, snd_ctl_new1(&temp, chip))) < 0)
			वापस err;
	पूर्ण

	/* PCM volumes, चयनes, monitoring */
	क्रम (i = 0; i < chip->hw->num_outs; i++) अणु
		पूर्णांक val = i * 2;
		temp = vx_control_audio_gain;
		temp.index = i;
		temp.name = "PCM Playback Volume";
		temp.निजी_value = val;
		अगर ((err = snd_ctl_add(card, snd_ctl_new1(&temp, chip))) < 0)
			वापस err;
		temp = vx_control_output_चयन;
		temp.index = i;
		temp.निजी_value = val;
		अगर ((err = snd_ctl_add(card, snd_ctl_new1(&temp, chip))) < 0)
			वापस err;
		temp = vx_control_monitor_gain;
		temp.index = i;
		temp.निजी_value = val;
		अगर ((err = snd_ctl_add(card, snd_ctl_new1(&temp, chip))) < 0)
			वापस err;
		temp = vx_control_monitor_चयन;
		temp.index = i;
		temp.निजी_value = val;
		अगर ((err = snd_ctl_add(card, snd_ctl_new1(&temp, chip))) < 0)
			वापस err;
	पूर्ण
	क्रम (i = 0; i < chip->hw->num_outs; i++) अणु
		temp = vx_control_audio_gain;
		temp.index = i;
		temp.name = "PCM Capture Volume";
		temp.निजी_value = (i * 2) | (1 << 8);
		अगर ((err = snd_ctl_add(card, snd_ctl_new1(&temp, chip))) < 0)
			वापस err;
	पूर्ण

	/* Audio source */
	अगर ((err = snd_ctl_add(card, snd_ctl_new1(&vx_control_audio_src, chip))) < 0)
		वापस err;
	/* घड़ी mode */
	अगर ((err = snd_ctl_add(card, snd_ctl_new1(&vx_control_घड़ी_mode, chip))) < 0)
		वापस err;
	/* IEC958 controls */
	अगर ((err = snd_ctl_add(card, snd_ctl_new1(&vx_control_iec958_mask, chip))) < 0)
		वापस err;
	अगर ((err = snd_ctl_add(card, snd_ctl_new1(&vx_control_iec958, chip))) < 0)
		वापस err;
	/* VU, peak, saturation meters */
	क्रम (c = 0; c < 2; c++) अणु
		अटल स्थिर अक्षर * स्थिर dir[2] = अणु "Output", "Input" पूर्ण;
		क्रम (i = 0; i < chip->hw->num_ins; i++) अणु
			पूर्णांक val = (i * 2) | (c << 8);
			अगर (c == 1) अणु
				temp = vx_control_saturation;
				temp.index = i;
				temp.निजी_value = val;
				अगर ((err = snd_ctl_add(card, snd_ctl_new1(&temp, chip))) < 0)
					वापस err;
			पूर्ण
			प्र_लिखो(name, "%s VU Meter", dir[c]);
			temp = vx_control_vu_meter;
			temp.index = i;
			temp.name = name;
			temp.निजी_value = val;
			अगर ((err = snd_ctl_add(card, snd_ctl_new1(&temp, chip))) < 0)
				वापस err;
			प्र_लिखो(name, "%s Peak Meter", dir[c]);
			temp = vx_control_peak_meter;
			temp.index = i;
			temp.name = name;
			temp.निजी_value = val;
			अगर ((err = snd_ctl_add(card, snd_ctl_new1(&temp, chip))) < 0)
				वापस err;
		पूर्ण
	पूर्ण
	vx_reset_audio_levels(chip);
	वापस 0;
पूर्ण
