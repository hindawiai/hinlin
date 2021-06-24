<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_EMUX_SYNTH_H
#घोषणा __SOUND_EMUX_SYNTH_H

/*
 *  Defines क्रम the Emu-series WaveTable chip
 *
 *  Copyright (C) 2000 Takashi Iwai <tiwai@suse.de>
 */

#समावेश <sound/seq_kernel.h>
#समावेश <sound/seq_device.h>
#समावेश <sound/soundfont.h>
#समावेश <sound/seq_midi_emul.h>
#समावेश <sound/seq_oss.h>
#समावेश <sound/emux_legacy.h>
#समावेश <sound/seq_virmidi.h>

/*
 * compile flags
 */
#घोषणा SNDRV_EMUX_USE_RAW_EFFECT

काष्ठा snd_emux;
काष्ठा snd_emux_port;
काष्ठा snd_emux_voice;
काष्ठा snd_emux_effect_table;

/*
 * चालकs
 */
काष्ठा snd_emux_चालकs अणु
	काष्ठा module *owner;
	काष्ठा snd_emux_voice *(*get_voice)(काष्ठा snd_emux *emu,
					    काष्ठा snd_emux_port *port);
	पूर्णांक (*prepare)(काष्ठा snd_emux_voice *vp);
	व्योम (*trigger)(काष्ठा snd_emux_voice *vp);
	व्योम (*release)(काष्ठा snd_emux_voice *vp);
	व्योम (*update)(काष्ठा snd_emux_voice *vp, पूर्णांक update);
	व्योम (*terminate)(काष्ठा snd_emux_voice *vp);
	व्योम (*मुक्त_voice)(काष्ठा snd_emux_voice *vp);
	व्योम (*reset)(काष्ठा snd_emux *emu, पूर्णांक ch);
	/* the first parameters are काष्ठा snd_emux */
	पूर्णांक (*sample_new)(काष्ठा snd_emux *emu, काष्ठा snd_sf_sample *sp,
			  काष्ठा snd_util_memhdr *hdr,
			  स्थिर व्योम __user *data, दीर्घ count);
	पूर्णांक (*sample_मुक्त)(काष्ठा snd_emux *emu, काष्ठा snd_sf_sample *sp,
			   काष्ठा snd_util_memhdr *hdr);
	व्योम (*sample_reset)(काष्ठा snd_emux *emu);
	पूर्णांक (*load_fx)(काष्ठा snd_emux *emu, पूर्णांक type, पूर्णांक arg,
		       स्थिर व्योम __user *data, दीर्घ count);
	व्योम (*sysex)(काष्ठा snd_emux *emu, अक्षर *buf, पूर्णांक len, पूर्णांक parsed,
		      काष्ठा snd_midi_channel_set *chset);
#अगर IS_ENABLED(CONFIG_SND_SEQUENCER_OSS)
	पूर्णांक (*oss_ioctl)(काष्ठा snd_emux *emu, पूर्णांक cmd, पूर्णांक p1, पूर्णांक p2);
#पूर्ण_अगर
पूर्ण;


/*
 * स्थिरant values
 */
#घोषणा SNDRV_EMUX_MAX_PORTS		32	/* max # of sequencer ports */
#घोषणा SNDRV_EMUX_MAX_VOICES		64	/* max # of voices */
#घोषणा SNDRV_EMUX_MAX_MULTI_VOICES	16	/* max # of playable voices
						 * simultineously
						 */

/*
 * flags
 */
#घोषणा SNDRV_EMUX_ACCEPT_ROM		(1<<0)

/*
 * emuX wavetable
 */
