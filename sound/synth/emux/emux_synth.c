<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Midi synth routines क्रम the Emu8k/Emu10k1
 *
 *  Copyright (C) 1999 Steve Ratclअगरfe
 *  Copyright (c) 1999-2000 Takashi Iwai <tiwai@suse.de>
 *
 *  Contains code based on awe_wave.c by Takashi Iwai
 */

#समावेश <linux/export.h>
#समावेश "emux_voice.h"
#समावेश <sound/asoundef.h>

/*
 * Prototypes
 */

/*
 * Ensure a value is between two poपूर्णांकs
 * macro evaluates its args more than once, so changed to upper-हाल.
 */
#घोषणा LIMITVALUE(x, a, b) करो अणु अगर ((x) < (a)) (x) = (a); अन्यथा अगर ((x) > (b)) (x) = (b); पूर्ण जबतक (0)
#घोषणा LIMITMAX(x, a) करो अणुअगर ((x) > (a)) (x) = (a); पूर्ण जबतक (0)

अटल पूर्णांक get_zone(काष्ठा snd_emux *emu, काष्ठा snd_emux_port *port,
		    पूर्णांक *notep, पूर्णांक vel, काष्ठा snd_midi_channel *chan,
		    काष्ठा snd_sf_zone **table);
अटल पूर्णांक get_bank(काष्ठा snd_emux_port *port, काष्ठा snd_midi_channel *chan);
अटल व्योम terminate_note1(काष्ठा snd_emux *emu, पूर्णांक note,
			    काष्ठा snd_midi_channel *chan, पूर्णांक मुक्त);
अटल व्योम exclusive_note_off(काष्ठा snd_emux *emu, काष्ठा snd_emux_port *port,
			       पूर्णांक exclass);
अटल व्योम terminate_voice(काष्ठा snd_emux *emu, काष्ठा snd_emux_voice *vp, पूर्णांक मुक्त);
अटल व्योम update_voice(काष्ठा snd_emux *emu, काष्ठा snd_emux_voice *vp, पूर्णांक update);
अटल व्योम setup_voice(काष्ठा snd_emux_voice *vp);
अटल पूर्णांक calc_pan(काष्ठा snd_emux_voice *vp);
अटल पूर्णांक calc_volume(काष्ठा snd_emux_voice *vp);
अटल पूर्णांक calc_pitch(काष्ठा snd_emux_voice *vp);


/*
 * Start a note.
 */
व्योम
snd_emux_note_on(व्योम *p, पूर्णांक note, पूर्णांक vel, काष्ठा snd_midi_channel *chan)
अणु
	काष्ठा snd_emux *emu;
	पूर्णांक i, key, nvoices;
	काष्ठा snd_emux_voice *vp;
	काष्ठा snd_sf_zone *table[SNDRV_EMUX_MAX_MULTI_VOICES];
	अचिन्हित दीर्घ flags;
	काष्ठा snd_emux_port *port;

	port = p;
	अगर (snd_BUG_ON(!port || !chan))
		वापस;

	emu = port->emu;
	अगर (snd_BUG_ON(!emu || !emu->ops.get_voice || !emu->ops.trigger))
		वापस;

	key = note; /* remember the original note */
	nvoices = get_zone(emu, port, &note, vel, chan, table);
	अगर (! nvoices)
		वापस;

	/* exclusive note off */
	क्रम (i = 0; i < nvoices; i++) अणु
		काष्ठा snd_sf_zone *zp = table[i];
		अगर (zp && zp->v.exclusiveClass)
			exclusive_note_off(emu, port, zp->v.exclusiveClass);
	पूर्ण

#अगर 0 // seems not necessary
	/* Turn off the same note on the same channel. */
	terminate_note1(emu, key, chan, 0);
#पूर्ण_अगर

	spin_lock_irqsave(&emu->voice_lock, flags);
	क्रम (i = 0; i < nvoices; i++) अणु

		/* set up each voice parameter */
		/* at this stage, we करोn't trigger the voice yet. */

		अगर (table[i] == शून्य)
			जारी;

		vp = emu->ops.get_voice(emu, port);
		अगर (vp == शून्य || vp->ch < 0)
			जारी;
		अगर (STATE_IS_PLAYING(vp->state))
			emu->ops.terminate(vp);

		vp->समय = emu->use_समय++;
		vp->chan = chan;
		vp->port = port;
		vp->key = key;
		vp->note = note;
		vp->velocity = vel;
		vp->zone = table[i];
		अगर (vp->zone->sample)
			vp->block = vp->zone->sample->block;
		अन्यथा
			vp->block = शून्य;

		setup_voice(vp);

		vp->state = SNDRV_EMUX_ST_STANDBY;
		अगर (emu->ops.prepare) अणु
			vp->state = SNDRV_EMUX_ST_OFF;
			अगर (emu->ops.prepare(vp) >= 0)
				vp->state = SNDRV_EMUX_ST_STANDBY;
		पूर्ण
	पूर्ण

	/* start envelope now */
	क्रम (i = 0; i < emu->max_voices; i++) अणु
		vp = &emu->voices[i];
		अगर (vp->state == SNDRV_EMUX_ST_STANDBY &&
		    vp->chan == chan) अणु
			emu->ops.trigger(vp);
			vp->state = SNDRV_EMUX_ST_ON;
			vp->onसमय = jअगरfies; /* remember the trigger timing */
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&emu->voice_lock, flags);

