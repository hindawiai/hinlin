<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  GM/GS/XG midi module.
 *
 *  Copyright (C) 1999 Steve Ratclअगरfe
 *
 *  Based on awe_wave.c by Takashi Iwai
 */
/*
 * This module is used to keep track of the current midi state.
 * It can be used क्रम drivers that are required to emulate midi when
 * the hardware करोesn't.
 *
 * It was written क्रम a AWE64 driver, but there should be no AWE specअगरic
 * code in here.  If there is it should be reported as a bug.
 */

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/seq_kernel.h>
#समावेश <sound/seq_midi_emul.h>
#समावेश <sound/initval.h>
#समावेश <sound/asoundef.h>

MODULE_AUTHOR("Takashi Iwai / Steve Ratcliffe");
MODULE_DESCRIPTION("Advanced Linux Sound Architecture sequencer MIDI emulation.");
MODULE_LICENSE("GPL");

/* Prototypes क्रम अटल functions */
अटल व्योम note_off(स्थिर काष्ठा snd_midi_op *ops, व्योम *drv,
		     काष्ठा snd_midi_channel *chan,
		     पूर्णांक note, पूर्णांक vel);
अटल व्योम करो_control(स्थिर काष्ठा snd_midi_op *ops, व्योम *निजी,
		       काष्ठा snd_midi_channel_set *chset,
		       काष्ठा snd_midi_channel *chan,
		       पूर्णांक control, पूर्णांक value);
अटल व्योम rpn(स्थिर काष्ठा snd_midi_op *ops, व्योम *drv,
		काष्ठा snd_midi_channel *chan,
		काष्ठा snd_midi_channel_set *chset);
अटल व्योम nrpn(स्थिर काष्ठा snd_midi_op *ops, व्योम *drv,
		 काष्ठा snd_midi_channel *chan,
		 काष्ठा snd_midi_channel_set *chset);
अटल व्योम sysex(स्थिर काष्ठा snd_midi_op *ops, व्योम *निजी,
		  अचिन्हित अक्षर *sysex,
		  पूर्णांक len, काष्ठा snd_midi_channel_set *chset);
अटल व्योम all_sounds_off(स्थिर काष्ठा snd_midi_op *ops, व्योम *निजी,
			   काष्ठा snd_midi_channel *chan);
अटल व्योम all_notes_off(स्थिर काष्ठा snd_midi_op *ops, व्योम *निजी,
			  काष्ठा snd_midi_channel *chan);
अटल व्योम snd_midi_reset_controllers(काष्ठा snd_midi_channel *chan);
अटल व्योम reset_all_channels(काष्ठा snd_midi_channel_set *chset);


/*
 * Process an event in a driver independent way.  This means dealing
 * with RPN, NRPN, SysEx etc that are defined क्रम common midi applications
 * such as GM, GS and XG.
 * There modes that this module will run in are:
 *   Generic MIDI - no पूर्णांकerpretation at all, it will just save current values
 *                  of controllers etc.
 *   GM - You can use all gm_ prefixed elements of chan.  Controls, RPN, NRPN,
 *        SysEx will be पूर्णांकerpreded as defined in General Midi.
 *   GS - You can use all gs_ prefixed elements of chan. Codes क्रम GS will be
 *        पूर्णांकerpreted.
 *   XG - You can use all xg_ prefixed elements of chan.  Codes क्रम XG will
 *        be पूर्णांकerpreted.
 */
व्योम
snd_midi_process_event(स्थिर काष्ठा snd_midi_op *ops,
		       काष्ठा snd_seq_event *ev,
		       काष्ठा snd_midi_channel_set *chanset)
