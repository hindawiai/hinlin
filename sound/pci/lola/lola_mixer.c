<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Support क्रम Digigram Lola PCI-e boards
 *
 *  Copyright (c) 2011 Takashi Iwai <tiwai@suse.de>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/पन.स>
#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/pcm.h>
#समावेश <sound/tlv.h>
#समावेश "lola.h"

अटल पूर्णांक lola_init_pin(काष्ठा lola *chip, काष्ठा lola_pin *pin,
			 पूर्णांक dir, पूर्णांक nid)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक err;

	pin->nid = nid;
	err = lola_पढ़ो_param(chip, nid, LOLA_PAR_AUDIO_WIDGET_CAP, &val);
	अगर (err < 0) अणु
		dev_err(chip->card->dev, "Can't read wcaps for 0x%x\n", nid);
		वापस err;
	पूर्ण
	val &= 0x00f00fff; /* test TYPE and bits 0..11 */
	अगर (val == 0x00400200)    /* Type = 4, Digital = 1 */
		pin->is_analog = false;
	अन्यथा अगर (val == 0x0040000a && dir == CAPT) /* Dig=0, InAmp/ovrd */
		pin->is_analog = true;
	अन्यथा अगर (val == 0x0040000c && dir == PLAY) /* Dig=0, OutAmp/ovrd */
		pin->is_analog = true;
	अन्यथा अणु
		dev_err(chip->card->dev, "Invalid wcaps 0x%x for 0x%x\n", val, nid);
		वापस -EINVAL;
	पूर्ण

	/* analog parameters only following, so जारी in हाल of Digital pin
	 */
	अगर (!pin->is_analog)
		वापस 0;

	अगर (dir == PLAY)
		err = lola_पढ़ो_param(chip, nid, LOLA_PAR_AMP_OUT_CAP, &val);
	अन्यथा
		err = lola_पढ़ो_param(chip, nid, LOLA_PAR_AMP_IN_CAP, &val);
	अगर (err < 0) अणु
		dev_err(chip->card->dev, "Can't read AMP-caps for 0x%x\n", nid);
		वापस err;
	पूर्ण

	pin->amp_mute = LOLA_AMP_MUTE_CAPABLE(val);
	pin->amp_step_size = LOLA_AMP_STEP_SIZE(val);
	pin->amp_num_steps = LOLA_AMP_NUM_STEPS(val);
	अगर (pin->amp_num_steps) अणु
		/* zero as mute state */
		pin->amp_num_steps++;
		pin->amp_step_size++;
	पूर्ण
	pin->amp_offset = LOLA_AMP_OFFSET(val);

	err = lola_codec_पढ़ो(chip, nid, LOLA_VERB_GET_MAX_LEVEL, 0, 0, &val,
			      शून्य);
	अगर (err < 0) अणु
		dev_err(chip->card->dev, "Can't get MAX_LEVEL 0x%x\n", nid);
		वापस err;
	पूर्ण
	pin->max_level = val & 0x3ff;   /* 10 bits */

	pin->config_शेष_reg = 0;
	pin->fixed_gain_list_len = 0;
	pin->cur_gain_step = 0;

	वापस 0;
पूर्ण

पूर्णांक lola_init_pins(काष्ठा lola *chip, पूर्णांक dir, पूर्णांक *nidp)
अणु
	पूर्णांक i, err, nid;
	nid = *nidp;
	क्रम (i = 0; i < chip->pin[dir].num_pins; i++, nid++) अणु
		err = lola_init_pin(chip, &chip->pin[dir].pins[i], dir, nid);
		अगर (err < 0)
			वापस err;
		अगर (chip->pin[dir].pins[i].is_analog)
			chip->pin[dir].num_analog_pins++;
	पूर्ण
	*nidp = nid;
	वापस 0;
पूर्ण

व्योम lola_मुक्त_mixer(काष्ठा lola *chip)
अणु
	vमुक्त(chip->mixer.array_saved);
पूर्ण

