<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  NRPN / SYSEX callbacks क्रम Emu8k/Emu10k1
 *
 *  Copyright (c) 1999-2000 Takashi Iwai <tiwai@suse.de>
 */

#समावेश "emux_voice.h"
#समावेश <sound/asoundef.h>

/*
 * conversion from NRPN/control parameters to Emu8000 raw parameters
 */

/* NRPN / CC -> Emu8000 parameter converter */
काष्ठा nrpn_conv_table अणु
	पूर्णांक control;
	पूर्णांक effect;
	पूर्णांक (*convert)(पूर्णांक val);
पूर्ण;

/* effect sensitivity */

#घोषणा FX_CUTOFF	0
#घोषणा FX_RESOन_अंकCE	1
#घोषणा FX_ATTACK	2
#घोषणा FX_RELEASE	3
#घोषणा FX_VIBRATE	4
#घोषणा FX_VIBDEPTH	5
#घोषणा FX_VIBDELAY	6
#घोषणा FX_NUMS		7

/*
 * convert NRPN/control values
 */

अटल पूर्णांक send_converted_effect(स्थिर काष्ठा nrpn_conv_table *table,
				 पूर्णांक num_tables,
				 काष्ठा snd_emux_port *port,
				 काष्ठा snd_midi_channel *chan,
				 पूर्णांक type, पूर्णांक val, पूर्णांक mode)
अणु
	पूर्णांक i, cval;
	क्रम (i = 0; i < num_tables; i++) अणु
		अगर (table[i].control == type) अणु
			cval = table[i].convert(val);
			snd_emux_send_effect(port, chan, table[i].effect,
					     cval, mode);
			वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा DEF_FX_CUTOFF		170
#घोषणा DEF_FX_RESOन_अंकCE	6
#घोषणा DEF_FX_ATTACK		50
#घोषणा DEF_FX_RELEASE		50
#घोषणा DEF_FX_VIBRATE		30
#घोषणा DEF_FX_VIBDEPTH		4
#घोषणा DEF_FX_VIBDELAY		1500

/* effect sensitivities क्रम GS NRPN:
 *  adjusted क्रम chaos 8MB soundfonts
 */
अटल स्थिर पूर्णांक gs_sense[] =
अणु
	DEF_FX_CUTOFF, DEF_FX_RESOन_अंकCE, DEF_FX_ATTACK, DEF_FX_RELEASE,
	DEF_FX_VIBRATE, DEF_FX_VIBDEPTH, DEF_FX_VIBDELAY
पूर्ण;

/* effect sensitivies क्रम XG controls:
 * adjusted क्रम chaos 8MB soundfonts
 */
अटल स्थिर पूर्णांक xg_sense[] =
अणु
	DEF_FX_CUTOFF, DEF_FX_RESOन_अंकCE, DEF_FX_ATTACK, DEF_FX_RELEASE,
	DEF_FX_VIBRATE, DEF_FX_VIBDEPTH, DEF_FX_VIBDELAY
पूर्ण;


/*
 * AWE32 NRPN effects
 */

अटल पूर्णांक fx_delay(पूर्णांक val);
अटल पूर्णांक fx_attack(पूर्णांक val);
अटल पूर्णांक fx_hold(पूर्णांक val);
अटल पूर्णांक fx_decay(पूर्णांक val);
अटल पूर्णांक fx_the_value(पूर्णांक val);
अटल पूर्णांक fx_twice_value(पूर्णांक val);
अटल पूर्णांक fx_conv_pitch(पूर्णांक val);
अटल पूर्णांक fx_conv_Q(पूर्णांक val);

/* function क्रम each NRPN */		/* [range]  units */
#घोषणा fx_env1_delay	fx_delay	/* [0,5900] 4msec */
#घोषणा fx_env1_attack	fx_attack	/* [0,5940] 1msec */
#घोषणा fx_env1_hold	fx_hold		/* [0,8191] 1msec */
#घोषणा fx_env1_decay	fx_decay	/* [0,5940] 4msec */
#घोषणा fx_env1_release	fx_decay	/* [0,5940] 4msec */
#घोषणा fx_env1_sustain	fx_the_value	/* [0,127] 0.75dB */
#घोषणा fx_env1_pitch	fx_the_value	/* [-127,127] 9.375cents */
#घोषणा fx_env1_cutoff	fx_the_value	/* [-127,127] 56.25cents */