अणु
	काष्ठा snd_midi_channel *chan;
	व्योम *drv;
	पूर्णांक dest_channel = 0;

	अगर (ev == शून्य || chanset == शून्य) अणु
		pr_debug("ALSA: seq_midi_emul: ev or chanbase NULL (snd_midi_process_event)\n");
		वापस;
	पूर्ण
	अगर (chanset->channels == शून्य)
		वापस;

	अगर (snd_seq_ev_is_channel_type(ev)) अणु
		dest_channel = ev->data.note.channel;
		अगर (dest_channel >= chanset->max_channels) अणु
			pr_debug("ALSA: seq_midi_emul: dest channel is %d, max is %d\n",
				   dest_channel, chanset->max_channels);
			वापस;
		पूर्ण
	पूर्ण

	chan = chanset->channels + dest_channel;
	drv  = chanset->निजी_data;

	/* EVENT_NOTE should be processed beक्रमe queued */
	अगर (ev->type == SNDRV_SEQ_EVENT_NOTE)
		वापस;

	/* Make sure that we करोn't have a note on that should really be
	 * a note off */
	अगर (ev->type == SNDRV_SEQ_EVENT_NOTEON && ev->data.note.velocity == 0)
		ev->type = SNDRV_SEQ_EVENT_NOTखातापूर्णF;

	/* Make sure the note is within array range */
	अगर (ev->type == SNDRV_SEQ_EVENT_NOTEON ||
	    ev->type == SNDRV_SEQ_EVENT_NOTखातापूर्णF ||
	    ev->type == SNDRV_SEQ_EVENT_KEYPRESS) अणु
		अगर (ev->data.note.note >= 128)
			वापस;
	पूर्ण

	चयन (ev->type) अणु
	हाल SNDRV_SEQ_EVENT_NOTEON:
		अगर (chan->note[ev->data.note.note] & SNDRV_MIDI_NOTE_ON) अणु
			अगर (ops->note_off)
				ops->note_off(drv, ev->data.note.note, 0, chan);
		पूर्ण
		chan->note[ev->data.note.note] = SNDRV_MIDI_NOTE_ON;
		अगर (ops->note_on)
			ops->note_on(drv, ev->data.note.note, ev->data.note.velocity, chan);
		अवरोध;
	हाल SNDRV_SEQ_EVENT_NOTखातापूर्णF:
		अगर (! (chan->note[ev->data.note.note] & SNDRV_MIDI_NOTE_ON))
			अवरोध;
		अगर (ops->note_off)
			note_off(ops, drv, chan, ev->data.note.note, ev->data.note.velocity);
		अवरोध;
	हाल SNDRV_SEQ_EVENT_KEYPRESS:
		अगर (ops->key_press)
			ops->key_press(drv, ev->data.note.note, ev->data.note.velocity, chan);
		अवरोध;
	हाल SNDRV_SEQ_EVENT_CONTROLLER:
		करो_control(ops, drv, chanset, chan,
			   ev->data.control.param, ev->data.control.value);
		अवरोध;
	हाल SNDRV_SEQ_EVENT_PGMCHANGE:
		chan->midi_program = ev->data.control.value;
		अवरोध;
	हाल SNDRV_SEQ_EVENT_PITCHBEND:
		chan->midi_pitchbend = ev->data.control.value;
		अगर (ops->control)
			ops->control(drv, MIDI_CTL_PITCHBEND, chan);
		अवरोध;
	हाल SNDRV_SEQ_EVENT_CHANPRESS:
		chan->midi_pressure = ev->data.control.value;
		अगर (ops->control)
			ops->control(drv, MIDI_CTL_CHAN_PRESSURE, chan);
		अवरोध;
	हाल SNDRV_SEQ_EVENT_CONTROL14:
		/* Best guess is that this is any of the 14 bit controller values */
		अगर (ev->data.control.param < 32) अणु
			/* set low part first */
			chan->control[ev->data.control.param + 32] =
				ev->data.control.value & 0x7f;
			करो_control(ops, drv, chanset, chan,
				   ev->data.control.param,
				   ((ev->data.control.value>>7) & 0x7f));
		पूर्ण अन्यथा
			करो_control(ops, drv, chanset, chan,
				   ev->data.control.param,
				   ev->data.control.value);
		अवरोध;
	हाल SNDRV_SEQ_EVENT_NONREGPARAM:
		/* Break it back पूर्णांकo its controller values */
		chan->param_type = SNDRV_MIDI_PARAM_TYPE_NONREGISTERED;
		chan->control[MIDI_CTL_MSB_DATA_ENTRY]
			= (ev->data.control.value >> 7) & 0x7f;
		chan->control[MIDI_CTL_LSB_DATA_ENTRY]
			= ev->data.control.value & 0x7f;
		chan->control[MIDI_CTL_NONREG_PARM_NUM_MSB]
			= (ev->data.control.param >> 7) & 0x7f;
		chan->control[MIDI_CTL_NONREG_PARM_NUM_LSB]
			= ev->data.control.param & 0x7f;
		nrpn(ops, drv, chan, chanset);
		अवरोध;
	हाल SNDRV_SEQ_EVENT_REGPARAM:
		/* Break it back पूर्णांकo its controller values */
		chan->param_type = SNDRV_MIDI_PARAM_TYPE_REGISTERED;
		chan->control[MIDI_CTL_MSB_DATA_ENTRY]
			= (ev->data.control.value >> 7) & 0x7f;
		chan->control[MIDI_CTL_LSB_DATA_ENTRY]
			= ev->data.control.value & 0x7f;
		chan->control[MIDI_CTL_REGIST_PARM_NUM_MSB]
			= (ev->data.control.param >> 7) & 0x7f;
		chan->control[MIDI_CTL_REGIST_PARM_NUM_LSB]
			= ev->data.control.param & 0x7f;
		rpn(ops, drv, chan, chanset);
		अवरोध;
	हाल SNDRV_SEQ_EVENT_SYSEX:
		अगर ((ev->flags & SNDRV_SEQ_EVENT_LENGTH_MASK) == SNDRV_SEQ_EVENT_LENGTH_VARIABLE) अणु
			अचिन्हित अक्षर sysexbuf[64];
			पूर्णांक len;
			len = snd_seq_expand_var_event(ev, माप(sysexbuf), sysexbuf, 1, 0);
			अगर (len > 0)
				sysex(ops, drv, sysexbuf, len, chanset);
		पूर्ण
		अवरोध;
	हाल SNDRV_SEQ_EVENT_SONGPOS:
	हाल SNDRV_SEQ_EVENT_SONGSEL:
	हाल SNDRV_SEQ_EVENT_CLOCK:
	हाल SNDRV_SEQ_EVENT_START:
	हाल SNDRV_SEQ_EVENT_CONTINUE:
	हाल SNDRV_SEQ_EVENT_STOP:
	हाल SNDRV_SEQ_EVENT_QFRAME:
	हाल SNDRV_SEQ_EVENT_TEMPO:
	हाल SNDRV_SEQ_EVENT_TIMESIGN:
	हाल SNDRV_SEQ_EVENT_KEYSIGN:
		जाओ not_yet;
	हाल SNDRV_SEQ_EVENT_SENSING:
		अवरोध;
	हाल SNDRV_SEQ_EVENT_CLIENT_START:
	हाल SNDRV_SEQ_EVENT_CLIENT_EXIT:
	हाल SNDRV_SEQ_EVENT_CLIENT_CHANGE:
	हाल SNDRV_SEQ_EVENT_PORT_START:
	हाल SNDRV_SEQ_EVENT_PORT_EXIT:
	हाल SNDRV_SEQ_EVENT_PORT_CHANGE:
	हाल SNDRV_SEQ_EVENT_ECHO:
	not_yet:
	शेष:
		/*pr_debug("ALSA: seq_midi_emul: Unimplemented event %d\n", ev->type);*/
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(snd_midi_process_event);