पूर्णांक lola_init_mixer_widget(काष्ठा lola *chip, पूर्णांक nid)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक err;

	err = lola_पढ़ो_param(chip, nid, LOLA_PAR_AUDIO_WIDGET_CAP, &val);
	अगर (err < 0) अणु
		dev_err(chip->card->dev, "Can't read wcaps for 0x%x\n", nid);
		वापस err;
	पूर्ण

	अगर ((val & 0xfff00000) != 0x02f00000) अणु /* test SubType and Type */
		dev_dbg(chip->card->dev, "No valid mixer widget\n");
		वापस 0;
	पूर्ण

	chip->mixer.nid = nid;
	chip->mixer.caps = val;
	chip->mixer.array = (काष्ठा lola_mixer_array __iomem *)
		(chip->bar[BAR1].remap_addr + LOLA_BAR1_SOURCE_GAIN_ENABLE);

	/* reserve memory to copy mixer data क्रम sleep mode transitions */
	chip->mixer.array_saved = vदो_स्मृति(माप(काष्ठा lola_mixer_array));

	/* mixer matrix sources are physical input data and play streams */
	chip->mixer.src_stream_outs = chip->pcm[PLAY].num_streams;
	chip->mixer.src_phys_ins = chip->pin[CAPT].num_pins;

	/* mixer matrix destinations are record streams and physical output */
	chip->mixer.dest_stream_ins = chip->pcm[CAPT].num_streams;
	chip->mixer.dest_phys_outs = chip->pin[PLAY].num_pins;

	/* mixer matrix may have unused areas between PhysIn and
	 * Play or Record and PhysOut zones
	 */
	chip->mixer.src_stream_out_ofs = chip->mixer.src_phys_ins +
		LOLA_MIXER_SRC_INPUT_PLAY_SEPARATION(val);
	chip->mixer.dest_phys_out_ofs = chip->mixer.dest_stream_ins +
		LOLA_MIXER_DEST_REC_OUTPUT_SEPARATION(val);

	/* example : MixerMatrix of LoLa881 (LoLa16161 uses unused zones)
	 * +-+  0-------8------16-------8------16
	 * | |  |       |       |       |       |
	 * |s|  | INPUT |       | INPUT |       |
	 * | |->|  ->   |unused |  ->   |unused |
	 * |r|  |CAPTURE|       | OUTPUT|       |
	 * | |  |  MIX  |       |  MIX  |       |
	 * |c|  8--------------------------------
	 * | |  |       |       |       |       |
	 * | |  |       |       |       |       |
	 * |g|  |unused |unused |unused |unused |
	 * | |  |       |       |       |       |
	 * |a|  |       |       |       |       |
	 * | |  16-------------------------------
	 * |i|  |       |       |       |       |
	 * | |  | PLAYBK|       | PLAYBK|       |
	 * |n|->|  ->   |unused |  ->   |unused |
	 * | |  |CAPTURE|       | OUTPUT|       |
	 * | |  |  MIX  |       |  MIX  |       |
	 * |a|  8--------------------------------
	 * |r|  |       |       |       |       |
	 * |r|  |       |       |       |       |
	 * |a|  |unused |unused |unused |unused |
	 * |y|  |       |       |       |       |
	 * | |  |       |       |       |       |
	 * +++  16--|---------------|------------
	 *      +---V---------------V-----------+
	 *      |  dest_mix_gain_enable array   |
	 *      +-------------------------------+
	 */
	/* example : MixerMatrix of LoLa280
	 * +-+  0-------8-2
	 * | |  |       | |
	 * |s|  | INPUT | |     INPUT
	 * |r|->|  ->   | |      ->
	 * |c|  |CAPTURE| | <-  OUTPUT
	 * | |  |  MIX  | |      MIX
	 * |g|  8----------
	 * |a|  |       | |
	 * |i|  | PLAYBK| |     PLAYBACK
	 * |n|->|  ->   | |      ->
	 * | |  |CAPTURE| | <-  OUTPUT
	 * |a|  |  MIX  | |      MIX
	 * |r|  8---|----|-
	 * |r|  +---V----V-------------------+
	 * |a|  | dest_mix_gain_enable array |
	 * |y|  +----------------------------+
	 */
	अगर (chip->mixer.src_stream_out_ofs > MAX_AUDIO_INOUT_COUNT ||
	    chip->mixer.dest_phys_out_ofs > MAX_STREAM_IN_COUNT) अणु
		dev_err(chip->card->dev, "Invalid mixer widget size\n");
		वापस -EINVAL;
	पूर्ण

	chip->mixer.src_mask = ((1U << chip->mixer.src_phys_ins) - 1) |
		(((1U << chip->mixer.src_stream_outs) - 1)
		 << chip->mixer.src_stream_out_ofs);
	chip->mixer.dest_mask = ((1U << chip->mixer.dest_stream_ins) - 1) |
		(((1U << chip->mixer.dest_phys_outs) - 1)
		 << chip->mixer.dest_phys_out_ofs);

	dev_dbg(chip->card->dev, "Mixer src_mask=%x, dest_mask=%x\n",
		    chip->mixer.src_mask, chip->mixer.dest_mask);

	वापस 0;
