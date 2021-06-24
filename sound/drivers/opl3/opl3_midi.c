<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) by Uros Bizjak <uros@kss-loka.si>
 *
 *  Midi synth routines क्रम OPL2/OPL3/OPL4 FM
 */

#अघोषित DEBUG_ALLOC
#अघोषित DEBUG_MIDI

#समावेश "opl3_voice.h"
#समावेश <sound/asoundef.h>

अटल व्योम snd_opl3_note_off_unsafe(व्योम *p, पूर्णांक note, पूर्णांक vel,
				     काष्ठा snd_midi_channel *chan);
/*
 * The next table looks magical, but it certainly is not. Its values have
 * been calculated as table[i]=8*log(i/64)/log(2) with an obvious exception
 * क्रम i=0. This log-table converts a linear volume-scaling (0..127) to a
 * logarithmic scaling as present in the FM-synthesizer chips. so :    Volume
 * 64 =  0 db = relative volume  0 and:    Volume 32 = -6 db = relative
 * volume -8 it was implemented as a table because it is only 128 bytes and
 * it saves a lot of log() calculations. (Rob Hooft <hooft@chem.ruu.nl>)
 */

अटल स्थिर अक्षर opl3_volume_table[128] =
अणु
	-63, -48, -40, -35, -32, -29, -27, -26,
	-24, -23, -21, -20, -19, -18, -18, -17,
	-16, -15, -15, -14, -13, -13, -12, -12,
	-11, -11, -10, -10, -10, -9, -9, -8,
	-8, -8, -7, -7, -7, -6, -6, -6,
	-5, -5, -5, -5, -4, -4, -4, -4,
	-3, -3, -3, -3, -2, -2, -2, -2,
	-2, -1, -1, -1, -1, 0, 0, 0,
	0, 0, 0, 1, 1, 1, 1, 1,
	1, 2, 2, 2, 2, 2, 2, 2,
	3, 3, 3, 3, 3, 3, 3, 4,
	4, 4, 4, 4, 4, 4, 4, 5,
	5, 5, 5, 5, 5, 5, 5, 5,
	6, 6, 6, 6, 6, 6, 6, 6,
	6, 7, 7, 7, 7, 7, 7, 7,
	7, 7, 7, 8, 8, 8, 8, 8
पूर्ण;

व्योम snd_opl3_calc_volume(अचिन्हित अक्षर *volbyte, पूर्णांक vel,
			  काष्ठा snd_midi_channel *chan)
अणु
	पूर्णांक oldvol, newvol, n;
	पूर्णांक volume;

	volume = (vel * chan->gm_volume * chan->gm_expression) / (127*127);
	अगर (volume > 127)
		volume = 127;

	oldvol = OPL3_TOTAL_LEVEL_MASK - (*volbyte & OPL3_TOTAL_LEVEL_MASK);

	newvol = opl3_volume_table[volume] + oldvol;
	अगर (newvol > OPL3_TOTAL_LEVEL_MASK)
		newvol = OPL3_TOTAL_LEVEL_MASK;
	अन्यथा अगर (newvol < 0)
		newvol = 0;

	n = OPL3_TOTAL_LEVEL_MASK - (newvol & OPL3_TOTAL_LEVEL_MASK);

	*volbyte = (*volbyte & OPL3_KSL_MASK) | (n & OPL3_TOTAL_LEVEL_MASK);
पूर्ण

/*
 * Converts the note frequency to block and fnum values क्रम the FM chip
 */
अटल स्थिर लघु opl3_note_table[16] =
अणु
	305, 323,	/* क्रम pitch bending, -2 semitones */
	343, 363, 385, 408, 432, 458, 485, 514, 544, 577, 611, 647,
	686, 726	/* क्रम pitch bending, +2 semitones */
पूर्ण;

अटल व्योम snd_opl3_calc_pitch(अचिन्हित अक्षर *fnum, अचिन्हित अक्षर *blocknum,
				पूर्णांक note, काष्ठा snd_midi_channel *chan)
