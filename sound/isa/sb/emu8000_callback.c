<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  synth callback routines क्रम the emu8000 (AWE32/64)
 *
 *  Copyright (C) 1999 Steve Ratclअगरfe
 *  Copyright (C) 1999-2000 Takashi Iwai <tiwai@suse.de>
 */

#समावेश "emu8000_local.h"
#समावेश <linux/export.h>
#समावेश <sound/asoundef.h>

/*
 * prototypes
 */
अटल काष्ठा snd_emux_voice *get_voice(काष्ठा snd_emux *emu,
					काष्ठा snd_emux_port *port);
अटल पूर्णांक start_voice(काष्ठा snd_emux_voice *vp);
अटल व्योम trigger_voice(काष्ठा snd_emux_voice *vp);
अटल व्योम release_voice(काष्ठा snd_emux_voice *vp);
अटल व्योम update_voice(काष्ठा snd_emux_voice *vp, पूर्णांक update);
अटल व्योम reset_voice(काष्ठा snd_emux *emu, पूर्णांक ch);
अटल व्योम terminate_voice(काष्ठा snd_emux_voice *vp);
अटल व्योम sysex(काष्ठा snd_emux *emu, अक्षर *buf, पूर्णांक len, पूर्णांक parsed,
		  काष्ठा snd_midi_channel_set *chset);
#अगर IS_ENABLED(CONFIG_SND_SEQUENCER_OSS)
अटल पूर्णांक oss_ioctl(काष्ठा snd_emux *emu, पूर्णांक cmd, पूर्णांक p1, पूर्णांक p2);
#पूर्ण_अगर
अटल पूर्णांक load_fx(काष्ठा snd_emux *emu, पूर्णांक type, पूर्णांक mode,
		   स्थिर व्योम __user *buf, दीर्घ len);

अटल व्योम set_pitch(काष्ठा snd_emu8000 *hw, काष्ठा snd_emux_voice *vp);
अटल व्योम set_volume(काष्ठा snd_emu8000 *hw, काष्ठा snd_emux_voice *vp);
अटल व्योम set_pan(काष्ठा snd_emu8000 *hw, काष्ठा snd_emux_voice *vp);
अटल व्योम set_fmmod(काष्ठा snd_emu8000 *hw, काष्ठा snd_emux_voice *vp);
अटल व्योम set_tremfreq(काष्ठा snd_emu8000 *hw, काष्ठा snd_emux_voice *vp);
अटल व्योम set_fm2frq2(काष्ठा snd_emu8000 *hw, काष्ठा snd_emux_voice *vp);
अटल व्योम set_filterQ(काष्ठा snd_emu8000 *hw, काष्ठा snd_emux_voice *vp);
अटल व्योम snd_emu8000_tweak_voice(काष्ठा snd_emu8000 *emu, पूर्णांक ch);

/*
 * Ensure a value is between two poपूर्णांकs
 * macro evaluates its args more than once, so changed to upper-हाल.
 */
#घोषणा LIMITVALUE(x, a, b) करो अणु अगर ((x) < (a)) (x) = (a); अन्यथा अगर ((x) > (b)) (x) = (b); पूर्ण जबतक (0)
#घोषणा LIMITMAX(x, a) करो अणुअगर ((x) > (a)) (x) = (a); पूर्ण जबतक (0)


/*
 * set up चालकs
 */
अटल स्थिर काष्ठा snd_emux_चालकs emu8000_ops = अणु
	.owner =	THIS_MODULE,
	.get_voice =	get_voice,
	.prepare =	start_voice,
	.trigger =	trigger_voice,
	.release =	release_voice,
	.update =	update_voice,
	.terminate =	terminate_voice,
	.reset =	reset_voice,
	.sample_new =	snd_emu8000_sample_new,
	.sample_मुक्त =	snd_emu8000_sample_मुक्त,
	.sample_reset = snd_emu8000_sample_reset,
	.load_fx =	load_fx,
	.sysex =	sysex,
#अगर IS_ENABLED(CONFIG_SND_SEQUENCER_OSS)
	.oss_ioctl =	oss_ioctl,
#पूर्ण_अगर
पूर्ण;

व्योम
snd_emu8000_ops_setup(काष्ठा snd_emu8000 *hw)
अणु
	hw->emu->ops = emu8000_ops;
