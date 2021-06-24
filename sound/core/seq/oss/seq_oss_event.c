<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * OSS compatible sequencer driver
 *
 * Copyright (C) 1998,99 Takashi Iwai <tiwai@suse.de>
 */

#समावेश "seq_oss_device.h"
#समावेश "seq_oss_synth.h"
#समावेश "seq_oss_midi.h"
#समावेश "seq_oss_event.h"
#समावेश "seq_oss_timer.h"
#समावेश <sound/seq_oss_legacy.h>
#समावेश "seq_oss_readq.h"
#समावेश "seq_oss_writeq.h"
#समावेश <linux/nospec.h>


/*
 * prototypes
 */
अटल पूर्णांक extended_event(काष्ठा seq_oss_devinfo *dp, जोड़ evrec *q, काष्ठा snd_seq_event *ev);
अटल पूर्णांक chn_voice_event(काष्ठा seq_oss_devinfo *dp, जोड़ evrec *event_rec, काष्ठा snd_seq_event *ev);
अटल पूर्णांक chn_common_event(काष्ठा seq_oss_devinfo *dp, जोड़ evrec *event_rec, काष्ठा snd_seq_event *ev);
अटल पूर्णांक timing_event(काष्ठा seq_oss_devinfo *dp, जोड़ evrec *event_rec, काष्ठा snd_seq_event *ev);
अटल पूर्णांक local_event(काष्ठा seq_oss_devinfo *dp, जोड़ evrec *event_rec, काष्ठा snd_seq_event *ev);
अटल पूर्णांक old_event(काष्ठा seq_oss_devinfo *dp, जोड़ evrec *q, काष्ठा snd_seq_event *ev);
अटल पूर्णांक note_on_event(काष्ठा seq_oss_devinfo *dp, पूर्णांक dev, पूर्णांक ch, पूर्णांक note, पूर्णांक vel, काष्ठा snd_seq_event *ev);
अटल पूर्णांक note_off_event(काष्ठा seq_oss_devinfo *dp, पूर्णांक dev, पूर्णांक ch, पूर्णांक note, पूर्णांक vel, काष्ठा snd_seq_event *ev);
अटल पूर्णांक set_note_event(काष्ठा seq_oss_devinfo *dp, पूर्णांक dev, पूर्णांक type, पूर्णांक ch, पूर्णांक note, पूर्णांक vel, काष्ठा snd_seq_event *ev);
अटल पूर्णांक set_control_event(काष्ठा seq_oss_devinfo *dp, पूर्णांक dev, पूर्णांक type, पूर्णांक ch, पूर्णांक param, पूर्णांक val, काष्ठा snd_seq_event *ev);
अटल पूर्णांक set_echo_event(काष्ठा seq_oss_devinfo *dp, जोड़ evrec *rec, काष्ठा snd_seq_event *ev);


/*
 * convert an OSS event to ALSA event
 * वापस 0 : enqueued
 *        non-zero : invalid - ignored
 */

पूर्णांक
snd_seq_oss_process_event(काष्ठा seq_oss_devinfo *dp, जोड़ evrec *q, काष्ठा snd_seq_event *ev)
अणु
	चयन (q->s.code) अणु
	हाल SEQ_EXTENDED:
		वापस extended_event(dp, q, ev);

	हाल EV_CHN_VOICE:
		वापस chn_voice_event(dp, q, ev);

	हाल EV_CHN_COMMON:
		वापस chn_common_event(dp, q, ev);

	हाल EV_TIMING:
		वापस timing_event(dp, q, ev);

	हाल EV_SEQ_LOCAL:
		वापस local_event(dp, q, ev);

	हाल EV_SYSEX:
		वापस snd_seq_oss_synth_sysex(dp, q->x.dev, q->x.buf, ev);

	हाल SEQ_MIDIPUTC:
		अगर (dp->seq_mode == SNDRV_SEQ_OSS_MODE_MUSIC)
			वापस -EINVAL;
		/* put a midi byte */
		अगर (! is_ग_लिखो_mode(dp->file_mode))
			अवरोध;
		अगर (snd_seq_oss_midi_खोलो(dp, q->s.dev, SNDRV_SEQ_OSS_खाता_WRITE))
			अवरोध;
		अगर (snd_seq_oss_midi_filemode(dp, q->s.dev) & SNDRV_SEQ_OSS_खाता_WRITE)
			वापस snd_seq_oss_midi_अ_दो(dp, q->s.dev, q->s.parm1, ev);
		अवरोध;

	हाल SEQ_ECHO:
		अगर (dp->seq_mode == SNDRV_SEQ_OSS_MODE_MUSIC)
			वापस -EINVAL;
		वापस set_echo_event(dp, q, ev);

	हाल SEQ_PRIVATE:
		अगर (dp->seq_mode == SNDRV_SEQ_OSS_MODE_MUSIC)
			वापस -EINVAL;
		वापस snd_seq_oss_synth_raw_event(dp, q->c[1], q->c, ev);

	शेष:
		अगर (dp->seq_mode == SNDRV_SEQ_OSS_MODE_MUSIC)
			वापस -EINVAL;
		वापस old_event(dp, q, ev);
	पूर्ण
	वापस -EINVAL;