अणु
	पूर्णांक block = ((note / 12) & 0x07) - 1;
	पूर्णांक idx = (note % 12) + 2;
	पूर्णांक freq;

	अगर (chan->midi_pitchbend) अणु
		पूर्णांक pitchbend = chan->midi_pitchbend;
		पूर्णांक segment;

		अगर (pitchbend < -0x2000)
			pitchbend = -0x2000;
		अगर (pitchbend > 0x1FFF)
			pitchbend = 0x1FFF;

		segment = pitchbend / 0x1000;
		freq = opl3_note_table[idx+segment];
		freq += ((opl3_note_table[idx+segment+1] - freq) *
			 (pitchbend % 0x1000)) / 0x1000;
	पूर्ण अन्यथा अणु
		freq = opl3_note_table[idx];
	पूर्ण

	*fnum = (अचिन्हित अक्षर) freq;
	*blocknum = ((freq >> 8) & OPL3_FNUM_HIGH_MASK) |
		((block << 2) & OPL3_BLOCKNUM_MASK);
पूर्ण


#अगर_घोषित DEBUG_ALLOC
अटल व्योम debug_alloc(काष्ठा snd_opl3 *opl3, अक्षर *s, पूर्णांक voice) अणु
	पूर्णांक i;
	अक्षर *str = "x.24";

	prपूर्णांकk(KERN_DEBUG "time %.5i: %s [%.2i]: ", opl3->use_समय, s, voice);
	क्रम (i = 0; i < opl3->max_voices; i++)
		prपूर्णांकk(KERN_CONT "%c", *(str + opl3->voices[i].state + 1));
	prपूर्णांकk(KERN_CONT "\n");
पूर्ण
#पूर्ण_अगर

/*
 * Get a FM voice (channel) to play a note on.
 */
अटल पूर्णांक opl3_get_voice(काष्ठा snd_opl3 *opl3, पूर्णांक instr_4op,
			  काष्ठा snd_midi_channel *chan) अणु
	पूर्णांक chan_4op_1;		/* first voice क्रम 4op instrument */
	पूर्णांक chan_4op_2;		/* second voice क्रम 4op instrument */

	काष्ठा snd_opl3_voice *vp, *vp2;
	अचिन्हित पूर्णांक voice_समय;
	पूर्णांक i;

#अगर_घोषित DEBUG_ALLOC
	अक्षर *alloc_type[3] = अणु "FREE     ", "CHEAP    ", "EXPENSIVE" पूर्ण;
#पूर्ण_अगर

	/* This is our "allocation cost" table */
	क्रमागत अणु
		FREE = 0, CHEAP, EXPENSIVE, END
	पूर्ण;

	/* Keeps track of what we are finding */
	काष्ठा best अणु
		अचिन्हित पूर्णांक समय;
		पूर्णांक voice;
	पूर्ण best[END];
	काष्ठा best *bp;

	क्रम (i = 0; i < END; i++) अणु
		best[i].समय = (अचिन्हित पूर्णांक)(-1); /* XXX MAX_?INT really */
		best[i].voice = -1;
	पूर्ण

	/* Look through all the channels क्रम the most suitable. */
	क्रम (i = 0; i < opl3->max_voices; i++) अणु
		vp = &opl3->voices[i];

		अगर (vp->state == SNDRV_OPL3_ST_NOT_AVAIL)
		  /* skip unavailable channels, allocated by
		     drum voices or by bounded 4op voices) */
			जारी;

		voice_समय = vp->समय;
		bp = best;

		chan_4op_1 = ((i < 3) || (i > 8 && i < 12));
		chan_4op_2 = ((i > 2 && i < 6) || (i > 11 && i < 15));
		अगर (instr_4op) अणु
			/* allocate 4op voice */
			/* skip channels unavailable to 4op instrument */
			अगर (!chan_4op_1)
				जारी;

			अगर (vp->state)
				/* समाप्त one voice, CHEAP */
				bp++;
			/* get state of bounded 2op channel
			   to be allocated क्रम 4op instrument */
			vp2 = &opl3->voices[i + 3];
			अगर (vp2->state == SNDRV_OPL3_ST_ON_2OP) अणु
				/* समाप्त two voices, EXPENSIVE */
				bp++;
				voice_समय = (voice_समय > vp->समय) ?
					voice_समय : vp->समय;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* allocate 2op voice */
			अगर ((chan_4op_1) || (chan_4op_2))
				/* use bounded channels क्रम 2op, CHEAP */
				bp++;
			अन्यथा अगर (vp->state)
				/* समाप्त one voice on 2op channel, CHEAP */
				bp++;
			/* उठाओ समाप्त cost to EXPENSIVE क्रम all channels */
			अगर (vp->state)
				bp++;
		पूर्ण
		अगर (voice_समय < bp->समय) अणु
			bp->समय = voice_समय;
			bp->voice = i;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < END; i++) अणु
		अगर (best[i].voice >= 0) अणु
