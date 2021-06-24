<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) by Uros Bizjak <uros@kss-loka.si>
 *                   
 *  Routines क्रम OPL2/OPL3/OPL4 control
 */

#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/nospec.h>
#समावेश <sound/opl3.h>
#समावेश <sound/asound_fm.h>
#समावेश "opl3_voice.h"

#अगर IS_ENABLED(CONFIG_SND_SEQUENCER)
#घोषणा OPL3_SUPPORT_SYNTH
#पूर्ण_अगर

/*
 *    There is 18 possible 2 OP voices
 *      (9 in the left and 9 in the right).
 *      The first OP is the modulator and 2nd is the carrier.
 *
 *      The first three voices in the both sides may be connected
 *      with another voice to a 4 OP voice. For example voice 0
 *      can be connected with voice 3. The चालकs of voice 3 are
 *      used as चालकs 3 and 4 of the new 4 OP voice.
 *      In this हाल the 2 OP voice number 0 is the 'first half' and
 *      voice 3 is the second.
 */


/*
 *    Register offset table क्रम OPL2/3 voices,
 *    OPL2 / one OPL3 रेजिस्टर array side only
 */

अक्षर snd_opl3_regmap[MAX_OPL2_VOICES][4] =
अणु
/*	  OP1   OP2   OP3   OP4		*/
/*	 ------------------------	*/
	अणु 0x00, 0x03, 0x08, 0x0b पूर्ण,
	अणु 0x01, 0x04, 0x09, 0x0c पूर्ण,
	अणु 0x02, 0x05, 0x0a, 0x0d पूर्ण,

	अणु 0x08, 0x0b, 0x00, 0x00 पूर्ण,
	अणु 0x09, 0x0c, 0x00, 0x00 पूर्ण,
	अणु 0x0a, 0x0d, 0x00, 0x00 पूर्ण,

	अणु 0x10, 0x13, 0x00, 0x00 पूर्ण,	/* used by percussive voices */
	अणु 0x11, 0x14, 0x00, 0x00 पूर्ण,	/* अगर the percussive mode */
	अणु 0x12, 0x15, 0x00, 0x00 पूर्ण	/* is selected (only left reg block) */
पूर्ण;

EXPORT_SYMBOL(snd_opl3_regmap);

/*
 * prototypes
 */
अटल पूर्णांक snd_opl3_play_note(काष्ठा snd_opl3 * opl3, काष्ठा snd_dm_fm_note * note);
अटल पूर्णांक snd_opl3_set_voice(काष्ठा snd_opl3 * opl3, काष्ठा snd_dm_fm_voice * voice);
अटल पूर्णांक snd_opl3_set_params(काष्ठा snd_opl3 * opl3, काष्ठा snd_dm_fm_params * params);
अटल पूर्णांक snd_opl3_set_mode(काष्ठा snd_opl3 * opl3, पूर्णांक mode);
अटल पूर्णांक snd_opl3_set_connection(काष्ठा snd_opl3 * opl3, पूर्णांक connection);

/* ------------------------------ */

/*
 * खोलो the device exclusively
 */
पूर्णांक snd_opl3_खोलो(काष्ठा snd_hwdep * hw, काष्ठा file *file)
अणु
	वापस 0;
पूर्ण

/*
 * ioctl क्रम hwdep device:
 */