पूर्ण



/*
 * Terminate a voice
 */
अटल व्योम
release_voice(काष्ठा snd_emux_voice *vp)
अणु
	पूर्णांक dcysusv;
	काष्ठा snd_emu8000 *hw;

	hw = vp->hw;
	dcysusv = 0x8000 | (अचिन्हित अक्षर)vp->reg.parm.modrelease;
	EMU8000_DCYSUS_WRITE(hw, vp->ch, dcysusv);
	dcysusv = 0x8000 | (अचिन्हित अक्षर)vp->reg.parm.volrelease;
	EMU8000_DCYSUSV_WRITE(hw, vp->ch, dcysusv);
पूर्ण


/*
 */
अटल व्योम
terminate_voice(काष्ठा snd_emux_voice *vp)
अणु
	काष्ठा snd_emu8000 *hw; 

	hw = vp->hw;
	EMU8000_DCYSUSV_WRITE(hw, vp->ch, 0x807F);
पूर्ण


/*
 */
अटल व्योम
update_voice(काष्ठा snd_emux_voice *vp, पूर्णांक update)
अणु
	काष्ठा snd_emu8000 *hw;

	hw = vp->hw;
	अगर (update & SNDRV_EMUX_UPDATE_VOLUME)
		set_volume(hw, vp);
	अगर (update & SNDRV_EMUX_UPDATE_PITCH)
		set_pitch(hw, vp);
	अगर ((update & SNDRV_EMUX_UPDATE_PAN) &&
	    vp->port->ctrls[EMUX_MD_REALTIME_PAN])
		set_pan(hw, vp);
	अगर (update & SNDRV_EMUX_UPDATE_FMMOD)
		set_fmmod(hw, vp);
	अगर (update & SNDRV_EMUX_UPDATE_TREMFREQ)
		set_tremfreq(hw, vp);
	अगर (update & SNDRV_EMUX_UPDATE_FM2FRQ2)
		set_fm2frq2(hw, vp);
	अगर (update & SNDRV_EMUX_UPDATE_Q)
		set_filterQ(hw, vp);
पूर्ण


/*
 * Find a channel (voice) within the EMU that is not in use or at least
 * less in use than other channels.  Always वापसs a valid poपूर्णांकer
 * no matter what.  If there is a real लघुage of voices then one
 * will be cut. Such is lअगरe.
 *
 * The channel index (vp->ch) must be initialized in this routine.
 * In Emu8k, it is identical with the array index.
 */
अटल काष्ठा snd_emux_voice *
get_voice(काष्ठा snd_emux *emu, काष्ठा snd_emux_port *port)
अणु
	पूर्णांक  i;
	काष्ठा snd_emux_voice *vp;
	काष्ठा snd_emu8000 *hw;

	/* what we are looking क्रम, in order of preference */
	क्रमागत अणु
		OFF=0, RELEASED, PLAYING, END
	पूर्ण;

	/* Keeps track of what we are finding */
	काष्ठा best अणु
		अचिन्हित पूर्णांक  समय;
		पूर्णांक voice;
	पूर्ण best[END];
	काष्ठा best *bp;

	hw = emu->hw;

	क्रम (i = 0; i < END; i++) अणु
		best[i].समय = (अचिन्हित पूर्णांक)(-1); /* XXX MAX_?INT really */
		best[i].voice = -1;
	पूर्ण

	/*
	 * Go through them all and get a best one to use.
	 */
	क्रम (i = 0; i < emu->max_voices; i++) अणु
		पूर्णांक state, val;

		vp = &emu->voices[i];
		state = vp->state;

		अगर (state == SNDRV_EMUX_ST_OFF)
			bp = best + OFF;
		अन्यथा अगर (state == SNDRV_EMUX_ST_RELEASED ||
			 state == SNDRV_EMUX_ST_PENDING) अणु
			bp = best + RELEASED;
			val = (EMU8000_CVCF_READ(hw, vp->ch) >> 16) & 0xffff;
			अगर (! val)
				bp = best + OFF;
		पूर्ण
		अन्यथा अगर (state & SNDRV_EMUX_ST_ON)
			bp = best + PLAYING;
		अन्यथा
			जारी;

		/* check अगर sample is finished playing (non-looping only) */
		अगर (state != SNDRV_EMUX_ST_OFF &&
		    (vp->reg.sample_mode & SNDRV_SFNT_SAMPLE_SINGLESHOT)) अणु
			val = EMU8000_CCCA_READ(hw, vp->ch) & 0xffffff;
			अगर (val >= vp->reg.loopstart)
				bp = best + OFF;
		पूर्ण

		अगर (vp->समय < bp->समय) अणु
			bp->समय = vp->समय;
			bp->voice = i;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < END; i++) अणु
		अगर (best[i].voice >= 0) अणु
			vp = &emu->voices[best[i].voice];
			vp->ch = best[i].voice;
			वापस vp;
		पूर्ण
	पूर्ण

	/* not found */
	वापस शून्य;