#घोषणा fx_env2_delay	fx_delay	/* [0,5900] 4msec */
#घोषणा fx_env2_attack	fx_attack	/* [0,5940] 1msec */
#घोषणा fx_env2_hold	fx_hold		/* [0,8191] 1msec */
#घोषणा fx_env2_decay	fx_decay	/* [0,5940] 4msec */
#घोषणा fx_env2_release	fx_decay	/* [0,5940] 4msec */
#घोषणा fx_env2_sustain	fx_the_value	/* [0,127] 0.75dB */

#घोषणा fx_lfo1_delay	fx_delay	/* [0,5900] 4msec */
#घोषणा fx_lfo1_freq	fx_twice_value	/* [0,127] 84mHz */
#घोषणा fx_lfo1_volume	fx_twice_value	/* [0,127] 0.1875dB */
#घोषणा fx_lfo1_pitch	fx_the_value	/* [-127,127] 9.375cents */
#घोषणा fx_lfo1_cutoff	fx_twice_value	/* [-64,63] 56.25cents */

#घोषणा fx_lfo2_delay	fx_delay	/* [0,5900] 4msec */
#घोषणा fx_lfo2_freq	fx_twice_value	/* [0,127] 84mHz */
#घोषणा fx_lfo2_pitch	fx_the_value	/* [-127,127] 9.375cents */

#घोषणा fx_init_pitch	fx_conv_pitch	/* [-8192,8192] cents */
#घोषणा fx_chorus	fx_the_value	/* [0,255] -- */
#घोषणा fx_reverb	fx_the_value	/* [0,255] -- */
#घोषणा fx_cutoff	fx_twice_value	/* [0,127] 62Hz */
#घोषणा fx_filterQ	fx_conv_Q	/* [0,127] -- */

अटल पूर्णांक fx_delay(पूर्णांक val)
अणु
	वापस (अचिन्हित लघु)snd_sf_calc_parm_delay(val);
पूर्ण

अटल पूर्णांक fx_attack(पूर्णांक val)
अणु
	वापस (अचिन्हित लघु)snd_sf_calc_parm_attack(val);
पूर्ण

अटल पूर्णांक fx_hold(पूर्णांक val)
अणु
	वापस (अचिन्हित लघु)snd_sf_calc_parm_hold(val);
पूर्ण

अटल पूर्णांक fx_decay(पूर्णांक val)
अणु
	वापस (अचिन्हित लघु)snd_sf_calc_parm_decay(val);
पूर्ण

अटल पूर्णांक fx_the_value(पूर्णांक val)
अणु
	वापस (अचिन्हित लघु)(val & 0xff);
पूर्ण

अटल पूर्णांक fx_twice_value(पूर्णांक val)
अणु
	वापस (अचिन्हित लघु)((val * 2) & 0xff);
पूर्ण

अटल पूर्णांक fx_conv_pitch(पूर्णांक val)
अणु
	वापस (लघु)(val * 4096 / 1200);
पूर्ण

अटल पूर्णांक fx_conv_Q(पूर्णांक val)
अणु
	वापस (अचिन्हित लघु)((val / 8) & 0xff);
पूर्ण