/*
 * release note
 */
अटल व्योम
note_off(स्थिर काष्ठा snd_midi_op *ops, व्योम *drv,
	 काष्ठा snd_midi_channel *chan,
	 पूर्णांक note, पूर्णांक vel)
अणु
	अगर (chan->gm_hold) अणु
		/* Hold this note until pedal is turned off */
		chan->note[note] |= SNDRV_MIDI_NOTE_RELEASED;
	पूर्ण अन्यथा अगर (chan->note[note] & SNDRV_MIDI_NOTE_SOSTENUTO) अणु
		/* Mark this note as release; it will be turned off when sostenuto
		 * is turned off */
		chan->note[note] |= SNDRV_MIDI_NOTE_RELEASED;
	पूर्ण अन्यथा अणु
		chan->note[note] = 0;
		अगर (ops->note_off)
			ops->note_off(drv, note, vel, chan);
	पूर्ण
पूर्ण

/*
 * Do all driver independent operations क्रम this controller and pass
 * events that need to take place immediately to the driver.
 */
अटल व्योम
करो_control(स्थिर काष्ठा snd_midi_op *ops, व्योम *drv,
	   काष्ठा snd_midi_channel_set *chset,
	   काष्ठा snd_midi_channel *chan, पूर्णांक control, पूर्णांक value)