#अगर_घोषित DEBUG_ALLOC
			prपूर्णांकk(KERN_DEBUG "%s %iop allocation on voice %i\n",
			       alloc_type[i], instr_4op ? 4 : 2,
			       best[i].voice);
#पूर्ण_अगर
			वापस best[i].voice;
		पूर्ण
	पूर्ण
	/* not found */
	वापस -1;
पूर्ण

/* ------------------------------ */

/*
 * System समयr पूर्णांकerrupt function
 */
व्योम snd_opl3_समयr_func(काष्ठा समयr_list *t)
अणु

	काष्ठा snd_opl3 *opl3 = from_समयr(opl3, t, tlist);
	अचिन्हित दीर्घ flags;
	पूर्णांक again = 0;
	पूर्णांक i;

	spin_lock_irqsave(&opl3->voice_lock, flags);
	क्रम (i = 0; i < opl3->max_voices; i++) अणु
		काष्ठा snd_opl3_voice *vp = &opl3->voices[i];
		अगर (vp->state > 0 && vp->note_off_check) अणु
			अगर (vp->note_off == jअगरfies)
				snd_opl3_note_off_unsafe(opl3, vp->note, 0,
							 vp->chan);
			अन्यथा
				again++;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&opl3->voice_lock, flags);

	spin_lock_irqsave(&opl3->sys_समयr_lock, flags);
	अगर (again)
		mod_समयr(&opl3->tlist, jअगरfies + 1);	/* invoke again */
	अन्यथा
		opl3->sys_समयr_status = 0;
	spin_unlock_irqrestore(&opl3->sys_समयr_lock, flags);
पूर्ण

/*
 * Start प्रणाली समयr
 */
अटल व्योम snd_opl3_start_समयr(काष्ठा snd_opl3 *opl3)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&opl3->sys_समयr_lock, flags);
	अगर (! opl3->sys_समयr_status) अणु
		mod_समयr(&opl3->tlist, jअगरfies + 1);
		opl3->sys_समयr_status = 1;
	पूर्ण
	spin_unlock_irqrestore(&opl3->sys_समयr_lock, flags);
पूर्ण

/* ------------------------------ */


अटल स्थिर पूर्णांक snd_opl3_oss_map[MAX_OPL3_VOICES] = अणु
	0, 1, 2, 9, 10, 11, 6, 7, 8, 15, 16, 17, 3, 4 ,5, 12, 13, 14
पूर्ण;

/*
 * Start a note.
 */
व्योम snd_opl3_note_on(व्योम *p, पूर्णांक note, पूर्णांक vel, काष्ठा snd_midi_channel *chan)
अणु
	काष्ठा snd_opl3 *opl3;
	पूर्णांक instr_4op;

	पूर्णांक voice;
	काष्ठा snd_opl3_voice *vp, *vp2;
	अचिन्हित लघु connect_mask;
	अचिन्हित अक्षर connection;
	अचिन्हित अक्षर vol_op[4];

	पूर्णांक extra_prg = 0;

	अचिन्हित लघु reg_side;
	अचिन्हित अक्षर op_offset;
	अचिन्हित अक्षर voice_offset;
	अचिन्हित लघु opl3_reg;
	अचिन्हित अक्षर reg_val;
	अचिन्हित अक्षर prg, bank;

	पूर्णांक key = note;
	अचिन्हित अक्षर fnum, blocknum;
	पूर्णांक i;

	काष्ठा fm_patch *patch;
	काष्ठा fm_instrument *fm;
	अचिन्हित दीर्घ flags;

	opl3 = p;

#अगर_घोषित DEBUG_MIDI
	snd_prपूर्णांकk(KERN_DEBUG "Note on, ch %i, inst %i, note %i, vel %i\n",
		   chan->number, chan->midi_program, note, vel);