अटल स्थिर काष्ठा nrpn_conv_table awe_effects[] =
अणु
	अणु 0, EMUX_FX_LFO1_DELAY,	fx_lfo1_delayपूर्ण,
	अणु 1, EMUX_FX_LFO1_FREQ,	fx_lfo1_freqपूर्ण,
	अणु 2, EMUX_FX_LFO2_DELAY,	fx_lfo2_delayपूर्ण,
	अणु 3, EMUX_FX_LFO2_FREQ,	fx_lfo2_freqपूर्ण,

	अणु 4, EMUX_FX_ENV1_DELAY,	fx_env1_delayपूर्ण,
	अणु 5, EMUX_FX_ENV1_ATTACK,fx_env1_attackपूर्ण,
	अणु 6, EMUX_FX_ENV1_HOLD,	fx_env1_holdपूर्ण,
	अणु 7, EMUX_FX_ENV1_DECAY,	fx_env1_decayपूर्ण,
	अणु 8, EMUX_FX_ENV1_SUSTAIN,	fx_env1_sustainपूर्ण,
	अणु 9, EMUX_FX_ENV1_RELEASE,	fx_env1_releaseपूर्ण,

	अणु10, EMUX_FX_ENV2_DELAY,	fx_env2_delayपूर्ण,
	अणु11, EMUX_FX_ENV2_ATTACK,	fx_env2_attackपूर्ण,
	अणु12, EMUX_FX_ENV2_HOLD,	fx_env2_holdपूर्ण,
	अणु13, EMUX_FX_ENV2_DECAY,	fx_env2_decayपूर्ण,
	अणु14, EMUX_FX_ENV2_SUSTAIN,	fx_env2_sustainपूर्ण,
	अणु15, EMUX_FX_ENV2_RELEASE,	fx_env2_releaseपूर्ण,

	अणु16, EMUX_FX_INIT_PITCH,	fx_init_pitchपूर्ण,
	अणु17, EMUX_FX_LFO1_PITCH,	fx_lfo1_pitchपूर्ण,
	अणु18, EMUX_FX_LFO2_PITCH,	fx_lfo2_pitchपूर्ण,
	अणु19, EMUX_FX_ENV1_PITCH,	fx_env1_pitchपूर्ण,
	अणु20, EMUX_FX_LFO1_VOLUME,	fx_lfo1_volumeपूर्ण,
	अणु21, EMUX_FX_CUTOFF,		fx_cutoffपूर्ण,
	अणु22, EMUX_FX_FILTERQ,	fx_filterQपूर्ण,
	अणु23, EMUX_FX_LFO1_CUTOFF,	fx_lfo1_cutoffपूर्ण,
	अणु24, EMUX_FX_ENV1_CUTOFF,	fx_env1_cutoffपूर्ण,
	अणु25, EMUX_FX_CHORUS,		fx_chorusपूर्ण,
	अणु26, EMUX_FX_REVERB,		fx_reverbपूर्ण,
पूर्ण;


/*
 * GS(SC88) NRPN effects; still experimental
 */

/* cutoff: quarter semitone step, max=255 */
अटल पूर्णांक gs_cutoff(पूर्णांक val)
अणु
	वापस (val - 64) * gs_sense[FX_CUTOFF] / 50;
पूर्ण

/* resonance: 0 to 15(max) */
अटल पूर्णांक gs_filterQ(पूर्णांक val)
अणु
	वापस (val - 64) * gs_sense[FX_RESOन_अंकCE] / 50;
पूर्ण

/* attack: */
अटल पूर्णांक gs_attack(पूर्णांक val)
अणु
	वापस -(val - 64) * gs_sense[FX_ATTACK] / 50;
पूर्ण

/* decay: */
अटल पूर्णांक gs_decay(पूर्णांक val)
अणु
	वापस -(val - 64) * gs_sense[FX_RELEASE] / 50;
पूर्ण

/* release: */
अटल पूर्णांक gs_release(पूर्णांक val)
अणु
	वापस -(val - 64) * gs_sense[FX_RELEASE] / 50;
पूर्ण

/* vibrato freq: 0.042Hz step, max=255 */
अटल पूर्णांक gs_vib_rate(पूर्णांक val)
अणु
	वापस (val - 64) * gs_sense[FX_VIBRATE] / 50;
पूर्ण

/* vibrato depth: max=127, 1 octave */
अटल पूर्णांक gs_vib_depth(पूर्णांक val)
अणु
	वापस (val - 64) * gs_sense[FX_VIBDEPTH] / 50;
पूर्ण

/* vibrato delay: -0.725msec step */
अटल पूर्णांक gs_vib_delay(पूर्णांक val)
अणु
	वापस -(val - 64) * gs_sense[FX_VIBDELAY] / 50;
पूर्ण

अटल स्थिर काष्ठा nrpn_conv_table gs_effects[] =
अणु
	अणु32, EMUX_FX_CUTOFF,	gs_cutoffपूर्ण,
	अणु33, EMUX_FX_FILTERQ,	gs_filterQपूर्ण,
	अणु99, EMUX_FX_ENV2_ATTACK, gs_attackपूर्ण,
	अणु100, EMUX_FX_ENV2_DECAY, gs_decayपूर्ण,
	अणु102, EMUX_FX_ENV2_RELEASE, gs_releaseपूर्ण,
	अणु8, EMUX_FX_LFO1_FREQ, gs_vib_rateपूर्ण,
	अणु9, EMUX_FX_LFO1_VOLUME, gs_vib_depthपूर्ण,
	अणु10, EMUX_FX_LFO1_DELAY, gs_vib_delayपूर्ण,
पूर्ण;


/*
 * NRPN events
 */