अणु
	पूर्णांक  i;

	अगर (control >= ARRAY_SIZE(chan->control))
		वापस;

	/* Switches */
	अगर ((control >=64 && control <=69) || (control >= 80 && control <= 83)) अणु
		/* These are all चयनes; either off or on so set to 0 or 127 */
		value = (value >= 64)? 127: 0;
	पूर्ण
	chan->control[control] = value;

	चयन (control) अणु
	हाल MIDI_CTL_SUSTAIN:
		अगर (value == 0) अणु
			/* Sustain has been released, turn off held notes */
			क्रम (i = 0; i < 128; i++) अणु
				अगर (chan->note[i] & SNDRV_MIDI_NOTE_RELEASED) अणु
					chan->note[i] = SNDRV_MIDI_NOTE_OFF;
					अगर (ops->note_off)
						ops->note_off(drv, i, 0, chan);
				पूर्ण
			पूर्ण
		पूर्ण
		अवरोध;
	हाल MIDI_CTL_PORTAMENTO:
		अवरोध;
	हाल MIDI_CTL_SOSTENUTO:
		अगर (value) अणु
			/* Mark each note that is currently held करोwn */
			क्रम (i = 0; i < 128; i++) अणु
				अगर (chan->note[i] & SNDRV_MIDI_NOTE_ON)
					chan->note[i] |= SNDRV_MIDI_NOTE_SOSTENUTO;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* release all notes that were held */
			क्रम (i = 0; i < 128; i++) अणु
				अगर (chan->note[i] & SNDRV_MIDI_NOTE_SOSTENUTO) अणु
					chan->note[i] &= ~SNDRV_MIDI_NOTE_SOSTENUTO;
					अगर (chan->note[i] & SNDRV_MIDI_NOTE_RELEASED) अणु
						chan->note[i] = SNDRV_MIDI_NOTE_OFF;
						अगर (ops->note_off)
							ops->note_off(drv, i, 0, chan);
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
		अवरोध;
	हाल MIDI_CTL_MSB_DATA_ENTRY:
		chan->control[MIDI_CTL_LSB_DATA_ENTRY] = 0;
		fallthrough;
	हाल MIDI_CTL_LSB_DATA_ENTRY:
		अगर (chan->param_type == SNDRV_MIDI_PARAM_TYPE_REGISTERED)
			rpn(ops, drv, chan, chset);
		अन्यथा
			nrpn(ops, drv, chan, chset);
		अवरोध;
	हाल MIDI_CTL_REGIST_PARM_NUM_LSB:
	हाल MIDI_CTL_REGIST_PARM_NUM_MSB:
		chan->param_type = SNDRV_MIDI_PARAM_TYPE_REGISTERED;
		अवरोध;
	हाल MIDI_CTL_NONREG_PARM_NUM_LSB:
	हाल MIDI_CTL_NONREG_PARM_NUM_MSB:
		chan->param_type = SNDRV_MIDI_PARAM_TYPE_NONREGISTERED;
		अवरोध;

	हाल MIDI_CTL_ALL_SOUNDS_OFF:
		all_sounds_off(ops, drv, chan);
		अवरोध;

	हाल MIDI_CTL_ALL_NOTES_OFF:
		all_notes_off(ops, drv, chan);
		अवरोध;

	हाल MIDI_CTL_MSB_BANK:
		अगर (chset->midi_mode == SNDRV_MIDI_MODE_XG) अणु
			अगर (value == 127)
				chan->drum_channel = 1;
			अन्यथा
				chan->drum_channel = 0;
		पूर्ण
		अवरोध;
	हाल MIDI_CTL_LSB_BANK:
		अवरोध;

	हाल MIDI_CTL_RESET_CONTROLLERS:
		snd_midi_reset_controllers(chan);
		अवरोध;

	हाल MIDI_CTL_SOFT_PEDAL:
	हाल MIDI_CTL_LEGATO_FOOTSWITCH:
	हाल MIDI_CTL_HOLD2:
	हाल MIDI_CTL_SC1_SOUND_VARIATION:
	हाल MIDI_CTL_SC2_TIMBRE:
	हाल MIDI_CTL_SC3_RELEASE_TIME:
	हाल MIDI_CTL_SC4_ATTACK_TIME:
	हाल MIDI_CTL_SC5_BRIGHTNESS:
	हाल MIDI_CTL_E1_REVERB_DEPTH:
	हाल MIDI_CTL_E2_TREMOLO_DEPTH:
	हाल MIDI_CTL_E3_CHORUS_DEPTH:
	हाल MIDI_CTL_E4_DETUNE_DEPTH:
	हाल MIDI_CTL_E5_PHASER_DEPTH:
		जाओ notyet;
	notyet:
	शेष:
		अगर (ops->control)
			ops->control(drv, control, chan);
		अवरोध;
	पूर्ण
