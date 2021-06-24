<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  synth callback routines क्रम Emu10k1
 *
 *  Copyright (C) 2000 Takashi Iwai <tiwai@suse.de>
 */

#समावेश <linux/export.h>
#समावेश "emu10k1_synth_local.h"
#समावेश <sound/asoundef.h>

/* voice status */
क्रमागत अणु
	V_FREE=0, V_OFF, V_RELEASED, V_PLAYING, V_END
पूर्ण;

/* Keeps track of what we are finding */
काष्ठा best_voice अणु
	अचिन्हित पूर्णांक समय;
	पूर्णांक voice;
पूर्ण;

/*
 * prototypes
 */
अटल व्योम lookup_voices(काष्ठा snd_emux *emux, काष्ठा snd_emu10k1 *hw,
			  काष्ठा best_voice *best, पूर्णांक active_only);
अटल काष्ठा snd_emux_voice *get_voice(काष्ठा snd_emux *emux,
					काष्ठा snd_emux_port *port);
अटल पूर्णांक start_voice(काष्ठा snd_emux_voice *vp);
अटल व्योम trigger_voice(काष्ठा snd_emux_voice *vp);
अटल व्योम release_voice(काष्ठा snd_emux_voice *vp);
अटल व्योम update_voice(काष्ठा snd_emux_voice *vp, पूर्णांक update);
अटल व्योम terminate_voice(काष्ठा snd_emux_voice *vp);
अटल व्योम मुक्त_voice(काष्ठा snd_emux_voice *vp);
अटल व्योम set_fmmod(काष्ठा snd_emu10k1 *hw, काष्ठा snd_emux_voice *vp);
अटल व्योम set_fm2frq2(काष्ठा snd_emu10k1 *hw, काष्ठा snd_emux_voice *vp);
अटल व्योम set_filterQ(काष्ठा snd_emu10k1 *hw, काष्ठा snd_emux_voice *vp);

/*
 * Ensure a value is between two poपूर्णांकs
 * macro evaluates its args more than once, so changed to upper-हाल.
 */
#घोषणा LIMITVALUE(x, a, b) करो अणु अगर ((x) < (a)) (x) = (a); अन्यथा अगर ((x) > (b)) (x) = (b); पूर्ण जबतक (0)
#घोषणा LIMITMAX(x, a) करो अणुअगर ((x) > (a)) (x) = (a); पूर्ण जबतक (0)


/*
 * set up चालकs
 */
अटल स्थिर काष्ठा snd_emux_चालकs emu10k1_ops = अणु
	.owner =	THIS_MODULE,
	.get_voice =	get_voice,
	.prepare =	start_voice,
	.trigger =	trigger_voice,
	.release =	release_voice,
	.update =	update_voice,
	.terminate =	terminate_voice,
	.मुक्त_voice =	मुक्त_voice,
	.sample_new =	snd_emu10k1_sample_new,
	.sample_मुक्त =	snd_emu10k1_sample_मुक्त,
पूर्ण;

व्योम
snd_emu10k1_ops_setup(काष्ठा snd_emux *emux)
अणु
	emux->ops = emu10k1_ops;
पूर्ण


/*
 * get more voice क्रम pcm
 *
 * terminate most inactive voice and give it as a pcm voice.
 *
 * voice_lock is alपढ़ोy held.
 */
पूर्णांक
snd_emu10k1_synth_get_voice(काष्ठा snd_emu10k1 *hw)
अणु
	काष्ठा snd_emux *emu;
	काष्ठा snd_emux_voice *vp;
	काष्ठा best_voice best[V_END];
	पूर्णांक i;

	emu = hw->synth;

	lookup_voices(emu, hw, best, 1); /* no OFF voices */
	क्रम (i = 0; i < V_END; i++) अणु
		अगर (best[i].voice >= 0) अणु
			पूर्णांक ch;
			vp = &emu->voices[best[i].voice];
			अगर ((ch = vp->ch) < 0) अणु
				/*
				dev_warn(emu->card->dev,
				       "synth_get_voice: ch < 0 (%d) ??", i);
				*/
				जारी;
			पूर्ण
			vp->emu->num_voices--;
			vp->ch = -1;
			vp->state = SNDRV_EMUX_ST_OFF;
			वापस ch;
		पूर्ण
	पूर्ण

	/* not found */
	वापस -ENOMEM;
