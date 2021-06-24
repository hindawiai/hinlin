<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_OPL3_H
#घोषणा __SOUND_OPL3_H

/*
 * Definitions of the OPL-3 रेजिस्टरs.
 *
 * Copyright (c) by Jaroslav Kysela <perex@perex.cz>,
 *                  Hannu Savolainen 1993-1996
 *
 *      The OPL-3 mode is चयनed on by writing 0x01, to the offset 5
 *      of the right side.
 *
 *      Another special रेजिस्टर at the right side is at offset 4. It contains
 *      a bit mask defining which voices are used as 4 OP voices.
 *
 *      The percussive mode is implemented in the left side only.
 *
 *      With the above exceptions the both sides can be operated independently.
 *      
 *      A 4 OP voice can be created by setting the corresponding
 *      bit at offset 4 of the right side.
 *
 *      For example setting the righपंचांगost bit (0x01) changes the
 *      first voice on the right side to the 4 OP mode. The fourth
 *      voice is made inaccessible.
 *
 *      If a voice is set to the 2 OP mode, it works like 2 OP modes
 *      of the original YM3812 (AdLib). In addition the voice can 
 *      be connected the left, right or both stereo channels. It can
 *      even be left unconnected. This works with 4 OP voices also.
 *
 *      The stereo connection bits are located in the FEEDBACK_CONNECTION
 *      रेजिस्टर of the voice (0xC0-0xC8). In 4 OP voices these bits are
 *      in the second half of the voice.
 */

#समावेश <sound/core.h>
#समावेश <sound/hwdep.h>
#समावेश <sound/समयr.h>
#समावेश <sound/seq_midi_emul.h>
#समावेश <sound/seq_oss.h>
#समावेश <sound/seq_oss_legacy.h>
#समावेश <sound/seq_device.h>
#समावेश <sound/asound_fm.h>

/*
 *    Register numbers क्रम the global रेजिस्टरs
 */

#घोषणा OPL3_REG_TEST			0x01
#घोषणा   OPL3_ENABLE_WAVE_SELECT	0x20

#घोषणा OPL3_REG_TIMER1			0x02
#घोषणा OPL3_REG_TIMER2			0x03
#घोषणा OPL3_REG_TIMER_CONTROL		0x04	/* Left side */
#घोषणा   OPL3_IRQ_RESET		0x80
#घोषणा   OPL3_TIMER1_MASK		0x40
#घोषणा   OPL3_TIMER2_MASK		0x20
#घोषणा   OPL3_TIMER1_START		0x01
#घोषणा   OPL3_TIMER2_START		0x02

#घोषणा OPL3_REG_CONNECTION_SELECT	0x04	/* Right side */
#घोषणा   OPL3_LEFT_4OP_0		0x01
#घोषणा   OPL3_LEFT_4OP_1		0x02
#घोषणा   OPL3_LEFT_4OP_2		0x04
#घोषणा   OPL3_RIGHT_4OP_0		0x08
#घोषणा   OPL3_RIGHT_4OP_1		0x10
#घोषणा   OPL3_RIGHT_4OP_2		0x20

#घोषणा OPL3_REG_MODE			0x05	/* Right side */
#घोषणा   OPL3_OPL3_ENABLE		0x01	/* OPL3 mode */
#घोषणा   OPL3_OPL4_ENABLE		0x02	/* OPL4 mode */

#घोषणा OPL3_REG_KBD_SPLIT		0x08	/* Left side */
#घोषणा   OPL3_COMPOSITE_SINE_WAVE_MODE	0x80	/* Don't use with OPL-3? */
#घोषणा   OPL3_KEYBOARD_SPLIT		0x40

#घोषणा OPL3_REG_PERCUSSION		0xbd	/* Left side only */
#घोषणा   OPL3_TREMOLO_DEPTH		0x80
#घोषणा   OPL3_VIBRATO_DEPTH		0x40
#घोषणा	  OPL3_PERCUSSION_ENABLE	0x20
#घोषणा   OPL3_BASSDRUM_ON		0x10
#घोषणा   OPL3_SNAREDRUM_ON		0x08
#घोषणा   OPL3_TOMTOM_ON		0x04
#घोषणा   OPL3_CYMBAL_ON		0x02
#घोषणा   OPL3_HIHAT_ON			0x01

/*
 *    Offsets to the रेजिस्टर banks क्रम चालकs. To get the
 *      रेजिस्टर number just add the चालक offset to the bank offset
 *
 *      AM/VIB/EG/KSR/Multiple (0x20 to 0x35)
 */