पूर्ण


/*
 * initialize the MIDI status
 */
व्योम
snd_midi_channel_set_clear(काष्ठा snd_midi_channel_set *chset)
अणु
	पूर्णांक i;

	chset->midi_mode = SNDRV_MIDI_MODE_GM;
	chset->gs_master_volume = 127;

	क्रम (i = 0; i < chset->max_channels; i++) अणु
		काष्ठा snd_midi_channel *chan = chset->channels + i;
		स_रखो(chan->note, 0, माप(chan->note));

		chan->midi_aftertouch = 0;
		chan->midi_pressure = 0;
		chan->midi_program = 0;
		chan->midi_pitchbend = 0;
		snd_midi_reset_controllers(chan);
		chan->gm_rpn_pitch_bend_range = 256; /* 2 semitones */
		chan->gm_rpn_fine_tuning = 0;
		chan->gm_rpn_coarse_tuning = 0;

		अगर (i == 9)
			chan->drum_channel = 1;
		अन्यथा
			chan->drum_channel = 0;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(snd_midi_channel_set_clear);

/*
 * Process a rpn message.
 */
अटल व्योम
rpn(स्थिर काष्ठा snd_midi_op *ops, व्योम *drv, काष्ठा snd_midi_channel *chan,
    काष्ठा snd_midi_channel_set *chset)