पूर्ण


/*
 * turn off the voice (not terminated)
 */
अटल व्योम
release_voice(काष्ठा snd_emux_voice *vp)
अणु
	पूर्णांक dcysusv;
	काष्ठा snd_emu10k1 *hw;
	
	hw = vp->hw;
	dcysusv = 0x8000 | (अचिन्हित अक्षर)vp->reg.parm.modrelease;
	snd_emu10k1_ptr_ग_लिखो(hw, DCYSUSM, vp->ch, dcysusv);
	dcysusv = 0x8000 | (अचिन्हित अक्षर)vp->reg.parm.volrelease | DCYSUSV_CHANNELENABLE_MASK;
	snd_emu10k1_ptr_ग_लिखो(hw, DCYSUSV, vp->ch, dcysusv);
पूर्ण


/*
 * terminate the voice
 */
अटल व्योम
terminate_voice(काष्ठा snd_emux_voice *vp)
अणु
	काष्ठा snd_emu10k1 *hw;
	
	अगर (snd_BUG_ON(!vp))
		वापस;
	hw = vp->hw;
	snd_emu10k1_ptr_ग_लिखो(hw, DCYSUSV, vp->ch, 0x807f | DCYSUSV_CHANNELENABLE_MASK);
	अगर (vp->block) अणु
		काष्ठा snd_emu10k1_memblk *emem;
		emem = (काष्ठा snd_emu10k1_memblk *)vp->block;
		अगर (emem->map_locked > 0)
			emem->map_locked--;
	पूर्ण
पूर्ण

/*
 * release the voice to प्रणाली
 */
अटल व्योम
मुक्त_voice(काष्ठा snd_emux_voice *vp)
अणु
	काष्ठा snd_emu10k1 *hw;
	
	hw = vp->hw;
	/* FIXME: emu10k1_synth is broken. */
	/* This can get called with hw == 0 */
	/* Problem apparent on plug, unplug then plug */
	/* on the Audigy 2 ZS Notebook. */
	अगर (hw && (vp->ch >= 0)) अणु
		snd_emu10k1_ptr_ग_लिखो(hw, IFATN, vp->ch, 0xff00);
		snd_emu10k1_ptr_ग_लिखो(hw, DCYSUSV, vp->ch, 0x807f | DCYSUSV_CHANNELENABLE_MASK);
		// snd_emu10k1_ptr_ग_लिखो(hw, DCYSUSV, vp->ch, 0);
		snd_emu10k1_ptr_ग_लिखो(hw, VTFT, vp->ch, 0xffff);
		snd_emu10k1_ptr_ग_लिखो(hw, CVCF, vp->ch, 0xffff);
		snd_emu10k1_voice_मुक्त(hw, &hw->voices[vp->ch]);
		vp->emu->num_voices--;
		vp->ch = -1;
	पूर्ण
पूर्ण


/*
 * update रेजिस्टरs
 */
अटल व्योम
update_voice(काष्ठा snd_emux_voice *vp, पूर्णांक update)
अणु
	काष्ठा snd_emu10k1 *hw;
	
	hw = vp->hw;
	अगर (update & SNDRV_EMUX_UPDATE_VOLUME)
		snd_emu10k1_ptr_ग_लिखो(hw, IFATN_ATTENUATION, vp->ch, vp->avol);
	अगर (update & SNDRV_EMUX_UPDATE_PITCH)
		snd_emu10k1_ptr_ग_लिखो(hw, IP, vp->ch, vp->apitch);
	अगर (update & SNDRV_EMUX_UPDATE_PAN) अणु
		snd_emu10k1_ptr_ग_लिखो(hw, PTRX_FXSENDAMOUNT_A, vp->ch, vp->apan);
		snd_emu10k1_ptr_ग_लिखो(hw, PTRX_FXSENDAMOUNT_B, vp->ch, vp->aaux);
	पूर्ण
	अगर (update & SNDRV_EMUX_UPDATE_FMMOD)
		set_fmmod(hw, vp);
	अगर (update & SNDRV_EMUX_UPDATE_TREMFREQ)
		snd_emu10k1_ptr_ग_लिखो(hw, TREMFRQ, vp->ch, vp->reg.parm.tremfrq);
	अगर (update & SNDRV_EMUX_UPDATE_FM2FRQ2)
		set_fm2frq2(hw, vp);
	अगर (update & SNDRV_EMUX_UPDATE_Q)
		set_filterQ(hw, vp);