पूर्ण

/* old type events: mode1 only */
अटल पूर्णांक
old_event(काष्ठा seq_oss_devinfo *dp, जोड़ evrec *q, काष्ठा snd_seq_event *ev)
अणु
	चयन (q->s.code) अणु
	हाल SEQ_NOTखातापूर्णF:
		वापस note_off_event(dp, 0, q->n.chn, q->n.note, q->n.vel, ev);

	हाल SEQ_NOTEON:
		वापस note_on_event(dp, 0, q->n.chn, q->n.note, q->n.vel, ev);

	हाल SEQ_WAIT:
		/* skip */
		अवरोध;

	हाल SEQ_PGMCHANGE:
		वापस set_control_event(dp, 0, SNDRV_SEQ_EVENT_PGMCHANGE,
					 q->n.chn, 0, q->n.note, ev);

	हाल SEQ_SYNCTIMER:
		वापस snd_seq_oss_समयr_reset(dp->समयr);
	पूर्ण

	वापस -EINVAL;
पूर्ण

/* 8bytes extended event: mode1 only */
अटल पूर्णांक
extended_event(काष्ठा seq_oss_devinfo *dp, जोड़ evrec *q, काष्ठा snd_seq_event *ev)
अणु
	पूर्णांक val;

	चयन (q->e.cmd) अणु
	हाल SEQ_NOTखातापूर्णF:
		वापस note_off_event(dp, q->e.dev, q->e.chn, q->e.p1, q->e.p2, ev);

	हाल SEQ_NOTEON:
		वापस note_on_event(dp, q->e.dev, q->e.chn, q->e.p1, q->e.p2, ev);

	हाल SEQ_PGMCHANGE:
		वापस set_control_event(dp, q->e.dev, SNDRV_SEQ_EVENT_PGMCHANGE,
					 q->e.chn, 0, q->e.p1, ev);

	हाल SEQ_AFTERTOUCH:
		वापस set_control_event(dp, q->e.dev, SNDRV_SEQ_EVENT_CHANPRESS,
					 q->e.chn, 0, q->e.p1, ev);

	हाल SEQ_BALANCE:
		/* convert -128:127 to 0:127 */
		val = (अक्षर)q->e.p1;
		val = (val + 128) / 2;
		वापस set_control_event(dp, q->e.dev, SNDRV_SEQ_EVENT_CONTROLLER,
					 q->e.chn, CTL_PAN, val, ev);

	हाल SEQ_CONTROLLER:
		val = ((लघु)q->e.p3 << 8) | (लघु)q->e.p2;
		चयन (q->e.p1) अणु
		हाल CTRL_PITCH_BENDER: /* SEQ1 V2 control */
			/* -0x2000:0x1fff */
			वापस set_control_event(dp, q->e.dev,
						 SNDRV_SEQ_EVENT_PITCHBEND,
						 q->e.chn, 0, val, ev);
		हाल CTRL_PITCH_BENDER_RANGE:
			/* conversion: 100/semitone -> 128/semitone */
			वापस set_control_event(dp, q->e.dev,
						 SNDRV_SEQ_EVENT_REGPARAM,
						 q->e.chn, 0, val*128/100, ev);
		शेष:
			वापस set_control_event(dp, q->e.dev,
						  SNDRV_SEQ_EVENT_CONTROL14,
						  q->e.chn, q->e.p1, val, ev);
		पूर्ण

	हाल SEQ_VOLMODE:
		वापस snd_seq_oss_synth_raw_event(dp, q->e.dev, q->c, ev);

	पूर्ण
	वापस -EINVAL;