अणु
	पूर्णांक type;
	पूर्णांक val;

	अगर (chset->midi_mode != SNDRV_MIDI_MODE_NONE) अणु
		type = (chan->control[MIDI_CTL_REGIST_PARM_NUM_MSB] << 8) |
			chan->control[MIDI_CTL_REGIST_PARM_NUM_LSB];
		val = (chan->control[MIDI_CTL_MSB_DATA_ENTRY] << 7) |
			chan->control[MIDI_CTL_LSB_DATA_ENTRY];

		चयन (type) अणु
		हाल 0x0000: /* Pitch bend sensitivity */
			/* MSB only / 1 semitone per 128 */
			chan->gm_rpn_pitch_bend_range = val;
			अवरोध;
					
		हाल 0x0001: /* fine tuning: */
			/* MSB/LSB, 8192=center, 100/8192 cent step */
			chan->gm_rpn_fine_tuning = val - 8192;
			अवरोध;

		हाल 0x0002: /* coarse tuning */
			/* MSB only / 8192=center, 1 semitone per 128 */
			chan->gm_rpn_coarse_tuning = val - 8192;
			अवरोध;

		हाल 0x7F7F: /* "lock-in" RPN */
			/* ignored */
			अवरोध;
		पूर्ण
	पूर्ण
	/* should call nrpn or rpn callback here.. */
पूर्ण

/*
 * Process an nrpn message.
 */
अटल व्योम
nrpn(स्थिर काष्ठा snd_midi_op *ops, व्योम *drv, काष्ठा snd_midi_channel *chan,
     काष्ठा snd_midi_channel_set *chset)
अणु
	/* parse XG NRPNs here अगर possible */
	अगर (ops->nrpn)
		ops->nrpn(drv, chan, chset);
पूर्ण


/*
 * convert channel parameter in GS sysex
 */
अटल पूर्णांक
get_channel(अचिन्हित अक्षर cmd)
अणु
	पूर्णांक p = cmd & 0x0f;
	अगर (p == 0)
		p = 9;
	अन्यथा अगर (p < 10)
		p--;
	वापस p;
पूर्ण


/*
 * Process a sysex message.
 */
अटल व्योम
sysex(स्थिर काष्ठा snd_midi_op *ops, व्योम *निजी, अचिन्हित अक्षर *buf, पूर्णांक len,
      काष्ठा snd_midi_channel_set *chset)