पूर्ण


/*
 * look up voice table - get the best voice in order of preference
 */
/* spinlock held! */
अटल व्योम
lookup_voices(काष्ठा snd_emux *emu, काष्ठा snd_emu10k1 *hw,
	      काष्ठा best_voice *best, पूर्णांक active_only)
अणु
	काष्ठा snd_emux_voice *vp;
	काष्ठा best_voice *bp;
	पूर्णांक  i;

	क्रम (i = 0; i < V_END; i++) अणु
		best[i].समय = (अचिन्हित पूर्णांक)-1; /* XXX MAX_?INT really */
		best[i].voice = -1;
	पूर्ण

	/*
	 * Go through them all and get a best one to use.
	 * NOTE: could also look at volume and pick the quietest one.
	 */
	क्रम (i = 0; i < emu->max_voices; i++) अणु
		पूर्णांक state, val;

		vp = &emu->voices[i];
		state = vp->state;
		अगर (state == SNDRV_EMUX_ST_OFF) अणु
			अगर (vp->ch < 0) अणु
				अगर (active_only)
					जारी;
				bp = best + V_FREE;
			पूर्ण अन्यथा
				bp = best + V_OFF;
		पूर्ण
		अन्यथा अगर (state == SNDRV_EMUX_ST_RELEASED ||
			 state == SNDRV_EMUX_ST_PENDING) अणु
			bp = best + V_RELEASED;
#अगर 1
			val = snd_emu10k1_ptr_पढ़ो(hw, CVCF_CURRENTVOL, vp->ch);
			अगर (! val)
				bp = best + V_OFF;
#पूर्ण_अगर
		पूर्ण
		अन्यथा अगर (state == SNDRV_EMUX_ST_STANDBY)
			जारी;
		अन्यथा अगर (state & SNDRV_EMUX_ST_ON)
			bp = best + V_PLAYING;
		अन्यथा
			जारी;

		/* check अगर sample is finished playing (non-looping only) */
		अगर (bp != best + V_OFF && bp != best + V_FREE &&
		    (vp->reg.sample_mode & SNDRV_SFNT_SAMPLE_SINGLESHOT)) अणु
			val = snd_emu10k1_ptr_पढ़ो(hw, CCCA_CURRADDR, vp->ch);
			अगर (val >= vp->reg.loopstart)
				bp = best + V_OFF;
		पूर्ण

		अगर (vp->समय < bp->समय) अणु
			bp->समय = vp->समय;
			bp->voice = i;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * get an empty voice
 *
 * emu->voice_lock is alपढ़ोy held.
 */
अटल काष्ठा snd_emux_voice *
get_voice(काष्ठा snd_emux *emu, काष्ठा snd_emux_port *port)
अणु
	काष्ठा snd_emu10k1 *hw;
	काष्ठा snd_emux_voice *vp;
	काष्ठा best_voice best[V_END];
	पूर्णांक i;

	hw = emu->hw;

	lookup_voices(emu, hw, best, 0);
	क्रम (i = 0; i < V_END; i++) अणु
		अगर (best[i].voice >= 0) अणु
			vp = &emu->voices[best[i].voice];
			अगर (vp->ch < 0) अणु
				/* allocate a voice */
				काष्ठा snd_emu10k1_voice *hwvoice;
				अगर (snd_emu10k1_voice_alloc(hw, EMU10K1_SYNTH, 1, &hwvoice) < 0 || hwvoice == शून्य)
					जारी;
				vp->ch = hwvoice->number;
				emu->num_voices++;
			पूर्ण
			वापस vp;
		पूर्ण
	पूर्ण

	/* not found */
	वापस शून्य;