काष्ठा snd_emux अणु

	काष्ठा snd_card *card;	/* asचिन्हित card */

	/* following should be initialized beक्रमe registration */
	पूर्णांक max_voices;		/* Number of voices */
	पूर्णांक mem_size;		/* memory size (in byte) */
	पूर्णांक num_ports;		/* number of ports to be created */
	पूर्णांक pitch_shअगरt;	/* pitch shअगरt value (क्रम Emu10k1) */
	काष्ठा snd_emux_चालकs ops;	/* चालकs */
	व्योम *hw;		/* hardware */
	अचिन्हित दीर्घ flags;	/* other conditions */
	पूर्णांक midi_ports;		/* number of भव midi devices */
	पूर्णांक midi_devidx;	/* device offset of भव midi */
	अचिन्हित पूर्णांक linear_panning: 1; /* panning is linear (sbawe = 1, emu10k1 = 0) */
	पूर्णांक hwdep_idx;		/* hwdep device index */
	काष्ठा snd_hwdep *hwdep;	/* hwdep device */

	/* निजी */
	पूर्णांक num_voices;		/* current number of voices */
	काष्ठा snd_sf_list *sflist;	/* root of SoundFont list */
	काष्ठा snd_emux_voice *voices;	/* Voices (EMU 'channel') */
	पूर्णांक use_समय;	/* allocation counter */
	spinlock_t voice_lock;	/* Lock क्रम voice access */
	काष्ठा mutex रेजिस्टर_mutex;
	पूर्णांक client;		/* For the sequencer client */
	पूर्णांक ports[SNDRV_EMUX_MAX_PORTS];	/* The ports क्रम this device */
	काष्ठा snd_emux_port *portptrs[SNDRV_EMUX_MAX_PORTS];
	पूर्णांक used;	/* use counter */
	अक्षर *name;	/* name of the device (पूर्णांकernal) */
	काष्ठा snd_rawmidi **vmidi;
	काष्ठा समयr_list tlist;	/* क्रम pending note-offs */
	पूर्णांक समयr_active;

	काष्ठा snd_util_memhdr *memhdr;	/* memory chunk inक्रमmation */

#अगर_घोषित CONFIG_SND_PROC_FS
	काष्ठा snd_info_entry *proc;
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_SND_SEQUENCER_OSS)
	काष्ठा snd_seq_device *oss_synth;
#पूर्ण_अगर
पूर्ण;


/*
 * sequencer port inक्रमmation
 */
काष्ठा snd_emux_port अणु

	काष्ठा snd_midi_channel_set chset;
	काष्ठा snd_emux *emu;

	अक्षर port_mode;			/* operation mode */
	पूर्णांक volume_atten;		/* emuX raw attenuation */
	अचिन्हित दीर्घ drum_flags;	/* drum biपंचांगaps */
	पूर्णांक ctrls[EMUX_MD_END];		/* control parameters */
#अगर_घोषित SNDRV_EMUX_USE_RAW_EFFECT
	काष्ठा snd_emux_effect_table *effect;
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_SND_SEQUENCER_OSS)
	काष्ठा snd_seq_oss_arg *oss_arg;
#पूर्ण_अगर
पूर्ण;

/* port_mode */
#घोषणा SNDRV_EMUX_PORT_MODE_MIDI		0	/* normal MIDI port */
#घोषणा SNDRV_EMUX_PORT_MODE_OSS_SYNTH	1	/* OSS synth port */
#घोषणा SNDRV_EMUX_PORT_MODE_OSS_MIDI	2	/* OSS multi channel synth port */

/*
 * A काष्ठाure to keep track of each hardware voice
 */
काष्ठा snd_emux_voice अणु
	पूर्णांक  ch;		/* Hardware channel number */

	पूर्णांक  state;		/* status */