अणु
	/* GM on */
	अटल स्थिर अचिन्हित अक्षर gm_on_macro[] = अणु
		0x7e,0x7f,0x09,0x01,
	पूर्ण;
	/* XG on */
	अटल स्थिर अचिन्हित अक्षर xg_on_macro[] = अणु
		0x43,0x10,0x4c,0x00,0x00,0x7e,0x00,
	पूर्ण;
	/* GS prefix
	 * drum channel: XX=0x1?(channel), YY=0x15, ZZ=on/off
	 * reverb mode: XX=0x01, YY=0x30, ZZ=0-7
	 * chorus mode: XX=0x01, YY=0x38, ZZ=0-7
	 * master vol:  XX=0x00, YY=0x04, ZZ=0-127
	 */
	अटल स्थिर अचिन्हित अक्षर gs_pfx_macro[] = अणु
		0x41,0x10,0x42,0x12,0x40,/*XX,YY,ZZ*/
	पूर्ण;

	पूर्णांक parsed = SNDRV_MIDI_SYSEX_NOT_PARSED;

	अगर (len <= 0 || buf[0] != 0xf0)
		वापस;
	/* skip first byte */
	buf++;
	len--;

	/* GM on */
	अगर (len >= (पूर्णांक)माप(gm_on_macro) &&
	    स_भेद(buf, gm_on_macro, माप(gm_on_macro)) == 0) अणु
		अगर (chset->midi_mode != SNDRV_MIDI_MODE_GS &&
		    chset->midi_mode != SNDRV_MIDI_MODE_XG) अणु
			chset->midi_mode = SNDRV_MIDI_MODE_GM;
			reset_all_channels(chset);
			parsed = SNDRV_MIDI_SYSEX_GM_ON;
		पूर्ण
	पूर्ण

	/* GS macros */
	अन्यथा अगर (len >= 8 &&
		 स_भेद(buf, gs_pfx_macro, माप(gs_pfx_macro)) == 0) अणु
		अगर (chset->midi_mode != SNDRV_MIDI_MODE_GS &&
		    chset->midi_mode != SNDRV_MIDI_MODE_XG)
			chset->midi_mode = SNDRV_MIDI_MODE_GS;

		अगर (buf[5] == 0x00 && buf[6] == 0x7f && buf[7] == 0x00) अणु
			/* GS reset */
			parsed = SNDRV_MIDI_SYSEX_GS_RESET;
			reset_all_channels(chset);
		पूर्ण

		अन्यथा अगर ((buf[5] & 0xf0) == 0x10 && buf[6] == 0x15) अणु
			/* drum pattern */
			पूर्णांक p = get_channel(buf[5]);
			अगर (p < chset->max_channels) अणु
				parsed = SNDRV_MIDI_SYSEX_GS_DRUM_CHANNEL;
				अगर (buf[7])
					chset->channels[p].drum_channel = 1;
				अन्यथा
					chset->channels[p].drum_channel = 0;
			पूर्ण

		पूर्ण अन्यथा अगर ((buf[5] & 0xf0) == 0x10 && buf[6] == 0x21) अणु
			/* program */
			पूर्णांक p = get_channel(buf[5]);
			अगर (p < chset->max_channels &&
			    ! chset->channels[p].drum_channel) अणु
				parsed = SNDRV_MIDI_SYSEX_GS_DRUM_CHANNEL;
				chset->channels[p].midi_program = buf[7];
			पूर्ण

		पूर्ण अन्यथा अगर (buf[5] == 0x01 && buf[6] == 0x30) अणु
			/* reverb mode */
			parsed = SNDRV_MIDI_SYSEX_GS_REVERB_MODE;
			chset->gs_reverb_mode = buf[7];

		पूर्ण अन्यथा अगर (buf[5] == 0x01 && buf[6] == 0x38) अणु
			/* chorus mode */
			parsed = SNDRV_MIDI_SYSEX_GS_CHORUS_MODE;
			chset->gs_chorus_mode = buf[7];

		पूर्ण अन्यथा अगर (buf[5] == 0x00 && buf[6] == 0x04) अणु
			/* master volume */
			parsed = SNDRV_MIDI_SYSEX_GS_MASTER_VOLUME;
			chset->gs_master_volume = buf[7];

		पूर्ण
	पूर्ण

	/* XG on */
	अन्यथा अगर (len >= (पूर्णांक)माप(xg_on_macro) &&
		 स_भेद(buf, xg_on_macro, माप(xg_on_macro)) == 0) अणु
		पूर्णांक i;
		chset->midi_mode = SNDRV_MIDI_MODE_XG;
		parsed = SNDRV_MIDI_SYSEX_XG_ON;
		/* reset CC#0 क्रम drums */
		क्रम (i = 0; i < chset->max_channels; i++) अणु
			अगर (chset->channels[i].drum_channel)
				chset->channels[i].control[MIDI_CTL_MSB_BANK] = 127;
			अन्यथा
				chset->channels[i].control[MIDI_CTL_MSB_BANK] = 0;
		पूर्ण
	पूर्ण

	अगर (ops->sysex)
		ops->sysex(निजी, buf - 1, len + 1, parsed, chset);
पूर्ण

/*
 * all sound off
 */
अटल व्योम
all_sounds_off(स्थिर काष्ठा snd_midi_op *ops, व्योम *drv,
	       काष्ठा snd_midi_channel *chan)
अणु
	पूर्णांक n;

	अगर (! ops->note_terminate)
		वापस;
	क्रम (n = 0; n < 128; n++) अणु
		अगर (chan->note[n]) अणु
			ops->note_terminate(drv, n, chan);
			chan->note[n] = 0;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * all notes off
 */