पूर्ण

/*
 * prepare envelopes and LFOs
 */
अटल पूर्णांक
start_voice(काष्ठा snd_emux_voice *vp)
अणु
	अचिन्हित पूर्णांक temp;
	पूर्णांक ch;
	अचिन्हित पूर्णांक addr, mapped_offset;
	काष्ठा snd_midi_channel *chan;
	काष्ठा snd_emu10k1 *hw;
	काष्ठा snd_emu10k1_memblk *emem;
	
	hw = vp->hw;
	ch = vp->ch;
	अगर (snd_BUG_ON(ch < 0))
		वापस -EINVAL;
	chan = vp->chan;

	emem = (काष्ठा snd_emu10k1_memblk *)vp->block;
	अगर (emem == शून्य)
		वापस -EINVAL;
	emem->map_locked++;
	अगर (snd_emu10k1_memblk_map(hw, emem) < 0) अणु
		/* dev_err(hw->card->devK, "emu: cannot map!\n"); */
		वापस -ENOMEM;
	पूर्ण
	mapped_offset = snd_emu10k1_memblk_offset(emem) >> 1;
	vp->reg.start += mapped_offset;
	vp->reg.end += mapped_offset;
	vp->reg.loopstart += mapped_offset;
	vp->reg.loखोलोd += mapped_offset;

	/* set channel routing */
	/* A = left(0), B = right(1), C = reverb(c), D = chorus(d) */
	अगर (hw->audigy) अणु
		temp = FXBUS_MIDI_LEFT | (FXBUS_MIDI_RIGHT << 8) | 
			(FXBUS_MIDI_REVERB << 16) | (FXBUS_MIDI_CHORUS << 24);
		snd_emu10k1_ptr_ग_लिखो(hw, A_FXRT1, ch, temp);
	पूर्ण अन्यथा अणु
		temp = (FXBUS_MIDI_LEFT << 16) | (FXBUS_MIDI_RIGHT << 20) | 
			(FXBUS_MIDI_REVERB << 24) | (FXBUS_MIDI_CHORUS << 28);
		snd_emu10k1_ptr_ग_लिखो(hw, FXRT, ch, temp);
	पूर्ण

	/* channel to be silent and idle */
	snd_emu10k1_ptr_ग_लिखो(hw, DCYSUSV, ch, 0x0000);
	snd_emu10k1_ptr_ग_लिखो(hw, VTFT, ch, 0x0000FFFF);
	snd_emu10k1_ptr_ग_लिखो(hw, CVCF, ch, 0x0000FFFF);
	snd_emu10k1_ptr_ग_लिखो(hw, PTRX, ch, 0);
	snd_emu10k1_ptr_ग_लिखो(hw, CPF, ch, 0);

	/* set pitch offset */
	snd_emu10k1_ptr_ग_लिखो(hw, IP, vp->ch, vp->apitch);

	/* set envelope parameters */
	snd_emu10k1_ptr_ग_लिखो(hw, ENVVAL, ch, vp->reg.parm.moddelay);
	snd_emu10k1_ptr_ग_लिखो(hw, ATKHLDM, ch, vp->reg.parm.modatkhld);
	snd_emu10k1_ptr_ग_लिखो(hw, DCYSUSM, ch, vp->reg.parm.moddcysus);
	snd_emu10k1_ptr_ग_लिखो(hw, ENVVOL, ch, vp->reg.parm.voldelay);
	snd_emu10k1_ptr_ग_लिखो(hw, ATKHLDV, ch, vp->reg.parm.volatkhld);
	/* decay/sustain parameter क्रम volume envelope is used
	   क्रम triggerg the voice */

	/* cutoff and volume */
	temp = (अचिन्हित पूर्णांक)vp->acutoff << 8 | (अचिन्हित अक्षर)vp->avol;
	snd_emu10k1_ptr_ग_लिखो(hw, IFATN, vp->ch, temp);

	/* modulation envelope heights */
	snd_emu10k1_ptr_ग_लिखो(hw, PEFE, ch, vp->reg.parm.pefe);

	/* lfo1/2 delay */
	snd_emu10k1_ptr_ग_लिखो(hw, LFOVAL1, ch, vp->reg.parm.lfo1delay);
	snd_emu10k1_ptr_ग_लिखो(hw, LFOVAL2, ch, vp->reg.parm.lfo2delay);

	/* lfo1 pitch & cutoff shअगरt */
	set_fmmod(hw, vp);
	/* lfo1 volume & freq */
	snd_emu10k1_ptr_ग_लिखो(hw, TREMFRQ, vp->ch, vp->reg.parm.tremfrq);
	/* lfo2 pitch & freq */
	set_fm2frq2(hw, vp);

	/* reverb and loop start (reverb 8bit, MSB) */
	temp = vp->reg.parm.reverb;
	temp += (पूर्णांक)vp->chan->control[MIDI_CTL_E1_REVERB_DEPTH] * 9 / 10;
	LIMITMAX(temp, 255);
	addr = vp->reg.loopstart;
	snd_emu10k1_ptr_ग_लिखो(hw, PSST, vp->ch, (temp << 24) | addr);

	/* chorus & loop end (chorus 8bit, MSB) */
	addr = vp->reg.loखोलोd;
	temp = vp->reg.parm.chorus;
	temp += (पूर्णांक)chan->control[MIDI_CTL_E3_CHORUS_DEPTH] * 9 / 10;
	LIMITMAX(temp, 255);
	temp = (temp <<24) | addr;
	snd_emu10k1_ptr_ग_लिखो(hw, DSL, ch, temp);

	/* clear filter delay memory */
	snd_emu10k1_ptr_ग_लिखो(hw, Z1, ch, 0);
	snd_emu10k1_ptr_ग_लिखो(hw, Z2, ch, 0);

	/* invalidate maps */
	temp = (hw->silent_page.addr << hw->address_mode) | (hw->address_mode ? MAP_PTI_MASK1 : MAP_PTI_MASK0);
	snd_emu10k1_ptr_ग_लिखो(hw, MAPA, ch, temp);
	snd_emu10k1_ptr_ग_लिखो(hw, MAPB, ch, temp);