#अगर_घोषित SNDRV_EMUX_USE_RAW_EFFECT
	अगर (port->port_mode == SNDRV_EMUX_PORT_MODE_OSS_SYNTH) अणु
		/* clear voice position क्रम the next note on this channel */
		काष्ठा snd_emux_effect_table *fx = chan->निजी;
		अगर (fx) अणु
			fx->flag[EMUX_FX_SAMPLE_START] = 0;
			fx->flag[EMUX_FX_COARSE_SAMPLE_START] = 0;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
पूर्ण

/*
 * Release a note in response to a midi note off.
 */
व्योम
snd_emux_note_off(व्योम *p, पूर्णांक note, पूर्णांक vel, काष्ठा snd_midi_channel *chan)
अणु
	पूर्णांक ch;
	काष्ठा snd_emux *emu;
	काष्ठा snd_emux_voice *vp;
	अचिन्हित दीर्घ flags;
	काष्ठा snd_emux_port *port;

	port = p;
	अगर (snd_BUG_ON(!port || !chan))
		वापस;

	emu = port->emu;
	अगर (snd_BUG_ON(!emu || !emu->ops.release))
		वापस;

	spin_lock_irqsave(&emu->voice_lock, flags);
	क्रम (ch = 0; ch < emu->max_voices; ch++) अणु
		vp = &emu->voices[ch];
		अगर (STATE_IS_PLAYING(vp->state) &&
		    vp->chan == chan && vp->key == note) अणु
			vp->state = SNDRV_EMUX_ST_RELEASED;
			अगर (vp->onसमय == jअगरfies) अणु
				/* अगर note-off is sent too लघुly after
				 * note-on, emuX engine cannot produce the sound
				 * correctly.  so we'll release this note
				 * a bit later via समयr callback.
				 */
				vp->state = SNDRV_EMUX_ST_PENDING;
				अगर (! emu->समयr_active) अणु
					mod_समयr(&emu->tlist, jअगरfies + 1);
					emu->समयr_active = 1;
				पूर्ण
			पूर्ण अन्यथा
				/* ok now release the note */
				emu->ops.release(vp);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&emu->voice_lock, flags);
पूर्ण

/*
 * समयr callback
 *
 * release the pending note-offs
 */
व्योम snd_emux_समयr_callback(काष्ठा समयr_list *t)
अणु
	काष्ठा snd_emux *emu = from_समयr(emu, t, tlist);
	काष्ठा snd_emux_voice *vp;
	अचिन्हित दीर्घ flags;
	पूर्णांक ch, करो_again = 0;

	spin_lock_irqsave(&emu->voice_lock, flags);
	क्रम (ch = 0; ch < emu->max_voices; ch++) अणु
		vp = &emu->voices[ch];
		अगर (vp->state == SNDRV_EMUX_ST_PENDING) अणु
			अगर (vp->onसमय == jअगरfies)
				करो_again++; /* release this at the next पूर्णांकerrupt */
			अन्यथा अणु
				emu->ops.release(vp);
				vp->state = SNDRV_EMUX_ST_RELEASED;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (करो_again) अणु
		mod_समयr(&emu->tlist, jअगरfies + 1);
		emu->समयr_active = 1;
	पूर्ण अन्यथा
		emu->समयr_active = 0;
	spin_unlock_irqrestore(&emu->voice_lock, flags);
पूर्ण

/*
 * key pressure change
 */
व्योम
snd_emux_key_press(व्योम *p, पूर्णांक note, पूर्णांक vel, काष्ठा snd_midi_channel *chan)
अणु
	पूर्णांक ch;
	काष्ठा snd_emux *emu;
	काष्ठा snd_emux_voice *vp;
	अचिन्हित दीर्घ flags;
	काष्ठा snd_emux_port *port;

	port = p;
	अगर (snd_BUG_ON(!port || !chan))
		वापस;

	emu = port->emu;
	अगर (snd_BUG_ON(!emu || !emu->ops.update))
		वापस;

	spin_lock_irqsave(&emu->voice_lock, flags);
	क्रम (ch = 0; ch < emu->max_voices; ch++) अणु
		vp = &emu->voices[ch];
		अगर (vp->state == SNDRV_EMUX_ST_ON &&
		    vp->chan == chan && vp->key == note) अणु
			vp->velocity = vel;
			update_voice(emu, vp, SNDRV_EMUX_UPDATE_VOLUME);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&emu->voice_lock, flags);
पूर्ण


/*
 * Modulate the voices which beदीर्घ to the channel
 */