अटल व्योम
all_notes_off(स्थिर काष्ठा snd_midi_op *ops, व्योम *drv,
	      काष्ठा snd_midi_channel *chan)
अणु
	पूर्णांक n;

	अगर (! ops->note_off)
		वापस;
	क्रम (n = 0; n < 128; n++) अणु
		अगर (chan->note[n] == SNDRV_MIDI_NOTE_ON)
			note_off(ops, drv, chan, n, 0);
	पूर्ण
पूर्ण

/*
 * Initialise a single midi channel control block.
 */
अटल व्योम snd_midi_channel_init(काष्ठा snd_midi_channel *p, पूर्णांक n)
अणु
	अगर (p == शून्य)
		वापस;

	स_रखो(p, 0, माप(काष्ठा snd_midi_channel));
	p->निजी = शून्य;
	p->number = n;

	snd_midi_reset_controllers(p);
	p->gm_rpn_pitch_bend_range = 256; /* 2 semitones */
	p->gm_rpn_fine_tuning = 0;
	p->gm_rpn_coarse_tuning = 0;

	अगर (n == 9)
		p->drum_channel = 1;	/* Default ch 10 as drums */
पूर्ण

/*
 * Allocate and initialise a set of midi channel control blocks.
 */
अटल काष्ठा snd_midi_channel *snd_midi_channel_init_set(पूर्णांक n)
अणु
	काष्ठा snd_midi_channel *chan;
	पूर्णांक  i;

	chan = kदो_स्मृति_array(n, माप(काष्ठा snd_midi_channel), GFP_KERNEL);
	अगर (chan) अणु
		क्रम (i = 0; i < n; i++)
			snd_midi_channel_init(chan+i, i);
	पूर्ण

	वापस chan;
पूर्ण

/*
 * reset all midi channels
 */
अटल व्योम
reset_all_channels(काष्ठा snd_midi_channel_set *chset)
अणु
	पूर्णांक ch;
	क्रम (ch = 0; ch < chset->max_channels; ch++) अणु
		काष्ठा snd_midi_channel *chan = chset->channels + ch;
		snd_midi_reset_controllers(chan);
		chan->gm_rpn_pitch_bend_range = 256; /* 2 semitones */
		chan->gm_rpn_fine_tuning = 0;
		chan->gm_rpn_coarse_tuning = 0;

		अगर (ch == 9)
			chan->drum_channel = 1;
		अन्यथा
			chan->drum_channel = 0;
	पूर्ण
पूर्ण


/*
 * Allocate and initialise a midi channel set.
 */
काष्ठा snd_midi_channel_set *snd_midi_channel_alloc_set(पूर्णांक n)
अणु
	काष्ठा snd_midi_channel_set *chset;

	chset = kदो_स्मृति(माप(*chset), GFP_KERNEL);
	अगर (chset) अणु
		chset->channels = snd_midi_channel_init_set(n);
		chset->निजी_data = शून्य;
		chset->max_channels = n;
	पूर्ण
	वापस chset;
पूर्ण
EXPORT_SYMBOL(snd_midi_channel_alloc_set);

/*
 * Reset the midi controllers on a particular channel to शेष values.
 */
अटल व्योम snd_midi_reset_controllers(काष्ठा snd_midi_channel *chan)
अणु
	स_रखो(chan->control, 0, माप(chan->control));
	chan->gm_volume = 127;
	chan->gm_expression = 127;
	chan->gm_pan = 64;
पूर्ण


/*
 * Free a midi channel set.
 */
व्योम snd_midi_channel_मुक्त_set(काष्ठा snd_midi_channel_set *chset)
अणु
	अगर (chset == शून्य)
		वापस;
	kमुक्त(chset->channels);
	kमुक्त(chset);
पूर्ण
EXPORT_SYMBOL(snd_midi_channel_मुक्त_set);