#घोषणा OPL3_REG_AM_VIB			0x20
#घोषणा   OPL3_TREMOLO_ON		0x80
#घोषणा   OPL3_VIBRATO_ON		0x40
#घोषणा   OPL3_SUSTAIN_ON		0x20
#घोषणा   OPL3_KSR			0x10	/* Key scaling rate */
#घोषणा   OPL3_MULTIPLE_MASK		0x0f	/* Frequency multiplier */

 /*
  *   KSL/Total level (0x40 to 0x55)
  */
#घोषणा OPL3_REG_KSL_LEVEL		0x40
#घोषणा   OPL3_KSL_MASK			0xc0	/* Envelope scaling bits */
#घोषणा   OPL3_TOTAL_LEVEL_MASK		0x3f	/* Strength (volume) of OP */

/*
 *    Attack / Decay rate (0x60 to 0x75)
 */
#घोषणा OPL3_REG_ATTACK_DECAY		0x60
#घोषणा   OPL3_ATTACK_MASK		0xf0
#घोषणा   OPL3_DECAY_MASK		0x0f

/*
 * Sustain level / Release rate (0x80 to 0x95)
 */
#घोषणा OPL3_REG_SUSTAIN_RELEASE	0x80
#घोषणा   OPL3_SUSTAIN_MASK		0xf0
#घोषणा   OPL3_RELEASE_MASK		0x0f

/*
 * Wave select (0xE0 to 0xF5)
 */
#घोषणा OPL3_REG_WAVE_SELECT		0xe0
#घोषणा   OPL3_WAVE_SELECT_MASK		0x07

/*
 *    Offsets to the रेजिस्टर banks क्रम voices. Just add to the
 *      voice number to get the रेजिस्टर number.
 *
 *      F-Number low bits (0xA0 to 0xA8).
 */
#घोषणा OPL3_REG_FNUM_LOW		0xa0

/*
 *    F-number high bits / Key on / Block (octave) (0xB0 to 0xB8)
 */
#घोषणा OPL3_REG_KEYON_BLOCK		0xb0
#घोषणा	  OPL3_KEYON_BIT		0x20
#घोषणा	  OPL3_BLOCKNUM_MASK		0x1c
#घोषणा   OPL3_FNUM_HIGH_MASK		0x03

/*
 *    Feedback / Connection (0xc0 to 0xc8)
 *
 *      These रेजिस्टरs have two new bits when the OPL-3 mode
 *      is selected. These bits controls connecting the voice
 *      to the stereo channels. For 4 OP voices this bit is
 *      defined in the second half of the voice (add 3 to the
 *      रेजिस्टर offset).
 *
 *      For 4 OP voices the connection bit is used in the
 *      both halves (gives 4 ways to connect the चालकs).
 */
#घोषणा OPL3_REG_FEEDBACK_CONNECTION	0xc0
#घोषणा   OPL3_FEEDBACK_MASK		0x0e	/* Valid just क्रम 1st OP of a voice */
#घोषणा   OPL3_CONNECTION_BIT		0x01
/*
 *    In the 4 OP mode there is four possible configurations how the
 *      चालकs can be connected together (in 2 OP modes there is just
 *      AM or FM). The 4 OP connection mode is defined by the righपंचांगost
 *      bit of the FEEDBACK_CONNECTION (0xC0-0xC8) on the both halves.
 *
 *      First half      Second half     Mode
 *
 *                                       +---+
 *                                       v   |
 *      0               0               >+-1-+--2--3--4-->
 *
 *
 *                                      
 *                                       +---+
 *                                       |   |
 *      0               1               >+-1-+--2-+
 *                                                |->
 *                                      >--3----4-+
 *                                      
 *                                       +---+
 *                                       |   |
 *      1               0               >+-1-+-----+
 *                                                 |->
 *                                      >--2--3--4-+
 *
 *                                       +---+
 *                                       |   |
 *      1               1               >+-1-+--+
 *                                              |
 *                                      >--2--3-+->
 *                                              |
 *                                      >--4----+
 */
#घोषणा   OPL3_STEREO_BITS		0x30	/* OPL-3 only */
#घोषणा     OPL3_VOICE_TO_LEFT		0x10
#घोषणा     OPL3_VOICE_TO_RIGHT		0x20

/*

 */

#घोषणा OPL3_LEFT		0x0000
#घोषणा OPL3_RIGHT		0x0100

