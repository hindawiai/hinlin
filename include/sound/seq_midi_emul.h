<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_SEQ_MIDI_EMUL_H
#घोषणा __SOUND_SEQ_MIDI_EMUL_H

/*
 *  Midi channel definition क्रम optional channel management.
 *
 *  Copyright (C) 1999 Steve Ratclअगरfe
 */

#समावेश <sound/seq_kernel.h>

/*
 * This काष्ठाure is used to keep track of the current state on each
 * channel.  All drivers क्रम hardware that करोes not understand midi
 * directly will probably need to use this काष्ठाure.
 */
काष्ठा snd_midi_channel अणु
	व्योम *निजी;		/* A back poपूर्णांकer to driver data */
	पूर्णांक  number;		/* The channel number */
	पूर्णांक  client;		/* The client associated with this channel */
	पूर्णांक  port;		/* The port associated with this channel */

	अचिन्हित अक्षर midi_mode;	/* GM, GS, XG etc */
	अचिन्हित पूर्णांक 
		drum_channel:1,		/* Drum channel */
		param_type:1		/* RPN/NRPN */
		;

	अचिन्हित अक्षर midi_aftertouch;	/* Aftertouch (key pressure) */
	अचिन्हित अक्षर midi_pressure;	/* Channel pressure */
	अचिन्हित अक्षर midi_program;	/* Instrument number */
	लघु midi_pitchbend;		/* Pitch bend amount */

	अचिन्हित अक्षर control[128];	/* Current value of all controls */
	अचिन्हित अक्षर note[128];	/* Current status क्रम all notes */

	लघु gm_rpn_pitch_bend_range;	/* Pitch bend range */
	लघु gm_rpn_fine_tuning; 	/* Master fine tuning */
	लघु gm_rpn_coarse_tuning;	/* Master coarse tuning */

पूर्ण;

/*
 * A काष्ठाure that represets a set of channels bound to a port.  There
 * would usually be 16 channels per port.  But fewer could be used क्रम
 * particular हालs.
 * The channel set consists of inक्रमmation describing the client and
 * port क्रम this midi synth and an array of snd_midi_channel काष्ठाures.
 * A driver that had no need क्रम snd_midi_channel could still use the
 * channel set type अगर it wished with the channel array null.
 */
काष्ठा snd_midi_channel_set अणु
	व्योम *निजी_data;		/* Driver data */
	पूर्णांक  client;			/* Client क्रम this port */
	पूर्णांक  port;			/* The port number */

	पूर्णांक  max_channels;		/* Size of the channels array */
	काष्ठा snd_midi_channel *channels;

	अचिन्हित अक्षर midi_mode;	/* MIDI operating mode */
	अचिन्हित अक्षर gs_master_volume;	/* SYSEX master volume: 0-127 */
	अचिन्हित अक्षर gs_chorus_mode;
	अचिन्हित अक्षर gs_reverb_mode;

पूर्ण;

काष्ठा snd_midi_op अणु
	व्योम (*note_on)(व्योम *निजी_data, पूर्णांक note, पूर्णांक vel, काष्ठा snd_midi_channel *chan);
	व्योम (*note_off)(व्योम *निजी_data,पूर्णांक note, पूर्णांक vel, काष्ठा snd_midi_channel *chan); /* release note */
	व्योम (*key_press)(व्योम *निजी_data, पूर्णांक note, पूर्णांक vel, काष्ठा snd_midi_channel *chan);
	व्योम (*note_terminate)(व्योम *निजी_data, पूर्णांक note, काष्ठा snd_midi_channel *chan); /* terminate note immediately */
	व्योम (*control)(व्योम *निजी_data, पूर्णांक type, काष्ठा snd_midi_channel *chan);
	व्योम (*nrpn)(व्योम *निजी_data, काष्ठा snd_midi_channel *chan,
		     काष्ठा snd_midi_channel_set *chset);
	व्योम (*sysex)(व्योम *निजी_data, अचिन्हित अक्षर *buf, पूर्णांक len, पूर्णांक parsed,
		      काष्ठा snd_midi_channel_set *chset);
पूर्ण;

/*
 * These defines are used so that pitchbend, aftertouch etc, can be
 * distinguished from controller values.
 */
/* 0-127 controller values */
#घोषणा MIDI_CTL_PITCHBEND	0x80
#घोषणा MIDI_CTL_AFTERTOUCH	0x81
#घोषणा MIDI_CTL_CHAN_PRESSURE	0x82

/*
 * These names exist to allow symbolic access to the controls array.
 * The usage is eg: chan->gm_bank_select.  Another implementation would
 * be really have these members in the काष्ठा, and not the array.
 */
#घोषणा gm_bank_select		control[0]
#घोषणा gm_modulation		control[1]
#घोषणा gm_breath		control[2]
#घोषणा gm_foot_pedal		control[4]
#घोषणा gm_portamento_समय	control[5]
#घोषणा gm_data_entry		control[6]
#घोषणा gm_volume		control[7]
#घोषणा gm_balance		control[8]
#घोषणा gm_pan			control[10]
#घोषणा gm_expression		control[11]
#घोषणा gm_effect_control1	control[12]
#घोषणा gm_effect_control2	control[13]
#घोषणा gm_slider1		control[16]
#घोषणा gm_slider2		control[17]
#घोषणा gm_slider3		control[18]
#घोषणा gm_slider4		control[19]