व्योम
snd_emux_update_channel(काष्ठा snd_emux_port *port, काष्ठा snd_midi_channel *chan, पूर्णांक update)
अणु
	काष्ठा snd_emux *emu;
	काष्ठा snd_emux_voice *vp;
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	अगर (! update)
		वापस;

	emu = port->emu;
	अगर (snd_BUG_ON(!emu || !emu->ops.update))
		वापस;

	spin_lock_irqsave(&emu->voice_lock, flags);
	क्रम (i = 0; i < emu->max_voices; i++) अणु
		vp = &emu->voices[i];
		अगर (vp->chan == chan)
			update_voice(emu, vp, update);
	पूर्ण
	spin_unlock_irqrestore(&emu->voice_lock, flags);
पूर्ण

/*
 * Modulate all the voices which beदीर्घ to the port.
 */
व्योम
snd_emux_update_port(काष्ठा snd_emux_port *port, पूर्णांक update)
अणु
	काष्ठा snd_emux *emu; 
	काष्ठा snd_emux_voice *vp;
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	अगर (! update)
		वापस;

	emu = port->emu;
	अगर (snd_BUG_ON(!emu || !emu->ops.update))
		वापस;

	spin_lock_irqsave(&emu->voice_lock, flags);
	क्रम (i = 0; i < emu->max_voices; i++) अणु
		vp = &emu->voices[i];
		अगर (vp->port == port)
			update_voice(emu, vp, update);
	पूर्ण
	spin_unlock_irqrestore(&emu->voice_lock, flags);
पूर्ण


/*
 * Deal with a controller type event.  This includes all types of
 * control events, not just the midi controllers
 */
व्योम
snd_emux_control(व्योम *p, पूर्णांक type, काष्ठा snd_midi_channel *chan)
अणु
	काष्ठा snd_emux_port *port;

	port = p;
	अगर (snd_BUG_ON(!port || !chan))
		वापस;

	चयन (type) अणु
	हाल MIDI_CTL_MSB_MAIN_VOLUME:
	हाल MIDI_CTL_MSB_EXPRESSION:
		snd_emux_update_channel(port, chan, SNDRV_EMUX_UPDATE_VOLUME);
		अवरोध;
		
	हाल MIDI_CTL_MSB_PAN:
		snd_emux_update_channel(port, chan, SNDRV_EMUX_UPDATE_PAN);
		अवरोध;

	हाल MIDI_CTL_SOFT_PEDAL:
#अगर_घोषित SNDRV_EMUX_USE_RAW_EFFECT
		/* FIXME: this is an emulation */
		अगर (chan->control[type] >= 64)
			snd_emux_send_effect(port, chan, EMUX_FX_CUTOFF, -160,
				     EMUX_FX_FLAG_ADD);
		अन्यथा
			snd_emux_send_effect(port, chan, EMUX_FX_CUTOFF, 0,
				     EMUX_FX_FLAG_OFF);
#पूर्ण_अगर
		अवरोध;

	हाल MIDI_CTL_PITCHBEND:
		snd_emux_update_channel(port, chan, SNDRV_EMUX_UPDATE_PITCH);
		अवरोध;

	हाल MIDI_CTL_MSB_MODWHEEL:
	हाल MIDI_CTL_CHAN_PRESSURE:
		snd_emux_update_channel(port, chan,
					SNDRV_EMUX_UPDATE_FMMOD |
					SNDRV_EMUX_UPDATE_FM2FRQ2);
		अवरोध;

	पूर्ण

	अगर (port->chset.midi_mode == SNDRV_MIDI_MODE_XG) अणु
		snd_emux_xg_control(port, chan, type);
	पूर्ण
पूर्ण


/*
 * terminate note - अगर मुक्त flag is true, मुक्त the terminated voice
 */
अटल व्योम
terminate_note1(काष्ठा snd_emux *emu, पूर्णांक note, काष्ठा snd_midi_channel *chan, पूर्णांक मुक्त)
अणु
	पूर्णांक  i;
	काष्ठा snd_emux_voice *vp;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&emu->voice_lock, flags);
	क्रम (i = 0; i < emu->max_voices; i++) अणु
		vp = &emu->voices[i];
		अगर (STATE_IS_PLAYING(vp->state) && vp->chan == chan &&
		    vp->key == note)
			terminate_voice(emu, vp, मुक्त);
	पूर्ण
	spin_unlock_irqrestore(&emu->voice_lock, flags);
पूर्ण


/*
 * terminate note - exported क्रम midi emulation
 */
व्योम
snd_emux_terminate_note(व्योम *p, पूर्णांक note, काष्ठा snd_midi_channel *chan)
अणु
	काष्ठा snd_emux *emu;
	काष्ठा snd_emux_port *port;

	port = p;
	अगर (snd_BUG_ON(!port || !chan))
		वापस;

	emu = port->emu;
	अगर (snd_BUG_ON(!emu || !emu->ops.terminate))
		वापस;

	terminate_note1(emu, note, chan, 1);
पूर्ण


/*
 * Terminate all the notes
 */