#पूर्ण_अगर

	/* in SYNTH mode, application takes care of voices */
	/* in SEQ mode, drum voice numbers are notes on drum channel */
	अगर (opl3->synth_mode == SNDRV_OPL3_MODE_SEQ) अणु
		अगर (chan->drum_channel) अणु
			/* percussion instruments are located in bank 128 */
			bank = 128;
			prg = note;
		पूर्ण अन्यथा अणु
			bank = chan->gm_bank_select;
			prg = chan->midi_program;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Prepare क्रम OSS mode */
		अगर (chan->number >= MAX_OPL3_VOICES)
			वापस;

		/* OSS instruments are located in bank 127 */
		bank = 127;
		prg = chan->midi_program;
	पूर्ण

	spin_lock_irqsave(&opl3->voice_lock, flags);

	अगर (use_पूर्णांकernal_drums) अणु
		snd_opl3_drum_चयन(opl3, note, vel, 1, chan);
		spin_unlock_irqrestore(&opl3->voice_lock, flags);
		वापस;
	पूर्ण

 __extra_prg:
	patch = snd_opl3_find_patch(opl3, prg, bank, 0);
	अगर (!patch) अणु
		spin_unlock_irqrestore(&opl3->voice_lock, flags);
		वापस;
	पूर्ण

	fm = &patch->inst;
	चयन (patch->type) अणु
	हाल FM_PATCH_OPL2:
		instr_4op = 0;
		अवरोध;
	हाल FM_PATCH_OPL3:
		अगर (opl3->hardware >= OPL3_HW_OPL3) अणु
			instr_4op = 1;
			अवरोध;
		पूर्ण
		fallthrough;
	शेष:
		spin_unlock_irqrestore(&opl3->voice_lock, flags);
		वापस;
	पूर्ण
#अगर_घोषित DEBUG_MIDI
	snd_prपूर्णांकk(KERN_DEBUG "  --> OPL%i instrument: %s\n",
		   instr_4op ? 3 : 2, patch->name);
#पूर्ण_अगर
	/* in SYNTH mode, application takes care of voices */
	/* in SEQ mode, allocate voice on मुक्त OPL3 channel */
	अगर (opl3->synth_mode == SNDRV_OPL3_MODE_SEQ) अणु
		voice = opl3_get_voice(opl3, instr_4op, chan);
	पूर्ण अन्यथा अणु
		/* remap OSS voice */
		voice = snd_opl3_oss_map[chan->number];		
	पूर्ण

	अगर (voice < 0) अणु
		spin_unlock_irqrestore(&opl3->voice_lock, flags);
		वापस;
	पूर्ण

	अगर (voice < MAX_OPL2_VOICES) अणु
		/* Left रेजिस्टर block क्रम voices 0 .. 8 */
		reg_side = OPL3_LEFT;
		voice_offset = voice;
		connect_mask = (OPL3_LEFT_4OP_0 << voice_offset) & 0x07;
	पूर्ण अन्यथा अणु
		/* Right रेजिस्टर block क्रम voices 9 .. 17 */
		reg_side = OPL3_RIGHT;
		voice_offset = voice - MAX_OPL2_VOICES;
		connect_mask = (OPL3_RIGHT_4OP_0 << voice_offset) & 0x38;
	पूर्ण

	/* समाप्त voice on channel */
	vp = &opl3->voices[voice];
	अगर (vp->state > 0) अणु
		opl3_reg = reg_side | (OPL3_REG_KEYON_BLOCK + voice_offset);
		reg_val = vp->keyon_reg & ~OPL3_KEYON_BIT;
		opl3->command(opl3, opl3_reg, reg_val);
	पूर्ण
	अगर (instr_4op) अणु
		vp2 = &opl3->voices[voice + 3];
		अगर (vp->state > 0) अणु
			opl3_reg = reg_side | (OPL3_REG_KEYON_BLOCK +
					       voice_offset + 3);
			reg_val = vp->keyon_reg & ~OPL3_KEYON_BIT;
			opl3->command(opl3, opl3_reg, reg_val);
		पूर्ण
	पूर्ण

	/* set connection रेजिस्टर */
	अगर (instr_4op) अणु
		अगर ((opl3->connection_reg ^ connect_mask) & connect_mask) अणु
			opl3->connection_reg |= connect_mask;
			/* set connection bit */
			opl3_reg = OPL3_RIGHT | OPL3_REG_CONNECTION_SELECT;
			opl3->command(opl3, opl3_reg, opl3->connection_reg);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((opl3->connection_reg ^ ~connect_mask) & connect_mask) अणु
			opl3->connection_reg &= ~connect_mask;
			/* clear connection bit */
			opl3_reg = OPL3_RIGHT | OPL3_REG_CONNECTION_SELECT;
			opl3->command(opl3, opl3_reg, opl3->connection_reg);
		पूर्ण
	पूर्ण

#अगर_घोषित DEBUG_MIDI
	snd_prपूर्णांकk(KERN_DEBUG "  --> setting OPL3 connection: 0x%x\n",
		   opl3->connection_reg);