पूर्ण

अटल पूर्णांक lola_mixer_set_src_gain(काष्ठा lola *chip, अचिन्हित पूर्णांक id,
				   अचिन्हित लघु gain, bool on)
अणु
	अचिन्हित पूर्णांक oldval, val;

	अगर (!(chip->mixer.src_mask & (1 << id)))
		वापस -EINVAL;
	oldval = val = पढ़ोl(&chip->mixer.array->src_gain_enable);
	अगर (on)
		val |= (1 << id);
	अन्यथा
		val &= ~(1 << id);
	/* test अगर values unchanged */
	अगर ((val == oldval) &&
	    (gain == पढ़ोw(&chip->mixer.array->src_gain[id])))
		वापस 0;

	dev_dbg(chip->card->dev,
		"lola_mixer_set_src_gain (id=%d, gain=%d) enable=%x\n",
			id, gain, val);
	ग_लिखोw(gain, &chip->mixer.array->src_gain[id]);
	ग_लिखोl(val, &chip->mixer.array->src_gain_enable);
	lola_codec_flush(chip);
	/* inक्रमm micro-controller about the new source gain */
	वापस lola_codec_ग_लिखो(chip, chip->mixer.nid,
				LOLA_VERB_SET_SOURCE_GAIN, id, 0);
पूर्ण

#अगर 0 /* not used */
अटल पूर्णांक lola_mixer_set_src_gains(काष्ठा lola *chip, अचिन्हित पूर्णांक mask,
				    अचिन्हित लघु *gains)
अणु
	पूर्णांक i;

	अगर ((chip->mixer.src_mask & mask) != mask)
		वापस -EINVAL;
	क्रम (i = 0; i < LOLA_MIXER_DIM; i++) अणु
		अगर (mask & (1 << i)) अणु
			ग_लिखोw(*gains, &chip->mixer.array->src_gain[i]);
			gains++;
		पूर्ण
	पूर्ण
	ग_लिखोl(mask, &chip->mixer.array->src_gain_enable);
	lola_codec_flush(chip);
	अगर (chip->mixer.caps & LOLA_PEAK_METER_CAN_AGC_MASK) अणु
		/* update क्रम all srcs at once */
		वापस lola_codec_ग_लिखो(chip, chip->mixer.nid,
					LOLA_VERB_SET_SOURCE_GAIN, 0x80, 0);
	पूर्ण
	/* update manually */
	क्रम (i = 0; i < LOLA_MIXER_DIM; i++) अणु
		अगर (mask & (1 << i)) अणु
			lola_codec_ग_लिखो(chip, chip->mixer.nid,
					 LOLA_VERB_SET_SOURCE_GAIN, i, 0);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर /* not used */

अटल पूर्णांक lola_mixer_set_mapping_gain(काष्ठा lola *chip,
				       अचिन्हित पूर्णांक src, अचिन्हित पूर्णांक dest,
				       अचिन्हित लघु gain, bool on)
अणु
	अचिन्हित पूर्णांक val;

	अगर (!(chip->mixer.src_mask & (1 << src)) ||
	    !(chip->mixer.dest_mask & (1 << dest)))
		वापस -EINVAL;
	अगर (on)
		ग_लिखोw(gain, &chip->mixer.array->dest_mix_gain[dest][src]);
	val = पढ़ोl(&chip->mixer.array->dest_mix_gain_enable[dest]);
	अगर (on)
		val |= (1 << src);
	अन्यथा
		val &= ~(1 << src);
	ग_लिखोl(val, &chip->mixer.array->dest_mix_gain_enable[dest]);
	lola_codec_flush(chip);
	वापस lola_codec_ग_लिखो(chip, chip->mixer.nid, LOLA_VERB_SET_MIX_GAIN,
				src, dest);
पूर्ण

#अगर 0 /* not used */
अटल पूर्णांक lola_mixer_set_dest_gains(काष्ठा lola *chip, अचिन्हित पूर्णांक id,
				     अचिन्हित पूर्णांक mask, अचिन्हित लघु *gains)