व्योम
snd_emux_nrpn(व्योम *p, काष्ठा snd_midi_channel *chan,
	      काष्ठा snd_midi_channel_set *chset)
अणु
	काष्ठा snd_emux_port *port;

	port = p;
	अगर (snd_BUG_ON(!port || !chan))
		वापस;

	अगर (chan->control[MIDI_CTL_NONREG_PARM_NUM_MSB] == 127 &&
	    chan->control[MIDI_CTL_NONREG_PARM_NUM_LSB] <= 26) अणु
		पूर्णांक val;
		/* Win/DOS AWE32 specअगरic NRPNs */
		/* both MSB/LSB necessary */
		val = (chan->control[MIDI_CTL_MSB_DATA_ENTRY] << 7) |
			chan->control[MIDI_CTL_LSB_DATA_ENTRY]; 
		val -= 8192;
		send_converted_effect
			(awe_effects, ARRAY_SIZE(awe_effects),
			 port, chan, chan->control[MIDI_CTL_NONREG_PARM_NUM_LSB],
			 val, EMUX_FX_FLAG_SET);
		वापस;
	पूर्ण

	अगर (port->chset.midi_mode == SNDRV_MIDI_MODE_GS &&
	    chan->control[MIDI_CTL_NONREG_PARM_NUM_MSB] == 1) अणु
		पूर्णांक val;
		/* GS specअगरic NRPNs */
		/* only MSB is valid */
		val = chan->control[MIDI_CTL_MSB_DATA_ENTRY];
		send_converted_effect
			(gs_effects, ARRAY_SIZE(gs_effects),
			 port, chan, chan->control[MIDI_CTL_NONREG_PARM_NUM_LSB],
			 val, EMUX_FX_FLAG_ADD);
		वापस;
	पूर्ण
पूर्ण


/*
 * XG control effects; still experimental
 */

/* cutoff: quarter semitone step, max=255 */
अटल पूर्णांक xg_cutoff(पूर्णांक val)
अणु
	वापस (val - 64) * xg_sense[FX_CUTOFF] / 64;
पूर्ण

/* resonance: 0(खोलो) to 15(most nasal) */
अटल पूर्णांक xg_filterQ(पूर्णांक val)
अणु
	वापस (val - 64) * xg_sense[FX_RESOन_अंकCE] / 64;
पूर्ण

/* attack: */
अटल पूर्णांक xg_attack(पूर्णांक val)
अणु
	वापस -(val - 64) * xg_sense[FX_ATTACK] / 64;
पूर्ण

/* release: */
अटल पूर्णांक xg_release(पूर्णांक val)
अणु
	वापस -(val - 64) * xg_sense[FX_RELEASE] / 64;
पूर्ण

अटल स्थिर काष्ठा nrpn_conv_table xg_effects[] =
अणु
	अणु71, EMUX_FX_CUTOFF,	xg_cutoffपूर्ण,
	अणु74, EMUX_FX_FILTERQ,	xg_filterQपूर्ण,
	अणु72, EMUX_FX_ENV2_RELEASE, xg_releaseपूर्ण,
	अणु73, EMUX_FX_ENV2_ATTACK, xg_attackपूर्ण,
पूर्ण;

पूर्णांक
snd_emux_xg_control(काष्ठा snd_emux_port *port, काष्ठा snd_midi_channel *chan,
		    पूर्णांक param)
अणु
	वापस send_converted_effect(xg_effects, ARRAY_SIZE(xg_effects),
				     port, chan, param,
				     chan->control[param],
				     EMUX_FX_FLAG_ADD);
पूर्ण

/*
 * receive sysex
 */
व्योम
snd_emux_sysex(व्योम *p, अचिन्हित अक्षर *buf, पूर्णांक len, पूर्णांक parsed,
	       काष्ठा snd_midi_channel_set *chset)
अणु
	काष्ठा snd_emux_port *port;
	काष्ठा snd_emux *emu;

	port = p;
	अगर (snd_BUG_ON(!port || !chset))
		वापस;
	emu = port->emu;

	चयन (parsed) अणु
	हाल SNDRV_MIDI_SYSEX_GS_MASTER_VOLUME:
		snd_emux_update_port(port, SNDRV_EMUX_UPDATE_VOLUME);
		अवरोध;
	शेष:
		अगर (emu->ops.sysex)
			emu->ops.sysex(emu, buf, len, parsed, chset);
		अवरोध;
	पूर्ण
पूर्ण