#घोषणा gm_bank_select_lsb	control[32]
#घोषणा gm_modulation_wheel_lsb	control[33]
#घोषणा gm_breath_lsb		control[34]
#घोषणा gm_foot_pedal_lsb	control[36]
#घोषणा gm_portamento_समय_lsb	control[37]
#घोषणा gm_data_entry_lsb	control[38]
#घोषणा gm_volume_lsb		control[39]
#घोषणा gm_balance_lsb		control[40]
#घोषणा gm_pan_lsb		control[42]
#घोषणा gm_expression_lsb	control[43]
#घोषणा gm_effect_control1_lsb	control[44]
#घोषणा gm_effect_control2_lsb	control[45]

#घोषणा gm_sustain	 	control[MIDI_CTL_SUSTAIN]
#घोषणा gm_hold			gm_sustain
#घोषणा gm_portamento		control[MIDI_CTL_PORTAMENTO]
#घोषणा gm_sostenuto		control[MIDI_CTL_SOSTENUTO]

/*
 * These macros give the complete value of the controls that consist
 * of coarse and fine pairs.  Of course the fine controls are selकरोm used
 * but there is no harm in being complete.
 */
#घोषणा SNDRV_GM_BANK_SELECT(cp)		(((cp)->control[0]<<7)|((cp)->control[32]))
#घोषणा SNDRV_GM_MODULATION_WHEEL(cp)	(((cp)->control[1]<<7)|((cp)->control[33]))
#घोषणा SNDRV_GM_BREATH(cp)		(((cp)->control[2]<<7)|((cp)->control[34]))
#घोषणा SNDRV_GM_FOOT_PEDAL(cp)		(((cp)->control[4]<<7)|((cp)->control[36]))
#घोषणा SNDRV_GM_PORTAMENTO_TIME(cp)	(((cp)->control[5]<<7)|((cp)->control[37]))
#घोषणा SNDRV_GM_DATA_ENTRY(cp)		(((cp)->control[6]<<7)|((cp)->control[38]))
#घोषणा SNDRV_GM_VOLUME(cp)		(((cp)->control[7]<<7)|((cp)->control[39]))
#घोषणा SNDRV_GM_BALANCE(cp)		(((cp)->control[8]<<7)|((cp)->control[40]))
#घोषणा SNDRV_GM_PAN(cp)			(((cp)->control[10]<<7)|((cp)->control[42]))
#घोषणा SNDRV_GM_EXPRESSION(cp)		(((cp)->control[11]<<7)|((cp)->control[43]))


/* MIDI mode */
#घोषणा SNDRV_MIDI_MODE_NONE	0	/* Generic midi */
#घोषणा SNDRV_MIDI_MODE_GM	1
#घोषणा SNDRV_MIDI_MODE_GS	2
#घोषणा SNDRV_MIDI_MODE_XG	3
#घोषणा SNDRV_MIDI_MODE_MT32	4

/* MIDI note state */
#घोषणा SNDRV_MIDI_NOTE_OFF		0x00
#घोषणा SNDRV_MIDI_NOTE_ON		0x01
#घोषणा SNDRV_MIDI_NOTE_RELEASED		0x02
#घोषणा SNDRV_MIDI_NOTE_SOSTENUTO		0x04
 
#घोषणा SNDRV_MIDI_PARAM_TYPE_REGISTERED		0
#घोषणा SNDRV_MIDI_PARAM_TYPE_NONREGISTERED	1

/* SYSEX parse flag */
क्रमागत अणु
	SNDRV_MIDI_SYSEX_NOT_PARSED = 0,
	SNDRV_MIDI_SYSEX_GM_ON,	
	SNDRV_MIDI_SYSEX_GS_ON,	
	SNDRV_MIDI_SYSEX_GS_RESET,	
	SNDRV_MIDI_SYSEX_GS_CHORUS_MODE,
	SNDRV_MIDI_SYSEX_GS_REVERB_MODE,
	SNDRV_MIDI_SYSEX_GS_MASTER_VOLUME,
	SNDRV_MIDI_SYSEX_GS_PROGRAM,
	SNDRV_MIDI_SYSEX_GS_DRUM_CHANNEL,
	SNDRV_MIDI_SYSEX_XG_ON,	
पूर्ण;

/* Prototypes क्रम midi_process.c */
व्योम snd_midi_process_event(स्थिर काष्ठा snd_midi_op *ops,
			    काष्ठा snd_seq_event *ev,
			    काष्ठा snd_midi_channel_set *chanset);
व्योम snd_midi_channel_set_clear(काष्ठा snd_midi_channel_set *chset);
काष्ठा snd_midi_channel_set *snd_midi_channel_alloc_set(पूर्णांक n);
व्योम snd_midi_channel_मुक्त_set(काष्ठा snd_midi_channel_set *chset);

#पूर्ण_अगर /* __SOUND_SEQ_MIDI_EMUL_H */