पूर्ण

/* channel voice events: mode1 and 2 */
अटल पूर्णांक
chn_voice_event(काष्ठा seq_oss_devinfo *dp, जोड़ evrec *q, काष्ठा snd_seq_event *ev)
अणु
	अगर (q->v.chn >= 32)
		वापस -EINVAL;
	चयन (q->v.cmd) अणु
	हाल MIDI_NOTEON:
		वापस note_on_event(dp, q->v.dev, q->v.chn, q->v.note, q->v.parm, ev);

	हाल MIDI_NOTखातापूर्णF:
		वापस note_off_event(dp, q->v.dev, q->v.chn, q->v.note, q->v.parm, ev);

	हाल MIDI_KEY_PRESSURE:
		वापस set_note_event(dp, q->v.dev, SNDRV_SEQ_EVENT_KEYPRESS,
				       q->v.chn, q->v.note, q->v.parm, ev);

	पूर्ण
	वापस -EINVAL;
पूर्ण

/* channel common events: mode1 and 2 */
अटल पूर्णांक
chn_common_event(काष्ठा seq_oss_devinfo *dp, जोड़ evrec *q, काष्ठा snd_seq_event *ev)
अणु
	अगर (q->l.chn >= 32)
		वापस -EINVAL;
	चयन (q->l.cmd) अणु
	हाल MIDI_PGM_CHANGE:
		वापस set_control_event(dp, q->l.dev, SNDRV_SEQ_EVENT_PGMCHANGE,
					  q->l.chn, 0, q->l.p1, ev);

	हाल MIDI_CTL_CHANGE:
		वापस set_control_event(dp, q->l.dev, SNDRV_SEQ_EVENT_CONTROLLER,
					  q->l.chn, q->l.p1, q->l.val, ev);

	हाल MIDI_PITCH_BEND:
		/* conversion: 0:0x3fff -> -0x2000:0x1fff */
		वापस set_control_event(dp, q->l.dev, SNDRV_SEQ_EVENT_PITCHBEND,
					  q->l.chn, 0, q->l.val - 8192, ev);
		
	हाल MIDI_CHN_PRESSURE:
		वापस set_control_event(dp, q->l.dev, SNDRV_SEQ_EVENT_CHANPRESS,
					  q->l.chn, 0, q->l.val, ev);
	पूर्ण
	वापस -EINVAL;
पूर्ण

/* समयr events: mode1 and mode2 */
अटल पूर्णांक
timing_event(काष्ठा seq_oss_devinfo *dp, जोड़ evrec *q, काष्ठा snd_seq_event *ev)
अणु
	चयन (q->t.cmd) अणु
	हाल TMR_ECHO:
		अगर (dp->seq_mode == SNDRV_SEQ_OSS_MODE_MUSIC)
			वापस set_echo_event(dp, q, ev);
		अन्यथा अणु
			जोड़ evrec पंचांगp;
			स_रखो(&पंचांगp, 0, माप(पंचांगp));
			/* XXX: only क्रम little-endian! */
			पंचांगp.echo = (q->t.समय << 8) | SEQ_ECHO;
			वापस set_echo_event(dp, &पंचांगp, ev);
		पूर्ण 

	हाल TMR_STOP:
		अगर (dp->seq_mode)
			वापस snd_seq_oss_समयr_stop(dp->समयr);
		वापस 0;

	हाल TMR_CONTINUE:
		अगर (dp->seq_mode)
			वापस snd_seq_oss_समयr_जारी(dp->समयr);
		वापस 0;

	हाल TMR_TEMPO:
		अगर (dp->seq_mode)
			वापस snd_seq_oss_समयr_tempo(dp->समयr, q->t.समय);
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

/* local events: mode1 and 2 */
अटल पूर्णांक
local_event(काष्ठा seq_oss_devinfo *dp, जोड़ evrec *q, काष्ठा snd_seq_event *ev)
अणु
	वापस -EINVAL;