#पूर्ण_अगर
	/*
	 * calculate volume depending on connection
	 * between FM चालकs (see include/opl3.h)
	 */
	क्रम (i = 0; i < (instr_4op ? 4 : 2); i++)
		vol_op[i] = fm->op[i].ksl_level;

	connection = fm->feedback_connection[0] & 0x01;
	अगर (instr_4op) अणु
		connection <<= 1;
		connection |= fm->feedback_connection[1] & 0x01;

		snd_opl3_calc_volume(&vol_op[3], vel, chan);
		चयन (connection) अणु
		हाल 0x03:
			snd_opl3_calc_volume(&vol_op[2], vel, chan);
			fallthrough;
		हाल 0x02:
			snd_opl3_calc_volume(&vol_op[0], vel, chan);
			अवरोध;
		हाल 0x01:
			snd_opl3_calc_volume(&vol_op[1], vel, chan);
		पूर्ण
	पूर्ण अन्यथा अणु
		snd_opl3_calc_volume(&vol_op[1], vel, chan);
		अगर (connection)
			snd_opl3_calc_volume(&vol_op[0], vel, chan);
	पूर्ण

	/* Program the FM voice अक्षरacteristics */
	क्रम (i = 0; i < (instr_4op ? 4 : 2); i++) अणु
#अगर_घोषित DEBUG_MIDI
		snd_prपूर्णांकk(KERN_DEBUG "  --> programming operator %i\n", i);
#पूर्ण_अगर
		op_offset = snd_opl3_regmap[voice_offset][i];

		/* Set OPL3 AM_VIB रेजिस्टर of requested voice/चालक */ 
		reg_val = fm->op[i].am_vib;
		opl3_reg = reg_side | (OPL3_REG_AM_VIB + op_offset);
		opl3->command(opl3, opl3_reg, reg_val);

		/* Set OPL3 KSL_LEVEL रेजिस्टर of requested voice/चालक */ 
		reg_val = vol_op[i];
		opl3_reg = reg_side | (OPL3_REG_KSL_LEVEL + op_offset);
		opl3->command(opl3, opl3_reg, reg_val);

		/* Set OPL3 ATTACK_DECAY रेजिस्टर of requested voice/चालक */ 
		reg_val = fm->op[i].attack_decay;
		opl3_reg = reg_side | (OPL3_REG_ATTACK_DECAY + op_offset);
		opl3->command(opl3, opl3_reg, reg_val);

		/* Set OPL3 SUSTAIN_RELEASE रेजिस्टर of requested voice/चालक */ 
		reg_val = fm->op[i].sustain_release;
		opl3_reg = reg_side | (OPL3_REG_SUSTAIN_RELEASE + op_offset);
		opl3->command(opl3, opl3_reg, reg_val);

		/* Select waveक्रमm */
		reg_val = fm->op[i].wave_select;
		opl3_reg = reg_side | (OPL3_REG_WAVE_SELECT + op_offset);
		opl3->command(opl3, opl3_reg, reg_val);
	पूर्ण

	/* Set चालक feedback and 2op पूर्णांकer-चालक connection */
	reg_val = fm->feedback_connection[0];
	/* Set output voice connection */
	reg_val |= OPL3_STEREO_BITS;
	अगर (chan->gm_pan < 43)
		reg_val &= ~OPL3_VOICE_TO_RIGHT;
	अगर (chan->gm_pan > 85)
		reg_val &= ~OPL3_VOICE_TO_LEFT;
	opl3_reg = reg_side | (OPL3_REG_FEEDBACK_CONNECTION + voice_offset);
	opl3->command(opl3, opl3_reg, reg_val);

	अगर (instr_4op) अणु
		/* Set 4op पूर्णांकer-चालक connection */
		reg_val = fm->feedback_connection[1] & OPL3_CONNECTION_BIT;
		/* Set output voice connection */
		reg_val |= OPL3_STEREO_BITS;
		अगर (chan->gm_pan < 43)
			reg_val &= ~OPL3_VOICE_TO_RIGHT;
		अगर (chan->gm_pan > 85)
			reg_val &= ~OPL3_VOICE_TO_LEFT;
		opl3_reg = reg_side | (OPL3_REG_FEEDBACK_CONNECTION +
				       voice_offset + 3);
		opl3->command(opl3, opl3_reg, reg_val);
	पूर्ण

	/*
	 * Special treaपंचांगent of percussion notes क्रम fm:
	 * Requested pitch is really program, and pitch क्रम
	 * device is whatever was specअगरied in the patch library.
	 */
	अगर (fm->fix_key)
		note = fm->fix_key;
	/*
	 * use transpose अगर defined in patch library
	 */
	अगर (fm->trnsps)
		note += (fm->trnsps - 64);

	snd_opl3_calc_pitch(&fnum, &blocknum, note, chan);

	/* Set OPL3 FNUM_LOW रेजिस्टर of requested voice */
	opl3_reg = reg_side | (OPL3_REG_FNUM_LOW + voice_offset);
	opl3->command(opl3, opl3_reg, fnum);

	opl3->voices[voice].keyon_reg = blocknum;

	/* Set output sound flag */
	blocknum |= OPL3_KEYON_BIT;