#अगर 0
	/* cache */
	अणु
		अचिन्हित पूर्णांक val, sample;
		val = 32;
		अगर (vp->reg.sample_mode & SNDRV_SFNT_SAMPLE_8BITS)
			sample = 0x80808080;
		अन्यथा अणु
			sample = 0;
			val *= 2;
		पूर्ण

		/* cache */
		snd_emu10k1_ptr_ग_लिखो(hw, CCR, ch, 0x1c << 16);
		snd_emu10k1_ptr_ग_लिखो(hw, CDE, ch, sample);
		snd_emu10k1_ptr_ग_लिखो(hw, CDF, ch, sample);

		/* invalidate maps */
		temp = ((अचिन्हित पूर्णांक)hw->silent_page.addr << hw_address_mode) | (hw->address_mode ? MAP_PTI_MASK1 : MAP_PTI_MASK0);
		snd_emu10k1_ptr_ग_लिखो(hw, MAPA, ch, temp);
		snd_emu10k1_ptr_ग_लिखो(hw, MAPB, ch, temp);
		
		/* fill cache */
		val -= 4;
		val <<= 25;
		val |= 0x1c << 16;
		snd_emu10k1_ptr_ग_लिखो(hw, CCR, ch, val);
	पूर्ण
#पूर्ण_अगर

	/* Q & current address (Q 4bit value, MSB) */
	addr = vp->reg.start;
	temp = vp->reg.parm.filterQ;
	temp = (temp<<28) | addr;
	अगर (vp->apitch < 0xe400)
		temp |= CCCA_INTERPROM_0;
	अन्यथा अणु
		अचिन्हित पूर्णांक shअगरt = (vp->apitch - 0xe000) >> 10;
		temp |= shअगरt << 25;
	पूर्ण
	अगर (vp->reg.sample_mode & SNDRV_SFNT_SAMPLE_8BITS)
		temp |= CCCA_8BITSELECT;
	snd_emu10k1_ptr_ग_लिखो(hw, CCCA, ch, temp);

	/* reset volume */
	temp = (अचिन्हित पूर्णांक)vp->vtarget << 16;
	snd_emu10k1_ptr_ग_लिखो(hw, VTFT, ch, temp | vp->ftarget);
	snd_emu10k1_ptr_ग_लिखो(hw, CVCF, ch, temp | 0xff00);
	वापस 0;