#घोषणा OPL3_HW_AUTO		0x0000
#घोषणा OPL3_HW_OPL2		0x0200
#घोषणा OPL3_HW_OPL3		0x0300
#घोषणा OPL3_HW_OPL3_SV		0x0301	/* S3 SonicVibes */
#घोषणा OPL3_HW_OPL3_CS		0x0302	/* CS4232/CS4236+ */
#घोषणा OPL3_HW_OPL3_FM801	0x0303	/* FM801 */
#घोषणा OPL3_HW_OPL3_CS4281	0x0304	/* CS4281 */
#घोषणा OPL3_HW_OPL4		0x0400	/* YMF278B/YMF295 */
#घोषणा OPL3_HW_OPL4_ML		0x0401	/* YMF704/YMF721 */
#घोषणा OPL3_HW_MASK		0xff00

#घोषणा MAX_OPL2_VOICES		9
#घोषणा MAX_OPL3_VOICES		18

काष्ठा snd_opl3;

/*
 * Instrument record, aka "Patch"
 */

/* FM चालक */
काष्ठा fm_चालक अणु
	अचिन्हित अक्षर am_vib;
	अचिन्हित अक्षर ksl_level;
	अचिन्हित अक्षर attack_decay;
	अचिन्हित अक्षर sustain_release;
	अचिन्हित अक्षर wave_select;
पूर्ण __attribute__((packed));

/* Instrument data */
काष्ठा fm_instrument अणु
	काष्ठा fm_चालक op[4];
	अचिन्हित अक्षर feedback_connection[2];
	अचिन्हित अक्षर echo_delay;
	अचिन्हित अक्षर echo_atten;
	अचिन्हित अक्षर chorus_spपढ़ो;
	अचिन्हित अक्षर trnsps;
	अचिन्हित अक्षर fix_dur;
	अचिन्हित अक्षर modes;
	अचिन्हित अक्षर fix_key;
पूर्ण;

/* type */
#घोषणा FM_PATCH_OPL2	0x01		/* OPL2 2 चालकs FM instrument */
#घोषणा FM_PATCH_OPL3	0x02		/* OPL3 4 चालकs FM instrument */

/* Instrument record */
काष्ठा fm_patch अणु
	अचिन्हित अक्षर prog;
	अचिन्हित अक्षर bank;
	अचिन्हित अक्षर type;
	काष्ठा fm_instrument inst;
	अक्षर name[24];
	काष्ठा fm_patch *next;
पूर्ण;


/*
 * A काष्ठाure to keep track of each hardware voice
 */
काष्ठा snd_opl3_voice अणु
	पूर्णांक  state;		/* status */
#घोषणा SNDRV_OPL3_ST_OFF		0	/* Not playing */
#घोषणा SNDRV_OPL3_ST_ON_2OP	1	/* 2op voice is allocated */
#घोषणा SNDRV_OPL3_ST_ON_4OP	2	/* 4op voice is allocated */
#घोषणा SNDRV_OPL3_ST_NOT_AVAIL	-1	/* voice is not available */

	अचिन्हित पूर्णांक समय;	/* An allocation समय */
	अचिन्हित अक्षर note;	/* Note currently asचिन्हित to this voice */

	अचिन्हित दीर्घ note_off;	/* note-off समय */
	पूर्णांक note_off_check;	/* check note-off समय */

	अचिन्हित अक्षर keyon_reg;	/* KON रेजिस्टर shaकरोw */

	काष्ठा snd_midi_channel *chan;	/* Midi channel क्रम this note */
पूर्ण;

काष्ठा snd_opl3 अणु
	अचिन्हित दीर्घ l_port;
	अचिन्हित दीर्घ r_port;
	काष्ठा resource *res_l_port;
	काष्ठा resource *res_r_port;
	अचिन्हित लघु hardware;
	/* hardware access */
	व्योम (*command) (काष्ठा snd_opl3 * opl3, अचिन्हित लघु cmd, अचिन्हित अक्षर val);
	अचिन्हित लघु समयr_enable;
	पूर्णांक seq_dev_num;	/* sequencer device number */
	काष्ठा snd_समयr *समयr1;
	काष्ठा snd_समयr *समयr2;
	spinlock_t समयr_lock;

	व्योम *निजी_data;
	व्योम (*निजी_मुक्त)(काष्ठा snd_opl3 *);

	काष्ठा snd_hwdep *hwdep;
	spinlock_t reg_lock;
	काष्ठा snd_card *card;		/* The card that this beदीर्घs to */
	अचिन्हित अक्षर fm_mode;		/* OPL mode, see SNDRV_DM_FM_MODE_XXX */
	अचिन्हित अक्षर rhythm;		/* percussion mode flag */
	अचिन्हित अक्षर max_voices;	/* max number of voices */