व्योम
snd_emux_terminate_all(काष्ठा snd_emux *emu)
अणु
	पूर्णांक i;
	काष्ठा snd_emux_voice *vp;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&emu->voice_lock, flags);
	क्रम (i = 0; i < emu->max_voices; i++) अणु
		vp = &emu->voices[i];
		अगर (STATE_IS_PLAYING(vp->state))
			terminate_voice(emu, vp, 0);
		अगर (vp->state == SNDRV_EMUX_ST_OFF) अणु
			अगर (emu->ops.मुक्त_voice)
				emu->ops.मुक्त_voice(vp);
			अगर (emu->ops.reset)
				emu->ops.reset(emu, i);
		पूर्ण
		vp->समय = 0;
	पूर्ण
	/* initialize allocation समय */
	emu->use_समय = 0;
	spin_unlock_irqrestore(&emu->voice_lock, flags);
पूर्ण

EXPORT_SYMBOL(snd_emux_terminate_all);

/*
 * Terminate all voices associated with the given port
 */
व्योम
snd_emux_sounds_off_all(काष्ठा snd_emux_port *port)
अणु
	पूर्णांक i;
	काष्ठा snd_emux *emu;
	काष्ठा snd_emux_voice *vp;
	अचिन्हित दीर्घ flags;

	अगर (snd_BUG_ON(!port))
		वापस;
	emu = port->emu;
	अगर (snd_BUG_ON(!emu || !emu->ops.terminate))
		वापस;

	spin_lock_irqsave(&emu->voice_lock, flags);
	क्रम (i = 0; i < emu->max_voices; i++) अणु
		vp = &emu->voices[i];
		अगर (STATE_IS_PLAYING(vp->state) &&
		    vp->port == port)
			terminate_voice(emu, vp, 0);
		अगर (vp->state == SNDRV_EMUX_ST_OFF) अणु
			अगर (emu->ops.मुक्त_voice)
				emu->ops.मुक्त_voice(vp);
			अगर (emu->ops.reset)
				emu->ops.reset(emu, i);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&emu->voice_lock, flags);
पूर्ण


/*
 * Terminate all voices that have the same exclusive class.  This
 * is मुख्यly क्रम drums.
 */
अटल व्योम
exclusive_note_off(काष्ठा snd_emux *emu, काष्ठा snd_emux_port *port, पूर्णांक exclass)
अणु
	काष्ठा snd_emux_voice *vp;
	पूर्णांक  i;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&emu->voice_lock, flags);
	क्रम (i = 0; i < emu->max_voices; i++) अणु
		vp = &emu->voices[i];
		अगर (STATE_IS_PLAYING(vp->state) && vp->port == port &&
		    vp->reg.exclusiveClass == exclass) अणु
			terminate_voice(emu, vp, 0);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&emu->voice_lock, flags);
पूर्ण

/*
 * terminate a voice
 * अगर मुक्त flag is true, call मुक्त_voice after termination
 */
अटल व्योम
terminate_voice(काष्ठा snd_emux *emu, काष्ठा snd_emux_voice *vp, पूर्णांक मुक्त)
अणु
	emu->ops.terminate(vp);
	vp->समय = emu->use_समय++;
	vp->chan = शून्य;
	vp->port = शून्य;
	vp->zone = शून्य;
	vp->block = शून्य;
	vp->state = SNDRV_EMUX_ST_OFF;
	अगर (मुक्त && emu->ops.मुक्त_voice)
		emu->ops.मुक्त_voice(vp);
पूर्ण


/*
 * Modulate the voice
 */
अटल व्योम
update_voice(काष्ठा snd_emux *emu, काष्ठा snd_emux_voice *vp, पूर्णांक update)
अणु
	अगर (!STATE_IS_PLAYING(vp->state))
		वापस;

	अगर (vp->chan == शून्य || vp->port == शून्य)
		वापस;
	अगर (update & SNDRV_EMUX_UPDATE_VOLUME)
		calc_volume(vp);
	अगर (update & SNDRV_EMUX_UPDATE_PITCH)
		calc_pitch(vp);
	अगर (update & SNDRV_EMUX_UPDATE_PAN) अणु
		अगर (! calc_pan(vp) && (update == SNDRV_EMUX_UPDATE_PAN))
			वापस;
	पूर्ण
	emu->ops.update(vp, update);
पूर्ण


#अगर 0 // not used
/* table क्रम volume target calculation */
अटल स्थिर अचिन्हित लघु voltarget[16] = अणु
	0xEAC0, 0xE0C8, 0xD740, 0xCE20, 0xC560, 0xBD08, 0xB500, 0xAD58,
	0xA5F8, 0x9EF0, 0x9830, 0x91C0, 0x8B90, 0x85A8, 0x8000, 0x7A90
पूर्ण;
#पूर्ण_अगर

#घोषणा LO_BYTE(v)	((v) & 0xff)
#घोषणा HI_BYTE(v)	(((v) >> 8) & 0xff)

/*
 * Sets up the voice काष्ठाure by calculating some values that
 * will be needed later.
 */
अटल व्योम
setup_voice(काष्ठा snd_emux_voice *vp)
अणु
	काष्ठा soundfont_voice_parm *parm;
	पूर्णांक pitch;

	/* copy the original रेजिस्टर values */
	vp->reg = vp->zone->v;

#अगर_घोषित SNDRV_EMUX_USE_RAW_EFFECT
	snd_emux_setup_effect(vp);