पूर्ण

/*
 */
अटल पूर्णांक
start_voice(काष्ठा snd_emux_voice *vp)
अणु
	अचिन्हित पूर्णांक temp;
	पूर्णांक ch;
	पूर्णांक addr;
	काष्ठा snd_midi_channel *chan;
	काष्ठा snd_emu8000 *hw;

	hw = vp->hw;
	ch = vp->ch;
	chan = vp->chan;

	/* channel to be silent and idle */
	EMU8000_DCYSUSV_WRITE(hw, ch, 0x0080);
	EMU8000_VTFT_WRITE(hw, ch, 0x0000FFFF);
	EMU8000_CVCF_WRITE(hw, ch, 0x0000FFFF);
	EMU8000_PTRX_WRITE(hw, ch, 0);
	EMU8000_CPF_WRITE(hw, ch, 0);

	/* set pitch offset */
	set_pitch(hw, vp);

	/* set envelope parameters */
	EMU8000_ENVVAL_WRITE(hw, ch, vp->reg.parm.moddelay);
	EMU8000_ATKHLD_WRITE(hw, ch, vp->reg.parm.modatkhld);
	EMU8000_DCYSUS_WRITE(hw, ch, vp->reg.parm.moddcysus);
	EMU8000_ENVVOL_WRITE(hw, ch, vp->reg.parm.voldelay);
	EMU8000_ATKHLDV_WRITE(hw, ch, vp->reg.parm.volatkhld);
	/* decay/sustain parameter क्रम volume envelope is used
	   क्रम triggerg the voice */

	/* cutoff and volume */
	set_volume(hw, vp);

	/* modulation envelope heights */
	EMU8000_PEFE_WRITE(hw, ch, vp->reg.parm.pefe);

	/* lfo1/2 delay */
	EMU8000_LFO1VAL_WRITE(hw, ch, vp->reg.parm.lfo1delay);
	EMU8000_LFO2VAL_WRITE(hw, ch, vp->reg.parm.lfo2delay);

	/* lfo1 pitch & cutoff shअगरt */
	set_fmmod(hw, vp);
	/* lfo1 volume & freq */
	set_tremfreq(hw, vp);
	/* lfo2 pitch & freq */
	set_fm2frq2(hw, vp);
	/* pan & loop start */
	set_pan(hw, vp);

	/* chorus & loop end (chorus 8bit, MSB) */
	addr = vp->reg.loखोलोd - 1;
	temp = vp->reg.parm.chorus;
	temp += (पूर्णांक)chan->control[MIDI_CTL_E3_CHORUS_DEPTH] * 9 / 10;
	LIMITMAX(temp, 255);
	temp = (temp <<24) | (अचिन्हित पूर्णांक)addr;
	EMU8000_CSL_WRITE(hw, ch, temp);

	/* Q & current address (Q 4bit value, MSB) */
	addr = vp->reg.start - 1;
	temp = vp->reg.parm.filterQ;
	temp = (temp<<28) | (अचिन्हित पूर्णांक)addr;
	EMU8000_CCCA_WRITE(hw, ch, temp);

	/* clear unknown रेजिस्टरs */
	EMU8000_00A0_WRITE(hw, ch, 0);
	EMU8000_0080_WRITE(hw, ch, 0);

	/* reset volume */
	temp = vp->vtarget << 16;
	EMU8000_VTFT_WRITE(hw, ch, temp | vp->ftarget);
	EMU8000_CVCF_WRITE(hw, ch, temp | 0xff00);

	वापस 0;