अणु
	पूर्णांक i;

	अगर (!(chip->mixer.dest_mask & (1 << id)) ||
	    (chip->mixer.src_mask & mask) != mask)
		वापस -EINVAL;
	क्रम (i = 0; i < LOLA_MIXER_DIM; i++) अणु
		अगर (mask & (1 << i)) अणु
			ग_लिखोw(*gains, &chip->mixer.array->dest_mix_gain[id][i]);
			gains++;
		पूर्ण
	पूर्ण
	ग_लिखोl(mask, &chip->mixer.array->dest_mix_gain_enable[id]);
	lola_codec_flush(chip);
	/* update क्रम all dests at once */
	वापस lola_codec_ग_लिखो(chip, chip->mixer.nid,
				LOLA_VERB_SET_DESTINATION_GAIN, id, 0);
पूर्ण
#पूर्ण_अगर /* not used */

/*
 */

अटल पूर्णांक set_analog_volume(काष्ठा lola *chip, पूर्णांक dir,
			     अचिन्हित पूर्णांक idx, अचिन्हित पूर्णांक val,
			     bool बाह्यal_call);

पूर्णांक lola_setup_all_analog_gains(काष्ठा lola *chip, पूर्णांक dir, bool mute)
अणु
	काष्ठा lola_pin *pin;
	पूर्णांक idx, max_idx;

	pin = chip->pin[dir].pins;
	max_idx = chip->pin[dir].num_pins;
	क्रम (idx = 0; idx < max_idx; idx++) अणु
		अगर (pin[idx].is_analog) अणु
			अचिन्हित पूर्णांक val = mute ? 0 : pin[idx].cur_gain_step;
			/* set volume and करो not save the value */
			set_analog_volume(chip, dir, idx, val, false);
		पूर्ण
	पूर्ण
	वापस lola_codec_flush(chip);
पूर्ण

व्योम lola_save_mixer(काष्ठा lola *chip)
अणु
	/* mute analog output */
	अगर (chip->mixer.array_saved) अणु
		/* store contents of mixer array */
		स_नकल_fromio(chip->mixer.array_saved, chip->mixer.array,
			      माप(*chip->mixer.array));
	पूर्ण
	lola_setup_all_analog_gains(chip, PLAY, true); /* output mute */
पूर्ण

व्योम lola_restore_mixer(काष्ठा lola *chip)
अणु
	पूर्णांक i;

	/*lola_reset_setups(chip);*/
	अगर (chip->mixer.array_saved) अणु
		/* restore contents of mixer array */
		स_नकल_toio(chip->mixer.array, chip->mixer.array_saved,
			    माप(*chip->mixer.array));
		/* inक्रमm micro-controller about all restored values
		 * and ignore वापस values
		 */
		क्रम (i = 0; i < chip->mixer.src_phys_ins; i++)
			lola_codec_ग_लिखो(chip, chip->mixer.nid,
					 LOLA_VERB_SET_SOURCE_GAIN,
					 i, 0);
		क्रम (i = 0; i < chip->mixer.src_stream_outs; i++)
			lola_codec_ग_लिखो(chip, chip->mixer.nid,
					 LOLA_VERB_SET_SOURCE_GAIN,
					 chip->mixer.src_stream_out_ofs + i, 0);
		क्रम (i = 0; i < chip->mixer.dest_stream_ins; i++)
			lola_codec_ग_लिखो(chip, chip->mixer.nid,
					 LOLA_VERB_SET_DESTINATION_GAIN,
					 i, 0);
		क्रम (i = 0; i < chip->mixer.dest_phys_outs; i++)
			lola_codec_ग_लिखो(chip, chip->mixer.nid,
					 LOLA_VERB_SET_DESTINATION_GAIN,
					 chip->mixer.dest_phys_out_ofs + i, 0);
		lola_codec_flush(chip);
	पूर्ण
पूर्ण

/*
 */

अटल पूर्णांक set_analog_volume(काष्ठा lola *chip, पूर्णांक dir,
			     अचिन्हित पूर्णांक idx, अचिन्हित पूर्णांक val,
			     bool बाह्यal_call)
अणु
	काष्ठा lola_pin *pin;
	पूर्णांक err;

	अगर (idx >= chip->pin[dir].num_pins)
		वापस -EINVAL;
	pin = &chip->pin[dir].pins[idx];
	अगर (!pin->is_analog || pin->amp_num_steps <= val)
		वापस -EINVAL;
	अगर (बाह्यal_call && pin->cur_gain_step == val)
		वापस 0;
	अगर (बाह्यal_call)
		lola_codec_flush(chip);
	dev_dbg(chip->card->dev,
		"set_analog_volume (dir=%d idx=%d, volume=%d)\n",
			dir, idx, val);
	err = lola_codec_ग_लिखो(chip, pin->nid,
			       LOLA_VERB_SET_AMP_GAIN_MUTE, val, 0);
	अगर (err < 0)
		वापस err;
	अगर (बाह्यal_call)
		pin->cur_gain_step = val;
	वापस 0;