#अगर_घोषित DEBUG_MIDI
	snd_prपूर्णांकk(KERN_DEBUG "  --> trigger voice %i\n", voice);
#पूर्ण_अगर
	/* Set OPL3 KEYON_BLOCK रेजिस्टर of requested voice */ 
	opl3_reg = reg_side | (OPL3_REG_KEYON_BLOCK + voice_offset);
	opl3->command(opl3, opl3_reg, blocknum);

	/* समाप्त note after fixed duration (in centiseconds) */
	अगर (fm->fix_dur) अणु
		opl3->voices[voice].note_off = jअगरfies +
			(fm->fix_dur * HZ) / 100;
		snd_opl3_start_समयr(opl3);
		opl3->voices[voice].note_off_check = 1;
	पूर्ण अन्यथा
		opl3->voices[voice].note_off_check = 0;

	/* get extra pgm, but aव्योम possible loops */
	extra_prg = (extra_prg) ? 0 : fm->modes;

	/* करो the bookkeeping */
	vp->समय = opl3->use_समय++;
	vp->note = key;
	vp->chan = chan;

	अगर (instr_4op) अणु
		vp->state = SNDRV_OPL3_ST_ON_4OP;

		vp2 = &opl3->voices[voice + 3];
		vp2->समय = opl3->use_समय++;
		vp2->note = key;
		vp2->chan = chan;
		vp2->state = SNDRV_OPL3_ST_NOT_AVAIL;
	पूर्ण अन्यथा अणु
		अगर (vp->state == SNDRV_OPL3_ST_ON_4OP) अणु
			/* 4op समाप्तed by 2op, release bounded voice */
			vp2 = &opl3->voices[voice + 3];
			vp2->समय = opl3->use_समय++;
			vp2->state = SNDRV_OPL3_ST_OFF;
		पूर्ण
		vp->state = SNDRV_OPL3_ST_ON_2OP;
	पूर्ण

#अगर_घोषित DEBUG_ALLOC
	debug_alloc(opl3, "note on ", voice);
#पूर्ण_अगर

	/* allocate extra program अगर specअगरied in patch library */
	अगर (extra_prg) अणु
		अगर (extra_prg > 128) अणु
			bank = 128;
			/* percussions start at 35 */
			prg = extra_prg - 128 + 35 - 1;
		पूर्ण अन्यथा अणु
			bank = 0;
			prg = extra_prg - 1;
		पूर्ण
#अगर_घोषित DEBUG_MIDI
		snd_prपूर्णांकk(KERN_DEBUG " *** allocating extra program\n");
#पूर्ण_अगर
		जाओ __extra_prg;
	पूर्ण
	spin_unlock_irqrestore(&opl3->voice_lock, flags);
पूर्ण

अटल व्योम snd_opl3_समाप्त_voice(काष्ठा snd_opl3 *opl3, पूर्णांक voice)
अणु
	अचिन्हित लघु reg_side;
	अचिन्हित अक्षर voice_offset;
	अचिन्हित लघु opl3_reg;

	काष्ठा snd_opl3_voice *vp, *vp2;

	अगर (snd_BUG_ON(voice >= MAX_OPL3_VOICES))
		वापस;

	vp = &opl3->voices[voice];
	अगर (voice < MAX_OPL2_VOICES) अणु
		/* Left रेजिस्टर block क्रम voices 0 .. 8 */
		reg_side = OPL3_LEFT;
		voice_offset = voice;
	पूर्ण अन्यथा अणु
		/* Right रेजिस्टर block क्रम voices 9 .. 17 */
		reg_side = OPL3_RIGHT;
		voice_offset = voice - MAX_OPL2_VOICES;
	पूर्ण

	/* समाप्त voice */
#अगर_घोषित DEBUG_MIDI
	snd_prपूर्णांकk(KERN_DEBUG "  --> kill voice %i\n", voice);