#पूर्ण_अगर

	/* reset status */
	vp->apan = -1;
	vp->avol = -1;
	vp->apitch = -1;

	calc_volume(vp);
	calc_pitch(vp);
	calc_pan(vp);

	parm = &vp->reg.parm;

	/* compute filter target and correct modulation parameters */
	अगर (LO_BYTE(parm->modatkhld) >= 0x80 && parm->moddelay >= 0x8000) अणु
		parm->moddelay = 0xbfff;
		pitch = (HI_BYTE(parm->pefe) << 4) + vp->apitch;
		अगर (pitch > 0xffff)
			pitch = 0xffff;
		/* calculate filter target */
		vp->ftarget = parm->cutoff + LO_BYTE(parm->pefe);
		LIMITVALUE(vp->ftarget, 0, 255);
		vp->ftarget <<= 8;
	पूर्ण अन्यथा अणु
		vp->ftarget = parm->cutoff;
		vp->ftarget <<= 8;
		pitch = vp->apitch;
	पूर्ण

	/* compute pitch target */
	अगर (pitch != 0xffff) अणु
		vp->ptarget = 1 << (pitch >> 12);
		अगर (pitch & 0x800) vp->ptarget += (vp->ptarget*0x102e)/0x2710;
		अगर (pitch & 0x400) vp->ptarget += (vp->ptarget*0x764)/0x2710;
		अगर (pitch & 0x200) vp->ptarget += (vp->ptarget*0x389)/0x2710;
		vp->ptarget += (vp->ptarget >> 1);
		अगर (vp->ptarget > 0xffff) vp->ptarget = 0xffff;
	पूर्ण अन्यथा
		vp->ptarget = 0xffff;

	अगर (LO_BYTE(parm->modatkhld) >= 0x80) अणु
		parm->modatkhld &= ~0xff;
		parm->modatkhld |= 0x7f;
	पूर्ण

	/* compute volume target and correct volume parameters */
	vp->vtarget = 0;
#अगर 0 /* FIXME: this leads to some clicks.. */
	अगर (LO_BYTE(parm->volatkhld) >= 0x80 && parm->voldelay >= 0x8000) अणु
		parm->voldelay = 0xbfff;
		vp->vtarget = voltarget[vp->avol % 0x10] >> (vp->avol >> 4);
	पूर्ण
#पूर्ण_अगर

	अगर (LO_BYTE(parm->volatkhld) >= 0x80) अणु
		parm->volatkhld &= ~0xff;
		parm->volatkhld |= 0x7f;
	पूर्ण
पूर्ण

/*
 * calculate pitch parameter
 */
अटल स्थिर अचिन्हित अक्षर pan_volumes[256] = अणु
0x00,0x03,0x06,0x09,0x0c,0x0f,0x12,0x14,0x17,0x1a,0x1d,0x20,0x22,0x25,0x28,0x2a,
0x2d,0x30,0x32,0x35,0x37,0x3a,0x3c,0x3f,0x41,0x44,0x46,0x49,0x4b,0x4d,0x50,0x52,
0x54,0x57,0x59,0x5b,0x5d,0x60,0x62,0x64,0x66,0x68,0x6a,0x6c,0x6f,0x71,0x73,0x75,
0x77,0x79,0x7b,0x7c,0x7e,0x80,0x82,0x84,0x86,0x88,0x89,0x8b,0x8d,0x8f,0x90,0x92,
0x94,0x96,0x97,0x99,0x9a,0x9c,0x9e,0x9f,0xa1,0xa2,0xa4,0xa5,0xa7,0xa8,0xaa,0xab,
0xad,0xae,0xaf,0xb1,0xb2,0xb3,0xb5,0xb6,0xb7,0xb9,0xba,0xbb,0xbc,0xbe,0xbf,0xc0,
0xc1,0xc2,0xc3,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,
0xd2,0xd3,0xd4,0xd5,0xd6,0xd7,0xd7,0xd8,0xd9,0xda,0xdb,0xdc,0xdc,0xdd,0xde,0xdf,
0xdf,0xe0,0xe1,0xe2,0xe2,0xe3,0xe4,0xe4,0xe5,0xe6,0xe6,0xe7,0xe8,0xe8,0xe9,0xe9,
0xea,0xeb,0xeb,0xec,0xec,0xed,0xed,0xee,0xee,0xef,0xef,0xf0,0xf0,0xf1,0xf1,0xf1,
0xf2,0xf2,0xf3,0xf3,0xf3,0xf4,0xf4,0xf5,0xf5,0xf5,0xf6,0xf6,0xf6,0xf7,0xf7,0xf7,
0xf7,0xf8,0xf8,0xf8,0xf9,0xf9,0xf9,0xf9,0xf9,0xfa,0xfa,0xfa,0xfa,0xfb,0xfb,0xfb,
0xfb,0xfb,0xfc,0xfc,0xfc,0xfc,0xfc,0xfc,0xfc,0xfd,0xfd,0xfd,0xfd,0xfd,0xfd,0xfd,
0xfd,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
पूर्ण;