पूर्ण

पूर्णांक lola_set_src_config(काष्ठा lola *chip, अचिन्हित पूर्णांक src_mask, bool update)
अणु
	पूर्णांक ret = 0;
	पूर्णांक success = 0;
	पूर्णांक n, err;

	/* SRC can be activated and the dwInputSRCMask is valid? */
	अगर ((chip->input_src_caps_mask & src_mask) != src_mask)
		वापस -EINVAL;
	/* handle all even Inमाला_दो - SRC is a stereo setting !!! */
	क्रम (n = 0; n < chip->pin[CAPT].num_pins; n += 2) अणु
		अचिन्हित पूर्णांक mask = 3U << n; /* handle the stereo हाल */
		अचिन्हित पूर्णांक new_src, src_state;
		अगर (!(chip->input_src_caps_mask & mask))
			जारी;
		/* अगर one IO needs SRC, both stereo IO will get SRC */
		new_src = (src_mask & mask) != 0;
		अगर (update) अणु
			src_state = (chip->input_src_mask & mask) != 0;
			अगर (src_state == new_src)
				जारी;   /* nothing to change क्रम this IO */
		पूर्ण
		err = lola_codec_ग_लिखो(chip, chip->pcm[CAPT].streams[n].nid,
				       LOLA_VERB_SET_SRC, new_src, 0);
		अगर (!err)
			success++;
		अन्यथा
			ret = err;
	पूर्ण
	अगर (success)
		ret = lola_codec_flush(chip);
	अगर (!ret)
		chip->input_src_mask = src_mask;
	वापस ret;
पूर्ण

/*
 */
अटल पूर्णांक init_mixer_values(काष्ठा lola *chip)
अणु
	पूर्णांक i;

	/* all sample rate converters on */
	lola_set_src_config(chip, (1 << chip->pin[CAPT].num_pins) - 1, false);

	/* clear all mixer matrix settings */
	स_रखो_io(chip->mixer.array, 0, माप(*chip->mixer.array));
	/* inक्रमm firmware about all updated matrix columns - capture part */
	क्रम (i = 0; i < chip->mixer.dest_stream_ins; i++)
		lola_codec_ग_लिखो(chip, chip->mixer.nid,
				 LOLA_VERB_SET_DESTINATION_GAIN,
				 i, 0);
	/* inक्रमm firmware about all updated matrix columns - output part */
	क्रम (i = 0; i < chip->mixer.dest_phys_outs; i++)
		lola_codec_ग_लिखो(chip, chip->mixer.nid,
				 LOLA_VERB_SET_DESTINATION_GAIN,
				 chip->mixer.dest_phys_out_ofs + i, 0);

	/* set all digital input source (master) gains to 0dB */
	क्रम (i = 0; i < chip->mixer.src_phys_ins; i++)
		lola_mixer_set_src_gain(chip, i, 336, true); /* 0dB */

	/* set all digital playback source (master) gains to 0dB */
	क्रम (i = 0; i < chip->mixer.src_stream_outs; i++)
		lola_mixer_set_src_gain(chip,
					i + chip->mixer.src_stream_out_ofs,
					336, true); /* 0dB */
	/* set gain value 0dB diagonally in matrix - part INPUT -> CAPTURE */
	क्रम (i = 0; i < chip->mixer.dest_stream_ins; i++) अणु
		पूर्णांक src = i % chip->mixer.src_phys_ins;
		lola_mixer_set_mapping_gain(chip, src, i, 336, true);
	पूर्ण
	/* set gain value 0dB diagonally in matrix , part PLAYBACK -> OUTPUT
	 * (LoLa280 : playback channel 0,2,4,6 linked to output channel 0)
	 * (LoLa280 : playback channel 1,3,5,7 linked to output channel 1)
	 */
	क्रम (i = 0; i < chip->mixer.src_stream_outs; i++) अणु
		पूर्णांक src = chip->mixer.src_stream_out_ofs + i;
		पूर्णांक dst = chip->mixer.dest_phys_out_ofs +
			i % chip->mixer.dest_phys_outs;
		lola_mixer_set_mapping_gain(chip, src, dst, 336, true);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * analog mixer control element
 */