#पूर्ण_अगर
	opl3_reg = reg_side | (OPL3_REG_KEYON_BLOCK + voice_offset);
	/* clear Key ON bit */
	opl3->command(opl3, opl3_reg, vp->keyon_reg);

	/* करो the bookkeeping */
	vp->समय = opl3->use_समय++;

	अगर (vp->state == SNDRV_OPL3_ST_ON_4OP) अणु
		vp2 = &opl3->voices[voice + 3];

		vp2->समय = opl3->use_समय++;
		vp2->state = SNDRV_OPL3_ST_OFF;
	पूर्ण
	vp->state = SNDRV_OPL3_ST_OFF;
#अगर_घोषित DEBUG_ALLOC
	debug_alloc(opl3, "note off", voice);
#पूर्ण_अगर

पूर्ण

/*
 * Release a note in response to a midi note off.
 */
अटल व्योम snd_opl3_note_off_unsafe(व्योम *p, पूर्णांक note, पूर्णांक vel,
				     काष्ठा snd_midi_channel *chan)
अणु
  	काष्ठा snd_opl3 *opl3;

	पूर्णांक voice;
	काष्ठा snd_opl3_voice *vp;

	opl3 = p;

#अगर_घोषित DEBUG_MIDI
	snd_prपूर्णांकk(KERN_DEBUG "Note off, ch %i, inst %i, note %i\n",
		   chan->number, chan->midi_program, note);
#पूर्ण_अगर

	अगर (opl3->synth_mode == SNDRV_OPL3_MODE_SEQ) अणु
		अगर (chan->drum_channel && use_पूर्णांकernal_drums) अणु
			snd_opl3_drum_चयन(opl3, note, vel, 0, chan);
			वापस;
		पूर्ण
		/* this loop will hopefully समाप्त all extra voices, because
		   they are grouped by the same channel and note values */
		क्रम (voice = 0; voice < opl3->max_voices; voice++) अणु
			vp = &opl3->voices[voice];
			अगर (vp->state > 0 && vp->chan == chan && vp->note == note) अणु
				snd_opl3_समाप्त_voice(opl3, voice);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* remap OSS voices */
		अगर (chan->number < MAX_OPL3_VOICES) अणु
			voice = snd_opl3_oss_map[chan->number];		
			snd_opl3_समाप्त_voice(opl3, voice);
		पूर्ण
	पूर्ण
पूर्ण

व्योम snd_opl3_note_off(व्योम *p, पूर्णांक note, पूर्णांक vel,
		       काष्ठा snd_midi_channel *chan)
अणु
	काष्ठा snd_opl3 *opl3 = p;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&opl3->voice_lock, flags);
	snd_opl3_note_off_unsafe(p, note, vel, chan);
	spin_unlock_irqrestore(&opl3->voice_lock, flags);
पूर्ण

/*
 * key pressure change
 */
व्योम snd_opl3_key_press(व्योम *p, पूर्णांक note, पूर्णांक vel, काष्ठा snd_midi_channel *chan)
अणु
#अगर_घोषित DEBUG_MIDI
	snd_prपूर्णांकk(KERN_DEBUG "Key pressure, ch#: %i, inst#: %i\n",
		   chan->number, chan->midi_program);
#पूर्ण_अगर
पूर्ण

/*
 * terminate note
 */
व्योम snd_opl3_terminate_note(व्योम *p, पूर्णांक note, काष्ठा snd_midi_channel *chan)
अणु
#अगर_घोषित DEBUG_MIDI
	snd_prपूर्णांकk(KERN_DEBUG "Terminate note, ch#: %i, inst#: %i\n",
		   chan->number, chan->midi_program);
#पूर्ण_अगर
पूर्ण