पूर्णांक snd_opl3_ioctl(काष्ठा snd_hwdep * hw, काष्ठा file *file,
		   अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा snd_opl3 *opl3 = hw->निजी_data;
	व्योम __user *argp = (व्योम __user *)arg;

	अगर (snd_BUG_ON(!opl3))
		वापस -EINVAL;

	चयन (cmd) अणु
		/* get inक्रमmation */
	हाल SNDRV_DM_FM_IOCTL_INFO:
		अणु
			काष्ठा snd_dm_fm_info info;

			स_रखो(&info, 0, माप(info));

			info.fm_mode = opl3->fm_mode;
			info.rhythm = opl3->rhythm;
			अगर (copy_to_user(argp, &info, माप(काष्ठा snd_dm_fm_info)))
				वापस -EFAULT;
			वापस 0;
		पूर्ण

	हाल SNDRV_DM_FM_IOCTL_RESET:
#अगर_घोषित CONFIG_SND_OSSEMUL
	हाल SNDRV_DM_FM_OSS_IOCTL_RESET:
#पूर्ण_अगर
		snd_opl3_reset(opl3);
		वापस 0;

	हाल SNDRV_DM_FM_IOCTL_PLAY_NOTE:
#अगर_घोषित CONFIG_SND_OSSEMUL
	हाल SNDRV_DM_FM_OSS_IOCTL_PLAY_NOTE:
#पूर्ण_अगर
		अणु
			काष्ठा snd_dm_fm_note note;
			अगर (copy_from_user(&note, argp, माप(काष्ठा snd_dm_fm_note)))
				वापस -EFAULT;
			वापस snd_opl3_play_note(opl3, &note);
		पूर्ण

	हाल SNDRV_DM_FM_IOCTL_SET_VOICE:
#अगर_घोषित CONFIG_SND_OSSEMUL
	हाल SNDRV_DM_FM_OSS_IOCTL_SET_VOICE:
#पूर्ण_अगर
		अणु
			काष्ठा snd_dm_fm_voice voice;
			अगर (copy_from_user(&voice, argp, माप(काष्ठा snd_dm_fm_voice)))
				वापस -EFAULT;
			वापस snd_opl3_set_voice(opl3, &voice);
		पूर्ण

	हाल SNDRV_DM_FM_IOCTL_SET_PARAMS:
#अगर_घोषित CONFIG_SND_OSSEMUL
	हाल SNDRV_DM_FM_OSS_IOCTL_SET_PARAMS:
#पूर्ण_अगर
		अणु
			काष्ठा snd_dm_fm_params params;
			अगर (copy_from_user(&params, argp, माप(काष्ठा snd_dm_fm_params)))
				वापस -EFAULT;
			वापस snd_opl3_set_params(opl3, &params);
		पूर्ण

	हाल SNDRV_DM_FM_IOCTL_SET_MODE:
#अगर_घोषित CONFIG_SND_OSSEMUL
	हाल SNDRV_DM_FM_OSS_IOCTL_SET_MODE:
#पूर्ण_अगर
		वापस snd_opl3_set_mode(opl3, (पूर्णांक) arg);

	हाल SNDRV_DM_FM_IOCTL_SET_CONNECTION:
#अगर_घोषित CONFIG_SND_OSSEMUL
	हाल SNDRV_DM_FM_OSS_IOCTL_SET_OPL:
#पूर्ण_अगर
		वापस snd_opl3_set_connection(opl3, (पूर्णांक) arg);

#अगर_घोषित OPL3_SUPPORT_SYNTH
	हाल SNDRV_DM_FM_IOCTL_CLEAR_PATCHES:
		snd_opl3_clear_patches(opl3);
		वापस 0;
#पूर्ण_अगर

#अगर_घोषित CONFIG_SND_DEBUG
	शेष:
		snd_prपूर्णांकk(KERN_WARNING "unknown IOCTL: 0x%x\n", cmd);
#पूर्ण_अगर
	पूर्ण
	वापस -ENOTTY;
पूर्ण

/*
 * बंद the device
 */
पूर्णांक snd_opl3_release(काष्ठा snd_hwdep * hw, काष्ठा file *file)
अणु
	काष्ठा snd_opl3 *opl3 = hw->निजी_data;

	snd_opl3_reset(opl3);
	वापस 0;
पूर्ण

#अगर_घोषित OPL3_SUPPORT_SYNTH
/*
 * ग_लिखो the device - load patches
 */
दीर्घ snd_opl3_ग_लिखो(काष्ठा snd_hwdep *hw, स्थिर अक्षर __user *buf, दीर्घ count,
		    loff_t *offset)
अणु
	काष्ठा snd_opl3 *opl3 = hw->निजी_data;
	दीर्घ result = 0;
	पूर्णांक err = 0;
	काष्ठा sbi_patch inst;

	जबतक (count >= माप(inst)) अणु
		अचिन्हित अक्षर type;
		अगर (copy_from_user(&inst, buf, माप(inst)))
			वापस -EFAULT;
		अगर (!स_भेद(inst.key, FM_KEY_SBI, 4) ||
		    !स_भेद(inst.key, FM_KEY_2OP, 4))
			type = FM_PATCH_OPL2;
		अन्यथा अगर (!स_भेद(inst.key, FM_KEY_4OP, 4))
			type = FM_PATCH_OPL3;
		अन्यथा /* invalid type */
			अवरोध;
		err = snd_opl3_load_patch(opl3, inst.prog, inst.bank, type,
					  inst.name, inst.extension,
					  inst.data);
		अगर (err < 0)
			अवरोध;
		result += माप(inst);
		count -= माप(inst);
	पूर्ण
	वापस result > 0 ? result : err;
पूर्ण


/*
 * Patch management
 */

/* offsets क्रम SBI params */
#घोषणा AM_VIB		0
#घोषणा KSL_LEVEL	2
#घोषणा ATTACK_DECAY	4
#घोषणा SUSTAIN_RELEASE	6
#घोषणा WAVE_SELECT	8

/* offset क्रम SBI instrument */
#घोषणा CONNECTION	10
#घोषणा OFFSET_4OP	11

/*
 * load a patch, obviously.
 *
 * loaded on the given program and bank numbers with the given type
 * (FM_PATCH_OPLx).
 * data is the poपूर्णांकer of SBI record _without_ header (key and name).
 * name is the name string of the patch.
 * ext is the extension data of 7 bytes दीर्घ (stored in name of SBI
 * data up to offset 25), or शून्य to skip.
 * वापस 0 अगर successful or a negative error code.
 */
पूर्णांक snd_opl3_load_patch(काष्ठा snd_opl3 *opl3,
			पूर्णांक prog, पूर्णांक bank, पूर्णांक type,
			स्थिर अक्षर *name,
			स्थिर अचिन्हित अक्षर *ext,
			स्थिर अचिन्हित अक्षर *data)
अणु
	काष्ठा fm_patch *patch;
	पूर्णांक i;

	patch = snd_opl3_find_patch(opl3, prog, bank, 1);
	अगर (!patch)
		वापस -ENOMEM;

	patch->type = type;

	क्रम (i = 0; i < 2; i++) अणु
		patch->inst.op[i].am_vib = data[AM_VIB + i];
		patch->inst.op[i].ksl_level = data[KSL_LEVEL + i];
		patch->inst.op[i].attack_decay = data[ATTACK_DECAY + i];
		patch->inst.op[i].sustain_release = data[SUSTAIN_RELEASE + i];
		patch->inst.op[i].wave_select = data[WAVE_SELECT + i];
	पूर्ण
	patch->inst.feedback_connection[0] = data[CONNECTION];

	अगर (type == FM_PATCH_OPL3) अणु
		क्रम (i = 0; i < 2; i++) अणु
			patch->inst.op[i+2].am_vib =
				data[OFFSET_4OP + AM_VIB + i];
			patch->inst.op[i+2].ksl_level =
				data[OFFSET_4OP + KSL_LEVEL + i];
			patch->inst.op[i+2].attack_decay =
				data[OFFSET_4OP + ATTACK_DECAY + i];
			patch->inst.op[i+2].sustain_release =
				data[OFFSET_4OP + SUSTAIN_RELEASE + i];
			patch->inst.op[i+2].wave_select =
				data[OFFSET_4OP + WAVE_SELECT + i];
		पूर्ण
		patch->inst.feedback_connection[1] =
			data[OFFSET_4OP + CONNECTION];
	पूर्ण

	अगर (ext) अणु
		patch->inst.echo_delay = ext[0];
		patch->inst.echo_atten = ext[1];
		patch->inst.chorus_spपढ़ो = ext[2];
		patch->inst.trnsps = ext[3];
		patch->inst.fix_dur = ext[4];
		patch->inst.modes = ext[5];
		patch->inst.fix_key = ext[6];
	पूर्ण

	अगर (name)
		strscpy(patch->name, name, माप(patch->name));

	वापस 0;
पूर्ण
EXPORT_SYMBOL(snd_opl3_load_patch);

/*
 * find a patch with the given program and bank numbers, वापसs its poपूर्णांकer
 * अगर no matching patch is found and create_patch is set, it creates a
 * new patch object.
 */
काष्ठा fm_patch *snd_opl3_find_patch(काष्ठा snd_opl3 *opl3, पूर्णांक prog, पूर्णांक bank,
				     पूर्णांक create_patch)
अणु
	/* pretty dumb hash key */
	अचिन्हित पूर्णांक key = (prog + bank) % OPL3_PATCH_HASH_SIZE;
	काष्ठा fm_patch *patch;

	क्रम (patch = opl3->patch_table[key]; patch; patch = patch->next) अणु
		अगर (patch->prog == prog && patch->bank == bank)
			वापस patch;
	पूर्ण
	अगर (!create_patch)
		वापस शून्य;

	patch = kzalloc(माप(*patch), GFP_KERNEL);
	अगर (!patch)
		वापस शून्य;
	patch->prog = prog;
	patch->bank = bank;
	patch->next = opl3->patch_table[key];
	opl3->patch_table[key] = patch;
	वापस patch;
पूर्ण
EXPORT_SYMBOL(snd_opl3_find_patch);

/*
 * Clear all patches of the given OPL3 instance
 */
व्योम snd_opl3_clear_patches(काष्ठा snd_opl3 *opl3)
अणु
	पूर्णांक i;
	क्रम (i = 0; i <  OPL3_PATCH_HASH_SIZE; i++) अणु
		काष्ठा fm_patch *patch, *next;
		क्रम (patch = opl3->patch_table[i]; patch; patch = next) अणु
			next = patch->next;
			kमुक्त(patch);
		पूर्ण
	पूर्ण
	स_रखो(opl3->patch_table, 0, माप(opl3->patch_table));
पूर्ण
#पूर्ण_अगर /* OPL3_SUPPORT_SYNTH */

/* ------------------------------ */

व्योम snd_opl3_reset(काष्ठा snd_opl3 * opl3)
अणु
	अचिन्हित लघु opl3_reg;

	अचिन्हित लघु reg_side;
	अचिन्हित अक्षर voice_offset;

	पूर्णांक max_voices, i;

	max_voices = (opl3->hardware < OPL3_HW_OPL3) ?
		MAX_OPL2_VOICES : MAX_OPL3_VOICES;

	क्रम (i = 0; i < max_voices; i++) अणु
		/* Get रेजिस्टर array side and offset of voice */
		अगर (i < MAX_OPL2_VOICES) अणु
			/* Left रेजिस्टर block क्रम voices 0 .. 8 */
			reg_side = OPL3_LEFT;
			voice_offset = i;
		पूर्ण अन्यथा अणु
			/* Right रेजिस्टर block क्रम voices 9 .. 17 */
			reg_side = OPL3_RIGHT;
			voice_offset = i - MAX_OPL2_VOICES;
		पूर्ण
		opl3_reg = reg_side | (OPL3_REG_KSL_LEVEL + snd_opl3_regmap[voice_offset][0]);
		opl3->command(opl3, opl3_reg, OPL3_TOTAL_LEVEL_MASK); /* Operator 1 volume */
		opl3_reg = reg_side | (OPL3_REG_KSL_LEVEL + snd_opl3_regmap[voice_offset][1]);
		opl3->command(opl3, opl3_reg, OPL3_TOTAL_LEVEL_MASK); /* Operator 2 volume */

		opl3_reg = reg_side | (OPL3_REG_KEYON_BLOCK + voice_offset);
		opl3->command(opl3, opl3_reg, 0x00);	/* Note off */
	पूर्ण

	opl3->max_voices = MAX_OPL2_VOICES;
	opl3->fm_mode = SNDRV_DM_FM_MODE_OPL2;

	opl3->command(opl3, OPL3_LEFT | OPL3_REG_TEST, OPL3_ENABLE_WAVE_SELECT);
	opl3->command(opl3, OPL3_LEFT | OPL3_REG_PERCUSSION, 0x00);	/* Melodic mode */
	opl3->rhythm = 0;
पूर्ण

EXPORT_SYMBOL(snd_opl3_reset);

अटल पूर्णांक snd_opl3_play_note(काष्ठा snd_opl3 * opl3, काष्ठा snd_dm_fm_note * note)
अणु
	अचिन्हित लघु reg_side;
	अचिन्हित अक्षर voice_offset;

	अचिन्हित लघु opl3_reg;
	अचिन्हित अक्षर reg_val;

	/* Voices 0 -  8 in OPL2 mode */
	/* Voices 0 - 17 in OPL3 mode */
	अगर (note->voice >= ((opl3->fm_mode == SNDRV_DM_FM_MODE_OPL3) ?
			    MAX_OPL3_VOICES : MAX_OPL2_VOICES))
		वापस -EINVAL;

	/* Get रेजिस्टर array side and offset of voice */
	अगर (note->voice < MAX_OPL2_VOICES) अणु
		/* Left रेजिस्टर block क्रम voices 0 .. 8 */
		reg_side = OPL3_LEFT;
		voice_offset = note->voice;
	पूर्ण अन्यथा अणु
		/* Right रेजिस्टर block क्रम voices 9 .. 17 */
		reg_side = OPL3_RIGHT;
		voice_offset = note->voice - MAX_OPL2_VOICES;
	पूर्ण

	/* Set lower 8 bits of note frequency */
	reg_val = (अचिन्हित अक्षर) note->fnum;
	opl3_reg = reg_side | (OPL3_REG_FNUM_LOW + voice_offset);
	opl3->command(opl3, opl3_reg, reg_val);
	
	reg_val = 0x00;
	/* Set output sound flag */
	अगर (note->key_on)
		reg_val |= OPL3_KEYON_BIT;
	/* Set octave */
	reg_val |= (note->octave << 2) & OPL3_BLOCKNUM_MASK;
	/* Set higher 2 bits of note frequency */
	reg_val |= (अचिन्हित अक्षर) (note->fnum >> 8) & OPL3_FNUM_HIGH_MASK;

	/* Set OPL3 KEYON_BLOCK रेजिस्टर of requested voice */ 
	opl3_reg = reg_side | (OPL3_REG_KEYON_BLOCK + voice_offset);
	opl3->command(opl3, opl3_reg, reg_val);

	वापस 0;
पूर्ण


अटल पूर्णांक snd_opl3_set_voice(काष्ठा snd_opl3 * opl3, काष्ठा snd_dm_fm_voice * voice)
अणु
	अचिन्हित लघु reg_side;
	अचिन्हित अक्षर op_offset;
	अचिन्हित अक्षर voice_offset, voice_op;

	अचिन्हित लघु opl3_reg;
	अचिन्हित अक्षर reg_val;

	/* Only चालकs 1 and 2 */
	अगर (voice->op > 1)
		वापस -EINVAL;
	/* Voices 0 -  8 in OPL2 mode */
	/* Voices 0 - 17 in OPL3 mode */
	अगर (voice->voice >= ((opl3->fm_mode == SNDRV_DM_FM_MODE_OPL3) ?
			     MAX_OPL3_VOICES : MAX_OPL2_VOICES))
		वापस -EINVAL;

	/* Get रेजिस्टर array side and offset of voice */
	अगर (voice->voice < MAX_OPL2_VOICES) अणु
		/* Left रेजिस्टर block क्रम voices 0 .. 8 */
		reg_side = OPL3_LEFT;
		voice_offset = voice->voice;
	पूर्ण अन्यथा अणु
		/* Right रेजिस्टर block क्रम voices 9 .. 17 */
		reg_side = OPL3_RIGHT;
		voice_offset = voice->voice - MAX_OPL2_VOICES;
	पूर्ण
	/* Get रेजिस्टर offset of चालक */
	voice_offset = array_index_nospec(voice_offset, MAX_OPL2_VOICES);
	voice_op = array_index_nospec(voice->op, 4);
	op_offset = snd_opl3_regmap[voice_offset][voice_op];

	reg_val = 0x00;
	/* Set amplitude modulation (tremolo) effect */
	अगर (voice->am)
		reg_val |= OPL3_TREMOLO_ON;
	/* Set vibrato effect */
	अगर (voice->vibrato)
		reg_val |= OPL3_VIBRATO_ON;
	/* Set sustaining sound phase */
	अगर (voice->करो_sustain)
		reg_val |= OPL3_SUSTAIN_ON;
	/* Set keyboard scaling bit */ 
	अगर (voice->kbd_scale)
		reg_val |= OPL3_KSR;
	/* Set harmonic or frequency multiplier */
	reg_val |= voice->harmonic & OPL3_MULTIPLE_MASK;

	/* Set OPL3 AM_VIB रेजिस्टर of requested voice/चालक */ 
	opl3_reg = reg_side | (OPL3_REG_AM_VIB + op_offset);
	opl3->command(opl3, opl3_reg, reg_val);

	/* Set decreasing volume of higher notes */
	reg_val = (voice->scale_level << 6) & OPL3_KSL_MASK;
	/* Set output volume */
	reg_val |= ~voice->volume & OPL3_TOTAL_LEVEL_MASK;

	/* Set OPL3 KSL_LEVEL रेजिस्टर of requested voice/चालक */ 
	opl3_reg = reg_side | (OPL3_REG_KSL_LEVEL + op_offset);
	opl3->command(opl3, opl3_reg, reg_val);

	/* Set attack phase level */
	reg_val = (voice->attack << 4) & OPL3_ATTACK_MASK;
	/* Set decay phase level */
	reg_val |= voice->decay & OPL3_DECAY_MASK;

	/* Set OPL3 ATTACK_DECAY रेजिस्टर of requested voice/चालक */ 
	opl3_reg = reg_side | (OPL3_REG_ATTACK_DECAY + op_offset);
	opl3->command(opl3, opl3_reg, reg_val);

	/* Set sustain phase level */
	reg_val = (voice->sustain << 4) & OPL3_SUSTAIN_MASK;
	/* Set release phase level */
	reg_val |= voice->release & OPL3_RELEASE_MASK;

	/* Set OPL3 SUSTAIN_RELEASE रेजिस्टर of requested voice/चालक */ 
	opl3_reg = reg_side | (OPL3_REG_SUSTAIN_RELEASE + op_offset);
	opl3->command(opl3, opl3_reg, reg_val);

	/* Set पूर्णांकer-चालक feedback */
	reg_val = (voice->feedback << 1) & OPL3_FEEDBACK_MASK;
	/* Set पूर्णांकer-चालक connection */
	अगर (voice->connection)
		reg_val |= OPL3_CONNECTION_BIT;
	/* OPL-3 only */
	अगर (opl3->fm_mode == SNDRV_DM_FM_MODE_OPL3) अणु
		अगर (voice->left)
			reg_val |= OPL3_VOICE_TO_LEFT;
		अगर (voice->right)
			reg_val |= OPL3_VOICE_TO_RIGHT;
	पूर्ण
	/* Feedback/connection bits are applicable to voice */
	opl3_reg = reg_side | (OPL3_REG_FEEDBACK_CONNECTION + voice_offset);
	opl3->command(opl3, opl3_reg, reg_val);

	/* Select waveक्रमm */
	reg_val = voice->waveक्रमm & OPL3_WAVE_SELECT_MASK;
	opl3_reg = reg_side | (OPL3_REG_WAVE_SELECT + op_offset);
	opl3->command(opl3, opl3_reg, reg_val);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_opl3_set_params(काष्ठा snd_opl3 * opl3, काष्ठा snd_dm_fm_params * params)
अणु
	अचिन्हित अक्षर reg_val;

	reg_val = 0x00;
	/* Set keyboard split method */
	अगर (params->kbd_split)
		reg_val |= OPL3_KEYBOARD_SPLIT;
	opl3->command(opl3, OPL3_LEFT | OPL3_REG_KBD_SPLIT, reg_val);

	reg_val = 0x00;
	/* Set amplitude modulation (tremolo) depth */
	अगर (params->am_depth)
		reg_val |= OPL3_TREMOLO_DEPTH;
	/* Set vibrato depth */
	अगर (params->vib_depth)
		reg_val |= OPL3_VIBRATO_DEPTH;
	/* Set percussion mode */
	अगर (params->rhythm) अणु
		reg_val |= OPL3_PERCUSSION_ENABLE;
		opl3->rhythm = 1;
	पूर्ण अन्यथा अणु
		opl3->rhythm = 0;
	पूर्ण
	/* Play percussion instruments */
	अगर (params->bass)
		reg_val |= OPL3_BASSDRUM_ON;
	अगर (params->snare)
		reg_val |= OPL3_SNAREDRUM_ON;
	अगर (params->tomtom)
		reg_val |= OPL3_TOMTOM_ON;
	अगर (params->cymbal)
		reg_val |= OPL3_CYMBAL_ON;
	अगर (params->hihat)
		reg_val |= OPL3_HIHAT_ON;

	opl3->command(opl3, OPL3_LEFT | OPL3_REG_PERCUSSION, reg_val);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_opl3_set_mode(काष्ठा snd_opl3 * opl3, पूर्णांक mode)
अणु
	अगर ((mode == SNDRV_DM_FM_MODE_OPL3) && (opl3->hardware < OPL3_HW_OPL3))
		वापस -EINVAL;

	opl3->fm_mode = mode;
	अगर (opl3->hardware >= OPL3_HW_OPL3)
		opl3->command(opl3, OPL3_RIGHT | OPL3_REG_CONNECTION_SELECT, 0x00);	/* Clear 4-op connections */

	वापस 0;
पूर्ण

अटल पूर्णांक snd_opl3_set_connection(काष्ठा snd_opl3 * opl3, पूर्णांक connection)
अणु
	अचिन्हित अक्षर reg_val;

	/* OPL-3 only */
	अगर (opl3->fm_mode != SNDRV_DM_FM_MODE_OPL3)
		वापस -EINVAL;

	reg_val = connection & (OPL3_RIGHT_4OP_0 | OPL3_RIGHT_4OP_1 | OPL3_RIGHT_4OP_2 |
				OPL3_LEFT_4OP_0 | OPL3_LEFT_4OP_1 | OPL3_LEFT_4OP_2);
	/* Set 4-op connections */
	opl3->command(opl3, OPL3_RIGHT | OPL3_REG_CONNECTION_SELECT, reg_val);

	वापस 0;
पूर्ण