पूर्ण

/*
 * Start envelope
 */
अटल व्योम
trigger_voice(काष्ठा snd_emux_voice *vp)
अणु
	पूर्णांक ch = vp->ch;
	अचिन्हित पूर्णांक temp;
	काष्ठा snd_emu8000 *hw;

	hw = vp->hw;

	/* set reverb and pitch target */
	temp = vp->reg.parm.reverb;
	temp += (पूर्णांक)vp->chan->control[MIDI_CTL_E1_REVERB_DEPTH] * 9 / 10;
	LIMITMAX(temp, 255);
	temp = (temp << 8) | (vp->ptarget << 16) | vp->aaux;
	EMU8000_PTRX_WRITE(hw, ch, temp);
	EMU8000_CPF_WRITE(hw, ch, vp->ptarget << 16);
	EMU8000_DCYSUSV_WRITE(hw, ch, vp->reg.parm.voldcysus);
पूर्ण

/*
 * reset voice parameters
 */
अटल व्योम
reset_voice(काष्ठा snd_emux *emu, पूर्णांक ch)
अणु
	काष्ठा snd_emu8000 *hw;

	hw = emu->hw;
	EMU8000_DCYSUSV_WRITE(hw, ch, 0x807F);
	snd_emu8000_tweak_voice(hw, ch);
पूर्ण

/*
 * Set the pitch of a possibly playing note.
 */
अटल व्योम
set_pitch(काष्ठा snd_emu8000 *hw, काष्ठा snd_emux_voice *vp)
अणु
	EMU8000_IP_WRITE(hw, vp->ch, vp->apitch);
पूर्ण

/*
 * Set the volume of a possibly alपढ़ोy playing note
 */
अटल व्योम
set_volume(काष्ठा snd_emu8000 *hw, काष्ठा snd_emux_voice *vp)
अणु
	पूर्णांक  अगरatn;

	अगरatn = (अचिन्हित अक्षर)vp->acutoff;
	अगरatn = (अगरatn << 8);
	अगरatn |= (अचिन्हित अक्षर)vp->avol;
	EMU8000_IFATN_WRITE(hw, vp->ch, अगरatn);
पूर्ण

/*
 * Set pan and loop start address.
 */
अटल व्योम
set_pan(काष्ठा snd_emu8000 *hw, काष्ठा snd_emux_voice *vp)
अणु
	अचिन्हित पूर्णांक temp;

	temp = ((अचिन्हित पूर्णांक)vp->apan<<24) | ((अचिन्हित पूर्णांक)vp->reg.loopstart - 1);
	EMU8000_PSST_WRITE(hw, vp->ch, temp);
पूर्ण

#घोषणा MOD_SENSE 18

अटल व्योम
set_fmmod(काष्ठा snd_emu8000 *hw, काष्ठा snd_emux_voice *vp)
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
	EMU8000_FMMOD_WRITE(hw, vp->ch, fmmod);
पूर्ण

/* set tremolo (lfo1) volume & frequency */
अटल व्योम
set_tremfreq(काष्ठा snd_emu8000 *hw, काष्ठा snd_emux_voice *vp)
अणु
	EMU8000_TREMFRQ_WRITE(hw, vp->ch, vp->reg.parm.tremfrq);
पूर्ण

/* set lfo2 pitch & frequency */
अटल व्योम
set_fm2frq2(काष्ठा snd_emu8000 *hw, काष्ठा snd_emux_voice *vp)
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
	EMU8000_FM2FRQ2_WRITE(hw, vp->ch, fm2frq2);
पूर्ण

/* set filterQ */
अटल व्योम
set_filterQ(काष्ठा snd_emu8000 *hw, काष्ठा snd_emux_voice *vp)
अणु
	अचिन्हित पूर्णांक addr;
	addr = EMU8000_CCCA_READ(hw, vp->ch) & 0xffffff;
	addr |= (vp->reg.parm.filterQ << 28);
	EMU8000_CCCA_WRITE(hw, vp->ch, addr);
पूर्ण

/*
 * set the envelope & LFO parameters to the शेष values
 */