अटल व्योम snd_opl3_update_pitch(काष्ठा snd_opl3 *opl3, पूर्णांक voice)
अणु
	अचिन्हित लघु reg_side;
	अचिन्हित अक्षर voice_offset;
	अचिन्हित लघु opl3_reg;

	अचिन्हित अक्षर fnum, blocknum;

	काष्ठा snd_opl3_voice *vp;

	अगर (snd_BUG_ON(voice >= MAX_OPL3_VOICES))
		वापस;

	vp = &opl3->voices[voice];
	अगर (vp->chan == शून्य)
		वापस; /* not allocated? */

	अगर (voice < MAX_OPL2_VOICES) अणु
		/* Left रेजिस्टर block क्रम voices 0 .. 8 */
		reg_side = OPL3_LEFT;
		voice_offset = voice;
	पूर्ण अन्यथा अणु
		/* Right रेजिस्टर block क्रम voices 9 .. 17 */
		reg_side = OPL3_RIGHT;
		voice_offset = voice - MAX_OPL2_VOICES;
	पूर्ण

	snd_opl3_calc_pitch(&fnum, &blocknum, vp->note, vp->chan);

	/* Set OPL3 FNUM_LOW रेजिस्टर of requested voice */
	opl3_reg = reg_side | (OPL3_REG_FNUM_LOW + voice_offset);
	opl3->command(opl3, opl3_reg, fnum);

	vp->keyon_reg = blocknum;

	/* Set output sound flag */
	blocknum |= OPL3_KEYON_BIT;

	/* Set OPL3 KEYON_BLOCK रेजिस्टर of requested voice */ 
	opl3_reg = reg_side | (OPL3_REG_KEYON_BLOCK + voice_offset);
	opl3->command(opl3, opl3_reg, blocknum);

	vp->समय = opl3->use_समय++;
पूर्ण

/*
 * Update voice pitch controller
 */
अटल व्योम snd_opl3_pitch_ctrl(काष्ठा snd_opl3 *opl3, काष्ठा snd_midi_channel *chan)
अणु
	पूर्णांक voice;
	काष्ठा snd_opl3_voice *vp;

	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&opl3->voice_lock, flags);

	अगर (opl3->synth_mode == SNDRV_OPL3_MODE_SEQ) अणु
		क्रम (voice = 0; voice < opl3->max_voices; voice++) अणु
			vp = &opl3->voices[voice];
			अगर (vp->state > 0 && vp->chan == chan) अणु
				snd_opl3_update_pitch(opl3, voice);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* remap OSS voices */
		अगर (chan->number < MAX_OPL3_VOICES) अणु
			voice = snd_opl3_oss_map[chan->number];		
			snd_opl3_update_pitch(opl3, voice);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&opl3->voice_lock, flags);
पूर्ण

/*
 * Deal with a controller type event.  This includes all types of
 * control events, not just the midi controllers
 */
व्योम snd_opl3_control(व्योम *p, पूर्णांक type, काष्ठा snd_midi_channel *chan)
अणु
  	काष्ठा snd_opl3 *opl3;

	opl3 = p;
#अगर_घोषित DEBUG_MIDI
	snd_prपूर्णांकk(KERN_DEBUG "Controller, TYPE = %i, ch#: %i, inst#: %i\n",
		   type, chan->number, chan->midi_program);
#पूर्ण_अगर

	चयन (type) अणु
	हाल MIDI_CTL_MSB_MODWHEEL:
		अगर (chan->control[MIDI_CTL_MSB_MODWHEEL] > 63)
			opl3->drum_reg |= OPL3_VIBRATO_DEPTH;
		अन्यथा 
			opl3->drum_reg &= ~OPL3_VIBRATO_DEPTH;
		opl3->command(opl3, OPL3_LEFT | OPL3_REG_PERCUSSION,
				 opl3->drum_reg);
		अवरोध;
	हाल MIDI_CTL_E2_TREMOLO_DEPTH:
		अगर (chan->control[MIDI_CTL_E2_TREMOLO_DEPTH] > 63)
			opl3->drum_reg |= OPL3_TREMOLO_DEPTH;
		अन्यथा 
			opl3->drum_reg &= ~OPL3_TREMOLO_DEPTH;
		opl3->command(opl3, OPL3_LEFT | OPL3_REG_PERCUSSION,
				 opl3->drum_reg);
		अवरोध;
	हाल MIDI_CTL_PITCHBEND:
		snd_opl3_pitch_ctrl(opl3, chan);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * NRPN events
 */
व्योम snd_opl3_nrpn(व्योम *p, काष्ठा snd_midi_channel *chan,
		   काष्ठा snd_midi_channel_set *chset)
अणु
#अगर_घोषित DEBUG_MIDI
	snd_prपूर्णांकk(KERN_DEBUG "NRPN, ch#: %i, inst#: %i\n",
		   chan->number, chan->midi_program);
#पूर्ण_अगर
पूर्ण

/*
 * receive sysex
 */
व्योम snd_opl3_sysex(व्योम *p, अचिन्हित अक्षर *buf, पूर्णांक len,
		    पूर्णांक parsed, काष्ठा snd_midi_channel_set *chset)
अणु
#अगर_घोषित DEBUG_MIDI
	snd_prपूर्णांकk(KERN_DEBUG "SYSEX\n");
#पूर्ण_अगर
पूर्ण