अटल पूर्णांक
calc_pan(काष्ठा snd_emux_voice *vp)
अणु
	काष्ठा snd_midi_channel *chan = vp->chan;
	पूर्णांक pan;

	/* pan & loop start (pan 8bit, MSB, 0:right, 0xff:left) */
	अगर (vp->reg.fixpan > 0)	/* 0-127 */
		pan = 255 - (पूर्णांक)vp->reg.fixpan * 2;
	अन्यथा अणु
		pan = chan->control[MIDI_CTL_MSB_PAN] - 64;
		अगर (vp->reg.pan >= 0) /* 0-127 */
			pan += vp->reg.pan - 64;
		pan = 127 - (पूर्णांक)pan * 2;
	पूर्ण
	LIMITVALUE(pan, 0, 255);

	अगर (vp->emu->linear_panning) अणु
		/* assuming linear volume */
		अगर (pan != vp->apan) अणु
			vp->apan = pan;
			अगर (pan == 0)
				vp->aaux = 0xff;
			अन्यथा
				vp->aaux = (-pan) & 0xff;
			वापस 1;
		पूर्ण अन्यथा
			वापस 0;
	पूर्ण अन्यथा अणु
		/* using volume table */
		अगर (vp->apan != (पूर्णांक)pan_volumes[pan]) अणु
			vp->apan = pan_volumes[pan];
			vp->aaux = pan_volumes[255 - pan];
			वापस 1;
		पूर्ण
		वापस 0;
	पूर्ण
पूर्ण


/*
 * calculate volume attenuation
 *
 * Voice volume is controlled by volume attenuation parameter.
 * So volume becomes maximum when avol is 0 (no attenuation), and
 * minimum when 255 (-96dB or silence).
 */

/* tables क्रम volume->attenuation calculation */
अटल स्थिर अचिन्हित अक्षर voltab1[128] = अणु
   0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63,
   0x63, 0x2b, 0x29, 0x28, 0x27, 0x26, 0x25, 0x24, 0x23, 0x22,
   0x21, 0x20, 0x1f, 0x1e, 0x1e, 0x1d, 0x1c, 0x1b, 0x1b, 0x1a,
   0x19, 0x19, 0x18, 0x17, 0x17, 0x16, 0x16, 0x15, 0x15, 0x14,
   0x14, 0x13, 0x13, 0x13, 0x12, 0x12, 0x11, 0x11, 0x11, 0x10,
   0x10, 0x10, 0x0f, 0x0f, 0x0f, 0x0e, 0x0e, 0x0e, 0x0e, 0x0d,
   0x0d, 0x0d, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0b, 0x0b, 0x0b,
   0x0b, 0x0a, 0x0a, 0x0a, 0x0a, 0x09, 0x09, 0x09, 0x09, 0x09,
   0x08, 0x08, 0x08, 0x08, 0x08, 0x07, 0x07, 0x07, 0x07, 0x06,
   0x06, 0x06, 0x06, 0x06, 0x05, 0x05, 0x05, 0x05, 0x05, 0x04,
   0x04, 0x04, 0x04, 0x04, 0x03, 0x03, 0x03, 0x03, 0x03, 0x02,
   0x02, 0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01,
   0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
पूर्ण;

अटल स्थिर अचिन्हित अक्षर voltab2[128] = अणु
   0x32, 0x31, 0x30, 0x2f, 0x2e, 0x2d, 0x2c, 0x2b, 0x2a, 0x2a,
   0x29, 0x28, 0x27, 0x26, 0x25, 0x24, 0x24, 0x23, 0x22, 0x21,
   0x21, 0x20, 0x1f, 0x1e, 0x1e, 0x1d, 0x1c, 0x1c, 0x1b, 0x1a,
   0x1a, 0x19, 0x19, 0x18, 0x18, 0x17, 0x16, 0x16, 0x15, 0x15,
   0x14, 0x14, 0x13, 0x13, 0x13, 0x12, 0x12, 0x11, 0x11, 0x10,
   0x10, 0x10, 0x0f, 0x0f, 0x0f, 0x0e, 0x0e, 0x0e, 0x0d, 0x0d,
   0x0d, 0x0c, 0x0c, 0x0c, 0x0b, 0x0b, 0x0b, 0x0b, 0x0a, 0x0a,
   0x0a, 0x0a, 0x09, 0x09, 0x09, 0x09, 0x09, 0x08, 0x08, 0x08,
   0x08, 0x08, 0x07, 0x07, 0x07, 0x07, 0x07, 0x06, 0x06, 0x06,
   0x06, 0x06, 0x06, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
   0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x03, 0x03, 0x03, 0x03,
   0x03, 0x03, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x01, 0x01,
   0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00
पूर्ण;