पूर्ण

/*
 * Start envelope
 */
अटल व्योम
trigger_voice(काष्ठा snd_emux_voice *vp)
अणु
	अचिन्हित पूर्णांक temp, ptarget;
	काष्ठा snd_emu10k1 *hw;
	काष्ठा snd_emu10k1_memblk *emem;
	
	hw = vp->hw;

	emem = (काष्ठा snd_emu10k1_memblk *)vp->block;
	अगर (! emem || emem->mapped_page < 0)
		वापस; /* not mapped */

#अगर 0
	ptarget = (अचिन्हित पूर्णांक)vp->ptarget << 16;
#अन्यथा
	ptarget = IP_TO_CP(vp->apitch);
#पूर्ण_अगर
	/* set pitch target and pan (volume) */
	temp = ptarget | (vp->apan << 8) | vp->aaux;
	snd_emu10k1_ptr_ग_लिखो(hw, PTRX, vp->ch, temp);

	/* pitch target */
	snd_emu10k1_ptr_ग_लिखो(hw, CPF, vp->ch, ptarget);

	/* trigger voice */
	snd_emu10k1_ptr_ग_लिखो(hw, DCYSUSV, vp->ch, vp->reg.parm.voldcysus|DCYSUSV_CHANNELENABLE_MASK);
पूर्ण

#घोषणा MOD_SENSE 18

/* set lfo1 modulation height and cutoff */
अटल व्योम
set_fmmod(काष्ठा snd_emu10k1 *hw, काष्ठा snd_emux_voice *vp)
अणु
	अचिन्हित लघु fmmod;
	लघु pitch;
	अचिन्हित अक्षर cutoff;
	पूर्णांक modulation;

	pitch = (अक्षर)(vp->reg.parm.fmmod>>8);
	cutoff = (vp->reg.parm.fmmod & 0xff);
	modulation = vp->chan->gm_modulation + vp->chan->midi_pressure;
	pitch += (MOD_SENSE * modulation) / 1200;
	LIMITVALUE(pitch, -128, 127);
	fmmod = ((अचिन्हित अक्षर)pitch<<8) | cutoff;
	snd_emu10k1_ptr_ग_लिखो(hw, FMMOD, vp->ch, fmmod);
पूर्ण

/* set lfo2 pitch & frequency */
अटल व्योम
set_fm2frq2(काष्ठा snd_emu10k1 *hw, काष्ठा snd_emux_voice *vp)
अणु
	अचिन्हित लघु fm2frq2;
	लघु pitch;
	अचिन्हित अक्षर freq;
	पूर्णांक modulation;

	pitch = (अक्षर)(vp->reg.parm.fm2frq2>>8);
	freq = vp->reg.parm.fm2frq2 & 0xff;
	modulation = vp->chan->gm_modulation + vp->chan->midi_pressure;
	pitch += (MOD_SENSE * modulation) / 1200;
	LIMITVALUE(pitch, -128, 127);
	fm2frq2 = ((अचिन्हित अक्षर)pitch<<8) | freq;
	snd_emu10k1_ptr_ग_लिखो(hw, FM2FRQ2, vp->ch, fm2frq2);
पूर्ण

/* set filterQ */
अटल व्योम
set_filterQ(काष्ठा snd_emu10k1 *hw, काष्ठा snd_emux_voice *vp)
अणु
	अचिन्हित पूर्णांक val;
	val = snd_emu10k1_ptr_पढ़ो(hw, CCCA, vp->ch) & ~CCCA_RESOन_अंकCE;
	val |= (vp->reg.parm.filterQ << 28);
	snd_emu10k1_ptr_ग_लिखो(hw, CCCA, vp->ch, val);
पूर्ण