#घोषणा SNDRV_EMUX_ST_OFF		0x00	/* Not playing, and inactive */
#घोषणा SNDRV_EMUX_ST_ON		0x01	/* Note on */
#घोषणा SNDRV_EMUX_ST_RELEASED 	(0x02|SNDRV_EMUX_ST_ON)	/* Note released */
#घोषणा SNDRV_EMUX_ST_SUSTAINED	(0x04|SNDRV_EMUX_ST_ON)	/* Note sustained */
#घोषणा SNDRV_EMUX_ST_STANDBY	(0x08|SNDRV_EMUX_ST_ON)	/* Waiting to be triggered */
#घोषणा SNDRV_EMUX_ST_PENDING 	(0x10|SNDRV_EMUX_ST_ON)	/* Note will be released */
#घोषणा SNDRV_EMUX_ST_LOCKED		0x100	/* Not accessible */

	अचिन्हित पूर्णांक  समय;	/* An allocation समय */
	अचिन्हित अक्षर note;	/* Note currently asचिन्हित to this voice */
	अचिन्हित अक्षर key;
	अचिन्हित अक्षर velocity;	/* Velocity of current note */

	काष्ठा snd_sf_zone *zone;	/* Zone asचिन्हित to this note */
	व्योम *block;		/* sample block poपूर्णांकer (optional) */
	काष्ठा snd_midi_channel *chan;	/* Midi channel क्रम this note */
	काष्ठा snd_emux_port *port;	/* associated port */
	काष्ठा snd_emux *emu;	/* asचिन्हित root info */
	व्योम *hw;		/* hardware poपूर्णांकer (emu8000 or emu10k1) */
	अचिन्हित दीर्घ onसमय;	/* jअगरfies at note triggered */
	
	/* Emu8k/Emu10k1 रेजिस्टरs */
	काष्ठा soundfont_voice_info reg;

	/* additional रेजिस्टरs */
	पूर्णांक avol;		/* volume attenuation */
	पूर्णांक acutoff;		/* cutoff target */
	पूर्णांक apitch;		/* pitch offset */
	पूर्णांक apan;		/* pan/aux pair */
	पूर्णांक aaux;
	पूर्णांक ptarget;		/* pitch target */
	पूर्णांक vtarget;		/* volume target */
	पूर्णांक ftarget;		/* filter target */

पूर्ण;

/*
 * update flags (can be combined)
 */
#घोषणा SNDRV_EMUX_UPDATE_VOLUME		(1<<0)
#घोषणा SNDRV_EMUX_UPDATE_PITCH		(1<<1)
#घोषणा SNDRV_EMUX_UPDATE_PAN		(1<<2)
#घोषणा SNDRV_EMUX_UPDATE_FMMOD		(1<<3)
#घोषणा SNDRV_EMUX_UPDATE_TREMFREQ	(1<<4)
#घोषणा SNDRV_EMUX_UPDATE_FM2FRQ2		(1<<5)
#घोषणा SNDRV_EMUX_UPDATE_Q		(1<<6)


#अगर_घोषित SNDRV_EMUX_USE_RAW_EFFECT
/*
 * effect table
 */
काष्ठा snd_emux_effect_table अणु
	/* Emu8000 specअगरic effects */
	लघु val[EMUX_NUM_EFFECTS];
	अचिन्हित अक्षर flag[EMUX_NUM_EFFECTS];
पूर्ण;
#पूर्ण_अगर /* SNDRV_EMUX_USE_RAW_EFFECT */


/*
 * prototypes - पूर्णांकerface to Emu10k1 and Emu8k routines
 */
पूर्णांक snd_emux_new(काष्ठा snd_emux **remu);
पूर्णांक snd_emux_रेजिस्टर(काष्ठा snd_emux *emu, काष्ठा snd_card *card, पूर्णांक index, अक्षर *name);
पूर्णांक snd_emux_मुक्त(काष्ठा snd_emux *emu);

/*
 * exported functions
 */
व्योम snd_emux_terminate_all(काष्ठा snd_emux *emu);
व्योम snd_emux_lock_voice(काष्ठा snd_emux *emu, पूर्णांक voice);
व्योम snd_emux_unlock_voice(काष्ठा snd_emux *emu, पूर्णांक voice);

#पूर्ण_अगर /* __SOUND_EMUX_SYNTH_H */