अटल स्थिर अचिन्हित अक्षर expressiontab[128] = अणु
   0x7f, 0x6c, 0x62, 0x5a, 0x54, 0x50, 0x4b, 0x48, 0x45, 0x42,
   0x40, 0x3d, 0x3b, 0x39, 0x38, 0x36, 0x34, 0x33, 0x31, 0x30,
   0x2f, 0x2d, 0x2c, 0x2b, 0x2a, 0x29, 0x28, 0x27, 0x26, 0x25,
   0x24, 0x24, 0x23, 0x22, 0x21, 0x21, 0x20, 0x1f, 0x1e, 0x1e,
   0x1d, 0x1d, 0x1c, 0x1b, 0x1b, 0x1a, 0x1a, 0x19, 0x18, 0x18,
   0x17, 0x17, 0x16, 0x16, 0x15, 0x15, 0x15, 0x14, 0x14, 0x13,
   0x13, 0x12, 0x12, 0x11, 0x11, 0x11, 0x10, 0x10, 0x0f, 0x0f,
   0x0f, 0x0e, 0x0e, 0x0e, 0x0d, 0x0d, 0x0d, 0x0c, 0x0c, 0x0c,
   0x0b, 0x0b, 0x0b, 0x0a, 0x0a, 0x0a, 0x09, 0x09, 0x09, 0x09,
   0x08, 0x08, 0x08, 0x07, 0x07, 0x07, 0x07, 0x06, 0x06, 0x06,
   0x06, 0x05, 0x05, 0x05, 0x04, 0x04, 0x04, 0x04, 0x04, 0x03,
   0x03, 0x03, 0x03, 0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 0x01,
   0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
पूर्ण;

/*
 * Magic to calculate the volume (actually attenuation) from all the
 * voice and channels parameters.
 */
अटल पूर्णांक
calc_volume(काष्ठा snd_emux_voice *vp)
अणु
	पूर्णांक vol;
	पूर्णांक मुख्य_vol, expression_vol, master_vol;
	काष्ठा snd_midi_channel *chan = vp->chan;
	काष्ठा snd_emux_port *port = vp->port;

	expression_vol = chan->control[MIDI_CTL_MSB_EXPRESSION];
	LIMITMAX(vp->velocity, 127);
	LIMITVALUE(expression_vol, 0, 127);
	अगर (port->port_mode == SNDRV_EMUX_PORT_MODE_OSS_SYNTH) अणु
		/* 0 - 127 */
		मुख्य_vol = chan->control[MIDI_CTL_MSB_MAIN_VOLUME];
		vol = (vp->velocity * मुख्य_vol * expression_vol) / (127*127);
		vol = vol * vp->reg.amplitude / 127;

		LIMITVALUE(vol, 0, 127);

		/* calc to attenuation */
		vol = snd_sf_vol_table[vol];

	पूर्ण अन्यथा अणु
		मुख्य_vol = chan->control[MIDI_CTL_MSB_MAIN_VOLUME] * vp->reg.amplitude / 127;
		LIMITVALUE(मुख्य_vol, 0, 127);

		vol = voltab1[मुख्य_vol] + voltab2[vp->velocity];
		vol = (vol * 8) / 3;
		vol += vp->reg.attenuation;
		vol += ((0x100 - vol) * expressiontab[expression_vol])/128;
	पूर्ण

	master_vol = port->chset.gs_master_volume;
	LIMITVALUE(master_vol, 0, 127);
	vol += snd_sf_vol_table[master_vol];
	vol += port->volume_atten;

#अगर_घोषित SNDRV_EMUX_USE_RAW_EFFECT
	अगर (chan->निजी) अणु
		काष्ठा snd_emux_effect_table *fx = chan->निजी;
		vol += fx->val[EMUX_FX_ATTEN];
	पूर्ण
#पूर्ण_अगर

	LIMITVALUE(vol, 0, 255);
	अगर (vp->avol == vol)
		वापस 0; /* value unchanged */

	vp->avol = vol;
	अगर (!SF_IS_DRUM_BANK(get_bank(port, chan))
	    && LO_BYTE(vp->reg.parm.volatkhld) < 0x7d) अणु
		पूर्णांक atten;
		अगर (vp->velocity < 70)
			atten = 70;
		अन्यथा
			atten = vp->velocity;
		vp->acutoff = (atten * vp->reg.parm.cutoff + 0xa0) >> 7;
	पूर्ण अन्यथा अणु
		vp->acutoff = vp->reg.parm.cutoff;
	पूर्ण

	वापस 1; /* value changed */
पूर्ण

/*
 * calculate pitch offset
 *
 * 0xE000 is no pitch offset at 44100Hz sample.
 * Every 4096 is one octave.
 */

अटल पूर्णांक
calc_pitch(काष्ठा snd_emux_voice *vp)
अणु
	काष्ठा snd_midi_channel *chan = vp->chan;
	पूर्णांक offset;

	/* calculate offset */
	अगर (vp->reg.fixkey >= 0) अणु
		offset = (vp->reg.fixkey - vp->reg.root) * 4096 / 12;
	पूर्ण अन्यथा अणु
		offset = (vp->note - vp->reg.root) * 4096 / 12;
	पूर्ण
	offset = (offset * vp->reg.scaleTuning) / 100;
	offset += vp->reg.tune * 4096 / 1200;
	अगर (chan->midi_pitchbend != 0) अणु
		/* (128 * 8192: 1 semitone) ==> (4096: 12 semitones) */
		offset += chan->midi_pitchbend * chan->gm_rpn_pitch_bend_range / 3072;
	पूर्ण

	/* tuning via RPN:
	 *   coarse = -8192 to 8192 (100 cent per 128)
	 *   fine = -8192 to 8192 (max=100cent)
	 */
	/* 4096 = 1200 cents in emu8000 parameter */
	offset += chan->gm_rpn_coarse_tuning * 4096 / (12 * 128);
	offset += chan->gm_rpn_fine_tuning / 24;