अटल व्योम
snd_emu8000_tweak_voice(काष्ठा snd_emu8000 *emu, पूर्णांक i)
अणु
	/* set all mod/vol envelope shape to minimum */
	EMU8000_ENVVOL_WRITE(emu, i, 0x8000);
	EMU8000_ENVVAL_WRITE(emu, i, 0x8000);
	EMU8000_DCYSUS_WRITE(emu, i, 0x7F7F);
	EMU8000_ATKHLDV_WRITE(emu, i, 0x7F7F);
	EMU8000_ATKHLD_WRITE(emu, i, 0x7F7F);
	EMU8000_PEFE_WRITE(emu, i, 0);  /* mod envelope height to zero */
	EMU8000_LFO1VAL_WRITE(emu, i, 0x8000); /* no delay क्रम LFO1 */
	EMU8000_LFO2VAL_WRITE(emu, i, 0x8000);
	EMU8000_IP_WRITE(emu, i, 0xE000);	/* no pitch shअगरt */
	EMU8000_IFATN_WRITE(emu, i, 0xFF00);	/* volume to minimum */
	EMU8000_FMMOD_WRITE(emu, i, 0);
	EMU8000_TREMFRQ_WRITE(emu, i, 0);
	EMU8000_FM2FRQ2_WRITE(emu, i, 0);
पूर्ण

/*
 * sysex callback
 */
अटल व्योम
sysex(काष्ठा snd_emux *emu, अक्षर *buf, पूर्णांक len, पूर्णांक parsed, काष्ठा snd_midi_channel_set *chset)
अणु
	काष्ठा snd_emu8000 *hw;

	hw = emu->hw;

	चयन (parsed) अणु
	हाल SNDRV_MIDI_SYSEX_GS_CHORUS_MODE:
		hw->chorus_mode = chset->gs_chorus_mode;
		snd_emu8000_update_chorus_mode(hw);
		अवरोध;

	हाल SNDRV_MIDI_SYSEX_GS_REVERB_MODE:
		hw->reverb_mode = chset->gs_reverb_mode;
		snd_emu8000_update_reverb_mode(hw);
		अवरोध;
	पूर्ण
पूर्ण


#अगर IS_ENABLED(CONFIG_SND_SEQUENCER_OSS)
/*
 * OSS ioctl callback
 */
अटल पूर्णांक
oss_ioctl(काष्ठा snd_emux *emu, पूर्णांक cmd, पूर्णांक p1, पूर्णांक p2)
अणु
	काष्ठा snd_emu8000 *hw;

	hw = emu->hw;

	चयन (cmd) अणु
	हाल _EMUX_OSS_REVERB_MODE:
		hw->reverb_mode = p1;
		snd_emu8000_update_reverb_mode(hw);
		अवरोध;

	हाल _EMUX_OSS_CHORUS_MODE:
		hw->chorus_mode = p1;
		snd_emu8000_update_chorus_mode(hw);
		अवरोध;

	हाल _EMUX_OSS_INITIALIZE_CHIP:
		/* snd_emu8000_init(hw); */ /*ignored*/
		अवरोध;

	हाल _EMUX_OSS_EQUALIZER:
		hw->bass_level = p1;
		hw->treble_level = p2;
		snd_emu8000_update_equalizer(hw);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर


/*
 * additional patch keys
 */

#घोषणा SNDRV_EMU8000_LOAD_CHORUS_FX	0x10	/* optarg=mode */
#घोषणा SNDRV_EMU8000_LOAD_REVERB_FX	0x11	/* optarg=mode */


/*
 * callback routine
 */

अटल पूर्णांक
load_fx(काष्ठा snd_emux *emu, पूर्णांक type, पूर्णांक mode, स्थिर व्योम __user *buf, दीर्घ len)
अणु
	काष्ठा snd_emu8000 *hw;
	hw = emu->hw;

	/* skip header */
	buf += 16;
	len -= 16;

	चयन (type) अणु
	हाल SNDRV_EMU8000_LOAD_CHORUS_FX:
		वापस snd_emu8000_load_chorus_fx(hw, mode, buf, len);
	हाल SNDRV_EMU8000_LOAD_REVERB_FX:
		वापस snd_emu8000_load_reverb_fx(hw, mode, buf, len);
	पूर्ण
	वापस -EINVAL;
पूर्ण