पूर्ण

/*
 * process note-on event क्रम OSS synth
 * three dअगरferent modes are available:
 * - SNDRV_SEQ_OSS_PROCESS_EVENTS  (क्रम one-voice per channel mode)
 *	Accept note 255 as volume change.
 * - SNDRV_SEQ_OSS_PASS_EVENTS
 *	Pass all events to lowlevel driver anyway
 * - SNDRV_SEQ_OSS_PROCESS_KEYPRESS  (mostly क्रम Emu8000)
 *	Use key-pressure अगर note >= 128
 */
अटल पूर्णांक
note_on_event(काष्ठा seq_oss_devinfo *dp, पूर्णांक dev, पूर्णांक ch, पूर्णांक note, पूर्णांक vel, काष्ठा snd_seq_event *ev)
अणु
	काष्ठा seq_oss_synthinfo *info;

	info = snd_seq_oss_synth_info(dp, dev);
	अगर (!info)
		वापस -ENXIO;

	चयन (info->arg.event_passing) अणु
	हाल SNDRV_SEQ_OSS_PROCESS_EVENTS:
		अगर (! info->ch || ch < 0 || ch >= info->nr_voices) अणु
			/* pass directly */
			वापस set_note_event(dp, dev, SNDRV_SEQ_EVENT_NOTEON, ch, note, vel, ev);
		पूर्ण

		ch = array_index_nospec(ch, info->nr_voices);
		अगर (note == 255 && info->ch[ch].note >= 0) अणु
			/* volume control */
			पूर्णांक type;
			//अगर (! vel)
				/* set volume to zero -- note off */
			//	type = SNDRV_SEQ_EVENT_NOTखातापूर्णF;
			//अन्यथा
				अगर (info->ch[ch].vel)
				/* sample alपढ़ोy started -- volume change */
				type = SNDRV_SEQ_EVENT_KEYPRESS;
			अन्यथा
				/* sample not started -- start now */
				type = SNDRV_SEQ_EVENT_NOTEON;
			info->ch[ch].vel = vel;
			वापस set_note_event(dp, dev, type, ch, info->ch[ch].note, vel, ev);
		पूर्ण अन्यथा अगर (note >= 128)
			वापस -EINVAL; /* invalid */

		अगर (note != info->ch[ch].note && info->ch[ch].note >= 0)
			/* note changed - note off at beginning */
			set_note_event(dp, dev, SNDRV_SEQ_EVENT_NOTखातापूर्णF, ch, info->ch[ch].note, 0, ev);
		/* set current status */
		info->ch[ch].note = note;
		info->ch[ch].vel = vel;
		अगर (vel) /* non-zero velocity - start the note now */
			वापस set_note_event(dp, dev, SNDRV_SEQ_EVENT_NOTEON, ch, note, vel, ev);
		वापस -EINVAL;
		
	हाल SNDRV_SEQ_OSS_PASS_EVENTS:
		/* pass the event anyway */
		वापस set_note_event(dp, dev, SNDRV_SEQ_EVENT_NOTEON, ch, note, vel, ev);

	हाल SNDRV_SEQ_OSS_PROCESS_KEYPRESS:
		अगर (note >= 128) /* key pressure: shअगरted by 128 */
			वापस set_note_event(dp, dev, SNDRV_SEQ_EVENT_KEYPRESS, ch, note - 128, vel, ev);
		अन्यथा /* normal note-on event */
			वापस set_note_event(dp, dev, SNDRV_SEQ_EVENT_NOTEON, ch, note, vel, ev);
	पूर्ण
	वापस -EINVAL;
पूर्ण

/*
 * process note-off event क्रम OSS synth
 */