#अगर_घोषित SNDRV_EMUX_USE_RAW_EFFECT
	/* add initial pitch correction */
	अगर (chan->निजी) अणु
		काष्ठा snd_emux_effect_table *fx = chan->निजी;
		अगर (fx->flag[EMUX_FX_INIT_PITCH])
			offset += fx->val[EMUX_FX_INIT_PITCH];
	पूर्ण
#पूर्ण_अगर

	/* 0xe000: root pitch */
	offset += 0xe000 + vp->reg.rate_offset;
	offset += vp->emu->pitch_shअगरt;
	LIMITVALUE(offset, 0, 0xffff);
	अगर (offset == vp->apitch)
		वापस 0; /* unchanged */
	vp->apitch = offset;
	वापस 1; /* value changed */
पूर्ण

/*
 * Get the bank number asचिन्हित to the channel
 */
अटल पूर्णांक
get_bank(काष्ठा snd_emux_port *port, काष्ठा snd_midi_channel *chan)
अणु
	पूर्णांक val;

	चयन (port->chset.midi_mode) अणु
	हाल SNDRV_MIDI_MODE_XG:
		val = chan->control[MIDI_CTL_MSB_BANK];
		अगर (val == 127)
			वापस 128; /* वापस drum bank */
		वापस chan->control[MIDI_CTL_LSB_BANK];

	हाल SNDRV_MIDI_MODE_GS:
		अगर (chan->drum_channel)
			वापस 128;
		/* ignore LSB (bank map) */
		वापस chan->control[MIDI_CTL_MSB_BANK];
		
	शेष:
		अगर (chan->drum_channel)
			वापस 128;
		वापस chan->control[MIDI_CTL_MSB_BANK];
	पूर्ण
पूर्ण


/* Look क्रम the zones matching with the given note and velocity.
 * The resultant zones are stored on table.
 */
अटल पूर्णांक
get_zone(काष्ठा snd_emux *emu, काष्ठा snd_emux_port *port,
	 पूर्णांक *notep, पूर्णांक vel, काष्ठा snd_midi_channel *chan,
	 काष्ठा snd_sf_zone **table)
अणु
	पूर्णांक preset, bank, def_preset, def_bank;

	bank = get_bank(port, chan);
	preset = chan->midi_program;

	अगर (SF_IS_DRUM_BANK(bank)) अणु
		def_preset = port->ctrls[EMUX_MD_DEF_DRUM];
		def_bank = bank;
	पूर्ण अन्यथा अणु
		def_preset = preset;
		def_bank = port->ctrls[EMUX_MD_DEF_BANK];
	पूर्ण

	वापस snd_soundfont_search_zone(emu->sflist, notep, vel, preset, bank,
					 def_preset, def_bank,
					 table, SNDRV_EMUX_MAX_MULTI_VOICES);
पूर्ण

/*
 */
व्योम
snd_emux_init_voices(काष्ठा snd_emux *emu)
अणु
	काष्ठा snd_emux_voice *vp;
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&emu->voice_lock, flags);
	क्रम (i = 0; i < emu->max_voices; i++) अणु
		vp = &emu->voices[i];
		vp->ch = -1; /* not used */
		vp->state = SNDRV_EMUX_ST_OFF;
		vp->chan = शून्य;
		vp->port = शून्य;
		vp->समय = 0;
		vp->emu = emu;
		vp->hw = emu->hw;
	पूर्ण
	spin_unlock_irqrestore(&emu->voice_lock, flags);
पूर्ण

/*
 */
व्योम snd_emux_lock_voice(काष्ठा snd_emux *emu, पूर्णांक voice)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&emu->voice_lock, flags);
	अगर (emu->voices[voice].state == SNDRV_EMUX_ST_OFF)
		emu->voices[voice].state = SNDRV_EMUX_ST_LOCKED;
	अन्यथा
		snd_prपूर्णांकk(KERN_WARNING
			   "invalid voice for lock %d (state = %x)\n",
			   voice, emu->voices[voice].state);
	spin_unlock_irqrestore(&emu->voice_lock, flags);
पूर्ण

EXPORT_SYMBOL(snd_emux_lock_voice);

/*
 */
व्योम snd_emux_unlock_voice(काष्ठा snd_emux *emu, पूर्णांक voice)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&emu->voice_lock, flags);
	अगर (emu->voices[voice].state == SNDRV_EMUX_ST_LOCKED)
		emu->voices[voice].state = SNDRV_EMUX_ST_OFF;
	अन्यथा
		snd_prपूर्णांकk(KERN_WARNING
			   "invalid voice for unlock %d (state = %x)\n",
			   voice, emu->voices[voice].state);
	spin_unlock_irqrestore(&emu->voice_lock, flags);
पूर्ण

EXPORT_SYMBOL(snd_emux_unlock_voice);