#अगर IS_ENABLED(CONFIG_SND_SEQUENCER)
#घोषणा SNDRV_OPL3_MODE_SYNTH 0		/* OSS - voices allocated by application */
#घोषणा SNDRV_OPL3_MODE_SEQ 1		/* ALSA - driver handles voice allocation */
	पूर्णांक synth_mode;			/* synth mode */
	पूर्णांक seq_client;

	काष्ठा snd_seq_device *seq_dev;	/* sequencer device */
	काष्ठा snd_midi_channel_set * chset;

#अगर IS_ENABLED(CONFIG_SND_SEQUENCER_OSS)
	काष्ठा snd_seq_device *oss_seq_dev;	/* OSS sequencer device */
	काष्ठा snd_midi_channel_set * oss_chset;
#पूर्ण_अगर
 
#घोषणा OPL3_PATCH_HASH_SIZE	32
	काष्ठा fm_patch *patch_table[OPL3_PATCH_HASH_SIZE];

	काष्ठा snd_opl3_voice voices[MAX_OPL3_VOICES]; /* Voices (OPL3 'channel') */
	पूर्णांक use_समय;			/* allocation counter */

	अचिन्हित लघु connection_reg;	/* connection reg shaकरोw */
	अचिन्हित अक्षर drum_reg;		/* percussion reg shaकरोw */

	spinlock_t voice_lock;		/* Lock क्रम voice access */

	काष्ठा समयr_list tlist;	/* समयr क्रम note-offs and effects */
	पूर्णांक sys_समयr_status;		/* प्रणाली समयr run status */
	spinlock_t sys_समयr_lock;	/* Lock क्रम प्रणाली समयr access */
#पूर्ण_अगर
पूर्ण;

/* opl3.c */
व्योम snd_opl3_पूर्णांकerrupt(काष्ठा snd_hwdep * hw);
पूर्णांक snd_opl3_new(काष्ठा snd_card *card, अचिन्हित लघु hardware,
		 काष्ठा snd_opl3 **ropl3);
पूर्णांक snd_opl3_init(काष्ठा snd_opl3 *opl3);
पूर्णांक snd_opl3_create(काष्ठा snd_card *card,
		    अचिन्हित दीर्घ l_port, अचिन्हित दीर्घ r_port,
		    अचिन्हित लघु hardware,
		    पूर्णांक पूर्णांकegrated,
		    काष्ठा snd_opl3 ** opl3);
पूर्णांक snd_opl3_समयr_new(काष्ठा snd_opl3 * opl3, पूर्णांक समयr1_dev, पूर्णांक समयr2_dev);
पूर्णांक snd_opl3_hwdep_new(काष्ठा snd_opl3 * opl3, पूर्णांक device, पूर्णांक seq_device,
		       काष्ठा snd_hwdep ** rhwdep);

/* opl3_synth */
पूर्णांक snd_opl3_खोलो(काष्ठा snd_hwdep * hw, काष्ठा file *file);
पूर्णांक snd_opl3_ioctl(काष्ठा snd_hwdep * hw, काष्ठा file *file,
		   अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);
पूर्णांक snd_opl3_release(काष्ठा snd_hwdep * hw, काष्ठा file *file);

व्योम snd_opl3_reset(काष्ठा snd_opl3 * opl3);

#अगर IS_ENABLED(CONFIG_SND_SEQUENCER)
दीर्घ snd_opl3_ग_लिखो(काष्ठा snd_hwdep *hw, स्थिर अक्षर __user *buf, दीर्घ count,
		    loff_t *offset);
पूर्णांक snd_opl3_load_patch(काष्ठा snd_opl3 *opl3,
			पूर्णांक prog, पूर्णांक bank, पूर्णांक type,
			स्थिर अक्षर *name,
			स्थिर अचिन्हित अक्षर *ext,
			स्थिर अचिन्हित अक्षर *data);
काष्ठा fm_patch *snd_opl3_find_patch(काष्ठा snd_opl3 *opl3, पूर्णांक prog, पूर्णांक bank,
				     पूर्णांक create_patch);
व्योम snd_opl3_clear_patches(काष्ठा snd_opl3 *opl3);
#अन्यथा
#घोषणा snd_opl3_ग_लिखो	शून्य
अटल अंतरभूत व्योम snd_opl3_clear_patches(काष्ठा snd_opl3 *opl3) अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __SOUND_OPL3_H */