अटल पूर्णांक
note_off_event(काष्ठा seq_oss_devinfo *dp, पूर्णांक dev, पूर्णांक ch, पूर्णांक note, पूर्णांक vel, काष्ठा snd_seq_event *ev)
अणु
	काष्ठा seq_oss_synthinfo *info;

	info = snd_seq_oss_synth_info(dp, dev);
	अगर (!info)
		वापस -ENXIO;

	चयन (info->arg.event_passing) अणु
	हाल SNDRV_SEQ_OSS_PROCESS_EVENTS:
		अगर (! info->ch || ch < 0 || ch >= info->nr_voices) अणु
			/* pass directly */
			वापस set_note_event(dp, dev, SNDRV_SEQ_EVENT_NOTEON, ch, note, vel, ev);
		पूर्ण

		ch = array_index_nospec(ch, info->nr_voices);
		अगर (info->ch[ch].note >= 0) अणु
			note = info->ch[ch].note;
			info->ch[ch].vel = 0;
			info->ch[ch].note = -1;
			वापस set_note_event(dp, dev, SNDRV_SEQ_EVENT_NOTखातापूर्णF, ch, note, vel, ev);
		पूर्ण
		वापस -EINVAL; /* invalid */

	हाल SNDRV_SEQ_OSS_PASS_EVENTS:
	हाल SNDRV_SEQ_OSS_PROCESS_KEYPRESS:
		/* pass the event anyway */
		वापस set_note_event(dp, dev, SNDRV_SEQ_EVENT_NOTखातापूर्णF, ch, note, vel, ev);

	पूर्ण
	वापस -EINVAL;
पूर्ण

/*
 * create a note event
 */
अटल पूर्णांक
set_note_event(काष्ठा seq_oss_devinfo *dp, पूर्णांक dev, पूर्णांक type, पूर्णांक ch, पूर्णांक note, पूर्णांक vel, काष्ठा snd_seq_event *ev)
अणु
	अगर (!snd_seq_oss_synth_info(dp, dev))
		वापस -ENXIO;
	
	ev->type = type;
	snd_seq_oss_synth_addr(dp, dev, ev);
	ev->data.note.channel = ch;
	ev->data.note.note = note;
	ev->data.note.velocity = vel;

	वापस 0;
पूर्ण

/*
 * create a control event
 */
अटल पूर्णांक
set_control_event(काष्ठा seq_oss_devinfo *dp, पूर्णांक dev, पूर्णांक type, पूर्णांक ch, पूर्णांक param, पूर्णांक val, काष्ठा snd_seq_event *ev)
अणु
	अगर (!snd_seq_oss_synth_info(dp, dev))
		वापस -ENXIO;
	
	ev->type = type;
	snd_seq_oss_synth_addr(dp, dev, ev);
	ev->data.control.channel = ch;
	ev->data.control.param = param;
	ev->data.control.value = val;

	वापस 0;
पूर्ण

/*
 * create an echo event
 */
अटल पूर्णांक
set_echo_event(काष्ठा seq_oss_devinfo *dp, जोड़ evrec *rec, काष्ठा snd_seq_event *ev)
अणु
	ev->type = SNDRV_SEQ_EVENT_ECHO;
	/* echo back to itself */
	snd_seq_oss_fill_addr(dp, ev, dp->addr.client, dp->addr.port);
	स_नकल(&ev->data, rec, LONG_EVENT_SIZE);
	वापस 0;
पूर्ण

/*
 * event input callback from ALSA sequencer:
 * the echo event is processed here.
 */
पूर्णांक
snd_seq_oss_event_input(काष्ठा snd_seq_event *ev, पूर्णांक direct, व्योम *निजी_data,
			पूर्णांक atomic, पूर्णांक hop)
अणु
	काष्ठा seq_oss_devinfo *dp = (काष्ठा seq_oss_devinfo *)निजी_data;
	जोड़ evrec *rec;

	अगर (ev->type != SNDRV_SEQ_EVENT_ECHO)
		वापस snd_seq_oss_midi_input(ev, direct, निजी_data);

	अगर (ev->source.client != dp->cseq)
		वापस 0; /* ignored */

	rec = (जोड़ evrec*)&ev->data;
	अगर (rec->s.code == SEQ_SYNCTIMER) अणु
		/* sync echo back */
		snd_seq_oss_ग_लिखोq_wakeup(dp->ग_लिखोq, rec->t.समय);
		
	पूर्ण अन्यथा अणु
		/* echo back event */
		अगर (dp->पढ़ोq == शून्य)
			वापस 0;
		snd_seq_oss_पढ़ोq_put_event(dp->पढ़ोq, rec);
	पूर्ण
	वापस 0;
पूर्ण