अटल पूर्णांक lola_analog_vol_info(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा lola *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक dir = kcontrol->निजी_value;

	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = chip->pin[dir].num_pins;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = chip->pin[dir].pins[0].amp_num_steps;
	वापस 0;
पूर्ण

अटल पूर्णांक lola_analog_vol_get(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा lola *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक dir = kcontrol->निजी_value;
	पूर्णांक i;

	क्रम (i = 0; i < chip->pin[dir].num_pins; i++)
		ucontrol->value.पूर्णांकeger.value[i] =
			chip->pin[dir].pins[i].cur_gain_step;
	वापस 0;
पूर्ण

अटल पूर्णांक lola_analog_vol_put(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा lola *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक dir = kcontrol->निजी_value;
	पूर्णांक i, err;

	क्रम (i = 0; i < chip->pin[dir].num_pins; i++) अणु
		err = set_analog_volume(chip, dir, i,
					ucontrol->value.पूर्णांकeger.value[i],
					true);
		अगर (err < 0)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक lola_analog_vol_tlv(काष्ठा snd_kcontrol *kcontrol, पूर्णांक op_flag,
			       अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक __user *tlv)
अणु
	काष्ठा lola *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक dir = kcontrol->निजी_value;
	अचिन्हित पूर्णांक val1, val2;
	काष्ठा lola_pin *pin;

	अगर (size < 4 * माप(अचिन्हित पूर्णांक))
		वापस -ENOMEM;
	pin = &chip->pin[dir].pins[0];

	val2 = pin->amp_step_size * 25;
	val1 = -1 * (पूर्णांक)pin->amp_offset * (पूर्णांक)val2;
#अगर_घोषित TLV_DB_SCALE_MUTE
	val2 |= TLV_DB_SCALE_MUTE;
#पूर्ण_अगर
	अगर (put_user(SNDRV_CTL_TLVT_DB_SCALE, tlv))
		वापस -EFAULT;
	अगर (put_user(2 * माप(अचिन्हित पूर्णांक), tlv + 1))
		वापस -EFAULT;
	अगर (put_user(val1, tlv + 2))
		वापस -EFAULT;
	अगर (put_user(val2, tlv + 3))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल काष्ठा snd_kcontrol_new lola_analog_mixer = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.access = (SNDRV_CTL_ELEM_ACCESS_READWRITE |
		   SNDRV_CTL_ELEM_ACCESS_TLV_READ |
		   SNDRV_CTL_ELEM_ACCESS_TLV_CALLBACK),
	.info = lola_analog_vol_info,
	.get = lola_analog_vol_get,
	.put = lola_analog_vol_put,
	.tlv.c = lola_analog_vol_tlv,
पूर्ण;

अटल पूर्णांक create_analog_mixer(काष्ठा lola *chip, पूर्णांक dir, अक्षर *name)
अणु
	अगर (!chip->pin[dir].num_pins)
		वापस 0;
	/* no analog volumes on digital only adapters */
	अगर (chip->pin[dir].num_pins != chip->pin[dir].num_analog_pins)
		वापस 0;
	lola_analog_mixer.name = name;
	lola_analog_mixer.निजी_value = dir;
	वापस snd_ctl_add(chip->card,
			   snd_ctl_new1(&lola_analog_mixer, chip));
पूर्ण

/*
 * Hardware sample rate converter on digital input
 */
अटल पूर्णांक lola_input_src_info(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा lola *chip = snd_kcontrol_chip(kcontrol);

	uinfo->type = SNDRV_CTL_ELEM_TYPE_BOOLEAN;
	uinfo->count = chip->pin[CAPT].num_pins;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक lola_input_src_get(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा lola *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक i;

	क्रम (i = 0; i < chip->pin[CAPT].num_pins; i++)
		ucontrol->value.पूर्णांकeger.value[i] =
			!!(chip->input_src_mask & (1 << i));
	वापस 0;
पूर्ण

अटल पूर्णांक lola_input_src_put(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा lola *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक i;
	अचिन्हित पूर्णांक mask;

	mask = 0;
	क्रम (i = 0; i < chip->pin[CAPT].num_pins; i++)
		अगर (ucontrol->value.पूर्णांकeger.value[i])
			mask |= 1 << i;
	वापस lola_set_src_config(chip, mask, true);
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new lola_input_src_mixer = अणु
	.name = "Digital SRC Capture Switch",
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.info = lola_input_src_info,
	.get = lola_input_src_get,
	.put = lola_input_src_put,
पूर्ण;

/*
 * Lola16161 or Lola881 can have Hardware sample rate converters
 * on its digital input pins
 */
अटल पूर्णांक create_input_src_mixer(काष्ठा lola *chip)
अणु
	अगर (!chip->input_src_caps_mask)
		वापस 0;

	वापस snd_ctl_add(chip->card,
			   snd_ctl_new1(&lola_input_src_mixer, chip));
पूर्ण

/*
 * src gain mixer
 */
अटल पूर्णांक lola_src_gain_info(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अचिन्हित पूर्णांक count = (kcontrol->निजी_value >> 8) & 0xff;

	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = count;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 409;
	वापस 0;
पूर्ण

अटल पूर्णांक lola_src_gain_get(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा lola *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक ofs = kcontrol->निजी_value & 0xff;
	अचिन्हित पूर्णांक count = (kcontrol->निजी_value >> 8) & 0xff;
	अचिन्हित पूर्णांक mask, i;

	mask = पढ़ोl(&chip->mixer.array->src_gain_enable);
	क्रम (i = 0; i < count; i++) अणु
		अचिन्हित पूर्णांक idx = ofs + i;
		अचिन्हित लघु val;
		अगर (!(chip->mixer.src_mask & (1 << idx)))
			वापस -EINVAL;
		अगर (mask & (1 << idx))
			val = पढ़ोw(&chip->mixer.array->src_gain[idx]) + 1;
		अन्यथा
			val = 0;
		ucontrol->value.पूर्णांकeger.value[i] = val;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक lola_src_gain_put(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा lola *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक ofs = kcontrol->निजी_value & 0xff;
	अचिन्हित पूर्णांक count = (kcontrol->निजी_value >> 8) & 0xff;
	पूर्णांक i, err;

	क्रम (i = 0; i < count; i++) अणु
		अचिन्हित पूर्णांक idx = ofs + i;
		अचिन्हित लघु val = ucontrol->value.पूर्णांकeger.value[i];
		अगर (val)
			val--;
		err = lola_mixer_set_src_gain(chip, idx, val, !!val);
		अगर (err < 0)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

/* raw value: 0 = -84dB, 336 = 0dB, 408=18dB, incremented 1 क्रम mute */
अटल स्थिर DECLARE_TLV_DB_SCALE(lola_src_gain_tlv, -8425, 25, 1);

अटल काष्ठा snd_kcontrol_new lola_src_gain_mixer = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.access = (SNDRV_CTL_ELEM_ACCESS_READWRITE |
		   SNDRV_CTL_ELEM_ACCESS_TLV_READ),
	.info = lola_src_gain_info,
	.get = lola_src_gain_get,
	.put = lola_src_gain_put,
	.tlv.p = lola_src_gain_tlv,
पूर्ण;

अटल पूर्णांक create_src_gain_mixer(काष्ठा lola *chip,
				 पूर्णांक num, पूर्णांक ofs, अक्षर *name)
अणु
	lola_src_gain_mixer.name = name;
	lola_src_gain_mixer.निजी_value = ofs + (num << 8);
	वापस snd_ctl_add(chip->card,
			   snd_ctl_new1(&lola_src_gain_mixer, chip));
पूर्ण

#अगर 0 /* not used */
/*
 * destination gain (matrix-like) mixer
 */
अटल पूर्णांक lola_dest_gain_info(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अचिन्हित पूर्णांक src_num = (kcontrol->निजी_value >> 8) & 0xff;

	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = src_num;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 433;
	वापस 0;
पूर्ण

अटल पूर्णांक lola_dest_gain_get(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा lola *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक src_ofs = kcontrol->निजी_value & 0xff;
	अचिन्हित पूर्णांक src_num = (kcontrol->निजी_value >> 8) & 0xff;
	अचिन्हित पूर्णांक dst_ofs = (kcontrol->निजी_value >> 16) & 0xff;
	अचिन्हित पूर्णांक dst, mask, i;

	dst = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id) + dst_ofs;
	mask = पढ़ोl(&chip->mixer.array->dest_mix_gain_enable[dst]);
	क्रम (i = 0; i < src_num; i++) अणु
		अचिन्हित पूर्णांक src = src_ofs + i;
		अचिन्हित लघु val;
		अगर (!(chip->mixer.src_mask & (1 << src)))
			वापस -EINVAL;
		अगर (mask & (1 << dst))
			val = पढ़ोw(&chip->mixer.array->dest_mix_gain[dst][src]) + 1;
		अन्यथा
			val = 0;
		ucontrol->value.पूर्णांकeger.value[i] = val;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक lola_dest_gain_put(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा lola *chip = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक src_ofs = kcontrol->निजी_value & 0xff;
	अचिन्हित पूर्णांक src_num = (kcontrol->निजी_value >> 8) & 0xff;
	अचिन्हित पूर्णांक dst_ofs = (kcontrol->निजी_value >> 16) & 0xff;
	अचिन्हित पूर्णांक dst, mask;
	अचिन्हित लघु gains[MAX_STREAM_COUNT];
	पूर्णांक i, num;

	mask = 0;
	num = 0;
	क्रम (i = 0; i < src_num; i++) अणु
		अचिन्हित लघु val = ucontrol->value.पूर्णांकeger.value[i];
		अगर (val) अणु
			gains[num++] = val - 1;
			mask |= 1 << i;
		पूर्ण
	पूर्ण
	mask <<= src_ofs;
	dst = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id) + dst_ofs;
	वापस lola_mixer_set_dest_gains(chip, dst, mask, gains);
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(lola_dest_gain_tlv, -8425, 25, 1);

अटल काष्ठा snd_kcontrol_new lola_dest_gain_mixer = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.access = (SNDRV_CTL_ELEM_ACCESS_READWRITE |
		   SNDRV_CTL_ELEM_ACCESS_TLV_READ),
	.info = lola_dest_gain_info,
	.get = lola_dest_gain_get,
	.put = lola_dest_gain_put,
	.tlv.p = lola_dest_gain_tlv,
पूर्ण;

अटल पूर्णांक create_dest_gain_mixer(काष्ठा lola *chip,
				  पूर्णांक src_num, पूर्णांक src_ofs,
				  पूर्णांक num, पूर्णांक ofs, अक्षर *name)
अणु
	lola_dest_gain_mixer.count = num;
	lola_dest_gain_mixer.name = name;
	lola_dest_gain_mixer.निजी_value =
		src_ofs + (src_num << 8) + (ofs << 16) + (num << 24);
	वापस snd_ctl_add(chip->card,
			  snd_ctl_new1(&lola_dest_gain_mixer, chip));
पूर्ण
#पूर्ण_अगर /* not used */

/*
 */
पूर्णांक lola_create_mixer(काष्ठा lola *chip)
अणु
	पूर्णांक err;

	err = create_analog_mixer(chip, PLAY, "Analog Playback Volume");
	अगर (err < 0)
		वापस err;
	err = create_analog_mixer(chip, CAPT, "Analog Capture Volume");
	अगर (err < 0)
		वापस err;
	err = create_input_src_mixer(chip);
	अगर (err < 0)
		वापस err;
	err = create_src_gain_mixer(chip, chip->mixer.src_phys_ins, 0,
				    "Digital Capture Volume");
	अगर (err < 0)
		वापस err;
	err = create_src_gain_mixer(chip, chip->mixer.src_stream_outs,
				    chip->mixer.src_stream_out_ofs,
				    "Digital Playback Volume");
	अगर (err < 0)
		वापस err;
#अगर 0
/* FIXME: buggy mixer matrix handling */
	err = create_dest_gain_mixer(chip,
				     chip->mixer.src_phys_ins, 0,
				     chip->mixer.dest_stream_ins, 0,
				     "Line Capture Volume");
	अगर (err < 0)
		वापस err;
	err = create_dest_gain_mixer(chip,
				     chip->mixer.src_stream_outs,
				     chip->mixer.src_stream_out_ofs,
				     chip->mixer.dest_stream_ins, 0,
				     "Stream-Loopback Capture Volume");
	अगर (err < 0)
		वापस err;
	err = create_dest_gain_mixer(chip,
				     chip->mixer.src_phys_ins, 0,
				     chip->mixer.dest_phys_outs,
				     chip->mixer.dest_phys_out_ofs,
				     "Line-Loopback Playback Volume");
	अगर (err < 0)
		वापस err;
	err = create_dest_gain_mixer(chip,
				     chip->mixer.src_stream_outs,
				     chip->mixer.src_stream_out_ofs,
				     chip->mixer.dest_phys_outs,
				     chip->mixer.dest_phys_out_ofs,
				     "Stream Playback Volume");
	अगर (err < 0)
		वापस err;
#पूर्ण_अगर /* FIXME */
	वापस init_mixer_values(chip);
पूर्ण
